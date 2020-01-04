/*
 * bitflip.c
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
 * [bitflip~] class for Pd (Pure Data, the work of Miller Puckette and others).
 * The scaled and raised signal input is cast to int. The bit at index 5
 * is flipped with xor. A small DC offset is optionally added to create a
 * noise gate effect.
 *
 */


#include <math.h>
#include "m_pd.h"
#include "bigorsmall.h"
#include "absolute.h"

#if PD_FLOAT_PRECISION == 32
#define COS cosf
#define SIN sinf
#else
#define COS cos
#define SIN sin
#endif

#define MASK 255
#define TOGGLEBIT 32
#define UP 128
#define DOWN 160                                // 128 + 32

static const t_float offset = 128.;
static const t_float scaleup = 42.666;          // 128 * 0.3
static const t_float scaledown = 0.005;
static const t_float filterfreq = 40.;          // DC filter cutoff frequency
static const t_float twopi = 6.283185307179586;
static const t_float fixedshiftup = 128.;
static const t_float shiftdown = 160;           // 128 + 32
static const t_float defaultnoisegate = 0.2;

// memcpy forward declaration
void *memcpy(void *to, const void *from, size_t size);


t_class *bitflip_class;


typedef struct
{
    t_object obj;
    t_float f;
    t_float scaleflip;
    t_float scalein;
    t_float shiftup;
    t_float coeff;
    t_float noisegate;
    t_float last;
} t_bitflip;


static t_int *bitflip_perform(t_int *w)
{
    t_bitflip *x = (t_bitflip*)w[1];
    t_sample *input = (t_sample*)w[2];
    t_sample *output = (t_sample*)w[3];
    t_int vecsize = (int)w[4];

    if(!x->scaleflip)
    {
        memcpy(output, input, vecsize * sizeof(t_float));
        return(w+5);
    }

    t_float scalein = x->scalein;
    t_float scaleflip = x->scaleflip;
    t_float coeff = x->coeff;
    t_float last = x->last;
    t_float shiftup = x->shiftup;
    t_float floatflip;
    int flip;

    while(vecsize--)
    {
        floatflip = (*input * scaleup) + shiftup;
        flip = (int)floatflip;
        flip &= MASK;
        flip ^= TOGGLEBIT;
        flip -= DOWN;
        floatflip = (t_float)flip * scaleflip;

        // bit flipped signal is hi pass filtered
        floatflip += coeff * last;
        *output++ = (*input++ * scalein) + floatflip - last ;
        last = floatflip;
    }
    if(bigorsmall(last)) last = 0.;
    x->last = last;
    return(w+5);
}


static void bitflip_noisegate(t_bitflip *x, t_floatarg noisegate)
{
    if(noisegate < 0.) noisegate = 0.;
    else if(noisegate > 1.) noisegate = 1.;

    x->shiftup = noisegate + fixedshiftup;
}


static void bitflip_mix(t_bitflip *x, t_floatarg mix)
{
    if(mix < 0.)
    {
        mix = 0.;
        x->last = 0.;
    }
    if(mix > 1.) mix = 1.;

    x->scaleflip = mix * scaledown;
    x->scalein = 1. - mix;
}


static void bitflip_dsp(t_bitflip *x, t_signal **sp)
{
    dsp_add(bitflip_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
    x->coeff = 1. - ((filterfreq * twopi) / (t_float)sp[0]->s_sr);
    x->last = 0.;
}


static void *bitflip_new(void)
{
    t_bitflip *x = (t_bitflip*)pd_new(bitflip_class);
    inlet_new(&x->obj, &x->obj.ob_pd, &s_float, gensym("mix"));
    inlet_new(&x->obj, &x->obj.ob_pd, &s_float, gensym("noisegate"));
    outlet_new(&x->obj, &s_signal);
    x->last = 0.;
    bitflip_noisegate(x, defaultnoisegate);
    bitflip_mix(x, 0.);
    return x;
}


void bitflip_tilde_setup(void)
{
    bitflip_class = class_new(gensym("bitflip~"), (t_newmethod)bitflip_new,
        NULL, sizeof(t_bitflip), CLASS_DEFAULT, A_NULL);
    CLASS_MAINSIGNALIN(bitflip_class, t_bitflip, f);
    class_addmethod(bitflip_class, (t_method)bitflip_dsp, gensym("dsp"),
        (t_atomtype) 0);
    class_addmethod(bitflip_class, (t_method)bitflip_mix, gensym("mix"),
        A_FLOAT, 0);
    class_addmethod(bitflip_class, (t_method)bitflip_noisegate, gensym("noisegate"),
        A_FLOAT, 0);
    post("[bitflip~] version 1.0 by Katja Vetter");
}

