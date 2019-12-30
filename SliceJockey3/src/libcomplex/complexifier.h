/*
 * complexifier.h
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
 * Make an analytic signal with coefficients of Olli Niemitalo for two cascades
 * of maximum-phase allpass filters.
 */

#ifndef complexifier_h
#define complexifier_h

#include "m_pd.h"
#define Z 2                     // number of samples delay
#define ZMASK (Z-1)
#define NSECTIONS 4             // number of sections in filter cascade

// Olli Niemitalo's coefficients
static const t_float coeffL[NSECTIONS] = {0.161758, 0.733029, 0.94535, 0.990598};
static const t_float coeffR[NSECTIONS] = {0.479401, 0.876218, 0.976599, 0.9975};


typedef struct
{
    t_float re;
    t_float im;
}t_complexout;


typedef struct
{
    t_float inL;
    t_float outL;
    t_float inR;
    t_float outR;
}t_filtersection;

typedef t_filtersection t_cascade[NSECTIONS];

typedef struct
{
    t_float previousinput;
    t_cascade cascades[Z];
}t_cfilters;


// make one real sample complex
// inlined and unrolled for efficiency
static inline void complexify_sample(t_cfilters *cfilters, t_float inL, t_complexout *output, int z)
{
    t_cascade *cascades = cfilters->cascades;
    t_float inR = cfilters->previousinput;
    cfilters->previousinput = inL;
    t_float outL, outR;

    outL = (coeffL[0] * (inL + cascades[z][0].outL)) - cascades[z][0].inL;
    cascades[z][0].inL = inL;
    cascades[z][0].outL = inL = outL;

    outR = (coeffR[0] * (inR + cascades[z][0].outR)) - cascades[z][0].inR;
    cascades[z][0].inR = inR;
    cascades[z][0].outR = inR = outR;

    outL = (coeffL[1] * (inL + cascades[z][1].outL)) - cascades[z][1].inL;
    cascades[z][1].inL = inL;
    cascades[z][1].outL = inL = outL;

    outR = (coeffR[1] * (inR + cascades[z][1].outR)) - cascades[z][1].inR;
    cascades[z][1].inR = inR;
    cascades[z][1].outR = inR = outR;

    outL = (coeffL[2] * (inL + cascades[z][2].outL)) - cascades[z][2].inL;
    cascades[z][2].inL = inL;
    cascades[z][2].outL = inL = outL;

    outR = (coeffR[2] * (inR + cascades[z][2].outR)) - cascades[z][2].inR;
    cascades[z][2].inR = inR;
    cascades[z][2].outR = inR = outR;

    outL = (coeffL[3] * (inL + cascades[z][3].outL)) - cascades[z][3].inL;
    cascades[z][3].inL = inL;
    cascades[z][3].outL = outL;

    outR = (coeffR[3] * (inR + cascades[z][3].outR)) - cascades[z][3].inR;
    cascades[z][3].inR = inR;
    cascades[z][3].outR = outR;

    output->re = outL;
    output->im = outR;
}


// from string.h
void *memset(void *s, int c, size_t n);

void init_cfilters(t_cfilters *cfilters)
{
    memset(cfilters, 0, sizeof(t_cfilters));
}


#endif  // end ifndef complexifier_h
