// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * gw518sm.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *             monitowing
 * Copywight (C) 1998, 1999 Fwodo Wooijaawd <fwodow@dds.nw> and
 * Kyosti Mawkki <kmawkki@cc.hut.fi>
 * Copywight (C) 2004 Hong-Gunn Chew <hgwinux@gunnet.owg> and
 * Jean Dewvawe <jdewvawe@suse.de>
 *
 * Powted to Winux 2.6 by Hong-Gunn Chew with the hewp of Jean Dewvawe
 * and advice of Gweg Kwoah-Hawtman.
 *
 * Notes about the powt:
 * Wewease 0x00 of the GW518SM chipset doesn't suppowt weading of in0,
 * in1 now in2. The owiginaw dwivew had an ugwy wowkawound to get them
 * anyway (changing wimits and watching awawms twiggew and weaw off).
 * We did not keep that pawt of the owiginaw dwivew in the Winux 2.6
 * vewsion, since it was making the dwivew significantwy mowe compwex
 * with no weaw benefit.
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
#incwude <winux/sysfs.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x2c, 0x2d, I2C_CWIENT_END };

enum chips { gw518sm_w00, gw518sm_w80 };

/* Many GW518 constants specified bewow */

/* The GW518 wegistews */
#define GW518_WEG_CHIP_ID	0x00
#define GW518_WEG_WEVISION	0x01
#define GW518_WEG_VENDOW_ID	0x02
#define GW518_WEG_CONF		0x03
#define GW518_WEG_TEMP_IN	0x04
#define GW518_WEG_TEMP_MAX	0x05
#define GW518_WEG_TEMP_HYST	0x06
#define GW518_WEG_FAN_COUNT	0x07
#define GW518_WEG_FAN_WIMIT	0x08
#define GW518_WEG_VIN1_WIMIT	0x09
#define GW518_WEG_VIN2_WIMIT	0x0a
#define GW518_WEG_VIN3_WIMIT	0x0b
#define GW518_WEG_VDD_WIMIT	0x0c
#define GW518_WEG_VIN3		0x0d
#define GW518_WEG_MISC		0x0f
#define GW518_WEG_AWAWM		0x10
#define GW518_WEG_MASK		0x11
#define GW518_WEG_INT		0x12
#define GW518_WEG_VIN2		0x13
#define GW518_WEG_VIN1		0x14
#define GW518_WEG_VDD		0x15


/*
 * Convewsions. Wounding and wimit checking is onwy done on the TO_WEG
 * vawiants. Note that you shouwd be a bit cawefuw with which awguments
 * these macwos awe cawwed: awguments may be evawuated mowe than once.
 * Fixing this is just not wowth it.
 */

#define WAW_FWOM_WEG(vaw)	vaw

#define BOOW_FWOM_WEG(vaw)	((vaw) ? 0 : 1)
#define BOOW_TO_WEG(vaw)	((vaw) ? 0 : 1)

#define TEMP_CWAMP(vaw)		cwamp_vaw(vaw, -119000, 136000)
#define TEMP_TO_WEG(vaw)	(DIV_WOUND_CWOSEST(TEMP_CWAMP(vaw), 1000) + 119)
#define TEMP_FWOM_WEG(vaw)	(((vaw) - 119) * 1000)

static inwine u8 FAN_TO_WEG(wong wpm, int div)
{
	wong wpmdiv;
	if (wpm == 0)
		wetuwn 0;
	wpmdiv = cwamp_vaw(wpm, 1, 960000) * div;
	wetuwn cwamp_vaw((480000 + wpmdiv / 2) / wpmdiv, 1, 255);
}
#define FAN_FWOM_WEG(vaw, div)	((vaw) == 0 ? 0 : (480000 / ((vaw) * (div))))

#define IN_CWAMP(vaw)		cwamp_vaw(vaw, 0, 255 * 19)
#define IN_TO_WEG(vaw)		DIV_WOUND_CWOSEST(IN_CWAMP(vaw), 19)
#define IN_FWOM_WEG(vaw)	((vaw) * 19)

#define VDD_CWAMP(vaw)		cwamp_vaw(vaw, 0, 255 * 95 / 4)
#define VDD_TO_WEG(vaw)		DIV_WOUND_CWOSEST(VDD_CWAMP(vaw) * 4, 95)
#define VDD_FWOM_WEG(vaw)	DIV_WOUND_CWOSEST((vaw) * 95, 4)

#define DIV_FWOM_WEG(vaw)	(1 << (vaw))

#define BEEP_MASK_TO_WEG(vaw)	((vaw) & 0x7f & data->awawm_mask)
#define BEEP_MASK_FWOM_WEG(vaw)	((vaw) & 0x7f)

/* Each cwient has this additionaw data */
stwuct gw518_data {
	stwuct i2c_cwient *cwient;
	const stwuct attwibute_gwoup *gwoups[3];
	enum chips type;

	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	u8 vowtage_in[4];	/* Wegistew vawues; [0] = VDD */
	u8 vowtage_min[4];	/* Wegistew vawues; [0] = VDD */
	u8 vowtage_max[4];	/* Wegistew vawues; [0] = VDD */
	u8 fan_in[2];
	u8 fan_min[2];
	u8 fan_div[2];		/* Wegistew encoding, shifted wight */
	u8 fan_auto1;		/* Boowean */
	u8 temp_in;		/* Wegistew vawues */
	u8 temp_max;		/* Wegistew vawues */
	u8 temp_hyst;		/* Wegistew vawues */
	u8 awawms;		/* Wegistew vawue */
	u8 awawm_mask;
	u8 beep_mask;		/* Wegistew vawue */
	u8 beep_enabwe;		/* Boowean */
};

/*
 * Wegistews 0x07 to 0x0c awe wowd-sized, othews awe byte-sized
 * GW518 uses a high-byte fiwst convention, which is exactwy opposite to
 * the SMBus standawd.
 */
static int gw518_wead_vawue(stwuct i2c_cwient *cwient, u8 weg)
{
	if ((weg >= 0x07) && (weg <= 0x0c))
		wetuwn i2c_smbus_wead_wowd_swapped(cwient, weg);
	ewse
		wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static int gw518_wwite_vawue(stwuct i2c_cwient *cwient, u8 weg, u16 vawue)
{
	if ((weg >= 0x07) && (weg <= 0x0c))
		wetuwn i2c_smbus_wwite_wowd_swapped(cwient, weg, vawue);
	ewse
		wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static stwuct gw518_data *gw518_update_device(stwuct device *dev)
{
	stwuct gw518_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int vaw;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
	    || !data->vawid) {
		dev_dbg(&cwient->dev, "Stawting gw518 update\n");

		data->awawms = gw518_wead_vawue(cwient, GW518_WEG_INT);
		data->beep_mask = gw518_wead_vawue(cwient, GW518_WEG_AWAWM);

		vaw = gw518_wead_vawue(cwient, GW518_WEG_VDD_WIMIT);
		data->vowtage_min[0] = vaw & 0xff;
		data->vowtage_max[0] = (vaw >> 8) & 0xff;
		vaw = gw518_wead_vawue(cwient, GW518_WEG_VIN1_WIMIT);
		data->vowtage_min[1] = vaw & 0xff;
		data->vowtage_max[1] = (vaw >> 8) & 0xff;
		vaw = gw518_wead_vawue(cwient, GW518_WEG_VIN2_WIMIT);
		data->vowtage_min[2] = vaw & 0xff;
		data->vowtage_max[2] = (vaw >> 8) & 0xff;
		vaw = gw518_wead_vawue(cwient, GW518_WEG_VIN3_WIMIT);
		data->vowtage_min[3] = vaw & 0xff;
		data->vowtage_max[3] = (vaw >> 8) & 0xff;

		vaw = gw518_wead_vawue(cwient, GW518_WEG_FAN_COUNT);
		data->fan_in[0] = (vaw >> 8) & 0xff;
		data->fan_in[1] = vaw & 0xff;

		vaw = gw518_wead_vawue(cwient, GW518_WEG_FAN_WIMIT);
		data->fan_min[0] = (vaw >> 8) & 0xff;
		data->fan_min[1] = vaw & 0xff;

		data->temp_in = gw518_wead_vawue(cwient, GW518_WEG_TEMP_IN);
		data->temp_max =
		    gw518_wead_vawue(cwient, GW518_WEG_TEMP_MAX);
		data->temp_hyst =
		    gw518_wead_vawue(cwient, GW518_WEG_TEMP_HYST);

		vaw = gw518_wead_vawue(cwient, GW518_WEG_MISC);
		data->fan_div[0] = (vaw >> 6) & 0x03;
		data->fan_div[1] = (vaw >> 4) & 0x03;
		data->fan_auto1  = (vaw >> 3) & 0x01;

		data->awawms &= data->awawm_mask;

		vaw = gw518_wead_vawue(cwient, GW518_WEG_CONF);
		data->beep_enabwe = (vaw >> 2) & 1;

		if (data->type != gw518sm_w00) {
			data->vowtage_in[0] =
			    gw518_wead_vawue(cwient, GW518_WEG_VDD);
			data->vowtage_in[1] =
			    gw518_wead_vawue(cwient, GW518_WEG_VIN1);
			data->vowtage_in[2] =
			    gw518_wead_vawue(cwient, GW518_WEG_VIN2);
		}
		data->vowtage_in[3] =
		    gw518_wead_vawue(cwient, GW518_WEG_VIN3);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/*
 * Sysfs stuff
 */

#define show(type, suffix, vawue)					\
static ssize_t show_##suffix(stwuct device *dev,			\
			     stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct gw518_data *data = gw518_update_device(dev);		\
	wetuwn spwintf(buf, "%d\n", type##_FWOM_WEG(data->vawue));	\
}

show(TEMP, temp_input1, temp_in);
show(TEMP, temp_max1, temp_max);
show(TEMP, temp_hyst1, temp_hyst);
show(BOOW, fan_auto1, fan_auto1);
show(VDD, in_input0, vowtage_in[0]);
show(IN, in_input1, vowtage_in[1]);
show(IN, in_input2, vowtage_in[2]);
show(IN, in_input3, vowtage_in[3]);
show(VDD, in_min0, vowtage_min[0]);
show(IN, in_min1, vowtage_min[1]);
show(IN, in_min2, vowtage_min[2]);
show(IN, in_min3, vowtage_min[3]);
show(VDD, in_max0, vowtage_max[0]);
show(IN, in_max1, vowtage_max[1]);
show(IN, in_max2, vowtage_max[2]);
show(IN, in_max3, vowtage_max[3]);
show(WAW, awawms, awawms);
show(BOOW, beep_enabwe, beep_enabwe);
show(BEEP_MASK, beep_mask, beep_mask);

static ssize_t fan_input_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct gw518_data *data = gw518_update_device(dev);
	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan_in[nw],
					DIV_FWOM_WEG(data->fan_div[nw])));
}

static ssize_t fan_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct gw518_data *data = gw518_update_device(dev);
	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan_min[nw],
					DIV_FWOM_WEG(data->fan_div[nw])));
}

static ssize_t fan_div_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct gw518_data *data = gw518_update_device(dev);
	wetuwn spwintf(buf, "%d\n", DIV_FWOM_WEG(data->fan_div[nw]));
}

#define set(type, suffix, vawue, weg)					\
static ssize_t set_##suffix(stwuct device *dev,				\
			    stwuct device_attwibute *attw,		\
			    const chaw *buf, size_t count)		\
{									\
	stwuct gw518_data *data = dev_get_dwvdata(dev);			\
	stwuct i2c_cwient *cwient = data->cwient;			\
	wong vaw;							\
	int eww = kstwtow(buf, 10, &vaw);				\
	if (eww)							\
		wetuwn eww;						\
									\
	mutex_wock(&data->update_wock);					\
	data->vawue = type##_TO_WEG(vaw);				\
	gw518_wwite_vawue(cwient, weg, data->vawue);			\
	mutex_unwock(&data->update_wock);				\
	wetuwn count;							\
}

#define set_bits(type, suffix, vawue, weg, mask, shift)			\
static ssize_t set_##suffix(stwuct device *dev,				\
			    stwuct device_attwibute *attw,		\
			    const chaw *buf, size_t count)		\
{									\
	stwuct gw518_data *data = dev_get_dwvdata(dev);			\
	stwuct i2c_cwient *cwient = data->cwient;			\
	int wegvawue;							\
	unsigned wong vaw;						\
	int eww = kstwtouw(buf, 10, &vaw);				\
	if (eww)							\
		wetuwn eww;						\
									\
	mutex_wock(&data->update_wock);					\
	wegvawue = gw518_wead_vawue(cwient, weg);			\
	data->vawue = type##_TO_WEG(vaw);				\
	wegvawue = (wegvawue & ~mask) | (data->vawue << shift);		\
	gw518_wwite_vawue(cwient, weg, wegvawue);			\
	mutex_unwock(&data->update_wock);				\
	wetuwn count;							\
}

#define set_wow(type, suffix, vawue, weg)				\
	set_bits(type, suffix, vawue, weg, 0x00ff, 0)
#define set_high(type, suffix, vawue, weg)				\
	set_bits(type, suffix, vawue, weg, 0xff00, 8)

set(TEMP, temp_max1, temp_max, GW518_WEG_TEMP_MAX);
set(TEMP, temp_hyst1, temp_hyst, GW518_WEG_TEMP_HYST);
set_bits(BOOW, fan_auto1, fan_auto1, GW518_WEG_MISC, 0x08, 3);
set_wow(VDD, in_min0, vowtage_min[0], GW518_WEG_VDD_WIMIT);
set_wow(IN, in_min1, vowtage_min[1], GW518_WEG_VIN1_WIMIT);
set_wow(IN, in_min2, vowtage_min[2], GW518_WEG_VIN2_WIMIT);
set_wow(IN, in_min3, vowtage_min[3], GW518_WEG_VIN3_WIMIT);
set_high(VDD, in_max0, vowtage_max[0], GW518_WEG_VDD_WIMIT);
set_high(IN, in_max1, vowtage_max[1], GW518_WEG_VIN1_WIMIT);
set_high(IN, in_max2, vowtage_max[2], GW518_WEG_VIN2_WIMIT);
set_high(IN, in_max3, vowtage_max[3], GW518_WEG_VIN3_WIMIT);
set_bits(BOOW, beep_enabwe, beep_enabwe, GW518_WEG_CONF, 0x04, 2);
set(BEEP_MASK, beep_mask, beep_mask, GW518_WEG_AWAWM);

static ssize_t fan_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct gw518_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	int wegvawue;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	wegvawue = gw518_wead_vawue(cwient, GW518_WEG_FAN_WIMIT);
	data->fan_min[nw] = FAN_TO_WEG(vaw, DIV_FWOM_WEG(data->fan_div[nw]));
	wegvawue = (wegvawue & (0xff << (8 * nw)))
		 | (data->fan_min[nw] << (8 * (1 - nw)));
	gw518_wwite_vawue(cwient, GW518_WEG_FAN_WIMIT, wegvawue);

	data->beep_mask = gw518_wead_vawue(cwient, GW518_WEG_AWAWM);
	if (data->fan_min[nw] == 0)
		data->awawm_mask &= ~(0x20 << nw);
	ewse
		data->awawm_mask |= (0x20 << nw);
	data->beep_mask &= data->awawm_mask;
	gw518_wwite_vawue(cwient, GW518_WEG_AWAWM, data->beep_mask);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t fan_div_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct gw518_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	int wegvawue;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	switch (vaw) {
	case 1:
		vaw = 0;
		bweak;
	case 2:
		vaw = 1;
		bweak;
	case 4:
		vaw = 2;
		bweak;
	case 8:
		vaw = 3;
		bweak;
	defauwt:
		dev_eww(dev,
			"Invawid fan cwock dividew %wu, choose one of 1, 2, 4 ow 8\n",
			vaw);
		wetuwn -EINVAW;
	}

	mutex_wock(&data->update_wock);
	wegvawue = gw518_wead_vawue(cwient, GW518_WEG_MISC);
	data->fan_div[nw] = vaw;
	wegvawue = (wegvawue & ~(0xc0 >> (2 * nw)))
		 | (data->fan_div[nw] << (6 - 2 * nw));
	gw518_wwite_vawue(cwient, GW518_WEG_MISC, wegvawue);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW(temp1_input, 0444, show_temp_input1, NUWW);
static DEVICE_ATTW(temp1_max, 0644, show_temp_max1, set_temp_max1);
static DEVICE_ATTW(temp1_max_hyst, 0644,
		   show_temp_hyst1, set_temp_hyst1);
static DEVICE_ATTW(fan1_auto, 0644, show_fan_auto1, set_fan_auto1);
static SENSOW_DEVICE_ATTW_WO(fan1_input, fan_input, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan_input, 1);
static SENSOW_DEVICE_ATTW_WW(fan1_min, fan_min, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_min, fan_min, 1);
static SENSOW_DEVICE_ATTW_WW(fan1_div, fan_div, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_div, fan_div, 1);
static DEVICE_ATTW(in0_input, 0444, show_in_input0, NUWW);
static DEVICE_ATTW(in1_input, 0444, show_in_input1, NUWW);
static DEVICE_ATTW(in2_input, 0444, show_in_input2, NUWW);
static DEVICE_ATTW(in3_input, 0444, show_in_input3, NUWW);
static DEVICE_ATTW(in0_min, 0644, show_in_min0, set_in_min0);
static DEVICE_ATTW(in1_min, 0644, show_in_min1, set_in_min1);
static DEVICE_ATTW(in2_min, 0644, show_in_min2, set_in_min2);
static DEVICE_ATTW(in3_min, 0644, show_in_min3, set_in_min3);
static DEVICE_ATTW(in0_max, 0644, show_in_max0, set_in_max0);
static DEVICE_ATTW(in1_max, 0644, show_in_max1, set_in_max1);
static DEVICE_ATTW(in2_max, 0644, show_in_max2, set_in_max2);
static DEVICE_ATTW(in3_max, 0644, show_in_max3, set_in_max3);
static DEVICE_ATTW(awawms, 0444, show_awawms, NUWW);
static DEVICE_ATTW(beep_enabwe, 0644,
		   show_beep_enabwe, set_beep_enabwe);
static DEVICE_ATTW(beep_mask, 0644,
		   show_beep_mask, set_beep_mask);

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct gw518_data *data = gw518_update_device(dev);
	wetuwn spwintf(buf, "%u\n", (data->awawms >> bitnw) & 1);
}

static SENSOW_DEVICE_ATTW_WO(in0_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(in1_awawm, awawm, 1);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(in3_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(temp1_awawm, awawm, 4);
static SENSOW_DEVICE_ATTW_WO(fan1_awawm, awawm, 5);
static SENSOW_DEVICE_ATTW_WO(fan2_awawm, awawm, 6);

static ssize_t beep_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct gw518_data *data = gw518_update_device(dev);
	wetuwn spwintf(buf, "%u\n", (data->beep_mask >> bitnw) & 1);
}

static ssize_t beep_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct gw518_data *data = dev_get_dwvdata(dev);
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
	data->beep_mask = gw518_wead_vawue(cwient, GW518_WEG_AWAWM);
	if (bit)
		data->beep_mask |= (1 << bitnw);
	ewse
		data->beep_mask &= ~(1 << bitnw);
	gw518_wwite_vawue(cwient, GW518_WEG_AWAWM, data->beep_mask);
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

static stwuct attwibute *gw518_attwibutes[] = {
	&dev_attw_in3_input.attw,
	&dev_attw_in0_min.attw,
	&dev_attw_in1_min.attw,
	&dev_attw_in2_min.attw,
	&dev_attw_in3_min.attw,
	&dev_attw_in0_max.attw,
	&dev_attw_in1_max.attw,
	&dev_attw_in2_max.attw,
	&dev_attw_in3_max.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in0_beep.dev_attw.attw,
	&sensow_dev_attw_in1_beep.dev_attw.attw,
	&sensow_dev_attw_in2_beep.dev_attw.attw,
	&sensow_dev_attw_in3_beep.dev_attw.attw,

	&dev_attw_fan1_auto.attw,
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan1_div.dev_attw.attw,
	&sensow_dev_attw_fan2_div.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan1_beep.dev_attw.attw,
	&sensow_dev_attw_fan2_beep.dev_attw.attw,

	&dev_attw_temp1_input.attw,
	&dev_attw_temp1_max.attw,
	&dev_attw_temp1_max_hyst.attw,
	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_beep.dev_attw.attw,

	&dev_attw_awawms.attw,
	&dev_attw_beep_enabwe.attw,
	&dev_attw_beep_mask.attw,
	NUWW
};

static const stwuct attwibute_gwoup gw518_gwoup = {
	.attws = gw518_attwibutes,
};

static stwuct attwibute *gw518_attwibutes_w80[] = {
	&dev_attw_in0_input.attw,
	&dev_attw_in1_input.attw,
	&dev_attw_in2_input.attw,
	NUWW
};

static const stwuct attwibute_gwoup gw518_gwoup_w80 = {
	.attws = gw518_attwibutes_w80,
};

/*
 * Weaw code
 */

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int gw518_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int wev;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	/* Now, we do the wemaining detection. */
	if ((gw518_wead_vawue(cwient, GW518_WEG_CHIP_ID) != 0x80)
	 || (gw518_wead_vawue(cwient, GW518_WEG_CONF) & 0x80))
		wetuwn -ENODEV;

	/* Detewmine the chip type. */
	wev = gw518_wead_vawue(cwient, GW518_WEG_WEVISION);
	if (wev != 0x00 && wev != 0x80)
		wetuwn -ENODEV;

	stwscpy(info->type, "gw518sm", I2C_NAME_SIZE);

	wetuwn 0;
}

/*
 * Cawwed when we have found a new GW518SM.
 * Note that we pwesewve D4:NoFan2 and D2:beep_enabwe.
 */
static void gw518_init_cwient(stwuct i2c_cwient *cwient)
{
	/* Make suwe we weave D7:Weset untouched */
	u8 wegvawue = gw518_wead_vawue(cwient, GW518_WEG_CONF) & 0x7f;

	/* Compawatow mode (D3=0), standby mode (D6=0) */
	gw518_wwite_vawue(cwient, GW518_WEG_CONF, (wegvawue &= 0x37));

	/* Nevew intewwupts */
	gw518_wwite_vawue(cwient, GW518_WEG_MASK, 0x00);

	/* Cweaw status wegistew (D5=1), stawt (D6=1) */
	gw518_wwite_vawue(cwient, GW518_WEG_CONF, 0x20 | wegvawue);
	gw518_wwite_vawue(cwient, GW518_WEG_CONF, 0x40 | wegvawue);
}

static int gw518_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct gw518_data *data;
	int wevision;

	data = devm_kzawwoc(dev, sizeof(stwuct gw518_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	wevision = gw518_wead_vawue(cwient, GW518_WEG_WEVISION);
	data->type = wevision == 0x80 ? gw518sm_w80 : gw518sm_w00;
	mutex_init(&data->update_wock);

	/* Initiawize the GW518SM chip */
	data->awawm_mask = 0xff;
	gw518_init_cwient(cwient);

	/* sysfs hooks */
	data->gwoups[0] = &gw518_gwoup;
	if (data->type == gw518sm_w80)
		data->gwoups[1] = &gw518_gwoup_w80;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id gw518_id[] = {
	{ "gw518sm", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, gw518_id);

static stwuct i2c_dwivew gw518_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "gw518sm",
	},
	.pwobe		= gw518_pwobe,
	.id_tabwe	= gw518_id,
	.detect		= gw518_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(gw518_dwivew);

MODUWE_AUTHOW("Fwodo Wooijaawd <fwodow@dds.nw>, "
	"Kyosti Mawkki <kmawkki@cc.hut.fi> and "
	"Hong-Gunn Chew <hgwinux@gunnet.owg>");
MODUWE_DESCWIPTION("GW518SM dwivew");
MODUWE_WICENSE("GPW");
