#!/bin/sh

git clone https://github.com/RT-Thread/rt-thread.git

cd toolchains
sh toolchains.sh
chmod a+x scons-2.3.0/script/scons
export PATH=`pwd`/arm-2012.09/bin:`pwd`/mips-2012.09/bin:`pwd`/scons-2.3.0/script:$PATH
cd ..

export RTT_ROOT=`pwd`/rt-thread
export RTT_CC=gcc
export RTT_EXEC_PATH=`pwd`/toolchains/arm-2012.09/bin
