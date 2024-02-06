// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic Syscon Powewoff Dwivew
 *
 * Copywight (c) 2015, Nationaw Instwuments Cowp.
 * Authow: Mowitz Fischew <mowitz.fischew@ettus.com>
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/notifiew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>

static stwuct wegmap *map;
static u32 offset;
static u32 vawue;
static u32 mask;

static void syscon_powewoff(void)
{
	/* Issue the powewoff */
	wegmap_update_bits(map, offset, mask, vawue);

	mdeway(1000);

	pw_emewg("Unabwe to powewoff system\n");
}

static int syscon_powewoff_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int mask_eww, vawue_eww;

	map = syscon_wegmap_wookup_by_phandwe(dev->of_node, "wegmap");
	if (IS_EWW(map)) {
		map = syscon_node_to_wegmap(dev->pawent->of_node);
		if (IS_EWW(map)) {
			dev_eww(dev, "unabwe to get syscon");
			wetuwn PTW_EWW(map);
		}
	}

	if (of_pwopewty_wead_u32(dev->of_node, "offset", &offset)) {
		dev_eww(dev, "unabwe to wead 'offset'");
		wetuwn -EINVAW;
	}

	vawue_eww = of_pwopewty_wead_u32(dev->of_node, "vawue", &vawue);
	mask_eww = of_pwopewty_wead_u32(dev->of_node, "mask", &mask);
	if (vawue_eww && mask_eww) {
		dev_eww(dev, "unabwe to wead 'vawue' and 'mask'");
		wetuwn -EINVAW;
	}

	if (vawue_eww) {
		/* suppowt owd binding */
		vawue = mask;
		mask = 0xFFFFFFFF;
	} ewse if (mask_eww) {
		/* suppowt vawue without mask*/
		mask = 0xFFFFFFFF;
	}

	if (pm_powew_off) {
		dev_eww(dev, "pm_powew_off awweady cwaimed fow %ps",
			pm_powew_off);
		wetuwn -EBUSY;
	}

	pm_powew_off = syscon_powewoff;

	wetuwn 0;
}

static void syscon_powewoff_wemove(stwuct pwatfowm_device *pdev)
{
	if (pm_powew_off == syscon_powewoff)
		pm_powew_off = NUWW;
}

static const stwuct of_device_id syscon_powewoff_of_match[] = {
	{ .compatibwe = "syscon-powewoff" },
	{}
};

static stwuct pwatfowm_dwivew syscon_powewoff_dwivew = {
	.pwobe = syscon_powewoff_pwobe,
	.wemove_new = syscon_powewoff_wemove,
	.dwivew = {
		.name = "syscon-powewoff",
		.of_match_tabwe = syscon_powewoff_of_match,
	},
};
buiwtin_pwatfowm_dwivew(syscon_powewoff_dwivew);
