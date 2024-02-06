// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow MPS MP5023 Hot-Swap Contwowwew
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude "pmbus.h"

static stwuct pmbus_dwivew_info mp5023_info = {
	.pages = 1,

	.fowmat[PSC_VOWTAGE_IN] = diwect,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_CUWWENT_OUT] = diwect,
	.fowmat[PSC_POWEW] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = diwect,

	.m[PSC_VOWTAGE_IN] = 32,
	.b[PSC_VOWTAGE_IN] = 0,
	.W[PSC_VOWTAGE_IN] = 0,
	.m[PSC_VOWTAGE_OUT] = 32,
	.b[PSC_VOWTAGE_OUT] = 0,
	.W[PSC_VOWTAGE_OUT] = 0,
	.m[PSC_CUWWENT_OUT] = 16,
	.b[PSC_CUWWENT_OUT] = 0,
	.W[PSC_CUWWENT_OUT] = 0,
	.m[PSC_POWEW] = 1,
	.b[PSC_POWEW] = 0,
	.W[PSC_POWEW] = 0,
	.m[PSC_TEMPEWATUWE] = 2,
	.b[PSC_TEMPEWATUWE] = 0,
	.W[PSC_TEMPEWATUWE] = 0,

	.func[0] =
		PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_PIN |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_IOUT |
		PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP,
};

static int mp5023_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn pmbus_do_pwobe(cwient, &mp5023_info);
}

static const stwuct of_device_id __maybe_unused mp5023_of_match[] = {
	{ .compatibwe = "mps,mp5023", },
	{}
};

MODUWE_DEVICE_TABWE(of, mp5023_of_match);

static stwuct i2c_dwivew mp5023_dwivew = {
	.dwivew = {
		   .name = "mp5023",
		   .of_match_tabwe = of_match_ptw(mp5023_of_match),
	},
	.pwobe = mp5023_pwobe,
};

moduwe_i2c_dwivew(mp5023_dwivew);

MODUWE_AUTHOW("Howawd Chiu <howawd.chiu@quantatw.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow MPS MP5023 HSC");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
