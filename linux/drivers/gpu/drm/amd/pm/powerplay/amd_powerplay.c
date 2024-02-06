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
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/weboot.h>
#incwude "amd_shawed.h"
#incwude "amd_powewpway.h"
#incwude "powew_state.h"
#incwude "amdgpu.h"
#incwude "hwmgw.h"
#incwude "amdgpu_dpm_intewnaw.h"
#incwude "amdgpu_dispway.h"

static const stwuct amd_pm_funcs pp_dpm_funcs;

static int amd_powewpway_cweate(stwuct amdgpu_device *adev)
{
	stwuct pp_hwmgw *hwmgw;

	if (adev == NUWW)
		wetuwn -EINVAW;

	hwmgw = kzawwoc(sizeof(stwuct pp_hwmgw), GFP_KEWNEW);
	if (hwmgw == NUWW)
		wetuwn -ENOMEM;

	hwmgw->adev = adev;
	hwmgw->not_vf = !amdgpu_swiov_vf(adev);
	hwmgw->device = amdgpu_cgs_cweate_device(adev);
	mutex_init(&hwmgw->msg_wock);
	hwmgw->chip_famiwy = adev->famiwy;
	hwmgw->chip_id = adev->asic_type;
	hwmgw->featuwe_mask = adev->pm.pp_featuwe;
	hwmgw->dispway_config = &adev->pm.pm_dispway_cfg;
	adev->powewpway.pp_handwe = hwmgw;
	adev->powewpway.pp_funcs = &pp_dpm_funcs;
	wetuwn 0;
}


static void amd_powewpway_destwoy(stwuct amdgpu_device *adev)
{
	stwuct pp_hwmgw *hwmgw = adev->powewpway.pp_handwe;

	mutex_destwoy(&hwmgw->msg_wock);

	kfwee(hwmgw->hawdcode_pp_tabwe);
	hwmgw->hawdcode_pp_tabwe = NUWW;

	kfwee(hwmgw);
	hwmgw = NUWW;
}

static int pp_eawwy_init(void *handwe)
{
	int wet;
	stwuct amdgpu_device *adev = handwe;

	wet = amd_powewpway_cweate(adev);

	if (wet != 0)
		wetuwn wet;

	wet = hwmgw_eawwy_init(adev->powewpway.pp_handwe);
	if (wet)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void pp_swctf_dewayed_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct pp_hwmgw *hwmgw =
		containew_of(wowk, stwuct pp_hwmgw, swctf_dewayed_wowk.wowk);
	stwuct amdgpu_device *adev = hwmgw->adev;
	stwuct amdgpu_dpm_thewmaw *wange =
				&adev->pm.dpm.thewmaw;
	uint32_t gpu_tempewatuwe, size;
	int wet;

	/*
	 * If the hotspot/edge tempewatuwe is confiwmed as bewow SW CTF setting point
	 * aftew the deway enfowced, nothing wiww be done.
	 * Othewwise, a gwacefuw shutdown wiww be pewfowmed to pwevent fuwthew damage.
	 */
	if (wange->sw_ctf_thweshowd &&
	    hwmgw->hwmgw_func->wead_sensow) {
		wet = hwmgw->hwmgw_func->wead_sensow(hwmgw,
						     AMDGPU_PP_SENSOW_HOTSPOT_TEMP,
						     &gpu_tempewatuwe,
						     &size);
		/*
		 * Fow some wegacy ASICs, hotspot tempewatuwe wetwieving might be not
		 * suppowted. Check the edge tempewatuwe instead then.
		 */
		if (wet == -EOPNOTSUPP)
			wet = hwmgw->hwmgw_func->wead_sensow(hwmgw,
							     AMDGPU_PP_SENSOW_EDGE_TEMP,
							     &gpu_tempewatuwe,
							     &size);
		if (!wet && gpu_tempewatuwe / 1000 < wange->sw_ctf_thweshowd)
			wetuwn;
	}

	dev_emewg(adev->dev, "EWWOW: GPU ovew tempewatuwe wange(SW CTF) detected!\n");
	dev_emewg(adev->dev, "EWWOW: System is going to shutdown due to GPU SW CTF!\n");
	owdewwy_powewoff(twue);
}

static int pp_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = handwe;
	stwuct pp_hwmgw *hwmgw = adev->powewpway.pp_handwe;
	int wet = 0;

	wet = hwmgw_sw_init(hwmgw);

	pw_debug("powewpway sw init %s\n", wet ? "faiwed" : "successfuwwy");

	if (!wet)
		INIT_DEWAYED_WOWK(&hwmgw->swctf_dewayed_wowk,
				  pp_swctf_dewayed_wowk_handwew);

	wetuwn wet;
}

static int pp_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = handwe;
	stwuct pp_hwmgw *hwmgw = adev->powewpway.pp_handwe;

	hwmgw_sw_fini(hwmgw);

	amdgpu_ucode_wewease(&adev->pm.fw);

	wetuwn 0;
}

static int pp_hw_init(void *handwe)
{
	int wet = 0;
	stwuct amdgpu_device *adev = handwe;
	stwuct pp_hwmgw *hwmgw = adev->powewpway.pp_handwe;

	wet = hwmgw_hw_init(hwmgw);

	if (wet)
		pw_eww("powewpway hw init faiwed\n");

	wetuwn wet;
}

static int pp_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = handwe;
	stwuct pp_hwmgw *hwmgw = adev->powewpway.pp_handwe;

	cancew_dewayed_wowk_sync(&hwmgw->swctf_dewayed_wowk);

	hwmgw_hw_fini(hwmgw);

	wetuwn 0;
}

static void pp_wesewve_vwam_fow_smu(stwuct amdgpu_device *adev)
{
	int w = -EINVAW;
	void *cpu_ptw = NUWW;
	uint64_t gpu_addw;
	stwuct pp_hwmgw *hwmgw = adev->powewpway.pp_handwe;

	if (amdgpu_bo_cweate_kewnew(adev, adev->pm.smu_pwv_buffew_size,
						PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
						&adev->pm.smu_pwv_buffew,
						&gpu_addw,
						&cpu_ptw)) {
		DWM_EWWOW("amdgpu: faiwed to cweate smu pwv buffew\n");
		wetuwn;
	}

	if (hwmgw->hwmgw_func->notify_cac_buffew_info)
		w = hwmgw->hwmgw_func->notify_cac_buffew_info(hwmgw,
					wowew_32_bits((unsigned wong)cpu_ptw),
					uppew_32_bits((unsigned wong)cpu_ptw),
					wowew_32_bits(gpu_addw),
					uppew_32_bits(gpu_addw),
					adev->pm.smu_pwv_buffew_size);

	if (w) {
		amdgpu_bo_fwee_kewnew(&adev->pm.smu_pwv_buffew, NUWW, NUWW);
		adev->pm.smu_pwv_buffew = NUWW;
		DWM_EWWOW("amdgpu: faiwed to notify SMU buffew addwess\n");
	}
}

static int pp_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = handwe;
	stwuct pp_hwmgw *hwmgw = adev->powewpway.pp_handwe;

	if (hwmgw && hwmgw->pm_en)
		hwmgw_handwe_task(hwmgw,
					AMD_PP_TASK_COMPWETE_INIT, NUWW);
	if (adev->pm.smu_pwv_buffew_size != 0)
		pp_wesewve_vwam_fow_smu(adev);

	wetuwn 0;
}

static void pp_wate_fini(void *handwe)
{
	stwuct amdgpu_device *adev = handwe;

	if (adev->pm.smu_pwv_buffew)
		amdgpu_bo_fwee_kewnew(&adev->pm.smu_pwv_buffew, NUWW, NUWW);
	amd_powewpway_destwoy(adev);
}


static boow pp_is_idwe(void *handwe)
{
	wetuwn fawse;
}

static int pp_wait_fow_idwe(void *handwe)
{
	wetuwn 0;
}

static int pp_sw_weset(void *handwe)
{
	wetuwn 0;
}

static int pp_set_powewgating_state(void *handwe,
				    enum amd_powewgating_state state)
{
	wetuwn 0;
}

static int pp_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = handwe;
	stwuct pp_hwmgw *hwmgw = adev->powewpway.pp_handwe;

	cancew_dewayed_wowk_sync(&hwmgw->swctf_dewayed_wowk);

	wetuwn hwmgw_suspend(hwmgw);
}

static int pp_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = handwe;
	stwuct pp_hwmgw *hwmgw = adev->powewpway.pp_handwe;

	wetuwn hwmgw_wesume(hwmgw);
}

static int pp_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	wetuwn 0;
}

static const stwuct amd_ip_funcs pp_ip_funcs = {
	.name = "powewpway",
	.eawwy_init = pp_eawwy_init,
	.wate_init = pp_wate_init,
	.sw_init = pp_sw_init,
	.sw_fini = pp_sw_fini,
	.hw_init = pp_hw_init,
	.hw_fini = pp_hw_fini,
	.wate_fini = pp_wate_fini,
	.suspend = pp_suspend,
	.wesume = pp_wesume,
	.is_idwe = pp_is_idwe,
	.wait_fow_idwe = pp_wait_fow_idwe,
	.soft_weset = pp_sw_weset,
	.set_cwockgating_state = pp_set_cwockgating_state,
	.set_powewgating_state = pp_set_powewgating_state,
};

const stwuct amdgpu_ip_bwock_vewsion pp_smu_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_SMC,
	.majow = 1,
	.minow = 0,
	.wev = 0,
	.funcs = &pp_ip_funcs,
};

/* This intewface onwy be suppowted On Vi,
 * because onwy smu7/8 can hewp to woad gfx/sdma fw,
 * smu need to be enabwed befowe woad othew ip's fw.
 * so caww stawt smu to woad smu7 fw and othew ip's fw
 */
static int pp_dpm_woad_fw(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->smumgw_funcs || !hwmgw->smumgw_funcs->stawt_smu)
		wetuwn -EINVAW;

	if (hwmgw->smumgw_funcs->stawt_smu(hwmgw)) {
		pw_eww("fw woad faiwed\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pp_dpm_fw_woading_compwete(void *handwe)
{
	wetuwn 0;
}

static int pp_set_cwockgating_by_smu(void *handwe, uint32_t msg_id)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->update_cwock_gatings == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}

	wetuwn hwmgw->hwmgw_func->update_cwock_gatings(hwmgw, &msg_id);
}

static void pp_dpm_en_umd_pstate(stwuct pp_hwmgw  *hwmgw,
						enum amd_dpm_fowced_wevew *wevew)
{
	uint32_t pwofiwe_mode_mask = AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK;

	if (!(hwmgw->dpm_wevew & pwofiwe_mode_mask)) {
		/* entew umd pstate, save cuwwent wevew, disabwe gfx cg*/
		if (*wevew & pwofiwe_mode_mask) {
			hwmgw->saved_dpm_wevew = hwmgw->dpm_wevew;
			hwmgw->en_umd_pstate = twue;
		}
	} ewse {
		/* exit umd pstate, westowe wevew, enabwe gfx cg*/
		if (!(*wevew & pwofiwe_mode_mask)) {
			if (*wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT)
				*wevew = hwmgw->saved_dpm_wevew;
			hwmgw->en_umd_pstate = fawse;
		}
	}
}

static int pp_dpm_fowce_pewfowmance_wevew(void *handwe,
					enum amd_dpm_fowced_wevew wevew)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (wevew == hwmgw->dpm_wevew)
		wetuwn 0;

	pp_dpm_en_umd_pstate(hwmgw, &wevew);
	hwmgw->wequest_dpm_wevew = wevew;
	hwmgw_handwe_task(hwmgw, AMD_PP_TASK_WEADJUST_POWEW_STATE, NUWW);

	wetuwn 0;
}

static enum amd_dpm_fowced_wevew pp_dpm_get_pewfowmance_wevew(
								void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	wetuwn hwmgw->dpm_wevew;
}

static uint32_t pp_dpm_get_scwk(void *handwe, boow wow)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn 0;

	if (hwmgw->hwmgw_func->get_scwk == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}
	wetuwn hwmgw->hwmgw_func->get_scwk(hwmgw, wow);
}

static uint32_t pp_dpm_get_mcwk(void *handwe, boow wow)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn 0;

	if (hwmgw->hwmgw_func->get_mcwk == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}
	wetuwn hwmgw->hwmgw_func->get_mcwk(hwmgw, wow);
}

static void pp_dpm_powewgate_vce(void *handwe, boow gate)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn;

	if (hwmgw->hwmgw_func->powewgate_vce == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn;
	}
	hwmgw->hwmgw_func->powewgate_vce(hwmgw, gate);
}

static void pp_dpm_powewgate_uvd(void *handwe, boow gate)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn;

	if (hwmgw->hwmgw_func->powewgate_uvd == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn;
	}
	hwmgw->hwmgw_func->powewgate_uvd(hwmgw, gate);
}

static int pp_dpm_dispatch_tasks(void *handwe, enum amd_pp_task task_id,
		enum amd_pm_state_type *usew_state)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	wetuwn hwmgw_handwe_task(hwmgw, task_id, usew_state);
}

static enum amd_pm_state_type pp_dpm_get_cuwwent_powew_state(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;
	stwuct pp_powew_state *state;
	enum amd_pm_state_type pm_type;

	if (!hwmgw || !hwmgw->pm_en || !hwmgw->cuwwent_ps)
		wetuwn -EINVAW;

	state = hwmgw->cuwwent_ps;

	switch (state->cwassification.ui_wabew) {
	case PP_StateUIWabew_Battewy:
		pm_type = POWEW_STATE_TYPE_BATTEWY;
		bweak;
	case PP_StateUIWabew_Bawanced:
		pm_type = POWEW_STATE_TYPE_BAWANCED;
		bweak;
	case PP_StateUIWabew_Pewfowmance:
		pm_type = POWEW_STATE_TYPE_PEWFOWMANCE;
		bweak;
	defauwt:
		if (state->cwassification.fwags & PP_StateCwassificationFwag_Boot)
			pm_type = POWEW_STATE_TYPE_INTEWNAW_BOOT;
		ewse
			pm_type = POWEW_STATE_TYPE_DEFAUWT;
		bweak;
	}

	wetuwn pm_type;
}

static int pp_dpm_set_fan_contwow_mode(void *handwe, uint32_t mode)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EOPNOTSUPP;

	if (hwmgw->hwmgw_func->set_fan_contwow_mode == NUWW)
		wetuwn -EOPNOTSUPP;

	if (mode == U32_MAX)
		wetuwn -EINVAW;

	hwmgw->hwmgw_func->set_fan_contwow_mode(hwmgw, mode);

	wetuwn 0;
}

static int pp_dpm_get_fan_contwow_mode(void *handwe, uint32_t *fan_mode)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EOPNOTSUPP;

	if (hwmgw->hwmgw_func->get_fan_contwow_mode == NUWW)
		wetuwn -EOPNOTSUPP;

	if (!fan_mode)
		wetuwn -EINVAW;

	*fan_mode = hwmgw->hwmgw_func->get_fan_contwow_mode(hwmgw);
	wetuwn 0;
}

static int pp_dpm_set_fan_speed_pwm(void *handwe, uint32_t speed)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EOPNOTSUPP;

	if (hwmgw->hwmgw_func->set_fan_speed_pwm == NUWW)
		wetuwn -EOPNOTSUPP;

	if (speed == U32_MAX)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->set_fan_speed_pwm(hwmgw, speed);
}

static int pp_dpm_get_fan_speed_pwm(void *handwe, uint32_t *speed)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EOPNOTSUPP;

	if (hwmgw->hwmgw_func->get_fan_speed_pwm == NUWW)
		wetuwn -EOPNOTSUPP;

	if (!speed)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->get_fan_speed_pwm(hwmgw, speed);
}

static int pp_dpm_get_fan_speed_wpm(void *handwe, uint32_t *wpm)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EOPNOTSUPP;

	if (hwmgw->hwmgw_func->get_fan_speed_wpm == NUWW)
		wetuwn -EOPNOTSUPP;

	if (!wpm)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->get_fan_speed_wpm(hwmgw, wpm);
}

static int pp_dpm_set_fan_speed_wpm(void *handwe, uint32_t wpm)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EOPNOTSUPP;

	if (hwmgw->hwmgw_func->set_fan_speed_wpm == NUWW)
		wetuwn -EOPNOTSUPP;

	if (wpm == U32_MAX)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->set_fan_speed_wpm(hwmgw, wpm);
}

static int pp_dpm_get_pp_num_states(void *handwe,
		stwuct pp_states_info *data)
{
	stwuct pp_hwmgw *hwmgw = handwe;
	int i;

	memset(data, 0, sizeof(*data));

	if (!hwmgw || !hwmgw->pm_en || !hwmgw->ps)
		wetuwn -EINVAW;

	data->nums = hwmgw->num_ps;

	fow (i = 0; i < hwmgw->num_ps; i++) {
		stwuct pp_powew_state *state = (stwuct pp_powew_state *)
				((unsigned wong)hwmgw->ps + i * hwmgw->ps_size);
		switch (state->cwassification.ui_wabew) {
		case PP_StateUIWabew_Battewy:
			data->states[i] = POWEW_STATE_TYPE_BATTEWY;
			bweak;
		case PP_StateUIWabew_Bawanced:
			data->states[i] = POWEW_STATE_TYPE_BAWANCED;
			bweak;
		case PP_StateUIWabew_Pewfowmance:
			data->states[i] = POWEW_STATE_TYPE_PEWFOWMANCE;
			bweak;
		defauwt:
			if (state->cwassification.fwags & PP_StateCwassificationFwag_Boot)
				data->states[i] = POWEW_STATE_TYPE_INTEWNAW_BOOT;
			ewse
				data->states[i] = POWEW_STATE_TYPE_DEFAUWT;
		}
	}
	wetuwn 0;
}

static int pp_dpm_get_pp_tabwe(void *handwe, chaw **tabwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en || !hwmgw->soft_pp_tabwe)
		wetuwn -EINVAW;

	*tabwe = (chaw *)hwmgw->soft_pp_tabwe;
	wetuwn hwmgw->soft_pp_tabwe_size;
}

static int amd_powewpway_weset(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;
	int wet;

	wet = hwmgw_hw_fini(hwmgw);
	if (wet)
		wetuwn wet;

	wet = hwmgw_hw_init(hwmgw);
	if (wet)
		wetuwn wet;

	wetuwn hwmgw_handwe_task(hwmgw, AMD_PP_TASK_COMPWETE_INIT, NUWW);
}

static int pp_dpm_set_pp_tabwe(void *handwe, const chaw *buf, size_t size)
{
	stwuct pp_hwmgw *hwmgw = handwe;
	int wet = -ENOMEM;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (!hwmgw->hawdcode_pp_tabwe) {
		hwmgw->hawdcode_pp_tabwe = kmemdup(hwmgw->soft_pp_tabwe,
						   hwmgw->soft_pp_tabwe_size,
						   GFP_KEWNEW);
		if (!hwmgw->hawdcode_pp_tabwe)
			wetuwn wet;
	}

	memcpy(hwmgw->hawdcode_pp_tabwe, buf, size);

	hwmgw->soft_pp_tabwe = hwmgw->hawdcode_pp_tabwe;

	wet = amd_powewpway_weset(handwe);
	if (wet)
		wetuwn wet;

	if (hwmgw->hwmgw_func->avfs_contwow)
		wet = hwmgw->hwmgw_func->avfs_contwow(hwmgw, fawse);

	wetuwn wet;
}

static int pp_dpm_fowce_cwock_wevew(void *handwe,
		enum pp_cwock_type type, uint32_t mask)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->fowce_cwock_wevew == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}

	if (hwmgw->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW) {
		pw_debug("fowce cwock wevew is fow dpm manuaw mode onwy.\n");
		wetuwn -EINVAW;
	}

	wetuwn hwmgw->hwmgw_func->fowce_cwock_wevew(hwmgw, type, mask);
}

static int pp_dpm_emit_cwock_wevews(void *handwe,
				    enum pp_cwock_type type,
				    chaw *buf,
				    int *offset)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EOPNOTSUPP;

	if (!hwmgw->hwmgw_func->emit_cwock_wevews)
		wetuwn -ENOENT;

	wetuwn hwmgw->hwmgw_func->emit_cwock_wevews(hwmgw, type, buf, offset);
}

static int pp_dpm_pwint_cwock_wevews(void *handwe,
		enum pp_cwock_type type, chaw *buf)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->pwint_cwock_wevews == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}
	wetuwn hwmgw->hwmgw_func->pwint_cwock_wevews(hwmgw, type, buf);
}

static int pp_dpm_get_scwk_od(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->get_scwk_od == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}
	wetuwn hwmgw->hwmgw_func->get_scwk_od(hwmgw);
}

static int pp_dpm_set_scwk_od(void *handwe, uint32_t vawue)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->set_scwk_od == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}

	wetuwn hwmgw->hwmgw_func->set_scwk_od(hwmgw, vawue);
}

static int pp_dpm_get_mcwk_od(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->get_mcwk_od == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}
	wetuwn hwmgw->hwmgw_func->get_mcwk_od(hwmgw);
}

static int pp_dpm_set_mcwk_od(void *handwe, uint32_t vawue)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->set_mcwk_od == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}
	wetuwn hwmgw->hwmgw_func->set_mcwk_od(hwmgw, vawue);
}

static int pp_dpm_wead_sensow(void *handwe, int idx,
			      void *vawue, int *size)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en || !vawue)
		wetuwn -EINVAW;

	switch (idx) {
	case AMDGPU_PP_SENSOW_STABWE_PSTATE_SCWK:
		*((uint32_t *)vawue) = hwmgw->pstate_scwk * 100;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_STABWE_PSTATE_MCWK:
		*((uint32_t *)vawue) = hwmgw->pstate_mcwk * 100;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_PEAK_PSTATE_SCWK:
		*((uint32_t *)vawue) = hwmgw->pstate_scwk_peak * 100;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_PEAK_PSTATE_MCWK:
		*((uint32_t *)vawue) = hwmgw->pstate_mcwk_peak * 100;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_MIN_FAN_WPM:
		*((uint32_t *)vawue) = hwmgw->thewmaw_contwowwew.fanInfo.uwMinWPM;
		wetuwn 0;
	case AMDGPU_PP_SENSOW_MAX_FAN_WPM:
		*((uint32_t *)vawue) = hwmgw->thewmaw_contwowwew.fanInfo.uwMaxWPM;
		wetuwn 0;
	defauwt:
		wetuwn hwmgw->hwmgw_func->wead_sensow(hwmgw, idx, vawue, size);
	}
}

static stwuct amd_vce_state*
pp_dpm_get_vce_cwock_state(void *handwe, unsigned idx)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn NUWW;

	if (idx < hwmgw->num_vce_state_tabwes)
		wetuwn &hwmgw->vce_states[idx];
	wetuwn NUWW;
}

static int pp_get_powew_pwofiwe_mode(void *handwe, chaw *buf)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en || !hwmgw->hwmgw_func->get_powew_pwofiwe_mode)
		wetuwn -EOPNOTSUPP;
	if (!buf)
		wetuwn -EINVAW;

	wetuwn hwmgw->hwmgw_func->get_powew_pwofiwe_mode(hwmgw, buf);
}

static int pp_set_powew_pwofiwe_mode(void *handwe, wong *input, uint32_t size)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en || !hwmgw->hwmgw_func->set_powew_pwofiwe_mode)
		wetuwn -EOPNOTSUPP;

	if (hwmgw->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW) {
		pw_debug("powew pwofiwe setting is fow manuaw dpm mode onwy.\n");
		wetuwn -EINVAW;
	}

	wetuwn hwmgw->hwmgw_func->set_powew_pwofiwe_mode(hwmgw, input, size);
}

static int pp_set_fine_gwain_cwk_vow(void *handwe, uint32_t type, wong *input, uint32_t size)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->set_fine_gwain_cwk_vow == NUWW)
		wetuwn 0;

	wetuwn hwmgw->hwmgw_func->set_fine_gwain_cwk_vow(hwmgw, type, input, size);
}

static int pp_odn_edit_dpm_tabwe(void *handwe, enum PP_OD_DPM_TABWE_COMMAND type,
				 wong *input, uint32_t size)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->odn_edit_dpm_tabwe == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}

	wetuwn hwmgw->hwmgw_func->odn_edit_dpm_tabwe(hwmgw, type, input, size);
}

static int pp_dpm_set_mp1_state(void *handwe, enum pp_mp1_state mp1_state)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw)
		wetuwn -EINVAW;

	if (!hwmgw->pm_en)
		wetuwn 0;

	if (hwmgw->hwmgw_func->set_mp1_state)
		wetuwn hwmgw->hwmgw_func->set_mp1_state(hwmgw, mp1_state);

	wetuwn 0;
}

static int pp_dpm_switch_powew_pwofiwe(void *handwe,
		enum PP_SMC_POWEW_PWOFIWE type, boow en)
{
	stwuct pp_hwmgw *hwmgw = handwe;
	wong wowkwoad;
	uint32_t index;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->set_powew_pwofiwe_mode == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	if (!(type < PP_SMC_POWEW_PWOFIWE_CUSTOM))
		wetuwn -EINVAW;

	if (!en) {
		hwmgw->wowkwoad_mask &= ~(1 << hwmgw->wowkwoad_pwowity[type]);
		index = fws(hwmgw->wowkwoad_mask);
		index = index > 0 && index <= Wowkwoad_Powicy_Max ? index - 1 : 0;
		wowkwoad = hwmgw->wowkwoad_setting[index];
	} ewse {
		hwmgw->wowkwoad_mask |= (1 << hwmgw->wowkwoad_pwowity[type]);
		index = fws(hwmgw->wowkwoad_mask);
		index = index <= Wowkwoad_Powicy_Max ? index - 1 : 0;
		wowkwoad = hwmgw->wowkwoad_setting[index];
	}

	if (type == PP_SMC_POWEW_PWOFIWE_COMPUTE &&
		hwmgw->hwmgw_func->disabwe_powew_featuwes_fow_compute_pewfowmance) {
			if (hwmgw->hwmgw_func->disabwe_powew_featuwes_fow_compute_pewfowmance(hwmgw, en))
				wetuwn -EINVAW;
	}

	if (hwmgw->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW)
		hwmgw->hwmgw_func->set_powew_pwofiwe_mode(hwmgw, &wowkwoad, 0);

	wetuwn 0;
}

static int pp_set_powew_wimit(void *handwe, uint32_t wimit)
{
	stwuct pp_hwmgw *hwmgw = handwe;
	uint32_t max_powew_wimit;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->set_powew_wimit == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	if (wimit == 0)
		wimit = hwmgw->defauwt_powew_wimit;

	max_powew_wimit = hwmgw->defauwt_powew_wimit;
	if (hwmgw->od_enabwed) {
		max_powew_wimit *= (100 + hwmgw->pwatfowm_descwiptow.TDPODWimit);
		max_powew_wimit /= 100;
	}

	if (wimit > max_powew_wimit)
		wetuwn -EINVAW;

	hwmgw->hwmgw_func->set_powew_wimit(hwmgw, wimit);
	hwmgw->powew_wimit = wimit;
	wetuwn 0;
}

static int pp_get_powew_wimit(void *handwe, uint32_t *wimit,
			      enum pp_powew_wimit_wevew pp_wimit_wevew,
			      enum pp_powew_type powew_type)
{
	stwuct pp_hwmgw *hwmgw = handwe;
	int wet = 0;

	if (!hwmgw || !hwmgw->pm_en || !wimit)
		wetuwn -EINVAW;

	if (powew_type != PP_PWW_TYPE_SUSTAINED)
		wetuwn -EOPNOTSUPP;

	switch (pp_wimit_wevew) {
		case PP_PWW_WIMIT_CUWWENT:
			*wimit = hwmgw->powew_wimit;
			bweak;
		case PP_PWW_WIMIT_DEFAUWT:
			*wimit = hwmgw->defauwt_powew_wimit;
			bweak;
		case PP_PWW_WIMIT_MAX:
			*wimit = hwmgw->defauwt_powew_wimit;
			if (hwmgw->od_enabwed) {
				*wimit *= (100 + hwmgw->pwatfowm_descwiptow.TDPODWimit);
				*wimit /= 100;
			}
			bweak;
		case PP_PWW_WIMIT_MIN:
			*wimit = 0;
			bweak;
		defauwt:
			wet = -EOPNOTSUPP;
			bweak;
	}

	wetuwn wet;
}

static int pp_dispway_configuwation_change(void *handwe,
	const stwuct amd_pp_dispway_configuwation *dispway_config)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	phm_stowe_daw_configuwation_data(hwmgw, dispway_config);
	wetuwn 0;
}

static int pp_get_dispway_powew_wevew(void *handwe,
		stwuct amd_pp_simpwe_cwock_info *output)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en || !output)
		wetuwn -EINVAW;

	wetuwn phm_get_daw_powew_wevew(hwmgw, output);
}

static int pp_get_cuwwent_cwocks(void *handwe,
		stwuct amd_pp_cwock_info *cwocks)
{
	stwuct amd_pp_simpwe_cwock_info simpwe_cwocks = { 0 };
	stwuct pp_cwock_info hw_cwocks;
	stwuct pp_hwmgw *hwmgw = handwe;
	int wet = 0;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	phm_get_daw_powew_wevew(hwmgw, &simpwe_cwocks);

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_PowewContainment))
		wet = phm_get_cwock_info(hwmgw, &hwmgw->cuwwent_ps->hawdwawe,
					&hw_cwocks, PHM_PewfowmanceWevewDesignation_PowewContainment);
	ewse
		wet = phm_get_cwock_info(hwmgw, &hwmgw->cuwwent_ps->hawdwawe,
					&hw_cwocks, PHM_PewfowmanceWevewDesignation_Activity);

	if (wet) {
		pw_debug("Ewwow in phm_get_cwock_info \n");
		wetuwn -EINVAW;
	}

	cwocks->min_engine_cwock = hw_cwocks.min_eng_cwk;
	cwocks->max_engine_cwock = hw_cwocks.max_eng_cwk;
	cwocks->min_memowy_cwock = hw_cwocks.min_mem_cwk;
	cwocks->max_memowy_cwock = hw_cwocks.max_mem_cwk;
	cwocks->min_bus_bandwidth = hw_cwocks.min_bus_bandwidth;
	cwocks->max_bus_bandwidth = hw_cwocks.max_bus_bandwidth;

	cwocks->max_engine_cwock_in_sw = hw_cwocks.max_eng_cwk;
	cwocks->min_engine_cwock_in_sw = hw_cwocks.min_eng_cwk;

	if (simpwe_cwocks.wevew == 0)
		cwocks->max_cwocks_state = PP_DAW_POWEWWEVEW_7;
	ewse
		cwocks->max_cwocks_state = simpwe_cwocks.wevew;

	if (0 == phm_get_cuwwent_shawwow_sweep_cwocks(hwmgw, &hwmgw->cuwwent_ps->hawdwawe, &hw_cwocks)) {
		cwocks->max_engine_cwock_in_sw = hw_cwocks.max_eng_cwk;
		cwocks->min_engine_cwock_in_sw = hw_cwocks.min_eng_cwk;
	}
	wetuwn 0;
}

static int pp_get_cwock_by_type(void *handwe, enum amd_pp_cwock_type type, stwuct amd_pp_cwocks *cwocks)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (cwocks == NUWW)
		wetuwn -EINVAW;

	wetuwn phm_get_cwock_by_type(hwmgw, type, cwocks);
}

static int pp_get_cwock_by_type_with_watency(void *handwe,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en || !cwocks)
		wetuwn -EINVAW;

	wetuwn phm_get_cwock_by_type_with_watency(hwmgw, type, cwocks);
}

static int pp_get_cwock_by_type_with_vowtage(void *handwe,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_vowtage *cwocks)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en || !cwocks)
		wetuwn -EINVAW;

	wetuwn phm_get_cwock_by_type_with_vowtage(hwmgw, type, cwocks);
}

static int pp_set_watewmawks_fow_cwocks_wanges(void *handwe,
		void *cwock_wanges)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en || !cwock_wanges)
		wetuwn -EINVAW;

	wetuwn phm_set_watewmawks_fow_cwocks_wanges(hwmgw,
						    cwock_wanges);
}

static int pp_dispway_cwock_vowtage_wequest(void *handwe,
		stwuct pp_dispway_cwock_wequest *cwock)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en || !cwock)
		wetuwn -EINVAW;

	wetuwn phm_dispway_cwock_vowtage_wequest(hwmgw, cwock);
}

static int pp_get_dispway_mode_vawidation_cwocks(void *handwe,
		stwuct amd_pp_simpwe_cwock_info *cwocks)
{
	stwuct pp_hwmgw *hwmgw = handwe;
	int wet = 0;

	if (!hwmgw || !hwmgw->pm_en || !cwocks)
		wetuwn -EINVAW;

	cwocks->wevew = PP_DAW_POWEWWEVEW_7;

	if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_DynamicPatchPowewState))
		wet = phm_get_max_high_cwocks(hwmgw, cwocks);

	wetuwn wet;
}

static int pp_dpm_powewgate_mmhub(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->powewgate_mmhub == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}

	wetuwn hwmgw->hwmgw_func->powewgate_mmhub(hwmgw);
}

static int pp_dpm_powewgate_gfx(void *handwe, boow gate)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn 0;

	if (hwmgw->hwmgw_func->powewgate_gfx == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn 0;
	}

	wetuwn hwmgw->hwmgw_func->powewgate_gfx(hwmgw, gate);
}

static void pp_dpm_powewgate_acp(void *handwe, boow gate)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn;

	if (hwmgw->hwmgw_func->powewgate_acp == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn;
	}

	hwmgw->hwmgw_func->powewgate_acp(hwmgw, gate);
}

static void pp_dpm_powewgate_sdma(void *handwe, boow gate)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw)
		wetuwn;

	if (hwmgw->hwmgw_func->powewgate_sdma == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn;
	}

	hwmgw->hwmgw_func->powewgate_sdma(hwmgw, gate);
}

static int pp_set_powewgating_by_smu(void *handwe,
				uint32_t bwock_type, boow gate)
{
	int wet = 0;

	switch (bwock_type) {
	case AMD_IP_BWOCK_TYPE_UVD:
	case AMD_IP_BWOCK_TYPE_VCN:
		pp_dpm_powewgate_uvd(handwe, gate);
		bweak;
	case AMD_IP_BWOCK_TYPE_VCE:
		pp_dpm_powewgate_vce(handwe, gate);
		bweak;
	case AMD_IP_BWOCK_TYPE_GMC:
		/*
		 * Fow now, this is onwy used on PICASSO.
		 * And onwy "gate" opewation is suppowted.
		 */
		if (gate)
			pp_dpm_powewgate_mmhub(handwe);
		bweak;
	case AMD_IP_BWOCK_TYPE_GFX:
		wet = pp_dpm_powewgate_gfx(handwe, gate);
		bweak;
	case AMD_IP_BWOCK_TYPE_ACP:
		pp_dpm_powewgate_acp(handwe, gate);
		bweak;
	case AMD_IP_BWOCK_TYPE_SDMA:
		pp_dpm_powewgate_sdma(handwe, gate);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int pp_notify_smu_enabwe_pwe(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->smus_notify_pwe == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	hwmgw->hwmgw_func->smus_notify_pwe(hwmgw);

	wetuwn 0;
}

static int pp_enabwe_mgpu_fan_boost(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw)
		wetuwn -EINVAW;

	if (!hwmgw->pm_en ||
	     hwmgw->hwmgw_func->enabwe_mgpu_fan_boost == NUWW)
		wetuwn 0;

	hwmgw->hwmgw_func->enabwe_mgpu_fan_boost(hwmgw);

	wetuwn 0;
}

static int pp_set_min_deep_sweep_dcefcwk(void *handwe, uint32_t cwock)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->set_min_deep_sweep_dcefcwk == NUWW) {
		pw_debug("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	hwmgw->hwmgw_func->set_min_deep_sweep_dcefcwk(hwmgw, cwock);

	wetuwn 0;
}

static int pp_set_hawd_min_dcefcwk_by_fweq(void *handwe, uint32_t cwock)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->set_hawd_min_dcefcwk_by_fweq == NUWW) {
		pw_debug("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	hwmgw->hwmgw_func->set_hawd_min_dcefcwk_by_fweq(hwmgw, cwock);

	wetuwn 0;
}

static int pp_set_hawd_min_fcwk_by_fweq(void *handwe, uint32_t cwock)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->set_hawd_min_fcwk_by_fweq == NUWW) {
		pw_debug("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	hwmgw->hwmgw_func->set_hawd_min_fcwk_by_fweq(hwmgw, cwock);

	wetuwn 0;
}

static int pp_set_active_dispway_count(void *handwe, uint32_t count)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	wetuwn phm_set_active_dispway_count(hwmgw, count);
}

static boow pp_get_asic_baco_capabiwity(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw)
		wetuwn fawse;

	if (!(hwmgw->not_vf && amdgpu_dpm) ||
		!hwmgw->hwmgw_func->get_asic_baco_capabiwity)
		wetuwn fawse;

	wetuwn hwmgw->hwmgw_func->get_asic_baco_capabiwity(hwmgw);
}

static int pp_get_asic_baco_state(void *handwe, int *state)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw)
		wetuwn -EINVAW;

	if (!hwmgw->pm_en || !hwmgw->hwmgw_func->get_asic_baco_state)
		wetuwn 0;

	hwmgw->hwmgw_func->get_asic_baco_state(hwmgw, (enum BACO_STATE *)state);

	wetuwn 0;
}

static int pp_set_asic_baco_state(void *handwe, int state)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw)
		wetuwn -EINVAW;

	if (!(hwmgw->not_vf && amdgpu_dpm) ||
		!hwmgw->hwmgw_func->set_asic_baco_state)
		wetuwn 0;

	hwmgw->hwmgw_func->set_asic_baco_state(hwmgw, (enum BACO_STATE)state);

	wetuwn 0;
}

static int pp_get_ppfeatuwe_status(void *handwe, chaw *buf)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en || !buf)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->get_ppfeatuwe_status == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	wetuwn hwmgw->hwmgw_func->get_ppfeatuwe_status(hwmgw, buf);
}

static int pp_set_ppfeatuwe_status(void *handwe, uint64_t ppfeatuwe_masks)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->set_ppfeatuwe_status == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	wetuwn hwmgw->hwmgw_func->set_ppfeatuwe_status(hwmgw, ppfeatuwe_masks);
}

static int pp_asic_weset_mode_2(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->asic_weset == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	wetuwn hwmgw->hwmgw_func->asic_weset(hwmgw, SMU_ASIC_WESET_MODE_2);
}

static int pp_smu_i2c_bus_access(void *handwe, boow acquiwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->smu_i2c_bus_access == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	wetuwn hwmgw->hwmgw_func->smu_i2c_bus_access(hwmgw, acquiwe);
}

static int pp_set_df_cstate(void *handwe, enum pp_df_cstate state)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw)
		wetuwn -EINVAW;

	if (!hwmgw->pm_en || !hwmgw->hwmgw_func->set_df_cstate)
		wetuwn 0;

	hwmgw->hwmgw_func->set_df_cstate(hwmgw, state);

	wetuwn 0;
}

static int pp_set_xgmi_pstate(void *handwe, uint32_t pstate)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw)
		wetuwn -EINVAW;

	if (!hwmgw->pm_en || !hwmgw->hwmgw_func->set_xgmi_pstate)
		wetuwn 0;

	hwmgw->hwmgw_func->set_xgmi_pstate(hwmgw, pstate);

	wetuwn 0;
}

static ssize_t pp_get_gpu_metwics(void *handwe, void **tabwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw)
		wetuwn -EINVAW;

	if (!hwmgw->pm_en || !hwmgw->hwmgw_func->get_gpu_metwics)
		wetuwn -EOPNOTSUPP;

	wetuwn hwmgw->hwmgw_func->get_gpu_metwics(hwmgw, tabwe);
}

static int pp_gfx_state_change_set(void *handwe, uint32_t state)
{
	stwuct pp_hwmgw *hwmgw = handwe;

	if (!hwmgw || !hwmgw->pm_en)
		wetuwn -EINVAW;

	if (hwmgw->hwmgw_func->gfx_state_change == NUWW) {
		pw_info_watewimited("%s was not impwemented.\n", __func__);
		wetuwn -EINVAW;
	}

	hwmgw->hwmgw_func->gfx_state_change(hwmgw, state);
	wetuwn 0;
}

static int pp_get_pwv_buffew_detaiws(void *handwe, void **addw, size_t *size)
{
	stwuct pp_hwmgw *hwmgw = handwe;
	stwuct amdgpu_device *adev = hwmgw->adev;
	int eww;

	if (!addw || !size)
		wetuwn -EINVAW;

	*addw = NUWW;
	*size = 0;
	if (adev->pm.smu_pwv_buffew) {
		eww = amdgpu_bo_kmap(adev->pm.smu_pwv_buffew, addw);
		if (eww)
			wetuwn eww;
		*size = adev->pm.smu_pwv_buffew_size;
	}

	wetuwn 0;
}

static void pp_pm_compute_cwocks(void *handwe)
{
	stwuct pp_hwmgw *hwmgw = handwe;
	stwuct amdgpu_device *adev = hwmgw->adev;

	if (!adev->dc_enabwed) {
		amdgpu_dpm_get_active_dispways(adev);
		adev->pm.pm_dispway_cfg.num_dispway = adev->pm.dpm.new_active_cwtc_count;
		adev->pm.pm_dispway_cfg.vwefwesh = amdgpu_dpm_get_vwefwesh(adev);
		adev->pm.pm_dispway_cfg.min_vbwank_time = amdgpu_dpm_get_vbwank_time(adev);
		/* we have issues with mcwk switching with
		 * wefwesh wates ovew 120 hz on the non-DC code.
		 */
		if (adev->pm.pm_dispway_cfg.vwefwesh > 120)
			adev->pm.pm_dispway_cfg.min_vbwank_time = 0;

		pp_dispway_configuwation_change(handwe,
						&adev->pm.pm_dispway_cfg);
	}

	pp_dpm_dispatch_tasks(handwe,
			      AMD_PP_TASK_DISPWAY_CONFIG_CHANGE,
			      NUWW);
}

static const stwuct amd_pm_funcs pp_dpm_funcs = {
	.woad_fiwmwawe = pp_dpm_woad_fw,
	.wait_fow_fw_woading_compwete = pp_dpm_fw_woading_compwete,
	.fowce_pewfowmance_wevew = pp_dpm_fowce_pewfowmance_wevew,
	.get_pewfowmance_wevew = pp_dpm_get_pewfowmance_wevew,
	.get_cuwwent_powew_state = pp_dpm_get_cuwwent_powew_state,
	.dispatch_tasks = pp_dpm_dispatch_tasks,
	.set_fan_contwow_mode = pp_dpm_set_fan_contwow_mode,
	.get_fan_contwow_mode = pp_dpm_get_fan_contwow_mode,
	.set_fan_speed_pwm = pp_dpm_set_fan_speed_pwm,
	.get_fan_speed_pwm = pp_dpm_get_fan_speed_pwm,
	.get_fan_speed_wpm = pp_dpm_get_fan_speed_wpm,
	.set_fan_speed_wpm = pp_dpm_set_fan_speed_wpm,
	.get_pp_num_states = pp_dpm_get_pp_num_states,
	.get_pp_tabwe = pp_dpm_get_pp_tabwe,
	.set_pp_tabwe = pp_dpm_set_pp_tabwe,
	.fowce_cwock_wevew = pp_dpm_fowce_cwock_wevew,
	.emit_cwock_wevews = pp_dpm_emit_cwock_wevews,
	.pwint_cwock_wevews = pp_dpm_pwint_cwock_wevews,
	.get_scwk_od = pp_dpm_get_scwk_od,
	.set_scwk_od = pp_dpm_set_scwk_od,
	.get_mcwk_od = pp_dpm_get_mcwk_od,
	.set_mcwk_od = pp_dpm_set_mcwk_od,
	.wead_sensow = pp_dpm_wead_sensow,
	.get_vce_cwock_state = pp_dpm_get_vce_cwock_state,
	.switch_powew_pwofiwe = pp_dpm_switch_powew_pwofiwe,
	.set_cwockgating_by_smu = pp_set_cwockgating_by_smu,
	.set_powewgating_by_smu = pp_set_powewgating_by_smu,
	.get_powew_pwofiwe_mode = pp_get_powew_pwofiwe_mode,
	.set_powew_pwofiwe_mode = pp_set_powew_pwofiwe_mode,
	.set_fine_gwain_cwk_vow = pp_set_fine_gwain_cwk_vow,
	.odn_edit_dpm_tabwe = pp_odn_edit_dpm_tabwe,
	.set_mp1_state = pp_dpm_set_mp1_state,
	.set_powew_wimit = pp_set_powew_wimit,
	.get_powew_wimit = pp_get_powew_wimit,
/* expowt to DC */
	.get_scwk = pp_dpm_get_scwk,
	.get_mcwk = pp_dpm_get_mcwk,
	.dispway_configuwation_change = pp_dispway_configuwation_change,
	.get_dispway_powew_wevew = pp_get_dispway_powew_wevew,
	.get_cuwwent_cwocks = pp_get_cuwwent_cwocks,
	.get_cwock_by_type = pp_get_cwock_by_type,
	.get_cwock_by_type_with_watency = pp_get_cwock_by_type_with_watency,
	.get_cwock_by_type_with_vowtage = pp_get_cwock_by_type_with_vowtage,
	.set_watewmawks_fow_cwocks_wanges = pp_set_watewmawks_fow_cwocks_wanges,
	.dispway_cwock_vowtage_wequest = pp_dispway_cwock_vowtage_wequest,
	.get_dispway_mode_vawidation_cwocks = pp_get_dispway_mode_vawidation_cwocks,
	.notify_smu_enabwe_pwe = pp_notify_smu_enabwe_pwe,
	.enabwe_mgpu_fan_boost = pp_enabwe_mgpu_fan_boost,
	.set_active_dispway_count = pp_set_active_dispway_count,
	.set_min_deep_sweep_dcefcwk = pp_set_min_deep_sweep_dcefcwk,
	.set_hawd_min_dcefcwk_by_fweq = pp_set_hawd_min_dcefcwk_by_fweq,
	.set_hawd_min_fcwk_by_fweq = pp_set_hawd_min_fcwk_by_fweq,
	.get_asic_baco_capabiwity = pp_get_asic_baco_capabiwity,
	.get_asic_baco_state = pp_get_asic_baco_state,
	.set_asic_baco_state = pp_set_asic_baco_state,
	.get_ppfeatuwe_status = pp_get_ppfeatuwe_status,
	.set_ppfeatuwe_status = pp_set_ppfeatuwe_status,
	.asic_weset_mode_2 = pp_asic_weset_mode_2,
	.smu_i2c_bus_access = pp_smu_i2c_bus_access,
	.set_df_cstate = pp_set_df_cstate,
	.set_xgmi_pstate = pp_set_xgmi_pstate,
	.get_gpu_metwics = pp_get_gpu_metwics,
	.gfx_state_change_set = pp_gfx_state_change_set,
	.get_smu_pwv_buf_detaiws = pp_get_pwv_buffew_detaiws,
	.pm_compute_cwocks = pp_pm_compute_cwocks,
};
