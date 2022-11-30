#include"motor_control.h"

   void CAR_GO()
	{
//	
		L_MOTOR_GO();
		R_MOTOR_GO();
	}
	void CAR_BACK()
	{
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,1200);
		L_MOTOR_BACK();
		R_MOTOR_BACK();
	}
	void CAR_LGO()
	{
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,500);
		L_MOTOR_BACK();
		R_MOTOR_GO();
	}
	void CAR_RGO()
	{
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,500);
		L_MOTOR_GO();
		R_MOTOR_BACK();
	}
	void CAR_STOP()
	{
		L_MOTOR_STOP();
		R_MOTOR_STOP();
	}