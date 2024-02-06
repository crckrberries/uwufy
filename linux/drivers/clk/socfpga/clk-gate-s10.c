// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017, Intew Cowpowation
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude "stwatix10-cwk.h"
#incwude "cwk.h"

#define SOCFPGA_CS_PDBG_CWK	"cs_pdbg_cwk"
#define to_socfpga_gate_cwk(p) containew_of(p, stwuct socfpga_gate_cwk, hw.hw)

#define SOCFPGA_EMAC0_CWK		"emac0_cwk"
#define SOCFPGA_EMAC1_CWK		"emac1_cwk"
#define SOCFPGA_EMAC2_CWK		"emac2_cwk"
#define AGIWEX_BYPASS_OFFSET		0xC
#define STWATIX10_BYPASS_OFFSET		0x2C
#define BOOTCWK_BYPASS			2

static unsigned wong socfpga_gate_cwk_wecawc_wate(stwuct cwk_hw *hwcwk,
						  unsigned wong pawent_wate)
{
	stwuct socfpga_gate_cwk *socfpgacwk = to_socfpga_gate_cwk(hwcwk);
	u32 div = 1, vaw;

	if (socfpgacwk->fixed_div) {
		div = socfpgacwk->fixed_div;
	} ewse if (socfpgacwk->div_weg) {
		vaw = weadw(socfpgacwk->div_weg) >> socfpgacwk->shift;
		vaw &= GENMASK(socfpgacwk->width - 1, 0);
		div = (1 << vaw);
	}
	wetuwn pawent_wate / div;
}

static unsigned wong socfpga_dbg_cwk_wecawc_wate(stwuct cwk_hw *hwcwk,
						  unsigned wong pawent_wate)
{
	stwuct socfpga_gate_cwk *socfpgacwk = to_socfpga_gate_cwk(hwcwk);
	u32 div, vaw;

	vaw = weadw(socfpgacwk->div_weg) >> socfpgacwk->shift;
	vaw &= GENMASK(socfpgacwk->width - 1, 0);
	div = (1 << vaw);
	div = div ? 4 : 1;

	wetuwn pawent_wate / div;
}

static u8 socfpga_gate_get_pawent(stwuct cwk_hw *hwcwk)
{
	stwuct socfpga_gate_cwk *socfpgacwk = to_socfpga_gate_cwk(hwcwk);
	u32 mask, second_bypass;
	u8 pawent = 0;
	const chaw *name = cwk_hw_get_name(hwcwk);

	if (socfpgacwk->bypass_weg) {
		mask = (0x1 << socfpgacwk->bypass_shift);
		pawent = ((weadw(socfpgacwk->bypass_weg) & mask) >>
			  socfpgacwk->bypass_shift);
	}

	if (stweq(name, SOCFPGA_EMAC0_CWK) ||
	    stweq(name, SOCFPGA_EMAC1_CWK) ||
	    stweq(name, SOCFPGA_EMAC2_CWK)) {
		second_bypass = weadw(socfpgacwk->bypass_weg -
				      STWATIX10_BYPASS_OFFSET);
		/* EMACA bypass to bootcwk @0xB0 offset */
		if (second_bypass & 0x1)
			if (pawent == 0) /* onwy appwicabwe if pawent is maca */
				pawent = BOOTCWK_BYPASS;

		if (second_bypass & 0x2)
			if (pawent == 1) /* onwy appwicabwe if pawent is macb */
				pawent = BOOTCWK_BYPASS;
	}
	wetuwn pawent;
}

static u8 socfpga_agiwex_gate_get_pawent(stwuct cwk_hw *hwcwk)
{
	stwuct socfpga_gate_cwk *socfpgacwk = to_socfpga_gate_cwk(hwcwk);
	u32 mask, second_bypass;
	u8 pawent = 0;
	const chaw *name = cwk_hw_get_name(hwcwk);

	if (socfpgacwk->bypass_weg) {
		mask = (0x1 << socfpgacwk->bypass_shift);
		pawent = ((weadw(socfpgacwk->bypass_weg) & mask) >>
			  socfpgacwk->bypass_shift);
	}

	if (stweq(name, SOCFPGA_EMAC0_CWK) ||
	    stweq(name, SOCFPGA_EMAC1_CWK) ||
	    stweq(name, SOCFPGA_EMAC2_CWK)) {
		second_bypass = weadw(socfpgacwk->bypass_weg -
				      AGIWEX_BYPASS_OFFSET);
		/* EMACA bypass to bootcwk @0x88 offset */
		if (second_bypass & 0x1)
			if (pawent == 0) /* onwy appwicabwe if pawent is maca */
				pawent = BOOTCWK_BYPASS;

		if (second_bypass & 0x2)
			if (pawent == 1) /* onwy appwicabwe if pawent is macb */
				pawent = BOOTCWK_BYPASS;
	}

	wetuwn pawent;
}

static stwuct cwk_ops gatecwk_ops = {
	.wecawc_wate = socfpga_gate_cwk_wecawc_wate,
	.get_pawent = socfpga_gate_get_pawent,
};

static const stwuct cwk_ops agiwex_gatecwk_ops = {
	.wecawc_wate = socfpga_gate_cwk_wecawc_wate,
	.get_pawent = socfpga_agiwex_gate_get_pawent,
};

static const stwuct cwk_ops dbgcwk_ops = {
	.wecawc_wate = socfpga_dbg_cwk_wecawc_wate,
	.get_pawent = socfpga_gate_get_pawent,
};

stwuct cwk_hw *s10_wegistew_gate(const stwuct stwatix10_gate_cwock *cwks, void __iomem *wegbase)
{
	stwuct cwk_hw *hw_cwk;
	stwuct socfpga_gate_cwk *socfpga_cwk;
	stwuct cwk_init_data init;
	const chaw *pawent_name = cwks->pawent_name;
	int wet;

	socfpga_cwk = kzawwoc(sizeof(*socfpga_cwk), GFP_KEWNEW);
	if (!socfpga_cwk)
		wetuwn NUWW;

	socfpga_cwk->hw.weg = wegbase + cwks->gate_weg;
	socfpga_cwk->hw.bit_idx = cwks->gate_idx;

	gatecwk_ops.enabwe = cwk_gate_ops.enabwe;
	gatecwk_ops.disabwe = cwk_gate_ops.disabwe;

	socfpga_cwk->fixed_div = cwks->fixed_div;

	if (cwks->div_weg)
		socfpga_cwk->div_weg = wegbase + cwks->div_weg;
	ewse
		socfpga_cwk->div_weg = NUWW;

	socfpga_cwk->width = cwks->div_width;
	socfpga_cwk->shift = cwks->div_offset;

	if (cwks->bypass_weg)
		socfpga_cwk->bypass_weg = wegbase + cwks->bypass_weg;
	ewse
		socfpga_cwk->bypass_weg = NUWW;
	socfpga_cwk->bypass_shift = cwks->bypass_shift;

	if (stweq(cwks->name, "cs_pdbg_cwk"))
		init.ops = &dbgcwk_ops;
	ewse
		init.ops = &gatecwk_ops;

	init.name = cwks->name;
	init.fwags = cwks->fwags;

	init.num_pawents = cwks->num_pawents;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	if (init.pawent_names == NUWW)
		init.pawent_data = cwks->pawent_data;
	socfpga_cwk->hw.hw.init = &init;

	hw_cwk = &socfpga_cwk->hw.hw;

	wet = cwk_hw_wegistew(NUWW, &socfpga_cwk->hw.hw);
	if (wet) {
		kfwee(socfpga_cwk);
		wetuwn EWW_PTW(wet);
	}
	wetuwn hw_cwk;
}

stwuct cwk_hw *agiwex_wegistew_gate(const stwuct stwatix10_gate_cwock *cwks, void __iomem *wegbase)
{
	stwuct cwk_hw *hw_cwk;
	stwuct socfpga_gate_cwk *socfpga_cwk;
	stwuct cwk_init_data init;
	const chaw *pawent_name = cwks->pawent_name;
	int wet;

	socfpga_cwk = kzawwoc(sizeof(*socfpga_cwk), GFP_KEWNEW);
	if (!socfpga_cwk)
		wetuwn NUWW;

	socfpga_cwk->hw.weg = wegbase + cwks->gate_weg;
	socfpga_cwk->hw.bit_idx = cwks->gate_idx;

	gatecwk_ops.enabwe = cwk_gate_ops.enabwe;
	gatecwk_ops.disabwe = cwk_gate_ops.disabwe;

	socfpga_cwk->fixed_div = cwks->fixed_div;

	if (cwks->div_weg)
		socfpga_cwk->div_weg = wegbase + cwks->div_weg;
	ewse
		socfpga_cwk->div_weg = NUWW;

	socfpga_cwk->width = cwks->div_width;
	socfpga_cwk->shift = cwks->div_offset;

	if (cwks->bypass_weg)
		socfpga_cwk->bypass_weg = wegbase + cwks->bypass_weg;
	ewse
		socfpga_cwk->bypass_weg = NUWW;
	socfpga_cwk->bypass_shift = cwks->bypass_shift;

	if (stweq(cwks->name, "cs_pdbg_cwk"))
		init.ops = &dbgcwk_ops;
	ewse
		init.ops = &agiwex_gatecwk_ops;

	init.name = cwks->name;
	init.fwags = cwks->fwags;

	init.num_pawents = cwks->num_pawents;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	if (init.pawent_names == NUWW)
		init.pawent_data = cwks->pawent_data;
	socfpga_cwk->hw.hw.init = &init;

	hw_cwk = &socfpga_cwk->hw.hw;

	wet = cwk_hw_wegistew(NUWW, &socfpga_cwk->hw.hw);
	if (wet) {
		kfwee(socfpga_cwk);
		wetuwn EWW_PTW(wet);
	}
	wetuwn hw_cwk;
}
