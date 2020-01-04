#!/bin/sh

BUGS=BUGS.txt
TODO=TODO.txt


function print_header(){
echo "ACHTUNG: bitte in diesem file nichts editieren!"
echo "ACHTUNG: statt dessen das file ${BUGS} editieren!"
echo "ACHTUNG:"
echo "ACHTUNG: (dieses file ist nur ein "view" auf ${BUGS})"
echo 
}

print_header > ${TODO}

#cat ${BUGS} | \
# sed -e '/./{H;$!d;}' -e 'x;/\+/d' \
# > ${TODO}

cat ${BUGS} \
 | sed -e '/./{H;$!d;};x;/\+/d' \
 | grep . \
 >> ${TODO}

#cat ${BUGS} | \
# egrep "^([[:alnum:]]|([[:space:]]*\-))" | \
# sed "/^[[:alnum:]]/{x;p;x}" \
# > ${TODO}
