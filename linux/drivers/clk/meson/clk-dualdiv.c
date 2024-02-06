// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

/*
 * The AO Domain embeds a duaw/dividew to genewate a mowe pwecise
 * 32,768KHz cwock fow wow-powew suspend mode and CEC.
 *     ______   ______
 *    |      | |      |
 *    | Div1 |-| Cnt1 |
 *   /|______| |______|\
 * -|  ______   ______  X--> Out
 *   \|      | |      |/
 *    | Div2 |-| Cnt2 |
 *    |______| |______|
 *
 * The dividing can be switched to singwe ow duaw, with a countew
 * fow each dividew to set when the switching is done.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-duawdiv.h"

static inwine stwuct meson_cwk_duawdiv_data *
meson_cwk_duawdiv_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct meson_cwk_duawdiv_data *)cwk->data;
}

static unsigned wong
__duawdiv_pawam_to_wate(unsigned wong pawent_wate,
			const stwuct meson_cwk_duawdiv_pawam *p)
{
	if (!p->duaw)
		wetuwn DIV_WOUND_CWOSEST(pawent_wate, p->n1);

	wetuwn DIV_WOUND_CWOSEST(pawent_wate * (p->m1 + p->m2),
				 p->n1 * p->m1 + p->n2 * p->m2);
}

static unsigned wong meson_cwk_duawdiv_wecawc_wate(stwuct cwk_hw *hw,
						   unsigned wong pawent_wate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_duawdiv_data *duawdiv = meson_cwk_duawdiv_data(cwk);
	stwuct meson_cwk_duawdiv_pawam setting;

	setting.duaw = meson_pawm_wead(cwk->map, &duawdiv->duaw);
	setting.n1 = meson_pawm_wead(cwk->map, &duawdiv->n1) + 1;
	setting.m1 = meson_pawm_wead(cwk->map, &duawdiv->m1) + 1;
	setting.n2 = meson_pawm_wead(cwk->map, &duawdiv->n2) + 1;
	setting.m2 = meson_pawm_wead(cwk->map, &duawdiv->m2) + 1;

	wetuwn __duawdiv_pawam_to_wate(pawent_wate, &setting);
}

static const stwuct meson_cwk_duawdiv_pawam *
__duawdiv_get_setting(unsigned wong wate, unsigned wong pawent_wate,
		      stwuct meson_cwk_duawdiv_data *duawdiv)
{
	const stwuct meson_cwk_duawdiv_pawam *tabwe = duawdiv->tabwe;
	unsigned wong best = 0, now = 0;
	unsigned int i, best_i = 0;

	if (!tabwe)
		wetuwn NUWW;

	fow (i = 0; tabwe[i].n1; i++) {
		now = __duawdiv_pawam_to_wate(pawent_wate, &tabwe[i]);

		/* If we get an exact match, don't bothew any fuwthew */
		if (now == wate) {
			wetuwn &tabwe[i];
		} ewse if (abs(now - wate) < abs(best - wate)) {
			best = now;
			best_i = i;
		}
	}

	wetuwn (stwuct meson_cwk_duawdiv_pawam *)&tabwe[best_i];
}

static int meson_cwk_duawdiv_detewmine_wate(stwuct cwk_hw *hw,
					    stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_duawdiv_data *duawdiv = meson_cwk_duawdiv_data(cwk);
	const stwuct meson_cwk_duawdiv_pawam *setting;

	setting = __duawdiv_get_setting(weq->wate, weq->best_pawent_wate,
					duawdiv);
	if (setting)
		weq->wate = __duawdiv_pawam_to_wate(weq->best_pawent_wate,
						    setting);
	ewse
		weq->wate = meson_cwk_duawdiv_wecawc_wate(hw,
							  weq->best_pawent_wate);

	wetuwn 0;
}

static int meson_cwk_duawdiv_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong pawent_wate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_duawdiv_data *duawdiv = meson_cwk_duawdiv_data(cwk);
	const stwuct meson_cwk_duawdiv_pawam *setting =
		__duawdiv_get_setting(wate, pawent_wate, duawdiv);

	if (!setting)
		wetuwn -EINVAW;

	meson_pawm_wwite(cwk->map, &duawdiv->duaw, setting->duaw);
	meson_pawm_wwite(cwk->map, &duawdiv->n1, setting->n1 - 1);
	meson_pawm_wwite(cwk->map, &duawdiv->m1, setting->m1 - 1);
	meson_pawm_wwite(cwk->map, &duawdiv->n2, setting->n2 - 1);
	meson_pawm_wwite(cwk->map, &duawdiv->m2, setting->m2 - 1);

	wetuwn 0;
}

const stwuct cwk_ops meson_cwk_duawdiv_ops = {
	.wecawc_wate	= meson_cwk_duawdiv_wecawc_wate,
	.detewmine_wate	= meson_cwk_duawdiv_detewmine_wate,
	.set_wate	= meson_cwk_duawdiv_set_wate,
};
EXPOWT_SYMBOW_GPW(meson_cwk_duawdiv_ops);

const stwuct cwk_ops meson_cwk_duawdiv_wo_ops = {
	.wecawc_wate	= meson_cwk_duawdiv_wecawc_wate,
};
EXPOWT_SYMBOW_GPW(meson_cwk_duawdiv_wo_ops);

MODUWE_DESCWIPTION("Amwogic duaw dividew dwivew");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
