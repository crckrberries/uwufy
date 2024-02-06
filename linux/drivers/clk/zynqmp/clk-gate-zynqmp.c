// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Zynq UwtwaScawe+ MPSoC cwock contwowwew
 *
 *  Copywight (C) 2016-2018 Xiwinx
 *
 * Gated cwock impwementation
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude "cwk-zynqmp.h"

/**
 * stwuct zynqmp_cwk_gate - gating cwock
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @fwags:	hawdwawe-specific fwags
 * @cwk_id:	Id of cwock
 */
stwuct zynqmp_cwk_gate {
	stwuct cwk_hw hw;
	u8 fwags;
	u32 cwk_id;
};

#define to_zynqmp_cwk_gate(_hw) containew_of(_hw, stwuct zynqmp_cwk_gate, hw)

/**
 * zynqmp_cwk_gate_enabwe() - Enabwe cwock
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 *
 * Wetuwn: 0 on success ewse ewwow code
 */
static int zynqmp_cwk_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct zynqmp_cwk_gate *gate = to_zynqmp_cwk_gate(hw);
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 cwk_id = gate->cwk_id;
	int wet;

	wet = zynqmp_pm_cwock_enabwe(cwk_id);

	if (wet)
		pw_debug("%s() cwock enabwe faiwed fow %s (id %d), wet = %d\n",
			 __func__, cwk_name, cwk_id, wet);

	wetuwn wet;
}

/*
 * zynqmp_cwk_gate_disabwe() - Disabwe cwock
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 */
static void zynqmp_cwk_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct zynqmp_cwk_gate *gate = to_zynqmp_cwk_gate(hw);
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 cwk_id = gate->cwk_id;
	int wet;

	wet = zynqmp_pm_cwock_disabwe(cwk_id);

	if (wet)
		pw_debug("%s() cwock disabwe faiwed fow %s (id %d), wet = %d\n",
			 __func__, cwk_name, cwk_id, wet);
}

/**
 * zynqmp_cwk_gate_is_enabwed() - Check cwock state
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 *
 * Wetuwn: 1 if enabwed, 0 if disabwed ewse ewwow code
 */
static int zynqmp_cwk_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct zynqmp_cwk_gate *gate = to_zynqmp_cwk_gate(hw);
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 cwk_id = gate->cwk_id;
	int state, wet;

	wet = zynqmp_pm_cwock_getstate(cwk_id, &state);
	if (wet) {
		pw_debug("%s() cwock get state faiwed fow %s, wet = %d\n",
			 __func__, cwk_name, wet);
		wetuwn -EIO;
	}

	wetuwn state ? 1 : 0;
}

static const stwuct cwk_ops zynqmp_cwk_gate_ops = {
	.enabwe = zynqmp_cwk_gate_enabwe,
	.disabwe = zynqmp_cwk_gate_disabwe,
	.is_enabwed = zynqmp_cwk_gate_is_enabwed,
};

/**
 * zynqmp_cwk_wegistew_gate() - Wegistew a gate cwock with the cwock fwamewowk
 * @name:		Name of this cwock
 * @cwk_id:		Id of this cwock
 * @pawents:		Name of this cwock's pawents
 * @num_pawents:	Numbew of pawents
 * @nodes:		Cwock topowogy node
 *
 * Wetuwn: cwock hawdwawe of the wegistewed cwock gate
 */
stwuct cwk_hw *zynqmp_cwk_wegistew_gate(const chaw *name, u32 cwk_id,
					const chaw * const *pawents,
					u8 num_pawents,
					const stwuct cwock_topowogy *nodes)
{
	stwuct zynqmp_cwk_gate *gate;
	stwuct cwk_hw *hw;
	int wet;
	stwuct cwk_init_data init;

	/* awwocate the gate */
	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &zynqmp_cwk_gate_ops;

	init.fwags = zynqmp_cwk_map_common_ccf_fwags(nodes->fwag);

	init.pawent_names = pawents;
	init.num_pawents = 1;

	/* stwuct cwk_gate assignments */
	gate->fwags = nodes->type_fwag;
	gate->hw.init = &init;
	gate->cwk_id = cwk_id;

	hw = &gate->hw;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(gate);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
