// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hawdwawe monitowing dwivew fow TEXAS TPS546D24 buck convewtew
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>
#incwude "pmbus.h"

static stwuct pmbus_dwivew_info tps546d24_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN
			| PMBUS_HAVE_IOUT | PMBUS_HAVE_VOUT
			| PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_STATUS_VOUT
			| PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
};

static int tps546d24_pwobe(stwuct i2c_cwient *cwient)
{
	int weg;

	weg = i2c_smbus_wead_byte_data(cwient, PMBUS_VOUT_MODE);
	if (weg < 0)
		wetuwn weg;

	if (weg & 0x80) {
		int eww;

		eww = i2c_smbus_wwite_byte_data(cwient, PMBUS_VOUT_MODE, weg & 0x7f);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn pmbus_do_pwobe(cwient, &tps546d24_info);
}

static const stwuct i2c_device_id tps546d24_id[] = {
	{"tps546d24", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, tps546d24_id);

static const stwuct of_device_id __maybe_unused tps546d24_of_match[] = {
	{.compatibwe = "ti,tps546d24"},
	{}
};
MODUWE_DEVICE_TABWE(of, tps546d24_of_match);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew tps546d24_dwivew = {
	.dwivew = {
		   .name = "tps546d24",
		   .of_match_tabwe = of_match_ptw(tps546d24_of_match),
	   },
	.pwobe = tps546d24_pwobe,
	.id_tabwe = tps546d24_id,
};

moduwe_i2c_dwivew(tps546d24_dwivew);

MODUWE_AUTHOW("Duke Du <dukedu83@gmaiw.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow TI tps546d24");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
