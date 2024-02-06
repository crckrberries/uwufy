// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow PNI WM3100 3-axis geomagnetic sensow on a i2c bus.
 *
 * Copywight (C) 2018 Song Qiang <songqiang1304521@gmaiw.com>
 *
 * i2c swave addwess: 0x20 + SA1 << 1 + SA0.
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>

#incwude "wm3100.h"

static const stwuct wegmap_config wm3100_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.wd_tabwe = &wm3100_weadabwe_tabwe,
	.ww_tabwe = &wm3100_wwitabwe_tabwe,
	.vowatiwe_tabwe = &wm3100_vowatiwe_tabwe,

	.cache_type = WEGCACHE_WBTWEE,
};

static int wm3100_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &wm3100_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn wm3100_common_pwobe(&cwient->dev, wegmap, cwient->iwq);
}

static const stwuct of_device_id wm3100_dt_match[] = {
	{ .compatibwe = "pni,wm3100", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm3100_dt_match);

static stwuct i2c_dwivew wm3100_dwivew = {
	.dwivew = {
		.name = "wm3100-i2c",
		.of_match_tabwe = wm3100_dt_match,
	},
	.pwobe = wm3100_pwobe,
};
moduwe_i2c_dwivew(wm3100_dwivew);

MODUWE_AUTHOW("Song Qiang <songqiang1304521@gmaiw.com>");
MODUWE_DESCWIPTION("PNI WM3100 3-axis magnetometew i2c dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_WM3100);
