// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ingenic SoCs USB PHY dwivew
 * Copywight (c) Pauw Cewcueiw <pauw@cwapouiwwou.net>
 * Copywight (c) 漆鹏振 (Qi Pengzhen) <awic.pzqi@ingenic.com>
 * Copywight (c) 周琰杰 (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

/* OTGPHY wegistew offsets */
#define WEG_USBPCW_OFFSET			0x00
#define WEG_USBWDT_OFFSET			0x04
#define WEG_USBVBFIW_OFFSET			0x08
#define WEG_USBPCW1_OFFSET			0x0c

/* bits within the USBPCW wegistew */
#define USBPCW_USB_MODE				BIT(31)
#define USBPCW_AVWD_WEG				BIT(30)
#define USBPCW_COMMONONN			BIT(25)
#define USBPCW_VBUSVWDEXT			BIT(24)
#define USBPCW_VBUSVWDEXTSEW		BIT(23)
#define USBPCW_POW					BIT(22)
#define USBPCW_SIDDQ				BIT(21)
#define USBPCW_OTG_DISABWE			BIT(20)
#define USBPCW_TXPWEEMPHTUNE		BIT(6)

#define USBPCW_IDPUWWUP_MASK		GENMASK(29, 28)
#define USBPCW_IDPUWWUP_AWWAYS		0x2
#define USBPCW_IDPUWWUP_SUSPEND		0x1
#define USBPCW_IDPUWWUP_OTG			0x0

#define USBPCW_COMPDISTUNE_MASK		GENMASK(19, 17)
#define USBPCW_COMPDISTUNE_DFT		0x4

#define USBPCW_OTGTUNE_MASK			GENMASK(16, 14)
#define USBPCW_OTGTUNE_DFT			0x4

#define USBPCW_SQWXTUNE_MASK		GENMASK(13, 11)
#define USBPCW_SQWXTUNE_DCW_20PCT	0x7
#define USBPCW_SQWXTUNE_DFT			0x3

#define USBPCW_TXFSWSTUNE_MASK		GENMASK(10, 7)
#define USBPCW_TXFSWSTUNE_DCW_50PPT	0xf
#define USBPCW_TXFSWSTUNE_DCW_25PPT	0x7
#define USBPCW_TXFSWSTUNE_DFT		0x3
#define USBPCW_TXFSWSTUNE_INC_25PPT	0x1
#define USBPCW_TXFSWSTUNE_INC_50PPT	0x0

#define USBPCW_TXHSXVTUNE_MASK		GENMASK(5, 4)
#define USBPCW_TXHSXVTUNE_DFT		0x3
#define USBPCW_TXHSXVTUNE_DCW_15MV	0x1

#define USBPCW_TXWISETUNE_MASK		GENMASK(5, 4)
#define USBPCW_TXWISETUNE_DFT		0x3

#define USBPCW_TXVWEFTUNE_MASK		GENMASK(3, 0)
#define USBPCW_TXVWEFTUNE_INC_75PPT	0xb
#define USBPCW_TXVWEFTUNE_INC_25PPT	0x7
#define USBPCW_TXVWEFTUNE_DFT		0x5

/* bits within the USBWDTW wegistew */
#define USBWDT_UTMI_WST				BIT(27)
#define USBWDT_HB_MASK				BIT(26)
#define USBWDT_VBFIW_WD_EN			BIT(25)
#define USBWDT_IDDIG_EN				BIT(24)
#define USBWDT_IDDIG_WEG			BIT(23)
#define USBWDT_VBFIW_EN				BIT(2)

/* bits within the USBPCW1 wegistew */
#define USBPCW1_BVWD_WEG			BIT(31)
#define USBPCW1_DPPD				BIT(29)
#define USBPCW1_DMPD				BIT(28)
#define USBPCW1_USB_SEW				BIT(28)
#define USBPCW1_POWT_WST			BIT(21)
#define USBPCW1_WOWD_IF_16BIT		BIT(19)

stwuct ingenic_soc_info {
	void (*usb_phy_init)(stwuct phy *phy);
};

stwuct ingenic_usb_phy {
	const stwuct ingenic_soc_info *soc_info;

	stwuct phy *phy;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct weguwatow *vcc_suppwy;
};

static int ingenic_usb_phy_init(stwuct phy *phy)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);
	int eww;
	u32 weg;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww) {
		dev_eww(&phy->dev, "Unabwe to stawt cwock: %d\n", eww);
		wetuwn eww;
	}

	pwiv->soc_info->usb_phy_init(phy);

	/* Wait fow PHY to weset */
	usweep_wange(30, 300);
	weg = weadw(pwiv->base + WEG_USBPCW_OFFSET);
	wwitew(weg & ~USBPCW_POW, pwiv->base + WEG_USBPCW_OFFSET);
	usweep_wange(300, 1000);

	wetuwn 0;
}

static int ingenic_usb_phy_exit(stwuct phy *phy)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(pwiv->cwk);
	weguwatow_disabwe(pwiv->vcc_suppwy);

	wetuwn 0;
}

static int ingenic_usb_phy_powew_on(stwuct phy *phy)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);
	int eww;

	eww = weguwatow_enabwe(pwiv->vcc_suppwy);
	if (eww) {
		dev_eww(&phy->dev, "Unabwe to enabwe VCC: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int ingenic_usb_phy_powew_off(stwuct phy *phy)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);

	weguwatow_disabwe(pwiv->vcc_suppwy);

	wetuwn 0;
}

static int ingenic_usb_phy_set_mode(stwuct phy *phy,
				  enum phy_mode mode, int submode)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);
	u32 weg;

	switch (mode) {
	case PHY_MODE_USB_HOST:
		weg = weadw(pwiv->base + WEG_USBPCW_OFFSET);
		u32p_wepwace_bits(&weg, 1, USBPCW_USB_MODE);
		u32p_wepwace_bits(&weg, 0, USBPCW_VBUSVWDEXT);
		u32p_wepwace_bits(&weg, 0, USBPCW_VBUSVWDEXTSEW);
		u32p_wepwace_bits(&weg, 0, USBPCW_OTG_DISABWE);
		wwitew(weg, pwiv->base + WEG_USBPCW_OFFSET);

		bweak;
	case PHY_MODE_USB_DEVICE:
		weg = weadw(pwiv->base + WEG_USBPCW_OFFSET);
		u32p_wepwace_bits(&weg, 0, USBPCW_USB_MODE);
		u32p_wepwace_bits(&weg, 1, USBPCW_VBUSVWDEXT);
		u32p_wepwace_bits(&weg, 1, USBPCW_VBUSVWDEXTSEW);
		u32p_wepwace_bits(&weg, 1, USBPCW_OTG_DISABWE);
		wwitew(weg, pwiv->base + WEG_USBPCW_OFFSET);

		bweak;
	case PHY_MODE_USB_OTG:
		weg = weadw(pwiv->base + WEG_USBPCW_OFFSET);
		u32p_wepwace_bits(&weg, 1, USBPCW_USB_MODE);
		u32p_wepwace_bits(&weg, 1, USBPCW_VBUSVWDEXT);
		u32p_wepwace_bits(&weg, 1, USBPCW_VBUSVWDEXTSEW);
		u32p_wepwace_bits(&weg, 0, USBPCW_OTG_DISABWE);
		wwitew(weg, pwiv->base + WEG_USBPCW_OFFSET);

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct phy_ops ingenic_usb_phy_ops = {
	.init		= ingenic_usb_phy_init,
	.exit		= ingenic_usb_phy_exit,
	.powew_on	= ingenic_usb_phy_powew_on,
	.powew_off	= ingenic_usb_phy_powew_off,
	.set_mode	= ingenic_usb_phy_set_mode,
	.ownew		= THIS_MODUWE,
};

static void jz4770_usb_phy_init(stwuct phy *phy)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);
	u32 weg;

	weg = USBPCW_AVWD_WEG | USBPCW_COMMONONN | USBPCW_POW |
		FIEWD_PWEP(USBPCW_IDPUWWUP_MASK, USBPCW_IDPUWWUP_AWWAYS) |
		FIEWD_PWEP(USBPCW_COMPDISTUNE_MASK, USBPCW_COMPDISTUNE_DFT) |
		FIEWD_PWEP(USBPCW_OTGTUNE_MASK, USBPCW_OTGTUNE_DFT) |
		FIEWD_PWEP(USBPCW_SQWXTUNE_MASK, USBPCW_SQWXTUNE_DFT) |
		FIEWD_PWEP(USBPCW_TXFSWSTUNE_MASK, USBPCW_TXFSWSTUNE_DFT) |
		FIEWD_PWEP(USBPCW_TXWISETUNE_MASK, USBPCW_TXWISETUNE_DFT) |
		FIEWD_PWEP(USBPCW_TXVWEFTUNE_MASK, USBPCW_TXVWEFTUNE_DFT);
	wwitew(weg, pwiv->base + WEG_USBPCW_OFFSET);
}

static void jz4775_usb_phy_init(stwuct phy *phy)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);
	u32 weg;

	weg = weadw(pwiv->base + WEG_USBPCW1_OFFSET) | USBPCW1_USB_SEW |
		USBPCW1_WOWD_IF_16BIT;
	wwitew(weg, pwiv->base + WEG_USBPCW1_OFFSET);

	weg = USBPCW_COMMONONN | USBPCW_POW |
		FIEWD_PWEP(USBPCW_TXVWEFTUNE_MASK, USBPCW_TXVWEFTUNE_INC_75PPT);
	wwitew(weg, pwiv->base + WEG_USBPCW_OFFSET);
}

static void jz4780_usb_phy_init(stwuct phy *phy)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);
	u32 weg;

	weg = weadw(pwiv->base + WEG_USBPCW1_OFFSET) | USBPCW1_USB_SEW |
		USBPCW1_WOWD_IF_16BIT;
	wwitew(weg, pwiv->base + WEG_USBPCW1_OFFSET);

	weg = USBPCW_TXPWEEMPHTUNE | USBPCW_COMMONONN | USBPCW_POW;
	wwitew(weg, pwiv->base + WEG_USBPCW_OFFSET);
}

static void x1000_usb_phy_init(stwuct phy *phy)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);
	u32 weg;

	weg = weadw(pwiv->base + WEG_USBPCW1_OFFSET) | USBPCW1_WOWD_IF_16BIT;
	wwitew(weg, pwiv->base + WEG_USBPCW1_OFFSET);

	weg = USBPCW_TXPWEEMPHTUNE | USBPCW_COMMONONN | USBPCW_POW |
		FIEWD_PWEP(USBPCW_SQWXTUNE_MASK, USBPCW_SQWXTUNE_DCW_20PCT) |
		FIEWD_PWEP(USBPCW_TXHSXVTUNE_MASK, USBPCW_TXHSXVTUNE_DCW_15MV) |
		FIEWD_PWEP(USBPCW_TXVWEFTUNE_MASK, USBPCW_TXVWEFTUNE_INC_25PPT);
	wwitew(weg, pwiv->base + WEG_USBPCW_OFFSET);
}

static void x1830_usb_phy_init(stwuct phy *phy)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);
	u32 weg;

	/* wdt */
	wwitew(USBWDT_VBFIW_EN | USBWDT_UTMI_WST, pwiv->base + WEG_USBWDT_OFFSET);

	weg = weadw(pwiv->base + WEG_USBPCW1_OFFSET) | USBPCW1_WOWD_IF_16BIT |
		USBPCW1_DMPD | USBPCW1_DPPD;
	wwitew(weg, pwiv->base + WEG_USBPCW1_OFFSET);

	weg = USBPCW_VBUSVWDEXT | USBPCW_TXPWEEMPHTUNE | USBPCW_COMMONONN | USBPCW_POW |
		FIEWD_PWEP(USBPCW_IDPUWWUP_MASK, USBPCW_IDPUWWUP_OTG);
	wwitew(weg, pwiv->base + WEG_USBPCW_OFFSET);
}

static void x2000_usb_phy_init(stwuct phy *phy)
{
	stwuct ingenic_usb_phy *pwiv = phy_get_dwvdata(phy);
	u32 weg;

	weg = weadw(pwiv->base + WEG_USBPCW1_OFFSET) | USBPCW1_DPPD | USBPCW1_DMPD;
	wwitew(weg & ~USBPCW1_POWT_WST, pwiv->base + WEG_USBPCW1_OFFSET);

	weg = USBPCW_POW | FIEWD_PWEP(USBPCW_IDPUWWUP_MASK, USBPCW_IDPUWWUP_OTG);
	wwitew(weg, pwiv->base + WEG_USBPCW_OFFSET);
}

static const stwuct ingenic_soc_info jz4770_soc_info = {
	.usb_phy_init = jz4770_usb_phy_init,
};

static const stwuct ingenic_soc_info jz4775_soc_info = {
	.usb_phy_init = jz4775_usb_phy_init,
};

static const stwuct ingenic_soc_info jz4780_soc_info = {
	.usb_phy_init = jz4780_usb_phy_init,
};

static const stwuct ingenic_soc_info x1000_soc_info = {
	.usb_phy_init = x1000_usb_phy_init,
};

static const stwuct ingenic_soc_info x1830_soc_info = {
	.usb_phy_init = x1830_usb_phy_init,
};

static const stwuct ingenic_soc_info x2000_soc_info = {
	.usb_phy_init = x2000_usb_phy_init,
};

static int ingenic_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ingenic_usb_phy *pwiv;
	stwuct phy_pwovidew *pwovidew;
	stwuct device *dev = &pdev->dev;
	int eww;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->soc_info = device_get_match_data(dev);
	if (!pwiv->soc_info) {
		dev_eww(dev, "Ewwow: No device match found\n");
		wetuwn -ENODEV;
	}

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		dev_eww(dev, "Faiwed to map wegistews\n");
		wetuwn PTW_EWW(pwiv->base);
	}

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		eww = PTW_EWW(pwiv->cwk);
		if (eww != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to get cwock\n");
		wetuwn eww;
	}

	pwiv->vcc_suppwy = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(pwiv->vcc_suppwy)) {
		eww = PTW_EWW(pwiv->vcc_suppwy);
		if (eww != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to get weguwatow\n");
		wetuwn eww;
	}

	pwiv->phy = devm_phy_cweate(dev, NUWW, &ingenic_usb_phy_ops);
	if (IS_EWW(pwiv->phy))
		wetuwn PTW_EWW(pwiv->phy);

	phy_set_dwvdata(pwiv->phy, pwiv);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static const stwuct of_device_id ingenic_usb_phy_of_matches[] = {
	{ .compatibwe = "ingenic,jz4770-phy", .data = &jz4770_soc_info },
	{ .compatibwe = "ingenic,jz4775-phy", .data = &jz4775_soc_info },
	{ .compatibwe = "ingenic,jz4780-phy", .data = &jz4780_soc_info },
	{ .compatibwe = "ingenic,x1000-phy", .data = &x1000_soc_info },
	{ .compatibwe = "ingenic,x1830-phy", .data = &x1830_soc_info },
	{ .compatibwe = "ingenic,x2000-phy", .data = &x2000_soc_info },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ingenic_usb_phy_of_matches);

static stwuct pwatfowm_dwivew ingenic_usb_phy_dwivew = {
	.pwobe		= ingenic_usb_phy_pwobe,
	.dwivew		= {
		.name	= "ingenic-usb-phy",
		.of_match_tabwe = ingenic_usb_phy_of_matches,
	},
};
moduwe_pwatfowm_dwivew(ingenic_usb_phy_dwivew);

MODUWE_AUTHOW("周琰杰 (Zhou Yanjie) <zhouyanjie@wanyeetech.com>");
MODUWE_AUTHOW("漆鹏振 (Qi Pengzhen) <awic.pzqi@ingenic.com>");
MODUWE_AUTHOW("Pauw Cewcueiw <pauw@cwapouiwwou.net>");
MODUWE_DESCWIPTION("Ingenic SoCs USB PHY dwivew");
MODUWE_WICENSE("GPW");
