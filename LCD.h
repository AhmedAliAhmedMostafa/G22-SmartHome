#include "std_types.h"
#include "Common_Macros.h"
#include "tm4c123gh6pm.h"
#include "Delay.h"
#include "PORT.h"


/* LCD Port Configuration */
#define RS                 0x00   //Pin PE0
#define RW                 0x01   //Pin PE1
#define E                  0x02   //Pin PE2
#define Data_Command_PORT  0x01
#define E_RS_RW_PORT       0x04


/* LCD Commands Configurations */
#define Clear_Display                 0x01
#define Display_ON_CURSOR_OFF         0x0C
#define Display_ON_CURSOR_ON          0x0E
#define SET_CURSOR_LOCATION           0x80
#define Set_Two_Lines_Eight_Bits_Mode 0x38


/* Functions' Prototype */
void LCD_Init (void);
void LCD_SendCommand (uint8 command);
void LCD_Display_Character (uint8 data);
void LCD_Display_string (const uint8 *str);
void LCD_Coursor_Position_On_Display (uint8 row, uint8 col);
void LCD_String_From_RowCOl (uint8 row, uint8 col, const uint8 *str);
void LCD_Display_Integer(uint16 data);
void LCD_clearScreen (void);