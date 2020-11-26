/*********************************************************************************************************//**
 * @file    USART/Interrupt/main.c
 * @version $Rev:: 4727         $
 * @date    $Date:: 2020-04-07 #$
 * @brief   Main program.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "ht32f5xxxx_pwrcu.h"
#include "string.h"
#include "stdlib.h"
#include "SL811HS.h"
#include "SL811HS_1.h"
#include "Delay.h"
#include "Descr.h"
#include "Descr_1.h"


#define Baud_rate 115200
#define Array_size 128
#define ack_time 1500
#define data_transfer_time 100
#define ASCII_Format_data_size 5000
#define Cut_delay 200
#define data_num_p 1
#define Make_datapackage 100
/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USART_Examples USART
  * @{
	
  */

/** @addtogroup Interrupt
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void UxART_Configuration(void);
void UxART_TxTest(void);
void UxART_RxTest(void);
void RTC_Configuration(void);
void Time_Display(u32 wTimeVar);
void USB_HOST_SET_1(void);
void USB_HOST_SET_2(void);
int ACSII_format_PC(int ,int ,int ,int ,int ,int ,int ,int ,int ,int );
int ACSII_format_UART(int ,int ,int ,int ,int ,int ,int ,int ,int ,int );
/* Global variables ----------------------------------------------------------------------------------------*/
uc8  *gURTx_Ptr;
vu32 gURTx_Length = 0;
u8  *gURRx_Ptr;
vu32 gURRx_Length = 0;
vu32 gIsTxFinished = FALSE;
unsigned char* input;
vu32 gwTimeDisplay = 0;
u32 TimeReg = 0;
unsigned char length,length_1;
/* Private variables ---------------------------------------------------------------------------------------*/

u8 gTx_Buffer[128];//def
u8 gRx_Buffer[128];
u8 Timer_buf[90];
u8 acsii_all[128]="";

/* Global functions ----------------------------------------------------------------------------------------*/
//void Delayms(unsigned long);
void AT_commandinit(void);	
void AT_Time(void);
void AT_MQTT(int);
void NBiot_check(void);
void NBiot_TIMER(void);
void char_combine(unsigned char*);
int acsii(char c);
void cmd_to_acsii(u8*, uint32_t, uint8_t*);
int count=1; 
int  Year=1,Month=1,Day=1,Hour=1,Minute=0,Second=0;
int clean_flag,MQTT_status=0,check_error=0;
char acsii_f[ASCII_Format_data_size]={0};
int ID=1;
int status_dataform=0;//conf_data;
int data_num=data_num_p;
char  f_ID[2],f_Year[2],f_Month[2],f_Day[2],f_Hour[2],f_Minute[2],f_Second[2],f_X[3],f_Y[3],f_Z[2];
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
	uint8_t local_time_len;
	char buffer[40]={0};
	char *local_time;
	u32 i=0;
	int len;
	int x[data_num_p],y[data_num_p],z[data_num_p];
	//PC13 switch key
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
	CKCUClock.Bit.PC = 1;
	CKCU_PeripClockConfig(CKCUClock, ENABLE); 
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_13, GPIO_DIR_IN);		
	GPIO_InputConfig(HT_GPIOC, GPIO_PIN_13, ENABLE);
	
	gURRx_Ptr = gRx_Buffer;
	UxART_Configuration();

	//AT_commandinit();
	AT_Time();
	
	data_num=data_num_p;
	USB_HOST_SET_1();
	Delayms(1000);
	USB_HOST_SET_2();
	Delayms(1000);
	while(1){
		for(i=0;i<data_num_p;i++){
			z[i]=Get_HID_data_Z();
			//printf("Z : %x\r\n",z[i]);
			Delayms(50);
			
			x[i]=Get_HID_data_x();
			//printf("X : %x\r\n",x[i]);
			//Delay(550);
			
			y[i]=Get_HID_data_y();
			//printf("Y : %x\r\n",y[i]);
			//Delay(550);

		}
		Delayms(200);
		status_dataform=0;
		check_error=0;
			if(GPIO_ReadInBit(HT_GPIOC,GPIO_PIN_13)!=SET){//PC
				for(i=0;i<data_num_p;i++)
					len=ACSII_format_UART(1,Year ,Month ,Day ,Hour ,Minute,Second, x[i],y[i],z[i]);
			}
			else{
				for(i=0;i<data_num_p;i++)
					len=ACSII_format_PC(1,1,1,1,1,1,1, x[i],y[i],z[i]);
			}
		if(GPIO_ReadInBit(HT_GPIOC,GPIO_PIN_13)!=SET)//PC
			AT_MQTT(len);
		else																			//MQTT
			printf("%s",acsii_f);
		memset(acsii_f,NULL,ASCII_Format_data_size);
	}
	while(1){};
}




/*************************************************************************************************************
  * @brief  Configure the UxART
  * @retval None
  ***********************************************************************************************************/
void UxART_Configuration(void)
{
  {
   /* Enable peripheral clock of AFIO, UxART                                                               */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.AFIO                   = 1;
		CKCUClock.Bit.BKP        = 1;
		CKCUClock.Bit.PA=1;
		CKCUClock.Bit.PB=1;
		CKCUClock.Bit.PC=1;
		CKCUClock.Bit.PD=1;
    CKCUClock.Bit.HTCFG_UART_RX_GPIO_CLK = 1;
    CKCUClock.Bit.HTCFG_UART_IPN         = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
		#if (!LIBCFG_NO_PWRCU_TEST_REG)
    if (PWRCU_CheckReadyAccessed() != PWRCU_OK)
    {
      while (1);
    }
  #endif
  }

  /* Turn on UxART Rx internal pull up resistor to prevent unknow state                                     */
  GPIO_PullResistorConfig(HTCFG_UART_RX_GPIO_PORT, HTCFG_UART_RX_GPIO_PIN, GPIO_PR_UP);

  /* Config AFIO mode as UxART function.                                                                    */
  AFIO_GPxConfig(HTCFG_UART_TX_GPIO_ID, HTCFG_UART_TX_AFIO_PIN, AFIO_FUN_USART_UART);
  AFIO_GPxConfig(HTCFG_UART_RX_GPIO_ID, HTCFG_UART_RX_AFIO_PIN, AFIO_FUN_USART_UART);

  {
    /* UxART configured as follow:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - None parity bit
    */
    USART_InitTypeDef USART_InitStructure = {0};
    USART_InitStructure.USART_BaudRate = Baud_rate;
    USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
    USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
    USART_InitStructure.USART_Parity = USART_PARITY_NO;
    USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
    USART_Init(HTCFG_UART_PORT, &USART_InitStructure);
  }

  /* Enable UxART interrupt of NVIC                                                                         */
  NVIC_EnableIRQ(HTCFG_UART_IRQn);

  /* Enable UxART Rx interrupt                                                                              */
  USART_IntConfig(HTCFG_UART_PORT, USART_INT_RXDR, ENABLE);

  /* Enable UxART Tx and Rx function                                                                        */
  USART_TxCmd(HTCFG_UART_PORT, ENABLE);
  USART_RxCmd(HTCFG_UART_PORT, ENABLE);
}

void USB_HOST_SET_1()
{
	GPIO_DirectionConfig(CS_HT_PORT, CS_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(RD_HT_PORT, RD_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(WR_HT_PORT, WR_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(IRQ_HT_PORT, IRQ_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(A0_HT_PORT, A0_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(RST_HT_PORT, RST_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(DACK_HT_PORT, DACK_GP, GPIO_DIR_OUT);
	
	host_init();
	ctl_length=8;
 	Get_ctl_length();
	rd_host(0x37);
	Delay(10);
	ctl_length=host_data;
	Set_Address(1);
	DEVICE_Descriptor();
	Config_Descriptor();
	rd_host(0x32);
	length=host_data;
	get_HID_IN_endpoint();
	Set_Config();
}

void USB_HOST_SET_2()
{
	GPIO_DirectionConfig(CS1_HT_PORT, CS1_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(RD1_HT_PORT, RD1_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(WR1_HT_PORT, WR1_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(IRQ1_HT_PORT, IRQ1_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(A01_HT_PORT, A01_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(RST1_HT_PORT, RST1_GP, GPIO_DIR_OUT);
	GPIO_DirectionConfig(DACK1_HT_PORT, DACK1_GP, GPIO_DIR_OUT);
	host_init_1();
	ctl_length_1=8;
 	Get_ctl_length_1();
	rd_host_1(0x37);
	Delay(10);
	ctl_length_1=host_data_1;
	Set_Address_1(2);
	DEVICE_Descriptor_1();
	Config_Descriptor_1();
	rd_host_1(0x32);
	length_1=host_data_1;
	get_HID_IN_endpoint_1();
	Set_Config_1();
}

/*void Delayms(unsigned long Time){
	unsigned long i;
	while(Time--){
		for(i=0;i<12000;i++); 
	}
}*/

//Initialized AT_command
void AT_commandinit(void){
	printf("AT\r\n");
	Delayms(ack_time);
	printf("AT+CPIN?\r\n");
	Delayms(ack_time);
	printf("AT+CFUN=0\r\n");
	Delayms(10000);
	printf("AT*MCGDEFCONT=\"IP\",\"internet.iot\"\r\n");
	Delayms(ack_time);
	printf("AT+CFUN=1\r\n");
	Delayms(ack_time);
	printf("AT+COPS=1,2,\"46601\"\r\n");
	Delayms(ack_time);
	printf("AT+CBAND=8,28\r\n");
	Delayms(ack_time);
	printf("AT+CSQ\r\n");
	Delayms(ack_time);
	printf("AT+COPS?\r\n");
	Delayms(ack_time);
}
//get Time from Base stand
void AT_Time(void){
	printf("AT+GMR\r\n");
	Delayms(ack_time);
	printf("AT+CTZR=1\r\n");
	Delayms(ack_time);
	printf("AT+CTZU=1\r\n");
	NBiot_check();
	printf("AT+CRESET\r\n");
	Delayms(ack_time);
	printf("AT+CGREG?\r\n");
	NBiot_check();
	printf("AT+CCLK?\r\n");
	NBiot_TIMER();
}
//New MQTT
void AT_MQTT(int datalen){
	printf("AT+CMQDISCON=0\r\n");
	MQTT_status=1;
	memset(gURRx_Ptr,NULL,gURRx_Length);
	gURRx_Length=0;
	//if(MQTT_status==1){
		printf("AT+CMQNEW=\"61.58.248.108\",\"1883\",30000,1000\r\n");
		NBiot_check();
	//}
	//if(MQTT_status==2){
		printf("AT+CMQCON=0,3,\"client_Jerry\",10,1,0\r\n");
		NBiot_check();
	//}
	//if(MQTT_status==3){
		printf("AT+CMQPUB=0,\"/test/\",1,0,0,%d,",datalen);
		printf("\"%s\"\r\n",acsii_f);
	//}
	

//	printf("AT+CMQDISCON=0\r\n");
//	NBiot_check();
//	printf("AT+CMQNEW=\"megahouse.nctu.me\",\"1883\",30000,1000\r\n");//megahouse.nctu.me    52.79.120.231 61.58.248.108 140.130.35.239
//	NBiot_check();
//	printf("AT+CMQCON=0,3,\"client_Jerry\",10,1,0\r\n");
//	NBiot_check();
//	printf("AT+CMQPUB=0,\"/test/\",1,0,0,%d,",datalen);
//	printf("\"%s\"\r\n",acsii_f);
}

//NBiot char analysis------------------------------------------------
void NBiot_check(void){
	int status_ACK;
	Delayms(500);
//	if(strcmp(gURRx_Ptr,"AT+CRESET\r")==0 && MQTT_status==10){
//		do{
//			printf("AT\r\n");
//			MQTT_status=0;
//			Delayms(ack_time);
//		}while(strcmp(gURRx_Ptr,"AT\r\r\nOK\r\n")==0);
//	}
//	if(gURRx_Ptr[gURRx_Length-3]=='K'	&&	MQTT_status==1){
//		MQTT_status=2;
//	}
//	else	if(MQTT_status==1){
//		check_error++;
//	}
//	if(gURRx_Ptr[gURRx_Length-3]=='K'	&&	MQTT_status==2){
//		MQTT_status=3;
//	}
//	else if(MQTT_status==2){
//		check_error++;
//	}
	
	memset(gURRx_Ptr,NULL,gURRx_Length);
	gURRx_Length=0;
}

void NBiot_TIMER(void){
	int pt,num=0;
	char *cc_buf;
	Delayms(3000);
	for(pt=0;pt<gURRx_Length;pt++){
		Timer_buf[num++]=gURRx_Ptr[pt];
	}
	num=0;
	Year =(Timer_buf[num+18]-'0')*10+(Timer_buf[num+19]-'0'); // Set Year
	Month  = (Timer_buf[num+21]-'0')*10+(Timer_buf[num+22]-'0');   // Set Month
	Day    = (Timer_buf[num+24]-'0')*10+(Timer_buf[num+25]-'0');   // Set Day
	Hour   = (Timer_buf[num+27]-'0')*10+(Timer_buf[num+28]-'0'+8);   // Set Hour
	Minute = (Timer_buf[num+30]-'0')*10+(Timer_buf[num+31]-'0');   // Set Minute
	Second = (Timer_buf[num+33]-'0')*10+(Timer_buf[num+34]-'0');    // Set Second
	
	memset(Timer_buf,NULL,num);
	gURRx_Length=0;
}
//---------------PC package make----------------------
int ACSII_format_PC(int ID,int year,int mon,int day,int hour, int min,int sec,int x,int y,int z){
	int i,j;
	char format_ascii[1000]={0};
	if(status_dataform==0){
		memset(acsii_f,NULL,ASCII_Format_data_size);
		status_dataform=1;
		sprintf(format_ascii,"!");//{\n ;
		strcat(acsii_f,format_ascii);
	}
	else{
		sprintf(format_ascii,"!");//,
		strcat(acsii_f,format_ascii);
	}
	if(sec>=60){
		sec=0;
		Second=0;
		min++;
		Minute++;
		if(min>=60){
			min=Minute=0;
			Hour++;
			hour++;
			if(hour>=24){
				hour=0;
				Hour=0;
				day++;
				Day++;
			}
		}
	}
	if(hour>=24){
				hour=Hour=0;
				day++;
				Day++;
	}
	Delayms(Make_datapackage);
	sprintf(format_ascii,"%02d,",ID);//ID
	strcat(acsii_f,format_ascii);
	sprintf(format_ascii,"20%02d-%02d-%02d %02d:%02d:%02d,",year,mon,day,hour,min,sec);
	strcat(acsii_f,format_ascii);
	snprintf(format_ascii,sizeof(acsii_f),"%03d,",x);
	strcat(acsii_f,format_ascii);
	snprintf(format_ascii,sizeof(acsii_f),"%03d,",y);
	strcat(acsii_f,format_ascii);
	sprintf(format_ascii,"%02d",z);
	strcat(acsii_f,format_ascii);
	data_num--; 
	if(data_num==0){
		sprintf(format_ascii,"]");//\n }
		strcat(acsii_f,format_ascii);
		data_num=data_num_p;
	}
	Second++;
	return strlen(acsii_f);
}
//--------------------------------------

//----------------UART package make-------------------
int ACSII_format_UART(int ID,int year,int mon,int day,int hour, int min,int sec,int x,int y,int z){
	int i,j;
	char format_ascii[1000]={0};
	if(status_dataform==0){
		memset(acsii_f,NULL,ASCII_Format_data_size);
		status_dataform=1;
		sprintf(format_ascii,"5b0a20");//{\n ;
		strcat(acsii_f,format_ascii);
	}
	else{
		sprintf(format_ascii,"2c0a20");//,
		strcat(acsii_f,format_ascii);
	}
	if(sec>=60){
		sec=0;
		Second=0;
		min++;
		Minute++;
		if(min>=60){
			min=Minute=0;
			Hour++;
			hour++;
			if(hour>=24){
				hour=0;
				Hour=0;
				day++;
				Day++;
			}
		}
	}
	if(hour>=24){
				hour=Hour=0;
				day++;
				Day++;
	}
	Delayms(Make_datapackage);
	f_ID[0]=ID+'0';
	f_Year[0]=year/10+'0';
	f_Year[1]=year%10+'0';
	f_Month[0]=mon/10+'0';
	f_Month [1]=mon%10+'0';
	f_Day[0]=Day/10+'0';
	f_Day[1]=Day%10+'0';
	f_Hour[0]=hour/10+'0';
	f_Hour[1]=hour%10+'0';
	f_Minute[0]=min/10+'0';
	f_Minute[1]=min%10+'0';
	f_Second[0]=sec/10+'0';
	f_Second[1]=sec%10+'0';
	f_X[2]=x/100+'0';
	f_X[1]=x/10%10+'0';
	f_X[0]=x%10+'0';
	f_Y[2]=y/100+'0';
	f_Y[1]=y/10%10+'0';
	f_Y[0]=y%10+'0';
	f_Z[1]=z/10+'0';
	f_Z[0]=z%10+'0';
	sprintf(format_ascii,"7b");//{
	strcat(acsii_f,format_ascii);
	sprintf(format_ascii,"0a20224944223a2022%02x222c0a",f_ID[0]);//ID
	strcat(acsii_f,format_ascii);
	snprintf(format_ascii,sizeof(acsii_f),"2022585f61786973223a2022%02x%02x%02x222c0a",f_X[2],f_X[1],f_X[0]);
	strcat(acsii_f,format_ascii);
	snprintf(format_ascii,sizeof(acsii_f),"2022595f61786973223a2022%02x%02x%02x222c0a",f_Y[2],f_Y[1],f_Y[0]);
	strcat(acsii_f,format_ascii);
	sprintf(format_ascii,"20225a5f61786973223a2022%02x%02x220a207d",f_Z[1],f_Z[0]);
	strcat(acsii_f,format_ascii);
	data_num--;
	if(data_num==0){
		sprintf(format_ascii,"0a5d");//\n }
		strcat(acsii_f,format_ascii);
		data_num=data_num_p;
		Delayms(Make_datapackage);
	}
	Second++;
	return strlen(acsii_f);
}




#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
  }
}
#endif


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
