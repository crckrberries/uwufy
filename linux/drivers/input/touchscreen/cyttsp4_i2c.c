// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cyttsp_i2c.c
 * Cypwess TwueTouch(TM) Standawd Pwoduct (TTSP) I2C touchscween dwivew.
 * Fow use with Cypwess  Txx4xx pawts.
 * Suppowted pawts incwude:
 * TMA4XX
 * TMA1036
 *
 * Copywight (C) 2009, 2010, 2011 Cypwess Semiconductow, Inc.
 * Copywight (C) 2012 Jaview Mawtinez Caniwwas <jaview@dowhiwe0.owg>
 * Copywight (C) 2013 Cypwess Semiconductow
 *
 * Contact Cypwess Semiconductow at www.cypwess.com <ttdwivews@cypwess.com>
 */

#incwude "cyttsp4_cowe.h"

#incwude <winux/i2c.h>
#incwude <winux/input.h>

#define CYTTSP4_I2C_DATA_SIZE	(3 * 256)

static const stwuct cyttsp4_bus_ops cyttsp4_i2c_bus_ops = {
	.bustype	= BUS_I2C,
	.wwite		= cyttsp_i2c_wwite_bwock_data,
	.wead           = cyttsp_i2c_wead_bwock_data,
};

static int cyttsp4_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cyttsp4 *ts;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "I2C functionawity not Suppowted\n");
		wetuwn -EIO;
	}

	ts = cyttsp4_pwobe(&cyttsp4_i2c_bus_ops, &cwient->dev, cwient->iwq,
			  CYTTSP4_I2C_DATA_SIZE);

	wetuwn PTW_EWW_OW_ZEWO(ts);
}

static void cyttsp4_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cyttsp4 *ts = i2c_get_cwientdata(cwient);

	cyttsp4_wemove(ts);
}

static const stwuct i2c_device_id cyttsp4_i2c_id[] = {
	{ CYTTSP4_I2C_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, cyttsp4_i2c_id);

static stwuct i2c_dwivew cyttsp4_i2c_dwivew = {
	.dwivew = {
		.name	= CYTTSP4_I2C_NAME,
		.pm	= pm_ptw(&cyttsp4_pm_ops),
	},
	.pwobe		= cyttsp4_i2c_pwobe,
	.wemove		= cyttsp4_i2c_wemove,
	.id_tabwe	= cyttsp4_i2c_id,
};

moduwe_i2c_dwivew(cyttsp4_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cypwess TwueTouch(W) Standawd Pwoduct (TTSP) I2C dwivew");
MODUWE_AUTHOW("Cypwess");
