ehu 0.8.6 -  10/2016 by www.ixi audio.net

https://github.com/enrike/ehu-abstractions


--- Description ---
EHU is a set of abstractions for PureData real-time graphical programming environment. 

EHU covers playing video files, controlling video cameras, displaying pictures, playing samples, audio effects, arduino, DMX controls, plus includes some general utilities.

EHU aims to allow for rapid prototyping of interactive systems. 

Most abstractions in EHU encapsulate the GUI controls minimising the job of creating widgets and connections.


-- Contact --
info@ixi-audio.net any type of feedback and/or contributions are welcome


-- HOW TO INSTALL THIS LIBRARY? --
Like any other PD library http://puredata.info/docs/faq/how-do-i-install-externals-and-help-files
You can also just keep the ehu folder next to your patches
Note that EHU relies on some PD externals, all of them are included in PD-Extended (no longer maintained, although it will probably work well). If you want to use EHU within standard vanilla PD you need to install those extras manually or using Deken. You can also use PD-l2ork 

dependencies:
The main dependencies are GEM (displaying graphics, cameras and video), GGEE (importing files for images, sound and video playing), HCS (some of the utilities) and cyclone (used in the video playing). This is the complete list

GEM
ggee /getdir
ggee/envgen (envelope)
hcs /folderlist
cyclone/counter
comport (Arduino and DMX abstractions)
freeverb~ (rev~ abstraction)
creb/dist~ (distortion~ abstraction)
sigpack/foldover~ (foldover~ abstraction)
zexy/limiter~ (limiter~ abstraction)


--- License --- GPL
This library is free software; you can redistribute it and/or modify it under the terms of the Lesser GNU, General Public License as published by the Free Software Foundation.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this library;
 if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 MA 02111-1307 USA

The pduino abstractions (port, analog_input, analog_output, digital_input digital_output_pwm,  set_input, digital_IO_mode) are based on code taken from arduino-help.pd example by Gerda Strobl and Georg Holtzmann licensed with GNU GPL
Some sound abstractions are based and use code by GuitarExtended, Pierre Massat 2012


--- List of abstractions included in EHU --- (check help files and examples included for further details)

GRAPHICS (GEM based, check ehu_gem_abstractions.pd file)

ehu/gem/win : opens/closes the GEM graphics window (it closes on ESC pressed)
ehu/gem/mouse : reports the mouse coordinates and click down/up events for all mouse buttons
ehu/gem/video : reads a video file (including audio channel which must be exported as WAV, check the help file)
ehu/gem/picture : reads an still image (TIFF, JPG, PNG), allows alpha 
ehu/gem/cam : reads video from a camera  
ehu/gem/texture : renders the output of a picture, cam or video
ehu/gem/rect : draws a rectangle 
ehu/gem/circle : draws a circle
ehu/gem/text : draws a text
ehu/gem/rec: recs video and audio into hardrive (video as QT and audio as WAV)

ehu/gem/rec: records video and audio into wav and mov files
ehu/gem/track : tracks movement from a video stream (ehu/cam or ehu/video)


UTILITIES (check ehu_utilities_abstractions.pd file)

ehu/abs_path : given a filename located in the same directory where the current working patch is, it returns the absolute path for that file 
ehu/rand_file : given a path to a directory it outputs paths to random files located in it on bang
ehu/loop_list : given a list or items (filenames, numbers) it loops them on bang 
ehu/list_folder: returns a list with the absolute paths of all files in a folder
ehu/timed_bang : given a list of times (in milliseconds) it outputs bangs on timeouts. (its a kind of sequencer)
ehu/timed_spigot : allows incomming values to pass through only every N milliseconds
ehu/follow : follows values with delay. Eases discontinuities in streams of numbers
ehu/elastic_follow : follows (elastically) values with delay. Eases discontinuities in streams of numbers
ehu/envelope : just wraps envgen adding some controls. it works as a kind of timeline sequencing object.
ehu/makeymakey : provides a simple abstraction that listens to events from a makeymakey device (wraps GEM mouse and keyboard)
ehu/vdelay: delays the output of a number for a given time
ehu/point_in_rect: outputs True if point is inside of rect


AUDIO (check ehu_sound_abstractions.pd file)

ehu/dsp : toogles Pure Data's DSP (Digital Sound Processing) on/off
ehu/splayer~ : plays a sound sample file with some control options (pitch, loop)
ehu/splayer2~ : plays a sound sample file with MANY control options
ehu/out~ : stereo sound output (dac~) with volume slider/mute and number
ehu/in~ : stereo sound input (adc~) with volume slider/mute and number
ehu/vol~ : controls volume of a sound signal with volume slider/mute and number
ehu/mix~ : mixes and fades two sound channels
ehu/plot : displays the waveform of an audio signal
ehu/rec~: records input signal into a hard drive as sound file. 
ehu/recorder~ : 	(Better use ehu/rec~) records input signal into a hard drive as sound file (experimental)
ehu/del~ : just a basic delay
ehu/rev~ : GUI to freeverb~ reverb object
ehu/ring~ : (Better use ehu/tremolo~) basic ring modulation 
ehu/distortion~ : just a distortion. wraps dist~ in creb library and provides a GUI
ehu/foldover~ : just wraps foldover~ in sigpack library and provides a GUI
ehu/limiter~ : just wraps limiter~ in zexy library and provides a GUI
ehu/tremolo~
ehu/phaser~
ehu/fuzz~
ehu/vibrato~
ehu/autodel~

ehu/pitch_sensor : analyses pitch and amplitude of sound signal (just wraps fiddle~)
ehu/hit_sensor : detects hits (onsets) in a sound signal (just wraps bonk~)
ehu/signal_sensor: outputs 1 when audio signal goes over a threshold, otherwise outputs 0


ARDUINO (check ehu_arduino_abstractions.pd file)

ehu/arduino/control : opens/closes the COM port where arduino is conected
ehu/arduino/set_analog : switches inputs on and off 
ehu/arduino/set_digital : sets mode (input or output) for digital pins 
ehu/arduino/get_analog : reports input on analog pins 
ehu/arduino/get_digital : reports input on digital pins 
ehu/arduino/send_analog : sends analog output pins (digital 9,10,11). Uses Pulse Width Modulation PWM
ehu/arduino/send_digital : sends output on digital pins 

Makeymakey :
ehu/makeymakey : just wraps gemkeyboard and mouse to output the values of the default keys associated with the makeymakey board

DMX (experimental controls for DMX, check ehu_dmx_abstractions.pd file)
ehu/dmx/control
ehu/dmx/matrix
ehu/dmx/slider



-- Remarks ---

The main folder is full with examples that illustrate different ways to use the abstractions. Check them out.

- The video abstraction wont play the sound track from video file. You need to provide a wav file with the same name as the video but with .wav extension next to the video file containing the audio track. For example : train.mov, train.wav. This is because GEM is mainly focused on video and 3D and it does not automatically read the audio from the video files.

- Paths to files are relative to the folder you are working. So it is a good idea to save working patches before starting to work on them. Check ehu/abs_path abstraction

- Image transparency: use TIFF images with alpha chanel

- Render order :
graphical abstracions (cam, video, picture ...) take a message "set" with an int 
number that sets its rendering order. Higher values render on top, min value is 1

- Render objects vs reader objects:
'Reader' objects load or read data such as images (ehu/gem/picture), videos (ehu/gem/video) or stream from webcam (ehu/gem/cam). The ehu/gem/texture object renders the data from a 'reader'. 

- Quality/mode
Pass a message [quality 1( or [quality 0( to ehu/win to change redeing quality of images and video. Default is quality 1
Pass a message [mode 1( or [mode 0( to ehu/win if you experince problems with video not being renderd (white square with no video), some graphic card require mode 0. Default is mode 1.

- Video file formats (thanks PD mailing list!) : 
Mac : Quicktime mov format with mjpeg (motion jpeg) works quite well and doesn't have too much cpu overhead.
Windows : avi format with dv codec might be running well (so you don't need to install quicktime).
GNU/Linux : just try. it depends on the libraries installed in your machine.

- Video effects/filters :
GEM provides many object to perform operations on the video signal output by ehu/gem/video, ehu/gem/cam or ehu/gem/image such as pix_contrast, pix_reduce and so on. Check the examples provided by GEM.

- Abstraction's GUI widgets:
Some EHU abstractions include embeded GUI elements to control them.  If you dont want to see the GUI, just right click them, select properties > untick "graph on parent" option, then save the file. Next time you open them they wont expose their GUI. Tick "graph on parent" again to revert to GUI mode. Additionally you can broadcast using object "send" a 1/0 message named EHU_gop. This  will be received by all active EHU objects. Since this changes the properties of the objects in the library use it at your own risk. However this should reduce CPU load, so you might want to use this if you are using it for situations where the abstractions GUI wont be used (such as an installation or a CPU hungry patch)

- List of global messages sent by EHU :
"EHU_quality" 1/0 affects the antialias of the images
"EHU_mode" 1/0 sets the mode to map the image texture, some graphic cards need "mode 0" in order to get any image or video rendered properly.
Alternatively you can pass a "quality" and "mode " message to ehu/win in the second inlet such as [quality 1( or [mode 0(
"EHU_gop" toogles the GUI widgets in the ehu objects
"EHU_win" message is broadcasted by the win object when it is opened. it contains a list with the width and height of the window. You can query that data to be broadcasted at any time by sending a message "EHU_win_get"
"EHU_comport_closed" when the port is closed or reopened by Arduino
"EHU_winopen" when the GEM window is opened
"EHU_winclose" when the GEM window is closed




-- Changes ---
0.86 10/2016
more abstractions added

0.85 09/2016
added signal_sensor and gem/rec objects
some small fixes here and there...

0.8 04/2016
changed folder structure to keep the ehu folder under the examples
several fixess all over, updated docs and examples, added list_folder, added experimental DMX controls

0.7.4 12/2013
removed from utilities: force, packers, moses4, rand_list

0.7.3 11/2013
fixed a few errors in examples and added comments
finally added video and video2 synchronization with audio, but droped video in favor of video2 functionality
updated examples and docs

0.7.2 11/2013
video loop was broken
added more examples and corrected documentation
added makeymakey object

0.7.1 7/2013
added rand_file object
added abs_path object
minor fixes in splayer~ and splayer2~ to change the way the paths are calculated
gem/video and gem/video2 almost there

0.7 5/2013
removed dependency from xgroove~
splayer and splayer2 introduced
plot has now a zoom control

0.6 12/2010
- Separated data reading from rendering by creating a texture object specialised on rendering. Cam/picture and video are focused now only in reading the data from the files.
- Several changes in track object

0.5 04/10
- render and reader funcionality separated into different objects. It allows for example to have multiple copies of the stream of a camara into screen.

0.4 11/09
- renamed arduino abstractions with get/set names to make it more clear.
- added list_rand / ifnew / moses4 abstractions
- arduino and gem abstractions have its own namespace ehu/arduino and ehu/gem

0.3 12/08
- new structure with folders documentation, ehu, examples 
- it can be installed now into extra folder within PD
- adding few many new objects for sound, arduino, utilities plus help and examples
- updating to PD extended 0.40.3
- major clean up/rewrite/creation of abstractions
- added GOP message to show/hide "graph on parent" GUI

0.2 5/08
- mayor cleanup. kind of usable now.

0.1.2 6/07
- examples combined with help files
- objects have now graphic GUI integrated (graph on parent => True)

0.1.1 5/07
- added filter examples
- changed names to [ehu/video] format to avoid having to set path
- removed open import dialogue. paths to files must be relative from now on.

0.1 5/07
- basic patches created





--- To do ---

- list_folder does not work properly with abs_path
- object that checks if all items in a list are equal?
- delete makeymakey object, the gemkeyboard codes are totally non crossplatform. better use gemkeyboard and mouse object directly
- win object ESC key window close does not work fine because keycodes are not crossplatform
- videos if stop on N frame then sent to M frame and then played again, they show frame N for a short time before moving into M

- timed_bang : on/off, fix loop 
- video does not bang on loop when go_to
- movement2 objet, pix_blob abs for color track
- change reg point of graphical objects to top/left or top/down



-- Aknowledgements --
The EHU library is supported by the Fine Arts college at the UPV/EHU Public University of the Basque Country (Euskal Herriko Universitatea, hence the name EHU) http://www.ehu.es. It is developed in collaboration with Josu Rekalde from the Arte y Tecnologia Department




