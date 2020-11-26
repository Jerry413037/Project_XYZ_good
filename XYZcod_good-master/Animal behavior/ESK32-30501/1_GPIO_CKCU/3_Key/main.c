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
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
 
  /*
    GPIO-In  : ESK32-2x001, Button1 -> ESK32-30501, PD1
               ESK32-2x001, Button2 -> ESK32-30501, PD2
    
    GPIO-Out : LED1 -> ESK32-30501, PC14
               LED2 -> ESK32-30501, PC15

    Try it:
    1. Key x2
  */
	
	CKCUClock.Bit.PD = 1;
	CKCU_PeripClockConfig(CKCUClock, ENABLE); 
	
	GPIO_DirectionConfig(HT_GPIOD, GPIO_PIN_1, GPIO_DIR_IN);		
	GPIO_InputConfig(HT_GPIOD, GPIO_PIN_1, ENABLE);
	
	LED_Configuration();

  while (1)
	{
		if (GPIO_ReadInBit(HT_GPIOD, GPIO_PIN_1) == SET)
		{
			GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, SET);    // Key released, LED OFF
		}
		else
		{
			GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, RESET);  // Key pressed, LED ON
		}
	}
}

void LED_Configuration(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
	
	CKCUClock.Bit.PC = 1;
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
