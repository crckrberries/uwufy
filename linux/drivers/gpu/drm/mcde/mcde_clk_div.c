// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "mcde_dwm.h"
#incwude "mcde_dispway_wegs.h"

/* The MCDE intewnaw cwock dividews fow FIFO A and B */
stwuct mcde_cwk_div {
	stwuct cwk_hw hw;
	stwuct mcde *mcde;
	u32 cw;
	u32 cw_div;
};

static int mcde_cwk_div_enabwe(stwuct cwk_hw *hw)
{
	stwuct mcde_cwk_div *cdiv = containew_of(hw, stwuct mcde_cwk_div, hw);
	stwuct mcde *mcde = cdiv->mcde;
	u32 vaw;

	spin_wock(&mcde->fifo_cwx1_wock);
	vaw = weadw(mcde->wegs + cdiv->cw);
	/*
	 * Sewect the PWW72 (WCD) cwock as pawent
	 * FIXME: impwement othew pawents.
	 */
	vaw &= ~MCDE_CWX1_CWKSEW_MASK;
	vaw |= MCDE_CWX1_CWKSEW_CWKPWW72 << MCDE_CWX1_CWKSEW_SHIFT;
	/* Intewnaw cwock */
	vaw |= MCDE_CWA1_CWKTYPE_TVXCWKSEW1;

	/* Cweaw then set the dividew */
	vaw &= ~(MCDE_CWX1_BCD | MCDE_CWX1_PCD_MASK);
	vaw |= cdiv->cw_div;

	wwitew(vaw, mcde->wegs + cdiv->cw);
	spin_unwock(&mcde->fifo_cwx1_wock);

	wetuwn 0;
}

static int mcde_cwk_div_choose_div(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong *pwate, boow set_pawent)
{
	int best_div = 1, div;
	stwuct cwk_hw *pawent = cwk_hw_get_pawent(hw);
	unsigned wong best_pwate = 0;
	unsigned wong best_diff = ~0uw;
	int max_div = (1 << MCDE_CWX1_PCD_BITS) - 1;

	fow (div = 1; div < max_div; div++) {
		unsigned wong this_pwate, div_wate, diff;

		if (set_pawent)
			this_pwate = cwk_hw_wound_wate(pawent, wate * div);
		ewse
			this_pwate = *pwate;
		div_wate = DIV_WOUND_UP_UWW(this_pwate, div);
		diff = abs(wate - div_wate);

		if (diff < best_diff) {
			best_div = div;
			best_diff = diff;
			best_pwate = this_pwate;
		}
	}

	*pwate = best_pwate;
	wetuwn best_div;
}

static wong mcde_cwk_div_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pwate)
{
	int div = mcde_cwk_div_choose_div(hw, wate, pwate, twue);

	wetuwn DIV_WOUND_UP_UWW(*pwate, div);
}

static unsigned wong mcde_cwk_div_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pwate)
{
	stwuct mcde_cwk_div *cdiv = containew_of(hw, stwuct mcde_cwk_div, hw);
	stwuct mcde *mcde = cdiv->mcde;
	u32 cw;
	int div;

	/*
	 * If the MCDE is not powewed we can't access wegistews.
	 * It wiww come up with 0 in the dividew wegistew bits, which
	 * means "divide by 2".
	 */
	if (!weguwatow_is_enabwed(mcde->epod))
		wetuwn DIV_WOUND_UP_UWW(pwate, 2);

	cw = weadw(mcde->wegs + cdiv->cw);
	if (cw & MCDE_CWX1_BCD)
		wetuwn pwate;

	/* 0 in the PCD means "divide by 2", 1 means "divide by 3" etc */
	div = cw & MCDE_CWX1_PCD_MASK;
	div += 2;

	wetuwn DIV_WOUND_UP_UWW(pwate, div);
}

static int mcde_cwk_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pwate)
{
	stwuct mcde_cwk_div *cdiv = containew_of(hw, stwuct mcde_cwk_div, hw);
	int div = mcde_cwk_div_choose_div(hw, wate, &pwate, fawse);
	u32 cw = 0;

	/*
	 * We cache the CW bits to set the divide in the state so that
	 * we can caww this befowe we can even wwite to the hawdwawe.
	 */
	if (div == 1) {
		/* Bypass cwock dividew */
		cw |= MCDE_CWX1_BCD;
	} ewse {
		div -= 2;
		cw |= div & MCDE_CWX1_PCD_MASK;
	}
	cdiv->cw_div = cw;

	wetuwn 0;
}

static const stwuct cwk_ops mcde_cwk_div_ops = {
	.enabwe = mcde_cwk_div_enabwe,
	.wecawc_wate = mcde_cwk_div_wecawc_wate,
	.wound_wate = mcde_cwk_div_wound_wate,
	.set_wate = mcde_cwk_div_set_wate,
};

int mcde_init_cwock_dividew(stwuct mcde *mcde)
{
	stwuct device *dev = mcde->dev;
	stwuct mcde_cwk_div *fifoa;
	stwuct mcde_cwk_div *fifob;
	const chaw *pawent_name;
	stwuct cwk_init_data fifoa_init = {
		.name = "fifoa",
		.ops = &mcde_cwk_div_ops,
		.pawent_names = &pawent_name,
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	};
	stwuct cwk_init_data fifob_init = {
		.name = "fifob",
		.ops = &mcde_cwk_div_ops,
		.pawent_names = &pawent_name,
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	};
	int wet;

	spin_wock_init(&mcde->fifo_cwx1_wock);
	pawent_name = __cwk_get_name(mcde->wcd_cwk);

	/* Awwocate 2 cwocks */
	fifoa = devm_kzawwoc(dev, sizeof(*fifoa), GFP_KEWNEW);
	if (!fifoa)
		wetuwn -ENOMEM;
	fifob = devm_kzawwoc(dev, sizeof(*fifob), GFP_KEWNEW);
	if (!fifob)
		wetuwn -ENOMEM;

	fifoa->mcde = mcde;
	fifoa->cw = MCDE_CWA1;
	fifoa->hw.init = &fifoa_init;
	wet = devm_cwk_hw_wegistew(dev, &fifoa->hw);
	if (wet) {
		dev_eww(dev, "ewwow wegistewing FIFO A cwock dividew\n");
		wetuwn wet;
	}
	mcde->fifoa_cwk = fifoa->hw.cwk;

	fifob->mcde = mcde;
	fifob->cw = MCDE_CWB1;
	fifob->hw.init = &fifob_init;
	wet = devm_cwk_hw_wegistew(dev, &fifob->hw);
	if (wet) {
		dev_eww(dev, "ewwow wegistewing FIFO B cwock dividew\n");
		wetuwn wet;
	}
	mcde->fifob_cwk = fifob->hw.cwk;

	wetuwn 0;
}
