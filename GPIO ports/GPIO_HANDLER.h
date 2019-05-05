#include"TM4C123GH6PM.h"
#include "motor.h"
// include transmit
void GPIOF_HANDLER(void)		// INTERNAL SWITCHES ARE AT ---PF1--- AND ---PF4---
{
	volatile int readback;
	char c ;
	while (GPIOF->MIS != 0)
	{
		if (GPIOF->MIS & 0x10) /* is it SW1(PF4)? */
		{
			/* CODE TO WRITE ON UART_DR REGISTER ex: UART0->DR = '$' WHERE THIS SIGN '$' MEANS +30 DEG AT MOTOR SIDE  */
			
			// make sure that the port is identified in motor.c 
			if ( UART_RECIEVE (0) == '$' )
					Rotate(negative,30);
			
			GPIOF->ICR |= 0x10;			 /* clear the interrupt flag */
			readback = GPIOF->ICR; 	/* a read to force clearing of interrupt*/
		}
		else if (GPIOF->MIS & 0x01) /* then it must be SW2(PF0) */
		{
			/* CODE TO WRITE ON UART_DR REGISTER ex: UART0->DR = '#' WHERE THIS SIGN '#' MEANS -30 DEG AT MOTOR SIDE  */
			
			/ make sure that the port is identified in motor.c 
			if ( UART_RECIEVE (0) == '#' ) 
				Rotate(positive,30);
			
			GPIOF->ICR |= 0x10;			 /* clear the interrupt flag */
			readback = GPIOF->ICR; 	/* a read to force clearing of interrupt*/
		}
	}
	//UART0->DR
}
