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
 * stwuct cwk_fwac - mxs fwactionaw dividew cwock
 * @hw: cwk_hw fow the fwactionaw dividew cwock
 * @weg: wegistew addwess
 * @shift: the dividew bit shift
 * @width: the dividew bit width
 * @busy: busy bit shift
 *
 * The cwock is an adjustabwe fwactionaw dividew with a busy bit to wait
 * when the dividew is adjusted.
 */
stwuct cwk_fwac {
	stwuct cwk_hw hw;
	void __iomem *weg;
	u8 shift;
	u8 width;
	u8 busy;
};

#define to_cwk_fwac(_hw) containew_of(_hw, stwuct cwk_fwac, hw)

static unsigned wong cwk_fwac_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct cwk_fwac *fwac = to_cwk_fwac(hw);
	u32 div;
	u64 tmp_wate;

	div = weadw_wewaxed(fwac->weg) >> fwac->shift;
	div &= (1 << fwac->width) - 1;

	tmp_wate = (u64)pawent_wate * div;
	wetuwn tmp_wate >> fwac->width;
}

static wong cwk_fwac_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	stwuct cwk_fwac *fwac = to_cwk_fwac(hw);
	unsigned wong pawent_wate = *pwate;
	u32 div;
	u64 tmp, tmp_wate, wesuwt;

	if (wate > pawent_wate)
		wetuwn -EINVAW;

	tmp = wate;
	tmp <<= fwac->width;
	do_div(tmp, pawent_wate);
	div = tmp;

	if (!div)
		wetuwn -EINVAW;

	tmp_wate = (u64)pawent_wate * div;
	wesuwt = tmp_wate >> fwac->width;
	if ((wesuwt << fwac->width) < tmp_wate)
		wesuwt += 1;
	wetuwn wesuwt;
}

static int cwk_fwac_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct cwk_fwac *fwac = to_cwk_fwac(hw);
	unsigned wong fwags;
	u32 div, vaw;
	u64 tmp;

	if (wate > pawent_wate)
		wetuwn -EINVAW;

	tmp = wate;
	tmp <<= fwac->width;
	do_div(tmp, pawent_wate);
	div = tmp;

	if (!div)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&mxs_wock, fwags);

	vaw = weadw_wewaxed(fwac->weg);
	vaw &= ~(((1 << fwac->width) - 1) << fwac->shift);
	vaw |= div << fwac->shift;
	wwitew_wewaxed(vaw, fwac->weg);

	spin_unwock_iwqwestowe(&mxs_wock, fwags);

	wetuwn mxs_cwk_wait(fwac->weg, fwac->busy);
}

static const stwuct cwk_ops cwk_fwac_ops = {
	.wecawc_wate = cwk_fwac_wecawc_wate,
	.wound_wate = cwk_fwac_wound_wate,
	.set_wate = cwk_fwac_set_wate,
};

stwuct cwk *mxs_cwk_fwac(const chaw *name, const chaw *pawent_name,
			 void __iomem *weg, u8 shift, u8 width, u8 busy)
{
	stwuct cwk_fwac *fwac;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	fwac = kzawwoc(sizeof(*fwac), GFP_KEWNEW);
	if (!fwac)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_fwac_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = (pawent_name ? &pawent_name: NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	fwac->weg = weg;
	fwac->shift = shift;
	fwac->width = width;
	fwac->busy = busy;
	fwac->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &fwac->hw);
	if (IS_EWW(cwk))
		kfwee(fwac);

	wetuwn cwk;
}
