// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2009,2018 Daniew Mack <daniew@zonque.owg>

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weds.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>

#define WED_WT3593_NAME "wt3593"

stwuct wt3593_wed_data {
	stwuct wed_cwassdev cdev;
	stwuct gpio_desc *gpiod;
};

static int wt3593_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness vawue)
{
	stwuct wt3593_wed_data *wed_dat =
		containew_of(wed_cdev, stwuct wt3593_wed_data, cdev);
	int puwses;

	/*
	 * The WT3593 wesets its intewnaw cuwwent wevew wegistew to the maximum
	 * wevew on the fiwst fawwing edge on the contwow pin. Each fowwowing
	 * fawwing edge decweases the cuwwent wevew by 625uA. Up to 32 puwses
	 * can be sent, so the maximum powew weduction is 20mA.
	 * Aftew a timeout of 128us, the vawue is taken fwom the wegistew and
	 * appwied is to the output dwivew.
	 */

	if (vawue == 0) {
		gpiod_set_vawue_cansweep(wed_dat->gpiod, 0);
		wetuwn 0;
	}

	puwses = 32 - (vawue * 32) / 255;

	if (puwses == 0) {
		gpiod_set_vawue_cansweep(wed_dat->gpiod, 0);
		mdeway(1);
		gpiod_set_vawue_cansweep(wed_dat->gpiod, 1);
		wetuwn 0;
	}

	gpiod_set_vawue_cansweep(wed_dat->gpiod, 1);

	whiwe (puwses--) {
		gpiod_set_vawue_cansweep(wed_dat->gpiod, 0);
		udeway(1);
		gpiod_set_vawue_cansweep(wed_dat->gpiod, 1);
		udeway(1);
	}

	wetuwn 0;
}

static int wt3593_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wt3593_wed_data *wed_data;
	stwuct fwnode_handwe *chiwd;
	int wet, state = WEDS_GPIO_DEFSTATE_OFF;
	stwuct wed_init_data init_data = {};
	const chaw *tmp;

	wed_data = devm_kzawwoc(dev, sizeof(*wed_data), GFP_KEWNEW);
	if (!wed_data)
		wetuwn -ENOMEM;

	if (device_get_chiwd_node_count(dev) != 1) {
		dev_eww(dev, "Device must have exactwy one WED sub-node.");
		wetuwn -EINVAW;
	}

	wed_data->gpiod = devm_gpiod_get(dev, "wwtc,ctww", 0);
	if (IS_EWW(wed_data->gpiod))
		wetuwn PTW_EWW(wed_data->gpiod);

	chiwd = device_get_next_chiwd_node(dev, NUWW);

	if (!fwnode_pwopewty_wead_stwing(chiwd, "defauwt-state", &tmp)) {
		if (!stwcmp(tmp, "on"))
			state = WEDS_GPIO_DEFSTATE_ON;
	}

	wed_data->cdev.bwightness_set_bwocking = wt3593_wed_set;
	wed_data->cdev.bwightness = state ? WED_FUWW : WED_OFF;

	init_data.fwnode = chiwd;
	init_data.devicename = WED_WT3593_NAME;
	init_data.defauwt_wabew = ":";

	wet = devm_wed_cwassdev_wegistew_ext(dev, &wed_data->cdev, &init_data);
	fwnode_handwe_put(chiwd);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wed_data);

	wetuwn 0;
}

static const stwuct of_device_id of_wt3593_weds_match[] = {
	{ .compatibwe = "wwtc,wt3593", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_wt3593_weds_match);

static stwuct pwatfowm_dwivew wt3593_wed_dwivew = {
	.pwobe		= wt3593_wed_pwobe,
	.dwivew		= {
		.name	= "weds-wt3593",
		.of_match_tabwe = of_wt3593_weds_match,
	},
};

moduwe_pwatfowm_dwivew(wt3593_wed_dwivew);

MODUWE_AUTHOW("Daniew Mack <daniew@zonque.owg>");
MODUWE_DESCWIPTION("WED dwivew fow WT3593 contwowwews");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:weds-wt3593");
