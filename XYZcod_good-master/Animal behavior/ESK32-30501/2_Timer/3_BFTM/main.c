/*********************************************************************************************************//**
 * @file    IP/Example/main.c
 * @version $Rev:: 971          $
 * @date    $Date:: 2016-09-08 #$
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

/** @addtogroup Example
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
void NVIC_Configuration(void);
void CKCU_Configuration(void);
void GPIO_Configuration(void);
#if (ENABLE_CKOUT == 1)
void CKOUTConfig(void);
#endif

void LED_Configuration(void);

/* Private macro -------------------------------------------------------------------------------------------*/
/* Global variables ----------------------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------------------------------------*/
/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	
  /*
	  Timer: BFTM, 0.5 sec
	  
	  GPIO-Out: LED1 -> ESK32-30501, PC14
	
		Try it:
		1. Time base 1 sec
	 
	*/
  
  LED_Configuration();
	
	CKCUClock.Bit.BFTM0 = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
  
  NVIC_EnableIRQ(BFTM0_IRQn);
	
	BFTM_SetCompare(HT_BFTM0, SystemCoreClock/10 * 5);
  BFTM_SetCounter(HT_BFTM0, 0);
  BFTM_IntConfig(HT_BFTM0, ENABLE);
  BFTM_EnaCmd(HT_BFTM0, ENABLE);	
  
  while (1);

}

void LED_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  
  CKCUClock.Bit.PC   = 1;
  CKCUClock.Bit.AFIO = 1;  
  CKCU_PeripClockConfig(CKCUClock, ENABLE);  
	
  AFIO_GPxConfig(GPIO_PC, AFIO_PIN_14, AFIO_MODE_DEFAULT);
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, SET);
  GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_14, GPIO_DIR_OUT);	
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
