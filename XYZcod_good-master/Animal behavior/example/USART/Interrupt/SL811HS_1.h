#ifndef __SL811HS_1_H
#define __SL811HS_1_H


//--------define register----------------------------------------	
#define CS1_PORT  GPIO_PC
#define RD1_PORT  GPIO_PC
#define WR1_PORT  GPIO_PB
#define IRQ1_PORT  GPIO_PD
#define A01_PORT  GPIO_PB
#define RST1_PORT  GPIO_PC
#define DACK1_PORT GPIO_PC
#define CS1_AF   AFIO_PIN_11
#define RD1_AF   AFIO_PIN_10
#define WR1_AF   AFIO_PIN_15
#define IRQ1_AF   AFIO_PIN_0
#define A01_AF   AFIO_PIN_8
#define RST1_AF   AFIO_PIN_8
#define DACK1_AF  AFIO_PIN_9

#define CS1_HT_PORT  HT_GPIOC
#define RD1_HT_PORT  HT_GPIOC
#define WR1_HT_PORT  HT_GPIOB
#define IRQ1_HT_PORT HT_GPIOD
#define A01_HT_PORT  HT_GPIOB
#define RST1_HT_PORT HT_GPIOC
#define DACK1_HT_PORT HT_GPIOC
#define CS1_GP  GPIO_PIN_11
#define RD1_GP  GPIO_PIN_10
#define WR1_GP  GPIO_PIN_15
#define IRQ1_GP  GPIO_PIN_0
#define A01_GP  GPIO_PIN_8
#define RST1_GP  GPIO_PIN_8
#define DACK1_GP GPIO_PIN_9

#define D71_PORT GPIO_PA
#define D61_PORT GPIO_PA
#define D51_PORT GPIO_PC
#define D41_PORT GPIO_PC
#define D31_PORT GPIO_PC
#define D21_PORT GPIO_PC
#define D11_PORT GPIO_PC
#define D01_PORT GPIO_PC
#define D71_AF AFIO_PIN_7
#define D61_AF AFIO_PIN_6
#define D51_AF AFIO_PIN_5
#define D41_AF AFIO_PIN_4
#define D31_AF AFIO_PIN_3
#define D21_AF AFIO_PIN_2
#define D11_AF AFIO_PIN_1
#define D01_AF AFIO_PIN_0

#define D71_HT_PORT HT_GPIOA
#define D61_HT_PORT HT_GPIOA
#define D51_HT_PORT HT_GPIOC
#define D41_HT_PORT HT_GPIOC
#define D31_HT_PORT HT_GPIOC
#define D21_HT_PORT HT_GPIOC
#define D11_HT_PORT HT_GPIOC
#define D01_HT_PORT HT_GPIOC
#define D71_GP GPIO_PIN_7
#define D61_GP GPIO_PIN_6
#define D51_GP GPIO_PIN_5
#define D41_GP GPIO_PIN_4
#define D31_GP GPIO_PIN_3
#define D21_GP GPIO_PIN_2
#define D11_GP GPIO_PIN_1
#define D01_GP GPIO_PIN_0

#define myTime 5
//---------------------------------

#define		cs1(x)			if(x==1){ CS1_HT_PORT->DOUTR		|= CS1_GP;		Delay(myTime);}else{ CS1_HT_PORT->DOUTR		&= ~CS1_GP;		Delay(myTime);}
#define		rd1(x)			if(x==1){ RD1_HT_PORT->DOUTR		|= RD1_GP;		Delay(myTime);}else{ RD1_HT_PORT->DOUTR		&= ~RD1_GP;		Delay(myTime);}
#define		wr1(x)			if(x==1){ WR1_HT_PORT->DOUTR		|= WR1_GP;		Delay(myTime);}else{ WR1_HT_PORT->DOUTR		&= ~WR1_GP;		Delay(myTime);}
#define		intrq1(x)		if(x==1){ IRQ1_HT_PORT->DOUTR		|= IRQ1_GP;		Delay(myTime);}else{ IRQ1_HT_PORT->DOUTR	&= ~IRQ1_GP;		Delay(myTime);}
#define		a01(x)			if(x==1){ A01_HT_PORT->DOUTR		|= A01_GP;		Delay(myTime);}else{ A01_HT_PORT->DOUTR		&= ~A01_GP;		Delay(myTime);}
#define		rst1(x)			if(x==1){ RST1_HT_PORT->DOUTR		|= RST1_GP;		Delay(myTime);}else{ RST1_HT_PORT->DOUTR	&= ~RST1_GP;		Delay(myTime);}
#define		dack1(x)		if(x==1){ DACK1_HT_PORT->DOUTR	|= DACK1_GP;	Delay(myTime);}else{ DACK1_HT_PORT->DOUTR	&= ~DACK1_GP;	Delay(myTime);}

#define		controlreg			0x00	// control registers
#define		baseaddress			0x01	// base address
#define		baselength			0x02	// base length
#define		pidep				0x03	// write-- pid,device endpoint
#define		usbstatus			0x03	// read--usb status
#define		transfercountreg	0x04	// read--transfer counter register
#define		usbaddress			0x04	// write--usb address
#define		controlreg1			0x05	// control register 1
#define 	intenreg			0x06	// interrpt Enable register
#define		intstatusreg		0x0D	// Interrupt status register
#define		sofcounterl			0x0E	// sof counter low
#define		sofcounterh			0x0F	// sof counter high
//-----------------------------------------------
#define 	outpid		0x10	
#define		inpid		0x90	
#define		setuppid	0xD0	
#define		sofpid		0x50
//-----------------------------------------------
#define		ack			0x01	
#define		error		0x02
#define		timeout		0x04
#define		nak			0x40	
#define		stall		0x80
//-----------------------------------------------------------------
#define		low				0x00	
#define		full			0x20
#define		nodevice		0x40
#define		data0			0x00
#define		data1			0x40
//--------------------------------------------------------
extern unsigned char host_data_1,speed_1,deviceaddr_1;
extern unsigned char endpoint_1;
extern unsigned char datatogglein,datatoggleout;
extern unsigned char ctl_length_1;
extern unsigned char HID_IN_endpoint_1;
//---------------------------------------
extern void host_port_1(unsigned char data);
extern void read_host_port_1(void);
extern void port_inout_1(int x);
extern void wr_host_1(unsigned char address, unsigned char wrdata );
extern void rd_host_1(unsigned char address);
extern void host_reset_1(void);
extern void host_set_1(void);
extern void host_go_1(unsigned char command);
extern void host_init_1(void);
extern void commandloop_1(unsigned char command);
extern void setup_1(unsigned char value1);
extern void in_1(unsigned char value2);
extern void out_1(unsigned char value2);

extern void setuppackage_1(unsigned char v1,unsigned char v2,unsigned char v3,unsigned char v4
						 ,unsigned char v5,unsigned char v6,unsigned char v7,unsigned char v8,unsigned char address);
						 
extern void inpackage_1(unsigned char startaddress,unsigned char length,unsigned char address,unsigned char datatoggle);
extern void outpackage_1(unsigned char startaddress,unsigned char length,unsigned char address,unsigned char datatoggle);					 
extern void Set_Address_1(unsigned char newaddress);
extern void Get_Descriptor_1(unsigned char v1,unsigned char v2,unsigned char v3,unsigned char v4,
						   unsigned char v5,unsigned char v6,unsigned char v7,unsigned char v8);
extern void get_HID_IN_endpoint_1(void);
extern void SL811_MemTest_1(void);
extern void read_reg_value_1(unsigned char address, unsigned char data ,unsigned char enable);
//-----------------------------------------------------------------------------

#endif
