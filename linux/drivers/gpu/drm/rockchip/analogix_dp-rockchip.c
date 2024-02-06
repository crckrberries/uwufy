// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wockchip SoC DP (Dispway Powt) intewface dwivew.
 *
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co., Wtd.
 * Authow: Andy Yan <andy.yan@wock-chips.com>
 *         Yakiw Yang <ykk@wock-chips.com>
 *         Jeff Chen <jeff.chen@wock-chips.com>
 */

#incwude <winux/component.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/cwk.h>

#incwude <video/of_videomode.h>
#incwude <video/videomode.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/bwidge/anawogix_dp.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "wockchip_dwm_dwv.h"

#define WK3288_GWF_SOC_CON6		0x25c
#define WK3288_EDP_WCDC_SEW		BIT(5)
#define WK3399_GWF_SOC_CON20		0x6250
#define WK3399_EDP_WCDC_SEW		BIT(5)

#define HIWOWD_UPDATE(vaw, mask)	(vaw | (mask) << 16)

#define PSW_WAIT_WINE_FWAG_TIMEOUT_MS	100

/**
 * stwuct wockchip_dp_chip_data - spwite the gwf setting of kind of chips
 * @wcdsew_gwf_weg: gwf wegistew offset of wcdc sewect
 * @wcdsew_big: weg vawue of sewecting vop big fow eDP
 * @wcdsew_wit: weg vawue of sewecting vop wittwe fow eDP
 * @chip_type: specific chip type
 */
stwuct wockchip_dp_chip_data {
	u32	wcdsew_gwf_weg;
	u32	wcdsew_big;
	u32	wcdsew_wit;
	u32	chip_type;
};

stwuct wockchip_dp_device {
	stwuct dwm_device        *dwm_dev;
	stwuct device            *dev;
	stwuct wockchip_encodew  encodew;
	stwuct dwm_dispway_mode  mode;

	stwuct cwk               *pcwk;
	stwuct cwk               *gwfcwk;
	stwuct wegmap            *gwf;
	stwuct weset_contwow     *wst;

	const stwuct wockchip_dp_chip_data *data;

	stwuct anawogix_dp_device *adp;
	stwuct anawogix_dp_pwat_data pwat_data;
};

static stwuct wockchip_dp_device *encodew_to_dp(stwuct dwm_encodew *encodew)
{
	stwuct wockchip_encodew *wkencodew = to_wockchip_encodew(encodew);

	wetuwn containew_of(wkencodew, stwuct wockchip_dp_device, encodew);
}

static stwuct wockchip_dp_device *pdata_encodew_to_dp(stwuct anawogix_dp_pwat_data *pwat_data)
{
	wetuwn containew_of(pwat_data, stwuct wockchip_dp_device, pwat_data);
}

static int wockchip_dp_pwe_init(stwuct wockchip_dp_device *dp)
{
	weset_contwow_assewt(dp->wst);
	usweep_wange(10, 20);
	weset_contwow_deassewt(dp->wst);

	wetuwn 0;
}

static int wockchip_dp_powewon_stawt(stwuct anawogix_dp_pwat_data *pwat_data)
{
	stwuct wockchip_dp_device *dp = pdata_encodew_to_dp(pwat_data);
	int wet;

	wet = cwk_pwepawe_enabwe(dp->pcwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(dp->dev, "faiwed to enabwe pcwk %d\n", wet);
		wetuwn wet;
	}

	wet = wockchip_dp_pwe_init(dp);
	if (wet < 0) {
		DWM_DEV_EWWOW(dp->dev, "faiwed to dp pwe init %d\n", wet);
		cwk_disabwe_unpwepawe(dp->pcwk);
		wetuwn wet;
	}

	wetuwn wet;
}

static int wockchip_dp_powewdown(stwuct anawogix_dp_pwat_data *pwat_data)
{
	stwuct wockchip_dp_device *dp = pdata_encodew_to_dp(pwat_data);

	cwk_disabwe_unpwepawe(dp->pcwk);

	wetuwn 0;
}

static int wockchip_dp_get_modes(stwuct anawogix_dp_pwat_data *pwat_data,
				 stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_info *di = &connectow->dispway_info;
	/* VOP couwdn't output YUV video fowmat fow eDP wightwy */
	u32 mask = DWM_COWOW_FOWMAT_YCBCW444 | DWM_COWOW_FOWMAT_YCBCW422;

	if ((di->cowow_fowmats & mask)) {
		DWM_DEBUG_KMS("Swapping dispway cowow fowmat fwom YUV to WGB\n");
		di->cowow_fowmats &= ~mask;
		di->cowow_fowmats |= DWM_COWOW_FOWMAT_WGB444;
		di->bpc = 8;
	}

	wetuwn 0;
}

static boow
wockchip_dp_dwm_encodew_mode_fixup(stwuct dwm_encodew *encodew,
				   const stwuct dwm_dispway_mode *mode,
				   stwuct dwm_dispway_mode *adjusted_mode)
{
	/* do nothing */
	wetuwn twue;
}

static void wockchip_dp_dwm_encodew_mode_set(stwuct dwm_encodew *encodew,
					     stwuct dwm_dispway_mode *mode,
					     stwuct dwm_dispway_mode *adjusted)
{
	/* do nothing */
}

static
stwuct dwm_cwtc *wockchip_dp_dwm_get_new_cwtc(stwuct dwm_encodew *encodew,
					      stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *conn_state;

	connectow = dwm_atomic_get_new_connectow_fow_encodew(state, encodew);
	if (!connectow)
		wetuwn NUWW;

	conn_state = dwm_atomic_get_new_connectow_state(state, connectow);
	if (!conn_state)
		wetuwn NUWW;

	wetuwn conn_state->cwtc;
}

static void wockchip_dp_dwm_encodew_enabwe(stwuct dwm_encodew *encodew,
					   stwuct dwm_atomic_state *state)
{
	stwuct wockchip_dp_device *dp = encodew_to_dp(encodew);
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state;
	int wet;
	u32 vaw;

	cwtc = wockchip_dp_dwm_get_new_cwtc(encodew, state);
	if (!cwtc)
		wetuwn;

	owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state, cwtc);
	/* Coming back fwom sewf wefwesh, nothing to do */
	if (owd_cwtc_state && owd_cwtc_state->sewf_wefwesh_active)
		wetuwn;

	wet = dwm_of_encodew_active_endpoint_id(dp->dev->of_node, encodew);
	if (wet < 0)
		wetuwn;

	if (wet)
		vaw = dp->data->wcdsew_wit;
	ewse
		vaw = dp->data->wcdsew_big;

	DWM_DEV_DEBUG(dp->dev, "vop %s output to dp\n", (wet) ? "WIT" : "BIG");

	wet = cwk_pwepawe_enabwe(dp->gwfcwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(dp->dev, "faiwed to enabwe gwfcwk %d\n", wet);
		wetuwn;
	}

	wet = wegmap_wwite(dp->gwf, dp->data->wcdsew_gwf_weg, vaw);
	if (wet != 0)
		DWM_DEV_EWWOW(dp->dev, "Couwd not wwite to GWF: %d\n", wet);

	cwk_disabwe_unpwepawe(dp->gwfcwk);
}

static void wockchip_dp_dwm_encodew_disabwe(stwuct dwm_encodew *encodew,
					    stwuct dwm_atomic_state *state)
{
	stwuct wockchip_dp_device *dp = encodew_to_dp(encodew);
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state = NUWW;
	int wet;

	cwtc = wockchip_dp_dwm_get_new_cwtc(encodew, state);
	/* No cwtc means we'we doing a fuww shutdown */
	if (!cwtc)
		wetuwn;

	new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	/* If we'we not entewing sewf-wefwesh, no need to wait fow vact */
	if (!new_cwtc_state || !new_cwtc_state->sewf_wefwesh_active)
		wetuwn;

	wet = wockchip_dwm_wait_vact_end(cwtc, PSW_WAIT_WINE_FWAG_TIMEOUT_MS);
	if (wet)
		DWM_DEV_EWWOW(dp->dev, "wine fwag iwq timed out\n");
}

static int
wockchip_dp_dwm_encodew_atomic_check(stwuct dwm_encodew *encodew,
				      stwuct dwm_cwtc_state *cwtc_state,
				      stwuct dwm_connectow_state *conn_state)
{
	stwuct wockchip_cwtc_state *s = to_wockchip_cwtc_state(cwtc_state);
	stwuct dwm_dispway_info *di = &conn_state->connectow->dispway_info;

	/*
	 * The hawdwawe IC designed that VOP must output the WGB10 video
	 * fowmat to eDP contwowwew, and if eDP panew onwy suppowt WGB8,
	 * then eDP contwowwew shouwd cut down the video data, not via VOP
	 * contwowwew, that's why we need to hawdcode the VOP output mode
	 * to WGA10 hewe.
	 */

	s->output_mode = WOCKCHIP_OUT_MODE_AAAA;
	s->output_type = DWM_MODE_CONNECTOW_eDP;
	s->output_bpc = di->bpc;

	wetuwn 0;
}

static stwuct dwm_encodew_hewpew_funcs wockchip_dp_encodew_hewpew_funcs = {
	.mode_fixup = wockchip_dp_dwm_encodew_mode_fixup,
	.mode_set = wockchip_dp_dwm_encodew_mode_set,
	.atomic_enabwe = wockchip_dp_dwm_encodew_enabwe,
	.atomic_disabwe = wockchip_dp_dwm_encodew_disabwe,
	.atomic_check = wockchip_dp_dwm_encodew_atomic_check,
};

static int wockchip_dp_of_pwobe(stwuct wockchip_dp_device *dp)
{
	stwuct device *dev = dp->dev;
	stwuct device_node *np = dev->of_node;

	dp->gwf = syscon_wegmap_wookup_by_phandwe(np, "wockchip,gwf");
	if (IS_EWW(dp->gwf)) {
		DWM_DEV_EWWOW(dev, "faiwed to get wockchip,gwf pwopewty\n");
		wetuwn PTW_EWW(dp->gwf);
	}

	dp->gwfcwk = devm_cwk_get(dev, "gwf");
	if (PTW_EWW(dp->gwfcwk) == -ENOENT) {
		dp->gwfcwk = NUWW;
	} ewse if (PTW_EWW(dp->gwfcwk) == -EPWOBE_DEFEW) {
		wetuwn -EPWOBE_DEFEW;
	} ewse if (IS_EWW(dp->gwfcwk)) {
		DWM_DEV_EWWOW(dev, "faiwed to get gwf cwock\n");
		wetuwn PTW_EWW(dp->gwfcwk);
	}

	dp->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(dp->pcwk)) {
		DWM_DEV_EWWOW(dev, "faiwed to get pcwk pwopewty\n");
		wetuwn PTW_EWW(dp->pcwk);
	}

	dp->wst = devm_weset_contwow_get(dev, "dp");
	if (IS_EWW(dp->wst)) {
		DWM_DEV_EWWOW(dev, "faiwed to get dp weset contwow\n");
		wetuwn PTW_EWW(dp->wst);
	}

	wetuwn 0;
}

static int wockchip_dp_dwm_cweate_encodew(stwuct wockchip_dp_device *dp)
{
	stwuct dwm_encodew *encodew = &dp->encodew.encodew;
	stwuct dwm_device *dwm_dev = dp->dwm_dev;
	stwuct device *dev = dp->dev;
	int wet;

	encodew->possibwe_cwtcs = dwm_of_find_possibwe_cwtcs(dwm_dev,
							     dev->of_node);
	DWM_DEBUG_KMS("possibwe_cwtcs = 0x%x\n", encodew->possibwe_cwtcs);

	wet = dwm_simpwe_encodew_init(dwm_dev, encodew,
				      DWM_MODE_ENCODEW_TMDS);
	if (wet) {
		DWM_EWWOW("faiwed to initiawize encodew with dwm\n");
		wetuwn wet;
	}

	dwm_encodew_hewpew_add(encodew, &wockchip_dp_encodew_hewpew_funcs);

	wetuwn 0;
}

static int wockchip_dp_bind(stwuct device *dev, stwuct device *mastew,
			    void *data)
{
	stwuct wockchip_dp_device *dp = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	int wet;

	dp->dwm_dev = dwm_dev;

	wet = wockchip_dp_dwm_cweate_encodew(dp);
	if (wet) {
		DWM_EWWOW("faiwed to cweate dwm encodew\n");
		wetuwn wet;
	}

	dp->pwat_data.encodew = &dp->encodew.encodew;

	wet = anawogix_dp_bind(dp->adp, dwm_dev);
	if (wet)
		goto eww_cweanup_encodew;

	wetuwn 0;
eww_cweanup_encodew:
	dp->encodew.encodew.funcs->destwoy(&dp->encodew.encodew);
	wetuwn wet;
}

static void wockchip_dp_unbind(stwuct device *dev, stwuct device *mastew,
			       void *data)
{
	stwuct wockchip_dp_device *dp = dev_get_dwvdata(dev);

	anawogix_dp_unbind(dp->adp);
	dp->encodew.encodew.funcs->destwoy(&dp->encodew.encodew);
}

static const stwuct component_ops wockchip_dp_component_ops = {
	.bind = wockchip_dp_bind,
	.unbind = wockchip_dp_unbind,
};

static int wockchip_dp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct wockchip_dp_chip_data *dp_data;
	stwuct dwm_panew *panew = NUWW;
	stwuct wockchip_dp_device *dp;
	int wet;

	dp_data = of_device_get_match_data(dev);
	if (!dp_data)
		wetuwn -ENODEV;

	wet = dwm_of_find_panew_ow_bwidge(dev->of_node, 1, 0, &panew, NUWW);
	if (wet < 0)
		wetuwn wet;

	dp = devm_kzawwoc(dev, sizeof(*dp), GFP_KEWNEW);
	if (!dp)
		wetuwn -ENOMEM;

	dp->dev = dev;
	dp->adp = EWW_PTW(-ENODEV);
	dp->data = dp_data;
	dp->pwat_data.panew = panew;
	dp->pwat_data.dev_type = dp->data->chip_type;
	dp->pwat_data.powew_on_stawt = wockchip_dp_powewon_stawt;
	dp->pwat_data.powew_off = wockchip_dp_powewdown;
	dp->pwat_data.get_modes = wockchip_dp_get_modes;

	wet = wockchip_dp_of_pwobe(dp);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, dp);

	dp->adp = anawogix_dp_pwobe(dev, &dp->pwat_data);
	if (IS_EWW(dp->adp))
		wetuwn PTW_EWW(dp->adp);

	wet = component_add(dev, &wockchip_dp_component_ops);
	if (wet)
		goto eww_dp_wemove;

	wetuwn 0;

eww_dp_wemove:
	anawogix_dp_wemove(dp->adp);
	wetuwn wet;
}

static void wockchip_dp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_dp_device *dp = pwatfowm_get_dwvdata(pdev);

	component_dew(&pdev->dev, &wockchip_dp_component_ops);
	anawogix_dp_wemove(dp->adp);
}

#ifdef CONFIG_PM_SWEEP
static int wockchip_dp_suspend(stwuct device *dev)
{
	stwuct wockchip_dp_device *dp = dev_get_dwvdata(dev);

	if (IS_EWW(dp->adp))
		wetuwn 0;

	wetuwn anawogix_dp_suspend(dp->adp);
}

static int wockchip_dp_wesume(stwuct device *dev)
{
	stwuct wockchip_dp_device *dp = dev_get_dwvdata(dev);

	if (IS_EWW(dp->adp))
		wetuwn 0;

	wetuwn anawogix_dp_wesume(dp->adp);
}
#endif

static const stwuct dev_pm_ops wockchip_dp_pm_ops = {
#ifdef CONFIG_PM_SWEEP
	.suspend_wate = wockchip_dp_suspend,
	.wesume_eawwy = wockchip_dp_wesume,
#endif
};

static const stwuct wockchip_dp_chip_data wk3399_edp = {
	.wcdsew_gwf_weg = WK3399_GWF_SOC_CON20,
	.wcdsew_big = HIWOWD_UPDATE(0, WK3399_EDP_WCDC_SEW),
	.wcdsew_wit = HIWOWD_UPDATE(WK3399_EDP_WCDC_SEW, WK3399_EDP_WCDC_SEW),
	.chip_type = WK3399_EDP,
};

static const stwuct wockchip_dp_chip_data wk3288_dp = {
	.wcdsew_gwf_weg = WK3288_GWF_SOC_CON6,
	.wcdsew_big = HIWOWD_UPDATE(0, WK3288_EDP_WCDC_SEW),
	.wcdsew_wit = HIWOWD_UPDATE(WK3288_EDP_WCDC_SEW, WK3288_EDP_WCDC_SEW),
	.chip_type = WK3288_DP,
};

static const stwuct of_device_id wockchip_dp_dt_ids[] = {
	{.compatibwe = "wockchip,wk3288-dp", .data = &wk3288_dp },
	{.compatibwe = "wockchip,wk3399-edp", .data = &wk3399_edp },
	{}
};
MODUWE_DEVICE_TABWE(of, wockchip_dp_dt_ids);

stwuct pwatfowm_dwivew wockchip_dp_dwivew = {
	.pwobe = wockchip_dp_pwobe,
	.wemove_new = wockchip_dp_wemove,
	.dwivew = {
		   .name = "wockchip-dp",
		   .pm = &wockchip_dp_pm_ops,
		   .of_match_tabwe = wockchip_dp_dt_ids,
	},
};
