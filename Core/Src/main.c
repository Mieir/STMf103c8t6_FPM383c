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
//uint8_t q=0x32;
FLASH_EraseInitTypeDef flash_massage;	
uint32_t pageerror=0;
int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
	
	//写入flash结构体
	flash_massage.TypeErase=FLASH_TYPEERASE_PAGES;
	flash_massage.PageAddress=0x0801FFF0;
	flash_massage.NbPages=1;

	
	
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
			HAL_GPIO_WritePin(GPIOA, Delete_led_Pin, GPIO_PIN_RESET);//设置删除led的状态
			while(1){
				Set_LED_mood("RED",1,3);
				//删除函数
			if(Get_image(PS_GetImageBuffer)&&Get_PS_Genchar(PS_GenChar,1)){
					//如果获得图形成功，跳出循环
				//给出状态位
				state=true;
			break;
			}
			}//获得指纹数据后才可删除
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
	 //指纹模块断电后会自动解锁
	 //加入触摸电平检测后，解决问题
			if(Get_PS_Genchar(PS_GenChar,1)&&HAL_GPIO_ReadPin(Touch_out_GPIO_Port,Touch_out_Pin)==GPIO_PIN_SET){
				if(Get_Ps_SearchMBBuffer(PS_SearchMBBuffer)){
			//验证成功	 
      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,*(uint8_t*)(0x0801FFF0));//待转角度，读取储存在flash内的角度。
				 HAL_Delay(1000);
				  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0x32);//回位角度
			}
			}
		}  Get_PS_Sleep(PS_SleepBuffer);
 } 
		
		
  }
 //舵机角度调整中断回调函数
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==GPIO_PIN_11){
	while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==RESET){
		HAL_FLASH_Unlock();  //解锁flash
		uint8_t q=*(uint8_t*)(0x0801FFF0);//获取flash内地址的值
		HAL_FLASHEx_Erase(&flash_massage,  &pageerror);//擦除地址内的数据
		q+=0x05;//角度加
		if(q>=0xFA){//如果角度超过一定数值
		q=0x32;//数据复原
		}
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,q);	//舵机旋转
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, 0x0801FFF0, q);//向flash内写入数据
		HAL_Delay(500);	
		HAL_FLASH_Lock();  //flash上锁
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
