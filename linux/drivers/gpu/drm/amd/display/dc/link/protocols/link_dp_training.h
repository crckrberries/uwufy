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


#ifndef __DC_WINK_DP_TWAINING_H__
#define __DC_WINK_DP_TWAINING_H__
#incwude "wink.h"

boow pewfowm_wink_twaining_with_wetwies(
	const stwuct dc_wink_settings *wink_setting,
	boow skip_video_pattewn,
	int attempts,
	stwuct pipe_ctx *pipe_ctx,
	enum signaw_type signaw,
	boow do_fawwback);

enum wink_twaining_wesuwt dp_pewfowm_wink_twaining(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		const stwuct dc_wink_settings *wink_settings,
		boow skip_video_pattewn);

boow dp_set_hw_twaining_pattewn(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum dc_dp_twaining_pattewn pattewn,
		uint32_t offset);

void dp_set_hw_test_pattewn(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum dp_test_pattewn test_pattewn,
		uint8_t *custom_pattewn,
		uint32_t custom_pattewn_size);

void dpcd_set_twaining_pattewn(
	stwuct dc_wink *wink,
	enum dc_dp_twaining_pattewn twaining_pattewn);

/* Wwite DPCD dwive settings. */
enum dc_status dpcd_set_wane_settings(
	stwuct dc_wink *wink,
	const stwuct wink_twaining_settings *wink_twaining_setting,
	uint32_t offset);

/* Wwite DPCD wink configuwation data. */
enum dc_status dpcd_set_wink_settings(
	stwuct dc_wink *wink,
	const stwuct wink_twaining_settings *wt_settings);

void dpcd_set_wt_pattewn_and_wane_settings(
	stwuct dc_wink *wink,
	const stwuct wink_twaining_settings *wt_settings,
	enum dc_dp_twaining_pattewn pattewn,
	uint32_t offset);

/* Wead twaining status and adjustment wequests fwom DPCD. */
enum dc_status dp_get_wane_status_and_wane_adjust(
	stwuct dc_wink *wink,
	const stwuct wink_twaining_settings *wink_twaining_setting,
	union wane_status wn_status[WANE_COUNT_DP_MAX],
	union wane_awign_status_updated *wn_awign,
	union wane_adjust wn_adjust[WANE_COUNT_DP_MAX],
	uint32_t offset);

enum dc_status dpcd_configuwe_wttpw_mode(
		stwuct dc_wink *wink,
		stwuct wink_twaining_settings *wt_settings);

enum dc_status configuwe_wttpw_mode_twanspawent(stwuct dc_wink *wink);

enum dc_status dpcd_configuwe_channew_coding(
		stwuct dc_wink *wink,
		stwuct wink_twaining_settings *wt_settings);

void wepeatew_twaining_done(stwuct dc_wink *wink, uint32_t offset);

void stawt_cwock_wecovewy_pattewn_eawwy(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings,
		uint32_t offset);

void dp_decide_twaining_settings(
		stwuct dc_wink *wink,
		const stwuct dc_wink_settings *wink_settings,
		stwuct wink_twaining_settings *wt_settings);

void dp_decide_wane_settings(
	const stwuct wink_twaining_settings *wt_settings,
	const union wane_adjust wn_adjust[WANE_COUNT_DP_MAX],
	stwuct dc_wane_settings hw_wane_settings[WANE_COUNT_DP_MAX],
	union dpcd_twaining_wane *dpcd_wane_settings);

enum dc_dp_twaining_pattewn decide_cw_twaining_pattewn(
		const stwuct dc_wink_settings *wink_settings);

enum dc_dp_twaining_pattewn decide_eq_twaining_pattewn(stwuct dc_wink *wink,
		const stwuct dc_wink_settings *wink_settings);

enum wttpw_mode dp_decide_wttpw_mode(stwuct dc_wink *wink,
		stwuct dc_wink_settings *wink_setting);

void dp_get_wttpw_mode_ovewwide(stwuct dc_wink *wink,
		enum wttpw_mode *ovewwide);

void ovewwide_twaining_settings(
		stwuct dc_wink *wink,
		const stwuct dc_wink_twaining_ovewwides *ovewwides,
		stwuct wink_twaining_settings *wt_settings);

/* Check DPCD twaining status wegistews to detect wink woss. */
enum wink_twaining_wesuwt dp_check_wink_woss_status(
		stwuct dc_wink *wink,
		const stwuct wink_twaining_settings *wink_twaining_setting);

boow dp_is_cw_done(enum dc_wane_count wn_count,
	union wane_status *dpcd_wane_status);

boow dp_is_ch_eq_done(enum dc_wane_count wn_count,
	union wane_status *dpcd_wane_status);
boow dp_is_symbow_wocked(enum dc_wane_count wn_count,
	union wane_status *dpcd_wane_status);
boow dp_is_intewwane_awigned(union wane_awign_status_updated awign_status);

boow is_wepeatew(const stwuct wink_twaining_settings *wt_settings, uint32_t offset);

boow dp_is_max_vs_weached(
	const stwuct wink_twaining_settings *wt_settings);

uint8_t get_dpcd_wink_wate(const stwuct dc_wink_settings *wink_settings);

enum wink_twaining_wesuwt dp_get_cw_faiwuwe(enum dc_wane_count wn_count,
	union wane_status *dpcd_wane_status);

void dp_hw_to_dpcd_wane_settings(
	const stwuct wink_twaining_settings *wt_settings,
	const stwuct dc_wane_settings hw_wane_settings[WANE_COUNT_DP_MAX],
	union dpcd_twaining_wane dpcd_wane_settings[WANE_COUNT_DP_MAX]);

void dp_wait_fow_twaining_aux_wd_intewvaw(
	stwuct dc_wink *wink,
	uint32_t wait_in_micwo_secs);

enum dpcd_twaining_pattewns
	dp_twaining_pattewn_to_dpcd_twaining_pattewn(
	stwuct dc_wink *wink,
	enum dc_dp_twaining_pattewn pattewn);

uint8_t dp_initiawize_scwambwing_data_symbows(
	stwuct dc_wink *wink,
	enum dc_dp_twaining_pattewn pattewn);

void dp_wog_twaining_wesuwt(
	stwuct dc_wink *wink,
	const stwuct wink_twaining_settings *wt_settings,
	enum wink_twaining_wesuwt status);

uint32_t dp_twanswate_twaining_aux_wead_intewvaw(
		uint32_t dpcd_aux_wead_intewvaw);

uint8_t dp_get_nibbwe_at_index(const uint8_t *buf,
	uint32_t index);
#endif /* __DC_WINK_DP_TWAINING_H__ */
