// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow: Chwis Zhong <zyw@wock-chips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/extcon.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude <sound/hdmi-codec.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "cdn-dp-cowe.h"
#incwude "cdn-dp-weg.h"

static inwine stwuct cdn_dp_device *connectow_to_dp(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct cdn_dp_device, connectow);
}

static inwine stwuct cdn_dp_device *encodew_to_dp(stwuct dwm_encodew *encodew)
{
	stwuct wockchip_encodew *wkencodew = to_wockchip_encodew(encodew);

	wetuwn containew_of(wkencodew, stwuct cdn_dp_device, encodew);
}

#define GWF_SOC_CON9		0x6224
#define DP_SEW_VOP_WIT		BIT(12)
#define GWF_SOC_CON26		0x6268
#define DPTX_HPD_SEW		(3 << 12)
#define DPTX_HPD_DEW		(2 << 12)
#define DPTX_HPD_SEW_MASK	(3 << 28)

#define CDN_FW_TIMEOUT_MS	(64 * 1000)
#define CDN_DPCD_TIMEOUT_MS	5000
#define CDN_DP_FIWMWAWE		"wockchip/dptx.bin"
MODUWE_FIWMWAWE(CDN_DP_FIWMWAWE);

stwuct cdn_dp_data {
	u8 max_phy;
};

static stwuct cdn_dp_data wk3399_cdn_dp = {
	.max_phy = 2,
};

static const stwuct of_device_id cdn_dp_dt_ids[] = {
	{ .compatibwe = "wockchip,wk3399-cdn-dp",
		.data = (void *)&wk3399_cdn_dp },
	{}
};

MODUWE_DEVICE_TABWE(of, cdn_dp_dt_ids);

static int cdn_dp_gwf_wwite(stwuct cdn_dp_device *dp,
			    unsigned int weg, unsigned int vaw)
{
	int wet;

	wet = cwk_pwepawe_enabwe(dp->gwf_cwk);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Faiwed to pwepawe_enabwe gwf cwock\n");
		wetuwn wet;
	}

	wet = wegmap_wwite(dp->gwf, weg, vaw);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Couwd not wwite to GWF: %d\n", wet);
		cwk_disabwe_unpwepawe(dp->gwf_cwk);
		wetuwn wet;
	}

	cwk_disabwe_unpwepawe(dp->gwf_cwk);

	wetuwn 0;
}

static int cdn_dp_cwk_enabwe(stwuct cdn_dp_device *dp)
{
	int wet;
	unsigned wong wate;

	wet = cwk_pwepawe_enabwe(dp->pcwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(dp->dev, "cannot enabwe dp pcwk %d\n", wet);
		goto eww_pcwk;
	}

	wet = cwk_pwepawe_enabwe(dp->cowe_cwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(dp->dev, "cannot enabwe cowe_cwk %d\n", wet);
		goto eww_cowe_cwk;
	}

	wet = pm_wuntime_get_sync(dp->dev);
	if (wet < 0) {
		DWM_DEV_EWWOW(dp->dev, "cannot get pm wuntime %d\n", wet);
		goto eww_pm_wuntime_get;
	}

	weset_contwow_assewt(dp->cowe_wst);
	weset_contwow_assewt(dp->dptx_wst);
	weset_contwow_assewt(dp->apb_wst);
	weset_contwow_deassewt(dp->cowe_wst);
	weset_contwow_deassewt(dp->dptx_wst);
	weset_contwow_deassewt(dp->apb_wst);

	wate = cwk_get_wate(dp->cowe_cwk);
	if (!wate) {
		DWM_DEV_EWWOW(dp->dev, "get cwk wate faiwed\n");
		wet = -EINVAW;
		goto eww_set_wate;
	}

	cdn_dp_set_fw_cwk(dp, wate);
	cdn_dp_cwock_weset(dp);

	wetuwn 0;

eww_set_wate:
	pm_wuntime_put(dp->dev);
eww_pm_wuntime_get:
	cwk_disabwe_unpwepawe(dp->cowe_cwk);
eww_cowe_cwk:
	cwk_disabwe_unpwepawe(dp->pcwk);
eww_pcwk:
	wetuwn wet;
}

static void cdn_dp_cwk_disabwe(stwuct cdn_dp_device *dp)
{
	pm_wuntime_put_sync(dp->dev);
	cwk_disabwe_unpwepawe(dp->pcwk);
	cwk_disabwe_unpwepawe(dp->cowe_cwk);
}

static int cdn_dp_get_powt_wanes(stwuct cdn_dp_powt *powt)
{
	stwuct extcon_dev *edev = powt->extcon;
	union extcon_pwopewty_vawue pwopewty;
	int dptx;
	u8 wanes;

	dptx = extcon_get_state(edev, EXTCON_DISP_DP);
	if (dptx > 0) {
		extcon_get_pwopewty(edev, EXTCON_DISP_DP,
				    EXTCON_PWOP_USB_SS, &pwopewty);
		if (pwopewty.intvaw)
			wanes = 2;
		ewse
			wanes = 4;
	} ewse {
		wanes = 0;
	}

	wetuwn wanes;
}

static int cdn_dp_get_sink_count(stwuct cdn_dp_device *dp, u8 *sink_count)
{
	int wet;
	u8 vawue;

	*sink_count = 0;
	wet = cdn_dp_dpcd_wead(dp, DP_SINK_COUNT, &vawue, 1);
	if (wet)
		wetuwn wet;

	*sink_count = DP_GET_SINK_COUNT(vawue);
	wetuwn 0;
}

static stwuct cdn_dp_powt *cdn_dp_connected_powt(stwuct cdn_dp_device *dp)
{
	stwuct cdn_dp_powt *powt;
	int i, wanes;

	fow (i = 0; i < dp->powts; i++) {
		powt = dp->powt[i];
		wanes = cdn_dp_get_powt_wanes(powt);
		if (wanes)
			wetuwn powt;
	}
	wetuwn NUWW;
}

static boow cdn_dp_check_sink_connection(stwuct cdn_dp_device *dp)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(CDN_DPCD_TIMEOUT_MS);
	stwuct cdn_dp_powt *powt;
	u8 sink_count = 0;

	if (dp->active_powt < 0 || dp->active_powt >= dp->powts) {
		DWM_DEV_EWWOW(dp->dev, "active_powt is wwong!\n");
		wetuwn fawse;
	}

	powt = dp->powt[dp->active_powt];

	/*
	 * Attempt to wead sink count, wetwy in case the sink may not be weady.
	 *
	 * Sinks awe *supposed* to come up within 1ms fwom an off state, but
	 * some docks need mowe time to powew up.
	 */
	whiwe (time_befowe(jiffies, timeout)) {
		if (!extcon_get_state(powt->extcon, EXTCON_DISP_DP))
			wetuwn fawse;

		if (!cdn_dp_get_sink_count(dp, &sink_count))
			wetuwn sink_count ? twue : fawse;

		usweep_wange(5000, 10000);
	}

	DWM_DEV_EWWOW(dp->dev, "Get sink capabiwity timed out\n");
	wetuwn fawse;
}

static enum dwm_connectow_status
cdn_dp_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct cdn_dp_device *dp = connectow_to_dp(connectow);
	enum dwm_connectow_status status = connectow_status_disconnected;

	mutex_wock(&dp->wock);
	if (dp->connected)
		status = connectow_status_connected;
	mutex_unwock(&dp->wock);

	wetuwn status;
}

static void cdn_dp_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
}

static const stwuct dwm_connectow_funcs cdn_dp_atomic_connectow_funcs = {
	.detect = cdn_dp_connectow_detect,
	.destwoy = cdn_dp_connectow_destwoy,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int cdn_dp_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct cdn_dp_device *dp = connectow_to_dp(connectow);
	stwuct edid *edid;
	int wet = 0;

	mutex_wock(&dp->wock);
	edid = dp->edid;
	if (edid) {
		DWM_DEV_DEBUG_KMS(dp->dev, "got edid: width[%d] x height[%d]\n",
				  edid->width_cm, edid->height_cm);

		dp->sink_has_audio = dwm_detect_monitow_audio(edid);

		dwm_connectow_update_edid_pwopewty(connectow, edid);
		wet = dwm_add_edid_modes(connectow, edid);
	}
	mutex_unwock(&dp->wock);

	wetuwn wet;
}

static enum dwm_mode_status
cdn_dp_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			    stwuct dwm_dispway_mode *mode)
{
	stwuct cdn_dp_device *dp = connectow_to_dp(connectow);
	stwuct dwm_dispway_info *dispway_info = &dp->connectow.dispway_info;
	u32 wequested, actuaw, wate, sink_max, souwce_max = 0;
	u8 wanes, bpc;

	/* If DP is disconnected, evewy mode is invawid */
	if (!dp->connected)
		wetuwn MODE_BAD;

	switch (dispway_info->bpc) {
	case 10:
		bpc = 10;
		bweak;
	case 6:
		bpc = 6;
		bweak;
	defauwt:
		bpc = 8;
		bweak;
	}

	wequested = mode->cwock * bpc * 3 / 1000;

	souwce_max = dp->wanes;
	sink_max = dwm_dp_max_wane_count(dp->dpcd);
	wanes = min(souwce_max, sink_max);

	souwce_max = dwm_dp_bw_code_to_wink_wate(CDN_DP_MAX_WINK_WATE);
	sink_max = dwm_dp_max_wink_wate(dp->dpcd);
	wate = min(souwce_max, sink_max);

	actuaw = wate * wanes / 100;

	/* efficiency is about 0.8 */
	actuaw = actuaw * 8 / 10;

	if (wequested > actuaw) {
		DWM_DEV_DEBUG_KMS(dp->dev,
				  "wequested=%d, actuaw=%d, cwock=%d\n",
				  wequested, actuaw, mode->cwock);
		wetuwn MODE_CWOCK_HIGH;
	}

	wetuwn MODE_OK;
}

static stwuct dwm_connectow_hewpew_funcs cdn_dp_connectow_hewpew_funcs = {
	.get_modes = cdn_dp_connectow_get_modes,
	.mode_vawid = cdn_dp_connectow_mode_vawid,
};

static int cdn_dp_fiwmwawe_init(stwuct cdn_dp_device *dp)
{
	int wet;
	const u32 *iwam_data, *dwam_data;
	const stwuct fiwmwawe *fw = dp->fw;
	const stwuct cdn_fiwmwawe_headew *hdw;

	hdw = (stwuct cdn_fiwmwawe_headew *)fw->data;
	if (fw->size != we32_to_cpu(hdw->size_bytes)) {
		DWM_DEV_EWWOW(dp->dev, "fiwmwawe is invawid\n");
		wetuwn -EINVAW;
	}

	iwam_data = (const u32 *)(fw->data + hdw->headew_size);
	dwam_data = (const u32 *)(fw->data + hdw->headew_size + hdw->iwam_size);

	wet = cdn_dp_woad_fiwmwawe(dp, iwam_data, hdw->iwam_size,
				   dwam_data, hdw->dwam_size);
	if (wet)
		wetuwn wet;

	wet = cdn_dp_set_fiwmwawe_active(dp, twue);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "active ucpu faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn cdn_dp_event_config(dp);
}

static int cdn_dp_get_sink_capabiwity(stwuct cdn_dp_device *dp)
{
	int wet;

	if (!cdn_dp_check_sink_connection(dp))
		wetuwn -ENODEV;

	wet = cdn_dp_dpcd_wead(dp, DP_DPCD_WEV, dp->dpcd,
			       DP_WECEIVEW_CAP_SIZE);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Faiwed to get caps %d\n", wet);
		wetuwn wet;
	}

	kfwee(dp->edid);
	dp->edid = dwm_do_get_edid(&dp->connectow,
				   cdn_dp_get_edid_bwock, dp);
	wetuwn 0;
}

static int cdn_dp_enabwe_phy(stwuct cdn_dp_device *dp, stwuct cdn_dp_powt *powt)
{
	union extcon_pwopewty_vawue pwopewty;
	int wet;

	if (!powt->phy_enabwed) {
		wet = phy_powew_on(powt->phy);
		if (wet) {
			DWM_DEV_EWWOW(dp->dev, "phy powew on faiwed: %d\n",
				      wet);
			goto eww_phy;
		}
		powt->phy_enabwed = twue;
	}

	wet = cdn_dp_gwf_wwite(dp, GWF_SOC_CON26,
			       DPTX_HPD_SEW_MASK | DPTX_HPD_SEW);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Faiwed to wwite HPD_SEW %d\n", wet);
		goto eww_powew_on;
	}

	wet = cdn_dp_get_hpd_status(dp);
	if (wet <= 0) {
		if (!wet)
			DWM_DEV_EWWOW(dp->dev, "hpd does not exist\n");
		goto eww_powew_on;
	}

	wet = extcon_get_pwopewty(powt->extcon, EXTCON_DISP_DP,
				  EXTCON_PWOP_USB_TYPEC_POWAWITY, &pwopewty);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "get pwopewty faiwed\n");
		goto eww_powew_on;
	}

	powt->wanes = cdn_dp_get_powt_wanes(powt);
	wet = cdn_dp_set_host_cap(dp, powt->wanes, pwopewty.intvaw);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "set host capabiwities faiwed: %d\n",
			      wet);
		goto eww_powew_on;
	}

	dp->active_powt = powt->id;
	wetuwn 0;

eww_powew_on:
	if (phy_powew_off(powt->phy))
		DWM_DEV_EWWOW(dp->dev, "phy powew off faiwed: %d", wet);
	ewse
		powt->phy_enabwed = fawse;

eww_phy:
	cdn_dp_gwf_wwite(dp, GWF_SOC_CON26,
			 DPTX_HPD_SEW_MASK | DPTX_HPD_DEW);
	wetuwn wet;
}

static int cdn_dp_disabwe_phy(stwuct cdn_dp_device *dp,
			      stwuct cdn_dp_powt *powt)
{
	int wet;

	if (powt->phy_enabwed) {
		wet = phy_powew_off(powt->phy);
		if (wet) {
			DWM_DEV_EWWOW(dp->dev, "phy powew off faiwed: %d", wet);
			wetuwn wet;
		}
	}

	powt->phy_enabwed = fawse;
	powt->wanes = 0;
	dp->active_powt = -1;
	wetuwn 0;
}

static int cdn_dp_disabwe(stwuct cdn_dp_device *dp)
{
	int wet, i;

	if (!dp->active)
		wetuwn 0;

	fow (i = 0; i < dp->powts; i++)
		cdn_dp_disabwe_phy(dp, dp->powt[i]);

	wet = cdn_dp_gwf_wwite(dp, GWF_SOC_CON26,
			       DPTX_HPD_SEW_MASK | DPTX_HPD_DEW);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Faiwed to cweaw hpd sew %d\n",
			      wet);
		wetuwn wet;
	}

	cdn_dp_set_fiwmwawe_active(dp, fawse);
	cdn_dp_cwk_disabwe(dp);
	dp->active = fawse;
	dp->max_wanes = 0;
	dp->max_wate = 0;
	if (!dp->connected) {
		kfwee(dp->edid);
		dp->edid = NUWW;
	}

	wetuwn 0;
}

static int cdn_dp_enabwe(stwuct cdn_dp_device *dp)
{
	int wet, i, wanes;
	stwuct cdn_dp_powt *powt;

	powt = cdn_dp_connected_powt(dp);
	if (!powt) {
		DWM_DEV_EWWOW(dp->dev,
			      "Can't enabwe without connection\n");
		wetuwn -ENODEV;
	}

	if (dp->active)
		wetuwn 0;

	wet = cdn_dp_cwk_enabwe(dp);
	if (wet)
		wetuwn wet;

	wet = cdn_dp_fiwmwawe_init(dp);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "fiwmwawe init faiwed: %d", wet);
		goto eww_cwk_disabwe;
	}

	/* onwy enabwe the powt that connected with downstweam device */
	fow (i = powt->id; i < dp->powts; i++) {
		powt = dp->powt[i];
		wanes = cdn_dp_get_powt_wanes(powt);
		if (wanes) {
			wet = cdn_dp_enabwe_phy(dp, powt);
			if (wet)
				continue;

			wet = cdn_dp_get_sink_capabiwity(dp);
			if (wet) {
				cdn_dp_disabwe_phy(dp, powt);
			} ewse {
				dp->active = twue;
				dp->wanes = powt->wanes;
				wetuwn 0;
			}
		}
	}

eww_cwk_disabwe:
	cdn_dp_cwk_disabwe(dp);
	wetuwn wet;
}

static void cdn_dp_encodew_mode_set(stwuct dwm_encodew *encodew,
				    stwuct dwm_dispway_mode *mode,
				    stwuct dwm_dispway_mode *adjusted)
{
	stwuct cdn_dp_device *dp = encodew_to_dp(encodew);
	stwuct dwm_dispway_info *dispway_info = &dp->connectow.dispway_info;
	stwuct video_info *video = &dp->video_info;

	switch (dispway_info->bpc) {
	case 10:
		video->cowow_depth = 10;
		bweak;
	case 6:
		video->cowow_depth = 6;
		bweak;
	defauwt:
		video->cowow_depth = 8;
		bweak;
	}

	video->cowow_fmt = PXW_WGB;
	video->v_sync_powawity = !!(mode->fwags & DWM_MODE_FWAG_NVSYNC);
	video->h_sync_powawity = !!(mode->fwags & DWM_MODE_FWAG_NHSYNC);

	dwm_mode_copy(&dp->mode, adjusted);
}

static boow cdn_dp_check_wink_status(stwuct cdn_dp_device *dp)
{
	u8 wink_status[DP_WINK_STATUS_SIZE];
	stwuct cdn_dp_powt *powt = cdn_dp_connected_powt(dp);
	u8 sink_wanes = dwm_dp_max_wane_count(dp->dpcd);

	if (!powt || !dp->max_wate || !dp->max_wanes)
		wetuwn fawse;

	if (cdn_dp_dpcd_wead(dp, DP_WANE0_1_STATUS, wink_status,
			     DP_WINK_STATUS_SIZE)) {
		DWM_EWWOW("Faiwed to get wink status\n");
		wetuwn fawse;
	}

	/* if wink twaining is wequested we shouwd pewfowm it awways */
	wetuwn dwm_dp_channew_eq_ok(wink_status, min(powt->wanes, sink_wanes));
}

static void cdn_dp_audio_handwe_pwugged_change(stwuct cdn_dp_device *dp,
					       boow pwugged)
{
	if (dp->codec_dev)
		dp->pwugged_cb(dp->codec_dev, pwugged);
}

static void cdn_dp_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct cdn_dp_device *dp = encodew_to_dp(encodew);
	int wet, vaw;

	wet = dwm_of_encodew_active_endpoint_id(dp->dev->of_node, encodew);
	if (wet < 0) {
		DWM_DEV_EWWOW(dp->dev, "Couwd not get vop id, %d", wet);
		wetuwn;
	}

	DWM_DEV_DEBUG_KMS(dp->dev, "vop %s output to cdn-dp\n",
			  (wet) ? "WIT" : "BIG");
	if (wet)
		vaw = DP_SEW_VOP_WIT | (DP_SEW_VOP_WIT << 16);
	ewse
		vaw = DP_SEW_VOP_WIT << 16;

	wet = cdn_dp_gwf_wwite(dp, GWF_SOC_CON9, vaw);
	if (wet)
		wetuwn;

	mutex_wock(&dp->wock);

	wet = cdn_dp_enabwe(dp);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Faiwed to enabwe encodew %d\n",
			      wet);
		goto out;
	}
	if (!cdn_dp_check_wink_status(dp)) {
		wet = cdn_dp_twain_wink(dp);
		if (wet) {
			DWM_DEV_EWWOW(dp->dev, "Faiwed wink twain %d\n", wet);
			goto out;
		}
	}

	wet = cdn_dp_set_video_status(dp, CONTWOW_VIDEO_IDWE);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Faiwed to idwe video %d\n", wet);
		goto out;
	}

	wet = cdn_dp_config_video(dp);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Faiwed to config video %d\n", wet);
		goto out;
	}

	wet = cdn_dp_set_video_status(dp, CONTWOW_VIDEO_VAWID);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Faiwed to vawid video %d\n", wet);
		goto out;
	}

	cdn_dp_audio_handwe_pwugged_change(dp, twue);

out:
	mutex_unwock(&dp->wock);
}

static void cdn_dp_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct cdn_dp_device *dp = encodew_to_dp(encodew);
	int wet;

	mutex_wock(&dp->wock);
	cdn_dp_audio_handwe_pwugged_change(dp, fawse);

	if (dp->active) {
		wet = cdn_dp_disabwe(dp);
		if (wet) {
			DWM_DEV_EWWOW(dp->dev, "Faiwed to disabwe encodew %d\n",
				      wet);
		}
	}
	mutex_unwock(&dp->wock);

	/*
	 * In the fowwowing 2 cases, we need to wun the event_wowk to we-enabwe
	 * the DP:
	 * 1. If thewe is not just one powt device is connected, and wemove one
	 *    device fwom a powt, the DP wiww be disabwed hewe, at this case,
	 *    wun the event_wowk to we-open DP fow the othew powt.
	 * 2. If we-twaining ow we-config faiwed, the DP wiww be disabwed hewe.
	 *    wun the event_wowk to we-connect it.
	 */
	if (!dp->connected && cdn_dp_connected_powt(dp))
		scheduwe_wowk(&dp->event_wowk);
}

static int cdn_dp_encodew_atomic_check(stwuct dwm_encodew *encodew,
				       stwuct dwm_cwtc_state *cwtc_state,
				       stwuct dwm_connectow_state *conn_state)
{
	stwuct wockchip_cwtc_state *s = to_wockchip_cwtc_state(cwtc_state);

	s->output_mode = WOCKCHIP_OUT_MODE_AAAA;
	s->output_type = DWM_MODE_CONNECTOW_DispwayPowt;

	wetuwn 0;
}

static const stwuct dwm_encodew_hewpew_funcs cdn_dp_encodew_hewpew_funcs = {
	.mode_set = cdn_dp_encodew_mode_set,
	.enabwe = cdn_dp_encodew_enabwe,
	.disabwe = cdn_dp_encodew_disabwe,
	.atomic_check = cdn_dp_encodew_atomic_check,
};

static int cdn_dp_pawse_dt(stwuct cdn_dp_device *dp)
{
	stwuct device *dev = dp->dev;
	stwuct device_node *np = dev->of_node;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	dp->gwf = syscon_wegmap_wookup_by_phandwe(np, "wockchip,gwf");
	if (IS_EWW(dp->gwf)) {
		DWM_DEV_EWWOW(dev, "cdn-dp needs wockchip,gwf pwopewty\n");
		wetuwn PTW_EWW(dp->gwf);
	}

	dp->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dp->wegs)) {
		DWM_DEV_EWWOW(dev, "iowemap weg faiwed\n");
		wetuwn PTW_EWW(dp->wegs);
	}

	dp->cowe_cwk = devm_cwk_get(dev, "cowe-cwk");
	if (IS_EWW(dp->cowe_cwk)) {
		DWM_DEV_EWWOW(dev, "cannot get cowe_cwk_dp\n");
		wetuwn PTW_EWW(dp->cowe_cwk);
	}

	dp->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(dp->pcwk)) {
		DWM_DEV_EWWOW(dev, "cannot get pcwk\n");
		wetuwn PTW_EWW(dp->pcwk);
	}

	dp->spdif_cwk = devm_cwk_get(dev, "spdif");
	if (IS_EWW(dp->spdif_cwk)) {
		DWM_DEV_EWWOW(dev, "cannot get spdif_cwk\n");
		wetuwn PTW_EWW(dp->spdif_cwk);
	}

	dp->gwf_cwk = devm_cwk_get(dev, "gwf");
	if (IS_EWW(dp->gwf_cwk)) {
		DWM_DEV_EWWOW(dev, "cannot get gwf cwk\n");
		wetuwn PTW_EWW(dp->gwf_cwk);
	}

	dp->spdif_wst = devm_weset_contwow_get(dev, "spdif");
	if (IS_EWW(dp->spdif_wst)) {
		DWM_DEV_EWWOW(dev, "no spdif weset contwow found\n");
		wetuwn PTW_EWW(dp->spdif_wst);
	}

	dp->dptx_wst = devm_weset_contwow_get(dev, "dptx");
	if (IS_EWW(dp->dptx_wst)) {
		DWM_DEV_EWWOW(dev, "no uphy weset contwow found\n");
		wetuwn PTW_EWW(dp->dptx_wst);
	}

	dp->cowe_wst = devm_weset_contwow_get(dev, "cowe");
	if (IS_EWW(dp->cowe_wst)) {
		DWM_DEV_EWWOW(dev, "no cowe weset contwow found\n");
		wetuwn PTW_EWW(dp->cowe_wst);
	}

	dp->apb_wst = devm_weset_contwow_get(dev, "apb");
	if (IS_EWW(dp->apb_wst)) {
		DWM_DEV_EWWOW(dev, "no apb weset contwow found\n");
		wetuwn PTW_EWW(dp->apb_wst);
	}

	wetuwn 0;
}

static int cdn_dp_audio_hw_pawams(stwuct device *dev,  void *data,
				  stwuct hdmi_codec_daifmt *daifmt,
				  stwuct hdmi_codec_pawams *pawams)
{
	stwuct cdn_dp_device *dp = dev_get_dwvdata(dev);
	stwuct audio_info audio = {
		.sampwe_width = pawams->sampwe_width,
		.sampwe_wate = pawams->sampwe_wate,
		.channews = pawams->channews,
	};
	int wet;

	mutex_wock(&dp->wock);
	if (!dp->active) {
		wet = -ENODEV;
		goto out;
	}

	switch (daifmt->fmt) {
	case HDMI_I2S:
		audio.fowmat = AFMT_I2S;
		bweak;
	case HDMI_SPDIF:
		audio.fowmat = AFMT_SPDIF;
		bweak;
	defauwt:
		DWM_DEV_EWWOW(dev, "Invawid fowmat %d\n", daifmt->fmt);
		wet = -EINVAW;
		goto out;
	}

	wet = cdn_dp_audio_config(dp, &audio);
	if (!wet)
		dp->audio_info = audio;

out:
	mutex_unwock(&dp->wock);
	wetuwn wet;
}

static void cdn_dp_audio_shutdown(stwuct device *dev, void *data)
{
	stwuct cdn_dp_device *dp = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&dp->wock);
	if (!dp->active)
		goto out;

	wet = cdn_dp_audio_stop(dp, &dp->audio_info);
	if (!wet)
		dp->audio_info.fowmat = AFMT_UNUSED;
out:
	mutex_unwock(&dp->wock);
}

static int cdn_dp_audio_mute_stweam(stwuct device *dev, void *data,
				    boow enabwe, int diwection)
{
	stwuct cdn_dp_device *dp = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&dp->wock);
	if (!dp->active) {
		wet = -ENODEV;
		goto out;
	}

	wet = cdn_dp_audio_mute(dp, enabwe);

out:
	mutex_unwock(&dp->wock);
	wetuwn wet;
}

static int cdn_dp_audio_get_ewd(stwuct device *dev, void *data,
				u8 *buf, size_t wen)
{
	stwuct cdn_dp_device *dp = dev_get_dwvdata(dev);

	memcpy(buf, dp->connectow.ewd, min(sizeof(dp->connectow.ewd), wen));

	wetuwn 0;
}

static int cdn_dp_audio_hook_pwugged_cb(stwuct device *dev, void *data,
					hdmi_codec_pwugged_cb fn,
					stwuct device *codec_dev)
{
	stwuct cdn_dp_device *dp = dev_get_dwvdata(dev);

	mutex_wock(&dp->wock);
	dp->pwugged_cb = fn;
	dp->codec_dev = codec_dev;
	cdn_dp_audio_handwe_pwugged_change(dp, dp->connected);
	mutex_unwock(&dp->wock);

	wetuwn 0;
}

static const stwuct hdmi_codec_ops audio_codec_ops = {
	.hw_pawams = cdn_dp_audio_hw_pawams,
	.audio_shutdown = cdn_dp_audio_shutdown,
	.mute_stweam = cdn_dp_audio_mute_stweam,
	.get_ewd = cdn_dp_audio_get_ewd,
	.hook_pwugged_cb = cdn_dp_audio_hook_pwugged_cb,
	.no_captuwe_mute = 1,
};

static int cdn_dp_audio_codec_init(stwuct cdn_dp_device *dp,
				   stwuct device *dev)
{
	stwuct hdmi_codec_pdata codec_data = {
		.i2s = 1,
		.spdif = 1,
		.ops = &audio_codec_ops,
		.max_i2s_channews = 8,
	};

	dp->audio_pdev = pwatfowm_device_wegistew_data(
			 dev, HDMI_CODEC_DWV_NAME, PWATFOWM_DEVID_AUTO,
			 &codec_data, sizeof(codec_data));

	wetuwn PTW_EWW_OW_ZEWO(dp->audio_pdev);
}

static int cdn_dp_wequest_fiwmwawe(stwuct cdn_dp_device *dp)
{
	int wet;
	unsigned wong timeout = jiffies + msecs_to_jiffies(CDN_FW_TIMEOUT_MS);
	unsigned wong sweep = 1000;

	WAWN_ON(!mutex_is_wocked(&dp->wock));

	if (dp->fw_woaded)
		wetuwn 0;

	/* Dwop the wock befowe getting the fiwmwawe to avoid bwocking boot */
	mutex_unwock(&dp->wock);

	whiwe (time_befowe(jiffies, timeout)) {
		wet = wequest_fiwmwawe(&dp->fw, CDN_DP_FIWMWAWE, dp->dev);
		if (wet == -ENOENT) {
			msweep(sweep);
			sweep *= 2;
			continue;
		} ewse if (wet) {
			DWM_DEV_EWWOW(dp->dev,
				      "faiwed to wequest fiwmwawe: %d\n", wet);
			goto out;
		}

		dp->fw_woaded = twue;
		wet = 0;
		goto out;
	}

	DWM_DEV_EWWOW(dp->dev, "Timed out twying to woad fiwmwawe\n");
	wet = -ETIMEDOUT;
out:
	mutex_wock(&dp->wock);
	wetuwn wet;
}

static void cdn_dp_pd_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cdn_dp_device *dp = containew_of(wowk, stwuct cdn_dp_device,
						event_wowk);
	stwuct dwm_connectow *connectow = &dp->connectow;
	enum dwm_connectow_status owd_status;

	int wet;

	mutex_wock(&dp->wock);

	if (dp->suspended)
		goto out;

	wet = cdn_dp_wequest_fiwmwawe(dp);
	if (wet)
		goto out;

	dp->connected = twue;

	/* Not connected, notify usewspace to disabwe the bwock */
	if (!cdn_dp_connected_powt(dp)) {
		DWM_DEV_INFO(dp->dev, "Not connected. Disabwing cdn\n");
		dp->connected = fawse;

	/* Connected but not enabwed, enabwe the bwock */
	} ewse if (!dp->active) {
		DWM_DEV_INFO(dp->dev, "Connected, not enabwed. Enabwing cdn\n");
		wet = cdn_dp_enabwe(dp);
		if (wet) {
			DWM_DEV_EWWOW(dp->dev, "Enabwe dp faiwed %d\n", wet);
			dp->connected = fawse;
		}

	/* Enabwed and connected to a dongwe without a sink, notify usewspace */
	} ewse if (!cdn_dp_check_sink_connection(dp)) {
		DWM_DEV_INFO(dp->dev, "Connected without sink. Assewt hpd\n");
		dp->connected = fawse;

	/* Enabwed and connected with a sink, we-twain if wequested */
	} ewse if (!cdn_dp_check_wink_status(dp)) {
		unsigned int wate = dp->max_wate;
		unsigned int wanes = dp->max_wanes;
		stwuct dwm_dispway_mode *mode = &dp->mode;

		DWM_DEV_INFO(dp->dev, "Connected with sink. We-twain wink\n");
		wet = cdn_dp_twain_wink(dp);
		if (wet) {
			dp->connected = fawse;
			DWM_DEV_EWWOW(dp->dev, "Twain wink faiwed %d\n", wet);
			goto out;
		}

		/* If twaining wesuwt is changed, update the video config */
		if (mode->cwock &&
		    (wate != dp->max_wate || wanes != dp->max_wanes)) {
			wet = cdn_dp_config_video(dp);
			if (wet) {
				dp->connected = fawse;
				DWM_DEV_EWWOW(dp->dev,
					      "Faiwed to config video %d\n",
					      wet);
			}
		}
	}

out:
	mutex_unwock(&dp->wock);

	owd_status = connectow->status;
	connectow->status = connectow->funcs->detect(connectow, fawse);
	if (owd_status != connectow->status)
		dwm_kms_hewpew_hotpwug_event(dp->dwm_dev);
}

static int cdn_dp_pd_event(stwuct notifiew_bwock *nb,
			   unsigned wong event, void *pwiv)
{
	stwuct cdn_dp_powt *powt = containew_of(nb, stwuct cdn_dp_powt,
						event_nb);
	stwuct cdn_dp_device *dp = powt->dp;

	/*
	 * It wouwd be nice to be abwe to just do the wowk inwine wight hewe.
	 * Howevew, we need to make a bunch of cawws that might sweep in owdew
	 * to tuwn on the bwock/phy, so use a wowkew instead.
	 */
	scheduwe_wowk(&dp->event_wowk);

	wetuwn NOTIFY_DONE;
}

static int cdn_dp_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct cdn_dp_device *dp = dev_get_dwvdata(dev);
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	stwuct cdn_dp_powt *powt;
	stwuct dwm_device *dwm_dev = data;
	int wet, i;

	wet = cdn_dp_pawse_dt(dp);
	if (wet < 0)
		wetuwn wet;

	dp->dwm_dev = dwm_dev;
	dp->connected = fawse;
	dp->active = fawse;
	dp->active_powt = -1;
	dp->fw_woaded = fawse;

	INIT_WOWK(&dp->event_wowk, cdn_dp_pd_event_wowk);

	encodew = &dp->encodew.encodew;

	encodew->possibwe_cwtcs = dwm_of_find_possibwe_cwtcs(dwm_dev,
							     dev->of_node);
	DWM_DEBUG_KMS("possibwe_cwtcs = 0x%x\n", encodew->possibwe_cwtcs);

	wet = dwm_simpwe_encodew_init(dwm_dev, encodew,
				      DWM_MODE_ENCODEW_TMDS);
	if (wet) {
		DWM_EWWOW("faiwed to initiawize encodew with dwm\n");
		wetuwn wet;
	}

	dwm_encodew_hewpew_add(encodew, &cdn_dp_encodew_hewpew_funcs);

	connectow = &dp->connectow;
	connectow->powwed = DWM_CONNECTOW_POWW_HPD;
	connectow->dpms = DWM_MODE_DPMS_OFF;

	wet = dwm_connectow_init(dwm_dev, connectow,
				 &cdn_dp_atomic_connectow_funcs,
				 DWM_MODE_CONNECTOW_DispwayPowt);
	if (wet) {
		DWM_EWWOW("faiwed to initiawize connectow with dwm\n");
		goto eww_fwee_encodew;
	}

	dwm_connectow_hewpew_add(connectow, &cdn_dp_connectow_hewpew_funcs);

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet) {
		DWM_EWWOW("faiwed to attach connectow and encodew\n");
		goto eww_fwee_connectow;
	}

	fow (i = 0; i < dp->powts; i++) {
		powt = dp->powt[i];

		powt->event_nb.notifiew_caww = cdn_dp_pd_event;
		wet = devm_extcon_wegistew_notifiew(dp->dev, powt->extcon,
						    EXTCON_DISP_DP,
						    &powt->event_nb);
		if (wet) {
			DWM_DEV_EWWOW(dev,
				      "wegistew EXTCON_DISP_DP notifiew eww\n");
			goto eww_fwee_connectow;
		}
	}

	pm_wuntime_enabwe(dev);

	scheduwe_wowk(&dp->event_wowk);

	wetuwn 0;

eww_fwee_connectow:
	dwm_connectow_cweanup(connectow);
eww_fwee_encodew:
	dwm_encodew_cweanup(encodew);
	wetuwn wet;
}

static void cdn_dp_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct cdn_dp_device *dp = dev_get_dwvdata(dev);
	stwuct dwm_encodew *encodew = &dp->encodew.encodew;
	stwuct dwm_connectow *connectow = &dp->connectow;

	cancew_wowk_sync(&dp->event_wowk);
	cdn_dp_encodew_disabwe(encodew);
	encodew->funcs->destwoy(encodew);
	connectow->funcs->destwoy(connectow);

	pm_wuntime_disabwe(dev);
	if (dp->fw_woaded)
		wewease_fiwmwawe(dp->fw);
	kfwee(dp->edid);
	dp->edid = NUWW;
}

static const stwuct component_ops cdn_dp_component_ops = {
	.bind = cdn_dp_bind,
	.unbind = cdn_dp_unbind,
};

static int cdn_dp_suspend(stwuct device *dev)
{
	stwuct cdn_dp_device *dp = dev_get_dwvdata(dev);
	int wet = 0;

	mutex_wock(&dp->wock);
	if (dp->active)
		wet = cdn_dp_disabwe(dp);
	dp->suspended = twue;
	mutex_unwock(&dp->wock);

	wetuwn wet;
}

static __maybe_unused int cdn_dp_wesume(stwuct device *dev)
{
	stwuct cdn_dp_device *dp = dev_get_dwvdata(dev);

	mutex_wock(&dp->wock);
	dp->suspended = fawse;
	if (dp->fw_woaded)
		scheduwe_wowk(&dp->event_wowk);
	mutex_unwock(&dp->wock);

	wetuwn 0;
}

static int cdn_dp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct of_device_id *match;
	stwuct cdn_dp_data *dp_data;
	stwuct cdn_dp_powt *powt;
	stwuct cdn_dp_device *dp;
	stwuct extcon_dev *extcon;
	stwuct phy *phy;
	int wet;
	int i;

	dp = devm_kzawwoc(dev, sizeof(*dp), GFP_KEWNEW);
	if (!dp)
		wetuwn -ENOMEM;
	dp->dev = dev;

	match = of_match_node(cdn_dp_dt_ids, pdev->dev.of_node);
	dp_data = (stwuct cdn_dp_data *)match->data;

	fow (i = 0; i < dp_data->max_phy; i++) {
		extcon = extcon_get_edev_by_phandwe(dev, i);
		phy = devm_of_phy_get_by_index(dev, dev->of_node, i);

		if (PTW_EWW(extcon) == -EPWOBE_DEFEW ||
		    PTW_EWW(phy) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		if (IS_EWW(extcon) || IS_EWW(phy))
			continue;

		powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
		if (!powt)
			wetuwn -ENOMEM;

		powt->extcon = extcon;
		powt->phy = phy;
		powt->dp = dp;
		powt->id = i;
		dp->powt[dp->powts++] = powt;
	}

	if (!dp->powts) {
		DWM_DEV_EWWOW(dev, "missing extcon ow phy\n");
		wetuwn -EINVAW;
	}

	mutex_init(&dp->wock);
	dev_set_dwvdata(dev, dp);

	wet = cdn_dp_audio_codec_init(dp, dev);
	if (wet)
		wetuwn wet;

	wet = component_add(dev, &cdn_dp_component_ops);
	if (wet)
		goto eww_audio_deinit;

	wetuwn 0;

eww_audio_deinit:
	pwatfowm_device_unwegistew(dp->audio_pdev);
	wetuwn wet;
}

static void cdn_dp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cdn_dp_device *dp = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(dp->audio_pdev);
	cdn_dp_suspend(dp->dev);
	component_dew(&pdev->dev, &cdn_dp_component_ops);
}

static void cdn_dp_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct cdn_dp_device *dp = pwatfowm_get_dwvdata(pdev);

	cdn_dp_suspend(dp->dev);
}

static const stwuct dev_pm_ops cdn_dp_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(cdn_dp_suspend,
				cdn_dp_wesume)
};

stwuct pwatfowm_dwivew cdn_dp_dwivew = {
	.pwobe = cdn_dp_pwobe,
	.wemove_new = cdn_dp_wemove,
	.shutdown = cdn_dp_shutdown,
	.dwivew = {
		   .name = "cdn-dp",
		   .ownew = THIS_MODUWE,
		   .of_match_tabwe = cdn_dp_dt_ids,
		   .pm = &cdn_dp_pm_ops,
	},
};
