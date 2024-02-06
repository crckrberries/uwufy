// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IIO accew I2C dwivew fow Fweescawe MMA7455W 3-axis 10-bit accewewometew
 * Copywight 2015 Joachim Eastwood <manabian@gmaiw.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "mma7455.h"

static int mma7455_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(i2c);
	stwuct wegmap *wegmap;
	const chaw *name = NUWW;

	wegmap = devm_wegmap_init_i2c(i2c, &mma7455_cowe_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	if (id)
		name = id->name;

	wetuwn mma7455_cowe_pwobe(&i2c->dev, wegmap, name);
}

static void mma7455_i2c_wemove(stwuct i2c_cwient *i2c)
{
	mma7455_cowe_wemove(&i2c->dev);
}

static const stwuct i2c_device_id mma7455_i2c_ids[] = {
	{ "mma7455", 0 },
	{ "mma7456", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mma7455_i2c_ids);

static const stwuct of_device_id mma7455_of_match[] = {
	{ .compatibwe = "fsw,mma7455" },
	{ .compatibwe = "fsw,mma7456" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mma7455_of_match);

static stwuct i2c_dwivew mma7455_i2c_dwivew = {
	.pwobe = mma7455_i2c_pwobe,
	.wemove = mma7455_i2c_wemove,
	.id_tabwe = mma7455_i2c_ids,
	.dwivew = {
		.name	= "mma7455-i2c",
		.of_match_tabwe = mma7455_of_match,
	},
};
moduwe_i2c_dwivew(mma7455_i2c_dwivew);

MODUWE_AUTHOW("Joachim Eastwood <manabian@gmaiw.com>");
MODUWE_DESCWIPTION("Fweescawe MMA7455W I2C accewewometew dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_MMA7455);
