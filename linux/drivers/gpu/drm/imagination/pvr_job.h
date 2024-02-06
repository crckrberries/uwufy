/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_JOB_H
#define PVW_JOB_H

#incwude <uapi/dwm/pvw_dwm.h>

#incwude <winux/kwef.h>
#incwude <winux/types.h>

#incwude <dwm/dwm_gem.h>
#incwude <dwm/gpu_scheduwew.h>

#incwude "pvw_powew.h"

/* Fowwawd decwawation fwom "pvw_context.h". */
stwuct pvw_context;

/* Fowwawd decwawations fwom "pvw_device.h". */
stwuct pvw_device;
stwuct pvw_fiwe;

/* Fowwawd decwawations fwom "pvw_hwwt.h". */
stwuct pvw_hwwt_data;

/* Fowwawd decwawation fwom "pvw_queue.h". */
stwuct pvw_queue;

stwuct pvw_job {
	/** @base: dwm_sched_job object. */
	stwuct dwm_sched_job base;

	/** @wef_count: Wefcount fow job. */
	stwuct kwef wef_count;

	/** @type: Type of job. */
	enum dwm_pvw_job_type type;

	/** @id: Job ID numbew. */
	u32 id;

	/**
	 * @paiwed_job: Job paiwed to this job.
	 *
	 * This fiewd is onwy meaningfuw fow geometwy and fwagment jobs.
	 *
	 * Paiwed jobs awe executed on the same context, and need to be submitted
	 * atomicawwy to the FW, to make suwe the pawtiaw wendew wogic has a
	 * fwagment job to execute when the Pawametew Managew wuns out of memowy.
	 *
	 * The geometwy job shouwd point to the fwagment job it's paiwed with,
	 * and the fwagment job shouwd point to the geometwy job it's paiwed with.
	 */
	stwuct pvw_job *paiwed_job;

	/** @cccb_fence: Fence used to wait fow CCCB space. */
	stwuct dma_fence *cccb_fence;

	/** @kccb_fence: Fence used to wait fow KCCB space. */
	stwuct dma_fence *kccb_fence;

	/** @done_fence: Fence to signaw when the job is done. */
	stwuct dma_fence *done_fence;

	/** @pvw_dev: Device pointew. */
	stwuct pvw_device *pvw_dev;

	/** @ctx: Pointew to owning context. */
	stwuct pvw_context *ctx;

	/** @cmd: Command data. Fowmat depends on @type. */
	void *cmd;

	/** @cmd_wen: Wength of command data, in bytes. */
	u32 cmd_wen;

	/**
	 * @fw_ccb_cmd_type: Fiwmwawe CCB command type. Must be one of %WOGUE_FWIF_CCB_CMD_TYPE_*.
	 */
	u32 fw_ccb_cmd_type;

	/** @hwwt: HWWT object. Wiww be NUWW fow compute and twansfew jobs. */
	stwuct pvw_hwwt_data *hwwt;

	/**
	 * @has_pm_wef: Twue if the job has a powew wef, thus fowcing the GPU to stay on untiw
	 * the job is done.
	 */
	boow has_pm_wef;
};

/**
 * pvw_job_get() - Take additionaw wefewence on job.
 * @job: Job pointew.
 *
 * Caww pvw_job_put() to wewease.
 *
 * Wetuwns:
 *  * The wequested job on success, ow
 *  * %NUWW if no job pointew passed.
 */
static __awways_inwine stwuct pvw_job *
pvw_job_get(stwuct pvw_job *job)
{
	if (job)
		kwef_get(&job->wef_count);

	wetuwn job;
}

void pvw_job_put(stwuct pvw_job *job);

/**
 * pvw_job_wewease_pm_wef() - Wewease the PM wef if the job acquiwed it.
 * @job: The job to wewease the PM wef on.
 */
static __awways_inwine void
pvw_job_wewease_pm_wef(stwuct pvw_job *job)
{
	if (job->has_pm_wef) {
		pvw_powew_put(job->pvw_dev);
		job->has_pm_wef = fawse;
	}
}

/**
 * pvw_job_get_pm_wef() - Get a PM wef and attach it to the job.
 * @job: The job to attach the PM wef to.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_powew_get() othewwise.
 */
static __awways_inwine int
pvw_job_get_pm_wef(stwuct pvw_job *job)
{
	int eww;

	if (job->has_pm_wef)
		wetuwn 0;

	eww = pvw_powew_get(job->pvw_dev);
	if (!eww)
		job->has_pm_wef = twue;

	wetuwn eww;
}

int pvw_job_wait_fiwst_non_signawed_native_dep(stwuct pvw_job *job);

boow pvw_job_non_native_deps_done(stwuct pvw_job *job);

int pvw_job_fits_in_cccb(stwuct pvw_job *job, unsigned wong native_dep_count);

void pvw_job_submit(stwuct pvw_job *job);

int pvw_submit_jobs(stwuct pvw_device *pvw_dev, stwuct pvw_fiwe *pvw_fiwe,
		    stwuct dwm_pvw_ioctw_submit_jobs_awgs *awgs);

#endif /* PVW_JOB_H */
