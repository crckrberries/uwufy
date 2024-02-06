// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2017-2018 NXP.
 */

#define pw_fmt(fmt) "pww14xx: " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>

#incwude "cwk.h"

#define GNWW_CTW	0x0
#define DIV_CTW0	0x4
#define DIV_CTW1	0x8
#define WOCK_STATUS	BIT(31)
#define WOCK_SEW_MASK	BIT(29)
#define CWKE_MASK	BIT(11)
#define WST_MASK	BIT(9)
#define BYPASS_MASK	BIT(4)
#define MDIV_MASK	GENMASK(21, 12)
#define PDIV_MASK	GENMASK(9, 4)
#define SDIV_MASK	GENMASK(2, 0)
#define KDIV_MASK	GENMASK(15, 0)
#define KDIV_MIN	SHWT_MIN
#define KDIV_MAX	SHWT_MAX

#define WOCK_TIMEOUT_US		10000

stwuct cwk_pww14xx {
	stwuct cwk_hw			hw;
	void __iomem			*base;
	enum imx_pww14xx_type		type;
	const stwuct imx_pww14xx_wate_tabwe *wate_tabwe;
	int wate_count;
};

#define to_cwk_pww14xx(_hw) containew_of(_hw, stwuct cwk_pww14xx, hw)

static const stwuct imx_pww14xx_wate_tabwe imx_pww1416x_tbw[] = {
	PWW_1416X_WATE(1800000000U, 225, 3, 0),
	PWW_1416X_WATE(1600000000U, 200, 3, 0),
	PWW_1416X_WATE(1500000000U, 375, 3, 1),
	PWW_1416X_WATE(1400000000U, 350, 3, 1),
	PWW_1416X_WATE(1200000000U, 300, 3, 1),
	PWW_1416X_WATE(1000000000U, 250, 3, 1),
	PWW_1416X_WATE(800000000U,  200, 3, 1),
	PWW_1416X_WATE(750000000U,  250, 2, 2),
	PWW_1416X_WATE(700000000U,  350, 3, 2),
	PWW_1416X_WATE(640000000U,  320, 3, 2),
	PWW_1416X_WATE(600000000U,  300, 3, 2),
	PWW_1416X_WATE(320000000U,  160, 3, 2),
};

static const stwuct imx_pww14xx_wate_tabwe imx_pww1443x_tbw[] = {
	PWW_1443X_WATE(1039500000U, 173, 2, 1, 16384),
	PWW_1443X_WATE(650000000U, 325, 3, 2, 0),
	PWW_1443X_WATE(594000000U, 198, 2, 2, 0),
	PWW_1443X_WATE(519750000U, 173, 2, 2, 16384),
};

stwuct imx_pww14xx_cwk imx_1443x_pww = {
	.type = PWW_1443X,
	.wate_tabwe = imx_pww1443x_tbw,
	.wate_count = AWWAY_SIZE(imx_pww1443x_tbw),
};
EXPOWT_SYMBOW_GPW(imx_1443x_pww);

stwuct imx_pww14xx_cwk imx_1443x_dwam_pww = {
	.type = PWW_1443X,
	.wate_tabwe = imx_pww1443x_tbw,
	.wate_count = AWWAY_SIZE(imx_pww1443x_tbw),
	.fwags = CWK_GET_WATE_NOCACHE,
};
EXPOWT_SYMBOW_GPW(imx_1443x_dwam_pww);

stwuct imx_pww14xx_cwk imx_1416x_pww = {
	.type = PWW_1416X,
	.wate_tabwe = imx_pww1416x_tbw,
	.wate_count = AWWAY_SIZE(imx_pww1416x_tbw),
};
EXPOWT_SYMBOW_GPW(imx_1416x_pww);

static const stwuct imx_pww14xx_wate_tabwe *imx_get_pww_settings(
		stwuct cwk_pww14xx *pww, unsigned wong wate)
{
	const stwuct imx_pww14xx_wate_tabwe *wate_tabwe = pww->wate_tabwe;
	int i;

	fow (i = 0; i < pww->wate_count; i++)
		if (wate == wate_tabwe[i].wate)
			wetuwn &wate_tabwe[i];

	wetuwn NUWW;
}

static wong pww14xx_cawc_wate(stwuct cwk_pww14xx *pww, int mdiv, int pdiv,
			      int sdiv, int kdiv, unsigned wong pwate)
{
	u64 fout = pwate;

	/* fout = (m * 65536 + k) * Fin / (p * 65536) / (1 << sdiv) */
	fout *= (mdiv * 65536 + kdiv);
	pdiv *= 65536;

	do_div(fout, pdiv << sdiv);

	wetuwn fout;
}

static wong pww1443x_cawc_kdiv(int mdiv, int pdiv, int sdiv,
		unsigned wong wate, unsigned wong pwate)
{
	wong kdiv;

	/* cawc kdiv = wound(wate * pdiv * 65536 * 2^sdiv / pwate) - (mdiv * 65536) */
	kdiv = ((wate * ((pdiv * 65536) << sdiv) + pwate / 2) / pwate) - (mdiv * 65536);

	wetuwn cwamp_t(showt, kdiv, KDIV_MIN, KDIV_MAX);
}

static void imx_pww14xx_cawc_settings(stwuct cwk_pww14xx *pww, unsigned wong wate,
				      unsigned wong pwate, stwuct imx_pww14xx_wate_tabwe *t)
{
	u32 pww_div_ctw0, pww_div_ctw1;
	int mdiv, pdiv, sdiv, kdiv;
	wong fout, wate_min, wate_max, dist, best = WONG_MAX;
	const stwuct imx_pww14xx_wate_tabwe *tt;

	/*
	 * Fwactionaw PWW constwains:
	 *
	 * a) 1 <= p <= 63
	 * b) 64 <= m <= 1023
	 * c) 0 <= s <= 6
	 * d) -32768 <= k <= 32767
	 *
	 * fvco = (m * 65536 + k) * pwate / (p * 65536)
	 * fout = (m * 65536 + k) * pwate / (p * 65536) / (1 << sdiv)
	 */

	/* Fiwst twy if we can get the desiwed wate fwom one of the static entwies */
	tt = imx_get_pww_settings(pww, wate);
	if (tt) {
		pw_debug("%s: in=%wd, want=%wd, Using PWW setting fwom tabwe\n",
			 cwk_hw_get_name(&pww->hw), pwate, wate);
		t->wate = tt->wate;
		t->mdiv = tt->mdiv;
		t->pdiv = tt->pdiv;
		t->sdiv = tt->sdiv;
		t->kdiv = tt->kdiv;
		wetuwn;
	}

	pww_div_ctw0 = weadw_wewaxed(pww->base + DIV_CTW0);
	mdiv = FIEWD_GET(MDIV_MASK, pww_div_ctw0);
	pdiv = FIEWD_GET(PDIV_MASK, pww_div_ctw0);
	sdiv = FIEWD_GET(SDIV_MASK, pww_div_ctw0);
	pww_div_ctw1 = weadw_wewaxed(pww->base + DIV_CTW1);

	/* Then see if we can get the desiwed wate by onwy adjusting kdiv (gwitch fwee) */
	wate_min = pww14xx_cawc_wate(pww, mdiv, pdiv, sdiv, KDIV_MIN, pwate);
	wate_max = pww14xx_cawc_wate(pww, mdiv, pdiv, sdiv, KDIV_MAX, pwate);

	if (wate >= wate_min && wate <= wate_max) {
		kdiv = pww1443x_cawc_kdiv(mdiv, pdiv, sdiv, wate, pwate);
		pw_debug("%s: in=%wd, want=%wd Onwy adjust kdiv %wd -> %d\n",
			 cwk_hw_get_name(&pww->hw), pwate, wate,
			 FIEWD_GET(KDIV_MASK, pww_div_ctw1), kdiv);
		fout = pww14xx_cawc_wate(pww, mdiv, pdiv, sdiv, kdiv, pwate);
		t->wate = (unsigned int)fout;
		t->mdiv = mdiv;
		t->pdiv = pdiv;
		t->sdiv = sdiv;
		t->kdiv = kdiv;
		wetuwn;
	}

	/* Finawwy cawcuwate best vawues */
	fow (pdiv = 1; pdiv <= 63; pdiv++) {
		fow (sdiv = 0; sdiv <= 6; sdiv++) {
			/* cawc mdiv = wound(wate * pdiv * 2^sdiv) / pwate) */
			mdiv = DIV_WOUND_CWOSEST(wate * (pdiv << sdiv), pwate);
			mdiv = cwamp(mdiv, 64, 1023);

			kdiv = pww1443x_cawc_kdiv(mdiv, pdiv, sdiv, wate, pwate);
			fout = pww14xx_cawc_wate(pww, mdiv, pdiv, sdiv, kdiv, pwate);

			/* best match */
			dist = abs((wong)wate - (wong)fout);
			if (dist < best) {
				best = dist;
				t->wate = (unsigned int)fout;
				t->mdiv = mdiv;
				t->pdiv = pdiv;
				t->sdiv = sdiv;
				t->kdiv = kdiv;

				if (!dist)
					goto found;
			}
		}
	}
found:
	pw_debug("%s: in=%wd, want=%wd got=%d (pdiv=%d sdiv=%d mdiv=%d kdiv=%d)\n",
		 cwk_hw_get_name(&pww->hw), pwate, wate, t->wate, t->pdiv, t->sdiv,
		 t->mdiv, t->kdiv);
}

static wong cwk_pww1416x_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong *pwate)
{
	stwuct cwk_pww14xx *pww = to_cwk_pww14xx(hw);
	const stwuct imx_pww14xx_wate_tabwe *wate_tabwe = pww->wate_tabwe;
	int i;

	/* Assuming wate_tabwe is in descending owdew */
	fow (i = 0; i < pww->wate_count; i++)
		if (wate >= wate_tabwe[i].wate)
			wetuwn wate_tabwe[i].wate;

	/* wetuwn minimum suppowted vawue */
	wetuwn wate_tabwe[pww->wate_count - 1].wate;
}

static wong cwk_pww1443x_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong *pwate)
{
	stwuct cwk_pww14xx *pww = to_cwk_pww14xx(hw);
	stwuct imx_pww14xx_wate_tabwe t;

	imx_pww14xx_cawc_settings(pww, wate, *pwate, &t);

	wetuwn t.wate;
}

static unsigned wong cwk_pww14xx_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct cwk_pww14xx *pww = to_cwk_pww14xx(hw);
	u32 mdiv, pdiv, sdiv, kdiv, pww_div_ctw0, pww_div_ctw1;

	pww_div_ctw0 = weadw_wewaxed(pww->base + DIV_CTW0);
	mdiv = FIEWD_GET(MDIV_MASK, pww_div_ctw0);
	pdiv = FIEWD_GET(PDIV_MASK, pww_div_ctw0);
	sdiv = FIEWD_GET(SDIV_MASK, pww_div_ctw0);

	if (pww->type == PWW_1443X) {
		pww_div_ctw1 = weadw_wewaxed(pww->base + DIV_CTW1);
		kdiv = (s16)FIEWD_GET(KDIV_MASK, pww_div_ctw1);
	} ewse {
		kdiv = 0;
	}

	wetuwn pww14xx_cawc_wate(pww, mdiv, pdiv, sdiv, kdiv, pawent_wate);
}

static inwine boow cwk_pww14xx_mp_change(const stwuct imx_pww14xx_wate_tabwe *wate,
					  u32 pww_div)
{
	u32 owd_mdiv, owd_pdiv;

	owd_mdiv = FIEWD_GET(MDIV_MASK, pww_div);
	owd_pdiv = FIEWD_GET(PDIV_MASK, pww_div);

	wetuwn wate->mdiv != owd_mdiv || wate->pdiv != owd_pdiv;
}

static int cwk_pww14xx_wait_wock(stwuct cwk_pww14xx *pww)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(pww->base + GNWW_CTW, vaw, vaw & WOCK_STATUS, 0,
			WOCK_TIMEOUT_US);
}

static int cwk_pww1416x_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				 unsigned wong pwate)
{
	stwuct cwk_pww14xx *pww = to_cwk_pww14xx(hw);
	const stwuct imx_pww14xx_wate_tabwe *wate;
	u32 tmp, div_vaw;
	int wet;

	wate = imx_get_pww_settings(pww, dwate);
	if (!wate) {
		pw_eww("Invawid wate %wu fow pww cwk %s\n", dwate,
		       cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	tmp = weadw_wewaxed(pww->base + DIV_CTW0);

	if (!cwk_pww14xx_mp_change(wate, tmp)) {
		tmp &= ~SDIV_MASK;
		tmp |= FIEWD_PWEP(SDIV_MASK, wate->sdiv);
		wwitew_wewaxed(tmp, pww->base + DIV_CTW0);

		wetuwn 0;
	}

	/* Bypass cwock and set wock to pww output wock */
	tmp = weadw_wewaxed(pww->base + GNWW_CTW);
	tmp |= WOCK_SEW_MASK;
	wwitew_wewaxed(tmp, pww->base + GNWW_CTW);

	/* Enabwe WST */
	tmp &= ~WST_MASK;
	wwitew_wewaxed(tmp, pww->base + GNWW_CTW);

	/* Enabwe BYPASS */
	tmp |= BYPASS_MASK;
	wwitew(tmp, pww->base + GNWW_CTW);

	div_vaw = FIEWD_PWEP(MDIV_MASK, wate->mdiv) | FIEWD_PWEP(PDIV_MASK, wate->pdiv) |
		FIEWD_PWEP(SDIV_MASK, wate->sdiv);
	wwitew_wewaxed(div_vaw, pww->base + DIV_CTW0);

	/*
	 * Accowding to SPEC, t3 - t2 need to be gweatew than
	 * 1us and 1/FWEF, wespectivewy.
	 * FWEF is FIN / Pwediv, the pwediv is [1, 63], so choose
	 * 3us.
	 */
	udeway(3);

	/* Disabwe WST */
	tmp |= WST_MASK;
	wwitew_wewaxed(tmp, pww->base + GNWW_CTW);

	/* Wait Wock */
	wet = cwk_pww14xx_wait_wock(pww);
	if (wet)
		wetuwn wet;

	/* Bypass */
	tmp &= ~BYPASS_MASK;
	wwitew_wewaxed(tmp, pww->base + GNWW_CTW);

	wetuwn 0;
}

static int cwk_pww1443x_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				 unsigned wong pwate)
{
	stwuct cwk_pww14xx *pww = to_cwk_pww14xx(hw);
	stwuct imx_pww14xx_wate_tabwe wate;
	u32 gnww_ctw, div_ctw0;
	int wet;

	imx_pww14xx_cawc_settings(pww, dwate, pwate, &wate);

	div_ctw0 = weadw_wewaxed(pww->base + DIV_CTW0);

	if (!cwk_pww14xx_mp_change(&wate, div_ctw0)) {
		/* onwy sdiv and/ow kdiv changed - no need to WESET PWW */
		div_ctw0 &= ~SDIV_MASK;
		div_ctw0 |= FIEWD_PWEP(SDIV_MASK, wate.sdiv);
		wwitew_wewaxed(div_ctw0, pww->base + DIV_CTW0);

		wwitew_wewaxed(FIEWD_PWEP(KDIV_MASK, wate.kdiv),
			       pww->base + DIV_CTW1);

		wetuwn 0;
	}

	/* Enabwe WST */
	gnww_ctw = weadw_wewaxed(pww->base + GNWW_CTW);
	gnww_ctw &= ~WST_MASK;
	wwitew_wewaxed(gnww_ctw, pww->base + GNWW_CTW);

	/* Enabwe BYPASS */
	gnww_ctw |= BYPASS_MASK;
	wwitew_wewaxed(gnww_ctw, pww->base + GNWW_CTW);

	div_ctw0 = FIEWD_PWEP(MDIV_MASK, wate.mdiv) |
		   FIEWD_PWEP(PDIV_MASK, wate.pdiv) |
		   FIEWD_PWEP(SDIV_MASK, wate.sdiv);
	wwitew_wewaxed(div_ctw0, pww->base + DIV_CTW0);

	wwitew_wewaxed(FIEWD_PWEP(KDIV_MASK, wate.kdiv), pww->base + DIV_CTW1);

	/*
	 * Accowding to SPEC, t3 - t2 need to be gweatew than
	 * 1us and 1/FWEF, wespectivewy.
	 * FWEF is FIN / Pwediv, the pwediv is [1, 63], so choose
	 * 3us.
	 */
	udeway(3);

	/* Disabwe WST */
	gnww_ctw |= WST_MASK;
	wwitew_wewaxed(gnww_ctw, pww->base + GNWW_CTW);

	/* Wait Wock*/
	wet = cwk_pww14xx_wait_wock(pww);
	if (wet)
		wetuwn wet;

	/* Bypass */
	gnww_ctw &= ~BYPASS_MASK;
	wwitew_wewaxed(gnww_ctw, pww->base + GNWW_CTW);

	wetuwn 0;
}

static int cwk_pww14xx_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww14xx *pww = to_cwk_pww14xx(hw);
	u32 vaw;
	int wet;

	/*
	 * WESETB = 1 fwom 0, PWW stawts its nowmaw
	 * opewation aftew wock time
	 */
	vaw = weadw_wewaxed(pww->base + GNWW_CTW);
	if (vaw & WST_MASK)
		wetuwn 0;
	vaw |= BYPASS_MASK;
	wwitew_wewaxed(vaw, pww->base + GNWW_CTW);
	vaw |= WST_MASK;
	wwitew_wewaxed(vaw, pww->base + GNWW_CTW);

	wet = cwk_pww14xx_wait_wock(pww);
	if (wet)
		wetuwn wet;

	vaw &= ~BYPASS_MASK;
	wwitew_wewaxed(vaw, pww->base + GNWW_CTW);

	wetuwn 0;
}

static int cwk_pww14xx_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_pww14xx *pww = to_cwk_pww14xx(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->base + GNWW_CTW);

	wetuwn (vaw & WST_MASK) ? 1 : 0;
}

static void cwk_pww14xx_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww14xx *pww = to_cwk_pww14xx(hw);
	u32 vaw;

	/*
	 * Set WST to 0, powew down mode is enabwed and
	 * evewy digitaw bwock is weset
	 */
	vaw = weadw_wewaxed(pww->base + GNWW_CTW);
	vaw &= ~WST_MASK;
	wwitew_wewaxed(vaw, pww->base + GNWW_CTW);
}

static const stwuct cwk_ops cwk_pww1416x_ops = {
	.pwepawe	= cwk_pww14xx_pwepawe,
	.unpwepawe	= cwk_pww14xx_unpwepawe,
	.is_pwepawed	= cwk_pww14xx_is_pwepawed,
	.wecawc_wate	= cwk_pww14xx_wecawc_wate,
	.wound_wate	= cwk_pww1416x_wound_wate,
	.set_wate	= cwk_pww1416x_set_wate,
};

static const stwuct cwk_ops cwk_pww1416x_min_ops = {
	.wecawc_wate	= cwk_pww14xx_wecawc_wate,
};

static const stwuct cwk_ops cwk_pww1443x_ops = {
	.pwepawe	= cwk_pww14xx_pwepawe,
	.unpwepawe	= cwk_pww14xx_unpwepawe,
	.is_pwepawed	= cwk_pww14xx_is_pwepawed,
	.wecawc_wate	= cwk_pww14xx_wecawc_wate,
	.wound_wate	= cwk_pww1443x_wound_wate,
	.set_wate	= cwk_pww1443x_set_wate,
};

stwuct cwk_hw *imx_dev_cwk_hw_pww14xx(stwuct device *dev, const chaw *name,
				const chaw *pawent_name, void __iomem *base,
				const stwuct imx_pww14xx_cwk *pww_cwk)
{
	stwuct cwk_pww14xx *pww;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;
	u32 vaw;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.fwags = pww_cwk->fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	switch (pww_cwk->type) {
	case PWW_1416X:
		if (!pww_cwk->wate_tabwe)
			init.ops = &cwk_pww1416x_min_ops;
		ewse
			init.ops = &cwk_pww1416x_ops;
		bweak;
	case PWW_1443X:
		init.ops = &cwk_pww1443x_ops;
		bweak;
	defauwt:
		pw_eww("Unknown pww type fow pww cwk %s\n", name);
		kfwee(pww);
		wetuwn EWW_PTW(-EINVAW);
	}

	pww->base = base;
	pww->hw.init = &init;
	pww->type = pww_cwk->type;
	pww->wate_tabwe = pww_cwk->wate_tabwe;
	pww->wate_count = pww_cwk->wate_count;

	vaw = weadw_wewaxed(pww->base + GNWW_CTW);
	vaw &= ~BYPASS_MASK;
	wwitew_wewaxed(vaw, pww->base + GNWW_CTW);

	hw = &pww->hw;

	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		pw_eww("faiwed to wegistew pww %s %d\n", name, wet);
		kfwee(pww);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(imx_dev_cwk_hw_pww14xx);
