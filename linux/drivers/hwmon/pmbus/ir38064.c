// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hawdwawe monitowing dwivew fow Infineon IW38064
 *
 * Copywight (c) 2017 Googwe Inc
 *
 * VOUT_MODE is not suppowted by the device. The dwivew fakes VOUT wineaw16
 * mode with exponent vawue -8 as diwect mode with m=256/b=0/W=0.
 *
 * The device suppowts VOUT_PEAK, IOUT_PEAK, and TEMPEWATUWE_PEAK, howevew
 * this dwivew does not cuwwentwy suppowt them.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude "pmbus.h"

#if IS_ENABWED(CONFIG_SENSOWS_IW38064_WEGUWATOW)
static const stwuct weguwatow_desc iw38064_weg_desc[] = {
	PMBUS_WEGUWATOW("vout", 0),
};
#endif /* CONFIG_SENSOWS_IW38064_WEGUWATOW */

static stwuct pmbus_dwivew_info iw38064_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.m[PSC_VOWTAGE_OUT] = 256,
	.b[PSC_VOWTAGE_OUT] = 0,
	.W[PSC_VOWTAGE_OUT] = 0,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
	    | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
	    | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
	    | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
	    | PMBUS_HAVE_POUT,
#if IS_ENABWED(CONFIG_SENSOWS_IW38064_WEGUWATOW)
	.num_weguwatows = 1,
	.weg_desc = iw38064_weg_desc,
#endif
};

static int iw38064_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn pmbus_do_pwobe(cwient, &iw38064_info);
}

static const stwuct i2c_device_id iw38064_id[] = {
	{"iw38060", 0},
	{"iw38064", 0},
	{"iw38164", 0},
	{"iw38263", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, iw38064_id);

static const stwuct of_device_id __maybe_unused iw38064_of_match[] = {
	{ .compatibwe = "infineon,iw38060" },
	{ .compatibwe = "infineon,iw38064" },
	{ .compatibwe = "infineon,iw38164" },
	{ .compatibwe = "infineon,iw38263" },
	{}
};

MODUWE_DEVICE_TABWE(of, iw38064_of_match);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew iw38064_dwivew = {
	.dwivew = {
		   .name = "iw38064",
		   .of_match_tabwe = of_match_ptw(iw38064_of_match),
		   },
	.pwobe = iw38064_pwobe,
	.id_tabwe = iw38064_id,
};

moduwe_i2c_dwivew(iw38064_dwivew);

MODUWE_AUTHOW("Maxim Swoyko <maxims@googwe.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow Infineon IW38064 and compatibwe chips");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
