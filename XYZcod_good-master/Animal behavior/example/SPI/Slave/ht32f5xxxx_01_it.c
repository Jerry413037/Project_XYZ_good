/*********************************************************************************************************//**
 * @file    SPI/Slave/ht32f5xxxx_01_it.c
 * @version $Rev:: 4000         $
 * @date    $Date:: 2019-07-05 #$
 * @brief   This file provides all interrupt service routine.
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
#include "ht32_board_config.h"
#include "ht32_board.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup SPI_Examples SPI
  * @{
  */

/** @addtogroup Slave
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief   This function handles NMI exception.
 * @retval  None
 ************************************************************************************************************/
void NMI_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Hard Fault exception.
 * @retval  None
 ************************************************************************************************************/
void HardFault_Handler(void)
{
  #if 1

  static vu32 gIsContinue = 0;
  /*--------------------------------------------------------------------------------------------------------*/
  /* For development FW, MCU run into the while loop when the hardfault occurred.                           */
  /* 1. Stack Checking                                                                                      */
  /*    When a hard fault exception occurs, MCU push following register into the stack (main or process     */
  /*    stack). Confirm R13(SP) value in the Register Window and typing it to the Memory Windows, you can   */
  /*    check following register, especially the PC value (indicate the last instruction before hard fault).*/
  /*    SP + 0x00    0x04    0x08    0x0C    0x10    0x14    0x18    0x1C                                   */
  /*           R0      R1      R2      R3     R12      LR      PC    xPSR                                   */
  while (gIsContinue == 0)
  {
  }
  /* 2. Step Out to Find the Clue                                                                           */
  /*    Change the variable "gIsContinue" to any other value than zero in a Local or Watch Window, then     */
  /*    step out the HardFault_Handler to reach the first instruction after the instruction which caused    */
  /*    the hard fault.                                                                                     */
  /*--------------------------------------------------------------------------------------------------------*/

  #else

  /*--------------------------------------------------------------------------------------------------------*/
  /* For production FW, you shall consider to reboot the system when hardfault occurred.                    */
  /*--------------------------------------------------------------------------------------------------------*/
  NVIC_SystemReset();

  #endif
}

/*********************************************************************************************************//**
 * @brief   This function handles SVCall exception.
 * @retval  None
 ************************************************************************************************************/
void SVC_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PendSVC exception.
 * @retval  None
 ************************************************************************************************************/
void PendSV_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles SysTick Handler.
 * @retval  None
 ************************************************************************************************************/
void SysTick_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles EXTI interrupt.
 * @retval  None
 ************************************************************************************************************/
#if defined(USE_HT32F52230_SK) || defined(USE_HT32F50230_SK) || defined(USE_HT32F0008_SK)
void EXTI2_3_IRQHandler(void)
{
  extern vu32 gIsKeyPress;
  gIsKeyPress = TRUE;
  EXTI_ClearEdgeFlag(KEY1_BUTTON_EXTI_CHANNEL);
}
#endif

#if defined(USE_HT32F52241_SK) || defined(USE_HT32F57341_SK) || defined(USE_HT32F57352_SK) || defined(USE_HT32F50343_SK) || defined(USE_HT32F52367_SK)
void EXTI4_15_IRQHandler(void)
{
  extern vu32 gIsKeyPress;
  gIsKeyPress = TRUE;
  EXTI_ClearEdgeFlag(KEY1_BUTTON_EXTI_CHANNEL);
}
#endif

#if (defined(USE_HT32F52352_SK) || defined(USE_HT32F52341_SK)) || defined(USE_HT32F0006_DVB)
void EXTI0_1_IRQHandler(void)
{
  extern vu32 gIsKeyPress;
  gIsKeyPress = TRUE;
  EXTI_ClearEdgeFlag(KEY1_BUTTON_EXTI_CHANNEL);
}
#endif

/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
void SPI0_IRQHandler(void)
{
  extern vu32 guReceivedCount;
  extern u8 guReceiveBuffer[];
  u32 uCount = SPI_GetFIFOStatus(HTCFG_SLAVE_SPI, SPI_FIFO_RX);

  while (uCount--)
  {
    guReceiveBuffer[guReceivedCount++] = SPI_ReceiveData(HTCFG_SLAVE_SPI);
    #if 0
    if (guReceivedCount == 8)
    {
      while (1);
    }
    #endif
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
