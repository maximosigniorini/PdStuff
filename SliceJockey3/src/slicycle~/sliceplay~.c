/*
 * sliceplay~.c
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
 * [sliceplay~]  class for Pd (Pure Data, the work of Miller Puckette and others).
 *
 * version 1.0 created Feb. 2013
 * - improved indexing method reduces aliasing
 * - cubic interpolation added, reduces aliasing further
 *
 * version 0.9.12 created 12/10/2010
 * - addition of 'interrupt' method and fade-out of interrupted slice
 * - addition of method and message selector 'minspeed' for minimum playback speed
 * - addition of play status message outlet
 * - negative cuepoints are now ignored, not interpreted modulo-loopsize
 *
 * version 0.9.11:
 * - used garray_getfloatwords() instead of garray_getfloatarray(),
 *   for 64 bit compatibility
 *
 * version 0.91:
 * - fixed bug with playback speed
 * - amplitude compensation is now variable user parameter
 *
 * version 0.9: initial version 11/17/09
 *
 * ****************************************************************************/


#include "m_pd.h"                   // Pure Data header file
#include "absolute.h"               // for fastabs()
#include "fastround.h"              // for fastround()

#define VERSION "1.0"
#define INTERRUPTDEFAULT 0          // default: no interrupt of actual slice playback
#define COMPENSATIONDEFAULT 0.      // default: no amplitude compensation
#define SPEEDDEFAULT 1.             // initial playback speed
#define MINSPEEDDEFAULT 0.125       // default minimum playback speed
#define INTERPDEFAULT 1.            // default interpolation type (0.=linear 1.=cubic)


// typed literal constants for cubic interpolation etc.
static const t_float half = 0.5;
static const t_float one = 1.;
static const t_float two = 2.;
static const t_float three = 3.;
static const t_float pointsixteen = 0.1666666666666666;


// global pointer to class struct
static t_class *sliceplay_class;


// slicrec~ class struct
typedef struct
{
    t_object x_obj;                 // pointer to instance of this struct
    t_int startindex;               // start point of slice
    t_int currentindex;             // last used index for playback
    t_int fadeoutpoint;             // index where a fade out of previous slice shall start
    t_float minspeed;               // minimum playback speed, user settinge
    t_float speed;                  // playback speed for coming slices, user setting
    t_float slicespeed;             // playback speed of current slice
    t_float fadeoutspeed;           // playback speed of previous slice
    t_float counter;                // to count steps for slice indexing
    t_float fadeoutcounter;         // to count steps for fadeout indexing
    t_float compensationsetting;    // amplitude compensation user parameter 0 - 1
    t_float compensationfactor;     // amplitude compensation factor of current slice
    t_float fadeoutcompensation;    // amplitude compensation factor of fade out tail
    t_int playtimer;                // playback countdown timer
    t_int fadeouttimer;             // fade out countdown timer
    t_int interrupt;                // flag for interrupt status
    t_int loopsize;                 // largest power of two that fits in external array
    t_int loopmask;                 // bitwise-and mask for loopsize
    t_word *arraypointer;           // pointer to the global / external array
    t_symbol *arrayname;            // pointer to struct containing global / external array name
    t_outlet *playstatusoutlet;     // outlet for play status message
    t_clock *statusclock;           // timer for play status message
    t_float testvalue;              // for debug
    void (*pPlaybackMethod)();      // pointer to playback method (linear or cubic interp.)
    void (*pOverlapMethod)();       // pointer to overlap method (linear or cubic interp.)
}t_sliceplay;


static void sliceplay_tick(t_sliceplay *x, t_int playstatus)
{
    outlet_float(x->playstatusoutlet, playstatus);  // playstatus is 0 or slice length
}


static void sliceplay_free(t_sliceplay *x)
{
    if(x->statusclock) clock_free(x->statusclock);
}


static void sliceplay_linear(t_sliceplay *x, t_float *output, t_int blocksize)
{
    t_float a, b, slicephase, frac;
    t_int index = 0, sliceindex = 0;

    t_word *arraypointer = x->arraypointer;
    t_int loopmask = x->loopmask;
    t_int playtimer = x->playtimer;
    t_int startindex = x->startindex;
    t_float counter = x->counter;
    t_float compensation= x->compensationfactor;
    t_float speed = x->slicespeed;

    for(;blocksize; blocksize--, output++)
    {
        *output = 0.;

        if(playtimer)
        {
            slicephase = counter * speed;
            sliceindex = (t_int)slicephase;
            frac = slicephase - (t_float)sliceindex;
            index = startindex + sliceindex;
            index &= loopmask;
            a = arraypointer[index].w_float;
            b = arraypointer[index+1].w_float;
            *output = (a + (frac * (b - a))) * compensation;
            playtimer--; counter += 1.;
        }
    }
    x->currentindex = index;  // in case next block starts with new slice
    x->counter = counter;
    x->playtimer = playtimer;
}
// end of sliceplay_linear function definition


static void sliceplay_cubic(t_sliceplay *x, t_float *output, t_int blocksize)
{
    t_float a, b, c, d, cminb, slicephase, frac;
    t_int index = 0, sliceindex = 0;

    t_word *arraypointer = x->arraypointer;
    t_int loopmask = x->loopmask;
    t_int startindex = x->startindex;
    t_int playtimer = x->playtimer;
    t_float counter = x->counter;
    t_float speed = x->slicespeed;
    t_float compensationfactor = x->compensationfactor;

    for(;blocksize; blocksize--, output++)
    {
        *output = 0.;

        if(playtimer)
        {
            slicephase = counter * speed;
            sliceindex = (t_int)slicephase;
            frac = slicephase - (t_float)sliceindex;
            index = startindex + sliceindex;
            index &= loopmask;

            // cubic interpolation
            a = arraypointer[index].w_float;
            b = arraypointer[index+1].w_float;
            c = arraypointer[index+2].w_float;
            d = arraypointer[index+3].w_float;
            cminb = c - b;
            *output = (b + frac * (cminb - pointsixteen
                * (one - frac) * ((d - a - three * cminb)
                * frac + (d + two * a - three * b))))
                * compensationfactor;

            playtimer--; counter += 1.;
        }
    }
    x->currentindex = index;  // in case next block starts with new slice
    x->counter = counter;
    x->playtimer = playtimer;
}
// end of sliceplay_cubic function definition


static void sliceplay_overlap_linear(t_sliceplay *x, t_float *output, t_int blocksize)
{
    t_float a, b, fadeoutphase, frac;
    t_int index, fadeoutindex;

    t_word *arraypointer = x->arraypointer;
    t_int loopmask = x->loopmask;
    t_int fadeouttimer = x->fadeouttimer;
    t_int fadeoutpoint = x->fadeoutpoint;
    t_float fadeoutcounter = x->fadeoutcounter;
    t_float speed = x->fadeoutspeed;
    t_float compensation = x->fadeoutcompensation;

    for(;blocksize; blocksize--, output++)
    {
        if(fadeouttimer)    // eventual previous slice tail
        {
            fadeoutphase = fadeoutcounter * speed;
            fadeoutindex = (t_int)fadeoutphase;
            frac = fadeoutphase - (t_float)fadeoutindex;
            index = fadeoutpoint + fadeoutindex;
            index &= loopmask;
            a = arraypointer[index].w_float;
            b = arraypointer[index+1].w_float;
            *output += (a + (frac * (b - a)))
                        * compensation
                        * (half - (half * cos_table[fadeouttimer]));    //window

            fadeoutcounter++; fadeouttimer--;
        }
    }
    x->fadeoutcounter = fadeoutcounter;
    x->fadeouttimer = fadeouttimer;
}
// end of sliceplay_overlap_linear function definition


static void sliceplay_overlap_cubic(t_sliceplay *x, t_float *output, t_int blocksize)
{
    t_float a, b, c, d, cminb, fadeoutphase, frac;
    t_int index, fadeoutindex;

    t_word *arraypointer = x->arraypointer;
    t_int loopmask = x->loopmask;
    t_int fadeouttimer = x->fadeouttimer;
    t_int fadeoutpoint = x->fadeoutpoint;
    t_float fadeoutcounter = x->fadeoutcounter;
    t_float speed = x->fadeoutspeed;
    t_float compensation = x->fadeoutcompensation;

    for(;blocksize; blocksize--, output++)
    {
        if(fadeouttimer)    // eventual previous slice tail
        {
            fadeoutphase = fadeoutcounter * speed;
            fadeoutindex = (t_int)fadeoutphase;
            frac = fadeoutphase - (t_float)fadeoutindex;
            index = fadeoutpoint + fadeoutindex;
            index &= loopmask;

            // cubic interpolation
            a = arraypointer[index].w_float;
            b = arraypointer[index+1].w_float;
            c = arraypointer[index+2].w_float;
            d = arraypointer[index+3].w_float;
            cminb = c - b;
            *output += (b + frac * (cminb - pointsixteen
                * (one - frac) * ((d - a - three * cminb)
                * frac + (d + two * a - three * b))))
                * compensation
                * (half - (half * cos_table[fadeouttimer]));    // window

            fadeoutcounter++; fadeouttimer--;
        }
    }
    x->fadeoutcounter = fadeoutcounter;
    x->fadeouttimer = fadeouttimer;
}
// end of sliceplay_overlap_cubic function definition


static t_int *sliceplay_perform(t_int *w)
{
    t_sample *output = (t_sample *)(w[1]);
    t_sliceplay *x = (t_sliceplay *)(w[2]);
    t_int blocksize = (t_int)(w[3]);

    // if there is no slice to be played, or if the buffer is not there
    if((!x->playtimer) | (!x->arraypointer))
    {
        while(blocksize--) *output++ = 0.;
        return (w+4);
    }

    // playback method and overlap method are selected via function pointers
    else
    {
        (*x->pPlaybackMethod)(x, output, blocksize);

         // if the tail of an old slice must be overlapped with new slice
        if(x->fadeouttimer) (*x->pOverlapMethod)(x, output, blocksize);
    }


    if(!x->playtimer) sliceplay_tick(x, 0); // send playstatus = 0 message

    return (w+4);
}
// end of sliceplay_perform function definition


static void sliceplay_set(t_sliceplay *x)
{
    t_garray *array;
    int arraysize, logloopsize;

    if(!(array = (t_garray *)pd_findbyclass(x->arrayname, garray_class)))
    {
        if (x->arrayname->s_name) pd_error(x, "sliceplay~: %s: no such array",
            x->arrayname->s_name);
        x->arraypointer = 0;
    }

    else if (!garray_getfloatwords(array, &arraysize, &x->arraypointer))
    {
        pd_error(x, "%s: bad template for sliceplay~", x->arrayname->s_name);
        x->arraypointer = 0;
    }

    else
    {
        logloopsize = ilog2(arraysize-3);   // arraysize must be at least loopsize + 1 sample
        x->loopsize = 1<<logloopsize;       // loopsize is rounded to a power of two
        x->loopmask = x->loopsize - 1;      // bitwise-and mask for loopsize
        garray_usedindsp(array);
    }
}
// end of sliceplay_set function definition


static void sliceplay_dsp(t_sliceplay *x, t_signal **sp)
{
    sliceplay_set(x);
    dsp_add(sliceplay_perform, 3, sp[0]->s_vec, x, sp[0]->s_n);
}


static inline void sliceplay_compensationfactor(t_sliceplay *x) // amplitude compensation
{
    t_float speed = fastabs(x->speed);
    t_float compensationfactor;
    compensationfactor = x->compensationsetting * (1. - speed) + 1.;
    if(compensationfactor < 0.7) compensationfactor = 0.7;
    x->compensationfactor = compensationfactor;
}


static void sliceplay_compensation(t_sliceplay *x, t_floatarg compensation)
{
    if(compensation > 1.) compensation = 1.;
    else if(compensation < 0.) compensation = 0.;
    x->compensationsetting = compensation;                      // user parameter for compensation
}


static void sliceplay_interrupt(t_sliceplay *x, t_floatarg interrupt)
{
    if((interrupt != -1) && (interrupt != 1)) interrupt = 0;
    x->interrupt = interrupt;
}


static void sliceplay_cuepoints(t_sliceplay *x, t_floatarg startindex, t_floatarg stopindex)
{
    if((startindex < 0.) || (stopindex < 0.)) return;           // negative cuepoints are ignored

    startindex -= 3.;   // start earlier for interpolation
    stopindex -= 3.;
    t_int samples, start, stop;
    t_int accept = 0;
    t_int interrupt = x->interrupt;                                 // x->interrupt can be -1, 0 or 1

    if(interrupt == 1) accept = 1;                                  // interrupt = 1: always interrupt
    else if(!x->playtimer) accept = 1;                              // if not playing, always accept new cuepoints
    else if((interrupt == -1) && (x->slicespeed < 0)) accept = 1;   // interrupt = -1: only interrupt reversed playback

    if(accept)                                                      // accept new cuepoints conditionally
    {
        if(x->playtimer)                                            // if interrupted, fade out previous slice
        {
            if(x->playtimer < COSTABSIZE>>1)
                x->fadeouttimer = x->playtimer;
            else x->fadeouttimer = COSTABSIZE>>1;
            x->fadeoutcounter = 0.;
            x->fadeoutpoint = x->currentindex + x->loopsize;    // hand over previous settings
            x->fadeoutspeed = x->slicespeed;
            x->fadeoutcompensation = x->compensationfactor;
        }

        if(x->speed > 0.) x->startindex = (t_int)startindex + x->loopsize;      // forward
        if(x->speed < 0.) x->startindex = (t_int)stopindex + x->loopsize - 1.;  // reverse
        x->counter = 0.;
        start = (t_int)startindex;
        stop = (t_int)stopindex;
        samples = ((stop - start + x->loopsize) & (x->loopmask)) - 1;
        x->playtimer = (t_int)(samples / x->speed);             // compute playback time in number of samples
        x->playtimer = fastabs(x->playtimer);
        x->slicespeed = x->speed;
        sliceplay_compensationfactor(x);
        sliceplay_tick(x, fastabs(x->playtimer));               // report slice length in nr of samples
    }
}
// end of sliceplay_cuepoints function definition


static void sliceplay_speed(t_sliceplay *x, t_floatarg speed)   // playback speed
{
    t_float minspeed = x->minspeed;

    if(speed >= 0)                                              // exclude very slow speeds
    {
        if(speed < minspeed) x->speed = minspeed;
        else x->speed = (t_float)speed;
    }
    else
    {
        if(speed > -minspeed) x->speed = -minspeed;
        else x->speed = (t_float)speed;
    }
}


static void sliceplay_minspeed(t_sliceplay *x, t_floatarg minspeed) // minimum playback speed
{
    x->minspeed = fastabs(minspeed);
}


static void sliceplay_interp(t_sliceplay *x, t_floatarg interp)
{
    if(interp)
    {
        x->pPlaybackMethod = &sliceplay_cubic;
        x->pOverlapMethod = &sliceplay_overlap_cubic;
    }

    else
    {
        x->pPlaybackMethod = &sliceplay_linear;
        x->pOverlapMethod = &sliceplay_overlap_linear;
    }
}


static void *sliceplay_new(t_symbol *symbol)
{
    t_sliceplay *x = (t_sliceplay *)pd_new(sliceplay_class);
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym ("list"), gensym("cuepoints"));
    outlet_new(&x->x_obj, gensym("signal"));
    x->playstatusoutlet = outlet_new(&x->x_obj, &s_float);
    x->arrayname = symbol;
    x->playtimer = 0;
    x->compensationfactor = 1.;
    x->speed = SPEEDDEFAULT;
    x->compensationsetting = COMPENSATIONDEFAULT;
    x->minspeed = MINSPEEDDEFAULT;
    x->interrupt = INTERRUPTDEFAULT;
    sliceplay_interp(x, INTERPDEFAULT);

    return (x);
}
// end of sliceplay_new function definition


void sliceplay_tilde_setup(void)
{
    sliceplay_class = class_new(gensym("sliceplay~"), (t_newmethod)sliceplay_new,
        (t_method)sliceplay_free, sizeof(t_sliceplay), 0, A_DEFSYM, 0);
    class_addfloat(sliceplay_class, (t_method)sliceplay_speed);
    class_addmethod(sliceplay_class, (t_method)sliceplay_dsp, gensym("dsp"), 0);
    class_addmethod(sliceplay_class, (t_method)sliceplay_cuepoints,
        gensym("cuepoints"), A_FLOAT, A_FLOAT, 0);
    class_addmethod(sliceplay_class, (t_method)sliceplay_compensation,
        gensym("compensation"), A_FLOAT, 0);
    class_addmethod(sliceplay_class, (t_method)sliceplay_interrupt,
        gensym("interrupt"), A_FLOAT, 0);
    class_addmethod(sliceplay_class, (t_method)sliceplay_minspeed,
        gensym("minspeed"), A_FLOAT, 0);
    class_addmethod(sliceplay_class, (t_method)sliceplay_interp,
        gensym("interp"), A_FLOAT, 0);
    class_sethelpsymbol(sliceplay_class, gensym("slicerec~-help.pd"));
    post("[sliceplay~] version %s written by Katja Vetter", VERSION);
}

