# Makefile for pure data class duck~ in lib kat.

lib.name := kat
class.sources := duck~.c
datafiles := duck~-help.pd

cflags := -I ../libhack

# Overridable path to find Makefile.pdlibbuilder.
ifndef PDLIBBUILDER_DIR
 PDLIBBUILDER_DIR := ..
endif

# Helper makefile.
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
