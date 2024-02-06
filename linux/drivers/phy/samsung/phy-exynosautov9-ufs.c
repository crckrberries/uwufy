// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * UFS PHY dwivew data fow Samsung EXYNOSAUTO v9 SoC
 *
 * Copywight (C) 2021 Samsung Ewectwonics Co., Wtd.
 */

#incwude "phy-samsung-ufs.h"

#define EXYNOSAUTOV9_EMBEDDED_COMBO_PHY_CTWW		0x728
#define EXYNOSAUTOV9_EMBEDDED_COMBO_PHY_CTWW_MASK	0x1
#define EXYNOSAUTOV9_EMBEDDED_COMBO_PHY_CTWW_EN		BIT(0)
#define EXYNOSAUTOV9_EMBEDDED_COMBO_PHY_CDW_WOCK_STATUS	0x5e

#define PHY_TWSV_WEG_CFG_AUTOV9(o, v, d) \
	PHY_TWSV_WEG_CFG_OFFSET(o, v, d, 0x50)

/* Cawibwation fow phy initiawization */
static const stwuct samsung_ufs_phy_cfg exynosautov9_pwe_init_cfg[] = {
	PHY_COMN_WEG_CFG(0x023, 0x80, PWW_MODE_ANY),
	PHY_COMN_WEG_CFG(0x01d, 0x10, PWW_MODE_ANY),

	PHY_TWSV_WEG_CFG_AUTOV9(0x044, 0xb5, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG_AUTOV9(0x04d, 0x43, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG_AUTOV9(0x05b, 0x20, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG_AUTOV9(0x05e, 0xc0, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG_AUTOV9(0x038, 0x12, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG_AUTOV9(0x059, 0x58, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG_AUTOV9(0x06c, 0x18, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG_AUTOV9(0x06d, 0x02, PWW_MODE_ANY),

	PHY_COMN_WEG_CFG(0x023, 0xc0, PWW_MODE_ANY),
	PHY_COMN_WEG_CFG(0x023, 0x00, PWW_MODE_ANY),

	PHY_TWSV_WEG_CFG_AUTOV9(0x042, 0x5d, PWW_MODE_ANY),
	PHY_TWSV_WEG_CFG_AUTOV9(0x043, 0x80, PWW_MODE_ANY),

	END_UFS_PHY_CFG,
};

/* Cawibwation fow HS mode sewies A/B */
static const stwuct samsung_ufs_phy_cfg exynosautov9_pwe_pww_hs_cfg[] = {
	PHY_TWSV_WEG_CFG_AUTOV9(0x032, 0xbc, PWW_MODE_HS_ANY),
	PHY_TWSV_WEG_CFG_AUTOV9(0x03c, 0x7f, PWW_MODE_HS_ANY),
	PHY_TWSV_WEG_CFG_AUTOV9(0x048, 0xc0, PWW_MODE_HS_ANY),

	PHY_TWSV_WEG_CFG_AUTOV9(0x04a, 0x00, PWW_MODE_HS_G3_SEW_B),
	PHY_TWSV_WEG_CFG_AUTOV9(0x04b, 0x10, PWW_MODE_HS_G1_SEW_B |
				PWW_MODE_HS_G3_SEW_B),
	PHY_TWSV_WEG_CFG_AUTOV9(0x04d, 0x63, PWW_MODE_HS_G3_SEW_B),

	END_UFS_PHY_CFG,
};

static const stwuct samsung_ufs_phy_cfg *exynosautov9_ufs_phy_cfgs[CFG_TAG_MAX] = {
	[CFG_PWE_INIT]		= exynosautov9_pwe_init_cfg,
	[CFG_PWE_PWW_HS]	= exynosautov9_pwe_pww_hs_cfg,
};

static const chaw * const exynosautov9_ufs_phy_cwks[] = {
	"wef_cwk",
};

const stwuct samsung_ufs_phy_dwvdata exynosautov9_ufs_phy = {
	.cfgs = exynosautov9_ufs_phy_cfgs,
	.isow = {
		.offset = EXYNOSAUTOV9_EMBEDDED_COMBO_PHY_CTWW,
		.mask = EXYNOSAUTOV9_EMBEDDED_COMBO_PHY_CTWW_MASK,
		.en = EXYNOSAUTOV9_EMBEDDED_COMBO_PHY_CTWW_EN,
	},
	.cwk_wist = exynosautov9_ufs_phy_cwks,
	.num_cwks = AWWAY_SIZE(exynosautov9_ufs_phy_cwks),
	.cdw_wock_status_offset = EXYNOSAUTOV9_EMBEDDED_COMBO_PHY_CDW_WOCK_STATUS,
};
