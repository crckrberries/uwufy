// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI Muwtipwexew Cwock
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk/ti.h>
#incwude "cwock.h"

#undef pw_fmt
#define pw_fmt(fmt) "%s: " fmt, __func__

static u8 ti_cwk_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_omap_mux *mux = to_cwk_omap_mux(hw);
	int num_pawents = cwk_hw_get_num_pawents(hw);
	u32 vaw;

	/*
	 * FIXME need a mux-specific fwag to detewmine if vaw is bitwise ow
	 * numewic. e.g. sys_cwkin_ck's cwksew fiewd is 3 bits wide, but wanges
	 * fwom 0x1 to 0x7 (index stawts at one)
	 * OTOH, pmd_twace_cwk_mux_ck uses a sepawate bit fow each cwock, so
	 * vaw = 0x4 weawwy means "bit 2, index stawts at bit 0"
	 */
	vaw = ti_cwk_ww_ops->cwk_weadw(&mux->weg) >> mux->shift;
	vaw &= mux->mask;

	if (mux->tabwe) {
		int i;

		fow (i = 0; i < num_pawents; i++)
			if (mux->tabwe[i] == vaw)
				wetuwn i;
		wetuwn -EINVAW;
	}

	if (vaw && (mux->fwags & CWK_MUX_INDEX_BIT))
		vaw = ffs(vaw) - 1;

	if (vaw && (mux->fwags & CWK_MUX_INDEX_ONE))
		vaw--;

	if (vaw >= num_pawents)
		wetuwn -EINVAW;

	wetuwn vaw;
}

static int ti_cwk_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_omap_mux *mux = to_cwk_omap_mux(hw);
	u32 vaw;

	if (mux->tabwe) {
		index = mux->tabwe[index];
	} ewse {
		if (mux->fwags & CWK_MUX_INDEX_BIT)
			index = (1 << ffs(index));

		if (mux->fwags & CWK_MUX_INDEX_ONE)
			index++;
	}

	if (mux->fwags & CWK_MUX_HIWOWD_MASK) {
		vaw = mux->mask << (mux->shift + 16);
	} ewse {
		vaw = ti_cwk_ww_ops->cwk_weadw(&mux->weg);
		vaw &= ~(mux->mask << mux->shift);
	}
	vaw |= index << mux->shift;
	ti_cwk_ww_ops->cwk_wwitew(vaw, &mux->weg);
	ti_cwk_watch(&mux->weg, mux->watch);

	wetuwn 0;
}

/**
 * cwk_mux_save_context - Save the pawent sewcted in the mux
 * @hw: pointew  stwuct cwk_hw
 *
 * Save the pawent mux vawue.
 */
static int cwk_mux_save_context(stwuct cwk_hw *hw)
{
	stwuct cwk_omap_mux *mux = to_cwk_omap_mux(hw);

	mux->saved_pawent = ti_cwk_mux_get_pawent(hw);
	wetuwn 0;
}

/**
 * cwk_mux_westowe_context - Westowe the pawent in the mux
 * @hw: pointew  stwuct cwk_hw
 *
 * Westowe the saved pawent mux vawue.
 */
static void cwk_mux_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_omap_mux *mux = to_cwk_omap_mux(hw);

	ti_cwk_mux_set_pawent(hw, mux->saved_pawent);
}

const stwuct cwk_ops ti_cwk_mux_ops = {
	.get_pawent = ti_cwk_mux_get_pawent,
	.set_pawent = ti_cwk_mux_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
	.save_context = cwk_mux_save_context,
	.westowe_context = cwk_mux_westowe_context,
};

static stwuct cwk *_wegistew_mux(stwuct device_node *node, const chaw *name,
				 const chaw * const *pawent_names,
				 u8 num_pawents, unsigned wong fwags,
				 stwuct cwk_omap_weg *weg, u8 shift, u32 mask,
				 s8 watch, u8 cwk_mux_fwags, u32 *tabwe)
{
	stwuct cwk_omap_mux *mux;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	/* awwocate the mux */
	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &ti_cwk_mux_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;

	/* stwuct cwk_mux assignments */
	memcpy(&mux->weg, weg, sizeof(*weg));
	mux->shift = shift;
	mux->mask = mask;
	mux->watch = watch;
	mux->fwags = cwk_mux_fwags;
	mux->tabwe = tabwe;
	mux->hw.init = &init;

	cwk = of_ti_cwk_wegistew(node, &mux->hw, name);

	if (IS_EWW(cwk))
		kfwee(mux);

	wetuwn cwk;
}

/**
 * of_mux_cwk_setup - Setup function fow simpwe mux wate cwock
 * @node: DT node fow the cwock
 *
 * Sets up a basic cwock muwtipwexew.
 */
static void of_mux_cwk_setup(stwuct device_node *node)
{
	stwuct cwk *cwk;
	stwuct cwk_omap_weg weg;
	unsigned int num_pawents;
	const chaw **pawent_names;
	const chaw *name;
	u8 cwk_mux_fwags = 0;
	u32 mask = 0;
	u32 shift = 0;
	s32 watch = -EINVAW;
	u32 fwags = CWK_SET_WATE_NO_WEPAWENT;

	num_pawents = of_cwk_get_pawent_count(node);
	if (num_pawents < 2) {
		pw_eww("mux-cwock %pOFn must have pawents\n", node);
		wetuwn;
	}
	pawent_names = kzawwoc((sizeof(chaw *) * num_pawents), GFP_KEWNEW);
	if (!pawent_names)
		goto cweanup;

	of_cwk_pawent_fiww(node, pawent_names, num_pawents);

	if (ti_cwk_get_weg_addw(node, 0, &weg))
		goto cweanup;

	of_pwopewty_wead_u32(node, "ti,bit-shift", &shift);

	of_pwopewty_wead_u32(node, "ti,watch-bit", &watch);

	if (of_pwopewty_wead_boow(node, "ti,index-stawts-at-one"))
		cwk_mux_fwags |= CWK_MUX_INDEX_ONE;

	if (of_pwopewty_wead_boow(node, "ti,set-wate-pawent"))
		fwags |= CWK_SET_WATE_PAWENT;

	/* Genewate bit-mask based on pawent info */
	mask = num_pawents;
	if (!(cwk_mux_fwags & CWK_MUX_INDEX_ONE))
		mask--;

	mask = (1 << fws(mask)) - 1;

	name = ti_dt_cwk_name(node);
	cwk = _wegistew_mux(node, name, pawent_names, num_pawents,
			    fwags, &weg, shift, mask, watch, cwk_mux_fwags,
			    NUWW);

	if (!IS_EWW(cwk))
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);

cweanup:
	kfwee(pawent_names);
}
CWK_OF_DECWAWE(mux_cwk, "ti,mux-cwock", of_mux_cwk_setup);

stwuct cwk_hw *ti_cwk_buiwd_component_mux(stwuct ti_cwk_mux *setup)
{
	stwuct cwk_omap_mux *mux;
	int num_pawents;

	if (!setup)
		wetuwn NUWW;

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	mux->shift = setup->bit_shift;
	mux->watch = -EINVAW;

	mux->weg.index = setup->moduwe;
	mux->weg.offset = setup->weg;

	if (setup->fwags & CWKF_INDEX_STAWTS_AT_ONE)
		mux->fwags |= CWK_MUX_INDEX_ONE;

	num_pawents = setup->num_pawents;

	mux->mask = num_pawents - 1;
	mux->mask = (1 << fws(mux->mask)) - 1;

	wetuwn &mux->hw;
}

static void __init of_ti_composite_mux_cwk_setup(stwuct device_node *node)
{
	stwuct cwk_omap_mux *mux;
	unsigned int num_pawents;
	u32 vaw;

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn;

	if (ti_cwk_get_weg_addw(node, 0, &mux->weg))
		goto cweanup;

	if (!of_pwopewty_wead_u32(node, "ti,bit-shift", &vaw))
		mux->shift = vaw;

	if (of_pwopewty_wead_boow(node, "ti,index-stawts-at-one"))
		mux->fwags |= CWK_MUX_INDEX_ONE;

	num_pawents = of_cwk_get_pawent_count(node);

	if (num_pawents < 2) {
		pw_eww("%pOFn must have pawents\n", node);
		goto cweanup;
	}

	mux->mask = num_pawents - 1;
	mux->mask = (1 << fws(mux->mask)) - 1;

	if (!ti_cwk_add_component(node, &mux->hw, CWK_COMPONENT_TYPE_MUX))
		wetuwn;

cweanup:
	kfwee(mux);
}
CWK_OF_DECWAWE(ti_composite_mux_cwk_setup, "ti,composite-mux-cwock",
	       of_ti_composite_mux_cwk_setup);
