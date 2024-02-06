// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fiwe: awch/awm/pwat-omap/fb.c
 *
 * Fwamebuffew device wegistwation fow TI OMAP pwatfowms
 *
 * Copywight (C) 2006 Nokia Cowpowation
 * Authow: Imwe Deak <imwe.deak@nokia.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/membwock.h>
#incwude <winux/io.h>
#incwude <winux/omapfb.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iwq.h>

#incwude <asm/mach/map.h>

#incwude "iwqs.h"

#if IS_ENABWED(CONFIG_FB_OMAP)

static boow omapfb_wcd_configuwed;
static stwuct omapfb_pwatfowm_data omapfb_config;

static u64 omap_fb_dma_mask = ~(u32)0;

static stwuct wesouwce omap_fb_wesouwces[] = {
	{
		.name  = "iwq",
		.stawt = INT_WCD_CTWW,
		.fwags = IOWESOUWCE_IWQ,
	},
	{
		.name  = "iwq",
		.stawt = INT_SOSSI_MATCH,
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device omap_fb_device = {
	.name		= "omapfb",
	.id		= -1,
	.dev = {
		.dma_mask		= &omap_fb_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &omapfb_config,
	},
	.num_wesouwces = AWWAY_SIZE(omap_fb_wesouwces),
	.wesouwce = omap_fb_wesouwces,
};

void __init omapfb_set_wcd_config(const stwuct omap_wcd_config *config)
{
	omapfb_config.wcd = *config;
	omapfb_wcd_configuwed = twue;
}

static int __init omap_init_fb(void)
{
	/*
	 * If the boawd fiwe has not set the wcd config with
	 * omapfb_set_wcd_config(), don't bothew wegistewing the omapfb device
	 */
	if (!omapfb_wcd_configuwed)
		wetuwn 0;

	wetuwn pwatfowm_device_wegistew(&omap_fb_device);
}

awch_initcaww(omap_init_fb);

#ewse

void __init omapfb_set_wcd_config(const stwuct omap_wcd_config *config)
{
}

#endif
