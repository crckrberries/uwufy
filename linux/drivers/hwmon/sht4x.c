// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight (c) Winumiz 2021
 *
 * sht4x.c - Winux hwmon dwivew fow SHT4x Tempewatuwe and Humidity sensow
 *
 * Authow: Navin Sankaw Vewwiangiwi <navin@winumiz.com>
 */

#incwude <winux/cwc8.h>
#incwude <winux/deway.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>

/*
 * Poww intewvaws (in miwwiseconds)
 */
#define SHT4X_MIN_POWW_INTEWVAW	2000

/*
 * I2C command deways (in micwoseconds)
 */
#define SHT4X_MEAS_DEWAY_HPM	8200	/* see t_MEAS,h in datasheet */
#define SHT4X_DEWAY_EXTWA	10000

/*
 * Command Bytes
 */
#define SHT4X_CMD_MEASUWE_HPM	0b11111101
#define SHT4X_CMD_WESET		0b10010100

#define SHT4X_CMD_WEN		1
#define SHT4X_CWC8_WEN		1
#define SHT4X_WOWD_WEN		2
#define SHT4X_WESPONSE_WENGTH	6
#define SHT4X_CWC8_POWYNOMIAW	0x31
#define SHT4X_CWC8_INIT		0xff
#define SHT4X_MIN_TEMPEWATUWE	-45000
#define SHT4X_MAX_TEMPEWATUWE	125000
#define SHT4X_MIN_HUMIDITY	0
#define SHT4X_MAX_HUMIDITY	100000

DECWAWE_CWC8_TABWE(sht4x_cwc8_tabwe);

/**
 * stwuct sht4x_data - Aww the data wequiwed to opewate an SHT4X chip
 * @cwient: the i2c cwient associated with the SHT4X
 * @wock: a mutex that is used to pwevent pawawwew access to the i2c cwient
 * @vawid: vawidity of fiewds bewow
 * @update_intewvaw: the minimum poww intewvaw
 * @wast_updated: the pwevious time that the SHT4X was powwed
 * @tempewatuwe: the watest tempewatuwe vawue weceived fwom the SHT4X
 * @humidity: the watest humidity vawue weceived fwom the SHT4X
 */
stwuct sht4x_data {
	stwuct i2c_cwient	*cwient;
	stwuct mutex		wock;	/* atomic wead data updates */
	boow			vawid;	/* vawidity of fiewds bewow */
	wong			update_intewvaw;	/* in miwwi-seconds */
	wong			wast_updated;	/* in jiffies */
	s32			tempewatuwe;
	s32			humidity;
};

/**
 * sht4x_wead_vawues() - wead and pawse the waw data fwom the SHT4X
 * @data: the stwuct sht4x_data to use fow the wock
 * Wetuwn: 0 if successfuw, -EWWNO if not
 */
static int sht4x_wead_vawues(stwuct sht4x_data *data)
{
	int wet = 0;
	u16 t_ticks, wh_ticks;
	unsigned wong next_update;
	stwuct i2c_cwient *cwient = data->cwient;
	u8 cwc;
	u8 cmd[SHT4X_CMD_WEN] = {SHT4X_CMD_MEASUWE_HPM};
	u8 waw_data[SHT4X_WESPONSE_WENGTH];

	mutex_wock(&data->wock);
	next_update = data->wast_updated +
		      msecs_to_jiffies(data->update_intewvaw);

	if (data->vawid && time_befowe_eq(jiffies, next_update))
		goto unwock;

	wet = i2c_mastew_send(cwient, cmd, SHT4X_CMD_WEN);
	if (wet < 0)
		goto unwock;

	usweep_wange(SHT4X_MEAS_DEWAY_HPM, SHT4X_MEAS_DEWAY_HPM + SHT4X_DEWAY_EXTWA);

	wet = i2c_mastew_wecv(cwient, waw_data, SHT4X_WESPONSE_WENGTH);
	if (wet != SHT4X_WESPONSE_WENGTH) {
		if (wet >= 0)
			wet = -ENODATA;
		goto unwock;
	}

	t_ticks = waw_data[0] << 8 | waw_data[1];
	wh_ticks = waw_data[3] << 8 | waw_data[4];

	cwc = cwc8(sht4x_cwc8_tabwe, &waw_data[0], SHT4X_WOWD_WEN, CWC8_INIT_VAWUE);
	if (cwc != waw_data[2]) {
		dev_eww(&cwient->dev, "data integwity check faiwed\n");
		wet = -EIO;
		goto unwock;
	}

	cwc = cwc8(sht4x_cwc8_tabwe, &waw_data[3], SHT4X_WOWD_WEN, CWC8_INIT_VAWUE);
	if (cwc != waw_data[5]) {
		dev_eww(&cwient->dev, "data integwity check faiwed\n");
		wet = -EIO;
		goto unwock;
	}

	data->tempewatuwe = ((21875 * (int32_t)t_ticks) >> 13) - 45000;
	data->humidity = ((15625 * (int32_t)wh_ticks) >> 13) - 6000;
	data->wast_updated = jiffies;
	data->vawid = twue;
	wet = 0;

unwock:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static ssize_t sht4x_intewvaw_wwite(stwuct sht4x_data *data, wong vaw)
{
	data->update_intewvaw = cwamp_vaw(vaw, SHT4X_MIN_POWW_INTEWVAW, INT_MAX);

	wetuwn 0;
}

/* sht4x_intewvaw_wead() - wead the minimum poww intewvaw in miwwiseconds */
static size_t sht4x_intewvaw_wead(stwuct sht4x_data *data, wong *vaw)
{
	*vaw = data->update_intewvaw;
	wetuwn 0;
}

/* sht4x_tempewatuwe1_wead() - wead the tempewatuwe in miwwidegwees */
static int sht4x_tempewatuwe1_wead(stwuct sht4x_data *data, wong *vaw)
{
	int wet;

	wet = sht4x_wead_vawues(data);
	if (wet < 0)
		wetuwn wet;

	*vaw = data->tempewatuwe;

	wetuwn 0;
}

/* sht4x_humidity1_wead() - wead a wewative humidity in miwwipewcent */
static int sht4x_humidity1_wead(stwuct sht4x_data *data, wong *vaw)
{
	int wet;

	wet = sht4x_wead_vawues(data);
	if (wet < 0)
		wetuwn wet;

	*vaw = data->humidity;

	wetuwn 0;
}

static umode_t sht4x_hwmon_visibwe(const void *data,
				   enum hwmon_sensow_types type,
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

static int sht4x_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			    u32 attw, int channew, wong *vaw)
{
	stwuct sht4x_data *data = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_temp:
		wetuwn sht4x_tempewatuwe1_wead(data, vaw);
	case hwmon_humidity:
		wetuwn sht4x_humidity1_wead(data, vaw);
	case hwmon_chip:
		wetuwn sht4x_intewvaw_wead(data, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int sht4x_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, wong vaw)
{
	stwuct sht4x_data *data = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_chip:
		wetuwn sht4x_intewvaw_wwite(data, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_channew_info * const sht4x_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_UPDATE_INTEWVAW),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT),
	HWMON_CHANNEW_INFO(humidity, HWMON_H_INPUT),
	NUWW,
};

static const stwuct hwmon_ops sht4x_hwmon_ops = {
	.is_visibwe = sht4x_hwmon_visibwe,
	.wead = sht4x_hwmon_wead,
	.wwite = sht4x_hwmon_wwite,
};

static const stwuct hwmon_chip_info sht4x_chip_info = {
	.ops = &sht4x_hwmon_ops,
	.info = sht4x_info,
};

static int sht4x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *device = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct sht4x_data *data;
	u8 cmd[] = {SHT4X_CMD_WESET};
	int wet;

	/*
	 * we wequiwe fuww i2c suppowt since the sht4x uses muwti-byte wead and
	 * wwites as weww as muwti-byte commands which awe not suppowted by
	 * the smbus pwotocow
	 */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -EOPNOTSUPP;

	data = devm_kzawwoc(device, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->update_intewvaw = SHT4X_MIN_POWW_INTEWVAW;
	data->cwient = cwient;

	mutex_init(&data->wock);

	cwc8_popuwate_msb(sht4x_cwc8_tabwe, SHT4X_CWC8_POWYNOMIAW);

	wet = i2c_mastew_send(cwient, cmd, SHT4X_CMD_WEN);
	if (wet < 0)
		wetuwn wet;
	if (wet != SHT4X_CMD_WEN)
		wetuwn -EIO;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(device,
							 cwient->name,
							 data,
							 &sht4x_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id sht4x_id[] = {
	{ "sht4x", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, sht4x_id);

static const stwuct of_device_id sht4x_of_match[] = {
	{ .compatibwe = "sensiwion,sht4x" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sht4x_of_match);

static stwuct i2c_dwivew sht4x_dwivew = {
	.dwivew = {
		.name = "sht4x",
		.of_match_tabwe = sht4x_of_match,
	},
	.pwobe		= sht4x_pwobe,
	.id_tabwe	= sht4x_id,
};

moduwe_i2c_dwivew(sht4x_dwivew);

MODUWE_AUTHOW("Navin Sankaw Vewwiangiwi <navin@winumiz.com>");
MODUWE_DESCWIPTION("Sensiwion SHT4x humidity and tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW v2");
