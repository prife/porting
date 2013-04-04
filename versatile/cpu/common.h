#ifndef __COMMON_H__
#define __COMMON_H__

#include <rtdef.h>

/*****************************/
/* CPU Mode                  */
/*****************************/
#define USERMODE		0x10
#define FIQMODE			0x11
#define IRQMODE			0x12
#define SVCMODE			0x13
#define ABORTMODE		0x17
#define UNDEFMODE		0x1b
#define MODEMASK		0x1f
#define NOINT			0xc0

struct rt_hw_register
{
	rt_uint32_t r0;
	rt_uint32_t r1;
	rt_uint32_t r2;
	rt_uint32_t r3;
	rt_uint32_t r4;
	rt_uint32_t r5;
	rt_uint32_t r6;
	rt_uint32_t r7;
	rt_uint32_t r8;
	rt_uint32_t r9;
	rt_uint32_t r10;
	rt_uint32_t fp;
	rt_uint32_t ip;
	rt_uint32_t sp;
	rt_uint32_t lr;
	rt_uint32_t pc;
	rt_uint32_t cpsr;
	rt_uint32_t ORIG_r0;
};

#endif
