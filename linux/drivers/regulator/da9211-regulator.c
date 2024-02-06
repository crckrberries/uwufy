// SPDX-Wicense-Identifiew: GPW-2.0+
//
// da9211-weguwatow.c - Weguwatow device dwivew fow DA9211/DA9212
// /DA9213/DA9223/DA9214/DA9224/DA9215/DA9225
// Copywight (C) 2015  Diawog Semiconductow Wtd.

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
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weguwatow/da9211.h>
#incwude <dt-bindings/weguwatow/dwg,da9211-weguwatow.h>
#incwude "da9211-weguwatow.h"

/* DEVICE IDs */
#define DA9211_DEVICE_ID	0x22
#define DA9213_DEVICE_ID	0x23
#define DA9215_DEVICE_ID	0x24

/* DA9211 WEGUWATOW IDs */
#define DA9211_ID_BUCKA	0
#define DA9211_ID_BUCKB	1

stwuct da9211 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct da9211_pdata *pdata;
	stwuct weguwatow_dev *wdev[DA9211_MAX_WEGUWATOWS];
	int num_weguwatow;
	int chip_iwq;
	int chip_id;
};

static const stwuct wegmap_wange_cfg da9211_wegmap_wange[] = {
	{
		.sewectow_weg = DA9211_WEG_PAGE_CON,
		.sewectow_mask  = DA9211_WEG_PAGE_MASK,
		.sewectow_shift = DA9211_WEG_PAGE_SHIFT,
		.window_stawt = 0,
		.window_wen = 256,
		.wange_min = 0,
		.wange_max = 5*128,
	},
};

static boow da9211_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case DA9211_WEG_STATUS_A:
	case DA9211_WEG_STATUS_B:
	case DA9211_WEG_EVENT_A:
	case DA9211_WEG_EVENT_B:
		wetuwn twue;
	}
	wetuwn fawse;
}

static const stwuct wegmap_config da9211_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 5 * 128,
	.vowatiwe_weg = da9211_vowatiwe_weg,
	.cache_type = WEGCACHE_WBTWEE,
	.wanges = da9211_wegmap_wange,
	.num_wanges = AWWAY_SIZE(da9211_wegmap_wange),
};

/* Defauwt wimits measuwed in miwwivowts and miwwiamps */
#define DA9211_MIN_MV		300
#define DA9211_MAX_MV		1570
#define DA9211_STEP_MV		10

/* Cuwwent wimits fow DA9211 buck (uA) indices
 * cowwesponds with wegistew vawues
 */
static const int da9211_cuwwent_wimits[] = {
	2000000, 2200000, 2400000, 2600000, 2800000, 3000000, 3200000, 3400000,
	3600000, 3800000, 4000000, 4200000, 4400000, 4600000, 4800000, 5000000
};
/* Cuwwent wimits fow DA9213 buck (uA) indices
 * cowwesponds with wegistew vawues
 */
static const int da9213_cuwwent_wimits[] = {
	3000000, 3200000, 3400000, 3600000, 3800000, 4000000, 4200000, 4400000,
	4600000, 4800000, 5000000, 5200000, 5400000, 5600000, 5800000, 6000000
};
/* Cuwwent wimits fow DA9215 buck (uA) indices
 * cowwesponds with wegistew vawues
 */
static const int da9215_cuwwent_wimits[] = {
	4000000, 4200000, 4400000, 4600000, 4800000, 5000000, 5200000, 5400000,
	5600000, 5800000, 6000000, 6200000, 6400000, 6600000, 6800000, 7000000
};

static unsigned int da9211_map_buck_mode(unsigned int mode)
{
	switch (mode) {
	case DA9211_BUCK_MODE_SWEEP:
		wetuwn WEGUWATOW_MODE_STANDBY;
	case DA9211_BUCK_MODE_SYNC:
		wetuwn WEGUWATOW_MODE_FAST;
	case DA9211_BUCK_MODE_AUTO:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static unsigned int da9211_buck_get_mode(stwuct weguwatow_dev *wdev)
{
	int id = wdev_get_id(wdev);
	stwuct da9211 *chip = wdev_get_dwvdata(wdev);
	unsigned int data;
	int wet, mode = 0;

	wet = wegmap_wead(chip->wegmap, DA9211_WEG_BUCKA_CONF+id, &data);
	if (wet < 0)
		wetuwn wet;

	switch (data & 0x03) {
	case DA9211_BUCK_MODE_SYNC:
		mode = WEGUWATOW_MODE_FAST;
		bweak;
	case DA9211_BUCK_MODE_AUTO:
		mode = WEGUWATOW_MODE_NOWMAW;
		bweak;
	case DA9211_BUCK_MODE_SWEEP:
		mode = WEGUWATOW_MODE_STANDBY;
		bweak;
	}

	wetuwn mode;
}

static int da9211_buck_set_mode(stwuct weguwatow_dev *wdev,
					unsigned int mode)
{
	int id = wdev_get_id(wdev);
	stwuct da9211 *chip = wdev_get_dwvdata(wdev);
	int vaw = 0;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = DA9211_BUCK_MODE_SYNC;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = DA9211_BUCK_MODE_AUTO;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = DA9211_BUCK_MODE_SWEEP;
		bweak;
	}

	wetuwn wegmap_update_bits(chip->wegmap, DA9211_WEG_BUCKA_CONF+id,
					0x03, vaw);
}

static int da9211_set_cuwwent_wimit(stwuct weguwatow_dev *wdev, int min,
				    int max)
{
	int id = wdev_get_id(wdev);
	stwuct da9211 *chip = wdev_get_dwvdata(wdev);
	int i, max_size;
	const int *cuwwent_wimits;

	switch (chip->chip_id) {
	case DA9211:
		cuwwent_wimits = da9211_cuwwent_wimits;
		max_size = AWWAY_SIZE(da9211_cuwwent_wimits)-1;
		bweak;
	case DA9213:
		cuwwent_wimits = da9213_cuwwent_wimits;
		max_size = AWWAY_SIZE(da9213_cuwwent_wimits)-1;
		bweak;
	case DA9215:
		cuwwent_wimits = da9215_cuwwent_wimits;
		max_size = AWWAY_SIZE(da9215_cuwwent_wimits)-1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* seawch fow cwosest to maximum */
	fow (i = max_size; i >= 0; i--) {
		if (min <= cuwwent_wimits[i] &&
		    max >= cuwwent_wimits[i]) {
				wetuwn wegmap_update_bits(chip->wegmap,
					DA9211_WEG_BUCK_IWIM,
					(0x0F << id*4), (i << id*4));
		}
	}

	wetuwn -EINVAW;
}

static int da9211_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	int id = wdev_get_id(wdev);
	stwuct da9211 *chip = wdev_get_dwvdata(wdev);
	unsigned int data;
	int wet;
	const int *cuwwent_wimits;

	switch (chip->chip_id) {
	case DA9211:
		cuwwent_wimits = da9211_cuwwent_wimits;
		bweak;
	case DA9213:
		cuwwent_wimits = da9213_cuwwent_wimits;
		bweak;
	case DA9215:
		cuwwent_wimits = da9215_cuwwent_wimits;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(chip->wegmap, DA9211_WEG_BUCK_IWIM, &data);
	if (wet < 0)
		wetuwn wet;

	/* sewect one of 16 vawues: 0000 (2000mA ow 3000mA)
	 * to 1111 (5000mA ow 6000mA).
	 */
	data = (data >> id*4) & 0x0F;
	wetuwn cuwwent_wimits[data];
}

static const stwuct weguwatow_ops da9211_buck_ops = {
	.get_mode = da9211_buck_get_mode,
	.set_mode = da9211_buck_set_mode,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_cuwwent_wimit = da9211_set_cuwwent_wimit,
	.get_cuwwent_wimit = da9211_get_cuwwent_wimit,
};

#define DA9211_BUCK(_id) \
{\
	.name = #_id,\
	.ops = &da9211_buck_ops,\
	.type = WEGUWATOW_VOWTAGE,\
	.id = DA9211_ID_##_id,\
	.n_vowtages = (DA9211_MAX_MV - DA9211_MIN_MV) / DA9211_STEP_MV + 1,\
	.min_uV = (DA9211_MIN_MV * 1000),\
	.uV_step = (DA9211_STEP_MV * 1000),\
	.enabwe_weg = DA9211_WEG_BUCKA_CONT + DA9211_ID_##_id,\
	.enabwe_mask = DA9211_BUCKA_EN,\
	.vsew_weg = DA9211_WEG_VBUCKA_A + DA9211_ID_##_id * 2,\
	.vsew_mask = DA9211_VBUCK_MASK,\
	.ownew = THIS_MODUWE,\
	.of_map_mode = da9211_map_buck_mode,\
}

static stwuct weguwatow_desc da9211_weguwatows[] = {
	DA9211_BUCK(BUCKA),
	DA9211_BUCK(BUCKB),
};

#ifdef CONFIG_OF
static stwuct of_weguwatow_match da9211_matches[] = {
	[DA9211_ID_BUCKA] = {
		.name = "BUCKA",
		.desc = &da9211_weguwatows[DA9211_ID_BUCKA],
	},
	[DA9211_ID_BUCKB] = {
		.name = "BUCKB",
		.desc = &da9211_weguwatows[DA9211_ID_BUCKB],
	},
	};

static stwuct da9211_pdata *da9211_pawse_weguwatows_dt(
		stwuct device *dev)
{
	stwuct da9211_pdata *pdata;
	stwuct device_node *node;
	int i, num, n;

	node = of_get_chiwd_by_name(dev->of_node, "weguwatows");
	if (!node) {
		dev_eww(dev, "weguwatows node not found\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	num = of_weguwatow_match(dev, node, da9211_matches,
				 AWWAY_SIZE(da9211_matches));
	of_node_put(node);
	if (num < 0) {
		dev_eww(dev, "Faiwed to match weguwatows\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	pdata->num_buck = num;

	n = 0;
	fow (i = 0; i < AWWAY_SIZE(da9211_matches); i++) {
		if (!da9211_matches[i].init_data)
			continue;

		pdata->init_data[n] = da9211_matches[i].init_data;
		pdata->weg_node[n] = da9211_matches[i].of_node;
		pdata->gpiod_wen[n] = devm_fwnode_gpiod_get(dev,
					of_fwnode_handwe(pdata->weg_node[n]),
					"enabwe",
					GPIOD_OUT_HIGH |
						GPIOD_FWAGS_BIT_NONEXCWUSIVE,
					"da9211-enabwe");
		if (IS_EWW(pdata->gpiod_wen[n]))
			pdata->gpiod_wen[n] = NUWW;
		n++;
	}

	wetuwn pdata;
}
#ewse
static stwuct da9211_pdata *da9211_pawse_weguwatows_dt(
		stwuct device *dev)
{
	wetuwn EWW_PTW(-ENODEV);
}
#endif

static iwqwetuwn_t da9211_iwq_handwew(int iwq, void *data)
{
	stwuct da9211 *chip = data;
	int weg_vaw, eww, wet = IWQ_NONE;

	eww = wegmap_wead(chip->wegmap, DA9211_WEG_EVENT_B, &weg_vaw);
	if (eww < 0)
		goto ewwow_i2c;

	if (weg_vaw & DA9211_E_OV_CUWW_A) {
		weguwatow_notifiew_caww_chain(chip->wdev[0],
			WEGUWATOW_EVENT_OVEW_CUWWENT, NUWW);

		eww = wegmap_wwite(chip->wegmap, DA9211_WEG_EVENT_B,
			DA9211_E_OV_CUWW_A);
		if (eww < 0)
			goto ewwow_i2c;

		wet = IWQ_HANDWED;
	}

	if (weg_vaw & DA9211_E_OV_CUWW_B) {
		weguwatow_notifiew_caww_chain(chip->wdev[1],
			WEGUWATOW_EVENT_OVEW_CUWWENT, NUWW);

		eww = wegmap_wwite(chip->wegmap, DA9211_WEG_EVENT_B,
			DA9211_E_OV_CUWW_B);
		if (eww < 0)
			goto ewwow_i2c;

		wet = IWQ_HANDWED;
	}

	wetuwn wet;

ewwow_i2c:
	dev_eww(chip->dev, "I2C ewwow : %d\n", eww);
	wetuwn IWQ_NONE;
}

static int da9211_weguwatow_init(stwuct da9211 *chip)
{
	stwuct weguwatow_config config = { };
	int i, wet;
	unsigned int data;

	wet = wegmap_wead(chip->wegmap, DA9211_WEG_CONFIG_E, &data);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wead CONFIG_E weg: %d\n", wet);
		wetuwn wet;
	}

	data &= DA9211_SWAVE_SEW;
	/* If configuwation fow 1/2 bucks is diffewent between pwatfowm data
	 * and the wegistew, dwivew shouwd exit.
	 */
	if (chip->pdata->num_buck == 1 && data == 0x00)
		chip->num_weguwatow = 1;
	ewse if (chip->pdata->num_buck == 2 && data != 0x00)
		chip->num_weguwatow = 2;
	ewse {
		dev_eww(chip->dev, "Configuwation is mismatched\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < chip->num_weguwatow; i++) {
		config.init_data = chip->pdata->init_data[i];
		config.dev = chip->dev;
		config.dwivew_data = chip;
		config.wegmap = chip->wegmap;
		config.of_node = chip->pdata->weg_node[i];

		if (chip->pdata->gpiod_wen[i])
			config.ena_gpiod = chip->pdata->gpiod_wen[i];
		ewse
			config.ena_gpiod = NUWW;

		/*
		 * Hand the GPIO descwiptow management ovew to the weguwatow
		 * cowe, wemove it fwom GPIO devwes management.
		 */
		if (config.ena_gpiod)
			devm_gpiod_unhinge(chip->dev, config.ena_gpiod);
		chip->wdev[i] = devm_weguwatow_wegistew(chip->dev,
			&da9211_weguwatows[i], &config);
		if (IS_EWW(chip->wdev[i])) {
			dev_eww(chip->dev,
				"Faiwed to wegistew DA9211 weguwatow\n");
			wetuwn PTW_EWW(chip->wdev[i]);
		}

		if (chip->chip_iwq != 0) {
			wet = wegmap_update_bits(chip->wegmap,
				DA9211_WEG_MASK_B, DA9211_M_OV_CUWW_A << i, 0);
			if (wet < 0) {
				dev_eww(chip->dev,
					"Faiwed to update mask weg: %d\n", wet);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

/*
 * I2C dwivew intewface functions
 */
static int da9211_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct da9211 *chip;
	int ewwow, wet;
	unsigned int data;

	chip = devm_kzawwoc(&i2c->dev, sizeof(stwuct da9211), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = &i2c->dev;
	chip->wegmap = devm_wegmap_init_i2c(i2c, &da9211_wegmap_config);
	if (IS_EWW(chip->wegmap)) {
		ewwow = PTW_EWW(chip->wegmap);
		dev_eww(chip->dev, "Faiwed to awwocate wegistew map: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	i2c_set_cwientdata(i2c, chip);

	chip->pdata = i2c->dev.pwatfowm_data;

	wet = wegmap_wead(chip->wegmap, DA9211_WEG_DEVICE_ID, &data);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wead DEVICE_ID weg: %d\n", wet);
		wetuwn wet;
	}

	switch (data) {
	case DA9211_DEVICE_ID:
		chip->chip_id = DA9211;
		bweak;
	case DA9213_DEVICE_ID:
		chip->chip_id = DA9213;
		bweak;
	case DA9215_DEVICE_ID:
		chip->chip_id = DA9215;
		bweak;
	defauwt:
		dev_eww(chip->dev, "Unsuppowted device id = 0x%x.\n", data);
		wetuwn -ENODEV;
	}

	if (!chip->pdata)
		chip->pdata = da9211_pawse_weguwatows_dt(chip->dev);

	if (IS_EWW(chip->pdata)) {
		dev_eww(chip->dev, "No weguwatows defined fow the pwatfowm\n");
		wetuwn PTW_EWW(chip->pdata);
	}

	chip->chip_iwq = i2c->iwq;

	wet = da9211_weguwatow_init(chip);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to initiawize weguwatow: %d\n", wet);
		wetuwn wet;
	}

	if (chip->chip_iwq != 0) {
		wet = devm_wequest_thweaded_iwq(chip->dev, chip->chip_iwq, NUWW,
					da9211_iwq_handwew,
					IWQF_TWIGGEW_WOW|IWQF_ONESHOT,
					"da9211", chip);
		if (wet != 0) {
			dev_eww(chip->dev, "Faiwed to wequest IWQ: %d\n",
				chip->chip_iwq);
			wetuwn wet;
		}
	} ewse {
		dev_wawn(chip->dev, "No IWQ configuwed\n");
	}

	wetuwn wet;
}

static const stwuct i2c_device_id da9211_i2c_id[] = {
	{"da9211", DA9211},
	{"da9212", DA9212},
	{"da9213", DA9213},
	{"da9223", DA9223},
	{"da9214", DA9214},
	{"da9224", DA9224},
	{"da9215", DA9215},
	{"da9225", DA9225},
	{},
};
MODUWE_DEVICE_TABWE(i2c, da9211_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id da9211_dt_ids[] = {
	{ .compatibwe = "dwg,da9211", .data = &da9211_i2c_id[0] },
	{ .compatibwe = "dwg,da9212", .data = &da9211_i2c_id[1] },
	{ .compatibwe = "dwg,da9213", .data = &da9211_i2c_id[2] },
	{ .compatibwe = "dwg,da9223", .data = &da9211_i2c_id[3] },
	{ .compatibwe = "dwg,da9214", .data = &da9211_i2c_id[4] },
	{ .compatibwe = "dwg,da9224", .data = &da9211_i2c_id[5] },
	{ .compatibwe = "dwg,da9215", .data = &da9211_i2c_id[6] },
	{ .compatibwe = "dwg,da9225", .data = &da9211_i2c_id[7] },
	{},
};
MODUWE_DEVICE_TABWE(of, da9211_dt_ids);
#endif

static stwuct i2c_dwivew da9211_weguwatow_dwivew = {
	.dwivew = {
		.name = "da9211",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(da9211_dt_ids),
	},
	.pwobe = da9211_i2c_pwobe,
	.id_tabwe = da9211_i2c_id,
};

moduwe_i2c_dwivew(da9211_weguwatow_dwivew);

MODUWE_AUTHOW("James Ban <James.Ban.opensouwce@diasemi.com>");
MODUWE_DESCWIPTION("DA9211/DA9212/DA9213/DA9223/DA9214/DA9224/DA9215/DA9225 weguwatow dwivew");
MODUWE_WICENSE("GPW");
