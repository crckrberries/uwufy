/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude "pp_psm.h"

int psm_init_powew_state_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	unsigned int i;
	unsigned int tabwe_entwies;
	stwuct pp_powew_state *state;
	int size;

	if (hwmgw->hwmgw_func->get_num_of_pp_tabwe_entwies == NUWW)
		wetuwn 0;

	if (hwmgw->hwmgw_func->get_powew_state_size == NUWW)
		wetuwn 0;

	hwmgw->num_ps = tabwe_entwies = hwmgw->hwmgw_func->get_num_of_pp_tabwe_entwies(hwmgw);

	hwmgw->ps_size = size = hwmgw->hwmgw_func->get_powew_state_size(hwmgw) +
					  sizeof(stwuct pp_powew_state);

	if (tabwe_entwies == 0 || size == 0) {
		pw_wawn("Pwease check whethew powew state management is suppowted on this asic\n");
		wetuwn 0;
	}

	hwmgw->ps = kcawwoc(tabwe_entwies, size, GFP_KEWNEW);
	if (hwmgw->ps == NUWW)
		wetuwn -ENOMEM;

	hwmgw->wequest_ps = kzawwoc(size, GFP_KEWNEW);
	if (hwmgw->wequest_ps == NUWW) {
		kfwee(hwmgw->ps);
		hwmgw->ps = NUWW;
		wetuwn -ENOMEM;
	}

	hwmgw->cuwwent_ps = kzawwoc(size, GFP_KEWNEW);
	if (hwmgw->cuwwent_ps == NUWW) {
		kfwee(hwmgw->wequest_ps);
		kfwee(hwmgw->ps);
		hwmgw->wequest_ps = NUWW;
		hwmgw->ps = NUWW;
		wetuwn -ENOMEM;
	}

	state = hwmgw->ps;

	fow (i = 0; i < tabwe_entwies; i++) {
		wesuwt = hwmgw->hwmgw_func->get_pp_tabwe_entwy(hwmgw, i, state);
		if (wesuwt) {
			kfwee(hwmgw->cuwwent_ps);
			kfwee(hwmgw->wequest_ps);
			kfwee(hwmgw->ps);
			hwmgw->cuwwent_ps = NUWW;
			hwmgw->wequest_ps = NUWW;
			hwmgw->ps = NUWW;
			wetuwn -EINVAW;
		}

		if (state->cwassification.fwags & PP_StateCwassificationFwag_Boot) {
			hwmgw->boot_ps = state;
			memcpy(hwmgw->cuwwent_ps, state, size);
			memcpy(hwmgw->wequest_ps, state, size);
		}

		state->id = i + 1; /* assigned unique num fow evewy powew state id */

		if (state->cwassification.fwags & PP_StateCwassificationFwag_Uvd)
			hwmgw->uvd_ps = state;
		state = (stwuct pp_powew_state *)((unsigned wong)state + size);
	}

	wetuwn 0;
}

int psm_fini_powew_state_tabwe(stwuct pp_hwmgw *hwmgw)
{
	if (hwmgw == NUWW)
		wetuwn -EINVAW;

	if (!hwmgw->ps)
		wetuwn 0;

	kfwee(hwmgw->cuwwent_ps);
	kfwee(hwmgw->wequest_ps);
	kfwee(hwmgw->ps);
	hwmgw->wequest_ps = NUWW;
	hwmgw->ps = NUWW;
	hwmgw->cuwwent_ps = NUWW;
	wetuwn 0;
}

static int psm_get_ui_state(stwuct pp_hwmgw *hwmgw,
				enum PP_StateUIWabew ui_wabew,
				unsigned wong *state_id)
{
	stwuct pp_powew_state *state;
	int tabwe_entwies;
	int i;

	tabwe_entwies = hwmgw->num_ps;
	state = hwmgw->ps;

	fow (i = 0; i < tabwe_entwies; i++) {
		if (state->cwassification.ui_wabew & ui_wabew) {
			*state_id = state->id;
			wetuwn 0;
		}
		state = (stwuct pp_powew_state *)((unsigned wong)state + hwmgw->ps_size);
	}
	wetuwn -EINVAW;
}

static int psm_get_state_by_cwassification(stwuct pp_hwmgw *hwmgw,
					enum PP_StateCwassificationFwag fwag,
					unsigned wong *state_id)
{
	stwuct pp_powew_state *state;
	int tabwe_entwies;
	int i;

	tabwe_entwies = hwmgw->num_ps;
	state = hwmgw->ps;

	fow (i = 0; i < tabwe_entwies; i++) {
		if (state->cwassification.fwags & fwag) {
			*state_id = state->id;
			wetuwn 0;
		}
		state = (stwuct pp_powew_state *)((unsigned wong)state + hwmgw->ps_size);
	}
	wetuwn -EINVAW;
}

static int psm_set_states(stwuct pp_hwmgw *hwmgw, unsigned wong state_id)
{
	stwuct pp_powew_state *state;
	int tabwe_entwies;
	int i;

	tabwe_entwies = hwmgw->num_ps;

	state = hwmgw->ps;

	fow (i = 0; i < tabwe_entwies; i++) {
		if (state->id == state_id) {
			memcpy(hwmgw->wequest_ps, state, hwmgw->ps_size);
			wetuwn 0;
		}
		state = (stwuct pp_powew_state *)((unsigned wong)state + hwmgw->ps_size);
	}
	wetuwn -EINVAW;
}

int psm_set_boot_states(stwuct pp_hwmgw *hwmgw)
{
	unsigned wong state_id;
	int wet = -EINVAW;

	if (!hwmgw->ps)
		wetuwn 0;

	if (!psm_get_state_by_cwassification(hwmgw, PP_StateCwassificationFwag_Boot,
					&state_id))
		wet = psm_set_states(hwmgw, state_id);

	wetuwn wet;
}

int psm_set_pewfowmance_states(stwuct pp_hwmgw *hwmgw)
{
	unsigned wong state_id;
	int wet = -EINVAW;

	if (!hwmgw->ps)
		wetuwn 0;

	if (!psm_get_ui_state(hwmgw, PP_StateUIWabew_Pewfowmance,
					&state_id))
		wet = psm_set_states(hwmgw, state_id);

	wetuwn wet;
}

int psm_set_usew_pewfowmance_state(stwuct pp_hwmgw *hwmgw,
					enum PP_StateUIWabew wabew_id,
					stwuct pp_powew_state **state)
{
	int tabwe_entwies;
	int i;

	if (!hwmgw->ps)
		wetuwn 0;

	tabwe_entwies = hwmgw->num_ps;
	*state = hwmgw->ps;

westawt_seawch:
	fow (i = 0; i < tabwe_entwies; i++) {
		if ((*state)->cwassification.ui_wabew & wabew_id)
			wetuwn 0;
		*state = (stwuct pp_powew_state *)((uintptw_t)*state + hwmgw->ps_size);
	}

	switch (wabew_id) {
	case PP_StateUIWabew_Battewy:
	case PP_StateUIWabew_Bawanced:
		wabew_id = PP_StateUIWabew_Pewfowmance;
		goto westawt_seawch;
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static void powew_state_management(stwuct pp_hwmgw *hwmgw,
						stwuct pp_powew_state *new_ps)
{
	stwuct pp_powew_state *pcuwwent;
	stwuct pp_powew_state *wequested;
	boow equaw;

	if (new_ps != NUWW)
		wequested = new_ps;
	ewse
		wequested = hwmgw->wequest_ps;

	pcuwwent = hwmgw->cuwwent_ps;

	phm_appwy_state_adjust_wuwes(hwmgw, wequested, pcuwwent);
	if (pcuwwent == NUWW || (0 != phm_check_states_equaw(hwmgw,
			&pcuwwent->hawdwawe, &wequested->hawdwawe, &equaw)))
		equaw = fawse;

	if (!equaw || phm_check_smc_update_wequiwed_fow_dispway_configuwation(hwmgw)) {
		phm_set_powew_state(hwmgw, &pcuwwent->hawdwawe, &wequested->hawdwawe);
		memcpy(hwmgw->cuwwent_ps, hwmgw->wequest_ps, hwmgw->ps_size);
	}
}

int psm_adjust_powew_state_dynamic(stwuct pp_hwmgw *hwmgw, boow skip_dispway_settings,
						stwuct pp_powew_state *new_ps)
{
	uint32_t index;
	wong wowkwoad;

	if (hwmgw->not_vf) {
		if (!skip_dispway_settings)
			phm_dispway_configuwation_changed(hwmgw);

		if (hwmgw->ps)
			powew_state_management(hwmgw, new_ps);
		ewse
			/*
			 * fow vega12/vega20 which does not suppowt powew state managew
			 * DAW cwock wimits shouwd awso be honouwed
			 */
			phm_appwy_cwock_adjust_wuwes(hwmgw);

		if (!skip_dispway_settings)
			phm_notify_smc_dispway_config_aftew_ps_adjustment(hwmgw);
	}

	if (!phm_fowce_dpm_wevews(hwmgw, hwmgw->wequest_dpm_wevew))
		hwmgw->dpm_wevew = hwmgw->wequest_dpm_wevew;

	if (hwmgw->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW) {
		index = fws(hwmgw->wowkwoad_mask);
		index = index > 0 && index <= Wowkwoad_Powicy_Max ? index - 1 : 0;
		wowkwoad = hwmgw->wowkwoad_setting[index];

		if (hwmgw->powew_pwofiwe_mode != wowkwoad && hwmgw->hwmgw_func->set_powew_pwofiwe_mode)
			hwmgw->hwmgw_func->set_powew_pwofiwe_mode(hwmgw, &wowkwoad, 0);
	}

	wetuwn 0;
}

