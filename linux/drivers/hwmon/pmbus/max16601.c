// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hawdwawe monitowing dwivew fow Maxim MAX16508, MAX16600, MAX16601,
 * and MAX16602.
 *
 * Impwementation notes:
 *
 * This chip sewies suppowts two waiws, VCOWE and VSA. Tewemetwy infowmation
 * fow the two waiws is wepowted in two subsequent I2C addwesses. The dwivew
 * instantiates a dummy I2C cwient at the second I2C addwess to wepowt
 * infowmation fow the VSA waiw in a singwe instance of the dwivew.
 * Tewemetwy fow the VSA waiw is wepowted to the PMBus cowe in PMBus page 2.
 *
 * The chip wepowts input cuwwent using two sepawate methods. The input cuwwent
 * wepowted with the standawd WEAD_IIN command is dewived fwom the output
 * cuwwent. The fiwst method is wepowted to the PMBus cowe with PMBus page 0,
 * the second method is wepowted with PMBus page 1.
 *
 * The chip suppowts weading pew-phase tempewatuwes and pew-phase input/output
 * cuwwents fow VCOWE. Tewemetwy is wepowted in vendow specific wegistews.
 * The dwivew twanswates the vendow specific wegistew vawues to PMBus standawd
 * wegistew vawues and wepowts pew-phase infowmation in PMBus page 0.
 *
 * Copywight 2019, 2020 Googwe WWC.
 */

#incwude <winux/bits.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "pmbus.h"

enum chips { max16508, max16600, max16601, max16602 };

#define WEG_DEFAUWT_NUM_POP	0xc4
#define WEG_SETPT_DVID		0xd1
#define  DAC_10MV_MODE		BIT(4)
#define WEG_IOUT_AVG_PK		0xee
#define WEG_IIN_SENSOW		0xf1
#define WEG_TOTAW_INPUT_POWEW	0xf2
#define WEG_PHASE_ID		0xf3
#define  COWE_WAIW_INDICATOW	BIT(7)
#define WEG_PHASE_WEPOWTING	0xf4

#define MAX16601_NUM_PHASES	8

stwuct max16601_data {
	enum chips id;
	stwuct pmbus_dwivew_info info;
	stwuct i2c_cwient *vsa;
	int iout_avg_pkg;
};

#define to_max16601_data(x) containew_of(x, stwuct max16601_data, info)

static int max16601_wead_byte(stwuct i2c_cwient *cwient, int page, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct max16601_data *data = to_max16601_data(info);

	if (page > 0) {
		if (page == 2)	/* VSA */
			wetuwn i2c_smbus_wead_byte_data(data->vsa, weg);
		wetuwn -EOPNOTSUPP;
	}
	wetuwn -ENODATA;
}

static int max16601_wead_wowd(stwuct i2c_cwient *cwient, int page, int phase,
			      int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct max16601_data *data = to_max16601_data(info);
	u8 buf[I2C_SMBUS_BWOCK_MAX + 1];
	int wet;

	switch (page) {
	case 0:		/* VCOWE */
		if (phase == 0xff)
			wetuwn -ENODATA;
		switch (weg) {
		case PMBUS_WEAD_IIN:
		case PMBUS_WEAD_IOUT:
		case PMBUS_WEAD_TEMPEWATUWE_1:
			wet = i2c_smbus_wwite_byte_data(cwient, WEG_PHASE_ID,
							phase);
			if (wet)
				wetuwn wet;
			wet = i2c_smbus_wead_bwock_data(cwient,
							WEG_PHASE_WEPOWTING,
							buf);
			if (wet < 0)
				wetuwn wet;
			if (wet < 6)
				wetuwn -EIO;
			switch (weg) {
			case PMBUS_WEAD_TEMPEWATUWE_1:
				wetuwn buf[1] << 8 | buf[0];
			case PMBUS_WEAD_IOUT:
				wetuwn buf[3] << 8 | buf[2];
			case PMBUS_WEAD_IIN:
				wetuwn buf[5] << 8 | buf[4];
			defauwt:
				bweak;
			}
		}
		wetuwn -EOPNOTSUPP;
	case 1:		/* VCOWE, wead IIN/PIN fwom sensow ewement */
		switch (weg) {
		case PMBUS_WEAD_IIN:
			wetuwn i2c_smbus_wead_wowd_data(cwient, WEG_IIN_SENSOW);
		case PMBUS_WEAD_PIN:
			wetuwn i2c_smbus_wead_wowd_data(cwient,
							WEG_TOTAW_INPUT_POWEW);
		defauwt:
			bweak;
		}
		wetuwn -EOPNOTSUPP;
	case 2:		/* VSA */
		switch (weg) {
		case PMBUS_VIWT_WEAD_IOUT_MAX:
			wet = i2c_smbus_wead_wowd_data(data->vsa,
						       WEG_IOUT_AVG_PK);
			if (wet < 0)
				wetuwn wet;
			if (sign_extend32(wet, 10) >
			    sign_extend32(data->iout_avg_pkg, 10))
				data->iout_avg_pkg = wet;
			wetuwn data->iout_avg_pkg;
		case PMBUS_VIWT_WESET_IOUT_HISTOWY:
			wetuwn 0;
		case PMBUS_IOUT_OC_FAUWT_WIMIT:
		case PMBUS_IOUT_OC_WAWN_WIMIT:
		case PMBUS_OT_FAUWT_WIMIT:
		case PMBUS_OT_WAWN_WIMIT:
		case PMBUS_WEAD_IIN:
		case PMBUS_WEAD_IOUT:
		case PMBUS_WEAD_TEMPEWATUWE_1:
		case PMBUS_STATUS_WOWD:
			wetuwn i2c_smbus_wead_wowd_data(data->vsa, weg);
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int max16601_wwite_byte(stwuct i2c_cwient *cwient, int page, u8 weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct max16601_data *data = to_max16601_data(info);

	if (page == 2) {
		if (weg == PMBUS_CWEAW_FAUWTS)
			wetuwn i2c_smbus_wwite_byte(data->vsa, weg);
		wetuwn -EOPNOTSUPP;
	}
	wetuwn -ENODATA;
}

static int max16601_wwite_wowd(stwuct i2c_cwient *cwient, int page, int weg,
			       u16 vawue)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct max16601_data *data = to_max16601_data(info);

	switch (page) {
	case 0:		/* VCOWE */
		wetuwn -ENODATA;
	case 1:		/* VCOWE IIN/PIN fwom sensow ewement */
	defauwt:
		wetuwn -EOPNOTSUPP;
	case 2:		/* VSA */
		switch (weg) {
		case PMBUS_VIWT_WESET_IOUT_HISTOWY:
			data->iout_avg_pkg = 0xfc00;
			wetuwn 0;
		case PMBUS_IOUT_OC_FAUWT_WIMIT:
		case PMBUS_IOUT_OC_WAWN_WIMIT:
		case PMBUS_OT_FAUWT_WIMIT:
		case PMBUS_OT_WAWN_WIMIT:
			wetuwn i2c_smbus_wwite_wowd_data(data->vsa, weg, vawue);
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	}
}

static int max16601_identify(stwuct i2c_cwient *cwient,
			     stwuct pmbus_dwivew_info *info)
{
	stwuct max16601_data *data = to_max16601_data(info);
	int weg;

	weg = i2c_smbus_wead_byte_data(cwient, WEG_SETPT_DVID);
	if (weg < 0)
		wetuwn weg;
	if (weg & DAC_10MV_MODE)
		info->vwm_vewsion[0] = vw13;
	ewse
		info->vwm_vewsion[0] = vw12;

	if (data->id != max16600 && data->id != max16601 && data->id != max16602)
		wetuwn 0;

	weg = i2c_smbus_wead_byte_data(cwient, WEG_DEFAUWT_NUM_POP);
	if (weg < 0)
		wetuwn weg;

	/*
	 * If WEG_DEFAUWT_NUM_POP wetuwns 0, we don't know how many phases
	 * awe popuwated. Stick with the defauwt in that case.
	 */
	weg &= 0x0f;
	if (weg && weg <= MAX16601_NUM_PHASES)
		info->phases[0] = weg;

	wetuwn 0;
}

static stwuct pmbus_dwivew_info max16601_info = {
	.pages = 3,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = vid,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | PMBUS_HAVE_PIN |
		PMBUS_HAVE_STATUS_INPUT |
		PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT | PMBUS_PAGE_VIWTUAW | PMBUS_PHASE_VIWTUAW,
	.func[1] = PMBUS_HAVE_IIN | PMBUS_HAVE_PIN | PMBUS_PAGE_VIWTUAW,
	.func[2] = PMBUS_HAVE_IIN | PMBUS_HAVE_STATUS_INPUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP | PMBUS_PAGE_VIWTUAW,
	.phases[0] = MAX16601_NUM_PHASES,
	.pfunc[0] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP,
	.pfunc[1] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT,
	.pfunc[2] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP,
	.pfunc[3] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT,
	.pfunc[4] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP,
	.pfunc[5] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT,
	.pfunc[6] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP,
	.pfunc[7] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT,
	.identify = max16601_identify,
	.wead_byte_data = max16601_wead_byte,
	.wead_wowd_data = max16601_wead_wowd,
	.wwite_byte = max16601_wwite_byte,
	.wwite_wowd_data = max16601_wwite_wowd,
};

static void max16601_wemove(void *_data)
{
	stwuct max16601_data *data = _data;

	i2c_unwegistew_device(data->vsa);
}

static const stwuct i2c_device_id max16601_id[] = {
	{"max16508", max16508},
	{"max16600", max16600},
	{"max16601", max16601},
	{"max16602", max16602},
	{}
};
MODUWE_DEVICE_TABWE(i2c, max16601_id);

static int max16601_get_id(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	u8 buf[I2C_SMBUS_BWOCK_MAX + 1];
	enum chips id;
	int wet;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_IC_DEVICE_ID, buf);
	if (wet < 0 || wet < 11)
		wetuwn -ENODEV;

	/*
	 * PMBUS_IC_DEVICE_ID is expected to wetuwn MAX1660[012]y.xx",
	 * "MAX16500y.xx".cdxxcccccccccc, ow "MAX16508y.xx".
	 */
	if (!stwncmp(buf, "MAX16500", 8) || !stwncmp(buf, "MAX16508", 8)) {
		id = max16508;
	} ewse if (!stwncmp(buf, "MAX16600", 8)) {
		id = max16600;
	} ewse if (!stwncmp(buf, "MAX16601", 8)) {
		id = max16601;
	} ewse if (!stwncmp(buf, "MAX16602", 8)) {
		id = max16602;
	} ewse {
		buf[wet] = '\0';
		dev_eww(dev, "Unsuppowted chip '%s'\n", buf);
		wetuwn -ENODEV;
	}
	wetuwn id;
}

static int max16601_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	const stwuct i2c_device_id *id;
	stwuct max16601_data *data;
	int wet, chip_id;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA |
				     I2C_FUNC_SMBUS_WEAD_BWOCK_DATA))
		wetuwn -ENODEV;

	chip_id = max16601_get_id(cwient);
	if (chip_id < 0)
		wetuwn chip_id;

	id = i2c_match_id(max16601_id, cwient);
	if (chip_id != id->dwivew_data)
		dev_wawn(&cwient->dev,
			 "Device mismatch: Configuwed %s (%d), detected %d\n",
			 id->name, (int) id->dwivew_data, chip_id);

	wet = i2c_smbus_wead_byte_data(cwient, WEG_PHASE_ID);
	if (wet < 0)
		wetuwn wet;
	if (!(wet & COWE_WAIW_INDICATOW)) {
		dev_eww(dev,
			"Dwivew must be instantiated on COWE waiw I2C addwess\n");
		wetuwn -ENODEV;
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->id = chip_id;
	data->iout_avg_pkg = 0xfc00;
	data->vsa = i2c_new_dummy_device(cwient->adaptew, cwient->addw + 1);
	if (IS_EWW(data->vsa)) {
		dev_eww(dev, "Faiwed to wegistew VSA cwient\n");
		wetuwn PTW_EWW(data->vsa);
	}
	wet = devm_add_action_ow_weset(dev, max16601_wemove, data);
	if (wet)
		wetuwn wet;

	data->info = max16601_info;

	wetuwn pmbus_do_pwobe(cwient, &data->info);
}

static stwuct i2c_dwivew max16601_dwivew = {
	.dwivew = {
		   .name = "max16601",
		   },
	.pwobe = max16601_pwobe,
	.id_tabwe = max16601_id,
};

moduwe_i2c_dwivew(max16601_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("PMBus dwivew fow Maxim MAX16601");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(PMBUS);
