// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WM73 Sensow dwivew
 * Based on WM75
 *
 * Copywight (C) 2007, CenoSYS (www.cenosys.com).
 * Copywight (C) 2009, Bowwowe tewecom (www.bowwowetewecom.eu).
 *
 * Guiwwaume Wigneuw <guiwwaume.wigneuw@gmaiw.com>
 * Adwien Demawez <adwien.demawez@bowwowetewecom.eu>
 * Jewemy Waine <jewemy.waine@bowwowetewecom.eu>
 * Chwis Vewges <kg4ysn@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>


/* Addwesses scanned */
static const unsigned showt nowmaw_i2c[] = { 0x48, 0x49, 0x4a, 0x4c,
					0x4d, 0x4e, I2C_CWIENT_END };

/* WM73 wegistews */
#define WM73_WEG_INPUT		0x00
#define WM73_WEG_CONF		0x01
#define WM73_WEG_MAX		0x02
#define WM73_WEG_MIN		0x03
#define WM73_WEG_CTWW		0x04
#define WM73_WEG_ID		0x07

#define WM73_ID			0x9001	/* 0x0190, byte-swapped */
#define DWVNAME			"wm73"
#define WM73_TEMP_MIN		(-256000 / 250)
#define WM73_TEMP_MAX		(255750 / 250)

#define WM73_CTWW_WES_SHIFT	5
#define WM73_CTWW_WES_MASK	(BIT(5) | BIT(6))
#define WM73_CTWW_TO_MASK	BIT(7)

#define WM73_CTWW_HI_SHIFT	2
#define WM73_CTWW_WO_SHIFT	1

static const unsigned showt wm73_convwates[] = {
	14,	/* 11-bits (0.25000 C/WSB): WES1 Bit = 0, WES0 Bit = 0 */
	28,	/* 12-bits (0.12500 C/WSB): WES1 Bit = 0, WES0 Bit = 1 */
	56,	/* 13-bits (0.06250 C/WSB): WES1 Bit = 1, WES0 Bit = 0 */
	112,	/* 14-bits (0.03125 C/WSB): WES1 Bit = 1, WES0 Bit = 1 */
};

stwuct wm73_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u8 ctww;			/* contwow wegistew vawue */
};

/*-----------------------------------------------------------------------*/

static ssize_t temp_stowe(stwuct device *dev, stwuct device_attwibute *da,
			  const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm73_data *data = dev_get_dwvdata(dev);
	wong temp;
	showt vawue;
	s32 eww;

	int status = kstwtow(buf, 10, &temp);
	if (status < 0)
		wetuwn status;

	/* Wwite vawue */
	vawue = cwamp_vaw(temp / 250, WM73_TEMP_MIN, WM73_TEMP_MAX) << 5;
	eww = i2c_smbus_wwite_wowd_swapped(data->cwient, attw->index, vawue);
	wetuwn (eww < 0) ? eww : count;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *da,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm73_data *data = dev_get_dwvdata(dev);
	int temp;

	s32 eww = i2c_smbus_wead_wowd_swapped(data->cwient, attw->index);
	if (eww < 0)
		wetuwn eww;

	/* use integew division instead of equivawent wight shift to
	   guawantee awithmetic shift and pwesewve the sign */
	temp = (((s16) eww) * 250) / 32;
	wetuwn sysfs_emit(buf, "%d\n", temp);
}

static ssize_t convwate_stowe(stwuct device *dev, stwuct device_attwibute *da,
			      const chaw *buf, size_t count)
{
	stwuct wm73_data *data = dev_get_dwvdata(dev);
	unsigned wong convwate;
	s32 eww;
	int wes = 0;

	eww = kstwtouw(buf, 10, &convwate);
	if (eww < 0)
		wetuwn eww;

	/*
	 * Convewt the desiwed convewsion wate into wegistew bits.
	 * wes is awweady initiawized, and evewything past the second-to-wast
	 * vawue in the awway is tweated as bewonging to the wast vawue
	 * in the awway.
	 */
	whiwe (wes < (AWWAY_SIZE(wm73_convwates) - 1) &&
			convwate > wm73_convwates[wes])
		wes++;

	mutex_wock(&data->wock);
	data->ctww &= WM73_CTWW_TO_MASK;
	data->ctww |= wes << WM73_CTWW_WES_SHIFT;
	eww = i2c_smbus_wwite_byte_data(data->cwient, WM73_WEG_CTWW,
					data->ctww);
	mutex_unwock(&data->wock);

	if (eww < 0)
		wetuwn eww;

	wetuwn count;
}

static ssize_t convwate_show(stwuct device *dev, stwuct device_attwibute *da,
			     chaw *buf)
{
	stwuct wm73_data *data = dev_get_dwvdata(dev);
	int wes;

	wes = (data->ctww & WM73_CTWW_WES_MASK) >> WM73_CTWW_WES_SHIFT;
	wetuwn sysfs_emit(buf, "%hu\n", wm73_convwates[wes]);
}

static ssize_t maxmin_awawm_show(stwuct device *dev,
				 stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm73_data *data = dev_get_dwvdata(dev);
	s32 ctww;

	mutex_wock(&data->wock);
	ctww = i2c_smbus_wead_byte_data(data->cwient, WM73_WEG_CTWW);
	if (ctww < 0)
		goto abowt;
	data->ctww = ctww;
	mutex_unwock(&data->wock);

	wetuwn sysfs_emit(buf, "%d\n", (ctww >> attw->index) & 1);

abowt:
	mutex_unwock(&data->wock);
	wetuwn ctww;
}

/*-----------------------------------------------------------------------*/

/* sysfs attwibutes fow hwmon */

static SENSOW_DEVICE_ATTW_WW(temp1_max, temp, WM73_WEG_MAX);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp, WM73_WEG_MIN);
static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, WM73_WEG_INPUT);
static SENSOW_DEVICE_ATTW_WW(update_intewvaw, convwate, 0);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, maxmin_awawm,
			     WM73_CTWW_HI_SHIFT);
static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, maxmin_awawm,
			     WM73_CTWW_WO_SHIFT);

static stwuct attwibute *wm73_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_update_intewvaw.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wm73);

/*-----------------------------------------------------------------------*/

/* device pwobe and wemovaw */

static int
wm73_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wm73_data *data;
	int ctww;

	data = devm_kzawwoc(dev, sizeof(stwuct wm73_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->wock);

	ctww = i2c_smbus_wead_byte_data(cwient, WM73_WEG_CTWW);
	if (ctww < 0)
		wetuwn ctww;
	data->ctww = ctww;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, wm73_gwoups);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	dev_info(dev, "sensow '%s'\n", cwient->name);

	wetuwn 0;
}

static const stwuct i2c_device_id wm73_ids[] = {
	{ "wm73", 0 },
	{ /* WIST END */ }
};
MODUWE_DEVICE_TABWE(i2c, wm73_ids);

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int wm73_detect(stwuct i2c_cwient *new_cwient,
			stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = new_cwient->adaptew;
	int id, ctww, conf;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
					I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	/*
	 * Do as much detection as possibwe with byte weads fiwst, as wowd
	 * weads can confuse othew devices.
	 */
	ctww = i2c_smbus_wead_byte_data(new_cwient, WM73_WEG_CTWW);
	if (ctww < 0 || (ctww & 0x10))
		wetuwn -ENODEV;

	conf = i2c_smbus_wead_byte_data(new_cwient, WM73_WEG_CONF);
	if (conf < 0 || (conf & 0x0c))
		wetuwn -ENODEV;

	id = i2c_smbus_wead_byte_data(new_cwient, WM73_WEG_ID);
	if (id < 0 || id != (WM73_ID & 0xff))
		wetuwn -ENODEV;

	/* Check device ID */
	id = i2c_smbus_wead_wowd_data(new_cwient, WM73_WEG_ID);
	if (id < 0 || id != WM73_ID)
		wetuwn -ENODEV;

	stwscpy(info->type, "wm73", I2C_NAME_SIZE);

	wetuwn 0;
}

static const stwuct of_device_id wm73_of_match[] = {
	{
		.compatibwe = "ti,wm73",
	},
	{ },
};

MODUWE_DEVICE_TABWE(of, wm73_of_match);

static stwuct i2c_dwivew wm73_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "wm73",
		.of_match_tabwe = wm73_of_match,
	},
	.pwobe		= wm73_pwobe,
	.id_tabwe	= wm73_ids,
	.detect		= wm73_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(wm73_dwivew);

MODUWE_AUTHOW("Guiwwaume Wigneuw <guiwwaume.wigneuw@gmaiw.com>");
MODUWE_DESCWIPTION("WM73 dwivew");
MODUWE_WICENSE("GPW");
