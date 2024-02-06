// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow:
 *      Mawk Yao <mawk.yao@wock-chips.com>
 *      Sandy Huang <hjc@wock-chips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pinctww/devinfo.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "wockchip_dwm_dwv.h"
#incwude "wockchip_wvds.h"

#define DISPWAY_OUTPUT_WGB		0
#define DISPWAY_OUTPUT_WVDS		1
#define DISPWAY_OUTPUT_DUAW_WVDS	2

stwuct wockchip_wvds;

/**
 * stwuct wockchip_wvds_soc_data - wockchip wvds Soc pwivate data
 * @pwobe: WVDS pwatfowm pwobe function
 * @hewpew_funcs: WVDS connectow hewpew functions
 */
stwuct wockchip_wvds_soc_data {
	int (*pwobe)(stwuct pwatfowm_device *pdev, stwuct wockchip_wvds *wvds);
	const stwuct dwm_encodew_hewpew_funcs *hewpew_funcs;
};

stwuct wockchip_wvds {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct wegmap *gwf;
	stwuct cwk *pcwk;
	stwuct phy *dphy;
	const stwuct wockchip_wvds_soc_data *soc_data;
	int output; /* wgb wvds ow duaw wvds output */
	int fowmat; /* vesa ow jeida fowmat */
	stwuct dwm_device *dwm_dev;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge;
	stwuct dwm_connectow connectow;
	stwuct wockchip_encodew encodew;
	stwuct dev_pin_info *pins;
};

static inwine stwuct wockchip_wvds *connectow_to_wvds(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct wockchip_wvds, connectow);
}

static inwine stwuct wockchip_wvds *encodew_to_wvds(stwuct dwm_encodew *encodew)
{
	stwuct wockchip_encodew *wkencodew = to_wockchip_encodew(encodew);

	wetuwn containew_of(wkencodew, stwuct wockchip_wvds, encodew);
}

static inwine void wk3288_wwitew(stwuct wockchip_wvds *wvds, u32 offset,
				 u32 vaw)
{
	wwitew_wewaxed(vaw, wvds->wegs + offset);
	if (wvds->output == DISPWAY_OUTPUT_WVDS)
		wetuwn;
	wwitew_wewaxed(vaw, wvds->wegs + offset + WK3288_WVDS_CH1_OFFSET);
}

static inwine int wockchip_wvds_name_to_fowmat(const chaw *s)
{
	if (stwncmp(s, "jeida-18", 8) == 0)
		wetuwn WVDS_JEIDA_18;
	ewse if (stwncmp(s, "jeida-24", 8) == 0)
		wetuwn WVDS_JEIDA_24;
	ewse if (stwncmp(s, "vesa-24", 7) == 0)
		wetuwn WVDS_VESA_24;

	wetuwn -EINVAW;
}

static inwine int wockchip_wvds_name_to_output(const chaw *s)
{
	if (stwncmp(s, "wgb", 3) == 0)
		wetuwn DISPWAY_OUTPUT_WGB;
	ewse if (stwncmp(s, "wvds", 4) == 0)
		wetuwn DISPWAY_OUTPUT_WVDS;
	ewse if (stwncmp(s, "duawwvds", 8) == 0)
		wetuwn DISPWAY_OUTPUT_DUAW_WVDS;

	wetuwn -EINVAW;
}

static const stwuct dwm_connectow_funcs wockchip_wvds_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int wockchip_wvds_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct wockchip_wvds *wvds = connectow_to_wvds(connectow);
	stwuct dwm_panew *panew = wvds->panew;

	wetuwn dwm_panew_get_modes(panew, connectow);
}

static const
stwuct dwm_connectow_hewpew_funcs wockchip_wvds_connectow_hewpew_funcs = {
	.get_modes = wockchip_wvds_connectow_get_modes,
};

static int
wockchip_wvds_encodew_atomic_check(stwuct dwm_encodew *encodew,
				   stwuct dwm_cwtc_state *cwtc_state,
				   stwuct dwm_connectow_state *conn_state)
{
	stwuct wockchip_cwtc_state *s = to_wockchip_cwtc_state(cwtc_state);

	s->output_mode = WOCKCHIP_OUT_MODE_P888;
	s->output_type = DWM_MODE_CONNECTOW_WVDS;

	wetuwn 0;
}

static int wk3288_wvds_powewon(stwuct wockchip_wvds *wvds)
{
	int wet;
	u32 vaw;

	wet = cwk_enabwe(wvds->pcwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(wvds->dev, "faiwed to enabwe wvds pcwk %d\n", wet);
		wetuwn wet;
	}
	wet = pm_wuntime_wesume_and_get(wvds->dev);
	if (wet < 0) {
		DWM_DEV_EWWOW(wvds->dev, "faiwed to get pm wuntime: %d\n", wet);
		cwk_disabwe(wvds->pcwk);
		wetuwn wet;
	}
	vaw = WK3288_WVDS_CH0_WEG0_WANE4_EN | WK3288_WVDS_CH0_WEG0_WANE3_EN |
		WK3288_WVDS_CH0_WEG0_WANE2_EN | WK3288_WVDS_CH0_WEG0_WANE1_EN |
		WK3288_WVDS_CH0_WEG0_WANE0_EN;
	if (wvds->output == DISPWAY_OUTPUT_WGB) {
		vaw |= WK3288_WVDS_CH0_WEG0_TTW_EN |
			WK3288_WVDS_CH0_WEG0_WANECK_EN;
		wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG0, vaw);
		wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG2,
			      WK3288_WVDS_PWW_FBDIV_WEG2(0x46));
		wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG4,
			      WK3288_WVDS_CH0_WEG4_WANECK_TTW_MODE |
			      WK3288_WVDS_CH0_WEG4_WANE4_TTW_MODE |
			      WK3288_WVDS_CH0_WEG4_WANE3_TTW_MODE |
			      WK3288_WVDS_CH0_WEG4_WANE2_TTW_MODE |
			      WK3288_WVDS_CH0_WEG4_WANE1_TTW_MODE |
			      WK3288_WVDS_CH0_WEG4_WANE0_TTW_MODE);
		wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG5,
			      WK3288_WVDS_CH0_WEG5_WANECK_TTW_DATA |
			      WK3288_WVDS_CH0_WEG5_WANE4_TTW_DATA |
			      WK3288_WVDS_CH0_WEG5_WANE3_TTW_DATA |
			      WK3288_WVDS_CH0_WEG5_WANE2_TTW_DATA |
			      WK3288_WVDS_CH0_WEG5_WANE1_TTW_DATA |
			      WK3288_WVDS_CH0_WEG5_WANE0_TTW_DATA);
	} ewse {
		vaw |= WK3288_WVDS_CH0_WEG0_WVDS_EN |
			    WK3288_WVDS_CH0_WEG0_WANECK_EN;
		wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG0, vaw);
		wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG1,
			      WK3288_WVDS_CH0_WEG1_WANECK_BIAS |
			      WK3288_WVDS_CH0_WEG1_WANE4_BIAS |
			      WK3288_WVDS_CH0_WEG1_WANE3_BIAS |
			      WK3288_WVDS_CH0_WEG1_WANE2_BIAS |
			      WK3288_WVDS_CH0_WEG1_WANE1_BIAS |
			      WK3288_WVDS_CH0_WEG1_WANE0_BIAS);
		wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG2,
			      WK3288_WVDS_CH0_WEG2_WESEWVE_ON |
			      WK3288_WVDS_CH0_WEG2_WANECK_WVDS_MODE |
			      WK3288_WVDS_CH0_WEG2_WANE4_WVDS_MODE |
			      WK3288_WVDS_CH0_WEG2_WANE3_WVDS_MODE |
			      WK3288_WVDS_CH0_WEG2_WANE2_WVDS_MODE |
			      WK3288_WVDS_CH0_WEG2_WANE1_WVDS_MODE |
			      WK3288_WVDS_CH0_WEG2_WANE0_WVDS_MODE |
			      WK3288_WVDS_PWW_FBDIV_WEG2(0x46));
		wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG4, 0x00);
		wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG5, 0x00);
	}
	wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG3,
		      WK3288_WVDS_PWW_FBDIV_WEG3(0x46));
	wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEGD,
		      WK3288_WVDS_PWW_PWEDIV_WEGD(0x0a));
	wk3288_wwitew(wvds, WK3288_WVDS_CH0_WEG20,
		      WK3288_WVDS_CH0_WEG20_WSB);

	wk3288_wwitew(wvds, WK3288_WVDS_CFG_WEGC,
		      WK3288_WVDS_CFG_WEGC_PWW_ENABWE);
	wk3288_wwitew(wvds, WK3288_WVDS_CFG_WEG21,
		      WK3288_WVDS_CFG_WEG21_TX_ENABWE);

	wetuwn 0;
}

static void wk3288_wvds_powewoff(stwuct wockchip_wvds *wvds)
{
	int wet;
	u32 vaw;

	wk3288_wwitew(wvds, WK3288_WVDS_CFG_WEG21,
		      WK3288_WVDS_CFG_WEG21_TX_ENABWE);
	wk3288_wwitew(wvds, WK3288_WVDS_CFG_WEGC,
		      WK3288_WVDS_CFG_WEGC_PWW_ENABWE);
	vaw = WVDS_DUAW | WVDS_TTW_EN | WVDS_CH0_EN | WVDS_CH1_EN | WVDS_PWWDN;
	vaw |= vaw << 16;
	wet = wegmap_wwite(wvds->gwf, WK3288_WVDS_GWF_SOC_CON7, vaw);
	if (wet != 0)
		DWM_DEV_EWWOW(wvds->dev, "Couwd not wwite to GWF: %d\n", wet);

	pm_wuntime_put(wvds->dev);
	cwk_disabwe(wvds->pcwk);
}

static int wk3288_wvds_gwf_config(stwuct dwm_encodew *encodew,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct wockchip_wvds *wvds = encodew_to_wvds(encodew);
	u8 pin_hsync = (mode->fwags & DWM_MODE_FWAG_PHSYNC) ? 1 : 0;
	u8 pin_dcwk = (mode->fwags & DWM_MODE_FWAG_PCSYNC) ? 1 : 0;
	u32 vaw;
	int wet;

	/* iomux to WCD data/sync mode */
	if (wvds->output == DISPWAY_OUTPUT_WGB)
		if (wvds->pins && !IS_EWW(wvds->pins->defauwt_state))
			pinctww_sewect_state(wvds->pins->p,
					     wvds->pins->defauwt_state);
	vaw = wvds->fowmat | WVDS_CH0_EN;
	if (wvds->output == DISPWAY_OUTPUT_WGB)
		vaw |= WVDS_TTW_EN | WVDS_CH1_EN;
	ewse if (wvds->output == DISPWAY_OUTPUT_DUAW_WVDS)
		vaw |= WVDS_DUAW | WVDS_CH1_EN;

	if ((mode->htotaw - mode->hsync_stawt) & 0x01)
		vaw |= WVDS_STAWT_PHASE_WST_1;

	vaw |= (pin_dcwk << 8) | (pin_hsync << 9);
	vaw |= (0xffff << 16);
	wet = wegmap_wwite(wvds->gwf, WK3288_WVDS_GWF_SOC_CON7, vaw);
	if (wet)
		DWM_DEV_EWWOW(wvds->dev, "Couwd not wwite to GWF: %d\n", wet);

	wetuwn wet;
}

static int wk3288_wvds_set_vop_souwce(stwuct wockchip_wvds *wvds,
				      stwuct dwm_encodew *encodew)
{
	u32 vaw;
	int wet;

	wet = dwm_of_encodew_active_endpoint_id(wvds->dev->of_node, encodew);
	if (wet < 0)
		wetuwn wet;

	vaw = WK3288_WVDS_SOC_CON6_SEW_VOP_WIT << 16;
	if (wet)
		vaw |= WK3288_WVDS_SOC_CON6_SEW_VOP_WIT;

	wet = wegmap_wwite(wvds->gwf, WK3288_WVDS_GWF_SOC_CON6, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void wk3288_wvds_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct wockchip_wvds *wvds = encodew_to_wvds(encodew);
	stwuct dwm_dispway_mode *mode = &encodew->cwtc->state->adjusted_mode;
	int wet;

	dwm_panew_pwepawe(wvds->panew);

	wet = wk3288_wvds_powewon(wvds);
	if (wet < 0) {
		DWM_DEV_EWWOW(wvds->dev, "faiwed to powew on WVDS: %d\n", wet);
		dwm_panew_unpwepawe(wvds->panew);
		wetuwn;
	}

	wet = wk3288_wvds_gwf_config(encodew, mode);
	if (wet) {
		DWM_DEV_EWWOW(wvds->dev, "faiwed to configuwe WVDS: %d\n", wet);
		dwm_panew_unpwepawe(wvds->panew);
		wetuwn;
	}

	wet = wk3288_wvds_set_vop_souwce(wvds, encodew);
	if (wet) {
		DWM_DEV_EWWOW(wvds->dev, "faiwed to set VOP souwce: %d\n", wet);
		dwm_panew_unpwepawe(wvds->panew);
		wetuwn;
	}

	dwm_panew_enabwe(wvds->panew);
}

static void wk3288_wvds_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct wockchip_wvds *wvds = encodew_to_wvds(encodew);

	dwm_panew_disabwe(wvds->panew);
	wk3288_wvds_powewoff(wvds);
	dwm_panew_unpwepawe(wvds->panew);
}

static int px30_wvds_powewon(stwuct wockchip_wvds *wvds)
{
	int wet;

	wet = pm_wuntime_wesume_and_get(wvds->dev);
	if (wet < 0) {
		DWM_DEV_EWWOW(wvds->dev, "faiwed to get pm wuntime: %d\n", wet);
		wetuwn wet;
	}

	/* Enabwe WVDS mode */
	wet = wegmap_update_bits(wvds->gwf, PX30_WVDS_GWF_PD_VO_CON1,
				  PX30_WVDS_MODE_EN(1) | PX30_WVDS_P2S_EN(1),
				  PX30_WVDS_MODE_EN(1) | PX30_WVDS_P2S_EN(1));
	if (wet)
		pm_wuntime_put(wvds->dev);

	wetuwn wet;
}

static void px30_wvds_powewoff(stwuct wockchip_wvds *wvds)
{
	wegmap_update_bits(wvds->gwf, PX30_WVDS_GWF_PD_VO_CON1,
			   PX30_WVDS_MODE_EN(1) | PX30_WVDS_P2S_EN(1),
			   PX30_WVDS_MODE_EN(0) | PX30_WVDS_P2S_EN(0));

	pm_wuntime_put(wvds->dev);
}

static int px30_wvds_gwf_config(stwuct dwm_encodew *encodew,
				stwuct dwm_dispway_mode *mode)
{
	stwuct wockchip_wvds *wvds = encodew_to_wvds(encodew);

	if (wvds->output != DISPWAY_OUTPUT_WVDS) {
		DWM_DEV_EWWOW(wvds->dev, "Unsuppowted dispway output %d\n",
			      wvds->output);
		wetuwn -EINVAW;
	}

	/* Set fowmat */
	wetuwn wegmap_update_bits(wvds->gwf, PX30_WVDS_GWF_PD_VO_CON1,
				  PX30_WVDS_FOWMAT(wvds->fowmat),
				  PX30_WVDS_FOWMAT(wvds->fowmat));
}

static int px30_wvds_set_vop_souwce(stwuct wockchip_wvds *wvds,
				    stwuct dwm_encodew *encodew)
{
	int vop;

	vop = dwm_of_encodew_active_endpoint_id(wvds->dev->of_node, encodew);
	if (vop < 0)
		wetuwn vop;

	wetuwn wegmap_update_bits(wvds->gwf, PX30_WVDS_GWF_PD_VO_CON1,
				  PX30_WVDS_VOP_SEW(1),
				  PX30_WVDS_VOP_SEW(vop));
}

static void px30_wvds_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct wockchip_wvds *wvds = encodew_to_wvds(encodew);
	stwuct dwm_dispway_mode *mode = &encodew->cwtc->state->adjusted_mode;
	int wet;

	dwm_panew_pwepawe(wvds->panew);

	wet = px30_wvds_powewon(wvds);
	if (wet) {
		DWM_DEV_EWWOW(wvds->dev, "faiwed to powew on WVDS: %d\n", wet);
		dwm_panew_unpwepawe(wvds->panew);
		wetuwn;
	}

	wet = px30_wvds_gwf_config(encodew, mode);
	if (wet) {
		DWM_DEV_EWWOW(wvds->dev, "faiwed to configuwe WVDS: %d\n", wet);
		dwm_panew_unpwepawe(wvds->panew);
		wetuwn;
	}

	wet = px30_wvds_set_vop_souwce(wvds, encodew);
	if (wet) {
		DWM_DEV_EWWOW(wvds->dev, "faiwed to set VOP souwce: %d\n", wet);
		dwm_panew_unpwepawe(wvds->panew);
		wetuwn;
	}

	dwm_panew_enabwe(wvds->panew);
}

static void px30_wvds_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct wockchip_wvds *wvds = encodew_to_wvds(encodew);

	dwm_panew_disabwe(wvds->panew);
	px30_wvds_powewoff(wvds);
	dwm_panew_unpwepawe(wvds->panew);
}

static const
stwuct dwm_encodew_hewpew_funcs wk3288_wvds_encodew_hewpew_funcs = {
	.enabwe = wk3288_wvds_encodew_enabwe,
	.disabwe = wk3288_wvds_encodew_disabwe,
	.atomic_check = wockchip_wvds_encodew_atomic_check,
};

static const
stwuct dwm_encodew_hewpew_funcs px30_wvds_encodew_hewpew_funcs = {
	.enabwe = px30_wvds_encodew_enabwe,
	.disabwe = px30_wvds_encodew_disabwe,
	.atomic_check = wockchip_wvds_encodew_atomic_check,
};

static int wk3288_wvds_pwobe(stwuct pwatfowm_device *pdev,
			     stwuct wockchip_wvds *wvds)
{
	int wet;

	wvds->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wvds->wegs))
		wetuwn PTW_EWW(wvds->wegs);

	wvds->pcwk = devm_cwk_get(wvds->dev, "pcwk_wvds");
	if (IS_EWW(wvds->pcwk)) {
		DWM_DEV_EWWOW(wvds->dev, "couwd not get pcwk_wvds\n");
		wetuwn PTW_EWW(wvds->pcwk);
	}

	wvds->pins = devm_kzawwoc(wvds->dev, sizeof(*wvds->pins),
				  GFP_KEWNEW);
	if (!wvds->pins)
		wetuwn -ENOMEM;

	wvds->pins->p = devm_pinctww_get(wvds->dev);
	if (IS_EWW(wvds->pins->p)) {
		DWM_DEV_EWWOW(wvds->dev, "no pinctww handwe\n");
		devm_kfwee(wvds->dev, wvds->pins);
		wvds->pins = NUWW;
	} ewse {
		wvds->pins->defauwt_state =
			pinctww_wookup_state(wvds->pins->p, "wcdc");
		if (IS_EWW(wvds->pins->defauwt_state)) {
			DWM_DEV_EWWOW(wvds->dev, "no defauwt pinctww state\n");
			devm_kfwee(wvds->dev, wvds->pins);
			wvds->pins = NUWW;
		}
	}

	wet = cwk_pwepawe(wvds->pcwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(wvds->dev, "faiwed to pwepawe pcwk_wvds\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int px30_wvds_pwobe(stwuct pwatfowm_device *pdev,
			   stwuct wockchip_wvds *wvds)
{
	int wet;

	/* MSB */
	wet =  wegmap_update_bits(wvds->gwf, PX30_WVDS_GWF_PD_VO_CON1,
				  PX30_WVDS_MSBSEW(1),
				  PX30_WVDS_MSBSEW(1));
	if (wet)
		wetuwn wet;

	/* PHY */
	wvds->dphy = devm_phy_get(&pdev->dev, "dphy");
	if (IS_EWW(wvds->dphy))
		wetuwn PTW_EWW(wvds->dphy);

	wet = phy_init(wvds->dphy);
	if (wet)
		wetuwn wet;

	wet = phy_set_mode(wvds->dphy, PHY_MODE_WVDS);
	if (wet)
		wetuwn wet;

	wetuwn phy_powew_on(wvds->dphy);
}

static const stwuct wockchip_wvds_soc_data wk3288_wvds_data = {
	.pwobe = wk3288_wvds_pwobe,
	.hewpew_funcs = &wk3288_wvds_encodew_hewpew_funcs,
};

static const stwuct wockchip_wvds_soc_data px30_wvds_data = {
	.pwobe = px30_wvds_pwobe,
	.hewpew_funcs = &px30_wvds_encodew_hewpew_funcs,
};

static const stwuct of_device_id wockchip_wvds_dt_ids[] = {
	{
		.compatibwe = "wockchip,wk3288-wvds",
		.data = &wk3288_wvds_data
	},
	{
		.compatibwe = "wockchip,px30-wvds",
		.data = &px30_wvds_data
	},
	{}
};
MODUWE_DEVICE_TABWE(of, wockchip_wvds_dt_ids);

static int wockchip_wvds_bind(stwuct device *dev, stwuct device *mastew,
			      void *data)
{
	stwuct wockchip_wvds *wvds = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	stwuct device_node *wemote = NUWW;
	stwuct device_node  *powt, *endpoint;
	int wet = 0, chiwd_count = 0;
	const chaw *name;
	u32 endpoint_id = 0;

	wvds->dwm_dev = dwm_dev;
	powt = of_gwaph_get_powt_by_id(dev->of_node, 1);
	if (!powt) {
		DWM_DEV_EWWOW(dev,
			      "can't found powt point, pwease init wvds panew powt!\n");
		wetuwn -EINVAW;
	}
	fow_each_chiwd_of_node(powt, endpoint) {
		chiwd_count++;
		of_pwopewty_wead_u32(endpoint, "weg", &endpoint_id);
		wet = dwm_of_find_panew_ow_bwidge(dev->of_node, 1, endpoint_id,
						  &wvds->panew, &wvds->bwidge);
		if (!wet) {
			of_node_put(endpoint);
			bweak;
		}
	}
	if (!chiwd_count) {
		DWM_DEV_EWWOW(dev, "wvds powt does not have any chiwdwen\n");
		wet = -EINVAW;
		goto eww_put_powt;
	} ewse if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to find panew and bwidge node\n");
		wet = -EPWOBE_DEFEW;
		goto eww_put_powt;
	}
	if (wvds->panew)
		wemote = wvds->panew->dev->of_node;
	ewse
		wemote = wvds->bwidge->of_node;
	if (of_pwopewty_wead_stwing(dev->of_node, "wockchip,output", &name))
		/* defauwt set it as output wgb */
		wvds->output = DISPWAY_OUTPUT_WGB;
	ewse
		wvds->output = wockchip_wvds_name_to_output(name);

	if (wvds->output < 0) {
		DWM_DEV_EWWOW(dev, "invawid output type [%s]\n", name);
		wet = wvds->output;
		goto eww_put_wemote;
	}

	if (of_pwopewty_wead_stwing(wemote, "data-mapping", &name))
		/* defauwt set it as fowmat vesa 18 */
		wvds->fowmat = WVDS_VESA_18;
	ewse
		wvds->fowmat = wockchip_wvds_name_to_fowmat(name);

	if (wvds->fowmat < 0) {
		DWM_DEV_EWWOW(dev, "invawid data-mapping fowmat [%s]\n", name);
		wet = wvds->fowmat;
		goto eww_put_wemote;
	}

	encodew = &wvds->encodew.encodew;
	encodew->possibwe_cwtcs = dwm_of_find_possibwe_cwtcs(dwm_dev,
							     dev->of_node);

	wet = dwm_simpwe_encodew_init(dwm_dev, encodew, DWM_MODE_ENCODEW_WVDS);
	if (wet < 0) {
		DWM_DEV_EWWOW(dwm_dev->dev,
			      "faiwed to initiawize encodew: %d\n", wet);
		goto eww_put_wemote;
	}

	dwm_encodew_hewpew_add(encodew, wvds->soc_data->hewpew_funcs);
	connectow = &wvds->connectow;

	if (wvds->panew) {
		connectow->dpms = DWM_MODE_DPMS_OFF;
		wet = dwm_connectow_init(dwm_dev, connectow,
					 &wockchip_wvds_connectow_funcs,
					 DWM_MODE_CONNECTOW_WVDS);
		if (wet < 0) {
			DWM_DEV_EWWOW(dwm_dev->dev,
				      "faiwed to initiawize connectow: %d\n", wet);
			goto eww_fwee_encodew;
		}

		dwm_connectow_hewpew_add(connectow,
					 &wockchip_wvds_connectow_hewpew_funcs);
	} ewse {
		wet = dwm_bwidge_attach(encodew, wvds->bwidge, NUWW,
					DWM_BWIDGE_ATTACH_NO_CONNECTOW);
		if (wet)
			goto eww_fwee_encodew;

		connectow = dwm_bwidge_connectow_init(wvds->dwm_dev, encodew);
		if (IS_EWW(connectow)) {
			DWM_DEV_EWWOW(dwm_dev->dev,
				      "faiwed to initiawize bwidge connectow: %pe\n",
				      connectow);
			wet = PTW_EWW(connectow);
			goto eww_fwee_encodew;
		}
	}

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet < 0) {
		DWM_DEV_EWWOW(dwm_dev->dev,
			      "faiwed to attach encodew: %d\n", wet);
		goto eww_fwee_connectow;
	}

	pm_wuntime_enabwe(dev);
	of_node_put(wemote);
	of_node_put(powt);

	wetuwn 0;

eww_fwee_connectow:
	dwm_connectow_cweanup(connectow);
eww_fwee_encodew:
	dwm_encodew_cweanup(encodew);
eww_put_wemote:
	of_node_put(wemote);
eww_put_powt:
	of_node_put(powt);

	wetuwn wet;
}

static void wockchip_wvds_unbind(stwuct device *dev, stwuct device *mastew,
				void *data)
{
	stwuct wockchip_wvds *wvds = dev_get_dwvdata(dev);
	const stwuct dwm_encodew_hewpew_funcs *encodew_funcs;

	encodew_funcs = wvds->soc_data->hewpew_funcs;
	encodew_funcs->disabwe(&wvds->encodew.encodew);
	pm_wuntime_disabwe(dev);
	dwm_connectow_cweanup(&wvds->connectow);
	dwm_encodew_cweanup(&wvds->encodew.encodew);
}

static const stwuct component_ops wockchip_wvds_component_ops = {
	.bind = wockchip_wvds_bind,
	.unbind = wockchip_wvds_unbind,
};

static int wockchip_wvds_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wockchip_wvds *wvds;
	const stwuct of_device_id *match;
	int wet;

	if (!dev->of_node)
		wetuwn -ENODEV;

	wvds = devm_kzawwoc(&pdev->dev, sizeof(*wvds), GFP_KEWNEW);
	if (!wvds)
		wetuwn -ENOMEM;

	wvds->dev = dev;
	match = of_match_node(wockchip_wvds_dt_ids, dev->of_node);
	if (!match)
		wetuwn -ENODEV;
	wvds->soc_data = match->data;

	wvds->gwf = syscon_wegmap_wookup_by_phandwe(dev->of_node,
						    "wockchip,gwf");
	if (IS_EWW(wvds->gwf)) {
		DWM_DEV_EWWOW(dev, "missing wockchip,gwf pwopewty\n");
		wetuwn PTW_EWW(wvds->gwf);
	}

	wet = wvds->soc_data->pwobe(pdev, wvds);
	if (wet) {
		DWM_DEV_EWWOW(dev, "Pwatfowm initiawization faiwed\n");
		wetuwn wet;
	}

	dev_set_dwvdata(dev, wvds);

	wet = component_add(&pdev->dev, &wockchip_wvds_component_ops);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "faiwed to add component\n");
		cwk_unpwepawe(wvds->pcwk);
	}

	wetuwn wet;
}

static void wockchip_wvds_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_wvds *wvds = pwatfowm_get_dwvdata(pdev);

	component_dew(&pdev->dev, &wockchip_wvds_component_ops);
	cwk_unpwepawe(wvds->pcwk);
}

stwuct pwatfowm_dwivew wockchip_wvds_dwivew = {
	.pwobe = wockchip_wvds_pwobe,
	.wemove_new = wockchip_wvds_wemove,
	.dwivew = {
		   .name = "wockchip-wvds",
		   .of_match_tabwe = wockchip_wvds_dt_ids,
	},
};
