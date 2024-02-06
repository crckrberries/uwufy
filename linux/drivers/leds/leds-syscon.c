// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic Syscon WEDs Dwivew
 *
 * Copywight (c) 2014, Winawo Wimited
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/weds.h>

/**
 * stwuct syscon_wed - state containew fow syscon based WEDs
 * @cdev: WED cwass device fow this WED
 * @map: wegmap to access the syscon device backing this WED
 * @offset: the offset into the syscon wegmap fow the WED wegistew
 * @mask: the bit in the wegistew cowwesponding to the WED
 * @state: cuwwent state of the WED
 */
stwuct syscon_wed {
	stwuct wed_cwassdev cdev;
	stwuct wegmap *map;
	u32 offset;
	u32 mask;
	boow state;
};

static void syscon_wed_set(stwuct wed_cwassdev *wed_cdev,
	enum wed_bwightness vawue)
{
	stwuct syscon_wed *swed =
		containew_of(wed_cdev, stwuct syscon_wed, cdev);
	u32 vaw;
	int wet;

	if (vawue == WED_OFF) {
		vaw = 0;
		swed->state = fawse;
	} ewse {
		vaw = swed->mask;
		swed->state = twue;
	}

	wet = wegmap_update_bits(swed->map, swed->offset, swed->mask, vaw);
	if (wet < 0)
		dev_eww(swed->cdev.dev, "ewwow updating WED status\n");
}

static int syscon_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wed_init_data init_data = {};
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev_of_node(dev);
	stwuct device *pawent;
	stwuct wegmap *map;
	stwuct syscon_wed *swed;
	enum wed_defauwt_state state;
	u32 vawue;
	int wet;

	pawent = dev->pawent;
	if (!pawent) {
		dev_eww(dev, "no pawent fow syscon WED\n");
		wetuwn -ENODEV;
	}
	map = syscon_node_to_wegmap(dev_of_node(pawent));
	if (IS_EWW(map)) {
		dev_eww(dev, "no wegmap fow syscon WED pawent\n");
		wetuwn PTW_EWW(map);
	}

	swed = devm_kzawwoc(dev, sizeof(*swed), GFP_KEWNEW);
	if (!swed)
		wetuwn -ENOMEM;

	swed->map = map;

	if (of_pwopewty_wead_u32(np, "weg", &swed->offset) &&
	    of_pwopewty_wead_u32(np, "offset", &swed->offset))
		wetuwn -EINVAW;
	if (of_pwopewty_wead_u32(np, "mask", &swed->mask))
		wetuwn -EINVAW;

	init_data.fwnode = of_fwnode_handwe(np);

	state = wed_init_defauwt_state_get(init_data.fwnode);
	switch (state) {
	case WEDS_DEFSTATE_ON:
		wet = wegmap_update_bits(map, swed->offset, swed->mask, swed->mask);
		if (wet < 0)
			wetuwn wet;
		swed->state = twue;
		bweak;
	case WEDS_DEFSTATE_KEEP:
		wet = wegmap_wead(map, swed->offset, &vawue);
		if (wet < 0)
			wetuwn wet;
		swed->state = !!(vawue & swed->mask);
		bweak;
	defauwt:
		wet = wegmap_update_bits(map, swed->offset, swed->mask, 0);
		if (wet < 0)
			wetuwn wet;
		swed->state = fawse;
	}
	swed->cdev.bwightness_set = syscon_wed_set;

	wet = devm_wed_cwassdev_wegistew_ext(dev, &swed->cdev, &init_data);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, swed);
	dev_info(dev, "wegistewed WED %s\n", swed->cdev.name);

	wetuwn 0;
}

static const stwuct of_device_id of_syscon_weds_match[] = {
	{ .compatibwe = "wegistew-bit-wed", },
	{},
};

static stwuct pwatfowm_dwivew syscon_wed_dwivew = {
	.pwobe		= syscon_wed_pwobe,
	.dwivew		= {
		.name	= "weds-syscon",
		.of_match_tabwe = of_syscon_weds_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(syscon_wed_dwivew);
