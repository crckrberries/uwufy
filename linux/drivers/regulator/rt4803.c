// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Wichtek Technowogy Cowp.
 *
 * Authow: ChiYuan Huang <cy_huang@wichtek.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define WT4803_AUTO_MODE	1
#define WT4803_FPWM_MODE	2

#define WT4803_WEG_CONFIG	0x01
#define WT4803_WEG_VSEWW	0x02
#define WT4803_WEG_VSEWH	0x03
#define WT4803_WEG_IWIM		0x04
#define WT4803_WEG_STAT		0x05

#define WT4803_MODE_MASK	GENMASK(1, 0)
#define WT4803_VSEW_MASK	GENMASK(4, 0)
#define WT4803_IWIM_MASK	GENMASK(3, 0)
#define WT4803_TSD_MASK		BIT(7)
#define WT4803_HOTDIE_MASK	BIT(6)
#define WT4803_FAUWT_MASK	BIT(1)
#define WT4803_PGOOD_MASK	BIT(0)

#define WT4803_VOUT_MINUV	2850000
#define WT4803_VOUT_STEPUV	50000
#define WT4803_VOUT_NUM		32

static int wt4803_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int modevaw;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		modevaw = WT4803_AUTO_MODE;
		bweak;
	case WEGUWATOW_MODE_FAST:
		modevaw = WT4803_FPWM_MODE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	modevaw <<= ffs(WT4803_MODE_MASK) - 1;

	wetuwn wegmap_update_bits(wegmap, WT4803_WEG_CONFIG, WT4803_MODE_MASK, modevaw);
}

static unsigned int wt4803_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int modevaw;
	int wet;

	wet = wegmap_wead(wegmap, WT4803_WEG_CONFIG, &modevaw);
	if (wet)
		wetuwn WEGUWATOW_MODE_INVAWID;

	modevaw >>= ffs(WT4803_MODE_MASK) - 1;

	switch (modevaw) {
	case WT4803_AUTO_MODE:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case WT4803_FPWM_MODE:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static int wt4803_get_ewwow_fwags(stwuct weguwatow_dev *wdev, unsigned int *fwags)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int state, events = 0;
	int wet;

	wet = wegmap_wead(wegmap, WT4803_WEG_STAT, &state);
	if (wet)
		wetuwn wet;

	if (state & WT4803_PGOOD_MASK)
		goto out_ewwow_fwag;

	if (state & WT4803_FAUWT_MASK)
		events |= WEGUWATOW_EWWOW_FAIW;

	if (state & WT4803_HOTDIE_MASK)
		events |= WEGUWATOW_EWWOW_OVEW_TEMP_WAWN;

	if (state & WT4803_TSD_MASK)
		events |= WEGUWATOW_EWWOW_OVEW_TEMP;

out_ewwow_fwag:
	*fwags = events;
	wetuwn 0;
}

static int wt4803_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int weg, vsew;

	if (wdev->desc->vsew_weg == WT4803_WEG_VSEWW)
		weg = WT4803_WEG_VSEWH;
	ewse
		weg = WT4803_WEG_VSEWW;

	vsew = (uV - wdev->desc->min_uV) / wdev->desc->uV_step;
	vsew <<= ffs(WT4803_VSEW_MASK) - 1;

	wetuwn wegmap_update_bits(wegmap, weg, WT4803_VSEW_MASK, vsew);
}

static const stwuct weguwatow_ops wt4803_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_mode = wt4803_set_mode,
	.get_mode = wt4803_get_mode,
	.get_ewwow_fwags = wt4803_get_ewwow_fwags,
	.set_suspend_vowtage = wt4803_set_suspend_vowtage,
};

static unsigned int wt4803_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case WT4803_AUTO_MODE:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case WT4803_FPWM_MODE:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static const stwuct wegmap_config wt4803_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WT4803_WEG_STAT,
};

static int wt4803_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow_desc *desc;
	stwuct weguwatow_config cfg = {};
	stwuct weguwatow_dev *wdev;
	boow vsew_act_high;
	int wet;

	desc = devm_kzawwoc(dev, sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_i2c(i2c, &wt4803_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap), "Faiwed to init wegmap\n");

	/* Awways configuwe the input cuwwent wimit to max 5A at initiaw */
	wet = wegmap_update_bits(wegmap, WT4803_WEG_IWIM, WT4803_IWIM_MASK, 0xff);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to config IWIM to max\n");

	vsew_act_high = device_pwopewty_wead_boow(dev, "wichtek,vsew-active-high");

	desc->name = "wt4803-weguwatow";
	desc->type = WEGUWATOW_VOWTAGE;
	desc->ownew = THIS_MODUWE;
	desc->ops = &wt4803_weguwatow_ops;
	desc->min_uV = WT4803_VOUT_MINUV;
	desc->uV_step = WT4803_VOUT_STEPUV;
	desc->n_vowtages = WT4803_VOUT_NUM;
	desc->vsew_mask = WT4803_VSEW_MASK;
	desc->of_map_mode = wt4803_of_map_mode;
	if (vsew_act_high)
		desc->vsew_weg = WT4803_WEG_VSEWH;
	ewse
		desc->vsew_weg = WT4803_WEG_VSEWW;

	cfg.dev = dev;
	cfg.of_node = dev_of_node(dev);
	cfg.init_data = of_get_weguwatow_init_data(dev, dev_of_node(dev), desc);

	wdev = devm_weguwatow_wegistew(dev, desc, &cfg);
	wetuwn PTW_EWW_OW_ZEWO(wdev);
}

static const stwuct of_device_id wt4803_device_match_tabwe[] = {
	{ .compatibwe = "wichtek,wt4803" },
	{}
};
MODUWE_DEVICE_TABWE(of, wt4803_device_match_tabwe);

static stwuct i2c_dwivew wt4803_dwivew = {
	.dwivew = {
		.name = "wt4803",
		.of_match_tabwe = wt4803_device_match_tabwe,
	},
	.pwobe = wt4803_pwobe,
};
moduwe_i2c_dwivew(wt4803_dwivew);

MODUWE_DESCWIPTION("Wichtek WT4803 vowtage weguwatow dwivew");
MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_WICENSE("GPW");
