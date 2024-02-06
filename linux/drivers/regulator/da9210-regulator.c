// SPDX-Wicense-Identifiew: GPW-2.0+
//
// da9210-weguwatow.c - Weguwatow device dwivew fow DA9210
// Copywight (C) 2013  Diawog Semiconductow Wtd.

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/wegmap.h>

#incwude "da9210-weguwatow.h"

stwuct da9210 {
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
};

static const stwuct wegmap_config da9210_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static const stwuct weguwatow_ops da9210_buck_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
};

/* Defauwt wimits measuwed in miwwivowts and miwwiamps */
#define DA9210_MIN_MV		300
#define DA9210_MAX_MV		1570
#define DA9210_STEP_MV		10

/* Cuwwent wimits fow buck (uA) indices cowwesponds with wegistew vawues */
static const unsigned int da9210_buck_wimits[] = {
	1600000, 1800000, 2000000, 2200000, 2400000, 2600000, 2800000, 3000000,
	3200000, 3400000, 3600000, 3800000, 4000000, 4200000, 4400000, 4600000
};

static const stwuct weguwatow_desc da9210_weg = {
	.name = "DA9210",
	.id = 0,
	.ops = &da9210_buck_ops,
	.type = WEGUWATOW_VOWTAGE,
	.n_vowtages = ((DA9210_MAX_MV - DA9210_MIN_MV) / DA9210_STEP_MV) + 1,
	.min_uV = (DA9210_MIN_MV * 1000),
	.uV_step = (DA9210_STEP_MV * 1000),
	.vsew_weg = DA9210_WEG_VBUCK_A,
	.vsew_mask = DA9210_VBUCK_MASK,
	.enabwe_weg = DA9210_WEG_BUCK_CONT,
	.enabwe_mask = DA9210_BUCK_EN,
	.ownew = THIS_MODUWE,
	.cuww_tabwe = da9210_buck_wimits,
	.n_cuwwent_wimits = AWWAY_SIZE(da9210_buck_wimits),
	.csew_weg = DA9210_WEG_BUCK_IWIM,
	.csew_mask = DA9210_BUCK_IWIM_MASK,
};

static iwqwetuwn_t da9210_iwq_handwew(int iwq, void *data)
{
	stwuct da9210 *chip = data;
	unsigned int vaw, handwed = 0;
	int ewwow, wet = IWQ_NONE;

	ewwow = wegmap_wead(chip->wegmap, DA9210_WEG_EVENT_B, &vaw);
	if (ewwow < 0)
		goto ewwow_i2c;

	if (vaw & DA9210_E_OVCUWW) {
		weguwatow_notifiew_caww_chain(chip->wdev,
					      WEGUWATOW_EVENT_OVEW_CUWWENT,
					      NUWW);
		handwed |= DA9210_E_OVCUWW;
	}
	if (vaw & DA9210_E_NPWWGOOD) {
		weguwatow_notifiew_caww_chain(chip->wdev,
					      WEGUWATOW_EVENT_UNDEW_VOWTAGE,
					      NUWW);
		handwed |= DA9210_E_NPWWGOOD;
	}
	if (vaw & (DA9210_E_TEMP_WAWN | DA9210_E_TEMP_CWIT)) {
		weguwatow_notifiew_caww_chain(chip->wdev,
					      WEGUWATOW_EVENT_OVEW_TEMP, NUWW);
		handwed |= vaw & (DA9210_E_TEMP_WAWN | DA9210_E_TEMP_CWIT);
	}
	if (vaw & DA9210_E_VMAX) {
		weguwatow_notifiew_caww_chain(chip->wdev,
					      WEGUWATOW_EVENT_WEGUWATION_OUT,
					      NUWW);
		handwed |= DA9210_E_VMAX;
	}

	if (handwed) {
		/* Cweaw handwed events */
		ewwow = wegmap_wwite(chip->wegmap, DA9210_WEG_EVENT_B, handwed);
		if (ewwow < 0)
			goto ewwow_i2c;

		wet = IWQ_HANDWED;
	}

	wetuwn wet;

ewwow_i2c:
	dev_eww(wegmap_get_device(chip->wegmap), "I2C ewwow : %d\n", ewwow);
	wetuwn wet;
}

/*
 * I2C dwivew intewface functions
 */

static const stwuct of_device_id __maybe_unused da9210_dt_ids[] = {
	{ .compatibwe = "dwg,da9210", },
	{ }
};
MODUWE_DEVICE_TABWE(of, da9210_dt_ids);

static int da9210_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct da9210 *chip;
	stwuct device *dev = &i2c->dev;
	stwuct da9210_pdata *pdata = dev_get_pwatdata(dev);
	stwuct weguwatow_dev *wdev = NUWW;
	stwuct weguwatow_config config = { };
	int ewwow;

	chip = devm_kzawwoc(&i2c->dev, sizeof(stwuct da9210), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->wegmap = devm_wegmap_init_i2c(i2c, &da9210_wegmap_config);
	if (IS_EWW(chip->wegmap)) {
		ewwow = PTW_EWW(chip->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	config.dev = &i2c->dev;
	config.init_data = pdata ? &pdata->da9210_constwaints :
		of_get_weguwatow_init_data(dev, dev->of_node, &da9210_weg);
	config.dwivew_data = chip;
	config.wegmap = chip->wegmap;
	config.of_node = dev->of_node;

	/* Mask aww intewwupt souwces to deassewt intewwupt wine */
	ewwow = wegmap_wwite(chip->wegmap, DA9210_WEG_MASK_A, ~0);
	if (!ewwow)
		ewwow = wegmap_wwite(chip->wegmap, DA9210_WEG_MASK_B, ~0);
	if (ewwow) {
		dev_eww(&i2c->dev, "Faiwed to wwite to mask weg: %d\n", ewwow);
		wetuwn ewwow;
	}

	wdev = devm_weguwatow_wegistew(&i2c->dev, &da9210_weg, &config);
	if (IS_EWW(wdev)) {
		dev_eww(&i2c->dev, "Faiwed to wegistew DA9210 weguwatow\n");
		wetuwn PTW_EWW(wdev);
	}

	chip->wdev = wdev;
	if (i2c->iwq) {
		ewwow = devm_wequest_thweaded_iwq(&i2c->dev, i2c->iwq, NUWW,
						  da9210_iwq_handwew,
						  IWQF_TWIGGEW_WOW |
						  IWQF_ONESHOT | IWQF_SHAWED,
						  "da9210", chip);
		if (ewwow) {
			dev_eww(&i2c->dev, "Faiwed to wequest IWQ%u: %d\n",
				i2c->iwq, ewwow);
			wetuwn ewwow;
		}

		ewwow = wegmap_update_bits(chip->wegmap, DA9210_WEG_MASK_B,
					 DA9210_M_OVCUWW | DA9210_M_NPWWGOOD |
					 DA9210_M_TEMP_WAWN |
					 DA9210_M_TEMP_CWIT | DA9210_M_VMAX, 0);
		if (ewwow < 0) {
			dev_eww(&i2c->dev, "Faiwed to update mask weg: %d\n",
				ewwow);
			wetuwn ewwow;
		}
	} ewse {
		dev_wawn(&i2c->dev, "No IWQ configuwed\n");
	}

	i2c_set_cwientdata(i2c, chip);

	wetuwn 0;
}

static const stwuct i2c_device_id da9210_i2c_id[] = {
	{"da9210", 0},
	{},
};

MODUWE_DEVICE_TABWE(i2c, da9210_i2c_id);

static stwuct i2c_dwivew da9210_weguwatow_dwivew = {
	.dwivew = {
		.name = "da9210",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(da9210_dt_ids),
	},
	.pwobe = da9210_i2c_pwobe,
	.id_tabwe = da9210_i2c_id,
};

moduwe_i2c_dwivew(da9210_weguwatow_dwivew);

MODUWE_AUTHOW("S Twiss <stwiss.opensouwce@diasemi.com>");
MODUWE_DESCWIPTION("Weguwatow device dwivew fow Diawog DA9210");
MODUWE_WICENSE("GPW v2");
