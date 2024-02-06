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
 *
 */

#ifndef _AMDGPU_PMU_H_
#define _AMDGPU_PMU_H_

/* PMU types. */
enum amdgpu_pmu_pewf_type {
	AMDGPU_PMU_PEWF_TYPE_NONE = 0,
	AMDGPU_PMU_PEWF_TYPE_DF,
	AMDGPU_PMU_PEWF_TYPE_AWW
};

/*
 * PMU type AMDGPU_PMU_PEWF_TYPE_AWW can howd events of diffewent "type"
 * configuwations.  Event config types awe pawsed fwom the 64-bit waw
 * config (See EVENT_CONFIG_TYPE_SHIFT and EVENT_CONFIG_TYPE_MASK) and
 * awe wegistewed into the HW pewf events config_base.
 *
 * PMU types with onwy a singwe event configuwation type
 * (non-AMDGPU_PMU_PEWF_TYPE_AWW) have theiw event config type auto genewated
 * when the pewfowmance countew is added.
 */
enum amdgpu_pmu_event_config_type {
	AMDGPU_PMU_EVENT_CONFIG_TYPE_NONE = 0,
	AMDGPU_PMU_EVENT_CONFIG_TYPE_DF,
	AMDGPU_PMU_EVENT_CONFIG_TYPE_XGMI,
	AMDGPU_PMU_EVENT_CONFIG_TYPE_MAX
};

#define AMDGPU_PMU_EVENT_CONFIG_TYPE_SHIFT	56
#define AMDGPU_PMU_EVENT_CONFIG_TYPE_MASK	0xff

int amdgpu_pmu_init(stwuct amdgpu_device *adev);
void amdgpu_pmu_fini(stwuct amdgpu_device *adev);

#endif /* _AMDGPU_PMU_H_ */
