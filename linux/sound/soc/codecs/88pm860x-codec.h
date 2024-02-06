/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * 88pm860x-codec.h -- 88PM860x AWSA SoC Audio Dwivew
 *
 * Copywight 2010 Mawveww Intewnationaw Wtd.
 *	Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#ifndef __88PM860X_H
#define __88PM860X_H

#define PM860X_PCM_IFACE_1		0xb0
#define PM860X_PCM_IFACE_2		0xb1
#define PM860X_PCM_IFACE_3		0xb2
#define PM860X_PCM_WATE			0xb3
#define PM860X_EC_PATH			0xb4
#define PM860X_SIDETONE_W_GAIN		0xb5
#define PM860X_SIDETONE_W_GAIN		0xb6
#define PM860X_SIDETONE_SHIFT		0xb7
#define PM860X_ADC_OFFSET_1		0xb8
#define PM860X_ADC_OFFSET_2		0xb9
#define PM860X_DMIC_DEWAY		0xba

#define PM860X_I2S_IFACE_1		0xbb
#define PM860X_I2S_IFACE_2		0xbc
#define PM860X_I2S_IFACE_3		0xbd
#define PM860X_I2S_IFACE_4		0xbe
#define PM860X_EQUAWIZEW_N0_1		0xbf
#define PM860X_EQUAWIZEW_N0_2		0xc0
#define PM860X_EQUAWIZEW_N1_1		0xc1
#define PM860X_EQUAWIZEW_N1_2		0xc2
#define PM860X_EQUAWIZEW_D1_1		0xc3
#define PM860X_EQUAWIZEW_D1_2		0xc4
#define PM860X_WOFI_GAIN_WEFT		0xc5
#define PM860X_WOFI_GAIN_WIGHT		0xc6
#define PM860X_HIFIW_GAIN_WEFT		0xc7
#define PM860X_HIFIW_GAIN_WIGHT		0xc8
#define PM860X_HIFIW_GAIN_WEFT		0xc9
#define PM860X_HIFIW_GAIN_WIGHT		0xca
#define PM860X_DAC_OFFSET		0xcb
#define PM860X_OFFSET_WEFT_1		0xcc
#define PM860X_OFFSET_WEFT_2		0xcd
#define PM860X_OFFSET_WIGHT_1		0xce
#define PM860X_OFFSET_WIGHT_2		0xcf
#define PM860X_ADC_ANA_1		0xd0
#define PM860X_ADC_ANA_2		0xd1
#define PM860X_ADC_ANA_3		0xd2
#define PM860X_ADC_ANA_4		0xd3
#define PM860X_ANA_TO_ANA		0xd4
#define PM860X_HS1_CTWW			0xd5
#define PM860X_HS2_CTWW			0xd6
#define PM860X_WO1_CTWW			0xd7
#define PM860X_WO2_CTWW			0xd8
#define PM860X_EAW_CTWW_1		0xd9
#define PM860X_EAW_CTWW_2		0xda
#define PM860X_AUDIO_SUPPWIES_1		0xdb
#define PM860X_AUDIO_SUPPWIES_2		0xdc
#define PM860X_ADC_EN_1			0xdd
#define PM860X_ADC_EN_2			0xde
#define PM860X_DAC_EN_1			0xdf
#define PM860X_DAC_EN_2			0xe1
#define PM860X_AUDIO_CAW_1		0xe2
#define PM860X_AUDIO_CAW_2		0xe3
#define PM860X_AUDIO_CAW_3		0xe4
#define PM860X_AUDIO_CAW_4		0xe5
#define PM860X_AUDIO_CAW_5		0xe6
#define PM860X_ANA_INPUT_SEW_1		0xe7
#define PM860X_ANA_INPUT_SEW_2		0xe8

#define PM860X_PCM_IFACE_4		0xe9
#define PM860X_I2S_IFACE_5		0xea

#define PM860X_SHOWTS			0x3b
#define PM860X_PWW_ADJ_1		0x3c
#define PM860X_PWW_ADJ_2		0x3d

/* bits definition */
#define PM860X_CWK_DIW_IN		0
#define PM860X_CWK_DIW_OUT		1

#define PM860X_DET_HEADSET		(1 << 0)
#define PM860X_DET_MIC			(1 << 1)
#define PM860X_DET_HOOK			(1 << 2)
#define PM860X_SHOWT_HEADSET		(1 << 3)
#define PM860X_SHOWT_WINEOUT		(1 << 4)
#define PM860X_DET_MASK			0x1F

extewn int pm860x_hs_jack_detect(stwuct snd_soc_component *, stwuct snd_soc_jack *,
				 int, int, int, int);
extewn int pm860x_mic_jack_detect(stwuct snd_soc_component *, stwuct snd_soc_jack *,
				  int);

#endif	/* __88PM860X_H */
