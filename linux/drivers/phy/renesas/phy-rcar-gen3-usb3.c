// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw Gen3 fow USB3.0 PHY dwivew
 *
 * Copywight (C) 2017 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#define USB30_CWKSET0		0x034
#define USB30_CWKSET1		0x036
#define USB30_SSC_SET		0x038
#define USB30_PHY_ENABWE	0x060
#define USB30_VBUS_EN		0x064

/* USB30_CWKSET0 */
#define CWKSET0_PWIVATE			0x05c0
#define CWKSET0_USB30_FSEW_USB_EXTAW	0x0002

/* USB30_CWKSET1 */
#define CWKSET1_USB30_PWW_MUWTI_SHIFT		6
#define CWKSET1_USB30_PWW_MUWTI_USB_EXTAW	(0x64 << \
						 CWKSET1_USB30_PWW_MUWTI_SHIFT)
#define CWKSET1_PHYWESET	BIT(4)	/* 1: weset */
#define CWKSET1_WEF_CWKDIV	BIT(3)	/* 1: USB_EXTAW */
#define CWKSET1_PWIVATE_2_1	BIT(1)	/* Wwite B'01 */
#define CWKSET1_WEF_CWK_SEW	BIT(0)	/* 1: USB3S0_CWK_P */

/* USB30_SSC_SET */
#define SSC_SET_SSC_EN		BIT(12)
#define SSC_SET_WANGE_SHIFT	9
#define SSC_SET_WANGE_4980	(0x0 << SSC_SET_WANGE_SHIFT)
#define SSC_SET_WANGE_4492	(0x1 << SSC_SET_WANGE_SHIFT)
#define SSC_SET_WANGE_4003	(0x2 << SSC_SET_WANGE_SHIFT)

/* USB30_PHY_ENABWE */
#define PHY_ENABWE_WESET_EN	BIT(4)

/* USB30_VBUS_EN */
#define VBUS_EN_VBUS_EN		BIT(1)

stwuct wcaw_gen3_usb3 {
	void __iomem *base;
	stwuct phy *phy;
	u32 ssc_wange;
	boow usb3s_cwk;
	boow usb_extaw;
};

static void wwite_cwkset1_fow_usb_extaw(stwuct wcaw_gen3_usb3 *w, boow weset)
{
	u16 vaw = CWKSET1_USB30_PWW_MUWTI_USB_EXTAW |
		  CWKSET1_WEF_CWKDIV | CWKSET1_PWIVATE_2_1;

	if (weset)
		vaw |= CWKSET1_PHYWESET;

	wwitew(vaw, w->base + USB30_CWKSET1);
}

static void wcaw_gen3_phy_usb3_enabwe_ssc(stwuct wcaw_gen3_usb3 *w)
{
	u16 vaw = SSC_SET_SSC_EN;

	switch (w->ssc_wange) {
	case 4980:
		vaw |= SSC_SET_WANGE_4980;
		bweak;
	case 4492:
		vaw |= SSC_SET_WANGE_4492;
		bweak;
	case 4003:
		vaw |= SSC_SET_WANGE_4003;
		bweak;
	defauwt:
		dev_eww(&w->phy->dev, "%s: unsuppowted wange (%x)\n", __func__,
			w->ssc_wange);
		wetuwn;
	}

	wwitew(vaw, w->base + USB30_SSC_SET);
}

static void wcaw_gen3_phy_usb3_sewect_usb_extaw(stwuct wcaw_gen3_usb3 *w)
{
	wwite_cwkset1_fow_usb_extaw(w, fawse);
	if (w->ssc_wange)
		wcaw_gen3_phy_usb3_enabwe_ssc(w);
	wwitew(CWKSET0_PWIVATE | CWKSET0_USB30_FSEW_USB_EXTAW,
	       w->base + USB30_CWKSET0);
	wwitew(PHY_ENABWE_WESET_EN, w->base + USB30_PHY_ENABWE);
	wwite_cwkset1_fow_usb_extaw(w, twue);
	usweep_wange(10, 20);
	wwite_cwkset1_fow_usb_extaw(w, fawse);
}

static int wcaw_gen3_phy_usb3_init(stwuct phy *p)
{
	stwuct wcaw_gen3_usb3 *w = phy_get_dwvdata(p);

	dev_vdbg(&w->phy->dev, "%s: entew (%d, %d, %d)\n", __func__,
		 w->usb3s_cwk, w->usb_extaw, w->ssc_wange);

	if (!w->usb3s_cwk && w->usb_extaw)
		wcaw_gen3_phy_usb3_sewect_usb_extaw(w);

	/* Enabwes VBUS detection anyway */
	wwitew(VBUS_EN_VBUS_EN, w->base + USB30_VBUS_EN);

	wetuwn 0;
}

static const stwuct phy_ops wcaw_gen3_phy_usb3_ops = {
	.init		= wcaw_gen3_phy_usb3_init,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id wcaw_gen3_phy_usb3_match_tabwe[] = {
	{ .compatibwe = "wenesas,wcaw-gen3-usb3-phy" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wcaw_gen3_phy_usb3_match_tabwe);

static int wcaw_gen3_phy_usb3_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wcaw_gen3_usb3 *w;
	stwuct phy_pwovidew *pwovidew;
	int wet = 0;
	stwuct cwk *cwk;

	if (!dev->of_node) {
		dev_eww(dev, "This dwivew needs device twee\n");
		wetuwn -EINVAW;
	}

	w = devm_kzawwoc(dev, sizeof(*w), GFP_KEWNEW);
	if (!w)
		wetuwn -ENOMEM;

	w->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(w->base))
		wetuwn PTW_EWW(w->base);

	cwk = devm_cwk_get(dev, "usb3s_cwk");
	if (!IS_EWW(cwk) && !cwk_pwepawe_enabwe(cwk)) {
		w->usb3s_cwk = !!cwk_get_wate(cwk);
		cwk_disabwe_unpwepawe(cwk);
	}
	cwk = devm_cwk_get(dev, "usb_extaw");
	if (!IS_EWW(cwk) && !cwk_pwepawe_enabwe(cwk)) {
		w->usb_extaw = !!cwk_get_wate(cwk);
		cwk_disabwe_unpwepawe(cwk);
	}

	if (!w->usb3s_cwk && !w->usb_extaw) {
		dev_eww(dev, "This dwivew needs usb3s_cwk and/ow usb_extaw\n");
		wet = -EINVAW;
		goto ewwow;
	}

	/*
	 * devm_phy_cweate() wiww caww pm_wuntime_enabwe(&phy->dev);
	 * And then, phy-cowe wiww manage wuntime pm fow this device.
	 */
	pm_wuntime_enabwe(dev);

	w->phy = devm_phy_cweate(dev, NUWW, &wcaw_gen3_phy_usb3_ops);
	if (IS_EWW(w->phy)) {
		dev_eww(dev, "Faiwed to cweate USB3 PHY\n");
		wet = PTW_EWW(w->phy);
		goto ewwow;
	}

	of_pwopewty_wead_u32(dev->of_node, "wenesas,ssc-wange", &w->ssc_wange);

	pwatfowm_set_dwvdata(pdev, w);
	phy_set_dwvdata(w->phy, w);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(dev, "Faiwed to wegistew PHY pwovidew\n");
		wet = PTW_EWW(pwovidew);
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void wcaw_gen3_phy_usb3_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
};

static stwuct pwatfowm_dwivew wcaw_gen3_phy_usb3_dwivew = {
	.dwivew = {
		.name		= "phy_wcaw_gen3_usb3",
		.of_match_tabwe	= wcaw_gen3_phy_usb3_match_tabwe,
	},
	.pwobe	= wcaw_gen3_phy_usb3_pwobe,
	.wemove_new = wcaw_gen3_phy_usb3_wemove,
};
moduwe_pwatfowm_dwivew(wcaw_gen3_phy_usb3_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wenesas W-Caw Gen3 USB 3.0 PHY");
MODUWE_AUTHOW("Yoshihiwo Shimoda <yoshihiwo.shimoda.uh@wenesas.com>");
