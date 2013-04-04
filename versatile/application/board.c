/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-04-02     Bernard      first implementation
 */

#include <rthw.h>

#include "board.h"
#include <uart.h>
#include <string.h>

extern void rt_hw_mmu_init(void);

#define __clk                   1000000
#define OS_TICK_BASE			VERSATILE_TIMER0_1_BASE

#define TIMER_LOAD(base)          __REG32(base + 0x00)
#define TIMER_VALUE(base)         __REG32(base + 0x04)
#define TIMER_CTRL(base)          __REG32(base + 0x08)
#define TIMER_INTCTRL(base)       __REG32(base + 0x0c)
#define TIMER_RIS(base)           __REG32(base + 0x10)
#define TIMER_MIS(base)           __REG32(base + 0x14)
#define TIMER_BGLOAD(base)        __REG32(base + 0x18)

/**
 * This function will handle rtos timer
 */
static void rt_timer_handler(int vector, void* param)
{
	rt_tick_increase();

	/* clear interrupt */
	TIMER_INTCTRL(OS_TICK_BASE) = 0;
}

/**
 * This function will initialize timer for system ticks
 */
static  void rt_hw_timer_init()
 {
	/* We need to disable timer before writing new values */
	TIMER_CTRL(OS_TICK_BASE) = 0;

	/* Setup timer1 in periodic mode */
	TIMER_BGLOAD(OS_TICK_BASE) = 0;
	TIMER_LOAD(OS_TICK_BASE) = (__clk/RT_TICK_PER_SECOND) * 10;

	rt_hw_interrupt_install(INT_TIMERINT0_1, rt_timer_handler, RT_NULL, "tick");	
	rt_hw_interrupt_umask(INT_TIMERINT0_1);

	/* enable timer, configure as Periodic, div1, interrupt enable */
	TIMER_CTRL(OS_TICK_BASE) = 0xe2;
}

/**
 * This function will initailize board.
 */
void rt_hw_board_init()
{
	/* initialize uart */
	rt_hw_uart_init();
	rt_console_set_device("uart");

	/* initialize mmu */
	// rt_hw_mmu_init();

	/* initialize timer4 */
	rt_hw_timer_init();
}
