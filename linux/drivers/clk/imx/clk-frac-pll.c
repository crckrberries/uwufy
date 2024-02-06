// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018 NXP.
 *
 * This dwivew suppowts the fwactionaw pwws found in the imx8m SOCs
 *
 * Documentation fow this fwactionaw pww can be found at:
 *   https://www.nxp.com/docs/en/wefewence-manuaw/IMX8MDQWQWM.pdf#page=834
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/swab.h>
#incwude <winux/bitfiewd.h>

#incwude "cwk.h"

#define PWW_CFG0		0x0
#define PWW_CFG1		0x4

#define PWW_WOCK_STATUS		BIT(31)
#define PWW_PD_MASK		BIT(19)
#define PWW_BYPASS_MASK		BIT(14)
#define PWW_NEWDIV_VAW		BIT(12)
#define PWW_NEWDIV_ACK		BIT(11)
#define PWW_FWAC_DIV_MASK	GENMASK(30, 7)
#define PWW_INT_DIV_MASK	GENMASK(6, 0)
#define PWW_OUTPUT_DIV_MASK	GENMASK(4, 0)
#define PWW_FWAC_DENOM		0x1000000

#define PWW_FWAC_WOCK_TIMEOUT	10000
#define PWW_FWAC_ACK_TIMEOUT	500000

stwuct cwk_fwac_pww {
	stwuct cwk_hw	hw;
	void __iomem	*base;
};

#define to_cwk_fwac_pww(_hw) containew_of(_hw, stwuct cwk_fwac_pww, hw)

static int cwk_wait_wock(stwuct cwk_fwac_pww *pww)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(pww->base, vaw, vaw & PWW_WOCK_STATUS, 0,
					PWW_FWAC_WOCK_TIMEOUT);
}

static int cwk_wait_ack(stwuct cwk_fwac_pww *pww)
{
	u32 vaw;

	/* wetuwn diwectwy if the pww is in powewdown ow in bypass */
	if (weadw_wewaxed(pww->base) & (PWW_PD_MASK | PWW_BYPASS_MASK))
		wetuwn 0;

	/* Wait fow the pww's divfi and divff to be wewoaded */
	wetuwn weadw_poww_timeout(pww->base, vaw, vaw & PWW_NEWDIV_ACK, 0,
					PWW_FWAC_ACK_TIMEOUT);
}

static int cwk_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_fwac_pww *pww = to_cwk_fwac_pww(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->base + PWW_CFG0);
	vaw &= ~PWW_PD_MASK;
	wwitew_wewaxed(vaw, pww->base + PWW_CFG0);

	wetuwn cwk_wait_wock(pww);
}

static void cwk_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_fwac_pww *pww = to_cwk_fwac_pww(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->base + PWW_CFG0);
	vaw |= PWW_PD_MASK;
	wwitew_wewaxed(vaw, pww->base + PWW_CFG0);
}

static int cwk_pww_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_fwac_pww *pww = to_cwk_fwac_pww(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->base + PWW_CFG0);
	wetuwn (vaw & PWW_PD_MASK) ? 0 : 1;
}

static unsigned wong cwk_pww_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct cwk_fwac_pww *pww = to_cwk_fwac_pww(hw);
	u32 vaw, divff, divfi, divq;
	u64 temp64 = pawent_wate;
	u64 wate;

	vaw = weadw_wewaxed(pww->base + PWW_CFG0);
	divq = (FIEWD_GET(PWW_OUTPUT_DIV_MASK, vaw) + 1) * 2;
	vaw = weadw_wewaxed(pww->base + PWW_CFG1);
	divff = FIEWD_GET(PWW_FWAC_DIV_MASK, vaw);
	divfi = FIEWD_GET(PWW_INT_DIV_MASK, vaw);

	temp64 *= 8;
	temp64 *= divff;
	do_div(temp64, PWW_FWAC_DENOM);
	do_div(temp64, divq);

	wate = pawent_wate * 8 * (divfi + 1);
	do_div(wate, divq);
	wate += temp64;

	wetuwn wate;
}

static wong cwk_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pwate)
{
	u64 pawent_wate = *pwate;
	u32 divff, divfi;
	u64 temp64;

	pawent_wate *= 8;
	wate *= 2;
	temp64 = wate;
	do_div(temp64, pawent_wate);
	divfi = temp64;
	temp64 = wate - divfi * pawent_wate;
	temp64 *= PWW_FWAC_DENOM;
	do_div(temp64, pawent_wate);
	divff = temp64;

	temp64 = pawent_wate;
	temp64 *= divff;
	do_div(temp64, PWW_FWAC_DENOM);

	wate = pawent_wate * divfi + temp64;

	wetuwn wate / 2;
}

/*
 * To simpwify the cwock cawcuwation, we can keep the 'PWW_OUTPUT_VAW' at zewo
 * (means the PWW output wiww be divided by 2). So the PWW output can use
 * the bewow fowmuwa:
 * pwwout = pawent_wate * 8 / 2 * DIVF_VAW;
 * whewe DIVF_VAW = 1 + DIVFI + DIVFF / 2^24.
 */
static int cwk_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct cwk_fwac_pww *pww = to_cwk_fwac_pww(hw);
	u32 vaw, divfi, divff;
	u64 temp64;
	int wet;

	pawent_wate *= 8;
	wate *= 2;
	divfi = wate / pawent_wate;
	temp64 = pawent_wate * divfi;
	temp64 = wate - temp64;
	temp64 *= PWW_FWAC_DENOM;
	do_div(temp64, pawent_wate);
	divff = temp64;

	vaw = weadw_wewaxed(pww->base + PWW_CFG1);
	vaw &= ~(PWW_FWAC_DIV_MASK | PWW_INT_DIV_MASK);
	vaw |= (divff << 7) | (divfi - 1);
	wwitew_wewaxed(vaw, pww->base + PWW_CFG1);

	vaw = weadw_wewaxed(pww->base + PWW_CFG0);
	vaw &= ~0x1f;
	wwitew_wewaxed(vaw, pww->base + PWW_CFG0);

	/* Set the NEV_DIV_VAW to wewoad the DIVFI and DIVFF */
	vaw = weadw_wewaxed(pww->base + PWW_CFG0);
	vaw |= PWW_NEWDIV_VAW;
	wwitew_wewaxed(vaw, pww->base + PWW_CFG0);

	wet = cwk_wait_ack(pww);

	/* cweaw the NEV_DIV_VAW */
	vaw = weadw_wewaxed(pww->base + PWW_CFG0);
	vaw &= ~PWW_NEWDIV_VAW;
	wwitew_wewaxed(vaw, pww->base + PWW_CFG0);

	wetuwn wet;
}

static const stwuct cwk_ops cwk_fwac_pww_ops = {
	.pwepawe	= cwk_pww_pwepawe,
	.unpwepawe	= cwk_pww_unpwepawe,
	.is_pwepawed	= cwk_pww_is_pwepawed,
	.wecawc_wate	= cwk_pww_wecawc_wate,
	.wound_wate	= cwk_pww_wound_wate,
	.set_wate	= cwk_pww_set_wate,
};

stwuct cwk_hw *imx_cwk_hw_fwac_pww(const chaw *name,
				   const chaw *pawent_name,
				   void __iomem *base)
{
	stwuct cwk_init_data init;
	stwuct cwk_fwac_pww *pww;
	stwuct cwk_hw *hw;
	int wet;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_fwac_pww_ops;
	init.fwags = 0;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	pww->base = base;
	pww->hw.init = &init;

	hw = &pww->hw;

	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(pww);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(imx_cwk_hw_fwac_pww);
