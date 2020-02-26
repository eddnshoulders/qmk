@echo off

cd %~dp0

bash -c "cd ../../ && export NRFSDK15_ROOT=/c/users/f402n/documents/NordicNRF5/libs/nRF5_SDK_15.0.0_a53641a && make spacemouse" || exit
