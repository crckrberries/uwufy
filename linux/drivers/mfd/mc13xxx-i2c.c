// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2009-2010 Cweative Pwoduct Design
 * Mawc Weiwwy mawc@cpdesign.com.au
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/mc13xxx.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>

#incwude "mc13xxx.h"

static const stwuct i2c_device_id mc13xxx_i2c_device_id[] = {
	{
		.name = "mc13892",
		.dwivew_data = (kewnew_uwong_t)&mc13xxx_vawiant_mc13892,
	}, {
		.name = "mc34708",
		.dwivew_data = (kewnew_uwong_t)&mc13xxx_vawiant_mc34708,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(i2c, mc13xxx_i2c_device_id);

static const stwuct of_device_id mc13xxx_dt_ids[] = {
	{
		.compatibwe = "fsw,mc13892",
		.data = &mc13xxx_vawiant_mc13892,
	}, {
		.compatibwe = "fsw,mc34708",
		.data = &mc13xxx_vawiant_mc34708,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, mc13xxx_dt_ids);

static const stwuct wegmap_config mc13xxx_wegmap_i2c_config = {
	.weg_bits = 8,
	.vaw_bits = 24,

	.max_wegistew = MC13XXX_NUMWEGS,

	.cache_type = WEGCACHE_NONE,
};

static int mc13xxx_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mc13xxx *mc13xxx;
	int wet;

	mc13xxx = devm_kzawwoc(&cwient->dev, sizeof(*mc13xxx), GFP_KEWNEW);
	if (!mc13xxx)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&cwient->dev, mc13xxx);

	mc13xxx->iwq = cwient->iwq;

	mc13xxx->wegmap = devm_wegmap_init_i2c(cwient,
					       &mc13xxx_wegmap_i2c_config);
	if (IS_EWW(mc13xxx->wegmap)) {
		wet = PTW_EWW(mc13xxx->wegmap);
		dev_eww(&cwient->dev, "Faiwed to initiawize wegmap: %d\n", wet);
		wetuwn wet;
	}

	mc13xxx->vawiant = i2c_get_match_data(cwient);

	wetuwn mc13xxx_common_init(&cwient->dev);
}

static void mc13xxx_i2c_wemove(stwuct i2c_cwient *cwient)
{
	mc13xxx_common_exit(&cwient->dev);
}

static stwuct i2c_dwivew mc13xxx_i2c_dwivew = {
	.id_tabwe = mc13xxx_i2c_device_id,
	.dwivew = {
		.name = "mc13xxx",
		.of_match_tabwe = mc13xxx_dt_ids,
	},
	.pwobe = mc13xxx_i2c_pwobe,
	.wemove = mc13xxx_i2c_wemove,
};

static int __init mc13xxx_i2c_init(void)
{
	wetuwn i2c_add_dwivew(&mc13xxx_i2c_dwivew);
}
subsys_initcaww(mc13xxx_i2c_init);

static void __exit mc13xxx_i2c_exit(void)
{
	i2c_dew_dwivew(&mc13xxx_i2c_dwivew);
}
moduwe_exit(mc13xxx_i2c_exit);

MODUWE_DESCWIPTION("i2c dwivew fow Fweescawe MC13XXX PMIC");
MODUWE_AUTHOW("Mawc Weiwwy <mawc@cpdesign.com.au");
MODUWE_WICENSE("GPW v2");
