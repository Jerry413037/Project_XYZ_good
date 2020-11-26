/**
 @page QSPI_Flash_Quad_Mode

 @verbatim
 * @file    QSPI/Flash_Quad_Mode/readme.txt
 * @version V1.00
 * @date    2018-10-25
 * @brief   Description of the QSPI_Flash example.
 @endverbatim

@par Example Description:

This example describes how to use the QSPI to communicate with MX25L12835F FLASH.

This example first read the Flash ID from QSPI flash.
Then Setting the status register and configuration register both on flash device.
Then start two tests respectively byte Read/Write and half word Read/Write, and 
the two test processes are similar, the only differences is data type.

Prior to write operation, the program should perform an erase operation of the selected sector.
Then a write of a Tx_Buffer to the memory followed by a quard output read of the written memory address.
The data read from the memory is stored in the Rx_Buffer and compared with the values of the
Tx_Buffer.

Finally, the same sectors are erased again. All the data address written before are read (non-dual output)
and checked with 0xFF.

If all the test are passed, LED1 will be turned on.

The FLASH_WriteAddress and the FLASH_ReadAddress are defined as 0x100000
in this example.

@par Directory Contents:

- QSPI/Flash_Quad_Mode/main.c                           Main program
- QSPI/Flash_Quad_Mode/ht32fxxxx_it.c                   Interrupt handlers
- QSPI/Flash_Quad_Mode/qspi_flash_MX25L12835F.c         MX25L12835F's firmware library
- QSPI/Flash_Quad_Mode/qspi_flash_MX25L12835F.h         The header file of MX25L12835F

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- The expansion board such as ESK32-2x001 is required, refer to the user manual for the jumper settings.
- This example requires external component on the expansion board but some development board (with the
  "USE_HT32XXXXXX_DVB" define) can not use with it directly. The extra jumper/wired connections may required
  to use this example.

@par Firmware Disclaimer Information

1. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
   proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
   other intellectual property laws.

2. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
   other than HOLTEK and the customer.

3. The program technical documentation, including the code, is provided "as is" and for customer reference
   only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
   the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
   the warranties of merchantability, satisfactory quality and fitness for a particular purpose.

 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 */
