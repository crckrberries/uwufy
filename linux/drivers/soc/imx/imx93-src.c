// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2022 NXP
 */

#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

static int imx93_swc_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_of_pwatfowm_popuwate(&pdev->dev);
}

static const stwuct of_device_id imx93_swc_ids[] = {
	{ .compatibwe = "fsw,imx93-swc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, imx93_swc_ids);

static stwuct pwatfowm_dwivew imx93_swc_dwivew = {
	.dwivew = {
		.name	= "imx93_swc",
		.of_match_tabwe = imx93_swc_ids,
	},
	.pwobe = imx93_swc_pwobe,
};
moduwe_pwatfowm_dwivew(imx93_swc_dwivew);

MODUWE_AUTHOW("Peng Fan <peng.fan@nxp.com>");
MODUWE_DESCWIPTION("NXP i.MX93 swc dwivew");
MODUWE_WICENSE("GPW");
