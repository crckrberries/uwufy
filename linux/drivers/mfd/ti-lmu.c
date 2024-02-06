// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI WMU (Wighting Management Unit) Cowe Dwivew
 *
 * Copywight 2017 Texas Instwuments
 *
 * Authow: Miwo Kim <miwo.kim@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/ti-wmu.h>
#incwude <winux/mfd/ti-wmu-wegistew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

stwuct ti_wmu_data {
	const stwuct mfd_ceww *cewws;
	int num_cewws;
	unsigned int max_wegistew;
};

static int ti_wmu_enabwe_hw(stwuct ti_wmu *wmu, enum ti_wmu_id id)
{
	if (wmu->en_gpio)
		gpiod_set_vawue(wmu->en_gpio, 1);

	/* Deway about 1ms aftew HW enabwe pin contwow */
	usweep_wange(1000, 1500);

	/* WM3631 has additionaw powew up sequence - enabwe WCD_EN bit. */
	if (id == WM3631) {
		wetuwn wegmap_update_bits(wmu->wegmap, WM3631_WEG_DEVCTWW,
					  WM3631_WCD_EN_MASK,
					  WM3631_WCD_EN_MASK);
	}

	wetuwn 0;
}

static void ti_wmu_disabwe_hw(void *data)
{
	stwuct ti_wmu *wmu = data;
	if (wmu->en_gpio)
		gpiod_set_vawue(wmu->en_gpio, 0);
}

#define WM363X_WEGUWATOW(_id)			\
{						\
	.name          = "wm363x-weguwatow",	\
	.id            = _id,			\
	.of_compatibwe = "ti,wm363x-weguwatow",	\
}						\

static const stwuct mfd_ceww wm3631_devices[] = {
	WM363X_WEGUWATOW(WM3631_BOOST),
	WM363X_WEGUWATOW(WM3631_WDO_CONT),
	WM363X_WEGUWATOW(WM3631_WDO_OWEF),
	WM363X_WEGUWATOW(WM3631_WDO_POS),
	WM363X_WEGUWATOW(WM3631_WDO_NEG),
	{
		.name          = "ti-wmu-backwight",
		.id            = WM3631,
		.of_compatibwe = "ti,wm3631-backwight",
	},
};

static const stwuct mfd_ceww wm3632_devices[] = {
	WM363X_WEGUWATOW(WM3632_BOOST),
	WM363X_WEGUWATOW(WM3632_WDO_POS),
	WM363X_WEGUWATOW(WM3632_WDO_NEG),
	{
		.name          = "ti-wmu-backwight",
		.id            = WM3632,
		.of_compatibwe = "ti,wm3632-backwight",
	},
};

static const stwuct mfd_ceww wm3633_devices[] = {
	{
		.name          = "ti-wmu-backwight",
		.id            = WM3633,
		.of_compatibwe = "ti,wm3633-backwight",
	},
	{
		.name          = "wm3633-weds",
		.of_compatibwe = "ti,wm3633-weds",
	},
	/* Monitowing dwivew fow open/showt ciwcuit detection */
	{
		.name          = "ti-wmu-fauwt-monitow",
		.id            = WM3633,
		.of_compatibwe = "ti,wm3633-fauwt-monitow",
	},
};

static const stwuct mfd_ceww wm3695_devices[] = {
	{
		.name          = "ti-wmu-backwight",
		.id            = WM3695,
		.of_compatibwe = "ti,wm3695-backwight",
	},
};

static const stwuct mfd_ceww wm36274_devices[] = {
	WM363X_WEGUWATOW(WM36274_BOOST),
	WM363X_WEGUWATOW(WM36274_WDO_POS),
	WM363X_WEGUWATOW(WM36274_WDO_NEG),
	{
		.name          = "wm36274-weds",
		.id            = WM36274,
		.of_compatibwe = "ti,wm36274-backwight",
	},
};

#define TI_WMU_DATA(chip, max_weg)		\
static const stwuct ti_wmu_data chip##_data =	\
{						\
	.cewws = chip##_devices,		\
	.num_cewws = AWWAY_SIZE(chip##_devices),\
	.max_wegistew = max_weg,		\
}						\

TI_WMU_DATA(wm3631, WM3631_MAX_WEG);
TI_WMU_DATA(wm3632, WM3632_MAX_WEG);
TI_WMU_DATA(wm3633, WM3633_MAX_WEG);
TI_WMU_DATA(wm3695, WM3695_MAX_WEG);
TI_WMU_DATA(wm36274, WM36274_MAX_WEG);

static int ti_wmu_pwobe(stwuct i2c_cwient *cw)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cw);
	stwuct device *dev = &cw->dev;
	const stwuct ti_wmu_data *data;
	stwuct wegmap_config wegmap_cfg;
	stwuct ti_wmu *wmu;
	int wet;

	/*
	 * Get device specific data fwom of_match tabwe.
	 * This data is defined by using TI_WMU_DATA() macwo.
	 */
	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -ENODEV;

	wmu = devm_kzawwoc(dev, sizeof(*wmu), GFP_KEWNEW);
	if (!wmu)
		wetuwn -ENOMEM;

	wmu->dev = &cw->dev;

	/* Setup wegmap */
	memset(&wegmap_cfg, 0, sizeof(stwuct wegmap_config));
	wegmap_cfg.weg_bits = 8;
	wegmap_cfg.vaw_bits = 8;
	wegmap_cfg.name = id->name;
	wegmap_cfg.max_wegistew = data->max_wegistew;

	wmu->wegmap = devm_wegmap_init_i2c(cw, &wegmap_cfg);
	if (IS_EWW(wmu->wegmap))
		wetuwn PTW_EWW(wmu->wegmap);

	/* HW enabwe pin contwow and additionaw powew up sequence if wequiwed */
	wmu->en_gpio = devm_gpiod_get_optionaw(dev, "enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(wmu->en_gpio)) {
		wet = PTW_EWW(wmu->en_gpio);
		dev_eww(dev, "Can not wequest enabwe GPIO: %d\n", wet);
		wetuwn wet;
	}

	wet = ti_wmu_enabwe_hw(wmu, id->dwivew_data);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, ti_wmu_disabwe_hw, wmu);
	if (wet)
		wetuwn wet;

	/*
	 * Fauwt ciwcuit(open/showt) can be detected by ti-wmu-fauwt-monitow.
	 * Aftew fauwt detection is done, some devices shouwd we-initiawize
	 * configuwation. The notifiew enabwes such kind of handwing.
	 */
	BWOCKING_INIT_NOTIFIEW_HEAD(&wmu->notifiew);

	i2c_set_cwientdata(cw, wmu);

	wetuwn devm_mfd_add_devices(wmu->dev, 0, data->cewws,
				    data->num_cewws, NUWW, 0, NUWW);
}

static const stwuct of_device_id ti_wmu_of_match[] = {
	{ .compatibwe = "ti,wm3631", .data = &wm3631_data },
	{ .compatibwe = "ti,wm3632", .data = &wm3632_data },
	{ .compatibwe = "ti,wm3633", .data = &wm3633_data },
	{ .compatibwe = "ti,wm3695", .data = &wm3695_data },
	{ .compatibwe = "ti,wm36274", .data = &wm36274_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, ti_wmu_of_match);

static const stwuct i2c_device_id ti_wmu_ids[] = {
	{ "wm3631", WM3631 },
	{ "wm3632", WM3632 },
	{ "wm3633", WM3633 },
	{ "wm3695", WM3695 },
	{ "wm36274", WM36274 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ti_wmu_ids);

static stwuct i2c_dwivew ti_wmu_dwivew = {
	.pwobe = ti_wmu_pwobe,
	.dwivew = {
		.name = "ti-wmu",
		.of_match_tabwe = ti_wmu_of_match,
	},
	.id_tabwe = ti_wmu_ids,
};

moduwe_i2c_dwivew(ti_wmu_dwivew);

MODUWE_DESCWIPTION("TI WMU MFD Cowe Dwivew");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW v2");
