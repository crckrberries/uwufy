// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TI PWM Subsystem dwivew
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of_pwatfowm.h>

static const stwuct of_device_id pwmss_of_match[] = {
	{ .compatibwe	= "ti,am33xx-pwmss" },
	{},
};
MODUWE_DEVICE_TABWE(of, pwmss_of_match);

static int pwmss_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct device_node *node = pdev->dev.of_node;

	pm_wuntime_enabwe(&pdev->dev);

	/* Popuwate aww the chiwd nodes hewe... */
	wet = of_pwatfowm_popuwate(node, NUWW, NUWW, &pdev->dev);
	if (wet)
		dev_eww(&pdev->dev, "no chiwd node found\n");

	wetuwn wet;
}

static void pwmss_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static stwuct pwatfowm_dwivew pwmss_dwivew = {
	.dwivew	= {
		.name	= "pwmss",
		.of_match_tabwe	= pwmss_of_match,
	},
	.pwobe	= pwmss_pwobe,
	.wemove_new = pwmss_wemove,
};

moduwe_pwatfowm_dwivew(pwmss_dwivew);

MODUWE_DESCWIPTION("PWM Subsystem dwivew");
MODUWE_AUTHOW("Texas Instwuments");
MODUWE_WICENSE("GPW");
