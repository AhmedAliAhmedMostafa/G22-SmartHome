#include "LCD.h"

/* Functions Prototypes */
void LCD_Init (void)
{
	//1. Enable used PORTS of the LCD Module:
	 PORT_Init (E_RS_RW_PORT);
	 PORT_Init (Data_Command_PORT);
	
	//2.Configure Pins E, RW, RS Pins as output pins:
  GPIO_PORTE_DIR_R = GPIO_PORTE_DIR_R | (1<<E) | (1<<RW) | (1<<RS);
	
	//2.Configure PORTD as output for LCD Data/Command:
	 GPIO_PORTB_DIR_R = 0xFF;
	
	//3.adjust cursor:
  LCD_SendCommand(Display_ON_CURSOR_OFF);
	
	//4./* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	LCD_SendCommand(Set_Two_Lines_Eight_Bits_Mode);
	
	/* clear LCD at the beginning */
	LCD_SendCommand(Clear_Display);	
}


void LCD_SendCommand (uint8 command) 
{
	 /* Instruction Mode RS=0 */
	 Clear_Bit(GPIO_PORTE_DATA_R,RS);  
	
	 /* write data to LCD so RW=0 */
	 Clear_Bit(GPIO_PORTE_DATA_R,RW);   
	
	/* delay for processing Tas = 50ns */
	 delay_ms(1);
	
	/* Enable LCD E=1 */
	Set_Bit(GPIO_PORTE_DATA_R,E);
	
	/* delay for processing Tpw - Tdws = 190ns */
	delay_ms(1); 
	
	/* out the required command to the data bus B0 --> B7 */
	GPIO_PORTB_DATA_R = command; 
	
	/* delay for processing Tdsw = 100ns */
	delay_ms(1); 
	
	/* disable LCD E=0 */
	Clear_Bit(GPIO_PORTE_DATA_R,E); 
	
	/* delay for processing Th = 13ns */
	delay_ms(1); 
}


void LCD_Display_Character (uint8 data)
{
	/* Data Mode RS=1 */
  Set_Bit(GPIO_PORTE_DATA_R , RS); 

	/* write data to LCD so RW=0 */
	Clear_Bit(GPIO_PORTE_DATA_R , RW);   

	/* delay for processing Tas = 50ns */
	delay_ms(1); 

	/* Enable LCD E=1 */
	Set_Bit(GPIO_PORTE_DATA_R , E);
	
	/* delay for processing Tpw - Tdws = 190ns */
	delay_ms(1); 
	
	/* out the required command to the data bus B0 --> B7 */
	GPIO_PORTB_DATA_R = data; 
	
	/* delay for processing Tdsw = 100ns */
	delay_ms(1); 
	
	/* disable LCD E=0 */
	Clear_Bit(GPIO_PORTE_DATA_R , E); 
	
	/* delay for processing Th = 13ns */
	delay_ms(1); 
}


void LCD_clearScreen(void)
{
	//clear display:
  LCD_SendCommand (Clear_Display);	
}


void LCD_Coursor_Position_On_Display (uint8 row, uint8 col)
{
	uint8 Address;
	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_SendCommand (Address | SET_CURSOR_LOCATION); 
}


void LCD_Display_string(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_Display_Character (Str[i]);
		i++;
	}
}


void LCD_String_From_RowCOl (uint8 row, uint8 col, const uint8 *str)
{
  LCD_Coursor_Position_On_Display (row,col); /* go to to the required LCD position */
	LCD_Display_string (str); /* display the string */

}


int itoa ( uint16 num, char* str, uint8 base ) 
{ 	uint8 temp;
	  uint8 start;
    uint8 end;
    int i = 0;  
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return 0; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        uint16 rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
		start = 0; 
    end = i -1; 
		
    while (start < end) 
    { temp = *(str+start);
			*(str+start) = *(str+end);
			*(str+end) = temp;
			
		    start++; 
      end--; 
    }
 return 0;
} 


void LCD_Display_Integer(uint16 data)
{	
  uint8 buff[16]; /* String to hold the ascii result */
  itoa(data,buff,10); /* 10 for decimal */
  LCD_Display_string(buff);
}