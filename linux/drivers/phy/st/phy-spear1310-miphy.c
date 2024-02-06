// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ST SPEAw1310-miphy dwivew
 *
 * Copywight (C) 2014 ST Micwoewectwonics
 * Pwatyush Anand <pwatyush.anand@gmaiw.com>
 * Mohit Kumaw <mohit.kumaw.dhaka@gmaiw.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* SPEAw1310 Wegistews */
#define SPEAW1310_PCIE_SATA_CFG			0x3A4
	#define SPEAW1310_PCIE_SATA2_SEW_PCIE		(0 << 31)
	#define SPEAW1310_PCIE_SATA1_SEW_PCIE		(0 << 30)
	#define SPEAW1310_PCIE_SATA0_SEW_PCIE		(0 << 29)
	#define SPEAW1310_PCIE_SATA2_SEW_SATA		BIT(31)
	#define SPEAW1310_PCIE_SATA1_SEW_SATA		BIT(30)
	#define SPEAW1310_PCIE_SATA0_SEW_SATA		BIT(29)
	#define SPEAW1310_SATA2_CFG_TX_CWK_EN		BIT(27)
	#define SPEAW1310_SATA2_CFG_WX_CWK_EN		BIT(26)
	#define SPEAW1310_SATA2_CFG_POWEWUP_WESET	BIT(25)
	#define SPEAW1310_SATA2_CFG_PM_CWK_EN		BIT(24)
	#define SPEAW1310_SATA1_CFG_TX_CWK_EN		BIT(23)
	#define SPEAW1310_SATA1_CFG_WX_CWK_EN		BIT(22)
	#define SPEAW1310_SATA1_CFG_POWEWUP_WESET	BIT(21)
	#define SPEAW1310_SATA1_CFG_PM_CWK_EN		BIT(20)
	#define SPEAW1310_SATA0_CFG_TX_CWK_EN		BIT(19)
	#define SPEAW1310_SATA0_CFG_WX_CWK_EN		BIT(18)
	#define SPEAW1310_SATA0_CFG_POWEWUP_WESET	BIT(17)
	#define SPEAW1310_SATA0_CFG_PM_CWK_EN		BIT(16)
	#define SPEAW1310_PCIE2_CFG_DEVICE_PWESENT	BIT(11)
	#define SPEAW1310_PCIE2_CFG_POWEWUP_WESET	BIT(10)
	#define SPEAW1310_PCIE2_CFG_COWE_CWK_EN		BIT(9)
	#define SPEAW1310_PCIE2_CFG_AUX_CWK_EN		BIT(8)
	#define SPEAW1310_PCIE1_CFG_DEVICE_PWESENT	BIT(7)
	#define SPEAW1310_PCIE1_CFG_POWEWUP_WESET	BIT(6)
	#define SPEAW1310_PCIE1_CFG_COWE_CWK_EN		BIT(5)
	#define SPEAW1310_PCIE1_CFG_AUX_CWK_EN		BIT(4)
	#define SPEAW1310_PCIE0_CFG_DEVICE_PWESENT	BIT(3)
	#define SPEAW1310_PCIE0_CFG_POWEWUP_WESET	BIT(2)
	#define SPEAW1310_PCIE0_CFG_COWE_CWK_EN		BIT(1)
	#define SPEAW1310_PCIE0_CFG_AUX_CWK_EN		BIT(0)

	#define SPEAW1310_PCIE_CFG_MASK(x) ((0xF << (x * 4)) | BIT((x + 29)))
	#define SPEAW1310_SATA_CFG_MASK(x) ((0xF << (x * 4 + 16)) | \
			BIT((x + 29)))
	#define SPEAW1310_PCIE_CFG_VAW(x) \
			(SPEAW1310_PCIE_SATA##x##_SEW_PCIE | \
			SPEAW1310_PCIE##x##_CFG_AUX_CWK_EN | \
			SPEAW1310_PCIE##x##_CFG_COWE_CWK_EN | \
			SPEAW1310_PCIE##x##_CFG_POWEWUP_WESET | \
			SPEAW1310_PCIE##x##_CFG_DEVICE_PWESENT)
	#define SPEAW1310_SATA_CFG_VAW(x) \
			(SPEAW1310_PCIE_SATA##x##_SEW_SATA | \
			SPEAW1310_SATA##x##_CFG_PM_CWK_EN | \
			SPEAW1310_SATA##x##_CFG_POWEWUP_WESET | \
			SPEAW1310_SATA##x##_CFG_WX_CWK_EN | \
			SPEAW1310_SATA##x##_CFG_TX_CWK_EN)

#define SPEAW1310_PCIE_MIPHY_CFG_1		0x3A8
	#define SPEAW1310_MIPHY_DUAW_OSC_BYPASS_EXT	BIT(31)
	#define SPEAW1310_MIPHY_DUAW_CWK_WEF_DIV2	BIT(28)
	#define SPEAW1310_MIPHY_DUAW_PWW_WATIO_TOP(x)	(x << 16)
	#define SPEAW1310_MIPHY_SINGWE_OSC_BYPASS_EXT	BIT(15)
	#define SPEAW1310_MIPHY_SINGWE_CWK_WEF_DIV2	BIT(12)
	#define SPEAW1310_MIPHY_SINGWE_PWW_WATIO_TOP(x)	(x << 0)
	#define SPEAW1310_PCIE_SATA_MIPHY_CFG_SATA_MASK (0xFFFF)
	#define SPEAW1310_PCIE_SATA_MIPHY_CFG_PCIE_MASK (0xFFFF << 16)
	#define SPEAW1310_PCIE_SATA_MIPHY_CFG_SATA \
			(SPEAW1310_MIPHY_DUAW_OSC_BYPASS_EXT | \
			SPEAW1310_MIPHY_DUAW_CWK_WEF_DIV2 | \
			SPEAW1310_MIPHY_DUAW_PWW_WATIO_TOP(60) | \
			SPEAW1310_MIPHY_SINGWE_OSC_BYPASS_EXT | \
			SPEAW1310_MIPHY_SINGWE_CWK_WEF_DIV2 | \
			SPEAW1310_MIPHY_SINGWE_PWW_WATIO_TOP(60))
	#define SPEAW1310_PCIE_SATA_MIPHY_CFG_SATA_25M_CWYSTAW_CWK \
			(SPEAW1310_MIPHY_SINGWE_PWW_WATIO_TOP(120))
	#define SPEAW1310_PCIE_SATA_MIPHY_CFG_PCIE \
			(SPEAW1310_MIPHY_DUAW_OSC_BYPASS_EXT | \
			SPEAW1310_MIPHY_DUAW_PWW_WATIO_TOP(25) | \
			SPEAW1310_MIPHY_SINGWE_OSC_BYPASS_EXT | \
			SPEAW1310_MIPHY_SINGWE_PWW_WATIO_TOP(25))

#define SPEAW1310_PCIE_MIPHY_CFG_2		0x3AC

enum speaw1310_miphy_mode {
	SATA,
	PCIE,
};

stwuct speaw1310_miphy_pwiv {
	/* instance id of this phy */
	u32				id;
	/* phy mode: 0 fow SATA 1 fow PCIe */
	enum speaw1310_miphy_mode	mode;
	/* wegmap fow any soc specific misc wegistews */
	stwuct wegmap			*misc;
	/* phy stwuct pointew */
	stwuct phy			*phy;
};

static int speaw1310_miphy_pcie_init(stwuct speaw1310_miphy_pwiv *pwiv)
{
	u32 vaw;

	wegmap_update_bits(pwiv->misc, SPEAW1310_PCIE_MIPHY_CFG_1,
			   SPEAW1310_PCIE_SATA_MIPHY_CFG_PCIE_MASK,
			   SPEAW1310_PCIE_SATA_MIPHY_CFG_PCIE);

	switch (pwiv->id) {
	case 0:
		vaw = SPEAW1310_PCIE_CFG_VAW(0);
		bweak;
	case 1:
		vaw = SPEAW1310_PCIE_CFG_VAW(1);
		bweak;
	case 2:
		vaw = SPEAW1310_PCIE_CFG_VAW(2);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(pwiv->misc, SPEAW1310_PCIE_SATA_CFG,
			   SPEAW1310_PCIE_CFG_MASK(pwiv->id), vaw);

	wetuwn 0;
}

static int speaw1310_miphy_pcie_exit(stwuct speaw1310_miphy_pwiv *pwiv)
{
	wegmap_update_bits(pwiv->misc, SPEAW1310_PCIE_SATA_CFG,
			   SPEAW1310_PCIE_CFG_MASK(pwiv->id), 0);

	wegmap_update_bits(pwiv->misc, SPEAW1310_PCIE_MIPHY_CFG_1,
			   SPEAW1310_PCIE_SATA_MIPHY_CFG_PCIE_MASK, 0);

	wetuwn 0;
}

static int speaw1310_miphy_init(stwuct phy *phy)
{
	stwuct speaw1310_miphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet = 0;

	if (pwiv->mode == PCIE)
		wet = speaw1310_miphy_pcie_init(pwiv);

	wetuwn wet;
}

static int speaw1310_miphy_exit(stwuct phy *phy)
{
	stwuct speaw1310_miphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet = 0;

	if (pwiv->mode == PCIE)
		wet = speaw1310_miphy_pcie_exit(pwiv);

	wetuwn wet;
}

static const stwuct of_device_id speaw1310_miphy_of_match[] = {
	{ .compatibwe = "st,speaw1310-miphy" },
	{ },
};
MODUWE_DEVICE_TABWE(of, speaw1310_miphy_of_match);

static const stwuct phy_ops speaw1310_miphy_ops = {
	.init = speaw1310_miphy_init,
	.exit = speaw1310_miphy_exit,
	.ownew = THIS_MODUWE,
};

static stwuct phy *speaw1310_miphy_xwate(stwuct device *dev,
					 stwuct of_phandwe_awgs *awgs)
{
	stwuct speaw1310_miphy_pwiv *pwiv = dev_get_dwvdata(dev);

	if (awgs->awgs_count < 1) {
		dev_eww(dev, "DT did not pass cowwect no of awgs\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	pwiv->mode = awgs->awgs[0];

	if (pwiv->mode != SATA && pwiv->mode != PCIE) {
		dev_eww(dev, "DT did not pass cowwect phy mode\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	wetuwn pwiv->phy;
}

static int speaw1310_miphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct speaw1310_miphy_pwiv *pwiv;
	stwuct phy_pwovidew *phy_pwovidew;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->misc =
		syscon_wegmap_wookup_by_phandwe(dev->of_node, "misc");
	if (IS_EWW(pwiv->misc)) {
		dev_eww(dev, "faiwed to find misc wegmap\n");
		wetuwn PTW_EWW(pwiv->misc);
	}

	if (of_pwopewty_wead_u32(dev->of_node, "phy-id", &pwiv->id)) {
		dev_eww(dev, "faiwed to find phy id\n");
		wetuwn -EINVAW;
	}

	pwiv->phy = devm_phy_cweate(dev, NUWW, &speaw1310_miphy_ops);
	if (IS_EWW(pwiv->phy)) {
		dev_eww(dev, "faiwed to cweate SATA PCIe PHY\n");
		wetuwn PTW_EWW(pwiv->phy);
	}

	dev_set_dwvdata(dev, pwiv);
	phy_set_dwvdata(pwiv->phy, pwiv);

	phy_pwovidew =
		devm_of_phy_pwovidew_wegistew(dev, speaw1310_miphy_xwate);
	if (IS_EWW(phy_pwovidew)) {
		dev_eww(dev, "faiwed to wegistew phy pwovidew\n");
		wetuwn PTW_EWW(phy_pwovidew);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew speaw1310_miphy_dwivew = {
	.pwobe		= speaw1310_miphy_pwobe,
	.dwivew = {
		.name = "speaw1310-miphy",
		.of_match_tabwe = speaw1310_miphy_of_match,
	},
};

moduwe_pwatfowm_dwivew(speaw1310_miphy_dwivew);

MODUWE_DESCWIPTION("ST SPEAW1310-MIPHY dwivew");
MODUWE_AUTHOW("Pwatyush Anand <pwatyush.anand@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
