#!/bin/bash

~/work/Zed/zynq_linux/arm-softmmu/qemu-system-arm -s -S -M xilinx-zynq-a9 -serial null -serial mon:stdio -nographic -kernel rtthread-realview.elf -gdb tcp::1234
