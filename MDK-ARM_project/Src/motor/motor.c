#include "motor.h"

void L_MOTOR_GO()
{
	HAL_GPIO_WritePin(GPIOA, IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, IN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN11_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, IN22_Pin, GPIO_PIN_RESET);

}

void R_MOTOR_GO()
{
	HAL_GPIO_WritePin(GPIOA, IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, IN4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN33_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, IN44_Pin, GPIO_PIN_RESET);

}

void L_MOTOR_BACK()
{
	HAL_GPIO_WritePin(GPIOA, IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, IN11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN22_Pin, GPIO_PIN_SET);

}

void R_MOTOR_BACK()
{
	HAL_GPIO_WritePin(GPIOA, IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, IN33_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN44_Pin, GPIO_PIN_SET);

}

void L_MOTOR_STOP()
{
	HAL_GPIO_WritePin(GPIOA, IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN22_Pin, GPIO_PIN_RESET);

}

void R_MOTOR_STOP()
{
	HAL_GPIO_WritePin(GPIOA, IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN33_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN44_Pin, GPIO_PIN_RESET);

}
