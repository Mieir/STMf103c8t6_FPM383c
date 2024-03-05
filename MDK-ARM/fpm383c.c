#include "fpm383c.h"
uint8_t PS_ReceiveBuffer[25];   //���ڽ������ݵ���ʱ��������

/********************* ע�ắ��ģ�� *******************************/
/* У�����ݰ������Ժ��� */
uint8_t Check_sum(uint8_t *receivebuffter){
	uint8_t sum=0x00;
	for(int i=6;i<=9;i++){
		//�ӻ������ĵ�6λ��ʼ�ۼ�
	sum+=receivebuffter[i];
	}	
return sum;//���У���
}



/* ָ��ע�� */
/* ��ָ����Ϣ�ŵ�������*/
bool Get_image(uint8_t *GetImageBuffer){	

	//HAL_UART_Transmit(&huart1,GetImageBuffer,12,100);
	TX_data(GetImageBuffer,12);
	//���ݷ��ͺ����ݽ���֮�䲻�ܼ���ʱ����
	//HAL_UART_Receive(&huart1,PS_ReceiveBuffer,12,HAL_MAX_DELAY);
	RX_data(PS_ReceiveBuffer,12);
	//��û������ݺ�������֤����������
	if(Check_sum(PS_ReceiveBuffer)==PS_ReceiveBuffer[11]){
	if(PS_ReceiveBuffer[9]==0x00){
		//�����ɹ�
		//�ɹ����ָ��ע��ͼ��
	//	Set_LED_mood("GREEN",1,5);
	//	HAL_Delay(1000);
	///	Set_LED_mood("GREEN",1,5);
		return true;
	
	}else{
		//ͼ����ʧ��
		//ʧ����ʾ
		//Set_LED_mood("RED",2,5);
		return false;
	}
	
	}else{
		//����У��ʧ��
		//Set_LED_mood("BLUE",2,5);
		return false;
	}	
}
/*  ��ͼ�񻺳����ڵ��ļ��������� */
bool Get_PS_Genchar(uint8_t *GetGenchar,int buffer_id){
	
	//д�뻺������
	GetGenchar[10]=buffer_id;
	//����У����
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
	//�жϽ��հ����������Ժ����̹���
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
		//����У��ʧ��
	//	Set_LED_mood("BLUE",2,5);
		return false;
	}	
}
/*** �ϲ�����(����ģ��)***/
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
		//����У��ʧ��
		return false;
	}	
}
/**(����ָ��ģ��)��ѯָ���Ƿ�ע��**/
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
		//����У��ʧ��
		return false;
	}	
}

/***��ȡģ����Ч����***/
/** ���ڼƻ�ͨ���ڲ�flash�������ݴ洢 **/
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
/**����ģ��**/
bool Get_PS_StoreChar(uint8_t *StoreChar,uint8_t id){
//Get_Ps_ValidTempleteNum(PS_SearchMBBuffer);
	//У��� 
	StoreChar[10]= 1;  //��������
	StoreChar[12]=id;//��ȡ��������id
	uint8_t sum=0x00;
	for(int i=6;i<=12;i++){
		//�ӻ������ĵ�6λ��ʼ�ۼ�
	sum+=StoreChar[i];
	}	
	//����Ч���
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
		//����У��ʧ��
	//	Set_LED_mood("RED",2,3);
		return false;
	}	
}
/**led���� **/
// mood  0    1    2
// mood ���� ����  ��˸
//times ��˸����
void Set_LED_mood(char *led_name,int mood , int times){
	//RGB��ɫ����Э��
uint8_t PS_LEDBuffer[16] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x07,0x3C,0x00,0x00,0x00,0x00,0x00,0x00};
	if(mood==0){//ģʽѡ�� //����
	PS_LEDBuffer[10]=0x04;
	}else if(mood==1){     //����
		PS_LEDBuffer[10]=0x03;
		if(!strcmp(led_name,"RED")){//��ɫѡ��
		PS_LEDBuffer[11]=0x04;
		PS_LEDBuffer[12]=0x04;
		}else if(!strcmp(led_name,"BLUE")){
		PS_LEDBuffer[11]=0x01;
		PS_LEDBuffer[12]=0x01;
		}else if(!strcmp(led_name,"GREEN")){
		PS_LEDBuffer[11]=0x02;
		PS_LEDBuffer[12]=0x02;
		}
	}else if(mood==2){    //��˸
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
HAL_UART_Receive(&huart1,PS_ReceiveBuffer,12,HAL_MAX_DELAY);//ÿ�����ݷ�����ɽ��н��ա�
	                                                          //��Ϊ���ݷ��ͼ�����˲ʱ�Ķ�����Ľ����������ġ�
}                                                             //�ᵼ�½��յ����ݳ�Ϊδ�����յ�����
/*************************ָ��ע�����̿�ʼ***********************/

/*************************ָ��ע�����̽���***********************/
//�Զ���ָ��ע��//

/*          ģ�����ߺ���           */
bool Get_PS_Sleep(uint8_t *PS_SleepBuffer){	

	HAL_UART_Transmit(&huart1,PS_SleepBuffer,12,100);
	//���ݷ��ͺ����ݽ���֮�䲻�ܼ���ʱ����
	HAL_UART_Receive(&huart1,PS_ReceiveBuffer,12,HAL_MAX_DELAY);
	//uint8_t sum =	Check_sum(PS_ReceiveBuffer);
	//��û������ݺ�������֤����������
	if(Check_sum(PS_ReceiveBuffer)==PS_ReceiveBuffer[11]){
	if(PS_ReceiveBuffer[9]==0x00){
		//�����ɹ�
		//�ɹ����ָ��ע��ͼ��
		//Set_LED_mood("BLUE",0,5);
		
		return true;
	
	}else{
		//ͼ����ʧ��
		//ʧ����ʾ
	//	Set_LED_mood("RED",2,5);
		return false;
	}
	
	}else{
		//����У��ʧ��
	//	Set_LED_mood("BLUE",2,5);
		return false;
	}	
}



/* д��Ĵ��� Լ��ָ��ע����� */
/************************* Ӧ�ò�ͨѶ�� ****************************/
//ָ��ע��ƴ�Ӵ���Э��
uint8_t PS_register[19]={0xF1,0x1F,0xE2,0x2E,0xB6,0x6B,0xA8,0x8A,0x00,0x08,0x85,0x00,0x00,0x00,0x00,0x02,0x0D,0x04,0xED};
void Set_register_times(int times){
uint8_t sum=0x00;
sum = PS_register[17]+(uint8_t)times+PS_register[15];
PS_register[18]=(~sum+1);
}

/*********�Զ���ɾ��*********/
//���ɾ��id
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
		//����У��ʧ��
	Set_LED_mood("RED",2,3);
		return false;
	}	

}
//�������ݷ�װ
void TX_data(uint8_t *TX_Data,int length){
if(	HAL_UART_Transmit(&huart1,TX_Data,length,100)!=HAL_OK){
	Set_LED_mood("BLUE",2,3);
}
}
//�������ݷ�װ
void RX_data(uint8_t *RX_Data,int length){
if(		HAL_UART_Receive(&huart1,RX_Data,length,500)!=HAL_OK){
	Set_LED_mood("GREEN",2,3);
}
}
 
