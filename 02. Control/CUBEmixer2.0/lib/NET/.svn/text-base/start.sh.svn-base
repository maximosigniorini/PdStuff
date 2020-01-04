#!/bin/sh

if [ "x$PD" = "x" ]
then
  PD=pd
fi

PDPATHS="-path .:..:../abs/:../libs/:../plugins/:abs"
PDLIBS="-lib zexy:iemlib1:iemlib2:iemgui:iemmatrix"

${PD} $PDPATHS $PDLIBS $@
