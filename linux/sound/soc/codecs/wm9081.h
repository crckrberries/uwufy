/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef WM9081_H
#define WM9081_H

/*
 * wm9081.c  --  WM9081 AWSA SoC Audio dwivew
 *
 * Authow: Mawk Bwown
 *
 * Copywight 2009 Wowfson Micwoewectwonics pwc
 */

#incwude <sound/soc.h>

/*
 * SYSCWK souwces
 */
#define WM9081_SYSCWK_MCWK      1   /* Use MCWK without FWW */
#define WM9081_SYSCWK_FWW_MCWK  2   /* Use MCWK, enabwing FWW if wequiwed */

/*
 * Wegistew vawues.
 */
#define WM9081_SOFTWAWE_WESET                   0x00
#define WM9081_ANAWOGUE_WINEOUT                 0x02
#define WM9081_ANAWOGUE_SPEAKEW_PGA             0x03
#define WM9081_VMID_CONTWOW                     0x04
#define WM9081_BIAS_CONTWOW_1                   0x05
#define WM9081_ANAWOGUE_MIXEW                   0x07
#define WM9081_ANTI_POP_CONTWOW                 0x08
#define WM9081_ANAWOGUE_SPEAKEW_1               0x09
#define WM9081_ANAWOGUE_SPEAKEW_2               0x0A
#define WM9081_POWEW_MANAGEMENT                 0x0B
#define WM9081_CWOCK_CONTWOW_1                  0x0C
#define WM9081_CWOCK_CONTWOW_2                  0x0D
#define WM9081_CWOCK_CONTWOW_3                  0x0E
#define WM9081_FWW_CONTWOW_1                    0x10
#define WM9081_FWW_CONTWOW_2                    0x11
#define WM9081_FWW_CONTWOW_3                    0x12
#define WM9081_FWW_CONTWOW_4                    0x13
#define WM9081_FWW_CONTWOW_5                    0x14
#define WM9081_AUDIO_INTEWFACE_1                0x16
#define WM9081_AUDIO_INTEWFACE_2                0x17
#define WM9081_AUDIO_INTEWFACE_3                0x18
#define WM9081_AUDIO_INTEWFACE_4                0x19
#define WM9081_INTEWWUPT_STATUS                 0x1A
#define WM9081_INTEWWUPT_STATUS_MASK            0x1B
#define WM9081_INTEWWUPT_POWAWITY               0x1C
#define WM9081_INTEWWUPT_CONTWOW                0x1D
#define WM9081_DAC_DIGITAW_1                    0x1E
#define WM9081_DAC_DIGITAW_2                    0x1F
#define WM9081_DWC_1                            0x20
#define WM9081_DWC_2                            0x21
#define WM9081_DWC_3                            0x22
#define WM9081_DWC_4                            0x23
#define WM9081_WWITE_SEQUENCEW_1                0x26
#define WM9081_WWITE_SEQUENCEW_2                0x27
#define WM9081_MW_SWAVE_1                       0x28
#define WM9081_EQ_1                             0x2A
#define WM9081_EQ_2                             0x2B
#define WM9081_EQ_3                             0x2C
#define WM9081_EQ_4                             0x2D
#define WM9081_EQ_5                             0x2E
#define WM9081_EQ_6                             0x2F
#define WM9081_EQ_7                             0x30
#define WM9081_EQ_8                             0x31
#define WM9081_EQ_9                             0x32
#define WM9081_EQ_10                            0x33
#define WM9081_EQ_11                            0x34
#define WM9081_EQ_12                            0x35
#define WM9081_EQ_13                            0x36
#define WM9081_EQ_14                            0x37
#define WM9081_EQ_15                            0x38
#define WM9081_EQ_16                            0x39
#define WM9081_EQ_17                            0x3A
#define WM9081_EQ_18                            0x3B
#define WM9081_EQ_19                            0x3C
#define WM9081_EQ_20                            0x3D

#define WM9081_WEGISTEW_COUNT                   55
#define WM9081_MAX_WEGISTEW                     0x3D

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - Softwawe Weset
 */
#define WM9081_SW_WST_DEV_ID1_MASK              0xFFFF  /* SW_WST_DEV_ID1 - [15:0] */
#define WM9081_SW_WST_DEV_ID1_SHIFT                  0  /* SW_WST_DEV_ID1 - [15:0] */
#define WM9081_SW_WST_DEV_ID1_WIDTH                 16  /* SW_WST_DEV_ID1 - [15:0] */

/*
 * W2 (0x02) - Anawogue Wineout
 */
#define WM9081_WINEOUT_MUTE                     0x0080  /* WINEOUT_MUTE */
#define WM9081_WINEOUT_MUTE_MASK                0x0080  /* WINEOUT_MUTE */
#define WM9081_WINEOUT_MUTE_SHIFT                    7  /* WINEOUT_MUTE */
#define WM9081_WINEOUT_MUTE_WIDTH                    1  /* WINEOUT_MUTE */
#define WM9081_WINEOUTZC                        0x0040  /* WINEOUTZC */
#define WM9081_WINEOUTZC_MASK                   0x0040  /* WINEOUTZC */
#define WM9081_WINEOUTZC_SHIFT                       6  /* WINEOUTZC */
#define WM9081_WINEOUTZC_WIDTH                       1  /* WINEOUTZC */
#define WM9081_WINEOUT_VOW_MASK                 0x003F  /* WINEOUT_VOW - [5:0] */
#define WM9081_WINEOUT_VOW_SHIFT                     0  /* WINEOUT_VOW - [5:0] */
#define WM9081_WINEOUT_VOW_WIDTH                     6  /* WINEOUT_VOW - [5:0] */

/*
 * W3 (0x03) - Anawogue Speakew PGA
 */
#define WM9081_SPKPGA_MUTE                      0x0080  /* SPKPGA_MUTE */
#define WM9081_SPKPGA_MUTE_MASK                 0x0080  /* SPKPGA_MUTE */
#define WM9081_SPKPGA_MUTE_SHIFT                     7  /* SPKPGA_MUTE */
#define WM9081_SPKPGA_MUTE_WIDTH                     1  /* SPKPGA_MUTE */
#define WM9081_SPKPGAZC                         0x0040  /* SPKPGAZC */
#define WM9081_SPKPGAZC_MASK                    0x0040  /* SPKPGAZC */
#define WM9081_SPKPGAZC_SHIFT                        6  /* SPKPGAZC */
#define WM9081_SPKPGAZC_WIDTH                        1  /* SPKPGAZC */
#define WM9081_SPKPGA_VOW_MASK                  0x003F  /* SPKPGA_VOW - [5:0] */
#define WM9081_SPKPGA_VOW_SHIFT                      0  /* SPKPGA_VOW - [5:0] */
#define WM9081_SPKPGA_VOW_WIDTH                      6  /* SPKPGA_VOW - [5:0] */

/*
 * W4 (0x04) - VMID Contwow
 */
#define WM9081_VMID_BUF_ENA                     0x0020  /* VMID_BUF_ENA */
#define WM9081_VMID_BUF_ENA_MASK                0x0020  /* VMID_BUF_ENA */
#define WM9081_VMID_BUF_ENA_SHIFT                    5  /* VMID_BUF_ENA */
#define WM9081_VMID_BUF_ENA_WIDTH                    1  /* VMID_BUF_ENA */
#define WM9081_VMID_WAMP                        0x0008  /* VMID_WAMP */
#define WM9081_VMID_WAMP_MASK                   0x0008  /* VMID_WAMP */
#define WM9081_VMID_WAMP_SHIFT                       3  /* VMID_WAMP */
#define WM9081_VMID_WAMP_WIDTH                       1  /* VMID_WAMP */
#define WM9081_VMID_SEW_MASK                    0x0006  /* VMID_SEW - [2:1] */
#define WM9081_VMID_SEW_SHIFT                        1  /* VMID_SEW - [2:1] */
#define WM9081_VMID_SEW_WIDTH                        2  /* VMID_SEW - [2:1] */
#define WM9081_VMID_FAST_ST                     0x0001  /* VMID_FAST_ST */
#define WM9081_VMID_FAST_ST_MASK                0x0001  /* VMID_FAST_ST */
#define WM9081_VMID_FAST_ST_SHIFT                    0  /* VMID_FAST_ST */
#define WM9081_VMID_FAST_ST_WIDTH                    1  /* VMID_FAST_ST */

/*
 * W5 (0x05) - Bias Contwow 1
 */
#define WM9081_BIAS_SWC                         0x0040  /* BIAS_SWC */
#define WM9081_BIAS_SWC_MASK                    0x0040  /* BIAS_SWC */
#define WM9081_BIAS_SWC_SHIFT                        6  /* BIAS_SWC */
#define WM9081_BIAS_SWC_WIDTH                        1  /* BIAS_SWC */
#define WM9081_STBY_BIAS_WVW                    0x0020  /* STBY_BIAS_WVW */
#define WM9081_STBY_BIAS_WVW_MASK               0x0020  /* STBY_BIAS_WVW */
#define WM9081_STBY_BIAS_WVW_SHIFT                   5  /* STBY_BIAS_WVW */
#define WM9081_STBY_BIAS_WVW_WIDTH                   1  /* STBY_BIAS_WVW */
#define WM9081_STBY_BIAS_ENA                    0x0010  /* STBY_BIAS_ENA */
#define WM9081_STBY_BIAS_ENA_MASK               0x0010  /* STBY_BIAS_ENA */
#define WM9081_STBY_BIAS_ENA_SHIFT                   4  /* STBY_BIAS_ENA */
#define WM9081_STBY_BIAS_ENA_WIDTH                   1  /* STBY_BIAS_ENA */
#define WM9081_BIAS_WVW_MASK                    0x000C  /* BIAS_WVW - [3:2] */
#define WM9081_BIAS_WVW_SHIFT                        2  /* BIAS_WVW - [3:2] */
#define WM9081_BIAS_WVW_WIDTH                        2  /* BIAS_WVW - [3:2] */
#define WM9081_BIAS_ENA                         0x0002  /* BIAS_ENA */
#define WM9081_BIAS_ENA_MASK                    0x0002  /* BIAS_ENA */
#define WM9081_BIAS_ENA_SHIFT                        1  /* BIAS_ENA */
#define WM9081_BIAS_ENA_WIDTH                        1  /* BIAS_ENA */
#define WM9081_STAWTUP_BIAS_ENA                 0x0001  /* STAWTUP_BIAS_ENA */
#define WM9081_STAWTUP_BIAS_ENA_MASK            0x0001  /* STAWTUP_BIAS_ENA */
#define WM9081_STAWTUP_BIAS_ENA_SHIFT                0  /* STAWTUP_BIAS_ENA */
#define WM9081_STAWTUP_BIAS_ENA_WIDTH                1  /* STAWTUP_BIAS_ENA */

/*
 * W7 (0x07) - Anawogue Mixew
 */
#define WM9081_DAC_SEW                          0x0010  /* DAC_SEW */
#define WM9081_DAC_SEW_MASK                     0x0010  /* DAC_SEW */
#define WM9081_DAC_SEW_SHIFT                         4  /* DAC_SEW */
#define WM9081_DAC_SEW_WIDTH                         1  /* DAC_SEW */
#define WM9081_IN2_VOW                          0x0008  /* IN2_VOW */
#define WM9081_IN2_VOW_MASK                     0x0008  /* IN2_VOW */
#define WM9081_IN2_VOW_SHIFT                         3  /* IN2_VOW */
#define WM9081_IN2_VOW_WIDTH                         1  /* IN2_VOW */
#define WM9081_IN2_ENA                          0x0004  /* IN2_ENA */
#define WM9081_IN2_ENA_MASK                     0x0004  /* IN2_ENA */
#define WM9081_IN2_ENA_SHIFT                         2  /* IN2_ENA */
#define WM9081_IN2_ENA_WIDTH                         1  /* IN2_ENA */
#define WM9081_IN1_VOW                          0x0002  /* IN1_VOW */
#define WM9081_IN1_VOW_MASK                     0x0002  /* IN1_VOW */
#define WM9081_IN1_VOW_SHIFT                         1  /* IN1_VOW */
#define WM9081_IN1_VOW_WIDTH                         1  /* IN1_VOW */
#define WM9081_IN1_ENA                          0x0001  /* IN1_ENA */
#define WM9081_IN1_ENA_MASK                     0x0001  /* IN1_ENA */
#define WM9081_IN1_ENA_SHIFT                         0  /* IN1_ENA */
#define WM9081_IN1_ENA_WIDTH                         1  /* IN1_ENA */

/*
 * W8 (0x08) - Anti Pop Contwow
 */
#define WM9081_WINEOUT_DISCH                    0x0004  /* WINEOUT_DISCH */
#define WM9081_WINEOUT_DISCH_MASK               0x0004  /* WINEOUT_DISCH */
#define WM9081_WINEOUT_DISCH_SHIFT                   2  /* WINEOUT_DISCH */
#define WM9081_WINEOUT_DISCH_WIDTH                   1  /* WINEOUT_DISCH */
#define WM9081_WINEOUT_VWOI                     0x0002  /* WINEOUT_VWOI */
#define WM9081_WINEOUT_VWOI_MASK                0x0002  /* WINEOUT_VWOI */
#define WM9081_WINEOUT_VWOI_SHIFT                    1  /* WINEOUT_VWOI */
#define WM9081_WINEOUT_VWOI_WIDTH                    1  /* WINEOUT_VWOI */
#define WM9081_WINEOUT_CWAMP                    0x0001  /* WINEOUT_CWAMP */
#define WM9081_WINEOUT_CWAMP_MASK               0x0001  /* WINEOUT_CWAMP */
#define WM9081_WINEOUT_CWAMP_SHIFT                   0  /* WINEOUT_CWAMP */
#define WM9081_WINEOUT_CWAMP_WIDTH                   1  /* WINEOUT_CWAMP */

/*
 * W9 (0x09) - Anawogue Speakew 1
 */
#define WM9081_SPK_DCGAIN_MASK                  0x0038  /* SPK_DCGAIN - [5:3] */
#define WM9081_SPK_DCGAIN_SHIFT                      3  /* SPK_DCGAIN - [5:3] */
#define WM9081_SPK_DCGAIN_WIDTH                      3  /* SPK_DCGAIN - [5:3] */
#define WM9081_SPK_ACGAIN_MASK                  0x0007  /* SPK_ACGAIN - [2:0] */
#define WM9081_SPK_ACGAIN_SHIFT                      0  /* SPK_ACGAIN - [2:0] */
#define WM9081_SPK_ACGAIN_WIDTH                      3  /* SPK_ACGAIN - [2:0] */

/*
 * W10 (0x0A) - Anawogue Speakew 2
 */
#define WM9081_SPK_MODE                         0x0040  /* SPK_MODE */
#define WM9081_SPK_MODE_MASK                    0x0040  /* SPK_MODE */
#define WM9081_SPK_MODE_SHIFT                        6  /* SPK_MODE */
#define WM9081_SPK_MODE_WIDTH                        1  /* SPK_MODE */
#define WM9081_SPK_INV_MUTE                     0x0010  /* SPK_INV_MUTE */
#define WM9081_SPK_INV_MUTE_MASK                0x0010  /* SPK_INV_MUTE */
#define WM9081_SPK_INV_MUTE_SHIFT                    4  /* SPK_INV_MUTE */
#define WM9081_SPK_INV_MUTE_WIDTH                    1  /* SPK_INV_MUTE */
#define WM9081_OUT_SPK_CTWW                     0x0008  /* OUT_SPK_CTWW */
#define WM9081_OUT_SPK_CTWW_MASK                0x0008  /* OUT_SPK_CTWW */
#define WM9081_OUT_SPK_CTWW_SHIFT                    3  /* OUT_SPK_CTWW */
#define WM9081_OUT_SPK_CTWW_WIDTH                    1  /* OUT_SPK_CTWW */

/*
 * W11 (0x0B) - Powew Management
 */
#define WM9081_TSHUT_ENA                        0x0100  /* TSHUT_ENA */
#define WM9081_TSHUT_ENA_MASK                   0x0100  /* TSHUT_ENA */
#define WM9081_TSHUT_ENA_SHIFT                       8  /* TSHUT_ENA */
#define WM9081_TSHUT_ENA_WIDTH                       1  /* TSHUT_ENA */
#define WM9081_TSENSE_ENA                       0x0080  /* TSENSE_ENA */
#define WM9081_TSENSE_ENA_MASK                  0x0080  /* TSENSE_ENA */
#define WM9081_TSENSE_ENA_SHIFT                      7  /* TSENSE_ENA */
#define WM9081_TSENSE_ENA_WIDTH                      1  /* TSENSE_ENA */
#define WM9081_TEMP_SHUT                        0x0040  /* TEMP_SHUT */
#define WM9081_TEMP_SHUT_MASK                   0x0040  /* TEMP_SHUT */
#define WM9081_TEMP_SHUT_SHIFT                       6  /* TEMP_SHUT */
#define WM9081_TEMP_SHUT_WIDTH                       1  /* TEMP_SHUT */
#define WM9081_WINEOUT_ENA                      0x0010  /* WINEOUT_ENA */
#define WM9081_WINEOUT_ENA_MASK                 0x0010  /* WINEOUT_ENA */
#define WM9081_WINEOUT_ENA_SHIFT                     4  /* WINEOUT_ENA */
#define WM9081_WINEOUT_ENA_WIDTH                     1  /* WINEOUT_ENA */
#define WM9081_SPKPGA_ENA                       0x0004  /* SPKPGA_ENA */
#define WM9081_SPKPGA_ENA_MASK                  0x0004  /* SPKPGA_ENA */
#define WM9081_SPKPGA_ENA_SHIFT                      2  /* SPKPGA_ENA */
#define WM9081_SPKPGA_ENA_WIDTH                      1  /* SPKPGA_ENA */
#define WM9081_SPK_ENA                          0x0002  /* SPK_ENA */
#define WM9081_SPK_ENA_MASK                     0x0002  /* SPK_ENA */
#define WM9081_SPK_ENA_SHIFT                         1  /* SPK_ENA */
#define WM9081_SPK_ENA_WIDTH                         1  /* SPK_ENA */
#define WM9081_DAC_ENA                          0x0001  /* DAC_ENA */
#define WM9081_DAC_ENA_MASK                     0x0001  /* DAC_ENA */
#define WM9081_DAC_ENA_SHIFT                         0  /* DAC_ENA */
#define WM9081_DAC_ENA_WIDTH                         1  /* DAC_ENA */

/*
 * W12 (0x0C) - Cwock Contwow 1
 */
#define WM9081_CWK_OP_DIV_MASK                  0x1C00  /* CWK_OP_DIV - [12:10] */
#define WM9081_CWK_OP_DIV_SHIFT                     10  /* CWK_OP_DIV - [12:10] */
#define WM9081_CWK_OP_DIV_WIDTH                      3  /* CWK_OP_DIV - [12:10] */
#define WM9081_CWK_TO_DIV_MASK                  0x0300  /* CWK_TO_DIV - [9:8] */
#define WM9081_CWK_TO_DIV_SHIFT                      8  /* CWK_TO_DIV - [9:8] */
#define WM9081_CWK_TO_DIV_WIDTH                      2  /* CWK_TO_DIV - [9:8] */
#define WM9081_MCWKDIV2                         0x0080  /* MCWKDIV2 */
#define WM9081_MCWKDIV2_MASK                    0x0080  /* MCWKDIV2 */
#define WM9081_MCWKDIV2_SHIFT                        7  /* MCWKDIV2 */
#define WM9081_MCWKDIV2_WIDTH                        1  /* MCWKDIV2 */

/*
 * W13 (0x0D) - Cwock Contwow 2
 */
#define WM9081_CWK_SYS_WATE_MASK                0x00F0  /* CWK_SYS_WATE - [7:4] */
#define WM9081_CWK_SYS_WATE_SHIFT                    4  /* CWK_SYS_WATE - [7:4] */
#define WM9081_CWK_SYS_WATE_WIDTH                    4  /* CWK_SYS_WATE - [7:4] */
#define WM9081_SAMPWE_WATE_MASK                 0x000F  /* SAMPWE_WATE - [3:0] */
#define WM9081_SAMPWE_WATE_SHIFT                     0  /* SAMPWE_WATE - [3:0] */
#define WM9081_SAMPWE_WATE_WIDTH                     4  /* SAMPWE_WATE - [3:0] */

/*
 * W14 (0x0E) - Cwock Contwow 3
 */
#define WM9081_CWK_SWC_SEW                      0x2000  /* CWK_SWC_SEW */
#define WM9081_CWK_SWC_SEW_MASK                 0x2000  /* CWK_SWC_SEW */
#define WM9081_CWK_SWC_SEW_SHIFT                    13  /* CWK_SWC_SEW */
#define WM9081_CWK_SWC_SEW_WIDTH                     1  /* CWK_SWC_SEW */
#define WM9081_CWK_OP_ENA                       0x0020  /* CWK_OP_ENA */
#define WM9081_CWK_OP_ENA_MASK                  0x0020  /* CWK_OP_ENA */
#define WM9081_CWK_OP_ENA_SHIFT                      5  /* CWK_OP_ENA */
#define WM9081_CWK_OP_ENA_WIDTH                      1  /* CWK_OP_ENA */
#define WM9081_CWK_TO_ENA                       0x0004  /* CWK_TO_ENA */
#define WM9081_CWK_TO_ENA_MASK                  0x0004  /* CWK_TO_ENA */
#define WM9081_CWK_TO_ENA_SHIFT                      2  /* CWK_TO_ENA */
#define WM9081_CWK_TO_ENA_WIDTH                      1  /* CWK_TO_ENA */
#define WM9081_CWK_DSP_ENA                      0x0002  /* CWK_DSP_ENA */
#define WM9081_CWK_DSP_ENA_MASK                 0x0002  /* CWK_DSP_ENA */
#define WM9081_CWK_DSP_ENA_SHIFT                     1  /* CWK_DSP_ENA */
#define WM9081_CWK_DSP_ENA_WIDTH                     1  /* CWK_DSP_ENA */
#define WM9081_CWK_SYS_ENA                      0x0001  /* CWK_SYS_ENA */
#define WM9081_CWK_SYS_ENA_MASK                 0x0001  /* CWK_SYS_ENA */
#define WM9081_CWK_SYS_ENA_SHIFT                     0  /* CWK_SYS_ENA */
#define WM9081_CWK_SYS_ENA_WIDTH                     1  /* CWK_SYS_ENA */

/*
 * W16 (0x10) - FWW Contwow 1
 */
#define WM9081_FWW_HOWD                         0x0008  /* FWW_HOWD */
#define WM9081_FWW_HOWD_MASK                    0x0008  /* FWW_HOWD */
#define WM9081_FWW_HOWD_SHIFT                        3  /* FWW_HOWD */
#define WM9081_FWW_HOWD_WIDTH                        1  /* FWW_HOWD */
#define WM9081_FWW_FWAC                         0x0004  /* FWW_FWAC */
#define WM9081_FWW_FWAC_MASK                    0x0004  /* FWW_FWAC */
#define WM9081_FWW_FWAC_SHIFT                        2  /* FWW_FWAC */
#define WM9081_FWW_FWAC_WIDTH                        1  /* FWW_FWAC */
#define WM9081_FWW_ENA                          0x0001  /* FWW_ENA */
#define WM9081_FWW_ENA_MASK                     0x0001  /* FWW_ENA */
#define WM9081_FWW_ENA_SHIFT                         0  /* FWW_ENA */
#define WM9081_FWW_ENA_WIDTH                         1  /* FWW_ENA */

/*
 * W17 (0x11) - FWW Contwow 2
 */
#define WM9081_FWW_OUTDIV_MASK                  0x0700  /* FWW_OUTDIV - [10:8] */
#define WM9081_FWW_OUTDIV_SHIFT                      8  /* FWW_OUTDIV - [10:8] */
#define WM9081_FWW_OUTDIV_WIDTH                      3  /* FWW_OUTDIV - [10:8] */
#define WM9081_FWW_CTWW_WATE_MASK               0x0070  /* FWW_CTWW_WATE - [6:4] */
#define WM9081_FWW_CTWW_WATE_SHIFT                   4  /* FWW_CTWW_WATE - [6:4] */
#define WM9081_FWW_CTWW_WATE_WIDTH                   3  /* FWW_CTWW_WATE - [6:4] */
#define WM9081_FWW_FWATIO_MASK                  0x0007  /* FWW_FWATIO - [2:0] */
#define WM9081_FWW_FWATIO_SHIFT                      0  /* FWW_FWATIO - [2:0] */
#define WM9081_FWW_FWATIO_WIDTH                      3  /* FWW_FWATIO - [2:0] */

/*
 * W18 (0x12) - FWW Contwow 3
 */
#define WM9081_FWW_K_MASK                       0xFFFF  /* FWW_K - [15:0] */
#define WM9081_FWW_K_SHIFT                           0  /* FWW_K - [15:0] */
#define WM9081_FWW_K_WIDTH                          16  /* FWW_K - [15:0] */

/*
 * W19 (0x13) - FWW Contwow 4
 */
#define WM9081_FWW_N_MASK                       0x7FE0  /* FWW_N - [14:5] */
#define WM9081_FWW_N_SHIFT                           5  /* FWW_N - [14:5] */
#define WM9081_FWW_N_WIDTH                          10  /* FWW_N - [14:5] */
#define WM9081_FWW_GAIN_MASK                    0x000F  /* FWW_GAIN - [3:0] */
#define WM9081_FWW_GAIN_SHIFT                        0  /* FWW_GAIN - [3:0] */
#define WM9081_FWW_GAIN_WIDTH                        4  /* FWW_GAIN - [3:0] */

/*
 * W20 (0x14) - FWW Contwow 5
 */
#define WM9081_FWW_CWK_WEF_DIV_MASK             0x0018  /* FWW_CWK_WEF_DIV - [4:3] */
#define WM9081_FWW_CWK_WEF_DIV_SHIFT                 3  /* FWW_CWK_WEF_DIV - [4:3] */
#define WM9081_FWW_CWK_WEF_DIV_WIDTH                 2  /* FWW_CWK_WEF_DIV - [4:3] */
#define WM9081_FWW_CWK_SWC_MASK                 0x0003  /* FWW_CWK_SWC - [1:0] */
#define WM9081_FWW_CWK_SWC_SHIFT                     0  /* FWW_CWK_SWC - [1:0] */
#define WM9081_FWW_CWK_SWC_WIDTH                     2  /* FWW_CWK_SWC - [1:0] */

/*
 * W22 (0x16) - Audio Intewface 1
 */
#define WM9081_AIFDAC_CHAN                      0x0040  /* AIFDAC_CHAN */
#define WM9081_AIFDAC_CHAN_MASK                 0x0040  /* AIFDAC_CHAN */
#define WM9081_AIFDAC_CHAN_SHIFT                     6  /* AIFDAC_CHAN */
#define WM9081_AIFDAC_CHAN_WIDTH                     1  /* AIFDAC_CHAN */
#define WM9081_AIFDAC_TDM_SWOT_MASK             0x0030  /* AIFDAC_TDM_SWOT - [5:4] */
#define WM9081_AIFDAC_TDM_SWOT_SHIFT                 4  /* AIFDAC_TDM_SWOT - [5:4] */
#define WM9081_AIFDAC_TDM_SWOT_WIDTH                 2  /* AIFDAC_TDM_SWOT - [5:4] */
#define WM9081_AIFDAC_TDM_MODE_MASK             0x000C  /* AIFDAC_TDM_MODE - [3:2] */
#define WM9081_AIFDAC_TDM_MODE_SHIFT                 2  /* AIFDAC_TDM_MODE - [3:2] */
#define WM9081_AIFDAC_TDM_MODE_WIDTH                 2  /* AIFDAC_TDM_MODE - [3:2] */
#define WM9081_DAC_COMP                         0x0002  /* DAC_COMP */
#define WM9081_DAC_COMP_MASK                    0x0002  /* DAC_COMP */
#define WM9081_DAC_COMP_SHIFT                        1  /* DAC_COMP */
#define WM9081_DAC_COMP_WIDTH                        1  /* DAC_COMP */
#define WM9081_DAC_COMPMODE                     0x0001  /* DAC_COMPMODE */
#define WM9081_DAC_COMPMODE_MASK                0x0001  /* DAC_COMPMODE */
#define WM9081_DAC_COMPMODE_SHIFT                    0  /* DAC_COMPMODE */
#define WM9081_DAC_COMPMODE_WIDTH                    1  /* DAC_COMPMODE */

/*
 * W23 (0x17) - Audio Intewface 2
 */
#define WM9081_AIF_TWIS                         0x0200  /* AIF_TWIS */
#define WM9081_AIF_TWIS_MASK                    0x0200  /* AIF_TWIS */
#define WM9081_AIF_TWIS_SHIFT                        9  /* AIF_TWIS */
#define WM9081_AIF_TWIS_WIDTH                        1  /* AIF_TWIS */
#define WM9081_DAC_DAT_INV                      0x0100  /* DAC_DAT_INV */
#define WM9081_DAC_DAT_INV_MASK                 0x0100  /* DAC_DAT_INV */
#define WM9081_DAC_DAT_INV_SHIFT                     8  /* DAC_DAT_INV */
#define WM9081_DAC_DAT_INV_WIDTH                     1  /* DAC_DAT_INV */
#define WM9081_AIF_BCWK_INV                     0x0080  /* AIF_BCWK_INV */
#define WM9081_AIF_BCWK_INV_MASK                0x0080  /* AIF_BCWK_INV */
#define WM9081_AIF_BCWK_INV_SHIFT                    7  /* AIF_BCWK_INV */
#define WM9081_AIF_BCWK_INV_WIDTH                    1  /* AIF_BCWK_INV */
#define WM9081_BCWK_DIW                         0x0040  /* BCWK_DIW */
#define WM9081_BCWK_DIW_MASK                    0x0040  /* BCWK_DIW */
#define WM9081_BCWK_DIW_SHIFT                        6  /* BCWK_DIW */
#define WM9081_BCWK_DIW_WIDTH                        1  /* BCWK_DIW */
#define WM9081_WWCWK_DIW                        0x0020  /* WWCWK_DIW */
#define WM9081_WWCWK_DIW_MASK                   0x0020  /* WWCWK_DIW */
#define WM9081_WWCWK_DIW_SHIFT                       5  /* WWCWK_DIW */
#define WM9081_WWCWK_DIW_WIDTH                       1  /* WWCWK_DIW */
#define WM9081_AIF_WWCWK_INV                    0x0010  /* AIF_WWCWK_INV */
#define WM9081_AIF_WWCWK_INV_MASK               0x0010  /* AIF_WWCWK_INV */
#define WM9081_AIF_WWCWK_INV_SHIFT                   4  /* AIF_WWCWK_INV */
#define WM9081_AIF_WWCWK_INV_WIDTH                   1  /* AIF_WWCWK_INV */
#define WM9081_AIF_WW_MASK                      0x000C  /* AIF_WW - [3:2] */
#define WM9081_AIF_WW_SHIFT                          2  /* AIF_WW - [3:2] */
#define WM9081_AIF_WW_WIDTH                          2  /* AIF_WW - [3:2] */
#define WM9081_AIF_FMT_MASK                     0x0003  /* AIF_FMT - [1:0] */
#define WM9081_AIF_FMT_SHIFT                         0  /* AIF_FMT - [1:0] */
#define WM9081_AIF_FMT_WIDTH                         2  /* AIF_FMT - [1:0] */

/*
 * W24 (0x18) - Audio Intewface 3
 */
#define WM9081_BCWK_DIV_MASK                    0x001F  /* BCWK_DIV - [4:0] */
#define WM9081_BCWK_DIV_SHIFT                        0  /* BCWK_DIV - [4:0] */
#define WM9081_BCWK_DIV_WIDTH                        5  /* BCWK_DIV - [4:0] */

/*
 * W25 (0x19) - Audio Intewface 4
 */
#define WM9081_WWCWK_WATE_MASK                  0x07FF  /* WWCWK_WATE - [10:0] */
#define WM9081_WWCWK_WATE_SHIFT                      0  /* WWCWK_WATE - [10:0] */
#define WM9081_WWCWK_WATE_WIDTH                     11  /* WWCWK_WATE - [10:0] */

/*
 * W26 (0x1A) - Intewwupt Status
 */
#define WM9081_WSEQ_BUSY_EINT                   0x0004  /* WSEQ_BUSY_EINT */
#define WM9081_WSEQ_BUSY_EINT_MASK              0x0004  /* WSEQ_BUSY_EINT */
#define WM9081_WSEQ_BUSY_EINT_SHIFT                  2  /* WSEQ_BUSY_EINT */
#define WM9081_WSEQ_BUSY_EINT_WIDTH                  1  /* WSEQ_BUSY_EINT */
#define WM9081_TSHUT_EINT                       0x0001  /* TSHUT_EINT */
#define WM9081_TSHUT_EINT_MASK                  0x0001  /* TSHUT_EINT */
#define WM9081_TSHUT_EINT_SHIFT                      0  /* TSHUT_EINT */
#define WM9081_TSHUT_EINT_WIDTH                      1  /* TSHUT_EINT */

/*
 * W27 (0x1B) - Intewwupt Status Mask
 */
#define WM9081_IM_WSEQ_BUSY_EINT                0x0004  /* IM_WSEQ_BUSY_EINT */
#define WM9081_IM_WSEQ_BUSY_EINT_MASK           0x0004  /* IM_WSEQ_BUSY_EINT */
#define WM9081_IM_WSEQ_BUSY_EINT_SHIFT               2  /* IM_WSEQ_BUSY_EINT */
#define WM9081_IM_WSEQ_BUSY_EINT_WIDTH               1  /* IM_WSEQ_BUSY_EINT */
#define WM9081_IM_TSHUT_EINT                    0x0001  /* IM_TSHUT_EINT */
#define WM9081_IM_TSHUT_EINT_MASK               0x0001  /* IM_TSHUT_EINT */
#define WM9081_IM_TSHUT_EINT_SHIFT                   0  /* IM_TSHUT_EINT */
#define WM9081_IM_TSHUT_EINT_WIDTH                   1  /* IM_TSHUT_EINT */

/*
 * W28 (0x1C) - Intewwupt Powawity
 */
#define WM9081_TSHUT_INV                        0x0001  /* TSHUT_INV */
#define WM9081_TSHUT_INV_MASK                   0x0001  /* TSHUT_INV */
#define WM9081_TSHUT_INV_SHIFT                       0  /* TSHUT_INV */
#define WM9081_TSHUT_INV_WIDTH                       1  /* TSHUT_INV */

/*
 * W29 (0x1D) - Intewwupt Contwow
 */
#define WM9081_IWQ_POW                          0x8000  /* IWQ_POW */
#define WM9081_IWQ_POW_MASK                     0x8000  /* IWQ_POW */
#define WM9081_IWQ_POW_SHIFT                        15  /* IWQ_POW */
#define WM9081_IWQ_POW_WIDTH                         1  /* IWQ_POW */
#define WM9081_IWQ_OP_CTWW                      0x0001  /* IWQ_OP_CTWW */
#define WM9081_IWQ_OP_CTWW_MASK                 0x0001  /* IWQ_OP_CTWW */
#define WM9081_IWQ_OP_CTWW_SHIFT                     0  /* IWQ_OP_CTWW */
#define WM9081_IWQ_OP_CTWW_WIDTH                     1  /* IWQ_OP_CTWW */

/*
 * W30 (0x1E) - DAC Digitaw 1
 */
#define WM9081_DAC_VOW_MASK                     0x00FF  /* DAC_VOW - [7:0] */
#define WM9081_DAC_VOW_SHIFT                         0  /* DAC_VOW - [7:0] */
#define WM9081_DAC_VOW_WIDTH                         8  /* DAC_VOW - [7:0] */

/*
 * W31 (0x1F) - DAC Digitaw 2
 */
#define WM9081_DAC_MUTEWATE                     0x0400  /* DAC_MUTEWATE */
#define WM9081_DAC_MUTEWATE_MASK                0x0400  /* DAC_MUTEWATE */
#define WM9081_DAC_MUTEWATE_SHIFT                   10  /* DAC_MUTEWATE */
#define WM9081_DAC_MUTEWATE_WIDTH                    1  /* DAC_MUTEWATE */
#define WM9081_DAC_MUTEMODE                     0x0200  /* DAC_MUTEMODE */
#define WM9081_DAC_MUTEMODE_MASK                0x0200  /* DAC_MUTEMODE */
#define WM9081_DAC_MUTEMODE_SHIFT                    9  /* DAC_MUTEMODE */
#define WM9081_DAC_MUTEMODE_WIDTH                    1  /* DAC_MUTEMODE */
#define WM9081_DAC_MUTE                         0x0008  /* DAC_MUTE */
#define WM9081_DAC_MUTE_MASK                    0x0008  /* DAC_MUTE */
#define WM9081_DAC_MUTE_SHIFT                        3  /* DAC_MUTE */
#define WM9081_DAC_MUTE_WIDTH                        1  /* DAC_MUTE */
#define WM9081_DEEMPH_MASK                      0x0006  /* DEEMPH - [2:1] */
#define WM9081_DEEMPH_SHIFT                          1  /* DEEMPH - [2:1] */
#define WM9081_DEEMPH_WIDTH                          2  /* DEEMPH - [2:1] */

/*
 * W32 (0x20) - DWC 1
 */
#define WM9081_DWC_ENA                          0x8000  /* DWC_ENA */
#define WM9081_DWC_ENA_MASK                     0x8000  /* DWC_ENA */
#define WM9081_DWC_ENA_SHIFT                        15  /* DWC_ENA */
#define WM9081_DWC_ENA_WIDTH                         1  /* DWC_ENA */
#define WM9081_DWC_STAWTUP_GAIN_MASK            0x07C0  /* DWC_STAWTUP_GAIN - [10:6] */
#define WM9081_DWC_STAWTUP_GAIN_SHIFT                6  /* DWC_STAWTUP_GAIN - [10:6] */
#define WM9081_DWC_STAWTUP_GAIN_WIDTH                5  /* DWC_STAWTUP_GAIN - [10:6] */
#define WM9081_DWC_FF_DWY                       0x0020  /* DWC_FF_DWY */
#define WM9081_DWC_FF_DWY_MASK                  0x0020  /* DWC_FF_DWY */
#define WM9081_DWC_FF_DWY_SHIFT                      5  /* DWC_FF_DWY */
#define WM9081_DWC_FF_DWY_WIDTH                      1  /* DWC_FF_DWY */
#define WM9081_DWC_QW                           0x0004  /* DWC_QW */
#define WM9081_DWC_QW_MASK                      0x0004  /* DWC_QW */
#define WM9081_DWC_QW_SHIFT                          2  /* DWC_QW */
#define WM9081_DWC_QW_WIDTH                          1  /* DWC_QW */
#define WM9081_DWC_ANTICWIP                     0x0002  /* DWC_ANTICWIP */
#define WM9081_DWC_ANTICWIP_MASK                0x0002  /* DWC_ANTICWIP */
#define WM9081_DWC_ANTICWIP_SHIFT                    1  /* DWC_ANTICWIP */
#define WM9081_DWC_ANTICWIP_WIDTH                    1  /* DWC_ANTICWIP */

/*
 * W33 (0x21) - DWC 2
 */
#define WM9081_DWC_ATK_MASK                     0xF000  /* DWC_ATK - [15:12] */
#define WM9081_DWC_ATK_SHIFT                        12  /* DWC_ATK - [15:12] */
#define WM9081_DWC_ATK_WIDTH                         4  /* DWC_ATK - [15:12] */
#define WM9081_DWC_DCY_MASK                     0x0F00  /* DWC_DCY - [11:8] */
#define WM9081_DWC_DCY_SHIFT                         8  /* DWC_DCY - [11:8] */
#define WM9081_DWC_DCY_WIDTH                         4  /* DWC_DCY - [11:8] */
#define WM9081_DWC_QW_THW_MASK                  0x00C0  /* DWC_QW_THW - [7:6] */
#define WM9081_DWC_QW_THW_SHIFT                      6  /* DWC_QW_THW - [7:6] */
#define WM9081_DWC_QW_THW_WIDTH                      2  /* DWC_QW_THW - [7:6] */
#define WM9081_DWC_QW_DCY_MASK                  0x0030  /* DWC_QW_DCY - [5:4] */
#define WM9081_DWC_QW_DCY_SHIFT                      4  /* DWC_QW_DCY - [5:4] */
#define WM9081_DWC_QW_DCY_WIDTH                      2  /* DWC_QW_DCY - [5:4] */
#define WM9081_DWC_MINGAIN_MASK                 0x000C  /* DWC_MINGAIN - [3:2] */
#define WM9081_DWC_MINGAIN_SHIFT                     2  /* DWC_MINGAIN - [3:2] */
#define WM9081_DWC_MINGAIN_WIDTH                     2  /* DWC_MINGAIN - [3:2] */
#define WM9081_DWC_MAXGAIN_MASK                 0x0003  /* DWC_MAXGAIN - [1:0] */
#define WM9081_DWC_MAXGAIN_SHIFT                     0  /* DWC_MAXGAIN - [1:0] */
#define WM9081_DWC_MAXGAIN_WIDTH                     2  /* DWC_MAXGAIN - [1:0] */

/*
 * W34 (0x22) - DWC 3
 */
#define WM9081_DWC_HI_COMP_MASK                 0x0038  /* DWC_HI_COMP - [5:3] */
#define WM9081_DWC_HI_COMP_SHIFT                     3  /* DWC_HI_COMP - [5:3] */
#define WM9081_DWC_HI_COMP_WIDTH                     3  /* DWC_HI_COMP - [5:3] */
#define WM9081_DWC_WO_COMP_MASK                 0x0007  /* DWC_WO_COMP - [2:0] */
#define WM9081_DWC_WO_COMP_SHIFT                     0  /* DWC_WO_COMP - [2:0] */
#define WM9081_DWC_WO_COMP_WIDTH                     3  /* DWC_WO_COMP - [2:0] */

/*
 * W35 (0x23) - DWC 4
 */
#define WM9081_DWC_KNEE_IP_MASK                 0x07E0  /* DWC_KNEE_IP - [10:5] */
#define WM9081_DWC_KNEE_IP_SHIFT                     5  /* DWC_KNEE_IP - [10:5] */
#define WM9081_DWC_KNEE_IP_WIDTH                     6  /* DWC_KNEE_IP - [10:5] */
#define WM9081_DWC_KNEE_OP_MASK                 0x001F  /* DWC_KNEE_OP - [4:0] */
#define WM9081_DWC_KNEE_OP_SHIFT                     0  /* DWC_KNEE_OP - [4:0] */
#define WM9081_DWC_KNEE_OP_WIDTH                     5  /* DWC_KNEE_OP - [4:0] */

/*
 * W38 (0x26) - Wwite Sequencew 1
 */
#define WM9081_WSEQ_ENA                         0x8000  /* WSEQ_ENA */
#define WM9081_WSEQ_ENA_MASK                    0x8000  /* WSEQ_ENA */
#define WM9081_WSEQ_ENA_SHIFT                       15  /* WSEQ_ENA */
#define WM9081_WSEQ_ENA_WIDTH                        1  /* WSEQ_ENA */
#define WM9081_WSEQ_ABOWT                       0x0200  /* WSEQ_ABOWT */
#define WM9081_WSEQ_ABOWT_MASK                  0x0200  /* WSEQ_ABOWT */
#define WM9081_WSEQ_ABOWT_SHIFT                      9  /* WSEQ_ABOWT */
#define WM9081_WSEQ_ABOWT_WIDTH                      1  /* WSEQ_ABOWT */
#define WM9081_WSEQ_STAWT                       0x0100  /* WSEQ_STAWT */
#define WM9081_WSEQ_STAWT_MASK                  0x0100  /* WSEQ_STAWT */
#define WM9081_WSEQ_STAWT_SHIFT                      8  /* WSEQ_STAWT */
#define WM9081_WSEQ_STAWT_WIDTH                      1  /* WSEQ_STAWT */
#define WM9081_WSEQ_STAWT_INDEX_MASK            0x007F  /* WSEQ_STAWT_INDEX - [6:0] */
#define WM9081_WSEQ_STAWT_INDEX_SHIFT                0  /* WSEQ_STAWT_INDEX - [6:0] */
#define WM9081_WSEQ_STAWT_INDEX_WIDTH                7  /* WSEQ_STAWT_INDEX - [6:0] */

/*
 * W39 (0x27) - Wwite Sequencew 2
 */
#define WM9081_WSEQ_CUWWENT_INDEX_MASK          0x07F0  /* WSEQ_CUWWENT_INDEX - [10:4] */
#define WM9081_WSEQ_CUWWENT_INDEX_SHIFT              4  /* WSEQ_CUWWENT_INDEX - [10:4] */
#define WM9081_WSEQ_CUWWENT_INDEX_WIDTH              7  /* WSEQ_CUWWENT_INDEX - [10:4] */
#define WM9081_WSEQ_BUSY                        0x0001  /* WSEQ_BUSY */
#define WM9081_WSEQ_BUSY_MASK                   0x0001  /* WSEQ_BUSY */
#define WM9081_WSEQ_BUSY_SHIFT                       0  /* WSEQ_BUSY */
#define WM9081_WSEQ_BUSY_WIDTH                       1  /* WSEQ_BUSY */

/*
 * W40 (0x28) - MW Swave 1
 */
#define WM9081_SPI_CFG                          0x0020  /* SPI_CFG */
#define WM9081_SPI_CFG_MASK                     0x0020  /* SPI_CFG */
#define WM9081_SPI_CFG_SHIFT                         5  /* SPI_CFG */
#define WM9081_SPI_CFG_WIDTH                         1  /* SPI_CFG */
#define WM9081_SPI_4WIWE                        0x0010  /* SPI_4WIWE */
#define WM9081_SPI_4WIWE_MASK                   0x0010  /* SPI_4WIWE */
#define WM9081_SPI_4WIWE_SHIFT                       4  /* SPI_4WIWE */
#define WM9081_SPI_4WIWE_WIDTH                       1  /* SPI_4WIWE */
#define WM9081_AWA_ENA                          0x0008  /* AWA_ENA */
#define WM9081_AWA_ENA_MASK                     0x0008  /* AWA_ENA */
#define WM9081_AWA_ENA_SHIFT                         3  /* AWA_ENA */
#define WM9081_AWA_ENA_WIDTH                         1  /* AWA_ENA */
#define WM9081_AUTO_INC                         0x0002  /* AUTO_INC */
#define WM9081_AUTO_INC_MASK                    0x0002  /* AUTO_INC */
#define WM9081_AUTO_INC_SHIFT                        1  /* AUTO_INC */
#define WM9081_AUTO_INC_WIDTH                        1  /* AUTO_INC */

/*
 * W42 (0x2A) - EQ 1
 */
#define WM9081_EQ_B1_GAIN_MASK                  0xF800  /* EQ_B1_GAIN - [15:11] */
#define WM9081_EQ_B1_GAIN_SHIFT                     11  /* EQ_B1_GAIN - [15:11] */
#define WM9081_EQ_B1_GAIN_WIDTH                      5  /* EQ_B1_GAIN - [15:11] */
#define WM9081_EQ_B2_GAIN_MASK                  0x07C0  /* EQ_B2_GAIN - [10:6] */
#define WM9081_EQ_B2_GAIN_SHIFT                      6  /* EQ_B2_GAIN - [10:6] */
#define WM9081_EQ_B2_GAIN_WIDTH                      5  /* EQ_B2_GAIN - [10:6] */
#define WM9081_EQ_B4_GAIN_MASK                  0x003E  /* EQ_B4_GAIN - [5:1] */
#define WM9081_EQ_B4_GAIN_SHIFT                      1  /* EQ_B4_GAIN - [5:1] */
#define WM9081_EQ_B4_GAIN_WIDTH                      5  /* EQ_B4_GAIN - [5:1] */
#define WM9081_EQ_ENA                           0x0001  /* EQ_ENA */
#define WM9081_EQ_ENA_MASK                      0x0001  /* EQ_ENA */
#define WM9081_EQ_ENA_SHIFT                          0  /* EQ_ENA */
#define WM9081_EQ_ENA_WIDTH                          1  /* EQ_ENA */

/*
 * W43 (0x2B) - EQ 2
 */
#define WM9081_EQ_B3_GAIN_MASK                  0xF800  /* EQ_B3_GAIN - [15:11] */
#define WM9081_EQ_B3_GAIN_SHIFT                     11  /* EQ_B3_GAIN - [15:11] */
#define WM9081_EQ_B3_GAIN_WIDTH                      5  /* EQ_B3_GAIN - [15:11] */
#define WM9081_EQ_B5_GAIN_MASK                  0x07C0  /* EQ_B5_GAIN - [10:6] */
#define WM9081_EQ_B5_GAIN_SHIFT                      6  /* EQ_B5_GAIN - [10:6] */
#define WM9081_EQ_B5_GAIN_WIDTH                      5  /* EQ_B5_GAIN - [10:6] */

/*
 * W44 (0x2C) - EQ 3
 */
#define WM9081_EQ_B1_A_MASK                     0xFFFF  /* EQ_B1_A - [15:0] */
#define WM9081_EQ_B1_A_SHIFT                         0  /* EQ_B1_A - [15:0] */
#define WM9081_EQ_B1_A_WIDTH                        16  /* EQ_B1_A - [15:0] */

/*
 * W45 (0x2D) - EQ 4
 */
#define WM9081_EQ_B1_B_MASK                     0xFFFF  /* EQ_B1_B - [15:0] */
#define WM9081_EQ_B1_B_SHIFT                         0  /* EQ_B1_B - [15:0] */
#define WM9081_EQ_B1_B_WIDTH                        16  /* EQ_B1_B - [15:0] */

/*
 * W46 (0x2E) - EQ 5
 */
#define WM9081_EQ_B1_PG_MASK                    0xFFFF  /* EQ_B1_PG - [15:0] */
#define WM9081_EQ_B1_PG_SHIFT                        0  /* EQ_B1_PG - [15:0] */
#define WM9081_EQ_B1_PG_WIDTH                       16  /* EQ_B1_PG - [15:0] */

/*
 * W47 (0x2F) - EQ 6
 */
#define WM9081_EQ_B2_A_MASK                     0xFFFF  /* EQ_B2_A - [15:0] */
#define WM9081_EQ_B2_A_SHIFT                         0  /* EQ_B2_A - [15:0] */
#define WM9081_EQ_B2_A_WIDTH                        16  /* EQ_B2_A - [15:0] */

/*
 * W48 (0x30) - EQ 7
 */
#define WM9081_EQ_B2_B_MASK                     0xFFFF  /* EQ_B2_B - [15:0] */
#define WM9081_EQ_B2_B_SHIFT                         0  /* EQ_B2_B - [15:0] */
#define WM9081_EQ_B2_B_WIDTH                        16  /* EQ_B2_B - [15:0] */

/*
 * W49 (0x31) - EQ 8
 */
#define WM9081_EQ_B2_C_MASK                     0xFFFF  /* EQ_B2_C - [15:0] */
#define WM9081_EQ_B2_C_SHIFT                         0  /* EQ_B2_C - [15:0] */
#define WM9081_EQ_B2_C_WIDTH                        16  /* EQ_B2_C - [15:0] */

/*
 * W50 (0x32) - EQ 9
 */
#define WM9081_EQ_B2_PG_MASK                    0xFFFF  /* EQ_B2_PG - [15:0] */
#define WM9081_EQ_B2_PG_SHIFT                        0  /* EQ_B2_PG - [15:0] */
#define WM9081_EQ_B2_PG_WIDTH                       16  /* EQ_B2_PG - [15:0] */

/*
 * W51 (0x33) - EQ 10
 */
#define WM9081_EQ_B4_A_MASK                     0xFFFF  /* EQ_B4_A - [15:0] */
#define WM9081_EQ_B4_A_SHIFT                         0  /* EQ_B4_A - [15:0] */
#define WM9081_EQ_B4_A_WIDTH                        16  /* EQ_B4_A - [15:0] */

/*
 * W52 (0x34) - EQ 11
 */
#define WM9081_EQ_B4_B_MASK                     0xFFFF  /* EQ_B4_B - [15:0] */
#define WM9081_EQ_B4_B_SHIFT                         0  /* EQ_B4_B - [15:0] */
#define WM9081_EQ_B4_B_WIDTH                        16  /* EQ_B4_B - [15:0] */

/*
 * W53 (0x35) - EQ 12
 */
#define WM9081_EQ_B4_C_MASK                     0xFFFF  /* EQ_B4_C - [15:0] */
#define WM9081_EQ_B4_C_SHIFT                         0  /* EQ_B4_C - [15:0] */
#define WM9081_EQ_B4_C_WIDTH                        16  /* EQ_B4_C - [15:0] */

/*
 * W54 (0x36) - EQ 13
 */
#define WM9081_EQ_B4_PG_MASK                    0xFFFF  /* EQ_B4_PG - [15:0] */
#define WM9081_EQ_B4_PG_SHIFT                        0  /* EQ_B4_PG - [15:0] */
#define WM9081_EQ_B4_PG_WIDTH                       16  /* EQ_B4_PG - [15:0] */

/*
 * W55 (0x37) - EQ 14
 */
#define WM9081_EQ_B3_A_MASK                     0xFFFF  /* EQ_B3_A - [15:0] */
#define WM9081_EQ_B3_A_SHIFT                         0  /* EQ_B3_A - [15:0] */
#define WM9081_EQ_B3_A_WIDTH                        16  /* EQ_B3_A - [15:0] */

/*
 * W56 (0x38) - EQ 15
 */
#define WM9081_EQ_B3_B_MASK                     0xFFFF  /* EQ_B3_B - [15:0] */
#define WM9081_EQ_B3_B_SHIFT                         0  /* EQ_B3_B - [15:0] */
#define WM9081_EQ_B3_B_WIDTH                        16  /* EQ_B3_B - [15:0] */

/*
 * W57 (0x39) - EQ 16
 */
#define WM9081_EQ_B3_C_MASK                     0xFFFF  /* EQ_B3_C - [15:0] */
#define WM9081_EQ_B3_C_SHIFT                         0  /* EQ_B3_C - [15:0] */
#define WM9081_EQ_B3_C_WIDTH                        16  /* EQ_B3_C - [15:0] */

/*
 * W58 (0x3A) - EQ 17
 */
#define WM9081_EQ_B3_PG_MASK                    0xFFFF  /* EQ_B3_PG - [15:0] */
#define WM9081_EQ_B3_PG_SHIFT                        0  /* EQ_B3_PG - [15:0] */
#define WM9081_EQ_B3_PG_WIDTH                       16  /* EQ_B3_PG - [15:0] */

/*
 * W59 (0x3B) - EQ 18
 */
#define WM9081_EQ_B5_A_MASK                     0xFFFF  /* EQ_B5_A - [15:0] */
#define WM9081_EQ_B5_A_SHIFT                         0  /* EQ_B5_A - [15:0] */
#define WM9081_EQ_B5_A_WIDTH                        16  /* EQ_B5_A - [15:0] */

/*
 * W60 (0x3C) - EQ 19
 */
#define WM9081_EQ_B5_B_MASK                     0xFFFF  /* EQ_B5_B - [15:0] */
#define WM9081_EQ_B5_B_SHIFT                         0  /* EQ_B5_B - [15:0] */
#define WM9081_EQ_B5_B_WIDTH                        16  /* EQ_B5_B - [15:0] */

/*
 * W61 (0x3D) - EQ 20
 */
#define WM9081_EQ_B5_PG_MASK                    0xFFFF  /* EQ_B5_PG - [15:0] */
#define WM9081_EQ_B5_PG_SHIFT                        0  /* EQ_B5_PG - [15:0] */
#define WM9081_EQ_B5_PG_WIDTH                       16  /* EQ_B5_PG - [15:0] */


#endif
