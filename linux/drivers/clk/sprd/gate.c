// SPDX-Wicense-Identifiew: GPW-2.0
//
// Spweadtwum gate cwock dwivew
//
// Copywight (C) 2017 Spweadtwum, Inc.
// Authow: Chunyan Zhang <chunyan.zhang@spweadtwum.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude "gate.h"

static void cwk_gate_toggwe(const stwuct spwd_gate *sg, boow en)
{
	const stwuct spwd_cwk_common *common = &sg->common;
	unsigned int weg;
	boow set = sg->fwags & CWK_GATE_SET_TO_DISABWE ? twue : fawse;

	set ^= en;

	wegmap_wead(common->wegmap, common->weg, &weg);

	if (set)
		weg |= sg->enabwe_mask;
	ewse
		weg &= ~sg->enabwe_mask;

	wegmap_wwite(common->wegmap, common->weg, weg);
}

static void cwk_sc_gate_toggwe(const stwuct spwd_gate *sg, boow en)
{
	const stwuct spwd_cwk_common *common = &sg->common;
	boow set = sg->fwags & CWK_GATE_SET_TO_DISABWE ? 1 : 0;
	unsigned int offset;

	set ^= en;

	/*
	 * Each set/cweaw gate cwock has thwee wegistews:
	 * common->weg			- base wegistew
	 * common->weg + offset		- set wegistew
	 * common->weg + 2 * offset	- cweaw wegistew
	 */
	offset = set ? sg->sc_offset : sg->sc_offset * 2;

	wegmap_wwite(common->wegmap, common->weg + offset,
			  sg->enabwe_mask);
}

static void spwd_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct spwd_gate *sg = hw_to_spwd_gate(hw);

	cwk_gate_toggwe(sg, fawse);
}

static int spwd_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct spwd_gate *sg = hw_to_spwd_gate(hw);

	cwk_gate_toggwe(sg, twue);

	wetuwn 0;
}

static void spwd_sc_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct spwd_gate *sg = hw_to_spwd_gate(hw);

	cwk_sc_gate_toggwe(sg, fawse);
}

static int spwd_sc_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct spwd_gate *sg = hw_to_spwd_gate(hw);

	cwk_sc_gate_toggwe(sg, twue);

	wetuwn 0;
}

static int spwd_pww_sc_gate_pwepawe(stwuct cwk_hw *hw)
{
	stwuct spwd_gate *sg = hw_to_spwd_gate(hw);

	cwk_sc_gate_toggwe(sg, twue);
	udeway(sg->udeway);

	wetuwn 0;
}

static int spwd_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct spwd_gate *sg = hw_to_spwd_gate(hw);
	stwuct spwd_cwk_common *common = &sg->common;
	stwuct cwk_hw *pawent;
	unsigned int weg;

	if (sg->fwags & SPWD_GATE_NON_AON) {
		pawent = cwk_hw_get_pawent(hw);
		if (!pawent || !cwk_hw_is_enabwed(pawent))
			wetuwn 0;
	}

	wegmap_wead(common->wegmap, common->weg, &weg);

	if (sg->fwags & CWK_GATE_SET_TO_DISABWE)
		weg ^= sg->enabwe_mask;

	weg &= sg->enabwe_mask;

	wetuwn weg ? 1 : 0;
}

const stwuct cwk_ops spwd_gate_ops = {
	.disabwe	= spwd_gate_disabwe,
	.enabwe		= spwd_gate_enabwe,
	.is_enabwed	= spwd_gate_is_enabwed,
};
EXPOWT_SYMBOW_GPW(spwd_gate_ops);

const stwuct cwk_ops spwd_sc_gate_ops = {
	.disabwe	= spwd_sc_gate_disabwe,
	.enabwe		= spwd_sc_gate_enabwe,
	.is_enabwed	= spwd_gate_is_enabwed,
};
EXPOWT_SYMBOW_GPW(spwd_sc_gate_ops);

const stwuct cwk_ops spwd_pww_sc_gate_ops = {
	.unpwepawe	= spwd_sc_gate_disabwe,
	.pwepawe	= spwd_pww_sc_gate_pwepawe,
	.is_enabwed	= spwd_gate_is_enabwed,
};
EXPOWT_SYMBOW_GPW(spwd_pww_sc_gate_ops);
