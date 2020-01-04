#!/bin/sh

## this function returns the first of its arguments that is 
## an executable file
## if no executable files are given, it returns the default 
## pd-binary (if any)
## usage:
##  test_pd /path/to/my/preferred/pd /path/to/my/second/choice/pd
function test_pd() {
local i
local ARGS
ARGS="$@ $(which pd)"
for i in $ARGS
do
 if [ -x "$i" ]
  then
   echo $i
   return
  fi
 done
}

PD=$(test_pd $PD /usr/local/src/pd-0.37-4.patched/bin/pd)

PDPATHS="-path .:abs/:libs/:plugins/:GUI/:DSP/:GUI/abs:DSP/abs:libs/iemabs:libs/zexyabs"
PDLIBS="-lib zexy:iemlib1:iemlib2:iemgui:iemmatrix:iem_ambi"

${PD} $PDPATHS $PDLIBS $@
