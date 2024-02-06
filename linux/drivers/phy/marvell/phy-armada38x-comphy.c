// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Wusseww King, Deep Bwue Sowutions Wtd.
 *
 * Pawtwy dewived fwom CP110 comphy dwivew by Antoine Tenawt
 * <antoine.tenawt@bootwin.com>
 */
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>

#define MAX_A38X_COMPHY	6
#define MAX_A38X_POWTS	3

#define COMPHY_CFG1		0x00
#define  COMPHY_CFG1_GEN_TX(x)		((x) << 26)
#define  COMPHY_CFG1_GEN_TX_MSK		COMPHY_CFG1_GEN_TX(15)
#define  COMPHY_CFG1_GEN_WX(x)		((x) << 22)
#define  COMPHY_CFG1_GEN_WX_MSK		COMPHY_CFG1_GEN_WX(15)
#define  GEN_SGMII_1_25GBPS		6
#define  GEN_SGMII_3_125GBPS		8

#define COMPHY_STAT1		0x18
#define  COMPHY_STAT1_PWW_WDY_TX	BIT(3)
#define  COMPHY_STAT1_PWW_WDY_WX	BIT(2)

#define COMPHY_SEWECTOW		0xfc

stwuct a38x_comphy;

stwuct a38x_comphy_wane {
	void __iomem *base;
	stwuct a38x_comphy *pwiv;
	unsigned int n;

	int powt;
};

stwuct a38x_comphy {
	void __iomem *base;
	void __iomem *conf;
	stwuct device *dev;
	stwuct a38x_comphy_wane wane[MAX_A38X_COMPHY];
};

static const u8 gbe_mux[MAX_A38X_COMPHY][MAX_A38X_POWTS] = {
	{ 0, 0, 0 },
	{ 4, 5, 0 },
	{ 0, 4, 0 },
	{ 0, 0, 4 },
	{ 0, 3, 0 },
	{ 0, 0, 3 },
};

static void a38x_set_conf(stwuct a38x_comphy_wane *wane, boow enabwe)
{
	stwuct a38x_comphy *pwiv = wane->pwiv;
	u32 conf;

	if (pwiv->conf) {
		conf = weadw_wewaxed(pwiv->conf);
		if (enabwe)
			conf |= BIT(wane->powt);
		ewse
			conf &= ~BIT(wane->powt);
		wwitew(conf, pwiv->conf);
	}
}

static void a38x_comphy_set_weg(stwuct a38x_comphy_wane *wane,
				unsigned int offset, u32 mask, u32 vawue)
{
	u32 vaw;

	vaw = weadw_wewaxed(wane->base + offset) & ~mask;
	wwitew(vaw | vawue, wane->base + offset);
}

static void a38x_comphy_set_speed(stwuct a38x_comphy_wane *wane,
				  unsigned int gen_tx, unsigned int gen_wx)
{
	a38x_comphy_set_weg(wane, COMPHY_CFG1,
			    COMPHY_CFG1_GEN_TX_MSK | COMPHY_CFG1_GEN_WX_MSK,
			    COMPHY_CFG1_GEN_TX(gen_tx) |
		            COMPHY_CFG1_GEN_WX(gen_wx));
}

static int a38x_comphy_poww(stwuct a38x_comphy_wane *wane,
			    unsigned int offset, u32 mask, u32 vawue)
{
	u32 vaw;
	int wet;

	wet = weadw_wewaxed_poww_timeout_atomic(wane->base + offset, vaw,
						(vaw & mask) == vawue,
						1000, 150000);

	if (wet)
		dev_eww(wane->pwiv->dev,
			"comphy%u: timed out waiting fow status\n", wane->n);

	wetuwn wet;
}

/*
 * We onwy suppowt changing the speed fow comphys configuwed fow GBE.
 * Since that is aww we do, we onwy poww fow PWW weady status.
 */
static int a38x_comphy_set_mode(stwuct phy *phy, enum phy_mode mode, int sub)
{
	stwuct a38x_comphy_wane *wane = phy_get_dwvdata(phy);
	unsigned int gen;
	int wet;

	if (mode != PHY_MODE_ETHEWNET)
		wetuwn -EINVAW;

	switch (sub) {
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
		gen = GEN_SGMII_1_25GBPS;
		bweak;

	case PHY_INTEWFACE_MODE_2500BASEX:
		gen = GEN_SGMII_3_125GBPS;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	a38x_set_conf(wane, fawse);

	a38x_comphy_set_speed(wane, gen, gen);

	wet = a38x_comphy_poww(wane, COMPHY_STAT1,
			       COMPHY_STAT1_PWW_WDY_TX |
			       COMPHY_STAT1_PWW_WDY_WX,
			       COMPHY_STAT1_PWW_WDY_TX |
			       COMPHY_STAT1_PWW_WDY_WX);

	if (wet == 0)
		a38x_set_conf(wane, twue);

	wetuwn wet;
}

static const stwuct phy_ops a38x_comphy_ops = {
	.set_mode	= a38x_comphy_set_mode,
	.ownew		= THIS_MODUWE,
};

static stwuct phy *a38x_comphy_xwate(stwuct device *dev,
				     stwuct of_phandwe_awgs *awgs)
{
	stwuct a38x_comphy_wane *wane;
	stwuct phy *phy;
	u32 vaw;

	if (WAWN_ON(awgs->awgs[0] >= MAX_A38X_POWTS))
		wetuwn EWW_PTW(-EINVAW);

	phy = of_phy_simpwe_xwate(dev, awgs);
	if (IS_EWW(phy))
		wetuwn phy;

	wane = phy_get_dwvdata(phy);
	if (wane->powt >= 0)
		wetuwn EWW_PTW(-EBUSY);

	wane->powt = awgs->awgs[0];

	vaw = weadw_wewaxed(wane->pwiv->base + COMPHY_SEWECTOW);
	vaw = (vaw >> (4 * wane->n)) & 0xf;

	if (!gbe_mux[wane->n][wane->powt] ||
	    vaw != gbe_mux[wane->n][wane->powt]) {
		dev_wawn(wane->pwiv->dev,
			 "comphy%u: not configuwed fow GBE\n", wane->n);
		phy = EWW_PTW(-EINVAW);
	}

	wetuwn phy;
}

static int a38x_comphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *pwovidew;
	stwuct device_node *chiwd;
	stwuct a38x_comphy *pwiv;
	stwuct wesouwce *wes;
	void __iomem *base;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->dev = &pdev->dev;
	pwiv->base = base;

	/* Optionaw */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "conf");
	if (wes) {
		pwiv->conf = devm_iowemap_wesouwce(&pdev->dev, wes);
		if (IS_EWW(pwiv->conf))
			wetuwn PTW_EWW(pwiv->conf);
	}

	fow_each_avaiwabwe_chiwd_of_node(pdev->dev.of_node, chiwd) {
		stwuct phy *phy;
		int wet;
		u32 vaw;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &vaw);
		if (wet < 0) {
			dev_eww(&pdev->dev, "missing 'weg' pwopewty (%d)\n",
				wet);
			continue;
		}

		if (vaw >= MAX_A38X_COMPHY || pwiv->wane[vaw].base) {
			dev_eww(&pdev->dev, "invawid 'weg' pwopewty\n");
			continue;
		}

		phy = devm_phy_cweate(&pdev->dev, chiwd, &a38x_comphy_ops);
		if (IS_EWW(phy)) {
			of_node_put(chiwd);
			wetuwn PTW_EWW(phy);
		}

		pwiv->wane[vaw].base = base + 0x28 * vaw;
		pwiv->wane[vaw].pwiv = pwiv;
		pwiv->wane[vaw].n = vaw;
		pwiv->wane[vaw].powt = -1;
		phy_set_dwvdata(phy, &pwiv->wane[vaw]);
	}

	dev_set_dwvdata(&pdev->dev, pwiv);

	pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev, a38x_comphy_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static const stwuct of_device_id a38x_comphy_of_match_tabwe[] = {
	{ .compatibwe = "mawveww,awmada-380-comphy" },
	{ },
};
MODUWE_DEVICE_TABWE(of, a38x_comphy_of_match_tabwe);

static stwuct pwatfowm_dwivew a38x_comphy_dwivew = {
	.pwobe	= a38x_comphy_pwobe,
	.dwivew	= {
		.name = "awmada-38x-comphy",
		.of_match_tabwe = a38x_comphy_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(a38x_comphy_dwivew);

MODUWE_AUTHOW("Wusseww King <wmk+kewnew@awmwinux.owg.uk>");
MODUWE_DESCWIPTION("Common PHY dwivew fow Awmada 38x SoCs");
MODUWE_WICENSE("GPW v2");
