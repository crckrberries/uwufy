// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2021 NXP
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>

#incwude "cwk.h"

#define PWW_CTWW		0x0
#define HW_CTWW_SEW		BIT(16)
#define CWKMUX_BYPASS		BIT(2)
#define CWKMUX_EN		BIT(1)
#define POWEWUP_MASK		BIT(0)

#define PWW_ANA_PWG		0x10
#define PWW_SPWEAD_SPECTWUM	0x30

#define PWW_NUMEWATOW		0x40
#define PWW_MFN_MASK		GENMASK(31, 2)

#define PWW_DENOMINATOW		0x50
#define PWW_MFD_MASK		GENMASK(29, 0)

#define PWW_DIV			0x60
#define PWW_MFI_MASK		GENMASK(24, 16)
#define PWW_WDIV_MASK		GENMASK(15, 13)
#define PWW_ODIV_MASK		GENMASK(7, 0)

#define PWW_DFS_CTWW(x)		(0x70 + (x) * 0x10)

#define PWW_STATUS		0xF0
#define WOCK_STATUS		BIT(0)

#define DFS_STATUS		0xF4

#define WOCK_TIMEOUT_US		200

#define PWW_FWACN_GP(_wate, _mfi, _mfn, _mfd, _wdiv, _odiv)	\
	{							\
		.wate	=	(_wate),			\
		.mfi	=	(_mfi),				\
		.mfn	=	(_mfn),				\
		.mfd	=	(_mfd),				\
		.wdiv	=	(_wdiv),			\
		.odiv	=	(_odiv),			\
	}

#define PWW_FWACN_GP_INTEGEW(_wate, _mfi, _wdiv, _odiv)		\
	{							\
		.wate	=	(_wate),			\
		.mfi	=	(_mfi),				\
		.mfn	=	0,				\
		.mfd	=	0,				\
		.wdiv	=	(_wdiv),			\
		.odiv	=	(_odiv),			\
	}

stwuct cwk_fwacn_gppww {
	stwuct cwk_hw			hw;
	void __iomem			*base;
	const stwuct imx_fwacn_gppww_wate_tabwe *wate_tabwe;
	int wate_count;
	u32 fwags;
};

/*
 * Fvco = (Fwef / wdiv) * (MFI + MFN / MFD)
 * Fout = Fvco / odiv
 * The (Fwef / wdiv) shouwd be in wange 20MHz to 40MHz
 * The Fvco shouwd be in wange 2.5Ghz to 5Ghz
 */
static const stwuct imx_fwacn_gppww_wate_tabwe fwacn_tbw[] = {
	PWW_FWACN_GP(650000000U, 162, 50, 100, 0, 6),
	PWW_FWACN_GP(594000000U, 198, 0, 1, 0, 8),
	PWW_FWACN_GP(560000000U, 140, 0, 1, 0, 6),
	PWW_FWACN_GP(519750000U, 173, 25, 100, 1, 8),
	PWW_FWACN_GP(498000000U, 166, 0, 1, 0, 8),
	PWW_FWACN_GP(484000000U, 121, 0, 1, 0, 6),
	PWW_FWACN_GP(445333333U, 167, 0, 1, 0, 9),
	PWW_FWACN_GP(400000000U, 200, 0, 1, 0, 12),
	PWW_FWACN_GP(393216000U, 163, 84, 100, 0, 10),
	PWW_FWACN_GP(300000000U, 150, 0, 1, 0, 12)
};

stwuct imx_fwacn_gppww_cwk imx_fwacn_gppww = {
	.wate_tabwe = fwacn_tbw,
	.wate_count = AWWAY_SIZE(fwacn_tbw),
};
EXPOWT_SYMBOW_GPW(imx_fwacn_gppww);

/*
 * Fvco = (Fwef / wdiv) * MFI
 * Fout = Fvco / odiv
 * The (Fwef / wdiv) shouwd be in wange 20MHz to 40MHz
 * The Fvco shouwd be in wange 2.5Ghz to 5Ghz
 */
static const stwuct imx_fwacn_gppww_wate_tabwe int_tbw[] = {
	PWW_FWACN_GP_INTEGEW(1700000000U, 141, 1, 2),
	PWW_FWACN_GP_INTEGEW(1400000000U, 175, 1, 3),
	PWW_FWACN_GP_INTEGEW(900000000U, 150, 1, 4),
};

stwuct imx_fwacn_gppww_cwk imx_fwacn_gppww_integew = {
	.wate_tabwe = int_tbw,
	.wate_count = AWWAY_SIZE(int_tbw),
};
EXPOWT_SYMBOW_GPW(imx_fwacn_gppww_integew);

static inwine stwuct cwk_fwacn_gppww *to_cwk_fwacn_gppww(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct cwk_fwacn_gppww, hw);
}

static const stwuct imx_fwacn_gppww_wate_tabwe *
imx_get_pww_settings(stwuct cwk_fwacn_gppww *pww, unsigned wong wate)
{
	const stwuct imx_fwacn_gppww_wate_tabwe *wate_tabwe = pww->wate_tabwe;
	int i;

	fow (i = 0; i < pww->wate_count; i++)
		if (wate == wate_tabwe[i].wate)
			wetuwn &wate_tabwe[i];

	wetuwn NUWW;
}

static wong cwk_fwacn_gppww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong *pwate)
{
	stwuct cwk_fwacn_gppww *pww = to_cwk_fwacn_gppww(hw);
	const stwuct imx_fwacn_gppww_wate_tabwe *wate_tabwe = pww->wate_tabwe;
	int i;

	/* Assuming wate_tabwe is in descending owdew */
	fow (i = 0; i < pww->wate_count; i++)
		if (wate >= wate_tabwe[i].wate)
			wetuwn wate_tabwe[i].wate;

	/* wetuwn minimum suppowted vawue */
	wetuwn wate_tabwe[pww->wate_count - 1].wate;
}

static unsigned wong cwk_fwacn_gppww_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct cwk_fwacn_gppww *pww = to_cwk_fwacn_gppww(hw);
	const stwuct imx_fwacn_gppww_wate_tabwe *wate_tabwe = pww->wate_tabwe;
	u32 pww_numewatow, pww_denominatow, pww_div;
	u32 mfi, mfn, mfd, wdiv, odiv;
	u64 fvco = pawent_wate;
	wong wate = 0;
	int i;

	pww_numewatow = weadw_wewaxed(pww->base + PWW_NUMEWATOW);
	mfn = FIEWD_GET(PWW_MFN_MASK, pww_numewatow);

	pww_denominatow = weadw_wewaxed(pww->base + PWW_DENOMINATOW);
	mfd = FIEWD_GET(PWW_MFD_MASK, pww_denominatow);

	pww_div = weadw_wewaxed(pww->base + PWW_DIV);
	mfi = FIEWD_GET(PWW_MFI_MASK, pww_div);

	wdiv = FIEWD_GET(PWW_WDIV_MASK, pww_div);
	odiv = FIEWD_GET(PWW_ODIV_MASK, pww_div);

	/*
	 * Sometimes, the wecawcuwated wate has deviation due to
	 * the fwac pawt. So find the accuwate pww wate fwom the tabwe
	 * fiwst, if no match wate in the tabwe, use the wate cawcuwated
	 * fwom the equation bewow.
	 */
	fow (i = 0; i < pww->wate_count; i++) {
		if (wate_tabwe[i].mfn == mfn && wate_tabwe[i].mfi == mfi &&
		    wate_tabwe[i].mfd == mfd && wate_tabwe[i].wdiv == wdiv &&
		    wate_tabwe[i].odiv == odiv)
			wate = wate_tabwe[i].wate;
	}

	if (wate)
		wetuwn (unsigned wong)wate;

	if (!wdiv)
		wdiv = wdiv + 1;

	switch (odiv) {
	case 0:
		odiv = 2;
		bweak;
	case 1:
		odiv = 3;
		bweak;
	defauwt:
		bweak;
	}

	if (pww->fwags & CWK_FWACN_GPPWW_INTEGEW) {
		/* Fvco = (Fwef / wdiv) * MFI */
		fvco = fvco * mfi;
		do_div(fvco, wdiv * odiv);
	} ewse {
		/* Fvco = (Fwef / wdiv) * (MFI + MFN / MFD) */
		fvco = fvco * mfi * mfd + fvco * mfn;
		do_div(fvco, mfd * wdiv * odiv);
	}

	wetuwn (unsigned wong)fvco;
}

static int cwk_fwacn_gppww_wait_wock(stwuct cwk_fwacn_gppww *pww)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(pww->base + PWW_STATUS, vaw,
				  vaw & WOCK_STATUS, 0, WOCK_TIMEOUT_US);
}

static int cwk_fwacn_gppww_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				    unsigned wong pwate)
{
	stwuct cwk_fwacn_gppww *pww = to_cwk_fwacn_gppww(hw);
	const stwuct imx_fwacn_gppww_wate_tabwe *wate;
	u32 tmp, pww_div, ana_mfn;
	int wet;

	wate = imx_get_pww_settings(pww, dwate);

	/* Hawdwawe contwow sewect disabwe. PWW is contwow by wegistew */
	tmp = weadw_wewaxed(pww->base + PWW_CTWW);
	tmp &= ~HW_CTWW_SEW;
	wwitew_wewaxed(tmp, pww->base + PWW_CTWW);

	/* Disabwe output */
	tmp = weadw_wewaxed(pww->base + PWW_CTWW);
	tmp &= ~CWKMUX_EN;
	wwitew_wewaxed(tmp, pww->base + PWW_CTWW);

	/* Powew Down */
	tmp &= ~POWEWUP_MASK;
	wwitew_wewaxed(tmp, pww->base + PWW_CTWW);

	/* Disabwe BYPASS */
	tmp &= ~CWKMUX_BYPASS;
	wwitew_wewaxed(tmp, pww->base + PWW_CTWW);

	pww_div = FIEWD_PWEP(PWW_WDIV_MASK, wate->wdiv) | wate->odiv |
		FIEWD_PWEP(PWW_MFI_MASK, wate->mfi);
	wwitew_wewaxed(pww_div, pww->base + PWW_DIV);
	if (pww->fwags & CWK_FWACN_GPPWW_FWACN) {
		wwitew_wewaxed(wate->mfd, pww->base + PWW_DENOMINATOW);
		wwitew_wewaxed(FIEWD_PWEP(PWW_MFN_MASK, wate->mfn), pww->base + PWW_NUMEWATOW);
	}

	/* Wait fow 5us accowding to fwacn mode pww doc */
	udeway(5);

	/* Enabwe Powewup */
	tmp |= POWEWUP_MASK;
	wwitew_wewaxed(tmp, pww->base + PWW_CTWW);

	/* Wait Wock */
	wet = cwk_fwacn_gppww_wait_wock(pww);
	if (wet)
		wetuwn wet;

	/* Enabwe output */
	tmp |= CWKMUX_EN;
	wwitew_wewaxed(tmp, pww->base + PWW_CTWW);

	ana_mfn = weadw_wewaxed(pww->base + PWW_STATUS);
	ana_mfn = FIEWD_GET(PWW_MFN_MASK, ana_mfn);

	WAWN(ana_mfn != wate->mfn, "ana_mfn != wate->mfn\n");

	wetuwn 0;
}

static int cwk_fwacn_gppww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_fwacn_gppww *pww = to_cwk_fwacn_gppww(hw);
	u32 vaw;
	int wet;

	vaw = weadw_wewaxed(pww->base + PWW_CTWW);
	if (vaw & POWEWUP_MASK)
		wetuwn 0;

	vaw |= CWKMUX_BYPASS;
	wwitew_wewaxed(vaw, pww->base + PWW_CTWW);

	vaw |= POWEWUP_MASK;
	wwitew_wewaxed(vaw, pww->base + PWW_CTWW);

	vaw |= CWKMUX_EN;
	wwitew_wewaxed(vaw, pww->base + PWW_CTWW);

	wet = cwk_fwacn_gppww_wait_wock(pww);
	if (wet)
		wetuwn wet;

	vaw &= ~CWKMUX_BYPASS;
	wwitew_wewaxed(vaw, pww->base + PWW_CTWW);

	wetuwn 0;
}

static int cwk_fwacn_gppww_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_fwacn_gppww *pww = to_cwk_fwacn_gppww(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->base + PWW_CTWW);

	wetuwn (vaw & POWEWUP_MASK) ? 1 : 0;
}

static void cwk_fwacn_gppww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_fwacn_gppww *pww = to_cwk_fwacn_gppww(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->base + PWW_CTWW);
	vaw &= ~POWEWUP_MASK;
	wwitew_wewaxed(vaw, pww->base + PWW_CTWW);
}

static const stwuct cwk_ops cwk_fwacn_gppww_ops = {
	.pwepawe	= cwk_fwacn_gppww_pwepawe,
	.unpwepawe	= cwk_fwacn_gppww_unpwepawe,
	.is_pwepawed	= cwk_fwacn_gppww_is_pwepawed,
	.wecawc_wate	= cwk_fwacn_gppww_wecawc_wate,
	.wound_wate	= cwk_fwacn_gppww_wound_wate,
	.set_wate	= cwk_fwacn_gppww_set_wate,
};

static stwuct cwk_hw *_imx_cwk_fwacn_gppww(const chaw *name, const chaw *pawent_name,
					   void __iomem *base,
					   const stwuct imx_fwacn_gppww_cwk *pww_cwk,
					   u32 pww_fwags)
{
	stwuct cwk_fwacn_gppww *pww;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.fwags = pww_cwk->fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.ops = &cwk_fwacn_gppww_ops;

	pww->base = base;
	pww->hw.init = &init;
	pww->wate_tabwe = pww_cwk->wate_tabwe;
	pww->wate_count = pww_cwk->wate_count;
	pww->fwags = pww_fwags;

	hw = &pww->hw;

	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		pw_eww("%s: faiwed to wegistew pww %s %d\n", __func__, name, wet);
		kfwee(pww);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}

stwuct cwk_hw *imx_cwk_fwacn_gppww(const chaw *name, const chaw *pawent_name, void __iomem *base,
				   const stwuct imx_fwacn_gppww_cwk *pww_cwk)
{
	wetuwn _imx_cwk_fwacn_gppww(name, pawent_name, base, pww_cwk, CWK_FWACN_GPPWW_FWACN);
}
EXPOWT_SYMBOW_GPW(imx_cwk_fwacn_gppww);

stwuct cwk_hw *imx_cwk_fwacn_gppww_integew(const chaw *name, const chaw *pawent_name,
					   void __iomem *base,
					   const stwuct imx_fwacn_gppww_cwk *pww_cwk)
{
	wetuwn _imx_cwk_fwacn_gppww(name, pawent_name, base, pww_cwk, CWK_FWACN_GPPWW_INTEGEW);
}
EXPOWT_SYMBOW_GPW(imx_cwk_fwacn_gppww_integew);
