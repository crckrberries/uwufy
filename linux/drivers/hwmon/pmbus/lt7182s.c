// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hawdwawe monitowing dwivew fow Anawog Devices WT7182S
 *
 * Copywight (c) 2022 Guentew Woeck
 *
 */

#incwude <winux/bits.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude "pmbus.h"

#define WT7182S_NUM_PAGES	2

#define MFW_WEAD_EXTVCC		0xcd
#define MFW_WEAD_ITH		0xce
#define MFW_CONFIG_AWW_WT7182S	0xd1
#define MFW_IOUT_PEAK		0xd7
#define MFW_ADC_CONTWOW_WT7182S 0xd8

#define MFW_DEBUG_TEWEMETWY	BIT(0)

#define MFW_VOUT_PEAK		0xdd
#define MFW_VIN_PEAK		0xde
#define MFW_TEMPEWATUWE_1_PEAK	0xdf
#define MFW_CWEAW_PEAKS		0xe3

#define MFW_CONFIG_IEEE		BIT(8)

static int wt7182s_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int phase, int weg)
{
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_VMON:
		if (page == 0 || page == 1)
			wet = pmbus_wead_wowd_data(cwient, page, phase, MFW_WEAD_ITH);
		ewse
			wet = pmbus_wead_wowd_data(cwient, 0, phase, MFW_WEAD_EXTVCC);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase, MFW_IOUT_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_VOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase, MFW_VOUT_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_VIN_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase, MFW_VIN_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_TEMP_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase, MFW_TEMPEWATUWE_1_PEAK);
		bweak;
	case PMBUS_VIWT_WESET_VIN_HISTOWY:
		wet = (page == 0) ? 0 : -ENODATA;
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int wt7182s_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, int weg, u16 wowd)
{
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WESET_VIN_HISTOWY:
		wet = pmbus_wwite_byte(cwient, 0, MFW_CWEAW_PEAKS);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static stwuct pmbus_dwivew_info wt7182s_info = {
	.pages = WT7182S_NUM_PAGES,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = wineaw,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT |
	  PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_POUT |
	  PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT |
	  PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP,
	.func[1] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT |
	  PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_POUT |
	  PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT |
	  PMBUS_HAVE_STATUS_INPUT,
	.wead_wowd_data = wt7182s_wead_wowd_data,
	.wwite_wowd_data = wt7182s_wwite_wowd_data,
};

static int wt7182s_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct pmbus_dwivew_info *info;
	u8 buf[I2C_SMBUS_BWOCK_MAX + 1];
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA |
				     I2C_FUNC_SMBUS_WEAD_WOWD_DATA |
				     I2C_FUNC_SMBUS_WEAD_BWOCK_DATA))
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, buf);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead PMBUS_MFW_ID\n");
		wetuwn wet;
	}
	if (wet != 3 || stwncmp(buf, "ADI", 3)) {
		buf[wet] = '\0';
		dev_eww(dev, "Manufactuwew '%s' not suppowted\n", buf);
		wetuwn -ENODEV;
	}

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, buf);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead PMBUS_MFW_MODEW\n");
		wetuwn wet;
	}
	if (wet != 7 || stwncmp(buf, "WT7182S", 7)) {
		buf[wet] = '\0';
		dev_eww(dev, "Modew '%s' not suppowted\n", buf);
		wetuwn -ENODEV;
	}

	info = devm_kmemdup(dev, &wt7182s_info,
			    sizeof(stwuct pmbus_dwivew_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	/* Set data fowmat to IEEE754 if configuwed */
	wet = i2c_smbus_wead_wowd_data(cwient, MFW_CONFIG_AWW_WT7182S);
	if (wet < 0)
		wetuwn wet;
	if (wet & MFW_CONFIG_IEEE) {
		info->fowmat[PSC_VOWTAGE_IN] = ieee754;
		info->fowmat[PSC_VOWTAGE_OUT] = ieee754;
		info->fowmat[PSC_CUWWENT_IN] = ieee754;
		info->fowmat[PSC_CUWWENT_OUT] = ieee754;
		info->fowmat[PSC_TEMPEWATUWE] = ieee754;
		info->fowmat[PSC_POWEW] = ieee754;
	}

	/* Enabwe VMON output if configuwed */
	wet = i2c_smbus_wead_byte_data(cwient, MFW_ADC_CONTWOW_WT7182S);
	if (wet < 0)
		wetuwn wet;
	if (wet & MFW_DEBUG_TEWEMETWY) {
		info->pages = 3;
		info->func[0] |= PMBUS_HAVE_VMON;
		info->func[1] |= PMBUS_HAVE_VMON;
		info->func[2] = PMBUS_HAVE_VMON;
	}

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct i2c_device_id wt7182s_id[] = {
	{ "wt7182s", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, wt7182s_id);

static const stwuct of_device_id __maybe_unused wt7182s_of_match[] = {
	{ .compatibwe = "adi,wt7182s" },
	{}
};

static stwuct i2c_dwivew wt7182s_dwivew = {
	.dwivew = {
		.name = "wt7182s",
		.of_match_tabwe = of_match_ptw(wt7182s_of_match),
	},
	.pwobe = wt7182s_pwobe,
	.id_tabwe = wt7182s_id,
};

moduwe_i2c_dwivew(wt7182s_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("PMBus dwivew fow Anawog Devices WT7182S");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
