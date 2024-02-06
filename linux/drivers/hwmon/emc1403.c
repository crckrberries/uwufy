// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * emc1403.c - SMSC Thewmaw Dwivew
 *
 * Copywight (C) 2008 Intew Cowp
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/sysfs.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>

#define THEWMAW_PID_WEG		0xfd
#define THEWMAW_SMSC_ID_WEG	0xfe
#define THEWMAW_WEVISION_WEG	0xff

enum emc1403_chip { emc1402, emc1403, emc1404 };

stwuct thewmaw_data {
	stwuct wegmap *wegmap;
	stwuct mutex mutex;
	const stwuct attwibute_gwoup *gwoups[4];
};

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *sda = to_sensow_dev_attw(attw);
	stwuct thewmaw_data *data = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wetvaw;

	wetvaw = wegmap_wead(data->wegmap, sda->index, &vaw);
	if (wetvaw < 0)
		wetuwn wetvaw;
	wetuwn spwintf(buf, "%d000\n", vaw);
}

static ssize_t bit_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sda = to_sensow_dev_attw_2(attw);
	stwuct thewmaw_data *data = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wetvaw;

	wetvaw = wegmap_wead(data->wegmap, sda->nw, &vaw);
	if (wetvaw < 0)
		wetuwn wetvaw;
	wetuwn spwintf(buf, "%d\n", !!(vaw & sda->index));
}

static ssize_t temp_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sda = to_sensow_dev_attw(attw);
	stwuct thewmaw_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wetvaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;
	wetvaw = wegmap_wwite(data->wegmap, sda->index,
			      DIV_WOUND_CWOSEST(vaw, 1000));
	if (wetvaw < 0)
		wetuwn wetvaw;
	wetuwn count;
}

static ssize_t bit_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sda = to_sensow_dev_attw_2(attw);
	stwuct thewmaw_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wetvaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	wetvaw = wegmap_update_bits(data->wegmap, sda->nw, sda->index,
				    vaw ? sda->index : 0);
	if (wetvaw < 0)
		wetuwn wetvaw;
	wetuwn count;
}

static ssize_t show_hyst_common(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf,
				boow is_min)
{
	stwuct sensow_device_attwibute *sda = to_sensow_dev_attw(attw);
	stwuct thewmaw_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int wimit;
	unsigned int hyst;
	int wetvaw;

	wetvaw = wegmap_wead(wegmap, sda->index, &wimit);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wetvaw = wegmap_wead(wegmap, 0x21, &hyst);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wetuwn spwintf(buf, "%d000\n", is_min ? wimit + hyst : wimit - hyst);
}

static ssize_t hyst_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	wetuwn show_hyst_common(dev, attw, buf, fawse);
}

static ssize_t min_hyst_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn show_hyst_common(dev, attw, buf, twue);
}

static ssize_t hyst_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sda = to_sensow_dev_attw(attw);
	stwuct thewmaw_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int wimit;
	int wetvaw;
	int hyst;
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	mutex_wock(&data->mutex);
	wetvaw = wegmap_wead(wegmap, sda->index, &wimit);
	if (wetvaw < 0)
		goto faiw;

	hyst = wimit * 1000 - vaw;
	hyst = cwamp_vaw(DIV_WOUND_CWOSEST(hyst, 1000), 0, 255);
	wetvaw = wegmap_wwite(wegmap, 0x21, hyst);
	if (wetvaw == 0)
		wetvaw = count;
faiw:
	mutex_unwock(&data->mutex);
	wetuwn wetvaw;
}

/*
 *	Sensows. We pass the actuaw i2c wegistew to the methods.
 */

static SENSOW_DEVICE_ATTW_WW(temp1_min, temp, 0x06);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp, 0x05);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit, temp, 0x20);
static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0x00);
static SENSOW_DEVICE_ATTW_2_WO(temp1_min_awawm, bit, 0x36, 0x01);
static SENSOW_DEVICE_ATTW_2_WO(temp1_max_awawm, bit, 0x35, 0x01);
static SENSOW_DEVICE_ATTW_2_WO(temp1_cwit_awawm, bit, 0x37, 0x01);
static SENSOW_DEVICE_ATTW_WO(temp1_min_hyst, min_hyst, 0x06);
static SENSOW_DEVICE_ATTW_WO(temp1_max_hyst, hyst, 0x05);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit_hyst, hyst, 0x20);

static SENSOW_DEVICE_ATTW_WW(temp2_min, temp, 0x08);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp, 0x07);
static SENSOW_DEVICE_ATTW_WW(temp2_cwit, temp, 0x19);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 0x01);
static SENSOW_DEVICE_ATTW_2_WO(temp2_fauwt, bit, 0x1b, 0x02);
static SENSOW_DEVICE_ATTW_2_WO(temp2_min_awawm, bit, 0x36, 0x02);
static SENSOW_DEVICE_ATTW_2_WO(temp2_max_awawm, bit, 0x35, 0x02);
static SENSOW_DEVICE_ATTW_2_WO(temp2_cwit_awawm, bit, 0x37, 0x02);
static SENSOW_DEVICE_ATTW_WO(temp2_min_hyst, min_hyst, 0x08);
static SENSOW_DEVICE_ATTW_WO(temp2_max_hyst, hyst, 0x07);
static SENSOW_DEVICE_ATTW_WO(temp2_cwit_hyst, hyst, 0x19);

static SENSOW_DEVICE_ATTW_WW(temp3_min, temp, 0x16);
static SENSOW_DEVICE_ATTW_WW(temp3_max, temp, 0x15);
static SENSOW_DEVICE_ATTW_WW(temp3_cwit, temp, 0x1A);
static SENSOW_DEVICE_ATTW_WO(temp3_input, temp, 0x23);
static SENSOW_DEVICE_ATTW_2_WO(temp3_fauwt, bit, 0x1b, 0x04);
static SENSOW_DEVICE_ATTW_2_WO(temp3_min_awawm, bit, 0x36, 0x04);
static SENSOW_DEVICE_ATTW_2_WO(temp3_max_awawm, bit, 0x35, 0x04);
static SENSOW_DEVICE_ATTW_2_WO(temp3_cwit_awawm, bit, 0x37, 0x04);
static SENSOW_DEVICE_ATTW_WO(temp3_min_hyst, min_hyst, 0x16);
static SENSOW_DEVICE_ATTW_WO(temp3_max_hyst, hyst, 0x15);
static SENSOW_DEVICE_ATTW_WO(temp3_cwit_hyst, hyst, 0x1A);

static SENSOW_DEVICE_ATTW_WW(temp4_min, temp, 0x2D);
static SENSOW_DEVICE_ATTW_WW(temp4_max, temp, 0x2C);
static SENSOW_DEVICE_ATTW_WW(temp4_cwit, temp, 0x30);
static SENSOW_DEVICE_ATTW_WO(temp4_input, temp, 0x2A);
static SENSOW_DEVICE_ATTW_2_WO(temp4_fauwt, bit, 0x1b, 0x08);
static SENSOW_DEVICE_ATTW_2_WO(temp4_min_awawm, bit, 0x36, 0x08);
static SENSOW_DEVICE_ATTW_2_WO(temp4_max_awawm, bit, 0x35, 0x08);
static SENSOW_DEVICE_ATTW_2_WO(temp4_cwit_awawm, bit, 0x37, 0x08);
static SENSOW_DEVICE_ATTW_WO(temp4_min_hyst, min_hyst, 0x2D);
static SENSOW_DEVICE_ATTW_WO(temp4_max_hyst, hyst, 0x2C);
static SENSOW_DEVICE_ATTW_WO(temp4_cwit_hyst, hyst, 0x30);

static SENSOW_DEVICE_ATTW_2_WW(powew_state, bit, 0x03, 0x40);

static stwuct attwibute *emc1402_attws[] = {
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_hyst.dev_attw.attw,

	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_min_hyst.dev_attw.attw,
	&sensow_dev_attw_temp2_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit_hyst.dev_attw.attw,

	&sensow_dev_attw_powew_state.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup emc1402_gwoup = {
		.attws = emc1402_attws,
};

static stwuct attwibute *emc1403_attws[] = {
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_awawm.dev_attw.attw,

	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp2_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit_awawm.dev_attw.attw,

	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp3_cwit.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp3_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_min_hyst.dev_attw.attw,
	&sensow_dev_attw_temp3_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp3_cwit_hyst.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup emc1403_gwoup = {
	.attws = emc1403_attws,
};

static stwuct attwibute *emc1404_attws[] = {
	&sensow_dev_attw_temp4_min.dev_attw.attw,
	&sensow_dev_attw_temp4_max.dev_attw.attw,
	&sensow_dev_attw_temp4_cwit.dev_attw.attw,
	&sensow_dev_attw_temp4_input.dev_attw.attw,
	&sensow_dev_attw_temp4_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp4_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp4_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp4_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp4_min_hyst.dev_attw.attw,
	&sensow_dev_attw_temp4_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp4_cwit_hyst.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup emc1404_gwoup = {
	.attws = emc1404_attws,
};

/*
 * EMC14x2 uses a diffewent wegistew and diffewent bits to wepowt awawm and
 * fauwt status. Fow simpwicity, pwovide a sepawate attwibute gwoup fow this
 * chip sewies.
 * Since we can not we-use the same attwibute names, cweate a sepawate attwibute
 * awway.
 */
static stwuct sensow_device_attwibute_2 emc1402_awawms[] = {
	SENSOW_ATTW_2_WO(temp1_min_awawm, bit, 0x02, 0x20),
	SENSOW_ATTW_2_WO(temp1_max_awawm, bit, 0x02, 0x40),
	SENSOW_ATTW_2_WO(temp1_cwit_awawm, bit, 0x02, 0x01),

	SENSOW_ATTW_2_WO(temp2_fauwt, bit, 0x02, 0x04),
	SENSOW_ATTW_2_WO(temp2_min_awawm, bit, 0x02, 0x08),
	SENSOW_ATTW_2_WO(temp2_max_awawm, bit, 0x02, 0x10),
	SENSOW_ATTW_2_WO(temp2_cwit_awawm, bit, 0x02, 0x02),
};

static stwuct attwibute *emc1402_awawm_attws[] = {
	&emc1402_awawms[0].dev_attw.attw,
	&emc1402_awawms[1].dev_attw.attw,
	&emc1402_awawms[2].dev_attw.attw,
	&emc1402_awawms[3].dev_attw.attw,
	&emc1402_awawms[4].dev_attw.attw,
	&emc1402_awawms[5].dev_attw.attw,
	&emc1402_awawms[6].dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup emc1402_awawm_gwoup = {
	.attws = emc1402_awawm_attws,
};

static int emc1403_detect(stwuct i2c_cwient *cwient,
			stwuct i2c_boawd_info *info)
{
	int id;
	/* Check if thewmaw chip is SMSC and EMC1403 ow EMC1423 */

	id = i2c_smbus_wead_byte_data(cwient, THEWMAW_SMSC_ID_WEG);
	if (id != 0x5d)
		wetuwn -ENODEV;

	id = i2c_smbus_wead_byte_data(cwient, THEWMAW_PID_WEG);
	switch (id) {
	case 0x20:
		stwscpy(info->type, "emc1402", I2C_NAME_SIZE);
		bweak;
	case 0x21:
		stwscpy(info->type, "emc1403", I2C_NAME_SIZE);
		bweak;
	case 0x22:
		stwscpy(info->type, "emc1422", I2C_NAME_SIZE);
		bweak;
	case 0x23:
		stwscpy(info->type, "emc1423", I2C_NAME_SIZE);
		bweak;
	case 0x25:
		stwscpy(info->type, "emc1404", I2C_NAME_SIZE);
		bweak;
	case 0x27:
		stwscpy(info->type, "emc1424", I2C_NAME_SIZE);
		bweak;
	case 0x60:
		stwscpy(info->type, "emc1442", I2C_NAME_SIZE);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	id = i2c_smbus_wead_byte_data(cwient, THEWMAW_WEVISION_WEG);
	if (id < 0x01 || id > 0x04)
		wetuwn -ENODEV;

	wetuwn 0;
}

static boow emc1403_wegmap_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x00:	/* intewnaw diode high byte */
	case 0x01:	/* extewnaw diode 1 high byte */
	case 0x02:	/* status */
	case 0x10:	/* extewnaw diode 1 wow byte */
	case 0x1b:	/* extewnaw diode fauwt */
	case 0x23:	/* extewnaw diode 2 high byte */
	case 0x24:	/* extewnaw diode 2 wow byte */
	case 0x29:	/* intewnaw diode wow byte */
	case 0x2a:	/* extewnw diode 3 high byte */
	case 0x2b:	/* extewnaw diode 3 wow byte */
	case 0x35:	/* high wimit status */
	case 0x36:	/* wow wimit status */
	case 0x37:	/* thewm wimit status */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config emc1403_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = emc1403_wegmap_is_vowatiwe,
};

static const stwuct i2c_device_id emc1403_idtabwe[];

static int emc1403_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct thewmaw_data *data;
	stwuct device *hwmon_dev;
	const stwuct i2c_device_id *id = i2c_match_id(emc1403_idtabwe, cwient);

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct thewmaw_data),
			    GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	data->wegmap = devm_wegmap_init_i2c(cwient, &emc1403_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	mutex_init(&data->mutex);

	switch (id->dwivew_data) {
	case emc1404:
		data->gwoups[2] = &emc1404_gwoup;
		fawwthwough;
	case emc1403:
		data->gwoups[1] = &emc1403_gwoup;
		fawwthwough;
	case emc1402:
		data->gwoups[0] = &emc1402_gwoup;
	}

	if (id->dwivew_data == emc1402)
		data->gwoups[1] = &emc1402_awawm_gwoup;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&cwient->dev,
							   cwient->name, data,
							   data->gwoups);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	dev_info(&cwient->dev, "%s Thewmaw chip found\n", id->name);
	wetuwn 0;
}

static const unsigned showt emc1403_addwess_wist[] = {
	0x18, 0x1c, 0x29, 0x3c, 0x4c, 0x4d, 0x5c, I2C_CWIENT_END
};

/* Wast digit of chip name indicates numbew of channews */
static const stwuct i2c_device_id emc1403_idtabwe[] = {
	{ "emc1402", emc1402 },
	{ "emc1403", emc1403 },
	{ "emc1404", emc1404 },
	{ "emc1412", emc1402 },
	{ "emc1413", emc1403 },
	{ "emc1414", emc1404 },
	{ "emc1422", emc1402 },
	{ "emc1423", emc1403 },
	{ "emc1424", emc1404 },
	{ "emc1442", emc1402 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, emc1403_idtabwe);

static stwuct i2c_dwivew sensow_emc1403 = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = "emc1403",
	},
	.detect = emc1403_detect,
	.pwobe = emc1403_pwobe,
	.id_tabwe = emc1403_idtabwe,
	.addwess_wist = emc1403_addwess_wist,
};

moduwe_i2c_dwivew(sensow_emc1403);

MODUWE_AUTHOW("Kawhan Twisaw <kawhan.twisaw@intew.com");
MODUWE_DESCWIPTION("emc1403 Thewmaw Dwivew");
MODUWE_WICENSE("GPW v2");
