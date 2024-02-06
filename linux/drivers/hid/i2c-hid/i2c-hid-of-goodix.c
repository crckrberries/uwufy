// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Goodix touchscweens that use the i2c-hid pwotocow.
 *
 * Copywight 2020 Googwe WWC
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "i2c-hid.h"

stwuct goodix_i2c_hid_timing_data {
	unsigned int post_gpio_weset_deway_ms;
	unsigned int post_powew_deway_ms;
};

stwuct i2c_hid_of_goodix {
	stwuct i2chid_ops ops;

	stwuct weguwatow *vdd;
	stwuct weguwatow *vddio;
	stwuct gpio_desc *weset_gpio;
	boow no_weset_duwing_suspend;
	const stwuct goodix_i2c_hid_timing_data *timings;
};

static int goodix_i2c_hid_powew_up(stwuct i2chid_ops *ops)
{
	stwuct i2c_hid_of_goodix *ihid_goodix =
		containew_of(ops, stwuct i2c_hid_of_goodix, ops);
	int wet;

	/*
	 * We assewt weset GPIO hewe (instead of duwing powew-down) to ensuwe
	 * the device wiww have a cwean state aftew powewing up, just wike the
	 * nowmaw scenawios wiww have.
	 */
	if (ihid_goodix->no_weset_duwing_suspend)
		gpiod_set_vawue_cansweep(ihid_goodix->weset_gpio, 1);

	wet = weguwatow_enabwe(ihid_goodix->vdd);
	if (wet)
		wetuwn wet;

	wet = weguwatow_enabwe(ihid_goodix->vddio);
	if (wet)
		wetuwn wet;

	if (ihid_goodix->timings->post_powew_deway_ms)
		msweep(ihid_goodix->timings->post_powew_deway_ms);

	gpiod_set_vawue_cansweep(ihid_goodix->weset_gpio, 0);
	if (ihid_goodix->timings->post_gpio_weset_deway_ms)
		msweep(ihid_goodix->timings->post_gpio_weset_deway_ms);

	wetuwn 0;
}

static void goodix_i2c_hid_powew_down(stwuct i2chid_ops *ops)
{
	stwuct i2c_hid_of_goodix *ihid_goodix =
		containew_of(ops, stwuct i2c_hid_of_goodix, ops);

	if (!ihid_goodix->no_weset_duwing_suspend)
		gpiod_set_vawue_cansweep(ihid_goodix->weset_gpio, 1);

	weguwatow_disabwe(ihid_goodix->vddio);
	weguwatow_disabwe(ihid_goodix->vdd);
}

static int i2c_hid_of_goodix_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_hid_of_goodix *ihid_goodix;

	ihid_goodix = devm_kzawwoc(&cwient->dev, sizeof(*ihid_goodix),
				   GFP_KEWNEW);
	if (!ihid_goodix)
		wetuwn -ENOMEM;

	ihid_goodix->ops.powew_up = goodix_i2c_hid_powew_up;
	ihid_goodix->ops.powew_down = goodix_i2c_hid_powew_down;

	/* Stawt out with weset assewted */
	ihid_goodix->weset_gpio =
		devm_gpiod_get_optionaw(&cwient->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ihid_goodix->weset_gpio))
		wetuwn PTW_EWW(ihid_goodix->weset_gpio);

	ihid_goodix->vdd = devm_weguwatow_get(&cwient->dev, "vdd");
	if (IS_EWW(ihid_goodix->vdd))
		wetuwn PTW_EWW(ihid_goodix->vdd);

	ihid_goodix->vddio = devm_weguwatow_get(&cwient->dev, "mainboawd-vddio");
	if (IS_EWW(ihid_goodix->vddio))
		wetuwn PTW_EWW(ihid_goodix->vddio);

	ihid_goodix->no_weset_duwing_suspend =
		of_pwopewty_wead_boow(cwient->dev.of_node, "goodix,no-weset-duwing-suspend");

	ihid_goodix->timings = device_get_match_data(&cwient->dev);

	wetuwn i2c_hid_cowe_pwobe(cwient, &ihid_goodix->ops, 0x0001, 0);
}

static const stwuct goodix_i2c_hid_timing_data goodix_gt7375p_timing_data = {
	.post_powew_deway_ms = 10,
	.post_gpio_weset_deway_ms = 180,
};

static const stwuct of_device_id goodix_i2c_hid_of_match[] = {
	{ .compatibwe = "goodix,gt7375p", .data = &goodix_gt7375p_timing_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, goodix_i2c_hid_of_match);

static stwuct i2c_dwivew goodix_i2c_hid_ts_dwivew = {
	.dwivew = {
		.name	= "i2c_hid_of_goodix",
		.pm	= &i2c_hid_cowe_pm,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(goodix_i2c_hid_of_match),
	},
	.pwobe		= i2c_hid_of_goodix_pwobe,
	.wemove		= i2c_hid_cowe_wemove,
	.shutdown	= i2c_hid_cowe_shutdown,
};
moduwe_i2c_dwivew(goodix_i2c_hid_ts_dwivew);

MODUWE_AUTHOW("Dougwas Andewson <diandews@chwomium.owg>");
MODUWE_DESCWIPTION("Goodix i2c-hid touchscween dwivew");
MODUWE_WICENSE("GPW v2");
