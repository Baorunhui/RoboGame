#ifndef INC_USART_H_
#define INC_USART_H_

#include "stm32f1xx_hal.h" 
extern UART_HandleTypeDef huart2; //usart2 structure

//usart2 max receive byte length
#define USART2_REC_LEN  200 

extern uint8_t  USART2_RX_BUF[USART2_REC_LEN];//usart receive buffer
extern uint16_t USART2_RX_STA; //receive state 
extern uint8_t USART2_NewData;// 1 byte 

void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart);

#endif /* INC_USART_H_ */