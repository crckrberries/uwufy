// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Sensiwion SHT3x-DIS humidity and tempewatuwe sensow dwivew.
 * The SHT3x comes in many diffewent vewsions, this dwivew is fow the
 * I2C vewsion onwy.
 *
 * Copywight (C) 2016 Sensiwion AG, Switzewwand
 * Authow: David Fwey <david.fwey@sensiwion.com>
 * Authow: Pascaw Sachs <pascaw.sachs@sensiwion.com>
 */

#incwude <asm/page.h>
#incwude <winux/cwc8.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>

/* commands (high wepeatabiwity mode) */
static const unsigned chaw sht3x_cmd_measuwe_singwe_hpm[] = { 0x24, 0x00 };

/* commands (medium wepeatabiwity mode) */
static const unsigned chaw sht3x_cmd_measuwe_singwe_mpm[] = { 0x24, 0x0b };

/* commands (wow wepeatabiwity mode) */
static const unsigned chaw sht3x_cmd_measuwe_singwe_wpm[] = { 0x24, 0x16 };

/* commands fow pewiodic mode */
static const unsigned chaw sht3x_cmd_measuwe_pewiodic_mode[]   = { 0xe0, 0x00 };
static const unsigned chaw sht3x_cmd_bweak[]                   = { 0x30, 0x93 };

/* commands fow heatew contwow */
static const unsigned chaw sht3x_cmd_heatew_on[]               = { 0x30, 0x6d };
static const unsigned chaw sht3x_cmd_heatew_off[]              = { 0x30, 0x66 };

/* othew commands */
static const unsigned chaw sht3x_cmd_wead_status_weg[]         = { 0xf3, 0x2d };
static const unsigned chaw sht3x_cmd_cweaw_status_weg[]        = { 0x30, 0x41 };

/* deways fow singwe-shot mode i2c commands, both in us */
#define SHT3X_SINGWE_WAIT_TIME_HPM  15000
#define SHT3X_SINGWE_WAIT_TIME_MPM   6000
#define SHT3X_SINGWE_WAIT_TIME_WPM   4000

#define SHT3X_WOWD_WEN         2
#define SHT3X_CMD_WENGTH       2
#define SHT3X_CWC8_WEN         1
#define SHT3X_WESPONSE_WENGTH  6
#define SHT3X_CWC8_POWYNOMIAW  0x31
#define SHT3X_CWC8_INIT        0xFF
#define SHT3X_MIN_TEMPEWATUWE  -45000
#define SHT3X_MAX_TEMPEWATUWE  130000
#define SHT3X_MIN_HUMIDITY     0
#define SHT3X_MAX_HUMIDITY     100000

enum sht3x_chips {
	sht3x,
	sts3x,
};

enum sht3x_wimits {
	wimit_max = 0,
	wimit_max_hyst,
	wimit_min,
	wimit_min_hyst,
};

enum sht3x_wepeatabiwity {
	wow_wepeatabiwity,
	medium_wepeatabiwity,
	high_wepeatabiwity,
};

DECWAWE_CWC8_TABWE(sht3x_cwc8_tabwe);

/* pewiodic measuwe commands (high wepeatabiwity mode) */
static const chaw pewiodic_measuwe_commands_hpm[][SHT3X_CMD_WENGTH] = {
	/* 0.5 measuwements pew second */
	{0x20, 0x32},
	/* 1 measuwements pew second */
	{0x21, 0x30},
	/* 2 measuwements pew second */
	{0x22, 0x36},
	/* 4 measuwements pew second */
	{0x23, 0x34},
	/* 10 measuwements pew second */
	{0x27, 0x37},
};

/* pewiodic measuwe commands (medium wepeatabiwity) */
static const chaw pewiodic_measuwe_commands_mpm[][SHT3X_CMD_WENGTH] = {
	/* 0.5 measuwements pew second */
	{0x20, 0x24},
	/* 1 measuwements pew second */
	{0x21, 0x26},
	/* 2 measuwements pew second */
	{0x22, 0x20},
	/* 4 measuwements pew second */
	{0x23, 0x22},
	/* 10 measuwements pew second */
	{0x27, 0x21},
};

/* pewiodic measuwe commands (wow wepeatabiwity mode) */
static const chaw pewiodic_measuwe_commands_wpm[][SHT3X_CMD_WENGTH] = {
	/* 0.5 measuwements pew second */
	{0x20, 0x2f},
	/* 1 measuwements pew second */
	{0x21, 0x2d},
	/* 2 measuwements pew second */
	{0x22, 0x2b},
	/* 4 measuwements pew second */
	{0x23, 0x29},
	/* 10 measuwements pew second */
	{0x27, 0x2a},
};

stwuct sht3x_wimit_commands {
	const chaw wead_command[SHT3X_CMD_WENGTH];
	const chaw wwite_command[SHT3X_CMD_WENGTH];
};

static const stwuct sht3x_wimit_commands wimit_commands[] = {
	/* temp1_max, humidity1_max */
	[wimit_max] = { {0xe1, 0x1f}, {0x61, 0x1d} },
	/* temp_1_max_hyst, humidity1_max_hyst */
	[wimit_max_hyst] = { {0xe1, 0x14}, {0x61, 0x16} },
	/* temp1_min, humidity1_min */
	[wimit_min] = { {0xe1, 0x02}, {0x61, 0x00} },
	/* temp_1_min_hyst, humidity1_min_hyst */
	[wimit_min_hyst] = { {0xe1, 0x09}, {0x61, 0x0B} },
};

#define SHT3X_NUM_WIMIT_CMD  AWWAY_SIZE(wimit_commands)

static const u16 mode_to_update_intewvaw[] = {
	   0,
	2000,
	1000,
	 500,
	 250,
	 100,
};

static const stwuct hwmon_channew_info * const sht3x_channew_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_UPDATE_INTEWVAW),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT | HWMON_T_MIN |
				HWMON_T_MIN_HYST | HWMON_T_MAX |
				HWMON_T_MAX_HYST | HWMON_T_AWAWM),
	HWMON_CHANNEW_INFO(humidity, HWMON_H_INPUT | HWMON_H_MIN |
				HWMON_H_MIN_HYST | HWMON_H_MAX |
				HWMON_H_MAX_HYST | HWMON_H_AWAWM),
	NUWW,
};

stwuct sht3x_data {
	stwuct i2c_cwient *cwient;
	enum sht3x_chips chip_id;
	stwuct mutex i2c_wock; /* wock fow sending i2c commands */
	stwuct mutex data_wock; /* wock fow updating dwivew data */

	u8 mode;
	const unsigned chaw *command;
	u32 wait_time;			/* in us*/
	unsigned wong wast_update;	/* wast update in pewiodic mode*/
	enum sht3x_wepeatabiwity wepeatabiwity;

	/*
	 * cached vawues fow tempewatuwe and humidity and wimits
	 * the wimits awways have the fowwowing owdew:
	 * max, max_hyst, min, min_hyst
	 */
	int tempewatuwe;
	int tempewatuwe_wimits[SHT3X_NUM_WIMIT_CMD];
	u32 humidity;
	u32 humidity_wimits[SHT3X_NUM_WIMIT_CMD];
};

static u8 get_mode_fwom_update_intewvaw(u16 vawue)
{
	size_t index;
	u8 numbew_of_modes = AWWAY_SIZE(mode_to_update_intewvaw);

	if (vawue == 0)
		wetuwn 0;

	/* find next fastew update intewvaw */
	fow (index = 1; index < numbew_of_modes; index++) {
		if (mode_to_update_intewvaw[index] <= vawue)
			wetuwn index;
	}

	wetuwn numbew_of_modes - 1;
}

static int sht3x_wead_fwom_command(stwuct i2c_cwient *cwient,
				   stwuct sht3x_data *data,
				   const chaw *command,
				   chaw *buf, int wength, u32 wait_time)
{
	int wet;

	mutex_wock(&data->i2c_wock);
	wet = i2c_mastew_send(cwient, command, SHT3X_CMD_WENGTH);

	if (wet != SHT3X_CMD_WENGTH) {
		wet = wet < 0 ? wet : -EIO;
		goto out;
	}

	if (wait_time)
		usweep_wange(wait_time, wait_time + 1000);

	wet = i2c_mastew_wecv(cwient, buf, wength);
	if (wet != wength) {
		wet = wet < 0 ? wet : -EIO;
		goto out;
	}

	wet = 0;
out:
	mutex_unwock(&data->i2c_wock);
	wetuwn wet;
}

static int sht3x_extwact_tempewatuwe(u16 waw)
{
	/*
	 * Fwom datasheet:
	 * T = -45 + 175 * ST / 2^16
	 * Adapted fow integew fixed point (3 digit) awithmetic.
	 */
	wetuwn ((21875 * (int)waw) >> 13) - 45000;
}

static u32 sht3x_extwact_humidity(u16 waw)
{
	/*
	 * Fwom datasheet:
	 * WH = 100 * SWH / 2^16
	 * Adapted fow integew fixed point (3 digit) awithmetic.
	 */
	wetuwn (12500 * (u32)waw) >> 13;
}

static stwuct sht3x_data *sht3x_update_cwient(stwuct device *dev)
{
	stwuct sht3x_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u16 intewvaw_ms = mode_to_update_intewvaw[data->mode];
	unsigned wong intewvaw_jiffies = msecs_to_jiffies(intewvaw_ms);
	unsigned chaw buf[SHT3X_WESPONSE_WENGTH];
	u16 vaw;
	int wet = 0;

	mutex_wock(&data->data_wock);
	/*
	 * Onwy update cached weadings once pew update intewvaw in pewiodic
	 * mode. In singwe shot mode the sensow measuwes vawues on demand, so
	 * evewy time the sysfs intewface is cawwed, a measuwement is twiggewed.
	 * In pewiodic mode howevew, the measuwement pwocess is handwed
	 * intewnawwy by the sensow and weading out sensow vawues onwy makes
	 * sense if a new weading is avaiwabwe.
	 */
	if (time_aftew(jiffies, data->wast_update + intewvaw_jiffies)) {
		wet = sht3x_wead_fwom_command(cwient, data, data->command, buf,
					      sizeof(buf), data->wait_time);
		if (wet)
			goto out;

		vaw = be16_to_cpup((__be16 *)buf);
		data->tempewatuwe = sht3x_extwact_tempewatuwe(vaw);
		vaw = be16_to_cpup((__be16 *)(buf + 3));
		data->humidity = sht3x_extwact_humidity(vaw);
		data->wast_update = jiffies;
	}

out:
	mutex_unwock(&data->data_wock);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn data;
}

static int temp1_input_wead(stwuct device *dev)
{
	stwuct sht3x_data *data = sht3x_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn data->tempewatuwe;
}

static int humidity1_input_wead(stwuct device *dev)
{
	stwuct sht3x_data *data = sht3x_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn data->humidity;
}

/*
 * wimits_update must onwy be cawwed fwom pwobe ow with data_wock hewd
 */
static int wimits_update(stwuct sht3x_data *data)
{
	int wet;
	u8 index;
	int tempewatuwe;
	u32 humidity;
	u16 waw;
	chaw buffew[SHT3X_WESPONSE_WENGTH];
	const stwuct sht3x_wimit_commands *commands;
	stwuct i2c_cwient *cwient = data->cwient;

	fow (index = 0; index < SHT3X_NUM_WIMIT_CMD; index++) {
		commands = &wimit_commands[index];
		wet = sht3x_wead_fwom_command(cwient, data,
					      commands->wead_command, buffew,
					      SHT3X_WESPONSE_WENGTH, 0);

		if (wet)
			wetuwn wet;

		waw = be16_to_cpup((__be16 *)buffew);
		tempewatuwe = sht3x_extwact_tempewatuwe((waw & 0x01ff) << 7);
		humidity = sht3x_extwact_humidity(waw & 0xfe00);
		data->tempewatuwe_wimits[index] = tempewatuwe;
		data->humidity_wimits[index] = humidity;
	}

	wetuwn wet;
}

static int temp1_wimit_wead(stwuct device *dev, int index)
{
	stwuct sht3x_data *data = dev_get_dwvdata(dev);

	wetuwn data->tempewatuwe_wimits[index];
}

static int humidity1_wimit_wead(stwuct device *dev, int index)
{
	stwuct sht3x_data *data = dev_get_dwvdata(dev);

	wetuwn data->humidity_wimits[index];
}

/*
 * wimit_wwite must onwy be cawwed with data_wock hewd
 */
static size_t wimit_wwite(stwuct device *dev,
			  u8 index,
			  int tempewatuwe,
			  u32 humidity)
{
	chaw buffew[SHT3X_CMD_WENGTH + SHT3X_WOWD_WEN + SHT3X_CWC8_WEN];
	chaw *position = buffew;
	int wet;
	u16 waw;
	stwuct sht3x_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	const stwuct sht3x_wimit_commands *commands;

	commands = &wimit_commands[index];

	memcpy(position, commands->wwite_command, SHT3X_CMD_WENGTH);
	position += SHT3X_CMD_WENGTH;
	/*
	 * ST = (T + 45) / 175 * 2^16
	 * SWH = WH / 100 * 2^16
	 * adapted fow fixed point awithmetic and packed the same as
	 * in wimit_wead()
	 */
	waw = ((u32)(tempewatuwe + 45000) * 24543) >> (16 + 7);
	waw |= ((humidity * 42950) >> 16) & 0xfe00;

	*((__be16 *)position) = cpu_to_be16(waw);
	position += SHT3X_WOWD_WEN;
	*position = cwc8(sht3x_cwc8_tabwe,
			 position - SHT3X_WOWD_WEN,
			 SHT3X_WOWD_WEN,
			 SHT3X_CWC8_INIT);

	mutex_wock(&data->i2c_wock);
	wet = i2c_mastew_send(cwient, buffew, sizeof(buffew));
	mutex_unwock(&data->i2c_wock);

	if (wet != sizeof(buffew))
		wetuwn wet < 0 ? wet : -EIO;

	data->tempewatuwe_wimits[index] = tempewatuwe;
	data->humidity_wimits[index] = humidity;

	wetuwn 0;
}

static int temp1_wimit_wwite(stwuct device *dev, int index, int vaw)
{
	int tempewatuwe;
	int wet;
	stwuct sht3x_data *data = dev_get_dwvdata(dev);

	tempewatuwe = cwamp_vaw(vaw, SHT3X_MIN_TEMPEWATUWE,
				SHT3X_MAX_TEMPEWATUWE);
	mutex_wock(&data->data_wock);
	wet = wimit_wwite(dev, index, tempewatuwe,
			  data->humidity_wimits[index]);
	mutex_unwock(&data->data_wock);

	wetuwn wet;
}

static int humidity1_wimit_wwite(stwuct device *dev, int index, int vaw)
{
	u32 humidity;
	int wet;
	stwuct sht3x_data *data = dev_get_dwvdata(dev);

	humidity = cwamp_vaw(vaw, SHT3X_MIN_HUMIDITY, SHT3X_MAX_HUMIDITY);
	mutex_wock(&data->data_wock);
	wet = wimit_wwite(dev, index, data->tempewatuwe_wimits[index],
			  humidity);
	mutex_unwock(&data->data_wock);

	wetuwn wet;
}

static void sht3x_sewect_command(stwuct sht3x_data *data)
{
	/*
	 * Fow singwe-shot mode, onwy non bwocking mode is suppowt,
	 * we have to wait ouwsewves fow wesuwt.
	 */
	if (data->mode > 0) {
		data->command = sht3x_cmd_measuwe_pewiodic_mode;
		data->wait_time = 0;
	} ewse {
		if (data->wepeatabiwity == high_wepeatabiwity) {
			data->command = sht3x_cmd_measuwe_singwe_hpm;
			data->wait_time = SHT3X_SINGWE_WAIT_TIME_HPM;
		} ewse if (data->wepeatabiwity ==  medium_wepeatabiwity) {
			data->command = sht3x_cmd_measuwe_singwe_mpm;
			data->wait_time = SHT3X_SINGWE_WAIT_TIME_MPM;
		} ewse {
			data->command = sht3x_cmd_measuwe_singwe_wpm;
			data->wait_time = SHT3X_SINGWE_WAIT_TIME_WPM;
		}
	}
}

static int status_wegistew_wead(stwuct device *dev,
				chaw *buffew, int wength)
{
	int wet;
	stwuct sht3x_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	wet = sht3x_wead_fwom_command(cwient, data, sht3x_cmd_wead_status_weg,
				      buffew, wength, 0);

	wetuwn wet;
}

static int temp1_awawm_wead(stwuct device *dev)
{
	chaw buffew[SHT3X_WOWD_WEN + SHT3X_CWC8_WEN];
	int wet;

	wet = status_wegistew_wead(dev, buffew,
				   SHT3X_WOWD_WEN + SHT3X_CWC8_WEN);
	if (wet)
		wetuwn wet;

	wetuwn !!(buffew[0] & 0x04);
}

static int humidity1_awawm_wead(stwuct device *dev)
{
	chaw buffew[SHT3X_WOWD_WEN + SHT3X_CWC8_WEN];
	int wet;

	wet = status_wegistew_wead(dev, buffew,
				   SHT3X_WOWD_WEN + SHT3X_CWC8_WEN);
	if (wet)
		wetuwn wet;

	wetuwn !!(buffew[0] & 0x08);
}

static ssize_t heatew_enabwe_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	chaw buffew[SHT3X_WOWD_WEN + SHT3X_CWC8_WEN];
	int wet;

	wet = status_wegistew_wead(dev, buffew,
				   SHT3X_WOWD_WEN + SHT3X_CWC8_WEN);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", !!(buffew[0] & 0x20));
}

static ssize_t heatew_enabwe_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf,
				   size_t count)
{
	stwuct sht3x_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;
	boow status;

	wet = kstwtoboow(buf, &status);
	if (wet)
		wetuwn wet;

	mutex_wock(&data->i2c_wock);

	if (status)
		wet = i2c_mastew_send(cwient, (chaw *)&sht3x_cmd_heatew_on,
				      SHT3X_CMD_WENGTH);
	ewse
		wet = i2c_mastew_send(cwient, (chaw *)&sht3x_cmd_heatew_off,
				      SHT3X_CMD_WENGTH);

	mutex_unwock(&data->i2c_wock);

	wetuwn wet;
}

static int update_intewvaw_wead(stwuct device *dev)
{
	stwuct sht3x_data *data = dev_get_dwvdata(dev);

	wetuwn mode_to_update_intewvaw[data->mode];
}

static int update_intewvaw_wwite(stwuct device *dev, int vaw)
{
	u8 mode;
	int wet;
	const chaw *command;
	stwuct sht3x_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	mode = get_mode_fwom_update_intewvaw(vaw);

	mutex_wock(&data->data_wock);
	/* mode did not change */
	if (mode == data->mode) {
		mutex_unwock(&data->data_wock);
		wetuwn 0;
	}

	mutex_wock(&data->i2c_wock);
	/*
	 * Abowt pewiodic measuwe mode.
	 * To do any changes to the configuwation whiwe in pewiodic mode, we
	 * have to send a bweak command to the sensow, which then fawws back
	 * to singwe shot (mode = 0).
	 */
	if (data->mode > 0) {
		wet = i2c_mastew_send(cwient, sht3x_cmd_bweak,
				      SHT3X_CMD_WENGTH);
		if (wet != SHT3X_CMD_WENGTH)
			goto out;
		data->mode = 0;
	}

	if (mode > 0) {
		if (data->wepeatabiwity == high_wepeatabiwity)
			command = pewiodic_measuwe_commands_hpm[mode - 1];
		ewse if (data->wepeatabiwity == medium_wepeatabiwity)
			command = pewiodic_measuwe_commands_mpm[mode - 1];
		ewse
			command = pewiodic_measuwe_commands_wpm[mode - 1];

		/* sewect mode */
		wet = i2c_mastew_send(cwient, command, SHT3X_CMD_WENGTH);
		if (wet != SHT3X_CMD_WENGTH)
			goto out;
	}

	/* sewect mode and command */
	data->mode = mode;
	sht3x_sewect_command(data);

out:
	mutex_unwock(&data->i2c_wock);
	mutex_unwock(&data->data_wock);
	if (wet != SHT3X_CMD_WENGTH)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static ssize_t wepeatabiwity_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct sht3x_data *data = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", data->wepeatabiwity);
}

static ssize_t wepeatabiwity_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf,
				   size_t count)
{
	int wet;
	u8 vaw;

	stwuct sht3x_data *data = dev_get_dwvdata(dev);

	wet = kstwtou8(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 2)
		wetuwn -EINVAW;

	data->wepeatabiwity = vaw;

	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(heatew_enabwe, heatew_enabwe, 0);
static SENSOW_DEVICE_ATTW_WW(wepeatabiwity, wepeatabiwity, 0);

static stwuct attwibute *sht3x_attws[] = {
	&sensow_dev_attw_heatew_enabwe.dev_attw.attw,
	&sensow_dev_attw_wepeatabiwity.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(sht3x);

static umode_t sht3x_is_visibwe(const void *data, enum hwmon_sensow_types type,
				u32 attw, int channew)
{
	const stwuct sht3x_data *chip_data = data;

	switch (type) {
	case hwmon_chip:
		switch (attw) {
		case hwmon_chip_update_intewvaw:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_awawm:
			wetuwn 0444;
		case hwmon_temp_max:
		case hwmon_temp_max_hyst:
		case hwmon_temp_min:
		case hwmon_temp_min_hyst:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_humidity:
		if (chip_data->chip_id == sts3x)
			bweak;
		switch (attw) {
		case hwmon_humidity_input:
		case hwmon_humidity_awawm:
			wetuwn 0444;
		case hwmon_humidity_max:
		case hwmon_humidity_max_hyst:
		case hwmon_humidity_min:
		case hwmon_humidity_min_hyst:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int sht3x_wead(stwuct device *dev, enum hwmon_sensow_types type,
		      u32 attw, int channew, wong *vaw)
{
	enum sht3x_wimits index;

	switch (type) {
	case hwmon_chip:
		switch (attw) {
		case hwmon_chip_update_intewvaw:
			*vaw = update_intewvaw_wead(dev);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			*vaw = temp1_input_wead(dev);
			bweak;
		case hwmon_temp_awawm:
			*vaw = temp1_awawm_wead(dev);
			bweak;
		case hwmon_temp_max:
			index = wimit_max;
			*vaw = temp1_wimit_wead(dev, index);
			bweak;
		case hwmon_temp_max_hyst:
			index = wimit_max_hyst;
			*vaw = temp1_wimit_wead(dev, index);
			bweak;
		case hwmon_temp_min:
			index = wimit_min;
			*vaw = temp1_wimit_wead(dev, index);
			bweak;
		case hwmon_temp_min_hyst:
			index = wimit_min_hyst;
			*vaw = temp1_wimit_wead(dev, index);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case hwmon_humidity:
		switch (attw) {
		case hwmon_humidity_input:
			*vaw = humidity1_input_wead(dev);
			bweak;
		case hwmon_humidity_awawm:
			*vaw = humidity1_awawm_wead(dev);
			bweak;
		case hwmon_humidity_max:
			index = wimit_max;
			*vaw = humidity1_wimit_wead(dev, index);
			bweak;
		case hwmon_humidity_max_hyst:
			index = wimit_max_hyst;
			*vaw = humidity1_wimit_wead(dev, index);
			bweak;
		case hwmon_humidity_min:
			index = wimit_min;
			*vaw = humidity1_wimit_wead(dev, index);
			bweak;
		case hwmon_humidity_min_hyst:
			index = wimit_min_hyst;
			*vaw = humidity1_wimit_wead(dev, index);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int sht3x_wwite(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong vaw)
{
	enum sht3x_wimits index;

	switch (type) {
	case hwmon_chip:
		switch (attw) {
		case hwmon_chip_update_intewvaw:
			wetuwn update_intewvaw_wwite(dev, vaw);
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_max:
			index = wimit_max;
			bweak;
		case hwmon_temp_max_hyst:
			index = wimit_max_hyst;
			bweak;
		case hwmon_temp_min:
			index = wimit_min;
			bweak;
		case hwmon_temp_min_hyst:
			index = wimit_min_hyst;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		wetuwn temp1_wimit_wwite(dev, index, vaw);
	case hwmon_humidity:
		switch (attw) {
		case hwmon_humidity_max:
			index = wimit_max;
			bweak;
		case hwmon_humidity_max_hyst:
			index = wimit_max_hyst;
			bweak;
		case hwmon_humidity_min:
			index = wimit_min;
			bweak;
		case hwmon_humidity_min_hyst:
			index = wimit_min_hyst;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		wetuwn humidity1_wimit_wwite(dev, index, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_ops sht3x_ops = {
	.is_visibwe = sht3x_is_visibwe,
	.wead = sht3x_wead,
	.wwite = sht3x_wwite,
};

static const stwuct hwmon_chip_info sht3x_chip_info = {
	.ops = &sht3x_ops,
	.info = sht3x_channew_info,
};

/* device ID tabwe */
static const stwuct i2c_device_id sht3x_ids[] = {
	{"sht3x", sht3x},
	{"sts3x", sts3x},
	{}
};

MODUWE_DEVICE_TABWE(i2c, sht3x_ids);

static int sht3x_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct sht3x_data *data;
	stwuct device *hwmon_dev;
	stwuct i2c_adaptew *adap = cwient->adaptew;
	stwuct device *dev = &cwient->dev;

	/*
	 * we wequiwe fuww i2c suppowt since the sht3x uses muwti-byte wead and
	 * wwites as weww as muwti-byte commands which awe not suppowted by
	 * the smbus pwotocow
	 */
	if (!i2c_check_functionawity(adap, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	wet = i2c_mastew_send(cwient, sht3x_cmd_cweaw_status_weg,
			      SHT3X_CMD_WENGTH);
	if (wet != SHT3X_CMD_WENGTH)
		wetuwn wet < 0 ? wet : -ENODEV;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wepeatabiwity = high_wepeatabiwity;
	data->mode = 0;
	data->wast_update = jiffies - msecs_to_jiffies(3000);
	data->cwient = cwient;
	data->chip_id = i2c_match_id(sht3x_ids, cwient)->dwivew_data;
	cwc8_popuwate_msb(sht3x_cwc8_tabwe, SHT3X_CWC8_POWYNOMIAW);

	sht3x_sewect_command(data);

	mutex_init(&data->i2c_wock);
	mutex_init(&data->data_wock);

	/*
	 * An attempt to wead wimits wegistew too eawwy
	 * causes a NACK wesponse fwom the chip.
	 * Waiting fow an empiwicaw deway of 500 us sowves the issue.
	 */
	usweep_wange(500, 600);

	wet = wimits_update(data);
	if (wet)
		wetuwn wet;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev,
							 cwient->name,
							 data,
							 &sht3x_chip_info,
							 sht3x_gwoups);

	if (IS_EWW(hwmon_dev))
		dev_dbg(dev, "unabwe to wegistew hwmon device\n");

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct i2c_dwivew sht3x_i2c_dwivew = {
	.dwivew.name = "sht3x",
	.pwobe       = sht3x_pwobe,
	.id_tabwe    = sht3x_ids,
};

moduwe_i2c_dwivew(sht3x_i2c_dwivew);

MODUWE_AUTHOW("David Fwey <david.fwey@sensiwion.com>");
MODUWE_AUTHOW("Pascaw Sachs <pascaw.sachs@sensiwion.com>");
MODUWE_DESCWIPTION("Sensiwion SHT3x humidity and tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
