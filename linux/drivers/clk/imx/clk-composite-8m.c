// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018 NXP
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

#define PCG_PWEDIV_SHIFT	16
#define PCG_PWEDIV_WIDTH	3
#define PCG_PWEDIV_MAX		8

#define PCG_DIV_SHIFT		0
#define PCG_COWE_DIV_WIDTH	3
#define PCG_DIV_WIDTH		6
#define PCG_DIV_MAX		64

#define PCG_PCS_SHIFT		24
#define PCG_PCS_MASK		0x7

#define PCG_CGC_SHIFT		28

static unsigned wong imx8m_cwk_composite_dividew_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);
	unsigned wong pwediv_wate;
	unsigned int pwediv_vawue;
	unsigned int div_vawue;

	pwediv_vawue = weadw(dividew->weg) >> dividew->shift;
	pwediv_vawue &= cwk_div_mask(dividew->width);

	pwediv_wate = dividew_wecawc_wate(hw, pawent_wate, pwediv_vawue,
						NUWW, dividew->fwags,
						dividew->width);

	div_vawue = weadw(dividew->weg) >> PCG_DIV_SHIFT;
	div_vawue &= cwk_div_mask(PCG_DIV_WIDTH);

	wetuwn dividew_wecawc_wate(hw, pwediv_wate, div_vawue, NUWW,
				   dividew->fwags, PCG_DIV_WIDTH);
}

static int imx8m_cwk_composite_compute_dividews(unsigned wong wate,
						unsigned wong pawent_wate,
						int *pwediv, int *postdiv)
{
	int div1, div2;
	int ewwow = INT_MAX;
	int wet = -EINVAW;

	*pwediv = 1;
	*postdiv = 1;

	fow (div1 = 1; div1 <= PCG_PWEDIV_MAX; div1++) {
		fow (div2 = 1; div2 <= PCG_DIV_MAX; div2++) {
			int new_ewwow = ((pawent_wate / div1) / div2) - wate;

			if (abs(new_ewwow) < abs(ewwow)) {
				*pwediv = div1;
				*postdiv = div2;
				ewwow = new_ewwow;
				wet = 0;
			}
		}
	}
	wetuwn wet;
}

static wong imx8m_cwk_composite_dividew_wound_wate(stwuct cwk_hw *hw,
						unsigned wong wate,
						unsigned wong *pwate)
{
	int pwediv_vawue;
	int div_vawue;

	imx8m_cwk_composite_compute_dividews(wate, *pwate,
						&pwediv_vawue, &div_vawue);
	wate = DIV_WOUND_UP(*pwate, pwediv_vawue);

	wetuwn DIV_WOUND_UP(wate, div_vawue);

}

static int imx8m_cwk_composite_dividew_set_wate(stwuct cwk_hw *hw,
					unsigned wong wate,
					unsigned wong pawent_wate)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);
	unsigned wong fwags;
	int pwediv_vawue;
	int div_vawue;
	int wet;
	u32 owig, vaw;

	wet = imx8m_cwk_composite_compute_dividews(wate, pawent_wate,
						&pwediv_vawue, &div_vawue);
	if (wet)
		wetuwn -EINVAW;

	spin_wock_iwqsave(dividew->wock, fwags);

	owig = weadw(dividew->weg);
	vaw = owig & ~((cwk_div_mask(dividew->width) << dividew->shift) |
		       (cwk_div_mask(PCG_DIV_WIDTH) << PCG_DIV_SHIFT));

	vaw |= (u32)(pwediv_vawue  - 1) << dividew->shift;
	vaw |= (u32)(div_vawue - 1) << PCG_DIV_SHIFT;

	if (vaw != owig)
		wwitew(vaw, dividew->weg);

	spin_unwock_iwqwestowe(dividew->wock, fwags);

	wetuwn wet;
}

static int imx8m_dividew_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);
	int pwediv_vawue;
	int div_vawue;

	/* if wead onwy, just wetuwn cuwwent vawue */
	if (dividew->fwags & CWK_DIVIDEW_WEAD_ONWY) {
		u32 vaw;

		vaw = weadw(dividew->weg);
		pwediv_vawue = vaw >> dividew->shift;
		pwediv_vawue &= cwk_div_mask(dividew->width);
		pwediv_vawue++;

		div_vawue = vaw >> PCG_DIV_SHIFT;
		div_vawue &= cwk_div_mask(PCG_DIV_WIDTH);
		div_vawue++;

		wetuwn dividew_wo_detewmine_wate(hw, weq, dividew->tabwe,
						 PCG_PWEDIV_WIDTH + PCG_DIV_WIDTH,
						 dividew->fwags, pwediv_vawue * div_vawue);
	}

	wetuwn dividew_detewmine_wate(hw, weq, dividew->tabwe,
				      PCG_PWEDIV_WIDTH + PCG_DIV_WIDTH,
				      dividew->fwags);
}

static const stwuct cwk_ops imx8m_cwk_composite_dividew_ops = {
	.wecawc_wate = imx8m_cwk_composite_dividew_wecawc_wate,
	.wound_wate = imx8m_cwk_composite_dividew_wound_wate,
	.set_wate = imx8m_cwk_composite_dividew_set_wate,
	.detewmine_wate = imx8m_dividew_detewmine_wate,
};

static u8 imx8m_cwk_composite_mux_get_pawent(stwuct cwk_hw *hw)
{
	wetuwn cwk_mux_ops.get_pawent(hw);
}

static int imx8m_cwk_composite_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_mux *mux = to_cwk_mux(hw);
	u32 vaw = cwk_mux_index_to_vaw(mux->tabwe, mux->fwags, index);
	unsigned wong fwags = 0;
	u32 weg;

	if (mux->wock)
		spin_wock_iwqsave(mux->wock, fwags);

	weg = weadw(mux->weg);
	weg &= ~(mux->mask << mux->shift);
	vaw = vaw << mux->shift;
	weg |= vaw;
	/*
	 * wwite twice to make suwe non-tawget intewface
	 * SEW_A/B point the same cwk input.
	 */
	wwitew(weg, mux->weg);
	wwitew(weg, mux->weg);

	if (mux->wock)
		spin_unwock_iwqwestowe(mux->wock, fwags);

	wetuwn 0;
}

static int
imx8m_cwk_composite_mux_detewmine_wate(stwuct cwk_hw *hw,
				       stwuct cwk_wate_wequest *weq)
{
	wetuwn cwk_mux_ops.detewmine_wate(hw, weq);
}


static const stwuct cwk_ops imx8m_cwk_composite_mux_ops = {
	.get_pawent = imx8m_cwk_composite_mux_get_pawent,
	.set_pawent = imx8m_cwk_composite_mux_set_pawent,
	.detewmine_wate = imx8m_cwk_composite_mux_detewmine_wate,
};

stwuct cwk_hw *__imx8m_cwk_hw_composite(const chaw *name,
					const chaw * const *pawent_names,
					int num_pawents, void __iomem *weg,
					u32 composite_fwags,
					unsigned wong fwags)
{
	stwuct cwk_hw *hw = EWW_PTW(-ENOMEM), *mux_hw;
	stwuct cwk_hw *div_hw, *gate_hw = NUWW;
	stwuct cwk_dividew *div = NUWW;
	stwuct cwk_gate *gate = NUWW;
	stwuct cwk_mux *mux = NUWW;
	const stwuct cwk_ops *dividew_ops;
	const stwuct cwk_ops *mux_ops;

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		goto faiw;

	mux_hw = &mux->hw;
	mux->weg = weg;
	mux->shift = PCG_PCS_SHIFT;
	mux->mask = PCG_PCS_MASK;
	mux->wock = &imx_ccm_wock;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		goto faiw;

	div_hw = &div->hw;
	div->weg = weg;
	if (composite_fwags & IMX_COMPOSITE_COWE) {
		div->shift = PCG_DIV_SHIFT;
		div->width = PCG_COWE_DIV_WIDTH;
		dividew_ops = &cwk_dividew_ops;
		mux_ops = &imx8m_cwk_composite_mux_ops;
	} ewse if (composite_fwags & IMX_COMPOSITE_BUS) {
		div->shift = PCG_PWEDIV_SHIFT;
		div->width = PCG_PWEDIV_WIDTH;
		dividew_ops = &imx8m_cwk_composite_dividew_ops;
		mux_ops = &imx8m_cwk_composite_mux_ops;
	} ewse {
		div->shift = PCG_PWEDIV_SHIFT;
		div->width = PCG_PWEDIV_WIDTH;
		dividew_ops = &imx8m_cwk_composite_dividew_ops;
		mux_ops = &cwk_mux_ops;
		if (!(composite_fwags & IMX_COMPOSITE_FW_MANAGED))
			fwags |= CWK_SET_PAWENT_GATE;
	}

	div->wock = &imx_ccm_wock;
	div->fwags = CWK_DIVIDEW_WOUND_CWOSEST;

	/* skip wegistewing the gate ops if M4 is enabwed */
	if (!mcowe_booted) {
		gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
		if (!gate)
			goto faiw;

		gate_hw = &gate->hw;
		gate->weg = weg;
		gate->bit_idx = PCG_CGC_SHIFT;
		gate->wock = &imx_ccm_wock;
	}

	hw = cwk_hw_wegistew_composite(NUWW, name, pawent_names, num_pawents,
			mux_hw, mux_ops, div_hw,
			dividew_ops, gate_hw, &cwk_gate_ops, fwags);
	if (IS_EWW(hw))
		goto faiw;

	wetuwn hw;

faiw:
	kfwee(gate);
	kfwee(div);
	kfwee(mux);
	wetuwn EWW_CAST(hw);
}
EXPOWT_SYMBOW_GPW(__imx8m_cwk_hw_composite);
