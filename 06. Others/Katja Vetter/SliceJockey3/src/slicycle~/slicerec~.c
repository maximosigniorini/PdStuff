/*
 * slicerec~.c
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
 * [slicerec~] class for Pd (Pure Data, the work of Miller Puckette and others).
 *
 * version 1.0:
 * - fixed fade out bug
 * - fade out now applied to all recorded slices (not only the interrupted ones)
 * - fade out window ends with silence samples, facilitating interpolated slice reading
 * - extra samples copied at buffer end, facilitating cubic interpolated slice reading
 *
 * version 0.9.11:
 * - function slicerec_fadeout() renewed and called from slicerec_analysis()
 * - message selector 'start' added, for manual slice-recording start
 *
 * version 0.9.1:
 * - used garray_getfloatwords() instead of garray_getfloatarray(), for 64 bit
 *   compatibility
 *
 * version 0.9.1: initial version
 *
 * ****************************************************************************/


#include "m_pd.h"
#include <math.h>

#define VERSION "1.0"

#define RECSTATUSDEFAULT 0          // record on / off status
#define ATTACKSTEPDEFAULT 6.
#define ATTACKSTEPMIN 1.
#define ATTACKTHRESHDEFAULT 70.
#define ATTACKTHRESHMIN 0.
#define SILENCETHRESHDEFAULT 55.
#define SILENCETHRESHMIN 0.
#define TIMECONSTANTDEFAULT 150.    // peak amplitude decay time
#define TIMECONSTANTMIN 10.
#define REFRACTPERIOD 14.           // refractory time after attack detection, in Hz
#define FADEOUTSIZE 64

static t_float fadeout_table[FADEOUTSIZE];


// global pointer to class struct
static t_class *slicerec_class;


// slicrec~ class struct
typedef struct
{
    t_object x_obj;
    t_float f;                      // for MAINSIGNALIN

    // struct members for recording
    t_int loopsize;
    t_int timeindex;
    t_int recstatus;                // flag for rec status
    t_int start;                    // flag for manual slice rec start
    t_int blocksize;                // signal block size
    t_int twoblockindex;            // index for small signal buffer
    t_float *twoblockpointer;       // pointer to small signal buffer, size of two signal blocks
    t_word *arraypointer;           // pointer to the global / external array
    t_symbol *arrayname;            // pointer to struct containing global / external array name

    // struct members for analysis
    t_float attackstep;             // deciBel difference value for attack test, user parameter
    t_float attackthreshold;        // deciBel absolute threshold for attack test, user parameter
    t_float silencethreshold;       // deciBel threshold for silence test, user parameter
    t_float timeconstant;           // time constant of peak envelope, user parameter
    t_float previousinput;          // previous input sample
    t_float previousamp;            // amplitude of previous vector
    t_float peakenvelope;           // envelope of absolute peaks in signal
    t_float radius;                 // radius for decay of peak envelope
    t_float samplerate;             // samplerate needed for time constant computation
    t_float vectorsizereciproce;    // 1. / vectorsize
    t_int cuepoint;                 // index point where an attack starts or a slice ends
    t_int zerocrosspoint;           // index point where a zero crossing is found
    t_int refractvectors;           // refractory time after attack detection, in nr of signal vectors
    t_int refractcounter;           // counter for refractory vectors after attack detection
    t_outlet *attackoutlet;         // outlet for attackpoint message
    t_outlet *silenceoutlet;        // outlet for silence detect
    t_outlet *recstatusoutlet;      // outlet for recstatus message
    t_clock *cuepointclock;         // timer for cuepoint message
} t_slicerec;


static void init_fadeout_table(void)
{
    int n;
    int curvelength = FADEOUTSIZE - 8;
    const t_float angle = 3.141592653589793 / (t_float)(curvelength);

    // smooth fade out curve (like second part of Hann window)
    for(n=0; n<curvelength; n++)
    {
        fadeout_table[n] = 0.5 + (0.5 * cos(n * angle));
    }

    // last few samples are zero to accommodate interpolated reading of slices
    for(n=curvelength; n<FADEOUTSIZE; n++)
    {
        fadeout_table[n] = 0.;
    }
}


// method being called at polling time
static void slicerec_tick(t_slicerec *x)
{
    switch(x->recstatus)
    {
        case 0: // silence
        outlet_float(x->silenceoutlet, x->cuepoint); break;

        case 1: // attack
        outlet_float(x->attackoutlet, x->cuepoint); break;
    }

    outlet_float(x->recstatusoutlet, x->recstatus);
}


static void flushbuffer(t_float *buffer, t_int buffersize)
{
    t_int index;
    for(index = 0; index < buffersize; index++) buffer[index] = 0.;
}


static void slicerec_free(t_slicerec *x)
{
    if(x->cuepointclock) clock_free(x->cuepointclock);
    if(x->twoblockpointer) freebytes(x->twoblockpointer, (2 * x->blocksize * sizeof(t_float)));
}


static void slicerec_step(t_slicerec *x, t_floatarg attackstep)
{
    if(attackstep < ATTACKSTEPMIN) attackstep = ATTACKSTEPMIN;
    x->attackstep = (t_float)attackstep;
}


static void slicerec_attackthreshold(t_slicerec *x, t_floatarg attackthresh)
{
    if(attackthresh < ATTACKTHRESHMIN) attackthresh = ATTACKTHRESHMIN;
    x->attackthreshold = (t_float)attackthresh;
}


static void slicerec_silencethreshold(t_slicerec *x, t_floatarg silencethreshold)
{
    if(silencethreshold < SILENCETHRESHMIN) silencethreshold = SILENCETHRESHMIN;
    x->silencethreshold = (t_float)silencethreshold;
}


static void slicerec_timeconstant(t_slicerec *x, t_floatarg timeconstant)
{
    if(x->timeconstant < 0.) x->timeconstant = 0.;
    x->timeconstant = timeconstant;
    x->radius = exp((-1000 / (x->samplerate * x->vectorsizereciproce)) / (t_float)timeconstant);
}


static void *slicerec_new(t_symbol *sym)
{
    t_slicerec *x = (t_slicerec *)pd_new(slicerec_class);
    x->attackoutlet = outlet_new(&x->x_obj, &s_float);
    x->silenceoutlet = outlet_new(&x->x_obj, &s_float);
    x->recstatusoutlet = outlet_new(&x->x_obj, &s_float);
    x->blocksize = 64;                                              // actual size is set in dsp method
    x->twoblockpointer = (t_float*)getbytes(2 * x->blocksize * sizeof(t_float));
    if(x->twoblockpointer) flushbuffer(x->twoblockpointer, (2 * x->blocksize));
    x->arrayname = sym;
    x->timeindex = 0;
    x->twoblockindex = 0;
    x->f = 0.;
    x->previousinput = 0.;
    x->samplerate = 44100.;
    x->peakenvelope = 0.;
    x->refractcounter = 0;
    x->start = 0;
    x->recstatus = RECSTATUSDEFAULT;
    x->attackstep = ATTACKSTEPDEFAULT;
    x->attackthreshold = ATTACKTHRESHDEFAULT;
    x->silencethreshold = SILENCETHRESHDEFAULT;
    x->timeconstant = TIMECONSTANTDEFAULT;
    slicerec_timeconstant(x, x->timeconstant);
    x->cuepointclock = clock_new(x, (t_method)slicerec_tick);

    return (x);
}
// end of slicerec_new function definition


static void slicerec_redraw(t_slicerec *x)
{
    t_garray *array = (t_garray *)pd_findbyclass(x->arrayname, garray_class);
    if(!array) bug("slicerec~ redraw");
    else garray_redraw(array);
}


// Two blocks of audio are continuously buffered even when recording into external array is stopped.
// When recording is resumed, these two blocks are inserted first, with a fade-in.
static void slicerec_inserttwoblocks(t_slicerec *x)
{
    t_int n;
    const t_float half = 0.5;
    const t_float pi = 3.141592653589793;
    t_int twoblockindex = x->twoblockindex;
    t_int timeindex = x->timeindex;
    t_float *twoblockpointer = x->twoblockpointer;
    t_word *arraypointer = x->arraypointer;
    t_float angle = pi / (t_float)x->blocksize;
    t_float window;

    for(n=x->blocksize; n; n--, timeindex++, twoblockindex++)
    {
        window = (half * cos(angle * n)) + half;                    // smooth fade-in
        arraypointer[timeindex].w_float = twoblockpointer[twoblockindex] * window;
    }

    twoblockindex &= (2 * x->blocksize) - 1;                        // mask twoblock index
    timeindex &= x->loopsize - 1;                                   // mask time index

    for(n=x->blocksize; n; n--, timeindex++, twoblockindex++)
    {
        arraypointer[timeindex].w_float = twoblockpointer[twoblockindex];
    }

    x->twoblockindex = twoblockindex & ((2 * x->blocksize) - 1);    // mask and restore indexes into struct
    x->timeindex = timeindex & (x->loopsize - 1);
}


// called when a new slice starts before the previous slice has decayed to zero
static void slicerec_fadeout(t_slicerec *x)
{
    t_int n, timeindex;
    t_int mask = x->loopsize - 1;
    t_word *arraypointer = x->arraypointer;

    timeindex = (x->cuepoint + x->loopsize - FADEOUTSIZE) & mask;   // find start of fade out region

    for(n=0; n<FADEOUTSIZE; n++, timeindex++)
    {
        arraypointer[timeindex].w_float *= fadeout_table[n];        // smooth out discontinuities
        timeindex &= mask;
    }

}


static void slicerec_analysis(t_slicerec *x, t_float power)
{
    t_float decibel, difference;
    t_float peakenvelope = x->peakenvelope;

    power *= x->vectorsizereciproce;                        // compute mean of sum of squares (power)
    decibel = powtodb(power);                               // express amplitude in logarithms (deciBel)
    difference = decibel - peakenvelope;                    // compute sound level increase/decrease

    if(((decibel > x->attackthreshold)
        &&(difference > x->attackstep)
        && (!x->refractcounter))
        || x->start)                                        // if bingo, new slice
    {
        if(!x->recstatus)                                   // if starting from silence...
        {
            slicerec_inserttwoblocks(x);                    // ...insert buffered samples
            x->recstatus = 1;
        }
        else
        {
            x->cuepoint = x->zerocrosspoint;                // zero cross point from previous vector
            slicerec_fadeout(x);                            // fade out of previous slice
        }
        x->start = 0;
        x->refractcounter = x->refractvectors;              // reset refractory period
        clock_delay(x->cuepointclock, 0);                   // set clock for attack detect message
    }

    peakenvelope *= x->radius;                              // let the peak envelope decay
    if(PD_BIGORSMALL(peakenvelope)) peakenvelope = 0.;      // clear small values
    if(decibel > peakenvelope) peakenvelope = decibel;      // store new peak

    if((x->recstatus) && (!x->refractcounter))
    {
        if(peakenvelope < x->silencethreshold)              // check if sound level gets low
        {
            x->recstatus = 0;
            x->cuepoint = x->timeindex;                     // store time index of silence detect
            slicerec_fadeout(x);
            clock_delay(x->cuepointclock, 0);               // set clock for silence detect message
        }
    }

    x->peakenvelope = peakenvelope;
}
// end of slicerec_analysis function definition


static t_int *slicerec_perform(t_int *w)
{
    t_sample *input = (t_sample *)(w[1]);                   // audio signal input
    t_slicerec *x = (t_slicerec *)(w[2]);
    t_int blocksize = (t_int)(w[3]);

    if(!x->arraypointer) return(w+4);

    t_word *arraypointer = x->arraypointer;
    t_float *twoblockpointer = x->twoblockpointer;
    t_float power = 0., inputsample;
    t_float zerocrosspoint = x->zerocrosspoint;
    t_float previousinput = x->previousinput;               // copy state variable to local for speed
    t_int timeindex = x->timeindex;
    t_int recstatus = x->recstatus;
    t_int twoblockindex = x->twoblockindex;
    t_int zerocrosscheck = 1;                               // flag, cleared when first zerocross found

    if(x->refractcounter) x->refractcounter--;              // countdown of refractory time

    if(!timeindex && recstatus)
    {
        arraypointer[x->loopsize].w_float = input[0];       // copy samples for interpolated reading
        arraypointer[x->loopsize+1].w_float = input[1];
        arraypointer[x->loopsize+2].w_float = input[2];
    }

    while (blocksize--)
    {
        if(recstatus)                                       // if recording is on
        {
            if(zerocrosscheck)
            {
                if((*input * previousinput) < 0)            // check for zero crossing
                {
                    zerocrosspoint = timeindex;             // store it's time index
                    zerocrosscheck = 0;                     // only first zero cross point in vector is wanted
                }
            }
            inputsample = *input;
            if(PD_BIGORSMALL(inputsample)) inputsample = 0.;// flush very small or very big numbers
            arraypointer[timeindex].w_float = inputsample;  // store input in external buffer
            timeindex++;
        }
        else                                                // if recording is off
        {
            twoblockpointer[twoblockindex] = *input;        // store input in small temporary buffer
            twoblockindex++;
        }

        previousinput = *input;
        power += *input * *input;                           // compute sum of squares for analysis
        input++;
    }
    // end of while(blocksize)

    x->timeindex = timeindex & (x->loopsize - 1);               // mask time index and restore in struct
    x->twoblockindex = twoblockindex & ((2 * x->blocksize) - 1);// mask twoblock index and restore in struct
    x->previousinput = previousinput;                           // store previous input in struct

    slicerec_analysis(x, power);                                // call analysis function

    x->zerocrosspoint = zerocrosspoint;                         // this restore must happen after analysis

    return (w+4);
}
// end of attackpoint_perform function definition


static void slicerec_set(t_slicerec *x)
{
    t_garray *arr;
    int arraysize;
    t_int logloopsize;

    if(!(arr = (t_garray *)pd_findbyclass(x->arrayname, garray_class)))
    {
        if (*x->arrayname->s_name) pd_error(x, "slicerec~: %s: no such array", x->arrayname->s_name);
        x->arraypointer = 0;
    }

    else if (!garray_getfloatwords(arr, &arraysize, &x->arraypointer))
    {
        pd_error(x, "%s: bad template for slicerec~", x->arrayname->s_name);
        x->arraypointer = 0;
    }

    else
    {
        logloopsize = ilog2(arraysize-3);           // arraysize must be at least loopsize + 3 samples
        x->loopsize = 1<<logloopsize;               // loopsize is rounded to a power of two
        garray_usedindsp(arr);
    }
}


static void slicerec_dsp(t_slicerec *x, t_signal **sp)
{
    x->samplerate = sp[0]->s_sr;
    x->refractvectors = sp[0]->s_sr / sp[0]->s_n / REFRACTPERIOD;
    if(x->refractvectors < 1) x->refractvectors = 1;
    x->vectorsizereciproce = 1. / (t_float) sp[0]->s_n;
    slicerec_timeconstant(x, x->timeconstant);
    slicerec_set(x);

    if(x->blocksize != sp[0]->s_n)                                      // in case of block resize
    {
        x->twoblockpointer = (t_float*)resizebytes(x->twoblockpointer,  // resize two-block buffer
            (2 * x->blocksize * sizeof(t_float)), (2 * sp[0]->s_n * sizeof(t_float)));
        x->blocksize = sp[0]->s_n;                                      // store new blocksize
        x->twoblockindex = 0;                                           // reset index

    }
    flushbuffer(x->twoblockpointer, (2 * x->blocksize));

    dsp_add(slicerec_perform, 3, sp[0]->s_vec, x, sp[0]->s_n);
}


static void slicerec_draw(t_slicerec *x)                                // stop recording and draw array
{
    x->recstatus = 0;
    slicerec_redraw(x);
}


static void slicerec_reset(t_slicerec *x)
{
    x->timeindex = 0;
    x->zerocrosspoint = 0;
    x->cuepoint = 0;
    x->recstatus = 0;
}


static void slicerec_start(t_slicerec *x)
{
    x->start = 1;
}


void slicerec_tilde_setup(void)
{
    slicerec_class = class_new(gensym("slicerec~"), (t_newmethod)slicerec_new,
        (t_method)slicerec_free, sizeof(t_slicerec), 0, A_DEFSYM, 0);
    CLASS_MAINSIGNALIN(slicerec_class, t_slicerec, f);
    class_addmethod(slicerec_class, (t_method)slicerec_dsp, gensym("dsp"), 0);
    class_addmethod(slicerec_class, (t_method)slicerec_draw, gensym("draw"), 0);
    class_addmethod(slicerec_class, (t_method)slicerec_reset, gensym("reset"), 0);
    class_addmethod(slicerec_class, (t_method)slicerec_step, gensym("attackstep"), A_FLOAT, 0);
    class_addmethod(slicerec_class, (t_method)slicerec_attackthreshold, gensym("attackthresh"), A_FLOAT, 0);
    class_addmethod(slicerec_class, (t_method)slicerec_silencethreshold, gensym("silencethresh"), A_FLOAT, 0);
    class_addmethod(slicerec_class, (t_method)slicerec_timeconstant, gensym("timeconstant"), A_FLOAT, 0);
    class_addmethod(slicerec_class, (t_method)slicerec_start, gensym("start"), 0);
    init_fadeout_table();
    post("[slicerec~] version %s written by Katja Vetter", VERSION);
}


