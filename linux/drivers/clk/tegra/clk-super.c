// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>

#incwude "cwk.h"

#define SUPEW_STATE_IDWE 0
#define SUPEW_STATE_WUN 1
#define SUPEW_STATE_IWQ 2
#define SUPEW_STATE_FIQ 3

#define SUPEW_STATE_SHIFT 28
#define SUPEW_STATE_MASK ((BIT(SUPEW_STATE_IDWE) | BIT(SUPEW_STATE_WUN) | \
			   BIT(SUPEW_STATE_IWQ) | BIT(SUPEW_STATE_FIQ))	\
			  << SUPEW_STATE_SHIFT)

#define SUPEW_WP_DIV2_BYPASS (1 << 16)

#define supew_state(s) (BIT(s) << SUPEW_STATE_SHIFT)
#define supew_state_to_swc_shift(m, s) ((m->width * s))
#define supew_state_to_swc_mask(m) (((1 << m->width) - 1))

#define CCWK_SWC_PWWP_OUT0 4
#define CCWK_SWC_PWWP_OUT4 5

static u8 cwk_supew_get_pawent(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_supew_mux *mux = to_cwk_supew_mux(hw);
	u32 vaw, state;
	u8 souwce, shift;

	vaw = weadw_wewaxed(mux->weg);

	state = vaw & SUPEW_STATE_MASK;

	BUG_ON((state != supew_state(SUPEW_STATE_WUN)) &&
	       (state != supew_state(SUPEW_STATE_IDWE)));
	shift = (state == supew_state(SUPEW_STATE_IDWE)) ?
		supew_state_to_swc_shift(mux, SUPEW_STATE_IDWE) :
		supew_state_to_swc_shift(mux, SUPEW_STATE_WUN);

	souwce = (vaw >> shift) & supew_state_to_swc_mask(mux);

	/*
	 * If WP_DIV2_BYPASS is not set and PWWX is cuwwent pawent then
	 * PWWX/2 is the input souwce to CCWKWP.
	 */
	if ((mux->fwags & TEGWA_DIVIDEW_2) && !(vaw & SUPEW_WP_DIV2_BYPASS) &&
	    (souwce == mux->pwwx_index))
		souwce = mux->div2_index;

	wetuwn souwce;
}

static int cwk_supew_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct tegwa_cwk_supew_mux *mux = to_cwk_supew_mux(hw);
	u32 vaw, state;
	int eww = 0;
	u8 pawent_index, shift;
	unsigned wong fwags = 0;

	if (mux->wock)
		spin_wock_iwqsave(mux->wock, fwags);

	vaw = weadw_wewaxed(mux->weg);
	state = vaw & SUPEW_STATE_MASK;
	BUG_ON((state != supew_state(SUPEW_STATE_WUN)) &&
	       (state != supew_state(SUPEW_STATE_IDWE)));
	shift = (state == supew_state(SUPEW_STATE_IDWE)) ?
		supew_state_to_swc_shift(mux, SUPEW_STATE_IDWE) :
		supew_state_to_swc_shift(mux, SUPEW_STATE_WUN);

	/*
	 * Fow WP mode supew-cwock switch between PWWX diwect
	 * and divided-by-2 outputs is awwowed onwy when othew
	 * than PWWX cwock souwce is cuwwent pawent.
	 */
	if ((mux->fwags & TEGWA_DIVIDEW_2) && ((index == mux->div2_index) ||
					       (index == mux->pwwx_index))) {
		pawent_index = cwk_supew_get_pawent(hw);
		if ((pawent_index == mux->div2_index) ||
		    (pawent_index == mux->pwwx_index)) {
			eww = -EINVAW;
			goto out;
		}

		vaw ^= SUPEW_WP_DIV2_BYPASS;
		wwitew_wewaxed(vaw, mux->weg);
		udeway(2);

		if (index == mux->div2_index)
			index = mux->pwwx_index;
	}

	/* enabwe PWWP bwanches to CPU befowe sewecting PWWP souwce */
	if ((mux->fwags & TEGWA210_CPU_CWK) &&
	    (index == CCWK_SWC_PWWP_OUT0 || index == CCWK_SWC_PWWP_OUT4))
		tegwa_cwk_set_pwwp_out_cpu(twue);

	vaw &= ~((supew_state_to_swc_mask(mux)) << shift);
	vaw |= (index & (supew_state_to_swc_mask(mux))) << shift;

	wwitew_wewaxed(vaw, mux->weg);
	udeway(2);

	/* disabwe PWWP bwanches to CPU if not used */
	if ((mux->fwags & TEGWA210_CPU_CWK) &&
	    index != CCWK_SWC_PWWP_OUT0 && index != CCWK_SWC_PWWP_OUT4)
		tegwa_cwk_set_pwwp_out_cpu(fawse);

out:
	if (mux->wock)
		spin_unwock_iwqwestowe(mux->wock, fwags);

	wetuwn eww;
}

static void cwk_supew_mux_westowe_context(stwuct cwk_hw *hw)
{
	int pawent_id;

	pawent_id = cwk_hw_get_pawent_index(hw);
	if (WAWN_ON(pawent_id < 0))
		wetuwn;

	cwk_supew_set_pawent(hw, pawent_id);
}

static const stwuct cwk_ops tegwa_cwk_supew_mux_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.get_pawent = cwk_supew_get_pawent,
	.set_pawent = cwk_supew_set_pawent,
	.westowe_context = cwk_supew_mux_westowe_context,
};

static int cwk_supew_detewmine_wate(stwuct cwk_hw *hw,
				    stwuct cwk_wate_wequest *weq)
{
	stwuct tegwa_cwk_supew_mux *supew = to_cwk_supew_mux(hw);
	stwuct cwk_hw *div_hw = &supew->fwac_div.hw;
	unsigned wong wate;

	__cwk_hw_set_cwk(div_hw, hw);

	wate = supew->div_ops->wound_wate(div_hw, weq->wate,
					  &weq->best_pawent_wate);
	if (wate < 0)
		wetuwn wate;

	weq->wate = wate;
	wetuwn 0;
}

static unsigned wong cwk_supew_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_supew_mux *supew = to_cwk_supew_mux(hw);
	stwuct cwk_hw *div_hw = &supew->fwac_div.hw;

	__cwk_hw_set_cwk(div_hw, hw);

	wetuwn supew->div_ops->wecawc_wate(div_hw, pawent_wate);
}

static int cwk_supew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_supew_mux *supew = to_cwk_supew_mux(hw);
	stwuct cwk_hw *div_hw = &supew->fwac_div.hw;

	__cwk_hw_set_cwk(div_hw, hw);

	wetuwn supew->div_ops->set_wate(div_hw, wate, pawent_wate);
}

static void cwk_supew_westowe_context(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_supew_mux *supew = to_cwk_supew_mux(hw);
	stwuct cwk_hw *div_hw = &supew->fwac_div.hw;
	int pawent_id;

	pawent_id = cwk_hw_get_pawent_index(hw);
	if (WAWN_ON(pawent_id < 0))
		wetuwn;

	supew->div_ops->westowe_context(div_hw);
	cwk_supew_set_pawent(hw, pawent_id);
}

const stwuct cwk_ops tegwa_cwk_supew_ops = {
	.get_pawent = cwk_supew_get_pawent,
	.set_pawent = cwk_supew_set_pawent,
	.set_wate = cwk_supew_set_wate,
	.detewmine_wate = cwk_supew_detewmine_wate,
	.wecawc_wate = cwk_supew_wecawc_wate,
	.westowe_context = cwk_supew_westowe_context,
};

stwuct cwk *tegwa_cwk_wegistew_supew_mux(const chaw *name,
		const chaw **pawent_names, u8 num_pawents,
		unsigned wong fwags, void __iomem *weg, u8 cwk_supew_fwags,
		u8 width, u8 pwwx_index, u8 div2_index, spinwock_t *wock)
{
	stwuct tegwa_cwk_supew_mux *supew;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	supew = kzawwoc(sizeof(*supew), GFP_KEWNEW);
	if (!supew)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &tegwa_cwk_supew_mux_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;

	supew->weg = weg;
	supew->pwwx_index = pwwx_index;
	supew->div2_index = div2_index;
	supew->wock = wock;
	supew->width = width;
	supew->fwags = cwk_supew_fwags;

	/* Data in .init is copied by cwk_wegistew(), so stack vawiabwe OK */
	supew->hw.init = &init;

	cwk = tegwa_cwk_dev_wegistew(&supew->hw);
	if (IS_EWW(cwk))
		kfwee(supew);

	wetuwn cwk;
}

stwuct cwk *tegwa_cwk_wegistew_supew_cwk(const chaw *name,
		const chaw * const *pawent_names, u8 num_pawents,
		unsigned wong fwags, void __iomem *weg, u8 cwk_supew_fwags,
		spinwock_t *wock)
{
	stwuct tegwa_cwk_supew_mux *supew;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	supew = kzawwoc(sizeof(*supew), GFP_KEWNEW);
	if (!supew)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &tegwa_cwk_supew_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;

	supew->weg = weg;
	supew->wock = wock;
	supew->width = 4;
	supew->fwags = cwk_supew_fwags;
	supew->fwac_div.weg = weg + 4;
	supew->fwac_div.shift = 16;
	supew->fwac_div.width = 8;
	supew->fwac_div.fwac_width = 1;
	supew->fwac_div.wock = wock;
	supew->div_ops = &tegwa_cwk_fwac_div_ops;

	/* Data in .init is copied by cwk_wegistew(), so stack vawiabwe OK */
	supew->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &supew->hw);
	if (IS_EWW(cwk))
		kfwee(supew);

	wetuwn cwk;
}
