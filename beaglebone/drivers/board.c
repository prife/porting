/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-20     Bernard    the first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"

/**
 * @addtogroup BeagleBone
 */
/*@{*/

void rt_timer_handler(int vector)
{
	rt_tick_increase();
}

/**
 * This function will initialize beaglebone board
 */
void rt_hw_board_init()
{
#if defined(RT_USING_DEVICE) && defined(RT_USING_UART1)
	rt_hw_serial_init();
	rt_console_set_device("uart1");
#endif

	rt_hw_interrupt_install(TIMER0_INT, rt_timer_handler, RT_NULL);	
	rt_hw_interrupt_umask(TIMER0_INT);
}

/*@}*/
