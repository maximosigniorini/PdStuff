# Root makefile for pure data classes in SliceJockey project. For native builds
# use regular build commands: make && make install. Binaries and helpfiles are
# installed in ../pdlibs/kat.

makefiledirs = \
bitflip~ \
krunch~ \
complexify~ \
duck~ \
qompand~ \
slicycle~ \
verbkit

# Project-relative path to install lib kat.
export PDLIBDIR := $(abspath $(CURDIR)/../pdlibs)

# Overridable path to find Makefile.pdlibbuilder.
ifndef PDLIBBUILDER_DIR
 PDLIBBUILDER_DIR := $(abspath $(CURDIR))
endif

# Helper makefile.
-include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder


################################################################################
################################################################################
################################################################################


# Target add-sources is only relevant in the context of creating a project
# distribution on developer machine where sources shared between projects
# are in directory pd-kat/src.
# - copy SliceJockey3 project dir
# - cd to SliceJockey3/src within copy
# - make add-sources pdkatdir=<path-to-pd-kat>

# Assumed path to pd-kat.
pdkatdir := ../../../pd-kat

# Source files and directories to copy.
sourcefiles := $(makefiledirs) libcomplex libhack libutil libinterp \
               Makefile.pdlibbuilder

dummy-default:
	$(info ++++ dummy default, Makefile.pdlibbuilder not included)

add-sources:
	$(foreach sourcefile, $(sourcefiles), \
        cp -aur $(addprefix $(pdkatdir)/src/,$(sourcefile)) ./;)

