#ifndef __PORT_H__
#define __PORT_H__

#include "tm4c123gh6pm.h"
#include "stdint.h"

#define pin0   0x01U
#define pin1   0x02U
#define pin2   0x04U
#define pin3   0x08U
#define pin4   0x10U
#define pin5   0x05U
#define pin6   0x06U
#define pin7   0x07U

#define port_set 			0xff
#define port_reset 		0x00

#define reg_set 			0xffffffff
#define reg_reset 		0x00000000

#define portA_clk 		0x00000001
#define portB_clk 		0x00000002
#define portC_clk 		0x00000004
#define portD_clk 		0x00000008
#define portE_clk 		0x00000010
#define portF_clk 		0x00000020

typedef enum   {PORT_PIN_IN , PORT_PIN_OUT }
Port_PinDirectionType;

void Port_Init (uint8_t PORT_Index) ;
void Port_SetPinDirection ( uint8_t port_index , uint8_t pins_mask , Port_PinDirectionType pins_direction );
void Port_SetPinPullUp ( uint8_t port_index , uint8_t pins_mask , uint8_t enable );
void Port_SetPinPullDown ( uint8_t port_index , uint8_t pins_mask , uint8_t enable );
uint8_t DIO_ReadPort ( uint8_t port_index , uint8_t pins_mask);


#endif