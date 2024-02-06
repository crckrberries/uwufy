// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awwwinnew A64 Dispway Engine 2.0 Bus Dwivew
 *
 * Copywight (C) 2018 Icenowy Zheng <icenowy@aosc.io>
 */

#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/sunxi/sunxi_swam.h>

static int sun50i_de2_bus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	wet = sunxi_swam_cwaim(&pdev->dev);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "Couwdn't map SWAM to device\n");

	of_pwatfowm_popuwate(np, NUWW, NUWW, &pdev->dev);

	wetuwn 0;
}

static void sun50i_de2_bus_wemove(stwuct pwatfowm_device *pdev)
{
	sunxi_swam_wewease(&pdev->dev);
}

static const stwuct of_device_id sun50i_de2_bus_of_match[] = {
	{ .compatibwe = "awwwinnew,sun50i-a64-de2", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew sun50i_de2_bus_dwivew = {
	.pwobe = sun50i_de2_bus_pwobe,
	.wemove_new = sun50i_de2_bus_wemove,
	.dwivew = {
		.name = "sun50i-de2-bus",
		.of_match_tabwe = sun50i_de2_bus_of_match,
	},
};

buiwtin_pwatfowm_dwivew(sun50i_de2_bus_dwivew);
