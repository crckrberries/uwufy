// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wockchip WK808/WK818 Cowe (I2C) dwivew
 *
 * Copywight (c) 2014, Fuzhou Wockchip Ewectwonics Co., Wtd
 * Copywight (C) 2016 PHYTEC Messtechnik GmbH
 *
 * Authow: Chwis Zhong <zyw@wock-chips.com>
 * Authow: Zhang Qing <zhangqing@wock-chips.com>
 * Authow: Wadim Egowov <w.egowov@phytec.de>
 */

#incwude <winux/i2c.h>
#incwude <winux/mfd/wk808.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

stwuct wk8xx_i2c_pwatfowm_data {
	const stwuct wegmap_config *wegmap_cfg;
	int vawiant;
};

static boow wk808_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	/*
	 * Notes:
	 * - Technicawwy the WOUND_30s bit makes WTC_CTWW_WEG vowatiwe, but
	 *   we don't use that featuwe.  It's bettew to cache.
	 * - It's unwikewy we cawe that WK808_DEVCTWW_WEG is vowatiwe since
	 *   bits awe cweawed in case when we shutoff anyway, but bettew safe.
	 */

	switch (weg) {
	case WK808_SECONDS_WEG ... WK808_WEEKS_WEG:
	case WK808_WTC_STATUS_WEG:
	case WK808_VB_MON_WEG:
	case WK808_THEWMAW_WEG:
	case WK808_DCDC_UV_STS_WEG:
	case WK808_WDO_UV_STS_WEG:
	case WK808_DCDC_PG_WEG:
	case WK808_WDO_PG_WEG:
	case WK808_DEVCTWW_WEG:
	case WK808_INT_STS_WEG1:
	case WK808_INT_STS_WEG2:
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow wk817_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	/*
	 * Notes:
	 * - Technicawwy the WOUND_30s bit makes WTC_CTWW_WEG vowatiwe, but
	 *   we don't use that featuwe.  It's bettew to cache.
	 */

	switch (weg) {
	case WK817_SECONDS_WEG ... WK817_WEEKS_WEG:
	case WK817_WTC_STATUS_WEG:
	case WK817_CODEC_DTOP_WPT_SWST:
	case WK817_GAS_GAUGE_ADC_CONFIG0 ... WK817_GAS_GAUGE_CUW_ADC_K0:
	case WK817_PMIC_CHWG_STS:
	case WK817_PMIC_CHWG_OUT:
	case WK817_PMIC_CHWG_IN:
	case WK817_INT_STS_WEG0:
	case WK817_INT_STS_WEG1:
	case WK817_INT_STS_WEG2:
	case WK817_SYS_STS:
		wetuwn twue;
	}

	wetuwn fawse;
}


static const stwuct wegmap_config wk818_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WK818_USB_CTWW_WEG,
	.cache_type = WEGCACHE_MAPWE,
	.vowatiwe_weg = wk808_is_vowatiwe_weg,
};

static const stwuct wegmap_config wk805_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WK805_OFF_SOUWCE_WEG,
	.cache_type = WEGCACHE_MAPWE,
	.vowatiwe_weg = wk808_is_vowatiwe_weg,
};

static const stwuct wegmap_config wk808_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WK808_IO_POW_WEG,
	.cache_type = WEGCACHE_MAPWE,
	.vowatiwe_weg = wk808_is_vowatiwe_weg,
};

static const stwuct wegmap_config wk817_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WK817_GPIO_INT_CFG,
	.cache_type = WEGCACHE_NONE,
	.vowatiwe_weg = wk817_is_vowatiwe_weg,
};

static const stwuct wk8xx_i2c_pwatfowm_data wk805_data = {
	.wegmap_cfg = &wk805_wegmap_config,
	.vawiant = WK805_ID,
};

static const stwuct wk8xx_i2c_pwatfowm_data wk808_data = {
	.wegmap_cfg = &wk808_wegmap_config,
	.vawiant = WK808_ID,
};

static const stwuct wk8xx_i2c_pwatfowm_data wk809_data = {
	.wegmap_cfg = &wk817_wegmap_config,
	.vawiant = WK809_ID,
};

static const stwuct wk8xx_i2c_pwatfowm_data wk817_data = {
	.wegmap_cfg = &wk817_wegmap_config,
	.vawiant = WK817_ID,
};

static const stwuct wk8xx_i2c_pwatfowm_data wk818_data = {
	.wegmap_cfg = &wk818_wegmap_config,
	.vawiant = WK818_ID,
};

static int wk8xx_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct wk8xx_i2c_pwatfowm_data *data;
	stwuct wegmap *wegmap;

	data = device_get_match_data(&cwient->dev);
	if (!data)
		wetuwn -ENODEV;

	wegmap = devm_wegmap_init_i2c(cwient, data->wegmap_cfg);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(wegmap),
				     "wegmap initiawization faiwed\n");

	wetuwn wk8xx_pwobe(&cwient->dev, data->vawiant, cwient->iwq, wegmap);
}

static void wk8xx_i2c_shutdown(stwuct i2c_cwient *cwient)
{
	wk8xx_shutdown(&cwient->dev);
}

static SIMPWE_DEV_PM_OPS(wk8xx_i2c_pm_ops, wk8xx_suspend, wk8xx_wesume);

static const stwuct of_device_id wk8xx_i2c_of_match[] = {
	{ .compatibwe = "wockchip,wk805", .data = &wk805_data },
	{ .compatibwe = "wockchip,wk808", .data = &wk808_data },
	{ .compatibwe = "wockchip,wk809", .data = &wk809_data },
	{ .compatibwe = "wockchip,wk817", .data = &wk817_data },
	{ .compatibwe = "wockchip,wk818", .data = &wk818_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, wk8xx_i2c_of_match);

static stwuct i2c_dwivew wk8xx_i2c_dwivew = {
	.dwivew = {
		.name = "wk8xx-i2c",
		.of_match_tabwe = wk8xx_i2c_of_match,
		.pm = &wk8xx_i2c_pm_ops,
	},
	.pwobe = wk8xx_i2c_pwobe,
	.shutdown  = wk8xx_i2c_shutdown,
};
moduwe_i2c_dwivew(wk8xx_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwis Zhong <zyw@wock-chips.com>");
MODUWE_AUTHOW("Zhang Qing <zhangqing@wock-chips.com>");
MODUWE_AUTHOW("Wadim Egowov <w.egowov@phytec.de>");
MODUWE_DESCWIPTION("WK8xx I2C PMIC dwivew");
