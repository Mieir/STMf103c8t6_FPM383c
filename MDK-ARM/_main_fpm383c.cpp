#include "vue.h"

/*************************/

//Õ‚≤øªΩ–—÷–∂œ
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{ if(GPIO_PIN_12==GPIO_Pin){

  Set_LED_mood("BLUE",2,5);
}
if(GPIO_PIN_8==GPIO_Pin){
	HAL_Delay(200);
	Set_LED_mood("BLUE",2,5);
		if(HAL_GPIO_ReadPin(GPIOA,Delete_led_Pin)==GPIO_PIN_SET)
			{	
				//µ„¡¡…æ≥˝led
				HAL_GPIO_WritePin(GPIOA, Delete_led_Pin, GPIO_PIN_RESET);	
	} 
}
if(GPIO_Pin==GPIO_PIN_11){

HAL_Delay(200);
	Set_LED_mood("BLUE",2,5);
		if(HAL_GPIO_ReadPin(GPIOA,Register_led_Pin)==GPIO_PIN_SET)
			{	
				//µ„¡¡◊¢≤·led
				//HAL_GPIO_WritePin(GPIOA, Register_led_Pin, GPIO_PIN_RESET);	
				
	} 




}
}
