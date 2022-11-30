# include "foot.h"

uint8_t  USART3_TX_BUF[USART3_LEN];

void FOOT_INIT()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x00, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}
void TO_CAR()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x07, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}


void TO_FOOT()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x00, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}

void TO_BOX()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x0c, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}

//tri walk

void TRIWALK_AHEAD()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x01, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}
void TRIWALK_BACK()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x04, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}
void TRIWALK_LEFT()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x02, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}
void TRIWALK_RIGHT()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x03, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}

//wave walk

void WAVEWALK_AHEAD()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x05, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}
void WAVEWALK_BACK()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x06, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}


void WAVEWALK_LEFT()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x08, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}
void WAVEWALK_RIGHT()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x09, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}



void DANCE_UP_DOWN()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x0a, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}

void DANCE_WAVE()
{
	HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x0b, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}