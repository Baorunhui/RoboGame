#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

#include "stm32f1xx_hal.h" 
#include <main.h>
#include "motor.h"


//extern TIM_HandleTypeDef htim2;// TIM2 structure

void CAR_GO();                 
void CAR_BACK();               
void CAR_LGO();                
void CAR_RGO();                
void CAR_STOP();               

#endif /* CONTROL_CONTROL_H_ */