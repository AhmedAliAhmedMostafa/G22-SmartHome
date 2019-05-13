#include "Delay.h"

//1.Delay with o.1 second:
void Delay_01s(void)
{
	volatile uint32_t  time;
  time = 727240*200/91;  // 0.1sec
  while(time)
	{
		time--;
  }
}	


void systick_init(void)
{
	NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE;
	NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;
	NVIC_ST_CURRENT_R = NVIC_ST_CURRENT_S;
	NVIC_ST_CTRL_R |= (NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE);
}


//2.Delay 1 miliseconds:

void systick_wait1ms(void)
{
	NVIC_ST_RELOAD_R = CLOCK_CYCLES_PER_MS - 1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R& NVIC_ST_CTRL_COUNT) != NVIC_ST_CTRL_COUNT);

}


//4.Delay with time in miliseconds:
void delay_ms(uint32_t time){
	uint32_t i,j;
	for(j=0;j<time;j++)
	{
	for(i = 0;i < 3180;i++){}
	}
}