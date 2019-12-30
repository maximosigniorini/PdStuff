/*
 * duck~.c
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
 * [duck~], class for Pd (Pure Data, the work of Miller Puckette and others).
 * Simple enveloper based on absolute signal values.
*/


#include <math.h>
#include "m_pd.h"
#include "bigorsmall.h"
#include "absolute.h"

#define VERSION "1.0"


#if PD_FLOAT_PRECISION == 64
#define EXP exp
#else
#define EXP expf
#endif


static const t_float one = 1.;
static const t_float initialdecay = 0.3;


typedef struct
{
    t_object x_obj;
    t_float f;
    int bypass;
    t_float depth;
    t_float peakenv;
    t_float decayratio;
    t_float decaysetting;
    t_float damped;
}t_duck;


static t_class *duck_class = NULL;


static inline t_float duck_sample(t_duck *x, t_float in)
{
    const t_float ampfloor = 1E-09;    // avoid subnnormals and division by zero
    t_float clipped, ampratio;

    if(bigfloat(in)) in = 0.;
    in = x->depth * fastabs(in) + ampfloor;

    x->peakenv *= x->decayratio;
    if(in > x->peakenv) x->peakenv = in;

    // amplitude envelope ratio
    clipped = x->peakenv;
    if(clipped > 1.) clipped = 1.;
    ampratio = clipped / x->peakenv;

    // lo pass filter
    ampratio *= one - x->decayratio;
    x->damped = x->damped * x->decayratio + ampratio;

    return x->damped;
}


static t_int *duck_perform(t_int *w)
{
    t_duck *x = (t_duck *)(w[1]);
    t_sample *input = (t_sample *)(w[2]);
    t_sample *output = (t_sample *)(w[3]);
    int vecsize = (t_int)(w[4]);

    if(x->bypass) goto out;

    t_float in;

    while(vecsize--)
    {
        in = *input++;
        *output++ = duck_sample(x, in);
    }

    return (w+5);

out:
    while(vecsize--) *output++ = 1.;
    return (w+5);
}


// decaytime for peak envelope and damper, range is 20 till 220 milliseconds
static void duck_decay(t_duck *x, t_floatarg decay)
{
    const t_float millisec = 1000.;
    const t_float decayscale = 200.;
    const t_float decayoffset = 20.;

    if(decay < 0.) decay = 0.;
    else if(decay > 1.) decay = 1.;

    x->decaysetting = decay;

    decay = (decay * decayscale) + decayoffset;  // convert to millisec

    x->decayratio = exp(-millisec / (sys_getsr() * decay));
}


static void duck_depth(t_duck *x, t_floatarg depth)
{
    const float maxdepth = 20;
    if(depth < 0.) depth = 0.;
    else if(depth > 1.) depth = 1.;
    x->depth = depth * maxdepth;
}


static void duck_bypass(t_duck *x, t_floatarg bypass)
{
    if(bypass)
    {
        x->bypass = 1;
        x->peakenv = 0.;
        x->damped = 0.;
    }
    else x->bypass = 0;
}


static void duck_dsp(t_duck *x, t_signal **sp)
{
    dsp_add(duck_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
    duck_decay(x, x->decaysetting);
}


static void *duck_new()
{
    t_duck *x = (t_duck *)pd_new(duck_class);
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("depth"));
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("response"));
    outlet_new(&x->x_obj, &s_signal);

    x->decaysetting = initialdecay;
    x->peakenv = 0.;
    x->damped = 0.;

    return (x);
}


void duck_tilde_setup(void)
{
    duck_class = class_new(gensym("duck~"), (t_newmethod)duck_new,
        0, sizeof(t_duck), 0, 0, 0);
    CLASS_MAINSIGNALIN(duck_class, t_duck, f);
    class_addmethod(duck_class, (t_method)duck_dsp, gensym("dsp"), 0);
    class_addmethod(duck_class, (t_method)duck_depth, gensym("depth"),
        A_FLOAT, 0);
    class_addmethod(duck_class, (t_method)duck_decay, gensym("response"),
        A_FLOAT, 0);
    class_addmethod(duck_class, (t_method)duck_bypass, gensym("bypass"),
        A_FLOAT, 0);
    post("[duck~] version %s, written by Katja Vetter", VERSION);
}
