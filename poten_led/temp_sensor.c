#include "temp_sensor.h"
#include "uart.h"
#include "adc.h"
//volatile uint8_t result;
//uart_init();
//void ADC0_init();
void ADC_sensor(){ //send temp in fehrenhait to uart
		ADC0_PSSI_R|=ADC_PSSI_SS3; /* start a conversion sequence 3 */
		while((ADC0_RIS_R & ADC_RIS_INR3) == 0) ; /* wait for conversion complete */
		temperature = ADC0_SSFIFO3_R * 330 / 4096;
		ADC0_ISC_R |=ADC_ISC_IN3; /* clear completion flag */
		// sprintf(buffer, "\r\nTemp = %dF", temperature);
//		UART0_puts(buffer);
		delayMs(1000);
}
void delayMs(int n)
{
		int32_t i, j;
		for(i = 0 ; i < n; i++)
		for(j = 0; j < 3180; j++)
					{} /* do nothing for 1 ms */
}
 