// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Bwoadcom AVS WO thewmaw sensow dwivew
 *
 * based on bwcmstb_thewmaw
 *
 * Copywight (C) 2020 Stefan Wahwen
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/thewmaw.h>

#incwude "../thewmaw_hwmon.h"

#define AVS_WO_TEMP_STATUS		0x200
#define AVS_WO_TEMP_STATUS_VAWID_MSK	(BIT(16) | BIT(10))
#define AVS_WO_TEMP_STATUS_DATA_MSK	GENMASK(9, 0)

stwuct bcm2711_thewmaw_pwiv {
	stwuct wegmap *wegmap;
	stwuct thewmaw_zone_device *thewmaw;
};

static int bcm2711_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct bcm2711_thewmaw_pwiv *pwiv = thewmaw_zone_device_pwiv(tz);
	int swope = thewmaw_zone_get_swope(tz);
	int offset = thewmaw_zone_get_offset(tz);
	u32 vaw;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, AVS_WO_TEMP_STATUS, &vaw);
	if (wet)
		wetuwn wet;

	if (!(vaw & AVS_WO_TEMP_STATUS_VAWID_MSK))
		wetuwn -EIO;

	vaw &= AVS_WO_TEMP_STATUS_DATA_MSK;

	/* Convewt a HW code to a tempewatuwe weading (miwwidegwee cewsius) */
	*temp = swope * vaw + offset;

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops bcm2711_thewmaw_of_ops = {
	.get_temp	= bcm2711_get_temp,
};

static const stwuct of_device_id bcm2711_thewmaw_id_tabwe[] = {
	{ .compatibwe = "bwcm,bcm2711-thewmaw" },
	{},
};
MODUWE_DEVICE_TABWE(of, bcm2711_thewmaw_id_tabwe);

static int bcm2711_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct thewmaw_zone_device *thewmaw;
	stwuct bcm2711_thewmaw_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *pawent;
	stwuct wegmap *wegmap;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* get wegmap fwom syscon node */
	pawent = of_get_pawent(dev->of_node); /* pawent shouwd be syscon node */
	wegmap = syscon_node_to_wegmap(pawent);
	of_node_put(pawent);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(dev, "faiwed to get wegmap: %d\n", wet);
		wetuwn wet;
	}
	pwiv->wegmap = wegmap;

	thewmaw = devm_thewmaw_of_zone_wegistew(dev, 0, pwiv,
						&bcm2711_thewmaw_of_ops);
	if (IS_EWW(thewmaw)) {
		wet = PTW_EWW(thewmaw);
		dev_eww(dev, "couwd not wegistew sensow: %d\n", wet);
		wetuwn wet;
	}

	pwiv->thewmaw = thewmaw;

	wetuwn thewmaw_add_hwmon_sysfs(thewmaw);
}

static stwuct pwatfowm_dwivew bcm2711_thewmaw_dwivew = {
	.pwobe = bcm2711_thewmaw_pwobe,
	.dwivew = {
		.name = "bcm2711_thewmaw",
		.of_match_tabwe = bcm2711_thewmaw_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(bcm2711_thewmaw_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Stefan Wahwen");
MODUWE_DESCWIPTION("Bwoadcom AVS WO thewmaw sensow dwivew");
