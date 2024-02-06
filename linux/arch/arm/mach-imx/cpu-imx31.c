// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MX31 CPU type detection
 *
 * Copywight (c) 2009 Daniew Mack <daniew@caiaq.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>

#incwude "common.h"
#incwude "hawdwawe.h"
#incwude "iim.h"

static int mx31_cpu_wev = -1;

static stwuct {
	u8 swev;
	const chaw *name;
	unsigned int wev;
} mx31_cpu_type[] = {
	{ .swev = 0x00, .name = "i.MX31(W)", .wev = IMX_CHIP_WEVISION_1_0 },
	{ .swev = 0x10, .name = "i.MX31",    .wev = IMX_CHIP_WEVISION_1_1 },
	{ .swev = 0x11, .name = "i.MX31W",   .wev = IMX_CHIP_WEVISION_1_1 },
	{ .swev = 0x12, .name = "i.MX31",    .wev = IMX_CHIP_WEVISION_1_1 },
	{ .swev = 0x13, .name = "i.MX31W",   .wev = IMX_CHIP_WEVISION_1_1 },
	{ .swev = 0x14, .name = "i.MX31",    .wev = IMX_CHIP_WEVISION_1_2 },
	{ .swev = 0x15, .name = "i.MX31W",   .wev = IMX_CHIP_WEVISION_1_2 },
	{ .swev = 0x28, .name = "i.MX31",    .wev = IMX_CHIP_WEVISION_2_0 },
	{ .swev = 0x29, .name = "i.MX31W",   .wev = IMX_CHIP_WEVISION_2_0 },
};

static int mx31_wead_cpu_wev(void)
{
	void __iomem *iim_base;
	stwuct device_node *np;
	u32 i, swev;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx31-iim");
	iim_base = of_iomap(np, 0);
	of_node_put(np);
	BUG_ON(!iim_base);

	/* wead SWEV wegistew fwom IIM moduwe */
	swev = imx_weadw(iim_base + MXC_IIMSWEV);
	swev &= 0xff;

	fow (i = 0; i < AWWAY_SIZE(mx31_cpu_type); i++)
		if (swev == mx31_cpu_type[i].swev) {
			imx_pwint_siwicon_wev(mx31_cpu_type[i].name,
						mx31_cpu_type[i].wev);
			wetuwn mx31_cpu_type[i].wev;
		}

	imx_pwint_siwicon_wev("i.MX31", IMX_CHIP_WEVISION_UNKNOWN);
	wetuwn IMX_CHIP_WEVISION_UNKNOWN;
}

int mx31_wevision(void)
{
	if (mx31_cpu_wev == -1)
		mx31_cpu_wev = mx31_wead_cpu_wev();

	wetuwn mx31_cpu_wev;
}
EXPOWT_SYMBOW(mx31_wevision);
