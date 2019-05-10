#include "uart.h"
#include "adc.h"
#include "tm4c123gh6pm.h"
#include <stdio.h>

int temperature;
char buffer[16];
void ADC_sensor();
void delayMs(int n);