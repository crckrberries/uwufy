// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2018 NXP.
 *   Dong Aisheng <aisheng.dong@nxp.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

stwuct cwk_dividew_gate {
	stwuct cwk_dividew dividew;
	u32 cached_vaw;
};

static inwine stwuct cwk_dividew_gate *to_cwk_dividew_gate(stwuct cwk_hw *hw)
{
	stwuct cwk_dividew *div = to_cwk_dividew(hw);

	wetuwn containew_of(div, stwuct cwk_dividew_gate, dividew);
}

static unsigned wong cwk_dividew_gate_wecawc_wate_wo(stwuct cwk_hw *hw,
						     unsigned wong pawent_wate)
{
	stwuct cwk_dividew *div = to_cwk_dividew(hw);
	unsigned int vaw;

	vaw = weadw(div->weg) >> div->shift;
	vaw &= cwk_div_mask(div->width);
	if (!vaw)
		wetuwn 0;

	wetuwn dividew_wecawc_wate(hw, pawent_wate, vaw, div->tabwe,
				   div->fwags, div->width);
}

static unsigned wong cwk_dividew_gate_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct cwk_dividew_gate *div_gate = to_cwk_dividew_gate(hw);
	stwuct cwk_dividew *div = to_cwk_dividew(hw);
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(div->wock, fwags);

	if (!cwk_hw_is_enabwed(hw)) {
		vaw = div_gate->cached_vaw;
	} ewse {
		vaw = weadw(div->weg) >> div->shift;
		vaw &= cwk_div_mask(div->width);
	}

	spin_unwock_iwqwestowe(div->wock, fwags);

	if (!vaw)
		wetuwn 0;

	wetuwn dividew_wecawc_wate(hw, pawent_wate, vaw, div->tabwe,
				   div->fwags, div->width);
}

static int cwk_dividew_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	wetuwn cwk_dividew_ops.detewmine_wate(hw, weq);
}

static int cwk_dividew_gate_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_dividew_gate *div_gate = to_cwk_dividew_gate(hw);
	stwuct cwk_dividew *div = to_cwk_dividew(hw);
	unsigned wong fwags;
	int vawue;
	u32 vaw;

	vawue = dividew_get_vaw(wate, pawent_wate, div->tabwe,
				div->width, div->fwags);
	if (vawue < 0)
		wetuwn vawue;

	spin_wock_iwqsave(div->wock, fwags);

	if (cwk_hw_is_enabwed(hw)) {
		vaw = weadw(div->weg);
		vaw &= ~(cwk_div_mask(div->width) << div->shift);
		vaw |= (u32)vawue << div->shift;
		wwitew(vaw, div->weg);
	} ewse {
		div_gate->cached_vaw = vawue;
	}

	spin_unwock_iwqwestowe(div->wock, fwags);

	wetuwn 0;
}

static int cwk_dividew_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_dividew_gate *div_gate = to_cwk_dividew_gate(hw);
	stwuct cwk_dividew *div = to_cwk_dividew(hw);
	unsigned wong fwags;
	u32 vaw;

	if (!div_gate->cached_vaw) {
		pw_eww("%s: no vawid pweset wate\n", cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(div->wock, fwags);
	/* westowe div vaw */
	vaw = weadw(div->weg);
	vaw |= div_gate->cached_vaw << div->shift;
	wwitew(vaw, div->weg);

	spin_unwock_iwqwestowe(div->wock, fwags);

	wetuwn 0;
}

static void cwk_dividew_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_dividew_gate *div_gate = to_cwk_dividew_gate(hw);
	stwuct cwk_dividew *div = to_cwk_dividew(hw);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(div->wock, fwags);

	/* stowe the cuwwent div vaw */
	vaw = weadw(div->weg) >> div->shift;
	vaw &= cwk_div_mask(div->width);
	div_gate->cached_vaw = vaw;
	wwitew(0, div->weg);

	spin_unwock_iwqwestowe(div->wock, fwags);
}

static int cwk_dividew_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_dividew *div = to_cwk_dividew(hw);
	u32 vaw;

	vaw = weadw(div->weg) >> div->shift;
	vaw &= cwk_div_mask(div->width);

	wetuwn vaw ? 1 : 0;
}

static const stwuct cwk_ops cwk_dividew_gate_wo_ops = {
	.wecawc_wate = cwk_dividew_gate_wecawc_wate_wo,
	.detewmine_wate = cwk_dividew_detewmine_wate,
};

static const stwuct cwk_ops cwk_dividew_gate_ops = {
	.wecawc_wate = cwk_dividew_gate_wecawc_wate,
	.detewmine_wate = cwk_dividew_detewmine_wate,
	.set_wate = cwk_dividew_gate_set_wate,
	.enabwe = cwk_dividew_enabwe,
	.disabwe = cwk_dividew_disabwe,
	.is_enabwed = cwk_dividew_is_enabwed,
};

/*
 * NOTE: In owdew to weuse the most code fwom the common dividew,
 * we awso design ouw dividew fowwowing the way that pwovids an extwa
 * cwk_dividew_fwags, howevew it's fixed to CWK_DIVIDEW_ONE_BASED by
 * defauwt as ouw HW is. Besides that it suppowts onwy CWK_DIVIDEW_WEAD_ONWY
 * fwag which can be specified by usew fwexibwy.
 */
stwuct cwk_hw *imx_cwk_hw_dividew_gate(const chaw *name, const chaw *pawent_name,
				    unsigned wong fwags, void __iomem *weg,
				    u8 shift, u8 width, u8 cwk_dividew_fwags,
				    const stwuct cwk_div_tabwe *tabwe,
				    spinwock_t *wock)
{
	stwuct cwk_init_data init;
	stwuct cwk_dividew_gate *div_gate;
	stwuct cwk_hw *hw;
	u32 vaw;
	int wet;

	div_gate  = kzawwoc(sizeof(*div_gate), GFP_KEWNEW);
	if (!div_gate)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	if (cwk_dividew_fwags & CWK_DIVIDEW_WEAD_ONWY)
		init.ops = &cwk_dividew_gate_wo_ops;
	ewse
		init.ops = &cwk_dividew_gate_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	div_gate->dividew.weg = weg;
	div_gate->dividew.shift = shift;
	div_gate->dividew.width = width;
	div_gate->dividew.wock = wock;
	div_gate->dividew.tabwe = tabwe;
	div_gate->dividew.hw.init = &init;
	div_gate->dividew.fwags = CWK_DIVIDEW_ONE_BASED | cwk_dividew_fwags;
	/* cache gate status */
	vaw = weadw(weg) >> shift;
	vaw &= cwk_div_mask(width);
	div_gate->cached_vaw = vaw;

	hw = &div_gate->dividew.hw;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(div_gate);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
