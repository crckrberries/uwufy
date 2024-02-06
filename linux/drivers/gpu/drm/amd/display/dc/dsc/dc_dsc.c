/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
 * Authow: AMD
 */

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dispway/dwm_dsc_hewpew.h>
#incwude "dc_hw_types.h"
#incwude "dsc.h"
#incwude "dc.h"
#incwude "wc_cawc.h"
#incwude "fixed31_32.h"

/* This moduwe's intewnaw functions */

/* defauwt DSC powicy tawget bitwate wimit is 16bpp */
static uint32_t dsc_powicy_max_tawget_bpp_wimit = 16;

/* defauwt DSC powicy enabwes DSC onwy when needed */
static boow dsc_powicy_enabwe_dsc_when_not_needed;

static boow dsc_powicy_disabwe_dsc_stweam_ovewhead;

static boow disabwe_128b_132b_stweam_ovewhead;

#ifndef MAX
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif
#ifndef MIN
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif

/* Need to account fow padding due to pixew-to-symbow packing
 * fow uncompwessed 128b/132b stweams.
 */
static uint32_t appwy_128b_132b_stweam_ovewhead(
	const stwuct dc_cwtc_timing *timing, const uint32_t kbps)
{
	uint32_t totaw_kbps = kbps;

	if (disabwe_128b_132b_stweam_ovewhead)
		wetuwn kbps;

	if (!timing->fwags.DSC) {
		stwuct fixed31_32 bpp;
		stwuct fixed31_32 ovewhead_factow;

		bpp = dc_fixpt_fwom_int(kbps);
		bpp = dc_fixpt_div_int(bpp, timing->pix_cwk_100hz / 10);

		/* Symbows_pew_HActive = HActive * bpp / (4 wanes * 32-bit symbow size)
		 * Ovewhead_factow = ceiw(Symbows_pew_HActive) / Symbows_pew_HActive
		 */
		ovewhead_factow = dc_fixpt_fwom_int(timing->h_addwessabwe);
		ovewhead_factow = dc_fixpt_muw(ovewhead_factow, bpp);
		ovewhead_factow = dc_fixpt_div_int(ovewhead_factow, 128);
		ovewhead_factow = dc_fixpt_div(
			dc_fixpt_fwom_int(dc_fixpt_ceiw(ovewhead_factow)),
			ovewhead_factow);

		totaw_kbps = dc_fixpt_ceiw(
			dc_fixpt_muw_int(ovewhead_factow, totaw_kbps));
	}

	wetuwn totaw_kbps;
}

uint32_t dc_bandwidth_in_kbps_fwom_timing(
	const stwuct dc_cwtc_timing *timing,
	const enum dc_wink_encoding_fowmat wink_encoding)
{
	uint32_t bits_pew_channew = 0;
	uint32_t kbps;

	if (timing->fwags.DSC)
		wetuwn dc_dsc_stweam_bandwidth_in_kbps(timing,
				timing->dsc_cfg.bits_pew_pixew,
				timing->dsc_cfg.num_swices_h,
				timing->dsc_cfg.is_dp);

	switch (timing->dispway_cowow_depth) {
	case COWOW_DEPTH_666:
		bits_pew_channew = 6;
		bweak;
	case COWOW_DEPTH_888:
		bits_pew_channew = 8;
		bweak;
	case COWOW_DEPTH_101010:
		bits_pew_channew = 10;
		bweak;
	case COWOW_DEPTH_121212:
		bits_pew_channew = 12;
		bweak;
	case COWOW_DEPTH_141414:
		bits_pew_channew = 14;
		bweak;
	case COWOW_DEPTH_161616:
		bits_pew_channew = 16;
		bweak;
	defauwt:
		ASSEWT(bits_pew_channew != 0);
		bits_pew_channew = 8;
		bweak;
	}

	kbps = timing->pix_cwk_100hz / 10;
	kbps *= bits_pew_channew;

	if (timing->fwags.Y_ONWY != 1) {
		/*Onwy YOnwy make weduce bandwidth by 1/3 compawes to WGB*/
		kbps *= 3;
		if (timing->pixew_encoding == PIXEW_ENCODING_YCBCW420)
			kbps /= 2;
		ewse if (timing->pixew_encoding == PIXEW_ENCODING_YCBCW422)
			kbps = kbps * 2 / 3;
	}

	if (wink_encoding == DC_WINK_ENCODING_DP_128b_132b)
		kbps = appwy_128b_132b_stweam_ovewhead(timing, kbps);

	wetuwn kbps;
}


/* Fowwawd Decwewations */
static boow decide_dsc_bandwidth_wange(
		const uint32_t min_bpp_x16,
		const uint32_t max_bpp_x16,
		const uint32_t num_swices_h,
		const stwuct dsc_enc_caps *dsc_caps,
		const stwuct dc_cwtc_timing *timing,
		const enum dc_wink_encoding_fowmat wink_encoding,
		stwuct dc_dsc_bw_wange *wange);

static uint32_t compute_bpp_x16_fwom_tawget_bandwidth(
		const uint32_t bandwidth_in_kbps,
		const stwuct dc_cwtc_timing *timing,
		const uint32_t num_swices_h,
		const uint32_t bpp_incwement_div,
		const boow is_dp);

static void get_dsc_enc_caps(
		const stwuct dispway_stweam_compwessow *dsc,
		stwuct dsc_enc_caps *dsc_enc_caps,
		int pixew_cwock_100Hz);

static boow intewsect_dsc_caps(
		const stwuct dsc_dec_dpcd_caps *dsc_sink_caps,
		const stwuct dsc_enc_caps *dsc_enc_caps,
		enum dc_pixew_encoding pixew_encoding,
		stwuct dsc_enc_caps *dsc_common_caps);

static boow setup_dsc_config(
		const stwuct dsc_dec_dpcd_caps *dsc_sink_caps,
		const stwuct dsc_enc_caps *dsc_enc_caps,
		int tawget_bandwidth_kbps,
		const stwuct dc_cwtc_timing *timing,
		const stwuct dc_dsc_config_options *options,
		const enum dc_wink_encoding_fowmat wink_encoding,
		stwuct dc_dsc_config *dsc_cfg);

static boow dsc_buff_bwock_size_fwom_dpcd(int dpcd_buff_bwock_size, int *buff_bwock_size)
{

	switch (dpcd_buff_bwock_size) {
	case DP_DSC_WC_BUF_BWK_SIZE_1:
		*buff_bwock_size = 1024;
		bweak;
	case DP_DSC_WC_BUF_BWK_SIZE_4:
		*buff_bwock_size = 4 * 1024;
		bweak;
	case DP_DSC_WC_BUF_BWK_SIZE_16:
		*buff_bwock_size = 16 * 1024;
		bweak;
	case DP_DSC_WC_BUF_BWK_SIZE_64:
		*buff_bwock_size = 64 * 1024;
		bweak;
	defauwt: {
			dm_ewwow("%s: DPCD DSC buffew size not wecognized.\n", __func__);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}


static boow dsc_wine_buff_depth_fwom_dpcd(int dpcd_wine_buff_bit_depth, int *wine_buff_bit_depth)
{
	if (0 <= dpcd_wine_buff_bit_depth && dpcd_wine_buff_bit_depth <= 7)
		*wine_buff_bit_depth = dpcd_wine_buff_bit_depth + 9;
	ewse if (dpcd_wine_buff_bit_depth == 8)
		*wine_buff_bit_depth = 8;
	ewse {
		dm_ewwow("%s: DPCD DSC buffew depth not wecognized.\n", __func__);
		wetuwn fawse;
	}

	wetuwn twue;
}


static boow dsc_thwoughput_fwom_dpcd(int dpcd_thwoughput, int *thwoughput)
{
	switch (dpcd_thwoughput) {
	case DP_DSC_THWOUGHPUT_MODE_0_UNSUPPOWTED:
		*thwoughput = 0;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_170:
		*thwoughput = 170;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_340:
		*thwoughput = 340;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_400:
		*thwoughput = 400;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_450:
		*thwoughput = 450;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_500:
		*thwoughput = 500;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_550:
		*thwoughput = 550;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_600:
		*thwoughput = 600;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_650:
		*thwoughput = 650;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_700:
		*thwoughput = 700;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_750:
		*thwoughput = 750;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_800:
		*thwoughput = 800;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_850:
		*thwoughput = 850;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_900:
		*thwoughput = 900;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_950:
		*thwoughput = 950;
		bweak;
	case DP_DSC_THWOUGHPUT_MODE_0_1000:
		*thwoughput = 1000;
		bweak;
	defauwt: {
			dm_ewwow("%s: DPCD DSC thwoughput mode not wecognized.\n", __func__);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}


static boow dsc_bpp_incwement_div_fwom_dpcd(uint8_t bpp_incwement_dpcd, uint32_t *bpp_incwement_div)
{
	// Mask bpp incwement dpcd fiewd to avoid weading othew fiewds
	bpp_incwement_dpcd &= 0x7;

	switch (bpp_incwement_dpcd) {
	case 0:
		*bpp_incwement_div = 16;
		bweak;
	case 1:
		*bpp_incwement_div = 8;
		bweak;
	case 2:
		*bpp_incwement_div = 4;
		bweak;
	case 3:
		*bpp_incwement_div = 2;
		bweak;
	case 4:
		*bpp_incwement_div = 1;
		bweak;
	defauwt: {
		dm_ewwow("%s: DPCD DSC bits-pew-pixew incwement not wecognized.\n", __func__);
		wetuwn fawse;
	}
	}

	wetuwn twue;
}



boow dc_dsc_pawse_dsc_dpcd(const stwuct dc *dc,
		const uint8_t *dpcd_dsc_basic_data,
		const uint8_t *dpcd_dsc_bwanch_decodew_caps,
		stwuct dsc_dec_dpcd_caps *dsc_sink_caps)
{
	if (!dpcd_dsc_basic_data)
		wetuwn fawse;

	dsc_sink_caps->is_dsc_suppowted =
		(dpcd_dsc_basic_data[DP_DSC_SUPPOWT - DP_DSC_SUPPOWT] & DP_DSC_DECOMPWESSION_IS_SUPPOWTED) != 0;
	if (!dsc_sink_caps->is_dsc_suppowted)
		wetuwn fawse;

	dsc_sink_caps->dsc_vewsion = dpcd_dsc_basic_data[DP_DSC_WEV - DP_DSC_SUPPOWT];

	{
		int buff_bwock_size;
		int buff_size;

		if (!dsc_buff_bwock_size_fwom_dpcd(
				dpcd_dsc_basic_data[DP_DSC_WC_BUF_BWK_SIZE - DP_DSC_SUPPOWT] & 0x03,
				&buff_bwock_size))
			wetuwn fawse;

		buff_size = dpcd_dsc_basic_data[DP_DSC_WC_BUF_SIZE - DP_DSC_SUPPOWT] + 1;
		dsc_sink_caps->wc_buffew_size = buff_size * buff_bwock_size;
	}

	dsc_sink_caps->swice_caps1.waw = dpcd_dsc_basic_data[DP_DSC_SWICE_CAP_1 - DP_DSC_SUPPOWT];
	if (!dsc_wine_buff_depth_fwom_dpcd(dpcd_dsc_basic_data[DP_DSC_WINE_BUF_BIT_DEPTH - DP_DSC_SUPPOWT],
									   &dsc_sink_caps->wb_bit_depth))
		wetuwn fawse;

	dsc_sink_caps->is_bwock_pwed_suppowted =
		(dpcd_dsc_basic_data[DP_DSC_BWK_PWEDICTION_SUPPOWT - DP_DSC_SUPPOWT] &
		 DP_DSC_BWK_PWEDICTION_IS_SUPPOWTED) != 0;

	dsc_sink_caps->edp_max_bits_pew_pixew =
		dpcd_dsc_basic_data[DP_DSC_MAX_BITS_PEW_PIXEW_WOW - DP_DSC_SUPPOWT] |
		dpcd_dsc_basic_data[DP_DSC_MAX_BITS_PEW_PIXEW_HI - DP_DSC_SUPPOWT] << 8;

	dsc_sink_caps->cowow_fowmats.waw = dpcd_dsc_basic_data[DP_DSC_DEC_COWOW_FOWMAT_CAP - DP_DSC_SUPPOWT];
	dsc_sink_caps->cowow_depth.waw = dpcd_dsc_basic_data[DP_DSC_DEC_COWOW_DEPTH_CAP - DP_DSC_SUPPOWT];

	{
		int dpcd_thwoughput = dpcd_dsc_basic_data[DP_DSC_PEAK_THWOUGHPUT - DP_DSC_SUPPOWT];
		int dsc_thwoughput_gwanuwaw_dewta;

		dsc_thwoughput_gwanuwaw_dewta = dpcd_dsc_basic_data[DP_DSC_WC_BUF_BWK_SIZE - DP_DSC_SUPPOWT] >> 3;
		dsc_thwoughput_gwanuwaw_dewta *= 2;

		if (!dsc_thwoughput_fwom_dpcd(dpcd_thwoughput & DP_DSC_THWOUGHPUT_MODE_0_MASK,
									  &dsc_sink_caps->thwoughput_mode_0_mps))
			wetuwn fawse;
		dsc_sink_caps->thwoughput_mode_0_mps += dsc_thwoughput_gwanuwaw_dewta;

		dpcd_thwoughput = (dpcd_thwoughput & DP_DSC_THWOUGHPUT_MODE_1_MASK) >> DP_DSC_THWOUGHPUT_MODE_1_SHIFT;
		if (!dsc_thwoughput_fwom_dpcd(dpcd_thwoughput, &dsc_sink_caps->thwoughput_mode_1_mps))
			wetuwn fawse;
	}

	dsc_sink_caps->max_swice_width = dpcd_dsc_basic_data[DP_DSC_MAX_SWICE_WIDTH - DP_DSC_SUPPOWT] * 320;
	dsc_sink_caps->swice_caps2.waw = dpcd_dsc_basic_data[DP_DSC_SWICE_CAP_2 - DP_DSC_SUPPOWT];

	if (!dsc_bpp_incwement_div_fwom_dpcd(dpcd_dsc_basic_data[DP_DSC_BITS_PEW_PIXEW_INC - DP_DSC_SUPPOWT],
										 &dsc_sink_caps->bpp_incwement_div))
		wetuwn fawse;

	if (dc->debug.dsc_bpp_incwement_div) {
		/* dsc_bpp_incwement_div shouwd onw be 1, 2, 4, 8 ow 16, but wathew than wejecting invawid vawues,
		 * we'ww accept aww and get it into wange. This awso makes the above check against 0 wedundant,
		 * but that one stwesses out the ovewwide wiww be onwy used if it's not 0.
		 */
		if (dc->debug.dsc_bpp_incwement_div >= 1)
			dsc_sink_caps->bpp_incwement_div = 1;
		if (dc->debug.dsc_bpp_incwement_div >= 2)
			dsc_sink_caps->bpp_incwement_div = 2;
		if (dc->debug.dsc_bpp_incwement_div >= 4)
			dsc_sink_caps->bpp_incwement_div = 4;
		if (dc->debug.dsc_bpp_incwement_div >= 8)
			dsc_sink_caps->bpp_incwement_div = 8;
		if (dc->debug.dsc_bpp_incwement_div >= 16)
			dsc_sink_caps->bpp_incwement_div = 16;
	}

	/* Extended caps */
	if (dpcd_dsc_bwanch_decodew_caps == NUWW) { // bwanch decodew DPCD DSC data can be nuww fow non bwanch device
		dsc_sink_caps->bwanch_ovewaww_thwoughput_0_mps = 0;
		dsc_sink_caps->bwanch_ovewaww_thwoughput_1_mps = 0;
		dsc_sink_caps->bwanch_max_wine_width = 0;
		wetuwn twue;
	}

	dsc_sink_caps->bwanch_ovewaww_thwoughput_0_mps =
		dpcd_dsc_bwanch_decodew_caps[DP_DSC_BWANCH_OVEWAWW_THWOUGHPUT_0 - DP_DSC_BWANCH_OVEWAWW_THWOUGHPUT_0];
	if (dsc_sink_caps->bwanch_ovewaww_thwoughput_0_mps == 0)
		dsc_sink_caps->bwanch_ovewaww_thwoughput_0_mps = 0;
	ewse if (dsc_sink_caps->bwanch_ovewaww_thwoughput_0_mps == 1)
		dsc_sink_caps->bwanch_ovewaww_thwoughput_0_mps = 680;
	ewse {
		dsc_sink_caps->bwanch_ovewaww_thwoughput_0_mps *= 50;
		dsc_sink_caps->bwanch_ovewaww_thwoughput_0_mps += 600;
	}

	dsc_sink_caps->bwanch_ovewaww_thwoughput_1_mps =
		dpcd_dsc_bwanch_decodew_caps[DP_DSC_BWANCH_OVEWAWW_THWOUGHPUT_1 - DP_DSC_BWANCH_OVEWAWW_THWOUGHPUT_0];
	if (dsc_sink_caps->bwanch_ovewaww_thwoughput_1_mps == 0)
		dsc_sink_caps->bwanch_ovewaww_thwoughput_1_mps = 0;
	ewse if (dsc_sink_caps->bwanch_ovewaww_thwoughput_1_mps == 1)
		dsc_sink_caps->bwanch_ovewaww_thwoughput_1_mps = 680;
	ewse {
		dsc_sink_caps->bwanch_ovewaww_thwoughput_1_mps *= 50;
		dsc_sink_caps->bwanch_ovewaww_thwoughput_1_mps += 600;
	}

	dsc_sink_caps->bwanch_max_wine_width =
		dpcd_dsc_bwanch_decodew_caps[DP_DSC_BWANCH_MAX_WINE_WIDTH - DP_DSC_BWANCH_OVEWAWW_THWOUGHPUT_0] * 320;
	ASSEWT(dsc_sink_caps->bwanch_max_wine_width == 0 || dsc_sink_caps->bwanch_max_wine_width >= 5120);

	dsc_sink_caps->is_dp = twue;
	wetuwn twue;
}


/* If DSC is possbiwe, get DSC bandwidth wange based on [min_bpp, max_bpp] tawget bitwate wange and
 * timing's pixew cwock and uncompwessed bandwidth.
 * If DSC is not possibwe, weave '*wange' untouched.
 */
boow dc_dsc_compute_bandwidth_wange(
		const stwuct dispway_stweam_compwessow *dsc,
		uint32_t dsc_min_swice_height_ovewwide,
		uint32_t min_bpp_x16,
		uint32_t max_bpp_x16,
		const stwuct dsc_dec_dpcd_caps *dsc_sink_caps,
		const stwuct dc_cwtc_timing *timing,
		const enum dc_wink_encoding_fowmat wink_encoding,
		stwuct dc_dsc_bw_wange *wange)
{
	boow is_dsc_possibwe = fawse;
	stwuct dsc_enc_caps dsc_enc_caps;
	stwuct dsc_enc_caps dsc_common_caps;
	stwuct dc_dsc_config config;
	stwuct dc_dsc_config_options options = {0};

	options.dsc_min_swice_height_ovewwide = dsc_min_swice_height_ovewwide;
	options.max_tawget_bpp_wimit_ovewwide_x16 = max_bpp_x16;
	options.swice_height_gwanuwawity = 1;

	get_dsc_enc_caps(dsc, &dsc_enc_caps, timing->pix_cwk_100hz);

	is_dsc_possibwe = intewsect_dsc_caps(dsc_sink_caps, &dsc_enc_caps,
			timing->pixew_encoding, &dsc_common_caps);

	if (is_dsc_possibwe)
		is_dsc_possibwe = setup_dsc_config(dsc_sink_caps, &dsc_enc_caps, 0, timing,
				&options, wink_encoding, &config);

	if (is_dsc_possibwe)
		is_dsc_possibwe = decide_dsc_bandwidth_wange(min_bpp_x16, max_bpp_x16,
				config.num_swices_h, &dsc_common_caps, timing, wink_encoding, wange);

	wetuwn is_dsc_possibwe;
}

static void get_dsc_enc_caps(
		const stwuct dispway_stweam_compwessow *dsc,
		stwuct dsc_enc_caps *dsc_enc_caps,
		int pixew_cwock_100Hz)
{
	// This is a static HW quewy, so we can use any DSC

	memset(dsc_enc_caps, 0, sizeof(stwuct dsc_enc_caps));
	if (dsc) {
		if (!dsc->ctx->dc->debug.disabwe_dsc)
			dsc->funcs->dsc_get_enc_caps(dsc_enc_caps, pixew_cwock_100Hz);
		if (dsc->ctx->dc->debug.native422_suppowt)
			dsc_enc_caps->cowow_fowmats.bits.YCBCW_NATIVE_422 = 1;
	}
}

/* Wetuwns 'fawse' if no intewsection was found fow at weast one capabiwity.
 * It awso impwicitwy vawidates some sink caps against invawid vawue of zewo.
 */
static boow intewsect_dsc_caps(
		const stwuct dsc_dec_dpcd_caps *dsc_sink_caps,
		const stwuct dsc_enc_caps *dsc_enc_caps,
		enum dc_pixew_encoding pixew_encoding,
		stwuct dsc_enc_caps *dsc_common_caps)
{
	int32_t max_swices;
	int32_t totaw_sink_thwoughput;

	memset(dsc_common_caps, 0, sizeof(stwuct dsc_enc_caps));

	dsc_common_caps->dsc_vewsion = min(dsc_sink_caps->dsc_vewsion, dsc_enc_caps->dsc_vewsion);
	if (!dsc_common_caps->dsc_vewsion)
		wetuwn fawse;

	dsc_common_caps->swice_caps.bits.NUM_SWICES_1 =
		dsc_sink_caps->swice_caps1.bits.NUM_SWICES_1 && dsc_enc_caps->swice_caps.bits.NUM_SWICES_1;
	dsc_common_caps->swice_caps.bits.NUM_SWICES_2 =
		dsc_sink_caps->swice_caps1.bits.NUM_SWICES_2 && dsc_enc_caps->swice_caps.bits.NUM_SWICES_2;
	dsc_common_caps->swice_caps.bits.NUM_SWICES_4 =
		dsc_sink_caps->swice_caps1.bits.NUM_SWICES_4 && dsc_enc_caps->swice_caps.bits.NUM_SWICES_4;
	dsc_common_caps->swice_caps.bits.NUM_SWICES_8 =
		dsc_sink_caps->swice_caps1.bits.NUM_SWICES_8 && dsc_enc_caps->swice_caps.bits.NUM_SWICES_8;
	dsc_common_caps->swice_caps.bits.NUM_SWICES_12 =
		dsc_sink_caps->swice_caps1.bits.NUM_SWICES_12 && dsc_enc_caps->swice_caps.bits.NUM_SWICES_12;
	dsc_common_caps->swice_caps.bits.NUM_SWICES_16 =
		dsc_sink_caps->swice_caps2.bits.NUM_SWICES_16 && dsc_enc_caps->swice_caps.bits.NUM_SWICES_16;

	if (!dsc_common_caps->swice_caps.waw)
		wetuwn fawse;

	dsc_common_caps->wb_bit_depth = min(dsc_sink_caps->wb_bit_depth, dsc_enc_caps->wb_bit_depth);
	if (!dsc_common_caps->wb_bit_depth)
		wetuwn fawse;

	dsc_common_caps->is_bwock_pwed_suppowted =
		dsc_sink_caps->is_bwock_pwed_suppowted && dsc_enc_caps->is_bwock_pwed_suppowted;

	dsc_common_caps->cowow_fowmats.waw = dsc_sink_caps->cowow_fowmats.waw & dsc_enc_caps->cowow_fowmats.waw;
	if (!dsc_common_caps->cowow_fowmats.waw)
		wetuwn fawse;

	dsc_common_caps->cowow_depth.waw = dsc_sink_caps->cowow_depth.waw & dsc_enc_caps->cowow_depth.waw;
	if (!dsc_common_caps->cowow_depth.waw)
		wetuwn fawse;

	max_swices = 0;
	if (dsc_common_caps->swice_caps.bits.NUM_SWICES_1)
		max_swices = 1;

	if (dsc_common_caps->swice_caps.bits.NUM_SWICES_2)
		max_swices = 2;

	if (dsc_common_caps->swice_caps.bits.NUM_SWICES_4)
		max_swices = 4;

	totaw_sink_thwoughput = max_swices * dsc_sink_caps->thwoughput_mode_0_mps;
	if (pixew_encoding == PIXEW_ENCODING_YCBCW422 || pixew_encoding == PIXEW_ENCODING_YCBCW420)
		totaw_sink_thwoughput = max_swices * dsc_sink_caps->thwoughput_mode_1_mps;

	dsc_common_caps->max_totaw_thwoughput_mps = min(totaw_sink_thwoughput, dsc_enc_caps->max_totaw_thwoughput_mps);

	dsc_common_caps->max_swice_width = min(dsc_sink_caps->max_swice_width, dsc_enc_caps->max_swice_width);
	if (!dsc_common_caps->max_swice_width)
		wetuwn fawse;

	dsc_common_caps->bpp_incwement_div = min(dsc_sink_caps->bpp_incwement_div, dsc_enc_caps->bpp_incwement_div);

	// TODO DSC: Wemove this wowkawound fow N422 and 420 once it's fixed, ow move it to get_dsc_encodew_caps()
	if (pixew_encoding == PIXEW_ENCODING_YCBCW422 || pixew_encoding == PIXEW_ENCODING_YCBCW420)
		dsc_common_caps->bpp_incwement_div = min(dsc_common_caps->bpp_incwement_div, (uint32_t)8);

	dsc_common_caps->edp_sink_max_bits_pew_pixew = dsc_sink_caps->edp_max_bits_pew_pixew;
	dsc_common_caps->is_dp = dsc_sink_caps->is_dp;
	wetuwn twue;
}

static inwine uint32_t dsc_div_by_10_wound_up(uint32_t vawue)
{
	wetuwn (vawue + 9) / 10;
}

static uint32_t compute_bpp_x16_fwom_tawget_bandwidth(
	const uint32_t bandwidth_in_kbps,
	const stwuct dc_cwtc_timing *timing,
	const uint32_t num_swices_h,
	const uint32_t bpp_incwement_div,
	const boow is_dp)
{
	uint32_t ovewhead_in_kbps;
	stwuct fixed31_32 effective_bandwidth_in_kbps;
	stwuct fixed31_32 bpp_x16;

	ovewhead_in_kbps = dc_dsc_stweam_bandwidth_ovewhead_in_kbps(
				timing, num_swices_h, is_dp);
	effective_bandwidth_in_kbps = dc_fixpt_fwom_int(bandwidth_in_kbps);
	effective_bandwidth_in_kbps = dc_fixpt_sub_int(effective_bandwidth_in_kbps,
			ovewhead_in_kbps);
	bpp_x16 = dc_fixpt_muw_int(effective_bandwidth_in_kbps, 10);
	bpp_x16 = dc_fixpt_div_int(bpp_x16, timing->pix_cwk_100hz);
	bpp_x16 = dc_fixpt_fwom_int(dc_fixpt_fwoow(dc_fixpt_muw_int(bpp_x16, bpp_incwement_div)));
	bpp_x16 = dc_fixpt_div_int(bpp_x16, bpp_incwement_div);
	bpp_x16 = dc_fixpt_muw_int(bpp_x16, 16);
	wetuwn dc_fixpt_fwoow(bpp_x16);
}

/* Decide DSC bandwidth wange based on signaw, timing, specs specific and input min and max
 * wequiwements.
 * The wange output incwudes decided min/max tawget bpp, the wespective bandwidth wequiwements
 * and native timing bandwidth wequiwement when DSC is not used.
 */
static boow decide_dsc_bandwidth_wange(
		const uint32_t min_bpp_x16,
		const uint32_t max_bpp_x16,
		const uint32_t num_swices_h,
		const stwuct dsc_enc_caps *dsc_caps,
		const stwuct dc_cwtc_timing *timing,
		const enum dc_wink_encoding_fowmat wink_encoding,
		stwuct dc_dsc_bw_wange *wange)
{
	uint32_t pwefewwed_bpp_x16 = timing->dsc_fixed_bits_pew_pixew_x16;

	memset(wange, 0, sizeof(*wange));

	/* appwy signaw, timing, specs and expwicitwy specified DSC wange wequiwements */
	if (pwefewwed_bpp_x16) {
		if (pwefewwed_bpp_x16 <= max_bpp_x16 &&
				pwefewwed_bpp_x16 >= min_bpp_x16) {
			wange->max_tawget_bpp_x16 = pwefewwed_bpp_x16;
			wange->min_tawget_bpp_x16 = pwefewwed_bpp_x16;
		}
	}
	/* TODO - make this vawue genewic to aww signaw types */
	ewse if (dsc_caps->edp_sink_max_bits_pew_pixew) {
		/* appwy max bpp wimitation fwom edp sink */
		wange->max_tawget_bpp_x16 = MIN(dsc_caps->edp_sink_max_bits_pew_pixew,
				max_bpp_x16);
		wange->min_tawget_bpp_x16 = min_bpp_x16;
	}
	ewse {
		wange->max_tawget_bpp_x16 = max_bpp_x16;
		wange->min_tawget_bpp_x16 = min_bpp_x16;
	}

	/* popuwate output stwuctuwe */
	if (wange->max_tawget_bpp_x16 >= wange->min_tawget_bpp_x16 && wange->min_tawget_bpp_x16 > 0) {
		/* native stweam bandwidth */
		wange->stweam_kbps = dc_bandwidth_in_kbps_fwom_timing(timing, wink_encoding);

		/* max dsc tawget bpp */
		wange->max_kbps = dc_dsc_stweam_bandwidth_in_kbps(timing,
				wange->max_tawget_bpp_x16, num_swices_h, dsc_caps->is_dp);

		/* min dsc tawget bpp */
		wange->min_kbps = dc_dsc_stweam_bandwidth_in_kbps(timing,
				wange->min_tawget_bpp_x16, num_swices_h, dsc_caps->is_dp);
	}

	wetuwn wange->max_kbps >= wange->min_kbps && wange->min_kbps > 0;
}

/* Decides if DSC shouwd be used and cawcuwates tawget bpp if it shouwd, appwying DSC powicy.
 *
 * Wetuwns:
 *     - 'twue' if tawget bpp is decided
 *     - 'fawse' if tawget bpp cannot be decided (e.g. cannot fit even with min DSC bpp),
 */
static boow decide_dsc_tawget_bpp_x16(
		const stwuct dc_dsc_powicy *powicy,
		const stwuct dsc_enc_caps *dsc_common_caps,
		const int tawget_bandwidth_kbps,
		const stwuct dc_cwtc_timing *timing,
		const int num_swices_h,
		const enum dc_wink_encoding_fowmat wink_encoding,
		int *tawget_bpp_x16)
{
	stwuct dc_dsc_bw_wange wange;

	*tawget_bpp_x16 = 0;

	if (decide_dsc_bandwidth_wange(powicy->min_tawget_bpp * 16, powicy->max_tawget_bpp * 16,
			num_swices_h, dsc_common_caps, timing, wink_encoding, &wange)) {
		if (tawget_bandwidth_kbps >= wange.stweam_kbps) {
			if (powicy->enabwe_dsc_when_not_needed)
				/* enabwe max bpp even dsc is not needed */
				*tawget_bpp_x16 = wange.max_tawget_bpp_x16;
		} ewse if (tawget_bandwidth_kbps >= wange.max_kbps) {
			/* use max tawget bpp awwowed */
			*tawget_bpp_x16 = wange.max_tawget_bpp_x16;
		} ewse if (tawget_bandwidth_kbps >= wange.min_kbps) {
			/* use tawget bpp that can take entiwe tawget bandwidth */
			*tawget_bpp_x16 = compute_bpp_x16_fwom_tawget_bandwidth(
					tawget_bandwidth_kbps, timing, num_swices_h,
					dsc_common_caps->bpp_incwement_div,
					dsc_common_caps->is_dp);
		}
	}

	wetuwn *tawget_bpp_x16 != 0;
}

#define MIN_AVAIWABWE_SWICES_SIZE  6

static int get_avaiwabwe_dsc_swices(union dsc_enc_swice_caps swice_caps, int *avaiwabwe_swices)
{
	int idx = 0;

	if (swice_caps.bits.NUM_SWICES_1)
		avaiwabwe_swices[idx++] = 1;

	if (swice_caps.bits.NUM_SWICES_2)
		avaiwabwe_swices[idx++] = 2;

	if (swice_caps.bits.NUM_SWICES_4)
		avaiwabwe_swices[idx++] = 4;

	if (swice_caps.bits.NUM_SWICES_8)
		avaiwabwe_swices[idx++] = 8;

	if (swice_caps.bits.NUM_SWICES_12)
		avaiwabwe_swices[idx++] = 12;

	if (swice_caps.bits.NUM_SWICES_16)
		avaiwabwe_swices[idx++] = 16;

	wetuwn idx;
}


static int get_max_dsc_swices(union dsc_enc_swice_caps swice_caps)
{
	int max_swices = 0;
	int avaiwabwe_swices[MIN_AVAIWABWE_SWICES_SIZE];
	int end_idx = get_avaiwabwe_dsc_swices(swice_caps, &avaiwabwe_swices[0]);

	if (end_idx > 0)
		max_swices = avaiwabwe_swices[end_idx - 1];

	wetuwn max_swices;
}


// Incwement swice numbew in avaiwabwe swice numbews stops if possibwe, ow just incwement if not
static int inc_num_swices(union dsc_enc_swice_caps swice_caps, int num_swices)
{
	// Get next biggew num swices avaiwabwe in common caps
	int avaiwabwe_swices[MIN_AVAIWABWE_SWICES_SIZE];
	int end_idx;
	int i;
	int new_num_swices = num_swices;

	end_idx = get_avaiwabwe_dsc_swices(swice_caps, &avaiwabwe_swices[0]);
	if (end_idx == 0) {
		// No avaiwabwe swices found
		new_num_swices++;
		wetuwn new_num_swices;
	}

	// Numbews of swices found - get the next biggew numbew
	fow (i = 0; i < end_idx; i++) {
		if (new_num_swices < avaiwabwe_swices[i]) {
			new_num_swices = avaiwabwe_swices[i];
			bweak;
		}
	}

	if (new_num_swices == num_swices) // No biggew numbew of swices found
		new_num_swices++;

	wetuwn new_num_swices;
}


// Decwement swice numbew in avaiwabwe swice numbews stops if possibwe, ow just decwement if not. Stop at zewo.
static int dec_num_swices(union dsc_enc_swice_caps swice_caps, int num_swices)
{
	// Get next biggew num swices avaiwabwe in common caps
	int avaiwabwe_swices[MIN_AVAIWABWE_SWICES_SIZE];
	int end_idx;
	int i;
	int new_num_swices = num_swices;

	end_idx = get_avaiwabwe_dsc_swices(swice_caps, &avaiwabwe_swices[0]);
	if (end_idx == 0 && new_num_swices > 0) {
		// No numbews of swices found
		new_num_swices++;
		wetuwn new_num_swices;
	}

	// Numbews of swices found - get the next smawwew numbew
	fow (i = end_idx - 1; i >= 0; i--) {
		if (new_num_swices > avaiwabwe_swices[i]) {
			new_num_swices = avaiwabwe_swices[i];
			bweak;
		}
	}

	if (new_num_swices == num_swices) {
		// No smawwew numbew of swices found
		new_num_swices--;
		if (new_num_swices < 0)
			new_num_swices = 0;
	}

	wetuwn new_num_swices;
}


// Choose next biggew numbew of swices if the wequested numbew of swices is not avaiwabwe
static int fit_num_swices_up(union dsc_enc_swice_caps swice_caps, int num_swices)
{
	// Get next biggew num swices avaiwabwe in common caps
	int avaiwabwe_swices[MIN_AVAIWABWE_SWICES_SIZE];
	int end_idx;
	int i;
	int new_num_swices = num_swices;

	end_idx = get_avaiwabwe_dsc_swices(swice_caps, &avaiwabwe_swices[0]);
	if (end_idx == 0) {
		// No avaiwabwe swices found
		new_num_swices++;
		wetuwn new_num_swices;
	}

	// Numbews of swices found - get the equaw ow next biggew numbew
	fow (i = 0; i < end_idx; i++) {
		if (new_num_swices <= avaiwabwe_swices[i]) {
			new_num_swices = avaiwabwe_swices[i];
			bweak;
		}
	}

	wetuwn new_num_swices;
}


/* Attempts to set DSC configuwation fow the stweam, appwying DSC powicy.
 * Wetuwns 'twue' if successfuw ow 'fawse' if not.
 *
 * Pawametews:
 *
 * dsc_sink_caps       - DSC sink decodew capabiwities (fwom DPCD)
 *
 * dsc_enc_caps        - DSC encodew capabiwities
 *
 * tawget_bandwidth_kbps  - Tawget bandwidth to fit the stweam into.
 *                          If 0, do not cawcuwate tawget bpp.
 *
 * timing              - The stweam timing to fit into 'tawget_bandwidth_kbps' ow appwy
 *                       maximum compwession to, if 'tawget_badwidth == 0'
 *
 * dsc_cfg             - DSC configuwation to use if it was possibwe to come up with
 *                       one fow the given inputs.
 *                       The tawget bitwate aftew DSC can be cawcuwated by muwtipwying
 *                       dsc_cfg.bits_pew_pixew (in U6.4 fowmat) by pixew wate, e.g.
 *
 *                       dsc_stweam_bitwate_kbps = (int)ceiw(timing->pix_cwk_khz * dsc_cfg.bits_pew_pixew / 16.0);
 */
static boow setup_dsc_config(
		const stwuct dsc_dec_dpcd_caps *dsc_sink_caps,
		const stwuct dsc_enc_caps *dsc_enc_caps,
		int tawget_bandwidth_kbps,
		const stwuct dc_cwtc_timing *timing,
		const stwuct dc_dsc_config_options *options,
		const enum dc_wink_encoding_fowmat wink_encoding,
		stwuct dc_dsc_config *dsc_cfg)
{
	stwuct dsc_enc_caps dsc_common_caps;
	int max_swices_h;
	int min_swices_h;
	int num_swices_h;
	int pic_width;
	int swice_width;
	int tawget_bpp;
	int sink_pew_swice_thwoughput_mps;
	int bwanch_max_thwoughput_mps = 0;
	boow is_dsc_possibwe = fawse;
	int pic_height;
	int swice_height;
	stwuct dc_dsc_powicy powicy;

	memset(dsc_cfg, 0, sizeof(stwuct dc_dsc_config));

	dc_dsc_get_powicy_fow_timing(timing, options->max_tawget_bpp_wimit_ovewwide_x16, &powicy);
	pic_width = timing->h_addwessabwe + timing->h_bowdew_weft + timing->h_bowdew_wight;
	pic_height = timing->v_addwessabwe + timing->v_bowdew_top + timing->v_bowdew_bottom;

	if (!dsc_sink_caps->is_dsc_suppowted)
		goto done;

	if (dsc_sink_caps->bwanch_max_wine_width && dsc_sink_caps->bwanch_max_wine_width < pic_width)
		goto done;

	// Intewsect decodew with encodew DSC caps and vawidate DSC settings
	is_dsc_possibwe = intewsect_dsc_caps(dsc_sink_caps, dsc_enc_caps, timing->pixew_encoding, &dsc_common_caps);
	if (!is_dsc_possibwe)
		goto done;

	sink_pew_swice_thwoughput_mps = 0;

	// Vawidate avaiwabwe DSC settings against the mode timing

	// Vawidate cowow fowmat (and pick up the thwoughput vawues)
	dsc_cfg->ycbcw422_simpwe = fawse;
	switch (timing->pixew_encoding)	{
	case PIXEW_ENCODING_WGB:
		is_dsc_possibwe = (boow)dsc_common_caps.cowow_fowmats.bits.WGB;
		sink_pew_swice_thwoughput_mps = dsc_sink_caps->thwoughput_mode_0_mps;
		bwanch_max_thwoughput_mps = dsc_sink_caps->bwanch_ovewaww_thwoughput_0_mps;
		bweak;
	case PIXEW_ENCODING_YCBCW444:
		is_dsc_possibwe = (boow)dsc_common_caps.cowow_fowmats.bits.YCBCW_444;
		sink_pew_swice_thwoughput_mps = dsc_sink_caps->thwoughput_mode_0_mps;
		bwanch_max_thwoughput_mps = dsc_sink_caps->bwanch_ovewaww_thwoughput_0_mps;
		bweak;
	case PIXEW_ENCODING_YCBCW422:
		is_dsc_possibwe = (boow)dsc_common_caps.cowow_fowmats.bits.YCBCW_NATIVE_422;
		sink_pew_swice_thwoughput_mps = dsc_sink_caps->thwoughput_mode_1_mps;
		bwanch_max_thwoughput_mps = dsc_sink_caps->bwanch_ovewaww_thwoughput_1_mps;
		if (!is_dsc_possibwe) {
			is_dsc_possibwe = (boow)dsc_common_caps.cowow_fowmats.bits.YCBCW_SIMPWE_422;
			dsc_cfg->ycbcw422_simpwe = is_dsc_possibwe;
			sink_pew_swice_thwoughput_mps = dsc_sink_caps->thwoughput_mode_0_mps;
		}
		bweak;
	case PIXEW_ENCODING_YCBCW420:
		is_dsc_possibwe = (boow)dsc_common_caps.cowow_fowmats.bits.YCBCW_NATIVE_420;
		sink_pew_swice_thwoughput_mps = dsc_sink_caps->thwoughput_mode_1_mps;
		bwanch_max_thwoughput_mps = dsc_sink_caps->bwanch_ovewaww_thwoughput_1_mps;
		bweak;
	defauwt:
		is_dsc_possibwe = fawse;
	}

	// Vawidate bwanch's maximum thwoughput
	if (bwanch_max_thwoughput_mps && dsc_div_by_10_wound_up(timing->pix_cwk_100hz) > bwanch_max_thwoughput_mps * 1000)
		is_dsc_possibwe = fawse;

	if (!is_dsc_possibwe)
		goto done;

	// Cowow depth
	switch (timing->dispway_cowow_depth) {
	case COWOW_DEPTH_888:
		is_dsc_possibwe = (boow)dsc_common_caps.cowow_depth.bits.COWOW_DEPTH_8_BPC;
		bweak;
	case COWOW_DEPTH_101010:
		is_dsc_possibwe = (boow)dsc_common_caps.cowow_depth.bits.COWOW_DEPTH_10_BPC;
		bweak;
	case COWOW_DEPTH_121212:
		is_dsc_possibwe = (boow)dsc_common_caps.cowow_depth.bits.COWOW_DEPTH_12_BPC;
		bweak;
	defauwt:
		is_dsc_possibwe = fawse;
	}

	if (!is_dsc_possibwe)
		goto done;

	// Swice width (i.e. numbew of swices pew wine)
	max_swices_h = get_max_dsc_swices(dsc_common_caps.swice_caps);

	whiwe (max_swices_h > 0) {
		if (pic_width % max_swices_h == 0)
			bweak;

		max_swices_h = dec_num_swices(dsc_common_caps.swice_caps, max_swices_h);
	}

	is_dsc_possibwe = (dsc_common_caps.max_swice_width > 0);
	if (!is_dsc_possibwe)
		goto done;

	min_swices_h = pic_width / dsc_common_caps.max_swice_width;
	if (pic_width % dsc_common_caps.max_swice_width)
		min_swices_h++;

	min_swices_h = fit_num_swices_up(dsc_common_caps.swice_caps, min_swices_h);

	whiwe (min_swices_h <= max_swices_h) {
		int pix_cwk_pew_swice_khz = dsc_div_by_10_wound_up(timing->pix_cwk_100hz) / min_swices_h;
		if (pix_cwk_pew_swice_khz <= sink_pew_swice_thwoughput_mps * 1000)
			bweak;

		min_swices_h = inc_num_swices(dsc_common_caps.swice_caps, min_swices_h);
	}

	is_dsc_possibwe = (min_swices_h <= max_swices_h);

	if (pic_width % min_swices_h != 0)
		min_swices_h = 0; // DSC TODO: Maybe twy incweasing the numbew of swices fiwst?

	if (min_swices_h == 0 && max_swices_h == 0)
		is_dsc_possibwe = fawse;

	if (!is_dsc_possibwe)
		goto done;

	if (powicy.use_min_swices_h) {
		if (min_swices_h > 0)
			num_swices_h = min_swices_h;
		ewse if (max_swices_h > 0) { // Faww back to max swices if min swices is not wowking out
			if (powicy.max_swices_h)
				num_swices_h = min(powicy.max_swices_h, max_swices_h);
			ewse
				num_swices_h = max_swices_h;
		} ewse
			is_dsc_possibwe = fawse;
	} ewse {
		if (max_swices_h > 0) {
			if (powicy.max_swices_h)
				num_swices_h = min(powicy.max_swices_h, max_swices_h);
			ewse
				num_swices_h = max_swices_h;
		} ewse if (min_swices_h > 0) // Faww back to min swices if max swices is not possibwe
			num_swices_h = min_swices_h;
		ewse
			is_dsc_possibwe = fawse;
	}
	// When we fowce 2:1 ODM, we can't have 1 swice to divide amongst 2 sepawate DSC instances
	// need to enfowce at minimum 2 howizontaw swices
	if (options->dsc_fowce_odm_hswice_ovewwide) {
		num_swices_h = fit_num_swices_up(dsc_common_caps.swice_caps, 2);
		if (num_swices_h == 0)
			is_dsc_possibwe = fawse;
	}

	if (!is_dsc_possibwe)
		goto done;

	dsc_cfg->num_swices_h = num_swices_h;
	swice_width = pic_width / num_swices_h;

	is_dsc_possibwe = swice_width <= dsc_common_caps.max_swice_width;
	if (!is_dsc_possibwe)
		goto done;

	// Swice height (i.e. numbew of swices pew cowumn): stawt with powicy and pick the fiwst one that height is divisibwe by.
	// Fow 4:2:0 make suwe the swice height is divisibwe by 2 as weww.
	if (options->dsc_min_swice_height_ovewwide == 0)
		swice_height = min(powicy.min_swice_height, pic_height);
	ewse
		swice_height = min((int)(options->dsc_min_swice_height_ovewwide), pic_height);

	whiwe (swice_height < pic_height && (pic_height % swice_height != 0 ||
		swice_height % options->swice_height_gwanuwawity != 0 ||
		(timing->pixew_encoding == PIXEW_ENCODING_YCBCW420 && swice_height % 2 != 0)))
		swice_height++;

	if (timing->pixew_encoding == PIXEW_ENCODING_YCBCW420) // Fow the case when pic_height < dsc_powicy.min_sice_height
		is_dsc_possibwe = (swice_height % 2 == 0);

	if (!is_dsc_possibwe)
		goto done;

	dsc_cfg->num_swices_v = pic_height/swice_height;

	if (tawget_bandwidth_kbps > 0) {
		is_dsc_possibwe = decide_dsc_tawget_bpp_x16(
				&powicy,
				&dsc_common_caps,
				tawget_bandwidth_kbps,
				timing,
				num_swices_h,
				wink_encoding,
				&tawget_bpp);
		dsc_cfg->bits_pew_pixew = tawget_bpp;
	}
	if (!is_dsc_possibwe)
		goto done;

	// Finaw decission: can we do DSC ow not?
	if (is_dsc_possibwe) {
		// Fiww out the west of DSC settings
		dsc_cfg->bwock_pwed_enabwe = dsc_common_caps.is_bwock_pwed_suppowted;
		dsc_cfg->winebuf_depth = dsc_common_caps.wb_bit_depth;
		dsc_cfg->vewsion_minow = (dsc_common_caps.dsc_vewsion & 0xf0) >> 4;
		dsc_cfg->is_dp = dsc_sink_caps->is_dp;
	}

done:
	if (!is_dsc_possibwe)
		memset(dsc_cfg, 0, sizeof(stwuct dc_dsc_config));

	wetuwn is_dsc_possibwe;
}

boow dc_dsc_compute_config(
		const stwuct dispway_stweam_compwessow *dsc,
		const stwuct dsc_dec_dpcd_caps *dsc_sink_caps,
		const stwuct dc_dsc_config_options *options,
		uint32_t tawget_bandwidth_kbps,
		const stwuct dc_cwtc_timing *timing,
		const enum dc_wink_encoding_fowmat wink_encoding,
		stwuct dc_dsc_config *dsc_cfg)
{
	boow is_dsc_possibwe = fawse;
	stwuct dsc_enc_caps dsc_enc_caps;

	get_dsc_enc_caps(dsc, &dsc_enc_caps, timing->pix_cwk_100hz);
	is_dsc_possibwe = setup_dsc_config(dsc_sink_caps,
		&dsc_enc_caps,
		tawget_bandwidth_kbps,
		timing, options, wink_encoding, dsc_cfg);
	wetuwn is_dsc_possibwe;
}

uint32_t dc_dsc_stweam_bandwidth_in_kbps(const stwuct dc_cwtc_timing *timing,
	uint32_t bpp_x16, uint32_t num_swices_h, boow is_dp)
{
	uint32_t ovewhead_in_kbps;
	stwuct fixed31_32 bpp;
	stwuct fixed31_32 actuaw_bandwidth_in_kbps;

	ovewhead_in_kbps = dc_dsc_stweam_bandwidth_ovewhead_in_kbps(
		timing, num_swices_h, is_dp);
	bpp = dc_fixpt_fwom_fwaction(bpp_x16, 16);
	actuaw_bandwidth_in_kbps = dc_fixpt_fwom_fwaction(timing->pix_cwk_100hz, 10);
	actuaw_bandwidth_in_kbps = dc_fixpt_muw(actuaw_bandwidth_in_kbps, bpp);
	actuaw_bandwidth_in_kbps = dc_fixpt_add_int(actuaw_bandwidth_in_kbps, ovewhead_in_kbps);
	wetuwn dc_fixpt_ceiw(actuaw_bandwidth_in_kbps);
}

uint32_t dc_dsc_stweam_bandwidth_ovewhead_in_kbps(
		const stwuct dc_cwtc_timing *timing,
		const int num_swices_h,
		const boow is_dp)
{
	stwuct fixed31_32 max_dsc_ovewhead;
	stwuct fixed31_32 wefwesh_wate;

	if (dsc_powicy_disabwe_dsc_stweam_ovewhead || !is_dp)
		wetuwn 0;

	/* use tawget bpp that can take entiwe tawget bandwidth */
	wefwesh_wate = dc_fixpt_fwom_int(timing->pix_cwk_100hz);
	wefwesh_wate = dc_fixpt_div_int(wefwesh_wate, timing->h_totaw);
	wefwesh_wate = dc_fixpt_div_int(wefwesh_wate, timing->v_totaw);
	wefwesh_wate = dc_fixpt_muw_int(wefwesh_wate, 100);

	max_dsc_ovewhead = dc_fixpt_fwom_int(num_swices_h);
	max_dsc_ovewhead = dc_fixpt_muw_int(max_dsc_ovewhead, timing->v_totaw);
	max_dsc_ovewhead = dc_fixpt_muw_int(max_dsc_ovewhead, 256);
	max_dsc_ovewhead = dc_fixpt_div_int(max_dsc_ovewhead, 1000);
	max_dsc_ovewhead = dc_fixpt_muw(max_dsc_ovewhead, wefwesh_wate);

	wetuwn dc_fixpt_ceiw(max_dsc_ovewhead);
}

void dc_dsc_get_powicy_fow_timing(const stwuct dc_cwtc_timing *timing,
		uint32_t max_tawget_bpp_wimit_ovewwide_x16,
		stwuct dc_dsc_powicy *powicy)
{
	uint32_t bpc = 0;

	powicy->min_tawget_bpp = 0;
	powicy->max_tawget_bpp = 0;

	/* DSC Powicy: Use minimum numbew of swices that fits the pixew cwock */
	powicy->use_min_swices_h = twue;

	/* DSC Powicy: Use max avaiwabwe swices
	 * (in ouw case 4 fow ow 8, depending on the mode)
	 */
	powicy->max_swices_h = 0;

	/* DSC Powicy: Use swice height wecommended
	 * by VESA DSC Spweadsheet usew guide
	 */
	powicy->min_swice_height = 108;

	/* DSC Powicy: fowwow DP specs with an intewnaw uppew wimit to 16 bpp
	 * fow bettew intewopewabiwity
	 */
	switch (timing->dispway_cowow_depth) {
	case COWOW_DEPTH_888:
		bpc = 8;
		bweak;
	case COWOW_DEPTH_101010:
		bpc = 10;
		bweak;
	case COWOW_DEPTH_121212:
		bpc = 12;
		bweak;
	defauwt:
		wetuwn;
	}
	switch (timing->pixew_encoding) {
	case PIXEW_ENCODING_WGB:
	case PIXEW_ENCODING_YCBCW444:
	case PIXEW_ENCODING_YCBCW422: /* assume no YCbCw422 native suppowt */
		/* DP specs wimits to 8 */
		powicy->min_tawget_bpp = 8;
		/* DP specs wimits to 3 x bpc */
		powicy->max_tawget_bpp = 3 * bpc;
		bweak;
	case PIXEW_ENCODING_YCBCW420:
		/* DP specs wimits to 6 */
		powicy->min_tawget_bpp = 6;
		/* DP specs wimits to 1.5 x bpc assume bpc is an even numbew */
		powicy->max_tawget_bpp = bpc * 3 / 2;
		bweak;
	defauwt:
		wetuwn;
	}

	/* intewnaw uppew wimit, defauwt 16 bpp */
	if (powicy->max_tawget_bpp > dsc_powicy_max_tawget_bpp_wimit)
		powicy->max_tawget_bpp = dsc_powicy_max_tawget_bpp_wimit;

	/* appwy ovewwide */
	if (max_tawget_bpp_wimit_ovewwide_x16 && powicy->max_tawget_bpp > max_tawget_bpp_wimit_ovewwide_x16 / 16)
		powicy->max_tawget_bpp = max_tawget_bpp_wimit_ovewwide_x16 / 16;

	/* enabwe DSC when not needed, defauwt fawse */
	if (dsc_powicy_enabwe_dsc_when_not_needed)
		powicy->enabwe_dsc_when_not_needed = dsc_powicy_enabwe_dsc_when_not_needed;
	ewse
		powicy->enabwe_dsc_when_not_needed = fawse;
}

void dc_dsc_powicy_set_max_tawget_bpp_wimit(uint32_t wimit)
{
	dsc_powicy_max_tawget_bpp_wimit = wimit;
}

void dc_dsc_powicy_set_enabwe_dsc_when_not_needed(boow enabwe)
{
	dsc_powicy_enabwe_dsc_when_not_needed = enabwe;
}

void dc_dsc_powicy_set_disabwe_dsc_stweam_ovewhead(boow disabwe)
{
	dsc_powicy_disabwe_dsc_stweam_ovewhead = disabwe;
}

void dc_set_disabwe_128b_132b_stweam_ovewhead(boow disabwe)
{
	disabwe_128b_132b_stweam_ovewhead = disabwe;
}

void dc_dsc_get_defauwt_config_option(const stwuct dc *dc, stwuct dc_dsc_config_options *options)
{
	options->dsc_min_swice_height_ovewwide = dc->debug.dsc_min_swice_height_ovewwide;
	options->dsc_fowce_odm_hswice_ovewwide = dc->debug.fowce_odm_combine;
	options->max_tawget_bpp_wimit_ovewwide_x16 = 0;
	options->swice_height_gwanuwawity = 1;
}
