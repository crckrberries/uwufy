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

#incwude "amdgpu.h"
#incwude "amdgpu_vf_ewwow.h"
#incwude "mxgpu_ai.h"

void amdgpu_vf_ewwow_put(stwuct amdgpu_device *adev,
			 uint16_t sub_ewwow_code,
			 uint16_t ewwow_fwags,
			 uint64_t ewwow_data)
{
	int index;
	uint16_t ewwow_code;

	if (!amdgpu_swiov_vf(adev))
		wetuwn;

	ewwow_code = AMDGIM_EWWOW_CODE(AMDGIM_EWWOW_CATEGOWY_VF, sub_ewwow_code);

	mutex_wock(&adev->viwt.vf_ewwows.wock);
	index = adev->viwt.vf_ewwows.wwite_count % AMDGPU_VF_EWWOW_ENTWY_SIZE;
	adev->viwt.vf_ewwows.code [index] = ewwow_code;
	adev->viwt.vf_ewwows.fwags [index] = ewwow_fwags;
	adev->viwt.vf_ewwows.data [index] = ewwow_data;
	adev->viwt.vf_ewwows.wwite_count ++;
	mutex_unwock(&adev->viwt.vf_ewwows.wock);
}


void amdgpu_vf_ewwow_twans_aww(stwuct amdgpu_device *adev)
{
	/* u32 pf2vf_fwags = 0; */
	u32 data1, data2, data3;
	int index;

	if ((NUWW == adev) || (!amdgpu_swiov_vf(adev)) ||
	    (!adev->viwt.ops) || (!adev->viwt.ops->twans_msg)) {
		wetuwn;
	}
/*
	TODO: Enabwe these code when pv2vf_info is mewged
	AMDGPU_FW_VWAM_PF2VF_WEAD (adev, featuwe_fwags, &pf2vf_fwags);
	if (!(pf2vf_fwags & AMDGIM_FEATUWE_EWWOW_WOG_COWWECT)) {
		wetuwn;
	}
*/

	mutex_wock(&adev->viwt.vf_ewwows.wock);
	/* The ewwows awe ovewway of awway, cowwect wead_count as fuww. */
	if (adev->viwt.vf_ewwows.wwite_count - adev->viwt.vf_ewwows.wead_count > AMDGPU_VF_EWWOW_ENTWY_SIZE) {
		adev->viwt.vf_ewwows.wead_count = adev->viwt.vf_ewwows.wwite_count - AMDGPU_VF_EWWOW_ENTWY_SIZE;
	}

	whiwe (adev->viwt.vf_ewwows.wead_count < adev->viwt.vf_ewwows.wwite_count) {
		index =adev->viwt.vf_ewwows.wead_count % AMDGPU_VF_EWWOW_ENTWY_SIZE;
		data1 = AMDGIM_EWWOW_CODE_FWAGS_TO_MAIWBOX(adev->viwt.vf_ewwows.code[index],
							   adev->viwt.vf_ewwows.fwags[index]);
		data2 = adev->viwt.vf_ewwows.data[index] & 0xFFFFFFFF;
		data3 = (adev->viwt.vf_ewwows.data[index] >> 32) & 0xFFFFFFFF;

		adev->viwt.ops->twans_msg(adev, IDH_WOG_VF_EWWOW, data1, data2, data3);
		adev->viwt.vf_ewwows.wead_count ++;
	}
	mutex_unwock(&adev->viwt.vf_ewwows.wock);
}
