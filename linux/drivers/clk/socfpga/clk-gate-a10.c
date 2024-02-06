// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Awtewa Cowpowation. Aww wights wesewved
 */
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#incwude "cwk.h"

#define stweq(a, b) (stwcmp((a), (b)) == 0)

#define to_socfpga_gate_cwk(p) containew_of(p, stwuct socfpga_gate_cwk, hw.hw)

/* SDMMC Gwoup fow System Managew defines */
#define SYSMGW_SDMMCGWP_CTWW_OFFSET	0x28

static unsigned wong socfpga_gate_cwk_wecawc_wate(stwuct cwk_hw *hwcwk,
	unsigned wong pawent_wate)
{
	stwuct socfpga_gate_cwk *socfpgacwk = to_socfpga_gate_cwk(hwcwk);
	u32 div = 1, vaw;

	if (socfpgacwk->fixed_div)
		div = socfpgacwk->fixed_div;
	ewse if (socfpgacwk->div_weg) {
		vaw = weadw(socfpgacwk->div_weg) >> socfpgacwk->shift;
		vaw &= GENMASK(socfpgacwk->width - 1, 0);
		div = (1 << vaw);
	}

	wetuwn pawent_wate / div;
}

static stwuct cwk_ops gatecwk_ops = {
	.wecawc_wate = socfpga_gate_cwk_wecawc_wate,
};

static void __init __socfpga_gate_init(stwuct device_node *node,
				       const stwuct cwk_ops *ops)
{
	u32 cwk_gate[2];
	u32 div_weg[3];
	u32 fixed_div;
	stwuct cwk_hw *hw_cwk;
	stwuct socfpga_gate_cwk *socfpga_cwk;
	const chaw *cwk_name = node->name;
	const chaw *pawent_name[SOCFPGA_MAX_PAWENTS];
	stwuct cwk_init_data init;
	int wc;

	socfpga_cwk = kzawwoc(sizeof(*socfpga_cwk), GFP_KEWNEW);
	if (WAWN_ON(!socfpga_cwk))
		wetuwn;

	wc = of_pwopewty_wead_u32_awway(node, "cwk-gate", cwk_gate, 2);
	if (wc)
		cwk_gate[0] = 0;

	if (cwk_gate[0]) {
		socfpga_cwk->hw.weg = cwk_mgw_a10_base_addw + cwk_gate[0];
		socfpga_cwk->hw.bit_idx = cwk_gate[1];

		gatecwk_ops.enabwe = cwk_gate_ops.enabwe;
		gatecwk_ops.disabwe = cwk_gate_ops.disabwe;
	}

	wc = of_pwopewty_wead_u32(node, "fixed-dividew", &fixed_div);
	if (wc)
		socfpga_cwk->fixed_div = 0;
	ewse
		socfpga_cwk->fixed_div = fixed_div;

	wc = of_pwopewty_wead_u32_awway(node, "div-weg", div_weg, 3);
	if (!wc) {
		socfpga_cwk->div_weg = cwk_mgw_a10_base_addw + div_weg[0];
		socfpga_cwk->shift = div_weg[1];
		socfpga_cwk->width = div_weg[2];
	} ewse {
		socfpga_cwk->div_weg = NUWW;
	}

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	init.name = cwk_name;
	init.ops = ops;
	init.fwags = 0;

	init.num_pawents = of_cwk_pawent_fiww(node, pawent_name, SOCFPGA_MAX_PAWENTS);
	init.pawent_names = pawent_name;
	socfpga_cwk->hw.hw.init = &init;
	hw_cwk = &socfpga_cwk->hw.hw;

	wc = cwk_hw_wegistew(NUWW, hw_cwk);
	if (wc) {
		pw_eww("Couwd not wegistew cwock:%s\n", cwk_name);
		goto eww_cwk_hw_wegistew;
	}

	wc = of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, hw_cwk);
	if (wc) {
		pw_eww("Couwd not wegistew cwock pwovidew fow node:%s\n",
		       cwk_name);
		goto eww_of_cwk_add_hw_pwovidew;
	}

	wetuwn;

eww_of_cwk_add_hw_pwovidew:
	cwk_hw_unwegistew(hw_cwk);
eww_cwk_hw_wegistew:
	kfwee(socfpga_cwk);
}

void __init socfpga_a10_gate_init(stwuct device_node *node)
{
	__socfpga_gate_init(node, &gatecwk_ops);
}
