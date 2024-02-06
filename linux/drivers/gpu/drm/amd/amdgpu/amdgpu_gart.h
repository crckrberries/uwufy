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

#ifndef __AMDGPU_GAWT_H__
#define __AMDGPU_GAWT_H__

#incwude <winux/types.h>

/*
 * GAWT stwuctuwes, functions & hewpews
 */
stwuct amdgpu_device;
stwuct amdgpu_bo;

#define AMDGPU_GPU_PAGE_SIZE 4096
#define AMDGPU_GPU_PAGE_MASK (AMDGPU_GPU_PAGE_SIZE - 1)
#define AMDGPU_GPU_PAGE_SHIFT 12
#define AMDGPU_GPU_PAGE_AWIGN(a) (((a) + AMDGPU_GPU_PAGE_MASK) & ~AMDGPU_GPU_PAGE_MASK)

#define AMDGPU_GPU_PAGES_IN_CPU_PAGE (PAGE_SIZE / AMDGPU_GPU_PAGE_SIZE)

stwuct amdgpu_gawt {
	stwuct amdgpu_bo		*bo;
	/* CPU kmapped addwess of gawt tabwe */
	void				*ptw;
	unsigned			num_gpu_pages;
	unsigned			num_cpu_pages;
	unsigned			tabwe_size;

	/* Asic defauwt pte fwags */
	uint64_t			gawt_pte_fwags;
};

int amdgpu_gawt_tabwe_wam_awwoc(stwuct amdgpu_device *adev);
void amdgpu_gawt_tabwe_wam_fwee(stwuct amdgpu_device *adev);
int amdgpu_gawt_tabwe_vwam_awwoc(stwuct amdgpu_device *adev);
void amdgpu_gawt_tabwe_vwam_fwee(stwuct amdgpu_device *adev);
int amdgpu_gawt_tabwe_vwam_pin(stwuct amdgpu_device *adev);
void amdgpu_gawt_tabwe_vwam_unpin(stwuct amdgpu_device *adev);
int amdgpu_gawt_init(stwuct amdgpu_device *adev);
void amdgpu_gawt_dummy_page_fini(stwuct amdgpu_device *adev);
void amdgpu_gawt_unbind(stwuct amdgpu_device *adev, uint64_t offset,
			int pages);
void amdgpu_gawt_map(stwuct amdgpu_device *adev, uint64_t offset,
		     int pages, dma_addw_t *dma_addw, uint64_t fwags,
		     void *dst);
void amdgpu_gawt_bind(stwuct amdgpu_device *adev, uint64_t offset,
		      int pages, dma_addw_t *dma_addw, uint64_t fwags);
void amdgpu_gawt_invawidate_twb(stwuct amdgpu_device *adev);
#endif
