#include "adc.h"
#include "tm4c123gh6pm_a.h"
#include "TM4C123GH6PM.H"
//uint8_t result;

void ADC0_init()
{
//	SYSCTL_RCGCGPIO_R |= 0X08;
	SYSCTL_RCGCADC_R=1;  						  /* enable clock to ADC0 */
  ADC0_ACTSS_R&=~ADC_ACTSS_ASEN3;   /* disable SS3 during configuration */
	ADC0_EMUX_R &= ~0xF000; 					/* software trigger conversion */
	ADC0_SSMUX3_R =ADC_SSMUX3_MUX0_S; /* get input from channel 0 */
	ADC0_SSCTL3_R|=0X0E;   // 1st Sample is End of Sequence -use interrupt-use temp sensor
	ADC0_ACTSS_R|=ADC_ACTSS_ASEN3;    /* enable ADC0 sequencer 3 */
	/* initialize PE3 for AIN0 input */
//  GPIO_PORTE_AFSEL_R |= 0X08; 					/* enable alternate function */
//  GPIO_PORTE_DEN_R &= ~0x08; 					/* disable digital function */
//  GPIO_PORTE_AMSEL_R |= 0x08; 					/* enable analog function */
 }
uint16_t get_temp(){
	uint16_t result;
	ADC0_PSSI_R|=ADC_PSSI_SS3;        /* start a conversion sequence 3 */
  while((ADC0_RIS_R & ADC_RIS_INR3)==0);/* wait for conversion complete */
  result=ADC0_SSFIFO3_R;            /* read conversion result */
  ADC0_ISC_R |=ADC_ISC_IN3; 	//clear completion flag 
	result= 147-(result* 247 )/4096;
	return result;
}