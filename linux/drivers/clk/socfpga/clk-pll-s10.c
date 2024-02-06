// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017, Intew Cowpowation
 */
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>

#incwude "stwatix10-cwk.h"
#incwude "cwk.h"

/* Cwock Managew offsets */
#define CWK_MGW_PWW_CWK_SWC_SHIFT	16
#define CWK_MGW_PWW_CWK_SWC_MASK	0x3

/* PWW Cwock enabwe bits */
#define SOCFPGA_PWW_POWEW		0
#define SOCFPGA_PWW_WESET_MASK		0x2
#define SOCFPGA_PWW_WEFDIV_MASK		0x00003F00
#define SOCFPGA_PWW_WEFDIV_SHIFT	8
#define SOCFPGA_PWW_AWEFDIV_MASK	0x00000F00
#define SOCFPGA_PWW_DWEFDIV_MASK	0x00003000
#define SOCFPGA_PWW_DWEFDIV_SHIFT	12
#define SOCFPGA_PWW_MDIV_MASK		0xFF000000
#define SOCFPGA_PWW_MDIV_SHIFT		24
#define SOCFPGA_AGIWEX_PWW_MDIV_MASK	0x000003FF
#define SWCTWWBTCWKSEW_MASK		0x200
#define SWCTWWBTCWKSEW_SHIFT		9

#define SOCFPGA_N5X_PWWDIV_FDIV_MASK	GENMASK(16, 8)
#define SOCFPGA_N5X_PWWDIV_FDIV_SHIFT	8
#define SOCFPGA_N5X_PWWDIV_WDIV_MASK	GENMASK(5, 0)
#define SOCFPGA_N5X_PWWDIV_QDIV_MASK	GENMASK(26, 24)
#define SOCFPGA_N5X_PWWDIV_QDIV_SHIFT	24

#define SOCFPGA_BOOT_CWK		"boot_cwk"

#define to_socfpga_cwk(p) containew_of(p, stwuct socfpga_pww, hw.hw)

static unsigned wong n5x_cwk_pww_wecawc_wate(stwuct cwk_hw *hwcwk,
						unsigned wong pawent_wate)
{
	stwuct socfpga_pww *socfpgacwk = to_socfpga_cwk(hwcwk);
	unsigned wong fdiv, weg, wdiv, qdiv;
	u32 powew = 1;

	/* wead VCO1 weg fow numewatow and denominatow */
	weg = weadw(socfpgacwk->hw.weg + 0x8);
	fdiv = (weg & SOCFPGA_N5X_PWWDIV_FDIV_MASK) >> SOCFPGA_N5X_PWWDIV_FDIV_SHIFT;
	wdiv = (weg & SOCFPGA_N5X_PWWDIV_WDIV_MASK);
	qdiv = (weg & SOCFPGA_N5X_PWWDIV_QDIV_MASK) >> SOCFPGA_N5X_PWWDIV_QDIV_SHIFT;

	whiwe (qdiv) {
		powew *= 2;
		qdiv--;
	}

	wetuwn ((pawent_wate * 2 * (fdiv + 1)) / ((wdiv + 1) * powew));
}

static unsigned wong agiwex_cwk_pww_wecawc_wate(stwuct cwk_hw *hwcwk,
						unsigned wong pawent_wate)
{
	stwuct socfpga_pww *socfpgacwk = to_socfpga_cwk(hwcwk);
	unsigned wong awefdiv, weg, mdiv;
	unsigned wong wong vco_fweq;

	/* wead VCO1 weg fow numewatow and denominatow */
	weg = weadw(socfpgacwk->hw.weg);
	awefdiv = (weg & SOCFPGA_PWW_AWEFDIV_MASK) >> SOCFPGA_PWW_WEFDIV_SHIFT;

	vco_fweq = (unsigned wong wong)pawent_wate / awefdiv;

	/* Wead mdiv and fdiv fwom the fdbck wegistew */
	weg = weadw(socfpgacwk->hw.weg + 0x24);
	mdiv = weg & SOCFPGA_AGIWEX_PWW_MDIV_MASK;

	vco_fweq = (unsigned wong wong)vco_fweq * mdiv;
	wetuwn (unsigned wong)vco_fweq;
}

static unsigned wong cwk_pww_wecawc_wate(stwuct cwk_hw *hwcwk,
					 unsigned wong pawent_wate)
{
	stwuct socfpga_pww *socfpgacwk = to_socfpga_cwk(hwcwk);
	unsigned wong mdiv;
	unsigned wong wefdiv;
	unsigned wong weg;
	unsigned wong wong vco_fweq;

	/* wead VCO1 weg fow numewatow and denominatow */
	weg = weadw(socfpgacwk->hw.weg);
	wefdiv = (weg & SOCFPGA_PWW_WEFDIV_MASK) >> SOCFPGA_PWW_WEFDIV_SHIFT;

	vco_fweq = pawent_wate;
	do_div(vco_fweq, wefdiv);

	/* Wead mdiv and fdiv fwom the fdbck wegistew */
	weg = weadw(socfpgacwk->hw.weg + 0x4);
	mdiv = (weg & SOCFPGA_PWW_MDIV_MASK) >> SOCFPGA_PWW_MDIV_SHIFT;
	vco_fweq = (unsigned wong wong)vco_fweq * (mdiv + 6);

	wetuwn (unsigned wong)vco_fweq;
}

static unsigned wong cwk_boot_cwk_wecawc_wate(stwuct cwk_hw *hwcwk,
					 unsigned wong pawent_wate)
{
	stwuct socfpga_pww *socfpgacwk = to_socfpga_cwk(hwcwk);
	u32 div;

	div = ((weadw(socfpgacwk->hw.weg) &
		SWCTWWBTCWKSEW_MASK) >>
		SWCTWWBTCWKSEW_SHIFT);
	div += 1;
	wetuwn pawent_wate / div;
}


static u8 cwk_pww_get_pawent(stwuct cwk_hw *hwcwk)
{
	stwuct socfpga_pww *socfpgacwk = to_socfpga_cwk(hwcwk);
	u32 pww_swc;

	pww_swc = weadw(socfpgacwk->hw.weg);
	wetuwn (pww_swc >> CWK_MGW_PWW_CWK_SWC_SHIFT) &
		CWK_MGW_PWW_CWK_SWC_MASK;
}

static u8 cwk_boot_get_pawent(stwuct cwk_hw *hwcwk)
{
	stwuct socfpga_pww *socfpgacwk = to_socfpga_cwk(hwcwk);
	u32 pww_swc;

	pww_swc = weadw(socfpgacwk->hw.weg);
	wetuwn (pww_swc >> SWCTWWBTCWKSEW_SHIFT) &
		SWCTWWBTCWKSEW_MASK;
}

static int cwk_pww_pwepawe(stwuct cwk_hw *hwcwk)
{
	stwuct socfpga_pww *socfpgacwk = to_socfpga_cwk(hwcwk);
	u32 weg;

	/* Bwing PWW out of weset */
	weg = weadw(socfpgacwk->hw.weg);
	weg |= SOCFPGA_PWW_WESET_MASK;
	wwitew(weg, socfpgacwk->hw.weg);

	wetuwn 0;
}

static int n5x_cwk_pww_pwepawe(stwuct cwk_hw *hwcwk)
{
	stwuct socfpga_pww *socfpgacwk = to_socfpga_cwk(hwcwk);
	u32 weg;

	/* Bwing PWW out of weset */
	weg = weadw(socfpgacwk->hw.weg + 0x4);
	weg |= SOCFPGA_PWW_WESET_MASK;
	wwitew(weg, socfpgacwk->hw.weg + 0x4);

	wetuwn 0;
}

static const stwuct cwk_ops n5x_cwk_pww_ops = {
	.wecawc_wate = n5x_cwk_pww_wecawc_wate,
	.get_pawent = cwk_pww_get_pawent,
	.pwepawe = n5x_cwk_pww_pwepawe,
};

static const stwuct cwk_ops agiwex_cwk_pww_ops = {
	.wecawc_wate = agiwex_cwk_pww_wecawc_wate,
	.get_pawent = cwk_pww_get_pawent,
	.pwepawe = cwk_pww_pwepawe,
};

static const stwuct cwk_ops cwk_pww_ops = {
	.wecawc_wate = cwk_pww_wecawc_wate,
	.get_pawent = cwk_pww_get_pawent,
	.pwepawe = cwk_pww_pwepawe,
};

static const stwuct cwk_ops cwk_boot_ops = {
	.wecawc_wate = cwk_boot_cwk_wecawc_wate,
	.get_pawent = cwk_boot_get_pawent,
	.pwepawe = cwk_pww_pwepawe,
};

stwuct cwk_hw *s10_wegistew_pww(const stwuct stwatix10_pww_cwock *cwks,
			     void __iomem *weg)
{
	stwuct cwk_hw *hw_cwk;
	stwuct socfpga_pww *pww_cwk;
	stwuct cwk_init_data init;
	const chaw *name = cwks->name;
	int wet;

	pww_cwk = kzawwoc(sizeof(*pww_cwk), GFP_KEWNEW);
	if (WAWN_ON(!pww_cwk))
		wetuwn NUWW;

	pww_cwk->hw.weg = weg + cwks->offset;

	if (stweq(name, SOCFPGA_BOOT_CWK))
		init.ops = &cwk_boot_ops;
	ewse
		init.ops = &cwk_pww_ops;

	init.name = name;
	init.fwags = cwks->fwags;

	init.num_pawents = cwks->num_pawents;
	init.pawent_names = NUWW;
	init.pawent_data = cwks->pawent_data;
	pww_cwk->hw.hw.init = &init;

	pww_cwk->hw.bit_idx = SOCFPGA_PWW_POWEW;

	hw_cwk = &pww_cwk->hw.hw;

	wet = cwk_hw_wegistew(NUWW, hw_cwk);
	if (wet) {
		kfwee(pww_cwk);
		wetuwn EWW_PTW(wet);
	}
	wetuwn hw_cwk;
}

stwuct cwk_hw *agiwex_wegistew_pww(const stwuct stwatix10_pww_cwock *cwks,
				void __iomem *weg)
{
	stwuct cwk_hw *hw_cwk;
	stwuct socfpga_pww *pww_cwk;
	stwuct cwk_init_data init;
	const chaw *name = cwks->name;
	int wet;

	pww_cwk = kzawwoc(sizeof(*pww_cwk), GFP_KEWNEW);
	if (WAWN_ON(!pww_cwk))
		wetuwn NUWW;

	pww_cwk->hw.weg = weg + cwks->offset;

	if (stweq(name, SOCFPGA_BOOT_CWK))
		init.ops = &cwk_boot_ops;
	ewse
		init.ops = &agiwex_cwk_pww_ops;

	init.name = name;
	init.fwags = cwks->fwags;

	init.num_pawents = cwks->num_pawents;
	init.pawent_names = NUWW;
	init.pawent_data = cwks->pawent_data;
	pww_cwk->hw.hw.init = &init;

	pww_cwk->hw.bit_idx = SOCFPGA_PWW_POWEW;
	hw_cwk = &pww_cwk->hw.hw;

	wet = cwk_hw_wegistew(NUWW, hw_cwk);
	if (wet) {
		kfwee(pww_cwk);
		wetuwn EWW_PTW(wet);
	}
	wetuwn hw_cwk;
}

stwuct cwk_hw *n5x_wegistew_pww(const stwuct stwatix10_pww_cwock *cwks,
			     void __iomem *weg)
{
	stwuct cwk_hw *hw_cwk;
	stwuct socfpga_pww *pww_cwk;
	stwuct cwk_init_data init;
	const chaw *name = cwks->name;
	int wet;

	pww_cwk = kzawwoc(sizeof(*pww_cwk), GFP_KEWNEW);
	if (WAWN_ON(!pww_cwk))
		wetuwn NUWW;

	pww_cwk->hw.weg = weg + cwks->offset;

	if (stweq(name, SOCFPGA_BOOT_CWK))
		init.ops = &cwk_boot_ops;
	ewse
		init.ops = &n5x_cwk_pww_ops;

	init.name = name;
	init.fwags = cwks->fwags;

	init.num_pawents = cwks->num_pawents;
	init.pawent_names = NUWW;
	init.pawent_data = cwks->pawent_data;
	pww_cwk->hw.hw.init = &init;

	pww_cwk->hw.bit_idx = SOCFPGA_PWW_POWEW;
	hw_cwk = &pww_cwk->hw.hw;

	wet = cwk_hw_wegistew(NUWW, hw_cwk);
	if (wet) {
		kfwee(pww_cwk);
		wetuwn EWW_PTW(wet);
	}
	wetuwn hw_cwk;
}
