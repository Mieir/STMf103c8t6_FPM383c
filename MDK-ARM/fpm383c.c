#include "fpm383c.h"
uint8_t PS_ReceiveBuffer[25];   //串口接收数据的临时缓冲数组

/********************* 注册函数模块 *******************************/
/* 校验数据包完整性函数 */
uint8_t Check_sum(uint8_t *receivebuffter){
	uint8_t sum=0x00;
	for(int i=6;i<=9;i++){
		//从缓冲区的第6位开始累加
	sum+=receivebuffter[i];
	}	
return sum;//获得校验和
}



/* 指纹注册 */
/* 将指纹信息放到缓冲区*/
bool Get_image(uint8_t *GetImageBuffer){	

	//HAL_UART_Transmit(&huart1,GetImageBuffer,12,100);
	TX_data(GetImageBuffer,12);
	//数据发送和数据接收之间不能加延时函数
	//HAL_UART_Receive(&huart1,PS_ReceiveBuffer,12,HAL_MAX_DELAY);
	RX_data(PS_ReceiveBuffer,12);
	//获得缓冲数据后首先验证数据完整性
	if(Check_sum(PS_ReceiveBuffer)==PS_ReceiveBuffer[11]){
	if(PS_ReceiveBuffer[9]==0x00){
		//操作成功
		//成功获得指纹注册图像
	//	Set_LED_mood("GREEN",1,5);
	//	HAL_Delay(1000);
	///	Set_LED_mood("GREEN",1,5);
		return true;
	
	}else{
		//图像获得失败
		//失败提示
		//Set_LED_mood("RED",2,5);
		return false;
	}
	
	}else{
		//数据校验失败
		//Set_LED_mood("BLUE",2,5);
		return false;
	}	
}
/*  将图像缓冲区内的文件生成特征 */
bool Get_PS_Genchar(uint8_t *GetGenchar,int buffer_id){
	
	//写入缓冲区号
	GetGenchar[10]=buffer_id;
	//计算校验码
	uint8_t sum=0x00;
	for(int i=6;i<=10;i++){
	sum+=GetGenchar[i];
	}
	GetGenchar[12]=sum;
	for(int i=0;i<=19;i++){
	PS_ReceiveBuffer[i]=0x00;
	}
	//HAL_UART_Transmit(&huart1,GetGenchar,13,200);
	//HAL_UART_Receive(&huart1,PS_ReceiveBuffer,12,HAL_MAX_DELAY);
	TX_data(GetGenchar,13);
	RX_data(PS_ReceiveBuffer,12);
	//判断接收包数据完整性和流程功能
if(Check_sum(PS_ReceiveBuffer)==PS_ReceiveBuffer[11]){
	if(PS_ReceiveBuffer[9]==0x00){
		
	//	Set_LED_mood("BULE",2,3);
		//HAL_Delay(600);
		//Set_LED_mood("GREEN",1,5);
		return true;
	
	}else{
	//error
		//led
	//	Set_LED_mood("RED",2,3);
		
		return false;
	}
	
	}else{
		//数据校验失败
	//	Set_LED_mood("BLUE",2,5);
		return false;
	}	
}
/*** 合并特征(生成模板)***/
bool Get_Ps_RegModel(uint8_t *RegModel){
	HAL_UART_Transmit(&huart1,RegModel,12,100);
	HAL_UART_Receive(&huart1,PS_ReceiveBuffer,12,HAL_MAX_DELAY);
if(Check_sum(PS_ReceiveBuffer)==PS_ReceiveBuffer[11]){
	if(PS_ReceiveBuffer[9]==0x00){
		
		//Set_LED_mood("BLUE",2,5);
		HAL_Delay(1000);
		return true;
	
	}else{
	//error
		//led
		//Set_LED_mood("RED",2,5);
		return false;
	}
	
	}else{
		//led
		//Set_LED_mood("BLUE",2,5);
		//数据校验失败
		return false;
	}	
}
/**(搜索指纹模块)查询指纹是否注册**/
bool Get_Ps_SearchMBBuffer(uint8_t *PS_SearchMBBuffer){
	TX_data(PS_SearchMBBuffer,17);
	RX_data(PS_ReceiveBuffer,16);
//	HAL_UART_Transmit(&huart1,PS_SearchMBBuffer,17,100);
	//HAL_UART_Receive(&huart1,PS_ReceiveBuffer,16,HAL_MAX_DELAY);
	uint8_t sum=0x00;
	for(int i=6;i<=13;i++){
		sum+=PS_ReceiveBuffer[i];
	}
if(sum==PS_ReceiveBuffer[15]){
	if(PS_ReceiveBuffer[9]==0x00){
		
		Set_LED_mood("GREEN",2,3);
		return true;
	
	}else{
	//error
		//led
	
		Set_LED_mood("RED",2,3);
		return false;
	}
	
	}else{
		//led
		Set_LED_mood("BLUE",2,5);
		//数据校验失败
		return false;
	}	
}

/***读取模板有效个数***/
/** 后期计划通过内部flash进行数据存储 **/
uint8_t Get_Ps_ValidTempleteNum(uint8_t * ValidTempleteNum){
	HAL_UART_Transmit(&huart1,ValidTempleteNum,12,100);
	HAL_UART_Receive(&huart1,PS_ReceiveBuffer,14,HAL_MAX_DELAY);
	//HAL_UART_Transmit(&huart1,ValidTempleteNum,18,100);
	//HAL_UART_Receive(&huart1,PS_ReceiveBuffer,24,HAL_MAX_DELAY);
	uint8_t sum=0x00;
	for(int i=6;i<=11;i++){
	sum+=PS_ReceiveBuffer[i];
	}
if(sum==PS_ReceiveBuffer[13]){
if(PS_ReceiveBuffer[9]==0x00){
	uint8_t num=0x00;
	num=PS_ReceiveBuffer[11];
		return num;
	}else{
		return 0xFF;
	}	
	}else{
		return 0xFF;
	}	
}
/**储存模板**/
bool Get_PS_StoreChar(uint8_t *StoreChar,uint8_t id){
//Get_Ps_ValidTempleteNum(PS_SearchMBBuffer);
	//校验和 
	StoreChar[10]= 1;  //缓冲区号
	StoreChar[12]=id;//获取储存数据id
	uint8_t sum=0x00;
	for(int i=6;i<=12;i++){
		//从缓冲区的第6位开始累加
	sum+=StoreChar[i];
	}	
	//发送效验和
	StoreChar[14]=sum;
	HAL_UART_Transmit(&huart1,StoreChar,15,100);
	HAL_UART_Receive(&huart1,PS_ReceiveBuffer,12,HAL_MAX_DELAY);
if(Check_sum(PS_ReceiveBuffer)==PS_ReceiveBuffer[11]){
	if(PS_ReceiveBuffer[9]==0x00){
		//uint8_t sum=Check_sum;
			//	Set_LED_mood("GREEN",2,5);
		//next
		return true;
	}else{
   // Set_LED_mood("BLUE",2,5);
		//led
		//error
		return false;
	}
	
	}else{
		//led
		//error
		//数据校验失败
	//	Set_LED_mood("RED",2,3);
		return false;
	}	
}
/**led函数 **/
// mood  0    1    2
// mood 常闭 常开  闪烁
//times 闪烁次数
void Set_LED_mood(char *led_name,int mood , int times){
	//RGB颜色控制协议
uint8_t PS_LEDBuffer[16] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x07,0x3C,0x00,0x00,0x00,0x00,0x00,0x00};
	if(mood==0){//模式选着 //常闭
	PS_LEDBuffer[10]=0x04;
	}else if(mood==1){     //常开
		PS_LEDBuffer[10]=0x03;
		if(!strcmp(led_name,"RED")){//颜色选着
		PS_LEDBuffer[11]=0x04;
		PS_LEDBuffer[12]=0x04;
		}else if(!strcmp(led_name,"BLUE")){
		PS_LEDBuffer[11]=0x01;
		PS_LEDBuffer[12]=0x01;
		}else if(!strcmp(led_name,"GREEN")){
		PS_LEDBuffer[11]=0x02;
		PS_LEDBuffer[12]=0x02;
		}
	}else if(mood==2){    //闪烁
		if(!strcmp(led_name,"RED")){
		PS_LEDBuffer[11]=0x04;
		PS_LEDBuffer[12]=0x04;
		}else if(!strcmp(led_name,"BLUE")){
		PS_LEDBuffer[11]=0x01;
		PS_LEDBuffer[12]=0x01;
		}else if(!strcmp(led_name,"GREEN")){
		PS_LEDBuffer[11]=0x02;
		PS_LEDBuffer[12]=0x02;
		}
	  PS_LEDBuffer[10]=0x02;
		PS_LEDBuffer[13]=0x00;
		PS_LEDBuffer[13]+=times;
	}
	for(int i=6;i<14;i++){

	PS_LEDBuffer[15]+=PS_LEDBuffer[i];
	}
HAL_UART_Transmit(&huart1,PS_LEDBuffer,16,100);
HAL_UART_Receive(&huart1,PS_ReceiveBuffer,12,HAL_MAX_DELAY);//每次数据发送完成进行接收。
	                                                          //因为数据发送几乎是瞬时的而后面的接收是阻塞的。
}                                                             //会导致接收的数据成为未被接收的内容
/*************************指纹注册流程开始***********************/

/*************************指纹注册流程结束***********************/
//自动化指纹注册//

/*          模块休眠函数           */
bool Get_PS_Sleep(uint8_t *PS_SleepBuffer){	

	HAL_UART_Transmit(&huart1,PS_SleepBuffer,12,100);
	//数据发送和数据接收之间不能加延时函数
	HAL_UART_Receive(&huart1,PS_ReceiveBuffer,12,HAL_MAX_DELAY);
	//uint8_t sum =	Check_sum(PS_ReceiveBuffer);
	//获得缓冲数据后首先验证数据完整性
	if(Check_sum(PS_ReceiveBuffer)==PS_ReceiveBuffer[11]){
	if(PS_ReceiveBuffer[9]==0x00){
		//操作成功
		//成功获得指纹注册图像
		//Set_LED_mood("BLUE",0,5);
		
		return true;
	
	}else{
		//图像获得失败
		//失败提示
	//	Set_LED_mood("RED",2,5);
		return false;
	}
	
	}else{
		//数据校验失败
	//	Set_LED_mood("BLUE",2,5);
		return false;
	}	
}



/* 写入寄存器 约定指纹注册次数 */
/************************* 应用层通讯包 ****************************/
//指纹注册拼接次数协议
uint8_t PS_register[19]={0xF1,0x1F,0xE2,0x2E,0xB6,0x6B,0xA8,0x8A,0x00,0x08,0x85,0x00,0x00,0x00,0x00,0x02,0x0D,0x04,0xED};
void Set_register_times(int times){
uint8_t sum=0x00;
sum = PS_register[17]+(uint8_t)times+PS_register[15];
PS_register[18]=(~sum+1);
}

/*********自动化删除*********/
//获得删除id
uint8_t Get_Delete_ID(uint8_t *PS_SearchMBBuffer){
	HAL_UART_Transmit(&huart1,PS_SearchMBBuffer,17,100);
	HAL_UART_Receive(&huart1,PS_ReceiveBuffer,16,HAL_MAX_DELAY);
	uint8_t sum=0x00;
	for(int i=6;i<=13;i++){
		sum+=PS_ReceiveBuffer[i];
	}
if(sum==PS_ReceiveBuffer[15]){
	if(PS_ReceiveBuffer[9]==0x00){
		
		
		return PS_ReceiveBuffer[11];
	
	}else{

		return 0xff;
	}
	
	}else{
		return 0xff;
	}	
}
bool Get_PS_DeleteBuffer(uint8_t *PS_DeleteBuffer,uint8_t ID){
	PS_DeleteBuffer[11]=ID;
	uint8_t sum=0x00;
	for(int i=6;i<=13;i++){
	sum+=PS_DeleteBuffer[i];
	}
	PS_DeleteBuffer[15]=sum;
	HAL_UART_Transmit(&huart1,PS_DeleteBuffer,16,100);
	HAL_UART_Receive(&huart1,PS_ReceiveBuffer,12,HAL_MAX_DELAY);
	if(Check_sum(PS_ReceiveBuffer)==PS_ReceiveBuffer[11]){
	if(PS_ReceiveBuffer[9]==0x00){
		//uint8_t sum=Check_sum;
			Set_LED_mood("BLUE",2,5);
		//next
		return true;
	}else{
    Set_LED_mood("RED",2,5);
		//led
		//error
		return false;
	}
	
	}else{
		//led
		//error
		//数据校验失败
	Set_LED_mood("RED",2,3);
		return false;
	}	

}
//发送数据封装
void TX_data(uint8_t *TX_Data,int length){
if(	HAL_UART_Transmit(&huart1,TX_Data,length,100)!=HAL_OK){
	Set_LED_mood("BLUE",2,3);
}
}
//接收数据封装
void RX_data(uint8_t *RX_Data,int length){
if(		HAL_UART_Receive(&huart1,RX_Data,length,500)!=HAL_OK){
	Set_LED_mood("GREEN",2,3);
}
}
 
