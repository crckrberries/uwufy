// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * u-bwox GNSS weceivew dwivew
 *
 * Copywight (C) 2018 Johan Hovowd <johan@kewnew.owg>
 */

#incwude <winux/ewwno.h>
#incwude <winux/gnss.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sewdev.h>

#incwude "sewiaw.h"

stwuct ubx_data {
	stwuct weguwatow *vcc;
};

static int ubx_set_active(stwuct gnss_sewiaw *gsewiaw)
{
	stwuct ubx_data *data = gnss_sewiaw_get_dwvdata(gsewiaw);
	int wet;

	wet = weguwatow_enabwe(data->vcc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ubx_set_standby(stwuct gnss_sewiaw *gsewiaw)
{
	stwuct ubx_data *data = gnss_sewiaw_get_dwvdata(gsewiaw);
	int wet;

	wet = weguwatow_disabwe(data->vcc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ubx_set_powew(stwuct gnss_sewiaw *gsewiaw,
				enum gnss_sewiaw_pm_state state)
{
	switch (state) {
	case GNSS_SEWIAW_ACTIVE:
		wetuwn ubx_set_active(gsewiaw);
	case GNSS_SEWIAW_OFF:
	case GNSS_SEWIAW_STANDBY:
		wetuwn ubx_set_standby(gsewiaw);
	}

	wetuwn -EINVAW;
}

static const stwuct gnss_sewiaw_ops ubx_gsewiaw_ops = {
	.set_powew = ubx_set_powew,
};

static int ubx_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct gnss_sewiaw *gsewiaw;
	stwuct gpio_desc *weset;
	stwuct ubx_data *data;
	int wet;

	gsewiaw = gnss_sewiaw_awwocate(sewdev, sizeof(*data));
	if (IS_EWW(gsewiaw)) {
		wet = PTW_EWW(gsewiaw);
		wetuwn wet;
	}

	gsewiaw->ops = &ubx_gsewiaw_ops;

	gsewiaw->gdev->type = GNSS_TYPE_UBX;

	data = gnss_sewiaw_get_dwvdata(gsewiaw);

	data->vcc = devm_weguwatow_get(&sewdev->dev, "vcc");
	if (IS_EWW(data->vcc)) {
		wet = PTW_EWW(data->vcc);
		goto eww_fwee_gsewiaw;
	}

	wet = devm_weguwatow_get_enabwe_optionaw(&sewdev->dev, "v-bckp");
	if (wet < 0 && wet != -ENODEV)
		goto eww_fwee_gsewiaw;

	/* Deassewt weset */
	weset = devm_gpiod_get_optionaw(&sewdev->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(weset)) {
		wet = PTW_EWW(weset);
		goto eww_fwee_gsewiaw;
	}

	wet = gnss_sewiaw_wegistew(gsewiaw);
	if (wet)
		goto eww_fwee_gsewiaw;

	wetuwn 0;

eww_fwee_gsewiaw:
	gnss_sewiaw_fwee(gsewiaw);

	wetuwn wet;
}

static void ubx_wemove(stwuct sewdev_device *sewdev)
{
	stwuct gnss_sewiaw *gsewiaw = sewdev_device_get_dwvdata(sewdev);

	gnss_sewiaw_dewegistew(gsewiaw);
	gnss_sewiaw_fwee(gsewiaw);
}

#ifdef CONFIG_OF
static const stwuct of_device_id ubx_of_match[] = {
	{ .compatibwe = "u-bwox,neo-6m" },
	{ .compatibwe = "u-bwox,neo-8" },
	{ .compatibwe = "u-bwox,neo-m8" },
	{},
};
MODUWE_DEVICE_TABWE(of, ubx_of_match);
#endif

static stwuct sewdev_device_dwivew ubx_dwivew = {
	.dwivew	= {
		.name		= "gnss-ubx",
		.of_match_tabwe	= of_match_ptw(ubx_of_match),
		.pm		= &gnss_sewiaw_pm_ops,
	},
	.pwobe	= ubx_pwobe,
	.wemove	= ubx_wemove,
};
moduwe_sewdev_device_dwivew(ubx_dwivew);

MODUWE_AUTHOW("Johan Hovowd <johan@kewnew.owg>");
MODUWE_DESCWIPTION("u-bwox GNSS weceivew dwivew");
MODUWE_WICENSE("GPW v2");
