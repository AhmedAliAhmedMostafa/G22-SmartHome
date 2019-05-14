#include <stdbool.h>
#include <stdint.h>
#include"TM4C123GH6PM.h"
#include"HW_INTER_STATE.h"
#include "adc.h"
#include"rom_map.h"
#include "Portdir.h"
#include"GPIO_INTER_ENABLE.h"
#include "uart.h"


// define ports
#define LED_PERIF	SYSCTL_PERIPH_GPIOF
#define LED_PORT	GPIO_PORTF_BASE
#define LED_RED		GPIO_PIN_1
#define LED_GREEN	GPIO_PIN_3
#define LED_BLUE	GPIO_PIN_2
#define LEDS		(LED_RED|LED_GREEN|LED_BLUE)
#define	LED_SET(X)	ROM_GPIOPinWrite(LED_PORT, LEDS, (X));


uint32_t rawtemp[4];

// this flag is set by the interrupt routine and read by the wait loop
volatile uint32_t newtemp;

// interrupt routine for the ADC
void ADC0handler(void)
{
	LED_SET(LED_BLUE);
	ROM_ADCIntClear(ADC0_BASE, 3);
	ROM_ADCSequenceDataGet(ADC0_BASE, 3, rawtemp);
	newtemp = 1;
	LED_SET(0);
}

void InitADC(void)
{
	// enable ADC0
	// set a slower conversion rate
	// use sequencer 3 (single sample), with manual trigger
	// seq 3, step 0, temperature-sensor, interrupt-enable, last-conversion
	// enable sequencer 3

	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	ROM_SysCtlDelay(2);
	ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_RATE_EIGHTH | ADC_CLOCK_SRC_PIOSC, 1);
	ROM_ADCHardwareOversampleConfigure(ADC0_BASE, 16); // 64 32 16 8 4 2
	ROM_ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
	ROM_ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);
	ROM_ADCSequenceEnable(ADC0_BASE, 3);

	// make sure interrupt flag is clear
	// enable the interrupt for the module and for the sequence
	ROM_ADCIntClear(ADC0_BASE, 3);
	ROM_IntEnable(INT_ADC0SS3);
	ROM_ADCIntEnable(ADC0_BASE, 3);
}

void InitConsole(void)
{
	// enable the port that has UART0 pins
	// configure the RX/TX port pins
	// enable the uart, set the clock, set the pins
	// set baudrate
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	ROM_SysCtlDelay(2);
	ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
	ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	ROM_UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTStdioConfig(0, 115200, 16000000);
}

int main(void)
{
	uint32_t i, tempC, tempF;

	ROM_SysCtlClockSet(SYSCTL_SYSDIV_2 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	ROM_SysCtlPeripheralEnable(LED_PERIF);
	ROM_SysCtlDelay(2);
	ROM_GPIOPinTypeGPIOOutput(LED_PORT, LEDS);
	LED_SET(0);

	InitConsole();
	InitADC();

	UARTprintf("\n\nADC internal temperature sensor\n");

	// allow interrupts
	ROM_IntMasterEnable();

	i = 0;
	while ( 1 ) {
		// clear the flag
		newtemp = 0;
		LED_SET(LED_RED);

		// start conversion
		ROM_ADCProcessorTrigger(ADC0_BASE, 3);

		// spin and wait for the interrupt handler to get the data
		while ( newtemp == 0 ) {
			__asm ("WFE\n	");
		}

		LED_SET(LED_GREEN);

		// print temp every two seconds
		if ( ++i == 2000 ) {
			i = 0;
			tempC = (1475 - ((2475 * rawtemp[0])) / 4096)/10;
			tempF = ((tempC * 9) + 160) / 5;
			UARTprintf("$%04x %4d   %3d C  %3d F\n", 
				rawtemp[0], rawtemp[0], tempC, tempF);
		}
		// delay to slow down the loop to around 1KHz
		ROM_SysCtlDelay(ROM_SysCtlClockGet()*3/8000);
	}
}