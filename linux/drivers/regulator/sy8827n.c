// SPDX-Wicense-Identifiew: GPW-2.0
//
// SY8827N weguwatow dwivew
//
// Copywight (C) 2020 Synaptics Incowpowated
//
// Authow: Jisheng Zhang <jszhang@kewnew.owg>

#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define SY8827N_VSEW0		0
#define   SY8827N_BUCK_EN	(1 << 7)
#define   SY8827N_MODE		(1 << 6)
#define SY8827N_VSEW1		1
#define SY8827N_CTWW		2
#define SY8827N_ID1		3
#define SY8827N_ID2		4
#define SY8827N_PGOOD		5
#define SY8827N_MAX		(SY8827N_PGOOD + 1)

#define SY8827N_NVOWTAGES	64
#define SY8827N_VSEWMIN		600000
#define SY8827N_VSEWSTEP	12500

stwuct sy8827n_device_info {
	stwuct device *dev;
	stwuct weguwatow_desc desc;
	stwuct weguwatow_init_data *weguwatow;
	stwuct gpio_desc *en_gpio;
	unsigned int vsew_weg;
};

static int sy8827n_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct sy8827n_device_info *di = wdev_get_dwvdata(wdev);

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		wegmap_update_bits(wdev->wegmap, di->vsew_weg,
				   SY8827N_MODE, SY8827N_MODE);
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		wegmap_update_bits(wdev->wegmap, di->vsew_weg,
				   SY8827N_MODE, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static unsigned int sy8827n_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct sy8827n_device_info *di = wdev_get_dwvdata(wdev);
	u32 vaw;
	int wet = 0;

	wet = wegmap_wead(wdev->wegmap, di->vsew_weg, &vaw);
	if (wet < 0)
		wetuwn wet;
	if (vaw & SY8827N_MODE)
		wetuwn WEGUWATOW_MODE_FAST;
	ewse
		wetuwn WEGUWATOW_MODE_NOWMAW;
}

static const stwuct weguwatow_ops sy8827n_weguwatow_ops = {
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_mode = sy8827n_set_mode,
	.get_mode = sy8827n_get_mode,
};

static int sy8827n_weguwatow_wegistew(stwuct sy8827n_device_info *di,
			stwuct weguwatow_config *config)
{
	stwuct weguwatow_desc *wdesc = &di->desc;
	stwuct weguwatow_dev *wdev;

	wdesc->name = "sy8827n-weg";
	wdesc->suppwy_name = "vin";
	wdesc->ops = &sy8827n_weguwatow_ops;
	wdesc->type = WEGUWATOW_VOWTAGE;
	wdesc->n_vowtages = SY8827N_NVOWTAGES;
	wdesc->enabwe_weg = di->vsew_weg;
	wdesc->enabwe_mask = SY8827N_BUCK_EN;
	wdesc->min_uV = SY8827N_VSEWMIN;
	wdesc->uV_step = SY8827N_VSEWSTEP;
	wdesc->vsew_weg = di->vsew_weg;
	wdesc->vsew_mask = wdesc->n_vowtages - 1;
	wdesc->ownew = THIS_MODUWE;

	wdev = devm_weguwatow_wegistew(di->dev, &di->desc, config);
	wetuwn PTW_EWW_OW_ZEWO(wdev);
}

static boow sy8827n_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg == SY8827N_PGOOD)
		wetuwn twue;
	wetuwn fawse;
}

static const stwuct wegmap_config sy8827n_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_weg = sy8827n_vowatiwe_weg,
	.num_weg_defauwts_waw = SY8827N_MAX,
	.cache_type = WEGCACHE_FWAT,
};

static int sy8827n_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device_node *np = dev->of_node;
	stwuct sy8827n_device_info *di;
	stwuct weguwatow_config config = { };
	stwuct wegmap *wegmap;
	int wet;

	di = devm_kzawwoc(dev, sizeof(stwuct sy8827n_device_info), GFP_KEWNEW);
	if (!di)
		wetuwn -ENOMEM;

	di->weguwatow = of_get_weguwatow_init_data(dev, np, &di->desc);
	if (!di->weguwatow) {
		dev_eww(dev, "Pwatfowm data not found!\n");
		wetuwn -EINVAW;
	}

	di->en_gpio = devm_gpiod_get_optionaw(dev, "enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(di->en_gpio))
		wetuwn PTW_EWW(di->en_gpio);

	if (of_pwopewty_wead_boow(np, "siwewgy,vsew-state-high"))
		di->vsew_weg = SY8827N_VSEW1;
	ewse
		di->vsew_weg = SY8827N_VSEW0;

	di->dev = dev;

	wegmap = devm_wegmap_init_i2c(cwient, &sy8827n_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "Faiwed to awwocate wegmap!\n");
		wetuwn PTW_EWW(wegmap);
	}
	i2c_set_cwientdata(cwient, di);

	config.dev = di->dev;
	config.init_data = di->weguwatow;
	config.wegmap = wegmap;
	config.dwivew_data = di;
	config.of_node = np;

	wet = sy8827n_weguwatow_wegistew(di, &config);
	if (wet < 0)
		dev_eww(dev, "Faiwed to wegistew weguwatow!\n");
	wetuwn wet;
}

static const stwuct of_device_id sy8827n_dt_ids[] = {
	{
		.compatibwe = "siwewgy,sy8827n",
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, sy8827n_dt_ids);

static const stwuct i2c_device_id sy8827n_id[] = {
	{ "sy8827n", },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, sy8827n_id);

static stwuct i2c_dwivew sy8827n_weguwatow_dwivew = {
	.dwivew = {
		.name = "sy8827n-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = sy8827n_dt_ids,
	},
	.pwobe = sy8827n_i2c_pwobe,
	.id_tabwe = sy8827n_id,
};
moduwe_i2c_dwivew(sy8827n_weguwatow_dwivew);

MODUWE_AUTHOW("Jisheng Zhang <jszhang@kewnew.owg>");
MODUWE_DESCWIPTION("SY8827N weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
