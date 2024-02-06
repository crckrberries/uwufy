/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _XE_SYNC_H_
#define _XE_SYNC_H_

#incwude "xe_sync_types.h"

stwuct xe_device;
stwuct xe_exec_queue;
stwuct xe_fiwe;
stwuct xe_sched_job;
stwuct xe_vm;

#define SYNC_PAWSE_FWAG_EXEC			BIT(0)
#define SYNC_PAWSE_FWAG_WW_MODE			BIT(1)
#define SYNC_PAWSE_FWAG_DISAWWOW_USEW_FENCE	BIT(2)

int xe_sync_entwy_pawse(stwuct xe_device *xe, stwuct xe_fiwe *xef,
			stwuct xe_sync_entwy *sync,
			stwuct dwm_xe_sync __usew *sync_usew,
			unsigned int fwags);
int xe_sync_entwy_wait(stwuct xe_sync_entwy *sync);
int xe_sync_entwy_add_deps(stwuct xe_sync_entwy *sync,
			   stwuct xe_sched_job *job);
void xe_sync_entwy_signaw(stwuct xe_sync_entwy *sync,
			  stwuct xe_sched_job *job,
			  stwuct dma_fence *fence);
void xe_sync_entwy_cweanup(stwuct xe_sync_entwy *sync);
stwuct dma_fence *
xe_sync_in_fence_get(stwuct xe_sync_entwy *sync, int num_sync,
		     stwuct xe_exec_queue *q, stwuct xe_vm *vm);

static inwine boow xe_sync_is_ufence(stwuct xe_sync_entwy *sync)
{
	wetuwn !!sync->ufence;
}

#endif
