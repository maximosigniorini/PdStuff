/*
 * damp~.c
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
 * [damp~], class for Pd (Pure Data, the work of Miller Puckette and others).
 *
 * This is a state variable filter with lo pass output only.
 *
 * For Intel:
 * A very small number, insignificant in terms of audio signals, is added to
 * the input to avoid computation of subnormals. Big float values or inf or NaN
 * are cleared once per dsp block so they can't recirculate permanently.
 *
 */


#include <math.h>
#include "m_pd.h"
#include "bigorsmall.h"

#if PD_FLOAT_PRECISION == 64
#define SIN sin
#else
#define SIN sinf
#endif


static const t_float twopi = 6.283185307179586;
static const t_float halfpi = 1.570796326794897;
static const t_float dampcoeff = 1.4;
static const t_float basefreq = 200.;
static const t_float tonedefault = 0.3;


t_class *damp_class;


typedef struct
{
    t_object obj;
    t_float f;
    t_float tone;   // user setting
    t_float sinomega;
    t_float lo;
    t_float band;
} t_damp;


static t_int *damp_perform(t_int *w)
{
    t_damp *x = (t_damp*)w[1];
    t_sample *input = (t_sample*)w[2];
    t_sample *output = (t_sample*)w[3];
    t_int vecsize = (int)w[4];

    t_float in, high;
    t_float sinomega = x->sinomega;
    t_float band = x->band;
    t_float lo = x->lo;

    while(vecsize--)
    {
        in = *input++;
        *output++ = lo = lo + (band * sinomega);
        high = in - lo - (band * dampcoeff);
        band += sinomega * high;
    }

    if(bigorsmall(band)) band = 0.;
    if(bigorsmall(lo)) lo = 0.;
    x->band = band;
    x->lo = lo;

    return(w+5);
}


static void damp_tone(t_damp *x, t_floatarg tone)
{
    t_float sr, freq, omega;

    if(tone<0.) tone = 0.;
    if(tone>1.) tone = 1.;
    x->tone = tone;

    tone *= tone;                                   // quadratic parameter curve

    sr = (t_float)(sys_getsr());
    freq = ((((t_float)sr / 4.) - basefreq) * tone) + basefreq;
    omega = (freq / sr) * twopi;                    // frequency in radians
    if(omega < 0.) omega = 0.;
    if(omega > halfpi) omega = halfpi;
    x->sinomega = SIN(omega);
}

static void damp_dsp(t_damp *x, t_signal **sp)
{
    dsp_add(damp_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
    damp_tone(x, x->tone);
}


static void *damp_new(void)
{
    t_damp *x = (t_damp*)pd_new(damp_class);
    inlet_new(&x->obj, &x->obj.ob_pd, &s_float, gensym("tone"));
    outlet_new(&x->obj, &s_signal);
    x->band = 0.;
    x->lo = 0.;
    x->tone = tonedefault;
    return x;
}


void damp_tilde_setup(void)
{
    damp_class = class_new(gensym("damp~"), (t_newmethod)damp_new,
        NULL, sizeof(t_damp), CLASS_DEFAULT, A_NULL);
    CLASS_MAINSIGNALIN(damp_class, t_damp, f);
    class_addmethod(damp_class, (t_method)damp_dsp, gensym("dsp"),
        (t_atomtype) 0);
    class_addmethod(damp_class, (t_method)damp_tone, gensym("tone"),
        A_FLOAT, 0);
}

