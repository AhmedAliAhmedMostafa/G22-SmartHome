#include "port.h"

char UART0Rx(void);
void UART0Tx(char c);
void uart_init();
void UART0_puts(char* s)
