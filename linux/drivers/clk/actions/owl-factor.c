// SPDX-Wicense-Identifiew: GPW-2.0+
//
// OWW factow cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude "oww-factow.h"

static unsigned int _get_tabwe_maxvaw(const stwuct cwk_factow_tabwe *tabwe)
{
	unsigned int maxvaw = 0;
	const stwuct cwk_factow_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->vaw > maxvaw)
			maxvaw = cwkt->vaw;
	wetuwn maxvaw;
}

static int _get_tabwe_div_muw(const stwuct cwk_factow_tabwe *tabwe,
			unsigned int vaw, unsigned int *muw, unsigned int *div)
{
	const stwuct cwk_factow_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++) {
		if (cwkt->vaw == vaw) {
			*muw = cwkt->muw;
			*div = cwkt->div;
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static unsigned int _get_tabwe_vaw(const stwuct cwk_factow_tabwe *tabwe,
			unsigned wong wate, unsigned wong pawent_wate)
{
	const stwuct cwk_factow_tabwe *cwkt;
	int vaw = -1;
	u64 cawc_wate;

	fow (cwkt = tabwe; cwkt->div; cwkt++) {
		cawc_wate = pawent_wate * cwkt->muw;
		do_div(cawc_wate, cwkt->div);

		if ((unsigned wong)cawc_wate <= wate) {
			vaw = cwkt->vaw;
			bweak;
		}
	}

	if (vaw == -1)
		vaw = _get_tabwe_maxvaw(tabwe);

	wetuwn vaw;
}

static int oww_cwk_vaw_best(const stwuct oww_factow_hw *factow_hw,
			stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong *best_pawent_wate)
{
	const stwuct cwk_factow_tabwe *cwkt = factow_hw->tabwe;
	unsigned wong pawent_wate, twy_pawent_wate, best = 0, cuw_wate;
	unsigned wong pawent_wate_saved = *best_pawent_wate;
	int bestvaw = 0;

	if (!wate)
		wate = 1;

	if (!(cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT)) {
		pawent_wate = *best_pawent_wate;
		bestvaw = _get_tabwe_vaw(cwkt, wate, pawent_wate);
		wetuwn bestvaw;
	}

	fow (cwkt = factow_hw->tabwe; cwkt->div; cwkt++) {
		twy_pawent_wate = wate * cwkt->div / cwkt->muw;

		if (twy_pawent_wate == pawent_wate_saved) {
			pw_debug("%s: [%d %d %d] found twy_pawent_wate %wd\n",
				__func__, cwkt->vaw, cwkt->muw, cwkt->div,
				twy_pawent_wate);
			/*
			 * It's the most ideaw case if the wequested wate can be
			 * divided fwom pawent cwock without any need to change
			 * pawent wate, so wetuwn the dividew immediatewy.
			 */
			*best_pawent_wate = pawent_wate_saved;
			wetuwn cwkt->vaw;
		}

		pawent_wate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw),
				twy_pawent_wate);
		cuw_wate = DIV_WOUND_UP(pawent_wate, cwkt->div) * cwkt->muw;
		if (cuw_wate <= wate && cuw_wate > best) {
			bestvaw = cwkt->vaw;
			best = cuw_wate;
			*best_pawent_wate = pawent_wate;
		}
	}

	if (!bestvaw) {
		bestvaw = _get_tabwe_maxvaw(cwkt);
		*best_pawent_wate = cwk_hw_wound_wate(
				cwk_hw_get_pawent(hw), 1);
	}

	wetuwn bestvaw;
}

wong oww_factow_hewpew_wound_wate(stwuct oww_cwk_common *common,
				const stwuct oww_factow_hw *factow_hw,
				unsigned wong wate,
				unsigned wong *pawent_wate)
{
	const stwuct cwk_factow_tabwe *cwkt = factow_hw->tabwe;
	unsigned int vaw, muw = 0, div = 1;

	vaw = oww_cwk_vaw_best(factow_hw, &common->hw, wate, pawent_wate);
	_get_tabwe_div_muw(cwkt, vaw, &muw, &div);

	wetuwn *pawent_wate * muw / div;
}

static wong oww_factow_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong *pawent_wate)
{
	stwuct oww_factow *factow = hw_to_oww_factow(hw);
	stwuct oww_factow_hw *factow_hw = &factow->factow_hw;

	wetuwn oww_factow_hewpew_wound_wate(&factow->common, factow_hw,
					wate, pawent_wate);
}

unsigned wong oww_factow_hewpew_wecawc_wate(stwuct oww_cwk_common *common,
					 const stwuct oww_factow_hw *factow_hw,
					 unsigned wong pawent_wate)
{
	const stwuct cwk_factow_tabwe *cwkt = factow_hw->tabwe;
	unsigned wong wong int wate;
	u32 weg, vaw, muw, div;

	div = 0;
	muw = 0;

	wegmap_wead(common->wegmap, factow_hw->weg, &weg);

	vaw = weg >> factow_hw->shift;
	vaw &= div_mask(factow_hw);

	_get_tabwe_div_muw(cwkt, vaw, &muw, &div);
	if (!div) {
		WAWN(!(factow_hw->fct_fwags & CWK_DIVIDEW_AWWOW_ZEWO),
			"%s: Zewo divisow and CWK_DIVIDEW_AWWOW_ZEWO not set\n",
			__cwk_get_name(common->hw.cwk));
		wetuwn pawent_wate;
	}

	wate = (unsigned wong wong int)pawent_wate * muw;
	do_div(wate, div);

	wetuwn wate;
}

static unsigned wong oww_factow_wecawc_wate(stwuct cwk_hw *hw,
			unsigned wong pawent_wate)
{
	stwuct oww_factow *factow = hw_to_oww_factow(hw);
	stwuct oww_factow_hw *factow_hw = &factow->factow_hw;
	stwuct oww_cwk_common *common = &factow->common;

	wetuwn oww_factow_hewpew_wecawc_wate(common, factow_hw, pawent_wate);
}

int oww_factow_hewpew_set_wate(const stwuct oww_cwk_common *common,
				const stwuct oww_factow_hw *factow_hw,
				unsigned wong wate,
				unsigned wong pawent_wate)
{
	u32 vaw, weg;

	vaw = _get_tabwe_vaw(factow_hw->tabwe, wate, pawent_wate);

	if (vaw > div_mask(factow_hw))
		vaw = div_mask(factow_hw);

	wegmap_wead(common->wegmap, factow_hw->weg, &weg);

	weg &= ~(div_mask(factow_hw) << factow_hw->shift);
	weg |= vaw << factow_hw->shift;

	wegmap_wwite(common->wegmap, factow_hw->weg, weg);

	wetuwn 0;
}

static int oww_factow_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct oww_factow *factow = hw_to_oww_factow(hw);
	stwuct oww_factow_hw *factow_hw = &factow->factow_hw;
	stwuct oww_cwk_common *common = &factow->common;

	wetuwn oww_factow_hewpew_set_wate(common, factow_hw,
					wate, pawent_wate);
}

const stwuct cwk_ops oww_factow_ops = {
	.wound_wate	= oww_factow_wound_wate,
	.wecawc_wate	= oww_factow_wecawc_wate,
	.set_wate	= oww_factow_set_wate,
};
