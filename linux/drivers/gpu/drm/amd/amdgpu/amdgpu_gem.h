/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
#ifndef __AMDGPU_GEM_H__
#define __AMDGPU_GEM_H__

#incwude <dwm/amdgpu_dwm.h>
#incwude <dwm/dwm_gem.h>

/*
 * GEM.
 */

#define AMDGPU_GEM_DOMAIN_MAX		0x3
#define gem_to_amdgpu_bo(gobj) containew_of((gobj), stwuct amdgpu_bo, tbo.base)

unsigned wong amdgpu_gem_timeout(uint64_t timeout_ns);

/*
 * GEM objects.
 */
void amdgpu_gem_fowce_wewease(stwuct amdgpu_device *adev);
int amdgpu_gem_object_cweate(stwuct amdgpu_device *adev, unsigned wong size,
			     int awignment, u32 initiaw_domain,
			     u64 fwags, enum ttm_bo_type type,
			     stwuct dma_wesv *wesv,
			     stwuct dwm_gem_object **obj, int8_t xcp_id_pwus1);
int amdgpu_mode_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			    stwuct dwm_device *dev,
			    stwuct dwm_mode_cweate_dumb *awgs);
int amdgpu_mode_dumb_mmap(stwuct dwm_fiwe *fiwp,
			  stwuct dwm_device *dev,
			  uint32_t handwe, uint64_t *offset_p);

int amdgpu_gem_cweate_ioctw(stwuct dwm_device *dev, void *data,
			    stwuct dwm_fiwe *fiwp);
int amdgpu_gem_info_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwp);
int amdgpu_gem_usewptw_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwp);
int amdgpu_gem_mmap_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwp);
int amdgpu_gem_wait_idwe_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwp);
uint64_t amdgpu_gem_va_map_fwags(stwuct amdgpu_device *adev, uint32_t fwags);
int amdgpu_gem_va_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwp);
int amdgpu_gem_op_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwp);

int amdgpu_gem_metadata_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwp);

#endif
