Particlechamber by Derek Holzer [Umatic.nl]

Particlechamber is a 32-voice asynchronous granular synthesizer for real-time 
transformation of a soundfile. It is loosely based on the famous Travelizer 
instrument from Reaktor 3, however I think it's much better because it is FREE!

This abstraction can be used to time-stretch or -compress a soundfile, although 
there are other tools [such as Frank Barknecht's Synchgrain object] which do 
this "nicer", but it's main strength is in generating clouds of sonic particles,time-scrambling a file, or creating abstract textures. If one does a bit of 
reverse engineering, it can also be used as a tool for learning about the 
techniques of granular synthesis. I have left a subpatch inside the granreader 
subpatch where others can add their own grain-level events, such as randomized 
or constant-Q filters or windowed envelopes, to see what is possible with this 
technique. Of course, I can only highly recommend Curtis Road's amazing book 
"Microsound" for those interested in learning more.

Particlechamber requires a few externals to run. It uses Freeverb~ for its 
reverb section [although you could easily replace it with another reverb], and 
uses Grid as a major GUI element [although you could hack your way around it if 
you can't install Grid by sending numbers directly to the table_locator subpatch. Look inside for details...]

It would be best to take Grid from the PD External Repository:
http://pure-data.sourceforge.net

However, Yves Degoyon's Grid external can also be found here: 
http://ydegoyon.free.fr/software.html

The freeverb~ external can be downloaded here: 
http://www.akustische-kunst.org/puredata/main.html


Operation of Particlechamber:

Open the Load subpatch and click the bangs to load samples. It is better to do 
this before you start playing, because loading soundfiles can cause audible 
glitches in PD's performance. Sorry...

The red buttons mute and unmute the file granulator and the reverb. The large 
vertical sliders are gain for each section. The reverb is post-fader from the 
file granulator, and can be bypassed either by muting it or with the wet/dry 
slider.

The envelope is a linear ramp, so a length of 0 means a pure triangular 
"window" for each grain. [(envelope x 2)+length=average grain length in ms]. 
Stereo_spread randomly pans each grain to a wider or lesser field. The range 
feature randomizes each parameter as a percentage plus or minus the given 
number.

Asynch randomizes which grains are passed through, from almost none to 
all. Vox activates or deactivates each of the 32 voices. Grain_spread makes 
small adjustments in the read position, which can be used to either add a 
reverb- or chorus-like effect, or to completely time-smear a file. Jitter makes 
larger adjustments in the read position, resulting in various degrees of 
time-scrambling.

The XY controller at the bottom determines the read position in the sample. This controller has an interpolation scale, adjustable by the gear-shift on the 
right. This means that Particlechamber will scan more slowly or quickly through 
the file depending on the cursor's Y position multiplied by the interpolation 
factor.

Particlechamber is free software and comes without any warrenty that it 
will do ANYTHING like what I say it will. Enjoy it all the same. 


----------------------------------------------------derek@umatic.nl 




