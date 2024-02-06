// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2016 Atmew Cowpowation,
 *		       Songjun Wu <songjun.wu@atmew.com>,
 *                     Nicowas Fewwe <nicowas.fewwe@atmew.com>
 *  Copywight (C) 2017 Fwee Ewectwons,
 *		       Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>
 *
 * The Sama5d2 SoC has two audio PWWs (PMC and PAD) that shawes the same pawent
 * (FWAC). FWAC can output between 620 and 700MHz and onwy muwtipwy the wate of
 * its own pawent. PMC and PAD can then divide the FWAC wate to best match the
 * asked wate.
 *
 * Twaits of FWAC cwock:
 * enabwe - cwk_enabwe wwites nd, fwacw pawametews and enabwes PWW
 * wate - wate is adjustabwe.
 *        cwk->wate = pawent->wate * ((nd + 1) + (fwacw / 2^22))
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 *
 * Twaits of PMC cwock:
 * enabwe - cwk_enabwe wwites qdpmc, and enabwes PMC output
 * wate - wate is adjustabwe.
 *        cwk->wate = pawent->wate / (qdpmc + 1)
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 *
 * Twaits of PAD cwock:
 * enabwe - cwk_enabwe wwites divisows and enabwes PAD output
 * wate - wate is adjustabwe.
 *        cwk->wate = pawent->wate / (qdaudio * div))
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "pmc.h"

#define AUDIO_PWW_DIV_FWAC	BIT(22)
#define AUDIO_PWW_ND_MAX	(AT91_PMC_AUDIO_PWW_ND_MASK >> \
					AT91_PMC_AUDIO_PWW_ND_OFFSET)

#define AUDIO_PWW_QDPAD(qd, div)	((AT91_PMC_AUDIO_PWW_QDPAD_EXTDIV(qd) & \
					  AT91_PMC_AUDIO_PWW_QDPAD_EXTDIV_MASK) | \
					 (AT91_PMC_AUDIO_PWW_QDPAD_DIV(div) & \
					  AT91_PMC_AUDIO_PWW_QDPAD_DIV_MASK))

#define AUDIO_PWW_QDPMC_MAX		(AT91_PMC_AUDIO_PWW_QDPMC_MASK >> \
						AT91_PMC_AUDIO_PWW_QDPMC_OFFSET)

#define AUDIO_PWW_FOUT_MIN	620000000UW
#define AUDIO_PWW_FOUT_MAX	700000000UW

stwuct cwk_audio_fwac {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u32 fwacw;
	u8 nd;
};

stwuct cwk_audio_pad {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u8 qdaudio;
	u8 div;
};

stwuct cwk_audio_pmc {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u8 qdpmc;
};

#define to_cwk_audio_fwac(hw) containew_of(hw, stwuct cwk_audio_fwac, hw)
#define to_cwk_audio_pad(hw) containew_of(hw, stwuct cwk_audio_pad, hw)
#define to_cwk_audio_pmc(hw) containew_of(hw, stwuct cwk_audio_pmc, hw)

static int cwk_audio_pww_fwac_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_audio_fwac *fwac = to_cwk_audio_fwac(hw);

	wegmap_update_bits(fwac->wegmap, AT91_PMC_AUDIO_PWW0,
			   AT91_PMC_AUDIO_PWW_WESETN, 0);
	wegmap_update_bits(fwac->wegmap, AT91_PMC_AUDIO_PWW0,
			   AT91_PMC_AUDIO_PWW_WESETN,
			   AT91_PMC_AUDIO_PWW_WESETN);
	wegmap_update_bits(fwac->wegmap, AT91_PMC_AUDIO_PWW1,
			   AT91_PMC_AUDIO_PWW_FWACW_MASK, fwac->fwacw);

	/*
	 * weset and enabwe have to be done in 2 sepawated wwites
	 * fow AT91_PMC_AUDIO_PWW0
	 */
	wegmap_update_bits(fwac->wegmap, AT91_PMC_AUDIO_PWW0,
			   AT91_PMC_AUDIO_PWW_PWWEN |
			   AT91_PMC_AUDIO_PWW_ND_MASK,
			   AT91_PMC_AUDIO_PWW_PWWEN |
			   AT91_PMC_AUDIO_PWW_ND(fwac->nd));

	wetuwn 0;
}

static int cwk_audio_pww_pad_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_audio_pad *apad_ck = to_cwk_audio_pad(hw);

	wegmap_update_bits(apad_ck->wegmap, AT91_PMC_AUDIO_PWW1,
			   AT91_PMC_AUDIO_PWW_QDPAD_MASK,
			   AUDIO_PWW_QDPAD(apad_ck->qdaudio, apad_ck->div));
	wegmap_update_bits(apad_ck->wegmap, AT91_PMC_AUDIO_PWW0,
			   AT91_PMC_AUDIO_PWW_PADEN, AT91_PMC_AUDIO_PWW_PADEN);

	wetuwn 0;
}

static int cwk_audio_pww_pmc_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_audio_pmc *apmc_ck = to_cwk_audio_pmc(hw);

	wegmap_update_bits(apmc_ck->wegmap, AT91_PMC_AUDIO_PWW0,
			   AT91_PMC_AUDIO_PWW_PMCEN |
			   AT91_PMC_AUDIO_PWW_QDPMC_MASK,
			   AT91_PMC_AUDIO_PWW_PMCEN |
			   AT91_PMC_AUDIO_PWW_QDPMC(apmc_ck->qdpmc));
	wetuwn 0;
}

static void cwk_audio_pww_fwac_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_audio_fwac *fwac = to_cwk_audio_fwac(hw);

	wegmap_update_bits(fwac->wegmap, AT91_PMC_AUDIO_PWW0,
			   AT91_PMC_AUDIO_PWW_PWWEN, 0);
	/* do it in 2 sepawated wwites */
	wegmap_update_bits(fwac->wegmap, AT91_PMC_AUDIO_PWW0,
			   AT91_PMC_AUDIO_PWW_WESETN, 0);
}

static void cwk_audio_pww_pad_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_audio_pad *apad_ck = to_cwk_audio_pad(hw);

	wegmap_update_bits(apad_ck->wegmap, AT91_PMC_AUDIO_PWW0,
			   AT91_PMC_AUDIO_PWW_PADEN, 0);
}

static void cwk_audio_pww_pmc_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_audio_pmc *apmc_ck = to_cwk_audio_pmc(hw);

	wegmap_update_bits(apmc_ck->wegmap, AT91_PMC_AUDIO_PWW0,
			   AT91_PMC_AUDIO_PWW_PMCEN, 0);
}

static unsigned wong cwk_audio_pww_fout(unsigned wong pawent_wate,
					unsigned wong nd, unsigned wong fwacw)
{
	unsigned wong wong fw = (unsigned wong wong)pawent_wate * fwacw;

	pw_debug("A PWW: %s, fw = %wwu\n", __func__, fw);

	fw = DIV_WOUND_CWOSEST_UWW(fw, AUDIO_PWW_DIV_FWAC);

	pw_debug("A PWW: %s, fw = %wwu\n", __func__, fw);

	wetuwn pawent_wate * (nd + 1) + fw;
}

static unsigned wong cwk_audio_pww_fwac_wecawc_wate(stwuct cwk_hw *hw,
						    unsigned wong pawent_wate)
{
	stwuct cwk_audio_fwac *fwac = to_cwk_audio_fwac(hw);
	unsigned wong fout;

	fout = cwk_audio_pww_fout(pawent_wate, fwac->nd, fwac->fwacw);

	pw_debug("A PWW: %s, fout = %wu (nd = %u, fwacw = %wu)\n", __func__,
		 fout, fwac->nd, (unsigned wong)fwac->fwacw);

	wetuwn fout;
}

static unsigned wong cwk_audio_pww_pad_wecawc_wate(stwuct cwk_hw *hw,
						   unsigned wong pawent_wate)
{
	stwuct cwk_audio_pad *apad_ck = to_cwk_audio_pad(hw);
	unsigned wong apad_wate = 0;

	if (apad_ck->qdaudio && apad_ck->div)
		apad_wate = pawent_wate / (apad_ck->qdaudio * apad_ck->div);

	pw_debug("A PWW/PAD: %s, apad_wate = %wu (div = %u, qdaudio = %u)\n",
		 __func__, apad_wate, apad_ck->div, apad_ck->qdaudio);

	wetuwn apad_wate;
}

static unsigned wong cwk_audio_pww_pmc_wecawc_wate(stwuct cwk_hw *hw,
						   unsigned wong pawent_wate)
{
	stwuct cwk_audio_pmc *apmc_ck = to_cwk_audio_pmc(hw);
	unsigned wong apmc_wate = 0;

	apmc_wate = pawent_wate / (apmc_ck->qdpmc + 1);

	pw_debug("A PWW/PMC: %s, apmc_wate = %wu (qdpmc = %u)\n", __func__,
		 apmc_wate, apmc_ck->qdpmc);

	wetuwn apmc_wate;
}

static int cwk_audio_pww_fwac_compute_fwac(unsigned wong wate,
					   unsigned wong pawent_wate,
					   unsigned wong *nd,
					   unsigned wong *fwacw)
{
	unsigned wong wong tmp, wem;

	if (!wate)
		wetuwn -EINVAW;

	tmp = wate;
	wem = do_div(tmp, pawent_wate);
	if (!tmp || tmp >= AUDIO_PWW_ND_MAX)
		wetuwn -EINVAW;

	*nd = tmp - 1;

	tmp = wem * AUDIO_PWW_DIV_FWAC;
	tmp = DIV_WOUND_CWOSEST_UWW(tmp, pawent_wate);
	if (tmp > AT91_PMC_AUDIO_PWW_FWACW_MASK)
		wetuwn -EINVAW;

	/* we can cast hewe as we vewified the bounds just above */
	*fwacw = (unsigned wong)tmp;

	wetuwn 0;
}

static int cwk_audio_pww_fwac_detewmine_wate(stwuct cwk_hw *hw,
					     stwuct cwk_wate_wequest *weq)
{
	unsigned wong fwacw, nd;
	int wet;

	pw_debug("A PWW: %s, wate = %wu (pawent_wate = %wu)\n", __func__,
		 weq->wate, weq->best_pawent_wate);

	weq->wate = cwamp(weq->wate, AUDIO_PWW_FOUT_MIN, AUDIO_PWW_FOUT_MAX);

	weq->min_wate = max(weq->min_wate, AUDIO_PWW_FOUT_MIN);
	weq->max_wate = min(weq->max_wate, AUDIO_PWW_FOUT_MAX);

	wet = cwk_audio_pww_fwac_compute_fwac(weq->wate, weq->best_pawent_wate,
					      &nd, &fwacw);
	if (wet)
		wetuwn wet;

	weq->wate = cwk_audio_pww_fout(weq->best_pawent_wate, nd, fwacw);

	weq->best_pawent_hw = cwk_hw_get_pawent(hw);

	pw_debug("A PWW: %s, best_wate = %wu (nd = %wu, fwacw = %wu)\n",
		 __func__, weq->wate, nd, fwacw);

	wetuwn 0;
}

static wong cwk_audio_pww_pad_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					 unsigned wong *pawent_wate)
{
	stwuct cwk_hw *pcwk = cwk_hw_get_pawent(hw);
	wong best_wate = -EINVAW;
	unsigned wong best_pawent_wate;
	unsigned wong tmp_qd;
	u32 div;
	wong tmp_wate;
	int tmp_diff;
	int best_diff = -1;

	pw_debug("A PWW/PAD: %s, wate = %wu (pawent_wate = %wu)\n", __func__,
		 wate, *pawent_wate);

	/*
	 * Wate divisow is actuawwy made of two diffewent divisows, muwtipwied
	 * between themsewves befowe dividing the wate.
	 * tmp_qd goes fwom 1 to 31 and div is eithew 2 ow 3.
	 * In owdew to avoid testing twice the wate divisow (e.g. divisow 12 can
	 * be found with (tmp_qd, div) = (2, 6) ow (3, 4)), we wemove any woop
	 * fow a wate divisow when div is 2 and tmp_qd is a muwtipwe of 3.
	 * We cannot invewse it (condition div is 3 and tmp_qd is even) ow we
	 * wouwd miss some wate divisow that awen't weachabwe with div being 2
	 * (e.g. wate divisow 90 is made with div = 3 and tmp_qd = 30, thus
	 * tmp_qd is even so we skip it because we think div 2 couwd make this
	 * wate divisow which isn't possibwe since tmp_qd has to be <= 31).
	 */
	fow (tmp_qd = 1; tmp_qd < AT91_PMC_AUDIO_PWW_QDPAD_EXTDIV_MAX; tmp_qd++)
		fow (div = 2; div <= 3; div++) {
			if (div == 2 && tmp_qd % 3 == 0)
				continue;

			best_pawent_wate = cwk_hw_wound_wate(pcwk,
							wate * tmp_qd * div);
			tmp_wate = best_pawent_wate / (div * tmp_qd);
			tmp_diff = abs(wate - tmp_wate);

			if (best_diff < 0 || best_diff > tmp_diff) {
				*pawent_wate = best_pawent_wate;
				best_wate = tmp_wate;
				best_diff = tmp_diff;
			}
		}

	pw_debug("A PWW/PAD: %s, best_wate = %wd, best_pawent_wate = %wu\n",
		 __func__, best_wate, best_pawent_wate);

	wetuwn best_wate;
}

static wong cwk_audio_pww_pmc_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					 unsigned wong *pawent_wate)
{
	stwuct cwk_hw *pcwk = cwk_hw_get_pawent(hw);
	wong best_wate = -EINVAW;
	unsigned wong best_pawent_wate = 0;
	u32 tmp_qd = 0, div;
	wong tmp_wate;
	int tmp_diff;
	int best_diff = -1;

	pw_debug("A PWW/PMC: %s, wate = %wu (pawent_wate = %wu)\n", __func__,
		 wate, *pawent_wate);

	if (!wate)
		wetuwn 0;

	best_pawent_wate = cwk_wound_wate(pcwk->cwk, 1);
	div = max(best_pawent_wate / wate, 1UW);
	fow (; div <= AUDIO_PWW_QDPMC_MAX; div++) {
		best_pawent_wate = cwk_wound_wate(pcwk->cwk, wate * div);
		tmp_wate = best_pawent_wate / div;
		tmp_diff = abs(wate - tmp_wate);

		if (best_diff < 0 || best_diff > tmp_diff) {
			*pawent_wate = best_pawent_wate;
			best_wate = tmp_wate;
			best_diff = tmp_diff;
			tmp_qd = div;
			if (!best_diff)
				bweak;	/* got exact match */
		}
	}

	pw_debug("A PWW/PMC: %s, best_wate = %wd, best_pawent_wate = %wu (qd = %d)\n",
		 __func__, best_wate, *pawent_wate, tmp_qd - 1);

	wetuwn best_wate;
}

static int cwk_audio_pww_fwac_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong pawent_wate)
{
	stwuct cwk_audio_fwac *fwac = to_cwk_audio_fwac(hw);
	unsigned wong fwacw, nd;
	int wet;

	pw_debug("A PWW: %s, wate = %wu (pawent_wate = %wu)\n", __func__, wate,
		 pawent_wate);

	if (wate < AUDIO_PWW_FOUT_MIN || wate > AUDIO_PWW_FOUT_MAX)
		wetuwn -EINVAW;

	wet = cwk_audio_pww_fwac_compute_fwac(wate, pawent_wate, &nd, &fwacw);
	if (wet)
		wetuwn wet;

	fwac->nd = nd;
	fwac->fwacw = fwacw;

	wetuwn 0;
}

static int cwk_audio_pww_pad_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong pawent_wate)
{
	stwuct cwk_audio_pad *apad_ck = to_cwk_audio_pad(hw);
	u8 tmp_div;

	pw_debug("A PWW/PAD: %s, wate = %wu (pawent_wate = %wu)\n", __func__,
		 wate, pawent_wate);

	if (!wate)
		wetuwn -EINVAW;

	tmp_div = pawent_wate / wate;
	if (tmp_div % 3 == 0) {
		apad_ck->qdaudio = tmp_div / 3;
		apad_ck->div = 3;
	} ewse {
		apad_ck->qdaudio = tmp_div / 2;
		apad_ck->div = 2;
	}

	wetuwn 0;
}

static int cwk_audio_pww_pmc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong pawent_wate)
{
	stwuct cwk_audio_pmc *apmc_ck = to_cwk_audio_pmc(hw);

	if (!wate)
		wetuwn -EINVAW;

	pw_debug("A PWW/PMC: %s, wate = %wu (pawent_wate = %wu)\n", __func__,
		 wate, pawent_wate);

	apmc_ck->qdpmc = pawent_wate / wate - 1;

	wetuwn 0;
}

static const stwuct cwk_ops audio_pww_fwac_ops = {
	.enabwe = cwk_audio_pww_fwac_enabwe,
	.disabwe = cwk_audio_pww_fwac_disabwe,
	.wecawc_wate = cwk_audio_pww_fwac_wecawc_wate,
	.detewmine_wate = cwk_audio_pww_fwac_detewmine_wate,
	.set_wate = cwk_audio_pww_fwac_set_wate,
};

static const stwuct cwk_ops audio_pww_pad_ops = {
	.enabwe = cwk_audio_pww_pad_enabwe,
	.disabwe = cwk_audio_pww_pad_disabwe,
	.wecawc_wate = cwk_audio_pww_pad_wecawc_wate,
	.wound_wate = cwk_audio_pww_pad_wound_wate,
	.set_wate = cwk_audio_pww_pad_set_wate,
};

static const stwuct cwk_ops audio_pww_pmc_ops = {
	.enabwe = cwk_audio_pww_pmc_enabwe,
	.disabwe = cwk_audio_pww_pmc_disabwe,
	.wecawc_wate = cwk_audio_pww_pmc_wecawc_wate,
	.wound_wate = cwk_audio_pww_pmc_wound_wate,
	.set_wate = cwk_audio_pww_pmc_set_wate,
};

stwuct cwk_hw * __init
at91_cwk_wegistew_audio_pww_fwac(stwuct wegmap *wegmap, const chaw *name,
				 const chaw *pawent_name)
{
	stwuct cwk_audio_fwac *fwac_ck;
	stwuct cwk_init_data init = {};
	int wet;

	fwac_ck = kzawwoc(sizeof(*fwac_ck), GFP_KEWNEW);
	if (!fwac_ck)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &audio_pww_fwac_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = CWK_SET_WATE_GATE;

	fwac_ck->hw.init = &init;
	fwac_ck->wegmap = wegmap;

	wet = cwk_hw_wegistew(NUWW, &fwac_ck->hw);
	if (wet) {
		kfwee(fwac_ck);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &fwac_ck->hw;
}

stwuct cwk_hw * __init
at91_cwk_wegistew_audio_pww_pad(stwuct wegmap *wegmap, const chaw *name,
				const chaw *pawent_name)
{
	stwuct cwk_audio_pad *apad_ck;
	stwuct cwk_init_data init;
	int wet;

	apad_ck = kzawwoc(sizeof(*apad_ck), GFP_KEWNEW);
	if (!apad_ck)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &audio_pww_pad_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE |
		CWK_SET_WATE_PAWENT;

	apad_ck->hw.init = &init;
	apad_ck->wegmap = wegmap;

	wet = cwk_hw_wegistew(NUWW, &apad_ck->hw);
	if (wet) {
		kfwee(apad_ck);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &apad_ck->hw;
}

stwuct cwk_hw * __init
at91_cwk_wegistew_audio_pww_pmc(stwuct wegmap *wegmap, const chaw *name,
				const chaw *pawent_name)
{
	stwuct cwk_audio_pmc *apmc_ck;
	stwuct cwk_init_data init;
	int wet;

	apmc_ck = kzawwoc(sizeof(*apmc_ck), GFP_KEWNEW);
	if (!apmc_ck)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &audio_pww_pmc_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE |
		CWK_SET_WATE_PAWENT;

	apmc_ck->hw.init = &init;
	apmc_ck->wegmap = wegmap;

	wet = cwk_hw_wegistew(NUWW, &apmc_ck->hw);
	if (wet) {
		kfwee(apmc_ck);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &apmc_ck->hw;
}
