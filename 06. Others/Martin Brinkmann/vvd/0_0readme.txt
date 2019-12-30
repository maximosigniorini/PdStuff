vvd "virtual (virtual) devices"
--------------------------------

a collection of modular building-blocks and instruments/effects.
replaces my "pure modules" and maybe "groovebox2". and contains
parts of the "generative collection" and my "instruments wip".

main difference to pure modules: signals AND messages!
no more "row-layout".
main diffwerence to groovebox2: no more song-position, everything is based on clock-pulses.

install:
-----------
everything should run from the "vvd" directory for a first test.
(or if you keep all your patches in the same directory...)
the overview-patches/module-collections are prefixed "0_".
the example patches are prefixed "ex_" (might contain buggy/outdaed modules)

you can copy the patches prefixed "abs_" somewhere into pds
abstraction-search-path ("extras",...) for enhanced convenience,
if you have not already copied my 'instruments_wip...' abstractions, which
are the same (and more).
or you could add the vvd folder (like any other folder with abstractions)
in pd-prefs to the path.

a few, maybe unexpected particularities:
-----------------------------------------
gates (and short gates) can(!) carry velocity/level information (unlike 'real' eurorack)

samples are at the moment not(!) stored with snapshots, but per patch. (all snapshots share the same
samples). recorded audio can/must be saved (and reloaded to capture the new filename)
manually. (before closing pd/the patch) that might become more elegant in future versions...

everything is audio in the range -1..1, but there are also messages. for example for
the polyphonic instruments and sequencers,and for filenames, global variables.

invisible 'wireless' connections are used for catch/throw needed for audio feedback,
and for filenames.

colourcoding:
audio signals have blue inlets, (polyphonic note)-messages (midi...) have grey inlets.
soundgenerators (osc, sampler,...) have dark red labels, sound modifiers (filters,fx,...)
dark blue ones, and utility/control (env, sequencers,...) dark green.
a violet button (bang) is used for assinging the samplefilebrowser.
midi-related functions (learn, monitor,...) are light green, other colourcoding is not
always consistent... (the redder, the more destructive, most of the time)

current pd (vanilla) (>=049) is preferred, older versions might require some adjustments
concerning pitch and oversampling, and missing objects.

8/2017: "version 0.1"
11/2017: v27112017, after some conceptual changes, first (bugfix, catch/throw is still easy to confuse...)
release, no examples yet... needs testing, a few modules still missing (switch, scanner...)
02/2018: small bugfixes
09/2018: fixed broken pm-operator and wavefolder
10/2018: redesigned catch/throw,thanx to nacho for testing, fixed bpm-clock, still more testing needed
03/2019: a few new modules, small bugfixes, fixed presetsaving for generative sequencers
08/2019: a few new modules, small bugfixes
