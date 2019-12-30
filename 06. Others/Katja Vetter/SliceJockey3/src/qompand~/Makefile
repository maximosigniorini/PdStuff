# Makefile for puredata class qompand~ in lib kat.

lib.name := kat
class.sources := qompand~.c
datafiles := qompand~-help.pd

cflags := -I ../libhack -I ../libcomplex

# Overridable path to find Makefile.pdlibbuilder.
ifndef PDLIBBUILDER_DIR
 PDLIBBUILDER_DIR := ..
endif

# Helper makefile.
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
