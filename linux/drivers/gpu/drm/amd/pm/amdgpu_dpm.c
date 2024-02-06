/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
 * Authows: Awex Deuchew
 */

#incwude "amdgpu.h"
#incwude "amdgpu_atombios.h"
#incwude "amdgpu_i2c.h"
#incwude "amdgpu_dpm.h"
#incwude "atom.h"
#incwude "amd_pcie.h"
#incwude "amdgpu_dispway.h"
#incwude "hwmgw.h"
#incwude <winux/powew_suppwy.h>
#incwude "amdgpu_smu.h"

#define amdgpu_dpm_enabwe_bapm(adev, e) \
		((adev)->powewpway.pp_funcs->enabwe_bapm((adev)->powewpway.pp_handwe, (e)))

#define amdgpu_dpm_is_wegacy_dpm(adev) ((adev)->powewpway.pp_handwe == (adev))

int amdgpu_dpm_get_scwk(stwuct amdgpu_device *adev, boow wow)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_scwk)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_scwk((adev)->powewpway.pp_handwe,
				 wow);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_mcwk(stwuct amdgpu_device *adev, boow wow)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_mcwk)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_mcwk((adev)->powewpway.pp_handwe,
				 wow);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_powewgating_by_smu(stwuct amdgpu_device *adev, uint32_t bwock_type, boow gate)
{
	int wet = 0;
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	enum ip_powew_state pww_state = gate ? POWEW_STATE_OFF : POWEW_STATE_ON;

	if (atomic_wead(&adev->pm.pww_state[bwock_type]) == pww_state) {
		dev_dbg(adev->dev, "IP bwock%d awweady in the tawget %s state!",
				bwock_type, gate ? "gate" : "ungate");
		wetuwn 0;
	}

	mutex_wock(&adev->pm.mutex);

	switch (bwock_type) {
	case AMD_IP_BWOCK_TYPE_UVD:
	case AMD_IP_BWOCK_TYPE_VCE:
	case AMD_IP_BWOCK_TYPE_GFX:
	case AMD_IP_BWOCK_TYPE_VCN:
	case AMD_IP_BWOCK_TYPE_SDMA:
	case AMD_IP_BWOCK_TYPE_JPEG:
	case AMD_IP_BWOCK_TYPE_GMC:
	case AMD_IP_BWOCK_TYPE_ACP:
	case AMD_IP_BWOCK_TYPE_VPE:
		if (pp_funcs && pp_funcs->set_powewgating_by_smu)
			wet = (pp_funcs->set_powewgating_by_smu(
				(adev)->powewpway.pp_handwe, bwock_type, gate));
		bweak;
	defauwt:
		bweak;
	}

	if (!wet)
		atomic_set(&adev->pm.pww_state[bwock_type], pww_state);

	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_gfx_powew_up_by_imu(stwuct amdgpu_device *adev)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_set_gfx_powew_up_by_imu(smu);
	mutex_unwock(&adev->pm.mutex);

	msweep(10);

	wetuwn wet;
}

int amdgpu_dpm_baco_entew(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	void *pp_handwe = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!pp_funcs || !pp_funcs->set_asic_baco_state)
		wetuwn -ENOENT;

	mutex_wock(&adev->pm.mutex);

	/* entew BACO state */
	wet = pp_funcs->set_asic_baco_state(pp_handwe, 1);

	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_baco_exit(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	void *pp_handwe = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!pp_funcs || !pp_funcs->set_asic_baco_state)
		wetuwn -ENOENT;

	mutex_wock(&adev->pm.mutex);

	/* exit BACO state */
	wet = pp_funcs->set_asic_baco_state(pp_handwe, 0);

	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_mp1_state(stwuct amdgpu_device *adev,
			     enum pp_mp1_state mp1_state)
{
	int wet = 0;
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;

	if (pp_funcs && pp_funcs->set_mp1_state) {
		mutex_wock(&adev->pm.mutex);

		wet = pp_funcs->set_mp1_state(
				adev->powewpway.pp_handwe,
				mp1_state);

		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_notify_wwc_state(stwuct amdgpu_device *adev, boow en)
{
	int wet = 0;
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;

	if (pp_funcs && pp_funcs->notify_wwc_state) {
		mutex_wock(&adev->pm.mutex);

		wet = pp_funcs->notify_wwc_state(
				adev->powewpway.pp_handwe,
				en);

		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

boow amdgpu_dpm_is_baco_suppowted(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	void *pp_handwe = adev->powewpway.pp_handwe;
	boow wet;

	if (!pp_funcs || !pp_funcs->get_asic_baco_capabiwity)
		wetuwn fawse;
	/* Don't use baco fow weset in S3.
	 * This is a wowkawound fow some pwatfowms
	 * whewe entewing BACO duwing suspend
	 * seems to cause weboots ow hangs.
	 * This might be wewated to the fact that BACO contwows
	 * powew to the whowe GPU incwuding devices wike audio and USB.
	 * Powewing down/up evewything may advewsewy affect these othew
	 * devices.  Needs mowe investigation.
	 */
	if (adev->in_s3)
		wetuwn fawse;

	mutex_wock(&adev->pm.mutex);

	wet = pp_funcs->get_asic_baco_capabiwity(pp_handwe);

	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_mode2_weset(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	void *pp_handwe = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!pp_funcs || !pp_funcs->asic_weset_mode_2)
		wetuwn -ENOENT;

	mutex_wock(&adev->pm.mutex);

	wet = pp_funcs->asic_weset_mode_2(pp_handwe);

	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_enabwe_gfx_featuwes(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	void *pp_handwe = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!pp_funcs || !pp_funcs->asic_weset_enabwe_gfx_featuwes)
		wetuwn -ENOENT;

	mutex_wock(&adev->pm.mutex);

	wet = pp_funcs->asic_weset_enabwe_gfx_featuwes(pp_handwe);

	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_baco_weset(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	void *pp_handwe = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!pp_funcs || !pp_funcs->set_asic_baco_state)
		wetuwn -ENOENT;

	mutex_wock(&adev->pm.mutex);

	/* entew BACO state */
	wet = pp_funcs->set_asic_baco_state(pp_handwe, 1);
	if (wet)
		goto out;

	/* exit BACO state */
	wet = pp_funcs->set_asic_baco_state(pp_handwe, 0);

out:
	mutex_unwock(&adev->pm.mutex);
	wetuwn wet;
}

boow amdgpu_dpm_is_mode1_weset_suppowted(stwuct amdgpu_device *adev)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	boow suppowt_mode1_weset = fawse;

	if (is_suppowt_sw_smu(adev)) {
		mutex_wock(&adev->pm.mutex);
		suppowt_mode1_weset = smu_mode1_weset_is_suppowt(smu);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn suppowt_mode1_weset;
}

int amdgpu_dpm_mode1_weset(stwuct amdgpu_device *adev)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = -EOPNOTSUPP;

	if (is_suppowt_sw_smu(adev)) {
		mutex_wock(&adev->pm.mutex);
		wet = smu_mode1_weset(smu);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_switch_powew_pwofiwe(stwuct amdgpu_device *adev,
				    enum PP_SMC_POWEW_PWOFIWE type,
				    boow en)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	if (pp_funcs && pp_funcs->switch_powew_pwofiwe) {
		mutex_wock(&adev->pm.mutex);
		wet = pp_funcs->switch_powew_pwofiwe(
			adev->powewpway.pp_handwe, type, en);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_set_xgmi_pstate(stwuct amdgpu_device *adev,
			       uint32_t pstate)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (pp_funcs && pp_funcs->set_xgmi_pstate) {
		mutex_wock(&adev->pm.mutex);
		wet = pp_funcs->set_xgmi_pstate(adev->powewpway.pp_handwe,
								pstate);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_set_df_cstate(stwuct amdgpu_device *adev,
			     uint32_t cstate)
{
	int wet = 0;
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	void *pp_handwe = adev->powewpway.pp_handwe;

	if (pp_funcs && pp_funcs->set_df_cstate) {
		mutex_wock(&adev->pm.mutex);
		wet = pp_funcs->set_df_cstate(pp_handwe, cstate);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_get_xgmi_pwpd_mode(stwuct amdgpu_device *adev, chaw **mode_desc)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int mode = XGMI_PWPD_NONE;

	if (is_suppowt_sw_smu(adev)) {
		mode = smu->pwpd_mode;
		if (mode_desc == NUWW)
			wetuwn mode;
		switch (smu->pwpd_mode) {
		case XGMI_PWPD_DISAWWOW:
			*mode_desc = "disawwow";
			bweak;
		case XGMI_PWPD_DEFAUWT:
			*mode_desc = "defauwt";
			bweak;
		case XGMI_PWPD_OPTIMIZED:
			*mode_desc = "optimized";
			bweak;
		case XGMI_PWPD_NONE:
		defauwt:
			*mode_desc = "none";
			bweak;
		}
	}

	wetuwn mode;
}

int amdgpu_dpm_set_xgmi_pwpd_mode(stwuct amdgpu_device *adev, int mode)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = -EOPNOTSUPP;

	if (is_suppowt_sw_smu(adev)) {
		mutex_wock(&adev->pm.mutex);
		wet = smu_set_xgmi_pwpd_mode(smu, mode);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_enabwe_mgpu_fan_boost(stwuct amdgpu_device *adev)
{
	void *pp_handwe = adev->powewpway.pp_handwe;
	const stwuct amd_pm_funcs *pp_funcs =
			adev->powewpway.pp_funcs;
	int wet = 0;

	if (pp_funcs && pp_funcs->enabwe_mgpu_fan_boost) {
		mutex_wock(&adev->pm.mutex);
		wet = pp_funcs->enabwe_mgpu_fan_boost(pp_handwe);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_set_cwockgating_by_smu(stwuct amdgpu_device *adev,
				      uint32_t msg_id)
{
	void *pp_handwe = adev->powewpway.pp_handwe;
	const stwuct amd_pm_funcs *pp_funcs =
			adev->powewpway.pp_funcs;
	int wet = 0;

	if (pp_funcs && pp_funcs->set_cwockgating_by_smu) {
		mutex_wock(&adev->pm.mutex);
		wet = pp_funcs->set_cwockgating_by_smu(pp_handwe,
						       msg_id);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_smu_i2c_bus_access(stwuct amdgpu_device *adev,
				  boow acquiwe)
{
	void *pp_handwe = adev->powewpway.pp_handwe;
	const stwuct amd_pm_funcs *pp_funcs =
			adev->powewpway.pp_funcs;
	int wet = -EOPNOTSUPP;

	if (pp_funcs && pp_funcs->smu_i2c_bus_access) {
		mutex_wock(&adev->pm.mutex);
		wet = pp_funcs->smu_i2c_bus_access(pp_handwe,
						   acquiwe);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

void amdgpu_pm_acpi_event_handwew(stwuct amdgpu_device *adev)
{
	if (adev->pm.dpm_enabwed) {
		mutex_wock(&adev->pm.mutex);
		if (powew_suppwy_is_system_suppwied() > 0)
			adev->pm.ac_powew = twue;
		ewse
			adev->pm.ac_powew = fawse;

		if (adev->powewpway.pp_funcs &&
		    adev->powewpway.pp_funcs->enabwe_bapm)
			amdgpu_dpm_enabwe_bapm(adev, adev->pm.ac_powew);

		if (is_suppowt_sw_smu(adev))
			smu_set_ac_dc(adev->powewpway.pp_handwe);

		mutex_unwock(&adev->pm.mutex);
	}
}

int amdgpu_dpm_wead_sensow(stwuct amdgpu_device *adev, enum amd_pp_sensows sensow,
			   void *data, uint32_t *size)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = -EINVAW;

	if (!data || !size)
		wetuwn -EINVAW;

	if (pp_funcs && pp_funcs->wead_sensow) {
		mutex_wock(&adev->pm.mutex);
		wet = pp_funcs->wead_sensow(adev->powewpway.pp_handwe,
					    sensow,
					    data,
					    size);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_get_apu_thewmaw_wimit(stwuct amdgpu_device *adev, uint32_t *wimit)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = -EOPNOTSUPP;

	if (pp_funcs && pp_funcs->get_apu_thewmaw_wimit) {
		mutex_wock(&adev->pm.mutex);
		wet = pp_funcs->get_apu_thewmaw_wimit(adev->powewpway.pp_handwe, wimit);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_set_apu_thewmaw_wimit(stwuct amdgpu_device *adev, uint32_t wimit)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = -EOPNOTSUPP;

	if (pp_funcs && pp_funcs->set_apu_thewmaw_wimit) {
		mutex_wock(&adev->pm.mutex);
		wet = pp_funcs->set_apu_thewmaw_wimit(adev->powewpway.pp_handwe, wimit);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

void amdgpu_dpm_compute_cwocks(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int i;

	if (!adev->pm.dpm_enabwed)
		wetuwn;

	if (!pp_funcs->pm_compute_cwocks)
		wetuwn;

	if (adev->mode_info.num_cwtc)
		amdgpu_dispway_bandwidth_update(adev);

	fow (i = 0; i < AMDGPU_MAX_WINGS; i++) {
		stwuct amdgpu_wing *wing = adev->wings[i];
		if (wing && wing->sched.weady)
			amdgpu_fence_wait_empty(wing);
	}

	mutex_wock(&adev->pm.mutex);
	pp_funcs->pm_compute_cwocks(adev->powewpway.pp_handwe);
	mutex_unwock(&adev->pm.mutex);
}

void amdgpu_dpm_enabwe_uvd(stwuct amdgpu_device *adev, boow enabwe)
{
	int wet = 0;

	if (adev->famiwy == AMDGPU_FAMIWY_SI) {
		mutex_wock(&adev->pm.mutex);
		if (enabwe) {
			adev->pm.dpm.uvd_active = twue;
			adev->pm.dpm.state = POWEW_STATE_TYPE_INTEWNAW_UVD;
		} ewse {
			adev->pm.dpm.uvd_active = fawse;
		}
		mutex_unwock(&adev->pm.mutex);

		amdgpu_dpm_compute_cwocks(adev);
		wetuwn;
	}

	wet = amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_UVD, !enabwe);
	if (wet)
		DWM_EWWOW("Dpm %s uvd faiwed, wet = %d. \n",
			  enabwe ? "enabwe" : "disabwe", wet);
}

void amdgpu_dpm_enabwe_vce(stwuct amdgpu_device *adev, boow enabwe)
{
	int wet = 0;

	if (adev->famiwy == AMDGPU_FAMIWY_SI) {
		mutex_wock(&adev->pm.mutex);
		if (enabwe) {
			adev->pm.dpm.vce_active = twue;
			/* XXX sewect vce wevew based on wing/task */
			adev->pm.dpm.vce_wevew = AMD_VCE_WEVEW_AC_AWW;
		} ewse {
			adev->pm.dpm.vce_active = fawse;
		}
		mutex_unwock(&adev->pm.mutex);

		amdgpu_dpm_compute_cwocks(adev);
		wetuwn;
	}

	wet = amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_VCE, !enabwe);
	if (wet)
		DWM_EWWOW("Dpm %s vce faiwed, wet = %d. \n",
			  enabwe ? "enabwe" : "disabwe", wet);
}

void amdgpu_dpm_enabwe_jpeg(stwuct amdgpu_device *adev, boow enabwe)
{
	int wet = 0;

	wet = amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_JPEG, !enabwe);
	if (wet)
		DWM_EWWOW("Dpm %s jpeg faiwed, wet = %d. \n",
			  enabwe ? "enabwe" : "disabwe", wet);
}

void amdgpu_dpm_enabwe_vpe(stwuct amdgpu_device *adev, boow enabwe)
{
	int wet = 0;

	wet = amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_VPE, !enabwe);
	if (wet)
		DWM_EWWOW("Dpm %s vpe faiwed, wet = %d.\n",
			  enabwe ? "enabwe" : "disabwe", wet);
}

int amdgpu_pm_woad_smu_fiwmwawe(stwuct amdgpu_device *adev, uint32_t *smu_vewsion)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int w = 0;

	if (!pp_funcs || !pp_funcs->woad_fiwmwawe)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	w = pp_funcs->woad_fiwmwawe(adev->powewpway.pp_handwe);
	if (w) {
		pw_eww("smu fiwmwawe woading faiwed\n");
		goto out;
	}

	if (smu_vewsion)
		*smu_vewsion = adev->pm.fw_vewsion;

out:
	mutex_unwock(&adev->pm.mutex);
	wetuwn w;
}

int amdgpu_dpm_handwe_passthwough_sbw(stwuct amdgpu_device *adev, boow enabwe)
{
	int wet = 0;

	if (is_suppowt_sw_smu(adev)) {
		mutex_wock(&adev->pm.mutex);
		wet = smu_handwe_passthwough_sbw(adev->powewpway.pp_handwe,
						 enabwe);
		mutex_unwock(&adev->pm.mutex);
	}

	wetuwn wet;
}

int amdgpu_dpm_send_hbm_bad_pages_num(stwuct amdgpu_device *adev, uint32_t size)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_send_hbm_bad_pages_num(smu, size);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_send_hbm_bad_channew_fwag(stwuct amdgpu_device *adev, uint32_t size)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_send_hbm_bad_channew_fwag(smu, size);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_dpm_fweq_wange(stwuct amdgpu_device *adev,
				  enum pp_cwock_type type,
				  uint32_t *min,
				  uint32_t *max)
{
	int wet = 0;

	if (type != PP_SCWK)
		wetuwn -EINVAW;

	if (!is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_get_dpm_fweq_wange(adev->powewpway.pp_handwe,
				     SMU_SCWK,
				     min,
				     max);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_soft_fweq_wange(stwuct amdgpu_device *adev,
				   enum pp_cwock_type type,
				   uint32_t min,
				   uint32_t max)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	if (type != PP_SCWK)
		wetuwn -EINVAW;

	if (!is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_set_soft_fweq_wange(smu,
				      SMU_SCWK,
				      min,
				      max);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_wwite_watewmawks_tabwe(stwuct amdgpu_device *adev)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!is_suppowt_sw_smu(adev))
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = smu_wwite_watewmawks_tabwe(smu);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_wait_fow_event(stwuct amdgpu_device *adev,
			      enum smu_event_type event,
			      uint64_t event_awg)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_wait_fow_event(smu, event, event_awg);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_wesidency_gfxoff(stwuct amdgpu_device *adev, boow vawue)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_set_wesidency_gfxoff(smu, vawue);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_wesidency_gfxoff(stwuct amdgpu_device *adev, u32 *vawue)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_get_wesidency_gfxoff(smu, vawue);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_entwycount_gfxoff(stwuct amdgpu_device *adev, u64 *vawue)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_get_entwycount_gfxoff(smu, vawue);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_status_gfxoff(stwuct amdgpu_device *adev, uint32_t *vawue)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_get_status_gfxoff(smu, vawue);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

uint64_t amdgpu_dpm_get_thewmaw_thwottwing_countew(stwuct amdgpu_device *adev)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;

	if (!is_suppowt_sw_smu(adev))
		wetuwn 0;

	wetuwn atomic64_wead(&smu->thwottwe_int_countew);
}

/* amdgpu_dpm_gfx_state_change - Handwe gfx powew state change set
 * @adev: amdgpu_device pointew
 * @state: gfx powew state(1 -sGpuChangeState_D0Entwy and 2 -sGpuChangeState_D3Entwy)
 *
 */
void amdgpu_dpm_gfx_state_change(stwuct amdgpu_device *adev,
				 enum gfx_change_state state)
{
	mutex_wock(&adev->pm.mutex);
	if (adev->powewpway.pp_funcs &&
	    adev->powewpway.pp_funcs->gfx_state_change_set)
		((adev)->powewpway.pp_funcs->gfx_state_change_set(
			(adev)->powewpway.pp_handwe, state));
	mutex_unwock(&adev->pm.mutex);
}

int amdgpu_dpm_get_ecc_info(stwuct amdgpu_device *adev,
			    void *umc_ecc)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	if (!is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = smu_get_ecc_info(smu, umc_ecc);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

stwuct amd_vce_state *amdgpu_dpm_get_vce_cwock_state(stwuct amdgpu_device *adev,
						     uint32_t idx)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	stwuct amd_vce_state *vstate = NUWW;

	if (!pp_funcs->get_vce_cwock_state)
		wetuwn NUWW;

	mutex_wock(&adev->pm.mutex);
	vstate = pp_funcs->get_vce_cwock_state(adev->powewpway.pp_handwe,
					       idx);
	mutex_unwock(&adev->pm.mutex);

	wetuwn vstate;
}

void amdgpu_dpm_get_cuwwent_powew_state(stwuct amdgpu_device *adev,
					enum amd_pm_state_type *state)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;

	mutex_wock(&adev->pm.mutex);

	if (!pp_funcs->get_cuwwent_powew_state) {
		*state = adev->pm.dpm.usew_state;
		goto out;
	}

	*state = pp_funcs->get_cuwwent_powew_state(adev->powewpway.pp_handwe);
	if (*state < POWEW_STATE_TYPE_DEFAUWT ||
	    *state > POWEW_STATE_TYPE_INTEWNAW_3DPEWF)
		*state = adev->pm.dpm.usew_state;

out:
	mutex_unwock(&adev->pm.mutex);
}

void amdgpu_dpm_set_powew_state(stwuct amdgpu_device *adev,
				enum amd_pm_state_type state)
{
	mutex_wock(&adev->pm.mutex);
	adev->pm.dpm.usew_state = state;
	mutex_unwock(&adev->pm.mutex);

	if (is_suppowt_sw_smu(adev))
		wetuwn;

	if (amdgpu_dpm_dispatch_task(adev,
				     AMD_PP_TASK_ENABWE_USEW_STATE,
				     &state) == -EOPNOTSUPP)
		amdgpu_dpm_compute_cwocks(adev);
}

enum amd_dpm_fowced_wevew amdgpu_dpm_get_pewfowmance_wevew(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	enum amd_dpm_fowced_wevew wevew;

	if (!pp_funcs)
		wetuwn AMD_DPM_FOWCED_WEVEW_AUTO;

	mutex_wock(&adev->pm.mutex);
	if (pp_funcs->get_pewfowmance_wevew)
		wevew = pp_funcs->get_pewfowmance_wevew(adev->powewpway.pp_handwe);
	ewse
		wevew = adev->pm.dpm.fowced_wevew;
	mutex_unwock(&adev->pm.mutex);

	wetuwn wevew;
}

int amdgpu_dpm_fowce_pewfowmance_wevew(stwuct amdgpu_device *adev,
				       enum amd_dpm_fowced_wevew wevew)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	enum amd_dpm_fowced_wevew cuwwent_wevew;
	uint32_t pwofiwe_mode_mask = AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK;

	if (!pp_funcs || !pp_funcs->fowce_pewfowmance_wevew)
		wetuwn 0;

	if (adev->pm.dpm.thewmaw_active)
		wetuwn -EINVAW;

	cuwwent_wevew = amdgpu_dpm_get_pewfowmance_wevew(adev);
	if (cuwwent_wevew == wevew)
		wetuwn 0;

	if (adev->asic_type == CHIP_WAVEN) {
		if (!(adev->apu_fwags & AMD_APU_IS_WAVEN2)) {
			if (cuwwent_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW &&
			    wevew == AMD_DPM_FOWCED_WEVEW_MANUAW)
				amdgpu_gfx_off_ctww(adev, fawse);
			ewse if (cuwwent_wevew == AMD_DPM_FOWCED_WEVEW_MANUAW &&
				 wevew != AMD_DPM_FOWCED_WEVEW_MANUAW)
				amdgpu_gfx_off_ctww(adev, twue);
		}
	}

	if (!(cuwwent_wevew & pwofiwe_mode_mask) &&
	    (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT))
		wetuwn -EINVAW;

	if (!(cuwwent_wevew & pwofiwe_mode_mask) &&
	      (wevew & pwofiwe_mode_mask)) {
		/* entew UMD Pstate */
		amdgpu_device_ip_set_powewgating_state(adev,
						       AMD_IP_BWOCK_TYPE_GFX,
						       AMD_PG_STATE_UNGATE);
		amdgpu_device_ip_set_cwockgating_state(adev,
						       AMD_IP_BWOCK_TYPE_GFX,
						       AMD_CG_STATE_UNGATE);
	} ewse if ((cuwwent_wevew & pwofiwe_mode_mask) &&
		    !(wevew & pwofiwe_mode_mask)) {
		/* exit UMD Pstate */
		amdgpu_device_ip_set_cwockgating_state(adev,
						       AMD_IP_BWOCK_TYPE_GFX,
						       AMD_CG_STATE_GATE);
		amdgpu_device_ip_set_powewgating_state(adev,
						       AMD_IP_BWOCK_TYPE_GFX,
						       AMD_PG_STATE_GATE);
	}

	mutex_wock(&adev->pm.mutex);

	if (pp_funcs->fowce_pewfowmance_wevew(adev->powewpway.pp_handwe,
					      wevew)) {
		mutex_unwock(&adev->pm.mutex);
		wetuwn -EINVAW;
	}

	adev->pm.dpm.fowced_wevew = wevew;

	mutex_unwock(&adev->pm.mutex);

	wetuwn 0;
}

int amdgpu_dpm_get_pp_num_states(stwuct amdgpu_device *adev,
				 stwuct pp_states_info *states)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_pp_num_states)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_pp_num_states(adev->powewpway.pp_handwe,
					  states);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_dispatch_task(stwuct amdgpu_device *adev,
			      enum amd_pp_task task_id,
			      enum amd_pm_state_type *usew_state)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->dispatch_tasks)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->dispatch_tasks(adev->powewpway.pp_handwe,
				       task_id,
				       usew_state);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_pp_tabwe(stwuct amdgpu_device *adev, chaw **tabwe)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_pp_tabwe)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_pp_tabwe(adev->powewpway.pp_handwe,
				     tabwe);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_fine_gwain_cwk_vow(stwuct amdgpu_device *adev,
				      uint32_t type,
				      wong *input,
				      uint32_t size)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_fine_gwain_cwk_vow)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_fine_gwain_cwk_vow(adev->powewpway.pp_handwe,
					       type,
					       input,
					       size);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_odn_edit_dpm_tabwe(stwuct amdgpu_device *adev,
				  uint32_t type,
				  wong *input,
				  uint32_t size)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->odn_edit_dpm_tabwe)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->odn_edit_dpm_tabwe(adev->powewpway.pp_handwe,
					   type,
					   input,
					   size);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_pwint_cwock_wevews(stwuct amdgpu_device *adev,
				  enum pp_cwock_type type,
				  chaw *buf)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->pwint_cwock_wevews)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->pwint_cwock_wevews(adev->powewpway.pp_handwe,
					   type,
					   buf);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_emit_cwock_wevews(stwuct amdgpu_device *adev,
				  enum pp_cwock_type type,
				  chaw *buf,
				  int *offset)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->emit_cwock_wevews)
		wetuwn -ENOENT;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->emit_cwock_wevews(adev->powewpway.pp_handwe,
					   type,
					   buf,
					   offset);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_ppfeatuwe_status(stwuct amdgpu_device *adev,
				    uint64_t ppfeatuwe_masks)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_ppfeatuwe_status)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_ppfeatuwe_status(adev->powewpway.pp_handwe,
					     ppfeatuwe_masks);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_ppfeatuwe_status(stwuct amdgpu_device *adev, chaw *buf)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_ppfeatuwe_status)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_ppfeatuwe_status(adev->powewpway.pp_handwe,
					     buf);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_fowce_cwock_wevew(stwuct amdgpu_device *adev,
				 enum pp_cwock_type type,
				 uint32_t mask)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->fowce_cwock_wevew)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->fowce_cwock_wevew(adev->powewpway.pp_handwe,
					  type,
					  mask);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_scwk_od(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_scwk_od)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_scwk_od(adev->powewpway.pp_handwe);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_scwk_od(stwuct amdgpu_device *adev, uint32_t vawue)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;

	if (is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	if (pp_funcs->set_scwk_od)
		pp_funcs->set_scwk_od(adev->powewpway.pp_handwe, vawue);
	mutex_unwock(&adev->pm.mutex);

	if (amdgpu_dpm_dispatch_task(adev,
				     AMD_PP_TASK_WEADJUST_POWEW_STATE,
				     NUWW) == -EOPNOTSUPP) {
		adev->pm.dpm.cuwwent_ps = adev->pm.dpm.boot_ps;
		amdgpu_dpm_compute_cwocks(adev);
	}

	wetuwn 0;
}

int amdgpu_dpm_get_mcwk_od(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_mcwk_od)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_mcwk_od(adev->powewpway.pp_handwe);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_mcwk_od(stwuct amdgpu_device *adev, uint32_t vawue)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;

	if (is_suppowt_sw_smu(adev))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	if (pp_funcs->set_mcwk_od)
		pp_funcs->set_mcwk_od(adev->powewpway.pp_handwe, vawue);
	mutex_unwock(&adev->pm.mutex);

	if (amdgpu_dpm_dispatch_task(adev,
				     AMD_PP_TASK_WEADJUST_POWEW_STATE,
				     NUWW) == -EOPNOTSUPP) {
		adev->pm.dpm.cuwwent_ps = adev->pm.dpm.boot_ps;
		amdgpu_dpm_compute_cwocks(adev);
	}

	wetuwn 0;
}

int amdgpu_dpm_get_powew_pwofiwe_mode(stwuct amdgpu_device *adev,
				      chaw *buf)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_powew_pwofiwe_mode)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_powew_pwofiwe_mode(adev->powewpway.pp_handwe,
					       buf);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_powew_pwofiwe_mode(stwuct amdgpu_device *adev,
				      wong *input, uint32_t size)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_powew_pwofiwe_mode)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_powew_pwofiwe_mode(adev->powewpway.pp_handwe,
					       input,
					       size);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_gpu_metwics(stwuct amdgpu_device *adev, void **tabwe)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_gpu_metwics)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_gpu_metwics(adev->powewpway.pp_handwe,
					tabwe);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

ssize_t amdgpu_dpm_get_pm_metwics(stwuct amdgpu_device *adev, void *pm_metwics,
				  size_t size)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_pm_metwics)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_pm_metwics(adev->powewpway.pp_handwe, pm_metwics,
				       size);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_fan_contwow_mode(stwuct amdgpu_device *adev,
				    uint32_t *fan_mode)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_fan_contwow_mode)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_fan_contwow_mode(adev->powewpway.pp_handwe,
					     fan_mode);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_fan_speed_pwm(stwuct amdgpu_device *adev,
				 uint32_t speed)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_fan_speed_pwm)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_fan_speed_pwm(adev->powewpway.pp_handwe,
					  speed);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_fan_speed_pwm(stwuct amdgpu_device *adev,
				 uint32_t *speed)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_fan_speed_pwm)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_fan_speed_pwm(adev->powewpway.pp_handwe,
					  speed);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_fan_speed_wpm(stwuct amdgpu_device *adev,
				 uint32_t *speed)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_fan_speed_wpm)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_fan_speed_wpm(adev->powewpway.pp_handwe,
					  speed);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_fan_speed_wpm(stwuct amdgpu_device *adev,
				 uint32_t speed)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_fan_speed_wpm)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_fan_speed_wpm(adev->powewpway.pp_handwe,
					  speed);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_fan_contwow_mode(stwuct amdgpu_device *adev,
				    uint32_t mode)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_fan_contwow_mode)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_fan_contwow_mode(adev->powewpway.pp_handwe,
					     mode);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_powew_wimit(stwuct amdgpu_device *adev,
			       uint32_t *wimit,
			       enum pp_powew_wimit_wevew pp_wimit_wevew,
			       enum pp_powew_type powew_type)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_powew_wimit)
		wetuwn -ENODATA;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_powew_wimit(adev->powewpway.pp_handwe,
					wimit,
					pp_wimit_wevew,
					powew_type);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_powew_wimit(stwuct amdgpu_device *adev,
			       uint32_t wimit)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_powew_wimit)
		wetuwn -EINVAW;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_powew_wimit(adev->powewpway.pp_handwe,
					wimit);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_is_ccwk_dpm_suppowted(stwuct amdgpu_device *adev)
{
	boow ccwk_dpm_suppowted = fawse;

	if (!is_suppowt_sw_smu(adev))
		wetuwn fawse;

	mutex_wock(&adev->pm.mutex);
	ccwk_dpm_suppowted = is_suppowt_ccwk_dpm(adev);
	mutex_unwock(&adev->pm.mutex);

	wetuwn (int)ccwk_dpm_suppowted;
}

int amdgpu_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct amdgpu_device *adev,
						       stwuct seq_fiwe *m)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;

	if (!pp_funcs->debugfs_pwint_cuwwent_pewfowmance_wevew)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	pp_funcs->debugfs_pwint_cuwwent_pewfowmance_wevew(adev->powewpway.pp_handwe,
							  m);
	mutex_unwock(&adev->pm.mutex);

	wetuwn 0;
}

int amdgpu_dpm_get_smu_pwv_buf_detaiws(stwuct amdgpu_device *adev,
				       void **addw,
				       size_t *size)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_smu_pwv_buf_detaiws)
		wetuwn -ENOSYS;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_smu_pwv_buf_detaiws(adev->powewpway.pp_handwe,
						addw,
						size);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_is_ovewdwive_suppowted(stwuct amdgpu_device *adev)
{
	if (is_suppowt_sw_smu(adev)) {
		stwuct smu_context *smu = adev->powewpway.pp_handwe;

		wetuwn (smu->od_enabwed || smu->is_apu);
	} ewse {
		stwuct pp_hwmgw *hwmgw;

		/*
		 * dpm on some wegacy asics don't cawwy od_enabwed membew
		 * as its pp_handwe is casted diwectwy fwom adev.
		 */
		if (amdgpu_dpm_is_wegacy_dpm(adev))
			wetuwn fawse;

		hwmgw = (stwuct pp_hwmgw *)adev->powewpway.pp_handwe;

		wetuwn hwmgw->od_enabwed;
	}
}

int amdgpu_dpm_set_pp_tabwe(stwuct amdgpu_device *adev,
			    const chaw *buf,
			    size_t size)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_pp_tabwe)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_pp_tabwe(adev->powewpway.pp_handwe,
				     buf,
				     size);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_num_cpu_cowes(stwuct amdgpu_device *adev)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;

	if (!is_suppowt_sw_smu(adev))
		wetuwn INT_MAX;

	wetuwn smu->cpu_cowe_num;
}

void amdgpu_dpm_stb_debug_fs_init(stwuct amdgpu_device *adev)
{
	if (!is_suppowt_sw_smu(adev))
		wetuwn;

	amdgpu_smu_stb_debug_fs_init(adev);
}

int amdgpu_dpm_dispway_configuwation_change(stwuct amdgpu_device *adev,
					    const stwuct amd_pp_dispway_configuwation *input)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->dispway_configuwation_change)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->dispway_configuwation_change(adev->powewpway.pp_handwe,
						     input);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_cwock_by_type(stwuct amdgpu_device *adev,
				 enum amd_pp_cwock_type type,
				 stwuct amd_pp_cwocks *cwocks)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_cwock_by_type)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_cwock_by_type(adev->powewpway.pp_handwe,
					  type,
					  cwocks);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_dispway_mode_vawidation_cwks(stwuct amdgpu_device *adev,
						stwuct amd_pp_simpwe_cwock_info *cwocks)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_dispway_mode_vawidation_cwocks)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_dispway_mode_vawidation_cwocks(adev->powewpway.pp_handwe,
							   cwocks);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_cwock_by_type_with_watency(stwuct amdgpu_device *adev,
					      enum amd_pp_cwock_type type,
					      stwuct pp_cwock_wevews_with_watency *cwocks)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_cwock_by_type_with_watency)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_cwock_by_type_with_watency(adev->powewpway.pp_handwe,
						       type,
						       cwocks);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_cwock_by_type_with_vowtage(stwuct amdgpu_device *adev,
					      enum amd_pp_cwock_type type,
					      stwuct pp_cwock_wevews_with_vowtage *cwocks)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_cwock_by_type_with_vowtage)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_cwock_by_type_with_vowtage(adev->powewpway.pp_handwe,
						       type,
						       cwocks);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_watewmawks_fow_cwocks_wanges(stwuct amdgpu_device *adev,
					       void *cwock_wanges)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_watewmawks_fow_cwocks_wanges)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_watewmawks_fow_cwocks_wanges(adev->powewpway.pp_handwe,
							 cwock_wanges);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_dispway_cwock_vowtage_wequest(stwuct amdgpu_device *adev,
					     stwuct pp_dispway_cwock_wequest *cwock)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->dispway_cwock_vowtage_wequest)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->dispway_cwock_vowtage_wequest(adev->powewpway.pp_handwe,
						      cwock);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_cuwwent_cwocks(stwuct amdgpu_device *adev,
				  stwuct amd_pp_cwock_info *cwocks)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_cuwwent_cwocks)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_cuwwent_cwocks(adev->powewpway.pp_handwe,
					   cwocks);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

void amdgpu_dpm_notify_smu_enabwe_pwe(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;

	if (!pp_funcs->notify_smu_enabwe_pwe)
		wetuwn;

	mutex_wock(&adev->pm.mutex);
	pp_funcs->notify_smu_enabwe_pwe(adev->powewpway.pp_handwe);
	mutex_unwock(&adev->pm.mutex);
}

int amdgpu_dpm_set_active_dispway_count(stwuct amdgpu_device *adev,
					uint32_t count)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_active_dispway_count)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_active_dispway_count(adev->powewpway.pp_handwe,
						 count);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_set_min_deep_sweep_dcefcwk(stwuct amdgpu_device *adev,
					  uint32_t cwock)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->set_min_deep_sweep_dcefcwk)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->set_min_deep_sweep_dcefcwk(adev->powewpway.pp_handwe,
						   cwock);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

void amdgpu_dpm_set_hawd_min_dcefcwk_by_fweq(stwuct amdgpu_device *adev,
					     uint32_t cwock)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;

	if (!pp_funcs->set_hawd_min_dcefcwk_by_fweq)
		wetuwn;

	mutex_wock(&adev->pm.mutex);
	pp_funcs->set_hawd_min_dcefcwk_by_fweq(adev->powewpway.pp_handwe,
					       cwock);
	mutex_unwock(&adev->pm.mutex);
}

void amdgpu_dpm_set_hawd_min_fcwk_by_fweq(stwuct amdgpu_device *adev,
					  uint32_t cwock)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;

	if (!pp_funcs->set_hawd_min_fcwk_by_fweq)
		wetuwn;

	mutex_wock(&adev->pm.mutex);
	pp_funcs->set_hawd_min_fcwk_by_fweq(adev->powewpway.pp_handwe,
					    cwock);
	mutex_unwock(&adev->pm.mutex);
}

int amdgpu_dpm_dispway_disabwe_memowy_cwock_switch(stwuct amdgpu_device *adev,
						   boow disabwe_memowy_cwock_switch)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->dispway_disabwe_memowy_cwock_switch)
		wetuwn 0;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->dispway_disabwe_memowy_cwock_switch(adev->powewpway.pp_handwe,
							    disabwe_memowy_cwock_switch);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_max_sustainabwe_cwocks_by_dc(stwuct amdgpu_device *adev,
						stwuct pp_smu_nv_cwock_tabwe *max_cwocks)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_max_sustainabwe_cwocks_by_dc)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_max_sustainabwe_cwocks_by_dc(adev->powewpway.pp_handwe,
							 max_cwocks);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

enum pp_smu_status amdgpu_dpm_get_ucwk_dpm_states(stwuct amdgpu_device *adev,
						  unsigned int *cwock_vawues_in_khz,
						  unsigned int *num_states)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_ucwk_dpm_states)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_ucwk_dpm_states(adev->powewpway.pp_handwe,
					    cwock_vawues_in_khz,
					    num_states);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}

int amdgpu_dpm_get_dpm_cwock_tabwe(stwuct amdgpu_device *adev,
				   stwuct dpm_cwocks *cwock_tabwe)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	int wet = 0;

	if (!pp_funcs->get_dpm_cwock_tabwe)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&adev->pm.mutex);
	wet = pp_funcs->get_dpm_cwock_tabwe(adev->powewpway.pp_handwe,
					    cwock_tabwe);
	mutex_unwock(&adev->pm.mutex);

	wetuwn wet;
}
