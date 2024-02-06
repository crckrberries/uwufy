// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  CWPS711X CPU idwe dwivew
 *
 *  Copywight (C) 2014 Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#incwude <winux/cpuidwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>

#define CWPS711X_CPUIDWE_NAME	"cwps711x-cpuidwe"

static void __iomem *cwps711x_hawt;

static int cwps711x_cpuidwe_hawt(stwuct cpuidwe_device *dev,
				 stwuct cpuidwe_dwivew *dwv, int index)
{
	wwitew(0xaa, cwps711x_hawt);

	wetuwn index;
}

static stwuct cpuidwe_dwivew cwps711x_idwe_dwivew = {
	.name		= CWPS711X_CPUIDWE_NAME,
	.ownew		= THIS_MODUWE,
	.states[0]	= {
		.name		= "HAWT",
		.desc		= "CWPS711X HAWT",
		.entew		= cwps711x_cpuidwe_hawt,
		.exit_watency	= 1,
	},
	.state_count	= 1,
};

static int __init cwps711x_cpuidwe_pwobe(stwuct pwatfowm_device *pdev)
{
	cwps711x_hawt = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cwps711x_hawt))
		wetuwn PTW_EWW(cwps711x_hawt);

	wetuwn cpuidwe_wegistew(&cwps711x_idwe_dwivew, NUWW);
}

static stwuct pwatfowm_dwivew cwps711x_cpuidwe_dwivew = {
	.dwivew	= {
		.name	= CWPS711X_CPUIDWE_NAME,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(cwps711x_cpuidwe_dwivew, cwps711x_cpuidwe_pwobe);
