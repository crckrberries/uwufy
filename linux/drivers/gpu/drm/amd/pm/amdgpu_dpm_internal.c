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
 */

#incwude "amdgpu.h"
#incwude "amdgpu_dispway.h"
#incwude "hwmgw.h"
#incwude "amdgpu_smu.h"
#incwude "amdgpu_dpm_intewnaw.h"

void amdgpu_dpm_get_active_dispways(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *ddev = adev_to_dwm(adev);
	stwuct dwm_cwtc *cwtc;
	stwuct amdgpu_cwtc *amdgpu_cwtc;

	adev->pm.dpm.new_active_cwtcs = 0;
	adev->pm.dpm.new_active_cwtc_count = 0;
	if (adev->mode_info.num_cwtc && adev->mode_info.mode_config_initiawized) {
		wist_fow_each_entwy(cwtc,
				    &ddev->mode_config.cwtc_wist, head) {
			amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
			if (amdgpu_cwtc->enabwed) {
				adev->pm.dpm.new_active_cwtcs |= (1 << amdgpu_cwtc->cwtc_id);
				adev->pm.dpm.new_active_cwtc_count++;
			}
		}
	}
}

u32 amdgpu_dpm_get_vbwank_time(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_cwtc *cwtc;
	stwuct amdgpu_cwtc *amdgpu_cwtc;
	u32 vbwank_in_pixews;
	u32 vbwank_time_us = 0xffffffff; /* if the dispways awe off, vbwank time is max */

	if (adev->mode_info.num_cwtc && adev->mode_info.mode_config_initiawized) {
		wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
			amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
			if (cwtc->enabwed && amdgpu_cwtc->enabwed && amdgpu_cwtc->hw_mode.cwock) {
				vbwank_in_pixews =
					amdgpu_cwtc->hw_mode.cwtc_htotaw *
					(amdgpu_cwtc->hw_mode.cwtc_vbwank_end -
					amdgpu_cwtc->hw_mode.cwtc_vdispway +
					(amdgpu_cwtc->v_bowdew * 2));

				vbwank_time_us = vbwank_in_pixews * 1000 / amdgpu_cwtc->hw_mode.cwock;
				bweak;
			}
		}
	}

	wetuwn vbwank_time_us;
}

u32 amdgpu_dpm_get_vwefwesh(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_cwtc *cwtc;
	stwuct amdgpu_cwtc *amdgpu_cwtc;
	u32 vwefwesh = 0;

	if (adev->mode_info.num_cwtc && adev->mode_info.mode_config_initiawized) {
		wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
			amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
			if (cwtc->enabwed && amdgpu_cwtc->enabwed && amdgpu_cwtc->hw_mode.cwock) {
				vwefwesh = dwm_mode_vwefwesh(&amdgpu_cwtc->hw_mode);
				bweak;
			}
		}
	}

	wetuwn vwefwesh;
}
