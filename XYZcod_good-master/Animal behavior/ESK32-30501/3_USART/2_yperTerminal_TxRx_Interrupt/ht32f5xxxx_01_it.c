/*********************************************************************************************************//**
 * @file    USART/HyperTerminal_TxRx_Interrupt/ht32f520xx_01_it.c
 * @version $Rev:: 914          $
 * @date    $Date:: 2016-07-21 #$
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
#include "ht32_board.h"
#include "usart_int.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USART_Examples USART
  * @{
  */

/** @addtogroup HyperTerminal_TxRx_Interrupt
  * @{
  */


/* Private define ------------------------------------------------------------------------------------------*/
#define USART_TIMEOUT_ON          ((u32)0x00000080)

/* COM1 definitions                                                                                        */
u8 URTxBuf[USART_BUFSIZE]={0x41,0x42,0x43,0x44,0x45};
u8 URRxBuf[USART_BUFSIZE];
vu32 URTxReadIndex = 0;
vu32 URTxWriteIndex = 0;
vu32 URRxWriteIndex = 0;
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
  while (1);
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
 * @brief   This function handles UARTx interrupt.
 * @retval  None
 ************************************************************************************************************/
#if defined(USE_HT32F52230_SK)
void UART0_IRQHandler(void)
#elif USE_HT32F52352_SK
void USART1_IRQHandler(void)
#else 
void UART1_IRQHandler(void)
#endif
{
  /* Tx, move data from buffer to UART                                                                */
  if(USART_GetFlagStatus(COM1_PORT,USART_FLAG_TXDE)) 
  {
    if(URTxWriteIndex>0)
    {
      u8 u8WriteIndex;
      u8 u8ReadIndex;
      USART_SendData(COM1_PORT, URTxBuf[URTxReadIndex]); 
      URTxReadIndex++;      
      u8WriteIndex =URTxWriteIndex;
      u8ReadIndex = URTxReadIndex;
      if(u8WriteIndex==u8ReadIndex)
      {
        URTxWriteIndex=0;
        URTxReadIndex=0;
        USART_IntConfig(COM1_PORT,USART_INT_TXDE,DISABLE);
        HT32F_DVB_LEDOff(HT_LED2);
      }
    }
  }
  /* Rx, move data from UART to buffer                                                                */
  if(USART_GetFlagStatus(COM1_PORT,USART_FLAG_RXDR))
  {
    USART_ClearFlag(COM1_PORT,USART_FLAG_RXDR);
    URRxBuf[URRxWriteIndex] = USART_ReceiveData(COM1_PORT);
    URRxWriteIndex = (URRxWriteIndex + 1) % USART_BUFSIZE;
    HT32F_DVB_LEDOn(HT_LED2);
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
