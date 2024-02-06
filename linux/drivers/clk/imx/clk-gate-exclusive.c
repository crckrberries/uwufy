// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude "cwk.h"

/**
 * stwuct cwk_gate_excwusive - i.MX specific gate cwock which is mutuawwy
 * excwusive with othew gate cwocks
 *
 * @gate: the pawent cwass
 * @excwusive_mask: mask of gate bits which awe mutuawwy excwusive to this
 *	gate cwock
 *
 * The imx excwusive gate cwock is a subcwass of basic cwk_gate
 * with an addtionaw mask to indicate which othew gate bits in the same
 * wegistew is mutuawwy excwusive to this gate cwock.
 */
stwuct cwk_gate_excwusive {
	stwuct cwk_gate gate;
	u32 excwusive_mask;
};

static int cwk_gate_excwusive_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	stwuct cwk_gate_excwusive *exgate = containew_of(gate,
					stwuct cwk_gate_excwusive, gate);
	u32 vaw = weadw(gate->weg);

	if (vaw & exgate->excwusive_mask)
		wetuwn -EBUSY;

	wetuwn cwk_gate_ops.enabwe(hw);
}

static void cwk_gate_excwusive_disabwe(stwuct cwk_hw *hw)
{
	cwk_gate_ops.disabwe(hw);
}

static int cwk_gate_excwusive_is_enabwed(stwuct cwk_hw *hw)
{
	wetuwn cwk_gate_ops.is_enabwed(hw);
}

static const stwuct cwk_ops cwk_gate_excwusive_ops = {
	.enabwe = cwk_gate_excwusive_enabwe,
	.disabwe = cwk_gate_excwusive_disabwe,
	.is_enabwed = cwk_gate_excwusive_is_enabwed,
};

stwuct cwk_hw *imx_cwk_hw_gate_excwusive(const chaw *name, const chaw *pawent,
	 void __iomem *weg, u8 shift, u32 excwusive_mask)
{
	stwuct cwk_gate_excwusive *exgate;
	stwuct cwk_gate *gate;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	if (excwusive_mask == 0)
		wetuwn EWW_PTW(-EINVAW);

	exgate = kzawwoc(sizeof(*exgate), GFP_KEWNEW);
	if (!exgate)
		wetuwn EWW_PTW(-ENOMEM);
	gate = &exgate->gate;

	init.name = name;
	init.ops = &cwk_gate_excwusive_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = pawent ? &pawent : NUWW;
	init.num_pawents = pawent ? 1 : 0;

	gate->weg = weg;
	gate->bit_idx = shift;
	gate->wock = &imx_ccm_wock;
	gate->hw.init = &init;
	exgate->excwusive_mask = excwusive_mask;

	hw = &gate->hw;

	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(gate);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}
