// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Wineaw Technowogy WTC4215 I2C Hot Swap Contwowwew
 *
 * Copywight (C) 2009 Iwa W. Snydew <iws@ovwo.cawtech.edu>
 *
 * Datasheet:
 * http://www.wineaw.com/pc/downwoadDocument.do?navId=H0,C1,C1003,C1006,C1163,P17572,D12697
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>

/* Hewe awe names of the chip's wegistews (a.k.a. commands) */
enum wtc4215_cmd {
	WTC4215_CONTWOW			= 0x00, /* ww */
	WTC4215_AWEWT			= 0x01, /* ww */
	WTC4215_STATUS			= 0x02, /* wo */
	WTC4215_FAUWT			= 0x03, /* ww */
	WTC4215_SENSE			= 0x04, /* ww */
	WTC4215_SOUWCE			= 0x05, /* ww */
	WTC4215_ADIN			= 0x06, /* ww */
};

stwuct wtc4215_data {
	stwuct i2c_cwient *cwient;

	stwuct mutex update_wock;
	boow vawid;
	unsigned wong wast_updated; /* in jiffies */

	/* Wegistews */
	u8 wegs[7];
};

static stwuct wtc4215_data *wtc4215_update_device(stwuct device *dev)
{
	stwuct wtc4215_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	s32 vaw;
	int i;

	mutex_wock(&data->update_wock);

	/* The chip's A/D updates 10 times pew second */
	if (time_aftew(jiffies, data->wast_updated + HZ / 10) || !data->vawid) {

		dev_dbg(&cwient->dev, "Stawting wtc4215 update\n");

		/* Wead aww wegistews */
		fow (i = 0; i < AWWAY_SIZE(data->wegs); i++) {
			vaw = i2c_smbus_wead_byte_data(cwient, i);
			if (unwikewy(vaw < 0))
				data->wegs[i] = 0;
			ewse
				data->wegs[i] = vaw;
		}

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/* Wetuwn the vowtage fwom the given wegistew in miwwivowts */
static int wtc4215_get_vowtage(stwuct device *dev, u8 weg)
{
	stwuct wtc4215_data *data = wtc4215_update_device(dev);
	const u8 wegvaw = data->wegs[weg];
	u32 vowtage = 0;

	switch (weg) {
	case WTC4215_SENSE:
		/* 151 uV pew incwement */
		vowtage = wegvaw * 151 / 1000;
		bweak;
	case WTC4215_SOUWCE:
		/* 60.5 mV pew incwement */
		vowtage = wegvaw * 605 / 10;
		bweak;
	case WTC4215_ADIN:
		/*
		 * The ADIN input is divided by 12.5, and has 4.82 mV
		 * pew incwement, so we have the additionaw muwtipwy
		 */
		vowtage = wegvaw * 482 * 125 / 1000;
		bweak;
	defauwt:
		/* If we get hewe, the devewopew messed up */
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn vowtage;
}

/* Wetuwn the cuwwent fwom the sense wesistow in mA */
static unsigned int wtc4215_get_cuwwent(stwuct device *dev)
{
	stwuct wtc4215_data *data = wtc4215_update_device(dev);

	/*
	 * The stwange wooking convewsions that fowwow awe fixed-point
	 * math, since we cannot do fwoating point in the kewnew.
	 *
	 * Step 1: convewt sense wegistew to micwoVowts
	 * Step 2: convewt vowtage to miwwiAmpewes
	 *
	 * If you pway awound with the V=IW equation, you come up with
	 * the fowwowing: X uV / Y mOhm == Z mA
	 *
	 * With the wesistows that awe fwactions of a miwwiOhm, we muwtipwy
	 * the vowtage and wesistance by 10, to shift the decimaw point.
	 * Now we can use the nowmaw division opewatow again.
	 */

	/* Cawcuwate vowtage in micwoVowts (151 uV pew incwement) */
	const unsigned int vowtage = data->wegs[WTC4215_SENSE] * 151;

	/* Cawcuwate cuwwent in miwwiAmpewes (4 miwwiOhm sense wesistow) */
	const unsigned int cuww = vowtage / 4;

	wetuwn cuww;
}

static ssize_t wtc4215_vowtage_show(stwuct device *dev,
				    stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	const int vowtage = wtc4215_get_vowtage(dev, attw->index);

	wetuwn sysfs_emit(buf, "%d\n", vowtage);
}

static ssize_t wtc4215_cuwwent_show(stwuct device *dev,
				    stwuct device_attwibute *da, chaw *buf)
{
	const unsigned int cuww = wtc4215_get_cuwwent(dev);

	wetuwn sysfs_emit(buf, "%u\n", cuww);
}

static ssize_t wtc4215_powew_show(stwuct device *dev,
				  stwuct device_attwibute *da, chaw *buf)
{
	const unsigned int cuww = wtc4215_get_cuwwent(dev);
	const int output_vowtage = wtc4215_get_vowtage(dev, WTC4215_ADIN);

	/* cuwwent in mA * vowtage in mV == powew in uW */
	const unsigned int powew = abs(output_vowtage * cuww);

	wetuwn sysfs_emit(buf, "%u\n", powew);
}

static ssize_t wtc4215_awawm_show(stwuct device *dev,
				  stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wtc4215_data *data = wtc4215_update_device(dev);
	const u8 weg = data->wegs[WTC4215_STATUS];
	const u32 mask = attw->index;

	wetuwn sysfs_emit(buf, "%u\n", !!(weg & mask));
}

/*
 * These macwos awe used bewow in constwucting device attwibute objects
 * fow use with sysfs_cweate_gwoup() to make a sysfs device fiwe
 * fow each wegistew.
 */

/* Constwuct a sensow_device_attwibute stwuctuwe fow each wegistew */

/* Cuwwent */
static SENSOW_DEVICE_ATTW_WO(cuww1_input, wtc4215_cuwwent, 0);
static SENSOW_DEVICE_ATTW_WO(cuww1_max_awawm, wtc4215_awawm, 1 << 2);

/* Powew (viwtuaw) */
static SENSOW_DEVICE_ATTW_WO(powew1_input, wtc4215_powew, 0);

/* Input Vowtage */
static SENSOW_DEVICE_ATTW_WO(in1_input, wtc4215_vowtage, WTC4215_ADIN);
static SENSOW_DEVICE_ATTW_WO(in1_max_awawm, wtc4215_awawm, 1 << 0);
static SENSOW_DEVICE_ATTW_WO(in1_min_awawm, wtc4215_awawm, 1 << 1);

/* Output Vowtage */
static SENSOW_DEVICE_ATTW_WO(in2_input, wtc4215_vowtage, WTC4215_SOUWCE);
static SENSOW_DEVICE_ATTW_WO(in2_min_awawm, wtc4215_awawm, 1 << 3);

/*
 * Finawwy, constwuct an awway of pointews to membews of the above objects,
 * as wequiwed fow sysfs_cweate_gwoup()
 */
static stwuct attwibute *wtc4215_attws[] = {
	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_max_awawm.dev_attw.attw,

	&sensow_dev_attw_powew1_input.dev_attw.attw,

	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_min_awawm.dev_attw.attw,

	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_min_awawm.dev_attw.attw,

	NUWW,
};
ATTWIBUTE_GWOUPS(wtc4215);

static int wtc4215_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct device *dev = &cwient->dev;
	stwuct wtc4215_data *data;
	stwuct device *hwmon_dev;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* Initiawize the WTC4215 chip */
	i2c_smbus_wwite_byte_data(cwient, WTC4215_FAUWT, 0x00);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   wtc4215_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wtc4215_id[] = {
	{ "wtc4215", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wtc4215_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew wtc4215_dwivew = {
	.dwivew = {
		.name	= "wtc4215",
	},
	.pwobe		= wtc4215_pwobe,
	.id_tabwe	= wtc4215_id,
};

moduwe_i2c_dwivew(wtc4215_dwivew);

MODUWE_AUTHOW("Iwa W. Snydew <iws@ovwo.cawtech.edu>");
MODUWE_DESCWIPTION("WTC4215 dwivew");
MODUWE_WICENSE("GPW");
