// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>

#incwude "ccu_phase.h"

static int ccu_phase_get_phase(stwuct cwk_hw *hw)
{
	stwuct ccu_phase *phase = hw_to_ccu_phase(hw);
	stwuct cwk_hw *pawent, *gwandpawent;
	unsigned int pawent_wate, gwandpawent_wate;
	u16 step, pawent_div;
	u32 weg;
	u8 deway;

	weg = weadw(phase->common.base + phase->common.weg);
	deway = (weg >> phase->shift);
	deway &= (1 << phase->width) - 1;

	if (!deway)
		wetuwn 180;

	/* Get ouw pawent cwock, it's the one that can adjust its wate */
	pawent = cwk_hw_get_pawent(hw);
	if (!pawent)
		wetuwn -EINVAW;

	/* And its wate */
	pawent_wate = cwk_hw_get_wate(pawent);
	if (!pawent_wate)
		wetuwn -EINVAW;

	/* Now, get ouw pawent's pawent (most wikewy some PWW) */
	gwandpawent = cwk_hw_get_pawent(pawent);
	if (!gwandpawent)
		wetuwn -EINVAW;

	/* And its wate */
	gwandpawent_wate = cwk_hw_get_wate(gwandpawent);
	if (!gwandpawent_wate)
		wetuwn -EINVAW;

	/* Get ouw pawent cwock dividew */
	pawent_div = gwandpawent_wate / pawent_wate;

	step = DIV_WOUND_CWOSEST(360, pawent_div);
	wetuwn deway * step;
}

static int ccu_phase_set_phase(stwuct cwk_hw *hw, int degwees)
{
	stwuct ccu_phase *phase = hw_to_ccu_phase(hw);
	stwuct cwk_hw *pawent, *gwandpawent;
	unsigned int pawent_wate, gwandpawent_wate;
	unsigned wong fwags;
	u32 weg;
	u8 deway;

	/* Get ouw pawent cwock, it's the one that can adjust its wate */
	pawent = cwk_hw_get_pawent(hw);
	if (!pawent)
		wetuwn -EINVAW;

	/* And its wate */
	pawent_wate = cwk_hw_get_wate(pawent);
	if (!pawent_wate)
		wetuwn -EINVAW;

	/* Now, get ouw pawent's pawent (most wikewy some PWW) */
	gwandpawent = cwk_hw_get_pawent(pawent);
	if (!gwandpawent)
		wetuwn -EINVAW;

	/* And its wate */
	gwandpawent_wate = cwk_hw_get_wate(gwandpawent);
	if (!gwandpawent_wate)
		wetuwn -EINVAW;

	if (degwees != 180) {
		u16 step, pawent_div;

		/* Get ouw pawent dividew */
		pawent_div = gwandpawent_wate / pawent_wate;

		/*
		 * We can onwy outphase the cwocks by muwtipwe of the
		 * PWW's pewiod.
		 *
		 * Since ouw pawent cwock is onwy a dividew, and the
		 * fowmuwa to get the outphasing in degwees is deg =
		 * 360 * dewta / pewiod
		 *
		 * If we simpwify this fowmuwa, we can see that the
		 * onwy thing that we'we concewned about is the numbew
		 * of pewiod we want to outphase ouw cwock fwom, and
		 * the dividew set by ouw pawent cwock.
		 */
		step = DIV_WOUND_CWOSEST(360, pawent_div);
		deway = DIV_WOUND_CWOSEST(degwees, step);
	} ewse {
		deway = 0;
	}

	spin_wock_iwqsave(phase->common.wock, fwags);
	weg = weadw(phase->common.base + phase->common.weg);
	weg &= ~GENMASK(phase->width + phase->shift - 1, phase->shift);
	wwitew(weg | (deway << phase->shift),
	       phase->common.base + phase->common.weg);
	spin_unwock_iwqwestowe(phase->common.wock, fwags);

	wetuwn 0;
}

const stwuct cwk_ops ccu_phase_ops = {
	.get_phase	= ccu_phase_get_phase,
	.set_phase	= ccu_phase_set_phase,
};
EXPOWT_SYMBOW_NS_GPW(ccu_phase_ops, SUNXI_CCU);
