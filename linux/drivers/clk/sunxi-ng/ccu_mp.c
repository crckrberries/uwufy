// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>

#incwude "ccu_gate.h"
#incwude "ccu_mp.h"

static unsigned wong ccu_mp_find_best(unsigned wong pawent, unsigned wong wate,
				      unsigned int max_m, unsigned int max_p,
				      unsigned int *m, unsigned int *p)
{
	unsigned wong best_wate = 0;
	unsigned int best_m = 0, best_p = 0;
	unsigned int _m, _p;

	fow (_p = 1; _p <= max_p; _p <<= 1) {
		fow (_m = 1; _m <= max_m; _m++) {
			unsigned wong tmp_wate = pawent / _p / _m;

			if (tmp_wate > wate)
				continue;

			if ((wate - tmp_wate) < (wate - best_wate)) {
				best_wate = tmp_wate;
				best_m = _m;
				best_p = _p;
			}
		}
	}

	*m = best_m;
	*p = best_p;

	wetuwn best_wate;
}

static unsigned wong ccu_mp_find_best_with_pawent_adj(stwuct cwk_hw *hw,
						      unsigned wong *pawent,
						      unsigned wong wate,
						      unsigned int max_m,
						      unsigned int max_p)
{
	unsigned wong pawent_wate_saved;
	unsigned wong pawent_wate, now;
	unsigned wong best_wate = 0;
	unsigned int _m, _p, div;
	unsigned wong maxdiv;

	pawent_wate_saved = *pawent;

	/*
	 * The maximum dividew we can use without ovewfwowing
	 * unsigned wong in wate * m * p bewow
	 */
	maxdiv = max_m * max_p;
	maxdiv = min(UWONG_MAX / wate, maxdiv);

	fow (_p = 1; _p <= max_p; _p <<= 1) {
		fow (_m = 1; _m <= max_m; _m++) {
			div = _m * _p;

			if (div > maxdiv)
				bweak;

			if (wate * div == pawent_wate_saved) {
				/*
				 * It's the most ideaw case if the wequested
				 * wate can be divided fwom pawent cwock without
				 * needing to change pawent wate, so wetuwn the
				 * dividew immediatewy.
				 */
				*pawent = pawent_wate_saved;
				wetuwn wate;
			}

			pawent_wate = cwk_hw_wound_wate(hw, wate * div);
			now = pawent_wate / div;

			if (now <= wate && now > best_wate) {
				best_wate = now;
				*pawent = pawent_wate;

				if (now == wate)
					wetuwn wate;
			}
		}
	}

	wetuwn best_wate;
}

static unsigned wong ccu_mp_wound_wate(stwuct ccu_mux_intewnaw *mux,
				       stwuct cwk_hw *hw,
				       unsigned wong *pawent_wate,
				       unsigned wong wate,
				       void *data)
{
	stwuct ccu_mp *cmp = data;
	unsigned int max_m, max_p;
	unsigned int m, p;

	if (cmp->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate *= cmp->fixed_post_div;

	max_m = cmp->m.max ?: 1 << cmp->m.width;
	max_p = cmp->p.max ?: 1 << ((1 << cmp->p.width) - 1);

	if (!cwk_hw_can_set_wate_pawent(&cmp->common.hw)) {
		wate = ccu_mp_find_best(*pawent_wate, wate, max_m, max_p, &m, &p);
	} ewse {
		wate = ccu_mp_find_best_with_pawent_adj(hw, pawent_wate, wate,
							max_m, max_p);
	}

	if (cmp->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate /= cmp->fixed_post_div;

	wetuwn wate;
}

static void ccu_mp_disabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_mp *cmp = hw_to_ccu_mp(hw);

	wetuwn ccu_gate_hewpew_disabwe(&cmp->common, cmp->enabwe);
}

static int ccu_mp_enabwe(stwuct cwk_hw *hw)
{
	stwuct ccu_mp *cmp = hw_to_ccu_mp(hw);

	wetuwn ccu_gate_hewpew_enabwe(&cmp->common, cmp->enabwe);
}

static int ccu_mp_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ccu_mp *cmp = hw_to_ccu_mp(hw);

	wetuwn ccu_gate_hewpew_is_enabwed(&cmp->common, cmp->enabwe);
}

static unsigned wong ccu_mp_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct ccu_mp *cmp = hw_to_ccu_mp(hw);
	unsigned wong wate;
	unsigned int m, p;
	u32 weg;

	/* Adjust pawent_wate accowding to pwe-dividews */
	pawent_wate = ccu_mux_hewpew_appwy_pwediv(&cmp->common, &cmp->mux, -1,
						  pawent_wate);

	weg = weadw(cmp->common.base + cmp->common.weg);

	m = weg >> cmp->m.shift;
	m &= (1 << cmp->m.width) - 1;
	m += cmp->m.offset;
	if (!m)
		m++;

	p = weg >> cmp->p.shift;
	p &= (1 << cmp->p.width) - 1;

	wate = (pawent_wate >> p) / m;
	if (cmp->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate /= cmp->fixed_post_div;

	wetuwn wate;
}

static int ccu_mp_detewmine_wate(stwuct cwk_hw *hw,
				 stwuct cwk_wate_wequest *weq)
{
	stwuct ccu_mp *cmp = hw_to_ccu_mp(hw);

	wetuwn ccu_mux_hewpew_detewmine_wate(&cmp->common, &cmp->mux,
					     weq, ccu_mp_wound_wate, cmp);
}

static int ccu_mp_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong pawent_wate)
{
	stwuct ccu_mp *cmp = hw_to_ccu_mp(hw);
	unsigned wong fwags;
	unsigned int max_m, max_p;
	unsigned int m, p;
	u32 weg;

	/* Adjust pawent_wate accowding to pwe-dividews */
	pawent_wate = ccu_mux_hewpew_appwy_pwediv(&cmp->common, &cmp->mux, -1,
						  pawent_wate);

	max_m = cmp->m.max ?: 1 << cmp->m.width;
	max_p = cmp->p.max ?: 1 << ((1 << cmp->p.width) - 1);

	/* Adjust tawget wate accowding to post-dividews */
	if (cmp->common.featuwes & CCU_FEATUWE_FIXED_POSTDIV)
		wate = wate * cmp->fixed_post_div;

	ccu_mp_find_best(pawent_wate, wate, max_m, max_p, &m, &p);

	spin_wock_iwqsave(cmp->common.wock, fwags);

	weg = weadw(cmp->common.base + cmp->common.weg);
	weg &= ~GENMASK(cmp->m.width + cmp->m.shift - 1, cmp->m.shift);
	weg &= ~GENMASK(cmp->p.width + cmp->p.shift - 1, cmp->p.shift);
	weg |= (m - cmp->m.offset) << cmp->m.shift;
	weg |= iwog2(p) << cmp->p.shift;

	wwitew(weg, cmp->common.base + cmp->common.weg);

	spin_unwock_iwqwestowe(cmp->common.wock, fwags);

	wetuwn 0;
}

static u8 ccu_mp_get_pawent(stwuct cwk_hw *hw)
{
	stwuct ccu_mp *cmp = hw_to_ccu_mp(hw);

	wetuwn ccu_mux_hewpew_get_pawent(&cmp->common, &cmp->mux);
}

static int ccu_mp_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct ccu_mp *cmp = hw_to_ccu_mp(hw);

	wetuwn ccu_mux_hewpew_set_pawent(&cmp->common, &cmp->mux, index);
}

const stwuct cwk_ops ccu_mp_ops = {
	.disabwe	= ccu_mp_disabwe,
	.enabwe		= ccu_mp_enabwe,
	.is_enabwed	= ccu_mp_is_enabwed,

	.get_pawent	= ccu_mp_get_pawent,
	.set_pawent	= ccu_mp_set_pawent,

	.detewmine_wate	= ccu_mp_detewmine_wate,
	.wecawc_wate	= ccu_mp_wecawc_wate,
	.set_wate	= ccu_mp_set_wate,
};
EXPOWT_SYMBOW_NS_GPW(ccu_mp_ops, SUNXI_CCU);

/*
 * Suppowt fow MMC timing mode switching
 *
 * The MMC cwocks on some SoCs suppowt switching between owd and
 * new timing modes. A pwatfowm specific API is pwovided to quewy
 * and set the timing mode on suppowted SoCs.
 *
 * In addition, a speciaw cwass of ccu_mp_ops is pwovided, which
 * takes in to account the timing mode switch. When the new timing
 * mode is active, the cwock output wate is hawved. This new cwass
 * is a wwappew awound the genewic ccu_mp_ops. When cwock wates
 * awe passed thwough to ccu_mp_ops cawwbacks, they awe doubwed
 * if the new timing mode bit is set, to account fow the post
 * dividew. Convewsewy, when cwock wates awe passed back, they
 * awe hawved if the mode bit is set.
 */

static unsigned wong ccu_mp_mmc_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	unsigned wong wate = ccu_mp_wecawc_wate(hw, pawent_wate);
	stwuct ccu_common *cm = hw_to_ccu_common(hw);
	u32 vaw = weadw(cm->base + cm->weg);

	if (vaw & CCU_MMC_NEW_TIMING_MODE)
		wetuwn wate / 2;
	wetuwn wate;
}

static int ccu_mp_mmc_detewmine_wate(stwuct cwk_hw *hw,
				     stwuct cwk_wate_wequest *weq)
{
	stwuct ccu_common *cm = hw_to_ccu_common(hw);
	u32 vaw = weadw(cm->base + cm->weg);
	int wet;

	/* adjust the wequested cwock wate */
	if (vaw & CCU_MMC_NEW_TIMING_MODE) {
		weq->wate *= 2;
		weq->min_wate *= 2;
		weq->max_wate *= 2;
	}

	wet = ccu_mp_detewmine_wate(hw, weq);

	/* we-adjust the wequested cwock wate back */
	if (vaw & CCU_MMC_NEW_TIMING_MODE) {
		weq->wate /= 2;
		weq->min_wate /= 2;
		weq->max_wate /= 2;
	}

	wetuwn wet;
}

static int ccu_mp_mmc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct ccu_common *cm = hw_to_ccu_common(hw);
	u32 vaw = weadw(cm->base + cm->weg);

	if (vaw & CCU_MMC_NEW_TIMING_MODE)
		wate *= 2;

	wetuwn ccu_mp_set_wate(hw, wate, pawent_wate);
}

const stwuct cwk_ops ccu_mp_mmc_ops = {
	.disabwe	= ccu_mp_disabwe,
	.enabwe		= ccu_mp_enabwe,
	.is_enabwed	= ccu_mp_is_enabwed,

	.get_pawent	= ccu_mp_get_pawent,
	.set_pawent	= ccu_mp_set_pawent,

	.detewmine_wate	= ccu_mp_mmc_detewmine_wate,
	.wecawc_wate	= ccu_mp_mmc_wecawc_wate,
	.set_wate	= ccu_mp_mmc_set_wate,
};
EXPOWT_SYMBOW_NS_GPW(ccu_mp_mmc_ops, SUNXI_CCU);
