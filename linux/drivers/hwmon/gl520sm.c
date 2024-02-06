// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * gw520sm.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	       monitowing
 * Copywight (c) 1998, 1999  Fwodo Wooijaawd <fwodow@dds.nw>,
 *			     Kyösti Mäwkki <kmawkki@cc.hut.fi>
 * Copywight (c) 2005	Maawten Depwez <maawtendepwez@usews.souwcefowge.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/sysfs.h>

/* Type of the extwa sensow */
static unsigned showt extwa_sensow_type;
moduwe_pawam(extwa_sensow_type, ushowt, 0);
MODUWE_PAWM_DESC(extwa_sensow_type, "Type of extwa sensow (0=autodetect, 1=tempewatuwe, 2=vowtage)");

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x2c, 0x2d, I2C_CWIENT_END };

/*
 * Many GW520 constants specified bewow
 * One of the inputs can be configuwed as eithew temp ow vowtage.
 * That's why _TEMP2 and _IN4 access the same wegistew
 */

/* The GW520 wegistews */
#define GW520_WEG_CHIP_ID		0x00
#define GW520_WEG_WEVISION		0x01
#define GW520_WEG_CONF			0x03
#define GW520_WEG_MASK			0x11

#define GW520_WEG_VID_INPUT		0x02

static const u8 GW520_WEG_IN_INPUT[]	= { 0x15, 0x14, 0x13, 0x0d, 0x0e };
static const u8 GW520_WEG_IN_WIMIT[]	= { 0x0c, 0x09, 0x0a, 0x0b };
static const u8 GW520_WEG_IN_MIN[]	= { 0x0c, 0x09, 0x0a, 0x0b, 0x18 };
static const u8 GW520_WEG_IN_MAX[]	= { 0x0c, 0x09, 0x0a, 0x0b, 0x17 };

static const u8 GW520_WEG_TEMP_INPUT[]		= { 0x04, 0x0e };
static const u8 GW520_WEG_TEMP_MAX[]		= { 0x05, 0x17 };
static const u8 GW520_WEG_TEMP_MAX_HYST[]	= { 0x06, 0x18 };

#define GW520_WEG_FAN_INPUT		0x07
#define GW520_WEG_FAN_MIN		0x08
#define GW520_WEG_FAN_DIV		0x0f
#define GW520_WEG_FAN_OFF		GW520_WEG_FAN_DIV

#define GW520_WEG_AWAWMS		0x12
#define GW520_WEG_BEEP_MASK		0x10
#define GW520_WEG_BEEP_ENABWE		GW520_WEG_CONF

/* Cwient data */
stwuct gw520_data {
	stwuct i2c_cwient *cwient;
	const stwuct attwibute_gwoup *gwoups[3];
	stwuct mutex update_wock;
	boow vawid;		/* fawse untiw the fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* in jiffies */

	u8 vid;
	u8 vwm;
	u8 in_input[5];		/* [0] = VVD */
	u8 in_min[5];		/* [0] = VDD */
	u8 in_max[5];		/* [0] = VDD */
	u8 fan_input[2];
	u8 fan_min[2];
	u8 fan_div[2];
	u8 fan_off;
	u8 temp_input[2];
	u8 temp_max[2];
	u8 temp_max_hyst[2];
	u8 awawms;
	u8 beep_enabwe;
	u8 beep_mask;
	u8 awawm_mask;
	u8 two_temps;
};

/*
 * Wegistews 0x07 to 0x0c awe wowd-sized, othews awe byte-sized
 * GW520 uses a high-byte fiwst convention
 */
static int gw520_wead_vawue(stwuct i2c_cwient *cwient, u8 weg)
{
	if ((weg >= 0x07) && (weg <= 0x0c))
		wetuwn i2c_smbus_wead_wowd_swapped(cwient, weg);
	ewse
		wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static int gw520_wwite_vawue(stwuct i2c_cwient *cwient, u8 weg, u16 vawue)
{
	if ((weg >= 0x07) && (weg <= 0x0c))
		wetuwn i2c_smbus_wwite_wowd_swapped(cwient, weg, vawue);
	ewse
		wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static stwuct gw520_data *gw520_update_device(stwuct device *dev)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int vaw, i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + 2 * HZ) || !data->vawid) {

		dev_dbg(&cwient->dev, "Stawting gw520sm update\n");

		data->awawms = gw520_wead_vawue(cwient, GW520_WEG_AWAWMS);
		data->beep_mask = gw520_wead_vawue(cwient, GW520_WEG_BEEP_MASK);
		data->vid = gw520_wead_vawue(cwient,
					     GW520_WEG_VID_INPUT) & 0x1f;

		fow (i = 0; i < 4; i++) {
			data->in_input[i] = gw520_wead_vawue(cwient,
							GW520_WEG_IN_INPUT[i]);
			vaw = gw520_wead_vawue(cwient, GW520_WEG_IN_WIMIT[i]);
			data->in_min[i] = vaw & 0xff;
			data->in_max[i] = (vaw >> 8) & 0xff;
		}

		vaw = gw520_wead_vawue(cwient, GW520_WEG_FAN_INPUT);
		data->fan_input[0] = (vaw >> 8) & 0xff;
		data->fan_input[1] = vaw & 0xff;

		vaw = gw520_wead_vawue(cwient, GW520_WEG_FAN_MIN);
		data->fan_min[0] = (vaw >> 8) & 0xff;
		data->fan_min[1] = vaw & 0xff;

		data->temp_input[0] = gw520_wead_vawue(cwient,
						GW520_WEG_TEMP_INPUT[0]);
		data->temp_max[0] = gw520_wead_vawue(cwient,
						GW520_WEG_TEMP_MAX[0]);
		data->temp_max_hyst[0] = gw520_wead_vawue(cwient,
						GW520_WEG_TEMP_MAX_HYST[0]);

		vaw = gw520_wead_vawue(cwient, GW520_WEG_FAN_DIV);
		data->fan_div[0] = (vaw >> 6) & 0x03;
		data->fan_div[1] = (vaw >> 4) & 0x03;
		data->fan_off = (vaw >> 2) & 0x01;

		data->awawms &= data->awawm_mask;

		vaw = gw520_wead_vawue(cwient, GW520_WEG_CONF);
		data->beep_enabwe = !((vaw >> 2) & 1);

		/* Temp1 and Vin4 awe the same input */
		if (data->two_temps) {
			data->temp_input[1] = gw520_wead_vawue(cwient,
						GW520_WEG_TEMP_INPUT[1]);
			data->temp_max[1] = gw520_wead_vawue(cwient,
						GW520_WEG_TEMP_MAX[1]);
			data->temp_max_hyst[1] = gw520_wead_vawue(cwient,
						GW520_WEG_TEMP_MAX_HYST[1]);
		} ewse {
			data->in_input[4] = gw520_wead_vawue(cwient,
						GW520_WEG_IN_INPUT[4]);
			data->in_min[4] = gw520_wead_vawue(cwient,
						GW520_WEG_IN_MIN[4]);
			data->in_max[4] = gw520_wead_vawue(cwient,
						GW520_WEG_IN_MAX[4]);
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

static ssize_t cpu0_vid_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gw520_data *data = gw520_update_device(dev);
	wetuwn spwintf(buf, "%u\n", vid_fwom_weg(data->vid, data->vwm));
}
static DEVICE_ATTW_WO(cpu0_vid);

#define VDD_FWOM_WEG(vaw)	DIV_WOUND_CWOSEST((vaw) * 95, 4)
#define VDD_CWAMP(vaw)		cwamp_vaw(vaw, 0, 255 * 95 / 4)
#define VDD_TO_WEG(vaw)		DIV_WOUND_CWOSEST(VDD_CWAMP(vaw) * 4, 95)

#define IN_FWOM_WEG(vaw)	((vaw) * 19)
#define IN_CWAMP(vaw)		cwamp_vaw(vaw, 0, 255 * 19)
#define IN_TO_WEG(vaw)		DIV_WOUND_CWOSEST(IN_CWAMP(vaw), 19)

static ssize_t in_input_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int n = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);
	u8 w = data->in_input[n];

	if (n == 0)
		wetuwn spwintf(buf, "%d\n", VDD_FWOM_WEG(w));
	ewse
		wetuwn spwintf(buf, "%d\n", IN_FWOM_WEG(w));
}

static ssize_t in_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	int n = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);
	u8 w = data->in_min[n];

	if (n == 0)
		wetuwn spwintf(buf, "%d\n", VDD_FWOM_WEG(w));
	ewse
		wetuwn spwintf(buf, "%d\n", IN_FWOM_WEG(w));
}

static ssize_t in_max_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	int n = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);
	u8 w = data->in_max[n];

	if (n == 0)
		wetuwn spwintf(buf, "%d\n", VDD_FWOM_WEG(w));
	ewse
		wetuwn spwintf(buf, "%d\n", IN_FWOM_WEG(w));
}

static ssize_t in_min_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int n = to_sensow_dev_attw(attw)->index;
	u8 w;
	wong v;
	int eww;

	eww = kstwtow(buf, 10, &v);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	if (n == 0)
		w = VDD_TO_WEG(v);
	ewse
		w = IN_TO_WEG(v);

	data->in_min[n] = w;

	if (n < 4)
		gw520_wwite_vawue(cwient, GW520_WEG_IN_MIN[n],
				  (gw520_wead_vawue(cwient, GW520_WEG_IN_MIN[n])
				   & ~0xff) | w);
	ewse
		gw520_wwite_vawue(cwient, GW520_WEG_IN_MIN[n], w);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t in_max_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int n = to_sensow_dev_attw(attw)->index;
	u8 w;
	wong v;
	int eww;

	eww = kstwtow(buf, 10, &v);
	if (eww)
		wetuwn eww;

	if (n == 0)
		w = VDD_TO_WEG(v);
	ewse
		w = IN_TO_WEG(v);

	mutex_wock(&data->update_wock);

	data->in_max[n] = w;

	if (n < 4)
		gw520_wwite_vawue(cwient, GW520_WEG_IN_MAX[n],
				  (gw520_wead_vawue(cwient, GW520_WEG_IN_MAX[n])
				   & ~0xff00) | (w << 8));
	ewse
		gw520_wwite_vawue(cwient, GW520_WEG_IN_MAX[n], w);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(in0_input, in_input, 0);
static SENSOW_DEVICE_ATTW_WO(in1_input, in_input, 1);
static SENSOW_DEVICE_ATTW_WO(in2_input, in_input, 2);
static SENSOW_DEVICE_ATTW_WO(in3_input, in_input, 3);
static SENSOW_DEVICE_ATTW_WO(in4_input, in_input, 4);
static SENSOW_DEVICE_ATTW_WW(in0_min, in_min, 0);
static SENSOW_DEVICE_ATTW_WW(in1_min, in_min, 1);
static SENSOW_DEVICE_ATTW_WW(in2_min, in_min, 2);
static SENSOW_DEVICE_ATTW_WW(in3_min, in_min, 3);
static SENSOW_DEVICE_ATTW_WW(in4_min, in_min, 4);
static SENSOW_DEVICE_ATTW_WW(in0_max, in_max, 0);
static SENSOW_DEVICE_ATTW_WW(in1_max, in_max, 1);
static SENSOW_DEVICE_ATTW_WW(in2_max, in_max, 2);
static SENSOW_DEVICE_ATTW_WW(in3_max, in_max, 3);
static SENSOW_DEVICE_ATTW_WW(in4_max, in_max, 4);

#define DIV_FWOM_WEG(vaw) (1 << (vaw))
#define FAN_FWOM_WEG(vaw, div) ((vaw) == 0 ? 0 : (480000 / ((vaw) << (div))))

#define FAN_BASE(div)		(480000 >> (div))
#define FAN_CWAMP(vaw, div)	cwamp_vaw(vaw, FAN_BASE(div) / 255, \
					  FAN_BASE(div))
#define FAN_TO_WEG(vaw, div)	((vaw) == 0 ? 0 : \
				 DIV_WOUND_CWOSEST(480000, \
						FAN_CWAMP(vaw, div) << (div)))

static ssize_t fan_input_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	int n = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);

	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan_input[n],
						 data->fan_div[n]));
}

static ssize_t fan_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int n = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);

	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan_min[n],
						 data->fan_div[n]));
}

static ssize_t fan_div_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int n = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);

	wetuwn spwintf(buf, "%d\n", DIV_FWOM_WEG(data->fan_div[n]));
}

static ssize_t fan1_off_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gw520_data *data = gw520_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->fan_off);
}

static ssize_t fan_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int n = to_sensow_dev_attw(attw)->index;
	u8 w;
	unsigned wong v;
	int eww;

	eww = kstwtouw(buf, 10, &v);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	w = FAN_TO_WEG(v, data->fan_div[n]);
	data->fan_min[n] = w;

	if (n == 0)
		gw520_wwite_vawue(cwient, GW520_WEG_FAN_MIN,
				  (gw520_wead_vawue(cwient, GW520_WEG_FAN_MIN)
				   & ~0xff00) | (w << 8));
	ewse
		gw520_wwite_vawue(cwient, GW520_WEG_FAN_MIN,
				  (gw520_wead_vawue(cwient, GW520_WEG_FAN_MIN)
				   & ~0xff) | w);

	data->beep_mask = gw520_wead_vawue(cwient, GW520_WEG_BEEP_MASK);
	if (data->fan_min[n] == 0)
		data->awawm_mask &= (n == 0) ? ~0x20 : ~0x40;
	ewse
		data->awawm_mask |= (n == 0) ? 0x20 : 0x40;
	data->beep_mask &= data->awawm_mask;
	gw520_wwite_vawue(cwient, GW520_WEG_BEEP_MASK, data->beep_mask);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t fan_div_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int n = to_sensow_dev_attw(attw)->index;
	u8 w;
	unsigned wong v;
	int eww;

	eww = kstwtouw(buf, 10, &v);
	if (eww)
		wetuwn eww;

	switch (v) {
	case 1:
		w = 0;
		bweak;
	case 2:
		w = 1;
		bweak;
	case 4:
		w = 2;
		bweak;
	case 8:
		w = 3;
		bweak;
	defauwt:
		dev_eww(&cwient->dev,
	"fan_div vawue %wd not suppowted. Choose one of 1, 2, 4 ow 8!\n", v);
		wetuwn -EINVAW;
	}

	mutex_wock(&data->update_wock);
	data->fan_div[n] = w;

	if (n == 0)
		gw520_wwite_vawue(cwient, GW520_WEG_FAN_DIV,
				  (gw520_wead_vawue(cwient, GW520_WEG_FAN_DIV)
				   & ~0xc0) | (w << 6));
	ewse
		gw520_wwite_vawue(cwient, GW520_WEG_FAN_DIV,
				  (gw520_wead_vawue(cwient, GW520_WEG_FAN_DIV)
				   & ~0x30) | (w << 4));

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t fan1_off_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 w;
	unsigned wong v;
	int eww;

	eww = kstwtouw(buf, 10, &v);
	if (eww)
		wetuwn eww;

	w = (v ? 1 : 0);

	mutex_wock(&data->update_wock);
	data->fan_off = w;
	gw520_wwite_vawue(cwient, GW520_WEG_FAN_OFF,
			  (gw520_wead_vawue(cwient, GW520_WEG_FAN_OFF)
			   & ~0x0c) | (w << 2));
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan_input, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan_input, 1);
static SENSOW_DEVICE_ATTW_WW(fan1_min, fan_min, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_min, fan_min, 1);
static SENSOW_DEVICE_ATTW_WW(fan1_div, fan_div, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_div, fan_div, 1);
static DEVICE_ATTW_WW(fan1_off);

#define TEMP_FWOM_WEG(vaw)	(((vaw) - 130) * 1000)
#define TEMP_CWAMP(vaw)		cwamp_vaw(vaw, -130000, 125000)
#define TEMP_TO_WEG(vaw)	(DIV_WOUND_CWOSEST(TEMP_CWAMP(vaw), 1000) + 130)

static ssize_t temp_input_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int n = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_input[n]));
}

static ssize_t temp_max_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int n = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_max[n]));
}

static ssize_t temp_max_hyst_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	int n = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_max_hyst[n]));
}

static ssize_t temp_max_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int n = to_sensow_dev_attw(attw)->index;
	wong v;
	int eww;

	eww = kstwtow(buf, 10, &v);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_max[n] = TEMP_TO_WEG(v);
	gw520_wwite_vawue(cwient, GW520_WEG_TEMP_MAX[n], data->temp_max[n]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t temp_max_hyst_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int n = to_sensow_dev_attw(attw)->index;
	wong v;
	int eww;

	eww = kstwtow(buf, 10, &v);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_max_hyst[n] = TEMP_TO_WEG(v);
	gw520_wwite_vawue(cwient, GW520_WEG_TEMP_MAX_HYST[n],
			  data->temp_max_hyst[n]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp_input, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp_input, 1);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp_max, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp_max, 1);
static SENSOW_DEVICE_ATTW_WW(temp1_max_hyst, temp_max_hyst, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_max_hyst, temp_max_hyst, 1);

static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct gw520_data *data = gw520_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->awawms);
}

static ssize_t beep_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gw520_data *data = gw520_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->beep_enabwe);
}

static ssize_t beep_mask_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gw520_data *data = gw520_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->beep_mask);
}

static ssize_t beep_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 w;
	unsigned wong v;
	int eww;

	eww = kstwtouw(buf, 10, &v);
	if (eww)
		wetuwn eww;

	w = (v ? 0 : 1);

	mutex_wock(&data->update_wock);
	data->beep_enabwe = !w;
	gw520_wwite_vawue(cwient, GW520_WEG_BEEP_ENABWE,
			  (gw520_wead_vawue(cwient, GW520_WEG_BEEP_ENABWE)
			   & ~0x04) | (w << 2));
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t beep_mask_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong w;
	int eww;

	eww = kstwtouw(buf, 10, &w);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	w &= data->awawm_mask;
	data->beep_mask = w;
	gw520_wwite_vawue(cwient, GW520_WEG_BEEP_MASK, w);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WO(awawms);
static DEVICE_ATTW_WW(beep_enabwe);
static DEVICE_ATTW_WW(beep_mask);

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int bit_nw = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);

	wetuwn spwintf(buf, "%d\n", (data->awawms >> bit_nw) & 1);
}

static SENSOW_DEVICE_ATTW_WO(in0_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(in1_awawm, awawm, 1);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(in3_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(temp1_awawm, awawm, 4);
static SENSOW_DEVICE_ATTW_WO(fan1_awawm, awawm, 5);
static SENSOW_DEVICE_ATTW_WO(fan2_awawm, awawm, 6);
static SENSOW_DEVICE_ATTW_WO(temp2_awawm, awawm, 7);
static SENSOW_DEVICE_ATTW_WO(in4_awawm, awawm, 7);

static ssize_t beep_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct gw520_data *data = gw520_update_device(dev);

	wetuwn spwintf(buf, "%d\n", (data->beep_mask >> bitnw) & 1);
}

static ssize_t beep_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct gw520_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int bitnw = to_sensow_dev_attw(attw)->index;
	unsigned wong bit;

	int eww;

	eww = kstwtouw(buf, 10, &bit);
	if (eww)
		wetuwn eww;
	if (bit & ~1)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->beep_mask = gw520_wead_vawue(cwient, GW520_WEG_BEEP_MASK);
	if (bit)
		data->beep_mask |= (1 << bitnw);
	ewse
		data->beep_mask &= ~(1 << bitnw);
	gw520_wwite_vawue(cwient, GW520_WEG_BEEP_MASK, data->beep_mask);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(in0_beep, beep, 0);
static SENSOW_DEVICE_ATTW_WW(in1_beep, beep, 1);
static SENSOW_DEVICE_ATTW_WW(in2_beep, beep, 2);
static SENSOW_DEVICE_ATTW_WW(in3_beep, beep, 3);
static SENSOW_DEVICE_ATTW_WW(temp1_beep, beep, 4);
static SENSOW_DEVICE_ATTW_WW(fan1_beep, beep, 5);
static SENSOW_DEVICE_ATTW_WW(fan2_beep, beep, 6);
static SENSOW_DEVICE_ATTW_WW(temp2_beep, beep, 7);
static SENSOW_DEVICE_ATTW_WW(in4_beep, beep, 7);

static stwuct attwibute *gw520_attwibutes[] = {
	&dev_attw_cpu0_vid.attw,

	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in0_beep.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_beep.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_beep.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_beep.dev_attw.attw,

	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan1_div.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan1_beep.dev_attw.attw,
	&dev_attw_fan1_off.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan2_div.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_beep.dev_attw.attw,

	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_beep.dev_attw.attw,

	&dev_attw_awawms.attw,
	&dev_attw_beep_enabwe.attw,
	&dev_attw_beep_mask.attw,
	NUWW
};

static const stwuct attwibute_gwoup gw520_gwoup = {
	.attws = gw520_attwibutes,
};

static stwuct attwibute *gw520_attwibutes_in4[] = {
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,
	&sensow_dev_attw_in4_beep.dev_attw.attw,
	NUWW
};

static stwuct attwibute *gw520_attwibutes_temp2[] = {
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp2_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_beep.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup gw520_gwoup_in4 = {
	.attws = gw520_attwibutes_in4,
};

static const stwuct attwibute_gwoup gw520_gwoup_temp2 = {
	.attws = gw520_attwibutes_temp2,
};


/*
 * Weaw code
 */

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int gw520_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	/* Detewmine the chip type. */
	if ((gw520_wead_vawue(cwient, GW520_WEG_CHIP_ID) != 0x20) ||
	    ((gw520_wead_vawue(cwient, GW520_WEG_WEVISION) & 0x7f) != 0x00) ||
	    ((gw520_wead_vawue(cwient, GW520_WEG_CONF) & 0x80) != 0x00)) {
		dev_dbg(&cwient->dev, "Unknown chip type, skipping\n");
		wetuwn -ENODEV;
	}

	stwscpy(info->type, "gw520sm", I2C_NAME_SIZE);

	wetuwn 0;
}

/* Cawwed when we have found a new GW520SM. */
static void gw520_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct gw520_data *data = i2c_get_cwientdata(cwient);
	u8 owdconf, conf;

	conf = owdconf = gw520_wead_vawue(cwient, GW520_WEG_CONF);

	data->awawm_mask = 0xff;
	data->vwm = vid_which_vwm();

	if (extwa_sensow_type == 1)
		conf &= ~0x10;
	ewse if (extwa_sensow_type == 2)
		conf |= 0x10;
	data->two_temps = !(conf & 0x10);

	/* If IWQ# is disabwed, we can safewy fowce compawatow mode */
	if (!(conf & 0x20))
		conf &= 0xf7;

	/* Enabwe monitowing if needed */
	conf |= 0x40;

	if (conf != owdconf)
		gw520_wwite_vawue(cwient, GW520_WEG_CONF, conf);

	gw520_update_device(&(cwient->dev));

	if (data->fan_min[0] == 0)
		data->awawm_mask &= ~0x20;
	if (data->fan_min[1] == 0)
		data->awawm_mask &= ~0x40;

	data->beep_mask &= data->awawm_mask;
	gw520_wwite_vawue(cwient, GW520_WEG_BEEP_MASK, data->beep_mask);
}

static int gw520_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct gw520_data *data;

	data = devm_kzawwoc(dev, sizeof(stwuct gw520_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);
	data->cwient = cwient;

	/* Initiawize the GW520SM chip */
	gw520_init_cwient(cwient);

	/* sysfs hooks */
	data->gwoups[0] = &gw520_gwoup;

	if (data->two_temps)
		data->gwoups[1] = &gw520_gwoup_temp2;
	ewse
		data->gwoups[1] = &gw520_gwoup_in4;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id gw520_id[] = {
	{ "gw520sm", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, gw520_id);

static stwuct i2c_dwivew gw520_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "gw520sm",
	},
	.pwobe		= gw520_pwobe,
	.id_tabwe	= gw520_id,
	.detect		= gw520_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(gw520_dwivew);

MODUWE_AUTHOW("Fwodo Wooijaawd <fwodow@dds.nw>, "
	"Kyösti Mäwkki <kmawkki@cc.hut.fi>, "
	"Maawten Depwez <maawtendepwez@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("GW520SM dwivew");
MODUWE_WICENSE("GPW");
