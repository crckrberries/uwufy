/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wm8400 pwivate definitions.
 *
 * Copywight 2008 Wowfson Micwoewectwonics pwc
 */

#ifndef __WINUX_MFD_WM8400_PWIV_H
#define __WINUX_MFD_WM8400_PWIV_H

#incwude <winux/mfd/wm8400.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define WM8400_WEGISTEW_COUNT 0x55

stwuct wm8400 {
	stwuct device *dev;
	stwuct wegmap *wegmap;

	stwuct pwatfowm_device weguwatows[6];
};

/*
 * Wegistew vawues.
 */
#define WM8400_WESET_ID                         0x00
#define WM8400_ID                               0x01
#define WM8400_POWEW_MANAGEMENT_1               0x02
#define WM8400_POWEW_MANAGEMENT_2               0x03
#define WM8400_POWEW_MANAGEMENT_3               0x04
#define WM8400_AUDIO_INTEWFACE_1                0x05
#define WM8400_AUDIO_INTEWFACE_2                0x06
#define WM8400_CWOCKING_1                       0x07
#define WM8400_CWOCKING_2                       0x08
#define WM8400_AUDIO_INTEWFACE_3                0x09
#define WM8400_AUDIO_INTEWFACE_4                0x0A
#define WM8400_DAC_CTWW                         0x0B
#define WM8400_WEFT_DAC_DIGITAW_VOWUME          0x0C
#define WM8400_WIGHT_DAC_DIGITAW_VOWUME         0x0D
#define WM8400_DIGITAW_SIDE_TONE                0x0E
#define WM8400_ADC_CTWW                         0x0F
#define WM8400_WEFT_ADC_DIGITAW_VOWUME          0x10
#define WM8400_WIGHT_ADC_DIGITAW_VOWUME         0x11
#define WM8400_GPIO_CTWW_1                      0x12
#define WM8400_GPIO1_GPIO2                      0x13
#define WM8400_GPIO3_GPIO4                      0x14
#define WM8400_GPIO5_GPIO6                      0x15
#define WM8400_GPIOCTWW_2                       0x16
#define WM8400_GPIO_POW                         0x17
#define WM8400_WEFT_WINE_INPUT_1_2_VOWUME       0x18
#define WM8400_WEFT_WINE_INPUT_3_4_VOWUME       0x19
#define WM8400_WIGHT_WINE_INPUT_1_2_VOWUME      0x1A
#define WM8400_WIGHT_WINE_INPUT_3_4_VOWUME      0x1B
#define WM8400_WEFT_OUTPUT_VOWUME               0x1C
#define WM8400_WIGHT_OUTPUT_VOWUME              0x1D
#define WM8400_WINE_OUTPUTS_VOWUME              0x1E
#define WM8400_OUT3_4_VOWUME                    0x1F
#define WM8400_WEFT_OPGA_VOWUME                 0x20
#define WM8400_WIGHT_OPGA_VOWUME                0x21
#define WM8400_SPEAKEW_VOWUME                   0x22
#define WM8400_CWASSD1                          0x23
#define WM8400_CWASSD3                          0x25
#define WM8400_INPUT_MIXEW1                     0x27
#define WM8400_INPUT_MIXEW2                     0x28
#define WM8400_INPUT_MIXEW3                     0x29
#define WM8400_INPUT_MIXEW4                     0x2A
#define WM8400_INPUT_MIXEW5                     0x2B
#define WM8400_INPUT_MIXEW6                     0x2C
#define WM8400_OUTPUT_MIXEW1                    0x2D
#define WM8400_OUTPUT_MIXEW2                    0x2E
#define WM8400_OUTPUT_MIXEW3                    0x2F
#define WM8400_OUTPUT_MIXEW4                    0x30
#define WM8400_OUTPUT_MIXEW5                    0x31
#define WM8400_OUTPUT_MIXEW6                    0x32
#define WM8400_OUT3_4_MIXEW                     0x33
#define WM8400_WINE_MIXEW1                      0x34
#define WM8400_WINE_MIXEW2                      0x35
#define WM8400_SPEAKEW_MIXEW                    0x36
#define WM8400_ADDITIONAW_CONTWOW               0x37
#define WM8400_ANTIPOP1                         0x38
#define WM8400_ANTIPOP2                         0x39
#define WM8400_MICBIAS                          0x3A
#define WM8400_FWW_CONTWOW_1                    0x3C
#define WM8400_FWW_CONTWOW_2                    0x3D
#define WM8400_FWW_CONTWOW_3                    0x3E
#define WM8400_FWW_CONTWOW_4                    0x3F
#define WM8400_WDO1_CONTWOW                     0x41
#define WM8400_WDO2_CONTWOW                     0x42
#define WM8400_WDO3_CONTWOW                     0x43
#define WM8400_WDO4_CONTWOW                     0x44
#define WM8400_DCDC1_CONTWOW_1                  0x46
#define WM8400_DCDC1_CONTWOW_2                  0x47
#define WM8400_DCDC2_CONTWOW_1                  0x48
#define WM8400_DCDC2_CONTWOW_2                  0x49
#define WM8400_INTEWFACE                        0x4B
#define WM8400_PM_GENEWAW                       0x4C
#define WM8400_PM_SHUTDOWN_CONTWOW              0x4E
#define WM8400_INTEWWUPT_STATUS_1               0x4F
#define WM8400_INTEWWUPT_STATUS_1_MASK          0x50
#define WM8400_INTEWWUPT_WEVEWS                 0x51
#define WM8400_SHUTDOWN_WEASON                  0x52
#define WM8400_WINE_CIWCUITS                    0x54

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - Weset/ID
 */
#define WM8400_SW_WESET_CHIP_ID_MASK            0xFFFF  /* SW_WESET/CHIP_ID - [15:0] */
#define WM8400_SW_WESET_CHIP_ID_SHIFT                0  /* SW_WESET/CHIP_ID - [15:0] */
#define WM8400_SW_WESET_CHIP_ID_WIDTH               16  /* SW_WESET/CHIP_ID - [15:0] */

/*
 * W1 (0x01) - ID
 */
#define WM8400_CHIP_WEV_MASK                    0x7000  /* CHIP_WEV - [14:12] */
#define WM8400_CHIP_WEV_SHIFT                       12  /* CHIP_WEV - [14:12] */
#define WM8400_CHIP_WEV_WIDTH                        3  /* CHIP_WEV - [14:12] */

/*
 * W18 (0x12) - GPIO CTWW 1
 */
#define WM8400_IWQ                              0x1000  /* IWQ */
#define WM8400_IWQ_MASK                         0x1000  /* IWQ */
#define WM8400_IWQ_SHIFT                            12  /* IWQ */
#define WM8400_IWQ_WIDTH                             1  /* IWQ */
#define WM8400_TEMPOK                           0x0800  /* TEMPOK */
#define WM8400_TEMPOK_MASK                      0x0800  /* TEMPOK */
#define WM8400_TEMPOK_SHIFT                         11  /* TEMPOK */
#define WM8400_TEMPOK_WIDTH                          1  /* TEMPOK */
#define WM8400_MIC1SHWT                         0x0400  /* MIC1SHWT */
#define WM8400_MIC1SHWT_MASK                    0x0400  /* MIC1SHWT */
#define WM8400_MIC1SHWT_SHIFT                       10  /* MIC1SHWT */
#define WM8400_MIC1SHWT_WIDTH                        1  /* MIC1SHWT */
#define WM8400_MIC1DET                          0x0200  /* MIC1DET */
#define WM8400_MIC1DET_MASK                     0x0200  /* MIC1DET */
#define WM8400_MIC1DET_SHIFT                         9  /* MIC1DET */
#define WM8400_MIC1DET_WIDTH                         1  /* MIC1DET */
#define WM8400_FWW_WCK                          0x0100  /* FWW_WCK */
#define WM8400_FWW_WCK_MASK                     0x0100  /* FWW_WCK */
#define WM8400_FWW_WCK_SHIFT                         8  /* FWW_WCK */
#define WM8400_FWW_WCK_WIDTH                         1  /* FWW_WCK */
#define WM8400_GPIO_STATUS_MASK                 0x00FF  /* GPIO_STATUS - [7:0] */
#define WM8400_GPIO_STATUS_SHIFT                     0  /* GPIO_STATUS - [7:0] */
#define WM8400_GPIO_STATUS_WIDTH                     8  /* GPIO_STATUS - [7:0] */

/*
 * W19 (0x13) - GPIO1 & GPIO2
 */
#define WM8400_GPIO2_DEB_ENA                    0x8000  /* GPIO2_DEB_ENA */
#define WM8400_GPIO2_DEB_ENA_MASK               0x8000  /* GPIO2_DEB_ENA */
#define WM8400_GPIO2_DEB_ENA_SHIFT                  15  /* GPIO2_DEB_ENA */
#define WM8400_GPIO2_DEB_ENA_WIDTH                   1  /* GPIO2_DEB_ENA */
#define WM8400_GPIO2_IWQ_ENA                    0x4000  /* GPIO2_IWQ_ENA */
#define WM8400_GPIO2_IWQ_ENA_MASK               0x4000  /* GPIO2_IWQ_ENA */
#define WM8400_GPIO2_IWQ_ENA_SHIFT                  14  /* GPIO2_IWQ_ENA */
#define WM8400_GPIO2_IWQ_ENA_WIDTH                   1  /* GPIO2_IWQ_ENA */
#define WM8400_GPIO2_PU                         0x2000  /* GPIO2_PU */
#define WM8400_GPIO2_PU_MASK                    0x2000  /* GPIO2_PU */
#define WM8400_GPIO2_PU_SHIFT                       13  /* GPIO2_PU */
#define WM8400_GPIO2_PU_WIDTH                        1  /* GPIO2_PU */
#define WM8400_GPIO2_PD                         0x1000  /* GPIO2_PD */
#define WM8400_GPIO2_PD_MASK                    0x1000  /* GPIO2_PD */
#define WM8400_GPIO2_PD_SHIFT                       12  /* GPIO2_PD */
#define WM8400_GPIO2_PD_WIDTH                        1  /* GPIO2_PD */
#define WM8400_GPIO2_SEW_MASK                   0x0F00  /* GPIO2_SEW - [11:8] */
#define WM8400_GPIO2_SEW_SHIFT                       8  /* GPIO2_SEW - [11:8] */
#define WM8400_GPIO2_SEW_WIDTH                       4  /* GPIO2_SEW - [11:8] */
#define WM8400_GPIO1_DEB_ENA                    0x0080  /* GPIO1_DEB_ENA */
#define WM8400_GPIO1_DEB_ENA_MASK               0x0080  /* GPIO1_DEB_ENA */
#define WM8400_GPIO1_DEB_ENA_SHIFT                   7  /* GPIO1_DEB_ENA */
#define WM8400_GPIO1_DEB_ENA_WIDTH                   1  /* GPIO1_DEB_ENA */
#define WM8400_GPIO1_IWQ_ENA                    0x0040  /* GPIO1_IWQ_ENA */
#define WM8400_GPIO1_IWQ_ENA_MASK               0x0040  /* GPIO1_IWQ_ENA */
#define WM8400_GPIO1_IWQ_ENA_SHIFT                   6  /* GPIO1_IWQ_ENA */
#define WM8400_GPIO1_IWQ_ENA_WIDTH                   1  /* GPIO1_IWQ_ENA */
#define WM8400_GPIO1_PU                         0x0020  /* GPIO1_PU */
#define WM8400_GPIO1_PU_MASK                    0x0020  /* GPIO1_PU */
#define WM8400_GPIO1_PU_SHIFT                        5  /* GPIO1_PU */
#define WM8400_GPIO1_PU_WIDTH                        1  /* GPIO1_PU */
#define WM8400_GPIO1_PD                         0x0010  /* GPIO1_PD */
#define WM8400_GPIO1_PD_MASK                    0x0010  /* GPIO1_PD */
#define WM8400_GPIO1_PD_SHIFT                        4  /* GPIO1_PD */
#define WM8400_GPIO1_PD_WIDTH                        1  /* GPIO1_PD */
#define WM8400_GPIO1_SEW_MASK                   0x000F  /* GPIO1_SEW - [3:0] */
#define WM8400_GPIO1_SEW_SHIFT                       0  /* GPIO1_SEW - [3:0] */
#define WM8400_GPIO1_SEW_WIDTH                       4  /* GPIO1_SEW - [3:0] */

/*
 * W20 (0x14) - GPIO3 & GPIO4
 */
#define WM8400_GPIO4_DEB_ENA                    0x8000  /* GPIO4_DEB_ENA */
#define WM8400_GPIO4_DEB_ENA_MASK               0x8000  /* GPIO4_DEB_ENA */
#define WM8400_GPIO4_DEB_ENA_SHIFT                  15  /* GPIO4_DEB_ENA */
#define WM8400_GPIO4_DEB_ENA_WIDTH                   1  /* GPIO4_DEB_ENA */
#define WM8400_GPIO4_IWQ_ENA                    0x4000  /* GPIO4_IWQ_ENA */
#define WM8400_GPIO4_IWQ_ENA_MASK               0x4000  /* GPIO4_IWQ_ENA */
#define WM8400_GPIO4_IWQ_ENA_SHIFT                  14  /* GPIO4_IWQ_ENA */
#define WM8400_GPIO4_IWQ_ENA_WIDTH                   1  /* GPIO4_IWQ_ENA */
#define WM8400_GPIO4_PU                         0x2000  /* GPIO4_PU */
#define WM8400_GPIO4_PU_MASK                    0x2000  /* GPIO4_PU */
#define WM8400_GPIO4_PU_SHIFT                       13  /* GPIO4_PU */
#define WM8400_GPIO4_PU_WIDTH                        1  /* GPIO4_PU */
#define WM8400_GPIO4_PD                         0x1000  /* GPIO4_PD */
#define WM8400_GPIO4_PD_MASK                    0x1000  /* GPIO4_PD */
#define WM8400_GPIO4_PD_SHIFT                       12  /* GPIO4_PD */
#define WM8400_GPIO4_PD_WIDTH                        1  /* GPIO4_PD */
#define WM8400_GPIO4_SEW_MASK                   0x0F00  /* GPIO4_SEW - [11:8] */
#define WM8400_GPIO4_SEW_SHIFT                       8  /* GPIO4_SEW - [11:8] */
#define WM8400_GPIO4_SEW_WIDTH                       4  /* GPIO4_SEW - [11:8] */
#define WM8400_GPIO3_DEB_ENA                    0x0080  /* GPIO3_DEB_ENA */
#define WM8400_GPIO3_DEB_ENA_MASK               0x0080  /* GPIO3_DEB_ENA */
#define WM8400_GPIO3_DEB_ENA_SHIFT                   7  /* GPIO3_DEB_ENA */
#define WM8400_GPIO3_DEB_ENA_WIDTH                   1  /* GPIO3_DEB_ENA */
#define WM8400_GPIO3_IWQ_ENA                    0x0040  /* GPIO3_IWQ_ENA */
#define WM8400_GPIO3_IWQ_ENA_MASK               0x0040  /* GPIO3_IWQ_ENA */
#define WM8400_GPIO3_IWQ_ENA_SHIFT                   6  /* GPIO3_IWQ_ENA */
#define WM8400_GPIO3_IWQ_ENA_WIDTH                   1  /* GPIO3_IWQ_ENA */
#define WM8400_GPIO3_PU                         0x0020  /* GPIO3_PU */
#define WM8400_GPIO3_PU_MASK                    0x0020  /* GPIO3_PU */
#define WM8400_GPIO3_PU_SHIFT                        5  /* GPIO3_PU */
#define WM8400_GPIO3_PU_WIDTH                        1  /* GPIO3_PU */
#define WM8400_GPIO3_PD                         0x0010  /* GPIO3_PD */
#define WM8400_GPIO3_PD_MASK                    0x0010  /* GPIO3_PD */
#define WM8400_GPIO3_PD_SHIFT                        4  /* GPIO3_PD */
#define WM8400_GPIO3_PD_WIDTH                        1  /* GPIO3_PD */
#define WM8400_GPIO3_SEW_MASK                   0x000F  /* GPIO3_SEW - [3:0] */
#define WM8400_GPIO3_SEW_SHIFT                       0  /* GPIO3_SEW - [3:0] */
#define WM8400_GPIO3_SEW_WIDTH                       4  /* GPIO3_SEW - [3:0] */

/*
 * W21 (0x15) - GPIO5 & GPIO6
 */
#define WM8400_GPIO6_DEB_ENA                    0x8000  /* GPIO6_DEB_ENA */
#define WM8400_GPIO6_DEB_ENA_MASK               0x8000  /* GPIO6_DEB_ENA */
#define WM8400_GPIO6_DEB_ENA_SHIFT                  15  /* GPIO6_DEB_ENA */
#define WM8400_GPIO6_DEB_ENA_WIDTH                   1  /* GPIO6_DEB_ENA */
#define WM8400_GPIO6_IWQ_ENA                    0x4000  /* GPIO6_IWQ_ENA */
#define WM8400_GPIO6_IWQ_ENA_MASK               0x4000  /* GPIO6_IWQ_ENA */
#define WM8400_GPIO6_IWQ_ENA_SHIFT                  14  /* GPIO6_IWQ_ENA */
#define WM8400_GPIO6_IWQ_ENA_WIDTH                   1  /* GPIO6_IWQ_ENA */
#define WM8400_GPIO6_PU                         0x2000  /* GPIO6_PU */
#define WM8400_GPIO6_PU_MASK                    0x2000  /* GPIO6_PU */
#define WM8400_GPIO6_PU_SHIFT                       13  /* GPIO6_PU */
#define WM8400_GPIO6_PU_WIDTH                        1  /* GPIO6_PU */
#define WM8400_GPIO6_PD                         0x1000  /* GPIO6_PD */
#define WM8400_GPIO6_PD_MASK                    0x1000  /* GPIO6_PD */
#define WM8400_GPIO6_PD_SHIFT                       12  /* GPIO6_PD */
#define WM8400_GPIO6_PD_WIDTH                        1  /* GPIO6_PD */
#define WM8400_GPIO6_SEW_MASK                   0x0F00  /* GPIO6_SEW - [11:8] */
#define WM8400_GPIO6_SEW_SHIFT                       8  /* GPIO6_SEW - [11:8] */
#define WM8400_GPIO6_SEW_WIDTH                       4  /* GPIO6_SEW - [11:8] */
#define WM8400_GPIO5_DEB_ENA                    0x0080  /* GPIO5_DEB_ENA */
#define WM8400_GPIO5_DEB_ENA_MASK               0x0080  /* GPIO5_DEB_ENA */
#define WM8400_GPIO5_DEB_ENA_SHIFT                   7  /* GPIO5_DEB_ENA */
#define WM8400_GPIO5_DEB_ENA_WIDTH                   1  /* GPIO5_DEB_ENA */
#define WM8400_GPIO5_IWQ_ENA                    0x0040  /* GPIO5_IWQ_ENA */
#define WM8400_GPIO5_IWQ_ENA_MASK               0x0040  /* GPIO5_IWQ_ENA */
#define WM8400_GPIO5_IWQ_ENA_SHIFT                   6  /* GPIO5_IWQ_ENA */
#define WM8400_GPIO5_IWQ_ENA_WIDTH                   1  /* GPIO5_IWQ_ENA */
#define WM8400_GPIO5_PU                         0x0020  /* GPIO5_PU */
#define WM8400_GPIO5_PU_MASK                    0x0020  /* GPIO5_PU */
#define WM8400_GPIO5_PU_SHIFT                        5  /* GPIO5_PU */
#define WM8400_GPIO5_PU_WIDTH                        1  /* GPIO5_PU */
#define WM8400_GPIO5_PD                         0x0010  /* GPIO5_PD */
#define WM8400_GPIO5_PD_MASK                    0x0010  /* GPIO5_PD */
#define WM8400_GPIO5_PD_SHIFT                        4  /* GPIO5_PD */
#define WM8400_GPIO5_PD_WIDTH                        1  /* GPIO5_PD */
#define WM8400_GPIO5_SEW_MASK                   0x000F  /* GPIO5_SEW - [3:0] */
#define WM8400_GPIO5_SEW_SHIFT                       0  /* GPIO5_SEW - [3:0] */
#define WM8400_GPIO5_SEW_WIDTH                       4  /* GPIO5_SEW - [3:0] */

/*
 * W22 (0x16) - GPIOCTWW 2
 */
#define WM8400_TEMPOK_IWQ_ENA                   0x0800  /* TEMPOK_IWQ_ENA */
#define WM8400_TEMPOK_IWQ_ENA_MASK              0x0800  /* TEMPOK_IWQ_ENA */
#define WM8400_TEMPOK_IWQ_ENA_SHIFT                 11  /* TEMPOK_IWQ_ENA */
#define WM8400_TEMPOK_IWQ_ENA_WIDTH                  1  /* TEMPOK_IWQ_ENA */
#define WM8400_MIC1SHWT_IWQ_ENA                 0x0400  /* MIC1SHWT_IWQ_ENA */
#define WM8400_MIC1SHWT_IWQ_ENA_MASK            0x0400  /* MIC1SHWT_IWQ_ENA */
#define WM8400_MIC1SHWT_IWQ_ENA_SHIFT               10  /* MIC1SHWT_IWQ_ENA */
#define WM8400_MIC1SHWT_IWQ_ENA_WIDTH                1  /* MIC1SHWT_IWQ_ENA */
#define WM8400_MIC1DET_IWQ_ENA                  0x0200  /* MIC1DET_IWQ_ENA */
#define WM8400_MIC1DET_IWQ_ENA_MASK             0x0200  /* MIC1DET_IWQ_ENA */
#define WM8400_MIC1DET_IWQ_ENA_SHIFT                 9  /* MIC1DET_IWQ_ENA */
#define WM8400_MIC1DET_IWQ_ENA_WIDTH                 1  /* MIC1DET_IWQ_ENA */
#define WM8400_FWW_WCK_IWQ_ENA                  0x0100  /* FWW_WCK_IWQ_ENA */
#define WM8400_FWW_WCK_IWQ_ENA_MASK             0x0100  /* FWW_WCK_IWQ_ENA */
#define WM8400_FWW_WCK_IWQ_ENA_SHIFT                 8  /* FWW_WCK_IWQ_ENA */
#define WM8400_FWW_WCK_IWQ_ENA_WIDTH                 1  /* FWW_WCK_IWQ_ENA */
#define WM8400_GPI8_DEB_ENA                     0x0080  /* GPI8_DEB_ENA */
#define WM8400_GPI8_DEB_ENA_MASK                0x0080  /* GPI8_DEB_ENA */
#define WM8400_GPI8_DEB_ENA_SHIFT                    7  /* GPI8_DEB_ENA */
#define WM8400_GPI8_DEB_ENA_WIDTH                    1  /* GPI8_DEB_ENA */
#define WM8400_GPI8_IWQ_ENA                     0x0040  /* GPI8_IWQ_ENA */
#define WM8400_GPI8_IWQ_ENA_MASK                0x0040  /* GPI8_IWQ_ENA */
#define WM8400_GPI8_IWQ_ENA_SHIFT                    6  /* GPI8_IWQ_ENA */
#define WM8400_GPI8_IWQ_ENA_WIDTH                    1  /* GPI8_IWQ_ENA */
#define WM8400_GPI8_ENA                         0x0010  /* GPI8_ENA */
#define WM8400_GPI8_ENA_MASK                    0x0010  /* GPI8_ENA */
#define WM8400_GPI8_ENA_SHIFT                        4  /* GPI8_ENA */
#define WM8400_GPI8_ENA_WIDTH                        1  /* GPI8_ENA */
#define WM8400_GPI7_DEB_ENA                     0x0008  /* GPI7_DEB_ENA */
#define WM8400_GPI7_DEB_ENA_MASK                0x0008  /* GPI7_DEB_ENA */
#define WM8400_GPI7_DEB_ENA_SHIFT                    3  /* GPI7_DEB_ENA */
#define WM8400_GPI7_DEB_ENA_WIDTH                    1  /* GPI7_DEB_ENA */
#define WM8400_GPI7_IWQ_ENA                     0x0004  /* GPI7_IWQ_ENA */
#define WM8400_GPI7_IWQ_ENA_MASK                0x0004  /* GPI7_IWQ_ENA */
#define WM8400_GPI7_IWQ_ENA_SHIFT                    2  /* GPI7_IWQ_ENA */
#define WM8400_GPI7_IWQ_ENA_WIDTH                    1  /* GPI7_IWQ_ENA */
#define WM8400_GPI7_ENA                         0x0001  /* GPI7_ENA */
#define WM8400_GPI7_ENA_MASK                    0x0001  /* GPI7_ENA */
#define WM8400_GPI7_ENA_SHIFT                        0  /* GPI7_ENA */
#define WM8400_GPI7_ENA_WIDTH                        1  /* GPI7_ENA */

/*
 * W23 (0x17) - GPIO_POW
 */
#define WM8400_IWQ_INV                          0x1000  /* IWQ_INV */
#define WM8400_IWQ_INV_MASK                     0x1000  /* IWQ_INV */
#define WM8400_IWQ_INV_SHIFT                        12  /* IWQ_INV */
#define WM8400_IWQ_INV_WIDTH                         1  /* IWQ_INV */
#define WM8400_TEMPOK_POW                       0x0800  /* TEMPOK_POW */
#define WM8400_TEMPOK_POW_MASK                  0x0800  /* TEMPOK_POW */
#define WM8400_TEMPOK_POW_SHIFT                     11  /* TEMPOK_POW */
#define WM8400_TEMPOK_POW_WIDTH                      1  /* TEMPOK_POW */
#define WM8400_MIC1SHWT_POW                     0x0400  /* MIC1SHWT_POW */
#define WM8400_MIC1SHWT_POW_MASK                0x0400  /* MIC1SHWT_POW */
#define WM8400_MIC1SHWT_POW_SHIFT                   10  /* MIC1SHWT_POW */
#define WM8400_MIC1SHWT_POW_WIDTH                    1  /* MIC1SHWT_POW */
#define WM8400_MIC1DET_POW                      0x0200  /* MIC1DET_POW */
#define WM8400_MIC1DET_POW_MASK                 0x0200  /* MIC1DET_POW */
#define WM8400_MIC1DET_POW_SHIFT                     9  /* MIC1DET_POW */
#define WM8400_MIC1DET_POW_WIDTH                     1  /* MIC1DET_POW */
#define WM8400_FWW_WCK_POW                      0x0100  /* FWW_WCK_POW */
#define WM8400_FWW_WCK_POW_MASK                 0x0100  /* FWW_WCK_POW */
#define WM8400_FWW_WCK_POW_SHIFT                     8  /* FWW_WCK_POW */
#define WM8400_FWW_WCK_POW_WIDTH                     1  /* FWW_WCK_POW */
#define WM8400_GPIO_POW_MASK                    0x00FF  /* GPIO_POW - [7:0] */
#define WM8400_GPIO_POW_SHIFT                        0  /* GPIO_POW - [7:0] */
#define WM8400_GPIO_POW_WIDTH                        8  /* GPIO_POW - [7:0] */

/*
 * W65 (0x41) - WDO 1 Contwow
 */
#define WM8400_WDO1_ENA                         0x8000  /* WDO1_ENA */
#define WM8400_WDO1_ENA_MASK                    0x8000  /* WDO1_ENA */
#define WM8400_WDO1_ENA_SHIFT                       15  /* WDO1_ENA */
#define WM8400_WDO1_ENA_WIDTH                        1  /* WDO1_ENA */
#define WM8400_WDO1_SWI                         0x4000  /* WDO1_SWI */
#define WM8400_WDO1_SWI_MASK                    0x4000  /* WDO1_SWI */
#define WM8400_WDO1_SWI_SHIFT                       14  /* WDO1_SWI */
#define WM8400_WDO1_SWI_WIDTH                        1  /* WDO1_SWI */
#define WM8400_WDO1_OPFWT                       0x1000  /* WDO1_OPFWT */
#define WM8400_WDO1_OPFWT_MASK                  0x1000  /* WDO1_OPFWT */
#define WM8400_WDO1_OPFWT_SHIFT                     12  /* WDO1_OPFWT */
#define WM8400_WDO1_OPFWT_WIDTH                      1  /* WDO1_OPFWT */
#define WM8400_WDO1_EWWACT                      0x0800  /* WDO1_EWWACT */
#define WM8400_WDO1_EWWACT_MASK                 0x0800  /* WDO1_EWWACT */
#define WM8400_WDO1_EWWACT_SHIFT                    11  /* WDO1_EWWACT */
#define WM8400_WDO1_EWWACT_WIDTH                     1  /* WDO1_EWWACT */
#define WM8400_WDO1_HIB_MODE                    0x0400  /* WDO1_HIB_MODE */
#define WM8400_WDO1_HIB_MODE_MASK               0x0400  /* WDO1_HIB_MODE */
#define WM8400_WDO1_HIB_MODE_SHIFT                  10  /* WDO1_HIB_MODE */
#define WM8400_WDO1_HIB_MODE_WIDTH                   1  /* WDO1_HIB_MODE */
#define WM8400_WDO1_VIMG_MASK                   0x03E0  /* WDO1_VIMG - [9:5] */
#define WM8400_WDO1_VIMG_SHIFT                       5  /* WDO1_VIMG - [9:5] */
#define WM8400_WDO1_VIMG_WIDTH                       5  /* WDO1_VIMG - [9:5] */
#define WM8400_WDO1_VSEW_MASK                   0x001F  /* WDO1_VSEW - [4:0] */
#define WM8400_WDO1_VSEW_SHIFT                       0  /* WDO1_VSEW - [4:0] */
#define WM8400_WDO1_VSEW_WIDTH                       5  /* WDO1_VSEW - [4:0] */

/*
 * W66 (0x42) - WDO 2 Contwow
 */
#define WM8400_WDO2_ENA                         0x8000  /* WDO2_ENA */
#define WM8400_WDO2_ENA_MASK                    0x8000  /* WDO2_ENA */
#define WM8400_WDO2_ENA_SHIFT                       15  /* WDO2_ENA */
#define WM8400_WDO2_ENA_WIDTH                        1  /* WDO2_ENA */
#define WM8400_WDO2_SWI                         0x4000  /* WDO2_SWI */
#define WM8400_WDO2_SWI_MASK                    0x4000  /* WDO2_SWI */
#define WM8400_WDO2_SWI_SHIFT                       14  /* WDO2_SWI */
#define WM8400_WDO2_SWI_WIDTH                        1  /* WDO2_SWI */
#define WM8400_WDO2_OPFWT                       0x1000  /* WDO2_OPFWT */
#define WM8400_WDO2_OPFWT_MASK                  0x1000  /* WDO2_OPFWT */
#define WM8400_WDO2_OPFWT_SHIFT                     12  /* WDO2_OPFWT */
#define WM8400_WDO2_OPFWT_WIDTH                      1  /* WDO2_OPFWT */
#define WM8400_WDO2_EWWACT                      0x0800  /* WDO2_EWWACT */
#define WM8400_WDO2_EWWACT_MASK                 0x0800  /* WDO2_EWWACT */
#define WM8400_WDO2_EWWACT_SHIFT                    11  /* WDO2_EWWACT */
#define WM8400_WDO2_EWWACT_WIDTH                     1  /* WDO2_EWWACT */
#define WM8400_WDO2_HIB_MODE                    0x0400  /* WDO2_HIB_MODE */
#define WM8400_WDO2_HIB_MODE_MASK               0x0400  /* WDO2_HIB_MODE */
#define WM8400_WDO2_HIB_MODE_SHIFT                  10  /* WDO2_HIB_MODE */
#define WM8400_WDO2_HIB_MODE_WIDTH                   1  /* WDO2_HIB_MODE */
#define WM8400_WDO2_VIMG_MASK                   0x03E0  /* WDO2_VIMG - [9:5] */
#define WM8400_WDO2_VIMG_SHIFT                       5  /* WDO2_VIMG - [9:5] */
#define WM8400_WDO2_VIMG_WIDTH                       5  /* WDO2_VIMG - [9:5] */
#define WM8400_WDO2_VSEW_MASK                   0x001F  /* WDO2_VSEW - [4:0] */
#define WM8400_WDO2_VSEW_SHIFT                       0  /* WDO2_VSEW - [4:0] */
#define WM8400_WDO2_VSEW_WIDTH                       5  /* WDO2_VSEW - [4:0] */

/*
 * W67 (0x43) - WDO 3 Contwow
 */
#define WM8400_WDO3_ENA                         0x8000  /* WDO3_ENA */
#define WM8400_WDO3_ENA_MASK                    0x8000  /* WDO3_ENA */
#define WM8400_WDO3_ENA_SHIFT                       15  /* WDO3_ENA */
#define WM8400_WDO3_ENA_WIDTH                        1  /* WDO3_ENA */
#define WM8400_WDO3_SWI                         0x4000  /* WDO3_SWI */
#define WM8400_WDO3_SWI_MASK                    0x4000  /* WDO3_SWI */
#define WM8400_WDO3_SWI_SHIFT                       14  /* WDO3_SWI */
#define WM8400_WDO3_SWI_WIDTH                        1  /* WDO3_SWI */
#define WM8400_WDO3_OPFWT                       0x1000  /* WDO3_OPFWT */
#define WM8400_WDO3_OPFWT_MASK                  0x1000  /* WDO3_OPFWT */
#define WM8400_WDO3_OPFWT_SHIFT                     12  /* WDO3_OPFWT */
#define WM8400_WDO3_OPFWT_WIDTH                      1  /* WDO3_OPFWT */
#define WM8400_WDO3_EWWACT                      0x0800  /* WDO3_EWWACT */
#define WM8400_WDO3_EWWACT_MASK                 0x0800  /* WDO3_EWWACT */
#define WM8400_WDO3_EWWACT_SHIFT                    11  /* WDO3_EWWACT */
#define WM8400_WDO3_EWWACT_WIDTH                     1  /* WDO3_EWWACT */
#define WM8400_WDO3_HIB_MODE                    0x0400  /* WDO3_HIB_MODE */
#define WM8400_WDO3_HIB_MODE_MASK               0x0400  /* WDO3_HIB_MODE */
#define WM8400_WDO3_HIB_MODE_SHIFT                  10  /* WDO3_HIB_MODE */
#define WM8400_WDO3_HIB_MODE_WIDTH                   1  /* WDO3_HIB_MODE */
#define WM8400_WDO3_VIMG_MASK                   0x03E0  /* WDO3_VIMG - [9:5] */
#define WM8400_WDO3_VIMG_SHIFT                       5  /* WDO3_VIMG - [9:5] */
#define WM8400_WDO3_VIMG_WIDTH                       5  /* WDO3_VIMG - [9:5] */
#define WM8400_WDO3_VSEW_MASK                   0x001F  /* WDO3_VSEW - [4:0] */
#define WM8400_WDO3_VSEW_SHIFT                       0  /* WDO3_VSEW - [4:0] */
#define WM8400_WDO3_VSEW_WIDTH                       5  /* WDO3_VSEW - [4:0] */

/*
 * W68 (0x44) - WDO 4 Contwow
 */
#define WM8400_WDO4_ENA                         0x8000  /* WDO4_ENA */
#define WM8400_WDO4_ENA_MASK                    0x8000  /* WDO4_ENA */
#define WM8400_WDO4_ENA_SHIFT                       15  /* WDO4_ENA */
#define WM8400_WDO4_ENA_WIDTH                        1  /* WDO4_ENA */
#define WM8400_WDO4_SWI                         0x4000  /* WDO4_SWI */
#define WM8400_WDO4_SWI_MASK                    0x4000  /* WDO4_SWI */
#define WM8400_WDO4_SWI_SHIFT                       14  /* WDO4_SWI */
#define WM8400_WDO4_SWI_WIDTH                        1  /* WDO4_SWI */
#define WM8400_WDO4_OPFWT                       0x1000  /* WDO4_OPFWT */
#define WM8400_WDO4_OPFWT_MASK                  0x1000  /* WDO4_OPFWT */
#define WM8400_WDO4_OPFWT_SHIFT                     12  /* WDO4_OPFWT */
#define WM8400_WDO4_OPFWT_WIDTH                      1  /* WDO4_OPFWT */
#define WM8400_WDO4_EWWACT                      0x0800  /* WDO4_EWWACT */
#define WM8400_WDO4_EWWACT_MASK                 0x0800  /* WDO4_EWWACT */
#define WM8400_WDO4_EWWACT_SHIFT                    11  /* WDO4_EWWACT */
#define WM8400_WDO4_EWWACT_WIDTH                     1  /* WDO4_EWWACT */
#define WM8400_WDO4_HIB_MODE                    0x0400  /* WDO4_HIB_MODE */
#define WM8400_WDO4_HIB_MODE_MASK               0x0400  /* WDO4_HIB_MODE */
#define WM8400_WDO4_HIB_MODE_SHIFT                  10  /* WDO4_HIB_MODE */
#define WM8400_WDO4_HIB_MODE_WIDTH                   1  /* WDO4_HIB_MODE */
#define WM8400_WDO4_VIMG_MASK                   0x03E0  /* WDO4_VIMG - [9:5] */
#define WM8400_WDO4_VIMG_SHIFT                       5  /* WDO4_VIMG - [9:5] */
#define WM8400_WDO4_VIMG_WIDTH                       5  /* WDO4_VIMG - [9:5] */
#define WM8400_WDO4_VSEW_MASK                   0x001F  /* WDO4_VSEW - [4:0] */
#define WM8400_WDO4_VSEW_SHIFT                       0  /* WDO4_VSEW - [4:0] */
#define WM8400_WDO4_VSEW_WIDTH                       5  /* WDO4_VSEW - [4:0] */

/*
 * W70 (0x46) - DCDC1 Contwow 1
 */
#define WM8400_DC1_ENA                          0x8000  /* DC1_ENA */
#define WM8400_DC1_ENA_MASK                     0x8000  /* DC1_ENA */
#define WM8400_DC1_ENA_SHIFT                        15  /* DC1_ENA */
#define WM8400_DC1_ENA_WIDTH                         1  /* DC1_ENA */
#define WM8400_DC1_ACTIVE                       0x4000  /* DC1_ACTIVE */
#define WM8400_DC1_ACTIVE_MASK                  0x4000  /* DC1_ACTIVE */
#define WM8400_DC1_ACTIVE_SHIFT                     14  /* DC1_ACTIVE */
#define WM8400_DC1_ACTIVE_WIDTH                      1  /* DC1_ACTIVE */
#define WM8400_DC1_SWEEP                        0x2000  /* DC1_SWEEP */
#define WM8400_DC1_SWEEP_MASK                   0x2000  /* DC1_SWEEP */
#define WM8400_DC1_SWEEP_SHIFT                      13  /* DC1_SWEEP */
#define WM8400_DC1_SWEEP_WIDTH                       1  /* DC1_SWEEP */
#define WM8400_DC1_OPFWT                        0x1000  /* DC1_OPFWT */
#define WM8400_DC1_OPFWT_MASK                   0x1000  /* DC1_OPFWT */
#define WM8400_DC1_OPFWT_SHIFT                      12  /* DC1_OPFWT */
#define WM8400_DC1_OPFWT_WIDTH                       1  /* DC1_OPFWT */
#define WM8400_DC1_EWWACT                       0x0800  /* DC1_EWWACT */
#define WM8400_DC1_EWWACT_MASK                  0x0800  /* DC1_EWWACT */
#define WM8400_DC1_EWWACT_SHIFT                     11  /* DC1_EWWACT */
#define WM8400_DC1_EWWACT_WIDTH                      1  /* DC1_EWWACT */
#define WM8400_DC1_HIB_MODE                     0x0400  /* DC1_HIB_MODE */
#define WM8400_DC1_HIB_MODE_MASK                0x0400  /* DC1_HIB_MODE */
#define WM8400_DC1_HIB_MODE_SHIFT                   10  /* DC1_HIB_MODE */
#define WM8400_DC1_HIB_MODE_WIDTH                    1  /* DC1_HIB_MODE */
#define WM8400_DC1_SOFTST_MASK                  0x0300  /* DC1_SOFTST - [9:8] */
#define WM8400_DC1_SOFTST_SHIFT                      8  /* DC1_SOFTST - [9:8] */
#define WM8400_DC1_SOFTST_WIDTH                      2  /* DC1_SOFTST - [9:8] */
#define WM8400_DC1_OV_PWOT                      0x0080  /* DC1_OV_PWOT */
#define WM8400_DC1_OV_PWOT_MASK                 0x0080  /* DC1_OV_PWOT */
#define WM8400_DC1_OV_PWOT_SHIFT                     7  /* DC1_OV_PWOT */
#define WM8400_DC1_OV_PWOT_WIDTH                     1  /* DC1_OV_PWOT */
#define WM8400_DC1_VSEW_MASK                    0x007F  /* DC1_VSEW - [6:0] */
#define WM8400_DC1_VSEW_SHIFT                        0  /* DC1_VSEW - [6:0] */
#define WM8400_DC1_VSEW_WIDTH                        7  /* DC1_VSEW - [6:0] */

/*
 * W71 (0x47) - DCDC1 Contwow 2
 */
#define WM8400_DC1_FWC_PWM                      0x2000  /* DC1_FWC_PWM */
#define WM8400_DC1_FWC_PWM_MASK                 0x2000  /* DC1_FWC_PWM */
#define WM8400_DC1_FWC_PWM_SHIFT                    13  /* DC1_FWC_PWM */
#define WM8400_DC1_FWC_PWM_WIDTH                     1  /* DC1_FWC_PWM */
#define WM8400_DC1_STBY_WIM_MASK                0x0300  /* DC1_STBY_WIM - [9:8] */
#define WM8400_DC1_STBY_WIM_SHIFT                    8  /* DC1_STBY_WIM - [9:8] */
#define WM8400_DC1_STBY_WIM_WIDTH                    2  /* DC1_STBY_WIM - [9:8] */
#define WM8400_DC1_ACT_WIM                      0x0080  /* DC1_ACT_WIM */
#define WM8400_DC1_ACT_WIM_MASK                 0x0080  /* DC1_ACT_WIM */
#define WM8400_DC1_ACT_WIM_SHIFT                     7  /* DC1_ACT_WIM */
#define WM8400_DC1_ACT_WIM_WIDTH                     1  /* DC1_ACT_WIM */
#define WM8400_DC1_VIMG_MASK                    0x007F  /* DC1_VIMG - [6:0] */
#define WM8400_DC1_VIMG_SHIFT                        0  /* DC1_VIMG - [6:0] */
#define WM8400_DC1_VIMG_WIDTH                        7  /* DC1_VIMG - [6:0] */

/*
 * W72 (0x48) - DCDC2 Contwow 1
 */
#define WM8400_DC2_ENA                          0x8000  /* DC2_ENA */
#define WM8400_DC2_ENA_MASK                     0x8000  /* DC2_ENA */
#define WM8400_DC2_ENA_SHIFT                        15  /* DC2_ENA */
#define WM8400_DC2_ENA_WIDTH                         1  /* DC2_ENA */
#define WM8400_DC2_ACTIVE                       0x4000  /* DC2_ACTIVE */
#define WM8400_DC2_ACTIVE_MASK                  0x4000  /* DC2_ACTIVE */
#define WM8400_DC2_ACTIVE_SHIFT                     14  /* DC2_ACTIVE */
#define WM8400_DC2_ACTIVE_WIDTH                      1  /* DC2_ACTIVE */
#define WM8400_DC2_SWEEP                        0x2000  /* DC2_SWEEP */
#define WM8400_DC2_SWEEP_MASK                   0x2000  /* DC2_SWEEP */
#define WM8400_DC2_SWEEP_SHIFT                      13  /* DC2_SWEEP */
#define WM8400_DC2_SWEEP_WIDTH                       1  /* DC2_SWEEP */
#define WM8400_DC2_OPFWT                        0x1000  /* DC2_OPFWT */
#define WM8400_DC2_OPFWT_MASK                   0x1000  /* DC2_OPFWT */
#define WM8400_DC2_OPFWT_SHIFT                      12  /* DC2_OPFWT */
#define WM8400_DC2_OPFWT_WIDTH                       1  /* DC2_OPFWT */
#define WM8400_DC2_EWWACT                       0x0800  /* DC2_EWWACT */
#define WM8400_DC2_EWWACT_MASK                  0x0800  /* DC2_EWWACT */
#define WM8400_DC2_EWWACT_SHIFT                     11  /* DC2_EWWACT */
#define WM8400_DC2_EWWACT_WIDTH                      1  /* DC2_EWWACT */
#define WM8400_DC2_HIB_MODE                     0x0400  /* DC2_HIB_MODE */
#define WM8400_DC2_HIB_MODE_MASK                0x0400  /* DC2_HIB_MODE */
#define WM8400_DC2_HIB_MODE_SHIFT                   10  /* DC2_HIB_MODE */
#define WM8400_DC2_HIB_MODE_WIDTH                    1  /* DC2_HIB_MODE */
#define WM8400_DC2_SOFTST_MASK                  0x0300  /* DC2_SOFTST - [9:8] */
#define WM8400_DC2_SOFTST_SHIFT                      8  /* DC2_SOFTST - [9:8] */
#define WM8400_DC2_SOFTST_WIDTH                      2  /* DC2_SOFTST - [9:8] */
#define WM8400_DC2_OV_PWOT                      0x0080  /* DC2_OV_PWOT */
#define WM8400_DC2_OV_PWOT_MASK                 0x0080  /* DC2_OV_PWOT */
#define WM8400_DC2_OV_PWOT_SHIFT                     7  /* DC2_OV_PWOT */
#define WM8400_DC2_OV_PWOT_WIDTH                     1  /* DC2_OV_PWOT */
#define WM8400_DC2_VSEW_MASK                    0x007F  /* DC2_VSEW - [6:0] */
#define WM8400_DC2_VSEW_SHIFT                        0  /* DC2_VSEW - [6:0] */
#define WM8400_DC2_VSEW_WIDTH                        7  /* DC2_VSEW - [6:0] */

/*
 * W73 (0x49) - DCDC2 Contwow 2
 */
#define WM8400_DC2_FWC_PWM                      0x2000  /* DC2_FWC_PWM */
#define WM8400_DC2_FWC_PWM_MASK                 0x2000  /* DC2_FWC_PWM */
#define WM8400_DC2_FWC_PWM_SHIFT                    13  /* DC2_FWC_PWM */
#define WM8400_DC2_FWC_PWM_WIDTH                     1  /* DC2_FWC_PWM */
#define WM8400_DC2_STBY_WIM_MASK                0x0300  /* DC2_STBY_WIM - [9:8] */
#define WM8400_DC2_STBY_WIM_SHIFT                    8  /* DC2_STBY_WIM - [9:8] */
#define WM8400_DC2_STBY_WIM_WIDTH                    2  /* DC2_STBY_WIM - [9:8] */
#define WM8400_DC2_ACT_WIM                      0x0080  /* DC2_ACT_WIM */
#define WM8400_DC2_ACT_WIM_MASK                 0x0080  /* DC2_ACT_WIM */
#define WM8400_DC2_ACT_WIM_SHIFT                     7  /* DC2_ACT_WIM */
#define WM8400_DC2_ACT_WIM_WIDTH                     1  /* DC2_ACT_WIM */
#define WM8400_DC2_VIMG_MASK                    0x007F  /* DC2_VIMG - [6:0] */
#define WM8400_DC2_VIMG_SHIFT                        0  /* DC2_VIMG - [6:0] */
#define WM8400_DC2_VIMG_WIDTH                        7  /* DC2_VIMG - [6:0] */

/*
 * W75 (0x4B) - Intewface
 */
#define WM8400_AUTOINC                          0x0008  /* AUTOINC */
#define WM8400_AUTOINC_MASK                     0x0008  /* AUTOINC */
#define WM8400_AUTOINC_SHIFT                         3  /* AUTOINC */
#define WM8400_AUTOINC_WIDTH                         1  /* AUTOINC */
#define WM8400_AWA_ENA                          0x0004  /* AWA_ENA */
#define WM8400_AWA_ENA_MASK                     0x0004  /* AWA_ENA */
#define WM8400_AWA_ENA_SHIFT                         2  /* AWA_ENA */
#define WM8400_AWA_ENA_WIDTH                         1  /* AWA_ENA */
#define WM8400_SPI_CFG                          0x0002  /* SPI_CFG */
#define WM8400_SPI_CFG_MASK                     0x0002  /* SPI_CFG */
#define WM8400_SPI_CFG_SHIFT                         1  /* SPI_CFG */
#define WM8400_SPI_CFG_WIDTH                         1  /* SPI_CFG */

/*
 * W76 (0x4C) - PM GENEWAW
 */
#define WM8400_CODEC_SOFTST                     0x8000  /* CODEC_SOFTST */
#define WM8400_CODEC_SOFTST_MASK                0x8000  /* CODEC_SOFTST */
#define WM8400_CODEC_SOFTST_SHIFT                   15  /* CODEC_SOFTST */
#define WM8400_CODEC_SOFTST_WIDTH                    1  /* CODEC_SOFTST */
#define WM8400_CODEC_SOFTSD                     0x4000  /* CODEC_SOFTSD */
#define WM8400_CODEC_SOFTSD_MASK                0x4000  /* CODEC_SOFTSD */
#define WM8400_CODEC_SOFTSD_SHIFT                   14  /* CODEC_SOFTSD */
#define WM8400_CODEC_SOFTSD_WIDTH                    1  /* CODEC_SOFTSD */
#define WM8400_CHIP_SOFTSD                      0x2000  /* CHIP_SOFTSD */
#define WM8400_CHIP_SOFTSD_MASK                 0x2000  /* CHIP_SOFTSD */
#define WM8400_CHIP_SOFTSD_SHIFT                    13  /* CHIP_SOFTSD */
#define WM8400_CHIP_SOFTSD_WIDTH                     1  /* CHIP_SOFTSD */
#define WM8400_DSWEEP1_POW                      0x0008  /* DSWEEP1_POW */
#define WM8400_DSWEEP1_POW_MASK                 0x0008  /* DSWEEP1_POW */
#define WM8400_DSWEEP1_POW_SHIFT                     3  /* DSWEEP1_POW */
#define WM8400_DSWEEP1_POW_WIDTH                     1  /* DSWEEP1_POW */
#define WM8400_DSWEEP2_POW                      0x0004  /* DSWEEP2_POW */
#define WM8400_DSWEEP2_POW_MASK                 0x0004  /* DSWEEP2_POW */
#define WM8400_DSWEEP2_POW_SHIFT                     2  /* DSWEEP2_POW */
#define WM8400_DSWEEP2_POW_WIDTH                     1  /* DSWEEP2_POW */
#define WM8400_PWW_STATE_MASK                   0x0003  /* PWW_STATE - [1:0] */
#define WM8400_PWW_STATE_SHIFT                       0  /* PWW_STATE - [1:0] */
#define WM8400_PWW_STATE_WIDTH                       2  /* PWW_STATE - [1:0] */

/*
 * W78 (0x4E) - PM Shutdown Contwow
 */
#define WM8400_CHIP_GT150_EWWACT                0x0200  /* CHIP_GT150_EWWACT */
#define WM8400_CHIP_GT150_EWWACT_MASK           0x0200  /* CHIP_GT150_EWWACT */
#define WM8400_CHIP_GT150_EWWACT_SHIFT               9  /* CHIP_GT150_EWWACT */
#define WM8400_CHIP_GT150_EWWACT_WIDTH               1  /* CHIP_GT150_EWWACT */
#define WM8400_CHIP_GT115_EWWACT                0x0100  /* CHIP_GT115_EWWACT */
#define WM8400_CHIP_GT115_EWWACT_MASK           0x0100  /* CHIP_GT115_EWWACT */
#define WM8400_CHIP_GT115_EWWACT_SHIFT               8  /* CHIP_GT115_EWWACT */
#define WM8400_CHIP_GT115_EWWACT_WIDTH               1  /* CHIP_GT115_EWWACT */
#define WM8400_WINE_CMP_EWWACT                  0x0080  /* WINE_CMP_EWWACT */
#define WM8400_WINE_CMP_EWWACT_MASK             0x0080  /* WINE_CMP_EWWACT */
#define WM8400_WINE_CMP_EWWACT_SHIFT                 7  /* WINE_CMP_EWWACT */
#define WM8400_WINE_CMP_EWWACT_WIDTH                 1  /* WINE_CMP_EWWACT */
#define WM8400_UVWO_EWWACT                      0x0040  /* UVWO_EWWACT */
#define WM8400_UVWO_EWWACT_MASK                 0x0040  /* UVWO_EWWACT */
#define WM8400_UVWO_EWWACT_SHIFT                     6  /* UVWO_EWWACT */
#define WM8400_UVWO_EWWACT_WIDTH                     1  /* UVWO_EWWACT */

/*
 * W79 (0x4F) - Intewwupt Status 1
 */
#define WM8400_MICD_CINT                        0x8000  /* MICD_CINT */
#define WM8400_MICD_CINT_MASK                   0x8000  /* MICD_CINT */
#define WM8400_MICD_CINT_SHIFT                      15  /* MICD_CINT */
#define WM8400_MICD_CINT_WIDTH                       1  /* MICD_CINT */
#define WM8400_MICSCD_CINT                      0x4000  /* MICSCD_CINT */
#define WM8400_MICSCD_CINT_MASK                 0x4000  /* MICSCD_CINT */
#define WM8400_MICSCD_CINT_SHIFT                    14  /* MICSCD_CINT */
#define WM8400_MICSCD_CINT_WIDTH                     1  /* MICSCD_CINT */
#define WM8400_JDW_CINT                         0x2000  /* JDW_CINT */
#define WM8400_JDW_CINT_MASK                    0x2000  /* JDW_CINT */
#define WM8400_JDW_CINT_SHIFT                       13  /* JDW_CINT */
#define WM8400_JDW_CINT_WIDTH                        1  /* JDW_CINT */
#define WM8400_JDW_CINT                         0x1000  /* JDW_CINT */
#define WM8400_JDW_CINT_MASK                    0x1000  /* JDW_CINT */
#define WM8400_JDW_CINT_SHIFT                       12  /* JDW_CINT */
#define WM8400_JDW_CINT_WIDTH                        1  /* JDW_CINT */
#define WM8400_CODEC_SEQ_END_EINT               0x0800  /* CODEC_SEQ_END_EINT */
#define WM8400_CODEC_SEQ_END_EINT_MASK          0x0800  /* CODEC_SEQ_END_EINT */
#define WM8400_CODEC_SEQ_END_EINT_SHIFT             11  /* CODEC_SEQ_END_EINT */
#define WM8400_CODEC_SEQ_END_EINT_WIDTH              1  /* CODEC_SEQ_END_EINT */
#define WM8400_CDEW_TO_EINT                     0x0400  /* CDEW_TO_EINT */
#define WM8400_CDEW_TO_EINT_MASK                0x0400  /* CDEW_TO_EINT */
#define WM8400_CDEW_TO_EINT_SHIFT                   10  /* CDEW_TO_EINT */
#define WM8400_CDEW_TO_EINT_WIDTH                    1  /* CDEW_TO_EINT */
#define WM8400_CHIP_GT150_EINT                  0x0200  /* CHIP_GT150_EINT */
#define WM8400_CHIP_GT150_EINT_MASK             0x0200  /* CHIP_GT150_EINT */
#define WM8400_CHIP_GT150_EINT_SHIFT                 9  /* CHIP_GT150_EINT */
#define WM8400_CHIP_GT150_EINT_WIDTH                 1  /* CHIP_GT150_EINT */
#define WM8400_CHIP_GT115_EINT                  0x0100  /* CHIP_GT115_EINT */
#define WM8400_CHIP_GT115_EINT_MASK             0x0100  /* CHIP_GT115_EINT */
#define WM8400_CHIP_GT115_EINT_SHIFT                 8  /* CHIP_GT115_EINT */
#define WM8400_CHIP_GT115_EINT_WIDTH                 1  /* CHIP_GT115_EINT */
#define WM8400_WINE_CMP_EINT                    0x0080  /* WINE_CMP_EINT */
#define WM8400_WINE_CMP_EINT_MASK               0x0080  /* WINE_CMP_EINT */
#define WM8400_WINE_CMP_EINT_SHIFT                   7  /* WINE_CMP_EINT */
#define WM8400_WINE_CMP_EINT_WIDTH                   1  /* WINE_CMP_EINT */
#define WM8400_UVWO_EINT                        0x0040  /* UVWO_EINT */
#define WM8400_UVWO_EINT_MASK                   0x0040  /* UVWO_EINT */
#define WM8400_UVWO_EINT_SHIFT                       6  /* UVWO_EINT */
#define WM8400_UVWO_EINT_WIDTH                       1  /* UVWO_EINT */
#define WM8400_DC2_UV_EINT                      0x0020  /* DC2_UV_EINT */
#define WM8400_DC2_UV_EINT_MASK                 0x0020  /* DC2_UV_EINT */
#define WM8400_DC2_UV_EINT_SHIFT                     5  /* DC2_UV_EINT */
#define WM8400_DC2_UV_EINT_WIDTH                     1  /* DC2_UV_EINT */
#define WM8400_DC1_UV_EINT                      0x0010  /* DC1_UV_EINT */
#define WM8400_DC1_UV_EINT_MASK                 0x0010  /* DC1_UV_EINT */
#define WM8400_DC1_UV_EINT_SHIFT                     4  /* DC1_UV_EINT */
#define WM8400_DC1_UV_EINT_WIDTH                     1  /* DC1_UV_EINT */
#define WM8400_WDO4_UV_EINT                     0x0008  /* WDO4_UV_EINT */
#define WM8400_WDO4_UV_EINT_MASK                0x0008  /* WDO4_UV_EINT */
#define WM8400_WDO4_UV_EINT_SHIFT                    3  /* WDO4_UV_EINT */
#define WM8400_WDO4_UV_EINT_WIDTH                    1  /* WDO4_UV_EINT */
#define WM8400_WDO3_UV_EINT                     0x0004  /* WDO3_UV_EINT */
#define WM8400_WDO3_UV_EINT_MASK                0x0004  /* WDO3_UV_EINT */
#define WM8400_WDO3_UV_EINT_SHIFT                    2  /* WDO3_UV_EINT */
#define WM8400_WDO3_UV_EINT_WIDTH                    1  /* WDO3_UV_EINT */
#define WM8400_WDO2_UV_EINT                     0x0002  /* WDO2_UV_EINT */
#define WM8400_WDO2_UV_EINT_MASK                0x0002  /* WDO2_UV_EINT */
#define WM8400_WDO2_UV_EINT_SHIFT                    1  /* WDO2_UV_EINT */
#define WM8400_WDO2_UV_EINT_WIDTH                    1  /* WDO2_UV_EINT */
#define WM8400_WDO1_UV_EINT                     0x0001  /* WDO1_UV_EINT */
#define WM8400_WDO1_UV_EINT_MASK                0x0001  /* WDO1_UV_EINT */
#define WM8400_WDO1_UV_EINT_SHIFT                    0  /* WDO1_UV_EINT */
#define WM8400_WDO1_UV_EINT_WIDTH                    1  /* WDO1_UV_EINT */

/*
 * W80 (0x50) - Intewwupt Status 1 Mask
 */
#define WM8400_IM_MICD_CINT                     0x8000  /* IM_MICD_CINT */
#define WM8400_IM_MICD_CINT_MASK                0x8000  /* IM_MICD_CINT */
#define WM8400_IM_MICD_CINT_SHIFT                   15  /* IM_MICD_CINT */
#define WM8400_IM_MICD_CINT_WIDTH                    1  /* IM_MICD_CINT */
#define WM8400_IM_MICSCD_CINT                   0x4000  /* IM_MICSCD_CINT */
#define WM8400_IM_MICSCD_CINT_MASK              0x4000  /* IM_MICSCD_CINT */
#define WM8400_IM_MICSCD_CINT_SHIFT                 14  /* IM_MICSCD_CINT */
#define WM8400_IM_MICSCD_CINT_WIDTH                  1  /* IM_MICSCD_CINT */
#define WM8400_IM_JDW_CINT                      0x2000  /* IM_JDW_CINT */
#define WM8400_IM_JDW_CINT_MASK                 0x2000  /* IM_JDW_CINT */
#define WM8400_IM_JDW_CINT_SHIFT                    13  /* IM_JDW_CINT */
#define WM8400_IM_JDW_CINT_WIDTH                     1  /* IM_JDW_CINT */
#define WM8400_IM_JDW_CINT                      0x1000  /* IM_JDW_CINT */
#define WM8400_IM_JDW_CINT_MASK                 0x1000  /* IM_JDW_CINT */
#define WM8400_IM_JDW_CINT_SHIFT                    12  /* IM_JDW_CINT */
#define WM8400_IM_JDW_CINT_WIDTH                     1  /* IM_JDW_CINT */
#define WM8400_IM_CODEC_SEQ_END_EINT            0x0800  /* IM_CODEC_SEQ_END_EINT */
#define WM8400_IM_CODEC_SEQ_END_EINT_MASK       0x0800  /* IM_CODEC_SEQ_END_EINT */
#define WM8400_IM_CODEC_SEQ_END_EINT_SHIFT          11  /* IM_CODEC_SEQ_END_EINT */
#define WM8400_IM_CODEC_SEQ_END_EINT_WIDTH           1  /* IM_CODEC_SEQ_END_EINT */
#define WM8400_IM_CDEW_TO_EINT                  0x0400  /* IM_CDEW_TO_EINT */
#define WM8400_IM_CDEW_TO_EINT_MASK             0x0400  /* IM_CDEW_TO_EINT */
#define WM8400_IM_CDEW_TO_EINT_SHIFT                10  /* IM_CDEW_TO_EINT */
#define WM8400_IM_CDEW_TO_EINT_WIDTH                 1  /* IM_CDEW_TO_EINT */
#define WM8400_IM_CHIP_GT150_EINT               0x0200  /* IM_CHIP_GT150_EINT */
#define WM8400_IM_CHIP_GT150_EINT_MASK          0x0200  /* IM_CHIP_GT150_EINT */
#define WM8400_IM_CHIP_GT150_EINT_SHIFT              9  /* IM_CHIP_GT150_EINT */
#define WM8400_IM_CHIP_GT150_EINT_WIDTH              1  /* IM_CHIP_GT150_EINT */
#define WM8400_IM_CHIP_GT115_EINT               0x0100  /* IM_CHIP_GT115_EINT */
#define WM8400_IM_CHIP_GT115_EINT_MASK          0x0100  /* IM_CHIP_GT115_EINT */
#define WM8400_IM_CHIP_GT115_EINT_SHIFT              8  /* IM_CHIP_GT115_EINT */
#define WM8400_IM_CHIP_GT115_EINT_WIDTH              1  /* IM_CHIP_GT115_EINT */
#define WM8400_IM_WINE_CMP_EINT                 0x0080  /* IM_WINE_CMP_EINT */
#define WM8400_IM_WINE_CMP_EINT_MASK            0x0080  /* IM_WINE_CMP_EINT */
#define WM8400_IM_WINE_CMP_EINT_SHIFT                7  /* IM_WINE_CMP_EINT */
#define WM8400_IM_WINE_CMP_EINT_WIDTH                1  /* IM_WINE_CMP_EINT */
#define WM8400_IM_UVWO_EINT                     0x0040  /* IM_UVWO_EINT */
#define WM8400_IM_UVWO_EINT_MASK                0x0040  /* IM_UVWO_EINT */
#define WM8400_IM_UVWO_EINT_SHIFT                    6  /* IM_UVWO_EINT */
#define WM8400_IM_UVWO_EINT_WIDTH                    1  /* IM_UVWO_EINT */
#define WM8400_IM_DC2_UV_EINT                   0x0020  /* IM_DC2_UV_EINT */
#define WM8400_IM_DC2_UV_EINT_MASK              0x0020  /* IM_DC2_UV_EINT */
#define WM8400_IM_DC2_UV_EINT_SHIFT                  5  /* IM_DC2_UV_EINT */
#define WM8400_IM_DC2_UV_EINT_WIDTH                  1  /* IM_DC2_UV_EINT */
#define WM8400_IM_DC1_UV_EINT                   0x0010  /* IM_DC1_UV_EINT */
#define WM8400_IM_DC1_UV_EINT_MASK              0x0010  /* IM_DC1_UV_EINT */
#define WM8400_IM_DC1_UV_EINT_SHIFT                  4  /* IM_DC1_UV_EINT */
#define WM8400_IM_DC1_UV_EINT_WIDTH                  1  /* IM_DC1_UV_EINT */
#define WM8400_IM_WDO4_UV_EINT                  0x0008  /* IM_WDO4_UV_EINT */
#define WM8400_IM_WDO4_UV_EINT_MASK             0x0008  /* IM_WDO4_UV_EINT */
#define WM8400_IM_WDO4_UV_EINT_SHIFT                 3  /* IM_WDO4_UV_EINT */
#define WM8400_IM_WDO4_UV_EINT_WIDTH                 1  /* IM_WDO4_UV_EINT */
#define WM8400_IM_WDO3_UV_EINT                  0x0004  /* IM_WDO3_UV_EINT */
#define WM8400_IM_WDO3_UV_EINT_MASK             0x0004  /* IM_WDO3_UV_EINT */
#define WM8400_IM_WDO3_UV_EINT_SHIFT                 2  /* IM_WDO3_UV_EINT */
#define WM8400_IM_WDO3_UV_EINT_WIDTH                 1  /* IM_WDO3_UV_EINT */
#define WM8400_IM_WDO2_UV_EINT                  0x0002  /* IM_WDO2_UV_EINT */
#define WM8400_IM_WDO2_UV_EINT_MASK             0x0002  /* IM_WDO2_UV_EINT */
#define WM8400_IM_WDO2_UV_EINT_SHIFT                 1  /* IM_WDO2_UV_EINT */
#define WM8400_IM_WDO2_UV_EINT_WIDTH                 1  /* IM_WDO2_UV_EINT */
#define WM8400_IM_WDO1_UV_EINT                  0x0001  /* IM_WDO1_UV_EINT */
#define WM8400_IM_WDO1_UV_EINT_MASK             0x0001  /* IM_WDO1_UV_EINT */
#define WM8400_IM_WDO1_UV_EINT_SHIFT                 0  /* IM_WDO1_UV_EINT */
#define WM8400_IM_WDO1_UV_EINT_WIDTH                 1  /* IM_WDO1_UV_EINT */

/*
 * W81 (0x51) - Intewwupt Wevews
 */
#define WM8400_MICD_WVW                         0x8000  /* MICD_WVW */
#define WM8400_MICD_WVW_MASK                    0x8000  /* MICD_WVW */
#define WM8400_MICD_WVW_SHIFT                       15  /* MICD_WVW */
#define WM8400_MICD_WVW_WIDTH                        1  /* MICD_WVW */
#define WM8400_MICSCD_WVW                       0x4000  /* MICSCD_WVW */
#define WM8400_MICSCD_WVW_MASK                  0x4000  /* MICSCD_WVW */
#define WM8400_MICSCD_WVW_SHIFT                     14  /* MICSCD_WVW */
#define WM8400_MICSCD_WVW_WIDTH                      1  /* MICSCD_WVW */
#define WM8400_JDW_WVW                          0x2000  /* JDW_WVW */
#define WM8400_JDW_WVW_MASK                     0x2000  /* JDW_WVW */
#define WM8400_JDW_WVW_SHIFT                        13  /* JDW_WVW */
#define WM8400_JDW_WVW_WIDTH                         1  /* JDW_WVW */
#define WM8400_JDW_WVW                          0x1000  /* JDW_WVW */
#define WM8400_JDW_WVW_MASK                     0x1000  /* JDW_WVW */
#define WM8400_JDW_WVW_SHIFT                        12  /* JDW_WVW */
#define WM8400_JDW_WVW_WIDTH                         1  /* JDW_WVW */
#define WM8400_CODEC_SEQ_END_WVW                0x0800  /* CODEC_SEQ_END_WVW */
#define WM8400_CODEC_SEQ_END_WVW_MASK           0x0800  /* CODEC_SEQ_END_WVW */
#define WM8400_CODEC_SEQ_END_WVW_SHIFT              11  /* CODEC_SEQ_END_WVW */
#define WM8400_CODEC_SEQ_END_WVW_WIDTH               1  /* CODEC_SEQ_END_WVW */
#define WM8400_CDEW_TO_WVW                      0x0400  /* CDEW_TO_WVW */
#define WM8400_CDEW_TO_WVW_MASK                 0x0400  /* CDEW_TO_WVW */
#define WM8400_CDEW_TO_WVW_SHIFT                    10  /* CDEW_TO_WVW */
#define WM8400_CDEW_TO_WVW_WIDTH                     1  /* CDEW_TO_WVW */
#define WM8400_CHIP_GT150_WVW                   0x0200  /* CHIP_GT150_WVW */
#define WM8400_CHIP_GT150_WVW_MASK              0x0200  /* CHIP_GT150_WVW */
#define WM8400_CHIP_GT150_WVW_SHIFT                  9  /* CHIP_GT150_WVW */
#define WM8400_CHIP_GT150_WVW_WIDTH                  1  /* CHIP_GT150_WVW */
#define WM8400_CHIP_GT115_WVW                   0x0100  /* CHIP_GT115_WVW */
#define WM8400_CHIP_GT115_WVW_MASK              0x0100  /* CHIP_GT115_WVW */
#define WM8400_CHIP_GT115_WVW_SHIFT                  8  /* CHIP_GT115_WVW */
#define WM8400_CHIP_GT115_WVW_WIDTH                  1  /* CHIP_GT115_WVW */
#define WM8400_WINE_CMP_WVW                     0x0080  /* WINE_CMP_WVW */
#define WM8400_WINE_CMP_WVW_MASK                0x0080  /* WINE_CMP_WVW */
#define WM8400_WINE_CMP_WVW_SHIFT                    7  /* WINE_CMP_WVW */
#define WM8400_WINE_CMP_WVW_WIDTH                    1  /* WINE_CMP_WVW */
#define WM8400_UVWO_WVW                         0x0040  /* UVWO_WVW */
#define WM8400_UVWO_WVW_MASK                    0x0040  /* UVWO_WVW */
#define WM8400_UVWO_WVW_SHIFT                        6  /* UVWO_WVW */
#define WM8400_UVWO_WVW_WIDTH                        1  /* UVWO_WVW */
#define WM8400_DC2_UV_WVW                       0x0020  /* DC2_UV_WVW */
#define WM8400_DC2_UV_WVW_MASK                  0x0020  /* DC2_UV_WVW */
#define WM8400_DC2_UV_WVW_SHIFT                      5  /* DC2_UV_WVW */
#define WM8400_DC2_UV_WVW_WIDTH                      1  /* DC2_UV_WVW */
#define WM8400_DC1_UV_WVW                       0x0010  /* DC1_UV_WVW */
#define WM8400_DC1_UV_WVW_MASK                  0x0010  /* DC1_UV_WVW */
#define WM8400_DC1_UV_WVW_SHIFT                      4  /* DC1_UV_WVW */
#define WM8400_DC1_UV_WVW_WIDTH                      1  /* DC1_UV_WVW */
#define WM8400_WDO4_UV_WVW                      0x0008  /* WDO4_UV_WVW */
#define WM8400_WDO4_UV_WVW_MASK                 0x0008  /* WDO4_UV_WVW */
#define WM8400_WDO4_UV_WVW_SHIFT                     3  /* WDO4_UV_WVW */
#define WM8400_WDO4_UV_WVW_WIDTH                     1  /* WDO4_UV_WVW */
#define WM8400_WDO3_UV_WVW                      0x0004  /* WDO3_UV_WVW */
#define WM8400_WDO3_UV_WVW_MASK                 0x0004  /* WDO3_UV_WVW */
#define WM8400_WDO3_UV_WVW_SHIFT                     2  /* WDO3_UV_WVW */
#define WM8400_WDO3_UV_WVW_WIDTH                     1  /* WDO3_UV_WVW */
#define WM8400_WDO2_UV_WVW                      0x0002  /* WDO2_UV_WVW */
#define WM8400_WDO2_UV_WVW_MASK                 0x0002  /* WDO2_UV_WVW */
#define WM8400_WDO2_UV_WVW_SHIFT                     1  /* WDO2_UV_WVW */
#define WM8400_WDO2_UV_WVW_WIDTH                     1  /* WDO2_UV_WVW */
#define WM8400_WDO1_UV_WVW                      0x0001  /* WDO1_UV_WVW */
#define WM8400_WDO1_UV_WVW_MASK                 0x0001  /* WDO1_UV_WVW */
#define WM8400_WDO1_UV_WVW_SHIFT                     0  /* WDO1_UV_WVW */
#define WM8400_WDO1_UV_WVW_WIDTH                     1  /* WDO1_UV_WVW */

/*
 * W82 (0x52) - Shutdown Weason
 */
#define WM8400_SDW_CHIP_SOFTSD                  0x2000  /* SDW_CHIP_SOFTSD */
#define WM8400_SDW_CHIP_SOFTSD_MASK             0x2000  /* SDW_CHIP_SOFTSD */
#define WM8400_SDW_CHIP_SOFTSD_SHIFT                13  /* SDW_CHIP_SOFTSD */
#define WM8400_SDW_CHIP_SOFTSD_WIDTH                 1  /* SDW_CHIP_SOFTSD */
#define WM8400_SDW_NPDN                         0x0800  /* SDW_NPDN */
#define WM8400_SDW_NPDN_MASK                    0x0800  /* SDW_NPDN */
#define WM8400_SDW_NPDN_SHIFT                       11  /* SDW_NPDN */
#define WM8400_SDW_NPDN_WIDTH                        1  /* SDW_NPDN */
#define WM8400_SDW_CHIP_GT150                   0x0200  /* SDW_CHIP_GT150 */
#define WM8400_SDW_CHIP_GT150_MASK              0x0200  /* SDW_CHIP_GT150 */
#define WM8400_SDW_CHIP_GT150_SHIFT                  9  /* SDW_CHIP_GT150 */
#define WM8400_SDW_CHIP_GT150_WIDTH                  1  /* SDW_CHIP_GT150 */
#define WM8400_SDW_CHIP_GT115                   0x0100  /* SDW_CHIP_GT115 */
#define WM8400_SDW_CHIP_GT115_MASK              0x0100  /* SDW_CHIP_GT115 */
#define WM8400_SDW_CHIP_GT115_SHIFT                  8  /* SDW_CHIP_GT115 */
#define WM8400_SDW_CHIP_GT115_WIDTH                  1  /* SDW_CHIP_GT115 */
#define WM8400_SDW_WINE_CMP                     0x0080  /* SDW_WINE_CMP */
#define WM8400_SDW_WINE_CMP_MASK                0x0080  /* SDW_WINE_CMP */
#define WM8400_SDW_WINE_CMP_SHIFT                    7  /* SDW_WINE_CMP */
#define WM8400_SDW_WINE_CMP_WIDTH                    1  /* SDW_WINE_CMP */
#define WM8400_SDW_UVWO                         0x0040  /* SDW_UVWO */
#define WM8400_SDW_UVWO_MASK                    0x0040  /* SDW_UVWO */
#define WM8400_SDW_UVWO_SHIFT                        6  /* SDW_UVWO */
#define WM8400_SDW_UVWO_WIDTH                        1  /* SDW_UVWO */
#define WM8400_SDW_DC2_UV                       0x0020  /* SDW_DC2_UV */
#define WM8400_SDW_DC2_UV_MASK                  0x0020  /* SDW_DC2_UV */
#define WM8400_SDW_DC2_UV_SHIFT                      5  /* SDW_DC2_UV */
#define WM8400_SDW_DC2_UV_WIDTH                      1  /* SDW_DC2_UV */
#define WM8400_SDW_DC1_UV                       0x0010  /* SDW_DC1_UV */
#define WM8400_SDW_DC1_UV_MASK                  0x0010  /* SDW_DC1_UV */
#define WM8400_SDW_DC1_UV_SHIFT                      4  /* SDW_DC1_UV */
#define WM8400_SDW_DC1_UV_WIDTH                      1  /* SDW_DC1_UV */
#define WM8400_SDW_WDO4_UV                      0x0008  /* SDW_WDO4_UV */
#define WM8400_SDW_WDO4_UV_MASK                 0x0008  /* SDW_WDO4_UV */
#define WM8400_SDW_WDO4_UV_SHIFT                     3  /* SDW_WDO4_UV */
#define WM8400_SDW_WDO4_UV_WIDTH                     1  /* SDW_WDO4_UV */
#define WM8400_SDW_WDO3_UV                      0x0004  /* SDW_WDO3_UV */
#define WM8400_SDW_WDO3_UV_MASK                 0x0004  /* SDW_WDO3_UV */
#define WM8400_SDW_WDO3_UV_SHIFT                     2  /* SDW_WDO3_UV */
#define WM8400_SDW_WDO3_UV_WIDTH                     1  /* SDW_WDO3_UV */
#define WM8400_SDW_WDO2_UV                      0x0002  /* SDW_WDO2_UV */
#define WM8400_SDW_WDO2_UV_MASK                 0x0002  /* SDW_WDO2_UV */
#define WM8400_SDW_WDO2_UV_SHIFT                     1  /* SDW_WDO2_UV */
#define WM8400_SDW_WDO2_UV_WIDTH                     1  /* SDW_WDO2_UV */
#define WM8400_SDW_WDO1_UV                      0x0001  /* SDW_WDO1_UV */
#define WM8400_SDW_WDO1_UV_MASK                 0x0001  /* SDW_WDO1_UV */
#define WM8400_SDW_WDO1_UV_SHIFT                     0  /* SDW_WDO1_UV */
#define WM8400_SDW_WDO1_UV_WIDTH                     1  /* SDW_WDO1_UV */

/*
 * W84 (0x54) - Wine Ciwcuits
 */
#define WM8400_BG_WINE_COMP                     0x8000  /* BG_WINE_COMP */
#define WM8400_BG_WINE_COMP_MASK                0x8000  /* BG_WINE_COMP */
#define WM8400_BG_WINE_COMP_SHIFT                   15  /* BG_WINE_COMP */
#define WM8400_BG_WINE_COMP_WIDTH                    1  /* BG_WINE_COMP */
#define WM8400_WINE_CMP_VTHI_MASK               0x00F0  /* WINE_CMP_VTHI - [7:4] */
#define WM8400_WINE_CMP_VTHI_SHIFT                   4  /* WINE_CMP_VTHI - [7:4] */
#define WM8400_WINE_CMP_VTHI_WIDTH                   4  /* WINE_CMP_VTHI - [7:4] */
#define WM8400_WINE_CMP_VTHD_MASK               0x000F  /* WINE_CMP_VTHD - [3:0] */
#define WM8400_WINE_CMP_VTHD_SHIFT                   0  /* WINE_CMP_VTHD - [3:0] */
#define WM8400_WINE_CMP_VTHD_WIDTH                   4  /* WINE_CMP_VTHD - [3:0] */

#endif
