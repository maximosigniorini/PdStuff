/*
 * qompand~.c
 *
 * Copyright 2013 - 2019 Katja Vetter (katjavetter@gmail.com, www.katjaas.nl)
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
 * qompand~.c, class for Pd (Pure Data, the work of Miller Puckette and others).
 * Compression, expansion and limiting based on instantaneous amplitude.
 */


#include <math.h>
#include "m_pd.h"
#include "bigorsmall.h"
#include "complexifier.h"
#include "fastsqrt.h"
#include "absolute.h"

#define VERSION "1.0"
#define MAPPINGSIZE 512
#define MAPPINGTABLESIZE (MAPPINGSIZE+4)
#define COUNT 2048                         // sample counter for bypass crossover

#if PD_FLOAT_PRECISION == 64
#define SIN sinf
#define EXP exp
#define POW pow
#define LOG log
#else
#define SIN sinf
#define EXP expf
#define POW powf
#define LOG logf
#endif


static const t_float one = 1.;
static const t_float isqrt2 = 0.707106781186548;
static const t_float halfpi = 1.570796326794897;
static const t_float logten = 2.302585092994046;
static const t_float mappingsize = (t_float)MAPPINGSIZE;
static const t_float initialdBpoint = -12.;


typedef struct
{
    t_object x_obj;
    t_float f;
    int bypass;
    int blocksize;
    t_float fadein;
    t_float amount;
    t_float dBpoint;
    t_float peakenv;
    t_float decayratio;
    t_float decay;
    t_float maptable[MAPPINGTABLESIZE];
    t_cfilters cfilters;
}t_qompand;


static t_class *qompand_class = NULL;


static inline t_float read_table(t_float *tab, t_float phase)
{
    phase *= mappingsize;
    int index = (int)phase;
    t_float fraction = phase - (t_float)index;

    // linear interpolation
    return (tab[index] + fraction * (tab[index+1] - tab[index]));
}


static inline t_float qompand_sample(t_qompand *x, t_float in, int z)
{
    t_float out, amp, ampcorrection;
    t_complexout complexout;

    in += SMALLFLOAT;           // SMALLFLOAT: anti-subnormals
    if(bigfloat(in)) in = 0.;

    // complexify sample and produce amplitude peak envelope
    complexify_sample(&x->cfilters, in, &complexout, z);
    amp = cheapsqrt(complexout.re * complexout.re + complexout.im * complexout.im);
    x->peakenv *= x->decayratio;
    if(amp > x->peakenv) x->peakenv = amp;

    // use amplitude peak envelope for amplitude correction
    if(x->peakenv > 1.) ampcorrection = isqrt2 / x->peakenv;       // limiter
    else ampcorrection = read_table(x->maptable, x->peakenv);      // compander
    out = (complexout.re + complexout.im) * ampcorrection;

    if(smallfloat(out)) out = 0.;
    return out;
}


static void qompand_vector(t_qompand *x, t_float *input, t_float *output, int vecsize)
{
    t_float in;
    vecsize >>= 1;

    while(vecsize--)
    {
        in = *input++;
        *output++ = qompand_sample(x, in, 0);
        in = *input++;
        *output++ = qompand_sample(x, in, 1);
    }
}


// fade in from bypass to qompander
static void qompand_fadein(t_qompand *x, t_float *input, t_float *output, int vecsize)
{
    int n, z = 0;
    t_float in;
    t_float fadein = x->fadein;
    t_float fadeout = one - x->fadein;
    const t_float faderatio = one / (t_float)COUNT;

    for(n=0; n<vecsize; n++)
    {
        in = *input++;
        *output++ = fadein * qompand_sample(x, in, z) + fadeout * in;
        fadein += faderatio;
        fadeout -= faderatio;
        z = (z + 1) & 1;
    }

    if(fadein >= (one - faderatio))
    {
        x->bypass = 0;
        fadein = 0.;
    }
    x->fadein = fadein;
}


// fade out from qompander to bypass
static void qompand_fadeout(t_qompand *x, t_float *input, t_float *output, int vecsize)
{
    int n, z = 0;
    t_float in;
    t_float fadein = x->fadein;
    t_float fadeout = one - x->fadein;
    const t_float faderatio = one / (t_float)COUNT;

    for(n=0; n<vecsize; n++)
    {
        in = *input++;
        *output++ = fadeout * qompand_sample(x, in, z) + fadein * in;
        fadein += faderatio;
        fadeout -= faderatio;
        z = (z + 1) & 1;
    }

    if(fadein >= (one - faderatio))
    {
        x->bypass = 1;
        fadein = 0.;
    }
    x->fadein = fadein;
}


static t_int *qompand_perform(t_int *w)
{
    t_qompand *x = (t_qompand *)(w[1]);
    t_sample *input = (t_sample *)(w[2]);
    t_sample *output = (t_sample *)(w[3]);
    int vecsize = (t_int)(w[4]);

    if(vecsize == 1) goto out;

    else if(x->bypass)
    {
        if(x->bypass == 3) qompand_fadein(x, input, output, vecsize);
        else if(x->bypass == 4) qompand_fadeout(x, input, output, vecsize);
        else goto out;
    }

    else qompand_vector(x, input, output, vecsize);

    return (w+5);

out:
    while(vecsize--) *output++ = *input++;
    return (w+5);
}


static t_float qompand_exponent(t_float dBpoint)
{
    t_float rms, exponent;
    const t_float itwenty = 0.05;

    rms = EXP((logten * itwenty) * dBpoint);
    exponent = (LOG(rms)/LOG(SIN(rms * halfpi)));
    return exponent;
}


// fill table with amplitude amounts based on desired amplitude curve
static void qompand_fill_table(t_qompand *x)
{
    int n;
    t_float peakenv, curve, line, exponent;
    t_float *table = &x->maptable[0];

    const t_float amount = x->amount;
    const t_float amountcomplement = one - x->amount;
    const t_float angle = halfpi / (t_float)MAPPINGSIZE;
    const t_float ratio = one / (t_float)MAPPINGSIZE;

    exponent = qompand_exponent(x->dBpoint);

    for(n=1; n<MAPPINGSIZE; n++)
    {
        peakenv = n * ratio;                                  // input peakenv
        curve = POW(SIN(angle * n), exponent) * amount;
        line = n * ratio * amountcomplement;
        table[n] = (curve + line) * isqrt2 / peakenv;         // amp ratio curve
    }
    table[0] = table[1];           // to avoid division by peakenv = 0
    table[MAPPINGSIZE] = isqrt2;   // one extra element for linear interpolation
}


// compander amount range is 0. till 1.
static void qompand_amount(t_qompand *x, t_floatarg amount)
{
    if(amount < 0.) amount = 0.;
    else if(amount > 1.) amount = 1.;

    if(amount != x->amount)
    {
        x->amount = amount;
        qompand_fill_table(x);
    }
}


// decaytime for amplitude peak enveloper, range is 20 till 220 milliseconds
static void qompand_decay(t_qompand *x, t_floatarg decay)
{
    const t_float millisec = 1000.;
    const t_float decayscale = 200.;
    const t_float decayoffset = 20.;

    if(decay < 0.) decay = 0.;
    else if(decay > 1.) decay = 1.;

    x->decay = decay;

    decay = (decay * decayscale) + decayoffset;  // convert to millisec

    x->decayratio = EXP(-millisec / (sys_getsr() * decay));
}


static void qompand_dBpoint(t_qompand *x, t_floatarg dBpoint)
{
    if(dBpoint < -18.) dBpoint = -18.;
    else if(dBpoint > -6.) dBpoint = -6.;

    if(dBpoint != x->dBpoint)
    {
        x->dBpoint = dBpoint;
        qompand_fill_table(x);
    }
}


static void qompand_dsp(t_qompand *x, t_signal **sp)
{
    dsp_add(qompand_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
    x->blocksize = sp[0]->s_n;
    qompand_decay(x, x->decay);
    if(sp[0]->s_n == 1) post("[qompand~]: block size 1 not supported");
}


static void *qompand_new()
{
    t_qompand *x = (t_qompand *)pd_new(qompand_class);
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("amount"));
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("dBpoint"));
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("decay"));
    outlet_new(&x->x_obj, &s_signal);
    init_cfilters(&x->cfilters);
    x->bypass = 0;
    x->peakenv = 0.;
    x->amount = 0.;
    x->decay = 0.;
    x->dBpoint = initialdBpoint;
    qompand_fill_table(x);

    return (x);
}


static void qompand_bypass(t_qompand *x, t_floatarg fbypass)
{
    int bypass = 0;
    if(fbypass) bypass = 1;

    if(x->blocksize > 2048)     // no fade in or fade out for blocksize > 2048
    {
        x->bypass = bypass;
        post("[qompand~] bypass: no smooth crossfade for blocksize > 2048");
        return;
    }

    if(bypass < x->bypass) // we go from bypass to qompander, 'fadein'
    {
        x->bypass = 3;
    }
    else if(bypass > x->bypass)  // we go from qompander to bypass, 'fadeout'
    {
        x->bypass = 4;
        x->peakenv = 0.;
    }
}


void qompand_tilde_setup(void)
{
    qompand_class = class_new(gensym("qompand~"), (t_newmethod)qompand_new,
        0, sizeof(t_qompand), 0, 0, 0);
    CLASS_MAINSIGNALIN(qompand_class, t_qompand, f);
    class_addmethod(qompand_class, (t_method)qompand_dsp, gensym("dsp"), 0);
    class_addmethod(qompand_class, (t_method)qompand_amount,
        gensym("amount"), A_FLOAT, 0);
    class_addmethod(qompand_class, (t_method)qompand_decay, gensym("decay"),
        A_FLOAT, 0);
    class_addmethod(qompand_class, (t_method)qompand_dBpoint, gensym("dBpoint"),
                    A_FLOAT, 0);
    class_addmethod(qompand_class, (t_method)qompand_bypass, gensym("bypass"),
                    A_FLOAT, 0);
    post("[qompand~] version %s, written by Katja Vetter", VERSION);
}
