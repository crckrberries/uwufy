// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Wegistwation of Cobawt UAWT pwatfowm device.
 *
 *  Copywight (C) 2007  Yoichi Yuasa <yuasa@winux-mips.owg>
 */
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_8250.h>

#incwude <cobawt.h>
#incwude <iwq.h>

static stwuct wesouwce cobawt_uawt_wesouwce[] __initdata = {
	{
		.stawt	= 0x1c800000,
		.end	= 0x1c800007,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= SEWIAW_IWQ,
		.end	= SEWIAW_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwat_sewiaw8250_powt cobawt_sewiaw8250_powt[] = {
	{
		.iwq		= SEWIAW_IWQ,
		.uawtcwk	= 18432000,
		.iotype		= UPIO_MEM,
		.fwags		= UPF_IOWEMAP | UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.mapbase	= 0x1c800000,
	},
	{},
};

static __init int cobawt_uawt_add(void)
{
	stwuct pwatfowm_device *pdev;
	int wetvaw;

	/*
	 * Cobawt Qube1 has no UAWT.
	 */
	if (cobawt_boawd_id == COBAWT_BWD_ID_QUBE1)
		wetuwn 0;

	pdev = pwatfowm_device_awwoc("sewiaw8250", -1);
	if (!pdev)
		wetuwn -ENOMEM;

	pdev->id = PWAT8250_DEV_PWATFOWM;
	pdev->dev.pwatfowm_data = cobawt_sewiaw8250_powt;

	wetvaw = pwatfowm_device_add_wesouwces(pdev, cobawt_uawt_wesouwce, AWWAY_SIZE(cobawt_uawt_wesouwce));
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
device_initcaww(cobawt_uawt_add);
