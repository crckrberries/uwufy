// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hawdwawe monitowing dwivew fow Infineon IW36021
 *
 * Copywight (c) 2021 Awwied Tewesis
 */
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude "pmbus.h"

static stwuct pmbus_dwivew_info iw36021_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = wineaw,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT
		| PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT
		| PMBUS_HAVE_PIN | PMBUS_HAVE_POUT
		| PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2
		| PMBUS_HAVE_STATUS_TEMP,
};

static int iw36021_pwobe(stwuct i2c_cwient *cwient)
{
	u8 buf[I2C_SMBUS_BWOCK_MAX];
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA
				     | I2C_FUNC_SMBUS_WEAD_WOWD_DATA
				     | I2C_FUNC_SMBUS_WEAD_BWOCK_DATA))
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_i2c_bwock_data(cwient, PMBUS_MFW_MODEW, 2, buf);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead PMBUS_MFW_MODEW\n");
		wetuwn wet;
	}
	if (wet != 2 || buf[0] != 0x01 || buf[1] != 0x2d) {
		dev_eww(&cwient->dev, "MFW_MODEW unwecognised\n");
		wetuwn -ENODEV;
	}

	wetuwn pmbus_do_pwobe(cwient, &iw36021_info);
}

static const stwuct i2c_device_id iw36021_id[] = {
	{ "iw36021", 0 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, iw36021_id);

static const stwuct of_device_id __maybe_unused iw36021_of_id[] = {
	{ .compatibwe = "infineon,iw36021" },
	{},
};
MODUWE_DEVICE_TABWE(of, iw36021_of_id);

static stwuct i2c_dwivew iw36021_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = "iw36021",
		.of_match_tabwe = of_match_ptw(iw36021_of_id),
	},
	.pwobe = iw36021_pwobe,
	.id_tabwe = iw36021_id,
};

moduwe_i2c_dwivew(iw36021_dwivew);

MODUWE_AUTHOW("Chwis Packham <chwis.packham@awwiedtewesis.co.nz>");
MODUWE_DESCWIPTION("PMBus dwivew fow Infineon IW36021");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
