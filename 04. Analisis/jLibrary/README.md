jLibrary
--------

FFT, convolution and general Pure Data library. Main objects are...

### [jTabConv]

Convolve two tables by multiplication in the frequency domain using FFT.

![jTabConv image](http://www.johnflynn.info/images/jTabConv-help.png)

- $1 Table 1 (referred to here as 'x')
- $2 Table 2 (referred to here as 'h')
- $3 Output table (referred to as 'y' or 'XH')
- in1 bang to convolve tables
- out2 bang when done

The FFT method works very quickly for long tables. In comparison, on this machine, for 1 second tables at 44.1k iem_tab tab_conv (presumably time domain?) takes >10 seconds whereas this method takes a few milliseconds. The speed of computation is governed by switch~'s oversampling rate (on this machine 2048 seems to be optimal).

There is some error when comparing to iem_tab tab_conv which presumably is down to number precision error going back and forth through fft~ and ifft~ (specifically gain from ifft~ at huge blocksize which needs to be normalised). This may be unacceptable for some applications e.g. filtering but acceptable for reverb or special effects.

Requires:

- jLibrary [jArraySize]
- jLibrary [jLog]
- iem_tab [tab_complex_mul]

### [jTabLookup]

Fill a table with values processed by cross-connected object(s).

![jTabLookup image](http://www.johnflynn.info/images/jTabLookup-help.png)

Lookup table by index via [tabread4] 4-point interpolation.

Useful for computationally expensive objects like [pow], [exp] etc., where a close approximation will suffice. Or for a complicated chain of objects, or an intricate [expr]. (Because lookup table is calculated over a specified range, this is only useful in situations where a finite range is acceptable.)

- $1 lower lookup bound (float)
- $2 upper lookup bound (float!=$1)
- $3 lookup table size (float>0)
- in1 lookup index ($1:$2) or bang to (re)fill table
- in2 from output of processing object(s)
- out1 tabread4 lookup values
- out2 to input of processing object(s)

Requires:

- rj [m_scale]
- iemguts [canvaserror]
