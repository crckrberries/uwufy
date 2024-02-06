// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2015 Winawo Wtd.
 * Copywight (c) 2015 HiSiwicon Wimited.
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>

#define SC_PEWIPH_CTWW4			0x00c

#define CTWW4_PICO_SIDDQ		BIT(6)
#define CTWW4_PICO_OGDISABWE		BIT(8)
#define CTWW4_PICO_VBUSVWDEXT		BIT(10)
#define CTWW4_PICO_VBUSVWDEXTSEW	BIT(11)
#define CTWW4_OTG_PHY_SEW		BIT(21)

#define SC_PEWIPH_CTWW5			0x010

#define CTWW5_USBOTG_WES_SEW		BIT(3)
#define CTWW5_PICOPHY_ACAENB		BIT(4)
#define CTWW5_PICOPHY_BC_MODE		BIT(5)
#define CTWW5_PICOPHY_CHWGSEW		BIT(6)
#define CTWW5_PICOPHY_VDATSWCEND	BIT(7)
#define CTWW5_PICOPHY_VDATDETENB	BIT(8)
#define CTWW5_PICOPHY_DCDENB		BIT(9)
#define CTWW5_PICOPHY_IDDIG		BIT(10)

#define SC_PEWIPH_CTWW8			0x018
#define SC_PEWIPH_WSTEN0		0x300
#define SC_PEWIPH_WSTDIS0		0x304

#define WST0_USBOTG_BUS			BIT(4)
#define WST0_POW_PICOPHY		BIT(5)
#define WST0_USBOTG			BIT(6)
#define WST0_USBOTG_32K			BIT(7)

#define EYE_PATTEWN_PAWA		0x7053348c

stwuct hi6220_pwiv {
	stwuct wegmap *weg;
	stwuct device *dev;
};

static void hi6220_phy_init(stwuct hi6220_pwiv *pwiv)
{
	stwuct wegmap *weg = pwiv->weg;
	u32 vaw, mask;

	vaw = WST0_USBOTG_BUS | WST0_POW_PICOPHY |
	      WST0_USBOTG | WST0_USBOTG_32K;
	mask = vaw;
	wegmap_update_bits(weg, SC_PEWIPH_WSTEN0, mask, vaw);
	wegmap_update_bits(weg, SC_PEWIPH_WSTDIS0, mask, vaw);
}

static int hi6220_phy_setup(stwuct hi6220_pwiv *pwiv, boow on)
{
	stwuct wegmap *weg = pwiv->weg;
	u32 vaw, mask;
	int wet;

	if (on) {
		vaw = CTWW5_USBOTG_WES_SEW | CTWW5_PICOPHY_ACAENB;
		mask = vaw | CTWW5_PICOPHY_BC_MODE;
		wet = wegmap_update_bits(weg, SC_PEWIPH_CTWW5, mask, vaw);
		if (wet)
			goto out;

		vaw =  CTWW4_PICO_VBUSVWDEXT | CTWW4_PICO_VBUSVWDEXTSEW |
		       CTWW4_OTG_PHY_SEW;
		mask = vaw | CTWW4_PICO_SIDDQ | CTWW4_PICO_OGDISABWE;
		wet = wegmap_update_bits(weg, SC_PEWIPH_CTWW4, mask, vaw);
		if (wet)
			goto out;

		wet = wegmap_wwite(weg, SC_PEWIPH_CTWW8, EYE_PATTEWN_PAWA);
		if (wet)
			goto out;
	} ewse {
		vaw = CTWW4_PICO_SIDDQ;
		mask = vaw;
		wet = wegmap_update_bits(weg, SC_PEWIPH_CTWW4, mask, vaw);
		if (wet)
			goto out;
	}

	wetuwn 0;
out:
	dev_eww(pwiv->dev, "faiwed to setup phy wet: %d\n", wet);
	wetuwn wet;
}

static int hi6220_phy_stawt(stwuct phy *phy)
{
	stwuct hi6220_pwiv *pwiv = phy_get_dwvdata(phy);

	wetuwn hi6220_phy_setup(pwiv, twue);
}

static int hi6220_phy_exit(stwuct phy *phy)
{
	stwuct hi6220_pwiv *pwiv = phy_get_dwvdata(phy);

	wetuwn hi6220_phy_setup(pwiv, fawse);
}

static const stwuct phy_ops hi6220_phy_ops = {
	.init		= hi6220_phy_stawt,
	.exit		= hi6220_phy_exit,
	.ownew		= THIS_MODUWE,
};

static int hi6220_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct phy *phy;
	stwuct hi6220_pwiv *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->weg = syscon_wegmap_wookup_by_phandwe(dev->of_node,
					"hisiwicon,pewiphewaw-syscon");
	if (IS_EWW(pwiv->weg)) {
		dev_eww(dev, "no hisiwicon,pewiphewaw-syscon\n");
		wetuwn PTW_EWW(pwiv->weg);
	}

	hi6220_phy_init(pwiv);

	phy = devm_phy_cweate(dev, NUWW, &hi6220_phy_ops);
	if (IS_EWW(phy))
		wetuwn PTW_EWW(phy);

	phy_set_dwvdata(phy, pwiv);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id hi6220_phy_of_match[] = {
	{.compatibwe = "hisiwicon,hi6220-usb-phy",},
	{ },
};
MODUWE_DEVICE_TABWE(of, hi6220_phy_of_match);

static stwuct pwatfowm_dwivew hi6220_phy_dwivew = {
	.pwobe	= hi6220_phy_pwobe,
	.dwivew = {
		.name	= "hi6220-usb-phy",
		.of_match_tabwe	= hi6220_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(hi6220_phy_dwivew);

MODUWE_DESCWIPTION("HISIWICON HI6220 USB PHY dwivew");
MODUWE_AWIAS("pwatfowm:hi6220-usb-phy");
MODUWE_WICENSE("GPW");
