#include"TM4C123GH6PM.h"
#define SYSTEM_CLOCK_RATE 16000000 // 16 mhz WHERE SUPPORTED RANGE BY PLL IS [5-25] MHZ
void uartInitM0(uint32_t baudrate)// PA0 = U0RX, PA1 = U0TX
{
	//--------------DECLARATIONS	----------------------
	char FREQ_DIV;
	uint16_t intbaud;
	float  fbaud;
	//--------------END DECLARATIONS-----------------------
	SYSCTL	->	RCGCUART	|=0X01;
	SYSCTL	->	RCGCGPIO	|=0X01;
	UART0	->	CC		 =0X00;					// TO USE SYSTEM CLK NOT PIOSC
	GPIOA	->	DEN		|=0X03;
	GPIOA	->	AFSEL		|=0X03;
	GPIOA   ->	PCTL		|=0X11;
	GPIOA	->	DIR		|=0X02;
	UART0	->	CTL		 =0X00;
	//--------------FOR BAUDRATE CALC AND SET----------------------------
	FREQ_DIV = ((UART0->CTL&0X20)==0X00)?16:8;
	intbaud=SYSTEM_CLOCK_RATE/(FREQ_DIV*baudrate);
	fbaud=(SYSTEM_CLOCK_RATE/(FREQ_DIV*baudrate*1.0)-intbaud)*64+0.5;
	UART0->IBRD=intbaud;
	UART0->FBRD=fbaud;
	//--------------END BAUDRATE CALC AND SET----------------------------
	UART0	->	LCRH		|=0X60;			// <===== no fifo is used
	UART0	->	CTL		|=0X301;
}
void uartInitM1(uint32_t baudrate)// PB0 = U1RX, PB1 = U1TX
{
	//--------------DECLARATIONS	-----------------------
	char FREQ_DIV;
	uint16_t intbaud;
	float  fbaud;
	//--------------END DECLARATIONS-----------------------
	SYSCTL	->	RCGCUART	|=0X02;
	SYSCTL	->	RCGCGPIO	|=0X02;
	UART1	->	CC		 =0X00;					// TO USE SYSTEM CLK NOT PIOSC
	GPIOB	->	DEN		|=0X03;
	GPIOB	->	AFSEL		|=0X03;
	GPIOB   ->	PCTL		|=0X11;
	GPIOB	->	DIR		|=0X02;
	UART1	->	CTL		 =0X00;
	//--------------FOR BAUDRATE CALC AND SET----------------------------
	FREQ_DIV = ((UART1->CTL&0X20)==0X00)?16:8;
	intbaud=SYSTEM_CLOCK_RATE/(FREQ_DIV*baudrate);
	fbaud=(SYSTEM_CLOCK_RATE/(FREQ_DIV*baudrate*1.0)-intbaud)*64+0.5;
	UART1->IBRD=intbaud;
	UART1->FBRD=fbaud;
	//--------------END BAUDRATE CALC AND SET----------------------------
	UART1	->	LCRH		|=0X60;
	UART1	->	CTL		|=0X301;
}
void uartInitM4(uint32_t baudrate)	// PC4 = U4RX, PC5 = U4TX
{
	//--------------DECLARATIONS	-----------------------
	char FREQ_DIV;
	uint16_t intbaud;
	float  fbaud;
	//--------------END DECLARATIONS-----------------------
	SYSCTL	->	RCGCUART	|=0X08;
	SYSCTL	->	RCGCGPIO	|=0X04;
	UART4	->	CC		 =0X00;					// TO USE SYSTEM CLK NOT PIOSC
	GPIOC	->	DEN		|=0X30;
	GPIOC	->	AFSEL		|=0X30;
	GPIOC 	->	PCTL		|=0X110000;
	GPIOC	->	DIR		|=0X20;
	UART4	->	CTL		 =0X00;
	//--------------FOR BAUDRATE CALC AND SET----------------------------
	FREQ_DIV = ((UART4->CTL&0X20)==0X00)?16:8;
	intbaud=SYSTEM_CLOCK_RATE/(FREQ_DIV*baudrate);
	fbaud=(SYSTEM_CLOCK_RATE/(FREQ_DIV*baudrate*1.0)-intbaud)*64+0.5;
	UART4->IBRD=intbaud;
	UART4->FBRD=fbaud;
	//--------------END BAUDRATE CALC AND SET----------------------------
	UART4	->	LCRH		|=0X60;
	UART4	->	CTL		|=0X301;
}
void uartInitM3(uint32_t baudrate)	// PC6 = U3RX, PC7 = U3TX
{
	//--------------DECLARATIONS	-----------------------
	char FREQ_DIV;
	uint16_t intbaud;
	float  fbaud;
	//--------------END DECLARATIONS-----------------------
	SYSCTL	->	RCGCUART	|=0X04;
	SYSCTL	->	RCGCGPIO	|=0X04;
	UART3	->	CC		 =0X00;					// TO USE SYSTEM CLK NOT PIOSC
	GPIOC	->	DEN		|=0XC0;
	GPIOC	->	AFSEL		|=0XC0;
	GPIOC 	->	PCTL		|=0X11000000;
	GPIOC	->	DIR		|=0X80;
	UART3	->	CTL		 =0X00;
	//--------------FOR BAUDRATE CALC AND SET----------------------------
	FREQ_DIV = ((UART3->CTL&0X20)==0X00)?16:8;
	intbaud=SYSTEM_CLOCK_RATE/(FREQ_DIV*baudrate);
	fbaud=(SYSTEM_CLOCK_RATE/(FREQ_DIV*baudrate*1.0)-intbaud)*64+0.5;
	UART3->IBRD=intbaud;
	UART3->FBRD=fbaud;
	//--------------END BAUDRATE CALC AND SET----------------------------
	UART3	->	LCRH		|=0X60;
	UART3	->	CTL		|=0X301;
}
void uartInterruptInit(uint8_t UARTn)
{
		if     (UARTn==0){UART0->IM|=0X010;NVIC->ISER[0]|=0X020;     __enable_irq();} //<===== ENABLES THE RECIVE INTERRUPT
		else if(UARTn==1){UART1->IM|=0X010;NVIC->ISER[0]|=0X040;     __enable_irq();}
		else if(UARTn==3){UART3->IM|=0X010;NVIC->ISER[1]|=0X08000000;__enable_irq();}
		else if(UARTn==4){UART4->IM|=0X010;NVIC->ISER[1]|=0X10000000;__enable_irq();}
}
