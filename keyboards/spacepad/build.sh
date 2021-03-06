#!/usr/bin/env bash

DIR=`pwd`

cd ../../
export NRFSDK15_ROOT=/mnt/c/users/f402n/documents/NordicNRF5/libs/nRF5_SDK_15.0.0_a53641a
make spacepad

cd .build
FILE=${1:-spacepad_default.hex}
cp $FILE $DIR
cd $DIR
python3 uf2conv.py $FILE -c -f 0xADA52840
