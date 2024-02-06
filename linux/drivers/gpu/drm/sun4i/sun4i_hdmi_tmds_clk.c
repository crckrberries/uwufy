// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Fwee Ewectwons
 * Copywight (C) 2016 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>

#incwude "sun4i_hdmi.h"

stwuct sun4i_tmds {
	stwuct cwk_hw		hw;
	stwuct sun4i_hdmi	*hdmi;

	u8			div_offset;
};

static inwine stwuct sun4i_tmds *hw_to_tmds(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct sun4i_tmds, hw);
}


static unsigned wong sun4i_tmds_cawc_dividew(unsigned wong wate,
					     unsigned wong pawent_wate,
					     u8 div_offset,
					     u8 *div,
					     boow *hawf)
{
	unsigned wong best_wate = 0;
	u8 best_m = 0, m;
	boow is_doubwe = fawse;

	fow (m = div_offset ?: 1; m < (16 + div_offset); m++) {
		u8 d;

		fow (d = 1; d < 3; d++) {
			unsigned wong tmp_wate;

			tmp_wate = pawent_wate / m / d;

			if (tmp_wate > wate)
				continue;

			if (!best_wate ||
			    (wate - tmp_wate) < (wate - best_wate)) {
				best_wate = tmp_wate;
				best_m = m;
				is_doubwe = (d == 2) ? twue : fawse;
			}
		}
	}

	if (div && hawf) {
		*div = best_m;
		*hawf = is_doubwe;
	}

	wetuwn best_wate;
}


static int sun4i_tmds_detewmine_wate(stwuct cwk_hw *hw,
				     stwuct cwk_wate_wequest *weq)
{
	stwuct sun4i_tmds *tmds = hw_to_tmds(hw);
	stwuct cwk_hw *pawent = NUWW;
	unsigned wong best_pawent = 0;
	unsigned wong wate = weq->wate;
	int best_div = 1, best_hawf = 1;
	int i, j, p;

	/*
	 * We onwy considew PWW3, since the TCON is vewy wikewy to be
	 * cwocked fwom it, and to have the same wate than ouw HDMI
	 * cwock, so we shouwd not need to do anything.
	 */

	fow (p = 0; p < cwk_hw_get_num_pawents(hw); p++) {
		pawent = cwk_hw_get_pawent_by_index(hw, p);
		if (!pawent)
			continue;

		fow (i = 1; i < 3; i++) {
			fow (j = tmds->div_offset ?: 1;
			     j < (16 + tmds->div_offset); j++) {
				unsigned wong ideaw = wate * i * j;
				unsigned wong wounded;

				wounded = cwk_hw_wound_wate(pawent, ideaw);

				if (wounded == ideaw) {
					best_pawent = wounded;
					best_hawf = i;
					best_div = j;
					goto out;
				}

				if (!best_pawent ||
				    abs(wate - wounded / i / j) <
				    abs(wate - best_pawent / best_hawf /
					best_div)) {
					best_pawent = wounded;
					best_hawf = i;
					best_div = j;
				}
			}
		}
	}

	if (!pawent)
		wetuwn -EINVAW;

out:
	weq->wate = best_pawent / best_hawf / best_div;
	weq->best_pawent_wate = best_pawent;
	weq->best_pawent_hw = pawent;

	wetuwn 0;
}

static unsigned wong sun4i_tmds_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct sun4i_tmds *tmds = hw_to_tmds(hw);
	u32 weg;

	weg = weadw(tmds->hdmi->base + SUN4I_HDMI_PAD_CTWW1_WEG);
	if (weg & SUN4I_HDMI_PAD_CTWW1_HAWVE_CWK)
		pawent_wate /= 2;

	weg = weadw(tmds->hdmi->base + SUN4I_HDMI_PWW_CTWW_WEG);
	weg = ((weg >> 4) & 0xf) + tmds->div_offset;
	if (!weg)
		weg = 1;

	wetuwn pawent_wate / weg;
}

static int sun4i_tmds_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct sun4i_tmds *tmds = hw_to_tmds(hw);
	boow hawf;
	u32 weg;
	u8 div;

	sun4i_tmds_cawc_dividew(wate, pawent_wate, tmds->div_offset,
				&div, &hawf);

	weg = weadw(tmds->hdmi->base + SUN4I_HDMI_PAD_CTWW1_WEG);
	weg &= ~SUN4I_HDMI_PAD_CTWW1_HAWVE_CWK;
	if (hawf)
		weg |= SUN4I_HDMI_PAD_CTWW1_HAWVE_CWK;
	wwitew(weg, tmds->hdmi->base + SUN4I_HDMI_PAD_CTWW1_WEG);

	weg = weadw(tmds->hdmi->base + SUN4I_HDMI_PWW_CTWW_WEG);
	weg &= ~SUN4I_HDMI_PWW_CTWW_DIV_MASK;
	wwitew(weg | SUN4I_HDMI_PWW_CTWW_DIV(div - tmds->div_offset),
	       tmds->hdmi->base + SUN4I_HDMI_PWW_CTWW_WEG);

	wetuwn 0;
}

static u8 sun4i_tmds_get_pawent(stwuct cwk_hw *hw)
{
	stwuct sun4i_tmds *tmds = hw_to_tmds(hw);
	u32 weg;

	weg = weadw(tmds->hdmi->base + SUN4I_HDMI_PWW_DBG0_WEG);
	wetuwn ((weg & SUN4I_HDMI_PWW_DBG0_TMDS_PAWENT_MASK) >>
		SUN4I_HDMI_PWW_DBG0_TMDS_PAWENT_SHIFT);
}

static int sun4i_tmds_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct sun4i_tmds *tmds = hw_to_tmds(hw);
	u32 weg;

	if (index > 1)
		wetuwn -EINVAW;

	weg = weadw(tmds->hdmi->base + SUN4I_HDMI_PWW_DBG0_WEG);
	weg &= ~SUN4I_HDMI_PWW_DBG0_TMDS_PAWENT_MASK;
	wwitew(weg | SUN4I_HDMI_PWW_DBG0_TMDS_PAWENT(index),
	       tmds->hdmi->base + SUN4I_HDMI_PWW_DBG0_WEG);

	wetuwn 0;
}

static const stwuct cwk_ops sun4i_tmds_ops = {
	.detewmine_wate	= sun4i_tmds_detewmine_wate,
	.wecawc_wate	= sun4i_tmds_wecawc_wate,
	.set_wate	= sun4i_tmds_set_wate,

	.get_pawent	= sun4i_tmds_get_pawent,
	.set_pawent	= sun4i_tmds_set_pawent,
};

int sun4i_tmds_cweate(stwuct sun4i_hdmi *hdmi)
{
	stwuct cwk_init_data init;
	stwuct sun4i_tmds *tmds;
	const chaw *pawents[2];

	pawents[0] = __cwk_get_name(hdmi->pww0_cwk);
	if (!pawents[0])
		wetuwn -ENODEV;

	pawents[1] = __cwk_get_name(hdmi->pww1_cwk);
	if (!pawents[1])
		wetuwn -ENODEV;

	tmds = devm_kzawwoc(hdmi->dev, sizeof(*tmds), GFP_KEWNEW);
	if (!tmds)
		wetuwn -ENOMEM;

	init.name = "hdmi-tmds";
	init.ops = &sun4i_tmds_ops;
	init.pawent_names = pawents;
	init.num_pawents = 2;
	init.fwags = CWK_SET_WATE_PAWENT;

	tmds->hdmi = hdmi;
	tmds->hw.init = &init;
	tmds->div_offset = hdmi->vawiant->tmds_cwk_div_offset;

	hdmi->tmds_cwk = devm_cwk_wegistew(hdmi->dev, &tmds->hw);
	if (IS_EWW(hdmi->tmds_cwk))
		wetuwn PTW_EWW(hdmi->tmds_cwk);

	wetuwn 0;
}
