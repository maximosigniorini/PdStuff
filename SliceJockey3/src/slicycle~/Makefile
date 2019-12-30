# Makefile for pure data classes slicerec~ and sliceplay~ in lib kat.

lib.name := kat

class.sources := slicerec~.c sliceplay~.c
datafiles := slicerec~-help.pd

# include libhack for absolute.h
cflags := -I ../libhack

# Overridable path to find Makefile.pdlibbuilder.
ifndef PDLIBBUILDER_DIR
 PDLIBBUILDER_DIR := ..
endif

# Helper makefile.
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
