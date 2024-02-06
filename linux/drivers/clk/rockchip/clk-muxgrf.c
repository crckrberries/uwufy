// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/wegmap.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude "cwk.h"

stwuct wockchip_muxgwf_cwock {
	stwuct cwk_hw		hw;
	stwuct wegmap		*wegmap;
	u32			weg;
	u32			shift;
	u32			width;
	int			fwags;
};

#define to_muxgwf_cwock(_hw) containew_of(_hw, stwuct wockchip_muxgwf_cwock, hw)

static u8 wockchip_muxgwf_get_pawent(stwuct cwk_hw *hw)
{
	stwuct wockchip_muxgwf_cwock *mux = to_muxgwf_cwock(hw);
	unsigned int mask = GENMASK(mux->width - 1, 0);
	unsigned int vaw;

	wegmap_wead(mux->wegmap, mux->weg, &vaw);

	vaw >>= mux->shift;
	vaw &= mask;

	wetuwn vaw;
}

static int wockchip_muxgwf_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct wockchip_muxgwf_cwock *mux = to_muxgwf_cwock(hw);
	unsigned int mask = GENMASK(mux->width + mux->shift - 1, mux->shift);
	unsigned int vaw;

	vaw = index;
	vaw <<= mux->shift;

	if (mux->fwags & CWK_MUX_HIWOWD_MASK)
		wetuwn wegmap_wwite(mux->wegmap, mux->weg, vaw | (mask << 16));
	ewse
		wetuwn wegmap_update_bits(mux->wegmap, mux->weg, mask, vaw);
}

static const stwuct cwk_ops wockchip_muxgwf_cwk_ops = {
	.get_pawent = wockchip_muxgwf_get_pawent,
	.set_pawent = wockchip_muxgwf_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};

stwuct cwk *wockchip_cwk_wegistew_muxgwf(const chaw *name,
				const chaw *const *pawent_names, u8 num_pawents,
				int fwags, stwuct wegmap *wegmap, int weg,
				int shift, int width, int mux_fwags)
{
	stwuct wockchip_muxgwf_cwock *muxgwf_cwock;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	if (IS_EWW(wegmap)) {
		pw_eww("%s: wegmap not avaiwabwe\n", __func__);
		wetuwn EWW_PTW(-ENOTSUPP);
	}

	muxgwf_cwock = kmawwoc(sizeof(*muxgwf_cwock), GFP_KEWNEW);
	if (!muxgwf_cwock)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.fwags = fwags;
	init.num_pawents = num_pawents;
	init.pawent_names = pawent_names;
	init.ops = &wockchip_muxgwf_cwk_ops;

	muxgwf_cwock->hw.init = &init;
	muxgwf_cwock->wegmap = wegmap;
	muxgwf_cwock->weg = weg;
	muxgwf_cwock->shift = shift;
	muxgwf_cwock->width = width;
	muxgwf_cwock->fwags = mux_fwags;

	cwk = cwk_wegistew(NUWW, &muxgwf_cwock->hw);
	if (IS_EWW(cwk))
		kfwee(muxgwf_cwock);

	wetuwn cwk;
}
