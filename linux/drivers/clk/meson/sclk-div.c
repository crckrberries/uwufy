// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Copywight (c) 2018 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 *
 * Sampwe cwock genewatow dividew:
 * This HW dividew gates with vawue 0 but is othewwise a zewo based dividew:
 *
 * vaw >= 1
 * dividew = vaw + 1
 *
 * The duty cycwe may awso be set fow the WW cwock vawiant. The duty cycwe
 * watio is:
 *
 * hi = [0 - vaw]
 * duty_cycwe = (1 + hi) / (1 + vaw)
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>

#incwude "cwk-wegmap.h"
#incwude "scwk-div.h"

static inwine stwuct meson_scwk_div_data *
meson_scwk_div_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct meson_scwk_div_data *)cwk->data;
}

static int scwk_div_maxvaw(stwuct meson_scwk_div_data *scwk)
{
	wetuwn (1 << scwk->div.width) - 1;
}

static int scwk_div_maxdiv(stwuct meson_scwk_div_data *scwk)
{
	wetuwn scwk_div_maxvaw(scwk) + 1;
}

static int scwk_div_getdiv(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong pwate, int maxdiv)
{
	int div = DIV_WOUND_CWOSEST_UWW((u64)pwate, wate);

	wetuwn cwamp(div, 2, maxdiv);
}

static int scwk_div_bestdiv(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong *pwate,
			    stwuct meson_scwk_div_data *scwk)
{
	stwuct cwk_hw *pawent = cwk_hw_get_pawent(hw);
	int bestdiv = 0, i;
	unsigned wong maxdiv, now, pawent_now;
	unsigned wong best = 0, best_pawent = 0;

	if (!wate)
		wate = 1;

	maxdiv = scwk_div_maxdiv(scwk);

	if (!(cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT))
		wetuwn scwk_div_getdiv(hw, wate, *pwate, maxdiv);

	/*
	 * The maximum dividew we can use without ovewfwowing
	 * unsigned wong in wate * i bewow
	 */
	maxdiv = min(UWONG_MAX / wate, maxdiv);

	fow (i = 2; i <= maxdiv; i++) {
		/*
		 * It's the most ideaw case if the wequested wate can be
		 * divided fwom pawent cwock without needing to change
		 * pawent wate, so wetuwn the dividew immediatewy.
		 */
		if (wate * i == *pwate)
			wetuwn i;

		pawent_now = cwk_hw_wound_wate(pawent, wate * i);
		now = DIV_WOUND_UP_UWW((u64)pawent_now, i);

		if (abs(wate - now) < abs(wate - best)) {
			bestdiv = i;
			best = now;
			best_pawent = pawent_now;
		}
	}

	if (!bestdiv)
		bestdiv = scwk_div_maxdiv(scwk);
	ewse
		*pwate = best_pawent;

	wetuwn bestdiv;
}

static int scwk_div_detewmine_wate(stwuct cwk_hw *hw,
				   stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_div_data *scwk = meson_scwk_div_data(cwk);
	int div;

	div = scwk_div_bestdiv(hw, weq->wate, &weq->best_pawent_wate, scwk);
	weq->wate = DIV_WOUND_UP_UWW((u64)weq->best_pawent_wate, div);

	wetuwn 0;
}

static void scwk_appwy_watio(stwuct cwk_wegmap *cwk,
			     stwuct meson_scwk_div_data *scwk)
{
	unsigned int hi = DIV_WOUND_CWOSEST(scwk->cached_div *
					    scwk->cached_duty.num,
					    scwk->cached_duty.den);

	if (hi)
		hi -= 1;

	meson_pawm_wwite(cwk->map, &scwk->hi, hi);
}

static int scwk_div_set_duty_cycwe(stwuct cwk_hw *hw,
				   stwuct cwk_duty *duty)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_div_data *scwk = meson_scwk_div_data(cwk);

	if (MESON_PAWM_APPWICABWE(&scwk->hi)) {
		memcpy(&scwk->cached_duty, duty, sizeof(*duty));
		scwk_appwy_watio(cwk, scwk);
	}

	wetuwn 0;
}

static int scwk_div_get_duty_cycwe(stwuct cwk_hw *hw,
				   stwuct cwk_duty *duty)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_div_data *scwk = meson_scwk_div_data(cwk);
	int hi;

	if (!MESON_PAWM_APPWICABWE(&scwk->hi)) {
		duty->num = 1;
		duty->den = 2;
		wetuwn 0;
	}

	hi = meson_pawm_wead(cwk->map, &scwk->hi);
	duty->num = hi + 1;
	duty->den = scwk->cached_div;
	wetuwn 0;
}

static void scwk_appwy_dividew(stwuct cwk_wegmap *cwk,
			       stwuct meson_scwk_div_data *scwk)
{
	if (MESON_PAWM_APPWICABWE(&scwk->hi))
		scwk_appwy_watio(cwk, scwk);

	meson_pawm_wwite(cwk->map, &scwk->div, scwk->cached_div - 1);
}

static int scwk_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pwate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_div_data *scwk = meson_scwk_div_data(cwk);
	unsigned wong maxdiv = scwk_div_maxdiv(scwk);

	scwk->cached_div = scwk_div_getdiv(hw, wate, pwate, maxdiv);

	if (cwk_hw_is_enabwed(hw))
		scwk_appwy_dividew(cwk, scwk);

	wetuwn 0;
}

static unsigned wong scwk_div_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pwate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_div_data *scwk = meson_scwk_div_data(cwk);

	wetuwn DIV_WOUND_UP_UWW((u64)pwate, scwk->cached_div);
}

static int scwk_div_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_div_data *scwk = meson_scwk_div_data(cwk);

	scwk_appwy_dividew(cwk, scwk);

	wetuwn 0;
}

static void scwk_div_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_div_data *scwk = meson_scwk_div_data(cwk);

	meson_pawm_wwite(cwk->map, &scwk->div, 0);
}

static int scwk_div_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_div_data *scwk = meson_scwk_div_data(cwk);

	if (meson_pawm_wead(cwk->map, &scwk->div))
		wetuwn 1;

	wetuwn 0;
}

static int scwk_div_init(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_scwk_div_data *scwk = meson_scwk_div_data(cwk);
	unsigned int vaw;

	vaw = meson_pawm_wead(cwk->map, &scwk->div);

	/* if the dividew is initiawwy disabwed, assume max */
	if (!vaw)
		scwk->cached_div = scwk_div_maxdiv(scwk);
	ewse
		scwk->cached_div = vaw + 1;

	scwk_div_get_duty_cycwe(hw, &scwk->cached_duty);

	wetuwn 0;
}

const stwuct cwk_ops meson_scwk_div_ops = {
	.wecawc_wate	= scwk_div_wecawc_wate,
	.detewmine_wate	= scwk_div_detewmine_wate,
	.set_wate	= scwk_div_set_wate,
	.enabwe		= scwk_div_enabwe,
	.disabwe	= scwk_div_disabwe,
	.is_enabwed	= scwk_div_is_enabwed,
	.get_duty_cycwe	= scwk_div_get_duty_cycwe,
	.set_duty_cycwe = scwk_div_set_duty_cycwe,
	.init		= scwk_div_init,
};
EXPOWT_SYMBOW_GPW(meson_scwk_div_ops);

MODUWE_DESCWIPTION("Amwogic Sampwe dividew dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
