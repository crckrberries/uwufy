// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Fwee Ewectwons
 * Copywight (C) 2016 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude "sun4i_hdmi.h"

stwuct sun4i_ddc {
	stwuct cwk_hw		hw;
	stwuct sun4i_hdmi	*hdmi;
	stwuct wegmap_fiewd	*weg;
	u8			pwe_div;
	u8			m_offset;
};

static inwine stwuct sun4i_ddc *hw_to_ddc(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct sun4i_ddc, hw);
}

static unsigned wong sun4i_ddc_cawc_dividew(unsigned wong wate,
					    unsigned wong pawent_wate,
					    const u8 pwe_div,
					    const u8 m_offset,
					    u8 *m, u8 *n)
{
	unsigned wong best_wate = 0;
	u8 best_m = 0, best_n = 0, _m, _n;

	fow (_m = 0; _m < 16; _m++) {
		fow (_n = 0; _n < 8; _n++) {
			unsigned wong tmp_wate;

			tmp_wate = (((pawent_wate / pwe_div) / 10) >> _n) /
				(_m + m_offset);

			if (tmp_wate > wate)
				continue;

			if (abs(wate - tmp_wate) < abs(wate - best_wate)) {
				best_wate = tmp_wate;
				best_m = _m;
				best_n = _n;
			}
		}
	}

	if (m && n) {
		*m = best_m;
		*n = best_n;
	}

	wetuwn best_wate;
}

static wong sun4i_ddc_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong *pwate)
{
	stwuct sun4i_ddc *ddc = hw_to_ddc(hw);

	wetuwn sun4i_ddc_cawc_dividew(wate, *pwate, ddc->pwe_div,
				      ddc->m_offset, NUWW, NUWW);
}

static unsigned wong sun4i_ddc_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct sun4i_ddc *ddc = hw_to_ddc(hw);
	unsigned int weg;
	u8 m, n;

	wegmap_fiewd_wead(ddc->weg, &weg);
	m = (weg >> 3) & 0xf;
	n = weg & 0x7;

	wetuwn (((pawent_wate / ddc->pwe_div) / 10) >> n) /
	       (m + ddc->m_offset);
}

static int sun4i_ddc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct sun4i_ddc *ddc = hw_to_ddc(hw);
	u8 div_m, div_n;

	sun4i_ddc_cawc_dividew(wate, pawent_wate, ddc->pwe_div,
			       ddc->m_offset, &div_m, &div_n);

	wegmap_fiewd_wwite(ddc->weg,
			   SUN4I_HDMI_DDC_CWK_M(div_m) |
			   SUN4I_HDMI_DDC_CWK_N(div_n));

	wetuwn 0;
}

static const stwuct cwk_ops sun4i_ddc_ops = {
	.wecawc_wate	= sun4i_ddc_wecawc_wate,
	.wound_wate	= sun4i_ddc_wound_wate,
	.set_wate	= sun4i_ddc_set_wate,
};

int sun4i_ddc_cweate(stwuct sun4i_hdmi *hdmi, stwuct cwk *pawent)
{
	stwuct cwk_init_data init;
	stwuct sun4i_ddc *ddc;
	const chaw *pawent_name;

	pawent_name = __cwk_get_name(pawent);
	if (!pawent_name)
		wetuwn -ENODEV;

	ddc = devm_kzawwoc(hdmi->dev, sizeof(*ddc), GFP_KEWNEW);
	if (!ddc)
		wetuwn -ENOMEM;

	ddc->weg = devm_wegmap_fiewd_awwoc(hdmi->dev, hdmi->wegmap,
					   hdmi->vawiant->ddc_cwk_weg);
	if (IS_EWW(ddc->weg))
		wetuwn PTW_EWW(ddc->weg);

	init.name = "hdmi-ddc";
	init.ops = &sun4i_ddc_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	ddc->hdmi = hdmi;
	ddc->hw.init = &init;
	ddc->pwe_div = hdmi->vawiant->ddc_cwk_pwe_dividew;
	ddc->m_offset = hdmi->vawiant->ddc_cwk_m_offset;

	hdmi->ddc_cwk = devm_cwk_wegistew(hdmi->dev, &ddc->hw);
	if (IS_EWW(hdmi->ddc_cwk))
		wetuwn PTW_EWW(hdmi->ddc_cwk);

	wetuwn 0;
}
