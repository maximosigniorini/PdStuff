# Pd
pure data patches / live audio processing
// spiritditch // v1 (October 2019)

A six-tap delay with independant control (per tap) of feedback, delay time, pitch, direction, and filter frequency. Loosely based on Rainmaker eurorack module by Intellijel, but I soon deviated to my own musical preferencees. Enjoy!

// controls //___________________________________________________

* i/o = open/close input to all six taps.
* freeze = set feedback to 100% retaining current characteristics. Freeze disables audio input. unfreeze returns feedback to previous settings.
* clear = clears all six taps.
* dry/wet = mix of microphone signal, default is 100% wet. Less than this CAN cause feedback.
* tempo = distance of spacing of taps. short = 50ms, medium = 250ms, long = 1600ms, ultra = 3600

// global parameters //____________________________________________

* tap times = length of individual taps in relation to mater time (tap I). see individual times on taps.
* pitch class: loco = no transposition, 8vb = some an octave lower, 8va = add some octave higher, fifths = add fifths, minor = add minor thirds, add major thirds, up fourth = transpose up a fourth.
* reverse = change direction of six taps.
* thinner = turning on will activate a mode where each tap only recieves a signal 60% of the time, good for turning on spiritditch for longer periods and not becoming overwhelmed.
* feedback = controls all six feedback parameters.
* filters = controls all six filter frequencies (filters are disengaged when at top position).

// randomise parameters //__________________________________________

* length = random tap length (except tap I master time).
* feedback = random feedback settings for all taps. This is disabled when in freeze mode.
* filters = random filter frequency for all taps.
* pitch = random pitch for all taps (chromatic between octave down and octave up).
* reverse = change direction for random amount of taps.
* ALL = randomise all parameters except thin and master time. When in freeze mode feedback is disabled to keep sustained sounds.
* play = auto randomiser, essentially a random metronome pressing ALL button.

// key commands (only active when toggle is on) //_____________________
i/o = spacebar. freeze = f. clear = c. length = l. feedback = b. filters = t. pitch = p. reverse = r. ALL = a. play = y. thinner = n.
