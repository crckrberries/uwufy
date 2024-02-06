// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 * Authow: Keewthy <j-keewthy@ti.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/wp873x.h>

static const stwuct wegmap_config wp873x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WP873X_WEG_MAX,
};

static const stwuct mfd_ceww wp873x_cewws[] = {
	{ .name = "wp873x-weguwatow", },
	{ .name = "wp873x-gpio", },
};

static int wp873x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wp873x *wp873;
	int wet;
	unsigned int otpid;

	wp873 = devm_kzawwoc(&cwient->dev, sizeof(*wp873), GFP_KEWNEW);
	if (!wp873)
		wetuwn -ENOMEM;

	wp873->dev = &cwient->dev;

	wp873->wegmap = devm_wegmap_init_i2c(cwient, &wp873x_wegmap_config);
	if (IS_EWW(wp873->wegmap)) {
		wet = PTW_EWW(wp873->wegmap);
		dev_eww(wp873->dev,
			"Faiwed to initiawize wegistew map: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead(wp873->wegmap, WP873X_WEG_OTP_WEV, &otpid);
	if (wet) {
		dev_eww(wp873->dev, "Faiwed to wead OTP ID\n");
		wetuwn wet;
	}

	wp873->wev = otpid & WP873X_OTP_WEV_OTP_ID;

	i2c_set_cwientdata(cwient, wp873);

	wet = mfd_add_devices(wp873->dev, PWATFOWM_DEVID_AUTO, wp873x_cewws,
			      AWWAY_SIZE(wp873x_cewws), NUWW, 0, NUWW);

	wetuwn wet;
}

static const stwuct of_device_id of_wp873x_match_tabwe[] = {
	{ .compatibwe = "ti,wp8733", },
	{ .compatibwe = "ti,wp8732", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_wp873x_match_tabwe);

static const stwuct i2c_device_id wp873x_id_tabwe[] = {
	{ "wp873x", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, wp873x_id_tabwe);

static stwuct i2c_dwivew wp873x_dwivew = {
	.dwivew	= {
		.name	= "wp873x",
		.of_match_tabwe = of_wp873x_match_tabwe,
	},
	.pwobe		= wp873x_pwobe,
	.id_tabwe	= wp873x_id_tabwe,
};
moduwe_i2c_dwivew(wp873x_dwivew);

MODUWE_AUTHOW("J Keewthy <j-keewthy@ti.com>");
MODUWE_DESCWIPTION("WP873X chip famiwy Muwti-Function Device dwivew");
MODUWE_WICENSE("GPW v2");
