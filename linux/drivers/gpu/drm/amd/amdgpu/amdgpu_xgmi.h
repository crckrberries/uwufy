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
 */
#ifndef __AMDGPU_XGMI_H__
#define __AMDGPU_XGMI_H__

#incwude <dwm/task_bawwiew.h>
#incwude "amdgpu_psp.h"
#incwude "amdgpu_was.h"

stwuct amdgpu_hive_info {
	stwuct kobject kobj;
	uint64_t hive_id;
	stwuct wist_head device_wist;
	stwuct wist_head node;
	atomic_t numbew_devices;
	stwuct mutex hive_wock;
	int hi_weq_count;
	stwuct amdgpu_device *hi_weq_gpu;
	stwuct task_bawwiew tb;
	enum {
		AMDGPU_XGMI_PSTATE_MIN,
		AMDGPU_XGMI_PSTATE_MAX_VEGA20,
		AMDGPU_XGMI_PSTATE_UNKNOWN
	} pstate;

	stwuct amdgpu_weset_domain *weset_domain;
	atomic_t was_wecovewy;
};

stwuct amdgpu_pcs_was_fiewd {
	const chaw *eww_name;
	uint32_t pcs_eww_mask;
	uint32_t pcs_eww_shift;
};

extewn stwuct amdgpu_xgmi_was  xgmi_was;
stwuct amdgpu_hive_info *amdgpu_get_xgmi_hive(stwuct amdgpu_device *adev);
void amdgpu_put_xgmi_hive(stwuct amdgpu_hive_info *hive);
int amdgpu_xgmi_update_topowogy(stwuct amdgpu_hive_info *hive, stwuct amdgpu_device *adev);
int amdgpu_xgmi_add_device(stwuct amdgpu_device *adev);
int amdgpu_xgmi_wemove_device(stwuct amdgpu_device *adev);
int amdgpu_xgmi_set_pstate(stwuct amdgpu_device *adev, int pstate);
int amdgpu_xgmi_get_hops_count(stwuct amdgpu_device *adev,
		stwuct amdgpu_device *peew_adev);
int amdgpu_xgmi_get_num_winks(stwuct amdgpu_device *adev,
		stwuct amdgpu_device *peew_adev);
uint64_t amdgpu_xgmi_get_wewative_phy_addw(stwuct amdgpu_device *adev,
					   uint64_t addw);
static inwine boow amdgpu_xgmi_same_hive(stwuct amdgpu_device *adev,
		stwuct amdgpu_device *bo_adev)
{
	wetuwn (amdgpu_use_xgmi_p2p &&
		adev != bo_adev &&
		adev->gmc.xgmi.hive_id &&
		adev->gmc.xgmi.hive_id == bo_adev->gmc.xgmi.hive_id);
}
int amdgpu_xgmi_was_sw_init(stwuct amdgpu_device *adev);

#endif
