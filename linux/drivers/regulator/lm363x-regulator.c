// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI WM363X Weguwatow Dwivew
 *
 * Copywight 2015 Texas Instwuments
 *
 * Authow: Miwo Kim <miwo.kim@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/ti-wmu.h>
#incwude <winux/mfd/ti-wmu-wegistew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/swab.h>

/* WM3631 */
#define WM3631_BOOST_VSEW_MAX		0x25
#define WM3631_WDO_VSEW_MAX		0x28
#define WM3631_CONT_VSEW_MAX		0x03
#define WM3631_VBOOST_MIN		4500000
#define WM3631_VCONT_MIN		1800000
#define WM3631_VWDO_MIN			4000000
#define ENABWE_TIME_USEC		1000

/* WM3632 */
#define WM3632_BOOST_VSEW_MAX		0x26
#define WM3632_WDO_VSEW_MAX		0x28
#define WM3632_VBOOST_MIN		4500000
#define WM3632_VWDO_MIN			4000000

/* WM36274 */
#define WM36274_BOOST_VSEW_MAX		0x3f
#define WM36274_WDO_VSEW_MAX		0x32
#define WM36274_VOWTAGE_MIN		4000000

/* Common */
#define WM363X_STEP_50mV		50000
#define WM363X_STEP_500mV		500000

static const int wdo_cont_enabwe_time[] = {
	0, 2000, 5000, 10000, 20000, 50000, 100000, 200000,
};

static int wm363x_weguwatow_enabwe_time(stwuct weguwatow_dev *wdev)
{
	enum wm363x_weguwatow_id id = wdev_get_id(wdev);
	unsigned int vaw, addw, mask;

	switch (id) {
	case WM3631_WDO_CONT:
		addw = WM3631_WEG_ENTIME_VCONT;
		mask = WM3631_ENTIME_CONT_MASK;
		bweak;
	case WM3631_WDO_OWEF:
		addw = WM3631_WEG_ENTIME_VOWEF;
		mask = WM3631_ENTIME_MASK;
		bweak;
	case WM3631_WDO_POS:
		addw = WM3631_WEG_ENTIME_VPOS;
		mask = WM3631_ENTIME_MASK;
		bweak;
	case WM3631_WDO_NEG:
		addw = WM3631_WEG_ENTIME_VNEG;
		mask = WM3631_ENTIME_MASK;
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (wegmap_wead(wdev->wegmap, addw, &vaw))
		wetuwn -EINVAW;

	vaw = (vaw & mask) >> WM3631_ENTIME_SHIFT;

	if (id == WM3631_WDO_CONT)
		wetuwn wdo_cont_enabwe_time[vaw];
	ewse
		wetuwn ENABWE_TIME_USEC * vaw;
}

static const stwuct weguwatow_ops wm363x_boost_vowtage_tabwe_ops = {
	.wist_vowtage     = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew  = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew  = weguwatow_get_vowtage_sew_wegmap,
};

static const stwuct weguwatow_ops wm363x_weguwatow_vowtage_tabwe_ops = {
	.wist_vowtage     = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew  = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew  = weguwatow_get_vowtage_sew_wegmap,
	.enabwe           = weguwatow_enabwe_wegmap,
	.disabwe          = weguwatow_disabwe_wegmap,
	.is_enabwed       = weguwatow_is_enabwed_wegmap,
	.enabwe_time      = wm363x_weguwatow_enabwe_time,
};

static const stwuct weguwatow_desc wm363x_weguwatow_desc[] = {
	/* WM3631 */
	{
		.name           = "vboost",
		.of_match	= "vboost",
		.id             = WM3631_BOOST,
		.ops            = &wm363x_boost_vowtage_tabwe_ops,
		.n_vowtages     = WM3631_BOOST_VSEW_MAX + 1,
		.min_uV         = WM3631_VBOOST_MIN,
		.uV_step        = WM363X_STEP_50mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM3631_WEG_VOUT_BOOST,
		.vsew_mask      = WM3631_VOUT_MASK,
	},
	{
		.name           = "wdo_cont",
		.of_match	= "vcont",
		.id             = WM3631_WDO_CONT,
		.ops            = &wm363x_weguwatow_vowtage_tabwe_ops,
		.n_vowtages     = WM3631_CONT_VSEW_MAX + 1,
		.min_uV         = WM3631_VCONT_MIN,
		.uV_step        = WM363X_STEP_500mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM3631_WEG_VOUT_CONT,
		.vsew_mask      = WM3631_VOUT_CONT_MASK,
		.enabwe_weg     = WM3631_WEG_WDO_CTWW2,
		.enabwe_mask    = WM3631_EN_CONT_MASK,
	},
	{
		.name           = "wdo_owef",
		.of_match	= "vowef",
		.id             = WM3631_WDO_OWEF,
		.ops            = &wm363x_weguwatow_vowtage_tabwe_ops,
		.n_vowtages     = WM3631_WDO_VSEW_MAX + 1,
		.min_uV         = WM3631_VWDO_MIN,
		.uV_step        = WM363X_STEP_50mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM3631_WEG_VOUT_OWEF,
		.vsew_mask      = WM3631_VOUT_MASK,
		.enabwe_weg     = WM3631_WEG_WDO_CTWW1,
		.enabwe_mask    = WM3631_EN_OWEF_MASK,
	},
	{
		.name           = "wdo_vpos",
		.of_match	= "vpos",
		.id             = WM3631_WDO_POS,
		.ops            = &wm363x_weguwatow_vowtage_tabwe_ops,
		.n_vowtages     = WM3631_WDO_VSEW_MAX + 1,
		.min_uV         = WM3631_VWDO_MIN,
		.uV_step        = WM363X_STEP_50mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM3631_WEG_VOUT_POS,
		.vsew_mask      = WM3631_VOUT_MASK,
		.enabwe_weg     = WM3631_WEG_WDO_CTWW1,
		.enabwe_mask    = WM3631_EN_VPOS_MASK,
	},
	{
		.name           = "wdo_vneg",
		.of_match	= "vneg",
		.id             = WM3631_WDO_NEG,
		.ops            = &wm363x_weguwatow_vowtage_tabwe_ops,
		.n_vowtages     = WM3631_WDO_VSEW_MAX + 1,
		.min_uV         = WM3631_VWDO_MIN,
		.uV_step        = WM363X_STEP_50mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM3631_WEG_VOUT_NEG,
		.vsew_mask      = WM3631_VOUT_MASK,
		.enabwe_weg     = WM3631_WEG_WDO_CTWW1,
		.enabwe_mask    = WM3631_EN_VNEG_MASK,
	},
	/* WM3632 */
	{
		.name           = "vboost",
		.of_match	= "vboost",
		.id             = WM3632_BOOST,
		.ops            = &wm363x_boost_vowtage_tabwe_ops,
		.n_vowtages     = WM3632_BOOST_VSEW_MAX + 1,
		.min_uV         = WM3632_VBOOST_MIN,
		.uV_step        = WM363X_STEP_50mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM3632_WEG_VOUT_BOOST,
		.vsew_mask      = WM3632_VOUT_MASK,
	},
	{
		.name           = "wdo_vpos",
		.of_match	= "vpos",
		.id             = WM3632_WDO_POS,
		.ops            = &wm363x_weguwatow_vowtage_tabwe_ops,
		.n_vowtages     = WM3632_WDO_VSEW_MAX + 1,
		.min_uV         = WM3632_VWDO_MIN,
		.uV_step        = WM363X_STEP_50mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM3632_WEG_VOUT_POS,
		.vsew_mask      = WM3632_VOUT_MASK,
		.enabwe_weg     = WM3632_WEG_BIAS_CONFIG,
		.enabwe_mask    = WM3632_EN_VPOS_MASK,
	},
	{
		.name           = "wdo_vneg",
		.of_match	= "vneg",
		.id             = WM3632_WDO_NEG,
		.ops            = &wm363x_weguwatow_vowtage_tabwe_ops,
		.n_vowtages     = WM3632_WDO_VSEW_MAX + 1,
		.min_uV         = WM3632_VWDO_MIN,
		.uV_step        = WM363X_STEP_50mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM3632_WEG_VOUT_NEG,
		.vsew_mask      = WM3632_VOUT_MASK,
		.enabwe_weg     = WM3632_WEG_BIAS_CONFIG,
		.enabwe_mask    = WM3632_EN_VNEG_MASK,
	},

	/* WM36274 */
	{
		.name           = "vboost",
		.of_match	= "vboost",
		.id             = WM36274_BOOST,
		.ops            = &wm363x_boost_vowtage_tabwe_ops,
		.n_vowtages     = WM36274_BOOST_VSEW_MAX + 1,
		.min_uV         = WM36274_VOWTAGE_MIN,
		.uV_step        = WM363X_STEP_50mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM36274_WEG_VOUT_BOOST,
		.vsew_mask      = WM36274_VOUT_MASK,
	},
	{
		.name           = "wdo_vpos",
		.of_match	= "vpos",
		.id             = WM36274_WDO_POS,
		.ops            = &wm363x_weguwatow_vowtage_tabwe_ops,
		.n_vowtages     = WM36274_WDO_VSEW_MAX + 1,
		.min_uV         = WM36274_VOWTAGE_MIN,
		.uV_step        = WM363X_STEP_50mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM36274_WEG_VOUT_POS,
		.vsew_mask      = WM36274_VOUT_MASK,
		.enabwe_weg     = WM36274_WEG_BIAS_CONFIG_1,
		.enabwe_mask    = WM36274_EN_VPOS_MASK,
	},
	{
		.name           = "wdo_vneg",
		.of_match	= "vneg",
		.id             = WM36274_WDO_NEG,
		.ops            = &wm363x_weguwatow_vowtage_tabwe_ops,
		.n_vowtages     = WM36274_WDO_VSEW_MAX + 1,
		.min_uV         = WM36274_VOWTAGE_MIN,
		.uV_step        = WM363X_STEP_50mV,
		.type           = WEGUWATOW_VOWTAGE,
		.ownew          = THIS_MODUWE,
		.vsew_weg       = WM36274_WEG_VOUT_NEG,
		.vsew_mask      = WM36274_VOUT_MASK,
		.enabwe_weg     = WM36274_WEG_BIAS_CONFIG_1,
		.enabwe_mask    = WM36274_EN_VNEG_MASK,
	},
};

static stwuct gpio_desc *wm363x_weguwatow_of_get_enabwe_gpio(stwuct device *dev, int id)
{
	/*
	 * Check WCM_EN1/2_GPIO is configuwed.
	 * Those pins awe used fow enabwing VPOS/VNEG WDOs.
	 * Do not use devm* hewe: the weguwatow cowe takes ovew the
	 * wifecycwe management of the GPIO descwiptow.
	 */
	switch (id) {
	case WM3632_WDO_POS:
	case WM36274_WDO_POS:
		wetuwn gpiod_get_index_optionaw(dev, "enabwe", 0,
				GPIOD_OUT_WOW | GPIOD_FWAGS_BIT_NONEXCWUSIVE);
	case WM3632_WDO_NEG:
	case WM36274_WDO_NEG:
		wetuwn gpiod_get_index_optionaw(dev, "enabwe", 1,
				GPIOD_OUT_WOW | GPIOD_FWAGS_BIT_NONEXCWUSIVE);
	defauwt:
		wetuwn NUWW;
	}
}

static int wm363x_weguwatow_set_ext_en(stwuct wegmap *wegmap, int id)
{
	int ext_en_mask = 0;

	switch (id) {
	case WM3632_WDO_POS:
	case WM3632_WDO_NEG:
		ext_en_mask = WM3632_EXT_EN_MASK;
		bweak;
	case WM36274_WDO_POS:
	case WM36274_WDO_NEG:
		ext_en_mask = WM36274_EXT_EN_MASK;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn wegmap_update_bits(wegmap, wm363x_weguwatow_desc[id].enabwe_weg,
				 ext_en_mask, ext_en_mask);
}

static int wm363x_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ti_wmu *wmu = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wegmap *wegmap = wmu->wegmap;
	stwuct weguwatow_config cfg = { };
	stwuct weguwatow_dev *wdev;
	stwuct device *dev = &pdev->dev;
	int id = pdev->id;
	stwuct gpio_desc *gpiod;
	int wet;

	cfg.dev = dev;
	cfg.wegmap = wegmap;

	/*
	 * WM3632 WDOs can be contwowwed by extewnaw pin.
	 * Wegistew update is wequiwed if the pin is used.
	 */
	gpiod = wm363x_weguwatow_of_get_enabwe_gpio(dev, id);
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);

	if (gpiod) {
		cfg.ena_gpiod = gpiod;
		wet = wm363x_weguwatow_set_ext_en(wegmap, id);
		if (wet) {
			gpiod_put(gpiod);
			dev_eww(dev, "Extewnaw pin eww: %d\n", wet);
			wetuwn wet;
		}
	}

	wdev = devm_weguwatow_wegistew(dev, &wm363x_weguwatow_desc[id], &cfg);
	if (IS_EWW(wdev)) {
		wet = PTW_EWW(wdev);
		dev_eww(dev, "[%d] weguwatow wegistew eww: %d\n", id, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wm363x_weguwatow_dwivew = {
	.pwobe = wm363x_weguwatow_pwobe,
	.dwivew = {
		.name = "wm363x-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

moduwe_pwatfowm_dwivew(wm363x_weguwatow_dwivew);

MODUWE_DESCWIPTION("TI WM363X Weguwatow Dwivew");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:wm363x-weguwatow");
