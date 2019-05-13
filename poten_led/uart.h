#include "TM4C123GH6PM_B.h"
void uartInitM4_BTN(uint32_t baudrate);
void uartInitM3_ADC(uint32_t baudrate)	;
void uartInterruptInit(uint8_t UARTn);
void UART_SEND_BTN(int8_t DATA_TO_SEND);
char UART_RECIEVE_BTN();
void UART_SEND_ADC (int8_t DATA_TO_SEND);
char UART_RECIEVE_ADC ();



