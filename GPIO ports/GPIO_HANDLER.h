#include"TM4C123GH6PM.h"
void GPIOF_HANDLER(void)		// INTERNAL SWITCHES ARE AT ---PF1--- AND ---PF4---
{
	volatile int readback;
	while (GPIOF->MIS != 0)
	{
		if (GPIOF->MIS & 0x10) /* is it SW1(PF4)? */
		{
			/* CODE TO WRITE ON UART_DR REGISTER ex: UART0->DR = '$' WHERE THIS SIGN '$' MEANS +30 DEG AT MOTOR SIDE  */
			GPIOF->ICR |= 0x10;			 /* clear the interrupt flag */
			readback = GPIOF->ICR; 	/* a read to force clearing of interrupt*/
		}
		else if (GPIOF->MIS & 0x01) /* then it must be SW2(PF0) */
		{
			/* CODE TO WRITE ON UART_DR REGISTER ex: UART0->DR = '#' WHERE THIS SIGN '#' MEANS -30 DEG AT MOTOR SIDE  */
			GPIOF->ICR |= 0x10;			 /* clear the interrupt flag */
			readback = GPIOF->ICR; 	/* a read to force clearing of interrupt*/
		}
	}
	//UART0->DR
}
