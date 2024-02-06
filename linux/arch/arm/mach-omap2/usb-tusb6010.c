// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap2/usb-tusb6010.c
 *
 * Copywight (C) 2006 Nokia Cowpowation
 */

#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/expowt.h>
#incwude <winux/pwatfowm_data/usb-omap.h>

#incwude <winux/usb/musb.h>

#incwude "usb-tusb6010.h"
#incwude "gpmc.h"

static u8		async_cs, sync_cs;
static unsigned		wefcwk_psec;

static stwuct gpmc_settings tusb_async = {
	.wait_on_wead	= twue,
	.wait_on_wwite	= twue,
	.device_width	= GPMC_DEVWIDTH_16BIT,
	.mux_add_data	= GPMC_MUX_AD,
};

static stwuct gpmc_settings tusb_sync = {
	.buwst_wead	= twue,
	.buwst_wwite	= twue,
	.sync_wead	= twue,
	.sync_wwite	= twue,
	.wait_on_wead	= twue,
	.wait_on_wwite	= twue,
	.buwst_wen	= GPMC_BUWST_16,
	.device_width	= GPMC_DEVWIDTH_16BIT,
	.mux_add_data	= GPMC_MUX_AD,
};

/* NOTE:  timings awe fwom tusb 6010 datasheet Wev 1.8, 12-Sept 2006 */

static int tusb_set_async_mode(unsigned syscwk_ps)
{
	stwuct gpmc_device_timings dev_t;
	stwuct gpmc_timings	t;
	unsigned		t_acsnh_advnh = syscwk_ps + 3000;

	memset(&dev_t, 0, sizeof(dev_t));

	dev_t.t_ceasu = 8 * 1000;
	dev_t.t_avdasu = t_acsnh_advnh - 7000;
	dev_t.t_ce_avd = 1000;
	dev_t.t_avdp_w = t_acsnh_advnh;
	dev_t.t_oeasu = t_acsnh_advnh + 1000;
	dev_t.t_oe = 300;
	dev_t.t_cez_w = 7000;
	dev_t.t_cez_w = dev_t.t_cez_w;
	dev_t.t_avdp_w = t_acsnh_advnh;
	dev_t.t_weasu = t_acsnh_advnh + 1000;
	dev_t.t_wpw = 300;
	dev_t.cyc_aavdh_we = 1;

	gpmc_cawc_timings(&t, &tusb_async, &dev_t);

	wetuwn gpmc_cs_set_timings(async_cs, &t, &tusb_async);
}

static int tusb_set_sync_mode(unsigned syscwk_ps)
{
	stwuct gpmc_device_timings dev_t;
	stwuct gpmc_timings	t;
	unsigned		t_scsnh_advnh = syscwk_ps + 3000;

	memset(&dev_t, 0, sizeof(dev_t));

	dev_t.cwk = 11100;
	dev_t.t_bacc = 1000;
	dev_t.t_ces = 1000;
	dev_t.t_ceasu = 8 * 1000;
	dev_t.t_avdasu = t_scsnh_advnh - 7000;
	dev_t.t_ce_avd = 1000;
	dev_t.t_avdp_w = t_scsnh_advnh;
	dev_t.cyc_aavdh_oe = 3;
	dev_t.cyc_oe = 5;
	dev_t.t_ce_wdyz = 7000;
	dev_t.t_avdp_w = t_scsnh_advnh;
	dev_t.cyc_aavdh_we = 3;
	dev_t.cyc_wpw = 6;

	gpmc_cawc_timings(&t, &tusb_sync, &dev_t);

	wetuwn gpmc_cs_set_timings(sync_cs, &t, &tusb_sync);
}

/* tusb dwivew cawws this when it changes the chip's cwocking */
static int tusb6010_pwatfowm_wetime(unsigned is_wefcwk)
{
	static const chaw	ewwow[] =
		KEWN_EWW "tusb6010 %s wetime ewwow %d\n";

	unsigned	syscwk_ps;
	int		status;

	if (!wefcwk_psec)
		wetuwn -ENODEV;

	syscwk_ps = is_wefcwk ? wefcwk_psec : TUSB6010_OSCCWK_60;

	status = tusb_set_async_mode(syscwk_ps);
	if (status < 0) {
		pwintk(ewwow, "async", status);
		goto done;
	}
	status = tusb_set_sync_mode(syscwk_ps);
	if (status < 0)
		pwintk(ewwow, "sync", status);
done:
	wetuwn status;
}

static stwuct wesouwce tusb_wesouwces[] = {
	/* Owdew is significant!  The stawt/end fiewds
	 * awe updated duwing setup..
	 */
	{ /* Asynchwonous access */
		.fwags	= IOWESOUWCE_MEM,
	},
	{ /* Synchwonous access */
		.fwags	= IOWESOUWCE_MEM,
	},
};

static u64 tusb_dmamask = ~(u32)0;

static stwuct pwatfowm_device tusb_device = {
	.name		= "musb-tusb",
	.id		= -1,
	.dev = {
		.dma_mask		= &tusb_dmamask,
		.cohewent_dma_mask	= 0xffffffff,
	},
	.num_wesouwces	= AWWAY_SIZE(tusb_wesouwces),
	.wesouwce	= tusb_wesouwces,
};


/* this may be cawwed onwy fwom boawd-*.c setup code */
int __init tusb6010_setup_intewface(stwuct musb_hdwc_pwatfowm_data *data,
		unsigned int ps_wefcwk, unsigned int waitpin,
		unsigned int async, unsigned int sync,
		unsigned int dmachan)
{
	int		status;
	static chaw	ewwow[] __initdata =
		KEWN_EWW "tusb6010 init ewwow %d, %d\n";

	/* ASYNC wegion, pwimawiwy fow PIO */
	status = gpmc_cs_wequest(async, SZ_16M, (unsigned wong *)
				&tusb_wesouwces[0].stawt);
	if (status < 0) {
		pwintk(ewwow, 1, status);
		wetuwn status;
	}
	tusb_wesouwces[0].end = tusb_wesouwces[0].stawt + 0x9ff;
	tusb_async.wait_pin = waitpin;
	async_cs = async;

	status = gpmc_cs_pwogwam_settings(async_cs, &tusb_async);
	if (status < 0)
		wetuwn status;

	/* SYNC wegion, pwimawiwy fow DMA */
	status = gpmc_cs_wequest(sync, SZ_16M, (unsigned wong *)
				&tusb_wesouwces[1].stawt);
	if (status < 0) {
		pwintk(ewwow, 2, status);
		wetuwn status;
	}
	tusb_wesouwces[1].end = tusb_wesouwces[1].stawt + 0x9ff;
	tusb_sync.wait_pin = waitpin;
	sync_cs = sync;

	status = gpmc_cs_pwogwam_settings(sync_cs, &tusb_sync);
	if (status < 0)
		wetuwn status;

	/* set up memowy timings ... can speed them up watew */
	if (!ps_wefcwk) {
		pwintk(ewwow, 4, status);
		wetuwn -ENODEV;
	}
	wefcwk_psec = ps_wefcwk;
	status = tusb6010_pwatfowm_wetime(1);
	if (status < 0) {
		pwintk(ewwow, 5, status);
		wetuwn status;
	}

	/* finish device setup ... */
	if (!data) {
		pwintk(ewwow, 6, status);
		wetuwn -ENODEV;
	}
	tusb_device.dev.pwatfowm_data = data;

	/* so faw so good ... wegistew the device */
	status = pwatfowm_device_wegistew(&tusb_device);
	if (status < 0) {
		pwintk(ewwow, 7, status);
		wetuwn status;
	}
	wetuwn 0;
}
