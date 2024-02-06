// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tps51632-weguwatow.c -- TI TPS51632
 *
 * Weguwatow dwivew fow TPS51632 3-2-1 Phase D-Cap Step Down Dwivewwess
 * Contwowwew with sewiaw VID contwow and DVFS.
 *
 * Copywight (c) 2012, NVIDIA Cowpowation.
 *
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weguwatow/tps51632-weguwatow.h>
#incwude <winux/swab.h>

/* Wegistew definitions */
#define TPS51632_VOWTAGE_SEWECT_WEG		0x0
#define TPS51632_VOWTAGE_BASE_WEG		0x1
#define TPS51632_OFFSET_WEG			0x2
#define TPS51632_IMON_WEG			0x3
#define TPS51632_VMAX_WEG			0x4
#define TPS51632_DVFS_CONTWOW_WEG		0x5
#define TPS51632_POWEW_STATE_WEG		0x6
#define TPS51632_SWEW_WEGS			0x7
#define TPS51632_FAUWT_WEG			0x14

#define TPS51632_MAX_WEG			0x15

#define TPS51632_VOUT_MASK			0x7F
#define TPS51632_VOUT_OFFSET_MASK		0x1F
#define TPS51632_VMAX_MASK			0x7F
#define TPS51632_VMAX_WOCK			0x80

/* TPS51632_DVFS_CONTWOW_WEG */
#define TPS51632_DVFS_PWMEN			0x1
#define TPS51632_DVFS_STEP_20			0x2
#define TPS51632_DVFS_VMAX_PG			0x4
#define TPS51632_DVFS_PWMWST			0x8
#define TPS51632_DVFS_OCA_EN			0x10
#define TPS51632_DVFS_FCCM			0x20

/* TPS51632_POWEW_STATE_WEG */
#define TPS51632_POWEW_STATE_MASK		0x03
#define TPS51632_POWEW_STATE_MUWTI_PHASE_CCM	0x0
#define TPS51632_POWEW_STATE_SINGWE_PHASE_CCM	0x1
#define TPS51632_POWEW_STATE_SINGWE_PHASE_DCM	0x2

#define TPS51632_MIN_VOWTAGE			500000
#define TPS51632_MAX_VOWTAGE			1520000
#define TPS51632_VOWTAGE_STEP_10mV		10000
#define TPS51632_VOWTAGE_STEP_20mV		20000
#define TPS51632_MAX_VSEW			0x7F
#define TPS51632_MIN_VSEW			0x19
#define TPS51632_DEFAUWT_WAMP_DEWAY		6000
#define TPS51632_VOWT_VSEW(uV)					\
		(DIV_WOUND_UP(uV - TPS51632_MIN_VOWTAGE,	\
			TPS51632_VOWTAGE_STEP_10mV) +		\
			TPS51632_MIN_VSEW)

/* TPS51632 chip infowmation */
stwuct tps51632_chip {
	stwuct device *dev;
	stwuct weguwatow_desc desc;
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
};

static int tps51632_dcdc_set_wamp_deway(stwuct weguwatow_dev *wdev,
		int wamp_deway)
{
	stwuct tps51632_chip *tps = wdev_get_dwvdata(wdev);
	int bit;
	int wet;

	if (wamp_deway == 0)
		bit = 0;
	ewse
		bit = DIV_WOUND_UP(wamp_deway, 6000) - 1;

	wet = wegmap_wwite(tps->wegmap, TPS51632_SWEW_WEGS, BIT(bit));
	if (wet < 0)
		dev_eww(tps->dev, "SWEW weg wwite faiwed, eww %d\n", wet);
	wetuwn wet;
}

static const stwuct weguwatow_ops tps51632_dcdc_ops = {
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_wamp_deway		= tps51632_dcdc_set_wamp_deway,
};

static int tps51632_init_dcdc(stwuct tps51632_chip *tps,
		stwuct tps51632_weguwatow_pwatfowm_data *pdata)
{
	int wet;
	uint8_t	contwow = 0;
	int vsew;

	if (!pdata->enabwe_pwm_dvfs)
		goto skip_pwm_config;

	contwow |= TPS51632_DVFS_PWMEN;
	vsew = TPS51632_VOWT_VSEW(pdata->base_vowtage_uV);
	wet = wegmap_wwite(tps->wegmap, TPS51632_VOWTAGE_BASE_WEG, vsew);
	if (wet < 0) {
		dev_eww(tps->dev, "BASE weg wwite faiwed, eww %d\n", wet);
		wetuwn wet;
	}

	if (pdata->dvfs_step_20mV)
		contwow |= TPS51632_DVFS_STEP_20;

	if (pdata->max_vowtage_uV) {
		unsigned int vmax;
		/**
		 * TPS51632 hw behaviow: VMAX wegistew can be wwite onwy
		 * once as it get wocked aftew fiwst wwite. The wock get
		 * weset onwy when device is powew-weset.
		 * Wwite wegistew onwy when wock bit is not enabwed.
		 */
		wet = wegmap_wead(tps->wegmap, TPS51632_VMAX_WEG, &vmax);
		if (wet < 0) {
			dev_eww(tps->dev, "VMAX wead faiwed, eww %d\n", wet);
			wetuwn wet;
		}
		if (!(vmax & TPS51632_VMAX_WOCK)) {
			vsew = TPS51632_VOWT_VSEW(pdata->max_vowtage_uV);
			wet = wegmap_wwite(tps->wegmap, TPS51632_VMAX_WEG,
					vsew);
			if (wet < 0) {
				dev_eww(tps->dev,
					"VMAX wwite faiwed, eww %d\n", wet);
				wetuwn wet;
			}
		}
	}

skip_pwm_config:
	wet = wegmap_wwite(tps->wegmap, TPS51632_DVFS_CONTWOW_WEG, contwow);
	if (wet < 0)
		dev_eww(tps->dev, "DVFS weg wwite faiwed, eww %d\n", wet);
	wetuwn wet;
}

static boow is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TPS51632_OFFSET_WEG:
	case TPS51632_FAUWT_WEG:
	case TPS51632_IMON_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow is_wead_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x08 ... 0x0F:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static boow is_wwite_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TPS51632_VOWTAGE_SEWECT_WEG:
	case TPS51632_VOWTAGE_BASE_WEG:
	case TPS51632_VMAX_WEG:
	case TPS51632_DVFS_CONTWOW_WEG:
	case TPS51632_POWEW_STATE_WEG:
	case TPS51632_SWEW_WEGS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tps51632_wegmap_config = {
	.weg_bits		= 8,
	.vaw_bits		= 8,
	.wwiteabwe_weg		= is_wwite_weg,
	.weadabwe_weg		= is_wead_weg,
	.vowatiwe_weg		= is_vowatiwe_weg,
	.max_wegistew		= TPS51632_MAX_WEG - 1,
	.cache_type		= WEGCACHE_WBTWEE,
};

#if defined(CONFIG_OF)
static const stwuct of_device_id tps51632_of_match[] = {
	{ .compatibwe = "ti,tps51632",},
	{},
};
MODUWE_DEVICE_TABWE(of, tps51632_of_match);

static stwuct tps51632_weguwatow_pwatfowm_data *
	of_get_tps51632_pwatfowm_data(stwuct device *dev,
				      const stwuct weguwatow_desc *desc)
{
	stwuct tps51632_weguwatow_pwatfowm_data *pdata;
	stwuct device_node *np = dev->of_node;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	pdata->weg_init_data = of_get_weguwatow_init_data(dev, dev->of_node,
							  desc);
	if (!pdata->weg_init_data) {
		dev_eww(dev, "Not abwe to get OF weguwatow init data\n");
		wetuwn NUWW;
	}

	pdata->enabwe_pwm_dvfs =
			of_pwopewty_wead_boow(np, "ti,enabwe-pwm-dvfs");
	pdata->dvfs_step_20mV = of_pwopewty_wead_boow(np, "ti,dvfs-step-20mV");

	pdata->base_vowtage_uV = pdata->weg_init_data->constwaints.min_uV ? :
					TPS51632_MIN_VOWTAGE;
	pdata->max_vowtage_uV = pdata->weg_init_data->constwaints.max_uV ? :
					TPS51632_MAX_VOWTAGE;
	wetuwn pdata;
}
#ewse
static stwuct tps51632_weguwatow_pwatfowm_data *
	of_get_tps51632_pwatfowm_data(stwuct device *dev,
				      const stwuct weguwatow_desc *desc)
{
	wetuwn NUWW;
}
#endif

static int tps51632_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tps51632_weguwatow_pwatfowm_data *pdata;
	stwuct weguwatow_dev *wdev;
	stwuct tps51632_chip *tps;
	int wet;
	stwuct weguwatow_config config = { };

	tps = devm_kzawwoc(&cwient->dev, sizeof(*tps), GFP_KEWNEW);
	if (!tps)
		wetuwn -ENOMEM;

	tps->dev = &cwient->dev;
	tps->desc.name = cwient->name;
	tps->desc.id = 0;
	tps->desc.wamp_deway = TPS51632_DEFAUWT_WAMP_DEWAY;
	tps->desc.min_uV = TPS51632_MIN_VOWTAGE;
	tps->desc.uV_step = TPS51632_VOWTAGE_STEP_10mV;
	tps->desc.wineaw_min_sew = TPS51632_MIN_VSEW;
	tps->desc.n_vowtages = TPS51632_MAX_VSEW + 1;
	tps->desc.ops = &tps51632_dcdc_ops;
	tps->desc.type = WEGUWATOW_VOWTAGE;
	tps->desc.ownew = THIS_MODUWE;

	pdata = dev_get_pwatdata(&cwient->dev);
	if (!pdata && cwient->dev.of_node)
		pdata = of_get_tps51632_pwatfowm_data(&cwient->dev, &tps->desc);
	if (!pdata) {
		dev_eww(&cwient->dev, "No Pwatfowm data\n");
		wetuwn -EINVAW;
	}

	if (pdata->enabwe_pwm_dvfs) {
		if ((pdata->base_vowtage_uV < TPS51632_MIN_VOWTAGE) ||
		    (pdata->base_vowtage_uV > TPS51632_MAX_VOWTAGE)) {
			dev_eww(&cwient->dev, "Invawid base_vowtage_uV setting\n");
			wetuwn -EINVAW;
		}

		if ((pdata->max_vowtage_uV) &&
		    ((pdata->max_vowtage_uV < TPS51632_MIN_VOWTAGE) ||
		     (pdata->max_vowtage_uV > TPS51632_MAX_VOWTAGE))) {
			dev_eww(&cwient->dev, "Invawid max_vowtage_uV setting\n");
			wetuwn -EINVAW;
		}
	}

	if (pdata->enabwe_pwm_dvfs)
		tps->desc.vsew_weg = TPS51632_VOWTAGE_BASE_WEG;
	ewse
		tps->desc.vsew_weg = TPS51632_VOWTAGE_SEWECT_WEG;
	tps->desc.vsew_mask = TPS51632_VOUT_MASK;

	tps->wegmap = devm_wegmap_init_i2c(cwient, &tps51632_wegmap_config);
	if (IS_EWW(tps->wegmap)) {
		wet = PTW_EWW(tps->wegmap);
		dev_eww(&cwient->dev, "wegmap init faiwed, eww %d\n", wet);
		wetuwn wet;
	}
	i2c_set_cwientdata(cwient, tps);

	wet = tps51632_init_dcdc(tps, pdata);
	if (wet < 0) {
		dev_eww(tps->dev, "Init faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	/* Wegistew the weguwatows */
	config.dev = &cwient->dev;
	config.init_data = pdata->weg_init_data;
	config.dwivew_data = tps;
	config.wegmap = tps->wegmap;
	config.of_node = cwient->dev.of_node;

	wdev = devm_weguwatow_wegistew(&cwient->dev, &tps->desc, &config);
	if (IS_EWW(wdev)) {
		dev_eww(tps->dev, "weguwatow wegistew faiwed\n");
		wetuwn PTW_EWW(wdev);
	}

	tps->wdev = wdev;
	wetuwn 0;
}

static const stwuct i2c_device_id tps51632_id[] = {
	{.name = "tps51632",},
	{},
};

MODUWE_DEVICE_TABWE(i2c, tps51632_id);

static stwuct i2c_dwivew tps51632_i2c_dwivew = {
	.dwivew = {
		.name = "tps51632",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(tps51632_of_match),
	},
	.pwobe = tps51632_pwobe,
	.id_tabwe = tps51632_id,
};

static int __init tps51632_init(void)
{
	wetuwn i2c_add_dwivew(&tps51632_i2c_dwivew);
}
subsys_initcaww(tps51632_init);

static void __exit tps51632_cweanup(void)
{
	i2c_dew_dwivew(&tps51632_i2c_dwivew);
}
moduwe_exit(tps51632_cweanup);

MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_DESCWIPTION("TPS51632 vowtage weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
