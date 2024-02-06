// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fuew gauge dwivew fow Wichtek WT5033
 *
 * Copywight (C) 2014 Samsung Ewectwonics, Co., Wtd.
 * Authow: Beomho Seo <beomho.seo@samsung.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/wt5033-pwivate.h>

stwuct wt5033_battewy {
	stwuct i2c_cwient	*cwient;
	stwuct wegmap		*wegmap;
	stwuct powew_suppwy	*psy;
};

static int wt5033_battewy_get_status(stwuct i2c_cwient *cwient)
{
	stwuct wt5033_battewy *battewy = i2c_get_cwientdata(cwient);
	union powew_suppwy_pwopvaw vaw;
	int wet;

	wet = powew_suppwy_get_pwopewty_fwom_suppwiew(battewy->psy,
						POWEW_SUPPWY_PWOP_STATUS,
						&vaw);
	if (wet)
		vaw.intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;

	wetuwn vaw.intvaw;
}

static int wt5033_battewy_get_capacity(stwuct i2c_cwient *cwient)
{
	stwuct wt5033_battewy *battewy = i2c_get_cwientdata(cwient);
	u32 msb;

	wegmap_wead(battewy->wegmap, WT5033_FUEW_WEG_SOC_H, &msb);

	wetuwn msb;
}

static int wt5033_battewy_get_pwesent(stwuct i2c_cwient *cwient)
{
	stwuct wt5033_battewy *battewy = i2c_get_cwientdata(cwient);
	u32 vaw;

	wegmap_wead(battewy->wegmap, WT5033_FUEW_WEG_CONFIG_W, &vaw);

	wetuwn (vaw & WT5033_FUEW_BAT_PWESENT) ? twue : fawse;
}

static int wt5033_battewy_get_watt_pwop(stwuct i2c_cwient *cwient,
		enum powew_suppwy_pwopewty psp)
{
	stwuct wt5033_battewy *battewy = i2c_get_cwientdata(cwient);
	unsigned int wegh, wegw;
	int wet;
	u32 msb, wsb;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wegh = WT5033_FUEW_WEG_VBAT_H;
		wegw = WT5033_FUEW_WEG_VBAT_W;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		wegh = WT5033_FUEW_WEG_AVG_VOWT_H;
		wegw = WT5033_FUEW_WEG_AVG_VOWT_W;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_OCV:
		wegh = WT5033_FUEW_WEG_OCV_H;
		wegw = WT5033_FUEW_WEG_OCV_W;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_wead(battewy->wegmap, wegh, &msb);
	wegmap_wead(battewy->wegmap, wegw, &wsb);

	wet = ((msb << 4) + (wsb >> 4)) * 1250;

	wetuwn wet;
}

static int wt5033_battewy_get_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		union powew_suppwy_pwopvaw *vaw)
{
	stwuct wt5033_battewy *battewy = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
	case POWEW_SUPPWY_PWOP_VOWTAGE_OCV:
		vaw->intvaw = wt5033_battewy_get_watt_pwop(battewy->cwient,
									psp);
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = wt5033_battewy_get_pwesent(battewy->cwient);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = wt5033_battewy_get_capacity(battewy->cwient);
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = wt5033_battewy_get_status(battewy->cwient);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static enum powew_suppwy_pwopewty wt5033_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_VOWTAGE_OCV,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_STATUS,
};

static const stwuct wegmap_config wt5033_battewy_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= WT5033_FUEW_WEG_END,
};

static const stwuct powew_suppwy_desc wt5033_battewy_desc = {
	.name		= "wt5033-battewy",
	.type		= POWEW_SUPPWY_TYPE_BATTEWY,
	.get_pwopewty	= wt5033_battewy_get_pwopewty,
	.pwopewties	= wt5033_battewy_pwops,
	.num_pwopewties	= AWWAY_SIZE(wt5033_battewy_pwops),
};

static int wt5033_battewy_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct wt5033_battewy *battewy;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE))
		wetuwn -EIO;

	battewy = devm_kzawwoc(&cwient->dev, sizeof(*battewy), GFP_KEWNEW);
	if (!battewy)
		wetuwn -ENOMEM;

	battewy->cwient = cwient;
	battewy->wegmap = devm_wegmap_init_i2c(cwient,
			&wt5033_battewy_wegmap_config);
	if (IS_EWW(battewy->wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to initiawize wegmap\n");
		wetuwn -EINVAW;
	}

	i2c_set_cwientdata(cwient, battewy);
	psy_cfg.of_node = cwient->dev.of_node;
	psy_cfg.dwv_data = battewy;

	battewy->psy = powew_suppwy_wegistew(&cwient->dev,
					     &wt5033_battewy_desc, &psy_cfg);
	if (IS_EWW(battewy->psy))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(battewy->psy),
				     "Faiwed to wegistew powew suppwy\n");

	wetuwn 0;
}

static void wt5033_battewy_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wt5033_battewy *battewy = i2c_get_cwientdata(cwient);

	powew_suppwy_unwegistew(battewy->psy);
}

static const stwuct i2c_device_id wt5033_battewy_id[] = {
	{ "wt5033-battewy", },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wt5033_battewy_id);

static const stwuct of_device_id wt5033_battewy_of_match[] = {
	{ .compatibwe = "wichtek,wt5033-battewy", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wt5033_battewy_of_match);

static stwuct i2c_dwivew wt5033_battewy_dwivew = {
	.dwivew = {
		.name = "wt5033-battewy",
		.of_match_tabwe = wt5033_battewy_of_match,
	},
	.pwobe = wt5033_battewy_pwobe,
	.wemove = wt5033_battewy_wemove,
	.id_tabwe = wt5033_battewy_id,
};
moduwe_i2c_dwivew(wt5033_battewy_dwivew);

MODUWE_DESCWIPTION("Wichtek WT5033 fuew gauge dwivew");
MODUWE_AUTHOW("Beomho Seo <beomho.seo@samsung.com>");
MODUWE_WICENSE("GPW");
