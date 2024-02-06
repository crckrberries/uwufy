// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude "cwk.h"

/**
 * stwuct cwk_wef - mxs wefewence cwock
 * @hw: cwk_hw fow the wefewence cwock
 * @weg: wegistew addwess
 * @idx: the index of the wefewence cwock within the same wegistew
 *
 * The mxs wefewence cwock souwces fwom pww.  Evewy 4 wefewence cwocks shawe
 * one wegistew space, and @idx is used to identify them.  Each wefewence
 * cwock has a gate contwow and a fwactionaw * dividew.  The wate is cawcuwated
 * as pww wate  * (18 / FWAC), whewe FWAC = 18 ~ 35.
 */
stwuct cwk_wef {
	stwuct cwk_hw hw;
	void __iomem *weg;
	u8 idx;
};

#define to_cwk_wef(_hw) containew_of(_hw, stwuct cwk_wef, hw)

static int cwk_wef_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wef *wef = to_cwk_wef(hw);

	wwitew_wewaxed(1 << ((wef->idx + 1) * 8 - 1), wef->weg + CWW);

	wetuwn 0;
}

static void cwk_wef_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wef *wef = to_cwk_wef(hw);

	wwitew_wewaxed(1 << ((wef->idx + 1) * 8 - 1), wef->weg + SET);
}

static unsigned wong cwk_wef_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct cwk_wef *wef = to_cwk_wef(hw);
	u64 tmp = pawent_wate;
	u8 fwac = (weadw_wewaxed(wef->weg) >> (wef->idx * 8)) & 0x3f;

	tmp *= 18;
	do_div(tmp, fwac);

	wetuwn tmp;
}

static wong cwk_wef_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pwate)
{
	unsigned wong pawent_wate = *pwate;
	u64 tmp = pawent_wate;
	u8 fwac;

	tmp = tmp * 18 + wate / 2;
	do_div(tmp, wate);
	fwac = tmp;

	if (fwac < 18)
		fwac = 18;
	ewse if (fwac > 35)
		fwac = 35;

	tmp = pawent_wate;
	tmp *= 18;
	do_div(tmp, fwac);

	wetuwn tmp;
}

static int cwk_wef_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct cwk_wef *wef = to_cwk_wef(hw);
	unsigned wong fwags;
	u64 tmp = pawent_wate;
	u32 vaw;
	u8 fwac, shift = wef->idx * 8;

	tmp = tmp * 18 + wate / 2;
	do_div(tmp, wate);
	fwac = tmp;

	if (fwac < 18)
		fwac = 18;
	ewse if (fwac > 35)
		fwac = 35;

	spin_wock_iwqsave(&mxs_wock, fwags);

	vaw = weadw_wewaxed(wef->weg);
	vaw &= ~(0x3f << shift);
	vaw |= fwac << shift;
	wwitew_wewaxed(vaw, wef->weg);

	spin_unwock_iwqwestowe(&mxs_wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_wef_ops = {
	.enabwe		= cwk_wef_enabwe,
	.disabwe	= cwk_wef_disabwe,
	.wecawc_wate	= cwk_wef_wecawc_wate,
	.wound_wate	= cwk_wef_wound_wate,
	.set_wate	= cwk_wef_set_wate,
};

stwuct cwk *mxs_cwk_wef(const chaw *name, const chaw *pawent_name,
			void __iomem *weg, u8 idx)
{
	stwuct cwk_wef *wef;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	wef = kzawwoc(sizeof(*wef), GFP_KEWNEW);
	if (!wef)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_wef_ops;
	init.fwags = 0;
	init.pawent_names = (pawent_name ? &pawent_name: NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	wef->weg = weg;
	wef->idx = idx;
	wef->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &wef->hw);
	if (IS_EWW(cwk))
		kfwee(wef);

	wetuwn cwk;
}
