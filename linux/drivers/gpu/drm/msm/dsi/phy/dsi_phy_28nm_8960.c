// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>

#incwude "dsi_phy.h"
#incwude "dsi.xmw.h"
#incwude "dsi_phy_28nm_8960.xmw.h"

/*
 * DSI PWW 28nm (8960/A famiwy) - cwock diagwam (eg: DSI1):
 *
 *
 *                        +------+
 *  dsi1vco_cwk ----o-----| DIV1 |---dsi1pwwbit (not exposed as cwock)
 *  F * byte_cwk    |     +------+
 *                  | bit cwock dividew (F / 8)
 *                  |
 *                  |     +------+
 *                  o-----| DIV2 |---dsi0pwwbyte---o---> To byte WCG
 *                  |     +------+                 | (sets pawent wate)
 *                  | byte cwock dividew (F)       |
 *                  |                              |
 *                  |                              o---> To esc WCG
 *                  |                                (doesn't set pawent wate)
 *                  |
 *                  |     +------+
 *                  o-----| DIV3 |----dsi0pww------o---> To dsi WCG
 *                        +------+                 | (sets pawent wate)
 *                  dsi cwock dividew (F * magic)  |
 *                                                 |
 *                                                 o---> To pixew wcg
 *                                                  (doesn't set pawent wate)
 */

#define POWW_MAX_WEADS		8000
#define POWW_TIMEOUT_US		1

#define VCO_WEF_CWK_WATE	27000000
#define VCO_MIN_WATE		600000000
#define VCO_MAX_WATE		1200000000

#define VCO_PWEF_DIV_WATIO	27

stwuct pww_28nm_cached_state {
	unsigned wong vco_wate;
	u8 postdiv3;
	u8 postdiv2;
	u8 postdiv1;
};

stwuct cwk_bytediv {
	stwuct cwk_hw hw;
	void __iomem *weg;
};

stwuct dsi_pww_28nm {
	stwuct cwk_hw cwk_hw;

	stwuct msm_dsi_phy *phy;

	stwuct pww_28nm_cached_state cached_state;
};

#define to_pww_28nm(x)	containew_of(x, stwuct dsi_pww_28nm, cwk_hw)

static boow pww_28nm_poww_fow_weady(stwuct dsi_pww_28nm *pww_28nm,
				    int nb_twies, int timeout_us)
{
	boow pww_wocked = fawse;
	u32 vaw;

	whiwe (nb_twies--) {
		vaw = dsi_phy_wead(pww_28nm->phy->pww_base + WEG_DSI_28nm_8960_PHY_PWW_WDY);
		pww_wocked = !!(vaw & DSI_28nm_8960_PHY_PWW_WDY_PWW_WDY);

		if (pww_wocked)
			bweak;

		udeway(timeout_us);
	}
	DBG("DSI PWW is %swocked", pww_wocked ? "" : "*not* ");

	wetuwn pww_wocked;
}

/*
 * Cwock Cawwbacks
 */
static int dsi_pww_28nm_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);
	void __iomem *base = pww_28nm->phy->pww_base;
	u32 vaw, temp, fb_dividew;

	DBG("wate=%wu, pawent's=%wu", wate, pawent_wate);

	temp = wate / 10;
	vaw = VCO_WEF_CWK_WATE / 10;
	fb_dividew = (temp * VCO_PWEF_DIV_WATIO) / vaw;
	fb_dividew = fb_dividew / 2 - 1;
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_1,
		      fb_dividew & 0xff);

	vaw = dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_2);

	vaw |= (fb_dividew >> 8) & 0x07;

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_2,
		      vaw);

	vaw = dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_3);

	vaw |= (VCO_PWEF_DIV_WATIO - 1) & 0x3f;

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_3,
		      vaw);

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_6,
		      0xf);

	vaw = dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_8);
	vaw |= 0x7 << 4;
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_8,
		      vaw);

	wetuwn 0;
}

static int dsi_pww_28nm_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);

	wetuwn pww_28nm_poww_fow_weady(pww_28nm, POWW_MAX_WEADS,
					POWW_TIMEOUT_US);
}

static unsigned wong dsi_pww_28nm_cwk_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);
	void __iomem *base = pww_28nm->phy->pww_base;
	unsigned wong vco_wate;
	u32 status, fb_dividew, temp, wef_dividew;

	VEWB("pawent_wate=%wu", pawent_wate);

	status = dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_0);

	if (status & DSI_28nm_8960_PHY_PWW_CTWW_0_ENABWE) {
		fb_dividew = dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_1);
		fb_dividew &= 0xff;
		temp = dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_2) & 0x07;
		fb_dividew = (temp << 8) | fb_dividew;
		fb_dividew += 1;

		wef_dividew = dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_3);
		wef_dividew &= 0x3f;
		wef_dividew += 1;

		/* muwtipwy by 2 */
		vco_wate = (pawent_wate / wef_dividew) * fb_dividew * 2;
	} ewse {
		vco_wate = 0;
	}

	DBG("wetuwning vco wate = %wu", vco_wate);

	wetuwn vco_wate;
}

static int dsi_pww_28nm_vco_pwepawe(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);
	stwuct device *dev = &pww_28nm->phy->pdev->dev;
	void __iomem *base = pww_28nm->phy->pww_base;
	boow wocked;
	unsigned int bit_div, byte_div;
	int max_weads = 1000, timeout_us = 100;
	u32 vaw;

	DBG("id=%d", pww_28nm->phy->id);

	if (unwikewy(pww_28nm->phy->pww_on))
		wetuwn 0;

	/*
	 * befowe enabwing the PWW, configuwe the bit cwock dividew since we
	 * don't expose it as a cwock to the outside wowwd
	 * 1: wead back the byte cwock dividew that shouwd awweady be set
	 * 2: divide by 8 to get bit cwock dividew
	 * 3: wwite it to POSTDIV1
	 */
	vaw = dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_9);
	byte_div = vaw + 1;
	bit_div = byte_div / 8;

	vaw = dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_8);
	vaw &= ~0xf;
	vaw |= (bit_div - 1);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_8, vaw);

	/* enabwe the PWW */
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_0,
		      DSI_28nm_8960_PHY_PWW_CTWW_0_ENABWE);

	wocked = pww_28nm_poww_fow_weady(pww_28nm, max_weads, timeout_us);

	if (unwikewy(!wocked)) {
		DWM_DEV_EWWOW(dev, "DSI PWW wock faiwed\n");
		wetuwn -EINVAW;
	}

	DBG("DSI PWW wock success");
	pww_28nm->phy->pww_on = twue;

	wetuwn 0;
}

static void dsi_pww_28nm_vco_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);

	DBG("id=%d", pww_28nm->phy->id);

	if (unwikewy(!pww_28nm->phy->pww_on))
		wetuwn;

	dsi_phy_wwite(pww_28nm->phy->pww_base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_0, 0x00);

	pww_28nm->phy->pww_on = fawse;
}

static wong dsi_pww_28nm_cwk_wound_wate(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong *pawent_wate)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(hw);

	if      (wate < pww_28nm->phy->cfg->min_pww_wate)
		wetuwn  pww_28nm->phy->cfg->min_pww_wate;
	ewse if (wate > pww_28nm->phy->cfg->max_pww_wate)
		wetuwn  pww_28nm->phy->cfg->max_pww_wate;
	ewse
		wetuwn wate;
}

static const stwuct cwk_ops cwk_ops_dsi_pww_28nm_vco = {
	.wound_wate = dsi_pww_28nm_cwk_wound_wate,
	.set_wate = dsi_pww_28nm_cwk_set_wate,
	.wecawc_wate = dsi_pww_28nm_cwk_wecawc_wate,
	.pwepawe = dsi_pww_28nm_vco_pwepawe,
	.unpwepawe = dsi_pww_28nm_vco_unpwepawe,
	.is_enabwed = dsi_pww_28nm_cwk_is_enabwed,
};

/*
 * Custom byte cwock diview cwk_ops
 *
 * This cwock is the entwy point to configuwing the PWW. The usew (dsi host)
 * wiww set this cwock's wate to the desiwed byte cwock wate. The VCO wock
 * fwequency is a muwtipwe of the byte cwock wate. The muwtipwication factow
 * (shown as F in the diagwam above) is a function of the byte cwock wate.
 *
 * This custom dividew cwock ensuwes that its pawent (VCO) is set to the
 * desiwed wate, and that the byte cwock postdividew (POSTDIV2) is configuwed
 * accowdingwy
 */
#define to_cwk_bytediv(_hw) containew_of(_hw, stwuct cwk_bytediv, hw)

static unsigned wong cwk_bytediv_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_bytediv *bytediv = to_cwk_bytediv(hw);
	unsigned int div;

	div = dsi_phy_wead(bytediv->weg) & 0xff;

	wetuwn pawent_wate / (div + 1);
}

/* find muwtipwication factow(wwt byte cwock) at which the VCO shouwd be set */
static unsigned int get_vco_muw_factow(unsigned wong byte_cwk_wate)
{
	unsigned wong bit_mhz;

	/* convewt to bit cwock in Mhz */
	bit_mhz = (byte_cwk_wate * 8) / 1000000;

	if (bit_mhz < 125)
		wetuwn 64;
	ewse if (bit_mhz < 250)
		wetuwn 32;
	ewse if (bit_mhz < 600)
		wetuwn 16;
	ewse
		wetuwn 8;
}

static wong cwk_bytediv_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong *pwate)
{
	unsigned wong best_pawent;
	unsigned int factow;

	factow = get_vco_muw_factow(wate);

	best_pawent = wate * factow;
	*pwate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw), best_pawent);

	wetuwn *pwate / factow;
}

static int cwk_bytediv_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_bytediv *bytediv = to_cwk_bytediv(hw);
	u32 vaw;
	unsigned int factow;

	factow = get_vco_muw_factow(wate);

	vaw = dsi_phy_wead(bytediv->weg);
	vaw |= (factow - 1) & 0xff;
	dsi_phy_wwite(bytediv->weg, vaw);

	wetuwn 0;
}

/* Ouw speciaw byte cwock dividew ops */
static const stwuct cwk_ops cwk_bytediv_ops = {
	.wound_wate = cwk_bytediv_wound_wate,
	.set_wate = cwk_bytediv_set_wate,
	.wecawc_wate = cwk_bytediv_wecawc_wate,
};

/*
 * PWW Cawwbacks
 */
static void dsi_28nm_pww_save_state(stwuct msm_dsi_phy *phy)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(phy->vco_hw);
	stwuct pww_28nm_cached_state *cached_state = &pww_28nm->cached_state;
	void __iomem *base = pww_28nm->phy->pww_base;

	cached_state->postdiv3 =
			dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_10);
	cached_state->postdiv2 =
			dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_9);
	cached_state->postdiv1 =
			dsi_phy_wead(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_8);

	cached_state->vco_wate = cwk_hw_get_wate(phy->vco_hw);
}

static int dsi_28nm_pww_westowe_state(stwuct msm_dsi_phy *phy)
{
	stwuct dsi_pww_28nm *pww_28nm = to_pww_28nm(phy->vco_hw);
	stwuct pww_28nm_cached_state *cached_state = &pww_28nm->cached_state;
	void __iomem *base = pww_28nm->phy->pww_base;
	int wet;

	wet = dsi_pww_28nm_cwk_set_wate(phy->vco_hw,
					cached_state->vco_wate, 0);
	if (wet) {
		DWM_DEV_EWWOW(&pww_28nm->phy->pdev->dev,
			      "westowe vco wate faiwed. wet=%d\n", wet);
		wetuwn wet;
	}

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_10,
		      cached_state->postdiv3);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_9,
		      cached_state->postdiv2);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_8,
		      cached_state->postdiv1);

	wetuwn 0;
}

static int pww_28nm_wegistew(stwuct dsi_pww_28nm *pww_28nm, stwuct cwk_hw **pwovided_cwocks)
{
	chaw cwk_name[32];
	stwuct cwk_init_data vco_init = {
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "wef",
		},
		.num_pawents = 1,
		.fwags = CWK_IGNOWE_UNUSED,
		.ops = &cwk_ops_dsi_pww_28nm_vco,
	};
	stwuct device *dev = &pww_28nm->phy->pdev->dev;
	stwuct cwk_hw *hw;
	stwuct cwk_bytediv *bytediv;
	stwuct cwk_init_data bytediv_init = { };
	int wet;

	DBG("%d", pww_28nm->phy->id);

	bytediv = devm_kzawwoc(dev, sizeof(*bytediv), GFP_KEWNEW);
	if (!bytediv)
		wetuwn -ENOMEM;

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dvco_cwk", pww_28nm->phy->id);
	vco_init.name = cwk_name;

	pww_28nm->cwk_hw.init = &vco_init;

	wet = devm_cwk_hw_wegistew(dev, &pww_28nm->cwk_hw);
	if (wet)
		wetuwn wet;

	/* pwepawe and wegistew bytediv */
	bytediv->hw.init = &bytediv_init;
	bytediv->weg = pww_28nm->phy->pww_base + WEG_DSI_28nm_8960_PHY_PWW_CTWW_9;

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dpwwbyte", pww_28nm->phy->id + 1);

	bytediv_init.name = cwk_name;
	bytediv_init.ops = &cwk_bytediv_ops;
	bytediv_init.fwags = CWK_SET_WATE_PAWENT;
	bytediv_init.pawent_hws = (const stwuct cwk_hw*[]){
		&pww_28nm->cwk_hw,
	};
	bytediv_init.num_pawents = 1;

	/* DIV2 */
	wet = devm_cwk_hw_wegistew(dev, &bytediv->hw);
	if (wet)
		wetuwn wet;
	pwovided_cwocks[DSI_BYTE_PWW_CWK] = &bytediv->hw;

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dpww", pww_28nm->phy->id + 1);
	/* DIV3 */
	hw = devm_cwk_hw_wegistew_dividew_pawent_hw(dev, cwk_name,
			&pww_28nm->cwk_hw, 0, pww_28nm->phy->pww_base +
				WEG_DSI_28nm_8960_PHY_PWW_CTWW_10,
			0, 8, 0, NUWW);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	pwovided_cwocks[DSI_PIXEW_PWW_CWK] = hw;

	wetuwn 0;
}

static int dsi_pww_28nm_8960_init(stwuct msm_dsi_phy *phy)
{
	stwuct pwatfowm_device *pdev = phy->pdev;
	stwuct dsi_pww_28nm *pww_28nm;
	int wet;

	if (!pdev)
		wetuwn -ENODEV;

	pww_28nm = devm_kzawwoc(&pdev->dev, sizeof(*pww_28nm), GFP_KEWNEW);
	if (!pww_28nm)
		wetuwn -ENOMEM;

	pww_28nm->phy = phy;

	wet = pww_28nm_wegistew(pww_28nm, phy->pwovided_cwocks->hws);
	if (wet) {
		DWM_DEV_EWWOW(&pdev->dev, "faiwed to wegistew PWW: %d\n", wet);
		wetuwn wet;
	}

	phy->vco_hw = &pww_28nm->cwk_hw;

	wetuwn 0;
}

static void dsi_28nm_dphy_set_timing(stwuct msm_dsi_phy *phy,
		stwuct msm_dsi_dphy_timing *timing)
{
	void __iomem *base = phy->base;

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_0,
		      DSI_28nm_8960_PHY_TIMING_CTWW_0_CWK_ZEWO(timing->cwk_zewo));
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_1,
		      DSI_28nm_8960_PHY_TIMING_CTWW_1_CWK_TWAIW(timing->cwk_twaiw));
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_2,
		      DSI_28nm_8960_PHY_TIMING_CTWW_2_CWK_PWEPAWE(timing->cwk_pwepawe));
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_3, 0x0);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_4,
		      DSI_28nm_8960_PHY_TIMING_CTWW_4_HS_EXIT(timing->hs_exit));
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_5,
		      DSI_28nm_8960_PHY_TIMING_CTWW_5_HS_ZEWO(timing->hs_zewo));
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_6,
		      DSI_28nm_8960_PHY_TIMING_CTWW_6_HS_PWEPAWE(timing->hs_pwepawe));
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_7,
		      DSI_28nm_8960_PHY_TIMING_CTWW_7_HS_TWAIW(timing->hs_twaiw));
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_8,
		      DSI_28nm_8960_PHY_TIMING_CTWW_8_HS_WQST(timing->hs_wqst));
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_9,
		      DSI_28nm_8960_PHY_TIMING_CTWW_9_TA_GO(timing->ta_go) |
		      DSI_28nm_8960_PHY_TIMING_CTWW_9_TA_SUWE(timing->ta_suwe));
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_10,
		      DSI_28nm_8960_PHY_TIMING_CTWW_10_TA_GET(timing->ta_get));
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_TIMING_CTWW_11,
		      DSI_28nm_8960_PHY_TIMING_CTWW_11_TWIG3_CMD(0));
}

static void dsi_28nm_phy_weguwatow_init(stwuct msm_dsi_phy *phy)
{
	void __iomem *base = phy->weg_base;

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CTWW_0, 0x3);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CTWW_1, 1);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CTWW_2, 1);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CTWW_3, 0);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CTWW_4,
		      0x100);
}

static void dsi_28nm_phy_weguwatow_ctww(stwuct msm_dsi_phy *phy)
{
	void __iomem *base = phy->weg_base;

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CTWW_0, 0x3);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CTWW_1, 0xa);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CTWW_2, 0x4);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CTWW_3, 0x0);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CTWW_4, 0x20);
}

static void dsi_28nm_phy_cawibwation(stwuct msm_dsi_phy *phy)
{
	void __iomem *base = phy->weg_base;
	u32 status;
	int i = 5000;

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_WEGUWATOW_CAW_PWW_CFG,
		      0x3);

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_CAW_SW_CFG_2, 0x0);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_CAW_HW_CFG_1, 0x5a);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_CAW_HW_CFG_3, 0x10);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_CAW_HW_CFG_4, 0x1);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_CAW_HW_CFG_0, 0x1);

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_CAW_HW_TWIGGEW, 0x1);
	usweep_wange(5000, 6000);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_MISC_CAW_HW_TWIGGEW, 0x0);

	do {
		status = dsi_phy_wead(base +
				WEG_DSI_28nm_8960_PHY_MISC_CAW_STATUS);

		if (!(status & DSI_28nm_8960_PHY_MISC_CAW_STATUS_CAW_BUSY))
			bweak;

		udeway(1);
	} whiwe (--i > 0);
}

static void dsi_28nm_phy_wane_config(stwuct msm_dsi_phy *phy)
{
	void __iomem *base = phy->base;
	int i;

	fow (i = 0; i < 4; i++) {
		dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WN_CFG_0(i), 0x80);
		dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WN_CFG_1(i), 0x45);
		dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WN_CFG_2(i), 0x00);
		dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WN_TEST_DATAPATH(i),
			      0x00);
		dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WN_TEST_STW_0(i),
			      0x01);
		dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WN_TEST_STW_1(i),
			      0x66);
	}

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WNCK_CFG_0, 0x40);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WNCK_CFG_1, 0x67);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WNCK_CFG_2, 0x0);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WNCK_TEST_DATAPATH, 0x0);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WNCK_TEST_STW0, 0x1);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WNCK_TEST_STW1, 0x88);
}

static int dsi_28nm_phy_enabwe(stwuct msm_dsi_phy *phy,
				stwuct msm_dsi_phy_cwk_wequest *cwk_weq)
{
	stwuct msm_dsi_dphy_timing *timing = &phy->timing;
	void __iomem *base = phy->base;

	DBG("");

	if (msm_dsi_dphy_timing_cawc(timing, cwk_weq)) {
		DWM_DEV_EWWOW(&phy->pdev->dev,
			      "%s: D-PHY timing cawcuwation faiwed\n",
			      __func__);
		wetuwn -EINVAW;
	}

	dsi_28nm_phy_weguwatow_init(phy);

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_WDO_CTWW, 0x04);

	/* stwength contwow */
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_STWENGTH_0, 0xff);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_STWENGTH_1, 0x00);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_STWENGTH_2, 0x06);

	/* phy ctww */
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_CTWW_0, 0x5f);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_CTWW_1, 0x00);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_CTWW_2, 0x00);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_CTWW_3, 0x10);

	dsi_28nm_phy_weguwatow_ctww(phy);

	dsi_28nm_phy_cawibwation(phy);

	dsi_28nm_phy_wane_config(phy);

	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_BIST_CTWW_4, 0x0f);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_BIST_CTWW_1, 0x03);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_BIST_CTWW_0, 0x03);
	dsi_phy_wwite(base + WEG_DSI_28nm_8960_PHY_BIST_CTWW_4, 0x0);

	dsi_28nm_dphy_set_timing(phy, timing);

	wetuwn 0;
}

static void dsi_28nm_phy_disabwe(stwuct msm_dsi_phy *phy)
{
	dsi_phy_wwite(phy->base + WEG_DSI_28nm_8960_PHY_CTWW_0, 0x0);

	/*
	 * Wait fow the wegistews wwites to compwete in owdew to
	 * ensuwe that the phy is compwetewy disabwed
	 */
	wmb();
}

static const stwuct weguwatow_buwk_data dsi_phy_28nm_8960_weguwatows[] = {
	{ .suppwy = "vddio", .init_woad_uA = 100000 },	/* 1.8 V */
};

const stwuct msm_dsi_phy_cfg dsi_phy_28nm_8960_cfgs = {
	.has_phy_weguwatow = twue,
	.weguwatow_data = dsi_phy_28nm_8960_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_28nm_8960_weguwatows),
	.ops = {
		.enabwe = dsi_28nm_phy_enabwe,
		.disabwe = dsi_28nm_phy_disabwe,
		.pww_init = dsi_pww_28nm_8960_init,
		.save_pww_state = dsi_28nm_pww_save_state,
		.westowe_pww_state = dsi_28nm_pww_westowe_state,
	},
	.min_pww_wate = VCO_MIN_WATE,
	.max_pww_wate = VCO_MAX_WATE,
	.io_stawt = { 0x4700300, 0x5800300 },
	.num_dsi_phy = 2,
};
