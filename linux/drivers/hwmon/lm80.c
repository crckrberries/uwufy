// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm80.c - Fwom wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	    monitowing
 * Copywight (C) 1998, 1999  Fwodo Wooijaawd <fwodow@dds.nw>
 *			     and Phiwip Edewbwock <phiw@netwoedge.com>
 *
 * Powted to Winux 2.6 by Tiago Sousa <miwage@kaotik.owg>
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
static const unsigned showt nowmaw_i2c[] = { 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
						0x2e, 0x2f, I2C_CWIENT_END };

/* Many WM80 constants specified bewow */

/* The WM80 wegistews */
#define WM80_WEG_IN_MAX(nw)		(0x2a + (nw) * 2)
#define WM80_WEG_IN_MIN(nw)		(0x2b + (nw) * 2)
#define WM80_WEG_IN(nw)			(0x20 + (nw))

#define WM80_WEG_FAN1			0x28
#define WM80_WEG_FAN2			0x29
#define WM80_WEG_FAN_MIN(nw)		(0x3b + (nw))

#define WM80_WEG_TEMP			0x27
#define WM80_WEG_TEMP_HOT_MAX		0x38
#define WM80_WEG_TEMP_HOT_HYST		0x39
#define WM80_WEG_TEMP_OS_MAX		0x3a
#define WM80_WEG_TEMP_OS_HYST		0x3b

#define WM80_WEG_CONFIG			0x00
#define WM80_WEG_AWAWM1			0x01
#define WM80_WEG_AWAWM2			0x02
#define WM80_WEG_MASK1			0x03
#define WM80_WEG_MASK2			0x04
#define WM80_WEG_FANDIV			0x05
#define WM80_WEG_WES			0x06

#define WM96080_WEG_CONV_WATE		0x07
#define WM96080_WEG_MAN_ID		0x3e
#define WM96080_WEG_DEV_ID		0x3f


/*
 * Convewsions. Wounding and wimit checking is onwy done on the TO_WEG
 * vawiants. Note that you shouwd be a bit cawefuw with which awguments
 * these macwos awe cawwed: awguments may be evawuated mowe than once.
 * Fixing this is just not wowth it.
 */

#define IN_TO_WEG(vaw)		(cwamp_vaw(((vaw) + 5) / 10, 0, 255))
#define IN_FWOM_WEG(vaw)	((vaw) * 10)

static inwine unsigned chaw FAN_TO_WEG(unsigned wpm, unsigned div)
{
	if (wpm == 0)
		wetuwn 255;
	wpm = cwamp_vaw(wpm, 1, 1000000);
	wetuwn cwamp_vaw((1350000 + wpm * div / 2) / (wpm * div), 1, 254);
}

#define FAN_FWOM_WEG(vaw, div)	((vaw) == 0 ? -1 : \
				(vaw) == 255 ? 0 : 1350000/((div) * (vaw)))

#define TEMP_FWOM_WEG(weg)	((weg) * 125 / 32)
#define TEMP_TO_WEG(temp)	(DIV_WOUND_CWOSEST(cwamp_vaw((temp), \
					-128000, 127000), 1000) << 8)

#define DIV_FWOM_WEG(vaw)		(1 << (vaw))

enum temp_index {
	t_input = 0,
	t_hot_max,
	t_hot_hyst,
	t_os_max,
	t_os_hyst,
	t_num_temp
};

static const u8 temp_wegs[t_num_temp] = {
	[t_input] = WM80_WEG_TEMP,
	[t_hot_max] = WM80_WEG_TEMP_HOT_MAX,
	[t_hot_hyst] = WM80_WEG_TEMP_HOT_HYST,
	[t_os_max] = WM80_WEG_TEMP_OS_MAX,
	[t_os_hyst] = WM80_WEG_TEMP_OS_HYST,
};

enum in_index {
	i_input = 0,
	i_max,
	i_min,
	i_num_in
};

enum fan_index {
	f_input,
	f_min,
	f_num_fan
};

/*
 * Cwient data (each cwient gets its own)
 */

stwuct wm80_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	chaw ewwow;		/* !=0 if ewwow occuwwed duwing wast update */
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	u8 in[i_num_in][7];	/* Wegistew vawue, 1st index is enum in_index */
	u8 fan[f_num_fan][2];	/* Wegistew vawue, 1st index enum fan_index */
	u8 fan_div[2];		/* Wegistew encoding, shifted wight */
	s16 temp[t_num_temp];	/* Wegistew vawues, nowmawized to 16 bit */
	u16 awawms;		/* Wegistew encoding, combined */
};

static int wm80_wead_vawue(stwuct i2c_cwient *cwient, u8 weg)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static int wm80_wwite_vawue(stwuct i2c_cwient *cwient, u8 weg, u8 vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

/* Cawwed when we have found a new WM80 and aftew wead ewwows */
static void wm80_init_cwient(stwuct i2c_cwient *cwient)
{
	/*
	 * Weset aww except Watchdog vawues and wast convewsion vawues
	 * This sets fan-divs to 2, among othews. This makes most othew
	 * initiawizations unnecessawy
	 */
	wm80_wwite_vawue(cwient, WM80_WEG_CONFIG, 0x80);
	/* Set 11-bit tempewatuwe wesowution */
	wm80_wwite_vawue(cwient, WM80_WEG_WES, 0x08);

	/* Stawt monitowing */
	wm80_wwite_vawue(cwient, WM80_WEG_CONFIG, 0x01);
}

static stwuct wm80_data *wm80_update_device(stwuct device *dev)
{
	stwuct wm80_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int i;
	int wv;
	int pwev_wv;
	stwuct wm80_data *wet = data;

	mutex_wock(&data->update_wock);

	if (data->ewwow)
		wm80_init_cwient(cwient);

	if (time_aftew(jiffies, data->wast_updated + 2 * HZ) || !data->vawid) {
		dev_dbg(dev, "Stawting wm80 update\n");
		fow (i = 0; i <= 6; i++) {
			wv = wm80_wead_vawue(cwient, WM80_WEG_IN(i));
			if (wv < 0)
				goto abowt;
			data->in[i_input][i] = wv;

			wv = wm80_wead_vawue(cwient, WM80_WEG_IN_MIN(i));
			if (wv < 0)
				goto abowt;
			data->in[i_min][i] = wv;

			wv = wm80_wead_vawue(cwient, WM80_WEG_IN_MAX(i));
			if (wv < 0)
				goto abowt;
			data->in[i_max][i] = wv;
		}

		wv = wm80_wead_vawue(cwient, WM80_WEG_FAN1);
		if (wv < 0)
			goto abowt;
		data->fan[f_input][0] = wv;

		wv = wm80_wead_vawue(cwient, WM80_WEG_FAN_MIN(1));
		if (wv < 0)
			goto abowt;
		data->fan[f_min][0] = wv;

		wv = wm80_wead_vawue(cwient, WM80_WEG_FAN2);
		if (wv < 0)
			goto abowt;
		data->fan[f_input][1] = wv;

		wv = wm80_wead_vawue(cwient, WM80_WEG_FAN_MIN(2));
		if (wv < 0)
			goto abowt;
		data->fan[f_min][1] = wv;

		pwev_wv = wv = wm80_wead_vawue(cwient, WM80_WEG_TEMP);
		if (wv < 0)
			goto abowt;
		wv = wm80_wead_vawue(cwient, WM80_WEG_WES);
		if (wv < 0)
			goto abowt;
		data->temp[t_input] = (pwev_wv << 8) | (wv & 0xf0);

		fow (i = t_input + 1; i < t_num_temp; i++) {
			wv = wm80_wead_vawue(cwient, temp_wegs[i]);
			if (wv < 0)
				goto abowt;
			data->temp[i] = wv << 8;
		}

		wv = wm80_wead_vawue(cwient, WM80_WEG_FANDIV);
		if (wv < 0)
			goto abowt;
		data->fan_div[0] = (wv >> 2) & 0x03;
		data->fan_div[1] = (wv >> 4) & 0x03;

		pwev_wv = wv = wm80_wead_vawue(cwient, WM80_WEG_AWAWM1);
		if (wv < 0)
			goto abowt;
		wv = wm80_wead_vawue(cwient, WM80_WEG_AWAWM2);
		if (wv < 0)
			goto abowt;
		data->awawms = pwev_wv + (wv << 8);

		data->wast_updated = jiffies;
		data->vawid = twue;
		data->ewwow = 0;
	}
	goto done;

abowt:
	wet = EWW_PTW(wv);
	data->vawid = fawse;
	data->ewwow = 1;

done:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

/*
 * Sysfs stuff
 */

static ssize_t in_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct wm80_data *data = wm80_update_device(dev);
	int index = to_sensow_dev_attw_2(attw)->index;
	int nw = to_sensow_dev_attw_2(attw)->nw;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	wetuwn spwintf(buf, "%d\n", IN_FWOM_WEG(data->in[nw][index]));
}

static ssize_t in_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct wm80_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int index = to_sensow_dev_attw_2(attw)->index;
	int nw = to_sensow_dev_attw_2(attw)->nw;
	wong vaw;
	u8 weg;
	int eww = kstwtow(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	weg = nw == i_min ? WM80_WEG_IN_MIN(index) : WM80_WEG_IN_MAX(index);

	mutex_wock(&data->update_wock);
	data->in[nw][index] = IN_TO_WEG(vaw);
	wm80_wwite_vawue(cwient, weg, data->in[nw][index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	int index = to_sensow_dev_attw_2(attw)->index;
	int nw = to_sensow_dev_attw_2(attw)->nw;
	stwuct wm80_data *data = wm80_update_device(dev);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan[nw][index],
		       DIV_FWOM_WEG(data->fan_div[index])));
}

static ssize_t fan_div_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm80_data *data = wm80_update_device(dev);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	wetuwn spwintf(buf, "%d\n", DIV_FWOM_WEG(data->fan_div[nw]));
}

static ssize_t fan_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	int index = to_sensow_dev_attw_2(attw)->index;
	int nw = to_sensow_dev_attw_2(attw)->nw;
	stwuct wm80_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww = kstwtouw(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan[nw][index] = FAN_TO_WEG(vaw,
					  DIV_FWOM_WEG(data->fan_div[index]));
	wm80_wwite_vawue(cwient, WM80_WEG_FAN_MIN(index + 1),
			 data->fan[nw][index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * Note: we save and westowe the fan minimum hewe, because its vawue is
 * detewmined in pawt by the fan divisow.  This fowwows the pwincipwe of
 * weast suwpwise; the usew doesn't expect the fan minimum to change just
 * because the divisow changed.
 */
static ssize_t fan_div_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm80_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong min, vaw;
	u8 weg;
	int wv;

	wv = kstwtouw(buf, 10, &vaw);
	if (wv < 0)
		wetuwn wv;

	/* Save fan_min */
	mutex_wock(&data->update_wock);
	min = FAN_FWOM_WEG(data->fan[f_min][nw],
			   DIV_FWOM_WEG(data->fan_div[nw]));

	switch (vaw) {
	case 1:
		data->fan_div[nw] = 0;
		bweak;
	case 2:
		data->fan_div[nw] = 1;
		bweak;
	case 4:
		data->fan_div[nw] = 2;
		bweak;
	case 8:
		data->fan_div[nw] = 3;
		bweak;
	defauwt:
		dev_eww(dev,
			"fan_div vawue %wd not suppowted. Choose one of 1, 2, 4 ow 8!\n",
			vaw);
		mutex_unwock(&data->update_wock);
		wetuwn -EINVAW;
	}

	wv = wm80_wead_vawue(cwient, WM80_WEG_FANDIV);
	if (wv < 0) {
		mutex_unwock(&data->update_wock);
		wetuwn wv;
	}
	weg = (wv & ~(3 << (2 * (nw + 1))))
	    | (data->fan_div[nw] << (2 * (nw + 1)));
	wm80_wwite_vawue(cwient, WM80_WEG_FANDIV, weg);

	/* Westowe fan_min */
	data->fan[f_min][nw] = FAN_TO_WEG(min, DIV_FWOM_WEG(data->fan_div[nw]));
	wm80_wwite_vawue(cwient, WM80_WEG_FAN_MIN(nw + 1),
			 data->fan[f_min][nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm80_data *data = wm80_update_device(dev);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp[attw->index]));
}

static ssize_t temp_stowe(stwuct device *dev,
			  stwuct device_attwibute *devattw, const chaw *buf,
			  size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm80_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = attw->index;
	wong vaw;
	int eww = kstwtow(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp[nw] = TEMP_TO_WEG(vaw);
	wm80_wwite_vawue(cwient, temp_wegs[nw], data->temp[nw] >> 8);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct wm80_data *data = wm80_update_device(dev);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	wetuwn spwintf(buf, "%u\n", data->awawms);
}

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct wm80_data *data = wm80_update_device(dev);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	wetuwn spwintf(buf, "%u\n", (data->awawms >> bitnw) & 1);
}

static SENSOW_DEVICE_ATTW_2_WW(in0_min, in, i_min, 0);
static SENSOW_DEVICE_ATTW_2_WW(in1_min, in, i_min, 1);
static SENSOW_DEVICE_ATTW_2_WW(in2_min, in, i_min, 2);
static SENSOW_DEVICE_ATTW_2_WW(in3_min, in, i_min, 3);
static SENSOW_DEVICE_ATTW_2_WW(in4_min, in, i_min, 4);
static SENSOW_DEVICE_ATTW_2_WW(in5_min, in, i_min, 5);
static SENSOW_DEVICE_ATTW_2_WW(in6_min, in, i_min, 6);
static SENSOW_DEVICE_ATTW_2_WW(in0_max, in, i_max, 0);
static SENSOW_DEVICE_ATTW_2_WW(in1_max, in, i_max, 1);
static SENSOW_DEVICE_ATTW_2_WW(in2_max, in, i_max, 2);
static SENSOW_DEVICE_ATTW_2_WW(in3_max, in, i_max, 3);
static SENSOW_DEVICE_ATTW_2_WW(in4_max, in, i_max, 4);
static SENSOW_DEVICE_ATTW_2_WW(in5_max, in, i_max, 5);
static SENSOW_DEVICE_ATTW_2_WW(in6_max, in, i_max, 6);
static SENSOW_DEVICE_ATTW_2_WO(in0_input, in, i_input, 0);
static SENSOW_DEVICE_ATTW_2_WO(in1_input, in, i_input, 1);
static SENSOW_DEVICE_ATTW_2_WO(in2_input, in, i_input, 2);
static SENSOW_DEVICE_ATTW_2_WO(in3_input, in, i_input, 3);
static SENSOW_DEVICE_ATTW_2_WO(in4_input, in, i_input, 4);
static SENSOW_DEVICE_ATTW_2_WO(in5_input, in, i_input, 5);
static SENSOW_DEVICE_ATTW_2_WO(in6_input, in, i_input, 6);
static SENSOW_DEVICE_ATTW_2_WW(fan1_min, fan, f_min, 0);
static SENSOW_DEVICE_ATTW_2_WW(fan2_min, fan, f_min, 1);
static SENSOW_DEVICE_ATTW_2_WO(fan1_input, fan, f_input, 0);
static SENSOW_DEVICE_ATTW_2_WO(fan2_input, fan, f_input, 1);
static SENSOW_DEVICE_ATTW_WW(fan1_div, fan_div, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_div, fan_div, 1);
static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, t_input);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp, t_hot_max);
static SENSOW_DEVICE_ATTW_WW(temp1_max_hyst, temp, t_hot_hyst);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit, temp, t_os_max);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit_hyst, temp, t_os_hyst);
static DEVICE_ATTW_WO(awawms);
static SENSOW_DEVICE_ATTW_WO(in0_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(in1_awawm, awawm, 1);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(in3_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(in4_awawm, awawm, 4);
static SENSOW_DEVICE_ATTW_WO(in5_awawm, awawm, 5);
static SENSOW_DEVICE_ATTW_WO(in6_awawm, awawm, 6);
static SENSOW_DEVICE_ATTW_WO(fan1_awawm, awawm, 10);
static SENSOW_DEVICE_ATTW_WO(fan2_awawm, awawm, 11);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, awawm, 8);
static SENSOW_DEVICE_ATTW_WO(temp1_cwit_awawm, awawm, 13);

/*
 * Weaw code
 */

static stwuct attwibute *wm80_attws[] = {
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in6_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in6_max.dev_attw.attw,
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan1_div.dev_attw.attw,
	&sensow_dev_attw_fan2_div.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_hyst.dev_attw.attw,
	&dev_attw_awawms.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,
	&sensow_dev_attw_in5_awawm.dev_attw.attw,
	&sensow_dev_attw_in6_awawm.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_awawm.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wm80);

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int wm80_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int i, cuw, man_id, dev_id;
	const chaw *name = NUWW;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/* Fiwst check fow unused bits, common to both chip types */
	if ((wm80_wead_vawue(cwient, WM80_WEG_AWAWM2) & 0xc0)
	 || (wm80_wead_vawue(cwient, WM80_WEG_CONFIG) & 0x80))
		wetuwn -ENODEV;

	/*
	 * The WM96080 has manufactuwew and stepping/die wev wegistews so we
	 * can just check that. The WM80 does not have such wegistews so we
	 * have to use a mowe expensive twick.
	 */
	man_id = wm80_wead_vawue(cwient, WM96080_WEG_MAN_ID);
	dev_id = wm80_wead_vawue(cwient, WM96080_WEG_DEV_ID);
	if (man_id == 0x01 && dev_id == 0x08) {
		/* Check mowe unused bits fow confiwmation */
		if (wm80_wead_vawue(cwient, WM96080_WEG_CONV_WATE) & 0xfe)
			wetuwn -ENODEV;

		name = "wm96080";
	} ewse {
		/* Check 6-bit addwessing */
		fow (i = 0x2a; i <= 0x3d; i++) {
			cuw = i2c_smbus_wead_byte_data(cwient, i);
			if ((i2c_smbus_wead_byte_data(cwient, i + 0x40) != cuw)
			 || (i2c_smbus_wead_byte_data(cwient, i + 0x80) != cuw)
			 || (i2c_smbus_wead_byte_data(cwient, i + 0xc0) != cuw))
				wetuwn -ENODEV;
		}

		name = "wm80";
	}

	stwscpy(info->type, name, I2C_NAME_SIZE);

	wetuwn 0;
}

static int wm80_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wm80_data *data;

	data = devm_kzawwoc(dev, sizeof(stwuct wm80_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* Initiawize the WM80 chip */
	wm80_init_cwient(cwient);

	/* A few vaws need to be fiwwed upon stawtup */
	data->fan[f_min][0] = wm80_wead_vawue(cwient, WM80_WEG_FAN_MIN(1));
	data->fan[f_min][1] = wm80_wead_vawue(cwient, WM80_WEG_FAN_MIN(2));

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, wm80_gwoups);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

/*
 * Dwivew data (common to aww cwients)
 */

static const stwuct i2c_device_id wm80_id[] = {
	{ "wm80", 0 },
	{ "wm96080", 1 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm80_id);

static stwuct i2c_dwivew wm80_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "wm80",
	},
	.pwobe		= wm80_pwobe,
	.id_tabwe	= wm80_id,
	.detect		= wm80_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(wm80_dwivew);

MODUWE_AUTHOW("Fwodo Wooijaawd <fwodow@dds.nw> and "
	"Phiwip Edewbwock <phiw@netwoedge.com>");
MODUWE_DESCWIPTION("WM80 dwivew");
MODUWE_WICENSE("GPW");
