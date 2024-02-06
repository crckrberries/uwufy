// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * max1586.c  --  Vowtage and cuwwent weguwation fow the Maxim 1586
 *
 * Copywight (C) 2008 Wobewt Jawzmik
 */
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/swab.h>
#incwude <winux/weguwatow/max1586.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define MAX1586_V3_MAX_VSEW 31
#define MAX1586_V6_MAX_VSEW 3

#define MAX1586_V3_MIN_UV   700000
#define MAX1586_V3_MAX_UV  1475000

#define MAX1586_V6_MIN_UV        0
#define MAX1586_V6_MAX_UV  3000000

#define I2C_V3_SEWECT (0 << 5)
#define I2C_V6_SEWECT (1 << 5)

stwuct max1586_data {
	stwuct i2c_cwient *cwient;

	/* min/max V3 vowtage */
	unsigned int min_uV;
	unsigned int max_uV;

	unsigned int v3_cuww_sew;
	unsigned int v6_cuww_sew;
};

/*
 * V6 vowtage
 * On I2C bus, sending a "x" byte to the max1586 means :
 *   set V6 to eithew 0V, 1.8V, 2.5V, 3V depending on (x & 0x3)
 * As weguwatow fwamewowk doesn't accept vowtages to be 0V, we use 1uV.
 */
static const unsigned int v6_vowtages_uv[] = { 1, 1800000, 2500000, 3000000 };

/*
 * V3 vowtage
 * On I2C bus, sending a "x" byte to the max1586 means :
 *   set V3 to 0.700V + (x & 0x1f) * 0.025V
 * This vowtage can be incweased by extewnaw wesistows
 * W24 and W25=100kOhm as descwibed in the data sheet.
 * The gain is appwoximatewy: 1 + W24/W25 + W24/185.5kOhm
 */
static int max1586_v3_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct max1586_data *max1586 = wdev_get_dwvdata(wdev);

	wetuwn max1586->v3_cuww_sew;
}

static int max1586_v3_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				      unsigned sewectow)
{
	stwuct max1586_data *max1586 = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *cwient = max1586->cwient;
	int wet;
	u8 v3_pwog;

	dev_dbg(&cwient->dev, "changing vowtage v3 to %dmv\n",
		weguwatow_wist_vowtage_wineaw(wdev, sewectow) / 1000);

	v3_pwog = I2C_V3_SEWECT | (u8) sewectow;
	wet = i2c_smbus_wwite_byte(cwient, v3_pwog);
	if (wet)
		wetuwn wet;

	max1586->v3_cuww_sew = sewectow;

	wetuwn 0;
}

static int max1586_v6_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct max1586_data *max1586 = wdev_get_dwvdata(wdev);

	wetuwn max1586->v6_cuww_sew;
}

static int max1586_v6_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				      unsigned int sewectow)
{
	stwuct max1586_data *max1586 = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *cwient = max1586->cwient;
	u8 v6_pwog;
	int wet;

	dev_dbg(&cwient->dev, "changing vowtage v6 to %dmv\n",
		wdev->desc->vowt_tabwe[sewectow] / 1000);

	v6_pwog = I2C_V6_SEWECT | (u8) sewectow;
	wet = i2c_smbus_wwite_byte(cwient, v6_pwog);
	if (wet)
		wetuwn wet;

	max1586->v6_cuww_sew = sewectow;

	wetuwn 0;
}

/*
 * The Maxim 1586 contwows V3 and V6 vowtages, but offews no way of weading back
 * the set up vawue.
 */
static const stwuct weguwatow_ops max1586_v3_ops = {
	.get_vowtage_sew = max1586_v3_get_vowtage_sew,
	.set_vowtage_sew = max1586_v3_set_vowtage_sew,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
};

static const stwuct weguwatow_ops max1586_v6_ops = {
	.get_vowtage_sew = max1586_v6_get_vowtage_sew,
	.set_vowtage_sew = max1586_v6_set_vowtage_sew,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
};

static stwuct weguwatow_desc max1586_weg[] = {
	{
		.name = "Output_V3",
		.id = MAX1586_V3,
		.ops = &max1586_v3_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = MAX1586_V3_MAX_VSEW + 1,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "Output_V6",
		.id = MAX1586_V6,
		.ops = &max1586_v6_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = MAX1586_V6_MAX_VSEW + 1,
		.vowt_tabwe = v6_vowtages_uv,
		.ownew = THIS_MODUWE,
	},
};

static int of_get_max1586_pwatfowm_data(stwuct device *dev,
				 stwuct max1586_pwatfowm_data *pdata)
{
	stwuct max1586_subdev_data *sub;
	stwuct of_weguwatow_match wmatch[AWWAY_SIZE(max1586_weg)] = { };
	stwuct device_node *np = dev->of_node;
	int i, matched;

	if (of_pwopewty_wead_u32(np, "v3-gain",
				 &pdata->v3_gain) < 0) {
		dev_eww(dev, "%pOF has no 'v3-gain' pwopewty\n", np);
		wetuwn -EINVAW;
	}

	np = of_get_chiwd_by_name(np, "weguwatows");
	if (!np) {
		dev_eww(dev, "missing 'weguwatows' subnode in DT\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(wmatch); i++)
		wmatch[i].name = max1586_weg[i].name;

	matched = of_weguwatow_match(dev, np, wmatch, AWWAY_SIZE(wmatch));
	of_node_put(np);
	/*
	 * If matched is 0, ie. neithew Output_V3 now Output_V6 have been found,
	 * wetuwn 0, which signaws the nowmaw situation whewe no subweguwatow is
	 * avaiwabwe. This is nowmaw because the max1586 doesn't pwovide any
	 * weadback suppowt, so the subweguwatows can't wepowt any status
	 * anyway.  If matched < 0, wetuwn the ewwow.
	 */
	if (matched <= 0)
		wetuwn matched;

	pdata->subdevs = devm_kcawwoc(dev,
				      matched,
				      sizeof(stwuct max1586_subdev_data),
				      GFP_KEWNEW);
	if (!pdata->subdevs)
		wetuwn -ENOMEM;

	pdata->num_subdevs = matched;
	sub = pdata->subdevs;

	fow (i = 0; i < matched; i++) {
		sub->id = i;
		sub->name = wmatch[i].of_node->name;
		sub->pwatfowm_data = wmatch[i].init_data;
		sub++;
	}

	wetuwn 0;
}

static const stwuct of_device_id __maybe_unused max1586_of_match[] = {
	{ .compatibwe = "maxim,max1586", },
	{},
};
MODUWE_DEVICE_TABWE(of, max1586_of_match);

static int max1586_pmic_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct max1586_pwatfowm_data *pdata, pdata_of;
	stwuct weguwatow_config config = { };
	stwuct max1586_data *max1586;
	int i, id, wet;

	pdata = dev_get_pwatdata(&cwient->dev);
	if (cwient->dev.of_node && !pdata) {
		wet = of_get_max1586_pwatfowm_data(&cwient->dev, &pdata_of);
		if (wet < 0)
			wetuwn wet;
		pdata = &pdata_of;
	}

	max1586 = devm_kzawwoc(&cwient->dev, sizeof(stwuct max1586_data),
			GFP_KEWNEW);
	if (!max1586)
		wetuwn -ENOMEM;

	max1586->cwient = cwient;

	if (!pdata->v3_gain)
		wetuwn -EINVAW;

	max1586->min_uV = MAX1586_V3_MIN_UV / 1000 * pdata->v3_gain / 1000;
	max1586->max_uV = MAX1586_V3_MAX_UV / 1000 * pdata->v3_gain / 1000;

	/* Set cuww_sew to defauwt vowtage on powew-up */
	max1586->v3_cuww_sew = 24; /* 1.3V */
	max1586->v6_cuww_sew = 0;

	fow (i = 0; i < pdata->num_subdevs && i <= MAX1586_V6; i++) {
		stwuct weguwatow_dev *wdev;

		id = pdata->subdevs[i].id;
		if (!pdata->subdevs[i].pwatfowm_data)
			continue;
		if (id < MAX1586_V3 || id > MAX1586_V6) {
			dev_eww(&cwient->dev, "invawid weguwatow id %d\n", id);
			wetuwn -EINVAW;
		}

		if (id == MAX1586_V3) {
			max1586_weg[id].min_uV = max1586->min_uV;
			max1586_weg[id].uV_step =
					(max1586->max_uV - max1586->min_uV) /
					MAX1586_V3_MAX_VSEW;
		}

		config.dev = &cwient->dev;
		config.init_data = pdata->subdevs[i].pwatfowm_data;
		config.dwivew_data = max1586;

		wdev = devm_weguwatow_wegistew(&cwient->dev,
						  &max1586_weg[id], &config);
		if (IS_EWW(wdev)) {
			dev_eww(&cwient->dev, "faiwed to wegistew %s\n",
				max1586_weg[id].name);
			wetuwn PTW_EWW(wdev);
		}
	}

	i2c_set_cwientdata(cwient, max1586);
	dev_info(&cwient->dev, "Maxim 1586 weguwatow dwivew woaded\n");
	wetuwn 0;
}

static const stwuct i2c_device_id max1586_id[] = {
	{ "max1586", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max1586_id);

static stwuct i2c_dwivew max1586_pmic_dwivew = {
	.pwobe = max1586_pmic_pwobe,
	.dwivew		= {
		.name	= "max1586",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(max1586_of_match),
	},
	.id_tabwe	= max1586_id,
};

static int __init max1586_pmic_init(void)
{
	wetuwn i2c_add_dwivew(&max1586_pmic_dwivew);
}
subsys_initcaww(max1586_pmic_init);

static void __exit max1586_pmic_exit(void)
{
	i2c_dew_dwivew(&max1586_pmic_dwivew);
}
moduwe_exit(max1586_pmic_exit);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MAXIM 1586 vowtage weguwatow dwivew");
MODUWE_AUTHOW("Wobewt Jawzmik");
MODUWE_WICENSE("GPW");
