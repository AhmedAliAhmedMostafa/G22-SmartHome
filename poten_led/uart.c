#include "tm4c123gh6pm_a.h"
#include "TM4C123GH6PM_B.h"
#include "uart.h"
#define SYSTEM_CLOCK_RATE 16000000 

void uartInitM4_BTN(uint32_t baudrate)	// PC4 = U4RX, PC5 = U4TX
{
	//--------------DECLARATIONS	-----------------------
	char FREQ_DIV;
	uint16_t intbaud;
	float  fbaud;
	//--------------END DECLARATIONS-----------------------
	SYSCTL	->	RCGCUART	|=0X10;
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
	UART4	->LCRH	|=0X60;
	UART4	->	CTL		|=0X301;
}
void uartInitM3_ADC(uint32_t baudrate)// PC6 = U3RX, PC7 = U3TX
{
	//--------------DECLARATIONS	-----------------------
	char FREQ_DIV;
	uint16_t intbaud;
	float  fbaud;
	//--------------END DECLARATIONS-----------------------
	SYSCTL	->	RCGCUART	|=0X08;
	SYSCTL	->	RCGCGPIO	|=0X04;
	while((SYSCTL_PRGPIO_R&0x04)==0);
	UART3	->	CC		 =0X00;					// TO USE SYSTEM CLK NOT PIOSC
	GPIOC	->	DEN		|=0X30;
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
	UART3	->	LCRH		|=0X70;
	UART3	->	CTL		|=0X301;
}
void uartInterruptInit(uint8_t UARTn)
{
		if     (UARTn==0){UART0->IM|=0X010;NVIC->ISER[0]|=0X020;     __enable_irq();} //<===== ENABLES THE RECIVE INTERRUPT
		else if(UARTn==1){UART1->IM|=0X010;NVIC->ISER[0]|=0X040;     __enable_irq();}
		else if(UARTn==3){UART3->IM|=0X010;NVIC->ISER[1]|=0X08000000;__enable_irq();}
		else if(UARTn==4){UART4->IM|=0X010;NVIC->ISER[1]|=0X10000000;__enable_irq();}
}
void UART_SEND_BTN(int8_t DATA_TO_SEND)		// BUSY WAIT TRANSMISSON AS DATA SIZE TO BE SENT IS SMALL
{

		while((UART4->FR & 0x20) != 0);
					UART4->DR=DATA_TO_SEND;
}
char UART_RECIEVE_BTN () // <==== BUSY WAIT RECIEVE BUT, NOT RECOMMENDED USED IN CASE UART_HANDLER DOES NOT WORK
{
	char C;
	while((UART4->FR & 0x10) != 0);
	 C = UART4->DR;
		return C;
}
void UART_SEND_ADC(int8_t DATA_TO_SEND)		// BUSY WAIT TRANSMISSON AS DATA SIZE TO BE SENT IS SMALL
{

		while((UART3->FR & 0x20) != 0);
					UART3->DR=DATA_TO_SEND;
}
char UART_RECIEVE_ADC () // <==== BUSY WAIT RECIEVE BUT, NOT RECOMMENDED USED IN CASE UART_HANDLER DOES NOT WORK
{
	char C;
	while((UART3->FR & 0x10) != 0);
	 C = UART3->DR;
		return C;
}
