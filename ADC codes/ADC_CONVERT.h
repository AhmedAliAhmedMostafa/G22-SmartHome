#include"TM4C123GH6PM.h"
uint16_t ADC_get_temp(void)	// FOR SAMPLE SEQUENCER 3
{
	uint16_t temperature=0;
	ADC0->PSSI |= 8;
	while((ADC0->RIS & 0x08) == 0x00) ;									// <===== THIS CAN ALSO BE INTERRUPT DRIVEN FOR FUTURE DEVELOPMENT
	temperature = 147 - (247 * ADC0->SSFIFO3) / 4096;		// WHERE 75 FROM DATASHEET AND Vdd = 3.3V >====> 75*3.3 = 247
	ADC0->ISC = 8;
	return temperature;
}
uint16_t ADC_get_read(void)								// MADE FOR GETTING ADC READING
{
	uint16_t RESULT = 0;
	ADC0->PSSI |= 8;
	while((ADC0->RIS & 0x08) == 0x00) ;		// <===== THIS CAN ALSO BE INTERRUPT DRIVEN FOR FUTURE DEVELOPMENT
	RESULT =  ADC0->SSFIFO3;		
	ADC0->ISC = 8;
	return RESULT;
}
