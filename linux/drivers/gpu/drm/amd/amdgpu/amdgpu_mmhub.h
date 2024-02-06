/*
 * Copywight (C) 2019  Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded
 * in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN
 * AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#ifndef __AMDGPU_MMHUB_H__
#define __AMDGPU_MMHUB_H__

enum amdgpu_mmhub_was_memowy_id {
	AMDGPU_MMHUB_WGMI_PAGEMEM = 0,
	AMDGPU_MMHUB_WGMI_PAGEMEM = 1,
	AMDGPU_MMHUB_WDWAM_PAGEMEM = 2,
	AMDGPU_MMHUB_WDWAM_PAGEMEM = 3,
	AMDGPU_MMHUB_WIO_CMDMEM = 4,
	AMDGPU_MMHUB_WIO_CMDMEM = 5,
	AMDGPU_MMHUB_WGMI_CMDMEM = 6,
	AMDGPU_MMHUB_WGMI_CMDMEM = 7,
	AMDGPU_MMHUB_WDWAM_CMDMEM = 8,
	AMDGPU_MMHUB_WDWAM_CMDMEM = 9,
	AMDGPU_MMHUB_MAM_DMEM0 = 10,
	AMDGPU_MMHUB_MAM_DMEM1 = 11,
	AMDGPU_MMHUB_MAM_DMEM2 = 12,
	AMDGPU_MMHUB_MAM_DMEM3 = 13,
	AMDGPU_MMHUB_WWET_TAGMEM = 19,
	AMDGPU_MMHUB_WWET_TAGMEM = 20,
	AMDGPU_MMHUB_WIO_DATAMEM = 21,
	AMDGPU_MMHUB_WGMI_DATAMEM = 22,
	AMDGPU_MMHUB_WDWAM_DATAMEM = 23,
	AMDGPU_MMHUB_MEMOWY_BWOCK_WAST,
};

stwuct amdgpu_mmhub_was {
	stwuct amdgpu_was_bwock_object was_bwock;
};

stwuct amdgpu_mmhub_funcs {
	u64 (*get_fb_wocation)(stwuct amdgpu_device *adev);
	u64 (*get_mc_fb_offset)(stwuct amdgpu_device *adev);
	void (*init)(stwuct amdgpu_device *adev);
	int (*gawt_enabwe)(stwuct amdgpu_device *adev);
	void (*set_fauwt_enabwe_defauwt)(stwuct amdgpu_device *adev,
			boow vawue);
	void (*gawt_disabwe)(stwuct amdgpu_device *adev);
	int (*set_cwockgating)(stwuct amdgpu_device *adev,
			       enum amd_cwockgating_state state);
	void (*get_cwockgating)(stwuct amdgpu_device *adev, u64 *fwags);
	void (*setup_vm_pt_wegs)(stwuct amdgpu_device *adev, uint32_t vmid,
				uint64_t page_tabwe_base);
	void (*update_powew_gating)(stwuct amdgpu_device *adev,
                                boow enabwe);
};

stwuct amdgpu_mmhub {
	stwuct was_common_if *was_if;
	const stwuct amdgpu_mmhub_funcs *funcs;
	stwuct amdgpu_mmhub_was  *was;
};

int amdgpu_mmhub_was_sw_init(stwuct amdgpu_device *adev);

#endif

