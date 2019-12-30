/*
 * instantamp~.c
 *
 * Copyright 2010 - 2019 Katja Vetter (katjavetter@gmail.com, www.katjaas.nl)
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
 * [instantamp~], class for Pd (Pure Data, the work of Miller Puckette and others).
 * Finds instantaneous amplitudes from real signal input, using coefficients of
 * Olli Niemitalo for two cascades of maximum-phase allpass filters (see
 * complexifier.h).
 *
 */


#include <math.h>
#include "m_pd.h"
#include "bigorsmall.h"
#include "export.h"
#include "complexifier.h"
#include "fastsqrt.h"

#define VERSION "1.0"

static const t_float isqrt2 = 0.707106781186548;


typedef struct
{
    t_object x_obj;
    t_float f;
    int z;
    t_cfilters cfilters;
}t_instantamp;


static t_class *instantamp_class = NULL;


static void *instantamp_new()
{
    t_instantamp *x = (t_instantamp *)pd_new(instantamp_class);
    outlet_new(&x->x_obj, &s_signal);
    init_cfilters(&x->cfilters);

    return (x);
}


static t_int *instantamp_perform(t_int *w)
{
    t_instantamp *x = (t_instantamp *)(w[1]);
    t_sample *input = (t_sample *)(w[2]);
    t_sample *output = (t_sample *)(w[3]);
    int vecsize = (t_int)(w[4]);

    t_float in, amp;
    t_complexout complexout;
    vecsize >>= 1;

    while (vecsize--)
    {
        in = *input++ + SMALLFLOAT;         // SMALLFLOAT: anti-subnormals
        if(bigfloat(in)) in = 0.;

        complexify_sample(&x->cfilters, in, &complexout, 0);
        amp = cheapsqrt(complexout.re * complexout.re + complexout.im * complexout.im);

        if(smallfloat(amp)) amp = 0.;
        *output++ = amp * isqrt2;


        ///// another sample //////////////////////////////
        in = *input++ + SMALLFLOAT;
        if(bigfloat(in)) in = 0.;

        complexify_sample(&x->cfilters, in, &complexout, 1);
        amp = cheapsqrt(complexout.re * complexout.re + complexout.im * complexout.im);

        if(smallfloat(amp)) amp = 0.;
        *output++ = amp * isqrt2;
    }

    return (w+5);
}

static t_int *instantamp_perform_one(t_int *w)
{
    t_instantamp *x = (t_instantamp *)(w[1]);
    t_sample *input = (t_sample *)(w[2]);
    t_sample *output = (t_sample *)(w[3]);


    t_float in, amp;
    t_complexout complexout;

    in = *input++ + SMALLFLOAT;                // SMALLFLOAT: anti-subnormals
    if(bigfloat(in)) in = 0.;

    complexify_sample(&x->cfilters, in, &complexout, x->z);
    amp = cheapsqrt(complexout.re * complexout.re + complexout.im * complexout.im);

    if(smallfloat(amp)) amp = 0.;
    *output++ = amp * isqrt2;

    x->z = (x->z + 1) & ZMASK;                 // flip flop z-index (0 1 0 1 etc)

    return (w+5);
}


static void instantamp_dsp(t_instantamp *x, t_signal **sp)
{
    if(sp[0]->s_n == 1) // if blocksize is 1
    {
        dsp_add(instantamp_perform_one, 4, x, sp[0]->s_vec,
            sp[1]->s_vec, sp[0]->s_n);
        x->z = 0;
    }

    // if blocksize is > 1
    else dsp_add(instantamp_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}


void instantamp_tilde_setup(void)
{
    instantamp_class = class_new(gensym("instantamp~"), (t_newmethod)instantamp_new,
        0, sizeof(t_instantamp), 0, 0, 0);
    CLASS_MAINSIGNALIN(instantamp_class, t_instantamp, f);
    class_addmethod(instantamp_class, (t_method)instantamp_dsp, gensym("dsp"), 0);
    post("[instantamp~] version %s, written by Katja Vetter", VERSION);
}
