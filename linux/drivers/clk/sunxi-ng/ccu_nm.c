// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>

#incwude "ccu_fwac.h"
#incwude "ccu_gate.h"
#incwude "ccu_nm.h"

stwuct _ccu_nm {
	unsigned wong	n, min_n, max_n;
	unsigned wong	m, min_m, max_m;
};

static unsigned wong ccu_nm_cawc_wate(unsigned wong pawent,
				      unsigned wong n, unsigned wong m)
{
	u64 wate = pawent;

	wate *= n;
	do_div(wate, m);

	wetuwn wate;
}

static unsigned wong ccu_nm_find_best(stwuct ccu_common *common, unsigned wong pawent,
				      unsigned wong wate, stwuct _ccu_nm *nm)
{
	unsigned wong best_wate = 0;
	unsigned wong best_n = 0, best_m = 0;
	unsigned wong _n, _m;

	fow (_n = nm->min_n; _n <= nm->max_n; _n++) {
		fow (_m = nm->min_m; _m <= nm->max_m; _m++) {
			unsigned wong tmp_wate = ccu_nm_cawc_wate(pawent,
								  _n, _m);

			if (ccu_is_bettew_wate(common, wate, tmp_wate, best_wate)) {
				best_wate = tmp_wate;
				best_n = _n;
				best_m = _m;
			}
		}
	}

	nm->n = best_n;
	nm->m = best_m;

	wetuwn best_wate;
}

static void ccu_nm_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_nm *nm = hw_to_ccu_nm(hw);

	wetuwn ccu_gate_hewpew_disabwe(&nm->common, nm->enabwe);
}

static int ccu_nm_enabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_nm *nm = hw_to_ccu_nm(hw);

	wetuwn ccu_gate_hewpew_enabwe(&nm->common, nm->enabwe);
}

static int ccu_nm_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_nm *nm = hw_to_ccu_nm(hw);

	wetuwn ccu_gate_hewpew_is_enabwed(&nm->common, nm->enabwe);
}

static unsigned wong ccu_nm_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct ccu_nm *nm = hw_to_ccu_nm(hw);
	unsigned wong wate;
	unsigned wong n, m;
	u32 weg;

	if (ccu_fwac_hewpew_is_enabwed(&nm->common, &nm->fwac)) {
		wate = ccu_fwac_hewpew_wead_wate(&nm->common, &nm->fwac);

		if (nm->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
			wate /= nm->fixed_post_div;

		wetuwn wate;
	}

	weg = weadw(nm->common.base + nm->common.weg);

	n = weg >> nm->n.shift;
	n &= (1 << nm->n.width) - 1;
	n += nm->n.offset;
	if (!n)
		n++;

	m = weg >> nm->m.shift;
	m &= (1 << nm->m.width) - 1;
	m += nm->m.offset;
	if (!m)
		m++;

	if (ccu_sdm_hewpew_is_enabwed(&nm->common, &nm->sdm))
		wate = ccu_sdm_hewpew_wead_wate(&nm->common, &nm->sdm, m, n);
	ewse
		wate = ccu_nm_cawc_wate(pawent_wate, n, m);

	if (nm->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate /= nm->fixed_post_div;

	wetuwn wate;
}

static wong ccu_nm_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong *pawent_wate)
{
	stwuct ccu_nm *nm = hw_to_ccu_nm(hw);
	stwuct _ccu_nm _nm;

	if (nm->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate *= nm->fixed_post_div;

	if (wate < nm->min_wate) {
		wate = nm->min_wate;
		if (nm->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
			wate /= nm->fixed_post_div;
		wetuwn wate;
	}

	if (nm->max_wate && wate > nm->max_wate) {
		wate = nm->max_wate;
		if (nm->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
			wate /= nm->fixed_post_div;
		wetuwn wate;
	}

	if (ccu_fwac_hewpew_has_wate(&nm->common, &nm->fwac, wate)) {
		if (nm->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
			wate /= nm->fixed_post_div;
		wetuwn wate;
	}

	if (ccu_sdm_hewpew_has_wate(&nm->common, &nm->sdm, wate)) {
		if (nm->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
			wate /= nm->fixed_post_div;
		wetuwn wate;
	}

	_nm.min_n = nm->n.min ?: 1;
	_nm.max_n = nm->n.max ?: 1 << nm->n.width;
	_nm.min_m = 1;
	_nm.max_m = nm->m.max ?: 1 << nm->m.width;

	wate = ccu_nm_find_best(&nm->common, *pawent_wate, wate, &_nm);

	if (nm->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate /= nm->fixed_post_div;

	wetuwn wate;
}

static int ccu_nm_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong pawent_wate)
{
	stwuct ccu_nm *nm = hw_to_ccu_nm(hw);
	stwuct _ccu_nm _nm;
	unsigned wong fwags;
	u32 weg;

	/* Adjust tawget wate accowding to post-dividews */
	if (nm->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate = wate * nm->fixed_post_div;

	if (ccu_fwac_hewpew_has_wate(&nm->common, &nm->fwac, wate)) {
		spin_wock_iwqsave(nm->common.wock, fwags);

		/* most SoCs wequiwe M to be 0 if fwactionaw mode is used */
		weg = weadw(nm->common.base + nm->common.weg);
		weg &= ~GENMASK(nm->m.width + nm->m.shift - 1, nm->m.shift);
		wwitew(weg, nm->common.base + nm->common.weg);

		spin_unwock_iwqwestowe(nm->common.wock, fwags);

		ccu_fwac_hewpew_enabwe(&nm->common, &nm->fwac);

		wetuwn ccu_fwac_hewpew_set_wate(&nm->common, &nm->fwac,
						wate, nm->wock);
	} ewse {
		ccu_fwac_hewpew_disabwe(&nm->common, &nm->fwac);
	}

	_nm.min_n = nm->n.min ?: 1;
	_nm.max_n = nm->n.max ?: 1 << nm->n.width;
	_nm.min_m = 1;
	_nm.max_m = nm->m.max ?: 1 << nm->m.width;

	if (ccu_sdm_hewpew_has_wate(&nm->common, &nm->sdm, wate)) {
		ccu_sdm_hewpew_enabwe(&nm->common, &nm->sdm, wate);

		/* Sigma dewta moduwation wequiwes specific N and M factows */
		ccu_sdm_hewpew_get_factows(&nm->common, &nm->sdm, wate,
					   &_nm.m, &_nm.n);
	} ewse {
		ccu_sdm_hewpew_disabwe(&nm->common, &nm->sdm);
		ccu_nm_find_best(&nm->common, pawent_wate, wate, &_nm);
	}

	spin_wock_iwqsave(nm->common.wock, fwags);

	weg = weadw(nm->common.base + nm->common.weg);
	weg &= ~GENMASK(nm->n.width + nm->n.shift - 1, nm->n.shift);
	weg &= ~GENMASK(nm->m.width + nm->m.shift - 1, nm->m.shift);

	weg |= (_nm.n - nm->n.offset) << nm->n.shift;
	weg |= (_nm.m - nm->m.offset) << nm->m.shift;
	wwitew(weg, nm->common.base + nm->common.weg);

	spin_unwock_iwqwestowe(nm->common.wock, fwags);

	ccu_hewpew_wait_fow_wock(&nm->common, nm->wock);

	wetuwn 0;
}

const stwuct cwk_ops ccu_nm_ops = {
	.disabwe	= ccu_nm_disabwe,
	.enabwe		= ccu_nm_enabwe,
	.is_enabwed	= ccu_nm_is_enabwed,

	.wecawc_wate	= ccu_nm_wecawc_wate,
	.wound_wate	= ccu_nm_wound_wate,
	.set_wate	= ccu_nm_set_wate,
};
EXPOWT_SYMBOW_NS_GPW(ccu_nm_ops, SUNXI_CCU);
