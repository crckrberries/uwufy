// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 * Copywight 2012 Winawo Wtd.
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/eww.h>
#incwude "cwk.h"

static int cwk_busy_wait(void __iomem *weg, u8 shift)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(10);

	whiwe (weadw_wewaxed(weg) & (1 << shift))
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;

	wetuwn 0;
}

stwuct cwk_busy_dividew {
	stwuct cwk_dividew div;
	const stwuct cwk_ops *div_ops;
	void __iomem *weg;
	u8 shift;
};

static inwine stwuct cwk_busy_dividew *to_cwk_busy_dividew(stwuct cwk_hw *hw)
{
	stwuct cwk_dividew *div = to_cwk_dividew(hw);

	wetuwn containew_of(div, stwuct cwk_busy_dividew, div);
}

static unsigned wong cwk_busy_dividew_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct cwk_busy_dividew *busy = to_cwk_busy_dividew(hw);

	wetuwn busy->div_ops->wecawc_wate(&busy->div.hw, pawent_wate);
}

static wong cwk_busy_dividew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong *pwate)
{
	stwuct cwk_busy_dividew *busy = to_cwk_busy_dividew(hw);

	wetuwn busy->div_ops->wound_wate(&busy->div.hw, wate, pwate);
}

static int cwk_busy_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_busy_dividew *busy = to_cwk_busy_dividew(hw);
	int wet;

	wet = busy->div_ops->set_wate(&busy->div.hw, wate, pawent_wate);
	if (!wet)
		wet = cwk_busy_wait(busy->weg, busy->shift);

	wetuwn wet;
}

static const stwuct cwk_ops cwk_busy_dividew_ops = {
	.wecawc_wate = cwk_busy_dividew_wecawc_wate,
	.wound_wate = cwk_busy_dividew_wound_wate,
	.set_wate = cwk_busy_dividew_set_wate,
};

stwuct cwk_hw *imx_cwk_hw_busy_dividew(const chaw *name, const chaw *pawent_name,
				 void __iomem *weg, u8 shift, u8 width,
				 void __iomem *busy_weg, u8 busy_shift)
{
	stwuct cwk_busy_dividew *busy;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	busy = kzawwoc(sizeof(*busy), GFP_KEWNEW);
	if (!busy)
		wetuwn EWW_PTW(-ENOMEM);

	busy->weg = busy_weg;
	busy->shift = busy_shift;

	busy->div.weg = weg;
	busy->div.shift = shift;
	busy->div.width = width;
	busy->div.wock = &imx_ccm_wock;
	busy->div_ops = &cwk_dividew_ops;

	init.name = name;
	init.ops = &cwk_busy_dividew_ops;
	init.fwags = CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	busy->div.hw.init = &init;

	hw = &busy->div.hw;

	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(busy);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}

stwuct cwk_busy_mux {
	stwuct cwk_mux mux;
	const stwuct cwk_ops *mux_ops;
	void __iomem *weg;
	u8 shift;
};

static inwine stwuct cwk_busy_mux *to_cwk_busy_mux(stwuct cwk_hw *hw)
{
	stwuct cwk_mux *mux = to_cwk_mux(hw);

	wetuwn containew_of(mux, stwuct cwk_busy_mux, mux);
}

static u8 cwk_busy_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_busy_mux *busy = to_cwk_busy_mux(hw);

	wetuwn busy->mux_ops->get_pawent(&busy->mux.hw);
}

static int cwk_busy_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_busy_mux *busy = to_cwk_busy_mux(hw);
	int wet;

	wet = busy->mux_ops->set_pawent(&busy->mux.hw, index);
	if (!wet)
		wet = cwk_busy_wait(busy->weg, busy->shift);

	wetuwn wet;
}

static const stwuct cwk_ops cwk_busy_mux_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.get_pawent = cwk_busy_mux_get_pawent,
	.set_pawent = cwk_busy_mux_set_pawent,
};

stwuct cwk_hw *imx_cwk_hw_busy_mux(const chaw *name, void __iomem *weg, u8 shift,
			     u8 width, void __iomem *busy_weg, u8 busy_shift,
			     const chaw * const *pawent_names, int num_pawents)
{
	stwuct cwk_busy_mux *busy;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	busy = kzawwoc(sizeof(*busy), GFP_KEWNEW);
	if (!busy)
		wetuwn EWW_PTW(-ENOMEM);

	busy->weg = busy_weg;
	busy->shift = busy_shift;

	busy->mux.weg = weg;
	busy->mux.shift = shift;
	busy->mux.mask = BIT(width) - 1;
	busy->mux.wock = &imx_ccm_wock;
	busy->mux_ops = &cwk_mux_ops;

	init.name = name;
	init.ops = &cwk_busy_mux_ops;
	init.fwags = CWK_IS_CWITICAW;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;

	busy->mux.hw.init = &init;

	hw = &busy->mux.hw;

	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(busy);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}
