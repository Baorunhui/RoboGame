#include "music.h"

uint8_t  *UART4_TX_BUF;

/*
00001 up_down
00002 wave
00003 walk
00004 walk
00005 reol
*/


void MUSIC_WALK()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf_1[15] = {0xAA, 0x08, 0x0B, 0x01, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x34, 0x2A, 0x4D, 0x50, 0x33, 0xDB};
	uint8_t buf_2[15] = {0xAA, 0x08, 0x0B, 0x01, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x33, 0x2A, 0x4D, 0x50, 0x33, 0xDA};
	HAL_Delay(20000);
	HAL_UART_Transmit(&huart4, buf_1, 15, HAL_MAX_DELAY);
	HAL_Delay(60000);
	HAL_UART_Transmit(&huart4, buf_1, 15, HAL_MAX_DELAY);
}

void MUSIC_UP_DOWN()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[15] = {0xAA, 0x08, 0x0B, 0x01, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x31, 0x2A, 0x4D, 0x50, 0x33, 0xD8};
	HAL_UART_Transmit(&huart4, buf, 15, HAL_MAX_DELAY);
}

void MUSIC_WAVE()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[15] = {0xAA, 0x08, 0x0B, 0x01, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x32, 0x2A, 0x4D, 0x50, 0x33, 0xD9};
	HAL_UART_Transmit(&huart4, buf, 15, HAL_MAX_DELAY);
}

void MUSIC_REOL()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[15] = {0xAA, 0x08, 0x0B, 0x01, 0x2F, 0x30, 0x30, 0x30, 0x30, 0x35, 0x2A, 0x4D, 0x50, 0x33, 0xDC};
	HAL_UART_Transmit(&huart4, buf, 15, HAL_MAX_DELAY);
}

void MUSIC_OFF()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[4] = {0xAA, 0x10, 0x00, 0xBA};
	HAL_UART_Transmit(&huart4, buf, 4, HAL_MAX_DELAY);
}
