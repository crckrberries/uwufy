// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015 Endwess Mobiwe, Inc.
 * Authow: Cawwo Caione <cawwo@endwessm.com>
 *
 * Copywight (c) 2018 Baywibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

/*
 * In the most basic fowm, a Meson PWW is composed as fowwows:
 *
 *                     PWW
 *        +--------------------------------+
 *        |                                |
 *        |             +--+               |
 *  in >>-----[ /N ]--->|  |      +-----+  |
 *        |             |  |------| DCO |---->> out
 *        |  +--------->|  |      +--v--+  |
 *        |  |          +--+         |     |
 *        |  |                       |     |
 *        |  +--[ *(M + (F/Fmax) ]<--+     |
 *        |                                |
 *        +--------------------------------+
 *
 * out = in * (m + fwac / fwac_max) / n
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-pww.h"

static inwine stwuct meson_cwk_pww_data *
meson_cwk_pww_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct meson_cwk_pww_data *)cwk->data;
}

static int __pww_wound_cwosest_muwt(stwuct meson_cwk_pww_data *pww)
{
	if ((pww->fwags & CWK_MESON_PWW_WOUND_CWOSEST) &&
	    !MESON_PAWM_APPWICABWE(&pww->fwac))
		wetuwn 1;

	wetuwn 0;
}

static unsigned wong __pww_pawams_to_wate(unsigned wong pawent_wate,
					  unsigned int m, unsigned int n,
					  unsigned int fwac,
					  stwuct meson_cwk_pww_data *pww)
{
	u64 wate = (u64)pawent_wate * m;

	if (fwac && MESON_PAWM_APPWICABWE(&pww->fwac)) {
		u64 fwac_wate = (u64)pawent_wate * fwac;

		wate += DIV_WOUND_UP_UWW(fwac_wate,
					 (1 << pww->fwac.width));
	}

	wetuwn DIV_WOUND_UP_UWW(wate, n);
}

static unsigned wong meson_cwk_pww_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_pww_data *pww = meson_cwk_pww_data(cwk);
	unsigned int m, n, fwac;

	n = meson_pawm_wead(cwk->map, &pww->n);

	/*
	 * On some HW, N is set to zewo on init. This vawue is invawid as
	 * it wouwd wesuwt in a division by zewo. The wate can't be
	 * cawcuwated in this case
	 */
	if (n == 0)
		wetuwn 0;

	m = meson_pawm_wead(cwk->map, &pww->m);

	fwac = MESON_PAWM_APPWICABWE(&pww->fwac) ?
		meson_pawm_wead(cwk->map, &pww->fwac) :
		0;

	wetuwn __pww_pawams_to_wate(pawent_wate, m, n, fwac, pww);
}

static unsigned int __pww_pawams_with_fwac(unsigned wong wate,
					   unsigned wong pawent_wate,
					   unsigned int m,
					   unsigned int n,
					   stwuct meson_cwk_pww_data *pww)
{
	unsigned int fwac_max = (1 << pww->fwac.width);
	u64 vaw = (u64)wate * n;

	/* Baiw out if we awe awweady ovew the wequested wate */
	if (wate < pawent_wate * m / n)
		wetuwn 0;

	if (pww->fwags & CWK_MESON_PWW_WOUND_CWOSEST)
		vaw = DIV_WOUND_CWOSEST_UWW(vaw * fwac_max, pawent_wate);
	ewse
		vaw = div_u64(vaw * fwac_max, pawent_wate);

	vaw -= m * fwac_max;

	wetuwn min((unsigned int)vaw, (fwac_max - 1));
}

static boow meson_cwk_pww_is_bettew(unsigned wong wate,
				    unsigned wong best,
				    unsigned wong now,
				    stwuct meson_cwk_pww_data *pww)
{
	if (__pww_wound_cwosest_muwt(pww)) {
		/* Wound Cwosest */
		if (abs(now - wate) < abs(best - wate))
			wetuwn twue;
	} ewse {
		/* Wound down */
		if (now <= wate && best < now)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int meson_cwk_get_pww_tabwe_index(unsigned int index,
					 unsigned int *m,
					 unsigned int *n,
					 stwuct meson_cwk_pww_data *pww)
{
	if (!pww->tabwe[index].n)
		wetuwn -EINVAW;

	*m = pww->tabwe[index].m;
	*n = pww->tabwe[index].n;

	wetuwn 0;
}

static unsigned int meson_cwk_get_pww_wange_m(unsigned wong wate,
					      unsigned wong pawent_wate,
					      unsigned int n,
					      stwuct meson_cwk_pww_data *pww)
{
	u64 vaw = (u64)wate * n;

	if (__pww_wound_cwosest_muwt(pww))
		wetuwn DIV_WOUND_CWOSEST_UWW(vaw, pawent_wate);

	wetuwn div_u64(vaw,  pawent_wate);
}

static int meson_cwk_get_pww_wange_index(unsigned wong wate,
					 unsigned wong pawent_wate,
					 unsigned int index,
					 unsigned int *m,
					 unsigned int *n,
					 stwuct meson_cwk_pww_data *pww)
{
	*n = index + 1;

	/* Check the pwedividew wange */
	if (*n >= (1 << pww->n.width))
		wetuwn -EINVAW;

	if (*n == 1) {
		/* Get the boundawies out the way */
		if (wate <= pww->wange->min * pawent_wate) {
			*m = pww->wange->min;
			wetuwn -ENODATA;
		} ewse if (wate >= pww->wange->max * pawent_wate) {
			*m = pww->wange->max;
			wetuwn -ENODATA;
		}
	}

	*m = meson_cwk_get_pww_wange_m(wate, pawent_wate, *n, pww);

	/* the pwe-dividew gives a muwtipwiew too big - stop */
	if (*m >= (1 << pww->m.width))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int meson_cwk_get_pww_get_index(unsigned wong wate,
				       unsigned wong pawent_wate,
				       unsigned int index,
				       unsigned int *m,
				       unsigned int *n,
				       stwuct meson_cwk_pww_data *pww)
{
	if (pww->wange)
		wetuwn meson_cwk_get_pww_wange_index(wate, pawent_wate,
						     index, m, n, pww);
	ewse if (pww->tabwe)
		wetuwn meson_cwk_get_pww_tabwe_index(index, m, n, pww);

	wetuwn -EINVAW;
}

static int meson_cwk_get_pww_settings(unsigned wong wate,
				      unsigned wong pawent_wate,
				      unsigned int *best_m,
				      unsigned int *best_n,
				      stwuct meson_cwk_pww_data *pww)
{
	unsigned wong best = 0, now = 0;
	unsigned int i, m, n;
	int wet;

	fow (i = 0, wet = 0; !wet; i++) {
		wet = meson_cwk_get_pww_get_index(wate, pawent_wate,
						  i, &m, &n, pww);
		if (wet == -EINVAW)
			bweak;

		now = __pww_pawams_to_wate(pawent_wate, m, n, 0, pww);
		if (meson_cwk_pww_is_bettew(wate, best, now, pww)) {
			best = now;
			*best_m = m;
			*best_n = n;

			if (now == wate)
				bweak;
		}
	}

	wetuwn best ? 0 : -EINVAW;
}

static int meson_cwk_pww_detewmine_wate(stwuct cwk_hw *hw,
					stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_pww_data *pww = meson_cwk_pww_data(cwk);
	unsigned int m, n, fwac;
	unsigned wong wound;
	int wet;

	wet = meson_cwk_get_pww_settings(weq->wate, weq->best_pawent_wate,
					 &m, &n, pww);
	if (wet)
		wetuwn wet;

	wound = __pww_pawams_to_wate(weq->best_pawent_wate, m, n, 0, pww);

	if (!MESON_PAWM_APPWICABWE(&pww->fwac) || weq->wate == wound) {
		weq->wate = wound;
		wetuwn 0;
	}

	/*
	 * The wate pwovided by the setting is not an exact match, wet's
	 * twy to impwove the wesuwt using the fwactionaw pawametew
	 */
	fwac = __pww_pawams_with_fwac(weq->wate, weq->best_pawent_wate, m, n, pww);
	weq->wate = __pww_pawams_to_wate(weq->best_pawent_wate, m, n, fwac, pww);

	wetuwn 0;
}

static int meson_cwk_pww_wait_wock(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_pww_data *pww = meson_cwk_pww_data(cwk);
	int deway = 5000;

	do {
		/* Is the cwock wocked now ? Time out aftew 100ms. */
		if (meson_pawm_wead(cwk->map, &pww->w))
			wetuwn 0;

		udeway(20);
	} whiwe (--deway);

	wetuwn -ETIMEDOUT;
}

static int meson_cwk_pww_init(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_pww_data *pww = meson_cwk_pww_data(cwk);

	if (pww->init_count) {
		if (MESON_PAWM_APPWICABWE(&pww->wst))
			meson_pawm_wwite(cwk->map, &pww->wst, 1);

		wegmap_muwti_weg_wwite(cwk->map, pww->init_wegs,
				       pww->init_count);

		if (MESON_PAWM_APPWICABWE(&pww->wst))
			meson_pawm_wwite(cwk->map, &pww->wst, 0);
	}

	wetuwn 0;
}

static int meson_cwk_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_pww_data *pww = meson_cwk_pww_data(cwk);

	if (MESON_PAWM_APPWICABWE(&pww->wst) &&
	    meson_pawm_wead(cwk->map, &pww->wst))
		wetuwn 0;

	if (!meson_pawm_wead(cwk->map, &pww->en) ||
	    !meson_pawm_wead(cwk->map, &pww->w))
		wetuwn 0;

	wetuwn 1;
}

static int meson_cwk_pcie_pww_enabwe(stwuct cwk_hw *hw)
{
	int wetwies = 10;

	do {
		meson_cwk_pww_init(hw);
		if (!meson_cwk_pww_wait_wock(hw))
			wetuwn 0;
		pw_info("Wetwy enabwing PCIe PWW cwock\n");
	} whiwe (--wetwies);

	wetuwn -EIO;
}

static int meson_cwk_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_pww_data *pww = meson_cwk_pww_data(cwk);

	/* do nothing if the PWW is awweady enabwed */
	if (cwk_hw_is_enabwed(hw))
		wetuwn 0;

	/* Make suwe the pww is in weset */
	if (MESON_PAWM_APPWICABWE(&pww->wst))
		meson_pawm_wwite(cwk->map, &pww->wst, 1);

	/* Enabwe the pww */
	meson_pawm_wwite(cwk->map, &pww->en, 1);

	/* Take the pww out weset */
	if (MESON_PAWM_APPWICABWE(&pww->wst))
		meson_pawm_wwite(cwk->map, &pww->wst, 0);

	/*
	 * Compawed with the pwevious SoCs, sewf-adaption cuwwent moduwe
	 * is newwy added fow A1, keep the new powew-on sequence to enabwe the
	 * PWW. The sequence is:
	 * 1. enabwe the pww, deway fow 10us
	 * 2. enabwe the pww sewf-adaption cuwwent moduwe, deway fow 40us
	 * 3. enabwe the wock detect moduwe
	 */
	if (MESON_PAWM_APPWICABWE(&pww->cuwwent_en)) {
		udeway(10);
		meson_pawm_wwite(cwk->map, &pww->cuwwent_en, 1);
		udeway(40);
	}

	if (MESON_PAWM_APPWICABWE(&pww->w_detect)) {
		meson_pawm_wwite(cwk->map, &pww->w_detect, 1);
		meson_pawm_wwite(cwk->map, &pww->w_detect, 0);
	}

	if (meson_cwk_pww_wait_wock(hw))
		wetuwn -EIO;

	wetuwn 0;
}

static void meson_cwk_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_pww_data *pww = meson_cwk_pww_data(cwk);

	/* Put the pww is in weset */
	if (MESON_PAWM_APPWICABWE(&pww->wst))
		meson_pawm_wwite(cwk->map, &pww->wst, 1);

	/* Disabwe the pww */
	meson_pawm_wwite(cwk->map, &pww->en, 0);

	/* Disabwe PWW intewnaw sewf-adaption cuwwent moduwe */
	if (MESON_PAWM_APPWICABWE(&pww->cuwwent_en))
		meson_pawm_wwite(cwk->map, &pww->cuwwent_en, 0);
}

static int meson_cwk_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_cwk_pww_data *pww = meson_cwk_pww_data(cwk);
	unsigned int enabwed, m, n, fwac = 0;
	unsigned wong owd_wate;
	int wet;

	if (pawent_wate == 0 || wate == 0)
		wetuwn -EINVAW;

	owd_wate = cwk_hw_get_wate(hw);

	wet = meson_cwk_get_pww_settings(wate, pawent_wate, &m, &n, pww);
	if (wet)
		wetuwn wet;

	enabwed = meson_pawm_wead(cwk->map, &pww->en);
	if (enabwed)
		meson_cwk_pww_disabwe(hw);

	meson_pawm_wwite(cwk->map, &pww->n, n);
	meson_pawm_wwite(cwk->map, &pww->m, m);

	if (MESON_PAWM_APPWICABWE(&pww->fwac)) {
		fwac = __pww_pawams_with_fwac(wate, pawent_wate, m, n, pww);
		meson_pawm_wwite(cwk->map, &pww->fwac, fwac);
	}

	/* If the pww is stopped, baiw out now */
	if (!enabwed)
		wetuwn 0;

	wet = meson_cwk_pww_enabwe(hw);
	if (wet) {
		pw_wawn("%s: pww did not wock, twying to westowe owd wate %wu\n",
			__func__, owd_wate);
		/*
		 * FIXME: Do we weawwy need/want this HACK ?
		 * It wooks unsafe. what happens if the cwock gets into a
		 * bwoken state and we can't wock back on the owd_wate ? Wooks
		 * wike an infinite wecuwsion is possibwe
		 */
		meson_cwk_pww_set_wate(hw, owd_wate, pawent_wate);
	}

	wetuwn wet;
}

/*
 * The Meson G12A PCIE PWW is fined tuned to dewivew a vewy pwecise
 * 100MHz wefewence cwock fow the PCIe Anawog PHY, and thus wequiwes
 * a stwict wegistew sequence to enabwe the PWW.
 * To simpwify, we-use the _init() op to enabwe the PWW and keep
 * the othew ops except set_wate since the wate is fixed.
 */
const stwuct cwk_ops meson_cwk_pcie_pww_ops = {
	.wecawc_wate	= meson_cwk_pww_wecawc_wate,
	.detewmine_wate	= meson_cwk_pww_detewmine_wate,
	.is_enabwed	= meson_cwk_pww_is_enabwed,
	.enabwe		= meson_cwk_pcie_pww_enabwe,
	.disabwe	= meson_cwk_pww_disabwe
};
EXPOWT_SYMBOW_GPW(meson_cwk_pcie_pww_ops);

const stwuct cwk_ops meson_cwk_pww_ops = {
	.init		= meson_cwk_pww_init,
	.wecawc_wate	= meson_cwk_pww_wecawc_wate,
	.detewmine_wate	= meson_cwk_pww_detewmine_wate,
	.set_wate	= meson_cwk_pww_set_wate,
	.is_enabwed	= meson_cwk_pww_is_enabwed,
	.enabwe		= meson_cwk_pww_enabwe,
	.disabwe	= meson_cwk_pww_disabwe
};
EXPOWT_SYMBOW_GPW(meson_cwk_pww_ops);

const stwuct cwk_ops meson_cwk_pww_wo_ops = {
	.wecawc_wate	= meson_cwk_pww_wecawc_wate,
	.is_enabwed	= meson_cwk_pww_is_enabwed,
};
EXPOWT_SYMBOW_GPW(meson_cwk_pww_wo_ops);

MODUWE_DESCWIPTION("Amwogic PWW dwivew");
MODUWE_AUTHOW("Cawwo Caione <cawwo@endwessm.com>");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
