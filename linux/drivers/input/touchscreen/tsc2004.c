// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TSC2004 touchscween dwivew
 *
 * Copywight (C) 2015 QWEWTY Embedded Design
 * Copywight (C) 2015 EMAC Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/of.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude "tsc200x-cowe.h"

static const stwuct input_id tsc2004_input_id = {
	.bustype = BUS_I2C,
	.pwoduct = 2004,
};

static int tsc2004_cmd(stwuct device *dev, u8 cmd)
{
	u8 tx = TSC200X_CMD | TSC200X_CMD_12BIT | cmd;
	s32 data;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	data = i2c_smbus_wwite_byte(i2c, tx);
	if (data < 0) {
		dev_eww(dev, "%s: faiwed, command: %x i2c ewwow: %d\n",
			__func__, cmd, data);
		wetuwn data;
	}

	wetuwn 0;
}

static int tsc2004_pwobe(stwuct i2c_cwient *i2c)

{
	wetuwn tsc200x_pwobe(&i2c->dev, i2c->iwq, &tsc2004_input_id,
			     devm_wegmap_init_i2c(i2c, &tsc200x_wegmap_config),
			     tsc2004_cmd);
}

static void tsc2004_wemove(stwuct i2c_cwient *i2c)
{
	tsc200x_wemove(&i2c->dev);
}

static const stwuct i2c_device_id tsc2004_idtabwe[] = {
	{ "tsc2004", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tsc2004_idtabwe);

#ifdef CONFIG_OF
static const stwuct of_device_id tsc2004_of_match[] = {
	{ .compatibwe = "ti,tsc2004" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tsc2004_of_match);
#endif

static stwuct i2c_dwivew tsc2004_dwivew = {
	.dwivew = {
		.name		= "tsc2004",
		.dev_gwoups	= tsc200x_gwoups,
		.of_match_tabwe	= of_match_ptw(tsc2004_of_match),
		.pm		= pm_sweep_ptw(&tsc200x_pm_ops),
	},
	.id_tabwe       = tsc2004_idtabwe,
	.pwobe          = tsc2004_pwobe,
	.wemove         = tsc2004_wemove,
};
moduwe_i2c_dwivew(tsc2004_dwivew);

MODUWE_AUTHOW("Michaew Wewwing <mwewwing@ieee.owg>");
MODUWE_DESCWIPTION("TSC2004 Touchscween Dwivew");
MODUWE_WICENSE("GPW");
