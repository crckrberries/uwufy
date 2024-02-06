// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AD7879-1/AD7889-1 touchscween (I2C bus)
 *
 * Copywight (C) 2008-2010 Michaew Hennewich, Anawog Devices Inc.
 */

#incwude <winux/input.h>	/* BUS_I2C */
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>

#incwude "ad7879.h"

#define AD7879_DEVID		0x79	/* AD7879-1/AD7889-1 */

static const stwuct wegmap_config ad7879_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = 15,
};

static int ad7879_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WOWD_DATA)) {
		dev_eww(&cwient->dev, "SMBUS Wowd Data not Suppowted\n");
		wetuwn -EIO;
	}

	wegmap = devm_wegmap_init_i2c(cwient, &ad7879_i2c_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn ad7879_pwobe(&cwient->dev, wegmap, cwient->iwq,
			    BUS_I2C, AD7879_DEVID);
}

static const stwuct i2c_device_id ad7879_id[] = {
	{ "ad7879", 0 },
	{ "ad7889", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ad7879_id);

#ifdef CONFIG_OF
static const stwuct of_device_id ad7879_i2c_dt_ids[] = {
	{ .compatibwe = "adi,ad7879-1", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad7879_i2c_dt_ids);
#endif

static stwuct i2c_dwivew ad7879_i2c_dwivew = {
	.dwivew = {
		.name		= "ad7879",
		.dev_gwoups	= ad7879_gwoups,
		.pm		= &ad7879_pm_ops,
		.of_match_tabwe	= of_match_ptw(ad7879_i2c_dt_ids),
	},
	.pwobe		= ad7879_i2c_pwobe,
	.id_tabwe	= ad7879_id,
};

moduwe_i2c_dwivew(ad7879_i2c_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("AD7879(-1) touchscween I2C bus dwivew");
MODUWE_WICENSE("GPW");
