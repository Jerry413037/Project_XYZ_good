#include "SL811HS.h"
#include "ht32.h"
#include "Delay.h"
#include "Descr.h"
void Get_ctl_length(void)
{
	Get_Descriptor(0x80,0x06,0x00,0x01,0x00,0x00,0x08,0x00);		//get device Descriptor
}
void DEVICE_Descriptor(void)
{
	Get_Descriptor(0x80,0x06,0x00,0x01,0x00,0x00,0x12,0x00);		//get device Descriptor
}
void Config_Descriptor(void)
{
	Get_Descriptor(0x80,0x06,0x00,0x02,0x00,0x00,0x09,0x00);	//get Configuration Descriptor
	rd_host(0x32);												//get Configuration Descriptor TotalLength:
	Get_Descriptor(0x80,0x06,0x00,0x02,0x00,0x00,host_data,0x00);
}
void Set_Config(void)
{
	setuppackage(0x00,0x09,0x01,0x00,0x00,0x00,0x00,0x00,deviceaddr);	//set config
	inpackage(0x30,0,deviceaddr,data1);
}
void String_Descriptor(void)
{
	Get_Descriptor(0x80,0x06,0x02,0x03,0x09,0x04,0x04,0x00);		//get String iProduct
	Get_Descriptor(0x80,0x06,0x02,0x03,0x09,0x04,0x2A,0x00);		//get String iProduct
	Get_Descriptor(0x80,0x06,0x02,0x03,0x09,0x04,0x04,0x00);		//get String iProduct
	Get_Descriptor(0x80,0x06,0x02,0x03,0x09,0x04,0x2A,0x00);		//get String iProduct
}
void Set_Idle(unsigned char Id,unsigned char Len)
{
	setuppackage(0x21,0x0A,0x00,0x00,Id,0x00,0x00,0x00,deviceaddr);	//Set Idle
	inpackage(0x30,0,deviceaddr,data1);
	
	Get_Descriptor(0x81,0x06,0x00,0x22,Id,0x00,Len,0x00);		//Get Report
}

char Get_HID_data_x(void)
{
	unsigned char x_data,y_data;
	int i=0;
	while(1)
	{
		endpoint=HID_IN_endpoint;
		//endpoint = 2;
		for(i=0;i<64;i++)
			wr_host(0x30+i,0);
		
		inpackage(0x30,0x40,deviceaddr,data0);//0x40  64 byte
		
		rd_host(4+0x30);  //x axis
		x_data=host_data;
		
		rd_host(6+0x30);	//y axis
		y_data=host_data;

		if(x_data!=0x00 && y_data!=0x00)
		{
			break;
		}
	}
	return x_data;
}

char Get_HID_data_y(void)
{
	unsigned char x_data,y_data;
	int i=0;
	while(1)
	{
		endpoint=HID_IN_endpoint;
		//endpoint = 2;
		for(i=0;i<64;i++)
			wr_host(0x30+i,0);
		
		inpackage(0x30,0x40,deviceaddr,data0);//0x40  64 byte
		
		rd_host(4+0x30);  //x axis
		x_data=host_data;
		
		rd_host(6+0x30);	//y axis
		y_data=host_data;

		if(x_data!=0x00 && y_data!=0x00)
		{
			break;
		}
	}
	return y_data;
}
