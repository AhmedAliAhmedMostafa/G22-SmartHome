#include"motor.h"
void Rotate(Rotation_Dirction dir,uint32_t degree)
{
  uint16_t num_steps;
	inti,j;
	num_steps=degree/motor_step;
  for(j=0;j<num_steps;j++)
	{	
		for(i=0;i<4;i++)
		{
			if(dir==positive)
			{
				GPIO_PORTX_DATA_R=(GPIO_PORTX_DATA_R&~Port_mask)|sequence[4-i];
			}
			else if(dir==negative)
			{
				GPIO_PORTX_DATA_R=(GPIO_PORTX_DATA_R&~Port_mask)|sequence[i];
			}
			/*wait some time depend on the motor data sheet*/
		}
	}
}
