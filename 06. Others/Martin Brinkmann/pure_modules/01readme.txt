a collection of modular building-blocks.

install: everything should run from the "pure_modules" directory.

open the "blocks_and_docs" patch for a module overview (and as a source for copy/paste,
the latest/fixed versions of modules are found here!)

or try one of the example patches (prefixed "ex_" (might contain buggy/outdaed modules)

you can copy the patches prefixed "abs_" somewhere into pds
abstraction-search-path ("extras",...) for enhanced convenience,
if you have not already copied my 'instruments_wip...' abstractions, which
are the same (and more).
or you could add the pure modules folder in pd-prefs.

a few, maybe unexpected particularities:
triggers/gates carry velocity information!
every module has a setting for trigger-sensibility for interfacing with
the real world or using audio as trigger, whatever.

pd (vanilla) >=046 is preferred, older versions might require some adjustments
concerning pitch and oversampling.

"version 0.1x", still a lot to be done:
-more modules!
-polyphonic midi-in?
-preset morphing?
-midi learn for everything...?
-everything a little quick and dirty
-does it work with 'real world modules'?
-bugs
-remove redundant patches?
-colourcoding of faders and labels?

-and maybe a "virtual virtual modular system" is nonsense anyway...

0.11, a few bugs fixed, a few missing modules
0.12, a few bugs fixed, a few additional modules
0.13, some more modules/bug fixes
0.14, added fx/sequencers, fixes 
0.15, a few new modules, bug fixes and some docs
0.16, added more missing modules, bug fixes
0.17, bug fixes, small improvements/added functions
0.18, bugs fixes, small improvements, added modules
0.19, i have to admit that inlet/outlet labels make sense.
wavefolder, better sequencers, few new modules, minor improvements.
0.20 minor improvements, bugs fixed
0.21 small bugfixes, added sample-save-functionality to all modules with audio-recording
probably the final release, since "pure modules" is superseded by "virtual virtual devices"...
