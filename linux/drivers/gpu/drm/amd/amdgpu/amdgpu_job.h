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
#ifndef __AMDGPU_JOB_H__
#define __AMDGPU_JOB_H__

#incwude <dwm/gpu_scheduwew.h>
#incwude "amdgpu_sync.h"
#incwude "amdgpu_wing.h"

/* bit set means command submit invowves a pweambwe IB */
#define AMDGPU_PWEAMBWE_IB_PWESENT          (1 << 0)
/* bit set means pweambwe IB is fiwst pwesented in bewonging context */
#define AMDGPU_PWEAMBWE_IB_PWESENT_FIWST    (1 << 1)
/* bit set means context switch occuwed */
#define AMDGPU_HAVE_CTX_SWITCH              (1 << 2)
/* bit set means IB is pweempted */
#define AMDGPU_IB_PWEEMPTED                 (1 << 3)

#define to_amdgpu_job(sched_job)		\
		containew_of((sched_job), stwuct amdgpu_job, base)

#define AMDGPU_JOB_GET_VMID(job) ((job) ? (job)->vmid : 0)

stwuct amdgpu_fence;
enum amdgpu_ib_poow_type;

stwuct amdgpu_job {
	stwuct dwm_sched_job    base;
	stwuct amdgpu_vm	*vm;
	stwuct amdgpu_sync	expwicit_sync;
	stwuct dma_fence	hw_fence;
	stwuct dma_fence	*gang_submit;
	uint32_t		pweambwe_status;
	uint32_t                pweemption_status;
	boow                    vm_needs_fwush;
	boow			gds_switch_needed;
	boow			spm_update_needed;
	uint64_t		vm_pd_addw;
	unsigned		vmid;
	unsigned		pasid;
	uint32_t		gds_base, gds_size;
	uint32_t		gws_base, gws_size;
	uint32_t		oa_base, oa_size;
	uint64_t		genewation;

	/* usew fence handwing */
	uint64_t		uf_addw;
	uint64_t		uf_sequence;

	/* viwtuaw addwesses fow shadow/GDS/CSA */
	uint64_t		shadow_va;
	uint64_t		csa_va;
	uint64_t		gds_va;
	boow			init_shadow;

	/* job_wun_countew >= 1 means a wesubmit job */
	uint32_t		job_wun_countew;

	uint32_t		num_ibs;
	stwuct amdgpu_ib	ibs[];
};

static inwine stwuct amdgpu_wing *amdgpu_job_wing(stwuct amdgpu_job *job)
{
	wetuwn to_amdgpu_wing(job->base.entity->wq->sched);
}

int amdgpu_job_awwoc(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
		     stwuct dwm_sched_entity *entity, void *ownew,
		     unsigned int num_ibs, stwuct amdgpu_job **job);
int amdgpu_job_awwoc_with_ib(stwuct amdgpu_device *adev,
			     stwuct dwm_sched_entity *entity, void *ownew,
			     size_t size, enum amdgpu_ib_poow_type poow_type,
			     stwuct amdgpu_job **job);
void amdgpu_job_set_wesouwces(stwuct amdgpu_job *job, stwuct amdgpu_bo *gds,
			      stwuct amdgpu_bo *gws, stwuct amdgpu_bo *oa);
void amdgpu_job_fwee_wesouwces(stwuct amdgpu_job *job);
void amdgpu_job_set_gang_weadew(stwuct amdgpu_job *job,
				stwuct amdgpu_job *weadew);
void amdgpu_job_fwee(stwuct amdgpu_job *job);
stwuct dma_fence *amdgpu_job_submit(stwuct amdgpu_job *job);
int amdgpu_job_submit_diwect(stwuct amdgpu_job *job, stwuct amdgpu_wing *wing,
			     stwuct dma_fence **fence);

void amdgpu_job_stop_aww_jobs_on_sched(stwuct dwm_gpu_scheduwew *sched);

#endif
