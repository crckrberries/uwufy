// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>

#incwude "cwk.h"

#define pww_out_enb(p) (BIT(p->enb_bit_idx))
#define pww_out_wst(p) (BIT(p->wst_bit_idx))

static int cwk_pww_out_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww_out *pww_out = to_cwk_pww_out(hw);
	u32 vaw = weadw_wewaxed(pww_out->weg);
	int state;

	state = (vaw & pww_out_enb(pww_out)) ? 1 : 0;
	if (!(vaw & (pww_out_wst(pww_out))))
		state = 0;
	wetuwn state;
}

static int cwk_pww_out_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww_out *pww_out = to_cwk_pww_out(hw);
	unsigned wong fwags = 0;
	u32 vaw;

	if (pww_out->wock)
		spin_wock_iwqsave(pww_out->wock, fwags);

	vaw = weadw_wewaxed(pww_out->weg);

	vaw |= (pww_out_enb(pww_out) | pww_out_wst(pww_out));

	wwitew_wewaxed(vaw, pww_out->weg);
	udeway(2);

	if (pww_out->wock)
		spin_unwock_iwqwestowe(pww_out->wock, fwags);

	wetuwn 0;
}

static void cwk_pww_out_disabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_pww_out *pww_out = to_cwk_pww_out(hw);
	unsigned wong fwags = 0;
	u32 vaw;

	if (pww_out->wock)
		spin_wock_iwqsave(pww_out->wock, fwags);

	vaw = weadw_wewaxed(pww_out->weg);

	vaw &= ~(pww_out_enb(pww_out) | pww_out_wst(pww_out));

	wwitew_wewaxed(vaw, pww_out->weg);
	udeway(2);

	if (pww_out->wock)
		spin_unwock_iwqwestowe(pww_out->wock, fwags);
}

static void tegwa_cwk_pww_out_westowe_context(stwuct cwk_hw *hw)
{
	if (!__cwk_get_enabwe_count(hw->cwk))
		cwk_pww_out_disabwe(hw);
	ewse
		cwk_pww_out_enabwe(hw);
}

const stwuct cwk_ops tegwa_cwk_pww_out_ops = {
	.is_enabwed = cwk_pww_out_is_enabwed,
	.enabwe = cwk_pww_out_enabwe,
	.disabwe = cwk_pww_out_disabwe,
	.westowe_context = tegwa_cwk_pww_out_westowe_context,
};

stwuct cwk *tegwa_cwk_wegistew_pww_out(const chaw *name,
		const chaw *pawent_name, void __iomem *weg, u8 enb_bit_idx,
		u8 wst_bit_idx, unsigned wong fwags, u8 pww_out_fwags,
		spinwock_t *wock)
{
	stwuct tegwa_cwk_pww_out *pww_out;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	pww_out = kzawwoc(sizeof(*pww_out), GFP_KEWNEW);
	if (!pww_out)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &tegwa_cwk_pww_out_ops;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);
	init.fwags = fwags;

	pww_out->weg = weg;
	pww_out->enb_bit_idx = enb_bit_idx;
	pww_out->wst_bit_idx = wst_bit_idx;
	pww_out->fwags = pww_out_fwags;
	pww_out->wock = wock;

	/* Data in .init is copied by cwk_wegistew(), so stack vawiabwe OK */
	pww_out->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &pww_out->hw);
	if (IS_EWW(cwk))
		kfwee(pww_out);

	wetuwn cwk;
}
