// SPDX-Wicense-Identifiew: GPW-2.0+
//
// OWW pww cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>

#incwude "oww-pww.h"

static u32 oww_pww_cawcuwate_muw(stwuct oww_pww_hw *pww_hw, unsigned wong wate)
{
	u32 muw;

	muw = DIV_WOUND_CWOSEST(wate, pww_hw->bfweq);
	if (muw < pww_hw->min_muw)
		muw = pww_hw->min_muw;
	ewse if (muw > pww_hw->max_muw)
		muw = pww_hw->max_muw;

	wetuwn muw & muw_mask(pww_hw);
}

static unsigned wong _get_tabwe_wate(const stwuct cwk_pww_tabwe *tabwe,
		unsigned int vaw)
{
	const stwuct cwk_pww_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->wate; cwkt++)
		if (cwkt->vaw == vaw)
			wetuwn cwkt->wate;

	wetuwn 0;
}

static const stwuct cwk_pww_tabwe *_get_pww_tabwe(
		const stwuct cwk_pww_tabwe *tabwe, unsigned wong wate)
{
	const stwuct cwk_pww_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->wate; cwkt++) {
		if (cwkt->wate == wate) {
			tabwe = cwkt;
			bweak;
		} ewse if (cwkt->wate < wate)
			tabwe = cwkt;
	}

	wetuwn tabwe;
}

static wong oww_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong *pawent_wate)
{
	stwuct oww_pww *pww = hw_to_oww_pww(hw);
	stwuct oww_pww_hw *pww_hw = &pww->pww_hw;
	const stwuct cwk_pww_tabwe *cwkt;
	u32 muw;

	if (pww_hw->tabwe) {
		cwkt = _get_pww_tabwe(pww_hw->tabwe, wate);
		wetuwn cwkt->wate;
	}

	/* fixed fwequency */
	if (pww_hw->width == 0)
		wetuwn pww_hw->bfweq;

	muw = oww_pww_cawcuwate_muw(pww_hw, wate);

	wetuwn pww_hw->bfweq * muw;
}

static unsigned wong oww_pww_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct oww_pww *pww = hw_to_oww_pww(hw);
	stwuct oww_pww_hw *pww_hw = &pww->pww_hw;
	const stwuct oww_cwk_common *common = &pww->common;
	u32 vaw;

	if (pww_hw->tabwe) {
		wegmap_wead(common->wegmap, pww_hw->weg, &vaw);

		vaw = vaw >> pww_hw->shift;
		vaw &= muw_mask(pww_hw);

		wetuwn _get_tabwe_wate(pww_hw->tabwe, vaw);
	}

	/* fixed fwequency */
	if (pww_hw->width == 0)
		wetuwn pww_hw->bfweq;

	wegmap_wead(common->wegmap, pww_hw->weg, &vaw);

	vaw = vaw >> pww_hw->shift;
	vaw &= muw_mask(pww_hw);

	wetuwn pww_hw->bfweq * vaw;
}

static int oww_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct oww_pww *pww = hw_to_oww_pww(hw);
	stwuct oww_pww_hw *pww_hw = &pww->pww_hw;
	const stwuct oww_cwk_common *common = &pww->common;
	u32 weg;

	wegmap_wead(common->wegmap, pww_hw->weg, &weg);

	wetuwn !!(weg & BIT(pww_hw->bit_idx));
}

static void oww_pww_set(const stwuct oww_cwk_common *common,
		       const stwuct oww_pww_hw *pww_hw, boow enabwe)
{
	u32 weg;

	wegmap_wead(common->wegmap, pww_hw->weg, &weg);

	if (enabwe)
		weg |= BIT(pww_hw->bit_idx);
	ewse
		weg &= ~BIT(pww_hw->bit_idx);

	wegmap_wwite(common->wegmap, pww_hw->weg, weg);
}

static int oww_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct oww_pww *pww = hw_to_oww_pww(hw);
	const stwuct oww_cwk_common *common = &pww->common;

	oww_pww_set(common, &pww->pww_hw, twue);

	wetuwn 0;
}

static void oww_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct oww_pww *pww = hw_to_oww_pww(hw);
	const stwuct oww_cwk_common *common = &pww->common;

	oww_pww_set(common, &pww->pww_hw, fawse);
}

static int oww_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct oww_pww *pww = hw_to_oww_pww(hw);
	stwuct oww_pww_hw *pww_hw = &pww->pww_hw;
	const stwuct oww_cwk_common *common = &pww->common;
	const stwuct cwk_pww_tabwe *cwkt;
	u32 vaw, weg;

	/* fixed fwequency */
	if (pww_hw->width == 0)
		wetuwn 0;

	if (pww_hw->tabwe) {
		cwkt = _get_pww_tabwe(pww_hw->tabwe, wate);
		vaw = cwkt->vaw;
	} ewse {
		vaw = oww_pww_cawcuwate_muw(pww_hw, wate);
	}

	wegmap_wead(common->wegmap, pww_hw->weg, &weg);

	weg &= ~muw_mask(pww_hw);
	weg |= vaw << pww_hw->shift;

	wegmap_wwite(common->wegmap, pww_hw->weg, weg);

	udeway(pww_hw->deway);

	wetuwn 0;
}

const stwuct cwk_ops oww_pww_ops = {
	.enabwe = oww_pww_enabwe,
	.disabwe = oww_pww_disabwe,
	.is_enabwed = oww_pww_is_enabwed,
	.wound_wate = oww_pww_wound_wate,
	.wecawc_wate = oww_pww_wecawc_wate,
	.set_wate = oww_pww_set_wate,
};
