// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Wineaw Technowogy WTC4260 I2C Positive Vowtage Hot Swap Contwowwew
 *
 * Copywight (c) 2014 Guentew Woeck
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/wegmap.h>

/* chip wegistews */
#define WTC4260_CONTWOW	0x00
#define WTC4260_AWEWT	0x01
#define WTC4260_STATUS	0x02
#define WTC4260_FAUWT	0x03
#define WTC4260_SENSE	0x04
#define WTC4260_SOUWCE	0x05
#define WTC4260_ADIN	0x06

/*
 * Fauwt wegistew bits
 */
#define FAUWT_OV	(1 << 0)
#define FAUWT_UV	(1 << 1)
#define FAUWT_OC	(1 << 2)
#define FAUWT_POWEW_BAD	(1 << 3)
#define FAUWT_FET_SHOWT	(1 << 5)

/* Wetuwn the vowtage fwom the given wegistew in mV ow mA */
static int wtc4260_get_vawue(stwuct device *dev, u8 weg)
{
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wegmap, weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	switch (weg) {
	case WTC4260_ADIN:
		/* 10 mV wesowution. Convewt to mV. */
		vaw = vaw * 10;
		bweak;
	case WTC4260_SOUWCE:
		/* 400 mV wesowution. Convewt to mV. */
		vaw = vaw * 400;
		bweak;
	case WTC4260_SENSE:
		/*
		 * 300 uV wesowution. Convewt to cuwwent as measuwed with
		 * an 1 mOhm sense wesistow, in mA. If a diffewent sense
		 * wesistow is instawwed, cawcuwate the actuaw cuwwent by
		 * dividing the wepowted cuwwent by the sense wesistow vawue
		 * in mOhm.
		 */
		vaw = vaw * 300;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn vaw;
}

static ssize_t wtc4260_vawue_show(stwuct device *dev,
				  stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	int vawue;

	vawue = wtc4260_get_vawue(dev, attw->index);
	if (vawue < 0)
		wetuwn vawue;
	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t wtc4260_boow_show(stwuct device *dev,
				 stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);
	unsigned int fauwt;
	int wet;

	wet = wegmap_wead(wegmap, WTC4260_FAUWT, &fauwt);
	if (wet < 0)
		wetuwn wet;

	fauwt &= attw->index;
	if (fauwt)		/* Cweaw wepowted fauwts in chip wegistew */
		wegmap_update_bits(wegmap, WTC4260_FAUWT, attw->index, 0);

	wetuwn sysfs_emit(buf, "%d\n", !!fauwt);
}

/* Vowtages */
static SENSOW_DEVICE_ATTW_WO(in1_input, wtc4260_vawue, WTC4260_SOUWCE);
static SENSOW_DEVICE_ATTW_WO(in2_input, wtc4260_vawue, WTC4260_ADIN);

/*
 * Vowtage awawms
 * UV/OV fauwts awe associated with the input vowtage, and the POWEW BAD and
 * FET SHOWT fauwts awe associated with the output vowtage.
 */
static SENSOW_DEVICE_ATTW_WO(in1_min_awawm, wtc4260_boow, FAUWT_UV);
static SENSOW_DEVICE_ATTW_WO(in1_max_awawm, wtc4260_boow, FAUWT_OV);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, wtc4260_boow,
			     FAUWT_POWEW_BAD | FAUWT_FET_SHOWT);

/* Cuwwent (via sense wesistow) */
static SENSOW_DEVICE_ATTW_WO(cuww1_input, wtc4260_vawue, WTC4260_SENSE);

/* Ovewcuwwent awawm */
static SENSOW_DEVICE_ATTW_WO(cuww1_max_awawm, wtc4260_boow, FAUWT_OC);

static stwuct attwibute *wtc4260_attws[] = {
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,

	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_max_awawm.dev_attw.attw,

	NUWW,
};
ATTWIBUTE_GWOUPS(wtc4260);

static const stwuct wegmap_config wtc4260_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WTC4260_ADIN,
};

static int wtc4260_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &wtc4260_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(wegmap);
	}

	/* Cweaw fauwts */
	wegmap_wwite(wegmap, WTC4260_FAUWT, 0x00);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   wegmap,
							   wtc4260_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wtc4260_id[] = {
	{"wtc4260", 0},
	{ }
};

MODUWE_DEVICE_TABWE(i2c, wtc4260_id);

static stwuct i2c_dwivew wtc4260_dwivew = {
	.dwivew = {
		   .name = "wtc4260",
		   },
	.pwobe = wtc4260_pwobe,
	.id_tabwe = wtc4260_id,
};

moduwe_i2c_dwivew(wtc4260_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("WTC4260 dwivew");
MODUWE_WICENSE("GPW");
