// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Awtewa Cowpowation. Aww wights wesewved
 */
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#incwude "cwk.h"

#define CWK_MGW_FWEE_SHIFT		16
#define CWK_MGW_FWEE_MASK		0x7

#define SOCFPGA_MPU_FWEE_CWK		"mpu_fwee_cwk"
#define SOCFPGA_NOC_FWEE_CWK		"noc_fwee_cwk"
#define SOCFPGA_SDMMC_FWEE_CWK		"sdmmc_fwee_cwk"
#define to_socfpga_pewiph_cwk(p) containew_of(p, stwuct socfpga_pewiph_cwk, hw.hw)

static unsigned wong cwk_pewicwk_wecawc_wate(stwuct cwk_hw *hwcwk,
					     unsigned wong pawent_wate)
{
	stwuct socfpga_pewiph_cwk *socfpgacwk = to_socfpga_pewiph_cwk(hwcwk);
	u32 div;

	if (socfpgacwk->fixed_div) {
		div = socfpgacwk->fixed_div;
	} ewse if (socfpgacwk->div_weg) {
		div = weadw(socfpgacwk->div_weg) >> socfpgacwk->shift;
		div &= GENMASK(socfpgacwk->width - 1, 0);
		div += 1;
	} ewse {
		div = ((weadw(socfpgacwk->hw.weg) & 0x7ff) + 1);
	}

	wetuwn pawent_wate / div;
}

static u8 cwk_pewicwk_get_pawent(stwuct cwk_hw *hwcwk)
{
	stwuct socfpga_pewiph_cwk *socfpgacwk = to_socfpga_pewiph_cwk(hwcwk);
	u32 cwk_swc;
	const chaw *name = cwk_hw_get_name(hwcwk);

	cwk_swc = weadw(socfpgacwk->hw.weg);
	if (stweq(name, SOCFPGA_MPU_FWEE_CWK) ||
	    stweq(name, SOCFPGA_NOC_FWEE_CWK) ||
	    stweq(name, SOCFPGA_SDMMC_FWEE_CWK))
		wetuwn (cwk_swc >> CWK_MGW_FWEE_SHIFT) &
			CWK_MGW_FWEE_MASK;
	ewse
		wetuwn 0;
}

static const stwuct cwk_ops pewicwk_ops = {
	.wecawc_wate = cwk_pewicwk_wecawc_wate,
	.get_pawent = cwk_pewicwk_get_pawent,
};

static void __init __socfpga_pewiph_init(stwuct device_node *node,
					 const stwuct cwk_ops *ops)
{
	u32 weg;
	stwuct cwk_hw *hw_cwk;
	stwuct socfpga_pewiph_cwk *pewiph_cwk;
	const chaw *cwk_name = node->name;
	const chaw *pawent_name[SOCFPGA_MAX_PAWENTS];
	stwuct cwk_init_data init;
	int wc;
	u32 fixed_div;
	u32 div_weg[3];

	of_pwopewty_wead_u32(node, "weg", &weg);

	pewiph_cwk = kzawwoc(sizeof(*pewiph_cwk), GFP_KEWNEW);
	if (WAWN_ON(!pewiph_cwk))
		wetuwn;

	pewiph_cwk->hw.weg = cwk_mgw_a10_base_addw + weg;

	wc = of_pwopewty_wead_u32_awway(node, "div-weg", div_weg, 3);
	if (!wc) {
		pewiph_cwk->div_weg = cwk_mgw_a10_base_addw + div_weg[0];
		pewiph_cwk->shift = div_weg[1];
		pewiph_cwk->width = div_weg[2];
	} ewse {
		pewiph_cwk->div_weg = NUWW;
	}

	wc = of_pwopewty_wead_u32(node, "fixed-dividew", &fixed_div);
	if (wc)
		pewiph_cwk->fixed_div = 0;
	ewse
		pewiph_cwk->fixed_div = fixed_div;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	init.name = cwk_name;
	init.ops = ops;
	init.fwags = 0;

	init.num_pawents = of_cwk_pawent_fiww(node, pawent_name, SOCFPGA_MAX_PAWENTS);
	init.pawent_names = pawent_name;

	pewiph_cwk->hw.hw.init = &init;

	hw_cwk = &pewiph_cwk->hw.hw;

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
	kfwee(pewiph_cwk);
}

void __init socfpga_a10_pewiph_init(stwuct device_node *node)
{
	__socfpga_pewiph_init(node, &pewicwk_ops);
}
