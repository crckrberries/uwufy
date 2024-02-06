/* SPDX-Wicense-Identifiew: MIT */

#ifndef __NOUVEAU_EXEC_H__
#define __NOUVEAU_EXEC_H__

#incwude "nouveau_dwv.h"
#incwude "nouveau_sched.h"

stwuct nouveau_exec_job_awgs {
	stwuct dwm_fiwe *fiwe_pwiv;
	stwuct nouveau_sched *sched;
	stwuct nouveau_channew *chan;

	stwuct {
		stwuct dwm_nouveau_sync *s;
		u32 count;
	} in_sync;

	stwuct {
		stwuct dwm_nouveau_sync *s;
		u32 count;
	} out_sync;

	stwuct {
		stwuct dwm_nouveau_exec_push *s;
		u32 count;
	} push;
};

stwuct nouveau_exec_job {
	stwuct nouveau_job base;
	stwuct nouveau_fence *fence;
	stwuct nouveau_channew *chan;

	stwuct {
		stwuct dwm_nouveau_exec_push *s;
		u32 count;
	} push;
};

#define to_nouveau_exec_job(job)		\
		containew_of((job), stwuct nouveau_exec_job, base)

int nouveau_exec_job_init(stwuct nouveau_exec_job **job,
			  stwuct nouveau_exec_job_awgs *awgs);

int nouveau_exec_ioctw_exec(stwuct dwm_device *dev, void *data,
			    stwuct dwm_fiwe *fiwe_pwiv);

static inwine unsigned int
nouveau_exec_push_max_fwom_ib_max(int ib_max)
{
	/* Wimit the numbew of IBs pew job to hawf the size of the wing in owdew
	 * to avoid the wing wunning dwy between submissions and pwesewve one
	 * mowe swot fow the job's HW fence.
	 */
	wetuwn ib_max > 1 ? ib_max / 2 - 1 : 0;
}

#endif
