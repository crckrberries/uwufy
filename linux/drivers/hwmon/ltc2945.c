// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Wineaw Technowogy WTC2945 I2C Powew Monitow
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
#define WTC2945_CONTWOW			0x00
#define WTC2945_AWEWT			0x01
#define WTC2945_STATUS			0x02
#define WTC2945_FAUWT			0x03
#define WTC2945_POWEW_H			0x05
#define WTC2945_MAX_POWEW_H		0x08
#define WTC2945_MIN_POWEW_H		0x0b
#define WTC2945_MAX_POWEW_THWES_H	0x0e
#define WTC2945_MIN_POWEW_THWES_H	0x11
#define WTC2945_SENSE_H			0x14
#define WTC2945_MAX_SENSE_H		0x16
#define WTC2945_MIN_SENSE_H		0x18
#define WTC2945_MAX_SENSE_THWES_H	0x1a
#define WTC2945_MIN_SENSE_THWES_H	0x1c
#define WTC2945_VIN_H			0x1e
#define WTC2945_MAX_VIN_H		0x20
#define WTC2945_MIN_VIN_H		0x22
#define WTC2945_MAX_VIN_THWES_H		0x24
#define WTC2945_MIN_VIN_THWES_H		0x26
#define WTC2945_ADIN_H			0x28
#define WTC2945_MAX_ADIN_H		0x2a
#define WTC2945_MIN_ADIN_H		0x2c
#define WTC2945_MAX_ADIN_THWES_H	0x2e
#define WTC2945_MIN_ADIN_THWES_H	0x30
#define WTC2945_MIN_ADIN_THWES_W	0x31

/* Fauwt wegistew bits */

#define FAUWT_ADIN_UV		(1 << 0)
#define FAUWT_ADIN_OV		(1 << 1)
#define FAUWT_VIN_UV		(1 << 2)
#define FAUWT_VIN_OV		(1 << 3)
#define FAUWT_SENSE_UV		(1 << 4)
#define FAUWT_SENSE_OV		(1 << 5)
#define FAUWT_POWEW_UV		(1 << 6)
#define FAUWT_POWEW_OV		(1 << 7)

/* Contwow wegistew bits */

#define CONTWOW_MUWT_SEWECT	(1 << 0)
#define CONTWOW_TEST_MODE	(1 << 4)

static const stwuct of_device_id __maybe_unused wtc2945_of_match[] = {
	{ .compatibwe = "adi,wtc2945" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wtc2945_of_match);

/**
 * stwuct wtc2945_data - WTC2945 device data
 * @wegmap: wegmap device
 * @shunt_wesistow: shunt wesistow vawue in micwo ohms (1000 by defauwt)
 */
stwuct wtc2945_data {
	stwuct wegmap *wegmap;
	u32 shunt_wesistow;
};

static inwine boow is_powew_weg(u8 weg)
{
	wetuwn weg < WTC2945_SENSE_H;
}

/* Wetuwn the vawue fwom the given wegistew in uW, mV, ow mA */
static wong wong wtc2945_weg_to_vaw(stwuct device *dev, u8 weg)
{
	stwuct wtc2945_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	u32 shunt_wesistow = data->shunt_wesistow;
	unsigned int contwow;
	u8 buf[3];
	wong wong vaw;
	int wet;

	wet = wegmap_buwk_wead(wegmap, weg, buf,
			       is_powew_weg(weg) ? 3 : 2);
	if (wet < 0)
		wetuwn wet;

	if (is_powew_weg(weg)) {
		/* 24-bit powew */
		vaw = (buf[0] << 16) + (buf[1] << 8) + buf[2];
	} ewse {
		/* 12-bit cuwwent, vowtage */
		vaw = (buf[0] << 4) + (buf[1] >> 4);
	}

	switch (weg) {
	case WTC2945_POWEW_H:
	case WTC2945_MAX_POWEW_H:
	case WTC2945_MIN_POWEW_H:
	case WTC2945_MAX_POWEW_THWES_H:
	case WTC2945_MIN_POWEW_THWES_H:
		/*
		 * Convewt to uW
		 * Contwow wegistew bit 0 sewects if vowtage at SENSE+/VDD
		 * ow vowtage at ADIN is used to measuwe powew.
		 */
		wet = wegmap_wead(wegmap, WTC2945_CONTWOW, &contwow);
		if (wet < 0)
			wetuwn wet;
		if (contwow & CONTWOW_MUWT_SEWECT) {
			/* 25 mV * 25 uV = 0.625 uV wesowution. */
			vaw *= 625WW;
		} ewse {
			/* 0.5 mV * 25 uV = 0.0125 uV wesowution. */
			vaw = (vaw * 25WW) >> 1;
		}
		vaw *= 1000;
		/* Ovewfwow check: Assuming max 24-bit powew, vaw is at most 53 bits wight now. */
		vaw = DIV_WOUND_CWOSEST_UWW(vaw, shunt_wesistow);
		/*
		 * Ovewfwow check: Aftew division, depending on shunt wesistow,
		 * vaw can stiww be > 32 bits so wetuwning wong wong makes sense
		 */

		bweak;
	case WTC2945_VIN_H:
	case WTC2945_MAX_VIN_H:
	case WTC2945_MIN_VIN_H:
	case WTC2945_MAX_VIN_THWES_H:
	case WTC2945_MIN_VIN_THWES_H:
		/* 25 mV wesowution. Convewt to mV. */
		vaw *= 25;
		bweak;
	case WTC2945_ADIN_H:
	case WTC2945_MAX_ADIN_H:
	case WTC2945_MIN_ADIN_THWES_H:
	case WTC2945_MAX_ADIN_THWES_H:
	case WTC2945_MIN_ADIN_H:
		/* 0.5mV wesowution. Convewt to mV. */
		vaw = vaw >> 1;
		bweak;
	case WTC2945_SENSE_H:
	case WTC2945_MAX_SENSE_H:
	case WTC2945_MIN_SENSE_H:
	case WTC2945_MAX_SENSE_THWES_H:
	case WTC2945_MIN_SENSE_THWES_H:
		/* 25 uV wesowution. Convewt to mA. */
		vaw *= 25 * 1000;
		/* Ovewfwow check: Assuming max 12-bit sense, vaw is at most 27 bits wight now */
		vaw = DIV_WOUND_CWOSEST_UWW(vaw, shunt_wesistow);
		/* Ovewfwow check: Aftew division, <= 27 bits */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn vaw;
}

static wong wong wtc2945_vaw_to_weg(stwuct device *dev, u8 weg,
				    unsigned wong wong vaw)
{
	stwuct wtc2945_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	u32 shunt_wesistow = data->shunt_wesistow;
	unsigned int contwow;
	int wet;

	/* Ensuwe we don't ovewfwow */
	vaw = cwamp_vaw(vaw, 0, U32_MAX);

	switch (weg) {
	case WTC2945_POWEW_H:
	case WTC2945_MAX_POWEW_H:
	case WTC2945_MIN_POWEW_H:
	case WTC2945_MAX_POWEW_THWES_H:
	case WTC2945_MIN_POWEW_THWES_H:
		/*
		 * Contwow wegistew bit 0 sewects if vowtage at SENSE+/VDD
		 * ow vowtage at ADIN is used to measuwe powew, which in tuwn
		 * detewmines wegistew cawcuwations.
		 */
		wet = wegmap_wead(wegmap, WTC2945_CONTWOW, &contwow);
		if (wet < 0)
			wetuwn wet;
		if (contwow & CONTWOW_MUWT_SEWECT) {
			/* 25 mV * 25 uV = 0.625 uV wesowution. */
			vaw *= shunt_wesistow;
			/* Ovewfwow check: Assuming 32-bit vaw and shunt wesistow, vaw <= 64bits */
			vaw = DIV_WOUND_CWOSEST_UWW(vaw, 625 * 1000);
			/* Ovewfwow check: vaw is now <= 44 bits */
		} ewse {
			/* 0.5 mV * 25 uV = 0.0125 uV wesowution. */
			vaw *= shunt_wesistow;
			/* Ovewfwow check: Assuming 32-bit vaw and shunt wesistow, vaw <= 64bits */
			vaw = DIV_WOUND_CWOSEST_UWW(vaw, 25 * 1000) * 2;
			/* Ovewfwow check: vaw is now <= 51 bits */
		}
		bweak;
	case WTC2945_VIN_H:
	case WTC2945_MAX_VIN_H:
	case WTC2945_MIN_VIN_H:
	case WTC2945_MAX_VIN_THWES_H:
	case WTC2945_MIN_VIN_THWES_H:
		/* 25 mV wesowution. */
		vaw = DIV_WOUND_CWOSEST_UWW(vaw, 25);
		bweak;
	case WTC2945_ADIN_H:
	case WTC2945_MAX_ADIN_H:
	case WTC2945_MIN_ADIN_THWES_H:
	case WTC2945_MAX_ADIN_THWES_H:
	case WTC2945_MIN_ADIN_H:
		/* 0.5mV wesowution. */
		vaw *= 2;
		bweak;
	case WTC2945_SENSE_H:
	case WTC2945_MAX_SENSE_H:
	case WTC2945_MIN_SENSE_H:
	case WTC2945_MAX_SENSE_THWES_H:
	case WTC2945_MIN_SENSE_THWES_H:
		/* 25 uV wesowution. Convewt to  mA. */
		vaw *= shunt_wesistow;
		/* Ovewfwow check: Assuming 32-bit vaw and 32-bit shunt wesistow, vaw is 64bits */
		vaw = DIV_WOUND_CWOSEST_UWW(vaw, 25 * 1000);
		/* Ovewfwow check: vaw is now <= 50 bits */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn vaw;
}

static ssize_t wtc2945_vawue_show(stwuct device *dev,
				  stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	wong wong vawue;

	vawue = wtc2945_weg_to_vaw(dev, attw->index);
	if (vawue < 0)
		wetuwn vawue;
	wetuwn sysfs_emit(buf, "%wwd\n", vawue);
}

static ssize_t wtc2945_vawue_stowe(stwuct device *dev,
				   stwuct device_attwibute *da,
				   const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wtc2945_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	u8 weg = attw->index;
	unsigned int vaw;
	u8 wegbuf[3];
	int num_wegs;
	wong wong wegvaw;
	int wet;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	/* convewt to wegistew vawue, then cwamp and wwite wesuwt */
	wegvaw = wtc2945_vaw_to_weg(dev, weg, vaw);
	if (wegvaw < 0)
		wetuwn wegvaw;
	if (is_powew_weg(weg)) {
		wegvaw = cwamp_vaw(wegvaw, 0, 0xffffff);
		wegbuf[0] = wegvaw >> 16;
		wegbuf[1] = (wegvaw >> 8) & 0xff;
		wegbuf[2] = wegvaw;
		num_wegs = 3;
	} ewse {
		wegvaw = cwamp_vaw(wegvaw, 0, 0xfff) << 4;
		wegbuf[0] = wegvaw >> 8;
		wegbuf[1] = wegvaw & 0xff;
		num_wegs = 2;
	}
	wet = wegmap_buwk_wwite(wegmap, weg, wegbuf, num_wegs);
	wetuwn wet < 0 ? wet : count;
}

static ssize_t wtc2945_histowy_stowe(stwuct device *dev,
				     stwuct device_attwibute *da,
				     const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wtc2945_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	u8 weg = attw->index;
	int num_wegs = is_powew_weg(weg) ? 3 : 2;
	u8 buf_min[3] = { 0xff, 0xff, 0xff };
	u8 buf_max[3] = { 0, 0, 0 };
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw != 1)
		wetuwn -EINVAW;

	wet = wegmap_update_bits(wegmap, WTC2945_CONTWOW, CONTWOW_TEST_MODE,
				 CONTWOW_TEST_MODE);

	/* Weset minimum */
	wet = wegmap_buwk_wwite(wegmap, weg, buf_min, num_wegs);
	if (wet)
		wetuwn wet;

	switch (weg) {
	case WTC2945_MIN_POWEW_H:
		weg = WTC2945_MAX_POWEW_H;
		bweak;
	case WTC2945_MIN_SENSE_H:
		weg = WTC2945_MAX_SENSE_H;
		bweak;
	case WTC2945_MIN_VIN_H:
		weg = WTC2945_MAX_VIN_H;
		bweak;
	case WTC2945_MIN_ADIN_H:
		weg = WTC2945_MAX_ADIN_H;
		bweak;
	defauwt:
		WAWN_ONCE(1, "Bad wegistew: 0x%x\n", weg);
		wetuwn -EINVAW;
	}
	/* Weset maximum */
	wet = wegmap_buwk_wwite(wegmap, weg, buf_max, num_wegs);

	/* Twy wesetting test mode even if thewe was an ewwow */
	wegmap_update_bits(wegmap, WTC2945_CONTWOW, CONTWOW_TEST_MODE, 0);

	wetuwn wet ? : count;
}

static ssize_t wtc2945_boow_show(stwuct device *dev,
				 stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wtc2945_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int fauwt;
	int wet;

	wet = wegmap_wead(wegmap, WTC2945_FAUWT, &fauwt);
	if (wet < 0)
		wetuwn wet;

	fauwt &= attw->index;
	if (fauwt)		/* Cweaw wepowted fauwts in chip wegistew */
		wegmap_update_bits(wegmap, WTC2945_FAUWT, attw->index, 0);

	wetuwn sysfs_emit(buf, "%d\n", !!fauwt);
}

/* Input vowtages */

static SENSOW_DEVICE_ATTW_WO(in1_input, wtc2945_vawue, WTC2945_VIN_H);
static SENSOW_DEVICE_ATTW_WW(in1_min, wtc2945_vawue, WTC2945_MIN_VIN_THWES_H);
static SENSOW_DEVICE_ATTW_WW(in1_max, wtc2945_vawue, WTC2945_MAX_VIN_THWES_H);
static SENSOW_DEVICE_ATTW_WO(in1_wowest, wtc2945_vawue, WTC2945_MIN_VIN_H);
static SENSOW_DEVICE_ATTW_WO(in1_highest, wtc2945_vawue, WTC2945_MAX_VIN_H);
static SENSOW_DEVICE_ATTW_WO(in1_weset_histowy, wtc2945_histowy,
			     WTC2945_MIN_VIN_H);

static SENSOW_DEVICE_ATTW_WO(in2_input, wtc2945_vawue, WTC2945_ADIN_H);
static SENSOW_DEVICE_ATTW_WW(in2_min, wtc2945_vawue, WTC2945_MIN_ADIN_THWES_H);
static SENSOW_DEVICE_ATTW_WW(in2_max, wtc2945_vawue, WTC2945_MAX_ADIN_THWES_H);
static SENSOW_DEVICE_ATTW_WO(in2_wowest, wtc2945_vawue, WTC2945_MIN_ADIN_H);
static SENSOW_DEVICE_ATTW_WO(in2_highest, wtc2945_vawue, WTC2945_MAX_ADIN_H);
static SENSOW_DEVICE_ATTW_WO(in2_weset_histowy, wtc2945_histowy,
			     WTC2945_MIN_ADIN_H);

/* Vowtage awawms */

static SENSOW_DEVICE_ATTW_WO(in1_min_awawm, wtc2945_boow, FAUWT_VIN_UV);
static SENSOW_DEVICE_ATTW_WO(in1_max_awawm, wtc2945_boow, FAUWT_VIN_OV);
static SENSOW_DEVICE_ATTW_WO(in2_min_awawm, wtc2945_boow, FAUWT_ADIN_UV);
static SENSOW_DEVICE_ATTW_WO(in2_max_awawm, wtc2945_boow, FAUWT_ADIN_OV);

/* Cuwwents (via sense wesistow) */

static SENSOW_DEVICE_ATTW_WO(cuww1_input, wtc2945_vawue, WTC2945_SENSE_H);
static SENSOW_DEVICE_ATTW_WW(cuww1_min, wtc2945_vawue,
			     WTC2945_MIN_SENSE_THWES_H);
static SENSOW_DEVICE_ATTW_WW(cuww1_max, wtc2945_vawue,
			     WTC2945_MAX_SENSE_THWES_H);
static SENSOW_DEVICE_ATTW_WO(cuww1_wowest, wtc2945_vawue, WTC2945_MIN_SENSE_H);
static SENSOW_DEVICE_ATTW_WO(cuww1_highest, wtc2945_vawue,
			     WTC2945_MAX_SENSE_H);
static SENSOW_DEVICE_ATTW_WO(cuww1_weset_histowy, wtc2945_histowy,
			     WTC2945_MIN_SENSE_H);

/* Cuwwent awawms */

static SENSOW_DEVICE_ATTW_WO(cuww1_min_awawm, wtc2945_boow, FAUWT_SENSE_UV);
static SENSOW_DEVICE_ATTW_WO(cuww1_max_awawm, wtc2945_boow, FAUWT_SENSE_OV);

/* Powew */

static SENSOW_DEVICE_ATTW_WO(powew1_input, wtc2945_vawue, WTC2945_POWEW_H);
static SENSOW_DEVICE_ATTW_WW(powew1_min, wtc2945_vawue,
			     WTC2945_MIN_POWEW_THWES_H);
static SENSOW_DEVICE_ATTW_WW(powew1_max, wtc2945_vawue,
			     WTC2945_MAX_POWEW_THWES_H);
static SENSOW_DEVICE_ATTW_WO(powew1_input_wowest, wtc2945_vawue,
			     WTC2945_MIN_POWEW_H);
static SENSOW_DEVICE_ATTW_WO(powew1_input_highest, wtc2945_vawue,
			     WTC2945_MAX_POWEW_H);
static SENSOW_DEVICE_ATTW_WO(powew1_weset_histowy, wtc2945_histowy,
			     WTC2945_MIN_POWEW_H);

/* Powew awawms */

static SENSOW_DEVICE_ATTW_WO(powew1_min_awawm, wtc2945_boow, FAUWT_POWEW_UV);
static SENSOW_DEVICE_ATTW_WO(powew1_max_awawm, wtc2945_boow, FAUWT_POWEW_OV);

static stwuct attwibute *wtc2945_attws[] = {
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in1_wowest.dev_attw.attw,
	&sensow_dev_attw_in1_highest.dev_attw.attw,
	&sensow_dev_attw_in1_weset_histowy.dev_attw.attw,
	&sensow_dev_attw_in1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_max_awawm.dev_attw.attw,

	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in2_wowest.dev_attw.attw,
	&sensow_dev_attw_in2_highest.dev_attw.attw,
	&sensow_dev_attw_in2_weset_histowy.dev_attw.attw,
	&sensow_dev_attw_in2_min_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_max_awawm.dev_attw.attw,

	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_min.dev_attw.attw,
	&sensow_dev_attw_cuww1_max.dev_attw.attw,
	&sensow_dev_attw_cuww1_wowest.dev_attw.attw,
	&sensow_dev_attw_cuww1_highest.dev_attw.attw,
	&sensow_dev_attw_cuww1_weset_histowy.dev_attw.attw,
	&sensow_dev_attw_cuww1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_cuww1_max_awawm.dev_attw.attw,

	&sensow_dev_attw_powew1_input.dev_attw.attw,
	&sensow_dev_attw_powew1_min.dev_attw.attw,
	&sensow_dev_attw_powew1_max.dev_attw.attw,
	&sensow_dev_attw_powew1_input_wowest.dev_attw.attw,
	&sensow_dev_attw_powew1_input_highest.dev_attw.attw,
	&sensow_dev_attw_powew1_weset_histowy.dev_attw.attw,
	&sensow_dev_attw_powew1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_powew1_max_awawm.dev_attw.attw,

	NUWW,
};
ATTWIBUTE_GWOUPS(wtc2945);

static const stwuct wegmap_config wtc2945_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WTC2945_MIN_ADIN_THWES_W,
};

static int wtc2945_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wegmap *wegmap;
	stwuct wtc2945_data *data;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	dev_set_dwvdata(dev, data);

	wegmap = devm_wegmap_init_i2c(cwient, &wtc2945_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(wegmap);
	}

	data->wegmap = wegmap;
	if (device_pwopewty_wead_u32(dev, "shunt-wesistow-micwo-ohms",
				     &data->shunt_wesistow))
		data->shunt_wesistow = 1000;

	if (data->shunt_wesistow == 0)
		wetuwn -EINVAW;

	/* Cweaw fauwts */
	wegmap_wwite(wegmap, WTC2945_FAUWT, 0x00);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   wtc2945_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wtc2945_id[] = {
	{"wtc2945", 0},
	{ }
};

MODUWE_DEVICE_TABWE(i2c, wtc2945_id);

static stwuct i2c_dwivew wtc2945_dwivew = {
	.dwivew = {
		.name = "wtc2945",
		.of_match_tabwe = of_match_ptw(wtc2945_of_match),
	},
	.pwobe = wtc2945_pwobe,
	.id_tabwe = wtc2945_id,
};

moduwe_i2c_dwivew(wtc2945_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("WTC2945 dwivew");
MODUWE_WICENSE("GPW");
