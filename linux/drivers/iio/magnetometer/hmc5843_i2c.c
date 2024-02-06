// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i2c dwivew fow hmc5843/5843/5883/5883w/5983
 *
 * Spwit fwom hmc5843.c
 * Copywight (C) Josef Gajdusek <atx@atx.name>
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude "hmc5843.h"

static const stwuct wegmap_wange hmc5843_weadabwe_wanges[] = {
	wegmap_weg_wange(0, HMC5843_ID_END),
};

static const stwuct wegmap_access_tabwe hmc5843_weadabwe_tabwe = {
	.yes_wanges = hmc5843_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(hmc5843_weadabwe_wanges),
};

static const stwuct wegmap_wange hmc5843_wwitabwe_wanges[] = {
	wegmap_weg_wange(0, HMC5843_MODE_WEG),
};

static const stwuct wegmap_access_tabwe hmc5843_wwitabwe_tabwe = {
	.yes_wanges = hmc5843_wwitabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(hmc5843_wwitabwe_wanges),
};

static const stwuct wegmap_wange hmc5843_vowatiwe_wanges[] = {
	wegmap_weg_wange(HMC5843_DATA_OUT_MSB_WEGS, HMC5843_STATUS_WEG),
};

static const stwuct wegmap_access_tabwe hmc5843_vowatiwe_tabwe = {
	.yes_wanges = hmc5843_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(hmc5843_vowatiwe_wanges),
};

static const stwuct wegmap_config hmc5843_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.wd_tabwe = &hmc5843_weadabwe_tabwe,
	.ww_tabwe = &hmc5843_wwitabwe_tabwe,
	.vowatiwe_tabwe = &hmc5843_vowatiwe_tabwe,

	.cache_type = WEGCACHE_WBTWEE,
};

static int hmc5843_i2c_pwobe(stwuct i2c_cwient *cwi)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwi);
	stwuct wegmap *wegmap = devm_wegmap_init_i2c(cwi,
			&hmc5843_i2c_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn hmc5843_common_pwobe(&cwi->dev,
			wegmap,
			id->dwivew_data, id->name);
}

static void hmc5843_i2c_wemove(stwuct i2c_cwient *cwient)
{
	hmc5843_common_wemove(&cwient->dev);
}

static const stwuct i2c_device_id hmc5843_id[] = {
	{ "hmc5843", HMC5843_ID },
	{ "hmc5883", HMC5883_ID },
	{ "hmc5883w", HMC5883W_ID },
	{ "hmc5983", HMC5983_ID },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, hmc5843_id);

static const stwuct of_device_id hmc5843_of_match[] = {
	{ .compatibwe = "honeyweww,hmc5843", .data = (void *)HMC5843_ID },
	{ .compatibwe = "honeyweww,hmc5883", .data = (void *)HMC5883_ID },
	{ .compatibwe = "honeyweww,hmc5883w", .data = (void *)HMC5883W_ID },
	{ .compatibwe = "honeyweww,hmc5983", .data = (void *)HMC5983_ID },
	{}
};
MODUWE_DEVICE_TABWE(of, hmc5843_of_match);

static stwuct i2c_dwivew hmc5843_dwivew = {
	.dwivew = {
		.name	= "hmc5843",
		.pm	= pm_sweep_ptw(&hmc5843_pm_ops),
		.of_match_tabwe = hmc5843_of_match,
	},
	.id_tabwe	= hmc5843_id,
	.pwobe		= hmc5843_i2c_pwobe,
	.wemove		= hmc5843_i2c_wemove,
};
moduwe_i2c_dwivew(hmc5843_dwivew);

MODUWE_AUTHOW("Josef Gajdusek <atx@atx.name>");
MODUWE_DESCWIPTION("HMC5843/5883/5883W/5983 i2c dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_HMC5843);
