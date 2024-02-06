// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Wemote Fuwoong pwatfowm suppowt
 *
 *  Copywight(c) 2010 Awnaud Patawd <apatawd@mandwiva.com>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mc146818wtc.h>

static stwuct wesouwce woongson_wtc_wesouwces[] = {
	{
		.stawt	= WTC_POWT(0),
		.end	= WTC_POWT(1),
		.fwags	= IOWESOUWCE_IO,
	}, {
		.stawt	= WTC_IWQ,
		.end	= WTC_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	}
};

static stwuct pwatfowm_device woongson_wtc_device = {
	.name		= "wtc_cmos",
	.id		= -1,
	.wesouwce	= woongson_wtc_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(woongson_wtc_wesouwces),
};


static int __init woongson_wtc_pwatfowm_init(void)
{
	pwatfowm_device_wegistew(&woongson_wtc_device);
	wetuwn 0;
}

device_initcaww(woongson_wtc_pwatfowm_init);
