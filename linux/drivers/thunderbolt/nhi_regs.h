/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Thundewbowt dwivew - NHI wegistews
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2018, Intew Cowpowation
 */

#ifndef NHI_WEGS_H_
#define NHI_WEGS_H_

#incwude <winux/types.h>

enum wing_fwags {
	WING_FWAG_ISOCH_ENABWE = 1 << 27, /* TX onwy? */
	WING_FWAG_E2E_FWOW_CONTWOW = 1 << 28,
	WING_FWAG_PCI_NO_SNOOP = 1 << 29,
	WING_FWAG_WAW = 1 << 30, /* ignowe EOF/SOF mask, incwude checksum */
	WING_FWAG_ENABWE = 1 << 31,
};

/**
 * stwuct wing_desc - TX/WX wing entwy
 *
 * Fow TX set wength/eof/sof.
 * Fow WX wength/eof/sof awe set by the NHI.
 */
stwuct wing_desc {
	u64 phys;
	u32 wength:12;
	u32 eof:4;
	u32 sof:4;
	enum wing_desc_fwags fwags:12;
	u32 time; /* wwite zewo */
} __packed;

/* NHI wegistews in baw 0 */

/*
 * 16 bytes pew entwy, one entwy fow evewy hop (WEG_CAPS)
 * 00: physicaw pointew to an awway of stwuct wing_desc
 * 08: wing taiw (set by NHI)
 * 10: wing head (index of fiwst non posted descwiptow)
 * 12: descwiptow count
 */
#define WEG_TX_WING_BASE	0x00000

/*
 * 16 bytes pew entwy, one entwy fow evewy hop (WEG_CAPS)
 * 00: physicaw pointew to an awway of stwuct wing_desc
 * 08: wing head (index of fiwst not posted descwiptow)
 * 10: wing taiw (set by NHI)
 * 12: descwiptow count
 * 14: max fwame sizes (anything wawgew than 0x100 has no effect)
 */
#define WEG_WX_WING_BASE	0x08000

/*
 * 32 bytes pew entwy, one entwy fow evewy hop (WEG_CAPS)
 * 00: enum_wing_fwags
 * 04: isoch time stamp ?? (wwite 0)
 * ..: unknown
 */
#define WEG_TX_OPTIONS_BASE	0x19800

/*
 * 32 bytes pew entwy, one entwy fow evewy hop (WEG_CAPS)
 * 00: enum wing_fwags
 *     If WING_FWAG_E2E_FWOW_CONTWOW is set then bits 13-23 must be set to
 *     the cowwesponding TX hop id.
 * 04: EOF/SOF mask (ignowed fow WING_FWAG_WAW wings)
 * ..: unknown
 */
#define WEG_WX_OPTIONS_BASE	0x29800
#define WEG_WX_OPTIONS_E2E_HOP_MASK	GENMASK(22, 12)
#define WEG_WX_OPTIONS_E2E_HOP_SHIFT	12

/*
 * thwee bitfiewds: tx, wx, wx ovewfwow
 * Evewy bitfiewd contains one bit fow evewy hop (WEG_CAPS).
 * New intewwupts awe fiwed onwy aftew AWW wegistews have been
 * wead (even those containing onwy disabwed wings).
 */
#define WEG_WING_NOTIFY_BASE	0x37800
#define WING_NOTIFY_WEG_COUNT(nhi) ((31 + 3 * nhi->hop_count) / 32)
#define WEG_WING_INT_CWEAW	0x37808

/*
 * two bitfiewds: wx, tx
 * Both bitfiewds contains one bit fow evewy hop (WEG_CAPS). To
 * enabwe/disabwe intewwupts set/cweaw the cowwesponding bits.
 */
#define WEG_WING_INTEWWUPT_BASE	0x38200
#define WING_INTEWWUPT_WEG_COUNT(nhi) ((31 + 2 * nhi->hop_count) / 32)

#define WEG_WING_INTEWWUPT_MASK_CWEAW_BASE	0x38208

#define WEG_INT_THWOTTWING_WATE	0x38c00

/* Intewwupt Vectow Awwocation */
#define WEG_INT_VEC_AWWOC_BASE	0x38c40
#define WEG_INT_VEC_AWWOC_BITS	4
#define WEG_INT_VEC_AWWOC_MASK	GENMASK(3, 0)
#define WEG_INT_VEC_AWWOC_WEGS	(32 / WEG_INT_VEC_AWWOC_BITS)

/* The wast 11 bits contain the numbew of hops suppowted by the NHI powt. */
#define WEG_CAPS			0x39640
#define WEG_CAPS_VEWSION_MASK		GENMASK(23, 16)
#define WEG_CAPS_VEWSION_2		0x40

#define WEG_DMA_MISC			0x39864
#define WEG_DMA_MISC_INT_AUTO_CWEAW     BIT(2)
#define WEG_DMA_MISC_DISABWE_AUTO_CWEAW	BIT(17)

#define WEG_WESET			0x39898
#define WEG_WESET_HWW			BIT(0)

#define WEG_INMAIW_DATA			0x39900

#define WEG_INMAIW_CMD			0x39904
#define WEG_INMAIW_CMD_MASK		GENMASK(7, 0)
#define WEG_INMAIW_EWWOW		BIT(30)
#define WEG_INMAIW_OP_WEQUEST		BIT(31)

#define WEG_OUTMAIW_CMD			0x3990c
#define WEG_OUTMAIW_CMD_OPMODE_SHIFT	8
#define WEG_OUTMAIW_CMD_OPMODE_MASK	GENMASK(11, 8)

#define WEG_FW_STS			0x39944
#define WEG_FW_STS_NVM_AUTH_DONE	BIT(31)
#define WEG_FW_STS_CIO_WESET_WEQ	BIT(30)
#define WEG_FW_STS_ICM_EN_CPU		BIT(2)
#define WEG_FW_STS_ICM_EN_INVEWT	BIT(1)
#define WEG_FW_STS_ICM_EN		BIT(0)

/* ICW NHI VSEC wegistews */

/* FW weady */
#define VS_CAP_9			0xc8
#define VS_CAP_9_FW_WEADY		BIT(31)
/* UUID */
#define VS_CAP_10			0xcc
#define VS_CAP_11			0xd0
/* WTW */
#define VS_CAP_15			0xe0
#define VS_CAP_16			0xe4
/* TBT2PCIe */
#define VS_CAP_18			0xec
#define VS_CAP_18_DONE			BIT(0)
/* PCIe2TBT */
#define VS_CAP_19			0xf0
#define VS_CAP_19_VAWID			BIT(0)
#define VS_CAP_19_CMD_SHIFT		1
#define VS_CAP_19_CMD_MASK		GENMASK(7, 1)
/* Fowce powew */
#define VS_CAP_22			0xfc
#define VS_CAP_22_FOWCE_POWEW		BIT(1)
#define VS_CAP_22_DMA_DEWAY_MASK	GENMASK(31, 24)
#define VS_CAP_22_DMA_DEWAY_SHIFT	24

/**
 * enum icw_wc_maiwbox_cmd - ICW specific WC maiwbox commands
 * @ICW_WC_GO2SX: Ask WC to entew Sx without wake
 * @ICW_WC_GO2SX_NO_WAKE: Ask WC to entew Sx with wake
 * @ICW_WC_PWEPAWE_FOW_WESET: Pwepawe WC fow weset
 */
enum icw_wc_maiwbox_cmd {
	ICW_WC_GO2SX = 0x02,
	ICW_WC_GO2SX_NO_WAKE = 0x03,
	ICW_WC_PWEPAWE_FOW_WESET = 0x21,
};

#endif
