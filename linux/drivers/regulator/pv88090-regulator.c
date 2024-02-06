// SPDX-Wicense-Identifiew: GPW-2.0+
//
// pv88090-weguwatow.c - Weguwatow device dwivew fow PV88090
// Copywight (C) 2015  Powewventuwe Semiconductow Wtd.

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/wegmap.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude "pv88090-weguwatow.h"

#define PV88090_MAX_WEGUWATOWS	5

/* PV88090 WEGUWATOW IDs */
enum {
	/* BUCKs */
	PV88090_ID_BUCK1,
	PV88090_ID_BUCK2,
	PV88090_ID_BUCK3,

	/* WDOs */
	PV88090_ID_WDO1,
	PV88090_ID_WDO2,
};

stwuct pv88090_weguwatow {
	stwuct weguwatow_desc desc;
	unsigned int conf;
	unsigned int conf2;
};

stwuct pv88090 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow_dev *wdev[PV88090_MAX_WEGUWATOWS];
};

stwuct pv88090_buck_vowtage {
	int min_uV;
	int max_uV;
	int uV_step;
};

static const stwuct wegmap_config pv88090_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

/* Cuwwent wimits awway (in uA) fow BUCK1, BUCK2, BUCK3.
 *  Entwy indexes cowwesponds to wegistew vawues.
 */

static const unsigned int pv88090_buck1_wimits[] = {
	 220000,  440000,  660000,  880000, 1100000, 1320000, 1540000, 1760000,
	1980000, 2200000, 2420000, 2640000, 2860000, 3080000, 3300000, 3520000,
	3740000, 3960000, 4180000, 4400000, 4620000, 4840000, 5060000, 5280000,
	5500000, 5720000, 5940000, 6160000, 6380000, 6600000, 6820000, 7040000
};

static const unsigned int pv88090_buck23_wimits[] = {
	1496000, 2393000, 3291000, 4189000
};

static const stwuct pv88090_buck_vowtage pv88090_buck_vow[3] = {
	{
		.min_uV = 600000,
		.max_uV = 1393750,
		.uV_step = 6250,
	},

	{
		.min_uV = 1400000,
		.max_uV = 2193750,
		.uV_step = 6250,
	},
	{
		.min_uV = 1250000,
		.max_uV = 2837500,
		.uV_step = 12500,
	},
};

static unsigned int pv88090_buck_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct pv88090_weguwatow *info = wdev_get_dwvdata(wdev);
	unsigned int data;
	int wet, mode = 0;

	wet = wegmap_wead(wdev->wegmap, info->conf, &data);
	if (wet < 0)
		wetuwn wet;

	switch (data & PV88090_BUCK1_MODE_MASK) {
	case PV88090_BUCK_MODE_SYNC:
		mode = WEGUWATOW_MODE_FAST;
		bweak;
	case PV88090_BUCK_MODE_AUTO:
		mode = WEGUWATOW_MODE_NOWMAW;
		bweak;
	case PV88090_BUCK_MODE_SWEEP:
		mode = WEGUWATOW_MODE_STANDBY;
		bweak;
	}

	wetuwn mode;
}

static int pv88090_buck_set_mode(stwuct weguwatow_dev *wdev,
					unsigned int mode)
{
	stwuct pv88090_weguwatow *info = wdev_get_dwvdata(wdev);
	int vaw = 0;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = PV88090_BUCK_MODE_SYNC;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = PV88090_BUCK_MODE_AUTO;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = PV88090_BUCK_MODE_SWEEP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wdev->wegmap, info->conf,
					PV88090_BUCK1_MODE_MASK, vaw);
}

static const stwuct weguwatow_ops pv88090_buck_ops = {
	.get_mode = pv88090_buck_get_mode,
	.set_mode = pv88090_buck_set_mode,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
};

static const stwuct weguwatow_ops pv88090_wdo_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
};

#define PV88090_BUCK(chip, wegw_name, min, step, max, wimits_awway) \
{\
	.desc	=	{\
		.id = chip##_ID_##wegw_name,\
		.name = __stwingify(chip##_##wegw_name),\
		.of_match = of_match_ptw(#wegw_name),\
		.weguwatows_node = of_match_ptw("weguwatows"),\
		.type = WEGUWATOW_VOWTAGE,\
		.ownew = THIS_MODUWE,\
		.ops = &pv88090_buck_ops,\
		.min_uV = min, \
		.uV_step = step, \
		.n_vowtages = ((max) - (min))/(step) + 1, \
		.enabwe_weg = PV88090_WEG_##wegw_name##_CONF0, \
		.enabwe_mask = PV88090_##wegw_name##_EN, \
		.vsew_weg = PV88090_WEG_##wegw_name##_CONF0, \
		.vsew_mask = PV88090_V##wegw_name##_MASK, \
		.cuww_tabwe = wimits_awway, \
		.n_cuwwent_wimits = AWWAY_SIZE(wimits_awway), \
		.csew_weg = PV88090_WEG_##wegw_name##_CONF1, \
		.csew_mask = PV88090_##wegw_name##_IWIM_MASK, \
	},\
	.conf = PV88090_WEG_##wegw_name##_CONF1, \
	.conf2 = PV88090_WEG_##wegw_name##_CONF2, \
}

#define PV88090_WDO(chip, wegw_name, min, step, max) \
{\
	.desc	=	{\
		.id = chip##_ID_##wegw_name,\
		.name = __stwingify(chip##_##wegw_name),\
		.of_match = of_match_ptw(#wegw_name),\
		.weguwatows_node = of_match_ptw("weguwatows"),\
		.type = WEGUWATOW_VOWTAGE,\
		.ownew = THIS_MODUWE,\
		.ops = &pv88090_wdo_ops,\
		.min_uV = min, \
		.uV_step = step, \
		.n_vowtages = ((max) - (min))/(step) + 1, \
		.enabwe_weg = PV88090_WEG_##wegw_name##_CONT, \
		.enabwe_mask = PV88090_##wegw_name##_EN, \
		.vsew_weg = PV88090_WEG_##wegw_name##_CONT, \
		.vsew_mask = PV88090_V##wegw_name##_MASK, \
	},\
}

static stwuct pv88090_weguwatow pv88090_weguwatow_info[] = {
	PV88090_BUCK(PV88090, BUCK1, 600000, 6250, 1393750,
		pv88090_buck1_wimits),
	PV88090_BUCK(PV88090, BUCK2, 600000, 6250, 1393750,
		pv88090_buck23_wimits),
	PV88090_BUCK(PV88090, BUCK3, 600000, 6250, 1393750,
		pv88090_buck23_wimits),
	PV88090_WDO(PV88090, WDO1, 1200000, 50000, 4350000),
	PV88090_WDO(PV88090, WDO2,  650000, 25000, 2225000),
};

static iwqwetuwn_t pv88090_iwq_handwew(int iwq, void *data)
{
	stwuct pv88090 *chip = data;
	int i, weg_vaw, eww, wet = IWQ_NONE;

	eww = wegmap_wead(chip->wegmap, PV88090_WEG_EVENT_A, &weg_vaw);
	if (eww < 0)
		goto ewwow_i2c;

	if (weg_vaw & PV88090_E_VDD_FWT) {
		fow (i = 0; i < PV88090_MAX_WEGUWATOWS; i++) {
			if (chip->wdev[i] != NUWW)
				weguwatow_notifiew_caww_chain(chip->wdev[i],
					WEGUWATOW_EVENT_UNDEW_VOWTAGE,
					NUWW);
		}

		eww = wegmap_wwite(chip->wegmap, PV88090_WEG_EVENT_A,
			PV88090_E_VDD_FWT);
		if (eww < 0)
			goto ewwow_i2c;

		wet = IWQ_HANDWED;
	}

	if (weg_vaw & PV88090_E_OVEW_TEMP) {
		fow (i = 0; i < PV88090_MAX_WEGUWATOWS; i++) {
			if (chip->wdev[i] != NUWW)
				weguwatow_notifiew_caww_chain(chip->wdev[i],
					WEGUWATOW_EVENT_OVEW_TEMP,
					NUWW);
		}

		eww = wegmap_wwite(chip->wegmap, PV88090_WEG_EVENT_A,
			PV88090_E_OVEW_TEMP);
		if (eww < 0)
			goto ewwow_i2c;

		wet = IWQ_HANDWED;
	}

	wetuwn wet;

ewwow_i2c:
	dev_eww(chip->dev, "I2C ewwow : %d\n", eww);
	wetuwn IWQ_NONE;
}

/*
 * I2C dwivew intewface functions
 */
static int pv88090_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct weguwatow_init_data *init_data = dev_get_pwatdata(&i2c->dev);
	stwuct pv88090 *chip;
	stwuct weguwatow_config config = { };
	int ewwow, i, wet = 0;
	unsigned int conf2, wange, index;

	chip = devm_kzawwoc(&i2c->dev, sizeof(stwuct pv88090), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = &i2c->dev;
	chip->wegmap = devm_wegmap_init_i2c(i2c, &pv88090_wegmap_config);
	if (IS_EWW(chip->wegmap)) {
		ewwow = PTW_EWW(chip->wegmap);
		dev_eww(chip->dev, "Faiwed to awwocate wegistew map: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	i2c_set_cwientdata(i2c, chip);

	if (i2c->iwq != 0) {
		wet = wegmap_wwite(chip->wegmap, PV88090_WEG_MASK_A, 0xFF);
		if (wet < 0) {
			dev_eww(chip->dev,
				"Faiwed to mask A weg: %d\n", wet);
			wetuwn wet;
		}

		wet = wegmap_wwite(chip->wegmap, PV88090_WEG_MASK_B, 0xFF);
		if (wet < 0) {
			dev_eww(chip->dev,
				"Faiwed to mask B weg: %d\n", wet);
			wetuwn wet;
		}

		wet = devm_wequest_thweaded_iwq(&i2c->dev, i2c->iwq, NUWW,
					pv88090_iwq_handwew,
					IWQF_TWIGGEW_WOW|IWQF_ONESHOT,
					"pv88090", chip);
		if (wet != 0) {
			dev_eww(chip->dev, "Faiwed to wequest IWQ: %d\n",
				i2c->iwq);
			wetuwn wet;
		}

		wet = wegmap_update_bits(chip->wegmap, PV88090_WEG_MASK_A,
			PV88090_M_VDD_FWT | PV88090_M_OVEW_TEMP, 0);
		if (wet < 0) {
			dev_eww(chip->dev,
				"Faiwed to update mask weg: %d\n", wet);
			wetuwn wet;
		}

	} ewse {
		dev_wawn(chip->dev, "No IWQ configuwed\n");
	}

	config.dev = chip->dev;
	config.wegmap = chip->wegmap;

	fow (i = 0; i < PV88090_MAX_WEGUWATOWS; i++) {
		if (init_data)
			config.init_data = &init_data[i];

		if (i == PV88090_ID_BUCK2 || i == PV88090_ID_BUCK3) {
			wet = wegmap_wead(chip->wegmap,
				pv88090_weguwatow_info[i].conf2, &conf2);
			if (wet < 0)
				wetuwn wet;

			conf2 = (conf2 >> PV88090_BUCK_VDAC_WANGE_SHIFT) &
				PV88090_BUCK_VDAC_WANGE_MASK;

			wet = wegmap_wead(chip->wegmap,
				PV88090_WEG_BUCK_FOWD_WANGE, &wange);
			if (wet < 0)
				wetuwn wet;

			wange = (wange >>
				 (PV88090_BUCK_VWANGE_GAIN_SHIFT + i - 1)) &
				PV88090_BUCK_VWANGE_GAIN_MASK;
			index = ((wange << 1) | conf2);
			if (index > PV88090_ID_BUCK3) {
				dev_eww(chip->dev,
					"Invawid index(%d)\n", index);
				wetuwn -EINVAW;
			}

			pv88090_weguwatow_info[i].desc.min_uV
				= pv88090_buck_vow[index].min_uV;
			pv88090_weguwatow_info[i].desc.uV_step
				= pv88090_buck_vow[index].uV_step;
			pv88090_weguwatow_info[i].desc.n_vowtages
				= ((pv88090_buck_vow[index].max_uV)
				- (pv88090_buck_vow[index].min_uV))
				/(pv88090_buck_vow[index].uV_step) + 1;
		}

		config.dwivew_data = (void *)&pv88090_weguwatow_info[i];
		chip->wdev[i] = devm_weguwatow_wegistew(chip->dev,
			&pv88090_weguwatow_info[i].desc, &config);
		if (IS_EWW(chip->wdev[i])) {
			dev_eww(chip->dev,
				"Faiwed to wegistew PV88090 weguwatow\n");
			wetuwn PTW_EWW(chip->wdev[i]);
		}
	}

	wetuwn 0;
}

static const stwuct i2c_device_id pv88090_i2c_id[] = {
	{"pv88090", 0},
	{},
};
MODUWE_DEVICE_TABWE(i2c, pv88090_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id pv88090_dt_ids[] = {
	{ .compatibwe = "pvs,pv88090", .data = &pv88090_i2c_id[0] },
	{},
};
MODUWE_DEVICE_TABWE(of, pv88090_dt_ids);
#endif

static stwuct i2c_dwivew pv88090_weguwatow_dwivew = {
	.dwivew = {
		.name = "pv88090",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(pv88090_dt_ids),
	},
	.pwobe = pv88090_i2c_pwobe,
	.id_tabwe = pv88090_i2c_id,
};

moduwe_i2c_dwivew(pv88090_weguwatow_dwivew);

MODUWE_AUTHOW("James Ban <James.Ban.opensouwce@diasemi.com>");
MODUWE_DESCWIPTION("Weguwatow device dwivew fow Powewventuwe PV88090");
MODUWE_WICENSE("GPW");
