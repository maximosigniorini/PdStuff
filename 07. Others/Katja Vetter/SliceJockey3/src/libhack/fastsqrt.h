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
 * Fast square root method as described by Chris Lomont and Charles McEniry
 * Do not feed negative values.
 */


#ifndef fastsqrt_h
#define fastsqrt_h
#include "m_pd.h"


#if PD_FLOAT_PRECISION == 64

static inline t_float cheapsqrt(t_float value)
{
    union
    {
        t_float f;
        long long i;
    }alias;

    const t_float half = 0.5;
    const t_float oneandhalf = 1.5;
    alias.f = value;
    alias.i = 0x5fe6eb50c7b537aa - (alias.i>>1);
    value *= alias.f * (oneandhalf - half * value * alias.f * alias.f);
    return value;
}


#else    // if not 64 bit precision, assume 32 bit (default)

static inline t_float cheapsqrt(t_float value)
{
    union
    {
        t_float f;
        int i;
    }alias;

    const t_float half = 0.5;
    const t_float oneandhalf = 1.5;
    alias.f = value;
    alias.i = 0x5f3759df - (alias.i>>1);
    value *= alias.f * (oneandhalf - half * value * alias.f * alias.f);
    return value;
}


#endif  // endif PD_FLOAT_PRECISION

#endif  // end ifndef fastsqrt_h
