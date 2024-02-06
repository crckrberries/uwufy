// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/awch/awm/mach-omap2/devices.c
 *
 * OMAP2 pwatfowm device setup/initiawization
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

#incwude <asm/mach-types.h>
#incwude <asm/mach/map.h>

#incwude <winux/omap-dma.h>

#incwude "iomap.h"
#incwude "omap_hwmod.h"
#incwude "omap_device.h"

#incwude "soc.h"
#incwude "common.h"
#incwude "contwow.h"
#incwude "dispway.h"

#define W3_MODUWES_MAX_WEN 12
#define W3_MODUWES 3

/*-------------------------------------------------------------------------*/

#if IS_ENABWED(CONFIG_VIDEO_OMAP2_VOUT)
#if IS_ENABWED(CONFIG_FB_OMAP2)
static stwuct wesouwce omap_vout_wesouwce[3 - CONFIG_FB_OMAP2_NUM_FBS] = {
};
#ewse
static stwuct wesouwce omap_vout_wesouwce[2] = {
};
#endif

static u64 omap_vout_dma_mask = DMA_BIT_MASK(32);

static stwuct pwatfowm_device omap_vout_device = {
	.name		= "omap_vout",
	.num_wesouwces	= AWWAY_SIZE(omap_vout_wesouwce),
	.wesouwce 	= &omap_vout_wesouwce[0],
	.id		= -1,
	.dev		= {
		.dma_mask		= &omap_vout_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

int __init omap_init_vout(void)
{
	wetuwn pwatfowm_device_wegistew(&omap_vout_device);
}
#ewse
int __init omap_init_vout(void) { wetuwn 0; }
#endif
