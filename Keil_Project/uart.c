#include"tm4c123gh6pm_a.h"
#include "uart.h"

void uart_init(){
   
	SYSCTL_RCGCUART_R  =1; //enale uart0
	SYSCTL_RCGCGPIO_R= 1;  //enable port a
  /* UART0 initialization */
  UART0_CTL_R = 0;       /* disable UART0 */
  UART0_IBRD_R = 104;    /* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
  UART0_FBRD_R = 11;     
  UART0_CC_R = 0;        /* use system clock */
  UART0_LCRH_R = 0x60;   /* 8-bit, no parity, 1-stop bit, no FIFO */
  UART0_CTL_R = 0x301;   /* enable UART0, TXE, RXE */
  
	/* UART0 TX0 and RX0 use PA0 and PA1. Set them up.init it in port.c*/

}

void UART0Tx(char c)
{
   while((UART0_FR_R & 0x20) != 0); /* wait until Tx buffer not full */
   UART0_DR_R = c;                  /* before giving it another byte */
}

char UART0Rx(void)
{
   char c;
   while((UART0_FR_R & 0x10) != 0); /* wait until the buffer is not empty */
   c = UART0_DR_R;                  /* read the received data */
       return c;                        /* and return it */
}