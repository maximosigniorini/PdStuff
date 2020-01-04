ambidecalc
==========


how to write a speakerlayout file:
==================================

the speaker layout file descibes the layout of your speaker-setup in a 
text-based line-oriented manner.
each line looks like:
	<lstype> <#id> <phi> <theta> [<options> ...]
- the <lstype> describes the type of the loudspeaker, e.g. whether it is a 
"real" or a "virtual" loudpspeaker
- the <#id> is a numeric id that must be unique within the given <lstype>,
	starting at 1(!)
- <phi> is the azimuth of the loudspeaker measured from a reference point, in 
	degree
- <theta> is the elevation of the loudspeaker measured from a reference point,
	in degree
- whether there are any options and what they are, depends on the <lstype>

loudspeaker-types
	currently there are 2 lstypes implemented: "real" and "phantom"

"real"
	the "real" lstype denotes real speakers; no options are available for 
	this kind of speakers
	example:
		"real 1 0 90": describes a real speaker at the zenith
"phantom"
	speakers of type "phantom" are non-existant speakers that are used to
	ease the calculation of the decoding matrix;
	in the resulting decoding matrix, the signals sent to these virtual
	speakers are either discarded, or distributed to "real" speakers in a
	weighted manner.
	the options for this type is a list of value-pairs; each value pair 
	consists of the #id of a real speaker, and a weight, by which the
	phantom-signal is weighted before it is added to the real speaker's
	signal:
		"phantom <#phantomid> <phi> <theta> [<#realid_i> <weight_i>]*"
	the #realid_i MUST denote an existing "real" loudspeaker
	the weightid_i is given in linear values (usually >0.f)
	examples:
		"phantom 1 0 0": describes virtual speaker #1 in front;
			this speaker's signal is discarded
		"phantom 9 22.5 -30 1 0.5 2 0.5": describes a virtual speaker 
			whose signal is added to the real-speakers #1 and #2 
			with -6dB

