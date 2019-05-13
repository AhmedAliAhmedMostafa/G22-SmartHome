#include "uart.h"
#include "LCD.h"
#include "adc.h"
#include "swicth.h"
void SystemInit()
{
	SW1_Init();
  SW2_Init();
//	uartInitM4_BTN(9600);
	uartInitM3_ADC(9600);
	LCD_Init ();
	ADC0_init();
	LCD_Init();
	Port_Init (4);   //port a
  Port_Init (1);	//port b
}
int main()
{ int chara;
 uint16_t temp;
SystemInit();
	

		LCD_Display_Integer(10);
		
		if((UART3->FR & 0x10) == 0)
		{
			temp=UART_RECIEVE_ADC ()<<4;
			while((UART3->FR & 0x10) == 0);
			temp|=UART_RECIEVE_ADC ();
			LCD_Display_Integer(temp);
		}
		if (!SW1_Input())
		{
			UART_SEND_BTN('#');
		}
		
		else if (!SW2_Input())
		{
			UART_SEND_BTN('$');
		}
		
		else 
		{
			UART_SEND(ADC_read());
		}	
		chara =UART_RECIEVE () ;
		LCD_Display_Integer(chara);
		
	


}
