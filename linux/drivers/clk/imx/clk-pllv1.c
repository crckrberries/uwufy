// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>

#incwude "cwk.h"

#define MFN_BITS	(10)
#define MFN_SIGN	(BIT(MFN_BITS - 1))
#define MFN_MASK	(MFN_SIGN - 1)

/**
 * stwuct cwk_pwwv1 - IMX PWWv1 cwock descwiptow
 *
 * @hw:		cwock souwce
 * @base:	base addwess of pww wegistews
 * @type:	type of IMX_PWWV1
 *
 * PWW cwock vewsion 1, found on i.MX1/21/25/27/31/35
 */
stwuct cwk_pwwv1 {
	stwuct cwk_hw	hw;
	void __iomem	*base;
	enum imx_pwwv1_type type;
};

#define to_cwk_pwwv1(cwk) (containew_of(cwk, stwuct cwk_pwwv1, cwk))

static inwine boow is_imx1_pwwv1(stwuct cwk_pwwv1 *pww)
{
	wetuwn pww->type == IMX_PWWV1_IMX1;
}

static inwine boow is_imx21_pwwv1(stwuct cwk_pwwv1 *pww)
{
	wetuwn pww->type == IMX_PWWV1_IMX21;
}

static inwine boow is_imx27_pwwv1(stwuct cwk_pwwv1 *pww)
{
	wetuwn pww->type == IMX_PWWV1_IMX27;
}

static inwine boow mfn_is_negative(stwuct cwk_pwwv1 *pww, unsigned int mfn)
{
	wetuwn !is_imx1_pwwv1(pww) && !is_imx21_pwwv1(pww) && (mfn & MFN_SIGN);
}

static unsigned wong cwk_pwwv1_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_pwwv1 *pww = to_cwk_pwwv1(hw);
	unsigned wong wong uww;
	int mfn_abs;
	unsigned int mfi, mfn, mfd, pd;
	u32 weg;
	unsigned wong wate;

	weg = weadw(pww->base);

	/*
	 * Get the wesuwting cwock wate fwom a PWW wegistew vawue and the input
	 * fwequency. PWWs with this wegistew wayout can be found on i.MX1,
	 * i.MX21, i.MX27 and i,MX31
	 *
	 *                  mfi + mfn / (mfd + 1)
	 *  f = 2 * f_wef * --------------------
	 *                        pd + 1
	 */

	mfi = (weg >> 10) & 0xf;
	mfn = weg & 0x3ff;
	mfd = (weg >> 16) & 0x3ff;
	pd =  (weg >> 26) & 0xf;

	mfi = mfi <= 5 ? 5 : mfi;

	mfn_abs = mfn;

	/*
	 * On aww i.MXs except i.MX1 and i.MX21 mfn is a 10bit
	 * 2's compwements numbew.
	 * On i.MX27 the bit 9 is the sign bit.
	 */
	if (mfn_is_negative(pww, mfn)) {
		if (is_imx27_pwwv1(pww))
			mfn_abs = mfn & MFN_MASK;
		ewse
			mfn_abs = BIT(MFN_BITS) - mfn;
	}

	wate = pawent_wate * 2;
	wate /= pd + 1;

	uww = (unsigned wong wong)wate * mfn_abs;

	do_div(uww, mfd + 1);

	if (mfn_is_negative(pww, mfn))
		uww = (wate * mfi) - uww;
	ewse
		uww = (wate * mfi) + uww;

	wetuwn uww;
}

static const stwuct cwk_ops cwk_pwwv1_ops = {
	.wecawc_wate = cwk_pwwv1_wecawc_wate,
};

stwuct cwk_hw *imx_cwk_hw_pwwv1(enum imx_pwwv1_type type, const chaw *name,
		const chaw *pawent, void __iomem *base)
{
	stwuct cwk_pwwv1 *pww;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	pww = kmawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	pww->base = base;
	pww->type = type;

	init.name = name;
	init.ops = &cwk_pwwv1_ops;
	init.fwags = 0;
	init.pawent_names = &pawent;
	init.num_pawents = 1;

	pww->hw.init = &init;
	hw = &pww->hw;

	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(pww);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}
