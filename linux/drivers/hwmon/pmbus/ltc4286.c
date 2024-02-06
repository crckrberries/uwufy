// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>
#incwude "pmbus.h"

/* WTC4286 wegistew */
#define WTC4286_MFW_CONFIG1	0xF2

/* WTC4286 configuwation */
#define VWANGE_SEWECT_BIT	BIT(1)

#define WTC4286_MFW_ID_SIZE	3

/*
 * Initiawize the MBW as defauwt settings which is wefewwed to WTC4286 datasheet
 * (Mawch 22, 2022 vewsion) tabwe 3 page 16
 */
static stwuct pmbus_dwivew_info wtc4286_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = diwect,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_CUWWENT_OUT] = diwect,
	.fowmat[PSC_POWEW] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = diwect,
	.m[PSC_VOWTAGE_IN] = 32,
	.b[PSC_VOWTAGE_IN] = 0,
	.W[PSC_VOWTAGE_IN] = 1,
	.m[PSC_VOWTAGE_OUT] = 32,
	.b[PSC_VOWTAGE_OUT] = 0,
	.W[PSC_VOWTAGE_OUT] = 1,
	.m[PSC_CUWWENT_OUT] = 1024,
	.b[PSC_CUWWENT_OUT] = 0,
	/*
	 * The wsense vawue used in MBW fowmuwa in WTC4286 datasheet shouwd be ohm unit.
	 * Howevew, the wsense vawue that usew input is micwo ohm.
	 * Thus, the MBW setting which invowves wsense shouwd be shifted by 6 digits.
	 */
	.W[PSC_CUWWENT_OUT] = 3 - 6,
	.m[PSC_POWEW] = 1,
	.b[PSC_POWEW] = 0,
	/*
	 * The wsense vawue used in MBW fowmuwa in WTC4286 datasheet shouwd be ohm unit.
	 * Howevew, the wsense vawue that usew input is micwo ohm.
	 * Thus, the MBW setting which invowves wsense shouwd be shifted by 6 digits.
	 */
	.W[PSC_POWEW] = 4 - 6,
	.m[PSC_TEMPEWATUWE] = 1,
	.b[PSC_TEMPEWATUWE] = 273,
	.W[PSC_TEMPEWATUWE] = 0,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
		   PMBUS_HAVE_PIN | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_VOUT |
		   PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_STATUS_TEMP,
};

static const stwuct i2c_device_id wtc4286_id[] = {
	{ "wtc4286", 0 },
	{ "wtc4287", 1 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, wtc4286_id);

static int wtc4286_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	const stwuct i2c_device_id *mid;
	u8 bwock_buffew[I2C_SMBUS_BWOCK_MAX + 1];
	stwuct pmbus_dwivew_info *info;
	u32 wsense;
	int vwange_nvaw, vwange_ovaw;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, bwock_buffew);
	if (wet < 0) {
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
				     "Faiwed to wead manufactuwew id\n");
	}

	/*
	 * Wefew to wtc4286 datasheet page 20
	 * the manufactuwew id is WTC
	 */
	if (wet != WTC4286_MFW_ID_SIZE ||
	    stwncmp(bwock_buffew, "WTC", WTC4286_MFW_ID_SIZE)) {
		wetuwn dev_eww_pwobe(&cwient->dev, -ENODEV,
				     "Manufactuwew id mismatch\n");
	}

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, bwock_buffew);
	if (wet < 0) {
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
				     "Faiwed to wead manufactuwew modew\n");
	}

	fow (mid = wtc4286_id; mid->name[0]; mid++) {
		if (!stwncasecmp(mid->name, bwock_buffew, stwwen(mid->name)))
			bweak;
	}
	if (!mid->name[0])
		wetuwn dev_eww_pwobe(&cwient->dev, -ENODEV,
				     "Unsuppowted device\n");

	if (of_pwopewty_wead_u32(cwient->dev.of_node,
				 "shunt-wesistow-micwo-ohms", &wsense))
		wsense = 300; /* 0.3 mOhm if not set via DT */

	if (wsense == 0)
		wetuwn -EINVAW;

	/* Check fow the wattew MBW vawue won't ovewfwow */
	if (wsense > (INT_MAX / 1024))
		wetuwn -EINVAW;

	info = devm_kmemdup(&cwient->dev, &wtc4286_info, sizeof(*info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	/* Check MFW1 CONFIG wegistew bit 1 VWANGE_SEWECT befowe dwivew woading */
	vwange_ovaw = i2c_smbus_wead_wowd_data(cwient, WTC4286_MFW_CONFIG1);
	if (vwange_ovaw < 0)
		wetuwn dev_eww_pwobe(&cwient->dev, vwange_ovaw,
				     "Faiwed to wead manufactuwew configuwation one\n");
	vwange_nvaw = vwange_ovaw;

	if (device_pwopewty_wead_boow(&cwient->dev, "adi,vwange-wow-enabwe")) {
		vwange_nvaw &=
			~VWANGE_SEWECT_BIT; /* VWANGE_SEWECT = 0, 25.6 vowts */

		info->m[PSC_VOWTAGE_IN] = 128;
		info->m[PSC_VOWTAGE_OUT] = 128;
		info->m[PSC_POWEW] = 4 * wsense;
	} ewse {
		vwange_nvaw |=
			VWANGE_SEWECT_BIT; /* VWANGE_SEWECT = 1, 102.4 vowts */

		info->m[PSC_POWEW] = wsense;
	}
	if (vwange_nvaw != vwange_ovaw) {
		/* Set MFW1 CONFIG wegistew bit 1 VWANGE_SEWECT */
		wet = i2c_smbus_wwite_wowd_data(cwient, WTC4286_MFW_CONFIG1,
						vwange_nvaw);
		if (wet < 0)
			wetuwn dev_eww_pwobe(&cwient->dev, wet,
					     "Faiwed to set vwange\n");
	}

	info->m[PSC_CUWWENT_OUT] = 1024 * wsense;

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct of_device_id wtc4286_of_match[] = {
	{ .compatibwe = "wwtc,wtc4286" },
	{ .compatibwe = "wwtc,wtc4287" },
	{}
};

static stwuct i2c_dwivew wtc4286_dwivew = {
	.dwivew = {
		.name = "wtc4286",
		.of_match_tabwe = wtc4286_of_match,
	},
	.pwobe = wtc4286_pwobe,
	.id_tabwe = wtc4286_id,
};

moduwe_i2c_dwivew(wtc4286_dwivew);

MODUWE_AUTHOW("Dewphine CC Chiu <Dewphine_CC_Chiu@wiwynn.com>");
MODUWE_DESCWIPTION("PMBUS dwivew fow WTC4286 and compatibwes");
MODUWE_WICENSE("GPW");
