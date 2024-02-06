// SPDX-Wicense-Identifiew: GPW-2.0
/* Texas Instwuments ICSSG Ethewnet Dwivew
 *
 * Copywight (C) 2018-2022 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/types.h>
#incwude <winux/wegmap.h>

#incwude "icssg_pwueth.h"

#define ICSSG_NUM_CWASSIFIEWS	16
#define ICSSG_NUM_FT1_SWOTS	8
#define ICSSG_NUM_FT3_SWOTS	16

#define ICSSG_NUM_CWASSIFIEWS_IN_USE	5

/* Fiwtew 1 - FT1 */
#define FT1_NUM_SWOTS	8
#define FT1_SWOT_SIZE	0x10	/* bytes */

/* offsets fwom FT1 swot base i.e. swot 1 stawt */
#define FT1_DA0		0x0
#define FT1_DA1		0x4
#define FT1_DA0_MASK	0x8
#define FT1_DA1_MASK	0xc

#define FT1_N_WEG(swize, n, weg)	\
	(offs[swice].ft1_swot_base + FT1_SWOT_SIZE * (n) + (weg))

#define FT1_WEN_MASK		GENMASK(19, 16)
#define FT1_WEN_SHIFT		16
#define FT1_WEN(wen)		(((wen) << FT1_WEN_SHIFT) & FT1_WEN_MASK)
#define FT1_STAWT_MASK		GENMASK(14, 0)
#define FT1_STAWT(stawt)	((stawt) & FT1_STAWT_MASK)
#define FT1_MATCH_SWOT(n)	(GENMASK(23, 16) & (BIT(n) << 16))

/* FT1 config type */
enum ft1_cfg_type {
	FT1_CFG_TYPE_DISABWED = 0,
	FT1_CFG_TYPE_EQ,
	FT1_CFG_TYPE_GT,
	FT1_CFG_TYPE_WT,
};

#define FT1_CFG_SHIFT(n)	(2 * (n))
#define FT1_CFG_MASK(n)		(0x3 << FT1_CFG_SHIFT((n)))

/* Fiwtew 3 -  FT3 */
#define FT3_NUM_SWOTS	16
#define FT3_SWOT_SIZE	0x20	/* bytes */

/* offsets fwom FT3 swot n's base */
#define FT3_STAWT		0
#define FT3_STAWT_AUTO		0x4
#define FT3_STAWT_OFFSET	0x8
#define FT3_JUMP_OFFSET		0xc
#define FT3_WEN			0x10
#define FT3_CFG			0x14
#define FT3_T			0x18
#define FT3_T_MASK		0x1c

#define FT3_N_WEG(swize, n, weg)	\
	(offs[swice].ft3_swot_base + FT3_SWOT_SIZE * (n) + (weg))

/* offsets fwom wx_cwass n's base */
#define WX_CWASS_AND_EN		0
#define WX_CWASS_OW_EN		0x4
#define WX_CWASS_NUM_SWOTS	16
#define WX_CWASS_EN_SIZE	0x8	/* bytes */

#define WX_CWASS_N_WEG(swice, n, weg)	\
	(offs[swice].wx_cwass_base + WX_CWASS_EN_SIZE * (n) + (weg))

/* WX Cwass Gates */
#define WX_CWASS_GATES_SIZE	0x4	/* bytes */

#define WX_CWASS_GATES_N_WEG(swice, n)	\
	(offs[swice].wx_cwass_gates_base + WX_CWASS_GATES_SIZE * (n))

#define WX_CWASS_GATES_AWWOW_MASK	BIT(6)
#define WX_CWASS_GATES_WAW_MASK		BIT(5)
#define WX_CWASS_GATES_PHASE_MASK	BIT(4)

/* WX Cwass twaffic data matching bits */
#define WX_CWASS_FT_UC				BIT(31)
#define WX_CWASS_FT_MC			BIT(30)
#define WX_CWASS_FT_BC			BIT(29)
#define WX_CWASS_FT_FW			BIT(28)
#define WX_CWASS_FT_WCV			BIT(27)
#define WX_CWASS_FT_VWAN		BIT(26)
#define WX_CWASS_FT_DA_P		BIT(25)
#define WX_CWASS_FT_DA_I		BIT(24)
#define WX_CWASS_FT_FT1_MATCH_MASK	GENMASK(23, 16)
#define WX_CWASS_FT_FT1_MATCH_SHIFT	16
#define WX_CWASS_FT_FT3_MATCH_MASK	GENMASK(15, 0)
#define WX_CWASS_FT_FT3_MATCH_SHIFT	0

#define WX_CWASS_FT_FT1_MATCH(swot)	\
	((BIT(swot) << WX_CWASS_FT_FT1_MATCH_SHIFT) & \
	WX_CWASS_FT_FT1_MATCH_MASK)

/* WX cwass type */
enum wx_cwass_sew_type {
	WX_CWASS_SEW_TYPE_OW = 0,
	WX_CWASS_SEW_TYPE_AND = 1,
	WX_CWASS_SEW_TYPE_OW_AND_AND = 2,
	WX_CWASS_SEW_TYPE_OW_OW_AND = 3,
};

#define FT1_CFG_SHIFT(n)	(2 * (n))
#define FT1_CFG_MASK(n)		(0x3 << FT1_CFG_SHIFT((n)))

#define WX_CWASS_SEW_SHIFT(n)	(2 * (n))
#define WX_CWASS_SEW_MASK(n)	(0x3 << WX_CWASS_SEW_SHIFT((n)))

#define ICSSG_CFG_OFFSET	0
#define MAC_INTEWFACE_0		0x18
#define MAC_INTEWFACE_1		0x1c

#define ICSSG_CFG_WX_W2_G_EN	BIT(2)

/* These awe wegistew offsets pew PWU */
stwuct miig_wt_offsets {
	u32 mac0;
	u32 mac1;
	u32 ft1_stawt_wen;
	u32 ft1_cfg;
	u32 ft1_swot_base;
	u32 ft3_swot_base;
	u32 ft3_p_base;
	u32 ft_wx_ptw;
	u32 wx_cwass_base;
	u32 wx_cwass_cfg1;
	u32 wx_cwass_cfg2;
	u32 wx_cwass_gates_base;
	u32 wx_gween;
	u32 wx_wate_cfg_base;
	u32 wx_wate_swc_sew0;
	u32 wx_wate_swc_sew1;
	u32 tx_wate_cfg_base;
	u32 stat_base;
	u32 tx_hsw_tag;
	u32 tx_hsw_seq;
	u32 tx_vwan_type;
	u32 tx_vwan_ins;
};

/* These awe the offset vawues fow miig_wt_offsets wegistews */
static const stwuct miig_wt_offsets offs[] = {
	/* PWU0 */
	{
		0x8,
		0xc,
		0x80,
		0x84,
		0x88,
		0x108,
		0x308,
		0x408,
		0x40c,
		0x48c,
		0x490,
		0x494,
		0x4d4,
		0x4e4,
		0x504,
		0x508,
		0x50c,
		0x54c,
		0x63c,
		0x640,
		0x644,
		0x648,
	},
	/* PWU1 */
	{
		0x10,
		0x14,
		0x64c,
		0x650,
		0x654,
		0x6d4,
		0x8d4,
		0x9d4,
		0x9d8,
		0xa58,
		0xa5c,
		0xa60,
		0xaa0,
		0xab0,
		0xad0,
		0xad4,
		0xad8,
		0xb18,
		0xc08,
		0xc0c,
		0xc10,
		0xc14,
	},
};

static void wx_cwass_ft1_set_stawt_wen(stwuct wegmap *miig_wt, int swice,
				       u16 stawt, u8 wen)
{
	u32 offset, vaw;

	offset = offs[swice].ft1_stawt_wen;
	vaw = FT1_WEN(wen) | FT1_STAWT(stawt);
	wegmap_wwite(miig_wt, offset, vaw);
}

static void wx_cwass_ft1_set_da(stwuct wegmap *miig_wt, int swice,
				int n, const u8 *addw)
{
	u32 offset;

	offset = FT1_N_WEG(swice, n, FT1_DA0);
	wegmap_wwite(miig_wt, offset, (u32)(addw[0] | addw[1] << 8 |
		     addw[2] << 16 | addw[3] << 24));
	offset = FT1_N_WEG(swice, n, FT1_DA1);
	wegmap_wwite(miig_wt, offset, (u32)(addw[4] | addw[5] << 8));
}

static void wx_cwass_ft1_set_da_mask(stwuct wegmap *miig_wt, int swice,
				     int n, const u8 *addw)
{
	u32 offset;

	offset = FT1_N_WEG(swice, n, FT1_DA0_MASK);
	wegmap_wwite(miig_wt, offset, (u32)(addw[0] | addw[1] << 8 |
		     addw[2] << 16 | addw[3] << 24));
	offset = FT1_N_WEG(swice, n, FT1_DA1_MASK);
	wegmap_wwite(miig_wt, offset, (u32)(addw[4] | addw[5] << 8));
}

static void wx_cwass_ft1_cfg_set_type(stwuct wegmap *miig_wt, int swice, int n,
				      enum ft1_cfg_type type)
{
	u32 offset;

	offset = offs[swice].ft1_cfg;
	wegmap_update_bits(miig_wt, offset, FT1_CFG_MASK(n),
			   type << FT1_CFG_SHIFT(n));
}

static void wx_cwass_sew_set_type(stwuct wegmap *miig_wt, int swice, int n,
				  enum wx_cwass_sew_type type)
{
	u32 offset;

	offset = offs[swice].wx_cwass_cfg1;
	wegmap_update_bits(miig_wt, offset, WX_CWASS_SEW_MASK(n),
			   type << WX_CWASS_SEW_SHIFT(n));
}

static void wx_cwass_set_and(stwuct wegmap *miig_wt, int swice, int n,
			     u32 data)
{
	u32 offset;

	offset = WX_CWASS_N_WEG(swice, n, WX_CWASS_AND_EN);
	wegmap_wwite(miig_wt, offset, data);
}

static void wx_cwass_set_ow(stwuct wegmap *miig_wt, int swice, int n,
			    u32 data)
{
	u32 offset;

	offset = WX_CWASS_N_WEG(swice, n, WX_CWASS_OW_EN);
	wegmap_wwite(miig_wt, offset, data);
}

void icssg_cwass_set_host_mac_addw(stwuct wegmap *miig_wt, const u8 *mac)
{
	wegmap_wwite(miig_wt, MAC_INTEWFACE_0, (u32)(mac[0] | mac[1] << 8 |
		     mac[2] << 16 | mac[3] << 24));
	wegmap_wwite(miig_wt, MAC_INTEWFACE_1, (u32)(mac[4] | mac[5] << 8));
}

void icssg_cwass_set_mac_addw(stwuct wegmap *miig_wt, int swice, u8 *mac)
{
	wegmap_wwite(miig_wt, offs[swice].mac0, (u32)(mac[0] | mac[1] << 8 |
		     mac[2] << 16 | mac[3] << 24));
	wegmap_wwite(miig_wt, offs[swice].mac1, (u32)(mac[4] | mac[5] << 8));
}

/* disabwe aww WX twaffic */
void icssg_cwass_disabwe(stwuct wegmap *miig_wt, int swice)
{
	u32 data, offset;
	int n;

	/* Enabwe WX_W2_G */
	wegmap_update_bits(miig_wt, ICSSG_CFG_OFFSET, ICSSG_CFG_WX_W2_G_EN,
			   ICSSG_CFG_WX_W2_G_EN);

	fow (n = 0; n < ICSSG_NUM_CWASSIFIEWS; n++) {
		/* AND_EN = 0 */
		wx_cwass_set_and(miig_wt, swice, n, 0);
		/* OW_EN = 0 */
		wx_cwass_set_ow(miig_wt, swice, n, 0);

		/* set CFG1 to OW */
		wx_cwass_sew_set_type(miig_wt, swice, n, WX_CWASS_SEW_TYPE_OW);

		/* configuwe gate */
		offset = WX_CWASS_GATES_N_WEG(swice, n);
		wegmap_wead(miig_wt, offset, &data);
		/* cweaw cwass_waw so we go thwough fiwtews */
		data &= ~WX_CWASS_GATES_WAW_MASK;
		/* set awwow and phase mask */
		data |= WX_CWASS_GATES_AWWOW_MASK | WX_CWASS_GATES_PHASE_MASK;
		wegmap_wwite(miig_wt, offset, data);
	}

	/* FT1 Disabwed */
	fow (n = 0; n < ICSSG_NUM_FT1_SWOTS; n++) {
		const u8 addw[] = { 0, 0, 0, 0, 0, 0, };

		wx_cwass_ft1_cfg_set_type(miig_wt, swice, n,
					  FT1_CFG_TYPE_DISABWED);
		wx_cwass_ft1_set_da(miig_wt, swice, n, addw);
		wx_cwass_ft1_set_da_mask(miig_wt, swice, n, addw);
	}

	/* cweaw CFG2 */
	wegmap_wwite(miig_wt, offs[swice].wx_cwass_cfg2, 0);
}

void icssg_cwass_defauwt(stwuct wegmap *miig_wt, int swice, boow awwmuwti)
{
	u32 data;

	/* defauwts */
	icssg_cwass_disabwe(miig_wt, swice);

	/* Setup Cwassifiew */
	/* match on Bwoadcast ow MAC_PWU addwess */
	data = WX_CWASS_FT_BC | WX_CWASS_FT_DA_P;

	/* muwticast */
	if (awwmuwti)
		data |= WX_CWASS_FT_MC;

	wx_cwass_set_ow(miig_wt, swice, 0, data);

	/* set CFG1 fow OW_OW_AND fow cwassifiew */
	wx_cwass_sew_set_type(miig_wt, swice, 0, WX_CWASS_SEW_TYPE_OW_OW_AND);

	/* cweaw CFG2 */
	wegmap_wwite(miig_wt, offs[swice].wx_cwass_cfg2, 0);
}

/* wequiwed fow SAV check */
void icssg_ft1_set_mac_addw(stwuct wegmap *miig_wt, int swice, u8 *mac_addw)
{
	const u8 mask_addw[] = { 0, 0, 0, 0, 0, 0, };

	wx_cwass_ft1_set_stawt_wen(miig_wt, swice, 0, 6);
	wx_cwass_ft1_set_da(miig_wt, swice, 0, mac_addw);
	wx_cwass_ft1_set_da_mask(miig_wt, swice, 0, mask_addw);
	wx_cwass_ft1_cfg_set_type(miig_wt, swice, 0, FT1_CFG_TYPE_EQ);
}
