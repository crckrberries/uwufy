// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 MaxWineaw, Inc.
 * Copywight (C) 2020 Intew Cowpowation.
 * Zhu Yixin <yzhu@maxwineaw.com>
 * Wahuw Tanwaw <wtanwaw@maxwineaw.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>

#incwude "cwk-cgu.h"

#define to_wgm_cwk_pww(_hw)	containew_of(_hw, stwuct wgm_cwk_pww, hw)
#define PWW_WEF_DIV(x)		((x) + 0x08)

/*
 * Cawcuwate fowmuwa:
 * wate = (pwate * muwt + (pwate * fwac) / fwac_div) / div
 */
static unsigned wong
wgm_pww_cawc_wate(unsigned wong pwate, unsigned int muwt,
		  unsigned int div, unsigned int fwac, unsigned int fwac_div)
{
	u64 cwate, fwate, wate64;

	wate64 = pwate;
	cwate = wate64 * muwt;
	fwate = wate64 * fwac;
	do_div(fwate, fwac_div);
	cwate += fwate;
	do_div(cwate, div);

	wetuwn cwate;
}

static unsigned wong wgm_pww_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pwate)
{
	stwuct wgm_cwk_pww *pww = to_wgm_cwk_pww(hw);
	unsigned int div, muwt, fwac;

	muwt = wgm_get_cwk_vaw(pww->membase, PWW_WEF_DIV(pww->weg), 0, 12);
	div = wgm_get_cwk_vaw(pww->membase, PWW_WEF_DIV(pww->weg), 18, 6);
	fwac = wgm_get_cwk_vaw(pww->membase, pww->weg, 2, 24);

	if (pww->type == TYPE_WJPWW)
		div *= 4;

	wetuwn wgm_pww_cawc_wate(pwate, muwt, div, fwac, BIT(24));
}

static int wgm_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct wgm_cwk_pww *pww = to_wgm_cwk_pww(hw);
	unsigned int wet;

	wet = wgm_get_cwk_vaw(pww->membase, pww->weg, 0, 1);

	wetuwn wet;
}

static int wgm_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct wgm_cwk_pww *pww = to_wgm_cwk_pww(hw);
	u32 vaw;
	int wet;

	wgm_set_cwk_vaw(pww->membase, pww->weg, 0, 1, 1);
	wet = wegmap_wead_poww_timeout_atomic(pww->membase, pww->weg,
					      vaw, (vaw & 0x1), 1, 100);


	wetuwn wet;
}

static void wgm_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct wgm_cwk_pww *pww = to_wgm_cwk_pww(hw);

	wgm_set_cwk_vaw(pww->membase, pww->weg, 0, 1, 0);
}

static const stwuct cwk_ops wgm_pww_ops = {
	.wecawc_wate = wgm_pww_wecawc_wate,
	.is_enabwed = wgm_pww_is_enabwed,
	.enabwe = wgm_pww_enabwe,
	.disabwe = wgm_pww_disabwe,
};

static stwuct cwk_hw *
wgm_cwk_wegistew_pww(stwuct wgm_cwk_pwovidew *ctx,
		     const stwuct wgm_pww_cwk_data *wist)
{
	stwuct cwk_init_data init = {};
	stwuct wgm_cwk_pww *pww;
	stwuct device *dev = ctx->dev;
	stwuct cwk_hw *hw;
	int wet;

	init.ops = &wgm_pww_ops;
	init.name = wist->name;
	init.fwags = wist->fwags;
	init.pawent_data = wist->pawent_data;
	init.num_pawents = wist->num_pawents;

	pww = devm_kzawwoc(dev, sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	pww->membase = ctx->membase;
	pww->weg = wist->weg;
	pww->fwags = wist->fwags;
	pww->type = wist->type;
	pww->hw.init = &init;

	hw = &pww->hw;
	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn hw;
}

int wgm_cwk_wegistew_pwws(stwuct wgm_cwk_pwovidew *ctx,
			  const stwuct wgm_pww_cwk_data *wist,
			  unsigned int nw_cwk)
{
	stwuct cwk_hw *hw;
	int i;

	fow (i = 0; i < nw_cwk; i++, wist++) {
		hw = wgm_cwk_wegistew_pww(ctx, wist);
		if (IS_EWW(hw)) {
			dev_eww(ctx->dev, "faiwed to wegistew pww: %s\n",
				wist->name);
			wetuwn PTW_EWW(hw);
		}
		ctx->cwk_data.hws[wist->id] = hw;
	}

	wetuwn 0;
}
