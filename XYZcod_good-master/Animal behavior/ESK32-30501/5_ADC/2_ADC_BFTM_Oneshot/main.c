/*********************************************************************************************************//**
 * @file    ADC/Potentiometer_ContinuousMode/main.c
 * @version $Rev:: 704          $
 * @date    $Date:: 2016-05-27 #$
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup ADC_Examples ADC
  * @{
  */

/** @addtogroup Potentiometer_ContinuousMode
  * @{
  */


/* Private variables ---------------------------------------------------------------------------------------*/
extern vu32 gPotentiometerLevel;

vu8 gCycleEndOfConversion = FALSE;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  * @details Main program as following
  *  - Configure USART used to output gPotentiometerLevel.
  *  - Enable the NVIC ADC Interrupt
  *  - Enable peripherals clock of ADC, AFIO.
  *  - Set ADC Divider as 64, therefore ADCLK frequency as CK_AHB / 64
  *  - Configure AFIO mode as ADC function.
  *  - ADC configure as Continuous Mode, Conversion Length 1, SubLength 1
  *  - Configure ADC Rank 0 to convert ADC channel n with 1.5 sampling clock.
  *  - Configure Software Trigger as ADC trigger source
  *  - Enable ADC single end of conversion interrupt.
  *    The ADC ISR will store the ADC result into global variable gPotentiometerLevel.
  *  - Software trigger to start continuous mode
  *  - Print gPotentiometerLevel in a infinite loop.
  *
  ***********************************************************************************************************/
int main(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	CKCU_ClocksTypeDef sysclk;
	
	/*
	  ADC-Continuous : ESK32-2x001, VR -> ESK32-30501, PA6 -> CH6
	
	  BFTM : 0.1 sec
		
	  Retarget: COM1
	
		Try it:
		
	*/

  RETARGET_Configuration();           /* Retarget Related configuration                                     */

  /* Enable the ADC Interrupts                                                                              */
  NVIC_EnableIRQ(ADC_IRQn);

  /* Enable peripheral clock of ADC                                                                         */
  CKCUClock.Bit.AFIO  = 1;
  CKCUClock.Bit.ADC   = 1;
	CKCUClock.Bit.BFTM0 = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* ADCLK frequency is set to 48/64 MHz = 0.75MHz                                                         */
  CKCU_SetADCPrescaler(CKCU_ADCPRE_DIV64);

  /* Config AFIO mode as ADC function                                                                       */
  AFIO_GPxConfig(HTCFG_VR_GPIO_ID, HTCFG_VR_AFIO_PIN, AFIO_FUN_ADC);

  /* Continuous Mode, Length 1, SubLength 0                                                                 */
  ADC_RegularGroupConfig(HT_ADC, ONE_SHOT_MODE, 1, 0);

  /* ADC Channel n, Rank 0, Sampling clock is (1.5 + 0) ADCLK
     Conversion time = (sampling clock + 12.5) / ADCLK = 12.4 uS */
  ADC_RegularChannelConfig(HT_ADC, HTCFG_VR_ADC_CH, 0);

  /* Use Software Trigger as ADC trigger source                                                             */
  ADC_RegularTrigConfig(HT_ADC, ADC_TRIG_BFTM0);

  /* Enable ADC single end of conversion interrupt,
     The ADC ISR will store the ADC result into global variable gPotentiometerLevel. */
  ADC_IntConfig(HT_ADC, ADC_INT_SINGLE_EOC, ENABLE);	
	
	ADC_Cmd(HT_ADC, ENABLE);

  /* BFTM0 Configuration */
  CKCU_GetClocksFrequency(&sysclk);
	
  BFTM_SetCompare(HT_BFTM0, sysclk.HCLK_Freq / 10);  
  BFTM_SetCounter(HT_BFTM0, 0);
	BFTM_OneShotModeCmd(HT_BFTM0, ENABLE);
  BFTM_EnaCmd(HT_BFTM0, ENABLE); 
	
	while (1)
  {
    if(gCycleEndOfConversion)
    {
			gCycleEndOfConversion = FALSE;
			BFTM_ClearFlag(HT_BFTM0); 			
			printf("\rPotentiometer level is %d %%  ", (int)gPotentiometerLevel);
			
			BFTM_EnaCmd(HT_BFTM0, ENABLE); 
		}
    
  }
}

#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
  }
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
