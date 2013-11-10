#!/bin/bash

~/work/Zed/zynq_linux/arm-softmmu/qemu-system-arm -M xilinx-zynq-a9 -serial null -serial mon:stdio -nographic -kernel rtthread-realview.elf
