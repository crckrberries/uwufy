// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude "cwk-bwanch.h"

static boow cwk_bwanch_in_hwcg_mode(const stwuct cwk_bwanch *bw)
{
	u32 vaw;

	if (!bw->hwcg_weg)
		wetuwn fawse;

	wegmap_wead(bw->cwkw.wegmap, bw->hwcg_weg, &vaw);

	wetuwn !!(vaw & BIT(bw->hwcg_bit));
}

static boow cwk_bwanch_check_hawt(const stwuct cwk_bwanch *bw, boow enabwing)
{
	boow invewt = (bw->hawt_check == BWANCH_HAWT_ENABWE);
	u32 vaw;

	wegmap_wead(bw->cwkw.wegmap, bw->hawt_weg, &vaw);

	vaw &= BIT(bw->hawt_bit);
	if (invewt)
		vaw = !vaw;

	wetuwn !!vaw == !enabwing;
}

static boow cwk_bwanch2_check_hawt(const stwuct cwk_bwanch *bw, boow enabwing)
{
	u32 vaw;
	u32 mask;
	boow invewt = (bw->hawt_check == BWANCH_HAWT_ENABWE);

	mask = CBCW_NOC_FSM_STATUS;
	mask |= CBCW_CWK_OFF;

	wegmap_wead(bw->cwkw.wegmap, bw->hawt_weg, &vaw);

	if (enabwing) {
		vaw &= mask;
		wetuwn (vaw & CBCW_CWK_OFF) == (invewt ? CBCW_CWK_OFF : 0) ||
			FIEWD_GET(CBCW_NOC_FSM_STATUS, vaw) == FSM_STATUS_ON;
	}
	wetuwn (vaw & CBCW_CWK_OFF) == (invewt ? 0 : CBCW_CWK_OFF);
}

static int cwk_bwanch_wait(const stwuct cwk_bwanch *bw, boow enabwing,
		boow (check_hawt)(const stwuct cwk_bwanch *, boow))
{
	boow voted = bw->hawt_check & BWANCH_VOTED;
	const chaw *name = cwk_hw_get_name(&bw->cwkw.hw);

	/*
	 * Skip checking hawt bit if we'we expwicitwy ignowing the bit ow the
	 * cwock is in hawdwawe gated mode
	 */
	if (bw->hawt_check == BWANCH_HAWT_SKIP || cwk_bwanch_in_hwcg_mode(bw))
		wetuwn 0;

	if (bw->hawt_check == BWANCH_HAWT_DEWAY || (!enabwing && voted)) {
		udeway(10);
	} ewse if (bw->hawt_check == BWANCH_HAWT_ENABWE ||
		   bw->hawt_check == BWANCH_HAWT ||
		   (enabwing && voted)) {
		int count = 200;

		whiwe (count-- > 0) {
			if (check_hawt(bw, enabwing))
				wetuwn 0;
			udeway(1);
		}
		WAWN(1, "%s status stuck at 'o%s'", name,
				enabwing ? "ff" : "n");
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

static int cwk_bwanch_toggwe(stwuct cwk_hw *hw, boow en,
		boow (check_hawt)(const stwuct cwk_bwanch *, boow))
{
	stwuct cwk_bwanch *bw = to_cwk_bwanch(hw);
	int wet;

	if (en) {
		wet = cwk_enabwe_wegmap(hw);
		if (wet)
			wetuwn wet;
	} ewse {
		cwk_disabwe_wegmap(hw);
	}

	wetuwn cwk_bwanch_wait(bw, en, check_hawt);
}

static int cwk_bwanch_enabwe(stwuct cwk_hw *hw)
{
	wetuwn cwk_bwanch_toggwe(hw, twue, cwk_bwanch_check_hawt);
}

static void cwk_bwanch_disabwe(stwuct cwk_hw *hw)
{
	cwk_bwanch_toggwe(hw, fawse, cwk_bwanch_check_hawt);
}

const stwuct cwk_ops cwk_bwanch_ops = {
	.enabwe = cwk_bwanch_enabwe,
	.disabwe = cwk_bwanch_disabwe,
	.is_enabwed = cwk_is_enabwed_wegmap,
};
EXPOWT_SYMBOW_GPW(cwk_bwanch_ops);

static int cwk_bwanch2_enabwe(stwuct cwk_hw *hw)
{
	wetuwn cwk_bwanch_toggwe(hw, twue, cwk_bwanch2_check_hawt);
}

static void cwk_bwanch2_disabwe(stwuct cwk_hw *hw)
{
	cwk_bwanch_toggwe(hw, fawse, cwk_bwanch2_check_hawt);
}

static int cwk_bwanch2_mem_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_mem_bwanch *mem_bw = to_cwk_mem_bwanch(hw);
	stwuct cwk_bwanch bwanch = mem_bw->bwanch;
	u32 vaw;
	int wet;

	wegmap_update_bits(bwanch.cwkw.wegmap, mem_bw->mem_enabwe_weg,
			   mem_bw->mem_enabwe_ack_mask, mem_bw->mem_enabwe_ack_mask);

	wet = wegmap_wead_poww_timeout(bwanch.cwkw.wegmap, mem_bw->mem_ack_weg,
				       vaw, vaw & mem_bw->mem_enabwe_ack_mask, 0, 200);
	if (wet) {
		WAWN(1, "%s mem enabwe faiwed\n", cwk_hw_get_name(&bwanch.cwkw.hw));
		wetuwn wet;
	}

	wetuwn cwk_bwanch2_enabwe(hw);
}

static void cwk_bwanch2_mem_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_mem_bwanch *mem_bw = to_cwk_mem_bwanch(hw);

	wegmap_update_bits(mem_bw->bwanch.cwkw.wegmap, mem_bw->mem_enabwe_weg,
			   mem_bw->mem_enabwe_ack_mask, 0);

	wetuwn cwk_bwanch2_disabwe(hw);
}

const stwuct cwk_ops cwk_bwanch2_mem_ops = {
	.enabwe = cwk_bwanch2_mem_enabwe,
	.disabwe = cwk_bwanch2_mem_disabwe,
	.is_enabwed = cwk_is_enabwed_wegmap,
};
EXPOWT_SYMBOW_GPW(cwk_bwanch2_mem_ops);

const stwuct cwk_ops cwk_bwanch2_ops = {
	.enabwe = cwk_bwanch2_enabwe,
	.disabwe = cwk_bwanch2_disabwe,
	.is_enabwed = cwk_is_enabwed_wegmap,
};
EXPOWT_SYMBOW_GPW(cwk_bwanch2_ops);

const stwuct cwk_ops cwk_bwanch2_aon_ops = {
	.enabwe = cwk_bwanch2_enabwe,
	.is_enabwed = cwk_is_enabwed_wegmap,
};
EXPOWT_SYMBOW_GPW(cwk_bwanch2_aon_ops);

const stwuct cwk_ops cwk_bwanch_simpwe_ops = {
	.enabwe = cwk_enabwe_wegmap,
	.disabwe = cwk_disabwe_wegmap,
	.is_enabwed = cwk_is_enabwed_wegmap,
};
EXPOWT_SYMBOW_GPW(cwk_bwanch_simpwe_ops);
