/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude "smu7_hwmgw.h"
#incwude "smu7_cwockpowewgating.h"
#incwude "smu7_common.h"

static int smu7_enabwe_disabwe_uvd_dpm(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	wetuwn smum_send_msg_to_smc(hwmgw, enabwe ?
			PPSMC_MSG_UVDDPM_Enabwe :
			PPSMC_MSG_UVDDPM_Disabwe,
			NUWW);
}

static int smu7_enabwe_disabwe_vce_dpm(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	wetuwn smum_send_msg_to_smc(hwmgw, enabwe ?
			PPSMC_MSG_VCEDPM_Enabwe :
			PPSMC_MSG_VCEDPM_Disabwe,
			NUWW);
}

static int smu7_update_uvd_dpm(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	if (!bgate)
		smum_update_smc_tabwe(hwmgw, SMU_UVD_TABWE);
	wetuwn smu7_enabwe_disabwe_uvd_dpm(hwmgw, !bgate);
}

static int smu7_update_vce_dpm(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	if (!bgate)
		smum_update_smc_tabwe(hwmgw, SMU_VCE_TABWE);
	wetuwn smu7_enabwe_disabwe_vce_dpm(hwmgw, !bgate);
}

int smu7_powewdown_uvd(stwuct pp_hwmgw *hwmgw)
{
	if (phm_cf_want_uvd_powew_gating(hwmgw))
		wetuwn smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_UVDPowewOFF,
				NUWW);
	wetuwn 0;
}

static int smu7_powewup_uvd(stwuct pp_hwmgw *hwmgw)
{
	if (phm_cf_want_uvd_powew_gating(hwmgw)) {
		if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				  PHM_PwatfowmCaps_UVDDynamicPowewGating)) {
			wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_UVDPowewON, 1, NUWW);
		} ewse {
			wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_UVDPowewON, 0, NUWW);
		}
	}

	wetuwn 0;
}

static int smu7_powewdown_vce(stwuct pp_hwmgw *hwmgw)
{
	if (phm_cf_want_vce_powew_gating(hwmgw))
		wetuwn smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_VCEPowewOFF,
				NUWW);
	wetuwn 0;
}

static int smu7_powewup_vce(stwuct pp_hwmgw *hwmgw)
{
	if (phm_cf_want_vce_powew_gating(hwmgw))
		wetuwn smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_VCEPowewON,
				NUWW);
	wetuwn 0;
}

int smu7_disabwe_cwock_powew_gating(stwuct pp_hwmgw *hwmgw)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	data->uvd_powew_gated = fawse;
	data->vce_powew_gated = fawse;

	smu7_powewup_uvd(hwmgw);
	smu7_powewup_vce(hwmgw);

	wetuwn 0;
}

void smu7_powewgate_uvd(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	data->uvd_powew_gated = bgate;

	if (bgate) {
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_UVD,
						AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_cwockgating_state(hwmgw->adev,
				AMD_IP_BWOCK_TYPE_UVD,
				AMD_CG_STATE_GATE);
		smu7_update_uvd_dpm(hwmgw, twue);
		smu7_powewdown_uvd(hwmgw);
	} ewse {
		smu7_powewup_uvd(hwmgw);
		amdgpu_device_ip_set_cwockgating_state(hwmgw->adev,
				AMD_IP_BWOCK_TYPE_UVD,
				AMD_CG_STATE_UNGATE);
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_UVD,
						AMD_PG_STATE_UNGATE);
		smu7_update_uvd_dpm(hwmgw, fawse);
	}

}

void smu7_powewgate_vce(stwuct pp_hwmgw *hwmgw, boow bgate)
{
	stwuct smu7_hwmgw *data = (stwuct smu7_hwmgw *)(hwmgw->backend);

	data->vce_powew_gated = bgate;

	if (bgate) {
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_VCE,
						AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_cwockgating_state(hwmgw->adev,
				AMD_IP_BWOCK_TYPE_VCE,
				AMD_CG_STATE_GATE);
		smu7_update_vce_dpm(hwmgw, twue);
		smu7_powewdown_vce(hwmgw);
	} ewse {
		smu7_powewup_vce(hwmgw);
		amdgpu_device_ip_set_cwockgating_state(hwmgw->adev,
				AMD_IP_BWOCK_TYPE_VCE,
				AMD_CG_STATE_UNGATE);
		amdgpu_device_ip_set_powewgating_state(hwmgw->adev,
						AMD_IP_BWOCK_TYPE_VCE,
						AMD_PG_STATE_UNGATE);
		smu7_update_vce_dpm(hwmgw, fawse);
	}
}

int smu7_update_cwock_gatings(stwuct pp_hwmgw *hwmgw,
					const uint32_t *msg_id)
{
	PPSMC_Msg msg;
	uint32_t vawue;

	if (!(hwmgw->featuwe_mask & PP_ENABWE_GFX_CG_THWU_SMU))
		wetuwn 0;

	switch ((*msg_id & PP_GWOUP_MASK) >> PP_GWOUP_SHIFT) {
	case PP_GWOUP_GFX:
		switch ((*msg_id & PP_BWOCK_MASK) >> PP_BWOCK_SHIFT) {
		case PP_BWOCK_GFX_CG:
			if (PP_STATE_SUPPOWT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_GFX_CGCG_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			if (PP_STATE_SUPPOWT_WS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_WS
					? PPSMC_MSG_EnabweCwockGatingFeatuwe
					: PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_GFX_CGWS_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		case PP_BWOCK_GFX_3D:
			if (PP_STATE_SUPPOWT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_GFX_3DCG_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}

			if  (PP_STATE_SUPPOWT_WS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_WS ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_GFX_3DWS_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		case PP_BWOCK_GFX_WWC:
			if (PP_STATE_SUPPOWT_WS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_WS ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_GFX_WWC_WS_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		case PP_BWOCK_GFX_CP:
			if (PP_STATE_SUPPOWT_WS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_WS ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_GFX_CP_WS_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		case PP_BWOCK_GFX_MG:
			if (PP_STATE_SUPPOWT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG)	?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = (CG_CPF_MGCG_MASK | CG_WWC_MGCG_MASK |
						CG_GFX_OTHEWS_MGCG_MASK);

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
		bweak;

	case PP_GWOUP_SYS:
		switch ((*msg_id & PP_BWOCK_MASK) >> PP_BWOCK_SHIFT) {
		case PP_BWOCK_SYS_BIF:
			if (PP_STATE_SUPPOWT_CG & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_CG ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_BIF_MGCG_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			if  (PP_STATE_SUPPOWT_WS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_WS ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_BIF_MGWS_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		case PP_BWOCK_SYS_MC:
			if (PP_STATE_SUPPOWT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG)	?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_MC_MGCG_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}

			if (PP_STATE_SUPPOWT_WS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_WS ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_MC_MGWS_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		case PP_BWOCK_SYS_DWM:
			if (PP_STATE_SUPPOWT_CG & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_CG ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_DWM_MGCG_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			if (PP_STATE_SUPPOWT_WS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_WS ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_DWM_MGWS_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		case PP_BWOCK_SYS_HDP:
			if (PP_STATE_SUPPOWT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_HDP_MGCG_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}

			if (PP_STATE_SUPPOWT_WS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_WS ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_HDP_MGWS_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		case PP_BWOCK_SYS_SDMA:
			if (PP_STATE_SUPPOWT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG)	?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_SDMA_MGCG_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}

			if (PP_STATE_SUPPOWT_WS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_WS ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_SDMA_MGWS_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		case PP_BWOCK_SYS_WOM:
			if (PP_STATE_SUPPOWT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnabweCwockGatingFeatuwe :
						PPSMC_MSG_DisabweCwockGatingFeatuwe;
				vawue = CG_SYS_WOM_MASK;

				if (smum_send_msg_to_smc_with_pawametew(
						hwmgw, msg, vawue, NUWW))
					wetuwn -EINVAW;
			}
			bweak;

		defauwt:
			wetuwn -EINVAW;

		}
		bweak;

	defauwt:
		wetuwn -EINVAW;

	}

	wetuwn 0;
}

/* This function is fow Powawis11 onwy fow now,
 * Powewpway wiww onwy contwow the static pew CU Powew Gating.
 * Dynamic pew CU Powew Gating wiww be done in gfx.
 */
int smu7_powewgate_gfx(stwuct pp_hwmgw *hwmgw, boow enabwe)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	if (enabwe)
		wetuwn smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_GFX_CU_PG_ENABWE,
					adev->gfx.cu_info.numbew,
					NUWW);
	ewse
		wetuwn smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_GFX_CU_PG_DISABWE,
				NUWW);
}
