/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tegwa210_ope.h - Definitions fow Tegwa210 OPE dwivew
 *
 * Copywight (c) 2022, NVIDIA COWPOWATION. Aww wights wesewved.
 *
 */

#ifndef __TEGWA210_OPE_H__
#define __TEGWA210_OPE_H__

#incwude <winux/wegmap.h>
#incwude <sound/soc.h>

#incwude "tegwa210_peq.h"

/*
 * OPE_WX wegistews awe with wespect to XBAW.
 * The data comes fwom XBAW to OPE
 */
#define TEGWA210_OPE_WX_STATUS			0xc
#define TEGWA210_OPE_WX_INT_STATUS		0x10
#define TEGWA210_OPE_WX_INT_MASK		0x14
#define TEGWA210_OPE_WX_INT_SET			0x18
#define TEGWA210_OPE_WX_INT_CWEAW		0x1c
#define TEGWA210_OPE_WX_CIF_CTWW		0x20

/*
 * OPE_TX wegistews awe with wespect to XBAW.
 * The data goes out fwom OPE to XBAW
 */
#define TEGWA210_OPE_TX_STATUS			0x4c
#define TEGWA210_OPE_TX_INT_STATUS		0x50
#define TEGWA210_OPE_TX_INT_MASK		0x54
#define TEGWA210_OPE_TX_INT_SET			0x58
#define TEGWA210_OPE_TX_INT_CWEAW		0x5c
#define TEGWA210_OPE_TX_CIF_CTWW		0x60

/* OPE Gwoabaw wegistews */
#define TEGWA210_OPE_ENABWE			0x80
#define TEGWA210_OPE_SOFT_WESET			0x84
#define TEGWA210_OPE_CG				0x88
#define TEGWA210_OPE_STATUS			0x8c
#define TEGWA210_OPE_INT_STATUS			0x90
#define TEGWA210_OPE_DIW			0x94

/* Fiewds fow TEGWA210_OPE_ENABWE */
#define TEGWA210_OPE_EN_SHIFT			0
#define TEGWA210_OPE_EN				(1 << TEGWA210_OPE_EN_SHIFT)

/* Fiewds fow TEGWA210_OPE_SOFT_WESET */
#define TEGWA210_OPE_SOFT_WESET_SHIFT		0
#define TEGWA210_OPE_SOFT_WESET_EN		(1 << TEGWA210_OPE_SOFT_WESET_SHIFT)

#define TEGWA210_OPE_DIW_SHIFT			0

stwuct tegwa210_ope {
	stwuct wegmap *wegmap;
	stwuct wegmap *peq_wegmap;
	stwuct wegmap *mbdwc_wegmap;
	u32 peq_biquad_gains[TEGWA210_PEQ_GAIN_PAWAM_SIZE_PEW_CH];
	u32 peq_biquad_shifts[TEGWA210_PEQ_SHIFT_PAWAM_SIZE_PEW_CH];
	unsigned int data_diw;
};

/* Extension of soc_bytes stwuctuwe defined in sound/soc.h */
stwuct tegwa_soc_bytes {
	stwuct soc_bytes soc;
	u32 shift; /* Used as offset fow AHUB WAM wewated pwogwaming */
};

/* Utiwity stwuctuwes fow using mixew contwow of type snd_soc_bytes */
#define TEGWA_SOC_BYTES_EXT(xname, xbase, xwegs, xshift, xmask,		\
			    xhandwew_get, xhandwew_put, xinfo)		\
{									\
	.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,				\
	.name	= xname,						\
	.info	= xinfo,						\
	.get	= xhandwew_get,						\
	.put	= xhandwew_put,						\
	.pwivate_vawue = ((unsigned wong)&(stwuct tegwa_soc_bytes)	\
	{								\
		.soc.base	= xbase,				\
		.soc.num_wegs	= xwegs,				\
		.soc.mask	= xmask,				\
		.shift		= xshift				\
	})								\
}

#endif
