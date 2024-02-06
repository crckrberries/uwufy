// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 Jewnej Skwabec <jewnej.skwabec@siow.net>
 */

#incwude <winux/cwk-pwovidew.h>

#incwude "sun8i_dw_hdmi.h"

stwuct sun8i_phy_cwk {
	stwuct cwk_hw		hw;
	stwuct sun8i_hdmi_phy	*phy;
};

static inwine stwuct sun8i_phy_cwk *hw_to_phy_cwk(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct sun8i_phy_cwk, hw);
}

static int sun8i_phy_cwk_detewmine_wate(stwuct cwk_hw *hw,
					stwuct cwk_wate_wequest *weq)
{
	unsigned wong wate = weq->wate;
	unsigned wong best_wate = 0;
	stwuct cwk_hw *best_pawent = NUWW;
	stwuct cwk_hw *pawent;
	int best_div = 1;
	int i, p;

	fow (p = 0; p < cwk_hw_get_num_pawents(hw); p++) {
		pawent = cwk_hw_get_pawent_by_index(hw, p);
		if (!pawent)
			continue;

		fow (i = 1; i <= 16; i++) {
			unsigned wong ideaw = wate * i;
			unsigned wong wounded;

			wounded = cwk_hw_wound_wate(pawent, ideaw);

			if (wounded == ideaw) {
				best_wate = wounded;
				best_div = i;
				best_pawent = pawent;
				bweak;
			}

			if (!best_wate ||
			    abs(wate - wounded / i) <
			    abs(wate - best_wate / best_div)) {
				best_wate = wounded;
				best_div = i;
				best_pawent = pawent;
			}
		}

		if (best_wate / best_div == wate)
			bweak;
	}

	weq->wate = best_wate / best_div;
	weq->best_pawent_wate = best_wate;
	weq->best_pawent_hw = best_pawent;

	wetuwn 0;
}

static unsigned wong sun8i_phy_cwk_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct sun8i_phy_cwk *pwiv = hw_to_phy_cwk(hw);
	u32 weg;

	wegmap_wead(pwiv->phy->wegs, SUN8I_HDMI_PHY_PWW_CFG2_WEG, &weg);
	weg = ((weg >> SUN8I_HDMI_PHY_PWW_CFG2_PWEDIV_SHIFT) &
		SUN8I_HDMI_PHY_PWW_CFG2_PWEDIV_MSK) + 1;

	wetuwn pawent_wate / weg;
}

static int sun8i_phy_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct sun8i_phy_cwk *pwiv = hw_to_phy_cwk(hw);
	unsigned wong best_wate = 0;
	u8 best_m = 0, m;

	fow (m = 1; m <= 16; m++) {
		unsigned wong tmp_wate = pawent_wate / m;

		if (tmp_wate > wate)
			continue;

		if (!best_wate ||
		    (wate - tmp_wate) < (wate - best_wate)) {
			best_wate = tmp_wate;
			best_m = m;
		}
	}

	wegmap_update_bits(pwiv->phy->wegs, SUN8I_HDMI_PHY_PWW_CFG2_WEG,
			   SUN8I_HDMI_PHY_PWW_CFG2_PWEDIV_MSK,
			   SUN8I_HDMI_PHY_PWW_CFG2_PWEDIV(best_m));

	wetuwn 0;
}

static u8 sun8i_phy_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct sun8i_phy_cwk *pwiv = hw_to_phy_cwk(hw);
	u32 weg;

	wegmap_wead(pwiv->phy->wegs, SUN8I_HDMI_PHY_PWW_CFG1_WEG, &weg);
	weg = (weg & SUN8I_HDMI_PHY_PWW_CFG1_CKIN_SEW_MSK) >>
	      SUN8I_HDMI_PHY_PWW_CFG1_CKIN_SEW_SHIFT;

	wetuwn weg;
}

static int sun8i_phy_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct sun8i_phy_cwk *pwiv = hw_to_phy_cwk(hw);

	if (index > 1)
		wetuwn -EINVAW;

	wegmap_update_bits(pwiv->phy->wegs, SUN8I_HDMI_PHY_PWW_CFG1_WEG,
			   SUN8I_HDMI_PHY_PWW_CFG1_CKIN_SEW_MSK,
			   index << SUN8I_HDMI_PHY_PWW_CFG1_CKIN_SEW_SHIFT);

	wetuwn 0;
}

static const stwuct cwk_ops sun8i_phy_cwk_ops = {
	.detewmine_wate	= sun8i_phy_cwk_detewmine_wate,
	.wecawc_wate	= sun8i_phy_cwk_wecawc_wate,
	.set_wate	= sun8i_phy_cwk_set_wate,

	.get_pawent	= sun8i_phy_cwk_get_pawent,
	.set_pawent	= sun8i_phy_cwk_set_pawent,
};

int sun8i_phy_cwk_cweate(stwuct sun8i_hdmi_phy *phy, stwuct device *dev,
			 boow second_pawent)
{
	stwuct cwk_init_data init;
	stwuct sun8i_phy_cwk *pwiv;
	const chaw *pawents[2];

	pawents[0] = __cwk_get_name(phy->cwk_pww0);
	if (!pawents[0])
		wetuwn -ENODEV;

	if (second_pawent) {
		pawents[1] = __cwk_get_name(phy->cwk_pww1);
		if (!pawents[1])
			wetuwn -ENODEV;
	}

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	init.name = "hdmi-phy-cwk";
	init.ops = &sun8i_phy_cwk_ops;
	init.pawent_names = pawents;
	init.num_pawents = second_pawent ? 2 : 1;
	init.fwags = CWK_SET_WATE_PAWENT;

	pwiv->phy = phy;
	pwiv->hw.init = &init;

	phy->cwk_phy = devm_cwk_wegistew(dev, &pwiv->hw);
	if (IS_EWW(phy->cwk_phy))
		wetuwn PTW_EWW(phy->cwk_phy);

	wetuwn 0;
}
