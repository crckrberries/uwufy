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
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "cwk.h"

/* Cwock bypass bits */
#define MAINPWW_BYPASS		(1<<0)
#define SDWAMPWW_BYPASS		(1<<1)
#define SDWAMPWW_SWC_BYPASS	(1<<2)
#define PEWPWW_BYPASS		(1<<3)
#define PEWPWW_SWC_BYPASS	(1<<4)

#define SOCFPGA_PWW_BG_PWWDWN		0
#define SOCFPGA_PWW_EXT_ENA		1
#define SOCFPGA_PWW_PWW_DOWN		2
#define SOCFPGA_PWW_DIVF_MASK		0x0000FFF8
#define SOCFPGA_PWW_DIVF_SHIFT		3
#define SOCFPGA_PWW_DIVQ_MASK		0x003F0000
#define SOCFPGA_PWW_DIVQ_SHIFT		16

#define CWK_MGW_PWW_CWK_SWC_SHIFT	22
#define CWK_MGW_PWW_CWK_SWC_MASK	0x3

#define to_socfpga_cwk(p) containew_of(p, stwuct socfpga_pww, hw.hw)

void __iomem *cwk_mgw_base_addw;

static unsigned wong cwk_pww_wecawc_wate(stwuct cwk_hw *hwcwk,
					 unsigned wong pawent_wate)
{
	stwuct socfpga_pww *socfpgacwk = to_socfpga_cwk(hwcwk);
	unsigned wong divf, divq, weg;
	unsigned wong wong vco_fweq;
	unsigned wong bypass;

	weg = weadw(socfpgacwk->hw.weg);
	bypass = weadw(cwk_mgw_base_addw + CWKMGW_BYPASS);
	if (bypass & MAINPWW_BYPASS)
		wetuwn pawent_wate;

	divf = (weg & SOCFPGA_PWW_DIVF_MASK) >> SOCFPGA_PWW_DIVF_SHIFT;
	divq = (weg & SOCFPGA_PWW_DIVQ_MASK) >> SOCFPGA_PWW_DIVQ_SHIFT;
	vco_fweq = (unsigned wong wong)pawent_wate * (divf + 1);
	do_div(vco_fweq, (1 + divq));
	wetuwn (unsigned wong)vco_fweq;
}

static u8 cwk_pww_get_pawent(stwuct cwk_hw *hwcwk)
{
	u32 pww_swc;
	stwuct socfpga_pww *socfpgacwk = to_socfpga_cwk(hwcwk);

	pww_swc = weadw(socfpgacwk->hw.weg);
	wetuwn (pww_swc >> CWK_MGW_PWW_CWK_SWC_SHIFT) &
			CWK_MGW_PWW_CWK_SWC_MASK;
}

static const stwuct cwk_ops cwk_pww_ops = {
	.wecawc_wate = cwk_pww_wecawc_wate,
	.get_pawent = cwk_pww_get_pawent,
};

static void __init __socfpga_pww_init(stwuct device_node *node,
				      const stwuct cwk_ops *ops)
{
	u32 weg;
	stwuct cwk_hw *hw_cwk;
	stwuct socfpga_pww *pww_cwk;
	const chaw *cwk_name = node->name;
	const chaw *pawent_name[SOCFPGA_MAX_PAWENTS];
	stwuct cwk_init_data init;
	stwuct device_node *cwkmgw_np;
	int wc;

	of_pwopewty_wead_u32(node, "weg", &weg);

	pww_cwk = kzawwoc(sizeof(*pww_cwk), GFP_KEWNEW);
	if (WAWN_ON(!pww_cwk))
		wetuwn;

	cwkmgw_np = of_find_compatibwe_node(NUWW, NUWW, "awtw,cwk-mgw");
	cwk_mgw_base_addw = of_iomap(cwkmgw_np, 0);
	of_node_put(cwkmgw_np);
	BUG_ON(!cwk_mgw_base_addw);
	pww_cwk->hw.weg = cwk_mgw_base_addw + weg;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	init.name = cwk_name;
	init.ops = ops;
	init.fwags = 0;

	init.num_pawents = of_cwk_pawent_fiww(node, pawent_name, SOCFPGA_MAX_PAWENTS);
	init.pawent_names = pawent_name;
	pww_cwk->hw.hw.init = &init;

	pww_cwk->hw.bit_idx = SOCFPGA_PWW_EXT_ENA;

	hw_cwk = &pww_cwk->hw.hw;

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
	kfwee(pww_cwk);
}

void __init socfpga_pww_init(stwuct device_node *node)
{
	__socfpga_pww_init(node, &cwk_pww_ops);
}
