/*
 * File      : trap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-13     Bernard      first version
 */

#include <rthw.h>
#include <board.h>

#define MAX_HANDLERS	32

extern rt_uint32_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * @addtogroup S3C24X0
 */
/*@{*/

void rt_hw_interrupt_handler(rt_uint32_t vector, void* param)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
	register rt_uint32_t idx;

	/* init exceptions table */
	for(idx=0; idx < MAX_HANDLERS; idx++)
	{
		isr_table[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handler;
		isr_table[idx].param = RT_NULL;
	}

	/* init interrupt nest, and context in thread sp */
	rt_interrupt_nest = 0;
	rt_interrupt_from_thread = 0;
	rt_interrupt_to_thread = 0;
	rt_thread_switch_interrupt_flag = 0;
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
	INT_CLEAR(VERSATILE_VIC_BASE) = 1 << vector;
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
	INT_ENABLE(VERSATILE_VIC_BASE) = 1 << vector;
}


/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param handler the interrupt service routine to be installed
 * @param param the parameter for interrupt service routine
 * @name unused.
 *
 * @return the old handler
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler, 
									void *param, char *name)
{
	rt_isr_handler_t old_handler = RT_NULL;

	if(vector >= 0 && vector < MAX_HANDLERS)
	{
		old_handler = isr_table[vector].handler;
		if (handler != RT_NULL)
		{
			isr_table[vector].handler = handler;
			isr_table[vector].param = param;
		}
	}

	return old_handler;
}

/*@}*/
