# Makefile for pure data class krunch~ in lib kat.

lib.name := kat
class.sources := krunch~.c
datafiles := krunch~-help.pd

cflags := -I ../libhack

# Overridable path to find Makefile.pdlibbuilder.
ifndef PDLIBBUILDER_DIR
 PDLIBBUILDER_DIR := ..
endif

# Helper makefile.
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
