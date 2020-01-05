=======
RTC-lib
=======

Real Time Composition Library for Pure Data
===========================================

Abstract 
========

This software library - a collection of patches and externals for Pure Data  -
offers the possibility to experiment with a number of compositional techniques,
such as serial procedures, permutations and controlled randomness. Most of
these objects are geared towards straightforward processing of data. By using
these specialized objects together in a patch, programming becomes much more
clear and easy. Many functions that are often useful in algorithmic composition
are provided with this library - therefore the composer could concentrate
rather on the composition than the programming aspects.

Originally, the Real Time Composition Library (RTC-lib) was developed during my
extensive work on Lexikon-Sonate (1992 ff.), an interactive realtime
composition for computer-controlled piano which I started at IRCAM, Paris in
1992.

Regardless the fact that it was conceived for a specific project it became more
and more obvious that its functionalities are open and generic enough to be
used by other composers in different compositional contexts. Based on paradigms
which have been extracted from serial thinking (cf. Gottfried Michael Koenig
and Karlheinz Stockhausen) and its further development until nowadays it does
not force towards a certain aesthetic, but provides a programming environment
for testing and developing compositional strategies.

The Real Time Composition Library comes with a Hypertext-like on-line help
which allows to have a perfect overview on the library objects and their
multiple relationships.  Thanks to Richard Dudas (Cycling74), Peter Elsea
(University of California, Santa Cruz), Serge Lemouton (IRCAM, Paris) and jasch
who have ported the RTC-lib's externals to OSX.

Contents
========

RTC-lib was ported to Pd mainly by Frank Barknecht in 2006. The port was made
without access to Max/MSP directly, but as RTC-lib contains excellent
documentation this wasn't really necessary most of the time. To import the
Max-patches, the Cyclone importer by Krzysztof Czaja was used, which turned out
to be an invaluable help.

RTC-lib for Pd contains almost all objects of the RTC-lib for Max/MSP. A
current list of what's still missing is contained in the file rtc-progress.csv.
Max-specific objects to control aspects of the Max-software deliberately have
been left out.

Where nameclashes with existing Pd objects and externals occured, the
respective RTC-objects also have been omitted. So far this only affected the
[minus] abstraction.

RTC-lib for Pd no lonfer mimicks the directory layout of the Max-version with
its seperate directories for each section likt Harmony, Rhythm etc. Instead all
patches and their help files have been put into a single directory called
"rtc".  To install the patches, either add this directory to your path and use
the objects with their standard names, or copy the while "rtc"-directory
somewhere into your path, like into /usr/lib/pd/extra/rtc and use them with a
"rtc"-namespace prefix: Then for example the [super-rhythm] object could be
called as [rtc/super-rhythm]. Note that then you may also need to add the
rtc-directory to your help path with "-helppath /usr/lib/pd/extra/rtc" or
similar, if you want to call the help-files.

Help-files have been placed next to their respective abstractions for
simplicity. They follow the naming convention "NAME-help.pd" to give help for
an abstraction "NAME.pd". Additionally you will find overview patches for each
topic section in the subdirectory "rtc/rtc-help". The main file here is
rtc/rtc-help/RTC-Overview.pd (Later this will be moved to "rtc/RTC-Overview.pd",
but a bug in the [declare] object currently makes this non-functional.

There is a special directory, "pdutils" which contains some small tools that
aided in the porting as well as some abstractions not included in the original
RTC-lib for Max, but that are used in the Pd-version.

Requirements
============

As a lot of the RTC-objects deal with list manipulations there is quite some
overlap with the abstraction collection "[list]-abs" by Frank Barknecht,
available in the Pd repository at http://pure-data.sf.net/. Having this
installed (without any kind of namespace-prefix) is necessary to be able to use
most RTC-lib abstractions.

Apart from that, also objects from the following external libraries have been
used:

* Cyclone (prob, zl, ...)
* zexy (sort,...)
* maxlib (???)

Generally if you install the pd-extended distribution you should be fine and
you will only need to load the respective libraries and adjust the search
paths.

The [play2] abstraction used in several help files optionally can play midi
notes with the [fluid~] soundfont synthesizer. If you don't have [fluid~], you
can also choose to send the midi output to an external player accessed through
[noteout]. See the [play2] help file for details. 

Feedback
========

Please report bugs and feature requests regarding the Pd version to:

Frank Barknecht
http://footils.org
fbar (a) footils.org 
