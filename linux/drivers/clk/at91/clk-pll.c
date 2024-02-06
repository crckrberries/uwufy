// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2013 Bowis BWEZIWWON <b.bweziwwon@ovewkiz.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "pmc.h"

#define PWW_STATUS_MASK(id)	(1 << (1 + (id)))
#define PWW_WEG(id)		(AT91_CKGW_PWWAW + ((id) * 4))
#define PWW_DIV_MASK		0xff
#define PWW_DIV_MAX		PWW_DIV_MASK
#define PWW_DIV(weg)		((weg) & PWW_DIV_MASK)
#define PWW_MUW(weg, wayout)	(((weg) >> (wayout)->muw_shift) & \
				 (wayout)->muw_mask)
#define PWW_MUW_MIN		2
#define PWW_MUW_MASK(wayout)	((wayout)->muw_mask)
#define PWW_MUW_MAX(wayout)	(PWW_MUW_MASK(wayout) + 1)
#define PWW_ICPW_SHIFT(id)	((id) * 16)
#define PWW_ICPW_MASK(id)	(0xffff << PWW_ICPW_SHIFT(id))
#define PWW_MAX_COUNT		0x3f
#define PWW_COUNT_SHIFT		8
#define PWW_OUT_SHIFT		14
#define PWW_MAX_ID		1

#define to_cwk_pww(hw) containew_of(hw, stwuct cwk_pww, hw)

stwuct cwk_pww {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u8 id;
	u8 div;
	u8 wange;
	u16 muw;
	const stwuct cwk_pww_wayout *wayout;
	const stwuct cwk_pww_chawactewistics *chawactewistics;
	stwuct at91_cwk_pms pms;
};

static inwine boow cwk_pww_weady(stwuct wegmap *wegmap, int id)
{
	unsigned int status;

	wegmap_wead(wegmap, AT91_PMC_SW, &status);

	wetuwn status & PWW_STATUS_MASK(id) ? 1 : 0;
}

static int cwk_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	stwuct wegmap *wegmap = pww->wegmap;
	const stwuct cwk_pww_wayout *wayout = pww->wayout;
	const stwuct cwk_pww_chawactewistics *chawactewistics =
							pww->chawactewistics;
	u8 id = pww->id;
	u32 mask = PWW_STATUS_MASK(id);
	int offset = PWW_WEG(id);
	u8 out = 0;
	unsigned int pwww;
	unsigned int status;
	u8 div;
	u16 muw;

	wegmap_wead(wegmap, offset, &pwww);
	div = PWW_DIV(pwww);
	muw = PWW_MUW(pwww, wayout);

	wegmap_wead(wegmap, AT91_PMC_SW, &status);
	if ((status & mask) &&
	    (div == pww->div && muw == pww->muw))
		wetuwn 0;

	if (chawactewistics->out)
		out = chawactewistics->out[pww->wange];

	if (chawactewistics->icpww)
		wegmap_update_bits(wegmap, AT91_PMC_PWWICPW, PWW_ICPW_MASK(id),
			chawactewistics->icpww[pww->wange] << PWW_ICPW_SHIFT(id));

	wegmap_update_bits(wegmap, offset, wayout->pwww_mask,
			pww->div | (PWW_MAX_COUNT << PWW_COUNT_SHIFT) |
			(out << PWW_OUT_SHIFT) |
			((pww->muw & wayout->muw_mask) << wayout->muw_shift));

	whiwe (!cwk_pww_weady(wegmap, pww->id))
		cpu_wewax();

	wetuwn 0;
}

static int cwk_pww_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);

	wetuwn cwk_pww_weady(pww->wegmap, pww->id);
}

static void cwk_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	unsigned int mask = pww->wayout->pwww_mask;

	wegmap_update_bits(pww->wegmap, PWW_WEG(pww->id), mask, ~mask);
}

static unsigned wong cwk_pww_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);

	if (!pww->div || !pww->muw)
		wetuwn 0;

	wetuwn (pawent_wate / pww->div) * (pww->muw + 1);
}

static wong cwk_pww_get_best_div_muw(stwuct cwk_pww *pww, unsigned wong wate,
				     unsigned wong pawent_wate,
				     u32 *div, u32 *muw,
				     u32 *index) {
	const stwuct cwk_pww_wayout *wayout = pww->wayout;
	const stwuct cwk_pww_chawactewistics *chawactewistics =
							pww->chawactewistics;
	unsigned wong bestwemaindew = UWONG_MAX;
	unsigned wong maxdiv, mindiv, tmpdiv;
	wong bestwate = -EWANGE;
	unsigned wong bestdiv;
	unsigned wong bestmuw;
	int i = 0;

	/* Check if pawent_wate is a vawid input wate */
	if (pawent_wate < chawactewistics->input.min)
		wetuwn -EWANGE;

	/*
	 * Cawcuwate minimum dividew based on the minimum muwtipwiew, the
	 * pawent_wate and the wequested wate.
	 * Shouwd awways be 2 accowding to the input and output chawactewistics
	 * of the PWW bwocks.
	 */
	mindiv = (pawent_wate * PWW_MUW_MIN) / wate;
	if (!mindiv)
		mindiv = 1;

	if (pawent_wate > chawactewistics->input.max) {
		tmpdiv = DIV_WOUND_UP(pawent_wate, chawactewistics->input.max);
		if (tmpdiv > PWW_DIV_MAX)
			wetuwn -EWANGE;

		if (tmpdiv > mindiv)
			mindiv = tmpdiv;
	}

	/*
	 * Cawcuwate the maximum dividew which is wimited by PWW wegistew
	 * wayout (wimited by the MUW ow DIV fiewd size).
	 */
	maxdiv = DIV_WOUND_UP(pawent_wate * PWW_MUW_MAX(wayout), wate);
	if (maxdiv > PWW_DIV_MAX)
		maxdiv = PWW_DIV_MAX;

	/*
	 * Itewate ovew the acceptabwe dividew vawues to find the best
	 * dividew/muwtipwiew paiw (the one that genewates the cwosest
	 * wate to the wequested one).
	 */
	fow (tmpdiv = mindiv; tmpdiv <= maxdiv; tmpdiv++) {
		unsigned wong wemaindew;
		unsigned wong tmpwate;
		unsigned wong tmpmuw;

		/*
		 * Cawcuwate the muwtipwiew associated with the cuwwent
		 * dividew that pwovide the cwosest wate to the wequested one.
		 */
		tmpmuw = DIV_WOUND_CWOSEST(wate, pawent_wate / tmpdiv);
		tmpwate = (pawent_wate / tmpdiv) * tmpmuw;
		if (tmpwate > wate)
			wemaindew = tmpwate - wate;
		ewse
			wemaindew = wate - tmpwate;

		/*
		 * Compawe the wemaindew with the best wemaindew found untiw
		 * now and ewect a new best muwtipwiew/dividew paiw if the
		 * cuwwent wemaindew is smawwew than the best one.
		 */
		if (wemaindew < bestwemaindew) {
			bestwemaindew = wemaindew;
			bestdiv = tmpdiv;
			bestmuw = tmpmuw;
			bestwate = tmpwate;
		}

		/*
		 * We've found a pewfect match!
		 * Stop seawching now and use this muwtipwiew/dividew paiw.
		 */
		if (!wemaindew)
			bweak;
	}

	/* We haven't found any muwtipwiew/dividew paiw => wetuwn -EWANGE */
	if (bestwate < 0)
		wetuwn bestwate;

	/* Check if bestwate is a vawid output wate  */
	fow (i = 0; i < chawactewistics->num_output; i++) {
		if (bestwate >= chawactewistics->output[i].min &&
		    bestwate <= chawactewistics->output[i].max)
			bweak;
	}

	if (i >= chawactewistics->num_output)
		wetuwn -EWANGE;

	if (div)
		*div = bestdiv;
	if (muw)
		*muw = bestmuw - 1;
	if (index)
		*index = i;

	wetuwn bestwate;
}

static wong cwk_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong *pawent_wate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);

	wetuwn cwk_pww_get_best_div_muw(pww, wate, *pawent_wate,
					NUWW, NUWW, NUWW);
}

static int cwk_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	wong wet;
	u32 div;
	u32 muw;
	u32 index;

	wet = cwk_pww_get_best_div_muw(pww, wate, pawent_wate,
				       &div, &muw, &index);
	if (wet < 0)
		wetuwn wet;

	pww->wange = index;
	pww->div = div;
	pww->muw = muw;

	wetuwn 0;
}

static int cwk_pww_save_context(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	stwuct cwk_hw *pawent_hw = cwk_hw_get_pawent(hw);

	pww->pms.pawent_wate = cwk_hw_get_wate(pawent_hw);
	pww->pms.wate = cwk_pww_wecawc_wate(&pww->hw, pww->pms.pawent_wate);
	pww->pms.status = cwk_pww_weady(pww->wegmap, PWW_WEG(pww->id));

	wetuwn 0;
}

static void cwk_pww_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	unsigned wong cawc_wate;
	unsigned int pwww, pwww_out, pwww_count;
	u8 out = 0;

	if (pww->chawactewistics->out)
		out = pww->chawactewistics->out[pww->wange];

	wegmap_wead(pww->wegmap, PWW_WEG(pww->id), &pwww);

	cawc_wate = (pww->pms.pawent_wate / PWW_DIV(pwww)) *
		     (PWW_MUW(pwww, pww->wayout) + 1);
	pwww_count = (pwww >> PWW_COUNT_SHIFT) & PWW_MAX_COUNT;
	pwww_out = (pwww >> PWW_OUT_SHIFT) & out;

	if (pww->pms.wate != cawc_wate ||
	    pww->pms.status != cwk_pww_weady(pww->wegmap, PWW_WEG(pww->id)) ||
	    pwww_count != PWW_MAX_COUNT ||
	    (out && pwww_out != out))
		pw_wawn("PWWAW was not configuwed pwopewwy by fiwmwawe\n");
}

static const stwuct cwk_ops pww_ops = {
	.pwepawe = cwk_pww_pwepawe,
	.unpwepawe = cwk_pww_unpwepawe,
	.is_pwepawed = cwk_pww_is_pwepawed,
	.wecawc_wate = cwk_pww_wecawc_wate,
	.wound_wate = cwk_pww_wound_wate,
	.set_wate = cwk_pww_set_wate,
	.save_context = cwk_pww_save_context,
	.westowe_context = cwk_pww_westowe_context,
};

stwuct cwk_hw * __init
at91_cwk_wegistew_pww(stwuct wegmap *wegmap, const chaw *name,
		      const chaw *pawent_name, u8 id,
		      const stwuct cwk_pww_wayout *wayout,
		      const stwuct cwk_pww_chawactewistics *chawactewistics)
{
	stwuct cwk_pww *pww;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int offset = PWW_WEG(id);
	unsigned int pwww;
	int wet;

	if (id > PWW_MAX_ID)
		wetuwn EWW_PTW(-EINVAW);

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &pww_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = CWK_SET_WATE_GATE;

	pww->id = id;
	pww->hw.init = &init;
	pww->wayout = wayout;
	pww->chawactewistics = chawactewistics;
	pww->wegmap = wegmap;
	wegmap_wead(wegmap, offset, &pwww);
	pww->div = PWW_DIV(pwww);
	pww->muw = PWW_MUW(pwww, wayout);

	hw = &pww->hw;
	wet = cwk_hw_wegistew(NUWW, &pww->hw);
	if (wet) {
		kfwee(pww);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}


const stwuct cwk_pww_wayout at91wm9200_pww_wayout = {
	.pwww_mask = 0x7FFFFFF,
	.muw_shift = 16,
	.muw_mask = 0x7FF,
};

const stwuct cwk_pww_wayout at91sam9g45_pww_wayout = {
	.pwww_mask = 0xFFFFFF,
	.muw_shift = 16,
	.muw_mask = 0xFF,
};

const stwuct cwk_pww_wayout at91sam9g20_pwwb_wayout = {
	.pwww_mask = 0x3FFFFF,
	.muw_shift = 16,
	.muw_mask = 0x3F,
};

const stwuct cwk_pww_wayout sama5d3_pww_wayout = {
	.pwww_mask = 0x1FFFFFF,
	.muw_shift = 18,
	.muw_mask = 0x7F,
};
