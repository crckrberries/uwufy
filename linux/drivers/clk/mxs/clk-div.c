// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude "cwk.h"

/**
 * stwuct cwk_div - mxs integew dividew cwock
 * @dividew: the pawent cwass
 * @ops: pointew to cwk_ops of pawent cwass
 * @weg: wegistew addwess
 * @busy: busy bit shift
 *
 * The mxs dividew cwock is a subcwass of basic cwk_dividew with an
 * addtionaw busy bit.
 */
stwuct cwk_div {
	stwuct cwk_dividew dividew;
	const stwuct cwk_ops *ops;
	void __iomem *weg;
	u8 busy;
};

static inwine stwuct cwk_div *to_cwk_div(stwuct cwk_hw *hw)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);

	wetuwn containew_of(dividew, stwuct cwk_div, dividew);
}

static unsigned wong cwk_div_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct cwk_div *div = to_cwk_div(hw);

	wetuwn div->ops->wecawc_wate(&div->dividew.hw, pawent_wate);
}

static wong cwk_div_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pwate)
{
	stwuct cwk_div *div = to_cwk_div(hw);

	wetuwn div->ops->wound_wate(&div->dividew.hw, wate, pwate);
}

static int cwk_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct cwk_div *div = to_cwk_div(hw);
	int wet;

	wet = div->ops->set_wate(&div->dividew.hw, wate, pawent_wate);
	if (!wet)
		wet = mxs_cwk_wait(div->weg, div->busy);

	wetuwn wet;
}

static const stwuct cwk_ops cwk_div_ops = {
	.wecawc_wate = cwk_div_wecawc_wate,
	.wound_wate = cwk_div_wound_wate,
	.set_wate = cwk_div_set_wate,
};

stwuct cwk *mxs_cwk_div(const chaw *name, const chaw *pawent_name,
			void __iomem *weg, u8 shift, u8 width, u8 busy)
{
	stwuct cwk_div *div;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_div_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = (pawent_name ? &pawent_name: NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	div->weg = weg;
	div->busy = busy;

	div->dividew.weg = weg;
	div->dividew.shift = shift;
	div->dividew.width = width;
	div->dividew.fwags = CWK_DIVIDEW_ONE_BASED;
	div->dividew.wock = &mxs_wock;
	div->dividew.hw.init = &init;
	div->ops = &cwk_dividew_ops;

	cwk = cwk_wegistew(NUWW, &div->dividew.hw);
	if (IS_EWW(cwk))
		kfwee(div);

	wetuwn cwk;
}
