#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "port.h"


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


void Port_Init (uint8_t PORT_Index) 
{
	volatile  uint8_t Delay ;
	
  //1.Clock Enable to the Selected PORT
  SYSCTL_RCGCGPIO_R  = SYSCTL_RCGCGPIO_R | (1<<PORT_Index);

	//2.Allow Clock
	Delay =  SYSCTL_RCGCGPIO_R  ;


	switch (PORT_Index)
	{
	  case 0: {
		      //Unlock PORTF Commit Register as we enable the Write access to it
            GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
		
			     //Make all bits in registers (AFSEL & PUR & PDR & DEN) are commited to all new values:
             GPIO_PORTA_CR_R = 0xFF;
		  
		       //Enable PORTF Digital I/O Mode
             GPIO_PORTA_DEN_R = 0XFF;

           //Disable PORTF Analog Mode Function
             GPIO_PORTA_AMSEL_R = 0x00; 	

			     //No Alternate Functions controls the GPIO PORTF Pins
             GPIO_PORTA_AFSEL_R = 0x00;
 
           //Disable all selection of Several Peripherals functions
             GPIO_PORTA_PCTL_R = 0X00000000;
      
		        break;      }
			     
		case 1: {
		        //Unlock PORTF Commit Register as we enable the Write access to it
              GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
		
			     //Make all bits in registers (AFSEL & PUR & PDR & DEN) are commited to all new values:
             GPIO_PORTB_CR_R = 0xFF;
		  
		       //Enable PORTF Digital I/O Mode
             GPIO_PORTB_DEN_R = 0XFF;

           //Disable PORTF Analog Mode Function
             GPIO_PORTB_AMSEL_R = 0x00; 	

			     //No Alternate Functions controls the GPIO PORTF Pins
             GPIO_PORTB_AFSEL_R = 0x00;
 
           //Disable all selection of Several Peripherals functions
             GPIO_PORTB_PCTL_R = 0X00000000;
      
		        break;     }
		
		case 2: {
		        //Unlock PORTF Commit Register as we enable the Write access to it
              GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;
		
			     //Make all bits in registers (AFSEL & PUR & PDR & DEN) are commited to all new values:
             GPIO_PORTC_CR_R = 0xFF;
		  
		       //Enable PORTF Digital I/O Mode
             GPIO_PORTC_DEN_R = 0XFF;

           //Disable PORTF Analog Mode Function
             GPIO_PORTC_AMSEL_R = 0x00; 	

			     //No Alternate Functions controls the GPIO PORTF Pins
             GPIO_PORTC_AFSEL_R = 0x00;
 
           //Disable all selection of Several Peripherals functions
             GPIO_PORTC_PCTL_R = 0X00000000;
      
		        break;     }
			
		case 3: {
		        //Unlock PORTF Commit Register as we enable the Write access to it
              GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
		
			     //Make all bits in registers (AFSEL & PUR & PDR & DEN) are commited to all new values:
             GPIO_PORTD_CR_R = 0xFF;
		  
		       //Enable PORTF Digital I/O Mode
             GPIO_PORTD_DEN_R = 0XFF;

           //Disable PORTF Analog Mode Function
             GPIO_PORTD_AMSEL_R = 0x00; 	

			     //No Alternate Functions controls the GPIO PORTF Pins
             GPIO_PORTD_AFSEL_R = 0x00;
 
           //Disable all selection of Several Peripherals functions
             GPIO_PORTD_PCTL_R = 0X00000000;
      
		        break;     }
			
		case 4: {
		        //Unlock PORTF Commit Register as we enable the Write access to it
              GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
		
			     //Make all bits in registers (AFSEL & PUR & PDR & DEN) are commited to all new values:
             GPIO_PORTE_CR_R = 0x3F;
		  
		       //Enable PORTF Digital I/O Mode
             GPIO_PORTE_DEN_R = 0X3F;

           //Disable PORTF Analog Mode Function
             GPIO_PORTE_AMSEL_R = 0x00; 	

			     //No Alternate Functions controls the GPIO PORTF Pins
             GPIO_PORTE_AFSEL_R = 0x00;
 
           //Disable all selection of Several Peripherals functions
             GPIO_PORTE_PCTL_R = 0X00000000;
      
		        break;     }
			
		case 5: {
		         //Unlock PORTF Commit Register as we enable the Write access to it
               GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
		
			     //Make all bits in registers (AFSEL & PUR & PDR & DEN) are commited to all new values:
             GPIO_PORTF_CR_R = 0x1F;
		  
		       //Enable PORTF Digital I/O Mode
             GPIO_PORTF_DEN_R = 0X1F;

           //Disable PORTF Analog Mode Function
             GPIO_PORTF_AMSEL_R = 0x00; 	

			     //No Alternate Functions controls the GPIO PORTF Pins
             GPIO_PORTF_AFSEL_R = 0x00;
 
           //Disable all selection of Several Peripherals functions
             GPIO_PORTF_PCTL_R = 0X00000000;
      
		        break;       }
			
	}		
		
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void Port_SetPinDirection ( uint8_t port_index , uint8_t pins_mask ,Port_PinDirectionType pins_direction )
{
		switch (port_index)
		{
			case 0 :
								if (pins_direction)											// if output 
										GPIO_PORTA_DIR_R  |= pins_mask ;
								else																		// if input 
										GPIO_PORTA_DIR_R  &= ~pins_mask ;
			
			case 1 :
								if (pins_direction)
										GPIO_PORTB_DIR_R  |= pins_mask ;
								else
										GPIO_PORTB_DIR_R  &= ~pins_mask ;
			
			
			case 2 :
								if (pins_direction)
										GPIO_PORTC_DIR_R  |= pins_mask ;
								else
										GPIO_PORTC_DIR_R  &= ~pins_mask ;
								
			case 3 :
								if (pins_direction)
										GPIO_PORTD_DIR_R  |= pins_mask ;
								else
										GPIO_PORTD_DIR_R  &= ~pins_mask ;
			
			case 4 :
								if (pins_direction)
										GPIO_PORTE_DIR_R  |= pins_mask ;
								else
										GPIO_PORTE_DIR_R  &= ~pins_mask ;
								
			case 5 :
								if (pins_direction)
										GPIO_PORTF_DIR_R  |= pins_mask ;
								else
										GPIO_PORTF_DIR_R  &= ~pins_mask ;													
		}
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void Port_SetPinPullUp ( uint8_t port_index , uint8_t pins_mask , uint8_t enable )
{
				switch (port_index)
		{
			case 0 :
								if (enable)											// if output 
										GPIO_PORTA_PUR_R  |= pins_mask ;
								else																		// if input 
										GPIO_PORTA_PUR_R  &= ~pins_mask ;
			
			case 1 :
								if (enable)
										GPIO_PORTB_PUR_R  |= pins_mask ;
								else
										GPIO_PORTB_PUR_R  &= ~pins_mask ;
			
			
			case 2 :
								if (enable)
										GPIO_PORTC_PUR_R  |= pins_mask ;
								else
										GPIO_PORTC_PUR_R  &= ~pins_mask ;
								
			case 3 :
								if (enable)
										GPIO_PORTD_PUR_R  |= pins_mask ;
								else
										GPIO_PORTD_PUR_R  &= ~pins_mask ;
			
			case 4 :
								if (enable)
										GPIO_PORTE_PUR_R  |= pins_mask ;
								else
										GPIO_PORTE_PUR_R  &= ~pins_mask ;
								
			case 5 :
								if (enable)
										GPIO_PORTF_PUR_R  |= pins_mask ;
								else
										GPIO_PORTF_PUR_R  &= ~pins_mask ;													
		}
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


void Port_SetPinPullDown ( uint8_t port_index , uint8_t pins_mask , uint8_t enable )
{
				switch (port_index)
		{
			case 0 :
								if (enable)											// if output 
										GPIO_PORTA_PDR_R  |= pins_mask ;
								else																		// if input 
										GPIO_PORTA_PDR_R  &= ~pins_mask ;
			
			case 1 :
								if (enable)
										GPIO_PORTB_PDR_R  |= pins_mask ;
								else
										GPIO_PORTB_PDR_R  &= ~pins_mask ;
			
			
			case 2 :
								if (enable)
										GPIO_PORTC_PDR_R  |= pins_mask ;
								else
										GPIO_PORTC_PDR_R  &= ~pins_mask ;
								
			case 3 :
								if (enable)
										GPIO_PORTD_PDR_R  |= pins_mask ;
								else
										GPIO_PORTD_PDR_R  &= ~pins_mask ;
			
			case 4 :
								if (enable)
										GPIO_PORTE_PDR_R  |= pins_mask ;
								else
										GPIO_PORTE_PDR_R  &= ~pins_mask ;
								
			case 5 :
								if (enable)
										GPIO_PORTF_PDR_R  |= pins_mask ;
								else
										GPIO_PORTF_PDR_R  &= ~pins_mask ;													
		}
}


////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

uint8_t DIO_ReadPort ( uint8_t port_index , uint8_t pins_mask)
{
		switch (port_index)
		{
			case 0 : 
				return GPIO_PORTA_DATA_R&pins_mask; 
			
			case 1 : 
				return GPIO_PORTB_DATA_R&pins_mask; 
			
			case 2 : 
				return GPIO_PORTC_DATA_R&pins_mask; 
			
			case 3 : 
				return GPIO_PORTD_DATA_R&pins_mask; 
			
			case 4 : 
				return GPIO_PORTE_DATA_R&pins_mask; 
			
			case 5 : 
				return GPIO_PORTF_DATA_R&pins_mask; 				
		}		
}


