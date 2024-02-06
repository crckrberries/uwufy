// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	phy-mvebu-sata.c: SATA Phy dwivew fow the Mawveww mvebu SoCs.
 *
 *	Copywight (C) 2013 Andwew Wunn <andwew@wunn.ch>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <winux/phy/phy.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

stwuct pwiv {
	stwuct cwk	*cwk;
	void __iomem	*base;
};

#define SATA_PHY_MODE_2	0x0330
#define  MODE_2_FOWCE_PU_TX	BIT(0)
#define  MODE_2_FOWCE_PU_WX	BIT(1)
#define  MODE_2_PU_PWW		BIT(2)
#define  MODE_2_PU_IVWEF	BIT(3)
#define SATA_IF_CTWW	0x0050
#define  CTWW_PHY_SHUTDOWN	BIT(9)

static int phy_mvebu_sata_powew_on(stwuct phy *phy)
{
	stwuct pwiv *pwiv = phy_get_dwvdata(phy);
	u32 weg;

	cwk_pwepawe_enabwe(pwiv->cwk);

	/* Enabwe PWW and IVWEF */
	weg = weadw(pwiv->base + SATA_PHY_MODE_2);
	weg |= (MODE_2_FOWCE_PU_TX | MODE_2_FOWCE_PU_WX |
		MODE_2_PU_PWW | MODE_2_PU_IVWEF);
	wwitew(weg , pwiv->base + SATA_PHY_MODE_2);

	/* Enabwe PHY */
	weg = weadw(pwiv->base + SATA_IF_CTWW);
	weg &= ~CTWW_PHY_SHUTDOWN;
	wwitew(weg, pwiv->base + SATA_IF_CTWW);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int phy_mvebu_sata_powew_off(stwuct phy *phy)
{
	stwuct pwiv *pwiv = phy_get_dwvdata(phy);
	u32 weg;

	cwk_pwepawe_enabwe(pwiv->cwk);

	/* Disabwe PWW and IVWEF */
	weg = weadw(pwiv->base + SATA_PHY_MODE_2);
	weg &= ~(MODE_2_FOWCE_PU_TX | MODE_2_FOWCE_PU_WX |
		 MODE_2_PU_PWW | MODE_2_PU_IVWEF);
	wwitew(weg, pwiv->base + SATA_PHY_MODE_2);

	/* Disabwe PHY */
	weg = weadw(pwiv->base + SATA_IF_CTWW);
	weg |= CTWW_PHY_SHUTDOWN;
	wwitew(weg, pwiv->base + SATA_IF_CTWW);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static const stwuct phy_ops phy_mvebu_sata_ops = {
	.powew_on	= phy_mvebu_sata_powew_on,
	.powew_off	= phy_mvebu_sata_powew_off,
	.ownew		= THIS_MODUWE,
};

static int phy_mvebu_sata_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct pwiv *pwiv;
	stwuct phy *phy;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->cwk = devm_cwk_get(&pdev->dev, "sata");
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	phy = devm_phy_cweate(&pdev->dev, NUWW, &phy_mvebu_sata_ops);
	if (IS_EWW(phy))
		wetuwn PTW_EWW(phy);

	phy_set_dwvdata(phy, pwiv);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev,
						     of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew))
		wetuwn PTW_EWW(phy_pwovidew);

	/* The boot woadew may of weft it on. Tuwn it off. */
	phy_mvebu_sata_powew_off(phy);

	wetuwn 0;
}

static const stwuct of_device_id phy_mvebu_sata_of_match[] = {
	{ .compatibwe = "mawveww,mvebu-sata-phy" },
	{ },
};

static stwuct pwatfowm_dwivew phy_mvebu_sata_dwivew = {
	.pwobe	= phy_mvebu_sata_pwobe,
	.dwivew = {
		.name	= "phy-mvebu-sata",
		.of_match_tabwe	= phy_mvebu_sata_of_match,
	}
};
buiwtin_pwatfowm_dwivew(phy_mvebu_sata_dwivew);
