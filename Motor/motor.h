typedef enum{positive,negative}Rotation_Dirction;//Positive=AntiClockWise
const uint8_t sequence[4];//will be initialized after selecting Pins that will drive the motor 
#define Port_mask;
#define motor_step;//From DataSheet
void Rotate(Rotation_Dirction dir,uint32_t degree);