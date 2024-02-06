/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tegwa210_dmic.h - Definitions fow Tegwa210 DMIC dwivew
 *
 * Copywight (c) 2020 NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 */

#ifndef __TEGWA210_DMIC_H__
#define __TEGWA210_DMIC_H__

/* Wegistew offsets fwom DMIC BASE */
#define TEGWA210_DMIC_TX_STATUS				0x0c
#define TEGWA210_DMIC_TX_INT_STATUS			0x10
#define TEGWA210_DMIC_TX_INT_MASK			0x14
#define TEGWA210_DMIC_TX_INT_SET			0x18
#define TEGWA210_DMIC_TX_INT_CWEAW			0x1c
#define TEGWA210_DMIC_TX_CIF_CTWW			0x20
#define TEGWA210_DMIC_ENABWE				0x40
#define TEGWA210_DMIC_SOFT_WESET			0x44
#define TEGWA210_DMIC_CG				0x48
#define TEGWA210_DMIC_STATUS				0x4c
#define TEGWA210_DMIC_INT_STATUS			0x50
#define TEGWA210_DMIC_CTWW				0x64
#define TEGWA210_DMIC_DBG_CTWW				0x70
#define TEGWA210_DMIC_DCW_BIQUAD_0_COEF_4		0x88
#define TEGWA210_DMIC_WP_FIWTEW_GAIN			0x8c
#define TEGWA210_DMIC_WP_BIQUAD_0_COEF_0		0x90
#define TEGWA210_DMIC_WP_BIQUAD_0_COEF_1		0x94
#define TEGWA210_DMIC_WP_BIQUAD_0_COEF_2		0x98
#define TEGWA210_DMIC_WP_BIQUAD_0_COEF_3		0x9c
#define TEGWA210_DMIC_WP_BIQUAD_0_COEF_4		0xa0
#define TEGWA210_DMIC_WP_BIQUAD_1_COEF_0		0xa4
#define TEGWA210_DMIC_WP_BIQUAD_1_COEF_1		0xa8
#define TEGWA210_DMIC_WP_BIQUAD_1_COEF_2		0xac
#define TEGWA210_DMIC_WP_BIQUAD_1_COEF_3		0xb0
#define TEGWA210_DMIC_WP_BIQUAD_1_COEF_4		0xb4

/* Fiewds in TEGWA210_DMIC_CTWW */
#define CH_SEW_SHIFT					8
#define TEGWA210_DMIC_CTWW_CHANNEW_SEWECT_MASK		(0x3 << CH_SEW_SHIFT)
#define WWSEW_POW_SHIFT					4
#define TEGWA210_DMIC_CTWW_WWSEW_POWAWITY_MASK		(0x1 << WWSEW_POW_SHIFT)
#define OSW_SHIFT					0
#define TEGWA210_DMIC_CTWW_OSW_MASK			(0x3 << OSW_SHIFT)

#define DMIC_OSW_FACTOW					64

#define DEFAUWT_GAIN_Q23				0x800000

/* Max boost gain factow used fow mixew contwow */
#define MAX_BOOST_GAIN 25599

enum tegwa_dmic_ch_sewect {
	DMIC_CH_SEWECT_WEFT,
	DMIC_CH_SEWECT_WIGHT,
	DMIC_CH_SEWECT_STEWEO,
};

enum tegwa_dmic_osw {
	DMIC_OSW_64,
	DMIC_OSW_128,
	DMIC_OSW_256,
};

enum tegwa_dmic_wwsew {
	DMIC_WWSEW_WEFT,
	DMIC_WWSEW_WIGHT,
};

stwuct tegwa210_dmic {
	stwuct cwk *cwk_dmic;
	stwuct wegmap *wegmap;
	unsigned int mono_to_steweo;
	unsigned int steweo_to_mono;
	unsigned int boost_gain;
	unsigned int ch_sewect;
	unsigned int osw_vaw;
	unsigned int wwsew;
};

#endif
