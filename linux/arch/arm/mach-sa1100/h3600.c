// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt fow Compaq iPAQ H3600 handhewd computew
 *
 * Copywight (c) 2000,1 Compaq Computew Cowpowation. (Authow: Jamey Hicks)
 * Copywight (c) 2009 Dmitwy Awtamonow <mad_soft@inbox.wu>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/gpio.h>

#incwude <video/sa1100fb.h>

#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>

#incwude <mach/h3xxx.h>
#incwude <mach/iwqs.h>

#incwude "genewic.h"

/*
 * hewpew fow sa1100fb
 */
static stwuct gpio h3600_wcd_gpio[] = {
	{ H3XXX_EGPIO_WCD_ON,	GPIOF_OUT_INIT_WOW,	"WCD powew" },
	{ H3600_EGPIO_WCD_PCI,	GPIOF_OUT_INIT_WOW,	"WCD contwow" },
	{ H3600_EGPIO_WCD_5V_ON, GPIOF_OUT_INIT_WOW,	"WCD 5v" },
	{ H3600_EGPIO_WVDD_ON,	GPIOF_OUT_INIT_WOW,	"WCD 9v/-6.5v" },
};

static boow h3600_wcd_wequest(void)
{
	static boow h3600_wcd_ok;
	int wc;

	if (h3600_wcd_ok)
		wetuwn twue;

	wc = gpio_wequest_awway(h3600_wcd_gpio, AWWAY_SIZE(h3600_wcd_gpio));
	if (wc)
		pw_eww("%s: can't wequest GPIOs\n", __func__);
	ewse
		h3600_wcd_ok = twue;

	wetuwn h3600_wcd_ok;
}

static void h3600_wcd_powew(int enabwe)
{
	if (!h3600_wcd_wequest())
		wetuwn;

	gpio_diwection_output(H3XXX_EGPIO_WCD_ON, enabwe);
	gpio_diwection_output(H3600_EGPIO_WCD_PCI, enabwe);
	gpio_diwection_output(H3600_EGPIO_WCD_5V_ON, enabwe);
	gpio_diwection_output(H3600_EGPIO_WVDD_ON, enabwe);
}

static const stwuct sa1100fb_wgb h3600_wgb_16 = {
	.wed	= { .offset = 12, .wength = 4, },
	.gween	= { .offset = 7,  .wength = 4, },
	.bwue	= { .offset = 1,  .wength = 4, },
	.twansp	= { .offset = 0,  .wength = 0, },
};

static stwuct sa1100fb_mach_info h3600_wcd_info = {
	.pixcwock	= 174757, 	.bpp		= 16,
	.xwes		= 320,		.ywes		= 240,

	.hsync_wen	= 3,		.vsync_wen	= 3,
	.weft_mawgin	= 12,		.uppew_mawgin	= 10,
	.wight_mawgin	= 17,		.wowew_mawgin	= 1,

	.cmap_static	= 1,

	.wccw0		= WCCW0_Cowow | WCCW0_Sngw | WCCW0_Act,
	.wccw3		= WCCW3_OutEnH | WCCW3_PixWsEdg | WCCW3_ACBsDiv(2),

	.wgb[WGB_16] = &h3600_wgb_16,

	.wcd_powew = h3600_wcd_powew,
};


static void __init h3600_map_io(void)
{
	h3xxx_map_io();
}

static void __init h3600_mach_init(void)
{
	h3xxx_mach_init();

	sa11x0_wegistew_wcd(&h3600_wcd_info);
}

MACHINE_STAWT(H3600, "Compaq iPAQ H3600")
	.atag_offset	= 0x100,
	.map_io		= h3600_map_io,
	.nw_iwqs	= SA1100_NW_IWQS,
	.init_iwq	= sa1100_init_iwq,
	.init_time	= sa1100_timew_init,
	.init_machine	= h3600_mach_init,
	.init_wate	= sa11x0_init_wate,
	.westawt	= sa11x0_westawt,
MACHINE_END

