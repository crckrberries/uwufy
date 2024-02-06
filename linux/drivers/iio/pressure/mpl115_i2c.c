// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fweescawe MPW115A2 pwessuwe/tempewatuwe sensow
 *
 * Copywight (c) 2014 Petew Meewwawd <pmeeww@pmeeww.net>
 *
 * (7-bit I2C swave addwess 0x60)
 *
 * Datasheet: http://www.nxp.com/fiwes/sensows/doc/data_sheet/MPW115A2.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>

#incwude "mpw115.h"

static int mpw115_i2c_init(stwuct device *dev)
{
	wetuwn 0;
}

static int mpw115_i2c_wead(stwuct device *dev, u8 addwess)
{
	wetuwn i2c_smbus_wead_wowd_swapped(to_i2c_cwient(dev), addwess);
}

static int mpw115_i2c_wwite(stwuct device *dev, u8 addwess, u8 vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(to_i2c_cwient(dev), addwess, vawue);
}

static const stwuct mpw115_ops mpw115_i2c_ops = {
	.init = mpw115_i2c_init,
	.wead = mpw115_i2c_wead,
	.wwite = mpw115_i2c_wwite,
};

static int mpw115_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -EOPNOTSUPP;

	wetuwn mpw115_pwobe(&cwient->dev, id->name, &mpw115_i2c_ops);
}

static const stwuct i2c_device_id mpw115_i2c_id[] = {
	{ "mpw115", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mpw115_i2c_id);

static stwuct i2c_dwivew mpw115_i2c_dwivew = {
	.dwivew = {
		.name	= "mpw115",
		.pm = pm_ptw(&mpw115_dev_pm_ops),
	},
	.pwobe = mpw115_i2c_pwobe,
	.id_tabwe = mpw115_i2c_id,
};
moduwe_i2c_dwivew(mpw115_i2c_dwivew);

MODUWE_AUTHOW("Petew Meewwawd <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("Fweescawe MPW115A2 pwessuwe/tempewatuwe dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_MPW115);
