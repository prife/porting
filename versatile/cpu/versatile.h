/*
 *  ARM ARM926EJ-S verstatile PB definitions
 *
 * COPYRIGHT (C) 2013, Shanghai Real-Thread Technology Co., Ltd
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion
 */

#ifndef __VERSATILE_H__
#define __VERSATILE_H__

#define __REG8(x) 	(*((volatile unsigned char*)(x)))
#define __REG16(x) 	(*((volatile unsigned short*)(x)))
#define __REG32(x)	(*((volatile unsigned long *)(x)))

#define VERSATILE_SCTL_BASE				0x101E0000	/* System controller */

#define VERSATILE_VIC_BASE             	0x10140000	/* Vectored interrupt controller */
#define VERSATILE_SIC_BASE             	0x10003000	/* Secondary interrupt controller */

#define VERSATILE_TIMER0_1_BASE        	0x101E2000	/* Timer 0 and 1 */
#define VERSATILE_TIMER2_3_BASE        	0x101E3000	/* Timer 2 and 3 */

#define VERSATILE_UART0_BASE           	0x101F1000	/* Uart 0 */
#define VERSATILE_UART1_BASE           	0x101F2000	/* Uart 1 */
#define VERSATILE_UART2_BASE           	0x101F3000	/* Uart 2 */
#define VERSATILE_UART3_BASE           	0x10009000	/* UART 3 */

#define INT_WDOGINT                     0	/* Watchdog timer */
#define INT_SOFTINT                     1	/* Software interrupt */
#define INT_COMMRx                      2	/* Debug Comm Rx interrupt */
#define INT_COMMTx                      3	/* Debug Comm Tx interrupt */
#define INT_TIMERINT0_1                 4	/* Timer 0 and 1 */
#define INT_TIMERINT2_3                 5	/* Timer 2 and 3 */
#define INT_GPIOINT0                    6	/* GPIO 0 */
#define INT_GPIOINT1                    7	/* GPIO 1 */
#define INT_GPIOINT2                    8	/* GPIO 2 */
#define INT_GPIOINT3                    9	/* GPIO 3 */
#define INT_RTCINT                      10	/* Real Time Clock */
#define INT_SSPINT                      11	/* Synchronous Serial Port */
#define INT_UARTINT0                    12	/* UART 0 on development chip */
#define INT_UARTINT1                    13	/* UART 1 on development chip */
#define INT_UARTINT2                    14	/* UART 2 on development chip */
#define INT_SCIINT                      15	/* Smart Card Interface */
#define INT_CLCDINT                     16	/* CLCD controller */
#define INT_DMAINT                      17	/* DMA controller */
#define INT_PWRFAILINT                  18	/* Power failure */
#define INT_MBXINT                      19	/* Graphics processor */
#define INT_GNDINT                      20	/* Reserved */
	/* External interrupt signals from logic tiles or secondary controller */
#define INT_VICSOURCE21                 21	/* Disk on Chip */
#define INT_VICSOURCE22                 22	/* MCI0A */
#define INT_VICSOURCE23                 23	/* MCI1A */
#define INT_VICSOURCE24                 24	/* AACI */
#define INT_VICSOURCE25                 25	/* Ethernet */
#define INT_VICSOURCE26                 26	/* USB */
#define INT_VICSOURCE27                 27	/* PCI 0 */
#define INT_VICSOURCE28                 28	/* PCI 1 */
#define INT_VICSOURCE29                 29	/* PCI 2 */
#define INT_VICSOURCE30                 30	/* PCI 3 */
#define INT_VICSOURCE31                 31	/* SIC source */

#define VERSATILE_SC_VALID_INT          0x003FFFFF

/* interrupt definitions */
#define IRQ_STATUS(base)		__REG32(base + 0x000)
#define FIQ_STATUS(base)		__REG32(base + 0x004)
#define RAW_INTR(base)			__REG32(base + 0x008)
#define INT_SELECT(base)		__REG32(base + 0x00c)
#define INT_ENABLE(base)		__REG32(base + 0x010)
#define INT_CLEAR(base)			__REG32(base + 0x014)
#define SOFT_INT(base)			__REG32(base + 0x018)
#define SOFT_INT_CLEAR(base)	__REG32(base + 0x01c)
#define PROTECTION(base)		__REG32(base + 0x020)
#define VECT_ADDR(base)			__REG32(base + 0x030)
#define DEF_VECT_ADDR(base)		__REG32(base + 0x034)

#define MAXIRQNUM                       31
#define MAXFIQNUM                       31
#define MAXSWINUM                       31

#include "common.h"

#endif

