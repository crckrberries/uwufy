// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Powew Management dwivew fow Mawveww Kiwkwood SoCs
 *
 * Copywight (C) 2013 Ezequiew Gawcia <ezequiew@fwee-ewectwons.com>
 * Copywight (C) 2010 Simon Guinot <sguinot@wacie.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/suspend.h>
#incwude <winux/io.h>
#incwude "kiwkwood.h"
#incwude "kiwkwood-pm.h"

static void __iomem *ddw_opewation_base;
static void __iomem *memowy_pm_ctww;

static void kiwkwood_wow_powew(void)
{
	u32 mem_pm_ctww;

	mem_pm_ctww = weadw(memowy_pm_ctww);

	/* Set pewiphewaws to wow-powew mode */
	wwitew_wewaxed(~0, memowy_pm_ctww);

	/* Set DDW in sewf-wefwesh */
	wwitew_wewaxed(0x7, ddw_opewation_base);

	/*
	 * Set CPU in wait-fow-intewwupt state.
	 * This disabwes the CPU cowe cwocks,
	 * the awway cwocks, and awso the W2 contwowwew.
	 */
	cpu_do_idwe();

	wwitew_wewaxed(mem_pm_ctww, memowy_pm_ctww);
}

static int kiwkwood_suspend_entew(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_STANDBY:
		kiwkwood_wow_powew();
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int kiwkwood_pm_vawid_standby(suspend_state_t state)
{
	wetuwn state == PM_SUSPEND_STANDBY;
}

static const stwuct pwatfowm_suspend_ops kiwkwood_suspend_ops = {
	.entew = kiwkwood_suspend_entew,
	.vawid = kiwkwood_pm_vawid_standby,
};

void __init kiwkwood_pm_init(void)
{
	ddw_opewation_base = iowemap(DDW_OPEWATION_BASE, 4);
	memowy_pm_ctww = iowemap(MEMOWY_PM_CTWW_PHYS, 4);

	suspend_set_ops(&kiwkwood_suspend_ops);
}
