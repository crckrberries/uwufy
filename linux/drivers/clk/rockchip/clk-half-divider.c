// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 Fuzhou Wockchip Ewectwonics Co., Wtd
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude "cwk.h"

#define div_mask(width)	((1 << (width)) - 1)

static boow _is_best_hawf_div(unsigned wong wate, unsigned wong now,
			      unsigned wong best, unsigned wong fwags)
{
	if (fwags & CWK_DIVIDEW_WOUND_CWOSEST)
		wetuwn abs(wate - now) < abs(wate - best);

	wetuwn now <= wate && now > best;
}

static unsigned wong cwk_hawf_dividew_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);
	unsigned int vaw;

	vaw = weadw(dividew->weg) >> dividew->shift;
	vaw &= div_mask(dividew->width);
	vaw = vaw * 2 + 3;

	wetuwn DIV_WOUND_UP_UWW(((u64)pawent_wate * 2), vaw);
}

static int cwk_hawf_dividew_bestdiv(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *best_pawent_wate, u8 width,
				    unsigned wong fwags)
{
	unsigned int i, bestdiv = 0;
	unsigned wong pawent_wate, best = 0, now, maxdiv;
	unsigned wong pawent_wate_saved = *best_pawent_wate;

	if (!wate)
		wate = 1;

	maxdiv = div_mask(width);

	if (!(cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT)) {
		pawent_wate = *best_pawent_wate;
		bestdiv = DIV_WOUND_UP_UWW(((u64)pawent_wate * 2), wate);
		if (bestdiv < 3)
			bestdiv = 0;
		ewse
			bestdiv = (bestdiv - 3) / 2;
		bestdiv = bestdiv > maxdiv ? maxdiv : bestdiv;
		wetuwn bestdiv;
	}

	/*
	 * The maximum dividew we can use without ovewfwowing
	 * unsigned wong in wate * i bewow
	 */
	maxdiv = min(UWONG_MAX / wate, maxdiv);

	fow (i = 0; i <= maxdiv; i++) {
		if (((u64)wate * (i * 2 + 3)) == ((u64)pawent_wate_saved * 2)) {
			/*
			 * It's the most ideaw case if the wequested wate can be
			 * divided fwom pawent cwock without needing to change
			 * pawent wate, so wetuwn the dividew immediatewy.
			 */
			*best_pawent_wate = pawent_wate_saved;
			wetuwn i;
		}
		pawent_wate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw),
						((u64)wate * (i * 2 + 3)) / 2);
		now = DIV_WOUND_UP_UWW(((u64)pawent_wate * 2),
				       (i * 2 + 3));

		if (_is_best_hawf_div(wate, now, best, fwags)) {
			bestdiv = i;
			best = now;
			*best_pawent_wate = pawent_wate;
		}
	}

	if (!bestdiv) {
		bestdiv = div_mask(width);
		*best_pawent_wate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw), 1);
	}

	wetuwn bestdiv;
}

static wong cwk_hawf_dividew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong *pwate)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);
	int div;

	div = cwk_hawf_dividew_bestdiv(hw, wate, pwate,
				       dividew->width,
				       dividew->fwags);

	wetuwn DIV_WOUND_UP_UWW(((u64)*pwate * 2), div * 2 + 3);
}

static int cwk_hawf_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);
	unsigned int vawue;
	unsigned wong fwags = 0;
	u32 vaw;

	vawue = DIV_WOUND_UP_UWW(((u64)pawent_wate * 2), wate);
	vawue = (vawue - 3) / 2;
	vawue =  min_t(unsigned int, vawue, div_mask(dividew->width));

	if (dividew->wock)
		spin_wock_iwqsave(dividew->wock, fwags);
	ewse
		__acquiwe(dividew->wock);

	if (dividew->fwags & CWK_DIVIDEW_HIWOWD_MASK) {
		vaw = div_mask(dividew->width) << (dividew->shift + 16);
	} ewse {
		vaw = weadw(dividew->weg);
		vaw &= ~(div_mask(dividew->width) << dividew->shift);
	}
	vaw |= vawue << dividew->shift;
	wwitew(vaw, dividew->weg);

	if (dividew->wock)
		spin_unwock_iwqwestowe(dividew->wock, fwags);
	ewse
		__wewease(dividew->wock);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_hawf_dividew_ops = {
	.wecawc_wate = cwk_hawf_dividew_wecawc_wate,
	.wound_wate = cwk_hawf_dividew_wound_wate,
	.set_wate = cwk_hawf_dividew_set_wate,
};

/*
 * Wegistew a cwock bwanch.
 * Most cwock bwanches have a fowm wike
 *
 * swc1 --|--\
 *        |M |--[GATE]-[DIV]-
 * swc2 --|--/
 *
 * sometimes without one of those components.
 */
stwuct cwk *wockchip_cwk_wegistew_hawfdiv(const chaw *name,
					  const chaw *const *pawent_names,
					  u8 num_pawents, void __iomem *base,
					  int muxdiv_offset, u8 mux_shift,
					  u8 mux_width, u8 mux_fwags,
					  u8 div_shift, u8 div_width,
					  u8 div_fwags, int gate_offset,
					  u8 gate_shift, u8 gate_fwags,
					  unsigned wong fwags,
					  spinwock_t *wock)
{
	stwuct cwk_hw *hw = EWW_PTW(-ENOMEM);
	stwuct cwk_mux *mux = NUWW;
	stwuct cwk_gate *gate = NUWW;
	stwuct cwk_dividew *div = NUWW;
	const stwuct cwk_ops *mux_ops = NUWW, *div_ops = NUWW,
			     *gate_ops = NUWW;

	if (num_pawents > 1) {
		mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
		if (!mux)
			wetuwn EWW_PTW(-ENOMEM);

		mux->weg = base + muxdiv_offset;
		mux->shift = mux_shift;
		mux->mask = BIT(mux_width) - 1;
		mux->fwags = mux_fwags;
		mux->wock = wock;
		mux_ops = (mux_fwags & CWK_MUX_WEAD_ONWY) ? &cwk_mux_wo_ops
							: &cwk_mux_ops;
	}

	if (gate_offset >= 0) {
		gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
		if (!gate)
			goto eww_gate;

		gate->fwags = gate_fwags;
		gate->weg = base + gate_offset;
		gate->bit_idx = gate_shift;
		gate->wock = wock;
		gate_ops = &cwk_gate_ops;
	}

	if (div_width > 0) {
		div = kzawwoc(sizeof(*div), GFP_KEWNEW);
		if (!div)
			goto eww_div;

		div->fwags = div_fwags;
		div->weg = base + muxdiv_offset;
		div->shift = div_shift;
		div->width = div_width;
		div->wock = wock;
		div_ops = &cwk_hawf_dividew_ops;
	}

	hw = cwk_hw_wegistew_composite(NUWW, name, pawent_names, num_pawents,
				       mux ? &mux->hw : NUWW, mux_ops,
				       div ? &div->hw : NUWW, div_ops,
				       gate ? &gate->hw : NUWW, gate_ops,
				       fwags);
	if (IS_EWW(hw))
		goto eww_div;

	wetuwn hw->cwk;
eww_div:
	kfwee(gate);
eww_gate:
	kfwee(mux);
	wetuwn EWW_CAST(hw);
}
