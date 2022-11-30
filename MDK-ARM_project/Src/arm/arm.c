#include "arm.h"

uint8_t  USART1_TX_BUF[USART1_LEN];

void ARM_GRASP()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART1_LEN] = {0xff, 0x09, 0x00, 0x00, 0x00};
	for(int i=0; i< USART1_LEN; i++)
		USART1_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart1, USART1_TX_BUF, USART1_LEN, HAL_MAX_DELAY);
}
void ARM_RELEASE()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART1_LEN] = {0xff, 0x09, 0x00, 0x0f, 0x00};
	for(int i=0; i< USART1_LEN; i++)
		USART1_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart1, USART1_TX_BUF, USART1_LEN, HAL_MAX_DELAY);
}


void ARM_BACK_1()
{
	uint8_t buf[USART1_LEN] = {0xFF, 0x09, 0x00, 0x02, 0x00};
	for(int i=0; i< USART1_LEN; i++)
		USART1_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart1, USART1_TX_BUF, USART1_LEN, HAL_MAX_DELAY);
}
void ARM_BACK_2()
{
	uint8_t buf[USART1_LEN] = {0xFF, 0x09, 0x00, 0x01, 0x00};
	for(int i=0; i< USART1_LEN; i++)
		USART1_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart1, USART1_TX_BUF, USART1_LEN, HAL_MAX_DELAY);
}
void ARM_MID()
{
	uint8_t buf[USART1_LEN] = {0xFF, 0x09, 0x00, 0x03, 0x00};
	for(int i=0; i< USART1_LEN; i++)
		USART1_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart1, USART1_TX_BUF, USART1_LEN, HAL_MAX_DELAY);
}     
void ARM_AHEAD_1()
{
	uint8_t buf[USART1_LEN] = {0xFF, 0x09, 0x00, 0x04, 0x00};
	for(int i=0; i< USART1_LEN; i++)
		USART1_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart1, USART1_TX_BUF, USART1_LEN, HAL_MAX_DELAY);
}
void ARM_AHEAD_2()
{
	uint8_t buf[USART1_LEN] = {0xFF, 0x09, 0x00, 0x05, 0x00};
	for(int i=0; i< USART1_LEN; i++)
		USART1_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart1, USART1_TX_BUF, USART1_LEN, HAL_MAX_DELAY);
}


