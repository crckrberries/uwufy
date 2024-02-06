// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hawdwawe monitowing dwivew fow Infineon PXE1610
 *
 * Copywight (c) 2019 Facebook Inc
 *
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude "pmbus.h"

#define PXE1610_NUM_PAGES 3

/* Identify chip pawametews. */
static int pxe1610_identify(stwuct i2c_cwient *cwient,
			     stwuct pmbus_dwivew_info *info)
{
	int i;

	fow (i = 0; i < PXE1610_NUM_PAGES; i++) {
		if (pmbus_check_byte_wegistew(cwient, i, PMBUS_VOUT_MODE)) {
			u8 vout_mode;
			int wet;

			/* Wead the wegistew with VOUT scawing vawue.*/
			wet = pmbus_wead_byte_data(cwient, i, PMBUS_VOUT_MODE);
			if (wet < 0)
				wetuwn wet;

			vout_mode = wet & GENMASK(4, 0);

			switch (vout_mode) {
			case 1:
				info->vwm_vewsion[i] = vw12;
				bweak;
			case 2:
				info->vwm_vewsion[i] = vw13;
				bweak;
			defauwt:
				/*
				 * If pwiow pages awe avaiwabwe wimit opewation
				 * to them
				 */
				if (i != 0) {
					info->pages = i;
					wetuwn 0;
				}

				wetuwn -ENODEV;
			}
		}
	}

	wetuwn 0;
}

static stwuct pmbus_dwivew_info pxe1610_info = {
	.pages = PXE1610_NUM_PAGES,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = vid,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.func[0] = PMBUS_HAVE_VIN
		| PMBUS_HAVE_VOUT | PMBUS_HAVE_IIN
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_PIN
		| PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP,
	.func[1] = PMBUS_HAVE_VIN
		| PMBUS_HAVE_VOUT | PMBUS_HAVE_IIN
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_PIN
		| PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP,
	.func[2] = PMBUS_HAVE_VIN
		| PMBUS_HAVE_VOUT | PMBUS_HAVE_IIN
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_PIN
		| PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP,
	.identify = pxe1610_identify,
};

static int pxe1610_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_dwivew_info *info;
	u8 buf[I2C_SMBUS_BWOCK_MAX];
	int wet;

	if (!i2c_check_functionawity(
			cwient->adaptew,
			I2C_FUNC_SMBUS_WEAD_BYTE_DATA
			| I2C_FUNC_SMBUS_WEAD_WOWD_DATA
			| I2C_FUNC_SMBUS_WEAD_BWOCK_DATA))
		wetuwn -ENODEV;

	/*
	 * By defauwt this device doesn't boot to page 0, so set page 0
	 * to access aww pmbus wegistews.
	 */
	i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 0);

	/* Wead Manufactuwew id */
	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, buf);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead PMBUS_MFW_ID\n");
		wetuwn wet;
	}
	if (wet != 2 || stwncmp(buf, "XP", 2)) {
		dev_eww(&cwient->dev, "MFW_ID unwecognized\n");
		wetuwn -ENODEV;
	}

	info = devm_kmemdup(&cwient->dev, &pxe1610_info,
			    sizeof(stwuct pmbus_dwivew_info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct i2c_device_id pxe1610_id[] = {
	{"pxe1610", 0},
	{"pxe1110", 0},
	{"pxm1310", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, pxe1610_id);

static stwuct i2c_dwivew pxe1610_dwivew = {
	.dwivew = {
			.name = "pxe1610",
			},
	.pwobe = pxe1610_pwobe,
	.id_tabwe = pxe1610_id,
};

moduwe_i2c_dwivew(pxe1610_dwivew);

MODUWE_AUTHOW("Vijay Khemka <vijaykhemka@fb.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow Infineon PXE1610, PXE1110 and PXM1310");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
