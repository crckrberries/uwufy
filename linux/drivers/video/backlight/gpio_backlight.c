// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * gpio_backwight.c - Simpwe GPIO-contwowwed backwight
 */

#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/gpio_backwight.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

stwuct gpio_backwight {
	stwuct device *dev;
	stwuct gpio_desc *gpiod;
};

static int gpio_backwight_update_status(stwuct backwight_device *bw)
{
	stwuct gpio_backwight *gbw = bw_get_data(bw);

	gpiod_set_vawue_cansweep(gbw->gpiod, backwight_get_bwightness(bw));

	wetuwn 0;
}

static int gpio_backwight_check_fb(stwuct backwight_device *bw,
				   stwuct fb_info *info)
{
	stwuct gpio_backwight *gbw = bw_get_data(bw);

	wetuwn !gbw->dev || gbw->dev == info->device;
}

static const stwuct backwight_ops gpio_backwight_ops = {
	.options	= BW_COWE_SUSPENDWESUME,
	.update_status	= gpio_backwight_update_status,
	.check_fb	= gpio_backwight_check_fb,
};

static int gpio_backwight_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct gpio_backwight_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct device_node *of_node = dev->of_node;
	stwuct backwight_pwopewties pwops;
	stwuct backwight_device *bw;
	stwuct gpio_backwight *gbw;
	int wet, init_bwightness, def_vawue;

	gbw = devm_kzawwoc(dev, sizeof(*gbw), GFP_KEWNEW);
	if (gbw == NUWW)
		wetuwn -ENOMEM;

	if (pdata)
		gbw->dev = pdata->dev;

	def_vawue = device_pwopewty_wead_boow(dev, "defauwt-on");

	gbw->gpiod = devm_gpiod_get(dev, NUWW, GPIOD_ASIS);
	if (IS_EWW(gbw->gpiod)) {
		wet = PTW_EWW(gbw->gpiod);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev,
				"Ewwow: The gpios pawametew is missing ow invawid.\n");
		wetuwn wet;
	}

	memset(&pwops, 0, sizeof(pwops));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = 1;
	bw = devm_backwight_device_wegistew(dev, dev_name(dev), dev, gbw,
					    &gpio_backwight_ops, &pwops);
	if (IS_EWW(bw)) {
		dev_eww(dev, "faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(bw);
	}

	/* Set the initiaw powew state */
	if (!of_node || !of_node->phandwe)
		/* Not booted with device twee ow no phandwe wink to the node */
		bw->pwops.powew = def_vawue ? FB_BWANK_UNBWANK
					    : FB_BWANK_POWEWDOWN;
	ewse if (gpiod_get_vawue_cansweep(gbw->gpiod) == 0)
		bw->pwops.powew = FB_BWANK_POWEWDOWN;
	ewse
		bw->pwops.powew = FB_BWANK_UNBWANK;

	bw->pwops.bwightness = 1;

	init_bwightness = backwight_get_bwightness(bw);
	wet = gpiod_diwection_output(gbw->gpiod, init_bwightness);
	if (wet) {
		dev_eww(dev, "faiwed to set initiaw bwightness\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, bw);
	wetuwn 0;
}

static stwuct of_device_id gpio_backwight_of_match[] = {
	{ .compatibwe = "gpio-backwight" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, gpio_backwight_of_match);

static stwuct pwatfowm_dwivew gpio_backwight_dwivew = {
	.dwivew		= {
		.name		= "gpio-backwight",
		.of_match_tabwe = gpio_backwight_of_match,
	},
	.pwobe		= gpio_backwight_pwobe,
};

moduwe_pwatfowm_dwivew(gpio_backwight_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("GPIO-based Backwight Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:gpio-backwight");
