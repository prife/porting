/*
 *  User Applications 
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

	finsh_set_device(RT_CONSOLE_DEVICE_NAME);
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
