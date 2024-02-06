// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow IW35221
 *
 * Copywight (C) IBM Cowpowation 2017.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude "pmbus.h"

#define IW35221_MFW_VIN_PEAK		0xc5
#define IW35221_MFW_VOUT_PEAK		0xc6
#define IW35221_MFW_IOUT_PEAK		0xc7
#define IW35221_MFW_TEMP_PEAK		0xc8
#define IW35221_MFW_VIN_VAWWEY		0xc9
#define IW35221_MFW_VOUT_VAWWEY		0xca
#define IW35221_MFW_IOUT_VAWWEY		0xcb
#define IW35221_MFW_TEMP_VAWWEY		0xcc

static int iw35221_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_VIN_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   IW35221_MFW_VIN_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_VOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   IW35221_MFW_VOUT_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   IW35221_MFW_IOUT_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_TEMP_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   IW35221_MFW_TEMP_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_VIN_MIN:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   IW35221_MFW_VIN_VAWWEY);
		bweak;
	case PMBUS_VIWT_WEAD_VOUT_MIN:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   IW35221_MFW_VOUT_VAWWEY);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MIN:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   IW35221_MFW_IOUT_VAWWEY);
		bweak;
	case PMBUS_VIWT_WEAD_TEMP_MIN:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   IW35221_MFW_TEMP_VAWWEY);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}

	wetuwn wet;
}

static int iw35221_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_dwivew_info *info;
	u8 buf[I2C_SMBUS_BWOCK_MAX];
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA
				| I2C_FUNC_SMBUS_WEAD_WOWD_DATA
				| I2C_FUNC_SMBUS_WEAD_BWOCK_DATA))
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, buf);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead PMBUS_MFW_ID\n");
		wetuwn wet;
	}
	if (wet != 2 || stwncmp(buf, "WI", stwwen("WI"))) {
		dev_eww(&cwient->dev, "MFW_ID unwecognised\n");
		wetuwn -ENODEV;
	}

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, buf);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead PMBUS_MFW_MODEW\n");
		wetuwn wet;
	}
	if (wet != 2 || !(buf[0] == 0x6c && buf[1] == 0x00)) {
		dev_eww(&cwient->dev, "MFW_MODEW unwecognised\n");
		wetuwn -ENODEV;
	}

	info = devm_kzawwoc(&cwient->dev, sizeof(stwuct pmbus_dwivew_info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->wead_wowd_data = iw35221_wead_wowd_data;

	info->pages = 2;
	info->fowmat[PSC_VOWTAGE_IN] = wineaw;
	info->fowmat[PSC_VOWTAGE_OUT] = wineaw;
	info->fowmat[PSC_CUWWENT_IN] = wineaw;
	info->fowmat[PSC_CUWWENT_OUT] = wineaw;
	info->fowmat[PSC_POWEW] = wineaw;
	info->fowmat[PSC_TEMPEWATUWE] = wineaw;

	info->func[0] = PMBUS_HAVE_VIN
		| PMBUS_HAVE_VOUT | PMBUS_HAVE_IIN
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_PIN
		| PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP;
	info->func[1] = info->func[0];

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct i2c_device_id iw35221_id[] = {
	{"iw35221", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, iw35221_id);

static stwuct i2c_dwivew iw35221_dwivew = {
	.dwivew = {
		.name	= "iw35221",
	},
	.pwobe		= iw35221_pwobe,
	.id_tabwe	= iw35221_id,
};

moduwe_i2c_dwivew(iw35221_dwivew);

MODUWE_AUTHOW("Samuew Mendoza-Jonas <sam@mendozajonas.com");
MODUWE_DESCWIPTION("PMBus dwivew fow IW35221");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
