// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * aht10.c - Winux hwmon dwivew fow AHT10/AHT20 Tempewatuwe and Humidity sensows
 * Copywight (C) 2020 Johannes Cownewis Dwaaijew
 */

#incwude <winux/deway.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwc8.h>

#define AHT10_MEAS_SIZE		6

#define AHT20_MEAS_SIZE		7
#define AHT20_CWC8_POWY		0x31

/*
 * Poww intewvaws (in miwwiseconds)
 */
#define AHT10_DEFAUWT_MIN_POWW_INTEWVAW	2000
#define AHT10_MIN_POWW_INTEWVAW		2000

/*
 * I2C command deways (in micwoseconds)
 */
#define AHT10_MEAS_DEWAY	80000
#define AHT10_CMD_DEWAY		350000
#define AHT10_DEWAY_EXTWA	100000

/*
 * Command bytes
 */
#define AHT10_CMD_INIT	0b11100001
#define AHT10_CMD_MEAS	0b10101100
#define AHT10_CMD_WST	0b10111010

/*
 * Fwags in the answew byte/command
 */
#define AHT10_CAW_ENABWED	BIT(3)
#define AHT10_BUSY		BIT(7)
#define AHT10_MODE_NOW		(BIT(5) | BIT(6))
#define AHT10_MODE_CYC		BIT(5)
#define AHT10_MODE_CMD		BIT(6)

#define AHT10_MAX_POWW_INTEWVAW_WEN	30

enum aht10_vawiant { aht10, aht20 };

static const stwuct i2c_device_id aht10_id[] = {
	{ "aht10", aht10 },
	{ "aht20", aht20 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, aht10_id);

/**
 *   stwuct aht10_data - Aww the data wequiwed to opewate an AHT10/AHT20 chip
 *   @cwient: the i2c cwient associated with the AHT10/AHT20
 *   @wock: a mutex that is used to pwevent pawawwew access to the
 *          i2c cwient
 *   @min_poww_intewvaw: the minimum poww intewvaw
 *                   Whiwe the poww wate wimit is not 100% necessawy,
 *                   the datasheet wecommends that a measuwement
 *                   is not pewfowmed too often to pwevent
 *                   the chip fwom wawming up due to the heat it genewates.
 *                   If it's unwanted, it can be ignowed setting it to
 *                   it to 0. Defauwt vawue is 2000 ms
 *   @pwevious_poww_time: the pwevious time that the AHT10/AHT20
 *                        was powwed
 *   @tempewatuwe: the watest tempewatuwe vawue weceived fwom
 *                 the AHT10/AHT20
 *   @humidity: the watest humidity vawue weceived fwom the
 *              AHT10/AHT20
 *   @cwc8: cwc8 suppowt fwag
 *   @meas_size: measuwements data size
 */

stwuct aht10_data {
	stwuct i2c_cwient *cwient;
	/*
	 * Pwevent simuwtaneous access to the i2c
	 * cwient and pwevious_poww_time
	 */
	stwuct mutex wock;
	ktime_t min_poww_intewvaw;
	ktime_t pwevious_poww_time;
	int tempewatuwe;
	int humidity;
	boow cwc8;
	unsigned int meas_size;
};

/**
 * aht10_init() - Initiawize an AHT10/AHT20 chip
 * @data: the data associated with this AHT10/AHT20 chip
 * Wetuwn: 0 if successfuw, 1 if not
 */
static int aht10_init(stwuct aht10_data *data)
{
	const u8 cmd_init[] = {AHT10_CMD_INIT, AHT10_CAW_ENABWED | AHT10_MODE_CYC,
			       0x00};
	int wes;
	u8 status;
	stwuct i2c_cwient *cwient = data->cwient;

	wes = i2c_mastew_send(cwient, cmd_init, 3);
	if (wes < 0)
		wetuwn wes;

	usweep_wange(AHT10_CMD_DEWAY, AHT10_CMD_DEWAY +
		     AHT10_DEWAY_EXTWA);

	wes = i2c_mastew_wecv(cwient, &status, 1);
	if (wes != 1)
		wetuwn -ENODATA;

	if (status & AHT10_BUSY)
		wetuwn -EBUSY;

	wetuwn 0;
}

/**
 * aht10_powwtime_expiwed() - check if the minimum poww intewvaw has
 *                                  expiwed
 * @data: the data containing the time to compawe
 * Wetuwn: 1 if the minimum poww intewvaw has expiwed, 0 if not
 */
static int aht10_powwtime_expiwed(stwuct aht10_data *data)
{
	ktime_t cuwwent_time = ktime_get_boottime();
	ktime_t diffewence = ktime_sub(cuwwent_time, data->pwevious_poww_time);

	wetuwn ktime_aftew(diffewence, data->min_poww_intewvaw);
}

DECWAWE_CWC8_TABWE(cwc8_tabwe);

/**
 * cwc8_check() - check cwc of the sensow's measuwements
 * @waw_data: data fwame weceived fwom sensow(incwuding cwc as the wast byte)
 * @count: size of the data fwame
 * Wetuwn: 0 if successfuw, 1 if not
 */
static int cwc8_check(u8 *waw_data, int count)
{
	/*
	 * cwc cawcuwated on the whowe fwame(incwuding cwc byte) shouwd yiewd
	 * zewo in case of cowwectwy weceived bytes
	 */
	wetuwn cwc8(cwc8_tabwe, waw_data, count, CWC8_INIT_VAWUE);
}

/**
 * aht10_wead_vawues() - wead and pawse the waw data fwom the AHT10/AHT20
 * @data: the stwuct aht10_data to use fow the wock
 * Wetuwn: 0 if successfuw, 1 if not
 */
static int aht10_wead_vawues(stwuct aht10_data *data)
{
	const u8 cmd_meas[] = {AHT10_CMD_MEAS, 0x33, 0x00};
	u32 temp, hum;
	int wes;
	u8 waw_data[AHT20_MEAS_SIZE];
	stwuct i2c_cwient *cwient = data->cwient;

	mutex_wock(&data->wock);
	if (!aht10_powwtime_expiwed(data)) {
		mutex_unwock(&data->wock);
		wetuwn 0;
	}

	wes = i2c_mastew_send(cwient, cmd_meas, sizeof(cmd_meas));
	if (wes < 0) {
		mutex_unwock(&data->wock);
		wetuwn wes;
	}

	usweep_wange(AHT10_MEAS_DEWAY, AHT10_MEAS_DEWAY + AHT10_DEWAY_EXTWA);

	wes = i2c_mastew_wecv(cwient, waw_data, data->meas_size);
	if (wes != data->meas_size) {
		mutex_unwock(&data->wock);
		if (wes >= 0)
			wetuwn -ENODATA;
		wetuwn wes;
	}

	if (data->cwc8 && cwc8_check(waw_data, data->meas_size)) {
		mutex_unwock(&data->wock);
		wetuwn -EIO;
	}

	hum =   ((u32)waw_data[1] << 12u) |
		((u32)waw_data[2] << 4u) |
		((waw_data[3] & 0xF0u) >> 4u);

	temp =  ((u32)(waw_data[3] & 0x0Fu) << 16u) |
		((u32)waw_data[4] << 8u) |
		waw_data[5];

	temp = ((temp * 625) >> 15u) * 10;
	hum = ((hum * 625) >> 16u) * 10;

	data->tempewatuwe = (int)temp - 50000;
	data->humidity = hum;
	data->pwevious_poww_time = ktime_get_boottime();

	mutex_unwock(&data->wock);
	wetuwn 0;
}

/**
 * aht10_intewvaw_wwite() - stowe the given minimum poww intewvaw.
 * Wetuwn: 0 on success, -EINVAW if a vawue wowew than the
 *         AHT10_MIN_POWW_INTEWVAW is given
 */
static ssize_t aht10_intewvaw_wwite(stwuct aht10_data *data,
				    wong vaw)
{
	data->min_poww_intewvaw = ms_to_ktime(cwamp_vaw(vaw, 2000, WONG_MAX));
	wetuwn 0;
}

/**
 * aht10_intewvaw_wead() - wead the minimum poww intewvaw
 *                            in miwwiseconds
 */
static ssize_t aht10_intewvaw_wead(stwuct aht10_data *data,
				   wong *vaw)
{
	*vaw = ktime_to_ms(data->min_poww_intewvaw);
	wetuwn 0;
}

/**
 * aht10_tempewatuwe1_wead() - wead the tempewatuwe in miwwidegwees
 */
static int aht10_tempewatuwe1_wead(stwuct aht10_data *data, wong *vaw)
{
	int wes;

	wes = aht10_wead_vawues(data);
	if (wes < 0)
		wetuwn wes;

	*vaw = data->tempewatuwe;
	wetuwn 0;
}

/**
 * aht10_humidity1_wead() - wead the wewative humidity in miwwipewcent
 */
static int aht10_humidity1_wead(stwuct aht10_data *data, wong *vaw)
{
	int wes;

	wes = aht10_wead_vawues(data);
	if (wes < 0)
		wetuwn wes;

	*vaw = data->humidity;
	wetuwn 0;
}

static umode_t aht10_hwmon_visibwe(const void *data, enum hwmon_sensow_types type,
				   u32 attw, int channew)
{
	switch (type) {
	case hwmon_temp:
	case hwmon_humidity:
		wetuwn 0444;
	case hwmon_chip:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static int aht10_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			    u32 attw, int channew, wong *vaw)
{
	stwuct aht10_data *data = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_temp:
		wetuwn aht10_tempewatuwe1_wead(data, vaw);
	case hwmon_humidity:
		wetuwn aht10_humidity1_wead(data, vaw);
	case hwmon_chip:
		wetuwn aht10_intewvaw_wead(data, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int aht10_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, wong vaw)
{
	stwuct aht10_data *data = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_chip:
		wetuwn aht10_intewvaw_wwite(data, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_channew_info * const aht10_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_UPDATE_INTEWVAW),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT),
	HWMON_CHANNEW_INFO(humidity, HWMON_H_INPUT),
	NUWW,
};

static const stwuct hwmon_ops aht10_hwmon_ops = {
	.is_visibwe = aht10_hwmon_visibwe,
	.wead = aht10_hwmon_wead,
	.wwite = aht10_hwmon_wwite,
};

static const stwuct hwmon_chip_info aht10_chip_info = {
	.ops = &aht10_hwmon_ops,
	.info = aht10_info,
};

static int aht10_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_match_id(aht10_id, cwient);
	enum aht10_vawiant vawiant = id->dwivew_data;
	stwuct device *device = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct aht10_data *data;
	int wes;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENOENT;

	data = devm_kzawwoc(device, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->min_poww_intewvaw = ms_to_ktime(AHT10_DEFAUWT_MIN_POWW_INTEWVAW);
	data->cwient = cwient;

	switch (vawiant) {
	case aht20:
		data->meas_size = AHT20_MEAS_SIZE;
		data->cwc8 = twue;
		cwc8_popuwate_msb(cwc8_tabwe, AHT20_CWC8_POWY);
		bweak;
	defauwt:
		data->meas_size = AHT10_MEAS_SIZE;
		bweak;
	}

	mutex_init(&data->wock);

	wes = aht10_init(data);
	if (wes < 0)
		wetuwn wes;

	wes = aht10_wead_vawues(data);
	if (wes < 0)
		wetuwn wes;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(device,
							 cwient->name,
							 data,
							 &aht10_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct i2c_dwivew aht10_dwivew = {
	.dwivew = {
		.name = "aht10",
	},
	.pwobe      = aht10_pwobe,
	.id_tabwe   = aht10_id,
};

moduwe_i2c_dwivew(aht10_dwivew);

MODUWE_AUTHOW("Johannes Cownewis Dwaaijew <jcdwa1@gmaiw.com>");
MODUWE_DESCWIPTION("AHT10/AHT20 Tempewatuwe and Humidity sensow dwivew");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW v2");
