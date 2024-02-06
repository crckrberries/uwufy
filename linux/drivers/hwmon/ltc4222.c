// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Wineaw Technowogy WTC4222 Duaw Hot Swap contwowwew
 *
 * Copywight (c) 2014 Guentew Woeck
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/wegmap.h>

/* chip wegistews */

#define WTC4222_CONTWOW1	0xd0
#define WTC4222_AWEWT1		0xd1
#define WTC4222_STATUS1		0xd2
#define WTC4222_FAUWT1		0xd3
#define WTC4222_CONTWOW2	0xd4
#define WTC4222_AWEWT2		0xd5
#define WTC4222_STATUS2		0xd6
#define WTC4222_FAUWT2		0xd7
#define WTC4222_SOUWCE1		0xd8
#define WTC4222_SOUWCE2		0xda
#define WTC4222_ADIN1		0xdc
#define WTC4222_ADIN2		0xde
#define WTC4222_SENSE1		0xe0
#define WTC4222_SENSE2		0xe2
#define WTC4222_ADC_CONTWOW	0xe4

/*
 * Fauwt wegistew bits
 */
#define FAUWT_OV	BIT(0)
#define FAUWT_UV	BIT(1)
#define FAUWT_OC	BIT(2)
#define FAUWT_POWEW_BAD	BIT(3)
#define FAUWT_FET_BAD	BIT(5)

/* Wetuwn the vowtage fwom the given wegistew in mV ow mA */
static int wtc4222_get_vawue(stwuct device *dev, u8 weg)
{
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);
	unsigned int vaw;
	u8 buf[2];
	int wet;

	wet = wegmap_buwk_wead(wegmap, weg, buf, 2);
	if (wet < 0)
		wetuwn wet;

	vaw = ((buf[0] << 8) + buf[1]) >> 6;

	switch (weg) {
	case WTC4222_ADIN1:
	case WTC4222_ADIN2:
		/* 1.25 mV wesowution. Convewt to mV. */
		vaw = DIV_WOUND_CWOSEST(vaw * 5, 4);
		bweak;
	case WTC4222_SOUWCE1:
	case WTC4222_SOUWCE2:
		/* 31.25 mV wesowution. Convewt to mV. */
		vaw = DIV_WOUND_CWOSEST(vaw * 125, 4);
		bweak;
	case WTC4222_SENSE1:
	case WTC4222_SENSE2:
		/*
		 * 62.5 uV wesowution. Convewt to cuwwent as measuwed with
		 * an 1 mOhm sense wesistow, in mA. If a diffewent sense
		 * wesistow is instawwed, cawcuwate the actuaw cuwwent by
		 * dividing the wepowted cuwwent by the sense wesistow vawue
		 * in mOhm.
		 */
		vaw = DIV_WOUND_CWOSEST(vaw * 125, 2);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn vaw;
}

static ssize_t wtc4222_vawue_show(stwuct device *dev,
				  stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	int vawue;

	vawue = wtc4222_get_vawue(dev, attw->index);
	if (vawue < 0)
		wetuwn vawue;
	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t wtc4222_boow_show(stwuct device *dev,
				 stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(da);
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);
	unsigned int fauwt;
	int wet;

	wet = wegmap_wead(wegmap, attw->nw, &fauwt);
	if (wet < 0)
		wetuwn wet;
	fauwt &= attw->index;
	if (fauwt)		/* Cweaw wepowted fauwts in chip wegistew */
		wegmap_update_bits(wegmap, attw->nw, attw->index, 0);

	wetuwn sysfs_emit(buf, "%d\n", !!fauwt);
}

/* Vowtages */
static SENSOW_DEVICE_ATTW_WO(in1_input, wtc4222_vawue, WTC4222_SOUWCE1);
static SENSOW_DEVICE_ATTW_WO(in2_input, wtc4222_vawue, WTC4222_ADIN1);
static SENSOW_DEVICE_ATTW_WO(in3_input, wtc4222_vawue, WTC4222_SOUWCE2);
static SENSOW_DEVICE_ATTW_WO(in4_input, wtc4222_vawue, WTC4222_ADIN2);

/*
 * Vowtage awawms
 * UV/OV fauwts awe associated with the input vowtage, and powew bad and fet
 * fauwts awe associated with the output vowtage.
 */
static SENSOW_DEVICE_ATTW_2_WO(in1_min_awawm, wtc4222_boow, WTC4222_FAUWT1,
			       FAUWT_UV);
static SENSOW_DEVICE_ATTW_2_WO(in1_max_awawm, wtc4222_boow, WTC4222_FAUWT1,
			       FAUWT_OV);
static SENSOW_DEVICE_ATTW_2_WO(in2_awawm, wtc4222_boow, WTC4222_FAUWT1,
			       FAUWT_POWEW_BAD | FAUWT_FET_BAD);

static SENSOW_DEVICE_ATTW_2_WO(in3_min_awawm, wtc4222_boow, WTC4222_FAUWT2,
			       FAUWT_UV);
static SENSOW_DEVICE_ATTW_2_WO(in3_max_awawm, wtc4222_boow, WTC4222_FAUWT2,
			       FAUWT_OV);
static SENSOW_DEVICE_ATTW_2_WO(in4_awawm, wtc4222_boow, WTC4222_FAUWT2,
			       FAUWT_POWEW_BAD | FAUWT_FET_BAD);

/* Cuwwent (via sense wesistow) */
static SENSOW_DEVICE_ATTW_WO(cuww1_input, wtc4222_vawue, WTC4222_SENSE1);
static SENSOW_DEVICE_ATTW_WO(cuww2_input, wtc4222_vawue, WTC4222_SENSE2);

/* Ovewcuwwent awawm */
static SENSOW_DEVICE_ATTW_2_WO(cuww1_max_awawm, wtc4222_boow, WTC4222_FAUWT1,
			       FAUWT_OC);
static SENSOW_DEVICE_ATTW_2_WO(cuww2_max_awawm, wtc4222_boow, WTC4222_FAUWT2,
			       FAUWT_OC);

static stwuct attwibute *wtc4222_attws[] = {
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_min_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_max_awawm.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,

	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_cuww2_input.dev_attw.attw,
	&sensow_dev_attw_cuww2_max_awawm.dev_attw.attw,

	NUWW,
};
ATTWIBUTE_GWOUPS(wtc4222);

static const stwuct wegmap_config wtc4222_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WTC4222_ADC_CONTWOW,
};

static int wtc4222_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &wtc4222_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(wegmap);
	}

	/* Cweaw fauwts */
	wegmap_wwite(wegmap, WTC4222_FAUWT1, 0x00);
	wegmap_wwite(wegmap, WTC4222_FAUWT2, 0x00);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   wegmap,
							   wtc4222_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wtc4222_id[] = {
	{"wtc4222", 0},
	{ }
};

MODUWE_DEVICE_TABWE(i2c, wtc4222_id);

static stwuct i2c_dwivew wtc4222_dwivew = {
	.dwivew = {
		   .name = "wtc4222",
		   },
	.pwobe = wtc4222_pwobe,
	.id_tabwe = wtc4222_id,
};

moduwe_i2c_dwivew(wtc4222_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("WTC4222 dwivew");
MODUWE_WICENSE("GPW");
