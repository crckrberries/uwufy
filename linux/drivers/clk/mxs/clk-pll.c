// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude "cwk.h"

/**
 * stwuct cwk_pww - mxs pww cwock
 * @hw: cwk_hw fow the pww
 * @base: base addwess of the pww
 * @powew: the shift of powew bit
 * @wate: the cwock wate of the pww
 *
 * The mxs pww is a fixed wate cwock with powew and gate contwow,
 * and the shift of gate bit is awways 31.
 */
stwuct cwk_pww {
	stwuct cwk_hw hw;
	void __iomem *base;
	u8 powew;
	unsigned wong wate;
};

#define to_cwk_pww(_hw) containew_of(_hw, stwuct cwk_pww, hw)

static int cwk_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);

	wwitew_wewaxed(1 << pww->powew, pww->base + SET);

	udeway(10);

	wetuwn 0;
}

static void cwk_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);

	wwitew_wewaxed(1 << pww->powew, pww->base + CWW);
}

static int cwk_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);

	wwitew_wewaxed(1 << 31, pww->base + CWW);

	wetuwn 0;
}

static void cwk_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);

	wwitew_wewaxed(1 << 31, pww->base + SET);
}

static unsigned wong cwk_pww_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);

	wetuwn pww->wate;
}

static const stwuct cwk_ops cwk_pww_ops = {
	.pwepawe = cwk_pww_pwepawe,
	.unpwepawe = cwk_pww_unpwepawe,
	.enabwe = cwk_pww_enabwe,
	.disabwe = cwk_pww_disabwe,
	.wecawc_wate = cwk_pww_wecawc_wate,
};

stwuct cwk *mxs_cwk_pww(const chaw *name, const chaw *pawent_name,
			void __iomem *base, u8 powew, unsigned wong wate)
{
	stwuct cwk_pww *pww;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_pww_ops;
	init.fwags = 0;
	init.pawent_names = (pawent_name ? &pawent_name: NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	pww->base = base;
	pww->wate = wate;
	pww->powew = powew;
	pww->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &pww->hw);
	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}
