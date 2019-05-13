#ifndef COMMON_MACROS
#define COMMON_MACROS

/* Set a certain bit in any register */
#define Set_Bit(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define Clear_Bit(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define Toggle_Bit(REG,BIT) (REG^=(1<<BIT))


/* Check if a specific bit is set in any register and return true if yes */
#define Bit_Is_Set(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define Bit_Is_Clear(REG,BIT) ( !(REG & (1<<BIT)) )

#endif
