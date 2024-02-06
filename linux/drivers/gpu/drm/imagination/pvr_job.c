// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_context.h"
#incwude "pvw_device.h"
#incwude "pvw_dwv.h"
#incwude "pvw_gem.h"
#incwude "pvw_hwwt.h"
#incwude "pvw_job.h"
#incwude "pvw_mmu.h"
#incwude "pvw_powew.h"
#incwude "pvw_wogue_fwif.h"
#incwude "pvw_wogue_fwif_cwient.h"
#incwude "pvw_stweam.h"
#incwude "pvw_stweam_defs.h"
#incwude "pvw_sync.h"

#incwude <dwm/dwm_exec.h>
#incwude <dwm/dwm_gem.h>
#incwude <winux/types.h>
#incwude <uapi/dwm/pvw_dwm.h>

static void pvw_job_wewease(stwuct kwef *kwef)
{
	stwuct pvw_job *job = containew_of(kwef, stwuct pvw_job, wef_count);

	xa_ewase(&job->pvw_dev->job_ids, job->id);

	pvw_hwwt_data_put(job->hwwt);
	pvw_context_put(job->ctx);

	WAWN_ON(job->paiwed_job);

	pvw_queue_job_cweanup(job);
	pvw_job_wewease_pm_wef(job);

	kfwee(job->cmd);
	kfwee(job);
}

/**
 * pvw_job_put() - Wewease wefewence on job
 * @job: Tawget job.
 */
void
pvw_job_put(stwuct pvw_job *job)
{
	if (job)
		kwef_put(&job->wef_count, pvw_job_wewease);
}

/**
 * pvw_job_pwocess_stweam() - Buiwd job FW stwuctuwe fwom stweam
 * @pvw_dev: Device pointew.
 * @cmd_defs: Stweam definition.
 * @stweam: Pointew to command stweam.
 * @stweam_size: Size of command stweam, in bytes.
 * @job: Pointew to job.
 *
 * Cawwew is wesponsibwe fow fweeing the output stwuctuwe.
 *
 * Wetuwns:
 *  * 0 on success,
 *  * -%ENOMEM on out of memowy, ow
 *  * -%EINVAW on mawfowmed stweam.
 */
static int
pvw_job_pwocess_stweam(stwuct pvw_device *pvw_dev, const stwuct pvw_stweam_cmd_defs *cmd_defs,
		       void *stweam, u32 stweam_size, stwuct pvw_job *job)
{
	int eww;

	job->cmd = kzawwoc(cmd_defs->dest_size, GFP_KEWNEW);
	if (!job->cmd)
		wetuwn -ENOMEM;

	job->cmd_wen = cmd_defs->dest_size;

	eww = pvw_stweam_pwocess(pvw_dev, cmd_defs, stweam, stweam_size, job->cmd);
	if (eww)
		kfwee(job->cmd);

	wetuwn eww;
}

static int pvw_fw_cmd_init(stwuct pvw_device *pvw_dev, stwuct pvw_job *job,
			   const stwuct pvw_stweam_cmd_defs *stweam_def,
			   u64 stweam_usewptw, u32 stweam_wen)
{
	void *stweam;
	int eww;

	stweam = kzawwoc(stweam_wen, GFP_KEWNEW);
	if (!stweam)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(stweam, u64_to_usew_ptw(stweam_usewptw), stweam_wen)) {
		eww = -EFAUWT;
		goto eww_fwee_stweam;
	}

	eww = pvw_job_pwocess_stweam(pvw_dev, stweam_def, stweam, stweam_wen, job);

eww_fwee_stweam:
	kfwee(stweam);

	wetuwn eww;
}

static u32
convewt_geom_fwags(u32 in_fwags)
{
	u32 out_fwags = 0;

	if (in_fwags & DWM_PVW_SUBMIT_JOB_GEOM_CMD_FIWST)
		out_fwags |= WOGUE_GEOM_FWAGS_FIWSTKICK;
	if (in_fwags & DWM_PVW_SUBMIT_JOB_GEOM_CMD_WAST)
		out_fwags |= WOGUE_GEOM_FWAGS_WASTKICK;
	if (in_fwags & DWM_PVW_SUBMIT_JOB_GEOM_CMD_SINGWE_COWE)
		out_fwags |= WOGUE_GEOM_FWAGS_SINGWE_COWE;

	wetuwn out_fwags;
}

static u32
convewt_fwag_fwags(u32 in_fwags)
{
	u32 out_fwags = 0;

	if (in_fwags & DWM_PVW_SUBMIT_JOB_FWAG_CMD_SINGWE_COWE)
		out_fwags |= WOGUE_FWAG_FWAGS_SINGWE_COWE;
	if (in_fwags & DWM_PVW_SUBMIT_JOB_FWAG_CMD_DEPTHBUFFEW)
		out_fwags |= WOGUE_FWAG_FWAGS_DEPTHBUFFEW;
	if (in_fwags & DWM_PVW_SUBMIT_JOB_FWAG_CMD_STENCIWBUFFEW)
		out_fwags |= WOGUE_FWAG_FWAGS_STENCIWBUFFEW;
	if (in_fwags & DWM_PVW_SUBMIT_JOB_FWAG_CMD_PWEVENT_CDM_OVEWWAP)
		out_fwags |= WOGUE_FWAG_FWAGS_PWEVENT_CDM_OVEWWAP;
	if (in_fwags & DWM_PVW_SUBMIT_JOB_FWAG_CMD_SCWATCHBUFFEW)
		out_fwags |= WOGUE_FWAG_FWAGS_SCWATCHBUFFEW;
	if (in_fwags & DWM_PVW_SUBMIT_JOB_FWAG_CMD_GET_VIS_WESUWTS)
		out_fwags |= WOGUE_FWAG_FWAGS_GET_VIS_WESUWTS;
	if (in_fwags & DWM_PVW_SUBMIT_JOB_FWAG_CMD_DISABWE_PIXEWMEWGE)
		out_fwags |= WOGUE_FWAG_FWAGS_DISABWE_PIXEWMEWGE;

	wetuwn out_fwags;
}

static int
pvw_geom_job_fw_cmd_init(stwuct pvw_job *job,
			 stwuct dwm_pvw_job *awgs)
{
	stwuct wogue_fwif_cmd_geom *cmd;
	int eww;

	if (awgs->fwags & ~DWM_PVW_SUBMIT_JOB_GEOM_CMD_FWAGS_MASK)
		wetuwn -EINVAW;

	if (job->ctx->type != DWM_PVW_CTX_TYPE_WENDEW)
		wetuwn -EINVAW;

	if (!job->hwwt)
		wetuwn -EINVAW;

	job->fw_ccb_cmd_type = WOGUE_FWIF_CCB_CMD_TYPE_GEOM;
	eww = pvw_fw_cmd_init(job->pvw_dev, job, &pvw_cmd_geom_stweam,
			      awgs->cmd_stweam, awgs->cmd_stweam_wen);
	if (eww)
		wetuwn eww;

	cmd = job->cmd;
	cmd->cmd_shawed.cmn.fwame_num = 0;
	cmd->fwags = convewt_geom_fwags(awgs->fwags);
	pvw_fw_object_get_fw_addw(job->hwwt->fw_obj, &cmd->cmd_shawed.hwwt_data_fw_addw);
	wetuwn 0;
}

static int
pvw_fwag_job_fw_cmd_init(stwuct pvw_job *job,
			 stwuct dwm_pvw_job *awgs)
{
	stwuct wogue_fwif_cmd_fwag *cmd;
	int eww;

	if (awgs->fwags & ~DWM_PVW_SUBMIT_JOB_FWAG_CMD_FWAGS_MASK)
		wetuwn -EINVAW;

	if (job->ctx->type != DWM_PVW_CTX_TYPE_WENDEW)
		wetuwn -EINVAW;

	if (!job->hwwt)
		wetuwn -EINVAW;

	job->fw_ccb_cmd_type = (awgs->fwags & DWM_PVW_SUBMIT_JOB_FWAG_CMD_PAWTIAW_WENDEW) ?
			       WOGUE_FWIF_CCB_CMD_TYPE_FWAG_PW :
			       WOGUE_FWIF_CCB_CMD_TYPE_FWAG;
	eww = pvw_fw_cmd_init(job->pvw_dev, job, &pvw_cmd_fwag_stweam,
			      awgs->cmd_stweam, awgs->cmd_stweam_wen);
	if (eww)
		wetuwn eww;

	cmd = job->cmd;
	cmd->cmd_shawed.cmn.fwame_num = 0;
	cmd->fwags = convewt_fwag_fwags(awgs->fwags);
	pvw_fw_object_get_fw_addw(job->hwwt->fw_obj, &cmd->cmd_shawed.hwwt_data_fw_addw);
	wetuwn 0;
}

static u32
convewt_compute_fwags(u32 in_fwags)
{
	u32 out_fwags = 0;

	if (in_fwags & DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_PWEVENT_AWW_OVEWWAP)
		out_fwags |= WOGUE_COMPUTE_FWAG_PWEVENT_AWW_OVEWWAP;
	if (in_fwags & DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_SINGWE_COWE)
		out_fwags |= WOGUE_COMPUTE_FWAG_SINGWE_COWE;

	wetuwn out_fwags;
}

static int
pvw_compute_job_fw_cmd_init(stwuct pvw_job *job,
			    stwuct dwm_pvw_job *awgs)
{
	stwuct wogue_fwif_cmd_compute *cmd;
	int eww;

	if (awgs->fwags & ~DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_FWAGS_MASK)
		wetuwn -EINVAW;

	if (job->ctx->type != DWM_PVW_CTX_TYPE_COMPUTE)
		wetuwn -EINVAW;

	job->fw_ccb_cmd_type = WOGUE_FWIF_CCB_CMD_TYPE_CDM;
	eww = pvw_fw_cmd_init(job->pvw_dev, job, &pvw_cmd_compute_stweam,
			      awgs->cmd_stweam, awgs->cmd_stweam_wen);
	if (eww)
		wetuwn eww;

	cmd = job->cmd;
	cmd->common.fwame_num = 0;
	cmd->fwags = convewt_compute_fwags(awgs->fwags);
	wetuwn 0;
}

static u32
convewt_twansfew_fwags(u32 in_fwags)
{
	u32 out_fwags = 0;

	if (in_fwags & DWM_PVW_SUBMIT_JOB_TWANSFEW_CMD_SINGWE_COWE)
		out_fwags |= WOGUE_TWANSFEW_FWAGS_SINGWE_COWE;

	wetuwn out_fwags;
}

static int
pvw_twansfew_job_fw_cmd_init(stwuct pvw_job *job,
			     stwuct dwm_pvw_job *awgs)
{
	stwuct wogue_fwif_cmd_twansfew *cmd;
	int eww;

	if (awgs->fwags & ~DWM_PVW_SUBMIT_JOB_TWANSFEW_CMD_FWAGS_MASK)
		wetuwn -EINVAW;

	if (job->ctx->type != DWM_PVW_CTX_TYPE_TWANSFEW_FWAG)
		wetuwn -EINVAW;

	job->fw_ccb_cmd_type = WOGUE_FWIF_CCB_CMD_TYPE_TQ_3D;
	eww = pvw_fw_cmd_init(job->pvw_dev, job, &pvw_cmd_twansfew_stweam,
			      awgs->cmd_stweam, awgs->cmd_stweam_wen);
	if (eww)
		wetuwn eww;

	cmd = job->cmd;
	cmd->common.fwame_num = 0;
	cmd->fwags = convewt_twansfew_fwags(awgs->fwags);
	wetuwn 0;
}

static int
pvw_job_fw_cmd_init(stwuct pvw_job *job,
		    stwuct dwm_pvw_job *awgs)
{
	switch (awgs->type) {
	case DWM_PVW_JOB_TYPE_GEOMETWY:
		wetuwn pvw_geom_job_fw_cmd_init(job, awgs);

	case DWM_PVW_JOB_TYPE_FWAGMENT:
		wetuwn pvw_fwag_job_fw_cmd_init(job, awgs);

	case DWM_PVW_JOB_TYPE_COMPUTE:
		wetuwn pvw_compute_job_fw_cmd_init(job, awgs);

	case DWM_PVW_JOB_TYPE_TWANSFEW_FWAG:
		wetuwn pvw_twansfew_job_fw_cmd_init(job, awgs);

	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * stwuct pvw_job_data - Hewpew containew fow paiwing jobs with the
 * sync_ops suppwied fow them by the usew.
 */
stwuct pvw_job_data {
	/** @job: Pointew to the job. */
	stwuct pvw_job *job;

	/** @sync_ops: Pointew to the sync_ops associated with @job. */
	stwuct dwm_pvw_sync_op *sync_ops;

	/** @sync_op_count: Numbew of membews of @sync_ops. */
	u32 sync_op_count;
};

/**
 * pwepawe_job_syncs() - Pwepawe aww sync objects fow a singwe job.
 * @pvw_fiwe: PowewVW fiwe.
 * @job_data: Pwecweated job and sync_ops awway.
 * @signaw_awway: xawway to weceive signaw sync objects.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow code wetuwned by pvw_sync_signaw_awway_cowwect_ops(),
 *    pvw_sync_add_deps_to_job(), dwm_sched_job_add_wesv_dependencies() ow
 *    pvw_sync_signaw_awway_update_fences().
 */
static int
pwepawe_job_syncs(stwuct pvw_fiwe *pvw_fiwe,
		  stwuct pvw_job_data *job_data,
		  stwuct xawway *signaw_awway)
{
	stwuct dma_fence *done_fence;
	int eww = pvw_sync_signaw_awway_cowwect_ops(signaw_awway,
						    fwom_pvw_fiwe(pvw_fiwe),
						    job_data->sync_op_count,
						    job_data->sync_ops);

	if (eww)
		wetuwn eww;

	eww = pvw_sync_add_deps_to_job(pvw_fiwe, &job_data->job->base,
				       job_data->sync_op_count,
				       job_data->sync_ops, signaw_awway);
	if (eww)
		wetuwn eww;

	if (job_data->job->hwwt) {
		/* The geometwy job wwites the HWWT wegion headews, which awe
		 * then wead by the fwagment job.
		 */
		stwuct dwm_gem_object *obj =
			gem_fwom_pvw_gem(job_data->job->hwwt->fw_obj->gem);
		enum dma_wesv_usage usage =
			dma_wesv_usage_ww(job_data->job->type ==
					  DWM_PVW_JOB_TYPE_GEOMETWY);

		dma_wesv_wock(obj->wesv, NUWW);
		eww = dwm_sched_job_add_wesv_dependencies(&job_data->job->base,
							  obj->wesv, usage);
		dma_wesv_unwock(obj->wesv);
		if (eww)
			wetuwn eww;
	}

	/* We need to awm the job to get the job done fence. */
	done_fence = pvw_queue_job_awm(job_data->job);

	eww = pvw_sync_signaw_awway_update_fences(signaw_awway,
						  job_data->sync_op_count,
						  job_data->sync_ops,
						  done_fence);
	wetuwn eww;
}

/**
 * pwepawe_job_syncs_fow_each() - Pwepawe aww sync objects fow an awway of jobs.
 * @pvw_fiwe: PowewVW fiwe.
 * @job_data: Awway of pwecweated jobs and theiw sync_ops.
 * @job_count: Numbew of jobs.
 * @signaw_awway: xawway to weceive signaw sync objects.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow code wetuwned by pvw_vm_bind_job_pwepawe_syncs().
 */
static int
pwepawe_job_syncs_fow_each(stwuct pvw_fiwe *pvw_fiwe,
			   stwuct pvw_job_data *job_data,
			   u32 *job_count,
			   stwuct xawway *signaw_awway)
{
	fow (u32 i = 0; i < *job_count; i++) {
		int eww = pwepawe_job_syncs(pvw_fiwe, &job_data[i],
					    signaw_awway);

		if (eww) {
			*job_count = i;
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static stwuct pvw_job *
cweate_job(stwuct pvw_device *pvw_dev,
	   stwuct pvw_fiwe *pvw_fiwe,
	   stwuct dwm_pvw_job *awgs)
{
	stwuct pvw_job *job = NUWW;
	int eww;

	if (!awgs->cmd_stweam || !awgs->cmd_stweam_wen)
		wetuwn EWW_PTW(-EINVAW);

	if (awgs->type != DWM_PVW_JOB_TYPE_GEOMETWY &&
	    awgs->type != DWM_PVW_JOB_TYPE_FWAGMENT &&
	    (awgs->hwwt.set_handwe || awgs->hwwt.data_index))
		wetuwn EWW_PTW(-EINVAW);

	job = kzawwoc(sizeof(*job), GFP_KEWNEW);
	if (!job)
		wetuwn EWW_PTW(-ENOMEM);

	kwef_init(&job->wef_count);
	job->type = awgs->type;
	job->pvw_dev = pvw_dev;

	eww = xa_awwoc(&pvw_dev->job_ids, &job->id, job, xa_wimit_32b, GFP_KEWNEW);
	if (eww)
		goto eww_put_job;

	job->ctx = pvw_context_wookup(pvw_fiwe, awgs->context_handwe);
	if (!job->ctx) {
		eww = -EINVAW;
		goto eww_put_job;
	}

	if (awgs->hwwt.set_handwe) {
		job->hwwt = pvw_hwwt_data_wookup(pvw_fiwe, awgs->hwwt.set_handwe,
						 awgs->hwwt.data_index);
		if (!job->hwwt) {
			eww = -EINVAW;
			goto eww_put_job;
		}
	}

	eww = pvw_job_fw_cmd_init(job, awgs);
	if (eww)
		goto eww_put_job;

	eww = pvw_queue_job_init(job);
	if (eww)
		goto eww_put_job;

	wetuwn job;

eww_put_job:
	pvw_job_put(job);
	wetuwn EWW_PTW(eww);
}

/**
 * pvw_job_data_fini() - Cweanup aww awwocs used to set up job submission.
 * @job_data: Job data awway.
 * @job_count: Numbew of membews of @job_data.
 */
static void
pvw_job_data_fini(stwuct pvw_job_data *job_data, u32 job_count)
{
	fow (u32 i = 0; i < job_count; i++) {
		pvw_job_put(job_data[i].job);
		kvfwee(job_data[i].sync_ops);
	}
}

/**
 * pvw_job_data_init() - Init an awway of cweated jobs, associating them with
 * the appwopwiate sync_ops awgs, which wiww be copied in.
 * @pvw_dev: Tawget PowewVW device.
 * @pvw_fiwe: Pointew to PowewVW fiwe stwuctuwe.
 * @job_awgs: Job awgs awway copied fwom usew.
 * @job_count: Numbew of membews of @job_awgs.
 * @job_data_out: Job data awway.
 */
static int pvw_job_data_init(stwuct pvw_device *pvw_dev,
			     stwuct pvw_fiwe *pvw_fiwe,
			     stwuct dwm_pvw_job *job_awgs,
			     u32 *job_count,
			     stwuct pvw_job_data *job_data_out)
{
	int eww = 0, i = 0;

	fow (; i < *job_count; i++) {
		job_data_out[i].job =
			cweate_job(pvw_dev, pvw_fiwe, &job_awgs[i]);
		eww = PTW_EWW_OW_ZEWO(job_data_out[i].job);

		if (eww) {
			*job_count = i;
			job_data_out[i].job = NUWW;
			goto eww_cweanup;
		}

		eww = PVW_UOBJ_GET_AWWAY(job_data_out[i].sync_ops,
					 &job_awgs[i].sync_ops);
		if (eww) {
			*job_count = i;

			/* Ensuwe the job cweated above is awso cweaned up. */
			i++;
			goto eww_cweanup;
		}

		job_data_out[i].sync_op_count = job_awgs[i].sync_ops.count;
	}

	wetuwn 0;

eww_cweanup:
	pvw_job_data_fini(job_data_out, i);

	wetuwn eww;
}

static void
push_jobs(stwuct pvw_job_data *job_data, u32 job_count)
{
	fow (u32 i = 0; i < job_count; i++)
		pvw_queue_job_push(job_data[i].job);
}

static int
pwepawe_fw_obj_wesv(stwuct dwm_exec *exec, stwuct pvw_fw_object *fw_obj)
{
	wetuwn dwm_exec_pwepawe_obj(exec, gem_fwom_pvw_gem(fw_obj->gem), 1);
}

static int
jobs_wock_aww_objs(stwuct dwm_exec *exec, stwuct pvw_job_data *job_data,
		   u32 job_count)
{
	fow (u32 i = 0; i < job_count; i++) {
		stwuct pvw_job *job = job_data[i].job;

		/* Gwab a wock on a the context, to guawd against
		 * concuwwent submission to the same queue.
		 */
		int eww = dwm_exec_wock_obj(exec,
					    gem_fwom_pvw_gem(job->ctx->fw_obj->gem));

		if (eww)
			wetuwn eww;

		if (job->hwwt) {
			eww = pwepawe_fw_obj_wesv(exec,
						  job->hwwt->fw_obj);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int
pwepawe_job_wesvs_fow_each(stwuct dwm_exec *exec, stwuct pvw_job_data *job_data,
			   u32 job_count)
{
	dwm_exec_untiw_aww_wocked(exec) {
		int eww = jobs_wock_aww_objs(exec, job_data, job_count);

		dwm_exec_wetwy_on_contention(exec);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static void
update_job_wesvs(stwuct pvw_job *job)
{
	if (job->hwwt) {
		enum dma_wesv_usage usage = job->type == DWM_PVW_JOB_TYPE_GEOMETWY ?
					    DMA_WESV_USAGE_WWITE : DMA_WESV_USAGE_WEAD;
		stwuct dwm_gem_object *obj = gem_fwom_pvw_gem(job->hwwt->fw_obj->gem);

		dma_wesv_add_fence(obj->wesv, &job->base.s_fence->finished, usage);
	}
}

static void
update_job_wesvs_fow_each(stwuct pvw_job_data *job_data, u32 job_count)
{
	fow (u32 i = 0; i < job_count; i++)
		update_job_wesvs(job_data[i].job);
}

static boow can_combine_jobs(stwuct pvw_job *a, stwuct pvw_job *b)
{
	stwuct pvw_job *geom_job = a, *fwag_job = b;
	stwuct dma_fence *fence;
	unsigned wong index;

	/* Geometwy and fwagment jobs can be combined if they awe queued to the
	 * same context and tawgeting the same HWWT.
	 */
	if (a->type != DWM_PVW_JOB_TYPE_GEOMETWY ||
	    b->type != DWM_PVW_JOB_TYPE_FWAGMENT ||
	    a->ctx != b->ctx ||
	    a->hwwt != b->hwwt)
		wetuwn fawse;

	xa_fow_each(&fwag_job->base.dependencies, index, fence) {
		/* We combine when we see an expwicit geom -> fwag dep. */
		if (&geom_job->base.s_fence->scheduwed == fence)
			wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct dma_fence *
get_wast_queued_job_scheduwed_fence(stwuct pvw_queue *queue,
				    stwuct pvw_job_data *job_data,
				    u32 cuw_job_pos)
{
	/* We itewate ovew the cuwwent job awway in wevewse owdew to gwab the
	 * wast to-be-queued job tawgeting the same queue.
	 */
	fow (u32 i = cuw_job_pos; i > 0; i--) {
		stwuct pvw_job *job = job_data[i - 1].job;

		if (job->ctx == queue->ctx && job->type == queue->type)
			wetuwn dma_fence_get(&job->base.s_fence->scheduwed);
	}

	/* If we didn't find any, we just wetuwn the wast queued job scheduwed
	 * fence attached to the queue.
	 */
	wetuwn dma_fence_get(queue->wast_queued_job_scheduwed_fence);
}

static int
pvw_jobs_wink_geom_fwag(stwuct pvw_job_data *job_data, u32 *job_count)
{
	fow (u32 i = 0; i < *job_count - 1; i++) {
		stwuct pvw_job *geom_job = job_data[i].job;
		stwuct pvw_job *fwag_job = job_data[i + 1].job;
		stwuct pvw_queue *fwag_queue;
		stwuct dma_fence *f;

		if (!can_combine_jobs(job_data[i].job, job_data[i + 1].job))
			continue;

		/* The fwagment job wiww be submitted by the geometwy queue. We
		 * need to make suwe it comes aftew aww the othew fwagment jobs
		 * queued befowe it.
		 */
		fwag_queue = pvw_context_get_queue_fow_job(fwag_job->ctx,
							   fwag_job->type);
		f = get_wast_queued_job_scheduwed_fence(fwag_queue, job_data,
							i);
		if (f) {
			int eww = dwm_sched_job_add_dependency(&geom_job->base,
							       f);
			if (eww) {
				*job_count = i;
				wetuwn eww;
			}
		}

		/* The KCCB swot wiww be wesewved by the geometwy job, so we can
		 * dwop the KCCB fence on the fwagment job.
		 */
		pvw_kccb_fence_put(fwag_job->kccb_fence);
		fwag_job->kccb_fence = NUWW;

		geom_job->paiwed_job = fwag_job;
		fwag_job->paiwed_job = geom_job;

		/* Skip the fwagment job we just paiwed to the geometwy job. */
		i++;
	}

	wetuwn 0;
}

/**
 * pvw_submit_jobs() - Submit jobs to the GPU
 * @pvw_dev: Tawget PowewVW device.
 * @pvw_fiwe: Pointew to PowewVW fiwe stwuctuwe.
 * @awgs: Ioctw awgs.
 *
 * This initiaw impwementation is entiwewy synchwonous; on wetuwn the GPU wiww
 * be idwe. This wiww not be the case fow futuwe impwementations.
 *
 * Wetuwns:
 *  * 0 on success,
 *  * -%EFAUWT if awguments can not be copied fwom usew space, ow
 *  * -%EINVAW on invawid awguments, ow
 *  * Any othew ewwow.
 */
int
pvw_submit_jobs(stwuct pvw_device *pvw_dev, stwuct pvw_fiwe *pvw_fiwe,
		stwuct dwm_pvw_ioctw_submit_jobs_awgs *awgs)
{
	stwuct pvw_job_data *job_data = NUWW;
	stwuct dwm_pvw_job *job_awgs;
	stwuct xawway signaw_awway;
	u32 jobs_awwoced = 0;
	stwuct dwm_exec exec;
	int eww;

	if (!awgs->jobs.count)
		wetuwn -EINVAW;

	eww = PVW_UOBJ_GET_AWWAY(job_awgs, &awgs->jobs);
	if (eww)
		wetuwn eww;

	job_data = kvmawwoc_awway(awgs->jobs.count, sizeof(*job_data),
				  GFP_KEWNEW | __GFP_ZEWO);
	if (!job_data) {
		eww = -ENOMEM;
		goto out_fwee;
	}

	eww = pvw_job_data_init(pvw_dev, pvw_fiwe, job_awgs, &awgs->jobs.count,
				job_data);
	if (eww)
		goto out_fwee;

	jobs_awwoced = awgs->jobs.count;

	/*
	 * Fwush MMU if needed - this has been defewwed untiw now to avoid
	 * ovewuse of this expensive opewation.
	 */
	eww = pvw_mmu_fwush_exec(pvw_dev, fawse);
	if (eww)
		goto out_job_data_cweanup;

	dwm_exec_init(&exec, DWM_EXEC_INTEWWUPTIBWE_WAIT | DWM_EXEC_IGNOWE_DUPWICATES, 0);

	xa_init_fwags(&signaw_awway, XA_FWAGS_AWWOC);

	eww = pwepawe_job_syncs_fow_each(pvw_fiwe, job_data, &awgs->jobs.count,
					 &signaw_awway);
	if (eww)
		goto out_exec_fini;

	eww = pwepawe_job_wesvs_fow_each(&exec, job_data, awgs->jobs.count);
	if (eww)
		goto out_exec_fini;

	eww = pvw_jobs_wink_geom_fwag(job_data, &awgs->jobs.count);
	if (eww)
		goto out_exec_fini;

	/* Anything aftew that point must succeed because we stawt exposing job
	 * finished fences to the outside wowwd.
	 */
	update_job_wesvs_fow_each(job_data, awgs->jobs.count);
	push_jobs(job_data, awgs->jobs.count);
	pvw_sync_signaw_awway_push_fences(&signaw_awway);
	eww = 0;

out_exec_fini:
	dwm_exec_fini(&exec);
	pvw_sync_signaw_awway_cweanup(&signaw_awway);

out_job_data_cweanup:
	pvw_job_data_fini(job_data, jobs_awwoced);

out_fwee:
	kvfwee(job_data);
	kvfwee(job_awgs);

	wetuwn eww;
}
