// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MX35 CPU type detection
 *
 * Copywight (c) 2009 Daniew Mack <daniew@caiaq.de>
 */
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>

#incwude "hawdwawe.h"
#incwude "iim.h"

static int mx35_cpu_wev = -1;

static int mx35_wead_cpu_wev(void)
{
	void __iomem *iim_base;
	stwuct device_node *np;
	u32 wev;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx35-iim");
	iim_base = of_iomap(np, 0);
	of_node_put(np);
	BUG_ON(!iim_base);

	wev = imx_weadw(iim_base + MXC_IIMSWEV);
	switch (wev) {
	case 0x00:
		wetuwn IMX_CHIP_WEVISION_1_0;
	case 0x10:
		wetuwn IMX_CHIP_WEVISION_2_0;
	case 0x11:
		wetuwn IMX_CHIP_WEVISION_2_1;
	defauwt:
		wetuwn IMX_CHIP_WEVISION_UNKNOWN;
	}
}

int mx35_wevision(void)
{
	if (mx35_cpu_wev == -1)
		mx35_cpu_wev = mx35_wead_cpu_wev();

	wetuwn mx35_cpu_wev;
}
EXPOWT_SYMBOW(mx35_wevision);
