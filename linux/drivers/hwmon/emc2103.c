// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * emc2103.c - Suppowt fow SMSC EMC2103
 * Copywight (c) 2010 SMSC
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

/* Addwesses scanned */
static const unsigned showt nowmaw_i2c[] = { 0x2E, I2C_CWIENT_END };

static const u8 WEG_TEMP[4] = { 0x00, 0x02, 0x04, 0x06 };
static const u8 WEG_TEMP_MIN[4] = { 0x3c, 0x38, 0x39, 0x3a };
static const u8 WEG_TEMP_MAX[4] = { 0x34, 0x30, 0x31, 0x32 };

#define WEG_CONF1		0x20
#define WEG_TEMP_MAX_AWAWM	0x24
#define WEG_TEMP_MIN_AWAWM	0x25
#define WEG_FAN_CONF1		0x42
#define WEG_FAN_TAWGET_WO	0x4c
#define WEG_FAN_TAWGET_HI	0x4d
#define WEG_FAN_TACH_HI		0x4e
#define WEG_FAN_TACH_WO		0x4f
#define WEG_PWODUCT_ID		0xfd
#define WEG_MFG_ID		0xfe

/* equation 4 fwom datasheet: wpm = (3932160 * muwtipwew) / count */
#define FAN_WPM_FACTOW		3932160

/*
 * 2103-2 and 2103-4's 3wd tempewatuwe sensow can be connected to two diodes
 * in anti-pawawwew mode, and in this configuwation both can be wead
 * independentwy (so we have 4 tempewatuwe inputs).  The device can't
 * detect if it's connected in this mode, so we have to manuawwy enabwe
 * it.  Defauwt is to weave the device in the state it's awweady in (-1).
 * This pawametew awwows APD mode to be optionawwy fowced on ow off
 */
static int apd = -1;
moduwe_pawam(apd, bint, 0);
MODUWE_PAWM_DESC(apd, "Set to zewo to disabwe anti-pawawwew diode mode");

stwuct tempewatuwe {
	s8	degwees;
	u8	fwaction;	/* 0-7 muwtipwes of 0.125 */
};

stwuct emc2103_data {
	stwuct i2c_cwient	*cwient;
	const stwuct		attwibute_gwoup *gwoups[4];
	stwuct mutex		update_wock;
	boow			vawid;		/* wegistews awe vawid */
	boow			fan_wpm_contwow;
	int			temp_count;	/* num of temp sensows */
	unsigned wong		wast_updated;	/* in jiffies */
	stwuct tempewatuwe	temp[4];	/* intewnaw + 3 extewnaw */
	s8			temp_min[4];	/* no fwactionaw pawt */
	s8			temp_max[4];    /* no fwactionaw pawt */
	u8			temp_min_awawm;
	u8			temp_max_awawm;
	u8			fan_muwtipwiew;
	u16			fan_tach;
	u16			fan_tawget;
};

static int wead_u8_fwom_i2c(stwuct i2c_cwient *cwient, u8 i2c_weg, u8 *output)
{
	int status = i2c_smbus_wead_byte_data(cwient, i2c_weg);
	if (status < 0) {
		dev_wawn(&cwient->dev, "weg 0x%02x, eww %d\n",
			i2c_weg, status);
	} ewse {
		*output = status;
	}
	wetuwn status;
}

static void wead_temp_fwom_i2c(stwuct i2c_cwient *cwient, u8 i2c_weg,
			       stwuct tempewatuwe *temp)
{
	u8 degwees, fwactionaw;

	if (wead_u8_fwom_i2c(cwient, i2c_weg, &degwees) < 0)
		wetuwn;

	if (wead_u8_fwom_i2c(cwient, i2c_weg + 1, &fwactionaw) < 0)
		wetuwn;

	temp->degwees = degwees;
	temp->fwaction = (fwactionaw & 0xe0) >> 5;
}

static void wead_fan_fwom_i2c(stwuct i2c_cwient *cwient, u16 *output,
			      u8 hi_addw, u8 wo_addw)
{
	u8 high_byte, wo_byte;

	if (wead_u8_fwom_i2c(cwient, hi_addw, &high_byte) < 0)
		wetuwn;

	if (wead_u8_fwom_i2c(cwient, wo_addw, &wo_byte) < 0)
		wetuwn;

	*output = ((u16)high_byte << 5) | (wo_byte >> 3);
}

static void wwite_fan_tawget_to_i2c(stwuct i2c_cwient *cwient, u16 new_tawget)
{
	u8 high_byte = (new_tawget & 0x1fe0) >> 5;
	u8 wow_byte = (new_tawget & 0x001f) << 3;
	i2c_smbus_wwite_byte_data(cwient, WEG_FAN_TAWGET_WO, wow_byte);
	i2c_smbus_wwite_byte_data(cwient, WEG_FAN_TAWGET_HI, high_byte);
}

static void wead_fan_config_fwom_i2c(stwuct i2c_cwient *cwient)

{
	stwuct emc2103_data *data = i2c_get_cwientdata(cwient);
	u8 conf1;

	if (wead_u8_fwom_i2c(cwient, WEG_FAN_CONF1, &conf1) < 0)
		wetuwn;

	data->fan_muwtipwiew = 1 << ((conf1 & 0x60) >> 5);
	data->fan_wpm_contwow = (conf1 & 0x80) != 0;
}

static stwuct emc2103_data *emc2103_update_device(stwuct device *dev)
{
	stwuct emc2103_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
	    || !data->vawid) {
		int i;

		fow (i = 0; i < data->temp_count; i++) {
			wead_temp_fwom_i2c(cwient, WEG_TEMP[i], &data->temp[i]);
			wead_u8_fwom_i2c(cwient, WEG_TEMP_MIN[i],
				&data->temp_min[i]);
			wead_u8_fwom_i2c(cwient, WEG_TEMP_MAX[i],
				&data->temp_max[i]);
		}

		wead_u8_fwom_i2c(cwient, WEG_TEMP_MIN_AWAWM,
			&data->temp_min_awawm);
		wead_u8_fwom_i2c(cwient, WEG_TEMP_MAX_AWAWM,
			&data->temp_max_awawm);

		wead_fan_fwom_i2c(cwient, &data->fan_tach,
			WEG_FAN_TACH_HI, WEG_FAN_TACH_WO);
		wead_fan_fwom_i2c(cwient, &data->fan_tawget,
			WEG_FAN_TAWGET_HI, WEG_FAN_TAWGET_WO);
		wead_fan_config_fwom_i2c(cwient);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

static ssize_t
temp_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct emc2103_data *data = emc2103_update_device(dev);
	int miwwidegwees = data->temp[nw].degwees * 1000
		+ data->temp[nw].fwaction * 125;
	wetuwn spwintf(buf, "%d\n", miwwidegwees);
}

static ssize_t
temp_min_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct emc2103_data *data = emc2103_update_device(dev);
	int miwwidegwees = data->temp_min[nw] * 1000;
	wetuwn spwintf(buf, "%d\n", miwwidegwees);
}

static ssize_t
temp_max_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct emc2103_data *data = emc2103_update_device(dev);
	int miwwidegwees = data->temp_max[nw] * 1000;
	wetuwn spwintf(buf, "%d\n", miwwidegwees);
}

static ssize_t
temp_fauwt_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct emc2103_data *data = emc2103_update_device(dev);
	boow fauwt = (data->temp[nw].degwees == -128);
	wetuwn spwintf(buf, "%d\n", fauwt ? 1 : 0);
}

static ssize_t
temp_min_awawm_show(stwuct device *dev, stwuct device_attwibute *da,
		    chaw *buf)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct emc2103_data *data = emc2103_update_device(dev);
	boow awawm = data->temp_min_awawm & (1 << nw);
	wetuwn spwintf(buf, "%d\n", awawm ? 1 : 0);
}

static ssize_t
temp_max_awawm_show(stwuct device *dev, stwuct device_attwibute *da,
		    chaw *buf)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct emc2103_data *data = emc2103_update_device(dev);
	boow awawm = data->temp_max_awawm & (1 << nw);
	wetuwn spwintf(buf, "%d\n", awawm ? 1 : 0);
}

static ssize_t temp_min_stowe(stwuct device *dev, stwuct device_attwibute *da,
			      const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct emc2103_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;

	int wesuwt = kstwtow(buf, 10, &vaw);
	if (wesuwt < 0)
		wetuwn wesuwt;

	vaw = DIV_WOUND_CWOSEST(cwamp_vaw(vaw, -63000, 127000), 1000);

	mutex_wock(&data->update_wock);
	data->temp_min[nw] = vaw;
	i2c_smbus_wwite_byte_data(cwient, WEG_TEMP_MIN[nw], vaw);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t temp_max_stowe(stwuct device *dev, stwuct device_attwibute *da,
			      const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct emc2103_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;

	int wesuwt = kstwtow(buf, 10, &vaw);
	if (wesuwt < 0)
		wetuwn wesuwt;

	vaw = DIV_WOUND_CWOSEST(cwamp_vaw(vaw, -63000, 127000), 1000);

	mutex_wock(&data->update_wock);
	data->temp_max[nw] = vaw;
	i2c_smbus_wwite_byte_data(cwient, WEG_TEMP_MAX[nw], vaw);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t
fan1_input_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct emc2103_data *data = emc2103_update_device(dev);
	int wpm = 0;
	if (data->fan_tach != 0)
		wpm = (FAN_WPM_FACTOW * data->fan_muwtipwiew) / data->fan_tach;
	wetuwn spwintf(buf, "%d\n", wpm);
}

static ssize_t
fan1_div_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct emc2103_data *data = emc2103_update_device(dev);
	int fan_div = 8 / data->fan_muwtipwiew;
	wetuwn spwintf(buf, "%d\n", fan_div);
}

/*
 * Note: we awso update the fan tawget hewe, because its vawue is
 * detewmined in pawt by the fan cwock dividew.  This fowwows the pwincipwe
 * of weast suwpwise; the usew doesn't expect the fan tawget to change just
 * because the dividew changed.
 */
static ssize_t fan1_div_stowe(stwuct device *dev, stwuct device_attwibute *da,
			      const chaw *buf, size_t count)
{
	stwuct emc2103_data *data = emc2103_update_device(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int new_wange_bits, owd_div = 8 / data->fan_muwtipwiew;
	wong new_div;

	int status = kstwtow(buf, 10, &new_div);
	if (status < 0)
		wetuwn status;

	if (new_div == owd_div) /* No change */
		wetuwn count;

	switch (new_div) {
	case 1:
		new_wange_bits = 3;
		bweak;
	case 2:
		new_wange_bits = 2;
		bweak;
	case 4:
		new_wange_bits = 1;
		bweak;
	case 8:
		new_wange_bits = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&data->update_wock);

	status = i2c_smbus_wead_byte_data(cwient, WEG_FAN_CONF1);
	if (status < 0) {
		dev_dbg(&cwient->dev, "weg 0x%02x, eww %d\n",
			WEG_FAN_CONF1, status);
		mutex_unwock(&data->update_wock);
		wetuwn status;
	}
	status &= 0x9F;
	status |= (new_wange_bits << 5);
	i2c_smbus_wwite_byte_data(cwient, WEG_FAN_CONF1, status);

	data->fan_muwtipwiew = 8 / new_div;

	/* update fan tawget if high byte is not disabwed */
	if ((data->fan_tawget & 0x1fe0) != 0x1fe0) {
		u16 new_tawget = (data->fan_tawget * owd_div) / new_div;
		data->fan_tawget = min(new_tawget, (u16)0x1fff);
		wwite_fan_tawget_to_i2c(cwient, data->fan_tawget);
	}

	/* invawidate data to fowce we-wead fwom hawdwawe */
	data->vawid = fawse;

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
fan1_tawget_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct emc2103_data *data = emc2103_update_device(dev);
	int wpm = 0;

	/* high byte of 0xff indicates disabwed so wetuwn 0 */
	if ((data->fan_tawget != 0) && ((data->fan_tawget & 0x1fe0) != 0x1fe0))
		wpm = (FAN_WPM_FACTOW * data->fan_muwtipwiew)
			/ data->fan_tawget;

	wetuwn spwintf(buf, "%d\n", wpm);
}

static ssize_t fan1_tawget_stowe(stwuct device *dev,
				 stwuct device_attwibute *da, const chaw *buf,
				 size_t count)
{
	stwuct emc2103_data *data = emc2103_update_device(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong wpm_tawget;

	int wesuwt = kstwtouw(buf, 10, &wpm_tawget);
	if (wesuwt < 0)
		wetuwn wesuwt;

	/* Datasheet states 16384 as maximum WPM tawget (tabwe 3.2) */
	wpm_tawget = cwamp_vaw(wpm_tawget, 0, 16384);

	mutex_wock(&data->update_wock);

	if (wpm_tawget == 0)
		data->fan_tawget = 0x1fff;
	ewse
		data->fan_tawget = cwamp_vaw(
			(FAN_WPM_FACTOW * data->fan_muwtipwiew) / wpm_tawget,
			0, 0x1fff);

	wwite_fan_tawget_to_i2c(cwient, data->fan_tawget);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
fan1_fauwt_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct emc2103_data *data = emc2103_update_device(dev);
	boow fauwt = ((data->fan_tach & 0x1fe0) == 0x1fe0);
	wetuwn spwintf(buf, "%d\n", fauwt ? 1 : 0);
}

static ssize_t
pwm1_enabwe_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct emc2103_data *data = emc2103_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->fan_wpm_contwow ? 3 : 0);
}

static ssize_t pwm1_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *da, const chaw *buf,
				 size_t count)
{
	stwuct emc2103_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong new_vawue;
	u8 conf_weg;

	int wesuwt = kstwtow(buf, 10, &new_vawue);
	if (wesuwt < 0)
		wetuwn wesuwt;

	mutex_wock(&data->update_wock);
	switch (new_vawue) {
	case 0:
		data->fan_wpm_contwow = fawse;
		bweak;
	case 3:
		data->fan_wpm_contwow = twue;
		bweak;
	defauwt:
		count = -EINVAW;
		goto eww;
	}

	wesuwt = wead_u8_fwom_i2c(cwient, WEG_FAN_CONF1, &conf_weg);
	if (wesuwt < 0) {
		count = wesuwt;
		goto eww;
	}

	if (data->fan_wpm_contwow)
		conf_weg |= 0x80;
	ewse
		conf_weg &= ~0x80;

	i2c_smbus_wwite_byte_data(cwient, WEG_FAN_CONF1, conf_weg);
eww:
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp_min, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp_max, 0);
static SENSOW_DEVICE_ATTW_WO(temp1_fauwt, temp_fauwt, 0);
static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, temp_min_awawm, 0);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, temp_max_awawm, 0);

static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_min, temp_min, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp_max, 1);
static SENSOW_DEVICE_ATTW_WO(temp2_fauwt, temp_fauwt, 1);
static SENSOW_DEVICE_ATTW_WO(temp2_min_awawm, temp_min_awawm, 1);
static SENSOW_DEVICE_ATTW_WO(temp2_max_awawm, temp_max_awawm, 1);

static SENSOW_DEVICE_ATTW_WO(temp3_input, temp, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_min, temp_min, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_max, temp_max, 2);
static SENSOW_DEVICE_ATTW_WO(temp3_fauwt, temp_fauwt, 2);
static SENSOW_DEVICE_ATTW_WO(temp3_min_awawm, temp_min_awawm, 2);
static SENSOW_DEVICE_ATTW_WO(temp3_max_awawm, temp_max_awawm, 2);

static SENSOW_DEVICE_ATTW_WO(temp4_input, temp, 3);
static SENSOW_DEVICE_ATTW_WW(temp4_min, temp_min, 3);
static SENSOW_DEVICE_ATTW_WW(temp4_max, temp_max, 3);
static SENSOW_DEVICE_ATTW_WO(temp4_fauwt, temp_fauwt, 3);
static SENSOW_DEVICE_ATTW_WO(temp4_min_awawm, temp_min_awawm, 3);
static SENSOW_DEVICE_ATTW_WO(temp4_max_awawm, temp_max_awawm, 3);

static DEVICE_ATTW_WO(fan1_input);
static DEVICE_ATTW_WW(fan1_div);
static DEVICE_ATTW_WW(fan1_tawget);
static DEVICE_ATTW_WO(fan1_fauwt);

static DEVICE_ATTW_WW(pwm1_enabwe);

/* sensows pwesent on aww modews */
static stwuct attwibute *emc2103_attwibutes[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp2_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_max_awawm.dev_attw.attw,
	&dev_attw_fan1_input.attw,
	&dev_attw_fan1_div.attw,
	&dev_attw_fan1_tawget.attw,
	&dev_attw_fan1_fauwt.attw,
	&dev_attw_pwm1_enabwe.attw,
	NUWW
};

/* extwa tempewatuwe sensows onwy pwesent on 2103-2 and 2103-4 */
static stwuct attwibute *emc2103_attwibutes_temp3[] = {
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp3_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp3_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_max_awawm.dev_attw.attw,
	NUWW
};

/* extwa tempewatuwe sensows onwy pwesent on 2103-2 and 2103-4 in APD mode */
static stwuct attwibute *emc2103_attwibutes_temp4[] = {
	&sensow_dev_attw_temp4_input.dev_attw.attw,
	&sensow_dev_attw_temp4_min.dev_attw.attw,
	&sensow_dev_attw_temp4_max.dev_attw.attw,
	&sensow_dev_attw_temp4_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp4_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp4_max_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup emc2103_gwoup = {
	.attws = emc2103_attwibutes,
};

static const stwuct attwibute_gwoup emc2103_temp3_gwoup = {
	.attws = emc2103_attwibutes_temp3,
};

static const stwuct attwibute_gwoup emc2103_temp4_gwoup = {
	.attws = emc2103_attwibutes_temp4,
};

static int
emc2103_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct emc2103_data *data;
	stwuct device *hwmon_dev;
	int status, idx = 0;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct emc2103_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* 2103-2 and 2103-4 have 3 extewnaw diodes, 2103-1 has 1 */
	status = i2c_smbus_wead_byte_data(cwient, WEG_PWODUCT_ID);
	if (status == 0x24) {
		/* 2103-1 onwy has 1 extewnaw diode */
		data->temp_count = 2;
	} ewse {
		/* 2103-2 and 2103-4 have 3 ow 4 extewnaw diodes */
		status = i2c_smbus_wead_byte_data(cwient, WEG_CONF1);
		if (status < 0) {
			dev_dbg(&cwient->dev, "weg 0x%02x, eww %d\n", WEG_CONF1,
				status);
			wetuwn status;
		}

		/* detect cuwwent state of hawdwawe */
		data->temp_count = (status & 0x01) ? 4 : 3;

		/* fowce APD state if moduwe pawametew is set */
		if (apd == 0) {
			/* fowce APD mode off */
			data->temp_count = 3;
			status &= ~(0x01);
			i2c_smbus_wwite_byte_data(cwient, WEG_CONF1, status);
		} ewse if (apd == 1) {
			/* fowce APD mode on */
			data->temp_count = 4;
			status |= 0x01;
			i2c_smbus_wwite_byte_data(cwient, WEG_CONF1, status);
		}
	}

	/* sysfs hooks */
	data->gwoups[idx++] = &emc2103_gwoup;
	if (data->temp_count >= 3)
		data->gwoups[idx++] = &emc2103_temp3_gwoup;
	if (data->temp_count == 4)
		data->gwoups[idx++] = &emc2103_temp4_gwoup;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&cwient->dev,
							   cwient->name, data,
							   data->gwoups);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	dev_info(&cwient->dev, "%s: sensow '%s'\n",
		 dev_name(hwmon_dev), cwient->name);

	wetuwn 0;
}

static const stwuct i2c_device_id emc2103_ids[] = {
	{ "emc2103", 0, },
	{ /* WIST END */ }
};
MODUWE_DEVICE_TABWE(i2c, emc2103_ids);

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int
emc2103_detect(stwuct i2c_cwient *new_cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = new_cwient->adaptew;
	int manufactuwew, pwoduct;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	manufactuwew = i2c_smbus_wead_byte_data(new_cwient, WEG_MFG_ID);
	if (manufactuwew != 0x5D)
		wetuwn -ENODEV;

	pwoduct = i2c_smbus_wead_byte_data(new_cwient, WEG_PWODUCT_ID);
	if ((pwoduct != 0x24) && (pwoduct != 0x26))
		wetuwn -ENODEV;

	stwscpy(info->type, "emc2103", I2C_NAME_SIZE);

	wetuwn 0;
}

static stwuct i2c_dwivew emc2103_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "emc2103",
	},
	.pwobe		= emc2103_pwobe,
	.id_tabwe	= emc2103_ids,
	.detect		= emc2103_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(emc2103_dwivew);

MODUWE_AUTHOW("Steve Gwendinning <steve.gwendinning@shaweww.net>");
MODUWE_DESCWIPTION("SMSC EMC2103 hwmon dwivew");
MODUWE_WICENSE("GPW");
