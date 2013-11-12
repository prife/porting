//for frequencies
#include <ps7_init.h>
#include <uart_hw.h>

void UartEnable(UART_Registers* uart)
{
	uint32_t tmp = uart->CR;
	tmp &= ~UART_CR_EN_DIS_MASK;
	tmp |= (UART_CR_TX_EN | UART_CR_RX_EN);

	uart->CR = tmp;
}

void UartDisable(UART_Registers* uart)
{
	uint32_t tmp = uart->CR;
	tmp &= ~UART_CR_EN_DIS_MASK;
	tmp |= (UART_CR_TX_DIS | UART_CR_RX_DIS);
	uart->CR = tmp;
}

void UartSetBaudrate(UART_Registers* uart, uint32_t baudrate)
{
    uint8_t uartBaudrateDivider;
	uint32_t uartInputClock = UART_FREQ;
	//uint32_t uartMaxErrorRate = 3;

	uint32_t uartBGGR = 0;
	uint32_t uartResultingBaudrate = 0;
	uint32_t uartBaudError = 0;

	uint32_t uartBestError = 0xFFFFFFFF;
	uint32_t uartBestBGGR = 0;
	uint32_t uartBestDivider = 0;

	//check if input clock is divided by 8
	if(uart->MR & UART_MR_CLKSEL)
		uartInputClock /= 8;

	for(uartBaudrateDivider = 3; uartBaudrateDivider < 255; uartBaudrateDivider++)
	{
		uartBGGR = uartInputClock / (baudrate * (uartBaudrateDivider + 1));
		uartResultingBaudrate = uartInputClock / (uartBGGR * (uartBaudrateDivider + 1));

		if(baudrate > uartResultingBaudrate)
			uartBaudError = baudrate - uartResultingBaudrate;
		else
			uartBaudError = uartResultingBaudrate - baudrate;

		if(uartBestError > uartBaudError)
		{
			uartBestBGGR = uartBGGR;
			uartBestDivider = uartBaudrateDivider;
			uartBestError = uartBaudError;
		}
	}

	//TODO: check if error is too big and bail

	//disable uart
	UartDisable(uart);

	uart->BAUDGEN = uartBestBGGR;
	uart->BAUDDIV = uartBestDivider;

	//reenable uart
	UartEnable(uart);
}

void UartInitialize(UART_Registers* uart, uint32_t baudrate)
{
	UartSetBaudrate(uart, baudrate);

	uint32_t modeRegister = uart->MR;
	modeRegister &= ~(UART_MR_CHARLEN_MASK |
					 UART_MR_STOPMODE_MASK |
					 UART_MR_PARITY_MASK);
	modeRegister |= (UART_MR_CHARLEN_8_BIT |
					UART_MR_STOPMODE_1_BIT |
					UART_MR_PARITY_NONE);
	uart->MR = modeRegister;

	//set tx fifo trigger level to 8
	uart->TXWM = 8;
	uart->RXWM = 1;

	//disable all interrupts
	//uart->IDR = UART_IXR_MASK;

    //enable intterrupt!
    //uart->IER = UART_IXR_RTRIG | UART_IXR_RFUL;
    uart->IER = UART_IXR_TXEMPTY | UART_IXR_RXEMPTY | UART_IXR_RXOVR| UART_IXR_OVER | UART_IXR_RXFULL;

	//uart->CR = (UART_CR_TX_EN | UART_CR_RX_EN | UART_CR_TXRST | UART_CR_RXRST);
}

