/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2007-11-20     Yi.Qiu		add rtgui application
 */

#include <rtthread.h>
#include <components.h>

void second_task(void *param)
{
	int counter = 0;

	while (1)
	{
		rt_thread_delay(RT_TICK_PER_SECOND);
		rt_kprintf("counter = %d\n", counter ++);
	}
}

void rt_init_thread_entry(void *parameter)
{
	rt_components_init();
}

int rt_application_init(void)
{
	rt_thread_t tid;

	tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL,
		2048, RT_THREAD_PRIORITY_MAX/3, 20);
	if (tid != RT_NULL) rt_thread_startup(tid);

#if 0
	tid = rt_thread_create("second", second_task, RT_NULL,
		1024, 20, 20);
	if (tid != RT_NULL) rt_thread_startup(tid);
#endif

	return 0;
}
