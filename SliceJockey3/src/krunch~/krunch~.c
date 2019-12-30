/*
 * krunch~.c
 *
 * Copyright 2009 - 2019 Katja Vetter (katjavetter@gmail.com, www.katjaas.nl)
 *
 * Licensed under the Apache License, version 2.0. For the specific language
 * governing permissions and limitations under this license you may obtain a
 * copy at:
 *
 *  www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under this license is distributed on an "as is" basis, without
 * warranties of any kind.
 *
 * *****************************************************************************
 *
 * [krunch~] for Pd (Pure Data, the work of Miller Puckette and others).
 *
 * Non-linear non-clipping wave-map, with powered arctangent curve
 * always running through (x,y) = (1,1). Rotation point is another (lower) point
 * where x = y. Below that point the input is attenuated, above that
 * point the input is amplified. A table is used for efficiency.
 *
 * version 1.0
 * - general code cleanup
 * - mapping table size reduced
 * - added option for extra channel, so two channels can share a table
 *
 * version 0.9
 * - initial version
 */


#include "m_pd.h"
#include <math.h>
#include "bigorsmall.h"
#include "absolute.h"

#define VERSION "1.0"

#if PD_FLOAT_PRECISION == 64
#define LOG log
#define POW pow
#define ATAN atan
#else
#define LOG logf
#define POW powf
#define ATAN atanf
#endif

#define MAPSIZE 512
#define TABRANGE 2
#define BYPASSDEFAULT 1
#define KRUNCHFACTORMIN 0.1
#define KRUNCHFACTORMAX 50.
#define DBPOINTDEFAULT -96.
#define DBPOINTMAX -20.

static const t_float tabrange = TABRANGE;
static const t_float tabscale = (t_float)MAPSIZE / (t_float)TABRANGE;
static const t_float itabscale = (t_float)TABRANGE / (t_float)MAPSIZE;


// global pointer to class struct
static t_class *krunch_class = NULL;


// krunch~ class struct
typedef struct
{
    t_object obj;
    t_float f;                          // for MAINSIGNALIN
    t_float krunchfactor;               // user parameter
    t_float rotationpoint;              // computed from user parameter dBpoint
    t_float quotient;
    t_float exponent;
    unsigned int bypass;                // a flag
    unsigned int nchannels;             // number of channels, one or two
    t_float testvalue1;
    t_float testvalue2;
    t_float mappingtable[MAPSIZE+4];    // extra samples for interpolation
}t_krunch;


static inline t_float krunch_exponent(t_float factor, t_float quotient, t_float point)
{
    return (LOG(point) / LOG(ATAN(factor * point) * quotient));
}


static inline t_float krunch_map(t_float in, t_float factor, t_float quotient, t_float exponent)
{
    return(POW(ATAN(factor * in) * quotient, exponent));
}


static void krunch_fill_mappingtable(t_krunch *x)
{
    t_float factor = x->krunchfactor;

    unsigned int n;
    t_float inputvalue;
    t_float quotient = x->quotient;
    t_float exponent = x->exponent;
    t_float *table = x->mappingtable;

    for(n=0; n<= MAPSIZE; n++)
    {
        inputvalue = (t_float)n * itabscale;
        table[n] = krunch_map(inputvalue, factor, quotient, exponent);
    }
}


static void krunch_set(t_krunch *x)
{
    const t_float one = 1.;
    t_float quotient;
    x->quotient = quotient = one / atan(x->krunchfactor);
    x->exponent = krunch_exponent(x->krunchfactor, quotient, x->rotationpoint);
    krunch_fill_mappingtable(x);
}


static t_int *krunch_perform(t_int *w)
{
    t_krunch *x = (t_krunch *)(w[1]);
    t_sample *input = (t_sample *)(w[2]);
    t_sample *output = (t_sample *)(w[3]);
    t_int blocksize = (t_int)(w[4]);

    // bypass in case of linear mapping
    if(x->bypass)
    {
        while(blocksize--) *output++ = *input++;
        return (w+5);
    }

    const t_float zero = 0., one = 1.;
    t_float in, out, frac, absolutevalue;
    t_float factor = x->krunchfactor;
    t_float quotient = x->quotient;
    t_float exponent = x->exponent;
    t_float *tab = x->mappingtable;
    unsigned int index;

    while (blocksize--)
    {
        in = *input++;

        absolutevalue = fastabs(in);

        if(absolutevalue < tabrange)
        {
            absolutevalue *= tabscale;
            index = (unsigned int)absolutevalue;     // truncate to int
            frac = absolutevalue - (t_float)index;
            out = tab[index] + (frac * (tab[index+1] - tab[index]));// linear interpolation
            if(in < zero) out *= -one;               // negative input values
        }

        // if table size will be exceeded, call mapping function
        else
        {
            out = krunch_map(absolutevalue, factor, quotient, exponent);
            if(in < zero) out *= -one;
        }

        *output++ = out;
    }

    return (w+5);
}
// end of krunch_perform function definition


static t_int *krunch_perform2(t_int *w)
{
    t_krunch *x = (t_krunch *)(w[1]);
    t_sample *inputL = (t_sample *)(w[2]);
    t_sample *inputR = (t_sample *)(w[3]);
    t_sample *outputL = (t_sample *)(w[4]);
    t_sample *outputR = (t_sample *)(w[5]);
    t_int blocksize = (t_int)(w[6]);

    // bypass in case of linear mapping
    if(x->bypass)
    {
        while(blocksize--)
        {
            *outputL++ = *inputL++;
            *outputR++ = *inputR++;
        }
        return (w+7);
    }

    const t_float zero = 0., one = 1.;
    t_float inL, inR, out, frac, absolutevalue;
    t_float factor = x->krunchfactor;
    t_float quotient = x->quotient;
    t_float exponent = x->exponent;
    t_float *tab = x->mappingtable;
    unsigned int index;

    while (blocksize--)
    {
        inL = *inputL++;
        inR = *inputR++;

        absolutevalue = fastabs(inL);

        if(absolutevalue < tabrange)
        {
            absolutevalue *= tabscale;
            index = (unsigned int)absolutevalue;                    // truncate to int
            frac = absolutevalue - (t_float)index;
            out = tab[index] + (frac * (tab[index+1] - tab[index]));// linear interpolation
            if(inL < zero) out *= -one;                              // negative input values
        }

        // if table size will be exceeded, call mapping function
        else
        {
            out = krunch_map(absolutevalue, factor, quotient, exponent);
            if(inL < zero) out *= -one;
        }

        *outputL++ = out;


        //////////// second channel /////////////////////////////////


        absolutevalue = fastabs(inR);

        if(absolutevalue < tabrange)
        {
            absolutevalue *= tabscale;
            index = (unsigned int)absolutevalue;                        // truncate to int
            frac = absolutevalue - (t_float)index;
            out = tab[index] + (frac * (tab[index+1] - tab[index]));    // linear interpolation
            if(inR < zero) out *= -one;                                 // negative input values
        }

        // if table size will be exceeded, call mapping function
        else
        {
            out = krunch_map(absolutevalue, factor, quotient, exponent);
            if(inR < zero) out *= -one;
        }

        *outputR++ = out;
    }

    return (w+7);
}
// end of krunch_perform2 function definition


static void krunch_dsp(t_krunch *x, t_signal **sp)
{
    if(x->nchannels == 1)
    {
        dsp_add(krunch_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
    }
    else
    {
        dsp_add(krunch_perform2, 6, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec,
            sp[3]->s_vec, sp[0]->s_n);
    }
}


static void krunch_krunchfactor(t_krunch *x, t_floatarg krunchfactor)
{
    if(krunchfactor < KRUNCHFACTORMIN)
    {
        krunchfactor = KRUNCHFACTORMIN;
        x->bypass = 1;
    }
    else x->bypass = 0;

    if(krunchfactor > KRUNCHFACTORMAX) krunchfactor = KRUNCHFACTORMAX;
    x->krunchfactor = krunchfactor;
    krunch_set(x);
}


static void krunch_dBpoint(t_krunch *x, t_floatarg dBpoint)
{
    t_float magnitude;
    const t_float logten = 2.302585092994;
    const t_float itwenty = 0.05;

    if(dBpoint < DBPOINTDEFAULT) dBpoint = DBPOINTDEFAULT;
    else if(dBpoint > DBPOINTMAX) dBpoint = DBPOINTMAX;

    magnitude = exp(logten * itwenty * dBpoint);    // convert dB to amplitude
    x->rotationpoint = magnitude;
    krunch_set(x);
}


static void krunch_test(t_krunch *x)    // for debug
{
    post("testvalue1 = %f", x->testvalue1);
    post("testvalue2 = %f", x->testvalue2);
}


static void *krunch_new(t_floatarg nchannels)
{
    if(nchannels != 2.) nchannels = 1.;

    t_krunch *x = NULL;
    x = (t_krunch *)pd_new(krunch_class);
    if(nchannels == 2) inlet_new(&x->obj, &x->obj.ob_pd, &s_signal, &s_signal);
    inlet_new(&x->obj, &x->obj.ob_pd, gensym ("float"), gensym("factor"));
    inlet_new(&x->obj, &x->obj.ob_pd, gensym ("float"), gensym("dBpoint"));
    outlet_new(&x->obj, &s_signal);
    if(nchannels == 2) outlet_new(&x->obj, &s_signal);

    x->nchannels = nchannels;
    x->krunchfactor = KRUNCHFACTORMIN;
    krunch_dBpoint(x, DBPOINTDEFAULT);
    x->bypass = BYPASSDEFAULT;

    return (x);
}
// end of krunch_new function definition


void krunch_tilde_setup(void)
{
    krunch_class = class_new(gensym("krunch~"), (t_newmethod)krunch_new,
        0, sizeof(t_krunch), CLASS_DEFAULT, A_DEFFLOAT, A_NULL);
    CLASS_MAINSIGNALIN(krunch_class, t_krunch, f);
    class_addmethod(krunch_class, (t_method)krunch_dsp, gensym("dsp"), 0);
    class_addmethod(krunch_class, (t_method)krunch_krunchfactor,
        gensym("factor"), A_FLOAT, 0);
    class_addmethod(krunch_class, (t_method)krunch_dBpoint,
        gensym("dBpoint"), A_FLOAT, 0);
    class_addmethod(krunch_class, (t_method)krunch_test, gensym("test"), 0);
    post("[krunch~] version %s written by Katja Vetter", VERSION);
}


