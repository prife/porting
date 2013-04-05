#!/bin/sh

git clone https://github.com/RT-Thread/rt-thread.git

cd toolchains
sh toolchains.sh
export PATH=`pwd`/arm-2012.09/bin:`pwd`/mips-2012.09/bin:$PATH
cd ..

export RTT_ROOT=`pwd`/rt-thread
export RTT_CC=gcc
