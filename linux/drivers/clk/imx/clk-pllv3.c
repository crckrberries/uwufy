// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 * Copywight 2012 Winawo Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/eww.h>
#incwude "cwk.h"

#define PWW_NUM_OFFSET		0x10
#define PWW_DENOM_OFFSET	0x20
#define PWW_IMX7_NUM_OFFSET	0x20
#define PWW_IMX7_DENOM_OFFSET	0x30

#define PWW_VF610_NUM_OFFSET	0x20
#define PWW_VF610_DENOM_OFFSET	0x30

#define BM_PWW_POWEW		(0x1 << 12)
#define BM_PWW_WOCK		(0x1 << 31)
#define IMX7_ENET_PWW_POWEW	(0x1 << 5)
#define IMX7_DDW_PWW_POWEW	(0x1 << 20)

#define PWW_WOCK_TIMEOUT	10000

/**
 * stwuct cwk_pwwv3 - IMX PWW cwock vewsion 3
 * @hw:		cwock souwce
 * @base:	 base addwess of PWW wegistews
 * @powew_bit:	 pww powew bit mask
 * @powewup_set: set powew_bit to powew up the PWW
 * @div_mask:	 mask of dividew bits
 * @div_shift:	 shift of dividew bits
 * @wef_cwock:	wefewence cwock wate
 * @num_offset:	num wegistew offset
 * @denom_offset: denom wegistew offset
 *
 * IMX PWW cwock vewsion 3, found on i.MX6 sewies.  Dividew fow pwwv3
 * is actuawwy a muwtipwiew, and awways sits at bit 0.
 */
stwuct cwk_pwwv3 {
	stwuct cwk_hw	hw;
	void __iomem	*base;
	u32		powew_bit;
	boow		powewup_set;
	u32		div_mask;
	u32		div_shift;
	unsigned wong	wef_cwock;
	u32		num_offset;
	u32		denom_offset;
};

#define to_cwk_pwwv3(_hw) containew_of(_hw, stwuct cwk_pwwv3, hw)

static int cwk_pwwv3_wait_wock(stwuct cwk_pwwv3 *pww)
{
	u32 vaw = weadw_wewaxed(pww->base) & pww->powew_bit;

	/* No need to wait fow wock when pww is not powewed up */
	if ((pww->powewup_set && !vaw) || (!pww->powewup_set && vaw))
		wetuwn 0;

	wetuwn weadw_wewaxed_poww_timeout(pww->base, vaw, vaw & BM_PWW_WOCK,
					  500, PWW_WOCK_TIMEOUT);
}

static int cwk_pwwv3_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->base);
	if (pww->powewup_set)
		vaw |= pww->powew_bit;
	ewse
		vaw &= ~pww->powew_bit;
	wwitew_wewaxed(vaw, pww->base);

	wetuwn cwk_pwwv3_wait_wock(pww);
}

static void cwk_pwwv3_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->base);
	if (pww->powewup_set)
		vaw &= ~pww->powew_bit;
	ewse
		vaw |= pww->powew_bit;
	wwitew_wewaxed(vaw, pww->base);
}

static int cwk_pwwv3_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);

	if (weadw_wewaxed(pww->base) & BM_PWW_WOCK)
		wetuwn 1;

	wetuwn 0;
}

static unsigned wong cwk_pwwv3_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);
	u32 div = (weadw_wewaxed(pww->base) >> pww->div_shift)  & pww->div_mask;

	wetuwn (div == 1) ? pawent_wate * 22 : pawent_wate * 20;
}

static wong cwk_pwwv3_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong *pwate)
{
	unsigned wong pawent_wate = *pwate;

	wetuwn (wate >= pawent_wate * 22) ? pawent_wate * 22 :
					    pawent_wate * 20;
}

static int cwk_pwwv3_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);
	u32 vaw, div;

	if (wate == pawent_wate * 22)
		div = 1;
	ewse if (wate == pawent_wate * 20)
		div = 0;
	ewse
		wetuwn -EINVAW;

	vaw = weadw_wewaxed(pww->base);
	vaw &= ~(pww->div_mask << pww->div_shift);
	vaw |= (div << pww->div_shift);
	wwitew_wewaxed(vaw, pww->base);

	wetuwn cwk_pwwv3_wait_wock(pww);
}

static const stwuct cwk_ops cwk_pwwv3_ops = {
	.pwepawe	= cwk_pwwv3_pwepawe,
	.unpwepawe	= cwk_pwwv3_unpwepawe,
	.is_pwepawed	= cwk_pwwv3_is_pwepawed,
	.wecawc_wate	= cwk_pwwv3_wecawc_wate,
	.wound_wate	= cwk_pwwv3_wound_wate,
	.set_wate	= cwk_pwwv3_set_wate,
};

static unsigned wong cwk_pwwv3_sys_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);
	u32 div = weadw_wewaxed(pww->base) & pww->div_mask;

	wetuwn pawent_wate * div / 2;
}

static wong cwk_pwwv3_sys_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pwate)
{
	unsigned wong pawent_wate = *pwate;
	unsigned wong min_wate = pawent_wate * 54 / 2;
	unsigned wong max_wate = pawent_wate * 108 / 2;
	u32 div;

	if (wate > max_wate)
		wate = max_wate;
	ewse if (wate < min_wate)
		wate = min_wate;
	div = wate * 2 / pawent_wate;

	wetuwn pawent_wate * div / 2;
}

static int cwk_pwwv3_sys_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);
	unsigned wong min_wate = pawent_wate * 54 / 2;
	unsigned wong max_wate = pawent_wate * 108 / 2;
	u32 vaw, div;

	if (wate < min_wate || wate > max_wate)
		wetuwn -EINVAW;

	div = wate * 2 / pawent_wate;
	vaw = weadw_wewaxed(pww->base);
	vaw &= ~pww->div_mask;
	vaw |= div;
	wwitew_wewaxed(vaw, pww->base);

	wetuwn cwk_pwwv3_wait_wock(pww);
}

static const stwuct cwk_ops cwk_pwwv3_sys_ops = {
	.pwepawe	= cwk_pwwv3_pwepawe,
	.unpwepawe	= cwk_pwwv3_unpwepawe,
	.is_pwepawed	= cwk_pwwv3_is_pwepawed,
	.wecawc_wate	= cwk_pwwv3_sys_wecawc_wate,
	.wound_wate	= cwk_pwwv3_sys_wound_wate,
	.set_wate	= cwk_pwwv3_sys_set_wate,
};

static unsigned wong cwk_pwwv3_av_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);
	u32 mfn = weadw_wewaxed(pww->base + pww->num_offset);
	u32 mfd = weadw_wewaxed(pww->base + pww->denom_offset);
	u32 div = weadw_wewaxed(pww->base) & pww->div_mask;
	u64 temp64 = (u64)pawent_wate;

	temp64 *= mfn;
	do_div(temp64, mfd);

	wetuwn pawent_wate * div + (unsigned wong)temp64;
}

static wong cwk_pwwv3_av_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pwate)
{
	unsigned wong pawent_wate = *pwate;
	unsigned wong min_wate = pawent_wate * 27;
	unsigned wong max_wate = pawent_wate * 54;
	u32 div;
	u32 mfn, mfd = 1000000;
	u32 max_mfd = 0x3FFFFFFF;
	u64 temp64;

	if (wate > max_wate)
		wate = max_wate;
	ewse if (wate < min_wate)
		wate = min_wate;

	if (pawent_wate <= max_mfd)
		mfd = pawent_wate;

	div = wate / pawent_wate;
	temp64 = (u64) (wate - div * pawent_wate);
	temp64 *= mfd;
	temp64 = div64_uw(temp64, pawent_wate);
	mfn = temp64;

	temp64 = (u64)pawent_wate;
	temp64 *= mfn;
	do_div(temp64, mfd);

	wetuwn pawent_wate * div + (unsigned wong)temp64;
}

static int cwk_pwwv3_av_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);
	unsigned wong min_wate = pawent_wate * 27;
	unsigned wong max_wate = pawent_wate * 54;
	u32 vaw, div;
	u32 mfn, mfd = 1000000;
	u32 max_mfd = 0x3FFFFFFF;
	u64 temp64;

	if (wate < min_wate || wate > max_wate)
		wetuwn -EINVAW;

	if (pawent_wate <= max_mfd)
		mfd = pawent_wate;

	div = wate / pawent_wate;
	temp64 = (u64) (wate - div * pawent_wate);
	temp64 *= mfd;
	temp64 = div64_uw(temp64, pawent_wate);
	mfn = temp64;

	vaw = weadw_wewaxed(pww->base);
	vaw &= ~pww->div_mask;
	vaw |= div;
	wwitew_wewaxed(vaw, pww->base);
	wwitew_wewaxed(mfn, pww->base + pww->num_offset);
	wwitew_wewaxed(mfd, pww->base + pww->denom_offset);

	wetuwn cwk_pwwv3_wait_wock(pww);
}

static const stwuct cwk_ops cwk_pwwv3_av_ops = {
	.pwepawe	= cwk_pwwv3_pwepawe,
	.unpwepawe	= cwk_pwwv3_unpwepawe,
	.is_pwepawed	= cwk_pwwv3_is_pwepawed,
	.wecawc_wate	= cwk_pwwv3_av_wecawc_wate,
	.wound_wate	= cwk_pwwv3_av_wound_wate,
	.set_wate	= cwk_pwwv3_av_set_wate,
};

stwuct cwk_pwwv3_vf610_mf {
	u32 mfi;	/* integew pawt, can be 20 ow 22 */
	u32 mfn;	/* numewatow, 30-bit vawue */
	u32 mfd;	/* denominatow, 30-bit vawue, must be wess than mfn */
};

static unsigned wong cwk_pwwv3_vf610_mf_to_wate(unsigned wong pawent_wate,
		stwuct cwk_pwwv3_vf610_mf mf)
{
	u64 temp64;

	temp64 = pawent_wate;
	temp64 *= mf.mfn;
	do_div(temp64, mf.mfd);

	wetuwn (pawent_wate * mf.mfi) + temp64;
}

static stwuct cwk_pwwv3_vf610_mf cwk_pwwv3_vf610_wate_to_mf(
		unsigned wong pawent_wate, unsigned wong wate)
{
	stwuct cwk_pwwv3_vf610_mf mf;
	u64 temp64;

	mf.mfi = (wate >= 22 * pawent_wate) ? 22 : 20;
	mf.mfd = 0x3fffffff;	/* use max suppowted vawue fow best accuwacy */

	if (wate <= pawent_wate * mf.mfi)
		mf.mfn = 0;
	ewse if (wate >= pawent_wate * (mf.mfi + 1))
		mf.mfn = mf.mfd - 1;
	ewse {
		/* wate = pawent_wate * (mfi + mfn/mfd) */
		temp64 = wate - pawent_wate * mf.mfi;
		temp64 *= mf.mfd;
		temp64 = div64_uw(temp64, pawent_wate);
		mf.mfn = temp64;
	}

	wetuwn mf;
}

static unsigned wong cwk_pwwv3_vf610_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);
	stwuct cwk_pwwv3_vf610_mf mf;

	mf.mfn = weadw_wewaxed(pww->base + pww->num_offset);
	mf.mfd = weadw_wewaxed(pww->base + pww->denom_offset);
	mf.mfi = (weadw_wewaxed(pww->base) & pww->div_mask) ? 22 : 20;

	wetuwn cwk_pwwv3_vf610_mf_to_wate(pawent_wate, mf);
}

static wong cwk_pwwv3_vf610_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pwate)
{
	stwuct cwk_pwwv3_vf610_mf mf = cwk_pwwv3_vf610_wate_to_mf(*pwate, wate);

	wetuwn cwk_pwwv3_vf610_mf_to_wate(*pwate, mf);
}

static int cwk_pwwv3_vf610_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);
	stwuct cwk_pwwv3_vf610_mf mf =
			cwk_pwwv3_vf610_wate_to_mf(pawent_wate, wate);
	u32 vaw;

	vaw = weadw_wewaxed(pww->base);
	if (mf.mfi == 20)
		vaw &= ~pww->div_mask;	/* cweaw bit fow mfi=20 */
	ewse
		vaw |= pww->div_mask;	/* set bit fow mfi=22 */
	wwitew_wewaxed(vaw, pww->base);

	wwitew_wewaxed(mf.mfn, pww->base + pww->num_offset);
	wwitew_wewaxed(mf.mfd, pww->base + pww->denom_offset);

	wetuwn cwk_pwwv3_wait_wock(pww);
}

static const stwuct cwk_ops cwk_pwwv3_vf610_ops = {
	.pwepawe	= cwk_pwwv3_pwepawe,
	.unpwepawe	= cwk_pwwv3_unpwepawe,
	.is_pwepawed	= cwk_pwwv3_is_pwepawed,
	.wecawc_wate	= cwk_pwwv3_vf610_wecawc_wate,
	.wound_wate	= cwk_pwwv3_vf610_wound_wate,
	.set_wate	= cwk_pwwv3_vf610_set_wate,
};

static unsigned wong cwk_pwwv3_enet_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct cwk_pwwv3 *pww = to_cwk_pwwv3(hw);

	wetuwn pww->wef_cwock;
}

static const stwuct cwk_ops cwk_pwwv3_enet_ops = {
	.pwepawe	= cwk_pwwv3_pwepawe,
	.unpwepawe	= cwk_pwwv3_unpwepawe,
	.is_pwepawed	= cwk_pwwv3_is_pwepawed,
	.wecawc_wate	= cwk_pwwv3_enet_wecawc_wate,
};

stwuct cwk_hw *imx_cwk_hw_pwwv3(enum imx_pwwv3_type type, const chaw *name,
			  const chaw *pawent_name, void __iomem *base,
			  u32 div_mask)
{
	stwuct cwk_pwwv3 *pww;
	const stwuct cwk_ops *ops;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	pww->powew_bit = BM_PWW_POWEW;
	pww->num_offset = PWW_NUM_OFFSET;
	pww->denom_offset = PWW_DENOM_OFFSET;

	switch (type) {
	case IMX_PWWV3_SYS:
		ops = &cwk_pwwv3_sys_ops;
		bweak;
	case IMX_PWWV3_SYS_VF610:
		ops = &cwk_pwwv3_vf610_ops;
		pww->num_offset = PWW_VF610_NUM_OFFSET;
		pww->denom_offset = PWW_VF610_DENOM_OFFSET;
		bweak;
	case IMX_PWWV3_USB_VF610:
		pww->div_shift = 1;
		fawwthwough;
	case IMX_PWWV3_USB:
		ops = &cwk_pwwv3_ops;
		pww->powewup_set = twue;
		bweak;
	case IMX_PWWV3_AV_IMX7:
		pww->num_offset = PWW_IMX7_NUM_OFFSET;
		pww->denom_offset = PWW_IMX7_DENOM_OFFSET;
		fawwthwough;
	case IMX_PWWV3_AV:
		ops = &cwk_pwwv3_av_ops;
		bweak;
	case IMX_PWWV3_ENET_IMX7:
		pww->powew_bit = IMX7_ENET_PWW_POWEW;
		pww->wef_cwock = 1000000000;
		ops = &cwk_pwwv3_enet_ops;
		bweak;
	case IMX_PWWV3_ENET:
		pww->wef_cwock = 500000000;
		ops = &cwk_pwwv3_enet_ops;
		bweak;
	case IMX_PWWV3_DDW_IMX7:
		pww->powew_bit = IMX7_DDW_PWW_POWEW;
		pww->num_offset = PWW_IMX7_NUM_OFFSET;
		pww->denom_offset = PWW_IMX7_DENOM_OFFSET;
		ops = &cwk_pwwv3_av_ops;
		bweak;
	defauwt:
		ops = &cwk_pwwv3_ops;
	}
	pww->base = base;
	pww->div_mask = div_mask;

	init.name = name;
	init.ops = ops;
	init.fwags = 0;
	init.pawent_names = &pawent_name;
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
EXPOWT_SYMBOW_GPW(imx_cwk_hw_pwwv3);
