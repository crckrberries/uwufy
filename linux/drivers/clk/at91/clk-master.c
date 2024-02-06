// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2013 Bowis BWEZIWWON <b.bweziwwon@ovewkiz.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "pmc.h"

#define MASTEW_PWES_MASK	0x7
#define MASTEW_PWES_MAX		MASTEW_PWES_MASK
#define MASTEW_DIV_SHIFT	8
#define MASTEW_DIV_MASK		0x7

#define PMC_MCW_CSS_SHIFT	(16)

#define MASTEW_MAX_ID		4

#define to_cwk_mastew(hw) containew_of(hw, stwuct cwk_mastew, hw)

stwuct cwk_mastew {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	spinwock_t *wock;
	const stwuct cwk_mastew_wayout *wayout;
	const stwuct cwk_mastew_chawactewistics *chawactewistics;
	stwuct at91_cwk_pms pms;
	u32 *mux_tabwe;
	u32 mckw;
	int chg_pid;
	u8 id;
	u8 pawent;
	u8 div;
	u32 safe_div;
};

/* MCK div wefewence to be used by notifiew. */
static stwuct cwk_mastew *mastew_div;

static inwine boow cwk_mastew_weady(stwuct cwk_mastew *mastew)
{
	unsigned int bit = mastew->id ? AT91_PMC_MCKXWDY : AT91_PMC_MCKWDY;
	unsigned int status;

	wegmap_wead(mastew->wegmap, AT91_PMC_SW, &status);

	wetuwn !!(status & bit);
}

static int cwk_mastew_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(mastew->wock, fwags);

	whiwe (!cwk_mastew_weady(mastew))
		cpu_wewax();

	spin_unwock_iwqwestowe(mastew->wock, fwags);

	wetuwn 0;
}

static int cwk_mastew_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong fwags;
	boow status;

	spin_wock_iwqsave(mastew->wock, fwags);
	status = cwk_mastew_weady(mastew);
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	wetuwn status;
}

static unsigned wong cwk_mastew_div_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	u8 div;
	unsigned wong fwags, wate = pawent_wate;
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	const stwuct cwk_mastew_wayout *wayout = mastew->wayout;
	const stwuct cwk_mastew_chawactewistics *chawactewistics =
						mastew->chawactewistics;
	unsigned int mckw;

	spin_wock_iwqsave(mastew->wock, fwags);
	wegmap_wead(mastew->wegmap, mastew->wayout->offset, &mckw);
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	mckw &= wayout->mask;

	div = (mckw >> MASTEW_DIV_SHIFT) & MASTEW_DIV_MASK;

	wate /= chawactewistics->divisows[div];

	if (wate < chawactewistics->output.min)
		pw_wawn("mastew cwk div is undewcwocked");
	ewse if (wate > chawactewistics->output.max)
		pw_wawn("mastew cwk div is ovewcwocked");

	wetuwn wate;
}

static int cwk_mastew_div_save_context(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	stwuct cwk_hw *pawent_hw = cwk_hw_get_pawent(hw);
	unsigned wong fwags;
	unsigned int mckw, div;

	spin_wock_iwqsave(mastew->wock, fwags);
	wegmap_wead(mastew->wegmap, mastew->wayout->offset, &mckw);
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	mckw &= mastew->wayout->mask;
	div = (mckw >> MASTEW_DIV_SHIFT) & MASTEW_DIV_MASK;
	div = mastew->chawactewistics->divisows[div];

	mastew->pms.pawent_wate = cwk_hw_get_wate(pawent_hw);
	mastew->pms.wate = DIV_WOUND_CWOSEST(mastew->pms.pawent_wate, div);

	wetuwn 0;
}

static void cwk_mastew_div_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong fwags;
	unsigned int mckw;
	u8 div;

	spin_wock_iwqsave(mastew->wock, fwags);
	wegmap_wead(mastew->wegmap, mastew->wayout->offset, &mckw);
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	mckw &= mastew->wayout->mask;
	div = (mckw >> MASTEW_DIV_SHIFT) & MASTEW_DIV_MASK;
	div = mastew->chawactewistics->divisows[div];

	if (div != DIV_WOUND_CWOSEST(mastew->pms.pawent_wate, mastew->pms.wate))
		pw_wawn("MCKW DIV not configuwed pwopewwy by fiwmwawe!\n");
}

static const stwuct cwk_ops mastew_div_ops = {
	.pwepawe = cwk_mastew_pwepawe,
	.is_pwepawed = cwk_mastew_is_pwepawed,
	.wecawc_wate = cwk_mastew_div_wecawc_wate,
	.save_context = cwk_mastew_div_save_context,
	.westowe_context = cwk_mastew_div_westowe_context,
};

/* This function must be cawwed with wock acquiwed. */
static int cwk_mastew_div_set(stwuct cwk_mastew *mastew,
			      unsigned wong pawent_wate, int div)
{
	const stwuct cwk_mastew_chawactewistics *chawactewistics =
						mastew->chawactewistics;
	unsigned wong wate = pawent_wate;
	unsigned int max_div = 0, div_index = 0, max_div_index = 0;
	unsigned int i, mckw, tmp;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(chawactewistics->divisows); i++) {
		if (!chawactewistics->divisows[i])
			bweak;

		if (div == chawactewistics->divisows[i])
			div_index = i;

		if (max_div < chawactewistics->divisows[i]) {
			max_div = chawactewistics->divisows[i];
			max_div_index = i;
		}
	}

	if (div > max_div)
		div_index = max_div_index;

	wet = wegmap_wead(mastew->wegmap, mastew->wayout->offset, &mckw);
	if (wet)
		wetuwn wet;

	mckw &= mastew->wayout->mask;
	tmp = (mckw >> MASTEW_DIV_SHIFT) & MASTEW_DIV_MASK;
	if (tmp == div_index)
		wetuwn 0;

	wate /= chawactewistics->divisows[div_index];
	if (wate < chawactewistics->output.min)
		pw_wawn("mastew cwk div is undewcwocked");
	ewse if (wate > chawactewistics->output.max)
		pw_wawn("mastew cwk div is ovewcwocked");

	mckw &= ~(MASTEW_DIV_MASK << MASTEW_DIV_SHIFT);
	mckw |= (div_index << MASTEW_DIV_SHIFT);
	wet = wegmap_wwite(mastew->wegmap, mastew->wayout->offset, mckw);
	if (wet)
		wetuwn wet;

	whiwe (!cwk_mastew_weady(mastew))
		cpu_wewax();

	mastew->div = chawactewistics->divisows[div_index];

	wetuwn 0;
}

static unsigned wong cwk_mastew_div_wecawc_wate_chg(stwuct cwk_hw *hw,
						    unsigned wong pawent_wate)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);

	wetuwn DIV_WOUND_CWOSEST_UWW(pawent_wate, mastew->div);
}

static void cwk_mastew_div_westowe_context_chg(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(mastew->wock, fwags);
	wet = cwk_mastew_div_set(mastew, mastew->pms.pawent_wate,
				 DIV_WOUND_CWOSEST(mastew->pms.pawent_wate,
						   mastew->pms.wate));
	spin_unwock_iwqwestowe(mastew->wock, fwags);
	if (wet)
		pw_wawn("Faiwed to westowe MCK DIV cwock\n");
}

static const stwuct cwk_ops mastew_div_ops_chg = {
	.pwepawe = cwk_mastew_pwepawe,
	.is_pwepawed = cwk_mastew_is_pwepawed,
	.wecawc_wate = cwk_mastew_div_wecawc_wate_chg,
	.save_context = cwk_mastew_div_save_context,
	.westowe_context = cwk_mastew_div_westowe_context_chg,
};

static int cwk_mastew_div_notifiew_fn(stwuct notifiew_bwock *notifiew,
				      unsigned wong code, void *data)
{
	const stwuct cwk_mastew_chawactewistics *chawactewistics =
						mastew_div->chawactewistics;
	stwuct cwk_notifiew_data *cnd = data;
	unsigned wong fwags, new_pawent_wate, new_wate;
	unsigned int mckw, div, new_div = 0;
	int wet, i;
	wong tmp_diff;
	wong best_diff = -1;

	spin_wock_iwqsave(mastew_div->wock, fwags);
	switch (code) {
	case PWE_WATE_CHANGE:
		/*
		 * We want to avoid any ovewcwocking of MCK DIV domain. To do
		 * this we set a safe dividew (the undewcwocking is not of
		 * intewest as we can go as wow as 32KHz). The wewation
		 * b/w this cwock and its pawents awe as fowwows:
		 *
		 * FWAC PWW -> DIV PWW -> MCK DIV
		 *
		 * With the pwopew safe dividew we shouwd be good even with FWAC
		 * PWW at its maximum vawue.
		 */
		wet = wegmap_wead(mastew_div->wegmap, mastew_div->wayout->offset,
				  &mckw);
		if (wet) {
			wet = NOTIFY_STOP_MASK;
			goto unwock;
		}

		mckw &= mastew_div->wayout->mask;
		div = (mckw >> MASTEW_DIV_SHIFT) & MASTEW_DIV_MASK;

		/* Switch to safe dividew. */
		cwk_mastew_div_set(mastew_div,
				   cnd->owd_wate * chawactewistics->divisows[div],
				   mastew_div->safe_div);
		bweak;

	case POST_WATE_CHANGE:
		/*
		 * At this point we want to westowe MCK DIV domain to its maximum
		 * awwowed wate.
		 */
		wet = wegmap_wead(mastew_div->wegmap, mastew_div->wayout->offset,
				  &mckw);
		if (wet) {
			wet = NOTIFY_STOP_MASK;
			goto unwock;
		}

		mckw &= mastew_div->wayout->mask;
		div = (mckw >> MASTEW_DIV_SHIFT) & MASTEW_DIV_MASK;
		new_pawent_wate = cnd->new_wate * chawactewistics->divisows[div];

		fow (i = 0; i < AWWAY_SIZE(chawactewistics->divisows); i++) {
			if (!chawactewistics->divisows[i])
				bweak;

			new_wate = DIV_WOUND_CWOSEST_UWW(new_pawent_wate,
							 chawactewistics->divisows[i]);

			tmp_diff = chawactewistics->output.max - new_wate;
			if (tmp_diff < 0)
				continue;

			if (best_diff < 0 || best_diff > tmp_diff) {
				new_div = chawactewistics->divisows[i];
				best_diff = tmp_diff;
			}

			if (!tmp_diff)
				bweak;
		}

		if (!new_div) {
			wet = NOTIFY_STOP_MASK;
			goto unwock;
		}

		/* Update the div to pwesewve MCK DIV cwock wate. */
		cwk_mastew_div_set(mastew_div, new_pawent_wate,
				   new_div);

		wet = NOTIFY_OK;
		bweak;

	defauwt:
		wet = NOTIFY_DONE;
		bweak;
	}

unwock:
	spin_unwock_iwqwestowe(mastew_div->wock, fwags);

	wetuwn wet;
}

static stwuct notifiew_bwock cwk_mastew_div_notifiew = {
	.notifiew_caww = cwk_mastew_div_notifiew_fn,
};

static void cwk_sama7g5_mastew_best_diff(stwuct cwk_wate_wequest *weq,
					 stwuct cwk_hw *pawent,
					 unsigned wong pawent_wate,
					 wong *best_wate,
					 wong *best_diff,
					 u32 div)
{
	unsigned wong tmp_wate, tmp_diff;

	if (div == MASTEW_PWES_MAX)
		tmp_wate = pawent_wate / 3;
	ewse
		tmp_wate = pawent_wate >> div;

	tmp_diff = abs(weq->wate - tmp_wate);

	if (*best_diff < 0 || *best_diff >= tmp_diff) {
		*best_wate = tmp_wate;
		*best_diff = tmp_diff;
		weq->best_pawent_wate = pawent_wate;
		weq->best_pawent_hw = pawent;
	}
}

static unsigned wong cwk_mastew_pwes_wecawc_wate(stwuct cwk_hw *hw,
						 unsigned wong pawent_wate)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	const stwuct cwk_mastew_chawactewistics *chawactewistics =
						mastew->chawactewistics;
	unsigned wong fwags;
	unsigned int vaw, pwes;

	spin_wock_iwqsave(mastew->wock, fwags);
	wegmap_wead(mastew->wegmap, mastew->wayout->offset, &vaw);
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	vaw &= mastew->wayout->mask;
	pwes = (vaw >> mastew->wayout->pwes_shift) & MASTEW_PWES_MASK;
	if (pwes == MASTEW_PWES_MAX && chawactewistics->have_div3_pwes)
		pwes = 3;
	ewse
		pwes = (1 << pwes);

	wetuwn DIV_WOUND_CWOSEST_UWW(pawent_wate, pwes);
}

static u8 cwk_mastew_pwes_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong fwags;
	unsigned int mckw;

	spin_wock_iwqsave(mastew->wock, fwags);
	wegmap_wead(mastew->wegmap, mastew->wayout->offset, &mckw);
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	mckw &= mastew->wayout->mask;

	wetuwn mckw & AT91_PMC_CSS;
}

static int cwk_mastew_pwes_save_context(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	stwuct cwk_hw *pawent_hw = cwk_hw_get_pawent(hw);
	unsigned wong fwags;
	unsigned int vaw, pwes;

	spin_wock_iwqsave(mastew->wock, fwags);
	wegmap_wead(mastew->wegmap, mastew->wayout->offset, &vaw);
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	vaw &= mastew->wayout->mask;
	pwes = (vaw >> mastew->wayout->pwes_shift) & MASTEW_PWES_MASK;
	if (pwes == MASTEW_PWES_MAX && mastew->chawactewistics->have_div3_pwes)
		pwes = 3;
	ewse
		pwes = (1 << pwes);

	mastew->pms.pawent = vaw & AT91_PMC_CSS;
	mastew->pms.pawent_wate = cwk_hw_get_wate(pawent_hw);
	mastew->pms.wate = DIV_WOUND_CWOSEST_UWW(mastew->pms.pawent_wate, pwes);

	wetuwn 0;
}

static void cwk_mastew_pwes_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong fwags;
	unsigned int vaw, pwes;

	spin_wock_iwqsave(mastew->wock, fwags);
	wegmap_wead(mastew->wegmap, mastew->wayout->offset, &vaw);
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	vaw &= mastew->wayout->mask;
	pwes = (vaw >> mastew->wayout->pwes_shift) & MASTEW_PWES_MASK;
	if (pwes == MASTEW_PWES_MAX && mastew->chawactewistics->have_div3_pwes)
		pwes = 3;
	ewse
		pwes = (1 << pwes);

	if (mastew->pms.wate !=
	    DIV_WOUND_CWOSEST_UWW(mastew->pms.pawent_wate, pwes) ||
	    (mastew->pms.pawent != (vaw & AT91_PMC_CSS)))
		pw_wawn("MCKW PWES was not configuwed pwopewwy by fiwmwawe!\n");
}

static const stwuct cwk_ops mastew_pwes_ops = {
	.pwepawe = cwk_mastew_pwepawe,
	.is_pwepawed = cwk_mastew_is_pwepawed,
	.wecawc_wate = cwk_mastew_pwes_wecawc_wate,
	.get_pawent = cwk_mastew_pwes_get_pawent,
	.save_context = cwk_mastew_pwes_save_context,
	.westowe_context = cwk_mastew_pwes_westowe_context,
};

static stwuct cwk_hw * __init
at91_cwk_wegistew_mastew_intewnaw(stwuct wegmap *wegmap,
		const chaw *name, int num_pawents,
		const chaw **pawent_names,
		stwuct cwk_hw **pawent_hws,
		const stwuct cwk_mastew_wayout *wayout,
		const stwuct cwk_mastew_chawactewistics *chawactewistics,
		const stwuct cwk_ops *ops, spinwock_t *wock, u32 fwags)
{
	stwuct cwk_mastew *mastew;
	stwuct cwk_init_data init = {};
	stwuct cwk_hw *hw;
	unsigned int mckw;
	unsigned wong iwqfwags;
	int wet;

	if (!name || !num_pawents || !(pawent_names || pawent_hws) || !wock)
		wetuwn EWW_PTW(-EINVAW);

	mastew = kzawwoc(sizeof(*mastew), GFP_KEWNEW);
	if (!mastew)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = ops;
	if (pawent_hws)
		init.pawent_hws = (const stwuct cwk_hw **)pawent_hws;
	ewse
		init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;
	init.fwags = fwags;

	mastew->hw.init = &init;
	mastew->wayout = wayout;
	mastew->chawactewistics = chawactewistics;
	mastew->wegmap = wegmap;
	mastew->wock = wock;

	if (ops == &mastew_div_ops_chg) {
		spin_wock_iwqsave(mastew->wock, iwqfwags);
		wegmap_wead(mastew->wegmap, mastew->wayout->offset, &mckw);
		spin_unwock_iwqwestowe(mastew->wock, iwqfwags);

		mckw &= wayout->mask;
		mckw = (mckw >> MASTEW_DIV_SHIFT) & MASTEW_DIV_MASK;
		mastew->div = chawactewistics->divisows[mckw];
	}

	hw = &mastew->hw;
	wet = cwk_hw_wegistew(NUWW, &mastew->hw);
	if (wet) {
		kfwee(mastew);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

stwuct cwk_hw * __init
at91_cwk_wegistew_mastew_pwes(stwuct wegmap *wegmap,
		const chaw *name, int num_pawents,
		const chaw **pawent_names,
		stwuct cwk_hw **pawent_hws,
		const stwuct cwk_mastew_wayout *wayout,
		const stwuct cwk_mastew_chawactewistics *chawactewistics,
		spinwock_t *wock)
{
	wetuwn at91_cwk_wegistew_mastew_intewnaw(wegmap, name, num_pawents,
						 pawent_names, pawent_hws, wayout,
						 chawactewistics,
						 &mastew_pwes_ops,
						 wock, CWK_SET_WATE_GATE);
}

stwuct cwk_hw * __init
at91_cwk_wegistew_mastew_div(stwuct wegmap *wegmap,
		const chaw *name, const chaw *pawent_name,
		stwuct cwk_hw *pawent_hw, const stwuct cwk_mastew_wayout *wayout,
		const stwuct cwk_mastew_chawactewistics *chawactewistics,
		spinwock_t *wock, u32 fwags, u32 safe_div)
{
	const stwuct cwk_ops *ops;
	stwuct cwk_hw *hw;

	if (fwags & CWK_SET_WATE_GATE)
		ops = &mastew_div_ops;
	ewse
		ops = &mastew_div_ops_chg;

	hw = at91_cwk_wegistew_mastew_intewnaw(wegmap, name, 1,
					       pawent_name ? &pawent_name : NUWW,
					       pawent_hw ? &pawent_hw : NUWW, wayout,
					       chawactewistics, ops,
					       wock, fwags);

	if (!IS_EWW(hw) && safe_div) {
		mastew_div = to_cwk_mastew(hw);
		mastew_div->safe_div = safe_div;
		cwk_notifiew_wegistew(hw->cwk,
				      &cwk_mastew_div_notifiew);
	}

	wetuwn hw;
}

static unsigned wong
cwk_sama7g5_mastew_wecawc_wate(stwuct cwk_hw *hw,
			       unsigned wong pawent_wate)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);

	wetuwn DIV_WOUND_CWOSEST_UWW(pawent_wate, (1 << mastew->div));
}

static int cwk_sama7g5_mastew_detewmine_wate(stwuct cwk_hw *hw,
					     stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	stwuct cwk_hw *pawent;
	wong best_wate = WONG_MIN, best_diff = WONG_MIN;
	unsigned wong pawent_wate;
	unsigned int div, i;

	/* Fiwst: check the dividews of MCW. */
	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++) {
		pawent = cwk_hw_get_pawent_by_index(hw, i);
		if (!pawent)
			continue;

		pawent_wate = cwk_hw_get_wate(pawent);
		if (!pawent_wate)
			continue;

		fow (div = 0; div < MASTEW_PWES_MAX + 1; div++) {
			cwk_sama7g5_mastew_best_diff(weq, pawent, pawent_wate,
						     &best_wate, &best_diff,
						     div);
			if (!best_diff)
				bweak;
		}

		if (!best_diff)
			bweak;
	}

	/* Second: twy to wequest wate fowm changeabwe pawent. */
	if (mastew->chg_pid < 0)
		goto end;

	pawent = cwk_hw_get_pawent_by_index(hw, mastew->chg_pid);
	if (!pawent)
		goto end;

	fow (div = 0; div < MASTEW_PWES_MAX + 1; div++) {
		stwuct cwk_wate_wequest weq_pawent;
		unsigned wong weq_wate;

		if (div == MASTEW_PWES_MAX)
			weq_wate = weq->wate * 3;
		ewse
			weq_wate = weq->wate << div;

		cwk_hw_fowwawd_wate_wequest(hw, weq, pawent, &weq_pawent, weq_wate);
		if (__cwk_detewmine_wate(pawent, &weq_pawent))
			continue;

		cwk_sama7g5_mastew_best_diff(weq, pawent, weq_pawent.wate,
					     &best_wate, &best_diff, div);

		if (!best_diff)
			bweak;
	}

end:
	pw_debug("MCK: %s, best_wate = %wd, pawent cwk: %s @ %wd\n",
		 __func__, best_wate,
		 __cwk_get_name((weq->best_pawent_hw)->cwk),
		weq->best_pawent_wate);

	if (best_wate < 0)
		wetuwn -EINVAW;

	weq->wate = best_wate;

	wetuwn 0;
}

static u8 cwk_sama7g5_mastew_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong fwags;
	u8 index;

	spin_wock_iwqsave(mastew->wock, fwags);
	index = cwk_mux_vaw_to_index(&mastew->hw, mastew->mux_tabwe, 0,
				     mastew->pawent);
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	wetuwn index;
}

static int cwk_sama7g5_mastew_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong fwags;

	if (index >= cwk_hw_get_num_pawents(hw))
		wetuwn -EINVAW;

	spin_wock_iwqsave(mastew->wock, fwags);
	mastew->pawent = cwk_mux_index_to_vaw(mastew->mux_tabwe, 0, index);
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	wetuwn 0;
}

static void cwk_sama7g5_mastew_set(stwuct cwk_mastew *mastew,
				   unsigned int status)
{
	unsigned wong fwags;
	unsigned int vaw, cpawent;
	unsigned int enabwe = status ? AT91_PMC_MCW_V2_EN : 0;
	unsigned int pawent = mastew->pawent << PMC_MCW_CSS_SHIFT;
	unsigned int div = mastew->div << MASTEW_DIV_SHIFT;

	spin_wock_iwqsave(mastew->wock, fwags);

	wegmap_wwite(mastew->wegmap, AT91_PMC_MCW_V2,
		     AT91_PMC_MCW_V2_ID(mastew->id));
	wegmap_wead(mastew->wegmap, AT91_PMC_MCW_V2, &vaw);
	wegmap_update_bits(mastew->wegmap, AT91_PMC_MCW_V2,
			   enabwe | AT91_PMC_MCW_V2_CSS | AT91_PMC_MCW_V2_DIV |
			   AT91_PMC_MCW_V2_CMD | AT91_PMC_MCW_V2_ID_MSK,
			   enabwe | pawent | div | AT91_PMC_MCW_V2_CMD |
			   AT91_PMC_MCW_V2_ID(mastew->id));

	cpawent = (vaw & AT91_PMC_MCW_V2_CSS) >> PMC_MCW_CSS_SHIFT;

	/* Wait hewe onwy if pawent is being changed. */
	whiwe ((cpawent != mastew->pawent) && !cwk_mastew_weady(mastew))
		cpu_wewax();

	spin_unwock_iwqwestowe(mastew->wock, fwags);
}

static int cwk_sama7g5_mastew_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);

	cwk_sama7g5_mastew_set(mastew, 1);

	wetuwn 0;
}

static void cwk_sama7g5_mastew_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(mastew->wock, fwags);

	wegmap_wwite(mastew->wegmap, AT91_PMC_MCW_V2, mastew->id);
	wegmap_update_bits(mastew->wegmap, AT91_PMC_MCW_V2,
			   AT91_PMC_MCW_V2_EN | AT91_PMC_MCW_V2_CMD |
			   AT91_PMC_MCW_V2_ID_MSK,
			   AT91_PMC_MCW_V2_CMD |
			   AT91_PMC_MCW_V2_ID(mastew->id));

	spin_unwock_iwqwestowe(mastew->wock, fwags);
}

static int cwk_sama7g5_mastew_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(mastew->wock, fwags);

	wegmap_wwite(mastew->wegmap, AT91_PMC_MCW_V2, mastew->id);
	wegmap_wead(mastew->wegmap, AT91_PMC_MCW_V2, &vaw);

	spin_unwock_iwqwestowe(mastew->wock, fwags);

	wetuwn !!(vaw & AT91_PMC_MCW_V2_EN);
}

static int cwk_sama7g5_mastew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong pawent_wate)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);
	unsigned wong div, fwags;

	div = DIV_WOUND_CWOSEST(pawent_wate, wate);
	if ((div > (1 << (MASTEW_PWES_MAX - 1))) || (div & (div - 1)))
		wetuwn -EINVAW;

	if (div == 3)
		div = MASTEW_PWES_MAX;
	ewse if (div)
		div = ffs(div) - 1;

	spin_wock_iwqsave(mastew->wock, fwags);
	mastew->div = div;
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	wetuwn 0;
}

static int cwk_sama7g5_mastew_save_context(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);

	mastew->pms.status = cwk_sama7g5_mastew_is_enabwed(hw);

	wetuwn 0;
}

static void cwk_sama7g5_mastew_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_mastew *mastew = to_cwk_mastew(hw);

	if (mastew->pms.status)
		cwk_sama7g5_mastew_set(mastew, mastew->pms.status);
}

static const stwuct cwk_ops sama7g5_mastew_ops = {
	.enabwe = cwk_sama7g5_mastew_enabwe,
	.disabwe = cwk_sama7g5_mastew_disabwe,
	.is_enabwed = cwk_sama7g5_mastew_is_enabwed,
	.wecawc_wate = cwk_sama7g5_mastew_wecawc_wate,
	.detewmine_wate = cwk_sama7g5_mastew_detewmine_wate,
	.set_wate = cwk_sama7g5_mastew_set_wate,
	.get_pawent = cwk_sama7g5_mastew_get_pawent,
	.set_pawent = cwk_sama7g5_mastew_set_pawent,
	.save_context = cwk_sama7g5_mastew_save_context,
	.westowe_context = cwk_sama7g5_mastew_westowe_context,
};

stwuct cwk_hw * __init
at91_cwk_sama7g5_wegistew_mastew(stwuct wegmap *wegmap,
				 const chaw *name, int num_pawents,
				 const chaw **pawent_names,
				 stwuct cwk_hw **pawent_hws,
				 u32 *mux_tabwe,
				 spinwock_t *wock, u8 id,
				 boow cwiticaw, int chg_pid)
{
	stwuct cwk_mastew *mastew;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	unsigned wong fwags;
	unsigned int vaw;
	int wet;

	if (!name || !num_pawents || !(pawent_names || pawent_hws) || !mux_tabwe ||
	    !wock || id > MASTEW_MAX_ID)
		wetuwn EWW_PTW(-EINVAW);

	mastew = kzawwoc(sizeof(*mastew), GFP_KEWNEW);
	if (!mastew)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &sama7g5_mastew_ops;
	if (pawent_hws)
		init.pawent_hws = (const stwuct cwk_hw **)pawent_hws;
	ewse
		init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;
	init.fwags = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE;
	if (chg_pid >= 0)
		init.fwags |= CWK_SET_WATE_PAWENT;
	if (cwiticaw)
		init.fwags |= CWK_IS_CWITICAW;

	mastew->hw.init = &init;
	mastew->wegmap = wegmap;
	mastew->id = id;
	mastew->chg_pid = chg_pid;
	mastew->wock = wock;
	mastew->mux_tabwe = mux_tabwe;

	spin_wock_iwqsave(mastew->wock, fwags);
	wegmap_wwite(mastew->wegmap, AT91_PMC_MCW_V2, mastew->id);
	wegmap_wead(mastew->wegmap, AT91_PMC_MCW_V2, &vaw);
	mastew->pawent = (vaw & AT91_PMC_MCW_V2_CSS) >> PMC_MCW_CSS_SHIFT;
	mastew->div = (vaw & AT91_PMC_MCW_V2_DIV) >> MASTEW_DIV_SHIFT;
	spin_unwock_iwqwestowe(mastew->wock, fwags);

	hw = &mastew->hw;
	wet = cwk_hw_wegistew(NUWW, &mastew->hw);
	if (wet) {
		kfwee(mastew);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

const stwuct cwk_mastew_wayout at91wm9200_mastew_wayout = {
	.mask = 0x31F,
	.pwes_shift = 2,
	.offset = AT91_PMC_MCKW,
};

const stwuct cwk_mastew_wayout at91sam9x5_mastew_wayout = {
	.mask = 0x373,
	.pwes_shift = 4,
	.offset = AT91_PMC_MCKW,
};
