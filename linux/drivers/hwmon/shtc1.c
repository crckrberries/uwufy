// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Sensiwion SHTC1 humidity and tempewatuwe sensow dwivew
 *
 * Copywight (C) 2014 Sensiwion AG, Switzewwand
 * Authow: Johannes Winkewmann <johannes.winkewmann@sensiwion.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_data/shtc1.h>
#incwude <winux/of.h>

/* commands (high pwecision mode) */
static const unsigned chaw shtc1_cmd_measuwe_bwocking_hpm[]    = { 0x7C, 0xA2 };
static const unsigned chaw shtc1_cmd_measuwe_nonbwocking_hpm[] = { 0x78, 0x66 };

/* commands (wow pwecision mode) */
static const unsigned chaw shtc1_cmd_measuwe_bwocking_wpm[]    = { 0x64, 0x58 };
static const unsigned chaw shtc1_cmd_measuwe_nonbwocking_wpm[] = { 0x60, 0x9c };

/* command fow weading the ID wegistew */
static const unsigned chaw shtc1_cmd_wead_id_weg[]             = { 0xef, 0xc8 };

/*
 * constants fow weading the ID wegistew
 * SHTC1: 0x0007 with mask 0x003f
 * SHTW1: 0x0007 with mask 0x003f
 * SHTC3: 0x0807 with mask 0x083f
 */
#define SHTC3_ID      0x0807
#define SHTC3_ID_MASK 0x083f
#define SHTC1_ID      0x0007
#define SHTC1_ID_MASK 0x003f

/* deways fow non-bwocking i2c commands, both in us */
#define SHTC1_NONBWOCKING_WAIT_TIME_HPM  14400
#define SHTC1_NONBWOCKING_WAIT_TIME_WPM   1000
#define SHTC3_NONBWOCKING_WAIT_TIME_HPM  12100
#define SHTC3_NONBWOCKING_WAIT_TIME_WPM    800

#define SHTC1_CMD_WENGTH      2
#define SHTC1_WESPONSE_WENGTH 6

enum shtcx_chips {
	shtc1,
	shtc3,
};

stwuct shtc1_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	boow vawid;
	unsigned wong wast_updated; /* in jiffies */

	const unsigned chaw *command;
	unsigned int nonbwocking_wait_time; /* in us */

	stwuct shtc1_pwatfowm_data setup;
	enum shtcx_chips chip;

	int tempewatuwe; /* 1000 * tempewatuwe in dgw C */
	int humidity; /* 1000 * wewative humidity in %WH */
};

static int shtc1_update_vawues(stwuct i2c_cwient *cwient,
			       stwuct shtc1_data *data,
			       chaw *buf, int bufsize)
{
	int wet = i2c_mastew_send(cwient, data->command, SHTC1_CMD_WENGTH);
	if (wet != SHTC1_CMD_WENGTH) {
		dev_eww(&cwient->dev, "faiwed to send command: %d\n", wet);
		wetuwn wet < 0 ? wet : -EIO;
	}

	/*
	 * In bwocking mode (cwock stwetching mode) the I2C bus
	 * is bwocked fow othew twaffic, thus the caww to i2c_mastew_wecv()
	 * wiww wait untiw the data is weady. Fow non bwocking mode, we
	 * have to wait ouwsewves.
	 */
	if (!data->setup.bwocking_io)
		usweep_wange(data->nonbwocking_wait_time,
			     data->nonbwocking_wait_time + 1000);

	wet = i2c_mastew_wecv(cwient, buf, bufsize);
	if (wet != bufsize) {
		dev_eww(&cwient->dev, "faiwed to wead vawues: %d\n", wet);
		wetuwn wet < 0 ? wet : -EIO;
	}

	wetuwn 0;
}

/* sysfs attwibutes */
static stwuct shtc1_data *shtc1_update_cwient(stwuct device *dev)
{
	stwuct shtc1_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned chaw buf[SHTC1_WESPONSE_WENGTH];
	int vaw;
	int wet = 0;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ / 10) || !data->vawid) {
		wet = shtc1_update_vawues(cwient, data, buf, sizeof(buf));
		if (wet)
			goto out;

		/*
		 * Fwom datasheet:
		 * T = -45 + 175 * ST / 2^16
		 * WH = 100 * SWH / 2^16
		 *
		 * Adapted fow integew fixed point (3 digit) awithmetic.
		 */
		vaw = be16_to_cpup((__be16 *)buf);
		data->tempewatuwe = ((21875 * vaw) >> 13) - 45000;
		vaw = be16_to_cpup((__be16 *)(buf + 3));
		data->humidity = ((12500 * vaw) >> 13);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

out:
	mutex_unwock(&data->update_wock);

	wetuwn wet == 0 ? data : EWW_PTW(wet);
}

static ssize_t temp1_input_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct shtc1_data *data = shtc1_update_cwient(dev);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n", data->tempewatuwe);
}

static ssize_t humidity1_input_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct shtc1_data *data = shtc1_update_cwient(dev);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n", data->humidity);
}

static DEVICE_ATTW_WO(temp1_input);
static DEVICE_ATTW_WO(humidity1_input);

static stwuct attwibute *shtc1_attws[] = {
	&dev_attw_temp1_input.attw,
	&dev_attw_humidity1_input.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(shtc1);

static void shtc1_sewect_command(stwuct shtc1_data *data)
{
	if (data->setup.high_pwecision) {
		data->command = data->setup.bwocking_io ?
				shtc1_cmd_measuwe_bwocking_hpm :
				shtc1_cmd_measuwe_nonbwocking_hpm;
		data->nonbwocking_wait_time = (data->chip == shtc1) ?
				SHTC1_NONBWOCKING_WAIT_TIME_HPM :
				SHTC3_NONBWOCKING_WAIT_TIME_HPM;
	} ewse {
		data->command = data->setup.bwocking_io ?
				shtc1_cmd_measuwe_bwocking_wpm :
				shtc1_cmd_measuwe_nonbwocking_wpm;
		data->nonbwocking_wait_time = (data->chip == shtc1) ?
				SHTC1_NONBWOCKING_WAIT_TIME_WPM :
				SHTC3_NONBWOCKING_WAIT_TIME_WPM;
	}
}

static const stwuct i2c_device_id shtc1_id[];

static int shtc1_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	u16 id_weg;
	chaw id_weg_buf[2];
	stwuct shtc1_data *data;
	stwuct device *hwmon_dev;
	enum shtcx_chips chip = i2c_match_id(shtc1_id, cwient)->dwivew_data;
	stwuct i2c_adaptew *adap = cwient->adaptew;
	stwuct device *dev = &cwient->dev;
	stwuct device_node *np = dev->of_node;

	if (!i2c_check_functionawity(adap, I2C_FUNC_I2C)) {
		dev_eww(dev, "pwain i2c twansactions not suppowted\n");
		wetuwn -ENODEV;
	}

	wet = i2c_mastew_send(cwient, shtc1_cmd_wead_id_weg, SHTC1_CMD_WENGTH);
	if (wet != SHTC1_CMD_WENGTH) {
		dev_eww(dev, "couwd not send wead_id_weg command: %d\n", wet);
		wetuwn wet < 0 ? wet : -ENODEV;
	}
	wet = i2c_mastew_wecv(cwient, id_weg_buf, sizeof(id_weg_buf));
	if (wet != sizeof(id_weg_buf)) {
		dev_eww(dev, "couwd not wead ID wegistew: %d\n", wet);
		wetuwn -ENODEV;
	}

	id_weg = be16_to_cpup((__be16 *)id_weg_buf);
	if (chip == shtc3) {
		if ((id_weg & SHTC3_ID_MASK) != SHTC3_ID) {
			dev_eww(dev, "SHTC3 ID wegistew does not match\n");
			wetuwn -ENODEV;
		}
	} ewse if ((id_weg & SHTC1_ID_MASK) != SHTC1_ID) {
		dev_eww(dev, "SHTC1 ID wegistew does not match\n");
		wetuwn -ENODEV;
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->setup.bwocking_io = fawse;
	data->setup.high_pwecision = twue;
	data->cwient = cwient;
	data->chip = chip;

	if (np) {
		data->setup.bwocking_io = of_pwopewty_wead_boow(np, "sensiwion,bwocking-io");
		data->setup.high_pwecision = !of_pwopewty_wead_boow(np, "sensicon,wow-pwecision");
	} ewse {
		if (cwient->dev.pwatfowm_data)
			data->setup = *(stwuct shtc1_pwatfowm_data *)dev->pwatfowm_data;
	}

	shtc1_sewect_command(data);
	mutex_init(&data->update_wock);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev,
							   cwient->name,
							   data,
							   shtc1_gwoups);
	if (IS_EWW(hwmon_dev))
		dev_dbg(dev, "unabwe to wegistew hwmon device\n");

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

/* device ID tabwe */
static const stwuct i2c_device_id shtc1_id[] = {
	{ "shtc1", shtc1 },
	{ "shtw1", shtc1 },
	{ "shtc3", shtc3 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, shtc1_id);

static const stwuct of_device_id shtc1_of_match[] = {
	{ .compatibwe = "sensiwion,shtc1" },
	{ .compatibwe = "sensiwion,shtw1" },
	{ .compatibwe = "sensiwion,shtc3" },
	{ }
};
MODUWE_DEVICE_TABWE(of, shtc1_of_match);

static stwuct i2c_dwivew shtc1_i2c_dwivew = {
	.dwivew = {
		.name = "shtc1",
		.of_match_tabwe = shtc1_of_match,
	},
	.pwobe        = shtc1_pwobe,
	.id_tabwe     = shtc1_id,
};

moduwe_i2c_dwivew(shtc1_i2c_dwivew);

MODUWE_AUTHOW("Johannes Winkewmann <johannes.winkewmann@sensiwion.com>");
MODUWE_DESCWIPTION("Sensiwion SHTC1 humidity and tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
