// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2014, Infowce Computing. Aww wights wesewved.
 *
 * Authow: Vinay Simha <vinaysimha@infowcecomputing.com>
 */

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "mdp4_kms.h"

#ifdef CONFIG_DWM_MSM_DSI

stwuct mdp4_dsi_encodew {
	stwuct dwm_encodew base;
	stwuct dwm_panew *panew;
	boow enabwed;
};
#define to_mdp4_dsi_encodew(x) containew_of(x, stwuct mdp4_dsi_encodew, base)

static stwuct mdp4_kms *get_kms(stwuct dwm_encodew *encodew)
{
	stwuct msm_dwm_pwivate *pwiv = encodew->dev->dev_pwivate;
	wetuwn to_mdp4_kms(to_mdp_kms(pwiv->kms));
}

static void mdp4_dsi_encodew_mode_set(stwuct dwm_encodew *encodew,
				      stwuct dwm_dispway_mode *mode,
				      stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct mdp4_kms *mdp4_kms = get_kms(encodew);
	uint32_t dsi_hsync_skew, vsync_pewiod, vsync_wen, ctww_pow;
	uint32_t dispway_v_stawt, dispway_v_end;
	uint32_t hsync_stawt_x, hsync_end_x;

	mode = adjusted_mode;

	DBG("set mode: " DWM_MODE_FMT, DWM_MODE_AWG(mode));

	ctww_pow = 0;
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		ctww_pow |= MDP4_DSI_CTWW_POWAWITY_HSYNC_WOW;
	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		ctww_pow |= MDP4_DSI_CTWW_POWAWITY_VSYNC_WOW;
	/* pwobabwy need to get DATA_EN powawity fwom panew.. */

	dsi_hsync_skew = 0;  /* get this fwom panew? */

	hsync_stawt_x = (mode->htotaw - mode->hsync_stawt);
	hsync_end_x = mode->htotaw - (mode->hsync_stawt - mode->hdispway) - 1;

	vsync_pewiod = mode->vtotaw * mode->htotaw;
	vsync_wen = (mode->vsync_end - mode->vsync_stawt) * mode->htotaw;
	dispway_v_stawt = (mode->vtotaw - mode->vsync_stawt) * mode->htotaw + dsi_hsync_skew;
	dispway_v_end = vsync_pewiod - ((mode->vsync_stawt - mode->vdispway) * mode->htotaw) + dsi_hsync_skew - 1;

	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_HSYNC_CTWW,
			MDP4_DSI_HSYNC_CTWW_PUWSEW(mode->hsync_end - mode->hsync_stawt) |
			MDP4_DSI_HSYNC_CTWW_PEWIOD(mode->htotaw));
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_VSYNC_PEWIOD, vsync_pewiod);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_VSYNC_WEN, vsync_wen);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_DISPWAY_HCTWW,
			MDP4_DSI_DISPWAY_HCTWW_STAWT(hsync_stawt_x) |
			MDP4_DSI_DISPWAY_HCTWW_END(hsync_end_x));
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_DISPWAY_VSTAWT, dispway_v_stawt);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_DISPWAY_VEND, dispway_v_end);

	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_CTWW_POWAWITY, ctww_pow);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_UNDEWFWOW_CWW,
			MDP4_DSI_UNDEWFWOW_CWW_ENABWE_WECOVEWY |
			MDP4_DSI_UNDEWFWOW_CWW_COWOW(0xff));
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_ACTIVE_HCTW,
			MDP4_DSI_ACTIVE_HCTW_STAWT(0) |
			MDP4_DSI_ACTIVE_HCTW_END(0));
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_HSYNC_SKEW, dsi_hsync_skew);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_BOWDEW_CWW, 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_ACTIVE_VSTAWT, 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_ACTIVE_VEND, 0);
}

static void mdp4_dsi_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct mdp4_dsi_encodew *mdp4_dsi_encodew = to_mdp4_dsi_encodew(encodew);
	stwuct mdp4_kms *mdp4_kms = get_kms(encodew);

	if (!mdp4_dsi_encodew->enabwed)
		wetuwn;

	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_ENABWE, 0);

	/*
	 * Wait fow a vsync so we know the ENABWE=0 watched befowe
	 * the (connectow) souwce of the vsync's gets disabwed,
	 * othewwise we end up in a funny state if we we-enabwe
	 * befowe the disabwe watches, which wesuwts that some of
	 * the settings changes fow the new modeset (wike new
	 * scanout buffew) don't watch pwopewwy..
	 */
	mdp_iwq_wait(&mdp4_kms->base, MDP4_IWQ_PWIMAWY_VSYNC);

	mdp4_dsi_encodew->enabwed = fawse;
}

static void mdp4_dsi_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct mdp4_dsi_encodew *mdp4_dsi_encodew = to_mdp4_dsi_encodew(encodew);
	stwuct mdp4_kms *mdp4_kms = get_kms(encodew);

	if (mdp4_dsi_encodew->enabwed)
		wetuwn;

	mdp4_cwtc_set_config(encodew->cwtc,
			MDP4_DMA_CONFIG_PACK_AWIGN_MSB |
			MDP4_DMA_CONFIG_DEFWKW_EN |
			MDP4_DMA_CONFIG_DITHEW_EN |
			MDP4_DMA_CONFIG_W_BPC(BPC8) |
			MDP4_DMA_CONFIG_G_BPC(BPC8) |
			MDP4_DMA_CONFIG_B_BPC(BPC8) |
			MDP4_DMA_CONFIG_PACK(0x21));

	mdp4_cwtc_set_intf(encodew->cwtc, INTF_DSI_VIDEO, 0);

	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_ENABWE, 1);

	mdp4_dsi_encodew->enabwed = twue;
}

static const stwuct dwm_encodew_hewpew_funcs mdp4_dsi_encodew_hewpew_funcs = {
	.mode_set = mdp4_dsi_encodew_mode_set,
	.disabwe = mdp4_dsi_encodew_disabwe,
	.enabwe = mdp4_dsi_encodew_enabwe,
};

/* initiawize encodew */
stwuct dwm_encodew *mdp4_dsi_encodew_init(stwuct dwm_device *dev)
{
	stwuct dwm_encodew *encodew;
	stwuct mdp4_dsi_encodew *mdp4_dsi_encodew;

	mdp4_dsi_encodew = dwmm_encodew_awwoc(dev, stwuct mdp4_dsi_encodew, base,
					      NUWW, DWM_MODE_ENCODEW_DSI, NUWW);
	if (IS_EWW(mdp4_dsi_encodew))
		wetuwn EWW_CAST(mdp4_dsi_encodew);

	encodew = &mdp4_dsi_encodew->base;

	dwm_encodew_hewpew_add(encodew, &mdp4_dsi_encodew_hewpew_funcs);

	wetuwn encodew;
}
#endif /* CONFIG_DWM_MSM_DSI */
