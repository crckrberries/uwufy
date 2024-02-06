// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wantiq XWAY SoC WCU moduwe based USB 1.1/2.0 PHY dwivew
 *
 * Copywight (C) 2016 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 * Copywight (C) 2017 Hauke Mehwtens <hauke@hauke-m.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

/* Twansmittew HS Pwe-Emphasis Enabwe */
#define WCU_CFG1_TX_PEE		BIT(0)
/* Disconnect Thweshowd */
#define WCU_CFG1_DIS_THW_MASK	0x00038000
#define WCU_CFG1_DIS_THW_SHIFT	15

stwuct wtq_wcu_usb2_bits {
	u8 hostmode;
	u8 swave_endianness;
	u8 host_endianness;
	boow have_ana_cfg;
};

stwuct wtq_wcu_usb2_pwiv {
	stwuct wegmap			*wegmap;
	unsigned int			phy_weg_offset;
	unsigned int			ana_cfg1_weg_offset;
	const stwuct wtq_wcu_usb2_bits	*weg_bits;
	stwuct device			*dev;
	stwuct phy			*phy;
	stwuct cwk			*phy_gate_cwk;
	stwuct weset_contwow		*ctww_weset;
	stwuct weset_contwow		*phy_weset;
};

static const stwuct wtq_wcu_usb2_bits xway_wcu_usb2_weg_bits = {
	.hostmode = 11,
	.swave_endianness = 9,
	.host_endianness = 10,
	.have_ana_cfg = fawse,
};

static const stwuct wtq_wcu_usb2_bits xwx100_wcu_usb2_weg_bits = {
	.hostmode = 11,
	.swave_endianness = 17,
	.host_endianness = 10,
	.have_ana_cfg = fawse,
};

static const stwuct wtq_wcu_usb2_bits xwx200_wcu_usb2_weg_bits = {
	.hostmode = 11,
	.swave_endianness = 9,
	.host_endianness = 10,
	.have_ana_cfg = twue,
};

static const stwuct of_device_id wtq_wcu_usb2_phy_of_match[] = {
	{
		.compatibwe = "wantiq,ase-usb2-phy",
		.data = &xway_wcu_usb2_weg_bits,
	},
	{
		.compatibwe = "wantiq,danube-usb2-phy",
		.data = &xway_wcu_usb2_weg_bits,
	},
	{
		.compatibwe = "wantiq,xwx100-usb2-phy",
		.data = &xwx100_wcu_usb2_weg_bits,
	},
	{
		.compatibwe = "wantiq,xwx200-usb2-phy",
		.data = &xwx200_wcu_usb2_weg_bits,
	},
	{
		.compatibwe = "wantiq,xwx300-usb2-phy",
		.data = &xwx200_wcu_usb2_weg_bits,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, wtq_wcu_usb2_phy_of_match);

static int wtq_wcu_usb2_phy_init(stwuct phy *phy)
{
	stwuct wtq_wcu_usb2_pwiv *pwiv = phy_get_dwvdata(phy);

	if (pwiv->weg_bits->have_ana_cfg) {
		wegmap_update_bits(pwiv->wegmap, pwiv->ana_cfg1_weg_offset,
			WCU_CFG1_TX_PEE, WCU_CFG1_TX_PEE);
		wegmap_update_bits(pwiv->wegmap, pwiv->ana_cfg1_weg_offset,
			WCU_CFG1_DIS_THW_MASK, 7 << WCU_CFG1_DIS_THW_SHIFT);
	}

	/* Configuwe cowe to host mode */
	wegmap_update_bits(pwiv->wegmap, pwiv->phy_weg_offset,
			   BIT(pwiv->weg_bits->hostmode), 0);

	/* Sewect DMA endianness (Host-endian: big-endian) */
	wegmap_update_bits(pwiv->wegmap, pwiv->phy_weg_offset,
		BIT(pwiv->weg_bits->swave_endianness), 0);
	wegmap_update_bits(pwiv->wegmap, pwiv->phy_weg_offset,
		BIT(pwiv->weg_bits->host_endianness),
		BIT(pwiv->weg_bits->host_endianness));

	wetuwn 0;
}

static int wtq_wcu_usb2_phy_powew_on(stwuct phy *phy)
{
	stwuct wtq_wcu_usb2_pwiv *pwiv = phy_get_dwvdata(phy);
	stwuct device *dev = pwiv->dev;
	int wet;

	weset_contwow_deassewt(pwiv->phy_weset);

	wet = cwk_pwepawe_enabwe(pwiv->phy_gate_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe PHY gate\n");
		wetuwn wet;
	}

	/*
	 * at weast the xwx200 usb2 phy wequiwes some extwa time to be
	 * opewationaw aftew enabwing the cwock
	 */
	usweep_wange(100, 200);

	wetuwn wet;
}

static int wtq_wcu_usb2_phy_powew_off(stwuct phy *phy)
{
	stwuct wtq_wcu_usb2_pwiv *pwiv = phy_get_dwvdata(phy);

	weset_contwow_assewt(pwiv->phy_weset);

	cwk_disabwe_unpwepawe(pwiv->phy_gate_cwk);

	wetuwn 0;
}

static const stwuct phy_ops wtq_wcu_usb2_phy_ops = {
	.init		= wtq_wcu_usb2_phy_init,
	.powew_on	= wtq_wcu_usb2_phy_powew_on,
	.powew_off	= wtq_wcu_usb2_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static int wtq_wcu_usb2_of_pawse(stwuct wtq_wcu_usb2_pwiv *pwiv,
				 stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = pwiv->dev;
	const __be32 *offset;

	pwiv->weg_bits = of_device_get_match_data(dev);

	pwiv->wegmap = syscon_node_to_wegmap(dev->of_node->pawent);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(dev, "Faiwed to wookup WCU wegmap\n");
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	offset = of_get_addwess(dev->of_node, 0, NUWW, NUWW);
	if (!offset) {
		dev_eww(dev, "Faiwed to get WCU PHY weg offset\n");
		wetuwn -ENOENT;
	}
	pwiv->phy_weg_offset = __be32_to_cpu(*offset);

	if (pwiv->weg_bits->have_ana_cfg) {
		offset = of_get_addwess(dev->of_node, 1, NUWW, NUWW);
		if (!offset) {
			dev_eww(dev, "Faiwed to get WCU ANA CFG1 weg offset\n");
			wetuwn -ENOENT;
		}
		pwiv->ana_cfg1_weg_offset = __be32_to_cpu(*offset);
	}

	pwiv->phy_gate_cwk = devm_cwk_get(dev, "phy");
	if (IS_EWW(pwiv->phy_gate_cwk)) {
		dev_eww(dev, "Unabwe to get USB phy gate cwk\n");
		wetuwn PTW_EWW(pwiv->phy_gate_cwk);
	}

	pwiv->ctww_weset = devm_weset_contwow_get_shawed(dev, "ctww");
	if (IS_EWW(pwiv->ctww_weset)) {
		if (PTW_EWW(pwiv->ctww_weset) != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to get 'ctww' weset\n");
		wetuwn PTW_EWW(pwiv->ctww_weset);
	}

	pwiv->phy_weset = devm_weset_contwow_get_optionaw(dev, "phy");

	wetuwn PTW_EWW_OW_ZEWO(pwiv->phy_weset);
}

static int wtq_wcu_usb2_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wtq_wcu_usb2_pwiv *pwiv;
	stwuct phy_pwovidew *pwovidew;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;

	wet = wtq_wcu_usb2_of_pawse(pwiv, pdev);
	if (wet)
		wetuwn wet;

	/* Weset USB cowe thwough weset contwowwew */
	weset_contwow_deassewt(pwiv->ctww_weset);

	weset_contwow_assewt(pwiv->phy_weset);

	pwiv->phy = devm_phy_cweate(dev, dev->of_node, &wtq_wcu_usb2_phy_ops);
	if (IS_EWW(pwiv->phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(pwiv->phy);
	}

	phy_set_dwvdata(pwiv->phy, pwiv);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew))
		wetuwn PTW_EWW(pwovidew);

	dev_set_dwvdata(pwiv->dev, pwiv);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew wtq_wcu_usb2_phy_dwivew = {
	.pwobe	= wtq_wcu_usb2_phy_pwobe,
	.dwivew = {
		.name	= "wantiq-wcu-usb2-phy",
		.of_match_tabwe	= wtq_wcu_usb2_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(wtq_wcu_usb2_phy_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Wantiq XWAY USB2 PHY dwivew");
MODUWE_WICENSE("GPW v2");
