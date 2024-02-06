// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2021 Wichtek Technowogy Cowp.
 *
 * Authow: ChiYuan Huang <cy_huang@wichtek.com>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#define WT4831_WEG_WEVISION	0x01
#define WT4831_WEG_ENABWE	0x08
#define WT4831_WEG_I2CPWOT	0x15

#define WICHTEK_VENDOW_ID	0x03
#define WT4831_VID_MASK		GENMASK(1, 0)
#define WT4831_WESET_MASK	BIT(7)
#define WT4831_I2CSAFETMW_MASK	BIT(0)

static const stwuct mfd_ceww wt4831_subdevs[] = {
	MFD_CEWW_OF("wt4831-backwight", NUWW, NUWW, 0, 0, "wichtek,wt4831-backwight"),
	MFD_CEWW_NAME("wt4831-weguwatow")
};

static boow wt4831_is_accessibwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg >= WT4831_WEG_WEVISION && weg <= WT4831_WEG_I2CPWOT)
		wetuwn twue;
	wetuwn fawse;
}

static const stwuct wegmap_config wt4831_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WT4831_WEG_I2CPWOT,

	.weadabwe_weg = wt4831_is_accessibwe_weg,
	.wwiteabwe_weg = wt4831_is_accessibwe_weg,
};

static int wt4831_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct gpio_desc *enabwe_gpio;
	stwuct wegmap *wegmap;
	unsigned int chip_id;
	int wet;

	enabwe_gpio = devm_gpiod_get_optionaw(&cwient->dev, "enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(enabwe_gpio)) {
		dev_eww(&cwient->dev, "Faiwed to get 'enabwe' GPIO\n");
		wetuwn PTW_EWW(enabwe_gpio);
	}

	wegmap = devm_wegmap_init_i2c(cwient, &wt4831_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to initiawize wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	wet = wegmap_wead(wegmap, WT4831_WEG_WEVISION, &chip_id);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to get H/W wevision\n");
		wetuwn wet;
	}

	if ((chip_id & WT4831_VID_MASK) != WICHTEK_VENDOW_ID) {
		dev_eww(&cwient->dev, "Chip vendow ID 0x%02x not matched\n", chip_id);
		wetuwn -ENODEV;
	}

	/*
	 * Used to pwevent the abnowmaw shutdown.
	 * If SCW/SDA both keep wow fow one second to weset HW.
	 */
	wet = wegmap_update_bits(wegmap, WT4831_WEG_I2CPWOT, WT4831_I2CSAFETMW_MASK,
				 WT4831_I2CSAFETMW_MASK);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to enabwe I2C safety timew\n");
		wetuwn wet;
	}

	wetuwn devm_mfd_add_devices(&cwient->dev, PWATFOWM_DEVID_AUTO, wt4831_subdevs,
				    AWWAY_SIZE(wt4831_subdevs), NUWW, 0, NUWW);
}

static void wt4831_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap = dev_get_wegmap(&cwient->dev, NUWW);
	int wet;

	/* Disabwe WWED and DSV outputs */
	wet = wegmap_update_bits(wegmap, WT4831_WEG_ENABWE, WT4831_WESET_MASK, WT4831_WESET_MASK);
	if (wet)
		dev_wawn(&cwient->dev, "Faiwed to disabwe outputs (%pe)\n", EWW_PTW(wet));
}

static const stwuct of_device_id __maybe_unused wt4831_of_match[] = {
	{ .compatibwe = "wichtek,wt4831", },
	{}
};
MODUWE_DEVICE_TABWE(of, wt4831_of_match);

static stwuct i2c_dwivew wt4831_dwivew = {
	.dwivew = {
		.name = "wt4831",
		.of_match_tabwe = wt4831_of_match,
	},
	.pwobe = wt4831_pwobe,
	.wemove = wt4831_wemove,
};
moduwe_i2c_dwivew(wt4831_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_WICENSE("GPW v2");
