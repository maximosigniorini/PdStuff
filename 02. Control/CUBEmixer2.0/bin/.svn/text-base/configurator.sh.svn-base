#!/bin/sh

#ECHO=echo

function test_pd() {
## this function returns the first of its arguments that is
## an executable file
## if no executable files are given, it returns the default
## pd-binary (if any)
## usage:
##  test_pd /path/to/my/preferred/pd /path/to/my/second/choice/pd
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

CUBEMIXERPATH=$(dirname $0)/..
cd ${CUBEMIXERPATH}/tools/configurator/ || (echo "directory for CONFIGURATOR not found!!"; exit -1)

LOCALVARSTEMPLATE="etc/CUBEmixer/LocalVars.template.sh"
LOCALVARS="etc/CUBEmixer/LocalVars.sh"

if [ -e ${LOCALVARSTEMPLATE} ]; then
 . ${LOCALVARSTEMPLATE}
fi
if [ -e ${LOCALVARS} ]; then
 . ${LOCALVARS}
fi

PD=$(test_pd $PD ${PD_INSTALL}/pd)

if [ "x$PD" = "x" ]
then
  echo "pd not found!"
  echo "set the environment variable PD to the full-path to the pd binary"
  echo "e.g.: \"export PD=/usr/bin/pd\""
  echo
  exit -1
fi

CONFIGURATOR_PATCH=MAIN.pd

${ECHO} ${PD} ${PD_OPTIONS} ${PD_PATH} ${PD_LIB} -path ../../lib/libs -lib zexy:folder_list -open ${CONFIGURATOR_PATCH}
