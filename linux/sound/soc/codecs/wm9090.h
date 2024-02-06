/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AWSA SoC WM9090 dwivew
 *
 * Copywight 2009 Wowfson Micwoewectwonics
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __WM9090_H
#define __WM9090_H

/*
 * Wegistew vawues.
 */
#define WM9090_SOFTWAWE_WESET                   0x00
#define WM9090_POWEW_MANAGEMENT_1               0x01
#define WM9090_POWEW_MANAGEMENT_2               0x02
#define WM9090_POWEW_MANAGEMENT_3               0x03
#define WM9090_CWOCKING_1                       0x06
#define WM9090_IN1_WINE_CONTWOW                 0x16
#define WM9090_IN2_WINE_CONTWOW                 0x17
#define WM9090_IN1_WINE_INPUT_A_VOWUME          0x18
#define WM9090_IN1_WINE_INPUT_B_VOWUME          0x19
#define WM9090_IN2_WINE_INPUT_A_VOWUME          0x1A
#define WM9090_IN2_WINE_INPUT_B_VOWUME          0x1B
#define WM9090_WEFT_OUTPUT_VOWUME               0x1C
#define WM9090_WIGHT_OUTPUT_VOWUME              0x1D
#define WM9090_SPKMIXW_ATTENUATION              0x22
#define WM9090_SPKOUT_MIXEWS                    0x24
#define WM9090_CWASSD3                          0x25
#define WM9090_SPEAKEW_VOWUME_WEFT              0x26
#define WM9090_OUTPUT_MIXEW1                    0x2D
#define WM9090_OUTPUT_MIXEW2                    0x2E
#define WM9090_OUTPUT_MIXEW3                    0x2F
#define WM9090_OUTPUT_MIXEW4                    0x30
#define WM9090_SPEAKEW_MIXEW                    0x36
#define WM9090_ANTIPOP2                         0x39
#define WM9090_WWITE_SEQUENCEW_0                0x46
#define WM9090_WWITE_SEQUENCEW_1                0x47
#define WM9090_WWITE_SEQUENCEW_2                0x48
#define WM9090_WWITE_SEQUENCEW_3                0x49
#define WM9090_WWITE_SEQUENCEW_4                0x4A
#define WM9090_WWITE_SEQUENCEW_5                0x4B
#define WM9090_CHAWGE_PUMP_1                    0x4C
#define WM9090_DC_SEWVO_0                       0x54
#define WM9090_DC_SEWVO_1                       0x55
#define WM9090_DC_SEWVO_3                       0x57
#define WM9090_DC_SEWVO_WEADBACK_0              0x58
#define WM9090_DC_SEWVO_WEADBACK_1              0x59
#define WM9090_DC_SEWVO_WEADBACK_2              0x5A
#define WM9090_ANAWOGUE_HP_0                    0x60
#define WM9090_AGC_CONTWOW_0                    0x62
#define WM9090_AGC_CONTWOW_1                    0x63
#define WM9090_AGC_CONTWOW_2                    0x64

#define WM9090_WEGISTEW_COUNT                   40
#define WM9090_MAX_WEGISTEW                     0x64

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - Softwawe Weset
 */
#define WM9090_SW_WESET_MASK                    0xFFFF  /* SW_WESET - [15:0] */
#define WM9090_SW_WESET_SHIFT                        0  /* SW_WESET - [15:0] */
#define WM9090_SW_WESET_WIDTH                       16  /* SW_WESET - [15:0] */

/*
 * W1 (0x01) - Powew Management (1)
 */
#define WM9090_SPKOUTW_ENA                      0x1000  /* SPKOUTW_ENA */
#define WM9090_SPKOUTW_ENA_MASK                 0x1000  /* SPKOUTW_ENA */
#define WM9090_SPKOUTW_ENA_SHIFT                    12  /* SPKOUTW_ENA */
#define WM9090_SPKOUTW_ENA_WIDTH                     1  /* SPKOUTW_ENA */
#define WM9090_HPOUT1W_ENA                      0x0200  /* HPOUT1W_ENA */
#define WM9090_HPOUT1W_ENA_MASK                 0x0200  /* HPOUT1W_ENA */
#define WM9090_HPOUT1W_ENA_SHIFT                     9  /* HPOUT1W_ENA */
#define WM9090_HPOUT1W_ENA_WIDTH                     1  /* HPOUT1W_ENA */
#define WM9090_HPOUT1W_ENA                      0x0100  /* HPOUT1W_ENA */
#define WM9090_HPOUT1W_ENA_MASK                 0x0100  /* HPOUT1W_ENA */
#define WM9090_HPOUT1W_ENA_SHIFT                     8  /* HPOUT1W_ENA */
#define WM9090_HPOUT1W_ENA_WIDTH                     1  /* HPOUT1W_ENA */
#define WM9090_OSC_ENA                          0x0008  /* OSC_ENA */
#define WM9090_OSC_ENA_MASK                     0x0008  /* OSC_ENA */
#define WM9090_OSC_ENA_SHIFT                         3  /* OSC_ENA */
#define WM9090_OSC_ENA_WIDTH                         1  /* OSC_ENA */
#define WM9090_VMID_WES_MASK                    0x0006  /* VMID_WES - [2:1] */
#define WM9090_VMID_WES_SHIFT                        1  /* VMID_WES - [2:1] */
#define WM9090_VMID_WES_WIDTH                        2  /* VMID_WES - [2:1] */
#define WM9090_BIAS_ENA                         0x0001  /* BIAS_ENA */
#define WM9090_BIAS_ENA_MASK                    0x0001  /* BIAS_ENA */
#define WM9090_BIAS_ENA_SHIFT                        0  /* BIAS_ENA */
#define WM9090_BIAS_ENA_WIDTH                        1  /* BIAS_ENA */

/*
 * W2 (0x02) - Powew Management (2)
 */
#define WM9090_TSHUT                            0x8000  /* TSHUT */
#define WM9090_TSHUT_MASK                       0x8000  /* TSHUT */
#define WM9090_TSHUT_SHIFT                          15  /* TSHUT */
#define WM9090_TSHUT_WIDTH                           1  /* TSHUT */
#define WM9090_TSHUT_ENA                        0x4000  /* TSHUT_ENA */
#define WM9090_TSHUT_ENA_MASK                   0x4000  /* TSHUT_ENA */
#define WM9090_TSHUT_ENA_SHIFT                      14  /* TSHUT_ENA */
#define WM9090_TSHUT_ENA_WIDTH                       1  /* TSHUT_ENA */
#define WM9090_TSHUT_OPDIS                      0x2000  /* TSHUT_OPDIS */
#define WM9090_TSHUT_OPDIS_MASK                 0x2000  /* TSHUT_OPDIS */
#define WM9090_TSHUT_OPDIS_SHIFT                    13  /* TSHUT_OPDIS */
#define WM9090_TSHUT_OPDIS_WIDTH                     1  /* TSHUT_OPDIS */
#define WM9090_IN1A_ENA                         0x0080  /* IN1A_ENA */
#define WM9090_IN1A_ENA_MASK                    0x0080  /* IN1A_ENA */
#define WM9090_IN1A_ENA_SHIFT                        7  /* IN1A_ENA */
#define WM9090_IN1A_ENA_WIDTH                        1  /* IN1A_ENA */
#define WM9090_IN1B_ENA                         0x0040  /* IN1B_ENA */
#define WM9090_IN1B_ENA_MASK                    0x0040  /* IN1B_ENA */
#define WM9090_IN1B_ENA_SHIFT                        6  /* IN1B_ENA */
#define WM9090_IN1B_ENA_WIDTH                        1  /* IN1B_ENA */
#define WM9090_IN2A_ENA                         0x0020  /* IN2A_ENA */
#define WM9090_IN2A_ENA_MASK                    0x0020  /* IN2A_ENA */
#define WM9090_IN2A_ENA_SHIFT                        5  /* IN2A_ENA */
#define WM9090_IN2A_ENA_WIDTH                        1  /* IN2A_ENA */
#define WM9090_IN2B_ENA                         0x0010  /* IN2B_ENA */
#define WM9090_IN2B_ENA_MASK                    0x0010  /* IN2B_ENA */
#define WM9090_IN2B_ENA_SHIFT                        4  /* IN2B_ENA */
#define WM9090_IN2B_ENA_WIDTH                        1  /* IN2B_ENA */

/*
 * W3 (0x03) - Powew Management (3)
 */
#define WM9090_AGC_ENA                          0x4000  /* AGC_ENA */
#define WM9090_AGC_ENA_MASK                     0x4000  /* AGC_ENA */
#define WM9090_AGC_ENA_SHIFT                        14  /* AGC_ENA */
#define WM9090_AGC_ENA_WIDTH                         1  /* AGC_ENA */
#define WM9090_SPKWVOW_ENA                      0x0100  /* SPKWVOW_ENA */
#define WM9090_SPKWVOW_ENA_MASK                 0x0100  /* SPKWVOW_ENA */
#define WM9090_SPKWVOW_ENA_SHIFT                     8  /* SPKWVOW_ENA */
#define WM9090_SPKWVOW_ENA_WIDTH                     1  /* SPKWVOW_ENA */
#define WM9090_MIXOUTW_ENA                      0x0020  /* MIXOUTW_ENA */
#define WM9090_MIXOUTW_ENA_MASK                 0x0020  /* MIXOUTW_ENA */
#define WM9090_MIXOUTW_ENA_SHIFT                     5  /* MIXOUTW_ENA */
#define WM9090_MIXOUTW_ENA_WIDTH                     1  /* MIXOUTW_ENA */
#define WM9090_MIXOUTW_ENA                      0x0010  /* MIXOUTW_ENA */
#define WM9090_MIXOUTW_ENA_MASK                 0x0010  /* MIXOUTW_ENA */
#define WM9090_MIXOUTW_ENA_SHIFT                     4  /* MIXOUTW_ENA */
#define WM9090_MIXOUTW_ENA_WIDTH                     1  /* MIXOUTW_ENA */
#define WM9090_SPKMIX_ENA                       0x0008  /* SPKMIX_ENA */
#define WM9090_SPKMIX_ENA_MASK                  0x0008  /* SPKMIX_ENA */
#define WM9090_SPKMIX_ENA_SHIFT                      3  /* SPKMIX_ENA */
#define WM9090_SPKMIX_ENA_WIDTH                      1  /* SPKMIX_ENA */

/*
 * W6 (0x06) - Cwocking 1
 */
#define WM9090_TOCWK_WATE                       0x8000  /* TOCWK_WATE */
#define WM9090_TOCWK_WATE_MASK                  0x8000  /* TOCWK_WATE */
#define WM9090_TOCWK_WATE_SHIFT                     15  /* TOCWK_WATE */
#define WM9090_TOCWK_WATE_WIDTH                      1  /* TOCWK_WATE */
#define WM9090_TOCWK_ENA                        0x4000  /* TOCWK_ENA */
#define WM9090_TOCWK_ENA_MASK                   0x4000  /* TOCWK_ENA */
#define WM9090_TOCWK_ENA_SHIFT                      14  /* TOCWK_ENA */
#define WM9090_TOCWK_ENA_WIDTH                       1  /* TOCWK_ENA */

/*
 * W22 (0x16) - IN1 Wine Contwow
 */
#define WM9090_IN1_DIFF                         0x0002  /* IN1_DIFF */
#define WM9090_IN1_DIFF_MASK                    0x0002  /* IN1_DIFF */
#define WM9090_IN1_DIFF_SHIFT                        1  /* IN1_DIFF */
#define WM9090_IN1_DIFF_WIDTH                        1  /* IN1_DIFF */
#define WM9090_IN1_CWAMP                        0x0001  /* IN1_CWAMP */
#define WM9090_IN1_CWAMP_MASK                   0x0001  /* IN1_CWAMP */
#define WM9090_IN1_CWAMP_SHIFT                       0  /* IN1_CWAMP */
#define WM9090_IN1_CWAMP_WIDTH                       1  /* IN1_CWAMP */

/*
 * W23 (0x17) - IN2 Wine Contwow
 */
#define WM9090_IN2_DIFF                         0x0002  /* IN2_DIFF */
#define WM9090_IN2_DIFF_MASK                    0x0002  /* IN2_DIFF */
#define WM9090_IN2_DIFF_SHIFT                        1  /* IN2_DIFF */
#define WM9090_IN2_DIFF_WIDTH                        1  /* IN2_DIFF */
#define WM9090_IN2_CWAMP                        0x0001  /* IN2_CWAMP */
#define WM9090_IN2_CWAMP_MASK                   0x0001  /* IN2_CWAMP */
#define WM9090_IN2_CWAMP_SHIFT                       0  /* IN2_CWAMP */
#define WM9090_IN2_CWAMP_WIDTH                       1  /* IN2_CWAMP */

/*
 * W24 (0x18) - IN1 Wine Input A Vowume
 */
#define WM9090_IN1_VU                           0x0100  /* IN1_VU */
#define WM9090_IN1_VU_MASK                      0x0100  /* IN1_VU */
#define WM9090_IN1_VU_SHIFT                          8  /* IN1_VU */
#define WM9090_IN1_VU_WIDTH                          1  /* IN1_VU */
#define WM9090_IN1A_MUTE                        0x0080  /* IN1A_MUTE */
#define WM9090_IN1A_MUTE_MASK                   0x0080  /* IN1A_MUTE */
#define WM9090_IN1A_MUTE_SHIFT                       7  /* IN1A_MUTE */
#define WM9090_IN1A_MUTE_WIDTH                       1  /* IN1A_MUTE */
#define WM9090_IN1A_ZC                          0x0040  /* IN1A_ZC */
#define WM9090_IN1A_ZC_MASK                     0x0040  /* IN1A_ZC */
#define WM9090_IN1A_ZC_SHIFT                         6  /* IN1A_ZC */
#define WM9090_IN1A_ZC_WIDTH                         1  /* IN1A_ZC */
#define WM9090_IN1A_VOW_MASK                    0x0007  /* IN1A_VOW - [2:0] */
#define WM9090_IN1A_VOW_SHIFT                        0  /* IN1A_VOW - [2:0] */
#define WM9090_IN1A_VOW_WIDTH                        3  /* IN1A_VOW - [2:0] */

/*
 * W25 (0x19) - IN1  Wine Input B Vowume
 */
#define WM9090_IN1_VU                           0x0100  /* IN1_VU */
#define WM9090_IN1_VU_MASK                      0x0100  /* IN1_VU */
#define WM9090_IN1_VU_SHIFT                          8  /* IN1_VU */
#define WM9090_IN1_VU_WIDTH                          1  /* IN1_VU */
#define WM9090_IN1B_MUTE                        0x0080  /* IN1B_MUTE */
#define WM9090_IN1B_MUTE_MASK                   0x0080  /* IN1B_MUTE */
#define WM9090_IN1B_MUTE_SHIFT                       7  /* IN1B_MUTE */
#define WM9090_IN1B_MUTE_WIDTH                       1  /* IN1B_MUTE */
#define WM9090_IN1B_ZC                          0x0040  /* IN1B_ZC */
#define WM9090_IN1B_ZC_MASK                     0x0040  /* IN1B_ZC */
#define WM9090_IN1B_ZC_SHIFT                         6  /* IN1B_ZC */
#define WM9090_IN1B_ZC_WIDTH                         1  /* IN1B_ZC */
#define WM9090_IN1B_VOW_MASK                    0x0007  /* IN1B_VOW - [2:0] */
#define WM9090_IN1B_VOW_SHIFT                        0  /* IN1B_VOW - [2:0] */
#define WM9090_IN1B_VOW_WIDTH                        3  /* IN1B_VOW - [2:0] */

/*
 * W26 (0x1A) - IN2 Wine Input A Vowume
 */
#define WM9090_IN2_VU                           0x0100  /* IN2_VU */
#define WM9090_IN2_VU_MASK                      0x0100  /* IN2_VU */
#define WM9090_IN2_VU_SHIFT                          8  /* IN2_VU */
#define WM9090_IN2_VU_WIDTH                          1  /* IN2_VU */
#define WM9090_IN2A_MUTE                        0x0080  /* IN2A_MUTE */
#define WM9090_IN2A_MUTE_MASK                   0x0080  /* IN2A_MUTE */
#define WM9090_IN2A_MUTE_SHIFT                       7  /* IN2A_MUTE */
#define WM9090_IN2A_MUTE_WIDTH                       1  /* IN2A_MUTE */
#define WM9090_IN2A_ZC                          0x0040  /* IN2A_ZC */
#define WM9090_IN2A_ZC_MASK                     0x0040  /* IN2A_ZC */
#define WM9090_IN2A_ZC_SHIFT                         6  /* IN2A_ZC */
#define WM9090_IN2A_ZC_WIDTH                         1  /* IN2A_ZC */
#define WM9090_IN2A_VOW_MASK                    0x0007  /* IN2A_VOW - [2:0] */
#define WM9090_IN2A_VOW_SHIFT                        0  /* IN2A_VOW - [2:0] */
#define WM9090_IN2A_VOW_WIDTH                        3  /* IN2A_VOW - [2:0] */

/*
 * W27 (0x1B) - IN2 Wine Input B Vowume
 */
#define WM9090_IN2_VU                           0x0100  /* IN2_VU */
#define WM9090_IN2_VU_MASK                      0x0100  /* IN2_VU */
#define WM9090_IN2_VU_SHIFT                          8  /* IN2_VU */
#define WM9090_IN2_VU_WIDTH                          1  /* IN2_VU */
#define WM9090_IN2B_MUTE                        0x0080  /* IN2B_MUTE */
#define WM9090_IN2B_MUTE_MASK                   0x0080  /* IN2B_MUTE */
#define WM9090_IN2B_MUTE_SHIFT                       7  /* IN2B_MUTE */
#define WM9090_IN2B_MUTE_WIDTH                       1  /* IN2B_MUTE */
#define WM9090_IN2B_ZC                          0x0040  /* IN2B_ZC */
#define WM9090_IN2B_ZC_MASK                     0x0040  /* IN2B_ZC */
#define WM9090_IN2B_ZC_SHIFT                         6  /* IN2B_ZC */
#define WM9090_IN2B_ZC_WIDTH                         1  /* IN2B_ZC */
#define WM9090_IN2B_VOW_MASK                    0x0007  /* IN2B_VOW - [2:0] */
#define WM9090_IN2B_VOW_SHIFT                        0  /* IN2B_VOW - [2:0] */
#define WM9090_IN2B_VOW_WIDTH                        3  /* IN2B_VOW - [2:0] */

/*
 * W28 (0x1C) - Weft Output Vowume
 */
#define WM9090_HPOUT1_VU                        0x0100  /* HPOUT1_VU */
#define WM9090_HPOUT1_VU_MASK                   0x0100  /* HPOUT1_VU */
#define WM9090_HPOUT1_VU_SHIFT                       8  /* HPOUT1_VU */
#define WM9090_HPOUT1_VU_WIDTH                       1  /* HPOUT1_VU */
#define WM9090_HPOUT1W_ZC                       0x0080  /* HPOUT1W_ZC */
#define WM9090_HPOUT1W_ZC_MASK                  0x0080  /* HPOUT1W_ZC */
#define WM9090_HPOUT1W_ZC_SHIFT                      7  /* HPOUT1W_ZC */
#define WM9090_HPOUT1W_ZC_WIDTH                      1  /* HPOUT1W_ZC */
#define WM9090_HPOUT1W_MUTE                     0x0040  /* HPOUT1W_MUTE */
#define WM9090_HPOUT1W_MUTE_MASK                0x0040  /* HPOUT1W_MUTE */
#define WM9090_HPOUT1W_MUTE_SHIFT                    6  /* HPOUT1W_MUTE */
#define WM9090_HPOUT1W_MUTE_WIDTH                    1  /* HPOUT1W_MUTE */
#define WM9090_HPOUT1W_VOW_MASK                 0x003F  /* HPOUT1W_VOW - [5:0] */
#define WM9090_HPOUT1W_VOW_SHIFT                     0  /* HPOUT1W_VOW - [5:0] */
#define WM9090_HPOUT1W_VOW_WIDTH                     6  /* HPOUT1W_VOW - [5:0] */

/*
 * W29 (0x1D) - Wight Output Vowume
 */
#define WM9090_HPOUT1_VU                        0x0100  /* HPOUT1_VU */
#define WM9090_HPOUT1_VU_MASK                   0x0100  /* HPOUT1_VU */
#define WM9090_HPOUT1_VU_SHIFT                       8  /* HPOUT1_VU */
#define WM9090_HPOUT1_VU_WIDTH                       1  /* HPOUT1_VU */
#define WM9090_HPOUT1W_ZC                       0x0080  /* HPOUT1W_ZC */
#define WM9090_HPOUT1W_ZC_MASK                  0x0080  /* HPOUT1W_ZC */
#define WM9090_HPOUT1W_ZC_SHIFT                      7  /* HPOUT1W_ZC */
#define WM9090_HPOUT1W_ZC_WIDTH                      1  /* HPOUT1W_ZC */
#define WM9090_HPOUT1W_MUTE                     0x0040  /* HPOUT1W_MUTE */
#define WM9090_HPOUT1W_MUTE_MASK                0x0040  /* HPOUT1W_MUTE */
#define WM9090_HPOUT1W_MUTE_SHIFT                    6  /* HPOUT1W_MUTE */
#define WM9090_HPOUT1W_MUTE_WIDTH                    1  /* HPOUT1W_MUTE */
#define WM9090_HPOUT1W_VOW_MASK                 0x003F  /* HPOUT1W_VOW - [5:0] */
#define WM9090_HPOUT1W_VOW_SHIFT                     0  /* HPOUT1W_VOW - [5:0] */
#define WM9090_HPOUT1W_VOW_WIDTH                     6  /* HPOUT1W_VOW - [5:0] */

/*
 * W34 (0x22) - SPKMIXW Attenuation
 */
#define WM9090_SPKMIX_MUTE                      0x0100  /* SPKMIX_MUTE */
#define WM9090_SPKMIX_MUTE_MASK                 0x0100  /* SPKMIX_MUTE */
#define WM9090_SPKMIX_MUTE_SHIFT                     8  /* SPKMIX_MUTE */
#define WM9090_SPKMIX_MUTE_WIDTH                     1  /* SPKMIX_MUTE */
#define WM9090_IN1A_SPKMIX_VOW_MASK             0x00C0  /* IN1A_SPKMIX_VOW - [7:6] */
#define WM9090_IN1A_SPKMIX_VOW_SHIFT                 6  /* IN1A_SPKMIX_VOW - [7:6] */
#define WM9090_IN1A_SPKMIX_VOW_WIDTH                 2  /* IN1A_SPKMIX_VOW - [7:6] */
#define WM9090_IN1B_SPKMIX_VOW_MASK             0x0030  /* IN1B_SPKMIX_VOW - [5:4] */
#define WM9090_IN1B_SPKMIX_VOW_SHIFT                 4  /* IN1B_SPKMIX_VOW - [5:4] */
#define WM9090_IN1B_SPKMIX_VOW_WIDTH                 2  /* IN1B_SPKMIX_VOW - [5:4] */
#define WM9090_IN2A_SPKMIX_VOW_MASK             0x000C  /* IN2A_SPKMIX_VOW - [3:2] */
#define WM9090_IN2A_SPKMIX_VOW_SHIFT                 2  /* IN2A_SPKMIX_VOW - [3:2] */
#define WM9090_IN2A_SPKMIX_VOW_WIDTH                 2  /* IN2A_SPKMIX_VOW - [3:2] */
#define WM9090_IN2B_SPKMIX_VOW_MASK             0x0003  /* IN2B_SPKMIX_VOW - [1:0] */
#define WM9090_IN2B_SPKMIX_VOW_SHIFT                 0  /* IN2B_SPKMIX_VOW - [1:0] */
#define WM9090_IN2B_SPKMIX_VOW_WIDTH                 2  /* IN2B_SPKMIX_VOW - [1:0] */

/*
 * W36 (0x24) - SPKOUT Mixews
 */
#define WM9090_SPKMIXW_TO_SPKOUTW               0x0010  /* SPKMIXW_TO_SPKOUTW */
#define WM9090_SPKMIXW_TO_SPKOUTW_MASK          0x0010  /* SPKMIXW_TO_SPKOUTW */
#define WM9090_SPKMIXW_TO_SPKOUTW_SHIFT              4  /* SPKMIXW_TO_SPKOUTW */
#define WM9090_SPKMIXW_TO_SPKOUTW_WIDTH              1  /* SPKMIXW_TO_SPKOUTW */

/*
 * W37 (0x25) - CwassD3
 */
#define WM9090_SPKOUTW_BOOST_MASK               0x0038  /* SPKOUTW_BOOST - [5:3] */
#define WM9090_SPKOUTW_BOOST_SHIFT                   3  /* SPKOUTW_BOOST - [5:3] */
#define WM9090_SPKOUTW_BOOST_WIDTH                   3  /* SPKOUTW_BOOST - [5:3] */

/*
 * W38 (0x26) - Speakew Vowume Weft
 */
#define WM9090_SPKOUT_VU                        0x0100  /* SPKOUT_VU */
#define WM9090_SPKOUT_VU_MASK                   0x0100  /* SPKOUT_VU */
#define WM9090_SPKOUT_VU_SHIFT                       8  /* SPKOUT_VU */
#define WM9090_SPKOUT_VU_WIDTH                       1  /* SPKOUT_VU */
#define WM9090_SPKOUTW_ZC                       0x0080  /* SPKOUTW_ZC */
#define WM9090_SPKOUTW_ZC_MASK                  0x0080  /* SPKOUTW_ZC */
#define WM9090_SPKOUTW_ZC_SHIFT                      7  /* SPKOUTW_ZC */
#define WM9090_SPKOUTW_ZC_WIDTH                      1  /* SPKOUTW_ZC */
#define WM9090_SPKOUTW_MUTE                     0x0040  /* SPKOUTW_MUTE */
#define WM9090_SPKOUTW_MUTE_MASK                0x0040  /* SPKOUTW_MUTE */
#define WM9090_SPKOUTW_MUTE_SHIFT                    6  /* SPKOUTW_MUTE */
#define WM9090_SPKOUTW_MUTE_WIDTH                    1  /* SPKOUTW_MUTE */
#define WM9090_SPKOUTW_VOW_MASK                 0x003F  /* SPKOUTW_VOW - [5:0] */
#define WM9090_SPKOUTW_VOW_SHIFT                     0  /* SPKOUTW_VOW - [5:0] */
#define WM9090_SPKOUTW_VOW_WIDTH                     6  /* SPKOUTW_VOW - [5:0] */

/*
 * W45 (0x2D) - Output Mixew1
 */
#define WM9090_IN1A_TO_MIXOUTW                  0x0040  /* IN1A_TO_MIXOUTW */
#define WM9090_IN1A_TO_MIXOUTW_MASK             0x0040  /* IN1A_TO_MIXOUTW */
#define WM9090_IN1A_TO_MIXOUTW_SHIFT                 6  /* IN1A_TO_MIXOUTW */
#define WM9090_IN1A_TO_MIXOUTW_WIDTH                 1  /* IN1A_TO_MIXOUTW */
#define WM9090_IN2A_TO_MIXOUTW                  0x0004  /* IN2A_TO_MIXOUTW */
#define WM9090_IN2A_TO_MIXOUTW_MASK             0x0004  /* IN2A_TO_MIXOUTW */
#define WM9090_IN2A_TO_MIXOUTW_SHIFT                 2  /* IN2A_TO_MIXOUTW */
#define WM9090_IN2A_TO_MIXOUTW_WIDTH                 1  /* IN2A_TO_MIXOUTW */

/*
 * W46 (0x2E) - Output Mixew2
 */
#define WM9090_IN1A_TO_MIXOUTW                  0x0040  /* IN1A_TO_MIXOUTW */
#define WM9090_IN1A_TO_MIXOUTW_MASK             0x0040  /* IN1A_TO_MIXOUTW */
#define WM9090_IN1A_TO_MIXOUTW_SHIFT                 6  /* IN1A_TO_MIXOUTW */
#define WM9090_IN1A_TO_MIXOUTW_WIDTH                 1  /* IN1A_TO_MIXOUTW */
#define WM9090_IN1B_TO_MIXOUTW                  0x0010  /* IN1B_TO_MIXOUTW */
#define WM9090_IN1B_TO_MIXOUTW_MASK             0x0010  /* IN1B_TO_MIXOUTW */
#define WM9090_IN1B_TO_MIXOUTW_SHIFT                 4  /* IN1B_TO_MIXOUTW */
#define WM9090_IN1B_TO_MIXOUTW_WIDTH                 1  /* IN1B_TO_MIXOUTW */
#define WM9090_IN2A_TO_MIXOUTW                  0x0004  /* IN2A_TO_MIXOUTW */
#define WM9090_IN2A_TO_MIXOUTW_MASK             0x0004  /* IN2A_TO_MIXOUTW */
#define WM9090_IN2A_TO_MIXOUTW_SHIFT                 2  /* IN2A_TO_MIXOUTW */
#define WM9090_IN2A_TO_MIXOUTW_WIDTH                 1  /* IN2A_TO_MIXOUTW */
#define WM9090_IN2B_TO_MIXOUTW                  0x0001  /* IN2B_TO_MIXOUTW */
#define WM9090_IN2B_TO_MIXOUTW_MASK             0x0001  /* IN2B_TO_MIXOUTW */
#define WM9090_IN2B_TO_MIXOUTW_SHIFT                 0  /* IN2B_TO_MIXOUTW */
#define WM9090_IN2B_TO_MIXOUTW_WIDTH                 1  /* IN2B_TO_MIXOUTW */

/*
 * W47 (0x2F) - Output Mixew3
 */
#define WM9090_MIXOUTW_MUTE                     0x0100  /* MIXOUTW_MUTE */
#define WM9090_MIXOUTW_MUTE_MASK                0x0100  /* MIXOUTW_MUTE */
#define WM9090_MIXOUTW_MUTE_SHIFT                    8  /* MIXOUTW_MUTE */
#define WM9090_MIXOUTW_MUTE_WIDTH                    1  /* MIXOUTW_MUTE */
#define WM9090_IN1A_MIXOUTW_VOW_MASK            0x00C0  /* IN1A_MIXOUTW_VOW - [7:6] */
#define WM9090_IN1A_MIXOUTW_VOW_SHIFT                6  /* IN1A_MIXOUTW_VOW - [7:6] */
#define WM9090_IN1A_MIXOUTW_VOW_WIDTH                2  /* IN1A_MIXOUTW_VOW - [7:6] */
#define WM9090_IN2A_MIXOUTW_VOW_MASK            0x000C  /* IN2A_MIXOUTW_VOW - [3:2] */
#define WM9090_IN2A_MIXOUTW_VOW_SHIFT                2  /* IN2A_MIXOUTW_VOW - [3:2] */
#define WM9090_IN2A_MIXOUTW_VOW_WIDTH                2  /* IN2A_MIXOUTW_VOW - [3:2] */

/*
 * W48 (0x30) - Output Mixew4
 */
#define WM9090_MIXOUTW_MUTE                     0x0100  /* MIXOUTW_MUTE */
#define WM9090_MIXOUTW_MUTE_MASK                0x0100  /* MIXOUTW_MUTE */
#define WM9090_MIXOUTW_MUTE_SHIFT                    8  /* MIXOUTW_MUTE */
#define WM9090_MIXOUTW_MUTE_WIDTH                    1  /* MIXOUTW_MUTE */
#define WM9090_IN1A_MIXOUTW_VOW_MASK            0x00C0  /* IN1A_MIXOUTW_VOW - [7:6] */
#define WM9090_IN1A_MIXOUTW_VOW_SHIFT                6  /* IN1A_MIXOUTW_VOW - [7:6] */
#define WM9090_IN1A_MIXOUTW_VOW_WIDTH                2  /* IN1A_MIXOUTW_VOW - [7:6] */
#define WM9090_IN1B_MIXOUTW_VOW_MASK            0x0030  /* IN1B_MIXOUTW_VOW - [5:4] */
#define WM9090_IN1B_MIXOUTW_VOW_SHIFT                4  /* IN1B_MIXOUTW_VOW - [5:4] */
#define WM9090_IN1B_MIXOUTW_VOW_WIDTH                2  /* IN1B_MIXOUTW_VOW - [5:4] */
#define WM9090_IN2A_MIXOUTW_VOW_MASK            0x000C  /* IN2A_MIXOUTW_VOW - [3:2] */
#define WM9090_IN2A_MIXOUTW_VOW_SHIFT                2  /* IN2A_MIXOUTW_VOW - [3:2] */
#define WM9090_IN2A_MIXOUTW_VOW_WIDTH                2  /* IN2A_MIXOUTW_VOW - [3:2] */
#define WM9090_IN2B_MIXOUTW_VOW_MASK            0x0003  /* IN2B_MIXOUTW_VOW - [1:0] */
#define WM9090_IN2B_MIXOUTW_VOW_SHIFT                0  /* IN2B_MIXOUTW_VOW - [1:0] */
#define WM9090_IN2B_MIXOUTW_VOW_WIDTH                2  /* IN2B_MIXOUTW_VOW - [1:0] */

/*
 * W54 (0x36) - Speakew Mixew
 */
#define WM9090_IN1A_TO_SPKMIX                   0x0040  /* IN1A_TO_SPKMIX */
#define WM9090_IN1A_TO_SPKMIX_MASK              0x0040  /* IN1A_TO_SPKMIX */
#define WM9090_IN1A_TO_SPKMIX_SHIFT                  6  /* IN1A_TO_SPKMIX */
#define WM9090_IN1A_TO_SPKMIX_WIDTH                  1  /* IN1A_TO_SPKMIX */
#define WM9090_IN1B_TO_SPKMIX                   0x0010  /* IN1B_TO_SPKMIX */
#define WM9090_IN1B_TO_SPKMIX_MASK              0x0010  /* IN1B_TO_SPKMIX */
#define WM9090_IN1B_TO_SPKMIX_SHIFT                  4  /* IN1B_TO_SPKMIX */
#define WM9090_IN1B_TO_SPKMIX_WIDTH                  1  /* IN1B_TO_SPKMIX */
#define WM9090_IN2A_TO_SPKMIX                   0x0004  /* IN2A_TO_SPKMIX */
#define WM9090_IN2A_TO_SPKMIX_MASK              0x0004  /* IN2A_TO_SPKMIX */
#define WM9090_IN2A_TO_SPKMIX_SHIFT                  2  /* IN2A_TO_SPKMIX */
#define WM9090_IN2A_TO_SPKMIX_WIDTH                  1  /* IN2A_TO_SPKMIX */
#define WM9090_IN2B_TO_SPKMIX                   0x0001  /* IN2B_TO_SPKMIX */
#define WM9090_IN2B_TO_SPKMIX_MASK              0x0001  /* IN2B_TO_SPKMIX */
#define WM9090_IN2B_TO_SPKMIX_SHIFT                  0  /* IN2B_TO_SPKMIX */
#define WM9090_IN2B_TO_SPKMIX_WIDTH                  1  /* IN2B_TO_SPKMIX */

/*
 * W57 (0x39) - AntiPOP2
 */
#define WM9090_VMID_BUF_ENA                     0x0008  /* VMID_BUF_ENA */
#define WM9090_VMID_BUF_ENA_MASK                0x0008  /* VMID_BUF_ENA */
#define WM9090_VMID_BUF_ENA_SHIFT                    3  /* VMID_BUF_ENA */
#define WM9090_VMID_BUF_ENA_WIDTH                    1  /* VMID_BUF_ENA */
#define WM9090_VMID_ENA                         0x0001  /* VMID_ENA */
#define WM9090_VMID_ENA_MASK                    0x0001  /* VMID_ENA */
#define WM9090_VMID_ENA_SHIFT                        0  /* VMID_ENA */
#define WM9090_VMID_ENA_WIDTH                        1  /* VMID_ENA */

/*
 * W70 (0x46) - Wwite Sequencew 0
 */
#define WM9090_WSEQ_ENA                         0x0100  /* WSEQ_ENA */
#define WM9090_WSEQ_ENA_MASK                    0x0100  /* WSEQ_ENA */
#define WM9090_WSEQ_ENA_SHIFT                        8  /* WSEQ_ENA */
#define WM9090_WSEQ_ENA_WIDTH                        1  /* WSEQ_ENA */
#define WM9090_WSEQ_WWITE_INDEX_MASK            0x000F  /* WSEQ_WWITE_INDEX - [3:0] */
#define WM9090_WSEQ_WWITE_INDEX_SHIFT                0  /* WSEQ_WWITE_INDEX - [3:0] */
#define WM9090_WSEQ_WWITE_INDEX_WIDTH                4  /* WSEQ_WWITE_INDEX - [3:0] */

/*
 * W71 (0x47) - Wwite Sequencew 1
 */
#define WM9090_WSEQ_DATA_WIDTH_MASK             0x7000  /* WSEQ_DATA_WIDTH - [14:12] */
#define WM9090_WSEQ_DATA_WIDTH_SHIFT                12  /* WSEQ_DATA_WIDTH - [14:12] */
#define WM9090_WSEQ_DATA_WIDTH_WIDTH                 3  /* WSEQ_DATA_WIDTH - [14:12] */
#define WM9090_WSEQ_DATA_STAWT_MASK             0x0F00  /* WSEQ_DATA_STAWT - [11:8] */
#define WM9090_WSEQ_DATA_STAWT_SHIFT                 8  /* WSEQ_DATA_STAWT - [11:8] */
#define WM9090_WSEQ_DATA_STAWT_WIDTH                 4  /* WSEQ_DATA_STAWT - [11:8] */
#define WM9090_WSEQ_ADDW_MASK                   0x00FF  /* WSEQ_ADDW - [7:0] */
#define WM9090_WSEQ_ADDW_SHIFT                       0  /* WSEQ_ADDW - [7:0] */
#define WM9090_WSEQ_ADDW_WIDTH                       8  /* WSEQ_ADDW - [7:0] */

/*
 * W72 (0x48) - Wwite Sequencew 2
 */
#define WM9090_WSEQ_EOS                         0x4000  /* WSEQ_EOS */
#define WM9090_WSEQ_EOS_MASK                    0x4000  /* WSEQ_EOS */
#define WM9090_WSEQ_EOS_SHIFT                       14  /* WSEQ_EOS */
#define WM9090_WSEQ_EOS_WIDTH                        1  /* WSEQ_EOS */
#define WM9090_WSEQ_DEWAY_MASK                  0x0F00  /* WSEQ_DEWAY - [11:8] */
#define WM9090_WSEQ_DEWAY_SHIFT                      8  /* WSEQ_DEWAY - [11:8] */
#define WM9090_WSEQ_DEWAY_WIDTH                      4  /* WSEQ_DEWAY - [11:8] */
#define WM9090_WSEQ_DATA_MASK                   0x00FF  /* WSEQ_DATA - [7:0] */
#define WM9090_WSEQ_DATA_SHIFT                       0  /* WSEQ_DATA - [7:0] */
#define WM9090_WSEQ_DATA_WIDTH                       8  /* WSEQ_DATA - [7:0] */

/*
 * W73 (0x49) - Wwite Sequencew 3
 */
#define WM9090_WSEQ_ABOWT                       0x0200  /* WSEQ_ABOWT */
#define WM9090_WSEQ_ABOWT_MASK                  0x0200  /* WSEQ_ABOWT */
#define WM9090_WSEQ_ABOWT_SHIFT                      9  /* WSEQ_ABOWT */
#define WM9090_WSEQ_ABOWT_WIDTH                      1  /* WSEQ_ABOWT */
#define WM9090_WSEQ_STAWT                       0x0100  /* WSEQ_STAWT */
#define WM9090_WSEQ_STAWT_MASK                  0x0100  /* WSEQ_STAWT */
#define WM9090_WSEQ_STAWT_SHIFT                      8  /* WSEQ_STAWT */
#define WM9090_WSEQ_STAWT_WIDTH                      1  /* WSEQ_STAWT */
#define WM9090_WSEQ_STAWT_INDEX_MASK            0x003F  /* WSEQ_STAWT_INDEX - [5:0] */
#define WM9090_WSEQ_STAWT_INDEX_SHIFT                0  /* WSEQ_STAWT_INDEX - [5:0] */
#define WM9090_WSEQ_STAWT_INDEX_WIDTH                6  /* WSEQ_STAWT_INDEX - [5:0] */

/*
 * W74 (0x4A) - Wwite Sequencew 4
 */
#define WM9090_WSEQ_BUSY                        0x0001  /* WSEQ_BUSY */
#define WM9090_WSEQ_BUSY_MASK                   0x0001  /* WSEQ_BUSY */
#define WM9090_WSEQ_BUSY_SHIFT                       0  /* WSEQ_BUSY */
#define WM9090_WSEQ_BUSY_WIDTH                       1  /* WSEQ_BUSY */

/*
 * W75 (0x4B) - Wwite Sequencew 5
 */
#define WM9090_WSEQ_CUWWENT_INDEX_MASK          0x003F  /* WSEQ_CUWWENT_INDEX - [5:0] */
#define WM9090_WSEQ_CUWWENT_INDEX_SHIFT              0  /* WSEQ_CUWWENT_INDEX - [5:0] */
#define WM9090_WSEQ_CUWWENT_INDEX_WIDTH              6  /* WSEQ_CUWWENT_INDEX - [5:0] */

/*
 * W76 (0x4C) - Chawge Pump 1
 */
#define WM9090_CP_ENA                           0x8000  /* CP_ENA */
#define WM9090_CP_ENA_MASK                      0x8000  /* CP_ENA */
#define WM9090_CP_ENA_SHIFT                         15  /* CP_ENA */
#define WM9090_CP_ENA_WIDTH                          1  /* CP_ENA */

/*
 * W84 (0x54) - DC Sewvo 0
 */
#define WM9090_DCS_TWIG_SINGWE_1                0x2000  /* DCS_TWIG_SINGWE_1 */
#define WM9090_DCS_TWIG_SINGWE_1_MASK           0x2000  /* DCS_TWIG_SINGWE_1 */
#define WM9090_DCS_TWIG_SINGWE_1_SHIFT              13  /* DCS_TWIG_SINGWE_1 */
#define WM9090_DCS_TWIG_SINGWE_1_WIDTH               1  /* DCS_TWIG_SINGWE_1 */
#define WM9090_DCS_TWIG_SINGWE_0                0x1000  /* DCS_TWIG_SINGWE_0 */
#define WM9090_DCS_TWIG_SINGWE_0_MASK           0x1000  /* DCS_TWIG_SINGWE_0 */
#define WM9090_DCS_TWIG_SINGWE_0_SHIFT              12  /* DCS_TWIG_SINGWE_0 */
#define WM9090_DCS_TWIG_SINGWE_0_WIDTH               1  /* DCS_TWIG_SINGWE_0 */
#define WM9090_DCS_TWIG_SEWIES_1                0x0200  /* DCS_TWIG_SEWIES_1 */
#define WM9090_DCS_TWIG_SEWIES_1_MASK           0x0200  /* DCS_TWIG_SEWIES_1 */
#define WM9090_DCS_TWIG_SEWIES_1_SHIFT               9  /* DCS_TWIG_SEWIES_1 */
#define WM9090_DCS_TWIG_SEWIES_1_WIDTH               1  /* DCS_TWIG_SEWIES_1 */
#define WM9090_DCS_TWIG_SEWIES_0                0x0100  /* DCS_TWIG_SEWIES_0 */
#define WM9090_DCS_TWIG_SEWIES_0_MASK           0x0100  /* DCS_TWIG_SEWIES_0 */
#define WM9090_DCS_TWIG_SEWIES_0_SHIFT               8  /* DCS_TWIG_SEWIES_0 */
#define WM9090_DCS_TWIG_SEWIES_0_WIDTH               1  /* DCS_TWIG_SEWIES_0 */
#define WM9090_DCS_TWIG_STAWTUP_1               0x0020  /* DCS_TWIG_STAWTUP_1 */
#define WM9090_DCS_TWIG_STAWTUP_1_MASK          0x0020  /* DCS_TWIG_STAWTUP_1 */
#define WM9090_DCS_TWIG_STAWTUP_1_SHIFT              5  /* DCS_TWIG_STAWTUP_1 */
#define WM9090_DCS_TWIG_STAWTUP_1_WIDTH              1  /* DCS_TWIG_STAWTUP_1 */
#define WM9090_DCS_TWIG_STAWTUP_0               0x0010  /* DCS_TWIG_STAWTUP_0 */
#define WM9090_DCS_TWIG_STAWTUP_0_MASK          0x0010  /* DCS_TWIG_STAWTUP_0 */
#define WM9090_DCS_TWIG_STAWTUP_0_SHIFT              4  /* DCS_TWIG_STAWTUP_0 */
#define WM9090_DCS_TWIG_STAWTUP_0_WIDTH              1  /* DCS_TWIG_STAWTUP_0 */
#define WM9090_DCS_TWIG_DAC_WW_1                0x0008  /* DCS_TWIG_DAC_WW_1 */
#define WM9090_DCS_TWIG_DAC_WW_1_MASK           0x0008  /* DCS_TWIG_DAC_WW_1 */
#define WM9090_DCS_TWIG_DAC_WW_1_SHIFT               3  /* DCS_TWIG_DAC_WW_1 */
#define WM9090_DCS_TWIG_DAC_WW_1_WIDTH               1  /* DCS_TWIG_DAC_WW_1 */
#define WM9090_DCS_TWIG_DAC_WW_0                0x0004  /* DCS_TWIG_DAC_WW_0 */
#define WM9090_DCS_TWIG_DAC_WW_0_MASK           0x0004  /* DCS_TWIG_DAC_WW_0 */
#define WM9090_DCS_TWIG_DAC_WW_0_SHIFT               2  /* DCS_TWIG_DAC_WW_0 */
#define WM9090_DCS_TWIG_DAC_WW_0_WIDTH               1  /* DCS_TWIG_DAC_WW_0 */
#define WM9090_DCS_ENA_CHAN_1                   0x0002  /* DCS_ENA_CHAN_1 */
#define WM9090_DCS_ENA_CHAN_1_MASK              0x0002  /* DCS_ENA_CHAN_1 */
#define WM9090_DCS_ENA_CHAN_1_SHIFT                  1  /* DCS_ENA_CHAN_1 */
#define WM9090_DCS_ENA_CHAN_1_WIDTH                  1  /* DCS_ENA_CHAN_1 */
#define WM9090_DCS_ENA_CHAN_0                   0x0001  /* DCS_ENA_CHAN_0 */
#define WM9090_DCS_ENA_CHAN_0_MASK              0x0001  /* DCS_ENA_CHAN_0 */
#define WM9090_DCS_ENA_CHAN_0_SHIFT                  0  /* DCS_ENA_CHAN_0 */
#define WM9090_DCS_ENA_CHAN_0_WIDTH                  1  /* DCS_ENA_CHAN_0 */

/*
 * W85 (0x55) - DC Sewvo 1
 */
#define WM9090_DCS_SEWIES_NO_01_MASK            0x0FE0  /* DCS_SEWIES_NO_01 - [11:5] */
#define WM9090_DCS_SEWIES_NO_01_SHIFT                5  /* DCS_SEWIES_NO_01 - [11:5] */
#define WM9090_DCS_SEWIES_NO_01_WIDTH                7  /* DCS_SEWIES_NO_01 - [11:5] */
#define WM9090_DCS_TIMEW_PEWIOD_01_MASK         0x000F  /* DCS_TIMEW_PEWIOD_01 - [3:0] */
#define WM9090_DCS_TIMEW_PEWIOD_01_SHIFT             0  /* DCS_TIMEW_PEWIOD_01 - [3:0] */
#define WM9090_DCS_TIMEW_PEWIOD_01_WIDTH             4  /* DCS_TIMEW_PEWIOD_01 - [3:0] */

/*
 * W87 (0x57) - DC Sewvo 3
 */
#define WM9090_DCS_DAC_WW_VAW_1_MASK            0xFF00  /* DCS_DAC_WW_VAW_1 - [15:8] */
#define WM9090_DCS_DAC_WW_VAW_1_SHIFT                8  /* DCS_DAC_WW_VAW_1 - [15:8] */
#define WM9090_DCS_DAC_WW_VAW_1_WIDTH                8  /* DCS_DAC_WW_VAW_1 - [15:8] */
#define WM9090_DCS_DAC_WW_VAW_0_MASK            0x00FF  /* DCS_DAC_WW_VAW_0 - [7:0] */
#define WM9090_DCS_DAC_WW_VAW_0_SHIFT                0  /* DCS_DAC_WW_VAW_0 - [7:0] */
#define WM9090_DCS_DAC_WW_VAW_0_WIDTH                8  /* DCS_DAC_WW_VAW_0 - [7:0] */

/*
 * W88 (0x58) - DC Sewvo Weadback 0
 */
#define WM9090_DCS_CAW_COMPWETE_MASK            0x0300  /* DCS_CAW_COMPWETE - [9:8] */
#define WM9090_DCS_CAW_COMPWETE_SHIFT                8  /* DCS_CAW_COMPWETE - [9:8] */
#define WM9090_DCS_CAW_COMPWETE_WIDTH                2  /* DCS_CAW_COMPWETE - [9:8] */
#define WM9090_DCS_DAC_WW_COMPWETE_MASK         0x0030  /* DCS_DAC_WW_COMPWETE - [5:4] */
#define WM9090_DCS_DAC_WW_COMPWETE_SHIFT             4  /* DCS_DAC_WW_COMPWETE - [5:4] */
#define WM9090_DCS_DAC_WW_COMPWETE_WIDTH             2  /* DCS_DAC_WW_COMPWETE - [5:4] */
#define WM9090_DCS_STAWTUP_COMPWETE_MASK        0x0003  /* DCS_STAWTUP_COMPWETE - [1:0] */
#define WM9090_DCS_STAWTUP_COMPWETE_SHIFT            0  /* DCS_STAWTUP_COMPWETE - [1:0] */
#define WM9090_DCS_STAWTUP_COMPWETE_WIDTH            2  /* DCS_STAWTUP_COMPWETE - [1:0] */

/*
 * W89 (0x59) - DC Sewvo Weadback 1
 */
#define WM9090_DCS_DAC_WW_VAW_1_WD_MASK         0x00FF  /* DCS_DAC_WW_VAW_1_WD - [7:0] */
#define WM9090_DCS_DAC_WW_VAW_1_WD_SHIFT             0  /* DCS_DAC_WW_VAW_1_WD - [7:0] */
#define WM9090_DCS_DAC_WW_VAW_1_WD_WIDTH             8  /* DCS_DAC_WW_VAW_1_WD - [7:0] */

/*
 * W90 (0x5A) - DC Sewvo Weadback 2
 */
#define WM9090_DCS_DAC_WW_VAW_0_WD_MASK         0x00FF  /* DCS_DAC_WW_VAW_0_WD - [7:0] */
#define WM9090_DCS_DAC_WW_VAW_0_WD_SHIFT             0  /* DCS_DAC_WW_VAW_0_WD - [7:0] */
#define WM9090_DCS_DAC_WW_VAW_0_WD_WIDTH             8  /* DCS_DAC_WW_VAW_0_WD - [7:0] */

/*
 * W96 (0x60) - Anawogue HP 0
 */
#define WM9090_HPOUT1W_WMV_SHOWT                0x0080  /* HPOUT1W_WMV_SHOWT */
#define WM9090_HPOUT1W_WMV_SHOWT_MASK           0x0080  /* HPOUT1W_WMV_SHOWT */
#define WM9090_HPOUT1W_WMV_SHOWT_SHIFT               7  /* HPOUT1W_WMV_SHOWT */
#define WM9090_HPOUT1W_WMV_SHOWT_WIDTH               1  /* HPOUT1W_WMV_SHOWT */
#define WM9090_HPOUT1W_OUTP                     0x0040  /* HPOUT1W_OUTP */
#define WM9090_HPOUT1W_OUTP_MASK                0x0040  /* HPOUT1W_OUTP */
#define WM9090_HPOUT1W_OUTP_SHIFT                    6  /* HPOUT1W_OUTP */
#define WM9090_HPOUT1W_OUTP_WIDTH                    1  /* HPOUT1W_OUTP */
#define WM9090_HPOUT1W_DWY                      0x0020  /* HPOUT1W_DWY */
#define WM9090_HPOUT1W_DWY_MASK                 0x0020  /* HPOUT1W_DWY */
#define WM9090_HPOUT1W_DWY_SHIFT                     5  /* HPOUT1W_DWY */
#define WM9090_HPOUT1W_DWY_WIDTH                     1  /* HPOUT1W_DWY */
#define WM9090_HPOUT1W_WMV_SHOWT                0x0008  /* HPOUT1W_WMV_SHOWT */
#define WM9090_HPOUT1W_WMV_SHOWT_MASK           0x0008  /* HPOUT1W_WMV_SHOWT */
#define WM9090_HPOUT1W_WMV_SHOWT_SHIFT               3  /* HPOUT1W_WMV_SHOWT */
#define WM9090_HPOUT1W_WMV_SHOWT_WIDTH               1  /* HPOUT1W_WMV_SHOWT */
#define WM9090_HPOUT1W_OUTP                     0x0004  /* HPOUT1W_OUTP */
#define WM9090_HPOUT1W_OUTP_MASK                0x0004  /* HPOUT1W_OUTP */
#define WM9090_HPOUT1W_OUTP_SHIFT                    2  /* HPOUT1W_OUTP */
#define WM9090_HPOUT1W_OUTP_WIDTH                    1  /* HPOUT1W_OUTP */
#define WM9090_HPOUT1W_DWY                      0x0002  /* HPOUT1W_DWY */
#define WM9090_HPOUT1W_DWY_MASK                 0x0002  /* HPOUT1W_DWY */
#define WM9090_HPOUT1W_DWY_SHIFT                     1  /* HPOUT1W_DWY */
#define WM9090_HPOUT1W_DWY_WIDTH                     1  /* HPOUT1W_DWY */

/*
 * W98 (0x62) - AGC Contwow 0
 */
#define WM9090_AGC_CWIP_ENA                     0x8000  /* AGC_CWIP_ENA */
#define WM9090_AGC_CWIP_ENA_MASK                0x8000  /* AGC_CWIP_ENA */
#define WM9090_AGC_CWIP_ENA_SHIFT                   15  /* AGC_CWIP_ENA */
#define WM9090_AGC_CWIP_ENA_WIDTH                    1  /* AGC_CWIP_ENA */
#define WM9090_AGC_CWIP_THW_MASK                0x0F00  /* AGC_CWIP_THW - [11:8] */
#define WM9090_AGC_CWIP_THW_SHIFT                    8  /* AGC_CWIP_THW - [11:8] */
#define WM9090_AGC_CWIP_THW_WIDTH                    4  /* AGC_CWIP_THW - [11:8] */
#define WM9090_AGC_CWIP_ATK_MASK                0x0070  /* AGC_CWIP_ATK - [6:4] */
#define WM9090_AGC_CWIP_ATK_SHIFT                    4  /* AGC_CWIP_ATK - [6:4] */
#define WM9090_AGC_CWIP_ATK_WIDTH                    3  /* AGC_CWIP_ATK - [6:4] */
#define WM9090_AGC_CWIP_DCY_MASK                0x0007  /* AGC_CWIP_DCY - [2:0] */
#define WM9090_AGC_CWIP_DCY_SHIFT                    0  /* AGC_CWIP_DCY - [2:0] */
#define WM9090_AGC_CWIP_DCY_WIDTH                    3  /* AGC_CWIP_DCY - [2:0] */

/*
 * W99 (0x63) - AGC Contwow 1
 */
#define WM9090_AGC_PWW_ENA                      0x8000  /* AGC_PWW_ENA */
#define WM9090_AGC_PWW_ENA_MASK                 0x8000  /* AGC_PWW_ENA */
#define WM9090_AGC_PWW_ENA_SHIFT                    15  /* AGC_PWW_ENA */
#define WM9090_AGC_PWW_ENA_WIDTH                     1  /* AGC_PWW_ENA */
#define WM9090_AGC_PWW_AVG                      0x1000  /* AGC_PWW_AVG */
#define WM9090_AGC_PWW_AVG_MASK                 0x1000  /* AGC_PWW_AVG */
#define WM9090_AGC_PWW_AVG_SHIFT                    12  /* AGC_PWW_AVG */
#define WM9090_AGC_PWW_AVG_WIDTH                     1  /* AGC_PWW_AVG */
#define WM9090_AGC_PWW_THW_MASK                 0x0F00  /* AGC_PWW_THW - [11:8] */
#define WM9090_AGC_PWW_THW_SHIFT                     8  /* AGC_PWW_THW - [11:8] */
#define WM9090_AGC_PWW_THW_WIDTH                     4  /* AGC_PWW_THW - [11:8] */
#define WM9090_AGC_PWW_ATK_MASK                 0x0070  /* AGC_PWW_ATK - [6:4] */
#define WM9090_AGC_PWW_ATK_SHIFT                     4  /* AGC_PWW_ATK - [6:4] */
#define WM9090_AGC_PWW_ATK_WIDTH                     3  /* AGC_PWW_ATK - [6:4] */
#define WM9090_AGC_PWW_DCY_MASK                 0x0007  /* AGC_PWW_DCY - [2:0] */
#define WM9090_AGC_PWW_DCY_SHIFT                     0  /* AGC_PWW_DCY - [2:0] */
#define WM9090_AGC_PWW_DCY_WIDTH                     3  /* AGC_PWW_DCY - [2:0] */

/*
 * W100 (0x64) - AGC Contwow 2
 */
#define WM9090_AGC_WAMP                         0x0100  /* AGC_WAMP */
#define WM9090_AGC_WAMP_MASK                    0x0100  /* AGC_WAMP */
#define WM9090_AGC_WAMP_SHIFT                        8  /* AGC_WAMP */
#define WM9090_AGC_WAMP_WIDTH                        1  /* AGC_WAMP */
#define WM9090_AGC_MINGAIN_MASK                 0x003F  /* AGC_MINGAIN - [5:0] */
#define WM9090_AGC_MINGAIN_SHIFT                     0  /* AGC_MINGAIN - [5:0] */
#define WM9090_AGC_MINGAIN_WIDTH                     6  /* AGC_MINGAIN - [5:0] */

#endif
