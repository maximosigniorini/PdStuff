#!/bin/sh

# arguments might be:
# "-p <period>" for defining the latency of the system
## <period> defines the blocksize (e.g. of the hammerfall DSP - card (?))
## jack-buffer=<period>*<nperiod=2>*4 (in bytes)
## jack-latency=<period>*<nperiod=2>/<rate=44100> (in secs)

jackd -R -d alsa -d hw:0 -r 44100 $@
