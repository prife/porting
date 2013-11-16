/*
 * File      : application.c
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
#ifdef RT_USING_COMPONENTS_INIT
#include <components.h>
#endif

/* thread phase init */
static void rt_init_thread_entry(void *parameter)
{
    /* do component initialization */
    rt_components_init();

    /* add your initialization here */
}

static void test_task(void *parameter)
{
    int count = 0;

    while (1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND);
        rt_kprintf("count = %d\n", count ++);
    }
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 2048,
                            RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    tid = rt_thread_create("test", test_task, RT_NULL, 512,
                            RT_THREAD_PRIORITY_MAX-2, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

