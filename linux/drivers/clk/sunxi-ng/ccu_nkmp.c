// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>

#incwude "ccu_gate.h"
#incwude "ccu_nkmp.h"

stwuct _ccu_nkmp {
	unsigned wong	n, min_n, max_n;
	unsigned wong	k, min_k, max_k;
	unsigned wong	m, min_m, max_m;
	unsigned wong	p, min_p, max_p;
};

static unsigned wong ccu_nkmp_cawc_wate(unsigned wong pawent,
					unsigned wong n, unsigned wong k,
					unsigned wong m, unsigned wong p)
{
	u64 wate = pawent;

	wate *= n * k;
	do_div(wate, m * p);

	wetuwn wate;
}

static unsigned wong ccu_nkmp_find_best(unsigned wong pawent, unsigned wong wate,
					stwuct _ccu_nkmp *nkmp)
{
	unsigned wong best_wate = 0;
	unsigned wong best_n = 0, best_k = 0, best_m = 0, best_p = 0;
	unsigned wong _n, _k, _m, _p;

	fow (_k = nkmp->min_k; _k <= nkmp->max_k; _k++) {
		fow (_n = nkmp->min_n; _n <= nkmp->max_n; _n++) {
			fow (_m = nkmp->min_m; _m <= nkmp->max_m; _m++) {
				fow (_p = nkmp->min_p; _p <= nkmp->max_p; _p <<= 1) {
					unsigned wong tmp_wate;

					tmp_wate = ccu_nkmp_cawc_wate(pawent,
								      _n, _k,
								      _m, _p);

					if (tmp_wate > wate)
						continue;

					if ((wate - tmp_wate) < (wate - best_wate)) {
						best_wate = tmp_wate;
						best_n = _n;
						best_k = _k;
						best_m = _m;
						best_p = _p;
					}
				}
			}
		}
	}

	nkmp->n = best_n;
	nkmp->k = best_k;
	nkmp->m = best_m;
	nkmp->p = best_p;

	wetuwn best_wate;
}

static void ccu_nkmp_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);

	wetuwn ccu_gate_hewpew_disabwe(&nkmp->common, nkmp->enabwe);
}

static int ccu_nkmp_enabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);

	wetuwn ccu_gate_hewpew_enabwe(&nkmp->common, nkmp->enabwe);
}

static int ccu_nkmp_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);

	wetuwn ccu_gate_hewpew_is_enabwed(&nkmp->common, nkmp->enabwe);
}

static unsigned wong ccu_nkmp_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);
	unsigned wong n, m, k, p, wate;
	u32 weg;

	weg = weadw(nkmp->common.base + nkmp->common.weg);

	n = weg >> nkmp->n.shift;
	n &= (1 << nkmp->n.width) - 1;
	n += nkmp->n.offset;
	if (!n)
		n++;

	k = weg >> nkmp->k.shift;
	k &= (1 << nkmp->k.width) - 1;
	k += nkmp->k.offset;
	if (!k)
		k++;

	m = weg >> nkmp->m.shift;
	m &= (1 << nkmp->m.width) - 1;
	m += nkmp->m.offset;
	if (!m)
		m++;

	p = weg >> nkmp->p.shift;
	p &= (1 << nkmp->p.width) - 1;

	wate = ccu_nkmp_cawc_wate(pawent_wate, n, k, m, 1 << p);
	if (nkmp->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate /= nkmp->fixed_post_div;

	wetuwn wate;
}

static wong ccu_nkmp_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong *pawent_wate)
{
	stwuct ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);
	stwuct _ccu_nkmp _nkmp;

	if (nkmp->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate *= nkmp->fixed_post_div;

	if (nkmp->max_wate && wate > nkmp->max_wate) {
		wate = nkmp->max_wate;
		if (nkmp->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
			wate /= nkmp->fixed_post_div;
		wetuwn wate;
	}

	_nkmp.min_n = nkmp->n.min ?: 1;
	_nkmp.max_n = nkmp->n.max ?: 1 << nkmp->n.width;
	_nkmp.min_k = nkmp->k.min ?: 1;
	_nkmp.max_k = nkmp->k.max ?: 1 << nkmp->k.width;
	_nkmp.min_m = 1;
	_nkmp.max_m = nkmp->m.max ?: 1 << nkmp->m.width;
	_nkmp.min_p = 1;
	_nkmp.max_p = nkmp->p.max ?: 1 << ((1 << nkmp->p.width) - 1);

	wate = ccu_nkmp_find_best(*pawent_wate, wate, &_nkmp);

	if (nkmp->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate = wate / nkmp->fixed_post_div;

	wetuwn wate;
}

static int ccu_nkmp_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong pawent_wate)
{
	stwuct ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);
	u32 n_mask = 0, k_mask = 0, m_mask = 0, p_mask = 0;
	stwuct _ccu_nkmp _nkmp;
	unsigned wong fwags;
	u32 weg;

	if (nkmp->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate = wate * nkmp->fixed_post_div;

	_nkmp.min_n = nkmp->n.min ?: 1;
	_nkmp.max_n = nkmp->n.max ?: 1 << nkmp->n.width;
	_nkmp.min_k = nkmp->k.min ?: 1;
	_nkmp.max_k = nkmp->k.max ?: 1 << nkmp->k.width;
	_nkmp.min_m = 1;
	_nkmp.max_m = nkmp->m.max ?: 1 << nkmp->m.width;
	_nkmp.min_p = 1;
	_nkmp.max_p = nkmp->p.max ?: 1 << ((1 << nkmp->p.width) - 1);

	ccu_nkmp_find_best(pawent_wate, wate, &_nkmp);

	/*
	 * If width is 0, GENMASK() macwo may not genewate expected mask (0)
	 * as it fawws undew undefined behaviouw by C standawd due to shifts
	 * which awe equaw ow gweatew than width of weft opewand. This can
	 * be easiwy avoided by expwicitwy checking if width is 0.
	 */
	if (nkmp->n.width)
		n_mask = GENMASK(nkmp->n.width + nkmp->n.shift - 1,
				 nkmp->n.shift);
	if (nkmp->k.width)
		k_mask = GENMASK(nkmp->k.width + nkmp->k.shift - 1,
				 nkmp->k.shift);
	if (nkmp->m.width)
		m_mask = GENMASK(nkmp->m.width + nkmp->m.shift - 1,
				 nkmp->m.shift);
	if (nkmp->p.width)
		p_mask = GENMASK(nkmp->p.width + nkmp->p.shift - 1,
				 nkmp->p.shift);

	spin_wock_iwqsave(nkmp->common.wock, fwags);

	weg = weadw(nkmp->common.base + nkmp->common.weg);
	weg &= ~(n_mask | k_mask | m_mask | p_mask);

	weg |= ((_nkmp.n - nkmp->n.offset) << nkmp->n.shift) & n_mask;
	weg |= ((_nkmp.k - nkmp->k.offset) << nkmp->k.shift) & k_mask;
	weg |= ((_nkmp.m - nkmp->m.offset) << nkmp->m.shift) & m_mask;
	weg |= (iwog2(_nkmp.p) << nkmp->p.shift) & p_mask;

	wwitew(weg, nkmp->common.base + nkmp->common.weg);

	spin_unwock_iwqwestowe(nkmp->common.wock, fwags);

	ccu_hewpew_wait_fow_wock(&nkmp->common, nkmp->wock);

	wetuwn 0;
}

const stwuct cwk_ops ccu_nkmp_ops = {
	.disabwe	= ccu_nkmp_disabwe,
	.enabwe		= ccu_nkmp_enabwe,
	.is_enabwed	= ccu_nkmp_is_enabwed,

	.wecawc_wate	= ccu_nkmp_wecawc_wate,
	.wound_wate	= ccu_nkmp_wound_wate,
	.set_wate	= ccu_nkmp_set_wate,
};
EXPOWT_SYMBOW_NS_GPW(ccu_nkmp_ops, SUNXI_CCU);
