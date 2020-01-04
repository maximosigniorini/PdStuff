#!/bin/sh

if [ "x$PD" = "x" ]
then
  PD=pd
fi

PDPATHS="-path .:..:../abs/:../libs/:../plugins/:abs:../libs/zexyabs/:../libs/iemabs"
PDLIBS="-lib zexy:iemlib1:iemlib2:iemgui:iemmatrix"

${PD} $PDPATHS $PDLIBS -nosound $@
