typedef enum{positive,negative}Rotation_Dirction;//Positive=AntiClockWises
#define Port_mask 0X0F;
#define motor_step 5.625;//From DataSheet
void motor_init(void);
void Rotate(Rotation_Dirction dir,int degree);