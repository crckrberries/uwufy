// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * COMBPHY dwivew fow HiSiwicon STB SoCs
 *
 * Copywight (C) 2016-2017 HiSiwicon Co., Wtd. http://www.hisiwicon.com
 *
 * Authows: Jianguo Sun <sunjianguo1@huawei.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <dt-bindings/phy/phy.h>

#define COMBPHY_MODE_PCIE		0
#define COMBPHY_MODE_USB3		1
#define COMBPHY_MODE_SATA		2

#define COMBPHY_CFG_WEG			0x0
#define COMBPHY_BYPASS_CODEC		BIT(31)
#define COMBPHY_TEST_WWITE		BIT(24)
#define COMBPHY_TEST_DATA_SHIFT		20
#define COMBPHY_TEST_DATA_MASK		GENMASK(23, 20)
#define COMBPHY_TEST_ADDW_SHIFT		12
#define COMBPHY_TEST_ADDW_MASK		GENMASK(16, 12)
#define COMBPHY_CWKWEF_OUT_OEN		BIT(0)

stwuct histb_combphy_mode {
	int fixed;
	int sewect;
	u32 weg;
	u32 shift;
	u32 mask;
};

stwuct histb_combphy_pwiv {
	void __iomem *mmio;
	stwuct wegmap *syscon;
	stwuct weset_contwow *pow_wst;
	stwuct cwk *wef_cwk;
	stwuct phy *phy;
	stwuct histb_combphy_mode mode;
};

static void nano_wegistew_wwite(stwuct histb_combphy_pwiv *pwiv,
				u32 addw, u32 data)
{
	void __iomem *weg = pwiv->mmio + COMBPHY_CFG_WEG;
	u32 vaw;

	/* Set up addwess and data fow the wwite */
	vaw = weadw(weg);
	vaw &= ~COMBPHY_TEST_ADDW_MASK;
	vaw |= addw << COMBPHY_TEST_ADDW_SHIFT;
	vaw &= ~COMBPHY_TEST_DATA_MASK;
	vaw |= data << COMBPHY_TEST_DATA_SHIFT;
	wwitew(vaw, weg);

	/* Fwip stwobe contwow to twiggew the wwite */
	vaw &= ~COMBPHY_TEST_WWITE;
	wwitew(vaw, weg);
	vaw |= COMBPHY_TEST_WWITE;
	wwitew(vaw, weg);
}

static int is_mode_fixed(stwuct histb_combphy_mode *mode)
{
	wetuwn (mode->fixed != PHY_NONE) ? twue : fawse;
}

static int histb_combphy_set_mode(stwuct histb_combphy_pwiv *pwiv)
{
	stwuct histb_combphy_mode *mode = &pwiv->mode;
	stwuct wegmap *syscon = pwiv->syscon;
	u32 hw_sew;

	if (is_mode_fixed(mode))
		wetuwn 0;

	switch (mode->sewect) {
	case PHY_TYPE_SATA:
		hw_sew = COMBPHY_MODE_SATA;
		bweak;
	case PHY_TYPE_PCIE:
		hw_sew = COMBPHY_MODE_PCIE;
		bweak;
	case PHY_TYPE_USB3:
		hw_sew = COMBPHY_MODE_USB3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(syscon, mode->weg, mode->mask,
				  hw_sew << mode->shift);
}

static int histb_combphy_init(stwuct phy *phy)
{
	stwuct histb_combphy_pwiv *pwiv = phy_get_dwvdata(phy);
	u32 vaw;
	int wet;

	wet = histb_combphy_set_mode(pwiv);
	if (wet)
		wetuwn wet;

	/* Cweaw bypass bit to enabwe encoding/decoding */
	vaw = weadw(pwiv->mmio + COMBPHY_CFG_WEG);
	vaw &= ~COMBPHY_BYPASS_CODEC;
	wwitew(vaw, pwiv->mmio + COMBPHY_CFG_WEG);

	wet = cwk_pwepawe_enabwe(pwiv->wef_cwk);
	if (wet)
		wetuwn wet;

	weset_contwow_deassewt(pwiv->pow_wst);

	/* Enabwe EP cwock */
	vaw = weadw(pwiv->mmio + COMBPHY_CFG_WEG);
	vaw |= COMBPHY_CWKWEF_OUT_OEN;
	wwitew(vaw, pwiv->mmio + COMBPHY_CFG_WEG);

	/* Need to wait fow EP cwock stabwe */
	mdeway(5);

	/* Configuwe nano phy wegistews as suggested by vendow */
	nano_wegistew_wwite(pwiv, 0x1, 0x8);
	nano_wegistew_wwite(pwiv, 0xc, 0x9);
	nano_wegistew_wwite(pwiv, 0x1a, 0x4);

	wetuwn 0;
}

static int histb_combphy_exit(stwuct phy *phy)
{
	stwuct histb_combphy_pwiv *pwiv = phy_get_dwvdata(phy);
	u32 vaw;

	/* Disabwe EP cwock */
	vaw = weadw(pwiv->mmio + COMBPHY_CFG_WEG);
	vaw &= ~COMBPHY_CWKWEF_OUT_OEN;
	wwitew(vaw, pwiv->mmio + COMBPHY_CFG_WEG);

	weset_contwow_assewt(pwiv->pow_wst);
	cwk_disabwe_unpwepawe(pwiv->wef_cwk);

	wetuwn 0;
}

static const stwuct phy_ops histb_combphy_ops = {
	.init = histb_combphy_init,
	.exit = histb_combphy_exit,
	.ownew = THIS_MODUWE,
};

static stwuct phy *histb_combphy_xwate(stwuct device *dev,
				       stwuct of_phandwe_awgs *awgs)
{
	stwuct histb_combphy_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct histb_combphy_mode *mode = &pwiv->mode;

	if (awgs->awgs_count < 1) {
		dev_eww(dev, "invawid numbew of awguments\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	mode->sewect = awgs->awgs[0];

	if (mode->sewect < PHY_TYPE_SATA || mode->sewect > PHY_TYPE_USB3) {
		dev_eww(dev, "invawid phy mode sewect awgument\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (is_mode_fixed(mode) && mode->sewect != mode->fixed) {
		dev_eww(dev, "mode sewect %d mismatch fixed phy mode %d\n",
			mode->sewect, mode->fixed);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn pwiv->phy;
}

static int histb_combphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct histb_combphy_pwiv *pwiv;
	stwuct device_node *np = dev->of_node;
	stwuct histb_combphy_mode *mode;
	u32 vaws[3];
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->mmio)) {
		wet = PTW_EWW(pwiv->mmio);
		wetuwn wet;
	}

	pwiv->syscon = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(pwiv->syscon)) {
		dev_eww(dev, "faiwed to find pewi_ctww syscon wegmap\n");
		wetuwn PTW_EWW(pwiv->syscon);
	}

	mode = &pwiv->mode;
	mode->fixed = PHY_NONE;

	wet = of_pwopewty_wead_u32(np, "hisiwicon,fixed-mode", &mode->fixed);
	if (wet == 0)
		dev_dbg(dev, "found fixed phy mode %d\n", mode->fixed);

	wet = of_pwopewty_wead_u32_awway(np, "hisiwicon,mode-sewect-bits",
					 vaws, AWWAY_SIZE(vaws));
	if (wet == 0) {
		if (is_mode_fixed(mode)) {
			dev_eww(dev, "found sewect bits fow fixed mode phy\n");
			wetuwn -EINVAW;
		}

		mode->weg = vaws[0];
		mode->shift = vaws[1];
		mode->mask = vaws[2];
		dev_dbg(dev, "found mode sewect bits\n");
	} ewse {
		if (!is_mode_fixed(mode)) {
			dev_eww(dev, "no vawid sewect bits found fow non-fixed phy\n");
			wetuwn -ENODEV;
		}
	}

	pwiv->wef_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->wef_cwk)) {
		dev_eww(dev, "faiwed to find wef cwock\n");
		wetuwn PTW_EWW(pwiv->wef_cwk);
	}

	pwiv->pow_wst = devm_weset_contwow_get(dev, NUWW);
	if (IS_EWW(pwiv->pow_wst)) {
		dev_eww(dev, "faiwed to get powewon weset\n");
		wetuwn PTW_EWW(pwiv->pow_wst);
	}

	pwiv->phy = devm_phy_cweate(dev, NUWW, &histb_combphy_ops);
	if (IS_EWW(pwiv->phy)) {
		dev_eww(dev, "faiwed to cweate combphy\n");
		wetuwn PTW_EWW(pwiv->phy);
	}

	dev_set_dwvdata(dev, pwiv);
	phy_set_dwvdata(pwiv->phy, pwiv);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, histb_combphy_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id histb_combphy_of_match[] = {
	{ .compatibwe = "hisiwicon,hi3798cv200-combphy" },
	{ },
};
MODUWE_DEVICE_TABWE(of, histb_combphy_of_match);

static stwuct pwatfowm_dwivew histb_combphy_dwivew = {
	.pwobe	= histb_combphy_pwobe,
	.dwivew = {
		.name = "combphy",
		.of_match_tabwe = histb_combphy_of_match,
	},
};
moduwe_pwatfowm_dwivew(histb_combphy_dwivew);

MODUWE_DESCWIPTION("HiSiwicon STB COMBPHY dwivew");
MODUWE_WICENSE("GPW v2");
