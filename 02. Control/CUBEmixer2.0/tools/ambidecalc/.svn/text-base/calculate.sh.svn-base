#!/bin/sh

INFILE=speakerlayout.txt
OUTFILE=output.mtx


function usage() {
 echo "${0##*/}: calculate ambisonic decoding matrix for a given loudspeaker-layout"
 echo "		this programm will read in the loudspeaker-setup from a given file"
 echo "		and will then calculate the decoding matrix and write it into an output file"
 echo
 echo "	-h, --help"
 echo "		print this help"
 echo "	-i, --infile <infile>"
 echo '		read the loudspeaker setup from <infile> instead of "'${INFILE}'"'
 echo "	-o, --outfile <outfile>"
 echo '		write the decoding matrix to <outfile> instead of "'${OUTFILE}'"'
 echo
 exit 0

}


function parse_args() {
 while [ "$#" -ge 1 ]; do 
  case "x$1" in
  x--help|x-h)
	usage
	;;
  x--infile|x-i)
	INFILE=$2
	shift
	;;
  x--outfile|x-o)
	OUTFILE=$2
	shift
	;;
  *)
	arg=$1
	if [ "x${arg}" != "x${arg#--infile=}" ]; then INFILE=${arg#--infile=}; fi
	if [ "x${arg}" != "x${arg#-i=}" ]; then INFILE=${arg#-i=}; fi

	if [ "x${arg}" != "x${arg#--outfile=}" ]; then OUTFILE=${arg#--outfile=}; fi
	if [ "x${arg}" != "x${arg#-o=}" ]; then OUTFILE=${arg#-o=}; fi
	;;
  esac
  shift
 done

 if [ -r "${INFILE}" ]; then
   :
 else
   echo "input file \"${INFILE}\" not readable!!"
   exit -1
 fi

 if [ -e "${OUTFILE}" ]; then
   echo "output file \"${OUTFILE}\" already exists!!"
   echo "please delete manually before proceeding..."
   exit -2
 fi
}


parse_args $@

echo "infile: ${INFILE}"
echo "outfile: ${OUTFILE}"

pd -nogui -path ../../lib/libs:../../lib/DSP/abs:. -lib iemmatrix:zexy:iem_ambi:iemlib1:iemlib2 -open MAIN.pd -send ";inoutfile ${INFILE} ${OUTFILE}; pd quit"
