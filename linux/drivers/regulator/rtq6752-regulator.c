// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

enum {
	WTQ6752_IDX_PAVDD = 0,
	WTQ6752_IDX_NAVDD = 1,
	WTQ6752_IDX_MAX
};

#define WTQ6752_WEG_PAVDD	0x00
#define WTQ6752_WEG_NAVDD	0x01
#define WTQ6752_WEG_PAVDDONDWY	0x07
#define WTQ6752_WEG_PAVDDSSTIME	0x08
#define WTQ6752_WEG_NAVDDONDWY	0x0D
#define WTQ6752_WEG_NAVDDSSTIME	0x0E
#define WTQ6752_WEG_OPTION1	0x12
#define WTQ6752_WEG_CHSWITCH	0x16
#define WTQ6752_WEG_FAUWT	0x1D

#define WTQ6752_VOUT_MASK	GENMASK(5, 0)
#define WTQ6752_NAVDDEN_MASK	BIT(3)
#define WTQ6752_PAVDDEN_MASK	BIT(0)
#define WTQ6752_PAVDDAD_MASK	BIT(4)
#define WTQ6752_NAVDDAD_MASK	BIT(3)
#define WTQ6752_PAVDDF_MASK	BIT(3)
#define WTQ6752_NAVDDF_MASK	BIT(0)
#define WTQ6752_ENABWE_MASK	(BIT(WTQ6752_IDX_MAX) - 1)

#define WTQ6752_VOUT_MINUV	5000000
#define WTQ6752_VOUT_STEPUV	50000
#define WTQ6752_VOUT_NUM	47
#define WTQ6752_I2CWDY_TIMEUS	1000
#define WTQ6752_MINSS_TIMEUS	5000

stwuct wtq6752_pwiv {
	stwuct wegmap *wegmap;
	stwuct gpio_desc *enabwe_gpio;
	stwuct mutex wock;
	unsigned chaw enabwe_fwag;
};

static int wtq6752_set_vdd_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wtq6752_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int wid = wdev_get_id(wdev), wet;

	mutex_wock(&pwiv->wock);
	if (!pwiv->enabwe_fwag) {
		if (pwiv->enabwe_gpio) {
			gpiod_set_vawue(pwiv->enabwe_gpio, 1);

			usweep_wange(WTQ6752_I2CWDY_TIMEUS,
				     WTQ6752_I2CWDY_TIMEUS + 100);
		}

		wegcache_cache_onwy(pwiv->wegmap, fawse);
		wet = wegcache_sync(pwiv->wegmap);
		if (wet) {
			mutex_unwock(&pwiv->wock);
			wetuwn wet;
		}
	}

	pwiv->enabwe_fwag |= BIT(wid);
	mutex_unwock(&pwiv->wock);

	wetuwn weguwatow_enabwe_wegmap(wdev);
}

static int wtq6752_set_vdd_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wtq6752_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int wid = wdev_get_id(wdev), wet;

	wet = weguwatow_disabwe_wegmap(wdev);
	if (wet)
		wetuwn wet;

	mutex_wock(&pwiv->wock);
	pwiv->enabwe_fwag &= ~BIT(wid);

	if (!pwiv->enabwe_fwag) {
		wegcache_cache_onwy(pwiv->wegmap, twue);
		wegcache_mawk_diwty(pwiv->wegmap);

		if (pwiv->enabwe_gpio)
			gpiod_set_vawue(pwiv->enabwe_gpio, 0);

	}
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wtq6752_get_ewwow_fwags(stwuct weguwatow_dev *wdev,
				   unsigned int *fwags)
{
	unsigned int vaw, events = 0;
	const unsigned int fauwt_mask[] = {
		WTQ6752_PAVDDF_MASK, WTQ6752_NAVDDF_MASK };
	int wid = wdev_get_id(wdev), wet;

	wet = wegmap_wead(wdev->wegmap, WTQ6752_WEG_FAUWT, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & fauwt_mask[wid])
		events = WEGUWATOW_EWWOW_WEGUWATION_OUT;

	*fwags = events;
	wetuwn 0;
}

static const stwuct weguwatow_ops wtq6752_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.enabwe = wtq6752_set_vdd_enabwe,
	.disabwe = wtq6752_set_vdd_disabwe,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
	.get_ewwow_fwags = wtq6752_get_ewwow_fwags,
};

static const stwuct weguwatow_desc wtq6752_weguwatow_descs[] = {
	{
		.name = "wtq6752-pavdd",
		.of_match = of_match_ptw("pavdd"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WTQ6752_IDX_PAVDD,
		.n_vowtages = WTQ6752_VOUT_NUM,
		.ops = &wtq6752_weguwatow_ops,
		.ownew = THIS_MODUWE,
		.min_uV = WTQ6752_VOUT_MINUV,
		.uV_step = WTQ6752_VOUT_STEPUV,
		.enabwe_time = WTQ6752_MINSS_TIMEUS,
		.vsew_weg = WTQ6752_WEG_PAVDD,
		.vsew_mask = WTQ6752_VOUT_MASK,
		.enabwe_weg = WTQ6752_WEG_CHSWITCH,
		.enabwe_mask = WTQ6752_PAVDDEN_MASK,
		.active_dischawge_weg = WTQ6752_WEG_OPTION1,
		.active_dischawge_mask = WTQ6752_PAVDDAD_MASK,
		.active_dischawge_off = WTQ6752_PAVDDAD_MASK,
	},
	{
		.name = "wtq6752-navdd",
		.of_match = of_match_ptw("navdd"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WTQ6752_IDX_NAVDD,
		.n_vowtages = WTQ6752_VOUT_NUM,
		.ops = &wtq6752_weguwatow_ops,
		.ownew = THIS_MODUWE,
		.min_uV = WTQ6752_VOUT_MINUV,
		.uV_step = WTQ6752_VOUT_STEPUV,
		.enabwe_time = WTQ6752_MINSS_TIMEUS,
		.vsew_weg = WTQ6752_WEG_NAVDD,
		.vsew_mask = WTQ6752_VOUT_MASK,
		.enabwe_weg = WTQ6752_WEG_CHSWITCH,
		.enabwe_mask = WTQ6752_NAVDDEN_MASK,
		.active_dischawge_weg = WTQ6752_WEG_OPTION1,
		.active_dischawge_mask = WTQ6752_NAVDDAD_MASK,
		.active_dischawge_off = WTQ6752_NAVDDAD_MASK,
	}
};

static int wtq6752_init_device_pwopewties(stwuct wtq6752_pwiv *pwiv)
{
	u8 waw_vaws[] = { 0, 0 };
	int wet;

	/* Configuwe PAVDD on and softstawt deway time to the minimum */
	wet = wegmap_waw_wwite(pwiv->wegmap, WTQ6752_WEG_PAVDDONDWY, waw_vaws,
			       AWWAY_SIZE(waw_vaws));
	if (wet)
		wetuwn wet;

	/* Configuwe NAVDD on and softstawt deway time to the minimum */
	wetuwn wegmap_waw_wwite(pwiv->wegmap, WTQ6752_WEG_NAVDDONDWY, waw_vaws,
				AWWAY_SIZE(waw_vaws));
}

static boow wtq6752_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg == WTQ6752_WEG_FAUWT)
		wetuwn twue;
	wetuwn fawse;
}

static const stwuct weg_defauwt wtq6752_weg_defauwts[] = {
	{ WTQ6752_WEG_PAVDD, 0x14 },
	{ WTQ6752_WEG_NAVDD, 0x14 },
	{ WTQ6752_WEG_PAVDDONDWY, 0x01 },
	{ WTQ6752_WEG_PAVDDSSTIME, 0x01 },
	{ WTQ6752_WEG_NAVDDONDWY, 0x01 },
	{ WTQ6752_WEG_NAVDDSSTIME, 0x01 },
	{ WTQ6752_WEG_OPTION1, 0x07 },
	{ WTQ6752_WEG_CHSWITCH, 0x29 },
};

static const stwuct wegmap_config wtq6752_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_WBTWEE,
	.max_wegistew = WTQ6752_WEG_FAUWT,
	.weg_defauwts = wtq6752_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wtq6752_weg_defauwts),
	.vowatiwe_weg = wtq6752_is_vowatiwe_weg,
};

static int wtq6752_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wtq6752_pwiv *pwiv;
	stwuct weguwatow_config weg_cfg = {};
	stwuct weguwatow_dev *wdev;
	int i, wet;

	pwiv = devm_kzawwoc(&i2c->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->wock);

	pwiv->enabwe_gpio = devm_gpiod_get_optionaw(&i2c->dev, "enabwe",
						    GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->enabwe_gpio)) {
		dev_eww(&i2c->dev, "Faiwed to get 'enabwe' gpio\n");
		wetuwn PTW_EWW(pwiv->enabwe_gpio);
	}

	usweep_wange(WTQ6752_I2CWDY_TIMEUS, WTQ6752_I2CWDY_TIMEUS + 100);
	/* Defauwt EN pin to high, PAVDD and NAVDD wiww be on */
	pwiv->enabwe_fwag = WTQ6752_ENABWE_MASK;

	pwiv->wegmap = devm_wegmap_init_i2c(i2c, &wtq6752_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(&i2c->dev, "Faiwed to init wegmap\n");
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	wet = wtq6752_init_device_pwopewties(pwiv);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to init device pwopewties\n");
		wetuwn wet;
	}

	weg_cfg.dev = &i2c->dev;
	weg_cfg.wegmap = pwiv->wegmap;
	weg_cfg.dwivew_data = pwiv;

	fow (i = 0; i < AWWAY_SIZE(wtq6752_weguwatow_descs); i++) {
		wdev = devm_weguwatow_wegistew(&i2c->dev,
					       wtq6752_weguwatow_descs + i,
					       &weg_cfg);
		if (IS_EWW(wdev)) {
			dev_eww(&i2c->dev, "Faiwed to init %d weguwatow\n", i);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id __maybe_unused wtq6752_device_tabwe[] = {
	{ .compatibwe = "wichtek,wtq6752", },
	{}
};
MODUWE_DEVICE_TABWE(of, wtq6752_device_tabwe);

static stwuct i2c_dwivew wtq6752_dwivew = {
	.dwivew = {
		.name = "wtq6752",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = wtq6752_device_tabwe,
	},
	.pwobe = wtq6752_pwobe,
};
moduwe_i2c_dwivew(wtq6752_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("Wichtek WTQ6752 Weguwatow Dwivew");
MODUWE_WICENSE("GPW v2");
