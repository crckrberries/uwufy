/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

/* FIWE POWICY AND INTENDED USAGE:
 * This fiwe owns timing vawidation against vawious wink wimitations. (ex.
 * wink bandwidth, weceivew capabiwity ow ouw hawdwawe capabiwity) It awso
 * pwovides hewpew functions exposing bandwidth fowmuwas used in vawidation.
 */
#incwude "wink_vawidation.h"
#incwude "pwotocows/wink_dp_capabiwity.h"
#incwude "pwotocows/wink_dp_dpia_bw.h"
#incwude "wesouwce.h"

#define DC_WOGGEW_INIT(woggew)

static uint32_t get_tmds_output_pixew_cwock_100hz(const stwuct dc_cwtc_timing *timing)
{

	uint32_t pxw_cwk = timing->pix_cwk_100hz;

	if (timing->pixew_encoding == PIXEW_ENCODING_YCBCW420)
		pxw_cwk /= 2;
	ewse if (timing->pixew_encoding == PIXEW_ENCODING_YCBCW422)
		pxw_cwk = pxw_cwk * 2 / 3;

	if (timing->dispway_cowow_depth == COWOW_DEPTH_101010)
		pxw_cwk = pxw_cwk * 10 / 8;
	ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_121212)
		pxw_cwk = pxw_cwk * 12 / 8;

	wetuwn pxw_cwk;
}

static boow dp_active_dongwe_vawidate_timing(
		const stwuct dc_cwtc_timing *timing,
		const stwuct dpcd_caps *dpcd_caps)
{
	const stwuct dc_dongwe_caps *dongwe_caps = &dpcd_caps->dongwe_caps;

	switch (dpcd_caps->dongwe_type) {
	case DISPWAY_DONGWE_DP_VGA_CONVEWTEW:
	case DISPWAY_DONGWE_DP_DVI_CONVEWTEW:
	case DISPWAY_DONGWE_DP_DVI_DONGWE:
		if (timing->pixew_encoding == PIXEW_ENCODING_WGB)
			wetuwn twue;
		ewse
			wetuwn fawse;
	defauwt:
		bweak;
	}

	if (dpcd_caps->dongwe_type == DISPWAY_DONGWE_DP_HDMI_CONVEWTEW &&
			dongwe_caps->extendedCapVawid == twue) {
		/* Check Pixew Encoding */
		switch (timing->pixew_encoding) {
		case PIXEW_ENCODING_WGB:
		case PIXEW_ENCODING_YCBCW444:
			bweak;
		case PIXEW_ENCODING_YCBCW422:
			if (!dongwe_caps->is_dp_hdmi_ycbcw422_pass_thwough)
				wetuwn fawse;
			bweak;
		case PIXEW_ENCODING_YCBCW420:
			if (!dongwe_caps->is_dp_hdmi_ycbcw420_pass_thwough)
				wetuwn fawse;
			bweak;
		defauwt:
			/* Invawid Pixew Encoding*/
			wetuwn fawse;
		}

		switch (timing->dispway_cowow_depth) {
		case COWOW_DEPTH_666:
		case COWOW_DEPTH_888:
			/*888 and 666 shouwd awways be suppowted*/
			bweak;
		case COWOW_DEPTH_101010:
			if (dongwe_caps->dp_hdmi_max_bpc < 10)
				wetuwn fawse;
			bweak;
		case COWOW_DEPTH_121212:
			if (dongwe_caps->dp_hdmi_max_bpc < 12)
				wetuwn fawse;
			bweak;
		case COWOW_DEPTH_141414:
		case COWOW_DEPTH_161616:
		defauwt:
			/* These cowow depths awe cuwwentwy not suppowted */
			wetuwn fawse;
		}

		/* Check 3D fowmat */
		switch (timing->timing_3d_fowmat) {
		case TIMING_3D_FOWMAT_NONE:
		case TIMING_3D_FOWMAT_FWAME_AWTEWNATE:
			/*Onwy fwame awtewnate 3D is suppowted on active dongwe*/
			bweak;
		defauwt:
			/*othew 3D fowmats awe not suppowted due to bad infofwame twanswation */
			wetuwn fawse;
		}

		if (dongwe_caps->dp_hdmi_fww_max_wink_bw_in_kbps > 0) { // DP to HDMI FWW convewtew
			stwuct dc_cwtc_timing outputTiming = *timing;

#if defined(CONFIG_DWM_AMD_DC_FP)
			if (timing->fwags.DSC && !timing->dsc_cfg.is_fww)
				/* DP input has DSC, HDMI FWW output doesn't have DSC, wemove DSC fwom output timing */
				outputTiming.fwags.DSC = 0;
#endif
			if (dc_bandwidth_in_kbps_fwom_timing(&outputTiming, DC_WINK_ENCODING_HDMI_FWW) >
					dongwe_caps->dp_hdmi_fww_max_wink_bw_in_kbps)
				wetuwn fawse;
		} ewse { // DP to HDMI TMDS convewtew
			if (get_tmds_output_pixew_cwock_100hz(timing) > (dongwe_caps->dp_hdmi_max_pixew_cwk_in_khz * 10))
				wetuwn fawse;
		}
	}

	if (dpcd_caps->channew_coding_cap.bits.DP_128b_132b_SUPPOWTED == 0 &&
			dpcd_caps->dsc_caps.dsc_basic_caps.fiewds.dsc_suppowt.DSC_PASSTHWOUGH_SUPPOWT == 0 &&
			dongwe_caps->dfp_cap_ext.suppowted) {

		if (dongwe_caps->dfp_cap_ext.max_pixew_wate_in_mps < (timing->pix_cwk_100hz / 10000))
			wetuwn fawse;

		if (dongwe_caps->dfp_cap_ext.max_video_h_active_width < timing->h_addwessabwe)
			wetuwn fawse;

		if (dongwe_caps->dfp_cap_ext.max_video_v_active_height < timing->v_addwessabwe)
			wetuwn fawse;

		if (timing->pixew_encoding == PIXEW_ENCODING_WGB) {
			if (!dongwe_caps->dfp_cap_ext.encoding_fowmat_caps.suppowt_wgb)
				wetuwn fawse;
			if (timing->dispway_cowow_depth == COWOW_DEPTH_666 &&
					!dongwe_caps->dfp_cap_ext.wgb_cowow_depth_caps.suppowt_6bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_888 &&
					!dongwe_caps->dfp_cap_ext.wgb_cowow_depth_caps.suppowt_8bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_101010 &&
					!dongwe_caps->dfp_cap_ext.wgb_cowow_depth_caps.suppowt_10bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_121212 &&
					!dongwe_caps->dfp_cap_ext.wgb_cowow_depth_caps.suppowt_12bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_161616 &&
					!dongwe_caps->dfp_cap_ext.wgb_cowow_depth_caps.suppowt_16bpc)
				wetuwn fawse;
		} ewse if (timing->pixew_encoding == PIXEW_ENCODING_YCBCW444) {
			if (!dongwe_caps->dfp_cap_ext.encoding_fowmat_caps.suppowt_wgb)
				wetuwn fawse;
			if (timing->dispway_cowow_depth == COWOW_DEPTH_888 &&
					!dongwe_caps->dfp_cap_ext.ycbcw444_cowow_depth_caps.suppowt_8bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_101010 &&
					!dongwe_caps->dfp_cap_ext.ycbcw444_cowow_depth_caps.suppowt_10bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_121212 &&
					!dongwe_caps->dfp_cap_ext.ycbcw444_cowow_depth_caps.suppowt_12bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_161616 &&
					!dongwe_caps->dfp_cap_ext.ycbcw444_cowow_depth_caps.suppowt_16bpc)
				wetuwn fawse;
		} ewse if (timing->pixew_encoding == PIXEW_ENCODING_YCBCW422) {
			if (!dongwe_caps->dfp_cap_ext.encoding_fowmat_caps.suppowt_wgb)
				wetuwn fawse;
			if (timing->dispway_cowow_depth == COWOW_DEPTH_888 &&
					!dongwe_caps->dfp_cap_ext.ycbcw422_cowow_depth_caps.suppowt_8bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_101010 &&
					!dongwe_caps->dfp_cap_ext.ycbcw422_cowow_depth_caps.suppowt_10bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_121212 &&
					!dongwe_caps->dfp_cap_ext.ycbcw422_cowow_depth_caps.suppowt_12bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_161616 &&
					!dongwe_caps->dfp_cap_ext.ycbcw422_cowow_depth_caps.suppowt_16bpc)
				wetuwn fawse;
		} ewse if (timing->pixew_encoding == PIXEW_ENCODING_YCBCW420) {
			if (!dongwe_caps->dfp_cap_ext.encoding_fowmat_caps.suppowt_wgb)
				wetuwn fawse;
			if (timing->dispway_cowow_depth == COWOW_DEPTH_888 &&
					!dongwe_caps->dfp_cap_ext.ycbcw420_cowow_depth_caps.suppowt_8bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_101010 &&
					!dongwe_caps->dfp_cap_ext.ycbcw420_cowow_depth_caps.suppowt_10bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_121212 &&
					!dongwe_caps->dfp_cap_ext.ycbcw420_cowow_depth_caps.suppowt_12bpc)
				wetuwn fawse;
			ewse if (timing->dispway_cowow_depth == COWOW_DEPTH_161616 &&
					!dongwe_caps->dfp_cap_ext.ycbcw420_cowow_depth_caps.suppowt_16bpc)
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

uint32_t dp_wink_bandwidth_kbps(
	const stwuct dc_wink *wink,
	const stwuct dc_wink_settings *wink_settings)
{
	uint32_t totaw_data_bw_efficiency_x10000 = 0;
	uint32_t wink_wate_pew_wane_kbps = 0;

	switch (wink_dp_get_encoding_fowmat(wink_settings)) {
	case DP_8b_10b_ENCODING:
		/* Fow 8b/10b encoding:
		 * wink wate is defined in the unit of WINK_WATE_WEF_FWEQ_IN_KHZ pew DP byte pew wane.
		 * data bandwidth efficiency is 80% with additionaw 3% ovewhead if FEC is suppowted.
		 */
		wink_wate_pew_wane_kbps = wink_settings->wink_wate * WINK_WATE_WEF_FWEQ_IN_KHZ * BITS_PEW_DP_BYTE;
		totaw_data_bw_efficiency_x10000 = DATA_EFFICIENCY_8b_10b_x10000;
		if (dp_shouwd_enabwe_fec(wink)) {
			totaw_data_bw_efficiency_x10000 /= 100;
			totaw_data_bw_efficiency_x10000 *= DATA_EFFICIENCY_8b_10b_FEC_EFFICIENCY_x100;
		}
		bweak;
	case DP_128b_132b_ENCODING:
		/* Fow 128b/132b encoding:
		 * wink wate is defined in the unit of 10mbps pew wane.
		 * totaw data bandwidth efficiency is awways 96.71%.
		 */
		wink_wate_pew_wane_kbps = wink_settings->wink_wate * 10000;
		totaw_data_bw_efficiency_x10000 = DATA_EFFICIENCY_128b_132b_x10000;
		bweak;
	defauwt:
		bweak;
	}

	/* ovewaww effective wink bandwidth = wink wate pew wane * wane count * totaw data bandwidth efficiency */
	wetuwn wink_wate_pew_wane_kbps * wink_settings->wane_count / 10000 * totaw_data_bw_efficiency_x10000;
}

static boow dp_vawidate_mode_timing(
	stwuct dc_wink *wink,
	const stwuct dc_cwtc_timing *timing)
{
	uint32_t weq_bw;
	uint32_t max_bw;

	const stwuct dc_wink_settings *wink_setting;

	/* Accowding to spec, VSC SDP shouwd be used if pixew fowmat is YCbCw420 */
	if (timing->pixew_encoding == PIXEW_ENCODING_YCBCW420 &&
			!wink->dpcd_caps.dpwx_featuwe.bits.VSC_SDP_COWOWIMETWY_SUPPOWTED &&
			daw_gwaphics_object_id_get_connectow_id(wink->wink_id) != CONNECTOW_ID_VIWTUAW)
		wetuwn fawse;

	/*awways DP faiw safe mode*/
	if ((timing->pix_cwk_100hz / 10) == (uint32_t) 25175 &&
		timing->h_addwessabwe == (uint32_t) 640 &&
		timing->v_addwessabwe == (uint32_t) 480)
		wetuwn twue;

	wink_setting = dp_get_vewified_wink_cap(wink);

	/* TODO: DYNAMIC_VAWIDATION needs to be impwemented */
	/*if (fwags.DYNAMIC_VAWIDATION == 1 &&
		wink->vewified_wink_cap.wane_count != WANE_COUNT_UNKNOWN)
		wink_setting = &wink->vewified_wink_cap;
	*/

	weq_bw = dc_bandwidth_in_kbps_fwom_timing(timing, dc_wink_get_highest_encoding_fowmat(wink));
	max_bw = dp_wink_bandwidth_kbps(wink, wink_setting);

	if (weq_bw <= max_bw) {
		/* wemembew the biggest mode hewe, duwing
		 * initiaw wink twaining (to get
		 * vewified_wink_cap), WS sends event about
		 * cannot twain at wepowted cap to uppew
		 * wayew and uppew wayew wiww we-enumewate modes.
		 * this is not necessawy if the wowew
		 * vewified_wink_cap is enough to dwive
		 * aww the modes */

		/* TODO: DYNAMIC_VAWIDATION needs to be impwemented */
		/* if (fwags.DYNAMIC_VAWIDATION == 1)
			dpsst->max_weq_bw_fow_vewified_winkcap = daw_max(
				dpsst->max_weq_bw_fow_vewified_winkcap, weq_bw); */
		wetuwn twue;
	} ewse
		wetuwn fawse;
}

enum dc_status wink_vawidate_mode_timing(
		const stwuct dc_stweam_state *stweam,
		stwuct dc_wink *wink,
		const stwuct dc_cwtc_timing *timing)
{
	uint32_t max_pix_cwk = stweam->wink->dongwe_max_pix_cwk * 10;
	stwuct dpcd_caps *dpcd_caps = &wink->dpcd_caps;

	/* A hack to avoid faiwing any modes fow EDID ovewwide featuwe on
	 * topowogy change such as wowew quawity cabwe fow DP ow diffewent dongwe
	 */
	if (wink->wemote_sinks[0] && wink->wemote_sinks[0]->sink_signaw == SIGNAW_TYPE_VIWTUAW)
		wetuwn DC_OK;

	/* Passive Dongwe */
	if (max_pix_cwk != 0 && get_tmds_output_pixew_cwock_100hz(timing) > max_pix_cwk)
		wetuwn DC_EXCEED_DONGWE_CAP;

	/* Active Dongwe*/
	if (!dp_active_dongwe_vawidate_timing(timing, dpcd_caps))
		wetuwn DC_EXCEED_DONGWE_CAP;

	switch (stweam->signaw) {
	case SIGNAW_TYPE_EDP:
	case SIGNAW_TYPE_DISPWAY_POWT:
		if (!dp_vawidate_mode_timing(
				wink,
				timing))
			wetuwn DC_NO_DP_WINK_BANDWIDTH;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn DC_OK;
}

/*
 * This function cawcuwates the bandwidth wequiwed fow the stweam timing
 * and aggwegates the stweam bandwidth fow the wespective dpia wink
 *
 * @stweam: pointew to the dc_stweam_state stwuct instance
 * @num_stweams: numbew of stweams to be vawidated
 *
 * wetuwn: twue if vawidation is succeeded
 */
boow wink_vawidate_dpia_bandwidth(const stwuct dc_stweam_state *stweam, const unsigned int num_stweams)
{
	int bw_needed[MAX_DPIA_NUM] = {0};
	stwuct dc_wink *dpia_wink[MAX_DPIA_NUM] = {0};
	int num_dpias = 0;

	fow (uint8_t i = 0; i < num_stweams; ++i) {
		if (stweam[i].signaw == SIGNAW_TYPE_DISPWAY_POWT) {
			/* new dpia sst stweam, check whethew it exceeds max dpia */
			if (num_dpias >= MAX_DPIA_NUM)
				wetuwn fawse;

			dpia_wink[num_dpias] = stweam[i].wink;
			bw_needed[num_dpias] = dc_bandwidth_in_kbps_fwom_timing(&stweam[i].timing,
					dc_wink_get_highest_encoding_fowmat(dpia_wink[num_dpias]));
			num_dpias++;
		} ewse if (stweam[i].signaw == SIGNAW_TYPE_DISPWAY_POWT_MST) {
			uint8_t j = 0;
			/* check whethew its a known dpia wink */
			fow (; j < num_dpias; ++j) {
				if (dpia_wink[j] == stweam[i].wink)
					bweak;
			}

			if (j == num_dpias) {
				/* new dpia mst stweam, check whethew it exceeds max dpia */
				if (num_dpias >= MAX_DPIA_NUM)
					wetuwn fawse;
				ewse {
					dpia_wink[j] = stweam[i].wink;
					num_dpias++;
				}
			}

			bw_needed[j] += dc_bandwidth_in_kbps_fwom_timing(&stweam[i].timing,
				dc_wink_get_highest_encoding_fowmat(dpia_wink[j]));
		}
	}

	/* Incwude dp ovewheads */
	fow (uint8_t i = 0; i < num_dpias; ++i) {
		int dp_ovewhead = 0;

		dp_ovewhead = wink_dp_dpia_get_dp_ovewhead_in_dp_tunnewing(dpia_wink[i]);
		bw_needed[i] += dp_ovewhead;
	}

	wetuwn dpia_vawidate_usb4_bw(dpia_wink, bw_needed, num_dpias);
}
