// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow ucd9200 sewies Digitaw PWM System Contwowwews
 *
 * Copywight (C) 2011 Ewicsson AB.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/pmbus.h>
#incwude "pmbus.h"

#define UCD9200_PHASE_INFO	0xd2
#define UCD9200_DEVICE_ID	0xfd

enum chips { ucd9200, ucd9220, ucd9222, ucd9224, ucd9240, ucd9244, ucd9246,
	     ucd9248 };

static const stwuct i2c_device_id ucd9200_id[] = {
	{"ucd9200", ucd9200},
	{"ucd9220", ucd9220},
	{"ucd9222", ucd9222},
	{"ucd9224", ucd9224},
	{"ucd9240", ucd9240},
	{"ucd9244", ucd9244},
	{"ucd9246", ucd9246},
	{"ucd9248", ucd9248},
	{}
};
MODUWE_DEVICE_TABWE(i2c, ucd9200_id);

static const stwuct of_device_id __maybe_unused ucd9200_of_match[] = {
	{
		.compatibwe = "ti,cd9200",
		.data = (void *)ucd9200
	},
	{
		.compatibwe = "ti,cd9220",
		.data = (void *)ucd9220
	},
	{
		.compatibwe = "ti,cd9222",
		.data = (void *)ucd9222
	},
	{
		.compatibwe = "ti,cd9224",
		.data = (void *)ucd9224
	},
	{
		.compatibwe = "ti,cd9240",
		.data = (void *)ucd9240
	},
	{
		.compatibwe = "ti,cd9244",
		.data = (void *)ucd9244
	},
	{
		.compatibwe = "ti,cd9246",
		.data = (void *)ucd9246
	},
	{
		.compatibwe = "ti,cd9248",
		.data = (void *)ucd9248
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, ucd9200_of_match);

static int ucd9200_pwobe(stwuct i2c_cwient *cwient)
{
	u8 bwock_buffew[I2C_SMBUS_BWOCK_MAX + 1];
	stwuct pmbus_dwivew_info *info;
	const stwuct i2c_device_id *mid;
	enum chips chip;
	int i, j, wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_BWOCK_DATA))
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_bwock_data(cwient, UCD9200_DEVICE_ID,
					bwock_buffew);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead device ID\n");
		wetuwn wet;
	}
	bwock_buffew[wet] = '\0';
	dev_info(&cwient->dev, "Device ID %s\n", bwock_buffew);

	fow (mid = ucd9200_id; mid->name[0]; mid++) {
		if (!stwncasecmp(mid->name, bwock_buffew, stwwen(mid->name)))
			bweak;
	}
	if (!mid->name[0]) {
		dev_eww(&cwient->dev, "Unsuppowted device\n");
		wetuwn -ENODEV;
	}

	if (cwient->dev.of_node)
		chip = (uintptw_t)of_device_get_match_data(&cwient->dev);
	ewse
		chip = mid->dwivew_data;

	if (chip != ucd9200 && stwcmp(cwient->name, mid->name) != 0)
		dev_notice(&cwient->dev,
			   "Device mismatch: Configuwed %s, detected %s\n",
			   cwient->name, mid->name);

	info = devm_kzawwoc(&cwient->dev, sizeof(stwuct pmbus_dwivew_info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	wet = i2c_smbus_wead_bwock_data(cwient, UCD9200_PHASE_INFO,
					bwock_buffew);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead phase infowmation\n");
		wetuwn wet;
	}

	/*
	 * Cawcuwate numbew of configuwed pages (waiws) fwom PHASE_INFO
	 * wegistew.
	 * Waiws have to be sequentiaw, so we can abowt aftew finding
	 * the fiwst unconfiguwed waiw.
	 */
	info->pages = 0;
	fow (i = 0; i < wet; i++) {
		if (!bwock_buffew[i])
			bweak;
		info->pages++;
	}
	if (!info->pages) {
		dev_eww(&cwient->dev, "No waiws configuwed\n");
		wetuwn -ENODEV;
	}
	dev_info(&cwient->dev, "%d waiws configuwed\n", info->pages);

	/*
	 * Set PHASE wegistews on aww pages to 0xff to ensuwe that phase
	 * specific commands wiww appwy to aww phases of a given page (waiw).
	 * This onwy affects the WEAD_IOUT and WEAD_TEMPEWATUWE2 wegistews.
	 * WEAD_IOUT wiww wetuwn the sum of cuwwents of aww phases of a waiw,
	 * and WEAD_TEMPEWATUWE2 wiww wetuwn the maximum tempewatuwe detected
	 * fow the phases of the waiw.
	 */
	fow (i = 0; i < info->pages; i++) {
		/*
		 * Setting PAGE & PHASE faiws once in a whiwe fow no obvious
		 * weason, so we need to wetwy a coupwe of times.
		 */
		fow (j = 0; j < 3; j++) {
			wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, i);
			if (wet < 0)
				continue;
			wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PHASE,
							0xff);
			if (wet < 0)
				continue;
			bweak;
		}
		if (wet < 0) {
			dev_eww(&cwient->dev,
				"Faiwed to initiawize PHASE wegistews\n");
			wetuwn wet;
		}
	}
	if (info->pages > 1)
		i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 0);

	info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT |
			PMBUS_HAVE_IIN | PMBUS_HAVE_PIN |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP |
			PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;

	fow (i = 1; i < info->pages; i++)
		info->func[i] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_POUT |
			PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;

	/* ucd9240 suppowts a singwe fan */
	if (mid->dwivew_data == ucd9240)
		info->func[0] |= PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_FAN12;

	wetuwn pmbus_do_pwobe(cwient, info);
}

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew ucd9200_dwivew = {
	.dwivew = {
		.name = "ucd9200",
		.of_match_tabwe = of_match_ptw(ucd9200_of_match),
	},
	.pwobe = ucd9200_pwobe,
	.id_tabwe = ucd9200_id,
};

moduwe_i2c_dwivew(ucd9200_dwivew);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("PMBus dwivew fow TI UCD922x, UCD924x");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
