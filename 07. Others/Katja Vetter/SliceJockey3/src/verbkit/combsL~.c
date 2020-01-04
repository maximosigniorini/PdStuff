/*
 * combsL~.c
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
 * [combsL~], class for Pd (Pure Data, the work of Miller Puckette and others).
 * Based on Jehar's freeverb.
 * The class has eight comb filters in parallel. Big float values or inf or NaN
 * at the input are set to zero. A very small number, insignificant in terms of
 * audio signals, is added to the input to avoid the computation of subnormals.
 */


#include "m_pd.h"
#include "bigorsmall.h"

#define DEL0 1116
#define DEL1 1188
#define DEL2 1277
#define DEL3 1356
#define DEL4 1422
#define DEL5 1491
#define DEL6 1557
#define DEL7 1617
#define NCOMBS 8

static const t_float fixedgain = 0.015;
static const t_float scaledecay = 0.28;
static const t_float offsetdecay = 0.7;
static const t_float initialdecay = 0.5;


t_class *combsL_class;


typedef struct
{
    t_float b0[DEL0];
    t_float b1[DEL1];
    t_float b2[DEL2];
    t_float b3[DEL3];
    t_float b4[DEL4];
    t_float b5[DEL5];
    t_float b6[DEL6];
    t_float b7[DEL7];
} t_bufs;


typedef struct
{
    t_object obj;
    t_float f;
    t_bufs bufs;
    t_float in;
    t_float feedback;
    int index[8];
} t_combsL;


#ifndef NOSIMD  // this code profits from SIMD instructions
static inline void combsL_process(t_combsL *x, t_float *input, t_float *output, int n)
{
    t_float in, out;
    t_float feedback = x->feedback;

    while(n--)
    {
        in = *input++ * fixedgain;
        if(bigfloat(in)) in = 0.;
        in += SMALLFLOAT;

        x->in = in;

        out = x->bufs.b0[x->index[0]] + x->bufs.b1[x->index[1]] +
                + x->bufs.b2[x->index[2]] + x->bufs.b3[x->index[3]]
                + x->bufs.b4[x->index[4]] + x->bufs.b5[x->index[5]]
                + x->bufs.b6[x->index[6]] + x->bufs.b7[x->index[7]];

        out = flushsubliminal(out);
        *output++ = out;

        // combfilter sections

        x->bufs.b0[x->index[0]] = x->in + (x->bufs.b0[x->index[0]] * feedback);
        if(++x->index[0] == DEL0) x->index[0] = 0;

        x->bufs.b1[x->index[1]] = x->in + (x->bufs.b1[x->index[1]] * feedback);
        if(++x->index[1] == DEL1) x->index[1] = 0;

        x->bufs.b2[x->index[2]] = x->in + (x->bufs.b2[x->index[2]] * feedback);
        if(++x->index[2] == DEL2) x->index[2] = 0;

        x->bufs.b3[x->index[3]] = x->in + (x->bufs.b3[x->index[3]] * feedback);
        if(++x->index[3] == DEL3) x->index[3] = 0;

        x->bufs.b4[x->index[4]] = x->in + (x->bufs.b4[x->index[4]] * feedback);
        if(++x->index[4] == DEL4) x->index[4] = 0;

        x->bufs.b5[x->index[5]] = x->in + (x->bufs.b5[x->index[5]] * feedback);
        if(++x->index[5] == DEL5) x->index[5] = 0;

        x->bufs.b6[x->index[6]] = x->in + (x->bufs.b6[x->index[6]] * feedback);
        if(++x->index[6] == DEL6) x->index[6] = 0;

        x->bufs.b7[x->index[7]] = x->in + (x->bufs.b7[x->index[7]] * feedback);
        if(++x->index[7] == DEL7) x->index[7] = 0;
    }
}
#endif  // end ifndef NOSIMD


#ifdef NOSIMD   // code optimised for archs without SIMD instructions
static inline void combsL_process(t_combsL *x, t_float *input, t_float *output, int n)
{
    t_float in, out;
    t_float feedback = x->feedback;

    int index0 = x->index[0];
    int index1 = x->index[1];
    int index2 = x->index[2];
    int index3 = x->index[3];
    int index4 = x->index[4];
    int index5 = x->index[5];
    int index6 = x->index[6];
    int index7 = x->index[7];

    t_float *buf0 = (t_float*)&x->bufs.b0[0];
    t_float *buf1 = (t_float*)&x->bufs.b1[0];
    t_float *buf2 = (t_float*)&x->bufs.b2[0];
    t_float *buf3 = (t_float*)&x->bufs.b3[0];
    t_float *buf4 = (t_float*)&x->bufs.b4[0];
    t_float *buf5 = (t_float*)&x->bufs.b5[0];
    t_float *buf6 = (t_float*)&x->bufs.b6[0];
    t_float *buf7 = (t_float*)&x->bufs.b7[0];

    while(n--)
    {
        in = *input++ * fixedgain;
        if(bigfloat(in)) in = 0.;
        in += SMALLFLOAT;

        out = buf0[index0] + buf1[index1] +  + buf2[index2] + buf3[index3]
                 + buf4[index4] + buf5[index5] + buf6[index6] + buf7[index7];

        out = flushsubliminal(out);
        *output++ = out;

        // combfilter sections

        buf0[index0] = in + (buf0[index0] * feedback);
        if(++index0 == DEL0) index0 = 0;

        buf1[index1] = in + (buf1[index1] * feedback);
        if(++index1 == DEL1) index1 = 0;

        buf2[index2] = in + (buf2[index2] * feedback);
        if(++index2 == DEL2) index2 = 0;

        buf3[index3] = in + (buf3[index3] * feedback);
        if(++index3 == DEL3) index3 = 0;

        buf4[index4] = in + (buf4[index4] * feedback);
        if(++index4 == DEL4) index4 = 0;

        buf5[index5] = in + (buf5[index5] * feedback);
        if(++index5 == DEL5) index5 = 0;

        buf6[index6] = in + (buf6[index6] * feedback);
        if(++index6 == DEL6) index6 = 0;

        buf7[index7] = in + (buf7[index7] * feedback);
        if(++index7 == DEL7) index7 = 0;
    }

    x->index[0] = index0;
    x->index[1] = index1;
    x->index[2] = index2;
    x->index[3] = index3;
    x->index[4] = index4;
    x->index[5] = index5;
    x->index[6] = index6;
    x->index[7] = index7;
}
#endif  // end ifdef NOSIMD


static t_int *combsL_perform(t_int *w)
{
    t_combsL *x = (t_combsL*)w[1];
    t_sample *input = (t_sample*)w[2];
    t_sample *output = (t_sample*)w[3];
    t_int vecsize = (int)w[4];

    combsL_process(x, input, output, vecsize);

    return(w+5);
}


static void combsL_decay(t_combsL *x, t_floatarg decay)
{
    if(decay < 0.) decay = 0.;
    if(decay > 1.) decay = 1.;
    x->feedback = (decay * scaledecay) + offsetdecay;
}


static void combsL_dsp(t_combsL *x, t_signal **sp)
{
    dsp_add(combsL_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}


static void *combsL_new(void)
{
    t_combsL *x = (t_combsL*)pd_new(combsL_class);
    inlet_new(&x->obj, &x->obj.ob_pd, &s_float, gensym("decay"));
    outlet_new(&x->obj, &s_signal);
    x->in = 0.;
    combsL_decay(x, initialdecay);
    return x;
}


void combsL_tilde_setup(void)
{
    combsL_class = class_new(gensym("combsL~"), (t_newmethod)combsL_new,
        NULL, sizeof(t_combsL), CLASS_DEFAULT, A_NULL);
    CLASS_MAINSIGNALIN(combsL_class, t_combsL, f);
    class_addmethod(combsL_class, (t_method)combsL_dsp, gensym("dsp"),
        (t_atomtype) 0);
    class_addmethod(combsL_class, (t_method)combsL_decay, gensym("decay"),
        A_FLOAT, 0);
}

