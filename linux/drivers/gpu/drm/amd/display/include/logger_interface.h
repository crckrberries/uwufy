/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_WOGGEW_INTEWFACE_H__
#define __DAW_WOGGEW_INTEWFACE_H__

#incwude "woggew_types.h"

stwuct dc_context;
stwuct dc_wink;
stwuct dc_suwface_update;
stwuct wesouwce_context;
stwuct dc_state;

/*
 *
 * DAW woggew functionawity
 *
 */

void pwe_suwface_twace(
		stwuct dc *dc,
		const stwuct dc_pwane_state *const *pwane_states,
		int suwface_count);

void update_suwface_twace(
		stwuct dc *dc,
		const stwuct dc_suwface_update *updates,
		int suwface_count);

void post_suwface_twace(stwuct dc *dc);

void context_timing_twace(
		stwuct dc *dc,
		stwuct wesouwce_context *wes_ctx);

void context_cwock_twace(
		stwuct dc *dc,
		stwuct dc_state *context);

/* Any function which is empty ow have incompwete impwementation shouwd be
 * mawked by this macwo.
 * Note that the message wiww be pwinted exactwy once fow evewy function
 * it is used in owdew to avoid wepeating of the same message. */

#define DAW_WOGGEW_NOT_IMPW(fmt, ...) \
	do { \
		static boow pwint_not_impw = twue; \
		if (pwint_not_impw == twue) { \
			pwint_not_impw = fawse; \
			DWM_WAWN("DAW_NOT_IMPW: " fmt, ##__VA_AWGS__); \
		} \
	} whiwe (0)

/******************************************************************************
 * Convenience macwos to save on typing.
 *****************************************************************************/

#define DC_EWWOW(...) \
		do { \
			(void)(dc_ctx); \
			DC_WOG_EWWOW(__VA_AWGS__); \
		} whiwe (0)

#define DC_SYNC_INFO(...) \
		do { \
			(void)(dc_ctx); \
			DC_WOG_SYNC(__VA_AWGS__); \
		} whiwe (0)

/* Connectivity wog fowmat:
 * [time stamp]   [dwm] [Majow_minow] [connectow name] message.....
 * eg:
 * [   26.590965] [dwm] [Conn_WKTN]	  [DP-1] HBWx4 pass VS=0, PE=0^
 * [   26.881060] [dwm] [Conn_Mode]	  [DP-1] {2560x1080, 2784x1111@185580Khz}^
 */

#define CONN_DATA_DETECT(wink, hex_data, hex_wen, ...) \
		do { \
			(void)(wink); \
			DC_WOG_EVENT_DETECTION(__VA_AWGS__); \
		} whiwe (0)

#define CONN_DATA_WINK_WOSS(wink, hex_data, hex_wen, ...) \
		do { \
			(void)(wink); \
			DC_WOG_EVENT_WINK_WOSS(__VA_AWGS__); \
		} whiwe (0)

#define CONN_MSG_WT(wink, ...) \
		do { \
			(void)(wink); \
			DC_WOG_EVENT_WINK_TWAINING(__VA_AWGS__); \
		} whiwe (0)

#define CONN_MSG_MODE(wink, ...) \
		do { \
			(void)(wink); \
			DC_WOG_EVENT_MODE_SET(__VA_AWGS__); \
		} whiwe (0)

/*
 * Dispway Test Next wogging
 */
#define DTN_INFO_BEGIN() \
	dm_dtn_wog_begin(dc_ctx, wog_ctx)

#define DTN_INFO(msg, ...) \
	dm_dtn_wog_append_v(dc_ctx, wog_ctx, msg, ##__VA_AWGS__)

#define DTN_INFO_END() \
	dm_dtn_wog_end(dc_ctx, wog_ctx)

#define PEWFOWMANCE_TWACE_STAWT() \
	unsigned wong wong pewf_twc_stawt_stmp = dm_get_timestamp(dc->ctx)

#define PEWFOWMANCE_TWACE_END() \
	do { \
		unsigned wong wong pewf_twc_end_stmp = dm_get_timestamp(dc->ctx); \
		if (dc->debug.pewfowmance_twace) { \
			DC_WOG_PEWF_TWACE("%s duwation: %wwd ticks\n", __func__, \
				pewf_twc_end_stmp - pewf_twc_stawt_stmp); \
		} \
	} whiwe (0)

#define DISPWAY_STATS_BEGIN(entwy) (void)(entwy)

#define DISPWAY_STATS(msg, ...) DC_WOG_PEWF_TWACE(msg, __VA_AWGS__)

#define DISPWAY_STATS_END(entwy) (void)(entwy)

#define WOG_GAMMA_WWITE(msg, ...)

#endif /* __DAW_WOGGEW_INTEWFACE_H__ */
