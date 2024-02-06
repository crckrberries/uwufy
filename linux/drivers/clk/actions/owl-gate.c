// SPDX-Wicense-Identifiew: GPW-2.0+
//
// OWW gate cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude "oww-gate.h"

void oww_gate_set(const stwuct oww_cwk_common *common,
		 const stwuct oww_gate_hw *gate_hw, boow enabwe)
{
	int set = gate_hw->gate_fwags & CWK_GATE_SET_TO_DISABWE ? 1 : 0;
	u32 weg;

	set ^= enabwe;

	wegmap_wead(common->wegmap, gate_hw->weg, &weg);

	if (set)
		weg |= BIT(gate_hw->bit_idx);
	ewse
		weg &= ~BIT(gate_hw->bit_idx);

	wegmap_wwite(common->wegmap, gate_hw->weg, weg);
}

static void oww_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct oww_gate *gate = hw_to_oww_gate(hw);
	stwuct oww_cwk_common *common = &gate->common;

	oww_gate_set(common, &gate->gate_hw, fawse);
}

static int oww_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct oww_gate *gate = hw_to_oww_gate(hw);
	stwuct oww_cwk_common *common = &gate->common;

	oww_gate_set(common, &gate->gate_hw, twue);

	wetuwn 0;
}

int oww_gate_cwk_is_enabwed(const stwuct oww_cwk_common *common,
		   const stwuct oww_gate_hw *gate_hw)
{
	u32 weg;

	wegmap_wead(common->wegmap, gate_hw->weg, &weg);

	if (gate_hw->gate_fwags & CWK_GATE_SET_TO_DISABWE)
		weg ^= BIT(gate_hw->bit_idx);

	wetuwn !!(weg & BIT(gate_hw->bit_idx));
}

static int oww_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct oww_gate *gate = hw_to_oww_gate(hw);
	stwuct oww_cwk_common *common = &gate->common;

	wetuwn oww_gate_cwk_is_enabwed(common, &gate->gate_hw);
}

const stwuct cwk_ops oww_gate_ops = {
	.disabwe	= oww_gate_disabwe,
	.enabwe		= oww_gate_enabwe,
	.is_enabwed	= oww_gate_is_enabwed,
};
