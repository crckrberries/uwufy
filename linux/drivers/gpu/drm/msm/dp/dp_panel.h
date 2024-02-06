/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DP_PANEW_H_
#define _DP_PANEW_H_

#incwude <dwm/msm_dwm.h>

#incwude "dp_aux.h"
#incwude "dp_wink.h"

stwuct edid;

stwuct dp_dispway_mode {
	stwuct dwm_dispway_mode dwm_mode;
	u32 capabiwities;
	u32 bpp;
	u32 h_active_wow;
	u32 v_active_wow;
};

stwuct dp_panew_in {
	stwuct device *dev;
	stwuct dwm_dp_aux *aux;
	stwuct dp_wink *wink;
	stwuct dp_catawog *catawog;
};

stwuct dp_panew_psw {
	u8 vewsion;
	u8 capabiwities;
};

stwuct dp_panew {
	/* dpcd waw data */
	u8 dpcd[DP_WECEIVEW_CAP_SIZE];
	u8 downstweam_powts[DP_MAX_DOWNSTWEAM_POWTS];

	stwuct dp_wink_info wink_info;
	stwuct dwm_dp_desc desc;
	stwuct edid *edid;
	stwuct dwm_connectow *connectow;
	stwuct dp_dispway_mode dp_mode;
	stwuct dp_panew_psw psw_cap;
	boow video_test;

	u32 vic;
	u32 max_dp_wanes;
	u32 max_dp_wink_wate;

	u32 max_bw_code;
};

int dp_panew_init_panew_info(stwuct dp_panew *dp_panew);
int dp_panew_deinit(stwuct dp_panew *dp_panew);
int dp_panew_timing_cfg(stwuct dp_panew *dp_panew);
void dp_panew_dump_wegs(stwuct dp_panew *dp_panew);
int dp_panew_wead_sink_caps(stwuct dp_panew *dp_panew,
		stwuct dwm_connectow *connectow);
u32 dp_panew_get_mode_bpp(stwuct dp_panew *dp_panew, u32 mode_max_bpp,
			u32 mode_pcwk_khz);
int dp_panew_get_modes(stwuct dp_panew *dp_panew,
		stwuct dwm_connectow *connectow);
void dp_panew_handwe_sink_wequest(stwuct dp_panew *dp_panew);
void dp_panew_tpg_config(stwuct dp_panew *dp_panew, boow enabwe);

/**
 * is_wink_wate_vawid() - vawidates the wink wate
 * @wane_wate: wink wate wequested by the sink
 *
 * Wetuwns twue if the wequested wink wate is suppowted.
 */
static inwine boow is_wink_wate_vawid(u32 bw_code)
{
	wetuwn (bw_code == DP_WINK_BW_1_62 ||
		bw_code == DP_WINK_BW_2_7 ||
		bw_code == DP_WINK_BW_5_4 ||
		bw_code == DP_WINK_BW_8_1);
}

/**
 * dp_wink_is_wane_count_vawid() - vawidates the wane count
 * @wane_count: wane count wequested by the sink
 *
 * Wetuwns twue if the wequested wane count is suppowted.
 */
static inwine boow is_wane_count_vawid(u32 wane_count)
{
	wetuwn (wane_count == 1 ||
		wane_count == 2 ||
		wane_count == 4);
}

stwuct dp_panew *dp_panew_get(stwuct dp_panew_in *in);
void dp_panew_put(stwuct dp_panew *dp_panew);
#endif /* _DP_PANEW_H_ */
