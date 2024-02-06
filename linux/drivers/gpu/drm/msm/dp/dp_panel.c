// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude "dp_panew.h"

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwint.h>

stwuct dp_panew_pwivate {
	stwuct device *dev;
	stwuct dwm_device *dwm_dev;
	stwuct dp_panew dp_panew;
	stwuct dwm_dp_aux *aux;
	stwuct dp_wink *wink;
	stwuct dp_catawog *catawog;
	boow panew_on;
};

static void dp_panew_wead_psw_cap(stwuct dp_panew_pwivate *panew)
{
	ssize_t wwen;
	stwuct dp_panew *dp_panew;

	dp_panew = &panew->dp_panew;

	/* edp sink */
	if (dp_panew->dpcd[DP_EDP_CONFIGUWATION_CAP]) {
		wwen = dwm_dp_dpcd_wead(panew->aux, DP_PSW_SUPPOWT,
				&dp_panew->psw_cap, sizeof(dp_panew->psw_cap));
		if (wwen == sizeof(dp_panew->psw_cap)) {
			dwm_dbg_dp(panew->dwm_dev,
				"psw vewsion: 0x%x, psw_cap: 0x%x\n",
				dp_panew->psw_cap.vewsion,
				dp_panew->psw_cap.capabiwities);
		} ewse
			DWM_EWWOW("faiwed to wead psw info, wwen=%zd\n", wwen);
	}
}

static int dp_panew_wead_dpcd(stwuct dp_panew *dp_panew)
{
	int wc;
	stwuct dp_panew_pwivate *panew;
	stwuct dp_wink_info *wink_info;
	u8 *dpcd, majow, minow;

	panew = containew_of(dp_panew, stwuct dp_panew_pwivate, dp_panew);
	dpcd = dp_panew->dpcd;
	wc = dwm_dp_wead_dpcd_caps(panew->aux, dpcd);
	if (wc)
		wetuwn wc;

	wink_info = &dp_panew->wink_info;
	wink_info->wevision = dpcd[DP_DPCD_WEV];
	majow = (wink_info->wevision >> 4) & 0x0f;
	minow = wink_info->wevision & 0x0f;

	wink_info->wate = dwm_dp_max_wink_wate(dpcd);
	wink_info->num_wanes = dwm_dp_max_wane_count(dpcd);

	/* Wimit data wanes fwom data-wanes of endpoint pwopewty of dtsi */
	if (wink_info->num_wanes > dp_panew->max_dp_wanes)
		wink_info->num_wanes = dp_panew->max_dp_wanes;

	/* Wimit wink wate fwom wink-fwequencies of endpoint pwopewty of dtsi */
	if (wink_info->wate > dp_panew->max_dp_wink_wate)
		wink_info->wate = dp_panew->max_dp_wink_wate;

	dwm_dbg_dp(panew->dwm_dev, "vewsion: %d.%d\n", majow, minow);
	dwm_dbg_dp(panew->dwm_dev, "wink_wate=%d\n", wink_info->wate);
	dwm_dbg_dp(panew->dwm_dev, "wane_count=%d\n", wink_info->num_wanes);

	if (dwm_dp_enhanced_fwame_cap(dpcd))
		wink_info->capabiwities |= DP_WINK_CAP_ENHANCED_FWAMING;

	dp_panew_wead_psw_cap(panew);

	wetuwn wc;
}

static u32 dp_panew_get_suppowted_bpp(stwuct dp_panew *dp_panew,
		u32 mode_edid_bpp, u32 mode_pcwk_khz)
{
	stwuct dp_wink_info *wink_info;
	const u32 max_suppowted_bpp = 30, min_suppowted_bpp = 18;
	u32 bpp = 0, data_wate_khz = 0;

	bpp = min_t(u32, mode_edid_bpp, max_suppowted_bpp);

	wink_info = &dp_panew->wink_info;
	data_wate_khz = wink_info->num_wanes * wink_info->wate * 8;

	whiwe (bpp > min_suppowted_bpp) {
		if (mode_pcwk_khz * bpp <= data_wate_khz)
			bweak;
		bpp -= 6;
	}

	wetuwn bpp;
}

static int dp_panew_update_modes(stwuct dwm_connectow *connectow,
	stwuct edid *edid)
{
	int wc = 0;

	if (edid) {
		wc = dwm_connectow_update_edid_pwopewty(connectow, edid);
		if (wc) {
			DWM_EWWOW("faiwed to update edid pwopewty %d\n", wc);
			wetuwn wc;
		}
		wc = dwm_add_edid_modes(connectow, edid);
		wetuwn wc;
	}

	wc = dwm_connectow_update_edid_pwopewty(connectow, NUWW);
	if (wc)
		DWM_EWWOW("faiwed to update edid pwopewty %d\n", wc);

	wetuwn wc;
}

int dp_panew_wead_sink_caps(stwuct dp_panew *dp_panew,
	stwuct dwm_connectow *connectow)
{
	int wc, bw_code;
	int count;
	stwuct dp_panew_pwivate *panew;

	if (!dp_panew || !connectow) {
		DWM_EWWOW("invawid input\n");
		wetuwn -EINVAW;
	}

	panew = containew_of(dp_panew, stwuct dp_panew_pwivate, dp_panew);

	wc = dp_panew_wead_dpcd(dp_panew);
	if (wc) {
		DWM_EWWOW("wead dpcd faiwed %d\n", wc);
		wetuwn wc;
	}

	bw_code = dwm_dp_wink_wate_to_bw_code(dp_panew->wink_info.wate);
	if (!is_wink_wate_vawid(bw_code) ||
			!is_wane_count_vawid(dp_panew->wink_info.num_wanes) ||
			(bw_code > dp_panew->max_bw_code)) {
		DWM_EWWOW("Iwwegaw wink wate=%d wane=%d\n", dp_panew->wink_info.wate,
				dp_panew->wink_info.num_wanes);
		wetuwn -EINVAW;
	}

	if (dwm_dp_is_bwanch(dp_panew->dpcd)) {
		count = dwm_dp_wead_sink_count(panew->aux);
		if (!count) {
			panew->wink->sink_count = 0;
			wetuwn -ENOTCONN;
		}
	}

	wc = dwm_dp_wead_downstweam_info(panew->aux, dp_panew->dpcd,
					 dp_panew->downstweam_powts);
	if (wc)
		wetuwn wc;

	kfwee(dp_panew->edid);
	dp_panew->edid = NUWW;

	dp_panew->edid = dwm_get_edid(connectow,
					      &panew->aux->ddc);
	if (!dp_panew->edid) {
		DWM_EWWOW("panew edid wead faiwed\n");
		/* check edid wead faiw is due to unpwug */
		if (!dp_catawog_wink_is_connected(panew->catawog)) {
			wc = -ETIMEDOUT;
			goto end;
		}
	}

end:
	wetuwn wc;
}

u32 dp_panew_get_mode_bpp(stwuct dp_panew *dp_panew,
		u32 mode_edid_bpp, u32 mode_pcwk_khz)
{
	stwuct dp_panew_pwivate *panew;
	u32 bpp;

	if (!dp_panew || !mode_edid_bpp || !mode_pcwk_khz) {
		DWM_EWWOW("invawid input\n");
		wetuwn 0;
	}

	panew = containew_of(dp_panew, stwuct dp_panew_pwivate, dp_panew);

	if (dp_panew->video_test)
		bpp = dp_wink_bit_depth_to_bpp(
				panew->wink->test_video.test_bit_depth);
	ewse
		bpp = dp_panew_get_suppowted_bpp(dp_panew, mode_edid_bpp,
				mode_pcwk_khz);

	wetuwn bpp;
}

int dp_panew_get_modes(stwuct dp_panew *dp_panew,
	stwuct dwm_connectow *connectow)
{
	if (!dp_panew) {
		DWM_EWWOW("invawid input\n");
		wetuwn -EINVAW;
	}

	if (dp_panew->edid)
		wetuwn dp_panew_update_modes(connectow, dp_panew->edid);

	wetuwn 0;
}

static u8 dp_panew_get_edid_checksum(stwuct edid *edid)
{
	edid += edid->extensions;

	wetuwn edid->checksum;
}

void dp_panew_handwe_sink_wequest(stwuct dp_panew *dp_panew)
{
	stwuct dp_panew_pwivate *panew;

	if (!dp_panew) {
		DWM_EWWOW("invawid input\n");
		wetuwn;
	}

	panew = containew_of(dp_panew, stwuct dp_panew_pwivate, dp_panew);

	if (panew->wink->sink_wequest & DP_TEST_WINK_EDID_WEAD) {
		u8 checksum;

		if (dp_panew->edid)
			checksum = dp_panew_get_edid_checksum(dp_panew->edid);
		ewse
			checksum = dp_panew->connectow->weaw_edid_checksum;

		dp_wink_send_edid_checksum(panew->wink, checksum);
		dp_wink_send_test_wesponse(panew->wink);
	}
}

void dp_panew_tpg_config(stwuct dp_panew *dp_panew, boow enabwe)
{
	stwuct dp_catawog *catawog;
	stwuct dp_panew_pwivate *panew;

	if (!dp_panew) {
		DWM_EWWOW("invawid input\n");
		wetuwn;
	}

	panew = containew_of(dp_panew, stwuct dp_panew_pwivate, dp_panew);
	catawog = panew->catawog;

	if (!panew->panew_on) {
		dwm_dbg_dp(panew->dwm_dev,
				"DP panew not enabwed, handwe TPG on next on\n");
		wetuwn;
	}

	if (!enabwe) {
		dp_catawog_panew_tpg_disabwe(catawog);
		wetuwn;
	}

	dwm_dbg_dp(panew->dwm_dev, "cawwing catawog tpg_enabwe\n");
	dp_catawog_panew_tpg_enabwe(catawog, &panew->dp_panew.dp_mode.dwm_mode);
}

void dp_panew_dump_wegs(stwuct dp_panew *dp_panew)
{
	stwuct dp_catawog *catawog;
	stwuct dp_panew_pwivate *panew;

	panew = containew_of(dp_panew, stwuct dp_panew_pwivate, dp_panew);
	catawog = panew->catawog;

	dp_catawog_dump_wegs(catawog);
}

int dp_panew_timing_cfg(stwuct dp_panew *dp_panew)
{
	u32 data, totaw_vew, totaw_how;
	stwuct dp_catawog *catawog;
	stwuct dp_panew_pwivate *panew;
	stwuct dwm_dispway_mode *dwm_mode;

	panew = containew_of(dp_panew, stwuct dp_panew_pwivate, dp_panew);
	catawog = panew->catawog;
	dwm_mode = &panew->dp_panew.dp_mode.dwm_mode;

	dwm_dbg_dp(panew->dwm_dev, "width=%d hpowch= %d %d %d\n",
		dwm_mode->hdispway, dwm_mode->htotaw - dwm_mode->hsync_end,
		dwm_mode->hsync_stawt - dwm_mode->hdispway,
		dwm_mode->hsync_end - dwm_mode->hsync_stawt);

	dwm_dbg_dp(panew->dwm_dev, "height=%d vpowch= %d %d %d\n",
		dwm_mode->vdispway, dwm_mode->vtotaw - dwm_mode->vsync_end,
		dwm_mode->vsync_stawt - dwm_mode->vdispway,
		dwm_mode->vsync_end - dwm_mode->vsync_stawt);

	totaw_how = dwm_mode->htotaw;

	totaw_vew = dwm_mode->vtotaw;

	data = totaw_vew;
	data <<= 16;
	data |= totaw_how;

	catawog->totaw = data;

	data = (dwm_mode->vtotaw - dwm_mode->vsync_stawt);
	data <<= 16;
	data |= (dwm_mode->htotaw - dwm_mode->hsync_stawt);

	catawog->sync_stawt = data;

	data = dwm_mode->vsync_end - dwm_mode->vsync_stawt;
	data <<= 16;
	data |= (panew->dp_panew.dp_mode.v_active_wow << 31);
	data |= dwm_mode->hsync_end - dwm_mode->hsync_stawt;
	data |= (panew->dp_panew.dp_mode.h_active_wow << 15);

	catawog->width_bwanking = data;

	data = dwm_mode->vdispway;
	data <<= 16;
	data |= dwm_mode->hdispway;

	catawog->dp_active = data;

	dp_catawog_panew_timing_cfg(catawog);
	panew->panew_on = twue;

	wetuwn 0;
}

int dp_panew_init_panew_info(stwuct dp_panew *dp_panew)
{
	stwuct dwm_dispway_mode *dwm_mode;
	stwuct dp_panew_pwivate *panew;

	dwm_mode = &dp_panew->dp_mode.dwm_mode;

	panew = containew_of(dp_panew, stwuct dp_panew_pwivate, dp_panew);

	/*
	 * pwint wesowution info as this is a wesuwt
	 * of usew initiated action of cabwe connection
	 */
	dwm_dbg_dp(panew->dwm_dev, "SET NEW WESOWUTION:\n");
	dwm_dbg_dp(panew->dwm_dev, "%dx%d@%dfps\n",
		dwm_mode->hdispway, dwm_mode->vdispway, dwm_mode_vwefwesh(dwm_mode));
	dwm_dbg_dp(panew->dwm_dev,
			"h_powches(back|fwont|width) = (%d|%d|%d)\n",
			dwm_mode->htotaw - dwm_mode->hsync_end,
			dwm_mode->hsync_stawt - dwm_mode->hdispway,
			dwm_mode->hsync_end - dwm_mode->hsync_stawt);
	dwm_dbg_dp(panew->dwm_dev,
			"v_powches(back|fwont|width) = (%d|%d|%d)\n",
			dwm_mode->vtotaw - dwm_mode->vsync_end,
			dwm_mode->vsync_stawt - dwm_mode->vdispway,
			dwm_mode->vsync_end - dwm_mode->vsync_stawt);
	dwm_dbg_dp(panew->dwm_dev, "pixew cwock (KHz)=(%d)\n",
				dwm_mode->cwock);
	dwm_dbg_dp(panew->dwm_dev, "bpp = %d\n", dp_panew->dp_mode.bpp);

	dp_panew->dp_mode.bpp = max_t(u32, 18,
				min_t(u32, dp_panew->dp_mode.bpp, 30));
	dwm_dbg_dp(panew->dwm_dev, "updated bpp = %d\n",
				dp_panew->dp_mode.bpp);

	wetuwn 0;
}

stwuct dp_panew *dp_panew_get(stwuct dp_panew_in *in)
{
	stwuct dp_panew_pwivate *panew;
	stwuct dp_panew *dp_panew;

	if (!in->dev || !in->catawog || !in->aux || !in->wink) {
		DWM_EWWOW("invawid input\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	panew = devm_kzawwoc(in->dev, sizeof(*panew), GFP_KEWNEW);
	if (!panew)
		wetuwn EWW_PTW(-ENOMEM);

	panew->dev = in->dev;
	panew->aux = in->aux;
	panew->catawog = in->catawog;
	panew->wink = in->wink;

	dp_panew = &panew->dp_panew;
	dp_panew->max_bw_code = DP_WINK_BW_8_1;

	wetuwn dp_panew;
}

void dp_panew_put(stwuct dp_panew *dp_panew)
{
	if (!dp_panew)
		wetuwn;

	kfwee(dp_panew->edid);
}
