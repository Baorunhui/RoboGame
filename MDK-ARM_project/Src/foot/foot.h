#ifndef FOOT_CONTROL_H_
#define FOOT_CONTROL_H_

#include "stm32f1xx_hal.h" 
#include <main.h>
extern UART_HandleTypeDef huart3; //usart1 structure

//usart3 transmit byte length
#define USART3_LEN  5 

extern uint8_t  USART3_TX_BUF[USART3_LEN];//usart transmit buffer

void FOOT_INIT(); 
void TO_CAR();
void TO_FOOT();
void TO_BOX();

void TRIWALK_AHEAD();
void TRIWALK_BACK();
void TRIWALK_LEFT();
void TRIWALK_RIGHT();

void WAVEWALK_AHEAD();
void WAVEWALK_BACK();
void WAVEWALK_LEFT();
void WAVEWALK_RIGHT();

void DANCE_UP_DOWN();
void DANCE_WAVE();

#endif /* FOOT_CONTROL_H_ */