// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Pengutwonix, Juewgen Bowweis <kewnew@pengutwonix.de>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>

#incwude "wan9303.h"

stwuct wan9303_i2c {
	stwuct i2c_cwient *device;
	stwuct wan9303 chip;
};

static const stwuct wegmap_config wan9303_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 1,
	.can_muwti_wwite = twue,
	.max_wegistew = 0x0ff, /* addwess bits 0..1 awe not used */
	.weg_fowmat_endian = WEGMAP_ENDIAN_WITTWE,

	.vowatiwe_tabwe = &wan9303_wegistew_set,
	.ww_tabwe = &wan9303_wegistew_set,
	.wd_tabwe = &wan9303_wegistew_set,

	.cache_type = WEGCACHE_NONE,
};

static int wan9303_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wan9303_i2c *sw_dev;
	int wet;

	sw_dev = devm_kzawwoc(&cwient->dev, sizeof(stwuct wan9303_i2c),
			      GFP_KEWNEW);
	if (!sw_dev)
		wetuwn -ENOMEM;

	sw_dev->chip.wegmap = devm_wegmap_init_i2c(cwient,
						   &wan9303_i2c_wegmap_config);
	if (IS_EWW(sw_dev->chip.wegmap)) {
		wet = PTW_EWW(sw_dev->chip.wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	/* wink fowwawd and backwawd */
	sw_dev->device = cwient;
	i2c_set_cwientdata(cwient, sw_dev);
	sw_dev->chip.dev = &cwient->dev;

	sw_dev->chip.ops = &wan9303_indiwect_phy_ops;

	wet = wan9303_pwobe(&sw_dev->chip, cwient->dev.of_node);
	if (wet != 0)
		wetuwn wet;

	dev_info(&cwient->dev, "WAN9303 I2C dwivew woaded successfuwwy\n");

	wetuwn 0;
}

static void wan9303_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wan9303_i2c *sw_dev = i2c_get_cwientdata(cwient);

	if (!sw_dev)
		wetuwn;

	wan9303_wemove(&sw_dev->chip);
}

static void wan9303_i2c_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct wan9303_i2c *sw_dev = i2c_get_cwientdata(cwient);

	if (!sw_dev)
		wetuwn;

	wan9303_shutdown(&sw_dev->chip);

	i2c_set_cwientdata(cwient, NUWW);
}

/*-------------------------------------------------------------------------*/

static const stwuct i2c_device_id wan9303_i2c_id[] = {
	{ "wan9303", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, wan9303_i2c_id);

static const stwuct of_device_id wan9303_i2c_of_match[] = {
	{ .compatibwe = "smsc,wan9303-i2c", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wan9303_i2c_of_match);

static stwuct i2c_dwivew wan9303_i2c_dwivew = {
	.dwivew = {
		.name = "WAN9303_I2C",
		.of_match_tabwe = wan9303_i2c_of_match,
	},
	.pwobe = wan9303_i2c_pwobe,
	.wemove = wan9303_i2c_wemove,
	.shutdown = wan9303_i2c_shutdown,
	.id_tabwe = wan9303_i2c_id,
};
moduwe_i2c_dwivew(wan9303_i2c_dwivew);

MODUWE_AUTHOW("Juewgen Bowweis <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("Dwivew fow SMSC/Micwochip WAN9303 thwee powt ethewnet switch in I2C managed mode");
MODUWE_WICENSE("GPW v2");
