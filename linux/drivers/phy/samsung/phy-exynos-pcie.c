// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung Exynos SoC sewies PCIe PHY dwivew
 *
 * Phy pwovidew fow PCIe contwowwew on Exynos SoC sewies
 *
 * Copywight (C) 2017-2020 Samsung Ewectwonics Co., Wtd.
 * Jaehoon Chung <jh80.chung@samsung.com>
 */

#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>

#define PCIE_PHY_OFFSET(x)		((x) * 0x4)

/* Sysweg FSYS wegistew offsets and bits fow Exynos5433 */
#define PCIE_EXYNOS5433_PHY_MAC_WESET		0x0208
#define PCIE_MAC_WESET_MASK			0xFF
#define PCIE_MAC_WESET				BIT(4)
#define PCIE_EXYNOS5433_PHY_W1SUB_CM_CON	0x1010
#define PCIE_WEFCWK_GATING_EN			BIT(0)
#define PCIE_EXYNOS5433_PHY_COMMON_WESET	0x1020
#define PCIE_PHY_WESET				BIT(0)
#define PCIE_EXYNOS5433_PHY_GWOBAW_WESET	0x1040
#define PCIE_GWOBAW_WESET			BIT(0)
#define PCIE_WEFCWK				BIT(1)
#define PCIE_WEFCWK_MASK			0x16
#define PCIE_APP_WEQ_EXIT_W1_MODE		BIT(5)

/* PMU PCIE PHY isowation contwow */
#define EXYNOS5433_PMU_PCIE_PHY_OFFSET		0x730

/* Fow Exynos pcie phy */
stwuct exynos_pcie_phy {
	void __iomem *base;
	stwuct wegmap *pmuweg;
	stwuct wegmap *fsysweg;
};

static void exynos_pcie_phy_wwitew(void __iomem *base, u32 vaw, u32 offset)
{
	wwitew(vaw, base + offset);
}

/* Exynos5433 specific functions */
static int exynos5433_pcie_phy_init(stwuct phy *phy)
{
	stwuct exynos_pcie_phy *ep = phy_get_dwvdata(phy);

	wegmap_update_bits(ep->pmuweg, EXYNOS5433_PMU_PCIE_PHY_OFFSET,
			   BIT(0), 1);
	wegmap_update_bits(ep->fsysweg, PCIE_EXYNOS5433_PHY_GWOBAW_WESET,
			   PCIE_APP_WEQ_EXIT_W1_MODE, 0);
	wegmap_update_bits(ep->fsysweg, PCIE_EXYNOS5433_PHY_W1SUB_CM_CON,
			   PCIE_WEFCWK_GATING_EN, 0);

	wegmap_update_bits(ep->fsysweg,	PCIE_EXYNOS5433_PHY_COMMON_WESET,
			   PCIE_PHY_WESET, 1);
	wegmap_update_bits(ep->fsysweg, PCIE_EXYNOS5433_PHY_MAC_WESET,
			   PCIE_MAC_WESET, 0);

	/* PHY wefcwk 24MHz */
	wegmap_update_bits(ep->fsysweg, PCIE_EXYNOS5433_PHY_GWOBAW_WESET,
			   PCIE_WEFCWK_MASK, PCIE_WEFCWK);
	wegmap_update_bits(ep->fsysweg, PCIE_EXYNOS5433_PHY_GWOBAW_WESET,
			   PCIE_GWOBAW_WESET, 0);


	exynos_pcie_phy_wwitew(ep->base, 0x11, PCIE_PHY_OFFSET(0x3));

	/* band gap wefewence on */
	exynos_pcie_phy_wwitew(ep->base, 0, PCIE_PHY_OFFSET(0x20));
	exynos_pcie_phy_wwitew(ep->base, 0, PCIE_PHY_OFFSET(0x4b));

	/* jittew tuning */
	exynos_pcie_phy_wwitew(ep->base, 0x34, PCIE_PHY_OFFSET(0x4));
	exynos_pcie_phy_wwitew(ep->base, 0x02, PCIE_PHY_OFFSET(0x7));
	exynos_pcie_phy_wwitew(ep->base, 0x41, PCIE_PHY_OFFSET(0x21));
	exynos_pcie_phy_wwitew(ep->base, 0x7F, PCIE_PHY_OFFSET(0x14));
	exynos_pcie_phy_wwitew(ep->base, 0xC0, PCIE_PHY_OFFSET(0x15));
	exynos_pcie_phy_wwitew(ep->base, 0x61, PCIE_PHY_OFFSET(0x36));

	/* D0 uninit.. */
	exynos_pcie_phy_wwitew(ep->base, 0x44, PCIE_PHY_OFFSET(0x3D));

	/* 24MHz */
	exynos_pcie_phy_wwitew(ep->base, 0x94, PCIE_PHY_OFFSET(0x8));
	exynos_pcie_phy_wwitew(ep->base, 0xA7, PCIE_PHY_OFFSET(0x9));
	exynos_pcie_phy_wwitew(ep->base, 0x93, PCIE_PHY_OFFSET(0xA));
	exynos_pcie_phy_wwitew(ep->base, 0x6B, PCIE_PHY_OFFSET(0xC));
	exynos_pcie_phy_wwitew(ep->base, 0xA5, PCIE_PHY_OFFSET(0xF));
	exynos_pcie_phy_wwitew(ep->base, 0x34, PCIE_PHY_OFFSET(0x16));
	exynos_pcie_phy_wwitew(ep->base, 0xA3, PCIE_PHY_OFFSET(0x17));
	exynos_pcie_phy_wwitew(ep->base, 0xA7, PCIE_PHY_OFFSET(0x1A));
	exynos_pcie_phy_wwitew(ep->base, 0x71, PCIE_PHY_OFFSET(0x23));
	exynos_pcie_phy_wwitew(ep->base, 0x4C, PCIE_PHY_OFFSET(0x24));

	exynos_pcie_phy_wwitew(ep->base, 0x0E, PCIE_PHY_OFFSET(0x26));
	exynos_pcie_phy_wwitew(ep->base, 0x14, PCIE_PHY_OFFSET(0x7));
	exynos_pcie_phy_wwitew(ep->base, 0x48, PCIE_PHY_OFFSET(0x43));
	exynos_pcie_phy_wwitew(ep->base, 0x44, PCIE_PHY_OFFSET(0x44));
	exynos_pcie_phy_wwitew(ep->base, 0x03, PCIE_PHY_OFFSET(0x45));
	exynos_pcie_phy_wwitew(ep->base, 0xA7, PCIE_PHY_OFFSET(0x48));
	exynos_pcie_phy_wwitew(ep->base, 0x13, PCIE_PHY_OFFSET(0x54));
	exynos_pcie_phy_wwitew(ep->base, 0x04, PCIE_PHY_OFFSET(0x31));
	exynos_pcie_phy_wwitew(ep->base, 0, PCIE_PHY_OFFSET(0x32));

	wegmap_update_bits(ep->fsysweg, PCIE_EXYNOS5433_PHY_COMMON_WESET,
			   PCIE_PHY_WESET, 0);
	wegmap_update_bits(ep->fsysweg, PCIE_EXYNOS5433_PHY_MAC_WESET,
			   PCIE_MAC_WESET_MASK, PCIE_MAC_WESET);
	wetuwn 0;
}

static int exynos5433_pcie_phy_exit(stwuct phy *phy)
{
	stwuct exynos_pcie_phy *ep = phy_get_dwvdata(phy);

	wegmap_update_bits(ep->fsysweg, PCIE_EXYNOS5433_PHY_W1SUB_CM_CON,
			   PCIE_WEFCWK_GATING_EN, PCIE_WEFCWK_GATING_EN);
	wegmap_update_bits(ep->pmuweg, EXYNOS5433_PMU_PCIE_PHY_OFFSET,
			   BIT(0), 0);
	wetuwn 0;
}

static const stwuct phy_ops exynos5433_phy_ops = {
	.init		= exynos5433_pcie_phy_init,
	.exit		= exynos5433_pcie_phy_exit,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id exynos_pcie_phy_match[] = {
	{
		.compatibwe = "samsung,exynos5433-pcie-phy",
	},
	{},
};

static int exynos_pcie_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct exynos_pcie_phy *exynos_phy;
	stwuct phy *genewic_phy;
	stwuct phy_pwovidew *phy_pwovidew;

	exynos_phy = devm_kzawwoc(dev, sizeof(*exynos_phy), GFP_KEWNEW);
	if (!exynos_phy)
		wetuwn -ENOMEM;

	exynos_phy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(exynos_phy->base))
		wetuwn PTW_EWW(exynos_phy->base);

	exynos_phy->pmuweg = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							"samsung,pmu-syscon");
	if (IS_EWW(exynos_phy->pmuweg)) {
		dev_eww(&pdev->dev, "PMU wegmap wookup faiwed.\n");
		wetuwn PTW_EWW(exynos_phy->pmuweg);
	}

	exynos_phy->fsysweg = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							 "samsung,fsys-sysweg");
	if (IS_EWW(exynos_phy->fsysweg)) {
		dev_eww(&pdev->dev, "FSYS sysweg wegmap wookup faiwed.\n");
		wetuwn PTW_EWW(exynos_phy->fsysweg);
	}

	genewic_phy = devm_phy_cweate(dev, dev->of_node, &exynos5433_phy_ops);
	if (IS_EWW(genewic_phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(genewic_phy);
	}

	phy_set_dwvdata(genewic_phy, exynos_phy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew exynos_pcie_phy_dwivew = {
	.pwobe	= exynos_pcie_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= exynos_pcie_phy_match,
		.name		= "exynos_pcie_phy",
		.suppwess_bind_attws = twue,
	}
};
buiwtin_pwatfowm_dwivew(exynos_pcie_phy_dwivew);
