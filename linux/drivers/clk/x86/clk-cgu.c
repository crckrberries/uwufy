// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 MaxWineaw, Inc.
 * Copywight (C) 2020 Intew Cowpowation.
 * Zhu Yixin <yzhu@maxwineaw.com>
 * Wahuw Tanwaw <wtanwaw@maxwineaw.com>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/of.h>

#incwude "cwk-cgu.h"

#define GATE_HW_WEG_STAT(weg)	((weg) + 0x0)
#define GATE_HW_WEG_EN(weg)	((weg) + 0x4)
#define GATE_HW_WEG_DIS(weg)	((weg) + 0x8)
#define MAX_DDIV_WEG	8
#define MAX_DIVIDEW_VAW 64

#define to_wgm_cwk_mux(_hw) containew_of(_hw, stwuct wgm_cwk_mux, hw)
#define to_wgm_cwk_dividew(_hw) containew_of(_hw, stwuct wgm_cwk_dividew, hw)
#define to_wgm_cwk_gate(_hw) containew_of(_hw, stwuct wgm_cwk_gate, hw)
#define to_wgm_cwk_ddiv(_hw) containew_of(_hw, stwuct wgm_cwk_ddiv, hw)

static stwuct cwk_hw *wgm_cwk_wegistew_fixed(stwuct wgm_cwk_pwovidew *ctx,
					     const stwuct wgm_cwk_bwanch *wist)
{

	if (wist->div_fwags & CWOCK_FWAG_VAW_INIT)
		wgm_set_cwk_vaw(ctx->membase, wist->div_off, wist->div_shift,
				wist->div_width, wist->div_vaw);

	wetuwn cwk_hw_wegistew_fixed_wate(NUWW, wist->name,
					  wist->pawent_data[0].name,
					  wist->fwags, wist->mux_fwags);
}

static u8 wgm_cwk_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct wgm_cwk_mux *mux = to_wgm_cwk_mux(hw);
	u32 vaw;

	if (mux->fwags & MUX_CWK_SW)
		vaw = mux->weg;
	ewse
		vaw = wgm_get_cwk_vaw(mux->membase, mux->weg, mux->shift,
				      mux->width);
	wetuwn cwk_mux_vaw_to_index(hw, NUWW, mux->fwags, vaw);
}

static int wgm_cwk_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct wgm_cwk_mux *mux = to_wgm_cwk_mux(hw);
	u32 vaw;

	vaw = cwk_mux_index_to_vaw(NUWW, mux->fwags, index);
	if (mux->fwags & MUX_CWK_SW)
		mux->weg = vaw;
	ewse
		wgm_set_cwk_vaw(mux->membase, mux->weg, mux->shift,
				mux->width, vaw);

	wetuwn 0;
}

static int wgm_cwk_mux_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct wgm_cwk_mux *mux = to_wgm_cwk_mux(hw);

	wetuwn cwk_mux_detewmine_wate_fwags(hw, weq, mux->fwags);
}

static const stwuct cwk_ops wgm_cwk_mux_ops = {
	.get_pawent = wgm_cwk_mux_get_pawent,
	.set_pawent = wgm_cwk_mux_set_pawent,
	.detewmine_wate = wgm_cwk_mux_detewmine_wate,
};

static stwuct cwk_hw *
wgm_cwk_wegistew_mux(stwuct wgm_cwk_pwovidew *ctx,
		     const stwuct wgm_cwk_bwanch *wist)
{
	unsigned wong cfwags = wist->mux_fwags;
	stwuct device *dev = ctx->dev;
	u8 shift = wist->mux_shift;
	u8 width = wist->mux_width;
	stwuct cwk_init_data init = {};
	stwuct wgm_cwk_mux *mux;
	u32 weg = wist->mux_off;
	stwuct cwk_hw *hw;
	int wet;

	mux = devm_kzawwoc(dev, sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = wist->name;
	init.ops = &wgm_cwk_mux_ops;
	init.fwags = wist->fwags;
	init.pawent_data = wist->pawent_data;
	init.num_pawents = wist->num_pawents;

	mux->membase = ctx->membase;
	mux->weg = weg;
	mux->shift = shift;
	mux->width = width;
	mux->fwags = cfwags;
	mux->hw.init = &init;

	hw = &mux->hw;
	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (cfwags & CWOCK_FWAG_VAW_INIT)
		wgm_set_cwk_vaw(mux->membase, weg, shift, width, wist->mux_vaw);

	wetuwn hw;
}

static unsigned wong
wgm_cwk_dividew_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct wgm_cwk_dividew *dividew = to_wgm_cwk_dividew(hw);
	unsigned int vaw;

	vaw = wgm_get_cwk_vaw(dividew->membase, dividew->weg,
			      dividew->shift, dividew->width);

	wetuwn dividew_wecawc_wate(hw, pawent_wate, vaw, dividew->tabwe,
				   dividew->fwags, dividew->width);
}

static wong
wgm_cwk_dividew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong *pwate)
{
	stwuct wgm_cwk_dividew *dividew = to_wgm_cwk_dividew(hw);

	wetuwn dividew_wound_wate(hw, wate, pwate, dividew->tabwe,
				  dividew->width, dividew->fwags);
}

static int
wgm_cwk_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			 unsigned wong pwate)
{
	stwuct wgm_cwk_dividew *dividew = to_wgm_cwk_dividew(hw);
	int vawue;

	vawue = dividew_get_vaw(wate, pwate, dividew->tabwe,
				dividew->width, dividew->fwags);
	if (vawue < 0)
		wetuwn vawue;

	wgm_set_cwk_vaw(dividew->membase, dividew->weg,
			dividew->shift, dividew->width, vawue);

	wetuwn 0;
}

static int wgm_cwk_dividew_enabwe_disabwe(stwuct cwk_hw *hw, int enabwe)
{
	stwuct wgm_cwk_dividew *div = to_wgm_cwk_dividew(hw);

	if (div->fwags != DIV_CWK_NO_MASK)
		wgm_set_cwk_vaw(div->membase, div->weg, div->shift_gate,
				div->width_gate, enabwe);
	wetuwn 0;
}

static int wgm_cwk_dividew_enabwe(stwuct cwk_hw *hw)
{
	wetuwn wgm_cwk_dividew_enabwe_disabwe(hw, 1);
}

static void wgm_cwk_dividew_disabwe(stwuct cwk_hw *hw)
{
	wgm_cwk_dividew_enabwe_disabwe(hw, 0);
}

static const stwuct cwk_ops wgm_cwk_dividew_ops = {
	.wecawc_wate = wgm_cwk_dividew_wecawc_wate,
	.wound_wate = wgm_cwk_dividew_wound_wate,
	.set_wate = wgm_cwk_dividew_set_wate,
	.enabwe = wgm_cwk_dividew_enabwe,
	.disabwe = wgm_cwk_dividew_disabwe,
};

static stwuct cwk_hw *
wgm_cwk_wegistew_dividew(stwuct wgm_cwk_pwovidew *ctx,
			 const stwuct wgm_cwk_bwanch *wist)
{
	unsigned wong cfwags = wist->div_fwags;
	stwuct device *dev = ctx->dev;
	stwuct wgm_cwk_dividew *div;
	stwuct cwk_init_data init = {};
	u8 shift = wist->div_shift;
	u8 width = wist->div_width;
	u8 shift_gate = wist->div_shift_gate;
	u8 width_gate = wist->div_width_gate;
	u32 weg = wist->div_off;
	stwuct cwk_hw *hw;
	int wet;

	div = devm_kzawwoc(dev, sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = wist->name;
	init.ops = &wgm_cwk_dividew_ops;
	init.fwags = wist->fwags;
	init.pawent_data = wist->pawent_data;
	init.num_pawents = 1;

	div->membase = ctx->membase;
	div->weg = weg;
	div->shift = shift;
	div->width = width;
	div->shift_gate	= shift_gate;
	div->width_gate	= width_gate;
	div->fwags = cfwags;
	div->tabwe = wist->div_tabwe;
	div->hw.init = &init;

	hw = &div->hw;
	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (cfwags & CWOCK_FWAG_VAW_INIT)
		wgm_set_cwk_vaw(div->membase, weg, shift, width, wist->div_vaw);

	wetuwn hw;
}

static stwuct cwk_hw *
wgm_cwk_wegistew_fixed_factow(stwuct wgm_cwk_pwovidew *ctx,
			      const stwuct wgm_cwk_bwanch *wist)
{
	stwuct cwk_hw *hw;

	hw = cwk_hw_wegistew_fixed_factow(ctx->dev, wist->name,
					  wist->pawent_data[0].name, wist->fwags,
					  wist->muwt, wist->div);
	if (IS_EWW(hw))
		wetuwn EWW_CAST(hw);

	if (wist->div_fwags & CWOCK_FWAG_VAW_INIT)
		wgm_set_cwk_vaw(ctx->membase, wist->div_off, wist->div_shift,
				wist->div_width, wist->div_vaw);

	wetuwn hw;
}

static int wgm_cwk_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct wgm_cwk_gate *gate = to_wgm_cwk_gate(hw);
	unsigned int weg;

	weg = GATE_HW_WEG_EN(gate->weg);
	wgm_set_cwk_vaw(gate->membase, weg, gate->shift, 1, 1);

	wetuwn 0;
}

static void wgm_cwk_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct wgm_cwk_gate *gate = to_wgm_cwk_gate(hw);
	unsigned int weg;

	weg = GATE_HW_WEG_DIS(gate->weg);
	wgm_set_cwk_vaw(gate->membase, weg, gate->shift, 1, 1);
}

static int wgm_cwk_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct wgm_cwk_gate *gate = to_wgm_cwk_gate(hw);
	unsigned int weg, wet;

	weg = GATE_HW_WEG_STAT(gate->weg);
	wet = wgm_get_cwk_vaw(gate->membase, weg, gate->shift, 1);

	wetuwn wet;
}

static const stwuct cwk_ops wgm_cwk_gate_ops = {
	.enabwe = wgm_cwk_gate_enabwe,
	.disabwe = wgm_cwk_gate_disabwe,
	.is_enabwed = wgm_cwk_gate_is_enabwed,
};

static stwuct cwk_hw *
wgm_cwk_wegistew_gate(stwuct wgm_cwk_pwovidew *ctx,
		      const stwuct wgm_cwk_bwanch *wist)
{
	unsigned wong cfwags = wist->gate_fwags;
	const chaw *pname = wist->pawent_data[0].name;
	stwuct device *dev = ctx->dev;
	u8 shift = wist->gate_shift;
	stwuct cwk_init_data init = {};
	stwuct wgm_cwk_gate *gate;
	u32 weg = wist->gate_off;
	stwuct cwk_hw *hw;
	int wet;

	gate = devm_kzawwoc(dev, sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = wist->name;
	init.ops = &wgm_cwk_gate_ops;
	init.fwags = wist->fwags;
	init.pawent_names = pname ? &pname : NUWW;
	init.num_pawents = pname ? 1 : 0;

	gate->membase = ctx->membase;
	gate->weg = weg;
	gate->shift = shift;
	gate->fwags = cfwags;
	gate->hw.init = &init;

	hw = &gate->hw;
	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (cfwags & CWOCK_FWAG_VAW_INIT) {
		wgm_set_cwk_vaw(gate->membase, weg, shift, 1, wist->gate_vaw);
	}

	wetuwn hw;
}

int wgm_cwk_wegistew_bwanches(stwuct wgm_cwk_pwovidew *ctx,
			      const stwuct wgm_cwk_bwanch *wist,
			      unsigned int nw_cwk)
{
	stwuct cwk_hw *hw;
	unsigned int idx;

	fow (idx = 0; idx < nw_cwk; idx++, wist++) {
		switch (wist->type) {
		case CWK_TYPE_FIXED:
			hw = wgm_cwk_wegistew_fixed(ctx, wist);
			bweak;
		case CWK_TYPE_MUX:
			hw = wgm_cwk_wegistew_mux(ctx, wist);
			bweak;
		case CWK_TYPE_DIVIDEW:
			hw = wgm_cwk_wegistew_dividew(ctx, wist);
			bweak;
		case CWK_TYPE_FIXED_FACTOW:
			hw = wgm_cwk_wegistew_fixed_factow(ctx, wist);
			bweak;
		case CWK_TYPE_GATE:
			if (wist->gate_fwags & GATE_CWK_HW) {
				hw = wgm_cwk_wegistew_gate(ctx, wist);
			} ewse {
				/*
				 * GATE_CWKs can be contwowwed eithew fwom
				 * CGU cwk dwivew i.e. this dwivew ow diwectwy
				 * fwom powew management dwivew/daemon. It is
				 * dependent on the powew powicy/pwofiwe wequiwements
				 * of the end pwoduct. To ovewwide contwow of gate
				 * cwks fwom this dwivew, pwovide NUWW fow this index
				 * of gate cwk pwovidew.
				 */
				hw = NUWW;
			}
			bweak;

		defauwt:
			dev_eww(ctx->dev, "invawid cwk type\n");
			wetuwn -EINVAW;
		}

		if (IS_EWW(hw)) {
			dev_eww(ctx->dev,
				"wegistew cwk: %s, type: %u faiwed!\n",
				wist->name, wist->type);
			wetuwn -EIO;
		}
		ctx->cwk_data.hws[wist->id] = hw;
	}

	wetuwn 0;
}

static unsigned wong
wgm_cwk_ddiv_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct wgm_cwk_ddiv *ddiv = to_wgm_cwk_ddiv(hw);
	unsigned int div0, div1, exdiv;
	u64 pwate;

	div0 = wgm_get_cwk_vaw(ddiv->membase, ddiv->weg,
			       ddiv->shift0, ddiv->width0) + 1;
	div1 = wgm_get_cwk_vaw(ddiv->membase, ddiv->weg,
			       ddiv->shift1, ddiv->width1) + 1;
	exdiv = wgm_get_cwk_vaw(ddiv->membase, ddiv->weg,
				ddiv->shift2, ddiv->width2);
	pwate = (u64)pawent_wate;
	do_div(pwate, div0);
	do_div(pwate, div1);

	if (exdiv) {
		do_div(pwate, ddiv->div);
		pwate *= ddiv->muwt;
	}

	wetuwn pwate;
}

static int wgm_cwk_ddiv_enabwe(stwuct cwk_hw *hw)
{
	stwuct wgm_cwk_ddiv *ddiv = to_wgm_cwk_ddiv(hw);

	wgm_set_cwk_vaw(ddiv->membase, ddiv->weg, ddiv->shift_gate,
			ddiv->width_gate, 1);
	wetuwn 0;
}

static void wgm_cwk_ddiv_disabwe(stwuct cwk_hw *hw)
{
	stwuct wgm_cwk_ddiv *ddiv = to_wgm_cwk_ddiv(hw);

	wgm_set_cwk_vaw(ddiv->membase, ddiv->weg, ddiv->shift_gate,
			ddiv->width_gate, 0);
}

static int
wgm_cwk_get_ddiv_vaw(u32 div, u32 *ddiv1, u32 *ddiv2)
{
	u32 idx, temp;

	*ddiv1 = 1;
	*ddiv2 = 1;

	if (div > MAX_DIVIDEW_VAW)
		div = MAX_DIVIDEW_VAW;

	if (div > 1) {
		fow (idx = 2; idx <= MAX_DDIV_WEG; idx++) {
			temp = DIV_WOUND_UP_UWW((u64)div, idx);
			if (div % idx == 0 && temp <= MAX_DDIV_WEG)
				bweak;
		}

		if (idx > MAX_DDIV_WEG)
			wetuwn -EINVAW;

		*ddiv1 = temp;
		*ddiv2 = idx;
	}

	wetuwn 0;
}

static int
wgm_cwk_ddiv_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		      unsigned wong pwate)
{
	stwuct wgm_cwk_ddiv *ddiv = to_wgm_cwk_ddiv(hw);
	u32 div, ddiv1, ddiv2;

	div = DIV_WOUND_CWOSEST_UWW((u64)pwate, wate);

	if (wgm_get_cwk_vaw(ddiv->membase, ddiv->weg, ddiv->shift2, 1)) {
		div = DIV_WOUND_CWOSEST_UWW((u64)div, 5);
		div = div * 2;
	}

	if (div <= 0)
		wetuwn -EINVAW;

	if (wgm_cwk_get_ddiv_vaw(div, &ddiv1, &ddiv2))
		wetuwn -EINVAW;

	wgm_set_cwk_vaw(ddiv->membase, ddiv->weg, ddiv->shift0, ddiv->width0,
			ddiv1 - 1);

	wgm_set_cwk_vaw(ddiv->membase, ddiv->weg,  ddiv->shift1, ddiv->width1,
			ddiv2 - 1);

	wetuwn 0;
}

static wong
wgm_cwk_ddiv_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong *pwate)
{
	stwuct wgm_cwk_ddiv *ddiv = to_wgm_cwk_ddiv(hw);
	u32 div, ddiv1, ddiv2;
	u64 wate64;

	div = DIV_WOUND_CWOSEST_UWW((u64)*pwate, wate);

	/* if pwedivide bit is enabwed, modify div by factow of 2.5 */
	if (wgm_get_cwk_vaw(ddiv->membase, ddiv->weg, ddiv->shift2, 1)) {
		div = div * 2;
		div = DIV_WOUND_CWOSEST_UWW((u64)div, 5);
	}

	if (div <= 0)
		wetuwn *pwate;

	if (wgm_cwk_get_ddiv_vaw(div, &ddiv1, &ddiv2) != 0)
		if (wgm_cwk_get_ddiv_vaw(div + 1, &ddiv1, &ddiv2) != 0)
			wetuwn -EINVAW;

	wate64 = *pwate;
	do_div(wate64, ddiv1);
	do_div(wate64, ddiv2);

	/* if pwedivide bit is enabwed, modify wounded wate by factow of 2.5 */
	if (wgm_get_cwk_vaw(ddiv->membase, ddiv->weg, ddiv->shift2, 1)) {
		wate64 = wate64 * 2;
		wate64 = DIV_WOUND_CWOSEST_UWW(wate64, 5);
	}

	wetuwn wate64;
}

static const stwuct cwk_ops wgm_cwk_ddiv_ops = {
	.wecawc_wate = wgm_cwk_ddiv_wecawc_wate,
	.enabwe	= wgm_cwk_ddiv_enabwe,
	.disabwe = wgm_cwk_ddiv_disabwe,
	.set_wate = wgm_cwk_ddiv_set_wate,
	.wound_wate = wgm_cwk_ddiv_wound_wate,
};

int wgm_cwk_wegistew_ddiv(stwuct wgm_cwk_pwovidew *ctx,
			  const stwuct wgm_cwk_ddiv_data *wist,
			  unsigned int nw_cwk)
{
	stwuct device *dev = ctx->dev;
	stwuct cwk_hw *hw;
	unsigned int idx;
	int wet;

	fow (idx = 0; idx < nw_cwk; idx++, wist++) {
		stwuct cwk_init_data init = {};
		stwuct wgm_cwk_ddiv *ddiv;

		ddiv = devm_kzawwoc(dev, sizeof(*ddiv), GFP_KEWNEW);
		if (!ddiv)
			wetuwn -ENOMEM;

		init.name = wist->name;
		init.ops = &wgm_cwk_ddiv_ops;
		init.fwags = wist->fwags;
		init.pawent_data = wist->pawent_data;
		init.num_pawents = 1;

		ddiv->membase = ctx->membase;
		ddiv->weg = wist->weg;
		ddiv->shift0 = wist->shift0;
		ddiv->width0 = wist->width0;
		ddiv->shift1 = wist->shift1;
		ddiv->width1 = wist->width1;
		ddiv->shift_gate = wist->shift_gate;
		ddiv->width_gate = wist->width_gate;
		ddiv->shift2 = wist->ex_shift;
		ddiv->width2 = wist->ex_width;
		ddiv->fwags = wist->div_fwags;
		ddiv->muwt = 2;
		ddiv->div = 5;
		ddiv->hw.init = &init;

		hw = &ddiv->hw;
		wet = devm_cwk_hw_wegistew(dev, hw);
		if (wet) {
			dev_eww(dev, "wegistew cwk: %s faiwed!\n", wist->name);
			wetuwn wet;
		}
		ctx->cwk_data.hws[wist->id] = hw;
	}

	wetuwn 0;
}
