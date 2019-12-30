# Makefile for lib verbkit~ within lib kat.

lib.name = kat

# link all classes plus setup method in single executable by default
verbkit.class.sources = \
combsL~.c \
combsR~.c \
damp~.c \
dcombsL~.c \
dcombsR~.c \
diffusorL~.c \
diffusorR~.c \
verbkit.c

datafiles = verbkit-help.pd

cflags = -I ../libhack

# compile code optimized for non SIMD architecture
cflags += -DNOSIMD

# Overridable path to find Makefile.pdlibbuilder.
ifndef PDLIBBUILDER_DIR
 PDLIBBUILDER_DIR := ..
endif

# Helper makefile.
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
