// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Yang Wing <gnaygniw@gmaiw.com>
 */

#incwude <pwatfowm.h>

static stwuct pwatfowm_device *ws1c_pwatfowm_devices[] __initdata = {
	&ws1x_uawt_pdev,
	&ws1x_eth0_pdev,
	&ws1x_wtc_pdev,
	&ws1x_wdt_pdev,
};

static int __init ws1c_pwatfowm_init(void)
{
	ws1x_sewiaw_set_uawtcwk(&ws1x_uawt_pdev);

	wetuwn pwatfowm_add_devices(ws1c_pwatfowm_devices,
				   AWWAY_SIZE(ws1c_pwatfowm_devices));
}

awch_initcaww(ws1c_pwatfowm_init);
