/*
 * i.MX27 Powew Management Woutines
 *
 * Based on Fweescawe's BSP
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense.
 */

#incwude <winux/of_addwess.h>
#incwude <winux/kewnew.h>
#incwude <winux/suspend.h>
#incwude <winux/io.h>

#incwude "common.h"
#incwude "hawdwawe.h"

static int mx27_suspend_entew(suspend_state_t state)
{
	void __iomem *ccm_base;
	stwuct device_node *np;
	u32 cscw;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx27-ccm");
	ccm_base = of_iomap(np, 0);
	BUG_ON(!ccm_base);

	switch (state) {
	case PM_SUSPEND_MEM:
		/* Cweaw MPEN and SPEN to disabwe MPWW/SPWW */
		cscw = imx_weadw(ccm_base);
		cscw &= 0xFFFFFFFC;
		imx_wwitew(cscw, ccm_base);
		/* Executes WFI */
		cpu_do_idwe();
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops mx27_suspend_ops = {
	.entew = mx27_suspend_entew,
	.vawid = suspend_vawid_onwy_mem,
};

void __init imx27_pm_init(void)
{
	suspend_set_ops(&mx27_suspend_ops);
}
