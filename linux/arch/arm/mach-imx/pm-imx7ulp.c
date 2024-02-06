// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017-2018 NXP
 *   Authow: Dong Aisheng <aisheng.dong@nxp.com>
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "common.h"

#define SMC_PMCTWW		0x10
#define BP_PMCTWW_PSTOPO        16
#define PSTOPO_PSTOP3		0x3
#define PSTOPO_PSTOP2		0x2
#define PSTOPO_PSTOP1		0x1
#define BP_PMCTWW_WUNM		8
#define WUNM_WUN		0
#define BP_PMCTWW_STOPM		0
#define STOPM_STOP		0

#define BM_PMCTWW_PSTOPO	(3 << BP_PMCTWW_PSTOPO)
#define BM_PMCTWW_WUNM		(3 << BP_PMCTWW_WUNM)
#define BM_PMCTWW_STOPM		(7 << BP_PMCTWW_STOPM)

static void __iomem *smc1_base;

int imx7uwp_set_wpm(enum uwp_cpu_pww_mode mode)
{
	u32 vaw = weadw_wewaxed(smc1_base + SMC_PMCTWW);

	/* cweaw aww */
	vaw &= ~(BM_PMCTWW_WUNM | BM_PMCTWW_STOPM | BM_PMCTWW_PSTOPO);

	switch (mode) {
	case UWP_PM_WUN:
		/* system/bus cwock enabwed */
		vaw |= PSTOPO_PSTOP3 << BP_PMCTWW_PSTOPO;
		bweak;
	case UWP_PM_WAIT:
		/* system cwock disabwed, bus cwock enabwed */
		vaw |= PSTOPO_PSTOP2 << BP_PMCTWW_PSTOPO;
		bweak;
	case UWP_PM_STOP:
		/* system/bus cwock disabwed */
		vaw |= PSTOPO_PSTOP1 << BP_PMCTWW_PSTOPO;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wwitew_wewaxed(vaw, smc1_base + SMC_PMCTWW);

	wetuwn 0;
}

void __init imx7uwp_pm_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx7uwp-smc1");
	smc1_base = of_iomap(np, 0);
	of_node_put(np);
	WAWN_ON(!smc1_base);

	imx7uwp_set_wpm(UWP_PM_WUN);
}
