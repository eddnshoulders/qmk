@echooff

%DIR = bash -c "pwd"

bash -c "cd ../../ && export NRFSDK15_ROOT=/mnt/c/users/f402n/documents/NordicNRF5/libs/nRF5_SDK_15.0.0_a53641a && make spacepad" || exit

cd ../../.build

set file=spacepad_default.hex

%DIR/uf2conv.py %file% -c -f 0xADA52840

echo Waiting for the UF2 drive. Press Reset twice...

:loop
if not exist d:\ goto :loop

timeout 1

copy flash.uf2 d:\

