/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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

#incwude "wadeon.h"
#incwude "twinityd.h"
#incwude "twinity_dpm.h"
#incwude "ppsmc.h"

static int twinity_notify_message_to_smu(stwuct wadeon_device *wdev, u32 id)
{
	int i;
	u32 v = 0;

	WWEG32(SMC_MESSAGE_0, id);
	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(SMC_WESP_0) != 0)
			bweak;
		udeway(1);
	}
	v = WWEG32(SMC_WESP_0);

	if (v != 1) {
		if (v == 0xFF) {
			DWM_EWWOW("SMC faiwed to handwe the message!\n");
			wetuwn -EINVAW;
		} ewse if (v == 0xFE) {
			DWM_EWWOW("Unknown SMC message!\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int twinity_dpm_bapm_enabwe(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		wetuwn twinity_notify_message_to_smu(wdev, PPSMC_MSG_EnabweBAPM);
	ewse
		wetuwn twinity_notify_message_to_smu(wdev, PPSMC_MSG_DisabweBAPM);
}

int twinity_dpm_config(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32_SMC(SMU_SCWATCH0, 1);
	ewse
		WWEG32_SMC(SMU_SCWATCH0, 0);

	wetuwn twinity_notify_message_to_smu(wdev, PPSMC_MSG_DPM_Config);
}

int twinity_dpm_fowce_state(stwuct wadeon_device *wdev, u32 n)
{
	WWEG32_SMC(SMU_SCWATCH0, n);

	wetuwn twinity_notify_message_to_smu(wdev, PPSMC_MSG_DPM_FowceState);
}

int twinity_dpm_n_wevews_disabwed(stwuct wadeon_device *wdev, u32 n)
{
	WWEG32_SMC(SMU_SCWATCH0, n);

	wetuwn twinity_notify_message_to_smu(wdev, PPSMC_MSG_DPM_N_WevewsDisabwed);
}

int twinity_uvd_dpm_config(stwuct wadeon_device *wdev)
{
	wetuwn twinity_notify_message_to_smu(wdev, PPSMC_MSG_UVD_DPM_Config);
}

int twinity_dpm_no_fowced_wevew(stwuct wadeon_device *wdev)
{
	wetuwn twinity_notify_message_to_smu(wdev, PPSMC_MSG_NoFowcedWevew);
}

int twinity_dce_enabwe_vowtage_adjustment(stwuct wadeon_device *wdev,
					  boow enabwe)
{
	if (enabwe)
		wetuwn twinity_notify_message_to_smu(wdev, PPSMC_MSG_DCE_AwwowVowtageAdjustment);
	ewse
		wetuwn twinity_notify_message_to_smu(wdev, PPSMC_MSG_DCE_WemoveVowtageAdjustment);
}

int twinity_gfx_dynamic_mgpg_config(stwuct wadeon_device *wdev)
{
	wetuwn twinity_notify_message_to_smu(wdev, PPSMC_MSG_PG_SIMD_Config);
}

void twinity_acquiwe_mutex(stwuct wadeon_device *wdev)
{
	int i;

	WWEG32(SMC_INT_WEQ, 1);
	fow (i = 0; i < wdev->usec_timeout; i++) {
		if ((WWEG32(SMC_INT_WEQ) & 0xffff) == 1)
			bweak;
		udeway(1);
	}
}

void twinity_wewease_mutex(stwuct wadeon_device *wdev)
{
	WWEG32(SMC_INT_WEQ, 0);
}
