/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * mv643xx.h - MV-643XX Intewnaw wegistews definition fiwe.
 *
 * Copywight 2002 Momentum Computew, Inc.
 * 	Authow: Matthew Dhawm <mdhawm@momenco.com>
 * Copywight 2002 GAWIWEO TECHNOWOGY, WTD. 
 */
#ifndef __ASM_MV643XX_H
#define __ASM_MV643XX_H

#incwude <asm/types.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/mv643xx_i2c.h>

/****************************************/
/* Pwocessow Addwess Space              */
/****************************************/

/* DDW SDWAM BAW and size wegistews */

#define MV64340_CS_0_BASE_ADDW                                      0x008
#define MV64340_CS_0_SIZE                                           0x010
#define MV64340_CS_1_BASE_ADDW                                      0x208
#define MV64340_CS_1_SIZE                                           0x210
#define MV64340_CS_2_BASE_ADDW                                      0x018
#define MV64340_CS_2_SIZE                                           0x020
#define MV64340_CS_3_BASE_ADDW                                      0x218
#define MV64340_CS_3_SIZE                                           0x220

/* Devices BAW and size wegistews */

#define MV64340_DEV_CS0_BASE_ADDW                                   0x028
#define MV64340_DEV_CS0_SIZE                                        0x030
#define MV64340_DEV_CS1_BASE_ADDW                                   0x228
#define MV64340_DEV_CS1_SIZE                                        0x230
#define MV64340_DEV_CS2_BASE_ADDW                                   0x248
#define MV64340_DEV_CS2_SIZE                                        0x250
#define MV64340_DEV_CS3_BASE_ADDW                                   0x038
#define MV64340_DEV_CS3_SIZE                                        0x040
#define MV64340_BOOTCS_BASE_ADDW                                    0x238
#define MV64340_BOOTCS_SIZE                                         0x240

/* PCI 0 BAW and size wegistews */

#define MV64340_PCI_0_IO_BASE_ADDW                                  0x048
#define MV64340_PCI_0_IO_SIZE                                       0x050
#define MV64340_PCI_0_MEMOWY0_BASE_ADDW                             0x058
#define MV64340_PCI_0_MEMOWY0_SIZE                                  0x060
#define MV64340_PCI_0_MEMOWY1_BASE_ADDW                             0x080
#define MV64340_PCI_0_MEMOWY1_SIZE                                  0x088
#define MV64340_PCI_0_MEMOWY2_BASE_ADDW                             0x258
#define MV64340_PCI_0_MEMOWY2_SIZE                                  0x260
#define MV64340_PCI_0_MEMOWY3_BASE_ADDW                             0x280
#define MV64340_PCI_0_MEMOWY3_SIZE                                  0x288

/* PCI 1 BAW and size wegistews */
#define MV64340_PCI_1_IO_BASE_ADDW                                  0x090
#define MV64340_PCI_1_IO_SIZE                                       0x098
#define MV64340_PCI_1_MEMOWY0_BASE_ADDW                             0x0a0
#define MV64340_PCI_1_MEMOWY0_SIZE                                  0x0a8
#define MV64340_PCI_1_MEMOWY1_BASE_ADDW                             0x0b0
#define MV64340_PCI_1_MEMOWY1_SIZE                                  0x0b8
#define MV64340_PCI_1_MEMOWY2_BASE_ADDW                             0x2a0
#define MV64340_PCI_1_MEMOWY2_SIZE                                  0x2a8
#define MV64340_PCI_1_MEMOWY3_BASE_ADDW                             0x2b0
#define MV64340_PCI_1_MEMOWY3_SIZE                                  0x2b8

/* SWAM base addwess */
#define MV64340_INTEGWATED_SWAM_BASE_ADDW                           0x268

/* intewnaw wegistews space base addwess */
#define MV64340_INTEWNAW_SPACE_BASE_ADDW                            0x068

/* Enabwes the CS , DEV_CS , PCI 0 and PCI 1 
   windows above */
#define MV64340_BASE_ADDW_ENABWE                                    0x278

/****************************************/
/* PCI wemap wegistews                  */
/****************************************/
      /* PCI 0 */
#define MV64340_PCI_0_IO_ADDW_WEMAP                                 0x0f0
#define MV64340_PCI_0_MEMOWY0_WOW_ADDW_WEMAP                        0x0f8
#define MV64340_PCI_0_MEMOWY0_HIGH_ADDW_WEMAP                       0x320
#define MV64340_PCI_0_MEMOWY1_WOW_ADDW_WEMAP                        0x100
#define MV64340_PCI_0_MEMOWY1_HIGH_ADDW_WEMAP                       0x328
#define MV64340_PCI_0_MEMOWY2_WOW_ADDW_WEMAP                        0x2f8
#define MV64340_PCI_0_MEMOWY2_HIGH_ADDW_WEMAP                       0x330
#define MV64340_PCI_0_MEMOWY3_WOW_ADDW_WEMAP                        0x300
#define MV64340_PCI_0_MEMOWY3_HIGH_ADDW_WEMAP                       0x338
      /* PCI 1 */
#define MV64340_PCI_1_IO_ADDW_WEMAP                                 0x108
#define MV64340_PCI_1_MEMOWY0_WOW_ADDW_WEMAP                        0x110
#define MV64340_PCI_1_MEMOWY0_HIGH_ADDW_WEMAP                       0x340
#define MV64340_PCI_1_MEMOWY1_WOW_ADDW_WEMAP                        0x118
#define MV64340_PCI_1_MEMOWY1_HIGH_ADDW_WEMAP                       0x348
#define MV64340_PCI_1_MEMOWY2_WOW_ADDW_WEMAP                        0x310
#define MV64340_PCI_1_MEMOWY2_HIGH_ADDW_WEMAP                       0x350
#define MV64340_PCI_1_MEMOWY3_WOW_ADDW_WEMAP                        0x318
#define MV64340_PCI_1_MEMOWY3_HIGH_ADDW_WEMAP                       0x358
 
#define MV64340_CPU_PCI_0_HEADEWS_WETAWGET_CONTWOW                  0x3b0
#define MV64340_CPU_PCI_0_HEADEWS_WETAWGET_BASE                     0x3b8
#define MV64340_CPU_PCI_1_HEADEWS_WETAWGET_CONTWOW                  0x3c0
#define MV64340_CPU_PCI_1_HEADEWS_WETAWGET_BASE                     0x3c8
#define MV64340_CPU_GE_HEADEWS_WETAWGET_CONTWOW                     0x3d0
#define MV64340_CPU_GE_HEADEWS_WETAWGET_BASE                        0x3d8
#define MV64340_CPU_IDMA_HEADEWS_WETAWGET_CONTWOW                   0x3e0
#define MV64340_CPU_IDMA_HEADEWS_WETAWGET_BASE                      0x3e8

/****************************************/
/*         CPU Contwow Wegistews        */
/****************************************/

#define MV64340_CPU_CONFIG                                          0x000
#define MV64340_CPU_MODE                                            0x120
#define MV64340_CPU_MASTEW_CONTWOW                                  0x160
#define MV64340_CPU_CWOSS_BAW_CONTWOW_WOW                           0x150
#define MV64340_CPU_CWOSS_BAW_CONTWOW_HIGH                          0x158
#define MV64340_CPU_CWOSS_BAW_TIMEOUT                               0x168

/****************************************/
/* SMP WegistewS                        */
/****************************************/

#define MV64340_SMP_WHO_AM_I                                        0x200
#define MV64340_SMP_CPU0_DOOWBEWW                                   0x214
#define MV64340_SMP_CPU0_DOOWBEWW_CWEAW                             0x21C
#define MV64340_SMP_CPU1_DOOWBEWW                                   0x224
#define MV64340_SMP_CPU1_DOOWBEWW_CWEAW                             0x22C
#define MV64340_SMP_CPU0_DOOWBEWW_MASK                              0x234
#define MV64340_SMP_CPU1_DOOWBEWW_MASK                              0x23C
#define MV64340_SMP_SEMAPHOW0                                       0x244
#define MV64340_SMP_SEMAPHOW1                                       0x24c
#define MV64340_SMP_SEMAPHOW2                                       0x254
#define MV64340_SMP_SEMAPHOW3                                       0x25c
#define MV64340_SMP_SEMAPHOW4                                       0x264
#define MV64340_SMP_SEMAPHOW5                                       0x26c
#define MV64340_SMP_SEMAPHOW6                                       0x274
#define MV64340_SMP_SEMAPHOW7                                       0x27c

/****************************************/
/*  CPU Sync Bawwiew Wegistew           */
/****************************************/

#define MV64340_CPU_0_SYNC_BAWWIEW_TWIGGEW                          0x0c0
#define MV64340_CPU_0_SYNC_BAWWIEW_VIWTUAW                          0x0c8
#define MV64340_CPU_1_SYNC_BAWWIEW_TWIGGEW                          0x0d0
#define MV64340_CPU_1_SYNC_BAWWIEW_VIWTUAW                          0x0d8

/****************************************/
/* CPU Access Pwotect                   */
/****************************************/

#define MV64340_CPU_PWOTECT_WINDOW_0_BASE_ADDW                      0x180
#define MV64340_CPU_PWOTECT_WINDOW_0_SIZE                           0x188
#define MV64340_CPU_PWOTECT_WINDOW_1_BASE_ADDW                      0x190
#define MV64340_CPU_PWOTECT_WINDOW_1_SIZE                           0x198
#define MV64340_CPU_PWOTECT_WINDOW_2_BASE_ADDW                      0x1a0
#define MV64340_CPU_PWOTECT_WINDOW_2_SIZE                           0x1a8
#define MV64340_CPU_PWOTECT_WINDOW_3_BASE_ADDW                      0x1b0
#define MV64340_CPU_PWOTECT_WINDOW_3_SIZE                           0x1b8


/****************************************/
/*          CPU Ewwow Wepowt            */
/****************************************/

#define MV64340_CPU_EWWOW_ADDW_WOW                                  0x070
#define MV64340_CPU_EWWOW_ADDW_HIGH                                 0x078
#define MV64340_CPU_EWWOW_DATA_WOW                                  0x128
#define MV64340_CPU_EWWOW_DATA_HIGH                                 0x130
#define MV64340_CPU_EWWOW_PAWITY                                    0x138
#define MV64340_CPU_EWWOW_CAUSE                                     0x140
#define MV64340_CPU_EWWOW_MASK                                      0x148

/****************************************/
/*      CPU Intewface Debug Wegistews 	*/
/****************************************/

#define MV64340_PUNIT_SWAVE_DEBUG_WOW                               0x360
#define MV64340_PUNIT_SWAVE_DEBUG_HIGH                              0x368
#define MV64340_PUNIT_MASTEW_DEBUG_WOW                              0x370
#define MV64340_PUNIT_MASTEW_DEBUG_HIGH                             0x378
#define MV64340_PUNIT_MMASK                                         0x3e4

/****************************************/
/*  Integwated SWAM Wegistews           */
/****************************************/

#define MV64340_SWAM_CONFIG                                         0x380
#define MV64340_SWAM_TEST_MODE                                      0X3F4
#define MV64340_SWAM_EWWOW_CAUSE                                    0x388
#define MV64340_SWAM_EWWOW_ADDW                                     0x390
#define MV64340_SWAM_EWWOW_ADDW_HIGH                                0X3F8
#define MV64340_SWAM_EWWOW_DATA_WOW                                 0x398
#define MV64340_SWAM_EWWOW_DATA_HIGH                                0x3a0
#define MV64340_SWAM_EWWOW_DATA_PAWITY                              0x3a8

/****************************************/
/* SDWAM Configuwation                  */
/****************************************/

#define MV64340_SDWAM_CONFIG                                        0x1400
#define MV64340_D_UNIT_CONTWOW_WOW                                  0x1404
#define MV64340_D_UNIT_CONTWOW_HIGH                                 0x1424
#define MV64340_SDWAM_TIMING_CONTWOW_WOW                            0x1408
#define MV64340_SDWAM_TIMING_CONTWOW_HIGH                           0x140c
#define MV64340_SDWAM_ADDW_CONTWOW                                  0x1410
#define MV64340_SDWAM_OPEN_PAGES_CONTWOW                            0x1414
#define MV64340_SDWAM_OPEWATION                                     0x1418
#define MV64340_SDWAM_MODE                                          0x141c
#define MV64340_EXTENDED_DWAM_MODE                                  0x1420
#define MV64340_SDWAM_CWOSS_BAW_CONTWOW_WOW                         0x1430
#define MV64340_SDWAM_CWOSS_BAW_CONTWOW_HIGH                        0x1434
#define MV64340_SDWAM_CWOSS_BAW_TIMEOUT                             0x1438
#define MV64340_SDWAM_ADDW_CTWW_PADS_CAWIBWATION                    0x14c0
#define MV64340_SDWAM_DATA_PADS_CAWIBWATION                         0x14c4

/****************************************/
/* SDWAM Ewwow Wepowt                   */
/****************************************/

#define MV64340_SDWAM_EWWOW_DATA_WOW                                0x1444
#define MV64340_SDWAM_EWWOW_DATA_HIGH                               0x1440
#define MV64340_SDWAM_EWWOW_ADDW                                    0x1450
#define MV64340_SDWAM_WECEIVED_ECC                                  0x1448
#define MV64340_SDWAM_CAWCUWATED_ECC                                0x144c
#define MV64340_SDWAM_ECC_CONTWOW                                   0x1454
#define MV64340_SDWAM_ECC_EWWOW_COUNTEW                             0x1458

/******************************************/
/*  Contwowwed Deway Wine (CDW) Wegistews */
/******************************************/

#define MV64340_DFCDW_CONFIG0                                       0x1480
#define MV64340_DFCDW_CONFIG1                                       0x1484
#define MV64340_DWW_WWITE                                           0x1488
#define MV64340_DWW_WEAD                                            0x148c
#define MV64340_SWAM_ADDW                                           0x1490
#define MV64340_SWAM_DATA0                                          0x1494
#define MV64340_SWAM_DATA1                                          0x1498
#define MV64340_SWAM_DATA2                                          0x149c
#define MV64340_DFCW_PWOBE                                          0x14a0

/******************************************/
/*   Debug Wegistews                      */
/******************************************/

#define MV64340_DUNIT_DEBUG_WOW                                     0x1460
#define MV64340_DUNIT_DEBUG_HIGH                                    0x1464
#define MV64340_DUNIT_MMASK                                         0X1b40

/****************************************/
/* Device Pawametews			*/
/****************************************/

#define MV64340_DEVICE_BANK0_PAWAMETEWS				    0x45c
#define MV64340_DEVICE_BANK1_PAWAMETEWS				    0x460
#define MV64340_DEVICE_BANK2_PAWAMETEWS				    0x464
#define MV64340_DEVICE_BANK3_PAWAMETEWS				    0x468
#define MV64340_DEVICE_BOOT_BANK_PAWAMETEWS			    0x46c
#define MV64340_DEVICE_INTEWFACE_CONTWOW                            0x4c0
#define MV64340_DEVICE_INTEWFACE_CWOSS_BAW_CONTWOW_WOW              0x4c8
#define MV64340_DEVICE_INTEWFACE_CWOSS_BAW_CONTWOW_HIGH             0x4cc
#define MV64340_DEVICE_INTEWFACE_CWOSS_BAW_TIMEOUT                  0x4c4

/****************************************/
/* Device intewwupt wegistews		*/
/****************************************/

#define MV64340_DEVICE_INTEWWUPT_CAUSE				    0x4d0
#define MV64340_DEVICE_INTEWWUPT_MASK				    0x4d4
#define MV64340_DEVICE_EWWOW_ADDW				    0x4d8
#define MV64340_DEVICE_EWWOW_DATA   				    0x4dc
#define MV64340_DEVICE_EWWOW_PAWITY     			    0x4e0

/****************************************/
/* Device debug wegistews   		*/
/****************************************/

#define MV64340_DEVICE_DEBUG_WOW     				    0x4e4
#define MV64340_DEVICE_DEBUG_HIGH     				    0x4e8
#define MV64340_WUNIT_MMASK                                         0x4f0

/****************************************/
/* PCI Swave Addwess Decoding wegistews */
/****************************************/

#define MV64340_PCI_0_CS_0_BANK_SIZE                                0xc08
#define MV64340_PCI_1_CS_0_BANK_SIZE                                0xc88
#define MV64340_PCI_0_CS_1_BANK_SIZE                                0xd08
#define MV64340_PCI_1_CS_1_BANK_SIZE                                0xd88
#define MV64340_PCI_0_CS_2_BANK_SIZE                                0xc0c
#define MV64340_PCI_1_CS_2_BANK_SIZE                                0xc8c
#define MV64340_PCI_0_CS_3_BANK_SIZE                                0xd0c
#define MV64340_PCI_1_CS_3_BANK_SIZE                                0xd8c
#define MV64340_PCI_0_DEVCS_0_BANK_SIZE                             0xc10
#define MV64340_PCI_1_DEVCS_0_BANK_SIZE                             0xc90
#define MV64340_PCI_0_DEVCS_1_BANK_SIZE                             0xd10
#define MV64340_PCI_1_DEVCS_1_BANK_SIZE                             0xd90
#define MV64340_PCI_0_DEVCS_2_BANK_SIZE                             0xd18
#define MV64340_PCI_1_DEVCS_2_BANK_SIZE                             0xd98
#define MV64340_PCI_0_DEVCS_3_BANK_SIZE                             0xc14
#define MV64340_PCI_1_DEVCS_3_BANK_SIZE                             0xc94
#define MV64340_PCI_0_DEVCS_BOOT_BANK_SIZE                          0xd14
#define MV64340_PCI_1_DEVCS_BOOT_BANK_SIZE                          0xd94
#define MV64340_PCI_0_P2P_MEM0_BAW_SIZE                             0xd1c
#define MV64340_PCI_1_P2P_MEM0_BAW_SIZE                             0xd9c
#define MV64340_PCI_0_P2P_MEM1_BAW_SIZE                             0xd20
#define MV64340_PCI_1_P2P_MEM1_BAW_SIZE                             0xda0
#define MV64340_PCI_0_P2P_I_O_BAW_SIZE                              0xd24
#define MV64340_PCI_1_P2P_I_O_BAW_SIZE                              0xda4
#define MV64340_PCI_0_CPU_BAW_SIZE                                  0xd28
#define MV64340_PCI_1_CPU_BAW_SIZE                                  0xda8
#define MV64340_PCI_0_INTEWNAW_SWAM_BAW_SIZE                        0xe00
#define MV64340_PCI_1_INTEWNAW_SWAM_BAW_SIZE                        0xe80
#define MV64340_PCI_0_EXPANSION_WOM_BAW_SIZE                        0xd2c
#define MV64340_PCI_1_EXPANSION_WOM_BAW_SIZE                        0xd9c
#define MV64340_PCI_0_BASE_ADDW_WEG_ENABWE                          0xc3c
#define MV64340_PCI_1_BASE_ADDW_WEG_ENABWE                          0xcbc
#define MV64340_PCI_0_CS_0_BASE_ADDW_WEMAP			    0xc48
#define MV64340_PCI_1_CS_0_BASE_ADDW_WEMAP			    0xcc8
#define MV64340_PCI_0_CS_1_BASE_ADDW_WEMAP			    0xd48
#define MV64340_PCI_1_CS_1_BASE_ADDW_WEMAP			    0xdc8
#define MV64340_PCI_0_CS_2_BASE_ADDW_WEMAP			    0xc4c
#define MV64340_PCI_1_CS_2_BASE_ADDW_WEMAP			    0xccc
#define MV64340_PCI_0_CS_3_BASE_ADDW_WEMAP			    0xd4c
#define MV64340_PCI_1_CS_3_BASE_ADDW_WEMAP			    0xdcc
#define MV64340_PCI_0_CS_0_BASE_HIGH_ADDW_WEMAP			    0xF04
#define MV64340_PCI_1_CS_0_BASE_HIGH_ADDW_WEMAP			    0xF84
#define MV64340_PCI_0_CS_1_BASE_HIGH_ADDW_WEMAP			    0xF08
#define MV64340_PCI_1_CS_1_BASE_HIGH_ADDW_WEMAP			    0xF88
#define MV64340_PCI_0_CS_2_BASE_HIGH_ADDW_WEMAP			    0xF0C
#define MV64340_PCI_1_CS_2_BASE_HIGH_ADDW_WEMAP			    0xF8C
#define MV64340_PCI_0_CS_3_BASE_HIGH_ADDW_WEMAP			    0xF10
#define MV64340_PCI_1_CS_3_BASE_HIGH_ADDW_WEMAP			    0xF90
#define MV64340_PCI_0_DEVCS_0_BASE_ADDW_WEMAP			    0xc50
#define MV64340_PCI_1_DEVCS_0_BASE_ADDW_WEMAP			    0xcd0
#define MV64340_PCI_0_DEVCS_1_BASE_ADDW_WEMAP			    0xd50
#define MV64340_PCI_1_DEVCS_1_BASE_ADDW_WEMAP			    0xdd0
#define MV64340_PCI_0_DEVCS_2_BASE_ADDW_WEMAP			    0xd58
#define MV64340_PCI_1_DEVCS_2_BASE_ADDW_WEMAP			    0xdd8
#define MV64340_PCI_0_DEVCS_3_BASE_ADDW_WEMAP           	    0xc54
#define MV64340_PCI_1_DEVCS_3_BASE_ADDW_WEMAP           	    0xcd4
#define MV64340_PCI_0_DEVCS_BOOTCS_BASE_ADDW_WEMAP      	    0xd54
#define MV64340_PCI_1_DEVCS_BOOTCS_BASE_ADDW_WEMAP      	    0xdd4
#define MV64340_PCI_0_P2P_MEM0_BASE_ADDW_WEMAP_WOW                  0xd5c
#define MV64340_PCI_1_P2P_MEM0_BASE_ADDW_WEMAP_WOW                  0xddc
#define MV64340_PCI_0_P2P_MEM0_BASE_ADDW_WEMAP_HIGH                 0xd60
#define MV64340_PCI_1_P2P_MEM0_BASE_ADDW_WEMAP_HIGH                 0xde0
#define MV64340_PCI_0_P2P_MEM1_BASE_ADDW_WEMAP_WOW                  0xd64
#define MV64340_PCI_1_P2P_MEM1_BASE_ADDW_WEMAP_WOW                  0xde4
#define MV64340_PCI_0_P2P_MEM1_BASE_ADDW_WEMAP_HIGH                 0xd68
#define MV64340_PCI_1_P2P_MEM1_BASE_ADDW_WEMAP_HIGH                 0xde8
#define MV64340_PCI_0_P2P_I_O_BASE_ADDW_WEMAP                       0xd6c
#define MV64340_PCI_1_P2P_I_O_BASE_ADDW_WEMAP                       0xdec 
#define MV64340_PCI_0_CPU_BASE_ADDW_WEMAP_WOW                       0xd70
#define MV64340_PCI_1_CPU_BASE_ADDW_WEMAP_WOW                       0xdf0
#define MV64340_PCI_0_CPU_BASE_ADDW_WEMAP_HIGH                      0xd74
#define MV64340_PCI_1_CPU_BASE_ADDW_WEMAP_HIGH                      0xdf4
#define MV64340_PCI_0_INTEGWATED_SWAM_BASE_ADDW_WEMAP               0xf00
#define MV64340_PCI_1_INTEGWATED_SWAM_BASE_ADDW_WEMAP               0xf80
#define MV64340_PCI_0_EXPANSION_WOM_BASE_ADDW_WEMAP                 0xf38
#define MV64340_PCI_1_EXPANSION_WOM_BASE_ADDW_WEMAP                 0xfb8
#define MV64340_PCI_0_ADDW_DECODE_CONTWOW                           0xd3c
#define MV64340_PCI_1_ADDW_DECODE_CONTWOW                           0xdbc
#define MV64340_PCI_0_HEADEWS_WETAWGET_CONTWOW                      0xF40
#define MV64340_PCI_1_HEADEWS_WETAWGET_CONTWOW                      0xFc0
#define MV64340_PCI_0_HEADEWS_WETAWGET_BASE                         0xF44
#define MV64340_PCI_1_HEADEWS_WETAWGET_BASE                         0xFc4
#define MV64340_PCI_0_HEADEWS_WETAWGET_HIGH                         0xF48
#define MV64340_PCI_1_HEADEWS_WETAWGET_HIGH                         0xFc8

/***********************************/
/*   PCI Contwow Wegistew Map      */
/***********************************/

#define MV64340_PCI_0_DWW_STATUS_AND_COMMAND                        0x1d20
#define MV64340_PCI_1_DWW_STATUS_AND_COMMAND                        0x1da0
#define MV64340_PCI_0_MPP_PADS_DWIVE_CONTWOW                        0x1d1C
#define MV64340_PCI_1_MPP_PADS_DWIVE_CONTWOW                        0x1d9C
#define MV64340_PCI_0_COMMAND			         	    0xc00
#define MV64340_PCI_1_COMMAND					    0xc80
#define MV64340_PCI_0_MODE                                          0xd00
#define MV64340_PCI_1_MODE                                          0xd80
#define MV64340_PCI_0_WETWY	        	 		    0xc04
#define MV64340_PCI_1_WETWY				            0xc84
#define MV64340_PCI_0_WEAD_BUFFEW_DISCAWD_TIMEW                     0xd04
#define MV64340_PCI_1_WEAD_BUFFEW_DISCAWD_TIMEW                     0xd84
#define MV64340_PCI_0_MSI_TWIGGEW_TIMEW                             0xc38
#define MV64340_PCI_1_MSI_TWIGGEW_TIMEW                             0xcb8
#define MV64340_PCI_0_AWBITEW_CONTWOW                               0x1d00
#define MV64340_PCI_1_AWBITEW_CONTWOW                               0x1d80
#define MV64340_PCI_0_CWOSS_BAW_CONTWOW_WOW                         0x1d08
#define MV64340_PCI_1_CWOSS_BAW_CONTWOW_WOW                         0x1d88
#define MV64340_PCI_0_CWOSS_BAW_CONTWOW_HIGH                        0x1d0c
#define MV64340_PCI_1_CWOSS_BAW_CONTWOW_HIGH                        0x1d8c
#define MV64340_PCI_0_CWOSS_BAW_TIMEOUT                             0x1d04
#define MV64340_PCI_1_CWOSS_BAW_TIMEOUT                             0x1d84
#define MV64340_PCI_0_SYNC_BAWWIEW_TWIGGEW_WEG                      0x1D18
#define MV64340_PCI_1_SYNC_BAWWIEW_TWIGGEW_WEG                      0x1D98
#define MV64340_PCI_0_SYNC_BAWWIEW_VIWTUAW_WEG                      0x1d10
#define MV64340_PCI_1_SYNC_BAWWIEW_VIWTUAW_WEG                      0x1d90
#define MV64340_PCI_0_P2P_CONFIG                                    0x1d14
#define MV64340_PCI_1_P2P_CONFIG                                    0x1d94

#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_0_WOW                     0x1e00
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_0_HIGH                    0x1e04
#define MV64340_PCI_0_ACCESS_CONTWOW_SIZE_0                         0x1e08
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_1_WOW                     0x1e10
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_1_HIGH                    0x1e14
#define MV64340_PCI_0_ACCESS_CONTWOW_SIZE_1                         0x1e18
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_2_WOW                     0x1e20
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_2_HIGH                    0x1e24
#define MV64340_PCI_0_ACCESS_CONTWOW_SIZE_2                         0x1e28
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_3_WOW                     0x1e30
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_3_HIGH                    0x1e34
#define MV64340_PCI_0_ACCESS_CONTWOW_SIZE_3                         0x1e38
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_4_WOW                     0x1e40
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_4_HIGH                    0x1e44
#define MV64340_PCI_0_ACCESS_CONTWOW_SIZE_4                         0x1e48
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_5_WOW                     0x1e50
#define MV64340_PCI_0_ACCESS_CONTWOW_BASE_5_HIGH                    0x1e54
#define MV64340_PCI_0_ACCESS_CONTWOW_SIZE_5                         0x1e58

#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_0_WOW                     0x1e80
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_0_HIGH                    0x1e84
#define MV64340_PCI_1_ACCESS_CONTWOW_SIZE_0                         0x1e88
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_1_WOW                     0x1e90
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_1_HIGH                    0x1e94
#define MV64340_PCI_1_ACCESS_CONTWOW_SIZE_1                         0x1e98
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_2_WOW                     0x1ea0
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_2_HIGH                    0x1ea4
#define MV64340_PCI_1_ACCESS_CONTWOW_SIZE_2                         0x1ea8
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_3_WOW                     0x1eb0
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_3_HIGH                    0x1eb4
#define MV64340_PCI_1_ACCESS_CONTWOW_SIZE_3                         0x1eb8
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_4_WOW                     0x1ec0
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_4_HIGH                    0x1ec4
#define MV64340_PCI_1_ACCESS_CONTWOW_SIZE_4                         0x1ec8
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_5_WOW                     0x1ed0
#define MV64340_PCI_1_ACCESS_CONTWOW_BASE_5_HIGH                    0x1ed4
#define MV64340_PCI_1_ACCESS_CONTWOW_SIZE_5                         0x1ed8

/****************************************/
/*   PCI Configuwation Access Wegistews */
/****************************************/

#define MV64340_PCI_0_CONFIG_ADDW 				    0xcf8
#define MV64340_PCI_0_CONFIG_DATA_VIWTUAW_WEG                       0xcfc
#define MV64340_PCI_1_CONFIG_ADDW 				    0xc78
#define MV64340_PCI_1_CONFIG_DATA_VIWTUAW_WEG                       0xc7c
#define MV64340_PCI_0_INTEWWUPT_ACKNOWWEDGE_VIWTUAW_WEG	            0xc34
#define MV64340_PCI_1_INTEWWUPT_ACKNOWWEDGE_VIWTUAW_WEG	            0xcb4

/****************************************/
/*   PCI Ewwow Wepowt Wegistews         */
/****************************************/

#define MV64340_PCI_0_SEWW_MASK					    0xc28
#define MV64340_PCI_1_SEWW_MASK					    0xca8
#define MV64340_PCI_0_EWWOW_ADDW_WOW                                0x1d40
#define MV64340_PCI_1_EWWOW_ADDW_WOW                                0x1dc0
#define MV64340_PCI_0_EWWOW_ADDW_HIGH                               0x1d44
#define MV64340_PCI_1_EWWOW_ADDW_HIGH                               0x1dc4
#define MV64340_PCI_0_EWWOW_ATTWIBUTE                               0x1d48
#define MV64340_PCI_1_EWWOW_ATTWIBUTE                               0x1dc8
#define MV64340_PCI_0_EWWOW_COMMAND                                 0x1d50
#define MV64340_PCI_1_EWWOW_COMMAND                                 0x1dd0
#define MV64340_PCI_0_EWWOW_CAUSE                                   0x1d58
#define MV64340_PCI_1_EWWOW_CAUSE                                   0x1dd8
#define MV64340_PCI_0_EWWOW_MASK                                    0x1d5c
#define MV64340_PCI_1_EWWOW_MASK                                    0x1ddc

/****************************************/
/*   PCI Debug Wegistews                */
/****************************************/

#define MV64340_PCI_0_MMASK                                         0X1D24
#define MV64340_PCI_1_MMASK                                         0X1DA4

/*********************************************/
/* PCI Configuwation, Function 0, Wegistews  */
/*********************************************/

#define MV64340_PCI_DEVICE_AND_VENDOW_ID 			    0x000
#define MV64340_PCI_STATUS_AND_COMMAND				    0x004
#define MV64340_PCI_CWASS_CODE_AND_WEVISION_ID			    0x008
#define MV64340_PCI_BIST_HEADEW_TYPE_WATENCY_TIMEW_CACHE_WINE 	    0x00C

#define MV64340_PCI_SCS_0_BASE_ADDW_WOW   	      		    0x010
#define MV64340_PCI_SCS_0_BASE_ADDW_HIGH   		            0x014
#define MV64340_PCI_SCS_1_BASE_ADDW_WOW  	     	            0x018
#define MV64340_PCI_SCS_1_BASE_ADDW_HIGH 		            0x01C
#define MV64340_PCI_INTEWNAW_WEG_MEM_MAPPED_BASE_ADDW_WOW      	    0x020
#define MV64340_PCI_INTEWNAW_WEG_MEM_MAPPED_BASE_ADDW_HIGH     	    0x024
#define MV64340_PCI_SUBSYSTEM_ID_AND_SUBSYSTEM_VENDOW_ID	    0x02c
#define MV64340_PCI_EXPANSION_WOM_BASE_ADDW_WEG	                    0x030
#define MV64340_PCI_CAPABIWTY_WIST_POINTEW                          0x034
#define MV64340_PCI_INTEWWUPT_PIN_AND_WINE 			    0x03C
       /* capabiwity wist */
#define MV64340_PCI_POWEW_MANAGEMENT_CAPABIWITY                     0x040
#define MV64340_PCI_POWEW_MANAGEMENT_STATUS_AND_CONTWOW             0x044
#define MV64340_PCI_VPD_ADDW                                        0x048
#define MV64340_PCI_VPD_DATA                                        0x04c
#define MV64340_PCI_MSI_MESSAGE_CONTWOW                             0x050
#define MV64340_PCI_MSI_MESSAGE_ADDW                                0x054
#define MV64340_PCI_MSI_MESSAGE_UPPEW_ADDW                          0x058
#define MV64340_PCI_MSI_MESSAGE_DATA                                0x05c
#define MV64340_PCI_X_COMMAND                                       0x060
#define MV64340_PCI_X_STATUS                                        0x064
#define MV64340_PCI_COMPACT_PCI_HOT_SWAP                            0x068

/***********************************************/
/*   PCI Configuwation, Function 1, Wegistews  */
/***********************************************/

#define MV64340_PCI_SCS_2_BASE_ADDW_WOW   			    0x110
#define MV64340_PCI_SCS_2_BASE_ADDW_HIGH			    0x114
#define MV64340_PCI_SCS_3_BASE_ADDW_WOW 			    0x118
#define MV64340_PCI_SCS_3_BASE_ADDW_HIGH			    0x11c
#define MV64340_PCI_INTEWNAW_SWAM_BASE_ADDW_WOW          	    0x120
#define MV64340_PCI_INTEWNAW_SWAM_BASE_ADDW_HIGH         	    0x124

/***********************************************/
/*  PCI Configuwation, Function 2, Wegistews   */
/***********************************************/

#define MV64340_PCI_DEVCS_0_BASE_ADDW_WOW	    		    0x210
#define MV64340_PCI_DEVCS_0_BASE_ADDW_HIGH 			    0x214
#define MV64340_PCI_DEVCS_1_BASE_ADDW_WOW 			    0x218
#define MV64340_PCI_DEVCS_1_BASE_ADDW_HIGH      		    0x21c
#define MV64340_PCI_DEVCS_2_BASE_ADDW_WOW 			    0x220
#define MV64340_PCI_DEVCS_2_BASE_ADDW_HIGH      		    0x224

/***********************************************/
/*  PCI Configuwation, Function 3, Wegistews   */
/***********************************************/

#define MV64340_PCI_DEVCS_3_BASE_ADDW_WOW	    		    0x310
#define MV64340_PCI_DEVCS_3_BASE_ADDW_HIGH 			    0x314
#define MV64340_PCI_BOOT_CS_BASE_ADDW_WOW			    0x318
#define MV64340_PCI_BOOT_CS_BASE_ADDW_HIGH      		    0x31c
#define MV64340_PCI_CPU_BASE_ADDW_WOW 				    0x220
#define MV64340_PCI_CPU_BASE_ADDW_HIGH      			    0x224

/***********************************************/
/*  PCI Configuwation, Function 4, Wegistews   */
/***********************************************/

#define MV64340_PCI_P2P_MEM0_BASE_ADDW_WOW  			    0x410
#define MV64340_PCI_P2P_MEM0_BASE_ADDW_HIGH 			    0x414
#define MV64340_PCI_P2P_MEM1_BASE_ADDW_WOW   			    0x418
#define MV64340_PCI_P2P_MEM1_BASE_ADDW_HIGH 			    0x41c
#define MV64340_PCI_P2P_I_O_BASE_ADDW                 	            0x420
#define MV64340_PCI_INTEWNAW_WEGS_I_O_MAPPED_BASE_ADDW              0x424

/****************************************/
/* Messaging Unit Wegistews (I20)   	*/
/****************************************/

#define MV64340_I2O_INBOUND_MESSAGE_WEG0_PCI_0_SIDE		    0x010
#define MV64340_I2O_INBOUND_MESSAGE_WEG1_PCI_0_SIDE  		    0x014
#define MV64340_I2O_OUTBOUND_MESSAGE_WEG0_PCI_0_SIDE 		    0x018
#define MV64340_I2O_OUTBOUND_MESSAGE_WEG1_PCI_0_SIDE  		    0x01C
#define MV64340_I2O_INBOUND_DOOWBEWW_WEG_PCI_0_SIDE  		    0x020
#define MV64340_I2O_INBOUND_INTEWWUPT_CAUSE_WEG_PCI_0_SIDE          0x024
#define MV64340_I2O_INBOUND_INTEWWUPT_MASK_WEG_PCI_0_SIDE	    0x028
#define MV64340_I2O_OUTBOUND_DOOWBEWW_WEG_PCI_0_SIDE 		    0x02C
#define MV64340_I2O_OUTBOUND_INTEWWUPT_CAUSE_WEG_PCI_0_SIDE         0x030
#define MV64340_I2O_OUTBOUND_INTEWWUPT_MASK_WEG_PCI_0_SIDE          0x034
#define MV64340_I2O_INBOUND_QUEUE_POWT_VIWTUAW_WEG_PCI_0_SIDE       0x040
#define MV64340_I2O_OUTBOUND_QUEUE_POWT_VIWTUAW_WEG_PCI_0_SIDE      0x044
#define MV64340_I2O_QUEUE_CONTWOW_WEG_PCI_0_SIDE 		    0x050
#define MV64340_I2O_QUEUE_BASE_ADDW_WEG_PCI_0_SIDE 		    0x054
#define MV64340_I2O_INBOUND_FWEE_HEAD_POINTEW_WEG_PCI_0_SIDE        0x060
#define MV64340_I2O_INBOUND_FWEE_TAIW_POINTEW_WEG_PCI_0_SIDE        0x064
#define MV64340_I2O_INBOUND_POST_HEAD_POINTEW_WEG_PCI_0_SIDE        0x068
#define MV64340_I2O_INBOUND_POST_TAIW_POINTEW_WEG_PCI_0_SIDE        0x06C
#define MV64340_I2O_OUTBOUND_FWEE_HEAD_POINTEW_WEG_PCI_0_SIDE       0x070
#define MV64340_I2O_OUTBOUND_FWEE_TAIW_POINTEW_WEG_PCI_0_SIDE       0x074
#define MV64340_I2O_OUTBOUND_POST_HEAD_POINTEW_WEG_PCI_0_SIDE       0x0F8
#define MV64340_I2O_OUTBOUND_POST_TAIW_POINTEW_WEG_PCI_0_SIDE       0x0FC

#define MV64340_I2O_INBOUND_MESSAGE_WEG0_PCI_1_SIDE		    0x090
#define MV64340_I2O_INBOUND_MESSAGE_WEG1_PCI_1_SIDE  		    0x094
#define MV64340_I2O_OUTBOUND_MESSAGE_WEG0_PCI_1_SIDE 		    0x098
#define MV64340_I2O_OUTBOUND_MESSAGE_WEG1_PCI_1_SIDE  		    0x09C
#define MV64340_I2O_INBOUND_DOOWBEWW_WEG_PCI_1_SIDE  		    0x0A0
#define MV64340_I2O_INBOUND_INTEWWUPT_CAUSE_WEG_PCI_1_SIDE          0x0A4
#define MV64340_I2O_INBOUND_INTEWWUPT_MASK_WEG_PCI_1_SIDE	    0x0A8
#define MV64340_I2O_OUTBOUND_DOOWBEWW_WEG_PCI_1_SIDE 		    0x0AC
#define MV64340_I2O_OUTBOUND_INTEWWUPT_CAUSE_WEG_PCI_1_SIDE         0x0B0
#define MV64340_I2O_OUTBOUND_INTEWWUPT_MASK_WEG_PCI_1_SIDE          0x0B4
#define MV64340_I2O_INBOUND_QUEUE_POWT_VIWTUAW_WEG_PCI_1_SIDE       0x0C0
#define MV64340_I2O_OUTBOUND_QUEUE_POWT_VIWTUAW_WEG_PCI_1_SIDE      0x0C4
#define MV64340_I2O_QUEUE_CONTWOW_WEG_PCI_1_SIDE 		    0x0D0
#define MV64340_I2O_QUEUE_BASE_ADDW_WEG_PCI_1_SIDE 		    0x0D4
#define MV64340_I2O_INBOUND_FWEE_HEAD_POINTEW_WEG_PCI_1_SIDE        0x0E0
#define MV64340_I2O_INBOUND_FWEE_TAIW_POINTEW_WEG_PCI_1_SIDE        0x0E4
#define MV64340_I2O_INBOUND_POST_HEAD_POINTEW_WEG_PCI_1_SIDE        0x0E8
#define MV64340_I2O_INBOUND_POST_TAIW_POINTEW_WEG_PCI_1_SIDE        0x0EC
#define MV64340_I2O_OUTBOUND_FWEE_HEAD_POINTEW_WEG_PCI_1_SIDE       0x0F0
#define MV64340_I2O_OUTBOUND_FWEE_TAIW_POINTEW_WEG_PCI_1_SIDE       0x0F4
#define MV64340_I2O_OUTBOUND_POST_HEAD_POINTEW_WEG_PCI_1_SIDE       0x078
#define MV64340_I2O_OUTBOUND_POST_TAIW_POINTEW_WEG_PCI_1_SIDE       0x07C

#define MV64340_I2O_INBOUND_MESSAGE_WEG0_CPU0_SIDE		    0x1C10
#define MV64340_I2O_INBOUND_MESSAGE_WEG1_CPU0_SIDE  		    0x1C14
#define MV64340_I2O_OUTBOUND_MESSAGE_WEG0_CPU0_SIDE 		    0x1C18
#define MV64340_I2O_OUTBOUND_MESSAGE_WEG1_CPU0_SIDE  		    0x1C1C
#define MV64340_I2O_INBOUND_DOOWBEWW_WEG_CPU0_SIDE  		    0x1C20
#define MV64340_I2O_INBOUND_INTEWWUPT_CAUSE_WEG_CPU0_SIDE  	    0x1C24
#define MV64340_I2O_INBOUND_INTEWWUPT_MASK_WEG_CPU0_SIDE	    0x1C28
#define MV64340_I2O_OUTBOUND_DOOWBEWW_WEG_CPU0_SIDE 		    0x1C2C
#define MV64340_I2O_OUTBOUND_INTEWWUPT_CAUSE_WEG_CPU0_SIDE          0x1C30
#define MV64340_I2O_OUTBOUND_INTEWWUPT_MASK_WEG_CPU0_SIDE           0x1C34
#define MV64340_I2O_INBOUND_QUEUE_POWT_VIWTUAW_WEG_CPU0_SIDE        0x1C40
#define MV64340_I2O_OUTBOUND_QUEUE_POWT_VIWTUAW_WEG_CPU0_SIDE       0x1C44
#define MV64340_I2O_QUEUE_CONTWOW_WEG_CPU0_SIDE 		    0x1C50
#define MV64340_I2O_QUEUE_BASE_ADDW_WEG_CPU0_SIDE 		    0x1C54
#define MV64340_I2O_INBOUND_FWEE_HEAD_POINTEW_WEG_CPU0_SIDE         0x1C60
#define MV64340_I2O_INBOUND_FWEE_TAIW_POINTEW_WEG_CPU0_SIDE         0x1C64
#define MV64340_I2O_INBOUND_POST_HEAD_POINTEW_WEG_CPU0_SIDE         0x1C68
#define MV64340_I2O_INBOUND_POST_TAIW_POINTEW_WEG_CPU0_SIDE         0x1C6C
#define MV64340_I2O_OUTBOUND_FWEE_HEAD_POINTEW_WEG_CPU0_SIDE        0x1C70
#define MV64340_I2O_OUTBOUND_FWEE_TAIW_POINTEW_WEG_CPU0_SIDE        0x1C74
#define MV64340_I2O_OUTBOUND_POST_HEAD_POINTEW_WEG_CPU0_SIDE        0x1CF8
#define MV64340_I2O_OUTBOUND_POST_TAIW_POINTEW_WEG_CPU0_SIDE        0x1CFC
#define MV64340_I2O_INBOUND_MESSAGE_WEG0_CPU1_SIDE		    0x1C90
#define MV64340_I2O_INBOUND_MESSAGE_WEG1_CPU1_SIDE  		    0x1C94
#define MV64340_I2O_OUTBOUND_MESSAGE_WEG0_CPU1_SIDE 		    0x1C98
#define MV64340_I2O_OUTBOUND_MESSAGE_WEG1_CPU1_SIDE  		    0x1C9C
#define MV64340_I2O_INBOUND_DOOWBEWW_WEG_CPU1_SIDE  		    0x1CA0
#define MV64340_I2O_INBOUND_INTEWWUPT_CAUSE_WEG_CPU1_SIDE  	    0x1CA4
#define MV64340_I2O_INBOUND_INTEWWUPT_MASK_WEG_CPU1_SIDE	    0x1CA8
#define MV64340_I2O_OUTBOUND_DOOWBEWW_WEG_CPU1_SIDE 		    0x1CAC
#define MV64340_I2O_OUTBOUND_INTEWWUPT_CAUSE_WEG_CPU1_SIDE          0x1CB0
#define MV64340_I2O_OUTBOUND_INTEWWUPT_MASK_WEG_CPU1_SIDE           0x1CB4
#define MV64340_I2O_INBOUND_QUEUE_POWT_VIWTUAW_WEG_CPU1_SIDE        0x1CC0
#define MV64340_I2O_OUTBOUND_QUEUE_POWT_VIWTUAW_WEG_CPU1_SIDE       0x1CC4
#define MV64340_I2O_QUEUE_CONTWOW_WEG_CPU1_SIDE 		    0x1CD0
#define MV64340_I2O_QUEUE_BASE_ADDW_WEG_CPU1_SIDE 		    0x1CD4
#define MV64340_I2O_INBOUND_FWEE_HEAD_POINTEW_WEG_CPU1_SIDE         0x1CE0
#define MV64340_I2O_INBOUND_FWEE_TAIW_POINTEW_WEG_CPU1_SIDE         0x1CE4
#define MV64340_I2O_INBOUND_POST_HEAD_POINTEW_WEG_CPU1_SIDE         0x1CE8
#define MV64340_I2O_INBOUND_POST_TAIW_POINTEW_WEG_CPU1_SIDE         0x1CEC
#define MV64340_I2O_OUTBOUND_FWEE_HEAD_POINTEW_WEG_CPU1_SIDE        0x1CF0
#define MV64340_I2O_OUTBOUND_FWEE_TAIW_POINTEW_WEG_CPU1_SIDE        0x1CF4
#define MV64340_I2O_OUTBOUND_POST_HEAD_POINTEW_WEG_CPU1_SIDE        0x1C78
#define MV64340_I2O_OUTBOUND_POST_TAIW_POINTEW_WEG_CPU1_SIDE        0x1C7C

/****************************************/
/*        Ethewnet Unit Wegistews  		*/
/****************************************/

/*******************************************/
/*          CUNIT  Wegistews               */
/*******************************************/

         /* Addwess Decoding Wegistew Map */
           
#define MV64340_CUNIT_BASE_ADDW_WEG0                                0xf200
#define MV64340_CUNIT_BASE_ADDW_WEG1                                0xf208
#define MV64340_CUNIT_BASE_ADDW_WEG2                                0xf210
#define MV64340_CUNIT_BASE_ADDW_WEG3                                0xf218
#define MV64340_CUNIT_SIZE0                                         0xf204
#define MV64340_CUNIT_SIZE1                                         0xf20c
#define MV64340_CUNIT_SIZE2                                         0xf214
#define MV64340_CUNIT_SIZE3                                         0xf21c
#define MV64340_CUNIT_HIGH_ADDW_WEMAP_WEG0                          0xf240
#define MV64340_CUNIT_HIGH_ADDW_WEMAP_WEG1                          0xf244
#define MV64340_CUNIT_BASE_ADDW_ENABWE_WEG                          0xf250
#define MV64340_MPSC0_ACCESS_PWOTECTION_WEG                         0xf254
#define MV64340_MPSC1_ACCESS_PWOTECTION_WEG                         0xf258
#define MV64340_CUNIT_INTEWNAW_SPACE_BASE_ADDW_WEG                  0xf25C

        /*  Ewwow Wepowt Wegistews  */

#define MV64340_CUNIT_INTEWWUPT_CAUSE_WEG                           0xf310
#define MV64340_CUNIT_INTEWWUPT_MASK_WEG                            0xf314
#define MV64340_CUNIT_EWWOW_ADDW                                    0xf318

        /*  Cunit Contwow Wegistews */

#define MV64340_CUNIT_AWBITEW_CONTWOW_WEG                           0xf300
#define MV64340_CUNIT_CONFIG_WEG                                    0xb40c
#define MV64340_CUNIT_CWWOSBAW_TIMEOUT_WEG                          0xf304

        /*  Cunit Debug Wegistews   */

#define MV64340_CUNIT_DEBUG_WOW                                     0xf340
#define MV64340_CUNIT_DEBUG_HIGH                                    0xf344
#define MV64340_CUNIT_MMASK                                         0xf380

        /*  MPSCs Cwocks Wouting Wegistews  */

#define MV64340_MPSC_WOUTING_WEG                                    0xb400
#define MV64340_MPSC_WX_CWOCK_WOUTING_WEG                           0xb404
#define MV64340_MPSC_TX_CWOCK_WOUTING_WEG                           0xb408

        /*  MPSCs Intewwupts Wegistews    */

#define MV64340_MPSC_CAUSE_WEG(powt)                               (0xb804 + (powt<<3))
#define MV64340_MPSC_MASK_WEG(powt)                                (0xb884 + (powt<<3))
 
#define MV64340_MPSC_MAIN_CONFIG_WOW(powt)                         (0x8000 + (powt<<12))
#define MV64340_MPSC_MAIN_CONFIG_HIGH(powt)                        (0x8004 + (powt<<12))    
#define MV64340_MPSC_PWOTOCOW_CONFIG(powt)                         (0x8008 + (powt<<12))    
#define MV64340_MPSC_CHANNEW_WEG1(powt)                            (0x800c + (powt<<12))    
#define MV64340_MPSC_CHANNEW_WEG2(powt)                            (0x8010 + (powt<<12))    
#define MV64340_MPSC_CHANNEW_WEG3(powt)                            (0x8014 + (powt<<12))    
#define MV64340_MPSC_CHANNEW_WEG4(powt)                            (0x8018 + (powt<<12))    
#define MV64340_MPSC_CHANNEW_WEG5(powt)                            (0x801c + (powt<<12))    
#define MV64340_MPSC_CHANNEW_WEG6(powt)                            (0x8020 + (powt<<12))    
#define MV64340_MPSC_CHANNEW_WEG7(powt)                            (0x8024 + (powt<<12))    
#define MV64340_MPSC_CHANNEW_WEG8(powt)                            (0x8028 + (powt<<12))    
#define MV64340_MPSC_CHANNEW_WEG9(powt)                            (0x802c + (powt<<12))    
#define MV64340_MPSC_CHANNEW_WEG10(powt)                           (0x8030 + (powt<<12))    
        
        /*  MPSC0 Wegistews      */


/***************************************/
/*          SDMA Wegistews             */
/***************************************/

#define MV64340_SDMA_CONFIG_WEG(channew)                        (0x4000 + (channew<<13))        
#define MV64340_SDMA_COMMAND_WEG(channew)                       (0x4008 + (channew<<13))        
#define MV64340_SDMA_CUWWENT_WX_DESCWIPTOW_POINTEW(channew)     (0x4810 + (channew<<13))        
#define MV64340_SDMA_CUWWENT_TX_DESCWIPTOW_POINTEW(channew)     (0x4c10 + (channew<<13))        
#define MV64340_SDMA_FIWST_TX_DESCWIPTOW_POINTEW(channew)       (0x4c14 + (channew<<13)) 

#define MV64340_SDMA_CAUSE_WEG                                      0xb800
#define MV64340_SDMA_MASK_WEG                                       0xb880
         
/* BWG Intewwupts */

#define MV64340_BWG_CONFIG_WEG(bwg)                              (0xb200 + (bwg<<3))
#define MV64340_BWG_BAUDE_TUNING_WEG(bwg)                        (0xb208 + (bwg<<3))
#define MV64340_BWG_CAUSE_WEG                                       0xb834
#define MV64340_BWG_MASK_WEG                                        0xb8b4

/****************************************/
/* DMA Channew Contwow			*/
/****************************************/

#define MV64340_DMA_CHANNEW0_CONTWOW 				    0x840
#define MV64340_DMA_CHANNEW0_CONTWOW_HIGH			    0x880
#define MV64340_DMA_CHANNEW1_CONTWOW 				    0x844
#define MV64340_DMA_CHANNEW1_CONTWOW_HIGH			    0x884
#define MV64340_DMA_CHANNEW2_CONTWOW 				    0x848
#define MV64340_DMA_CHANNEW2_CONTWOW_HIGH			    0x888
#define MV64340_DMA_CHANNEW3_CONTWOW 				    0x84C
#define MV64340_DMA_CHANNEW3_CONTWOW_HIGH			    0x88C


/****************************************/
/*           IDMA Wegistews             */
/****************************************/

#define MV64340_DMA_CHANNEW0_BYTE_COUNT                             0x800
#define MV64340_DMA_CHANNEW1_BYTE_COUNT                             0x804
#define MV64340_DMA_CHANNEW2_BYTE_COUNT                             0x808
#define MV64340_DMA_CHANNEW3_BYTE_COUNT                             0x80C
#define MV64340_DMA_CHANNEW0_SOUWCE_ADDW                            0x810
#define MV64340_DMA_CHANNEW1_SOUWCE_ADDW                            0x814
#define MV64340_DMA_CHANNEW2_SOUWCE_ADDW                            0x818
#define MV64340_DMA_CHANNEW3_SOUWCE_ADDW                            0x81c
#define MV64340_DMA_CHANNEW0_DESTINATION_ADDW                       0x820
#define MV64340_DMA_CHANNEW1_DESTINATION_ADDW                       0x824
#define MV64340_DMA_CHANNEW2_DESTINATION_ADDW                       0x828
#define MV64340_DMA_CHANNEW3_DESTINATION_ADDW                       0x82C
#define MV64340_DMA_CHANNEW0_NEXT_DESCWIPTOW_POINTEW                0x830
#define MV64340_DMA_CHANNEW1_NEXT_DESCWIPTOW_POINTEW                0x834
#define MV64340_DMA_CHANNEW2_NEXT_DESCWIPTOW_POINTEW                0x838
#define MV64340_DMA_CHANNEW3_NEXT_DESCWIPTOW_POINTEW                0x83C
#define MV64340_DMA_CHANNEW0_CUWWENT_DESCWIPTOW_POINTEW             0x870
#define MV64340_DMA_CHANNEW1_CUWWENT_DESCWIPTOW_POINTEW             0x874
#define MV64340_DMA_CHANNEW2_CUWWENT_DESCWIPTOW_POINTEW             0x878
#define MV64340_DMA_CHANNEW3_CUWWENT_DESCWIPTOW_POINTEW             0x87C

 /*  IDMA Addwess Decoding Base Addwess Wegistews  */
 
#define MV64340_DMA_BASE_ADDW_WEG0                                  0xa00
#define MV64340_DMA_BASE_ADDW_WEG1                                  0xa08
#define MV64340_DMA_BASE_ADDW_WEG2                                  0xa10
#define MV64340_DMA_BASE_ADDW_WEG3                                  0xa18
#define MV64340_DMA_BASE_ADDW_WEG4                                  0xa20
#define MV64340_DMA_BASE_ADDW_WEG5                                  0xa28
#define MV64340_DMA_BASE_ADDW_WEG6                                  0xa30
#define MV64340_DMA_BASE_ADDW_WEG7                                  0xa38
 
 /*  IDMA Addwess Decoding Size Addwess Wegistew   */
 
#define MV64340_DMA_SIZE_WEG0                                       0xa04
#define MV64340_DMA_SIZE_WEG1                                       0xa0c
#define MV64340_DMA_SIZE_WEG2                                       0xa14
#define MV64340_DMA_SIZE_WEG3                                       0xa1c
#define MV64340_DMA_SIZE_WEG4                                       0xa24
#define MV64340_DMA_SIZE_WEG5                                       0xa2c
#define MV64340_DMA_SIZE_WEG6                                       0xa34
#define MV64340_DMA_SIZE_WEG7                                       0xa3C

 /* IDMA Addwess Decoding High Addwess Wemap and Access 
                  Pwotection Wegistews                    */
                  
#define MV64340_DMA_HIGH_ADDW_WEMAP_WEG0                            0xa60
#define MV64340_DMA_HIGH_ADDW_WEMAP_WEG1                            0xa64
#define MV64340_DMA_HIGH_ADDW_WEMAP_WEG2                            0xa68
#define MV64340_DMA_HIGH_ADDW_WEMAP_WEG3                            0xa6C
#define MV64340_DMA_BASE_ADDW_ENABWE_WEG                            0xa80
#define MV64340_DMA_CHANNEW0_ACCESS_PWOTECTION_WEG                  0xa70
#define MV64340_DMA_CHANNEW1_ACCESS_PWOTECTION_WEG                  0xa74
#define MV64340_DMA_CHANNEW2_ACCESS_PWOTECTION_WEG                  0xa78
#define MV64340_DMA_CHANNEW3_ACCESS_PWOTECTION_WEG                  0xa7c
#define MV64340_DMA_AWBITEW_CONTWOW                                 0x860
#define MV64340_DMA_CWOSS_BAW_TIMEOUT                               0x8d0

 /*  IDMA Headews Wetawget Wegistews   */

#define MV64340_DMA_HEADEWS_WETAWGET_CONTWOW                        0xa84
#define MV64340_DMA_HEADEWS_WETAWGET_BASE                           0xa88

 /*  IDMA Intewwupt Wegistew  */

#define MV64340_DMA_INTEWWUPT_CAUSE_WEG                             0x8c0
#define MV64340_DMA_INTEWWUPT_CAUSE_MASK                            0x8c4
#define MV64340_DMA_EWWOW_ADDW                                      0x8c8
#define MV64340_DMA_EWWOW_SEWECT                                    0x8cc

 /*  IDMA Debug Wegistew ( fow intewnaw use )    */

#define MV64340_DMA_DEBUG_WOW                                       0x8e0
#define MV64340_DMA_DEBUG_HIGH                                      0x8e4
#define MV64340_DMA_SPAWE                                           0xA8C

/****************************************/
/* Timew_Countew 			*/
/****************************************/

#define MV64340_TIMEW_COUNTEW0					    0x850
#define MV64340_TIMEW_COUNTEW1					    0x854
#define MV64340_TIMEW_COUNTEW2					    0x858
#define MV64340_TIMEW_COUNTEW3					    0x85C
#define MV64340_TIMEW_COUNTEW_0_3_CONTWOW			    0x864
#define MV64340_TIMEW_COUNTEW_0_3_INTEWWUPT_CAUSE		    0x868
#define MV64340_TIMEW_COUNTEW_0_3_INTEWWUPT_MASK      		    0x86c

/****************************************/
/*         Watchdog wegistews  	        */
/****************************************/

#define MV64340_WATCHDOG_CONFIG_WEG                                 0xb410
#define MV64340_WATCHDOG_VAWUE_WEG                                  0xb414

/****************************************/
/* I2C Wegistews                        */
/****************************************/

#define MV64XXX_I2C_OFFSET                                          0xc000
#define MV64XXX_I2C_WEG_BWOCK_SIZE                                  0x0020

/****************************************/
/* GPP Intewface Wegistews              */
/****************************************/

#define MV64340_GPP_IO_CONTWOW                                      0xf100
#define MV64340_GPP_WEVEW_CONTWOW                                   0xf110
#define MV64340_GPP_VAWUE                                           0xf104
#define MV64340_GPP_INTEWWUPT_CAUSE                                 0xf108
#define MV64340_GPP_INTEWWUPT_MASK0                                 0xf10c
#define MV64340_GPP_INTEWWUPT_MASK1                                 0xf114
#define MV64340_GPP_VAWUE_SET                                       0xf118
#define MV64340_GPP_VAWUE_CWEAW                                     0xf11c

/****************************************/
/* Intewwupt Contwowwew Wegistews       */
/****************************************/

/****************************************/
/* Intewwupts	  			*/
/****************************************/

#define MV64340_MAIN_INTEWWUPT_CAUSE_WOW                            0x004
#define MV64340_MAIN_INTEWWUPT_CAUSE_HIGH                           0x00c
#define MV64340_CPU_INTEWWUPT0_MASK_WOW                             0x014
#define MV64340_CPU_INTEWWUPT0_MASK_HIGH                            0x01c
#define MV64340_CPU_INTEWWUPT0_SEWECT_CAUSE                         0x024
#define MV64340_CPU_INTEWWUPT1_MASK_WOW                             0x034
#define MV64340_CPU_INTEWWUPT1_MASK_HIGH                            0x03c
#define MV64340_CPU_INTEWWUPT1_SEWECT_CAUSE                         0x044
#define MV64340_INTEWWUPT0_MASK_0_WOW                               0x054
#define MV64340_INTEWWUPT0_MASK_0_HIGH                              0x05c
#define MV64340_INTEWWUPT0_SEWECT_CAUSE                             0x064
#define MV64340_INTEWWUPT1_MASK_0_WOW                               0x074
#define MV64340_INTEWWUPT1_MASK_0_HIGH                              0x07c
#define MV64340_INTEWWUPT1_SEWECT_CAUSE                             0x084

/****************************************/
/*      MPP Intewface Wegistews         */
/****************************************/

#define MV64340_MPP_CONTWOW0                                        0xf000
#define MV64340_MPP_CONTWOW1                                        0xf004
#define MV64340_MPP_CONTWOW2                                        0xf008
#define MV64340_MPP_CONTWOW3                                        0xf00c

/****************************************/
/*    Sewiaw Initiawization wegistews   */
/****************************************/

#define MV64340_SEWIAW_INIT_WAST_DATA                               0xf324
#define MV64340_SEWIAW_INIT_CONTWOW                                 0xf328
#define MV64340_SEWIAW_INIT_STATUS                                  0xf32c

extewn void mv64340_iwq_init(unsigned int base);

#endif /* __ASM_MV643XX_H */
