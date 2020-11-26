/*********************************************************************************************************//**
 * @file    main.c
 * @version $Rev:: 216          $
 * @date    $Date:: 2015-04-30 #$
 * @brief   Main program.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2014 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/
// <<< Use Configuration Wizard in Context Menu >>>

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"

/** @addtogroup Project_Template Project Template
  * @{
  */

/** @addtogroup IP_Examples IP
  * @{
  */

/** @addtogroup Example_SK
  * @{
  */

#if 1 
/*********************************************************************************************************//**
  * @brief  Test1: Compiling error, and Stack Overview.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  int i;
	RETARGET_Configuration();
  u8 u32Array[600]; /* Stack overflow. Modify "MDK-ARM/startup_ht32f5xxxx_01.s" */
  u32 u32Sum = 0;
	
  //RETARGET_Configuration();
	for(i=0;i<600;i++)
  {
    u32Array[i] = 1;
    u32Sum += u32Array[i];
  }

  /*  Display Result  */
  printf("u32Sum = %d\r\n", u32Sum);
  printf("Test1 Finish\r\n");
  while (1)
    ;
}
#endif

#if 0 
/*********************************************************************************************************//**
  * @brief  Test2: Hard Fault, clock is disabled before use.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
//  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
//  CKCUClock.Bit.AFIO       = 1;
//  CKCUClock.Bit.PB         = 1;
//  CKCU_PeripClockConfig(CKCUClock, ENABLE);
  
	RETARGET_Configuration();
	//AFIO_GPxConfig(GPIO_PB,AFIO_PIN_0,AFIO_FUN_GPIO); //Hard Fault 
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_0, GPIO_DIR_OUT);
  
	/*  Display Result  */   
  printf("Test2 Finish\r\n");
  while (1)
    ;
}
#endif

#if 0 
/*********************************************************************************************************//**
  * @brief  Test3.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  u8 u8Array[] = {0x00,0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};
  u32 *pu32Ptr;
  pu32Ptr = (u32*)&(u8Array[1]);  //Hard Fault : unaligned
  /*  Display Result  */
  RETARGET_Configuration();
  printf("pu32Ptr = 0x%x\r\n", *pu32Ptr);
  printf("Test3 Finish\r\n");
  while (1)
    ;
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
