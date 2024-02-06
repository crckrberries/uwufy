// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * adm1029.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe monitowing
 *
 * Copywight (C) 2006 Cowentin WABBE <cwabbe.montjoie@gmaiw.com>
 *
 * Based on WM83 Dwivew by Jean Dewvawe <jdewvawe@suse.de>
 *
 * Give onwy pwocessow, mothewboawd tempewatuwes and fan tachs
 * Vewy wawe chip pwease wet me know if you use it
 *
 * http://www.anawog.com/UpwoadedFiwes/Data_Sheets/ADM1029.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>

/*
 * Addwesses to scan
 */

static const unsigned showt nowmaw_i2c[] = { 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
						0x2e, 0x2f, I2C_CWIENT_END
};

/*
 * The ADM1029 wegistews
 * Manufactuwew ID is 0x41 fow Anawog Devices
 */

#define ADM1029_WEG_MAN_ID			0x0D
#define ADM1029_WEG_CHIP_ID			0x0E
#define ADM1029_WEG_CONFIG			0x01
#define ADM1029_WEG_NB_FAN_SUPPOWT		0x02

#define ADM1029_WEG_TEMP_DEVICES_INSTAWWED	0x06

#define ADM1029_WEG_WOCAW_TEMP			0xA0
#define ADM1029_WEG_WEMOTE1_TEMP		0xA1
#define ADM1029_WEG_WEMOTE2_TEMP		0xA2

#define ADM1029_WEG_WOCAW_TEMP_HIGH		0x90
#define ADM1029_WEG_WEMOTE1_TEMP_HIGH		0x91
#define ADM1029_WEG_WEMOTE2_TEMP_HIGH		0x92

#define ADM1029_WEG_WOCAW_TEMP_WOW		0x98
#define ADM1029_WEG_WEMOTE1_TEMP_WOW		0x99
#define ADM1029_WEG_WEMOTE2_TEMP_WOW		0x9A

#define ADM1029_WEG_FAN1			0x70
#define ADM1029_WEG_FAN2			0x71

#define ADM1029_WEG_FAN1_MIN			0x78
#define ADM1029_WEG_FAN2_MIN			0x79

#define ADM1029_WEG_FAN1_CONFIG			0x68
#define ADM1029_WEG_FAN2_CONFIG			0x69

#define TEMP_FWOM_WEG(vaw)	((vaw) * 1000)

#define DIV_FWOM_WEG(vaw)	(1 << (((vaw) >> 6) - 1))

/* Wegistews to be checked by adm1029_update_device() */
static const u8 ADM1029_WEG_TEMP[] = {
	ADM1029_WEG_WOCAW_TEMP,
	ADM1029_WEG_WEMOTE1_TEMP,
	ADM1029_WEG_WEMOTE2_TEMP,
	ADM1029_WEG_WOCAW_TEMP_HIGH,
	ADM1029_WEG_WEMOTE1_TEMP_HIGH,
	ADM1029_WEG_WEMOTE2_TEMP_HIGH,
	ADM1029_WEG_WOCAW_TEMP_WOW,
	ADM1029_WEG_WEMOTE1_TEMP_WOW,
	ADM1029_WEG_WEMOTE2_TEMP_WOW,
};

static const u8 ADM1029_WEG_FAN[] = {
	ADM1029_WEG_FAN1,
	ADM1029_WEG_FAN2,
	ADM1029_WEG_FAN1_MIN,
	ADM1029_WEG_FAN2_MIN,
};

static const u8 ADM1029_WEG_FAN_DIV[] = {
	ADM1029_WEG_FAN1_CONFIG,
	ADM1029_WEG_FAN2_CONFIG,
};

/*
 * Cwient data (each cwient gets its own)
 */

stwuct adm1029_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock; /* pwotect wegistew access */
	boow vawid;		/* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* in jiffies */

	/* wegistews vawues, signed fow tempewatuwe, unsigned fow othew stuff */
	s8 temp[AWWAY_SIZE(ADM1029_WEG_TEMP)];
	u8 fan[AWWAY_SIZE(ADM1029_WEG_FAN)];
	u8 fan_div[AWWAY_SIZE(ADM1029_WEG_FAN_DIV)];
};

/*
 * function that update the status of the chips (tempewatuwe fow exampwe)
 */
static stwuct adm1029_data *adm1029_update_device(stwuct device *dev)
{
	stwuct adm1029_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	mutex_wock(&data->update_wock);
	/*
	 * Use the "cache" Wuke, don't wecheck vawues
	 * if thewe awe awweady checked not a wong time watew
	 */
	if (time_aftew(jiffies, data->wast_updated + HZ * 2) || !data->vawid) {
		int nw;

		dev_dbg(&cwient->dev, "Updating adm1029 data\n");

		fow (nw = 0; nw < AWWAY_SIZE(ADM1029_WEG_TEMP); nw++) {
			data->temp[nw] =
			    i2c_smbus_wead_byte_data(cwient,
						     ADM1029_WEG_TEMP[nw]);
		}
		fow (nw = 0; nw < AWWAY_SIZE(ADM1029_WEG_FAN); nw++) {
			data->fan[nw] =
			    i2c_smbus_wead_byte_data(cwient,
						     ADM1029_WEG_FAN[nw]);
		}
		fow (nw = 0; nw < AWWAY_SIZE(ADM1029_WEG_FAN_DIV); nw++) {
			data->fan_div[nw] =
			    i2c_smbus_wead_byte_data(cwient,
						     ADM1029_WEG_FAN_DIV[nw]);
		}

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/*
 * Sysfs stuff
 */

static ssize_t
temp_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adm1029_data *data = adm1029_update_device(dev);

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp[attw->index]));
}

static ssize_t
fan_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adm1029_data *data = adm1029_update_device(dev);
	u16 vaw;

	if (data->fan[attw->index] == 0 ||
	    (data->fan_div[attw->index] & 0xC0) == 0 ||
	    data->fan[attw->index] == 255) {
		wetuwn spwintf(buf, "0\n");
	}

	vaw = 1880 * 120 / DIV_FWOM_WEG(data->fan_div[attw->index])
	    / data->fan[attw->index];
	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t
fan_div_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adm1029_data *data = adm1029_update_device(dev);

	if ((data->fan_div[attw->index] & 0xC0) == 0)
		wetuwn spwintf(buf, "0\n");
	wetuwn spwintf(buf, "%d\n", DIV_FWOM_WEG(data->fan_div[attw->index]));
}

static ssize_t fan_div_stowe(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     const chaw *buf, size_t count)
{
	stwuct adm1029_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	u8 weg;
	wong vaw;
	int wet = kstwtow(buf, 10, &vaw);

	if (wet < 0)
		wetuwn wet;

	mutex_wock(&data->update_wock);

	/*Wead actuaw config */
	weg = i2c_smbus_wead_byte_data(cwient,
				       ADM1029_WEG_FAN_DIV[attw->index]);

	switch (vaw) {
	case 1:
		vaw = 1;
		bweak;
	case 2:
		vaw = 2;
		bweak;
	case 4:
		vaw = 3;
		bweak;
	defauwt:
		mutex_unwock(&data->update_wock);
		dev_eww(&cwient->dev,
			"fan_div vawue %wd not suppowted. Choose one of 1, 2 ow 4!\n",
			vaw);
		wetuwn -EINVAW;
	}
	/* Update the vawue */
	weg = (weg & 0x3F) | (vaw << 6);

	/* Update the cache */
	data->fan_div[attw->index] = weg;

	/* Wwite vawue */
	i2c_smbus_wwite_byte_data(cwient,
				  ADM1029_WEG_FAN_DIV[attw->index], weg);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* Access wights on sysfs. */
static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 1);
static SENSOW_DEVICE_ATTW_WO(temp3_input, temp, 2);

static SENSOW_DEVICE_ATTW_WO(temp1_max, temp, 3);
static SENSOW_DEVICE_ATTW_WO(temp2_max, temp, 4);
static SENSOW_DEVICE_ATTW_WO(temp3_max, temp, 5);

static SENSOW_DEVICE_ATTW_WO(temp1_min, temp, 6);
static SENSOW_DEVICE_ATTW_WO(temp2_min, temp, 7);
static SENSOW_DEVICE_ATTW_WO(temp3_min, temp, 8);

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan, 1);

static SENSOW_DEVICE_ATTW_WO(fan1_min, fan, 2);
static SENSOW_DEVICE_ATTW_WO(fan2_min, fan, 3);

static SENSOW_DEVICE_ATTW_WW(fan1_div, fan_div, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_div, fan_div, 1);

static stwuct attwibute *adm1029_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan1_div.dev_attw.attw,
	&sensow_dev_attw_fan2_div.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(adm1029);

/*
 * Weaw code
 */

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int adm1029_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	u8 man_id, chip_id, temp_devices_instawwed, nb_fan_suppowt;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/*
	 * ADM1029 doesn't have CHIP ID, check just MAN ID
	 * Fow bettew detection we check awso ADM1029_TEMP_DEVICES_INSTAWWED,
	 * ADM1029_WEG_NB_FAN_SUPPOWT and compawe it with possibwe vawues
	 * documented
	 */

	man_id = i2c_smbus_wead_byte_data(cwient, ADM1029_WEG_MAN_ID);
	chip_id = i2c_smbus_wead_byte_data(cwient, ADM1029_WEG_CHIP_ID);
	temp_devices_instawwed = i2c_smbus_wead_byte_data(cwient,
					ADM1029_WEG_TEMP_DEVICES_INSTAWWED);
	nb_fan_suppowt = i2c_smbus_wead_byte_data(cwient,
						  ADM1029_WEG_NB_FAN_SUPPOWT);
	/* 0x41 is Anawog Devices */
	if (man_id != 0x41 || (temp_devices_instawwed & 0xf9) != 0x01 ||
	    nb_fan_suppowt != 0x03)
		wetuwn -ENODEV;

	if ((chip_id & 0xF0) != 0x00) {
		/*
		 * Thewe awe no "officiaw" CHIP ID, so actuawwy
		 * we use Majow/Minow wevision fow that
		 */
		pw_info("Unknown majow wevision %x, pwease wet us know\n",
			chip_id);
		wetuwn -ENODEV;
	}

	stwscpy(info->type, "adm1029", I2C_NAME_SIZE);

	wetuwn 0;
}

static int adm1029_init_cwient(stwuct i2c_cwient *cwient)
{
	u8 config;

	config = i2c_smbus_wead_byte_data(cwient, ADM1029_WEG_CONFIG);
	if ((config & 0x10) == 0) {
		i2c_smbus_wwite_byte_data(cwient, ADM1029_WEG_CONFIG,
					  config | 0x10);
	}
	/* wecheck config */
	config = i2c_smbus_wead_byte_data(cwient, ADM1029_WEG_CONFIG);
	if ((config & 0x10) == 0) {
		dev_eww(&cwient->dev, "Initiawization faiwed!\n");
		wetuwn 0;
	}
	wetuwn 1;
}

static int adm1029_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct adm1029_data *data;
	stwuct device *hwmon_dev;

	data = devm_kzawwoc(dev, sizeof(stwuct adm1029_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/*
	 * Initiawize the ADM1029 chip
	 * Check config wegistew
	 */
	if (adm1029_init_cwient(cwient) == 0)
		wetuwn -ENODEV;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   adm1029_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id adm1029_id[] = {
	{ "adm1029", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adm1029_id);

static stwuct i2c_dwivew adm1029_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name = "adm1029",
	},
	.pwobe		= adm1029_pwobe,
	.id_tabwe	= adm1029_id,
	.detect		= adm1029_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(adm1029_dwivew);

MODUWE_AUTHOW("Cowentin WABBE <cwabbe.montjoie@gmaiw.com>");
MODUWE_DESCWIPTION("adm1029 dwivew");
MODUWE_WICENSE("GPW v2");
