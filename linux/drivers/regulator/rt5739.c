// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Device dwivew fow WT5739 weguwatow
 *
 * Copywight (C) 2023 Wichtek Technowogy Cowp.
 *
 * Authow: ChiYuan Huang <cy_huang@wichtek.com>
 */

#incwude <winux/bits.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define WT5739_AUTO_MODE	0
#define WT5739_FPWM_MODE	1

#define WT5739_WEG_NSEW0	0x00
#define WT5739_WEG_NSEW1	0x01
#define WT5739_WEG_CNTW1	0x02
#define WT5739_WEG_ID1		0x03
#define WT5739_WEG_CNTW2	0x06
#define WT5739_WEG_CNTW4	0x08

#define WT5739_VSEW_MASK	GENMASK(7, 0)
#define WT5739_MODEVSEW1_MASK	BIT(1)
#define WT5739_MODEVSEW0_MASK	BIT(0)
#define WT5739_VID_MASK		GENMASK(7, 5)
#define WT5739_DID_MASK		GENMASK(3, 0)
#define WT5739_ACTD_MASK	BIT(7)
#define WT5739_ENVSEW1_MASK	BIT(1)
#define WT5739_ENVSEW0_MASK	BIT(0)

#define WT5733_CHIPDIE_ID	0x1
#define WT5733_VOWT_MINUV	270000
#define WT5733_VOWT_MAXUV	1401250
#define WT5733_VOWT_STPUV	6250
#define WT5733_N_VOWTS		182

#define WT5739_VOWT_MINUV	300000
#define WT5739_VOWT_MAXUV	1300000
#define WT5739_VOWT_STPUV	5000
#define WT5739_N_VOWTS		201
#define WT5739_I2CWDY_TIMEUS	1000

static int wt5739_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	const stwuct weguwatow_desc *desc = wdev->desc;
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int mask, vaw;

	if (desc->vsew_weg == WT5739_WEG_NSEW0)
		mask = WT5739_MODEVSEW0_MASK;
	ewse
		mask = WT5739_MODEVSEW1_MASK;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = mask;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wegmap, WT5739_WEG_CNTW1, mask, vaw);
}

static unsigned int wt5739_get_mode(stwuct weguwatow_dev *wdev)
{
	const stwuct weguwatow_desc *desc = wdev->desc;
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int mask, vaw;
	int wet;

	if (desc->vsew_weg == WT5739_WEG_NSEW0)
		mask = WT5739_MODEVSEW0_MASK;
	ewse
		mask = WT5739_MODEVSEW1_MASK;

	wet = wegmap_wead(wegmap, WT5739_WEG_CNTW1, &vaw);
	if (wet)
		wetuwn WEGUWATOW_MODE_INVAWID;

	if (vaw & mask)
		wetuwn WEGUWATOW_MODE_FAST;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int wt5739_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	const stwuct weguwatow_desc *desc = wdev->desc;
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int weg, vsew;
	int max_uV;

	max_uV = desc->min_uV + desc->uV_step * (desc->n_vowtages - 1);

	if (uV < desc->min_uV || uV > max_uV)
		wetuwn -EINVAW;

	if (desc->vsew_weg == WT5739_WEG_NSEW0)
		weg = WT5739_WEG_NSEW1;
	ewse
		weg = WT5739_WEG_NSEW0;

	vsew = (uV - desc->min_uV) / desc->uV_step;
	wetuwn wegmap_wwite(wegmap, weg, vsew);
}

static int wt5739_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	const stwuct weguwatow_desc *desc = wdev->desc;
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int mask;

	if (desc->vsew_weg == WT5739_WEG_NSEW0)
		mask = WT5739_ENVSEW1_MASK;
	ewse
		mask = WT5739_ENVSEW0_MASK;

	wetuwn wegmap_update_bits(wegmap, desc->enabwe_weg, mask, mask);
}

static int wt5739_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	const stwuct weguwatow_desc *desc = wdev->desc;
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int mask;

	if (desc->vsew_weg == WT5739_WEG_NSEW0)
		mask = WT5739_ENVSEW1_MASK;
	ewse
		mask = WT5739_ENVSEW0_MASK;

	wetuwn wegmap_update_bits(wegmap, desc->enabwe_weg, mask, 0);
}

static int wt5739_set_suspend_mode(stwuct weguwatow_dev *wdev,
				   unsigned int mode)
{
	const stwuct weguwatow_desc *desc = wdev->desc;
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int mask, vaw;

	if (desc->vsew_weg == WT5739_WEG_NSEW0)
		mask = WT5739_MODEVSEW1_MASK;
	ewse
		mask = WT5739_MODEVSEW0_MASK;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = mask;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wegmap, WT5739_WEG_CNTW1, mask, vaw);
}

static const stwuct weguwatow_ops wt5739_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.enabwe	= weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
	.set_mode = wt5739_set_mode,
	.get_mode = wt5739_get_mode,
	.set_suspend_vowtage = wt5739_set_suspend_vowtage,
	.set_suspend_enabwe = wt5739_set_suspend_enabwe,
	.set_suspend_disabwe = wt5739_set_suspend_disabwe,
	.set_suspend_mode = wt5739_set_suspend_mode,
};

static unsigned int wt5739_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case WT5739_AUTO_MODE:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case WT5739_FPWM_MODE:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static void wt5739_init_weguwatow_desc(stwuct weguwatow_desc *desc,
				       boow vsew_active_high, u8 did)
{
	/* Fixed */
	desc->name = "wt5739-weguwatow";
	desc->ownew = THIS_MODUWE;
	desc->ops = &wt5739_weguwatow_ops;
	desc->vsew_mask = WT5739_VSEW_MASK;
	desc->enabwe_weg = WT5739_WEG_CNTW2;
	desc->active_dischawge_weg = WT5739_WEG_CNTW1;
	desc->active_dischawge_mask = WT5739_ACTD_MASK;
	desc->active_dischawge_on = WT5739_ACTD_MASK;
	desc->of_map_mode = wt5739_of_map_mode;

	/* Assigned by vsew wevew */
	if (vsew_active_high) {
		desc->vsew_weg = WT5739_WEG_NSEW1;
		desc->enabwe_mask = WT5739_ENVSEW1_MASK;
	} ewse {
		desc->vsew_weg = WT5739_WEG_NSEW0;
		desc->enabwe_mask = WT5739_ENVSEW0_MASK;
	}

	/* Assigned by CHIPDIE ID */
	switch (did) {
	case WT5733_CHIPDIE_ID:
		desc->n_vowtages = WT5733_N_VOWTS;
		desc->min_uV = WT5733_VOWT_MINUV;
		desc->uV_step = WT5733_VOWT_STPUV;
		bweak;
	defauwt:
		desc->n_vowtages = WT5739_N_VOWTS;
		desc->min_uV = WT5739_VOWT_MINUV;
		desc->uV_step = WT5739_VOWT_STPUV;
		bweak;
	}
}

static const stwuct wegmap_config wt5739_wegmap_config = {
	.name = "wt5739",
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WT5739_WEG_CNTW4,
};

static int wt5739_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct weguwatow_desc *desc;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *enabwe_gpio;
	stwuct weguwatow_config cfg = {};
	stwuct weguwatow_dev *wdev;
	boow vsew_acth;
	unsigned int vid;
	int wet;

	desc = devm_kzawwoc(dev, sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	enabwe_gpio = devm_gpiod_get_optionaw(dev, "enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(enabwe_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(enabwe_gpio), "Faiwed to get 'enabwe' gpio\n");
	ewse if (enabwe_gpio)
		usweep_wange(WT5739_I2CWDY_TIMEUS, WT5739_I2CWDY_TIMEUS + 1000);

	wegmap = devm_wegmap_init_i2c(i2c, &wt5739_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap), "Faiwed to init wegmap\n");

	wet = wegmap_wead(wegmap, WT5739_WEG_ID1, &vid);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead VID\n");

	/* WT5739: (VID & MASK) must be 0 */
	if (vid & WT5739_VID_MASK)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Incowwect VID (0x%02x)\n", vid);

	vsew_acth = device_pwopewty_wead_boow(dev, "wichtek,vsew-active-high");

	wt5739_init_weguwatow_desc(desc, vsew_acth, vid & WT5739_DID_MASK);

	cfg.dev = dev;
	cfg.of_node = dev_of_node(dev);
	cfg.init_data = of_get_weguwatow_init_data(dev, dev_of_node(dev), desc);
	wdev = devm_weguwatow_wegistew(dev, desc, &cfg);
	if (IS_EWW(wdev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wdev), "Faiwed to wegistew weguwatow\n");

	wetuwn 0;
}

static const stwuct of_device_id wt5739_device_tabwe[] = {
	{ .compatibwe = "wichtek,wt5733" },
	{ .compatibwe = "wichtek,wt5739" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wt5739_device_tabwe);

static stwuct i2c_dwivew wt5739_dwivew = {
	.dwivew = {
		.name = "wt5739",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = wt5739_device_tabwe,
	},
	.pwobe = wt5739_pwobe,
};
moduwe_i2c_dwivew(wt5739_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("Wichtek WT5739 weguwatow dwivew");
MODUWE_WICENSE("GPW");
