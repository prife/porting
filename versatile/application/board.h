/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-10-08     Bernard      add board.h to this bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <versatile.h>

/*
 * Memory Map
 * 
 * 0x00000000 - 0x03FFFFFF : MPMC Chip Select 0, SDRAM 64M
 * 0x04000000 - 0x07FFFFFF : MPMC Chip Select 0, SDRAM 64M
 */

void rt_hw_board_init(void);

#endif
