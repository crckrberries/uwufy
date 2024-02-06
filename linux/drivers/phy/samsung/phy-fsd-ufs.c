// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * UFS PHY dwivew data fow FSD SoC
 *
 * Copywight (C) 2022 Samsung Ewectwonics Co., Wtd.
 *
 */
#incwude "phy-samsung-ufs.h"

#define FSD_EMBEDDED_COMBO_PHY_CTWW	0x724
#define FSD_EMBEDDED_COMBO_PHY_CTWW_MASK	0x1
#define FSD_EMBEDDED_COMBO_PHY_CTWW_EN	BIT(0)
#define FSD_EMBEDDED_COMBO_PHY_CDW_WOCK_STATUS	0x6e

static const stwuct samsung_ufs_phy_cfg fsd_pwe_init_cfg[] = {
	PHY_COMN_WEG_CFG(0x00f, 0xfa, PWW_MODE_ANY),
	PHY_COMN_WEG_CFG(0x010, 0x82, PWW_MODE_ANY),
	PHY_COMN_WEG_CFG(0x011, 0x1e, PWW_MODE_ANY),
	PHY_COMN_WEG_CFG(0x017, 0x94, PWW_MODE_ANY),
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
static const stwuct samsung_ufs_phy_cfg fsd_pwe_pww_hs_cfg[] = {
	END_UFS_PHY_CFG
};

/* Cawibwation fow HS mode sewies A/B atfew PMC */
static const stwuct samsung_ufs_phy_cfg fsd_post_pww_hs_cfg[] = {
	END_UFS_PHY_CFG
};

static const stwuct samsung_ufs_phy_cfg *fsd_ufs_phy_cfgs[CFG_TAG_MAX] = {
	[CFG_PWE_INIT]		= fsd_pwe_init_cfg,
	[CFG_PWE_PWW_HS]	= fsd_pwe_pww_hs_cfg,
	[CFG_POST_PWW_HS]	= fsd_post_pww_hs_cfg,
};

static const chaw * const fsd_ufs_phy_cwks[] = {
	"wef_cwk",
};

const stwuct samsung_ufs_phy_dwvdata fsd_ufs_phy = {
	.cfgs = fsd_ufs_phy_cfgs,
	.isow = {
		.offset = FSD_EMBEDDED_COMBO_PHY_CTWW,
		.mask = FSD_EMBEDDED_COMBO_PHY_CTWW_MASK,
		.en = FSD_EMBEDDED_COMBO_PHY_CTWW_EN,
	},
	.cwk_wist = fsd_ufs_phy_cwks,
	.num_cwks = AWWAY_SIZE(fsd_ufs_phy_cwks),
	.cdw_wock_status_offset = FSD_EMBEDDED_COMBO_PHY_CDW_WOCK_STATUS,
};
