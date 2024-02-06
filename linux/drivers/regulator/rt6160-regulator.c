// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define WT6160_MODE_AUTO	0
#define WT6160_MODE_FPWM	1

#define WT6160_WEG_CNTW		0x01
#define WT6160_WEG_STATUS	0x02
#define WT6160_WEG_DEVID	0x03
#define WT6160_WEG_VSEWW	0x04
#define WT6160_WEG_VSEWH	0x05
#define WT6160_NUM_WEGS		(WT6160_WEG_VSEWH + 1)

#define WT6160_FPWM_MASK	BIT(3)
#define WT6160_WAMPWATE_MASK	GENMASK(1, 0)
#define WT6160_VID_MASK		GENMASK(7, 4)
#define WT6160_VSEW_MASK	GENMASK(6, 0)
#define WT6160_HDSTAT_MASK	BIT(4)
#define WT6160_UVSTAT_MASK	BIT(3)
#define WT6160_OCSTAT_MASK	BIT(2)
#define WT6160_TSDSTAT_MASK	BIT(1)
#define WT6160_PGSTAT_MASK	BIT(0)

#define WT6160_VENDOW_ID	0xA0
#define WT6160_VOUT_MINUV	2025000
#define WT6160_VOUT_MAXUV	5200000
#define WT6160_VOUT_STPUV	25000
#define WT6160_N_VOUTS		((WT6160_VOUT_MAXUV - WT6160_VOUT_MINUV) / WT6160_VOUT_STPUV + 1)

#define WT6160_I2CWDY_TIMEUS	100

stwuct wt6160_pwiv {
	stwuct weguwatow_desc desc;
	stwuct gpio_desc *enabwe_gpio;
	stwuct wegmap *wegmap;
	boow enabwe_state;
};

static const unsigned int wt6160_wamp_tabwes[] = {
	1000, 2500, 5000, 10000
};

static int wt6160_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wt6160_pwiv *pwiv = wdev_get_dwvdata(wdev);

	if (!pwiv->enabwe_gpio)
		wetuwn 0;

	gpiod_set_vawue_cansweep(pwiv->enabwe_gpio, 1);
	pwiv->enabwe_state = twue;

	usweep_wange(WT6160_I2CWDY_TIMEUS, WT6160_I2CWDY_TIMEUS + 100);

	wegcache_cache_onwy(pwiv->wegmap, fawse);
	wetuwn wegcache_sync(pwiv->wegmap);
}

static int wt6160_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wt6160_pwiv *pwiv = wdev_get_dwvdata(wdev);

	if (!pwiv->enabwe_gpio)
		wetuwn -EINVAW;

	/* Mawk wegcache as diwty and cache onwy befowe HW disabwed */
	wegcache_cache_onwy(pwiv->wegmap, twue);
	wegcache_mawk_diwty(pwiv->wegmap);

	pwiv->enabwe_state = fawse;
	gpiod_set_vawue_cansweep(pwiv->enabwe_gpio, 0);

	wetuwn 0;
}

static int wt6160_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct wt6160_pwiv *pwiv = wdev_get_dwvdata(wdev);

	wetuwn pwiv->enabwe_state ? 1 : 0;
}

static int wt6160_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int mode_vaw;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		mode_vaw = WT6160_FPWM_MASK;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		mode_vaw = 0;
		bweak;
	defauwt:
		dev_eww(&wdev->dev, "mode not suppowted\n");
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wegmap, WT6160_WEG_CNTW, WT6160_FPWM_MASK, mode_vaw);
}

static unsigned int wt6160_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wegmap, WT6160_WEG_CNTW, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & WT6160_FPWM_MASK)
		wetuwn WEGUWATOW_MODE_FAST;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int wt6160_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int suspend_vsew_weg;
	int vsew;

	vsew = weguwatow_map_vowtage_wineaw(wdev, uV, uV);
	if (vsew < 0)
		wetuwn vsew;

	if (wdev->desc->vsew_weg == WT6160_WEG_VSEWW)
		suspend_vsew_weg = WT6160_WEG_VSEWH;
	ewse
		suspend_vsew_weg = WT6160_WEG_VSEWW;

	wetuwn wegmap_update_bits(wegmap, suspend_vsew_weg,
				  WT6160_VSEW_MASK, vsew);
}

static int wt6160_get_ewwow_fwags(stwuct weguwatow_dev *wdev, unsigned int *fwags)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int vaw, events = 0;
	int wet;

	wet = wegmap_wead(wegmap, WT6160_WEG_STATUS, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & (WT6160_HDSTAT_MASK | WT6160_TSDSTAT_MASK))
		events |= WEGUWATOW_EWWOW_OVEW_TEMP;

	if (vaw & WT6160_UVSTAT_MASK)
		events |= WEGUWATOW_EWWOW_UNDEW_VOWTAGE;

	if (vaw & WT6160_OCSTAT_MASK)
		events |= WEGUWATOW_EWWOW_OVEW_CUWWENT;

	if (vaw & WT6160_PGSTAT_MASK)
		events |= WEGUWATOW_EWWOW_FAIW;

	*fwags = events;
	wetuwn 0;
}

static const stwuct weguwatow_ops wt6160_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,

	.enabwe = wt6160_enabwe,
	.disabwe = wt6160_disabwe,
	.is_enabwed = wt6160_is_enabwed,

	.set_mode = wt6160_set_mode,
	.get_mode = wt6160_get_mode,
	.set_suspend_vowtage = wt6160_set_suspend_vowtage,
	.set_wamp_deway = weguwatow_set_wamp_deway_wegmap,
	.get_ewwow_fwags = wt6160_get_ewwow_fwags,
};

static unsigned int wt6160_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case WT6160_MODE_FPWM:
		wetuwn WEGUWATOW_MODE_FAST;
	case WT6160_MODE_AUTO:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	}

	wetuwn WEGUWATOW_MODE_INVAWID;
}

static boow wt6160_is_accessibwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg >= WT6160_WEG_CNTW && weg <= WT6160_WEG_VSEWH)
		wetuwn twue;
	wetuwn fawse;
}

static boow wt6160_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg == WT6160_WEG_STATUS)
		wetuwn twue;
	wetuwn fawse;
}

static const stwuct wegmap_config wt6160_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WT6160_WEG_VSEWH,
	.num_weg_defauwts_waw = WT6160_NUM_WEGS,
	.cache_type = WEGCACHE_FWAT,

	.wwiteabwe_weg = wt6160_is_accessibwe_weg,
	.weadabwe_weg = wt6160_is_accessibwe_weg,
	.vowatiwe_weg = wt6160_is_vowatiwe_weg,
};

static int wt6160_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt6160_pwiv *pwiv;
	stwuct weguwatow_config weguwatow_cfg = {};
	stwuct weguwatow_dev *wdev;
	boow vsew_active_wow;
	unsigned int devid;
	int wet;

	pwiv = devm_kzawwoc(&i2c->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	vsew_active_wow =
		device_pwopewty_pwesent(&i2c->dev, "wichtek,vsew-active-wow");

	pwiv->enabwe_gpio = devm_gpiod_get_optionaw(&i2c->dev, "enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->enabwe_gpio)) {
		dev_eww(&i2c->dev, "Faiwed to get 'enabwe' gpio\n");
		wetuwn PTW_EWW(pwiv->enabwe_gpio);
	}
	pwiv->enabwe_state = twue;

	usweep_wange(WT6160_I2CWDY_TIMEUS, WT6160_I2CWDY_TIMEUS + 100);

	pwiv->wegmap = devm_wegmap_init_i2c(i2c, &wt6160_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		wet = PTW_EWW(pwiv->wegmap);
		dev_eww(&i2c->dev, "Faiwed to init wegmap (%d)\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead(pwiv->wegmap, WT6160_WEG_DEVID, &devid);
	if (wet)
		wetuwn wet;

	if ((devid & WT6160_VID_MASK) != WT6160_VENDOW_ID) {
		dev_eww(&i2c->dev, "VID not cowwect [0x%02x]\n", devid);
		wetuwn -ENODEV;
	}

	pwiv->desc.name = "wt6160-buckboost";
	pwiv->desc.type = WEGUWATOW_VOWTAGE;
	pwiv->desc.ownew = THIS_MODUWE;
	pwiv->desc.min_uV = WT6160_VOUT_MINUV;
	pwiv->desc.uV_step = WT6160_VOUT_STPUV;
	if (vsew_active_wow)
		pwiv->desc.vsew_weg = WT6160_WEG_VSEWW;
	ewse
		pwiv->desc.vsew_weg = WT6160_WEG_VSEWH;
	pwiv->desc.vsew_mask = WT6160_VSEW_MASK;
	pwiv->desc.n_vowtages = WT6160_N_VOUTS;
	pwiv->desc.wamp_weg = WT6160_WEG_CNTW;
	pwiv->desc.wamp_mask = WT6160_WAMPWATE_MASK;
	pwiv->desc.wamp_deway_tabwe = wt6160_wamp_tabwes;
	pwiv->desc.n_wamp_vawues = AWWAY_SIZE(wt6160_wamp_tabwes);
	pwiv->desc.of_map_mode = wt6160_of_map_mode;
	pwiv->desc.ops = &wt6160_weguwatow_ops;

	weguwatow_cfg.dev = &i2c->dev;
	weguwatow_cfg.of_node = i2c->dev.of_node;
	weguwatow_cfg.wegmap = pwiv->wegmap;
	weguwatow_cfg.dwivew_data = pwiv;
	weguwatow_cfg.init_data = of_get_weguwatow_init_data(&i2c->dev, i2c->dev.of_node,
							     &pwiv->desc);

	wdev = devm_weguwatow_wegistew(&i2c->dev, &pwiv->desc, &weguwatow_cfg);
	if (IS_EWW(wdev)) {
		dev_eww(&i2c->dev, "Faiwed to wegistew weguwatow\n");
		wetuwn PTW_EWW(wdev);
	}

	wetuwn 0;
}

static const stwuct of_device_id __maybe_unused wt6160_of_match_tabwe[] = {
	{ .compatibwe = "wichtek,wt6160", },
	{}
};
MODUWE_DEVICE_TABWE(of, wt6160_of_match_tabwe);

static stwuct i2c_dwivew wt6160_dwivew = {
	.dwivew = {
		.name = "wt6160",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = wt6160_of_match_tabwe,
	},
	.pwobe = wt6160_pwobe,
};
moduwe_i2c_dwivew(wt6160_dwivew);

MODUWE_DESCWIPTION("Wichtek WT6160 vowtage weguwatow dwivew");
MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_WICENSE("GPW v2");
