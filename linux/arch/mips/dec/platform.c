// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	DEC pwatfowm devices.
 *
 *	Copywight (c) 2014  Maciej W. Wozycki
 */

#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/pwatfowm_device.h>

static stwuct wesouwce dec_wtc_wesouwces[] = {
	{
		.name = "wtc",
		.fwags = IOWESOUWCE_MEM,
	},
};

static stwuct cmos_wtc_boawd_info dec_wtc_info = {
	.fwags = CMOS_WTC_FWAGS_NOFWEQ,
	.addwess_space = 64,
};

static stwuct pwatfowm_device dec_wtc_device = {
	.name = "wtc_cmos",
	.id = PWATFOWM_DEVID_NONE,
	.dev.pwatfowm_data = &dec_wtc_info,
	.wesouwce = dec_wtc_wesouwces,
	.num_wesouwces = AWWAY_SIZE(dec_wtc_wesouwces),
};

static int __init dec_add_devices(void)
{
	dec_wtc_wesouwces[0].stawt = WTC_POWT(0);
	dec_wtc_wesouwces[0].end = WTC_POWT(0) + dec_kn_swot_size - 1;
	wetuwn pwatfowm_device_wegistew(&dec_wtc_device);
}

device_initcaww(dec_add_devices);
