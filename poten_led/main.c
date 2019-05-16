#include "uart.h"
#include "LCD.h"
#include "ADC.h"
#include "swicth.h"
typedef enum {PB5,PB4,PE0,PE1,PE2,PE3,PE4,PE5,PD0,PD1,PD2,PD3}ANALOG_IN;
void SystemInit()
{
	SW1_Init();
  SW2_Init();
	uartInitM4_BTN(9600);
//	uartInitM3_ADC(9600);
	LCD_Init ();
	ADC_Init(PD1);

//	Port_Init (4);   //port a
//  Port_Init (1);	//port b
}
void display_intro(void)
{
	int i;
	uint8_t  temp_string[12]={'t','e','m','p',' ','n','o','w',' ','i','s',':'};
	for( i=0;i<12;i++)
	{
		LCD_Display_Character (temp_string[i]);
	}


}
int main()
{uint16_t data_adc;
	uint16_t temp;
uint16_t previous=0;
char duty_cycle;
SystemInit();
display_intro();




while(1)
{
		if((UART4->FR & 0x10) == 0)
		{
			temp=UART_RECIEVE_BTN ();
			if(previous==0)
			{
				delay_ms(250);
				LCD_SendCommand (Clear_Display);
				display_intro();
				LCD_Display_Integer(temp);
				previous=temp;
				
			}
			else if(temp!=previous)
			{
					delay_ms(250);
				
				LCD_SendCommand (Clear_Display);
				display_intro();
				LCD_Display_Integer(temp);
				previous=temp;
				
			}
			
			
		}
		if (!SW1_Input())
		{
			UART_SEND_BTN('#');
		}
		
		else if (!SW2_Input())
		{
			UART_SEND_BTN('$');
		}
		data_adc=ADC_get_read();
		duty_cycle=(data_adc)*100/4096;
		UART_SEND_BTN(duty_cycle);
		
		
		
		
	}
}

//}


