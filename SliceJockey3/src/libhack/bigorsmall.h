/*
 * bigorsmall.h
 *
 * Copyright 2011 - 2019 Katja Vetter (katjavetter@gmail.com, www.katjaas.nl)
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
 * Type aliasing via unions, allowed with compiler option -fstrict-aliasing.
 * Only needed for Intel and arm processors. Attention: when building OSX fat
 * binaries, __i386__ or __x86_64__ may not be defined. Compile with -DOSXFAT or
 * alternatively build for all architectures separately and lipo them together.
 *
 */


#ifndef BIGORSMALL_H
#define BIGORSMALL_H

#include "absolute.h"


#if defined(__i386__) || defined(__x86_64__) || defined(__arm__) || defined(OSXFAT)


/////////////////// precision //////////////////////////////////////////////////

#if PD_FLOAT_PRECISION == 64

#define SMALLFLOAT 1.e-156  // a float for which smallfloat() returns true

typedef union
{
    t_float f;
    unsigned int ui[2];
} t_alias64;


static inline int badfloat(t_float f)    // test for NAN, inf and denormal
{
    t_alias64 alias;
    alias.f = f;
    alias.ui[1] &= 0x7ff00000;
    return ((alias.ui[1] == 0) | (alias.ui[1] == 0x7ff00000));
}

static inline int bigorsmall(t_float f)  // > abs(2^513) or < abs(2^-513)
{
    t_alias64 alias;
    alias.f = f;
    return ((alias.ui[1] & 0x20000000) == ((alias.ui[1] >> 1) & 0x20000000));
}

static inline int bigfloat(t_float f)    // test for NAN, inf and > abs(2^513)
{
    t_alias64 alias;
    alias.f = f;
    return ((alias.ui[1] & 0x60000000) == 0x60000000);
}

static inline int smallfloat(t_float f)  // test for < abs(2^-513)
{
    t_alias64 alias;
    alias.f = f;
    return ((alias.ui[1] & 0x60000000) == 0);
}


#else    // if not 64 bit precision, assume 32 bit (default)

#define SMALLFLOAT 1E-23f    // a float for which smallfloat() returns true

typedef union
{
    t_float f;
    unsigned int ui;
} t_alias32;

static inline int badfloat(t_float f)    // test for NAN, inf and denormal
{
    t_alias32 alias;
    alias.f = f;
    alias.ui &= 0x7f800000;
    return ((alias.ui == 0) | (alias.ui == 0x7f800000));
}

static inline int bigorsmall(t_float f)    // > abs(2^65) or < abs(2^-65)
{
    t_alias32 alias;
    alias.f = f;
    return ((alias.ui & 0x20000000) == ((alias.ui >> 1) & 0x20000000));
}

static inline int bigfloat(t_float f)  // test for NAN, inf and > abs(2^65)
{
    t_alias32 alias;
    alias.f = f;
    return ((alias.ui & 0x60000000) == 0x60000000);
}

static inline int smallfloat(t_float f)    // test for < abs(2^-65)
{
    t_alias32 alias;
    alias.f = f;
    return ((alias.ui & 0x60000000) == 0);
}

#endif    // end if PD_FLOAT_PRECISION == 64

// flush values below resolution of 24 bit audio interface
static inline t_float flushsubliminal(t_float f)
{
    const t_float subliminal = 6E-08;

    if(fastabs(f) < subliminal) f = 0.;
    return f;
}

#else     // if not i386, x86_64, arm or OSXFAT
#define bigorsmall(f) 0
#define bigfloat(f) 0
#define smallfloat(f) 0
#define SMALLFLOAT 0

#endif // end if defined(__i386__) || defined(__x86_64__) || defined(__arm__) || defined(OSXFAT)
#endif // end ifndef BIGORSMALL_H
