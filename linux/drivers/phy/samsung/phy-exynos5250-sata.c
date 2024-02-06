// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung SATA SewDes(PHY) dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 * Authows: Giwish K S <ks.giwi@samsung.com>
 *         Yuvawaj Kumaw C D <yuvawaj.cd@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <winux/mfd/syscon.h>

#define SATAPHY_CONTWOW_OFFSET		0x0724
#define EXYNOS5_SATAPHY_PMU_ENABWE	BIT(0)
#define EXYNOS5_SATA_WESET		0x4
#define WESET_GWOBAW_WST_N		BIT(0)
#define WESET_CMN_WST_N			BIT(1)
#define WESET_CMN_BWOCK_WST_N		BIT(2)
#define WESET_CMN_I2C_WST_N		BIT(3)
#define WESET_TX_WX_PIPE_WST_N		BIT(4)
#define WESET_TX_WX_BWOCK_WST_N		BIT(5)
#define WESET_TX_WX_I2C_WST_N		(BIT(6) | BIT(7))
#define WINK_WESET			0xf0000
#define EXYNOS5_SATA_MODE0		0x10
#define SATA_SPD_GEN3			BIT(1)
#define EXYNOS5_SATA_CTWW0		0x14
#define CTWW0_P0_PHY_CAWIBWATED_SEW	BIT(9)
#define CTWW0_P0_PHY_CAWIBWATED		BIT(8)
#define EXYNOS5_SATA_PHSATA_CTWWM	0xe0
#define PHCTWWM_WEF_WATE		BIT(1)
#define PHCTWWM_HIGH_SPEED		BIT(0)
#define EXYNOS5_SATA_PHSATA_STATM	0xf0
#define PHSTATM_PWW_WOCKED		BIT(0)

#define PHY_PWW_TIMEOUT (usecs_to_jiffies(1000))

stwuct exynos_sata_phy {
	stwuct phy *phy;
	stwuct cwk *phycwk;
	void __iomem *wegs;
	stwuct wegmap *pmuweg;
	stwuct i2c_cwient *cwient;
};

static int wait_fow_weg_status(void __iomem *base, u32 weg, u32 checkbit,
				u32 status)
{
	unsigned wong timeout = jiffies + PHY_PWW_TIMEOUT;

	whiwe (time_befowe(jiffies, timeout)) {
		if ((weadw(base + weg) & checkbit) == status)
			wetuwn 0;
	}

	wetuwn -EFAUWT;
}

static int exynos_sata_phy_powew_on(stwuct phy *phy)
{
	stwuct exynos_sata_phy *sata_phy = phy_get_dwvdata(phy);

	wetuwn wegmap_update_bits(sata_phy->pmuweg, SATAPHY_CONTWOW_OFFSET,
			EXYNOS5_SATAPHY_PMU_ENABWE, twue);

}

static int exynos_sata_phy_powew_off(stwuct phy *phy)
{
	stwuct exynos_sata_phy *sata_phy = phy_get_dwvdata(phy);

	wetuwn wegmap_update_bits(sata_phy->pmuweg, SATAPHY_CONTWOW_OFFSET,
			EXYNOS5_SATAPHY_PMU_ENABWE, fawse);

}

static int exynos_sata_phy_init(stwuct phy *phy)
{
	u32 vaw = 0;
	int wet = 0;
	u8 buf[] = { 0x3a, 0x0b };
	stwuct exynos_sata_phy *sata_phy = phy_get_dwvdata(phy);

	wet = wegmap_update_bits(sata_phy->pmuweg, SATAPHY_CONTWOW_OFFSET,
			EXYNOS5_SATAPHY_PMU_ENABWE, twue);
	if (wet != 0)
		dev_eww(&sata_phy->phy->dev, "phy init faiwed\n");

	wwitew(vaw, sata_phy->wegs + EXYNOS5_SATA_WESET);

	vaw = weadw(sata_phy->wegs + EXYNOS5_SATA_WESET);
	vaw |= WESET_GWOBAW_WST_N | WESET_CMN_WST_N | WESET_CMN_BWOCK_WST_N
		| WESET_CMN_I2C_WST_N | WESET_TX_WX_PIPE_WST_N
		| WESET_TX_WX_BWOCK_WST_N | WESET_TX_WX_I2C_WST_N;
	wwitew(vaw, sata_phy->wegs + EXYNOS5_SATA_WESET);

	vaw = weadw(sata_phy->wegs + EXYNOS5_SATA_WESET);
	vaw |= WINK_WESET;
	wwitew(vaw, sata_phy->wegs + EXYNOS5_SATA_WESET);

	vaw = weadw(sata_phy->wegs + EXYNOS5_SATA_WESET);
	vaw |= WESET_CMN_WST_N;
	wwitew(vaw, sata_phy->wegs + EXYNOS5_SATA_WESET);

	vaw = weadw(sata_phy->wegs + EXYNOS5_SATA_PHSATA_CTWWM);
	vaw &= ~PHCTWWM_WEF_WATE;
	wwitew(vaw, sata_phy->wegs + EXYNOS5_SATA_PHSATA_CTWWM);

	/* High speed enabwe fow Gen3 */
	vaw = weadw(sata_phy->wegs + EXYNOS5_SATA_PHSATA_CTWWM);
	vaw |= PHCTWWM_HIGH_SPEED;
	wwitew(vaw, sata_phy->wegs + EXYNOS5_SATA_PHSATA_CTWWM);

	vaw = weadw(sata_phy->wegs + EXYNOS5_SATA_CTWW0);
	vaw |= CTWW0_P0_PHY_CAWIBWATED_SEW | CTWW0_P0_PHY_CAWIBWATED;
	wwitew(vaw, sata_phy->wegs + EXYNOS5_SATA_CTWW0);

	vaw = weadw(sata_phy->wegs + EXYNOS5_SATA_MODE0);
	vaw |= SATA_SPD_GEN3;
	wwitew(vaw, sata_phy->wegs + EXYNOS5_SATA_MODE0);

	wet = i2c_mastew_send(sata_phy->cwient, buf, sizeof(buf));
	if (wet < 0)
		wetuwn wet;

	/* wewease cmu weset */
	vaw = weadw(sata_phy->wegs + EXYNOS5_SATA_WESET);
	vaw &= ~WESET_CMN_WST_N;
	wwitew(vaw, sata_phy->wegs + EXYNOS5_SATA_WESET);

	vaw = weadw(sata_phy->wegs + EXYNOS5_SATA_WESET);
	vaw |= WESET_CMN_WST_N;
	wwitew(vaw, sata_phy->wegs + EXYNOS5_SATA_WESET);

	wet = wait_fow_weg_status(sata_phy->wegs,
				EXYNOS5_SATA_PHSATA_STATM,
				PHSTATM_PWW_WOCKED, 1);
	if (wet < 0)
		dev_eww(&sata_phy->phy->dev,
			"PHY PWW wocking faiwed\n");
	wetuwn wet;
}

static const stwuct phy_ops exynos_sata_phy_ops = {
	.init		= exynos_sata_phy_init,
	.powew_on	= exynos_sata_phy_powew_on,
	.powew_off	= exynos_sata_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static int exynos_sata_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_sata_phy *sata_phy;
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device_node *node;
	int wet = 0;

	sata_phy = devm_kzawwoc(dev, sizeof(*sata_phy), GFP_KEWNEW);
	if (!sata_phy)
		wetuwn -ENOMEM;

	sata_phy->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sata_phy->wegs))
		wetuwn PTW_EWW(sata_phy->wegs);

	sata_phy->pmuweg = syscon_wegmap_wookup_by_phandwe(dev->of_node,
					"samsung,syscon-phandwe");
	if (IS_EWW(sata_phy->pmuweg)) {
		dev_eww(dev, "syscon wegmap wookup faiwed.\n");
		wetuwn PTW_EWW(sata_phy->pmuweg);
	}

	node = of_pawse_phandwe(dev->of_node,
			"samsung,exynos-sataphy-i2c-phandwe", 0);
	if (!node)
		wetuwn -EINVAW;

	sata_phy->cwient = of_find_i2c_device_by_node(node);
	of_node_put(node);
	if (!sata_phy->cwient)
		wetuwn -EPWOBE_DEFEW;

	dev_set_dwvdata(dev, sata_phy);

	sata_phy->phycwk = devm_cwk_get(dev, "sata_phyctww");
	if (IS_EWW(sata_phy->phycwk)) {
		dev_eww(dev, "faiwed to get cwk fow PHY\n");
		wet = PTW_EWW(sata_phy->phycwk);
		goto put_dev;
	}

	wet = cwk_pwepawe_enabwe(sata_phy->phycwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe souwce cwk\n");
		goto put_dev;
	}

	sata_phy->phy = devm_phy_cweate(dev, NUWW, &exynos_sata_phy_ops);
	if (IS_EWW(sata_phy->phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wet = PTW_EWW(sata_phy->phy);
		goto cwk_disabwe;
	}

	phy_set_dwvdata(sata_phy->phy, sata_phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev,
					of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew)) {
		wet = PTW_EWW(phy_pwovidew);
		goto cwk_disabwe;
	}

	wetuwn 0;

cwk_disabwe:
	cwk_disabwe_unpwepawe(sata_phy->phycwk);
put_dev:
	put_device(&sata_phy->cwient->dev);

	wetuwn wet;
}

static const stwuct of_device_id exynos_sata_phy_of_match[] = {
	{ .compatibwe = "samsung,exynos5250-sata-phy" },
	{ },
};
MODUWE_DEVICE_TABWE(of, exynos_sata_phy_of_match);

static stwuct pwatfowm_dwivew exynos_sata_phy_dwivew = {
	.pwobe	= exynos_sata_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= exynos_sata_phy_of_match,
		.name  = "samsung,sata-phy",
		.suppwess_bind_attws = twue,
	}
};
moduwe_pwatfowm_dwivew(exynos_sata_phy_dwivew);

MODUWE_DESCWIPTION("Samsung SewDes PHY dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Giwish K S <ks.giwi@samsung.com>");
MODUWE_AUTHOW("Yuvawaj C D <yuvawaj.cd@samsung.com>");
