/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8904.h  --  WM8904 ASoC dwivew
 *
 * Copywight 2009 Wowfson Micwoewectwonics, pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef _WM8904_H
#define _WM8904_H

#define WM8904_CWK_AUTO 0
#define WM8904_CWK_MCWK 1
#define WM8904_CWK_FWW  2

#define WM8904_FWW_MCWK          1
#define WM8904_FWW_BCWK          2
#define WM8904_FWW_WWCWK         3
#define WM8904_FWW_FWEE_WUNNING  4

/*
 * Wegistew vawues.
 */
#define WM8904_SW_WESET_AND_ID                  0x00
#define WM8904_WEVISION				0x01
#define WM8904_BIAS_CONTWOW_0                   0x04
#define WM8904_VMID_CONTWOW_0                   0x05
#define WM8904_MIC_BIAS_CONTWOW_0               0x06
#define WM8904_MIC_BIAS_CONTWOW_1               0x07
#define WM8904_ANAWOGUE_DAC_0                   0x08
#define WM8904_MIC_FIWTEW_CONTWOW               0x09
#define WM8904_ANAWOGUE_ADC_0                   0x0A
#define WM8904_POWEW_MANAGEMENT_0               0x0C
#define WM8904_POWEW_MANAGEMENT_2               0x0E
#define WM8904_POWEW_MANAGEMENT_3               0x0F
#define WM8904_POWEW_MANAGEMENT_6               0x12
#define WM8904_CWOCK_WATES_0                    0x14
#define WM8904_CWOCK_WATES_1                    0x15
#define WM8904_CWOCK_WATES_2                    0x16
#define WM8904_AUDIO_INTEWFACE_0                0x18
#define WM8904_AUDIO_INTEWFACE_1                0x19
#define WM8904_AUDIO_INTEWFACE_2                0x1A
#define WM8904_AUDIO_INTEWFACE_3                0x1B
#define WM8904_DAC_DIGITAW_VOWUME_WEFT          0x1E
#define WM8904_DAC_DIGITAW_VOWUME_WIGHT         0x1F
#define WM8904_DAC_DIGITAW_0                    0x20
#define WM8904_DAC_DIGITAW_1                    0x21
#define WM8904_ADC_DIGITAW_VOWUME_WEFT          0x24
#define WM8904_ADC_DIGITAW_VOWUME_WIGHT         0x25
#define WM8904_ADC_DIGITAW_0                    0x26
#define WM8904_DIGITAW_MICWOPHONE_0             0x27
#define WM8904_DWC_0                            0x28
#define WM8904_DWC_1                            0x29
#define WM8904_DWC_2                            0x2A
#define WM8904_DWC_3                            0x2B
#define WM8904_ANAWOGUE_WEFT_INPUT_0            0x2C
#define WM8904_ANAWOGUE_WIGHT_INPUT_0           0x2D
#define WM8904_ANAWOGUE_WEFT_INPUT_1            0x2E
#define WM8904_ANAWOGUE_WIGHT_INPUT_1           0x2F
#define WM8904_ANAWOGUE_OUT1_WEFT               0x39
#define WM8904_ANAWOGUE_OUT1_WIGHT              0x3A
#define WM8904_ANAWOGUE_OUT2_WEFT               0x3B
#define WM8904_ANAWOGUE_OUT2_WIGHT              0x3C
#define WM8904_ANAWOGUE_OUT12_ZC                0x3D
#define WM8904_DC_SEWVO_0                       0x43
#define WM8904_DC_SEWVO_1                       0x44
#define WM8904_DC_SEWVO_2                       0x45
#define WM8904_DC_SEWVO_4                       0x47
#define WM8904_DC_SEWVO_5                       0x48
#define WM8904_DC_SEWVO_6                       0x49
#define WM8904_DC_SEWVO_7                       0x4A
#define WM8904_DC_SEWVO_8                       0x4B
#define WM8904_DC_SEWVO_9                       0x4C
#define WM8904_DC_SEWVO_WEADBACK_0              0x4D
#define WM8904_ANAWOGUE_HP_0                    0x5A
#define WM8904_ANAWOGUE_WINEOUT_0               0x5E
#define WM8904_CHAWGE_PUMP_0                    0x62
#define WM8904_CWASS_W_0                        0x68
#define WM8904_WWITE_SEQUENCEW_0                0x6C
#define WM8904_WWITE_SEQUENCEW_1                0x6D
#define WM8904_WWITE_SEQUENCEW_2                0x6E
#define WM8904_WWITE_SEQUENCEW_3                0x6F
#define WM8904_WWITE_SEQUENCEW_4                0x70
#define WM8904_FWW_CONTWOW_1                    0x74
#define WM8904_FWW_CONTWOW_2                    0x75
#define WM8904_FWW_CONTWOW_3                    0x76
#define WM8904_FWW_CONTWOW_4                    0x77
#define WM8904_FWW_CONTWOW_5                    0x78
#define WM8904_GPIO_CONTWOW_1                   0x79
#define WM8904_GPIO_CONTWOW_2                   0x7A
#define WM8904_GPIO_CONTWOW_3                   0x7B
#define WM8904_GPIO_CONTWOW_4                   0x7C
#define WM8904_DIGITAW_PUWWS                    0x7E
#define WM8904_INTEWWUPT_STATUS                 0x7F
#define WM8904_INTEWWUPT_STATUS_MASK            0x80
#define WM8904_INTEWWUPT_POWAWITY               0x81
#define WM8904_INTEWWUPT_DEBOUNCE               0x82
#define WM8904_EQ1                              0x86
#define WM8904_EQ2                              0x87
#define WM8904_EQ3                              0x88
#define WM8904_EQ4                              0x89
#define WM8904_EQ5                              0x8A
#define WM8904_EQ6                              0x8B
#define WM8904_EQ7                              0x8C
#define WM8904_EQ8                              0x8D
#define WM8904_EQ9                              0x8E
#define WM8904_EQ10                             0x8F
#define WM8904_EQ11                             0x90
#define WM8904_EQ12                             0x91
#define WM8904_EQ13                             0x92
#define WM8904_EQ14                             0x93
#define WM8904_EQ15                             0x94
#define WM8904_EQ16                             0x95
#define WM8904_EQ17                             0x96
#define WM8904_EQ18                             0x97
#define WM8904_EQ19                             0x98
#define WM8904_EQ20                             0x99
#define WM8904_EQ21                             0x9A
#define WM8904_EQ22                             0x9B
#define WM8904_EQ23                             0x9C
#define WM8904_EQ24                             0x9D
#define WM8904_CONTWOW_INTEWFACE_TEST_1         0xA1
#define WM8904_ADC_TEST_0			0xC6
#define WM8904_ANAWOGUE_OUTPUT_BIAS_0           0xCC
#define WM8904_FWW_NCO_TEST_0                   0xF7
#define WM8904_FWW_NCO_TEST_1                   0xF8

#define WM8904_WEGISTEW_COUNT                   101
#define WM8904_MAX_WEGISTEW                     0xF8

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - SW Weset and ID
 */
#define WM8904_SW_WST_DEV_ID1_MASK              0xFFFF  /* SW_WST_DEV_ID1 - [15:0] */
#define WM8904_SW_WST_DEV_ID1_SHIFT                  0  /* SW_WST_DEV_ID1 - [15:0] */
#define WM8904_SW_WST_DEV_ID1_WIDTH                 16  /* SW_WST_DEV_ID1 - [15:0] */

/*
 * W1 (0x01) - Wevision
 */
#define WM8904_WEVISION_MASK              	0x000F  /* WEVISION - [3:0] */
#define WM8904_WEVISION_SHIFT             	     0  /* WEVISION - [3:0] */
#define WM8904_WEVISION_WIDTH             	    16  /* WEVISION - [3:0] */

/*
 * W4 (0x04) - Bias Contwow 0
 */
#define WM8904_POBCTWW                          0x0010  /* POBCTWW */
#define WM8904_POBCTWW_MASK                     0x0010  /* POBCTWW */
#define WM8904_POBCTWW_SHIFT                         4  /* POBCTWW */
#define WM8904_POBCTWW_WIDTH                         1  /* POBCTWW */
#define WM8904_ISEW_MASK                        0x000C  /* ISEW - [3:2] */
#define WM8904_ISEW_SHIFT                            2  /* ISEW - [3:2] */
#define WM8904_ISEW_WIDTH                            2  /* ISEW - [3:2] */
#define WM8904_STAWTUP_BIAS_ENA                 0x0002  /* STAWTUP_BIAS_ENA */
#define WM8904_STAWTUP_BIAS_ENA_MASK            0x0002  /* STAWTUP_BIAS_ENA */
#define WM8904_STAWTUP_BIAS_ENA_SHIFT                1  /* STAWTUP_BIAS_ENA */
#define WM8904_STAWTUP_BIAS_ENA_WIDTH                1  /* STAWTUP_BIAS_ENA */
#define WM8904_BIAS_ENA                         0x0001  /* BIAS_ENA */
#define WM8904_BIAS_ENA_MASK                    0x0001  /* BIAS_ENA */
#define WM8904_BIAS_ENA_SHIFT                        0  /* BIAS_ENA */
#define WM8904_BIAS_ENA_WIDTH                        1  /* BIAS_ENA */

/*
 * W5 (0x05) - VMID Contwow 0
 */
#define WM8904_VMID_BUF_ENA                     0x0040  /* VMID_BUF_ENA */
#define WM8904_VMID_BUF_ENA_MASK                0x0040  /* VMID_BUF_ENA */
#define WM8904_VMID_BUF_ENA_SHIFT                    6  /* VMID_BUF_ENA */
#define WM8904_VMID_BUF_ENA_WIDTH                    1  /* VMID_BUF_ENA */
#define WM8904_VMID_WES_MASK                    0x0006  /* VMID_WES - [2:1] */
#define WM8904_VMID_WES_SHIFT                        1  /* VMID_WES - [2:1] */
#define WM8904_VMID_WES_WIDTH                        2  /* VMID_WES - [2:1] */
#define WM8904_VMID_ENA                         0x0001  /* VMID_ENA */
#define WM8904_VMID_ENA_MASK                    0x0001  /* VMID_ENA */
#define WM8904_VMID_ENA_SHIFT                        0  /* VMID_ENA */
#define WM8904_VMID_ENA_WIDTH                        1  /* VMID_ENA */

/*
 * W8 (0x08) - Anawogue DAC 0
 */
#define WM8904_DAC_BIAS_SEW_MASK                0x0018  /* DAC_BIAS_SEW - [4:3] */
#define WM8904_DAC_BIAS_SEW_SHIFT                    3  /* DAC_BIAS_SEW - [4:3] */
#define WM8904_DAC_BIAS_SEW_WIDTH                    2  /* DAC_BIAS_SEW - [4:3] */
#define WM8904_DAC_VMID_BIAS_SEW_MASK           0x0006  /* DAC_VMID_BIAS_SEW - [2:1] */
#define WM8904_DAC_VMID_BIAS_SEW_SHIFT               1  /* DAC_VMID_BIAS_SEW - [2:1] */
#define WM8904_DAC_VMID_BIAS_SEW_WIDTH               2  /* DAC_VMID_BIAS_SEW - [2:1] */

/*
 * W9 (0x09) - mic Fiwtew Contwow
 */
#define WM8904_MIC_DET_SET_THWESHOWD_MASK       0xF000  /* MIC_DET_SET_THWESHOWD - [15:12] */
#define WM8904_MIC_DET_SET_THWESHOWD_SHIFT          12  /* MIC_DET_SET_THWESHOWD - [15:12] */
#define WM8904_MIC_DET_SET_THWESHOWD_WIDTH           4  /* MIC_DET_SET_THWESHOWD - [15:12] */
#define WM8904_MIC_DET_WESET_THWESHOWD_MASK     0x0F00  /* MIC_DET_WESET_THWESHOWD - [11:8] */
#define WM8904_MIC_DET_WESET_THWESHOWD_SHIFT         8  /* MIC_DET_WESET_THWESHOWD - [11:8] */
#define WM8904_MIC_DET_WESET_THWESHOWD_WIDTH         4  /* MIC_DET_WESET_THWESHOWD - [11:8] */
#define WM8904_MIC_SHOWT_SET_THWESHOWD_MASK     0x00F0  /* MIC_SHOWT_SET_THWESHOWD - [7:4] */
#define WM8904_MIC_SHOWT_SET_THWESHOWD_SHIFT         4  /* MIC_SHOWT_SET_THWESHOWD - [7:4] */
#define WM8904_MIC_SHOWT_SET_THWESHOWD_WIDTH         4  /* MIC_SHOWT_SET_THWESHOWD - [7:4] */
#define WM8904_MIC_SHOWT_WESET_THWESHOWD_MASK   0x000F  /* MIC_SHOWT_WESET_THWESHOWD - [3:0] */
#define WM8904_MIC_SHOWT_WESET_THWESHOWD_SHIFT       0  /* MIC_SHOWT_WESET_THWESHOWD - [3:0] */
#define WM8904_MIC_SHOWT_WESET_THWESHOWD_WIDTH       4  /* MIC_SHOWT_WESET_THWESHOWD - [3:0] */

/*
 * W10 (0x0A) - Anawogue ADC 0
 */
#define WM8904_ADC_OSW128                       0x0001  /* ADC_OSW128 */
#define WM8904_ADC_OSW128_MASK                  0x0001  /* ADC_OSW128 */
#define WM8904_ADC_OSW128_SHIFT                      0  /* ADC_OSW128 */
#define WM8904_ADC_OSW128_WIDTH                      1  /* ADC_OSW128 */

/*
 * W12 (0x0C) - Powew Management 0
 */
#define WM8904_INW_ENA                          0x0002  /* INW_ENA */
#define WM8904_INW_ENA_MASK                     0x0002  /* INW_ENA */
#define WM8904_INW_ENA_SHIFT                         1  /* INW_ENA */
#define WM8904_INW_ENA_WIDTH                         1  /* INW_ENA */
#define WM8904_INW_ENA                          0x0001  /* INW_ENA */
#define WM8904_INW_ENA_MASK                     0x0001  /* INW_ENA */
#define WM8904_INW_ENA_SHIFT                         0  /* INW_ENA */
#define WM8904_INW_ENA_WIDTH                         1  /* INW_ENA */

/*
 * W14 (0x0E) - Powew Management 2
 */
#define WM8904_HPW_PGA_ENA                      0x0002  /* HPW_PGA_ENA */
#define WM8904_HPW_PGA_ENA_MASK                 0x0002  /* HPW_PGA_ENA */
#define WM8904_HPW_PGA_ENA_SHIFT                     1  /* HPW_PGA_ENA */
#define WM8904_HPW_PGA_ENA_WIDTH                     1  /* HPW_PGA_ENA */
#define WM8904_HPW_PGA_ENA                      0x0001  /* HPW_PGA_ENA */
#define WM8904_HPW_PGA_ENA_MASK                 0x0001  /* HPW_PGA_ENA */
#define WM8904_HPW_PGA_ENA_SHIFT                     0  /* HPW_PGA_ENA */
#define WM8904_HPW_PGA_ENA_WIDTH                     1  /* HPW_PGA_ENA */

/*
 * W15 (0x0F) - Powew Management 3
 */
#define WM8904_WINEOUTW_PGA_ENA                 0x0002  /* WINEOUTW_PGA_ENA */
#define WM8904_WINEOUTW_PGA_ENA_MASK            0x0002  /* WINEOUTW_PGA_ENA */
#define WM8904_WINEOUTW_PGA_ENA_SHIFT                1  /* WINEOUTW_PGA_ENA */
#define WM8904_WINEOUTW_PGA_ENA_WIDTH                1  /* WINEOUTW_PGA_ENA */
#define WM8904_WINEOUTW_PGA_ENA                 0x0001  /* WINEOUTW_PGA_ENA */
#define WM8904_WINEOUTW_PGA_ENA_MASK            0x0001  /* WINEOUTW_PGA_ENA */
#define WM8904_WINEOUTW_PGA_ENA_SHIFT                0  /* WINEOUTW_PGA_ENA */
#define WM8904_WINEOUTW_PGA_ENA_WIDTH                1  /* WINEOUTW_PGA_ENA */

/*
 * W18 (0x12) - Powew Management 6
 */
#define WM8904_DACW_ENA                         0x0008  /* DACW_ENA */
#define WM8904_DACW_ENA_MASK                    0x0008  /* DACW_ENA */
#define WM8904_DACW_ENA_SHIFT                        3  /* DACW_ENA */
#define WM8904_DACW_ENA_WIDTH                        1  /* DACW_ENA */
#define WM8904_DACW_ENA                         0x0004  /* DACW_ENA */
#define WM8904_DACW_ENA_MASK                    0x0004  /* DACW_ENA */
#define WM8904_DACW_ENA_SHIFT                        2  /* DACW_ENA */
#define WM8904_DACW_ENA_WIDTH                        1  /* DACW_ENA */
#define WM8904_ADCW_ENA                         0x0002  /* ADCW_ENA */
#define WM8904_ADCW_ENA_MASK                    0x0002  /* ADCW_ENA */
#define WM8904_ADCW_ENA_SHIFT                        1  /* ADCW_ENA */
#define WM8904_ADCW_ENA_WIDTH                        1  /* ADCW_ENA */
#define WM8904_ADCW_ENA                         0x0001  /* ADCW_ENA */
#define WM8904_ADCW_ENA_MASK                    0x0001  /* ADCW_ENA */
#define WM8904_ADCW_ENA_SHIFT                        0  /* ADCW_ENA */
#define WM8904_ADCW_ENA_WIDTH                        1  /* ADCW_ENA */

/*
 * W20 (0x14) - Cwock Wates 0
 */
#define WM8904_TOCWK_WATE_DIV16                 0x4000  /* TOCWK_WATE_DIV16 */
#define WM8904_TOCWK_WATE_DIV16_MASK            0x4000  /* TOCWK_WATE_DIV16 */
#define WM8904_TOCWK_WATE_DIV16_SHIFT               14  /* TOCWK_WATE_DIV16 */
#define WM8904_TOCWK_WATE_DIV16_WIDTH                1  /* TOCWK_WATE_DIV16 */
#define WM8904_TOCWK_WATE_X4                    0x2000  /* TOCWK_WATE_X4 */
#define WM8904_TOCWK_WATE_X4_MASK               0x2000  /* TOCWK_WATE_X4 */
#define WM8904_TOCWK_WATE_X4_SHIFT                  13  /* TOCWK_WATE_X4 */
#define WM8904_TOCWK_WATE_X4_WIDTH                   1  /* TOCWK_WATE_X4 */
#define WM8904_SW_MODE                          0x1000  /* SW_MODE */
#define WM8904_SW_MODE_MASK                     0x1000  /* SW_MODE */
#define WM8904_SW_MODE_SHIFT                        12  /* SW_MODE */
#define WM8904_SW_MODE_WIDTH                         1  /* SW_MODE */
#define WM8904_MCWK_DIV                         0x0001  /* MCWK_DIV */
#define WM8904_MCWK_DIV_MASK                    0x0001  /* MCWK_DIV */
#define WM8904_MCWK_DIV_SHIFT                        0  /* MCWK_DIV */
#define WM8904_MCWK_DIV_WIDTH                        1  /* MCWK_DIV */

/*
 * W21 (0x15) - Cwock Wates 1
 */
#define WM8904_CWK_SYS_WATE_MASK                0x3C00  /* CWK_SYS_WATE - [13:10] */
#define WM8904_CWK_SYS_WATE_SHIFT                   10  /* CWK_SYS_WATE - [13:10] */
#define WM8904_CWK_SYS_WATE_WIDTH                    4  /* CWK_SYS_WATE - [13:10] */
#define WM8904_SAMPWE_WATE_MASK                 0x0007  /* SAMPWE_WATE - [2:0] */
#define WM8904_SAMPWE_WATE_SHIFT                     0  /* SAMPWE_WATE - [2:0] */
#define WM8904_SAMPWE_WATE_WIDTH                     3  /* SAMPWE_WATE - [2:0] */

/*
 * W22 (0x16) - Cwock Wates 2
 */
#define WM8904_MCWK_INV                         0x8000  /* MCWK_INV */
#define WM8904_MCWK_INV_MASK                    0x8000  /* MCWK_INV */
#define WM8904_MCWK_INV_SHIFT                       15  /* MCWK_INV */
#define WM8904_MCWK_INV_WIDTH                        1  /* MCWK_INV */
#define WM8904_SYSCWK_SWC                       0x4000  /* SYSCWK_SWC */
#define WM8904_SYSCWK_SWC_MASK                  0x4000  /* SYSCWK_SWC */
#define WM8904_SYSCWK_SWC_SHIFT                     14  /* SYSCWK_SWC */
#define WM8904_SYSCWK_SWC_WIDTH                      1  /* SYSCWK_SWC */
#define WM8904_TOCWK_WATE                       0x1000  /* TOCWK_WATE */
#define WM8904_TOCWK_WATE_MASK                  0x1000  /* TOCWK_WATE */
#define WM8904_TOCWK_WATE_SHIFT                     12  /* TOCWK_WATE */
#define WM8904_TOCWK_WATE_WIDTH                      1  /* TOCWK_WATE */
#define WM8904_OPCWK_ENA                        0x0008  /* OPCWK_ENA */
#define WM8904_OPCWK_ENA_MASK                   0x0008  /* OPCWK_ENA */
#define WM8904_OPCWK_ENA_SHIFT                       3  /* OPCWK_ENA */
#define WM8904_OPCWK_ENA_WIDTH                       1  /* OPCWK_ENA */
#define WM8904_CWK_SYS_ENA                      0x0004  /* CWK_SYS_ENA */
#define WM8904_CWK_SYS_ENA_MASK                 0x0004  /* CWK_SYS_ENA */
#define WM8904_CWK_SYS_ENA_SHIFT                     2  /* CWK_SYS_ENA */
#define WM8904_CWK_SYS_ENA_WIDTH                     1  /* CWK_SYS_ENA */
#define WM8904_CWK_DSP_ENA                      0x0002  /* CWK_DSP_ENA */
#define WM8904_CWK_DSP_ENA_MASK                 0x0002  /* CWK_DSP_ENA */
#define WM8904_CWK_DSP_ENA_SHIFT                     1  /* CWK_DSP_ENA */
#define WM8904_CWK_DSP_ENA_WIDTH                     1  /* CWK_DSP_ENA */
#define WM8904_TOCWK_ENA                        0x0001  /* TOCWK_ENA */
#define WM8904_TOCWK_ENA_MASK                   0x0001  /* TOCWK_ENA */
#define WM8904_TOCWK_ENA_SHIFT                       0  /* TOCWK_ENA */
#define WM8904_TOCWK_ENA_WIDTH                       1  /* TOCWK_ENA */

/*
 * W24 (0x18) - Audio Intewface 0
 */
#define WM8904_DACW_DATINV                      0x1000  /* DACW_DATINV */
#define WM8904_DACW_DATINV_MASK                 0x1000  /* DACW_DATINV */
#define WM8904_DACW_DATINV_SHIFT                    12  /* DACW_DATINV */
#define WM8904_DACW_DATINV_WIDTH                     1  /* DACW_DATINV */
#define WM8904_DACW_DATINV                      0x0800  /* DACW_DATINV */
#define WM8904_DACW_DATINV_MASK                 0x0800  /* DACW_DATINV */
#define WM8904_DACW_DATINV_SHIFT                    11  /* DACW_DATINV */
#define WM8904_DACW_DATINV_WIDTH                     1  /* DACW_DATINV */
#define WM8904_DAC_BOOST_MASK                   0x0600  /* DAC_BOOST - [10:9] */
#define WM8904_DAC_BOOST_SHIFT                       9  /* DAC_BOOST - [10:9] */
#define WM8904_DAC_BOOST_WIDTH                       2  /* DAC_BOOST - [10:9] */
#define WM8904_WOOPBACK                         0x0100  /* WOOPBACK */
#define WM8904_WOOPBACK_MASK                    0x0100  /* WOOPBACK */
#define WM8904_WOOPBACK_SHIFT                        8  /* WOOPBACK */
#define WM8904_WOOPBACK_WIDTH                        1  /* WOOPBACK */
#define WM8904_AIFADCW_SWC                      0x0080  /* AIFADCW_SWC */
#define WM8904_AIFADCW_SWC_MASK                 0x0080  /* AIFADCW_SWC */
#define WM8904_AIFADCW_SWC_SHIFT                     7  /* AIFADCW_SWC */
#define WM8904_AIFADCW_SWC_WIDTH                     1  /* AIFADCW_SWC */
#define WM8904_AIFADCW_SWC                      0x0040  /* AIFADCW_SWC */
#define WM8904_AIFADCW_SWC_MASK                 0x0040  /* AIFADCW_SWC */
#define WM8904_AIFADCW_SWC_SHIFT                     6  /* AIFADCW_SWC */
#define WM8904_AIFADCW_SWC_WIDTH                     1  /* AIFADCW_SWC */
#define WM8904_AIFDACW_SWC                      0x0020  /* AIFDACW_SWC */
#define WM8904_AIFDACW_SWC_MASK                 0x0020  /* AIFDACW_SWC */
#define WM8904_AIFDACW_SWC_SHIFT                     5  /* AIFDACW_SWC */
#define WM8904_AIFDACW_SWC_WIDTH                     1  /* AIFDACW_SWC */
#define WM8904_AIFDACW_SWC                      0x0010  /* AIFDACW_SWC */
#define WM8904_AIFDACW_SWC_MASK                 0x0010  /* AIFDACW_SWC */
#define WM8904_AIFDACW_SWC_SHIFT                     4  /* AIFDACW_SWC */
#define WM8904_AIFDACW_SWC_WIDTH                     1  /* AIFDACW_SWC */
#define WM8904_ADC_COMP                         0x0008  /* ADC_COMP */
#define WM8904_ADC_COMP_MASK                    0x0008  /* ADC_COMP */
#define WM8904_ADC_COMP_SHIFT                        3  /* ADC_COMP */
#define WM8904_ADC_COMP_WIDTH                        1  /* ADC_COMP */
#define WM8904_ADC_COMPMODE                     0x0004  /* ADC_COMPMODE */
#define WM8904_ADC_COMPMODE_MASK                0x0004  /* ADC_COMPMODE */
#define WM8904_ADC_COMPMODE_SHIFT                    2  /* ADC_COMPMODE */
#define WM8904_ADC_COMPMODE_WIDTH                    1  /* ADC_COMPMODE */
#define WM8904_DAC_COMP                         0x0002  /* DAC_COMP */
#define WM8904_DAC_COMP_MASK                    0x0002  /* DAC_COMP */
#define WM8904_DAC_COMP_SHIFT                        1  /* DAC_COMP */
#define WM8904_DAC_COMP_WIDTH                        1  /* DAC_COMP */
#define WM8904_DAC_COMPMODE                     0x0001  /* DAC_COMPMODE */
#define WM8904_DAC_COMPMODE_MASK                0x0001  /* DAC_COMPMODE */
#define WM8904_DAC_COMPMODE_SHIFT                    0  /* DAC_COMPMODE */
#define WM8904_DAC_COMPMODE_WIDTH                    1  /* DAC_COMPMODE */

/*
 * W25 (0x19) - Audio Intewface 1
 */
#define WM8904_AIFDAC_TDM                       0x2000  /* AIFDAC_TDM */
#define WM8904_AIFDAC_TDM_MASK                  0x2000  /* AIFDAC_TDM */
#define WM8904_AIFDAC_TDM_SHIFT                     13  /* AIFDAC_TDM */
#define WM8904_AIFDAC_TDM_WIDTH                      1  /* AIFDAC_TDM */
#define WM8904_AIFDAC_TDM_CHAN                  0x1000  /* AIFDAC_TDM_CHAN */
#define WM8904_AIFDAC_TDM_CHAN_MASK             0x1000  /* AIFDAC_TDM_CHAN */
#define WM8904_AIFDAC_TDM_CHAN_SHIFT                12  /* AIFDAC_TDM_CHAN */
#define WM8904_AIFDAC_TDM_CHAN_WIDTH                 1  /* AIFDAC_TDM_CHAN */
#define WM8904_AIFADC_TDM                       0x0800  /* AIFADC_TDM */
#define WM8904_AIFADC_TDM_MASK                  0x0800  /* AIFADC_TDM */
#define WM8904_AIFADC_TDM_SHIFT                     11  /* AIFADC_TDM */
#define WM8904_AIFADC_TDM_WIDTH                      1  /* AIFADC_TDM */
#define WM8904_AIFADC_TDM_CHAN                  0x0400  /* AIFADC_TDM_CHAN */
#define WM8904_AIFADC_TDM_CHAN_MASK             0x0400  /* AIFADC_TDM_CHAN */
#define WM8904_AIFADC_TDM_CHAN_SHIFT                10  /* AIFADC_TDM_CHAN */
#define WM8904_AIFADC_TDM_CHAN_WIDTH                 1  /* AIFADC_TDM_CHAN */
#define WM8904_AIF_TWIS                         0x0100  /* AIF_TWIS */
#define WM8904_AIF_TWIS_MASK                    0x0100  /* AIF_TWIS */
#define WM8904_AIF_TWIS_SHIFT                        8  /* AIF_TWIS */
#define WM8904_AIF_TWIS_WIDTH                        1  /* AIF_TWIS */
#define WM8904_AIF_BCWK_INV                     0x0080  /* AIF_BCWK_INV */
#define WM8904_AIF_BCWK_INV_MASK                0x0080  /* AIF_BCWK_INV */
#define WM8904_AIF_BCWK_INV_SHIFT                    7  /* AIF_BCWK_INV */
#define WM8904_AIF_BCWK_INV_WIDTH                    1  /* AIF_BCWK_INV */
#define WM8904_BCWK_DIW                         0x0040  /* BCWK_DIW */
#define WM8904_BCWK_DIW_MASK                    0x0040  /* BCWK_DIW */
#define WM8904_BCWK_DIW_SHIFT                        6  /* BCWK_DIW */
#define WM8904_BCWK_DIW_WIDTH                        1  /* BCWK_DIW */
#define WM8904_AIF_WWCWK_INV                    0x0010  /* AIF_WWCWK_INV */
#define WM8904_AIF_WWCWK_INV_MASK               0x0010  /* AIF_WWCWK_INV */
#define WM8904_AIF_WWCWK_INV_SHIFT                   4  /* AIF_WWCWK_INV */
#define WM8904_AIF_WWCWK_INV_WIDTH                   1  /* AIF_WWCWK_INV */
#define WM8904_AIF_WW_MASK                      0x000C  /* AIF_WW - [3:2] */
#define WM8904_AIF_WW_SHIFT                          2  /* AIF_WW - [3:2] */
#define WM8904_AIF_WW_WIDTH                          2  /* AIF_WW - [3:2] */
#define WM8904_AIF_FMT_MASK                     0x0003  /* AIF_FMT - [1:0] */
#define WM8904_AIF_FMT_SHIFT                         0  /* AIF_FMT - [1:0] */
#define WM8904_AIF_FMT_WIDTH                         2  /* AIF_FMT - [1:0] */

/*
 * W26 (0x1A) - Audio Intewface 2
 */
#define WM8904_OPCWK_DIV_MASK                   0x0F00  /* OPCWK_DIV - [11:8] */
#define WM8904_OPCWK_DIV_SHIFT                       8  /* OPCWK_DIV - [11:8] */
#define WM8904_OPCWK_DIV_WIDTH                       4  /* OPCWK_DIV - [11:8] */
#define WM8904_BCWK_DIV_MASK                    0x001F  /* BCWK_DIV - [4:0] */
#define WM8904_BCWK_DIV_SHIFT                        0  /* BCWK_DIV - [4:0] */
#define WM8904_BCWK_DIV_WIDTH                        5  /* BCWK_DIV - [4:0] */

/*
 * W27 (0x1B) - Audio Intewface 3
 */
#define WM8904_WWCWK_DIW                        0x0800  /* WWCWK_DIW */
#define WM8904_WWCWK_DIW_MASK                   0x0800  /* WWCWK_DIW */
#define WM8904_WWCWK_DIW_SHIFT                      11  /* WWCWK_DIW */
#define WM8904_WWCWK_DIW_WIDTH                       1  /* WWCWK_DIW */
#define WM8904_WWCWK_WATE_MASK                  0x07FF  /* WWCWK_WATE - [10:0] */
#define WM8904_WWCWK_WATE_SHIFT                      0  /* WWCWK_WATE - [10:0] */
#define WM8904_WWCWK_WATE_WIDTH                     11  /* WWCWK_WATE - [10:0] */

/*
 * W30 (0x1E) - DAC Digitaw Vowume Weft
 */
#define WM8904_DAC_VU                           0x0100  /* DAC_VU */
#define WM8904_DAC_VU_MASK                      0x0100  /* DAC_VU */
#define WM8904_DAC_VU_SHIFT                          8  /* DAC_VU */
#define WM8904_DAC_VU_WIDTH                          1  /* DAC_VU */
#define WM8904_DACW_VOW_MASK                    0x00FF  /* DACW_VOW - [7:0] */
#define WM8904_DACW_VOW_SHIFT                        0  /* DACW_VOW - [7:0] */
#define WM8904_DACW_VOW_WIDTH                        8  /* DACW_VOW - [7:0] */

/*
 * W31 (0x1F) - DAC Digitaw Vowume Wight
 */
#define WM8904_DAC_VU                           0x0100  /* DAC_VU */
#define WM8904_DAC_VU_MASK                      0x0100  /* DAC_VU */
#define WM8904_DAC_VU_SHIFT                          8  /* DAC_VU */
#define WM8904_DAC_VU_WIDTH                          1  /* DAC_VU */
#define WM8904_DACW_VOW_MASK                    0x00FF  /* DACW_VOW - [7:0] */
#define WM8904_DACW_VOW_SHIFT                        0  /* DACW_VOW - [7:0] */
#define WM8904_DACW_VOW_WIDTH                        8  /* DACW_VOW - [7:0] */

/*
 * W32 (0x20) - DAC Digitaw 0
 */
#define WM8904_ADCW_DAC_SVOW_MASK               0x0F00  /* ADCW_DAC_SVOW - [11:8] */
#define WM8904_ADCW_DAC_SVOW_SHIFT                   8  /* ADCW_DAC_SVOW - [11:8] */
#define WM8904_ADCW_DAC_SVOW_WIDTH                   4  /* ADCW_DAC_SVOW - [11:8] */
#define WM8904_ADCW_DAC_SVOW_MASK               0x00F0  /* ADCW_DAC_SVOW - [7:4] */
#define WM8904_ADCW_DAC_SVOW_SHIFT                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8904_ADCW_DAC_SVOW_WIDTH                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8904_ADC_TO_DACW_MASK                 0x000C  /* ADC_TO_DACW - [3:2] */
#define WM8904_ADC_TO_DACW_SHIFT                     2  /* ADC_TO_DACW - [3:2] */
#define WM8904_ADC_TO_DACW_WIDTH                     2  /* ADC_TO_DACW - [3:2] */
#define WM8904_ADC_TO_DACW_MASK                 0x0003  /* ADC_TO_DACW - [1:0] */
#define WM8904_ADC_TO_DACW_SHIFT                     0  /* ADC_TO_DACW - [1:0] */
#define WM8904_ADC_TO_DACW_WIDTH                     2  /* ADC_TO_DACW - [1:0] */

/*
 * W33 (0x21) - DAC Digitaw 1
 */
#define WM8904_DAC_MONO                         0x1000  /* DAC_MONO */
#define WM8904_DAC_MONO_MASK                    0x1000  /* DAC_MONO */
#define WM8904_DAC_MONO_SHIFT                       12  /* DAC_MONO */
#define WM8904_DAC_MONO_WIDTH                        1  /* DAC_MONO */
#define WM8904_DAC_SB_FIWT                      0x0800  /* DAC_SB_FIWT */
#define WM8904_DAC_SB_FIWT_MASK                 0x0800  /* DAC_SB_FIWT */
#define WM8904_DAC_SB_FIWT_SHIFT                    11  /* DAC_SB_FIWT */
#define WM8904_DAC_SB_FIWT_WIDTH                     1  /* DAC_SB_FIWT */
#define WM8904_DAC_MUTEWATE                     0x0400  /* DAC_MUTEWATE */
#define WM8904_DAC_MUTEWATE_MASK                0x0400  /* DAC_MUTEWATE */
#define WM8904_DAC_MUTEWATE_SHIFT                   10  /* DAC_MUTEWATE */
#define WM8904_DAC_MUTEWATE_WIDTH                    1  /* DAC_MUTEWATE */
#define WM8904_DAC_UNMUTE_WAMP                  0x0200  /* DAC_UNMUTE_WAMP */
#define WM8904_DAC_UNMUTE_WAMP_MASK             0x0200  /* DAC_UNMUTE_WAMP */
#define WM8904_DAC_UNMUTE_WAMP_SHIFT                 9  /* DAC_UNMUTE_WAMP */
#define WM8904_DAC_UNMUTE_WAMP_WIDTH                 1  /* DAC_UNMUTE_WAMP */
#define WM8904_DAC_OSW128                       0x0040  /* DAC_OSW128 */
#define WM8904_DAC_OSW128_MASK                  0x0040  /* DAC_OSW128 */
#define WM8904_DAC_OSW128_SHIFT                      6  /* DAC_OSW128 */
#define WM8904_DAC_OSW128_WIDTH                      1  /* DAC_OSW128 */
#define WM8904_DAC_MUTE                         0x0008  /* DAC_MUTE */
#define WM8904_DAC_MUTE_MASK                    0x0008  /* DAC_MUTE */
#define WM8904_DAC_MUTE_SHIFT                        3  /* DAC_MUTE */
#define WM8904_DAC_MUTE_WIDTH                        1  /* DAC_MUTE */
#define WM8904_DEEMPH_MASK                      0x0006  /* DEEMPH - [2:1] */
#define WM8904_DEEMPH_SHIFT                          1  /* DEEMPH - [2:1] */
#define WM8904_DEEMPH_WIDTH                          2  /* DEEMPH - [2:1] */

/*
 * W36 (0x24) - ADC Digitaw Vowume Weft
 */
#define WM8904_ADC_VU                           0x0100  /* ADC_VU */
#define WM8904_ADC_VU_MASK                      0x0100  /* ADC_VU */
#define WM8904_ADC_VU_SHIFT                          8  /* ADC_VU */
#define WM8904_ADC_VU_WIDTH                          1  /* ADC_VU */
#define WM8904_ADCW_VOW_MASK                    0x00FF  /* ADCW_VOW - [7:0] */
#define WM8904_ADCW_VOW_SHIFT                        0  /* ADCW_VOW - [7:0] */
#define WM8904_ADCW_VOW_WIDTH                        8  /* ADCW_VOW - [7:0] */

/*
 * W37 (0x25) - ADC Digitaw Vowume Wight
 */
#define WM8904_ADC_VU                           0x0100  /* ADC_VU */
#define WM8904_ADC_VU_MASK                      0x0100  /* ADC_VU */
#define WM8904_ADC_VU_SHIFT                          8  /* ADC_VU */
#define WM8904_ADC_VU_WIDTH                          1  /* ADC_VU */
#define WM8904_ADCW_VOW_MASK                    0x00FF  /* ADCW_VOW - [7:0] */
#define WM8904_ADCW_VOW_SHIFT                        0  /* ADCW_VOW - [7:0] */
#define WM8904_ADCW_VOW_WIDTH                        8  /* ADCW_VOW - [7:0] */

/*
 * W38 (0x26) - ADC Digitaw 0
 */
#define WM8904_ADC_HPF_CUT_MASK                 0x0060  /* ADC_HPF_CUT - [6:5] */
#define WM8904_ADC_HPF_CUT_SHIFT                     5  /* ADC_HPF_CUT - [6:5] */
#define WM8904_ADC_HPF_CUT_WIDTH                     2  /* ADC_HPF_CUT - [6:5] */
#define WM8904_ADC_HPF                          0x0010  /* ADC_HPF */
#define WM8904_ADC_HPF_MASK                     0x0010  /* ADC_HPF */
#define WM8904_ADC_HPF_SHIFT                         4  /* ADC_HPF */
#define WM8904_ADC_HPF_WIDTH                         1  /* ADC_HPF */
#define WM8904_ADCW_DATINV                      0x0002  /* ADCW_DATINV */
#define WM8904_ADCW_DATINV_MASK                 0x0002  /* ADCW_DATINV */
#define WM8904_ADCW_DATINV_SHIFT                     1  /* ADCW_DATINV */
#define WM8904_ADCW_DATINV_WIDTH                     1  /* ADCW_DATINV */
#define WM8904_ADCW_DATINV                      0x0001  /* ADCW_DATINV */
#define WM8904_ADCW_DATINV_MASK                 0x0001  /* ADCW_DATINV */
#define WM8904_ADCW_DATINV_SHIFT                     0  /* ADCW_DATINV */
#define WM8904_ADCW_DATINV_WIDTH                     1  /* ADCW_DATINV */

/*
 * W39 (0x27) - Digitaw Micwophone 0
 */
#define WM8904_DMIC_ENA                         0x1000  /* DMIC_ENA */
#define WM8904_DMIC_ENA_MASK                    0x1000  /* DMIC_ENA */
#define WM8904_DMIC_ENA_SHIFT                       12  /* DMIC_ENA */
#define WM8904_DMIC_ENA_WIDTH                        1  /* DMIC_ENA */
#define WM8904_DMIC_SWC                         0x0800  /* DMIC_SWC */
#define WM8904_DMIC_SWC_MASK                    0x0800  /* DMIC_SWC */
#define WM8904_DMIC_SWC_SHIFT                       11  /* DMIC_SWC */
#define WM8904_DMIC_SWC_WIDTH                        1  /* DMIC_SWC */

/*
 * W40 (0x28) - DWC 0
 */
#define WM8904_DWC_ENA                          0x8000  /* DWC_ENA */
#define WM8904_DWC_ENA_MASK                     0x8000  /* DWC_ENA */
#define WM8904_DWC_ENA_SHIFT                        15  /* DWC_ENA */
#define WM8904_DWC_ENA_WIDTH                         1  /* DWC_ENA */
#define WM8904_DWC_DAC_PATH                     0x4000  /* DWC_DAC_PATH */
#define WM8904_DWC_DAC_PATH_MASK                0x4000  /* DWC_DAC_PATH */
#define WM8904_DWC_DAC_PATH_SHIFT                   14  /* DWC_DAC_PATH */
#define WM8904_DWC_DAC_PATH_WIDTH                    1  /* DWC_DAC_PATH */
#define WM8904_DWC_GS_HYST_WVW_MASK             0x1800  /* DWC_GS_HYST_WVW - [12:11] */
#define WM8904_DWC_GS_HYST_WVW_SHIFT                11  /* DWC_GS_HYST_WVW - [12:11] */
#define WM8904_DWC_GS_HYST_WVW_WIDTH                 2  /* DWC_GS_HYST_WVW - [12:11] */
#define WM8904_DWC_STAWTUP_GAIN_MASK            0x07C0  /* DWC_STAWTUP_GAIN - [10:6] */
#define WM8904_DWC_STAWTUP_GAIN_SHIFT                6  /* DWC_STAWTUP_GAIN - [10:6] */
#define WM8904_DWC_STAWTUP_GAIN_WIDTH                5  /* DWC_STAWTUP_GAIN - [10:6] */
#define WM8904_DWC_FF_DEWAY                     0x0020  /* DWC_FF_DEWAY */
#define WM8904_DWC_FF_DEWAY_MASK                0x0020  /* DWC_FF_DEWAY */
#define WM8904_DWC_FF_DEWAY_SHIFT                    5  /* DWC_FF_DEWAY */
#define WM8904_DWC_FF_DEWAY_WIDTH                    1  /* DWC_FF_DEWAY */
#define WM8904_DWC_GS_ENA                       0x0008  /* DWC_GS_ENA */
#define WM8904_DWC_GS_ENA_MASK                  0x0008  /* DWC_GS_ENA */
#define WM8904_DWC_GS_ENA_SHIFT                      3  /* DWC_GS_ENA */
#define WM8904_DWC_GS_ENA_WIDTH                      1  /* DWC_GS_ENA */
#define WM8904_DWC_QW                           0x0004  /* DWC_QW */
#define WM8904_DWC_QW_MASK                      0x0004  /* DWC_QW */
#define WM8904_DWC_QW_SHIFT                          2  /* DWC_QW */
#define WM8904_DWC_QW_WIDTH                          1  /* DWC_QW */
#define WM8904_DWC_ANTICWIP                     0x0002  /* DWC_ANTICWIP */
#define WM8904_DWC_ANTICWIP_MASK                0x0002  /* DWC_ANTICWIP */
#define WM8904_DWC_ANTICWIP_SHIFT                    1  /* DWC_ANTICWIP */
#define WM8904_DWC_ANTICWIP_WIDTH                    1  /* DWC_ANTICWIP */
#define WM8904_DWC_GS_HYST                      0x0001  /* DWC_GS_HYST */
#define WM8904_DWC_GS_HYST_MASK                 0x0001  /* DWC_GS_HYST */
#define WM8904_DWC_GS_HYST_SHIFT                     0  /* DWC_GS_HYST */
#define WM8904_DWC_GS_HYST_WIDTH                     1  /* DWC_GS_HYST */

/*
 * W41 (0x29) - DWC 1
 */
#define WM8904_DWC_ATK_MASK                     0xF000  /* DWC_ATK - [15:12] */
#define WM8904_DWC_ATK_SHIFT                        12  /* DWC_ATK - [15:12] */
#define WM8904_DWC_ATK_WIDTH                         4  /* DWC_ATK - [15:12] */
#define WM8904_DWC_DCY_MASK                     0x0F00  /* DWC_DCY - [11:8] */
#define WM8904_DWC_DCY_SHIFT                         8  /* DWC_DCY - [11:8] */
#define WM8904_DWC_DCY_WIDTH                         4  /* DWC_DCY - [11:8] */
#define WM8904_DWC_QW_THW_MASK                  0x00C0  /* DWC_QW_THW - [7:6] */
#define WM8904_DWC_QW_THW_SHIFT                      6  /* DWC_QW_THW - [7:6] */
#define WM8904_DWC_QW_THW_WIDTH                      2  /* DWC_QW_THW - [7:6] */
#define WM8904_DWC_QW_DCY_MASK                  0x0030  /* DWC_QW_DCY - [5:4] */
#define WM8904_DWC_QW_DCY_SHIFT                      4  /* DWC_QW_DCY - [5:4] */
#define WM8904_DWC_QW_DCY_WIDTH                      2  /* DWC_QW_DCY - [5:4] */
#define WM8904_DWC_MINGAIN_MASK                 0x000C  /* DWC_MINGAIN - [3:2] */
#define WM8904_DWC_MINGAIN_SHIFT                     2  /* DWC_MINGAIN - [3:2] */
#define WM8904_DWC_MINGAIN_WIDTH                     2  /* DWC_MINGAIN - [3:2] */
#define WM8904_DWC_MAXGAIN_MASK                 0x0003  /* DWC_MAXGAIN - [1:0] */
#define WM8904_DWC_MAXGAIN_SHIFT                     0  /* DWC_MAXGAIN - [1:0] */
#define WM8904_DWC_MAXGAIN_WIDTH                     2  /* DWC_MAXGAIN - [1:0] */

/*
 * W42 (0x2A) - DWC 2
 */
#define WM8904_DWC_HI_COMP_MASK                 0x0038  /* DWC_HI_COMP - [5:3] */
#define WM8904_DWC_HI_COMP_SHIFT                     3  /* DWC_HI_COMP - [5:3] */
#define WM8904_DWC_HI_COMP_WIDTH                     3  /* DWC_HI_COMP - [5:3] */
#define WM8904_DWC_WO_COMP_MASK                 0x0007  /* DWC_WO_COMP - [2:0] */
#define WM8904_DWC_WO_COMP_SHIFT                     0  /* DWC_WO_COMP - [2:0] */
#define WM8904_DWC_WO_COMP_WIDTH                     3  /* DWC_WO_COMP - [2:0] */

/*
 * W43 (0x2B) - DWC 3
 */
#define WM8904_DWC_KNEE_IP_MASK                 0x07E0  /* DWC_KNEE_IP - [10:5] */
#define WM8904_DWC_KNEE_IP_SHIFT                     5  /* DWC_KNEE_IP - [10:5] */
#define WM8904_DWC_KNEE_IP_WIDTH                     6  /* DWC_KNEE_IP - [10:5] */
#define WM8904_DWC_KNEE_OP_MASK                 0x001F  /* DWC_KNEE_OP - [4:0] */
#define WM8904_DWC_KNEE_OP_SHIFT                     0  /* DWC_KNEE_OP - [4:0] */
#define WM8904_DWC_KNEE_OP_WIDTH                     5  /* DWC_KNEE_OP - [4:0] */

/*
 * W44 (0x2C) - Anawogue Weft Input 0
 */
#define WM8904_WINMUTE                          0x0080  /* WINMUTE */
#define WM8904_WINMUTE_MASK                     0x0080  /* WINMUTE */
#define WM8904_WINMUTE_SHIFT                         7  /* WINMUTE */
#define WM8904_WINMUTE_WIDTH                         1  /* WINMUTE */
#define WM8904_WIN_VOW_MASK                     0x001F  /* WIN_VOW - [4:0] */
#define WM8904_WIN_VOW_SHIFT                         0  /* WIN_VOW - [4:0] */
#define WM8904_WIN_VOW_WIDTH                         5  /* WIN_VOW - [4:0] */

/*
 * W45 (0x2D) - Anawogue Wight Input 0
 */
#define WM8904_WINMUTE                          0x0080  /* WINMUTE */
#define WM8904_WINMUTE_MASK                     0x0080  /* WINMUTE */
#define WM8904_WINMUTE_SHIFT                         7  /* WINMUTE */
#define WM8904_WINMUTE_WIDTH                         1  /* WINMUTE */
#define WM8904_WIN_VOW_MASK                     0x001F  /* WIN_VOW - [4:0] */
#define WM8904_WIN_VOW_SHIFT                         0  /* WIN_VOW - [4:0] */
#define WM8904_WIN_VOW_WIDTH                         5  /* WIN_VOW - [4:0] */

/*
 * W46 (0x2E) - Anawogue Weft Input 1
 */
#define WM8904_INW_CM_ENA                       0x0040  /* INW_CM_ENA */
#define WM8904_INW_CM_ENA_MASK                  0x0040  /* INW_CM_ENA */
#define WM8904_INW_CM_ENA_SHIFT                      6  /* INW_CM_ENA */
#define WM8904_INW_CM_ENA_WIDTH                      1  /* INW_CM_ENA */
#define WM8904_W_IP_SEW_N_MASK                  0x0030  /* W_IP_SEW_N - [5:4] */
#define WM8904_W_IP_SEW_N_SHIFT                      4  /* W_IP_SEW_N - [5:4] */
#define WM8904_W_IP_SEW_N_WIDTH                      2  /* W_IP_SEW_N - [5:4] */
#define WM8904_W_IP_SEW_P_MASK                  0x000C  /* W_IP_SEW_P - [3:2] */
#define WM8904_W_IP_SEW_P_SHIFT                      2  /* W_IP_SEW_P - [3:2] */
#define WM8904_W_IP_SEW_P_WIDTH                      2  /* W_IP_SEW_P - [3:2] */
#define WM8904_W_MODE_MASK                      0x0003  /* W_MODE - [1:0] */
#define WM8904_W_MODE_SHIFT                          0  /* W_MODE - [1:0] */
#define WM8904_W_MODE_WIDTH                          2  /* W_MODE - [1:0] */

/*
 * W47 (0x2F) - Anawogue Wight Input 1
 */
#define WM8904_INW_CM_ENA                       0x0040  /* INW_CM_ENA */
#define WM8904_INW_CM_ENA_MASK                  0x0040  /* INW_CM_ENA */
#define WM8904_INW_CM_ENA_SHIFT                      6  /* INW_CM_ENA */
#define WM8904_INW_CM_ENA_WIDTH                      1  /* INW_CM_ENA */
#define WM8904_W_IP_SEW_N_MASK                  0x0030  /* W_IP_SEW_N - [5:4] */
#define WM8904_W_IP_SEW_N_SHIFT                      4  /* W_IP_SEW_N - [5:4] */
#define WM8904_W_IP_SEW_N_WIDTH                      2  /* W_IP_SEW_N - [5:4] */
#define WM8904_W_IP_SEW_P_MASK                  0x000C  /* W_IP_SEW_P - [3:2] */
#define WM8904_W_IP_SEW_P_SHIFT                      2  /* W_IP_SEW_P - [3:2] */
#define WM8904_W_IP_SEW_P_WIDTH                      2  /* W_IP_SEW_P - [3:2] */
#define WM8904_W_MODE_MASK                      0x0003  /* W_MODE - [1:0] */
#define WM8904_W_MODE_SHIFT                          0  /* W_MODE - [1:0] */
#define WM8904_W_MODE_WIDTH                          2  /* W_MODE - [1:0] */

/*
 * W57 (0x39) - Anawogue OUT1 Weft
 */
#define WM8904_HPOUTW_MUTE                      0x0100  /* HPOUTW_MUTE */
#define WM8904_HPOUTW_MUTE_MASK                 0x0100  /* HPOUTW_MUTE */
#define WM8904_HPOUTW_MUTE_SHIFT                     8  /* HPOUTW_MUTE */
#define WM8904_HPOUTW_MUTE_WIDTH                     1  /* HPOUTW_MUTE */
#define WM8904_HPOUT_VU                         0x0080  /* HPOUT_VU */
#define WM8904_HPOUT_VU_MASK                    0x0080  /* HPOUT_VU */
#define WM8904_HPOUT_VU_SHIFT                        7  /* HPOUT_VU */
#define WM8904_HPOUT_VU_WIDTH                        1  /* HPOUT_VU */
#define WM8904_HPOUTWZC                         0x0040  /* HPOUTWZC */
#define WM8904_HPOUTWZC_MASK                    0x0040  /* HPOUTWZC */
#define WM8904_HPOUTWZC_SHIFT                        6  /* HPOUTWZC */
#define WM8904_HPOUTWZC_WIDTH                        1  /* HPOUTWZC */
#define WM8904_HPOUTW_VOW_MASK                  0x003F  /* HPOUTW_VOW - [5:0] */
#define WM8904_HPOUTW_VOW_SHIFT                      0  /* HPOUTW_VOW - [5:0] */
#define WM8904_HPOUTW_VOW_WIDTH                      6  /* HPOUTW_VOW - [5:0] */

/*
 * W58 (0x3A) - Anawogue OUT1 Wight
 */
#define WM8904_HPOUTW_MUTE                      0x0100  /* HPOUTW_MUTE */
#define WM8904_HPOUTW_MUTE_MASK                 0x0100  /* HPOUTW_MUTE */
#define WM8904_HPOUTW_MUTE_SHIFT                     8  /* HPOUTW_MUTE */
#define WM8904_HPOUTW_MUTE_WIDTH                     1  /* HPOUTW_MUTE */
#define WM8904_HPOUT_VU                         0x0080  /* HPOUT_VU */
#define WM8904_HPOUT_VU_MASK                    0x0080  /* HPOUT_VU */
#define WM8904_HPOUT_VU_SHIFT                        7  /* HPOUT_VU */
#define WM8904_HPOUT_VU_WIDTH                        1  /* HPOUT_VU */
#define WM8904_HPOUTWZC                         0x0040  /* HPOUTWZC */
#define WM8904_HPOUTWZC_MASK                    0x0040  /* HPOUTWZC */
#define WM8904_HPOUTWZC_SHIFT                        6  /* HPOUTWZC */
#define WM8904_HPOUTWZC_WIDTH                        1  /* HPOUTWZC */
#define WM8904_HPOUTW_VOW_MASK                  0x003F  /* HPOUTW_VOW - [5:0] */
#define WM8904_HPOUTW_VOW_SHIFT                      0  /* HPOUTW_VOW - [5:0] */
#define WM8904_HPOUTW_VOW_WIDTH                      6  /* HPOUTW_VOW - [5:0] */

/*
 * W59 (0x3B) - Anawogue OUT2 Weft
 */
#define WM8904_WINEOUTW_MUTE                    0x0100  /* WINEOUTW_MUTE */
#define WM8904_WINEOUTW_MUTE_MASK               0x0100  /* WINEOUTW_MUTE */
#define WM8904_WINEOUTW_MUTE_SHIFT                   8  /* WINEOUTW_MUTE */
#define WM8904_WINEOUTW_MUTE_WIDTH                   1  /* WINEOUTW_MUTE */
#define WM8904_WINEOUT_VU                       0x0080  /* WINEOUT_VU */
#define WM8904_WINEOUT_VU_MASK                  0x0080  /* WINEOUT_VU */
#define WM8904_WINEOUT_VU_SHIFT                      7  /* WINEOUT_VU */
#define WM8904_WINEOUT_VU_WIDTH                      1  /* WINEOUT_VU */
#define WM8904_WINEOUTWZC                       0x0040  /* WINEOUTWZC */
#define WM8904_WINEOUTWZC_MASK                  0x0040  /* WINEOUTWZC */
#define WM8904_WINEOUTWZC_SHIFT                      6  /* WINEOUTWZC */
#define WM8904_WINEOUTWZC_WIDTH                      1  /* WINEOUTWZC */
#define WM8904_WINEOUTW_VOW_MASK                0x003F  /* WINEOUTW_VOW - [5:0] */
#define WM8904_WINEOUTW_VOW_SHIFT                    0  /* WINEOUTW_VOW - [5:0] */
#define WM8904_WINEOUTW_VOW_WIDTH                    6  /* WINEOUTW_VOW - [5:0] */

/*
 * W60 (0x3C) - Anawogue OUT2 Wight
 */
#define WM8904_WINEOUTW_MUTE                    0x0100  /* WINEOUTW_MUTE */
#define WM8904_WINEOUTW_MUTE_MASK               0x0100  /* WINEOUTW_MUTE */
#define WM8904_WINEOUTW_MUTE_SHIFT                   8  /* WINEOUTW_MUTE */
#define WM8904_WINEOUTW_MUTE_WIDTH                   1  /* WINEOUTW_MUTE */
#define WM8904_WINEOUT_VU                       0x0080  /* WINEOUT_VU */
#define WM8904_WINEOUT_VU_MASK                  0x0080  /* WINEOUT_VU */
#define WM8904_WINEOUT_VU_SHIFT                      7  /* WINEOUT_VU */
#define WM8904_WINEOUT_VU_WIDTH                      1  /* WINEOUT_VU */
#define WM8904_WINEOUTWZC                       0x0040  /* WINEOUTWZC */
#define WM8904_WINEOUTWZC_MASK                  0x0040  /* WINEOUTWZC */
#define WM8904_WINEOUTWZC_SHIFT                      6  /* WINEOUTWZC */
#define WM8904_WINEOUTWZC_WIDTH                      1  /* WINEOUTWZC */
#define WM8904_WINEOUTW_VOW_MASK                0x003F  /* WINEOUTW_VOW - [5:0] */
#define WM8904_WINEOUTW_VOW_SHIFT                    0  /* WINEOUTW_VOW - [5:0] */
#define WM8904_WINEOUTW_VOW_WIDTH                    6  /* WINEOUTW_VOW - [5:0] */

/*
 * W61 (0x3D) - Anawogue OUT12 ZC
 */
#define WM8904_HPW_BYP_ENA                      0x0008  /* HPW_BYP_ENA */
#define WM8904_HPW_BYP_ENA_MASK                 0x0008  /* HPW_BYP_ENA */
#define WM8904_HPW_BYP_ENA_SHIFT                     3  /* HPW_BYP_ENA */
#define WM8904_HPW_BYP_ENA_WIDTH                     1  /* HPW_BYP_ENA */
#define WM8904_HPW_BYP_ENA                      0x0004  /* HPW_BYP_ENA */
#define WM8904_HPW_BYP_ENA_MASK                 0x0004  /* HPW_BYP_ENA */
#define WM8904_HPW_BYP_ENA_SHIFT                     2  /* HPW_BYP_ENA */
#define WM8904_HPW_BYP_ENA_WIDTH                     1  /* HPW_BYP_ENA */
#define WM8904_WINEOUTW_BYP_ENA                 0x0002  /* WINEOUTW_BYP_ENA */
#define WM8904_WINEOUTW_BYP_ENA_MASK            0x0002  /* WINEOUTW_BYP_ENA */
#define WM8904_WINEOUTW_BYP_ENA_SHIFT                1  /* WINEOUTW_BYP_ENA */
#define WM8904_WINEOUTW_BYP_ENA_WIDTH                1  /* WINEOUTW_BYP_ENA */
#define WM8904_WINEOUTW_BYP_ENA                 0x0001  /* WINEOUTW_BYP_ENA */
#define WM8904_WINEOUTW_BYP_ENA_MASK            0x0001  /* WINEOUTW_BYP_ENA */
#define WM8904_WINEOUTW_BYP_ENA_SHIFT                0  /* WINEOUTW_BYP_ENA */
#define WM8904_WINEOUTW_BYP_ENA_WIDTH                1  /* WINEOUTW_BYP_ENA */

/*
 * W67 (0x43) - DC Sewvo 0
 */
#define WM8904_DCS_ENA_CHAN_3                   0x0008  /* DCS_ENA_CHAN_3 */
#define WM8904_DCS_ENA_CHAN_3_MASK              0x0008  /* DCS_ENA_CHAN_3 */
#define WM8904_DCS_ENA_CHAN_3_SHIFT                  3  /* DCS_ENA_CHAN_3 */
#define WM8904_DCS_ENA_CHAN_3_WIDTH                  1  /* DCS_ENA_CHAN_3 */
#define WM8904_DCS_ENA_CHAN_2                   0x0004  /* DCS_ENA_CHAN_2 */
#define WM8904_DCS_ENA_CHAN_2_MASK              0x0004  /* DCS_ENA_CHAN_2 */
#define WM8904_DCS_ENA_CHAN_2_SHIFT                  2  /* DCS_ENA_CHAN_2 */
#define WM8904_DCS_ENA_CHAN_2_WIDTH                  1  /* DCS_ENA_CHAN_2 */
#define WM8904_DCS_ENA_CHAN_1                   0x0002  /* DCS_ENA_CHAN_1 */
#define WM8904_DCS_ENA_CHAN_1_MASK              0x0002  /* DCS_ENA_CHAN_1 */
#define WM8904_DCS_ENA_CHAN_1_SHIFT                  1  /* DCS_ENA_CHAN_1 */
#define WM8904_DCS_ENA_CHAN_1_WIDTH                  1  /* DCS_ENA_CHAN_1 */
#define WM8904_DCS_ENA_CHAN_0                   0x0001  /* DCS_ENA_CHAN_0 */
#define WM8904_DCS_ENA_CHAN_0_MASK              0x0001  /* DCS_ENA_CHAN_0 */
#define WM8904_DCS_ENA_CHAN_0_SHIFT                  0  /* DCS_ENA_CHAN_0 */
#define WM8904_DCS_ENA_CHAN_0_WIDTH                  1  /* DCS_ENA_CHAN_0 */

/*
 * W68 (0x44) - DC Sewvo 1
 */
#define WM8904_DCS_TWIG_SINGWE_3                0x8000  /* DCS_TWIG_SINGWE_3 */
#define WM8904_DCS_TWIG_SINGWE_3_MASK           0x8000  /* DCS_TWIG_SINGWE_3 */
#define WM8904_DCS_TWIG_SINGWE_3_SHIFT              15  /* DCS_TWIG_SINGWE_3 */
#define WM8904_DCS_TWIG_SINGWE_3_WIDTH               1  /* DCS_TWIG_SINGWE_3 */
#define WM8904_DCS_TWIG_SINGWE_2                0x4000  /* DCS_TWIG_SINGWE_2 */
#define WM8904_DCS_TWIG_SINGWE_2_MASK           0x4000  /* DCS_TWIG_SINGWE_2 */
#define WM8904_DCS_TWIG_SINGWE_2_SHIFT              14  /* DCS_TWIG_SINGWE_2 */
#define WM8904_DCS_TWIG_SINGWE_2_WIDTH               1  /* DCS_TWIG_SINGWE_2 */
#define WM8904_DCS_TWIG_SINGWE_1                0x2000  /* DCS_TWIG_SINGWE_1 */
#define WM8904_DCS_TWIG_SINGWE_1_MASK           0x2000  /* DCS_TWIG_SINGWE_1 */
#define WM8904_DCS_TWIG_SINGWE_1_SHIFT              13  /* DCS_TWIG_SINGWE_1 */
#define WM8904_DCS_TWIG_SINGWE_1_WIDTH               1  /* DCS_TWIG_SINGWE_1 */
#define WM8904_DCS_TWIG_SINGWE_0                0x1000  /* DCS_TWIG_SINGWE_0 */
#define WM8904_DCS_TWIG_SINGWE_0_MASK           0x1000  /* DCS_TWIG_SINGWE_0 */
#define WM8904_DCS_TWIG_SINGWE_0_SHIFT              12  /* DCS_TWIG_SINGWE_0 */
#define WM8904_DCS_TWIG_SINGWE_0_WIDTH               1  /* DCS_TWIG_SINGWE_0 */
#define WM8904_DCS_TWIG_SEWIES_3                0x0800  /* DCS_TWIG_SEWIES_3 */
#define WM8904_DCS_TWIG_SEWIES_3_MASK           0x0800  /* DCS_TWIG_SEWIES_3 */
#define WM8904_DCS_TWIG_SEWIES_3_SHIFT              11  /* DCS_TWIG_SEWIES_3 */
#define WM8904_DCS_TWIG_SEWIES_3_WIDTH               1  /* DCS_TWIG_SEWIES_3 */
#define WM8904_DCS_TWIG_SEWIES_2                0x0400  /* DCS_TWIG_SEWIES_2 */
#define WM8904_DCS_TWIG_SEWIES_2_MASK           0x0400  /* DCS_TWIG_SEWIES_2 */
#define WM8904_DCS_TWIG_SEWIES_2_SHIFT              10  /* DCS_TWIG_SEWIES_2 */
#define WM8904_DCS_TWIG_SEWIES_2_WIDTH               1  /* DCS_TWIG_SEWIES_2 */
#define WM8904_DCS_TWIG_SEWIES_1                0x0200  /* DCS_TWIG_SEWIES_1 */
#define WM8904_DCS_TWIG_SEWIES_1_MASK           0x0200  /* DCS_TWIG_SEWIES_1 */
#define WM8904_DCS_TWIG_SEWIES_1_SHIFT               9  /* DCS_TWIG_SEWIES_1 */
#define WM8904_DCS_TWIG_SEWIES_1_WIDTH               1  /* DCS_TWIG_SEWIES_1 */
#define WM8904_DCS_TWIG_SEWIES_0                0x0100  /* DCS_TWIG_SEWIES_0 */
#define WM8904_DCS_TWIG_SEWIES_0_MASK           0x0100  /* DCS_TWIG_SEWIES_0 */
#define WM8904_DCS_TWIG_SEWIES_0_SHIFT               8  /* DCS_TWIG_SEWIES_0 */
#define WM8904_DCS_TWIG_SEWIES_0_WIDTH               1  /* DCS_TWIG_SEWIES_0 */
#define WM8904_DCS_TWIG_STAWTUP_3               0x0080  /* DCS_TWIG_STAWTUP_3 */
#define WM8904_DCS_TWIG_STAWTUP_3_MASK          0x0080  /* DCS_TWIG_STAWTUP_3 */
#define WM8904_DCS_TWIG_STAWTUP_3_SHIFT              7  /* DCS_TWIG_STAWTUP_3 */
#define WM8904_DCS_TWIG_STAWTUP_3_WIDTH              1  /* DCS_TWIG_STAWTUP_3 */
#define WM8904_DCS_TWIG_STAWTUP_2               0x0040  /* DCS_TWIG_STAWTUP_2 */
#define WM8904_DCS_TWIG_STAWTUP_2_MASK          0x0040  /* DCS_TWIG_STAWTUP_2 */
#define WM8904_DCS_TWIG_STAWTUP_2_SHIFT              6  /* DCS_TWIG_STAWTUP_2 */
#define WM8904_DCS_TWIG_STAWTUP_2_WIDTH              1  /* DCS_TWIG_STAWTUP_2 */
#define WM8904_DCS_TWIG_STAWTUP_1               0x0020  /* DCS_TWIG_STAWTUP_1 */
#define WM8904_DCS_TWIG_STAWTUP_1_MASK          0x0020  /* DCS_TWIG_STAWTUP_1 */
#define WM8904_DCS_TWIG_STAWTUP_1_SHIFT              5  /* DCS_TWIG_STAWTUP_1 */
#define WM8904_DCS_TWIG_STAWTUP_1_WIDTH              1  /* DCS_TWIG_STAWTUP_1 */
#define WM8904_DCS_TWIG_STAWTUP_0               0x0010  /* DCS_TWIG_STAWTUP_0 */
#define WM8904_DCS_TWIG_STAWTUP_0_MASK          0x0010  /* DCS_TWIG_STAWTUP_0 */
#define WM8904_DCS_TWIG_STAWTUP_0_SHIFT              4  /* DCS_TWIG_STAWTUP_0 */
#define WM8904_DCS_TWIG_STAWTUP_0_WIDTH              1  /* DCS_TWIG_STAWTUP_0 */
#define WM8904_DCS_TWIG_DAC_WW_3                0x0008  /* DCS_TWIG_DAC_WW_3 */
#define WM8904_DCS_TWIG_DAC_WW_3_MASK           0x0008  /* DCS_TWIG_DAC_WW_3 */
#define WM8904_DCS_TWIG_DAC_WW_3_SHIFT               3  /* DCS_TWIG_DAC_WW_3 */
#define WM8904_DCS_TWIG_DAC_WW_3_WIDTH               1  /* DCS_TWIG_DAC_WW_3 */
#define WM8904_DCS_TWIG_DAC_WW_2                0x0004  /* DCS_TWIG_DAC_WW_2 */
#define WM8904_DCS_TWIG_DAC_WW_2_MASK           0x0004  /* DCS_TWIG_DAC_WW_2 */
#define WM8904_DCS_TWIG_DAC_WW_2_SHIFT               2  /* DCS_TWIG_DAC_WW_2 */
#define WM8904_DCS_TWIG_DAC_WW_2_WIDTH               1  /* DCS_TWIG_DAC_WW_2 */
#define WM8904_DCS_TWIG_DAC_WW_1                0x0002  /* DCS_TWIG_DAC_WW_1 */
#define WM8904_DCS_TWIG_DAC_WW_1_MASK           0x0002  /* DCS_TWIG_DAC_WW_1 */
#define WM8904_DCS_TWIG_DAC_WW_1_SHIFT               1  /* DCS_TWIG_DAC_WW_1 */
#define WM8904_DCS_TWIG_DAC_WW_1_WIDTH               1  /* DCS_TWIG_DAC_WW_1 */
#define WM8904_DCS_TWIG_DAC_WW_0                0x0001  /* DCS_TWIG_DAC_WW_0 */
#define WM8904_DCS_TWIG_DAC_WW_0_MASK           0x0001  /* DCS_TWIG_DAC_WW_0 */
#define WM8904_DCS_TWIG_DAC_WW_0_SHIFT               0  /* DCS_TWIG_DAC_WW_0 */
#define WM8904_DCS_TWIG_DAC_WW_0_WIDTH               1  /* DCS_TWIG_DAC_WW_0 */

/*
 * W69 (0x45) - DC Sewvo 2
 */
#define WM8904_DCS_TIMEW_PEWIOD_23_MASK         0x0F00  /* DCS_TIMEW_PEWIOD_23 - [11:8] */
#define WM8904_DCS_TIMEW_PEWIOD_23_SHIFT             8  /* DCS_TIMEW_PEWIOD_23 - [11:8] */
#define WM8904_DCS_TIMEW_PEWIOD_23_WIDTH             4  /* DCS_TIMEW_PEWIOD_23 - [11:8] */
#define WM8904_DCS_TIMEW_PEWIOD_01_MASK         0x000F  /* DCS_TIMEW_PEWIOD_01 - [3:0] */
#define WM8904_DCS_TIMEW_PEWIOD_01_SHIFT             0  /* DCS_TIMEW_PEWIOD_01 - [3:0] */
#define WM8904_DCS_TIMEW_PEWIOD_01_WIDTH             4  /* DCS_TIMEW_PEWIOD_01 - [3:0] */

/*
 * W71 (0x47) - DC Sewvo 4
 */
#define WM8904_DCS_SEWIES_NO_23_MASK            0x007F  /* DCS_SEWIES_NO_23 - [6:0] */
#define WM8904_DCS_SEWIES_NO_23_SHIFT                0  /* DCS_SEWIES_NO_23 - [6:0] */
#define WM8904_DCS_SEWIES_NO_23_WIDTH                7  /* DCS_SEWIES_NO_23 - [6:0] */

/*
 * W72 (0x48) - DC Sewvo 5
 */
#define WM8904_DCS_SEWIES_NO_01_MASK            0x007F  /* DCS_SEWIES_NO_01 - [6:0] */
#define WM8904_DCS_SEWIES_NO_01_SHIFT                0  /* DCS_SEWIES_NO_01 - [6:0] */
#define WM8904_DCS_SEWIES_NO_01_WIDTH                7  /* DCS_SEWIES_NO_01 - [6:0] */

/*
 * W73 (0x49) - DC Sewvo 6
 */
#define WM8904_DCS_DAC_WW_VAW_3_MASK            0x00FF  /* DCS_DAC_WW_VAW_3 - [7:0] */
#define WM8904_DCS_DAC_WW_VAW_3_SHIFT                0  /* DCS_DAC_WW_VAW_3 - [7:0] */
#define WM8904_DCS_DAC_WW_VAW_3_WIDTH                8  /* DCS_DAC_WW_VAW_3 - [7:0] */

/*
 * W74 (0x4A) - DC Sewvo 7
 */
#define WM8904_DCS_DAC_WW_VAW_2_MASK            0x00FF  /* DCS_DAC_WW_VAW_2 - [7:0] */
#define WM8904_DCS_DAC_WW_VAW_2_SHIFT                0  /* DCS_DAC_WW_VAW_2 - [7:0] */
#define WM8904_DCS_DAC_WW_VAW_2_WIDTH                8  /* DCS_DAC_WW_VAW_2 - [7:0] */

/*
 * W75 (0x4B) - DC Sewvo 8
 */
#define WM8904_DCS_DAC_WW_VAW_1_MASK            0x00FF  /* DCS_DAC_WW_VAW_1 - [7:0] */
#define WM8904_DCS_DAC_WW_VAW_1_SHIFT                0  /* DCS_DAC_WW_VAW_1 - [7:0] */
#define WM8904_DCS_DAC_WW_VAW_1_WIDTH                8  /* DCS_DAC_WW_VAW_1 - [7:0] */

/*
 * W76 (0x4C) - DC Sewvo 9
 */
#define WM8904_DCS_DAC_WW_VAW_0_MASK            0x00FF  /* DCS_DAC_WW_VAW_0 - [7:0] */
#define WM8904_DCS_DAC_WW_VAW_0_SHIFT                0  /* DCS_DAC_WW_VAW_0 - [7:0] */
#define WM8904_DCS_DAC_WW_VAW_0_WIDTH                8  /* DCS_DAC_WW_VAW_0 - [7:0] */

/*
 * W77 (0x4D) - DC Sewvo Weadback 0
 */
#define WM8904_DCS_CAW_COMPWETE_MASK            0x0F00  /* DCS_CAW_COMPWETE - [11:8] */
#define WM8904_DCS_CAW_COMPWETE_SHIFT                8  /* DCS_CAW_COMPWETE - [11:8] */
#define WM8904_DCS_CAW_COMPWETE_WIDTH                4  /* DCS_CAW_COMPWETE - [11:8] */
#define WM8904_DCS_DAC_WW_COMPWETE_MASK         0x00F0  /* DCS_DAC_WW_COMPWETE - [7:4] */
#define WM8904_DCS_DAC_WW_COMPWETE_SHIFT             4  /* DCS_DAC_WW_COMPWETE - [7:4] */
#define WM8904_DCS_DAC_WW_COMPWETE_WIDTH             4  /* DCS_DAC_WW_COMPWETE - [7:4] */
#define WM8904_DCS_STAWTUP_COMPWETE_MASK        0x000F  /* DCS_STAWTUP_COMPWETE - [3:0] */
#define WM8904_DCS_STAWTUP_COMPWETE_SHIFT            0  /* DCS_STAWTUP_COMPWETE - [3:0] */
#define WM8904_DCS_STAWTUP_COMPWETE_WIDTH            4  /* DCS_STAWTUP_COMPWETE - [3:0] */

/*
 * W90 (0x5A) - Anawogue HP 0
 */
#define WM8904_HPW_WMV_SHOWT                    0x0080  /* HPW_WMV_SHOWT */
#define WM8904_HPW_WMV_SHOWT_MASK               0x0080  /* HPW_WMV_SHOWT */
#define WM8904_HPW_WMV_SHOWT_SHIFT                   7  /* HPW_WMV_SHOWT */
#define WM8904_HPW_WMV_SHOWT_WIDTH                   1  /* HPW_WMV_SHOWT */
#define WM8904_HPW_ENA_OUTP                     0x0040  /* HPW_ENA_OUTP */
#define WM8904_HPW_ENA_OUTP_MASK                0x0040  /* HPW_ENA_OUTP */
#define WM8904_HPW_ENA_OUTP_SHIFT                    6  /* HPW_ENA_OUTP */
#define WM8904_HPW_ENA_OUTP_WIDTH                    1  /* HPW_ENA_OUTP */
#define WM8904_HPW_ENA_DWY                      0x0020  /* HPW_ENA_DWY */
#define WM8904_HPW_ENA_DWY_MASK                 0x0020  /* HPW_ENA_DWY */
#define WM8904_HPW_ENA_DWY_SHIFT                     5  /* HPW_ENA_DWY */
#define WM8904_HPW_ENA_DWY_WIDTH                     1  /* HPW_ENA_DWY */
#define WM8904_HPW_ENA                          0x0010  /* HPW_ENA */
#define WM8904_HPW_ENA_MASK                     0x0010  /* HPW_ENA */
#define WM8904_HPW_ENA_SHIFT                         4  /* HPW_ENA */
#define WM8904_HPW_ENA_WIDTH                         1  /* HPW_ENA */
#define WM8904_HPW_WMV_SHOWT                    0x0008  /* HPW_WMV_SHOWT */
#define WM8904_HPW_WMV_SHOWT_MASK               0x0008  /* HPW_WMV_SHOWT */
#define WM8904_HPW_WMV_SHOWT_SHIFT                   3  /* HPW_WMV_SHOWT */
#define WM8904_HPW_WMV_SHOWT_WIDTH                   1  /* HPW_WMV_SHOWT */
#define WM8904_HPW_ENA_OUTP                     0x0004  /* HPW_ENA_OUTP */
#define WM8904_HPW_ENA_OUTP_MASK                0x0004  /* HPW_ENA_OUTP */
#define WM8904_HPW_ENA_OUTP_SHIFT                    2  /* HPW_ENA_OUTP */
#define WM8904_HPW_ENA_OUTP_WIDTH                    1  /* HPW_ENA_OUTP */
#define WM8904_HPW_ENA_DWY                      0x0002  /* HPW_ENA_DWY */
#define WM8904_HPW_ENA_DWY_MASK                 0x0002  /* HPW_ENA_DWY */
#define WM8904_HPW_ENA_DWY_SHIFT                     1  /* HPW_ENA_DWY */
#define WM8904_HPW_ENA_DWY_WIDTH                     1  /* HPW_ENA_DWY */
#define WM8904_HPW_ENA                          0x0001  /* HPW_ENA */
#define WM8904_HPW_ENA_MASK                     0x0001  /* HPW_ENA */
#define WM8904_HPW_ENA_SHIFT                         0  /* HPW_ENA */
#define WM8904_HPW_ENA_WIDTH                         1  /* HPW_ENA */

/*
 * W94 (0x5E) - Anawogue Wineout 0
 */
#define WM8904_WINEOUTW_WMV_SHOWT               0x0080  /* WINEOUTW_WMV_SHOWT */
#define WM8904_WINEOUTW_WMV_SHOWT_MASK          0x0080  /* WINEOUTW_WMV_SHOWT */
#define WM8904_WINEOUTW_WMV_SHOWT_SHIFT              7  /* WINEOUTW_WMV_SHOWT */
#define WM8904_WINEOUTW_WMV_SHOWT_WIDTH              1  /* WINEOUTW_WMV_SHOWT */
#define WM8904_WINEOUTW_ENA_OUTP                0x0040  /* WINEOUTW_ENA_OUTP */
#define WM8904_WINEOUTW_ENA_OUTP_MASK           0x0040  /* WINEOUTW_ENA_OUTP */
#define WM8904_WINEOUTW_ENA_OUTP_SHIFT               6  /* WINEOUTW_ENA_OUTP */
#define WM8904_WINEOUTW_ENA_OUTP_WIDTH               1  /* WINEOUTW_ENA_OUTP */
#define WM8904_WINEOUTW_ENA_DWY                 0x0020  /* WINEOUTW_ENA_DWY */
#define WM8904_WINEOUTW_ENA_DWY_MASK            0x0020  /* WINEOUTW_ENA_DWY */
#define WM8904_WINEOUTW_ENA_DWY_SHIFT                5  /* WINEOUTW_ENA_DWY */
#define WM8904_WINEOUTW_ENA_DWY_WIDTH                1  /* WINEOUTW_ENA_DWY */
#define WM8904_WINEOUTW_ENA                     0x0010  /* WINEOUTW_ENA */
#define WM8904_WINEOUTW_ENA_MASK                0x0010  /* WINEOUTW_ENA */
#define WM8904_WINEOUTW_ENA_SHIFT                    4  /* WINEOUTW_ENA */
#define WM8904_WINEOUTW_ENA_WIDTH                    1  /* WINEOUTW_ENA */
#define WM8904_WINEOUTW_WMV_SHOWT               0x0008  /* WINEOUTW_WMV_SHOWT */
#define WM8904_WINEOUTW_WMV_SHOWT_MASK          0x0008  /* WINEOUTW_WMV_SHOWT */
#define WM8904_WINEOUTW_WMV_SHOWT_SHIFT              3  /* WINEOUTW_WMV_SHOWT */
#define WM8904_WINEOUTW_WMV_SHOWT_WIDTH              1  /* WINEOUTW_WMV_SHOWT */
#define WM8904_WINEOUTW_ENA_OUTP                0x0004  /* WINEOUTW_ENA_OUTP */
#define WM8904_WINEOUTW_ENA_OUTP_MASK           0x0004  /* WINEOUTW_ENA_OUTP */
#define WM8904_WINEOUTW_ENA_OUTP_SHIFT               2  /* WINEOUTW_ENA_OUTP */
#define WM8904_WINEOUTW_ENA_OUTP_WIDTH               1  /* WINEOUTW_ENA_OUTP */
#define WM8904_WINEOUTW_ENA_DWY                 0x0002  /* WINEOUTW_ENA_DWY */
#define WM8904_WINEOUTW_ENA_DWY_MASK            0x0002  /* WINEOUTW_ENA_DWY */
#define WM8904_WINEOUTW_ENA_DWY_SHIFT                1  /* WINEOUTW_ENA_DWY */
#define WM8904_WINEOUTW_ENA_DWY_WIDTH                1  /* WINEOUTW_ENA_DWY */
#define WM8904_WINEOUTW_ENA                     0x0001  /* WINEOUTW_ENA */
#define WM8904_WINEOUTW_ENA_MASK                0x0001  /* WINEOUTW_ENA */
#define WM8904_WINEOUTW_ENA_SHIFT                    0  /* WINEOUTW_ENA */
#define WM8904_WINEOUTW_ENA_WIDTH                    1  /* WINEOUTW_ENA */

/*
 * W98 (0x62) - Chawge Pump 0
 */
#define WM8904_CP_ENA                           0x0001  /* CP_ENA */
#define WM8904_CP_ENA_MASK                      0x0001  /* CP_ENA */
#define WM8904_CP_ENA_SHIFT                          0  /* CP_ENA */
#define WM8904_CP_ENA_WIDTH                          1  /* CP_ENA */

/*
 * W104 (0x68) - Cwass W 0
 */
#define WM8904_CP_DYN_PWW                       0x0001  /* CP_DYN_PWW */
#define WM8904_CP_DYN_PWW_MASK                  0x0001  /* CP_DYN_PWW */
#define WM8904_CP_DYN_PWW_SHIFT                      0  /* CP_DYN_PWW */
#define WM8904_CP_DYN_PWW_WIDTH                      1  /* CP_DYN_PWW */

/*
 * W108 (0x6C) - Wwite Sequencew 0
 */
#define WM8904_WSEQ_ENA                         0x0100  /* WSEQ_ENA */
#define WM8904_WSEQ_ENA_MASK                    0x0100  /* WSEQ_ENA */
#define WM8904_WSEQ_ENA_SHIFT                        8  /* WSEQ_ENA */
#define WM8904_WSEQ_ENA_WIDTH                        1  /* WSEQ_ENA */
#define WM8904_WSEQ_WWITE_INDEX_MASK            0x001F  /* WSEQ_WWITE_INDEX - [4:0] */
#define WM8904_WSEQ_WWITE_INDEX_SHIFT                0  /* WSEQ_WWITE_INDEX - [4:0] */
#define WM8904_WSEQ_WWITE_INDEX_WIDTH                5  /* WSEQ_WWITE_INDEX - [4:0] */

/*
 * W109 (0x6D) - Wwite Sequencew 1
 */
#define WM8904_WSEQ_DATA_WIDTH_MASK             0x7000  /* WSEQ_DATA_WIDTH - [14:12] */
#define WM8904_WSEQ_DATA_WIDTH_SHIFT                12  /* WSEQ_DATA_WIDTH - [14:12] */
#define WM8904_WSEQ_DATA_WIDTH_WIDTH                 3  /* WSEQ_DATA_WIDTH - [14:12] */
#define WM8904_WSEQ_DATA_STAWT_MASK             0x0F00  /* WSEQ_DATA_STAWT - [11:8] */
#define WM8904_WSEQ_DATA_STAWT_SHIFT                 8  /* WSEQ_DATA_STAWT - [11:8] */
#define WM8904_WSEQ_DATA_STAWT_WIDTH                 4  /* WSEQ_DATA_STAWT - [11:8] */
#define WM8904_WSEQ_ADDW_MASK                   0x00FF  /* WSEQ_ADDW - [7:0] */
#define WM8904_WSEQ_ADDW_SHIFT                       0  /* WSEQ_ADDW - [7:0] */
#define WM8904_WSEQ_ADDW_WIDTH                       8  /* WSEQ_ADDW - [7:0] */

/*
 * W110 (0x6E) - Wwite Sequencew 2
 */
#define WM8904_WSEQ_EOS                         0x4000  /* WSEQ_EOS */
#define WM8904_WSEQ_EOS_MASK                    0x4000  /* WSEQ_EOS */
#define WM8904_WSEQ_EOS_SHIFT                       14  /* WSEQ_EOS */
#define WM8904_WSEQ_EOS_WIDTH                        1  /* WSEQ_EOS */
#define WM8904_WSEQ_DEWAY_MASK                  0x0F00  /* WSEQ_DEWAY - [11:8] */
#define WM8904_WSEQ_DEWAY_SHIFT                      8  /* WSEQ_DEWAY - [11:8] */
#define WM8904_WSEQ_DEWAY_WIDTH                      4  /* WSEQ_DEWAY - [11:8] */
#define WM8904_WSEQ_DATA_MASK                   0x00FF  /* WSEQ_DATA - [7:0] */
#define WM8904_WSEQ_DATA_SHIFT                       0  /* WSEQ_DATA - [7:0] */
#define WM8904_WSEQ_DATA_WIDTH                       8  /* WSEQ_DATA - [7:0] */

/*
 * W111 (0x6F) - Wwite Sequencew 3
 */
#define WM8904_WSEQ_ABOWT                       0x0200  /* WSEQ_ABOWT */
#define WM8904_WSEQ_ABOWT_MASK                  0x0200  /* WSEQ_ABOWT */
#define WM8904_WSEQ_ABOWT_SHIFT                      9  /* WSEQ_ABOWT */
#define WM8904_WSEQ_ABOWT_WIDTH                      1  /* WSEQ_ABOWT */
#define WM8904_WSEQ_STAWT                       0x0100  /* WSEQ_STAWT */
#define WM8904_WSEQ_STAWT_MASK                  0x0100  /* WSEQ_STAWT */
#define WM8904_WSEQ_STAWT_SHIFT                      8  /* WSEQ_STAWT */
#define WM8904_WSEQ_STAWT_WIDTH                      1  /* WSEQ_STAWT */
#define WM8904_WSEQ_STAWT_INDEX_MASK            0x003F  /* WSEQ_STAWT_INDEX - [5:0] */
#define WM8904_WSEQ_STAWT_INDEX_SHIFT                0  /* WSEQ_STAWT_INDEX - [5:0] */
#define WM8904_WSEQ_STAWT_INDEX_WIDTH                6  /* WSEQ_STAWT_INDEX - [5:0] */

/*
 * W112 (0x70) - Wwite Sequencew 4
 */
#define WM8904_WSEQ_CUWWENT_INDEX_MASK          0x03F0  /* WSEQ_CUWWENT_INDEX - [9:4] */
#define WM8904_WSEQ_CUWWENT_INDEX_SHIFT              4  /* WSEQ_CUWWENT_INDEX - [9:4] */
#define WM8904_WSEQ_CUWWENT_INDEX_WIDTH              6  /* WSEQ_CUWWENT_INDEX - [9:4] */
#define WM8904_WSEQ_BUSY                        0x0001  /* WSEQ_BUSY */
#define WM8904_WSEQ_BUSY_MASK                   0x0001  /* WSEQ_BUSY */
#define WM8904_WSEQ_BUSY_SHIFT                       0  /* WSEQ_BUSY */
#define WM8904_WSEQ_BUSY_WIDTH                       1  /* WSEQ_BUSY */

/*
 * W116 (0x74) - FWW Contwow 1
 */
#define WM8904_FWW_FWACN_ENA                    0x0004  /* FWW_FWACN_ENA */
#define WM8904_FWW_FWACN_ENA_MASK               0x0004  /* FWW_FWACN_ENA */
#define WM8904_FWW_FWACN_ENA_SHIFT                   2  /* FWW_FWACN_ENA */
#define WM8904_FWW_FWACN_ENA_WIDTH                   1  /* FWW_FWACN_ENA */
#define WM8904_FWW_OSC_ENA                      0x0002  /* FWW_OSC_ENA */
#define WM8904_FWW_OSC_ENA_MASK                 0x0002  /* FWW_OSC_ENA */
#define WM8904_FWW_OSC_ENA_SHIFT                     1  /* FWW_OSC_ENA */
#define WM8904_FWW_OSC_ENA_WIDTH                     1  /* FWW_OSC_ENA */
#define WM8904_FWW_ENA                          0x0001  /* FWW_ENA */
#define WM8904_FWW_ENA_MASK                     0x0001  /* FWW_ENA */
#define WM8904_FWW_ENA_SHIFT                         0  /* FWW_ENA */
#define WM8904_FWW_ENA_WIDTH                         1  /* FWW_ENA */

/*
 * W117 (0x75) - FWW Contwow 2
 */
#define WM8904_FWW_OUTDIV_MASK                  0x3F00  /* FWW_OUTDIV - [13:8] */
#define WM8904_FWW_OUTDIV_SHIFT                      8  /* FWW_OUTDIV - [13:8] */
#define WM8904_FWW_OUTDIV_WIDTH                      6  /* FWW_OUTDIV - [13:8] */
#define WM8904_FWW_CTWW_WATE_MASK               0x0070  /* FWW_CTWW_WATE - [6:4] */
#define WM8904_FWW_CTWW_WATE_SHIFT                   4  /* FWW_CTWW_WATE - [6:4] */
#define WM8904_FWW_CTWW_WATE_WIDTH                   3  /* FWW_CTWW_WATE - [6:4] */
#define WM8904_FWW_FWATIO_MASK                  0x0007  /* FWW_FWATIO - [2:0] */
#define WM8904_FWW_FWATIO_SHIFT                      0  /* FWW_FWATIO - [2:0] */
#define WM8904_FWW_FWATIO_WIDTH                      3  /* FWW_FWATIO - [2:0] */

/*
 * W118 (0x76) - FWW Contwow 3
 */
#define WM8904_FWW_K_MASK                       0xFFFF  /* FWW_K - [15:0] */
#define WM8904_FWW_K_SHIFT                           0  /* FWW_K - [15:0] */
#define WM8904_FWW_K_WIDTH                          16  /* FWW_K - [15:0] */

/*
 * W119 (0x77) - FWW Contwow 4
 */
#define WM8904_FWW_N_MASK                       0x7FE0  /* FWW_N - [14:5] */
#define WM8904_FWW_N_SHIFT                           5  /* FWW_N - [14:5] */
#define WM8904_FWW_N_WIDTH                          10  /* FWW_N - [14:5] */
#define WM8904_FWW_GAIN_MASK                    0x000F  /* FWW_GAIN - [3:0] */
#define WM8904_FWW_GAIN_SHIFT                        0  /* FWW_GAIN - [3:0] */
#define WM8904_FWW_GAIN_WIDTH                        4  /* FWW_GAIN - [3:0] */

/*
 * W120 (0x78) - FWW Contwow 5
 */
#define WM8904_FWW_CWK_WEF_DIV_MASK             0x0018  /* FWW_CWK_WEF_DIV - [4:3] */
#define WM8904_FWW_CWK_WEF_DIV_SHIFT                 3  /* FWW_CWK_WEF_DIV - [4:3] */
#define WM8904_FWW_CWK_WEF_DIV_WIDTH                 2  /* FWW_CWK_WEF_DIV - [4:3] */
#define WM8904_FWW_CWK_WEF_SWC_MASK             0x0003  /* FWW_CWK_WEF_SWC - [1:0] */
#define WM8904_FWW_CWK_WEF_SWC_SHIFT                 0  /* FWW_CWK_WEF_SWC - [1:0] */
#define WM8904_FWW_CWK_WEF_SWC_WIDTH                 2  /* FWW_CWK_WEF_SWC - [1:0] */

/*
 * W126 (0x7E) - Digitaw Puwws
 */
#define WM8904_MCWK_PU                          0x0080  /* MCWK_PU */
#define WM8904_MCWK_PU_MASK                     0x0080  /* MCWK_PU */
#define WM8904_MCWK_PU_SHIFT                         7  /* MCWK_PU */
#define WM8904_MCWK_PU_WIDTH                         1  /* MCWK_PU */
#define WM8904_MCWK_PD                          0x0040  /* MCWK_PD */
#define WM8904_MCWK_PD_MASK                     0x0040  /* MCWK_PD */
#define WM8904_MCWK_PD_SHIFT                         6  /* MCWK_PD */
#define WM8904_MCWK_PD_WIDTH                         1  /* MCWK_PD */
#define WM8904_DACDAT_PU                        0x0020  /* DACDAT_PU */
#define WM8904_DACDAT_PU_MASK                   0x0020  /* DACDAT_PU */
#define WM8904_DACDAT_PU_SHIFT                       5  /* DACDAT_PU */
#define WM8904_DACDAT_PU_WIDTH                       1  /* DACDAT_PU */
#define WM8904_DACDAT_PD                        0x0010  /* DACDAT_PD */
#define WM8904_DACDAT_PD_MASK                   0x0010  /* DACDAT_PD */
#define WM8904_DACDAT_PD_SHIFT                       4  /* DACDAT_PD */
#define WM8904_DACDAT_PD_WIDTH                       1  /* DACDAT_PD */
#define WM8904_WWCWK_PU                         0x0008  /* WWCWK_PU */
#define WM8904_WWCWK_PU_MASK                    0x0008  /* WWCWK_PU */
#define WM8904_WWCWK_PU_SHIFT                        3  /* WWCWK_PU */
#define WM8904_WWCWK_PU_WIDTH                        1  /* WWCWK_PU */
#define WM8904_WWCWK_PD                         0x0004  /* WWCWK_PD */
#define WM8904_WWCWK_PD_MASK                    0x0004  /* WWCWK_PD */
#define WM8904_WWCWK_PD_SHIFT                        2  /* WWCWK_PD */
#define WM8904_WWCWK_PD_WIDTH                        1  /* WWCWK_PD */
#define WM8904_BCWK_PU                          0x0002  /* BCWK_PU */
#define WM8904_BCWK_PU_MASK                     0x0002  /* BCWK_PU */
#define WM8904_BCWK_PU_SHIFT                         1  /* BCWK_PU */
#define WM8904_BCWK_PU_WIDTH                         1  /* BCWK_PU */
#define WM8904_BCWK_PD                          0x0001  /* BCWK_PD */
#define WM8904_BCWK_PD_MASK                     0x0001  /* BCWK_PD */
#define WM8904_BCWK_PD_SHIFT                         0  /* BCWK_PD */
#define WM8904_BCWK_PD_WIDTH                         1  /* BCWK_PD */

/*
 * W127 (0x7F) - Intewwupt Status
 */
#define WM8904_IWQ                              0x0400  /* IWQ */
#define WM8904_IWQ_MASK                         0x0400  /* IWQ */
#define WM8904_IWQ_SHIFT                            10  /* IWQ */
#define WM8904_IWQ_WIDTH                             1  /* IWQ */
#define WM8904_GPIO_BCWK_EINT                   0x0200  /* GPIO_BCWK_EINT */
#define WM8904_GPIO_BCWK_EINT_MASK              0x0200  /* GPIO_BCWK_EINT */
#define WM8904_GPIO_BCWK_EINT_SHIFT                  9  /* GPIO_BCWK_EINT */
#define WM8904_GPIO_BCWK_EINT_WIDTH                  1  /* GPIO_BCWK_EINT */
#define WM8904_WSEQ_EINT                        0x0100  /* WSEQ_EINT */
#define WM8904_WSEQ_EINT_MASK                   0x0100  /* WSEQ_EINT */
#define WM8904_WSEQ_EINT_SHIFT                       8  /* WSEQ_EINT */
#define WM8904_WSEQ_EINT_WIDTH                       1  /* WSEQ_EINT */
#define WM8904_GPIO3_EINT                       0x0080  /* GPIO3_EINT */
#define WM8904_GPIO3_EINT_MASK                  0x0080  /* GPIO3_EINT */
#define WM8904_GPIO3_EINT_SHIFT                      7  /* GPIO3_EINT */
#define WM8904_GPIO3_EINT_WIDTH                      1  /* GPIO3_EINT */
#define WM8904_GPIO2_EINT                       0x0040  /* GPIO2_EINT */
#define WM8904_GPIO2_EINT_MASK                  0x0040  /* GPIO2_EINT */
#define WM8904_GPIO2_EINT_SHIFT                      6  /* GPIO2_EINT */
#define WM8904_GPIO2_EINT_WIDTH                      1  /* GPIO2_EINT */
#define WM8904_GPIO1_EINT                       0x0020  /* GPIO1_EINT */
#define WM8904_GPIO1_EINT_MASK                  0x0020  /* GPIO1_EINT */
#define WM8904_GPIO1_EINT_SHIFT                      5  /* GPIO1_EINT */
#define WM8904_GPIO1_EINT_WIDTH                      1  /* GPIO1_EINT */
#define WM8904_GPI8_EINT                        0x0010  /* GPI8_EINT */
#define WM8904_GPI8_EINT_MASK                   0x0010  /* GPI8_EINT */
#define WM8904_GPI8_EINT_SHIFT                       4  /* GPI8_EINT */
#define WM8904_GPI8_EINT_WIDTH                       1  /* GPI8_EINT */
#define WM8904_GPI7_EINT                        0x0008  /* GPI7_EINT */
#define WM8904_GPI7_EINT_MASK                   0x0008  /* GPI7_EINT */
#define WM8904_GPI7_EINT_SHIFT                       3  /* GPI7_EINT */
#define WM8904_GPI7_EINT_WIDTH                       1  /* GPI7_EINT */
#define WM8904_FWW_WOCK_EINT                    0x0004  /* FWW_WOCK_EINT */
#define WM8904_FWW_WOCK_EINT_MASK               0x0004  /* FWW_WOCK_EINT */
#define WM8904_FWW_WOCK_EINT_SHIFT                   2  /* FWW_WOCK_EINT */
#define WM8904_FWW_WOCK_EINT_WIDTH                   1  /* FWW_WOCK_EINT */
#define WM8904_MIC_SHWT_EINT                    0x0002  /* MIC_SHWT_EINT */
#define WM8904_MIC_SHWT_EINT_MASK               0x0002  /* MIC_SHWT_EINT */
#define WM8904_MIC_SHWT_EINT_SHIFT                   1  /* MIC_SHWT_EINT */
#define WM8904_MIC_SHWT_EINT_WIDTH                   1  /* MIC_SHWT_EINT */
#define WM8904_MIC_DET_EINT                     0x0001  /* MIC_DET_EINT */
#define WM8904_MIC_DET_EINT_MASK                0x0001  /* MIC_DET_EINT */
#define WM8904_MIC_DET_EINT_SHIFT                    0  /* MIC_DET_EINT */
#define WM8904_MIC_DET_EINT_WIDTH                    1  /* MIC_DET_EINT */

/*
 * W128 (0x80) - Intewwupt Status Mask
 */
#define WM8904_IM_GPIO_BCWK_EINT                0x0200  /* IM_GPIO_BCWK_EINT */
#define WM8904_IM_GPIO_BCWK_EINT_MASK           0x0200  /* IM_GPIO_BCWK_EINT */
#define WM8904_IM_GPIO_BCWK_EINT_SHIFT               9  /* IM_GPIO_BCWK_EINT */
#define WM8904_IM_GPIO_BCWK_EINT_WIDTH               1  /* IM_GPIO_BCWK_EINT */
#define WM8904_IM_WSEQ_EINT                     0x0100  /* IM_WSEQ_EINT */
#define WM8904_IM_WSEQ_EINT_MASK                0x0100  /* IM_WSEQ_EINT */
#define WM8904_IM_WSEQ_EINT_SHIFT                    8  /* IM_WSEQ_EINT */
#define WM8904_IM_WSEQ_EINT_WIDTH                    1  /* IM_WSEQ_EINT */
#define WM8904_IM_GPIO3_EINT                    0x0080  /* IM_GPIO3_EINT */
#define WM8904_IM_GPIO3_EINT_MASK               0x0080  /* IM_GPIO3_EINT */
#define WM8904_IM_GPIO3_EINT_SHIFT                   7  /* IM_GPIO3_EINT */
#define WM8904_IM_GPIO3_EINT_WIDTH                   1  /* IM_GPIO3_EINT */
#define WM8904_IM_GPIO2_EINT                    0x0040  /* IM_GPIO2_EINT */
#define WM8904_IM_GPIO2_EINT_MASK               0x0040  /* IM_GPIO2_EINT */
#define WM8904_IM_GPIO2_EINT_SHIFT                   6  /* IM_GPIO2_EINT */
#define WM8904_IM_GPIO2_EINT_WIDTH                   1  /* IM_GPIO2_EINT */
#define WM8904_IM_GPIO1_EINT                    0x0020  /* IM_GPIO1_EINT */
#define WM8904_IM_GPIO1_EINT_MASK               0x0020  /* IM_GPIO1_EINT */
#define WM8904_IM_GPIO1_EINT_SHIFT                   5  /* IM_GPIO1_EINT */
#define WM8904_IM_GPIO1_EINT_WIDTH                   1  /* IM_GPIO1_EINT */
#define WM8904_IM_GPI8_EINT                     0x0010  /* IM_GPI8_EINT */
#define WM8904_IM_GPI8_EINT_MASK                0x0010  /* IM_GPI8_EINT */
#define WM8904_IM_GPI8_EINT_SHIFT                    4  /* IM_GPI8_EINT */
#define WM8904_IM_GPI8_EINT_WIDTH                    1  /* IM_GPI8_EINT */
#define WM8904_IM_GPI7_EINT                     0x0008  /* IM_GPI7_EINT */
#define WM8904_IM_GPI7_EINT_MASK                0x0008  /* IM_GPI7_EINT */
#define WM8904_IM_GPI7_EINT_SHIFT                    3  /* IM_GPI7_EINT */
#define WM8904_IM_GPI7_EINT_WIDTH                    1  /* IM_GPI7_EINT */
#define WM8904_IM_FWW_WOCK_EINT                 0x0004  /* IM_FWW_WOCK_EINT */
#define WM8904_IM_FWW_WOCK_EINT_MASK            0x0004  /* IM_FWW_WOCK_EINT */
#define WM8904_IM_FWW_WOCK_EINT_SHIFT                2  /* IM_FWW_WOCK_EINT */
#define WM8904_IM_FWW_WOCK_EINT_WIDTH                1  /* IM_FWW_WOCK_EINT */
#define WM8904_IM_MIC_SHWT_EINT                 0x0002  /* IM_MIC_SHWT_EINT */
#define WM8904_IM_MIC_SHWT_EINT_MASK            0x0002  /* IM_MIC_SHWT_EINT */
#define WM8904_IM_MIC_SHWT_EINT_SHIFT                1  /* IM_MIC_SHWT_EINT */
#define WM8904_IM_MIC_SHWT_EINT_WIDTH                1  /* IM_MIC_SHWT_EINT */
#define WM8904_IM_MIC_DET_EINT                  0x0001  /* IM_MIC_DET_EINT */
#define WM8904_IM_MIC_DET_EINT_MASK             0x0001  /* IM_MIC_DET_EINT */
#define WM8904_IM_MIC_DET_EINT_SHIFT                 0  /* IM_MIC_DET_EINT */
#define WM8904_IM_MIC_DET_EINT_WIDTH                 1  /* IM_MIC_DET_EINT */

/*
 * W129 (0x81) - Intewwupt Powawity
 */
#define WM8904_GPIO_BCWK_EINT_POW               0x0200  /* GPIO_BCWK_EINT_POW */
#define WM8904_GPIO_BCWK_EINT_POW_MASK          0x0200  /* GPIO_BCWK_EINT_POW */
#define WM8904_GPIO_BCWK_EINT_POW_SHIFT              9  /* GPIO_BCWK_EINT_POW */
#define WM8904_GPIO_BCWK_EINT_POW_WIDTH              1  /* GPIO_BCWK_EINT_POW */
#define WM8904_WSEQ_EINT_POW                    0x0100  /* WSEQ_EINT_POW */
#define WM8904_WSEQ_EINT_POW_MASK               0x0100  /* WSEQ_EINT_POW */
#define WM8904_WSEQ_EINT_POW_SHIFT                   8  /* WSEQ_EINT_POW */
#define WM8904_WSEQ_EINT_POW_WIDTH                   1  /* WSEQ_EINT_POW */
#define WM8904_GPIO3_EINT_POW                   0x0080  /* GPIO3_EINT_POW */
#define WM8904_GPIO3_EINT_POW_MASK              0x0080  /* GPIO3_EINT_POW */
#define WM8904_GPIO3_EINT_POW_SHIFT                  7  /* GPIO3_EINT_POW */
#define WM8904_GPIO3_EINT_POW_WIDTH                  1  /* GPIO3_EINT_POW */
#define WM8904_GPIO2_EINT_POW                   0x0040  /* GPIO2_EINT_POW */
#define WM8904_GPIO2_EINT_POW_MASK              0x0040  /* GPIO2_EINT_POW */
#define WM8904_GPIO2_EINT_POW_SHIFT                  6  /* GPIO2_EINT_POW */
#define WM8904_GPIO2_EINT_POW_WIDTH                  1  /* GPIO2_EINT_POW */
#define WM8904_GPIO1_EINT_POW                   0x0020  /* GPIO1_EINT_POW */
#define WM8904_GPIO1_EINT_POW_MASK              0x0020  /* GPIO1_EINT_POW */
#define WM8904_GPIO1_EINT_POW_SHIFT                  5  /* GPIO1_EINT_POW */
#define WM8904_GPIO1_EINT_POW_WIDTH                  1  /* GPIO1_EINT_POW */
#define WM8904_GPI8_EINT_POW                    0x0010  /* GPI8_EINT_POW */
#define WM8904_GPI8_EINT_POW_MASK               0x0010  /* GPI8_EINT_POW */
#define WM8904_GPI8_EINT_POW_SHIFT                   4  /* GPI8_EINT_POW */
#define WM8904_GPI8_EINT_POW_WIDTH                   1  /* GPI8_EINT_POW */
#define WM8904_GPI7_EINT_POW                    0x0008  /* GPI7_EINT_POW */
#define WM8904_GPI7_EINT_POW_MASK               0x0008  /* GPI7_EINT_POW */
#define WM8904_GPI7_EINT_POW_SHIFT                   3  /* GPI7_EINT_POW */
#define WM8904_GPI7_EINT_POW_WIDTH                   1  /* GPI7_EINT_POW */
#define WM8904_FWW_WOCK_EINT_POW                0x0004  /* FWW_WOCK_EINT_POW */
#define WM8904_FWW_WOCK_EINT_POW_MASK           0x0004  /* FWW_WOCK_EINT_POW */
#define WM8904_FWW_WOCK_EINT_POW_SHIFT               2  /* FWW_WOCK_EINT_POW */
#define WM8904_FWW_WOCK_EINT_POW_WIDTH               1  /* FWW_WOCK_EINT_POW */
#define WM8904_MIC_SHWT_EINT_POW                0x0002  /* MIC_SHWT_EINT_POW */
#define WM8904_MIC_SHWT_EINT_POW_MASK           0x0002  /* MIC_SHWT_EINT_POW */
#define WM8904_MIC_SHWT_EINT_POW_SHIFT               1  /* MIC_SHWT_EINT_POW */
#define WM8904_MIC_SHWT_EINT_POW_WIDTH               1  /* MIC_SHWT_EINT_POW */
#define WM8904_MIC_DET_EINT_POW                 0x0001  /* MIC_DET_EINT_POW */
#define WM8904_MIC_DET_EINT_POW_MASK            0x0001  /* MIC_DET_EINT_POW */
#define WM8904_MIC_DET_EINT_POW_SHIFT                0  /* MIC_DET_EINT_POW */
#define WM8904_MIC_DET_EINT_POW_WIDTH                1  /* MIC_DET_EINT_POW */

/*
 * W130 (0x82) - Intewwupt Debounce
 */
#define WM8904_GPIO_BCWK_EINT_DB                0x0200  /* GPIO_BCWK_EINT_DB */
#define WM8904_GPIO_BCWK_EINT_DB_MASK           0x0200  /* GPIO_BCWK_EINT_DB */
#define WM8904_GPIO_BCWK_EINT_DB_SHIFT               9  /* GPIO_BCWK_EINT_DB */
#define WM8904_GPIO_BCWK_EINT_DB_WIDTH               1  /* GPIO_BCWK_EINT_DB */
#define WM8904_WSEQ_EINT_DB                     0x0100  /* WSEQ_EINT_DB */
#define WM8904_WSEQ_EINT_DB_MASK                0x0100  /* WSEQ_EINT_DB */
#define WM8904_WSEQ_EINT_DB_SHIFT                    8  /* WSEQ_EINT_DB */
#define WM8904_WSEQ_EINT_DB_WIDTH                    1  /* WSEQ_EINT_DB */
#define WM8904_GPIO3_EINT_DB                    0x0080  /* GPIO3_EINT_DB */
#define WM8904_GPIO3_EINT_DB_MASK               0x0080  /* GPIO3_EINT_DB */
#define WM8904_GPIO3_EINT_DB_SHIFT                   7  /* GPIO3_EINT_DB */
#define WM8904_GPIO3_EINT_DB_WIDTH                   1  /* GPIO3_EINT_DB */
#define WM8904_GPIO2_EINT_DB                    0x0040  /* GPIO2_EINT_DB */
#define WM8904_GPIO2_EINT_DB_MASK               0x0040  /* GPIO2_EINT_DB */
#define WM8904_GPIO2_EINT_DB_SHIFT                   6  /* GPIO2_EINT_DB */
#define WM8904_GPIO2_EINT_DB_WIDTH                   1  /* GPIO2_EINT_DB */
#define WM8904_GPIO1_EINT_DB                    0x0020  /* GPIO1_EINT_DB */
#define WM8904_GPIO1_EINT_DB_MASK               0x0020  /* GPIO1_EINT_DB */
#define WM8904_GPIO1_EINT_DB_SHIFT                   5  /* GPIO1_EINT_DB */
#define WM8904_GPIO1_EINT_DB_WIDTH                   1  /* GPIO1_EINT_DB */
#define WM8904_GPI8_EINT_DB                     0x0010  /* GPI8_EINT_DB */
#define WM8904_GPI8_EINT_DB_MASK                0x0010  /* GPI8_EINT_DB */
#define WM8904_GPI8_EINT_DB_SHIFT                    4  /* GPI8_EINT_DB */
#define WM8904_GPI8_EINT_DB_WIDTH                    1  /* GPI8_EINT_DB */
#define WM8904_GPI7_EINT_DB                     0x0008  /* GPI7_EINT_DB */
#define WM8904_GPI7_EINT_DB_MASK                0x0008  /* GPI7_EINT_DB */
#define WM8904_GPI7_EINT_DB_SHIFT                    3  /* GPI7_EINT_DB */
#define WM8904_GPI7_EINT_DB_WIDTH                    1  /* GPI7_EINT_DB */
#define WM8904_FWW_WOCK_EINT_DB                 0x0004  /* FWW_WOCK_EINT_DB */
#define WM8904_FWW_WOCK_EINT_DB_MASK            0x0004  /* FWW_WOCK_EINT_DB */
#define WM8904_FWW_WOCK_EINT_DB_SHIFT                2  /* FWW_WOCK_EINT_DB */
#define WM8904_FWW_WOCK_EINT_DB_WIDTH                1  /* FWW_WOCK_EINT_DB */
#define WM8904_MIC_SHWT_EINT_DB                 0x0002  /* MIC_SHWT_EINT_DB */
#define WM8904_MIC_SHWT_EINT_DB_MASK            0x0002  /* MIC_SHWT_EINT_DB */
#define WM8904_MIC_SHWT_EINT_DB_SHIFT                1  /* MIC_SHWT_EINT_DB */
#define WM8904_MIC_SHWT_EINT_DB_WIDTH                1  /* MIC_SHWT_EINT_DB */
#define WM8904_MIC_DET_EINT_DB                  0x0001  /* MIC_DET_EINT_DB */
#define WM8904_MIC_DET_EINT_DB_MASK             0x0001  /* MIC_DET_EINT_DB */
#define WM8904_MIC_DET_EINT_DB_SHIFT                 0  /* MIC_DET_EINT_DB */
#define WM8904_MIC_DET_EINT_DB_WIDTH                 1  /* MIC_DET_EINT_DB */

/*
 * W134 (0x86) - EQ1
 */
#define WM8904_EQ_ENA                           0x0001  /* EQ_ENA */
#define WM8904_EQ_ENA_MASK                      0x0001  /* EQ_ENA */
#define WM8904_EQ_ENA_SHIFT                          0  /* EQ_ENA */
#define WM8904_EQ_ENA_WIDTH                          1  /* EQ_ENA */

/*
 * W135 (0x87) - EQ2
 */
#define WM8904_EQ_B1_GAIN_MASK                  0x001F  /* EQ_B1_GAIN - [4:0] */
#define WM8904_EQ_B1_GAIN_SHIFT                      0  /* EQ_B1_GAIN - [4:0] */
#define WM8904_EQ_B1_GAIN_WIDTH                      5  /* EQ_B1_GAIN - [4:0] */

/*
 * W136 (0x88) - EQ3
 */
#define WM8904_EQ_B2_GAIN_MASK                  0x001F  /* EQ_B2_GAIN - [4:0] */
#define WM8904_EQ_B2_GAIN_SHIFT                      0  /* EQ_B2_GAIN - [4:0] */
#define WM8904_EQ_B2_GAIN_WIDTH                      5  /* EQ_B2_GAIN - [4:0] */

/*
 * W137 (0x89) - EQ4
 */
#define WM8904_EQ_B3_GAIN_MASK                  0x001F  /* EQ_B3_GAIN - [4:0] */
#define WM8904_EQ_B3_GAIN_SHIFT                      0  /* EQ_B3_GAIN - [4:0] */
#define WM8904_EQ_B3_GAIN_WIDTH                      5  /* EQ_B3_GAIN - [4:0] */

/*
 * W138 (0x8A) - EQ5
 */
#define WM8904_EQ_B4_GAIN_MASK                  0x001F  /* EQ_B4_GAIN - [4:0] */
#define WM8904_EQ_B4_GAIN_SHIFT                      0  /* EQ_B4_GAIN - [4:0] */
#define WM8904_EQ_B4_GAIN_WIDTH                      5  /* EQ_B4_GAIN - [4:0] */

/*
 * W139 (0x8B) - EQ6
 */
#define WM8904_EQ_B5_GAIN_MASK                  0x001F  /* EQ_B5_GAIN - [4:0] */
#define WM8904_EQ_B5_GAIN_SHIFT                      0  /* EQ_B5_GAIN - [4:0] */
#define WM8904_EQ_B5_GAIN_WIDTH                      5  /* EQ_B5_GAIN - [4:0] */

/*
 * W140 (0x8C) - EQ7
 */
#define WM8904_EQ_B1_A_MASK                     0xFFFF  /* EQ_B1_A - [15:0] */
#define WM8904_EQ_B1_A_SHIFT                         0  /* EQ_B1_A - [15:0] */
#define WM8904_EQ_B1_A_WIDTH                        16  /* EQ_B1_A - [15:0] */

/*
 * W141 (0x8D) - EQ8
 */
#define WM8904_EQ_B1_B_MASK                     0xFFFF  /* EQ_B1_B - [15:0] */
#define WM8904_EQ_B1_B_SHIFT                         0  /* EQ_B1_B - [15:0] */
#define WM8904_EQ_B1_B_WIDTH                        16  /* EQ_B1_B - [15:0] */

/*
 * W142 (0x8E) - EQ9
 */
#define WM8904_EQ_B1_PG_MASK                    0xFFFF  /* EQ_B1_PG - [15:0] */
#define WM8904_EQ_B1_PG_SHIFT                        0  /* EQ_B1_PG - [15:0] */
#define WM8904_EQ_B1_PG_WIDTH                       16  /* EQ_B1_PG - [15:0] */

/*
 * W143 (0x8F) - EQ10
 */
#define WM8904_EQ_B2_A_MASK                     0xFFFF  /* EQ_B2_A - [15:0] */
#define WM8904_EQ_B2_A_SHIFT                         0  /* EQ_B2_A - [15:0] */
#define WM8904_EQ_B2_A_WIDTH                        16  /* EQ_B2_A - [15:0] */

/*
 * W144 (0x90) - EQ11
 */
#define WM8904_EQ_B2_B_MASK                     0xFFFF  /* EQ_B2_B - [15:0] */
#define WM8904_EQ_B2_B_SHIFT                         0  /* EQ_B2_B - [15:0] */
#define WM8904_EQ_B2_B_WIDTH                        16  /* EQ_B2_B - [15:0] */

/*
 * W145 (0x91) - EQ12
 */
#define WM8904_EQ_B2_C_MASK                     0xFFFF  /* EQ_B2_C - [15:0] */
#define WM8904_EQ_B2_C_SHIFT                         0  /* EQ_B2_C - [15:0] */
#define WM8904_EQ_B2_C_WIDTH                        16  /* EQ_B2_C - [15:0] */

/*
 * W146 (0x92) - EQ13
 */
#define WM8904_EQ_B2_PG_MASK                    0xFFFF  /* EQ_B2_PG - [15:0] */
#define WM8904_EQ_B2_PG_SHIFT                        0  /* EQ_B2_PG - [15:0] */
#define WM8904_EQ_B2_PG_WIDTH                       16  /* EQ_B2_PG - [15:0] */

/*
 * W147 (0x93) - EQ14
 */
#define WM8904_EQ_B3_A_MASK                     0xFFFF  /* EQ_B3_A - [15:0] */
#define WM8904_EQ_B3_A_SHIFT                         0  /* EQ_B3_A - [15:0] */
#define WM8904_EQ_B3_A_WIDTH                        16  /* EQ_B3_A - [15:0] */

/*
 * W148 (0x94) - EQ15
 */
#define WM8904_EQ_B3_B_MASK                     0xFFFF  /* EQ_B3_B - [15:0] */
#define WM8904_EQ_B3_B_SHIFT                         0  /* EQ_B3_B - [15:0] */
#define WM8904_EQ_B3_B_WIDTH                        16  /* EQ_B3_B - [15:0] */

/*
 * W149 (0x95) - EQ16
 */
#define WM8904_EQ_B3_C_MASK                     0xFFFF  /* EQ_B3_C - [15:0] */
#define WM8904_EQ_B3_C_SHIFT                         0  /* EQ_B3_C - [15:0] */
#define WM8904_EQ_B3_C_WIDTH                        16  /* EQ_B3_C - [15:0] */

/*
 * W150 (0x96) - EQ17
 */
#define WM8904_EQ_B3_PG_MASK                    0xFFFF  /* EQ_B3_PG - [15:0] */
#define WM8904_EQ_B3_PG_SHIFT                        0  /* EQ_B3_PG - [15:0] */
#define WM8904_EQ_B3_PG_WIDTH                       16  /* EQ_B3_PG - [15:0] */

/*
 * W151 (0x97) - EQ18
 */
#define WM8904_EQ_B4_A_MASK                     0xFFFF  /* EQ_B4_A - [15:0] */
#define WM8904_EQ_B4_A_SHIFT                         0  /* EQ_B4_A - [15:0] */
#define WM8904_EQ_B4_A_WIDTH                        16  /* EQ_B4_A - [15:0] */

/*
 * W152 (0x98) - EQ19
 */
#define WM8904_EQ_B4_B_MASK                     0xFFFF  /* EQ_B4_B - [15:0] */
#define WM8904_EQ_B4_B_SHIFT                         0  /* EQ_B4_B - [15:0] */
#define WM8904_EQ_B4_B_WIDTH                        16  /* EQ_B4_B - [15:0] */

/*
 * W153 (0x99) - EQ20
 */
#define WM8904_EQ_B4_C_MASK                     0xFFFF  /* EQ_B4_C - [15:0] */
#define WM8904_EQ_B4_C_SHIFT                         0  /* EQ_B4_C - [15:0] */
#define WM8904_EQ_B4_C_WIDTH                        16  /* EQ_B4_C - [15:0] */

/*
 * W154 (0x9A) - EQ21
 */
#define WM8904_EQ_B4_PG_MASK                    0xFFFF  /* EQ_B4_PG - [15:0] */
#define WM8904_EQ_B4_PG_SHIFT                        0  /* EQ_B4_PG - [15:0] */
#define WM8904_EQ_B4_PG_WIDTH                       16  /* EQ_B4_PG - [15:0] */

/*
 * W155 (0x9B) - EQ22
 */
#define WM8904_EQ_B5_A_MASK                     0xFFFF  /* EQ_B5_A - [15:0] */
#define WM8904_EQ_B5_A_SHIFT                         0  /* EQ_B5_A - [15:0] */
#define WM8904_EQ_B5_A_WIDTH                        16  /* EQ_B5_A - [15:0] */

/*
 * W156 (0x9C) - EQ23
 */
#define WM8904_EQ_B5_B_MASK                     0xFFFF  /* EQ_B5_B - [15:0] */
#define WM8904_EQ_B5_B_SHIFT                         0  /* EQ_B5_B - [15:0] */
#define WM8904_EQ_B5_B_WIDTH                        16  /* EQ_B5_B - [15:0] */

/*
 * W157 (0x9D) - EQ24
 */
#define WM8904_EQ_B5_PG_MASK                    0xFFFF  /* EQ_B5_PG - [15:0] */
#define WM8904_EQ_B5_PG_SHIFT                        0  /* EQ_B5_PG - [15:0] */
#define WM8904_EQ_B5_PG_WIDTH                       16  /* EQ_B5_PG - [15:0] */

/*
 * W161 (0xA1) - Contwow Intewface Test 1
 */
#define WM8904_USEW_KEY                         0x0002  /* USEW_KEY */
#define WM8904_USEW_KEY_MASK                    0x0002  /* USEW_KEY */
#define WM8904_USEW_KEY_SHIFT                        1  /* USEW_KEY */
#define WM8904_USEW_KEY_WIDTH                        1  /* USEW_KEY */

/*
 * W198 (0xC6) - ADC Test 0
 */
#define WM8904_ADC_128_OSW_TST_MODE             0x0004  /* ADC_128_OSW_TST_MODE */
#define WM8904_ADC_128_OSW_TST_MODE_SHIFT            2  /* ADC_128_OSW_TST_MODE */
#define WM8904_ADC_128_OSW_TST_MODE_WIDTH            1  /* ADC_128_OSW_TST_MODE */
#define WM8904_ADC_BIASX1P5                     0x0001  /* ADC_BIASX1P5 */
#define WM8904_ADC_BIASX1P5_SHIFT                    0  /* ADC_BIASX1P5 */
#define WM8904_ADC_BIASX1P5_WIDTH                    1  /* ADC_BIASX1P5 */

/*
 * W204 (0xCC) - Anawogue Output Bias 0
 */
#define WM8904_PGA_BIAS_MASK                    0x0070  /* PGA_BIAS - [6:4] */
#define WM8904_PGA_BIAS_SHIFT                        4  /* PGA_BIAS - [6:4] */
#define WM8904_PGA_BIAS_WIDTH                        3  /* PGA_BIAS - [6:4] */

/*
 * W247 (0xF7) - FWW NCO Test 0
 */
#define WM8904_FWW_FWC_NCO                      0x0001  /* FWW_FWC_NCO */
#define WM8904_FWW_FWC_NCO_MASK                 0x0001  /* FWW_FWC_NCO */
#define WM8904_FWW_FWC_NCO_SHIFT                     0  /* FWW_FWC_NCO */
#define WM8904_FWW_FWC_NCO_WIDTH                     1  /* FWW_FWC_NCO */

/*
 * W248 (0xF8) - FWW NCO Test 1
 */
#define WM8904_FWW_FWC_NCO_VAW_MASK             0x003F  /* FWW_FWC_NCO_VAW - [5:0] */
#define WM8904_FWW_FWC_NCO_VAW_SHIFT                 0  /* FWW_FWC_NCO_VAW - [5:0] */
#define WM8904_FWW_FWC_NCO_VAW_WIDTH                 6  /* FWW_FWC_NCO_VAW - [5:0] */

#endif
