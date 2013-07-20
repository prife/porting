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
 * 2013-07-06     Bernard      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "realview.h"

#define MAX_HANDLERS				NR_IRQS_PBA8

extern volatile rt_uint8_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

static void rt_hw_interrupt_handle(int vector, void *param)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

extern void rt_cpu_vector_set_base(rt_uint32_t addr);
extern int system_vectors;

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
	register rt_uint32_t idx;
    unsigned int *vectors_base =  (unsigned int *)&system_vectors;

	/* set vector table */
	rt_cpu_vector_set_base((rt_uint32_t)vectors_base);

	GIC_DIST_CTRL = 0x00;
	/* disable CPU interrupt */
	GIC_CPU_CTRL = 0x00;

    /* init exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));
    for(idx=0; idx < MAX_HANDLERS; idx++)
    {
        isr_table[idx].handler = rt_hw_interrupt_handle;
    }

    /* disable all interrupt */
	for (idx = 0; idx < MAX_HANDLERS; idx ++)
	{
		GIC_DIST_CONFIG(idx) = 0x00;
		GIC_DIST_TARGET(idx) = 0xa0a0a0a0;
		GIC_DIST_ENABLE_CLEAR(idx) = 0xffffffff;
	}

	/* interrupts are enable for this CPU */
	GIC_DIST_CTRL = 0x01;
	GIC_CPU_PRIMASK = 0xf0;

	/* enable CPU interrupt */
	GIC_CPU_CTRL = 0x01;

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
	GIC_DIST_ENABLE_SET(vector) = 0x1 << (vector % 32);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
	GIC_DIST_ENABLE_CLEAR(vector) = 0x1 << (vector % 32);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
                                        void *param, char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if(vector < MAX_HANDLERS)
    {
        old_handler = isr_table[vector].handler;

        if (handler != RT_NULL)
        {
#ifdef RT_USING_INTERRUPT_INFO
		    rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
		    isr_table[vector].handler = handler;
            isr_table[vector].param = param;
        }
    }

    return old_handler;
}

