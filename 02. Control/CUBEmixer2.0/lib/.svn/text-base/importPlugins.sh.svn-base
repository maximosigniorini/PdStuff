#!/bin/sh

FORCE=

PLUGINDIR=plugins
PLUGINFILE=${PLUGINDIR}/plugins.txt

GUIPATCH=GUI.pd
DSPPATCH=DSP.pd

OUT_GUIPATCH=GUI/inchan/plugin/EFF_PLUG_IN.pd
OUT_DSPPATCH=DSP/abs/EFF_PLUG_IN~.pd

function usage() {
 echo "$0 [-f] [-h] [<plugindir>]"
 exit 0
}

function parse_args() {
 while [ "$1" ]; do
  case "$1" in
  -h|--help)
    usage
    ;;
  -f|--force)
    FORCE="yes"
    ;;
  *)
    PLUGINDIR="$1"
    ;;
  esac
  shift
 done
}

if [ -d ${PLUGINDIR} ]; then
 :
else
 usage
fi

if [ -z "${GUIPATCH}" ]; then
 echo "no gui-patch defined!"
fi

if [ -z "${DSPPATCH}" ]; then
 echo "no dsp-patch defined!"
fi

function checkPlugin() {
 local d
 d=$1
  if [ -f ${d}/${GUIPATCH} ] && [ -f ${d}/${DSPPATCH} ]; then
    echo ${d#${PLUGINDIR}/}
  fi

}

function list_plugins() {
 local plugin
 find ${PLUGINDIR} -mindepth 1 -maxdepth 1 -type d | while read plugin; do
  checkPlugin $plugin
 done
}

function generateGUIpatch() {
  local plugin
  local plugfile
  local connector
  local pluginlist
  plugfile=$1
  pluginlist="";
  for plugin in $(cat ${plugfile}); do
      pluginlist="${pluginlist} ${plugin}"
  done
  if [ -r "${plugfile}" ]; then
    echo "#N canvas 0 0 450 300 10;"
    let connector=0
    for plugin in ${pluginlist}; do
      echo "#X obj 60 $[100+25*${connector}] inchan/plugin/plugin ${plugin} \\\$1 \\\$2;"
      let connector++
    done
  fi
}

function generateDSPpatch() {
  local plugin
  local plugfile
  local connector
  local pluginlist
  plugfile=$1
  pluginlist="";
  for plugin in $(cat ${plugfile}); do
      pluginlist="${pluginlist} ${plugin}"
  done
  if [ -r "${plugfile}" ]; then
    echo "#N canvas 0 0 450 300 10;"
    echo "#X obj 0   0 inlet~;"
    echo "#X obj 0 200 outlet~;"
    echo "#X obj 0  50 CUBEmixer_plugin0~ \\\$0 \\\$1 \\\$2;"

    let connector=0
    for plugin in ${pluginlist}; do
      echo "#X obj 60 $[100+25*${connector}] CUBEmixer_plugin~ \\\$0 ${plugin} \\\$1 \\\$2;"
      let connector++
    done

    echo "#X connect 0 0 2 0;"
    echo "#X connect 2 0 1 0;"

    let connector=3
    for plugin in ${pluginlist}; do
      echo "#X connect 0 0 ${connector} 0;"
      echo "#X connect ${connector} 0 1 0;"
      let connector++
    done

  fi
}




parse_args $@

if [ -e "${PLUGINFILE}" ] && [ -z "${FORCE}" ]; then
 echo "${PLUGINFILE} already exists!"
 echo "not overriding unless you specify \"-f\""
 echo
 exit -2
fi

if [ "${PLUGINFILE}" ]; then
 list_plugins > ${PLUGINFILE}

generateGUIpatch ${PLUGINFILE} > ${OUT_GUIPATCH} 
generateDSPpatch ${PLUGINFILE} > ${OUT_DSPPATCH} 

else 
 list_plugins
fi



