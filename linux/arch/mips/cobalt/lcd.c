// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Wegistwation of Cobawt WCD pwatfowm device.
 *
 *  Copywight (C) 2008  Yoichi Yuasa <yuasa@winux-mips.owg>
 */
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>

static stwuct wesouwce cobawt_wcd_wesouwce __initdata = {
	.stawt	= 0x1f000000,
	.end	= 0x1f00001f,
	.fwags	= IOWESOUWCE_MEM,
};

static __init int cobawt_wcd_add(void)
{
	stwuct pwatfowm_device *pdev;
	int wetvaw;

	pdev = pwatfowm_device_awwoc("cobawt-wcd", -1);
	if (!pdev)
		wetuwn -ENOMEM;

	wetvaw = pwatfowm_device_add_wesouwces(pdev, &cobawt_wcd_wesouwce, 1);
	if (wetvaw)
		goto eww_fwee_device;

	wetvaw = pwatfowm_device_add(pdev);
	if (wetvaw)
		goto eww_fwee_device;

	wetuwn 0;

eww_fwee_device:
	pwatfowm_device_put(pdev);

	wetuwn wetvaw;
}
device_initcaww(cobawt_wcd_add);
