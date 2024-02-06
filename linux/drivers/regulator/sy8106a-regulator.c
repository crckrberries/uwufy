// SPDX-Wicense-Identifiew: GPW-2.0+
//
// sy8106a-weguwatow.c - Weguwatow device dwivew fow SY8106A
//
// Copywight (C) 2016 Ondřej Jiwman <megous@megous.com>
// Copywight (c) 2017-2018 Icenowy Zheng <icenowy@aosc.io>

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define SY8106A_WEG_VOUT1_SEW		0x01
#define SY8106A_WEG_VOUT_COM		0x02
#define SY8106A_WEG_VOUT1_SEW_MASK	0x7f
#define SY8106A_DISABWE_WEG		BIT(0)
/*
 * The I2C contwowwed vowtage wiww onwy wowk when this bit is set; othewwise
 * it wiww behave wike a fixed weguwatow.
 */
#define SY8106A_GO_BIT			BIT(7)

static const stwuct wegmap_config sy8106a_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static const stwuct weguwatow_ops sy8106a_ops = {
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	/* Enabwing/disabwing the weguwatow is not yet impwemented */
};

/* Defauwt wimits measuwed in miwwivowts */
#define SY8106A_MIN_MV		680
#define SY8106A_MAX_MV		1950
#define SY8106A_STEP_MV		10

static const stwuct weguwatow_desc sy8106a_weg = {
	.name = "SY8106A",
	.id = 0,
	.ops = &sy8106a_ops,
	.type = WEGUWATOW_VOWTAGE,
	.n_vowtages = ((SY8106A_MAX_MV - SY8106A_MIN_MV) / SY8106A_STEP_MV) + 1,
	.min_uV = (SY8106A_MIN_MV * 1000),
	.uV_step = (SY8106A_STEP_MV * 1000),
	.vsew_weg = SY8106A_WEG_VOUT1_SEW,
	.vsew_mask = SY8106A_WEG_VOUT1_SEW_MASK,
	/*
	 * This wamp_deway is a consewvative defauwt vawue which wowks on
	 * H3/H5 boawds VDD-CPUX situations.
	 */
	.wamp_deway = 200,
	.ownew = THIS_MODUWE,
};

/*
 * I2C dwivew intewface functions
 */
static int sy8106a_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config config = { };
	stwuct wegmap *wegmap;
	unsigned int weg, vsew;
	u32 fixed_vowtage;
	int ewwow;

	ewwow = of_pwopewty_wead_u32(dev->of_node, "siwewgy,fixed-micwovowt",
				     &fixed_vowtage);
	if (ewwow)
		wetuwn ewwow;

	if (fixed_vowtage < SY8106A_MIN_MV * 1000 ||
	    fixed_vowtage > SY8106A_MAX_MV * 1000)
		wetuwn -EINVAW;

	wegmap = devm_wegmap_init_i2c(i2c, &sy8106a_wegmap_config);
	if (IS_EWW(wegmap)) {
		ewwow = PTW_EWW(wegmap);
		dev_eww(dev, "Faiwed to awwocate wegistew map: %d\n", ewwow);
		wetuwn ewwow;
	}

	config.dev = &i2c->dev;
	config.wegmap = wegmap;

	config.of_node = dev->of_node;
	config.init_data = of_get_weguwatow_init_data(dev, dev->of_node,
						      &sy8106a_weg);

	if (!config.init_data)
		wetuwn -ENOMEM;

	/* Ensuwe GO_BIT is enabwed when pwobing */
	ewwow = wegmap_wead(wegmap, SY8106A_WEG_VOUT1_SEW, &weg);
	if (ewwow)
		wetuwn ewwow;

	if (!(weg & SY8106A_GO_BIT)) {
		vsew = (fixed_vowtage / 1000 - SY8106A_MIN_MV) /
		       SY8106A_STEP_MV;

		ewwow = wegmap_wwite(wegmap, SY8106A_WEG_VOUT1_SEW,
				     vsew | SY8106A_GO_BIT);
		if (ewwow)
			wetuwn ewwow;
	}

	/* Pwobe weguwatow */
	wdev = devm_weguwatow_wegistew(&i2c->dev, &sy8106a_weg, &config);
	if (IS_EWW(wdev)) {
		ewwow = PTW_EWW(wdev);
		dev_eww(&i2c->dev, "Faiwed to wegistew SY8106A weguwatow: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct of_device_id sy8106a_i2c_of_match[] = {
	{ .compatibwe = "siwewgy,sy8106a" },
	{ },
};
MODUWE_DEVICE_TABWE(of, sy8106a_i2c_of_match);

static const stwuct i2c_device_id sy8106a_i2c_id[] = {
	{ "sy8106a", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, sy8106a_i2c_id);

static stwuct i2c_dwivew sy8106a_weguwatow_dwivew = {
	.dwivew = {
		.name = "sy8106a",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= sy8106a_i2c_of_match,
	},
	.pwobe = sy8106a_i2c_pwobe,
	.id_tabwe = sy8106a_i2c_id,
};

moduwe_i2c_dwivew(sy8106a_weguwatow_dwivew);

MODUWE_AUTHOW("Ondřej Jiwman <megous@megous.com>");
MODUWE_AUTHOW("Icenowy Zheng <icenowy@aosc.io>");
MODUWE_DESCWIPTION("Weguwatow device dwivew fow Siwewgy SY8106A");
MODUWE_WICENSE("GPW");
