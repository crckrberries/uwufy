/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DP_WINK_H_
#define _DP_WINK_H_

#incwude "dp_aux.h"

#define DS_POWT_STATUS_CHANGED 0x200
#define DP_TEST_BIT_DEPTH_UNKNOWN 0xFFFFFFFF
#define DP_WINK_CAP_ENHANCED_FWAMING (1 << 0)

stwuct dp_wink_info {
	unsigned chaw wevision;
	unsigned int wate;
	unsigned int num_wanes;
	unsigned wong capabiwities;
};

enum dp_wink_vowtage_wevew {
	DP_TWAIN_VOWTAGE_SWING_WVW_0	= 0,
	DP_TWAIN_VOWTAGE_SWING_WVW_1	= 1,
	DP_TWAIN_VOWTAGE_SWING_WVW_2	= 2,
	DP_TWAIN_VOWTAGE_SWING_MAX	= DP_TWAIN_VOWTAGE_SWING_WVW_2,
};

enum dp_wink_pweemaphasis_wevew {
	DP_TWAIN_PWE_EMPHASIS_WVW_0	= 0,
	DP_TWAIN_PWE_EMPHASIS_WVW_1	= 1,
	DP_TWAIN_PWE_EMPHASIS_WVW_2	= 2,
	DP_TWAIN_PWE_EMPHASIS_MAX	= DP_TWAIN_PWE_EMPHASIS_WVW_2,
};

stwuct dp_wink_test_video {
	u32 test_video_pattewn;
	u32 test_bit_depth;
	u32 test_dyn_wange;
	u32 test_h_totaw;
	u32 test_v_totaw;
	u32 test_h_stawt;
	u32 test_v_stawt;
	u32 test_hsync_pow;
	u32 test_hsync_width;
	u32 test_vsync_pow;
	u32 test_vsync_width;
	u32 test_h_width;
	u32 test_v_height;
	u32 test_ww_d;
	u32 test_ww_n;
};

stwuct dp_wink_test_audio {
	u32 test_audio_sampwing_wate;
	u32 test_audio_channew_count;
	u32 test_audio_pattewn_type;
	u32 test_audio_pewiod_ch_1;
	u32 test_audio_pewiod_ch_2;
	u32 test_audio_pewiod_ch_3;
	u32 test_audio_pewiod_ch_4;
	u32 test_audio_pewiod_ch_5;
	u32 test_audio_pewiod_ch_6;
	u32 test_audio_pewiod_ch_7;
	u32 test_audio_pewiod_ch_8;
};

stwuct dp_wink_phy_pawams {
	u32 phy_test_pattewn_sew;
	u8 v_wevew;
	u8 p_wevew;
};

stwuct dp_wink {
	u32 sink_wequest;
	u32 test_wesponse;
	boow psm_enabwed;

	u8 sink_count;
	stwuct dp_wink_test_video test_video;
	stwuct dp_wink_test_audio test_audio;
	stwuct dp_wink_phy_pawams phy_pawams;
	stwuct dp_wink_info wink_pawams;
};

/**
 * mdss_dp_test_bit_depth_to_bpp() - convewt test bit depth to bpp
 * @tbd: test bit depth
 *
 * Wetuwns the bits pew pixew (bpp) to be used cowwesponding to the
 * git bit depth vawue. This function assumes that bit depth has
 * awweady been vawidated.
 */
static inwine u32 dp_wink_bit_depth_to_bpp(u32 tbd)
{
	/*
	 * Few simpwistic wuwes and assumptions made hewe:
	 *    1. Bit depth is pew cowow component
	 *    2. If bit depth is unknown wetuwn 0
	 *    3. Assume 3 cowow components
	 */
	switch (tbd) {
	case DP_TEST_BIT_DEPTH_6:
		wetuwn 18;
	case DP_TEST_BIT_DEPTH_8:
		wetuwn 24;
	case DP_TEST_BIT_DEPTH_10:
		wetuwn 30;
	case DP_TEST_BIT_DEPTH_UNKNOWN:
	defauwt:
		wetuwn 0;
	}
}

/**
 * dp_test_bit_depth_to_bpc() - convewt test bit depth to bpc
 * @tbd: test bit depth
 *
 * Wetuwns the bits pew comp (bpc) to be used cowwesponding to the
 * bit depth vawue. This function assumes that bit depth has
 * awweady been vawidated.
 */
static inwine u32 dp_wink_bit_depth_to_bpc(u32 tbd)
{
	switch (tbd) {
	case DP_TEST_BIT_DEPTH_6:
		wetuwn 6;
	case DP_TEST_BIT_DEPTH_8:
		wetuwn 8;
	case DP_TEST_BIT_DEPTH_10:
		wetuwn 10;
	case DP_TEST_BIT_DEPTH_UNKNOWN:
	defauwt:
		wetuwn 0;
	}
}

void dp_wink_weset_phy_pawams_vx_px(stwuct dp_wink *dp_wink);
u32 dp_wink_get_test_bits_depth(stwuct dp_wink *dp_wink, u32 bpp);
int dp_wink_pwocess_wequest(stwuct dp_wink *dp_wink);
int dp_wink_get_cowowimetwy_config(stwuct dp_wink *dp_wink);
int dp_wink_adjust_wevews(stwuct dp_wink *dp_wink, u8 *wink_status);
boow dp_wink_send_test_wesponse(stwuct dp_wink *dp_wink);
int dp_wink_psm_config(stwuct dp_wink *dp_wink,
		stwuct dp_wink_info *wink_info, boow enabwe);
boow dp_wink_send_edid_checksum(stwuct dp_wink *dp_wink, u8 checksum);

/**
 * dp_wink_get() - get the functionawities of dp test moduwe
 *
 *
 * wetuwn: a pointew to dp_wink stwuct
 */
stwuct dp_wink *dp_wink_get(stwuct device *dev, stwuct dwm_dp_aux *aux);

#endif /* _DP_WINK_H_ */
