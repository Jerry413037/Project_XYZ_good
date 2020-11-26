#include "SL811HS.h"
#include "ht32.h"
#include "ht32_board.h"
#include "Delay.h"
#define myDebug 0x00
//#define USB_DEBUG
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
unsigned char host_data,speed,deviceaddr=0;
unsigned int loopcounter=0;
unsigned char endpoint=0;
unsigned char ctl_length;
unsigned char HID_IN_endpoint;
unsigned char flag=0;
//---------------------------------------------------------------------------------------------
//SL811HS command 
//---------------------------------------------------------------------------------------------

void host_port(unsigned char data){
	if((data&0x80)==0x80){
		D7_HT_PORT->DOUTR |= D7_GP;
	}else{
		D7_HT_PORT->DOUTR &= ~D7_GP;
	}
	data%=128;
	if((data&0x40)==0x40){
		D6_HT_PORT->DOUTR |= D6_GP;
	}else{
		D6_HT_PORT->DOUTR &= ~D6_GP;
	}
	data%=64;
	if((data&0x20)==0x20){
		D5_HT_PORT->DOUTR |= D5_GP;
	}else{
		D5_HT_PORT->DOUTR &= ~D5_GP;
	}
	data%=32;
	if((data&0x10)==0x10){
		D4_HT_PORT->DOUTR |= D4_GP;
	}else{
		D4_HT_PORT->DOUTR &= ~D4_GP;
	}
	data%=16;
	if((data&0x08)==0x08){
		D3_HT_PORT->DOUTR |= D3_GP;
	}else{
		D3_HT_PORT->DOUTR &= ~D3_GP;
	}
	data%=8;
	if((data&0x04)==0x04){
		D2_HT_PORT->DOUTR |= D2_GP;
	}else{
		D2_HT_PORT->DOUTR &= ~D2_GP;
	}
	data%=4;
	if((data&0x02)==0x02){
		D1_HT_PORT->DOUTR |= D1_GP;
	}else{
		D1_HT_PORT->DOUTR &= ~D1_GP;
	}
	data%=2;
	if((data&0x01)==0x01){
		D0_HT_PORT->DOUTR |= D0_GP;
  }else{
		D0_HT_PORT->DOUTR &= ~D0_GP;
	}
	Delay(5);
	
}
void read_host_port(void){
	host_data=0x00;
	if (((D7_HT_PORT->DINR)&GPIO_PIN_7)==D7_GP){
		host_data+=128;
	}
	if (((D6_HT_PORT->DINR)&GPIO_PIN_6)==D6_GP){
		host_data+=64;
	}
	if (((D5_HT_PORT->DINR)&GPIO_PIN_5)==D5_GP){
		host_data+=32;
	}
	if (((D4_HT_PORT->DINR)&GPIO_PIN_4)==D4_GP){
		host_data+=16;
	}
	if (((D3_HT_PORT->DINR)&GPIO_PIN_3)==D3_GP){
		host_data+=8;
	}
	if (((D2_HT_PORT->DINR)&GPIO_PIN_2)==D2_GP){
		host_data+=4;
	}
	if (((D1_HT_PORT->DINR)&GPIO_PIN_1)==D1_GP){
		host_data+=2;
	}
	if (((D0_HT_PORT->DINR)&GPIO_PIN_0)==D0_GP){
		host_data+=1;
	}
	Delay(5);
}
void port_inout(int x){
	if(x==1){
		GPIO_DirectionConfig(D7_HT_PORT, D7_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D6_HT_PORT, D6_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D5_HT_PORT, D5_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D4_HT_PORT, D4_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D3_HT_PORT, D3_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D2_HT_PORT, D2_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D1_HT_PORT, D1_GP, GPIO_DIR_IN);
		GPIO_DirectionConfig(D0_HT_PORT, D0_GP, GPIO_DIR_IN);
		GPIO_PullResistorConfig(D7_HT_PORT, D7_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D6_HT_PORT, D6_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D5_HT_PORT, D5_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D4_HT_PORT, D4_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D3_HT_PORT, D3_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D2_HT_PORT, D2_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D1_HT_PORT, D1_GP, GPIO_PR_UP);
		GPIO_PullResistorConfig(D0_HT_PORT, D0_GP, GPIO_PR_UP);
		GPIO_InputConfig(D7_HT_PORT, D7_GP, ENABLE);
		GPIO_InputConfig(D6_HT_PORT, D6_GP, ENABLE);
		GPIO_InputConfig(D5_HT_PORT, D5_GP, ENABLE);
		GPIO_InputConfig(D4_HT_PORT, D4_GP, ENABLE);
		GPIO_InputConfig(D3_HT_PORT, D3_GP, ENABLE);
		GPIO_InputConfig(D2_HT_PORT, D2_GP, ENABLE);
		GPIO_InputConfig(D1_HT_PORT, D1_GP, ENABLE);
		GPIO_InputConfig(D0_HT_PORT, D0_GP, ENABLE);
	}else{
		GPIO_DirectionConfig(D7_HT_PORT, D7_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D6_HT_PORT, D6_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D5_HT_PORT, D5_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D4_HT_PORT, D4_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D3_HT_PORT, D3_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D2_HT_PORT, D2_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D1_HT_PORT, D1_GP, GPIO_DIR_OUT);
		GPIO_DirectionConfig(D0_HT_PORT, D0_GP, GPIO_DIR_OUT);
	}
	Delay(5);
}
//---------------------------------------------------------------------------------------------
void wr_host(unsigned char address, unsigned char wrdata )  // write(address,data)
{
	cs(0);				// sl811hs cs
	host_port(address);
	a0(0);					// set write address mode
	wr(0);				//wr=0
	wr(1);				//wr=1
	host_port(wrdata);				//
	a0(1);
	wr(0);
	wr(1);
	cs(1);
	host_port(0xff);
}
//---------------------------------------------------------------------------------------------
void rd_host(unsigned char address)//read (data)  return RDDATA value
{
	cs(0);
	host_port(address);Delayus(100);
	a0(0);
	wr(0);
	wr(1);
	host_port(0xff);Delayus(100);
	port_inout(1);
	a0(1);
	rd(0);
	read_host_port();
	rd(1);
	cs(1);
	port_inout(0);
}
//---------------------------------------------------------------------------------------------
void host_reset(void)	//reset USB bus
{
	rd_host(controlreg1);						//sl81shs datasheet page 12
	wr_host(controlreg1,host_data|0x08);
	Delayus(4);	//1000 
	wr_host(controlreg1,host_data);
}
//---------------------------------------------------------------------------------------------
void host_set(void)
{
	cs(0);
	intrq(1);				//always=1
	dack(1);
	rst(1);				// hardware  reset
	Delayus(4);	//1000
	rst(0);
	Delayus(4);	//1000			 
	rst(1);
	cs(1);
}
//---------------------------------------------------------------------------------------------
void host_go(unsigned char command)			// Launch an 811 operation. 
{
	wr_host(intstatusreg,0xff);
	wr_host(controlreg,command);
	do
	{
		rd_host(intstatusreg);
	}
	while((host_data&0x01)==0x00);
	wr_host(intstatusreg,0xff);
	rd_host(usbstatus);
}
//---------------------------------------------------------------------------------------------
void host_init(void)						
{

	host_set();									//set sl811hs

	wr_host(sofcounterh,0xae);	rd_host(sofcounterh);					//SET SOF =1ms

	wr_host(controlreg1,0x08);	rd_host(controlreg1);	
	Delayus(4);
	
	wr_host(controlreg1,0x00);  rd_host(controlreg1);

	wr_host(intenreg,0x61);rd_host(intenreg);

	do
	{
		wr_host(intstatusreg,0xff);
		rd_host(intstatusreg);
	}
	while(host_data==nodevice);					//WAIT DEVICE PLUG IN
	
	//----------------------------------
	if(host_data==0x80)				//full speed
	{
		wr_host(sofcounterl,0xe0);	//set SOF=1ms
		wr_host(sofcounterh,0xae);	//
		wr_host(controlreg1,0x05);	//48mhz sof enable
		speed=full;
	}
	else							//lows peed
	{
		wr_host(sofcounterl,0xe0);	//set SOF=1ms
		wr_host(sofcounterh,0xee);	//		
		wr_host(controlreg1,0x21);	//48mhz sof enable
		speed=low;
	}
	wr_host(pidep,sofpid);				//start SOF and EOF
	wr_host(usbaddress,0x00);
	wr_host(controlreg,0x01);
	Delayus(4);	//1000
	wr_host(intstatusreg,0xff);
	host_reset();

	Delayus(250);	//1000
}
//---------------------------------------------------------------------------------------------
void commandloop(unsigned char command)
{
	loopcounter=0;
	while(1)
	{	
		host_go(command);							//sl811hs datasheet page 11
		if((host_data&timeout)==timeout)			//if time out ,do 1000 times
		{
			if(loopcounter>=1000)
			break;
			else
			loopcounter++;
		}
		//------------------------------
		else if((host_data&ack)==ack)				//ack pass
			break;
		//------------------------------	
	}
}
//---------------------------------------------------------------------------------------------
void setup(unsigned char value1)
{
	commandloop(value1 | 0x07);				//sl811hs datasheet page 10
}
void in(unsigned char value2)
{
	commandloop(value2 | 0x03);
}
void out(unsigned char value2)
{
	commandloop(value2 | 0x07);
}
void setuppackage(unsigned char v1,unsigned char v2,unsigned char v3,unsigned char v4,unsigned char v5,unsigned char v6,unsigned char v7,unsigned char v8,unsigned char address)
{
	wr_host(0x10,v1);        
	wr_host(0x11,v2);
	wr_host(0x12,v3);
	wr_host(0x13,v4);
	wr_host(0x14,v5);
	wr_host(0x15,v6);
	wr_host(0x16,v7);
	wr_host(0x17,v8);
	//-----------------------------
	wr_host(baseaddress,0x10);		//set data start address
	wr_host(baselength,0x08);		//set data length
	wr_host(usbaddress,address);		//set device address
	wr_host(pidep,setuppid|endpoint);
	setup(speed|data0);
}
void inpackage(unsigned char startaddress,unsigned char length,unsigned char address,unsigned char datatoggle)
{
	wr_host(baseaddress,startaddress);		//set data start address
	wr_host(baselength,length);				//set data length
	wr_host(usbaddress,address);				//set device address
	wr_host(pidep,inpid|endpoint);
	in(speed|datatoggle);
}
void outpackage(unsigned char startaddress,unsigned char length,unsigned char address,unsigned char datatoggle)
{
	wr_host(baseaddress,startaddress);		//set data start address
	wr_host(baselength,length);		//set data length
	wr_host(usbaddress,address);		//set device address
	wr_host(pidep,outpid|endpoint);
	out(speed|datatoggle);
}
//---------------------------------------------------------------------------------------------
void Set_Address(unsigned char newaddress)//set_usb address
{
	deviceaddr=newaddress;
	endpoint=0;
	setuppackage(0,5,newaddress,0,0,0,0,0,0);
	inpackage(0x30,0,0,data1);
}
//---------------------------------------------------------------------------------------------
void Get_Descriptor(unsigned char v1,unsigned char v2,unsigned char v3,unsigned char v4,unsigned char v5,unsigned char v6,unsigned char length,unsigned char v8)//use in usb 1.0 or 1.0
{															//in usb 1.1 or 1.0 control each transmit is 8 byte and start is data1 next is data0
	unsigned char i=0,saveaddr=0x30;
	setuppackage(v1,v2,v3,v4,v5,v6,length,v8,deviceaddr);
	//----------------------------------------------------
	while(1)
	{
		if((i%2)==0)inpackage(saveaddr,ctl_length,deviceaddr,data1);
		else		inpackage(saveaddr,ctl_length,deviceaddr,data0);
		saveaddr=saveaddr+ctl_length;
		i++;
		Delay(4);	//100
		if(length<=ctl_length)break;
		else length=length-ctl_length;
	}
	//----------------------------------------------------
	outpackage(0x30,0x00,deviceaddr,data1);
}
//---------------------------------------------------------------------------------------------
void get_HID_IN_endpoint(void)
{
	unsigned char i=0x30;
	while(1)
	{
		rd_host(i);
		if(host_data==0x07)
		{
			rd_host(i+2);
			HID_IN_endpoint=host_data & 0x7f;	
			break;
		}
		else
		i=i+host_data;
   	}
}
void SL811_MemTest(void)
{
	unsigned char value,MemTest_temp;

	// 0x10-0xFF ¦sÀx½w½Ä¾¹ 
	
	for( value = 0x10 ; value < 0xff; value++ )  
	{
		wr_host( value , value );
		Delay(1000);
		rd_host(value);
		printf("%d,%d\r\n",value,host_data);	Delay(1000);
	}
	
	for( value = 0x10 ; value < 0xff; value++ )  
	{
		/*if( value != host_data)
		{
#ifdef USB_DEBUG
			printf("SL811 is error \r\n");
#endif
			return;
		}*/
	}
	
	for( value = 0x10 ; value < 0xff; value++ )  
	{
		wr_host( value , ~value ); 
	}
	
	for( value = 0x10 ; value < 0xff; value++ )  
	{
		MemTest_temp = ~value;
		rd_host(value);
		if(  MemTest_temp != host_data )
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
void read_reg_value(unsigned char address, unsigned char data ,unsigned char  enable){
	if(enable==0xff)
	{
		rd_host(address);	printf(" : 0x%x\r\n",host_data);
	}
}
