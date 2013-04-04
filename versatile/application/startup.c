/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-02-26     Bernard      first implementation
 * 2006-05-05     Bernard      add two test thread
 * 2006-08-10     Bernard      use rt_show_version to display version information
 * 2008-07-14     Bernard      modify the heap memory init parameter
 */

#include <rthw.h>
#include "board.h"

extern void rt_hw_interrupt_init(void);
extern void rt_application_init(void);

/**
 * @addtogroup mini2440
 */

/*@{*/
#if defined(__CC_ARM)
	extern int Image$$ER_ZI$$ZI$$Base;
	extern int Image$$ER_ZI$$ZI$$Length;
	extern int Image$$ER_ZI$$ZI$$Limit;
#elif (defined (__GNUC__))
	rt_uint8_t _irq_stack_start[1024];
	rt_uint8_t _fiq_stack_start[1024];
	rt_uint8_t _undefined_stack_start[512];
	rt_uint8_t _abort_stack_start[512];
	rt_uint8_t _svc_stack_start[4096] SECTION(".nobss");
	extern unsigned char __bss_start;
	extern unsigned char __bss_end;
#endif

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* enable cpu cache */
	rt_hw_cpu_icache_enable();
	rt_hw_cpu_dcache_enable();

	/* init hardware interrupt */
	rt_hw_interrupt_init();

	/* init board */
	rt_hw_board_init();

	/* show version */
	rt_show_version();

	/* init timer system */
	rt_system_timer_init();

	/* init heap memory system */
#ifdef __CC_ARM
	rt_system_heap_init((void*)&Image$$ER_ZI$$ZI$$Limit, (void*)0x03FFFFFF);
#else
	rt_system_heap_init((void*)&__bss_end, (void*)0x03FFFFFF);
#endif

#ifdef RT_USING_MODULE
	/* init module system*/
	rt_system_module_init();
#endif

	/* init scheduler system */
	rt_system_scheduler_init();

	/* init application */
	rt_application_init();

	rt_system_timer_thread_init();

	/* init idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */
	return ;
}

int main(void)
{
	/* disable interrupt first */
	rt_hw_interrupt_disable();

	/* startup RT-Thread RTOS */
	rtthread_startup();

	return 0;
}

