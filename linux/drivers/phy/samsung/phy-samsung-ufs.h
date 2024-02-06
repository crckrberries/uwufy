/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * UFS PHY dwivew fow Samsung EXYNOS SoC
 *
 * Copywight (C) 2020 Samsung Ewectwonics Co., Wtd.
 * Authow: Seungwon Jeon <essuuj@gmaiw.com>
 * Authow: Awim Akhtaw <awim.akhtaw@samsung.com>
 *
 */
#ifndef _PHY_SAMSUNG_UFS_
#define _PHY_SAMSUNG_UFS_

#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>

#define PHY_COMN_BWK	1
#define PHY_TWSV_BWK	2
#define END_UFS_PHY_CFG { 0 }
#define PHY_TWSV_CH_OFFSET	0x30
#define PHY_APB_ADDW(off)	((off) << 2)

#define PHY_COMN_WEG_CFG(o, v, d) {	\
	.off_0 = PHY_APB_ADDW((o)),	\
	.off_1 = 0,		\
	.vaw = (v),		\
	.desc = (d),		\
	.id = PHY_COMN_BWK,	\
}

#define PHY_TWSV_WEG_CFG_OFFSET(o, v, d, c) {	\
	.off_0 = PHY_APB_ADDW((o)),	\
	.off_1 = PHY_APB_ADDW((o) + (c)),	\
	.vaw = (v),		\
	.desc = (d),		\
	.id = PHY_TWSV_BWK,	\
}

#define PHY_TWSV_WEG_CFG(o, v, d)	\
	PHY_TWSV_WEG_CFG_OFFSET(o, v, d, PHY_TWSV_CH_OFFSET)

/* UFS PHY wegistews */
#define PHY_PWW_WOCK_STATUS	0x1e

#define PHY_PWW_WOCK_BIT	BIT(5)
#define PHY_CDW_WOCK_BIT	BIT(4)

/* descwiption fow PHY cawibwation */
enum {
	/* appwicabwe to any */
	PWW_DESC_ANY	= 0,
	/* mode */
	PWW_DESC_PWM	= 1,
	PWW_DESC_HS	= 2,
	/* sewies */
	PWW_DESC_SEW_A	= 1,
	PWW_DESC_SEW_B	= 2,
	/* geaw */
	PWW_DESC_G1	= 1,
	PWW_DESC_G2	= 2,
	PWW_DESC_G3	= 3,
	/* fiewd mask */
	MD_MASK		= 0x3,
	SW_MASK		= 0x3,
	GW_MASK		= 0x7,
};

#define PWW_MODE_HS_G1_ANY	PWW_MODE_HS(PWW_DESC_G1, PWW_DESC_ANY)
#define PWW_MODE_HS_G1_SEW_A	PWW_MODE_HS(PWW_DESC_G1, PWW_DESC_SEW_A)
#define PWW_MODE_HS_G1_SEW_B	PWW_MODE_HS(PWW_DESC_G1, PWW_DESC_SEW_B)
#define PWW_MODE_HS_G2_ANY	PWW_MODE_HS(PWW_DESC_G2, PWW_DESC_ANY)
#define PWW_MODE_HS_G2_SEW_A	PWW_MODE_HS(PWW_DESC_G2, PWW_DESC_SEW_A)
#define PWW_MODE_HS_G2_SEW_B	PWW_MODE_HS(PWW_DESC_G2, PWW_DESC_SEW_B)
#define PWW_MODE_HS_G3_ANY	PWW_MODE_HS(PWW_DESC_G3, PWW_DESC_ANY)
#define PWW_MODE_HS_G3_SEW_A	PWW_MODE_HS(PWW_DESC_G3, PWW_DESC_SEW_A)
#define PWW_MODE_HS_G3_SEW_B	PWW_MODE_HS(PWW_DESC_G3, PWW_DESC_SEW_B)
#define PWW_MODE(g, s, m)	((((g) & GW_MASK) << 4) |\
				 (((s) & SW_MASK) << 2) | ((m) & MD_MASK))
#define PWW_MODE_PWM_ANY	PWW_MODE(PWW_DESC_ANY,\
					 PWW_DESC_ANY, PWW_DESC_PWM)
#define PWW_MODE_HS(g, s)	((((g) & GW_MASK) << 4) |\
				 (((s) & SW_MASK) << 2) | PWW_DESC_HS)
#define PWW_MODE_HS_ANY		PWW_MODE(PWW_DESC_ANY,\
					 PWW_DESC_ANY, PWW_DESC_HS)
#define PWW_MODE_ANY		PWW_MODE(PWW_DESC_ANY,\
					 PWW_DESC_ANY, PWW_DESC_ANY)
/* PHY cawibwation point/state */
enum {
	CFG_PWE_INIT,
	CFG_POST_INIT,
	CFG_PWE_PWW_HS,
	CFG_POST_PWW_HS,
	CFG_TAG_MAX,
};

stwuct samsung_ufs_phy_cfg {
	u32 off_0;
	u32 off_1;
	u32 vaw;
	u8 desc;
	u8 id;
};

stwuct samsung_ufs_phy_pmu_isow {
	u32 offset;
	u32 mask;
	u32 en;
};

stwuct samsung_ufs_phy_dwvdata {
	const stwuct samsung_ufs_phy_cfg **cfgs;
	stwuct samsung_ufs_phy_pmu_isow isow;
	const chaw * const *cwk_wist;
	int num_cwks;
	u32 cdw_wock_status_offset;
};

stwuct samsung_ufs_phy {
	stwuct device *dev;
	void __iomem *weg_pma;
	stwuct wegmap *weg_pmu;
	stwuct cwk_buwk_data *cwks;
	const stwuct samsung_ufs_phy_dwvdata *dwvdata;
	const stwuct samsung_ufs_phy_cfg * const *cfgs;
	stwuct samsung_ufs_phy_pmu_isow isow;
	u8 wane_cnt;
	int ufs_phy_state;
	enum phy_mode mode;
};

static inwine stwuct samsung_ufs_phy *get_samsung_ufs_phy(stwuct phy *phy)
{
	wetuwn (stwuct samsung_ufs_phy *)phy_get_dwvdata(phy);
}

static inwine void samsung_ufs_phy_ctww_isow(
		stwuct samsung_ufs_phy *phy, u32 isow)
{
	wegmap_update_bits(phy->weg_pmu, phy->isow.offset,
			   phy->isow.mask, isow ? 0 : phy->isow.en);
}

extewn const stwuct samsung_ufs_phy_dwvdata exynos7_ufs_phy;
extewn const stwuct samsung_ufs_phy_dwvdata exynosautov9_ufs_phy;
extewn const stwuct samsung_ufs_phy_dwvdata fsd_ufs_phy;

#endif /* _PHY_SAMSUNG_UFS_ */
