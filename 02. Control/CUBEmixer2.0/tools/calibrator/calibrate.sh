#!/bin/sh

cd ${0%/*}

CALIBRATOR_PATCH="CALIBRATOR.pd"
CALIBRATOR_PATH="-path ../../lib/libs/"
CALIBRATOR_LIBS="-lib zexy:iemmatrix"

pd -rt -inchannels 2 ${CALIBRATOR_PATH} ${CALIBRATOR_LIBS} ${CALIBRATOR_PATCH}
