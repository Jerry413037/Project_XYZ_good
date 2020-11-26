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
void LED_Twinkle(void);

void SysClockConfig_8MHz(void);
void SysClockConfig_40MHz(void);

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
  
  /*
	  CKCU     : 48MHz -> 8MHz -> 40MHz
	
	  GPIO-Out : LED1 -> ESK32-30501, PC14
               LED2 -> ESK32-30501, PC15

    Try it:
    
  */

	LED_Configuration();  
  LED_Twinkle();
	
	SysClockConfig_8MHz();
	LED_Configuration();
	LED_Twinkle();
	
	SysClockConfig_40MHz();
	LED_Configuration();
	LED_Twinkle();
	
	while (1);
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

void LED_Twinkle(void)
{
	u32 i, j;
	
	for (j = 0; j < 5; j++)
	{
		GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, RESET);    
		for (i = 0; i < 0x100000; i++);
    
		GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, SET);
		for (i = 0; i < 0x100000; i++);
	}
}

void SysClockConfig_8MHz(void)
{
  CKCU_PLLInitTypeDef PLLInit;
	ErrStatus ClockStatus;

  /* Reset CKCU, SYSCLK = HSI */
  CKCU_DeInit();

  /* Enable HSE */
  CKCU_HSECmd(ENABLE);

  /* Wait until HSE is ready or time-out */
  ClockStatus = CKCU_WaitHSEReady();
  if(ClockStatus == SUCCESS)
  {
    /* PLL configuration */
    PLLInit.ClockSource = CKCU_PLLSRC_HSE;
    PLLInit.CFG = CKCU_PLL_8M_32M;
    PLLInit.BYPASSCmd = DISABLE;
    CKCU_PLLInit(&PLLInit);

    CKCU_PLLCmd(ENABLE);

    /* Wait until PLL is ready */
    while(CKCU_GetClockReadyStatus(CKCU_FLAG_PLLRDY) == RESET);

    /* FLASH wait state configuration */
    FLASH_SetWaitState(FLASH_WAITSTATE_0);  /* FLASH zero wait clock */

    /* HCLK = SYSCLK/4 */
    CKCU_SetHCLKPrescaler(CKCU_SYSCLK_DIV4);

    /* Configure PLL as system clock */
    ClockStatus = CKCU_SysClockConfig(CKCU_SW_PLL);

    if(ClockStatus != SUCCESS)
    {
      while(1);
    }
  }
  else
  {
    /* HSE is failed. User can handle this situation here. */
    while(1);
  }
}

void SysClockConfig_40MHz(void)
{
	CKCU_PLLInitTypeDef PLLInit;
  ErrStatus ClockStatus;

  /* Reset CKCU, SYSCLK = HSI */
  CKCU_DeInit();

  /* Enable HSE */
  CKCU_HSECmd(ENABLE);

  /* Wait until HSE is ready or time-out */
  ClockStatus = CKCU_WaitHSEReady();

  if(ClockStatus == SUCCESS)
  {
    /* PLL configuration, PLLCLK = 40MHz */
    PLLInit.ClockSource = CKCU_PLLSRC_HSE;
    PLLInit.CFG = CKCU_PLL_8M_40M;
    PLLInit.BYPASSCmd = DISABLE;
    CKCU_PLLInit(&PLLInit);

    CKCU_PLLCmd(ENABLE);

    /* Wait until PLL is ready */
    while(CKCU_GetClockReadyStatus(CKCU_FLAG_PLLRDY) == RESET);

    /* FLASH wait state configuration */
    FLASH_SetWaitState(FLASH_WAITSTATE_1);  /* FLASH one wait clock */

    /* HCLK = SYSCLK/1 */
    CKCU_SetHCLKPrescaler(CKCU_SYSCLK_DIV1);

    /* Configure PLL as system clock */
    ClockStatus = CKCU_SysClockConfig(CKCU_SW_PLL);

    if(ClockStatus != SUCCESS)
    {
      while(1);
    }
  }
  else
  {
    /* HSE is failed. User can handle this situation here. */
    while(1);
  }
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
