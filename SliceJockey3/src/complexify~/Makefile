# Makefile for pure data class complexify~ in lib kat.

lib.name := kat
class.sources := complexify~.c
datafiles := complexify~-help.pd

cflags := -I ../libhack -I ../libcomplex

# Overridable path to find Makefile.pdlibbuilder.
ifndef PDLIBBUILDER_DIR
 PDLIBBUILDER_DIR := ..
endif

# Helper makefile.
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
