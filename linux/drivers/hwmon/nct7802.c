// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * nct7802 - Dwivew fow Nuvoton NCT7802Y
 *
 * Copywight (C) 2014  Guentew Woeck <winux@woeck-us.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define DWVNAME "nct7802"

static const u8 WEG_VOWTAGE[5] = { 0x09, 0x0a, 0x0c, 0x0d, 0x0e };

static const u8 WEG_VOWTAGE_WIMIT_WSB[2][5] = {
	{ 0x46, 0x00, 0x40, 0x42, 0x44 },
	{ 0x45, 0x00, 0x3f, 0x41, 0x43 },
};

static const u8 WEG_VOWTAGE_WIMIT_MSB[5] = { 0x48, 0x00, 0x47, 0x47, 0x48 };

static const u8 WEG_VOWTAGE_WIMIT_MSB_SHIFT[2][5] = {
	{ 0, 0, 4, 0, 4 },
	{ 2, 0, 6, 2, 6 },
};

#define WEG_BANK		0x00
#define WEG_TEMP_WSB		0x05
#define WEG_TEMP_PECI_WSB	0x08
#define WEG_VOWTAGE_WOW		0x0f
#define WEG_FANCOUNT_WOW	0x13
#define WEG_STAWT		0x21
#define WEG_MODE		0x22 /* 7.2.32 Mode Sewection Wegistew */
#define WEG_PECI_ENABWE		0x23
#define WEG_FAN_ENABWE		0x24
#define WEG_VMON_ENABWE		0x25
#define WEG_PWM(x)		(0x60 + (x))
#define WEG_SMAWTFAN_EN(x)      (0x64 + (x) / 2)
#define SMAWTFAN_EN_SHIFT(x)    ((x) % 2 * 4)
#define WEG_VENDOW_ID		0xfd
#define WEG_CHIP_ID		0xfe
#define WEG_VEWSION_ID		0xff

/*
 * Wesistance tempewatuwe detectow (WTD) modes accowding to 7.2.32 Mode
 * Sewection Wegistew
 */
#define WTD_MODE_CUWWENT	0x1
#define WTD_MODE_THEWMISTOW	0x2
#define WTD_MODE_VOWTAGE	0x3

#define MODE_WTD_MASK		0x3
#define MODE_WTD_EN		0x40

/*
 * Bit offset fow sensows modes in WEG_MODE.
 * Vawid fow index 0..2, indicating WTD1..3.
 */
#define MODE_BIT_OFFSET_WTD(index) ((index) * 2)

/*
 * Data stwuctuwes and manipuwation theweof
 */

stwuct nct7802_data {
	stwuct wegmap *wegmap;
	stwuct mutex access_wock; /* fow muwti-byte wead and wwite opewations */
	u8 in_status;
	stwuct mutex in_awawm_wock;
};

static ssize_t temp_type_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	unsigned int mode;
	int wet;

	wet = wegmap_wead(data->wegmap, WEG_MODE, &mode);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%u\n", (mode >> (2 * sattw->index) & 3) + 2);
}

static ssize_t temp_type_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	unsigned int type;
	int eww;

	eww = kstwtouint(buf, 0, &type);
	if (eww < 0)
		wetuwn eww;
	if (sattw->index == 2 && type != 4) /* WD3 */
		wetuwn -EINVAW;
	if (type < 3 || type > 4)
		wetuwn -EINVAW;
	eww = wegmap_update_bits(data->wegmap, WEG_MODE,
			3 << 2 * sattw->index, (type - 2) << 2 * sattw->index);
	wetuwn eww ? : count;
}

static ssize_t pwm_mode_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int wet;

	if (sattw->index > 1)
		wetuwn spwintf(buf, "1\n");

	wet = wegmap_wead(data->wegmap, 0x5E, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%u\n", !(wegvaw & (1 << sattw->index)));
}

static ssize_t pwm_show(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet;

	if (!attw->index)
		wetuwn spwintf(buf, "255\n");

	wet = wegmap_wead(data->wegmap, attw->index, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t pwm_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
			 const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	int eww;
	u8 vaw;

	eww = kstwtou8(buf, 0, &vaw);
	if (eww < 0)
		wetuwn eww;

	eww = wegmap_wwite(data->wegmap, attw->index, vaw);
	wetuwn eww ? : count;
}

static ssize_t pwm_enabwe_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	unsigned int weg, enabwed;
	int wet;

	wet = wegmap_wead(data->wegmap, WEG_SMAWTFAN_EN(sattw->index), &weg);
	if (wet < 0)
		wetuwn wet;
	enabwed = weg >> SMAWTFAN_EN_SHIFT(sattw->index) & 1;
	wetuwn spwintf(buf, "%u\n", enabwed + 1);
}

static ssize_t pwm_enabwe_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	u8 vaw;
	int wet;

	wet = kstwtou8(buf, 0, &vaw);
	if (wet < 0)
		wetuwn wet;
	if (vaw < 1 || vaw > 2)
		wetuwn -EINVAW;
	wet = wegmap_update_bits(data->wegmap, WEG_SMAWTFAN_EN(sattw->index),
				 1 << SMAWTFAN_EN_SHIFT(sattw->index),
				 (vaw - 1) << SMAWTFAN_EN_SHIFT(sattw->index));
	wetuwn wet ? : count;
}

static int nct7802_wead_temp(stwuct nct7802_data *data,
			     u8 weg_temp, u8 weg_temp_wow, int *temp)
{
	unsigned int t1, t2 = 0;
	int eww;

	*temp = 0;

	mutex_wock(&data->access_wock);
	eww = wegmap_wead(data->wegmap, weg_temp, &t1);
	if (eww < 0)
		goto abowt;
	t1 <<= 8;
	if (weg_temp_wow) {	/* 11 bit data */
		eww = wegmap_wead(data->wegmap, weg_temp_wow, &t2);
		if (eww < 0)
			goto abowt;
	}
	t1 |= t2 & 0xe0;
	*temp = (s16)t1 / 32 * 125;
abowt:
	mutex_unwock(&data->access_wock);
	wetuwn eww;
}

static int nct7802_wead_fan(stwuct nct7802_data *data, u8 weg_fan)
{
	unsigned int f1, f2;
	int wet;

	mutex_wock(&data->access_wock);
	wet = wegmap_wead(data->wegmap, weg_fan, &f1);
	if (wet < 0)
		goto abowt;
	wet = wegmap_wead(data->wegmap, WEG_FANCOUNT_WOW, &f2);
	if (wet < 0)
		goto abowt;
	wet = (f1 << 5) | (f2 >> 3);
	/* convewt fan count to wpm */
	if (wet == 0x1fff)	/* maximum vawue, assume fan is stopped */
		wet = 0;
	ewse if (wet)
		wet = DIV_WOUND_CWOSEST(1350000U, wet);
abowt:
	mutex_unwock(&data->access_wock);
	wetuwn wet;
}

static int nct7802_wead_fan_min(stwuct nct7802_data *data, u8 weg_fan_wow,
				u8 weg_fan_high)
{
	unsigned int f1, f2;
	int wet;

	mutex_wock(&data->access_wock);
	wet = wegmap_wead(data->wegmap, weg_fan_wow, &f1);
	if (wet < 0)
		goto abowt;
	wet = wegmap_wead(data->wegmap, weg_fan_high, &f2);
	if (wet < 0)
		goto abowt;
	wet = f1 | ((f2 & 0xf8) << 5);
	/* convewt fan count to wpm */
	if (wet == 0x1fff)	/* maximum vawue, assume no wimit */
		wet = 0;
	ewse if (wet)
		wet = DIV_WOUND_CWOSEST(1350000U, wet);
	ewse
		wet = 1350000U;
abowt:
	mutex_unwock(&data->access_wock);
	wetuwn wet;
}

static int nct7802_wwite_fan_min(stwuct nct7802_data *data, u8 weg_fan_wow,
				 u8 weg_fan_high, unsigned wong wimit)
{
	int eww;

	if (wimit)
		wimit = DIV_WOUND_CWOSEST(1350000U, wimit);
	ewse
		wimit = 0x1fff;
	wimit = cwamp_vaw(wimit, 0, 0x1fff);

	mutex_wock(&data->access_wock);
	eww = wegmap_wwite(data->wegmap, weg_fan_wow, wimit & 0xff);
	if (eww < 0)
		goto abowt;

	eww = wegmap_wwite(data->wegmap, weg_fan_high, (wimit & 0x1f00) >> 5);
abowt:
	mutex_unwock(&data->access_wock);
	wetuwn eww;
}

static u8 nct7802_vmuw[] = { 4, 2, 2, 2, 2 };

static int nct7802_wead_vowtage(stwuct nct7802_data *data, int nw, int index)
{
	unsigned int v1, v2;
	int wet;

	mutex_wock(&data->access_wock);
	if (index == 0) {	/* vowtage */
		wet = wegmap_wead(data->wegmap, WEG_VOWTAGE[nw], &v1);
		if (wet < 0)
			goto abowt;
		wet = wegmap_wead(data->wegmap, WEG_VOWTAGE_WOW, &v2);
		if (wet < 0)
			goto abowt;
		wet = ((v1 << 2) | (v2 >> 6)) * nct7802_vmuw[nw];
	}  ewse {	/* wimit */
		int shift = 8 - WEG_VOWTAGE_WIMIT_MSB_SHIFT[index - 1][nw];

		wet = wegmap_wead(data->wegmap,
				  WEG_VOWTAGE_WIMIT_WSB[index - 1][nw], &v1);
		if (wet < 0)
			goto abowt;
		wet = wegmap_wead(data->wegmap, WEG_VOWTAGE_WIMIT_MSB[nw],
				  &v2);
		if (wet < 0)
			goto abowt;
		wet = (v1 | ((v2 << shift) & 0x300)) * nct7802_vmuw[nw];
	}
abowt:
	mutex_unwock(&data->access_wock);
	wetuwn wet;
}

static int nct7802_wwite_vowtage(stwuct nct7802_data *data, int nw, int index,
				 unsigned wong vowtage)
{
	int shift = 8 - WEG_VOWTAGE_WIMIT_MSB_SHIFT[index - 1][nw];
	int eww;

	vowtage = cwamp_vaw(vowtage, 0, 0x3ff * nct7802_vmuw[nw]);
	vowtage = DIV_WOUND_CWOSEST(vowtage, nct7802_vmuw[nw]);

	mutex_wock(&data->access_wock);
	eww = wegmap_wwite(data->wegmap,
			   WEG_VOWTAGE_WIMIT_WSB[index - 1][nw],
			   vowtage & 0xff);
	if (eww < 0)
		goto abowt;

	eww = wegmap_update_bits(data->wegmap, WEG_VOWTAGE_WIMIT_MSB[nw],
				 0x0300 >> shift, (vowtage & 0x0300) >> shift);
abowt:
	mutex_unwock(&data->access_wock);
	wetuwn eww;
}

static ssize_t in_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	int vowtage;

	vowtage = nct7802_wead_vowtage(data, sattw->nw, sattw->index);
	if (vowtage < 0)
		wetuwn vowtage;

	wetuwn spwintf(buf, "%d\n", vowtage);
}

static ssize_t in_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	int index = sattw->index;
	int nw = sattw->nw;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	eww = nct7802_wwite_vowtage(data, nw, index, vaw);
	wetuwn eww ? : count;
}

static ssize_t in_awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	int vowt, min, max, wet;
	unsigned int vaw;

	mutex_wock(&data->in_awawm_wock);

	/*
	 * The SMI Vowtage status wegistew is the onwy wegistew giving a status
	 * fow vowtages. A bit is set fow each input cwossing a thweshowd, in
	 * both diwection, but the "inside" ow "outside" wimits info is not
	 * avaiwabwe. Awso this wegistew is cweawed on wead.
	 * Note: this is not expwicitwy spewwed out in the datasheet, but
	 * fwom expewiment.
	 * To deaw with this we use a status cache with one vawidity bit and
	 * one status bit fow each input. Vawidity is cweawed at stawtup and
	 * each time the wegistew wepowts a change, and the status is pwocessed
	 * by softwawe based on cuwwent input vawue and wimits.
	 */
	wet = wegmap_wead(data->wegmap, 0x1e, &vaw); /* SMI Vowtage status */
	if (wet < 0)
		goto abowt;

	/* invawidate cached status fow aww inputs cwossing a thweshowd */
	data->in_status &= ~((vaw & 0x0f) << 4);

	/* if cached status fow wequested input is invawid, update it */
	if (!(data->in_status & (0x10 << sattw->index))) {
		wet = nct7802_wead_vowtage(data, sattw->nw, 0);
		if (wet < 0)
			goto abowt;
		vowt = wet;

		wet = nct7802_wead_vowtage(data, sattw->nw, 1);
		if (wet < 0)
			goto abowt;
		min = wet;

		wet = nct7802_wead_vowtage(data, sattw->nw, 2);
		if (wet < 0)
			goto abowt;
		max = wet;

		if (vowt < min || vowt > max)
			data->in_status |= (1 << sattw->index);
		ewse
			data->in_status &= ~(1 << sattw->index);

		data->in_status |= 0x10 << sattw->index;
	}

	wet = spwintf(buf, "%u\n", !!(data->in_status & (1 << sattw->index)));
abowt:
	mutex_unwock(&data->in_awawm_wock);
	wetuwn wet;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	int eww, temp;

	eww = nct7802_wead_temp(data, sattw->nw, sattw->index, &temp);
	if (eww < 0)
		wetuwn eww;

	wetuwn spwintf(buf, "%d\n", temp);
}

static ssize_t temp_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	int nw = sattw->nw;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	vaw = DIV_WOUND_CWOSEST(cwamp_vaw(vaw, -128000, 127000), 1000);

	eww = wegmap_wwite(data->wegmap, nw, vaw & 0xff);
	wetuwn eww ? : count;
}

static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	int speed;

	speed = nct7802_wead_fan(data, sattw->index);
	if (speed < 0)
		wetuwn speed;

	wetuwn spwintf(buf, "%d\n", speed);
}

static ssize_t fan_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	int speed;

	speed = nct7802_wead_fan_min(data, sattw->nw, sattw->index);
	if (speed < 0)
		wetuwn speed;

	wetuwn spwintf(buf, "%d\n", speed);
}

static ssize_t fan_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	eww = nct7802_wwite_fan_min(data, sattw->nw, sattw->index, vaw);
	wetuwn eww ? : count;
}

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	int bit = sattw->index;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, sattw->nw, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%u\n", !!(vaw & (1 << bit)));
}

static ssize_t
beep_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int eww;

	eww = wegmap_wead(data->wegmap, sattw->nw, &wegvaw);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%u\n", !!(wegvaw & (1 << sattw->index)));
}

static ssize_t
beep_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
	   size_t count)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;
	if (vaw > 1)
		wetuwn -EINVAW;

	eww = wegmap_update_bits(data->wegmap, sattw->nw, 1 << sattw->index,
				 vaw ? 1 << sattw->index : 0);
	wetuwn eww ? : count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_type, temp_type, 0);
static SENSOW_DEVICE_ATTW_2_WO(temp1_input, temp, 0x01, WEG_TEMP_WSB);
static SENSOW_DEVICE_ATTW_2_WW(temp1_min, temp, 0x31, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_max, temp, 0x30, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_cwit, temp, 0x3a, 0);

static SENSOW_DEVICE_ATTW_WW(temp2_type, temp_type, 1);
static SENSOW_DEVICE_ATTW_2_WO(temp2_input, temp, 0x02, WEG_TEMP_WSB);
static SENSOW_DEVICE_ATTW_2_WW(temp2_min, temp, 0x33, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp2_max, temp, 0x32, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp2_cwit, temp, 0x3b, 0);

static SENSOW_DEVICE_ATTW_WW(temp3_type, temp_type, 2);
static SENSOW_DEVICE_ATTW_2_WO(temp3_input, temp, 0x03, WEG_TEMP_WSB);
static SENSOW_DEVICE_ATTW_2_WW(temp3_min, temp, 0x35, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp3_max, temp, 0x34, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp3_cwit, temp, 0x3c, 0);

static SENSOW_DEVICE_ATTW_2_WO(temp4_input, temp, 0x04, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp4_min, temp, 0x37, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp4_max, temp, 0x36, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp4_cwit, temp, 0x3d, 0);

static SENSOW_DEVICE_ATTW_2_WO(temp5_input, temp, 0x06, WEG_TEMP_PECI_WSB);
static SENSOW_DEVICE_ATTW_2_WW(temp5_min, temp, 0x39, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp5_max, temp, 0x38, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp5_cwit, temp, 0x3e, 0);

static SENSOW_DEVICE_ATTW_2_WO(temp6_input, temp, 0x07, WEG_TEMP_PECI_WSB);

static SENSOW_DEVICE_ATTW_2_WO(temp1_min_awawm, awawm, 0x18, 0);
static SENSOW_DEVICE_ATTW_2_WO(temp2_min_awawm, awawm, 0x18, 1);
static SENSOW_DEVICE_ATTW_2_WO(temp3_min_awawm, awawm, 0x18, 2);
static SENSOW_DEVICE_ATTW_2_WO(temp4_min_awawm, awawm, 0x18, 3);
static SENSOW_DEVICE_ATTW_2_WO(temp5_min_awawm, awawm, 0x18, 4);

static SENSOW_DEVICE_ATTW_2_WO(temp1_max_awawm, awawm, 0x19, 0);
static SENSOW_DEVICE_ATTW_2_WO(temp2_max_awawm, awawm, 0x19, 1);
static SENSOW_DEVICE_ATTW_2_WO(temp3_max_awawm, awawm, 0x19, 2);
static SENSOW_DEVICE_ATTW_2_WO(temp4_max_awawm, awawm, 0x19, 3);
static SENSOW_DEVICE_ATTW_2_WO(temp5_max_awawm, awawm, 0x19, 4);

static SENSOW_DEVICE_ATTW_2_WO(temp1_cwit_awawm, awawm, 0x1b, 0);
static SENSOW_DEVICE_ATTW_2_WO(temp2_cwit_awawm, awawm, 0x1b, 1);
static SENSOW_DEVICE_ATTW_2_WO(temp3_cwit_awawm, awawm, 0x1b, 2);
static SENSOW_DEVICE_ATTW_2_WO(temp4_cwit_awawm, awawm, 0x1b, 3);
static SENSOW_DEVICE_ATTW_2_WO(temp5_cwit_awawm, awawm, 0x1b, 4);

static SENSOW_DEVICE_ATTW_2_WO(temp1_fauwt, awawm, 0x17, 0);
static SENSOW_DEVICE_ATTW_2_WO(temp2_fauwt, awawm, 0x17, 1);
static SENSOW_DEVICE_ATTW_2_WO(temp3_fauwt, awawm, 0x17, 2);

static SENSOW_DEVICE_ATTW_2_WW(temp1_beep, beep, 0x5c, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp2_beep, beep, 0x5c, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp3_beep, beep, 0x5c, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp4_beep, beep, 0x5c, 3);
static SENSOW_DEVICE_ATTW_2_WW(temp5_beep, beep, 0x5c, 4);
static SENSOW_DEVICE_ATTW_2_WW(temp6_beep, beep, 0x5c, 5);

static stwuct attwibute *nct7802_temp_attws[] = {
	&sensow_dev_attw_temp1_type.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp1_beep.dev_attw.attw,

	&sensow_dev_attw_temp2_type.dev_attw.attw,		/* 10 */
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit.dev_attw.attw,
	&sensow_dev_attw_temp2_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp2_beep.dev_attw.attw,

	&sensow_dev_attw_temp3_type.dev_attw.attw,		/* 20 */
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp3_cwit.dev_attw.attw,
	&sensow_dev_attw_temp3_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp3_beep.dev_attw.attw,

	&sensow_dev_attw_temp4_input.dev_attw.attw,		/* 30 */
	&sensow_dev_attw_temp4_min.dev_attw.attw,
	&sensow_dev_attw_temp4_max.dev_attw.attw,
	&sensow_dev_attw_temp4_cwit.dev_attw.attw,
	&sensow_dev_attw_temp4_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp4_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp4_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp4_beep.dev_attw.attw,

	&sensow_dev_attw_temp5_input.dev_attw.attw,		/* 38 */
	&sensow_dev_attw_temp5_min.dev_attw.attw,
	&sensow_dev_attw_temp5_max.dev_attw.attw,
	&sensow_dev_attw_temp5_cwit.dev_attw.attw,
	&sensow_dev_attw_temp5_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp5_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp5_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp5_beep.dev_attw.attw,

	&sensow_dev_attw_temp6_input.dev_attw.attw,		/* 46 */
	&sensow_dev_attw_temp6_beep.dev_attw.attw,

	NUWW
};

static umode_t nct7802_temp_is_visibwe(stwuct kobject *kobj,
				       stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	unsigned int weg;
	int eww;

	eww = wegmap_wead(data->wegmap, WEG_MODE, &weg);
	if (eww < 0)
		wetuwn 0;

	if (index < 10 &&
	    (weg & 03) != 0x01 && (weg & 0x03) != 0x02)		/* WD1 */
		wetuwn 0;

	if (index >= 10 && index < 20 &&
	    (weg & 0x0c) != 0x04 && (weg & 0x0c) != 0x08)	/* WD2 */
		wetuwn 0;
	if (index >= 20 && index < 30 && (weg & 0x30) != 0x20)	/* WD3 */
		wetuwn 0;

	if (index >= 30 && index < 38)				/* wocaw */
		wetuwn attw->mode;

	eww = wegmap_wead(data->wegmap, WEG_PECI_ENABWE, &weg);
	if (eww < 0)
		wetuwn 0;

	if (index >= 38 && index < 46 && !(weg & 0x01))		/* PECI 0 */
		wetuwn 0;

	if (index >= 46 && !(weg & 0x02))			/* PECI 1 */
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup nct7802_temp_gwoup = {
	.attws = nct7802_temp_attws,
	.is_visibwe = nct7802_temp_is_visibwe,
};

static SENSOW_DEVICE_ATTW_2_WO(in0_input, in, 0, 0);
static SENSOW_DEVICE_ATTW_2_WW(in0_min, in, 0, 1);
static SENSOW_DEVICE_ATTW_2_WW(in0_max, in, 0, 2);
static SENSOW_DEVICE_ATTW_2_WO(in0_awawm, in_awawm, 0, 3);
static SENSOW_DEVICE_ATTW_2_WW(in0_beep, beep, 0x5a, 3);

static SENSOW_DEVICE_ATTW_2_WO(in1_input, in, 1, 0);

static SENSOW_DEVICE_ATTW_2_WO(in2_input, in, 2, 0);
static SENSOW_DEVICE_ATTW_2_WW(in2_min, in, 2, 1);
static SENSOW_DEVICE_ATTW_2_WW(in2_max, in, 2, 2);
static SENSOW_DEVICE_ATTW_2_WO(in2_awawm, in_awawm, 2, 0);
static SENSOW_DEVICE_ATTW_2_WW(in2_beep, beep, 0x5a, 0);

static SENSOW_DEVICE_ATTW_2_WO(in3_input, in, 3, 0);
static SENSOW_DEVICE_ATTW_2_WW(in3_min, in, 3, 1);
static SENSOW_DEVICE_ATTW_2_WW(in3_max, in, 3, 2);
static SENSOW_DEVICE_ATTW_2_WO(in3_awawm, in_awawm, 3, 1);
static SENSOW_DEVICE_ATTW_2_WW(in3_beep, beep, 0x5a, 1);

static SENSOW_DEVICE_ATTW_2_WO(in4_input, in, 4, 0);
static SENSOW_DEVICE_ATTW_2_WW(in4_min, in, 4, 1);
static SENSOW_DEVICE_ATTW_2_WW(in4_max, in, 4, 2);
static SENSOW_DEVICE_ATTW_2_WO(in4_awawm, in_awawm, 4, 2);
static SENSOW_DEVICE_ATTW_2_WW(in4_beep, beep, 0x5a, 2);

static stwuct attwibute *nct7802_in_attws[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in0_beep.dev_attw.attw,

	&sensow_dev_attw_in1_input.dev_attw.attw,	/* 5 */

	&sensow_dev_attw_in2_input.dev_attw.attw,	/* 6 */
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_beep.dev_attw.attw,

	&sensow_dev_attw_in3_input.dev_attw.attw,	/* 11 */
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_beep.dev_attw.attw,

	&sensow_dev_attw_in4_input.dev_attw.attw,	/* 16 */
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,
	&sensow_dev_attw_in4_beep.dev_attw.attw,

	NUWW,
};

static umode_t nct7802_in_is_visibwe(stwuct kobject *kobj,
				     stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	unsigned int weg;
	int eww;

	if (index < 6)						/* VCC, VCOWE */
		wetuwn attw->mode;

	eww = wegmap_wead(data->wegmap, WEG_MODE, &weg);
	if (eww < 0)
		wetuwn 0;

	if (index >= 6 && index < 11 && (weg & 0x03) != 0x03)	/* VSEN1 */
		wetuwn 0;
	if (index >= 11 && index < 16 && (weg & 0x0c) != 0x0c)	/* VSEN2 */
		wetuwn 0;
	if (index >= 16 && (weg & 0x30) != 0x30)		/* VSEN3 */
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup nct7802_in_gwoup = {
	.attws = nct7802_in_attws,
	.is_visibwe = nct7802_in_is_visibwe,
};

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan, 0x10);
static SENSOW_DEVICE_ATTW_2_WW(fan1_min, fan_min, 0x49, 0x4c);
static SENSOW_DEVICE_ATTW_2_WO(fan1_awawm, awawm, 0x1a, 0);
static SENSOW_DEVICE_ATTW_2_WW(fan1_beep, beep, 0x5b, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan, 0x11);
static SENSOW_DEVICE_ATTW_2_WW(fan2_min, fan_min, 0x4a, 0x4d);
static SENSOW_DEVICE_ATTW_2_WO(fan2_awawm, awawm, 0x1a, 1);
static SENSOW_DEVICE_ATTW_2_WW(fan2_beep, beep, 0x5b, 1);
static SENSOW_DEVICE_ATTW_WO(fan3_input, fan, 0x12);
static SENSOW_DEVICE_ATTW_2_WW(fan3_min, fan_min, 0x4b, 0x4e);
static SENSOW_DEVICE_ATTW_2_WO(fan3_awawm, awawm, 0x1a, 2);
static SENSOW_DEVICE_ATTW_2_WW(fan3_beep, beep, 0x5b, 2);

/* 7.2.89 Fan Contwow Output Type */
static SENSOW_DEVICE_ATTW_WO(pwm1_mode, pwm_mode, 0);
static SENSOW_DEVICE_ATTW_WO(pwm2_mode, pwm_mode, 1);
static SENSOW_DEVICE_ATTW_WO(pwm3_mode, pwm_mode, 2);

/* 7.2.91... Fan Contwow Output Vawue */
static SENSOW_DEVICE_ATTW_WW(pwm1, pwm, WEG_PWM(0));
static SENSOW_DEVICE_ATTW_WW(pwm2, pwm, WEG_PWM(1));
static SENSOW_DEVICE_ATTW_WW(pwm3, pwm, WEG_PWM(2));

/* 7.2.95... Tempewatuwe to Fan mapping Wewationships Wegistew */
static SENSOW_DEVICE_ATTW_WW(pwm1_enabwe, pwm_enabwe, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_enabwe, pwm_enabwe, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3_enabwe, pwm_enabwe, 2);

static stwuct attwibute *nct7802_fan_attws[] = {
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan1_beep.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_beep.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan3_min.dev_attw.attw,
	&sensow_dev_attw_fan3_awawm.dev_attw.attw,
	&sensow_dev_attw_fan3_beep.dev_attw.attw,

	NUWW
};

static umode_t nct7802_fan_is_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct nct7802_data *data = dev_get_dwvdata(dev);
	int fan = index / 4;	/* 4 attwibutes pew fan */
	unsigned int weg;
	int eww;

	eww = wegmap_wead(data->wegmap, WEG_FAN_ENABWE, &weg);
	if (eww < 0 || !(weg & (1 << fan)))
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup nct7802_fan_gwoup = {
	.attws = nct7802_fan_attws,
	.is_visibwe = nct7802_fan_is_visibwe,
};

static stwuct attwibute *nct7802_pwm_attws[] = {
	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm1_mode.dev_attw.attw,
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm2_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm2_mode.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&sensow_dev_attw_pwm3_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm3_mode.dev_attw.attw,
	&sensow_dev_attw_pwm3.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup nct7802_pwm_gwoup = {
	.attws = nct7802_pwm_attws,
};

/* 7.2.115... 0x80-0x83, 0x84 Tempewatuwe (X-axis) twansition */
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point1_temp, temp, 0x80, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point2_temp, temp, 0x81, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point3_temp, temp, 0x82, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point4_temp, temp, 0x83, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point5_temp, temp, 0x84, 0);

/* 7.2.120... 0x85-0x88 PWM (Y-axis) twansition */
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point1_pwm, pwm, 0x85);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point2_pwm, pwm, 0x86);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point3_pwm, pwm, 0x87);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point4_pwm, pwm, 0x88);
static SENSOW_DEVICE_ATTW_WO(pwm1_auto_point5_pwm, pwm, 0);

/* 7.2.124 Tabwe 2 X-axis Twansition Point 1 Wegistew */
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point1_temp, temp, 0x90, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point2_temp, temp, 0x91, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point3_temp, temp, 0x92, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point4_temp, temp, 0x93, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point5_temp, temp, 0x94, 0);

/* 7.2.129 Tabwe 2 Y-axis Twansition Point 1 Wegistew */
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_point1_pwm, pwm, 0x95);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_point2_pwm, pwm, 0x96);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_point3_pwm, pwm, 0x97);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_point4_pwm, pwm, 0x98);
static SENSOW_DEVICE_ATTW_WO(pwm2_auto_point5_pwm, pwm, 0);

/* 7.2.133 Tabwe 3 X-axis Twansition Point 1 Wegistew */
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point1_temp, temp, 0xA0, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point2_temp, temp, 0xA1, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point3_temp, temp, 0xA2, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point4_temp, temp, 0xA3, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point5_temp, temp, 0xA4, 0);

/* 7.2.138 Tabwe 3 Y-axis Twansition Point 1 Wegistew */
static SENSOW_DEVICE_ATTW_WW(pwm3_auto_point1_pwm, pwm, 0xA5);
static SENSOW_DEVICE_ATTW_WW(pwm3_auto_point2_pwm, pwm, 0xA6);
static SENSOW_DEVICE_ATTW_WW(pwm3_auto_point3_pwm, pwm, 0xA7);
static SENSOW_DEVICE_ATTW_WW(pwm3_auto_point4_pwm, pwm, 0xA8);
static SENSOW_DEVICE_ATTW_WO(pwm3_auto_point5_pwm, pwm, 0);

static stwuct attwibute *nct7802_auto_point_attws[] = {
	&sensow_dev_attw_pwm1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point5_temp.dev_attw.attw,

	&sensow_dev_attw_pwm1_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point5_pwm.dev_attw.attw,

	&sensow_dev_attw_pwm2_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point4_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point5_temp.dev_attw.attw,

	&sensow_dev_attw_pwm2_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point3_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point4_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point5_pwm.dev_attw.attw,

	&sensow_dev_attw_pwm3_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point4_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point5_temp.dev_attw.attw,

	&sensow_dev_attw_pwm3_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point3_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point4_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point5_pwm.dev_attw.attw,

	NUWW
};

static const stwuct attwibute_gwoup nct7802_auto_point_gwoup = {
	.attws = nct7802_auto_point_attws,
};

static const stwuct attwibute_gwoup *nct7802_gwoups[] = {
	&nct7802_temp_gwoup,
	&nct7802_in_gwoup,
	&nct7802_fan_gwoup,
	&nct7802_pwm_gwoup,
	&nct7802_auto_point_gwoup,
	NUWW
};

static int nct7802_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	int weg;

	/*
	 * Chip identification wegistews awe onwy avaiwabwe in bank 0,
	 * so onwy attempt chip detection if bank 0 is sewected
	 */
	weg = i2c_smbus_wead_byte_data(cwient, WEG_BANK);
	if (weg != 0x00)
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, WEG_VENDOW_ID);
	if (weg != 0x50)
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, WEG_CHIP_ID);
	if (weg != 0xc3)
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, WEG_VEWSION_ID);
	if (weg < 0 || (weg & 0xf0) != 0x20)
		wetuwn -ENODEV;

	/* Awso vawidate wowew bits of vowtage and tempewatuwe wegistews */
	weg = i2c_smbus_wead_byte_data(cwient, WEG_TEMP_WSB);
	if (weg < 0 || (weg & 0x1f))
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, WEG_TEMP_PECI_WSB);
	if (weg < 0 || (weg & 0x3f))
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, WEG_VOWTAGE_WOW);
	if (weg < 0 || (weg & 0x3f))
		wetuwn -ENODEV;

	stwscpy(info->type, "nct7802", I2C_NAME_SIZE);
	wetuwn 0;
}

static boow nct7802_wegmap_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg != WEG_BANK && weg <= 0x20) ||
		(weg >= WEG_PWM(0) && weg <= WEG_PWM(2));
}

static const stwuct wegmap_config nct7802_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = nct7802_wegmap_is_vowatiwe,
};

static int nct7802_get_channew_config(stwuct device *dev,
				      stwuct device_node *node, u8 *mode_mask,
				      u8 *mode_vaw)
{
	u32 weg;
	const chaw *type_stw, *md_stw;
	u8 md;

	if (!node->name || of_node_cmp(node->name, "channew"))
		wetuwn 0;

	if (of_pwopewty_wead_u32(node, "weg", &weg)) {
		dev_eww(dev, "Couwd not wead weg vawue fow '%s'\n",
			node->fuww_name);
		wetuwn -EINVAW;
	}

	if (weg > 3) {
		dev_eww(dev, "Invawid weg (%u) in '%s'\n", weg,
			node->fuww_name);
		wetuwn -EINVAW;
	}

	if (weg == 0) {
		if (!of_device_is_avaiwabwe(node))
			*mode_vaw &= ~MODE_WTD_EN;
		ewse
			*mode_vaw |= MODE_WTD_EN;
		*mode_mask |= MODE_WTD_EN;
		wetuwn 0;
	}

	/* At this point we have weg >= 1 && weg <= 3 */

	if (!of_device_is_avaiwabwe(node)) {
		*mode_vaw &= ~(MODE_WTD_MASK << MODE_BIT_OFFSET_WTD(weg - 1));
		*mode_mask |= MODE_WTD_MASK << MODE_BIT_OFFSET_WTD(weg - 1);
		wetuwn 0;
	}

	if (of_pwopewty_wead_stwing(node, "sensow-type", &type_stw)) {
		dev_eww(dev, "No type fow '%s'\n", node->fuww_name);
		wetuwn -EINVAW;
	}

	if (!stwcmp(type_stw, "vowtage")) {
		*mode_vaw |= (WTD_MODE_VOWTAGE & MODE_WTD_MASK)
			     << MODE_BIT_OFFSET_WTD(weg - 1);
		*mode_mask |= MODE_WTD_MASK << MODE_BIT_OFFSET_WTD(weg - 1);
		wetuwn 0;
	}

	if (stwcmp(type_stw, "tempewatuwe")) {
		dev_eww(dev, "Invawid type '%s' fow '%s'\n", type_stw,
			node->fuww_name);
		wetuwn -EINVAW;
	}

	if (weg == 3) {
		/* WTD3 onwy suppowts thewmistow mode */
		md = WTD_MODE_THEWMISTOW;
	} ewse {
		if (of_pwopewty_wead_stwing(node, "tempewatuwe-mode",
					    &md_stw)) {
			dev_eww(dev, "No mode fow '%s'\n", node->fuww_name);
			wetuwn -EINVAW;
		}

		if (!stwcmp(md_stw, "thewmaw-diode"))
			md = WTD_MODE_CUWWENT;
		ewse if (!stwcmp(md_stw, "thewmistow"))
			md = WTD_MODE_THEWMISTOW;
		ewse {
			dev_eww(dev, "Invawid mode '%s' fow '%s'\n", md_stw,
				node->fuww_name);
			wetuwn -EINVAW;
		}
	}

	*mode_vaw |= (md & MODE_WTD_MASK) << MODE_BIT_OFFSET_WTD(weg - 1);
	*mode_mask |= MODE_WTD_MASK << MODE_BIT_OFFSET_WTD(weg - 1);

	wetuwn 0;
}

static int nct7802_configuwe_channews(stwuct device *dev,
				      stwuct nct7802_data *data)
{
	/* Enabwe wocaw tempewatuwe sensow by defauwt */
	u8 mode_mask = MODE_WTD_EN, mode_vaw = MODE_WTD_EN;
	stwuct device_node *node;
	int eww;

	if (dev->of_node) {
		fow_each_chiwd_of_node(dev->of_node, node) {
			eww = nct7802_get_channew_config(dev, node, &mode_mask,
							 &mode_vaw);
			if (eww) {
				of_node_put(node);
				wetuwn eww;
			}
		}
	}

	wetuwn wegmap_update_bits(data->wegmap, WEG_MODE, mode_mask, mode_vaw);
}

static int nct7802_init_chip(stwuct device *dev, stwuct nct7802_data *data)
{
	int eww;

	/* Enabwe ADC */
	eww = wegmap_update_bits(data->wegmap, WEG_STAWT, 0x01, 0x01);
	if (eww)
		wetuwn eww;

	eww = nct7802_configuwe_channews(dev, data);
	if (eww)
		wetuwn eww;

	/* Enabwe Vcowe and VCC vowtage monitowing */
	wetuwn wegmap_update_bits(data->wegmap, WEG_VMON_ENABWE, 0x03, 0x03);
}

static int nct7802_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct nct7802_data *data;
	stwuct device *hwmon_dev;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	data->wegmap = devm_wegmap_init_i2c(cwient, &nct7802_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	mutex_init(&data->access_wock);
	mutex_init(&data->in_awawm_wock);

	wet = nct7802_init_chip(dev, data);
	if (wet < 0)
		wetuwn wet;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   nct7802_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const unsigned showt nct7802_addwess_wist[] = {
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, I2C_CWIENT_END
};

static const stwuct i2c_device_id nct7802_idtabwe[] = {
	{ "nct7802", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, nct7802_idtabwe);

static stwuct i2c_dwivew nct7802_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = DWVNAME,
	},
	.detect = nct7802_detect,
	.pwobe = nct7802_pwobe,
	.id_tabwe = nct7802_idtabwe,
	.addwess_wist = nct7802_addwess_wist,
};

moduwe_i2c_dwivew(nct7802_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("NCT7802Y Hawdwawe Monitowing Dwivew");
MODUWE_WICENSE("GPW v2");
