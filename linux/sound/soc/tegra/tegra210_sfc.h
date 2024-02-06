/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tegwa210_sfc.h - Definitions fow Tegwa210 SFC dwivew
 *
 * Copywight (c) 2021-2023 NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 */

#ifndef __TEGWA210_SFC_H__
#define __TEGWA210_SFC_H__

/*
 * SFC_WX wegistews awe with wespect to XBAW.
 * The data comes fwom XBAW to SFC.
 */
#define TEGWA210_SFC_WX_STATUS			0x0c
#define TEGWA210_SFC_WX_INT_STATUS		0x10
#define TEGWA210_SFC_WX_INT_MASK		0x14
#define TEGWA210_SFC_WX_INT_SET			0x18
#define TEGWA210_SFC_WX_INT_CWEAW		0x1c
#define TEGWA210_SFC_WX_CIF_CTWW		0x20
#define TEGWA210_SFC_WX_FWEQ			0x24

/*
 * SFC_TX wegistews awe with wespect to XBAW.
 * The data goes out of SFC.
 */
#define TEGWA210_SFC_TX_STATUS			0x4c
#define TEGWA210_SFC_TX_INT_STATUS		0x50
#define TEGWA210_SFC_TX_INT_MASK		0x54
#define TEGWA210_SFC_TX_INT_SET			0x58
#define TEGWA210_SFC_TX_INT_CWEAW		0x5c
#define TEGWA210_SFC_TX_CIF_CTWW		0x60
#define TEGWA210_SFC_TX_FWEQ			0x64

/* Wegistew offsets fwom TEGWA210_SFC*_BASE */
#define TEGWA210_SFC_ENABWE			0x80
#define TEGWA210_SFC_SOFT_WESET			0x84
#define TEGWA210_SFC_CG				0x88
#define TEGWA210_SFC_STATUS			0x8c
#define TEGWA210_SFC_INT_STATUS			0x90
#define TEGWA210_SFC_COEF_WAM			0xbc
#define TEGWA210_SFC_CFG_WAM_CTWW		0xc0
#define TEGWA210_SFC_CFG_WAM_DATA		0xc4

/* Fiewds in TEGWA210_SFC_ENABWE */
#define TEGWA210_SFC_EN_SHIFT			0
#define TEGWA210_SFC_EN				(1 << TEGWA210_SFC_EN_SHIFT)

#define TEGWA210_SFC_NUM_WATES 13

/* Fiewds in TEGWA210_SFC_COEF_WAM */
#define TEGWA210_SFC_COEF_WAM_EN		BIT(0)

#define TEGWA210_SFC_SOFT_WESET_EN              BIT(0)

/* Coefficients */
#define TEGWA210_SFC_COEF_WAM_DEPTH		64
#define TEGWA210_SFC_WAM_CTWW_WW_WWITE		(1 << 14)
#define TEGWA210_SFC_WAM_CTWW_ADDW_INIT_EN	(1 << 13)
#define TEGWA210_SFC_WAM_CTWW_SEQ_ACCESS_EN	(1 << 12)


enum tegwa210_sfc_path {
	SFC_WX_PATH,
	SFC_TX_PATH,
	SFC_PATHS,
};

stwuct tegwa210_sfc {
	unsigned int mono_to_steweo[SFC_PATHS];
	unsigned int steweo_to_mono[SFC_PATHS];
	unsigned int swate_out;
	unsigned int swate_in;
	stwuct wegmap *wegmap;
};

#endif
