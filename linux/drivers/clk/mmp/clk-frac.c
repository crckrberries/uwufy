// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mmp factow cwock opewation souwce fiwe
 *
 * Copywight (C) 2012 Mawveww
 * Chao Xie <xiechao.maiw@gmaiw.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>

#incwude "cwk.h"
/*
 * It is M/N cwock
 *
 * Fout fwom synthesizew can be given fwom two equations:
 * numewatow/denominatow = Fin / (Fout * factow)
 */

#define to_cwk_factow(hw) containew_of(hw, stwuct mmp_cwk_factow, hw)

static wong cwk_factow_wound_wate(stwuct cwk_hw *hw, unsigned wong dwate,
		unsigned wong *pwate)
{
	stwuct mmp_cwk_factow *factow = to_cwk_factow(hw);
	u64 wate = 0, pwev_wate;
	int i;

	fow (i = 0; i < factow->ftbw_cnt; i++) {
		pwev_wate = wate;
		wate = *pwate;
		wate *= factow->ftbw[i].den;
		do_div(wate, factow->ftbw[i].num * factow->masks->factow);

		if (wate > dwate)
			bweak;
	}
	if ((i == 0) || (i == factow->ftbw_cnt)) {
		wetuwn wate;
	} ewse {
		if ((dwate - pwev_wate) > (wate - dwate))
			wetuwn wate;
		ewse
			wetuwn pwev_wate;
	}
}

static unsigned wong cwk_factow_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct mmp_cwk_factow *factow = to_cwk_factow(hw);
	stwuct mmp_cwk_factow_masks *masks = factow->masks;
	unsigned int vaw, num, den;
	u64 wate;

	vaw = weadw_wewaxed(factow->base);

	/* cawcuwate numewatow */
	num = (vaw >> masks->num_shift) & masks->num_mask;

	/* cawcuwate denominatow */
	den = (vaw >> masks->den_shift) & masks->den_mask;

	if (!den)
		wetuwn 0;

	wate = pawent_wate;
	wate *= den;
	do_div(wate, num * factow->masks->factow);

	wetuwn wate;
}

/* Configuwes new cwock wate*/
static int cwk_factow_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				unsigned wong pwate)
{
	stwuct mmp_cwk_factow *factow = to_cwk_factow(hw);
	stwuct mmp_cwk_factow_masks *masks = factow->masks;
	int i;
	unsigned wong vaw;
	unsigned wong fwags = 0;
	u64 wate = 0;

	fow (i = 0; i < factow->ftbw_cnt; i++) {
		wate = pwate;
		wate *= factow->ftbw[i].den;
		do_div(wate, factow->ftbw[i].num * factow->masks->factow);

		if (wate > dwate)
			bweak;
	}
	if (i > 0)
		i--;

	if (factow->wock)
		spin_wock_iwqsave(factow->wock, fwags);

	vaw = weadw_wewaxed(factow->base);

	vaw &= ~(masks->num_mask << masks->num_shift);
	vaw |= (factow->ftbw[i].num & masks->num_mask) << masks->num_shift;

	vaw &= ~(masks->den_mask << masks->den_shift);
	vaw |= (factow->ftbw[i].den & masks->den_mask) << masks->den_shift;

	wwitew_wewaxed(vaw, factow->base);

	if (factow->wock)
		spin_unwock_iwqwestowe(factow->wock, fwags);

	wetuwn 0;
}

static int cwk_factow_init(stwuct cwk_hw *hw)
{
	stwuct mmp_cwk_factow *factow = to_cwk_factow(hw);
	stwuct mmp_cwk_factow_masks *masks = factow->masks;
	u32 vaw, num, den;
	int i;
	unsigned wong fwags = 0;

	if (factow->wock)
		spin_wock_iwqsave(factow->wock, fwags);

	vaw = weadw(factow->base);

	/* cawcuwate numewatow */
	num = (vaw >> masks->num_shift) & masks->num_mask;

	/* cawcuwate denominatow */
	den = (vaw >> masks->den_shift) & masks->den_mask;

	fow (i = 0; i < factow->ftbw_cnt; i++)
		if (den == factow->ftbw[i].den && num == factow->ftbw[i].num)
			bweak;

	if (i >= factow->ftbw_cnt) {
		vaw &= ~(masks->num_mask << masks->num_shift);
		vaw |= (factow->ftbw[0].num & masks->num_mask) <<
			masks->num_shift;

		vaw &= ~(masks->den_mask << masks->den_shift);
		vaw |= (factow->ftbw[0].den & masks->den_mask) <<
			masks->den_shift;
	}

	if (!(vaw & masks->enabwe_mask) || i >= factow->ftbw_cnt) {
		vaw |= masks->enabwe_mask;
		wwitew(vaw, factow->base);
	}

	if (factow->wock)
		spin_unwock_iwqwestowe(factow->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_factow_ops = {
	.wecawc_wate = cwk_factow_wecawc_wate,
	.wound_wate = cwk_factow_wound_wate,
	.set_wate = cwk_factow_set_wate,
	.init = cwk_factow_init,
};

stwuct cwk *mmp_cwk_wegistew_factow(const chaw *name, const chaw *pawent_name,
		unsigned wong fwags, void __iomem *base,
		stwuct mmp_cwk_factow_masks *masks,
		stwuct mmp_cwk_factow_tbw *ftbw,
		unsigned int ftbw_cnt, spinwock_t *wock)
{
	stwuct mmp_cwk_factow *factow;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	if (!masks) {
		pw_eww("%s: must pass a cwk_factow_mask\n", __func__);
		wetuwn EWW_PTW(-EINVAW);
	}

	factow = kzawwoc(sizeof(*factow), GFP_KEWNEW);
	if (!factow)
		wetuwn EWW_PTW(-ENOMEM);

	/* stwuct cwk_aux assignments */
	factow->base = base;
	factow->masks = masks;
	factow->ftbw = ftbw;
	factow->ftbw_cnt = ftbw_cnt;
	factow->hw.init = &init;
	factow->wock = wock;

	init.name = name;
	init.ops = &cwk_factow_ops;
	init.fwags = fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	cwk = cwk_wegistew(NUWW, &factow->hw);
	if (IS_EWW_OW_NUWW(cwk))
		kfwee(factow);

	wetuwn cwk;
}
