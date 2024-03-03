#ifndef __VUE_H
#define __VUE_H

#ifdef __cplusplus
extern "C" {
#endif
#include "stdint.h"
#include "fpm383c.h"
//char str[20];    //用于sprint函数的临时数组
//int SearchID,EnrollID;    //搜索指纹的ID号和注册指纹的ID号
//uint16_t ScanState = 0,WiFi_Connected_State = 0,ErrorNum = 0,PageID = 0;   //状态标志变量；WiFi是否连接状态标志位；扫描指纹错误次数标志位；输入ID号变量
//uint8_t PS_ReceiveBuffer[20];   //串口接收数据的临时缓冲数组

/* 包标示 */
#define CMD 0x01
#define DATA 0x02
#define END 0x08
/*  数据包头 */
#define Data_head 0xEF01
/*设备地址码*/
#define Address 0xFF


//休眠协议
uint8_t PS_SleepBuffer[12] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x33,0x00,0x37};
/*
//清空指纹协议
uint8_t PS_EmptyBuffer[12] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x0D,0x00,0x11};
*/
//验证获取图像协议
 uint8_t PS_GetImageBuffer[12] = {0xEF,0x01,Address,Address,Address,Address,0x01,0x00,0x03,CMD,0x00,0x05};
//注册获取图像协议
uint8_t PS_GetEnrollmageBuffer[12] = {0xEF,0x01,Address,Address,Address,Address,0x01,0x00,0x03,0x29,0x00,0x2D};
//生成特征值协议
uint8_t PS_GenChar[13] =             {0xEF,0x01,Address,Address,Address,Address,0x01,0x00,0x04,0x02,0x00,0x00,0x00};
//生成模板协议
uint8_t  PS_RegModel[12]= {0xEF,0x01,Address,Address,Address,Address,0x01,0x00,0x03,0x05,0x00,0x09};
//写入寄存器协议
//uint8_t PS_WriteEnrollTimes[]={0xEF,0x01,Address,Address,Address,Address,0x01,0x00,0x05,0x0e,0x00,0x2D};
//储存模板协议
uint8_t PS_StoreChar[15]={0xEF,0x01,Address,Address,Address,Address,0x01,0x00,0x06,0x06,0x01,0x00,0x00,0x00,0x00};
//取消命令协议
//uint8_t PS_CancelBuffer[12] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x30,0x00,0x34};

//生成模块协议
uint8_t PS_GetChar1Buffer[13] = {0xEF,0x01,Address,Address,Address,Address,0x01,0x00,0x04,DATA,0x01,0x00,0x08};
//uint8_t PS_GetChar2Buffer[13] = {0xEF,0x01,Address,Address,Address,Address,0x01,0x00,0x04,0x02,0x02,0x00,0x09};

//RGB颜色控制协议
//uint8_t PS_LEDBuffer[16] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x07,0x3C,0x00,0x00,0x00,0x00,0x00,0x00};


//搜索指纹协议
uint8_t PS_SearchMBBuffer[17] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x08,0x04,0x01,0x00,0x00,0xFF,0xFF,0x02,0x0C};

//自动注册指纹协议
//uint8_t PS_AutoEnrollBuffer[17] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x08,0x31,'\0','\0',0x04,0x00,0x16,'\0','\0'}; //PageID: bit 10:11，SUM: bit 15:16

//删除指纹协议
uint8_t PS_DeleteBuffer[16] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x07,0x0C,0x00,0x00,0x00,0x01,0x00,0x00}; 
//读取模板有效个数
uint8_t PS_ValidTempleteNum[12]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x1D,0x00,0x21};
	
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
