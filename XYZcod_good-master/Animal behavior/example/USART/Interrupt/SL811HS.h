#ifndef __SL811HS_H
#define __SL811HS_H


//--------define register----------------------------------------	
#define CS_PORT  GPIO_PA
#define RD_PORT  GPIO_PA
#define WR_PORT  GPIO_PA
#define IRQ_PORT GPIO_PA
#define A0_PORT  GPIO_PD
#define RST_PORT GPIO_PD
#define DACK_PORT GPIO_PD
#define CS_AF  AFIO_PIN_15
#define RD_AF  AFIO_PIN_14
#define WR_AF  AFIO_PIN_11
#define IRQ_AF AFIO_PIN_10
#define A0_AF  AFIO_PIN_1
#define RST_AF AFIO_PIN_2
#define DACK_AF AFIO_PIN_3

#define CS_HT_PORT  HT_GPIOA
#define RD_HT_PORT  HT_GPIOA
#define WR_HT_PORT  HT_GPIOA
#define IRQ_HT_PORT  HT_GPIOA
#define A0_HT_PORT  HT_GPIOD
#define RST_HT_PORT  HT_GPIOD
#define DACK_HT_PORT HT_GPIOD
#define CS_GP  GPIO_PIN_15
#define RD_GP  GPIO_PIN_14
#define WR_GP  GPIO_PIN_11
#define IRQ_GP GPIO_PIN_10
#define A0_GP  GPIO_PIN_1
#define RST_GP GPIO_PIN_2
#define DACK_GP GPIO_PIN_3

#define D7_PORT GPIO_PB
#define D6_PORT GPIO_PB
#define D5_PORT GPIO_PB
#define D4_PORT GPIO_PB
#define D3_PORT GPIO_PB
#define D2_PORT GPIO_PB
#define D1_PORT GPIO_PB
#define D0_PORT GPIO_PB
#define D7_AF AFIO_PIN_7
#define D6_AF AFIO_PIN_6
#define D5_AF AFIO_PIN_5
#define D4_AF AFIO_PIN_4
#define D3_AF AFIO_PIN_3
#define D2_AF AFIO_PIN_2
#define D1_AF AFIO_PIN_1
#define D0_AF AFIO_PIN_0

#define D7_HT_PORT HT_GPIOB
#define D6_HT_PORT HT_GPIOB
#define D5_HT_PORT HT_GPIOB
#define D4_HT_PORT HT_GPIOB
#define D3_HT_PORT HT_GPIOB
#define D2_HT_PORT HT_GPIOB
#define D1_HT_PORT HT_GPIOB
#define D0_HT_PORT HT_GPIOB
#define D7_GP GPIO_PIN_7
#define D6_GP GPIO_PIN_6
#define D5_GP GPIO_PIN_5
#define D4_GP GPIO_PIN_4
#define D3_GP GPIO_PIN_3
#define D2_GP GPIO_PIN_2
#define D1_GP GPIO_PIN_1
#define D0_GP GPIO_PIN_0

#define myTime 5
//---------------------------------

#define		cs(x)			if(x==1){ CS_HT_PORT->DOUTR		|= CS_GP;		Delay(myTime);}else{ CS_HT_PORT->DOUTR		&= ~CS_GP;		Delay(myTime);}
#define		rd(x)			if(x==1){ RD_HT_PORT->DOUTR		|= RD_GP;		Delay(myTime);}else{ RD_HT_PORT->DOUTR		&= ~RD_GP;		Delay(myTime);}
#define		wr(x)			if(x==1){ WR_HT_PORT->DOUTR		|= WR_GP;		Delay(myTime);}else{ WR_HT_PORT->DOUTR		&= ~WR_GP;		Delay(myTime);}
#define		intrq(x)	if(x==1){ IRQ_HT_PORT->DOUTR	|= IRQ_GP;	Delay(myTime);}else{ IRQ_HT_PORT->DOUTR	&= ~IRQ_GP;		Delay(myTime);}
#define		a0(x)			if(x==1){ A0_HT_PORT->DOUTR		|= A0_GP;		Delay(myTime);}else{ A0_HT_PORT->DOUTR		&= ~A0_GP;		Delay(myTime);}
#define		rst(x)		if(x==1){ RST_HT_PORT->DOUTR	|= RST_GP;	Delay(myTime);}else{ RST_HT_PORT->DOUTR	&= ~RST_GP;		Delay(myTime);}
#define		dack(x)		if(x==1){ DACK_HT_PORT->DOUTR	|= DACK_GP;	Delay(myTime);}else{ DACK_HT_PORT->DOUTR	&= ~DACK_GP;	Delay(myTime);}

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
extern unsigned char host_data,speed,deviceaddr;
extern unsigned char endpoint;
extern unsigned char datatogglein,datatoggleout;
extern unsigned char ctl_length;
extern unsigned char HID_IN_endpoint;
//---------------------------------------
extern void host_port(unsigned char data);
extern void read_host_port(void);
extern void port_inout(int x);
extern void wr_host(unsigned char address, unsigned char wrdata );
extern void rd_host(unsigned char address);
extern void host_reset(void);
extern void host_set(void);
extern void host_go(unsigned char command);
extern void host_init(void);
extern void commandloop(unsigned char command);
extern void setup(unsigned char value1);
extern void in(unsigned char value2);
extern void out(unsigned char value2);

extern void setuppackage(unsigned char v1,unsigned char v2,unsigned char v3,unsigned char v4,
						 unsigned char v5,unsigned char v6,unsigned char v7,unsigned char v8,unsigned char address);
						 
extern void inpackage(unsigned char startaddress,unsigned char length,unsigned char address,unsigned char datatoggle);
extern void outpackage(unsigned char startaddress,unsigned char length,unsigned char address,unsigned char datatoggle);					 
extern void Set_Address(unsigned char newaddress);
extern void Get_Descriptor(unsigned char v1,unsigned char v2,unsigned char v3,unsigned char v4,
						   unsigned char v5,unsigned char v6,unsigned char v7,unsigned char v8);
extern void get_HID_IN_endpoint(void);
extern void SL811_MemTest(void);
extern void read_reg_value(unsigned char address, unsigned char data ,unsigned char enable);
//-----------------------------------------------------------------------------

#endif
