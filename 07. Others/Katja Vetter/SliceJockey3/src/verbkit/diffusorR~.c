/*
 * diffusorR~.c
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
 * [diffusorR~], class for Pd (Pure Data, the work of Miller Puckette and others).
 * Based on Jehar's freeverb.
 * The diffusor has four allpass filters in series. Big float values or inf or NaN
 * at the input are set to zero. A very small number, insignificant in terms of
 * audio signals, is added to the input to avoid the computation of subnormals.
 *
 */


#include "m_pd.h"
#include "bigorsmall.h"

#define STEREOSPREAD 23

#define DEL1 (556 + STEREOSPREAD)
#define DEL2 (441 + STEREOSPREAD)
#define DEL3 (341 + STEREOSPREAD)
#define DEL4 (225 + STEREOSPREAD)
#define NDIFFUSORS 4

static const t_float feedback = 0.5;

t_class *diffusorR_class;


typedef struct
{
    t_float b1[DEL1];
    t_float b2[DEL2];
    t_float b3[DEL3];
    t_float b4[DEL4];
} t_bufs;


typedef struct
{
    t_object obj;
    t_float f;
    t_bufs bufs;
    t_int index[NDIFFUSORS];
} t_diffusorR;



static t_int *diffusorR_perform(t_int *w)
{
    t_diffusorR *x = (t_diffusorR*)w[1];
    t_sample *input = (t_sample*)w[2];
    t_sample *output = (t_sample*)w[3];
    t_int vecsize = (int)w[4];

    t_int i1 = x->index[0];
    t_int i2 = x->index[1];
    t_int i3 = x->index[2];
    t_int i4 = x->index[3];

    t_float in, out;
    t_float buf1, buf2, buf3, buf4;

    while(vecsize--)
    {
        in = *input++;
        if(bigfloat(in)) in = 0.;

        buf1 = x->bufs.b1[i1];
        buf2 = x->bufs.b2[i2];
        buf3 = x->bufs.b3[i3];
        buf4 = x->bufs.b4[i4];

        in += SMALLFLOAT;

        // first allpass section
        x->bufs.b1[i1++] = in + (buf1 * feedback);
        out = buf1 - in;
        if(i1 == DEL1) i1 = 0;

        // second allpass section
        x->bufs.b2[i2++] = out + (buf2 * feedback);
        out = buf2 - out;
        if(i2 == DEL2) i2 = 0;

        // third allpass section
        x->bufs.b3[i3++] = out + (buf3 * feedback);
        out = buf3 - out;
        if(i3 == DEL3) i3 = 0;

        // fourth allpass section
        x->bufs.b4[i4++] = out + (buf4 * feedback);
        out = buf4 - out;
        if(i4 == DEL4) i4 = 0;

        if(smallfloat(out)) out = 0.;
        *output++ = out;
    }

    x->index[0] = i1;
    x->index[1] = i2;
    x->index[2] = i3;
    x->index[3] = i4;

    return(w+5);
}


static void diffusorR_dsp(t_diffusorR *x, t_signal **sp)
{
    dsp_add(diffusorR_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}


static void *diffusorR_new(void)
{
    t_diffusorR *x = (t_diffusorR*)pd_new(diffusorR_class);
    outlet_new(&x->obj, &s_signal);
    return x;
}


void diffusorR_tilde_setup(void)
{
    diffusorR_class = class_new(gensym("diffusorR~"), (t_newmethod)diffusorR_new,
        NULL, sizeof(t_diffusorR), CLASS_DEFAULT, A_NULL);
    CLASS_MAINSIGNALIN(diffusorR_class, t_diffusorR, f);
    class_addmethod(diffusorR_class, (t_method)diffusorR_dsp, gensym("dsp"),
        (t_atomtype) 0);
}

