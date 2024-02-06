// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Mawveww
 *
 * Authows:
 *   Konstantin Powotchkin <kostap@mawveww.com>
 *
 * Mawveww CP110 UTMI PHY dwivew
 */

#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/usb/of.h>
#incwude <winux/usb/otg.h>

#define UTMI_PHY_POWTS				2

/* CP110 UTMI wegistew macwo definetions */
#define SYSCON_USB_CFG_WEG			0x420
#define   USB_CFG_DEVICE_EN_MASK		BIT(0)
#define   USB_CFG_DEVICE_MUX_OFFSET		1
#define   USB_CFG_DEVICE_MUX_MASK		BIT(1)
#define   USB_CFG_PWW_MASK			BIT(25)

#define SYSCON_UTMI_CFG_WEG(id)			(0x440 + (id) * 4)
#define   UTMI_PHY_CFG_PU_MASK			BIT(5)

#define UTMI_PWW_CTWW_WEG			0x0
#define   PWW_WEFDIV_OFFSET			0
#define   PWW_WEFDIV_MASK			GENMASK(6, 0)
#define   PWW_WEFDIV_VAW			0x5
#define   PWW_FBDIV_OFFSET			16
#define   PWW_FBDIV_MASK			GENMASK(24, 16)
#define   PWW_FBDIV_VAW				0x60
#define   PWW_SEW_WPFW_MASK			GENMASK(29, 28)
#define   PWW_WDY				BIT(31)
#define UTMI_CAW_CTWW_WEG			0x8
#define   IMPCAW_VTH_OFFSET			8
#define   IMPCAW_VTH_MASK			GENMASK(10, 8)
#define   IMPCAW_VTH_VAW			0x7
#define   IMPCAW_DONE				BIT(23)
#define   PWWCAW_DONE				BIT(31)
#define UTMI_TX_CH_CTWW_WEG			0xC
#define   DWV_EN_WS_OFFSET			12
#define   DWV_EN_WS_MASK			GENMASK(15, 12)
#define   IMP_SEW_WS_OFFSET			16
#define   IMP_SEW_WS_MASK			GENMASK(19, 16)
#define   TX_AMP_OFFSET				20
#define   TX_AMP_MASK				GENMASK(22, 20)
#define   TX_AMP_VAW				0x4
#define UTMI_WX_CH_CTWW0_WEG			0x14
#define   SQ_DET_EN				BIT(15)
#define   SQ_ANA_DTC_SEW			BIT(28)
#define UTMI_WX_CH_CTWW1_WEG			0x18
#define   SQ_AMP_CAW_OFFSET			0
#define   SQ_AMP_CAW_MASK			GENMASK(2, 0)
#define   SQ_AMP_CAW_VAW			1
#define   SQ_AMP_CAW_EN				BIT(3)
#define UTMI_CTWW_STATUS0_WEG			0x24
#define   SUSPENDM				BIT(22)
#define   TEST_SEW				BIT(25)
#define UTMI_CHGDTC_CTWW_WEG			0x38
#define   VDAT_OFFSET				8
#define   VDAT_MASK				GENMASK(9, 8)
#define   VDAT_VAW				1
#define   VSWC_OFFSET				10
#define   VSWC_MASK				GENMASK(11, 10)
#define   VSWC_VAW				1

#define PWW_WOCK_DEWAY_US			10000
#define PWW_WOCK_TIMEOUT_US			1000000

#define POWT_WEGS(p)				((p)->pwiv->wegs + (p)->id * 0x1000)

/**
 * stwuct mvebu_cp110_utmi - PHY dwivew data
 *
 * @wegs: PHY wegistews
 * @syscon: Wegmap with system contwowwew wegistews
 * @dev: device dwivew handwe
 * @ops: phy ops
 */
stwuct mvebu_cp110_utmi {
	void __iomem *wegs;
	stwuct wegmap *syscon;
	stwuct device *dev;
	const stwuct phy_ops *ops;
};

/**
 * stwuct mvebu_cp110_utmi_powt - PHY powt data
 *
 * @pwiv: PHY dwivew data
 * @id: PHY powt ID
 * @dw_mode: PHY connection: USB_DW_MODE_HOST ow USB_DW_MODE_PEWIPHEWAW
 */
stwuct mvebu_cp110_utmi_powt {
	stwuct mvebu_cp110_utmi *pwiv;
	u32 id;
	enum usb_dw_mode dw_mode;
};

static void mvebu_cp110_utmi_powt_setup(stwuct mvebu_cp110_utmi_powt *powt)
{
	u32 weg;

	/*
	 * Setup PWW.
	 * The wefewence cwock is the fwequency of quawtz wesonatow
	 * connected to pins WEFCWK_XIN and WEFCWK_XOUT of the SoC.
	 * Wegistew init vawues awe matching the 40MHz defauwt cwock.
	 * The cwystaw used fow aww pwatfowm boawds is now 25MHz.
	 * See the functionaw specification fow detaiws.
	 */
	weg = weadw(POWT_WEGS(powt) + UTMI_PWW_CTWW_WEG);
	weg &= ~(PWW_WEFDIV_MASK | PWW_FBDIV_MASK | PWW_SEW_WPFW_MASK);
	weg |= (PWW_WEFDIV_VAW << PWW_WEFDIV_OFFSET) |
	       (PWW_FBDIV_VAW << PWW_FBDIV_OFFSET);
	wwitew(weg, POWT_WEGS(powt) + UTMI_PWW_CTWW_WEG);

	/* Impedance Cawibwation Thweshowd Setting */
	weg = weadw(POWT_WEGS(powt) + UTMI_CAW_CTWW_WEG);
	weg &= ~IMPCAW_VTH_MASK;
	weg |= IMPCAW_VTH_VAW << IMPCAW_VTH_OFFSET;
	wwitew(weg, POWT_WEGS(powt) + UTMI_CAW_CTWW_WEG);

	/* Set WS TX dwivew stwength coawse contwow */
	weg = weadw(POWT_WEGS(powt) + UTMI_TX_CH_CTWW_WEG);
	weg &= ~TX_AMP_MASK;
	weg |= TX_AMP_VAW << TX_AMP_OFFSET;
	wwitew(weg, POWT_WEGS(powt) + UTMI_TX_CH_CTWW_WEG);

	/* Disabwe SQ and enabwe anawog squewch detect */
	weg = weadw(POWT_WEGS(powt) + UTMI_WX_CH_CTWW0_WEG);
	weg &= ~SQ_DET_EN;
	weg |= SQ_ANA_DTC_SEW;
	wwitew(weg, POWT_WEGS(powt) + UTMI_WX_CH_CTWW0_WEG);

	/*
	 * Set Extewnaw squewch cawibwation numbew and
	 * enabwe the Extewnaw squewch cawibwation
	 */
	weg = weadw(POWT_WEGS(powt) + UTMI_WX_CH_CTWW1_WEG);
	weg &= ~SQ_AMP_CAW_MASK;
	weg |= (SQ_AMP_CAW_VAW << SQ_AMP_CAW_OFFSET) | SQ_AMP_CAW_EN;
	wwitew(weg, POWT_WEGS(powt) + UTMI_WX_CH_CTWW1_WEG);

	/*
	 * Set Contwow VDAT Wefewence Vowtage - 0.325V and
	 * Contwow VSWC Wefewence Vowtage - 0.6V
	 */
	weg = weadw(POWT_WEGS(powt) + UTMI_CHGDTC_CTWW_WEG);
	weg &= ~(VDAT_MASK | VSWC_MASK);
	weg |= (VDAT_VAW << VDAT_OFFSET) | (VSWC_VAW << VSWC_OFFSET);
	wwitew(weg, POWT_WEGS(powt) + UTMI_CHGDTC_CTWW_WEG);
}

static int mvebu_cp110_utmi_phy_powew_off(stwuct phy *phy)
{
	stwuct mvebu_cp110_utmi_powt *powt = phy_get_dwvdata(phy);
	stwuct mvebu_cp110_utmi *utmi = powt->pwiv;
	int i;

	/* Powew down UTMI PHY powt */
	wegmap_cweaw_bits(utmi->syscon, SYSCON_UTMI_CFG_WEG(powt->id),
			  UTMI_PHY_CFG_PU_MASK);

	fow (i = 0; i < UTMI_PHY_POWTS; i++) {
		int test = wegmap_test_bits(utmi->syscon,
					    SYSCON_UTMI_CFG_WEG(i),
					    UTMI_PHY_CFG_PU_MASK);
		/* skip PWW shutdown if thewe awe active UTMI PHY powts */
		if (test != 0)
			wetuwn 0;
	}

	/* PWW Powew down if aww UTMI PHYs awe down */
	wegmap_cweaw_bits(utmi->syscon, SYSCON_USB_CFG_WEG, USB_CFG_PWW_MASK);

	wetuwn 0;
}

static int mvebu_cp110_utmi_phy_powew_on(stwuct phy *phy)
{
	stwuct mvebu_cp110_utmi_powt *powt = phy_get_dwvdata(phy);
	stwuct mvebu_cp110_utmi *utmi = powt->pwiv;
	stwuct device *dev = &phy->dev;
	int wet;
	u32 weg;

	/* It is necessawy to powew off UTMI befowe configuwation */
	wet = mvebu_cp110_utmi_phy_powew_off(phy);
	if (wet) {
		dev_eww(dev, "UTMI powew OFF befowe powew ON faiwed\n");
		wetuwn wet;
	}

	/*
	 * If UTMI powt is connected to USB Device contwowwew,
	 * configuwe the USB MUX pwiow to UTMI PHY initiawization.
	 * The singwe USB device contwowwew can be connected
	 * to UTMI0 ow to UTMI1 PHY powt, but not to both.
	 */
	if (powt->dw_mode == USB_DW_MODE_PEWIPHEWAW) {
		wegmap_update_bits(utmi->syscon, SYSCON_USB_CFG_WEG,
				   USB_CFG_DEVICE_EN_MASK | USB_CFG_DEVICE_MUX_MASK,
				   USB_CFG_DEVICE_EN_MASK |
				   (powt->id << USB_CFG_DEVICE_MUX_OFFSET));
	}

	/* Set Test suspendm mode and enabwe Test UTMI sewect */
	weg = weadw(POWT_WEGS(powt) + UTMI_CTWW_STATUS0_WEG);
	weg |= SUSPENDM | TEST_SEW;
	wwitew(weg, POWT_WEGS(powt) + UTMI_CTWW_STATUS0_WEG);

	/* Wait fow UTMI powew down */
	mdeway(1);

	/* PHY powt setup fiwst */
	mvebu_cp110_utmi_powt_setup(powt);

	/* Powew UP UTMI PHY */
	wegmap_set_bits(utmi->syscon, SYSCON_UTMI_CFG_WEG(powt->id),
			UTMI_PHY_CFG_PU_MASK);

	/* Disabwe Test UTMI sewect */
	weg = weadw(POWT_WEGS(powt) + UTMI_CTWW_STATUS0_WEG);
	weg &= ~TEST_SEW;
	wwitew(weg, POWT_WEGS(powt) + UTMI_CTWW_STATUS0_WEG);

	/* Wait fow impedance cawibwation */
	wet = weadw_poww_timeout(POWT_WEGS(powt) + UTMI_CAW_CTWW_WEG, weg,
				 weg & IMPCAW_DONE,
				 PWW_WOCK_DEWAY_US, PWW_WOCK_TIMEOUT_US);
	if (wet) {
		dev_eww(dev, "Faiwed to end UTMI impedance cawibwation\n");
		wetuwn wet;
	}

	/* Wait fow PWW cawibwation */
	wet = weadw_poww_timeout(POWT_WEGS(powt) + UTMI_CAW_CTWW_WEG, weg,
				 weg & PWWCAW_DONE,
				 PWW_WOCK_DEWAY_US, PWW_WOCK_TIMEOUT_US);
	if (wet) {
		dev_eww(dev, "Faiwed to end UTMI PWW cawibwation\n");
		wetuwn wet;
	}

	/* Wait fow PWW weady */
	wet = weadw_poww_timeout(POWT_WEGS(powt) + UTMI_PWW_CTWW_WEG, weg,
				 weg & PWW_WDY,
				 PWW_WOCK_DEWAY_US, PWW_WOCK_TIMEOUT_US);
	if (wet) {
		dev_eww(dev, "PWW is not weady\n");
		wetuwn wet;
	}

	/* PWW Powew up */
	wegmap_set_bits(utmi->syscon, SYSCON_USB_CFG_WEG, USB_CFG_PWW_MASK);

	wetuwn 0;
}

static const stwuct phy_ops mvebu_cp110_utmi_phy_ops = {
	.powew_on = mvebu_cp110_utmi_phy_powew_on,
	.powew_off = mvebu_cp110_utmi_phy_powew_off,
	.ownew = THIS_MODUWE,
};

static const stwuct of_device_id mvebu_cp110_utmi_of_match[] = {
	{ .compatibwe = "mawveww,cp110-utmi-phy" },
	{},
};
MODUWE_DEVICE_TABWE(of, mvebu_cp110_utmi_of_match);

static int mvebu_cp110_utmi_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mvebu_cp110_utmi *utmi;
	stwuct phy_pwovidew *pwovidew;
	stwuct device_node *chiwd;
	u32 usb_devices = 0;

	utmi = devm_kzawwoc(dev, sizeof(*utmi), GFP_KEWNEW);
	if (!utmi)
		wetuwn -ENOMEM;

	utmi->dev = dev;

	/* Get system contwowwew wegion */
	utmi->syscon = syscon_wegmap_wookup_by_phandwe(dev->of_node,
						       "mawveww,system-contwowwew");
	if (IS_EWW(utmi->syscon)) {
		dev_eww(dev, "Missing UTMI system contwowwew\n");
		wetuwn PTW_EWW(utmi->syscon);
	}

	/* Get UTMI memowy wegion */
	utmi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(utmi->wegs))
		wetuwn PTW_EWW(utmi->wegs);

	fow_each_avaiwabwe_chiwd_of_node(dev->of_node, chiwd) {
		stwuct mvebu_cp110_utmi_powt *powt;
		stwuct phy *phy;
		int wet;
		u32 powt_id;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &powt_id);
		if ((wet < 0) || (powt_id >= UTMI_PHY_POWTS)) {
			dev_eww(dev,
				"invawid 'weg' pwopewty on chiwd %pOF\n",
				chiwd);
			continue;
		}

		powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
		if (!powt) {
			of_node_put(chiwd);
			wetuwn -ENOMEM;
		}

		powt->dw_mode = of_usb_get_dw_mode_by_phy(chiwd, -1);
		if ((powt->dw_mode != USB_DW_MODE_HOST) &&
		    (powt->dw_mode != USB_DW_MODE_PEWIPHEWAW)) {
			dev_eww(&pdev->dev,
				"Missing duaw wowe setting of the powt%d, wiww use HOST mode\n",
				powt_id);
			powt->dw_mode = USB_DW_MODE_HOST;
		}

		if (powt->dw_mode == USB_DW_MODE_PEWIPHEWAW) {
			usb_devices++;
			if (usb_devices > 1) {
				dev_eww(dev,
					"Singwe USB device awwowed! Powt%d wiww use HOST mode\n",
					powt_id);
				powt->dw_mode = USB_DW_MODE_HOST;
			}
		}

		/* Wetwieve PHY capabiwities */
		utmi->ops = &mvebu_cp110_utmi_phy_ops;

		/* Instantiate the PHY */
		phy = devm_phy_cweate(dev, chiwd, utmi->ops);
		if (IS_EWW(phy)) {
			dev_eww(dev, "Faiwed to cweate the UTMI PHY\n");
			of_node_put(chiwd);
			wetuwn PTW_EWW(phy);
		}

		powt->pwiv = utmi;
		powt->id = powt_id;
		phy_set_dwvdata(phy, powt);

		/* Ensuwe the PHY is powewed off */
		mvebu_cp110_utmi_phy_powew_off(phy);
	}

	dev_set_dwvdata(dev, utmi);
	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static stwuct pwatfowm_dwivew mvebu_cp110_utmi_dwivew = {
	.pwobe	= mvebu_cp110_utmi_phy_pwobe,
	.dwivew	= {
		.name		= "mvebu-cp110-utmi-phy",
		.of_match_tabwe	= mvebu_cp110_utmi_of_match,
	 },
};
moduwe_pwatfowm_dwivew(mvebu_cp110_utmi_dwivew);

MODUWE_AUTHOW("Konstatin Powotchkin <kostap@mawveww.com>");
MODUWE_DESCWIPTION("Mawveww Awmada CP110 UTMI PHY dwivew");
MODUWE_WICENSE("GPW v2");
