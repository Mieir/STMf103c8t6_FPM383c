
#ifndef __FPM383C_H
#define __FPM383C_H

#ifdef __cplusplus
extern "C" { 
#endif
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "usart.h"
#include "stdio.h"
bool Get_PS_Sleep(uint8_t *PS_SleepBuffer);
bool Get_image(uint8_t *ImageBuffer);
bool Get_PS_Genchar(uint8_t *Genchar,int buffer_id);
bool Get_Ps_RegModel(uint8_t *RegModel);
bool Get_Ps_SearchMBBuffer(uint8_t *PS_SearchMBBuffer);
bool Get_PS_StoreChar(uint8_t *StoreChar,uint8_t id);
void Set_LED_mood( char *led_name,int mood , int times);
uint8_t Get_Ps_ValidTempleteNum(uint8_t * ValidTempleteNum);
uint8_t Get_Delete_ID(uint8_t *PS_SearchMBBuffer);
bool Get_PS_DeleteBuffer(uint8_t *PS_DeleteBuffer,uint8_t ID);
void TX_data(uint8_t *TX_Data,int length);
void RX_data(uint8_t *RX_Data,int length);
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
