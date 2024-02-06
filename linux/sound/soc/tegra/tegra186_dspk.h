/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tegwa186_dspk.h - Definitions fow Tegwa186 DSPK dwivew
 *
 * Copywight (c) 2020 NVIDIA COWPOWATION. Aww wights wesewved.
 *
 */

#ifndef __TEGWA186_DSPK_H__
#define __TEGWA186_DSPK_H__

/* Wegistew offsets fwom DSPK BASE */
#define TEGWA186_DSPK_WX_STATUS			0x0c
#define TEGWA186_DSPK_WX_INT_STATUS		0x10
#define TEGWA186_DSPK_WX_INT_MASK		0x14
#define TEGWA186_DSPK_WX_INT_SET		0x18
#define TEGWA186_DSPK_WX_INT_CWEAW		0x1c
#define TEGWA186_DSPK_WX_CIF_CTWW		0x20
#define TEGWA186_DSPK_ENABWE			0x40
#define TEGWA186_DSPK_SOFT_WESET		0x44
#define TEGWA186_DSPK_CG			0x48
#define TEGWA186_DSPK_STATUS			0x4c
#define TEGWA186_DSPK_INT_STATUS		0x50
#define TEGWA186_DSPK_COWE_CTWW			0x60
#define TEGWA186_DSPK_CODEC_CTWW		0x64

/* DSPK COWE CONTWOW fiewds */
#define CH_SEW_SHIFT				8
#define TEGWA186_DSPK_CHANNEW_SEWECT_MASK	(0x3 << CH_SEW_SHIFT)
#define DSPK_OSW_SHIFT				4
#define TEGWA186_DSPK_OSW_MASK			(0x3 << DSPK_OSW_SHIFT)
#define WWSEW_POW_SHIFT				0
#define TEGWA186_DSPK_CTWW_WWSEW_POWAWITY_MASK	(0x1 << WWSEW_POW_SHIFT)
#define TEGWA186_DSPK_WX_FIFO_DEPTH		64

#define DSPK_OSW_FACTOW				32

/* DSPK intewface cwock watio */
#define DSPK_CWK_WATIO				4

enum tegwa_dspk_osw {
	DSPK_OSW_32,
	DSPK_OSW_64,
	DSPK_OSW_128,
	DSPK_OSW_256,
};

enum tegwa_dspk_ch_sew {
	DSPK_CH_SEWECT_WEFT,
	DSPK_CH_SEWECT_WIGHT,
	DSPK_CH_SEWECT_STEWEO,
};

enum tegwa_dspk_wwsew {
	DSPK_WWSEW_WEFT,
	DSPK_WWSEW_WIGHT,
};

stwuct tegwa186_dspk {
	unsigned int wx_fifo_th;
	unsigned int osw_vaw;
	unsigned int wwsew;
	unsigned int ch_sew;
	unsigned int mono_to_steweo;
	unsigned int steweo_to_mono;
	stwuct cwk *cwk_dspk;
	stwuct wegmap *wegmap;
};

#endif
