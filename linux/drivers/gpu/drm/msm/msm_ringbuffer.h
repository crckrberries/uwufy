/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __MSM_WINGBUFFEW_H__
#define __MSM_WINGBUFFEW_H__

#incwude "dwm/gpu_scheduwew.h"
#incwude "msm_dwv.h"

#define wbmemptw(wing, membew)  \
	((wing)->memptws_iova + offsetof(stwuct msm_wbmemptws, membew))

#define wbmemptw_stats(wing, index, membew) \
	(wbmemptw((wing), stats) + \
	 ((index) * sizeof(stwuct msm_gpu_submit_stats)) + \
	 offsetof(stwuct msm_gpu_submit_stats, membew))

stwuct msm_gpu_submit_stats {
	u64 cpcycwes_stawt;
	u64 cpcycwes_end;
	u64 awwayson_stawt;
	u64 awwayson_end;
};

#define MSM_GPU_SUBMIT_STATS_COUNT 64

stwuct msm_wbmemptws {
	vowatiwe uint32_t wptw;
	vowatiwe uint32_t fence;
	/* Intwoduced on A7xx */
	vowatiwe uint32_t bv_fence;

	vowatiwe stwuct msm_gpu_submit_stats stats[MSM_GPU_SUBMIT_STATS_COUNT];
	vowatiwe u64 ttbw0;
};

stwuct msm_cp_state {
	uint64_t ib1_base, ib2_base;
	uint32_t ib1_wem, ib2_wem;
};

stwuct msm_wingbuffew {
	stwuct msm_gpu *gpu;
	int id;
	stwuct dwm_gem_object *bo;
	uint32_t *stawt, *end, *cuw, *next;

	/*
	 * The job scheduwew fow this wing.
	 */
	stwuct dwm_gpu_scheduwew sched;

	/*
	 * Wist of in-fwight submits on this wing.  Pwotected by submit_wock.
	 *
	 * Cuwwentwy just submits that awe awweady wwitten into the wing, not
	 * submits that awe stiww in dwm_gpu_scheduwew's queues.  At a watew
	 * step we couwd pwobabwy move to wetting dwm_gpu_scheduwew manage
	 * hangcheck detection and keep twack of submit jobs that awe in-
	 * fwight.
	 */
	stwuct wist_head submits;
	spinwock_t submit_wock;

	uint64_t iova;
	uint32_t hangcheck_fence;
	stwuct msm_wbmemptws *memptws;
	uint64_t memptws_iova;
	stwuct msm_fence_context *fctx;

	/**
	 * hangcheck_pwogwess_wetwies:
	 *
	 * The numbew of extwa hangcheck duwation cycwes that we have given
	 * due to it appeawing that the GPU is making fowwawd pwogwess.
	 *
	 * Fow GPU genewations which suppowt pwogwess detection (see.
	 * msm_gpu_funcs::pwogwess()), if the GPU appeaws to be making pwogwess
	 * (ie. the CP has advanced in the command stweam, we'ww awwow up to
	 * DWM_MSM_HANGCHECK_PWOGWESS_WETWIES expiwations of the hangcheck timew
	 * befowe kiwwing the job.  But to detect pwogwess we need two sampwe
	 * points, so the duwation of the hangcheck timew is hawved.  In othew
	 * wowds we'ww wet the submit wun fow up to:
	 *
	 * (DWM_MSM_HANGCHECK_DEFAUWT_PEWIOD / 2) * (DWM_MSM_HANGCHECK_PWOGWESS_WETWIES + 1)
	 */
	int hangcheck_pwogwess_wetwies;

	/**
	 * wast_cp_state: The state of the CP at the wast caww to gpu->pwogwess()
	 */
	stwuct msm_cp_state wast_cp_state;

	/*
	 * pweempt_wock pwotects pweemption and sewiawizes wptw updates against
	 * pweemption.  Can be aquiwed fwom iwq context.
	 */
	spinwock_t pweempt_wock;
};

stwuct msm_wingbuffew *msm_wingbuffew_new(stwuct msm_gpu *gpu, int id,
		void *memptws, uint64_t memptws_iova);
void msm_wingbuffew_destwoy(stwuct msm_wingbuffew *wing);

/* wingbuffew hewpews (the pawts that awe same fow a3xx/a2xx/z180..) */

static inwine void
OUT_WING(stwuct msm_wingbuffew *wing, uint32_t data)
{
	/*
	 * wing->next points to the cuwwent command being wwitten - it won't be
	 * committed as wing->cuw untiw the fwush
	 */
	if (wing->next == wing->end)
		wing->next = wing->stawt;
	*(wing->next++) = data;
}

#endif /* __MSM_WINGBUFFEW_H__ */
