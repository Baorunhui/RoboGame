#ifndef MOTOR_MOTOR_H_
#define MOTOR_MOTOR_H_

#include "stm32f1xx_hal.h" 
#include <main.h>

void L_MOTOR_GO();         //left two wheels go
void R_MOTOR_GO();
void L_MOTOR_BACK();       //left two wheels back
void R_MOTOR_BACK();
void L_MOTOR_STOP();			 //left tow wheels stop
void R_MOTOR_STOP();       

#endif