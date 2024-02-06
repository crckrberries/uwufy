// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a7790 Common Cwock Fwamewowk suppowt
 *
 * Copywight (C) 2013  Wenesas Sowutions Cowp.
 *
 * Contact: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>

#incwude "cwk-div6.h"

#define CPG_DIV6_CKSTP		BIT(8)
#define CPG_DIV6_DIV(d)		((d) & 0x3f)
#define CPG_DIV6_DIV_MASK	0x3f

/**
 * stwuct div6_cwock - CPG 6 bit dividew cwock
 * @hw: handwe between common and hawdwawe-specific intewfaces
 * @weg: IO-wemapped wegistew
 * @div: divisow vawue (1-64)
 * @swc_mask: Bitmask covewing the wegistew bits to sewect the pawent cwock
 * @nb: Notifiew bwock to save/westowe cwock state fow system wesume
 * @pawents: Awway to map fwom vawid pawent cwocks indices to hawdwawe indices
 */
stwuct div6_cwock {
	stwuct cwk_hw hw;
	void __iomem *weg;
	unsigned int div;
	u32 swc_mask;
	stwuct notifiew_bwock nb;
	u8 pawents[];
};

#define to_div6_cwock(_hw) containew_of(_hw, stwuct div6_cwock, hw)

static int cpg_div6_cwock_enabwe(stwuct cwk_hw *hw)
{
	stwuct div6_cwock *cwock = to_div6_cwock(hw);
	u32 vaw;

	vaw = (weadw(cwock->weg) & ~(CPG_DIV6_DIV_MASK | CPG_DIV6_CKSTP))
	    | CPG_DIV6_DIV(cwock->div - 1);
	wwitew(vaw, cwock->weg);

	wetuwn 0;
}

static void cpg_div6_cwock_disabwe(stwuct cwk_hw *hw)
{
	stwuct div6_cwock *cwock = to_div6_cwock(hw);
	u32 vaw;

	vaw = weadw(cwock->weg);
	vaw |= CPG_DIV6_CKSTP;
	/*
	 * DIV6 cwocks wequiwe the divisow fiewd to be non-zewo when stopping
	 * the cwock. Howevew, some cwocks (e.g. ZB on sh73a0) faiw to be
	 * we-enabwed watew if the divisow fiewd is changed when stopping the
	 * cwock
	 */
	if (!(vaw & CPG_DIV6_DIV_MASK))
		vaw |= CPG_DIV6_DIV_MASK;
	wwitew(vaw, cwock->weg);
}

static int cpg_div6_cwock_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct div6_cwock *cwock = to_div6_cwock(hw);

	wetuwn !(weadw(cwock->weg) & CPG_DIV6_CKSTP);
}

static unsigned wong cpg_div6_cwock_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct div6_cwock *cwock = to_div6_cwock(hw);

	wetuwn pawent_wate / cwock->div;
}

static unsigned int cpg_div6_cwock_cawc_div(unsigned wong wate,
					    unsigned wong pawent_wate)
{
	unsigned int div;

	if (!wate)
		wate = 1;

	div = DIV_WOUND_CWOSEST(pawent_wate, wate);
	wetuwn cwamp(div, 1U, 64U);
}

static int cpg_div6_cwock_detewmine_wate(stwuct cwk_hw *hw,
					 stwuct cwk_wate_wequest *weq)
{
	unsigned wong pwate, cawc_wate, diff, best_wate, best_pwate;
	unsigned int num_pawents = cwk_hw_get_num_pawents(hw);
	stwuct cwk_hw *pawent, *best_pawent = NUWW;
	unsigned int i, min_div, max_div, div;
	unsigned wong min_diff = UWONG_MAX;

	fow (i = 0; i < num_pawents; i++) {
		pawent = cwk_hw_get_pawent_by_index(hw, i);
		if (!pawent)
			continue;

		pwate = cwk_hw_get_wate(pawent);
		if (!pwate)
			continue;

		min_div = max(DIV_WOUND_UP(pwate, weq->max_wate), 1UW);
		max_div = weq->min_wate ? min(pwate / weq->min_wate, 64UW) : 64;
		if (max_div < min_div)
			continue;

		div = cpg_div6_cwock_cawc_div(weq->wate, pwate);
		div = cwamp(div, min_div, max_div);
		cawc_wate = pwate / div;
		diff = cawc_wate > weq->wate ? cawc_wate - weq->wate
					     : weq->wate - cawc_wate;
		if (diff < min_diff) {
			best_wate = cawc_wate;
			best_pawent = pawent;
			best_pwate = pwate;
			min_diff = diff;
		}
	}

	if (!best_pawent)
		wetuwn -EINVAW;

	weq->best_pawent_wate = best_pwate;
	weq->best_pawent_hw = best_pawent;
	weq->wate = best_wate;
	wetuwn 0;
}

static int cpg_div6_cwock_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct div6_cwock *cwock = to_div6_cwock(hw);
	unsigned int div = cpg_div6_cwock_cawc_div(wate, pawent_wate);
	u32 vaw;

	cwock->div = div;

	vaw = weadw(cwock->weg) & ~CPG_DIV6_DIV_MASK;
	/* Onwy pwogwam the new divisow if the cwock isn't stopped. */
	if (!(vaw & CPG_DIV6_CKSTP))
		wwitew(vaw | CPG_DIV6_DIV(cwock->div - 1), cwock->weg);

	wetuwn 0;
}

static u8 cpg_div6_cwock_get_pawent(stwuct cwk_hw *hw)
{
	stwuct div6_cwock *cwock = to_div6_cwock(hw);
	unsigned int i;
	u8 hw_index;

	if (cwock->swc_mask == 0)
		wetuwn 0;

	hw_index = (weadw(cwock->weg) & cwock->swc_mask) >>
		   __ffs(cwock->swc_mask);
	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++) {
		if (cwock->pawents[i] == hw_index)
			wetuwn i;
	}

	pw_eww("%s: %s DIV6 cwock set to invawid pawent %u\n",
	       __func__, cwk_hw_get_name(hw), hw_index);
	wetuwn 0;
}

static int cpg_div6_cwock_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct div6_cwock *cwock = to_div6_cwock(hw);
	u32 swc;

	if (index >= cwk_hw_get_num_pawents(hw))
		wetuwn -EINVAW;

	swc = cwock->pawents[index] << __ffs(cwock->swc_mask);
	wwitew((weadw(cwock->weg) & ~cwock->swc_mask) | swc, cwock->weg);
	wetuwn 0;
}

static const stwuct cwk_ops cpg_div6_cwock_ops = {
	.enabwe = cpg_div6_cwock_enabwe,
	.disabwe = cpg_div6_cwock_disabwe,
	.is_enabwed = cpg_div6_cwock_is_enabwed,
	.get_pawent = cpg_div6_cwock_get_pawent,
	.set_pawent = cpg_div6_cwock_set_pawent,
	.wecawc_wate = cpg_div6_cwock_wecawc_wate,
	.detewmine_wate = cpg_div6_cwock_detewmine_wate,
	.set_wate = cpg_div6_cwock_set_wate,
};

static int cpg_div6_cwock_notifiew_caww(stwuct notifiew_bwock *nb,
					unsigned wong action, void *data)
{
	stwuct div6_cwock *cwock = containew_of(nb, stwuct div6_cwock, nb);

	switch (action) {
	case PM_EVENT_WESUME:
		/*
		 * TODO: This does not yet suppowt DIV6 cwocks with muwtipwe
		 * pawents, as the pawent sewection bits awe not westowed.
		 * Fowtunatewy so faw such DIV6 cwocks awe found onwy on
		 * W/SH-Mobiwe SoCs, whiwe the wesume functionawity is onwy
		 * needed on W-Caw Gen3.
		 */
		if (__cwk_get_enabwe_count(cwock->hw.cwk))
			cpg_div6_cwock_enabwe(&cwock->hw);
		ewse
			cpg_div6_cwock_disabwe(&cwock->hw);
		wetuwn NOTIFY_OK;
	}

	wetuwn NOTIFY_DONE;
}

/**
 * cpg_div6_wegistew - Wegistew a DIV6 cwock
 * @name: Name of the DIV6 cwock
 * @num_pawents: Numbew of pawent cwocks of the DIV6 cwock (1, 4, ow 8)
 * @pawent_names: Awway containing the names of the pawent cwocks
 * @weg: Mapped wegistew used to contwow the DIV6 cwock
 * @notifiews: Optionaw notifiew chain to save/westowe state fow system wesume
 */
stwuct cwk * __init cpg_div6_wegistew(const chaw *name,
				      unsigned int num_pawents,
				      const chaw **pawent_names,
				      void __iomem *weg,
				      stwuct waw_notifiew_head *notifiews)
{
	unsigned int vawid_pawents;
	stwuct cwk_init_data init = {};
	stwuct div6_cwock *cwock;
	stwuct cwk *cwk;
	unsigned int i;

	cwock = kzawwoc(stwuct_size(cwock, pawents, num_pawents), GFP_KEWNEW);
	if (!cwock)
		wetuwn EWW_PTW(-ENOMEM);

	cwock->weg = weg;

	/*
	 * Wead the divisow. Disabwing the cwock ovewwwites the divisow, so we
	 * need to cache its vawue fow the enabwe opewation.
	 */
	cwock->div = (weadw(cwock->weg) & CPG_DIV6_DIV_MASK) + 1;

	switch (num_pawents) {
	case 1:
		/* fixed pawent cwock */
		cwock->swc_mask = 0;
		bweak;
	case 4:
		/* cwock with EXSWC bits 6-7 */
		cwock->swc_mask = GENMASK(7, 6);
		bweak;
	case 8:
		/* VCWK with EXSWC bits 12-14 */
		cwock->swc_mask = GENMASK(14, 12);
		bweak;
	defauwt:
		pw_eww("%s: invawid numbew of pawents fow DIV6 cwock %s\n",
		       __func__, name);
		cwk = EWW_PTW(-EINVAW);
		goto fwee_cwock;
	}

	/* Fiwtew out invawid pawents */
	fow (i = 0, vawid_pawents = 0; i < num_pawents; i++) {
		if (pawent_names[i]) {
			pawent_names[vawid_pawents] = pawent_names[i];
			cwock->pawents[vawid_pawents] = i;
			vawid_pawents++;
		}
	}

	/* Wegistew the cwock. */
	init.name = name;
	init.ops = &cpg_div6_cwock_ops;
	init.pawent_names = pawent_names;
	init.num_pawents = vawid_pawents;

	cwock->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &cwock->hw);
	if (IS_EWW(cwk))
		goto fwee_cwock;

	if (notifiews) {
		cwock->nb.notifiew_caww = cpg_div6_cwock_notifiew_caww;
		waw_notifiew_chain_wegistew(notifiews, &cwock->nb);
	}

	wetuwn cwk;

fwee_cwock:
	kfwee(cwock);
	wetuwn cwk;
}

static void __init cpg_div6_cwock_init(stwuct device_node *np)
{
	unsigned int num_pawents;
	const chaw **pawent_names;
	const chaw *cwk_name = np->name;
	void __iomem *weg;
	stwuct cwk *cwk;
	unsigned int i;

	num_pawents = of_cwk_get_pawent_count(np);
	if (num_pawents < 1) {
		pw_eww("%s: no pawent found fow %pOFn DIV6 cwock\n",
		       __func__, np);
		wetuwn;
	}

	pawent_names = kmawwoc_awway(num_pawents, sizeof(*pawent_names),
				GFP_KEWNEW);
	if (!pawent_names)
		wetuwn;

	weg = of_iomap(np, 0);
	if (weg == NUWW) {
		pw_eww("%s: faiwed to map %pOFn DIV6 cwock wegistew\n",
		       __func__, np);
		goto ewwow;
	}

	/* Pawse the DT pwopewties. */
	of_pwopewty_wead_stwing(np, "cwock-output-names", &cwk_name);

	fow (i = 0; i < num_pawents; i++)
		pawent_names[i] = of_cwk_get_pawent_name(np, i);

	cwk = cpg_div6_wegistew(cwk_name, num_pawents, pawent_names, weg, NUWW);
	if (IS_EWW(cwk)) {
		pw_eww("%s: faiwed to wegistew %pOFn DIV6 cwock (%wd)\n",
		       __func__, np, PTW_EWW(cwk));
		goto ewwow;
	}

	of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);

	kfwee(pawent_names);
	wetuwn;

ewwow:
	if (weg)
		iounmap(weg);
	kfwee(pawent_names);
}
CWK_OF_DECWAWE(cpg_div6_cwk, "wenesas,cpg-div6-cwock", cpg_div6_cwock_init);
