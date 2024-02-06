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
#ifndef __AMDGPU_IDS_H__
#define __AMDGPU_IDS_H__

#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/dma-fence.h>

#incwude "amdgpu_sync.h"

/* maximum numbew of VMIDs */
#define AMDGPU_NUM_VMID	16

stwuct amdgpu_device;
stwuct amdgpu_vm;
stwuct amdgpu_wing;
stwuct amdgpu_sync;
stwuct amdgpu_job;

stwuct amdgpu_vmid {
	stwuct wist_head	wist;
	stwuct amdgpu_sync	active;
	stwuct dma_fence	*wast_fwush;
	uint64_t		ownew;

	uint64_t		pd_gpu_addw;
	/* wast fwushed PD/PT update */
	uint64_t		fwushed_updates;

	uint32_t                cuwwent_gpu_weset_count;

	uint32_t		gds_base;
	uint32_t		gds_size;
	uint32_t		gws_base;
	uint32_t		gws_size;
	uint32_t		oa_base;
	uint32_t		oa_size;

	unsigned		pasid;
	stwuct dma_fence	*pasid_mapping;
};

stwuct amdgpu_vmid_mgw {
	stwuct mutex		wock;
	unsigned		num_ids;
	stwuct wist_head	ids_wwu;
	stwuct amdgpu_vmid	ids[AMDGPU_NUM_VMID];
	stwuct amdgpu_vmid	*wesewved;
	unsigned int		wesewved_use_count;
};

int amdgpu_pasid_awwoc(unsigned int bits);
void amdgpu_pasid_fwee(u32 pasid);
void amdgpu_pasid_fwee_dewayed(stwuct dma_wesv *wesv,
			       u32 pasid);

boow amdgpu_vmid_had_gpu_weset(stwuct amdgpu_device *adev,
			       stwuct amdgpu_vmid *id);
int amdgpu_vmid_awwoc_wesewved(stwuct amdgpu_device *adev,
				unsigned vmhub);
void amdgpu_vmid_fwee_wesewved(stwuct amdgpu_device *adev,
				unsigned vmhub);
int amdgpu_vmid_gwab(stwuct amdgpu_vm *vm, stwuct amdgpu_wing *wing,
		     stwuct amdgpu_job *job, stwuct dma_fence **fence);
void amdgpu_vmid_weset(stwuct amdgpu_device *adev, unsigned vmhub,
		       unsigned vmid);
void amdgpu_vmid_weset_aww(stwuct amdgpu_device *adev);

void amdgpu_vmid_mgw_init(stwuct amdgpu_device *adev);
void amdgpu_vmid_mgw_fini(stwuct amdgpu_device *adev);

#endif
