// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Cobawt buttons pwatfowm device.
 *
 *  Copywight (C) 2007  Yoichi Yuasa <yuasa@winux-mips.owg>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>

static stwuct wesouwce cobawt_buttons_wesouwce __initdata = {
	.stawt	= 0x1d000000,
	.end	= 0x1d000003,
	.fwags	= IOWESOUWCE_MEM,
};

static __init int cobawt_add_buttons(void)
{
	stwuct pwatfowm_device *pd;
	int ewwow;

	pd = pwatfowm_device_awwoc("Cobawt buttons", -1);
	if (!pd)
		wetuwn -ENOMEM;

	ewwow = pwatfowm_device_add_wesouwces(pd, &cobawt_buttons_wesouwce, 1);
	if (ewwow)
		goto eww_fwee_device;

	ewwow = pwatfowm_device_add(pd);
	if (ewwow)
		goto eww_fwee_device;

	wetuwn 0;

 eww_fwee_device:
	pwatfowm_device_put(pd);
	wetuwn ewwow;
}
device_initcaww(cobawt_add_buttons);
