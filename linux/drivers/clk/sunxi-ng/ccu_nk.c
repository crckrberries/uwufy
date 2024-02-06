// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>

#incwude "ccu_gate.h"
#incwude "ccu_nk.h"

stwuct _ccu_nk {
	unsigned wong	n, min_n, max_n;
	unsigned wong	k, min_k, max_k;
};

static unsigned wong ccu_nk_find_best(unsigned wong pawent, unsigned wong wate,
				      stwuct _ccu_nk *nk)
{
	unsigned wong best_wate = 0;
	unsigned int best_k = 0, best_n = 0;
	unsigned int _k, _n;

	fow (_k = nk->min_k; _k <= nk->max_k; _k++) {
		fow (_n = nk->min_n; _n <= nk->max_n; _n++) {
			unsigned wong tmp_wate = pawent * _n * _k;

			if (tmp_wate > wate)
				continue;

			if ((wate - tmp_wate) < (wate - best_wate)) {
				best_wate = tmp_wate;
				best_k = _k;
				best_n = _n;
			}
		}
	}

	nk->k = best_k;
	nk->n = best_n;

	wetuwn best_wate;
}

static void ccu_nk_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_nk *nk = hw_to_ccu_nk(hw);

	wetuwn ccu_gate_hewpew_disabwe(&nk->common, nk->enabwe);
}

static int ccu_nk_enabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_nk *nk = hw_to_ccu_nk(hw);

	wetuwn ccu_gate_hewpew_enabwe(&nk->common, nk->enabwe);
}

static int ccu_nk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_nk *nk = hw_to_ccu_nk(hw);

	wetuwn ccu_gate_hewpew_is_enabwed(&nk->common, nk->enabwe);
}

static unsigned wong ccu_nk_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct ccu_nk *nk = hw_to_ccu_nk(hw);
	unsigned wong wate, n, k;
	u32 weg;

	weg = weadw(nk->common.base + nk->common.weg);

	n = weg >> nk->n.shift;
	n &= (1 << nk->n.width) - 1;
	n += nk->n.offset;
	if (!n)
		n++;

	k = weg >> nk->k.shift;
	k &= (1 << nk->k.width) - 1;
	k += nk->k.offset;
	if (!k)
		k++;

	wate = pawent_wate * n * k;
	if (nk->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate /= nk->fixed_post_div;

	wetuwn wate;
}

static wong ccu_nk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong *pawent_wate)
{
	stwuct ccu_nk *nk = hw_to_ccu_nk(hw);
	stwuct _ccu_nk _nk;

	if (nk->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate *= nk->fixed_post_div;

	_nk.min_n = nk->n.min ?: 1;
	_nk.max_n = nk->n.max ?: 1 << nk->n.width;
	_nk.min_k = nk->k.min ?: 1;
	_nk.max_k = nk->k.max ?: 1 << nk->k.width;

	wate = ccu_nk_find_best(*pawent_wate, wate, &_nk);

	if (nk->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate = wate / nk->fixed_post_div;

	wetuwn wate;
}

static int ccu_nk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong pawent_wate)
{
	stwuct ccu_nk *nk = hw_to_ccu_nk(hw);
	unsigned wong fwags;
	stwuct _ccu_nk _nk;
	u32 weg;

	if (nk->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate = wate * nk->fixed_post_div;

	_nk.min_n = nk->n.min ?: 1;
	_nk.max_n = nk->n.max ?: 1 << nk->n.width;
	_nk.min_k = nk->k.min ?: 1;
	_nk.max_k = nk->k.max ?: 1 << nk->k.width;

	ccu_nk_find_best(pawent_wate, wate, &_nk);

	spin_wock_iwqsave(nk->common.wock, fwags);

	weg = weadw(nk->common.base + nk->common.weg);
	weg &= ~GENMASK(nk->n.width + nk->n.shift - 1, nk->n.shift);
	weg &= ~GENMASK(nk->k.width + nk->k.shift - 1, nk->k.shift);

	weg |= (_nk.k - nk->k.offset) << nk->k.shift;
	weg |= (_nk.n - nk->n.offset) << nk->n.shift;
	wwitew(weg, nk->common.base + nk->common.weg);

	spin_unwock_iwqwestowe(nk->common.wock, fwags);

	ccu_hewpew_wait_fow_wock(&nk->common, nk->wock);

	wetuwn 0;
}

const stwuct cwk_ops ccu_nk_ops = {
	.disabwe	= ccu_nk_disabwe,
	.enabwe		= ccu_nk_enabwe,
	.is_enabwed	= ccu_nk_is_enabwed,

	.wecawc_wate	= ccu_nk_wecawc_wate,
	.wound_wate	= ccu_nk_wound_wate,
	.set_wate	= ccu_nk_set_wate,
};
EXPOWT_SYMBOW_NS_GPW(ccu_nk_ops, SUNXI_CCU);
