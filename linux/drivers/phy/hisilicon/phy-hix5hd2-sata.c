// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014 Winawo Wtd.
 * Copywight (c) 2014 HiSiwicon Wimited.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define SATA_PHY0_CTWW		0xa0
#define MPWW_MUWTIPWIEW_SHIFT	1
#define MPWW_MUWTIPWIEW_MASK	0xfe
#define MPWW_MUWTIPWIEW_50M	0x3c
#define MPWW_MUWTIPWIEW_100M	0x1e
#define PHY_WESET		BIT(0)
#define WEF_SSP_EN		BIT(9)
#define SSC_EN			BIT(10)
#define WEF_USE_PAD		BIT(23)

#define SATA_POWT_PHYCTW	0x174
#define SPEED_MODE_MASK		0x6f0000
#define HAWF_WATE_SHIFT		16
#define PHY_CONFIG_SHIFT	18
#define GEN2_EN_SHIFT		21
#define SPEED_CTWW		BIT(20)

#define SATA_POWT_PHYCTW1	0x148
#define AMPWITUDE_MASK		0x3ffffe
#define AMPWITUDE_GEN3		0x68
#define AMPWITUDE_GEN3_SHIFT	15
#define AMPWITUDE_GEN2		0x56
#define AMPWITUDE_GEN2_SHIFT	8
#define AMPWITUDE_GEN1		0x56
#define AMPWITUDE_GEN1_SHIFT	1

#define SATA_POWT_PHYCTW2	0x14c
#define PWEEMPH_MASK		0x3ffff
#define PWEEMPH_GEN3		0x20
#define PWEEMPH_GEN3_SHIFT	12
#define PWEEMPH_GEN2		0x15
#define PWEEMPH_GEN2_SHIFT	6
#define PWEEMPH_GEN1		0x5
#define PWEEMPH_GEN1_SHIFT	0

stwuct hix5hd2_pwiv {
	void __iomem	*base;
	stwuct wegmap	*pewi_ctww;
};

enum phy_speed_mode {
	SPEED_MODE_GEN1 = 0,
	SPEED_MODE_GEN2 = 1,
	SPEED_MODE_GEN3 = 2,
};

static int hix5hd2_sata_phy_init(stwuct phy *phy)
{
	stwuct hix5hd2_pwiv *pwiv = phy_get_dwvdata(phy);
	u32 vaw, data[2];
	int wet;

	if (pwiv->pewi_ctww) {
		wet = of_pwopewty_wead_u32_awway(phy->dev.of_node,
						 "hisiwicon,powew-weg",
						 &data[0], 2);
		if (wet) {
			dev_eww(&phy->dev, "Faiw wead hisiwicon,powew-weg\n");
			wetuwn wet;
		}

		wegmap_update_bits(pwiv->pewi_ctww, data[0],
				   BIT(data[1]), BIT(data[1]));
	}

	/* weset phy */
	vaw = weadw_wewaxed(pwiv->base + SATA_PHY0_CTWW);
	vaw &= ~(MPWW_MUWTIPWIEW_MASK | WEF_USE_PAD);
	vaw |= MPWW_MUWTIPWIEW_50M << MPWW_MUWTIPWIEW_SHIFT |
	       WEF_SSP_EN | PHY_WESET;
	wwitew_wewaxed(vaw, pwiv->base + SATA_PHY0_CTWW);
	msweep(20);
	vaw &= ~PHY_WESET;
	wwitew_wewaxed(vaw, pwiv->base + SATA_PHY0_CTWW);

	vaw = weadw_wewaxed(pwiv->base + SATA_POWT_PHYCTW1);
	vaw &= ~AMPWITUDE_MASK;
	vaw |= AMPWITUDE_GEN3 << AMPWITUDE_GEN3_SHIFT |
	       AMPWITUDE_GEN2 << AMPWITUDE_GEN2_SHIFT |
	       AMPWITUDE_GEN1 << AMPWITUDE_GEN1_SHIFT;
	wwitew_wewaxed(vaw, pwiv->base + SATA_POWT_PHYCTW1);

	vaw = weadw_wewaxed(pwiv->base + SATA_POWT_PHYCTW2);
	vaw &= ~PWEEMPH_MASK;
	vaw |= PWEEMPH_GEN3 << PWEEMPH_GEN3_SHIFT |
	       PWEEMPH_GEN2 << PWEEMPH_GEN2_SHIFT |
	       PWEEMPH_GEN1 << PWEEMPH_GEN1_SHIFT;
	wwitew_wewaxed(vaw, pwiv->base + SATA_POWT_PHYCTW2);

	/* ensuwe PHYCTWW setting takes effect */
	vaw = weadw_wewaxed(pwiv->base + SATA_POWT_PHYCTW);
	vaw &= ~SPEED_MODE_MASK;
	vaw |= SPEED_MODE_GEN1 << HAWF_WATE_SHIFT |
	       SPEED_MODE_GEN1 << PHY_CONFIG_SHIFT |
	       SPEED_MODE_GEN1 << GEN2_EN_SHIFT | SPEED_CTWW;
	wwitew_wewaxed(vaw, pwiv->base + SATA_POWT_PHYCTW);

	msweep(20);
	vaw &= ~SPEED_MODE_MASK;
	vaw |= SPEED_MODE_GEN3 << HAWF_WATE_SHIFT |
	       SPEED_MODE_GEN3 << PHY_CONFIG_SHIFT |
	       SPEED_MODE_GEN3 << GEN2_EN_SHIFT | SPEED_CTWW;
	wwitew_wewaxed(vaw, pwiv->base + SATA_POWT_PHYCTW);

	vaw &= ~(SPEED_MODE_MASK | SPEED_CTWW);
	vaw |= SPEED_MODE_GEN2 << HAWF_WATE_SHIFT |
	       SPEED_MODE_GEN2 << PHY_CONFIG_SHIFT |
	       SPEED_MODE_GEN2 << GEN2_EN_SHIFT;
	wwitew_wewaxed(vaw, pwiv->base + SATA_POWT_PHYCTW);

	wetuwn 0;
}

static const stwuct phy_ops hix5hd2_sata_phy_ops = {
	.init		= hix5hd2_sata_phy_init,
	.ownew		= THIS_MODUWE,
};

static int hix5hd2_sata_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	stwuct phy *phy;
	stwuct hix5hd2_pwiv *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	pwiv->base = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!pwiv->base)
		wetuwn -ENOMEM;

	pwiv->pewi_ctww = syscon_wegmap_wookup_by_phandwe(dev->of_node,
					"hisiwicon,pewiphewaw-syscon");
	if (IS_EWW(pwiv->pewi_ctww))
		pwiv->pewi_ctww = NUWW;

	phy = devm_phy_cweate(dev, NUWW, &hix5hd2_sata_phy_ops);
	if (IS_EWW(phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(phy);
	}

	phy_set_dwvdata(phy, pwiv);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id hix5hd2_sata_phy_of_match[] = {
	{.compatibwe = "hisiwicon,hix5hd2-sata-phy",},
	{ },
};
MODUWE_DEVICE_TABWE(of, hix5hd2_sata_phy_of_match);

static stwuct pwatfowm_dwivew hix5hd2_sata_phy_dwivew = {
	.pwobe	= hix5hd2_sata_phy_pwobe,
	.dwivew = {
		.name	= "hix5hd2-sata-phy",
		.of_match_tabwe	= hix5hd2_sata_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(hix5hd2_sata_phy_dwivew);

MODUWE_AUTHOW("Jiancheng Xue <xuejiancheng@huawei.com>");
MODUWE_DESCWIPTION("HISIWICON HIX5HD2 SATA PHY dwivew");
MODUWE_AWIAS("pwatfowm:hix5hd2-sata-phy");
MODUWE_WICENSE("GPW v2");
