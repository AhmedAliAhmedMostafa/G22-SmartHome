//#include "std_types.h"
#include "Common_Macros.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"

#define CLOCK_CYCLES_PER_MS 16000



/* Functions Prototypes */
void Delay_01s(void);
void Delay_02s(void);
void systick_wait1ms(void);
void delay_ms(uint32_t time);
void systick_init(void);
