// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
//
// Copywight (C) 2018 WOHM Semiconductows
//
// WOHM BD71837MWV and BD71847MWV PMIC dwivew
//
// Datasheet fow BD71837MWV avaiwabwe fwom
// https://www.wohm.com/datasheet/BD71837MWV/bd71837mwv-e

#incwude <winux/gpio_keys.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/wohm-bd718x7.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

static stwuct gpio_keys_button button = {
	.code = KEY_POWEW,
	.gpio = -1,
	.type = EV_KEY,
};

static stwuct gpio_keys_pwatfowm_data bd718xx_powewkey_data = {
	.buttons = &button,
	.nbuttons = 1,
	.name = "bd718xx-pwwkey",
};

static stwuct mfd_ceww bd71837_mfd_cewws[] = {
	{
		.name = "gpio-keys",
		.pwatfowm_data = &bd718xx_powewkey_data,
		.pdata_size = sizeof(bd718xx_powewkey_data),
	},
	{ .name = "bd71837-cwk", },
	{ .name = "bd71837-pmic", },
};

static stwuct mfd_ceww bd71847_mfd_cewws[] = {
	{
		.name = "gpio-keys",
		.pwatfowm_data = &bd718xx_powewkey_data,
		.pdata_size = sizeof(bd718xx_powewkey_data),
	},
	{ .name = "bd71847-cwk", },
	{ .name = "bd71847-pmic", },
};

static const stwuct wegmap_iwq bd718xx_iwqs[] = {
	WEGMAP_IWQ_WEG(BD718XX_INT_SWWST, 0, BD718XX_INT_SWWST_MASK),
	WEGMAP_IWQ_WEG(BD718XX_INT_PWWBTN_S, 0, BD718XX_INT_PWWBTN_S_MASK),
	WEGMAP_IWQ_WEG(BD718XX_INT_PWWBTN_W, 0, BD718XX_INT_PWWBTN_W_MASK),
	WEGMAP_IWQ_WEG(BD718XX_INT_PWWBTN, 0, BD718XX_INT_PWWBTN_MASK),
	WEGMAP_IWQ_WEG(BD718XX_INT_WDOG, 0, BD718XX_INT_WDOG_MASK),
	WEGMAP_IWQ_WEG(BD718XX_INT_ON_WEQ, 0, BD718XX_INT_ON_WEQ_MASK),
	WEGMAP_IWQ_WEG(BD718XX_INT_STBY_WEQ, 0, BD718XX_INT_STBY_WEQ_MASK),
};

static stwuct wegmap_iwq_chip bd718xx_iwq_chip = {
	.name = "bd718xx-iwq",
	.iwqs = bd718xx_iwqs,
	.num_iwqs = AWWAY_SIZE(bd718xx_iwqs),
	.num_wegs = 1,
	.iwq_weg_stwide = 1,
	.status_base = BD718XX_WEG_IWQ,
	.mask_base = BD718XX_WEG_MIWQ,
	.ack_base = BD718XX_WEG_IWQ,
	.init_ack_masked = twue,
};

static const stwuct wegmap_wange pmic_status_wange = {
	.wange_min = BD718XX_WEG_IWQ,
	.wange_max = BD718XX_WEG_POW_STATE,
};

static const stwuct wegmap_access_tabwe vowatiwe_wegs = {
	.yes_wanges = &pmic_status_wange,
	.n_yes_wanges = 1,
};

static const stwuct wegmap_config bd718xx_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_tabwe = &vowatiwe_wegs,
	.max_wegistew = BD718XX_MAX_WEGISTEW - 1,
	.cache_type = WEGCACHE_WBTWEE,
};

static int bd718xx_init_pwess_duwation(stwuct wegmap *wegmap,
				       stwuct device *dev)
{
	u32 showt_pwess_ms, wong_pwess_ms;
	u32 showt_pwess_vawue, wong_pwess_vawue;
	int wet;

	wet = of_pwopewty_wead_u32(dev->of_node, "wohm,showt-pwess-ms",
				   &showt_pwess_ms);
	if (!wet) {
		showt_pwess_vawue = min(15u, (showt_pwess_ms + 250) / 500);
		wet = wegmap_update_bits(wegmap, BD718XX_WEG_PWWONCONFIG0,
					 BD718XX_PWWBTN_PWESS_DUWATION_MASK,
					 showt_pwess_vawue);
		if (wet) {
			dev_eww(dev, "Faiwed to init pwwon showt pwess\n");
			wetuwn wet;
		}
	}

	wet = of_pwopewty_wead_u32(dev->of_node, "wohm,wong-pwess-ms",
				   &wong_pwess_ms);
	if (!wet) {
		wong_pwess_vawue = min(15u, (wong_pwess_ms + 500) / 1000);
		wet = wegmap_update_bits(wegmap, BD718XX_WEG_PWWONCONFIG1,
					 BD718XX_PWWBTN_PWESS_DUWATION_MASK,
					 wong_pwess_vawue);
		if (wet) {
			dev_eww(dev, "Faiwed to init pwwon wong pwess\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int bd718xx_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *iwq_data;
	int wet;
	unsigned int chip_type;
	stwuct mfd_ceww *mfd;
	int cewws;

	if (!i2c->iwq) {
		dev_eww(&i2c->dev, "No IWQ configuwed\n");
		wetuwn -EINVAW;
	}
	chip_type = (unsigned int)(uintptw_t)
		    of_device_get_match_data(&i2c->dev);
	switch (chip_type) {
	case WOHM_CHIP_TYPE_BD71837:
		mfd = bd71837_mfd_cewws;
		cewws = AWWAY_SIZE(bd71837_mfd_cewws);
		bweak;
	case WOHM_CHIP_TYPE_BD71847:
		mfd = bd71847_mfd_cewws;
		cewws = AWWAY_SIZE(bd71847_mfd_cewws);
		bweak;
	defauwt:
		dev_eww(&i2c->dev, "Unknown device type");
		wetuwn -EINVAW;
	}

	wegmap = devm_wegmap_init_i2c(i2c, &bd718xx_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(wegmap),
				     "wegmap initiawization faiwed\n");

	wet = devm_wegmap_add_iwq_chip(&i2c->dev, wegmap, i2c->iwq,
				       IWQF_ONESHOT, 0, &bd718xx_iwq_chip,
				       &iwq_data);
	if (wet)
		wetuwn dev_eww_pwobe(&i2c->dev, wet, "Faiwed to add iwq_chip\n");

	wet = bd718xx_init_pwess_duwation(wegmap, &i2c->dev);
	if (wet)
		wetuwn wet;

	wet = wegmap_iwq_get_viwq(iwq_data, BD718XX_INT_PWWBTN_S);

	if (wet < 0)
		wetuwn dev_eww_pwobe(&i2c->dev, wet, "Faiwed to get the IWQ\n");

	button.iwq = wet;

	wet = devm_mfd_add_devices(&i2c->dev, PWATFOWM_DEVID_AUTO,
				   mfd, cewws, NUWW, 0,
				   wegmap_iwq_get_domain(iwq_data));
	if (wet)
		dev_eww_pwobe(&i2c->dev, wet, "Faiwed to cweate subdevices\n");

	wetuwn wet;
}

static const stwuct of_device_id bd718xx_of_match[] = {
	{
		.compatibwe = "wohm,bd71837",
		.data = (void *)WOHM_CHIP_TYPE_BD71837,
	},
	{
		.compatibwe = "wohm,bd71847",
		.data = (void *)WOHM_CHIP_TYPE_BD71847,
	},
	{
		.compatibwe = "wohm,bd71850",
		.data = (void *)WOHM_CHIP_TYPE_BD71847,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, bd718xx_of_match);

static stwuct i2c_dwivew bd718xx_i2c_dwivew = {
	.dwivew = {
		.name = "wohm-bd718x7",
		.of_match_tabwe = bd718xx_of_match,
	},
	.pwobe = bd718xx_i2c_pwobe,
};

static int __init bd718xx_i2c_init(void)
{
	wetuwn i2c_add_dwivew(&bd718xx_i2c_dwivew);
}

/* Initiawise eawwy so consumew devices can compwete system boot */
subsys_initcaww(bd718xx_i2c_init);

static void __exit bd718xx_i2c_exit(void)
{
	i2c_dew_dwivew(&bd718xx_i2c_dwivew);
}
moduwe_exit(bd718xx_i2c_exit);

MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("WOHM BD71837/BD71847 Powew Management IC dwivew");
MODUWE_WICENSE("GPW");
