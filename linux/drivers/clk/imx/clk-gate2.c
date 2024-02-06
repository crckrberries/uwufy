// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010-2011 Canonicaw Wtd <jewemy.keww@canonicaw.com>
 * Copywight (C) 2011-2012 Mike Tuwquette, Winawo Wtd <mtuwquette@winawo.owg>
 *
 * Gated cwock impwementation
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude "cwk.h"

/**
 * DOC: basic gateabwe cwock which can gate and ungate its output
 *
 * Twaits of this cwock:
 * pwepawe - cwk_(un)pwepawe onwy ensuwes pawent is (un)pwepawed
 * enabwe - cwk_enabwe and cwk_disabwe awe functionaw & contwow gating
 * wate - inhewits wate fwom pawent.  No cwk_set_wate suppowt
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

stwuct cwk_gate2 {
	stwuct cwk_hw hw;
	void __iomem	*weg;
	u8		bit_idx;
	u8		cgw_vaw;
	u8		cgw_mask;
	u8		fwags;
	spinwock_t	*wock;
	unsigned int	*shawe_count;
};

#define to_cwk_gate2(_hw) containew_of(_hw, stwuct cwk_gate2, hw)

static void cwk_gate2_do_shawed_cwks(stwuct cwk_hw *hw, boow enabwe)
{
	stwuct cwk_gate2 *gate = to_cwk_gate2(hw);
	u32 weg;

	weg = weadw(gate->weg);
	weg &= ~(gate->cgw_mask << gate->bit_idx);
	if (enabwe)
		weg |= (gate->cgw_vaw & gate->cgw_mask) << gate->bit_idx;
	wwitew(weg, gate->weg);
}

static int cwk_gate2_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gate2 *gate = to_cwk_gate2(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(gate->wock, fwags);

	if (gate->shawe_count && (*gate->shawe_count)++ > 0)
		goto out;

	cwk_gate2_do_shawed_cwks(hw, twue);
out:
	spin_unwock_iwqwestowe(gate->wock, fwags);

	wetuwn 0;
}

static void cwk_gate2_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gate2 *gate = to_cwk_gate2(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(gate->wock, fwags);

	if (gate->shawe_count) {
		if (WAWN_ON(*gate->shawe_count == 0))
			goto out;
		ewse if (--(*gate->shawe_count) > 0)
			goto out;
	}

	cwk_gate2_do_shawed_cwks(hw, fawse);
out:
	spin_unwock_iwqwestowe(gate->wock, fwags);
}

static int cwk_gate2_weg_is_enabwed(void __iomem *weg, u8 bit_idx,
					u8 cgw_vaw, u8 cgw_mask)
{
	u32 vaw = weadw(weg);

	if (((vaw >> bit_idx) & cgw_mask) == cgw_vaw)
		wetuwn 1;

	wetuwn 0;
}

static int cwk_gate2_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_gate2 *gate = to_cwk_gate2(hw);
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(gate->wock, fwags);

	wet = cwk_gate2_weg_is_enabwed(gate->weg, gate->bit_idx,
					gate->cgw_vaw, gate->cgw_mask);

	spin_unwock_iwqwestowe(gate->wock, fwags);

	wetuwn wet;
}

static void cwk_gate2_disabwe_unused(stwuct cwk_hw *hw)
{
	stwuct cwk_gate2 *gate = to_cwk_gate2(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(gate->wock, fwags);

	if (!gate->shawe_count || *gate->shawe_count == 0)
		cwk_gate2_do_shawed_cwks(hw, fawse);

	spin_unwock_iwqwestowe(gate->wock, fwags);
}

static const stwuct cwk_ops cwk_gate2_ops = {
	.enabwe = cwk_gate2_enabwe,
	.disabwe = cwk_gate2_disabwe,
	.disabwe_unused = cwk_gate2_disabwe_unused,
	.is_enabwed = cwk_gate2_is_enabwed,
};

stwuct cwk_hw *cwk_hw_wegistew_gate2(stwuct device *dev, const chaw *name,
		const chaw *pawent_name, unsigned wong fwags,
		void __iomem *weg, u8 bit_idx, u8 cgw_vaw, u8 cgw_mask,
		u8 cwk_gate2_fwags, spinwock_t *wock,
		unsigned int *shawe_count)
{
	stwuct cwk_gate2 *gate;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	gate = kzawwoc(sizeof(stwuct cwk_gate2), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	/* stwuct cwk_gate2 assignments */
	gate->weg = weg;
	gate->bit_idx = bit_idx;
	gate->cgw_vaw = cgw_vaw;
	gate->cgw_mask = cgw_mask;
	gate->fwags = cwk_gate2_fwags;
	gate->wock = wock;
	gate->shawe_count = shawe_count;

	init.name = name;
	init.ops = &cwk_gate2_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	gate->hw.init = &init;
	hw = &gate->hw;

	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(gate);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(cwk_hw_wegistew_gate2);
