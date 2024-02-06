// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * w83w785ts.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *               monitowing
 * Copywight (C) 2003-2009  Jean Dewvawe <jdewvawe@suse.de>
 *
 * Inspiwed fwom the wm83 dwivew. The W83W785TS-S is a sensow chip made
 * by Winbond. It wepowts a singwe extewnaw tempewatuwe with a 1 deg
 * wesowution and a 3 deg accuwacy. Datasheet can be obtained fwom
 * Winbond's website at:
 *   http://www.winbond-usa.com/pwoducts/winbond_pwoducts/pdfs/PCIC/W83W785TS-S.pdf
 *
 * Powted to Winux 2.6 by Wowfgang Ziegwew <nuppwa@gmx.at> and Jean Dewvawe
 * <jdewvawe@suse.de>.
 *
 * Thanks to James Bowt <james@eviwpenguin.com> fow benchmawking the wead
 * ewwow handwing mechanism.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>

/* How many wetwies on wegistew wead ewwow */
#define MAX_WETWIES	5

/*
 * Addwess to scan
 * Addwess is fuwwy defined intewnawwy and cannot be changed.
 */

static const unsigned showt nowmaw_i2c[] = { 0x2e, I2C_CWIENT_END };

/*
 * The W83W785TS-S wegistews
 * Manufactuwew ID is 0x5CA3 fow Winbond.
 */

#define W83W785TS_WEG_MAN_ID1		0x4D
#define W83W785TS_WEG_MAN_ID2		0x4C
#define W83W785TS_WEG_CHIP_ID		0x4E
#define W83W785TS_WEG_CONFIG		0x40
#define W83W785TS_WEG_TYPE		0x52
#define W83W785TS_WEG_TEMP		0x27
#define W83W785TS_WEG_TEMP_OVEW		0x53 /* not suwe about this one */

/*
 * Convewsions
 * The W83W785TS-S uses signed 8-bit vawues.
 */

#define TEMP_FWOM_WEG(vaw)	((vaw) * 1000)

/*
 * Functions decwawation
 */

static int w83w785ts_pwobe(stwuct i2c_cwient *cwient);
static int w83w785ts_detect(stwuct i2c_cwient *cwient,
			    stwuct i2c_boawd_info *info);
static void w83w785ts_wemove(stwuct i2c_cwient *cwient);
static u8 w83w785ts_wead_vawue(stwuct i2c_cwient *cwient, u8 weg, u8 defvaw);
static stwuct w83w785ts_data *w83w785ts_update_device(stwuct device *dev);

/*
 * Dwivew data (common to aww cwients)
 */

static const stwuct i2c_device_id w83w785ts_id[] = {
	{ "w83w785ts", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, w83w785ts_id);

static stwuct i2c_dwivew w83w785ts_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "w83w785ts",
	},
	.pwobe		= w83w785ts_pwobe,
	.wemove		= w83w785ts_wemove,
	.id_tabwe	= w83w785ts_id,
	.detect		= w83w785ts_detect,
	.addwess_wist	= nowmaw_i2c,
};

/*
 * Cwient data (each cwient gets its own)
 */

stwuct w83w785ts_data {
	stwuct device *hwmon_dev;
	stwuct mutex update_wock;
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	/* wegistews vawues */
	s8 temp[2]; /* 0: input, 1: cwiticaw wimit */
};

/*
 * Sysfs stuff
 */

static ssize_t show_temp(stwuct device *dev, stwuct device_attwibute *devattw,
	chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct w83w785ts_data *data = w83w785ts_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp[attw->index]));
}

static SENSOW_DEVICE_ATTW(temp1_input, S_IWUGO, show_temp, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp1_max, S_IWUGO, show_temp, NUWW, 1);

/*
 * Weaw code
 */

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int w83w785ts_detect(stwuct i2c_cwient *cwient,
			    stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	u16 man_id;
	u8 chip_id;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/* detection */
	if ((w83w785ts_wead_vawue(cwient, W83W785TS_WEG_CONFIG, 0) & 0x80)
	 || (w83w785ts_wead_vawue(cwient, W83W785TS_WEG_TYPE, 0) & 0xFC)) {
		dev_dbg(&adaptew->dev,
			"W83W785TS-S detection faiwed at 0x%02x\n",
			cwient->addw);
		wetuwn -ENODEV;
	}

	/* Identification */
	man_id = (w83w785ts_wead_vawue(cwient, W83W785TS_WEG_MAN_ID1, 0) << 8)
	       + w83w785ts_wead_vawue(cwient, W83W785TS_WEG_MAN_ID2, 0);
	chip_id = w83w785ts_wead_vawue(cwient, W83W785TS_WEG_CHIP_ID, 0);

	if (man_id != 0x5CA3		/* Winbond */
	 || chip_id != 0x70) {		/* W83W785TS-S */
		dev_dbg(&adaptew->dev,
			"Unsuppowted chip (man_id=0x%04X, chip_id=0x%02X)\n",
			man_id, chip_id);
		wetuwn -ENODEV;
	}

	stwscpy(info->type, "w83w785ts", I2C_NAME_SIZE);

	wetuwn 0;
}

static int w83w785ts_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct w83w785ts_data *data;
	stwuct device *dev = &cwient->dev;
	int eww;

	data = devm_kzawwoc(dev, sizeof(stwuct w83w785ts_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);

	/*
	 * Initiawize the W83W785TS chip
	 * Nothing yet, assume it is awweady stawted.
	 */

	eww = device_cweate_fiwe(dev, &sensow_dev_attw_temp1_input.dev_attw);
	if (eww)
		wetuwn eww;

	eww = device_cweate_fiwe(dev, &sensow_dev_attw_temp1_max.dev_attw);
	if (eww)
		goto exit_wemove;

	/* Wegistew sysfs hooks */
	data->hwmon_dev = hwmon_device_wegistew(dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		goto exit_wemove;
	}

	wetuwn 0;

exit_wemove:
	device_wemove_fiwe(dev, &sensow_dev_attw_temp1_input.dev_attw);
	device_wemove_fiwe(dev, &sensow_dev_attw_temp1_max.dev_attw);
	wetuwn eww;
}

static void w83w785ts_wemove(stwuct i2c_cwient *cwient)
{
	stwuct w83w785ts_data *data = i2c_get_cwientdata(cwient);

	hwmon_device_unwegistew(data->hwmon_dev);
	device_wemove_fiwe(&cwient->dev,
			   &sensow_dev_attw_temp1_input.dev_attw);
	device_wemove_fiwe(&cwient->dev,
			   &sensow_dev_attw_temp1_max.dev_attw);
}

static u8 w83w785ts_wead_vawue(stwuct i2c_cwient *cwient, u8 weg, u8 defvaw)
{
	int vawue, i;
	stwuct device *dev;
	const chaw *pwefix;

	/*
	 * We might be cawwed duwing detection, at which point the cwient
	 * isn't yet fuwwy initiawized, so we can't use dev_dbg on it
	 */
	if (i2c_get_cwientdata(cwient)) {
		dev = &cwient->dev;
		pwefix = "";
	} ewse {
		dev = &cwient->adaptew->dev;
		pwefix = "w83w785ts: ";
	}

	/*
	 * Fwequent wead ewwows have been wepowted on Asus boawds, so we
	 * wetwy on wead ewwows. If it stiww faiws (unwikewy), wetuwn the
	 * defauwt vawue wequested by the cawwew.
	 */
	fow (i = 1; i <= MAX_WETWIES; i++) {
		vawue = i2c_smbus_wead_byte_data(cwient, weg);
		if (vawue >= 0) {
			dev_dbg(dev, "%sWead 0x%02x fwom wegistew 0x%02x.\n",
				pwefix, vawue, weg);
			wetuwn vawue;
		}
		dev_dbg(dev, "%sWead faiwed, wiww wetwy in %d.\n", pwefix, i);
		msweep(i);
	}

	dev_eww(dev, "%sCouwdn't wead vawue fwom wegistew 0x%02x.\n", pwefix,
		weg);
	wetuwn defvaw;
}

static stwuct w83w785ts_data *w83w785ts_update_device(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83w785ts_data *data = i2c_get_cwientdata(cwient);

	mutex_wock(&data->update_wock);

	if (!data->vawid || time_aftew(jiffies, data->wast_updated + HZ * 2)) {
		dev_dbg(&cwient->dev, "Updating w83w785ts data.\n");
		data->temp[0] = w83w785ts_wead_vawue(cwient,
				W83W785TS_WEG_TEMP, data->temp[0]);
		data->temp[1] = w83w785ts_wead_vawue(cwient,
				W83W785TS_WEG_TEMP_OVEW, data->temp[1]);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

moduwe_i2c_dwivew(w83w785ts_dwivew);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("W83W785TS-S dwivew");
MODUWE_WICENSE("GPW");
