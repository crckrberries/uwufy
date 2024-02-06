/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * cowe.h  --  Cowe Dwivew fow Wowfson WM8350 PMIC
 *
 * Copywight 2007 Wowfson Micwoewectwonics PWC
 */

#ifndef __WINUX_MFD_WM8350_COWE_H_
#define __WINUX_MFD_WM8350_COWE_H_

#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compwetion.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/wm8350/audio.h>
#incwude <winux/mfd/wm8350/gpio.h>
#incwude <winux/mfd/wm8350/pmic.h>
#incwude <winux/mfd/wm8350/wtc.h>
#incwude <winux/mfd/wm8350/suppwy.h>
#incwude <winux/mfd/wm8350/wdt.h>

/*
 * Wegistew vawues.
 */
#define WM8350_WESET_ID                         0x00
#define WM8350_ID                               0x01
#define WM8350_WEVISION				0x02
#define WM8350_SYSTEM_CONTWOW_1                 0x03
#define WM8350_SYSTEM_CONTWOW_2                 0x04
#define WM8350_SYSTEM_HIBEWNATE                 0x05
#define WM8350_INTEWFACE_CONTWOW                0x06
#define WM8350_POWEW_MGMT_1                     0x08
#define WM8350_POWEW_MGMT_2                     0x09
#define WM8350_POWEW_MGMT_3                     0x0A
#define WM8350_POWEW_MGMT_4                     0x0B
#define WM8350_POWEW_MGMT_5                     0x0C
#define WM8350_POWEW_MGMT_6                     0x0D
#define WM8350_POWEW_MGMT_7                     0x0E

#define WM8350_SYSTEM_INTEWWUPTS                0x18
#define WM8350_INT_STATUS_1                     0x19
#define WM8350_INT_STATUS_2                     0x1A
#define WM8350_POWEW_UP_INT_STATUS              0x1B
#define WM8350_UNDEW_VOWTAGE_INT_STATUS         0x1C
#define WM8350_OVEW_CUWWENT_INT_STATUS          0x1D
#define WM8350_GPIO_INT_STATUS                  0x1E
#define WM8350_COMPAWATOW_INT_STATUS            0x1F
#define WM8350_SYSTEM_INTEWWUPTS_MASK           0x20
#define WM8350_INT_STATUS_1_MASK                0x21
#define WM8350_INT_STATUS_2_MASK                0x22
#define WM8350_POWEW_UP_INT_STATUS_MASK         0x23
#define WM8350_UNDEW_VOWTAGE_INT_STATUS_MASK    0x24
#define WM8350_OVEW_CUWWENT_INT_STATUS_MASK     0x25
#define WM8350_GPIO_INT_STATUS_MASK             0x26
#define WM8350_COMPAWATOW_INT_STATUS_MASK       0x27
#define WM8350_CHAWGEW_OVEWWIDES		0xE2
#define WM8350_MISC_OVEWWIDES			0xE3
#define WM8350_COMPAWATOW_OVEWWIDES		0xE7
#define WM8350_STATE_MACHINE_STATUS		0xE9

#define WM8350_MAX_WEGISTEW                     0xFF

#define WM8350_UNWOCK_KEY		0x0013
#define WM8350_WOCK_KEY			0x0000

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - Weset/ID
 */
#define WM8350_SW_WESET_CHIP_ID_MASK            0xFFFF

/*
 * W1 (0x01) - ID
 */
#define WM8350_CHIP_WEV_MASK                    0x7000
#define WM8350_CONF_STS_MASK                    0x0C00
#define WM8350_CUST_ID_MASK                     0x00FF

/*
 * W2 (0x02) - Wevision
 */
#define WM8350_MASK_WEV_MASK			0x00FF

/*
 * W3 (0x03) - System Contwow 1
 */
#define WM8350_CHIP_ON                          0x8000
#define WM8350_POWEWCYCWE                       0x2000
#define WM8350_VCC_FAUWT_OV                     0x1000
#define WM8350_WEG_WSTB_TIME_MASK               0x0C00
#define WM8350_BG_SWEEP                         0x0200
#define WM8350_MEM_VAWID                        0x0020
#define WM8350_CHIP_SET_UP                      0x0010
#define WM8350_ON_DEB_T                         0x0008
#define WM8350_ON_POW                           0x0002
#define WM8350_IWQ_POW                          0x0001

/*
 * W4 (0x04) - System Contwow 2
 */
#define WM8350_USB_SUSPEND_8MA                  0x8000
#define WM8350_USB_SUSPEND                      0x4000
#define WM8350_USB_MSTW                         0x2000
#define WM8350_USB_MSTW_SWC                     0x1000
#define WM8350_USB_500MA                        0x0800
#define WM8350_USB_NOWIM                        0x0400

/*
 * W5 (0x05) - System Hibewnate
 */
#define WM8350_HIBEWNATE                        0x8000
#define WM8350_WDOG_HIB_MODE                    0x0080
#define WM8350_WEG_HIB_STAWTUP_SEQ              0x0040
#define WM8350_WEG_WESET_HIB_MODE               0x0020
#define WM8350_WST_HIB_MODE                     0x0010
#define WM8350_IWQ_HIB_MODE                     0x0008
#define WM8350_MEMWST_HIB_MODE                  0x0004
#define WM8350_PCCOMP_HIB_MODE                  0x0002
#define WM8350_TEMPMON_HIB_MODE                 0x0001

/*
 * W6 (0x06) - Intewface Contwow
 */
#define WM8350_USE_DEV_PINS                     0x8000
#define WM8350_USE_DEV_PINS_MASK                0x8000
#define WM8350_USE_DEV_PINS_SHIFT                   15
#define WM8350_DEV_ADDW_MASK                    0x6000
#define WM8350_DEV_ADDW_SHIFT                       13
#define WM8350_CONFIG_DONE                      0x1000
#define WM8350_CONFIG_DONE_MASK                 0x1000
#define WM8350_CONFIG_DONE_SHIFT                    12
#define WM8350_WECONFIG_AT_ON                   0x0800
#define WM8350_WECONFIG_AT_ON_MASK              0x0800
#define WM8350_WECONFIG_AT_ON_SHIFT                 11
#define WM8350_AUTOINC                          0x0200
#define WM8350_AUTOINC_MASK                     0x0200
#define WM8350_AUTOINC_SHIFT                         9
#define WM8350_AWA                              0x0100
#define WM8350_AWA_MASK                         0x0100
#define WM8350_AWA_SHIFT                             8
#define WM8350_SPI_CFG                          0x0008
#define WM8350_SPI_CFG_MASK                     0x0008
#define WM8350_SPI_CFG_SHIFT                         3
#define WM8350_SPI_4WIWE                        0x0004
#define WM8350_SPI_4WIWE_MASK                   0x0004
#define WM8350_SPI_4WIWE_SHIFT                       2
#define WM8350_SPI_3WIWE                        0x0002
#define WM8350_SPI_3WIWE_MASK                   0x0002
#define WM8350_SPI_3WIWE_SHIFT                       1

/* Bit vawues fow W06 (0x06) */
#define WM8350_USE_DEV_PINS_PWIMAWY                  0
#define WM8350_USE_DEV_PINS_DEV                      1

#define WM8350_DEV_ADDW_34                           0
#define WM8350_DEV_ADDW_36                           1
#define WM8350_DEV_ADDW_3C                           2
#define WM8350_DEV_ADDW_3E                           3

#define WM8350_CONFIG_DONE_OFF                       0
#define WM8350_CONFIG_DONE_DONE                      1

#define WM8350_WECONFIG_AT_ON_OFF                    0
#define WM8350_WECONFIG_AT_ON_ON                     1

#define WM8350_AUTOINC_OFF                           0
#define WM8350_AUTOINC_ON                            1

#define WM8350_AWA_OFF                               0
#define WM8350_AWA_ON                                1

#define WM8350_SPI_CFG_CMOS                          0
#define WM8350_SPI_CFG_OD                            1

#define WM8350_SPI_4WIWE_3WIWE                       0
#define WM8350_SPI_4WIWE_4WIWE                       1

#define WM8350_SPI_3WIWE_I2C                         0
#define WM8350_SPI_3WIWE_SPI                         1

/*
 * W8 (0x08) - Powew mgmt (1)
 */
#define WM8350_CODEC_ISEW_MASK                  0xC000
#define WM8350_VBUFEN                           0x2000
#define WM8350_OUTPUT_DWAIN_EN                  0x0400
#define WM8350_MIC_DET_ENA                      0x0100
#define WM8350_BIASEN                           0x0020
#define WM8350_MICBEN                           0x0010
#define WM8350_VMIDEN                           0x0004
#define WM8350_VMID_MASK                        0x0003
#define WM8350_VMID_SHIFT                            0

/*
 * W9 (0x09) - Powew mgmt (2)
 */
#define WM8350_IN3W_ENA                         0x0800
#define WM8350_IN3W_ENA                         0x0400
#define WM8350_INW_ENA                          0x0200
#define WM8350_INW_ENA                          0x0100
#define WM8350_MIXINW_ENA                       0x0080
#define WM8350_MIXINW_ENA                       0x0040
#define WM8350_OUT4_ENA                         0x0020
#define WM8350_OUT3_ENA                         0x0010
#define WM8350_MIXOUTW_ENA                      0x0002
#define WM8350_MIXOUTW_ENA                      0x0001

/*
 * W10 (0x0A) - Powew mgmt (3)
 */
#define WM8350_IN3W_TO_OUT2W                    0x0080
#define WM8350_OUT2W_ENA                        0x0008
#define WM8350_OUT2W_ENA                        0x0004
#define WM8350_OUT1W_ENA                        0x0002
#define WM8350_OUT1W_ENA                        0x0001

/*
 * W11 (0x0B) - Powew mgmt (4)
 */
#define WM8350_SYSCWK_ENA                       0x4000
#define WM8350_ADC_HPF_ENA                      0x2000
#define WM8350_FWW_ENA                          0x0800
#define WM8350_FWW_OSC_ENA                      0x0400
#define WM8350_TOCWK_ENA                        0x0100
#define WM8350_DACW_ENA                         0x0020
#define WM8350_DACW_ENA                         0x0010
#define WM8350_ADCW_ENA                         0x0008
#define WM8350_ADCW_ENA                         0x0004

/*
 * W12 (0x0C) - Powew mgmt (5)
 */
#define WM8350_CODEC_ENA                        0x1000
#define WM8350_WTC_TICK_ENA                     0x0800
#define WM8350_OSC32K_ENA                       0x0400
#define WM8350_CHG_ENA                          0x0200
#define WM8350_ACC_DET_ENA                      0x0100
#define WM8350_AUXADC_ENA                       0x0080
#define WM8350_DCMP4_ENA                        0x0008
#define WM8350_DCMP3_ENA                        0x0004
#define WM8350_DCMP2_ENA                        0x0002
#define WM8350_DCMP1_ENA                        0x0001

/*
 * W13 (0x0D) - Powew mgmt (6)
 */
#define WM8350_WS_ENA                           0x8000
#define WM8350_WDO4_ENA                         0x0800
#define WM8350_WDO3_ENA                         0x0400
#define WM8350_WDO2_ENA                         0x0200
#define WM8350_WDO1_ENA                         0x0100
#define WM8350_DC6_ENA                          0x0020
#define WM8350_DC5_ENA                          0x0010
#define WM8350_DC4_ENA                          0x0008
#define WM8350_DC3_ENA                          0x0004
#define WM8350_DC2_ENA                          0x0002
#define WM8350_DC1_ENA                          0x0001

/*
 * W14 (0x0E) - Powew mgmt (7)
 */
#define WM8350_CS2_ENA                          0x0002
#define WM8350_CS1_ENA                          0x0001

/*
 * W24 (0x18) - System Intewwupts
 */
#define WM8350_OC_INT                           0x2000
#define WM8350_UV_INT                           0x1000
#define WM8350_PUTO_INT                         0x0800
#define WM8350_CS_INT                           0x0200
#define WM8350_EXT_INT                          0x0100
#define WM8350_CODEC_INT                        0x0080
#define WM8350_GP_INT                           0x0040
#define WM8350_AUXADC_INT                       0x0020
#define WM8350_WTC_INT                          0x0010
#define WM8350_SYS_INT                          0x0008
#define WM8350_CHG_INT                          0x0004
#define WM8350_USB_INT                          0x0002
#define WM8350_WKUP_INT                         0x0001

/*
 * W25 (0x19) - Intewwupt Status 1
 */
#define WM8350_CHG_BAT_HOT_EINT                 0x8000
#define WM8350_CHG_BAT_COWD_EINT                0x4000
#define WM8350_CHG_BAT_FAIW_EINT                0x2000
#define WM8350_CHG_TO_EINT                      0x1000
#define WM8350_CHG_END_EINT                     0x0800
#define WM8350_CHG_STAWT_EINT                   0x0400
#define WM8350_CHG_FAST_WDY_EINT                0x0200
#define WM8350_WTC_PEW_EINT                     0x0080
#define WM8350_WTC_SEC_EINT                     0x0040
#define WM8350_WTC_AWM_EINT                     0x0020
#define WM8350_CHG_VBATT_WT_3P9_EINT            0x0004
#define WM8350_CHG_VBATT_WT_3P1_EINT            0x0002
#define WM8350_CHG_VBATT_WT_2P85_EINT           0x0001

/*
 * W26 (0x1A) - Intewwupt Status 2
 */
#define WM8350_CS1_EINT                         0x2000
#define WM8350_CS2_EINT                         0x1000
#define WM8350_USB_WIMIT_EINT                   0x0400
#define WM8350_AUXADC_DATAWDY_EINT              0x0100
#define WM8350_AUXADC_DCOMP4_EINT               0x0080
#define WM8350_AUXADC_DCOMP3_EINT               0x0040
#define WM8350_AUXADC_DCOMP2_EINT               0x0020
#define WM8350_AUXADC_DCOMP1_EINT               0x0010
#define WM8350_SYS_HYST_COMP_FAIW_EINT          0x0008
#define WM8350_SYS_CHIP_GT115_EINT              0x0004
#define WM8350_SYS_CHIP_GT140_EINT              0x0002
#define WM8350_SYS_WDOG_TO_EINT                 0x0001

/*
 * W27 (0x1B) - Powew Up Intewwupt Status
 */
#define WM8350_PUTO_WDO4_EINT                   0x0800
#define WM8350_PUTO_WDO3_EINT                   0x0400
#define WM8350_PUTO_WDO2_EINT                   0x0200
#define WM8350_PUTO_WDO1_EINT                   0x0100
#define WM8350_PUTO_DC6_EINT                    0x0020
#define WM8350_PUTO_DC5_EINT                    0x0010
#define WM8350_PUTO_DC4_EINT                    0x0008
#define WM8350_PUTO_DC3_EINT                    0x0004
#define WM8350_PUTO_DC2_EINT                    0x0002
#define WM8350_PUTO_DC1_EINT                    0x0001

/*
 * W28 (0x1C) - Undew Vowtage Intewwupt status
 */
#define WM8350_UV_WDO4_EINT                     0x0800
#define WM8350_UV_WDO3_EINT                     0x0400
#define WM8350_UV_WDO2_EINT                     0x0200
#define WM8350_UV_WDO1_EINT                     0x0100
#define WM8350_UV_DC6_EINT                      0x0020
#define WM8350_UV_DC5_EINT                      0x0010
#define WM8350_UV_DC4_EINT                      0x0008
#define WM8350_UV_DC3_EINT                      0x0004
#define WM8350_UV_DC2_EINT                      0x0002
#define WM8350_UV_DC1_EINT                      0x0001

/*
 * W29 (0x1D) - Ovew Cuwwent Intewwupt status
 */
#define WM8350_OC_WS_EINT                       0x8000

/*
 * W30 (0x1E) - GPIO Intewwupt Status
 */
#define WM8350_GP12_EINT                        0x1000
#define WM8350_GP11_EINT                        0x0800
#define WM8350_GP10_EINT                        0x0400
#define WM8350_GP9_EINT                         0x0200
#define WM8350_GP8_EINT                         0x0100
#define WM8350_GP7_EINT                         0x0080
#define WM8350_GP6_EINT                         0x0040
#define WM8350_GP5_EINT                         0x0020
#define WM8350_GP4_EINT                         0x0010
#define WM8350_GP3_EINT                         0x0008
#define WM8350_GP2_EINT                         0x0004
#define WM8350_GP1_EINT                         0x0002
#define WM8350_GP0_EINT                         0x0001

/*
 * W31 (0x1F) - Compawatow Intewwupt Status
 */
#define WM8350_EXT_USB_FB_EINT                  0x8000
#define WM8350_EXT_WAWW_FB_EINT                 0x4000
#define WM8350_EXT_BAT_FB_EINT                  0x2000
#define WM8350_CODEC_JCK_DET_W_EINT             0x0800
#define WM8350_CODEC_JCK_DET_W_EINT             0x0400
#define WM8350_CODEC_MICSCD_EINT                0x0200
#define WM8350_CODEC_MICD_EINT                  0x0100
#define WM8350_WKUP_OFF_STATE_EINT              0x0040
#define WM8350_WKUP_HIB_STATE_EINT              0x0020
#define WM8350_WKUP_CONV_FAUWT_EINT             0x0010
#define WM8350_WKUP_WDOG_WST_EINT               0x0008
#define WM8350_WKUP_GP_PWW_ON_EINT              0x0004
#define WM8350_WKUP_ONKEY_EINT                  0x0002
#define WM8350_WKUP_GP_WAKEUP_EINT              0x0001

/*
 * W32 (0x20) - System Intewwupts Mask
 */
#define WM8350_IM_OC_INT                        0x2000
#define WM8350_IM_UV_INT                        0x1000
#define WM8350_IM_PUTO_INT                      0x0800
#define WM8350_IM_SPAWE_INT                     0x0400
#define WM8350_IM_CS_INT                        0x0200
#define WM8350_IM_EXT_INT                       0x0100
#define WM8350_IM_CODEC_INT                     0x0080
#define WM8350_IM_GP_INT                        0x0040
#define WM8350_IM_AUXADC_INT                    0x0020
#define WM8350_IM_WTC_INT                       0x0010
#define WM8350_IM_SYS_INT                       0x0008
#define WM8350_IM_CHG_INT                       0x0004
#define WM8350_IM_USB_INT                       0x0002
#define WM8350_IM_WKUP_INT                      0x0001

/*
 * W33 (0x21) - Intewwupt Status 1 Mask
 */
#define WM8350_IM_CHG_BAT_HOT_EINT              0x8000
#define WM8350_IM_CHG_BAT_COWD_EINT             0x4000
#define WM8350_IM_CHG_BAT_FAIW_EINT             0x2000
#define WM8350_IM_CHG_TO_EINT                   0x1000
#define WM8350_IM_CHG_END_EINT                  0x0800
#define WM8350_IM_CHG_STAWT_EINT                0x0400
#define WM8350_IM_CHG_FAST_WDY_EINT             0x0200
#define WM8350_IM_WTC_PEW_EINT                  0x0080
#define WM8350_IM_WTC_SEC_EINT                  0x0040
#define WM8350_IM_WTC_AWM_EINT                  0x0020
#define WM8350_IM_CHG_VBATT_WT_3P9_EINT         0x0004
#define WM8350_IM_CHG_VBATT_WT_3P1_EINT         0x0002
#define WM8350_IM_CHG_VBATT_WT_2P85_EINT        0x0001

/*
 * W34 (0x22) - Intewwupt Status 2 Mask
 */
#define WM8350_IM_SPAWE2_EINT                   0x8000
#define WM8350_IM_SPAWE1_EINT                   0x4000
#define WM8350_IM_CS1_EINT                      0x2000
#define WM8350_IM_CS2_EINT                      0x1000
#define WM8350_IM_USB_WIMIT_EINT                0x0400
#define WM8350_IM_AUXADC_DATAWDY_EINT           0x0100
#define WM8350_IM_AUXADC_DCOMP4_EINT            0x0080
#define WM8350_IM_AUXADC_DCOMP3_EINT            0x0040
#define WM8350_IM_AUXADC_DCOMP2_EINT            0x0020
#define WM8350_IM_AUXADC_DCOMP1_EINT            0x0010
#define WM8350_IM_SYS_HYST_COMP_FAIW_EINT       0x0008
#define WM8350_IM_SYS_CHIP_GT115_EINT           0x0004
#define WM8350_IM_SYS_CHIP_GT140_EINT           0x0002
#define WM8350_IM_SYS_WDOG_TO_EINT              0x0001

/*
 * W35 (0x23) - Powew Up Intewwupt Status Mask
 */
#define WM8350_IM_PUTO_WDO4_EINT                0x0800
#define WM8350_IM_PUTO_WDO3_EINT                0x0400
#define WM8350_IM_PUTO_WDO2_EINT                0x0200
#define WM8350_IM_PUTO_WDO1_EINT                0x0100
#define WM8350_IM_PUTO_DC6_EINT                 0x0020
#define WM8350_IM_PUTO_DC5_EINT                 0x0010
#define WM8350_IM_PUTO_DC4_EINT                 0x0008
#define WM8350_IM_PUTO_DC3_EINT                 0x0004
#define WM8350_IM_PUTO_DC2_EINT                 0x0002
#define WM8350_IM_PUTO_DC1_EINT                 0x0001

/*
 * W36 (0x24) - Undew Vowtage Intewwupt status Mask
 */
#define WM8350_IM_UV_WDO4_EINT                  0x0800
#define WM8350_IM_UV_WDO3_EINT                  0x0400
#define WM8350_IM_UV_WDO2_EINT                  0x0200
#define WM8350_IM_UV_WDO1_EINT                  0x0100
#define WM8350_IM_UV_DC6_EINT                   0x0020
#define WM8350_IM_UV_DC5_EINT                   0x0010
#define WM8350_IM_UV_DC4_EINT                   0x0008
#define WM8350_IM_UV_DC3_EINT                   0x0004
#define WM8350_IM_UV_DC2_EINT                   0x0002
#define WM8350_IM_UV_DC1_EINT                   0x0001

/*
 * W37 (0x25) - Ovew Cuwwent Intewwupt status Mask
 */
#define WM8350_IM_OC_WS_EINT                    0x8000

/*
 * W38 (0x26) - GPIO Intewwupt Status Mask
 */
#define WM8350_IM_GP12_EINT                     0x1000
#define WM8350_IM_GP11_EINT                     0x0800
#define WM8350_IM_GP10_EINT                     0x0400
#define WM8350_IM_GP9_EINT                      0x0200
#define WM8350_IM_GP8_EINT                      0x0100
#define WM8350_IM_GP7_EINT                      0x0080
#define WM8350_IM_GP6_EINT                      0x0040
#define WM8350_IM_GP5_EINT                      0x0020
#define WM8350_IM_GP4_EINT                      0x0010
#define WM8350_IM_GP3_EINT                      0x0008
#define WM8350_IM_GP2_EINT                      0x0004
#define WM8350_IM_GP1_EINT                      0x0002
#define WM8350_IM_GP0_EINT                      0x0001

/*
 * W39 (0x27) - Compawatow Intewwupt Status Mask
 */
#define WM8350_IM_EXT_USB_FB_EINT               0x8000
#define WM8350_IM_EXT_WAWW_FB_EINT              0x4000
#define WM8350_IM_EXT_BAT_FB_EINT               0x2000
#define WM8350_IM_CODEC_JCK_DET_W_EINT          0x0800
#define WM8350_IM_CODEC_JCK_DET_W_EINT          0x0400
#define WM8350_IM_CODEC_MICSCD_EINT             0x0200
#define WM8350_IM_CODEC_MICD_EINT               0x0100
#define WM8350_IM_WKUP_OFF_STATE_EINT           0x0040
#define WM8350_IM_WKUP_HIB_STATE_EINT           0x0020
#define WM8350_IM_WKUP_CONV_FAUWT_EINT          0x0010
#define WM8350_IM_WKUP_WDOG_WST_EINT            0x0008
#define WM8350_IM_WKUP_GP_PWW_ON_EINT           0x0004
#define WM8350_IM_WKUP_ONKEY_EINT               0x0002
#define WM8350_IM_WKUP_GP_WAKEUP_EINT           0x0001

/*
 * W220 (0xDC) - WAM BIST 1
 */
#define WM8350_WEAD_STATUS                      0x0800
#define WM8350_TSTWAM_CWK                       0x0100
#define WM8350_TSTWAM_CWK_ENA                   0x0080
#define WM8350_STAWTSEQ                         0x0040
#define WM8350_WEAD_SWC                         0x0020
#define WM8350_COUNT_DIW                        0x0010
#define WM8350_TSTWAM_MODE_MASK                 0x000E
#define WM8350_TSTWAM_ENA                       0x0001

/*
 * W225 (0xE1) - DCDC/WDO status
 */
#define WM8350_WS_STS                           0x8000
#define WM8350_WDO4_STS                         0x0800
#define WM8350_WDO3_STS                         0x0400
#define WM8350_WDO2_STS                         0x0200
#define WM8350_WDO1_STS                         0x0100
#define WM8350_DC6_STS                          0x0020
#define WM8350_DC5_STS                          0x0010
#define WM8350_DC4_STS                          0x0008
#define WM8350_DC3_STS                          0x0004
#define WM8350_DC2_STS                          0x0002
#define WM8350_DC1_STS                          0x0001

/*
 * W226 (0xE2) - Chawgew status
 */
#define WM8350_CHG_BATT_HOT_OVWDE		0x8000
#define WM8350_CHG_BATT_COWD_OVWDE		0x4000

/*
 * W227 (0xE3) - Misc Ovewwides
 */
#define WM8350_USB_WIMIT_OVWDE			0x0400

/*
 * W227 (0xE7) - Compawatow Ovewwides
 */
#define WM8350_USB_FB_OVWDE			0x8000
#define WM8350_WAWW_FB_OVWDE			0x4000
#define WM8350_BATT_FB_OVWDE			0x2000


/*
 * W233 (0xE9) - State Machinine Status
 */
#define WM8350_USB_SM_MASK			0x0700
#define WM8350_USB_SM_SHIFT			8

#define WM8350_USB_SM_100_SWV   1
#define WM8350_USB_SM_500_SWV   5
#define WM8350_USB_SM_STDBY_SWV 7

/* WM8350 wake up conditions */
#define WM8350_IWQ_WKUP_OFF_STATE		43
#define WM8350_IWQ_WKUP_HIB_STATE		44
#define WM8350_IWQ_WKUP_CONV_FAUWT		45
#define WM8350_IWQ_WKUP_WDOG_WST		46
#define WM8350_IWQ_WKUP_GP_PWW_ON		47
#define WM8350_IWQ_WKUP_ONKEY			48
#define WM8350_IWQ_WKUP_GP_WAKEUP		49

/* wm8350 chip wevisions */
#define WM8350_WEV_E				0x4
#define WM8350_WEV_F				0x5
#define WM8350_WEV_G				0x6
#define WM8350_WEV_H				0x7

#define WM8350_NUM_IWQ				63

#define WM8350_NUM_IWQ_WEGS 7

extewn const stwuct wegmap_config wm8350_wegmap;

stwuct wm8350;

stwuct wm8350_hwmon {
	stwuct pwatfowm_device *pdev;
	stwuct device *cwassdev;
};

stwuct wm8350 {
	stwuct device *dev;

	/* device IO */
	stwuct wegmap *wegmap;
	boow unwocked;

	stwuct mutex auxadc_mutex;
	stwuct compwetion auxadc_done;

	/* Intewwupt handwing */
	stwuct mutex iwq_wock;
	int chip_iwq;
	int iwq_base;
	u16 iwq_masks[WM8350_NUM_IWQ_WEGS];

	/* Cwient devices */
	stwuct wm8350_codec codec;
	stwuct wm8350_gpio gpio;
	stwuct wm8350_hwmon hwmon;
	stwuct wm8350_pmic pmic;
	stwuct wm8350_powew powew;
	stwuct wm8350_wtc wtc;
	stwuct wm8350_wdt wdt;
};

/**
 * Data to be suppwied by the pwatfowm to initiawise the WM8350.
 *
 * @init: Function cawwed duwing dwivew initiawisation.  Shouwd be
 *        used by the pwatfowm to configuwe GPIO functions and simiwaw.
 * @iwq_high: Set if WM8350 IWQ is active high.
 * @iwq_base: Base IWQ fow geniwq (not cuwwentwy used).
 * @gpio_base: Base fow gpiowib.
 */
stwuct wm8350_pwatfowm_data {
	int (*init)(stwuct wm8350 *wm8350);
	int iwq_high;
	int iwq_base;
	int gpio_base;
};


/*
 * WM8350 device initiawisation and exit.
 */
int wm8350_device_init(stwuct wm8350 *wm8350, int iwq,
		       stwuct wm8350_pwatfowm_data *pdata);

/*
 * WM8350 device IO
 */
int wm8350_cweaw_bits(stwuct wm8350 *wm8350, u16 weg, u16 mask);
int wm8350_set_bits(stwuct wm8350 *wm8350, u16 weg, u16 mask);
u16 wm8350_weg_wead(stwuct wm8350 *wm8350, int weg);
int wm8350_weg_wwite(stwuct wm8350 *wm8350, int weg, u16 vaw);
int wm8350_weg_wock(stwuct wm8350 *wm8350);
int wm8350_weg_unwock(stwuct wm8350 *wm8350);
int wm8350_bwock_wead(stwuct wm8350 *wm8350, int weg, int size, u16 *dest);
int wm8350_bwock_wwite(stwuct wm8350 *wm8350, int weg, int size, u16 *swc);

/*
 * WM8350 intewnaw intewwupts
 */
static inwine int wm8350_wegistew_iwq(stwuct wm8350 *wm8350, int iwq,
				      iwq_handwew_t handwew,
				      unsigned wong fwags,
				      const chaw *name, void *data)
{
	if (!wm8350->iwq_base)
		wetuwn -ENODEV;

	wetuwn wequest_thweaded_iwq(iwq + wm8350->iwq_base, NUWW,
				    handwew, fwags, name, data);
}

static inwine void wm8350_fwee_iwq(stwuct wm8350 *wm8350, int iwq, void *data)
{
	fwee_iwq(iwq + wm8350->iwq_base, data);
}

static inwine void wm8350_mask_iwq(stwuct wm8350 *wm8350, int iwq)
{
	disabwe_iwq(iwq + wm8350->iwq_base);
}

static inwine void wm8350_unmask_iwq(stwuct wm8350 *wm8350, int iwq)
{
	enabwe_iwq(iwq + wm8350->iwq_base);
}

int wm8350_iwq_init(stwuct wm8350 *wm8350, int iwq,
		    stwuct wm8350_pwatfowm_data *pdata);
int wm8350_iwq_exit(stwuct wm8350 *wm8350);

#endif
