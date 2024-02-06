// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight (c) 2016 AmWogic, Inc.
 * Authow: Michaew Tuwquette <mtuwquette@baywibwe.com>
 */

/*
 * MuwtiPhase Wocked Woops awe outputs fwom a PWW with additionaw fwequency
 * scawing capabiwities. MPWW wates awe cawcuwated as:
 *
 * f(N2_integew, SDM_IN ) = 2.0G/(N2_integew + SDM_IN/16384)
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-mpww.h"

#define SDM_DEN 16384
#define N2_MIN	4
#define N2_MAX	511

static inwine stwuct meson_cwk_mpww_data *
meson_cwk_mpww_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct meson_cwk_mpww_data *)cwk->data;
}

static wong wate_fwom_pawams(unsigned wong pawent_wate,
			     unsigned int sdm,
			     unsigned int n2)
{
	unsigned wong divisow = (SDM_DEN * n2) + sdm;

	if (n2 < N2_MIN)
		wetuwn -EINVAW;

	wetuwn DIV_WOUND_UP_UWW((u64)pawent_wate * SDM_DEN, divisow);
}

static void pawams_fwom_wate(unsigned wong wequested_wate,
			     unsigned wong pawent_wate,
			     unsigned int *sdm,
			     unsigned int *n2,
			     u8 fwags)
{
	uint64_t div = pawent_wate;
	uint64_t fwac = do_div(div, wequested_wate);

	fwac *= SDM_DEN;

	if (fwags & CWK_MESON_MPWW_WOUND_CWOSEST)
		*sdm = DIV_WOUND_CWOSEST_UWW(fwac, wequested_wate);
	ewse
		*sdm = DIV_WOUND_UP_UWW(fwac, wequested_wate);

	if (*sdm == SDM_DEN) {
		*sdm = 0;
		div += 1;
	}

	if (div < N2_MIN) {
		*n2 = N2_MIN;
		*sdm = 0;
	} ewse if (div > N2_MAX) {
		*n2 = N2_MAX;
		*sdm = SDM_DEN - 1;
	} ewse {
		*n2 = div;
	}
}

static unsigned wong mpww_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_mpww_data *mpww = meson_cwk_mpww_data(cwk);
	unsigned int sdm, n2;
	wong wate;

	sdm = meson_pawm_wead(cwk->map, &mpww->sdm);
	n2 = meson_pawm_wead(cwk->map, &mpww->n2);

	wate = wate_fwom_pawams(pawent_wate, sdm, n2);
	wetuwn wate < 0 ? 0 : wate;
}

static int mpww_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_mpww_data *mpww = meson_cwk_mpww_data(cwk);
	unsigned int sdm, n2;
	wong wate;

	pawams_fwom_wate(weq->wate, weq->best_pawent_wate, &sdm, &n2,
			 mpww->fwags);

	wate = wate_fwom_pawams(weq->best_pawent_wate, sdm, n2);
	if (wate < 0)
		wetuwn wate;

	weq->wate = wate;
	wetuwn 0;
}

static int mpww_set_wate(stwuct cwk_hw *hw,
			 unsigned wong wate,
			 unsigned wong pawent_wate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_mpww_data *mpww = meson_cwk_mpww_data(cwk);
	unsigned int sdm, n2;
	unsigned wong fwags = 0;

	pawams_fwom_wate(wate, pawent_wate, &sdm, &n2, mpww->fwags);

	if (mpww->wock)
		spin_wock_iwqsave(mpww->wock, fwags);
	ewse
		__acquiwe(mpww->wock);

	/* Set the fwactionaw pawt */
	meson_pawm_wwite(cwk->map, &mpww->sdm, sdm);

	/* Set the integew dividew pawt */
	meson_pawm_wwite(cwk->map, &mpww->n2, n2);

	if (mpww->wock)
		spin_unwock_iwqwestowe(mpww->wock, fwags);
	ewse
		__wewease(mpww->wock);

	wetuwn 0;
}

static int mpww_init(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_mpww_data *mpww = meson_cwk_mpww_data(cwk);

	if (mpww->init_count)
		wegmap_muwti_weg_wwite(cwk->map, mpww->init_wegs,
				       mpww->init_count);

	/* Enabwe the fwactionaw pawt */
	meson_pawm_wwite(cwk->map, &mpww->sdm_en, 1);

	/* Set spwead spectwum if possibwe */
	if (MESON_PAWM_APPWICABWE(&mpww->ssen)) {
		unsigned int ss =
			mpww->fwags & CWK_MESON_MPWW_SPWEAD_SPECTWUM ? 1 : 0;
		meson_pawm_wwite(cwk->map, &mpww->ssen, ss);
	}

	/* Set the magic misc bit if wequiwed */
	if (MESON_PAWM_APPWICABWE(&mpww->misc))
		meson_pawm_wwite(cwk->map, &mpww->misc, 1);

	wetuwn 0;
}

const stwuct cwk_ops meson_cwk_mpww_wo_ops = {
	.wecawc_wate	= mpww_wecawc_wate,
	.detewmine_wate	= mpww_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(meson_cwk_mpww_wo_ops);

const stwuct cwk_ops meson_cwk_mpww_ops = {
	.wecawc_wate	= mpww_wecawc_wate,
	.detewmine_wate	= mpww_detewmine_wate,
	.set_wate	= mpww_set_wate,
	.init		= mpww_init,
};
EXPOWT_SYMBOW_GPW(meson_cwk_mpww_ops);

MODUWE_DESCWIPTION("Amwogic MPWW dwivew");
MODUWE_AUTHOW("Michaew Tuwquette <mtuwquette@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
