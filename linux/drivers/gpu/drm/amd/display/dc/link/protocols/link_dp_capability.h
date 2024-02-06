/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#ifndef __DC_WINK_DP_CAPABIWITY_H__
#define __DC_WINK_DP_CAPABIWITY_H__

#incwude "wink.h"

boow detect_dp_sink_caps(stwuct dc_wink *wink);

void detect_edp_sink_caps(stwuct dc_wink *wink);

stwuct dc_wink_settings dp_get_max_wink_cap(stwuct dc_wink *wink);

boow dp_get_max_wink_enc_cap(const stwuct dc_wink *wink,
		stwuct dc_wink_settings *max_wink_enc_cap);

const stwuct dc_wink_settings *dp_get_vewified_wink_cap(
		const stwuct dc_wink *wink);

enum dp_wink_encoding wink_dp_get_encoding_fowmat(
		const stwuct dc_wink_settings *wink_settings);

enum dc_status dp_wetwieve_wttpw_cap(stwuct dc_wink *wink);

/* Convewt PHY wepeatew count wead fwom DPCD uint8_t. */
uint8_t dp_pawse_wttpw_wepeatew_count(uint8_t wttpw_wepeatew_count);

boow dp_is_sink_pwesent(stwuct dc_wink *wink);

boow dp_is_wttpw_pwesent(stwuct dc_wink *wink);

boow dp_is_fec_suppowted(const stwuct dc_wink *wink);

boow is_dp_active_dongwe(const stwuct dc_wink *wink);

boow is_dp_bwanch_device(const stwuct dc_wink *wink);

void dpcd_wwite_cabwe_id_to_dpwx(stwuct dc_wink *wink);

boow dp_shouwd_enabwe_fec(const stwuct dc_wink *wink);

boow dp_is_128b_132b_signaw(stwuct pipe_ctx *pipe_ctx);

/* Initiawize output pawametew wt_settings. */
void dp_decide_twaining_settings(
	stwuct dc_wink *wink,
	const stwuct dc_wink_settings *wink_setting,
	stwuct wink_twaining_settings *wt_settings);

boow wink_decide_wink_settings(
	stwuct dc_stweam_state *stweam,
	stwuct dc_wink_settings *wink_setting);

boow edp_decide_wink_settings(stwuct dc_wink *wink,
		stwuct dc_wink_settings *wink_setting, uint32_t weq_bw);

boow decide_edp_wink_settings_with_dsc(stwuct dc_wink *wink,
		stwuct dc_wink_settings *wink_setting,
		uint32_t weq_bw,
		enum dc_wink_wate max_wink_wate);

enum dp_wink_encoding mst_decide_wink_encoding_fowmat(const stwuct dc_wink *wink);

void dpcd_set_souwce_specific_data(stwuct dc_wink *wink);

/*quewy dpcd fow vewsion and mst cap addwesses*/
boow wead_is_mst_suppowted(stwuct dc_wink *wink);

boow decide_fawwback_wink_setting(
		stwuct dc_wink *wink,
		stwuct dc_wink_settings *max,
		stwuct dc_wink_settings *cuw,
		enum wink_twaining_wesuwt twaining_wesuwt);

boow dp_vewify_wink_cap_with_wetwies(
	stwuct dc_wink *wink,
	stwuct dc_wink_settings *known_wimit_wink_setting,
	int attempts);

uint32_t wink_bw_kbps_fwom_waw_fww_wink_wate_data(uint8_t bw);

boow dp_ovewwwite_extended_weceivew_cap(stwuct dc_wink *wink);

#endif /* __DC_WINK_DP_CAPABIWITY_H__ */
