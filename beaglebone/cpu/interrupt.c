/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-20     Bernard      first version
 */

#include <rtthread.h>
#include "am33xx.h"

#define MAX_HANDLERS	128

extern rt_uint32_t rt_interrupt_nest;

/* exception and interrupt handler table */
rt_isr_handler_t isr_table[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * @addtogroup AM33xx
 */
/*@{*/

rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
	return RT_NULL;
}

static void rt_hw_vector_copy(void)
{
	void *dst, *src;

	extern volatile rt_uint32_t Entry_Point;

	dst = (void*) (0xffff0000);
	src = (void*) (&Entry_Point);

	/* copy vector to 0xffff 0000 */
	rt_memcpy(dst, src, 64);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
	register rt_uint32_t idx;

	/* copy vector table */
	rt_hw_vector_copy();
	
	/* initialize exceptions table */
	for(idx=0; idx < MAX_HANDLERS; idx++)
	{
		isr_table[idx] = (rt_isr_handler_t)rt_hw_interrupt_handle;
	}

    /* disable all interrupt */
    for(idx = 0; idx < 4; idx ++)
    {
        AINTC->ECR[idx] = 0xffffffff;
    }

	/* initialize interrupt channel mapping */
	{
		volatile rt_uint32_t *cmp;
		
		cmp = (volatile rt_uint32_t *)(0xFFFEE400);
		for (idx = 0; idx < 26; idx ++)
		{
			*cmp = 0x10101010;
			cmp ++;
		}
	}

    /* no priority holing mode and no nesting mode */
    AINTC->CR = 0;
    /* enable IRQ */
    AINTC->HIER = 0x03;
	/* set as IRQ for INDEX interrupt */
	AINTC->HIEISR = 0x01;
    /* enable global interrupt */
    AINTC->GER = 0x01;
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
    AINTC->EICR = vector & 0x7f;
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
	AINTC->EISR = vector & 0x7f;
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
void rt_hw_interrupt_install(int vector, rt_isr_handler_t new_handler, rt_isr_handler_t *old_handler)
{
	if(vector < MAX_HANDLERS)
	{
		if (old_handler != RT_NULL) *old_handler = isr_table[vector];
		if (new_handler != RT_NULL) isr_table[vector] = new_handler;
	}
}

/*@}*/
