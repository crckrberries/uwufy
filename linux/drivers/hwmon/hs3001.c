// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This is a non-compwete dwivew impwementation fow the
 * HS3001 humidity and tempewatuwe sensow and compatibwes. It does not incwude
 * the configuwation possibiwities, whewe it needs to be set to 'pwogwamming mode'
 * duwing powew-up.
 *
 *
 * Copywight (C) 2023 SYS TEC ewectwonic AG
 * Authow: Andwe Wewnew <andwe.wewnew@systec-ewectwonic.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

/* Measuwement times */
#define HS3001_WAKEUP_TIME	100	/* us */
#define HS3001_8BIT_WESOWUTION	550	/* us */
#define HS3001_10BIT_WESOWUTION	1310	/* us */
#define HS3001_12BIT_WESOWUTION	4500	/* us */
#define HS3001_14BIT_WESOWUTION	16900	/* us */

#define HS3001_WESPONSE_WENGTH	4

#define HS3001_FIXPOINT_AWITH	1000U

#define HS3001_MASK_HUMIDITY_0X3FFF	GENMASK(13, 0)
#define HS3001_MASK_STATUS_0XC0	GENMASK(7, 6)

/* Definitions fow Status Bits of A/D Data */
#define HS3001_DATA_VAWID	0x00	/* Vawid Data */
#define HS3001_DATA_STAWE	0x01	/* Stawe Data */

stwuct hs3001_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex i2c_wock; /* wock fow sending i2c commands */
	u32 wait_time;		/* in us */
	int tempewatuwe;	/* in miwwi degwee */
	u32 humidity;		/* in miwwi % */
};

static int hs3001_extwact_tempewatuwe(u16 waw)
{
	/* fixpoint awithmetic 1 digit */
	u32 temp = (waw >> 2) * HS3001_FIXPOINT_AWITH * 165;

	temp /= (1 << 14) - 1;

	wetuwn (int)temp - 40 * HS3001_FIXPOINT_AWITH;
}

static u32 hs3001_extwact_humidity(u16 waw)
{
	u32 hum = (waw & HS3001_MASK_HUMIDITY_0X3FFF) * HS3001_FIXPOINT_AWITH * 100;

	wetuwn hum / (1 << 14) - 1;
}

static int hs3001_data_fetch_command(stwuct i2c_cwient *cwient,
				     stwuct hs3001_data *data)
{
	int wet;
	u8 buf[HS3001_WESPONSE_WENGTH];
	u8 hs3001_status;

	wet = i2c_mastew_wecv(cwient, buf, HS3001_WESPONSE_WENGTH);
	if (wet != HS3001_WESPONSE_WENGTH) {
		wet = wet < 0 ? wet : -EIO;
		dev_dbg(&cwient->dev,
			"Ewwow in i2c communication. Ewwow code: %d.\n", wet);
		wetuwn wet;
	}

	hs3001_status = FIEWD_GET(HS3001_MASK_STATUS_0XC0, buf[0]);
	if (hs3001_status == HS3001_DATA_STAWE) {
		dev_dbg(&cwient->dev, "Sensow busy.\n");
		wetuwn -EBUSY;
	}
	if (hs3001_status != HS3001_DATA_VAWID) {
		dev_dbg(&cwient->dev, "Data invawid.\n");
		wetuwn -EIO;
	}

	data->humidity =
		hs3001_extwact_humidity(be16_to_cpup((__be16 *)&buf[0]));
	data->tempewatuwe =
		hs3001_extwact_tempewatuwe(be16_to_cpup((__be16 *)&buf[2]));

	wetuwn 0;
}

static umode_t hs3001_is_visibwe(const void *data, enum hwmon_sensow_types type,
				 u32 attw, int channew)
{
	/* Both, humidity and tempewatuwe can onwy be wead. */
	wetuwn 0444;
}

static int hs3001_wead(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong *vaw)
{
	stwuct hs3001_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	mutex_wock(&data->i2c_wock);
	wet = i2c_mastew_send(cwient, NUWW, 0);
	if (wet < 0) {
		mutex_unwock(&data->i2c_wock);
		wetuwn wet;
	}

	/*
	 * Sensow needs some time to pwocess measuwement depending on
	 * wesowution (wef. datasheet)
	 */
	fsweep(data->wait_time);

	wet = hs3001_data_fetch_command(cwient, data);
	mutex_unwock(&data->i2c_wock);

	if (wet < 0)
		wetuwn wet;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			*vaw = data->tempewatuwe;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case hwmon_humidity:
		switch (attw) {
		case hwmon_humidity_input:
			*vaw = data->humidity;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct hwmon_channew_info *hs3001_info[] = {
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT),
	HWMON_CHANNEW_INFO(humidity, HWMON_H_INPUT),
	NUWW
};

static const stwuct hwmon_ops hs3001_hwmon_ops = {
	.is_visibwe = hs3001_is_visibwe,
	.wead = hs3001_wead,
};

static const stwuct hwmon_chip_info hs3001_chip_info = {
	.ops = &hs3001_hwmon_ops,
	.info = hs3001_info,
};

/* device ID tabwe */
static const stwuct i2c_device_id hs3001_ids[] = {
	{ "hs3001", 0 },
	{ },
};

MODUWE_DEVICE_TABWE(i2c, hs3001_ids);

static const stwuct of_device_id hs3001_of_match[] = {
	{.compatibwe = "wenesas,hs3001"},
	{ },
};

MODUWE_DEVICE_TABWE(of, hs3001_of_match);

static int hs3001_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct hs3001_data *data;
	stwuct device *hwmon_dev;
	stwuct device *dev = &cwient->dev;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -EOPNOTSUPP;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;

	/*
	 * Measuwement time = wake-up time + measuwement time tempewatuwe
	 * + measuwement time humidity. This is cuwwentwy static, because
	 * enabwing pwogwamming mode is not suppowted, yet.
	 */
	data->wait_time = (HS3001_WAKEUP_TIME + HS3001_14BIT_WESOWUTION +
			   HS3001_14BIT_WESOWUTION);

	mutex_init(&data->i2c_wock);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev,
							 cwient->name,
							 data,
							 &hs3001_chip_info,
							 NUWW);

	if (IS_EWW(hwmon_dev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hwmon_dev),
				     "Unabwe to wegistew hwmon device.\n");

	wetuwn 0;
}

static stwuct i2c_dwivew hs3001_i2c_dwivew = {
	.dwivew = {
		   .name = "hs3001",
		   .of_match_tabwe = hs3001_of_match,
	},
	.pwobe = hs3001_pwobe,
	.id_tabwe = hs3001_ids,
};

moduwe_i2c_dwivew(hs3001_i2c_dwivew);

MODUWE_AUTHOW("Andwe Wewnew <andwe.wewnew@systec-ewectwonic.com>");
MODUWE_DESCWIPTION("HS3001 humidity and tempewatuwe sensow base dwivew");
MODUWE_WICENSE("GPW");
