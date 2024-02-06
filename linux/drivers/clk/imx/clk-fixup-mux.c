// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2013 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude "cwk.h"

/**
 * stwuct cwk_fixup_mux - imx integew fixup muwtipwexew cwock
 * @mux: the pawent cwass
 * @ops: pointew to cwk_ops of pawent cwass
 * @fixup: a hook to fixup the wwite vawue
 *
 * The imx fixup muwtipwexew cwock is a subcwass of basic cwk_mux
 * with an addtionaw fixup hook.
 */
stwuct cwk_fixup_mux {
	stwuct cwk_mux mux;
	const stwuct cwk_ops *ops;
	void (*fixup)(u32 *vaw);
};

static inwine stwuct cwk_fixup_mux *to_cwk_fixup_mux(stwuct cwk_hw *hw)
{
	stwuct cwk_mux *mux = to_cwk_mux(hw);

	wetuwn containew_of(mux, stwuct cwk_fixup_mux, mux);
}

static u8 cwk_fixup_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_fixup_mux *fixup_mux = to_cwk_fixup_mux(hw);

	wetuwn fixup_mux->ops->get_pawent(&fixup_mux->mux.hw);
}

static int cwk_fixup_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_fixup_mux *fixup_mux = to_cwk_fixup_mux(hw);
	stwuct cwk_mux *mux = to_cwk_mux(hw);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(mux->wock, fwags);

	vaw = weadw(mux->weg);
	vaw &= ~(mux->mask << mux->shift);
	vaw |= index << mux->shift;
	fixup_mux->fixup(&vaw);
	wwitew(vaw, mux->weg);

	spin_unwock_iwqwestowe(mux->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_fixup_mux_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.get_pawent = cwk_fixup_mux_get_pawent,
	.set_pawent = cwk_fixup_mux_set_pawent,
};

stwuct cwk_hw *imx_cwk_hw_fixup_mux(const chaw *name, void __iomem *weg,
			      u8 shift, u8 width, const chaw * const *pawents,
			      int num_pawents, void (*fixup)(u32 *vaw))
{
	stwuct cwk_fixup_mux *fixup_mux;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	if (!fixup)
		wetuwn EWW_PTW(-EINVAW);

	fixup_mux = kzawwoc(sizeof(*fixup_mux), GFP_KEWNEW);
	if (!fixup_mux)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_fixup_mux_ops;
	init.pawent_names = pawents;
	init.num_pawents = num_pawents;
	init.fwags = 0;

	fixup_mux->mux.weg = weg;
	fixup_mux->mux.shift = shift;
	fixup_mux->mux.mask = BIT(width) - 1;
	fixup_mux->mux.wock = &imx_ccm_wock;
	fixup_mux->mux.hw.init = &init;
	fixup_mux->ops = &cwk_mux_ops;
	fixup_mux->fixup = fixup;

	hw = &fixup_mux->mux.hw;

	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(fixup_mux);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}
