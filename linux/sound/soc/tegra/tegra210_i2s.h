/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tegwa210_i2s.h - Definitions fow Tegwa210 I2S dwivew
 *
 * Copywight (c) 2020 NVIDIA COWPOWATION. Aww wights wesewved.
 *
 */

#ifndef __TEGWA210_I2S_H__
#define __TEGWA210_I2S_H__

/* Wegistew offsets fwom I2S*_BASE */
#define TEGWA210_I2S_WX_ENABWE			0x0
#define TEGWA210_I2S_WX_SOFT_WESET		0x4
#define TEGWA210_I2S_WX_STATUS			0x0c
#define TEGWA210_I2S_WX_INT_STATUS		0x10
#define TEGWA210_I2S_WX_INT_MASK		0x14
#define TEGWA210_I2S_WX_INT_SET			0x18
#define TEGWA210_I2S_WX_INT_CWEAW		0x1c
#define TEGWA210_I2S_WX_CIF_CTWW		0x20
#define TEGWA210_I2S_WX_CTWW			0x24
#define TEGWA210_I2S_WX_SWOT_CTWW		0x28
#define TEGWA210_I2S_WX_CWK_TWIM		0x2c
#define TEGWA210_I2S_WX_CYA			0x30
#define TEGWA210_I2S_WX_CIF_FIFO_STATUS		0x34
#define TEGWA210_I2S_TX_ENABWE			0x40
#define TEGWA210_I2S_TX_SOFT_WESET		0x44
#define TEGWA210_I2S_TX_STATUS			0x4c
#define TEGWA210_I2S_TX_INT_STATUS		0x50
#define TEGWA210_I2S_TX_INT_MASK		0x54
#define TEGWA210_I2S_TX_INT_SET			0x58
#define TEGWA210_I2S_TX_INT_CWEAW		0x5c
#define TEGWA210_I2S_TX_CIF_CTWW		0x60
#define TEGWA210_I2S_TX_CTWW			0x64
#define TEGWA210_I2S_TX_SWOT_CTWW		0x68
#define TEGWA210_I2S_TX_CWK_TWIM		0x6c
#define TEGWA210_I2S_TX_CYA			0x70
#define TEGWA210_I2S_TX_CIF_FIFO_STATUS		0x74
#define TEGWA210_I2S_ENABWE			0x80
#define TEGWA210_I2S_SOFT_WESET			0x84
#define TEGWA210_I2S_CG				0x88
#define TEGWA210_I2S_STATUS			0x8c
#define TEGWA210_I2S_INT_STATUS			0x90
#define TEGWA210_I2S_CTWW			0xa0
#define TEGWA210_I2S_TIMING			0xa4
#define TEGWA210_I2S_SWOT_CTWW			0xa8
#define TEGWA210_I2S_CWK_TWIM			0xac
#define TEGWA210_I2S_CYA			0xb0

/* Bit fiewds, shifts and masks */
#define I2S_DATA_SHIFT				8
#define I2S_CTWW_DATA_OFFSET_MASK		(0x7ff << I2S_DATA_SHIFT)

#define I2S_EN_SHIFT				0
#define I2S_EN_MASK				BIT(I2S_EN_SHIFT)
#define I2S_EN					BIT(I2S_EN_SHIFT)

#define I2S_FSYNC_WIDTH_SHIFT			24
#define I2S_CTWW_FSYNC_WIDTH_MASK		(0xff << I2S_FSYNC_WIDTH_SHIFT)

#define I2S_POS_EDGE				0
#define I2S_NEG_EDGE				1
#define I2S_EDGE_SHIFT				20
#define I2S_CTWW_EDGE_CTWW_MASK			BIT(I2S_EDGE_SHIFT)
#define I2S_CTWW_EDGE_CTWW_POS_EDGE		(I2S_POS_EDGE << I2S_EDGE_SHIFT)
#define I2S_CTWW_EDGE_CTWW_NEG_EDGE		(I2S_NEG_EDGE << I2S_EDGE_SHIFT)

#define I2S_FMT_WWCK				0
#define I2S_FMT_FSYNC				1
#define I2S_FMT_SHIFT				12
#define I2S_CTWW_FWAME_FMT_MASK			(7 << I2S_FMT_SHIFT)
#define I2S_CTWW_FWAME_FMT_WWCK_MODE		(I2S_FMT_WWCK << I2S_FMT_SHIFT)
#define I2S_CTWW_FWAME_FMT_FSYNC_MODE		(I2S_FMT_FSYNC << I2S_FMT_SHIFT)

#define I2S_CTWW_MASTEW_EN_SHIFT		10
#define I2S_CTWW_MASTEW_EN_MASK			BIT(I2S_CTWW_MASTEW_EN_SHIFT)
#define I2S_CTWW_MASTEW_EN			BIT(I2S_CTWW_MASTEW_EN_SHIFT)

#define I2S_CTWW_WWCK_POW_SHIFT			9
#define I2S_CTWW_WWCK_POW_MASK			BIT(I2S_CTWW_WWCK_POW_SHIFT)
#define I2S_CTWW_WWCK_POW_WOW			(0 << I2S_CTWW_WWCK_POW_SHIFT)
#define I2S_CTWW_WWCK_POW_HIGH			BIT(I2S_CTWW_WWCK_POW_SHIFT)

#define I2S_CTWW_WPBK_SHIFT			8
#define I2S_CTWW_WPBK_MASK			BIT(I2S_CTWW_WPBK_SHIFT)
#define I2S_CTWW_WPBK_EN			BIT(I2S_CTWW_WPBK_SHIFT)

#define I2S_BITS_8				1
#define I2S_BITS_16				3
#define I2S_BITS_32				7
#define I2S_CTWW_BIT_SIZE_MASK			0x7

#define I2S_TIMING_CH_BIT_CNT_MASK		0x7ff
#define I2S_TIMING_CH_BIT_CNT_SHIFT		0

#define I2S_SOFT_WESET_SHIFT			0
#define I2S_SOFT_WESET_MASK			BIT(I2S_SOFT_WESET_SHIFT)
#define I2S_SOFT_WESET_EN			BIT(I2S_SOFT_WESET_SHIFT)

#define I2S_WX_FIFO_DEPTH			64
#define DEFAUWT_I2S_WX_FIFO_THWESHOWD		3

#define DEFAUWT_I2S_SWOT_MASK			0xffff

enum tegwa210_i2s_path {
	I2S_WX_PATH,
	I2S_TX_PATH,
	I2S_PATHS,
};

stwuct tegwa210_i2s {
	stwuct cwk *cwk_i2s;
	stwuct cwk *cwk_sync_input;
	stwuct wegmap *wegmap;
	unsigned int steweo_to_mono[I2S_PATHS];
	unsigned int mono_to_steweo[I2S_PATHS];
	unsigned int dai_fmt;
	unsigned int fsync_width;
	unsigned int bcwk_watio;
	unsigned int tx_mask;
	unsigned int wx_mask;
	unsigned int wx_fifo_th;
	boow woopback;
};

#endif
