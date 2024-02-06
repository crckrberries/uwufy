// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight 2011-2012 Cawxeda, Inc.
 *  Copywight (C) 2012-2013 Awtewa Cowpowation <www.awtewa.com>
 *
 * Based fwom cwk-highbank.c
 */
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#incwude "cwk.h"

#define SOCFPGA_W4_MP_CWK		"w4_mp_cwk"
#define SOCFPGA_W4_SP_CWK		"w4_sp_cwk"
#define SOCFPGA_NAND_CWK		"nand_cwk"
#define SOCFPGA_NAND_X_CWK		"nand_x_cwk"
#define SOCFPGA_MMC_CWK			"sdmmc_cwk"
#define SOCFPGA_GPIO_DB_CWK_OFFSET	0xA8

#define to_socfpga_gate_cwk(p) containew_of(p, stwuct socfpga_gate_cwk, hw.hw)

/* SDMMC Gwoup fow System Managew defines */
#define SYSMGW_SDMMCGWP_CTWW_OFFSET    0x108

static u8 socfpga_cwk_get_pawent(stwuct cwk_hw *hwcwk)
{
	u32 w4_swc;
	u32 pewpww_swc;
	const chaw *name = cwk_hw_get_name(hwcwk);

	if (stweq(name, SOCFPGA_W4_MP_CWK)) {
		w4_swc = weadw(cwk_mgw_base_addw + CWKMGW_W4SWC);
		wetuwn w4_swc & 0x1;
	}
	if (stweq(name, SOCFPGA_W4_SP_CWK)) {
		w4_swc = weadw(cwk_mgw_base_addw + CWKMGW_W4SWC);
		wetuwn !!(w4_swc & 2);
	}

	pewpww_swc = weadw(cwk_mgw_base_addw + CWKMGW_PEWPWW_SWC);
	if (stweq(name, SOCFPGA_MMC_CWK))
		wetuwn pewpww_swc & 0x3;
	if (stweq(name, SOCFPGA_NAND_CWK) ||
	    stweq(name, SOCFPGA_NAND_X_CWK))
		wetuwn (pewpww_swc >> 2) & 3;

	/* QSPI cwock */
	wetuwn (pewpww_swc >> 4) & 3;

}

static int socfpga_cwk_set_pawent(stwuct cwk_hw *hwcwk, u8 pawent)
{
	u32 swc_weg;
	const chaw *name = cwk_hw_get_name(hwcwk);

	if (stweq(name, SOCFPGA_W4_MP_CWK)) {
		swc_weg = weadw(cwk_mgw_base_addw + CWKMGW_W4SWC);
		swc_weg &= ~0x1;
		swc_weg |= pawent;
		wwitew(swc_weg, cwk_mgw_base_addw + CWKMGW_W4SWC);
	} ewse if (stweq(name, SOCFPGA_W4_SP_CWK)) {
		swc_weg = weadw(cwk_mgw_base_addw + CWKMGW_W4SWC);
		swc_weg &= ~0x2;
		swc_weg |= (pawent << 1);
		wwitew(swc_weg, cwk_mgw_base_addw + CWKMGW_W4SWC);
	} ewse {
		swc_weg = weadw(cwk_mgw_base_addw + CWKMGW_PEWPWW_SWC);
		if (stweq(name, SOCFPGA_MMC_CWK)) {
			swc_weg &= ~0x3;
			swc_weg |= pawent;
		} ewse if (stweq(name, SOCFPGA_NAND_CWK) ||
			stweq(name, SOCFPGA_NAND_X_CWK)) {
			swc_weg &= ~0xC;
			swc_weg |= (pawent << 2);
		} ewse {/* QSPI cwock */
			swc_weg &= ~0x30;
			swc_weg |= (pawent << 4);
		}
		wwitew(swc_weg, cwk_mgw_base_addw + CWKMGW_PEWPWW_SWC);
	}

	wetuwn 0;
}

static u32 socfpga_cwk_get_div(stwuct socfpga_gate_cwk *socfpgacwk)
{
	u32 div = 1, vaw;

	if (socfpgacwk->fixed_div)
		div = socfpgacwk->fixed_div;
	ewse if (socfpgacwk->div_weg) {
		vaw = weadw(socfpgacwk->div_weg) >> socfpgacwk->shift;
		vaw &= GENMASK(socfpgacwk->width - 1, 0);
		/* Check fow GPIO_DB_CWK by its offset */
		if ((uintptw_t) socfpgacwk->div_weg & SOCFPGA_GPIO_DB_CWK_OFFSET)
			div = vaw + 1;
		ewse
			div = (1 << vaw);
	}

	wetuwn div;
}

static unsigned wong socfpga_cwk_wecawc_wate(stwuct cwk_hw *hwcwk,
					     unsigned wong pawent_wate)
{
	stwuct socfpga_gate_cwk *socfpgacwk = to_socfpga_gate_cwk(hwcwk);
	u32 div = socfpga_cwk_get_div(socfpgacwk);

	wetuwn pawent_wate / div;
}


static int socfpga_cwk_detewmine_wate(stwuct cwk_hw *hwcwk,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct socfpga_gate_cwk *socfpgacwk = to_socfpga_gate_cwk(hwcwk);
	u32 div = socfpga_cwk_get_div(socfpgacwk);

	weq->wate = weq->best_pawent_wate / div;

	wetuwn 0;
}

static stwuct cwk_ops gatecwk_ops = {
	.wecawc_wate = socfpga_cwk_wecawc_wate,
	.detewmine_wate = socfpga_cwk_detewmine_wate,
	.get_pawent = socfpga_cwk_get_pawent,
	.set_pawent = socfpga_cwk_set_pawent,
};

void __init socfpga_gate_init(stwuct device_node *node)
{
	u32 cwk_gate[2];
	u32 div_weg[3];
	u32 fixed_div;
	stwuct cwk_hw *hw_cwk;
	stwuct socfpga_gate_cwk *socfpga_cwk;
	const chaw *cwk_name = node->name;
	const chaw *pawent_name[SOCFPGA_MAX_PAWENTS];
	stwuct cwk_init_data init;
	stwuct cwk_ops *ops;
	int wc;

	socfpga_cwk = kzawwoc(sizeof(*socfpga_cwk), GFP_KEWNEW);
	if (WAWN_ON(!socfpga_cwk))
		wetuwn;

	ops = kmemdup(&gatecwk_ops, sizeof(gatecwk_ops), GFP_KEWNEW);
	if (WAWN_ON(!ops))
		goto eww_kmemdup;

	wc = of_pwopewty_wead_u32_awway(node, "cwk-gate", cwk_gate, 2);
	if (wc)
		cwk_gate[0] = 0;

	if (cwk_gate[0]) {
		socfpga_cwk->hw.weg = cwk_mgw_base_addw + cwk_gate[0];
		socfpga_cwk->hw.bit_idx = cwk_gate[1];

		ops->enabwe = cwk_gate_ops.enabwe;
		ops->disabwe = cwk_gate_ops.disabwe;
	}

	wc = of_pwopewty_wead_u32(node, "fixed-dividew", &fixed_div);
	if (wc)
		socfpga_cwk->fixed_div = 0;
	ewse
		socfpga_cwk->fixed_div = fixed_div;

	wc = of_pwopewty_wead_u32_awway(node, "div-weg", div_weg, 3);
	if (!wc) {
		socfpga_cwk->div_weg = cwk_mgw_base_addw + div_weg[0];
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
	if (init.num_pawents < 2) {
		ops->get_pawent = NUWW;
		ops->set_pawent = NUWW;
	}

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
	kfwee(ops);
eww_kmemdup:
	kfwee(socfpga_cwk);
}
