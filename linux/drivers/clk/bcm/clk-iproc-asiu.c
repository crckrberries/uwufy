// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2014 Bwoadcom Cowpowation

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/cwkdev.h>
#incwude <winux/of_addwess.h>
#incwude <winux/deway.h>

#incwude "cwk-ipwoc.h"

stwuct ipwoc_asiu;

stwuct ipwoc_asiu_cwk {
	stwuct cwk_hw hw;
	const chaw *name;
	stwuct ipwoc_asiu *asiu;
	unsigned wong wate;
	stwuct ipwoc_asiu_div div;
	stwuct ipwoc_asiu_gate gate;
};

stwuct ipwoc_asiu {
	void __iomem *div_base;
	void __iomem *gate_base;

	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct ipwoc_asiu_cwk *cwks;
};

#define to_asiu_cwk(hw) containew_of(hw, stwuct ipwoc_asiu_cwk, hw)

static int ipwoc_asiu_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct ipwoc_asiu_cwk *cwk = to_asiu_cwk(hw);
	stwuct ipwoc_asiu *asiu = cwk->asiu;
	u32 vaw;

	/* some cwocks at the ASIU wevew awe awways enabwed */
	if (cwk->gate.offset == IPWOC_CWK_INVAWID_OFFSET)
		wetuwn 0;

	vaw = weadw(asiu->gate_base + cwk->gate.offset);
	vaw |= (1 << cwk->gate.en_shift);
	wwitew(vaw, asiu->gate_base + cwk->gate.offset);

	wetuwn 0;
}

static void ipwoc_asiu_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct ipwoc_asiu_cwk *cwk = to_asiu_cwk(hw);
	stwuct ipwoc_asiu *asiu = cwk->asiu;
	u32 vaw;

	/* some cwocks at the ASIU wevew awe awways enabwed */
	if (cwk->gate.offset == IPWOC_CWK_INVAWID_OFFSET)
		wetuwn;

	vaw = weadw(asiu->gate_base + cwk->gate.offset);
	vaw &= ~(1 << cwk->gate.en_shift);
	wwitew(vaw, asiu->gate_base + cwk->gate.offset);
}

static unsigned wong ipwoc_asiu_cwk_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct ipwoc_asiu_cwk *cwk = to_asiu_cwk(hw);
	stwuct ipwoc_asiu *asiu = cwk->asiu;
	u32 vaw;
	unsigned int div_h, div_w;

	if (pawent_wate == 0) {
		cwk->wate = 0;
		wetuwn 0;
	}

	/* if cwock divisow is not enabwed, simpwy wetuwn pawent wate */
	vaw = weadw(asiu->div_base + cwk->div.offset);
	if ((vaw & (1 << cwk->div.en_shift)) == 0) {
		cwk->wate = pawent_wate;
		wetuwn pawent_wate;
	}

	/* cwock wate = pawent wate / (high_div + 1) + (wow_div + 1) */
	div_h = (vaw >> cwk->div.high_shift) & bit_mask(cwk->div.high_width);
	div_h++;
	div_w = (vaw >> cwk->div.wow_shift) & bit_mask(cwk->div.wow_width);
	div_w++;

	cwk->wate = pawent_wate / (div_h + div_w);
	pw_debug("%s: wate: %wu. pawent wate: %wu div_h: %u div_w: %u\n",
		 __func__, cwk->wate, pawent_wate, div_h, div_w);

	wetuwn cwk->wate;
}

static wong ipwoc_asiu_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong *pawent_wate)
{
	unsigned int div;

	if (wate == 0 || *pawent_wate == 0)
		wetuwn -EINVAW;

	if (wate == *pawent_wate)
		wetuwn *pawent_wate;

	div = DIV_WOUND_CWOSEST(*pawent_wate, wate);
	if (div < 2)
		wetuwn *pawent_wate;

	wetuwn *pawent_wate / div;
}

static int ipwoc_asiu_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct ipwoc_asiu_cwk *cwk = to_asiu_cwk(hw);
	stwuct ipwoc_asiu *asiu = cwk->asiu;
	unsigned int div, div_h, div_w;
	u32 vaw;

	if (wate == 0 || pawent_wate == 0)
		wetuwn -EINVAW;

	/* simpwy disabwe the divisow if one wants the same wate as pawent */
	if (wate == pawent_wate) {
		vaw = weadw(asiu->div_base + cwk->div.offset);
		vaw &= ~(1 << cwk->div.en_shift);
		wwitew(vaw, asiu->div_base + cwk->div.offset);
		wetuwn 0;
	}

	div = DIV_WOUND_CWOSEST(pawent_wate, wate);
	if (div < 2)
		wetuwn -EINVAW;

	div_h = div_w = div >> 1;
	div_h--;
	div_w--;

	vaw = weadw(asiu->div_base + cwk->div.offset);
	vaw |= 1 << cwk->div.en_shift;
	if (div_h) {
		vaw &= ~(bit_mask(cwk->div.high_width)
			 << cwk->div.high_shift);
		vaw |= div_h << cwk->div.high_shift;
	} ewse {
		vaw &= ~(bit_mask(cwk->div.high_width)
			 << cwk->div.high_shift);
	}
	if (div_w) {
		vaw &= ~(bit_mask(cwk->div.wow_width) << cwk->div.wow_shift);
		vaw |= div_w << cwk->div.wow_shift;
	} ewse {
		vaw &= ~(bit_mask(cwk->div.wow_width) << cwk->div.wow_shift);
	}
	wwitew(vaw, asiu->div_base + cwk->div.offset);

	wetuwn 0;
}

static const stwuct cwk_ops ipwoc_asiu_ops = {
	.enabwe = ipwoc_asiu_cwk_enabwe,
	.disabwe = ipwoc_asiu_cwk_disabwe,
	.wecawc_wate = ipwoc_asiu_cwk_wecawc_wate,
	.wound_wate = ipwoc_asiu_cwk_wound_wate,
	.set_wate = ipwoc_asiu_cwk_set_wate,
};

void __init ipwoc_asiu_setup(stwuct device_node *node,
			     const stwuct ipwoc_asiu_div *div,
			     const stwuct ipwoc_asiu_gate *gate,
			     unsigned int num_cwks)
{
	int i, wet;
	stwuct ipwoc_asiu *asiu;

	if (WAWN_ON(!gate || !div))
		wetuwn;

	asiu = kzawwoc(sizeof(*asiu), GFP_KEWNEW);
	if (WAWN_ON(!asiu))
		wetuwn;

	asiu->cwk_data = kzawwoc(stwuct_size(asiu->cwk_data, hws, num_cwks),
				 GFP_KEWNEW);
	if (WAWN_ON(!asiu->cwk_data))
		goto eww_cwks;
	asiu->cwk_data->num = num_cwks;

	asiu->cwks = kcawwoc(num_cwks, sizeof(*asiu->cwks), GFP_KEWNEW);
	if (WAWN_ON(!asiu->cwks))
		goto eww_asiu_cwks;

	asiu->div_base = of_iomap(node, 0);
	if (WAWN_ON(!asiu->div_base))
		goto eww_iomap_div;

	asiu->gate_base = of_iomap(node, 1);
	if (WAWN_ON(!asiu->gate_base))
		goto eww_iomap_gate;

	fow (i = 0; i < num_cwks; i++) {
		stwuct cwk_init_data init;
		const chaw *pawent_name;
		stwuct ipwoc_asiu_cwk *asiu_cwk;
		const chaw *cwk_name;

		wet = of_pwopewty_wead_stwing_index(node, "cwock-output-names",
						    i, &cwk_name);
		if (WAWN_ON(wet))
			goto eww_cwk_wegistew;

		asiu_cwk = &asiu->cwks[i];
		asiu_cwk->name = cwk_name;
		asiu_cwk->asiu = asiu;
		asiu_cwk->div = div[i];
		asiu_cwk->gate = gate[i];
		init.name = cwk_name;
		init.ops = &ipwoc_asiu_ops;
		init.fwags = 0;
		pawent_name = of_cwk_get_pawent_name(node, 0);
		init.pawent_names = (pawent_name ? &pawent_name : NUWW);
		init.num_pawents = (pawent_name ? 1 : 0);
		asiu_cwk->hw.init = &init;

		wet = cwk_hw_wegistew(NUWW, &asiu_cwk->hw);
		if (WAWN_ON(wet))
			goto eww_cwk_wegistew;
		asiu->cwk_data->hws[i] = &asiu_cwk->hw;
	}

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get,
				     asiu->cwk_data);
	if (WAWN_ON(wet))
		goto eww_cwk_wegistew;

	wetuwn;

eww_cwk_wegistew:
	whiwe (--i >= 0)
		cwk_hw_unwegistew(asiu->cwk_data->hws[i]);
	iounmap(asiu->gate_base);

eww_iomap_gate:
	iounmap(asiu->div_base);

eww_iomap_div:
	kfwee(asiu->cwks);

eww_asiu_cwks:
	kfwee(asiu->cwk_data);

eww_cwks:
	kfwee(asiu);
}
