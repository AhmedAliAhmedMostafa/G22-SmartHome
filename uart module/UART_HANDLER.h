#include"TM4C123GH6PM.h"

int uartRX; // GLOBAL VARIABLE TO WRITE RECIEVED DATA TO
void UART0_Handler(void)		// THIS IS THE UART RECEIVE
{
	//-------------- DECLARATIONS	------------------
	volatile int readback;
	int16_t C;
	//-------------- END DECLARATIONS ----------------
	if (UART0->MIS & 0x0010)					// recieve interrupt
	{
		uartRX = UART0->DR;																//<===== MAY CAUSE HAZARD IF FIFO EXISTS BUT NEEDS TESTING
		/*	CODE TO WRITE THIS DATA TO LCD SHOULD BE HERE	or TAKE THIS DATA TO DRIVE MOTOR	*/
		UART0->ICR|=0X0010;
		readback = UART0->ICR;			
	}
	else
	{
		UART0->ICR|=0X0010;
		readback = UART0->ICR;
	}
}
void UART1_Handler(void)		// THIS IS THE UART RECEIVE
{
	//-------------- DECLARATIONS	------------------
	volatile int readback;
	int16_t C;
	//-------------- END DECLARATIONS ----------------
	if (UART1->MIS & 0x0010)						// recieve interrupt
	{
		uartRX = UART1->DR;
		/*	CODE TO WRITE THIS DATA TO LCD SHOULD BE HERE	or TAKE THIS DATA TO DRIVE MOTOR	*/
		UART1->ICR|=0X0010;
		readback = UART1->ICR;			
	}
	else
	{
		UART1->ICR|=0X0010;
		readback = UART1->ICR;
	}
}
void UART3_Handler(void)		// THIS IS THE UART RECEIVE
{
	//-------------- DECLARATIONS	------------------
	volatile int readback;
	int16_t C;
	//-------------- END DECLARATIONS ----------------
	if (UART3->MIS & 0x0010)					// recieve interrupt
	{
		uartRX = UART3->DR;
		/*	CODE TO WRITE THIS DATA TO LCD SHOULD BE HERE	or TAKE THIS DATA TO DRIVE MOTOR	*/
		UART3->ICR|=0X0010;
		readback = UART3->ICR;			
	}
	else
	{
		UART3->ICR|=0X0010;
		readback = UART3->ICR;
	}
}
void UART4_Handler(void)		// THIS IS THE UART RECEIVE
{
	//-------------- DECLARATIONS	------------------
	volatile int readback;
	int16_t C;
	//-------------- END DECLARATIONS ----------------
	if (UART4->MIS & 0x0010)					// recieve interrupt
	{
		uartRX = UART4->DR;
		/*	CODE TO WRITE THIS DATA TO LCD SHOULD BE HERE	or TAKE THIS DATA TO DRIVE MOTOR	*/
		UART4->ICR|=0X0010;
		readback = UART4->ICR;			
	}
	else
	{
		UART4->ICR|=0X0010;
		readback = UART4->ICR;
	}
}
