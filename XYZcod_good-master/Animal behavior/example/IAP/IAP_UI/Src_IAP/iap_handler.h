/*********************************************************************************************************//**
 * @file    IAP/IAP_UI/Src_IAP/iap_handler.h
 * @version $Rev:: 4191         $
 * @date    $Date:: 2019-08-12 #$
 * @brief   The header file of IAP Handler.
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

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __IAP_HANDLER_H
#define __IAP_HANDLER_H

/* Includes ------------------------------------------------------------------------------------------------*/

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup IAP_Examples IAP
  * @{
  */

/** @addtogroup UI_mode UI mode
  * @{
  */

/** @addtogroup UI_mode_IAP IAP
  * @{
  */


/* Exported constants --------------------------------------------------------------------------------------*/

// IAP_FLASH_SIZE = Flash Size (except option bytes) - Loader Size

#if defined(USE_MEM_HT32F52230)
  #define IAP_CHIP_NAME         "HT32F52230"
  #define IAP_FLASH_SIZE        "27648"
  #define IAP_PPBIT             "31"
#endif

#if defined(USE_MEM_HT32F52241)
  #define IAP_CHIP_NAME         "HT32F52241"
  #define IAP_FLASH_SIZE        "60416"
  #define IAP_PPBIT             "63"
#endif

#if defined(USE_MEM_HT32F52253)
  #define IAP_CHIP_NAME         "HT32F52253"
  #define IAP_FLASH_SIZE        "125952"
  #define IAP_PPBIT             "127"
#endif

#if defined(USE_MEM_HT32F52341)
  #define IAP_CHIP_NAME         "HT32F52341"
  #define IAP_FLASH_SIZE        "60928"
  #define IAP_PPBIT             "127"
#endif

#if defined(USE_MEM_HT32F52352)
  #define IAP_CHIP_NAME         "HT32F52352"
  #define IAP_FLASH_SIZE        "126464"
  #define IAP_PPBIT             "127"
#endif

#if defined(USE_MEM_HT32F0008)
  #define IAP_CHIP_NAME         "HT32F0008"
  #define IAP_FLASH_SIZE        "60416"
  #define IAP_PPBIT             "63"
#endif

#if defined(USE_MEM_HT32F50230)
  #define IAP_CHIP_NAME         "HT32F50230"
  #define IAP_FLASH_SIZE        "27648"
  #define IAP_PPBIT             "31"
#endif

#if defined(USE_MEM_HT32F50241)
  #define IAP_CHIP_NAME         "HT32F50241"
  #define IAP_FLASH_SIZE        "60416"
  #define IAP_PPBIT             "63"
#endif

#if defined(USE_MEM_HT32F52354)
  #define IAP_CHIP_NAME         "HT32F52354"
  #define IAP_FLASH_SIZE        "126464"
  #define IAP_PPBIT             "127"
#endif

#if defined(USE_MEM_HT32F57341)
  #define IAP_CHIP_NAME         "HT32F57341"
  #define IAP_FLASH_SIZE        "60416"
  #define IAP_PPBIT             "63"
#endif

#if defined(USE_MEM_HT32F57352)
  #define IAP_CHIP_NAME         "HT32F57352"
  #define IAP_FLASH_SIZE        "126464"
  #define IAP_PPBIT             "127"
#endif

#if defined(USE_MEM_HT32F0006)
  #define IAP_CHIP_NAME         "HT32F0006"
  #define IAP_FLASH_SIZE        "126464"
  #define IAP_PPBIT             "127"
#endif

#if defined(USE_MEM_HT32F52367)
  #define IAP_CHIP_NAME         "HT32F52367"
  #define IAP_FLASH_SIZE        "257024"
  #define IAP_PPBIT             "255"
#endif

#if defined(USE_MEM_HT32F50343)
  #define IAP_CHIP_NAME         "HT32F50343"
  #define IAP_FLASH_SIZE        "60416"
  #define IAP_PPBIT             "63"
#endif

#define IAP_APFLASH_SIZE        (LIBCFG_FLASH_SIZE)
#define IAP_APFLASH_END         (IAP_APFLASH_SIZE - 1)

#define IAP_APSRAM_SIZE         (LIBCFG_RAM_SIZE)
#define IAP_APSRAM_END          (HT_SRAM_BASE + IAP_APSRAM_SIZE)

#define IAP_START               ("4096")

#define IAP_OB_START            (0x1FF00000)
#define IAP_OB_END              (IAP_OB_START + LIBCFG_FLASH_PAGESIZE - 1)

#define IAP_DATA_START          (0x1FF00050)

#define IAP_GO_EXEC             (0)
#define IAP_GO_EXIT             (1)
#define IAP_GO_RESET            (2)

/* Exported functions --------------------------------------------------------------------------------------*/
u32 IAP_Go(u32 type);
void IAP_Handler(void);
void iapSendString(u8 *String);


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif
