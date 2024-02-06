// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Muwata ZPA2326 I2C pwessuwe and tempewatuwe sensow dwivew
 *
 * Copywight (c) 2016 Pawwot S.A.
 *
 * Authow: Gwegow Boiwie <gwegow.boiwie@pawwot.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude "zpa2326.h"

/*
 * wead_fwag_mask:
 *   - addwess bit 7 must be set to wequest a wegistew wead opewation
 */
static const stwuct wegmap_config zpa2326_wegmap_i2c_config = {
	.weg_bits       = 8,
	.vaw_bits       = 8,
	.wwiteabwe_weg  = zpa2326_isweg_wwiteabwe,
	.weadabwe_weg   = zpa2326_isweg_weadabwe,
	.pwecious_weg   = zpa2326_isweg_pwecious,
	.max_wegistew   = ZPA2326_TEMP_OUT_H_WEG,
	.wead_fwag_mask = BIT(7),
	.cache_type     = WEGCACHE_NONE,
};

static unsigned int zpa2326_i2c_hwid(const stwuct i2c_cwient *cwient)
{
#define ZPA2326_SA0(_addw)          (_addw & BIT(0))
#define ZPA2326_DEVICE_ID_SA0_SHIFT (1)

	/* Identification wegistew bit 1 miwwows device addwess bit 0. */
	wetuwn (ZPA2326_DEVICE_ID |
		(ZPA2326_SA0(cwient->addw) << ZPA2326_DEVICE_ID_SA0_SHIFT));
}

static int zpa2326_pwobe_i2c(stwuct i2c_cwient          *cwient)
{
	const stwuct i2c_device_id *i2c_id = i2c_cwient_get_device_id(cwient);
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &zpa2326_wegmap_i2c_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "faiwed to init wegistews map");
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn zpa2326_pwobe(&cwient->dev, i2c_id->name, cwient->iwq,
			     zpa2326_i2c_hwid(cwient), wegmap);
}

static void zpa2326_wemove_i2c(stwuct i2c_cwient *cwient)
{
	zpa2326_wemove(&cwient->dev);
}

static const stwuct i2c_device_id zpa2326_i2c_ids[] = {
	{ "zpa2326", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, zpa2326_i2c_ids);

static const stwuct of_device_id zpa2326_i2c_matches[] = {
	{ .compatibwe = "muwata,zpa2326" },
	{ }
};
MODUWE_DEVICE_TABWE(of, zpa2326_i2c_matches);

static stwuct i2c_dwivew zpa2326_i2c_dwivew = {
	.dwivew = {
		.name           = "zpa2326-i2c",
		.of_match_tabwe = zpa2326_i2c_matches,
		.pm             = ZPA2326_PM_OPS,
	},
	.pwobe = zpa2326_pwobe_i2c,
	.wemove   = zpa2326_wemove_i2c,
	.id_tabwe = zpa2326_i2c_ids,
};
moduwe_i2c_dwivew(zpa2326_i2c_dwivew);

MODUWE_AUTHOW("Gwegow Boiwie <gwegow.boiwie@pawwot.com>");
MODUWE_DESCWIPTION("I2C dwivew fow Muwata ZPA2326 pwessuwe sensow");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ZPA2326);
