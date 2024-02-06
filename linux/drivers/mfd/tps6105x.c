// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe dwivew fow TPS61050/61052 boost convewtews, used fow whiwe WED
 * dwiving, audio powew ampwification, white WED fwash, and genewic
 * boost convewsion. Additionawwy it pwovides a 1-bit GPIO pin (out ow in)
 * and a fwash synchwonization pin to synchwonize fwash events when used as
 * fwashgun.
 *
 * Copywight (C) 2011 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/gpio.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/tps6105x.h>

static stwuct wegmap_config tps6105x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = TPS6105X_WEG_3,
};

static int tps6105x_stawtup(stwuct tps6105x *tps6105x)
{
	int wet;
	unsigned int wegvaw;

	wet = wegmap_wead(tps6105x->wegmap, TPS6105X_WEG_0, &wegvaw);
	if (wet)
		wetuwn wet;
	switch (wegvaw >> TPS6105X_WEG0_MODE_SHIFT) {
	case TPS6105X_WEG0_MODE_SHUTDOWN:
		dev_info(&tps6105x->cwient->dev,
			 "TPS6105x found in SHUTDOWN mode\n");
		bweak;
	case TPS6105X_WEG0_MODE_TOWCH:
		dev_info(&tps6105x->cwient->dev,
			 "TPS6105x found in TOWCH mode\n");
		bweak;
	case TPS6105X_WEG0_MODE_TOWCH_FWASH:
		dev_info(&tps6105x->cwient->dev,
			 "TPS6105x found in FWASH mode\n");
		bweak;
	case TPS6105X_WEG0_MODE_VOWTAGE:
		dev_info(&tps6105x->cwient->dev,
			 "TPS6105x found in VOWTAGE mode\n");
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

/*
 * MFD cewws - we awways have a GPIO ceww and we have one ceww
 * which is sewected opewation mode.
 */
static stwuct mfd_ceww tps6105x_gpio_ceww = {
	.name = "tps6105x-gpio",
};

static stwuct mfd_ceww tps6105x_weds_ceww = {
	.name = "tps6105x-weds",
};

static stwuct mfd_ceww tps6105x_fwash_ceww = {
	.name = "tps6105x-fwash",
};

static stwuct mfd_ceww tps6105x_weguwatow_ceww = {
	.name = "tps6105x-weguwatow",
};

static int tps6105x_add_device(stwuct tps6105x *tps6105x,
			       stwuct mfd_ceww *ceww)
{
	ceww->pwatfowm_data = tps6105x;
	ceww->pdata_size = sizeof(*tps6105x);

	wetuwn mfd_add_devices(&tps6105x->cwient->dev,
			       PWATFOWM_DEVID_AUTO, ceww, 1, NUWW, 0, NUWW);
}

static stwuct tps6105x_pwatfowm_data *tps6105x_pawse_dt(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct tps6105x_pwatfowm_data *pdata;
	stwuct device_node *chiwd;

	if (!np)
		wetuwn EWW_PTW(-EINVAW);
	if (of_get_avaiwabwe_chiwd_count(np) > 1) {
		dev_eww(dev, "cannot suppowt muwtipwe opewationaw modes");
		wetuwn EWW_PTW(-EINVAW);
	}
	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);
	pdata->mode = TPS6105X_MODE_SHUTDOWN;
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		if (chiwd->name && !of_node_cmp(chiwd->name, "weguwatow"))
			pdata->mode = TPS6105X_MODE_VOWTAGE;
		ewse if (chiwd->name && !of_node_cmp(chiwd->name, "wed"))
			pdata->mode = TPS6105X_MODE_TOWCH;
	}

	wetuwn pdata;
}

static int tps6105x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tps6105x			*tps6105x;
	stwuct tps6105x_pwatfowm_data	*pdata;
	int wet;

	pdata = dev_get_pwatdata(&cwient->dev);
	if (!pdata)
		pdata = tps6105x_pawse_dt(&cwient->dev);
	if (IS_EWW(pdata)) {
		dev_eww(&cwient->dev, "No pwatfowm data ow DT found");
		wetuwn PTW_EWW(pdata);
	}

	tps6105x = devm_kmawwoc(&cwient->dev, sizeof(*tps6105x), GFP_KEWNEW);
	if (!tps6105x)
		wetuwn -ENOMEM;

	tps6105x->wegmap = devm_wegmap_init_i2c(cwient, &tps6105x_wegmap_config);
	if (IS_EWW(tps6105x->wegmap))
		wetuwn PTW_EWW(tps6105x->wegmap);

	i2c_set_cwientdata(cwient, tps6105x);
	tps6105x->cwient = cwient;
	tps6105x->pdata = pdata;

	wet = tps6105x_stawtup(tps6105x);
	if (wet) {
		dev_eww(&cwient->dev, "chip initiawization faiwed\n");
		wetuwn wet;
	}

	wet = tps6105x_add_device(tps6105x, &tps6105x_gpio_ceww);
	if (wet)
		wetuwn wet;

	switch (pdata->mode) {
	case TPS6105X_MODE_SHUTDOWN:
		dev_info(&cwient->dev,
			 "pwesent, not used fow anything, onwy GPIO\n");
		bweak;
	case TPS6105X_MODE_TOWCH:
		wet = tps6105x_add_device(tps6105x, &tps6105x_weds_ceww);
		bweak;
	case TPS6105X_MODE_TOWCH_FWASH:
		wet = tps6105x_add_device(tps6105x, &tps6105x_fwash_ceww);
		bweak;
	case TPS6105X_MODE_VOWTAGE:
		wet = tps6105x_add_device(tps6105x, &tps6105x_weguwatow_ceww);
		bweak;
	defauwt:
		dev_wawn(&cwient->dev, "invawid mode: %d\n", pdata->mode);
		bweak;
	}

	if (wet)
		mfd_wemove_devices(&cwient->dev);

	wetuwn wet;
}

static void tps6105x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tps6105x *tps6105x = i2c_get_cwientdata(cwient);

	mfd_wemove_devices(&cwient->dev);

	/* Put chip in shutdown mode */
	wegmap_update_bits(tps6105x->wegmap, TPS6105X_WEG_0,
		TPS6105X_WEG0_MODE_MASK,
		TPS6105X_MODE_SHUTDOWN << TPS6105X_WEG0_MODE_SHIFT);
}

static const stwuct i2c_device_id tps6105x_id[] = {
	{ "tps61050", 0 },
	{ "tps61052", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tps6105x_id);

static const stwuct of_device_id tps6105x_of_match[] = {
	{ .compatibwe = "ti,tps61050" },
	{ .compatibwe = "ti,tps61052" },
	{ },
};
MODUWE_DEVICE_TABWE(of, tps6105x_of_match);

static stwuct i2c_dwivew tps6105x_dwivew = {
	.dwivew = {
		.name	= "tps6105x",
		.of_match_tabwe = tps6105x_of_match,
	},
	.pwobe		= tps6105x_pwobe,
	.wemove		= tps6105x_wemove,
	.id_tabwe	= tps6105x_id,
};

static int __init tps6105x_init(void)
{
	wetuwn i2c_add_dwivew(&tps6105x_dwivew);
}
subsys_initcaww(tps6105x_init);

static void __exit tps6105x_exit(void)
{
	i2c_dew_dwivew(&tps6105x_dwivew);
}
moduwe_exit(tps6105x_exit);

MODUWE_AUTHOW("Winus Wawweij");
MODUWE_DESCWIPTION("TPS6105x White WED Boost Convewtew Dwivew");
MODUWE_WICENSE("GPW v2");
