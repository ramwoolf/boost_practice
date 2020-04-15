#!/usr/bin/bash

ENV_SH=env.sh
if [[ -f $ENV_SH && -x $ENV_SH ]]
then ./$ENV_SH
else echo WARNING: \$ENV_SH is not found\! Global environment is used.
fi

BUILD_DIR_PREF=build
TEST_ENABLE=OFF

if [[ $3 = "test" ]]
then TEST_ENABLE=ON
fi

TARGET="ALL"
SRC="src/"

if [[ $2 != "" ]]
then TARGET=$2
fi

BUILD_TYPE=release
if [[ $1 = "debug" ]]
then BUILD_TYPE=debug
fi

BUILD_DIR="${BUILD_DIR_PREF}_gcc_${BUILD_TYPE}"

if ! [[ -d $BUILD_DIR ]] 
then mkdir $BUILD_DIR
fi

cd $BUILD_DIR
echo Clean solution: $BUILD_DIR
rm -r ./* > /dev/null

echo "Start cmake"
cmake .. -G "Unix Makefiles" -DWANTED=$TARGET -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_SH="CMAKE_SH-NOTFOUND" -DTEST_ENABLE=$TEST_ENABLE
make -j4 && make -j4 install
cd ../