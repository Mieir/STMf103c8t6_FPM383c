/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "vue.h"

void SystemClock_Config(void);
int q=50;
int main(void)
{

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);//***定时器初始化
	 __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,50); //相当于一个周期内（20ms）有0.5ms高脉冲
	HAL_Delay(500);
	Set_LED_mood("BLUE",2,3);
	Get_PS_Sleep(PS_SleepBuffer);
  while (1)
  {			 
if(HAL_GPIO_ReadPin(GPIOA,Register_button_Pin)==GPIO_PIN_RESET){
			//判断注册按钮是否按下
			//进行注册
			HAL_Delay(200);
			HAL_GPIO_WritePin(GPIOA, Register_led_Pin, GPIO_PIN_RESET);
					int i=1;
					bool state=false;
					while(1){
						Set_LED_mood("BLUE",1,2);
							if(Get_image(PS_GetEnrollmageBuffer)&&Get_PS_Genchar(PS_GenChar,i)){
								Set_LED_mood("GREEN",2,3);
								HAL_Delay(1000);
								i++;
								if(i>4){
									state=true;
										break;
								}
							}
						}
					if(state){	
						if(Get_Ps_RegModel(PS_RegModel)&&Get_PS_StoreChar(PS_StoreChar,Get_Ps_ValidTempleteNum(PS_ValidTempleteNum))){
							Set_LED_mood("GREEN",1,5);
							HAL_Delay(1000);
							Set_LED_mood("GREEN",0,5);
							HAL_GPIO_WritePin(GPIOA, Register_led_Pin, GPIO_PIN_SET);
						}
					}
					Get_PS_Sleep(PS_SleepBuffer);
		
		}
if(HAL_GPIO_ReadPin(GPIOA,Delete_button_Pin)==GPIO_PIN_RESET){
				//判断删除指纹按钮是否按下
			bool state=false;
			HAL_GPIO_WritePin(GPIOA, Delete_led_Pin, GPIO_PIN_RESET);
			while(1){
				Set_LED_mood("RED",1,3);
				//删除函数
			if(Get_image(PS_GetImageBuffer)&&Get_PS_Genchar(PS_GenChar,1)){
				state=true;
			break;
			}
			}
			if(state){
				uint8_t ID=0x00;
				ID=Get_Delete_ID(PS_SearchMBBuffer);
				if(ID!=0xff){
					Get_PS_DeleteBuffer(PS_DeleteBuffer,ID);
					HAL_Delay(1000);
					}
			}
			Get_PS_Sleep(PS_SleepBuffer);
		  HAL_GPIO_WritePin(GPIOA, Delete_led_Pin, GPIO_PIN_SET);
		}
 if(HAL_GPIO_ReadPin(Touch_out_GPIO_Port,Touch_out_Pin)==GPIO_PIN_SET){
 //指纹验证函数
 if(Get_image(PS_GetImageBuffer)&&HAL_GPIO_ReadPin(Touch_out_GPIO_Port,Touch_out_Pin)==GPIO_PIN_SET){
	 
			if(Get_PS_Genchar(PS_GenChar,1)&&HAL_GPIO_ReadPin(Touch_out_GPIO_Port,Touch_out_Pin)==GPIO_PIN_SET){
				if(Get_Ps_SearchMBBuffer(PS_SearchMBBuffer)){
			//验证成功
      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,q); //相当于一个周期内（20ms）有2.5ms高脉冲
				 HAL_Delay(1000);
				  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,50);
			}
			}
		}  Get_PS_Sleep(PS_SleepBuffer);
 } 
		
		
  }
  /* USER CODE END 3 */
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==GPIO_PIN_11){
	while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==RESET){
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,q);
		q+=5;
		HAL_Delay(500);
		if(q>=250){
		q=50;
		}
	}
	
	}
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
