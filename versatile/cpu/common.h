/*
 *  ARM common defitions.
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

#ifndef __COMMON_H__
#define __COMMON_H__

#include <rtdef.h>

/*****************************/
/* CPU Mode                  */
/*****************************/
#define USERMODE		0x10
#define FIQMODE			0x11
#define IRQMODE			0x12
#define SVCMODE			0x13
#define ABORTMODE		0x17
#define UNDEFMODE		0x1b
#define MODEMASK		0x1f
#define NOINT			0xc0

struct rt_hw_register
{
	rt_uint32_t r0;
	rt_uint32_t r1;
	rt_uint32_t r2;
	rt_uint32_t r3;
	rt_uint32_t r4;
	rt_uint32_t r5;
	rt_uint32_t r6;
	rt_uint32_t r7;
	rt_uint32_t r8;
	rt_uint32_t r9;
	rt_uint32_t r10;
	rt_uint32_t fp;
	rt_uint32_t ip;
	rt_uint32_t sp;
	rt_uint32_t lr;
	rt_uint32_t pc;
	rt_uint32_t cpsr;
	rt_uint32_t ORIG_r0;
};

#endif
