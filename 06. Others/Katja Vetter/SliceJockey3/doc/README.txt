

SliceJockey version 3.0.0 package for vanilla Pd (tested with Pd 0.49).


- Pure Data patches
- project-specific binaries:
  [bitflip~] [krunch~]
  [complexify~] [duck~] [qompand~]
  [slicerec~] [sliceplay~]
  [verbkit]
- source code of these classes
- help patches for these classes


///////// DEPENDENCIES /////////////////////////////////////////////////////////


In order to use SliceJockey3 you must have vanilla Pd installed on your computer (msp.ucsd.edu), plus external libraries nilwind, hcs, zexy. These libs can be installed via Pd menu Help > Find externals or on Linux via distro package manager.

nilwind: svf~
nilwind: mousestate
nilwind: scope~

hcs: split_path
hcs: window_name
hcs: sys_gui
hcs: canvas_name

zexy: limiter~
zexy: z~


///////// INSTALL //////////////////////////////////////////////////////////////


The SliceJockey3 zipped package contains directory SliceJockey3. Copy or move directory SliceJockey3 with all it's contents to any location on your computer which suits you. Do not reorganize the content within directory SliceJockey3 and do not change directory names.


///////// RUN //////////////////////////////////////////////////////////////////


Start Pd extended. Select file >> open and load the patch SliceJockey3.pd from directory SliceJockey3. For help, click the question mark in the SliceJockey3 window. For settings, click the exclamation mark. Pay special attention to audio settings. To start slice-recording, activate one of the [>] buttons and feed sounds into your computer.


///////// SESSION RECORDING ////////////////////////////////////////////////////


Directory 'SJsessions' is for session recordings which are automatically stored there. You can safely rename recorded .wav files, play them with any soundfile player, or copy them to another location.


////////// SUPPORT /////////////////////////////////////////////////////////////


SliceJockey is documented with included help files, and a webpage at:

www.katjaas.nl/slicejockey/slicejockey.html

For questions about installation and configuration of Pure Data and external libraries, consult puredata.info/docs.

Also consider searching the forum and the Pd mailing list archives:

puredata.hurleur.com
lists.puredata.info/pipermail/pd-list

If you find a bug in patch [SliceJockey3] or any of the included abstractions and classes, please send an email to katjavetter@gmail.com.


////////// SLICEJOCKEY VERSION HISTORY /////////////////////////////////////////


SliceJockey3.pd
- made compatible with vanilla Pd >= 0.49 + nilwind + hcs + zexy
- not compatible with Pd-extended

SliceJockey2.pd
- made compatible across Pd-extended 0.42 and 0.43
- introduction of playback tonalities (harmonic, minor, major, 12-tone, hijaz,     slendro)
- feedback loop around effects (resonant filter, krunch)
- presets for slicycle settings
- manual record start
- midi-controlled record start / stop
- improved built-in help
- dropped: xy-object 'active time'
- dropped: gamepad support

SliceJockey.pd
- initial version


Version history of included classes: see source files slicerec~.c, sliceplay~.c etcetera.

