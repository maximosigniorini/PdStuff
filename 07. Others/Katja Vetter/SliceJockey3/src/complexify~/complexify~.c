/*
 * complexify~.c
 *
 * Copyright 2019 Katja Vetter (katjavetter@gmail.com, www.katjaas.nl)
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
 * [complexify~], class for Pd (Pure Data, the work of Miller Puckette and others).
 * Makes an analytic signal with coefficients of Olli Niemitalo for two cascades
 * of maximum-phase allpass filters (see complexifier.h).
 */


#include "m_pd.h"
#include "bigorsmall.h"
#include "complexifier.h"

#define VERSION "1.0"


typedef struct
{
    t_object x_obj;
    t_float f;
    int z;
    t_cfilters cfilters;
}t_complexify;


static t_class *complexify_class = NULL;


static void *complexify_new()
{
    t_complexify *x = (t_complexify *)pd_new(complexify_class);

    outlet_new(&x->x_obj, &s_signal);
    outlet_new(&x->x_obj, &s_signal);
    init_cfilters(&x->cfilters);

    return (x);
}


static t_int *complexify_perform(t_int *w)
{
    t_complexify *x = (t_complexify *)(w[1]);
    t_sample *input = (t_sample *)(w[2]);
    t_sample *outputL = (t_sample *)(w[3]);
    t_sample *outputR = (t_sample *)(w[4]);
    int vecsize = (t_int)(w[5]);

    t_float in;
    t_complexout complexout;
    vecsize >>= 1;

    while (vecsize--)
    {
        in = *input++ + SMALLFLOAT;         // SMALLFLOAT: anti-subnormals
        if(bigfloat(in)) in = 0.;

        complexify_sample(&x->cfilters, in, &complexout, 0);

        if(smallfloat(complexout.re)) complexout.re = 0.;
        if(smallfloat(complexout.im)) complexout.im = 0.;
        *outputL++ = complexout.re;
        *outputR++ = complexout.im;

        ///// another sample //////////////////////////////
        in = *input++ + SMALLFLOAT;
        if(bigfloat(in)) in = 0.;

        complexify_sample(&x->cfilters, in, &complexout, 1);

        if(smallfloat(complexout.re)) complexout.re = 0.;
        if(smallfloat(complexout.im)) complexout.im = 0.;
        *outputL++ = complexout.re;
        *outputR++ = complexout.im;
    }

    return (w+6);
}

static t_int *complexify_perform_one(t_int *w)
{
    t_complexify *x = (t_complexify *)(w[1]);
    t_sample *input = (t_sample *)(w[2]);
    t_sample *outputL = (t_sample *)(w[3]);
    t_sample *outputR = (t_sample *)(w[4]);

    t_float in;
    t_complexout complexout;

    in = *input++ + SMALLFLOAT;     // SMALLFLOAT: anti-subnormals
    if(bigfloat(in)) in = 0.;

    complexify_sample(&x->cfilters, in, &complexout, x->z);

    if(smallfloat(complexout.re)) complexout.re = 0.;
    if(smallfloat(complexout.im)) complexout.im = 0.;
    *outputL = complexout.re;
    *outputR = complexout.im;

    x->z = (x->z + 1) & ZMASK;      // flip flop z-index (0 1 0 1 etc)

    return (w+6);
}


static void complexify_dsp(t_complexify *x, t_signal **sp)
{
    if(sp[0]->s_n == 1) // if blocksize is 1
    {
        dsp_add(complexify_perform_one, 5, x, sp[0]->s_vec,
            sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
        x->z = 0;
    }

    // if blocksize is > 1
    else dsp_add(complexify_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec,
        sp[2]->s_vec, sp[0]->s_n);
}


void complexify_tilde_setup(void)
{
    complexify_class = class_new(gensym("complexify~"), (t_newmethod)complexify_new,
        0, sizeof(t_complexify), 0, 0, 0);
    CLASS_MAINSIGNALIN(complexify_class, t_complexify, f);
    class_addmethod(complexify_class, (t_method)complexify_dsp, gensym("dsp"), 0);
    post("[complexify~] version %s, written by Katja Vetter", VERSION);
    post("[complexify~] is based on Olli Niemitalo's coefficients");
}
