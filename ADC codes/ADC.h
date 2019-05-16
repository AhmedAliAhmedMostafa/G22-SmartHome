typedef enum {PB5,PB4,PE0,PE1,PE2,PE3,PE4,PE5,PD0,PD1,PD2,PD3}ANALOG_IN;
void ADC_Init_TEMP(void);
uint16_t ADC_get_temp(void);
uint16_t ADC_get_read(void);
void ADC_Init(ANALOG_IN AIN)