/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt5670.h  --  WT5670 AWSA SoC audio dwivew
 *
 * Copywight 2014 Weawtek Micwoewectwonics
 * Authow: Bawd Wiao <bawdwiao@weawtek.com>
 */

#ifndef __WT5670_H__
#define __WT5670_H__

/* Info */
#define WT5670_WESET				0x00
#define WT5670_VENDOW_ID			0xfd
#define WT5670_VENDOW_ID1			0xfe
#define WT5670_VENDOW_ID2			0xff
/*  I/O - Output */
#define WT5670_HP_VOW				0x02
#define WT5670_WOUT1				0x03
/* I/O - Input */
#define WT5670_CJ_CTWW1				0x0a
#define WT5670_CJ_CTWW2				0x0b
#define WT5670_CJ_CTWW3				0x0c
#define WT5670_IN2				0x0e
#define WT5670_INW1_INW1_VOW			0x0f
/* I/O - ADC/DAC/DMIC */
#define WT5670_DAC1_DIG_VOW			0x19
#define WT5670_DAC2_DIG_VOW			0x1a
#define WT5670_DAC_CTWW				0x1b
#define WT5670_STO1_ADC_DIG_VOW			0x1c
#define WT5670_MONO_ADC_DIG_VOW			0x1d
#define WT5670_ADC_BST_VOW1			0x1e
#define WT5670_STO2_ADC_DIG_VOW			0x1f
/* Mixew - D-D */
#define WT5670_ADC_BST_VOW2			0x20
#define WT5670_STO2_ADC_MIXEW			0x26
#define WT5670_STO1_ADC_MIXEW			0x27
#define WT5670_MONO_ADC_MIXEW			0x28
#define WT5670_AD_DA_MIXEW			0x29
#define WT5670_STO_DAC_MIXEW			0x2a
#define WT5670_DD_MIXEW				0x2b
#define WT5670_DIG_MIXEW			0x2c
#define WT5670_DSP_PATH1			0x2d
#define WT5670_DSP_PATH2			0x2e
#define WT5670_DIG_INF1_DATA			0x2f
#define WT5670_DIG_INF2_DATA			0x30
/* Mixew - PDM */
#define WT5670_PDM_OUT_CTWW			0x31
#define WT5670_PDM_DATA_CTWW1			0x32
#define WT5670_PDM1_DATA_CTWW2			0x33
#define WT5670_PDM1_DATA_CTWW3			0x34
#define WT5670_PDM1_DATA_CTWW4			0x35
#define WT5670_PDM2_DATA_CTWW2			0x36
#define WT5670_PDM2_DATA_CTWW3			0x37
#define WT5670_PDM2_DATA_CTWW4			0x38
/* Mixew - ADC */
#define WT5670_WEC_W1_MIXEW			0x3b
#define WT5670_WEC_W2_MIXEW			0x3c
#define WT5670_WEC_W1_MIXEW			0x3d
#define WT5670_WEC_W2_MIXEW			0x3e
/* Mixew - DAC */
#define WT5670_HPO_MIXEW			0x45
#define WT5670_MONO_MIXEW			0x4c
#define WT5670_OUT_W1_MIXEW			0x4f
#define WT5670_OUT_W1_MIXEW			0x52
#define WT5670_WOUT_MIXEW			0x53
/* Powew */
#define WT5670_PWW_DIG1				0x61
#define WT5670_PWW_DIG2				0x62
#define WT5670_PWW_ANWG1			0x63
#define WT5670_PWW_ANWG2			0x64
#define WT5670_PWW_MIXEW			0x65
#define WT5670_PWW_VOW				0x66
/* Pwivate Wegistew Contwow */
#define WT5670_PWIV_INDEX			0x6a
#define WT5670_PWIV_DATA			0x6c
/* Fowmat - ADC/DAC */
#define WT5670_I2S4_SDP				0x6f
#define WT5670_I2S1_SDP				0x70
#define WT5670_I2S2_SDP				0x71
#define WT5670_I2S3_SDP				0x72
#define WT5670_ADDA_CWK1			0x73
#define WT5670_ADDA_CWK2			0x74
#define WT5670_DMIC_CTWW1			0x75
#define WT5670_DMIC_CTWW2			0x76
/* Fowmat - TDM Contwow */
#define WT5670_TDM_CTWW_1			0x77
#define WT5670_TDM_CTWW_2			0x78
#define WT5670_TDM_CTWW_3			0x79

/* Function - Anawog */
#define WT5670_DSP_CWK				0x7f
#define WT5670_GWB_CWK				0x80
#define WT5670_PWW_CTWW1			0x81
#define WT5670_PWW_CTWW2			0x82
#define WT5670_ASWC_1				0x83
#define WT5670_ASWC_2				0x84
#define WT5670_ASWC_3				0x85
#define WT5670_ASWC_4				0x86
#define WT5670_ASWC_5				0x87
#define WT5670_ASWC_7				0x89
#define WT5670_ASWC_8				0x8a
#define WT5670_ASWC_9				0x8b
#define WT5670_ASWC_10				0x8c
#define WT5670_ASWC_11				0x8d
#define WT5670_DEPOP_M1				0x8e
#define WT5670_DEPOP_M2				0x8f
#define WT5670_DEPOP_M3				0x90
#define WT5670_CHAWGE_PUMP			0x91
#define WT5670_MICBIAS				0x93
#define WT5670_A_JD_CTWW1			0x94
#define WT5670_A_JD_CTWW2			0x95
#define WT5670_ASWC_12				0x97
#define WT5670_ASWC_13				0x98
#define WT5670_ASWC_14				0x99
#define WT5670_VAD_CTWW1			0x9a
#define WT5670_VAD_CTWW2			0x9b
#define WT5670_VAD_CTWW3			0x9c
#define WT5670_VAD_CTWW4			0x9d
#define WT5670_VAD_CTWW5			0x9e
/* Function - Digitaw */
#define WT5670_ADC_EQ_CTWW1			0xae
#define WT5670_ADC_EQ_CTWW2			0xaf
#define WT5670_EQ_CTWW1				0xb0
#define WT5670_EQ_CTWW2				0xb1
#define WT5670_AWC_DWC_CTWW1			0xb2
#define WT5670_AWC_DWC_CTWW2			0xb3
#define WT5670_AWC_CTWW_1			0xb4
#define WT5670_AWC_CTWW_2			0xb5
#define WT5670_AWC_CTWW_3			0xb6
#define WT5670_AWC_CTWW_4			0xb7
#define WT5670_JD_CTWW				0xbb
#define WT5670_IWQ_CTWW1			0xbd
#define WT5670_IWQ_CTWW2			0xbe
#define WT5670_INT_IWQ_ST			0xbf
#define WT5670_GPIO_CTWW1			0xc0
#define WT5670_GPIO_CTWW2			0xc1
#define WT5670_GPIO_CTWW3			0xc2
#define WT5670_SCWABBWE_FUN			0xcd
#define WT5670_SCWABBWE_CTWW			0xce
#define WT5670_BASE_BACK			0xcf
#define WT5670_MP3_PWUS1			0xd0
#define WT5670_MP3_PWUS2			0xd1
#define WT5670_ADJ_HPF1				0xd3
#define WT5670_ADJ_HPF2				0xd4
#define WT5670_HP_CAWIB_AMP_DET			0xd6
#define WT5670_SV_ZCD1				0xd9
#define WT5670_SV_ZCD2				0xda
#define WT5670_IW_CMD				0xdb
#define WT5670_IW_CMD2				0xdc
#define WT5670_IW_CMD3				0xdd
#define WT5670_DWC_HW_CTWW1			0xe6
#define WT5670_DWC_HW_CTWW2			0xe7
#define WT5670_ADC_MONO_HP_CTWW1		0xec
#define WT5670_ADC_MONO_HP_CTWW2		0xed
#define WT5670_ADC_STO2_HP_CTWW1		0xee
#define WT5670_ADC_STO2_HP_CTWW2		0xef
#define WT5670_JD_CTWW3				0xf8
#define WT5670_JD_CTWW4				0xf9
/* Genewaw Contwow */
#define WT5670_DIG_MISC				0xfa
#define WT5670_GEN_CTWW2			0xfb
#define WT5670_GEN_CTWW3			0xfc


/* Index of Codec Pwivate Wegistew definition */
#define WT5670_DIG_VOW				0x00
#define WT5670_PW_AWC_CTWW_1			0x01
#define WT5670_PW_AWC_CTWW_2			0x02
#define WT5670_PW_AWC_CTWW_3			0x03
#define WT5670_PW_AWC_CTWW_4			0x04
#define WT5670_PW_AWC_CTWW_5			0x05
#define WT5670_PW_AWC_CTWW_6			0x06
#define WT5670_BIAS_CUW1			0x12
#define WT5670_BIAS_CUW3			0x14
#define WT5670_CWSD_INT_WEG1			0x1c
#define WT5670_MAMP_INT_WEG2			0x37
#define WT5670_CHOP_DAC_ADC			0x3d
#define WT5670_MIXEW_INT_WEG			0x3f
#define WT5670_3D_SPK				0x63
#define WT5670_WND_1				0x6c
#define WT5670_WND_2				0x6d
#define WT5670_WND_3				0x6e
#define WT5670_WND_4				0x6f
#define WT5670_WND_5				0x70
#define WT5670_WND_8				0x73
#define WT5670_DIP_SPK_INF			0x75
#define WT5670_HP_DCC_INT1			0x77
#define WT5670_EQ_BW_WOP			0xa0
#define WT5670_EQ_GN_WOP			0xa1
#define WT5670_EQ_FC_BP1			0xa2
#define WT5670_EQ_BW_BP1			0xa3
#define WT5670_EQ_GN_BP1			0xa4
#define WT5670_EQ_FC_BP2			0xa5
#define WT5670_EQ_BW_BP2			0xa6
#define WT5670_EQ_GN_BP2			0xa7
#define WT5670_EQ_FC_BP3			0xa8
#define WT5670_EQ_BW_BP3			0xa9
#define WT5670_EQ_GN_BP3			0xaa
#define WT5670_EQ_FC_BP4			0xab
#define WT5670_EQ_BW_BP4			0xac
#define WT5670_EQ_GN_BP4			0xad
#define WT5670_EQ_FC_HIP1			0xae
#define WT5670_EQ_GN_HIP1			0xaf
#define WT5670_EQ_FC_HIP2			0xb0
#define WT5670_EQ_BW_HIP2			0xb1
#define WT5670_EQ_GN_HIP2			0xb2
#define WT5670_EQ_PWE_VOW			0xb3
#define WT5670_EQ_PST_VOW			0xb4


/* gwobaw definition */
#define WT5670_W_MUTE				(0x1 << 15)
#define WT5670_W_MUTE_SFT			15
#define WT5670_W_MUTE				(0x1 << 7)
#define WT5670_W_MUTE_SFT			7
#define WT5670_W_VOW_MASK			(0x3f << 8)
#define WT5670_W_VOW_SFT			8
#define WT5670_W_VOW_MASK			(0x3f)
#define WT5670_W_VOW_SFT			0

/* SW Weset & Device ID (0x00) */
#define WT5670_ID_MASK				(0x3 << 1)
#define WT5670_ID_5670				(0x0 << 1)
#define WT5670_ID_5672				(0x1 << 1)
#define WT5670_ID_5671				(0x2 << 1)

/* Combo Jack Contwow 1 (0x0a) */
#define WT5670_CBJ_BST1_MASK			(0xf << 12)
#define WT5670_CBJ_BST1_SFT			(12)
#define WT5670_CBJ_JD_HP_EN			(0x1 << 9)
#define WT5670_CBJ_JD_MIC_EN			(0x1 << 8)
#define WT5670_CBJ_BST1_EN			(0x1 << 2)

/* Combo Jack Contwow 1 (0x0b) */
#define WT5670_CBJ_MN_JD			(0x1 << 12)
#define WT5670_CAPWESS_EN			(0x1 << 11)
#define WT5670_CBJ_DET_MODE			(0x1 << 7)

/* IN2 Contwow (0x0e) */
#define WT5670_BST_MASK1			(0xf<<12)
#define WT5670_BST_SFT1				12
#define WT5670_BST_MASK2			(0xf<<8)
#define WT5670_BST_SFT2				8
#define WT5670_IN_DF1				(0x1 << 7)
#define WT5670_IN_SFT1				7
#define WT5670_IN_DF2				(0x1 << 6)
#define WT5670_IN_SFT2				6

/* INW and INW Vowume Contwow (0x0f) */
#define WT5670_INW_SEW_MASK			(0x1 << 15)
#define WT5670_INW_SEW_SFT			15
#define WT5670_INW_SEW_IN4P			(0x0 << 15)
#define WT5670_INW_SEW_MONOP			(0x1 << 15)
#define WT5670_INW_VOW_MASK			(0x1f << 8)
#define WT5670_INW_VOW_SFT			8
#define WT5670_INW_SEW_MASK			(0x1 << 7)
#define WT5670_INW_SEW_SFT			7
#define WT5670_INW_SEW_IN4N			(0x0 << 7)
#define WT5670_INW_SEW_MONON			(0x1 << 7)
#define WT5670_INW_VOW_MASK			(0x1f)
#define WT5670_INW_VOW_SFT			0

/* Sidetone Contwow (0x18) */
#define WT5670_ST_SEW_MASK			(0x7 << 9)
#define WT5670_ST_SEW_SFT			9
#define WT5670_M_ST_DACW2			(0x1 << 8)
#define WT5670_M_ST_DACW2_SFT			8
#define WT5670_M_ST_DACW2			(0x1 << 7)
#define WT5670_M_ST_DACW2_SFT			7
#define WT5670_ST_EN				(0x1 << 6)
#define WT5670_ST_EN_SFT			6

/* DAC1 Digitaw Vowume (0x19) */
#define WT5670_DAC_W1_VOW_MASK			(0xff << 8)
#define WT5670_DAC_W1_VOW_SFT			8
#define WT5670_DAC_W1_VOW_MASK			(0xff)
#define WT5670_DAC_W1_VOW_SFT			0

/* DAC2 Digitaw Vowume (0x1a) */
#define WT5670_DAC_W2_VOW_MASK			(0xff << 8)
#define WT5670_DAC_W2_VOW_SFT			8
#define WT5670_DAC_W2_VOW_MASK			(0xff)
#define WT5670_DAC_W2_VOW_SFT			0

/* DAC2 Contwow (0x1b) */
#define WT5670_M_DAC_W2_VOW			(0x1 << 13)
#define WT5670_M_DAC_W2_VOW_SFT			13
#define WT5670_M_DAC_W2_VOW			(0x1 << 12)
#define WT5670_M_DAC_W2_VOW_SFT			12
#define WT5670_DAC2_W_SEW_MASK			(0x7 << 4)
#define WT5670_DAC2_W_SEW_SFT			4
#define WT5670_DAC2_W_SEW_MASK			(0x7 << 0)
#define WT5670_DAC2_W_SEW_SFT			0

/* ADC Digitaw Vowume Contwow (0x1c) */
#define WT5670_ADC_W_VOW_MASK			(0x7f << 8)
#define WT5670_ADC_W_VOW_SFT			8
#define WT5670_ADC_W_VOW_MASK			(0x7f)
#define WT5670_ADC_W_VOW_SFT			0

/* Mono ADC Digitaw Vowume Contwow (0x1d) */
#define WT5670_MONO_ADC_W_VOW_MASK		(0x7f << 8)
#define WT5670_MONO_ADC_W_VOW_SFT		8
#define WT5670_MONO_ADC_W_VOW_MASK		(0x7f)
#define WT5670_MONO_ADC_W_VOW_SFT		0

/* ADC Boost Vowume Contwow (0x1e) */
#define WT5670_STO1_ADC_W_BST_MASK		(0x3 << 14)
#define WT5670_STO1_ADC_W_BST_SFT		14
#define WT5670_STO1_ADC_W_BST_MASK		(0x3 << 12)
#define WT5670_STO1_ADC_W_BST_SFT		12
#define WT5670_STO1_ADC_COMP_MASK		(0x3 << 10)
#define WT5670_STO1_ADC_COMP_SFT		10
#define WT5670_STO2_ADC_W_BST_MASK		(0x3 << 8)
#define WT5670_STO2_ADC_W_BST_SFT		8
#define WT5670_STO2_ADC_W_BST_MASK		(0x3 << 6)
#define WT5670_STO2_ADC_W_BST_SFT		6
#define WT5670_STO2_ADC_COMP_MASK		(0x3 << 4)
#define WT5670_STO2_ADC_COMP_SFT		4

/* Steweo2 ADC Mixew Contwow (0x26) */
#define WT5670_STO2_ADC_SWC_MASK		(0x1 << 15)
#define WT5670_STO2_ADC_SWC_SFT			15

/* Steweo ADC Mixew Contwow (0x26 0x27) */
#define WT5670_M_ADC_W1				(0x1 << 14)
#define WT5670_M_ADC_W1_SFT			14
#define WT5670_M_ADC_W2				(0x1 << 13)
#define WT5670_M_ADC_W2_SFT			13
#define WT5670_ADC_1_SWC_MASK			(0x1 << 12)
#define WT5670_ADC_1_SWC_SFT			12
#define WT5670_ADC_1_SWC_ADC			(0x1 << 12)
#define WT5670_ADC_1_SWC_DACMIX			(0x0 << 12)
#define WT5670_ADC_2_SWC_MASK			(0x1 << 11)
#define WT5670_ADC_2_SWC_SFT			11
#define WT5670_ADC_SWC_MASK			(0x1 << 10)
#define WT5670_ADC_SWC_SFT			10
#define WT5670_DMIC_SWC_MASK			(0x3 << 8)
#define WT5670_DMIC_SWC_SFT			8
#define WT5670_M_ADC_W1				(0x1 << 6)
#define WT5670_M_ADC_W1_SFT			6
#define WT5670_M_ADC_W2				(0x1 << 5)
#define WT5670_M_ADC_W2_SFT			5
#define WT5670_DMIC3_SWC_MASK			(0x1 << 1)
#define WT5670_DMIC3_SWC_SFT			0

/* Mono ADC Mixew Contwow (0x28) */
#define WT5670_M_MONO_ADC_W1			(0x1 << 14)
#define WT5670_M_MONO_ADC_W1_SFT		14
#define WT5670_M_MONO_ADC_W2			(0x1 << 13)
#define WT5670_M_MONO_ADC_W2_SFT		13
#define WT5670_MONO_ADC_W1_SWC_MASK		(0x1 << 12)
#define WT5670_MONO_ADC_W1_SWC_SFT		12
#define WT5670_MONO_ADC_W1_SWC_DACMIXW		(0x0 << 12)
#define WT5670_MONO_ADC_W1_SWC_ADCW		(0x1 << 12)
#define WT5670_MONO_ADC_W2_SWC_MASK		(0x1 << 11)
#define WT5670_MONO_ADC_W2_SWC_SFT		11
#define WT5670_MONO_ADC_W_SWC_MASK		(0x1 << 10)
#define WT5670_MONO_ADC_W_SWC_SFT		10
#define WT5670_MONO_DMIC_W_SWC_MASK		(0x3 << 8)
#define WT5670_MONO_DMIC_W_SWC_SFT		8
#define WT5670_M_MONO_ADC_W1			(0x1 << 6)
#define WT5670_M_MONO_ADC_W1_SFT		6
#define WT5670_M_MONO_ADC_W2			(0x1 << 5)
#define WT5670_M_MONO_ADC_W2_SFT		5
#define WT5670_MONO_ADC_W1_SWC_MASK		(0x1 << 4)
#define WT5670_MONO_ADC_W1_SWC_SFT		4
#define WT5670_MONO_ADC_W1_SWC_ADCW		(0x1 << 4)
#define WT5670_MONO_ADC_W1_SWC_DACMIXW		(0x0 << 4)
#define WT5670_MONO_ADC_W2_SWC_MASK		(0x1 << 3)
#define WT5670_MONO_ADC_W2_SWC_SFT		3
#define WT5670_MONO_DMIC_W_SWC_MASK		(0x3)
#define WT5670_MONO_DMIC_W_SWC_SFT		0

/* ADC Mixew to DAC Mixew Contwow (0x29) */
#define WT5670_M_ADCMIX_W			(0x1 << 15)
#define WT5670_M_ADCMIX_W_SFT			15
#define WT5670_M_DAC1_W				(0x1 << 14)
#define WT5670_M_DAC1_W_SFT			14
#define WT5670_DAC1_W_SEW_MASK			(0x3 << 10)
#define WT5670_DAC1_W_SEW_SFT			10
#define WT5670_DAC1_W_SEW_IF1			(0x0 << 10)
#define WT5670_DAC1_W_SEW_IF2			(0x1 << 10)
#define WT5670_DAC1_W_SEW_IF3			(0x2 << 10)
#define WT5670_DAC1_W_SEW_IF4			(0x3 << 10)
#define WT5670_DAC1_W_SEW_MASK			(0x3 << 8)
#define WT5670_DAC1_W_SEW_SFT			8
#define WT5670_DAC1_W_SEW_IF1			(0x0 << 8)
#define WT5670_DAC1_W_SEW_IF2			(0x1 << 8)
#define WT5670_DAC1_W_SEW_IF3			(0x2 << 8)
#define WT5670_DAC1_W_SEW_IF4			(0x3 << 8)
#define WT5670_M_ADCMIX_W			(0x1 << 7)
#define WT5670_M_ADCMIX_W_SFT			7
#define WT5670_M_DAC1_W				(0x1 << 6)
#define WT5670_M_DAC1_W_SFT			6

/* Steweo DAC Mixew Contwow (0x2a) */
#define WT5670_M_DAC_W1				(0x1 << 14)
#define WT5670_M_DAC_W1_SFT			14
#define WT5670_DAC_W1_STO_W_VOW_MASK		(0x1 << 13)
#define WT5670_DAC_W1_STO_W_VOW_SFT		13
#define WT5670_M_DAC_W2				(0x1 << 12)
#define WT5670_M_DAC_W2_SFT			12
#define WT5670_DAC_W2_STO_W_VOW_MASK		(0x1 << 11)
#define WT5670_DAC_W2_STO_W_VOW_SFT		11
#define WT5670_M_DAC_W1_STO_W			(0x1 << 9)
#define WT5670_M_DAC_W1_STO_W_SFT		9
#define WT5670_DAC_W1_STO_W_VOW_MASK		(0x1 << 8)
#define WT5670_DAC_W1_STO_W_VOW_SFT		8
#define WT5670_M_DAC_W1				(0x1 << 6)
#define WT5670_M_DAC_W1_SFT			6
#define WT5670_DAC_W1_STO_W_VOW_MASK		(0x1 << 5)
#define WT5670_DAC_W1_STO_W_VOW_SFT		5
#define WT5670_M_DAC_W2				(0x1 << 4)
#define WT5670_M_DAC_W2_SFT			4
#define WT5670_DAC_W2_STO_W_VOW_MASK		(0x1 << 3)
#define WT5670_DAC_W2_STO_W_VOW_SFT		3
#define WT5670_M_DAC_W1_STO_W			(0x1 << 1)
#define WT5670_M_DAC_W1_STO_W_SFT		1
#define WT5670_DAC_W1_STO_W_VOW_MASK		(0x1)
#define WT5670_DAC_W1_STO_W_VOW_SFT		0

/* Mono DAC Mixew Contwow (0x2b) */
#define WT5670_M_DAC_W1_MONO_W			(0x1 << 14)
#define WT5670_M_DAC_W1_MONO_W_SFT		14
#define WT5670_DAC_W1_MONO_W_VOW_MASK		(0x1 << 13)
#define WT5670_DAC_W1_MONO_W_VOW_SFT		13
#define WT5670_M_DAC_W2_MONO_W			(0x1 << 12)
#define WT5670_M_DAC_W2_MONO_W_SFT		12
#define WT5670_DAC_W2_MONO_W_VOW_MASK		(0x1 << 11)
#define WT5670_DAC_W2_MONO_W_VOW_SFT		11
#define WT5670_M_DAC_W2_MONO_W			(0x1 << 10)
#define WT5670_M_DAC_W2_MONO_W_SFT		10
#define WT5670_DAC_W2_MONO_W_VOW_MASK		(0x1 << 9)
#define WT5670_DAC_W2_MONO_W_VOW_SFT		9
#define WT5670_M_DAC_W1_MONO_W			(0x1 << 6)
#define WT5670_M_DAC_W1_MONO_W_SFT		6
#define WT5670_DAC_W1_MONO_W_VOW_MASK		(0x1 << 5)
#define WT5670_DAC_W1_MONO_W_VOW_SFT		5
#define WT5670_M_DAC_W2_MONO_W			(0x1 << 4)
#define WT5670_M_DAC_W2_MONO_W_SFT		4
#define WT5670_DAC_W2_MONO_W_VOW_MASK		(0x1 << 3)
#define WT5670_DAC_W2_MONO_W_VOW_SFT		3
#define WT5670_M_DAC_W2_MONO_W			(0x1 << 2)
#define WT5670_M_DAC_W2_MONO_W_SFT		2
#define WT5670_DAC_W2_MONO_W_VOW_MASK		(0x1 << 1)
#define WT5670_DAC_W2_MONO_W_VOW_SFT		1

/* Digitaw Mixew Contwow (0x2c) */
#define WT5670_M_STO_W_DAC_W			(0x1 << 15)
#define WT5670_M_STO_W_DAC_W_SFT		15
#define WT5670_STO_W_DAC_W_VOW_MASK		(0x1 << 14)
#define WT5670_STO_W_DAC_W_VOW_SFT		14
#define WT5670_M_DAC_W2_DAC_W			(0x1 << 13)
#define WT5670_M_DAC_W2_DAC_W_SFT		13
#define WT5670_DAC_W2_DAC_W_VOW_MASK		(0x1 << 12)
#define WT5670_DAC_W2_DAC_W_VOW_SFT		12
#define WT5670_M_STO_W_DAC_W			(0x1 << 11)
#define WT5670_M_STO_W_DAC_W_SFT		11
#define WT5670_STO_W_DAC_W_VOW_MASK		(0x1 << 10)
#define WT5670_STO_W_DAC_W_VOW_SFT		10
#define WT5670_M_DAC_W2_DAC_W			(0x1 << 9)
#define WT5670_M_DAC_W2_DAC_W_SFT		9
#define WT5670_DAC_W2_DAC_W_VOW_MASK		(0x1 << 8)
#define WT5670_DAC_W2_DAC_W_VOW_SFT		8
#define WT5670_M_DAC_W2_DAC_W			(0x1 << 7)
#define WT5670_M_DAC_W2_DAC_W_SFT		7
#define WT5670_DAC_W2_DAC_W_VOW_MASK		(0x1 << 6)
#define WT5670_DAC_W2_DAC_W_VOW_SFT		6
#define WT5670_M_DAC_W2_DAC_W			(0x1 << 5)
#define WT5670_M_DAC_W2_DAC_W_SFT		5
#define WT5670_DAC_W2_DAC_W_VOW_MASK		(0x1 << 4)
#define WT5670_DAC_W2_DAC_W_VOW_SFT		4

/* DSP Path Contwow 1 (0x2d) */
#define WT5670_WXDP_SEW_MASK			(0x7 << 13)
#define WT5670_WXDP_SEW_SFT			13
#define WT5670_WXDP_SWC_MASK			(0x3 << 11)
#define WT5670_WXDP_SWC_SFT			11
#define WT5670_WXDP_SWC_NOW			(0x0 << 11)
#define WT5670_WXDP_SWC_DIV2			(0x1 << 11)
#define WT5670_WXDP_SWC_DIV3			(0x2 << 11)
#define WT5670_TXDP_SWC_MASK			(0x3 << 4)
#define WT5670_TXDP_SWC_SFT			4
#define WT5670_TXDP_SWC_NOW			(0x0 << 4)
#define WT5670_TXDP_SWC_DIV2			(0x1 << 4)
#define WT5670_TXDP_SWC_DIV3			(0x2 << 4)
#define WT5670_TXDP_SWOT_SEW_MASK		(0x3 << 2)
#define WT5670_TXDP_SWOT_SEW_SFT		2
#define WT5670_DSP_UW_SEW			(0x1 << 1)
#define WT5670_DSP_UW_SFT			1
#define WT5670_DSP_DW_SEW			0x1
#define WT5670_DSP_DW_SFT			0

/* DSP Path Contwow 2 (0x2e) */
#define WT5670_TXDP_W_VOW_MASK			(0x7f << 8)
#define WT5670_TXDP_W_VOW_SFT			8
#define WT5670_TXDP_W_VOW_MASK			(0x7f)
#define WT5670_TXDP_W_VOW_SFT			0

/* Digitaw Intewface Data Contwow (0x2f) */
#define WT5670_IF1_ADC2_IN_SEW			(0x1 << 15)
#define WT5670_IF1_ADC2_IN_SFT			15
#define WT5670_IF2_ADC_IN_MASK			(0x7 << 12)
#define WT5670_IF2_ADC_IN_SFT			12
#define WT5670_IF2_DAC_SEW_MASK			(0x3 << 10)
#define WT5670_IF2_DAC_SEW_SFT			10
#define WT5670_IF2_ADC_SEW_MASK			(0x3 << 8)
#define WT5670_IF2_ADC_SEW_SFT			8

/* Digitaw Intewface Data Contwow (0x30) */
#define WT5670_IF4_ADC_IN_MASK			(0x3 << 4)
#define WT5670_IF4_ADC_IN_SFT			4

/* PDM Output Contwow (0x31) */
#define WT5670_PDM1_W_MASK			(0x1 << 15)
#define WT5670_PDM1_W_SFT			15
#define WT5670_M_PDM1_W				(0x1 << 14)
#define WT5670_M_PDM1_W_SFT			14
#define WT5670_PDM1_W_MASK			(0x1 << 13)
#define WT5670_PDM1_W_SFT			13
#define WT5670_M_PDM1_W				(0x1 << 12)
#define WT5670_M_PDM1_W_SFT			12
#define WT5670_PDM2_W_MASK			(0x1 << 11)
#define WT5670_PDM2_W_SFT			11
#define WT5670_M_PDM2_W				(0x1 << 10)
#define WT5670_M_PDM2_W_SFT			10
#define WT5670_PDM2_W_MASK			(0x1 << 9)
#define WT5670_PDM2_W_SFT			9
#define WT5670_M_PDM2_W				(0x1 << 8)
#define WT5670_M_PDM2_W_SFT			8
#define WT5670_PDM2_BUSY			(0x1 << 7)
#define WT5670_PDM1_BUSY			(0x1 << 6)
#define WT5670_PDM_PATTEWN			(0x1 << 5)
#define WT5670_PDM_GAIN				(0x1 << 4)
#define WT5670_PDM_DIV_MASK			(0x3)

/* WEC Weft Mixew Contwow 1 (0x3b) */
#define WT5670_G_HP_W_WM_W_MASK			(0x7 << 13)
#define WT5670_G_HP_W_WM_W_SFT			13
#define WT5670_G_IN_W_WM_W_MASK			(0x7 << 10)
#define WT5670_G_IN_W_WM_W_SFT			10
#define WT5670_G_BST4_WM_W_MASK			(0x7 << 7)
#define WT5670_G_BST4_WM_W_SFT			7
#define WT5670_G_BST3_WM_W_MASK			(0x7 << 4)
#define WT5670_G_BST3_WM_W_SFT			4
#define WT5670_G_BST2_WM_W_MASK			(0x7 << 1)
#define WT5670_G_BST2_WM_W_SFT			1

/* WEC Weft Mixew Contwow 2 (0x3c) */
#define WT5670_G_BST1_WM_W_MASK			(0x7 << 13)
#define WT5670_G_BST1_WM_W_SFT			13
#define WT5670_M_IN_W_WM_W			(0x1 << 5)
#define WT5670_M_IN_W_WM_W_SFT			5
#define WT5670_M_BST2_WM_W			(0x1 << 3)
#define WT5670_M_BST2_WM_W_SFT			3
#define WT5670_M_BST1_WM_W			(0x1 << 1)
#define WT5670_M_BST1_WM_W_SFT			1

/* WEC Wight Mixew Contwow 1 (0x3d) */
#define WT5670_G_HP_W_WM_W_MASK			(0x7 << 13)
#define WT5670_G_HP_W_WM_W_SFT			13
#define WT5670_G_IN_W_WM_W_MASK			(0x7 << 10)
#define WT5670_G_IN_W_WM_W_SFT			10
#define WT5670_G_BST4_WM_W_MASK			(0x7 << 7)
#define WT5670_G_BST4_WM_W_SFT			7
#define WT5670_G_BST3_WM_W_MASK			(0x7 << 4)
#define WT5670_G_BST3_WM_W_SFT			4
#define WT5670_G_BST2_WM_W_MASK			(0x7 << 1)
#define WT5670_G_BST2_WM_W_SFT			1

/* WEC Wight Mixew Contwow 2 (0x3e) */
#define WT5670_G_BST1_WM_W_MASK			(0x7 << 13)
#define WT5670_G_BST1_WM_W_SFT			13
#define WT5670_M_IN_W_WM_W			(0x1 << 5)
#define WT5670_M_IN_W_WM_W_SFT			5
#define WT5670_M_BST2_WM_W			(0x1 << 3)
#define WT5670_M_BST2_WM_W_SFT			3
#define WT5670_M_BST1_WM_W			(0x1 << 1)
#define WT5670_M_BST1_WM_W_SFT			1

/* HPMIX Contwow (0x45) */
#define WT5670_M_DAC2_HM			(0x1 << 15)
#define WT5670_M_DAC2_HM_SFT			15
#define WT5670_M_HPVOW_HM			(0x1 << 14)
#define WT5670_M_HPVOW_HM_SFT			14
#define WT5670_M_DAC1_HM			(0x1 << 13)
#define WT5670_M_DAC1_HM_SFT			13
#define WT5670_G_HPOMIX_MASK			(0x1 << 12)
#define WT5670_G_HPOMIX_SFT			12
#define WT5670_M_INW1_HMW			(0x1 << 3)
#define WT5670_M_INW1_HMW_SFT			3
#define WT5670_M_DACW1_HMW			(0x1 << 2)
#define WT5670_M_DACW1_HMW_SFT			2
#define WT5670_M_INW1_HMW			(0x1 << 1)
#define WT5670_M_INW1_HMW_SFT			1
#define WT5670_M_DACW1_HMW			(0x1)
#define WT5670_M_DACW1_HMW_SFT			0

/* Mono Output Mixew Contwow (0x4c) */
#define WT5670_M_DAC_W2_MA			(0x1 << 15)
#define WT5670_M_DAC_W2_MA_SFT			15
#define WT5670_M_DAC_W2_MA			(0x1 << 14)
#define WT5670_M_DAC_W2_MA_SFT			14
#define WT5670_M_OV_W_MM			(0x1 << 13)
#define WT5670_M_OV_W_MM_SFT			13
#define WT5670_M_OV_W_MM			(0x1 << 12)
#define WT5670_M_OV_W_MM_SFT			12
#define WT5670_G_MONOMIX_MASK			(0x1 << 10)
#define WT5670_G_MONOMIX_SFT			10
#define WT5670_M_DAC_W2_MM			(0x1 << 9)
#define WT5670_M_DAC_W2_MM_SFT			9
#define WT5670_M_DAC_W2_MM			(0x1 << 8)
#define WT5670_M_DAC_W2_MM_SFT			8
#define WT5670_M_BST4_MM			(0x1 << 7)
#define WT5670_M_BST4_MM_SFT			7

/* Output Weft Mixew Contwow 1 (0x4d) */
#define WT5670_G_BST3_OM_W_MASK			(0x7 << 13)
#define WT5670_G_BST3_OM_W_SFT			13
#define WT5670_G_BST2_OM_W_MASK			(0x7 << 10)
#define WT5670_G_BST2_OM_W_SFT			10
#define WT5670_G_BST1_OM_W_MASK			(0x7 << 7)
#define WT5670_G_BST1_OM_W_SFT			7
#define WT5670_G_IN_W_OM_W_MASK			(0x7 << 4)
#define WT5670_G_IN_W_OM_W_SFT			4
#define WT5670_G_WM_W_OM_W_MASK			(0x7 << 1)
#define WT5670_G_WM_W_OM_W_SFT			1

/* Output Weft Mixew Contwow 2 (0x4e) */
#define WT5670_G_DAC_W2_OM_W_MASK		(0x7 << 13)
#define WT5670_G_DAC_W2_OM_W_SFT		13
#define WT5670_G_DAC_W2_OM_W_MASK		(0x7 << 10)
#define WT5670_G_DAC_W2_OM_W_SFT		10
#define WT5670_G_DAC_W1_OM_W_MASK		(0x7 << 7)
#define WT5670_G_DAC_W1_OM_W_SFT		7

/* Output Weft Mixew Contwow 3 (0x4f) */
#define WT5670_M_BST1_OM_W			(0x1 << 5)
#define WT5670_M_BST1_OM_W_SFT			5
#define WT5670_M_IN_W_OM_W			(0x1 << 4)
#define WT5670_M_IN_W_OM_W_SFT			4
#define WT5670_M_DAC_W2_OM_W			(0x1 << 1)
#define WT5670_M_DAC_W2_OM_W_SFT		1
#define WT5670_M_DAC_W1_OM_W			(0x1)
#define WT5670_M_DAC_W1_OM_W_SFT		0

/* Output Wight Mixew Contwow 1 (0x50) */
#define WT5670_G_BST4_OM_W_MASK			(0x7 << 13)
#define WT5670_G_BST4_OM_W_SFT			13
#define WT5670_G_BST2_OM_W_MASK			(0x7 << 10)
#define WT5670_G_BST2_OM_W_SFT			10
#define WT5670_G_BST1_OM_W_MASK			(0x7 << 7)
#define WT5670_G_BST1_OM_W_SFT			7
#define WT5670_G_IN_W_OM_W_MASK			(0x7 << 4)
#define WT5670_G_IN_W_OM_W_SFT			4
#define WT5670_G_WM_W_OM_W_MASK			(0x7 << 1)
#define WT5670_G_WM_W_OM_W_SFT			1

/* Output Wight Mixew Contwow 2 (0x51) */
#define WT5670_G_DAC_W2_OM_W_MASK		(0x7 << 13)
#define WT5670_G_DAC_W2_OM_W_SFT		13
#define WT5670_G_DAC_W2_OM_W_MASK		(0x7 << 10)
#define WT5670_G_DAC_W2_OM_W_SFT		10
#define WT5670_G_DAC_W1_OM_W_MASK		(0x7 << 7)
#define WT5670_G_DAC_W1_OM_W_SFT		7

/* Output Wight Mixew Contwow 3 (0x52) */
#define WT5670_M_BST2_OM_W			(0x1 << 6)
#define WT5670_M_BST2_OM_W_SFT			6
#define WT5670_M_IN_W_OM_W			(0x1 << 4)
#define WT5670_M_IN_W_OM_W_SFT			4
#define WT5670_M_DAC_W2_OM_W			(0x1 << 1)
#define WT5670_M_DAC_W2_OM_W_SFT		1
#define WT5670_M_DAC_W1_OM_W			(0x1)
#define WT5670_M_DAC_W1_OM_W_SFT		0

/* WOUT Mixew Contwow (0x53) */
#define WT5670_M_DAC_W1_WM			(0x1 << 15)
#define WT5670_M_DAC_W1_WM_SFT			15
#define WT5670_M_DAC_W1_WM			(0x1 << 14)
#define WT5670_M_DAC_W1_WM_SFT			14
#define WT5670_M_OV_W_WM			(0x1 << 13)
#define WT5670_M_OV_W_WM_SFT			13
#define WT5670_M_OV_W_WM			(0x1 << 12)
#define WT5670_M_OV_W_WM_SFT			12
#define WT5670_G_WOUTMIX_MASK			(0x1 << 11)
#define WT5670_G_WOUTMIX_SFT			11

/* Powew Management fow Digitaw 1 (0x61) */
#define WT5670_PWW_I2S1				(0x1 << 15)
#define WT5670_PWW_I2S1_BIT			15
#define WT5670_PWW_I2S2				(0x1 << 14)
#define WT5670_PWW_I2S2_BIT			14
#define WT5670_PWW_DAC_W1			(0x1 << 12)
#define WT5670_PWW_DAC_W1_BIT			12
#define WT5670_PWW_DAC_W1			(0x1 << 11)
#define WT5670_PWW_DAC_W1_BIT			11
#define WT5670_PWW_DAC_W2			(0x1 << 7)
#define WT5670_PWW_DAC_W2_BIT			7
#define WT5670_PWW_DAC_W2			(0x1 << 6)
#define WT5670_PWW_DAC_W2_BIT			6
#define WT5670_PWW_ADC_W			(0x1 << 2)
#define WT5670_PWW_ADC_W_BIT			2
#define WT5670_PWW_ADC_W			(0x1 << 1)
#define WT5670_PWW_ADC_W_BIT			1
#define WT5670_PWW_CWS_D			(0x1)
#define WT5670_PWW_CWS_D_BIT			0

/* Powew Management fow Digitaw 2 (0x62) */
#define WT5670_PWW_ADC_S1F			(0x1 << 15)
#define WT5670_PWW_ADC_S1F_BIT			15
#define WT5670_PWW_ADC_MF_W			(0x1 << 14)
#define WT5670_PWW_ADC_MF_W_BIT			14
#define WT5670_PWW_ADC_MF_W			(0x1 << 13)
#define WT5670_PWW_ADC_MF_W_BIT			13
#define WT5670_PWW_I2S_DSP			(0x1 << 12)
#define WT5670_PWW_I2S_DSP_BIT			12
#define WT5670_PWW_DAC_S1F			(0x1 << 11)
#define WT5670_PWW_DAC_S1F_BIT			11
#define WT5670_PWW_DAC_MF_W			(0x1 << 10)
#define WT5670_PWW_DAC_MF_W_BIT			10
#define WT5670_PWW_DAC_MF_W			(0x1 << 9)
#define WT5670_PWW_DAC_MF_W_BIT			9
#define WT5670_PWW_ADC_S2F			(0x1 << 8)
#define WT5670_PWW_ADC_S2F_BIT			8
#define WT5670_PWW_PDM1				(0x1 << 7)
#define WT5670_PWW_PDM1_BIT			7
#define WT5670_PWW_PDM2				(0x1 << 6)
#define WT5670_PWW_PDM2_BIT			6

/* Powew Management fow Anawog 1 (0x63) */
#define WT5670_PWW_VWEF1			(0x1 << 15)
#define WT5670_PWW_VWEF1_BIT			15
#define WT5670_PWW_FV1				(0x1 << 14)
#define WT5670_PWW_FV1_BIT			14
#define WT5670_PWW_MB				(0x1 << 13)
#define WT5670_PWW_MB_BIT			13
#define WT5670_PWW_WM				(0x1 << 12)
#define WT5670_PWW_WM_BIT			12
#define WT5670_PWW_BG				(0x1 << 11)
#define WT5670_PWW_BG_BIT			11
#define WT5670_PWW_HP_W				(0x1 << 7)
#define WT5670_PWW_HP_W_BIT			7
#define WT5670_PWW_HP_W				(0x1 << 6)
#define WT5670_PWW_HP_W_BIT			6
#define WT5670_PWW_HA				(0x1 << 5)
#define WT5670_PWW_HA_BIT			5
#define WT5670_PWW_VWEF2			(0x1 << 4)
#define WT5670_PWW_VWEF2_BIT			4
#define WT5670_PWW_FV2				(0x1 << 3)
#define WT5670_PWW_FV2_BIT			3
#define WT5670_WDO_SEW_MASK			(0x7)
#define WT5670_WDO_SEW_SFT			0

/* Powew Management fow Anawog 2 (0x64) */
#define WT5670_PWW_BST1				(0x1 << 15)
#define WT5670_PWW_BST1_BIT			15
#define WT5670_PWW_BST2				(0x1 << 13)
#define WT5670_PWW_BST2_BIT			13
#define WT5670_PWW_MB1				(0x1 << 11)
#define WT5670_PWW_MB1_BIT			11
#define WT5670_PWW_MB2				(0x1 << 10)
#define WT5670_PWW_MB2_BIT			10
#define WT5670_PWW_PWW				(0x1 << 9)
#define WT5670_PWW_PWW_BIT			9
#define WT5670_PWW_BST1_P			(0x1 << 6)
#define WT5670_PWW_BST1_P_BIT			6
#define WT5670_PWW_BST2_P			(0x1 << 4)
#define WT5670_PWW_BST2_P_BIT			4
#define WT5670_PWW_JD1				(0x1 << 2)
#define WT5670_PWW_JD1_BIT			2
#define WT5670_PWW_JD				(0x1 << 1)
#define WT5670_PWW_JD_BIT			1

/* Powew Management fow Mixew (0x65) */
#define WT5670_PWW_OM_W				(0x1 << 15)
#define WT5670_PWW_OM_W_BIT			15
#define WT5670_PWW_OM_W				(0x1 << 14)
#define WT5670_PWW_OM_W_BIT			14
#define WT5670_PWW_WM_W				(0x1 << 11)
#define WT5670_PWW_WM_W_BIT			11
#define WT5670_PWW_WM_W				(0x1 << 10)
#define WT5670_PWW_WM_W_BIT			10

/* Powew Management fow Vowume (0x66) */
#define WT5670_PWW_HV_W				(0x1 << 11)
#define WT5670_PWW_HV_W_BIT			11
#define WT5670_PWW_HV_W				(0x1 << 10)
#define WT5670_PWW_HV_W_BIT			10
#define WT5670_PWW_IN_W				(0x1 << 9)
#define WT5670_PWW_IN_W_BIT			9
#define WT5670_PWW_IN_W				(0x1 << 8)
#define WT5670_PWW_IN_W_BIT			8
#define WT5670_PWW_MIC_DET			(0x1 << 5)
#define WT5670_PWW_MIC_DET_BIT			5

/* I2S1/2/3 Audio Sewiaw Data Powt Contwow (0x70 0x71 0x72) */
#define WT5670_I2S_MS_MASK			(0x1 << 15)
#define WT5670_I2S_MS_SFT			15
#define WT5670_I2S_MS_M				(0x0 << 15)
#define WT5670_I2S_MS_S				(0x1 << 15)
#define WT5670_I2S_IF_MASK			(0x7 << 12)
#define WT5670_I2S_IF_SFT			12
#define WT5670_I2S_O_CP_MASK			(0x3 << 10)
#define WT5670_I2S_O_CP_SFT			10
#define WT5670_I2S_O_CP_OFF			(0x0 << 10)
#define WT5670_I2S_O_CP_U_WAW			(0x1 << 10)
#define WT5670_I2S_O_CP_A_WAW			(0x2 << 10)
#define WT5670_I2S_I_CP_MASK			(0x3 << 8)
#define WT5670_I2S_I_CP_SFT			8
#define WT5670_I2S_I_CP_OFF			(0x0 << 8)
#define WT5670_I2S_I_CP_U_WAW			(0x1 << 8)
#define WT5670_I2S_I_CP_A_WAW			(0x2 << 8)
#define WT5670_I2S_BP_MASK			(0x1 << 7)
#define WT5670_I2S_BP_SFT			7
#define WT5670_I2S_BP_NOW			(0x0 << 7)
#define WT5670_I2S_BP_INV			(0x1 << 7)
#define WT5670_I2S_DW_MASK			(0x3 << 2)
#define WT5670_I2S_DW_SFT			2
#define WT5670_I2S_DW_16			(0x0 << 2)
#define WT5670_I2S_DW_20			(0x1 << 2)
#define WT5670_I2S_DW_24			(0x2 << 2)
#define WT5670_I2S_DW_8				(0x3 << 2)
#define WT5670_I2S_DF_MASK			(0x3)
#define WT5670_I2S_DF_SFT			0
#define WT5670_I2S_DF_I2S			(0x0)
#define WT5670_I2S_DF_WEFT			(0x1)
#define WT5670_I2S_DF_PCM_A			(0x2)
#define WT5670_I2S_DF_PCM_B			(0x3)

/* I2S2 Audio Sewiaw Data Powt Contwow (0x71) */
#define WT5670_I2S2_SDI_MASK			(0x1 << 6)
#define WT5670_I2S2_SDI_SFT			6
#define WT5670_I2S2_SDI_I2S1			(0x0 << 6)
#define WT5670_I2S2_SDI_I2S2			(0x1 << 6)

/* ADC/DAC Cwock Contwow 1 (0x73) */
#define WT5670_I2S_BCWK_MS1_MASK		(0x1 << 15)
#define WT5670_I2S_BCWK_MS1_SFT			15
#define WT5670_I2S_BCWK_MS1_32			(0x0 << 15)
#define WT5670_I2S_BCWK_MS1_64			(0x1 << 15)
#define WT5670_I2S_PD1_MASK			(0x7 << 12)
#define WT5670_I2S_PD1_SFT			12
#define WT5670_I2S_PD1_1			(0x0 << 12)
#define WT5670_I2S_PD1_2			(0x1 << 12)
#define WT5670_I2S_PD1_3			(0x2 << 12)
#define WT5670_I2S_PD1_4			(0x3 << 12)
#define WT5670_I2S_PD1_6			(0x4 << 12)
#define WT5670_I2S_PD1_8			(0x5 << 12)
#define WT5670_I2S_PD1_12			(0x6 << 12)
#define WT5670_I2S_PD1_16			(0x7 << 12)
#define WT5670_I2S_BCWK_MS2_MASK		(0x1 << 11)
#define WT5670_I2S_BCWK_MS2_SFT			11
#define WT5670_I2S_BCWK_MS2_32			(0x0 << 11)
#define WT5670_I2S_BCWK_MS2_64			(0x1 << 11)
#define WT5670_I2S_PD2_MASK			(0x7 << 8)
#define WT5670_I2S_PD2_SFT			8
#define WT5670_I2S_PD2_1			(0x0 << 8)
#define WT5670_I2S_PD2_2			(0x1 << 8)
#define WT5670_I2S_PD2_3			(0x2 << 8)
#define WT5670_I2S_PD2_4			(0x3 << 8)
#define WT5670_I2S_PD2_6			(0x4 << 8)
#define WT5670_I2S_PD2_8			(0x5 << 8)
#define WT5670_I2S_PD2_12			(0x6 << 8)
#define WT5670_I2S_PD2_16			(0x7 << 8)
#define WT5670_I2S_BCWK_MS3_MASK		(0x1 << 7)
#define WT5670_I2S_BCWK_MS3_SFT			7
#define WT5670_I2S_BCWK_MS3_32			(0x0 << 7)
#define WT5670_I2S_BCWK_MS3_64			(0x1 << 7)
#define WT5670_I2S_PD3_MASK			(0x7 << 4)
#define WT5670_I2S_PD3_SFT			4
#define WT5670_I2S_PD3_1			(0x0 << 4)
#define WT5670_I2S_PD3_2			(0x1 << 4)
#define WT5670_I2S_PD3_3			(0x2 << 4)
#define WT5670_I2S_PD3_4			(0x3 << 4)
#define WT5670_I2S_PD3_6			(0x4 << 4)
#define WT5670_I2S_PD3_8			(0x5 << 4)
#define WT5670_I2S_PD3_12			(0x6 << 4)
#define WT5670_I2S_PD3_16			(0x7 << 4)
#define WT5670_DAC_OSW_MASK			(0x3 << 2)
#define WT5670_DAC_OSW_SFT			2
#define WT5670_DAC_OSW_128			(0x0 << 2)
#define WT5670_DAC_OSW_64			(0x1 << 2)
#define WT5670_DAC_OSW_32			(0x2 << 2)
#define WT5670_DAC_OSW_16			(0x3 << 2)
#define WT5670_ADC_OSW_MASK			(0x3)
#define WT5670_ADC_OSW_SFT			0
#define WT5670_ADC_OSW_128			(0x0)
#define WT5670_ADC_OSW_64			(0x1)
#define WT5670_ADC_OSW_32			(0x2)
#define WT5670_ADC_OSW_16			(0x3)

/* ADC/DAC Cwock Contwow 2 (0x74) */
#define WT5670_DAC_W_OSW_MASK			(0x3 << 14)
#define WT5670_DAC_W_OSW_SFT			14
#define WT5670_DAC_W_OSW_128			(0x0 << 14)
#define WT5670_DAC_W_OSW_64			(0x1 << 14)
#define WT5670_DAC_W_OSW_32			(0x2 << 14)
#define WT5670_DAC_W_OSW_16			(0x3 << 14)
#define WT5670_ADC_W_OSW_MASK			(0x3 << 12)
#define WT5670_ADC_W_OSW_SFT			12
#define WT5670_ADC_W_OSW_128			(0x0 << 12)
#define WT5670_ADC_W_OSW_64			(0x1 << 12)
#define WT5670_ADC_W_OSW_32			(0x2 << 12)
#define WT5670_ADC_W_OSW_16			(0x3 << 12)
#define WT5670_DAHPF_EN				(0x1 << 11)
#define WT5670_DAHPF_EN_SFT			11
#define WT5670_ADHPF_EN				(0x1 << 10)
#define WT5670_ADHPF_EN_SFT			10

/* Digitaw Micwophone Contwow (0x75) */
#define WT5670_DMIC_1_EN_MASK			(0x1 << 15)
#define WT5670_DMIC_1_EN_SFT			15
#define WT5670_DMIC_1_DIS			(0x0 << 15)
#define WT5670_DMIC_1_EN			(0x1 << 15)
#define WT5670_DMIC_2_EN_MASK			(0x1 << 14)
#define WT5670_DMIC_2_EN_SFT			14
#define WT5670_DMIC_2_DIS			(0x0 << 14)
#define WT5670_DMIC_2_EN			(0x1 << 14)
#define WT5670_DMIC_1W_WH_MASK			(0x1 << 13)
#define WT5670_DMIC_1W_WH_SFT			13
#define WT5670_DMIC_1W_WH_FAWWING		(0x0 << 13)
#define WT5670_DMIC_1W_WH_WISING		(0x1 << 13)
#define WT5670_DMIC_1W_WH_MASK			(0x1 << 12)
#define WT5670_DMIC_1W_WH_SFT			12
#define WT5670_DMIC_1W_WH_FAWWING		(0x0 << 12)
#define WT5670_DMIC_1W_WH_WISING		(0x1 << 12)
#define WT5670_DMIC_2_DP_MASK			(0x1 << 10)
#define WT5670_DMIC_2_DP_SFT			10
#define WT5670_DMIC_2_DP_GPIO8			(0x0 << 10)
#define WT5670_DMIC_2_DP_IN3N			(0x1 << 10)
#define WT5670_DMIC_2W_WH_MASK			(0x1 << 9)
#define WT5670_DMIC_2W_WH_SFT			9
#define WT5670_DMIC_2W_WH_FAWWING		(0x0 << 9)
#define WT5670_DMIC_2W_WH_WISING		(0x1 << 9)
#define WT5670_DMIC_2W_WH_MASK			(0x1 << 8)
#define WT5670_DMIC_2W_WH_SFT			8
#define WT5670_DMIC_2W_WH_FAWWING		(0x0 << 8)
#define WT5670_DMIC_2W_WH_WISING		(0x1 << 8)
#define WT5670_DMIC_CWK_MASK			(0x7 << 5)
#define WT5670_DMIC_CWK_SFT			5
#define WT5670_DMIC_3_EN_MASK			(0x1 << 4)
#define WT5670_DMIC_3_EN_SFT			4
#define WT5670_DMIC_3_DIS			(0x0 << 4)
#define WT5670_DMIC_3_EN			(0x1 << 4)
#define WT5670_DMIC_1_DP_MASK			(0x3 << 0)
#define WT5670_DMIC_1_DP_SFT			0
#define WT5670_DMIC_1_DP_GPIO6			(0x0 << 0)
#define WT5670_DMIC_1_DP_IN2P			(0x1 << 0)
#define WT5670_DMIC_1_DP_GPIO7			(0x2 << 0)

/* Digitaw Micwophone Contwow2 (0x76) */
#define WT5670_DMIC_3_DP_MASK			(0x3 << 6)
#define WT5670_DMIC_3_DP_SFT			6
#define WT5670_DMIC_3_DP_GPIO9			(0x0 << 6)
#define WT5670_DMIC_3_DP_GPIO10			(0x1 << 6)
#define WT5670_DMIC_3_DP_GPIO5			(0x2 << 6)

/* Gwobaw Cwock Contwow (0x80) */
#define WT5670_SCWK_SWC_MASK			(0x3 << 14)
#define WT5670_SCWK_SWC_SFT			14
#define WT5670_SCWK_SWC_MCWK			(0x0 << 14)
#define WT5670_SCWK_SWC_PWW1			(0x1 << 14)
#define WT5670_SCWK_SWC_WCCWK			(0x2 << 14) /* 15MHz */
#define WT5670_PWW1_SWC_MASK			(0x7 << 11)
#define WT5670_PWW1_SWC_SFT			11
#define WT5670_PWW1_SWC_MCWK			(0x0 << 11)
#define WT5670_PWW1_SWC_BCWK1			(0x1 << 11)
#define WT5670_PWW1_SWC_BCWK2			(0x2 << 11)
#define WT5670_PWW1_SWC_BCWK3			(0x3 << 11)
#define WT5670_PWW1_PD_MASK			(0x1 << 3)
#define WT5670_PWW1_PD_SFT			3
#define WT5670_PWW1_PD_1			(0x0 << 3)
#define WT5670_PWW1_PD_2			(0x1 << 3)

#define WT5670_PWW_INP_MAX			40000000
#define WT5670_PWW_INP_MIN			256000
/* PWW M/N/K Code Contwow 1 (0x81) */
#define WT5670_PWW_N_MAX			0x1ff
#define WT5670_PWW_N_MASK			(WT5670_PWW_N_MAX << 7)
#define WT5670_PWW_N_SFT			7
#define WT5670_PWW_K_MAX			0x1f
#define WT5670_PWW_K_MASK			(WT5670_PWW_K_MAX)
#define WT5670_PWW_K_SFT			0

/* PWW M/N/K Code Contwow 2 (0x82) */
#define WT5670_PWW_M_MAX			0xf
#define WT5670_PWW_M_MASK			(WT5670_PWW_M_MAX << 12)
#define WT5670_PWW_M_SFT			12
#define WT5670_PWW_M_BP				(0x1 << 11)
#define WT5670_PWW_M_BP_SFT			11

/* ASWC Contwow 1 (0x83) */
#define WT5670_STO_T_MASK			(0x1 << 15)
#define WT5670_STO_T_SFT			15
#define WT5670_STO_T_SCWK			(0x0 << 15)
#define WT5670_STO_T_WWCK1			(0x1 << 15)
#define WT5670_M1_T_MASK			(0x1 << 14)
#define WT5670_M1_T_SFT				14
#define WT5670_M1_T_I2S2			(0x0 << 14)
#define WT5670_M1_T_I2S2_D3			(0x1 << 14)
#define WT5670_I2S2_F_MASK			(0x1 << 12)
#define WT5670_I2S2_F_SFT			12
#define WT5670_I2S2_F_I2S2_D2			(0x0 << 12)
#define WT5670_I2S2_F_I2S1_TCWK			(0x1 << 12)
#define WT5670_DMIC_1_M_MASK			(0x1 << 9)
#define WT5670_DMIC_1_M_SFT			9
#define WT5670_DMIC_1_M_NOW			(0x0 << 9)
#define WT5670_DMIC_1_M_ASYN			(0x1 << 9)
#define WT5670_DMIC_2_M_MASK			(0x1 << 8)
#define WT5670_DMIC_2_M_SFT			8
#define WT5670_DMIC_2_M_NOW			(0x0 << 8)
#define WT5670_DMIC_2_M_ASYN			(0x1 << 8)

/* ASWC cwock souwce sewection (0x84, 0x85) */
#define WT5670_CWK_SEW_SYS			(0x0)
#define WT5670_CWK_SEW_I2S1_ASWC		(0x1)
#define WT5670_CWK_SEW_I2S2_ASWC		(0x2)
#define WT5670_CWK_SEW_I2S3_ASWC		(0x3)
#define WT5670_CWK_SEW_SYS2			(0x5)
#define WT5670_CWK_SEW_SYS3			(0x6)

/* ASWC Contwow 2 (0x84) */
#define WT5670_DA_STO_CWK_SEW_MASK		(0xf << 12)
#define WT5670_DA_STO_CWK_SEW_SFT		12
#define WT5670_DA_MONOW_CWK_SEW_MASK		(0xf << 8)
#define WT5670_DA_MONOW_CWK_SEW_SFT		8
#define WT5670_DA_MONOW_CWK_SEW_MASK		(0xf << 4)
#define WT5670_DA_MONOW_CWK_SEW_SFT		4
#define WT5670_AD_STO1_CWK_SEW_MASK		(0xf << 0)
#define WT5670_AD_STO1_CWK_SEW_SFT		0

/* ASWC Contwow 3 (0x85) */
#define WT5670_UP_CWK_SEW_MASK			(0xf << 12)
#define WT5670_UP_CWK_SEW_SFT			12
#define WT5670_DOWN_CWK_SEW_MASK		(0xf << 8)
#define WT5670_DOWN_CWK_SEW_SFT			8
#define WT5670_AD_MONOW_CWK_SEW_MASK		(0xf << 4)
#define WT5670_AD_MONOW_CWK_SEW_SFT		4
#define WT5670_AD_MONOW_CWK_SEW_MASK		(0xf << 0)
#define WT5670_AD_MONOW_CWK_SEW_SFT		0

/* ASWC Contwow 4 (0x89) */
#define WT5670_I2S1_PD_MASK			(0x7 << 12)
#define WT5670_I2S1_PD_SFT			12
#define WT5670_I2S2_PD_MASK			(0x7 << 8)
#define WT5670_I2S2_PD_SFT			8

/* HPOUT Ovew Cuwwent Detection (0x8b) */
#define WT5670_HP_OVCD_MASK			(0x1 << 10)
#define WT5670_HP_OVCD_SFT			10
#define WT5670_HP_OVCD_DIS			(0x0 << 10)
#define WT5670_HP_OVCD_EN			(0x1 << 10)
#define WT5670_HP_OC_TH_MASK			(0x3 << 8)
#define WT5670_HP_OC_TH_SFT			8
#define WT5670_HP_OC_TH_90			(0x0 << 8)
#define WT5670_HP_OC_TH_105			(0x1 << 8)
#define WT5670_HP_OC_TH_120			(0x2 << 8)
#define WT5670_HP_OC_TH_135			(0x3 << 8)

/* Cwass D Ovew Cuwwent Contwow (0x8c) */
#define WT5670_CWSD_OC_MASK			(0x1 << 9)
#define WT5670_CWSD_OC_SFT			9
#define WT5670_CWSD_OC_PU			(0x0 << 9)
#define WT5670_CWSD_OC_PD			(0x1 << 9)
#define WT5670_AUTO_PD_MASK			(0x1 << 8)
#define WT5670_AUTO_PD_SFT			8
#define WT5670_AUTO_PD_DIS			(0x0 << 8)
#define WT5670_AUTO_PD_EN			(0x1 << 8)
#define WT5670_CWSD_OC_TH_MASK			(0x3f)
#define WT5670_CWSD_OC_TH_SFT			0

/* Cwass D Output Contwow (0x8d) */
#define WT5670_CWSD_WATIO_MASK			(0xf << 12)
#define WT5670_CWSD_WATIO_SFT			12
#define WT5670_CWSD_OM_MASK			(0x1 << 11)
#define WT5670_CWSD_OM_SFT			11
#define WT5670_CWSD_OM_MONO			(0x0 << 11)
#define WT5670_CWSD_OM_STO			(0x1 << 11)
#define WT5670_CWSD_SCH_MASK			(0x1 << 10)
#define WT5670_CWSD_SCH_SFT			10
#define WT5670_CWSD_SCH_W			(0x0 << 10)
#define WT5670_CWSD_SCH_S			(0x1 << 10)

/* Depop Mode Contwow 1 (0x8e) */
#define WT5670_SMT_TWIG_MASK			(0x1 << 15)
#define WT5670_SMT_TWIG_SFT			15
#define WT5670_SMT_TWIG_DIS			(0x0 << 15)
#define WT5670_SMT_TWIG_EN			(0x1 << 15)
#define WT5670_HP_W_SMT_MASK			(0x1 << 9)
#define WT5670_HP_W_SMT_SFT			9
#define WT5670_HP_W_SMT_DIS			(0x0 << 9)
#define WT5670_HP_W_SMT_EN			(0x1 << 9)
#define WT5670_HP_W_SMT_MASK			(0x1 << 8)
#define WT5670_HP_W_SMT_SFT			8
#define WT5670_HP_W_SMT_DIS			(0x0 << 8)
#define WT5670_HP_W_SMT_EN			(0x1 << 8)
#define WT5670_HP_CD_PD_MASK			(0x1 << 7)
#define WT5670_HP_CD_PD_SFT			7
#define WT5670_HP_CD_PD_DIS			(0x0 << 7)
#define WT5670_HP_CD_PD_EN			(0x1 << 7)
#define WT5670_WSTN_MASK			(0x1 << 6)
#define WT5670_WSTN_SFT				6
#define WT5670_WSTN_DIS				(0x0 << 6)
#define WT5670_WSTN_EN				(0x1 << 6)
#define WT5670_WSTP_MASK			(0x1 << 5)
#define WT5670_WSTP_SFT				5
#define WT5670_WSTP_DIS				(0x0 << 5)
#define WT5670_WSTP_EN				(0x1 << 5)
#define WT5670_HP_CO_MASK			(0x1 << 4)
#define WT5670_HP_CO_SFT			4
#define WT5670_HP_CO_DIS			(0x0 << 4)
#define WT5670_HP_CO_EN				(0x1 << 4)
#define WT5670_HP_CP_MASK			(0x1 << 3)
#define WT5670_HP_CP_SFT			3
#define WT5670_HP_CP_PD				(0x0 << 3)
#define WT5670_HP_CP_PU				(0x1 << 3)
#define WT5670_HP_SG_MASK			(0x1 << 2)
#define WT5670_HP_SG_SFT			2
#define WT5670_HP_SG_DIS			(0x0 << 2)
#define WT5670_HP_SG_EN				(0x1 << 2)
#define WT5670_HP_DP_MASK			(0x1 << 1)
#define WT5670_HP_DP_SFT			1
#define WT5670_HP_DP_PD				(0x0 << 1)
#define WT5670_HP_DP_PU				(0x1 << 1)
#define WT5670_HP_CB_MASK			(0x1)
#define WT5670_HP_CB_SFT			0
#define WT5670_HP_CB_PD				(0x0)
#define WT5670_HP_CB_PU				(0x1)

/* Depop Mode Contwow 2 (0x8f) */
#define WT5670_DEPOP_MASK			(0x1 << 13)
#define WT5670_DEPOP_SFT			13
#define WT5670_DEPOP_AUTO			(0x0 << 13)
#define WT5670_DEPOP_MAN			(0x1 << 13)
#define WT5670_WAMP_MASK			(0x1 << 12)
#define WT5670_WAMP_SFT				12
#define WT5670_WAMP_DIS				(0x0 << 12)
#define WT5670_WAMP_EN				(0x1 << 12)
#define WT5670_BPS_MASK				(0x1 << 11)
#define WT5670_BPS_SFT				11
#define WT5670_BPS_DIS				(0x0 << 11)
#define WT5670_BPS_EN				(0x1 << 11)
#define WT5670_FAST_UPDN_MASK			(0x1 << 10)
#define WT5670_FAST_UPDN_SFT			10
#define WT5670_FAST_UPDN_DIS			(0x0 << 10)
#define WT5670_FAST_UPDN_EN			(0x1 << 10)
#define WT5670_MWES_MASK			(0x3 << 8)
#define WT5670_MWES_SFT				8
#define WT5670_MWES_15MO			(0x0 << 8)
#define WT5670_MWES_25MO			(0x1 << 8)
#define WT5670_MWES_35MO			(0x2 << 8)
#define WT5670_MWES_45MO			(0x3 << 8)
#define WT5670_VWO_MASK				(0x1 << 7)
#define WT5670_VWO_SFT				7
#define WT5670_VWO_3V				(0x0 << 7)
#define WT5670_VWO_32V				(0x1 << 7)
#define WT5670_DIG_DP_MASK			(0x1 << 6)
#define WT5670_DIG_DP_SFT			6
#define WT5670_DIG_DP_DIS			(0x0 << 6)
#define WT5670_DIG_DP_EN			(0x1 << 6)
#define WT5670_DP_TH_MASK			(0x3 << 4)
#define WT5670_DP_TH_SFT			4

/* Depop Mode Contwow 3 (0x90) */
#define WT5670_CP_SYS_MASK			(0x7 << 12)
#define WT5670_CP_SYS_SFT			12
#define WT5670_CP_FQ1_MASK			(0x7 << 8)
#define WT5670_CP_FQ1_SFT			8
#define WT5670_CP_FQ2_MASK			(0x7 << 4)
#define WT5670_CP_FQ2_SFT			4
#define WT5670_CP_FQ3_MASK			(0x7)
#define WT5670_CP_FQ3_SFT			0
#define WT5670_CP_FQ_1_5_KHZ			0
#define WT5670_CP_FQ_3_KHZ			1
#define WT5670_CP_FQ_6_KHZ			2
#define WT5670_CP_FQ_12_KHZ			3
#define WT5670_CP_FQ_24_KHZ			4
#define WT5670_CP_FQ_48_KHZ			5
#define WT5670_CP_FQ_96_KHZ			6
#define WT5670_CP_FQ_192_KHZ			7

/* HPOUT chawge pump (0x91) */
#define WT5670_OSW_W_MASK			(0x1 << 11)
#define WT5670_OSW_W_SFT			11
#define WT5670_OSW_W_DIS			(0x0 << 11)
#define WT5670_OSW_W_EN				(0x1 << 11)
#define WT5670_OSW_W_MASK			(0x1 << 10)
#define WT5670_OSW_W_SFT			10
#define WT5670_OSW_W_DIS			(0x0 << 10)
#define WT5670_OSW_W_EN				(0x1 << 10)
#define WT5670_PM_HP_MASK			(0x3 << 8)
#define WT5670_PM_HP_SFT			8
#define WT5670_PM_HP_WV				(0x0 << 8)
#define WT5670_PM_HP_MV				(0x1 << 8)
#define WT5670_PM_HP_HV				(0x2 << 8)
#define WT5670_IB_HP_MASK			(0x3 << 6)
#define WT5670_IB_HP_SFT			6
#define WT5670_IB_HP_125IW			(0x0 << 6)
#define WT5670_IB_HP_25IW			(0x1 << 6)
#define WT5670_IB_HP_5IW			(0x2 << 6)
#define WT5670_IB_HP_1IW			(0x3 << 6)

/* PV detection and SPK gain contwow (0x92) */
#define WT5670_PVDD_DET_MASK			(0x1 << 15)
#define WT5670_PVDD_DET_SFT			15
#define WT5670_PVDD_DET_DIS			(0x0 << 15)
#define WT5670_PVDD_DET_EN			(0x1 << 15)
#define WT5670_SPK_AG_MASK			(0x1 << 14)
#define WT5670_SPK_AG_SFT			14
#define WT5670_SPK_AG_DIS			(0x0 << 14)
#define WT5670_SPK_AG_EN			(0x1 << 14)

/* Micbias Contwow (0x93) */
#define WT5670_MIC1_BS_MASK			(0x1 << 15)
#define WT5670_MIC1_BS_SFT			15
#define WT5670_MIC1_BS_9AV			(0x0 << 15)
#define WT5670_MIC1_BS_75AV			(0x1 << 15)
#define WT5670_MIC2_BS_MASK			(0x1 << 14)
#define WT5670_MIC2_BS_SFT			14
#define WT5670_MIC2_BS_9AV			(0x0 << 14)
#define WT5670_MIC2_BS_75AV			(0x1 << 14)
#define WT5670_MIC1_CWK_MASK			(0x1 << 13)
#define WT5670_MIC1_CWK_SFT			13
#define WT5670_MIC1_CWK_DIS			(0x0 << 13)
#define WT5670_MIC1_CWK_EN			(0x1 << 13)
#define WT5670_MIC2_CWK_MASK			(0x1 << 12)
#define WT5670_MIC2_CWK_SFT			12
#define WT5670_MIC2_CWK_DIS			(0x0 << 12)
#define WT5670_MIC2_CWK_EN			(0x1 << 12)
#define WT5670_MIC1_OVCD_MASK			(0x1 << 11)
#define WT5670_MIC1_OVCD_SFT			11
#define WT5670_MIC1_OVCD_DIS			(0x0 << 11)
#define WT5670_MIC1_OVCD_EN			(0x1 << 11)
#define WT5670_MIC1_OVTH_MASK			(0x3 << 9)
#define WT5670_MIC1_OVTH_SFT			9
#define WT5670_MIC1_OVTH_600UA			(0x0 << 9)
#define WT5670_MIC1_OVTH_1500UA			(0x1 << 9)
#define WT5670_MIC1_OVTH_2000UA			(0x2 << 9)
#define WT5670_MIC2_OVCD_MASK			(0x1 << 8)
#define WT5670_MIC2_OVCD_SFT			8
#define WT5670_MIC2_OVCD_DIS			(0x0 << 8)
#define WT5670_MIC2_OVCD_EN			(0x1 << 8)
#define WT5670_MIC2_OVTH_MASK			(0x3 << 6)
#define WT5670_MIC2_OVTH_SFT			6
#define WT5670_MIC2_OVTH_600UA			(0x0 << 6)
#define WT5670_MIC2_OVTH_1500UA			(0x1 << 6)
#define WT5670_MIC2_OVTH_2000UA			(0x2 << 6)
#define WT5670_PWW_MB_MASK			(0x1 << 5)
#define WT5670_PWW_MB_SFT			5
#define WT5670_PWW_MB_PD			(0x0 << 5)
#define WT5670_PWW_MB_PU			(0x1 << 5)
#define WT5670_PWW_CWK25M_MASK			(0x1 << 4)
#define WT5670_PWW_CWK25M_SFT			4
#define WT5670_PWW_CWK25M_PD			(0x0 << 4)
#define WT5670_PWW_CWK25M_PU			(0x1 << 4)

/* Anawog JD Contwow 1 (0x94) */
#define WT5670_JD1_MODE_MASK			(0x3 << 0)
#define WT5670_JD1_MODE_0			(0x0 << 0)
#define WT5670_JD1_MODE_1			(0x1 << 0)
#define WT5670_JD1_MODE_2			(0x2 << 0)

/* VAD Contwow 4 (0x9d) */
#define WT5670_VAD_SEW_MASK			(0x3 << 8)
#define WT5670_VAD_SEW_SFT			8

/* EQ Contwow 1 (0xb0) */
#define WT5670_EQ_SWC_MASK			(0x1 << 15)
#define WT5670_EQ_SWC_SFT			15
#define WT5670_EQ_SWC_DAC			(0x0 << 15)
#define WT5670_EQ_SWC_ADC			(0x1 << 15)
#define WT5670_EQ_UPD				(0x1 << 14)
#define WT5670_EQ_UPD_BIT			14
#define WT5670_EQ_CD_MASK			(0x1 << 13)
#define WT5670_EQ_CD_SFT			13
#define WT5670_EQ_CD_DIS			(0x0 << 13)
#define WT5670_EQ_CD_EN				(0x1 << 13)
#define WT5670_EQ_DITH_MASK			(0x3 << 8)
#define WT5670_EQ_DITH_SFT			8
#define WT5670_EQ_DITH_NOW			(0x0 << 8)
#define WT5670_EQ_DITH_WSB			(0x1 << 8)
#define WT5670_EQ_DITH_WSB_1			(0x2 << 8)
#define WT5670_EQ_DITH_WSB_2			(0x3 << 8)

/* EQ Contwow 2 (0xb1) */
#define WT5670_EQ_HPF1_M_MASK			(0x1 << 8)
#define WT5670_EQ_HPF1_M_SFT			8
#define WT5670_EQ_HPF1_M_HI			(0x0 << 8)
#define WT5670_EQ_HPF1_M_1ST			(0x1 << 8)
#define WT5670_EQ_WPF1_M_MASK			(0x1 << 7)
#define WT5670_EQ_WPF1_M_SFT			7
#define WT5670_EQ_WPF1_M_WO			(0x0 << 7)
#define WT5670_EQ_WPF1_M_1ST			(0x1 << 7)
#define WT5670_EQ_HPF2_MASK			(0x1 << 6)
#define WT5670_EQ_HPF2_SFT			6
#define WT5670_EQ_HPF2_DIS			(0x0 << 6)
#define WT5670_EQ_HPF2_EN			(0x1 << 6)
#define WT5670_EQ_HPF1_MASK			(0x1 << 5)
#define WT5670_EQ_HPF1_SFT			5
#define WT5670_EQ_HPF1_DIS			(0x0 << 5)
#define WT5670_EQ_HPF1_EN			(0x1 << 5)
#define WT5670_EQ_BPF4_MASK			(0x1 << 4)
#define WT5670_EQ_BPF4_SFT			4
#define WT5670_EQ_BPF4_DIS			(0x0 << 4)
#define WT5670_EQ_BPF4_EN			(0x1 << 4)
#define WT5670_EQ_BPF3_MASK			(0x1 << 3)
#define WT5670_EQ_BPF3_SFT			3
#define WT5670_EQ_BPF3_DIS			(0x0 << 3)
#define WT5670_EQ_BPF3_EN			(0x1 << 3)
#define WT5670_EQ_BPF2_MASK			(0x1 << 2)
#define WT5670_EQ_BPF2_SFT			2
#define WT5670_EQ_BPF2_DIS			(0x0 << 2)
#define WT5670_EQ_BPF2_EN			(0x1 << 2)
#define WT5670_EQ_BPF1_MASK			(0x1 << 1)
#define WT5670_EQ_BPF1_SFT			1
#define WT5670_EQ_BPF1_DIS			(0x0 << 1)
#define WT5670_EQ_BPF1_EN			(0x1 << 1)
#define WT5670_EQ_WPF_MASK			(0x1)
#define WT5670_EQ_WPF_SFT			0
#define WT5670_EQ_WPF_DIS			(0x0)
#define WT5670_EQ_WPF_EN			(0x1)
#define WT5670_EQ_CTWW_MASK			(0x7f)

/* Memowy Test (0xb2) */
#define WT5670_MT_MASK				(0x1 << 15)
#define WT5670_MT_SFT				15
#define WT5670_MT_DIS				(0x0 << 15)
#define WT5670_MT_EN				(0x1 << 15)

/* DWC/AGC Contwow 1 (0xb4) */
#define WT5670_DWC_AGC_P_MASK			(0x1 << 15)
#define WT5670_DWC_AGC_P_SFT			15
#define WT5670_DWC_AGC_P_DAC			(0x0 << 15)
#define WT5670_DWC_AGC_P_ADC			(0x1 << 15)
#define WT5670_DWC_AGC_MASK			(0x1 << 14)
#define WT5670_DWC_AGC_SFT			14
#define WT5670_DWC_AGC_DIS			(0x0 << 14)
#define WT5670_DWC_AGC_EN			(0x1 << 14)
#define WT5670_DWC_AGC_UPD			(0x1 << 13)
#define WT5670_DWC_AGC_UPD_BIT			13
#define WT5670_DWC_AGC_AW_MASK			(0x1f << 8)
#define WT5670_DWC_AGC_AW_SFT			8
#define WT5670_DWC_AGC_W_MASK			(0x7 << 5)
#define WT5670_DWC_AGC_W_SFT			5
#define WT5670_DWC_AGC_W_48K			(0x1 << 5)
#define WT5670_DWC_AGC_W_96K			(0x2 << 5)
#define WT5670_DWC_AGC_W_192K			(0x3 << 5)
#define WT5670_DWC_AGC_W_441K			(0x5 << 5)
#define WT5670_DWC_AGC_W_882K			(0x6 << 5)
#define WT5670_DWC_AGC_W_1764K			(0x7 << 5)
#define WT5670_DWC_AGC_WC_MASK			(0x1f)
#define WT5670_DWC_AGC_WC_SFT			0

/* DWC/AGC Contwow 2 (0xb5) */
#define WT5670_DWC_AGC_POB_MASK			(0x3f << 8)
#define WT5670_DWC_AGC_POB_SFT			8
#define WT5670_DWC_AGC_CP_MASK			(0x1 << 7)
#define WT5670_DWC_AGC_CP_SFT			7
#define WT5670_DWC_AGC_CP_DIS			(0x0 << 7)
#define WT5670_DWC_AGC_CP_EN			(0x1 << 7)
#define WT5670_DWC_AGC_CPW_MASK			(0x3 << 5)
#define WT5670_DWC_AGC_CPW_SFT			5
#define WT5670_DWC_AGC_CPW_1_1			(0x0 << 5)
#define WT5670_DWC_AGC_CPW_1_2			(0x1 << 5)
#define WT5670_DWC_AGC_CPW_1_3			(0x2 << 5)
#define WT5670_DWC_AGC_CPW_1_4			(0x3 << 5)
#define WT5670_DWC_AGC_PWB_MASK			(0x1f)
#define WT5670_DWC_AGC_PWB_SFT			0

/* DWC/AGC Contwow 3 (0xb6) */
#define WT5670_DWC_AGC_NGB_MASK			(0xf << 12)
#define WT5670_DWC_AGC_NGB_SFT			12
#define WT5670_DWC_AGC_TAW_MASK			(0x1f << 7)
#define WT5670_DWC_AGC_TAW_SFT			7
#define WT5670_DWC_AGC_NG_MASK			(0x1 << 6)
#define WT5670_DWC_AGC_NG_SFT			6
#define WT5670_DWC_AGC_NG_DIS			(0x0 << 6)
#define WT5670_DWC_AGC_NG_EN			(0x1 << 6)
#define WT5670_DWC_AGC_NGH_MASK			(0x1 << 5)
#define WT5670_DWC_AGC_NGH_SFT			5
#define WT5670_DWC_AGC_NGH_DIS			(0x0 << 5)
#define WT5670_DWC_AGC_NGH_EN			(0x1 << 5)
#define WT5670_DWC_AGC_NGT_MASK			(0x1f)
#define WT5670_DWC_AGC_NGT_SFT			0

/* Jack Detect Contwow (0xbb) */
#define WT5670_JD_MASK				(0x7 << 13)
#define WT5670_JD_SFT				13
#define WT5670_JD_DIS				(0x0 << 13)
#define WT5670_JD_GPIO1				(0x1 << 13)
#define WT5670_JD_JD1_IN4P			(0x2 << 13)
#define WT5670_JD_JD2_IN4N			(0x3 << 13)
#define WT5670_JD_GPIO2				(0x4 << 13)
#define WT5670_JD_GPIO3				(0x5 << 13)
#define WT5670_JD_GPIO4				(0x6 << 13)
#define WT5670_JD_HP_MASK			(0x1 << 11)
#define WT5670_JD_HP_SFT			11
#define WT5670_JD_HP_DIS			(0x0 << 11)
#define WT5670_JD_HP_EN				(0x1 << 11)
#define WT5670_JD_HP_TWG_MASK			(0x1 << 10)
#define WT5670_JD_HP_TWG_SFT			10
#define WT5670_JD_HP_TWG_WO			(0x0 << 10)
#define WT5670_JD_HP_TWG_HI			(0x1 << 10)
#define WT5670_JD_SPW_MASK			(0x1 << 9)
#define WT5670_JD_SPW_SFT			9
#define WT5670_JD_SPW_DIS			(0x0 << 9)
#define WT5670_JD_SPW_EN			(0x1 << 9)
#define WT5670_JD_SPW_TWG_MASK			(0x1 << 8)
#define WT5670_JD_SPW_TWG_SFT			8
#define WT5670_JD_SPW_TWG_WO			(0x0 << 8)
#define WT5670_JD_SPW_TWG_HI			(0x1 << 8)
#define WT5670_JD_SPW_MASK			(0x1 << 7)
#define WT5670_JD_SPW_SFT			7
#define WT5670_JD_SPW_DIS			(0x0 << 7)
#define WT5670_JD_SPW_EN			(0x1 << 7)
#define WT5670_JD_SPW_TWG_MASK			(0x1 << 6)
#define WT5670_JD_SPW_TWG_SFT			6
#define WT5670_JD_SPW_TWG_WO			(0x0 << 6)
#define WT5670_JD_SPW_TWG_HI			(0x1 << 6)
#define WT5670_JD_MO_MASK			(0x1 << 5)
#define WT5670_JD_MO_SFT			5
#define WT5670_JD_MO_DIS			(0x0 << 5)
#define WT5670_JD_MO_EN				(0x1 << 5)
#define WT5670_JD_MO_TWG_MASK			(0x1 << 4)
#define WT5670_JD_MO_TWG_SFT			4
#define WT5670_JD_MO_TWG_WO			(0x0 << 4)
#define WT5670_JD_MO_TWG_HI			(0x1 << 4)
#define WT5670_JD_WO_MASK			(0x1 << 3)
#define WT5670_JD_WO_SFT			3
#define WT5670_JD_WO_DIS			(0x0 << 3)
#define WT5670_JD_WO_EN				(0x1 << 3)
#define WT5670_JD_WO_TWG_MASK			(0x1 << 2)
#define WT5670_JD_WO_TWG_SFT			2
#define WT5670_JD_WO_TWG_WO			(0x0 << 2)
#define WT5670_JD_WO_TWG_HI			(0x1 << 2)
#define WT5670_JD1_IN4P_MASK			(0x1 << 1)
#define WT5670_JD1_IN4P_SFT			1
#define WT5670_JD1_IN4P_DIS			(0x0 << 1)
#define WT5670_JD1_IN4P_EN			(0x1 << 1)
#define WT5670_JD2_IN4N_MASK			(0x1)
#define WT5670_JD2_IN4N_SFT			0
#define WT5670_JD2_IN4N_DIS			(0x0)
#define WT5670_JD2_IN4N_EN			(0x1)

/* IWQ Contwow 1 (0xbd) */
#define WT5670_IWQ_JD_MASK			(0x1 << 15)
#define WT5670_IWQ_JD_SFT			15
#define WT5670_IWQ_JD_BP			(0x0 << 15)
#define WT5670_IWQ_JD_NOW			(0x1 << 15)
#define WT5670_IWQ_OT_MASK			(0x1 << 14)
#define WT5670_IWQ_OT_SFT			14
#define WT5670_IWQ_OT_BP			(0x0 << 14)
#define WT5670_IWQ_OT_NOW			(0x1 << 14)
#define WT5670_JD_STKY_MASK			(0x1 << 13)
#define WT5670_JD_STKY_SFT			13
#define WT5670_JD_STKY_DIS			(0x0 << 13)
#define WT5670_JD_STKY_EN			(0x1 << 13)
#define WT5670_OT_STKY_MASK			(0x1 << 12)
#define WT5670_OT_STKY_SFT			12
#define WT5670_OT_STKY_DIS			(0x0 << 12)
#define WT5670_OT_STKY_EN			(0x1 << 12)
#define WT5670_JD_P_MASK			(0x1 << 11)
#define WT5670_JD_P_SFT				11
#define WT5670_JD_P_NOW				(0x0 << 11)
#define WT5670_JD_P_INV				(0x1 << 11)
#define WT5670_OT_P_MASK			(0x1 << 10)
#define WT5670_OT_P_SFT				10
#define WT5670_OT_P_NOW				(0x0 << 10)
#define WT5670_OT_P_INV				(0x1 << 10)
#define WT5670_JD1_1_EN_MASK			(0x1 << 9)
#define WT5670_JD1_1_EN_SFT			9
#define WT5670_JD1_1_DIS			(0x0 << 9)
#define WT5670_JD1_1_EN				(0x1 << 9)

/* IWQ Contwow 2 (0xbe) */
#define WT5670_IWQ_MB1_OC_MASK			(0x1 << 15)
#define WT5670_IWQ_MB1_OC_SFT			15
#define WT5670_IWQ_MB1_OC_BP			(0x0 << 15)
#define WT5670_IWQ_MB1_OC_NOW			(0x1 << 15)
#define WT5670_IWQ_MB2_OC_MASK			(0x1 << 14)
#define WT5670_IWQ_MB2_OC_SFT			14
#define WT5670_IWQ_MB2_OC_BP			(0x0 << 14)
#define WT5670_IWQ_MB2_OC_NOW			(0x1 << 14)
#define WT5670_MB1_OC_STKY_MASK			(0x1 << 11)
#define WT5670_MB1_OC_STKY_SFT			11
#define WT5670_MB1_OC_STKY_DIS			(0x0 << 11)
#define WT5670_MB1_OC_STKY_EN			(0x1 << 11)
#define WT5670_MB2_OC_STKY_MASK			(0x1 << 10)
#define WT5670_MB2_OC_STKY_SFT			10
#define WT5670_MB2_OC_STKY_DIS			(0x0 << 10)
#define WT5670_MB2_OC_STKY_EN			(0x1 << 10)
#define WT5670_MB1_OC_P_MASK			(0x1 << 7)
#define WT5670_MB1_OC_P_SFT			7
#define WT5670_MB1_OC_P_NOW			(0x0 << 7)
#define WT5670_MB1_OC_P_INV			(0x1 << 7)
#define WT5670_MB2_OC_P_MASK			(0x1 << 6)
#define WT5670_MB2_OC_P_SFT			6
#define WT5670_MB2_OC_P_NOW			(0x0 << 6)
#define WT5670_MB2_OC_P_INV			(0x1 << 6)
#define WT5670_MB1_OC_CWW			(0x1 << 3)
#define WT5670_MB1_OC_CWW_SFT			3
#define WT5670_MB2_OC_CWW			(0x1 << 2)
#define WT5670_MB2_OC_CWW_SFT			2

/* GPIO Contwow 1 (0xc0) */
#define WT5670_GP1_PIN_MASK			(0x1 << 15)
#define WT5670_GP1_PIN_SFT			15
#define WT5670_GP1_PIN_GPIO1			(0x0 << 15)
#define WT5670_GP1_PIN_IWQ			(0x1 << 15)
#define WT5670_GP2_PIN_MASK			(0x1 << 14)
#define WT5670_GP2_PIN_SFT			14
#define WT5670_GP2_PIN_GPIO2			(0x0 << 14)
#define WT5670_GP2_PIN_DMIC1_SCW		(0x1 << 14)
#define WT5670_GP3_PIN_MASK			(0x3 << 12)
#define WT5670_GP3_PIN_SFT			12
#define WT5670_GP3_PIN_GPIO3			(0x0 << 12)
#define WT5670_GP3_PIN_DMIC1_SDA		(0x1 << 12)
#define WT5670_GP3_PIN_IWQ			(0x2 << 12)
#define WT5670_GP4_PIN_MASK			(0x1 << 11)
#define WT5670_GP4_PIN_SFT			11
#define WT5670_GP4_PIN_GPIO4			(0x0 << 11)
#define WT5670_GP4_PIN_DMIC2_SDA		(0x1 << 11)
#define WT5670_DP_SIG_MASK			(0x1 << 10)
#define WT5670_DP_SIG_SFT			10
#define WT5670_DP_SIG_TEST			(0x0 << 10)
#define WT5670_DP_SIG_AP			(0x1 << 10)
#define WT5670_GPIO_M_MASK			(0x1 << 9)
#define WT5670_GPIO_M_SFT			9
#define WT5670_GPIO_M_FWT			(0x0 << 9)
#define WT5670_GPIO_M_PH			(0x1 << 9)
#define WT5670_I2S2_PIN_MASK			(0x1 << 8)
#define WT5670_I2S2_PIN_SFT			8
#define WT5670_I2S2_PIN_I2S			(0x0 << 8)
#define WT5670_I2S2_PIN_GPIO			(0x1 << 8)
#define WT5670_GP5_PIN_MASK			(0x1 << 7)
#define WT5670_GP5_PIN_SFT			7
#define WT5670_GP5_PIN_GPIO5			(0x0 << 7)
#define WT5670_GP5_PIN_DMIC3_SDA		(0x1 << 7)
#define WT5670_GP6_PIN_MASK			(0x1 << 6)
#define WT5670_GP6_PIN_SFT			6
#define WT5670_GP6_PIN_GPIO6			(0x0 << 6)
#define WT5670_GP6_PIN_DMIC1_SDA		(0x1 << 6)
#define WT5670_GP7_PIN_MASK			(0x3 << 4)
#define WT5670_GP7_PIN_SFT			4
#define WT5670_GP7_PIN_GPIO7			(0x0 << 4)
#define WT5670_GP7_PIN_DMIC1_SDA		(0x1 << 4)
#define WT5670_GP7_PIN_PDM_SCW2			(0x2 << 4)
#define WT5670_GP8_PIN_MASK			(0x1 << 3)
#define WT5670_GP8_PIN_SFT			3
#define WT5670_GP8_PIN_GPIO8			(0x0 << 3)
#define WT5670_GP8_PIN_DMIC2_SDA		(0x1 << 3)
#define WT5670_GP9_PIN_MASK			(0x1 << 2)
#define WT5670_GP9_PIN_SFT			2
#define WT5670_GP9_PIN_GPIO9			(0x0 << 2)
#define WT5670_GP9_PIN_DMIC3_SDA		(0x1 << 2)
#define WT5670_GP10_PIN_MASK			(0x3)
#define WT5670_GP10_PIN_SFT			0
#define WT5670_GP10_PIN_GPIO9			(0x0)
#define WT5670_GP10_PIN_DMIC3_SDA		(0x1)
#define WT5670_GP10_PIN_PDM_ADT2		(0x2)

/* GPIO Contwow 2 (0xc1) */
#define WT5670_GP4_PF_MASK			(0x1 << 11)
#define WT5670_GP4_PF_SFT			11
#define WT5670_GP4_PF_IN			(0x0 << 11)
#define WT5670_GP4_PF_OUT			(0x1 << 11)
#define WT5670_GP4_OUT_MASK			(0x1 << 10)
#define WT5670_GP4_OUT_SFT			10
#define WT5670_GP4_OUT_WO			(0x0 << 10)
#define WT5670_GP4_OUT_HI			(0x1 << 10)
#define WT5670_GP4_P_MASK			(0x1 << 9)
#define WT5670_GP4_P_SFT			9
#define WT5670_GP4_P_NOW			(0x0 << 9)
#define WT5670_GP4_P_INV			(0x1 << 9)
#define WT5670_GP3_PF_MASK			(0x1 << 8)
#define WT5670_GP3_PF_SFT			8
#define WT5670_GP3_PF_IN			(0x0 << 8)
#define WT5670_GP3_PF_OUT			(0x1 << 8)
#define WT5670_GP3_OUT_MASK			(0x1 << 7)
#define WT5670_GP3_OUT_SFT			7
#define WT5670_GP3_OUT_WO			(0x0 << 7)
#define WT5670_GP3_OUT_HI			(0x1 << 7)
#define WT5670_GP3_P_MASK			(0x1 << 6)
#define WT5670_GP3_P_SFT			6
#define WT5670_GP3_P_NOW			(0x0 << 6)
#define WT5670_GP3_P_INV			(0x1 << 6)
#define WT5670_GP2_PF_MASK			(0x1 << 5)
#define WT5670_GP2_PF_SFT			5
#define WT5670_GP2_PF_IN			(0x0 << 5)
#define WT5670_GP2_PF_OUT			(0x1 << 5)
#define WT5670_GP2_OUT_MASK			(0x1 << 4)
#define WT5670_GP2_OUT_SFT			4
#define WT5670_GP2_OUT_WO			(0x0 << 4)
#define WT5670_GP2_OUT_HI			(0x1 << 4)
#define WT5670_GP2_P_MASK			(0x1 << 3)
#define WT5670_GP2_P_SFT			3
#define WT5670_GP2_P_NOW			(0x0 << 3)
#define WT5670_GP2_P_INV			(0x1 << 3)
#define WT5670_GP1_PF_MASK			(0x1 << 2)
#define WT5670_GP1_PF_SFT			2
#define WT5670_GP1_PF_IN			(0x0 << 2)
#define WT5670_GP1_PF_OUT			(0x1 << 2)
#define WT5670_GP1_OUT_MASK			(0x1 << 1)
#define WT5670_GP1_OUT_SFT			1
#define WT5670_GP1_OUT_WO			(0x0 << 1)
#define WT5670_GP1_OUT_HI			(0x1 << 1)
#define WT5670_GP1_P_MASK			(0x1)
#define WT5670_GP1_P_SFT			0
#define WT5670_GP1_P_NOW			(0x0)
#define WT5670_GP1_P_INV			(0x1)

/* Scwambwe Function (0xcd) */
#define WT5670_SCB_KEY_MASK			(0xff)
#define WT5670_SCB_KEY_SFT			0

/* Scwambwe Contwow (0xce) */
#define WT5670_SCB_SWAP_MASK			(0x1 << 15)
#define WT5670_SCB_SWAP_SFT			15
#define WT5670_SCB_SWAP_DIS			(0x0 << 15)
#define WT5670_SCB_SWAP_EN			(0x1 << 15)
#define WT5670_SCB_MASK				(0x1 << 14)
#define WT5670_SCB_SFT				14
#define WT5670_SCB_DIS				(0x0 << 14)
#define WT5670_SCB_EN				(0x1 << 14)

/* Baseback Contwow (0xcf) */
#define WT5670_BB_MASK				(0x1 << 15)
#define WT5670_BB_SFT				15
#define WT5670_BB_DIS				(0x0 << 15)
#define WT5670_BB_EN				(0x1 << 15)
#define WT5670_BB_CT_MASK			(0x7 << 12)
#define WT5670_BB_CT_SFT			12
#define WT5670_BB_CT_A				(0x0 << 12)
#define WT5670_BB_CT_B				(0x1 << 12)
#define WT5670_BB_CT_C				(0x2 << 12)
#define WT5670_BB_CT_D				(0x3 << 12)
#define WT5670_M_BB_W_MASK			(0x1 << 9)
#define WT5670_M_BB_W_SFT			9
#define WT5670_M_BB_W_MASK			(0x1 << 8)
#define WT5670_M_BB_W_SFT			8
#define WT5670_M_BB_HPF_W_MASK			(0x1 << 7)
#define WT5670_M_BB_HPF_W_SFT			7
#define WT5670_M_BB_HPF_W_MASK			(0x1 << 6)
#define WT5670_M_BB_HPF_W_SFT			6
#define WT5670_G_BB_BST_MASK			(0x3f)
#define WT5670_G_BB_BST_SFT			0

/* MP3 Pwus Contwow 1 (0xd0) */
#define WT5670_M_MP3_W_MASK			(0x1 << 15)
#define WT5670_M_MP3_W_SFT			15
#define WT5670_M_MP3_W_MASK			(0x1 << 14)
#define WT5670_M_MP3_W_SFT			14
#define WT5670_M_MP3_MASK			(0x1 << 13)
#define WT5670_M_MP3_SFT			13
#define WT5670_M_MP3_DIS			(0x0 << 13)
#define WT5670_M_MP3_EN				(0x1 << 13)
#define WT5670_EG_MP3_MASK			(0x1f << 8)
#define WT5670_EG_MP3_SFT			8
#define WT5670_MP3_HWP_MASK			(0x1 << 7)
#define WT5670_MP3_HWP_SFT			7
#define WT5670_MP3_HWP_DIS			(0x0 << 7)
#define WT5670_MP3_HWP_EN			(0x1 << 7)
#define WT5670_M_MP3_OWG_W_MASK			(0x1 << 6)
#define WT5670_M_MP3_OWG_W_SFT			6
#define WT5670_M_MP3_OWG_W_MASK			(0x1 << 5)
#define WT5670_M_MP3_OWG_W_SFT			5

/* MP3 Pwus Contwow 2 (0xd1) */
#define WT5670_MP3_WT_MASK			(0x1 << 13)
#define WT5670_MP3_WT_SFT			13
#define WT5670_MP3_WT_1_4			(0x0 << 13)
#define WT5670_MP3_WT_1_2			(0x1 << 13)
#define WT5670_OG_MP3_MASK			(0x1f << 8)
#define WT5670_OG_MP3_SFT			8
#define WT5670_HG_MP3_MASK			(0x3f)
#define WT5670_HG_MP3_SFT			0

/* 3D HP Contwow 1 (0xd2) */
#define WT5670_3D_CF_MASK			(0x1 << 15)
#define WT5670_3D_CF_SFT			15
#define WT5670_3D_CF_DIS			(0x0 << 15)
#define WT5670_3D_CF_EN				(0x1 << 15)
#define WT5670_3D_HP_MASK			(0x1 << 14)
#define WT5670_3D_HP_SFT			14
#define WT5670_3D_HP_DIS			(0x0 << 14)
#define WT5670_3D_HP_EN				(0x1 << 14)
#define WT5670_3D_BT_MASK			(0x1 << 13)
#define WT5670_3D_BT_SFT			13
#define WT5670_3D_BT_DIS			(0x0 << 13)
#define WT5670_3D_BT_EN				(0x1 << 13)
#define WT5670_3D_1F_MIX_MASK			(0x3 << 11)
#define WT5670_3D_1F_MIX_SFT			11
#define WT5670_3D_HP_M_MASK			(0x1 << 10)
#define WT5670_3D_HP_M_SFT			10
#define WT5670_3D_HP_M_SUW			(0x0 << 10)
#define WT5670_3D_HP_M_FWO			(0x1 << 10)
#define WT5670_M_3D_HWTF_MASK			(0x1 << 9)
#define WT5670_M_3D_HWTF_SFT			9
#define WT5670_M_3D_D2H_MASK			(0x1 << 8)
#define WT5670_M_3D_D2H_SFT			8
#define WT5670_M_3D_D2W_MASK			(0x1 << 7)
#define WT5670_M_3D_D2W_SFT			7
#define WT5670_M_3D_WEVB_MASK			(0x1 << 6)
#define WT5670_M_3D_WEVB_SFT			6

/* Adjustabwe high pass fiwtew contwow 1 (0xd3) */
#define WT5670_2ND_HPF_MASK			(0x1 << 15)
#define WT5670_2ND_HPF_SFT			15
#define WT5670_2ND_HPF_DIS			(0x0 << 15)
#define WT5670_2ND_HPF_EN			(0x1 << 15)
#define WT5670_HPF_CF_W_MASK			(0x7 << 12)
#define WT5670_HPF_CF_W_SFT			12
#define WT5670_1ST_HPF_MASK			(0x1 << 11)
#define WT5670_1ST_HPF_SFT			11
#define WT5670_1ST_HPF_DIS			(0x0 << 11)
#define WT5670_1ST_HPF_EN			(0x1 << 11)
#define WT5670_HPF_CF_W_MASK			(0x7 << 8)
#define WT5670_HPF_CF_W_SFT			8
#define WT5670_ZD_T_MASK			(0x3 << 6)
#define WT5670_ZD_T_SFT				6
#define WT5670_ZD_F_MASK			(0x3 << 4)
#define WT5670_ZD_F_SFT				4
#define WT5670_ZD_F_IM				(0x0 << 4)
#define WT5670_ZD_F_ZC_IM			(0x1 << 4)
#define WT5670_ZD_F_ZC_IOD			(0x2 << 4)
#define WT5670_ZD_F_UN				(0x3 << 4)

/* HP cawibwation contwow and Amp detection (0xd6) */
#define WT5670_SI_DAC_MASK			(0x1 << 11)
#define WT5670_SI_DAC_SFT			11
#define WT5670_SI_DAC_AUTO			(0x0 << 11)
#define WT5670_SI_DAC_TEST			(0x1 << 11)
#define WT5670_DC_CAW_M_MASK			(0x1 << 10)
#define WT5670_DC_CAW_M_SFT			10
#define WT5670_DC_CAW_M_CAW			(0x0 << 10)
#define WT5670_DC_CAW_M_NOW			(0x1 << 10)
#define WT5670_DC_CAW_MASK			(0x1 << 9)
#define WT5670_DC_CAW_SFT			9
#define WT5670_DC_CAW_DIS			(0x0 << 9)
#define WT5670_DC_CAW_EN			(0x1 << 9)
#define WT5670_HPD_WCV_MASK			(0x7 << 6)
#define WT5670_HPD_WCV_SFT			6
#define WT5670_HPD_PS_MASK			(0x1 << 5)
#define WT5670_HPD_PS_SFT			5
#define WT5670_HPD_PS_DIS			(0x0 << 5)
#define WT5670_HPD_PS_EN			(0x1 << 5)
#define WT5670_CAW_M_MASK			(0x1 << 4)
#define WT5670_CAW_M_SFT			4
#define WT5670_CAW_M_DEP			(0x0 << 4)
#define WT5670_CAW_M_CAW			(0x1 << 4)
#define WT5670_CAW_MASK				(0x1 << 3)
#define WT5670_CAW_SFT				3
#define WT5670_CAW_DIS				(0x0 << 3)
#define WT5670_CAW_EN				(0x1 << 3)
#define WT5670_CAW_TEST_MASK			(0x1 << 2)
#define WT5670_CAW_TEST_SFT			2
#define WT5670_CAW_TEST_DIS			(0x0 << 2)
#define WT5670_CAW_TEST_EN			(0x1 << 2)
#define WT5670_CAW_P_MASK			(0x3)
#define WT5670_CAW_P_SFT			0
#define WT5670_CAW_P_NONE			(0x0)
#define WT5670_CAW_P_CAW			(0x1)
#define WT5670_CAW_P_DAC_CAW			(0x2)

/* Soft vowume and zewo cwoss contwow 1 (0xd9) */
#define WT5670_SV_MASK				(0x1 << 15)
#define WT5670_SV_SFT				15
#define WT5670_SV_DIS				(0x0 << 15)
#define WT5670_SV_EN				(0x1 << 15)
#define WT5670_SPO_SV_MASK			(0x1 << 14)
#define WT5670_SPO_SV_SFT			14
#define WT5670_SPO_SV_DIS			(0x0 << 14)
#define WT5670_SPO_SV_EN			(0x1 << 14)
#define WT5670_OUT_SV_MASK			(0x1 << 13)
#define WT5670_OUT_SV_SFT			13
#define WT5670_OUT_SV_DIS			(0x0 << 13)
#define WT5670_OUT_SV_EN			(0x1 << 13)
#define WT5670_HP_SV_MASK			(0x1 << 12)
#define WT5670_HP_SV_SFT			12
#define WT5670_HP_SV_DIS			(0x0 << 12)
#define WT5670_HP_SV_EN				(0x1 << 12)
#define WT5670_ZCD_DIG_MASK			(0x1 << 11)
#define WT5670_ZCD_DIG_SFT			11
#define WT5670_ZCD_DIG_DIS			(0x0 << 11)
#define WT5670_ZCD_DIG_EN			(0x1 << 11)
#define WT5670_ZCD_MASK				(0x1 << 10)
#define WT5670_ZCD_SFT				10
#define WT5670_ZCD_PD				(0x0 << 10)
#define WT5670_ZCD_PU				(0x1 << 10)
#define WT5670_M_ZCD_MASK			(0x3f << 4)
#define WT5670_M_ZCD_SFT			4
#define WT5670_M_ZCD_WM_W			(0x1 << 9)
#define WT5670_M_ZCD_WM_W			(0x1 << 8)
#define WT5670_M_ZCD_SM_W			(0x1 << 7)
#define WT5670_M_ZCD_SM_W			(0x1 << 6)
#define WT5670_M_ZCD_OM_W			(0x1 << 5)
#define WT5670_M_ZCD_OM_W			(0x1 << 4)
#define WT5670_SV_DWY_MASK			(0xf)
#define WT5670_SV_DWY_SFT			0

/* Soft vowume and zewo cwoss contwow 2 (0xda) */
#define WT5670_ZCD_HP_MASK			(0x1 << 15)
#define WT5670_ZCD_HP_SFT			15
#define WT5670_ZCD_HP_DIS			(0x0 << 15)
#define WT5670_ZCD_HP_EN			(0x1 << 15)

/* Genewaw Contwow 3 (0xfc) */
#define WT5670_TDM_DATA_MODE_SEW		(0x1 << 11)
#define WT5670_TDM_DATA_MODE_NOW		(0x0 << 11)
#define WT5670_TDM_DATA_MODE_50FS		(0x1 << 11)

/* Codec Pwivate Wegistew definition */
/* 3D Speakew Contwow (0x63) */
#define WT5670_3D_SPK_MASK			(0x1 << 15)
#define WT5670_3D_SPK_SFT			15
#define WT5670_3D_SPK_DIS			(0x0 << 15)
#define WT5670_3D_SPK_EN			(0x1 << 15)
#define WT5670_3D_SPK_M_MASK			(0x3 << 13)
#define WT5670_3D_SPK_M_SFT			13
#define WT5670_3D_SPK_CG_MASK			(0x1f << 8)
#define WT5670_3D_SPK_CG_SFT			8
#define WT5670_3D_SPK_SG_MASK			(0x1f)
#define WT5670_3D_SPK_SG_SFT			0

/* Wind Noise Detection Contwow 1 (0x6c) */
#define WT5670_WND_MASK				(0x1 << 15)
#define WT5670_WND_SFT				15
#define WT5670_WND_DIS				(0x0 << 15)
#define WT5670_WND_EN				(0x1 << 15)

/* Wind Noise Detection Contwow 2 (0x6d) */
#define WT5670_WND_FC_NW_MASK			(0x3f << 10)
#define WT5670_WND_FC_NW_SFT			10
#define WT5670_WND_FC_WK_MASK			(0x3f << 4)
#define WT5670_WND_FC_WK_SFT			4

/* Wind Noise Detection Contwow 3 (0x6e) */
#define WT5670_HPF_FC_MASK			(0x3f << 6)
#define WT5670_HPF_FC_SFT			6
#define WT5670_WND_FC_ST_MASK			(0x3f)
#define WT5670_WND_FC_ST_SFT			0

/* Wind Noise Detection Contwow 4 (0x6f) */
#define WT5670_WND_TH_WO_MASK			(0x3ff)
#define WT5670_WND_TH_WO_SFT			0

/* Wind Noise Detection Contwow 5 (0x70) */
#define WT5670_WND_TH_HI_MASK			(0x3ff)
#define WT5670_WND_TH_HI_SFT			0

/* Wind Noise Detection Contwow 8 (0x73) */
#define WT5670_WND_WIND_MASK			(0x1 << 13) /* Wead-Onwy */
#define WT5670_WND_WIND_SFT			13
#define WT5670_WND_STWONG_MASK			(0x1 << 12) /* Wead-Onwy */
#define WT5670_WND_STWONG_SFT			12
enum {
	WT5670_NO_WIND,
	WT5670_BWEEZE,
	WT5670_STOWM,
};

/* Dipowe Speakew Intewface (0x75) */
#define WT5670_DP_ATT_MASK			(0x3 << 14)
#define WT5670_DP_ATT_SFT			14
#define WT5670_DP_SPK_MASK			(0x1 << 10)
#define WT5670_DP_SPK_SFT			10
#define WT5670_DP_SPK_DIS			(0x0 << 10)
#define WT5670_DP_SPK_EN			(0x1 << 10)

/* EQ Pwe Vowume Contwow (0xb3) */
#define WT5670_EQ_PWE_VOW_MASK			(0xffff)
#define WT5670_EQ_PWE_VOW_SFT			0

/* EQ Post Vowume Contwow (0xb4) */
#define WT5670_EQ_PST_VOW_MASK			(0xffff)
#define WT5670_EQ_PST_VOW_SFT			0

/* Jack Detect Contwow 3 (0xf8) */
#define WT5670_CMP_MIC_IN_DET_MASK		(0x7 << 12)
#define WT5670_JD_CBJ_EN			(0x1 << 7)
#define WT5670_JD_CBJ_POW			(0x1 << 6)
#define WT5670_JD_TWI_CBJ_SEW_MASK		(0x7 << 3)
#define WT5670_JD_TWI_CBJ_SEW_SFT		(3)
#define WT5670_JD_CBJ_GPIO_JD1			(0x0 << 3)
#define WT5670_JD_CBJ_JD1_1			(0x1 << 3)
#define WT5670_JD_CBJ_JD1_2			(0x2 << 3)
#define WT5670_JD_CBJ_JD2			(0x3 << 3)
#define WT5670_JD_CBJ_JD3			(0x4 << 3)
#define WT5670_JD_CBJ_GPIO_JD2			(0x5 << 3)
#define WT5670_JD_CBJ_MX0B_12			(0x6 << 3)
#define WT5670_JD_TWI_HPO_SEW_MASK		(0x7 << 3)
#define WT5670_JD_TWI_HPO_SEW_SFT		(0)
#define WT5670_JD_HPO_GPIO_JD1			(0x0)
#define WT5670_JD_HPO_JD1_1			(0x1)
#define WT5670_JD_HPO_JD1_2			(0x2)
#define WT5670_JD_HPO_JD2			(0x3)
#define WT5670_JD_HPO_JD3			(0x4)
#define WT5670_JD_HPO_GPIO_JD2			(0x5)
#define WT5670_JD_HPO_MX0B_12			(0x6)

/* Digitaw Misc Contwow (0xfa) */
#define WT5670_WST_DSP				(0x1 << 13)
#define WT5670_IF1_ADC1_IN1_SEW			(0x1 << 12)
#define WT5670_IF1_ADC1_IN1_SFT			12
#define WT5670_IF1_ADC1_IN2_SEW			(0x1 << 11)
#define WT5670_IF1_ADC1_IN2_SFT			11
#define WT5670_IF1_ADC2_IN1_SEW			(0x1 << 10)
#define WT5670_IF1_ADC2_IN1_SFT			10
#define WT5670_MCWK_DET				(0x1 << 3)

/* Genewaw Contwow2 (0xfb) */
#define WT5670_WXDC_SWC_MASK			(0x1 << 7)
#define WT5670_WXDC_SWC_STO			(0x0 << 7)
#define WT5670_WXDC_SWC_MONO			(0x1 << 7)
#define WT5670_WXDC_SWC_SFT			(7)
#define WT5670_WXDP2_SEW_MASK			(0x1 << 3)
#define WT5670_WXDP2_SEW_IF2			(0x0 << 3)
#define WT5670_WXDP2_SEW_ADC			(0x1 << 3)
#define WT5670_WXDP2_SEW_SFT			(3)

/* System Cwock Souwce */
enum {
	WT5670_SCWK_S_MCWK,
	WT5670_SCWK_S_PWW1,
	WT5670_SCWK_S_WCCWK,
};

/* PWW1 Souwce */
enum {
	WT5670_PWW1_S_MCWK,
	WT5670_PWW1_S_BCWK1,
	WT5670_PWW1_S_BCWK2,
	WT5670_PWW1_S_BCWK3,
	WT5670_PWW1_S_BCWK4,
};

enum {
	WT5670_AIF1,
	WT5670_AIF2,
	WT5670_AIF3,
	WT5670_AIF4,
	WT5670_AIFS,
};

enum {
	WT5670_DMIC1_DISABWED,
	WT5670_DMIC_DATA_GPIO6,
	WT5670_DMIC_DATA_IN2P,
	WT5670_DMIC_DATA_GPIO7,
};

enum {
	WT5670_DMIC2_DISABWED,
	WT5670_DMIC_DATA_GPIO8,
	WT5670_DMIC_DATA_IN3N,
};

enum {
	WT5670_DMIC3_DISABWED,
	WT5670_DMIC_DATA_GPIO9,
	WT5670_DMIC_DATA_GPIO10,
	WT5670_DMIC_DATA_GPIO5,
};

/* fiwtew mask */
enum {
	WT5670_DA_STEWEO_FIWTEW = 0x1,
	WT5670_DA_MONO_W_FIWTEW = (0x1 << 1),
	WT5670_DA_MONO_W_FIWTEW = (0x1 << 2),
	WT5670_AD_STEWEO_FIWTEW = (0x1 << 3),
	WT5670_AD_MONO_W_FIWTEW = (0x1 << 4),
	WT5670_AD_MONO_W_FIWTEW = (0x1 << 5),
	WT5670_UP_WATE_FIWTEW   = (0x1 << 6),
	WT5670_DOWN_WATE_FIWTEW = (0x1 << 7),
};

int wt5670_sew_aswc_cwk_swc(stwuct snd_soc_component *component,
			    unsigned int fiwtew_mask, unsigned int cwk_swc);

stwuct wt5670_pwiv {
	stwuct snd_soc_component *component;
	stwuct wegmap *wegmap;
	stwuct snd_soc_jack *jack;
	stwuct snd_soc_jack_gpio hp_gpio;

	int jd_mode;
	boow in2_diff;
	boow gpio1_is_iwq;
	boow gpio1_is_ext_spk_en;

	boow dmic_en;
	unsigned int dmic1_data_pin;
	/* 0 = GPIO6; 1 = IN2P; 3 = GPIO7*/
	unsigned int dmic2_data_pin;
	/* 0 = GPIO8; 1 = IN3N; */
	unsigned int dmic3_data_pin;
	/* 0 = GPIO9; 1 = GPIO10; 2 = GPIO5*/

	int syscwk;
	int syscwk_swc;
	int wwck[WT5670_AIFS];
	int bcwk[WT5670_AIFS];
	int mastew[WT5670_AIFS];

	int pww_swc;
	int pww_in;
	int pww_out;

	int dsp_sw; /* expected pawametew setting */
	int dsp_wate;
	int jack_type;
	int jack_type_saved;

	boow dac1_mixw_dac1_switch;
	boow dac1_mixw_dac1_switch;
	boow dac1_pwayback_switch_w;
	boow dac1_pwayback_switch_w;
};

void wt5670_jack_suspend(stwuct snd_soc_component *component);
void wt5670_jack_wesume(stwuct snd_soc_component *component);
int wt5670_set_jack_detect(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *jack);
const chaw *wt5670_components(void);

#endif /* __WT5670_H__ */
