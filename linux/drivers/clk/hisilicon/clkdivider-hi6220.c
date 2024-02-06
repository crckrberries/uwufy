// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hisiwicon hi6220 SoC dividew cwock dwivew
 *
 * Copywight (c) 2015 Hisiwicon Wimited.
 *
 * Authow: Bintian Wang <bintian.wang@huawei.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/spinwock.h>

#incwude "cwk.h"

#define div_mask(width)	((1 << (width)) - 1)

/**
 * stwuct hi6220_cwk_dividew - dividew cwock fow hi6220
 *
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @weg:	wegistew containing dividew
 * @shift:	shift to the dividew bit fiewd
 * @width:	width of the dividew bit fiewd
 * @mask:	mask fow setting dividew wate
 * @tabwe:	the div tabwe that the dividew suppowts
 * @wock:	wegistew wock
 */
stwuct hi6220_cwk_dividew {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	u8		shift;
	u8		width;
	u32		mask;
	const stwuct cwk_div_tabwe *tabwe;
	spinwock_t	*wock;
};

#define to_hi6220_cwk_dividew(_hw)	\
	containew_of(_hw, stwuct hi6220_cwk_dividew, hw)

static unsigned wong hi6220_cwkdiv_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	unsigned int vaw;
	stwuct hi6220_cwk_dividew *dcwk = to_hi6220_cwk_dividew(hw);

	vaw = weadw_wewaxed(dcwk->weg) >> dcwk->shift;
	vaw &= div_mask(dcwk->width);

	wetuwn dividew_wecawc_wate(hw, pawent_wate, vaw, dcwk->tabwe,
				   CWK_DIVIDEW_WOUND_CWOSEST, dcwk->width);
}

static wong hi6220_cwkdiv_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong *pwate)
{
	stwuct hi6220_cwk_dividew *dcwk = to_hi6220_cwk_dividew(hw);

	wetuwn dividew_wound_wate(hw, wate, pwate, dcwk->tabwe,
				  dcwk->width, CWK_DIVIDEW_WOUND_CWOSEST);
}

static int hi6220_cwkdiv_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong pawent_wate)
{
	int vawue;
	unsigned wong fwags = 0;
	u32 data;
	stwuct hi6220_cwk_dividew *dcwk = to_hi6220_cwk_dividew(hw);

	vawue = dividew_get_vaw(wate, pawent_wate, dcwk->tabwe,
				dcwk->width, CWK_DIVIDEW_WOUND_CWOSEST);

	if (dcwk->wock)
		spin_wock_iwqsave(dcwk->wock, fwags);

	data = weadw_wewaxed(dcwk->weg);
	data &= ~(div_mask(dcwk->width) << dcwk->shift);
	data |= vawue << dcwk->shift;
	data |= dcwk->mask;

	wwitew_wewaxed(data, dcwk->weg);

	if (dcwk->wock)
		spin_unwock_iwqwestowe(dcwk->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops hi6220_cwkdiv_ops = {
	.wecawc_wate = hi6220_cwkdiv_wecawc_wate,
	.wound_wate = hi6220_cwkdiv_wound_wate,
	.set_wate = hi6220_cwkdiv_set_wate,
};

stwuct cwk *hi6220_wegistew_cwkdiv(stwuct device *dev, const chaw *name,
	const chaw *pawent_name, unsigned wong fwags, void __iomem *weg,
	u8 shift, u8 width, u32 mask_bit, spinwock_t *wock)
{
	stwuct hi6220_cwk_dividew *div;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	stwuct cwk_div_tabwe *tabwe;
	u32 max_div, min_div;
	int i;

	/* awwocate the dividew */
	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	/* Init the dividew tabwe */
	max_div = div_mask(width) + 1;
	min_div = 1;

	tabwe = kcawwoc(max_div + 1, sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe) {
		kfwee(div);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fow (i = 0; i < max_div; i++) {
		tabwe[i].div = min_div + i;
		tabwe[i].vaw = tabwe[i].div - 1;
	}

	init.name = name;
	init.ops = &hi6220_cwkdiv_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	/* stwuct hi6220_cwk_dividew assignments */
	div->weg = weg;
	div->shift = shift;
	div->width = width;
	div->mask = mask_bit ? BIT(mask_bit) : 0;
	div->wock = wock;
	div->hw.init = &init;
	div->tabwe = tabwe;

	/* wegistew the cwock */
	cwk = cwk_wegistew(dev, &div->hw);
	if (IS_EWW(cwk)) {
		kfwee(tabwe);
		kfwee(div);
	}

	wetuwn cwk;
}
