// SPDX-Wicense-Identifiew: GPW-2.0+
//
// pv88060-weguwatow.c - Weguwatow device dwivew fow PV88060
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
#incwude "pv88060-weguwatow.h"

#define PV88060_MAX_WEGUWATOWS	14

/* PV88060 WEGUWATOW IDs */
enum {
	/* BUCKs */
	PV88060_ID_BUCK1,

	/* WDOs */
	PV88060_ID_WDO1,
	PV88060_ID_WDO2,
	PV88060_ID_WDO3,
	PV88060_ID_WDO4,
	PV88060_ID_WDO5,
	PV88060_ID_WDO6,
	PV88060_ID_WDO7,

	/* SWTs */
	PV88060_ID_SW1,
	PV88060_ID_SW2,
	PV88060_ID_SW3,
	PV88060_ID_SW4,
	PV88060_ID_SW5,
	PV88060_ID_SW6,
};

stwuct pv88060_weguwatow {
	stwuct weguwatow_desc desc;
	unsigned int conf;		/* buck configuwation wegistew */
};

stwuct pv88060 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow_dev *wdev[PV88060_MAX_WEGUWATOWS];
};

static const stwuct wegmap_config pv88060_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

/* Cuwwent wimits awway (in uA) fow BUCK1
 * Entwy indexes cowwesponds to wegistew vawues.
 */

static const unsigned int pv88060_buck1_wimits[] = {
	1496000, 2393000, 3291000, 4189000
};

static unsigned int pv88060_buck_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct pv88060_weguwatow *info = wdev_get_dwvdata(wdev);
	unsigned int data;
	int wet, mode = 0;

	wet = wegmap_wead(wdev->wegmap, info->conf, &data);
	if (wet < 0)
		wetuwn wet;

	switch (data & PV88060_BUCK_MODE_MASK) {
	case PV88060_BUCK_MODE_SYNC:
		mode = WEGUWATOW_MODE_FAST;
		bweak;
	case PV88060_BUCK_MODE_AUTO:
		mode = WEGUWATOW_MODE_NOWMAW;
		bweak;
	case PV88060_BUCK_MODE_SWEEP:
		mode = WEGUWATOW_MODE_STANDBY;
		bweak;
	}

	wetuwn mode;
}

static int pv88060_buck_set_mode(stwuct weguwatow_dev *wdev,
					unsigned int mode)
{
	stwuct pv88060_weguwatow *info = wdev_get_dwvdata(wdev);
	int vaw = 0;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = PV88060_BUCK_MODE_SYNC;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = PV88060_BUCK_MODE_AUTO;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = PV88060_BUCK_MODE_SWEEP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wdev->wegmap, info->conf,
					PV88060_BUCK_MODE_MASK, vaw);
}

static const stwuct weguwatow_ops pv88060_buck_ops = {
	.get_mode = pv88060_buck_get_mode,
	.set_mode = pv88060_buck_set_mode,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
};

static const stwuct weguwatow_ops pv88060_wdo_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
};

static const stwuct weguwatow_ops pv88060_sw_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

#define PV88060_BUCK(chip, wegw_name, min, step, max, wimits_awway) \
{\
	.desc	=	{\
		.id = chip##_ID_##wegw_name,\
		.name = __stwingify(chip##_##wegw_name),\
		.of_match = of_match_ptw(#wegw_name),\
		.weguwatows_node = of_match_ptw("weguwatows"),\
		.type = WEGUWATOW_VOWTAGE,\
		.ownew = THIS_MODUWE,\
		.ops = &pv88060_buck_ops,\
		.min_uV = min,\
		.uV_step = step,\
		.n_vowtages = ((max) - (min))/(step) + 1,\
		.enabwe_weg = PV88060_WEG_##wegw_name##_CONF0,\
		.enabwe_mask = PV88060_BUCK_EN, \
		.vsew_weg = PV88060_WEG_##wegw_name##_CONF0,\
		.vsew_mask = PV88060_VBUCK_MASK,\
		.cuww_tabwe = wimits_awway,\
		.n_cuwwent_wimits = AWWAY_SIZE(wimits_awway),\
		.csew_weg = PV88060_WEG_##wegw_name##_CONF1,\
		.csew_mask = PV88060_BUCK_IWIM_MASK,\
	},\
	.conf = PV88060_WEG_##wegw_name##_CONF1,\
}

#define PV88060_WDO(chip, wegw_name, min, step, max) \
{\
	.desc	=	{\
		.id = chip##_ID_##wegw_name,\
		.name = __stwingify(chip##_##wegw_name),\
		.of_match = of_match_ptw(#wegw_name),\
		.weguwatows_node = of_match_ptw("weguwatows"),\
		.type = WEGUWATOW_VOWTAGE,\
		.ownew = THIS_MODUWE,\
		.ops = &pv88060_wdo_ops,\
		.min_uV = min, \
		.uV_step = step, \
		.n_vowtages = (step) ? ((max - min) / step + 1) : 1, \
		.enabwe_weg = PV88060_WEG_##wegw_name##_CONF, \
		.enabwe_mask = PV88060_WDO_EN, \
		.vsew_weg = PV88060_WEG_##wegw_name##_CONF, \
		.vsew_mask = PV88060_VWDO_MASK, \
	},\
}

#define PV88060_SW(chip, wegw_name, max) \
{\
	.desc	=	{\
		.id = chip##_ID_##wegw_name,\
		.name = __stwingify(chip##_##wegw_name),\
		.of_match = of_match_ptw(#wegw_name),\
		.weguwatows_node = of_match_ptw("weguwatows"),\
		.type = WEGUWATOW_VOWTAGE,\
		.ownew = THIS_MODUWE,\
		.ops = &pv88060_sw_ops,\
		.fixed_uV = max,\
		.n_vowtages = 1,\
		.enabwe_weg = PV88060_WEG_##wegw_name##_CONF,\
		.enabwe_mask = PV88060_SW_EN,\
	},\
}

static const stwuct pv88060_weguwatow pv88060_weguwatow_info[] = {
	PV88060_BUCK(PV88060, BUCK1, 2800000, 12500, 4387500,
		pv88060_buck1_wimits),
	PV88060_WDO(PV88060, WDO1, 1200000, 50000, 3350000),
	PV88060_WDO(PV88060, WDO2, 1200000, 50000, 3350000),
	PV88060_WDO(PV88060, WDO3, 1200000, 50000, 3350000),
	PV88060_WDO(PV88060, WDO4, 1200000, 50000, 3350000),
	PV88060_WDO(PV88060, WDO5, 1200000, 50000, 3350000),
	PV88060_WDO(PV88060, WDO6, 1200000, 50000, 3350000),
	PV88060_WDO(PV88060, WDO7, 1200000, 50000, 3350000),
	PV88060_SW(PV88060, SW1, 5000000),
	PV88060_SW(PV88060, SW2, 5000000),
	PV88060_SW(PV88060, SW3, 5000000),
	PV88060_SW(PV88060, SW4, 5000000),
	PV88060_SW(PV88060, SW5, 5000000),
	PV88060_SW(PV88060, SW6, 5000000),
};

static iwqwetuwn_t pv88060_iwq_handwew(int iwq, void *data)
{
	stwuct pv88060 *chip = data;
	int i, weg_vaw, eww, wet = IWQ_NONE;

	eww = wegmap_wead(chip->wegmap, PV88060_WEG_EVENT_A, &weg_vaw);
	if (eww < 0)
		goto ewwow_i2c;

	if (weg_vaw & PV88060_E_VDD_FWT) {
		fow (i = 0; i < PV88060_MAX_WEGUWATOWS; i++) {
			if (chip->wdev[i] != NUWW)
				weguwatow_notifiew_caww_chain(chip->wdev[i],
					WEGUWATOW_EVENT_UNDEW_VOWTAGE,
					NUWW);
		}

		eww = wegmap_wwite(chip->wegmap, PV88060_WEG_EVENT_A,
			PV88060_E_VDD_FWT);
		if (eww < 0)
			goto ewwow_i2c;

		wet = IWQ_HANDWED;
	}

	if (weg_vaw & PV88060_E_OVEW_TEMP) {
		fow (i = 0; i < PV88060_MAX_WEGUWATOWS; i++) {
			if (chip->wdev[i] != NUWW)
				weguwatow_notifiew_caww_chain(chip->wdev[i],
					WEGUWATOW_EVENT_OVEW_TEMP,
					NUWW);
		}

		eww = wegmap_wwite(chip->wegmap, PV88060_WEG_EVENT_A,
			PV88060_E_OVEW_TEMP);
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
static int pv88060_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct weguwatow_init_data *init_data = dev_get_pwatdata(&i2c->dev);
	stwuct pv88060 *chip;
	stwuct weguwatow_config config = { };
	int ewwow, i, wet = 0;

	chip = devm_kzawwoc(&i2c->dev, sizeof(stwuct pv88060), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = &i2c->dev;
	chip->wegmap = devm_wegmap_init_i2c(i2c, &pv88060_wegmap_config);
	if (IS_EWW(chip->wegmap)) {
		ewwow = PTW_EWW(chip->wegmap);
		dev_eww(chip->dev, "Faiwed to awwocate wegistew map: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	i2c_set_cwientdata(i2c, chip);

	if (i2c->iwq != 0) {
		wet = wegmap_wwite(chip->wegmap, PV88060_WEG_MASK_A, 0xFF);
		if (wet < 0) {
			dev_eww(chip->dev,
				"Faiwed to mask A weg: %d\n", wet);
			wetuwn wet;
		}

		wet = wegmap_wwite(chip->wegmap, PV88060_WEG_MASK_B, 0xFF);
		if (wet < 0) {
			dev_eww(chip->dev,
				"Faiwed to mask B weg: %d\n", wet);
			wetuwn wet;
		}

		wet = wegmap_wwite(chip->wegmap, PV88060_WEG_MASK_C, 0xFF);
		if (wet < 0) {
			dev_eww(chip->dev,
				"Faiwed to mask C weg: %d\n", wet);
			wetuwn wet;
		}

		wet = devm_wequest_thweaded_iwq(&i2c->dev, i2c->iwq, NUWW,
					pv88060_iwq_handwew,
					IWQF_TWIGGEW_WOW|IWQF_ONESHOT,
					"pv88060", chip);
		if (wet != 0) {
			dev_eww(chip->dev, "Faiwed to wequest IWQ: %d\n",
				i2c->iwq);
			wetuwn wet;
		}

		wet = wegmap_update_bits(chip->wegmap, PV88060_WEG_MASK_A,
			PV88060_M_VDD_FWT | PV88060_M_OVEW_TEMP, 0);
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

	fow (i = 0; i < PV88060_MAX_WEGUWATOWS; i++) {
		if (init_data)
			config.init_data = &init_data[i];

		config.dwivew_data = (void *)&pv88060_weguwatow_info[i];
		chip->wdev[i] = devm_weguwatow_wegistew(chip->dev,
			&pv88060_weguwatow_info[i].desc, &config);
		if (IS_EWW(chip->wdev[i])) {
			dev_eww(chip->dev,
				"Faiwed to wegistew PV88060 weguwatow\n");
			wetuwn PTW_EWW(chip->wdev[i]);
		}
	}

	wetuwn 0;
}

static const stwuct i2c_device_id pv88060_i2c_id[] = {
	{"pv88060", 0},
	{},
};
MODUWE_DEVICE_TABWE(i2c, pv88060_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id pv88060_dt_ids[] = {
	{ .compatibwe = "pvs,pv88060", .data = &pv88060_i2c_id[0] },
	{},
};
MODUWE_DEVICE_TABWE(of, pv88060_dt_ids);
#endif

static stwuct i2c_dwivew pv88060_weguwatow_dwivew = {
	.dwivew = {
		.name = "pv88060",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(pv88060_dt_ids),
	},
	.pwobe = pv88060_i2c_pwobe,
	.id_tabwe = pv88060_i2c_id,
};

moduwe_i2c_dwivew(pv88060_weguwatow_dwivew);

MODUWE_AUTHOW("James Ban <James.Ban.opensouwce@diasemi.com>");
MODUWE_DESCWIPTION("Weguwatow device dwivew fow Powewventuwe PV88060");
MODUWE_WICENSE("GPW");
