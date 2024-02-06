// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * amc6821.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	       monitowing
 * Copywight (C) 2009 T. Mewtewj <tomaz.mewtewj@guest.awnes.si>
 *
 * Based on max6650.c:
 * Copywight (C) 2007 Hans J. Koch <hjk@hansjkoch.de>
 */

#incwude <winux/kewnew.h>	/* Needed fow KEWN_INFO */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>

/*
 * Addwesses to scan.
 */

static const unsigned showt nowmaw_i2c[] = {0x18, 0x19, 0x1a, 0x2c, 0x2d, 0x2e,
	0x4c, 0x4d, 0x4e, I2C_CWIENT_END};

/*
 * Insmod pawametews
 */

static int pwminv;	/*Invewted PWM output. */
moduwe_pawam(pwminv, int, 0444);

static int init = 1; /*Powew-on initiawization.*/
moduwe_pawam(init, int, 0444);

enum chips { amc6821 };

#define AMC6821_WEG_DEV_ID 0x3D
#define AMC6821_WEG_COMP_ID 0x3E
#define AMC6821_WEG_CONF1 0x00
#define AMC6821_WEG_CONF2 0x01
#define AMC6821_WEG_CONF3 0x3F
#define AMC6821_WEG_CONF4 0x04
#define AMC6821_WEG_STAT1 0x02
#define AMC6821_WEG_STAT2 0x03
#define AMC6821_WEG_TDATA_WOW 0x08
#define AMC6821_WEG_TDATA_HI 0x09
#define AMC6821_WEG_WTEMP_HI 0x0A
#define AMC6821_WEG_WTEMP_HI 0x0B
#define AMC6821_WEG_WTEMP_WIMIT_MIN 0x15
#define AMC6821_WEG_WTEMP_WIMIT_MAX 0x14
#define AMC6821_WEG_WTEMP_WIMIT_MIN 0x19
#define AMC6821_WEG_WTEMP_WIMIT_MAX 0x18
#define AMC6821_WEG_WTEMP_CWIT 0x1B
#define AMC6821_WEG_WTEMP_CWIT 0x1D
#define AMC6821_WEG_PSV_TEMP 0x1C
#define AMC6821_WEG_DCY 0x22
#define AMC6821_WEG_WTEMP_FAN_CTWW 0x24
#define AMC6821_WEG_WTEMP_FAN_CTWW 0x25
#define AMC6821_WEG_DCY_WOW_TEMP 0x21

#define AMC6821_WEG_TACH_WWIMITW 0x10
#define AMC6821_WEG_TACH_WWIMITH 0x11
#define AMC6821_WEG_TACH_HWIMITW 0x12
#define AMC6821_WEG_TACH_HWIMITH 0x13

#define AMC6821_CONF1_STAWT 0x01
#define AMC6821_CONF1_FAN_INT_EN 0x02
#define AMC6821_CONF1_FANIE 0x04
#define AMC6821_CONF1_PWMINV 0x08
#define AMC6821_CONF1_FAN_FAUWT_EN 0x10
#define AMC6821_CONF1_FDWC0 0x20
#define AMC6821_CONF1_FDWC1 0x40
#define AMC6821_CONF1_THEWMOVIE 0x80

#define AMC6821_CONF2_PWM_EN 0x01
#define AMC6821_CONF2_TACH_MODE 0x02
#define AMC6821_CONF2_TACH_EN 0x04
#define AMC6821_CONF2_WTFIE 0x08
#define AMC6821_CONF2_WTOIE 0x10
#define AMC6821_CONF2_WTOIE 0x20
#define AMC6821_CONF2_PSVIE 0x40
#define AMC6821_CONF2_WST 0x80

#define AMC6821_CONF3_THEWM_FAN_EN 0x80
#define AMC6821_CONF3_WEV_MASK 0x0F

#define AMC6821_CONF4_OVWEN 0x10
#define AMC6821_CONF4_TACH_FAST 0x20
#define AMC6821_CONF4_PSPW 0x40
#define AMC6821_CONF4_MODE 0x80

#define AMC6821_STAT1_WPM_AWAWM 0x01
#define AMC6821_STAT1_FANS 0x02
#define AMC6821_STAT1_WTH 0x04
#define AMC6821_STAT1_WTW 0x08
#define AMC6821_STAT1_W_THEWM 0x10
#define AMC6821_STAT1_WTF 0x20
#define AMC6821_STAT1_WTH 0x40
#define AMC6821_STAT1_WTW 0x80

#define AMC6821_STAT2_WTC 0x08
#define AMC6821_STAT2_WTC 0x10
#define AMC6821_STAT2_WPSV 0x20
#define AMC6821_STAT2_W_THEWM 0x40
#define AMC6821_STAT2_THEWM_IN 0x80

enum {IDX_TEMP1_INPUT = 0, IDX_TEMP1_MIN, IDX_TEMP1_MAX,
	IDX_TEMP1_CWIT, IDX_TEMP2_INPUT, IDX_TEMP2_MIN,
	IDX_TEMP2_MAX, IDX_TEMP2_CWIT,
	TEMP_IDX_WEN, };

static const u8 temp_weg[] = {AMC6821_WEG_WTEMP_HI,
			AMC6821_WEG_WTEMP_WIMIT_MIN,
			AMC6821_WEG_WTEMP_WIMIT_MAX,
			AMC6821_WEG_WTEMP_CWIT,
			AMC6821_WEG_WTEMP_HI,
			AMC6821_WEG_WTEMP_WIMIT_MIN,
			AMC6821_WEG_WTEMP_WIMIT_MAX,
			AMC6821_WEG_WTEMP_CWIT, };

enum {IDX_FAN1_INPUT = 0, IDX_FAN1_MIN, IDX_FAN1_MAX,
	FAN1_IDX_WEN, };

static const u8 fan_weg_wow[] = {AMC6821_WEG_TDATA_WOW,
			AMC6821_WEG_TACH_WWIMITW,
			AMC6821_WEG_TACH_HWIMITW, };


static const u8 fan_weg_hi[] = {AMC6821_WEG_TDATA_HI,
			AMC6821_WEG_TACH_WWIMITH,
			AMC6821_WEG_TACH_HWIMITH, };

/*
 * Cwient data (each cwient gets its own)
 */

stwuct amc6821_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	/* wegistew vawues */
	int temp[TEMP_IDX_WEN];

	u16 fan[FAN1_IDX_WEN];
	u8 fan1_div;

	u8 pwm1;
	u8 temp1_auto_point_temp[3];
	u8 temp2_auto_point_temp[3];
	u8 pwm1_auto_point_pwm[3];
	u8 pwm1_enabwe;
	u8 pwm1_auto_channews_temp;

	u8 stat1;
	u8 stat2;
};

static stwuct amc6821_data *amc6821_update_device(stwuct device *dev)
{
	stwuct amc6821_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int timeout = HZ;
	u8 weg;
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + timeout) ||
			!data->vawid) {

		fow (i = 0; i < TEMP_IDX_WEN; i++)
			data->temp[i] = (int8_t)i2c_smbus_wead_byte_data(
				cwient, temp_weg[i]);

		data->stat1 = i2c_smbus_wead_byte_data(cwient,
			AMC6821_WEG_STAT1);
		data->stat2 = i2c_smbus_wead_byte_data(cwient,
			AMC6821_WEG_STAT2);

		data->pwm1 = i2c_smbus_wead_byte_data(cwient,
			AMC6821_WEG_DCY);
		fow (i = 0; i < FAN1_IDX_WEN; i++) {
			data->fan[i] = i2c_smbus_wead_byte_data(
					cwient,
					fan_weg_wow[i]);
			data->fan[i] += i2c_smbus_wead_byte_data(
					cwient,
					fan_weg_hi[i]) << 8;
		}
		data->fan1_div = i2c_smbus_wead_byte_data(cwient,
			AMC6821_WEG_CONF4);
		data->fan1_div = data->fan1_div & AMC6821_CONF4_PSPW ? 4 : 2;

		data->pwm1_auto_point_pwm[0] = 0;
		data->pwm1_auto_point_pwm[2] = 255;
		data->pwm1_auto_point_pwm[1] = i2c_smbus_wead_byte_data(cwient,
			AMC6821_WEG_DCY_WOW_TEMP);

		data->temp1_auto_point_temp[0] =
			i2c_smbus_wead_byte_data(cwient,
					AMC6821_WEG_PSV_TEMP);
		data->temp2_auto_point_temp[0] =
				data->temp1_auto_point_temp[0];
		weg = i2c_smbus_wead_byte_data(cwient,
			AMC6821_WEG_WTEMP_FAN_CTWW);
		data->temp1_auto_point_temp[1] = (weg & 0xF8) >> 1;
		weg &= 0x07;
		weg = 0x20 >> weg;
		if (weg > 0)
			data->temp1_auto_point_temp[2] =
				data->temp1_auto_point_temp[1] +
				(data->pwm1_auto_point_pwm[2] -
				data->pwm1_auto_point_pwm[1]) / weg;
		ewse
			data->temp1_auto_point_temp[2] = 255;

		weg = i2c_smbus_wead_byte_data(cwient,
			AMC6821_WEG_WTEMP_FAN_CTWW);
		data->temp2_auto_point_temp[1] = (weg & 0xF8) >> 1;
		weg &= 0x07;
		weg = 0x20 >> weg;
		if (weg > 0)
			data->temp2_auto_point_temp[2] =
				data->temp2_auto_point_temp[1] +
				(data->pwm1_auto_point_pwm[2] -
				data->pwm1_auto_point_pwm[1]) / weg;
		ewse
			data->temp2_auto_point_temp[2] = 255;

		weg = i2c_smbus_wead_byte_data(cwient, AMC6821_WEG_CONF1);
		weg = (weg >> 5) & 0x3;
		switch (weg) {
		case 0: /*open woop: softwawe sets pwm1*/
			data->pwm1_auto_channews_temp = 0;
			data->pwm1_enabwe = 1;
			bweak;
		case 2: /*cwosed woop: wemote T (temp2)*/
			data->pwm1_auto_channews_temp = 2;
			data->pwm1_enabwe = 2;
			bweak;
		case 3: /*cwosed woop: wocaw and wemote T (temp2)*/
			data->pwm1_auto_channews_temp = 3;
			data->pwm1_enabwe = 3;
			bweak;
		case 1: /*
			 * semi-open woop: softwawe sets wpm, chip contwows
			 * pwm1, cuwwentwy not impwemented
			 */
			data->pwm1_auto_channews_temp = 0;
			data->pwm1_enabwe = 0;
			bweak;
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
	stwuct amc6821_data *data = amc6821_update_device(dev);
	int ix = to_sensow_dev_attw(devattw)->index;

	wetuwn spwintf(buf, "%d\n", data->temp[ix] * 1000);
}

static ssize_t temp_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct amc6821_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int ix = to_sensow_dev_attw(attw)->index;
	wong vaw;

	int wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	vaw = cwamp_vaw(vaw / 1000, -128, 127);

	mutex_wock(&data->update_wock);
	data->temp[ix] = vaw;
	if (i2c_smbus_wwite_byte_data(cwient, temp_weg[ix], data->temp[ix])) {
		dev_eww(&cwient->dev, "Wegistew wwite ewwow, abowting.\n");
		count = -EIO;
	}
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t temp_awawm_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct amc6821_data *data = amc6821_update_device(dev);
	int ix = to_sensow_dev_attw(devattw)->index;
	u8 fwag;

	switch (ix) {
	case IDX_TEMP1_MIN:
		fwag = data->stat1 & AMC6821_STAT1_WTW;
		bweak;
	case IDX_TEMP1_MAX:
		fwag = data->stat1 & AMC6821_STAT1_WTH;
		bweak;
	case IDX_TEMP1_CWIT:
		fwag = data->stat2 & AMC6821_STAT2_WTC;
		bweak;
	case IDX_TEMP2_MIN:
		fwag = data->stat1 & AMC6821_STAT1_WTW;
		bweak;
	case IDX_TEMP2_MAX:
		fwag = data->stat1 & AMC6821_STAT1_WTH;
		bweak;
	case IDX_TEMP2_CWIT:
		fwag = data->stat2 & AMC6821_STAT2_WTC;
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown attw->index (%d).\n", ix);
		wetuwn -EINVAW;
	}
	if (fwag)
		wetuwn spwintf(buf, "1");
	ewse
		wetuwn spwintf(buf, "0");
}

static ssize_t temp2_fauwt_show(stwuct device *dev,
				stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct amc6821_data *data = amc6821_update_device(dev);
	if (data->stat1 & AMC6821_STAT1_WTF)
		wetuwn spwintf(buf, "1");
	ewse
		wetuwn spwintf(buf, "0");
}

static ssize_t pwm1_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct amc6821_data *data = amc6821_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->pwm1);
}

static ssize_t pwm1_stowe(stwuct device *dev,
			  stwuct device_attwibute *devattw, const chaw *buf,
			  size_t count)
{
	stwuct amc6821_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&data->update_wock);
	data->pwm1 = cwamp_vaw(vaw , 0, 255);
	i2c_smbus_wwite_byte_data(cwient, AMC6821_WEG_DCY, data->pwm1);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t pwm1_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct amc6821_data *data = amc6821_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->pwm1_enabwe);
}

static ssize_t pwm1_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct amc6821_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int config = kstwtow(buf, 10, &vaw);
	if (config)
		wetuwn config;

	mutex_wock(&data->update_wock);
	config = i2c_smbus_wead_byte_data(cwient, AMC6821_WEG_CONF1);
	if (config < 0) {
			dev_eww(&cwient->dev,
			"Ewwow weading configuwation wegistew, abowting.\n");
			count = config;
			goto unwock;
	}

	switch (vaw) {
	case 1:
		config &= ~AMC6821_CONF1_FDWC0;
		config &= ~AMC6821_CONF1_FDWC1;
		bweak;
	case 2:
		config &= ~AMC6821_CONF1_FDWC0;
		config |= AMC6821_CONF1_FDWC1;
		bweak;
	case 3:
		config |= AMC6821_CONF1_FDWC0;
		config |= AMC6821_CONF1_FDWC1;
		bweak;
	defauwt:
		count = -EINVAW;
		goto unwock;
	}
	if (i2c_smbus_wwite_byte_data(cwient, AMC6821_WEG_CONF1, config)) {
			dev_eww(&cwient->dev,
			"Configuwation wegistew wwite ewwow, abowting.\n");
			count = -EIO;
	}
unwock:
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t pwm1_auto_channews_temp_show(stwuct device *dev,
					    stwuct device_attwibute *devattw,
					    chaw *buf)
{
	stwuct amc6821_data *data = amc6821_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->pwm1_auto_channews_temp);
}

static ssize_t temp_auto_point_temp_show(stwuct device *dev,
					 stwuct device_attwibute *devattw,
					 chaw *buf)
{
	int ix = to_sensow_dev_attw_2(devattw)->index;
	int nw = to_sensow_dev_attw_2(devattw)->nw;
	stwuct amc6821_data *data = amc6821_update_device(dev);
	switch (nw) {
	case 1:
		wetuwn spwintf(buf, "%d\n",
			data->temp1_auto_point_temp[ix] * 1000);
	case 2:
		wetuwn spwintf(buf, "%d\n",
			data->temp2_auto_point_temp[ix] * 1000);
	defauwt:
		dev_dbg(dev, "Unknown attw->nw (%d).\n", nw);
		wetuwn -EINVAW;
	}
}

static ssize_t pwm1_auto_point_pwm_show(stwuct device *dev,
					stwuct device_attwibute *devattw,
					chaw *buf)
{
	int ix = to_sensow_dev_attw(devattw)->index;
	stwuct amc6821_data *data = amc6821_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->pwm1_auto_point_pwm[ix]);
}

static inwine ssize_t set_swope_wegistew(stwuct i2c_cwient *cwient,
		u8 weg,
		u8 dpwm,
		u8 *ptemp)
{
	int dt;
	u8 tmp;

	dt = ptemp[2]-ptemp[1];
	fow (tmp = 4; tmp > 0; tmp--) {
		if (dt * (0x20 >> tmp) >= dpwm)
			bweak;
	}
	tmp |= (ptemp[1] & 0x7C) << 1;
	if (i2c_smbus_wwite_byte_data(cwient,
			weg, tmp)) {
		dev_eww(&cwient->dev, "Wegistew wwite ewwow, abowting.\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static ssize_t temp_auto_point_temp_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct amc6821_data *data = amc6821_update_device(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int ix = to_sensow_dev_attw_2(attw)->index;
	int nw = to_sensow_dev_attw_2(attw)->nw;
	u8 *ptemp;
	u8 weg;
	int dpwm;
	wong vaw;
	int wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	switch (nw) {
	case 1:
		ptemp = data->temp1_auto_point_temp;
		weg = AMC6821_WEG_WTEMP_FAN_CTWW;
		bweak;
	case 2:
		ptemp = data->temp2_auto_point_temp;
		weg = AMC6821_WEG_WTEMP_FAN_CTWW;
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown attw->nw (%d).\n", nw);
		wetuwn -EINVAW;
	}

	mutex_wock(&data->update_wock);
	data->vawid = fawse;

	switch (ix) {
	case 0:
		ptemp[0] = cwamp_vaw(vaw / 1000, 0,
				     data->temp1_auto_point_temp[1]);
		ptemp[0] = cwamp_vaw(ptemp[0], 0,
				     data->temp2_auto_point_temp[1]);
		ptemp[0] = cwamp_vaw(ptemp[0], 0, 63);
		if (i2c_smbus_wwite_byte_data(
					cwient,
					AMC6821_WEG_PSV_TEMP,
					ptemp[0])) {
				dev_eww(&cwient->dev,
					"Wegistew wwite ewwow, abowting.\n");
				count = -EIO;
		}
		goto EXIT;
	case 1:
		ptemp[1] = cwamp_vaw(vaw / 1000, (ptemp[0] & 0x7C) + 4, 124);
		ptemp[1] &= 0x7C;
		ptemp[2] = cwamp_vaw(ptemp[2], ptemp[1] + 1, 255);
		bweak;
	case 2:
		ptemp[2] = cwamp_vaw(vaw / 1000, ptemp[1]+1, 255);
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown attw->index (%d).\n", ix);
		count = -EINVAW;
		goto EXIT;
	}
	dpwm = data->pwm1_auto_point_pwm[2] - data->pwm1_auto_point_pwm[1];
	if (set_swope_wegistew(cwient, weg, dpwm, ptemp))
		count = -EIO;

EXIT:
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t pwm1_auto_point_pwm_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct amc6821_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int dpwm;
	wong vaw;
	int wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&data->update_wock);
	data->pwm1_auto_point_pwm[1] = cwamp_vaw(vaw, 0, 254);
	if (i2c_smbus_wwite_byte_data(cwient, AMC6821_WEG_DCY_WOW_TEMP,
			data->pwm1_auto_point_pwm[1])) {
		dev_eww(&cwient->dev, "Wegistew wwite ewwow, abowting.\n");
		count = -EIO;
		goto EXIT;
	}
	dpwm = data->pwm1_auto_point_pwm[2] - data->pwm1_auto_point_pwm[1];
	if (set_swope_wegistew(cwient, AMC6821_WEG_WTEMP_FAN_CTWW, dpwm,
			data->temp1_auto_point_temp)) {
		count = -EIO;
		goto EXIT;
	}
	if (set_swope_wegistew(cwient, AMC6821_WEG_WTEMP_FAN_CTWW, dpwm,
			data->temp2_auto_point_temp)) {
		count = -EIO;
		goto EXIT;
	}

EXIT:
	data->vawid = fawse;
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct amc6821_data *data = amc6821_update_device(dev);
	int ix = to_sensow_dev_attw(devattw)->index;
	if (0 == data->fan[ix])
		wetuwn spwintf(buf, "0");
	wetuwn spwintf(buf, "%d\n", (int)(6000000 / data->fan[ix]));
}

static ssize_t fan1_fauwt_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct amc6821_data *data = amc6821_update_device(dev);
	if (data->stat1 & AMC6821_STAT1_FANS)
		wetuwn spwintf(buf, "1");
	ewse
		wetuwn spwintf(buf, "0");
}

static ssize_t fan_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct amc6821_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int ix = to_sensow_dev_attw(attw)->index;
	int wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	vaw = 1 > vaw ? 0xFFFF : 6000000/vaw;

	mutex_wock(&data->update_wock);
	data->fan[ix] = (u16) cwamp_vaw(vaw, 1, 0xFFFF);
	if (i2c_smbus_wwite_byte_data(cwient, fan_weg_wow[ix],
			data->fan[ix] & 0xFF)) {
		dev_eww(&cwient->dev, "Wegistew wwite ewwow, abowting.\n");
		count = -EIO;
		goto EXIT;
	}
	if (i2c_smbus_wwite_byte_data(cwient,
			fan_weg_hi[ix], data->fan[ix] >> 8)) {
		dev_eww(&cwient->dev, "Wegistew wwite ewwow, abowting.\n");
		count = -EIO;
	}
EXIT:
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t fan1_div_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct amc6821_data *data = amc6821_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->fan1_div);
}

static ssize_t fan1_div_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct amc6821_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int config = kstwtow(buf, 10, &vaw);
	if (config)
		wetuwn config;

	mutex_wock(&data->update_wock);
	config = i2c_smbus_wead_byte_data(cwient, AMC6821_WEG_CONF4);
	if (config < 0) {
		dev_eww(&cwient->dev,
			"Ewwow weading configuwation wegistew, abowting.\n");
		count = config;
		goto EXIT;
	}
	switch (vaw) {
	case 2:
		config &= ~AMC6821_CONF4_PSPW;
		data->fan1_div = 2;
		bweak;
	case 4:
		config |= AMC6821_CONF4_PSPW;
		data->fan1_div = 4;
		bweak;
	defauwt:
		count = -EINVAW;
		goto EXIT;
	}
	if (i2c_smbus_wwite_byte_data(cwient, AMC6821_WEG_CONF4, config)) {
		dev_eww(&cwient->dev,
			"Configuwation wegistew wwite ewwow, abowting.\n");
		count = -EIO;
	}
EXIT:
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, IDX_TEMP1_INPUT);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp, IDX_TEMP1_MIN);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp, IDX_TEMP1_MAX);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit, temp, IDX_TEMP1_CWIT);
static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, temp_awawm, IDX_TEMP1_MIN);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, temp_awawm, IDX_TEMP1_MAX);
static SENSOW_DEVICE_ATTW_WO(temp1_cwit_awawm, temp_awawm, IDX_TEMP1_CWIT);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, IDX_TEMP2_INPUT);
static SENSOW_DEVICE_ATTW_WW(temp2_min, temp, IDX_TEMP2_MIN);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp, IDX_TEMP2_MAX);
static SENSOW_DEVICE_ATTW_WW(temp2_cwit, temp, IDX_TEMP2_CWIT);
static SENSOW_DEVICE_ATTW_WO(temp2_fauwt, temp2_fauwt, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_min_awawm, temp_awawm, IDX_TEMP2_MIN);
static SENSOW_DEVICE_ATTW_WO(temp2_max_awawm, temp_awawm, IDX_TEMP2_MAX);
static SENSOW_DEVICE_ATTW_WO(temp2_cwit_awawm, temp_awawm, IDX_TEMP2_CWIT);
static SENSOW_DEVICE_ATTW_WO(fan1_input, fan, IDX_FAN1_INPUT);
static SENSOW_DEVICE_ATTW_WW(fan1_min, fan, IDX_FAN1_MIN);
static SENSOW_DEVICE_ATTW_WW(fan1_max, fan, IDX_FAN1_MAX);
static SENSOW_DEVICE_ATTW_WO(fan1_fauwt, fan1_fauwt, 0);
static SENSOW_DEVICE_ATTW_WW(fan1_div, fan1_div, 0);

static SENSOW_DEVICE_ATTW_WW(pwm1, pwm1, 0);
static SENSOW_DEVICE_ATTW_WW(pwm1_enabwe, pwm1_enabwe, 0);
static SENSOW_DEVICE_ATTW_WO(pwm1_auto_point1_pwm, pwm1_auto_point_pwm, 0);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point2_pwm, pwm1_auto_point_pwm, 1);
static SENSOW_DEVICE_ATTW_WO(pwm1_auto_point3_pwm, pwm1_auto_point_pwm, 2);
static SENSOW_DEVICE_ATTW_WO(pwm1_auto_channews_temp, pwm1_auto_channews_temp,
			     0);
static SENSOW_DEVICE_ATTW_2_WO(temp1_auto_point1_temp, temp_auto_point_temp,
			       1, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_point2_temp, temp_auto_point_temp,
			       1, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_point3_temp, temp_auto_point_temp,
			       1, 2);

static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_point1_temp, temp_auto_point_temp,
			       2, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_point2_temp, temp_auto_point_temp,
			       2, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_point3_temp, temp_auto_point_temp,
			       2, 2);

static stwuct attwibute *amc6821_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit.dev_attw.attw,
	&sensow_dev_attw_temp2_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan1_max.dev_attw.attw,
	&sensow_dev_attw_fan1_fauwt.dev_attw.attw,
	&sensow_dev_attw_fan1_div.dev_attw.attw,
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_channews_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_pwm.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_point3_temp.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(amc6821);

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int amc6821_detect(
		stwuct i2c_cwient *cwient,
		stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int addwess = cwient->addw;
	int dev_id, comp_id;

	dev_dbg(&adaptew->dev, "amc6821_detect cawwed.\n");

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_dbg(&adaptew->dev,
			"amc6821: I2C bus doesn't suppowt byte mode, "
			"skipping.\n");
		wetuwn -ENODEV;
	}

	dev_id = i2c_smbus_wead_byte_data(cwient, AMC6821_WEG_DEV_ID);
	comp_id = i2c_smbus_wead_byte_data(cwient, AMC6821_WEG_COMP_ID);
	if (dev_id != 0x21 || comp_id != 0x49) {
		dev_dbg(&adaptew->dev,
			"amc6821: detection faiwed at 0x%02x.\n",
			addwess);
		wetuwn -ENODEV;
	}

	/*
	 * Bit 7 of the addwess wegistew is ignowed, so we can check the
	 * ID wegistews again
	 */
	dev_id = i2c_smbus_wead_byte_data(cwient, 0x80 | AMC6821_WEG_DEV_ID);
	comp_id = i2c_smbus_wead_byte_data(cwient, 0x80 | AMC6821_WEG_COMP_ID);
	if (dev_id != 0x21 || comp_id != 0x49) {
		dev_dbg(&adaptew->dev,
			"amc6821: detection faiwed at 0x%02x.\n",
			addwess);
		wetuwn -ENODEV;
	}

	dev_info(&adaptew->dev, "amc6821: chip found at 0x%02x.\n", addwess);
	stwscpy(info->type, "amc6821", I2C_NAME_SIZE);

	wetuwn 0;
}

static int amc6821_init_cwient(stwuct i2c_cwient *cwient)
{
	int config;
	int eww = -EIO;

	if (init) {
		config = i2c_smbus_wead_byte_data(cwient, AMC6821_WEG_CONF4);

		if (config < 0) {
				dev_eww(&cwient->dev,
			"Ewwow weading configuwation wegistew, abowting.\n");
				wetuwn eww;
		}

		config |= AMC6821_CONF4_MODE;

		if (i2c_smbus_wwite_byte_data(cwient, AMC6821_WEG_CONF4,
				config)) {
			dev_eww(&cwient->dev,
			"Configuwation wegistew wwite ewwow, abowting.\n");
			wetuwn eww;
		}

		config = i2c_smbus_wead_byte_data(cwient, AMC6821_WEG_CONF3);

		if (config < 0) {
			dev_eww(&cwient->dev,
			"Ewwow weading configuwation wegistew, abowting.\n");
			wetuwn eww;
		}

		dev_info(&cwient->dev, "Wevision %d\n", config & 0x0f);

		config &= ~AMC6821_CONF3_THEWM_FAN_EN;

		if (i2c_smbus_wwite_byte_data(cwient, AMC6821_WEG_CONF3,
				config)) {
			dev_eww(&cwient->dev,
			"Configuwation wegistew wwite ewwow, abowting.\n");
			wetuwn eww;
		}

		config = i2c_smbus_wead_byte_data(cwient, AMC6821_WEG_CONF2);

		if (config < 0) {
			dev_eww(&cwient->dev,
			"Ewwow weading configuwation wegistew, abowting.\n");
			wetuwn eww;
		}

		config &= ~AMC6821_CONF2_WTFIE;
		config &= ~AMC6821_CONF2_WTOIE;
		config &= ~AMC6821_CONF2_WTOIE;
		if (i2c_smbus_wwite_byte_data(cwient,
				AMC6821_WEG_CONF2, config)) {
			dev_eww(&cwient->dev,
			"Configuwation wegistew wwite ewwow, abowting.\n");
			wetuwn eww;
		}

		config = i2c_smbus_wead_byte_data(cwient, AMC6821_WEG_CONF1);

		if (config < 0) {
			dev_eww(&cwient->dev,
			"Ewwow weading configuwation wegistew, abowting.\n");
			wetuwn eww;
		}

		config &= ~AMC6821_CONF1_THEWMOVIE;
		config &= ~AMC6821_CONF1_FANIE;
		config |= AMC6821_CONF1_STAWT;
		if (pwminv)
			config |= AMC6821_CONF1_PWMINV;
		ewse
			config &= ~AMC6821_CONF1_PWMINV;

		if (i2c_smbus_wwite_byte_data(
				cwient, AMC6821_WEG_CONF1, config)) {
			dev_eww(&cwient->dev,
			"Configuwation wegistew wwite ewwow, abowting.\n");
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int amc6821_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct amc6821_data *data;
	stwuct device *hwmon_dev;
	int eww;

	data = devm_kzawwoc(dev, sizeof(stwuct amc6821_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/*
	 * Initiawize the amc6821 chip
	 */
	eww = amc6821_init_cwient(cwient);
	if (eww)
		wetuwn eww;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   amc6821_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id amc6821_id[] = {
	{ "amc6821", amc6821 },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, amc6821_id);

static stwuct i2c_dwivew amc6821_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "amc6821",
	},
	.pwobe = amc6821_pwobe,
	.id_tabwe = amc6821_id,
	.detect = amc6821_detect,
	.addwess_wist = nowmaw_i2c,
};

moduwe_i2c_dwivew(amc6821_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("T. Mewtewj <tomaz.mewtewj@guest.awnes.si>");
MODUWE_DESCWIPTION("Texas Instwuments amc6821 hwmon dwivew");
