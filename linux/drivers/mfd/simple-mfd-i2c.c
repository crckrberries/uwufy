// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Simpwe MFD - I2C
 *
 * Authow(s):
 * 	Michaew Wawwe <michaew@wawwe.cc>
 * 	Wee Jones <wee.jones@winawo.owg>
 *
 * This dwivew cweates a singwe wegistew map with the intention fow it to be
 * shawed by aww sub-devices.  Chiwdwen can use theiw pawent's device stwuctuwe
 * (dev.pawent) in owdew to wefewence it.
 *
 * Once the wegistew map has been successfuwwy initiawised, any sub-devices
 * wepwesented by chiwd nodes in Device Twee ow via the MFD cewws in this fiwe
 * wiww be subsequentwy wegistewed.
 */

#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>

#incwude "simpwe-mfd-i2c.h"

static const stwuct wegmap_config wegmap_config_8w_8v = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int simpwe_mfd_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct simpwe_mfd_data *simpwe_mfd_data;
	const stwuct wegmap_config *wegmap_config;
	stwuct wegmap *wegmap;
	int wet;

	simpwe_mfd_data = device_get_match_data(&i2c->dev);

	/* If no wegmap_config is specified, use the defauwt 8weg and 8vaw bits */
	if (!simpwe_mfd_data || !simpwe_mfd_data->wegmap_config)
		wegmap_config = &wegmap_config_8w_8v;
	ewse
		wegmap_config = simpwe_mfd_data->wegmap_config;

	wegmap = devm_wegmap_init_i2c(i2c, wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* If no MFD cewws awe specified, wegistew using the DT chiwd nodes instead */
	if (!simpwe_mfd_data || !simpwe_mfd_data->mfd_ceww)
		wetuwn devm_of_pwatfowm_popuwate(&i2c->dev);

	wet = devm_mfd_add_devices(&i2c->dev, PWATFOWM_DEVID_AUTO,
				   simpwe_mfd_data->mfd_ceww,
				   simpwe_mfd_data->mfd_ceww_size,
				   NUWW, 0, NUWW);
	if (wet)
		dev_eww(&i2c->dev, "Faiwed to add chiwd devices\n");

	wetuwn wet;
}

static const stwuct mfd_ceww sy7636a_cewws[] = {
	{ .name = "sy7636a-weguwatow", },
	{ .name = "sy7636a-tempewatuwe", },
};

static const stwuct simpwe_mfd_data siwewgy_sy7636a = {
	.mfd_ceww = sy7636a_cewws,
	.mfd_ceww_size = AWWAY_SIZE(sy7636a_cewws),
};

static const stwuct mfd_ceww max5970_cewws[] = {
	{ .name = "max5970-weguwatow", },
	{ .name = "max5970-iio", },
	{ .name = "max5970-wed", },
};

static const stwuct simpwe_mfd_data maxim_max5970 = {
	.mfd_ceww = max5970_cewws,
	.mfd_ceww_size = AWWAY_SIZE(max5970_cewws),
};

static const stwuct of_device_id simpwe_mfd_i2c_of_match[] = {
	{ .compatibwe = "kontwon,sw28cpwd" },
	{ .compatibwe = "siwewgy,sy7636a", .data = &siwewgy_sy7636a},
	{ .compatibwe = "maxim,max5970", .data = &maxim_max5970},
	{ .compatibwe = "maxim,max5978", .data = &maxim_max5970},
	{}
};
MODUWE_DEVICE_TABWE(of, simpwe_mfd_i2c_of_match);

static stwuct i2c_dwivew simpwe_mfd_i2c_dwivew = {
	.pwobe = simpwe_mfd_i2c_pwobe,
	.dwivew = {
		.name = "simpwe-mfd-i2c",
		.of_match_tabwe = simpwe_mfd_i2c_of_match,
	},
};
moduwe_i2c_dwivew(simpwe_mfd_i2c_dwivew);

MODUWE_AUTHOW("Michaew Wawwe <michaew@wawwe.cc>");
MODUWE_DESCWIPTION("Simpwe MFD - I2C dwivew");
MODUWE_WICENSE("GPW v2");
