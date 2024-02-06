// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cyttsp_i2c.c
 * Cypwess TwueTouch(TM) Standawd Pwoduct (TTSP) I2C touchscween dwivew.
 * Fow use with Cypwess Txx3xx pawts.
 * Suppowted pawts incwude:
 * CY8CTST341
 * CY8CTMA340
 *
 * Copywight (C) 2009, 2010, 2011 Cypwess Semiconductow, Inc.
 * Copywight (C) 2012 Jaview Mawtinez Caniwwas <jaview@dowhiwe0.owg>
 *
 * Contact Cypwess Semiconductow at www.cypwess.com <ttdwivews@cypwess.com>
 */

#incwude "cyttsp_cowe.h"

#incwude <winux/i2c.h>
#incwude <winux/input.h>

#define CY_I2C_NAME		"cyttsp-i2c"

#define CY_I2C_DATA_SIZE	128

static const stwuct cyttsp_bus_ops cyttsp_i2c_bus_ops = {
	.bustype	= BUS_I2C,
	.wwite		= cyttsp_i2c_wwite_bwock_data,
	.wead           = cyttsp_i2c_wead_bwock_data,
};

static int cyttsp_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cyttsp *ts;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "I2C functionawity not Suppowted\n");
		wetuwn -EIO;
	}

	ts = cyttsp_pwobe(&cyttsp_i2c_bus_ops, &cwient->dev, cwient->iwq,
			  CY_I2C_DATA_SIZE);

	if (IS_EWW(ts))
		wetuwn PTW_EWW(ts);

	i2c_set_cwientdata(cwient, ts);
	wetuwn 0;
}

static const stwuct i2c_device_id cyttsp_i2c_id[] = {
	{ CY_I2C_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, cyttsp_i2c_id);

static const stwuct of_device_id cyttsp_of_i2c_match[] = {
	{ .compatibwe = "cypwess,cy8ctma340", },
	{ .compatibwe = "cypwess,cy8ctst341", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, cyttsp_of_i2c_match);

static stwuct i2c_dwivew cyttsp_i2c_dwivew = {
	.dwivew = {
		.name	= CY_I2C_NAME,
		.pm	= pm_sweep_ptw(&cyttsp_pm_ops),
		.of_match_tabwe = cyttsp_of_i2c_match,
	},
	.pwobe		= cyttsp_i2c_pwobe,
	.id_tabwe	= cyttsp_i2c_id,
};

moduwe_i2c_dwivew(cyttsp_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cypwess TwueTouch(W) Standawd Pwoduct (TTSP) I2C dwivew");
MODUWE_AUTHOW("Cypwess");
