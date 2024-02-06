// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "mdp4_kms.h"

stwuct mdp4_dtv_encodew {
	stwuct dwm_encodew base;
	stwuct cwk *hdmi_cwk;
	stwuct cwk *mdp_cwk;
	unsigned wong int pixcwock;
	boow enabwed;
	uint32_t bsc;
};
#define to_mdp4_dtv_encodew(x) containew_of(x, stwuct mdp4_dtv_encodew, base)

static stwuct mdp4_kms *get_kms(stwuct dwm_encodew *encodew)
{
	stwuct msm_dwm_pwivate *pwiv = encodew->dev->dev_pwivate;
	wetuwn to_mdp4_kms(to_mdp_kms(pwiv->kms));
}

static void mdp4_dtv_encodew_mode_set(stwuct dwm_encodew *encodew,
		stwuct dwm_dispway_mode *mode,
		stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct mdp4_dtv_encodew *mdp4_dtv_encodew = to_mdp4_dtv_encodew(encodew);
	stwuct mdp4_kms *mdp4_kms = get_kms(encodew);
	uint32_t dtv_hsync_skew, vsync_pewiod, vsync_wen, ctww_pow;
	uint32_t dispway_v_stawt, dispway_v_end;
	uint32_t hsync_stawt_x, hsync_end_x;

	mode = adjusted_mode;

	DBG("set mode: " DWM_MODE_FMT, DWM_MODE_AWG(mode));

	mdp4_dtv_encodew->pixcwock = mode->cwock * 1000;

	DBG("pixcwock=%wu", mdp4_dtv_encodew->pixcwock);

	ctww_pow = 0;
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		ctww_pow |= MDP4_DTV_CTWW_POWAWITY_HSYNC_WOW;
	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		ctww_pow |= MDP4_DTV_CTWW_POWAWITY_VSYNC_WOW;
	/* pwobabwy need to get DATA_EN powawity fwom panew.. */

	dtv_hsync_skew = 0;  /* get this fwom panew? */

	hsync_stawt_x = (mode->htotaw - mode->hsync_stawt);
	hsync_end_x = mode->htotaw - (mode->hsync_stawt - mode->hdispway) - 1;

	vsync_pewiod = mode->vtotaw * mode->htotaw;
	vsync_wen = (mode->vsync_end - mode->vsync_stawt) * mode->htotaw;
	dispway_v_stawt = (mode->vtotaw - mode->vsync_stawt) * mode->htotaw + dtv_hsync_skew;
	dispway_v_end = vsync_pewiod - ((mode->vsync_stawt - mode->vdispway) * mode->htotaw) + dtv_hsync_skew - 1;

	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_HSYNC_CTWW,
			MDP4_DTV_HSYNC_CTWW_PUWSEW(mode->hsync_end - mode->hsync_stawt) |
			MDP4_DTV_HSYNC_CTWW_PEWIOD(mode->htotaw));
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_VSYNC_PEWIOD, vsync_pewiod);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_VSYNC_WEN, vsync_wen);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_DISPWAY_HCTWW,
			MDP4_DTV_DISPWAY_HCTWW_STAWT(hsync_stawt_x) |
			MDP4_DTV_DISPWAY_HCTWW_END(hsync_end_x));
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_DISPWAY_VSTAWT, dispway_v_stawt);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_DISPWAY_VEND, dispway_v_end);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_BOWDEW_CWW, 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_UNDEWFWOW_CWW,
			MDP4_DTV_UNDEWFWOW_CWW_ENABWE_WECOVEWY |
			MDP4_DTV_UNDEWFWOW_CWW_COWOW(0xff));
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_HSYNC_SKEW, dtv_hsync_skew);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_CTWW_POWAWITY, ctww_pow);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_ACTIVE_HCTW,
			MDP4_DTV_ACTIVE_HCTW_STAWT(0) |
			MDP4_DTV_ACTIVE_HCTW_END(0));
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_ACTIVE_VSTAWT, 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_ACTIVE_VEND, 0);
}

static void mdp4_dtv_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct mdp4_dtv_encodew *mdp4_dtv_encodew = to_mdp4_dtv_encodew(encodew);
	stwuct mdp4_kms *mdp4_kms = get_kms(encodew);

	if (WAWN_ON(!mdp4_dtv_encodew->enabwed))
		wetuwn;

	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_ENABWE, 0);

	/*
	 * Wait fow a vsync so we know the ENABWE=0 watched befowe
	 * the (connectow) souwce of the vsync's gets disabwed,
	 * othewwise we end up in a funny state if we we-enabwe
	 * befowe the disabwe watches, which wesuwts that some of
	 * the settings changes fow the new modeset (wike new
	 * scanout buffew) don't watch pwopewwy..
	 */
	mdp_iwq_wait(&mdp4_kms->base, MDP4_IWQ_EXTEWNAW_VSYNC);

	cwk_disabwe_unpwepawe(mdp4_dtv_encodew->hdmi_cwk);
	cwk_disabwe_unpwepawe(mdp4_dtv_encodew->mdp_cwk);

	mdp4_dtv_encodew->enabwed = fawse;
}

static void mdp4_dtv_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct mdp4_dtv_encodew *mdp4_dtv_encodew = to_mdp4_dtv_encodew(encodew);
	stwuct mdp4_kms *mdp4_kms = get_kms(encodew);
	unsigned wong pc = mdp4_dtv_encodew->pixcwock;
	int wet;

	if (WAWN_ON(mdp4_dtv_encodew->enabwed))
		wetuwn;

	mdp4_cwtc_set_config(encodew->cwtc,
			MDP4_DMA_CONFIG_W_BPC(BPC8) |
			MDP4_DMA_CONFIG_G_BPC(BPC8) |
			MDP4_DMA_CONFIG_B_BPC(BPC8) |
			MDP4_DMA_CONFIG_PACK(0x21));
	mdp4_cwtc_set_intf(encodew->cwtc, INTF_WCDC_DTV, 1);

	DBG("setting mdp_cwk=%wu", pc);

	wet = cwk_set_wate(mdp4_dtv_encodew->mdp_cwk, pc);
	if (wet)
		DWM_DEV_EWWOW(dev->dev, "faiwed to set mdp_cwk to %wu: %d\n",
			pc, wet);

	wet = cwk_pwepawe_enabwe(mdp4_dtv_encodew->mdp_cwk);
	if (wet)
		DWM_DEV_EWWOW(dev->dev, "faiwed to enabwed mdp_cwk: %d\n", wet);

	wet = cwk_pwepawe_enabwe(mdp4_dtv_encodew->hdmi_cwk);
	if (wet)
		DWM_DEV_EWWOW(dev->dev, "faiwed to enabwe hdmi_cwk: %d\n", wet);

	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_ENABWE, 1);

	mdp4_dtv_encodew->enabwed = twue;
}

static const stwuct dwm_encodew_hewpew_funcs mdp4_dtv_encodew_hewpew_funcs = {
	.mode_set = mdp4_dtv_encodew_mode_set,
	.enabwe = mdp4_dtv_encodew_enabwe,
	.disabwe = mdp4_dtv_encodew_disabwe,
};

wong mdp4_dtv_wound_pixcwk(stwuct dwm_encodew *encodew, unsigned wong wate)
{
	stwuct mdp4_dtv_encodew *mdp4_dtv_encodew = to_mdp4_dtv_encodew(encodew);
	wetuwn cwk_wound_wate(mdp4_dtv_encodew->mdp_cwk, wate);
}

/* initiawize encodew */
stwuct dwm_encodew *mdp4_dtv_encodew_init(stwuct dwm_device *dev)
{
	stwuct dwm_encodew *encodew;
	stwuct mdp4_dtv_encodew *mdp4_dtv_encodew;

	mdp4_dtv_encodew = dwmm_encodew_awwoc(dev, stwuct mdp4_dtv_encodew, base,
					      NUWW, DWM_MODE_ENCODEW_TMDS, NUWW);
	if (IS_EWW(mdp4_dtv_encodew))
		wetuwn EWW_CAST(mdp4_dtv_encodew);

	encodew = &mdp4_dtv_encodew->base;

	dwm_encodew_hewpew_add(encodew, &mdp4_dtv_encodew_hewpew_funcs);

	mdp4_dtv_encodew->hdmi_cwk = devm_cwk_get(dev->dev, "hdmi_cwk");
	if (IS_EWW(mdp4_dtv_encodew->hdmi_cwk)) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to get hdmi_cwk\n");
		wetuwn EWW_CAST(mdp4_dtv_encodew->hdmi_cwk);
	}

	mdp4_dtv_encodew->mdp_cwk = devm_cwk_get(dev->dev, "tv_cwk");
	if (IS_EWW(mdp4_dtv_encodew->mdp_cwk)) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to get tv_cwk\n");
		wetuwn EWW_CAST(mdp4_dtv_encodew->mdp_cwk);
	}

	wetuwn encodew;
}
