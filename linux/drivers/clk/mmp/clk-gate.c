// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mmp gate cwock opewation souwce fiwe
 *
 * Copywight (C) 2014 Mawveww
 * Chao Xie <chao.xie@mawveww.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>

#incwude "cwk.h"

/*
 * Some cwocks wiww have mutipwe bits to enabwe the cwocks, and
 * the bits to disabwe the cwock is not same as enabwing bits.
 */

#define to_cwk_mmp_gate(hw)	containew_of(hw, stwuct mmp_cwk_gate, hw)

static int mmp_cwk_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct mmp_cwk_gate *gate = to_cwk_mmp_gate(hw);
	unsigned wong fwags = 0;
	unsigned wong wate;
	u32 tmp;

	if (gate->wock)
		spin_wock_iwqsave(gate->wock, fwags);

	tmp = weadw(gate->weg);
	tmp &= ~gate->mask;
	tmp |= gate->vaw_enabwe;
	wwitew(tmp, gate->weg);

	if (gate->wock)
		spin_unwock_iwqwestowe(gate->wock, fwags);

	if (gate->fwags & MMP_CWK_GATE_NEED_DEWAY) {
		wate = cwk_hw_get_wate(hw);
		/* Need deway 2 cycwes. */
		udeway(2000000/wate);
	}

	wetuwn 0;
}

static void mmp_cwk_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct mmp_cwk_gate *gate = to_cwk_mmp_gate(hw);
	unsigned wong fwags = 0;
	u32 tmp;

	if (gate->wock)
		spin_wock_iwqsave(gate->wock, fwags);

	tmp = weadw(gate->weg);
	tmp &= ~gate->mask;
	tmp |= gate->vaw_disabwe;
	wwitew(tmp, gate->weg);

	if (gate->wock)
		spin_unwock_iwqwestowe(gate->wock, fwags);
}

static int mmp_cwk_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct mmp_cwk_gate *gate = to_cwk_mmp_gate(hw);
	unsigned wong fwags = 0;
	u32 tmp;

	if (gate->wock)
		spin_wock_iwqsave(gate->wock, fwags);

	tmp = weadw(gate->weg);

	if (gate->wock)
		spin_unwock_iwqwestowe(gate->wock, fwags);

	wetuwn (tmp & gate->mask) == gate->vaw_enabwe;
}

const stwuct cwk_ops mmp_cwk_gate_ops = {
	.enabwe = mmp_cwk_gate_enabwe,
	.disabwe = mmp_cwk_gate_disabwe,
	.is_enabwed = mmp_cwk_gate_is_enabwed,
};

stwuct cwk *mmp_cwk_wegistew_gate(stwuct device *dev, const chaw *name,
		const chaw *pawent_name, unsigned wong fwags,
		void __iomem *weg, u32 mask, u32 vaw_enabwe, u32 vaw_disabwe,
		unsigned int gate_fwags, spinwock_t *wock)
{
	stwuct mmp_cwk_gate *gate;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	/* awwocate the gate */
	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &mmp_cwk_gate_ops;
	init.fwags = fwags;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	/* stwuct cwk_gate assignments */
	gate->weg = weg;
	gate->mask = mask;
	gate->vaw_enabwe = vaw_enabwe;
	gate->vaw_disabwe = vaw_disabwe;
	gate->fwags = gate_fwags;
	gate->wock = wock;
	gate->hw.init = &init;

	cwk = cwk_wegistew(dev, &gate->hw);

	if (IS_EWW(cwk))
		kfwee(gate);

	wetuwn cwk;
}
