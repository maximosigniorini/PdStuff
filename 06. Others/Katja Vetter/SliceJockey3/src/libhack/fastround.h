/*
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
 * Inline functions for finding integral part and fraction of a float without
 * cast, and storing these values in a struct.
 */


#ifndef fastround_h
#define fastround_h

#include "m_pd.h"   // for t_float

typedef struct
{
    t_float round;
    t_float frac;
}t_fround;


typedef struct
{
    t_float round;
    t_float frac;
}t_froundd;


#if PD_FLOAT_PRECISION == 64

static inline void roundnearest(t_fround *fr, t_float value)
{
    static const t_float bit52plus = 6369051672525773.; // 2^52.5
    t_float large;
    large = value + bit52plus;
    fr->round = large - bit52plus;
    fr->frac = value - fr->round;
}


#else    // if not 64 bit precision, assume 32 bit (default)

static inline void roundnearest(t_fround *fr, t_float value)
{
    static const t_float bit23plus = 11863283.; // 2^23.5
    t_float large;
    large = value + bit23plus;
    fr->round = large - bit23plus;
    fr->frac = value - fr->round;
}


#endif  // endif PD_FLOAT_PRECISION


static inline void roundnearestd(t_froundd *fr, double value)
{
    static const t_float bit52plus = 6369051672525773.; // 2^52.5
    double large;
    large = value + bit52plus;
    fr->round = large - bit52plus;
    fr->frac = value - fr->round;
}

#endif  // end ifndef fastround_h
