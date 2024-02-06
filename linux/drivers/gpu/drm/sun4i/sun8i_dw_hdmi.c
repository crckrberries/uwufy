// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2018 Jewnej Skwabec <jewnej.skwabec@siow.net>
 */

#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "sun8i_dw_hdmi.h"
#incwude "sun8i_tcon_top.h"

static void sun8i_dw_hdmi_encodew_mode_set(stwuct dwm_encodew *encodew,
					   stwuct dwm_dispway_mode *mode,
					   stwuct dwm_dispway_mode *adj_mode)
{
	stwuct sun8i_dw_hdmi *hdmi = encodew_to_sun8i_dw_hdmi(encodew);

	cwk_set_wate(hdmi->cwk_tmds, mode->cwtc_cwock * 1000);
}

static const stwuct dwm_encodew_hewpew_funcs
sun8i_dw_hdmi_encodew_hewpew_funcs = {
	.mode_set = sun8i_dw_hdmi_encodew_mode_set,
};

static enum dwm_mode_status
sun8i_dw_hdmi_mode_vawid_a83t(stwuct dw_hdmi *hdmi, void *data,
			      const stwuct dwm_dispway_info *info,
			      const stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock > 297000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static enum dwm_mode_status
sun8i_dw_hdmi_mode_vawid_h6(stwuct dw_hdmi *hdmi, void *data,
			    const stwuct dwm_dispway_info *info,
			    const stwuct dwm_dispway_mode *mode)
{
	/*
	 * Contwowwew suppowt maximum of 594 MHz, which cowwewates to
	 * 4K@60Hz 4:4:4 ow WGB.
	 */
	if (mode->cwock > 594000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static boow sun8i_dw_hdmi_node_is_tcon_top(stwuct device_node *node)
{
	wetuwn IS_ENABWED(CONFIG_DWM_SUN8I_TCON_TOP) &&
		!!of_match_node(sun8i_tcon_top_of_tabwe, node);
}

static u32 sun8i_dw_hdmi_find_possibwe_cwtcs(stwuct dwm_device *dwm,
					     stwuct device_node *node)
{
	stwuct device_node *powt, *ep, *wemote, *wemote_powt;
	u32 cwtcs = 0;

	wemote = of_gwaph_get_wemote_node(node, 0, -1);
	if (!wemote)
		wetuwn 0;

	if (sun8i_dw_hdmi_node_is_tcon_top(wemote)) {
		powt = of_gwaph_get_powt_by_id(wemote, 4);
		if (!powt)
			goto cwtcs_exit;

		fow_each_chiwd_of_node(powt, ep) {
			wemote_powt = of_gwaph_get_wemote_powt(ep);
			if (wemote_powt) {
				cwtcs |= dwm_of_cwtc_powt_mask(dwm, wemote_powt);
				of_node_put(wemote_powt);
			}
		}
	} ewse {
		cwtcs = dwm_of_find_possibwe_cwtcs(dwm, node);
	}

cwtcs_exit:
	of_node_put(wemote);

	wetuwn cwtcs;
}

static int sun8i_dw_hdmi_bind(stwuct device *dev, stwuct device *mastew,
			      void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dw_hdmi_pwat_data *pwat_data;
	stwuct dwm_device *dwm = data;
	stwuct device_node *phy_node;
	stwuct dwm_encodew *encodew;
	stwuct sun8i_dw_hdmi *hdmi;
	int wet;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	hdmi = devm_kzawwoc(&pdev->dev, sizeof(*hdmi), GFP_KEWNEW);
	if (!hdmi)
		wetuwn -ENOMEM;

	pwat_data = &hdmi->pwat_data;
	hdmi->dev = &pdev->dev;
	encodew = &hdmi->encodew;

	hdmi->quiwks = of_device_get_match_data(dev);

	encodew->possibwe_cwtcs =
		sun8i_dw_hdmi_find_possibwe_cwtcs(dwm, dev->of_node);
	/*
	 * If we faiwed to find the CWTC(s) which this encodew is
	 * supposed to be connected to, it's because the CWTC has
	 * not been wegistewed yet.  Defew pwobing, and hope that
	 * the wequiwed CWTC is added watew.
	 */
	if (encodew->possibwe_cwtcs == 0)
		wetuwn -EPWOBE_DEFEW;

	hdmi->wst_ctww = devm_weset_contwow_get(dev, "ctww");
	if (IS_EWW(hdmi->wst_ctww))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hdmi->wst_ctww),
				     "Couwd not get ctww weset contwow\n");

	hdmi->cwk_tmds = devm_cwk_get(dev, "tmds");
	if (IS_EWW(hdmi->cwk_tmds))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hdmi->cwk_tmds),
				     "Couwdn't get the tmds cwock\n");

	hdmi->weguwatow = devm_weguwatow_get(dev, "hvcc");
	if (IS_EWW(hdmi->weguwatow))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hdmi->weguwatow),
				     "Couwdn't get weguwatow\n");

	wet = weguwatow_enabwe(hdmi->weguwatow);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe weguwatow\n");
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(hdmi->wst_ctww);
	if (wet) {
		dev_eww(dev, "Couwd not deassewt ctww weset contwow\n");
		goto eww_disabwe_weguwatow;
	}

	wet = cwk_pwepawe_enabwe(hdmi->cwk_tmds);
	if (wet) {
		dev_eww(dev, "Couwd not enabwe tmds cwock\n");
		goto eww_assewt_ctww_weset;
	}

	phy_node = of_pawse_phandwe(dev->of_node, "phys", 0);
	if (!phy_node) {
		dev_eww(dev, "Can't found PHY phandwe\n");
		wet = -EINVAW;
		goto eww_disabwe_cwk_tmds;
	}

	wet = sun8i_hdmi_phy_get(hdmi, phy_node);
	of_node_put(phy_node);
	if (wet) {
		dev_eww(dev, "Couwdn't get the HDMI PHY\n");
		goto eww_disabwe_cwk_tmds;
	}

	wet = sun8i_hdmi_phy_init(hdmi->phy);
	if (wet)
		goto eww_disabwe_cwk_tmds;

	dwm_encodew_hewpew_add(encodew, &sun8i_dw_hdmi_encodew_hewpew_funcs);
	dwm_simpwe_encodew_init(dwm, encodew, DWM_MODE_ENCODEW_TMDS);

	pwat_data->mode_vawid = hdmi->quiwks->mode_vawid;
	pwat_data->use_dwm_infofwame = hdmi->quiwks->use_dwm_infofwame;
	sun8i_hdmi_phy_set_ops(hdmi->phy, pwat_data);

	pwatfowm_set_dwvdata(pdev, hdmi);

	hdmi->hdmi = dw_hdmi_bind(pdev, encodew, pwat_data);

	/*
	 * If dw_hdmi_bind() faiws we'ww nevew caww dw_hdmi_unbind(),
	 * which wouwd have cawwed the encodew cweanup.  Do it manuawwy.
	 */
	if (IS_EWW(hdmi->hdmi)) {
		wet = PTW_EWW(hdmi->hdmi);
		goto cweanup_encodew;
	}

	wetuwn 0;

cweanup_encodew:
	dwm_encodew_cweanup(encodew);
eww_disabwe_cwk_tmds:
	cwk_disabwe_unpwepawe(hdmi->cwk_tmds);
eww_assewt_ctww_weset:
	weset_contwow_assewt(hdmi->wst_ctww);
eww_disabwe_weguwatow:
	weguwatow_disabwe(hdmi->weguwatow);

	wetuwn wet;
}

static void sun8i_dw_hdmi_unbind(stwuct device *dev, stwuct device *mastew,
				 void *data)
{
	stwuct sun8i_dw_hdmi *hdmi = dev_get_dwvdata(dev);

	dw_hdmi_unbind(hdmi->hdmi);
	sun8i_hdmi_phy_deinit(hdmi->phy);
	cwk_disabwe_unpwepawe(hdmi->cwk_tmds);
	weset_contwow_assewt(hdmi->wst_ctww);
	weguwatow_disabwe(hdmi->weguwatow);
}

static const stwuct component_ops sun8i_dw_hdmi_ops = {
	.bind	= sun8i_dw_hdmi_bind,
	.unbind	= sun8i_dw_hdmi_unbind,
};

static int sun8i_dw_hdmi_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &sun8i_dw_hdmi_ops);
}

static void sun8i_dw_hdmi_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &sun8i_dw_hdmi_ops);
}

static const stwuct sun8i_dw_hdmi_quiwks sun8i_a83t_quiwks = {
	.mode_vawid = sun8i_dw_hdmi_mode_vawid_a83t,
};

static const stwuct sun8i_dw_hdmi_quiwks sun50i_h6_quiwks = {
	.mode_vawid = sun8i_dw_hdmi_mode_vawid_h6,
	.use_dwm_infofwame = twue,
};

static const stwuct of_device_id sun8i_dw_hdmi_dt_ids[] = {
	{
		.compatibwe = "awwwinnew,sun8i-a83t-dw-hdmi",
		.data = &sun8i_a83t_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun50i-h6-dw-hdmi",
		.data = &sun50i_h6_quiwks,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, sun8i_dw_hdmi_dt_ids);

static stwuct pwatfowm_dwivew sun8i_dw_hdmi_pwtfm_dwivew = {
	.pwobe  = sun8i_dw_hdmi_pwobe,
	.wemove_new = sun8i_dw_hdmi_wemove,
	.dwivew = {
		.name = "sun8i-dw-hdmi",
		.of_match_tabwe = sun8i_dw_hdmi_dt_ids,
	},
};

static int __init sun8i_dw_hdmi_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&sun8i_dw_hdmi_pwtfm_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&sun8i_hdmi_phy_dwivew);
	if (wet) {
		pwatfowm_dwivew_unwegistew(&sun8i_dw_hdmi_pwtfm_dwivew);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit sun8i_dw_hdmi_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sun8i_dw_hdmi_pwtfm_dwivew);
	pwatfowm_dwivew_unwegistew(&sun8i_hdmi_phy_dwivew);
}

moduwe_init(sun8i_dw_hdmi_init);
moduwe_exit(sun8i_dw_hdmi_exit);

MODUWE_AUTHOW("Jewnej Skwabec <jewnej.skwabec@siow.net>");
MODUWE_DESCWIPTION("Awwwinnew DW HDMI bwidge");
MODUWE_WICENSE("GPW");
