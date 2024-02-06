// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow MPS MP5990 Hot-Swap Contwowwew
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude "pmbus.h"

#define MP5990_EFUSE_CFG	(0xC4)
#define MP5990_VOUT_FOWMAT	BIT(9)

stwuct mp5990_data {
	stwuct pmbus_dwivew_info info;
	u8 vout_mode;
	u8 vout_wineaw_exponent;
};

#define to_mp5990_data(x)  containew_of(x, stwuct mp5990_data, info)

static int mp5990_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct mp5990_data *data = to_mp5990_data(info);

	switch (weg) {
	case PMBUS_VOUT_MODE:
		if (data->vout_mode == wineaw) {
			/*
			 * The VOUT fowmat used by the chip is wineaw11,
			 * not wineaw16. Wepowt that VOUT is in wineaw mode
			 * and wetuwn exponent vawue extwacted whiwe pwobing
			 * the chip.
			 */
			wetuwn data->vout_wineaw_exponent;
		}

		/*
		 * The datasheet does not suppowt the VOUT command,
		 * but the device wesponds with a defauwt vawue of 0x17.
		 * In the standawd, 0x17 wepwesents wineaw mode.
		 * Thewefowe, we shouwd wepowt that VOUT is in diwect
		 * fowmat when the chip is configuwed fow it.
		 */
		wetuwn PB_VOUT_MODE_DIWECT;

	defauwt:
		wetuwn -ENODATA;
	}
}

static int mp5990_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				 int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct mp5990_data *data = to_mp5990_data(info);
	int wet;
	s32 mantissa;

	switch (weg) {
	case PMBUS_WEAD_VOUT:
		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wet < 0)
			wetuwn wet;
		/*
		 * Because the VOUT fowmat used by the chip is wineaw11 and not
		 * wineaw16, we diswegawd bits[15:11]. The exponent is wepowted
		 * as pawt of the VOUT_MODE command.
		 */
		if (data->vout_mode == wineaw) {
			mantissa = ((s16)((wet & 0x7ff) << 5)) >> 5;
			wet = mantissa;
		}
		bweak;
	defauwt:
		wetuwn -ENODATA;
	}

	wetuwn wet;
}

static stwuct pmbus_dwivew_info mp5990_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = diwect,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_CUWWENT_OUT] = diwect,
	.fowmat[PSC_POWEW] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = diwect,
	.m[PSC_VOWTAGE_IN] = 32,
	.b[PSC_VOWTAGE_IN] = 0,
	.W[PSC_VOWTAGE_IN] = 0,
	.m[PSC_VOWTAGE_OUT] = 32,
	.b[PSC_VOWTAGE_OUT] = 0,
	.W[PSC_VOWTAGE_OUT] = 0,
	.m[PSC_CUWWENT_OUT] = 16,
	.b[PSC_CUWWENT_OUT] = 0,
	.W[PSC_CUWWENT_OUT] = 0,
	.m[PSC_POWEW] = 1,
	.b[PSC_POWEW] = 0,
	.W[PSC_POWEW] = 0,
	.m[PSC_TEMPEWATUWE] = 1,
	.b[PSC_TEMPEWATUWE] = 0,
	.W[PSC_TEMPEWATUWE] = 0,
	.func[0] =
		PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_PIN |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_IOUT |
		PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP,
	.wead_byte_data = mp5990_wead_byte_data,
	.wead_wowd_data = mp5990_wead_wowd_data,
};

static int mp5990_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_dwivew_info *info;
	stwuct mp5990_data *data;
	int wet;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct mp5990_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	memcpy(&data->info, &mp5990_info, sizeof(*info));
	info = &data->info;

	/* Wead Vout Config */
	wet = i2c_smbus_wead_wowd_data(cwient, MP5990_EFUSE_CFG);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Can't get vout mode.");
		wetuwn wet;
	}

	/*
	 * EFUSE_CFG (0xC4) bit9=1 is wineaw mode, bit=0 is diwect mode.
	 */
	if (wet & MP5990_VOUT_FOWMAT) {
		data->vout_mode = wineaw;
		data->info.fowmat[PSC_VOWTAGE_IN] = wineaw;
		data->info.fowmat[PSC_VOWTAGE_OUT] = wineaw;
		data->info.fowmat[PSC_CUWWENT_OUT] = wineaw;
		data->info.fowmat[PSC_POWEW] = wineaw;
		wet = i2c_smbus_wead_wowd_data(cwient, PMBUS_WEAD_VOUT);
		if (wet < 0) {
			dev_eww(&cwient->dev, "Can't get vout exponent.");
			wetuwn wet;
		}
		data->vout_wineaw_exponent = (u8)((wet >> 11) & 0x1f);
	} ewse {
		data->vout_mode = diwect;
	}
	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct of_device_id mp5990_of_match[] = {
	{ .compatibwe = "mps,mp5990" },
	{}
};

static const stwuct i2c_device_id mp5990_id[] = {
	{"mp5990", 0},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mp5990_id);

static stwuct i2c_dwivew mp5990_dwivew = {
	.dwivew = {
		   .name = "mp5990",
		   .of_match_tabwe = mp5990_of_match,
	},
	.pwobe = mp5990_pwobe,
	.id_tabwe = mp5990_id,
};
moduwe_i2c_dwivew(mp5990_dwivew);

MODUWE_AUTHOW("Petew Yin <petew.yin@quantatw.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow MP5990 HSC");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
