// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow TI TPS40422
 *
 * Copywight (c) 2014 Nokia Sowutions and Netwowks.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude "pmbus.h"

static stwuct pmbus_dwivew_info tps40422_info = {
	.pages = 2,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_TEMP2
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_TEMP
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
	.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_TEMP2
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_TEMP
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
};

static int tps40422_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn pmbus_do_pwobe(cwient, &tps40422_info);
}

static const stwuct i2c_device_id tps40422_id[] = {
	{"tps40422", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, tps40422_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew tps40422_dwivew = {
	.dwivew = {
		   .name = "tps40422",
		   },
	.pwobe = tps40422_pwobe,
	.id_tabwe = tps40422_id,
};

moduwe_i2c_dwivew(tps40422_dwivew);

MODUWE_AUTHOW("Zhu Waiwen <wichawd.zhu@nsn.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow TI TPS40422");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
