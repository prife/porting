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

#define ZED_UART_INT_DISABLE(UART) (UART->IER &= ~(UART_IXR_RXOVR | UART_IXR_RXFULL))
#define ZED_UART_INT_ENABLE(UART) (UART->IER |= (UART_IXR_RXOVR | UART_IXR_RXFULL))

struct hw_uart_device
{
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
};

#define UART_TxRxFIFO0(base) __REG32(base + 0x30)

#define UART_DR(base)   __REG32(base + 0x00)
#define UART_FR(base)   __REG32(base + 0x18)
#define UART_CR(base)   __REG32(base + 0x30)
#define UART_IMSC(base) __REG32(base + 0x38)
#define UART_ICR(base)  __REG32(base + 0x44)

#define UARTFR_RXFE     0x10
#define UARTFR_TXFF     0x20
#define UARTIMSC_RXIM   0x10
#define UARTIMSC_TXIM   0x20
#define UARTICR_RXIC    0x10
#define UARTICR_TXIC    0x20

/*
* Initiate UART1  ( /dev/ttyACM0 on host computer )
*   115,200 Baud 8-bit No-Parity 1-stop-bit
*/
#if 0
void init_uart1_RxTx_115200_8N1()
{
    /* Disable the transmitter and receiver before writing to the Baud Rate Generator */
    UART1->control_reg0=0;

    /* Set Baudrate to 115,200 Baud */
    UART1->baud_rate_divider =XUARTPS_BDIV_CD_115200;
    UART1->baud_rate_gen=     XUARTPS_BRGR_CD_115200;

    /*Set 8-bit NoParity 1-StopBit*/
    UART1->mode_reg0   =  XUARTPS_MR_PAR_NONE;

    /* enable interrupt! */
    UART1->Rcvr_FIFO_trigger_level0 = 1;
    UART1->intrpt_en_reg0 = UART_IXR_RTRIG | UART_IXR_RFUL;
    rt_kprintf("reg:0x%x, write:0x%x\n",  UART1->intrpt_en_reg0, UART_IXR_RTRIG | UART_IXR_RFUL);
    //UART1->Tx_FIFO_trigger_level = ?

    /*Enable Rx & Tx*/
    UART1->control_reg0=  XUARTPS_CR_TXEN | XUARTPS_CR_RXEN | XUARTPS_CR_TXRES | XUARTPS_CR_RXRES ;
}

void sendUART1char(char s)
{
    /*Make sure that the uart is ready for new char's before continuing*/
    while ((( UART1->channel_sts_reg0 ) & UART_STS_TXFULL) > 0) ;

    /* Loop until end of string */
    UART1->tx_rx_fifo= (unsigned int) s; /* Transmit char */
}
#endif

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
        ZED_UART_INT_DISABLE(UART1);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        ZED_UART_INT_ENABLE(UART1);
        rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, serial, "uart");
        rt_hw_interrupt_umask(uart->irqno);
        break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

#if 0
    /*Make sure that the uart is ready for new char's before continuing*/
    //while (UART_FR(uart->hw_base) & UARTFR_TXFF);
    while (( UART1->channel_sts_reg0 ) & UART_STS_TXFULL) ;

    /* Loop until end of string */
    //UART_TxRxFIFO0(uart->hw_base) = c;
	UART1->tx_rx_fifo= c;
#else
    /*Make sure that the uart is ready for new char's before continuing*/
    while ((UART1->SR) & UART_SR_TXFULL) ;
	UART1->FIFO= c;

#endif

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

#if 0
    ch = -1;

    if (UART1->chnl_int_sts_reg0 & UART_IXR_RTRIG)
    {
        ch = UART1->tx_rx_fifo & 0xff;
        //FIXME:write 1 to clear?!!
        UART1->chnl_int_sts_reg0 = (UART_IXR_RTRIG | UART_IXR_RFUL);
    }
#else
    ch = -1;

    if (UART1->ISR & UART_SR_RXOVR)
    {
        ch = UART1->FIFO & 0xff;
        //FIXME:write 1 to clear?!!
        UART1->ISR = (UART_IXR_RXOVR | UART_IXR_RXFULL);
    }

#endif
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
    ZED_UART1_BASE,
    IRQ_ZED_UART1,
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

    /* register UART1 device */
    rt_hw_serial_register(&_serial, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          uart);
    /* enable Rx and Tx of UART */
    //UART_CR(uart->hw_base) = (1 << 0) | (1 << 8) | (1 << 9);
    //init_uart1_RxTx_115200_8N1();
    UartInitialize(UART1, 115200);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

