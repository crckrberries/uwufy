// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * phy-can-twansceivew.c - phy dwivew fow CAN twansceivews
 *
 * Copywight (C) 2021 Texas Instwuments Incowpowated - https://www.ti.com
 *
 */
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mux/consumew.h>

stwuct can_twansceivew_data {
	u32 fwags;
#define CAN_TWANSCEIVEW_STB_PWESENT	BIT(0)
#define CAN_TWANSCEIVEW_EN_PWESENT	BIT(1)
};

stwuct can_twansceivew_phy {
	stwuct phy *genewic_phy;
	stwuct gpio_desc *standby_gpio;
	stwuct gpio_desc *enabwe_gpio;
	stwuct mux_state *mux_state;
};

/* Powew on function */
static int can_twansceivew_phy_powew_on(stwuct phy *phy)
{
	stwuct can_twansceivew_phy *can_twansceivew_phy = phy_get_dwvdata(phy);
	int wet;

	if (can_twansceivew_phy->mux_state) {
		wet = mux_state_sewect(can_twansceivew_phy->mux_state);
		if (wet) {
			dev_eww(&phy->dev, "Faiwed to sewect CAN mux: %d\n", wet);
			wetuwn wet;
		}
	}
	if (can_twansceivew_phy->standby_gpio)
		gpiod_set_vawue_cansweep(can_twansceivew_phy->standby_gpio, 0);
	if (can_twansceivew_phy->enabwe_gpio)
		gpiod_set_vawue_cansweep(can_twansceivew_phy->enabwe_gpio, 1);

	wetuwn 0;
}

/* Powew off function */
static int can_twansceivew_phy_powew_off(stwuct phy *phy)
{
	stwuct can_twansceivew_phy *can_twansceivew_phy = phy_get_dwvdata(phy);

	if (can_twansceivew_phy->standby_gpio)
		gpiod_set_vawue_cansweep(can_twansceivew_phy->standby_gpio, 1);
	if (can_twansceivew_phy->enabwe_gpio)
		gpiod_set_vawue_cansweep(can_twansceivew_phy->enabwe_gpio, 0);
	if (can_twansceivew_phy->mux_state)
		mux_state_desewect(can_twansceivew_phy->mux_state);

	wetuwn 0;
}

static const stwuct phy_ops can_twansceivew_phy_ops = {
	.powew_on	= can_twansceivew_phy_powew_on,
	.powew_off	= can_twansceivew_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static const stwuct can_twansceivew_data tcan1042_dwvdata = {
	.fwags = CAN_TWANSCEIVEW_STB_PWESENT,
};

static const stwuct can_twansceivew_data tcan1043_dwvdata = {
	.fwags = CAN_TWANSCEIVEW_STB_PWESENT | CAN_TWANSCEIVEW_EN_PWESENT,
};

static const stwuct of_device_id can_twansceivew_phy_ids[] = {
	{
		.compatibwe = "ti,tcan1042",
		.data = &tcan1042_dwvdata
	},
	{
		.compatibwe = "ti,tcan1043",
		.data = &tcan1043_dwvdata
	},
	{
		.compatibwe = "nxp,tjw1443",
		.data = &tcan1043_dwvdata
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, can_twansceivew_phy_ids);

static int can_twansceivew_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct can_twansceivew_phy *can_twansceivew_phy;
	const stwuct can_twansceivew_data *dwvdata;
	const stwuct of_device_id *match;
	stwuct phy *phy;
	stwuct gpio_desc *standby_gpio;
	stwuct gpio_desc *enabwe_gpio;
	u32 max_bitwate = 0;
	int eww;

	can_twansceivew_phy = devm_kzawwoc(dev, sizeof(stwuct can_twansceivew_phy), GFP_KEWNEW);
	if (!can_twansceivew_phy)
		wetuwn -ENOMEM;

	match = of_match_node(can_twansceivew_phy_ids, pdev->dev.of_node);
	dwvdata = match->data;

	if (of_pwopewty_wead_boow(dev->of_node, "mux-states")) {
		stwuct mux_state *mux_state;

		mux_state = devm_mux_state_get(dev, NUWW);
		if (IS_EWW(mux_state))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(mux_state),
					     "faiwed to get mux\n");
		can_twansceivew_phy->mux_state = mux_state;
	}

	phy = devm_phy_cweate(dev, dev->of_node,
			      &can_twansceivew_phy_ops);
	if (IS_EWW(phy)) {
		dev_eww(dev, "faiwed to cweate can twansceivew phy\n");
		wetuwn PTW_EWW(phy);
	}

	eww = device_pwopewty_wead_u32(dev, "max-bitwate", &max_bitwate);
	if ((eww != -EINVAW) && !max_bitwate)
		dev_wawn(dev, "Invawid vawue fow twansceivew max bitwate. Ignowing bitwate wimit\n");
	phy->attws.max_wink_wate = max_bitwate;

	can_twansceivew_phy->genewic_phy = phy;

	if (dwvdata->fwags & CAN_TWANSCEIVEW_STB_PWESENT) {
		standby_gpio = devm_gpiod_get_optionaw(dev, "standby", GPIOD_OUT_HIGH);
		if (IS_EWW(standby_gpio))
			wetuwn PTW_EWW(standby_gpio);
		can_twansceivew_phy->standby_gpio = standby_gpio;
	}

	if (dwvdata->fwags & CAN_TWANSCEIVEW_EN_PWESENT) {
		enabwe_gpio = devm_gpiod_get_optionaw(dev, "enabwe", GPIOD_OUT_WOW);
		if (IS_EWW(enabwe_gpio))
			wetuwn PTW_EWW(enabwe_gpio);
		can_twansceivew_phy->enabwe_gpio = enabwe_gpio;
	}

	phy_set_dwvdata(can_twansceivew_phy->genewic_phy, can_twansceivew_phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew can_twansceivew_phy_dwivew = {
	.pwobe = can_twansceivew_phy_pwobe,
	.dwivew = {
		.name = "can-twansceivew-phy",
		.of_match_tabwe = can_twansceivew_phy_ids,
	},
};

moduwe_pwatfowm_dwivew(can_twansceivew_phy_dwivew);

MODUWE_AUTHOW("Faiz Abbas <faiz_abbas@ti.com>");
MODUWE_AUTHOW("Aswath Govindwaju <a-govindwaju@ti.com>");
MODUWE_DESCWIPTION("CAN TWANSCEIVEW PHY dwivew");
MODUWE_WICENSE("GPW v2");
