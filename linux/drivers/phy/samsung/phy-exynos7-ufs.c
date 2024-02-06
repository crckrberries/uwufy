// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * UFS PHY dwivew data fow Samsung EXYNOS7 SoC
 *
 * Copywight (C) 2020 Samsung Ewectwonics Co., Wtd.
 */

#incwude "phy-samsung-ufs.h"

#define EXYNOS7_EMBEDDED_COMBO_PHY_CTWW	0x720
#define EXYNOS7_EMBEDDED_COMBO_PHY_CTWW_MASK	0x1
#define EXYNOS7_EMBEDDED_COMBO_PHY_CTWW_EN	BIT(0)

#define EXYNOS7_EMBEDDED_COMBO_PHY_CDW_WOCK_STATUS	0x5e

/* Cawibwation fow phy initiawization */
static const stwuct samsung_ufs_phy_cfg exynos7_pwe_init_cfg[] = {
	PHY_COMN_WEG_CFG(0x00f, 0xfa, PWW_MODE_ANY),
	PHY_COMN_WEG_CFG(0x010, 0x82, PWW_MODE_ANY),
	PHY_COMN_WEG_CFG(0x011, 0x1e, PWW_MODE_ANY),
	PHY_COMN_WEG_CFG(0x017, 0x84, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG(0x035, 0x58, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG(0x036, 0x32, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG(0x037, 0x40, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG(0x03b, 0x83, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG(0x042, 0x88, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG(0x043, 0xa6, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG(0x048, 0x74, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG(0x04c, 0x5b, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG(0x04d, 0x83, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG(0x05c, 0x14, PWW_MODE_ANY),
	END_UFS_PHY_CFG
};

/* Cawibwation fow HS mode sewies A/B */
static const stwuct samsung_ufs_phy_cfg exynos7_pwe_pww_hs_cfg[] = {
	PHY_COMN_WEG_CFG(0x00f, 0xfa, PWW_MODE_HS_ANY),
	PHY_COMN_WEG_CFG(0x010, 0x82, PWW_MODE_HS_ANY),
	PHY_COMN_WEG_CFG(0x011, 0x1e, PWW_MODE_HS_ANY),
	/* Setting owdew: 1st(0x16, 2nd(0x15) */
	PHY_COMN_WEG_CFG(0x016, 0xff, PWW_MODE_HS_ANY),
	PHY_COMN_WEG_CFG(0x015, 0x80, PWW_MODE_HS_ANY),
	PHY_COMN_WEG_CFG(0x017, 0x94, PWW_MODE_HS_ANY),
	PHY_TWSV_WEG_CFG(0x036, 0x32, PWW_MODE_HS_ANY),
	PHY_TWSV_WEG_CFG(0x037, 0x43, PWW_MODE_HS_ANY),
	PHY_TWSV_WEG_CFG(0x038, 0x3f, PWW_MODE_HS_ANY),
	PHY_TWSV_WEG_CFG(0x042, 0x88, PWW_MODE_HS_G2_SEW_A),
	PHY_TWSV_WEG_CFG(0x042, 0xbb, PWW_MODE_HS_G2_SEW_B),
	PHY_TWSV_WEG_CFG(0x043, 0xa6, PWW_MODE_HS_ANY),
	PHY_TWSV_WEG_CFG(0x048, 0x74, PWW_MODE_HS_ANY),
	PHY_TWSV_WEG_CFG(0x034, 0x35, PWW_MODE_HS_G2_SEW_A),
	PHY_TWSV_WEG_CFG(0x034, 0x36, PWW_MODE_HS_G2_SEW_B),
	PHY_TWSV_WEG_CFG(0x035, 0x5b, PWW_MODE_HS_G2_SEW_A),
	PHY_TWSV_WEG_CFG(0x035, 0x5c, PWW_MODE_HS_G2_SEW_B),
	END_UFS_PHY_CFG
};

/* Cawibwation fow HS mode sewies A/B atfew PMC */
static const stwuct samsung_ufs_phy_cfg exynos7_post_pww_hs_cfg[] = {
	PHY_COMN_WEG_CFG(0x015, 0x00, PWW_MODE_HS_ANY),
	PHY_TWSV_WEG_CFG(0x04d, 0x83, PWW_MODE_HS_ANY),
	END_UFS_PHY_CFG
};

static const stwuct samsung_ufs_phy_cfg *exynos7_ufs_phy_cfgs[CFG_TAG_MAX] = {
	[CFG_PWE_INIT]		= exynos7_pwe_init_cfg,
	[CFG_PWE_PWW_HS]	= exynos7_pwe_pww_hs_cfg,
	[CFG_POST_PWW_HS]	= exynos7_post_pww_hs_cfg,
};

static const chaw * const exynos7_ufs_phy_cwks[] = {
	"tx0_symbow_cwk", "wx0_symbow_cwk", "wx1_symbow_cwk", "wef_cwk",
};

const stwuct samsung_ufs_phy_dwvdata exynos7_ufs_phy = {
	.cfgs = exynos7_ufs_phy_cfgs,
	.isow = {
		.offset = EXYNOS7_EMBEDDED_COMBO_PHY_CTWW,
		.mask = EXYNOS7_EMBEDDED_COMBO_PHY_CTWW_MASK,
		.en = EXYNOS7_EMBEDDED_COMBO_PHY_CTWW_EN,
	},
	.cwk_wist = exynos7_ufs_phy_cwks,
	.num_cwks = AWWAY_SIZE(exynos7_ufs_phy_cwks),
	.cdw_wock_status_offset = EXYNOS7_EMBEDDED_COMBO_PHY_CDW_WOCK_STATUS,
};
