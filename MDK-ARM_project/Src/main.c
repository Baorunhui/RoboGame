/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "./motor/motor_control.h"
#include "usart.h"
#include "./arm/arm.h"
#include "./foot/foot.h"
#include "./music/music.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
//HAL_GPIO_WritePin(GPIOB, LED0_Pin,GPIO_PIN_RESET);
//HAL_Delay(1000);
//HAL_GPIO_WritePin(GPIOB, LED0_Pin,GPIO_PIN_SET);

HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);   //??TIM2??1?PWM,???????PWM??
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);   //??TIM2??1?PWM,???????PWM??
HAL_Delay(500);
HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
HAL_Delay(500);
HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); //??????

uint8_t last_mode = 0xff;

ARM_AHEAD_1();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		if(USART2_RX_STA&0x8000)              //?????????(??????USART2)
      {
    	 if((USART2_RX_STA&0x7FFF) ==10 	//??????3?                    
    			&& USART2_RX_BUF[0]==0xA5 	//?????1????????0xA5
    			&& USART2_RX_BUF[9]==(USART2_RX_BUF[1] + USART2_RX_BUF[2] + USART2_RX_BUF[3] + USART2_RX_BUF[4] + USART2_RX_BUF[5] + USART2_RX_BUF[6] + USART2_RX_BUF[7] + USART2_RX_BUF[8])%0x100)	//?????????????????8?
    	{
				
				uint8_t move_dir = USART2_RX_BUF[1];
				uint8_t left_speed = USART2_RX_BUF[2];
				uint8_t right_speed = USART2_RX_BUF[3];
				uint8_t arm = USART2_RX_BUF[4];
				uint8_t grasp = USART2_RX_BUF[5];
				uint8_t mode = USART2_RX_BUF[6];
				uint8_t dance = USART2_RX_BUF[7];
				uint8_t save = USART2_RX_BUF[8];
				
				
					switch(left_speed)      //left speed switch
    		 {   //TIM2????ARR???CubeMX????20000
    		 case(0x00):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,0);break;    //0%???
				 case(0x14):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,4000) ;break;//20%???
				 case(0x28):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,8000) ;break;//40%???
				 case(0x3C):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,12000);break;//60%???
				 case(0x50):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,16000);break;//80%???
				 case(0x64):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,20000);break;//100%???
				 default:break;
    		 }
				 
				 switch(right_speed)      //right speed switch
    		 {   //TIM2????ARR???CubeMX????20000
    		 case(0x00):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,0);break;    //0%???
				 case(0x14):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,4000) ;break;//20%???
				 case(0x28):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,8000) ;break;//40%???
				 case(0x3C):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,12000);break;//60%???
				 case(0x50):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,16000);break;//80%???
				 case(0x64):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,20000);break;//100%???
				 default:break;
    		 }
				 
    		 switch(mode)
				 {
					 case(0x00):			//car move
					 {
						 if(last_mode != 0xff && last_mode != mode)	//switch to car
						 {
							TO_CAR();
							 
							//hand
							//RESET: back
							//SET: forward
							HAL_GPIO_WritePin(GPIOF ,GPIO_PIN_13,GPIO_PIN_RESET );
							HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
							HAL_Delay (1000);
							HAL_TIM_PWM_Stop(&htim8,TIM_CHANNEL_2);
							 
						 }
						 switch(move_dir)      //motion switch
						 {
							 case(0x01):CAR_GO();break;
							 case(0x02):CAR_RGO();break;
							 case(0x03):CAR_LGO();break;
							 case(0x04):CAR_BACK();break;
							 case(0x00):CAR_STOP();break;
							 default:break;
						 }
						 break;
					 }
						case(0x01):				//foot mode (tri)
						{
							if(last_mode != 0xff && last_mode != mode && last_mode !=0x02 )	//switch to foot
						 {
							TO_FOOT();
								
							//hand
							//RESET: back
							//SET: forward
							HAL_GPIO_WritePin(GPIOF ,GPIO_PIN_13,GPIO_PIN_SET );
							HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
							HAL_Delay (1000);
							HAL_TIM_PWM_Stop(&htim8,TIM_CHANNEL_2);
								
						 }
						 switch(move_dir)      //motion switch
						 {
							 case(0x01):
							 {
								 //MUSIC_WALK();
								 TRIWALK_AHEAD();
								 break;
							 }
							 case(0x02):TRIWALK_LEFT();break;
							 case(0x03):TRIWALK_RIGHT();break;
							 case(0x04):TRIWALK_BACK();break;
							 case(0x00):FOOT_INIT();break;
							 default:break;
						 }
						 
						 if(dance == 0x01)
						 {
								DANCE_WAVE();
								//MUSIC_WAVE();
						 }
						 break;
						}
						case(0x02):				//foot mode (wave)
						{
							if(last_mode != 0xff && last_mode != mode && last_mode !=0x01 )	//switch to foot
						 {
							TO_FOOT();
								
							//hand
							//RESET: back
							//SET: forward
							HAL_GPIO_WritePin(GPIOF ,GPIO_PIN_13,GPIO_PIN_SET );
							HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
							HAL_Delay (1000);
							HAL_TIM_PWM_Stop(&htim8,TIM_CHANNEL_2);
								
						 }
							switch(move_dir)      //motion switch
							{
							 case(0x01):WAVEWALK_AHEAD();break;
							 case(0x02):WAVEWALK_LEFT();break;
							 case(0x03):WAVEWALK_RIGHT();break;
							 case(0x04):WAVEWALK_BACK();break;
							 case(0x00):FOOT_INIT();break;
							 default:break;
						 }
							
						 if(dance == 0x01)
						 {
								DANCE_UP_DOWN();
								//MUSIC_UP_DOWN();
						 }
						 break;
						}
						case(0x03):				//box mode 
						{
							if(last_mode != 0xff && last_mode != mode)	//switch to box
						 {
							TO_BOX();
							if(last_mode == 0x00)
							 {
								 
							 }
							 else if(last_mode == 0x01 || last_mode == 0x02)
							 {
								//hand
								//RESET: back
								//SET: forward
								HAL_GPIO_WritePin(GPIOF ,GPIO_PIN_13,GPIO_PIN_RESET );
								HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
								HAL_Delay (1000);
								HAL_TIM_PWM_Stop(&htim8,TIM_CHANNEL_2);
							 }	
						 }
							
						}
						default:break;
				 }
				 
				 switch(grasp)      //grasp control
    		 {
					case(0x01):ARM_GRASP();break;
					case(0x00):ARM_RELEASE();break;
    		 default:break;
    		 }
				 
				 switch(arm)      //arm control
    		 {
					 case(0x9C):ARM_BACK_2();break;
					 case(0xce):ARM_BACK_1();break;
					 case(0x00):ARM_MID();break;
					 case(0x32):ARM_AHEAD_1();break;
					 case(0x64):ARM_AHEAD_2(); break;
    		 default:break;
    		 }
				 
				 last_mode = mode;
    	 }
       USART2_RX_STA=0;//????0,??????
			 
			 
      }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 71;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 19999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, IN1_Pin|IN2_Pin|IN3_Pin|IN4_Pin
                          |IN11_Pin|IN22_Pin|IN33_Pin|IN44_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PE4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : LED1_Pin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : IN1_Pin IN2_Pin IN3_Pin IN4_Pin
                           IN11_Pin IN22_Pin IN33_Pin IN44_Pin */
  GPIO_InitStruct.Pin = IN1_Pin|IN2_Pin|IN3_Pin|IN4_Pin
                          |IN11_Pin|IN22_Pin|IN33_Pin|IN44_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED0_Pin */
  GPIO_InitStruct.Pin = LED0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
