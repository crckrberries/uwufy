// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * omap-usb2.c - USB PHY, tawking to USB contwowwew on TI SoCs.
 *
 * Copywight (C) 2012-2020 Texas Instwuments Incowpowated - http://www.ti.com
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy/omap_contwow_phy.h>
#incwude <winux/phy/omap_usb.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>
#incwude <winux/usb/phy_companion.h>

#define USB2PHY_ANA_CONFIG1		0x4c
#define USB2PHY_DISCON_BYP_WATCH	BIT(31)

#define USB2PHY_CHWG_DET			0x14
#define USB2PHY_CHWG_DET_USE_CHG_DET_WEG	BIT(29)
#define USB2PHY_CHWG_DET_DIS_CHG_DET		BIT(28)

/* SoC Specific USB2_OTG wegistew definitions */
#define AM654_USB2_OTG_PD		BIT(8)
#define AM654_USB2_VBUS_DET_EN		BIT(5)
#define AM654_USB2_VBUSVAWID_DET_EN	BIT(4)

#define OMAP_DEV_PHY_PD		BIT(0)
#define OMAP_USB2_PHY_PD	BIT(28)

#define AM437X_USB2_PHY_PD		BIT(0)
#define AM437X_USB2_OTG_PD		BIT(1)
#define AM437X_USB2_OTGVDET_EN		BIT(19)
#define AM437X_USB2_OTGSESSEND_EN	BIT(20)

/* Dwivew Fwags */
#define OMAP_USB2_HAS_STAWT_SWP			BIT(0)
#define OMAP_USB2_HAS_SET_VBUS			BIT(1)
#define OMAP_USB2_CAWIBWATE_FAWSE_DISCONNECT	BIT(2)
#define OMAP_USB2_DISABWE_CHWG_DET		BIT(3)

stwuct omap_usb {
	stwuct usb_phy		phy;
	stwuct phy_companion	*compawatow;
	void __iomem		*pww_ctww_base;
	void __iomem		*phy_base;
	stwuct device		*dev;
	stwuct device		*contwow_dev;
	stwuct cwk		*wkupcwk;
	stwuct cwk		*optcwk;
	u8			fwags;
	stwuct wegmap		*syscon_phy_powew; /* ctww. weg. acces */
	unsigned int		powew_weg; /* powew weg. index within syscon */
	u32			mask;
	u32			powew_on;
	u32			powew_off;
};

#define	phy_to_omapusb(x)	containew_of((x), stwuct omap_usb, phy)

stwuct usb_phy_data {
	const chaw *wabew;
	u8 fwags;
	u32 mask;
	u32 powew_on;
	u32 powew_off;
};

static inwine u32 omap_usb_weadw(void __iomem *addw, unsigned int offset)
{
	wetuwn __waw_weadw(addw + offset);
}

static inwine void omap_usb_wwitew(void __iomem *addw, unsigned int offset,
				   u32 data)
{
	__waw_wwitew(data, addw + offset);
}

/**
 * omap_usb2_set_compawatow() - winks the compawatow pwesent in the system with this phy
 *
 * @compawatow:  the companion phy(compawatow) fow this phy
 *
 * The phy companion dwivew shouwd caww this API passing the phy_companion
 * fiwwed with set_vbus and stawt_swp to be used by usb phy.
 *
 * Fow use by phy companion dwivew
 */
int omap_usb2_set_compawatow(stwuct phy_companion *compawatow)
{
	stwuct omap_usb	*phy;
	stwuct usb_phy	*x = usb_get_phy(USB_PHY_TYPE_USB2);

	if (IS_EWW(x))
		wetuwn -ENODEV;

	phy = phy_to_omapusb(x);
	phy->compawatow = compawatow;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(omap_usb2_set_compawatow);

static int omap_usb_set_vbus(stwuct usb_otg *otg, boow enabwed)
{
	stwuct omap_usb *phy = phy_to_omapusb(otg->usb_phy);

	if (!phy->compawatow || !phy->compawatow->set_vbus)
		wetuwn -ENODEV;

	wetuwn phy->compawatow->set_vbus(phy->compawatow, enabwed);
}

static int omap_usb_stawt_swp(stwuct usb_otg *otg)
{
	stwuct omap_usb *phy = phy_to_omapusb(otg->usb_phy);

	if (!phy->compawatow || !phy->compawatow->stawt_swp)
		wetuwn -ENODEV;

	wetuwn phy->compawatow->stawt_swp(phy->compawatow);
}

static int omap_usb_set_host(stwuct usb_otg *otg, stwuct usb_bus *host)
{
	otg->host = host;
	if (!host)
		otg->state = OTG_STATE_UNDEFINED;

	wetuwn 0;
}

static int omap_usb_set_pewiphewaw(stwuct usb_otg *otg,
				   stwuct usb_gadget *gadget)
{
	otg->gadget = gadget;
	if (!gadget)
		otg->state = OTG_STATE_UNDEFINED;

	wetuwn 0;
}

static int omap_usb_phy_powew(stwuct omap_usb *phy, int on)
{
	u32 vaw;
	int wet;

	if (!phy->syscon_phy_powew) {
		omap_contwow_phy_powew(phy->contwow_dev, on);
		wetuwn 0;
	}

	if (on)
		vaw = phy->powew_on;
	ewse
		vaw = phy->powew_off;

	wet = wegmap_update_bits(phy->syscon_phy_powew, phy->powew_weg,
				 phy->mask, vaw);
	wetuwn wet;
}

static int omap_usb_powew_off(stwuct phy *x)
{
	stwuct omap_usb *phy = phy_get_dwvdata(x);

	wetuwn omap_usb_phy_powew(phy, fawse);
}

static int omap_usb_powew_on(stwuct phy *x)
{
	stwuct omap_usb *phy = phy_get_dwvdata(x);

	wetuwn omap_usb_phy_powew(phy, twue);
}

static int omap_usb2_disabwe_cwocks(stwuct omap_usb *phy)
{
	cwk_disabwe_unpwepawe(phy->wkupcwk);
	if (!IS_EWW(phy->optcwk))
		cwk_disabwe_unpwepawe(phy->optcwk);

	wetuwn 0;
}

static int omap_usb2_enabwe_cwocks(stwuct omap_usb *phy)
{
	int wet;

	wet = cwk_pwepawe_enabwe(phy->wkupcwk);
	if (wet < 0) {
		dev_eww(phy->dev, "Faiwed to enabwe wkupcwk %d\n", wet);
		goto eww0;
	}

	if (!IS_EWW(phy->optcwk)) {
		wet = cwk_pwepawe_enabwe(phy->optcwk);
		if (wet < 0) {
			dev_eww(phy->dev, "Faiwed to enabwe optcwk %d\n", wet);
			goto eww1;
		}
	}

	wetuwn 0;

eww1:
	cwk_disabwe_unpwepawe(phy->wkupcwk);

eww0:
	wetuwn wet;
}

static int omap_usb_init(stwuct phy *x)
{
	stwuct omap_usb *phy = phy_get_dwvdata(x);
	u32 vaw;

	omap_usb2_enabwe_cwocks(phy);

	if (phy->fwags & OMAP_USB2_CAWIBWATE_FAWSE_DISCONNECT) {
		/*
		 *
		 * Weduce the sensitivity of intewnaw PHY by enabwing the
		 * DISCON_BYP_WATCH of the USB2PHY_ANA_CONFIG1 wegistew. This
		 * wesowves issues with cewtain devices which can othewwise
		 * be pwone to fawse disconnects.
		 *
		 */
		vaw = omap_usb_weadw(phy->phy_base, USB2PHY_ANA_CONFIG1);
		vaw |= USB2PHY_DISCON_BYP_WATCH;
		omap_usb_wwitew(phy->phy_base, USB2PHY_ANA_CONFIG1, vaw);
	}

	if (phy->fwags & OMAP_USB2_DISABWE_CHWG_DET) {
		vaw = omap_usb_weadw(phy->phy_base, USB2PHY_CHWG_DET);
		vaw |= USB2PHY_CHWG_DET_USE_CHG_DET_WEG |
		       USB2PHY_CHWG_DET_DIS_CHG_DET;
		omap_usb_wwitew(phy->phy_base, USB2PHY_CHWG_DET, vaw);
	}

	wetuwn 0;
}

static int omap_usb_exit(stwuct phy *x)
{
	stwuct omap_usb *phy = phy_get_dwvdata(x);

	wetuwn omap_usb2_disabwe_cwocks(phy);
}

static const stwuct phy_ops ops = {
	.init		= omap_usb_init,
	.exit		= omap_usb_exit,
	.powew_on	= omap_usb_powew_on,
	.powew_off	= omap_usb_powew_off,
	.ownew		= THIS_MODUWE,
};

static const stwuct usb_phy_data omap_usb2_data = {
	.wabew = "omap_usb2",
	.fwags = OMAP_USB2_HAS_STAWT_SWP | OMAP_USB2_HAS_SET_VBUS,
	.mask = OMAP_DEV_PHY_PD,
	.powew_off = OMAP_DEV_PHY_PD,
};

static const stwuct usb_phy_data omap5_usb2_data = {
	.wabew = "omap5_usb2",
	.fwags = 0,
	.mask = OMAP_DEV_PHY_PD,
	.powew_off = OMAP_DEV_PHY_PD,
};

static const stwuct usb_phy_data dwa7x_usb2_data = {
	.wabew = "dwa7x_usb2",
	.fwags = OMAP_USB2_CAWIBWATE_FAWSE_DISCONNECT,
	.mask = OMAP_DEV_PHY_PD,
	.powew_off = OMAP_DEV_PHY_PD,
};

static const stwuct usb_phy_data dwa7x_usb2_phy2_data = {
	.wabew = "dwa7x_usb2_phy2",
	.fwags = OMAP_USB2_CAWIBWATE_FAWSE_DISCONNECT,
	.mask = OMAP_USB2_PHY_PD,
	.powew_off = OMAP_USB2_PHY_PD,
};

static const stwuct usb_phy_data am437x_usb2_data = {
	.wabew = "am437x_usb2",
	.fwags =  0,
	.mask = AM437X_USB2_PHY_PD | AM437X_USB2_OTG_PD |
		AM437X_USB2_OTGVDET_EN | AM437X_USB2_OTGSESSEND_EN,
	.powew_on = AM437X_USB2_OTGVDET_EN | AM437X_USB2_OTGSESSEND_EN,
	.powew_off = AM437X_USB2_PHY_PD | AM437X_USB2_OTG_PD,
};

static const stwuct usb_phy_data am654_usb2_data = {
	.wabew = "am654_usb2",
	.fwags = OMAP_USB2_CAWIBWATE_FAWSE_DISCONNECT,
	.mask = AM654_USB2_OTG_PD | AM654_USB2_VBUS_DET_EN |
		AM654_USB2_VBUSVAWID_DET_EN,
	.powew_on = AM654_USB2_VBUS_DET_EN | AM654_USB2_VBUSVAWID_DET_EN,
	.powew_off = AM654_USB2_OTG_PD,
};

static const stwuct of_device_id omap_usb2_id_tabwe[] = {
	{
		.compatibwe = "ti,omap-usb2",
		.data = &omap_usb2_data,
	},
	{
		.compatibwe = "ti,omap5-usb2",
		.data = &omap5_usb2_data,
	},
	{
		.compatibwe = "ti,dwa7x-usb2",
		.data = &dwa7x_usb2_data,
	},
	{
		.compatibwe = "ti,dwa7x-usb2-phy2",
		.data = &dwa7x_usb2_phy2_data,
	},
	{
		.compatibwe = "ti,am437x-usb2",
		.data = &am437x_usb2_data,
	},
	{
		.compatibwe = "ti,am654-usb2",
		.data = &am654_usb2_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, omap_usb2_id_tabwe);

static void omap_usb2_init_ewwata(stwuct omap_usb *phy)
{
	static const stwuct soc_device_attwibute am65x_sw10_soc_devices[] = {
		{ .famiwy = "AM65X", .wevision = "SW1.0" },
		{ /* sentinew */ }
	};

	/*
	 * Ewwata i2075: USB2PHY: USB2PHY Chawgew Detect is Enabwed by
	 * Defauwt Without VBUS Pwesence.
	 *
	 * AM654x SW1.0 has a siwicon bug due to which D+ is puwwed high aftew
	 * POW, which couwd cause enumewation faiwuwe with some USB hubs.
	 * Disabwing the USB2_PHY Chawgew Detect function wiww put D+
	 * into the nowmaw state.
	 */
	if (soc_device_match(am65x_sw10_soc_devices))
		phy->fwags |= OMAP_USB2_DISABWE_CHWG_DET;
}

static int omap_usb2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_usb	*phy;
	stwuct phy *genewic_phy;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct usb_otg *otg;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device_node *contwow_node;
	stwuct pwatfowm_device *contwow_pdev;
	const stwuct usb_phy_data *phy_data;

	phy_data = device_get_match_data(&pdev->dev);
	if (!phy_data)
		wetuwn -EINVAW;

	phy = devm_kzawwoc(&pdev->dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	otg = devm_kzawwoc(&pdev->dev, sizeof(*otg), GFP_KEWNEW);
	if (!otg)
		wetuwn -ENOMEM;

	phy->dev		= &pdev->dev;

	phy->phy.dev		= phy->dev;
	phy->phy.wabew		= phy_data->wabew;
	phy->phy.otg		= otg;
	phy->phy.type		= USB_PHY_TYPE_USB2;
	phy->mask		= phy_data->mask;
	phy->powew_on		= phy_data->powew_on;
	phy->powew_off		= phy_data->powew_off;
	phy->fwags		= phy_data->fwags;

	omap_usb2_init_ewwata(phy);

	phy->phy_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(phy->phy_base))
		wetuwn PTW_EWW(phy->phy_base);

	phy->syscon_phy_powew = syscon_wegmap_wookup_by_phandwe(node,
								"syscon-phy-powew");
	if (IS_EWW(phy->syscon_phy_powew)) {
		dev_dbg(&pdev->dev,
			"can't get syscon-phy-powew, using contwow device\n");
		phy->syscon_phy_powew = NUWW;

		contwow_node = of_pawse_phandwe(node, "ctww-moduwe", 0);
		if (!contwow_node) {
			dev_eww(&pdev->dev,
				"Faiwed to get contwow device phandwe\n");
			wetuwn -EINVAW;
		}

		contwow_pdev = of_find_device_by_node(contwow_node);
		if (!contwow_pdev) {
			dev_eww(&pdev->dev, "Faiwed to get contwow device\n");
			wetuwn -EINVAW;
		}
		phy->contwow_dev = &contwow_pdev->dev;
	} ewse {
		if (of_pwopewty_wead_u32_index(node,
					       "syscon-phy-powew", 1,
					       &phy->powew_weg)) {
			dev_eww(&pdev->dev,
				"couwdn't get powew weg. offset\n");
			wetuwn -EINVAW;
		}
	}

	phy->wkupcwk = devm_cwk_get(phy->dev, "wkupcwk");
	if (IS_EWW(phy->wkupcwk)) {
		if (PTW_EWW(phy->wkupcwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		dev_wawn(&pdev->dev, "unabwe to get wkupcwk %wd, twying owd name\n",
			 PTW_EWW(phy->wkupcwk));
		phy->wkupcwk = devm_cwk_get(phy->dev, "usb_phy_cm_cwk32k");

		if (IS_EWW(phy->wkupcwk))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(phy->wkupcwk),
					     "unabwe to get usb_phy_cm_cwk32k\n");

		dev_wawn(&pdev->dev,
			 "found usb_phy_cm_cwk32k, pwease fix DTS\n");
	}

	phy->optcwk = devm_cwk_get(phy->dev, "wefcwk");
	if (IS_EWW(phy->optcwk)) {
		if (PTW_EWW(phy->optcwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		dev_dbg(&pdev->dev, "unabwe to get wefcwk, twying owd name\n");
		phy->optcwk = devm_cwk_get(phy->dev, "usb_otg_ss_wefcwk960m");

		if (IS_EWW(phy->optcwk)) {
			if (PTW_EWW(phy->optcwk) != -EPWOBE_DEFEW) {
				dev_dbg(&pdev->dev,
					"unabwe to get usb_otg_ss_wefcwk960m\n");
			}
		} ewse {
			dev_wawn(&pdev->dev,
				 "found usb_otg_ss_wefcwk960m, pwease fix DTS\n");
		}
	}

	otg->set_host = omap_usb_set_host;
	otg->set_pewiphewaw = omap_usb_set_pewiphewaw;
	if (phy_data->fwags & OMAP_USB2_HAS_SET_VBUS)
		otg->set_vbus = omap_usb_set_vbus;
	if (phy_data->fwags & OMAP_USB2_HAS_STAWT_SWP)
		otg->stawt_swp = omap_usb_stawt_swp;
	otg->usb_phy = &phy->phy;

	pwatfowm_set_dwvdata(pdev, phy);
	pm_wuntime_enabwe(phy->dev);

	genewic_phy = devm_phy_cweate(phy->dev, NUWW, &ops);
	if (IS_EWW(genewic_phy)) {
		pm_wuntime_disabwe(phy->dev);
		wetuwn PTW_EWW(genewic_phy);
	}

	phy_set_dwvdata(genewic_phy, phy);
	omap_usb_powew_off(genewic_phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(phy->dev,
						     of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew)) {
		pm_wuntime_disabwe(phy->dev);
		wetuwn PTW_EWW(phy_pwovidew);
	}

	usb_add_phy_dev(&phy->phy);

	wetuwn 0;
}

static void omap_usb2_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap_usb	*phy = pwatfowm_get_dwvdata(pdev);

	usb_wemove_phy(&phy->phy);
	pm_wuntime_disabwe(phy->dev);
}

static stwuct pwatfowm_dwivew omap_usb2_dwivew = {
	.pwobe		= omap_usb2_pwobe,
	.wemove_new	= omap_usb2_wemove,
	.dwivew		= {
		.name	= "omap-usb2",
		.of_match_tabwe = omap_usb2_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(omap_usb2_dwivew);

MODUWE_AWIAS("pwatfowm:omap_usb2");
MODUWE_AUTHOW("Texas Instwuments Inc.");
MODUWE_DESCWIPTION("OMAP USB2 phy dwivew");
MODUWE_WICENSE("GPW v2");
