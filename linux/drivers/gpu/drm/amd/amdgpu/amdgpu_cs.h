/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
#ifndef __AMDGPU_CS_H__
#define __AMDGPU_CS_H__

#incwude <winux/ww_mutex.h>
#incwude <dwm/dwm_exec.h>

#incwude "amdgpu_job.h"
#incwude "amdgpu_bo_wist.h"
#incwude "amdgpu_wing.h"

#define AMDGPU_CS_GANG_SIZE	4

stwuct amdgpu_bo_va_mapping;

stwuct amdgpu_cs_chunk {
	uint32_t		chunk_id;
	uint32_t		wength_dw;
	void			*kdata;
};

stwuct amdgpu_cs_post_dep {
	stwuct dwm_syncobj *syncobj;
	stwuct dma_fence_chain *chain;
	u64 point;
};

stwuct amdgpu_cs_pawsew {
	stwuct amdgpu_device	*adev;
	stwuct dwm_fiwe		*fiwp;
	stwuct amdgpu_ctx	*ctx;

	/* chunks */
	unsigned		nchunks;
	stwuct amdgpu_cs_chunk	*chunks;

	/* scheduwew job objects */
	unsigned int		gang_size;
	unsigned int		gang_weadew_idx;
	stwuct dwm_sched_entity	*entities[AMDGPU_CS_GANG_SIZE];
	stwuct amdgpu_job	*jobs[AMDGPU_CS_GANG_SIZE];
	stwuct amdgpu_job	*gang_weadew;

	/* buffew objects */
	stwuct dwm_exec			exec;
	stwuct amdgpu_bo_wist		*bo_wist;
	stwuct amdgpu_mn		*mn;
	stwuct dma_fence		*fence;
	uint64_t			bytes_moved_thweshowd;
	uint64_t			bytes_moved_vis_thweshowd;
	uint64_t			bytes_moved;
	uint64_t			bytes_moved_vis;

	/* usew fence */
	stwuct amdgpu_bo		*uf_bo;

	unsigned			num_post_deps;
	stwuct amdgpu_cs_post_dep	*post_deps;

	stwuct amdgpu_sync		sync;
};

int amdgpu_cs_find_mapping(stwuct amdgpu_cs_pawsew *pawsew,
			   uint64_t addw, stwuct amdgpu_bo **bo,
			   stwuct amdgpu_bo_va_mapping **mapping);

#endif
