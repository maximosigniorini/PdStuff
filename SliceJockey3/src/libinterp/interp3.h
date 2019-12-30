#ifndef interp3_h
#define interp3_h

// parabolic interpolation

static inline t_float interpolate3max(const t_float buf[], const int peakindex)
{
    t_float a = buf[peakindex-1];
    t_float b = buf[peakindex];
    t_float c = buf[peakindex+1];
    t_float realpeak;
    
    realpeak = b + (t_float)0.125 * (c - a) * (c - a) / ((t_float)2. * b - a - c);
    
    return(realpeak);
}



static inline t_float interpolate3phase(const t_float buf[], const int peakindex)
{
    t_float a = buf[peakindex-1];
    t_float b = buf[peakindex];
    t_float c = buf[peakindex+1];
    t_float fraction;
    
    fraction = ((t_float)0.5 * (c - a)) / ((t_float)2. * b - a - c);
    
    return(fraction);
}


#endif // end ifndef interp3_h
