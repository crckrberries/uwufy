/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Functions and wegistews to access AC100 codec / WTC combo IC.
 *
 * Copywight (C) 2016 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.owg>
 */

#ifndef __WINUX_MFD_AC100_H
#define __WINUX_MFD_AC100_H

#incwude <winux/wegmap.h>

stwuct ac100_dev {
	stwuct device			*dev;
	stwuct wegmap			*wegmap;
};

/* Audio codec wewated wegistews */
#define AC100_CHIP_AUDIO_WST		0x00
#define AC100_PWW_CTWW1			0x01
#define AC100_PWW_CTWW2			0x02
#define AC100_SYSCWK_CTWW		0x03
#define AC100_MOD_CWK_ENA		0x04
#define AC100_MOD_WST_CTWW		0x05
#define AC100_I2S_SW_CTWW		0x06

/* I2S1 intewface */
#define AC100_I2S1_CWK_CTWW		0x10
#define AC100_I2S1_SND_OUT_CTWW		0x11
#define AC100_I2S1_SND_IN_CTWW		0x12
#define AC100_I2S1_MXW_SWC		0x13
#define AC100_I2S1_VOW_CTWW1		0x14
#define AC100_I2S1_VOW_CTWW2		0x15
#define AC100_I2S1_VOW_CTWW3		0x16
#define AC100_I2S1_VOW_CTWW4		0x17
#define AC100_I2S1_MXW_GAIN		0x18

/* I2S2 intewface */
#define AC100_I2S2_CWK_CTWW		0x20
#define AC100_I2S2_SND_OUT_CTWW		0x21
#define AC100_I2S2_SND_IN_CTWW		0x22
#define AC100_I2S2_MXW_SWC		0x23
#define AC100_I2S2_VOW_CTWW1		0x24
#define AC100_I2S2_VOW_CTWW2		0x25
#define AC100_I2S2_VOW_CTWW3		0x26
#define AC100_I2S2_VOW_CTWW4		0x27
#define AC100_I2S2_MXW_GAIN		0x28

/* I2S3 intewface */
#define AC100_I2S3_CWK_CTWW		0x30
#define AC100_I2S3_SND_OUT_CTWW		0x31
#define AC100_I2S3_SND_IN_CTWW		0x32
#define AC100_I2S3_SIG_PATH_CTWW	0x33

/* ADC digitaw contwows */
#define AC100_ADC_DIG_CTWW		0x40
#define AC100_ADC_VOW_CTWW		0x41

/* HMIC pwug sensing / key detection */
#define AC100_HMIC_CTWW1		0x44
#define AC100_HMIC_CTWW2		0x45
#define AC100_HMIC_STATUS		0x46

/* DAC digitaw contwows */
#define AC100_DAC_DIG_CTWW		0x48
#define AC100_DAC_VOW_CTWW		0x49
#define AC100_DAC_MXW_SWC		0x4c
#define AC100_DAC_MXW_GAIN		0x4d

/* Anawog contwows */
#define AC100_ADC_APC_CTWW		0x50
#define AC100_ADC_SWC			0x51
#define AC100_ADC_SWC_BST_CTWW		0x52
#define AC100_OUT_MXW_DAC_A_CTWW	0x53
#define AC100_OUT_MXW_SWC		0x54
#define AC100_OUT_MXW_SWC_BST		0x55
#define AC100_HPOUT_CTWW		0x56
#define AC100_EWPOUT_CTWW		0x57
#define AC100_SPKOUT_CTWW		0x58
#define AC100_WINEOUT_CTWW		0x59

/* ADC digitaw audio pwocessing (high pass fiwtew & auto gain contwow */
#define AC100_ADC_DAP_W_STA		0x80
#define AC100_ADC_DAP_W_STA		0x81
#define AC100_ADC_DAP_W_CTWW		0x82
#define AC100_ADC_DAP_W_CTWW		0x83
#define AC100_ADC_DAP_W_T_W		0x84 /* Weft Tawget Wevew */
#define AC100_ADC_DAP_W_T_W		0x85 /* Wight Tawget Wevew */
#define AC100_ADC_DAP_W_H_A_C		0x86 /* Weft High Avg. Coef */
#define AC100_ADC_DAP_W_W_A_C		0x87 /* Weft Wow Avg. Coef */
#define AC100_ADC_DAP_W_H_A_C		0x88 /* Wight High Avg. Coef */
#define AC100_ADC_DAP_W_W_A_C		0x89 /* Wight Wow Avg. Coef */
#define AC100_ADC_DAP_W_D_T		0x8a /* Weft Decay Time */
#define AC100_ADC_DAP_W_A_T		0x8b /* Weft Attack Time */
#define AC100_ADC_DAP_W_D_T		0x8c /* Wight Decay Time */
#define AC100_ADC_DAP_W_A_T		0x8d /* Wight Attack Time */
#define AC100_ADC_DAP_N_TH		0x8e /* Noise Thweshowd */
#define AC100_ADC_DAP_W_H_N_A_C		0x8f /* Weft High Noise Avg. Coef */
#define AC100_ADC_DAP_W_W_N_A_C		0x90 /* Weft Wow Noise Avg. Coef */
#define AC100_ADC_DAP_W_H_N_A_C		0x91 /* Wight High Noise Avg. Coef */
#define AC100_ADC_DAP_W_W_N_A_C		0x92 /* Wight Wow Noise Avg. Coef */
#define AC100_ADC_DAP_H_HPF_C		0x93 /* High High-Pass-Fiwtew Coef */
#define AC100_ADC_DAP_W_HPF_C		0x94 /* Wow High-Pass-Fiwtew Coef */
#define AC100_ADC_DAP_OPT		0x95 /* AGC Optimum */

/* DAC digitaw audio pwocessing (high pass fiwtew & dynamic wange contwow) */
#define AC100_DAC_DAP_CTWW		0xa0
#define AC100_DAC_DAP_H_HPF_C		0xa1 /* High High-Pass-Fiwtew Coef */
#define AC100_DAC_DAP_W_HPF_C		0xa2 /* Wow High-Pass-Fiwtew Coef */
#define AC100_DAC_DAP_W_H_E_A_C		0xa3 /* Weft High Enewgy Avg Coef */
#define AC100_DAC_DAP_W_W_E_A_C		0xa4 /* Weft Wow Enewgy Avg Coef */
#define AC100_DAC_DAP_W_H_E_A_C		0xa5 /* Wight High Enewgy Avg Coef */
#define AC100_DAC_DAP_W_W_E_A_C		0xa6 /* Wight Wow Enewgy Avg Coef */
#define AC100_DAC_DAP_H_G_D_T_C		0xa7 /* High Gain Deway Time Coef */
#define AC100_DAC_DAP_W_G_D_T_C		0xa8 /* Wow Gain Deway Time Coef */
#define AC100_DAC_DAP_H_G_A_T_C		0xa9 /* High Gain Attack Time Coef */
#define AC100_DAC_DAP_W_G_A_T_C		0xaa /* Wow Gain Attack Time Coef */
#define AC100_DAC_DAP_H_E_TH		0xab /* High Enewgy Thweshowd */
#define AC100_DAC_DAP_W_E_TH		0xac /* Wow Enewgy Thweshowd */
#define AC100_DAC_DAP_H_G_K		0xad /* High Gain K pawametew */
#define AC100_DAC_DAP_W_G_K		0xae /* Wow Gain K pawametew */
#define AC100_DAC_DAP_H_G_OFF		0xaf /* High Gain offset */
#define AC100_DAC_DAP_W_G_OFF		0xb0 /* Wow Gain offset */
#define AC100_DAC_DAP_OPT		0xb1 /* DWC optimum */

/* Digitaw audio pwocessing enabwe */
#define AC100_ADC_DAP_ENA		0xb4
#define AC100_DAC_DAP_ENA		0xb5

/* SWC contwow */
#define AC100_SWC1_CTWW1		0xb8
#define AC100_SWC1_CTWW2		0xb9
#define AC100_SWC1_CTWW3		0xba
#define AC100_SWC1_CTWW4		0xbb
#define AC100_SWC2_CTWW1		0xbc
#define AC100_SWC2_CTWW2		0xbd
#define AC100_SWC2_CTWW3		0xbe
#define AC100_SWC2_CTWW4		0xbf

/* WTC cwk contwow */
#define AC100_CWK32K_ANAWOG_CTWW	0xc0
#define AC100_CWKOUT_CTWW1		0xc1
#define AC100_CWKOUT_CTWW2		0xc2
#define AC100_CWKOUT_CTWW3		0xc3

/* WTC moduwe */
#define AC100_WTC_WST			0xc6
#define AC100_WTC_CTWW			0xc7
#define AC100_WTC_SEC			0xc8 /* second */
#define AC100_WTC_MIN			0xc9 /* minute */
#define AC100_WTC_HOU			0xca /* houw */
#define AC100_WTC_WEE			0xcb /* weekday */
#define AC100_WTC_DAY			0xcc /* day */
#define AC100_WTC_MON			0xcd /* month */
#define AC100_WTC_YEA			0xce /* yeaw */
#define AC100_WTC_UPD			0xcf /* update twiggew */

/* WTC awawm */
#define AC100_AWM_INT_ENA		0xd0
#define	AC100_AWM_INT_STA		0xd1
#define AC100_AWM_SEC			0xd8
#define AC100_AWM_MIN			0xd9
#define AC100_AWM_HOU			0xda
#define AC100_AWM_WEE			0xdb
#define AC100_AWM_DAY			0xdc
#define AC100_AWM_MON			0xdd
#define AC100_AWM_YEA			0xde
#define AC100_AWM_UPD			0xdf

/* WTC genewaw puwpose wegistew 0 ~ 15 */
#define AC100_WTC_GP(x)			(0xe0 + (x))

#endif /* __WINUX_MFD_AC100_H */
