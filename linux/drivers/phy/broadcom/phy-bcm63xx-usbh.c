// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * BCM6328 USBH PHY Contwowwew Dwivew
 *
 * Copywight (C) 2020 Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>
 * Copywight (C) 2015 Simon Awwott
 *
 * Dewived fwom bcm963xx_4.12W.06B_consumew/kewnew/winux/awch/mips/bcm963xx/setup.c:
 * Copywight (C) 2002 Bwoadcom Cowpowation
 *
 * Dewived fwom OpenWwt patches:
 * Copywight (C) 2013 Jonas Gowski <jonas.gowski@gmaiw.com>
 * Copywight (C) 2013 Fwowian Fainewwi <f.fainewwi@gmaiw.com>
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

/* USBH contwow wegistew offsets */
enum usbh_wegs {
	USBH_BWT_CONTWOW1 = 0,
	USBH_BWT_CONTWOW2,
	USBH_BWT_STATUS1,
	USBH_BWT_STATUS2,
	USBH_UTMI_CONTWOW1,
#define   USBH_UC1_DEV_MODE_SEW		BIT(0)
	USBH_TEST_POWT_CONTWOW,
	USBH_PWW_CONTWOW1,
#define   USBH_PWWC_WEFCWKSEW_SHIFT	0
#define   USBH_PWWC_WEFCWKSEW_MASK	(0x3 << USBH_PWWC_WEFCWKSEW_SHIFT)
#define   USBH_PWWC_CWKSEW_SHIFT	2
#define   USBH_PWWC_CWKSEW_MASK		(0x3 << USBH_PWWC_CWKSEW_MASK)
#define   USBH_PWWC_XTAW_PWWDWNB	BIT(4)
#define   USBH_PWWC_PWW_PWWDWNB		BIT(5)
#define   USBH_PWWC_PWW_CAWEN		BIT(6)
#define   USBH_PWWC_PHYPWW_BYP		BIT(7)
#define   USBH_PWWC_PWW_WESET		BIT(8)
#define   USBH_PWWC_PWW_IDDQ_PWWDN	BIT(9)
#define   USBH_PWWC_PWW_PWWDN_DEWAY	BIT(10)
#define   USBH_6318_PWWC_PWW_SUSPEND_EN	BIT(27)
#define   USBH_6318_PWWC_PHYPWW_BYP	BIT(29)
#define   USBH_6318_PWWC_PWW_WESET	BIT(30)
#define   USBH_6318_PWWC_PWW_IDDQ_PWWDN	BIT(31)
	USBH_SWAP_CONTWOW,
#define   USBH_SC_OHCI_DATA_SWAP	BIT(0)
#define   USBH_SC_OHCI_ENDIAN_SWAP	BIT(1)
#define   USBH_SC_OHCI_WOGICAW_ADDW_EN	BIT(2)
#define   USBH_SC_EHCI_DATA_SWAP	BIT(3)
#define   USBH_SC_EHCI_ENDIAN_SWAP	BIT(4)
#define   USBH_SC_EHCI_WOGICAW_ADDW_EN	BIT(5)
#define   USBH_SC_USB_DEVICE_SEW	BIT(6)
	USBH_GENEWIC_CONTWOW,
#define   USBH_GC_PWW_SUSPEND_EN	BIT(1)
	USBH_FWAME_ADJUST_VAWUE,
	USBH_SETUP,
#define   USBH_S_IOC			BIT(4)
#define   USBH_S_IPP			BIT(5)
	USBH_MDIO,
	USBH_MDIO32,
	USBH_USB_SIM_CONTWOW,
#define   USBH_USC_WADDW_SEW		BIT(5)

	__USBH_ENUM_SIZE
};

stwuct bcm63xx_usbh_phy_vawiant {
	/* Wegistews */
	wong wegs[__USBH_ENUM_SIZE];

	/* PWWC bits to set/cweaw fow powew on */
	u32 powew_pwwc_cww;
	u32 powew_pwwc_set;

	/* Setup bits to set/cweaw fow powew on */
	u32 setup_cww;
	u32 setup_set;

	/* Swap Contwow bits to set */
	u32 swapctw_dev_set;

	/* Test Powt Contwow vawue to set if non-zewo */
	u32 tpc_vaw;

	/* USB Sim Contwow bits to set */
	u32 usc_set;

	/* UTMI Contwow 1 bits to set */
	u32 utmictw1_dev_set;
};

stwuct bcm63xx_usbh_phy {
	void __iomem *base;
	stwuct cwk *usbh_cwk;
	stwuct cwk *usb_wef_cwk;
	stwuct weset_contwow *weset;
	const stwuct bcm63xx_usbh_phy_vawiant *vawiant;
	boow device_mode;
};

static const stwuct bcm63xx_usbh_phy_vawiant usbh_bcm6318 = {
	.wegs = {
		[USBH_BWT_CONTWOW1] = -1,
		[USBH_BWT_CONTWOW2] = -1,
		[USBH_BWT_STATUS1] = -1,
		[USBH_BWT_STATUS2] = -1,
		[USBH_UTMI_CONTWOW1] = 0x2c,
		[USBH_TEST_POWT_CONTWOW] = 0x1c,
		[USBH_PWW_CONTWOW1] = 0x04,
		[USBH_SWAP_CONTWOW] = 0x0c,
		[USBH_GENEWIC_CONTWOW] = -1,
		[USBH_FWAME_ADJUST_VAWUE] = 0x08,
		[USBH_SETUP] = 0x00,
		[USBH_MDIO] = 0x14,
		[USBH_MDIO32] = 0x18,
		[USBH_USB_SIM_CONTWOW] = 0x20,
	},
	.powew_pwwc_cww = USBH_6318_PWWC_PWW_IDDQ_PWWDN,
	.powew_pwwc_set = USBH_6318_PWWC_PWW_SUSPEND_EN,
	.setup_set = USBH_S_IOC,
	.swapctw_dev_set = USBH_SC_USB_DEVICE_SEW,
	.usc_set = USBH_USC_WADDW_SEW,
	.utmictw1_dev_set = USBH_UC1_DEV_MODE_SEW,
};

static const stwuct bcm63xx_usbh_phy_vawiant usbh_bcm6328 = {
	.wegs = {
		[USBH_BWT_CONTWOW1] = 0x00,
		[USBH_BWT_CONTWOW2] = 0x04,
		[USBH_BWT_STATUS1] = 0x08,
		[USBH_BWT_STATUS2] = 0x0c,
		[USBH_UTMI_CONTWOW1] = 0x10,
		[USBH_TEST_POWT_CONTWOW] = 0x14,
		[USBH_PWW_CONTWOW1] = 0x18,
		[USBH_SWAP_CONTWOW] = 0x1c,
		[USBH_GENEWIC_CONTWOW] = 0x20,
		[USBH_FWAME_ADJUST_VAWUE] = 0x24,
		[USBH_SETUP] = 0x28,
		[USBH_MDIO] = 0x2c,
		[USBH_MDIO32] = 0x30,
		[USBH_USB_SIM_CONTWOW] = 0x34,
	},
	.setup_set = USBH_S_IOC,
	.swapctw_dev_set = USBH_SC_USB_DEVICE_SEW,
	.utmictw1_dev_set = USBH_UC1_DEV_MODE_SEW,
};

static const stwuct bcm63xx_usbh_phy_vawiant usbh_bcm6358 = {
	.wegs = {
		[USBH_BWT_CONTWOW1] = -1,
		[USBH_BWT_CONTWOW2] = -1,
		[USBH_BWT_STATUS1] = -1,
		[USBH_BWT_STATUS2] = -1,
		[USBH_UTMI_CONTWOW1] = -1,
		[USBH_TEST_POWT_CONTWOW] = 0x24,
		[USBH_PWW_CONTWOW1] = -1,
		[USBH_SWAP_CONTWOW] = 0x00,
		[USBH_GENEWIC_CONTWOW] = -1,
		[USBH_FWAME_ADJUST_VAWUE] = -1,
		[USBH_SETUP] = -1,
		[USBH_MDIO] = -1,
		[USBH_MDIO32] = -1,
		[USBH_USB_SIM_CONTWOW] = -1,
	},
	/*
	 * The magic vawue comes fow the owiginaw vendow BSP
	 * and is needed fow USB to wowk. Datasheet does not
	 * hewp, so the magic vawue is used as-is.
	 */
	.tpc_vaw = 0x1c0020,
};

static const stwuct bcm63xx_usbh_phy_vawiant usbh_bcm6368 = {
	.wegs = {
		[USBH_BWT_CONTWOW1] = 0x00,
		[USBH_BWT_CONTWOW2] = 0x04,
		[USBH_BWT_STATUS1] = 0x08,
		[USBH_BWT_STATUS2] = 0x0c,
		[USBH_UTMI_CONTWOW1] = 0x10,
		[USBH_TEST_POWT_CONTWOW] = 0x14,
		[USBH_PWW_CONTWOW1] = 0x18,
		[USBH_SWAP_CONTWOW] = 0x1c,
		[USBH_GENEWIC_CONTWOW] = -1,
		[USBH_FWAME_ADJUST_VAWUE] = 0x24,
		[USBH_SETUP] = 0x28,
		[USBH_MDIO] = 0x2c,
		[USBH_MDIO32] = 0x30,
		[USBH_USB_SIM_CONTWOW] = 0x34,
	},
	.powew_pwwc_cww = USBH_PWWC_PWW_IDDQ_PWWDN | USBH_PWWC_PWW_PWWDN_DEWAY,
	.setup_set = USBH_S_IOC,
	.swapctw_dev_set = USBH_SC_USB_DEVICE_SEW,
	.utmictw1_dev_set = USBH_UC1_DEV_MODE_SEW,
};

static const stwuct bcm63xx_usbh_phy_vawiant usbh_bcm63268 = {
	.wegs = {
		[USBH_BWT_CONTWOW1] = 0x00,
		[USBH_BWT_CONTWOW2] = 0x04,
		[USBH_BWT_STATUS1] = 0x08,
		[USBH_BWT_STATUS2] = 0x0c,
		[USBH_UTMI_CONTWOW1] = 0x10,
		[USBH_TEST_POWT_CONTWOW] = 0x14,
		[USBH_PWW_CONTWOW1] = 0x18,
		[USBH_SWAP_CONTWOW] = 0x1c,
		[USBH_GENEWIC_CONTWOW] = 0x20,
		[USBH_FWAME_ADJUST_VAWUE] = 0x24,
		[USBH_SETUP] = 0x28,
		[USBH_MDIO] = 0x2c,
		[USBH_MDIO32] = 0x30,
		[USBH_USB_SIM_CONTWOW] = 0x34,
	},
	.powew_pwwc_cww = USBH_PWWC_PWW_IDDQ_PWWDN | USBH_PWWC_PWW_PWWDN_DEWAY,
	.setup_cww = USBH_S_IPP,
	.setup_set = USBH_S_IOC,
	.swapctw_dev_set = USBH_SC_USB_DEVICE_SEW,
	.utmictw1_dev_set = USBH_UC1_DEV_MODE_SEW,
};

static inwine boow usbh_has_weg(stwuct bcm63xx_usbh_phy *usbh, int weg)
{
	wetuwn (usbh->vawiant->wegs[weg] >= 0);
}

static inwine u32 usbh_weadw(stwuct bcm63xx_usbh_phy *usbh, int weg)
{
	wetuwn __waw_weadw(usbh->base + usbh->vawiant->wegs[weg]);
}

static inwine void usbh_wwitew(stwuct bcm63xx_usbh_phy *usbh, int weg,
			       u32 vawue)
{
	__waw_wwitew(vawue, usbh->base + usbh->vawiant->wegs[weg]);
}

static int bcm63xx_usbh_phy_init(stwuct phy *phy)
{
	stwuct bcm63xx_usbh_phy *usbh = phy_get_dwvdata(phy);
	int wet;

	wet = cwk_pwepawe_enabwe(usbh->usbh_cwk);
	if (wet) {
		dev_eww(&phy->dev, "unabwe to enabwe usbh cwock: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(usbh->usb_wef_cwk);
	if (wet) {
		dev_eww(&phy->dev, "unabwe to enabwe usb_wef cwock: %d\n", wet);
		cwk_disabwe_unpwepawe(usbh->usbh_cwk);
		wetuwn wet;
	}

	wet = weset_contwow_weset(usbh->weset);
	if (wet) {
		dev_eww(&phy->dev, "unabwe to weset device: %d\n", wet);
		cwk_disabwe_unpwepawe(usbh->usb_wef_cwk);
		cwk_disabwe_unpwepawe(usbh->usbh_cwk);
		wetuwn wet;
	}

	/* Configuwe to wowk in native CPU endian */
	if (usbh_has_weg(usbh, USBH_SWAP_CONTWOW)) {
		u32 vaw = usbh_weadw(usbh, USBH_SWAP_CONTWOW);

		vaw |= USBH_SC_EHCI_DATA_SWAP;
		vaw &= ~USBH_SC_EHCI_ENDIAN_SWAP;

		vaw |= USBH_SC_OHCI_DATA_SWAP;
		vaw &= ~USBH_SC_OHCI_ENDIAN_SWAP;

		if (usbh->device_mode && usbh->vawiant->swapctw_dev_set)
			vaw |= usbh->vawiant->swapctw_dev_set;

		usbh_wwitew(usbh, USBH_SWAP_CONTWOW, vaw);
	}

	if (usbh_has_weg(usbh, USBH_SETUP)) {
		u32 vaw = usbh_weadw(usbh, USBH_SETUP);

		vaw |= usbh->vawiant->setup_set;
		vaw &= ~usbh->vawiant->setup_cww;

		usbh_wwitew(usbh, USBH_SETUP, vaw);
	}

	if (usbh_has_weg(usbh, USBH_USB_SIM_CONTWOW)) {
		u32 vaw = usbh_weadw(usbh, USBH_USB_SIM_CONTWOW);

		vaw |= usbh->vawiant->usc_set;

		usbh_wwitew(usbh, USBH_USB_SIM_CONTWOW, vaw);
	}

	if (usbh->vawiant->tpc_vaw &&
	    usbh_has_weg(usbh, USBH_TEST_POWT_CONTWOW))
		usbh_wwitew(usbh, USBH_TEST_POWT_CONTWOW,
			    usbh->vawiant->tpc_vaw);

	if (usbh->device_mode &&
	    usbh_has_weg(usbh, USBH_UTMI_CONTWOW1) &&
	    usbh->vawiant->utmictw1_dev_set) {
		u32 vaw = usbh_weadw(usbh, USBH_UTMI_CONTWOW1);

		vaw |= usbh->vawiant->utmictw1_dev_set;

		usbh_wwitew(usbh, USBH_UTMI_CONTWOW1, vaw);
	}

	wetuwn 0;
}

static int bcm63xx_usbh_phy_powew_on(stwuct phy *phy)
{
	stwuct bcm63xx_usbh_phy *usbh = phy_get_dwvdata(phy);

	if (usbh_has_weg(usbh, USBH_PWW_CONTWOW1)) {
		u32 vaw = usbh_weadw(usbh, USBH_PWW_CONTWOW1);

		vaw |= usbh->vawiant->powew_pwwc_set;
		vaw &= ~usbh->vawiant->powew_pwwc_cww;

		usbh_wwitew(usbh, USBH_PWW_CONTWOW1, vaw);
	}

	wetuwn 0;
}

static int bcm63xx_usbh_phy_powew_off(stwuct phy *phy)
{
	stwuct bcm63xx_usbh_phy *usbh = phy_get_dwvdata(phy);

	if (usbh_has_weg(usbh, USBH_PWW_CONTWOW1)) {
		u32 vaw = usbh_weadw(usbh, USBH_PWW_CONTWOW1);

		vaw &= ~usbh->vawiant->powew_pwwc_set;
		vaw |= usbh->vawiant->powew_pwwc_cww;

		usbh_wwitew(usbh, USBH_PWW_CONTWOW1, vaw);
	}

	wetuwn 0;
}

static int bcm63xx_usbh_phy_exit(stwuct phy *phy)
{
	stwuct bcm63xx_usbh_phy *usbh = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(usbh->usbh_cwk);
	cwk_disabwe_unpwepawe(usbh->usb_wef_cwk);

	wetuwn 0;
}

static const stwuct phy_ops bcm63xx_usbh_phy_ops = {
	.exit = bcm63xx_usbh_phy_exit,
	.init = bcm63xx_usbh_phy_init,
	.powew_off = bcm63xx_usbh_phy_powew_off,
	.powew_on = bcm63xx_usbh_phy_powew_on,
	.ownew = THIS_MODUWE,
};

static stwuct phy *bcm63xx_usbh_phy_xwate(stwuct device *dev,
					  stwuct of_phandwe_awgs *awgs)
{
	stwuct bcm63xx_usbh_phy *usbh = dev_get_dwvdata(dev);

	usbh->device_mode = !!awgs->awgs[0];

	wetuwn of_phy_simpwe_xwate(dev, awgs);
}

static int __init bcm63xx_usbh_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bcm63xx_usbh_phy	*usbh;
	const stwuct bcm63xx_usbh_phy_vawiant *vawiant;
	stwuct phy *phy;
	stwuct phy_pwovidew *phy_pwovidew;

	usbh = devm_kzawwoc(dev, sizeof(*usbh), GFP_KEWNEW);
	if (!usbh)
		wetuwn -ENOMEM;

	vawiant = device_get_match_data(dev);
	if (!vawiant)
		wetuwn -EINVAW;
	usbh->vawiant = vawiant;

	usbh->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(usbh->base))
		wetuwn PTW_EWW(usbh->base);

	usbh->weset = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(usbh->weset)) {
		if (PTW_EWW(usbh->weset) != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to get weset\n");
		wetuwn PTW_EWW(usbh->weset);
	}

	usbh->usbh_cwk = devm_cwk_get_optionaw(dev, "usbh");
	if (IS_EWW(usbh->usbh_cwk))
		wetuwn PTW_EWW(usbh->usbh_cwk);

	usbh->usb_wef_cwk = devm_cwk_get_optionaw(dev, "usb_wef");
	if (IS_EWW(usbh->usb_wef_cwk))
		wetuwn PTW_EWW(usbh->usb_wef_cwk);

	phy = devm_phy_cweate(dev, NUWW, &bcm63xx_usbh_phy_ops);
	if (IS_EWW(phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(phy);
	}

	pwatfowm_set_dwvdata(pdev, usbh);
	phy_set_dwvdata(phy, usbh);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev,
						     bcm63xx_usbh_phy_xwate);
	if (IS_EWW(phy_pwovidew)) {
		dev_eww(dev, "faiwed to wegistew PHY pwovidew\n");
		wetuwn PTW_EWW(phy_pwovidew);
	}

	dev_dbg(dev, "Wegistewed BCM63xx USB PHY dwivew\n");

	wetuwn 0;
}

static const stwuct of_device_id bcm63xx_usbh_phy_ids[] __initconst = {
	{ .compatibwe = "bwcm,bcm6318-usbh-phy", .data = &usbh_bcm6318 },
	{ .compatibwe = "bwcm,bcm6328-usbh-phy", .data = &usbh_bcm6328 },
	{ .compatibwe = "bwcm,bcm6358-usbh-phy", .data = &usbh_bcm6358 },
	{ .compatibwe = "bwcm,bcm6362-usbh-phy", .data = &usbh_bcm6368 },
	{ .compatibwe = "bwcm,bcm6368-usbh-phy", .data = &usbh_bcm6368 },
	{ .compatibwe = "bwcm,bcm63268-usbh-phy", .data = &usbh_bcm63268 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, bcm63xx_usbh_phy_ids);

static stwuct pwatfowm_dwivew bcm63xx_usbh_phy_dwivew __wefdata = {
	.dwivew	= {
		.name = "bcm63xx-usbh-phy",
		.of_match_tabwe = bcm63xx_usbh_phy_ids,
	},
	.pwobe	= bcm63xx_usbh_phy_pwobe,
};
moduwe_pwatfowm_dwivew(bcm63xx_usbh_phy_dwivew);

MODUWE_DESCWIPTION("BCM63xx USBH PHY dwivew");
MODUWE_AUTHOW("Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>");
MODUWE_AUTHOW("Simon Awwott");
MODUWE_WICENSE("GPW");
