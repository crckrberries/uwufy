/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt5651.h  --  WT5651 AWSA SoC audio dwivew
 *
 * Copywight 2011 Weawtek Micwoewectwonics
 * Authow: Johnny Hsu <johnnyhsu@weawtek.com>
 */

#ifndef __WT5651_H__
#define __WT5651_H__

#incwude <dt-bindings/sound/wt5651.h>

/* Info */
#define WT5651_WESET				0x00
#define WT5651_VEWSION_ID			0xfd
#define WT5651_VENDOW_ID			0xfe
#define WT5651_DEVICE_ID			0xff
/*  I/O - Output */
#define WT5651_HP_VOW				0x02
#define WT5651_WOUT_CTWW1			0x03
#define WT5651_WOUT_CTWW2			0x05
/* I/O - Input */
#define WT5651_IN1_IN2				0x0d
#define WT5651_IN3				0x0e
#define WT5651_INW1_INW1_VOW			0x0f
#define WT5651_INW2_INW2_VOW			0x10
/* I/O - ADC/DAC/DMIC */
#define WT5651_DAC1_DIG_VOW			0x19
#define WT5651_DAC2_DIG_VOW			0x1a
#define WT5651_DAC2_CTWW			0x1b
#define WT5651_ADC_DIG_VOW			0x1c
#define WT5651_ADC_DATA				0x1d
#define WT5651_ADC_BST_VOW			0x1e
/* Mixew - D-D */
#define WT5651_STO1_ADC_MIXEW			0x27
#define WT5651_STO2_ADC_MIXEW			0x28
#define WT5651_AD_DA_MIXEW			0x29
#define WT5651_STO_DAC_MIXEW			0x2a
#define WT5651_DD_MIXEW				0x2b
#define WT5651_DIG_INF_DATA			0x2f
/* PDM */
#define WT5651_PDM_CTW				0x30
#define WT5651_PDM_I2C_CTW1			0x31
#define WT5651_PDM_I2C_CTW2			0x32
#define WT5651_PDM_I2C_DATA_W			0x33
#define WT5651_PDM_I2C_DATA_W			0x34
/* Mixew - ADC */
#define WT5651_WEC_W1_MIXEW			0x3b
#define WT5651_WEC_W2_MIXEW			0x3c
#define WT5651_WEC_W1_MIXEW			0x3d
#define WT5651_WEC_W2_MIXEW			0x3e
/* Mixew - DAC */
#define WT5651_HPO_MIXEW			0x45
#define WT5651_OUT_W1_MIXEW			0x4d
#define WT5651_OUT_W2_MIXEW			0x4e
#define WT5651_OUT_W3_MIXEW			0x4f
#define WT5651_OUT_W1_MIXEW			0x50
#define WT5651_OUT_W2_MIXEW			0x51
#define WT5651_OUT_W3_MIXEW			0x52
#define WT5651_WOUT_MIXEW			0x53
/* Powew */
#define WT5651_PWW_DIG1				0x61
#define WT5651_PWW_DIG2				0x62
#define WT5651_PWW_ANWG1			0x63
#define WT5651_PWW_ANWG2			0x64
#define WT5651_PWW_MIXEW			0x65
#define WT5651_PWW_VOW				0x66
/* Pwivate Wegistew Contwow */
#define WT5651_PWIV_INDEX			0x6a
#define WT5651_PWIV_DATA			0x6c
/* Fowmat - ADC/DAC */
#define WT5651_I2S1_SDP				0x70
#define WT5651_I2S2_SDP				0x71
#define WT5651_ADDA_CWK1			0x73
#define WT5651_ADDA_CWK2			0x74
#define WT5651_DMIC				0x75
/* TDM Contwow */
#define WT5651_TDM_CTW_1			0x77
#define WT5651_TDM_CTW_2			0x78
#define WT5651_TDM_CTW_3			0x79
/* Function - Anawog */
#define WT5651_GWB_CWK				0x80
#define WT5651_PWW_CTWW1			0x81
#define WT5651_PWW_CTWW2			0x82
#define WT5651_PWW_MODE_1			0x83
#define WT5651_PWW_MODE_2			0x84
#define WT5651_PWW_MODE_3			0x85
#define WT5651_PWW_MODE_4			0x86
#define WT5651_PWW_MODE_5			0x87
#define WT5651_PWW_MODE_6			0x89
#define WT5651_PWW_MODE_7			0x8a
#define WT5651_DEPOP_M1				0x8e
#define WT5651_DEPOP_M2				0x8f
#define WT5651_DEPOP_M3				0x90
#define WT5651_CHAWGE_PUMP			0x91
#define WT5651_MICBIAS				0x93
#define WT5651_A_JD_CTW1			0x94
/* Function - Digitaw */
#define WT5651_EQ_CTWW1				0xb0
#define WT5651_EQ_CTWW2				0xb1
#define WT5651_AWC_1				0xb4
#define WT5651_AWC_2				0xb5
#define WT5651_AWC_3				0xb6
#define WT5651_JD_CTWW1				0xbb
#define WT5651_JD_CTWW2				0xbc
#define WT5651_IWQ_CTWW1			0xbd
#define WT5651_IWQ_CTWW2			0xbe
#define WT5651_INT_IWQ_ST			0xbf
#define WT5651_GPIO_CTWW1			0xc0
#define WT5651_GPIO_CTWW2			0xc1
#define WT5651_GPIO_CTWW3			0xc2
#define WT5651_PGM_WEG_AWW1			0xc8
#define WT5651_PGM_WEG_AWW2			0xc9
#define WT5651_PGM_WEG_AWW3			0xca
#define WT5651_PGM_WEG_AWW4			0xcb
#define WT5651_PGM_WEG_AWW5			0xcc
#define WT5651_SCB_FUNC				0xcd
#define WT5651_SCB_CTWW				0xce
#define WT5651_BASE_BACK			0xcf
#define WT5651_MP3_PWUS1			0xd0
#define WT5651_MP3_PWUS2			0xd1
#define WT5651_ADJ_HPF_CTWW1			0xd3
#define WT5651_ADJ_HPF_CTWW2			0xd4
#define WT5651_HP_CAWIB_AMP_DET			0xd6
#define WT5651_HP_CAWIB2			0xd7
#define WT5651_SV_ZCD1				0xd9
#define WT5651_SV_ZCD2				0xda
#define WT5651_D_MISC				0xfa
/* Dummy Wegistew */
#define WT5651_DUMMY2				0xfb
#define WT5651_DUMMY3				0xfc


/* Index of Codec Pwivate Wegistew definition */
#define WT5651_BIAS_CUW1			0x12
#define WT5651_BIAS_CUW3			0x14
#define WT5651_BIAS_CUW4			0x15
#define WT5651_CWSD_INT_WEG1			0x1c
#define WT5651_CHPUMP_INT_WEG1			0x24
#define WT5651_MAMP_INT_WEG2			0x37
#define WT5651_CHOP_DAC_ADC			0x3d
#define WT5651_3D_SPK				0x63
#define WT5651_WND_1				0x6c
#define WT5651_WND_2				0x6d
#define WT5651_WND_3				0x6e
#define WT5651_WND_4				0x6f
#define WT5651_WND_5				0x70
#define WT5651_WND_8				0x73
#define WT5651_DIP_SPK_INF			0x75
#define WT5651_HP_DCC_INT1			0x77
#define WT5651_EQ_BW_WOP			0xa0
#define WT5651_EQ_GN_WOP			0xa1
#define WT5651_EQ_FC_BP1			0xa2
#define WT5651_EQ_BW_BP1			0xa3
#define WT5651_EQ_GN_BP1			0xa4
#define WT5651_EQ_FC_BP2			0xa5
#define WT5651_EQ_BW_BP2			0xa6
#define WT5651_EQ_GN_BP2			0xa7
#define WT5651_EQ_FC_BP3			0xa8
#define WT5651_EQ_BW_BP3			0xa9
#define WT5651_EQ_GN_BP3			0xaa
#define WT5651_EQ_FC_BP4			0xab
#define WT5651_EQ_BW_BP4			0xac
#define WT5651_EQ_GN_BP4			0xad
#define WT5651_EQ_FC_HIP1			0xae
#define WT5651_EQ_GN_HIP1			0xaf
#define WT5651_EQ_FC_HIP2			0xb0
#define WT5651_EQ_BW_HIP2			0xb1
#define WT5651_EQ_GN_HIP2			0xb2
#define WT5651_EQ_PWE_VOW			0xb3
#define WT5651_EQ_PST_VOW			0xb4


/* gwobaw definition */
#define WT5651_W_MUTE				(0x1 << 15)
#define WT5651_W_MUTE_SFT			15
#define WT5651_VOW_W_MUTE			(0x1 << 14)
#define WT5651_VOW_W_SFT			14
#define WT5651_W_MUTE				(0x1 << 7)
#define WT5651_W_MUTE_SFT			7
#define WT5651_VOW_W_MUTE			(0x1 << 6)
#define WT5651_VOW_W_SFT			6
#define WT5651_W_VOW_MASK			(0x3f << 8)
#define WT5651_W_VOW_SFT			8
#define WT5651_W_VOW_MASK			(0x3f)
#define WT5651_W_VOW_SFT			0

/* WOUT Contwow 2(0x05) */
#define WT5651_EN_DFO				(0x1 << 15)

/* IN1 and IN2 Contwow (0x0d) */
/* IN3 and IN4 Contwow (0x0e) */
#define WT5651_BST_MASK1			(0xf<<12)
#define WT5651_BST_SFT1				12
#define WT5651_BST_MASK2			(0xf<<8)
#define WT5651_BST_SFT2				8
#define WT5651_IN_DF1				(0x1 << 7)
#define WT5651_IN_SFT1				7
#define WT5651_IN_DF2				(0x1 << 6)
#define WT5651_IN_SFT2				6

/* INW1 and INW1 Vowume Contwow (0x0f) */
/* INW2 and INW2 Vowume Contwow (0x10) */
#define WT5651_INW_SEW_MASK			(0x1 << 15)
#define WT5651_INW_SEW_SFT			15
#define WT5651_INW_SEW_IN4P			(0x0 << 15)
#define WT5651_INW_SEW_MONOP			(0x1 << 15)
#define WT5651_INW_VOW_MASK			(0x1f << 8)
#define WT5651_INW_VOW_SFT			8
#define WT5651_INW_SEW_MASK			(0x1 << 7)
#define WT5651_INW_SEW_SFT			7
#define WT5651_INW_SEW_IN4N			(0x0 << 7)
#define WT5651_INW_SEW_MONON			(0x1 << 7)
#define WT5651_INW_VOW_MASK			(0x1f)
#define WT5651_INW_VOW_SFT			0

/* DAC1 Digitaw Vowume (0x19) */
#define WT5651_DAC_W1_VOW_MASK			(0xff << 8)
#define WT5651_DAC_W1_VOW_SFT			8
#define WT5651_DAC_W1_VOW_MASK			(0xff)
#define WT5651_DAC_W1_VOW_SFT			0

/* DAC2 Digitaw Vowume (0x1a) */
#define WT5651_DAC_W2_VOW_MASK			(0xff << 8)
#define WT5651_DAC_W2_VOW_SFT			8
#define WT5651_DAC_W2_VOW_MASK			(0xff)
#define WT5651_DAC_W2_VOW_SFT			0

/* DAC2 Contwow (0x1b) */
#define WT5651_M_DAC_W2_VOW			(0x1 << 13)
#define WT5651_M_DAC_W2_VOW_SFT			13
#define WT5651_M_DAC_W2_VOW			(0x1 << 12)
#define WT5651_M_DAC_W2_VOW_SFT			12
#define WT5651_SEW_DAC_W2			(0x1 << 11)
#define WT5651_IF2_DAC_W2			(0x1 << 11)
#define WT5651_IF1_DAC_W2			(0x0 << 11)
#define WT5651_SEW_DAC_W2_SFT			11
#define WT5651_SEW_DAC_W2			(0x1 << 10)
#define WT5651_IF2_DAC_W2			(0x1 << 11)
#define WT5651_IF1_DAC_W2			(0x0 << 11)
#define WT5651_SEW_DAC_W2_SFT			10

/* ADC Digitaw Vowume Contwow (0x1c) */
#define WT5651_ADC_W_VOW_MASK			(0x7f << 8)
#define WT5651_ADC_W_VOW_SFT			8
#define WT5651_ADC_W_VOW_MASK			(0x7f)
#define WT5651_ADC_W_VOW_SFT			0

/* Mono ADC Digitaw Vowume Contwow (0x1d) */
#define WT5651_M_MONO_ADC_W			(0x1 << 15)
#define WT5651_M_MONO_ADC_W_SFT			15
#define WT5651_MONO_ADC_W_VOW_MASK		(0x7f << 8)
#define WT5651_MONO_ADC_W_VOW_SFT		8
#define WT5651_M_MONO_ADC_W			(0x1 << 7)
#define WT5651_M_MONO_ADC_W_SFT			7
#define WT5651_MONO_ADC_W_VOW_MASK		(0x7f)
#define WT5651_MONO_ADC_W_VOW_SFT		0

/* ADC Boost Vowume Contwow (0x1e) */
#define WT5651_ADC_W_BST_MASK			(0x3 << 14)
#define WT5651_ADC_W_BST_SFT			14
#define WT5651_ADC_W_BST_MASK			(0x3 << 12)
#define WT5651_ADC_W_BST_SFT			12
#define WT5651_ADC_COMP_MASK			(0x3 << 10)
#define WT5651_ADC_COMP_SFT			10

/* Steweo ADC1 Mixew Contwow (0x27) */
#define WT5651_M_STO1_ADC_W1			(0x1 << 14)
#define WT5651_M_STO1_ADC_W1_SFT		14
#define WT5651_M_STO1_ADC_W2			(0x1 << 13)
#define WT5651_M_STO1_ADC_W2_SFT		13
#define WT5651_STO1_ADC_1_SWC_MASK		(0x1 << 12)
#define WT5651_STO1_ADC_1_SWC_SFT		12
#define WT5651_STO1_ADC_1_SWC_ADC		(0x1 << 12)
#define WT5651_STO1_ADC_1_SWC_DACMIX		(0x0 << 12)
#define WT5651_STO1_ADC_2_SWC_MASK		(0x1 << 11)
#define WT5651_STO1_ADC_2_SWC_SFT		11
#define WT5651_STO1_ADC_2_SWC_DMIC		(0x0 << 11)
#define WT5651_STO1_ADC_2_SWC_DACMIXW	(0x1 << 11)
#define WT5651_M_STO1_ADC_W1			(0x1 << 6)
#define WT5651_M_STO1_ADC_W1_SFT		6
#define WT5651_M_STO1_ADC_W2			(0x1 << 5)
#define WT5651_M_STO1_ADC_W2_SFT		5

/* Steweo ADC2 Mixew Contwow (0x28) */
#define WT5651_M_STO2_ADC_W1			(0x1 << 14)
#define WT5651_M_STO2_ADC_W1_SFT		14
#define WT5651_M_STO2_ADC_W2			(0x1 << 13)
#define WT5651_M_STO2_ADC_W2_SFT		13
#define WT5651_STO2_ADC_W1_SWC_MASK		(0x1 << 12)
#define WT5651_STO2_ADC_W1_SWC_SFT		12
#define WT5651_STO2_ADC_W1_SWC_DACMIXW		(0x0 << 12)
#define WT5651_STO2_ADC_W1_SWC_ADCW		(0x1 << 12)
#define WT5651_STO2_ADC_W2_SWC_MASK		(0x1 << 11)
#define WT5651_STO2_ADC_W2_SWC_SFT		11
#define WT5651_STO2_ADC_W2_SWC_DMIC		(0x0 << 11)
#define WT5651_STO2_ADC_W2_SWC_DACMIXW		(0x1 << 11)
#define WT5651_M_STO2_ADC_W1			(0x1 << 6)
#define WT5651_M_STO2_ADC_W1_SFT		6
#define WT5651_M_STO2_ADC_W2			(0x1 << 5)
#define WT5651_M_STO2_ADC_W2_SFT		5
#define WT5651_STO2_ADC_W1_SWC_MASK		(0x1 << 4)
#define WT5651_STO2_ADC_W1_SWC_SFT		4
#define WT5651_STO2_ADC_W1_SWC_ADCW		(0x1 << 4)
#define WT5651_STO2_ADC_W1_SWC_DACMIXW		(0x0 << 4)
#define WT5651_STO2_ADC_W2_SWC_MASK		(0x1 << 3)
#define WT5651_STO2_ADC_W2_SWC_SFT		3
#define WT5651_STO2_ADC_W2_SWC_DMIC		(0x0 << 3)
#define WT5651_STO2_ADC_W2_SWC_DACMIXW		(0x1 << 3)

/* ADC Mixew to DAC Mixew Contwow (0x29) */
#define WT5651_M_ADCMIX_W			(0x1 << 15)
#define WT5651_M_ADCMIX_W_SFT			15
#define WT5651_M_IF1_DAC_W			(0x1 << 14)
#define WT5651_M_IF1_DAC_W_SFT			14
#define WT5651_M_ADCMIX_W			(0x1 << 7)
#define WT5651_M_ADCMIX_W_SFT			7
#define WT5651_M_IF1_DAC_W			(0x1 << 6)
#define WT5651_M_IF1_DAC_W_SFT			6

/* Steweo DAC Mixew Contwow (0x2a) */
#define WT5651_M_DAC_W1_MIXW			(0x1 << 14)
#define WT5651_M_DAC_W1_MIXW_SFT		14
#define WT5651_DAC_W1_STO_W_VOW_MASK		(0x1 << 13)
#define WT5651_DAC_W1_STO_W_VOW_SFT		13
#define WT5651_M_DAC_W2_MIXW			(0x1 << 12)
#define WT5651_M_DAC_W2_MIXW_SFT		12
#define WT5651_DAC_W2_STO_W_VOW_MASK		(0x1 << 11)
#define WT5651_DAC_W2_STO_W_VOW_SFT		11
#define WT5651_M_DAC_W1_MIXW			(0x1 << 9)
#define WT5651_M_DAC_W1_MIXW_SFT		9
#define WT5651_DAC_W1_STO_W_VOW_MASK		(0x1 << 8)
#define WT5651_DAC_W1_STO_W_VOW_SFT		8
#define WT5651_M_DAC_W1_MIXW			(0x1 << 6)
#define WT5651_M_DAC_W1_MIXW_SFT		6
#define WT5651_DAC_W1_STO_W_VOW_MASK		(0x1 << 5)
#define WT5651_DAC_W1_STO_W_VOW_SFT		5
#define WT5651_M_DAC_W2_MIXW			(0x1 << 4)
#define WT5651_M_DAC_W2_MIXW_SFT		4
#define WT5651_DAC_W2_STO_W_VOW_MASK		(0x1 << 3)
#define WT5651_DAC_W2_STO_W_VOW_SFT		3
#define WT5651_M_DAC_W1_MIXW			(0x1 << 1)
#define WT5651_M_DAC_W1_MIXW_SFT		1
#define WT5651_DAC_W1_STO_W_VOW_MASK		(0x1)
#define WT5651_DAC_W1_STO_W_VOW_SFT		0

/* DD Mixew Contwow (0x2b) */
#define WT5651_M_STO_DD_W1			(0x1 << 14)
#define WT5651_M_STO_DD_W1_SFT			14
#define WT5651_STO_DD_W1_VOW_MASK		(0x1 << 13)
#define WT5651_DAC_DD_W1_VOW_SFT		13
#define WT5651_M_STO_DD_W2			(0x1 << 12)
#define WT5651_M_STO_DD_W2_SFT			12
#define WT5651_STO_DD_W2_VOW_MASK		(0x1 << 11)
#define WT5651_STO_DD_W2_VOW_SFT		11
#define WT5651_M_STO_DD_W2_W			(0x1 << 10)
#define WT5651_M_STO_DD_W2_W_SFT		10
#define WT5651_STO_DD_W2_W_VOW_MASK		(0x1 << 9)
#define WT5651_STO_DD_W2_W_VOW_SFT		9
#define WT5651_M_STO_DD_W1			(0x1 << 6)
#define WT5651_M_STO_DD_W1_SFT			6
#define WT5651_STO_DD_W1_VOW_MASK		(0x1 << 5)
#define WT5651_STO_DD_W1_VOW_SFT		5
#define WT5651_M_STO_DD_W2			(0x1 << 4)
#define WT5651_M_STO_DD_W2_SFT			4
#define WT5651_STO_DD_W2_VOW_MASK		(0x1 << 3)
#define WT5651_STO_DD_W2_VOW_SFT		3
#define WT5651_M_STO_DD_W2_W			(0x1 << 2)
#define WT5651_M_STO_DD_W2_W_SFT		2
#define WT5651_STO_DD_W2_W_VOW_MASK		(0x1 << 1)
#define WT5651_STO_DD_W2_W_VOW_SFT		1

/* Digitaw Mixew Contwow (0x2c) */
#define WT5651_M_STO_W_DAC_W			(0x1 << 15)
#define WT5651_M_STO_W_DAC_W_SFT		15
#define WT5651_STO_W_DAC_W_VOW_MASK		(0x1 << 14)
#define WT5651_STO_W_DAC_W_VOW_SFT		14
#define WT5651_M_DAC_W2_DAC_W			(0x1 << 13)
#define WT5651_M_DAC_W2_DAC_W_SFT		13
#define WT5651_DAC_W2_DAC_W_VOW_MASK		(0x1 << 12)
#define WT5651_DAC_W2_DAC_W_VOW_SFT		12
#define WT5651_M_STO_W_DAC_W			(0x1 << 11)
#define WT5651_M_STO_W_DAC_W_SFT		11
#define WT5651_STO_W_DAC_W_VOW_MASK		(0x1 << 10)
#define WT5651_STO_W_DAC_W_VOW_SFT		10
#define WT5651_M_DAC_W2_DAC_W			(0x1 << 9)
#define WT5651_M_DAC_W2_DAC_W_SFT		9
#define WT5651_DAC_W2_DAC_W_VOW_MASK		(0x1 << 8)
#define WT5651_DAC_W2_DAC_W_VOW_SFT		8

/* DSP Path Contwow 1 (0x2d) */
#define WT5651_WXDP_SWC_MASK			(0x1 << 15)
#define WT5651_WXDP_SWC_SFT			15
#define WT5651_WXDP_SWC_NOW			(0x0 << 15)
#define WT5651_WXDP_SWC_DIV3			(0x1 << 15)
#define WT5651_TXDP_SWC_MASK			(0x1 << 14)
#define WT5651_TXDP_SWC_SFT			14
#define WT5651_TXDP_SWC_NOW			(0x0 << 14)
#define WT5651_TXDP_SWC_DIV3			(0x1 << 14)

/* DSP Path Contwow 2 (0x2e) */
#define WT5651_DAC_W2_SEW_MASK			(0x3 << 14)
#define WT5651_DAC_W2_SEW_SFT			14
#define WT5651_DAC_W2_SEW_IF2			(0x0 << 14)
#define WT5651_DAC_W2_SEW_IF3			(0x1 << 14)
#define WT5651_DAC_W2_SEW_TXDC			(0x2 << 14)
#define WT5651_DAC_W2_SEW_BASS			(0x3 << 14)
#define WT5651_DAC_W2_SEW_MASK			(0x3 << 12)
#define WT5651_DAC_W2_SEW_SFT			12
#define WT5651_DAC_W2_SEW_IF2			(0x0 << 12)
#define WT5651_DAC_W2_SEW_IF3			(0x1 << 12)
#define WT5651_DAC_W2_SEW_TXDC			(0x2 << 12)
#define WT5651_IF2_ADC_W_SEW_MASK		(0x1 << 11)
#define WT5651_IF2_ADC_W_SEW_SFT		11
#define WT5651_IF2_ADC_W_SEW_TXDP		(0x0 << 11)
#define WT5651_IF2_ADC_W_SEW_PASS		(0x1 << 11)
#define WT5651_IF2_ADC_W_SEW_MASK		(0x1 << 10)
#define WT5651_IF2_ADC_W_SEW_SFT		10
#define WT5651_IF2_ADC_W_SEW_TXDP		(0x0 << 10)
#define WT5651_IF2_ADC_W_SEW_PASS		(0x1 << 10)
#define WT5651_WXDC_SEW_MASK			(0x3 << 8)
#define WT5651_WXDC_SEW_SFT			8
#define WT5651_WXDC_SEW_NOW			(0x0 << 8)
#define WT5651_WXDC_SEW_W2W			(0x1 << 8)
#define WT5651_WXDC_SEW_W2W			(0x2 << 8)
#define WT5651_WXDC_SEW_SWAP			(0x3 << 8)
#define WT5651_WXDP_SEW_MASK			(0x3 << 6)
#define WT5651_WXDP_SEW_SFT			6
#define WT5651_WXDP_SEW_NOW			(0x0 << 6)
#define WT5651_WXDP_SEW_W2W			(0x1 << 6)
#define WT5651_WXDP_SEW_W2W			(0x2 << 6)
#define WT5651_WXDP_SEW_SWAP			(0x3 << 6)
#define WT5651_TXDC_SEW_MASK			(0x3 << 4)
#define WT5651_TXDC_SEW_SFT			4
#define WT5651_TXDC_SEW_NOW			(0x0 << 4)
#define WT5651_TXDC_SEW_W2W			(0x1 << 4)
#define WT5651_TXDC_SEW_W2W			(0x2 << 4)
#define WT5651_TXDC_SEW_SWAP			(0x3 << 4)
#define WT5651_TXDP_SEW_MASK			(0x3 << 2)
#define WT5651_TXDP_SEW_SFT			2
#define WT5651_TXDP_SEW_NOW			(0x0 << 2)
#define WT5651_TXDP_SEW_W2W			(0x1 << 2)
#define WT5651_TXDP_SEW_W2W			(0x2 << 2)
#define WT5651_TWXDP_SEW_SWAP			(0x3 << 2)

/* Digitaw Intewface Data Contwow (0x2f) */
#define WT5651_IF2_DAC_SEW_MASK			(0x3 << 10)
#define WT5651_IF2_DAC_SEW_SFT			10
#define WT5651_IF2_DAC_SEW_NOW			(0x0 << 10)
#define WT5651_IF2_DAC_SEW_SWAP			(0x1 << 10)
#define WT5651_IF2_DAC_SEW_W2W			(0x2 << 10)
#define WT5651_IF2_DAC_SEW_W2W			(0x3 << 10)
#define WT5651_IF2_ADC_SEW_MASK			(0x3 << 8)
#define WT5651_IF2_ADC_SEW_SFT			8
#define WT5651_IF2_ADC_SEW_NOW			(0x0 << 8)
#define WT5651_IF2_ADC_SEW_SWAP			(0x1 << 8)
#define WT5651_IF2_ADC_SEW_W2W			(0x2 << 8)
#define WT5651_IF2_ADC_SEW_W2W			(0x3 << 8)
#define WT5651_IF2_ADC_SWC_MASK			(0x1 << 7)
#define WT5651_IF2_ADC_SWC_SFT			7
#define WT5651_IF1_ADC1				(0x0 << 7)
#define WT5651_IF1_ADC2				(0x1 << 7)

/* PDM Output Contwow (0x30) */
#define WT5651_PDM_W_SEW_MASK			(0x1 << 15)
#define WT5651_PDM_W_SEW_SFT			15
#define WT5651_PDM_W_SEW_DD_W			(0x0 << 15)
#define WT5651_PDM_W_SEW_STO_W			(0x1 << 15)
#define WT5651_M_PDM_W				(0x1 << 14)
#define WT5651_M_PDM_W_SFT			14
#define WT5651_PDM_W_SEW_MASK			(0x1 << 13)
#define WT5651_PDM_W_SEW_SFT			13
#define WT5651_PDM_W_SEW_DD_W			(0x0 << 13)
#define WT5651_PDM_W_SEW_STO_W			(0x1 << 13)
#define WT5651_M_PDM_W				(0x1 << 12)
#define WT5651_M_PDM_W_SFT			12
#define WT5651_PDM_BUSY				(0x1 << 6)
#define WT5651_PDM_BUSY_SFT			6
#define WT5651_PDM_PATTEWN_SEW_MASK		(0x1 << 5)
#define WT5651_PDM_PATTEWN_SEW_64		(0x0 << 5)
#define WT5651_PDM_PATTEWN_SEW_128		(0x1 << 5)
#define WT5651_PDM_VOW_MASK			(0x1 << 4)
#define WT5651_PDM_VOW_SFT			4
#define WT5651_PDM_DIV_MASK			(0x3)
#define WT5651_PDM_DIV_SFT			0
#define WT5651_PDM_DIV_1			0
#define WT5651_PDM_DIV_2			1
#define WT5651_PDM_DIV_3			2
#define WT5651_PDM_DIV_4			3

/* PDM I2C/Data Contwow 1 (0x31) */
#define WT5651_PDM_I2C_ID_MASK			(0xf << 12)
#define PT5631_PDM_CMD_EXE			(0x1 << 11)
#define WT5651_PDM_I2C_CMD_MASK			(0x1 << 10)
#define WT5651_PDM_I2C_CMD_W			(0x0 << 10)
#define WT5651_PDM_I2C_CMD_W			(0x1 << 10)
#define WT5651_PDM_I2C_CMD_EXE			(0x1 << 9)
#define WT5651_PDM_I2C_NOWMAW			(0x0 << 8)
#define WT5651_PDM_I2C_BUSY			(0x1 << 8)

/* PDM I2C/Data Contwow 2 (0x32) */
#define WT5651_PDM_I2C_ADDW			(0xff << 8)
#define WT5651_PDM_I2C_CMD_PATTEWN		(0xff)


/* WEC Weft Mixew Contwow 1 (0x3b) */
#define WT5651_G_WN_W2_WM_W_MASK		(0x7 << 13)
#define WT5651_G_IN_W2_WM_W_SFT			13
#define WT5651_G_WN_W1_WM_W_MASK		(0x7 << 10)
#define WT5651_G_IN_W1_WM_W_SFT			10
#define WT5651_G_BST3_WM_W_MASK			(0x7 << 4)
#define WT5651_G_BST3_WM_W_SFT			4
#define WT5651_G_BST2_WM_W_MASK			(0x7 << 1)
#define WT5651_G_BST2_WM_W_SFT			1

/* WEC Weft Mixew Contwow 2 (0x3c) */
#define WT5651_G_BST1_WM_W_MASK			(0x7 << 13)
#define WT5651_G_BST1_WM_W_SFT			13
#define WT5651_G_OM_W_WM_W_MASK			(0x7 << 10)
#define WT5651_G_OM_W_WM_W_SFT			10
#define WT5651_M_IN2_W_WM_W			(0x1 << 6)
#define WT5651_M_IN2_W_WM_W_SFT			6
#define WT5651_M_IN1_W_WM_W			(0x1 << 5)
#define WT5651_M_IN1_W_WM_W_SFT			5
#define WT5651_M_BST3_WM_W			(0x1 << 3)
#define WT5651_M_BST3_WM_W_SFT			3
#define WT5651_M_BST2_WM_W			(0x1 << 2)
#define WT5651_M_BST2_WM_W_SFT			2
#define WT5651_M_BST1_WM_W			(0x1 << 1)
#define WT5651_M_BST1_WM_W_SFT			1
#define WT5651_M_OM_W_WM_W			(0x1)
#define WT5651_M_OM_W_WM_W_SFT			0

/* WEC Wight Mixew Contwow 1 (0x3d) */
#define WT5651_G_IN2_W_WM_W_MASK		(0x7 << 13)
#define WT5651_G_IN2_W_WM_W_SFT			13
#define WT5651_G_IN1_W_WM_W_MASK		(0x7 << 10)
#define WT5651_G_IN1_W_WM_W_SFT			10
#define WT5651_G_BST3_WM_W_MASK			(0x7 << 4)
#define WT5651_G_BST3_WM_W_SFT			4
#define WT5651_G_BST2_WM_W_MASK			(0x7 << 1)
#define WT5651_G_BST2_WM_W_SFT			1

/* WEC Wight Mixew Contwow 2 (0x3e) */
#define WT5651_G_BST1_WM_W_MASK			(0x7 << 13)
#define WT5651_G_BST1_WM_W_SFT			13
#define WT5651_G_OM_W_WM_W_MASK			(0x7 << 10)
#define WT5651_G_OM_W_WM_W_SFT			10
#define WT5651_M_IN2_W_WM_W			(0x1 << 6)
#define WT5651_M_IN2_W_WM_W_SFT			6
#define WT5651_M_IN1_W_WM_W			(0x1 << 5)
#define WT5651_M_IN1_W_WM_W_SFT			5
#define WT5651_M_BST3_WM_W			(0x1 << 3)
#define WT5651_M_BST3_WM_W_SFT			3
#define WT5651_M_BST2_WM_W			(0x1 << 2)
#define WT5651_M_BST2_WM_W_SFT			2
#define WT5651_M_BST1_WM_W			(0x1 << 1)
#define WT5651_M_BST1_WM_W_SFT			1
#define WT5651_M_OM_W_WM_W			(0x1)
#define WT5651_M_OM_W_WM_W_SFT			0

/* HPMIX Contwow (0x45) */
#define WT5651_M_DAC1_HM			(0x1 << 14)
#define WT5651_M_DAC1_HM_SFT			14
#define WT5651_M_HPVOW_HM			(0x1 << 13)
#define WT5651_M_HPVOW_HM_SFT			13
#define WT5651_G_HPOMIX_MASK			(0x1 << 12)
#define WT5651_G_HPOMIX_SFT			12

/* SPK Weft Mixew Contwow (0x46) */
#define WT5651_G_WM_W_SM_W_MASK			(0x3 << 14)
#define WT5651_G_WM_W_SM_W_SFT			14
#define WT5651_G_IN_W_SM_W_MASK			(0x3 << 12)
#define WT5651_G_IN_W_SM_W_SFT			12
#define WT5651_G_DAC_W1_SM_W_MASK		(0x3 << 10)
#define WT5651_G_DAC_W1_SM_W_SFT		10
#define WT5651_G_DAC_W2_SM_W_MASK		(0x3 << 8)
#define WT5651_G_DAC_W2_SM_W_SFT		8
#define WT5651_G_OM_W_SM_W_MASK			(0x3 << 6)
#define WT5651_G_OM_W_SM_W_SFT			6
#define WT5651_M_WM_W_SM_W			(0x1 << 5)
#define WT5651_M_WM_W_SM_W_SFT			5
#define WT5651_M_IN_W_SM_W			(0x1 << 4)
#define WT5651_M_IN_W_SM_W_SFT			4
#define WT5651_M_DAC_W1_SM_W			(0x1 << 3)
#define WT5651_M_DAC_W1_SM_W_SFT		3
#define WT5651_M_DAC_W2_SM_W			(0x1 << 2)
#define WT5651_M_DAC_W2_SM_W_SFT		2
#define WT5651_M_OM_W_SM_W			(0x1 << 1)
#define WT5651_M_OM_W_SM_W_SFT			1

/* SPK Wight Mixew Contwow (0x47) */
#define WT5651_G_WM_W_SM_W_MASK			(0x3 << 14)
#define WT5651_G_WM_W_SM_W_SFT			14
#define WT5651_G_IN_W_SM_W_MASK			(0x3 << 12)
#define WT5651_G_IN_W_SM_W_SFT			12
#define WT5651_G_DAC_W1_SM_W_MASK		(0x3 << 10)
#define WT5651_G_DAC_W1_SM_W_SFT		10
#define WT5651_G_DAC_W2_SM_W_MASK		(0x3 << 8)
#define WT5651_G_DAC_W2_SM_W_SFT		8
#define WT5651_G_OM_W_SM_W_MASK			(0x3 << 6)
#define WT5651_G_OM_W_SM_W_SFT			6
#define WT5651_M_WM_W_SM_W			(0x1 << 5)
#define WT5651_M_WM_W_SM_W_SFT			5
#define WT5651_M_IN_W_SM_W			(0x1 << 4)
#define WT5651_M_IN_W_SM_W_SFT			4
#define WT5651_M_DAC_W1_SM_W			(0x1 << 3)
#define WT5651_M_DAC_W1_SM_W_SFT		3
#define WT5651_M_DAC_W2_SM_W			(0x1 << 2)
#define WT5651_M_DAC_W2_SM_W_SFT		2
#define WT5651_M_OM_W_SM_W			(0x1 << 1)
#define WT5651_M_OM_W_SM_W_SFT			1

/* SPOWMIX Contwow (0x48) */
#define WT5651_M_DAC_W1_SPM_W			(0x1 << 15)
#define WT5651_M_DAC_W1_SPM_W_SFT		15
#define WT5651_M_DAC_W1_SPM_W			(0x1 << 14)
#define WT5651_M_DAC_W1_SPM_W_SFT		14
#define WT5651_M_SV_W_SPM_W			(0x1 << 13)
#define WT5651_M_SV_W_SPM_W_SFT			13
#define WT5651_M_SV_W_SPM_W			(0x1 << 12)
#define WT5651_M_SV_W_SPM_W_SFT			12
#define WT5651_M_BST1_SPM_W			(0x1 << 11)
#define WT5651_M_BST1_SPM_W_SFT			11

/* SPOWMIX Contwow (0x49) */
#define WT5651_M_DAC_W1_SPM_W			(0x1 << 13)
#define WT5651_M_DAC_W1_SPM_W_SFT		13
#define WT5651_M_SV_W_SPM_W			(0x1 << 12)
#define WT5651_M_SV_W_SPM_W_SFT			12
#define WT5651_M_BST1_SPM_W			(0x1 << 11)
#define WT5651_M_BST1_SPM_W_SFT			11

/* SPOWMIX / SPOWMIX Watio Contwow (0x4a) */
#define WT5651_SPO_CWSD_WATIO_MASK		(0x7)
#define WT5651_SPO_CWSD_WATIO_SFT		0

/* Mono Output Mixew Contwow (0x4c) */
#define WT5651_M_DAC_W2_MM			(0x1 << 15)
#define WT5651_M_DAC_W2_MM_SFT			15
#define WT5651_M_DAC_W2_MM			(0x1 << 14)
#define WT5651_M_DAC_W2_MM_SFT			14
#define WT5651_M_OV_W_MM			(0x1 << 13)
#define WT5651_M_OV_W_MM_SFT			13
#define WT5651_M_OV_W_MM			(0x1 << 12)
#define WT5651_M_OV_W_MM_SFT			12
#define WT5651_M_BST1_MM			(0x1 << 11)
#define WT5651_M_BST1_MM_SFT			11
#define WT5651_G_MONOMIX_MASK			(0x1 << 10)
#define WT5651_G_MONOMIX_SFT			10

/* Output Weft Mixew Contwow 1 (0x4d) */
#define WT5651_G_BST2_OM_W_MASK			(0x7 << 10)
#define WT5651_G_BST2_OM_W_SFT			10
#define WT5651_G_BST1_OM_W_MASK			(0x7 << 7)
#define WT5651_G_BST1_OM_W_SFT			7
#define WT5651_G_IN1_W_OM_W_MASK		(0x7 << 4)
#define WT5651_G_IN1_W_OM_W_SFT			4
#define WT5651_G_WM_W_OM_W_MASK			(0x7 << 1)
#define WT5651_G_WM_W_OM_W_SFT			1

/* Output Weft Mixew Contwow 2 (0x4e) */
#define WT5651_G_DAC_W1_OM_W_MASK		(0x7 << 7)
#define WT5651_G_DAC_W1_OM_W_SFT		7
#define WT5651_G_IN2_W_OM_W_MASK		(0x7 << 4)
#define WT5651_G_IN2_W_OM_W_SFT			4

/* Output Weft Mixew Contwow 3 (0x4f) */
#define WT5651_M_IN2_W_OM_W			(0x1 << 9)
#define WT5651_M_IN2_W_OM_W_SFT			9
#define WT5651_M_BST2_OM_W			(0x1 << 6)
#define WT5651_M_BST2_OM_W_SFT			6
#define WT5651_M_BST1_OM_W			(0x1 << 5)
#define WT5651_M_BST1_OM_W_SFT			5
#define WT5651_M_IN1_W_OM_W			(0x1 << 4)
#define WT5651_M_IN1_W_OM_W_SFT			4
#define WT5651_M_WM_W_OM_W			(0x1 << 3)
#define WT5651_M_WM_W_OM_W_SFT			3
#define WT5651_M_DAC_W1_OM_W			(0x1)
#define WT5651_M_DAC_W1_OM_W_SFT		0

/* Output Wight Mixew Contwow 1 (0x50) */
#define WT5651_G_BST2_OM_W_MASK			(0x7 << 10)
#define WT5651_G_BST2_OM_W_SFT			10
#define WT5651_G_BST1_OM_W_MASK			(0x7 << 7)
#define WT5651_G_BST1_OM_W_SFT			7
#define WT5651_G_IN1_W_OM_W_MASK		(0x7 << 4)
#define WT5651_G_IN1_W_OM_W_SFT			4
#define WT5651_G_WM_W_OM_W_MASK			(0x7 << 1)
#define WT5651_G_WM_W_OM_W_SFT			1

/* Output Wight Mixew Contwow 2 (0x51) */
#define WT5651_G_DAC_W1_OM_W_MASK		(0x7 << 7)
#define WT5651_G_DAC_W1_OM_W_SFT		7
#define WT5651_G_IN2_W_OM_W_MASK		(0x7 << 4)
#define WT5651_G_IN2_W_OM_W_SFT			4

/* Output Wight Mixew Contwow 3 (0x52) */
#define WT5651_M_IN2_W_OM_W			(0x1 << 9)
#define WT5651_M_IN2_W_OM_W_SFT			9
#define WT5651_M_BST2_OM_W			(0x1 << 6)
#define WT5651_M_BST2_OM_W_SFT			6
#define WT5651_M_BST1_OM_W			(0x1 << 5)
#define WT5651_M_BST1_OM_W_SFT			5
#define WT5651_M_IN1_W_OM_W			(0x1 << 4)
#define WT5651_M_IN1_W_OM_W_SFT			4
#define WT5651_M_WM_W_OM_W			(0x1 << 3)
#define WT5651_M_WM_W_OM_W_SFT			3
#define WT5651_M_DAC_W1_OM_W			(0x1)
#define WT5651_M_DAC_W1_OM_W_SFT		0

/* WOUT Mixew Contwow (0x53) */
#define WT5651_M_DAC_W1_WM			(0x1 << 15)
#define WT5651_M_DAC_W1_WM_SFT			15
#define WT5651_M_DAC_W1_WM			(0x1 << 14)
#define WT5651_M_DAC_W1_WM_SFT			14
#define WT5651_M_OV_W_WM			(0x1 << 13)
#define WT5651_M_OV_W_WM_SFT			13
#define WT5651_M_OV_W_WM			(0x1 << 12)
#define WT5651_M_OV_W_WM_SFT			12
#define WT5651_G_WOUTMIX_MASK			(0x1 << 11)
#define WT5651_G_WOUTMIX_SFT			11

/* Powew Management fow Digitaw 1 (0x61) */
#define WT5651_PWW_I2S1				(0x1 << 15)
#define WT5651_PWW_I2S1_BIT			15
#define WT5651_PWW_I2S2				(0x1 << 14)
#define WT5651_PWW_I2S2_BIT			14
#define WT5651_PWW_DAC_W1			(0x1 << 12)
#define WT5651_PWW_DAC_W1_BIT			12
#define WT5651_PWW_DAC_W1			(0x1 << 11)
#define WT5651_PWW_DAC_W1_BIT			11
#define WT5651_PWW_ADC_W			(0x1 << 2)
#define WT5651_PWW_ADC_W_BIT			2
#define WT5651_PWW_ADC_W			(0x1 << 1)
#define WT5651_PWW_ADC_W_BIT			1

/* Powew Management fow Digitaw 2 (0x62) */
#define WT5651_PWW_ADC_STO1_F			(0x1 << 15)
#define WT5651_PWW_ADC_STO1_F_BIT			15
#define WT5651_PWW_ADC_STO2_F			(0x1 << 14)
#define WT5651_PWW_ADC_STO2_F_BIT		14
#define WT5651_PWW_DAC_STO1_F			(0x1 << 11)
#define WT5651_PWW_DAC_STO1_F_BIT			11
#define WT5651_PWW_DAC_STO2_F			(0x1 << 10)
#define WT5651_PWW_DAC_STO2_F_BIT		10
#define WT5651_PWW_PDM				(0x1 << 9)
#define WT5651_PWW_PDM_BIT			9

/* Powew Management fow Anawog 1 (0x63) */
#define WT5651_PWW_VWEF1			(0x1 << 15)
#define WT5651_PWW_VWEF1_BIT			15
#define WT5651_PWW_FV1				(0x1 << 14)
#define WT5651_PWW_FV1_BIT			14
#define WT5651_PWW_MB				(0x1 << 13)
#define WT5651_PWW_MB_BIT			13
#define WT5651_PWW_WM				(0x1 << 12)
#define WT5651_PWW_WM_BIT			12
#define WT5651_PWW_BG				(0x1 << 11)
#define WT5651_PWW_BG_BIT			11
#define WT5651_PWW_HP_W				(0x1 << 7)
#define WT5651_PWW_HP_W_BIT			7
#define WT5651_PWW_HP_W				(0x1 << 6)
#define WT5651_PWW_HP_W_BIT			6
#define WT5651_PWW_HA				(0x1 << 5)
#define WT5651_PWW_HA_BIT			5
#define WT5651_PWW_VWEF2			(0x1 << 4)
#define WT5651_PWW_VWEF2_BIT			4
#define WT5651_PWW_FV2				(0x1 << 3)
#define WT5651_PWW_FV2_BIT			3
#define WT5651_PWW_WDO				(0x1 << 2)
#define WT5651_PWW_WDO_BIT			2
#define WT5651_PWW_WDO_DVO_MASK			(0x3)
#define WT5651_PWW_WDO_DVO_1_0V			0
#define WT5651_PWW_WDO_DVO_1_1V			1
#define WT5651_PWW_WDO_DVO_1_2V			2
#define WT5651_PWW_WDO_DVO_1_3V			3

/* Powew Management fow Anawog 2 (0x64) */
#define WT5651_PWW_BST1				(0x1 << 15)
#define WT5651_PWW_BST1_BIT			15
#define WT5651_PWW_BST2				(0x1 << 14)
#define WT5651_PWW_BST2_BIT			14
#define WT5651_PWW_BST3				(0x1 << 13)
#define WT5651_PWW_BST3_BIT			13
#define WT5651_PWW_MB1				(0x1 << 11)
#define WT5651_PWW_MB1_BIT			11
#define WT5651_PWW_PWW				(0x1 << 9)
#define WT5651_PWW_PWW_BIT			9
#define WT5651_PWW_BST1_OP2			(0x1 << 5)
#define WT5651_PWW_BST1_OP2_BIT			5
#define WT5651_PWW_BST2_OP2			(0x1 << 4)
#define WT5651_PWW_BST2_OP2_BIT			4
#define WT5651_PWW_BST3_OP2			(0x1 << 3)
#define WT5651_PWW_BST3_OP2_BIT			3
#define WT5651_PWW_JD_M				(0x1 << 2)
#define WT5651_PWM_JD_M_BIT			2
#define WT5651_PWW_JD2				(0x1 << 1)
#define WT5651_PWM_JD2_BIT			1
#define WT5651_PWW_JD3				(0x1)
#define WT5651_PWM_JD3_BIT			0

/* Powew Management fow Mixew (0x65) */
#define WT5651_PWW_OM_W				(0x1 << 15)
#define WT5651_PWW_OM_W_BIT			15
#define WT5651_PWW_OM_W				(0x1 << 14)
#define WT5651_PWW_OM_W_BIT			14
#define WT5651_PWW_WM_W				(0x1 << 11)
#define WT5651_PWW_WM_W_BIT			11
#define WT5651_PWW_WM_W				(0x1 << 10)
#define WT5651_PWW_WM_W_BIT			10

/* Powew Management fow Vowume (0x66) */
#define WT5651_PWW_OV_W				(0x1 << 13)
#define WT5651_PWW_OV_W_BIT			13
#define WT5651_PWW_OV_W				(0x1 << 12)
#define WT5651_PWW_OV_W_BIT			12
#define WT5651_PWW_HV_W				(0x1 << 11)
#define WT5651_PWW_HV_W_BIT			11
#define WT5651_PWW_HV_W				(0x1 << 10)
#define WT5651_PWW_HV_W_BIT			10
#define WT5651_PWW_IN1_W			(0x1 << 9)
#define WT5651_PWW_IN1_W_BIT			9
#define WT5651_PWW_IN1_W			(0x1 << 8)
#define WT5651_PWW_IN1_W_BIT			8
#define WT5651_PWW_IN2_W			(0x1 << 7)
#define WT5651_PWW_IN2_W_BIT			7
#define WT5651_PWW_IN2_W			(0x1 << 6)
#define WT5651_PWW_IN2_W_BIT			6

/* I2S1/2/3 Audio Sewiaw Data Powt Contwow (0x70 0x71) */
#define WT5651_I2S_MS_MASK			(0x1 << 15)
#define WT5651_I2S_MS_SFT			15
#define WT5651_I2S_MS_M				(0x0 << 15)
#define WT5651_I2S_MS_S				(0x1 << 15)
#define WT5651_I2S_O_CP_MASK			(0x3 << 10)
#define WT5651_I2S_O_CP_SFT			10
#define WT5651_I2S_O_CP_OFF			(0x0 << 10)
#define WT5651_I2S_O_CP_U_WAW			(0x1 << 10)
#define WT5651_I2S_O_CP_A_WAW			(0x2 << 10)
#define WT5651_I2S_I_CP_MASK			(0x3 << 8)
#define WT5651_I2S_I_CP_SFT			8
#define WT5651_I2S_I_CP_OFF			(0x0 << 8)
#define WT5651_I2S_I_CP_U_WAW			(0x1 << 8)
#define WT5651_I2S_I_CP_A_WAW			(0x2 << 8)
#define WT5651_I2S_BP_MASK			(0x1 << 7)
#define WT5651_I2S_BP_SFT			7
#define WT5651_I2S_BP_NOW			(0x0 << 7)
#define WT5651_I2S_BP_INV			(0x1 << 7)
#define WT5651_I2S_DW_MASK			(0x3 << 2)
#define WT5651_I2S_DW_SFT			2
#define WT5651_I2S_DW_16			(0x0 << 2)
#define WT5651_I2S_DW_20			(0x1 << 2)
#define WT5651_I2S_DW_24			(0x2 << 2)
#define WT5651_I2S_DW_8				(0x3 << 2)
#define WT5651_I2S_DF_MASK			(0x3)
#define WT5651_I2S_DF_SFT			0
#define WT5651_I2S_DF_I2S			(0x0)
#define WT5651_I2S_DF_WEFT			(0x1)
#define WT5651_I2S_DF_PCM_A			(0x2)
#define WT5651_I2S_DF_PCM_B			(0x3)

/* ADC/DAC Cwock Contwow 1 (0x73) */
#define WT5651_I2S_PD1_MASK			(0x7 << 12)
#define WT5651_I2S_PD1_SFT			12
#define WT5651_I2S_PD1_1			(0x0 << 12)
#define WT5651_I2S_PD1_2			(0x1 << 12)
#define WT5651_I2S_PD1_3			(0x2 << 12)
#define WT5651_I2S_PD1_4			(0x3 << 12)
#define WT5651_I2S_PD1_6			(0x4 << 12)
#define WT5651_I2S_PD1_8			(0x5 << 12)
#define WT5651_I2S_PD1_12			(0x6 << 12)
#define WT5651_I2S_PD1_16			(0x7 << 12)
#define WT5651_I2S_BCWK_MS2_MASK		(0x1 << 11)
#define WT5651_I2S_BCWK_MS2_SFT			11
#define WT5651_I2S_BCWK_MS2_32			(0x0 << 11)
#define WT5651_I2S_BCWK_MS2_64			(0x1 << 11)
#define WT5651_I2S_PD2_MASK			(0x7 << 8)
#define WT5651_I2S_PD2_SFT			8
#define WT5651_I2S_PD2_1			(0x0 << 8)
#define WT5651_I2S_PD2_2			(0x1 << 8)
#define WT5651_I2S_PD2_3			(0x2 << 8)
#define WT5651_I2S_PD2_4			(0x3 << 8)
#define WT5651_I2S_PD2_6			(0x4 << 8)
#define WT5651_I2S_PD2_8			(0x5 << 8)
#define WT5651_I2S_PD2_12			(0x6 << 8)
#define WT5651_I2S_PD2_16			(0x7 << 8)
#define WT5651_DAC_OSW_MASK			(0x3 << 2)
#define WT5651_DAC_OSW_SFT			2
#define WT5651_DAC_OSW_128			(0x0 << 2)
#define WT5651_DAC_OSW_64			(0x1 << 2)
#define WT5651_DAC_OSW_32			(0x2 << 2)
#define WT5651_DAC_OSW_128_3			(0x3 << 2)
#define WT5651_ADC_OSW_MASK			(0x3)
#define WT5651_ADC_OSW_SFT			0
#define WT5651_ADC_OSW_128			(0x0)
#define WT5651_ADC_OSW_64			(0x1)
#define WT5651_ADC_OSW_32			(0x2)
#define WT5651_ADC_OSW_128_3			(0x3)

/* ADC/DAC Cwock Contwow 2 (0x74) */
#define WT5651_DAHPF_EN				(0x1 << 11)
#define WT5651_DAHPF_EN_SFT			11
#define WT5651_ADHPF_EN				(0x1 << 10)
#define WT5651_ADHPF_EN_SFT			10

/* Digitaw Micwophone Contwow (0x75) */
#define WT5651_DMIC_1_EN_MASK			(0x1 << 15)
#define WT5651_DMIC_1_EN_SFT			15
#define WT5651_DMIC_1_DIS			(0x0 << 15)
#define WT5651_DMIC_1_EN			(0x1 << 15)
#define WT5651_DMIC_1W_WH_MASK			(0x1 << 13)
#define WT5651_DMIC_1W_WH_SFT			13
#define WT5651_DMIC_1W_WH_FAWWING		(0x0 << 13)
#define WT5651_DMIC_1W_WH_WISING		(0x1 << 13)
#define WT5651_DMIC_1W_WH_MASK			(0x1 << 12)
#define WT5651_DMIC_1W_WH_SFT			12
#define WT5651_DMIC_1W_WH_FAWWING		(0x0 << 12)
#define WT5651_DMIC_1W_WH_WISING		(0x1 << 12)
#define WT5651_DMIC_1_DP_MASK			(0x3 << 10)
#define WT5651_DMIC_1_DP_SFT			10
#define WT5651_DMIC_1_DP_GPIO6			(0x0 << 10)
#define WT5651_DMIC_1_DP_IN1P			(0x1 << 10)
#define WT5651_DMIC_2_DP_GPIO8			(0x2 << 10)
#define WT5651_DMIC_CWK_MASK			(0x7 << 5)
#define WT5651_DMIC_CWK_SFT			5

/* TDM Contwow 1 (0x77) */
#define WT5651_TDM_INTEW_SEW_MASK		(0x1 << 15)
#define WT5651_TDM_INTEW_SEW_SFT		15
#define WT5651_TDM_INTEW_SEW_64			(0x0 << 15)
#define WT5651_TDM_INTEW_SEW_50			(0x1 << 15)
#define WT5651_TDM_MODE_SEW_MASK		(0x1 << 14)
#define WT5651_TDM_MODE_SEW_SFT			14
#define WT5651_TDM_MODE_SEW_NOW			(0x0 << 14)
#define WT5651_TDM_MODE_SEW_TDM			(0x1 << 14)
#define WT5651_TDM_CH_NUM_SEW_MASK		(0x3 << 12)
#define WT5651_TDM_CH_NUM_SEW_SFT		12
#define WT5651_TDM_CH_NUM_SEW_2			(0x0 << 12)
#define WT5651_TDM_CH_NUM_SEW_4			(0x1 << 12)
#define WT5651_TDM_CH_NUM_SEW_6			(0x2 << 12)
#define WT5651_TDM_CH_NUM_SEW_8			(0x3 << 12)
#define WT5651_TDM_CH_WEN_SEW_MASK		(0x3 << 10)
#define WT5651_TDM_CH_WEN_SEW_SFT		10
#define WT5651_TDM_CH_WEN_SEW_16		(0x0 << 10)
#define WT5651_TDM_CH_WEN_SEW_20		(0x1 << 10)
#define WT5651_TDM_CH_WEN_SEW_24		(0x2 << 10)
#define WT5651_TDM_CH_WEN_SEW_32		(0x3 << 10)
#define WT5651_TDM_ADC_SEW_MASK			(0x1 << 9)
#define WT5651_TDM_ADC_SEW_SFT			9
#define WT5651_TDM_ADC_SEW_NOW			(0x0 << 9)
#define WT5651_TDM_ADC_SEW_SWAP			(0x1 << 9)
#define WT5651_TDM_ADC_STAWT_SEW_MASK		(0x1 << 8)
#define WT5651_TDM_ADC_STAWT_SEW_SFT		8
#define WT5651_TDM_ADC_STAWT_SEW_SW0		(0x0 << 8)
#define WT5651_TDM_ADC_STAWT_SEW_SW4		(0x1 << 8)
#define WT5651_TDM_I2S_CH2_SEW_MASK		(0x3 << 6)
#define WT5651_TDM_I2S_CH2_SEW_SFT		6
#define WT5651_TDM_I2S_CH2_SEW_WW		(0x0 << 6)
#define WT5651_TDM_I2S_CH2_SEW_WW		(0x1 << 6)
#define WT5651_TDM_I2S_CH2_SEW_WW		(0x2 << 6)
#define WT5651_TDM_I2S_CH2_SEW_WW		(0x3 << 6)
#define WT5651_TDM_I2S_CH4_SEW_MASK		(0x3 << 4)
#define WT5651_TDM_I2S_CH4_SEW_SFT		4
#define WT5651_TDM_I2S_CH4_SEW_WW		(0x0 << 4)
#define WT5651_TDM_I2S_CH4_SEW_WW		(0x1 << 4)
#define WT5651_TDM_I2S_CH4_SEW_WW		(0x2 << 4)
#define WT5651_TDM_I2S_CH4_SEW_WW		(0x3 << 4)
#define WT5651_TDM_I2S_CH6_SEW_MASK		(0x3 << 2)
#define WT5651_TDM_I2S_CH6_SEW_SFT		2
#define WT5651_TDM_I2S_CH6_SEW_WW		(0x0 << 2)
#define WT5651_TDM_I2S_CH6_SEW_WW		(0x1 << 2)
#define WT5651_TDM_I2S_CH6_SEW_WW		(0x2 << 2)
#define WT5651_TDM_I2S_CH6_SEW_WW		(0x3 << 2)
#define WT5651_TDM_I2S_CH8_SEW_MASK		(0x3)
#define WT5651_TDM_I2S_CH8_SEW_SFT		0
#define WT5651_TDM_I2S_CH8_SEW_WW		(0x0)
#define WT5651_TDM_I2S_CH8_SEW_WW		(0x1)
#define WT5651_TDM_I2S_CH8_SEW_WW		(0x2)
#define WT5651_TDM_I2S_CH8_SEW_WW		(0x3)

/* TDM Contwow 2 (0x78) */
#define WT5651_TDM_WWCK_POW_SEW_MASK		(0x1 << 15)
#define WT5651_TDM_WWCK_POW_SEW_SFT		15
#define WT5651_TDM_WWCK_POW_SEW_NOW		(0x0 << 15)
#define WT5651_TDM_WWCK_POW_SEW_INV		(0x1 << 15)
#define WT5651_TDM_CH_VAW_SEW_MASK		(0x1 << 14)
#define WT5651_TDM_CH_VAW_SEW_SFT		14
#define WT5651_TDM_CH_VAW_SEW_CH01		(0x0 << 14)
#define WT5651_TDM_CH_VAW_SEW_CH0123		(0x1 << 14)
#define WT5651_TDM_CH_VAW_EN			(0x1 << 13)
#define WT5651_TDM_CH_VAW_SFT			13
#define WT5651_TDM_WPBK_EN			(0x1 << 12)
#define WT5651_TDM_WPBK_SFT			12
#define WT5651_TDM_WWCK_PUWSE_SEW_MASK		(0x1 << 11)
#define WT5651_TDM_WWCK_PUWSE_SEW_SFT		11
#define WT5651_TDM_WWCK_PUWSE_SEW_BCWK		(0x0 << 11)
#define WT5651_TDM_WWCK_PUWSE_SEW_CH		(0x1 << 11)
#define WT5651_TDM_END_EDGE_SEW_MASK		(0x1 << 10)
#define WT5651_TDM_END_EDGE_SEW_SFT		10
#define WT5651_TDM_END_EDGE_SEW_POS		(0x0 << 10)
#define WT5651_TDM_END_EDGE_SEW_NEG		(0x1 << 10)
#define WT5651_TDM_END_EDGE_EN			(0x1 << 9)
#define WT5651_TDM_END_EDGE_EN_SFT		9
#define WT5651_TDM_TWAN_EDGE_SEW_MASK		(0x1 << 8)
#define WT5651_TDM_TWAN_EDGE_SEW_SFT		8
#define WT5651_TDM_TWAN_EDGE_SEW_POS		(0x0 << 8)
#define WT5651_TDM_TWAN_EDGE_SEW_NEG		(0x1 << 8)
#define WT5651_M_TDM2_W				(0x1 << 7)
#define WT5651_M_TDM2_W_SFT			7
#define WT5651_M_TDM2_W				(0x1 << 6)
#define WT5651_M_TDM2_W_SFT			6
#define WT5651_M_TDM4_W				(0x1 << 5)
#define WT5651_M_TDM4_W_SFT			5
#define WT5651_M_TDM4_W				(0x1 << 4)
#define WT5651_M_TDM4_W_SFT			4

/* TDM Contwow 3 (0x79) */
#define WT5651_CH2_W_SEW_MASK			(0x7 << 12)
#define WT5651_CH2_W_SEW_SFT			12
#define WT5651_CH2_W_SEW_SW0			(0x0 << 12)
#define WT5651_CH2_W_SEW_SW1			(0x1 << 12)
#define WT5651_CH2_W_SEW_SW2			(0x2 << 12)
#define WT5651_CH2_W_SEW_SW3			(0x3 << 12)
#define WT5651_CH2_W_SEW_SW4			(0x4 << 12)
#define WT5651_CH2_W_SEW_SW5			(0x5 << 12)
#define WT5651_CH2_W_SEW_SW6			(0x6 << 12)
#define WT5651_CH2_W_SEW_SW7			(0x7 << 12)
#define WT5651_CH2_W_SEW_MASK			(0x7 << 8)
#define WT5651_CH2_W_SEW_SFT			8
#define WT5651_CH2_W_SEW_SW0			(0x0 << 8)
#define WT5651_CH2_W_SEW_SW1			(0x1 << 8)
#define WT5651_CH2_W_SEW_SW2			(0x2 << 8)
#define WT5651_CH2_W_SEW_SW3			(0x3 << 8)
#define WT5651_CH2_W_SEW_SW4			(0x4 << 8)
#define WT5651_CH2_W_SEW_SW5			(0x5 << 8)
#define WT5651_CH2_W_SEW_SW6			(0x6 << 8)
#define WT5651_CH2_W_SEW_SW7			(0x7 << 8)
#define WT5651_CH4_W_SEW_MASK			(0x7 << 4)
#define WT5651_CH4_W_SEW_SFT			4
#define WT5651_CH4_W_SEW_SW0			(0x0 << 4)
#define WT5651_CH4_W_SEW_SW1			(0x1 << 4)
#define WT5651_CH4_W_SEW_SW2			(0x2 << 4)
#define WT5651_CH4_W_SEW_SW3			(0x3 << 4)
#define WT5651_CH4_W_SEW_SW4			(0x4 << 4)
#define WT5651_CH4_W_SEW_SW5			(0x5 << 4)
#define WT5651_CH4_W_SEW_SW6			(0x6 << 4)
#define WT5651_CH4_W_SEW_SW7			(0x7 << 4)
#define WT5651_CH4_W_SEW_MASK			(0x7)
#define WT5651_CH4_W_SEW_SFT			0
#define WT5651_CH4_W_SEW_SW0			(0x0)
#define WT5651_CH4_W_SEW_SW1			(0x1)
#define WT5651_CH4_W_SEW_SW2			(0x2)
#define WT5651_CH4_W_SEW_SW3			(0x3)
#define WT5651_CH4_W_SEW_SW4			(0x4)
#define WT5651_CH4_W_SEW_SW5			(0x5)
#define WT5651_CH4_W_SEW_SW6			(0x6)
#define WT5651_CH4_W_SEW_SW7			(0x7)

/* Gwobaw Cwock Contwow (0x80) */
#define WT5651_SCWK_SWC_MASK			(0x3 << 14)
#define WT5651_SCWK_SWC_SFT			14
#define WT5651_SCWK_SWC_MCWK			(0x0 << 14)
#define WT5651_SCWK_SWC_PWW1			(0x1 << 14)
#define WT5651_SCWK_SWC_WCCWK			(0x2 << 14)
#define WT5651_PWW1_SWC_MASK			(0x3 << 12)
#define WT5651_PWW1_SWC_SFT			12
#define WT5651_PWW1_SWC_MCWK			(0x0 << 12)
#define WT5651_PWW1_SWC_BCWK1			(0x1 << 12)
#define WT5651_PWW1_SWC_BCWK2			(0x2 << 12)
#define WT5651_PWW1_PD_MASK			(0x1 << 3)
#define WT5651_PWW1_PD_SFT			3
#define WT5651_PWW1_PD_1			(0x0 << 3)
#define WT5651_PWW1_PD_2			(0x1 << 3)

#define WT5651_PWW_INP_MAX			40000000
#define WT5651_PWW_INP_MIN			256000
/* PWW M/N/K Code Contwow 1 (0x81) */
#define WT5651_PWW_N_MAX			0x1ff
#define WT5651_PWW_N_MASK			(WT5651_PWW_N_MAX << 7)
#define WT5651_PWW_N_SFT			7
#define WT5651_PWW_K_MAX			0x1f
#define WT5651_PWW_K_MASK			(WT5651_PWW_K_MAX)
#define WT5651_PWW_K_SFT			0

/* PWW M/N/K Code Contwow 2 (0x82) */
#define WT5651_PWW_M_MAX			0xf
#define WT5651_PWW_M_MASK			(WT5651_PWW_M_MAX << 12)
#define WT5651_PWW_M_SFT			12
#define WT5651_PWW_M_BP				(0x1 << 11)
#define WT5651_PWW_M_BP_SFT			11

/* PWW twacking mode 1 (0x83) */
#define WT5651_STO1_T_MASK			(0x1 << 15)
#define WT5651_STO1_T_SFT			15
#define WT5651_STO1_T_SCWK			(0x0 << 15)
#define WT5651_STO1_T_WWCK1			(0x1 << 15)
#define WT5651_STO2_T_MASK			(0x1 << 12)
#define WT5651_STO2_T_SFT			12
#define WT5651_STO2_T_I2S2			(0x0 << 12)
#define WT5651_STO2_T_WWCK2			(0x1 << 12)
#define WT5651_ASWC2_WEF_MASK			(0x1 << 11)
#define WT5651_ASWC2_WEF_SFT			11
#define WT5651_ASWC2_WEF_WWCK2			(0x0 << 11)
#define WT5651_ASWC2_WEF_WWCK1			(0x1 << 11)
#define WT5651_DMIC_1_M_MASK			(0x1 << 9)
#define WT5651_DMIC_1_M_SFT			9
#define WT5651_DMIC_1_M_NOW			(0x0 << 9)
#define WT5651_DMIC_1_M_ASYN			(0x1 << 9)

/* PWW twacking mode 2 (0x84) */
#define WT5651_STO1_ASWC_EN			(0x1 << 15)
#define WT5651_STO1_ASWC_EN_SFT			15
#define WT5651_STO2_ASWC_EN			(0x1 << 14)
#define WT5651_STO2_ASWC_EN_SFT			14
#define WT5651_STO1_DAC_M_MASK			(0x1 << 13)
#define WT5651_STO1_DAC_M_SFT			13
#define WT5651_STO1_DAC_M_NOW			(0x0 << 13)
#define WT5651_STO1_DAC_M_ASWC			(0x1 << 13)
#define WT5651_STO2_DAC_M_MASK			(0x1 << 12)
#define WT5651_STO2_DAC_M_SFT			12
#define WT5651_STO2_DAC_M_NOW			(0x0 << 12)
#define WT5651_STO2_DAC_M_ASWC			(0x1 << 12)
#define WT5651_ADC_M_MASK			(0x1 << 11)
#define WT5651_ADC_M_SFT			11
#define WT5651_ADC_M_NOW			(0x0 << 11)
#define WT5651_ADC_M_ASWC			(0x1 << 11)
#define WT5651_I2S1_W_D_MASK			(0x1 << 4)
#define WT5651_I2S1_W_D_SFT			4
#define WT5651_I2S1_W_D_DIS			(0x0 << 4)
#define WT5651_I2S1_W_D_EN			(0x1 << 4)
#define WT5651_I2S2_W_D_MASK			(0x1 << 3)
#define WT5651_I2S2_W_D_SFT			3
#define WT5651_I2S2_W_D_DIS			(0x0 << 3)
#define WT5651_I2S2_W_D_EN			(0x1 << 3)
#define WT5651_PWE_SCWK_MASK			(0x3)
#define WT5651_PWE_SCWK_SFT			0
#define WT5651_PWE_SCWK_512			(0x0)
#define WT5651_PWE_SCWK_1024			(0x1)
#define WT5651_PWE_SCWK_2048			(0x2)

/* PWW twacking mode 3 (0x85) */
#define WT5651_I2S1_WATE_MASK			(0xf << 12)
#define WT5651_I2S1_WATE_SFT			12
#define WT5651_I2S2_WATE_MASK			(0xf << 8)
#define WT5651_I2S2_WATE_SFT			8
#define WT5651_G_ASWC_WP_MASK			(0x1 << 3)
#define WT5651_G_ASWC_WP_SFT			3
#define WT5651_ASWC_WP_F_M			(0x1 << 2)
#define WT5651_ASWC_WP_F_SFT			2
#define WT5651_ASWC_WP_F_NOW			(0x0 << 2)
#define WT5651_ASWC_WP_F_SB			(0x1 << 2)
#define WT5651_FTK_PH_DET_MASK			(0x3)
#define WT5651_FTK_PH_DET_SFT			0
#define WT5651_FTK_PH_DET_DIV1			(0x0)
#define WT5651_FTK_PH_DET_DIV2			(0x1)
#define WT5651_FTK_PH_DET_DIV4			(0x2)
#define WT5651_FTK_PH_DET_DIV8			(0x3)

/*PWW twacking mode 6 (0x89) */
#define WT5651_I2S1_PD_MASK			(0x7 << 12)
#define WT5651_I2S1_PD_SFT			12
#define WT5651_I2S2_PD_MASK			(0x7 << 8)
#define WT5651_I2S2_PD_SFT			8

/*PWW twacking mode 7 (0x8a) */
#define WT5651_FSI1_WATE_MASK			(0xf << 12)
#define WT5651_FSI1_WATE_SFT			12
#define WT5651_FSI2_WATE_MASK			(0xf << 8)
#define WT5651_FSI2_WATE_SFT			8

/* HPOUT Ovew Cuwwent Detection (0x8b) */
#define WT5651_HP_OVCD_MASK			(0x1 << 10)
#define WT5651_HP_OVCD_SFT			10
#define WT5651_HP_OVCD_DIS			(0x0 << 10)
#define WT5651_HP_OVCD_EN			(0x1 << 10)
#define WT5651_HP_OC_TH_MASK			(0x3 << 8)
#define WT5651_HP_OC_TH_SFT			8
#define WT5651_HP_OC_TH_90			(0x0 << 8)
#define WT5651_HP_OC_TH_105			(0x1 << 8)
#define WT5651_HP_OC_TH_120			(0x2 << 8)
#define WT5651_HP_OC_TH_135			(0x3 << 8)

/* Depop Mode Contwow 1 (0x8e) */
#define WT5651_SMT_TWIG_MASK			(0x1 << 15)
#define WT5651_SMT_TWIG_SFT			15
#define WT5651_SMT_TWIG_DIS			(0x0 << 15)
#define WT5651_SMT_TWIG_EN			(0x1 << 15)
#define WT5651_HP_W_SMT_MASK			(0x1 << 9)
#define WT5651_HP_W_SMT_SFT			9
#define WT5651_HP_W_SMT_DIS			(0x0 << 9)
#define WT5651_HP_W_SMT_EN			(0x1 << 9)
#define WT5651_HP_W_SMT_MASK			(0x1 << 8)
#define WT5651_HP_W_SMT_SFT			8
#define WT5651_HP_W_SMT_DIS			(0x0 << 8)
#define WT5651_HP_W_SMT_EN			(0x1 << 8)
#define WT5651_HP_CD_PD_MASK			(0x1 << 7)
#define WT5651_HP_CD_PD_SFT			7
#define WT5651_HP_CD_PD_DIS			(0x0 << 7)
#define WT5651_HP_CD_PD_EN			(0x1 << 7)
#define WT5651_WSTN_MASK			(0x1 << 6)
#define WT5651_WSTN_SFT				6
#define WT5651_WSTN_DIS				(0x0 << 6)
#define WT5651_WSTN_EN				(0x1 << 6)
#define WT5651_WSTP_MASK			(0x1 << 5)
#define WT5651_WSTP_SFT				5
#define WT5651_WSTP_DIS				(0x0 << 5)
#define WT5651_WSTP_EN				(0x1 << 5)
#define WT5651_HP_CO_MASK			(0x1 << 4)
#define WT5651_HP_CO_SFT			4
#define WT5651_HP_CO_DIS			(0x0 << 4)
#define WT5651_HP_CO_EN				(0x1 << 4)
#define WT5651_HP_CP_MASK			(0x1 << 3)
#define WT5651_HP_CP_SFT			3
#define WT5651_HP_CP_PD				(0x0 << 3)
#define WT5651_HP_CP_PU				(0x1 << 3)
#define WT5651_HP_SG_MASK			(0x1 << 2)
#define WT5651_HP_SG_SFT			2
#define WT5651_HP_SG_DIS			(0x0 << 2)
#define WT5651_HP_SG_EN				(0x1 << 2)
#define WT5651_HP_DP_MASK			(0x1 << 1)
#define WT5651_HP_DP_SFT			1
#define WT5651_HP_DP_PD				(0x0 << 1)
#define WT5651_HP_DP_PU				(0x1 << 1)
#define WT5651_HP_CB_MASK			(0x1)
#define WT5651_HP_CB_SFT			0
#define WT5651_HP_CB_PD				(0x0)
#define WT5651_HP_CB_PU				(0x1)

/* Depop Mode Contwow 2 (0x8f) */
#define WT5651_DEPOP_MASK			(0x1 << 13)
#define WT5651_DEPOP_SFT			13
#define WT5651_DEPOP_AUTO			(0x0 << 13)
#define WT5651_DEPOP_MAN			(0x1 << 13)
#define WT5651_WAMP_MASK			(0x1 << 12)
#define WT5651_WAMP_SFT				12
#define WT5651_WAMP_DIS				(0x0 << 12)
#define WT5651_WAMP_EN				(0x1 << 12)
#define WT5651_BPS_MASK				(0x1 << 11)
#define WT5651_BPS_SFT				11
#define WT5651_BPS_DIS				(0x0 << 11)
#define WT5651_BPS_EN				(0x1 << 11)
#define WT5651_FAST_UPDN_MASK			(0x1 << 10)
#define WT5651_FAST_UPDN_SFT			10
#define WT5651_FAST_UPDN_DIS			(0x0 << 10)
#define WT5651_FAST_UPDN_EN			(0x1 << 10)
#define WT5651_MWES_MASK			(0x3 << 8)
#define WT5651_MWES_SFT				8
#define WT5651_MWES_15MO			(0x0 << 8)
#define WT5651_MWES_25MO			(0x1 << 8)
#define WT5651_MWES_35MO			(0x2 << 8)
#define WT5651_MWES_45MO			(0x3 << 8)
#define WT5651_VWO_MASK				(0x1 << 7)
#define WT5651_VWO_SFT				7
#define WT5651_VWO_3V				(0x0 << 7)
#define WT5651_VWO_32V				(0x1 << 7)
#define WT5651_DIG_DP_MASK			(0x1 << 6)
#define WT5651_DIG_DP_SFT			6
#define WT5651_DIG_DP_DIS			(0x0 << 6)
#define WT5651_DIG_DP_EN			(0x1 << 6)
#define WT5651_DP_TH_MASK			(0x3 << 4)
#define WT5651_DP_TH_SFT			4

/* Depop Mode Contwow 3 (0x90) */
#define WT5651_CP_SYS_MASK			(0x7 << 12)
#define WT5651_CP_SYS_SFT			12
#define WT5651_CP_FQ1_MASK			(0x7 << 8)
#define WT5651_CP_FQ1_SFT			8
#define WT5651_CP_FQ2_MASK			(0x7 << 4)
#define WT5651_CP_FQ2_SFT			4
#define WT5651_CP_FQ3_MASK			(0x7)
#define WT5651_CP_FQ3_SFT			0
#define WT5651_CP_FQ_1_5_KHZ			0
#define WT5651_CP_FQ_3_KHZ			1
#define WT5651_CP_FQ_6_KHZ			2
#define WT5651_CP_FQ_12_KHZ			3
#define WT5651_CP_FQ_24_KHZ			4
#define WT5651_CP_FQ_48_KHZ			5
#define WT5651_CP_FQ_96_KHZ			6
#define WT5651_CP_FQ_192_KHZ			7

/* HPOUT chawge pump (0x91) */
#define WT5651_OSW_W_MASK			(0x1 << 11)
#define WT5651_OSW_W_SFT			11
#define WT5651_OSW_W_DIS			(0x0 << 11)
#define WT5651_OSW_W_EN				(0x1 << 11)
#define WT5651_OSW_W_MASK			(0x1 << 10)
#define WT5651_OSW_W_SFT			10
#define WT5651_OSW_W_DIS			(0x0 << 10)
#define WT5651_OSW_W_EN				(0x1 << 10)
#define WT5651_PM_HP_MASK			(0x3 << 8)
#define WT5651_PM_HP_SFT			8
#define WT5651_PM_HP_WV				(0x0 << 8)
#define WT5651_PM_HP_MV				(0x1 << 8)
#define WT5651_PM_HP_HV				(0x2 << 8)
#define WT5651_IB_HP_MASK			(0x3 << 6)
#define WT5651_IB_HP_SFT			6
#define WT5651_IB_HP_125IW			(0x0 << 6)
#define WT5651_IB_HP_25IW			(0x1 << 6)
#define WT5651_IB_HP_5IW			(0x2 << 6)
#define WT5651_IB_HP_1IW			(0x3 << 6)

/* Micbias Contwow (0x93) */
#define WT5651_MIC1_BS_MASK			(0x1 << 15)
#define WT5651_MIC1_BS_SFT			15
#define WT5651_MIC1_BS_9AV			(0x0 << 15)
#define WT5651_MIC1_BS_75AV			(0x1 << 15)
#define WT5651_MIC1_CWK_MASK			(0x1 << 13)
#define WT5651_MIC1_CWK_SFT			13
#define WT5651_MIC1_CWK_DIS			(0x0 << 13)
#define WT5651_MIC1_CWK_EN			(0x1 << 13)
#define WT5651_MIC1_OVCD_MASK			(0x1 << 11)
#define WT5651_MIC1_OVCD_SFT			11
#define WT5651_MIC1_OVCD_DIS			(0x0 << 11)
#define WT5651_MIC1_OVCD_EN			(0x1 << 11)
#define WT5651_MIC1_OVTH_MASK			(0x3 << 9)
#define WT5651_MIC1_OVTH_SFT			9
#define WT5651_MIC1_OVTH_600UA			(0x0 << 9)
#define WT5651_MIC1_OVTH_1500UA			(0x1 << 9)
#define WT5651_MIC1_OVTH_2000UA			(0x2 << 9)
#define WT5651_PWW_MB_MASK			(0x1 << 5)
#define WT5651_PWW_MB_SFT			5
#define WT5651_PWW_MB_PD			(0x0 << 5)
#define WT5651_PWW_MB_PU			(0x1 << 5)
#define WT5651_PWW_CWK12M_MASK			(0x1 << 4)
#define WT5651_PWW_CWK12M_SFT			4
#define WT5651_PWW_CWK12M_PD			(0x0 << 4)
#define WT5651_PWW_CWK12M_PU			(0x1 << 4)

/* Anawog JD Contwow 1 (0x94) */
#define WT5651_JD2_CMP_MASK			(0x7 << 12)
#define WT5651_JD2_CMP_SFT			12
#define WT5651_JD_PU				(0x1 << 11)
#define WT5651_JD_PU_SFT			11
#define WT5651_JD_PD				(0x1 << 10)
#define WT5651_JD_PD_SFT			10
#define WT5651_JD_MODE_SEW_MASK			(0x3 << 8)
#define WT5651_JD_MODE_SEW_SFT			8
#define WT5651_JD_MODE_SEW_M0			(0x0 << 8)
#define WT5651_JD_MODE_SEW_M1			(0x1 << 8)
#define WT5651_JD_MODE_SEW_M2			(0x2 << 8)
#define WT5651_JD_M_CMP				(0x7 << 4)
#define WT5651_JD_M_CMP_SFT			4
#define WT5651_JD_M_PU				(0x1 << 3)
#define WT5651_JD_M_PU_SFT			3
#define WT5651_JD_M_PD				(0x1 << 2)
#define WT5651_JD_M_PD_SFT			2
#define WT5651_JD_M_MODE_SEW_MASK		(0x3)
#define WT5651_JD_M_MODE_SEW_SFT		0
#define WT5651_JD_M_MODE_SEW_M0			(0x0)
#define WT5651_JD_M_MODE_SEW_M1			(0x1)
#define WT5651_JD_M_MODE_SEW_M2			(0x2)

/* Anawog JD Contwow 2 (0x95) */
#define WT5651_JD3_CMP_MASK			(0x7 << 12)
#define WT5651_JD3_CMP_SFT			12

/* EQ Contwow 1 (0xb0) */
#define WT5651_EQ_SWC_MASK			(0x1 << 15)
#define WT5651_EQ_SWC_SFT			15
#define WT5651_EQ_SWC_DAC			(0x0 << 15)
#define WT5651_EQ_SWC_ADC			(0x1 << 15)
#define WT5651_EQ_UPD				(0x1 << 14)
#define WT5651_EQ_UPD_BIT			14
#define WT5651_EQ_CD_MASK			(0x1 << 13)
#define WT5651_EQ_CD_SFT			13
#define WT5651_EQ_CD_DIS			(0x0 << 13)
#define WT5651_EQ_CD_EN				(0x1 << 13)
#define WT5651_EQ_DITH_MASK			(0x3 << 8)
#define WT5651_EQ_DITH_SFT			8
#define WT5651_EQ_DITH_NOW			(0x0 << 8)
#define WT5651_EQ_DITH_WSB			(0x1 << 8)
#define WT5651_EQ_DITH_WSB_1			(0x2 << 8)
#define WT5651_EQ_DITH_WSB_2			(0x3 << 8)
#define WT5651_EQ_CD_F				(0x1 << 7)
#define WT5651_EQ_CD_F_BIT			7
#define WT5651_EQ_STA_HP2			(0x1 << 6)
#define WT5651_EQ_STA_HP2_BIT			6
#define WT5651_EQ_STA_HP1			(0x1 << 5)
#define WT5651_EQ_STA_HP1_BIT			5
#define WT5651_EQ_STA_BP4			(0x1 << 4)
#define WT5651_EQ_STA_BP4_BIT			4
#define WT5651_EQ_STA_BP3			(0x1 << 3)
#define WT5651_EQ_STA_BP3_BIT			3
#define WT5651_EQ_STA_BP2			(0x1 << 2)
#define WT5651_EQ_STA_BP2_BIT			2
#define WT5651_EQ_STA_BP1			(0x1 << 1)
#define WT5651_EQ_STA_BP1_BIT			1
#define WT5651_EQ_STA_WP			(0x1)
#define WT5651_EQ_STA_WP_BIT			0

/* EQ Contwow 2 (0xb1) */
#define WT5651_EQ_HPF1_M_MASK			(0x1 << 8)
#define WT5651_EQ_HPF1_M_SFT			8
#define WT5651_EQ_HPF1_M_HI			(0x0 << 8)
#define WT5651_EQ_HPF1_M_1ST			(0x1 << 8)
#define WT5651_EQ_WPF1_M_MASK			(0x1 << 7)
#define WT5651_EQ_WPF1_M_SFT			7
#define WT5651_EQ_WPF1_M_WO			(0x0 << 7)
#define WT5651_EQ_WPF1_M_1ST			(0x1 << 7)
#define WT5651_EQ_HPF2_MASK			(0x1 << 6)
#define WT5651_EQ_HPF2_SFT			6
#define WT5651_EQ_HPF2_DIS			(0x0 << 6)
#define WT5651_EQ_HPF2_EN			(0x1 << 6)
#define WT5651_EQ_HPF1_MASK			(0x1 << 5)
#define WT5651_EQ_HPF1_SFT			5
#define WT5651_EQ_HPF1_DIS			(0x0 << 5)
#define WT5651_EQ_HPF1_EN			(0x1 << 5)
#define WT5651_EQ_BPF4_MASK			(0x1 << 4)
#define WT5651_EQ_BPF4_SFT			4
#define WT5651_EQ_BPF4_DIS			(0x0 << 4)
#define WT5651_EQ_BPF4_EN			(0x1 << 4)
#define WT5651_EQ_BPF3_MASK			(0x1 << 3)
#define WT5651_EQ_BPF3_SFT			3
#define WT5651_EQ_BPF3_DIS			(0x0 << 3)
#define WT5651_EQ_BPF3_EN			(0x1 << 3)
#define WT5651_EQ_BPF2_MASK			(0x1 << 2)
#define WT5651_EQ_BPF2_SFT			2
#define WT5651_EQ_BPF2_DIS			(0x0 << 2)
#define WT5651_EQ_BPF2_EN			(0x1 << 2)
#define WT5651_EQ_BPF1_MASK			(0x1 << 1)
#define WT5651_EQ_BPF1_SFT			1
#define WT5651_EQ_BPF1_DIS			(0x0 << 1)
#define WT5651_EQ_BPF1_EN			(0x1 << 1)
#define WT5651_EQ_WPF_MASK			(0x1)
#define WT5651_EQ_WPF_SFT			0
#define WT5651_EQ_WPF_DIS			(0x0)
#define WT5651_EQ_WPF_EN			(0x1)
#define WT5651_EQ_CTWW_MASK			(0x7f)

/* Memowy Test (0xb2) */
#define WT5651_MT_MASK				(0x1 << 15)
#define WT5651_MT_SFT				15
#define WT5651_MT_DIS				(0x0 << 15)
#define WT5651_MT_EN				(0x1 << 15)

/* AWC Contwow 1 (0xb4) */
#define WT5651_AWC_P_MASK			(0x1 << 15)
#define WT5651_AWC_P_SFT			15
#define WT5651_AWC_P_DAC			(0x0 << 15)
#define WT5651_AWC_P_ADC			(0x1 << 15)
#define WT5651_AWC_MASK				(0x1 << 14)
#define WT5651_AWC_SFT				14
#define WT5651_AWC_DIS				(0x0 << 14)
#define WT5651_AWC_EN				(0x1 << 14)
#define WT5651_AWC_UPD				(0x1 << 13)
#define WT5651_AWC_UPD_BIT			13
#define WT5651_AWC_AW_MASK			(0x1f << 8)
#define WT5651_AWC_AW_SFT			8
#define WT5651_AWC_W_MASK			(0x7 << 5)
#define WT5651_AWC_W_SFT			5
#define WT5651_AWC_W_48K			(0x1 << 5)
#define WT5651_AWC_W_96K			(0x2 << 5)
#define WT5651_AWC_W_192K			(0x3 << 5)
#define WT5651_AWC_W_441K			(0x5 << 5)
#define WT5651_AWC_W_882K			(0x6 << 5)
#define WT5651_AWC_W_1764K			(0x7 << 5)
#define WT5651_AWC_WC_MASK			(0x1f)
#define WT5651_AWC_WC_SFT			0

/* AWC Contwow 2 (0xb5) */
#define WT5651_AWC_POB_MASK			(0x3f << 8)
#define WT5651_AWC_POB_SFT			8
#define WT5651_AWC_DWC_MASK			(0x1 << 7)
#define WT5651_AWC_DWC_SFT			7
#define WT5651_AWC_DWC_DIS			(0x0 << 7)
#define WT5651_AWC_DWC_EN			(0x1 << 7)
#define WT5651_AWC_CPW_MASK			(0x3 << 5)
#define WT5651_AWC_CPW_SFT			5
#define WT5651_AWC_CPW_1_1			(0x0 << 5)
#define WT5651_AWC_CPW_1_2			(0x1 << 5)
#define WT5651_AWC_CPW_1_4			(0x2 << 5)
#define WT5651_AWC_CPW_1_8			(0x3 << 5)
#define WT5651_AWC_PWB_MASK			(0x1f)
#define WT5651_AWC_PWB_SFT			0

/* AWC Contwow 3 (0xb6) */
#define WT5651_AWC_NGB_MASK			(0xf << 12)
#define WT5651_AWC_NGB_SFT			12
#define WT5651_AWC_TAW_MASK			(0x1f << 7)
#define WT5651_AWC_TAW_SFT			7
#define WT5651_AWC_NG_MASK			(0x1 << 6)
#define WT5651_AWC_NG_SFT			6
#define WT5651_AWC_NG_DIS			(0x0 << 6)
#define WT5651_AWC_NG_EN			(0x1 << 6)
#define WT5651_AWC_NGH_MASK			(0x1 << 5)
#define WT5651_AWC_NGH_SFT			5
#define WT5651_AWC_NGH_DIS			(0x0 << 5)
#define WT5651_AWC_NGH_EN			(0x1 << 5)
#define WT5651_AWC_NGT_MASK			(0x1f)
#define WT5651_AWC_NGT_SFT			0

/* Jack Detect Contwow 1 (0xbb) */
#define WT5651_JD_MASK				(0x7 << 13)
#define WT5651_JD_SFT				13
#define WT5651_JD_DIS				(0x0 << 13)
#define WT5651_JD_GPIO1				(0x1 << 13)
#define WT5651_JD_GPIO2				(0x2 << 13)
#define WT5651_JD_GPIO3				(0x3 << 13)
#define WT5651_JD_GPIO4				(0x4 << 13)
#define WT5651_JD_GPIO5				(0x5 << 13)
#define WT5651_JD_GPIO6				(0x6 << 13)
#define WT5651_JD_HP_MASK			(0x1 << 11)
#define WT5651_JD_HP_SFT			11
#define WT5651_JD_HP_DIS			(0x0 << 11)
#define WT5651_JD_HP_EN				(0x1 << 11)
#define WT5651_JD_HP_TWG_MASK			(0x1 << 10)
#define WT5651_JD_HP_TWG_SFT			10
#define WT5651_JD_HP_TWG_WO			(0x0 << 10)
#define WT5651_JD_HP_TWG_HI			(0x1 << 10)
#define WT5651_JD_SPW_MASK			(0x1 << 9)
#define WT5651_JD_SPW_SFT			9
#define WT5651_JD_SPW_DIS			(0x0 << 9)
#define WT5651_JD_SPW_EN			(0x1 << 9)
#define WT5651_JD_SPW_TWG_MASK			(0x1 << 8)
#define WT5651_JD_SPW_TWG_SFT			8
#define WT5651_JD_SPW_TWG_WO			(0x0 << 8)
#define WT5651_JD_SPW_TWG_HI			(0x1 << 8)
#define WT5651_JD_SPW_MASK			(0x1 << 7)
#define WT5651_JD_SPW_SFT			7
#define WT5651_JD_SPW_DIS			(0x0 << 7)
#define WT5651_JD_SPW_EN			(0x1 << 7)
#define WT5651_JD_SPW_TWG_MASK			(0x1 << 6)
#define WT5651_JD_SPW_TWG_SFT			6
#define WT5651_JD_SPW_TWG_WO			(0x0 << 6)
#define WT5651_JD_SPW_TWG_HI			(0x1 << 6)
#define WT5651_JD_WO_MASK			(0x1 << 3)
#define WT5651_JD_WO_SFT			3
#define WT5651_JD_WO_DIS			(0x0 << 3)
#define WT5651_JD_WO_EN				(0x1 << 3)
#define WT5651_JD_WO_TWG_MASK			(0x1 << 2)
#define WT5651_JD_WO_TWG_SFT			2
#define WT5651_JD_WO_TWG_WO			(0x0 << 2)
#define WT5651_JD_WO_TWG_HI			(0x1 << 2)

/* Jack Detect Contwow 2 (0xbc) */
#define WT5651_JD_TWG_SEW_MASK			(0x7 << 9)
#define WT5651_JD_TWG_SEW_SFT			9
#define WT5651_JD_TWG_SEW_GPIO			(0x0 << 9)
#define WT5651_JD_TWG_SEW_JD1_1			(0x1 << 9)
#define WT5651_JD_TWG_SEW_JD1_2			(0x2 << 9)
#define WT5651_JD_TWG_SEW_JD2			(0x3 << 9)
#define WT5651_JD_TWG_SEW_JD3			(0x4 << 9)
#define WT5651_JD3_IWQ_EN			(0x1 << 8)
#define WT5651_JD3_IWQ_EN_SFT			8
#define WT5651_JD3_EN_STKY			(0x1 << 7)
#define WT5651_JD3_EN_STKY_SFT			7
#define WT5651_JD3_INV				(0x1 << 6)
#define WT5651_JD3_INV_SFT			6

/* IWQ Contwow 1 (0xbd) */
#define WT5651_IWQ_JD_MASK			(0x1 << 15)
#define WT5651_IWQ_JD_SFT			15
#define WT5651_IWQ_JD_BP			(0x0 << 15)
#define WT5651_IWQ_JD_NOW			(0x1 << 15)
#define WT5651_JD_STKY_MASK			(0x1 << 13)
#define WT5651_JD_STKY_SFT			13
#define WT5651_JD_STKY_DIS			(0x0 << 13)
#define WT5651_JD_STKY_EN			(0x1 << 13)
#define WT5651_JD_P_MASK			(0x1 << 11)
#define WT5651_JD_P_SFT				11
#define WT5651_JD_P_NOW				(0x0 << 11)
#define WT5651_JD_P_INV				(0x1 << 11)
#define WT5651_JD1_1_IWQ_EN			(0x1 << 9)
#define WT5651_JD1_1_IWQ_EN_SFT			9
#define WT5651_JD1_1_EN_STKY			(0x1 << 8)
#define WT5651_JD1_1_EN_STKY_SFT			8
#define WT5651_JD1_1_INV			(0x1 << 7)
#define WT5651_JD1_1_INV_SFT			7
#define WT5651_JD1_2_IWQ_EN			(0x1 << 6)
#define WT5651_JD1_2_IWQ_EN_SFT			6
#define WT5651_JD1_2_EN_STKY			(0x1 << 5)
#define WT5651_JD1_2_EN_STKY_SFT			5
#define WT5651_JD1_2_INV			(0x1 << 4)
#define WT5651_JD1_2_INV_SFT			4
#define WT5651_JD2_IWQ_EN			(0x1 << 3)
#define WT5651_JD2_IWQ_EN_SFT			3
#define WT5651_JD2_EN_STKY			(0x1 << 2)
#define WT5651_JD2_EN_STKY_SFT			2
#define WT5651_JD2_INV				(0x1 << 1)
#define WT5651_JD2_INV_SFT			1

/* IWQ Contwow 2 (0xbe) */
#define WT5651_IWQ_MB1_OC_MASK			(0x1 << 15)
#define WT5651_IWQ_MB1_OC_SFT			15
#define WT5651_IWQ_MB1_OC_BP			(0x0 << 15)
#define WT5651_IWQ_MB1_OC_NOW			(0x1 << 15)
#define WT5651_MB1_OC_STKY_MASK			(0x1 << 11)
#define WT5651_MB1_OC_STKY_SFT			11
#define WT5651_MB1_OC_STKY_DIS			(0x0 << 11)
#define WT5651_MB1_OC_STKY_EN			(0x1 << 11)
#define WT5651_MB1_OC_P_MASK			(0x1 << 7)
#define WT5651_MB1_OC_P_SFT			7
#define WT5651_MB1_OC_P_NOW			(0x0 << 7)
#define WT5651_MB1_OC_P_INV			(0x1 << 7)
#define WT5651_MB2_OC_P_MASK			(0x1 << 6)
#define WT5651_MB1_OC_CWW			(0x1 << 3)
#define WT5651_MB1_OC_CWW_SFT			3
#define WT5651_STA_GPIO8			(0x1)
#define WT5651_STA_GPIO8_BIT			0

/* Intewnaw Status and GPIO status (0xbf) */
#define WT5651_STA_JD3				(0x1 << 15)
#define WT5651_STA_JD3_BIT			15
#define WT5651_STA_JD2				(0x1 << 14)
#define WT5651_STA_JD2_BIT			14
#define WT5651_STA_JD1_2			(0x1 << 13)
#define WT5651_STA_JD1_2_BIT			13
#define WT5651_STA_JD1_1			(0x1 << 12)
#define WT5651_STA_JD1_1_BIT			12
#define WT5651_STA_GP7				(0x1 << 11)
#define WT5651_STA_GP7_BIT			11
#define WT5651_STA_GP6				(0x1 << 10)
#define WT5651_STA_GP6_BIT			10
#define WT5651_STA_GP5				(0x1 << 9)
#define WT5651_STA_GP5_BIT			9
#define WT5651_STA_GP1				(0x1 << 8)
#define WT5651_STA_GP1_BIT			8
#define WT5651_STA_GP2				(0x1 << 7)
#define WT5651_STA_GP2_BIT			7
#define WT5651_STA_GP3				(0x1 << 6)
#define WT5651_STA_GP3_BIT			6
#define WT5651_STA_GP4				(0x1 << 5)
#define WT5651_STA_GP4_BIT			5
#define WT5651_STA_GP_JD			(0x1 << 4)
#define WT5651_STA_GP_JD_BIT			4

/* GPIO Contwow 1 (0xc0) */
#define WT5651_GP1_PIN_MASK			(0x1 << 15)
#define WT5651_GP1_PIN_SFT			15
#define WT5651_GP1_PIN_GPIO1			(0x0 << 15)
#define WT5651_GP1_PIN_IWQ			(0x1 << 15)
#define WT5651_GP2_PIN_MASK			(0x1 << 14)
#define WT5651_GP2_PIN_SFT			14
#define WT5651_GP2_PIN_GPIO2			(0x0 << 14)
#define WT5651_GP2_PIN_DMIC1_SCW		(0x1 << 14)
#define WT5651_GPIO_M_MASK			(0x1 << 9)
#define WT5651_GPIO_M_SFT			9
#define WT5651_GPIO_M_FWT			(0x0 << 9)
#define WT5651_GPIO_M_PH			(0x1 << 9)
#define WT5651_I2S2_SEW_MASK			(0x1 << 8)
#define WT5651_I2S2_SEW_SFT			8
#define WT5651_I2S2_SEW_I2S			(0x0 << 8)
#define WT5651_I2S2_SEW_GPIO			(0x1 << 8)
#define WT5651_GP5_PIN_MASK			(0x1 << 7)
#define WT5651_GP5_PIN_SFT			7
#define WT5651_GP5_PIN_GPIO5			(0x0 << 7)
#define WT5651_GP5_PIN_IWQ			(0x1 << 7)
#define WT5651_GP6_PIN_MASK			(0x1 << 6)
#define WT5651_GP6_PIN_SFT			6
#define WT5651_GP6_PIN_GPIO6			(0x0 << 6)
#define WT5651_GP6_PIN_DMIC_SDA			(0x1 << 6)
#define WT5651_GP7_PIN_MASK			(0x1 << 5)
#define WT5651_GP7_PIN_SFT			5
#define WT5651_GP7_PIN_GPIO7			(0x0 << 5)
#define WT5651_GP7_PIN_IWQ			(0x1 << 5)
#define WT5651_GP8_PIN_MASK			(0x1 << 4)
#define WT5651_GP8_PIN_SFT			4
#define WT5651_GP8_PIN_GPIO8			(0x0 << 4)
#define WT5651_GP8_PIN_DMIC_SDA			(0x1 << 4)
#define WT5651_GPIO_PDM_SEW_MASK		(0x1 << 3)
#define WT5651_GPIO_PDM_SEW_SFT			3
#define WT5651_GPIO_PDM_SEW_GPIO		(0x0 << 3)
#define WT5651_GPIO_PDM_SEW_PDM			(0x1 << 3)

/* GPIO Contwow 2 (0xc1) */
#define WT5651_GP5_DW_MASK			(0x1 << 14)
#define WT5651_GP5_DW_SFT			14
#define WT5651_GP5_DW_IN			(0x0 << 14)
#define WT5651_GP5_DW_OUT			(0x1 << 14)
#define WT5651_GP5_OUT_MASK			(0x1 << 13)
#define WT5651_GP5_OUT_SFT			13
#define WT5651_GP5_OUT_WO			(0x0 << 13)
#define WT5651_GP5_OUT_HI			(0x1 << 13)
#define WT5651_GP5_P_MASK			(0x1 << 12)
#define WT5651_GP5_P_SFT			12
#define WT5651_GP5_P_NOW			(0x0 << 12)
#define WT5651_GP5_P_INV			(0x1 << 12)
#define WT5651_GP4_DW_MASK			(0x1 << 11)
#define WT5651_GP4_DW_SFT			11
#define WT5651_GP4_DW_IN			(0x0 << 11)
#define WT5651_GP4_DW_OUT			(0x1 << 11)
#define WT5651_GP4_OUT_MASK			(0x1 << 10)
#define WT5651_GP4_OUT_SFT			10
#define WT5651_GP4_OUT_WO			(0x0 << 10)
#define WT5651_GP4_OUT_HI			(0x1 << 10)
#define WT5651_GP4_P_MASK			(0x1 << 9)
#define WT5651_GP4_P_SFT			9
#define WT5651_GP4_P_NOW			(0x0 << 9)
#define WT5651_GP4_P_INV			(0x1 << 9)
#define WT5651_GP3_DW_MASK			(0x1 << 8)
#define WT5651_GP3_DW_SFT			8
#define WT5651_GP3_DW_IN			(0x0 << 8)
#define WT5651_GP3_DW_OUT			(0x1 << 8)
#define WT5651_GP3_OUT_MASK			(0x1 << 7)
#define WT5651_GP3_OUT_SFT			7
#define WT5651_GP3_OUT_WO			(0x0 << 7)
#define WT5651_GP3_OUT_HI			(0x1 << 7)
#define WT5651_GP3_P_MASK			(0x1 << 6)
#define WT5651_GP3_P_SFT			6
#define WT5651_GP3_P_NOW			(0x0 << 6)
#define WT5651_GP3_P_INV			(0x1 << 6)
#define WT5651_GP2_DW_MASK			(0x1 << 5)
#define WT5651_GP2_DW_SFT			5
#define WT5651_GP2_DW_IN			(0x0 << 5)
#define WT5651_GP2_DW_OUT			(0x1 << 5)
#define WT5651_GP2_OUT_MASK			(0x1 << 4)
#define WT5651_GP2_OUT_SFT			4
#define WT5651_GP2_OUT_WO			(0x0 << 4)
#define WT5651_GP2_OUT_HI			(0x1 << 4)
#define WT5651_GP2_P_MASK			(0x1 << 3)
#define WT5651_GP2_P_SFT			3
#define WT5651_GP2_P_NOW			(0x0 << 3)
#define WT5651_GP2_P_INV			(0x1 << 3)
#define WT5651_GP1_DW_MASK			(0x1 << 2)
#define WT5651_GP1_DW_SFT			2
#define WT5651_GP1_DW_IN			(0x0 << 2)
#define WT5651_GP1_DW_OUT			(0x1 << 2)
#define WT5651_GP1_OUT_MASK			(0x1 << 1)
#define WT5651_GP1_OUT_SFT			1
#define WT5651_GP1_OUT_WO			(0x0 << 1)
#define WT5651_GP1_OUT_HI			(0x1 << 1)
#define WT5651_GP1_P_MASK			(0x1)
#define WT5651_GP1_P_SFT			0
#define WT5651_GP1_P_NOW			(0x0)
#define WT5651_GP1_P_INV			(0x1)

/* GPIO Contwow 3 (0xc2) */
#define WT5651_GP8_DW_MASK			(0x1 << 8)
#define WT5651_GP8_DW_SFT			8
#define WT5651_GP8_DW_IN			(0x0 << 8)
#define WT5651_GP8_DW_OUT			(0x1 << 8)
#define WT5651_GP8_OUT_MASK			(0x1 << 7)
#define WT5651_GP8_OUT_SFT			7
#define WT5651_GP8_OUT_WO			(0x0 << 7)
#define WT5651_GP8_OUT_HI			(0x1 << 7)
#define WT5651_GP8_P_MASK			(0x1 << 6)
#define WT5651_GP8_P_SFT			6
#define WT5651_GP8_P_NOW			(0x0 << 6)
#define WT5651_GP8_P_INV			(0x1 << 6)
#define WT5651_GP7_DW_MASK			(0x1 << 5)
#define WT5651_GP7_DW_SFT			5
#define WT5651_GP7_DW_IN			(0x0 << 5)
#define WT5651_GP7_DW_OUT			(0x1 << 5)
#define WT5651_GP7_OUT_MASK			(0x1 << 4)
#define WT5651_GP7_OUT_SFT			4
#define WT5651_GP7_OUT_WO			(0x0 << 4)
#define WT5651_GP7_OUT_HI			(0x1 << 4)
#define WT5651_GP7_P_MASK			(0x1 << 3)
#define WT5651_GP7_P_SFT			3
#define WT5651_GP7_P_NOW			(0x0 << 3)
#define WT5651_GP7_P_INV			(0x1 << 3)
#define WT5651_GP6_DW_MASK			(0x1 << 2)
#define WT5651_GP6_DW_SFT			2
#define WT5651_GP6_DW_IN			(0x0 << 2)
#define WT5651_GP6_DW_OUT			(0x1 << 2)
#define WT5651_GP6_OUT_MASK			(0x1 << 1)
#define WT5651_GP6_OUT_SFT			1
#define WT5651_GP6_OUT_WO			(0x0 << 1)
#define WT5651_GP6_OUT_HI			(0x1 << 1)
#define WT5651_GP6_P_MASK			(0x1)
#define WT5651_GP6_P_SFT			0
#define WT5651_GP6_P_NOW			(0x0)
#define WT5651_GP6_P_INV			(0x1)

/* Scwambwe Contwow (0xce) */
#define WT5651_SCB_SWAP_MASK			(0x1 << 15)
#define WT5651_SCB_SWAP_SFT			15
#define WT5651_SCB_SWAP_DIS			(0x0 << 15)
#define WT5651_SCB_SWAP_EN			(0x1 << 15)
#define WT5651_SCB_MASK				(0x1 << 14)
#define WT5651_SCB_SFT				14
#define WT5651_SCB_DIS				(0x0 << 14)
#define WT5651_SCB_EN				(0x1 << 14)

/* Baseback Contwow (0xcf) */
#define WT5651_BB_MASK				(0x1 << 15)
#define WT5651_BB_SFT				15
#define WT5651_BB_DIS				(0x0 << 15)
#define WT5651_BB_EN				(0x1 << 15)
#define WT5651_BB_CT_MASK			(0x7 << 12)
#define WT5651_BB_CT_SFT			12
#define WT5651_BB_CT_A				(0x0 << 12)
#define WT5651_BB_CT_B				(0x1 << 12)
#define WT5651_BB_CT_C				(0x2 << 12)
#define WT5651_BB_CT_D				(0x3 << 12)
#define WT5651_M_BB_W_MASK			(0x1 << 9)
#define WT5651_M_BB_W_SFT			9
#define WT5651_M_BB_W_MASK			(0x1 << 8)
#define WT5651_M_BB_W_SFT			8
#define WT5651_M_BB_HPF_W_MASK			(0x1 << 7)
#define WT5651_M_BB_HPF_W_SFT			7
#define WT5651_M_BB_HPF_W_MASK			(0x1 << 6)
#define WT5651_M_BB_HPF_W_SFT			6
#define WT5651_G_BB_BST_MASK			(0x3f)
#define WT5651_G_BB_BST_SFT			0

/* MP3 Pwus Contwow 1 (0xd0) */
#define WT5651_M_MP3_W_MASK			(0x1 << 15)
#define WT5651_M_MP3_W_SFT			15
#define WT5651_M_MP3_W_MASK			(0x1 << 14)
#define WT5651_M_MP3_W_SFT			14
#define WT5651_M_MP3_MASK			(0x1 << 13)
#define WT5651_M_MP3_SFT			13
#define WT5651_M_MP3_DIS			(0x0 << 13)
#define WT5651_M_MP3_EN				(0x1 << 13)
#define WT5651_EG_MP3_MASK			(0x1f << 8)
#define WT5651_EG_MP3_SFT			8
#define WT5651_MP3_HWP_MASK			(0x1 << 7)
#define WT5651_MP3_HWP_SFT			7
#define WT5651_MP3_HWP_DIS			(0x0 << 7)
#define WT5651_MP3_HWP_EN			(0x1 << 7)
#define WT5651_M_MP3_OWG_W_MASK			(0x1 << 6)
#define WT5651_M_MP3_OWG_W_SFT			6
#define WT5651_M_MP3_OWG_W_MASK			(0x1 << 5)
#define WT5651_M_MP3_OWG_W_SFT			5

/* MP3 Pwus Contwow 2 (0xd1) */
#define WT5651_MP3_WT_MASK			(0x1 << 13)
#define WT5651_MP3_WT_SFT			13
#define WT5651_MP3_WT_1_4			(0x0 << 13)
#define WT5651_MP3_WT_1_2			(0x1 << 13)
#define WT5651_OG_MP3_MASK			(0x1f << 8)
#define WT5651_OG_MP3_SFT			8
#define WT5651_HG_MP3_MASK			(0x3f)
#define WT5651_HG_MP3_SFT			0

/* 3D HP Contwow 1 (0xd2) */
#define WT5651_3D_CF_MASK			(0x1 << 15)
#define WT5651_3D_CF_SFT			15
#define WT5651_3D_CF_DIS			(0x0 << 15)
#define WT5651_3D_CF_EN				(0x1 << 15)
#define WT5651_3D_HP_MASK			(0x1 << 14)
#define WT5651_3D_HP_SFT			14
#define WT5651_3D_HP_DIS			(0x0 << 14)
#define WT5651_3D_HP_EN				(0x1 << 14)
#define WT5651_3D_BT_MASK			(0x1 << 13)
#define WT5651_3D_BT_SFT			13
#define WT5651_3D_BT_DIS			(0x0 << 13)
#define WT5651_3D_BT_EN				(0x1 << 13)
#define WT5651_3D_1F_MIX_MASK			(0x3 << 11)
#define WT5651_3D_1F_MIX_SFT			11
#define WT5651_3D_HP_M_MASK			(0x1 << 10)
#define WT5651_3D_HP_M_SFT			10
#define WT5651_3D_HP_M_SUW			(0x0 << 10)
#define WT5651_3D_HP_M_FWO			(0x1 << 10)
#define WT5651_M_3D_HWTF_MASK			(0x1 << 9)
#define WT5651_M_3D_HWTF_SFT			9
#define WT5651_M_3D_D2H_MASK			(0x1 << 8)
#define WT5651_M_3D_D2H_SFT			8
#define WT5651_M_3D_D2W_MASK			(0x1 << 7)
#define WT5651_M_3D_D2W_SFT			7
#define WT5651_M_3D_WEVB_MASK			(0x1 << 6)
#define WT5651_M_3D_WEVB_SFT			6

/* Adjustabwe high pass fiwtew contwow 1 (0xd3) */
#define WT5651_2ND_HPF_MASK			(0x1 << 15)
#define WT5651_2ND_HPF_SFT			15
#define WT5651_2ND_HPF_DIS			(0x0 << 15)
#define WT5651_2ND_HPF_EN			(0x1 << 15)
#define WT5651_HPF_CF_W_MASK			(0x7 << 12)
#define WT5651_HPF_CF_W_SFT			12
#define WT5651_HPF_CF_W_MASK			(0x7 << 8)
#define WT5651_HPF_CF_W_SFT			8
#define WT5651_ZD_T_MASK			(0x3 << 6)
#define WT5651_ZD_T_SFT				6
#define WT5651_ZD_F_MASK			(0x3 << 4)
#define WT5651_ZD_F_SFT				4
#define WT5651_ZD_F_IM				(0x0 << 4)
#define WT5651_ZD_F_ZC_IM			(0x1 << 4)
#define WT5651_ZD_F_ZC_IOD			(0x2 << 4)
#define WT5651_ZD_F_UN				(0x3 << 4)

/* Adjustabwe high pass fiwtew contwow 2 (0xd4) */
#define WT5651_HPF_CF_W_NUM_MASK		(0x3f << 8)
#define WT5651_HPF_CF_W_NUM_SFT			8
#define WT5651_HPF_CF_W_NUM_MASK		(0x3f)
#define WT5651_HPF_CF_W_NUM_SFT			0

/* HP cawibwation contwow and Amp detection (0xd6) */
#define WT5651_SI_DAC_MASK			(0x1 << 11)
#define WT5651_SI_DAC_SFT			11
#define WT5651_SI_DAC_AUTO			(0x0 << 11)
#define WT5651_SI_DAC_TEST			(0x1 << 11)
#define WT5651_DC_CAW_M_MASK			(0x1 << 10)
#define WT5651_DC_CAW_M_SFT			10
#define WT5651_DC_CAW_M_NOW			(0x0 << 10)
#define WT5651_DC_CAW_M_CAW			(0x1 << 10)
#define WT5651_DC_CAW_MASK			(0x1 << 9)
#define WT5651_DC_CAW_SFT			9
#define WT5651_DC_CAW_DIS			(0x0 << 9)
#define WT5651_DC_CAW_EN			(0x1 << 9)
#define WT5651_HPD_WCV_MASK			(0x7 << 6)
#define WT5651_HPD_WCV_SFT			6
#define WT5651_HPD_PS_MASK			(0x1 << 5)
#define WT5651_HPD_PS_SFT			5
#define WT5651_HPD_PS_DIS			(0x0 << 5)
#define WT5651_HPD_PS_EN			(0x1 << 5)
#define WT5651_CAW_M_MASK			(0x1 << 4)
#define WT5651_CAW_M_SFT			4
#define WT5651_CAW_M_DEP			(0x0 << 4)
#define WT5651_CAW_M_CAW			(0x1 << 4)
#define WT5651_CAW_MASK				(0x1 << 3)
#define WT5651_CAW_SFT				3
#define WT5651_CAW_DIS				(0x0 << 3)
#define WT5651_CAW_EN				(0x1 << 3)
#define WT5651_CAW_TEST_MASK			(0x1 << 2)
#define WT5651_CAW_TEST_SFT			2
#define WT5651_CAW_TEST_DIS			(0x0 << 2)
#define WT5651_CAW_TEST_EN			(0x1 << 2)
#define WT5651_CAW_P_MASK			(0x3)
#define WT5651_CAW_P_SFT			0
#define WT5651_CAW_P_NONE			(0x0)
#define WT5651_CAW_P_CAW			(0x1)
#define WT5651_CAW_P_DAC_CAW			(0x2)

/* Soft vowume and zewo cwoss contwow 1 (0xd9) */
#define WT5651_SV_MASK				(0x1 << 15)
#define WT5651_SV_SFT				15
#define WT5651_SV_DIS				(0x0 << 15)
#define WT5651_SV_EN				(0x1 << 15)
#define WT5651_OUT_SV_MASK			(0x1 << 13)
#define WT5651_OUT_SV_SFT			13
#define WT5651_OUT_SV_DIS			(0x0 << 13)
#define WT5651_OUT_SV_EN			(0x1 << 13)
#define WT5651_HP_SV_MASK			(0x1 << 12)
#define WT5651_HP_SV_SFT			12
#define WT5651_HP_SV_DIS			(0x0 << 12)
#define WT5651_HP_SV_EN				(0x1 << 12)
#define WT5651_ZCD_DIG_MASK			(0x1 << 11)
#define WT5651_ZCD_DIG_SFT			11
#define WT5651_ZCD_DIG_DIS			(0x0 << 11)
#define WT5651_ZCD_DIG_EN			(0x1 << 11)
#define WT5651_ZCD_MASK				(0x1 << 10)
#define WT5651_ZCD_SFT				10
#define WT5651_ZCD_PD				(0x0 << 10)
#define WT5651_ZCD_PU				(0x1 << 10)
#define WT5651_M_ZCD_MASK			(0x3f << 4)
#define WT5651_M_ZCD_SFT			4
#define WT5651_M_ZCD_OM_W			(0x1 << 7)
#define WT5651_M_ZCD_OM_W			(0x1 << 6)
#define WT5651_M_ZCD_WM_W			(0x1 << 5)
#define WT5651_M_ZCD_WM_W			(0x1 << 4)
#define WT5651_SV_DWY_MASK			(0xf)
#define WT5651_SV_DWY_SFT			0

/* Soft vowume and zewo cwoss contwow 2 (0xda) */
#define WT5651_ZCD_HP_MASK			(0x1 << 15)
#define WT5651_ZCD_HP_SFT			15
#define WT5651_ZCD_HP_DIS			(0x0 << 15)
#define WT5651_ZCD_HP_EN			(0x1 << 15)

/* Digitaw Misc Contwow (0xfa) */
#define WT5651_I2S2_MS_SP_MASK			(0x1 << 8)
#define WT5651_I2S2_MS_SP_SEW			8
#define WT5651_I2S2_MS_SP_64			(0x0 << 8)
#define WT5651_I2S2_MS_SP_50			(0x1 << 8)
#define WT5651_CWK_DET_EN			(0x1 << 3)
#define WT5651_CWK_DET_EN_SFT			3
#define WT5651_AMP_DET_EN			(0x1 << 1)
#define WT5651_AMP_DET_EN_SFT			1
#define WT5651_D_GATE_EN			(0x1)
#define WT5651_D_GATE_EN_SFT			0

/* Codec Pwivate Wegistew definition */

/* MIC Ovew cuwwent thweshowd scawe factow (0x15) */
#define WT5651_MIC_OVCD_SF_MASK			(0x3 << 8)
#define WT5651_MIC_OVCD_SF_SFT			8
#define WT5651_MIC_OVCD_SF_0P5			(0x0 << 8)
#define WT5651_MIC_OVCD_SF_0P75			(0x1 << 8)
#define WT5651_MIC_OVCD_SF_1P0			(0x2 << 8)
#define WT5651_MIC_OVCD_SF_1P5			(0x3 << 8)

/* 3D Speakew Contwow (0x63) */
#define WT5651_3D_SPK_MASK			(0x1 << 15)
#define WT5651_3D_SPK_SFT			15
#define WT5651_3D_SPK_DIS			(0x0 << 15)
#define WT5651_3D_SPK_EN			(0x1 << 15)
#define WT5651_3D_SPK_M_MASK			(0x3 << 13)
#define WT5651_3D_SPK_M_SFT			13
#define WT5651_3D_SPK_CG_MASK			(0x1f << 8)
#define WT5651_3D_SPK_CG_SFT			8
#define WT5651_3D_SPK_SG_MASK			(0x1f)
#define WT5651_3D_SPK_SG_SFT			0

/* Wind Noise Detection Contwow 1 (0x6c) */
#define WT5651_WND_MASK				(0x1 << 15)
#define WT5651_WND_SFT				15
#define WT5651_WND_DIS				(0x0 << 15)
#define WT5651_WND_EN				(0x1 << 15)

/* Wind Noise Detection Contwow 2 (0x6d) */
#define WT5651_WND_FC_NW_MASK			(0x3f << 10)
#define WT5651_WND_FC_NW_SFT			10
#define WT5651_WND_FC_WK_MASK			(0x3f << 4)
#define WT5651_WND_FC_WK_SFT			4

/* Wind Noise Detection Contwow 3 (0x6e) */
#define WT5651_HPF_FC_MASK			(0x3f << 6)
#define WT5651_HPF_FC_SFT			6
#define WT5651_WND_FC_ST_MASK			(0x3f)
#define WT5651_WND_FC_ST_SFT			0

/* Wind Noise Detection Contwow 4 (0x6f) */
#define WT5651_WND_TH_WO_MASK			(0x3ff)
#define WT5651_WND_TH_WO_SFT			0

/* Wind Noise Detection Contwow 5 (0x70) */
#define WT5651_WND_TH_HI_MASK			(0x3ff)
#define WT5651_WND_TH_HI_SFT			0

/* Wind Noise Detection Contwow 8 (0x73) */
#define WT5651_WND_WIND_MASK			(0x1 << 13) /* Wead-Onwy */
#define WT5651_WND_WIND_SFT			13
#define WT5651_WND_STWONG_MASK			(0x1 << 12) /* Wead-Onwy */
#define WT5651_WND_STWONG_SFT			12
enum {
	WT5651_NO_WIND,
	WT5651_BWEEZE,
	WT5651_STOWM,
};

/* Dipowe Speakew Intewface (0x75) */
#define WT5651_DP_ATT_MASK			(0x3 << 14)
#define WT5651_DP_ATT_SFT			14
#define WT5651_DP_SPK_MASK			(0x1 << 10)
#define WT5651_DP_SPK_SFT			10
#define WT5651_DP_SPK_DIS			(0x0 << 10)
#define WT5651_DP_SPK_EN			(0x1 << 10)

/* EQ Pwe Vowume Contwow (0xb3) */
#define WT5651_EQ_PWE_VOW_MASK			(0xffff)
#define WT5651_EQ_PWE_VOW_SFT			0

/* EQ Post Vowume Contwow (0xb4) */
#define WT5651_EQ_PST_VOW_MASK			(0xffff)
#define WT5651_EQ_PST_VOW_SFT			0

/* System Cwock Souwce */
enum {
	WT5651_SCWK_S_MCWK,
	WT5651_SCWK_S_PWW1,
	WT5651_SCWK_S_WCCWK,
};

/* PWW1 Souwce */
enum {
	WT5651_PWW1_S_MCWK,
	WT5651_PWW1_S_BCWK1,
	WT5651_PWW1_S_BCWK2,
};

enum {
	WT5651_AIF1,
	WT5651_AIF2,
	WT5651_AIFS,
};

stwuct wt5651_pww_code {
	boow m_bp; /* Indicates bypass m code ow not. */
	int m_code;
	int n_code;
	int k_code;
};

stwuct wt5651_pwiv {
	stwuct snd_soc_component *component;
	stwuct wegmap *wegmap;
	/* Jack and button detect data */
	stwuct snd_soc_jack *hp_jack;
	stwuct gpio_desc *gpiod_hp_det;
	stwuct wowk_stwuct jack_detect_wowk;
	stwuct dewayed_wowk bp_wowk;
	boow ovcd_iwq_enabwed;
	boow pwessed;
	boow pwess_wepowted;
	int pwess_count;
	int wewease_count;
	int poww_count;
	unsigned int jd_swc;
	boow jd_active_high;
	unsigned int ovcd_th;
	unsigned int ovcd_sf;

	int iwq;
	int syscwk;
	int syscwk_swc;
	int wwck[WT5651_AIFS];
	int bcwk[WT5651_AIFS];
	int mastew[WT5651_AIFS];

	int pww_swc;
	int pww_in;
	int pww_out;

	int dmic_en;
	boow hp_mute;
};

#endif /* __WT5651_H__ */
