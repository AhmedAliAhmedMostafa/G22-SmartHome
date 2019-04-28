#include"TM4C123GH6PM.h"
void UART_SEND(uint8_t UARTn,uint8_t DATA_TO_SEND)		// BUSY WAIT TRANSMISSON AS DATA SIZE TO BE SENT IS SMALL
{
		if     (UARTn==0){while((UART0->FR & 0x20) != 0);
					UART0->DR=DATA_TO_SEND;} 
		else if(UARTn==1){while((UART1->FR & 0x20) != 0);
					UART1->DR=DATA_TO_SEND;}
		else if(UARTn==3){while((UART3->FR & 0x20) != 0);
					UART3->DR=DATA_TO_SEND;}
		else if(UARTn==4){while((UART4->FR & 0x20) != 0);
					UART4->DR=DATA_TO_SEND;}
}
char UART_RECIEVE(uint8_t UARTn)	// <==== BUSY WAIT RECIEVE BUT, NOT RECOMMENDED USED IN CASE UART_HANDLER DOES NOT WORK
{
	char C;
		if     (UARTn==0){while((UART0->FR & 0x10) != 0);
						 C = UART0->DR;} 
		else if(UARTn==1){while((UART1->FR & 0x10) != 0);
						 C = UART1->DR;}
		else if(UARTn==3){while((UART3->FR & 0x10) != 0);
						 C = UART3->DR;}
		else if(UARTn==4){while((UART4->FR & 0x10) != 0);
						 C = UART4->DR;}
		return C;
}
