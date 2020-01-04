a collection of (sub)patches to make (quick and dirty) generative music and sound.
low- and higher level patches to build generative "ensembles"
in a kind of "eurorack-style". patching and combining devices to make
'virtual windchimes'... there are some intersections with my instruments-collection
and the "pure modules" virtual(virtual) modular.

install: everything should run from the "generative_collection" directory.
you can copy the patches prefixed "abs_" somewhere into pds
abstraction-search-path ("extras",...) for enhanced convenience. and as usual, these
abstractions are a subset of the abstractions included with my "instruments".

naming, colourcoding, placing of gui-elements is not exactly consistent,
since there was a lot copy&paste from my other work...
there are a few conventions though:

-pitch and other message-values (non audio) are usually numbers in the range 0..127 (sometimes negative)
midi-compatible, but not necessariely integers.
with only a few exceptions, for example: preset nrs (small ints), random seeds (larger numbers)
or preset data (list-messages) or (sample)filenames.

-if it makes sense, all message-inputs are "hot", a message on any input produces an output
value. (for example the "add"-patches. and for example not the "qt2clock" patch.

-there is a global variable $0globalbpm1, used for all tempo/length calculation. it can be
overriden by the local bpm-inlets though, and is set by the "tempo" subpatch.

-time is usually measured in beats (1/4 notes), with length depending on tempo.

-for clocks etc. instead of "bangs", any message (usually a number) can be used.

-everything is basically monophonic, like it is often the case with modular synthesizers.
synths etc. use rather triggers than midi-notes (on/off), note length is set elswhere,
if applicable. (since not meant to be played by humans) there is a "makenote"-patch
to play polyphonic synths though.

the overview-patches have a name starting with a number, the examples are prefixed "ex_".

work in progress.

8/2016 version 0.1x,  still a lot to be done...
12/2016 v 0.11, some new patches, small adjustments and bugfixes
6/2017 v 0.12 small bugfixes, some features added (eoc...), some new patches
6/2018 0.13 small bugfixes

