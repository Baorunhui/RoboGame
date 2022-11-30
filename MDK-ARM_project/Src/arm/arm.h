#ifndef ARM_CONTROL_H_
#define ARM_CONTROL_H_

#include "stm32f1xx_hal.h" 
#include <main.h>
extern UART_HandleTypeDef huart1; //usart1 structure

//usart2 transmit byte length
#define USART1_LEN  5 

extern uint8_t  USART1_TX_BUF[USART1_LEN];//usart transmit buffer

void ARM_GRASP();
void ARM_RELEASE();

void ARM_BACK_1(); 
void ARM_BACK_2();
void ARM_MID();
void ARM_AHEAD_1();
void ARM_AHEAD_2();

#endif /* ARM_CONTROL_H_ */