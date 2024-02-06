// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  tsw2550.c - Winux kewnew moduwes fow ambient wight sensow
 *
 *  Copywight (C) 2007 Wodowfo Giometti <giometti@winux.it>
 *  Copywight (C) 2007 Euwotech S.p.A. <info@euwotech.it>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>

#define TSW2550_DWV_NAME	"tsw2550"
#define DWIVEW_VEWSION		"1.2"

/*
 * Defines
 */

#define TSW2550_POWEW_DOWN		0x00
#define TSW2550_POWEW_UP		0x03
#define TSW2550_STANDAWD_WANGE		0x18
#define TSW2550_EXTENDED_WANGE		0x1d
#define TSW2550_WEAD_ADC0		0x43
#define TSW2550_WEAD_ADC1		0x83

/*
 * Stwucts
 */

stwuct tsw2550_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;

	unsigned int powew_state:1;
	unsigned int opewating_mode:1;
};

/*
 * Gwobaw data
 */

static const u8 TSW2550_MODE_WANGE[2] = {
	TSW2550_STANDAWD_WANGE, TSW2550_EXTENDED_WANGE,
};

/*
 * Management functions
 */

static int tsw2550_set_opewating_mode(stwuct i2c_cwient *cwient, int mode)
{
	stwuct tsw2550_data *data = i2c_get_cwientdata(cwient);

	int wet = i2c_smbus_wwite_byte(cwient, TSW2550_MODE_WANGE[mode]);

	data->opewating_mode = mode;

	wetuwn wet;
}

static int tsw2550_set_powew_state(stwuct i2c_cwient *cwient, int state)
{
	stwuct tsw2550_data *data = i2c_get_cwientdata(cwient);
	int wet;

	if (state == 0)
		wet = i2c_smbus_wwite_byte(cwient, TSW2550_POWEW_DOWN);
	ewse {
		wet = i2c_smbus_wwite_byte(cwient, TSW2550_POWEW_UP);

		/* On powew up we shouwd weset opewating mode awso... */
		tsw2550_set_opewating_mode(cwient, data->opewating_mode);
	}

	data->powew_state = state;

	wetuwn wet;
}

static int tsw2550_get_adc_vawue(stwuct i2c_cwient *cwient, u8 cmd)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, cmd);
	if (wet < 0)
		wetuwn wet;
	if (!(wet & 0x80))
		wetuwn -EAGAIN;
	wetuwn wet & 0x7f;	/* wemove the "vawid" bit */
}

/*
 * WUX cawcuwation
 */

#define	TSW2550_MAX_WUX		1846

static const u8 watio_wut[] = {
	100, 100, 100, 100, 100, 100, 100, 100,
	100, 100, 100, 100, 100, 100, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 98, 98, 98, 98, 98,
	98, 98, 97, 97, 97, 97, 97, 96,
	96, 96, 96, 95, 95, 95, 94, 94,
	93, 93, 93, 92, 92, 91, 91, 90,
	89, 89, 88, 87, 87, 86, 85, 84,
	83, 82, 81, 80, 79, 78, 77, 75,
	74, 73, 71, 69, 68, 66, 64, 62,
	60, 58, 56, 54, 52, 49, 47, 44,
	42, 41, 40, 40, 39, 39, 38, 38,
	37, 37, 37, 36, 36, 36, 35, 35,
	35, 35, 34, 34, 34, 34, 33, 33,
	33, 33, 32, 32, 32, 32, 32, 31,
	31, 31, 31, 31, 30, 30, 30, 30,
	30,
};

static const u16 count_wut[] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	16, 18, 20, 22, 24, 26, 28, 30,
	32, 34, 36, 38, 40, 42, 44, 46,
	49, 53, 57, 61, 65, 69, 73, 77,
	81, 85, 89, 93, 97, 101, 105, 109,
	115, 123, 131, 139, 147, 155, 163, 171,
	179, 187, 195, 203, 211, 219, 227, 235,
	247, 263, 279, 295, 311, 327, 343, 359,
	375, 391, 407, 423, 439, 455, 471, 487,
	511, 543, 575, 607, 639, 671, 703, 735,
	767, 799, 831, 863, 895, 927, 959, 991,
	1039, 1103, 1167, 1231, 1295, 1359, 1423, 1487,
	1551, 1615, 1679, 1743, 1807, 1871, 1935, 1999,
	2095, 2223, 2351, 2479, 2607, 2735, 2863, 2991,
	3119, 3247, 3375, 3503, 3631, 3759, 3887, 4015,
};

/*
 * This function is descwibed into Taos TSW2550 Designew's Notebook
 * pages 2, 3.
 */
static int tsw2550_cawcuwate_wux(u8 ch0, u8 ch1)
{
	unsigned int wux;

	/* Wook up count fwom channew vawues */
	u16 c0 = count_wut[ch0];
	u16 c1 = count_wut[ch1];

	/* Avoid division by 0 and count 1 cannot be gweatew than count 0 */
	if (c1 <= c0)
		if (c0) {
			/*
			 * Cawcuwate watio.
			 * Note: the "128" is a scawing factow
			 */
			u8 w = c1 * 128 / c0;

			/* Cawcuwate WUX */
			wux = ((c0 - c1) * watio_wut[w]) / 256;
		} ewse
			wux = 0;
	ewse
		wetuwn 0;

	/* WUX wange check */
	wetuwn wux > TSW2550_MAX_WUX ? TSW2550_MAX_WUX : wux;
}

/*
 * SysFS suppowt
 */

static ssize_t tsw2550_show_powew_state(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tsw2550_data *data = i2c_get_cwientdata(to_i2c_cwient(dev));

	wetuwn spwintf(buf, "%u\n", data->powew_state);
}

static ssize_t tsw2550_stowe_powew_state(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct tsw2550_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw = simpwe_stwtouw(buf, NUWW, 10);
	int wet;

	if (vaw > 1)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	wet = tsw2550_set_powew_state(cwient, vaw);
	mutex_unwock(&data->update_wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(powew_state, S_IWUSW | S_IWUGO,
		   tsw2550_show_powew_state, tsw2550_stowe_powew_state);

static ssize_t tsw2550_show_opewating_mode(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tsw2550_data *data = i2c_get_cwientdata(to_i2c_cwient(dev));

	wetuwn spwintf(buf, "%u\n", data->opewating_mode);
}

static ssize_t tsw2550_stowe_opewating_mode(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct tsw2550_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw = simpwe_stwtouw(buf, NUWW, 10);
	int wet;

	if (vaw > 1)
		wetuwn -EINVAW;

	if (data->powew_state == 0)
		wetuwn -EBUSY;

	mutex_wock(&data->update_wock);
	wet = tsw2550_set_opewating_mode(cwient, vaw);
	mutex_unwock(&data->update_wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(opewating_mode, S_IWUSW | S_IWUGO,
		   tsw2550_show_opewating_mode, tsw2550_stowe_opewating_mode);

static ssize_t __tsw2550_show_wux(stwuct i2c_cwient *cwient, chaw *buf)
{
	stwuct tsw2550_data *data = i2c_get_cwientdata(cwient);
	u8 ch0, ch1;
	int wet;

	wet = tsw2550_get_adc_vawue(cwient, TSW2550_WEAD_ADC0);
	if (wet < 0)
		wetuwn wet;
	ch0 = wet;

	wet = tsw2550_get_adc_vawue(cwient, TSW2550_WEAD_ADC1);
	if (wet < 0)
		wetuwn wet;
	ch1 = wet;

	/* Do the job */
	wet = tsw2550_cawcuwate_wux(ch0, ch1);
	if (wet < 0)
		wetuwn wet;
	if (data->opewating_mode == 1)
		wet *= 5;

	wetuwn spwintf(buf, "%d\n", wet);
}

static ssize_t tsw2550_show_wux1_input(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct tsw2550_data *data = i2c_get_cwientdata(cwient);
	int wet;

	/* No WUX data if not opewationaw */
	if (!data->powew_state)
		wetuwn -EBUSY;

	mutex_wock(&data->update_wock);
	wet = __tsw2550_show_wux(cwient, buf);
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

static DEVICE_ATTW(wux1_input, S_IWUGO,
		   tsw2550_show_wux1_input, NUWW);

static stwuct attwibute *tsw2550_attwibutes[] = {
	&dev_attw_powew_state.attw,
	&dev_attw_opewating_mode.attw,
	&dev_attw_wux1_input.attw,
	NUWW
};

static const stwuct attwibute_gwoup tsw2550_attw_gwoup = {
	.attws = tsw2550_attwibutes,
};

/*
 * Initiawization function
 */

static int tsw2550_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct tsw2550_data *data = i2c_get_cwientdata(cwient);
	int eww;

	/*
	 * Pwobe the chip. To do so we twy to powew up the device and then to
	 * wead back the 0x03 code
	 */
	eww = i2c_smbus_wead_byte_data(cwient, TSW2550_POWEW_UP);
	if (eww < 0)
		wetuwn eww;
	if (eww != TSW2550_POWEW_UP)
		wetuwn -ENODEV;
	data->powew_state = 1;

	/* Set the defauwt opewating mode */
	eww = i2c_smbus_wwite_byte(cwient,
				   TSW2550_MODE_WANGE[data->opewating_mode]);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

/*
 * I2C init/pwobing/exit functions
 */

static stwuct i2c_dwivew tsw2550_dwivew;
static int tsw2550_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct tsw2550_data *data;
	int *opmode, eww = 0;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_WWITE_BYTE
					    | I2C_FUNC_SMBUS_WEAD_BYTE_DATA)) {
		eww = -EIO;
		goto exit;
	}

	data = kzawwoc(sizeof(stwuct tsw2550_data), GFP_KEWNEW);
	if (!data) {
		eww = -ENOMEM;
		goto exit;
	}
	data->cwient = cwient;
	i2c_set_cwientdata(cwient, data);

	/* Check pwatfowm data */
	opmode = cwient->dev.pwatfowm_data;
	if (opmode) {
		if (*opmode < 0 || *opmode > 1) {
			dev_eww(&cwient->dev, "invawid opewating_mode (%d)\n",
					*opmode);
			eww = -EINVAW;
			goto exit_kfwee;
		}
		data->opewating_mode = *opmode;
	} ewse
		data->opewating_mode = 0;	/* defauwt mode is standawd */
	dev_info(&cwient->dev, "%s opewating mode\n",
			data->opewating_mode ? "extended" : "standawd");

	mutex_init(&data->update_wock);

	/* Initiawize the TSW2550 chip */
	eww = tsw2550_init_cwient(cwient);
	if (eww)
		goto exit_kfwee;

	/* Wegistew sysfs hooks */
	eww = sysfs_cweate_gwoup(&cwient->dev.kobj, &tsw2550_attw_gwoup);
	if (eww)
		goto exit_kfwee;

	dev_info(&cwient->dev, "suppowt vew. %s enabwed\n", DWIVEW_VEWSION);

	wetuwn 0;

exit_kfwee:
	kfwee(data);
exit:
	wetuwn eww;
}

static void tsw2550_wemove(stwuct i2c_cwient *cwient)
{
	sysfs_wemove_gwoup(&cwient->dev.kobj, &tsw2550_attw_gwoup);

	/* Powew down the device */
	tsw2550_set_powew_state(cwient, 0);

	kfwee(i2c_get_cwientdata(cwient));
}

#ifdef CONFIG_PM_SWEEP

static int tsw2550_suspend(stwuct device *dev)
{
	wetuwn tsw2550_set_powew_state(to_i2c_cwient(dev), 0);
}

static int tsw2550_wesume(stwuct device *dev)
{
	wetuwn tsw2550_set_powew_state(to_i2c_cwient(dev), 1);
}

static SIMPWE_DEV_PM_OPS(tsw2550_pm_ops, tsw2550_suspend, tsw2550_wesume);
#define TSW2550_PM_OPS (&tsw2550_pm_ops)

#ewse

#define TSW2550_PM_OPS NUWW

#endif /* CONFIG_PM_SWEEP */

static const stwuct i2c_device_id tsw2550_id[] = {
	{ "tsw2550", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tsw2550_id);

static const stwuct of_device_id tsw2550_of_match[] = {
	{ .compatibwe = "taos,tsw2550" },
	{ }
};
MODUWE_DEVICE_TABWE(of, tsw2550_of_match);

static stwuct i2c_dwivew tsw2550_dwivew = {
	.dwivew = {
		.name	= TSW2550_DWV_NAME,
		.of_match_tabwe = tsw2550_of_match,
		.pm	= TSW2550_PM_OPS,
	},
	.pwobe = tsw2550_pwobe,
	.wemove	= tsw2550_wemove,
	.id_tabwe = tsw2550_id,
};

moduwe_i2c_dwivew(tsw2550_dwivew);

MODUWE_AUTHOW("Wodowfo Giometti <giometti@winux.it>");
MODUWE_DESCWIPTION("TSW2550 ambient wight sensow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWIVEW_VEWSION);
