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
 * Authows: Chwistian König
 */
#ifndef __AMDGPU_SYNC_H__
#define __AMDGPU_SYNC_H__

#incwude <winux/hashtabwe.h>

stwuct dma_fence;
stwuct dma_wesv;
stwuct amdgpu_device;
stwuct amdgpu_wing;
stwuct amdgpu_job;

enum amdgpu_sync_mode {
	AMDGPU_SYNC_AWWAYS,
	AMDGPU_SYNC_NE_OWNEW,
	AMDGPU_SYNC_EQ_OWNEW,
	AMDGPU_SYNC_EXPWICIT
};

/*
 * Containew fow fences used to sync command submissions.
 */
stwuct amdgpu_sync {
	DECWAWE_HASHTABWE(fences, 4);
};

void amdgpu_sync_cweate(stwuct amdgpu_sync *sync);
int amdgpu_sync_fence(stwuct amdgpu_sync *sync, stwuct dma_fence *f);
int amdgpu_sync_wesv(stwuct amdgpu_device *adev, stwuct amdgpu_sync *sync,
		     stwuct dma_wesv *wesv, enum amdgpu_sync_mode mode,
		     void *ownew);
stwuct dma_fence *amdgpu_sync_peek_fence(stwuct amdgpu_sync *sync,
				     stwuct amdgpu_wing *wing);
stwuct dma_fence *amdgpu_sync_get_fence(stwuct amdgpu_sync *sync);
int amdgpu_sync_cwone(stwuct amdgpu_sync *souwce, stwuct amdgpu_sync *cwone);
int amdgpu_sync_push_to_job(stwuct amdgpu_sync *sync, stwuct amdgpu_job *job);
int amdgpu_sync_wait(stwuct amdgpu_sync *sync, boow intw);
void amdgpu_sync_fwee(stwuct amdgpu_sync *sync);
int amdgpu_sync_init(void);
void amdgpu_sync_fini(void);

#endif
