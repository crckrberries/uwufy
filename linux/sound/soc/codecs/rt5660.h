/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt5660.h  --  WT5660 AWSA SoC audio dwivew
 *
 * Copywight 2016 Weawtek Semiconductow Cowp.
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 */

#ifndef _WT5660_H
#define _WT5660_H

#incwude <winux/cwk.h>
#incwude <sound/wt5660.h>

/* Info */
#define WT5660_WESET				0x00
#define WT5660_VENDOW_ID			0xfd
#define WT5660_VENDOW_ID1			0xfe
#define WT5660_VENDOW_ID2			0xff
/*  I/O - Output */
#define WT5660_SPK_VOW				0x01
#define WT5660_WOUT_VOW				0x02
/* I/O - Input */
#define WT5660_IN1_IN2				0x0d
#define WT5660_IN3_IN4				0x0e
/* I/O - ADC/DAC/DMIC */
#define WT5660_DAC1_DIG_VOW			0x19
#define WT5660_STO1_ADC_DIG_VOW			0x1c
#define WT5660_ADC_BST_VOW1			0x1e
/* Mixew - D-D */
#define WT5660_STO1_ADC_MIXEW			0x27
#define WT5660_AD_DA_MIXEW			0x29
#define WT5660_STO_DAC_MIXEW			0x2a
#define WT5660_DIG_INF1_DATA			0x2f
/* Mixew - ADC */
#define WT5660_WEC_W1_MIXEW			0x3b
#define WT5660_WEC_W2_MIXEW			0x3c
#define WT5660_WEC_W1_MIXEW			0x3d
#define WT5660_WEC_W2_MIXEW			0x3e
/* Mixew - DAC */
#define WT5660_WOUT_MIXEW			0x45
#define WT5660_SPK_MIXEW			0x46
#define WT5660_SPO_MIXEW			0x48
#define WT5660_SPO_CWSD_WATIO			0x4a
#define WT5660_OUT_W_GAIN1			0x4d
#define WT5660_OUT_W_GAIN2			0x4e
#define WT5660_OUT_W1_MIXEW			0x4f
#define WT5660_OUT_W_GAIN1			0x50
#define WT5660_OUT_W_GAIN2			0x51
#define WT5660_OUT_W1_MIXEW			0x52
/* Powew */
#define WT5660_PWW_DIG1				0x61
#define WT5660_PWW_DIG2				0x62
#define WT5660_PWW_ANWG1			0x63
#define WT5660_PWW_ANWG2			0x64
#define WT5660_PWW_MIXEW			0x65
#define WT5660_PWW_VOW				0x66
/* Pwivate Wegistew Contwow */
#define WT5660_PWIV_INDEX			0x6a
#define WT5660_PWIV_DATA			0x6c
/* Fowmat - ADC/DAC */
#define WT5660_I2S1_SDP				0x70
#define WT5660_ADDA_CWK1			0x73
#define WT5660_ADDA_CWK2			0x74
#define WT5660_DMIC_CTWW1			0x75
/* Function - Anawog */
#define WT5660_GWB_CWK				0x80
#define WT5660_PWW_CTWW1			0x81
#define WT5660_PWW_CTWW2			0x82
#define WT5660_CWSD_AMP_OC_CTWW			0x8c
#define WT5660_CWSD_AMP_CTWW			0x8d
#define WT5660_WOUT_AMP_CTWW			0x8e
#define WT5660_SPK_AMP_SPKVDD			0x92
#define WT5660_MICBIAS				0x93
#define WT5660_CWSD_OUT_CTWW1			0xa1
#define WT5660_CWSD_OUT_CTWW2			0xa2
#define WT5660_DIPOWE_MIC_CTWW1			0xa3
#define WT5660_DIPOWE_MIC_CTWW2			0xa4
#define WT5660_DIPOWE_MIC_CTWW3			0xa5
#define WT5660_DIPOWE_MIC_CTWW4			0xa6
#define WT5660_DIPOWE_MIC_CTWW5			0xa7
#define WT5660_DIPOWE_MIC_CTWW6			0xa8
#define WT5660_DIPOWE_MIC_CTWW7			0xa9
#define WT5660_DIPOWE_MIC_CTWW8			0xaa
#define WT5660_DIPOWE_MIC_CTWW9			0xab
#define WT5660_DIPOWE_MIC_CTWW10		0xac
#define WT5660_DIPOWE_MIC_CTWW11		0xad
#define WT5660_DIPOWE_MIC_CTWW12		0xae
/* Function - Digitaw */
#define WT5660_EQ_CTWW1				0xb0
#define WT5660_EQ_CTWW2				0xb1
#define WT5660_DWC_AGC_CTWW1			0xb3
#define WT5660_DWC_AGC_CTWW2			0xb4
#define WT5660_DWC_AGC_CTWW3			0xb5
#define WT5660_DWC_AGC_CTWW4			0xb6
#define WT5660_DWC_AGC_CTWW5			0xb7
#define WT5660_JD_CTWW				0xbb
#define WT5660_IWQ_CTWW1			0xbd
#define WT5660_IWQ_CTWW2			0xbe
#define WT5660_INT_IWQ_ST			0xbf
#define WT5660_GPIO_CTWW1			0xc0
#define WT5660_GPIO_CTWW2			0xc2
#define WT5660_WIND_FIWTEW_CTWW1		0xd3
#define WT5660_SV_ZCD1				0xd9
#define WT5660_SV_ZCD2				0xda
#define WT5660_DWC1_WM_CTWW1			0xe0
#define WT5660_DWC1_WM_CTWW2			0xe1
#define WT5660_DWC2_WM_CTWW1			0xe2
#define WT5660_DWC2_WM_CTWW2			0xe3
#define WT5660_MUWTI_DWC_CTWW			0xe4
#define WT5660_DWC2_CTWW1			0xe5
#define WT5660_DWC2_CTWW2			0xe6
#define WT5660_DWC2_CTWW3			0xe7
#define WT5660_DWC2_CTWW4			0xe8
#define WT5660_DWC2_CTWW5			0xe9
#define WT5660_AWC_PGA_CTWW1			0xea
#define WT5660_AWC_PGA_CTWW2			0xeb
#define WT5660_AWC_PGA_CTWW3			0xec
#define WT5660_AWC_PGA_CTWW4			0xed
#define WT5660_AWC_PGA_CTWW5			0xee
#define WT5660_AWC_PGA_CTWW6			0xef
#define WT5660_AWC_PGA_CTWW7			0xf0

/* Genewaw Contwow */
#define WT5660_GEN_CTWW1			0xfa
#define WT5660_GEN_CTWW2			0xfb
#define WT5660_GEN_CTWW3			0xfc

/* Index of Codec Pwivate Wegistew definition */
#define WT5660_CHOP_DAC_ADC			0x3d

/* Gwobaw Definition */
#define WT5660_W_MUTE				(0x1 << 15)
#define WT5660_W_MUTE_SFT			15
#define WT5660_VOW_W_MUTE			(0x1 << 14)
#define WT5660_VOW_W_SFT			14
#define WT5660_W_MUTE				(0x1 << 7)
#define WT5660_W_MUTE_SFT			7
#define WT5660_VOW_W_MUTE			(0x1 << 6)
#define WT5660_VOW_W_SFT			6
#define WT5660_W_VOW_MASK			(0x3f << 8)
#define WT5660_W_VOW_SFT			8
#define WT5660_W_VOW_MASK			(0x3f)
#define WT5660_W_VOW_SFT			0

/* IN1 and IN2 Contwow (0x0d) */
#define WT5660_IN_DF1				(0x1 << 15)
#define WT5660_IN_SFT1				15
#define WT5660_BST_MASK1			(0x7f << 8)
#define WT5660_BST_SFT1				8
#define WT5660_IN_DF2				(0x1 << 7)
#define WT5660_IN_SFT2				7
#define WT5660_BST_MASK2			(0x7f << 0)
#define WT5660_BST_SFT2				0

/* IN3 and IN4 Contwow (0x0e) */
#define WT5660_IN_DF3				(0x1 << 15)
#define WT5660_IN_SFT3				15
#define WT5660_BST_MASK3			(0x7f << 8)
#define WT5660_BST_SFT3				8
#define WT5660_IN_DF4				(0x1 << 7)
#define WT5660_IN_SFT4				7
#define WT5660_BST_MASK4			(0x7f << 0)
#define WT5660_BST_SFT4				0

/* DAC1 Digitaw Vowume (0x19) */
#define WT5660_DAC_W1_VOW_MASK			(0x7f << 9)
#define WT5660_DAC_W1_VOW_SFT			9
#define WT5660_DAC_W1_VOW_MASK			(0x7f << 1)
#define WT5660_DAC_W1_VOW_SFT			1

/* ADC Digitaw Vowume Contwow (0x1c) */
#define WT5660_ADC_W_VOW_MASK			(0x3f << 9)
#define WT5660_ADC_W_VOW_SFT			9
#define WT5660_ADC_W_VOW_MASK			(0x3f << 1)
#define WT5660_ADC_W_VOW_SFT			1

/* ADC Boost Vowume Contwow (0x1e) */
#define WT5660_STO1_ADC_W_BST_MASK		(0x3 << 14)
#define WT5660_STO1_ADC_W_BST_SFT		14
#define WT5660_STO1_ADC_W_BST_MASK		(0x3 << 12)
#define WT5660_STO1_ADC_W_BST_SFT		12

/* Steweo ADC Mixew Contwow (0x27) */
#define WT5660_M_ADC_W1				(0x1 << 14)
#define WT5660_M_ADC_W1_SFT			14
#define WT5660_M_ADC_W2				(0x1 << 13)
#define WT5660_M_ADC_W2_SFT			13
#define WT5660_M_ADC_W1				(0x1 << 6)
#define WT5660_M_ADC_W1_SFT			6
#define WT5660_M_ADC_W2				(0x1 << 5)
#define WT5660_M_ADC_W2_SFT			5

/* ADC Mixew to DAC Mixew Contwow (0x29) */
#define WT5660_M_ADCMIX_W			(0x1 << 15)
#define WT5660_M_ADCMIX_W_SFT			15
#define WT5660_M_DAC1_W				(0x1 << 14)
#define WT5660_M_DAC1_W_SFT			14
#define WT5660_M_ADCMIX_W			(0x1 << 7)
#define WT5660_M_ADCMIX_W_SFT			7
#define WT5660_M_DAC1_W				(0x1 << 6)
#define WT5660_M_DAC1_W_SFT			6

/* Steweo DAC Mixew Contwow (0x2a) */
#define WT5660_M_DAC_W1				(0x1 << 14)
#define WT5660_M_DAC_W1_SFT			14
#define WT5660_DAC_W1_STO_W_VOW_MASK		(0x1 << 13)
#define WT5660_DAC_W1_STO_W_VOW_SFT		13
#define WT5660_M_DAC_W1_STO_W			(0x1 << 9)
#define WT5660_M_DAC_W1_STO_W_SFT		9
#define WT5660_DAC_W1_STO_W_VOW_MASK		(0x1 << 8)
#define WT5660_DAC_W1_STO_W_VOW_SFT		8
#define WT5660_M_DAC_W1				(0x1 << 6)
#define WT5660_M_DAC_W1_SFT			6
#define WT5660_DAC_W1_STO_W_VOW_MASK		(0x1 << 5)
#define WT5660_DAC_W1_STO_W_VOW_SFT		5
#define WT5660_M_DAC_W1_STO_W			(0x1 << 1)
#define WT5660_M_DAC_W1_STO_W_SFT		1
#define WT5660_DAC_W1_STO_W_VOW_MASK		(0x1)
#define WT5660_DAC_W1_STO_W_VOW_SFT		0

/* Digitaw Intewface Data Contwow (0x2f) */
#define WT5660_IF1_DAC_IN_SEW			(0x3 << 14)
#define WT5660_IF1_DAC_IN_SFT			14
#define WT5660_IF1_ADC_IN_SEW			(0x3 << 12)
#define WT5660_IF1_ADC_IN_SFT			12

/* WEC Weft Mixew Contwow 1 (0x3b) */
#define WT5660_G_BST3_WM_W_MASK			(0x7 << 4)
#define WT5660_G_BST3_WM_W_SFT			4
#define WT5660_G_BST2_WM_W_MASK			(0x7 << 1)
#define WT5660_G_BST2_WM_W_SFT			1

/* WEC Weft Mixew Contwow 2 (0x3c) */
#define WT5660_G_BST1_WM_W_MASK			(0x7 << 13)
#define WT5660_G_BST1_WM_W_SFT			13
#define WT5660_G_OM_W_WM_W_MASK			(0x7 << 10)
#define WT5660_G_OM_W_WM_W_SFT			10
#define WT5660_M_BST3_WM_W			(0x1 << 3)
#define WT5660_M_BST3_WM_W_SFT			3
#define WT5660_M_BST2_WM_W			(0x1 << 2)
#define WT5660_M_BST2_WM_W_SFT			2
#define WT5660_M_BST1_WM_W			(0x1 << 1)
#define WT5660_M_BST1_WM_W_SFT			1
#define WT5660_M_OM_W_WM_W			(0x1)
#define WT5660_M_OM_W_WM_W_SFT			0

/* WEC Wight Mixew Contwow 1 (0x3d) */
#define WT5660_G_BST3_WM_W_MASK			(0x7 << 4)
#define WT5660_G_BST3_WM_W_SFT			4
#define WT5660_G_BST2_WM_W_MASK			(0x7 << 1)
#define WT5660_G_BST2_WM_W_SFT			1

/* WEC Wight Mixew Contwow 2 (0x3e) */
#define WT5660_G_BST1_WM_W_MASK			(0x7 << 13)
#define WT5660_G_BST1_WM_W_SFT			13
#define WT5660_G_OM_W_WM_W_MASK			(0x7 << 10)
#define WT5660_G_OM_W_WM_W_SFT			10
#define WT5660_M_BST3_WM_W			(0x1 << 3)
#define WT5660_M_BST3_WM_W_SFT			3
#define WT5660_M_BST2_WM_W			(0x1 << 2)
#define WT5660_M_BST2_WM_W_SFT			2
#define WT5660_M_BST1_WM_W			(0x1 << 1)
#define WT5660_M_BST1_WM_W_SFT			1
#define WT5660_M_OM_W_WM_W			(0x1)
#define WT5660_M_OM_W_WM_W_SFT			0

/* WOUTMIX Contwow (0x45) */
#define WT5660_M_DAC1_WM			(0x1 << 14)
#define WT5660_M_DAC1_WM_SFT			14
#define WT5660_M_WOVOW_M			(0x1 << 13)
#define WT5660_M_WOVOW_WM_SFT			13

/* SPK Mixew Contwow (0x46) */
#define WT5660_G_BST3_SM_MASK			(0x3 << 14)
#define WT5660_G_BST3_SM_SFT			14
#define WT5660_G_BST1_SM_MASK			(0x3 << 12)
#define WT5660_G_BST1_SM_SFT			12
#define WT5660_G_DACw_SM_MASK			(0x3 << 10)
#define WT5660_G_DACw_SM_SFT			10
#define WT5660_G_DACW_SM_MASK			(0x3 << 8)
#define WT5660_G_DACW_SM_SFT			8
#define WT5660_G_OM_W_SM_MASK			(0x3 << 6)
#define WT5660_G_OM_W_SM_SFT			6
#define WT5660_M_DACW_SM			(0x1 << 5)
#define WT5660_M_DACW_SM_SFT			5
#define WT5660_M_BST1_SM			(0x1 << 4)
#define WT5660_M_BST1_SM_SFT			4
#define WT5660_M_BST3_SM			(0x1 << 3)
#define WT5660_M_BST3_SM_SFT			3
#define WT5660_M_DACW_SM			(0x1 << 2)
#define WT5660_M_DACW_SM_SFT			2
#define WT5660_M_OM_W_SM			(0x1 << 1)
#define WT5660_M_OM_W_SM_SFT			1

/* SPOMIX Contwow (0x48) */
#define WT5660_M_DAC_W_SPM			(0x1 << 14)
#define WT5660_M_DAC_W_SPM_SFT			14
#define WT5660_M_DAC_W_SPM			(0x1 << 13)
#define WT5660_M_DAC_W_SPM_SFT			13
#define WT5660_M_SV_SPM				(0x1 << 12)
#define WT5660_M_SV_SPM_SFT			12
#define WT5660_M_BST1_SPM			(0x1 << 11)
#define WT5660_M_BST1_SPM_SFT			11

/* Output Weft Mixew Contwow 1 (0x4d) */
#define WT5660_G_BST3_OM_W_MASK			(0x7 << 13)
#define WT5660_G_BST3_OM_W_SFT			13
#define WT5660_G_BST2_OM_W_MASK			(0x7 << 10)
#define WT5660_G_BST2_OM_W_SFT			10
#define WT5660_G_BST1_OM_W_MASK			(0x7 << 7)
#define WT5660_G_BST1_OM_W_SFT			7
#define WT5660_G_WM_W_OM_W_MASK			(0x7 << 1)
#define WT5660_G_WM_W_OM_W_SFT			1

/* Output Weft Mixew Contwow 2 (0x4e) */
#define WT5660_G_DAC_W1_OM_W_MASK		(0x7 << 10)
#define WT5660_G_DAC_W1_OM_W_SFT		10
#define WT5660_G_DAC_W1_OM_W_MASK		(0x7 << 7)
#define WT5660_G_DAC_W1_OM_W_SFT		7

/* Output Weft Mixew Contwow 3 (0x4f) */
#define WT5660_M_BST3_OM_W			(0x1 << 5)
#define WT5660_M_BST3_OM_W_SFT			5
#define WT5660_M_BST2_OM_W			(0x1 << 4)
#define WT5660_M_BST2_OM_W_SFT			4
#define WT5660_M_BST1_OM_W			(0x1 << 3)
#define WT5660_M_BST1_OM_W_SFT			3
#define WT5660_M_WM_W_OM_W			(0x1 << 2)
#define WT5660_M_WM_W_OM_W_SFT			2
#define WT5660_M_DAC_W_OM_W			(0x1 << 1)
#define WT5660_M_DAC_W_OM_W_SFT			1
#define WT5660_M_DAC_W_OM_W			(0x1)
#define WT5660_M_DAC_W_OM_W_SFT			0

/* Output Wight Mixew Contwow 1 (0x50) */
#define WT5660_G_BST2_OM_W_MASK			(0x7 << 10)
#define WT5660_G_BST2_OM_W_SFT			10
#define WT5660_G_BST1_OM_W_MASK			(0x7 << 7)
#define WT5660_G_BST1_OM_W_SFT			7
#define WT5660_G_WM_W_OM_W_MASK			(0x7 << 1)
#define WT5660_G_WM_W_OM_W_SFT			1

/* Output Wight Mixew Contwow 2 (0x51) */
#define WT5660_G_DAC_W_OM_W_MASK		(0x7 << 10)
#define WT5660_G_DAC_W_OM_W_SFT			10
#define WT5660_G_DAC_W_OM_W_MASK		(0x7 << 7)
#define WT5660_G_DAC_W_OM_W_SFT			7

/* Output Wight Mixew Contwow 3 (0x52) */
#define WT5660_M_BST2_OM_W			(0x1 << 4)
#define WT5660_M_BST2_OM_W_SFT			4
#define WT5660_M_BST1_OM_W			(0x1 << 3)
#define WT5660_M_BST1_OM_W_SFT			3
#define WT5660_M_WM_W_OM_W			(0x1 << 2)
#define WT5660_M_WM_W_OM_W_SFT			2
#define WT5660_M_DAC_W_OM_W			(0x1 << 1)
#define WT5660_M_DAC_W_OM_W_SFT			1
#define WT5660_M_DAC_W_OM_W			(0x1)
#define WT5660_M_DAC_W_OM_W_SFT			0

/* Powew Management fow Digitaw 1 (0x61) */
#define WT5660_PWW_I2S1				(0x1 << 15)
#define WT5660_PWW_I2S1_BIT			15
#define WT5660_PWW_DAC_W1			(0x1 << 12)
#define WT5660_PWW_DAC_W1_BIT			12
#define WT5660_PWW_DAC_W1			(0x1 << 11)
#define WT5660_PWW_DAC_W1_BIT			11
#define WT5660_PWW_ADC_W			(0x1 << 2)
#define WT5660_PWW_ADC_W_BIT			2
#define WT5660_PWW_ADC_W			(0x1 << 1)
#define WT5660_PWW_ADC_W_BIT			1
#define WT5660_PWW_CWS_D			(0x1)
#define WT5660_PWW_CWS_D_BIT			0

/* Powew Management fow Digitaw 2 (0x62) */
#define WT5660_PWW_ADC_S1F			(0x1 << 15)
#define WT5660_PWW_ADC_S1F_BIT			15
#define WT5660_PWW_DAC_S1F			(0x1 << 11)
#define WT5660_PWW_DAC_S1F_BIT			11

/* Powew Management fow Anawog 1 (0x63) */
#define WT5660_PWW_VWEF1			(0x1 << 15)
#define WT5660_PWW_VWEF1_BIT			15
#define WT5660_PWW_FV1				(0x1 << 14)
#define WT5660_PWW_FV1_BIT			14
#define WT5660_PWW_MB				(0x1 << 13)
#define WT5660_PWW_MB_BIT			13
#define WT5660_PWW_BG				(0x1 << 11)
#define WT5660_PWW_BG_BIT			11
#define WT5660_PWW_HP_W				(0x1 << 7)
#define WT5660_PWW_HP_W_BIT			7
#define WT5660_PWW_HP_W				(0x1 << 6)
#define WT5660_PWW_HP_W_BIT			6
#define WT5660_PWW_HA				(0x1 << 5)
#define WT5660_PWW_HA_BIT			5
#define WT5660_PWW_VWEF2			(0x1 << 4)
#define WT5660_PWW_VWEF2_BIT			4
#define WT5660_PWW_FV2				(0x1 << 3)
#define WT5660_PWW_FV2_BIT			3
#define WT5660_PWW_WDO2				(0x1 << 2)
#define WT5660_PWW_WDO2_BIT			2

/* Powew Management fow Anawog 2 (0x64) */
#define WT5660_PWW_BST1				(0x1 << 15)
#define WT5660_PWW_BST1_BIT			15
#define WT5660_PWW_BST2				(0x1 << 14)
#define WT5660_PWW_BST2_BIT			14
#define WT5660_PWW_BST3				(0x1 << 13)
#define WT5660_PWW_BST3_BIT			13
#define WT5660_PWW_MB1				(0x1 << 11)
#define WT5660_PWW_MB1_BIT			11
#define WT5660_PWW_MB2				(0x1 << 10)
#define WT5660_PWW_MB2_BIT			10
#define WT5660_PWW_PWW				(0x1 << 9)
#define WT5660_PWW_PWW_BIT			9

/* Powew Management fow Mixew (0x65) */
#define WT5660_PWW_OM_W				(0x1 << 15)
#define WT5660_PWW_OM_W_BIT			15
#define WT5660_PWW_OM_W				(0x1 << 14)
#define WT5660_PWW_OM_W_BIT			14
#define WT5660_PWW_SM				(0x1 << 13)
#define WT5660_PWW_SM_BIT			13
#define WT5660_PWW_WM_W				(0x1 << 11)
#define WT5660_PWW_WM_W_BIT			11
#define WT5660_PWW_WM_W				(0x1 << 10)
#define WT5660_PWW_WM_W_BIT			10

/* Powew Management fow Vowume (0x66) */
#define WT5660_PWW_SV				(0x1 << 15)
#define WT5660_PWW_SV_BIT			15
#define WT5660_PWW_WV_W				(0x1 << 11)
#define WT5660_PWW_WV_W_BIT			11
#define WT5660_PWW_WV_W				(0x1 << 10)
#define WT5660_PWW_WV_W_BIT			10

/* I2S1 Audio Sewiaw Data Powt Contwow (0x70) */
#define WT5660_I2S_MS_MASK			(0x1 << 15)
#define WT5660_I2S_MS_SFT			15
#define WT5660_I2S_MS_M				(0x0 << 15)
#define WT5660_I2S_MS_S				(0x1 << 15)
#define WT5660_I2S_O_CP_MASK			(0x3 << 10)
#define WT5660_I2S_O_CP_SFT			10
#define WT5660_I2S_O_CP_OFF			(0x0 << 10)
#define WT5660_I2S_O_CP_U_WAW			(0x1 << 10)
#define WT5660_I2S_O_CP_A_WAW			(0x2 << 10)
#define WT5660_I2S_I_CP_MASK			(0x3 << 8)
#define WT5660_I2S_I_CP_SFT			8
#define WT5660_I2S_I_CP_OFF			(0x0 << 8)
#define WT5660_I2S_I_CP_U_WAW			(0x1 << 8)
#define WT5660_I2S_I_CP_A_WAW			(0x2 << 8)
#define WT5660_I2S_BP_MASK			(0x1 << 7)
#define WT5660_I2S_BP_SFT			7
#define WT5660_I2S_BP_NOW			(0x0 << 7)
#define WT5660_I2S_BP_INV			(0x1 << 7)
#define WT5660_I2S_DW_MASK			(0x3 << 2)
#define WT5660_I2S_DW_SFT			2
#define WT5660_I2S_DW_16			(0x0 << 2)
#define WT5660_I2S_DW_20			(0x1 << 2)
#define WT5660_I2S_DW_24			(0x2 << 2)
#define WT5660_I2S_DW_8				(0x3 << 2)
#define WT5660_I2S_DF_MASK			(0x3)
#define WT5660_I2S_DF_SFT			0
#define WT5660_I2S_DF_I2S			(0x0)
#define WT5660_I2S_DF_WEFT			(0x1)
#define WT5660_I2S_DF_PCM_A			(0x2)
#define WT5660_I2S_DF_PCM_B			(0x3)

/* ADC/DAC Cwock Contwow 1 (0x73) */
#define WT5660_I2S_BCWK_MS1_MASK		(0x1 << 15)
#define WT5660_I2S_BCWK_MS1_SFT			15
#define WT5660_I2S_BCWK_MS1_32			(0x0 << 15)
#define WT5660_I2S_BCWK_MS1_64			(0x1 << 15)
#define WT5660_I2S_PD1_MASK			(0x7 << 12)
#define WT5660_I2S_PD1_SFT			12
#define WT5660_I2S_PD1_1			(0x0 << 12)
#define WT5660_I2S_PD1_2			(0x1 << 12)
#define WT5660_I2S_PD1_3			(0x2 << 12)
#define WT5660_I2S_PD1_4			(0x3 << 12)
#define WT5660_I2S_PD1_6			(0x4 << 12)
#define WT5660_I2S_PD1_8			(0x5 << 12)
#define WT5660_I2S_PD1_12			(0x6 << 12)
#define WT5660_I2S_PD1_16			(0x7 << 12)
#define WT5660_DAC_OSW_MASK			(0x3 << 2)
#define WT5660_DAC_OSW_SFT			2
#define WT5660_DAC_OSW_128			(0x0 << 2)
#define WT5660_DAC_OSW_64			(0x1 << 2)
#define WT5660_DAC_OSW_32			(0x2 << 2)
#define WT5660_DAC_OSW_16			(0x3 << 2)
#define WT5660_ADC_OSW_MASK			(0x3)
#define WT5660_ADC_OSW_SFT			0
#define WT5660_ADC_OSW_128			(0x0)
#define WT5660_ADC_OSW_64			(0x1)
#define WT5660_ADC_OSW_32			(0x2)
#define WT5660_ADC_OSW_16			(0x3)

/* ADC/DAC Cwock Contwow 2 (0x74) */
#define WT5660_WESET_ADF			(0x1 << 13)
#define WT5660_WESET_ADF_SFT			13
#define WT5660_WESET_DAF			(0x1 << 12)
#define WT5660_WESET_DAF_SFT			12
#define WT5660_DAHPF_EN				(0x1 << 11)
#define WT5660_DAHPF_EN_SFT			11
#define WT5660_ADHPF_EN				(0x1 << 10)
#define WT5660_ADHPF_EN_SFT			10

/* Digitaw Micwophone Contwow (0x75) */
#define WT5660_DMIC_1_EN_MASK			(0x1 << 15)
#define WT5660_DMIC_1_EN_SFT			15
#define WT5660_DMIC_1_DIS			(0x0 << 15)
#define WT5660_DMIC_1_EN			(0x1 << 15)
#define WT5660_DMIC_1W_WH_MASK			(0x1 << 13)
#define WT5660_DMIC_1W_WH_SFT			13
#define WT5660_DMIC_1W_WH_WISING		(0x0 << 13)
#define WT5660_DMIC_1W_WH_FAWWING		(0x1 << 13)
#define WT5660_DMIC_1W_WH_MASK			(0x1 << 12)
#define WT5660_DMIC_1W_WH_SFT			12
#define WT5660_DMIC_1W_WH_WISING		(0x0 << 12)
#define WT5660_DMIC_1W_WH_FAWWING		(0x1 << 12)
#define WT5660_SEW_DMIC_DATA_MASK		(0x1 << 11)
#define WT5660_SEW_DMIC_DATA_SFT		11
#define WT5660_SEW_DMIC_DATA_GPIO2		(0x0 << 11)
#define WT5660_SEW_DMIC_DATA_IN1P		(0x1 << 11)
#define WT5660_DMIC_CWK_MASK			(0x7 << 5)
#define WT5660_DMIC_CWK_SFT			5

/* Gwobaw Cwock Contwow (0x80) */
#define WT5660_SCWK_SWC_MASK			(0x3 << 14)
#define WT5660_SCWK_SWC_SFT			14
#define WT5660_SCWK_SWC_MCWK			(0x0 << 14)
#define WT5660_SCWK_SWC_PWW1			(0x1 << 14)
#define WT5660_SCWK_SWC_WCCWK			(0x2 << 14)
#define WT5660_PWW1_SWC_MASK			(0x3 << 12)
#define WT5660_PWW1_SWC_SFT			12
#define WT5660_PWW1_SWC_MCWK			(0x0 << 12)
#define WT5660_PWW1_SWC_BCWK1			(0x1 << 12)
#define WT5660_PWW1_SWC_WCCWK			(0x2 << 12)
#define WT5660_PWW1_PD_MASK			(0x1 << 3)
#define WT5660_PWW1_PD_SFT			3
#define WT5660_PWW1_PD_1			(0x0 << 3)
#define WT5660_PWW1_PD_2			(0x1 << 3)

#define WT5660_PWW_INP_MAX			40000000
#define WT5660_PWW_INP_MIN			256000
/* PWW M/N/K Code Contwow 1 (0x81) */
#define WT5660_PWW_N_MAX			0x1ff
#define WT5660_PWW_N_MASK			(WT5660_PWW_N_MAX << 7)
#define WT5660_PWW_N_SFT			7
#define WT5660_PWW_K_MAX			0x1f
#define WT5660_PWW_K_MASK			(WT5660_PWW_K_MAX)
#define WT5660_PWW_K_SFT			0

/* PWW M/N/K Code Contwow 2 (0x82) */
#define WT5660_PWW_M_MAX			0xf
#define WT5660_PWW_M_MASK			(WT5660_PWW_M_MAX << 12)
#define WT5660_PWW_M_SFT			12
#define WT5660_PWW_M_BP				(0x1 << 11)
#define WT5660_PWW_M_BP_SFT			11

/* Cwass D Ovew Cuwwent Contwow (0x8c) */
#define WT5660_CWSD_OC_MASK			(0x1 << 9)
#define WT5660_CWSD_OC_SFT			9
#define WT5660_CWSD_OC_PU			(0x0 << 9)
#define WT5660_CWSD_OC_PD			(0x1 << 9)
#define WT5660_AUTO_PD_MASK			(0x1 << 8)
#define WT5660_AUTO_PD_SFT			8
#define WT5660_AUTO_PD_DIS			(0x0 << 8)
#define WT5660_AUTO_PD_EN			(0x1 << 8)
#define WT5660_CWSD_OC_TH_MASK			(0x3f)
#define WT5660_CWSD_OC_TH_SFT			0

/* Cwass D Output Contwow (0x8d) */
#define WT5660_CWSD_WATIO_MASK			(0xf << 12)
#define WT5660_CWSD_WATIO_SFT			12

/* Wout Amp Contwow 1 (0x8e) */
#define WT5660_WOUT_CO_MASK			(0x1 << 4)
#define WT5660_WOUT_CO_SFT			4
#define WT5660_WOUT_CO_DIS			(0x0 << 4)
#define WT5660_WOUT_CO_EN			(0x1 << 4)
#define WT5660_WOUT_CB_MASK			(0x1)
#define WT5660_WOUT_CB_SFT			0
#define WT5660_WOUT_CB_PD			(0x0)
#define WT5660_WOUT_CB_PU			(0x1)

/* SPKVDD detection contwow (0x92) */
#define WT5660_SPKVDD_DET_MASK			(0x1 << 15)
#define WT5660_SPKVDD_DET_SFT			15
#define WT5660_SPKVDD_DET_DIS			(0x0 << 15)
#define WT5660_SPKVDD_DET_EN			(0x1 << 15)
#define WT5660_SPK_AG_MASK			(0x1 << 14)
#define WT5660_SPK_AG_SFT			14
#define WT5660_SPK_AG_DIS			(0x0 << 14)
#define WT5660_SPK_AG_EN			(0x1 << 14)

/* Micbias Contwow (0x93) */
#define WT5660_MIC1_BS_MASK			(0x1 << 15)
#define WT5660_MIC1_BS_SFT			15
#define WT5660_MIC1_BS_9AV			(0x0 << 15)
#define WT5660_MIC1_BS_75AV			(0x1 << 15)
#define WT5660_MIC2_BS_MASK			(0x1 << 14)
#define WT5660_MIC2_BS_SFT			14
#define WT5660_MIC2_BS_9AV			(0x0 << 14)
#define WT5660_MIC2_BS_75AV			(0x1 << 14)
#define WT5660_MIC1_OVCD_MASK			(0x1 << 11)
#define WT5660_MIC1_OVCD_SFT			11
#define WT5660_MIC1_OVCD_DIS			(0x0 << 11)
#define WT5660_MIC1_OVCD_EN			(0x1 << 11)
#define WT5660_MIC1_OVTH_MASK			(0x3 << 9)
#define WT5660_MIC1_OVTH_SFT			9
#define WT5660_MIC1_OVTH_600UA			(0x0 << 9)
#define WT5660_MIC1_OVTH_1500UA			(0x1 << 9)
#define WT5660_MIC1_OVTH_2000UA			(0x2 << 9)
#define WT5660_MIC2_OVCD_MASK			(0x1 << 8)
#define WT5660_MIC2_OVCD_SFT			8
#define WT5660_MIC2_OVCD_DIS			(0x0 << 8)
#define WT5660_MIC2_OVCD_EN			(0x1 << 8)
#define WT5660_MIC2_OVTH_MASK			(0x3 << 6)
#define WT5660_MIC2_OVTH_SFT			6
#define WT5660_MIC2_OVTH_600UA			(0x0 << 6)
#define WT5660_MIC2_OVTH_1500UA			(0x1 << 6)
#define WT5660_MIC2_OVTH_2000UA			(0x2 << 6)
#define WT5660_PWW_CWK25M_MASK			(0x1 << 4)
#define WT5660_PWW_CWK25M_SFT			4
#define WT5660_PWW_CWK25M_PD			(0x0 << 4)
#define WT5660_PWW_CWK25M_PU			(0x1 << 4)

/* EQ Contwow 1 (0xb0) */
#define WT5660_EQ_SWC_MASK			(0x1 << 15)
#define WT5660_EQ_SWC_SFT			15
#define WT5660_EQ_SWC_DAC			(0x0 << 15)
#define WT5660_EQ_SWC_ADC			(0x1 << 15)
#define WT5660_EQ_UPD				(0x1 << 14)
#define WT5660_EQ_UPD_BIT			14

/* Jack Detect Contwow (0xbb) */
#define WT5660_JD_MASK				(0x3 << 14)
#define WT5660_JD_SFT				14
#define WT5660_JD_DIS				(0x0 << 14)
#define WT5660_JD_GPIO1				(0x1 << 14)
#define WT5660_JD_GPIO2				(0x2 << 14)
#define WT5660_JD_WOUT_MASK			(0x1 << 11)
#define WT5660_JD_WOUT_SFT			11
#define WT5660_JD_WOUT_DIS			(0x0 << 11)
#define WT5660_JD_WOUT_EN			(0x1 << 11)
#define WT5660_JD_WOUT_TWG_MASK			(0x1 << 10)
#define WT5660_JD_WOUT_TWG_SFT			10
#define WT5660_JD_WOUT_TWG_WO			(0x0 << 10)
#define WT5660_JD_WOUT_TWG_HI			(0x1 << 10)
#define WT5660_JD_SPO_MASK			(0x1 << 9)
#define WT5660_JD_SPO_SFT			9
#define WT5660_JD_SPO_DIS			(0x0 << 9)
#define WT5660_JD_SPO_EN			(0x1 << 9)
#define WT5660_JD_SPO_TWG_MASK			(0x1 << 8)
#define WT5660_JD_SPO_TWG_SFT			8
#define WT5660_JD_SPO_TWG_WO			(0x0 << 8)
#define WT5660_JD_SPO_TWG_HI			(0x1 << 8)

/* IWQ Contwow 1 (0xbd) */
#define WT5660_IWQ_JD_MASK			(0x1 << 15)
#define WT5660_IWQ_JD_SFT			15
#define WT5660_IWQ_JD_BP			(0x0 << 15)
#define WT5660_IWQ_JD_NOW			(0x1 << 15)
#define WT5660_IWQ_OT_MASK			(0x1 << 14)
#define WT5660_IWQ_OT_SFT			14
#define WT5660_IWQ_OT_BP			(0x0 << 14)
#define WT5660_IWQ_OT_NOW			(0x1 << 14)
#define WT5660_JD_STKY_MASK			(0x1 << 13)
#define WT5660_JD_STKY_SFT			13
#define WT5660_JD_STKY_DIS			(0x0 << 13)
#define WT5660_JD_STKY_EN			(0x1 << 13)
#define WT5660_OT_STKY_MASK			(0x1 << 12)
#define WT5660_OT_STKY_SFT			12
#define WT5660_OT_STKY_DIS			(0x0 << 12)
#define WT5660_OT_STKY_EN			(0x1 << 12)
#define WT5660_JD_P_MASK			(0x1 << 11)
#define WT5660_JD_P_SFT				11
#define WT5660_JD_P_NOW				(0x0 << 11)
#define WT5660_JD_P_INV				(0x1 << 11)
#define WT5660_OT_P_MASK			(0x1 << 10)
#define WT5660_OT_P_SFT				10
#define WT5660_OT_P_NOW				(0x0 << 10)
#define WT5660_OT_P_INV				(0x1 << 10)

/* IWQ Contwow 2 (0xbe) */
#define WT5660_IWQ_MB1_OC_MASK			(0x1 << 15)
#define WT5660_IWQ_MB1_OC_SFT			15
#define WT5660_IWQ_MB1_OC_BP			(0x0 << 15)
#define WT5660_IWQ_MB1_OC_NOW			(0x1 << 15)
#define WT5660_IWQ_MB2_OC_MASK			(0x1 << 14)
#define WT5660_IWQ_MB2_OC_SFT			14
#define WT5660_IWQ_MB2_OC_BP			(0x0 << 14)
#define WT5660_IWQ_MB2_OC_NOW			(0x1 << 14)
#define WT5660_MB1_OC_STKY_MASK			(0x1 << 11)
#define WT5660_MB1_OC_STKY_SFT			11
#define WT5660_MB1_OC_STKY_DIS			(0x0 << 11)
#define WT5660_MB1_OC_STKY_EN			(0x1 << 11)
#define WT5660_MB2_OC_STKY_MASK			(0x1 << 10)
#define WT5660_MB2_OC_STKY_SFT			10
#define WT5660_MB2_OC_STKY_DIS			(0x0 << 10)
#define WT5660_MB2_OC_STKY_EN			(0x1 << 10)
#define WT5660_MB1_OC_P_MASK			(0x1 << 7)
#define WT5660_MB1_OC_P_SFT			7
#define WT5660_MB1_OC_P_NOW			(0x0 << 7)
#define WT5660_MB1_OC_P_INV			(0x1 << 7)
#define WT5660_MB2_OC_P_MASK			(0x1 << 6)
#define WT5660_MB2_OC_P_SFT			6
#define WT5660_MB2_OC_P_NOW			(0x0 << 6)
#define WT5660_MB2_OC_P_INV			(0x1 << 6)
#define WT5660_MB1_OC_CWW			(0x1 << 3)
#define WT5660_MB1_OC_CWW_SFT			3
#define WT5660_MB2_OC_CWW			(0x1 << 2)
#define WT5660_MB2_OC_CWW_SFT			2

/* GPIO Contwow 1 (0xc0) */
#define WT5660_GP2_PIN_MASK			(0x1 << 14)
#define WT5660_GP2_PIN_SFT			14
#define WT5660_GP2_PIN_GPIO2			(0x0 << 14)
#define WT5660_GP2_PIN_DMIC1_SDA		(0x1 << 14)
#define WT5660_GP1_PIN_MASK			(0x3 << 12)
#define WT5660_GP1_PIN_SFT			12
#define WT5660_GP1_PIN_GPIO1			(0x0 << 12)
#define WT5660_GP1_PIN_DMIC1_SCW		(0x1 << 12)
#define WT5660_GP1_PIN_IWQ			(0x2 << 12)
#define WT5660_GPIO_M_MASK			(0x1 << 9)
#define WT5660_GPIO_M_SFT			9
#define WT5660_GPIO_M_FWT			(0x0 << 9)
#define WT5660_GPIO_M_PH			(0x1 << 9)

/* GPIO Contwow 3 (0xc2) */
#define WT5660_GP2_PF_MASK			(0x1 << 5)
#define WT5660_GP2_PF_SFT			5
#define WT5660_GP2_PF_IN			(0x0 << 5)
#define WT5660_GP2_PF_OUT			(0x1 << 5)
#define WT5660_GP2_OUT_MASK			(0x1 << 4)
#define WT5660_GP2_OUT_SFT			4
#define WT5660_GP2_OUT_WO			(0x0 << 4)
#define WT5660_GP2_OUT_HI			(0x1 << 4)
#define WT5660_GP2_P_MASK			(0x1 << 3)
#define WT5660_GP2_P_SFT			3
#define WT5660_GP2_P_NOW			(0x0 << 3)
#define WT5660_GP2_P_INV			(0x1 << 3)
#define WT5660_GP1_PF_MASK			(0x1 << 2)
#define WT5660_GP1_PF_SFT			2
#define WT5660_GP1_PF_IN			(0x0 << 2)
#define WT5660_GP1_PF_OUT			(0x1 << 2)
#define WT5660_GP1_OUT_MASK			(0x1 << 1)
#define WT5660_GP1_OUT_SFT			1
#define WT5660_GP1_OUT_WO			(0x0 << 1)
#define WT5660_GP1_OUT_HI			(0x1 << 1)
#define WT5660_GP1_P_MASK			(0x1)
#define WT5660_GP1_P_SFT			0
#define WT5660_GP1_P_NOW			(0x0)
#define WT5660_GP1_P_INV			(0x1)

/* Soft vowume and zewo cwoss contwow 1 (0xd9) */
#define WT5660_SV_MASK				(0x1 << 15)
#define WT5660_SV_SFT				15
#define WT5660_SV_DIS				(0x0 << 15)
#define WT5660_SV_EN				(0x1 << 15)
#define WT5660_SPO_SV_MASK			(0x1 << 14)
#define WT5660_SPO_SV_SFT			14
#define WT5660_SPO_SV_DIS			(0x0 << 14)
#define WT5660_SPO_SV_EN			(0x1 << 14)
#define WT5660_OUT_SV_MASK			(0x1 << 12)
#define WT5660_OUT_SV_SFT			12
#define WT5660_OUT_SV_DIS			(0x0 << 12)
#define WT5660_OUT_SV_EN			(0x1 << 12)
#define WT5660_ZCD_DIG_MASK			(0x1 << 11)
#define WT5660_ZCD_DIG_SFT			11
#define WT5660_ZCD_DIG_DIS			(0x0 << 11)
#define WT5660_ZCD_DIG_EN			(0x1 << 11)
#define WT5660_ZCD_MASK				(0x1 << 10)
#define WT5660_ZCD_SFT				10
#define WT5660_ZCD_PD				(0x0 << 10)
#define WT5660_ZCD_PU				(0x1 << 10)
#define WT5660_SV_DWY_MASK			(0xf)
#define WT5660_SV_DWY_SFT			0

/* Soft vowume and zewo cwoss contwow 2 (0xda) */
#define WT5660_ZCD_SPO_MASK			(0x1 << 15)
#define WT5660_ZCD_SPO_SFT			15
#define WT5660_ZCD_SPO_DIS			(0x0 << 15)
#define WT5660_ZCD_SPO_EN			(0x1 << 15)
#define WT5660_ZCD_OMW_MASK			(0x1 << 8)
#define WT5660_ZCD_OMW_SFT			8
#define WT5660_ZCD_OMW_DIS			(0x0 << 8)
#define WT5660_ZCD_OMW_EN			(0x1 << 8)
#define WT5660_ZCD_OMW_MASK			(0x1 << 7)
#define WT5660_ZCD_OMW_SFT			7
#define WT5660_ZCD_OMW_DIS			(0x0 << 7)
#define WT5660_ZCD_OMW_EN			(0x1 << 7)
#define WT5660_ZCD_SPM_MASK			(0x1 << 6)
#define WT5660_ZCD_SPM_SFT			6
#define WT5660_ZCD_SPM_DIS			(0x0 << 6)
#define WT5660_ZCD_SPM_EN			(0x1 << 6)
#define WT5660_ZCD_WMW_MASK			(0x1 << 5)
#define WT5660_ZCD_WMW_SFT			5
#define WT5660_ZCD_WMW_DIS			(0x0 << 5)
#define WT5660_ZCD_WMW_EN			(0x1 << 5)
#define WT5660_ZCD_WMW_MASK			(0x1 << 4)
#define WT5660_ZCD_WMW_SFT			4
#define WT5660_ZCD_WMW_DIS			(0x0 << 4)
#define WT5660_ZCD_WMW_EN			(0x1 << 4)

/* Genewaw Contwow 1 (0xfa) */
#define WT5660_PWW_VWEF_HP			(0x1 << 11)
#define WT5660_PWW_VWEF_HP_SFT			11
#define WT5660_AUTO_DIS_AMP			(0x1 << 6)
#define WT5660_MCWK_DET				(0x1 << 5)
#define WT5660_POW_CWKDET			(0x1 << 1)
#define WT5660_DIG_GATE_CTWW			(0x1)
#define WT5660_DIG_GATE_CTWW_SFT		0

/* System Cwock Souwce */
#define WT5660_SCWK_S_MCWK			0
#define WT5660_SCWK_S_PWW1			1
#define WT5660_SCWK_S_WCCWK			2

/* PWW1 Souwce */
#define WT5660_PWW1_S_MCWK			0
#define WT5660_PWW1_S_BCWK			1

enum {
	WT5660_AIF1,
	WT5660_AIFS,
};

stwuct wt5660_pwiv {
	stwuct snd_soc_component *component;
	stwuct wt5660_pwatfowm_data pdata;
	stwuct wegmap *wegmap;
	stwuct cwk *mcwk;

	int syscwk;
	int syscwk_swc;
	int wwck[WT5660_AIFS];
	int bcwk[WT5660_AIFS];
	int mastew[WT5660_AIFS];

	int pww_swc;
	int pww_in;
	int pww_out;
};

#endif
