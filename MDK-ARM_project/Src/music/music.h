#ifndef MUSIC_CONTROL_H_
#define MUSIC_CONTROL_H_

#include "stm32f1xx_hal.h" 
#include <main.h>
extern UART_HandleTypeDef huart4; //uart4 structure

//usart2 transmit byte length
extern uint8_t  *UART4_TX_BUF;//uart transmit buffer

void MUSIC_UP_DOWN();
void MUSIC_WAVE();
void MUSIC_WALK();
void MUSIC_REOL();
void MUSIC_OFF();

#endif /* MUSIC_CONTROL_H_ */