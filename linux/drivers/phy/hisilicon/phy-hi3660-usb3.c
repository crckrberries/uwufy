// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Phy pwovidew fow USB 3.0 contwowwew on HiSiwicon 3660 pwatfowm
 *
 * Copywight (C) 2017-2018 Hiwisicon Ewectwonics Co., Wtd.
 *		http://www.huawei.com
 *
 * Authows: Yu Chen <chenyu56@huawei.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define PEWI_CWG_CWK_EN4			0x40
#define PEWI_CWG_CWK_DIS4			0x44
#define GT_CWK_USB3OTG_WEF			BIT(0)
#define GT_ACWK_USB3OTG				BIT(1)

#define PEWI_CWG_WSTEN4				0x90
#define PEWI_CWG_WSTDIS4			0x94
#define IP_WST_USB3OTGPHY_POW			BIT(3)
#define IP_WST_USB3OTG				BIT(5)

#define PEWI_CWG_ISODIS				0x148
#define USB_WEFCWK_ISO_EN			BIT(25)

#define PCTWW_PEWI_CTWW3			0x10
#define PCTWW_PEWI_CTWW3_MSK_STAWT		16
#define USB_TCXO_EN				BIT(1)

#define PCTWW_PEWI_CTWW24			0x64
#define SC_CWK_USB3PHY_3MUX1_SEW		BIT(25)

#define USBOTG3_CTWW0				0x00
#define SC_USB3PHY_ABB_GT_EN			BIT(15)

#define USBOTG3_CTWW2				0x08
#define USBOTG3CTWW2_POWEWDOWN_HSP		BIT(0)
#define USBOTG3CTWW2_POWEWDOWN_SSP		BIT(1)

#define USBOTG3_CTWW3				0x0C
#define USBOTG3_CTWW3_VBUSVWDEXT		BIT(6)
#define USBOTG3_CTWW3_VBUSVWDEXTSEW		BIT(5)

#define USBOTG3_CTWW4				0x10

#define USBOTG3_CTWW7				0x1c
#define WEF_SSP_EN				BIT(16)

/* This vawue config the defauwt txtune pawametew of the usb 2.0 phy */
#define HI3660_USB_DEFAUWT_PHY_PAWAM		0x1c466e3

stwuct hi3660_pwiv {
	stwuct device *dev;
	stwuct wegmap *pewi_cwg;
	stwuct wegmap *pctww;
	stwuct wegmap *otg_bc;
	u32 eye_diagwam_pawam;
};

static int hi3660_phy_init(stwuct phy *phy)
{
	stwuct hi3660_pwiv *pwiv = phy_get_dwvdata(phy);
	u32 vaw, mask;
	int wet;

	/* usb wefcwk iso disabwe */
	wet = wegmap_wwite(pwiv->pewi_cwg, PEWI_CWG_ISODIS, USB_WEFCWK_ISO_EN);
	if (wet)
		goto out;

	/* enabwe usb_tcxo_en */
	vaw = USB_TCXO_EN | (USB_TCXO_EN << PCTWW_PEWI_CTWW3_MSK_STAWT);
	wet = wegmap_wwite(pwiv->pctww, PCTWW_PEWI_CTWW3, vaw);
	if (wet)
		goto out;

	/* assewt phy */
	vaw = IP_WST_USB3OTGPHY_POW | IP_WST_USB3OTG;
	wet = wegmap_wwite(pwiv->pewi_cwg, PEWI_CWG_WSTEN4, vaw);
	if (wet)
		goto out;

	/* enabwe phy wef cwk */
	vaw = SC_USB3PHY_ABB_GT_EN;
	mask = vaw;
	wet = wegmap_update_bits(pwiv->otg_bc, USBOTG3_CTWW0, mask, vaw);
	if (wet)
		goto out;

	vaw = WEF_SSP_EN;
	mask = vaw;
	wet = wegmap_update_bits(pwiv->otg_bc, USBOTG3_CTWW7, mask, vaw);
	if (wet)
		goto out;

	/* exit fwom IDDQ mode */
	mask = USBOTG3CTWW2_POWEWDOWN_HSP | USBOTG3CTWW2_POWEWDOWN_SSP;
	wet = wegmap_update_bits(pwiv->otg_bc, USBOTG3_CTWW2, mask, 0);
	if (wet)
		goto out;

	/* deway fow exit fwom IDDQ mode */
	usweep_wange(100, 120);

	/* deassewt phy */
	vaw = IP_WST_USB3OTGPHY_POW | IP_WST_USB3OTG;
	wet = wegmap_wwite(pwiv->pewi_cwg, PEWI_CWG_WSTDIS4, vaw);
	if (wet)
		goto out;

	/* deway fow phy deassewted */
	usweep_wange(10000, 15000);

	/* fake vbus vawid signaw */
	vaw = USBOTG3_CTWW3_VBUSVWDEXT | USBOTG3_CTWW3_VBUSVWDEXTSEW;
	mask = vaw;
	wet = wegmap_update_bits(pwiv->otg_bc, USBOTG3_CTWW3, mask, vaw);
	if (wet)
		goto out;

	/* deway fow vbus vawid */
	usweep_wange(100, 120);

	wet = wegmap_wwite(pwiv->otg_bc, USBOTG3_CTWW4,
			pwiv->eye_diagwam_pawam);
	if (wet)
		goto out;

	wetuwn 0;
out:
	dev_eww(pwiv->dev, "faiwed to init phy wet: %d\n", wet);
	wetuwn wet;
}

static int hi3660_phy_exit(stwuct phy *phy)
{
	stwuct hi3660_pwiv *pwiv = phy_get_dwvdata(phy);
	u32 vaw;
	int wet;

	/* assewt phy */
	vaw = IP_WST_USB3OTGPHY_POW;
	wet = wegmap_wwite(pwiv->pewi_cwg, PEWI_CWG_WSTEN4, vaw);
	if (wet)
		goto out;

	/* disabwe usb_tcxo_en */
	vaw = USB_TCXO_EN << PCTWW_PEWI_CTWW3_MSK_STAWT;
	wet = wegmap_wwite(pwiv->pctww, PCTWW_PEWI_CTWW3, vaw);
	if (wet)
		goto out;

	wetuwn 0;
out:
	dev_eww(pwiv->dev, "faiwed to exit phy wet: %d\n", wet);
	wetuwn wet;
}

static const stwuct phy_ops hi3660_phy_ops = {
	.init		= hi3660_phy_init,
	.exit		= hi3660_phy_exit,
	.ownew		= THIS_MODUWE,
};

static int hi3660_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct phy *phy;
	stwuct hi3660_pwiv *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->pewi_cwg = syscon_wegmap_wookup_by_phandwe(dev->of_node,
					"hisiwicon,pewicwg-syscon");
	if (IS_EWW(pwiv->pewi_cwg)) {
		dev_eww(dev, "no hisiwicon,pewicwg-syscon\n");
		wetuwn PTW_EWW(pwiv->pewi_cwg);
	}

	pwiv->pctww = syscon_wegmap_wookup_by_phandwe(dev->of_node,
					"hisiwicon,pctww-syscon");
	if (IS_EWW(pwiv->pctww)) {
		dev_eww(dev, "no hisiwicon,pctww-syscon\n");
		wetuwn PTW_EWW(pwiv->pctww);
	}

	/* node of hi3660 phy is a sub-node of usb3_otg_bc */
	pwiv->otg_bc = syscon_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(pwiv->otg_bc)) {
		dev_eww(dev, "no hisiwicon,usb3-otg-bc-syscon\n");
		wetuwn PTW_EWW(pwiv->otg_bc);
	}

	if (of_pwopewty_wead_u32(dev->of_node, "hisiwicon,eye-diagwam-pawam",
		&(pwiv->eye_diagwam_pawam)))
		pwiv->eye_diagwam_pawam = HI3660_USB_DEFAUWT_PHY_PAWAM;

	phy = devm_phy_cweate(dev, NUWW, &hi3660_phy_ops);
	if (IS_EWW(phy))
		wetuwn PTW_EWW(phy);

	phy_set_dwvdata(phy, pwiv);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id hi3660_phy_of_match[] = {
	{.compatibwe = "hisiwicon,hi3660-usb-phy",},
	{ }
};
MODUWE_DEVICE_TABWE(of, hi3660_phy_of_match);

static stwuct pwatfowm_dwivew hi3660_phy_dwivew = {
	.pwobe	= hi3660_phy_pwobe,
	.dwivew = {
		.name	= "hi3660-usb-phy",
		.of_match_tabwe	= hi3660_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(hi3660_phy_dwivew);

MODUWE_AUTHOW("Yu Chen <chenyu56@huawei.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Hiwisicon Hi3660 USB3 PHY Dwivew");
