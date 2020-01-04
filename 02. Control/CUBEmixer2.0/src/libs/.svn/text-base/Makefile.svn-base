EXT=pd_linux

CVSROOT=-d:pserver:anonymous@cvs.pd.iem.at:/cvsroot/pure-data
REVISION=HEAD

LOCINSTALL_DIR=../../lib/libs/

.PHONY: install locinstall checkpddir aconnect-src iem_ambi-src iem_bin_ambi-src iemgui-src iemlib-src iemmatrix-src popup-src zexy-src 

install: checkpddir locinstall

ifeq (,$(findstring clean, $(MAKECMDGOALS)))
checkpddir:
	@if [ ! -d "$(PDSOURCE)" ]; then \
	  echo "please give the path to your PD-Sources with: make PDSOURCE=/path/to/pd/src";\
	exit -1; fi
endif

sf-login:
	cvs $(CVSROOT) login
	touch sf-login

######## AMIXER ################
#amixer-src: sf-login
#	cvs $(CVSROOT) checkout -r $(REVISION) -d amixer externals/iem/amixer/
#amixer-build: amixer-src
#	make -C amixer
#amixer-locinstall: amixer-build
#	cp mixer/*.$(EXT) amixer/amixer.pd $(LOCINSTALL_DIR)
#amixer: amixer-locinstall

######## HDSPMMIXER ################
hdspm_mixer-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d hdspm_mixer externals/iem/hdspm_mixer/

hdspm_mixer-build: hdspm_mixer-src
	make -C hdspm_mixer

hdspm_mixer-locinstall: hdspm_mixer-build
	cp hdspm_mixer/*.$(EXT) hdspm_mixer/hdspmmixer-help.pd $(LOCINSTALL_DIR)

hdspm_mixer: hdspm_mixer-locinstall

hdspm_mixer-clean:
	rm -rf hdspm_mixer


######## ACONNECT ################

aconnect-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d aconnect externals/iem/aconnect/

aconnect-build: aconnect-src
	make -C aconnect

aconnect-locinstall: aconnect-build
	cp aconnect/*.$(EXT) aconnect/aconnects.pd $(LOCINSTALL_DIR)

aconnect: aconnect-locinstall

aconnect-clean:
	rm -rf aconnect

######### hcs's folder_list ###############

folder_list-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d folder_list externals/hcs/folder_list.c

folder_list-build: folder_list-src
	$(CC) -DPD -O2 -funroll-loops -fomit-frame-pointer -fPIC -I$(PDSOURCE) -export_dynamic -shared -lc -lm -o folder_list/folder_list.$(EXT) folder_list/folder_list.c

folder_list-locinstall: folder_list-build
	cp folder_list/folder_list.$(EXT) $(LOCINSTALL_DIR)

folder_list: folder_list-locinstall

folder_list-clean:
	rm -rf folder_list

######### IEM AMBI ###############

iem_ambi-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d iem_ambi externals/iem/iem_ambi/

iem_ambi-build: iem_ambi-src
	make -C iem_ambi/src

iem_ambi-locinstall: iem_ambi-build
	cp iem_ambi/iem_ambi.$(EXT) $(LOCINSTALL_DIR)

iem_ambi: iem_ambi-locinstall

iem_ambi-clean:
	rm -rf iem_ambi

######### IEM BIN AMBI ###############

iem_bin_ambi-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d iem_bin_ambi externals/iem/iem_bin_ambi/

iem_bin_ambi-build: iem_bin_ambi-src
	make -C iem_bin_ambi/src

iem_bin_ambi-locinstall: iem_bin_ambi-build
	cp iem_bin_ambi/src/iem_bin_ambi.$(EXT) $(LOCINSTALL_DIR)

iem_bin_ambi: iem_bin_ambi-locinstall

iem_bin_ambi-clean:
	rm -rf iem_bin_ambi

######## IEM GUI ##################

iemgui-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d iemgui externals/iem/iemgui

iemgui-build: iemgui-src
	make -C iemgui/src

iemgui-locinstall: iemgui-build
	cp iemgui/iemgui.$(EXT) $(LOCINSTALL_DIR)

iemgui: iemgui-locinstall

iemgui-clean:
	rm -rf iemgui

######## IEM SPEC2 ##################

iem_spec2-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d iem_spec2 externals/iem/iem_spec2

iem_spec2-build: iem_spec2-src
	make -C iem_spec2/src

iem_spec2-locinstall: iem_spec2-build
	cp iem_spec2/iem_spec2.$(EXT) $(LOCINSTALL_DIR)

iem_spec2: iem_spec2-locinstall

iem_spec2-clean:
	rm -rf iem_spec2

######## IEM LIB ##################

iemlib-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d iemlib externals/iemlib/
	mkdir -p iemlib/lib

iemlib-build: iemlib-src
	make -C iemlib

iemlib-locinstall: iemlib-build
	cp iemlib/lib/*.$(EXT) $(LOCINSTALL_DIR)
	cp iemlib/iemabs/*.pd $(LOCINSTALL_DIR)

iemlib: iemlib-locinstall

iemlib-clean:
	rm -rf iemlib

####### IEM Matrix ###############

iemmatrix-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d iemmatrix externals/iem/iemmatrix/

iemmatrix-build: iemmatrix-src
	make -C iemmatrix/src

iemmatrix-locinstall: iemmatrix-build
	cp iemmatrix/*.$(EXT) $(LOCINSTALL_DIR)
	cp iemmatrix/abs/*.pd $(LOCINSTALL_DIR)

iemmatrix: iemmatrix-locinstall

iemmatrix-clean:
	rm -rf iemmatrix


########### miXed needed for the seq external in cyclone ##########################
# maybe substituted by xeq in future

miXed-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d miXed externals/miXed/

miXed-build: miXed-src
	make -C miXed PD_DIR=$(PDSOURCE)

miXed_objects=seq midiflush midiformat midiparse tot
miXed_externals=$(miXed_objects:=.pd_linux)

miXed-locinstall: miXed-build
	for i in $(miXed_externals); do cp -v miXed/bin/$$i $(LOCINSTALL_DIR); done
#	for i in $(miXed_objects); do cp -v miXed/test/cyclone/$$i-test.pd $(LOCINSTALL_DIR)/$$i-help.pd; done

miXed: miXed-locinstall

miXed-clean:
	rm -rf miXed

######## IEM GUI ##################
# maybe substituted by iem-gui in future

popup-src_: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d popup externals/bbogart/popup/

popup-build_: popup-src
	make -C popup pd_linux

popup-locinstall_: popup-build_
	cp popup/*.$(EXT) $(LOCINSTALL_DIR)

popup-clean_:
	rm -rf popup

# ############  local popup ###############
popup-src: 

popup-build: popup-src
	make -C ../popup pd_linux

popup-locinstall: popup-build
	cp ../popup/*.$(EXT) $(LOCINSTALL_DIR)

popup: popup-locinstall

popup-clean:
	make -C ../popup clean

######## OSC ##################

osc-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d osc externals/mrpeach/osc

osc-build: osc-src
	make -C osc -f ../Makefile.subdir $(EXT)

osc-locinstall: osc-build
	cp osc/*.$(EXT) $(LOCINSTALL_DIR)

osc-clean:
	rm -rf osc

osc: osc-locinstall

######## NET ##################

net-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d net externals/mrpeach/net

net-build: net-src
	make -C net -f ../Makefile.subdir $(EXT)

net-locinstall: net-build
	cp net/*.$(EXT) $(LOCINSTALL_DIR)

net-clean:
	rm -rf net

net: net-locinstall

######## ZEXY ##################

zexy-src: sf-login
	cvs $(CVSROOT) checkout -r $(REVISION) -d zexy externals/zexy 

zexy-build: zexy-src
	make -C zexy/src

zexy-locinstall: zexy-build
	cp zexy/*.$(EXT) $(LOCINSTALL_DIR)
	cp zexy/abs/*.pd $(LOCINSTALL_DIR)

zexy-clean:
	rm -rf zexy

zexy: zexy-locinstall

######## doit #################################

sources: aconnect-src folder_list-build iem_ambi-src iem_bin_ambi-src iemgui-src iemlib-src iemmatrix-src iem_spec2-src miXed-src net-src osc-src popup-src zexy-src

build: aconnect-build folder_list-build iem_ambi-build iem_bin_ambi-build iemgui-build iemlib-build iemmatrix-build iem_spec2-build miXed-build net-build osc-build popup-build zexy-build

locinstall: aconnect-locinstall folder_list-locinstall iem_ambi-locinstall iem_bin_ambi-locinstall iemgui-locinstall iemlib-locinstall iemmatrix-locinstall iem_spec2-locinstall miXed-locinstall net-locinstall osc-locinstall popup-locinstall zexy-locinstall

clean: aconnect-clean folder_list-clean iem_ambi-clean iem_bin_ambi-clean iemgui-clean iemlib-clean iemmatrix-clean iem_spec2-clean miXed-clean net-clean osc-clean popup-clean zexy-clean
	rm -f sf-login

distclean: clean
	rm -rf $(LOCINSTALL_DIR)/*
