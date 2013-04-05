# !/bin/sh

if [ ! -f "arm-2012.09-63-arm-none-eabi-i686-pc-linux-gnu.tar.bz2" ];then
wget -c https://sourcery.mentor.com/public/gnu_toolchain/arm-none-eabi/arm-2012.09-63-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
tar jxvf arm-2012.09-63-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
fi

if [ ! -f "mips-2012.09-98-mips-sde-elf-i686-pc-linux-gnu.tar.bz2" ];then
wget -c https://sourcery.mentor.com/public/gnu_toolchain/mips-sde-elf/mips-2012.09-98-mips-sde-elf-i686-pc-linux-gnu.tar.bz2
tar jxvf mips-2012.09-98-mips-sde-elf-i686-pc-linux-gnu.tar.bz2
fi
