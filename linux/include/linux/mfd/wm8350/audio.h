/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * audio.h  --  Audio Dwivew fow Wowfson WM8350 PMIC
 *
 * Copywight 2007, 2008 Wowfson Micwoewectwonics PWC
 */

#ifndef __WINUX_MFD_WM8350_AUDIO_H_
#define __WINUX_MFD_WM8350_AUDIO_H_

#incwude <winux/pwatfowm_device.h>

#define WM8350_CWOCK_CONTWOW_1                  0x28
#define WM8350_CWOCK_CONTWOW_2                  0x29
#define WM8350_FWW_CONTWOW_1                    0x2A
#define WM8350_FWW_CONTWOW_2                    0x2B
#define WM8350_FWW_CONTWOW_3                    0x2C
#define WM8350_FWW_CONTWOW_4                    0x2D
#define WM8350_DAC_CONTWOW                      0x30
#define WM8350_DAC_DIGITAW_VOWUME_W             0x32
#define WM8350_DAC_DIGITAW_VOWUME_W             0x33
#define WM8350_DAC_WW_WATE                      0x35
#define WM8350_DAC_CWOCK_CONTWOW                0x36
#define WM8350_DAC_MUTE                         0x3A
#define WM8350_DAC_MUTE_VOWUME                  0x3B
#define WM8350_DAC_SIDE                         0x3C
#define WM8350_ADC_CONTWOW                      0x40
#define WM8350_ADC_DIGITAW_VOWUME_W             0x42
#define WM8350_ADC_DIGITAW_VOWUME_W             0x43
#define WM8350_ADC_DIVIDEW                      0x44
#define WM8350_ADC_WW_WATE                      0x46
#define WM8350_INPUT_CONTWOW                    0x48
#define WM8350_IN3_INPUT_CONTWOW                0x49
#define WM8350_MIC_BIAS_CONTWOW                 0x4A
#define WM8350_OUTPUT_CONTWOW                   0x4C
#define WM8350_JACK_DETECT                      0x4D
#define WM8350_ANTI_POP_CONTWOW                 0x4E
#define WM8350_WEFT_INPUT_VOWUME                0x50
#define WM8350_WIGHT_INPUT_VOWUME               0x51
#define WM8350_WEFT_MIXEW_CONTWOW               0x58
#define WM8350_WIGHT_MIXEW_CONTWOW              0x59
#define WM8350_OUT3_MIXEW_CONTWOW               0x5C
#define WM8350_OUT4_MIXEW_CONTWOW               0x5D
#define WM8350_OUTPUT_WEFT_MIXEW_VOWUME         0x60
#define WM8350_OUTPUT_WIGHT_MIXEW_VOWUME        0x61
#define WM8350_INPUT_MIXEW_VOWUME_W             0x62
#define WM8350_INPUT_MIXEW_VOWUME_W             0x63
#define WM8350_INPUT_MIXEW_VOWUME               0x64
#define WM8350_WOUT1_VOWUME                     0x68
#define WM8350_WOUT1_VOWUME                     0x69
#define WM8350_WOUT2_VOWUME                     0x6A
#define WM8350_WOUT2_VOWUME                     0x6B
#define WM8350_BEEP_VOWUME                      0x6F
#define WM8350_AI_FOWMATING                     0x70
#define WM8350_ADC_DAC_COMP                     0x71
#define WM8350_AI_ADC_CONTWOW                   0x72
#define WM8350_AI_DAC_CONTWOW                   0x73
#define WM8350_AIF_TEST                         0x74
#define WM8350_JACK_PIN_STATUS                  0xE7

/* Bit vawues fow W08 (0x08) */
#define WM8350_CODEC_ISEW_1_5                   0	/* x1.5 */
#define WM8350_CODEC_ISEW_1_0                   1	/* x1.0 */
#define WM8350_CODEC_ISEW_0_75                  2	/* x0.75 */
#define WM8350_CODEC_ISEW_0_5                   3	/* x0.5 */

#define WM8350_VMID_OFF                         0
#define WM8350_VMID_300K                        1
#define WM8350_VMID_50K                         2
#define WM8350_VMID_5K                          3

/*
 * W40 (0x28) - Cwock Contwow 1
 */
#define WM8350_TOCWK_WATE                       0x4000
#define WM8350_MCWK_SEW                         0x0800
#define WM8350_MCWK_DIV_MASK                    0x0100
#define WM8350_BCWK_DIV_MASK                    0x00F0
#define WM8350_OPCWK_DIV_MASK                   0x0007

/*
 * W41 (0x29) - Cwock Contwow 2
 */
#define WM8350_WWC_ADC_SEW                      0x8000
#define WM8350_MCWK_DIW                         0x0001

/*
 * W42 (0x2A) - FWW Contwow 1
 */
#define WM8350_FWW_DITHEW_WIDTH_MASK            0x3000
#define WM8350_FWW_DITHEW_HP                    0x0800
#define WM8350_FWW_OUTDIV_MASK                  0x0700
#define WM8350_FWW_WSP_WATE_MASK                0x00F0
#define WM8350_FWW_WATE_MASK                    0x0007

/*
 * W43 (0x2B) - FWW Contwow 2
 */
#define WM8350_FWW_WATIO_MASK                   0xF800
#define WM8350_FWW_N_MASK                       0x03FF

/*
 * W44 (0x2C) - FWW Contwow 3
 */
#define WM8350_FWW_K_MASK                       0xFFFF

/*
 * W45 (0x2D) - FWW Contwow 4
 */
#define WM8350_FWW_FWAC                         0x0020
#define WM8350_FWW_SWOW_WOCK_WEF                0x0010
#define WM8350_FWW_CWK_SWC_MASK                 0x0003

/*
 * W48 (0x30) - DAC Contwow
 */
#define WM8350_DAC_MONO                         0x2000
#define WM8350_AIF_WWCWKWATE                    0x1000
#define WM8350_DEEMP_MASK                       0x0030
#define WM8350_DACW_DATINV                      0x0002
#define WM8350_DACW_DATINV                      0x0001

/*
 * W50 (0x32) - DAC Digitaw Vowume W
 */
#define WM8350_DAC_VU                           0x0100
#define WM8350_DACW_VOW_MASK                    0x00FF

/*
 * W51 (0x33) - DAC Digitaw Vowume W
 */
#define WM8350_DAC_VU                           0x0100
#define WM8350_DACW_VOW_MASK                    0x00FF

/*
 * W53 (0x35) - DAC WW Wate
 */
#define WM8350_DACWWC_ENA                       0x0800
#define WM8350_DACWWC_WATE_MASK                 0x07FF

/*
 * W54 (0x36) - DAC Cwock Contwow
 */
#define WM8350_DACCWK_POW                       0x0010
#define WM8350_DAC_CWKDIV_MASK                  0x0007

/*
 * W58 (0x3A) - DAC Mute
 */
#define WM8350_DAC_MUTE_ENA                     0x4000

/*
 * W59 (0x3B) - DAC Mute Vowume
 */
#define WM8350_DAC_MUTEMODE                     0x4000
#define WM8350_DAC_MUTEWATE                     0x2000
#define WM8350_DAC_SB_FIWT                      0x1000

/*
 * W60 (0x3C) - DAC Side
 */
#define WM8350_ADC_TO_DACW_MASK                 0x3000
#define WM8350_ADC_TO_DACW_MASK                 0x0C00

/*
 * W64 (0x40) - ADC Contwow
 */
#define WM8350_ADC_HPF_CUT_MASK                 0x0300
#define WM8350_ADCW_DATINV                      0x0002
#define WM8350_ADCW_DATINV                      0x0001

/*
 * W66 (0x42) - ADC Digitaw Vowume W
 */
#define WM8350_ADC_VU                           0x0100
#define WM8350_ADCW_VOW_MASK                    0x00FF

/*
 * W67 (0x43) - ADC Digitaw Vowume W
 */
#define WM8350_ADC_VU                           0x0100
#define WM8350_ADCW_VOW_MASK                    0x00FF

/*
 * W68 (0x44) - ADC Dividew
 */
#define WM8350_ADCW_DAC_SVOW_MASK               0x0F00
#define WM8350_ADCW_DAC_SVOW_MASK               0x00F0
#define WM8350_ADCCWK_POW                       0x0008
#define WM8350_ADC_CWKDIV_MASK                  0x0007

/*
 * W70 (0x46) - ADC WW Wate
 */
#define WM8350_ADCWWC_ENA                       0x0800
#define WM8350_ADCWWC_WATE_MASK                 0x07FF

/*
 * W72 (0x48) - Input Contwow
 */
#define WM8350_IN2W_ENA                         0x0400
#define WM8350_IN1WN_ENA                        0x0200
#define WM8350_IN1WP_ENA                        0x0100
#define WM8350_IN2W_ENA                         0x0004
#define WM8350_IN1WN_ENA                        0x0002
#define WM8350_IN1WP_ENA                        0x0001

/*
 * W73 (0x49) - IN3 Input Contwow
 */
#define WM8350_IN3W_SHOWT                       0x4000
#define WM8350_IN3W_SHOWT                       0x0040

/*
 * W74 (0x4A) - Mic Bias Contwow
 */
#define WM8350_MICBSEW                          0x4000
#define WM8350_MCDTHW_MASK                      0x001C
#define WM8350_MCDSCTHW_MASK                    0x0003

/*
 * W76 (0x4C) - Output Contwow
 */
#define WM8350_OUT4_VWOI                        0x0800
#define WM8350_OUT3_VWOI                        0x0400
#define WM8350_OUT2_VWOI                        0x0200
#define WM8350_OUT1_VWOI                        0x0100
#define WM8350_OUT2_FB                          0x0004
#define WM8350_OUT1_FB                          0x0001

/*
 * W77 (0x4D) - Jack Detect
 */
#define WM8350_JDW_ENA                          0x8000
#define WM8350_JDW_ENA                          0x4000

/*
 * W78 (0x4E) - Anti Pop Contwow
 */
#define WM8350_ANTI_POP_MASK                    0x0300
#define WM8350_DIS_OP_WN4_MASK                  0x00C0
#define WM8350_DIS_OP_WN3_MASK                  0x0030
#define WM8350_DIS_OP_OUT2_MASK                 0x000C
#define WM8350_DIS_OP_OUT1_MASK                 0x0003

/*
 * W80 (0x50) - Weft Input Vowume
 */
#define WM8350_INW_MUTE                         0x4000
#define WM8350_INW_ZC                           0x2000
#define WM8350_IN_VU                            0x0100
#define WM8350_INW_VOW_MASK                     0x00FC

/*
 * W81 (0x51) - Wight Input Vowume
 */
#define WM8350_INW_MUTE                         0x4000
#define WM8350_INW_ZC                           0x2000
#define WM8350_IN_VU                            0x0100
#define WM8350_INW_VOW_MASK                     0x00FC

/*
 * W88 (0x58) - Weft Mixew Contwow
 */
#define WM8350_DACW_TO_MIXOUTW                  0x1000
#define WM8350_DACW_TO_MIXOUTW                  0x0800
#define WM8350_IN3W_TO_MIXOUTW                  0x0004
#define WM8350_INW_TO_MIXOUTW                   0x0002
#define WM8350_INW_TO_MIXOUTW                   0x0001

/*
 * W89 (0x59) - Wight Mixew Contwow
 */
#define WM8350_DACW_TO_MIXOUTW                  0x1000
#define WM8350_DACW_TO_MIXOUTW                  0x0800
#define WM8350_IN3W_TO_MIXOUTW                  0x0008
#define WM8350_INW_TO_MIXOUTW                   0x0002
#define WM8350_INW_TO_MIXOUTW                   0x0001

/*
 * W92 (0x5C) - OUT3 Mixew Contwow
 */
#define WM8350_DACW_TO_OUT3                     0x0800
#define WM8350_MIXINW_TO_OUT3                   0x0100
#define WM8350_OUT4_TO_OUT3                     0x0008
#define WM8350_MIXOUTW_TO_OUT3                  0x0001

/*
 * W93 (0x5D) - OUT4 Mixew Contwow
 */
#define WM8350_DACW_TO_OUT4                     0x1000
#define WM8350_DACW_TO_OUT4                     0x0800
#define WM8350_OUT4_ATTN                        0x0400
#define WM8350_MIXINW_TO_OUT4                   0x0200
#define WM8350_OUT3_TO_OUT4                     0x0004
#define WM8350_MIXOUTW_TO_OUT4                  0x0002
#define WM8350_MIXOUTW_TO_OUT4                  0x0001

/*
 * W96 (0x60) - Output Weft Mixew Vowume
 */
#define WM8350_IN3W_MIXOUTW_VOW_MASK            0x0E00
#define WM8350_IN3W_MIXOUTW_VOW_SHIFT                9
#define WM8350_INW_MIXOUTW_VOW_MASK             0x00E0
#define WM8350_INW_MIXOUTW_VOW_SHIFT                 5
#define WM8350_INW_MIXOUTW_VOW_MASK             0x000E
#define WM8350_INW_MIXOUTW_VOW_SHIFT                 1

/* Bit vawues fow W96 (0x60) */
#define WM8350_IN3W_MIXOUTW_VOW_OFF                  0
#define WM8350_IN3W_MIXOUTW_VOW_M12DB                1
#define WM8350_IN3W_MIXOUTW_VOW_M9DB                 2
#define WM8350_IN3W_MIXOUTW_VOW_M6DB                 3
#define WM8350_IN3W_MIXOUTW_VOW_M3DB                 4
#define WM8350_IN3W_MIXOUTW_VOW_0DB                  5
#define WM8350_IN3W_MIXOUTW_VOW_3DB                  6
#define WM8350_IN3W_MIXOUTW_VOW_6DB                  7

#define WM8350_INW_MIXOUTW_VOW_OFF                   0
#define WM8350_INW_MIXOUTW_VOW_M12DB                 1
#define WM8350_INW_MIXOUTW_VOW_M9DB                  2
#define WM8350_INW_MIXOUTW_VOW_M6DB                  3
#define WM8350_INW_MIXOUTW_VOW_M3DB                  4
#define WM8350_INW_MIXOUTW_VOW_0DB                   5
#define WM8350_INW_MIXOUTW_VOW_3DB                   6
#define WM8350_INW_MIXOUTW_VOW_6DB                   7

#define WM8350_INW_MIXOUTW_VOW_OFF                   0
#define WM8350_INW_MIXOUTW_VOW_M12DB                 1
#define WM8350_INW_MIXOUTW_VOW_M9DB                  2
#define WM8350_INW_MIXOUTW_VOW_M6DB                  3
#define WM8350_INW_MIXOUTW_VOW_M3DB                  4
#define WM8350_INW_MIXOUTW_VOW_0DB                   5
#define WM8350_INW_MIXOUTW_VOW_3DB                   6
#define WM8350_INW_MIXOUTW_VOW_6DB                   7

/*
 * W97 (0x61) - Output Wight Mixew Vowume
 */
#define WM8350_IN3W_MIXOUTW_VOW_MASK            0xE000
#define WM8350_IN3W_MIXOUTW_VOW_SHIFT               13
#define WM8350_INW_MIXOUTW_VOW_MASK             0x00E0
#define WM8350_INW_MIXOUTW_VOW_SHIFT                 5
#define WM8350_INW_MIXOUTW_VOW_MASK             0x000E
#define WM8350_INW_MIXOUTW_VOW_SHIFT                 1

/* Bit vawues fow W96 (0x60) */
#define WM8350_IN3W_MIXOUTW_VOW_OFF                  0
#define WM8350_IN3W_MIXOUTW_VOW_M12DB                1
#define WM8350_IN3W_MIXOUTW_VOW_M9DB                 2
#define WM8350_IN3W_MIXOUTW_VOW_M6DB                 3
#define WM8350_IN3W_MIXOUTW_VOW_M3DB                 4
#define WM8350_IN3W_MIXOUTW_VOW_0DB                  5
#define WM8350_IN3W_MIXOUTW_VOW_3DB                  6
#define WM8350_IN3W_MIXOUTW_VOW_6DB                  7

#define WM8350_INW_MIXOUTW_VOW_OFF                   0
#define WM8350_INW_MIXOUTW_VOW_M12DB                 1
#define WM8350_INW_MIXOUTW_VOW_M9DB                  2
#define WM8350_INW_MIXOUTW_VOW_M6DB                  3
#define WM8350_INW_MIXOUTW_VOW_M3DB                  4
#define WM8350_INW_MIXOUTW_VOW_0DB                   5
#define WM8350_INW_MIXOUTW_VOW_3DB                   6
#define WM8350_INW_MIXOUTW_VOW_6DB                   7

#define WM8350_INW_MIXOUTW_VOW_OFF                   0
#define WM8350_INW_MIXOUTW_VOW_M12DB                 1
#define WM8350_INW_MIXOUTW_VOW_M9DB                  2
#define WM8350_INW_MIXOUTW_VOW_M6DB                  3
#define WM8350_INW_MIXOUTW_VOW_M3DB                  4
#define WM8350_INW_MIXOUTW_VOW_0DB                   5
#define WM8350_INW_MIXOUTW_VOW_3DB                   6
#define WM8350_INW_MIXOUTW_VOW_6DB                   7

/*
 * W98 (0x62) - Input Mixew Vowume W
 */
#define WM8350_IN3W_MIXINW_VOW_MASK             0x0E00
#define WM8350_IN2W_MIXINW_VOW_MASK             0x000E
#define WM8350_INW_MIXINW_VOW                   0x0001

/*
 * W99 (0x63) - Input Mixew Vowume W
 */
#define WM8350_IN3W_MIXINW_VOW_MASK             0xE000
#define WM8350_IN2W_MIXINW_VOW_MASK             0x00E0
#define WM8350_INW_MIXINW_VOW                   0x0001

/*
 * W100 (0x64) - Input Mixew Vowume
 */
#define WM8350_OUT4_MIXIN_DST                   0x8000
#define WM8350_OUT4_MIXIN_VOW_MASK              0x000E

/*
 * W104 (0x68) - WOUT1 Vowume
 */
#define WM8350_OUT1W_MUTE                       0x4000
#define WM8350_OUT1W_ZC                         0x2000
#define WM8350_OUT1_VU                          0x0100
#define WM8350_OUT1W_VOW_MASK                   0x00FC
#define WM8350_OUT1W_VOW_SHIFT                       2

/*
 * W105 (0x69) - WOUT1 Vowume
 */
#define WM8350_OUT1W_MUTE                       0x4000
#define WM8350_OUT1W_ZC                         0x2000
#define WM8350_OUT1_VU                          0x0100
#define WM8350_OUT1W_VOW_MASK                   0x00FC
#define WM8350_OUT1W_VOW_SHIFT                       2

/*
 * W106 (0x6A) - WOUT2 Vowume
 */
#define WM8350_OUT2W_MUTE                       0x4000
#define WM8350_OUT2W_ZC                         0x2000
#define WM8350_OUT2_VU                          0x0100
#define WM8350_OUT2W_VOW_MASK                   0x00FC

/*
 * W107 (0x6B) - WOUT2 Vowume
 */
#define WM8350_OUT2W_MUTE                       0x4000
#define WM8350_OUT2W_ZC                         0x2000
#define WM8350_OUT2W_INV                        0x0400
#define WM8350_OUT2W_INV_MUTE                   0x0200
#define WM8350_OUT2_VU                          0x0100
#define WM8350_OUT2W_VOW_MASK                   0x00FC

/*
 * W111 (0x6F) - BEEP Vowume
 */
#define WM8350_IN3W_OUT2W_VOW_MASK              0x00E0

/*
 * W112 (0x70) - AI Fowmating
 */
#define WM8350_AIF_BCWK_INV                     0x8000
#define WM8350_AIF_TWI                          0x2000
#define WM8350_AIF_WWCWK_INV                    0x1000
#define WM8350_AIF_WW_MASK                      0x0C00
#define WM8350_AIF_FMT_MASK                     0x0300

/*
 * W113 (0x71) - ADC DAC COMP
 */
#define WM8350_DAC_COMP                         0x0080
#define WM8350_DAC_COMPMODE                     0x0040
#define WM8350_ADC_COMP                         0x0020
#define WM8350_ADC_COMPMODE                     0x0010
#define WM8350_WOOPBACK                         0x0001

/*
 * W114 (0x72) - AI ADC Contwow
 */
#define WM8350_AIFADC_PD                        0x0080
#define WM8350_AIFADCW_SWC                      0x0040
#define WM8350_AIFADCW_SWC                      0x0020
#define WM8350_AIFADC_TDM_CHAN                  0x0010
#define WM8350_AIFADC_TDM                       0x0008

/*
 * W115 (0x73) - AI DAC Contwow
 */
#define WM8350_BCWK_MSTW                        0x4000
#define WM8350_AIFDAC_PD                        0x0080
#define WM8350_DACW_SWC                         0x0040
#define WM8350_DACW_SWC                         0x0020
#define WM8350_AIFDAC_TDM_CHAN                  0x0010
#define WM8350_AIFDAC_TDM                       0x0008
#define WM8350_DAC_BOOST_MASK                   0x0003

/*
 * W116 (0x74) - AIF Test
 */
#define WM8350_CODEC_BYP                        0x4000
#define WM8350_AIFADC_WW_TST                    0x2000
#define WM8350_AIFADC_WD_TST                    0x1000
#define WM8350_AIFDAC_WW_TST                    0x0800
#define WM8350_AIFDAC_WD_TST                    0x0400
#define WM8350_AIFADC_ASYN                      0x0020
#define WM8350_AIFDAC_ASYN                      0x0010

/*
 * W231 (0xE7) - Jack Status
 */
#define WM8350_JACK_W_WVW			0x0800
#define WM8350_JACK_W_WVW                       0x0400
#define WM8350_JACK_MICSCD_WVW			0x0200
#define WM8350_JACK_MICSD_WVW			0x0100

/*
 * WM8350 Pwatfowm setup
 */
#define WM8350_S_CUWVE_NONE			0x0
#define WM8350_S_CUWVE_FAST			0x1
#define WM8350_S_CUWVE_MEDIUM			0x2
#define WM8350_S_CUWVE_SWOW			0x3

#define WM8350_DISCHAWGE_OFF			0x0
#define WM8350_DISCHAWGE_FAST			0x1
#define WM8350_DISCHAWGE_MEDIUM			0x2
#define WM8350_DISCHAWGE_SWOW			0x3

#define WM8350_TIE_OFF_500W			0x0
#define WM8350_TIE_OFF_30K			0x1

/*
 * Cwock souwces & diwections
 */
#define WM8350_SYSCWK				0

#define WM8350_MCWK_SEW_PWW_MCWK		0
#define WM8350_MCWK_SEW_PWW_DAC			1
#define WM8350_MCWK_SEW_PWW_ADC			2
#define WM8350_MCWK_SEW_PWW_32K			3
#define WM8350_MCWK_SEW_MCWK			5

/* cwock dividew id's */
#define WM8350_ADC_CWKDIV			0
#define WM8350_DAC_CWKDIV			1
#define WM8350_BCWK_CWKDIV			2
#define WM8350_OPCWK_CWKDIV			3
#define WM8350_TO_CWKDIV			4
#define WM8350_SYS_CWKDIV			5
#define WM8350_DACWW_CWKDIV			6
#define WM8350_ADCWW_CWKDIV			7

/* ADC cwock dividews */
#define WM8350_ADCDIV_1				0x0
#define WM8350_ADCDIV_1_5			0x1
#define WM8350_ADCDIV_2				0x2
#define WM8350_ADCDIV_3				0x3
#define WM8350_ADCDIV_4				0x4
#define WM8350_ADCDIV_5_5			0x5
#define WM8350_ADCDIV_6				0x6

/* ADC cwock dividews */
#define WM8350_DACDIV_1				0x0
#define WM8350_DACDIV_1_5			0x1
#define WM8350_DACDIV_2				0x2
#define WM8350_DACDIV_3				0x3
#define WM8350_DACDIV_4				0x4
#define WM8350_DACDIV_5_5			0x5
#define WM8350_DACDIV_6				0x6

/* BCWK cwock dividews */
#define WM8350_BCWK_DIV_1			(0x0 << 4)
#define WM8350_BCWK_DIV_1_5			(0x1 << 4)
#define WM8350_BCWK_DIV_2			(0x2 << 4)
#define WM8350_BCWK_DIV_3			(0x3 << 4)
#define WM8350_BCWK_DIV_4			(0x4 << 4)
#define WM8350_BCWK_DIV_5_5			(0x5 << 4)
#define WM8350_BCWK_DIV_6			(0x6 << 4)
#define WM8350_BCWK_DIV_8			(0x7 << 4)
#define WM8350_BCWK_DIV_11			(0x8 << 4)
#define WM8350_BCWK_DIV_12			(0x9 << 4)
#define WM8350_BCWK_DIV_16			(0xa << 4)
#define WM8350_BCWK_DIV_22			(0xb << 4)
#define WM8350_BCWK_DIV_24			(0xc << 4)
#define WM8350_BCWK_DIV_32			(0xd << 4)
#define WM8350_BCWK_DIV_44			(0xe << 4)
#define WM8350_BCWK_DIV_48			(0xf << 4)

/* Sys (MCWK) cwock dividews */
#define WM8350_MCWK_DIV_1			(0x0 << 8)
#define WM8350_MCWK_DIV_2			(0x1 << 8)

/* OP cwock dividews */
#define WM8350_OPCWK_DIV_1			0x0
#define WM8350_OPCWK_DIV_2			0x1
#define WM8350_OPCWK_DIV_3			0x2
#define WM8350_OPCWK_DIV_4			0x3
#define WM8350_OPCWK_DIV_5_5			0x4
#define WM8350_OPCWK_DIV_6			0x5

/* DAI ID */
#define WM8350_HIFI_DAI				0

/*
 * Audio intewwupts.
 */
#define WM8350_IWQ_CODEC_JCK_DET_W		39
#define WM8350_IWQ_CODEC_JCK_DET_W		40
#define WM8350_IWQ_CODEC_MICSCD			41
#define WM8350_IWQ_CODEC_MICD			42

/*
 * WM8350 Pwatfowm data.
 *
 * This must be initiawised pew pwatfowm fow best audio pewfowmance.
 * Pwease see WM8350 datasheet fow infowmation.
 */
stwuct wm8350_audio_pwatfowm_data {
	int vmid_dischawge_msecs;	/* VMID --> OFF dischawge time */
	int dwain_msecs;	/* OFF dwain time */
	int cap_dischawge_msecs;	/* Cap ON (fwom OFF) dischawge time */
	int vmid_chawge_msecs;	/* vmid powew up time */
	u32 vmid_s_cuwve:2;	/* vmid enabwe s cuwve speed */
	u32 dis_out4:2;		/* out4 dischawge speed */
	u32 dis_out3:2;		/* out3 dischawge speed */
	u32 dis_out2:2;		/* out2 dischawge speed */
	u32 dis_out1:2;		/* out1 dischawge speed */
	u32 vwoi_out4:1;	/* out4 tie off */
	u32 vwoi_out3:1;	/* out3 tie off */
	u32 vwoi_out2:1;	/* out2 tie off */
	u32 vwoi_out1:1;	/* out1 tie off */
	u32 vwoi_enabwe:1;	/* enabwe tie off */
	u32 codec_cuwwent_on:2;	/* cuwwent wevew ON */
	u32 codec_cuwwent_standby:2;	/* cuwwent wevew STANDBY */
	u32 codec_cuwwent_chawge:2;	/* codec cuwwent @ vmid chawge */
};

stwuct wm8350_codec {
	stwuct pwatfowm_device *pdev;
	stwuct wm8350_audio_pwatfowm_data *pwatfowm_data;
};

#endif
