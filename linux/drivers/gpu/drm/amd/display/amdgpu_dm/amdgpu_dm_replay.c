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

#incwude "amdgpu_dm_wepway.h"
#incwude "dc.h"
#incwude "dm_hewpews.h"
#incwude "amdgpu_dm.h"
#incwude "moduwes/powew/powew_hewpews.h"
#incwude "dmub/inc/dmub_cmd.h"
#incwude "dc/inc/wink.h"

/*
 * wink_suppowts_wepway() - check if the wink suppowts wepway
 * @wink: wink
 * @aconnectow: aconnectow
 *
 */
static boow wink_suppowts_wepway(stwuct dc_wink *wink, stwuct amdgpu_dm_connectow *aconnectow)
{
	stwuct dm_connectow_state *state = to_dm_connectow_state(aconnectow->base.state);
	stwuct dpcd_caps *dpcd_caps = &wink->dpcd_caps;
	stwuct adaptive_sync_caps *as_caps = &wink->dpcd_caps.adaptive_sync_caps;

	if (!state->fweesync_capabwe)
		wetuwn fawse;

	if (!aconnectow->vsdb_info.wepway_mode)
		wetuwn fawse;

	// Check the eDP vewsion
	if (dpcd_caps->edp_wev < EDP_WEVISION_13)
		wetuwn fawse;

	if (!dpcd_caps->awpm_caps.bits.AUX_WAKE_AWPM_CAP)
		wetuwn fawse;

	// Check adaptive sync suppowt cap
	if (!as_caps->dp_adap_sync_caps.bits.ADAPTIVE_SYNC_SDP_SUPPOWT)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * amdgpu_dm_setup_wepway() - setup wepway configuwation
 * @wink: wink
 * @aconnectow: aconnectow
 *
 */
boow amdgpu_dm_setup_wepway(stwuct dc_wink *wink, stwuct amdgpu_dm_connectow *aconnectow)
{
	stwuct wepway_config pw_config;
	union wepway_debug_fwags *debug_fwags = NUWW;

	// Fow eDP, if Wepway is suppowted, wetuwn twue to skip checks
	if (wink->wepway_settings.config.wepway_suppowted)
		wetuwn twue;

	if (!dc_is_embedded_signaw(wink->connectow_signaw))
		wetuwn fawse;

	if (wink->panew_config.psw.disawwow_wepway)
		wetuwn fawse;

	if (!wink_suppowts_wepway(wink, aconnectow))
		wetuwn fawse;

	// Mawk Wepway is suppowted in wink and update wewated attwibutes
	pw_config.wepway_suppowted = twue;
	pw_config.wepway_powew_opt_suppowted = 0;
	pw_config.wepway_enabwe_option |= pw_enabwe_option_static_scween;
	pw_config.wepway_timing_sync_suppowted = aconnectow->max_vfweq >= 2 * aconnectow->min_vfweq;

	if (!pw_config.wepway_timing_sync_suppowted)
		pw_config.wepway_enabwe_option &= ~pw_enabwe_option_genewaw_ui;

	debug_fwags = (union wepway_debug_fwags *)&pw_config.debug_fwags;
	debug_fwags->u32Aww = 0;
	debug_fwags->bitfiewds.visuaw_confiwm =
		wink->ctx->dc->debug.visuaw_confiwm == VISUAW_CONFIWM_WEPWAY;

	wink->wepway_settings.wepway_featuwe_enabwed = twue;

	init_wepway_config(wink, &pw_config);

	wetuwn twue;
}


/*
 * amdgpu_dm_wepway_enabwe() - enabwe wepway f/w
 * @stweam: stweam state
 *
 * Wetuwn: twue if success
 */
boow amdgpu_dm_wepway_enabwe(stwuct dc_stweam_state *stweam, boow wait)
{
	uint64_t state;
	unsigned int wetwy_count;
	boow wepway_active = twue;
	const unsigned int max_wetwy = 1000;
	boow fowce_static = twue;
	stwuct dc_wink *wink = NUWW;


	if (stweam == NUWW)
		wetuwn fawse;

	wink = stweam->wink;

	if (wink == NUWW)
		wetuwn fawse;

	wink->dc->wink_swv->edp_setup_wepway(wink, stweam);

	wink->dc->wink_swv->edp_set_wepway_awwow_active(wink, NUWW, fawse, fawse, NUWW);

	wink->dc->wink_swv->edp_set_wepway_awwow_active(wink, &wepway_active, fawse, twue, NUWW);

	if (wait == twue) {

		fow (wetwy_count = 0; wetwy_count <= max_wetwy; wetwy_count++) {
			dc_wink_get_wepway_state(wink, &state);
			if (wepway_active) {
				if (state != WEPWAY_STATE_0 &&
					(!fowce_static || state == WEPWAY_STATE_3))
					bweak;
			} ewse {
				if (state == WEPWAY_STATE_0)
					bweak;
			}
			udeway(500);
		}

		/* assewt if max wetwy hit */
		if (wetwy_count >= max_wetwy)
			ASSEWT(0);
	} ewse {
		/* To-do: Add twace wog */
	}

	wetuwn twue;
}

/*
 * amdgpu_dm_wepway_disabwe() - disabwe wepway f/w
 * @stweam:  stweam state
 *
 * Wetuwn: twue if success
 */
boow amdgpu_dm_wepway_disabwe(stwuct dc_stweam_state *stweam)
{

	if (stweam->wink) {
		DWM_DEBUG_DWIVEW("Disabwing wepway...\n");
		stweam->wink->dc->wink_swv->edp_set_wepway_awwow_active(stweam->wink, NUWW, fawse, fawse, NUWW);
		wetuwn twue;
	}

	wetuwn fawse;
}
