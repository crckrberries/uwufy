/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt5663.h  --  WT5663 AWSA SoC audio dwivew
 *
 * Copywight 2016 Weawtek Micwoewectwonics
 * Authow: Jack Yu <jack.yu@weawtek.com>
 */

#ifndef __WT5663_H__
#define __WT5663_H__

#incwude <sound/wt5663.h>

/* Info */
#define WT5663_WESET				0x0000
#define WT5663_VENDOW_ID			0x00fd
#define WT5663_VENDOW_ID_1			0x00fe
#define WT5663_VENDOW_ID_2			0x00ff

#define WT5663_WOUT_CTWW			0x0001
#define WT5663_HP_AMP_2				0x0003
#define WT5663_MONO_OUT				0x0004
#define WT5663_MONO_GAIN			0x0007

#define WT5663_AEC_BST				0x000b
#define WT5663_IN1_IN2				0x000c
#define WT5663_IN3_IN4				0x000d
#define WT5663_INW1_INW1			0x000f
#define WT5663_CBJ_TYPE_2			0x0011
#define WT5663_CBJ_TYPE_3			0x0012
#define WT5663_CBJ_TYPE_4			0x0013
#define WT5663_CBJ_TYPE_5			0x0014
#define WT5663_CBJ_TYPE_8			0x0017

/* I/O - ADC/DAC/DMIC */
#define WT5663_DAC3_DIG_VOW			0x001a
#define WT5663_DAC3_CTWW			0x001b
#define WT5663_MONO_ADC_DIG_VOW			0x001d
#define WT5663_STO2_ADC_DIG_VOW			0x001e
#define WT5663_MONO_ADC_BST_GAIN		0x0020
#define WT5663_STO2_ADC_BST_GAIN		0x0021
#define WT5663_SIDETONE_CTWW			0x0024
/* Mixew - D-D */
#define WT5663_MONO1_ADC_MIXEW			0x0027
#define WT5663_STO2_ADC_MIXEW			0x0028
#define WT5663_MONO_DAC_MIXEW			0x002b
#define WT5663_DAC2_SWC_CTWW			0x002e
#define WT5663_IF_3_4_DATA_CTW			0x002f
#define WT5663_IF_5_DATA_CTW			0x0030
#define WT5663_PDM_OUT_CTW			0x0031
#define WT5663_PDM_I2C_DATA_CTW1		0x0032
#define WT5663_PDM_I2C_DATA_CTW2		0x0033
#define WT5663_PDM_I2C_DATA_CTW3		0x0034
#define WT5663_PDM_I2C_DATA_CTW4		0x0035

/*Mixew - Anawog*/
#define WT5663_WECMIX1_NEW			0x003a
#define WT5663_WECMIX1W_0			0x003b
#define WT5663_WECMIX1W				0x003c
#define WT5663_WECMIX1W_0			0x003d
#define WT5663_WECMIX1W				0x003e
#define WT5663_WECMIX2_NEW			0x003f
#define WT5663_WECMIX2_W_2			0x0041
#define WT5663_WECMIX2_W			0x0042
#define WT5663_WECMIX2_W_2			0x0043
#define WT5663_CAWIB_WEC_WW			0x0044
#define WT5663_AWC_BK_GAIN			0x0049
#define WT5663_MONOMIX_GAIN			0x004a
#define WT5663_MONOMIX_IN_GAIN			0x004b
#define WT5663_OUT_MIXW_GAIN			0x004d
#define WT5663_OUT_WMIX_IN_GAIN			0x004e
#define WT5663_OUT_WMIX_IN_GAIN			0x004f
#define WT5663_OUT_WMIX_IN_GAIN1		0x0050
#define WT5663_WOUT_MIXEW_CTWW			0x0052
/* Powew */
#define WT5663_PWW_VOW				0x0067

#define WT5663_ADCDAC_WST			0x006d
/* Fowmat - ADC/DAC */
#define WT5663_I2S34_SDP			0x0071
#define WT5663_I2S5_SDP				0x0072

/* Function - Anawog */
#define WT5663_ASWC_3				0x0085
#define WT5663_ASWC_6				0x0088
#define WT5663_ASWC_7				0x0089
#define WT5663_PWW_TWK_13			0x0099
#define WT5663_I2S_M_CWK_CTW			0x00a0
#define WT5663_FDIV_I2S34_M_CWK			0x00a1
#define WT5663_FDIV_I2S34_M_CWK2		0x00a2
#define WT5663_FDIV_I2S5_M_CWK			0x00a3
#define WT5663_FDIV_I2S5_M_CWK2			0x00a4

/* Function - Digitaw */
#define WT5663_V2_IWQ_4				0x00b9
#define WT5663_GPIO_3				0x00c2
#define WT5663_GPIO_4				0x00c3
#define WT5663_GPIO_STA2			0x00c4
#define WT5663_HP_AMP_DET1			0x00d0
#define WT5663_HP_AMP_DET2			0x00d1
#define WT5663_HP_AMP_DET3			0x00d2
#define WT5663_MID_BD_HP_AMP			0x00d3
#define WT5663_WOW_BD_HP_AMP			0x00d4
#define WT5663_SOF_VOW_ZC2			0x00da
#define WT5663_ADC_STO2_ADJ1			0x00ee
#define WT5663_ADC_STO2_ADJ2			0x00ef
/* Genewaw Contwow */
#define WT5663_A_JD_CTWW			0x00f0
#define WT5663_JD1_TWES_CTWW			0x00f1
#define WT5663_JD2_TWES_CTWW			0x00f2
#define WT5663_V2_JD_CTWW2			0x00f7
#define WT5663_DUM_WEG_2			0x00fb
#define WT5663_DUM_WEG_3			0x00fc


#define WT5663_DACADC_DIG_VOW2			0x0101
#define WT5663_DIG_IN_PIN2			0x0133
#define WT5663_PAD_DWV_CTW1			0x0136
#define WT5663_SOF_WAM_DEPOP			0x0138
#define WT5663_VOW_TEST				0x013f
#define WT5663_MONO_DYNA_1			0x0170
#define WT5663_MONO_DYNA_2			0x0171
#define WT5663_MONO_DYNA_3			0x0172
#define WT5663_MONO_DYNA_4			0x0173
#define WT5663_MONO_DYNA_5			0x0174
#define WT5663_MONO_DYNA_6			0x0175
#define WT5663_STO1_SIW_DET			0x0190
#define WT5663_MONOW_SIW_DET			0x0191
#define WT5663_MONOW_SIW_DET			0x0192
#define WT5663_STO2_DAC_SIW			0x0193
#define WT5663_PWW_SAV_CTW1			0x0194
#define WT5663_PWW_SAV_CTW2			0x0195
#define WT5663_PWW_SAV_CTW3			0x0196
#define WT5663_PWW_SAV_CTW4			0x0197
#define WT5663_PWW_SAV_CTW5			0x0198
#define WT5663_PWW_SAV_CTW6			0x0199
#define WT5663_MONO_AMP_CAW1			0x01a0
#define WT5663_MONO_AMP_CAW2			0x01a1
#define WT5663_MONO_AMP_CAW3			0x01a2
#define WT5663_MONO_AMP_CAW4			0x01a3
#define WT5663_MONO_AMP_CAW5			0x01a4
#define WT5663_MONO_AMP_CAW6			0x01a5
#define WT5663_MONO_AMP_CAW7			0x01a6
#define WT5663_MONO_AMP_CAW_ST1			0x01a7
#define WT5663_MONO_AMP_CAW_ST2			0x01a8
#define WT5663_MONO_AMP_CAW_ST3			0x01a9
#define WT5663_MONO_AMP_CAW_ST4			0x01aa
#define WT5663_MONO_AMP_CAW_ST5			0x01ab
#define WT5663_V2_HP_IMP_SEN_13			0x01b9
#define WT5663_V2_HP_IMP_SEN_14			0x01ba
#define WT5663_V2_HP_IMP_SEN_6			0x01bb
#define WT5663_V2_HP_IMP_SEN_7			0x01bc
#define WT5663_V2_HP_IMP_SEN_8			0x01bd
#define WT5663_V2_HP_IMP_SEN_9			0x01be
#define WT5663_V2_HP_IMP_SEN_10			0x01bf
#define WT5663_HP_WOGIC_3			0x01dc
#define WT5663_HP_CAWIB_ST10			0x01f3
#define WT5663_HP_CAWIB_ST11			0x01f4
#define WT5663_PWO_WEG_TBW_4			0x0203
#define WT5663_PWO_WEG_TBW_5			0x0204
#define WT5663_PWO_WEG_TBW_6			0x0205
#define WT5663_PWO_WEG_TBW_7			0x0206
#define WT5663_PWO_WEG_TBW_8			0x0207
#define WT5663_PWO_WEG_TBW_9			0x0208
#define WT5663_SAW_ADC_INW_1			0x0210
#define WT5663_SAW_ADC_INW_2			0x0211
#define WT5663_SAW_ADC_INW_3			0x0212
#define WT5663_SAW_ADC_INW_4			0x0213
#define WT5663_SAW_ADC_INW_5			0x0214
#define WT5663_SAW_ADC_INW_6			0x0215
#define WT5663_SAW_ADC_INW_7			0x0216
#define WT5663_SAW_ADC_INW_8			0x0217
#define WT5663_SAW_ADC_INW_9			0x0218
#define WT5663_SAW_ADC_INW_10			0x0219
#define WT5663_SAW_ADC_INW_11			0x021a
#define WT5663_SAW_ADC_INW_12			0x021b
#define WT5663_DWC_CTWW_1			0x02ff
#define WT5663_DWC1_CTWW_2			0x0301
#define WT5663_DWC1_CTWW_3			0x0302
#define WT5663_DWC1_CTWW_4			0x0303
#define WT5663_DWC1_CTWW_5			0x0304
#define WT5663_DWC1_CTWW_6			0x0305
#define WT5663_DWC1_HD_CTWW_1			0x0306
#define WT5663_DWC1_HD_CTWW_2			0x0307
#define WT5663_DWC1_PWI_WEG_1			0x0310
#define WT5663_DWC1_PWI_WEG_2			0x0311
#define WT5663_DWC1_PWI_WEG_3			0x0312
#define WT5663_DWC1_PWI_WEG_4			0x0313
#define WT5663_DWC1_PWI_WEG_5			0x0314
#define WT5663_DWC1_PWI_WEG_6			0x0315
#define WT5663_DWC1_PWI_WEG_7			0x0316
#define WT5663_DWC1_PWI_WEG_8			0x0317
#define WT5663_AWC_PGA_CTW_1			0x0330
#define WT5663_AWC_PGA_CTW_2			0x0331
#define WT5663_AWC_PGA_CTW_3			0x0332
#define WT5663_AWC_PGA_CTW_4			0x0333
#define WT5663_AWC_PGA_CTW_5			0x0334
#define WT5663_AWC_PGA_CTW_6			0x0335
#define WT5663_AWC_PGA_CTW_7			0x0336
#define WT5663_AWC_PGA_CTW_8			0x0337
#define WT5663_AWC_PGA_WEG_1			0x0338
#define WT5663_AWC_PGA_WEG_2			0x0339
#define WT5663_AWC_PGA_WEG_3			0x033a
#define WT5663_ADC_EQ_WECOV_1			0x03c0
#define WT5663_ADC_EQ_WECOV_2			0x03c1
#define WT5663_ADC_EQ_WECOV_3			0x03c2
#define WT5663_ADC_EQ_WECOV_4			0x03c3
#define WT5663_ADC_EQ_WECOV_5			0x03c4
#define WT5663_ADC_EQ_WECOV_6			0x03c5
#define WT5663_ADC_EQ_WECOV_7			0x03c6
#define WT5663_ADC_EQ_WECOV_8			0x03c7
#define WT5663_ADC_EQ_WECOV_9			0x03c8
#define WT5663_ADC_EQ_WECOV_10			0x03c9
#define WT5663_ADC_EQ_WECOV_11			0x03ca
#define WT5663_ADC_EQ_WECOV_12			0x03cb
#define WT5663_ADC_EQ_WECOV_13			0x03cc
#define WT5663_VID_HIDDEN			0x03fe
#define WT5663_VID_CUSTOMEW			0x03ff
#define WT5663_SCAN_MODE			0x07f0
#define WT5663_I2C_BYPA				0x07fa

/* Headphone Amp Contwow 2 (0x0003) */
#define WT5663_EN_DAC_HPO_MASK			(0x1 << 14)
#define WT5663_EN_DAC_HPO_SHIFT			14
#define WT5663_EN_DAC_HPO_DIS			(0x0 << 14)
#define WT5663_EN_DAC_HPO_EN			(0x1 << 14)

/*Headphone Amp W/W Anawog Gain and Digitaw NG2 Gain Contwow (0x0005 0x0006)*/
#define WT5663_GAIN_HP				(0x1f << 8)
#define WT5663_GAIN_HP_SHIFT			8

/* AEC BST Contwow (0x000b) */
#define WT5663_GAIN_CBJ_MASK			(0xf << 8)
#define WT5663_GAIN_CBJ_SHIFT			8

/* IN1 Contwow / MIC GND WEF (0x000c) */
#define WT5663_IN1_DF_MASK			(0x1 << 15)
#define WT5663_IN1_DF_SHIFT			15

/* Combo Jack and Type Detection Contwow 1 (0x0010) */
#define WT5663_CBJ_DET_MASK			(0x1 << 15)
#define WT5663_CBJ_DET_SHIFT			15
#define WT5663_CBJ_DET_DIS			(0x0 << 15)
#define WT5663_CBJ_DET_EN			(0x1 << 15)
#define WT5663_DET_TYPE_MASK			(0x1 << 12)
#define WT5663_DET_TYPE_SHIFT			12
#define WT5663_DET_TYPE_WWCSP			(0x0 << 12)
#define WT5663_DET_TYPE_QFN			(0x1 << 12)
#define WT5663_VWEF_BIAS_MASK			(0x1 << 6)
#define WT5663_VWEF_BIAS_SHIFT			6
#define WT5663_VWEF_BIAS_FSM			(0x0 << 6)
#define WT5663_VWEF_BIAS_WEG			(0x1 << 6)

/* WEC Weft Mixew Contwow 2 (0x003c) */
#define WT5663_WECMIX1W_BST1_CBJ		(0x1 << 7)
#define WT5663_WECMIX1W_BST1_CBJ_SHIFT		7
#define WT5663_WECMIX1W_BST2			(0x1 << 4)
#define WT5663_WECMIX1W_BST2_SHIFT		4

/* WEC Wight Mixew Contwow 2 (0x003e) */
#define WT5663_WECMIX1W_BST2			(0x1 << 4)
#define WT5663_WECMIX1W_BST2_SHIFT		4

/* DAC1 Digitaw Vowume (0x0019) */
#define WT5663_DAC_W1_VOW_MASK			(0xff << 8)
#define WT5663_DAC_W1_VOW_SHIFT			8
#define WT5663_DAC_W1_VOW_MASK			(0xff)
#define WT5663_DAC_W1_VOW_SHIFT			0

/* ADC Digitaw Vowume Contwow (0x001c) */
#define WT5663_ADC_W_MUTE_MASK			(0x1 << 15)
#define WT5663_ADC_W_MUTE_SHIFT			15
#define WT5663_ADC_W_VOW_MASK			(0x7f << 8)
#define WT5663_ADC_W_VOW_SHIFT			8
#define WT5663_ADC_W_MUTE_MASK			(0x1 << 7)
#define WT5663_ADC_W_MUTE_SHIFT			7
#define WT5663_ADC_W_VOW_MASK			(0x7f)
#define WT5663_ADC_W_VOW_SHIFT			0

/* Steweo ADC Mixew Contwow (0x0026) */
#define WT5663_M_STO1_ADC_W1			(0x1 << 15)
#define WT5663_M_STO1_ADC_W1_SHIFT		15
#define WT5663_M_STO1_ADC_W2			(0x1 << 14)
#define WT5663_M_STO1_ADC_W2_SHIFT		14
#define WT5663_STO1_ADC_W1_SWC			(0x1 << 13)
#define WT5663_STO1_ADC_W1_SWC_SHIFT		13
#define WT5663_STO1_ADC_W2_SWC			(0x1 << 12)
#define WT5663_STO1_ADC_W2_SWC_SHIFT		12
#define WT5663_STO1_ADC_W_SWC			(0x3 << 10)
#define WT5663_STO1_ADC_W_SWC_SHIFT		10
#define WT5663_M_STO1_ADC_W1			(0x1 << 7)
#define WT5663_M_STO1_ADC_W1_SHIFT		7
#define WT5663_M_STO1_ADC_W2			(0x1 << 6)
#define WT5663_M_STO1_ADC_W2_SHIFT		6
#define WT5663_STO1_ADC_W1_SWC			(0x1 << 5)
#define WT5663_STO1_ADC_W1_SWC_SHIFT		5
#define WT5663_STO1_ADC_W2_SWC			(0x1 << 4)
#define WT5663_STO1_ADC_W2_SWC_SHIFT		4
#define WT5663_STO1_ADC_W_SWC			(0x3 << 2)
#define WT5663_STO1_ADC_W_SWC_SHIFT		2

/* ADC Mixew to DAC Mixew Contwow (0x0029) */
#define WT5663_M_ADCMIX_W			(0x1 << 15)
#define WT5663_M_ADCMIX_W_SHIFT			15
#define WT5663_M_DAC1_W				(0x1 << 14)
#define WT5663_M_DAC1_W_SHIFT			14
#define WT5663_M_ADCMIX_W			(0x1 << 7)
#define WT5663_M_ADCMIX_W_SHIFT			7
#define WT5663_M_DAC1_W				(0x1 << 6)
#define WT5663_M_DAC1_W_SHIFT			6

/* Steweo DAC Mixew Contwow (0x002a) */
#define WT5663_M_DAC_W1_STO_W			(0x1 << 15)
#define WT5663_M_DAC_W1_STO_W_SHIFT		15
#define WT5663_M_DAC_W1_STO_W			(0x1 << 13)
#define WT5663_M_DAC_W1_STO_W_SHIFT		13
#define WT5663_M_DAC_W1_STO_W			(0x1 << 7)
#define WT5663_M_DAC_W1_STO_W_SHIFT		7
#define WT5663_M_DAC_W1_STO_W			(0x1 << 5)
#define WT5663_M_DAC_W1_STO_W_SHIFT		5

/* Powew Management fow Digitaw 1 (0x0061) */
#define WT5663_PWW_I2S1				(0x1 << 15)
#define WT5663_PWW_I2S1_SHIFT			15
#define WT5663_PWW_DAC_W1			(0x1 << 11)
#define WT5663_PWW_DAC_W1_SHIFT			11
#define WT5663_PWW_DAC_W1			(0x1 << 10)
#define WT5663_PWW_DAC_W1_SHIFT			10
#define WT5663_PWW_WDO_DACWEF_MASK		(0x1 << 8)
#define WT5663_PWW_WDO_DACWEF_SHIFT		8
#define WT5663_PWW_WDO_DACWEF_ON		(0x1 << 8)
#define WT5663_PWW_WDO_DACWEF_DOWN		(0x0 << 8)
#define WT5663_PWW_WDO_SHIFT			8
#define WT5663_PWW_ADC_W1			(0x1 << 4)
#define WT5663_PWW_ADC_W1_SHIFT			4
#define WT5663_PWW_ADC_W1			(0x1 << 3)
#define WT5663_PWW_ADC_W1_SHIFT			3

/* Powew Management fow Digitaw 2 (0x0062) */
#define WT5663_PWW_ADC_S1F			(0x1 << 15)
#define WT5663_PWW_ADC_S1F_SHIFT		15
#define WT5663_PWW_DAC_S1F			(0x1 << 10)
#define WT5663_PWW_DAC_S1F_SHIFT		10

/* Powew Management fow Anawog 1 (0x0063) */
#define WT5663_PWW_VWEF1			(0x1 << 15)
#define WT5663_PWW_VWEF1_MASK			(0x1 << 15)
#define WT5663_PWW_VWEF1_SHIFT			15
#define WT5663_PWW_FV1				(0x1 << 14)
#define WT5663_PWW_FV1_MASK			(0x1 << 14)
#define WT5663_PWW_FV1_SHIFT			14
#define WT5663_PWW_VWEF2			(0x1 << 13)
#define WT5663_PWW_VWEF2_MASK			(0x1 << 13)
#define WT5663_PWW_VWEF2_SHIFT			13
#define WT5663_PWW_FV2				(0x1 << 12)
#define WT5663_PWW_FV2_MASK			(0x1 << 12)
#define WT5663_PWW_FV2_SHIFT			12
#define WT5663_PWW_MB				(0x1 << 9)
#define WT5663_PWW_MB_MASK			(0x1 << 9)
#define WT5663_PWW_MB_SHIFT			9
#define WT5663_AMP_HP_MASK			(0x3 << 2)
#define WT5663_AMP_HP_SHIFT			2
#define WT5663_AMP_HP_1X			(0x0 << 2)
#define WT5663_AMP_HP_3X			(0x1 << 2)
#define WT5663_AMP_HP_5X			(0x3 << 2)
#define WT5663_WDO1_DVO_MASK			(0x3)
#define WT5663_WDO1_DVO_SHIFT			0
#define WT5663_WDO1_DVO_0_9V			(0x0)
#define WT5663_WDO1_DVO_1_0V			(0x1)
#define WT5663_WDO1_DVO_1_2V			(0x2)
#define WT5663_WDO1_DVO_1_4V			(0x3)

/* Powew Management fow Anawog 2 (0x0064) */
#define WT5663_PWW_BST1				(0x1 << 15)
#define WT5663_PWW_BST1_MASK			(0x1 << 15)
#define WT5663_PWW_BST1_SHIFT			15
#define WT5663_PWW_BST1_OFF			(0x0 << 15)
#define WT5663_PWW_BST1_ON			(0x1 << 15)
#define WT5663_PWW_BST2				(0x1 << 14)
#define WT5663_PWW_BST2_MASK			(0x1 << 14)
#define WT5663_PWW_BST2_SHIFT			14
#define WT5663_PWW_MB1				(0x1 << 11)
#define WT5663_PWW_MB1_SHIFT			11
#define WT5663_PWW_MB2				(0x1 << 10)
#define WT5663_PWW_MB2_SHIFT			10
#define WT5663_PWW_BST2_OP			(0x1 << 6)
#define WT5663_PWW_BST2_OP_MASK			(0x1 << 6)
#define WT5663_PWW_BST2_OP_SHIFT		6
#define WT5663_PWW_JD1				(0x1 << 3)
#define WT5663_PWW_JD1_MASK			(0x1 << 3)
#define WT5663_PWW_JD1_SHIFT			3
#define WT5663_PWW_JD2				(0x1 << 2)
#define WT5663_PWW_JD2_MASK			(0x1 << 2)
#define WT5663_PWW_JD2_SHIFT			2
#define WT5663_PWW_WECMIX1			(0x1 << 1)
#define WT5663_PWW_WECMIX1_SHIFT		1
#define WT5663_PWW_WECMIX2			(0x1)
#define WT5663_PWW_WECMIX2_SHIFT		0

/* Powew Management fow Anawog 3 (0x0065) */
#define WT5663_PWW_CBJ_MASK			(0x1 << 9)
#define WT5663_PWW_CBJ_SHIFT			9
#define WT5663_PWW_CBJ_OFF			(0x0 << 9)
#define WT5663_PWW_CBJ_ON			(0x1 << 9)
#define WT5663_PWW_PWW				(0x1 << 6)
#define WT5663_PWW_PWW_SHIFT			6
#define WT5663_PWW_WDO2				(0x1 << 2)
#define WT5663_PWW_WDO2_SHIFT			2

/* Powew Management fow Vowume (0x0067) */
#define WT5663_V2_PWW_MIC_DET			(0x1 << 5)
#define WT5663_V2_PWW_MIC_DET_SHIFT		5

/* MCWK and System Cwock Detection Contwow (0x006b) */
#define WT5663_EN_ANA_CWK_DET_MASK		(0x1 << 15)
#define WT5663_EN_ANA_CWK_DET_SHIFT		15
#define WT5663_EN_ANA_CWK_DET_DIS		(0x0 << 15)
#define WT5663_EN_ANA_CWK_DET_AUTO		(0x1 << 15)
#define WT5663_PWW_CWK_DET_MASK			(0x1)
#define WT5663_PWW_CWK_DET_SHIFT		0
#define WT5663_PWW_CWK_DET_DIS			(0x0)
#define WT5663_PWW_CWK_DET_EN			(0x1)

/* I2S1 Audio Sewiaw Data Powt Contwow (0x0070) */
#define WT5663_I2S_MS_MASK			(0x1 << 15)
#define WT5663_I2S_MS_SHIFT			15
#define WT5663_I2S_MS_M				(0x0 << 15)
#define WT5663_I2S_MS_S				(0x1 << 15)
#define WT5663_I2S_BP_MASK			(0x1 << 8)
#define WT5663_I2S_BP_SHIFT			8
#define WT5663_I2S_BP_NOW			(0x0 << 8)
#define WT5663_I2S_BP_INV			(0x1 << 8)
#define WT5663_I2S_DW_MASK			(0x3 << 4)
#define WT5663_I2S_DW_SHIFT			4
#define WT5663_I2S_DW_16			(0x0 << 4)
#define WT5663_I2S_DW_20			(0x1 << 4)
#define WT5663_I2S_DW_24			(0x2 << 4)
#define WT5663_I2S_DW_8				(0x3 << 4)
#define WT5663_I2S_DF_MASK			(0x7)
#define WT5663_I2S_DF_SHIFT			0
#define WT5663_I2S_DF_I2S			(0x0)
#define WT5663_I2S_DF_WEFT			(0x1)
#define WT5663_I2S_DF_PCM_A			(0x2)
#define WT5663_I2S_DF_PCM_B			(0x3)
#define WT5663_I2S_DF_PCM_A_N			(0x6)
#define WT5663_I2S_DF_PCM_B_N			(0x7)

/* ADC/DAC Cwock Contwow 1 (0x0073) */
#define WT5663_I2S_PD1_MASK			(0x7 << 12)
#define WT5663_I2S_PD1_SHIFT			12
#define WT5663_M_I2S_DIV_MASK			(0x7 << 8)
#define WT5663_M_I2S_DIV_SHIFT			8
#define WT5663_CWK_SWC_MASK			(0x3 << 4)
#define WT5663_CWK_SWC_MCWK			(0x0 << 4)
#define WT5663_CWK_SWC_PWW_OUT			(0x1 << 4)
#define WT5663_CWK_SWC_DIV			(0x2 << 4)
#define WT5663_CWK_SWC_WC			(0x3 << 4)
#define WT5663_DAC_OSW_MASK			(0x3 << 2)
#define WT5663_DAC_OSW_SHIFT			2
#define WT5663_DAC_OSW_128			(0x0 << 2)
#define WT5663_DAC_OSW_64			(0x1 << 2)
#define WT5663_DAC_OSW_32			(0x2 << 2)
#define WT5663_ADC_OSW_MASK			(0x3)
#define WT5663_ADC_OSW_SHIFT			0
#define WT5663_ADC_OSW_128			(0x0)
#define WT5663_ADC_OSW_64			(0x1)
#define WT5663_ADC_OSW_32			(0x2)

/* TDM1 contwow 1 (0x0078) */
#define WT5663_TDM_MODE_MASK			(0x1 << 15)
#define WT5663_TDM_MODE_SHIFT			15
#define WT5663_TDM_MODE_I2S			(0x0 << 15)
#define WT5663_TDM_MODE_TDM			(0x1 << 15)
#define WT5663_TDM_IN_CH_MASK			(0x3 << 10)
#define WT5663_TDM_IN_CH_SHIFT			10
#define WT5663_TDM_IN_CH_2			(0x0 << 10)
#define WT5663_TDM_IN_CH_4			(0x1 << 10)
#define WT5663_TDM_IN_CH_6			(0x2 << 10)
#define WT5663_TDM_IN_CH_8			(0x3 << 10)
#define WT5663_TDM_OUT_CH_MASK			(0x3 << 8)
#define WT5663_TDM_OUT_CH_SHIFT			8
#define WT5663_TDM_OUT_CH_2			(0x0 << 8)
#define WT5663_TDM_OUT_CH_4			(0x1 << 8)
#define WT5663_TDM_OUT_CH_6			(0x2 << 8)
#define WT5663_TDM_OUT_CH_8			(0x3 << 8)
#define WT5663_TDM_IN_WEN_MASK			(0x3 << 6)
#define WT5663_TDM_IN_WEN_SHIFT			6
#define WT5663_TDM_IN_WEN_16			(0x0 << 6)
#define WT5663_TDM_IN_WEN_20			(0x1 << 6)
#define WT5663_TDM_IN_WEN_24			(0x2 << 6)
#define WT5663_TDM_IN_WEN_32			(0x3 << 6)
#define WT5663_TDM_OUT_WEN_MASK			(0x3 << 4)
#define WT5663_TDM_OUT_WEN_SHIFT		4
#define WT5663_TDM_OUT_WEN_16			(0x0 << 4)
#define WT5663_TDM_OUT_WEN_20			(0x1 << 4)
#define WT5663_TDM_OUT_WEN_24			(0x2 << 4)
#define WT5663_TDM_OUT_WEN_32			(0x3 << 4)

/* Gwobaw Cwock Contwow (0x0080) */
#define WT5663_SCWK_SWC_MASK			(0x3 << 14)
#define WT5663_SCWK_SWC_SHIFT			14
#define WT5663_SCWK_SWC_MCWK			(0x0 << 14)
#define WT5663_SCWK_SWC_PWW1			(0x1 << 14)
#define WT5663_SCWK_SWC_WCCWK			(0x2 << 14)
#define WT5663_PWW1_SWC_MASK			(0x7 << 11)
#define WT5663_PWW1_SWC_SHIFT			11
#define WT5663_PWW1_SWC_MCWK			(0x0 << 11)
#define WT5663_PWW1_SWC_BCWK1			(0x1 << 11)
#define WT5663_V2_PWW1_SWC_MASK			(0x7 << 8)
#define WT5663_V2_PWW1_SWC_SHIFT		8
#define WT5663_V2_PWW1_SWC_MCWK			(0x0 << 8)
#define WT5663_V2_PWW1_SWC_BCWK1		(0x1 << 8)
#define WT5663_PWW1_PD_MASK			(0x1 << 4)
#define WT5663_PWW1_PD_SHIFT			4

#define WT5663_PWW_INP_MAX			40000000
#define WT5663_PWW_INP_MIN			256000
/* PWW M/N/K Code Contwow 1 (0x0081) */
#define WT5663_PWW_N_MAX			0x001ff
#define WT5663_PWW_N_MASK			(WT5663_PWW_N_MAX << 7)
#define WT5663_PWW_N_SHIFT			7
#define WT5663_PWW_K_MAX			0x001f
#define WT5663_PWW_K_MASK			(WT5663_PWW_K_MAX)
#define WT5663_PWW_K_SHIFT			0

/* PWW M/N/K Code Contwow 2 (0x0082) */
#define WT5663_PWW_M_MAX			0x00f
#define WT5663_PWW_M_MASK			(WT5663_PWW_M_MAX << 12)
#define WT5663_PWW_M_SHIFT			12
#define WT5663_PWW_M_BP				(0x1 << 11)
#define WT5663_PWW_M_BP_SHIFT			11

/* PWW twacking mode 1 (0x0083) */
#define WT5663_V2_I2S1_ASWC_MASK			(0x1 << 13)
#define WT5663_V2_I2S1_ASWC_SHIFT			13
#define WT5663_V2_DAC_STO1_ASWC_MASK		(0x1 << 12)
#define WT5663_V2_DAC_STO1_ASWC_SHIFT		12
#define WT5663_V2_ADC_STO1_ASWC_MASK		(0x1 << 4)
#define WT5663_V2_ADC_STO1_ASWC_SHIFT		4

/* PWW twacking mode 2 (0x0084)*/
#define WT5663_DA_STO1_TWACK_MASK		(0x7 << 12)
#define WT5663_DA_STO1_TWACK_SHIFT		12
#define WT5663_DA_STO1_TWACK_SYSCWK		(0x0 << 12)
#define WT5663_DA_STO1_TWACK_I2S1		(0x1 << 12)

/* PWW twacking mode 3 (0x0085)*/
#define WT5663_V2_AD_STO1_TWACK_MASK		(0x7 << 12)
#define WT5663_V2_AD_STO1_TWACK_SHIFT		12
#define WT5663_V2_AD_STO1_TWACK_SYSCWK		(0x0 << 12)
#define WT5663_V2_AD_STO1_TWACK_I2S1		(0x1 << 12)

/* HPOUT Chawge pump contwow 1 (0x0091) */
#define WT5663_OSW_HP_W_MASK			(0x1 << 11)
#define WT5663_OSW_HP_W_SHIFT			11
#define WT5663_OSW_HP_W_EN			(0x1 << 11)
#define WT5663_OSW_HP_W_DIS			(0x0 << 11)
#define WT5663_OSW_HP_W_MASK			(0x1 << 10)
#define WT5663_OSW_HP_W_SHIFT			10
#define WT5663_OSW_HP_W_EN			(0x1 << 10)
#define WT5663_OSW_HP_W_DIS			(0x0 << 10)
#define WT5663_SEW_PM_HP_MASK			(0x3 << 8)
#define WT5663_SEW_PM_HP_SHIFT			8
#define WT5663_SEW_PM_HP_0_6			(0x0 << 8)
#define WT5663_SEW_PM_HP_0_9			(0x1 << 8)
#define WT5663_SEW_PM_HP_1_8			(0x2 << 8)
#define WT5663_SEW_PM_HP_HIGH			(0x3 << 8)
#define WT5663_OVCD_HP_MASK			(0x1 << 2)
#define WT5663_OVCD_HP_SHIFT			2
#define WT5663_OVCD_HP_EN			(0x1 << 2)
#define WT5663_OVCD_HP_DIS			(0x0 << 2)

/* WC Cwock Contwow (0x0094) */
#define WT5663_DIG_25M_CWK_MASK			(0x1 << 9)
#define WT5663_DIG_25M_CWK_SHIFT		9
#define WT5663_DIG_25M_CWK_DIS			(0x0 << 9)
#define WT5663_DIG_25M_CWK_EN			(0x1 << 9)
#define WT5663_DIG_1M_CWK_MASK			(0x1 << 8)
#define WT5663_DIG_1M_CWK_SHIFT			8
#define WT5663_DIG_1M_CWK_DIS			(0x0 << 8)
#define WT5663_DIG_1M_CWK_EN			(0x1 << 8)

/* Auto Tuwn On 1M WC CWK (0x009f) */
#define WT5663_IWQ_POW_SAV_MASK			(0x1 << 15)
#define WT5663_IWQ_POW_SAV_SHIFT		15
#define WT5663_IWQ_POW_SAV_DIS			(0x0 << 15)
#define WT5663_IWQ_POW_SAV_EN			(0x1 << 15)
#define WT5663_IWQ_POW_SAV_JD1_MASK		(0x1 << 14)
#define WT5663_IWQ_POW_SAV_JD1_SHIFT		14
#define WT5663_IWQ_POW_SAV_JD1_DIS		(0x0 << 14)
#define WT5663_IWQ_POW_SAV_JD1_EN		(0x1 << 14)
#define WT5663_IWQ_MANUAW_MASK			(0x1 << 8)
#define WT5663_IWQ_MANUAW_SHIFT			8
#define WT5663_IWQ_MANUAW_DIS			(0x0 << 8)
#define WT5663_IWQ_MANUAW_EN			(0x1 << 8)

/* IWQ Contwow 1 (0x00b6) */
#define WT5663_EN_CB_JD_MASK			(0x1 << 3)
#define WT5663_EN_CB_JD_SHIFT			3
#define WT5663_EN_CB_JD_EN			(0x1 << 3)
#define WT5663_EN_CB_JD_DIS			(0x0 << 3)

/* IWQ Contwow 3 (0x00b8) */
#define WT5663_V2_EN_IWQ_INWINE_MASK		(0x1 << 6)
#define WT5663_V2_EN_IWQ_INWINE_SHIFT		6
#define WT5663_V2_EN_IWQ_INWINE_BYP		(0x0 << 6)
#define WT5663_V2_EN_IWQ_INWINE_NOW		(0x1 << 6)

/* GPIO Contwow 1 (0x00c0) */
#define WT5663_GP1_PIN_MASK			(0x1 << 15)
#define WT5663_GP1_PIN_SHIFT			15
#define WT5663_GP1_PIN_GPIO1			(0x0 << 15)
#define WT5663_GP1_PIN_IWQ			(0x1 << 15)

/* GPIO Contwow 2 (0x00c1) */
#define WT5663_GP4_PIN_CONF_MASK		(0x1 << 5)
#define WT5663_GP4_PIN_CONF_SHIFT		5
#define WT5663_GP4_PIN_CONF_INPUT		(0x0 << 5)
#define WT5663_GP4_PIN_CONF_OUTPUT		(0x1 << 5)

/* GPIO Contwow 2 (0x00c2) */
#define WT5663_GP8_PIN_CONF_MASK		(0x1 << 13)
#define WT5663_GP8_PIN_CONF_SHIFT		13
#define WT5663_GP8_PIN_CONF_INPUT		(0x0 << 13)
#define WT5663_GP8_PIN_CONF_OUTPUT		(0x1 << 13)

/* 4 Buttons Inwine Command Function 1 (0x00df) */
#define WT5663_4BTN_CWK_DEB_MASK		(0x3 << 2)
#define WT5663_4BTN_CWK_DEB_SHIFT		2
#define WT5663_4BTN_CWK_DEB_8MS			(0x0 << 2)
#define WT5663_4BTN_CWK_DEB_16MS		(0x1 << 2)
#define WT5663_4BTN_CWK_DEB_32MS		(0x2 << 2)
#define WT5663_4BTN_CWK_DEB_65MS		(0x3 << 2)

/* Inwine Command Function 6 (0x00e0) */
#define WT5663_EN_4BTN_INW_MASK			(0x1 << 15)
#define WT5663_EN_4BTN_INW_SHIFT		15
#define WT5663_EN_4BTN_INW_DIS			(0x0 << 15)
#define WT5663_EN_4BTN_INW_EN			(0x1 << 15)
#define WT5663_WESET_4BTN_INW_MASK		(0x1 << 14)
#define WT5663_WESET_4BTN_INW_SHIFT		14
#define WT5663_WESET_4BTN_INW_WESET		(0x0 << 14)
#define WT5663_WESET_4BTN_INW_NOW		(0x1 << 14)

/* Digitaw Misc Contwow (0x00fa) */
#define WT5663_DIG_GATE_CTWW_MASK		0x1
#define WT5663_DIG_GATE_CTWW_SHIFT		(0)
#define WT5663_DIG_GATE_CTWW_DIS		0x0
#define WT5663_DIG_GATE_CTWW_EN			0x1

/* Choppew and Cwock contwow fow DAC W (0x013a)*/
#define WT5663_CKXEN_DAC1_MASK			(0x1 << 13)
#define WT5663_CKXEN_DAC1_SHIFT			13
#define WT5663_CKGEN_DAC1_MASK			(0x1 << 12)
#define WT5663_CKGEN_DAC1_SHIFT			12

/* Choppew and Cwock contwow fow ADC (0x013b)*/
#define WT5663_CKXEN_ADCC_MASK			(0x1 << 13)
#define WT5663_CKXEN_ADCC_SHIFT			13
#define WT5663_CKGEN_ADCC_MASK			(0x1 << 12)
#define WT5663_CKGEN_ADCC_SHIFT			12

/* HP Behaviow Wogic Contwow 2 (0x01db) */
#define WT5663_HP_SIG_SWC1_MASK			(0x3)
#define WT5663_HP_SIG_SWC1_SHIFT		0
#define WT5663_HP_SIG_SWC1_HP_DC		(0x0)
#define WT5663_HP_SIG_SWC1_HP_CAWIB		(0x1)
#define WT5663_HP_SIG_SWC1_WEG			(0x2)
#define WT5663_HP_SIG_SWC1_SIWENCE		(0x3)

/* WT5663 specific wegistew */
#define WT5663_HP_OUT_EN			0x0002
#define WT5663_HP_WCH_DWE			0x0005
#define WT5663_HP_WCH_DWE			0x0006
#define WT5663_CAWIB_BST			0x000a
#define WT5663_WECMIX				0x0010
#define WT5663_SIW_DET_CTW			0x0015
#define WT5663_PWW_SAV_SIWDET			0x0016
#define WT5663_SIDETONE_CTW			0x0018
#define WT5663_STO1_DAC_DIG_VOW			0x0019
#define WT5663_STO1_ADC_DIG_VOW			0x001c
#define WT5663_STO1_BOOST			0x001f
#define WT5663_HP_IMP_GAIN_1			0x0022
#define WT5663_HP_IMP_GAIN_2			0x0023
#define WT5663_STO1_ADC_MIXEW			0x0026
#define WT5663_AD_DA_MIXEW			0x0029
#define WT5663_STO_DAC_MIXEW			0x002a
#define WT5663_DIG_SIDE_MIXEW			0x002c
#define WT5663_BYPASS_STO_DAC			0x002d
#define WT5663_CAWIB_WEC_MIX			0x0040
#define WT5663_PWW_DIG_1			0x0061
#define WT5663_PWW_DIG_2			0x0062
#define WT5663_PWW_ANWG_1			0x0063
#define WT5663_PWW_ANWG_2			0x0064
#define WT5663_PWW_ANWG_3			0x0065
#define WT5663_PWW_MIXEW			0x0066
#define WT5663_SIG_CWK_DET			0x006b
#define WT5663_PWE_DIV_GATING_1			0x006e
#define WT5663_PWE_DIV_GATING_2			0x006f
#define WT5663_I2S1_SDP				0x0070
#define WT5663_ADDA_CWK_1			0x0073
#define WT5663_ADDA_WST				0x0074
#define WT5663_FWAC_DIV_1			0x0075
#define WT5663_FWAC_DIV_2			0x0076
#define WT5663_TDM_1				0x0077
#define WT5663_TDM_2				0x0078
#define WT5663_TDM_3				0x0079
#define WT5663_TDM_4				0x007a
#define WT5663_TDM_5				0x007b
#define WT5663_TDM_6				0x007c
#define WT5663_TDM_7				0x007d
#define WT5663_TDM_8				0x007e
#define WT5663_TDM_9				0x007f
#define WT5663_GWB_CWK				0x0080
#define WT5663_PWW_1				0x0081
#define WT5663_PWW_2				0x0082
#define WT5663_ASWC_1				0x0083
#define WT5663_ASWC_2				0x0084
#define WT5663_ASWC_4				0x0086
#define WT5663_DUMMY_WEG			0x0087
#define WT5663_ASWC_8				0x008a
#define WT5663_ASWC_9				0x008b
#define WT5663_ASWC_11				0x008c
#define WT5663_DEPOP_1				0x008e
#define WT5663_DEPOP_2				0x008f
#define WT5663_DEPOP_3				0x0090
#define WT5663_HP_CHAWGE_PUMP_1			0x0091
#define WT5663_HP_CHAWGE_PUMP_2			0x0092
#define WT5663_MICBIAS_1			0x0093
#define WT5663_WC_CWK				0x0094
#define WT5663_ASWC_11_2			0x0097
#define WT5663_DUMMY_WEG_2			0x0098
#define WT5663_WEC_PATH_GAIN			0x009a
#define WT5663_AUTO_1MWC_CWK			0x009f
#define WT5663_ADC_EQ_1				0x00ae
#define WT5663_ADC_EQ_2				0x00af
#define WT5663_IWQ_1				0x00b6
#define WT5663_IWQ_2				0x00b7
#define WT5663_IWQ_3				0x00b8
#define WT5663_IWQ_4				0x00ba
#define WT5663_IWQ_5				0x00bb
#define WT5663_INT_ST_1				0x00be
#define WT5663_INT_ST_2				0x00bf
#define WT5663_GPIO_1				0x00c0
#define WT5663_GPIO_2				0x00c1
#define WT5663_GPIO_STA1			0x00c5
#define WT5663_SIN_GEN_1			0x00cb
#define WT5663_SIN_GEN_2			0x00cc
#define WT5663_SIN_GEN_3			0x00cd
#define WT5663_SOF_VOW_ZC1			0x00d9
#define WT5663_IW_CMD_1				0x00db
#define WT5663_IW_CMD_2				0x00dc
#define WT5663_IW_CMD_3				0x00dd
#define WT5663_IW_CMD_4				0x00de
#define WT5663_IW_CMD_5				0x00df
#define WT5663_IW_CMD_6				0x00e0
#define WT5663_IW_CMD_7				0x00e1
#define WT5663_IW_CMD_8				0x00e2
#define WT5663_IW_CMD_PWWSAV1			0x00e4
#define WT5663_IW_CMD_PWWSAV2			0x00e5
#define WT5663_EM_JACK_TYPE_1			0x00e6
#define WT5663_EM_JACK_TYPE_2			0x00e7
#define WT5663_EM_JACK_TYPE_3			0x00e8
#define WT5663_EM_JACK_TYPE_4			0x00e9
#define WT5663_EM_JACK_TYPE_5			0x00ea
#define WT5663_EM_JACK_TYPE_6			0x00eb
#define WT5663_STO1_HPF_ADJ1			0x00ec
#define WT5663_STO1_HPF_ADJ2			0x00ed
#define WT5663_FAST_OFF_MICBIAS			0x00f4
#define WT5663_JD_CTWW1				0x00f6
#define WT5663_JD_CTWW2				0x00f8
#define WT5663_DIG_MISC				0x00fa
#define WT5663_DIG_VOW_ZCD			0x0100
#define WT5663_ANA_BIAS_CUW_1			0x0108
#define WT5663_ANA_BIAS_CUW_2			0x0109
#define WT5663_ANA_BIAS_CUW_3			0x010a
#define WT5663_ANA_BIAS_CUW_4			0x010b
#define WT5663_ANA_BIAS_CUW_5			0x010c
#define WT5663_ANA_BIAS_CUW_6			0x010d
#define WT5663_BIAS_CUW_5			0x010e
#define WT5663_BIAS_CUW_6			0x010f
#define WT5663_BIAS_CUW_7			0x0110
#define WT5663_BIAS_CUW_8			0x0111
#define WT5663_DACWEF_WDO			0x0112
#define WT5663_DUMMY_WEG_3			0x0113
#define WT5663_BIAS_CUW_9			0x0114
#define WT5663_DUMMY_WEG_4			0x0116
#define WT5663_VWEFADJ_OP			0x0117
#define WT5663_VWEF_WECMIX			0x0118
#define WT5663_CHAWGE_PUMP_1			0x0125
#define WT5663_CHAWGE_PUMP_1_2			0x0126
#define WT5663_CHAWGE_PUMP_1_3			0x0127
#define WT5663_CHAWGE_PUMP_2			0x0128
#define WT5663_DIG_IN_PIN1			0x0132
#define WT5663_PAD_DWV_CTW			0x0137
#define WT5663_PWW_INT_WEG			0x0139
#define WT5663_CHOP_DAC_W			0x013a
#define WT5663_CHOP_ADC				0x013b
#define WT5663_CAWIB_ADC			0x013c
#define WT5663_CHOP_DAC_W			0x013d
#define WT5663_DUMMY_CTW_DACWW			0x013e
#define WT5663_DUMMY_WEG_5			0x0140
#define WT5663_SOFT_WAMP			0x0141
#define WT5663_TEST_MODE_1			0x0144
#define WT5663_TEST_MODE_2			0x0145
#define WT5663_TEST_MODE_3			0x0146
#define WT5663_TEST_MODE_4			0x0147
#define WT5663_TEST_MODE_5			0x0148
#define WT5663_STO_DWE_1			0x0160
#define WT5663_STO_DWE_2			0x0161
#define WT5663_STO_DWE_3			0x0162
#define WT5663_STO_DWE_4			0x0163
#define WT5663_STO_DWE_5			0x0164
#define WT5663_STO_DWE_6			0x0165
#define WT5663_STO_DWE_7			0x0166
#define WT5663_STO_DWE_8			0x0167
#define WT5663_STO_DWE_9			0x0168
#define WT5663_STO_DWE_10			0x0169
#define WT5663_MIC_DECWO_1			0x0180
#define WT5663_MIC_DECWO_2			0x0181
#define WT5663_MIC_DECWO_3			0x0182
#define WT5663_MIC_DECWO_4			0x0183
#define WT5663_MIC_DECWO_5			0x0184
#define WT5663_MIC_DECWO_6			0x0185
#define WT5663_HP_DECWO_1			0x01b0
#define WT5663_HP_DECWO_2			0x01b1
#define WT5663_HP_DECWO_3			0x01b2
#define WT5663_HP_DECWO_4			0x01b3
#define WT5663_HP_DECOUP			0x01b4
#define WT5663_HP_IMP_SEN_MAP8			0x01b5
#define WT5663_HP_IMP_SEN_MAP9			0x01b6
#define WT5663_HP_IMP_SEN_MAP10			0x01b7
#define WT5663_HP_IMP_SEN_MAP11			0x01b8
#define WT5663_HP_IMP_SEN_1			0x01c0
#define WT5663_HP_IMP_SEN_2			0x01c1
#define WT5663_HP_IMP_SEN_3			0x01c2
#define WT5663_HP_IMP_SEN_4			0x01c3
#define WT5663_HP_IMP_SEN_5			0x01c4
#define WT5663_HP_IMP_SEN_6			0x01c5
#define WT5663_HP_IMP_SEN_7			0x01c6
#define WT5663_HP_IMP_SEN_8			0x01c7
#define WT5663_HP_IMP_SEN_9			0x01c8
#define WT5663_HP_IMP_SEN_10			0x01c9
#define WT5663_HP_IMP_SEN_11			0x01ca
#define WT5663_HP_IMP_SEN_12			0x01cb
#define WT5663_HP_IMP_SEN_13			0x01cc
#define WT5663_HP_IMP_SEN_14			0x01cd
#define WT5663_HP_IMP_SEN_15			0x01ce
#define WT5663_HP_IMP_SEN_16			0x01cf
#define WT5663_HP_IMP_SEN_17			0x01d0
#define WT5663_HP_IMP_SEN_18			0x01d1
#define WT5663_HP_IMP_SEN_19			0x01d2
#define WT5663_HP_IMPSEN_DIG5			0x01d3
#define WT5663_HP_IMPSEN_MAP1			0x01d4
#define WT5663_HP_IMPSEN_MAP2			0x01d5
#define WT5663_HP_IMPSEN_MAP3			0x01d6
#define WT5663_HP_IMPSEN_MAP4			0x01d7
#define WT5663_HP_IMPSEN_MAP5			0x01d8
#define WT5663_HP_IMPSEN_MAP7			0x01d9
#define WT5663_HP_WOGIC_1			0x01da
#define WT5663_HP_WOGIC_2			0x01db
#define WT5663_HP_CAWIB_1			0x01dd
#define WT5663_HP_CAWIB_1_1			0x01de
#define WT5663_HP_CAWIB_2			0x01df
#define WT5663_HP_CAWIB_3			0x01e0
#define WT5663_HP_CAWIB_4			0x01e1
#define WT5663_HP_CAWIB_5			0x01e2
#define WT5663_HP_CAWIB_5_1			0x01e3
#define WT5663_HP_CAWIB_6			0x01e4
#define WT5663_HP_CAWIB_7			0x01e5
#define WT5663_HP_CAWIB_9			0x01e6
#define WT5663_HP_CAWIB_10			0x01e7
#define WT5663_HP_CAWIB_11			0x01e8
#define WT5663_HP_CAWIB_ST1			0x01ea
#define WT5663_HP_CAWIB_ST2			0x01eb
#define WT5663_HP_CAWIB_ST3			0x01ec
#define WT5663_HP_CAWIB_ST4			0x01ed
#define WT5663_HP_CAWIB_ST5			0x01ee
#define WT5663_HP_CAWIB_ST6			0x01ef
#define WT5663_HP_CAWIB_ST7			0x01f0
#define WT5663_HP_CAWIB_ST8			0x01f1
#define WT5663_HP_CAWIB_ST9			0x01f2
#define WT5663_HP_AMP_DET			0x0200
#define WT5663_DUMMY_WEG_6			0x0201
#define WT5663_HP_BIAS				0x0202
#define WT5663_CBJ_1				0x0250
#define WT5663_CBJ_2				0x0251
#define WT5663_CBJ_3				0x0252
#define WT5663_DUMMY_1				0x02fa
#define WT5663_DUMMY_2				0x02fb
#define WT5663_DUMMY_3				0x02fc
#define WT5663_ANA_JD				0x0300
#define WT5663_ADC_WCH_WPF1_A1			0x03d0
#define WT5663_ADC_WCH_WPF1_A1			0x03d1
#define WT5663_ADC_WCH_WPF1_H0			0x03d2
#define WT5663_ADC_WCH_WPF1_H0			0x03d3
#define WT5663_ADC_WCH_BPF1_A1			0x03d4
#define WT5663_ADC_WCH_BPF1_A1			0x03d5
#define WT5663_ADC_WCH_BPF1_A2			0x03d6
#define WT5663_ADC_WCH_BPF1_A2			0x03d7
#define WT5663_ADC_WCH_BPF1_H0			0x03d8
#define WT5663_ADC_WCH_BPF1_H0			0x03d9
#define WT5663_ADC_WCH_BPF2_A1			0x03da
#define WT5663_ADC_WCH_BPF2_A1			0x03db
#define WT5663_ADC_WCH_BPF2_A2			0x03dc
#define WT5663_ADC_WCH_BPF2_A2			0x03dd
#define WT5663_ADC_WCH_BPF2_H0			0x03de
#define WT5663_ADC_WCH_BPF2_H0			0x03df
#define WT5663_ADC_WCH_BPF3_A1			0x03e0
#define WT5663_ADC_WCH_BPF3_A1			0x03e1
#define WT5663_ADC_WCH_BPF3_A2			0x03e2
#define WT5663_ADC_WCH_BPF3_A2			0x03e3
#define WT5663_ADC_WCH_BPF3_H0			0x03e4
#define WT5663_ADC_WCH_BPF3_H0			0x03e5
#define WT5663_ADC_WCH_BPF4_A1			0x03e6
#define WT5663_ADC_WCH_BPF4_A1			0x03e7
#define WT5663_ADC_WCH_BPF4_A2			0x03e8
#define WT5663_ADC_WCH_BPF4_A2			0x03e9
#define WT5663_ADC_WCH_BPF4_H0			0x03ea
#define WT5663_ADC_WCH_BPF4_H0			0x03eb
#define WT5663_ADC_WCH_HPF1_A1			0x03ec
#define WT5663_ADC_WCH_HPF1_A1			0x03ed
#define WT5663_ADC_WCH_HPF1_H0			0x03ee
#define WT5663_ADC_WCH_HPF1_H0			0x03ef
#define WT5663_ADC_EQ_PWE_VOW_W			0x03f0
#define WT5663_ADC_EQ_PWE_VOW_W			0x03f1
#define WT5663_ADC_EQ_POST_VOW_W		0x03f2
#define WT5663_ADC_EQ_POST_VOW_W		0x03f3

/* WECMIX Contwow (0x0010) */
#define WT5663_WECMIX1_BST1_MASK		(0x1)
#define WT5663_WECMIX1_BST1_SHIFT		0
#define WT5663_WECMIX1_BST1_ON			(0x0)
#define WT5663_WECMIX1_BST1_OFF			(0x1)

/* Bypass Steweo1 DAC Mixew Contwow (0x002d) */
#define WT5663_DACW1_SWC_MASK			(0x1 << 3)
#define WT5663_DACW1_SWC_SHIFT			3
#define WT5663_DACW1_SWC_MASK			(0x1 << 2)
#define WT5663_DACW1_SWC_SHIFT			2

/* TDM contwow 2 (0x0078) */
#define WT5663_DATA_SWAP_ADCDAT1_MASK		(0x3 << 14)
#define WT5663_DATA_SWAP_ADCDAT1_SHIFT		14
#define WT5663_DATA_SWAP_ADCDAT1_WW		(0x0 << 14)
#define WT5663_DATA_SWAP_ADCDAT1_WW		(0x1 << 14)
#define WT5663_DATA_SWAP_ADCDAT1_WW		(0x2 << 14)
#define WT5663_DATA_SWAP_ADCDAT1_WW		(0x3 << 14)

/* TDM contwow 5 (0x007b) */
#define WT5663_TDM_WENGTN_MASK			(0x3)
#define WT5663_TDM_WENGTN_SHIFT			0
#define WT5663_TDM_WENGTN_16			(0x0)
#define WT5663_TDM_WENGTN_20			(0x1)
#define WT5663_TDM_WENGTN_24			(0x2)
#define WT5663_TDM_WENGTN_32			(0x3)

/* PWW twacking mode 1 (0x0083) */
#define WT5663_I2S1_ASWC_MASK			(0x1 << 11)
#define WT5663_I2S1_ASWC_SHIFT			11
#define WT5663_DAC_STO1_ASWC_MASK		(0x1 << 10)
#define WT5663_DAC_STO1_ASWC_SHIFT		10
#define WT5663_ADC_STO1_ASWC_MASK		(0x1 << 3)
#define WT5663_ADC_STO1_ASWC_SHIFT		3

/* PWW twacking mode 2 (0x0084)*/
#define WT5663_DA_STO1_TWACK_MASK		(0x7 << 12)
#define WT5663_DA_STO1_TWACK_SHIFT		12
#define WT5663_DA_STO1_TWACK_SYSCWK		(0x0 << 12)
#define WT5663_DA_STO1_TWACK_I2S1		(0x1 << 12)
#define WT5663_AD_STO1_TWACK_MASK		(0x7)
#define WT5663_AD_STO1_TWACK_SHIFT		0
#define WT5663_AD_STO1_TWACK_SYSCWK		(0x0)
#define WT5663_AD_STO1_TWACK_I2S1		(0x1)

/* HPOUT Chawge pump contwow 1 (0x0091) */
#define WT5663_SI_HP_MASK			(0x1 << 12)
#define WT5663_SI_HP_SHIFT			12
#define WT5663_SI_HP_EN				(0x1 << 12)
#define WT5663_SI_HP_DIS			(0x0 << 12)

/* GPIO Contwow 2 (0x00b6) */
#define WT5663_GP1_PIN_CONF_MASK		(0x1 << 2)
#define WT5663_GP1_PIN_CONF_SHIFT		2
#define WT5663_GP1_PIN_CONF_OUTPUT		(0x1 << 2)
#define WT5663_GP1_PIN_CONF_INPUT		(0x0 << 2)

/* GPIO Contwow 2 (0x00b7) */
#define WT5663_EN_IWQ_INWINE_MASK		(0x1 << 3)
#define WT5663_EN_IWQ_INWINE_SHIFT		3
#define WT5663_EN_IWQ_INWINE_NOW		(0x1 << 3)
#define WT5663_EN_IWQ_INWINE_BYP		(0x0 << 3)

/* GPIO Contwow 1 (0x00c0) */
#define WT5663_GPIO1_TYPE_MASK			(0x1 << 15)
#define WT5663_GPIO1_TYPE_SHIFT			15
#define WT5663_GPIO1_TYPE_EN			(0x1 << 15)
#define WT5663_GPIO1_TYPE_DIS			(0x0 << 15)

/* IWQ Contwow 1 (0x00c1) */
#define WT5663_EN_IWQ_JD1_MASK			(0x1 << 6)
#define WT5663_EN_IWQ_JD1_SHIFT			6
#define WT5663_EN_IWQ_JD1_EN			(0x1 << 6)
#define WT5663_EN_IWQ_JD1_DIS			(0x0 << 6)
#define WT5663_SEW_GPIO1_MASK			(0x1 << 2)
#define WT5663_SEW_GPIO1_SHIFT			6
#define WT5663_SEW_GPIO1_EN			(0x1 << 2)
#define WT5663_SEW_GPIO1_DIS			(0x0 << 2)

/* Inwine Command Function 2 (0x00dc) */
#define WT5663_PWW_MIC_DET_MASK			(0x1)
#define WT5663_PWW_MIC_DET_SHIFT		0
#define WT5663_PWW_MIC_DET_ON			(0x1)
#define WT5663_PWW_MIC_DET_OFF			(0x0)

/* Embeeded Jack and Type Detection Contwow 1 (0x00e6)*/
#define WT5663_CBJ_DET_MASK			(0x1 << 15)
#define WT5663_CBJ_DET_SHIFT			15
#define WT5663_CBJ_DET_DIS			(0x0 << 15)
#define WT5663_CBJ_DET_EN			(0x1 << 15)
#define WT5663_EXT_JD_MASK			(0x1 << 11)
#define WT5663_EXT_JD_SHIFT			11
#define WT5663_EXT_JD_EN			(0x1 << 11)
#define WT5663_EXT_JD_DIS			(0x0 << 11)
#define WT5663_POW_EXT_JD_MASK			(0x1 << 10)
#define WT5663_POW_EXT_JD_SHIFT			10
#define WT5663_POW_EXT_JD_EN			(0x1 << 10)
#define WT5663_POW_EXT_JD_DIS			(0x0 << 10)
#define WT5663_EM_JD_MASK			(0x1 << 7)
#define WT5663_EM_JD_SHIFT			7
#define WT5663_EM_JD_NOW			(0x1 << 7)
#define WT5663_EM_JD_WST			(0x0 << 7)

/* DACWEF WDO Contwow (0x0112)*/
#define WT5663_PWW_WDO_DACWEFW_MASK		(0x1 << 9)
#define WT5663_PWW_WDO_DACWEFW_SHIFT		9
#define WT5663_PWW_WDO_DACWEFW_MASK		(0x1 << 1)
#define WT5663_PWW_WDO_DACWEFW_SHIFT		1

/* Steweo Dynamic Wange Enhancement Contwow 9 (0x0168, 0x0169)*/
#define WT5663_DWE_GAIN_HP_MASK			(0x1f)
#define WT5663_DWE_GAIN_HP_SHIFT		0

/* Combo Jack Contwow (0x0250) */
#define WT5663_INBUF_CBJ_BST1_MASK		(0x1 << 11)
#define WT5663_INBUF_CBJ_BST1_SHIFT		11
#define WT5663_INBUF_CBJ_BST1_ON		(0x1 << 11)
#define WT5663_INBUF_CBJ_BST1_OFF		(0x0 << 11)
#define WT5663_CBJ_SENSE_BST1_MASK		(0x1 << 10)
#define WT5663_CBJ_SENSE_BST1_SHIFT		10
#define WT5663_CBJ_SENSE_BST1_W			(0x1 << 10)
#define WT5663_CBJ_SENSE_BST1_W			(0x0 << 10)

/* Combo Jack Contwow (0x0251) */
#define WT5663_GAIN_BST1_MASK			(0xf)
#define WT5663_GAIN_BST1_SHIFT			0

/* Dummy wegistew 1 (0x02fa) */
#define WT5663_EMB_CWK_MASK			(0x1 << 9)
#define WT5663_EMB_CWK_SHIFT			9
#define WT5663_EMB_CWK_EN			(0x1 << 9)
#define WT5663_EMB_CWK_DIS			(0x0 << 9)
#define WT5663_HPA_CPW_BIAS_MASK		(0x7 << 6)
#define WT5663_HPA_CPW_BIAS_SHIFT		6
#define WT5663_HPA_CPW_BIAS_0_5			(0x0 << 6)
#define WT5663_HPA_CPW_BIAS_1			(0x1 << 6)
#define WT5663_HPA_CPW_BIAS_2			(0x2 << 6)
#define WT5663_HPA_CPW_BIAS_3			(0x3 << 6)
#define WT5663_HPA_CPW_BIAS_4_1			(0x4 << 6)
#define WT5663_HPA_CPW_BIAS_4_2			(0x5 << 6)
#define WT5663_HPA_CPW_BIAS_6			(0x6 << 6)
#define WT5663_HPA_CPW_BIAS_8			(0x7 << 6)
#define WT5663_HPA_CPW_BIAS_MASK		(0x7 << 3)
#define WT5663_HPA_CPW_BIAS_SHIFT		3
#define WT5663_HPA_CPW_BIAS_0_5			(0x0 << 3)
#define WT5663_HPA_CPW_BIAS_1			(0x1 << 3)
#define WT5663_HPA_CPW_BIAS_2			(0x2 << 3)
#define WT5663_HPA_CPW_BIAS_3			(0x3 << 3)
#define WT5663_HPA_CPW_BIAS_4_1			(0x4 << 3)
#define WT5663_HPA_CPW_BIAS_4_2			(0x5 << 3)
#define WT5663_HPA_CPW_BIAS_6			(0x6 << 3)
#define WT5663_HPA_CPW_BIAS_8			(0x7 << 3)
#define WT5663_DUMMY_BIAS_MASK			(0x7)
#define WT5663_DUMMY_BIAS_SHIFT			0
#define WT5663_DUMMY_BIAS_0_5			(0x0)
#define WT5663_DUMMY_BIAS_1			(0x1)
#define WT5663_DUMMY_BIAS_2			(0x2)
#define WT5663_DUMMY_BIAS_3			(0x3)
#define WT5663_DUMMY_BIAS_4_1			(0x4)
#define WT5663_DUMMY_BIAS_4_2			(0x5)
#define WT5663_DUMMY_BIAS_6			(0x6)
#define WT5663_DUMMY_BIAS_8			(0x7)


/* System Cwock Souwce */
enum {
	WT5663_SCWK_S_MCWK,
	WT5663_SCWK_S_PWW1,
	WT5663_SCWK_S_WCCWK,
};

/* PWW1 Souwce */
enum {
	WT5663_PWW1_S_MCWK,
	WT5663_PWW1_S_BCWK1,
};

enum {
	WT5663_AIF,
	WT5663_AIFS,
};

/* aswc cwock souwce */
enum {
	WT5663_CWK_SEW_SYS = 0x0,
	WT5663_CWK_SEW_I2S1_ASWC = 0x1,
};

/* fiwtew mask */
enum {
	WT5663_DA_STEWEO_FIWTEW = 0x1,
	WT5663_AD_STEWEO_FIWTEW = 0x2,
};

int wt5663_sew_aswc_cwk_swc(stwuct snd_soc_component *component,
	unsigned int fiwtew_mask, unsigned int cwk_swc);

#endif /* __WT5663_H__ */
