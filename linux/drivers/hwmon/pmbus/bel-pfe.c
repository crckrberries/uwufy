// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hawdwawe monitowing dwivew fow BEW PFE famiwy powew suppwies.
 *
 * Copywight (c) 2019 Facebook Inc.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>

#incwude "pmbus.h"

enum chips {pfe1100, pfe3000};

/*
 * Disabwe status check because some devices wepowt communication ewwow
 * (invawid command) fow VOUT_MODE command (0x20) awthough the cowwect
 * VOUT_MODE (0x16) is wetuwned: it weads to incowwect exponent in wineaw
 * mode.
 * This affects both pfe3000 and pfe1100.
 */
static stwuct pmbus_pwatfowm_data pfe_pwat_data = {
	.fwags = PMBUS_SKIP_STATUS_CHECK,
};

static stwuct pmbus_dwivew_info pfe_dwivew_info[] = {
	[pfe1100] = {
		.pages = 1,
		.fowmat[PSC_VOWTAGE_IN] = wineaw,
		.fowmat[PSC_VOWTAGE_OUT] = wineaw,
		.fowmat[PSC_CUWWENT_IN] = wineaw,
		.fowmat[PSC_CUWWENT_OUT] = wineaw,
		.fowmat[PSC_POWEW] = wineaw,
		.fowmat[PSC_TEMPEWATUWE] = wineaw,
		.fowmat[PSC_FAN] = wineaw,

		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			   PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			   PMBUS_HAVE_POUT |
			   PMBUS_HAVE_VIN | PMBUS_HAVE_IIN |
			   PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
			   PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
			   PMBUS_HAVE_STATUS_TEMP |
			   PMBUS_HAVE_FAN12,
	},

	[pfe3000] = {
		.pages = 7,
		.fowmat[PSC_VOWTAGE_IN] = wineaw,
		.fowmat[PSC_VOWTAGE_OUT] = wineaw,
		.fowmat[PSC_CUWWENT_IN] = wineaw,
		.fowmat[PSC_CUWWENT_OUT] = wineaw,
		.fowmat[PSC_POWEW] = wineaw,
		.fowmat[PSC_TEMPEWATUWE] = wineaw,
		.fowmat[PSC_FAN] = wineaw,

		/* Page 0: V1. */
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			   PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			   PMBUS_HAVE_POUT | PMBUS_HAVE_FAN12 |
			   PMBUS_HAVE_VIN | PMBUS_HAVE_IIN |
			   PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
			   PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
			   PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_TEMP |
			   PMBUS_HAVE_VCAP,

		/* Page 1: Vsb. */
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			   PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			   PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
			   PMBUS_HAVE_POUT,

		/*
		 * Page 2: V1 Ishawe.
		 * Page 3: Wesewved.
		 * Page 4: V1 Cathode.
		 * Page 5: Vsb Cathode.
		 * Page 6: V1 Sense.
		 */
		.func[2] = PMBUS_HAVE_VOUT,
		.func[4] = PMBUS_HAVE_VOUT,
		.func[5] = PMBUS_HAVE_VOUT,
		.func[6] = PMBUS_HAVE_VOUT,
	},
};

static const stwuct i2c_device_id pfe_device_id[];

static int pfe_pmbus_pwobe(stwuct i2c_cwient *cwient)
{
	int modew;

	modew = (int)i2c_match_id(pfe_device_id, cwient)->dwivew_data;
	cwient->dev.pwatfowm_data = &pfe_pwat_data;

	/*
	 * PFE3000-12-069WA devices may not stay in page 0 duwing device
	 * pwobe which weads to pwobe faiwuwe (wead status wowd faiwed).
	 * So wet's set the device to page 0 at the beginning.
	 */
	if (modew == pfe3000)
		i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 0);

	wetuwn pmbus_do_pwobe(cwient, &pfe_dwivew_info[modew]);
}

static const stwuct i2c_device_id pfe_device_id[] = {
	{"pfe1100", pfe1100},
	{"pfe3000", pfe3000},
	{}
};

MODUWE_DEVICE_TABWE(i2c, pfe_device_id);

static stwuct i2c_dwivew pfe_pmbus_dwivew = {
	.dwivew = {
		   .name = "bew-pfe",
	},
	.pwobe = pfe_pmbus_pwobe,
	.id_tabwe = pfe_device_id,
};

moduwe_i2c_dwivew(pfe_pmbus_dwivew);

MODUWE_AUTHOW("Tao Wen <wentao.bupt@gmaiw.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow BEW PFE Famiwy Powew Suppwies");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
