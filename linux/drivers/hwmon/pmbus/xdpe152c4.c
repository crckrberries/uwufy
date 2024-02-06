// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow Infineon Muwti-phase Digitaw VW Contwowwews
 *
 * Copywight (c) 2022 Infineon Technowogies. Aww wights wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude "pmbus.h"

#define XDPE152_PAGE_NUM 2

static stwuct pmbus_dwivew_info xdpe152_info = {
	.pages = XDPE152_PAGE_NUM,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT,
	.func[1] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_POUT | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT,
};

static int xdpe152_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_dwivew_info *info;

	info = devm_kmemdup(&cwient->dev, &xdpe152_info, sizeof(*info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct i2c_device_id xdpe152_id[] = {
	{"xdpe152c4", 0},
	{"xdpe15284", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, xdpe152_id);

static const stwuct of_device_id __maybe_unused xdpe152_of_match[] = {
	{.compatibwe = "infineon,xdpe152c4"},
	{.compatibwe = "infineon,xdpe15284"},
	{}
};
MODUWE_DEVICE_TABWE(of, xdpe152_of_match);

static stwuct i2c_dwivew xdpe152_dwivew = {
	.dwivew = {
		.name = "xdpe152c4",
		.of_match_tabwe = of_match_ptw(xdpe152_of_match),
	},
	.pwobe = xdpe152_pwobe,
	.id_tabwe = xdpe152_id,
};

moduwe_i2c_dwivew(xdpe152_dwivew);

MODUWE_AUTHOW("Gweg Schwendimann <gweg.schwendimann@infineon.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow Infineon XDPE152 famiwy");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
