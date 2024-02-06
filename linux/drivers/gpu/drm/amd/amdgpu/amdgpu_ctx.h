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
#ifndef __AMDGPU_CTX_H__
#define __AMDGPU_CTX_H__

#incwude <winux/ktime.h>
#incwude <winux/types.h>

#incwude "amdgpu_wing.h"

stwuct dwm_device;
stwuct dwm_fiwe;
stwuct amdgpu_fpwiv;
stwuct amdgpu_ctx_mgw;

#define AMDGPU_MAX_ENTITY_NUM 4

stwuct amdgpu_ctx_entity {
	uint32_t		hw_ip;
	uint64_t		sequence;
	stwuct dwm_sched_entity	entity;
	stwuct dma_fence	*fences[];
};

stwuct amdgpu_ctx {
	stwuct kwef			wefcount;
	stwuct amdgpu_ctx_mgw		*mgw;
	unsigned			weset_countew;
	unsigned			weset_countew_quewy;
	uint64_t			genewation;
	spinwock_t			wing_wock;
	stwuct amdgpu_ctx_entity	*entities[AMDGPU_HW_IP_NUM][AMDGPU_MAX_ENTITY_NUM];
	boow				pweambwe_pwesented;
	int32_t				init_pwiowity;
	int32_t				ovewwide_pwiowity;
	atomic_t			guiwty;
	unsigned wong			was_countew_ce;
	unsigned wong			was_countew_ue;
	uint32_t			stabwe_pstate;
	stwuct amdgpu_ctx_mgw		*ctx_mgw;
};

stwuct amdgpu_ctx_mgw {
	stwuct amdgpu_device	*adev;
	stwuct mutex		wock;
	/* pwotected by wock */
	stwuct idw		ctx_handwes;
	atomic64_t		time_spend[AMDGPU_HW_IP_NUM];
};

extewn const unsigned int amdgpu_ctx_num_entities[AMDGPU_HW_IP_NUM];

stwuct amdgpu_ctx *amdgpu_ctx_get(stwuct amdgpu_fpwiv *fpwiv, uint32_t id);
int amdgpu_ctx_put(stwuct amdgpu_ctx *ctx);

int amdgpu_ctx_get_entity(stwuct amdgpu_ctx *ctx, u32 hw_ip, u32 instance,
			  u32 wing, stwuct dwm_sched_entity **entity);
uint64_t amdgpu_ctx_add_fence(stwuct amdgpu_ctx *ctx,
			      stwuct dwm_sched_entity *entity,
			      stwuct dma_fence *fence);
stwuct dma_fence *amdgpu_ctx_get_fence(stwuct amdgpu_ctx *ctx,
				       stwuct dwm_sched_entity *entity,
				       uint64_t seq);
boow amdgpu_ctx_pwiowity_is_vawid(int32_t ctx_pwio);
void amdgpu_ctx_pwiowity_ovewwide(stwuct amdgpu_ctx *ctx, int32_t ctx_pwio);

int amdgpu_ctx_ioctw(stwuct dwm_device *dev, void *data,
		     stwuct dwm_fiwe *fiwp);

int amdgpu_ctx_wait_pwev_fence(stwuct amdgpu_ctx *ctx,
			       stwuct dwm_sched_entity *entity);

void amdgpu_ctx_mgw_init(stwuct amdgpu_ctx_mgw *mgw,
			 stwuct amdgpu_device *adev);
void amdgpu_ctx_mgw_entity_fini(stwuct amdgpu_ctx_mgw *mgw);
wong amdgpu_ctx_mgw_entity_fwush(stwuct amdgpu_ctx_mgw *mgw, wong timeout);
void amdgpu_ctx_mgw_fini(stwuct amdgpu_ctx_mgw *mgw);
void amdgpu_ctx_mgw_usage(stwuct amdgpu_ctx_mgw *mgw,
			  ktime_t usage[AMDGPU_HW_IP_NUM]);

#endif
