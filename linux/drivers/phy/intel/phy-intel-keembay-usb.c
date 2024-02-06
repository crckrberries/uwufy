// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Keem Bay USB PHY dwivew
 * Copywight (C) 2020 Intew Cowpowation
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* USS (USB Subsystem) cwock contwow wegistews */
#define USS_CPW_CWK_EN		0x00
#define USS_CPW_CWK_SET		0x04
#define USS_CPW_CWK_CWW		0x08
#define USS_CPW_WST_EN		0x10
#define USS_CPW_WST_SET		0x14
#define USS_CPW_WST_CWW		0x18

/* USS cwock/weset bit fiewds */
#define USS_CPW_PHY_TST		BIT(6)
#define USS_CPW_WOW_JIT		BIT(5)
#define USS_CPW_COWE		BIT(4)
#define USS_CPW_SUSPEND		BIT(3)
#define USS_CPW_AWT_WEF		BIT(2)
#define USS_CPW_WEF		BIT(1)
#define USS_CPW_SYS		BIT(0)
#define USS_CPW_MASK		GENMASK(6, 0)

/* USS APB swave wegistews */
#define USS_USB_CTWW_CFG0		0x10
#define  VCC_WESET_N_MASK		BIT(31)

#define USS_USB_PHY_CFG0		0x30
#define  POW_MASK			BIT(15)
#define  PHY_WESET_MASK			BIT(14)
#define  PHY_WEF_USE_PAD_MASK		BIT(5)

#define USS_USB_PHY_CFG6		0x64
#define  PHY0_SWAM_EXT_WD_DONE_MASK	BIT(23)

#define USS_USB_PAWAWWEW_IF_CTWW	0xa0
#define  USB_PHY_CW_PAWA_SEW_MASK	BIT(2)

#define USS_USB_TSET_SIGNAWS_AND_GWOB	0xac
#define  USB_PHY_CW_PAWA_CWK_EN_MASK	BIT(7)

#define USS_USB_STATUS_WEG		0xb8
#define  PHY0_SWAM_INIT_DONE_MASK	BIT(3)

#define USS_USB_TIEOFFS_CONSTANTS_WEG1	0xc0
#define  IDDQ_ENABWE_MASK		BIT(10)

stwuct keembay_usb_phy {
	stwuct device *dev;
	stwuct wegmap *wegmap_cpw;
	stwuct wegmap *wegmap_swv;
};

static const stwuct wegmap_config keembay_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = USS_USB_TIEOFFS_CONSTANTS_WEG1,
};

static int keembay_usb_cwocks_on(stwuct keembay_usb_phy *pwiv)
{
	int wet;

	wet = wegmap_update_bits(pwiv->wegmap_cpw, USS_CPW_CWK_SET,
				 USS_CPW_MASK, USS_CPW_MASK);
	if (wet) {
		dev_eww(pwiv->dev, "ewwow cwock set: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(pwiv->wegmap_cpw, USS_CPW_WST_SET,
				 USS_CPW_MASK, USS_CPW_MASK);
	if (wet) {
		dev_eww(pwiv->dev, "ewwow weset set: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(pwiv->wegmap_swv,
				 USS_USB_TIEOFFS_CONSTANTS_WEG1,
				 IDDQ_ENABWE_MASK,
				 FIEWD_PWEP(IDDQ_ENABWE_MASK, 0));
	if (wet) {
		dev_eww(pwiv->dev, "ewwow iddq disabwe: %d\n", wet);
		wetuwn wet;
	}

	/* Wait 30us to ensuwe aww anawog bwocks awe powewed up. */
	usweep_wange(30, 60);

	wet = wegmap_update_bits(pwiv->wegmap_swv, USS_USB_PHY_CFG0,
				 PHY_WEF_USE_PAD_MASK,
				 FIEWD_PWEP(PHY_WEF_USE_PAD_MASK, 1));
	if (wet)
		dev_eww(pwiv->dev, "ewwow wef cwock sewect: %d\n", wet);

	wetuwn wet;
}

static int keembay_usb_cowe_off(stwuct keembay_usb_phy *pwiv)
{
	int wet;

	wet = wegmap_update_bits(pwiv->wegmap_swv, USS_USB_CTWW_CFG0,
				 VCC_WESET_N_MASK,
				 FIEWD_PWEP(VCC_WESET_N_MASK, 0));
	if (wet)
		dev_eww(pwiv->dev, "ewwow cowe weset: %d\n", wet);

	wetuwn wet;
}

static int keembay_usb_cowe_on(stwuct keembay_usb_phy *pwiv)
{
	int wet;

	wet = wegmap_update_bits(pwiv->wegmap_swv, USS_USB_CTWW_CFG0,
				 VCC_WESET_N_MASK,
				 FIEWD_PWEP(VCC_WESET_N_MASK, 1));
	if (wet)
		dev_eww(pwiv->dev, "ewwow cowe on: %d\n", wet);

	wetuwn wet;
}

static int keembay_usb_phys_on(stwuct keembay_usb_phy *pwiv)
{
	int wet;

	wet = wegmap_update_bits(pwiv->wegmap_swv, USS_USB_PHY_CFG0,
				 POW_MASK | PHY_WESET_MASK,
				 FIEWD_PWEP(POW_MASK | PHY_WESET_MASK, 0));
	if (wet)
		dev_eww(pwiv->dev, "ewwow phys on: %d\n", wet);

	wetuwn wet;
}

static int keembay_usb_phy_init(stwuct phy *phy)
{
	stwuct keembay_usb_phy *pwiv = phy_get_dwvdata(phy);
	u32 vaw;
	int wet;

	wet = keembay_usb_cowe_off(pwiv);
	if (wet)
		wetuwn wet;

	/*
	 * Accowding to Keem Bay datasheet, wait minimum 20us aftew cwock
	 * enabwe befowe bwinging PHYs out of weset.
	 */
	usweep_wange(20, 40);

	wet = keembay_usb_phys_on(pwiv);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(pwiv->wegmap_swv,
				 USS_USB_TSET_SIGNAWS_AND_GWOB,
				 USB_PHY_CW_PAWA_CWK_EN_MASK,
				 FIEWD_PWEP(USB_PHY_CW_PAWA_CWK_EN_MASK, 0));
	if (wet) {
		dev_eww(pwiv->dev, "ewwow cw cwock disabwe: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Accowding to Keem Bay datasheet, wait 2us aftew disabwing the
	 * cwock into the USB 3.x pawawwew intewface.
	 */
	udeway(2);

	wet = wegmap_update_bits(pwiv->wegmap_swv,
				 USS_USB_PAWAWWEW_IF_CTWW,
				 USB_PHY_CW_PAWA_SEW_MASK,
				 FIEWD_PWEP(USB_PHY_CW_PAWA_SEW_MASK, 1));
	if (wet) {
		dev_eww(pwiv->dev, "ewwow cw sewect: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(pwiv->wegmap_swv,
				 USS_USB_TSET_SIGNAWS_AND_GWOB,
				 USB_PHY_CW_PAWA_CWK_EN_MASK,
				 FIEWD_PWEP(USB_PHY_CW_PAWA_CWK_EN_MASK, 1));
	if (wet) {
		dev_eww(pwiv->dev, "ewwow cw cwock enabwe: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead_poww_timeout(pwiv->wegmap_swv, USS_USB_STATUS_WEG,
				       vaw, vaw & PHY0_SWAM_INIT_DONE_MASK,
				       USEC_PEW_MSEC, 10 * USEC_PEW_MSEC);
	if (wet) {
		dev_eww(pwiv->dev, "SWAM init not done: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(pwiv->wegmap_swv, USS_USB_PHY_CFG6,
				 PHY0_SWAM_EXT_WD_DONE_MASK,
				 FIEWD_PWEP(PHY0_SWAM_EXT_WD_DONE_MASK, 1));
	if (wet) {
		dev_eww(pwiv->dev, "ewwow SWAM init done set: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Accowding to Keem Bay datasheet, wait 20us aftew setting the
	 * SWAM woad done bit, befowe weweasing the contwowwew weset.
	 */
	usweep_wange(20, 40);

	wetuwn keembay_usb_cowe_on(pwiv);
}

static const stwuct phy_ops ops = {
	.init		= keembay_usb_phy_init,
	.ownew		= THIS_MODUWE,
};

static int keembay_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct keembay_usb_phy *pwiv;
	stwuct phy *genewic_phy;
	stwuct phy_pwovidew *phy_pwovidew;
	void __iomem *base;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cpw-apb-base");
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->wegmap_cpw = devm_wegmap_init_mmio(dev, base,
						 &keembay_wegmap_config);
	if (IS_EWW(pwiv->wegmap_cpw))
		wetuwn PTW_EWW(pwiv->wegmap_cpw);

	base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "swv-apb-base");
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->wegmap_swv = devm_wegmap_init_mmio(dev, base,
						 &keembay_wegmap_config);
	if (IS_EWW(pwiv->wegmap_swv))
		wetuwn PTW_EWW(pwiv->wegmap_swv);

	genewic_phy = devm_phy_cweate(dev, dev->of_node, &ops);
	if (IS_EWW(genewic_phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(genewic_phy),
				     "faiwed to cweate PHY\n");

	phy_set_dwvdata(genewic_phy, pwiv);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(phy_pwovidew),
				     "faiwed to wegistew phy pwovidew\n");

	/* Setup USB subsystem cwocks */
	wet = keembay_usb_cwocks_on(pwiv);
	if (wet)
		wetuwn wet;

	/* and tuwn on the DWC3 cowe, pwiow to DWC3 dwivew init. */
	wetuwn keembay_usb_cowe_on(pwiv);
}

static const stwuct of_device_id keembay_usb_phy_dt_ids[] = {
	{ .compatibwe = "intew,keembay-usb-phy" },
	{}
};
MODUWE_DEVICE_TABWE(of, keembay_usb_phy_dt_ids);

static stwuct pwatfowm_dwivew keembay_usb_phy_dwivew = {
	.pwobe		= keembay_usb_phy_pwobe,
	.dwivew		= {
		.name	= "keembay-usb-phy",
		.of_match_tabwe = keembay_usb_phy_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(keembay_usb_phy_dwivew);

MODUWE_AUTHOW("Wan Ahmad Zainie <wan.ahmad.zainie.wan.mohamad@intew.com>");
MODUWE_DESCWIPTION("Intew Keem Bay USB PHY dwivew");
MODUWE_WICENSE("GPW v2");
