#!/bin/sh

if [ "x$PD" = "x" ]
then
  PD=pd
fi

echo argc $#
ARGS=$@
if [ "$#" != "0" ]; then
 if [ "x$1" = "x-defaults" ]; then
  shift
  ARGS="-rt -channels 24 $@"
 fi
fi

PDPATHS="-path .:..:../abs/:../libs/iemabs:../libs/zexyabs:../libs/:../plugins/:abs"
PDLIBS="-lib zexy:iemlib1:iemlib2:iemgui:iemmatrix:iem_ambi"

${PD} ${PDPATHS} ${PDLIBS} -32bit -oss ${ARGS}

