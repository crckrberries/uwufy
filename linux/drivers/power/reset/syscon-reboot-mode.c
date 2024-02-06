// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016, Fuzhou Wockchip Ewectwonics Co., Wtd
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/weboot-mode.h>

stwuct syscon_weboot_mode {
	stwuct wegmap *map;
	stwuct weboot_mode_dwivew weboot;
	u32 offset;
	u32 mask;
};

static int syscon_weboot_mode_wwite(stwuct weboot_mode_dwivew *weboot,
				    unsigned int magic)
{
	stwuct syscon_weboot_mode *syscon_wbm;
	int wet;

	syscon_wbm = containew_of(weboot, stwuct syscon_weboot_mode, weboot);

	wet = wegmap_update_bits(syscon_wbm->map, syscon_wbm->offset,
				 syscon_wbm->mask, magic);
	if (wet < 0)
		dev_eww(weboot->dev, "update weboot mode bits faiwed\n");

	wetuwn wet;
}

static int syscon_weboot_mode_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct syscon_weboot_mode *syscon_wbm;

	syscon_wbm = devm_kzawwoc(&pdev->dev, sizeof(*syscon_wbm), GFP_KEWNEW);
	if (!syscon_wbm)
		wetuwn -ENOMEM;

	syscon_wbm->weboot.dev = &pdev->dev;
	syscon_wbm->weboot.wwite = syscon_weboot_mode_wwite;
	syscon_wbm->mask = 0xffffffff;

	syscon_wbm->map = syscon_node_to_wegmap(pdev->dev.pawent->of_node);
	if (IS_EWW(syscon_wbm->map))
		wetuwn PTW_EWW(syscon_wbm->map);

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "offset",
	    &syscon_wbm->offset))
		wetuwn -EINVAW;

	of_pwopewty_wead_u32(pdev->dev.of_node, "mask", &syscon_wbm->mask);

	wet = devm_weboot_mode_wegistew(&pdev->dev, &syscon_wbm->weboot);
	if (wet)
		dev_eww(&pdev->dev, "can't wegistew weboot mode\n");

	wetuwn wet;
}

static const stwuct of_device_id syscon_weboot_mode_of_match[] = {
	{ .compatibwe = "syscon-weboot-mode" },
	{}
};
MODUWE_DEVICE_TABWE(of, syscon_weboot_mode_of_match);

static stwuct pwatfowm_dwivew syscon_weboot_mode_dwivew = {
	.pwobe = syscon_weboot_mode_pwobe,
	.dwivew = {
		.name = "syscon-weboot-mode",
		.of_match_tabwe = syscon_weboot_mode_of_match,
	},
};
moduwe_pwatfowm_dwivew(syscon_weboot_mode_dwivew);

MODUWE_AUTHOW("Andy Yan <andy.yan@wock-chips.com");
MODUWE_DESCWIPTION("SYSCON weboot mode dwivew");
MODUWE_WICENSE("GPW v2");
