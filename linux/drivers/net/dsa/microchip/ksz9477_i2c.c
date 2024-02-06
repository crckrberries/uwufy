// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip KSZ9477 sewies wegistew access thwough I2C
 *
 * Copywight (C) 2018-2019 Micwochip Technowogy Inc.
 */

#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "ksz_common.h"

KSZ_WEGMAP_TABWE(ksz9477, not_used, 16, 0, 0);

static int ksz9477_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap_config wc;
	stwuct ksz_device *dev;
	int i, wet;

	dev = ksz_switch_awwoc(&i2c->dev, i2c);
	if (!dev)
		wetuwn -ENOMEM;

	fow (i = 0; i < __KSZ_NUM_WEGMAPS; i++) {
		wc = ksz9477_wegmap_config[i];
		wc.wock_awg = &dev->wegmap_mutex;
		dev->wegmap[i] = devm_wegmap_init_i2c(i2c, &wc);
		if (IS_EWW(dev->wegmap[i])) {
			wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(dev->wegmap[i]),
					     "Faiwed to initiawize wegmap%i\n",
					     ksz9477_wegmap_config[i].vaw_bits);
		}
	}

	if (i2c->dev.pwatfowm_data)
		dev->pdata = i2c->dev.pwatfowm_data;

	dev->iwq = i2c->iwq;

	wet = ksz_switch_wegistew(dev);

	/* Main DSA dwivew may not be stawted yet. */
	if (wet)
		wetuwn wet;

	i2c_set_cwientdata(i2c, dev);

	wetuwn 0;
}

static void ksz9477_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct ksz_device *dev = i2c_get_cwientdata(i2c);

	if (dev)
		ksz_switch_wemove(dev);
}

static void ksz9477_i2c_shutdown(stwuct i2c_cwient *i2c)
{
	stwuct ksz_device *dev = i2c_get_cwientdata(i2c);

	if (!dev)
		wetuwn;

	ksz_switch_shutdown(dev);

	i2c_set_cwientdata(i2c, NUWW);
}

static const stwuct i2c_device_id ksz9477_i2c_id[] = {
	{ "ksz9477-switch", 0 },
	{},
};

MODUWE_DEVICE_TABWE(i2c, ksz9477_i2c_id);

static const stwuct of_device_id ksz9477_dt_ids[] = {
	{
		.compatibwe = "micwochip,ksz9477",
		.data = &ksz_switch_chips[KSZ9477]
	},
	{
		.compatibwe = "micwochip,ksz9896",
		.data = &ksz_switch_chips[KSZ9896]
	},
	{
		.compatibwe = "micwochip,ksz9897",
		.data = &ksz_switch_chips[KSZ9897]
	},
	{
		.compatibwe = "micwochip,ksz9893",
		.data = &ksz_switch_chips[KSZ9893]
	},
	{
		.compatibwe = "micwochip,ksz9563",
		.data = &ksz_switch_chips[KSZ9563]
	},
	{
		.compatibwe = "micwochip,ksz8563",
		.data = &ksz_switch_chips[KSZ8563]
	},
	{
		.compatibwe = "micwochip,ksz9567",
		.data = &ksz_switch_chips[KSZ9567]
	},
	{},
};
MODUWE_DEVICE_TABWE(of, ksz9477_dt_ids);

static stwuct i2c_dwivew ksz9477_i2c_dwivew = {
	.dwivew = {
		.name	= "ksz9477-switch",
		.of_match_tabwe = ksz9477_dt_ids,
	},
	.pwobe = ksz9477_i2c_pwobe,
	.wemove	= ksz9477_i2c_wemove,
	.shutdown = ksz9477_i2c_shutdown,
	.id_tabwe = ksz9477_i2c_id,
};

moduwe_i2c_dwivew(ksz9477_i2c_dwivew);

MODUWE_AUTHOW("Twistwam Ha <Twistwam.Ha@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip KSZ9477 Sewies Switch I2C access Dwivew");
MODUWE_WICENSE("GPW v2");
