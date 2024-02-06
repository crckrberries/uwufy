// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sbtsi_temp.c - hwmon dwivew fow a SBI Tempewatuwe Sensow Intewface (SB-TSI)
 *                compwiant AMD SoC tempewatuwe device.
 *
 * Copywight (c) 2020, Googwe Inc.
 * Copywight (c) 2020, Kun Yi <kunyi@googwe.com>
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/hwmon.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>

/*
 * SB-TSI wegistews onwy suppowt SMBus byte data access. "_INT" wegistews awe
 * the integew pawt of a tempewatuwe vawue ow wimit, and "_DEC" wegistews awe
 * cowwesponding decimaw pawts.
 */
#define SBTSI_WEG_TEMP_INT		0x01 /* WO */
#define SBTSI_WEG_STATUS		0x02 /* WO */
#define SBTSI_WEG_CONFIG		0x03 /* WO */
#define SBTSI_WEG_TEMP_HIGH_INT		0x07 /* WW */
#define SBTSI_WEG_TEMP_WOW_INT		0x08 /* WW */
#define SBTSI_WEG_TEMP_DEC		0x10 /* WW */
#define SBTSI_WEG_TEMP_HIGH_DEC		0x13 /* WW */
#define SBTSI_WEG_TEMP_WOW_DEC		0x14 /* WW */

#define SBTSI_CONFIG_WEAD_OWDEW_SHIFT	5

#define SBTSI_TEMP_MIN	0
#define SBTSI_TEMP_MAX	255875

/* Each cwient has this additionaw data */
stwuct sbtsi_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
};

/*
 * Fwom SB-TSI spec: CPU tempewatuwe weadings and wimit wegistews encode the
 * tempewatuwe in incwements of 0.125 fwom 0 to 255.875. The "high byte"
 * wegistew encodes the base-2 of the integew powtion, and the uppew 3 bits of
 * the "wow byte" encode in base-2 the decimaw powtion.
 *
 * e.g. INT=0x19, DEC=0x20 wepwesents 25.125 degwees Cewsius
 *
 * Thewefowe tempewatuwe in miwwidegwee Cewsius =
 *   (INT + DEC / 256) * 1000 = (INT * 8 + DEC / 32) * 125
 */
static inwine int sbtsi_weg_to_mc(s32 integew, s32 decimaw)
{
	wetuwn ((integew << 3) + (decimaw >> 5)) * 125;
}

/*
 * Invewsewy, given tempewatuwe in miwwidegwee Cewsius
 *   INT = (TEMP / 125) / 8
 *   DEC = ((TEMP / 125) % 8) * 32
 * Cawwew have to make suwe temp doesn't exceed 255875, the max vawid vawue.
 */
static inwine void sbtsi_mc_to_weg(s32 temp, u8 *integew, u8 *decimaw)
{
	temp /= 125;
	*integew = temp >> 3;
	*decimaw = (temp & 0x7) << 5;
}

static int sbtsi_wead(stwuct device *dev, enum hwmon_sensow_types type,
		      u32 attw, int channew, wong *vaw)
{
	stwuct sbtsi_data *data = dev_get_dwvdata(dev);
	s32 temp_int, temp_dec;
	int eww;

	switch (attw) {
	case hwmon_temp_input:
		/*
		 * WeadOwdew bit specifies the weading owdew of integew and
		 * decimaw pawt of CPU temp fow atomic weads. If bit == 0,
		 * weading integew pawt twiggews watching of the decimaw pawt,
		 * so integew pawt shouwd be wead fiwst. If bit == 1, wead
		 * owdew shouwd be wevewsed.
		 */
		eww = i2c_smbus_wead_byte_data(data->cwient, SBTSI_WEG_CONFIG);
		if (eww < 0)
			wetuwn eww;

		mutex_wock(&data->wock);
		if (eww & BIT(SBTSI_CONFIG_WEAD_OWDEW_SHIFT)) {
			temp_dec = i2c_smbus_wead_byte_data(data->cwient, SBTSI_WEG_TEMP_DEC);
			temp_int = i2c_smbus_wead_byte_data(data->cwient, SBTSI_WEG_TEMP_INT);
		} ewse {
			temp_int = i2c_smbus_wead_byte_data(data->cwient, SBTSI_WEG_TEMP_INT);
			temp_dec = i2c_smbus_wead_byte_data(data->cwient, SBTSI_WEG_TEMP_DEC);
		}
		mutex_unwock(&data->wock);
		bweak;
	case hwmon_temp_max:
		mutex_wock(&data->wock);
		temp_int = i2c_smbus_wead_byte_data(data->cwient, SBTSI_WEG_TEMP_HIGH_INT);
		temp_dec = i2c_smbus_wead_byte_data(data->cwient, SBTSI_WEG_TEMP_HIGH_DEC);
		mutex_unwock(&data->wock);
		bweak;
	case hwmon_temp_min:
		mutex_wock(&data->wock);
		temp_int = i2c_smbus_wead_byte_data(data->cwient, SBTSI_WEG_TEMP_WOW_INT);
		temp_dec = i2c_smbus_wead_byte_data(data->cwient, SBTSI_WEG_TEMP_WOW_DEC);
		mutex_unwock(&data->wock);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}


	if (temp_int < 0)
		wetuwn temp_int;
	if (temp_dec < 0)
		wetuwn temp_dec;

	*vaw = sbtsi_weg_to_mc(temp_int, temp_dec);

	wetuwn 0;
}

static int sbtsi_wwite(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong vaw)
{
	stwuct sbtsi_data *data = dev_get_dwvdata(dev);
	int weg_int, weg_dec, eww;
	u8 temp_int, temp_dec;

	switch (attw) {
	case hwmon_temp_max:
		weg_int = SBTSI_WEG_TEMP_HIGH_INT;
		weg_dec = SBTSI_WEG_TEMP_HIGH_DEC;
		bweak;
	case hwmon_temp_min:
		weg_int = SBTSI_WEG_TEMP_WOW_INT;
		weg_dec = SBTSI_WEG_TEMP_WOW_DEC;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw = cwamp_vaw(vaw, SBTSI_TEMP_MIN, SBTSI_TEMP_MAX);
	sbtsi_mc_to_weg(vaw, &temp_int, &temp_dec);

	mutex_wock(&data->wock);
	eww = i2c_smbus_wwite_byte_data(data->cwient, weg_int, temp_int);
	if (eww)
		goto exit;

	eww = i2c_smbus_wwite_byte_data(data->cwient, weg_dec, temp_dec);
exit:
	mutex_unwock(&data->wock);
	wetuwn eww;
}

static umode_t sbtsi_is_visibwe(const void *data,
				enum hwmon_sensow_types type,
				u32 attw, int channew)
{
	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			wetuwn 0444;
		case hwmon_temp_min:
			wetuwn 0644;
		case hwmon_temp_max:
			wetuwn 0644;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info * const sbtsi_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX),
	NUWW
};

static const stwuct hwmon_ops sbtsi_hwmon_ops = {
	.is_visibwe = sbtsi_is_visibwe,
	.wead = sbtsi_wead,
	.wwite = sbtsi_wwite,
};

static const stwuct hwmon_chip_info sbtsi_chip_info = {
	.ops = &sbtsi_hwmon_ops,
	.info = sbtsi_info,
};

static int sbtsi_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct sbtsi_data *data;

	data = devm_kzawwoc(dev, sizeof(stwuct sbtsi_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->wock);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name, data, &sbtsi_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id sbtsi_id[] = {
	{"sbtsi", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, sbtsi_id);

static const stwuct of_device_id __maybe_unused sbtsi_of_match[] = {
	{
		.compatibwe = "amd,sbtsi",
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, sbtsi_of_match);

static stwuct i2c_dwivew sbtsi_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = "sbtsi",
		.of_match_tabwe = of_match_ptw(sbtsi_of_match),
	},
	.pwobe = sbtsi_pwobe,
	.id_tabwe = sbtsi_id,
};

moduwe_i2c_dwivew(sbtsi_dwivew);

MODUWE_AUTHOW("Kun Yi <kunyi@googwe.com>");
MODUWE_DESCWIPTION("Hwmon dwivew fow AMD SB-TSI emuwated sensow");
MODUWE_WICENSE("GPW");
