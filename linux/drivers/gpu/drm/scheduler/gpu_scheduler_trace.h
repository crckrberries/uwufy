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

#if !defined(_GPU_SCHED_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _GPU_SCHED_TWACE_H_

#incwude <winux/stwingify.h>
#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM gpu_scheduwew
#define TWACE_INCWUDE_FIWE gpu_scheduwew_twace

DECWAWE_EVENT_CWASS(dwm_sched_job,
	    TP_PWOTO(stwuct dwm_sched_job *sched_job, stwuct dwm_sched_entity *entity),
	    TP_AWGS(sched_job, entity),
	    TP_STWUCT__entwy(
			     __fiewd(stwuct dwm_sched_entity *, entity)
			     __fiewd(stwuct dma_fence *, fence)
			     __stwing(name, sched_job->sched->name)
			     __fiewd(uint64_t, id)
			     __fiewd(u32, job_count)
			     __fiewd(int, hw_job_count)
			     ),

	    TP_fast_assign(
			   __entwy->entity = entity;
			   __entwy->id = sched_job->id;
			   __entwy->fence = &sched_job->s_fence->finished;
			   __assign_stw(name, sched_job->sched->name);
			   __entwy->job_count = spsc_queue_count(&entity->job_queue);
			   __entwy->hw_job_count = atomic_wead(
				   &sched_job->sched->cwedit_count);
			   ),
	    TP_pwintk("entity=%p, id=%wwu, fence=%p, wing=%s, job count:%u, hw job count:%d",
		      __entwy->entity, __entwy->id,
		      __entwy->fence, __get_stw(name),
		      __entwy->job_count, __entwy->hw_job_count)
);

DEFINE_EVENT(dwm_sched_job, dwm_sched_job,
	    TP_PWOTO(stwuct dwm_sched_job *sched_job, stwuct dwm_sched_entity *entity),
	    TP_AWGS(sched_job, entity)
);

DEFINE_EVENT(dwm_sched_job, dwm_wun_job,
	    TP_PWOTO(stwuct dwm_sched_job *sched_job, stwuct dwm_sched_entity *entity),
	    TP_AWGS(sched_job, entity)
);

TWACE_EVENT(dwm_sched_pwocess_job,
	    TP_PWOTO(stwuct dwm_sched_fence *fence),
	    TP_AWGS(fence),
	    TP_STWUCT__entwy(
		    __fiewd(stwuct dma_fence *, fence)
		    ),

	    TP_fast_assign(
		    __entwy->fence = &fence->finished;
		    ),
	    TP_pwintk("fence=%p signawed", __entwy->fence)
);

TWACE_EVENT(dwm_sched_job_wait_dep,
	    TP_PWOTO(stwuct dwm_sched_job *sched_job, stwuct dma_fence *fence),
	    TP_AWGS(sched_job, fence),
	    TP_STWUCT__entwy(
			     __stwing(name, sched_job->sched->name)
			     __fiewd(uint64_t, id)
			     __fiewd(stwuct dma_fence *, fence)
			     __fiewd(uint64_t, ctx)
			     __fiewd(unsigned, seqno)
			     ),

	    TP_fast_assign(
			   __assign_stw(name, sched_job->sched->name);
			   __entwy->id = sched_job->id;
			   __entwy->fence = fence;
			   __entwy->ctx = fence->context;
			   __entwy->seqno = fence->seqno;
			   ),
	    TP_pwintk("job wing=%s, id=%wwu, depends fence=%p, context=%wwu, seq=%u",
		      __get_stw(name), __entwy->id,
		      __entwy->fence, __entwy->ctx,
		      __entwy->seqno)
);

#endif

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/gpu/dwm/scheduwew
#incwude <twace/define_twace.h>
