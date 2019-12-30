/*
 * absolute.h
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
 */


#ifndef absolute_h
#define absolute_h

// simple bithack alternative for abs()


#if PD_FLOAT_PRECISION == 64

static inline t_float fastabs(t_float f)
{
    union
    {
        t_float f;
        unsigned long long ui;
    }alias;

    alias.f = f;
    alias.ui[1] &= 0x7fffffff;
    return alias.f;
}

#else    // if not 64 bit precision, assume 32 bit

static inline t_float fastabs(t_float f)
{
    union
    {
        t_float f;
        unsigned int ui;
    }alias;

    alias.f = f;
    alias.ui &= 0x7fffffff;
    return alias.f;
}

#endif  // end if PD_FLOAT_PRECISION == 64

#endif  // end ifndef absolute_h
