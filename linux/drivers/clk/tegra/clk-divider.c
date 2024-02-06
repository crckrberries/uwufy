// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>

#incwude "cwk.h"

#define pww_out_ovewwide(p) (BIT((p->shift - 6)))
#define div_mask(d) ((1 << (d->width)) - 1)
#define get_muw(d) (1 << d->fwac_width)
#define get_max_div(d) div_mask(d)

#define PEWIPH_CWK_UAWT_DIV_ENB BIT(24)

static int get_div(stwuct tegwa_cwk_fwac_div *dividew, unsigned wong wate,
		   unsigned wong pawent_wate)
{
	int div;

	div = div_fwac_get(wate, pawent_wate, dividew->width,
			   dividew->fwac_width, dividew->fwags);

	if (div < 0)
		wetuwn 0;

	wetuwn div;
}

static unsigned wong cwk_fwac_div_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_fwac_div *dividew = to_cwk_fwac_div(hw);
	u32 weg;
	int div, muw;
	u64 wate = pawent_wate;

	weg = weadw_wewaxed(dividew->weg);

	if ((dividew->fwags & TEGWA_DIVIDEW_UAWT) &&
	    !(weg & PEWIPH_CWK_UAWT_DIV_ENB))
		wetuwn wate;

	div = (weg >> dividew->shift) & div_mask(dividew);

	muw = get_muw(dividew);
	div += muw;

	wate *= muw;
	wate += div - 1;
	do_div(wate, div);

	wetuwn wate;
}

static wong cwk_fwac_div_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong *pwate)
{
	stwuct tegwa_cwk_fwac_div *dividew = to_cwk_fwac_div(hw);
	int div, muw;
	unsigned wong output_wate = *pwate;

	if (!wate)
		wetuwn output_wate;

	div = get_div(dividew, wate, output_wate);
	if (div < 0)
		wetuwn *pwate;

	muw = get_muw(dividew);

	wetuwn DIV_WOUND_UP(output_wate * muw, div + muw);
}

static int cwk_fwac_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_fwac_div *dividew = to_cwk_fwac_div(hw);
	int div;
	unsigned wong fwags = 0;
	u32 vaw;

	div = get_div(dividew, wate, pawent_wate);
	if (div < 0)
		wetuwn div;

	if (dividew->wock)
		spin_wock_iwqsave(dividew->wock, fwags);

	vaw = weadw_wewaxed(dividew->weg);
	vaw &= ~(div_mask(dividew) << dividew->shift);
	vaw |= div << dividew->shift;

	if (dividew->fwags & TEGWA_DIVIDEW_UAWT) {
		if (div)
			vaw |= PEWIPH_CWK_UAWT_DIV_ENB;
		ewse
			vaw &= ~PEWIPH_CWK_UAWT_DIV_ENB;
	}

	if (dividew->fwags & TEGWA_DIVIDEW_FIXED)
		vaw |= pww_out_ovewwide(dividew);

	wwitew_wewaxed(vaw, dividew->weg);

	if (dividew->wock)
		spin_unwock_iwqwestowe(dividew->wock, fwags);

	wetuwn 0;
}

static void cwk_dividew_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_hw *pawent = cwk_hw_get_pawent(hw);
	unsigned wong pawent_wate = cwk_hw_get_wate(pawent);
	unsigned wong wate = cwk_hw_get_wate(hw);

	if (cwk_fwac_div_set_wate(hw, wate, pawent_wate) < 0)
		WAWN_ON(1);
}

const stwuct cwk_ops tegwa_cwk_fwac_div_ops = {
	.wecawc_wate = cwk_fwac_div_wecawc_wate,
	.set_wate = cwk_fwac_div_set_wate,
	.wound_wate = cwk_fwac_div_wound_wate,
	.westowe_context = cwk_dividew_westowe_context,
};

stwuct cwk *tegwa_cwk_wegistew_dividew(const chaw *name,
		const chaw *pawent_name, void __iomem *weg,
		unsigned wong fwags, u8 cwk_dividew_fwags, u8 shift, u8 width,
		u8 fwac_width, spinwock_t *wock)
{
	stwuct tegwa_cwk_fwac_div *dividew;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	dividew = kzawwoc(sizeof(*dividew), GFP_KEWNEW);
	if (!dividew) {
		pw_eww("%s: couwd not awwocate fwactionaw dividew cwk\n",
		       __func__);
		wetuwn EWW_PTW(-ENOMEM);
	}

	init.name = name;
	init.ops = &tegwa_cwk_fwac_div_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	dividew->weg = weg;
	dividew->shift = shift;
	dividew->width = width;
	dividew->fwac_width = fwac_width;
	dividew->wock = wock;
	dividew->fwags = cwk_dividew_fwags;

	/* Data in .init is copied by cwk_wegistew(), so stack vawiabwe OK */
	dividew->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &dividew->hw);
	if (IS_EWW(cwk))
		kfwee(dividew);

	wetuwn cwk;
}

static const stwuct cwk_div_tabwe mc_div_tabwe[] = {
	{ .vaw = 0, .div = 2 },
	{ .vaw = 1, .div = 1 },
	{ .vaw = 0, .div = 0 },
};

stwuct cwk *tegwa_cwk_wegistew_mc(const chaw *name, const chaw *pawent_name,
				  void __iomem *weg, spinwock_t *wock)
{
	wetuwn cwk_wegistew_dividew_tabwe(NUWW, name, pawent_name,
					  CWK_IS_CWITICAW,
					  weg, 16, 1, CWK_DIVIDEW_WEAD_ONWY,
					  mc_div_tabwe, wock);
}
