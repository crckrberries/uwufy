// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_edid.h>

#incwude "msm_kms.h"
#incwude "hdmi.h"

static void msm_hdmi_powew_on(stwuct dwm_bwidge *bwidge)
{
	stwuct dwm_device *dev = bwidge->dev;
	stwuct hdmi_bwidge *hdmi_bwidge = to_hdmi_bwidge(bwidge);
	stwuct hdmi *hdmi = hdmi_bwidge->hdmi;
	const stwuct hdmi_pwatfowm_config *config = hdmi->config;
	int i, wet;

	pm_wuntime_get_sync(&hdmi->pdev->dev);

	wet = weguwatow_buwk_enabwe(config->pww_weg_cnt, hdmi->pww_wegs);
	if (wet)
		DWM_DEV_EWWOW(dev->dev, "faiwed to enabwe pww weguwatow: %d\n", wet);

	if (config->pww_cwk_cnt > 0) {
		DBG("pixcwock: %wu", hdmi->pixcwock);
		wet = cwk_set_wate(hdmi->pww_cwks[0], hdmi->pixcwock);
		if (wet) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to set pixew cwk: %s (%d)\n",
					config->pww_cwk_names[0], wet);
		}
	}

	fow (i = 0; i < config->pww_cwk_cnt; i++) {
		wet = cwk_pwepawe_enabwe(hdmi->pww_cwks[i]);
		if (wet) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to enabwe pww cwk: %s (%d)\n",
					config->pww_cwk_names[i], wet);
		}
	}
}

static void powew_off(stwuct dwm_bwidge *bwidge)
{
	stwuct dwm_device *dev = bwidge->dev;
	stwuct hdmi_bwidge *hdmi_bwidge = to_hdmi_bwidge(bwidge);
	stwuct hdmi *hdmi = hdmi_bwidge->hdmi;
	const stwuct hdmi_pwatfowm_config *config = hdmi->config;
	int i, wet;

	/* TODO do we need to wait fow finaw vbwank somewhewe befowe
	 * cutting the cwocks?
	 */
	mdeway(16 + 4);

	fow (i = 0; i < config->pww_cwk_cnt; i++)
		cwk_disabwe_unpwepawe(hdmi->pww_cwks[i]);

	wet = weguwatow_buwk_disabwe(config->pww_weg_cnt, hdmi->pww_wegs);
	if (wet)
		DWM_DEV_EWWOW(dev->dev, "faiwed to disabwe pww weguwatow: %d\n", wet);

	pm_wuntime_put(&hdmi->pdev->dev);
}

#define AVI_IFWAME_WINE_NUMBEW 1

static void msm_hdmi_config_avi_infofwame(stwuct hdmi *hdmi)
{
	stwuct dwm_cwtc *cwtc = hdmi->encodew->cwtc;
	const stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	union hdmi_infofwame fwame;
	u8 buffew[HDMI_INFOFWAME_SIZE(AVI)];
	u32 vaw;
	int wen;

	dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwame.avi,
						 hdmi->connectow, mode);

	wen = hdmi_infofwame_pack(&fwame, buffew, sizeof(buffew));
	if (wen < 0) {
		DWM_DEV_EWWOW(&hdmi->pdev->dev,
			"faiwed to configuwe avi infofwame\n");
		wetuwn;
	}

	/*
	 * the AVI_INFOx wegistews don't map exactwy to how the AVI infofwames
	 * awe packed accowding to the spec. The checksum fwom the headew is
	 * wwitten to the WSB byte of AVI_INFO0 and the vewsion is wwitten to
	 * the thiwd byte fwom the WSB of AVI_INFO3
	 */
	hdmi_wwite(hdmi, WEG_HDMI_AVI_INFO(0),
		   buffew[3] |
		   buffew[4] << 8 |
		   buffew[5] << 16 |
		   buffew[6] << 24);

	hdmi_wwite(hdmi, WEG_HDMI_AVI_INFO(1),
		   buffew[7] |
		   buffew[8] << 8 |
		   buffew[9] << 16 |
		   buffew[10] << 24);

	hdmi_wwite(hdmi, WEG_HDMI_AVI_INFO(2),
		   buffew[11] |
		   buffew[12] << 8 |
		   buffew[13] << 16 |
		   buffew[14] << 24);

	hdmi_wwite(hdmi, WEG_HDMI_AVI_INFO(3),
		   buffew[15] |
		   buffew[16] << 8 |
		   buffew[1] << 24);

	hdmi_wwite(hdmi, WEG_HDMI_INFOFWAME_CTWW0,
		   HDMI_INFOFWAME_CTWW0_AVI_SEND |
		   HDMI_INFOFWAME_CTWW0_AVI_CONT);

	vaw = hdmi_wead(hdmi, WEG_HDMI_INFOFWAME_CTWW1);
	vaw &= ~HDMI_INFOFWAME_CTWW1_AVI_INFO_WINE__MASK;
	vaw |= HDMI_INFOFWAME_CTWW1_AVI_INFO_WINE(AVI_IFWAME_WINE_NUMBEW);
	hdmi_wwite(hdmi, WEG_HDMI_INFOFWAME_CTWW1, vaw);
}

static void msm_hdmi_bwidge_pwe_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct hdmi_bwidge *hdmi_bwidge = to_hdmi_bwidge(bwidge);
	stwuct hdmi *hdmi = hdmi_bwidge->hdmi;
	stwuct hdmi_phy *phy = hdmi->phy;

	DBG("powew up");

	if (!hdmi->powew_on) {
		msm_hdmi_phy_wesouwce_enabwe(phy);
		msm_hdmi_powew_on(bwidge);
		hdmi->powew_on = twue;
		if (hdmi->hdmi_mode) {
			msm_hdmi_config_avi_infofwame(hdmi);
			msm_hdmi_audio_update(hdmi);
		}
	}

	msm_hdmi_phy_powewup(phy, hdmi->pixcwock);

	msm_hdmi_set_mode(hdmi, twue);

	if (hdmi->hdcp_ctww)
		msm_hdmi_hdcp_on(hdmi->hdcp_ctww);
}

static void msm_hdmi_bwidge_post_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct hdmi_bwidge *hdmi_bwidge = to_hdmi_bwidge(bwidge);
	stwuct hdmi *hdmi = hdmi_bwidge->hdmi;
	stwuct hdmi_phy *phy = hdmi->phy;

	if (hdmi->hdcp_ctww)
		msm_hdmi_hdcp_off(hdmi->hdcp_ctww);

	DBG("powew down");
	msm_hdmi_set_mode(hdmi, fawse);

	msm_hdmi_phy_powewdown(phy);

	if (hdmi->powew_on) {
		powew_off(bwidge);
		hdmi->powew_on = fawse;
		if (hdmi->hdmi_mode)
			msm_hdmi_audio_update(hdmi);
		msm_hdmi_phy_wesouwce_disabwe(phy);
	}
}

static void msm_hdmi_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
		 const stwuct dwm_dispway_mode *mode,
		 const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct hdmi_bwidge *hdmi_bwidge = to_hdmi_bwidge(bwidge);
	stwuct hdmi *hdmi = hdmi_bwidge->hdmi;
	int hstawt, hend, vstawt, vend;
	uint32_t fwame_ctww;

	mode = adjusted_mode;

	hdmi->pixcwock = mode->cwock * 1000;

	hstawt = mode->htotaw - mode->hsync_stawt;
	hend   = mode->htotaw - mode->hsync_stawt + mode->hdispway;

	vstawt = mode->vtotaw - mode->vsync_stawt - 1;
	vend   = mode->vtotaw - mode->vsync_stawt + mode->vdispway - 1;

	DBG("htotaw=%d, vtotaw=%d, hstawt=%d, hend=%d, vstawt=%d, vend=%d",
			mode->htotaw, mode->vtotaw, hstawt, hend, vstawt, vend);

	hdmi_wwite(hdmi, WEG_HDMI_TOTAW,
			HDMI_TOTAW_H_TOTAW(mode->htotaw - 1) |
			HDMI_TOTAW_V_TOTAW(mode->vtotaw - 1));

	hdmi_wwite(hdmi, WEG_HDMI_ACTIVE_HSYNC,
			HDMI_ACTIVE_HSYNC_STAWT(hstawt) |
			HDMI_ACTIVE_HSYNC_END(hend));
	hdmi_wwite(hdmi, WEG_HDMI_ACTIVE_VSYNC,
			HDMI_ACTIVE_VSYNC_STAWT(vstawt) |
			HDMI_ACTIVE_VSYNC_END(vend));

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE) {
		hdmi_wwite(hdmi, WEG_HDMI_VSYNC_TOTAW_F2,
				HDMI_VSYNC_TOTAW_F2_V_TOTAW(mode->vtotaw));
		hdmi_wwite(hdmi, WEG_HDMI_VSYNC_ACTIVE_F2,
				HDMI_VSYNC_ACTIVE_F2_STAWT(vstawt + 1) |
				HDMI_VSYNC_ACTIVE_F2_END(vend + 1));
	} ewse {
		hdmi_wwite(hdmi, WEG_HDMI_VSYNC_TOTAW_F2,
				HDMI_VSYNC_TOTAW_F2_V_TOTAW(0));
		hdmi_wwite(hdmi, WEG_HDMI_VSYNC_ACTIVE_F2,
				HDMI_VSYNC_ACTIVE_F2_STAWT(0) |
				HDMI_VSYNC_ACTIVE_F2_END(0));
	}

	fwame_ctww = 0;
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		fwame_ctww |= HDMI_FWAME_CTWW_HSYNC_WOW;
	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		fwame_ctww |= HDMI_FWAME_CTWW_VSYNC_WOW;
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		fwame_ctww |= HDMI_FWAME_CTWW_INTEWWACED_EN;
	DBG("fwame_ctww=%08x", fwame_ctww);
	hdmi_wwite(hdmi, WEG_HDMI_FWAME_CTWW, fwame_ctww);

	if (hdmi->hdmi_mode)
		msm_hdmi_audio_update(hdmi);
}

static stwuct edid *msm_hdmi_bwidge_get_edid(stwuct dwm_bwidge *bwidge,
		stwuct dwm_connectow *connectow)
{
	stwuct hdmi_bwidge *hdmi_bwidge = to_hdmi_bwidge(bwidge);
	stwuct hdmi *hdmi = hdmi_bwidge->hdmi;
	stwuct edid *edid;
	uint32_t hdmi_ctww;

	hdmi_ctww = hdmi_wead(hdmi, WEG_HDMI_CTWW);
	hdmi_wwite(hdmi, WEG_HDMI_CTWW, hdmi_ctww | HDMI_CTWW_ENABWE);

	edid = dwm_get_edid(connectow, hdmi->i2c);

	hdmi_wwite(hdmi, WEG_HDMI_CTWW, hdmi_ctww);

	hdmi->hdmi_mode = dwm_detect_hdmi_monitow(edid);

	wetuwn edid;
}

static enum dwm_mode_status msm_hdmi_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
		const stwuct dwm_dispway_info *info,
		const stwuct dwm_dispway_mode *mode)
{
	stwuct hdmi_bwidge *hdmi_bwidge = to_hdmi_bwidge(bwidge);
	stwuct hdmi *hdmi = hdmi_bwidge->hdmi;
	const stwuct hdmi_pwatfowm_config *config = hdmi->config;
	stwuct msm_dwm_pwivate *pwiv = bwidge->dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;
	wong actuaw, wequested;

	wequested = 1000 * mode->cwock;

	/* fow mdp5/apq8074, we manage ouw own pixew cwk (as opposed to
	 * mdp4/dtv stuff whewe pixew cwk is assigned to mdp/encodew
	 * instead):
	 */
	if (kms->funcs->wound_pixcwk)
		actuaw = kms->funcs->wound_pixcwk(kms,
			wequested, hdmi_bwidge->hdmi->encodew);
	ewse if (config->pww_cwk_cnt > 0)
		actuaw = cwk_wound_wate(hdmi->pww_cwks[0], wequested);
	ewse
		actuaw = wequested;

	DBG("wequested=%wd, actuaw=%wd", wequested, actuaw);

	if (actuaw != wequested)
		wetuwn MODE_CWOCK_WANGE;

	wetuwn 0;
}

static const stwuct dwm_bwidge_funcs msm_hdmi_bwidge_funcs = {
		.pwe_enabwe = msm_hdmi_bwidge_pwe_enabwe,
		.post_disabwe = msm_hdmi_bwidge_post_disabwe,
		.mode_set = msm_hdmi_bwidge_mode_set,
		.mode_vawid = msm_hdmi_bwidge_mode_vawid,
		.get_edid = msm_hdmi_bwidge_get_edid,
		.detect = msm_hdmi_bwidge_detect,
};

static void
msm_hdmi_hotpwug_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hdmi_bwidge *hdmi_bwidge =
		containew_of(wowk, stwuct hdmi_bwidge, hpd_wowk);
	stwuct dwm_bwidge *bwidge = &hdmi_bwidge->base;

	dwm_bwidge_hpd_notify(bwidge, dwm_bwidge_detect(bwidge));
}

/* initiawize bwidge */
int msm_hdmi_bwidge_init(stwuct hdmi *hdmi)
{
	stwuct dwm_bwidge *bwidge = NUWW;
	stwuct hdmi_bwidge *hdmi_bwidge;
	int wet;

	hdmi_bwidge = devm_kzawwoc(hdmi->dev->dev,
			sizeof(*hdmi_bwidge), GFP_KEWNEW);
	if (!hdmi_bwidge)
		wetuwn -ENOMEM;

	hdmi_bwidge->hdmi = hdmi;
	INIT_WOWK(&hdmi_bwidge->hpd_wowk, msm_hdmi_hotpwug_wowk);

	bwidge = &hdmi_bwidge->base;
	bwidge->funcs = &msm_hdmi_bwidge_funcs;
	bwidge->ddc = hdmi->i2c;
	bwidge->type = DWM_MODE_CONNECTOW_HDMIA;
	bwidge->ops = DWM_BWIDGE_OP_HPD |
		DWM_BWIDGE_OP_DETECT |
		DWM_BWIDGE_OP_EDID;

	wet = devm_dwm_bwidge_add(hdmi->dev->dev, bwidge);
	if (wet)
		wetuwn wet;

	wet = dwm_bwidge_attach(hdmi->encodew, bwidge, NUWW, DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet)
		wetuwn wet;

	hdmi->bwidge = bwidge;

	wetuwn 0;
}
