#ifndef __Descr_H
#define __Descr_H

void Get_ctl_length(void);
void DEVICE_Descriptor(void);
void Config_Descriptor(void);
void Set_Config(void);
void String_Descriptor(void);
void Set_Idle(unsigned char Id,unsigned char Len);
char Get_HID_data_x(void);
char Get_HID_data_y(void);
#endif
