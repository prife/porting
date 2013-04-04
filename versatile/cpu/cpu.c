/*
 *  ARM926EJ-S porting
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

#include <rthw.h>
#include <board.h>

#define ICACHE_MASK	(rt_uint32_t)(1 << 12)
#define DCACHE_MASK	(rt_uint32_t)(1 << 2)

#ifdef __GNUC__
rt_inline rt_uint32_t cp15_rd(void)
{
	rt_uint32_t i;

	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));
	return i;
}

rt_inline void cache_enable(rt_uint32_t bit)
{
	__asm__ __volatile__(			\
		"mrc  p15,0,r0,c1,c0,0\n\t"	\
		"orr  r0,r0,%0\n\t"			\
	   	"mcr  p15,0,r0,c1,c0,0"		\
		:							\
		:"r" (bit)					\
		:"memory");
}

rt_inline void cache_disable(rt_uint32_t bit)
{
	__asm__ __volatile__(			\
		"mrc  p15,0,r0,c1,c0,0\n\t"	\
		"bic  r0,r0,%0\n\t"			\
		"mcr  p15,0,r0,c1,c0,0"		\
		:							\
		:"r" (bit)					\
		:"memory");
}
#endif

#ifdef __CC_ARM
rt_inline rt_uint32_t cp15_rd(void)
{
	rt_uint32_t i;

	__asm
	{
		mrc p15, 0, i, c1, c0, 0
	}

	return i;
}

rt_inline void cache_enable(rt_uint32_t bit)
{
	rt_uint32_t value;

	__asm
	{
		mrc p15, 0, value, c1, c0, 0
		orr value, value, bit
		mcr p15, 0, value, c1, c0, 0
	}
}

rt_inline void cache_disable(rt_uint32_t bit)
{
	rt_uint32_t value;

	__asm
	{
		mrc p15, 0, value, c1, c0, 0
		bic value, value, bit
		mcr p15, 0, value, c1, c0, 0
	}
}
#endif

/**
 * enable I-Cache
 *
 */
void rt_hw_cpu_icache_enable()
{
	cache_enable(ICACHE_MASK);
}

/**
 * disable I-Cache
 *
 */
void rt_hw_cpu_icache_disable()
{
	cache_disable(ICACHE_MASK);
}

/**
 * return the status of I-Cache
 *
 */
rt_base_t rt_hw_cpu_icache_status()
{
	return (cp15_rd() & ICACHE_MASK);
}

/**
 * enable D-Cache
 *
 */
void rt_hw_cpu_dcache_enable()
{
	cache_enable(DCACHE_MASK);
}

/**
 * disable D-Cache
 *
 */
void rt_hw_cpu_dcache_disable()
{
	cache_disable(DCACHE_MASK);
}

/**
 * return the status of D-Cache
 *
 */
rt_base_t rt_hw_cpu_dcache_status()
{
	return (cp15_rd() & DCACHE_MASK);
}

/**
 * reset cpu by dog's time-out
 *
 */
void rt_hw_cpu_reset()
{
	rt_kprintf("reset, un-implementation.\n");
}

/**
 *  shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
	rt_uint32_t level;
	rt_kprintf("shutdown...\n");

	level = rt_hw_interrupt_disable();
	while (level)
	{
		RT_ASSERT(0);
	}
}
