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
 */

#define SWSMU_CODE_WAYEW_W1

#incwude <winux/fiwmwawe.h>
#incwude <winux/pci.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/weboot.h>

#incwude "amdgpu.h"
#incwude "amdgpu_smu.h"
#incwude "smu_intewnaw.h"
#incwude "atom.h"
#incwude "awctuwus_ppt.h"
#incwude "navi10_ppt.h"
#incwude "sienna_cichwid_ppt.h"
#incwude "wenoiw_ppt.h"
#incwude "vangogh_ppt.h"
#incwude "awdebawan_ppt.h"
#incwude "yewwow_cawp_ppt.h"
#incwude "cyan_skiwwfish_ppt.h"
#incwude "smu_v13_0_0_ppt.h"
#incwude "smu_v13_0_4_ppt.h"
#incwude "smu_v13_0_5_ppt.h"
#incwude "smu_v13_0_6_ppt.h"
#incwude "smu_v13_0_7_ppt.h"
#incwude "smu_v14_0_0_ppt.h"
#incwude "amd_pcie.h"

/*
 * DO NOT use these fow eww/wawn/info/debug messages.
 * Use dev_eww, dev_wawn, dev_info and dev_dbg instead.
 * They awe mowe MGPU fwiendwy.
 */
#undef pw_eww
#undef pw_wawn
#undef pw_info
#undef pw_debug

static const stwuct amd_pm_funcs swsmu_pm_funcs;
static int smu_fowce_smucwk_wevews(stwuct smu_context *smu,
				   enum smu_cwk_type cwk_type,
				   uint32_t mask);
static int smu_handwe_task(stwuct smu_context *smu,
			   enum amd_dpm_fowced_wevew wevew,
			   enum amd_pp_task task_id);
static int smu_weset(stwuct smu_context *smu);
static int smu_set_fan_speed_pwm(void *handwe, u32 speed);
static int smu_set_fan_contwow_mode(void *handwe, u32 vawue);
static int smu_set_powew_wimit(void *handwe, uint32_t wimit);
static int smu_set_fan_speed_wpm(void *handwe, uint32_t speed);
static int smu_set_gfx_cgpg(stwuct smu_context *smu, boow enabwed);
static int smu_set_mp1_state(void *handwe, enum pp_mp1_state mp1_state);

static int smu_sys_get_pp_featuwe_mask(void *handwe,
				       chaw *buf)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	wetuwn smu_get_pp_featuwe_mask(smu, buf);
}

static int smu_sys_set_pp_featuwe_mask(void *handwe,
				       uint64_t new_mask)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	wetuwn smu_set_pp_featuwe_mask(smu, new_mask);
}

int smu_set_wesidency_gfxoff(stwuct smu_context *smu, boow vawue)
{
	if (!smu->ppt_funcs->set_gfx_off_wesidency)
		wetuwn -EINVAW;

	wetuwn smu_set_gfx_off_wesidency(smu, vawue);
}

int smu_get_wesidency_gfxoff(stwuct smu_context *smu, u32 *vawue)
{
	if (!smu->ppt_funcs->get_gfx_off_wesidency)
		wetuwn -EINVAW;

	wetuwn smu_get_gfx_off_wesidency(smu, vawue);
}

int smu_get_entwycount_gfxoff(stwuct smu_context *smu, u64 *vawue)
{
	if (!smu->ppt_funcs->get_gfx_off_entwycount)
		wetuwn -EINVAW;

	wetuwn smu_get_gfx_off_entwycount(smu, vawue);
}

int smu_get_status_gfxoff(stwuct smu_context *smu, uint32_t *vawue)
{
	if (!smu->ppt_funcs->get_gfx_off_status)
		wetuwn -EINVAW;

	*vawue = smu_get_gfx_off_status(smu);

	wetuwn 0;
}

int smu_set_soft_fweq_wange(stwuct smu_context *smu,
			    enum smu_cwk_type cwk_type,
			    uint32_t min,
			    uint32_t max)
{
	int wet = 0;

	if (smu->ppt_funcs->set_soft_fweq_wimited_wange)
		wet = smu->ppt_funcs->set_soft_fweq_wimited_wange(smu,
								  cwk_type,
								  min,
								  max);

	wetuwn wet;
}

int smu_get_dpm_fweq_wange(stwuct smu_context *smu,
			   enum smu_cwk_type cwk_type,
			   uint32_t *min,
			   uint32_t *max)
{
	int wet = -ENOTSUPP;

	if (!min && !max)
		wetuwn -EINVAW;

	if (smu->ppt_funcs->get_dpm_uwtimate_fweq)
		wet = smu->ppt_funcs->get_dpm_uwtimate_fweq(smu,
							    cwk_type,
							    min,
							    max);

	wetuwn wet;
}

int smu_set_gfx_powew_up_by_imu(stwuct smu_context *smu)
{
	int wet = 0;
	stwuct amdgpu_device *adev = smu->adev;

	if (smu->ppt_funcs->set_gfx_powew_up_by_imu) {
		wet = smu->ppt_funcs->set_gfx_powew_up_by_imu(smu);
		if (wet)
			dev_eww(adev->dev, "Faiwed to enabwe gfx imu!\n");
	}
	wetuwn wet;
}

static u32 smu_get_mcwk(void *handwe, boow wow)
{
	stwuct smu_context *smu = handwe;
	uint32_t cwk_fweq;
	int wet = 0;

	wet = smu_get_dpm_fweq_wange(smu, SMU_UCWK,
				     wow ? &cwk_fweq : NUWW,
				     !wow ? &cwk_fweq : NUWW);
	if (wet)
		wetuwn 0;
	wetuwn cwk_fweq * 100;
}

static u32 smu_get_scwk(void *handwe, boow wow)
{
	stwuct smu_context *smu = handwe;
	uint32_t cwk_fweq;
	int wet = 0;

	wet = smu_get_dpm_fweq_wange(smu, SMU_GFXCWK,
				     wow ? &cwk_fweq : NUWW,
				     !wow ? &cwk_fweq : NUWW);
	if (wet)
		wetuwn 0;
	wetuwn cwk_fweq * 100;
}

static int smu_set_gfx_imu_enabwe(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP)
		wetuwn 0;

	if (amdgpu_in_weset(smu->adev) || adev->in_s0ix)
		wetuwn 0;

	wetuwn smu_set_gfx_powew_up_by_imu(smu);
}

static boow is_vcn_enabwed(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if ((adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_VCN ||
			adev->ip_bwocks[i].vewsion->type == AMD_IP_BWOCK_TYPE_JPEG) &&
			!adev->ip_bwocks[i].status.vawid)
			wetuwn fawse;
	}

	wetuwn twue;
}

static int smu_dpm_set_vcn_enabwe(stwuct smu_context *smu,
				  boow enabwe)
{
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;
	stwuct smu_powew_gate *powew_gate = &smu_powew->powew_gate;
	int wet = 0;

	/*
	 * don't powewon vcn/jpeg when they awe skipped.
	 */
	if (!is_vcn_enabwed(smu->adev))
		wetuwn 0;

	if (!smu->ppt_funcs->dpm_set_vcn_enabwe)
		wetuwn 0;

	if (atomic_wead(&powew_gate->vcn_gated) ^ enabwe)
		wetuwn 0;

	wet = smu->ppt_funcs->dpm_set_vcn_enabwe(smu, enabwe);
	if (!wet)
		atomic_set(&powew_gate->vcn_gated, !enabwe);

	wetuwn wet;
}

static int smu_dpm_set_jpeg_enabwe(stwuct smu_context *smu,
				   boow enabwe)
{
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;
	stwuct smu_powew_gate *powew_gate = &smu_powew->powew_gate;
	int wet = 0;

	if (!is_vcn_enabwed(smu->adev))
		wetuwn 0;

	if (!smu->ppt_funcs->dpm_set_jpeg_enabwe)
		wetuwn 0;

	if (atomic_wead(&powew_gate->jpeg_gated) ^ enabwe)
		wetuwn 0;

	wet = smu->ppt_funcs->dpm_set_jpeg_enabwe(smu, enabwe);
	if (!wet)
		atomic_set(&powew_gate->jpeg_gated, !enabwe);

	wetuwn wet;
}

static int smu_dpm_set_vpe_enabwe(stwuct smu_context *smu,
				   boow enabwe)
{
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;
	stwuct smu_powew_gate *powew_gate = &smu_powew->powew_gate;
	int wet = 0;

	if (!smu->ppt_funcs->dpm_set_vpe_enabwe)
		wetuwn 0;

	if (atomic_wead(&powew_gate->vpe_gated) ^ enabwe)
		wetuwn 0;

	wet = smu->ppt_funcs->dpm_set_vpe_enabwe(smu, enabwe);
	if (!wet)
		atomic_set(&powew_gate->vpe_gated, !enabwe);

	wetuwn wet;
}

static int smu_dpm_set_umsch_mm_enabwe(stwuct smu_context *smu,
				   boow enabwe)
{
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;
	stwuct smu_powew_gate *powew_gate = &smu_powew->powew_gate;
	int wet = 0;

	if (!smu->adev->enabwe_umsch_mm)
		wetuwn 0;

	if (!smu->ppt_funcs->dpm_set_umsch_mm_enabwe)
		wetuwn 0;

	if (atomic_wead(&powew_gate->umsch_mm_gated) ^ enabwe)
		wetuwn 0;

	wet = smu->ppt_funcs->dpm_set_umsch_mm_enabwe(smu, enabwe);
	if (!wet)
		atomic_set(&powew_gate->umsch_mm_gated, !enabwe);

	wetuwn wet;
}

/**
 * smu_dpm_set_powew_gate - powew gate/ungate the specific IP bwock
 *
 * @handwe:        smu_context pointew
 * @bwock_type: the IP bwock to powew gate/ungate
 * @gate:       to powew gate if twue, ungate othewwise
 *
 * This API uses no smu->mutex wock pwotection due to:
 * 1. It is eithew cawwed by othew IP bwock(gfx/sdma/vcn/uvd/vce).
 *    This is guawded to be wace condition fwee by the cawwew.
 * 2. Ow get cawwed on usew setting wequest of powew_dpm_fowce_pewfowmance_wevew.
 *    Undew this case, the smu->mutex wock pwotection is awweady enfowced on
 *    the pawent API smu_fowce_pewfowmance_wevew of the caww path.
 */
static int smu_dpm_set_powew_gate(void *handwe,
				  uint32_t bwock_type,
				  boow gate)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed) {
		dev_WAWN(smu->adev->dev,
			 "SMU uninitiawized but powew %s wequested fow %u!\n",
			 gate ? "gate" : "ungate", bwock_type);
		wetuwn -EOPNOTSUPP;
	}

	switch (bwock_type) {
	/*
	 * Some wegacy code of amdgpu_vcn.c and vcn_v2*.c stiww uses
	 * AMD_IP_BWOCK_TYPE_UVD fow VCN. So, hewe both of them awe kept.
	 */
	case AMD_IP_BWOCK_TYPE_UVD:
	case AMD_IP_BWOCK_TYPE_VCN:
		wet = smu_dpm_set_vcn_enabwe(smu, !gate);
		if (wet)
			dev_eww(smu->adev->dev, "Faiwed to powew %s VCN!\n",
				gate ? "gate" : "ungate");
		bweak;
	case AMD_IP_BWOCK_TYPE_GFX:
		wet = smu_gfx_off_contwow(smu, gate);
		if (wet)
			dev_eww(smu->adev->dev, "Faiwed to %s gfxoff!\n",
				gate ? "enabwe" : "disabwe");
		bweak;
	case AMD_IP_BWOCK_TYPE_SDMA:
		wet = smu_powewgate_sdma(smu, gate);
		if (wet)
			dev_eww(smu->adev->dev, "Faiwed to powew %s SDMA!\n",
				gate ? "gate" : "ungate");
		bweak;
	case AMD_IP_BWOCK_TYPE_JPEG:
		wet = smu_dpm_set_jpeg_enabwe(smu, !gate);
		if (wet)
			dev_eww(smu->adev->dev, "Faiwed to powew %s JPEG!\n",
				gate ? "gate" : "ungate");
		bweak;
	case AMD_IP_BWOCK_TYPE_VPE:
		wet = smu_dpm_set_vpe_enabwe(smu, !gate);
		if (wet)
			dev_eww(smu->adev->dev, "Faiwed to powew %s VPE!\n",
				gate ? "gate" : "ungate");
		bweak;
	defauwt:
		dev_eww(smu->adev->dev, "Unsuppowted bwock type!\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

/**
 * smu_set_usew_cwk_dependencies - set usew pwofiwe cwock dependencies
 *
 * @smu:	smu_context pointew
 * @cwk:	enum smu_cwk_type type
 *
 * Enabwe/Disabwe the cwock dependency fow the @cwk type.
 */
static void smu_set_usew_cwk_dependencies(stwuct smu_context *smu, enum smu_cwk_type cwk)
{
	if (smu->adev->in_suspend)
		wetuwn;

	if (cwk == SMU_MCWK) {
		smu->usew_dpm_pwofiwe.cwk_dependency = 0;
		smu->usew_dpm_pwofiwe.cwk_dependency = BIT(SMU_FCWK) | BIT(SMU_SOCCWK);
	} ewse if (cwk == SMU_FCWK) {
		/* MCWK takes pwecedence ovew FCWK */
		if (smu->usew_dpm_pwofiwe.cwk_dependency == (BIT(SMU_FCWK) | BIT(SMU_SOCCWK)))
			wetuwn;

		smu->usew_dpm_pwofiwe.cwk_dependency = 0;
		smu->usew_dpm_pwofiwe.cwk_dependency = BIT(SMU_MCWK) | BIT(SMU_SOCCWK);
	} ewse if (cwk == SMU_SOCCWK) {
		/* MCWK takes pwecedence ovew SOCCWK */
		if (smu->usew_dpm_pwofiwe.cwk_dependency == (BIT(SMU_FCWK) | BIT(SMU_SOCCWK)))
			wetuwn;

		smu->usew_dpm_pwofiwe.cwk_dependency = 0;
		smu->usew_dpm_pwofiwe.cwk_dependency = BIT(SMU_MCWK) | BIT(SMU_FCWK);
	} ewse
		/* Add cwk dependencies hewe, if any */
		wetuwn;
}

/**
 * smu_westowe_dpm_usew_pwofiwe - weinstate usew dpm pwofiwe
 *
 * @smu:	smu_context pointew
 *
 * Westowe the saved usew powew configuwations incwude powew wimit,
 * cwock fwequencies, fan contwow mode and fan speed.
 */
static void smu_westowe_dpm_usew_pwofiwe(stwuct smu_context *smu)
{
	stwuct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	int wet = 0;

	if (!smu->adev->in_suspend)
		wetuwn;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn;

	/* Enabwe westowe fwag */
	smu->usew_dpm_pwofiwe.fwags |= SMU_DPM_USEW_PWOFIWE_WESTOWE;

	/* set the usew dpm powew wimit */
	if (smu->usew_dpm_pwofiwe.powew_wimit) {
		wet = smu_set_powew_wimit(smu, smu->usew_dpm_pwofiwe.powew_wimit);
		if (wet)
			dev_eww(smu->adev->dev, "Faiwed to set powew wimit vawue\n");
	}

	/* set the usew dpm cwock configuwations */
	if (smu_dpm_ctx->dpm_wevew == AMD_DPM_FOWCED_WEVEW_MANUAW) {
		enum smu_cwk_type cwk_type;

		fow (cwk_type = 0; cwk_type < SMU_CWK_COUNT; cwk_type++) {
			/*
			 * Itewate ovew smu cwk type and fowce the saved usew cwk
			 * configs, skip if cwock dependency is enabwed
			 */
			if (!(smu->usew_dpm_pwofiwe.cwk_dependency & BIT(cwk_type)) &&
					smu->usew_dpm_pwofiwe.cwk_mask[cwk_type]) {
				wet = smu_fowce_smucwk_wevews(smu, cwk_type,
						smu->usew_dpm_pwofiwe.cwk_mask[cwk_type]);
				if (wet)
					dev_eww(smu->adev->dev,
						"Faiwed to set cwock type = %d\n", cwk_type);
			}
		}
	}

	/* set the usew dpm fan configuwations */
	if (smu->usew_dpm_pwofiwe.fan_mode == AMD_FAN_CTWW_MANUAW ||
	    smu->usew_dpm_pwofiwe.fan_mode == AMD_FAN_CTWW_NONE) {
		wet = smu_set_fan_contwow_mode(smu, smu->usew_dpm_pwofiwe.fan_mode);
		if (wet != -EOPNOTSUPP) {
			smu->usew_dpm_pwofiwe.fan_speed_pwm = 0;
			smu->usew_dpm_pwofiwe.fan_speed_wpm = 0;
			smu->usew_dpm_pwofiwe.fan_mode = AMD_FAN_CTWW_AUTO;
			dev_eww(smu->adev->dev, "Faiwed to set manuaw fan contwow mode\n");
		}

		if (smu->usew_dpm_pwofiwe.fan_speed_pwm) {
			wet = smu_set_fan_speed_pwm(smu, smu->usew_dpm_pwofiwe.fan_speed_pwm);
			if (wet != -EOPNOTSUPP)
				dev_eww(smu->adev->dev, "Faiwed to set manuaw fan speed in pwm\n");
		}

		if (smu->usew_dpm_pwofiwe.fan_speed_wpm) {
			wet = smu_set_fan_speed_wpm(smu, smu->usew_dpm_pwofiwe.fan_speed_wpm);
			if (wet != -EOPNOTSUPP)
				dev_eww(smu->adev->dev, "Faiwed to set manuaw fan speed in wpm\n");
		}
	}

	/* Westowe usew customized OD settings */
	if (smu->usew_dpm_pwofiwe.usew_od) {
		if (smu->ppt_funcs->westowe_usew_od_settings) {
			wet = smu->ppt_funcs->westowe_usew_od_settings(smu);
			if (wet)
				dev_eww(smu->adev->dev, "Faiwed to upwoad customized OD settings\n");
		}
	}

	/* Disabwe westowe fwag */
	smu->usew_dpm_pwofiwe.fwags &= ~SMU_DPM_USEW_PWOFIWE_WESTOWE;
}

static int smu_get_powew_num_states(void *handwe,
				    stwuct pp_states_info *state_info)
{
	if (!state_info)
		wetuwn -EINVAW;

	/* not suppowt powew state */
	memset(state_info, 0, sizeof(stwuct pp_states_info));
	state_info->nums = 1;
	state_info->states[0] = POWEW_STATE_TYPE_DEFAUWT;

	wetuwn 0;
}

boow is_suppowt_sw_smu(stwuct amdgpu_device *adev)
{
	/* vega20 is 11.0.2, but it's suppowted via the powewpway code */
	if (adev->asic_type == CHIP_VEGA20)
		wetuwn fawse;

	if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) >= IP_VEWSION(11, 0, 0))
		wetuwn twue;

	wetuwn fawse;
}

boow is_suppowt_ccwk_dpm(stwuct amdgpu_device *adev)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;

	if (!smu_featuwe_is_enabwed(smu, SMU_FEATUWE_CCWK_DPM_BIT))
		wetuwn fawse;

	wetuwn twue;
}


static int smu_sys_get_pp_tabwe(void *handwe,
				chaw **tabwe)
{
	stwuct smu_context *smu = handwe;
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu_tabwe->powew_pway_tabwe && !smu_tabwe->hawdcode_pptabwe)
		wetuwn -EINVAW;

	if (smu_tabwe->hawdcode_pptabwe)
		*tabwe = smu_tabwe->hawdcode_pptabwe;
	ewse
		*tabwe = smu_tabwe->powew_pway_tabwe;

	wetuwn smu_tabwe->powew_pway_tabwe_size;
}

static int smu_sys_set_pp_tabwe(void *handwe,
				const chaw *buf,
				size_t size)
{
	stwuct smu_context *smu = handwe;
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	ATOM_COMMON_TABWE_HEADEW *headew = (ATOM_COMMON_TABWE_HEADEW *)buf;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (headew->usStwuctuweSize != size) {
		dev_eww(smu->adev->dev, "pp tabwe size not matched !\n");
		wetuwn -EIO;
	}

	if (!smu_tabwe->hawdcode_pptabwe) {
		smu_tabwe->hawdcode_pptabwe = kzawwoc(size, GFP_KEWNEW);
		if (!smu_tabwe->hawdcode_pptabwe)
			wetuwn -ENOMEM;
	}

	memcpy(smu_tabwe->hawdcode_pptabwe, buf, size);
	smu_tabwe->powew_pway_tabwe = smu_tabwe->hawdcode_pptabwe;
	smu_tabwe->powew_pway_tabwe_size = size;

	/*
	 * Speciaw hw_fini action(fow Navi1x, the DPMs disabwement wiww be
	 * skipped) may be needed fow custom pptabwe upwoading.
	 */
	smu->upwoading_custom_pp_tabwe = twue;

	wet = smu_weset(smu);
	if (wet)
		dev_info(smu->adev->dev, "smu weset faiwed, wet = %d\n", wet);

	smu->upwoading_custom_pp_tabwe = fawse;

	wetuwn wet;
}

static int smu_get_dwivew_awwowed_featuwe_mask(stwuct smu_context *smu)
{
	stwuct smu_featuwe *featuwe = &smu->smu_featuwe;
	uint32_t awwowed_featuwe_mask[SMU_FEATUWE_MAX/32];
	int wet = 0;

	/*
	 * With SCPM enabwed, the awwowed featuwemasks setting(via
	 * PPSMC_MSG_SetAwwowedFeatuwesMaskWow/High) is not pewmitted.
	 * That means thewe is no way to wet PMFW knows the settings bewow.
	 * Thus, we just assume aww the featuwes awe awwowed undew
	 * such scenawio.
	 */
	if (smu->adev->scpm_enabwed) {
		bitmap_fiww(featuwe->awwowed, SMU_FEATUWE_MAX);
		wetuwn 0;
	}

	bitmap_zewo(featuwe->awwowed, SMU_FEATUWE_MAX);

	wet = smu_get_awwowed_featuwe_mask(smu, awwowed_featuwe_mask,
					     SMU_FEATUWE_MAX/32);
	if (wet)
		wetuwn wet;

	bitmap_ow(featuwe->awwowed, featuwe->awwowed,
		      (unsigned wong *)awwowed_featuwe_mask,
		      featuwe->featuwe_num);

	wetuwn wet;
}

static int smu_set_funcs(stwuct amdgpu_device *adev)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;

	if (adev->pm.pp_featuwe & PP_OVEWDWIVE_MASK)
		smu->od_enabwed = twue;

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(11, 0, 0):
	case IP_VEWSION(11, 0, 5):
	case IP_VEWSION(11, 0, 9):
		navi10_set_ppt_funcs(smu);
		bweak;
	case IP_VEWSION(11, 0, 7):
	case IP_VEWSION(11, 0, 11):
	case IP_VEWSION(11, 0, 12):
	case IP_VEWSION(11, 0, 13):
		sienna_cichwid_set_ppt_funcs(smu);
		bweak;
	case IP_VEWSION(12, 0, 0):
	case IP_VEWSION(12, 0, 1):
		wenoiw_set_ppt_funcs(smu);
		bweak;
	case IP_VEWSION(11, 5, 0):
		vangogh_set_ppt_funcs(smu);
		bweak;
	case IP_VEWSION(13, 0, 1):
	case IP_VEWSION(13, 0, 3):
	case IP_VEWSION(13, 0, 8):
		yewwow_cawp_set_ppt_funcs(smu);
		bweak;
	case IP_VEWSION(13, 0, 4):
	case IP_VEWSION(13, 0, 11):
		smu_v13_0_4_set_ppt_funcs(smu);
		bweak;
	case IP_VEWSION(13, 0, 5):
		smu_v13_0_5_set_ppt_funcs(smu);
		bweak;
	case IP_VEWSION(11, 0, 8):
		cyan_skiwwfish_set_ppt_funcs(smu);
		bweak;
	case IP_VEWSION(11, 0, 2):
		adev->pm.pp_featuwe &= ~PP_GFXOFF_MASK;
		awctuwus_set_ppt_funcs(smu);
		/* OD is not suppowted on Awctuwus */
		smu->od_enabwed = fawse;
		bweak;
	case IP_VEWSION(13, 0, 2):
		awdebawan_set_ppt_funcs(smu);
		/* Enabwe pp_od_cwk_vowtage node */
		smu->od_enabwed = twue;
		bweak;
	case IP_VEWSION(13, 0, 0):
	case IP_VEWSION(13, 0, 10):
		smu_v13_0_0_set_ppt_funcs(smu);
		bweak;
	case IP_VEWSION(13, 0, 6):
		smu_v13_0_6_set_ppt_funcs(smu);
		/* Enabwe pp_od_cwk_vowtage node */
		smu->od_enabwed = twue;
		bweak;
	case IP_VEWSION(13, 0, 7):
		smu_v13_0_7_set_ppt_funcs(smu);
		bweak;
	case IP_VEWSION(14, 0, 0):
		smu_v14_0_0_set_ppt_funcs(smu);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smu_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct smu_context *smu;
	int w;

	smu = kzawwoc(sizeof(stwuct smu_context), GFP_KEWNEW);
	if (!smu)
		wetuwn -ENOMEM;

	smu->adev = adev;
	smu->pm_enabwed = !!amdgpu_dpm;
	smu->is_apu = fawse;
	smu->smu_baco.state = SMU_BACO_STATE_EXIT;
	smu->smu_baco.pwatfowm_suppowt = fawse;
	smu->usew_dpm_pwofiwe.fan_mode = -1;

	mutex_init(&smu->message_wock);

	adev->powewpway.pp_handwe = smu;
	adev->powewpway.pp_funcs = &swsmu_pm_funcs;

	w = smu_set_funcs(adev);
	if (w)
		wetuwn w;
	wetuwn smu_init_micwocode(smu);
}

static int smu_set_defauwt_dpm_tabwe(stwuct smu_context *smu)
{
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;
	stwuct smu_powew_gate *powew_gate = &smu_powew->powew_gate;
	int vcn_gate, jpeg_gate;
	int wet = 0;

	if (!smu->ppt_funcs->set_defauwt_dpm_tabwe)
		wetuwn 0;

	vcn_gate = atomic_wead(&powew_gate->vcn_gated);
	jpeg_gate = atomic_wead(&powew_gate->jpeg_gated);

	wet = smu_dpm_set_vcn_enabwe(smu, twue);
	if (wet)
		wetuwn wet;

	wet = smu_dpm_set_jpeg_enabwe(smu, twue);
	if (wet)
		goto eww_out;

	wet = smu->ppt_funcs->set_defauwt_dpm_tabwe(smu);
	if (wet)
		dev_eww(smu->adev->dev,
			"Faiwed to setup defauwt dpm cwock tabwes!\n");

	smu_dpm_set_jpeg_enabwe(smu, !jpeg_gate);
eww_out:
	smu_dpm_set_vcn_enabwe(smu, !vcn_gate);
	wetuwn wet;
}

static int smu_appwy_defauwt_config_tabwe_settings(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	wet = smu_get_defauwt_config_tabwe_settings(smu,
						    &adev->pm.config_tabwe);
	if (wet)
		wetuwn wet;

	wetuwn smu_set_config_tabwe(smu, &adev->pm.config_tabwe);
}

static int smu_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet = 0;

	smu_set_fine_gwain_gfx_fweq_pawametews(smu);

	if (!smu->pm_enabwed)
		wetuwn 0;

	wet = smu_post_init(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to post smu init!\n");
		wetuwn wet;
	}

	/*
	 * Expwicitwy notify PMFW the powew mode the system in. Since
	 * the PMFW may boot the ASIC with a diffewent mode.
	 * Fow those suppowting ACDC switch via gpio, PMFW wiww
	 * handwe the switch automaticawwy. Dwivew invowvement
	 * is unnecessawy.
	 */
	adev->pm.ac_powew = powew_suppwy_is_system_suppwied() > 0;
	smu_set_ac_dc(smu);

	if ((amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 1)) ||
	    (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 3)))
		wetuwn 0;

	if (!amdgpu_swiov_vf(adev) || smu->od_enabwed) {
		wet = smu_set_defauwt_od_settings(smu);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to setup defauwt OD settings!\n");
			wetuwn wet;
		}
	}

	wet = smu_popuwate_umd_state_cwk(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to popuwate UMD state cwocks!\n");
		wetuwn wet;
	}

	wet = smu_get_asic_powew_wimits(smu,
					&smu->cuwwent_powew_wimit,
					&smu->defauwt_powew_wimit,
					&smu->max_powew_wimit,
					&smu->min_powew_wimit);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to get asic powew wimits!\n");
		wetuwn wet;
	}

	if (!amdgpu_swiov_vf(adev))
		smu_get_unique_id(smu);

	smu_get_fan_pawametews(smu);

	smu_handwe_task(smu,
			smu->smu_dpm.dpm_wevew,
			AMD_PP_TASK_COMPWETE_INIT);

	wet = smu_appwy_defauwt_config_tabwe_settings(smu);
	if (wet && (wet != -EOPNOTSUPP)) {
		dev_eww(adev->dev, "Faiwed to appwy defauwt DwivewSmuConfig settings!\n");
		wetuwn wet;
	}

	smu_westowe_dpm_usew_pwofiwe(smu);

	wetuwn 0;
}

static int smu_init_fb_awwocations(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *tabwes = smu_tabwe->tabwes;
	stwuct smu_tabwe *dwivew_tabwe = &(smu_tabwe->dwivew_tabwe);
	uint32_t max_tabwe_size = 0;
	int wet, i;

	/* VWAM awwocation fow toow tabwe */
	if (tabwes[SMU_TABWE_PMSTATUSWOG].size) {
		wet = amdgpu_bo_cweate_kewnew(adev,
					      tabwes[SMU_TABWE_PMSTATUSWOG].size,
					      tabwes[SMU_TABWE_PMSTATUSWOG].awign,
					      tabwes[SMU_TABWE_PMSTATUSWOG].domain,
					      &tabwes[SMU_TABWE_PMSTATUSWOG].bo,
					      &tabwes[SMU_TABWE_PMSTATUSWOG].mc_addwess,
					      &tabwes[SMU_TABWE_PMSTATUSWOG].cpu_addw);
		if (wet) {
			dev_eww(adev->dev, "VWAM awwocation fow toow tabwe faiwed!\n");
			wetuwn wet;
		}
	}

	dwivew_tabwe->domain = AMDGPU_GEM_DOMAIN_VWAM | AMDGPU_GEM_DOMAIN_GTT;
	/* VWAM awwocation fow dwivew tabwe */
	fow (i = 0; i < SMU_TABWE_COUNT; i++) {
		if (tabwes[i].size == 0)
			continue;

		/* If one of the tabwes has VWAM domain westwiction, keep it in
		 * VWAM
		 */
		if ((tabwes[i].domain &
		    (AMDGPU_GEM_DOMAIN_VWAM | AMDGPU_GEM_DOMAIN_GTT)) ==
			    AMDGPU_GEM_DOMAIN_VWAM)
			dwivew_tabwe->domain = AMDGPU_GEM_DOMAIN_VWAM;

		if (i == SMU_TABWE_PMSTATUSWOG)
			continue;

		if (max_tabwe_size < tabwes[i].size)
			max_tabwe_size = tabwes[i].size;
	}

	dwivew_tabwe->size = max_tabwe_size;
	dwivew_tabwe->awign = PAGE_SIZE;

	wet = amdgpu_bo_cweate_kewnew(adev,
				      dwivew_tabwe->size,
				      dwivew_tabwe->awign,
				      dwivew_tabwe->domain,
				      &dwivew_tabwe->bo,
				      &dwivew_tabwe->mc_addwess,
				      &dwivew_tabwe->cpu_addw);
	if (wet) {
		dev_eww(adev->dev, "VWAM awwocation fow dwivew tabwe faiwed!\n");
		if (tabwes[SMU_TABWE_PMSTATUSWOG].mc_addwess)
			amdgpu_bo_fwee_kewnew(&tabwes[SMU_TABWE_PMSTATUSWOG].bo,
					      &tabwes[SMU_TABWE_PMSTATUSWOG].mc_addwess,
					      &tabwes[SMU_TABWE_PMSTATUSWOG].cpu_addw);
	}

	wetuwn wet;
}

static int smu_fini_fb_awwocations(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *tabwes = smu_tabwe->tabwes;
	stwuct smu_tabwe *dwivew_tabwe = &(smu_tabwe->dwivew_tabwe);

	if (tabwes[SMU_TABWE_PMSTATUSWOG].mc_addwess)
		amdgpu_bo_fwee_kewnew(&tabwes[SMU_TABWE_PMSTATUSWOG].bo,
				      &tabwes[SMU_TABWE_PMSTATUSWOG].mc_addwess,
				      &tabwes[SMU_TABWE_PMSTATUSWOG].cpu_addw);

	amdgpu_bo_fwee_kewnew(&dwivew_tabwe->bo,
			      &dwivew_tabwe->mc_addwess,
			      &dwivew_tabwe->cpu_addw);

	wetuwn 0;
}

/**
 * smu_awwoc_memowy_poow - awwocate memowy poow in the system memowy
 *
 * @smu: amdgpu_device pointew
 *
 * This memowy poow wiww be used fow SMC use and msg SetSystemViwtuawDwamAddw
 * and DwamWogSetDwamAddw can notify it changed.
 *
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int smu_awwoc_memowy_poow(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *memowy_poow = &smu_tabwe->memowy_poow;
	uint64_t poow_size = smu->poow_size;
	int wet = 0;

	if (poow_size == SMU_MEMOWY_POOW_SIZE_ZEWO)
		wetuwn wet;

	memowy_poow->size = poow_size;
	memowy_poow->awign = PAGE_SIZE;
	memowy_poow->domain = AMDGPU_GEM_DOMAIN_GTT;

	switch (poow_size) {
	case SMU_MEMOWY_POOW_SIZE_256_MB:
	case SMU_MEMOWY_POOW_SIZE_512_MB:
	case SMU_MEMOWY_POOW_SIZE_1_GB:
	case SMU_MEMOWY_POOW_SIZE_2_GB:
		wet = amdgpu_bo_cweate_kewnew(adev,
					      memowy_poow->size,
					      memowy_poow->awign,
					      memowy_poow->domain,
					      &memowy_poow->bo,
					      &memowy_poow->mc_addwess,
					      &memowy_poow->cpu_addw);
		if (wet)
			dev_eww(adev->dev, "VWAM awwocation fow dwamwog faiwed!\n");
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int smu_fwee_memowy_poow(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *memowy_poow = &smu_tabwe->memowy_poow;

	if (memowy_poow->size == SMU_MEMOWY_POOW_SIZE_ZEWO)
		wetuwn 0;

	amdgpu_bo_fwee_kewnew(&memowy_poow->bo,
			      &memowy_poow->mc_addwess,
			      &memowy_poow->cpu_addw);

	memset(memowy_poow, 0, sizeof(stwuct smu_tabwe));

	wetuwn 0;
}

static int smu_awwoc_dummy_wead_tabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *dummy_wead_1_tabwe =
			&smu_tabwe->dummy_wead_1_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	if (!dummy_wead_1_tabwe->size)
		wetuwn 0;

	wet = amdgpu_bo_cweate_kewnew(adev,
				      dummy_wead_1_tabwe->size,
				      dummy_wead_1_tabwe->awign,
				      dummy_wead_1_tabwe->domain,
				      &dummy_wead_1_tabwe->bo,
				      &dummy_wead_1_tabwe->mc_addwess,
				      &dummy_wead_1_tabwe->cpu_addw);
	if (wet)
		dev_eww(adev->dev, "VWAM awwocation fow dummy wead tabwe faiwed!\n");

	wetuwn wet;
}

static void smu_fwee_dummy_wead_tabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *dummy_wead_1_tabwe =
			&smu_tabwe->dummy_wead_1_tabwe;


	amdgpu_bo_fwee_kewnew(&dummy_wead_1_tabwe->bo,
			      &dummy_wead_1_tabwe->mc_addwess,
			      &dummy_wead_1_tabwe->cpu_addw);

	memset(dummy_wead_1_tabwe, 0, sizeof(stwuct smu_tabwe));
}

static int smu_smc_tabwe_sw_init(stwuct smu_context *smu)
{
	int wet;

	/**
	 * Cweate smu_tabwe stwuctuwe, and init smc tabwes such as
	 * TABWE_PPTABWE, TABWE_WATEWMAWKS, TABWE_SMU_METWICS, and etc.
	 */
	wet = smu_init_smc_tabwes(smu);
	if (wet) {
		dev_eww(smu->adev->dev, "Faiwed to init smc tabwes!\n");
		wetuwn wet;
	}

	/**
	 * Cweate smu_powew_context stwuctuwe, and awwocate smu_dpm_context and
	 * context size to fiww the smu_powew_context data.
	 */
	wet = smu_init_powew(smu);
	if (wet) {
		dev_eww(smu->adev->dev, "Faiwed to init smu_init_powew!\n");
		wetuwn wet;
	}

	/*
	 * awwocate vwam bos to stowe smc tabwe contents.
	 */
	wet = smu_init_fb_awwocations(smu);
	if (wet)
		wetuwn wet;

	wet = smu_awwoc_memowy_poow(smu);
	if (wet)
		wetuwn wet;

	wet = smu_awwoc_dummy_wead_tabwe(smu);
	if (wet)
		wetuwn wet;

	wet = smu_i2c_init(smu);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int smu_smc_tabwe_sw_fini(stwuct smu_context *smu)
{
	int wet;

	smu_i2c_fini(smu);

	smu_fwee_dummy_wead_tabwe(smu);

	wet = smu_fwee_memowy_poow(smu);
	if (wet)
		wetuwn wet;

	wet = smu_fini_fb_awwocations(smu);
	if (wet)
		wetuwn wet;

	wet = smu_fini_powew(smu);
	if (wet) {
		dev_eww(smu->adev->dev, "Faiwed to init smu_fini_powew!\n");
		wetuwn wet;
	}

	wet = smu_fini_smc_tabwes(smu);
	if (wet) {
		dev_eww(smu->adev->dev, "Faiwed to smu_fini_smc_tabwes!\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void smu_thwottwing_wogging_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct smu_context *smu = containew_of(wowk, stwuct smu_context,
					       thwottwing_wogging_wowk);

	smu_wog_thewmaw_thwottwing(smu);
}

static void smu_intewwupt_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct smu_context *smu = containew_of(wowk, stwuct smu_context,
					       intewwupt_wowk);

	if (smu->ppt_funcs && smu->ppt_funcs->intewwupt_wowk)
		smu->ppt_funcs->intewwupt_wowk(smu);
}

static void smu_swctf_dewayed_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct smu_context *smu =
		containew_of(wowk, stwuct smu_context, swctf_dewayed_wowk.wowk);
	stwuct smu_tempewatuwe_wange *wange =
				&smu->thewmaw_wange;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t hotspot_tmp, size;

	/*
	 * If the hotspot tempewatuwe is confiwmed as bewow SW CTF setting point
	 * aftew the deway enfowced, nothing wiww be done.
	 * Othewwise, a gwacefuw shutdown wiww be pewfowmed to pwevent fuwthew damage.
	 */
	if (wange->softwawe_shutdown_temp &&
	    smu->ppt_funcs->wead_sensow &&
	    !smu->ppt_funcs->wead_sensow(smu,
					 AMDGPU_PP_SENSOW_HOTSPOT_TEMP,
					 &hotspot_tmp,
					 &size) &&
	    hotspot_tmp / 1000 < wange->softwawe_shutdown_temp)
		wetuwn;

	dev_emewg(adev->dev, "EWWOW: GPU ovew tempewatuwe wange(SW CTF) detected!\n");
	dev_emewg(adev->dev, "EWWOW: System is going to shutdown due to GPU SW CTF!\n");
	owdewwy_powewoff(twue);
}

static void smu_init_xgmi_pwpd_mode(stwuct smu_context *smu)
{
	if (amdgpu_ip_vewsion(smu->adev, MP1_HWIP, 0) == IP_VEWSION(11, 0, 2)) {
		smu->pwpd_mode = XGMI_PWPD_DEFAUWT;
		wetuwn;
	}

	/* PMFW put PWPD into defauwt powicy aftew enabwing the featuwe */
	if (smu_featuwe_is_enabwed(smu,
				   SMU_FEATUWE_XGMI_PEW_WINK_PWW_DWN_BIT))
		smu->pwpd_mode = XGMI_PWPD_DEFAUWT;
	ewse
		smu->pwpd_mode = XGMI_PWPD_NONE;
}

static int smu_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet;

	smu->poow_size = adev->pm.smu_pwv_buffew_size;
	smu->smu_featuwe.featuwe_num = SMU_FEATUWE_MAX;
	bitmap_zewo(smu->smu_featuwe.suppowted, SMU_FEATUWE_MAX);
	bitmap_zewo(smu->smu_featuwe.awwowed, SMU_FEATUWE_MAX);

	INIT_WOWK(&smu->thwottwing_wogging_wowk, smu_thwottwing_wogging_wowk_fn);
	INIT_WOWK(&smu->intewwupt_wowk, smu_intewwupt_wowk_fn);
	atomic64_set(&smu->thwottwe_int_countew, 0);
	smu->watewmawks_bitmap = 0;
	smu->powew_pwofiwe_mode = PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT;
	smu->defauwt_powew_pwofiwe_mode = PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT;

	atomic_set(&smu->smu_powew.powew_gate.vcn_gated, 1);
	atomic_set(&smu->smu_powew.powew_gate.jpeg_gated, 1);
	atomic_set(&smu->smu_powew.powew_gate.vpe_gated, 1);
	atomic_set(&smu->smu_powew.powew_gate.umsch_mm_gated, 1);

	smu->wowkwoad_mask = 1 << smu->wowkwoad_pwowity[PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT];
	smu->wowkwoad_pwowity[PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT] = 0;
	smu->wowkwoad_pwowity[PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D] = 1;
	smu->wowkwoad_pwowity[PP_SMC_POWEW_PWOFIWE_POWEWSAVING] = 2;
	smu->wowkwoad_pwowity[PP_SMC_POWEW_PWOFIWE_VIDEO] = 3;
	smu->wowkwoad_pwowity[PP_SMC_POWEW_PWOFIWE_VW] = 4;
	smu->wowkwoad_pwowity[PP_SMC_POWEW_PWOFIWE_COMPUTE] = 5;
	smu->wowkwoad_pwowity[PP_SMC_POWEW_PWOFIWE_CUSTOM] = 6;

	smu->wowkwoad_setting[0] = PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT;
	smu->wowkwoad_setting[1] = PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D;
	smu->wowkwoad_setting[2] = PP_SMC_POWEW_PWOFIWE_POWEWSAVING;
	smu->wowkwoad_setting[3] = PP_SMC_POWEW_PWOFIWE_VIDEO;
	smu->wowkwoad_setting[4] = PP_SMC_POWEW_PWOFIWE_VW;
	smu->wowkwoad_setting[5] = PP_SMC_POWEW_PWOFIWE_COMPUTE;
	smu->wowkwoad_setting[6] = PP_SMC_POWEW_PWOFIWE_CUSTOM;
	smu->dispway_config = &adev->pm.pm_dispway_cfg;

	smu->smu_dpm.dpm_wevew = AMD_DPM_FOWCED_WEVEW_AUTO;
	smu->smu_dpm.wequested_dpm_wevew = AMD_DPM_FOWCED_WEVEW_AUTO;

	INIT_DEWAYED_WOWK(&smu->swctf_dewayed_wowk,
			  smu_swctf_dewayed_wowk_handwew);

	wet = smu_smc_tabwe_sw_init(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to sw init smc tabwe!\n");
		wetuwn wet;
	}

	/* get boot_vawues fwom vbios to set wevision, gfxcwk, and etc. */
	wet = smu_get_vbios_bootup_vawues(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to get VBIOS boot cwock vawues!\n");
		wetuwn wet;
	}

	wet = smu_init_pptabwe_micwocode(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to setup pptabwe fiwmwawe!\n");
		wetuwn wet;
	}

	wet = smu_wegistew_iwq_handwew(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to wegistew smc iwq handwew!\n");
		wetuwn wet;
	}

	/* If thewe is no way to quewy fan contwow mode, fan contwow is not suppowted */
	if (!smu->ppt_funcs->get_fan_contwow_mode)
		smu->adev->pm.no_fan = twue;

	wetuwn 0;
}

static int smu_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet;

	wet = smu_smc_tabwe_sw_fini(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to sw fini smc tabwe!\n");
		wetuwn wet;
	}

	smu_fini_micwocode(smu);

	wetuwn 0;
}

static int smu_get_thewmaw_tempewatuwe_wange(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct smu_tempewatuwe_wange *wange =
				&smu->thewmaw_wange;
	int wet = 0;

	if (!smu->ppt_funcs->get_thewmaw_tempewatuwe_wange)
		wetuwn 0;

	wet = smu->ppt_funcs->get_thewmaw_tempewatuwe_wange(smu, wange);
	if (wet)
		wetuwn wet;

	adev->pm.dpm.thewmaw.min_temp = wange->min;
	adev->pm.dpm.thewmaw.max_temp = wange->max;
	adev->pm.dpm.thewmaw.max_edge_emewgency_temp = wange->edge_emewgency_max;
	adev->pm.dpm.thewmaw.min_hotspot_temp = wange->hotspot_min;
	adev->pm.dpm.thewmaw.max_hotspot_cwit_temp = wange->hotspot_cwit_max;
	adev->pm.dpm.thewmaw.max_hotspot_emewgency_temp = wange->hotspot_emewgency_max;
	adev->pm.dpm.thewmaw.min_mem_temp = wange->mem_min;
	adev->pm.dpm.thewmaw.max_mem_cwit_temp = wange->mem_cwit_max;
	adev->pm.dpm.thewmaw.max_mem_emewgency_temp = wange->mem_emewgency_max;

	wetuwn wet;
}

/**
 * smu_wbwf_handwe_excwusion_wanges - consume the wbwf excwusion wanges
 *
 * @smu: smu_context pointew
 *
 * Wetwieve the wbwf excwusion wanges and send them to PMFW fow pwopew handwing.
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int smu_wbwf_handwe_excwusion_wanges(stwuct smu_context *smu)
{
	stwuct wbwf_wanges_in_out wbwf_excwusion = {0};
	stwuct fweq_band_wange *wifi_bands = wbwf_excwusion.band_wist;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t num_of_wbwf_wanges = MAX_NUM_OF_WBWF_WANGES;
	uint64_t stawt, end;
	int wet, i, j;

	wet = amd_wbwf_wetwieve_fweq_band(adev->dev, &wbwf_excwusion);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to wetwieve excwusion wanges!\n");
		wetuwn wet;
	}

	/*
	 * The excwusion wanges awway we got might be fiwwed with howes and dupwicate
	 * entwies. Fow exampwe:
	 * {(2400, 2500), (0, 0), (6882, 6962), (2400, 2500), (0, 0), (6117, 6189), (0, 0)...}
	 * We need to do some sowtups to ewiminate those howes and dupwicate entwies.
	 * Expected output: {(2400, 2500), (6117, 6189), (6882, 6962), (0, 0)...}
	 */
	fow (i = 0; i < num_of_wbwf_wanges; i++) {
		stawt = wifi_bands[i].stawt;
		end = wifi_bands[i].end;

		/* get the wast vawid entwy to fiww the intewmediate howe */
		if (!stawt && !end) {
			fow (j = num_of_wbwf_wanges - 1; j > i; j--)
				if (wifi_bands[j].stawt && wifi_bands[j].end)
					bweak;

			/* no vawid entwy weft */
			if (j <= i)
				bweak;

			stawt = wifi_bands[i].stawt = wifi_bands[j].stawt;
			end = wifi_bands[i].end = wifi_bands[j].end;
			wifi_bands[j].stawt = 0;
			wifi_bands[j].end = 0;
			num_of_wbwf_wanges = j;
		}

		/* ewiminate dupwicate entwies */
		fow (j = i + 1; j < num_of_wbwf_wanges; j++) {
			if ((wifi_bands[j].stawt == stawt) && (wifi_bands[j].end == end)) {
				wifi_bands[j].stawt = 0;
				wifi_bands[j].end = 0;
			}
		}
	}

	/* Send the sowted wifi_bands to PMFW */
	wet = smu_set_wbwf_excwusion_wanges(smu, wifi_bands);
	/* Twy to set the wifi_bands again */
	if (unwikewy(wet == -EBUSY)) {
		mdeway(5);
		wet = smu_set_wbwf_excwusion_wanges(smu, wifi_bands);
	}

	wetuwn wet;
}

/**
 * smu_wbwf_event_handwew - handwe notify events
 *
 * @nb: notifiew bwock
 * @action: event type
 * @_awg: event data
 *
 * Cawws wewevant amdgpu function in wesponse to wbwf event
 * notification fwom kewnew.
 */
static int smu_wbwf_event_handwew(stwuct notifiew_bwock *nb,
				  unsigned wong action, void *_awg)
{
	stwuct smu_context *smu = containew_of(nb, stwuct smu_context, wbwf_notifiew);

	switch (action) {
	case WBWF_CHANGED:
		scheduwe_dewayed_wowk(&smu->wbwf_dewayed_wowk,
				      msecs_to_jiffies(SMU_WBWF_EVENT_HANDWING_PACE));
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_OK;
}

/**
 * smu_wbwf_dewayed_wowk_handwew - cawwback on dewayed wowk timew expiwed
 *
 * @wowk: stwuct wowk_stwuct pointew
 *
 * Fwood is ovew and dwivew wiww consume the watest excwusion wanges.
 */
static void smu_wbwf_dewayed_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct smu_context *smu = containew_of(wowk, stwuct smu_context, wbwf_dewayed_wowk.wowk);

	smu_wbwf_handwe_excwusion_wanges(smu);
}

/**
 * smu_wbwf_suppowt_check - check wbwf suppowt
 *
 * @smu: smu_context pointew
 *
 * Vewifies the ACPI intewface whethew wbwf is suppowted.
 */
static void smu_wbwf_suppowt_check(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	smu->wbwf_suppowted = smu_is_asic_wbwf_suppowted(smu) && amdgpu_wbwf &&
							acpi_amd_wbwf_suppowted_consumew(adev->dev);

	if (smu->wbwf_suppowted)
		dev_info(adev->dev, "WF intewfewence mitigation is suppowted\n");
}

/**
 * smu_wbwf_init - init dwivew wbwf suppowt
 *
 * @smu: smu_context pointew
 *
 * Vewifies the AMD ACPI intewfaces and wegistews with the wbwf
 * notifiew chain if wbwf featuwe is suppowted.
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int smu_wbwf_init(stwuct smu_context *smu)
{
	int wet;

	if (!smu->wbwf_suppowted)
		wetuwn 0;

	INIT_DEWAYED_WOWK(&smu->wbwf_dewayed_wowk, smu_wbwf_dewayed_wowk_handwew);

	smu->wbwf_notifiew.notifiew_caww = smu_wbwf_event_handwew;
	wet = amd_wbwf_wegistew_notifiew(&smu->wbwf_notifiew);
	if (wet)
		wetuwn wet;

	/*
	 * Some wifiband excwusion wanges may be awweady thewe
	 * befowe ouw dwivew woaded. To make suwe ouw dwivew
	 * is awawed of those excwusion wanges.
	 */
	scheduwe_dewayed_wowk(&smu->wbwf_dewayed_wowk,
			      msecs_to_jiffies(SMU_WBWF_EVENT_HANDWING_PACE));

	wetuwn 0;
}

/**
 * smu_wbwf_fini - teaw down dwivew wbwf suppowt
 *
 * @smu: smu_context pointew
 *
 * Unwegistews with the wbwf notifiew chain.
 */
static void smu_wbwf_fini(stwuct smu_context *smu)
{
	if (!smu->wbwf_suppowted)
		wetuwn;

	amd_wbwf_unwegistew_notifiew(&smu->wbwf_notifiew);

	cancew_dewayed_wowk_sync(&smu->wbwf_dewayed_wowk);
}

static int smu_smc_hw_setup(stwuct smu_context *smu)
{
	stwuct smu_featuwe *featuwe = &smu->smu_featuwe;
	stwuct amdgpu_device *adev = smu->adev;
	uint8_t pcie_gen = 0, pcie_width = 0;
	uint64_t featuwes_suppowted;
	int wet = 0;

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(11, 0, 7):
	case IP_VEWSION(11, 0, 11):
	case IP_VEWSION(11, 5, 0):
	case IP_VEWSION(11, 0, 12):
		if (adev->in_suspend && smu_is_dpm_wunning(smu)) {
			dev_info(adev->dev, "dpm has been enabwed\n");
			wet = smu_system_featuwes_contwow(smu, twue);
			if (wet)
				dev_eww(adev->dev, "Faiwed system featuwes contwow!\n");
			wetuwn wet;
		}
		bweak;
	defauwt:
		bweak;
	}

	wet = smu_init_dispway_count(smu, 0);
	if (wet) {
		dev_info(adev->dev, "Faiwed to pwe-set dispway count as 0!\n");
		wetuwn wet;
	}

	wet = smu_set_dwivew_tabwe_wocation(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to SetDwivewDwamAddw!\n");
		wetuwn wet;
	}

	/*
	 * Set PMSTATUSWOG tabwe bo addwess with SetToowsDwamAddw MSG fow toows.
	 */
	wet = smu_set_toow_tabwe_wocation(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to SetToowsDwamAddw!\n");
		wetuwn wet;
	}

	/*
	 * Use msg SetSystemViwtuawDwamAddw and DwamWogSetDwamAddw can notify
	 * poow wocation.
	 */
	wet = smu_notify_memowy_poow_wocation(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to SetDwamWogDwamAddw!\n");
		wetuwn wet;
	}

	/*
	 * It is assumed the pptabwe used befowe wunpm is same as
	 * the one used aftewwawds. Thus, we can weuse the stowed
	 * copy and do not need to wesetup the pptabwe again.
	 */
	if (!adev->in_wunpm) {
		wet = smu_setup_pptabwe(smu);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to setup pptabwe!\n");
			wetuwn wet;
		}
	}

	/* smu_dump_pptabwe(smu); */

	/*
	 * With SCPM enabwed, PSP is wesponsibwe fow the PPTabwe twansfewwing
	 * (to SMU). Dwivew invowvement is not needed and pewmitted.
	 */
	if (!adev->scpm_enabwed) {
		/*
		 * Copy pptabwe bo in the vwam to smc with SMU MSGs such as
		 * SetDwivewDwamAddw and TwansfewTabweDwam2Smu.
		 */
		wet = smu_wwite_pptabwe(smu);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to twansfew pptabwe to SMC!\n");
			wetuwn wet;
		}
	}

	/* issue Wun*Btc msg */
	wet = smu_wun_btc(smu);
	if (wet)
		wetuwn wet;

	/* Enabwe UcwkShadow on wbwf suppowted */
	if (smu->wbwf_suppowted) {
		wet = smu_enabwe_ucwk_shadow(smu, twue);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to enabwe UcwkShadow featuwe to suppowt wbwf!\n");
			wetuwn wet;
		}
	}

	/*
	 * With SCPM enabwed, these actions(and wewevant messages) awe
	 * not needed and pewmitted.
	 */
	if (!adev->scpm_enabwed) {
		wet = smu_featuwe_set_awwowed_mask(smu);
		if (wet) {
			dev_eww(adev->dev, "Faiwed to set dwivew awwowed featuwes mask!\n");
			wetuwn wet;
		}
	}

	wet = smu_system_featuwes_contwow(smu, twue);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to enabwe wequested dpm featuwes!\n");
		wetuwn wet;
	}

	smu_init_xgmi_pwpd_mode(smu);

	wet = smu_featuwe_get_enabwed_mask(smu, &featuwes_suppowted);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to wetwieve suppowted dpm featuwes!\n");
		wetuwn wet;
	}
	bitmap_copy(featuwe->suppowted,
		    (unsigned wong *)&featuwes_suppowted,
		    featuwe->featuwe_num);

	if (!smu_is_dpm_wunning(smu))
		dev_info(adev->dev, "dpm has been disabwed\n");

	/*
	 * Set initiawized vawues (get fwom vbios) to dpm tabwes context such as
	 * gfxcwk, memcwk, dcefcwk, and etc. And enabwe the DPM featuwe fow each
	 * type of cwks.
	 */
	wet = smu_set_defauwt_dpm_tabwe(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to setup defauwt dpm cwock tabwes!\n");
		wetuwn wet;
	}

	if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN4)
		pcie_gen = 3;
	ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3)
		pcie_gen = 2;
	ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2)
		pcie_gen = 1;
	ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1)
		pcie_gen = 0;

	/* Bit 31:16: WCWK DPM wevew. 0 is DPM0, and 1 is DPM1
	 * Bit 15:8:  PCIE GEN, 0 to 3 cowwesponds to GEN1 to GEN4
	 * Bit 7:0:   PCIE wane width, 1 to 7 cowwesponds is x1 to x32
	 */
	if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X16)
		pcie_width = 6;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X12)
		pcie_width = 5;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8)
		pcie_width = 4;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4)
		pcie_width = 3;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2)
		pcie_width = 2;
	ewse if (adev->pm.pcie_mww_mask & CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1)
		pcie_width = 1;
	wet = smu_update_pcie_pawametews(smu, pcie_gen, pcie_width);
	if (wet) {
		dev_eww(adev->dev, "Attempt to ovewwide pcie pawams faiwed!\n");
		wetuwn wet;
	}

	wet = smu_get_thewmaw_tempewatuwe_wange(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to get thewmaw tempewatuwe wanges!\n");
		wetuwn wet;
	}

	wet = smu_enabwe_thewmaw_awewt(smu);
	if (wet) {
	  dev_eww(adev->dev, "Faiwed to enabwe thewmaw awewt!\n");
	  wetuwn wet;
	}

	wet = smu_notify_dispway_change(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to notify dispway change!\n");
		wetuwn wet;
	}

	/*
	 * Set min deep sweep dce fcwk with bootup vawue fwom vbios via
	 * SetMinDeepSweepDcefcwk MSG.
	 */
	wet = smu_set_min_dcef_deep_sweep(smu,
					  smu->smu_tabwe.boot_vawues.dcefcwk / 100);
	if (wet) {
		dev_eww(adev->dev, "Ewwow setting min deepsweep dcefcwk\n");
		wetuwn wet;
	}

	/* Init wbwf suppowt. Pwopewwy setup the notifiew */
	wet = smu_wbwf_init(smu);
	if (wet)
		dev_eww(adev->dev, "Ewwow duwing wbwf init caww\n");

	wetuwn wet;
}

static int smu_stawt_smc_engine(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP) {
		if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) < IP_VEWSION(11, 0, 0)) {
			if (smu->ppt_funcs->woad_micwocode) {
				wet = smu->ppt_funcs->woad_micwocode(smu);
				if (wet)
					wetuwn wet;
			}
		}
	}

	if (smu->ppt_funcs->check_fw_status) {
		wet = smu->ppt_funcs->check_fw_status(smu);
		if (wet) {
			dev_eww(adev->dev, "SMC is not weady\n");
			wetuwn wet;
		}
	}

	/*
	 * Send msg GetDwivewIfVewsion to check if the wetuwn vawue is equaw
	 * with DWIVEW_IF_VEWSION of smc headew.
	 */
	wet = smu_check_fw_vewsion(smu);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static int smu_hw_init(void *handwe)
{
	int wet;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;

	if (amdgpu_swiov_vf(adev) && !amdgpu_swiov_is_pp_one_vf(adev)) {
		smu->pm_enabwed = fawse;
		wetuwn 0;
	}

	wet = smu_stawt_smc_engine(smu);
	if (wet) {
		dev_eww(adev->dev, "SMC engine is not cowwectwy up!\n");
		wetuwn wet;
	}

	/*
	 * Check whethew wbwf is suppowted. This needs to be done
	 * befowe SMU setup stawts since pawt of SMU configuwation
	 * wewies on this.
	 */
	smu_wbwf_suppowt_check(smu);

	if (smu->is_apu) {
		wet = smu_set_gfx_imu_enabwe(smu);
		if (wet)
			wetuwn wet;
		smu_dpm_set_vcn_enabwe(smu, twue);
		smu_dpm_set_jpeg_enabwe(smu, twue);
		smu_dpm_set_vpe_enabwe(smu, twue);
		smu_dpm_set_umsch_mm_enabwe(smu, twue);
		smu_set_gfx_cgpg(smu, twue);
	}

	if (!smu->pm_enabwed)
		wetuwn 0;

	wet = smu_get_dwivew_awwowed_featuwe_mask(smu);
	if (wet)
		wetuwn wet;

	wet = smu_smc_hw_setup(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to setup smc hw!\n");
		wetuwn wet;
	}

	/*
	 * Move maximum sustainabwe cwock wetwieving hewe considewing
	 * 1. It is not needed on wesume(fwom S3).
	 * 2. DAW settings come between .hw_init and .wate_init of SMU.
	 *    And DAW needs to know the maximum sustainabwe cwocks. Thus
	 *    it cannot be put in .wate_init().
	 */
	wet = smu_init_max_sustainabwe_cwocks(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to init max sustainabwe cwocks!\n");
		wetuwn wet;
	}

	adev->pm.dpm_enabwed = twue;

	dev_info(adev->dev, "SMU is initiawized successfuwwy!\n");

	wetuwn 0;
}

static int smu_disabwe_dpms(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;
	boow use_baco = !smu->is_apu &&
		((amdgpu_in_weset(adev) &&
		  (amdgpu_asic_weset_method(adev) == AMD_WESET_METHOD_BACO)) ||
		 ((adev->in_wunpm || adev->in_s4) && amdgpu_asic_suppowts_baco(adev)));

	/*
	 * Fow SMU 13.0.0 and 13.0.7, PMFW wiww handwe the DPM featuwes(disabwement ow othews)
	 * pwopewwy on suspend/weset/unwoad. Dwivew invowvement may cause some unexpected issues.
	 */
	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(13, 0, 0):
	case IP_VEWSION(13, 0, 7):
	case IP_VEWSION(13, 0, 10):
		wetuwn 0;
	defauwt:
		bweak;
	}

	/*
	 * Fow custom pptabwe upwoading, skip the DPM featuwes
	 * disabwe pwocess on Navi1x ASICs.
	 *   - As the gfx wewated featuwes awe undew contwow of
	 *     WWC on those ASICs. WWC weinitiawization wiww be
	 *     needed to weenabwe them. That wiww cost much mowe
	 *     effowts.
	 *
	 *   - SMU fiwmwawe can handwe the DPM weenabwement
	 *     pwopewwy.
	 */
	if (smu->upwoading_custom_pp_tabwe) {
		switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
		case IP_VEWSION(11, 0, 0):
		case IP_VEWSION(11, 0, 5):
		case IP_VEWSION(11, 0, 9):
		case IP_VEWSION(11, 0, 7):
		case IP_VEWSION(11, 0, 11):
		case IP_VEWSION(11, 5, 0):
		case IP_VEWSION(11, 0, 12):
		case IP_VEWSION(11, 0, 13):
			wetuwn 0;
		defauwt:
			bweak;
		}
	}

	/*
	 * Fow Sienna_Cichwid, PMFW wiww handwe the featuwes disabwement pwopewwy
	 * on BACO in. Dwivew invowvement is unnecessawy.
	 */
	if (use_baco) {
		switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
		case IP_VEWSION(11, 0, 7):
		case IP_VEWSION(11, 0, 0):
		case IP_VEWSION(11, 0, 5):
		case IP_VEWSION(11, 0, 9):
		case IP_VEWSION(13, 0, 7):
			wetuwn 0;
		defauwt:
			bweak;
		}
	}

	/*
	 * Fow SMU 13.0.4/11 and 14.0.0, PMFW wiww handwe the featuwes disabwement pwopewwy
	 * fow gpu weset and S0i3 cases. Dwivew invowvement is unnecessawy.
	 */
	if (amdgpu_in_weset(adev) || adev->in_s0ix) {
		switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
		case IP_VEWSION(13, 0, 4):
		case IP_VEWSION(13, 0, 11):
		case IP_VEWSION(14, 0, 0):
			wetuwn 0;
		defauwt:
			bweak;
		}
	}

	/*
	 * Fow gpu weset, wunpm and hibewnation thwough BACO,
	 * BACO featuwe has to be kept enabwed.
	 */
	if (use_baco && smu_featuwe_is_enabwed(smu, SMU_FEATUWE_BACO_BIT)) {
		wet = smu_disabwe_aww_featuwes_with_exception(smu,
							      SMU_FEATUWE_BACO_BIT);
		if (wet)
			dev_eww(adev->dev, "Faiwed to disabwe smu featuwes except BACO.\n");
	} ewse {
		/* DisabweAwwSmuFeatuwes message is not pewmitted with SCPM enabwed */
		if (!adev->scpm_enabwed) {
			wet = smu_system_featuwes_contwow(smu, fawse);
			if (wet)
				dev_eww(adev->dev, "Faiwed to disabwe smu featuwes.\n");
		}
	}

	/* Notify SMU WWC is going to be off, stop WWC and SMU intewaction.
	 * othewwise SMU wiww hang whiwe intewacting with WWC if WWC is hawted
	 * this is a WA fow Vangogh asic which fix the SMU hang issue.
	 */
	wet = smu_notify_wwc_state(smu, fawse);
	if (wet) {
		dev_eww(adev->dev, "Faiw to notify wwc status!\n");
		wetuwn wet;
	}

	if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) >= IP_VEWSION(9, 4, 2) &&
	    !((adev->fwags & AMD_IS_APU) && adev->gfx.imu.funcs) &&
	    !amdgpu_swiov_vf(adev) && adev->gfx.wwc.funcs->stop)
		adev->gfx.wwc.funcs->stop(adev);

	wetuwn wet;
}

static int smu_smc_hw_cweanup(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	smu_wbwf_fini(smu);

	cancew_wowk_sync(&smu->thwottwing_wogging_wowk);
	cancew_wowk_sync(&smu->intewwupt_wowk);

	wet = smu_disabwe_thewmaw_awewt(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiw to disabwe thewmaw awewt!\n");
		wetuwn wet;
	}

	cancew_dewayed_wowk_sync(&smu->swctf_dewayed_wowk);

	wet = smu_disabwe_dpms(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiw to disabwe dpm featuwes!\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int smu_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;

	if (amdgpu_swiov_vf(adev) && !amdgpu_swiov_is_pp_one_vf(adev))
		wetuwn 0;

	smu_dpm_set_vcn_enabwe(smu, fawse);
	smu_dpm_set_jpeg_enabwe(smu, fawse);
	smu_dpm_set_vpe_enabwe(smu, fawse);
	smu_dpm_set_umsch_mm_enabwe(smu, fawse);

	adev->vcn.cuw_state = AMD_PG_STATE_GATE;
	adev->jpeg.cuw_state = AMD_PG_STATE_GATE;

	if (!smu->pm_enabwed)
		wetuwn 0;

	adev->pm.dpm_enabwed = fawse;

	wetuwn smu_smc_hw_cweanup(smu);
}

static void smu_wate_fini(void *handwe)
{
	stwuct amdgpu_device *adev = handwe;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;

	kfwee(smu);
}

static int smu_weset(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet;

	wet = smu_hw_fini(adev);
	if (wet)
		wetuwn wet;

	wet = smu_hw_init(adev);
	if (wet)
		wetuwn wet;

	wet = smu_wate_init(adev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int smu_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet;
	uint64_t count;

	if (amdgpu_swiov_vf(adev) && !amdgpu_swiov_is_pp_one_vf(adev))
		wetuwn 0;

	if (!smu->pm_enabwed)
		wetuwn 0;

	adev->pm.dpm_enabwed = fawse;

	wet = smu_smc_hw_cweanup(smu);
	if (wet)
		wetuwn wet;

	smu->watewmawks_bitmap &= ~(WATEWMAWKS_WOADED);

	smu_set_gfx_cgpg(smu, fawse);

	/*
	 * pwfw wesets entwycount when device is suspended, so we save the
	 * wast vawue to be used when we wesume to keep it consistent
	 */
	wet = smu_get_entwycount_gfxoff(smu, &count);
	if (!wet)
		adev->gfx.gfx_off_entwycount = count;

	wetuwn 0;
}

static int smu_wesume(void *handwe)
{
	int wet;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;

	if (amdgpu_swiov_vf(adev)&& !amdgpu_swiov_is_pp_one_vf(adev))
		wetuwn 0;

	if (!smu->pm_enabwed)
		wetuwn 0;

	dev_info(adev->dev, "SMU is wesuming...\n");

	wet = smu_stawt_smc_engine(smu);
	if (wet) {
		dev_eww(adev->dev, "SMC engine is not cowwectwy up!\n");
		wetuwn wet;
	}

	wet = smu_smc_hw_setup(smu);
	if (wet) {
		dev_eww(adev->dev, "Faiwed to setup smc hw!\n");
		wetuwn wet;
	}

	wet = smu_set_gfx_imu_enabwe(smu);
	if (wet)
		wetuwn wet;

	smu_set_gfx_cgpg(smu, twue);

	smu->disabwe_ucwk_switch = 0;

	adev->pm.dpm_enabwed = twue;

	dev_info(adev->dev, "SMU is wesumed successfuwwy!\n");

	wetuwn 0;
}

static int smu_dispway_configuwation_change(void *handwe,
					    const stwuct amd_pp_dispway_configuwation *dispway_config)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!dispway_config)
		wetuwn -EINVAW;

	smu_set_min_dcef_deep_sweep(smu,
				    dispway_config->min_dcef_deep_sweep_set_cwk / 100);

	wetuwn 0;
}

static int smu_set_cwockgating_state(void *handwe,
				     enum amd_cwockgating_state state)
{
	wetuwn 0;
}

static int smu_set_powewgating_state(void *handwe,
				     enum amd_powewgating_state state)
{
	wetuwn 0;
}

static int smu_enabwe_umd_pstate(void *handwe,
		      enum amd_dpm_fowced_wevew *wevew)
{
	uint32_t pwofiwe_mode_mask = AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK |
					AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK;

	stwuct smu_context *smu = (stwuct smu_context*)(handwe);
	stwuct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);

	if (!smu->is_apu && !smu_dpm_ctx->dpm_context)
		wetuwn -EINVAW;

	if (!(smu_dpm_ctx->dpm_wevew & pwofiwe_mode_mask)) {
		/* entew umd pstate, save cuwwent wevew, disabwe gfx cg*/
		if (*wevew & pwofiwe_mode_mask) {
			smu_dpm_ctx->saved_dpm_wevew = smu_dpm_ctx->dpm_wevew;
			smu_gpo_contwow(smu, fawse);
			smu_gfx_uwv_contwow(smu, fawse);
			smu_deep_sweep_contwow(smu, fawse);
			amdgpu_asic_update_umd_stabwe_pstate(smu->adev, twue);
		}
	} ewse {
		/* exit umd pstate, westowe wevew, enabwe gfx cg*/
		if (!(*wevew & pwofiwe_mode_mask)) {
			if (*wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT)
				*wevew = smu_dpm_ctx->saved_dpm_wevew;
			amdgpu_asic_update_umd_stabwe_pstate(smu->adev, fawse);
			smu_deep_sweep_contwow(smu, twue);
			smu_gfx_uwv_contwow(smu, twue);
			smu_gpo_contwow(smu, twue);
		}
	}

	wetuwn 0;
}

static int smu_bump_powew_pwofiwe_mode(stwuct smu_context *smu,
					   wong *pawam,
					   uint32_t pawam_size)
{
	int wet = 0;

	if (smu->ppt_funcs->set_powew_pwofiwe_mode)
		wet = smu->ppt_funcs->set_powew_pwofiwe_mode(smu, pawam, pawam_size);

	wetuwn wet;
}

static int smu_adjust_powew_state_dynamic(stwuct smu_context *smu,
				   enum amd_dpm_fowced_wevew wevew,
				   boow skip_dispway_settings)
{
	int wet = 0;
	int index = 0;
	wong wowkwoad;
	stwuct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);

	if (!skip_dispway_settings) {
		wet = smu_dispway_config_changed(smu);
		if (wet) {
			dev_eww(smu->adev->dev, "Faiwed to change dispway config!");
			wetuwn wet;
		}
	}

	wet = smu_appwy_cwocks_adjust_wuwes(smu);
	if (wet) {
		dev_eww(smu->adev->dev, "Faiwed to appwy cwocks adjust wuwes!");
		wetuwn wet;
	}

	if (!skip_dispway_settings) {
		wet = smu_notify_smc_dispway_config(smu);
		if (wet) {
			dev_eww(smu->adev->dev, "Faiwed to notify smc dispway config!");
			wetuwn wet;
		}
	}

	if (smu_dpm_ctx->dpm_wevew != wevew) {
		wet = smu_asic_set_pewfowmance_wevew(smu, wevew);
		if (wet) {
			dev_eww(smu->adev->dev, "Faiwed to set pewfowmance wevew!");
			wetuwn wet;
		}

		/* update the saved copy */
		smu_dpm_ctx->dpm_wevew = wevew;
	}

	if (smu_dpm_ctx->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW &&
		smu_dpm_ctx->dpm_wevew != AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM) {
		index = fws(smu->wowkwoad_mask);
		index = index > 0 && index <= WOWKWOAD_POWICY_MAX ? index - 1 : 0;
		wowkwoad = smu->wowkwoad_setting[index];

		if (smu->powew_pwofiwe_mode != wowkwoad)
			smu_bump_powew_pwofiwe_mode(smu, &wowkwoad, 0);
	}

	wetuwn wet;
}

static int smu_handwe_task(stwuct smu_context *smu,
			   enum amd_dpm_fowced_wevew wevew,
			   enum amd_pp_task task_id)
{
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	switch (task_id) {
	case AMD_PP_TASK_DISPWAY_CONFIG_CHANGE:
		wet = smu_pwe_dispway_config_changed(smu);
		if (wet)
			wetuwn wet;
		wet = smu_adjust_powew_state_dynamic(smu, wevew, fawse);
		bweak;
	case AMD_PP_TASK_COMPWETE_INIT:
	case AMD_PP_TASK_WEADJUST_POWEW_STATE:
		wet = smu_adjust_powew_state_dynamic(smu, wevew, twue);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int smu_handwe_dpm_task(void *handwe,
			       enum amd_pp_task task_id,
			       enum amd_pm_state_type *usew_state)
{
	stwuct smu_context *smu = handwe;
	stwuct smu_dpm_context *smu_dpm = &smu->smu_dpm;

	wetuwn smu_handwe_task(smu, smu_dpm->dpm_wevew, task_id);

}

static int smu_switch_powew_pwofiwe(void *handwe,
				    enum PP_SMC_POWEW_PWOFIWE type,
				    boow en)
{
	stwuct smu_context *smu = handwe;
	stwuct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	wong wowkwoad;
	uint32_t index;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!(type < PP_SMC_POWEW_PWOFIWE_CUSTOM))
		wetuwn -EINVAW;

	if (!en) {
		smu->wowkwoad_mask &= ~(1 << smu->wowkwoad_pwowity[type]);
		index = fws(smu->wowkwoad_mask);
		index = index > 0 && index <= WOWKWOAD_POWICY_MAX ? index - 1 : 0;
		wowkwoad = smu->wowkwoad_setting[index];
	} ewse {
		smu->wowkwoad_mask |= (1 << smu->wowkwoad_pwowity[type]);
		index = fws(smu->wowkwoad_mask);
		index = index <= WOWKWOAD_POWICY_MAX ? index - 1 : 0;
		wowkwoad = smu->wowkwoad_setting[index];
	}

	if (smu_dpm_ctx->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW &&
		smu_dpm_ctx->dpm_wevew != AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM)
		smu_bump_powew_pwofiwe_mode(smu, &wowkwoad, 0);

	wetuwn 0;
}

static enum amd_dpm_fowced_wevew smu_get_pewfowmance_wevew(void *handwe)
{
	stwuct smu_context *smu = handwe;
	stwuct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->is_apu && !smu_dpm_ctx->dpm_context)
		wetuwn -EINVAW;

	wetuwn smu_dpm_ctx->dpm_wevew;
}

static int smu_fowce_pewfowmance_wevew(void *handwe,
				       enum amd_dpm_fowced_wevew wevew)
{
	stwuct smu_context *smu = handwe;
	stwuct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->is_apu && !smu_dpm_ctx->dpm_context)
		wetuwn -EINVAW;

	wet = smu_enabwe_umd_pstate(smu, &wevew);
	if (wet)
		wetuwn wet;

	wet = smu_handwe_task(smu, wevew,
			      AMD_PP_TASK_WEADJUST_POWEW_STATE);

	/* weset usew dpm cwock state */
	if (!wet && smu_dpm_ctx->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW) {
		memset(smu->usew_dpm_pwofiwe.cwk_mask, 0, sizeof(smu->usew_dpm_pwofiwe.cwk_mask));
		smu->usew_dpm_pwofiwe.cwk_dependency = 0;
	}

	wetuwn wet;
}

static int smu_set_dispway_count(void *handwe, uint32_t count)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	wetuwn smu_init_dispway_count(smu, count);
}

static int smu_fowce_smucwk_wevews(stwuct smu_context *smu,
			 enum smu_cwk_type cwk_type,
			 uint32_t mask)
{
	stwuct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu_dpm_ctx->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW) {
		dev_dbg(smu->adev->dev, "fowce cwock wevew is fow dpm manuaw mode onwy.\n");
		wetuwn -EINVAW;
	}

	if (smu->ppt_funcs && smu->ppt_funcs->fowce_cwk_wevews) {
		wet = smu->ppt_funcs->fowce_cwk_wevews(smu, cwk_type, mask);
		if (!wet && !(smu->usew_dpm_pwofiwe.fwags & SMU_DPM_USEW_PWOFIWE_WESTOWE)) {
			smu->usew_dpm_pwofiwe.cwk_mask[cwk_type] = mask;
			smu_set_usew_cwk_dependencies(smu, cwk_type);
		}
	}

	wetuwn wet;
}

static int smu_fowce_ppcwk_wevews(void *handwe,
				  enum pp_cwock_type type,
				  uint32_t mask)
{
	stwuct smu_context *smu = handwe;
	enum smu_cwk_type cwk_type;

	switch (type) {
	case PP_SCWK:
		cwk_type = SMU_SCWK; bweak;
	case PP_MCWK:
		cwk_type = SMU_MCWK; bweak;
	case PP_PCIE:
		cwk_type = SMU_PCIE; bweak;
	case PP_SOCCWK:
		cwk_type = SMU_SOCCWK; bweak;
	case PP_FCWK:
		cwk_type = SMU_FCWK; bweak;
	case PP_DCEFCWK:
		cwk_type = SMU_DCEFCWK; bweak;
	case PP_VCWK:
		cwk_type = SMU_VCWK; bweak;
	case PP_VCWK1:
		cwk_type = SMU_VCWK1; bweak;
	case PP_DCWK:
		cwk_type = SMU_DCWK; bweak;
	case PP_DCWK1:
		cwk_type = SMU_DCWK1; bweak;
	case OD_SCWK:
		cwk_type = SMU_OD_SCWK; bweak;
	case OD_MCWK:
		cwk_type = SMU_OD_MCWK; bweak;
	case OD_VDDC_CUWVE:
		cwk_type = SMU_OD_VDDC_CUWVE; bweak;
	case OD_WANGE:
		cwk_type = SMU_OD_WANGE; bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn smu_fowce_smucwk_wevews(smu, cwk_type, mask);
}

/*
 * On system suspending ow wesetting, the dpm_enabwed
 * fwag wiww be cweawed. So that those SMU sewvices which
 * awe not suppowted wiww be gated.
 * Howevew, the mp1 state setting shouwd stiww be gwanted
 * even if the dpm_enabwed cweawed.
 */
static int smu_set_mp1_state(void *handwe,
			     enum pp_mp1_state mp1_state)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs &&
	    smu->ppt_funcs->set_mp1_state)
		wet = smu->ppt_funcs->set_mp1_state(smu, mp1_state);

	wetuwn wet;
}

static int smu_set_df_cstate(void *handwe,
			     enum pp_df_cstate state)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->ppt_funcs || !smu->ppt_funcs->set_df_cstate)
		wetuwn 0;

	wet = smu->ppt_funcs->set_df_cstate(smu, state);
	if (wet)
		dev_eww(smu->adev->dev, "[SetDfCstate] faiwed!\n");

	wetuwn wet;
}

int smu_wwite_watewmawks_tabwe(stwuct smu_context *smu)
{
	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	wetuwn smu_set_watewmawks_tabwe(smu, NUWW);
}

static int smu_set_watewmawks_fow_cwock_wanges(void *handwe,
					       stwuct pp_smu_wm_wange_sets *cwock_wanges)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->disabwe_watewmawk)
		wetuwn 0;

	wetuwn smu_set_watewmawks_tabwe(smu, cwock_wanges);
}

int smu_set_ac_dc(stwuct smu_context *smu)
{
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	/* contwowwed by fiwmwawe */
	if (smu->dc_contwowwed_by_gpio)
		wetuwn 0;

	wet = smu_set_powew_souwce(smu,
				   smu->adev->pm.ac_powew ? SMU_POWEW_SOUWCE_AC :
				   SMU_POWEW_SOUWCE_DC);
	if (wet)
		dev_eww(smu->adev->dev, "Faiwed to switch to %s mode!\n",
		       smu->adev->pm.ac_powew ? "AC" : "DC");

	wetuwn wet;
}

const stwuct amd_ip_funcs smu_ip_funcs = {
	.name = "smu",
	.eawwy_init = smu_eawwy_init,
	.wate_init = smu_wate_init,
	.sw_init = smu_sw_init,
	.sw_fini = smu_sw_fini,
	.hw_init = smu_hw_init,
	.hw_fini = smu_hw_fini,
	.wate_fini = smu_wate_fini,
	.suspend = smu_suspend,
	.wesume = smu_wesume,
	.is_idwe = NUWW,
	.check_soft_weset = NUWW,
	.wait_fow_idwe = NUWW,
	.soft_weset = NUWW,
	.set_cwockgating_state = smu_set_cwockgating_state,
	.set_powewgating_state = smu_set_powewgating_state,
};

const stwuct amdgpu_ip_bwock_vewsion smu_v11_0_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_SMC,
	.majow = 11,
	.minow = 0,
	.wev = 0,
	.funcs = &smu_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion smu_v12_0_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_SMC,
	.majow = 12,
	.minow = 0,
	.wev = 0,
	.funcs = &smu_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion smu_v13_0_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_SMC,
	.majow = 13,
	.minow = 0,
	.wev = 0,
	.funcs = &smu_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion smu_v14_0_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_SMC,
	.majow = 14,
	.minow = 0,
	.wev = 0,
	.funcs = &smu_ip_funcs,
};

static int smu_woad_micwocode(void *handwe)
{
	stwuct smu_context *smu = handwe;
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	if (!smu->pm_enabwed)
		wetuwn -EOPNOTSUPP;

	/* This shouwd be used fow non PSP woading */
	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP)
		wetuwn 0;

	if (smu->ppt_funcs->woad_micwocode) {
		wet = smu->ppt_funcs->woad_micwocode(smu);
		if (wet) {
			dev_eww(adev->dev, "Woad micwocode faiwed\n");
			wetuwn wet;
		}
	}

	if (smu->ppt_funcs->check_fw_status) {
		wet = smu->ppt_funcs->check_fw_status(smu);
		if (wet) {
			dev_eww(adev->dev, "SMC is not weady\n");
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int smu_set_gfx_cgpg(stwuct smu_context *smu, boow enabwed)
{
	int wet = 0;

	if (smu->ppt_funcs->set_gfx_cgpg)
		wet = smu->ppt_funcs->set_gfx_cgpg(smu, enabwed);

	wetuwn wet;
}

static int smu_set_fan_speed_wpm(void *handwe, uint32_t speed)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->ppt_funcs->set_fan_speed_wpm)
		wetuwn -EOPNOTSUPP;

	if (speed == U32_MAX)
		wetuwn -EINVAW;

	wet = smu->ppt_funcs->set_fan_speed_wpm(smu, speed);
	if (!wet && !(smu->usew_dpm_pwofiwe.fwags & SMU_DPM_USEW_PWOFIWE_WESTOWE)) {
		smu->usew_dpm_pwofiwe.fwags |= SMU_CUSTOM_FAN_SPEED_WPM;
		smu->usew_dpm_pwofiwe.fan_speed_wpm = speed;

		/* Ovewwide custom PWM setting as they cannot co-exist */
		smu->usew_dpm_pwofiwe.fwags &= ~SMU_CUSTOM_FAN_SPEED_PWM;
		smu->usew_dpm_pwofiwe.fan_speed_pwm = 0;
	}

	wetuwn wet;
}

/**
 * smu_get_powew_wimit - Wequest one of the SMU Powew Wimits
 *
 * @handwe: pointew to smu context
 * @wimit: wequested wimit is wwitten back to this vawiabwe
 * @pp_wimit_wevew: &pp_powew_wimit_wevew which wimit of the powew to wetuwn
 * @pp_powew_type: &pp_powew_type type of powew
 * Wetuwn:  0 on success, <0 on ewwow
 *
 */
int smu_get_powew_wimit(void *handwe,
			uint32_t *wimit,
			enum pp_powew_wimit_wevew pp_wimit_wevew,
			enum pp_powew_type pp_powew_type)
{
	stwuct smu_context *smu = handwe;
	stwuct amdgpu_device *adev = smu->adev;
	enum smu_ppt_wimit_wevew wimit_wevew;
	uint32_t wimit_type;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	switch (pp_powew_type) {
	case PP_PWW_TYPE_SUSTAINED:
		wimit_type = SMU_DEFAUWT_PPT_WIMIT;
		bweak;
	case PP_PWW_TYPE_FAST:
		wimit_type = SMU_FAST_PPT_WIMIT;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	switch (pp_wimit_wevew) {
	case PP_PWW_WIMIT_CUWWENT:
		wimit_wevew = SMU_PPT_WIMIT_CUWWENT;
		bweak;
	case PP_PWW_WIMIT_DEFAUWT:
		wimit_wevew = SMU_PPT_WIMIT_DEFAUWT;
		bweak;
	case PP_PWW_WIMIT_MAX:
		wimit_wevew = SMU_PPT_WIMIT_MAX;
		bweak;
	case PP_PWW_WIMIT_MIN:
		wimit_wevew = SMU_PPT_WIMIT_MIN;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (wimit_type != SMU_DEFAUWT_PPT_WIMIT) {
		if (smu->ppt_funcs->get_ppt_wimit)
			wet = smu->ppt_funcs->get_ppt_wimit(smu, wimit, wimit_type, wimit_wevew);
	} ewse {
		switch (wimit_wevew) {
		case SMU_PPT_WIMIT_CUWWENT:
			switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
			case IP_VEWSION(13, 0, 2):
			case IP_VEWSION(13, 0, 6):
			case IP_VEWSION(11, 0, 7):
			case IP_VEWSION(11, 0, 11):
			case IP_VEWSION(11, 0, 12):
			case IP_VEWSION(11, 0, 13):
				wet = smu_get_asic_powew_wimits(smu,
								&smu->cuwwent_powew_wimit,
								NUWW, NUWW, NUWW);
				bweak;
			defauwt:
				bweak;
			}
			*wimit = smu->cuwwent_powew_wimit;
			bweak;
		case SMU_PPT_WIMIT_DEFAUWT:
			*wimit = smu->defauwt_powew_wimit;
			bweak;
		case SMU_PPT_WIMIT_MAX:
			*wimit = smu->max_powew_wimit;
			bweak;
		case SMU_PPT_WIMIT_MIN:
			*wimit = smu->min_powew_wimit;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn wet;
}

static int smu_set_powew_wimit(void *handwe, uint32_t wimit)
{
	stwuct smu_context *smu = handwe;
	uint32_t wimit_type = wimit >> 24;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	wimit &= (1<<24)-1;
	if (wimit_type != SMU_DEFAUWT_PPT_WIMIT)
		if (smu->ppt_funcs->set_powew_wimit)
			wetuwn smu->ppt_funcs->set_powew_wimit(smu, wimit_type, wimit);

	if ((wimit > smu->max_powew_wimit) || (wimit < smu->min_powew_wimit)) {
		dev_eww(smu->adev->dev,
			"New powew wimit (%d) is out of wange [%d,%d]\n",
			wimit, smu->min_powew_wimit, smu->max_powew_wimit);
		wetuwn -EINVAW;
	}

	if (!wimit)
		wimit = smu->cuwwent_powew_wimit;

	if (smu->ppt_funcs->set_powew_wimit) {
		wet = smu->ppt_funcs->set_powew_wimit(smu, wimit_type, wimit);
		if (!wet && !(smu->usew_dpm_pwofiwe.fwags & SMU_DPM_USEW_PWOFIWE_WESTOWE))
			smu->usew_dpm_pwofiwe.powew_wimit = wimit;
	}

	wetuwn wet;
}

static int smu_pwint_smucwk_wevews(stwuct smu_context *smu, enum smu_cwk_type cwk_type, chaw *buf)
{
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->pwint_cwk_wevews)
		wet = smu->ppt_funcs->pwint_cwk_wevews(smu, cwk_type, buf);

	wetuwn wet;
}

static enum smu_cwk_type smu_convewt_to_smucwk(enum pp_cwock_type type)
{
	enum smu_cwk_type cwk_type;

	switch (type) {
	case PP_SCWK:
		cwk_type = SMU_SCWK; bweak;
	case PP_MCWK:
		cwk_type = SMU_MCWK; bweak;
	case PP_PCIE:
		cwk_type = SMU_PCIE; bweak;
	case PP_SOCCWK:
		cwk_type = SMU_SOCCWK; bweak;
	case PP_FCWK:
		cwk_type = SMU_FCWK; bweak;
	case PP_DCEFCWK:
		cwk_type = SMU_DCEFCWK; bweak;
	case PP_VCWK:
		cwk_type = SMU_VCWK; bweak;
	case PP_VCWK1:
		cwk_type = SMU_VCWK1; bweak;
	case PP_DCWK:
		cwk_type = SMU_DCWK; bweak;
	case PP_DCWK1:
		cwk_type = SMU_DCWK1; bweak;
	case OD_SCWK:
		cwk_type = SMU_OD_SCWK; bweak;
	case OD_MCWK:
		cwk_type = SMU_OD_MCWK; bweak;
	case OD_VDDC_CUWVE:
		cwk_type = SMU_OD_VDDC_CUWVE; bweak;
	case OD_WANGE:
		cwk_type = SMU_OD_WANGE; bweak;
	case OD_VDDGFX_OFFSET:
		cwk_type = SMU_OD_VDDGFX_OFFSET; bweak;
	case OD_CCWK:
		cwk_type = SMU_OD_CCWK; bweak;
	case OD_FAN_CUWVE:
		cwk_type = SMU_OD_FAN_CUWVE; bweak;
	case OD_ACOUSTIC_WIMIT:
		cwk_type = SMU_OD_ACOUSTIC_WIMIT; bweak;
	case OD_ACOUSTIC_TAWGET:
		cwk_type = SMU_OD_ACOUSTIC_TAWGET; bweak;
	case OD_FAN_TAWGET_TEMPEWATUWE:
		cwk_type = SMU_OD_FAN_TAWGET_TEMPEWATUWE; bweak;
	case OD_FAN_MINIMUM_PWM:
		cwk_type = SMU_OD_FAN_MINIMUM_PWM; bweak;
	defauwt:
		cwk_type = SMU_CWK_COUNT; bweak;
	}

	wetuwn cwk_type;
}

static int smu_pwint_ppcwk_wevews(void *handwe,
				  enum pp_cwock_type type,
				  chaw *buf)
{
	stwuct smu_context *smu = handwe;
	enum smu_cwk_type cwk_type;

	cwk_type = smu_convewt_to_smucwk(type);
	if (cwk_type == SMU_CWK_COUNT)
		wetuwn -EINVAW;

	wetuwn smu_pwint_smucwk_wevews(smu, cwk_type, buf);
}

static int smu_emit_ppcwk_wevews(void *handwe, enum pp_cwock_type type, chaw *buf, int *offset)
{
	stwuct smu_context *smu = handwe;
	enum smu_cwk_type cwk_type;

	cwk_type = smu_convewt_to_smucwk(type);
	if (cwk_type == SMU_CWK_COUNT)
		wetuwn -EINVAW;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->ppt_funcs->emit_cwk_wevews)
		wetuwn -ENOENT;

	wetuwn smu->ppt_funcs->emit_cwk_wevews(smu, cwk_type, buf, offset);

}

static int smu_od_edit_dpm_tabwe(void *handwe,
				 enum PP_OD_DPM_TABWE_COMMAND type,
				 wong *input, uint32_t size)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->od_edit_dpm_tabwe) {
		wet = smu->ppt_funcs->od_edit_dpm_tabwe(smu, type, input, size);
	}

	wetuwn wet;
}

static int smu_wead_sensow(void *handwe,
			   int sensow,
			   void *data,
			   int *size_awg)
{
	stwuct smu_context *smu = handwe;
	stwuct smu_umd_pstate_tabwe *pstate_tabwe =
				&smu->pstate_tabwe;
	int wet = 0;
	uint32_t *size, size_vaw;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!data || !size_awg)
		wetuwn -EINVAW;

	size_vaw = *size_awg;
	size = &size_vaw;

	if (smu->ppt_funcs->wead_sensow)
		if (!smu->ppt_funcs->wead_sensow(smu, sensow, data, size))
			goto unwock;

	switch (sensow) {
	case AMDGPU_PP_SENSOW_STABWE_PSTATE_SCWK:
		*((uint32_t *)data) = pstate_tabwe->gfxcwk_pstate.standawd * 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_STABWE_PSTATE_MCWK:
		*((uint32_t *)data) = pstate_tabwe->ucwk_pstate.standawd * 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_PEAK_PSTATE_SCWK:
		*((uint32_t *)data) = pstate_tabwe->gfxcwk_pstate.peak * 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_PEAK_PSTATE_MCWK:
		*((uint32_t *)data) = pstate_tabwe->ucwk_pstate.peak * 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_ENABWED_SMC_FEATUWES_MASK:
		wet = smu_featuwe_get_enabwed_mask(smu, (uint64_t *)data);
		*size = 8;
		bweak;
	case AMDGPU_PP_SENSOW_UVD_POWEW:
		*(uint32_t *)data = smu_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_UVD_BIT) ? 1 : 0;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VCE_POWEW:
		*(uint32_t *)data = smu_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_VCE_BIT) ? 1 : 0;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VCN_POWEW_STATE:
		*(uint32_t *)data = atomic_wead(&smu->smu_powew.powew_gate.vcn_gated) ? 0 : 1;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_MIN_FAN_WPM:
		*(uint32_t *)data = 0;
		*size = 4;
		bweak;
	defauwt:
		*size = 0;
		wet = -EOPNOTSUPP;
		bweak;
	}

unwock:
	// assign uint32_t to int
	*size_awg = size_vaw;

	wetuwn wet;
}

static int smu_get_apu_thewmaw_wimit(void *handwe, uint32_t *wimit)
{
	int wet = -EOPNOTSUPP;
	stwuct smu_context *smu = handwe;

	if (smu->ppt_funcs && smu->ppt_funcs->get_apu_thewmaw_wimit)
		wet = smu->ppt_funcs->get_apu_thewmaw_wimit(smu, wimit);

	wetuwn wet;
}

static int smu_set_apu_thewmaw_wimit(void *handwe, uint32_t wimit)
{
	int wet = -EOPNOTSUPP;
	stwuct smu_context *smu = handwe;

	if (smu->ppt_funcs && smu->ppt_funcs->set_apu_thewmaw_wimit)
		wet = smu->ppt_funcs->set_apu_thewmaw_wimit(smu, wimit);

	wetuwn wet;
}

static int smu_get_powew_pwofiwe_mode(void *handwe, chaw *buf)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed ||
	    !smu->ppt_funcs->get_powew_pwofiwe_mode)
		wetuwn -EOPNOTSUPP;
	if (!buf)
		wetuwn -EINVAW;

	wetuwn smu->ppt_funcs->get_powew_pwofiwe_mode(smu, buf);
}

static int smu_set_powew_pwofiwe_mode(void *handwe,
				      wong *pawam,
				      uint32_t pawam_size)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed ||
	    !smu->ppt_funcs->set_powew_pwofiwe_mode)
		wetuwn -EOPNOTSUPP;

	wetuwn smu_bump_powew_pwofiwe_mode(smu, pawam, pawam_size);
}

static int smu_get_fan_contwow_mode(void *handwe, u32 *fan_mode)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->ppt_funcs->get_fan_contwow_mode)
		wetuwn -EOPNOTSUPP;

	if (!fan_mode)
		wetuwn -EINVAW;

	*fan_mode = smu->ppt_funcs->get_fan_contwow_mode(smu);

	wetuwn 0;
}

static int smu_set_fan_contwow_mode(void *handwe, u32 vawue)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->ppt_funcs->set_fan_contwow_mode)
		wetuwn -EOPNOTSUPP;

	if (vawue == U32_MAX)
		wetuwn -EINVAW;

	wet = smu->ppt_funcs->set_fan_contwow_mode(smu, vawue);
	if (wet)
		goto out;

	if (!(smu->usew_dpm_pwofiwe.fwags & SMU_DPM_USEW_PWOFIWE_WESTOWE)) {
		smu->usew_dpm_pwofiwe.fan_mode = vawue;

		/* weset usew dpm fan speed */
		if (vawue != AMD_FAN_CTWW_MANUAW) {
			smu->usew_dpm_pwofiwe.fan_speed_pwm = 0;
			smu->usew_dpm_pwofiwe.fan_speed_wpm = 0;
			smu->usew_dpm_pwofiwe.fwags &= ~(SMU_CUSTOM_FAN_SPEED_WPM | SMU_CUSTOM_FAN_SPEED_PWM);
		}
	}

out:
	wetuwn wet;
}

static int smu_get_fan_speed_pwm(void *handwe, u32 *speed)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->ppt_funcs->get_fan_speed_pwm)
		wetuwn -EOPNOTSUPP;

	if (!speed)
		wetuwn -EINVAW;

	wet = smu->ppt_funcs->get_fan_speed_pwm(smu, speed);

	wetuwn wet;
}

static int smu_set_fan_speed_pwm(void *handwe, u32 speed)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->ppt_funcs->set_fan_speed_pwm)
		wetuwn -EOPNOTSUPP;

	if (speed == U32_MAX)
		wetuwn -EINVAW;

	wet = smu->ppt_funcs->set_fan_speed_pwm(smu, speed);
	if (!wet && !(smu->usew_dpm_pwofiwe.fwags & SMU_DPM_USEW_PWOFIWE_WESTOWE)) {
		smu->usew_dpm_pwofiwe.fwags |= SMU_CUSTOM_FAN_SPEED_PWM;
		smu->usew_dpm_pwofiwe.fan_speed_pwm = speed;

		/* Ovewwide custom WPM setting as they cannot co-exist */
		smu->usew_dpm_pwofiwe.fwags &= ~SMU_CUSTOM_FAN_SPEED_WPM;
		smu->usew_dpm_pwofiwe.fan_speed_wpm = 0;
	}

	wetuwn wet;
}

static int smu_get_fan_speed_wpm(void *handwe, uint32_t *speed)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->ppt_funcs->get_fan_speed_wpm)
		wetuwn -EOPNOTSUPP;

	if (!speed)
		wetuwn -EINVAW;

	wet = smu->ppt_funcs->get_fan_speed_wpm(smu, speed);

	wetuwn wet;
}

static int smu_set_deep_sweep_dcefcwk(void *handwe, uint32_t cwk)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	wetuwn smu_set_min_dcef_deep_sweep(smu, cwk);
}

static int smu_get_cwock_by_type_with_watency(void *handwe,
					      enum amd_pp_cwock_type type,
					      stwuct pp_cwock_wevews_with_watency *cwocks)
{
	stwuct smu_context *smu = handwe;
	enum smu_cwk_type cwk_type;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->get_cwock_by_type_with_watency) {
		switch (type) {
		case amd_pp_sys_cwock:
			cwk_type = SMU_GFXCWK;
			bweak;
		case amd_pp_mem_cwock:
			cwk_type = SMU_MCWK;
			bweak;
		case amd_pp_dcef_cwock:
			cwk_type = SMU_DCEFCWK;
			bweak;
		case amd_pp_disp_cwock:
			cwk_type = SMU_DISPCWK;
			bweak;
		defauwt:
			dev_eww(smu->adev->dev, "Invawid cwock type!\n");
			wetuwn -EINVAW;
		}

		wet = smu->ppt_funcs->get_cwock_by_type_with_watency(smu, cwk_type, cwocks);
	}

	wetuwn wet;
}

static int smu_dispway_cwock_vowtage_wequest(void *handwe,
					     stwuct pp_dispway_cwock_wequest *cwock_weq)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->dispway_cwock_vowtage_wequest)
		wet = smu->ppt_funcs->dispway_cwock_vowtage_wequest(smu, cwock_weq);

	wetuwn wet;
}


static int smu_dispway_disabwe_memowy_cwock_switch(void *handwe,
						   boow disabwe_memowy_cwock_switch)
{
	stwuct smu_context *smu = handwe;
	int wet = -EINVAW;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->dispway_disabwe_memowy_cwock_switch)
		wet = smu->ppt_funcs->dispway_disabwe_memowy_cwock_switch(smu, disabwe_memowy_cwock_switch);

	wetuwn wet;
}

static int smu_set_xgmi_pstate(void *handwe,
			       uint32_t pstate)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->set_xgmi_pstate)
		wet = smu->ppt_funcs->set_xgmi_pstate(smu, pstate);

	if (wet)
		dev_eww(smu->adev->dev, "Faiwed to set XGMI pstate!\n");

	wetuwn wet;
}

static boow smu_get_baco_capabiwity(void *handwe)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed)
		wetuwn fawse;

	if (!smu->ppt_funcs || !smu->ppt_funcs->baco_is_suppowt)
		wetuwn fawse;

	wetuwn smu->ppt_funcs->baco_is_suppowt(smu);
}

static int smu_baco_set_state(void *handwe, int state)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (state == 0) {
		if (smu->ppt_funcs->baco_exit)
			wet = smu->ppt_funcs->baco_exit(smu);
	} ewse if (state == 1) {
		if (smu->ppt_funcs->baco_entew)
			wet = smu->ppt_funcs->baco_entew(smu);
	} ewse {
		wetuwn -EINVAW;
	}

	if (wet)
		dev_eww(smu->adev->dev, "Faiwed to %s BACO state!\n",
				(state)?"entew":"exit");

	wetuwn wet;
}

boow smu_mode1_weset_is_suppowt(stwuct smu_context *smu)
{
	boow wet = fawse;

	if (!smu->pm_enabwed)
		wetuwn fawse;

	if (smu->ppt_funcs && smu->ppt_funcs->mode1_weset_is_suppowt)
		wet = smu->ppt_funcs->mode1_weset_is_suppowt(smu);

	wetuwn wet;
}

boow smu_mode2_weset_is_suppowt(stwuct smu_context *smu)
{
	boow wet = fawse;

	if (!smu->pm_enabwed)
		wetuwn fawse;

	if (smu->ppt_funcs && smu->ppt_funcs->mode2_weset_is_suppowt)
		wet = smu->ppt_funcs->mode2_weset_is_suppowt(smu);

	wetuwn wet;
}

int smu_mode1_weset(stwuct smu_context *smu)
{
	int wet = 0;

	if (!smu->pm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->mode1_weset)
		wet = smu->ppt_funcs->mode1_weset(smu);

	wetuwn wet;
}

static int smu_mode2_weset(void *handwe)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->mode2_weset)
		wet = smu->ppt_funcs->mode2_weset(smu);

	if (wet)
		dev_eww(smu->adev->dev, "Mode2 weset faiwed!\n");

	wetuwn wet;
}

static int smu_enabwe_gfx_featuwes(void *handwe)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->enabwe_gfx_featuwes)
		wet = smu->ppt_funcs->enabwe_gfx_featuwes(smu);

	if (wet)
		dev_eww(smu->adev->dev, "enabwe gfx featuwes faiwed!\n");

	wetuwn wet;
}

static int smu_get_max_sustainabwe_cwocks_by_dc(void *handwe,
						stwuct pp_smu_nv_cwock_tabwe *max_cwocks)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->get_max_sustainabwe_cwocks_by_dc)
		wet = smu->ppt_funcs->get_max_sustainabwe_cwocks_by_dc(smu, max_cwocks);

	wetuwn wet;
}

static int smu_get_ucwk_dpm_states(void *handwe,
				   unsigned int *cwock_vawues_in_khz,
				   unsigned int *num_states)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->get_ucwk_dpm_states)
		wet = smu->ppt_funcs->get_ucwk_dpm_states(smu, cwock_vawues_in_khz, num_states);

	wetuwn wet;
}

static enum amd_pm_state_type smu_get_cuwwent_powew_state(void *handwe)
{
	stwuct smu_context *smu = handwe;
	enum amd_pm_state_type pm_state = POWEW_STATE_TYPE_DEFAUWT;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->get_cuwwent_powew_state)
		pm_state = smu->ppt_funcs->get_cuwwent_powew_state(smu);

	wetuwn pm_state;
}

static int smu_get_dpm_cwock_tabwe(void *handwe,
				   stwuct dpm_cwocks *cwock_tabwe)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->get_dpm_cwock_tabwe)
		wet = smu->ppt_funcs->get_dpm_cwock_tabwe(smu, cwock_tabwe);

	wetuwn wet;
}

static ssize_t smu_sys_get_gpu_metwics(void *handwe, void **tabwe)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->ppt_funcs->get_gpu_metwics)
		wetuwn -EOPNOTSUPP;

	wetuwn smu->ppt_funcs->get_gpu_metwics(smu, tabwe);
}

static ssize_t smu_sys_get_pm_metwics(void *handwe, void *pm_metwics,
				      size_t size)
{
	stwuct smu_context *smu = handwe;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (!smu->ppt_funcs->get_pm_metwics)
		wetuwn -EOPNOTSUPP;

	wetuwn smu->ppt_funcs->get_pm_metwics(smu, pm_metwics, size);
}

static int smu_enabwe_mgpu_fan_boost(void *handwe)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn -EOPNOTSUPP;

	if (smu->ppt_funcs->enabwe_mgpu_fan_boost)
		wet = smu->ppt_funcs->enabwe_mgpu_fan_boost(smu);

	wetuwn wet;
}

static int smu_gfx_state_change_set(void *handwe,
				    uint32_t state)
{
	stwuct smu_context *smu = handwe;
	int wet = 0;

	if (smu->ppt_funcs->gfx_state_change_set)
		wet = smu->ppt_funcs->gfx_state_change_set(smu, state);

	wetuwn wet;
}

int smu_handwe_passthwough_sbw(stwuct smu_context *smu, boow enabwe)
{
	int wet = 0;

	if (smu->ppt_funcs->smu_handwe_passthwough_sbw)
		wet = smu->ppt_funcs->smu_handwe_passthwough_sbw(smu, enabwe);

	wetuwn wet;
}

int smu_get_ecc_info(stwuct smu_context *smu, void *umc_ecc)
{
	int wet = -EOPNOTSUPP;

	if (smu->ppt_funcs &&
		smu->ppt_funcs->get_ecc_info)
		wet = smu->ppt_funcs->get_ecc_info(smu, umc_ecc);

	wetuwn wet;

}

static int smu_get_pwv_buffew_detaiws(void *handwe, void **addw, size_t *size)
{
	stwuct smu_context *smu = handwe;
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *memowy_poow = &smu_tabwe->memowy_poow;

	if (!addw || !size)
		wetuwn -EINVAW;

	*addw = NUWW;
	*size = 0;
	if (memowy_poow->bo) {
		*addw = memowy_poow->cpu_addw;
		*size = memowy_poow->size;
	}

	wetuwn 0;
}

int smu_set_xgmi_pwpd_mode(stwuct smu_context *smu,
			   enum pp_xgmi_pwpd_mode mode)
{
	int wet = -EOPNOTSUPP;

	if (!smu->pm_enabwed || !smu->adev->pm.dpm_enabwed)
		wetuwn wet;

	/* PWPD powicy is not suppowted if it's NONE */
	if (smu->pwpd_mode == XGMI_PWPD_NONE)
		wetuwn wet;

	if (smu->pwpd_mode == mode)
		wetuwn 0;

	if (smu->ppt_funcs && smu->ppt_funcs->sewect_xgmi_pwpd_powicy)
		wet = smu->ppt_funcs->sewect_xgmi_pwpd_powicy(smu, mode);

	if (!wet)
		smu->pwpd_mode = mode;

	wetuwn wet;
}

static const stwuct amd_pm_funcs swsmu_pm_funcs = {
	/* expowt fow sysfs */
	.set_fan_contwow_mode    = smu_set_fan_contwow_mode,
	.get_fan_contwow_mode    = smu_get_fan_contwow_mode,
	.set_fan_speed_pwm   = smu_set_fan_speed_pwm,
	.get_fan_speed_pwm   = smu_get_fan_speed_pwm,
	.fowce_cwock_wevew       = smu_fowce_ppcwk_wevews,
	.pwint_cwock_wevews      = smu_pwint_ppcwk_wevews,
	.emit_cwock_wevews       = smu_emit_ppcwk_wevews,
	.fowce_pewfowmance_wevew = smu_fowce_pewfowmance_wevew,
	.wead_sensow             = smu_wead_sensow,
	.get_apu_thewmaw_wimit       = smu_get_apu_thewmaw_wimit,
	.set_apu_thewmaw_wimit       = smu_set_apu_thewmaw_wimit,
	.get_pewfowmance_wevew   = smu_get_pewfowmance_wevew,
	.get_cuwwent_powew_state = smu_get_cuwwent_powew_state,
	.get_fan_speed_wpm       = smu_get_fan_speed_wpm,
	.set_fan_speed_wpm       = smu_set_fan_speed_wpm,
	.get_pp_num_states       = smu_get_powew_num_states,
	.get_pp_tabwe            = smu_sys_get_pp_tabwe,
	.set_pp_tabwe            = smu_sys_set_pp_tabwe,
	.switch_powew_pwofiwe    = smu_switch_powew_pwofiwe,
	/* expowt to amdgpu */
	.dispatch_tasks          = smu_handwe_dpm_task,
	.woad_fiwmwawe           = smu_woad_micwocode,
	.set_powewgating_by_smu  = smu_dpm_set_powew_gate,
	.set_powew_wimit         = smu_set_powew_wimit,
	.get_powew_wimit         = smu_get_powew_wimit,
	.get_powew_pwofiwe_mode  = smu_get_powew_pwofiwe_mode,
	.set_powew_pwofiwe_mode  = smu_set_powew_pwofiwe_mode,
	.odn_edit_dpm_tabwe      = smu_od_edit_dpm_tabwe,
	.set_mp1_state           = smu_set_mp1_state,
	.gfx_state_change_set    = smu_gfx_state_change_set,
	/* expowt to DC */
	.get_scwk                         = smu_get_scwk,
	.get_mcwk                         = smu_get_mcwk,
	.dispway_configuwation_change     = smu_dispway_configuwation_change,
	.get_cwock_by_type_with_watency   = smu_get_cwock_by_type_with_watency,
	.dispway_cwock_vowtage_wequest    = smu_dispway_cwock_vowtage_wequest,
	.enabwe_mgpu_fan_boost            = smu_enabwe_mgpu_fan_boost,
	.set_active_dispway_count         = smu_set_dispway_count,
	.set_min_deep_sweep_dcefcwk       = smu_set_deep_sweep_dcefcwk,
	.get_asic_baco_capabiwity         = smu_get_baco_capabiwity,
	.set_asic_baco_state              = smu_baco_set_state,
	.get_ppfeatuwe_status             = smu_sys_get_pp_featuwe_mask,
	.set_ppfeatuwe_status             = smu_sys_set_pp_featuwe_mask,
	.asic_weset_mode_2                = smu_mode2_weset,
	.asic_weset_enabwe_gfx_featuwes   = smu_enabwe_gfx_featuwes,
	.set_df_cstate                    = smu_set_df_cstate,
	.set_xgmi_pstate                  = smu_set_xgmi_pstate,
	.get_gpu_metwics                  = smu_sys_get_gpu_metwics,
	.get_pm_metwics                   = smu_sys_get_pm_metwics,
	.set_watewmawks_fow_cwock_wanges     = smu_set_watewmawks_fow_cwock_wanges,
	.dispway_disabwe_memowy_cwock_switch = smu_dispway_disabwe_memowy_cwock_switch,
	.get_max_sustainabwe_cwocks_by_dc    = smu_get_max_sustainabwe_cwocks_by_dc,
	.get_ucwk_dpm_states              = smu_get_ucwk_dpm_states,
	.get_dpm_cwock_tabwe              = smu_get_dpm_cwock_tabwe,
	.get_smu_pwv_buf_detaiws = smu_get_pwv_buffew_detaiws,
};

int smu_wait_fow_event(stwuct smu_context *smu, enum smu_event_type event,
		       uint64_t event_awg)
{
	int wet = -EINVAW;

	if (smu->ppt_funcs->wait_fow_event)
		wet = smu->ppt_funcs->wait_fow_event(smu, event, event_awg);

	wetuwn wet;
}

int smu_stb_cowwect_info(stwuct smu_context *smu, void *buf, uint32_t size)
{

	if (!smu->ppt_funcs->stb_cowwect_info || !smu->stb_context.enabwed)
		wetuwn -EOPNOTSUPP;

	/* Confiwm the buffew awwocated is of cowwect size */
	if (size != smu->stb_context.stb_buf_size)
		wetuwn -EINVAW;

	/*
	 * No need to wock smu mutex as we access STB diwectwy thwough MMIO
	 * and not going thwough SMU messaging woute (fow now at weast).
	 * Fow wegistews access wewy on impwementation intewnaw wocking.
	 */
	wetuwn smu->ppt_funcs->stb_cowwect_info(smu, buf, size);
}

#if defined(CONFIG_DEBUG_FS)

static int smu_stb_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct amdgpu_device *adev = fiwp->f_inode->i_pwivate;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	unsigned chaw *buf;
	int w;

	buf = kvmawwoc_awway(smu->stb_context.stb_buf_size, sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	w = smu_stb_cowwect_info(smu, buf, smu->stb_context.stb_buf_size);
	if (w)
		goto out;

	fiwp->pwivate_data = buf;

	wetuwn 0;

out:
	kvfwee(buf);
	wetuwn w;
}

static ssize_t smu_stb_debugfs_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t size,
				woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwp->f_inode->i_pwivate;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;


	if (!fiwp->pwivate_data)
		wetuwn -EINVAW;

	wetuwn simpwe_wead_fwom_buffew(buf,
				       size,
				       pos, fiwp->pwivate_data,
				       smu->stb_context.stb_buf_size);
}

static int smu_stb_debugfs_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	kvfwee(fiwp->pwivate_data);
	fiwp->pwivate_data = NUWW;

	wetuwn 0;
}

/*
 * We have to define not onwy wead method but awso
 * open and wewease because .wead takes up to PAGE_SIZE
 * data each time so and so is invoked muwtipwe times.
 *  We awwocate the STB buffew in .open and wewease it
 *  in .wewease
 */
static const stwuct fiwe_opewations smu_stb_debugfs_fops = {
	.ownew = THIS_MODUWE,
	.open = smu_stb_debugfs_open,
	.wead = smu_stb_debugfs_wead,
	.wewease = smu_stb_debugfs_wewease,
	.wwseek = defauwt_wwseek,
};

#endif

void amdgpu_smu_stb_debug_fs_init(stwuct amdgpu_device *adev)
{
#if defined(CONFIG_DEBUG_FS)

	stwuct smu_context *smu = adev->powewpway.pp_handwe;

	if (!smu || (!smu->stb_context.stb_buf_size))
		wetuwn;

	debugfs_cweate_fiwe_size("amdgpu_smu_stb_dump",
			    S_IWUSW,
			    adev_to_dwm(adev)->pwimawy->debugfs_woot,
			    adev,
			    &smu_stb_debugfs_fops,
			    smu->stb_context.stb_buf_size);
#endif
}

int smu_send_hbm_bad_pages_num(stwuct smu_context *smu, uint32_t size)
{
	int wet = 0;

	if (smu->ppt_funcs && smu->ppt_funcs->send_hbm_bad_pages_num)
		wet = smu->ppt_funcs->send_hbm_bad_pages_num(smu, size);

	wetuwn wet;
}

int smu_send_hbm_bad_channew_fwag(stwuct smu_context *smu, uint32_t size)
{
	int wet = 0;

	if (smu->ppt_funcs && smu->ppt_funcs->send_hbm_bad_channew_fwag)
		wet = smu->ppt_funcs->send_hbm_bad_channew_fwag(smu, size);

	wetuwn wet;
}
