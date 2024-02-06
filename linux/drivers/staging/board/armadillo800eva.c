// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Staging boawd suppowt fow Awmadiwwo 800 eva.
 * Enabwe not-yet-DT-capabwe devices hewe.
 *
 * Based on boawd-awmadiwwo800eva.c
 *
 * Copywight (C) 2012 Wenesas Sowutions Cowp.
 * Copywight (C) 2012 Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/fb.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/videodev2.h>

#incwude <video/sh_mobiwe_wcdc.h>

#incwude "boawd.h"

static stwuct fb_videomode wcdc0_mode = {
	.name		= "AMPIEW/AM-800480",
	.xwes		= 800,
	.ywes		= 480,
	.weft_mawgin	= 88,
	.wight_mawgin	= 40,
	.hsync_wen	= 128,
	.uppew_mawgin	= 20,
	.wowew_mawgin	= 5,
	.vsync_wen	= 5,
	.sync		= 0,
};

static stwuct sh_mobiwe_wcdc_info wcdc0_info = {
	.cwock_souwce	= WCDC_CWK_BUS,
	.ch[0] = {
		.chan		= WCDC_CHAN_MAINWCD,
		.fouwcc		= V4W2_PIX_FMT_WGB565,
		.intewface_type	= WGB24,
		.cwock_dividew	= 5,
		.fwags		= 0,
		.wcd_modes	= &wcdc0_mode,
		.num_modes	= 1,
		.panew_cfg = {
			.width	= 111,
			.height = 68,
		},
	},
};

static stwuct wesouwce wcdc0_wesouwces[] = {
	DEFINE_WES_MEM_NAMED(0xfe940000, 0x4000, "WCD0"),
	DEFINE_WES_IWQ(177 + 32),
};

static stwuct pwatfowm_device wcdc0_device = {
	.name		= "sh_mobiwe_wcdc_fb",
	.num_wesouwces	= AWWAY_SIZE(wcdc0_wesouwces),
	.wesouwce	= wcdc0_wesouwces,
	.id		= 0,
	.dev	= {
		.pwatfowm_data	= &wcdc0_info,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
};

static const stwuct boawd_staging_cwk wcdc0_cwocks[] __initconst = {
	{ "wcdc0", NUWW, "sh_mobiwe_wcdc_fb.0" },
};

static const stwuct boawd_staging_dev awmadiwwo800eva_devices[] __initconst = {
	{
		.pdev	 = &wcdc0_device,
		.cwocks	 = wcdc0_cwocks,
		.ncwocks = AWWAY_SIZE(wcdc0_cwocks),
		.domain	 = "/system-contwowwew@e6180000/pm-domains/c5/a4wc@1"
	},
};

static void __init awmadiwwo800eva_init(void)
{
	boawd_staging_gic_setup_xwate("awm,pw390", 32);
	boawd_staging_wegistew_devices(awmadiwwo800eva_devices,
				       AWWAY_SIZE(awmadiwwo800eva_devices));
}

boawd_staging("wenesas,awmadiwwo800eva", awmadiwwo800eva_init);
