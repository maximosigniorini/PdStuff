#!/bin/sh

egrep -h "^/" $@ | sed -e 's|/[0-9]*/|/\$1/|' -e 's|/[0-9]*/|/\$2/|' | sort -u 
