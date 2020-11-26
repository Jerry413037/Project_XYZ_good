#include "SL811HS_1.h"
#include "ht32.h"
#include "ht32_board.h"
#include "Delay.h"
#define myDebug 0x00
//#define USB_DEBUG
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
unsigned char host_data_1,speed_1,deviceaddr_1=0;
unsigned int loopcounter_1=0;
unsigned char endpoint_1=0;
unsigned char ctl_length_1;
unsigned char HID_IN_endpoint_1;
unsigned char flag_1=0;
//---------------------------------------------------------------------------------------------
//SL811HS command 
//---------------------------------------------------------------------------------------------

void host_port_1(unsigned char data){
	if((data&0x80)==0x80){
		D71_HT_PORT->DOUTR |= D71_GP;
	}else{
		D71_HT_PORT->DOUTR &= ~D71_GP;
	}
	data%=128;
	if((data&0x40)==0x40){
		D61_HT_PORT->DOUTR |= D61_GP;
	}else{
		D61_HT_PORT->DOUTR &= ~D61_GP;
	}
	data%=64;
	if((data&0x20)==0x20){
		D51_HT_PORT->DOUTR |= D51_GP;
	}else{
		D51_HT_PORT->DOUTR &= ~D51_GP;
	}
	data%=32;
	if((data&0x10)==0x10){
		D41_HT_PORT->DOUTR |= D41_GP;
	}else{
		D41_HT_PORT->DOUTR &= ~D41_GP;
	}
	data%=16;
	if((data&0x08)==0x08){
		D31_HT_PORT->DOUTR |= D31_GP;
	}else{
		D31_HT_PORT->DOUTR &= ~D31_GP;
	}
	data%=8;
	if((data&0x04)==0x04){
		D21_HT_PORT->DOUTR |= D21_GP;
	}else{
		D21_HT_PORT->DOUTR &= ~D21_GP;
	}
	data%=4;
	if((data&0x02)==0x02){
		D11_HT_PORT->DOUTR |= D11_GP;
	}else{
		D11_HT_PORT->DOUTR &= ~D11_GP;
	}
	data%=2;
	if((data&0x01)==0x01){
		D01_HT_PORT->DOUTR |= D01_GP;
  }else{
		D01_HT_PORT->DOUTR &= ~D01_GP;
	}
	Delay(5);
	
}
void read_host_port_1(void){
	host_data_1=0x00;
	if (((D71_HT_PORT->DINR)&GPIO_PIN_7)==D71_GP){
		host_data_1+=128;
	}
	if (((D61_HT_PORT->DINR)&GPIO_PIN_6)==D61_GP){
		host_data_1+=64;
	}
	if (((D51_HT_PORT->DINR)&GPIO_PIN_5)==D51_GP){
		host_data_1+=32;
	}
	if (((D41_HT_PORT->DINR)&GPIO_PIN_4)==D41_GP){
		host_data_1+=16;
	}
	if (((D31_HT_PORT->DINR)&GPIO_PIN_3)==D31_GP){
		host_data_1+=8;
	}
	if (((D21_HT_PORT->DINR)&GPIO_PIN_2)==D21_GP){
		host_data_1+=4;
	}
	if (((D11_HT_PORT->DINR)&GPIO_PIN_1)==D11_GP){
		host_data_1+=2;
	}
	if (((D01_HT_PORT->DINR)&GPIO_PIN_0)==D01_GP){
		host_data_1+=1;
	}
	Delay(5);
}
void port_inout_1(int x){
	if(x==1){
		GPIO_DirectionConfig(D71_HT_PORT, D71_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D61_HT_PORT, D61_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D51_HT_PORT, D51_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D41_HT_PORT, D41_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D31_HT_PORT, D31_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D21_HT_PORT, D21_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D11_HT_PORT, D11_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D01_HT_PORT, D01_GP, GPIO_DIR_IN);
		GPIO_PullResistorConfig(D71_HT_PORT, D71_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D61_HT_PORT, D61_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D51_HT_PORT, D51_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D41_HT_PORT, D41_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D31_HT_PORT, D31_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D21_HT_PORT, D21_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D11_HT_PORT, D11_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D01_HT_PORT, D01_GP, GPIO_PR_UP);
		GPIO_InputConfig(D71_HT_PORT, D71_GP, ENABLE);
		GPIO_InputConfig(D61_HT_PORT, D61_GP, ENABLE);
		GPIO_InputConfig(D51_HT_PORT, D51_GP, ENABLE);
		GPIO_InputConfig(D41_HT_PORT, D41_GP, ENABLE);
		GPIO_InputConfig(D31_HT_PORT, D31_GP, ENABLE);
		GPIO_InputConfig(D21_HT_PORT, D21_GP, ENABLE);
		GPIO_InputConfig(D11_HT_PORT, D11_GP, ENABLE);
		GPIO_InputConfig(D01_HT_PORT, D01_GP, ENABLE);
	}else{
		GPIO_DirectionConfig(D71_HT_PORT, D71_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D61_HT_PORT, D61_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D51_HT_PORT, D51_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D41_HT_PORT, D41_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D31_HT_PORT, D31_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D21_HT_PORT, D21_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D11_HT_PORT, D11_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D01_HT_PORT, D01_GP, GPIO_DIR_OUT);
	}
	Delay(5);
}
//---------------------------------------------------------------------------------------------
void wr_host_1(unsigned char address, unsigned char wrdata )  // write(address,data)
{
	cs1(0);				// sl811hs cs
	host_port_1(address);
	a01(0);					// set write address mode
	wr1(0);				//wr=0
	wr1(1);				//wr=1
	host_port_1(wrdata);				//
	a01(1);
	wr1(0);
	wr1(1);
	cs1(1);
	host_port_1(0xff);
}
//---------------------------------------------------------------------------------------------
void rd_host_1(unsigned char address)//read (data)  return RDDATA value
{
	cs1(0);
	host_port_1(address);Delayus(100);
	a01(0);
	wr1(0);
	wr1(1);
	host_port_1(0xff);Delayus(100);
	port_inout_1(1);
	a01(1);
	rd1(0);
	read_host_port_1();
	rd1(1);
	cs1(1);
	port_inout_1(0);
}
//---------------------------------------------------------------------------------------------
void host_reset_1(void)	//reset USB bus
{
	rd_host_1(controlreg1);						//sl81shs datasheet page 12
	wr_host_1(controlreg1,host_data_1|0x08);
	Delayus(4);	//1000 
	wr_host_1(controlreg1,host_data_1);
}
//---------------------------------------------------------------------------------------------
void host_set_1(void)
{
	cs1(0);
	intrq1(1);				//always=1
	dack1(1);
	rst1(1);				// hardware  reset
	Delayus(4);	//1000
	rst1(0);
	Delayus(4);	//1000			 
	rst1(1);
	cs1(1);
}
//---------------------------------------------------------------------------------------------
void host_go_1(unsigned char command)			// Launch an 811 operation. 
{
	wr_host_1(intstatusreg,0xff);
	wr_host_1(controlreg,command);
	do
	{
		rd_host_1(intstatusreg);
	}
	while((host_data_1&0x01)==0x00);
	wr_host_1(intstatusreg,0xff);
	rd_host_1(usbstatus);
}
//---------------------------------------------------------------------------------------------
void host_init_1(void)						
{

	host_set_1();									//set sl811hs

	wr_host_1(sofcounterh,0xae);	rd_host_1(sofcounterh);					//SET SOF =1ms

	wr_host_1(controlreg1,0x08);	rd_host_1(controlreg1);	
	Delayus(4);
	
	wr_host_1(controlreg1,0x00);  rd_host_1(controlreg1);

	wr_host_1(intenreg,0x61);rd_host_1(intenreg);

	do
	{
		wr_host_1(intstatusreg,0xff);
		rd_host_1(intstatusreg);
	}
	while(host_data_1==nodevice);					//WAIT DEVICE PLUG IN
	
	//----------------------------------
	if(host_data_1==0x80)				//full speed_1
	{
		wr_host_1(sofcounterl,0xe0);	//set SOF=1ms
		wr_host_1(sofcounterh,0xae);	//
		wr_host_1(controlreg1,0x05);	//48mhz sof enable
		speed_1=full;
	}
	else							//lows peed
	{
		wr_host_1(sofcounterl,0xe0);	//set SOF=1ms
		wr_host_1(sofcounterh,0xee);	//		
		wr_host_1(controlreg1,0x21);	//48mhz sof enable
		speed_1=low;
	}
	wr_host_1(pidep,sofpid);				//start SOF and EOF
	wr_host_1(usbaddress,0x00);
	wr_host_1(controlreg,0x01);
	Delayus(4);	//1000
	wr_host_1(intstatusreg,0xff);
	host_reset_1();

	Delayus(250);	//1000
}
//---------------------------------------------------------------------------------------------
void commandloop_1(unsigned char command)
{
	loopcounter_1=0;
	while(1)
	{	
		host_go_1(command);							//sl811hs datasheet page 11
		if((host_data_1&timeout)==timeout)			//if time out ,do 1000 times
		{
			if(loopcounter_1>=1000)
			break;
			else
			loopcounter_1++;
		}
		//------------------------------
		else if((host_data_1&ack)==ack)				//ack pass
			break;
		//------------------------------	
	}
}
//---------------------------------------------------------------------------------------------
void setup_1(unsigned char value1)
{
	commandloop_1(value1 | 0x07);				//sl811hs datasheet page 10
}
void in_1(unsigned char value2)
{
	commandloop_1(value2 | 0x03);
}
void out_1(unsigned char value2)
{
	commandloop_1(value2 | 0x07);
}
void setuppackage_1(unsigned char v1,unsigned char v2,unsigned char v3,unsigned char v4,unsigned char v5,unsigned char v6,unsigned char v7,unsigned char v8,unsigned char address)
{
	wr_host_1(0x10,v1);        
	wr_host_1(0x11,v2);
	wr_host_1(0x12,v3);
	wr_host_1(0x13,v4);
	wr_host_1(0x14,v5);
	wr_host_1(0x15,v6);
	wr_host_1(0x16,v7);
	wr_host_1(0x17,v8);
	//-----------------------------
	wr_host_1(baseaddress,0x10);		//set data start address
	wr_host_1(baselength,0x08);		//set data length
	wr_host_1(usbaddress,address);		//set device address
	wr_host_1(pidep,setuppid|endpoint_1);
	setup_1(speed_1|data0);
}
void inpackage_1(unsigned char startaddress,unsigned char length,unsigned char address,unsigned char datatoggle)
{
	wr_host_1(baseaddress,startaddress);		//set data start address
	wr_host_1(baselength,length);				//set data length
	wr_host_1(usbaddress,address);				//set device address
	wr_host_1(pidep,inpid|endpoint_1);
	in_1(speed_1|datatoggle);
}
void outpackage_1(unsigned char startaddress,unsigned char length,unsigned char address,unsigned char datatoggle)
{
	wr_host_1(baseaddress,startaddress);		//set data start address
	wr_host_1(baselength,length);		//set data length
	wr_host_1(usbaddress,address);		//set device address
	wr_host_1(pidep,outpid|endpoint_1);
	out_1(speed_1|datatoggle);
}
//---------------------------------------------------------------------------------------------
void Set_Address_1(unsigned char newaddress)//set_usb address
{
	deviceaddr_1=newaddress;
	endpoint_1=0;
	setuppackage_1(0,5,newaddress,0,0,0,0,0,0);
	inpackage_1(0x30,0,0,data1);
}
//---------------------------------------------------------------------------------------------
void Get_Descriptor_1(unsigned char v1,unsigned char v2,unsigned char v3,unsigned char v4,unsigned char v5,unsigned char v6,unsigned char length,unsigned char v8)//use in usb 1.0 or 1.0
{															//in usb 1.1 or 1.0 control each transmit is 8 byte and start is data1 next is data0
	unsigned char i=0,saveaddr=0x30;
	setuppackage_1(v1,v2,v3,v4,v5,v6,length,v8,deviceaddr_1);
	//----------------------------------------------------
	while(1)
	{
		if((i%2)==0)inpackage_1(saveaddr,ctl_length_1,deviceaddr_1,data1);
		else		inpackage_1(saveaddr,ctl_length_1,deviceaddr_1,data0);
		saveaddr=saveaddr+ctl_length_1;
		i++;
		Delay(4);	//100
		if(length<=ctl_length_1)break;
		else length=length-ctl_length_1;
	}
	//----------------------------------------------------
	outpackage_1(0x30,0x00,deviceaddr_1,data1);
}
//---------------------------------------------------------------------------------------------
void get_HID_IN_endpoint_1(void)
{
	unsigned char i=0x30;
	while(1)
	{
		rd_host_1(i);
		if(host_data_1==0x07)
		{
			rd_host_1(i+2);
			HID_IN_endpoint_1=host_data_1 & 0x7f;	
			break;
		}
		else
		i=i+host_data_1;
   	}
}
void SL811_MemTest_1(void)
{
	unsigned char value,MemTest_temp;

	// 0x10-0xFF ¦sÀx½w½Ä¾¹ 
	
	for( value = 0x10 ; value < 0xff; value++ )  
	{
		wr_host_1( value , value );
		Delay(1000);
		rd_host_1(value);
		printf("%d,%d\r\n",value,host_data_1);	Delay(1000);
	}
	
	for( value = 0x10 ; value < 0xff; value++ )  
	{
		/*if( value != host_data_1)
		{
#ifdef USB_DEBUG
			printf("SL811 is error \r\n");
#endif
			return;
		}*/
	}
	
	for( value = 0x10 ; value < 0xff; value++ )  
	{
		wr_host_1( value , ~value ); 
	}
	
	for( value = 0x10 ; value < 0xff; value++ )  
	{
		MemTest_temp = ~value;
		rd_host_1(value);
		if(  MemTest_temp != host_data_1 )
		{
#ifdef USB_DEBUG
			printf("SL811 is error \r\n");
#endif
			return;
		}
	}
#ifdef USB_DEBUG
	printf("SL811 is OK \r\n"); 
#endif

}
//---------------------------------------------------------------------------------------------
void read_reg_value_1(unsigned char address, unsigned char data ,unsigned char  enable){
	if(enable==0xff)
	{
		rd_host_1(address);	printf(" : 0x%x\r\n",host_data_1);
	}
}
