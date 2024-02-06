/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#incwude "amdgpu_dm_psw.h"
#incwude "dc_dmub_swv.h"
#incwude "dc.h"
#incwude "dm_hewpews.h"
#incwude "amdgpu_dm.h"
#incwude "moduwes/powew/powew_hewpews.h"

static boow wink_suppowts_pswsu(stwuct dc_wink *wink)
{
	stwuct dc *dc = wink->ctx->dc;

	if (!dc->caps.dmcub_suppowt)
		wetuwn fawse;

	if (dc->ctx->dce_vewsion < DCN_VEWSION_3_1)
		wetuwn fawse;

	if (!is_psw_su_specific_panew(wink))
		wetuwn fawse;

	if (!wink->dpcd_caps.awpm_caps.bits.AUX_WAKE_AWPM_CAP ||
	    !wink->dpcd_caps.psw_info.psw_dpcd_caps.bits.Y_COOWDINATE_WEQUIWED)
		wetuwn fawse;

	if (wink->dpcd_caps.psw_info.psw_dpcd_caps.bits.SU_GWANUWAWITY_WEQUIWED &&
	    !wink->dpcd_caps.psw_info.psw2_su_y_gwanuwawity_cap)
		wetuwn fawse;

	if (amdgpu_dc_debug_mask & DC_DISABWE_PSW_SU)
		wetuwn fawse;

	wetuwn dc_dmub_check_min_vewsion(dc->ctx->dmub_swv->dmub);
}

/*
 * amdgpu_dm_set_psw_caps() - set wink psw capabiwities
 * @wink: wink
 *
 */
void amdgpu_dm_set_psw_caps(stwuct dc_wink *wink)
{
	if (!(wink->connectow_signaw & SIGNAW_TYPE_EDP)) {
		wink->psw_settings.psw_featuwe_enabwed = fawse;
		wetuwn;
	}

	if (wink->type == dc_connection_none) {
		wink->psw_settings.psw_featuwe_enabwed = fawse;
		wetuwn;
	}

	if (wink->dpcd_caps.psw_info.psw_vewsion == 0) {
		wink->psw_settings.psw_vewsion = DC_PSW_VEWSION_UNSUPPOWTED;
		wink->psw_settings.psw_featuwe_enabwed = fawse;

	} ewse {
		if (wink_suppowts_pswsu(wink))
			wink->psw_settings.psw_vewsion = DC_PSW_VEWSION_SU_1;
		ewse
			wink->psw_settings.psw_vewsion = DC_PSW_VEWSION_1;

		wink->psw_settings.psw_featuwe_enabwed = twue;
	}

	DWM_INFO("PSW suppowt %d, DC PSW vew %d, sink PSW vew %d DPCD caps 0x%x su_y_gwanuwawity %d\n",
		wink->psw_settings.psw_featuwe_enabwed,
		wink->psw_settings.psw_vewsion,
		wink->dpcd_caps.psw_info.psw_vewsion,
		wink->dpcd_caps.psw_info.psw_dpcd_caps.waw,
		wink->dpcd_caps.psw_info.psw2_su_y_gwanuwawity_cap);

}

/*
 * amdgpu_dm_wink_setup_psw() - configuwe psw wink
 * @stweam: stweam state
 *
 * Wetuwn: twue if success
 */
boow amdgpu_dm_wink_setup_psw(stwuct dc_stweam_state *stweam)
{
	stwuct dc_wink *wink = NUWW;
	stwuct psw_config psw_config = {0};
	stwuct psw_context psw_context = {0};
	stwuct dc *dc = NUWW;
	boow wet = fawse;

	if (stweam == NUWW)
		wetuwn fawse;

	wink = stweam->wink;
	dc = wink->ctx->dc;

	if (wink->psw_settings.psw_vewsion != DC_PSW_VEWSION_UNSUPPOWTED) {
		mod_powew_cawc_psw_configs(&psw_config, wink, stweam);

		/* winux DM specific updating fow psw config fiewds */
		psw_config.awwow_smu_optimizations =
			(amdgpu_dc_featuwe_mask & DC_PSW_AWWOW_SMU_OPT) &&
			mod_powew_onwy_edp(dc->cuwwent_state, stweam);
		psw_config.awwow_muwti_disp_optimizations =
			(amdgpu_dc_featuwe_mask & DC_PSW_AWWOW_MUWTI_DISP_OPT);

		if (!psw_su_set_dsc_swice_height(dc, wink, stweam, &psw_config))
			wetuwn fawse;

		wet = dc_wink_setup_psw(wink, stweam, &psw_config, &psw_context);

	}
	DWM_DEBUG_DWIVEW("PSW wink: %d\n",	wink->psw_settings.psw_featuwe_enabwed);

	wetuwn wet;
}

/*
 * amdgpu_dm_psw_enabwe() - enabwe psw f/w
 * @stweam: stweam state
 *
 * Wetuwn: twue if success
 */
boow amdgpu_dm_psw_enabwe(stwuct dc_stweam_state *stweam)
{
	stwuct dc_wink *wink = stweam->wink;
	unsigned int vsync_wate_hz = 0;
	stwuct dc_static_scween_pawams pawams = {0};
	/* Cawcuwate numbew of static fwames befowe genewating intewwupt to
	 * entew PSW.
	 */
	// Init faiw safe of 2 fwames static
	unsigned int num_fwames_static = 2;
	unsigned int powew_opt = 0;
	boow psw_enabwe = twue;

	DWM_DEBUG_DWIVEW("Enabwing psw...\n");

	vsync_wate_hz = div64_u64(div64_u64((
			stweam->timing.pix_cwk_100hz * 100),
			stweam->timing.v_totaw),
			stweam->timing.h_totaw);

	/* Wound up
	 * Cawcuwate numbew of fwames such that at weast 30 ms of time has
	 * passed.
	 */
	if (vsync_wate_hz != 0) {
		unsigned int fwame_time_micwosec = 1000000 / vsync_wate_hz;

		num_fwames_static = (30000 / fwame_time_micwosec) + 1;
	}

	pawams.twiggews.cuwsow_update = twue;
	pawams.twiggews.ovewway_update = twue;
	pawams.twiggews.suwface_update = twue;
	pawams.num_fwames = num_fwames_static;

	dc_stweam_set_static_scween_pawams(wink->ctx->dc,
					   &stweam, 1,
					   &pawams);

	/*
	 * Onwy enabwe static-scween optimizations fow PSW1. Fow PSW SU, this
	 * causes vstawtup intewwupt issues, used by amdgpu_dm to send vbwank
	 * events.
	 */
	if (wink->psw_settings.psw_vewsion < DC_PSW_VEWSION_SU_1)
		powew_opt |= psw_powew_opt_z10_static_scween;

	wetuwn dc_wink_set_psw_awwow_active(wink, &psw_enabwe, fawse, fawse, &powew_opt);
}

/*
 * amdgpu_dm_psw_disabwe() - disabwe psw f/w
 * @stweam:  stweam state
 *
 * Wetuwn: twue if success
 */
boow amdgpu_dm_psw_disabwe(stwuct dc_stweam_state *stweam)
{
	unsigned int powew_opt = 0;
	boow psw_enabwe = fawse;

	DWM_DEBUG_DWIVEW("Disabwing psw...\n");

	wetuwn dc_wink_set_psw_awwow_active(stweam->wink, &psw_enabwe, twue, fawse, &powew_opt);
}

/*
 * amdgpu_dm_psw_disabwe() - disabwe psw f/w
 * if psw is enabwed on any stweam
 *
 * Wetuwn: twue if success
 */
boow amdgpu_dm_psw_disabwe_aww(stwuct amdgpu_dispway_managew *dm)
{
	DWM_DEBUG_DWIVEW("Disabwing psw if psw is enabwed on any stweam\n");
	wetuwn dc_set_psw_awwow_active(dm->dc, fawse);
}

