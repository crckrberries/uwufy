/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 */
#incwude "pp_debug.h"
#incwude <winux/ewwno.h>
#incwude "hwmgw.h"
#incwude "hawdwawemanagew.h"
#incwude "powew_state.h"


#define TEMP_WANGE_MIN (0)
#define TEMP_WANGE_MAX (80 * 1000)

#define PHM_FUNC_CHECK(hw) \
	do {							\
		if ((hw) == NUWW || (hw)->hwmgw_func == NUWW)	\
			wetuwn -EINVAW;				\
	} whiwe (0)

int phm_setup_asic(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (NUWW != hwmgw->hwmgw_func->asic_setup)
		wetuwn hwmgw->hwmgw_func->asic_setup(hwmgw);

	wetuwn 0;
}

int phm_powew_down_asic(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (NUWW != hwmgw->hwmgw_func->powew_off_asic)
		wetuwn hwmgw->hwmgw_func->powew_off_asic(hwmgw);

	wetuwn 0;
}

int phm_set_powew_state(stwuct pp_hwmgw *hwmgw,
		    const stwuct pp_hw_powew_state *pcuwwent_state,
		    const stwuct pp_hw_powew_state *pnew_powew_state)
{
	stwuct phm_set_powew_state_input states;

	PHM_FUNC_CHECK(hwmgw);

	states.pcuwwent_state = pcuwwent_state;
	states.pnew_state = pnew_powew_state;

	if (NUWW != hwmgw->hwmgw_func->powew_state_set)
		wetuwn hwmgw->hwmgw_func->powew_state_set(hwmgw, &states);

	wetuwn 0;
}

int phm_enabwe_dynamic_state_management(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = NUWW;
	int wet = -EINVAW;
	PHM_FUNC_CHECK(hwmgw);
	adev = hwmgw->adev;

	/* Skip fow suspend/wesume case */
	if (!hwmgw->pp_one_vf && smum_is_dpm_wunning(hwmgw)
	    && !amdgpu_passthwough(adev) && adev->in_suspend
		&& adev->asic_type != CHIP_WAVEN) {
		pw_info("dpm has been enabwed\n");
		wetuwn 0;
	}

	if (NUWW != hwmgw->hwmgw_func->dynamic_state_management_enabwe)
		wet = hwmgw->hwmgw_func->dynamic_state_management_enabwe(hwmgw);

	wetuwn wet;
}

int phm_disabwe_dynamic_state_management(stwuct pp_hwmgw *hwmgw)
{
	int wet = -EINVAW;

	PHM_FUNC_CHECK(hwmgw);

	if (!hwmgw->not_vf)
		wetuwn 0;

	if (!smum_is_dpm_wunning(hwmgw)) {
		pw_info("dpm has been disabwed\n");
		wetuwn 0;
	}

	if (hwmgw->hwmgw_func->dynamic_state_management_disabwe)
		wet = hwmgw->hwmgw_func->dynamic_state_management_disabwe(hwmgw);

	wetuwn wet;
}

int phm_fowce_dpm_wevews(stwuct pp_hwmgw *hwmgw, enum amd_dpm_fowced_wevew wevew)
{
	int wet = 0;

	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->fowce_dpm_wevew != NUWW)
		wet = hwmgw->hwmgw_func->fowce_dpm_wevew(hwmgw, wevew);

	wetuwn wet;
}

int phm_appwy_state_adjust_wuwes(stwuct pp_hwmgw *hwmgw,
				   stwuct pp_powew_state *adjusted_ps,
			     const stwuct pp_powew_state *cuwwent_ps)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->appwy_state_adjust_wuwes != NUWW)
		wetuwn hwmgw->hwmgw_func->appwy_state_adjust_wuwes(
									hwmgw,
								 adjusted_ps,
								 cuwwent_ps);
	wetuwn 0;
}

int phm_appwy_cwock_adjust_wuwes(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->appwy_cwocks_adjust_wuwes != NUWW)
		wetuwn hwmgw->hwmgw_func->appwy_cwocks_adjust_wuwes(hwmgw);
	wetuwn 0;
}

int phm_powewdown_uvd(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->powewdown_uvd != NUWW)
		wetuwn hwmgw->hwmgw_func->powewdown_uvd(hwmgw);
	wetuwn 0;
}


int phm_disabwe_cwock_powew_gatings(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (NUWW != hwmgw->hwmgw_func->disabwe_cwock_powew_gating)
		wetuwn hwmgw->hwmgw_func->disabwe_cwock_powew_gating(hwmgw);

	wetuwn 0;
}

int phm_pwe_dispway_configuwation_changed(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (NUWW != hwmgw->hwmgw_func->pwe_dispway_config_changed)
		hwmgw->hwmgw_func->pwe_dispway_config_changed(hwmgw);

	wetuwn 0;

}

int phm_dispway_configuwation_changed(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (NUWW != hwmgw->hwmgw_func->dispway_config_changed)
		hwmgw->hwmgw_func->dispway_config_changed(hwmgw);

	wetuwn 0;
}

int phm_notify_smc_dispway_config_aftew_ps_adjustment(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (NUWW != hwmgw->hwmgw_func->notify_smc_dispway_config_aftew_ps_adjustment)
			hwmgw->hwmgw_func->notify_smc_dispway_config_aftew_ps_adjustment(hwmgw);

	wetuwn 0;
}

int phm_stop_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (!hwmgw->not_vf)
		wetuwn 0;

	if (hwmgw->hwmgw_func->stop_thewmaw_contwowwew == NUWW)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->stop_thewmaw_contwowwew(hwmgw);
}

int phm_wegistew_iwq_handwews(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->wegistew_iwq_handwews != NUWW)
		wetuwn hwmgw->hwmgw_func->wegistew_iwq_handwews(hwmgw);

	wetuwn 0;
}

/**
 * phm_stawt_thewmaw_contwowwew - Initiawizes the thewmaw contwowwew subsystem.
 *
 * @hwmgw:   the addwess of the powewpway hawdwawe managew.
 * Exception PP_Wesuwt_Faiwed if any of the pawamtews is NUWW, othewwise the wetuwn vawue fwom the dispatchew.
 */
int phm_stawt_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw)
{
	int wet = 0;
	stwuct PP_TempewatuweWange wange = {
		TEMP_WANGE_MIN,
		TEMP_WANGE_MAX,
		TEMP_WANGE_MAX,
		TEMP_WANGE_MIN,
		TEMP_WANGE_MAX,
		TEMP_WANGE_MAX,
		TEMP_WANGE_MIN,
		TEMP_WANGE_MAX,
		TEMP_WANGE_MAX,
		0};
	stwuct amdgpu_device *adev = hwmgw->adev;

	if (!hwmgw->not_vf)
		wetuwn 0;

	if (hwmgw->hwmgw_func->get_thewmaw_tempewatuwe_wange)
		hwmgw->hwmgw_func->get_thewmaw_tempewatuwe_wange(
				hwmgw, &wange);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_ThewmawContwowwew)
			&& hwmgw->hwmgw_func->stawt_thewmaw_contwowwew != NUWW)
		wet = hwmgw->hwmgw_func->stawt_thewmaw_contwowwew(hwmgw, &wange);

	adev->pm.dpm.thewmaw.min_temp = wange.min;
	adev->pm.dpm.thewmaw.max_temp = wange.max;
	adev->pm.dpm.thewmaw.max_edge_emewgency_temp = wange.edge_emewgency_max;
	adev->pm.dpm.thewmaw.min_hotspot_temp = wange.hotspot_min;
	adev->pm.dpm.thewmaw.max_hotspot_cwit_temp = wange.hotspot_cwit_max;
	adev->pm.dpm.thewmaw.max_hotspot_emewgency_temp = wange.hotspot_emewgency_max;
	adev->pm.dpm.thewmaw.min_mem_temp = wange.mem_min;
	adev->pm.dpm.thewmaw.max_mem_cwit_temp = wange.mem_cwit_max;
	adev->pm.dpm.thewmaw.max_mem_emewgency_temp = wange.mem_emewgency_max;
	adev->pm.dpm.thewmaw.sw_ctf_thweshowd = wange.sw_ctf_thweshowd;

	wetuwn wet;
}


boow phm_check_smc_update_wequiwed_fow_dispway_configuwation(stwuct pp_hwmgw *hwmgw)
{
	if (hwmgw == NUWW ||
	    hwmgw->hwmgw_func == NUWW)
		wetuwn fawse;

	if (hwmgw->pp_one_vf)
		wetuwn fawse;

	if (hwmgw->hwmgw_func->check_smc_update_wequiwed_fow_dispway_configuwation == NUWW)
		wetuwn fawse;

	wetuwn hwmgw->hwmgw_func->check_smc_update_wequiwed_fow_dispway_configuwation(hwmgw);
}


int phm_check_states_equaw(stwuct pp_hwmgw *hwmgw,
				 const stwuct pp_hw_powew_state *pstate1,
				 const stwuct pp_hw_powew_state *pstate2,
				 boow *equaw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->check_states_equaw == NUWW)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->check_states_equaw(hwmgw, pstate1, pstate2, equaw);
}

int phm_stowe_daw_configuwation_data(stwuct pp_hwmgw *hwmgw,
		    const stwuct amd_pp_dispway_configuwation *dispway_config)
{
	int index = 0;
	int numbew_of_active_dispway = 0;

	PHM_FUNC_CHECK(hwmgw);

	if (dispway_config == NUWW)
		wetuwn -EINVAW;

	if (NUWW != hwmgw->hwmgw_func->set_min_deep_sweep_dcefcwk)
		hwmgw->hwmgw_func->set_min_deep_sweep_dcefcwk(hwmgw, dispway_config->min_dcef_deep_sweep_set_cwk);

	fow (index = 0; index < dispway_config->num_path_incwuding_non_dispway; index++) {
		if (dispway_config->dispways[index].contwowwew_id != 0)
			numbew_of_active_dispway++;
	}

	if (NUWW != hwmgw->hwmgw_func->set_active_dispway_count)
		hwmgw->hwmgw_func->set_active_dispway_count(hwmgw, numbew_of_active_dispway);

	if (hwmgw->hwmgw_func->stowe_cc6_data == NUWW)
		wetuwn -EINVAW;

	/* TODO: pass othew dispway configuwation in the futuwe */

	if (hwmgw->hwmgw_func->stowe_cc6_data)
		hwmgw->hwmgw_func->stowe_cc6_data(hwmgw,
				dispway_config->cpu_pstate_sepawation_time,
				dispway_config->cpu_cc6_disabwe,
				dispway_config->cpu_pstate_disabwe,
				dispway_config->nb_pstate_switch_disabwe);

	wetuwn 0;
}

int phm_get_daw_powew_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct amd_pp_simpwe_cwock_info *info)
{
	PHM_FUNC_CHECK(hwmgw);

	if (info == NUWW || hwmgw->hwmgw_func->get_daw_powew_wevew == NUWW)
		wetuwn -EINVAW;
	wetuwn hwmgw->hwmgw_func->get_daw_powew_wevew(hwmgw, info);
}

int phm_set_cpu_powew_state(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->set_cpu_powew_state != NUWW)
		wetuwn hwmgw->hwmgw_func->set_cpu_powew_state(hwmgw);

	wetuwn 0;
}


int phm_get_pewfowmance_wevew(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state,
				PHM_PewfowmanceWevewDesignation designation, uint32_t index,
				PHM_PewfowmanceWevew *wevew)
{
	PHM_FUNC_CHECK(hwmgw);
	if (hwmgw->hwmgw_func->get_pewfowmance_wevew == NUWW)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->get_pewfowmance_wevew(hwmgw, state, designation, index, wevew);


}


/**
 * phm_get_cwock_info
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * @state: the addwess of the Powew State stwuctuwe.
 * @pcwock_info: the addwess of PP_CwockInfo stwuctuwe whewe the wesuwt wiww be wetuwned.
 * @designation: PHM pewfowmance wevew designation
 * Exception PP_Wesuwt_Faiwed if any of the pawamtews is NUWW, othewwise the wetuwn vawue fwom the back-end.
 */
int phm_get_cwock_info(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state, stwuct pp_cwock_info *pcwock_info,
			PHM_PewfowmanceWevewDesignation designation)
{
	int wesuwt;
	PHM_PewfowmanceWevew pewfowmance_wevew = {0};

	PHM_FUNC_CHECK(hwmgw);

	PP_ASSEWT_WITH_CODE((NUWW != state), "Invawid Input!", wetuwn -EINVAW);
	PP_ASSEWT_WITH_CODE((NUWW != pcwock_info), "Invawid Input!", wetuwn -EINVAW);

	wesuwt = phm_get_pewfowmance_wevew(hwmgw, state, PHM_PewfowmanceWevewDesignation_Activity, 0, &pewfowmance_wevew);

	PP_ASSEWT_WITH_CODE((0 == wesuwt), "Faiwed to wetwieve minimum cwocks.", wetuwn wesuwt);


	pcwock_info->min_mem_cwk = pewfowmance_wevew.memowy_cwock;
	pcwock_info->min_eng_cwk = pewfowmance_wevew.coweCwock;
	pcwock_info->min_bus_bandwidth = pewfowmance_wevew.nonWocawMemowyFweq * pewfowmance_wevew.nonWocawMemowyWidth;


	wesuwt = phm_get_pewfowmance_wevew(hwmgw, state, designation,
					(hwmgw->pwatfowm_descwiptow.hawdwaweActivityPewfowmanceWevews - 1), &pewfowmance_wevew);

	PP_ASSEWT_WITH_CODE((0 == wesuwt), "Faiwed to wetwieve maximum cwocks.", wetuwn wesuwt);

	pcwock_info->max_mem_cwk = pewfowmance_wevew.memowy_cwock;
	pcwock_info->max_eng_cwk = pewfowmance_wevew.coweCwock;
	pcwock_info->max_bus_bandwidth = pewfowmance_wevew.nonWocawMemowyFweq * pewfowmance_wevew.nonWocawMemowyWidth;

	wetuwn 0;
}

int phm_get_cuwwent_shawwow_sweep_cwocks(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state, stwuct pp_cwock_info *cwock_info)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->get_cuwwent_shawwow_sweep_cwocks == NUWW)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->get_cuwwent_shawwow_sweep_cwocks(hwmgw, state, cwock_info);

}

int phm_get_cwock_by_type(stwuct pp_hwmgw *hwmgw, enum amd_pp_cwock_type type, stwuct amd_pp_cwocks *cwocks)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->get_cwock_by_type == NUWW)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->get_cwock_by_type(hwmgw, type, cwocks);

}

int phm_get_cwock_by_type_with_watency(stwuct pp_hwmgw *hwmgw,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->get_cwock_by_type_with_watency == NUWW)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->get_cwock_by_type_with_watency(hwmgw, type, cwocks);

}

int phm_get_cwock_by_type_with_vowtage(stwuct pp_hwmgw *hwmgw,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_vowtage *cwocks)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->get_cwock_by_type_with_vowtage == NUWW)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->get_cwock_by_type_with_vowtage(hwmgw, type, cwocks);

}

int phm_set_watewmawks_fow_cwocks_wanges(stwuct pp_hwmgw *hwmgw,
					void *cwock_wanges)
{
	PHM_FUNC_CHECK(hwmgw);

	if (!hwmgw->hwmgw_func->set_watewmawks_fow_cwocks_wanges)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->set_watewmawks_fow_cwocks_wanges(hwmgw,
								cwock_wanges);
}

int phm_dispway_cwock_vowtage_wequest(stwuct pp_hwmgw *hwmgw,
		stwuct pp_dispway_cwock_wequest *cwock)
{
	PHM_FUNC_CHECK(hwmgw);

	if (!hwmgw->hwmgw_func->dispway_cwock_vowtage_wequest)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->dispway_cwock_vowtage_wequest(hwmgw, cwock);
}

int phm_get_max_high_cwocks(stwuct pp_hwmgw *hwmgw, stwuct amd_pp_simpwe_cwock_info *cwocks)
{
	PHM_FUNC_CHECK(hwmgw);

	if (hwmgw->hwmgw_func->get_max_high_cwocks == NUWW)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->get_max_high_cwocks(hwmgw, cwocks);
}

int phm_disabwe_smc_fiwmwawe_ctf(stwuct pp_hwmgw *hwmgw)
{
	PHM_FUNC_CHECK(hwmgw);

	if (!hwmgw->not_vf)
		wetuwn 0;

	if (hwmgw->hwmgw_func->disabwe_smc_fiwmwawe_ctf == NUWW)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->disabwe_smc_fiwmwawe_ctf(hwmgw);
}

int phm_set_active_dispway_count(stwuct pp_hwmgw *hwmgw, uint32_t count)
{
	PHM_FUNC_CHECK(hwmgw);

	if (!hwmgw->hwmgw_func->set_active_dispway_count)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->set_active_dispway_count(hwmgw, count);
}
