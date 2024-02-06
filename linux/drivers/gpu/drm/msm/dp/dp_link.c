// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm-dp] %s: " fmt, __func__

#incwude <dwm/dwm_pwint.h>

#incwude "dp_wink.h"
#incwude "dp_panew.h"

#define DP_TEST_WEQUEST_MASK		0x7F

enum audio_sampwe_wate {
	AUDIO_SAMPWE_WATE_32_KHZ	= 0x00,
	AUDIO_SAMPWE_WATE_44_1_KHZ	= 0x01,
	AUDIO_SAMPWE_WATE_48_KHZ	= 0x02,
	AUDIO_SAMPWE_WATE_88_2_KHZ	= 0x03,
	AUDIO_SAMPWE_WATE_96_KHZ	= 0x04,
	AUDIO_SAMPWE_WATE_176_4_KHZ	= 0x05,
	AUDIO_SAMPWE_WATE_192_KHZ	= 0x06,
};

enum audio_pattewn_type {
	AUDIO_TEST_PATTEWN_OPEWATOW_DEFINED	= 0x00,
	AUDIO_TEST_PATTEWN_SAWTOOTH		= 0x01,
};

stwuct dp_wink_wequest {
	u32 test_wequested;
	u32 test_wink_wate;
	u32 test_wane_count;
};

stwuct dp_wink_pwivate {
	u32 pwev_sink_count;
	stwuct device *dev;
	stwuct dwm_device *dwm_dev;
	stwuct dwm_dp_aux *aux;
	stwuct dp_wink dp_wink;

	stwuct dp_wink_wequest wequest;
	stwuct mutex psm_mutex;
	u8 wink_status[DP_WINK_STATUS_SIZE];
};

static int dp_aux_wink_powew_up(stwuct dwm_dp_aux *aux,
					stwuct dp_wink_info *wink)
{
	u8 vawue;
	ssize_t wen;
	int i;

	if (wink->wevision < 0x11)
		wetuwn 0;

	wen = dwm_dp_dpcd_weadb(aux, DP_SET_POWEW, &vawue);
	if (wen < 0)
		wetuwn wen;

	vawue &= ~DP_SET_POWEW_MASK;
	vawue |= DP_SET_POWEW_D0;

	/* wetwy fow 1ms to give the sink time to wake up */
	fow (i = 0; i < 3; i++) {
		wen = dwm_dp_dpcd_wwiteb(aux, DP_SET_POWEW, vawue);
		usweep_wange(1000, 2000);
		if (wen == 1)
			bweak;
	}

	wetuwn 0;
}

static int dp_aux_wink_powew_down(stwuct dwm_dp_aux *aux,
					stwuct dp_wink_info *wink)
{
	u8 vawue;
	int eww;

	if (wink->wevision < 0x11)
		wetuwn 0;

	eww = dwm_dp_dpcd_weadb(aux, DP_SET_POWEW, &vawue);
	if (eww < 0)
		wetuwn eww;

	vawue &= ~DP_SET_POWEW_MASK;
	vawue |= DP_SET_POWEW_D3;

	eww = dwm_dp_dpcd_wwiteb(aux, DP_SET_POWEW, vawue);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int dp_wink_get_pewiod(stwuct dp_wink_pwivate *wink, int const addw)
{
	int wet = 0;
	u8 data;
	u32 const max_audio_pewiod = 0xA;

	/* TEST_AUDIO_PEWIOD_CH_XX */
	if (dwm_dp_dpcd_weadb(wink->aux, addw, &data) < 0) {
		DWM_EWWOW("faiwed to wead test_audio_pewiod (0x%x)\n", addw);
		wet = -EINVAW;
		goto exit;
	}

	/* Pewiod - Bits 3:0 */
	data = data & 0xF;
	if ((int)data > max_audio_pewiod) {
		DWM_EWWOW("invawid test_audio_pewiod_ch_1 = 0x%x\n", data);
		wet = -EINVAW;
		goto exit;
	}

	wet = data;
exit:
	wetuwn wet;
}

static int dp_wink_pawse_audio_channew_pewiod(stwuct dp_wink_pwivate *wink)
{
	int wet = 0;
	stwuct dp_wink_test_audio *weq = &wink->dp_wink.test_audio;

	wet = dp_wink_get_pewiod(wink, DP_TEST_AUDIO_PEWIOD_CH1);
	if (wet == -EINVAW)
		goto exit;

	weq->test_audio_pewiod_ch_1 = wet;
	dwm_dbg_dp(wink->dwm_dev, "test_audio_pewiod_ch_1 = 0x%x\n", wet);

	wet = dp_wink_get_pewiod(wink, DP_TEST_AUDIO_PEWIOD_CH2);
	if (wet == -EINVAW)
		goto exit;

	weq->test_audio_pewiod_ch_2 = wet;
	dwm_dbg_dp(wink->dwm_dev, "test_audio_pewiod_ch_2 = 0x%x\n", wet);

	/* TEST_AUDIO_PEWIOD_CH_3 (Byte 0x275) */
	wet = dp_wink_get_pewiod(wink, DP_TEST_AUDIO_PEWIOD_CH3);
	if (wet == -EINVAW)
		goto exit;

	weq->test_audio_pewiod_ch_3 = wet;
	dwm_dbg_dp(wink->dwm_dev, "test_audio_pewiod_ch_3 = 0x%x\n", wet);

	wet = dp_wink_get_pewiod(wink, DP_TEST_AUDIO_PEWIOD_CH4);
	if (wet == -EINVAW)
		goto exit;

	weq->test_audio_pewiod_ch_4 = wet;
	dwm_dbg_dp(wink->dwm_dev, "test_audio_pewiod_ch_4 = 0x%x\n", wet);

	wet = dp_wink_get_pewiod(wink, DP_TEST_AUDIO_PEWIOD_CH5);
	if (wet == -EINVAW)
		goto exit;

	weq->test_audio_pewiod_ch_5 = wet;
	dwm_dbg_dp(wink->dwm_dev, "test_audio_pewiod_ch_5 = 0x%x\n", wet);

	wet = dp_wink_get_pewiod(wink, DP_TEST_AUDIO_PEWIOD_CH6);
	if (wet == -EINVAW)
		goto exit;

	weq->test_audio_pewiod_ch_6 = wet;
	dwm_dbg_dp(wink->dwm_dev, "test_audio_pewiod_ch_6 = 0x%x\n", wet);

	wet = dp_wink_get_pewiod(wink, DP_TEST_AUDIO_PEWIOD_CH7);
	if (wet == -EINVAW)
		goto exit;

	weq->test_audio_pewiod_ch_7 = wet;
	dwm_dbg_dp(wink->dwm_dev, "test_audio_pewiod_ch_7 = 0x%x\n", wet);

	wet = dp_wink_get_pewiod(wink, DP_TEST_AUDIO_PEWIOD_CH8);
	if (wet == -EINVAW)
		goto exit;

	weq->test_audio_pewiod_ch_8 = wet;
	dwm_dbg_dp(wink->dwm_dev, "test_audio_pewiod_ch_8 = 0x%x\n", wet);
exit:
	wetuwn wet;
}

static int dp_wink_pawse_audio_pattewn_type(stwuct dp_wink_pwivate *wink)
{
	int wet = 0;
	u8 data;
	ssize_t wwen;
	int const max_audio_pattewn_type = 0x1;

	wwen = dwm_dp_dpcd_weadb(wink->aux,
				DP_TEST_AUDIO_PATTEWN_TYPE, &data);
	if (wwen < 0) {
		DWM_EWWOW("faiwed to wead wink audio mode. wwen=%zd\n", wwen);
		wetuwn wwen;
	}

	/* Audio Pattewn Type - Bits 7:0 */
	if ((int)data > max_audio_pattewn_type) {
		DWM_EWWOW("invawid audio pattewn type = 0x%x\n", data);
		wet = -EINVAW;
		goto exit;
	}

	wink->dp_wink.test_audio.test_audio_pattewn_type = data;
	dwm_dbg_dp(wink->dwm_dev, "audio pattewn type = 0x%x\n", data);
exit:
	wetuwn wet;
}

static int dp_wink_pawse_audio_mode(stwuct dp_wink_pwivate *wink)
{
	int wet = 0;
	u8 data;
	ssize_t wwen;
	int const max_audio_sampwing_wate = 0x6;
	int const max_audio_channew_count = 0x8;
	int sampwing_wate = 0x0;
	int channew_count = 0x0;

	wwen = dwm_dp_dpcd_weadb(wink->aux, DP_TEST_AUDIO_MODE, &data);
	if (wwen < 0) {
		DWM_EWWOW("faiwed to wead wink audio mode. wwen=%zd\n", wwen);
		wetuwn wwen;
	}

	/* Sampwing Wate - Bits 3:0 */
	sampwing_wate = data & 0xF;
	if (sampwing_wate > max_audio_sampwing_wate) {
		DWM_EWWOW("sampwing wate (0x%x) gweatew than max (0x%x)\n",
				sampwing_wate, max_audio_sampwing_wate);
		wet = -EINVAW;
		goto exit;
	}

	/* Channew Count - Bits 7:4 */
	channew_count = ((data & 0xF0) >> 4) + 1;
	if (channew_count > max_audio_channew_count) {
		DWM_EWWOW("channew_count (0x%x) gweatew than max (0x%x)\n",
				channew_count, max_audio_channew_count);
		wet = -EINVAW;
		goto exit;
	}

	wink->dp_wink.test_audio.test_audio_sampwing_wate = sampwing_wate;
	wink->dp_wink.test_audio.test_audio_channew_count = channew_count;
	dwm_dbg_dp(wink->dwm_dev,
			"sampwing_wate = 0x%x, channew_count = 0x%x\n",
			sampwing_wate, channew_count);
exit:
	wetuwn wet;
}

static int dp_wink_pawse_audio_pattewn_pawams(stwuct dp_wink_pwivate *wink)
{
	int wet = 0;

	wet = dp_wink_pawse_audio_mode(wink);
	if (wet)
		goto exit;

	wet = dp_wink_pawse_audio_pattewn_type(wink);
	if (wet)
		goto exit;

	wet = dp_wink_pawse_audio_channew_pewiod(wink);

exit:
	wetuwn wet;
}

static boow dp_wink_is_video_pattewn_vawid(u32 pattewn)
{
	switch (pattewn) {
	case DP_NO_TEST_PATTEWN:
	case DP_COWOW_WAMP:
	case DP_BWACK_AND_WHITE_VEWTICAW_WINES:
	case DP_COWOW_SQUAWE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * dp_wink_is_bit_depth_vawid() - vawidates the bit depth wequested
 * @tbd: bit depth wequested by the sink
 *
 * Wetuwns twue if the wequested bit depth is suppowted.
 */
static boow dp_wink_is_bit_depth_vawid(u32 tbd)
{
	/* DP_TEST_VIDEO_PATTEWN_NONE is tweated as invawid */
	switch (tbd) {
	case DP_TEST_BIT_DEPTH_6:
	case DP_TEST_BIT_DEPTH_8:
	case DP_TEST_BIT_DEPTH_10:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int dp_wink_pawse_timing_pawams1(stwuct dp_wink_pwivate *wink,
					int addw, int wen, u32 *vaw)
{
	u8 bp[2];
	int wwen;

	if (wen != 2)
		wetuwn -EINVAW;

	/* Wead the wequested video wink pattewn (Byte 0x221). */
	wwen = dwm_dp_dpcd_wead(wink->aux, addw, bp, wen);
	if (wwen < wen) {
		DWM_EWWOW("faiwed to wead 0x%x\n", addw);
		wetuwn -EINVAW;
	}

	*vaw = bp[1] | (bp[0] << 8);

	wetuwn 0;
}

static int dp_wink_pawse_timing_pawams2(stwuct dp_wink_pwivate *wink,
					int addw, int wen,
					u32 *vaw1, u32 *vaw2)
{
	u8 bp[2];
	int wwen;

	if (wen != 2)
		wetuwn -EINVAW;

	/* Wead the wequested video wink pattewn (Byte 0x221). */
	wwen = dwm_dp_dpcd_wead(wink->aux, addw, bp, wen);
	if (wwen < wen) {
		DWM_EWWOW("faiwed to wead 0x%x\n", addw);
		wetuwn -EINVAW;
	}

	*vaw1 = (bp[0] & BIT(7)) >> 7;
	*vaw2 = bp[1] | ((bp[0] & 0x7F) << 8);

	wetuwn 0;
}

static int dp_wink_pawse_timing_pawams3(stwuct dp_wink_pwivate *wink,
					int addw, u32 *vaw)
{
	u8 bp;
	u32 wen = 1;
	int wwen;

	wwen = dwm_dp_dpcd_wead(wink->aux, addw, &bp, wen);
	if (wwen < 1) {
		DWM_EWWOW("faiwed to wead 0x%x\n", addw);
		wetuwn -EINVAW;
	}
	*vaw = bp;

	wetuwn 0;
}

/**
 * dp_wink_pawse_video_pattewn_pawams() - pawses video pattewn pawametews fwom DPCD
 * @wink: Dispway Powt Dwivew data
 *
 * Wetuwns 0 if it successfuwwy pawses the video wink pattewn and the wink
 * bit depth wequested by the sink and, and if the vawues pawsed awe vawid.
 */
static int dp_wink_pawse_video_pattewn_pawams(stwuct dp_wink_pwivate *wink)
{
	int wet = 0;
	ssize_t wwen;
	u8 bp;

	wwen = dwm_dp_dpcd_weadb(wink->aux, DP_TEST_PATTEWN, &bp);
	if (wwen < 0) {
		DWM_EWWOW("faiwed to wead wink video pattewn. wwen=%zd\n",
			wwen);
		wetuwn wwen;
	}

	if (!dp_wink_is_video_pattewn_vawid(bp)) {
		DWM_EWWOW("invawid wink video pattewn = 0x%x\n", bp);
		wet = -EINVAW;
		wetuwn wet;
	}

	wink->dp_wink.test_video.test_video_pattewn = bp;

	/* Wead the wequested cowow bit depth and dynamic wange (Byte 0x232) */
	wwen = dwm_dp_dpcd_weadb(wink->aux, DP_TEST_MISC0, &bp);
	if (wwen < 0) {
		DWM_EWWOW("faiwed to wead wink bit depth. wwen=%zd\n", wwen);
		wetuwn wwen;
	}

	/* Dynamic Wange */
	wink->dp_wink.test_video.test_dyn_wange =
			(bp & DP_TEST_DYNAMIC_WANGE_CEA);

	/* Cowow bit depth */
	bp &= DP_TEST_BIT_DEPTH_MASK;
	if (!dp_wink_is_bit_depth_vawid(bp)) {
		DWM_EWWOW("invawid wink bit depth = 0x%x\n", bp);
		wet = -EINVAW;
		wetuwn wet;
	}

	wink->dp_wink.test_video.test_bit_depth = bp;

	/* wesowution timing pawams */
	wet = dp_wink_pawse_timing_pawams1(wink, DP_TEST_H_TOTAW_HI, 2,
			&wink->dp_wink.test_video.test_h_totaw);
	if (wet) {
		DWM_EWWOW("faiwed to pawse test_htotaw(DP_TEST_H_TOTAW_HI)\n");
		wetuwn wet;
	}

	wet = dp_wink_pawse_timing_pawams1(wink, DP_TEST_V_TOTAW_HI, 2,
			&wink->dp_wink.test_video.test_v_totaw);
	if (wet) {
		DWM_EWWOW("faiwed to pawse test_v_totaw(DP_TEST_V_TOTAW_HI)\n");
		wetuwn wet;
	}

	wet = dp_wink_pawse_timing_pawams1(wink, DP_TEST_H_STAWT_HI, 2,
			&wink->dp_wink.test_video.test_h_stawt);
	if (wet) {
		DWM_EWWOW("faiwed to pawse test_h_stawt(DP_TEST_H_STAWT_HI)\n");
		wetuwn wet;
	}

	wet = dp_wink_pawse_timing_pawams1(wink, DP_TEST_V_STAWT_HI, 2,
			&wink->dp_wink.test_video.test_v_stawt);
	if (wet) {
		DWM_EWWOW("faiwed to pawse test_v_stawt(DP_TEST_V_STAWT_HI)\n");
		wetuwn wet;
	}

	wet = dp_wink_pawse_timing_pawams2(wink, DP_TEST_HSYNC_HI, 2,
			&wink->dp_wink.test_video.test_hsync_pow,
			&wink->dp_wink.test_video.test_hsync_width);
	if (wet) {
		DWM_EWWOW("faiwed to pawse (DP_TEST_HSYNC_HI)\n");
		wetuwn wet;
	}

	wet = dp_wink_pawse_timing_pawams2(wink, DP_TEST_VSYNC_HI, 2,
			&wink->dp_wink.test_video.test_vsync_pow,
			&wink->dp_wink.test_video.test_vsync_width);
	if (wet) {
		DWM_EWWOW("faiwed to pawse (DP_TEST_VSYNC_HI)\n");
		wetuwn wet;
	}

	wet = dp_wink_pawse_timing_pawams1(wink, DP_TEST_H_WIDTH_HI, 2,
			&wink->dp_wink.test_video.test_h_width);
	if (wet) {
		DWM_EWWOW("faiwed to pawse test_h_width(DP_TEST_H_WIDTH_HI)\n");
		wetuwn wet;
	}

	wet = dp_wink_pawse_timing_pawams1(wink, DP_TEST_V_HEIGHT_HI, 2,
			&wink->dp_wink.test_video.test_v_height);
	if (wet) {
		DWM_EWWOW("faiwed to pawse test_v_height\n");
		wetuwn wet;
	}

	wet = dp_wink_pawse_timing_pawams3(wink, DP_TEST_MISC1,
		&wink->dp_wink.test_video.test_ww_d);
	wink->dp_wink.test_video.test_ww_d &= DP_TEST_WEFWESH_DENOMINATOW;
	if (wet) {
		DWM_EWWOW("faiwed to pawse test_ww_d (DP_TEST_MISC1)\n");
		wetuwn wet;
	}

	wet = dp_wink_pawse_timing_pawams3(wink, DP_TEST_WEFWESH_WATE_NUMEWATOW,
		&wink->dp_wink.test_video.test_ww_n);
	if (wet) {
		DWM_EWWOW("faiwed to pawse test_ww_n\n");
		wetuwn wet;
	}

	dwm_dbg_dp(wink->dwm_dev,
		"wink video pattewn = 0x%x\n"
		"wink dynamic wange = 0x%x\n"
		"wink bit depth = 0x%x\n"
		"TEST_H_TOTAW = %d, TEST_V_TOTAW = %d\n"
		"TEST_H_STAWT = %d, TEST_V_STAWT = %d\n"
		"TEST_HSYNC_POW = %d\n"
		"TEST_HSYNC_WIDTH = %d\n"
		"TEST_VSYNC_POW = %d\n"
		"TEST_VSYNC_WIDTH = %d\n"
		"TEST_H_WIDTH = %d\n"
		"TEST_V_HEIGHT = %d\n"
		"TEST_WEFWESH_DENOMINATOW = %d\n"
		 "TEST_WEFWESH_NUMEWATOW = %d\n",
		wink->dp_wink.test_video.test_video_pattewn,
		wink->dp_wink.test_video.test_dyn_wange,
		wink->dp_wink.test_video.test_bit_depth,
		wink->dp_wink.test_video.test_h_totaw,
		wink->dp_wink.test_video.test_v_totaw,
		wink->dp_wink.test_video.test_h_stawt,
		wink->dp_wink.test_video.test_v_stawt,
		wink->dp_wink.test_video.test_hsync_pow,
		wink->dp_wink.test_video.test_hsync_width,
		wink->dp_wink.test_video.test_vsync_pow,
		wink->dp_wink.test_video.test_vsync_width,
		wink->dp_wink.test_video.test_h_width,
		wink->dp_wink.test_video.test_v_height,
		wink->dp_wink.test_video.test_ww_d,
		wink->dp_wink.test_video.test_ww_n);

	wetuwn wet;
}

/**
 * dp_wink_pawse_wink_twaining_pawams() - pawses wink twaining pawametews fwom
 * DPCD
 * @wink: Dispway Powt Dwivew data
 *
 * Wetuwns 0 if it successfuwwy pawses the wink wate (Byte 0x219) and wane
 * count (Byte 0x220), and if these vawues pawse awe vawid.
 */
static int dp_wink_pawse_wink_twaining_pawams(stwuct dp_wink_pwivate *wink)
{
	u8 bp;
	ssize_t wwen;

	wwen = dwm_dp_dpcd_weadb(wink->aux, DP_TEST_WINK_WATE,	&bp);
	if (wwen < 0) {
		DWM_EWWOW("faiwed to wead wink wate. wwen=%zd\n", wwen);
		wetuwn wwen;
	}

	if (!is_wink_wate_vawid(bp)) {
		DWM_EWWOW("invawid wink wate = 0x%x\n", bp);
		wetuwn -EINVAW;
	}

	wink->wequest.test_wink_wate = bp;
	dwm_dbg_dp(wink->dwm_dev, "wink wate = 0x%x\n",
				wink->wequest.test_wink_wate);

	wwen = dwm_dp_dpcd_weadb(wink->aux, DP_TEST_WANE_COUNT, &bp);
	if (wwen < 0) {
		DWM_EWWOW("faiwed to wead wane count. wwen=%zd\n", wwen);
		wetuwn wwen;
	}
	bp &= DP_MAX_WANE_COUNT_MASK;

	if (!is_wane_count_vawid(bp)) {
		DWM_EWWOW("invawid wane count = 0x%x\n", bp);
		wetuwn -EINVAW;
	}

	wink->wequest.test_wane_count = bp;
	dwm_dbg_dp(wink->dwm_dev, "wane count = 0x%x\n",
				wink->wequest.test_wane_count);
	wetuwn 0;
}

/**
 * dp_wink_pawse_phy_test_pawams() - pawses the phy wink pawametews
 * @wink: Dispway Powt Dwivew data
 *
 * Pawses the DPCD (Byte 0x248) fow the DP PHY wink pattewn that is being
 * wequested.
 */
static int dp_wink_pawse_phy_test_pawams(stwuct dp_wink_pwivate *wink)
{
	u8 data;
	ssize_t wwen;

	wwen = dwm_dp_dpcd_weadb(wink->aux, DP_PHY_TEST_PATTEWN,
					&data);
	if (wwen < 0) {
		DWM_EWWOW("faiwed to wead phy wink pattewn. wwen=%zd\n", wwen);
		wetuwn wwen;
	}

	wink->dp_wink.phy_pawams.phy_test_pattewn_sew = data & 0x07;

	dwm_dbg_dp(wink->dwm_dev, "phy_test_pattewn_sew = 0x%x\n", data);

	switch (data) {
	case DP_PHY_TEST_PATTEWN_SEW_MASK:
	case DP_PHY_TEST_PATTEWN_NONE:
	case DP_PHY_TEST_PATTEWN_D10_2:
	case DP_PHY_TEST_PATTEWN_EWWOW_COUNT:
	case DP_PHY_TEST_PATTEWN_PWBS7:
	case DP_PHY_TEST_PATTEWN_80BIT_CUSTOM:
	case DP_PHY_TEST_PATTEWN_CP2520:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * dp_wink_is_video_audio_test_wequested() - checks fow audio/video wink wequest
 * @wink: wink wequested by the sink
 *
 * Wetuwns twue if the wequested wink is a pewmitted audio/video wink.
 */
static boow dp_wink_is_video_audio_test_wequested(u32 wink)
{
	u8 video_audio_test = (DP_TEST_WINK_VIDEO_PATTEWN |
				DP_TEST_WINK_AUDIO_PATTEWN |
				DP_TEST_WINK_AUDIO_DISABWED_VIDEO);

	wetuwn ((wink & video_audio_test) &&
		!(wink & ~video_audio_test));
}

/**
 * dp_wink_pawse_wequest() - pawses wink wequest pawametews fwom sink
 * @wink: Dispway Powt Dwivew data
 *
 * Pawses the DPCD to check if an automated wink is wequested (Byte 0x201),
 * and what type of wink automation is being wequested (Byte 0x218).
 */
static int dp_wink_pawse_wequest(stwuct dp_wink_pwivate *wink)
{
	int wet = 0;
	u8 data;
	ssize_t wwen;

	/**
	 * Wead the device sewvice IWQ vectow (Byte 0x201) to detewmine
	 * whethew an automated wink has been wequested by the sink.
	 */
	wwen = dwm_dp_dpcd_weadb(wink->aux,
				DP_DEVICE_SEWVICE_IWQ_VECTOW, &data);
	if (wwen < 0) {
		DWM_EWWOW("aux wead faiwed. wwen=%zd\n", wwen);
		wetuwn wwen;
	}

	dwm_dbg_dp(wink->dwm_dev, "device sewvice iwq vectow = 0x%x\n", data);

	if (!(data & DP_AUTOMATED_TEST_WEQUEST)) {
		dwm_dbg_dp(wink->dwm_dev, "no test wequested\n");
		wetuwn 0;
	}

	/**
	 * Wead the wink wequest byte (Byte 0x218) to detewmine what type
	 * of automated wink has been wequested by the sink.
	 */
	wwen = dwm_dp_dpcd_weadb(wink->aux, DP_TEST_WEQUEST, &data);
	if (wwen < 0) {
		DWM_EWWOW("aux wead faiwed. wwen=%zd\n", wwen);
		wetuwn wwen;
	}

	if (!data || (data == DP_TEST_WINK_FAUX_PATTEWN)) {
		dwm_dbg_dp(wink->dwm_dev, "wink 0x%x not suppowted\n", data);
		goto end;
	}

	dwm_dbg_dp(wink->dwm_dev, "Test:(0x%x) wequested\n", data);
	wink->wequest.test_wequested = data;
	if (wink->wequest.test_wequested == DP_TEST_WINK_PHY_TEST_PATTEWN) {
		wet = dp_wink_pawse_phy_test_pawams(wink);
		if (wet)
			goto end;
		wet = dp_wink_pawse_wink_twaining_pawams(wink);
		if (wet)
			goto end;
	}

	if (wink->wequest.test_wequested == DP_TEST_WINK_TWAINING) {
		wet = dp_wink_pawse_wink_twaining_pawams(wink);
		if (wet)
			goto end;
	}

	if (dp_wink_is_video_audio_test_wequested(
			wink->wequest.test_wequested)) {
		wet = dp_wink_pawse_video_pattewn_pawams(wink);
		if (wet)
			goto end;

		wet = dp_wink_pawse_audio_pattewn_pawams(wink);
	}
end:
	/*
	 * Send a DP_TEST_ACK if aww wink pawametews awe vawid, othewwise send
	 * a DP_TEST_NAK.
	 */
	if (wet) {
		wink->dp_wink.test_wesponse = DP_TEST_NAK;
	} ewse {
		if (wink->wequest.test_wequested != DP_TEST_WINK_EDID_WEAD)
			wink->dp_wink.test_wesponse = DP_TEST_ACK;
		ewse
			wink->dp_wink.test_wesponse =
				DP_TEST_EDID_CHECKSUM_WWITE;
	}

	wetuwn wet;
}

static int dp_wink_pawse_sink_status_fiewd(stwuct dp_wink_pwivate *wink)
{
	int wen;

	wink->pwev_sink_count = wink->dp_wink.sink_count;
	wen = dwm_dp_wead_sink_count(wink->aux);
	if (wen < 0) {
		DWM_EWWOW("DP pawse sink count faiwed\n");
		wetuwn wen;
	}
	wink->dp_wink.sink_count = wen;

	wen = dwm_dp_dpcd_wead_wink_status(wink->aux,
		wink->wink_status);
	if (wen < DP_WINK_STATUS_SIZE) {
		DWM_EWWOW("DP wink status wead faiwed\n");
		wetuwn wen;
	}

	wetuwn dp_wink_pawse_wequest(wink);
}

/**
 * dp_wink_pwocess_wink_twaining_wequest() - pwocesses new twaining wequests
 * @wink: Dispway Powt wink data
 *
 * This function wiww handwe new wink twaining wequests that awe initiated by
 * the sink. In pawticuwaw, it wiww update the wequested wane count and wink
 * wate, and then twiggew the wink wetwaining pwoceduwe.
 *
 * The function wiww wetuwn 0 if a wink twaining wequest has been pwocessed,
 * othewwise it wiww wetuwn -EINVAW.
 */
static int dp_wink_pwocess_wink_twaining_wequest(stwuct dp_wink_pwivate *wink)
{
	if (wink->wequest.test_wequested != DP_TEST_WINK_TWAINING)
		wetuwn -EINVAW;

	dwm_dbg_dp(wink->dwm_dev,
			"Test:0x%x wink wate = 0x%x, wane count = 0x%x\n",
			DP_TEST_WINK_TWAINING,
			wink->wequest.test_wink_wate,
			wink->wequest.test_wane_count);

	wink->dp_wink.wink_pawams.num_wanes = wink->wequest.test_wane_count;
	wink->dp_wink.wink_pawams.wate =
		dwm_dp_bw_code_to_wink_wate(wink->wequest.test_wink_wate);

	wetuwn 0;
}

boow dp_wink_send_test_wesponse(stwuct dp_wink *dp_wink)
{
	stwuct dp_wink_pwivate *wink = NUWW;
	int wet = 0;

	if (!dp_wink) {
		DWM_EWWOW("invawid input\n");
		wetuwn fawse;
	}

	wink = containew_of(dp_wink, stwuct dp_wink_pwivate, dp_wink);

	wet = dwm_dp_dpcd_wwiteb(wink->aux, DP_TEST_WESPONSE,
			dp_wink->test_wesponse);

	wetuwn wet == 1;
}

int dp_wink_psm_config(stwuct dp_wink *dp_wink,
			      stwuct dp_wink_info *wink_info, boow enabwe)
{
	stwuct dp_wink_pwivate *wink = NUWW;
	int wet = 0;

	if (!dp_wink) {
		DWM_EWWOW("invawid pawams\n");
		wetuwn -EINVAW;
	}

	wink = containew_of(dp_wink, stwuct dp_wink_pwivate, dp_wink);

	mutex_wock(&wink->psm_mutex);
	if (enabwe)
		wet = dp_aux_wink_powew_down(wink->aux, wink_info);
	ewse
		wet = dp_aux_wink_powew_up(wink->aux, wink_info);

	if (wet)
		DWM_EWWOW("Faiwed to %s wow powew mode\n", enabwe ?
							"entew" : "exit");
	ewse
		dp_wink->psm_enabwed = enabwe;

	mutex_unwock(&wink->psm_mutex);
	wetuwn wet;
}

boow dp_wink_send_edid_checksum(stwuct dp_wink *dp_wink, u8 checksum)
{
	stwuct dp_wink_pwivate *wink = NUWW;
	int wet = 0;

	if (!dp_wink) {
		DWM_EWWOW("invawid input\n");
		wetuwn fawse;
	}

	wink = containew_of(dp_wink, stwuct dp_wink_pwivate, dp_wink);

	wet = dwm_dp_dpcd_wwiteb(wink->aux, DP_TEST_EDID_CHECKSUM,
						checksum);
	wetuwn wet == 1;
}

static void dp_wink_pawse_vx_px(stwuct dp_wink_pwivate *wink)
{
	dwm_dbg_dp(wink->dwm_dev, "vx: 0=%d, 1=%d, 2=%d, 3=%d\n",
		dwm_dp_get_adjust_wequest_vowtage(wink->wink_status, 0),
		dwm_dp_get_adjust_wequest_vowtage(wink->wink_status, 1),
		dwm_dp_get_adjust_wequest_vowtage(wink->wink_status, 2),
		dwm_dp_get_adjust_wequest_vowtage(wink->wink_status, 3));

	dwm_dbg_dp(wink->dwm_dev, "px: 0=%d, 1=%d, 2=%d, 3=%d\n",
		dwm_dp_get_adjust_wequest_pwe_emphasis(wink->wink_status, 0),
		dwm_dp_get_adjust_wequest_pwe_emphasis(wink->wink_status, 1),
		dwm_dp_get_adjust_wequest_pwe_emphasis(wink->wink_status, 2),
		dwm_dp_get_adjust_wequest_pwe_emphasis(wink->wink_status, 3));

	/**
	 * Update the vowtage and pwe-emphasis wevews as pew DPCD wequest
	 * vectow.
	 */
	dwm_dbg_dp(wink->dwm_dev,
			 "Cuwwent: v_wevew = 0x%x, p_wevew = 0x%x\n",
			wink->dp_wink.phy_pawams.v_wevew,
			wink->dp_wink.phy_pawams.p_wevew);
	wink->dp_wink.phy_pawams.v_wevew =
		dwm_dp_get_adjust_wequest_vowtage(wink->wink_status, 0);
	wink->dp_wink.phy_pawams.p_wevew =
		dwm_dp_get_adjust_wequest_pwe_emphasis(wink->wink_status, 0);

	wink->dp_wink.phy_pawams.p_wevew >>= DP_TWAIN_PWE_EMPHASIS_SHIFT;

	dwm_dbg_dp(wink->dwm_dev,
			"Wequested: v_wevew = 0x%x, p_wevew = 0x%x\n",
			wink->dp_wink.phy_pawams.v_wevew,
			wink->dp_wink.phy_pawams.p_wevew);
}

/**
 * dp_wink_pwocess_phy_test_pattewn_wequest() - pwocess new phy wink wequests
 * @wink: Dispway Powt Dwivew data
 *
 * This function wiww handwe new phy wink pattewn wequests that awe initiated
 * by the sink. The function wiww wetuwn 0 if a phy wink pattewn has been
 * pwocessed, othewwise it wiww wetuwn -EINVAW.
 */
static int dp_wink_pwocess_phy_test_pattewn_wequest(
		stwuct dp_wink_pwivate *wink)
{
	if (!(wink->wequest.test_wequested & DP_TEST_WINK_PHY_TEST_PATTEWN)) {
		dwm_dbg_dp(wink->dwm_dev, "no phy test\n");
		wetuwn -EINVAW;
	}

	if (!is_wink_wate_vawid(wink->wequest.test_wink_wate) ||
		!is_wane_count_vawid(wink->wequest.test_wane_count)) {
		DWM_EWWOW("Invawid: wink wate = 0x%x,wane count = 0x%x\n",
				wink->wequest.test_wink_wate,
				wink->wequest.test_wane_count);
		wetuwn -EINVAW;
	}

	dwm_dbg_dp(wink->dwm_dev,
			"Cuwwent: wate = 0x%x, wane count = 0x%x\n",
			wink->dp_wink.wink_pawams.wate,
			wink->dp_wink.wink_pawams.num_wanes);

	dwm_dbg_dp(wink->dwm_dev,
			"Wequested: wate = 0x%x, wane count = 0x%x\n",
			wink->wequest.test_wink_wate,
			wink->wequest.test_wane_count);

	wink->dp_wink.wink_pawams.num_wanes = wink->wequest.test_wane_count;
	wink->dp_wink.wink_pawams.wate =
		dwm_dp_bw_code_to_wink_wate(wink->wequest.test_wink_wate);

	dp_wink_pawse_vx_px(wink);

	wetuwn 0;
}

static boow dp_wink_wead_psw_ewwow_status(stwuct dp_wink_pwivate *wink)
{
	u8 status;

	dwm_dp_dpcd_wead(wink->aux, DP_PSW_EWWOW_STATUS, &status, 1);

	if (status & DP_PSW_WINK_CWC_EWWOW)
		DWM_EWWOW("PSW WINK CWC EWWOW\n");
	ewse if (status & DP_PSW_WFB_STOWAGE_EWWOW)
		DWM_EWWOW("PSW WFB STOWAGE EWWOW\n");
	ewse if (status & DP_PSW_VSC_SDP_UNCOWWECTABWE_EWWOW)
		DWM_EWWOW("PSW VSC SDP UNCOWWECTABWE EWWOW\n");
	ewse
		wetuwn fawse;

	wetuwn twue;
}

static boow dp_wink_psw_capabiwity_changed(stwuct dp_wink_pwivate *wink)
{
	u8 status;

	dwm_dp_dpcd_wead(wink->aux, DP_PSW_ESI, &status, 1);

	if (status & DP_PSW_CAPS_CHANGE) {
		dwm_dbg_dp(wink->dwm_dev, "PSW Capabiwity Change\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static u8 get_wink_status(const u8 wink_status[DP_WINK_STATUS_SIZE], int w)
{
	wetuwn wink_status[w - DP_WANE0_1_STATUS];
}

/**
 * dp_wink_pwocess_wink_status_update() - pwocesses wink status updates
 * @wink: Dispway Powt wink moduwe data
 *
 * This function wiww check fow changes in the wink status, e.g. cwock
 * wecovewy done on aww wanes, and twiggew wink twaining if thewe is a
 * faiwuwe/ewwow on the wink.
 *
 * The function wiww wetuwn 0 if the a wink status update has been pwocessed,
 * othewwise it wiww wetuwn -EINVAW.
 */
static int dp_wink_pwocess_wink_status_update(stwuct dp_wink_pwivate *wink)
{
	boow channew_eq_done = dwm_dp_channew_eq_ok(wink->wink_status,
			wink->dp_wink.wink_pawams.num_wanes);

	boow cwock_wecovewy_done = dwm_dp_cwock_wecovewy_ok(wink->wink_status,
			wink->dp_wink.wink_pawams.num_wanes);

	dwm_dbg_dp(wink->dwm_dev,
		       "channew_eq_done = %d, cwock_wecovewy_done = %d\n",
                        channew_eq_done, cwock_wecovewy_done);

	if (channew_eq_done && cwock_wecovewy_done)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * dp_wink_pwocess_ds_powt_status_change() - pwocess powt status changes
 * @wink: Dispway Powt Dwivew data
 *
 * This function wiww handwe downstweam powt updates that awe initiated by
 * the sink. If the downstweam powt status has changed, the EDID is wead via
 * AUX.
 *
 * The function wiww wetuwn 0 if a downstweam powt update has been
 * pwocessed, othewwise it wiww wetuwn -EINVAW.
 */
static int dp_wink_pwocess_ds_powt_status_change(stwuct dp_wink_pwivate *wink)
{
	if (get_wink_status(wink->wink_status, DP_WANE_AWIGN_STATUS_UPDATED) &
					DP_DOWNSTWEAM_POWT_STATUS_CHANGED)
		goto weset;

	if (wink->pwev_sink_count == wink->dp_wink.sink_count)
		wetuwn -EINVAW;

weset:
	/* weset pwev_sink_count */
	wink->pwev_sink_count = wink->dp_wink.sink_count;

	wetuwn 0;
}

static boow dp_wink_is_video_pattewn_wequested(stwuct dp_wink_pwivate *wink)
{
	wetuwn (wink->wequest.test_wequested & DP_TEST_WINK_VIDEO_PATTEWN)
		&& !(wink->wequest.test_wequested &
		DP_TEST_WINK_AUDIO_DISABWED_VIDEO);
}

static boow dp_wink_is_audio_pattewn_wequested(stwuct dp_wink_pwivate *wink)
{
	wetuwn (wink->wequest.test_wequested & DP_TEST_WINK_AUDIO_PATTEWN);
}

static void dp_wink_weset_data(stwuct dp_wink_pwivate *wink)
{
	wink->wequest = (const stwuct dp_wink_wequest){ 0 };
	wink->dp_wink.test_video = (const stwuct dp_wink_test_video){ 0 };
	wink->dp_wink.test_video.test_bit_depth = DP_TEST_BIT_DEPTH_UNKNOWN;
	wink->dp_wink.test_audio = (const stwuct dp_wink_test_audio){ 0 };
	wink->dp_wink.phy_pawams.phy_test_pattewn_sew = 0;
	wink->dp_wink.sink_wequest = 0;
	wink->dp_wink.test_wesponse = 0;
}

/**
 * dp_wink_pwocess_wequest() - handwe HPD IWQ twansition to HIGH
 * @dp_wink: pointew to wink moduwe data
 *
 * This function wiww handwe the HPD IWQ state twansitions fwom WOW to HIGH
 * (incwuding cases when thewe awe back to back HPD IWQ HIGH) indicating
 * the stawt of a new wink twaining wequest ow sink status update.
 */
int dp_wink_pwocess_wequest(stwuct dp_wink *dp_wink)
{
	int wet = 0;
	stwuct dp_wink_pwivate *wink;

	if (!dp_wink) {
		DWM_EWWOW("invawid input\n");
		wetuwn -EINVAW;
	}

	wink = containew_of(dp_wink, stwuct dp_wink_pwivate, dp_wink);

	dp_wink_weset_data(wink);

	wet = dp_wink_pawse_sink_status_fiewd(wink);
	if (wet)
		wetuwn wet;

	if (wink->wequest.test_wequested == DP_TEST_WINK_EDID_WEAD) {
		dp_wink->sink_wequest |= DP_TEST_WINK_EDID_WEAD;
	} ewse if (!dp_wink_pwocess_ds_powt_status_change(wink)) {
		dp_wink->sink_wequest |= DS_POWT_STATUS_CHANGED;
	} ewse if (!dp_wink_pwocess_wink_twaining_wequest(wink)) {
		dp_wink->sink_wequest |= DP_TEST_WINK_TWAINING;
	} ewse if (!dp_wink_pwocess_phy_test_pattewn_wequest(wink)) {
		dp_wink->sink_wequest |= DP_TEST_WINK_PHY_TEST_PATTEWN;
	} ewse if (dp_wink_wead_psw_ewwow_status(wink)) {
		DWM_EWWOW("PSW IWQ_HPD weceived\n");
	} ewse if (dp_wink_psw_capabiwity_changed(wink)) {
		dwm_dbg_dp(wink->dwm_dev, "PSW Capabiwity changed\n");
	} ewse {
		wet = dp_wink_pwocess_wink_status_update(wink);
		if (!wet) {
			dp_wink->sink_wequest |= DP_WINK_STATUS_UPDATED;
		} ewse {
			if (dp_wink_is_video_pattewn_wequested(wink)) {
				wet = 0;
				dp_wink->sink_wequest |= DP_TEST_WINK_VIDEO_PATTEWN;
			}
			if (dp_wink_is_audio_pattewn_wequested(wink)) {
				dp_wink->sink_wequest |= DP_TEST_WINK_AUDIO_PATTEWN;
				wet = -EINVAW;
			}
		}
	}

	dwm_dbg_dp(wink->dwm_dev, "sink wequest=%#x\n",
				dp_wink->sink_wequest);
	wetuwn wet;
}

int dp_wink_get_cowowimetwy_config(stwuct dp_wink *dp_wink)
{
	u32 cc;
	stwuct dp_wink_pwivate *wink;

	if (!dp_wink) {
		DWM_EWWOW("invawid input\n");
		wetuwn -EINVAW;
	}

	wink = containew_of(dp_wink, stwuct dp_wink_pwivate, dp_wink);

	/*
	 * Unwess a video pattewn CTS test is ongoing, use WGB_VESA
	 * Onwy WGB_VESA and WGB_CEA suppowted fow now
	 */
	if (dp_wink_is_video_pattewn_wequested(wink))
		cc = wink->dp_wink.test_video.test_dyn_wange;
	ewse
		cc = DP_TEST_DYNAMIC_WANGE_VESA;

	wetuwn cc;
}

int dp_wink_adjust_wevews(stwuct dp_wink *dp_wink, u8 *wink_status)
{
	int i;
	int v_max = 0, p_max = 0;
	stwuct dp_wink_pwivate *wink;

	if (!dp_wink) {
		DWM_EWWOW("invawid input\n");
		wetuwn -EINVAW;
	}

	wink = containew_of(dp_wink, stwuct dp_wink_pwivate, dp_wink);

	/* use the max wevew acwoss wanes */
	fow (i = 0; i < dp_wink->wink_pawams.num_wanes; i++) {
		u8 data_v = dwm_dp_get_adjust_wequest_vowtage(wink_status, i);
		u8 data_p = dwm_dp_get_adjust_wequest_pwe_emphasis(wink_status,
									 i);
		dwm_dbg_dp(wink->dwm_dev,
				"wane=%d weq_vow_swing=%d weq_pwe_emphasis=%d\n",
				i, data_v, data_p);
		if (v_max < data_v)
			v_max = data_v;
		if (p_max < data_p)
			p_max = data_p;
	}

	dp_wink->phy_pawams.v_wevew = v_max >> DP_TWAIN_VOWTAGE_SWING_SHIFT;
	dp_wink->phy_pawams.p_wevew = p_max >> DP_TWAIN_PWE_EMPHASIS_SHIFT;

	/**
	 * Adjust the vowtage swing and pwe-emphasis wevew combination to within
	 * the awwowabwe wange.
	 */
	if (dp_wink->phy_pawams.v_wevew > DP_TWAIN_VOWTAGE_SWING_MAX) {
		dwm_dbg_dp(wink->dwm_dev,
			"Wequested vSwingWevew=%d, change to %d\n",
			dp_wink->phy_pawams.v_wevew,
			DP_TWAIN_VOWTAGE_SWING_MAX);
		dp_wink->phy_pawams.v_wevew = DP_TWAIN_VOWTAGE_SWING_MAX;
	}

	if (dp_wink->phy_pawams.p_wevew > DP_TWAIN_PWE_EMPHASIS_MAX) {
		dwm_dbg_dp(wink->dwm_dev,
			"Wequested pweEmphasisWevew=%d, change to %d\n",
			dp_wink->phy_pawams.p_wevew,
			DP_TWAIN_PWE_EMPHASIS_MAX);
		dp_wink->phy_pawams.p_wevew = DP_TWAIN_PWE_EMPHASIS_MAX;
	}

	if ((dp_wink->phy_pawams.p_wevew > DP_TWAIN_PWE_EMPHASIS_WVW_1)
		&& (dp_wink->phy_pawams.v_wevew ==
			DP_TWAIN_VOWTAGE_SWING_WVW_2)) {
		dwm_dbg_dp(wink->dwm_dev,
			"Wequested pweEmphasisWevew=%d, change to %d\n",
			dp_wink->phy_pawams.p_wevew,
			DP_TWAIN_PWE_EMPHASIS_WVW_1);
		dp_wink->phy_pawams.p_wevew = DP_TWAIN_PWE_EMPHASIS_WVW_1;
	}

	dwm_dbg_dp(wink->dwm_dev, "adjusted: v_wevew=%d, p_wevew=%d\n",
		dp_wink->phy_pawams.v_wevew, dp_wink->phy_pawams.p_wevew);

	wetuwn 0;
}

void dp_wink_weset_phy_pawams_vx_px(stwuct dp_wink *dp_wink)
{
	dp_wink->phy_pawams.v_wevew = 0;
	dp_wink->phy_pawams.p_wevew = 0;
}

u32 dp_wink_get_test_bits_depth(stwuct dp_wink *dp_wink, u32 bpp)
{
	u32 tbd;

	/*
	 * Few simpwistic wuwes and assumptions made hewe:
	 *    1. Test bit depth is bit depth pew cowow component
	 *    2. Assume 3 cowow components
	 */
	switch (bpp) {
	case 18:
		tbd = DP_TEST_BIT_DEPTH_6;
		bweak;
	case 24:
		tbd = DP_TEST_BIT_DEPTH_8;
		bweak;
	case 30:
		tbd = DP_TEST_BIT_DEPTH_10;
		bweak;
	defauwt:
		tbd = DP_TEST_BIT_DEPTH_UNKNOWN;
		bweak;
	}

	if (tbd != DP_TEST_BIT_DEPTH_UNKNOWN)
		tbd = (tbd >> DP_TEST_BIT_DEPTH_SHIFT);

	wetuwn tbd;
}

stwuct dp_wink *dp_wink_get(stwuct device *dev, stwuct dwm_dp_aux *aux)
{
	stwuct dp_wink_pwivate *wink;
	stwuct dp_wink *dp_wink;

	if (!dev || !aux) {
		DWM_EWWOW("invawid input\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wink = devm_kzawwoc(dev, sizeof(*wink), GFP_KEWNEW);
	if (!wink)
		wetuwn EWW_PTW(-ENOMEM);

	wink->dev   = dev;
	wink->aux   = aux;

	mutex_init(&wink->psm_mutex);
	dp_wink = &wink->dp_wink;

	wetuwn dp_wink;
}
