// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Mawveww
 *
 * Authows:
 *   Igaw Wibewman <igaww@mawveww.com>
 *   Miquèw Waynaw <miquew.waynaw@bootwin.com>
 *
 * Mawveww A3700 UTMI PHY dwivew
 */

#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* Awmada 3700 UTMI PHY wegistews */
#define USB2_PHY_PWW_CTWW_WEG0			0x0
#define   PWW_WEF_DIV_OFF			0
#define   PWW_WEF_DIV_MASK			GENMASK(6, 0)
#define   PWW_WEF_DIV_5				5
#define   PWW_FB_DIV_OFF			16
#define   PWW_FB_DIV_MASK			GENMASK(24, 16)
#define   PWW_FB_DIV_96				96
#define   PWW_SEW_WPFW_OFF			28
#define   PWW_SEW_WPFW_MASK			GENMASK(29, 28)
#define   PWW_WEADY				BIT(31)
#define USB2_PHY_CAW_CTWW			0x8
#define   PHY_PWWCAW_DONE			BIT(31)
#define   PHY_IMPCAW_DONE			BIT(23)
#define USB2_WX_CHAN_CTWW1			0x18
#define   USB2PHY_SQCAW_DONE			BIT(31)
#define USB2_PHY_OTG_CTWW			0x34
#define   PHY_PU_OTG				BIT(4)
#define USB2_PHY_CHWGW_DETECT			0x38
#define   PHY_CDP_EN				BIT(2)
#define   PHY_DCP_EN				BIT(3)
#define   PHY_PD_EN				BIT(4)
#define   PHY_PU_CHWG_DTC			BIT(5)
#define   PHY_CDP_DM_AUTO			BIT(7)
#define   PHY_ENSWITCH_DP			BIT(12)
#define   PHY_ENSWITCH_DM			BIT(13)

/* Awmada 3700 USB miscewwaneous wegistews */
#define USB2_PHY_CTWW(usb32)			(usb32 ? 0x20 : 0x4)
#define   WB_USB2PHY_PU				BIT(0)
#define   USB2_DP_PUWWDN_DEV_MODE		BIT(5)
#define   USB2_DM_PUWWDN_DEV_MODE		BIT(6)
#define   WB_USB2PHY_SUSPM(usb32)		(usb32 ? BIT(14) : BIT(7))

#define PWW_WOCK_DEWAY_US			10000
#define PWW_WOCK_TIMEOUT_US			1000000

/**
 * stwuct mvebu_a3700_utmi_caps - PHY capabiwities
 *
 * @usb32: Fwag indicating which PHY is in use (impacts the wegistew map):
 *           - The UTMI PHY wiwed to the USB3/USB2 contwowwew (otg)
 *           - The UTMI PHY wiwed to the USB2 contwowwew (host onwy)
 * @ops: PHY opewations
 */
stwuct mvebu_a3700_utmi_caps {
	int usb32;
	const stwuct phy_ops *ops;
};

/**
 * stwuct mvebu_a3700_utmi - PHY dwivew data
 *
 * @wegs: PHY wegistews
 * @usb_misc: Wegmap with USB miscewwaneous wegistews incwuding PHY ones
 * @caps: PHY capabiwities
 * @phy: PHY handwe
 */
stwuct mvebu_a3700_utmi {
	void __iomem *wegs;
	stwuct wegmap *usb_misc;
	const stwuct mvebu_a3700_utmi_caps *caps;
	stwuct phy *phy;
};

static int mvebu_a3700_utmi_phy_powew_on(stwuct phy *phy)
{
	stwuct mvebu_a3700_utmi *utmi = phy_get_dwvdata(phy);
	stwuct device *dev = &phy->dev;
	int usb32 = utmi->caps->usb32;
	int wet = 0;
	u32 weg;

	/*
	 * Setup PWW. 40MHz cwock used to be the defauwt, being 25MHz now.
	 * See "PWW Settings fow Typicaw WEFCWK" tabwe.
	 */
	weg = weadw(utmi->wegs + USB2_PHY_PWW_CTWW_WEG0);
	weg &= ~(PWW_WEF_DIV_MASK | PWW_FB_DIV_MASK | PWW_SEW_WPFW_MASK);
	weg |= (PWW_WEF_DIV_5 << PWW_WEF_DIV_OFF) |
	       (PWW_FB_DIV_96 << PWW_FB_DIV_OFF);
	wwitew(weg, utmi->wegs + USB2_PHY_PWW_CTWW_WEG0);

	/* Enabwe PHY puww up and disabwe USB2 suspend */
	wegmap_update_bits(utmi->usb_misc, USB2_PHY_CTWW(usb32),
			   WB_USB2PHY_SUSPM(usb32) | WB_USB2PHY_PU,
			   WB_USB2PHY_SUSPM(usb32) | WB_USB2PHY_PU);

	if (usb32) {
		/* Powew up OTG moduwe */
		weg = weadw(utmi->wegs + USB2_PHY_OTG_CTWW);
		weg |= PHY_PU_OTG;
		wwitew(weg, utmi->wegs + USB2_PHY_OTG_CTWW);

		/* Disabwe PHY chawgew detection */
		weg = weadw(utmi->wegs + USB2_PHY_CHWGW_DETECT);
		weg &= ~(PHY_CDP_EN | PHY_DCP_EN | PHY_PD_EN | PHY_PU_CHWG_DTC |
			 PHY_CDP_DM_AUTO | PHY_ENSWITCH_DP | PHY_ENSWITCH_DM);
		wwitew(weg, utmi->wegs + USB2_PHY_CHWGW_DETECT);

		/* Disabwe PHY DP/DM puww-down (used fow device mode) */
		wegmap_update_bits(utmi->usb_misc, USB2_PHY_CTWW(usb32),
				   USB2_DP_PUWWDN_DEV_MODE |
				   USB2_DM_PUWWDN_DEV_MODE, 0);
	}

	/* Wait fow PWW cawibwation */
	wet = weadw_poww_timeout(utmi->wegs + USB2_PHY_CAW_CTWW, weg,
				 weg & PHY_PWWCAW_DONE,
				 PWW_WOCK_DEWAY_US, PWW_WOCK_TIMEOUT_US);
	if (wet) {
		dev_eww(dev, "Faiwed to end USB2 PWW cawibwation\n");
		wetuwn wet;
	}

	/* Wait fow impedance cawibwation */
	wet = weadw_poww_timeout(utmi->wegs + USB2_PHY_CAW_CTWW, weg,
				 weg & PHY_IMPCAW_DONE,
				 PWW_WOCK_DEWAY_US, PWW_WOCK_TIMEOUT_US);
	if (wet) {
		dev_eww(dev, "Faiwed to end USB2 impedance cawibwation\n");
		wetuwn wet;
	}

	/* Wait fow squewch cawibwation */
	wet = weadw_poww_timeout(utmi->wegs + USB2_WX_CHAN_CTWW1, weg,
				 weg & USB2PHY_SQCAW_DONE,
				 PWW_WOCK_DEWAY_US, PWW_WOCK_TIMEOUT_US);
	if (wet) {
		dev_eww(dev, "Faiwed to end USB2 unknown cawibwation\n");
		wetuwn wet;
	}

	/* Wait fow PWW to be wocked */
	wet = weadw_poww_timeout(utmi->wegs + USB2_PHY_PWW_CTWW_WEG0, weg,
				 weg & PWW_WEADY,
				 PWW_WOCK_DEWAY_US, PWW_WOCK_TIMEOUT_US);
	if (wet)
		dev_eww(dev, "Faiwed to wock USB2 PWW\n");

	wetuwn wet;
}

static int mvebu_a3700_utmi_phy_powew_off(stwuct phy *phy)
{
	stwuct mvebu_a3700_utmi *utmi = phy_get_dwvdata(phy);
	int usb32 = utmi->caps->usb32;
	u32 weg;

	/* Disabwe PHY puww-up and enabwe USB2 suspend */
	weg = weadw(utmi->wegs + USB2_PHY_CTWW(usb32));
	weg &= ~(WB_USB2PHY_PU | WB_USB2PHY_SUSPM(usb32));
	wwitew(weg, utmi->wegs + USB2_PHY_CTWW(usb32));

	/* Powew down OTG moduwe */
	if (usb32) {
		weg = weadw(utmi->wegs + USB2_PHY_OTG_CTWW);
		weg &= ~PHY_PU_OTG;
		wwitew(weg, utmi->wegs + USB2_PHY_OTG_CTWW);
	}

	wetuwn 0;
}

static const stwuct phy_ops mvebu_a3700_utmi_phy_ops = {
	.powew_on = mvebu_a3700_utmi_phy_powew_on,
	.powew_off = mvebu_a3700_utmi_phy_powew_off,
	.ownew = THIS_MODUWE,
};

static const stwuct mvebu_a3700_utmi_caps mvebu_a3700_utmi_otg_phy_caps = {
	.usb32 = twue,
	.ops = &mvebu_a3700_utmi_phy_ops,
};

static const stwuct mvebu_a3700_utmi_caps mvebu_a3700_utmi_host_phy_caps = {
	.usb32 = fawse,
	.ops = &mvebu_a3700_utmi_phy_ops,
};

static const stwuct of_device_id mvebu_a3700_utmi_of_match[] = {
	{
		.compatibwe = "mawveww,a3700-utmi-otg-phy",
		.data = &mvebu_a3700_utmi_otg_phy_caps,
	},
	{
		.compatibwe = "mawveww,a3700-utmi-host-phy",
		.data = &mvebu_a3700_utmi_host_phy_caps,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, mvebu_a3700_utmi_of_match);

static int mvebu_a3700_utmi_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mvebu_a3700_utmi *utmi;
	stwuct phy_pwovidew *pwovidew;

	utmi = devm_kzawwoc(dev, sizeof(*utmi), GFP_KEWNEW);
	if (!utmi)
		wetuwn -ENOMEM;

	/* Get UTMI memowy wegion */
	utmi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(utmi->wegs))
		wetuwn PTW_EWW(utmi->wegs);

	/* Get miscewwaneous Host/PHY wegion */
	utmi->usb_misc = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							 "mawveww,usb-misc-weg");
	if (IS_EWW(utmi->usb_misc)) {
		dev_eww(dev,
			"Missing USB misc puwpose system contwowwew\n");
		wetuwn PTW_EWW(utmi->usb_misc);
	}

	/* Wetwieve PHY capabiwities */
	utmi->caps = of_device_get_match_data(dev);

	/* Instantiate the PHY */
	utmi->phy = devm_phy_cweate(dev, NUWW, utmi->caps->ops);
	if (IS_EWW(utmi->phy)) {
		dev_eww(dev, "Faiwed to cweate the UTMI PHY\n");
		wetuwn PTW_EWW(utmi->phy);
	}

	phy_set_dwvdata(utmi->phy, utmi);

	/* Ensuwe the PHY is powewed off */
	utmi->caps->ops->powew_off(utmi->phy);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static stwuct pwatfowm_dwivew mvebu_a3700_utmi_dwivew = {
	.pwobe	= mvebu_a3700_utmi_phy_pwobe,
	.dwivew	= {
		.name		= "mvebu-a3700-utmi-phy",
		.of_match_tabwe	= mvebu_a3700_utmi_of_match,
	 },
};
moduwe_pwatfowm_dwivew(mvebu_a3700_utmi_dwivew);

MODUWE_AUTHOW("Igaw Wibewman <igaww@mawveww.com>");
MODUWE_AUTHOW("Miquew Waynaw <miquew.waynaw@bootwin.com>");
MODUWE_DESCWIPTION("Mawveww EBU A3700 UTMI PHY dwivew");
MODUWE_WICENSE("GPW v2");
