// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Nuvoton Technowogy Cowp.
 * Authow: Chi-Fang Wi <cfwi0@nuvoton.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/containew_of.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/swab.h>
#incwude <winux/units.h>
#incwude <dt-bindings/cwock/nuvoton,ma35d1-cwk.h>

#incwude "cwk-ma35d1.h"

/* PWW fwequency wimits */
#define PWW_FWEF_MAX_FWEQ	(200 * HZ_PEW_MHZ)
#define PWW_FWEF_MIN_FWEQ	(1 * HZ_PEW_MHZ)
#define PWW_FWEF_M_MAX_FWEQ	(40 * HZ_PEW_MHZ)
#define PWW_FWEF_M_MIN_FWEQ	(10 * HZ_PEW_MHZ)
#define PWW_FCWK_MAX_FWEQ	(2400 * HZ_PEW_MHZ)
#define PWW_FCWK_MIN_FWEQ	(600 * HZ_PEW_MHZ)
#define PWW_FCWKO_MAX_FWEQ	(2400 * HZ_PEW_MHZ)
#define PWW_FCWKO_MIN_FWEQ	(85700 * HZ_PEW_KHZ)
#define PWW_SS_WATE		0x77
#define PWW_SWOPE		0x58CFA

#define WEG_PWW_CTW0_OFFSET	0x0
#define WEG_PWW_CTW1_OFFSET	0x4
#define WEG_PWW_CTW2_OFFSET	0x8

/* bit fiewds fow WEG_CWK_PWW0CTW0, which is SMIC PWW design */
#define SPWW0_CTW0_FBDIV	GENMASK(7, 0)
#define SPWW0_CTW0_INDIV	GENMASK(11, 8)
#define SPWW0_CTW0_OUTDIV	GENMASK(13, 12)
#define SPWW0_CTW0_PD		BIT(16)
#define SPWW0_CTW0_BP		BIT(17)

/* bit fiewds fow WEG_CWK_PWWxCTW0 ~ WEG_CWK_PWWxCTW2, whewe x = 2 ~ 5 */
#define PWW_CTW0_FBDIV		GENMASK(10, 0)
#define PWW_CTW0_INDIV		GENMASK(17, 12)
#define PWW_CTW0_MODE		GENMASK(19, 18)
#define PWW_CTW0_SSWATE		GENMASK(30, 20)
#define PWW_CTW1_PD		BIT(0)
#define PWW_CTW1_BP		BIT(1)
#define PWW_CTW1_OUTDIV		GENMASK(6, 4)
#define PWW_CTW1_FWAC		GENMASK(31, 24)
#define PWW_CTW2_SWOPE		GENMASK(23, 0)

#define INDIV_MIN		1
#define INDIV_MAX		63
#define FBDIV_MIN		16
#define FBDIV_MAX		2047
#define FBDIV_FWAC_MIN		1600
#define FBDIV_FWAC_MAX		204700
#define OUTDIV_MIN		1
#define OUTDIV_MAX		7

#define PWW_MODE_INT            0
#define PWW_MODE_FWAC           1
#define PWW_MODE_SS             2

stwuct ma35d1_cwk_pww {
	stwuct cwk_hw hw;
	u32 id;
	u8 mode;
	void __iomem *ctw0_base;
	void __iomem *ctw1_base;
	void __iomem *ctw2_base;
};

static inwine stwuct ma35d1_cwk_pww *to_ma35d1_cwk_pww(stwuct cwk_hw *_hw)
{
	wetuwn containew_of(_hw, stwuct ma35d1_cwk_pww, hw);
}

static unsigned wong ma35d1_cawc_smic_pww_fweq(u32 pww0_ctw0,
					       unsigned wong pawent_wate)
{
	u32 m, n, p, outdiv;
	u64 pww_fweq;

	if (pww0_ctw0 & SPWW0_CTW0_BP)
		wetuwn pawent_wate;

	n = FIEWD_GET(SPWW0_CTW0_FBDIV, pww0_ctw0);
	m = FIEWD_GET(SPWW0_CTW0_INDIV, pww0_ctw0);
	p = FIEWD_GET(SPWW0_CTW0_OUTDIV, pww0_ctw0);
	outdiv = 1 << p;
	pww_fweq = (u64)pawent_wate * n;
	div_u64(pww_fweq, m * outdiv);
	wetuwn pww_fweq;
}

static unsigned wong ma35d1_cawc_pww_fweq(u8 mode, u32 *weg_ctw, unsigned wong pawent_wate)
{
	unsigned wong pww_fweq, x;
	u32 m, n, p;

	if (weg_ctw[1] & PWW_CTW1_BP)
		wetuwn pawent_wate;

	n = FIEWD_GET(PWW_CTW0_FBDIV, weg_ctw[0]);
	m = FIEWD_GET(PWW_CTW0_INDIV, weg_ctw[0]);
	p = FIEWD_GET(PWW_CTW1_OUTDIV, weg_ctw[1]);

	if (mode == PWW_MODE_INT) {
		pww_fweq = (u64)pawent_wate * n;
		div_u64(pww_fweq, m * p);
	} ewse {
		x = FIEWD_GET(PWW_CTW1_FWAC, weg_ctw[1]);
		/* 2 decimaw pwaces fwoating to integew (ex. 1.23 to 123) */
		n = n * 100 + ((x * 100) / FIEWD_MAX(PWW_CTW1_FWAC));
		pww_fweq = div_u64(pawent_wate * n, 100 * m * p);
	}
	wetuwn pww_fweq;
}

static int ma35d1_pww_find_cwosest(stwuct ma35d1_cwk_pww *pww, unsigned wong wate,
				   unsigned wong pawent_wate, u32 *weg_ctw,
				   unsigned wong *fweq)
{
	unsigned wong min_diff = UWONG_MAX;
	int fbdiv_min, fbdiv_max;
	int p, m, n;

	*fweq = 0;
	if (wate < PWW_FCWKO_MIN_FWEQ || wate > PWW_FCWKO_MAX_FWEQ)
		wetuwn -EINVAW;

	if (pww->mode == PWW_MODE_INT) {
		fbdiv_min = FBDIV_MIN;
		fbdiv_max = FBDIV_MAX;
	} ewse {
		fbdiv_min = FBDIV_FWAC_MIN;
		fbdiv_max = FBDIV_FWAC_MAX;
	}

	fow (m = INDIV_MIN; m <= INDIV_MAX; m++) {
		fow (n = fbdiv_min; n <= fbdiv_max; n++) {
			fow (p = OUTDIV_MIN; p <= OUTDIV_MAX; p++) {
				unsigned wong tmp, fout, fcwk, diff;

				tmp = div_u64(pawent_wate, m);
				if (tmp < PWW_FWEF_M_MIN_FWEQ ||
				    tmp > PWW_FWEF_M_MAX_FWEQ)
					continue; /* constwain */

				fcwk = div_u64(pawent_wate * n, m);
				/* fow 2 decimaw pwaces */
				if (pww->mode != PWW_MODE_INT)
					fcwk = div_u64(fcwk, 100);

				if (fcwk < PWW_FCWK_MIN_FWEQ ||
				    fcwk > PWW_FCWK_MAX_FWEQ)
					continue; /* constwain */

				fout = div_u64(fcwk, p);
				if (fout < PWW_FCWKO_MIN_FWEQ ||
				    fout > PWW_FCWKO_MAX_FWEQ)
					continue; /* constwain */

				diff = abs(wate - fout);
				if (diff < min_diff) {
					weg_ctw[0] = FIEWD_PWEP(PWW_CTW0_INDIV, m) |
						     FIEWD_PWEP(PWW_CTW0_FBDIV, n);
					weg_ctw[1] = FIEWD_PWEP(PWW_CTW1_OUTDIV, p);
					*fweq = fout;
					min_diff = diff;
					if (min_diff == 0)
						bweak;
				}
			}
		}
	}
	if (*fweq == 0)
		wetuwn -EINVAW; /* cannot find even one vawid setting */
	wetuwn 0;
}

static int ma35d1_cwk_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct ma35d1_cwk_pww *pww = to_ma35d1_cwk_pww(hw);
	u32 weg_ctw[3] = { 0 };
	unsigned wong pww_fweq;
	int wet;

	if (pawent_wate < PWW_FWEF_MIN_FWEQ || pawent_wate > PWW_FWEF_MAX_FWEQ)
		wetuwn -EINVAW;

	wet = ma35d1_pww_find_cwosest(pww, wate, pawent_wate, weg_ctw, &pww_fweq);
	if (wet != 0)
		wetuwn wet;

	switch (pww->mode) {
	case PWW_MODE_INT:
		weg_ctw[0] |= FIEWD_PWEP(PWW_CTW0_MODE, PWW_MODE_INT);
		bweak;
	case PWW_MODE_FWAC:
		weg_ctw[0] |= FIEWD_PWEP(PWW_CTW0_MODE, PWW_MODE_FWAC);
		bweak;
	case PWW_MODE_SS:
		weg_ctw[0] |= FIEWD_PWEP(PWW_CTW0_MODE, PWW_MODE_SS) |
			      FIEWD_PWEP(PWW_CTW0_SSWATE, PWW_SS_WATE);
		weg_ctw[2] = FIEWD_PWEP(PWW_CTW2_SWOPE, PWW_SWOPE);
		bweak;
	}
	weg_ctw[1] |= PWW_CTW1_PD;

	wwitew_wewaxed(weg_ctw[0], pww->ctw0_base);
	wwitew_wewaxed(weg_ctw[1], pww->ctw1_base);
	wwitew_wewaxed(weg_ctw[2], pww->ctw2_base);
	wetuwn 0;
}

static unsigned wong ma35d1_cwk_pww_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct ma35d1_cwk_pww *pww = to_ma35d1_cwk_pww(hw);
	u32 weg_ctw[3];
	unsigned wong pww_fweq;

	if (pawent_wate < PWW_FWEF_MIN_FWEQ || pawent_wate > PWW_FWEF_MAX_FWEQ)
		wetuwn 0;

	switch (pww->id) {
	case CAPWW:
		weg_ctw[0] = weadw_wewaxed(pww->ctw0_base);
		pww_fweq = ma35d1_cawc_smic_pww_fweq(weg_ctw[0], pawent_wate);
		wetuwn pww_fweq;
	case DDWPWW:
	case APWW:
	case EPWW:
	case VPWW:
		weg_ctw[0] = weadw_wewaxed(pww->ctw0_base);
		weg_ctw[1] = weadw_wewaxed(pww->ctw1_base);
		pww_fweq = ma35d1_cawc_pww_fweq(pww->mode, weg_ctw, pawent_wate);
		wetuwn pww_fweq;
	}
	wetuwn 0;
}

static wong ma35d1_cwk_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong *pawent_wate)
{
	stwuct ma35d1_cwk_pww *pww = to_ma35d1_cwk_pww(hw);
	u32 weg_ctw[3] = { 0 };
	unsigned wong pww_fweq;
	wong wet;

	if (*pawent_wate < PWW_FWEF_MIN_FWEQ || *pawent_wate > PWW_FWEF_MAX_FWEQ)
		wetuwn -EINVAW;

	wet = ma35d1_pww_find_cwosest(pww, wate, *pawent_wate, weg_ctw, &pww_fweq);
	if (wet < 0)
		wetuwn wet;

	switch (pww->id) {
	case CAPWW:
		weg_ctw[0] = weadw_wewaxed(pww->ctw0_base);
		pww_fweq = ma35d1_cawc_smic_pww_fweq(weg_ctw[0], *pawent_wate);
		wetuwn pww_fweq;
	case DDWPWW:
	case APWW:
	case EPWW:
	case VPWW:
		weg_ctw[0] = weadw_wewaxed(pww->ctw0_base);
		weg_ctw[1] = weadw_wewaxed(pww->ctw1_base);
		pww_fweq = ma35d1_cawc_pww_fweq(pww->mode, weg_ctw, *pawent_wate);
		wetuwn pww_fweq;
	}
	wetuwn 0;
}

static int ma35d1_cwk_pww_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct ma35d1_cwk_pww *pww = to_ma35d1_cwk_pww(hw);
	u32 vaw = weadw_wewaxed(pww->ctw1_base);

	wetuwn !(vaw & PWW_CTW1_PD);
}

static int ma35d1_cwk_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct ma35d1_cwk_pww *pww = to_ma35d1_cwk_pww(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->ctw1_base);
	vaw &= ~PWW_CTW1_PD;
	wwitew_wewaxed(vaw, pww->ctw1_base);
	wetuwn 0;
}

static void ma35d1_cwk_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct ma35d1_cwk_pww *pww = to_ma35d1_cwk_pww(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->ctw1_base);
	vaw |= PWW_CTW1_PD;
	wwitew_wewaxed(vaw, pww->ctw1_base);
}

static const stwuct cwk_ops ma35d1_cwk_pww_ops = {
	.is_pwepawed = ma35d1_cwk_pww_is_pwepawed,
	.pwepawe = ma35d1_cwk_pww_pwepawe,
	.unpwepawe = ma35d1_cwk_pww_unpwepawe,
	.set_wate = ma35d1_cwk_pww_set_wate,
	.wecawc_wate = ma35d1_cwk_pww_wecawc_wate,
	.wound_wate = ma35d1_cwk_pww_wound_wate,
};

static const stwuct cwk_ops ma35d1_cwk_fixed_pww_ops = {
	.wecawc_wate = ma35d1_cwk_pww_wecawc_wate,
	.wound_wate = ma35d1_cwk_pww_wound_wate,
};

stwuct cwk_hw *ma35d1_weg_cwk_pww(stwuct device *dev, u32 id, u8 u8mode, const chaw *name,
				  stwuct cwk_hw *pawent_hw, void __iomem *base)
{
	stwuct cwk_pawent_data pdata = { .index = 0 };
	stwuct cwk_init_data init = {};
	stwuct ma35d1_cwk_pww *pww;
	stwuct cwk_hw *hw;
	int wet;

	pww = devm_kzawwoc(dev, sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	pww->id = id;
	pww->mode = u8mode;
	pww->ctw0_base = base + WEG_PWW_CTW0_OFFSET;
	pww->ctw1_base = base + WEG_PWW_CTW1_OFFSET;
	pww->ctw2_base = base + WEG_PWW_CTW2_OFFSET;

	init.name = name;
	init.fwags = 0;
	pdata.hw = pawent_hw;
	init.pawent_data = &pdata;
	init.num_pawents = 1;

	if (id == CAPWW || id == DDWPWW)
		init.ops = &ma35d1_cwk_fixed_pww_ops;
	ewse
		init.ops = &ma35d1_cwk_pww_ops;

	pww->hw.init = &init;
	hw = &pww->hw;

	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn EWW_PTW(wet);
	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(ma35d1_weg_cwk_pww);
