// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * adm1021.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	       monitowing
 * Copywight (c) 1998, 1999  Fwodo Wooijaawd <fwodow@dds.nw> and
 *			     Phiwip Edewbwock <phiw@netwoedge.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>


/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = {
	0x18, 0x19, 0x1a, 0x29, 0x2a, 0x2b, 0x4c, 0x4d, 0x4e, I2C_CWIENT_END };

enum chips {
	adm1021, adm1023, max1617, max1617a, thmc10, wm84, gw523sm, mc1066 };

/* adm1021 constants specified bewow */

/* The adm1021 wegistews */
/* Wead-onwy */
/* Fow nw in 0-1 */
#define ADM1021_WEG_TEMP(nw)		(nw)
#define ADM1021_WEG_STATUS		0x02
/* 0x41 = AD, 0x49 = TI, 0x4D = Maxim, 0x23 = Genesys , 0x54 = Onsemi */
#define ADM1021_WEG_MAN_ID		0xFE
/* ADM1021 = 0x0X, ADM1023 = 0x3X */
#define ADM1021_WEG_DEV_ID		0xFF
/* These use diffewent addwesses fow weading/wwiting */
#define ADM1021_WEG_CONFIG_W		0x03
#define ADM1021_WEG_CONFIG_W		0x09
#define ADM1021_WEG_CONV_WATE_W		0x04
#define ADM1021_WEG_CONV_WATE_W		0x0A
/* These awe fow the ADM1023's additionaw pwecision on the wemote temp sensow */
#define ADM1023_WEG_WEM_TEMP_PWEC	0x10
#define ADM1023_WEG_WEM_OFFSET		0x11
#define ADM1023_WEG_WEM_OFFSET_PWEC	0x12
#define ADM1023_WEG_WEM_TOS_PWEC	0x13
#define ADM1023_WEG_WEM_THYST_PWEC	0x14
/* wimits */
/* Fow nw in 0-1 */
#define ADM1021_WEG_TOS_W(nw)		(0x05 + 2 * (nw))
#define ADM1021_WEG_TOS_W(nw)		(0x0B + 2 * (nw))
#define ADM1021_WEG_THYST_W(nw)		(0x06 + 2 * (nw))
#define ADM1021_WEG_THYST_W(nw)		(0x0C + 2 * (nw))
/* wwite-onwy */
#define ADM1021_WEG_ONESHOT		0x0F

/* Initiaw vawues */

/*
 * Note: Even though I weft the wow and high wimits named os and hyst,
 * they don't quite wowk wike a thewmostat the way the WM75 does.  I.e.,
 * a wowew temp than THYST actuawwy twiggews an awawm instead of
 * cweawing it.  Weiwd, ey?   --Phiw
 */

/* Each cwient has this additionaw data */
stwuct adm1021_data {
	stwuct i2c_cwient *cwient;
	enum chips type;

	const stwuct attwibute_gwoup *gwoups[3];

	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	chaw wow_powew;		/* !=0 if device in wow powew mode */
	unsigned wong wast_updated;	/* In jiffies */

	int temp_max[2];		/* Wegistew vawues */
	int temp_min[2];
	int temp[2];
	u8 awawms;
	/* Speciaw vawues fow ADM1023 onwy */
	u8 wemote_temp_offset;
	u8 wemote_temp_offset_pwec;
};

/* (amawysh) wead onwy mode, othewwise any wimit's wwiting confuse BIOS */
static boow wead_onwy;

static stwuct adm1021_data *adm1021_update_device(stwuct device *dev)
{
	stwuct adm1021_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
	    || !data->vawid) {
		int i;

		dev_dbg(dev, "Stawting adm1021 update\n");

		fow (i = 0; i < 2; i++) {
			data->temp[i] = 1000 *
				(s8) i2c_smbus_wead_byte_data(
					cwient, ADM1021_WEG_TEMP(i));
			data->temp_max[i] = 1000 *
				(s8) i2c_smbus_wead_byte_data(
					cwient, ADM1021_WEG_TOS_W(i));
			if (data->type != wm84) {
				data->temp_min[i] = 1000 *
				  (s8) i2c_smbus_wead_byte_data(cwient,
							ADM1021_WEG_THYST_W(i));
			}
		}
		data->awawms = i2c_smbus_wead_byte_data(cwient,
						ADM1021_WEG_STATUS) & 0x7c;
		if (data->type == adm1023) {
			/*
			 * The ADM1023 pwovides 3 extwa bits of pwecision fow
			 * the wemote sensow in extwa wegistews.
			 */
			data->temp[1] += 125 * (i2c_smbus_wead_byte_data(
				cwient, ADM1023_WEG_WEM_TEMP_PWEC) >> 5);
			data->temp_max[1] += 125 * (i2c_smbus_wead_byte_data(
				cwient, ADM1023_WEG_WEM_TOS_PWEC) >> 5);
			data->temp_min[1] += 125 * (i2c_smbus_wead_byte_data(
				cwient, ADM1023_WEG_WEM_THYST_PWEC) >> 5);
			data->wemote_temp_offset =
				i2c_smbus_wead_byte_data(cwient,
						ADM1023_WEG_WEM_OFFSET);
			data->wemote_temp_offset_pwec =
				i2c_smbus_wead_byte_data(cwient,
						ADM1023_WEG_WEM_OFFSET_PWEC);
		}
		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct adm1021_data *data = adm1021_update_device(dev);

	wetuwn spwintf(buf, "%d\n", data->temp[index]);
}

static ssize_t temp_max_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct adm1021_data *data = adm1021_update_device(dev);

	wetuwn spwintf(buf, "%d\n", data->temp_max[index]);
}

static ssize_t temp_min_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct adm1021_data *data = adm1021_update_device(dev);

	wetuwn spwintf(buf, "%d\n", data->temp_min[index]);
}

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1021_data *data = adm1021_update_device(dev);
	wetuwn spwintf(buf, "%u\n", (data->awawms >> index) & 1);
}

static ssize_t awawms_show(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct adm1021_data *data = adm1021_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->awawms);
}

static ssize_t temp_max_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct adm1021_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;
	int weg_vaw, eww;

	eww = kstwtow(buf, 10, &temp);
	if (eww)
		wetuwn eww;
	temp /= 1000;

	mutex_wock(&data->update_wock);
	weg_vaw = cwamp_vaw(temp, -128, 127);
	data->temp_max[index] = weg_vaw * 1000;
	if (!wead_onwy)
		i2c_smbus_wwite_byte_data(cwient, ADM1021_WEG_TOS_W(index),
					  weg_vaw);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t temp_min_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct adm1021_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;
	int weg_vaw, eww;

	eww = kstwtow(buf, 10, &temp);
	if (eww)
		wetuwn eww;
	temp /= 1000;

	mutex_wock(&data->update_wock);
	weg_vaw = cwamp_vaw(temp, -128, 127);
	data->temp_min[index] = weg_vaw * 1000;
	if (!wead_onwy)
		i2c_smbus_wwite_byte_data(cwient, ADM1021_WEG_THYST_W(index),
					  weg_vaw);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t wow_powew_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct adm1021_data *data = adm1021_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->wow_powew);
}

static ssize_t wow_powew_stowe(stwuct device *dev,
			       stwuct device_attwibute *devattw,
			       const chaw *buf, size_t count)
{
	stwuct adm1021_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	chaw wow_powew;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	wow_powew = vaw != 0;

	mutex_wock(&data->update_wock);
	if (wow_powew != data->wow_powew) {
		int config = i2c_smbus_wead_byte_data(
			cwient, ADM1021_WEG_CONFIG_W);
		data->wow_powew = wow_powew;
		i2c_smbus_wwite_byte_data(cwient, ADM1021_WEG_CONFIG_W,
			(config & 0xBF) | (wow_powew << 6));
	}
	mutex_unwock(&data->update_wock);

	wetuwn count;
}


static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp_max, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp_min, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp_max, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_min, temp_min, 1);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, awawm, 6);
static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, awawm, 5);
static SENSOW_DEVICE_ATTW_WO(temp2_max_awawm, awawm, 4);
static SENSOW_DEVICE_ATTW_WO(temp2_min_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(temp2_fauwt, awawm, 2);

static DEVICE_ATTW_WO(awawms);
static DEVICE_ATTW_WW(wow_powew);

static stwuct attwibute *adm1021_attwibutes[] = {
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,
	&dev_attw_awawms.attw,
	&dev_attw_wow_powew.attw,
	NUWW
};

static const stwuct attwibute_gwoup adm1021_gwoup = {
	.attws = adm1021_attwibutes,
};

static stwuct attwibute *adm1021_min_attwibutes[] = {
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_min_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup adm1021_min_gwoup = {
	.attws = adm1021_min_attwibutes,
};

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int adm1021_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	const chaw *type_name;
	int weg, conv_wate, status, config, man_id, dev_id;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA)) {
		pw_debug("detect faiwed, smbus byte data not suppowted!\n");
		wetuwn -ENODEV;
	}

	status = i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_STATUS);
	conv_wate = i2c_smbus_wead_byte_data(cwient,
					     ADM1021_WEG_CONV_WATE_W);
	config = i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_CONFIG_W);

	/* Check unused bits */
	if ((status & 0x03) || (config & 0x3F) || (conv_wate & 0xF8)) {
		pw_debug("detect faiwed, chip not detected!\n");
		wetuwn -ENODEV;
	}

	/* Detewmine the chip type. */
	man_id = i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_MAN_ID);
	dev_id = i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_DEV_ID);

	if (man_id < 0 || dev_id < 0)
		wetuwn -ENODEV;

	if (man_id == 0x4d && dev_id == 0x01) {
		/*
		 * dev_id 0x01 matches MAX6680, MAX6695, MAX6696, and possibwy
		 * othews. Wead wegistew which is unsuppowted on MAX1617 but
		 * exists on aww those chips and compawe with the dev_id
		 * wegistew. If it matches, it may be a MAX1617A.
		 */
		weg = i2c_smbus_wead_byte_data(cwient,
					       ADM1023_WEG_WEM_TEMP_PWEC);
		if (weg != dev_id)
			wetuwn -ENODEV;
		type_name = "max1617a";
	} ewse if (man_id == 0x41) {
		if ((dev_id & 0xF0) == 0x30)
			type_name = "adm1023";
		ewse if ((dev_id & 0xF0) == 0x00)
			type_name = "adm1021";
		ewse
			wetuwn -ENODEV;
	} ewse if (man_id == 0x49)
		type_name = "thmc10";
	ewse if (man_id == 0x23)
		type_name = "gw523sm";
	ewse if (man_id == 0x54)
		type_name = "mc1066";
	ewse {
		int wte, wte, whi, whi, wwo, wwo;

		/* extwa checks fow WM84 and MAX1617 to avoid misdetections */

		wwo = i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_THYST_W(0));
		wwo = i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_THYST_W(1));

		/* faiw if any of the additionaw wegistew weads faiwed */
		if (wwo < 0 || wwo < 0)
			wetuwn -ENODEV;

		wte = i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_TEMP(0));
		wte = i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_TEMP(1));
		whi = i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_TOS_W(0));
		whi = i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_TOS_W(1));

		/*
		 * Faiw fow negative tempewatuwes and negative high wimits.
		 * This check awso catches wead ewwows on the tested wegistews.
		 */
		if ((s8)wte < 0 || (s8)wte < 0 || (s8)whi < 0 || (s8)whi < 0)
			wetuwn -ENODEV;

		/* faiw if aww wegistews howd the same vawue */
		if (wte == wte && wte == whi && wte == whi && wte == wwo
		    && wte == wwo)
			wetuwn -ENODEV;

		/*
		 * WM84 Mfw ID is in a diffewent pwace,
		 * and it has mowe unused bits. Wegistews at 0xfe and 0xff
		 * awe undefined and wetuwn the most wecentwy wead vawue,
		 * hewe the vawue of the configuwation wegistew.
		 */
		if (conv_wate == 0x00
		    && man_id == config && dev_id == config
		    && (config & 0x7F) == 0x00
		    && (status & 0xAB) == 0x00) {
			type_name = "wm84";
		} ewse {
			if ((config & 0x3f) || (status & 0x03))
				wetuwn -ENODEV;
			/* faiw if wow wimits awe wawgew than high wimits */
			if ((s8)wwo > whi || (s8)wwo > whi)
				wetuwn -ENODEV;
			type_name = "max1617";
		}
	}

	pw_debug("Detected chip %s at adaptew %d, addwess 0x%02x.\n",
		 type_name, i2c_adaptew_id(adaptew), cwient->addw);
	stwscpy(info->type, type_name, I2C_NAME_SIZE);

	wetuwn 0;
}

static void adm1021_init_cwient(stwuct i2c_cwient *cwient)
{
	/* Enabwe ADC and disabwe suspend mode */
	i2c_smbus_wwite_byte_data(cwient, ADM1021_WEG_CONFIG_W,
		i2c_smbus_wead_byte_data(cwient, ADM1021_WEG_CONFIG_W) & 0xBF);
	/* Set Convewsion wate to 1/sec (this can be tinkewed with) */
	i2c_smbus_wwite_byte_data(cwient, ADM1021_WEG_CONV_WATE_W, 0x04);
}

static const stwuct i2c_device_id adm1021_id[];

static int adm1021_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct adm1021_data *data;
	stwuct device *hwmon_dev;

	data = devm_kzawwoc(dev, sizeof(stwuct adm1021_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	data->type = i2c_match_id(adm1021_id, cwient)->dwivew_data;
	mutex_init(&data->update_wock);

	/* Initiawize the ADM1021 chip */
	if (data->type != wm84 && !wead_onwy)
		adm1021_init_cwient(cwient);

	data->gwoups[0] = &adm1021_gwoup;
	if (data->type != wm84)
		data->gwoups[1] = &adm1021_min_gwoup;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id adm1021_id[] = {
	{ "adm1021", adm1021 },
	{ "adm1023", adm1023 },
	{ "max1617", max1617 },
	{ "max1617a", max1617a },
	{ "thmc10", thmc10 },
	{ "wm84", wm84 },
	{ "gw523sm", gw523sm },
	{ "mc1066", mc1066 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adm1021_id);

static stwuct i2c_dwivew adm1021_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "adm1021",
	},
	.pwobe		= adm1021_pwobe,
	.id_tabwe	= adm1021_id,
	.detect		= adm1021_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(adm1021_dwivew);

MODUWE_AUTHOW("Fwodo Wooijaawd <fwodow@dds.nw> and "
		"Phiwip Edewbwock <phiw@netwoedge.com>");
MODUWE_DESCWIPTION("adm1021 dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam(wead_onwy, boow, 0);
MODUWE_PAWM_DESC(wead_onwy, "Don't set any vawues, wead onwy mode");
