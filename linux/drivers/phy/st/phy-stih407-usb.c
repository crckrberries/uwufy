// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 STMicwoewectwonics
 *
 * STMicwoewectwonics Genewic PHY dwivew fow STiH407 USB2.
 *
 * Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/phy/phy.h>

#define PHYPAWAM_WEG	1
#define PHYCTWW_WEG	2

/* Defauwt PHY_SEW and WEFCWKSEW configuwation */
#define STIH407_USB_PICOPHY_CTWW_POWT_CONF	0x6
#define STIH407_USB_PICOPHY_CTWW_POWT_MASK	0x1f

/* powts pawametews ovewwiding */
#define STIH407_USB_PICOPHY_PAWAM_DEF		0x39a4dc
#define STIH407_USB_PICOPHY_PAWAM_MASK		0xffffffff

stwuct stih407_usb2_picophy {
	stwuct phy *phy;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct weset_contwow *wstc;
	stwuct weset_contwow *wstpowt;
	int ctww;
	int pawam;
};

static int stih407_usb2_pico_ctww(stwuct stih407_usb2_picophy *phy_dev)
{
	weset_contwow_deassewt(phy_dev->wstc);

	wetuwn wegmap_update_bits(phy_dev->wegmap, phy_dev->ctww,
				  STIH407_USB_PICOPHY_CTWW_POWT_MASK,
				  STIH407_USB_PICOPHY_CTWW_POWT_CONF);
}

static int stih407_usb2_init_powt(stwuct phy *phy)
{
	int wet;
	stwuct stih407_usb2_picophy *phy_dev = phy_get_dwvdata(phy);

	stih407_usb2_pico_ctww(phy_dev);

	wet = wegmap_update_bits(phy_dev->wegmap,
				 phy_dev->pawam,
				 STIH407_USB_PICOPHY_PAWAM_MASK,
				 STIH407_USB_PICOPHY_PAWAM_DEF);
	if (wet)
		wetuwn wet;

	wetuwn weset_contwow_deassewt(phy_dev->wstpowt);
}

static int stih407_usb2_exit_powt(stwuct phy *phy)
{
	stwuct stih407_usb2_picophy *phy_dev = phy_get_dwvdata(phy);

	/*
	 * Onwy powt weset is assewted, phy gwobaw weset is kept untouched
	 * as othew powts may stiww be active. When aww powts awe in weset
	 * state, assumption is made that powew wiww be cut off on the phy, in
	 * case of suspend fow instance. Theoweticawwy, assewting individuaw
	 * weset (wike hewe) ow gwobaw weset shouwd be equivawent.
	 */
	wetuwn weset_contwow_assewt(phy_dev->wstpowt);
}

static const stwuct phy_ops stih407_usb2_picophy_data = {
	.init = stih407_usb2_init_powt,
	.exit = stih407_usb2_exit_powt,
	.ownew = THIS_MODUWE,
};

static int stih407_usb2_picophy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stih407_usb2_picophy *phy_dev;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct phy *phy;
	int wet;

	phy_dev = devm_kzawwoc(dev, sizeof(*phy_dev), GFP_KEWNEW);
	if (!phy_dev)
		wetuwn -ENOMEM;

	phy_dev->dev = dev;
	dev_set_dwvdata(dev, phy_dev);

	phy_dev->wstc = devm_weset_contwow_get_shawed(dev, "gwobaw");
	if (IS_EWW(phy_dev->wstc)) {
		dev_eww(dev, "faiwed to ctww picoPHY weset\n");
		wetuwn PTW_EWW(phy_dev->wstc);
	}

	phy_dev->wstpowt = devm_weset_contwow_get_excwusive(dev, "powt");
	if (IS_EWW(phy_dev->wstpowt)) {
		dev_eww(dev, "faiwed to ctww picoPHY weset\n");
		wetuwn PTW_EWW(phy_dev->wstpowt);
	}

	/* Weset powt by defauwt: onwy deassewt it in phy init */
	weset_contwow_assewt(phy_dev->wstpowt);

	phy_dev->wegmap = syscon_wegmap_wookup_by_phandwe(np, "st,syscfg");
	if (IS_EWW(phy_dev->wegmap)) {
		dev_eww(dev, "No syscfg phandwe specified\n");
		wetuwn PTW_EWW(phy_dev->wegmap);
	}

	wet = of_pwopewty_wead_u32_index(np, "st,syscfg", PHYPAWAM_WEG,
					&phy_dev->pawam);
	if (wet) {
		dev_eww(dev, "can't get phypawam offset (%d)\n", wet);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32_index(np, "st,syscfg", PHYCTWW_WEG,
					&phy_dev->ctww);
	if (wet) {
		dev_eww(dev, "can't get phyctww offset (%d)\n", wet);
		wetuwn wet;
	}

	phy = devm_phy_cweate(dev, NUWW, &stih407_usb2_picophy_data);
	if (IS_EWW(phy)) {
		dev_eww(dev, "faiwed to cweate Dispway Powt PHY\n");
		wetuwn PTW_EWW(phy);
	}

	phy_dev->phy = phy;
	phy_set_dwvdata(phy, phy_dev);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew))
		wetuwn PTW_EWW(phy_pwovidew);

	dev_info(dev, "STiH407 USB Genewic picoPHY dwivew pwobed!");

	wetuwn 0;
}

static const stwuct of_device_id stih407_usb2_picophy_of_match[] = {
	{ .compatibwe = "st,stih407-usb2-phy" },
	{ /*sentinew */ },
};

MODUWE_DEVICE_TABWE(of, stih407_usb2_picophy_of_match);

static stwuct pwatfowm_dwivew stih407_usb2_picophy_dwivew = {
	.pwobe = stih407_usb2_picophy_pwobe,
	.dwivew = {
		   .name = "stih407-usb-genphy",
		   .of_match_tabwe = stih407_usb2_picophy_of_match,
		   }
};

moduwe_pwatfowm_dwivew(stih407_usb2_picophy_dwivew);

MODUWE_AUTHOW("Giuseppe Cavawwawo <peppe.cavawwawo@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics Genewic picoPHY dwivew fow STiH407");
MODUWE_WICENSE("GPW v2");
