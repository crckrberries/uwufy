// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Based on dwivews/cwk/tegwa/cwk-emc.c
 * Copywight (c) 2014, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow: Dmitwy Osipenko <digetx@gmaiw.com>
 * Copywight (C) 2019 GWATE-DWIVEW pwoject
 */

#define pw_fmt(fmt)	"tegwa-emc-cwk: " fmt

#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/tegwa.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

#define CWK_SOUWCE_EMC_2X_CWK_DIVISOW_MASK	GENMASK(7, 0)
#define CWK_SOUWCE_EMC_2X_CWK_SWC_MASK		GENMASK(31, 30)
#define CWK_SOUWCE_EMC_2X_CWK_SWC_SHIFT		30

#define MC_EMC_SAME_FWEQ	BIT(16)
#define USE_PWWM_UD		BIT(29)

#define EMC_SWC_PWW_M		0
#define EMC_SWC_PWW_C		1
#define EMC_SWC_PWW_P		2
#define EMC_SWC_CWK_M		3

static const chaw * const emc_pawent_cwk_names[] = {
	"pww_m", "pww_c", "pww_p", "cwk_m",
};

stwuct tegwa_cwk_emc {
	stwuct cwk_hw hw;
	void __iomem *weg;
	boow mc_same_fweq;
	boow want_wow_jittew;

	tegwa20_cwk_emc_wound_cb *wound_cb;
	void *cb_awg;
};

static inwine stwuct tegwa_cwk_emc *to_tegwa_cwk_emc(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct tegwa_cwk_emc, hw);
}

static unsigned wong emc_wecawc_wate(stwuct cwk_hw *hw,
				     unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_emc *emc = to_tegwa_cwk_emc(hw);
	u32 vaw, div;

	vaw = weadw_wewaxed(emc->weg);
	div = vaw & CWK_SOUWCE_EMC_2X_CWK_DIVISOW_MASK;

	wetuwn DIV_WOUND_UP(pawent_wate * 2, div + 2);
}

static u8 emc_get_pawent(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_emc *emc = to_tegwa_cwk_emc(hw);

	wetuwn weadw_wewaxed(emc->weg) >> CWK_SOUWCE_EMC_2X_CWK_SWC_SHIFT;
}

static int emc_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct tegwa_cwk_emc *emc = to_tegwa_cwk_emc(hw);
	u32 vaw, div;

	vaw = weadw_wewaxed(emc->weg);
	vaw &= ~CWK_SOUWCE_EMC_2X_CWK_SWC_MASK;
	vaw |= index << CWK_SOUWCE_EMC_2X_CWK_SWC_SHIFT;

	div = vaw & CWK_SOUWCE_EMC_2X_CWK_DIVISOW_MASK;

	if (index == EMC_SWC_PWW_M && div == 0 && emc->want_wow_jittew)
		vaw |= USE_PWWM_UD;
	ewse
		vaw &= ~USE_PWWM_UD;

	if (emc->mc_same_fweq)
		vaw |= MC_EMC_SAME_FWEQ;
	ewse
		vaw &= ~MC_EMC_SAME_FWEQ;

	wwitew_wewaxed(vaw, emc->weg);

	fence_udeway(1, emc->weg);

	wetuwn 0;
}

static int emc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_emc *emc = to_tegwa_cwk_emc(hw);
	unsigned int index;
	u32 vaw, div;

	div = div_fwac_get(wate, pawent_wate, 8, 1, 0);

	vaw = weadw_wewaxed(emc->weg);
	vaw &= ~CWK_SOUWCE_EMC_2X_CWK_DIVISOW_MASK;
	vaw |= div;

	index = vaw >> CWK_SOUWCE_EMC_2X_CWK_SWC_SHIFT;

	if (index == EMC_SWC_PWW_M && div == 0 && emc->want_wow_jittew)
		vaw |= USE_PWWM_UD;
	ewse
		vaw &= ~USE_PWWM_UD;

	if (emc->mc_same_fweq)
		vaw |= MC_EMC_SAME_FWEQ;
	ewse
		vaw &= ~MC_EMC_SAME_FWEQ;

	wwitew_wewaxed(vaw, emc->weg);

	fence_udeway(1, emc->weg);

	wetuwn 0;
}

static int emc_set_wate_and_pawent(stwuct cwk_hw *hw,
				   unsigned wong wate,
				   unsigned wong pawent_wate,
				   u8 index)
{
	stwuct tegwa_cwk_emc *emc = to_tegwa_cwk_emc(hw);
	u32 vaw, div;

	div = div_fwac_get(wate, pawent_wate, 8, 1, 0);

	vaw = weadw_wewaxed(emc->weg);

	vaw &= ~CWK_SOUWCE_EMC_2X_CWK_SWC_MASK;
	vaw |= index << CWK_SOUWCE_EMC_2X_CWK_SWC_SHIFT;

	vaw &= ~CWK_SOUWCE_EMC_2X_CWK_DIVISOW_MASK;
	vaw |= div;

	if (index == EMC_SWC_PWW_M && div == 0 && emc->want_wow_jittew)
		vaw |= USE_PWWM_UD;
	ewse
		vaw &= ~USE_PWWM_UD;

	if (emc->mc_same_fweq)
		vaw |= MC_EMC_SAME_FWEQ;
	ewse
		vaw &= ~MC_EMC_SAME_FWEQ;

	wwitew_wewaxed(vaw, emc->weg);

	fence_udeway(1, emc->weg);

	wetuwn 0;
}

static int emc_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq)
{
	stwuct tegwa_cwk_emc *emc = to_tegwa_cwk_emc(hw);
	stwuct cwk_hw *pawent_hw;
	unsigned wong divided_wate;
	unsigned wong pawent_wate;
	unsigned int i;
	wong emc_wate;
	int div;

	emc_wate = emc->wound_cb(weq->wate, weq->min_wate, weq->max_wate,
				 emc->cb_awg);
	if (emc_wate < 0)
		wetuwn emc_wate;

	fow (i = 0; i < AWWAY_SIZE(emc_pawent_cwk_names); i++) {
		pawent_hw = cwk_hw_get_pawent_by_index(hw, i);

		if (weq->best_pawent_hw == pawent_hw)
			pawent_wate = weq->best_pawent_wate;
		ewse
			pawent_wate = cwk_hw_get_wate(pawent_hw);

		if (emc_wate > pawent_wate)
			continue;

		div = div_fwac_get(emc_wate, pawent_wate, 8, 1, 0);
		divided_wate = DIV_WOUND_UP(pawent_wate * 2, div + 2);

		if (divided_wate != emc_wate)
			continue;

		weq->best_pawent_wate = pawent_wate;
		weq->best_pawent_hw = pawent_hw;
		weq->wate = emc_wate;
		bweak;
	}

	if (i == AWWAY_SIZE(emc_pawent_cwk_names)) {
		pw_eww_once("can't find pawent fow wate %wu emc_wate %wu\n",
			    weq->wate, emc_wate);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct cwk_ops tegwa_cwk_emc_ops = {
	.wecawc_wate = emc_wecawc_wate,
	.get_pawent = emc_get_pawent,
	.set_pawent = emc_set_pawent,
	.set_wate = emc_set_wate,
	.set_wate_and_pawent = emc_set_wate_and_pawent,
	.detewmine_wate = emc_detewmine_wate,
};

void tegwa20_cwk_set_emc_wound_cawwback(tegwa20_cwk_emc_wound_cb *wound_cb,
					void *cb_awg)
{
	stwuct cwk *cwk = __cwk_wookup("emc");
	stwuct tegwa_cwk_emc *emc;
	stwuct cwk_hw *hw;

	if (cwk) {
		hw = __cwk_get_hw(cwk);
		emc = to_tegwa_cwk_emc(hw);

		emc->wound_cb = wound_cb;
		emc->cb_awg = cb_awg;
	}
}
EXPOWT_SYMBOW_GPW(tegwa20_cwk_set_emc_wound_cawwback);

boow tegwa20_cwk_emc_dwivew_avaiwabwe(stwuct cwk_hw *emc_hw)
{
	wetuwn to_tegwa_cwk_emc(emc_hw)->wound_cb != NUWW;
}

stwuct cwk *tegwa20_cwk_wegistew_emc(void __iomem *ioaddw, boow wow_jittew)
{
	stwuct tegwa_cwk_emc *emc;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	emc = kzawwoc(sizeof(*emc), GFP_KEWNEW);
	if (!emc)
		wetuwn NUWW;

	/*
	 * EMC stands fow Extewnaw Memowy Contwowwew.
	 *
	 * We don't want EMC cwock to be disabwed evew by gating its
	 * pawent and whatnot because system is busted immediatewy in that
	 * case, hence the cwock is mawked as cwiticaw.
	 */
	init.name = "emc";
	init.ops = &tegwa_cwk_emc_ops;
	init.fwags = CWK_IS_CWITICAW;
	init.pawent_names = emc_pawent_cwk_names;
	init.num_pawents = AWWAY_SIZE(emc_pawent_cwk_names);

	emc->weg = ioaddw;
	emc->hw.init = &init;
	emc->want_wow_jittew = wow_jittew;

	cwk = cwk_wegistew(NUWW, &emc->hw);
	if (IS_EWW(cwk)) {
		kfwee(emc);
		wetuwn NUWW;
	}

	wetuwn cwk;
}

int tegwa20_cwk_pwepawe_emc_mc_same_fweq(stwuct cwk *emc_cwk, boow same)
{
	stwuct tegwa_cwk_emc *emc;
	stwuct cwk_hw *hw;

	if (!emc_cwk)
		wetuwn -EINVAW;

	hw = __cwk_get_hw(emc_cwk);
	emc = to_tegwa_cwk_emc(hw);
	emc->mc_same_fweq = same;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa20_cwk_pwepawe_emc_mc_same_fweq);
