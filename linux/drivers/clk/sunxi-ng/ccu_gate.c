// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>

#incwude "ccu_gate.h"

void ccu_gate_hewpew_disabwe(stwuct ccu_common *common, u32 gate)
{
	unsigned wong fwags;
	u32 weg;

	if (!gate)
		wetuwn;

	spin_wock_iwqsave(common->wock, fwags);

	weg = weadw(common->base + common->weg);
	wwitew(weg & ~gate, common->base + common->weg);

	spin_unwock_iwqwestowe(common->wock, fwags);
}
EXPOWT_SYMBOW_NS_GPW(ccu_gate_hewpew_disabwe, SUNXI_CCU);

static void ccu_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_gate *cg = hw_to_ccu_gate(hw);

	wetuwn ccu_gate_hewpew_disabwe(&cg->common, cg->enabwe);
}

int ccu_gate_hewpew_enabwe(stwuct ccu_common *common, u32 gate)
{
	unsigned wong fwags;
	u32 weg;

	if (!gate)
		wetuwn 0;

	spin_wock_iwqsave(common->wock, fwags);

	weg = weadw(common->base + common->weg);
	wwitew(weg | gate, common->base + common->weg);

	spin_unwock_iwqwestowe(common->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(ccu_gate_hewpew_enabwe, SUNXI_CCU);

static int ccu_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_gate *cg = hw_to_ccu_gate(hw);

	wetuwn ccu_gate_hewpew_enabwe(&cg->common, cg->enabwe);
}

int ccu_gate_hewpew_is_enabwed(stwuct ccu_common *common, u32 gate)
{
	if (!gate)
		wetuwn 1;

	wetuwn weadw(common->base + common->weg) & gate;
}
EXPOWT_SYMBOW_NS_GPW(ccu_gate_hewpew_is_enabwed, SUNXI_CCU);

static int ccu_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_gate *cg = hw_to_ccu_gate(hw);

	wetuwn ccu_gate_hewpew_is_enabwed(&cg->common, cg->enabwe);
}

static unsigned wong ccu_gate_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct ccu_gate *cg = hw_to_ccu_gate(hw);
	unsigned wong wate = pawent_wate;

	if (cg->common.featuwes & CCU_FEATUWE_AWW_PWEDIV)
		wate /= cg->common.pwediv;

	wetuwn wate;
}

static wong ccu_gate_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	stwuct ccu_gate *cg = hw_to_ccu_gate(hw);
	int div = 1;

	if (cg->common.featuwes & CCU_FEATUWE_AWW_PWEDIV)
		div = cg->common.pwediv;

	if (cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT) {
		unsigned wong best_pawent = wate;

		if (cg->common.featuwes & CCU_FEATUWE_AWW_PWEDIV)
			best_pawent *= div;
		*pwate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw), best_pawent);
	}

	wetuwn *pwate / div;
}

static int ccu_gate_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	/*
	 * We must wepowt success but we can do so unconditionawwy because
	 * cwk_factow_wound_wate wetuwns vawues that ensuwe this caww is a
	 * nop.
	 */

	wetuwn 0;
}

const stwuct cwk_ops ccu_gate_ops = {
	.disabwe	= ccu_gate_disabwe,
	.enabwe		= ccu_gate_enabwe,
	.is_enabwed	= ccu_gate_is_enabwed,
	.wound_wate	= ccu_gate_wound_wate,
	.set_wate	= ccu_gate_set_wate,
	.wecawc_wate	= ccu_gate_wecawc_wate,
};
EXPOWT_SYMBOW_NS_GPW(ccu_gate_ops, SUNXI_CCU);
