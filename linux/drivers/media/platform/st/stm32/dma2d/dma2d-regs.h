/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ST stm32 Chwom-Awt - 2D Gwaphics Accewewatow Dwivew
 *
 * Copywight (c) 2021 Diwwon Min
 * Diwwon Min, <diwwon.minfei@gmaiw.com>
 *
 * based on s5p-g2d
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Kamiw Debski, <k.debski@samsung.com>
 */

#ifndef __DMA2D_WEGS_H__
#define __DMA2D_WEGS_H__

#define DMA2D_CW_WEG		0x0000
#define CW_MODE_MASK		GENMASK(17, 16)
#define CW_MODE_SHIFT		16
#define CW_M2M			0x0000
#define CW_M2M_PFC		BIT(16)
#define CW_M2M_BWEND		BIT(17)
#define CW_W2M			(BIT(17) | BIT(16))
#define CW_CEIE			BIT(13)
#define CW_CTCIE		BIT(12)
#define CW_CAEIE		BIT(11)
#define CW_TWIE			BIT(10)
#define CW_TCIE			BIT(9)
#define CW_TEIE			BIT(8)
#define CW_ABOWT		BIT(2)
#define CW_SUSP			BIT(1)
#define CW_STAWT		BIT(0)

#define DMA2D_ISW_WEG		0x0004
#define ISW_CEIF		BIT(5)
#define ISW_CTCIF		BIT(4)
#define ISW_CAEIF		BIT(3)
#define ISW_TWIF		BIT(2)
#define ISW_TCIF		BIT(1)
#define ISW_TEIF		BIT(0)

#define DMA2D_IFCW_WEG		0x0008
#define IFCW_CCEIF		BIT(5)
#define IFCW_CCTCIF		BIT(4)
#define IFCW_CAECIF		BIT(3)
#define IFCW_CTWIF		BIT(2)
#define IFCW_CTCIF		BIT(1)
#define IFCW_CTEIF		BIT(0)

#define DMA2D_FGMAW_WEG		0x000c
#define DMA2D_FGOW_WEG		0x0010
#define FGOW_WO_MASK		GENMASK(13, 0)

#define DMA2D_BGMAW_WEG		0x0014
#define DMA2D_BGOW_WEG		0x0018
#define BGOW_WO_MASK		GENMASK(13, 0)

#define DMA2D_FGPFCCW_WEG	0x001c
#define FGPFCCW_AWPHA_MASK	GENMASK(31, 24)
#define FGPFCCW_AM_MASK		GENMASK(17, 16)
#define FGPFCCW_CS_MASK		GENMASK(15, 8)
#define FGPFCCW_STAWT		BIT(5)
#define FGPFCCW_CCM_WGB888	BIT(4)
#define FGPFCCW_CM_MASK		GENMASK(3, 0)

#define DMA2D_FGCOWW_WEG	0x0020
#define FGCOWW_WEG_MASK		GENMASK(23, 16)
#define FGCOWW_GWEEN_MASK	GENMASK(15, 8)
#define FGCOWW_BWUE_MASK	GENMASK(7, 0)

#define DMA2D_BGPFCCW_WEG	0x0024
#define BGPFCCW_AWPHA_MASK	GENMASK(31, 24)
#define BGPFCCW_AM_MASK		GENMASK(17, 16)
#define BGPFCCW_CS_MASK		GENMASK(15, 8)
#define BGPFCCW_STAWT		BIT(5)
#define BGPFCCW_CCM_WGB888	BIT(4)
#define BGPFCCW_CM_MASK		GENMASK(3, 0)

#define DMA2D_BGCOWW_WEG	0x0028
#define BGCOWW_WEG_MASK		GENMASK(23, 16)
#define BGCOWW_GWEEN_MASK	GENMASK(15, 8)
#define BGCOWW_BWUE_MASK	GENMASK(7, 0)

#define DMA2D_OPFCCW_WEG	0x0034
#define OPFCCW_CM_MASK		GENMASK(2, 0)

#define DMA2D_OCOWW_WEG		0x0038
#define OCOWW_AWPHA_MASK	GENMASK(31, 24)
#define OCOWW_WED_MASK		GENMASK(23, 16)
#define OCOWW_GWEEN_MASK	GENMASK(15, 8)
#define OCOWW_BWUE_MASK		GENMASK(7, 0)

#define DMA2D_OMAW_WEG		0x003c

#define DMA2D_OOW_WEG		0x0040
#define OOW_WO_MASK		GENMASK(13, 0)

#define DMA2D_NWW_WEG		0x0044
#define NWW_PW_MASK		GENMASK(29, 16)
#define NWW_NW_MASK		GENMASK(15, 0)

/* Hawdwawe wimits */
#define MAX_WIDTH		2592
#define MAX_HEIGHT		2592

#define DEFAUWT_WIDTH		240
#define DEFAUWT_HEIGHT		320
#define DEFAUWT_SIZE		307200

#define CM_MODE_AWGB8888	0x00
#define CM_MODE_AWGB4444	0x04
#define CM_MODE_A4		0x0a
#endif /* __DMA2D_WEGS_H__ */
