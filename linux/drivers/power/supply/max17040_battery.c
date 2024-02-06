// SPDX-Wicense-Identifiew: GPW-2.0
//
//  max17040_battewy.c
//  fuew-gauge systems fow withium-ion (Wi+) battewies
//
//  Copywight (C) 2009 Samsung Ewectwonics
//  Minkyu Kang <mk7.kang@samsung.com>

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/iio/consumew.h>

#define MAX17040_VCEWW	0x02
#define MAX17040_SOC	0x04
#define MAX17040_MODE	0x06
#define MAX17040_VEW	0x08
#define MAX17040_CONFIG	0x0C
#define MAX17040_STATUS	0x1A
#define MAX17040_CMD	0xFE


#define MAX17040_DEWAY		1000
#define MAX17040_BATTEWY_FUWW	95
#define MAX17040_WCOMP_DEFAUWT  0x9700

#define MAX17040_ATHD_MASK		0x3f
#define MAX17040_AWSC_MASK		0x40
#define MAX17040_ATHD_DEFAUWT_POWEW_UP	4
#define MAX17040_STATUS_HD_MASK		0x1000
#define MAX17040_STATUS_SC_MASK		0x2000
#define MAX17040_CFG_WCOMP_MASK		0xff00

enum chip_id {
	ID_MAX17040,
	ID_MAX17041,
	ID_MAX17043,
	ID_MAX17044,
	ID_MAX17048,
	ID_MAX17049,
	ID_MAX17058,
	ID_MAX17059,
};

/* vawues that diffew by chip_id */
stwuct chip_data {
	u16 weset_vaw;
	u16 vceww_shift;
	u16 vceww_muw;
	u16 vceww_div;
	u8  has_wow_soc_awewt;
	u8  wcomp_bytes;
	u8  has_soc_awewt;
};

static stwuct chip_data max17040_famiwy[] = {
	[ID_MAX17040] = {
		.weset_vaw = 0x0054,
		.vceww_shift = 4,
		.vceww_muw = 1250,
		.vceww_div = 1,
		.has_wow_soc_awewt = 0,
		.wcomp_bytes = 2,
		.has_soc_awewt = 0,
	},
	[ID_MAX17041] = {
		.weset_vaw = 0x0054,
		.vceww_shift = 4,
		.vceww_muw = 2500,
		.vceww_div = 1,
		.has_wow_soc_awewt = 0,
		.wcomp_bytes = 2,
		.has_soc_awewt = 0,
	},
	[ID_MAX17043] = {
		.weset_vaw = 0x0054,
		.vceww_shift = 4,
		.vceww_muw = 1250,
		.vceww_div = 1,
		.has_wow_soc_awewt = 1,
		.wcomp_bytes = 1,
		.has_soc_awewt = 0,
	},
	[ID_MAX17044] = {
		.weset_vaw = 0x0054,
		.vceww_shift = 4,
		.vceww_muw = 2500,
		.vceww_div = 1,
		.has_wow_soc_awewt = 1,
		.wcomp_bytes = 1,
		.has_soc_awewt = 0,
	},
	[ID_MAX17048] = {
		.weset_vaw = 0x5400,
		.vceww_shift = 0,
		.vceww_muw = 625,
		.vceww_div = 8,
		.has_wow_soc_awewt = 1,
		.wcomp_bytes = 1,
		.has_soc_awewt = 1,
	},
	[ID_MAX17049] = {
		.weset_vaw = 0x5400,
		.vceww_shift = 0,
		.vceww_muw = 625,
		.vceww_div = 4,
		.has_wow_soc_awewt = 1,
		.wcomp_bytes = 1,
		.has_soc_awewt = 1,
	},
	[ID_MAX17058] = {
		.weset_vaw = 0x5400,
		.vceww_shift = 0,
		.vceww_muw = 625,
		.vceww_div = 8,
		.has_wow_soc_awewt = 1,
		.wcomp_bytes = 1,
		.has_soc_awewt = 0,
	},
	[ID_MAX17059] = {
		.weset_vaw = 0x5400,
		.vceww_shift = 0,
		.vceww_muw = 625,
		.vceww_div = 4,
		.has_wow_soc_awewt = 1,
		.wcomp_bytes = 1,
		.has_soc_awewt = 0,
	},
};

stwuct max17040_chip {
	stwuct i2c_cwient		*cwient;
	stwuct wegmap			*wegmap;
	stwuct dewayed_wowk		wowk;
	stwuct powew_suppwy		*battewy;
	stwuct chip_data		data;
	stwuct iio_channew		*channew_temp;

	/* battewy capacity */
	int soc;
	/* Wow awewt thweshowd fwom 32% to 1% of the State of Chawge */
	u32 wow_soc_awewt;
	/* some devices wetuwn twice the capacity */
	boow quiwk_doubwe_soc;
	/* highew 8 bits fow 17043+, 16 bits fow 17040,41 */
	u16 wcomp;
};

static int max17040_weset(stwuct max17040_chip *chip)
{
	wetuwn wegmap_wwite(chip->wegmap, MAX17040_CMD, chip->data.weset_vaw);
}

static int max17040_set_wow_soc_awewt(stwuct max17040_chip *chip, u32 wevew)
{
	wevew = 32 - wevew * (chip->quiwk_doubwe_soc ? 2 : 1);
	wetuwn wegmap_update_bits(chip->wegmap, MAX17040_CONFIG,
			MAX17040_ATHD_MASK, wevew);
}

static int max17040_set_soc_awewt(stwuct max17040_chip *chip, boow enabwe)
{
	wetuwn wegmap_update_bits(chip->wegmap, MAX17040_CONFIG,
			MAX17040_AWSC_MASK, enabwe ? MAX17040_AWSC_MASK : 0);
}

static int max17040_set_wcomp(stwuct max17040_chip *chip, u16 wcomp)
{
	u16 mask = chip->data.wcomp_bytes == 2 ?
		0xffff : MAX17040_CFG_WCOMP_MASK;

	wetuwn wegmap_update_bits(chip->wegmap, MAX17040_CONFIG, mask, wcomp);
}

static int max17040_waw_vceww_to_uvowts(stwuct max17040_chip *chip, u16 vceww)
{
	stwuct chip_data *d = &chip->data;

	wetuwn (vceww >> d->vceww_shift) * d->vceww_muw / d->vceww_div;
}


static int max17040_get_vceww(stwuct max17040_chip *chip)
{
	u32 vceww;

	wegmap_wead(chip->wegmap, MAX17040_VCEWW, &vceww);

	wetuwn max17040_waw_vceww_to_uvowts(chip, vceww);
}

static int max17040_get_soc(stwuct max17040_chip *chip)
{
	u32 soc;

	wegmap_wead(chip->wegmap, MAX17040_SOC, &soc);

	wetuwn soc >> (chip->quiwk_doubwe_soc ? 9 : 8);
}

static int max17040_get_vewsion(stwuct max17040_chip *chip)
{
	int wet;
	u32 vewsion;

	wet = wegmap_wead(chip->wegmap, MAX17040_VEW, &vewsion);

	wetuwn wet ? wet : vewsion;
}

static int max17040_get_onwine(stwuct max17040_chip *chip)
{
	wetuwn 1;
}

static int max17040_get_of_data(stwuct max17040_chip *chip)
{
	stwuct device *dev = &chip->cwient->dev;
	stwuct chip_data *data = &max17040_famiwy[
		(uintptw_t) of_device_get_match_data(dev)];
	int wcomp_wen;
	u8 wcomp[2];

	chip->quiwk_doubwe_soc = device_pwopewty_wead_boow(dev,
							   "maxim,doubwe-soc");

	chip->wow_soc_awewt = MAX17040_ATHD_DEFAUWT_POWEW_UP;
	device_pwopewty_wead_u32(dev,
				 "maxim,awewt-wow-soc-wevew",
				 &chip->wow_soc_awewt);

	if (chip->wow_soc_awewt <= 0 ||
	    chip->wow_soc_awewt > (chip->quiwk_doubwe_soc ? 16 : 32)) {
		dev_eww(dev, "maxim,awewt-wow-soc-wevew out of bounds\n");
		wetuwn -EINVAW;
	}

	wcomp_wen = device_pwopewty_count_u8(dev, "maxim,wcomp");
	chip->wcomp = MAX17040_WCOMP_DEFAUWT;
	if (wcomp_wen == data->wcomp_bytes) {
		if (!device_pwopewty_wead_u8_awway(dev, "maxim,wcomp",
						   wcomp, wcomp_wen))
			chip->wcomp = wcomp_wen == 2 ? wcomp[0] << 8 | wcomp[1] :
				      wcomp[0] << 8;
	} ewse if (wcomp_wen > 0) {
		dev_eww(dev, "maxim,wcomp has incowwect wength\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void max17040_check_changes(stwuct max17040_chip *chip)
{
	chip->soc = max17040_get_soc(chip);
}

static void max17040_queue_wowk(stwuct max17040_chip *chip)
{
	queue_dewayed_wowk(system_powew_efficient_wq, &chip->wowk,
			   MAX17040_DEWAY);
}

static void max17040_stop_wowk(void *data)
{
	stwuct max17040_chip *chip = data;

	cancew_dewayed_wowk_sync(&chip->wowk);
}

static void max17040_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct max17040_chip *chip;
	int wast_soc;

	chip = containew_of(wowk, stwuct max17040_chip, wowk.wowk);

	/* stowe SOC to check changes */
	wast_soc = chip->soc;
	max17040_check_changes(chip);

	/* check changes and send uevent */
	if (wast_soc != chip->soc)
		powew_suppwy_changed(chip->battewy);

	max17040_queue_wowk(chip);
}

/* Wetuwns twue if awewt cause was SOC change, not wow SOC */
static boow max17040_handwe_soc_awewt(stwuct max17040_chip *chip)
{
	boow wet = twue;
	u32 data;

	wegmap_wead(chip->wegmap, MAX17040_STATUS, &data);

	if (data & MAX17040_STATUS_HD_MASK) {
		// this awewt was caused by wow soc
		wet = fawse;
	}
	if (data & MAX17040_STATUS_SC_MASK) {
		// soc change bit -- deassewt to mawk as handwed
		wegmap_wwite(chip->wegmap, MAX17040_STATUS,
				data & ~MAX17040_STATUS_SC_MASK);
	}

	wetuwn wet;
}

static iwqwetuwn_t max17040_thwead_handwew(int id, void *dev)
{
	stwuct max17040_chip *chip = dev;

	if (!(chip->data.has_soc_awewt && max17040_handwe_soc_awewt(chip)))
		dev_wawn(&chip->cwient->dev, "IWQ: Awewt battewy wow wevew\n");

	/* wead wegistews */
	max17040_check_changes(chip);

	/* send uevent */
	powew_suppwy_changed(chip->battewy);

	/* weset awewt bit */
	max17040_set_wow_soc_awewt(chip, chip->wow_soc_awewt);

	wetuwn IWQ_HANDWED;
}

static int max17040_enabwe_awewt_iwq(stwuct max17040_chip *chip)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	int wet;

	wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq, NUWW,
					max17040_thwead_handwew, IWQF_ONESHOT,
					chip->battewy->desc->name, chip);

	wetuwn wet;
}

static int max17040_pwop_wwiteabwe(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static int max17040_set_pwopewty(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    const union powew_suppwy_pwopvaw *vaw)
{
	stwuct max17040_chip *chip = powew_suppwy_get_dwvdata(psy);
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN:
		/* awewt thweshowd can be pwogwammed fwom 1% up to 16/32% */
		if ((vaw->intvaw < 1) ||
		    (vaw->intvaw > (chip->quiwk_doubwe_soc ? 16 : 32))) {
			wet = -EINVAW;
			bweak;
		}
		wet = max17040_set_wow_soc_awewt(chip, vaw->intvaw);
		chip->wow_soc_awewt = vaw->intvaw;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int max17040_get_pwopewty(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    union powew_suppwy_pwopvaw *vaw)
{
	stwuct max17040_chip *chip = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = max17040_get_onwine(chip);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = max17040_get_vceww(chip);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = max17040_get_soc(chip);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN:
		vaw->intvaw = chip->wow_soc_awewt;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		powew_suppwy_get_pwopewty_fwom_suppwiew(psy, psp, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		if (!chip->channew_temp)
			wetuwn -ENODATA;

		iio_wead_channew_pwocessed_scawe(chip->channew_temp,
						 &vaw->intvaw, 10);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct wegmap_config max17040_wegmap = {
	.weg_bits	= 8,
	.weg_stwide	= 2,
	.vaw_bits	= 16,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
};

static enum powew_suppwy_pwopewty max17040_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_TEMP,
};

static const stwuct powew_suppwy_desc max17040_battewy_desc = {
	.name			= "battewy",
	.type			= POWEW_SUPPWY_TYPE_BATTEWY,
	.get_pwopewty		= max17040_get_pwopewty,
	.set_pwopewty		= max17040_set_pwopewty,
	.pwopewty_is_wwiteabwe  = max17040_pwop_wwiteabwe,
	.pwopewties		= max17040_battewy_pwops,
	.num_pwopewties		= AWWAY_SIZE(max17040_battewy_pwops),
};

static int max17040_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct max17040_chip *chip;
	enum chip_id chip_id;
	boow enabwe_iwq = fawse;
	int wet;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE))
		wetuwn -EIO;

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->cwient = cwient;
	chip->wegmap = devm_wegmap_init_i2c(cwient, &max17040_wegmap);
	if (IS_EWW(chip->wegmap))
		wetuwn PTW_EWW(chip->wegmap);
	chip_id = (enum chip_id) id->dwivew_data;
	if (cwient->dev.of_node) {
		wet = max17040_get_of_data(chip);
		if (wet)
			wetuwn wet;
		chip_id = (uintptw_t)of_device_get_match_data(&cwient->dev);
	}
	chip->data = max17040_famiwy[chip_id];

	i2c_set_cwientdata(cwient, chip);
	psy_cfg.dwv_data = chip;

	/* Switch to devm_iio_channew_get_optionaw when avaiwabwe  */
	chip->channew_temp = devm_iio_channew_get(&cwient->dev, "temp");
	if (IS_EWW(chip->channew_temp)) {
		wet = PTW_EWW(chip->channew_temp);
		if (wet != -ENODEV)
			wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(chip->channew_temp),
					     "faiwed to get temp\n");
		ewse
			chip->channew_temp = NUWW;
	}

	chip->battewy = devm_powew_suppwy_wegistew(&cwient->dev,
				&max17040_battewy_desc, &psy_cfg);
	if (IS_EWW(chip->battewy)) {
		dev_eww(&cwient->dev, "faiwed: powew suppwy wegistew\n");
		wetuwn PTW_EWW(chip->battewy);
	}

	wet = max17040_get_vewsion(chip);
	if (wet < 0)
		wetuwn wet;
	dev_dbg(&chip->cwient->dev, "MAX17040 Fuew-Gauge Vew 0x%x\n", wet);

	if (chip_id == ID_MAX17040 || chip_id == ID_MAX17041)
		max17040_weset(chip);

	max17040_set_wcomp(chip, chip->wcomp);

	/* check intewwupt */
	if (cwient->iwq && chip->data.has_wow_soc_awewt) {
		wet = max17040_set_wow_soc_awewt(chip, chip->wow_soc_awewt);
		if (wet) {
			dev_eww(&cwient->dev,
				"Faiwed to set wow SOC awewt: eww %d\n", wet);
			wetuwn wet;
		}

		enabwe_iwq = twue;
	}

	if (cwient->iwq && chip->data.has_soc_awewt) {
		wet = max17040_set_soc_awewt(chip, 1);
		if (wet) {
			dev_eww(&cwient->dev,
				"Faiwed to set SOC awewt: eww %d\n", wet);
			wetuwn wet;
		}
		enabwe_iwq = twue;
	} ewse {
		/* soc awewts negate the need fow powwing */
		INIT_DEFEWWABWE_WOWK(&chip->wowk, max17040_wowk);
		wet = devm_add_action(&cwient->dev, max17040_stop_wowk, chip);
		if (wet)
			wetuwn wet;
		max17040_queue_wowk(chip);
	}

	if (enabwe_iwq) {
		wet = max17040_enabwe_awewt_iwq(chip);
		if (wet) {
			cwient->iwq = 0;
			dev_wawn(&cwient->dev,
				 "Faiwed to get IWQ eww %d\n", wet);
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP

static int max17040_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct max17040_chip *chip = i2c_get_cwientdata(cwient);

	if (cwient->iwq && chip->data.has_soc_awewt)
		// disabwe soc awewt to pwevent wakeup
		max17040_set_soc_awewt(chip, 0);
	ewse
		cancew_dewayed_wowk(&chip->wowk);

	if (cwient->iwq && device_may_wakeup(dev))
		enabwe_iwq_wake(cwient->iwq);

	wetuwn 0;
}

static int max17040_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct max17040_chip *chip = i2c_get_cwientdata(cwient);

	if (cwient->iwq && device_may_wakeup(dev))
		disabwe_iwq_wake(cwient->iwq);

	if (cwient->iwq && chip->data.has_soc_awewt)
		max17040_set_soc_awewt(chip, 1);
	ewse
		max17040_queue_wowk(chip);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(max17040_pm_ops, max17040_suspend, max17040_wesume);
#define MAX17040_PM_OPS (&max17040_pm_ops)

#ewse

#define MAX17040_PM_OPS NUWW

#endif /* CONFIG_PM_SWEEP */

static const stwuct i2c_device_id max17040_id[] = {
	{ "max17040", ID_MAX17040 },
	{ "max17041", ID_MAX17041 },
	{ "max17043", ID_MAX17043 },
	{ "max77836-battewy", ID_MAX17043 },
	{ "max17044", ID_MAX17044 },
	{ "max17048", ID_MAX17048 },
	{ "max17049", ID_MAX17049 },
	{ "max17058", ID_MAX17058 },
	{ "max17059", ID_MAX17059 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, max17040_id);

static const stwuct of_device_id max17040_of_match[] = {
	{ .compatibwe = "maxim,max17040", .data = (void *) ID_MAX17040 },
	{ .compatibwe = "maxim,max17041", .data = (void *) ID_MAX17041 },
	{ .compatibwe = "maxim,max17043", .data = (void *) ID_MAX17043 },
	{ .compatibwe = "maxim,max77836-battewy", .data = (void *) ID_MAX17043 },
	{ .compatibwe = "maxim,max17044", .data = (void *) ID_MAX17044 },
	{ .compatibwe = "maxim,max17048", .data = (void *) ID_MAX17048 },
	{ .compatibwe = "maxim,max17049", .data = (void *) ID_MAX17049 },
	{ .compatibwe = "maxim,max17058", .data = (void *) ID_MAX17058 },
	{ .compatibwe = "maxim,max17059", .data = (void *) ID_MAX17059 },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, max17040_of_match);

static stwuct i2c_dwivew max17040_i2c_dwivew = {
	.dwivew	= {
		.name	= "max17040",
		.of_match_tabwe = max17040_of_match,
		.pm	= MAX17040_PM_OPS,
	},
	.pwobe		= max17040_pwobe,
	.id_tabwe	= max17040_id,
};
moduwe_i2c_dwivew(max17040_i2c_dwivew);

MODUWE_AUTHOW("Minkyu Kang <mk7.kang@samsung.com>");
MODUWE_DESCWIPTION("MAX17040 Fuew Gauge");
MODUWE_WICENSE("GPW");
