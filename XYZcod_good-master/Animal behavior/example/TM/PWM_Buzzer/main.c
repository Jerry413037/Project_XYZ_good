/*********************************************************************************************************//**
 * @file    TM/PWM_Buzzer/main.c
 * @version $Rev:: 4713         $
 * @date    $Date:: 2020-04-06 #$
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

/** @addtogroup TM_Examples TM
  * @{
  */

/** @addtogroup PWM_Buzzer
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define BEE_TM_PRE                      (4)
#define BEE_SYS_CLK                     (LIBCFG_MAX_SPEED)      // Calculate with fix value (#define)
//#define BEE_SYS_CLK                     (SystemCoreClock)       // Calculate on the fly (variable)
#define BEE_DUTY                        (33) // 33 % duty

/* Private function prototypes -----------------------------------------------------------------------------*/
void Buzzer_Init(u32 uFrequency);
void Buzzer_Start(u32 uBeeTimes, u32 uFrequency, u32 uActive_ms, u32 uInActive_ms);
u32 Buzzer_IsFinish(void);

void Buzzer_Fun1(void);
void Buzzer_Fun2(void);
void Buzzer_PlayTable(void);

/* Private macro -------------------------------------------------------------------------------------------*/
#define BEE_TIME_MS(t, f)               (f * t / 1000)

/* Global variables ----------------------------------------------------------------------------------------*/
u32  gBee_Time;
u32  gBee_Active;
u32  gBee_InActive;
vu32 gBee_Count;

u16 gBee_Scale[] =
{
    0,
  262,  294,  330,  349,  392,  440,  494,
  523,  587,  659,  698,  784,  880,  988,
 1046, 1175, 1318, 1397, 1568, 1760, 1976
};

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  Buzzer_Fun1();

  Buzzer_Fun2();

  Buzzer_Init(0);

  while (1)
  {
    Buzzer_PlayTable();
  }
}

/*********************************************************************************************************//**
  * @brief  Buzzer function 1.
  * @retval None
  ***********************************************************************************************************/
void Buzzer_Fun1(void)
{
  /* Bee 4 times, 3 kHz, active 50 ms, inactive 50 ms                                                       */
  Buzzer_Init(0);
  Buzzer_Start(4, 3000, 50, 50);
  while (Buzzer_IsFinish() == FALSE);
}

/*********************************************************************************************************//**
  * @brief  Buzzer function 2.
  * @retval None
  ***********************************************************************************************************/
void Buzzer_Fun2(void)
{
  /* Bee 2 times, 800 Hz, active 1000 ms, inactive 500 ms                                                   */
  Buzzer_Init(0);
  Buzzer_Start(2, 800, 1000, 500);
  while (Buzzer_IsFinish() == FALSE);
}

/*********************************************************************************************************//**
  * @brief  Buzzer play table function.
  * @retval None
  ***********************************************************************************************************/
void Buzzer_PlayTable(void)
{
  static u32 i = 1;

  /* Bee 1 times, gBee_Scale[i] Hz, active 250 ms, inactive 250 ms                                          */
  if (Buzzer_IsFinish() == TRUE && i <= 21)
  {
    Buzzer_Start(1, gBee_Scale[i], 250, 250);
    i++;
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the timer for buzzer.
  * @param  uFrequency: Frequency of Buzzer (Hz).
  * @retval None
  ***********************************************************************************************************/
void Buzzer_Init(u32 uFrequency)
{
  u32 uReload;

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_BUZZER_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as TM function                                                                     */
  HT32F_DVB_GPxConfig(HTCFG_BUZZER_GPIO_ID, HTCFG_BUZZER_AFIO_PIN, HTCFG_BUZZER_AFIO_FUN);

  uReload = (BEE_SYS_CLK / BEE_TM_PRE / uFrequency) - 1;

  { /* Time base configuration                                                                              */
    TM_TimeBaseInitTypeDef TimeBaseInit;
    TimeBaseInit.Prescaler =  BEE_TM_PRE - 1;
    TimeBaseInit.CounterReload = uReload;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_BUZZER_PORT, &TimeBaseInit);

    /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                 */
    TM_ClearFlag(HTCFG_BUZZER_PORT, TM_FLAG_UEV);
  }

  { /* Channel n output configuration                                                                       */
    TM_OutputInitTypeDef OutInit;
    OutInit.Channel = HTCFG_BUZZER_CH;
    OutInit.OutputMode = TM_OM_PWM2;
    OutInit.Control = TM_CHCTL_DISABLE;
    OutInit.ControlN = TM_CHCTL_DISABLE;
    OutInit.Polarity = TM_CHP_NONINVERTED;
    OutInit.PolarityN = TM_CHP_NONINVERTED;
    OutInit.IdleState = MCTM_OIS_LOW;
    OutInit.IdleStateN = MCTM_OIS_HIGH;
    OutInit.Compare = ((uReload + 1) * (100 - BEE_DUTY)) / 100;
    OutInit.AsymmetricCompare = 0;
    TM_OutputInit(HTCFG_BUZZER_PORT, &OutInit);
  }

  #if (LIBCFG_MCTM0)
  if (HTCFG_BUZZER_PORT == HT_MCTM0)
  {
    /* MCTM channel Main Output Enable                                                                      */
    MCTM_CHMOECmd(HTCFG_BUZZER_PORT, ENABLE);
  }
  #endif

  /* Enable TM interrupt                                                                                    */
  NVIC_EnableIRQ(HTCFG_BUZZER_IRQn);
}

/*********************************************************************************************************//**
  * @brief  Start the Buzzer.
  * @param  uBeeTimes: Bee times.
  * @param  uFrequency: Frequency of Buzzer (Hz).
  * @param  uActive_ms: Bee active time based on ms.
  * @param  uInActive_ms: Bee inactive time based ms.
  * @retval None
  ***********************************************************************************************************/
void Buzzer_Start(u32 uBeeTimes, u32 uFrequency, u32 uActive_ms, u32 uInActive_ms)
{
  u32 uReload  =  (BEE_SYS_CLK / BEE_TM_PRE / uFrequency) - 1;
  u32 uCompare =  ((uReload + 1) * (100 - BEE_DUTY)) / 100;

  gBee_Time = uBeeTimes;
  gBee_Active = BEE_TIME_MS(uActive_ms, uFrequency);
  gBee_InActive = BEE_TIME_MS(uInActive_ms, uFrequency);
  gBee_Count = gBee_Active + gBee_InActive;

  TM_SetCounterReload(HTCFG_BUZZER_PORT, uReload);
  TM_SetCaptureCompare(HTCFG_BUZZER_PORT, HTCFG_BUZZER_CH, uCompare);

  TM_IntConfig(HTCFG_BUZZER_PORT, TM_INT_UEV, ENABLE);
  TM_ChannelConfig(BUZZER_TM, BUZZER_TM_CHANNEL, TM_CHCTL_ENABLE);
  TM_Cmd(HTCFG_BUZZER_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Is Buzzer finished.
  * @retval TRUE or FALSE
  ***********************************************************************************************************/
u32 Buzzer_IsFinish(void)
{
  return (gBee_Time ? FALSE : TRUE);
}

/*********************************************************************************************************//**
 * @brief   This function handles TM interrupt.
 * @retval  None
 ************************************************************************************************************/
void HTCFG_BUZZER_IRQHandler(void)
{
  TM_ClearFlag(HTCFG_BUZZER_PORT, TM_INT_UEV);

  if (gBee_Count)
  {
    gBee_Count--;
    if (gBee_Count == gBee_InActive)
    {
      TM_ChannelConfig(BUZZER_TM, BUZZER_TM_CHANNEL, TM_CHCTL_DISABLE);
    }

    if (gBee_Count == 0)
    {
      gBee_Count = gBee_Active + gBee_InActive;
      TM_ChannelConfig(BUZZER_TM, BUZZER_TM_CHANNEL, TM_CHCTL_ENABLE);

      if (gBee_Time)
        gBee_Time--;

      if (gBee_Time == 0)
      {
        TM_Cmd(HTCFG_BUZZER_PORT, DISABLE);
      }
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
