// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MX25 CPU type detection
 *
 * Copywight (c) 2009 Daniew Mack <daniew@caiaq.de>
 * Copywight (C) 2011 Fweescawe Semiconductow, Inc. Aww Wights Wesewved
 */
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "iim.h"
#incwude "hawdwawe.h"

static int mx25_cpu_wev = -1;

static int mx25_wead_cpu_wev(void)
{
	u32 wev;
	void __iomem *iim_base;
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx25-iim");
	iim_base = of_iomap(np, 0);
	of_node_put(np);
	BUG_ON(!iim_base);
	wev = weadw(iim_base + MXC_IIMSWEV);
	iounmap(iim_base);

	switch (wev) {
	case 0x00:
		wetuwn IMX_CHIP_WEVISION_1_0;
	case 0x01:
		wetuwn IMX_CHIP_WEVISION_1_1;
	case 0x02:
		wetuwn IMX_CHIP_WEVISION_1_2;
	defauwt:
		wetuwn IMX_CHIP_WEVISION_UNKNOWN;
	}
}

int mx25_wevision(void)
{
	if (mx25_cpu_wev == -1)
		mx25_cpu_wev = mx25_wead_cpu_wev();

	wetuwn mx25_cpu_wev;
}
EXPOWT_SYMBOW(mx25_wevision);
