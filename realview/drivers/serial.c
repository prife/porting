/*
 *  serial.c UART driver
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

#include <rthw.h>
#include <rtdevice.h>

#include "serial.h"
#include "uart_hw.h"

#define BOARD_UART UART1
#define BOARD_UART_BASE   ZED_UART1_BASE
#define BOARD_UART_IRQ    IRQ_ZED_UART1

#define ZED_UART_INT_DISABLE(UART)       \
    (UART->IER &= ~(UART_IXR_RXOVR | UART_IXR_RXFULL))
#define ZED_UART_INT_ENABLE(UART)        \
    (UART->IER |= (UART_IXR_RXOVR | UART_IXR_RXFULL))

#define ZED_UART_SENDCHAR(UART, ch)           \
    do {                                      \
        while ((UART->SR) & UART_SR_TXFULL) ; \
        UART->FIFO= ch;                       \
    }while(0)

#define ZED_UART_GETCHAR(UART, ch)                         \
    do {                                                   \
        if (UART->ISR & UART_SR_RXOVR)                     \
        {                                                  \
            ch = UART->FIFO & 0xff;                        \
            UART->ISR = (UART_IXR_RXOVR | UART_IXR_RXFULL);\
        }                                                  \
    } while(0)

struct hw_uart_device
{
    UART_Registers * uart;
    rt_uint32_t irqno;
};

/* RT-Thread UART interface */

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        ZED_UART_INT_DISABLE(BOARD_UART);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        ZED_UART_INT_ENABLE(BOARD_UART);
        rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, serial, "uart");
        rt_hw_interrupt_umask(uart->irqno);
        break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct hw_uart_device *dev;

    RT_ASSERT(serial != RT_NULL);
    dev = (struct hw_uart_device *)serial->parent.user_data;

    /*Make sure that the uart is ready for new char's before continuing*/
    ZED_UART_SENDCHAR(dev->uart, c);
    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *dev;

    RT_ASSERT(serial != RT_NULL);
    dev = (struct hw_uart_device *)serial->parent.user_data;

    ch = -1;

    ZED_UART_GETCHAR(dev->uart, ch);
    return ch;
}

static const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};

/* UART device driver structure */
static struct serial_ringbuffer _uart_int_rx;
static struct hw_uart_device _uart_device =
{
    BOARD_UART_BASE,
    BOARD_UART_IRQ,
};
static struct rt_serial_device _serial;

int rt_hw_uart_init(void)
{
    struct hw_uart_device *uart;
    struct serial_configure config;

    uart = &_uart_device;
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;

    _serial.ops    = &_uart_ops;
    _serial.int_rx = &_uart_int_rx;
    _serial.config = config;

    /* register uart device */
    rt_hw_serial_register(&_serial, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          uart);

    /* enable Rx and Tx of uart */
    UartInitialize(BOARD_UART, 115200);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

