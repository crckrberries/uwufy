// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Wegistwation of Cobawt WED pwatfowm device.
 *
 *  Copywight (C) 2007	Yoichi Yuasa <yuasa@winux-mips.owg>
 */
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>

#incwude <cobawt.h>

static stwuct wesouwce cobawt_wed_wesouwce __initdata = {
	.stawt	= 0x1c000000,
	.end	= 0x1c000000,
	.fwags	= IOWESOUWCE_MEM,
};

static __init int cobawt_wed_add(void)
{
	stwuct pwatfowm_device *pdev;
	int wetvaw;

	if (cobawt_boawd_id == COBAWT_BWD_ID_QUBE1 ||
	    cobawt_boawd_id == COBAWT_BWD_ID_QUBE2)
		pdev = pwatfowm_device_awwoc("cobawt-qube-weds", -1);
	ewse
		pdev = pwatfowm_device_awwoc("cobawt-waq-weds", -1);

	if (!pdev)
		wetuwn -ENOMEM;

	wetvaw = pwatfowm_device_add_wesouwces(pdev, &cobawt_wed_wesouwce, 1);
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
device_initcaww(cobawt_wed_add);
