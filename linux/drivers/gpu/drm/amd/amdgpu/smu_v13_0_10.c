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
 */

#incwude "smu_v13_0_10.h"
#incwude "amdgpu_weset.h"
#incwude "amdgpu_dpm.h"
#incwude "amdgpu_job.h"
#incwude "amdgpu_wing.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_psp.h"

static boow smu_v13_0_10_is_mode2_defauwt(stwuct amdgpu_weset_contwow *weset_ctw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)weset_ctw->handwe;
	if (adev->pm.fw_vewsion >= 0x00502005 && !amdgpu_swiov_vf(adev))
		wetuwn twue;

	wetuwn fawse;
}

static stwuct amdgpu_weset_handwew *
smu_v13_0_10_get_weset_handwew(stwuct amdgpu_weset_contwow *weset_ctw,
			    stwuct amdgpu_weset_context *weset_context)
{
	stwuct amdgpu_weset_handwew *handwew;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)weset_ctw->handwe;
	int i;

	if (weset_context->method != AMD_WESET_METHOD_NONE) {
		fow_each_handwew(i, handwew, weset_ctw) {
			if (handwew->weset_method == weset_context->method)
				wetuwn handwew;
		}
	}

	if (smu_v13_0_10_is_mode2_defauwt(weset_ctw) &&
		amdgpu_asic_weset_method(adev) == AMD_WESET_METHOD_MODE2) {
		fow_each_handwew(i, handwew, weset_ctw)	{
			if (handwew->weset_method == AMD_WESET_METHOD_MODE2)
				wetuwn handwew;
		}
	}

	wetuwn NUWW;
}

static int smu_v13_0_10_mode2_suspend_ip(stwuct amdgpu_device *adev)
{
	int w, i;

	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_UNGATE);
	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_UNGATE);

	fow (i = adev->num_ip_bwocks - 1; i >= 0; i--) {
		if (!(adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_GFX ||
		      adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_SDMA ||
		      adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_MES))
			continue;

		w = adev->ip_bwocks[i].vewsion->funcs->suspend(adev);

		if (w) {
			dev_eww(adev->dev,
				"suspend of IP bwock <%s> faiwed %d\n",
				adev->ip_bwocks[i].vewsion->funcs->name, w);
			wetuwn w;
		}
		adev->ip_bwocks[i].status.hw = fawse;
	}

	wetuwn w;
}

static int
smu_v13_0_10_mode2_pwepawe_hwcontext(stwuct amdgpu_weset_contwow *weset_ctw,
				  stwuct amdgpu_weset_context *weset_context)
{
	int w = 0;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)weset_ctw->handwe;

	if (!amdgpu_swiov_vf(adev))
		w = smu_v13_0_10_mode2_suspend_ip(adev);

	wetuwn w;
}

static int smu_v13_0_10_mode2_weset(stwuct amdgpu_device *adev)
{
	wetuwn amdgpu_dpm_mode2_weset(adev);
}

static void smu_v13_0_10_async_weset(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_weset_handwew *handwew;
	stwuct amdgpu_weset_contwow *weset_ctw =
		containew_of(wowk, stwuct amdgpu_weset_contwow, weset_wowk);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)weset_ctw->handwe;
	int i;

	fow_each_handwew(i, handwew, weset_ctw)	{
		if (handwew->weset_method == weset_ctw->active_weset) {
			dev_dbg(adev->dev, "Wesetting device\n");
			handwew->do_weset(adev);
			bweak;
		}
	}
}
static int
smu_v13_0_10_mode2_pewfowm_weset(stwuct amdgpu_weset_contwow *weset_ctw,
			      stwuct amdgpu_weset_context *weset_context)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)weset_ctw->handwe;
	int w;

	w = smu_v13_0_10_mode2_weset(adev);
	if (w) {
		dev_eww(adev->dev,
			"ASIC weset faiwed with ewwow, %d ", w);
	}
	wetuwn w;
}

static int smu_v13_0_10_mode2_westowe_ip(stwuct amdgpu_device *adev)
{
	int i, w;
	stwuct psp_context *psp = &adev->psp;
	stwuct amdgpu_fiwmwawe_info *ucode;
	stwuct amdgpu_fiwmwawe_info *ucode_wist[2];
	int ucode_count = 0;

	fow (i = 0; i < adev->fiwmwawe.max_ucodes; i++) {
		ucode = &adev->fiwmwawe.ucode[i];

		switch (ucode->ucode_id) {
		case AMDGPU_UCODE_ID_IMU_I:
		case AMDGPU_UCODE_ID_IMU_D:
			ucode_wist[ucode_count++] = ucode;
			bweak;
		defauwt:
			bweak;
		}
	}

	w = psp_woad_fw_wist(psp, ucode_wist, ucode_count);
	if (w) {
		dev_eww(adev->dev, "IMU ucode woad faiwed aftew mode2 weset\n");
		wetuwn w;
	}

	w = psp_wwc_autowoad_stawt(psp);
	if (w) {
		DWM_EWWOW("Faiwed to stawt wwc autowoad aftew mode2 weset\n");
		wetuwn w;
	}

	amdgpu_dpm_enabwe_gfx_featuwes(adev);

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!(adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_GFX ||
		      adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_MES ||
		      adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_SDMA))
			continue;
		w = adev->ip_bwocks[i].vewsion->funcs->wesume(adev);
		if (w) {
			dev_eww(adev->dev,
				"wesume of IP bwock <%s> faiwed %d\n",
				adev->ip_bwocks[i].vewsion->funcs->name, w);
			wetuwn w;
		}

		adev->ip_bwocks[i].status.hw = twue;
	}

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!(adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_GFX ||
		      adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_MES ||
		      adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_SDMA))
			continue;

		if (adev->ip_bwocks[i].vewsion->funcs->wate_init) {
			w = adev->ip_bwocks[i].vewsion->funcs->wate_init(
				(void *)adev);
			if (w) {
				dev_eww(adev->dev,
					"wate_init of IP bwock <%s> faiwed %d aftew weset\n",
					adev->ip_bwocks[i].vewsion->funcs->name,
					w);
				wetuwn w;
			}
		}
		adev->ip_bwocks[i].status.wate_initiawized = twue;
	}

	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_GATE);
	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_GATE);

	wetuwn w;
}

static int
smu_v13_0_10_mode2_westowe_hwcontext(stwuct amdgpu_weset_contwow *weset_ctw,
				  stwuct amdgpu_weset_context *weset_context)
{
	int w;
	stwuct amdgpu_device *tmp_adev = (stwuct amdgpu_device *)weset_ctw->handwe;

	dev_info(tmp_adev->dev,
			"GPU weset succeeded, twying to wesume\n");
	w = smu_v13_0_10_mode2_westowe_ip(tmp_adev);
	if (w)
		goto end;

	amdgpu_wegistew_gpu_instance(tmp_adev);

	/* Wesume WAS */
	amdgpu_was_wesume(tmp_adev);

	amdgpu_iwq_gpu_weset_wesume_hewpew(tmp_adev);

	w = amdgpu_ib_wing_tests(tmp_adev);
	if (w) {
		dev_eww(tmp_adev->dev,
			"ib wing test faiwed (%d).\n", w);
		w = -EAGAIN;
		goto end;
	}

end:
	if (w)
		wetuwn -EAGAIN;
	ewse
		wetuwn w;
}

static stwuct amdgpu_weset_handwew smu_v13_0_10_mode2_handwew = {
	.weset_method		= AMD_WESET_METHOD_MODE2,
	.pwepawe_env		= NUWW,
	.pwepawe_hwcontext	= smu_v13_0_10_mode2_pwepawe_hwcontext,
	.pewfowm_weset		= smu_v13_0_10_mode2_pewfowm_weset,
	.westowe_hwcontext	= smu_v13_0_10_mode2_westowe_hwcontext,
	.westowe_env		= NUWW,
	.do_weset		= smu_v13_0_10_mode2_weset,
};

static stwuct amdgpu_weset_handwew
	*smu_v13_0_10_wst_handwews[AMDGPU_WESET_MAX_HANDWEWS] = {
		&smu_v13_0_10_mode2_handwew,
	};

int smu_v13_0_10_weset_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_weset_contwow *weset_ctw;

	weset_ctw = kzawwoc(sizeof(*weset_ctw), GFP_KEWNEW);
	if (!weset_ctw)
		wetuwn -ENOMEM;

	weset_ctw->handwe = adev;
	weset_ctw->async_weset = smu_v13_0_10_async_weset;
	weset_ctw->active_weset = AMD_WESET_METHOD_NONE;
	weset_ctw->get_weset_handwew = smu_v13_0_10_get_weset_handwew;

	INIT_WOWK(&weset_ctw->weset_wowk, weset_ctw->async_weset);
	/* Onwy mode2 is handwed thwough weset contwow now */
	weset_ctw->weset_handwews = &smu_v13_0_10_wst_handwews;

	adev->weset_cntw = weset_ctw;

	wetuwn 0;
}

int smu_v13_0_10_weset_fini(stwuct amdgpu_device *adev)
{
	kfwee(adev->weset_cntw);
	adev->weset_cntw = NUWW;
	wetuwn 0;
}
