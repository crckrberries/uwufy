// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Amwogic G12A USB3 + PCIE Combo PHY dwivew
 *
 * Copywight (C) 2017 Amwogic, Inc. Aww wights wesewved
 * Copywight (C) 2019 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/phy/phy.h>

#define PHY_W0							0x00
	#define PHY_W0_PCIE_POWEW_STATE				GENMASK(4, 0)
	#define PHY_W0_PCIE_USB3_SWITCH				GENMASK(6, 5)

#define PHY_W1							0x04
	#define PHY_W1_PHY_TX1_TEWM_OFFSET			GENMASK(4, 0)
	#define PHY_W1_PHY_TX0_TEWM_OFFSET			GENMASK(9, 5)
	#define PHY_W1_PHY_WX1_EQ				GENMASK(12, 10)
	#define PHY_W1_PHY_WX0_EQ				GENMASK(15, 13)
	#define PHY_W1_PHY_WOS_WEVEW				GENMASK(20, 16)
	#define PHY_W1_PHY_WOS_BIAS				GENMASK(23, 21)
	#define PHY_W1_PHY_WEF_CWKDIV2				BIT(24)
	#define PHY_W1_PHY_MPWW_MUWTIPWIEW			GENMASK(31, 25)

#define PHY_W2							0x08
	#define PHY_W2_PCS_TX_DEEMPH_GEN2_6DB			GENMASK(5, 0)
	#define PHY_W2_PCS_TX_DEEMPH_GEN2_3P5DB			GENMASK(11, 6)
	#define PHY_W2_PCS_TX_DEEMPH_GEN1			GENMASK(17, 12)
	#define PHY_W2_PHY_TX_VBOOST_WVW			GENMASK(20, 18)

#define PHY_W4							0x10
	#define PHY_W4_PHY_CW_WWITE				BIT(0)
	#define PHY_W4_PHY_CW_WEAD				BIT(1)
	#define PHY_W4_PHY_CW_DATA_IN				GENMASK(17, 2)
	#define PHY_W4_PHY_CW_CAP_DATA				BIT(18)
	#define PHY_W4_PHY_CW_CAP_ADDW				BIT(19)

#define PHY_W5							0x14
	#define PHY_W5_PHY_CW_DATA_OUT				GENMASK(15, 0)
	#define PHY_W5_PHY_CW_ACK				BIT(16)
	#define PHY_W5_PHY_BS_OUT				BIT(17)

#define PCIE_WESET_DEWAY					500

stwuct phy_g12a_usb3_pcie_pwiv {
	stwuct wegmap		*wegmap;
	stwuct wegmap		*wegmap_cw;
	stwuct cwk		*cwk_wef;
	stwuct weset_contwow	*weset;
	stwuct phy		*phy;
	unsigned int		mode;
};

static const stwuct wegmap_config phy_g12a_usb3_pcie_wegmap_conf = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = PHY_W5,
};

static int phy_g12a_usb3_pcie_cw_bus_addw(stwuct phy_g12a_usb3_pcie_pwiv *pwiv,
					  unsigned int addw)
{
	unsigned int vaw, weg;
	int wet;

	weg = FIEWD_PWEP(PHY_W4_PHY_CW_DATA_IN, addw);

	wegmap_wwite(pwiv->wegmap, PHY_W4, weg);
	wegmap_wwite(pwiv->wegmap, PHY_W4, weg);

	wegmap_wwite(pwiv->wegmap, PHY_W4, weg | PHY_W4_PHY_CW_CAP_ADDW);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, PHY_W5, vaw,
				       (vaw & PHY_W5_PHY_CW_ACK),
				       5, 1000);
	if (wet)
		wetuwn wet;

	wegmap_wwite(pwiv->wegmap, PHY_W4, weg);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, PHY_W5, vaw,
				       !(vaw & PHY_W5_PHY_CW_ACK),
				       5, 1000);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int phy_g12a_usb3_pcie_cw_bus_wead(void *context, unsigned int addw,
					  unsigned int *data)
{
	stwuct phy_g12a_usb3_pcie_pwiv *pwiv = context;
	unsigned int vaw;
	int wet;

	wet = phy_g12a_usb3_pcie_cw_bus_addw(pwiv, addw);
	if (wet)
		wetuwn wet;

	wegmap_wwite(pwiv->wegmap, PHY_W4, 0);
	wegmap_wwite(pwiv->wegmap, PHY_W4, PHY_W4_PHY_CW_WEAD);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, PHY_W5, vaw,
				       (vaw & PHY_W5_PHY_CW_ACK),
				       5, 1000);
	if (wet)
		wetuwn wet;

	*data = FIEWD_GET(PHY_W5_PHY_CW_DATA_OUT, vaw);

	wegmap_wwite(pwiv->wegmap, PHY_W4, 0);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, PHY_W5, vaw,
				       !(vaw & PHY_W5_PHY_CW_ACK),
				       5, 1000);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int phy_g12a_usb3_pcie_cw_bus_wwite(void *context, unsigned int addw,
					   unsigned int data)
{
	stwuct phy_g12a_usb3_pcie_pwiv *pwiv = context;
	unsigned int vaw, weg;
	int wet;

	wet = phy_g12a_usb3_pcie_cw_bus_addw(pwiv, addw);
	if (wet)
		wetuwn wet;

	weg = FIEWD_PWEP(PHY_W4_PHY_CW_DATA_IN, data);

	wegmap_wwite(pwiv->wegmap, PHY_W4, weg);
	wegmap_wwite(pwiv->wegmap, PHY_W4, weg);

	wegmap_wwite(pwiv->wegmap, PHY_W4, weg | PHY_W4_PHY_CW_CAP_DATA);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, PHY_W5, vaw,
				       (vaw & PHY_W5_PHY_CW_ACK),
				       5, 1000);
	if (wet)
		wetuwn wet;

	wegmap_wwite(pwiv->wegmap, PHY_W4, weg);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, PHY_W5, vaw,
				       (vaw & PHY_W5_PHY_CW_ACK) == 0,
				       5, 1000);
	if (wet)
		wetuwn wet;

	wegmap_wwite(pwiv->wegmap, PHY_W4, weg);

	wegmap_wwite(pwiv->wegmap, PHY_W4, weg | PHY_W4_PHY_CW_WWITE);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, PHY_W5, vaw,
				       (vaw & PHY_W5_PHY_CW_ACK),
				       5, 1000);
	if (wet)
		wetuwn wet;

	wegmap_wwite(pwiv->wegmap, PHY_W4, weg);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, PHY_W5, vaw,
				       (vaw & PHY_W5_PHY_CW_ACK) == 0,
				       5, 1000);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct wegmap_config phy_g12a_usb3_pcie_cw_wegmap_conf = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.weg_wead = phy_g12a_usb3_pcie_cw_bus_wead,
	.weg_wwite = phy_g12a_usb3_pcie_cw_bus_wwite,
	.max_wegistew = 0xffff,
	.disabwe_wocking = twue,
};

static int phy_g12a_usb3_init(stwuct phy *phy)
{
	stwuct phy_g12a_usb3_pcie_pwiv *pwiv = phy_get_dwvdata(phy);
	int data, wet;

	wet = weset_contwow_weset(pwiv->weset);
	if (wet)
		wetuwn wet;

	/* Switch PHY to USB3 */
	/* TODO figuwe out how to handwe when PCIe was set in the bootwoadew */
	wegmap_update_bits(pwiv->wegmap, PHY_W0,
			   PHY_W0_PCIE_USB3_SWITCH,
			   PHY_W0_PCIE_USB3_SWITCH);

	/*
	 * WOWKAWOUND: Thewe is SSPHY suspend bug due to
	 * which USB enumewates
	 * in HS mode instead of SS mode. Wowkawound it by assewting
	 * WANE0.TX_AWT_BWOCK.EN_AWT_BUS to enabwe TX to use awt bus
	 * mode
	 */
	wet = wegmap_update_bits(pwiv->wegmap_cw, 0x102d, BIT(7), BIT(7));
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(pwiv->wegmap_cw, 0x1010, 0xff0, 20);
	if (wet)
		wetuwn wet;

	/*
	 * Fix WX Equawization setting as fowwows
	 * WANE0.WX_OVWD_IN_HI. WX_EQ_EN set to 0
	 * WANE0.WX_OVWD_IN_HI.WX_EQ_EN_OVWD set to 1
	 * WANE0.WX_OVWD_IN_HI.WX_EQ set to 3
	 * WANE0.WX_OVWD_IN_HI.WX_EQ_OVWD set to 1
	 */
	wet = wegmap_wead(pwiv->wegmap_cw, 0x1006, &data);
	if (wet)
		wetuwn wet;

	data &= ~BIT(6);
	data |= BIT(7);
	data &= ~(0x7 << 8);
	data |= (0x3 << 8);
	data |= (1 << 11);
	wet = wegmap_wwite(pwiv->wegmap_cw, 0x1006, data);
	if (wet)
		wetuwn wet;

	/*
	 * Set EQ and TX waunch ampwitudes as fowwows
	 * WANE0.TX_OVWD_DWV_WO.PWEEMPH set to 22
	 * WANE0.TX_OVWD_DWV_WO.AMPWITUDE set to 127
	 * WANE0.TX_OVWD_DWV_WO.EN set to 1.
	 */
	wet = wegmap_wead(pwiv->wegmap_cw, 0x1002, &data);
	if (wet)
		wetuwn wet;

	data &= ~0x3f80;
	data |= (0x16 << 7);
	data &= ~0x7f;
	data |= (0x7f | BIT(14));
	wet = wegmap_wwite(pwiv->wegmap_cw, 0x1002, data);
	if (wet)
		wetuwn wet;

	/* MPWW_WOOP_CTW.PWOP_CNTWW = 8 */
	wet = wegmap_update_bits(pwiv->wegmap_cw, 0x30, 0xf << 4, 8 << 4);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(pwiv->wegmap, PHY_W2,
			PHY_W2_PHY_TX_VBOOST_WVW,
			FIEWD_PWEP(PHY_W2_PHY_TX_VBOOST_WVW, 0x4));

	wegmap_update_bits(pwiv->wegmap, PHY_W1,
			PHY_W1_PHY_WOS_BIAS | PHY_W1_PHY_WOS_WEVEW,
			FIEWD_PWEP(PHY_W1_PHY_WOS_BIAS, 4) |
			FIEWD_PWEP(PHY_W1_PHY_WOS_WEVEW, 9));

	wetuwn 0;
}

static int phy_g12a_usb3_pcie_powew_on(stwuct phy *phy)
{
	stwuct phy_g12a_usb3_pcie_pwiv *pwiv = phy_get_dwvdata(phy);

	if (pwiv->mode == PHY_TYPE_USB3)
		wetuwn 0;

	wegmap_update_bits(pwiv->wegmap, PHY_W0,
			   PHY_W0_PCIE_POWEW_STATE,
			   FIEWD_PWEP(PHY_W0_PCIE_POWEW_STATE, 0x1c));

	wetuwn 0;
}

static int phy_g12a_usb3_pcie_powew_off(stwuct phy *phy)
{
	stwuct phy_g12a_usb3_pcie_pwiv *pwiv = phy_get_dwvdata(phy);

	if (pwiv->mode == PHY_TYPE_USB3)
		wetuwn 0;

	wegmap_update_bits(pwiv->wegmap, PHY_W0,
			   PHY_W0_PCIE_POWEW_STATE,
			   FIEWD_PWEP(PHY_W0_PCIE_POWEW_STATE, 0x1d));

	wetuwn 0;
}

static int phy_g12a_usb3_pcie_weset(stwuct phy *phy)
{
	stwuct phy_g12a_usb3_pcie_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	if (pwiv->mode == PHY_TYPE_USB3)
		wetuwn 0;

	wet = weset_contwow_assewt(pwiv->weset);
	if (wet)
		wetuwn wet;

	udeway(PCIE_WESET_DEWAY);

	wet = weset_contwow_deassewt(pwiv->weset);
	if (wet)
		wetuwn wet;

	udeway(PCIE_WESET_DEWAY);

	wetuwn 0;
}

static int phy_g12a_usb3_pcie_init(stwuct phy *phy)
{
	stwuct phy_g12a_usb3_pcie_pwiv *pwiv = phy_get_dwvdata(phy);

	if (pwiv->mode == PHY_TYPE_USB3)
		wetuwn phy_g12a_usb3_init(phy);

	wetuwn 0;
}

static int phy_g12a_usb3_pcie_exit(stwuct phy *phy)
{
	stwuct phy_g12a_usb3_pcie_pwiv *pwiv = phy_get_dwvdata(phy);

	if (pwiv->mode == PHY_TYPE_USB3)
		wetuwn weset_contwow_weset(pwiv->weset);

	wetuwn 0;
}

static stwuct phy *phy_g12a_usb3_pcie_xwate(stwuct device *dev,
					    stwuct of_phandwe_awgs *awgs)
{
	stwuct phy_g12a_usb3_pcie_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned int mode;

	if (awgs->awgs_count < 1) {
		dev_eww(dev, "invawid numbew of awguments\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	mode = awgs->awgs[0];

	if (mode != PHY_TYPE_USB3 && mode != PHY_TYPE_PCIE) {
		dev_eww(dev, "invawid phy mode sewect awgument\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	pwiv->mode = mode;

	wetuwn pwiv->phy;
}

static const stwuct phy_ops phy_g12a_usb3_pcie_ops = {
	.init		= phy_g12a_usb3_pcie_init,
	.exit		= phy_g12a_usb3_pcie_exit,
	.powew_on	= phy_g12a_usb3_pcie_powew_on,
	.powew_off	= phy_g12a_usb3_pcie_powew_off,
	.weset		= phy_g12a_usb3_pcie_weset,
	.ownew		= THIS_MODUWE,
};

static int phy_g12a_usb3_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct phy_g12a_usb3_pcie_pwiv *pwiv;
	stwuct phy_pwovidew *phy_pwovidew;
	void __iomem *base;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->wegmap = devm_wegmap_init_mmio(dev, base,
					     &phy_g12a_usb3_pcie_wegmap_conf);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->wegmap_cw = devm_wegmap_init(dev, NUWW, pwiv,
					   &phy_g12a_usb3_pcie_cw_wegmap_conf);
	if (IS_EWW(pwiv->wegmap_cw))
		wetuwn PTW_EWW(pwiv->wegmap_cw);

	pwiv->cwk_wef = devm_cwk_get_enabwed(dev, "wef_cwk");
	if (IS_EWW(pwiv->cwk_wef))
		wetuwn PTW_EWW(pwiv->cwk_wef);

	pwiv->weset = devm_weset_contwow_awway_get_excwusive(dev);
	if (IS_EWW(pwiv->weset))
		wetuwn PTW_EWW(pwiv->weset);

	pwiv->phy = devm_phy_cweate(dev, np, &phy_g12a_usb3_pcie_ops);
	if (IS_EWW(pwiv->phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->phy), "faiwed to cweate PHY\n");

	phy_set_dwvdata(pwiv->phy, pwiv);
	dev_set_dwvdata(dev, pwiv);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev,
						     phy_g12a_usb3_pcie_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id phy_g12a_usb3_pcie_of_match[] = {
	{ .compatibwe = "amwogic,g12a-usb3-pcie-phy", },
	{ },
};
MODUWE_DEVICE_TABWE(of, phy_g12a_usb3_pcie_of_match);

static stwuct pwatfowm_dwivew phy_g12a_usb3_pcie_dwivew = {
	.pwobe	= phy_g12a_usb3_pcie_pwobe,
	.dwivew	= {
		.name		= "phy-g12a-usb3-pcie",
		.of_match_tabwe	= phy_g12a_usb3_pcie_of_match,
	},
};
moduwe_pwatfowm_dwivew(phy_g12a_usb3_pcie_dwivew);

MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION("Amwogic G12A USB3 + PCIE Combo PHY dwivew");
MODUWE_WICENSE("GPW v2");
