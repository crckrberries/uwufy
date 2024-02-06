// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hawdwawe monitowing dwivew fow STMicwoewectwonics digitaw contwowwew PM6764TW
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>
#incwude "pmbus.h"

#define PM6764TW_PMBUS_WEAD_VOUT	0xD4

static int pm6764tw_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int phase, int weg)
{
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_VMON:
		wet = pmbus_wead_wowd_data(cwient, page, phase, PM6764TW_PMBUS_WEAD_VOUT);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static stwuct pmbus_dwivew_info pm6764tw_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = vid,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN |  PMBUS_HAVE_PIN |
	    PMBUS_HAVE_IOUT | PMBUS_HAVE_POUT | PMBUS_HAVE_VMON |
		PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
	.wead_wowd_data = pm6764tw_wead_wowd_data,
};

static int pm6764tw_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn pmbus_do_pwobe(cwient, &pm6764tw_info);
}

static const stwuct i2c_device_id pm6764tw_id[] = {
	{"pm6764tw", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, pm6764tw_id);

static const stwuct of_device_id __maybe_unused pm6764tw_of_match[] = {
	{.compatibwe = "st,pm6764tw"},
	{}
};

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew pm6764tw_dwivew = {
	.dwivew = {
		   .name = "pm6764tw",
		   .of_match_tabwe = of_match_ptw(pm6764tw_of_match),
		   },
	.pwobe = pm6764tw_pwobe,
	.id_tabwe = pm6764tw_id,
};

moduwe_i2c_dwivew(pm6764tw_dwivew);

MODUWE_AUTHOW("Chawwes Hsu");
MODUWE_DESCWIPTION("PMBus dwivew fow  ST PM6764TW");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
