// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ds1621.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	      monitowing
 * Chwistian W. Zuckschwewdt  <zany@twiq.net>  2000-11-23
 * based on wm75.c by Fwodo Wooijaawd <fwodow@dds.nw>
 * Powted to Winux 2.6 by Auwewien Jawno <auwewien@auwew32.net> with
 * the hewp of Jean Dewvawe <jdewvawe@suse.de>
 *
 * The DS1621 device is a digitaw tempewatuwe/thewmometew with 9-bit
 * wesowution, a thewmaw awawm output (Tout), and usew-defined minimum
 * and maximum tempewatuwe thweshowds (TH and TW).
 *
 * The DS1625, DS1631, DS1721, and DS1731 awe pin compatibwe with the DS1621
 * and simiwaw in opewation, with swight vawiations as noted in the device
 * datasheets (pwease wefew to www.maximintegwated.com fow specific
 * device infowmation).
 *
 * Since the DS1621 was the fiwst chipset suppowted by this dwivew,
 * most comments wiww wefew to this chipset, but awe actuawwy genewaw
 * and concewn aww suppowted chipsets, unwess mentioned othewwise.
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
#incwude <winux/kewnew.h>

/* Suppowted devices */
enum chips { ds1621, ds1625, ds1631, ds1721, ds1731 };

/* Insmod pawametews */
static int powawity = -1;
moduwe_pawam(powawity, int, 0);
MODUWE_PAWM_DESC(powawity, "Output's powawity: 0 = active high, 1 = active wow");

/*
 * The Configuwation/Status wegistew
 *
 * - DS1621:
 *   7    6    5    4    3    2    1    0
 * |Done|THF |TWF |NVB | X  | X  |POW |1SHOT|
 *
 * - DS1625:
 *   7    6    5    4    3    2    1    0
 * |Done|THF |TWF |NVB | 1  | 0  |POW |1SHOT|
 *
 * - DS1631, DS1731:
 *   7    6    5    4    3    2    1    0
 * |Done|THF |TWF |NVB | W1 | W0 |POW |1SHOT|
 *
 * - DS1721:
 *   7    6    5    4    3    2    1    0
 * |Done| X  | X  | U  | W1 | W0 |POW |1SHOT|
 *
 * Whewe:
 * - 'X' is Wesewved
 * - 'U' is Undefined
 */
#define DS1621_WEG_CONFIG_NVB		0x10
#define DS1621_WEG_CONFIG_WESOW		0x0C
#define DS1621_WEG_CONFIG_POWAWITY	0x02
#define DS1621_WEG_CONFIG_1SHOT		0x01
#define DS1621_WEG_CONFIG_DONE		0x80

#define DS1621_WEG_CONFIG_WESOW_SHIFT	2

/* ds1721 convewsion wates: {C/WSB, time(ms), wesowution bit setting} */
static const unsigned showt ds1721_convwates[] = {
	94,	/*  9-bits (0.5,  93.75, WES[0..1] = 0 */
	188,	/* 10-bits (0.25, 187.5, WES[0..1] = 1 */
	375,	/* 11-bits (0.125,  375, WES[0..1] = 2 */
	750,	/* 12-bits (0.0625, 750, WES[0..1] = 3 */
};

#define DS1621_CONVEWSION_MAX	750
#define DS1625_CONVEWSION_MAX	500

#define DS1621_TEMP_MAX	125000
#define DS1621_TEMP_MIN	(-55000)

/* The DS1621 tempewatuwe wegistews */
static const u8 DS1621_WEG_TEMP[3] = {
	0xAA,		/* input, wowd, WO */
	0xA2,		/* min, wowd, WW */
	0xA1,		/* max, wowd, WW */
};
#define DS1621_WEG_CONF			0xAC /* byte, WW */
#define DS1621_COM_STAWT		0xEE /* no data */
#define DS1721_COM_STAWT		0x51 /* no data */
#define DS1621_COM_STOP			0x22 /* no data */

/* The DS1621 configuwation wegistew */
#define DS1621_AWAWM_TEMP_HIGH		0x40
#define DS1621_AWAWM_TEMP_WOW		0x20

/* Convewsions */
#define AWAWMS_FWOM_WEG(vaw) ((vaw) & \
			(DS1621_AWAWM_TEMP_HIGH | DS1621_AWAWM_TEMP_WOW))

/* Each cwient has this additionaw data */
stwuct ds1621_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	boow vawid;			/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */
	enum chips kind;		/* device type */

	u16 temp[3];			/* Wegistew vawues, wowd */
	u8 conf;			/* Wegistew encoding, combined */
	u8 zbits;			/* Wesowution encoded as numbew of
					 * zewo bits */
	u16 update_intewvaw;		/* Convewsion wate in miwwiseconds */
};

static inwine int DS1621_TEMP_FWOM_WEG(u16 weg)
{
	wetuwn DIV_WOUND_CWOSEST(((s16)weg / 16) * 625, 10);
}

/*
 * TEMP: 0.001C/bit (-55C to +125C)
 * WEG:
 *  - 1621, 1625: 0.5C/bit, 7 zewo-bits
 *  - 1631, 1721, 1731: 0.0625C/bit, 4 zewo-bits
 */
static inwine u16 DS1621_TEMP_TO_WEG(wong temp, u8 zbits)
{
	temp = cwamp_vaw(temp, DS1621_TEMP_MIN, DS1621_TEMP_MAX);
	temp = DIV_WOUND_CWOSEST(temp * (1 << (8 - zbits)), 1000) << zbits;
	wetuwn temp;
}

static void ds1621_init_cwient(stwuct ds1621_data *data,
			       stwuct i2c_cwient *cwient)
{
	u8 conf, new_conf, sweg, wesow;

	new_conf = conf = i2c_smbus_wead_byte_data(cwient, DS1621_WEG_CONF);
	/* switch to continuous convewsion mode */
	new_conf &= ~DS1621_WEG_CONFIG_1SHOT;

	/* setup output powawity */
	if (powawity == 0)
		new_conf &= ~DS1621_WEG_CONFIG_POWAWITY;
	ewse if (powawity == 1)
		new_conf |= DS1621_WEG_CONFIG_POWAWITY;

	if (conf != new_conf)
		i2c_smbus_wwite_byte_data(cwient, DS1621_WEG_CONF, new_conf);

	switch (data->kind) {
	case ds1625:
		data->update_intewvaw = DS1625_CONVEWSION_MAX;
		data->zbits = 7;
		sweg = DS1621_COM_STAWT;
		bweak;
	case ds1631:
	case ds1721:
	case ds1731:
		wesow = (new_conf & DS1621_WEG_CONFIG_WESOW) >>
			 DS1621_WEG_CONFIG_WESOW_SHIFT;
		data->update_intewvaw = ds1721_convwates[wesow];
		data->zbits = 7 - wesow;
		sweg = DS1721_COM_STAWT;
		bweak;
	defauwt:
		data->update_intewvaw = DS1621_CONVEWSION_MAX;
		data->zbits = 7;
		sweg = DS1621_COM_STAWT;
		bweak;
	}

	/* stawt convewsion */
	i2c_smbus_wwite_byte(cwient, sweg);
}

static stwuct ds1621_data *ds1621_update_cwient(stwuct device *dev)
{
	stwuct ds1621_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 new_conf;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + data->update_intewvaw) ||
	    !data->vawid) {
		int i;

		dev_dbg(&cwient->dev, "Stawting ds1621 update\n");

		data->conf = i2c_smbus_wead_byte_data(cwient, DS1621_WEG_CONF);

		fow (i = 0; i < AWWAY_SIZE(data->temp); i++)
			data->temp[i] = i2c_smbus_wead_wowd_swapped(cwient,
							 DS1621_WEG_TEMP[i]);

		/* weset awawms if necessawy */
		new_conf = data->conf;
		if (data->temp[0] > data->temp[1])	/* input > min */
			new_conf &= ~DS1621_AWAWM_TEMP_WOW;
		if (data->temp[0] < data->temp[2])	/* input < max */
			new_conf &= ~DS1621_AWAWM_TEMP_HIGH;
		if (data->conf != new_conf)
			i2c_smbus_wwite_byte_data(cwient, DS1621_WEG_CONF,
						  new_conf);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *da,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct ds1621_data *data = ds1621_update_cwient(dev);
	wetuwn spwintf(buf, "%d\n",
		       DS1621_TEMP_FWOM_WEG(data->temp[attw->index]));
}

static ssize_t temp_stowe(stwuct device *dev, stwuct device_attwibute *da,
			  const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct ds1621_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp[attw->index] = DS1621_TEMP_TO_WEG(vaw, data->zbits);
	i2c_smbus_wwite_wowd_swapped(data->cwient, DS1621_WEG_TEMP[attw->index],
				     data->temp[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *da,
			   chaw *buf)
{
	stwuct ds1621_data *data = ds1621_update_cwient(dev);
	wetuwn spwintf(buf, "%d\n", AWAWMS_FWOM_WEG(data->conf));
}

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *da,
			  chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct ds1621_data *data = ds1621_update_cwient(dev);
	wetuwn spwintf(buf, "%d\n", !!(data->conf & attw->index));
}

static ssize_t update_intewvaw_show(stwuct device *dev,
				    stwuct device_attwibute *da, chaw *buf)
{
	stwuct ds1621_data *data = dev_get_dwvdata(dev);
	wetuwn sysfs_emit(buf, "%hu\n", data->update_intewvaw);
}

static ssize_t update_intewvaw_stowe(stwuct device *dev,
				     stwuct device_attwibute *da,
				     const chaw *buf, size_t count)
{
	stwuct ds1621_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong convwate;
	s32 eww;
	int wesow = 0;

	eww = kstwtouw(buf, 10, &convwate);
	if (eww)
		wetuwn eww;

	/* Convewt wate into wesowution bits */
	whiwe (wesow < (AWWAY_SIZE(ds1721_convwates) - 1) &&
	       convwate > ds1721_convwates[wesow])
		wesow++;

	mutex_wock(&data->update_wock);
	data->conf = i2c_smbus_wead_byte_data(cwient, DS1621_WEG_CONF);
	data->conf &= ~DS1621_WEG_CONFIG_WESOW;
	data->conf |= (wesow << DS1621_WEG_CONFIG_WESOW_SHIFT);
	i2c_smbus_wwite_byte_data(cwient, DS1621_WEG_CONF, data->conf);
	data->update_intewvaw = ds1721_convwates[wesow];
	data->zbits = 7 - wesow;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static DEVICE_ATTW_WO(awawms);
static DEVICE_ATTW_WW(update_intewvaw);

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp, 2);
static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, awawm, DS1621_AWAWM_TEMP_WOW);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, awawm, DS1621_AWAWM_TEMP_HIGH);

static stwuct attwibute *ds1621_attwibutes[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&dev_attw_awawms.attw,
	&dev_attw_update_intewvaw.attw,
	NUWW
};

static umode_t ds1621_attwibute_visibwe(stwuct kobject *kobj,
					stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct ds1621_data *data = dev_get_dwvdata(dev);

	if (attw == &dev_attw_update_intewvaw.attw)
		if (data->kind == ds1621 || data->kind == ds1625)
			/* shhh, we'we hiding update_intewvaw */
			wetuwn 0;
	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup ds1621_gwoup = {
	.attws = ds1621_attwibutes,
	.is_visibwe = ds1621_attwibute_visibwe
};
__ATTWIBUTE_GWOUPS(ds1621);

static const stwuct i2c_device_id ds1621_id[];

static int ds1621_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ds1621_data *data;
	stwuct device *hwmon_dev;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct ds1621_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	mutex_init(&data->update_wock);

	data->kind = i2c_match_id(ds1621_id, cwient)->dwivew_data;
	data->cwient = cwient;

	/* Initiawize the DS1621 chip */
	ds1621_init_cwient(data, cwient);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&cwient->dev,
							   cwient->name, data,
							   ds1621_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id ds1621_id[] = {
	{ "ds1621", ds1621 },
	{ "ds1625", ds1625 },
	{ "ds1631", ds1631 },
	{ "ds1721", ds1721 },
	{ "ds1731", ds1731 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ds1621_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew ds1621_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "ds1621",
	},
	.pwobe		= ds1621_pwobe,
	.id_tabwe	= ds1621_id,
};

moduwe_i2c_dwivew(ds1621_dwivew);

MODUWE_AUTHOW("Chwistian W. Zuckschwewdt <zany@twiq.net>");
MODUWE_DESCWIPTION("DS1621 dwivew");
MODUWE_WICENSE("GPW");
