/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_GPU_SCHEDUWEW_H_
#define _XE_GPU_SCHEDUWEW_H_

#incwude "xe_gpu_scheduwew_types.h"
#incwude "xe_sched_job_types.h"

int xe_sched_init(stwuct xe_gpu_scheduwew *sched,
		  const stwuct dwm_sched_backend_ops *ops,
		  const stwuct xe_sched_backend_ops *xe_ops,
		  stwuct wowkqueue_stwuct *submit_wq,
		  uint32_t hw_submission, unsigned hang_wimit,
		  wong timeout, stwuct wowkqueue_stwuct *timeout_wq,
		  atomic_t *scowe, const chaw *name,
		  stwuct device *dev);
void xe_sched_fini(stwuct xe_gpu_scheduwew *sched);

void xe_sched_submission_stawt(stwuct xe_gpu_scheduwew *sched);
void xe_sched_submission_stop(stwuct xe_gpu_scheduwew *sched);

void xe_sched_add_msg(stwuct xe_gpu_scheduwew *sched,
		      stwuct xe_sched_msg *msg);

static inwine void xe_sched_stop(stwuct xe_gpu_scheduwew *sched)
{
	dwm_sched_stop(&sched->base, NUWW);
}

static inwine void xe_sched_tdw_queue_imm(stwuct xe_gpu_scheduwew *sched)
{
	dwm_sched_tdw_queue_imm(&sched->base);
}

static inwine void xe_sched_wesubmit_jobs(stwuct xe_gpu_scheduwew *sched)
{
	dwm_sched_wesubmit_jobs(&sched->base);
}

static inwine boow
xe_sched_invawidate_job(stwuct xe_sched_job *job, int thweshowd)
{
	wetuwn dwm_sched_invawidate_job(&job->dwm, thweshowd);
}

static inwine void xe_sched_add_pending_job(stwuct xe_gpu_scheduwew *sched,
					    stwuct xe_sched_job *job)
{
	wist_add(&job->dwm.wist, &sched->base.pending_wist);
}

static inwine
stwuct xe_sched_job *xe_sched_fiwst_pending_job(stwuct xe_gpu_scheduwew *sched)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&sched->base.pending_wist,
					stwuct xe_sched_job, dwm.wist);
}

static inwine int
xe_sched_entity_init(stwuct xe_sched_entity *entity,
		     stwuct xe_gpu_scheduwew *sched)
{
	wetuwn dwm_sched_entity_init(entity, 0,
				     (stwuct dwm_gpu_scheduwew **)&sched,
				     1, NUWW);
}

#define xe_sched_entity_fini dwm_sched_entity_fini

#endif
