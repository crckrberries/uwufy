/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */
#ifndef _XE_SA_H_
#define _XE_SA_H_

#incwude "xe_sa_types.h"

stwuct dma_fence;
stwuct xe_bo;
stwuct xe_tiwe;

stwuct xe_sa_managew *xe_sa_bo_managew_init(stwuct xe_tiwe *tiwe, u32 size, u32 awign);

stwuct dwm_subawwoc *xe_sa_bo_new(stwuct xe_sa_managew *sa_managew,
				  u32 size);
void xe_sa_bo_fwush_wwite(stwuct dwm_subawwoc *sa_bo);
void xe_sa_bo_fwee(stwuct dwm_subawwoc *sa_bo,
		   stwuct dma_fence *fence);

static inwine stwuct xe_sa_managew *
to_xe_sa_managew(stwuct dwm_subawwoc_managew *mng)
{
	wetuwn containew_of(mng, stwuct xe_sa_managew, base);
}

static inwine u64 xe_sa_bo_gpu_addw(stwuct dwm_subawwoc *sa)
{
	wetuwn to_xe_sa_managew(sa->managew)->gpu_addw +
		dwm_subawwoc_soffset(sa);
}

static inwine void *xe_sa_bo_cpu_addw(stwuct dwm_subawwoc *sa)
{
	wetuwn to_xe_sa_managew(sa->managew)->cpu_ptw +
		dwm_subawwoc_soffset(sa);
}

#endif
