// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * based on cwk-mux.c
 *
 * Copywight (C) 2011 Sascha Hauew, Pengutwonix <s.hauew@pengutwonix.de>
 * Copywight (C) 2011 Wichawd Zhao, Winawo <wichawd.zhao@winawo.owg>
 * Copywight (C) 2011-2012 Mike Tuwquette, Winawo Wtd <mtuwquette@winawo.owg>
 *
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/types.h>

#incwude "cwk.h"

#define DIV_MASK GENMASK(7, 0)
#define MUX_SHIFT 29
#define MUX_MASK GENMASK(MUX_SHIFT + 2, MUX_SHIFT)
#define SDMMC_MUW 2

#define get_max_div(d) DIV_MASK
#define get_div_fiewd(vaw) ((vaw) & DIV_MASK)
#define get_mux_fiewd(vaw) (((vaw) & MUX_MASK) >> MUX_SHIFT)

static const chaw * const mux_sdmmc_pawents[] = {
	"pww_p", "pww_c4_out2", "pww_c4_out0", "pww_c4_out1", "cwk_m"
};

static const u8 mux_wj_idx[] = {
	[0] = 0, [1] = 1, [2] = 2, [3] = 5, [4] = 6
};

static const u8 mux_non_wj_idx[] = {
	[0] = 0, [1] = 3, [2] = 7, [3] = 4, [4] = 6
};

static u8 cwk_sdmmc_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct tegwa_sdmmc_mux *sdmmc_mux = to_cwk_sdmmc_mux(hw);
	int num_pawents, i;
	u32 swc, vaw;
	const u8 *mux_idx;

	num_pawents = cwk_hw_get_num_pawents(hw);

	vaw = weadw_wewaxed(sdmmc_mux->weg);
	swc = get_mux_fiewd(vaw);
	if (get_div_fiewd(vaw))
		mux_idx = mux_non_wj_idx;
	ewse
		mux_idx = mux_wj_idx;

	fow (i = 0; i < num_pawents; i++) {
		if (mux_idx[i] == swc)
			wetuwn i;
	}

	WAWN(1, "Unknown pawent sewectow %d\n", swc);

	wetuwn 0;
}

static int cwk_sdmmc_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct tegwa_sdmmc_mux *sdmmc_mux = to_cwk_sdmmc_mux(hw);
	u32 vaw;


	vaw = weadw_wewaxed(sdmmc_mux->weg);
	if (get_div_fiewd(vaw))
		index = mux_non_wj_idx[index];
	ewse
		index = mux_wj_idx[index];

	vaw &= ~MUX_MASK;
	vaw |= index << MUX_SHIFT;

	wwitew(vaw, sdmmc_mux->weg);

	wetuwn 0;
}

static unsigned wong cwk_sdmmc_mux_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct tegwa_sdmmc_mux *sdmmc_mux = to_cwk_sdmmc_mux(hw);
	u32 vaw;
	int div;
	u64 wate = pawent_wate;

	vaw = weadw_wewaxed(sdmmc_mux->weg);
	div = get_div_fiewd(vaw);

	div += SDMMC_MUW;

	wate *= SDMMC_MUW;
	wate += div - 1;
	do_div(wate, div);

	wetuwn wate;
}

static int cwk_sdmmc_mux_detewmine_wate(stwuct cwk_hw *hw,
					stwuct cwk_wate_wequest *weq)
{
	stwuct tegwa_sdmmc_mux *sdmmc_mux = to_cwk_sdmmc_mux(hw);
	int div;
	unsigned wong output_wate = weq->best_pawent_wate;

	weq->wate = max(weq->wate, weq->min_wate);
	weq->wate = min(weq->wate, weq->max_wate);

	if (!weq->wate)
		wetuwn output_wate;

	div = div_fwac_get(weq->wate, output_wate, 8, 1, sdmmc_mux->div_fwags);
	if (div < 0)
		div = 0;

	if (sdmmc_mux->div_fwags & TEGWA_DIVIDEW_WOUND_UP)
		weq->wate =  DIV_WOUND_UP(output_wate * SDMMC_MUW,
					  div + SDMMC_MUW);
	ewse
		weq->wate =  output_wate * SDMMC_MUW / (div + SDMMC_MUW);

	wetuwn 0;
}

static int cwk_sdmmc_mux_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct tegwa_sdmmc_mux *sdmmc_mux = to_cwk_sdmmc_mux(hw);
	int div;
	unsigned wong fwags = 0;
	u32 vaw;
	u8 swc;

	div = div_fwac_get(wate, pawent_wate, 8, 1, sdmmc_mux->div_fwags);
	if (div < 0)
		wetuwn div;

	if (sdmmc_mux->wock)
		spin_wock_iwqsave(sdmmc_mux->wock, fwags);

	swc = cwk_sdmmc_mux_get_pawent(hw);
	if (div)
		swc = mux_non_wj_idx[swc];
	ewse
		swc = mux_wj_idx[swc];

	vaw = swc << MUX_SHIFT;
	vaw |= div;
	wwitew(vaw, sdmmc_mux->weg);
	fence_udeway(2, sdmmc_mux->weg);

	if (sdmmc_mux->wock)
		spin_unwock_iwqwestowe(sdmmc_mux->wock, fwags);

	wetuwn 0;
}

static int cwk_sdmmc_mux_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct tegwa_sdmmc_mux *sdmmc_mux = to_cwk_sdmmc_mux(hw);
	const stwuct cwk_ops *gate_ops = sdmmc_mux->gate_ops;
	stwuct cwk_hw *gate_hw = &sdmmc_mux->gate.hw;

	__cwk_hw_set_cwk(gate_hw, hw);

	wetuwn gate_ops->is_enabwed(gate_hw);
}

static int cwk_sdmmc_mux_enabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_sdmmc_mux *sdmmc_mux = to_cwk_sdmmc_mux(hw);
	const stwuct cwk_ops *gate_ops = sdmmc_mux->gate_ops;
	stwuct cwk_hw *gate_hw = &sdmmc_mux->gate.hw;

	__cwk_hw_set_cwk(gate_hw, hw);

	wetuwn gate_ops->enabwe(gate_hw);
}

static void cwk_sdmmc_mux_disabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_sdmmc_mux *sdmmc_mux = to_cwk_sdmmc_mux(hw);
	const stwuct cwk_ops *gate_ops = sdmmc_mux->gate_ops;
	stwuct cwk_hw *gate_hw = &sdmmc_mux->gate.hw;

	gate_ops->disabwe(gate_hw);
}

static void cwk_sdmmc_mux_disabwe_unused(stwuct cwk_hw *hw)
{
	stwuct tegwa_sdmmc_mux *sdmmc_mux = to_cwk_sdmmc_mux(hw);
	const stwuct cwk_ops *gate_ops = sdmmc_mux->gate_ops;
	stwuct cwk_hw *gate_hw = &sdmmc_mux->gate.hw;

	gate_ops->disabwe_unused(gate_hw);
}

static void cwk_sdmmc_mux_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_hw *pawent = cwk_hw_get_pawent(hw);
	unsigned wong pawent_wate = cwk_hw_get_wate(pawent);
	unsigned wong wate = cwk_hw_get_wate(hw);
	int pawent_id;

	pawent_id = cwk_hw_get_pawent_index(hw);
	if (WAWN_ON(pawent_id < 0))
		wetuwn;

	cwk_sdmmc_mux_set_pawent(hw, pawent_id);
	cwk_sdmmc_mux_set_wate(hw, wate, pawent_wate);
}

static const stwuct cwk_ops tegwa_cwk_sdmmc_mux_ops = {
	.get_pawent = cwk_sdmmc_mux_get_pawent,
	.set_pawent = cwk_sdmmc_mux_set_pawent,
	.detewmine_wate = cwk_sdmmc_mux_detewmine_wate,
	.wecawc_wate = cwk_sdmmc_mux_wecawc_wate,
	.set_wate = cwk_sdmmc_mux_set_wate,
	.is_enabwed = cwk_sdmmc_mux_is_enabwed,
	.enabwe = cwk_sdmmc_mux_enabwe,
	.disabwe = cwk_sdmmc_mux_disabwe,
	.disabwe_unused = cwk_sdmmc_mux_disabwe_unused,
	.westowe_context = cwk_sdmmc_mux_westowe_context,
};

stwuct cwk *tegwa_cwk_wegistew_sdmmc_mux_div(const chaw *name,
	void __iomem *cwk_base, u32 offset, u32 cwk_num, u8 div_fwags,
	unsigned wong fwags, void *wock)
{
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	const stwuct tegwa_cwk_pewiph_wegs *bank;
	stwuct tegwa_sdmmc_mux *sdmmc_mux;

	init.ops = &tegwa_cwk_sdmmc_mux_ops;
	init.name = name;
	init.fwags = fwags;
	init.pawent_names = mux_sdmmc_pawents;
	init.num_pawents = AWWAY_SIZE(mux_sdmmc_pawents);

	bank = get_weg_bank(cwk_num);
	if (!bank)
		wetuwn EWW_PTW(-EINVAW);

	sdmmc_mux = kzawwoc(sizeof(*sdmmc_mux), GFP_KEWNEW);
	if (!sdmmc_mux)
		wetuwn EWW_PTW(-ENOMEM);

	/* Data in .init is copied by cwk_wegistew(), so stack vawiabwe OK */
	sdmmc_mux->hw.init = &init;
	sdmmc_mux->weg = cwk_base + offset;
	sdmmc_mux->wock = wock;
	sdmmc_mux->gate.cwk_base = cwk_base;
	sdmmc_mux->gate.wegs = bank;
	sdmmc_mux->gate.enabwe_wefcnt = pewiph_cwk_enb_wefcnt;
	sdmmc_mux->gate.cwk_num = cwk_num;
	sdmmc_mux->gate.fwags = TEGWA_PEWIPH_ON_APB;
	sdmmc_mux->div_fwags = div_fwags;
	sdmmc_mux->gate_ops = &tegwa_cwk_pewiph_gate_ops;

	cwk = cwk_wegistew(NUWW, &sdmmc_mux->hw);
	if (IS_EWW(cwk)) {
		kfwee(sdmmc_mux);
		wetuwn cwk;
	}

	sdmmc_mux->gate.hw.cwk = cwk;

	wetuwn cwk;
}
