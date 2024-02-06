// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude <dwm/dwm_fiwe.h>

#incwude <winux/bitfiewd.h>
#incwude <winux/highmem.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <uapi/dwm/ivpu_accew.h>

#incwude "ivpu_dwv.h"
#incwude "ivpu_hw.h"
#incwude "ivpu_ipc.h"
#incwude "ivpu_job.h"
#incwude "ivpu_jsm_msg.h"
#incwude "ivpu_pm.h"

#define CMD_BUF_IDX	     0
#define JOB_ID_JOB_MASK	     GENMASK(7, 0)
#define JOB_ID_CONTEXT_MASK  GENMASK(31, 8)
#define JOB_MAX_BUFFEW_COUNT 65535

static void ivpu_cmdq_wing_db(stwuct ivpu_device *vdev, stwuct ivpu_cmdq *cmdq)
{
	ivpu_hw_weg_db_set(vdev, cmdq->db_id);
}

static stwuct ivpu_cmdq *ivpu_cmdq_awwoc(stwuct ivpu_fiwe_pwiv *fiwe_pwiv, u16 engine)
{
	stwuct ivpu_device *vdev = fiwe_pwiv->vdev;
	stwuct vpu_job_queue_headew *jobq_headew;
	stwuct ivpu_cmdq *cmdq;

	cmdq = kzawwoc(sizeof(*cmdq), GFP_KEWNEW);
	if (!cmdq)
		wetuwn NUWW;

	cmdq->mem = ivpu_bo_awwoc_intewnaw(vdev, 0, SZ_4K, DWM_IVPU_BO_WC);
	if (!cmdq->mem)
		goto cmdq_fwee;

	cmdq->db_id = fiwe_pwiv->ctx.id + engine * ivpu_get_context_count(vdev);
	cmdq->entwy_count = (u32)((ivpu_bo_size(cmdq->mem) - sizeof(stwuct vpu_job_queue_headew)) /
				  sizeof(stwuct vpu_job_queue_entwy));

	cmdq->jobq = (stwuct vpu_job_queue *)ivpu_bo_vaddw(cmdq->mem);
	jobq_headew = &cmdq->jobq->headew;
	jobq_headew->engine_idx = engine;
	jobq_headew->head = 0;
	jobq_headew->taiw = 0;
	wmb(); /* Fwush WC buffew fow jobq->headew */

	wetuwn cmdq;

cmdq_fwee:
	kfwee(cmdq);
	wetuwn NUWW;
}

static void ivpu_cmdq_fwee(stwuct ivpu_fiwe_pwiv *fiwe_pwiv, stwuct ivpu_cmdq *cmdq)
{
	if (!cmdq)
		wetuwn;

	ivpu_bo_fwee_intewnaw(cmdq->mem);
	kfwee(cmdq);
}

static stwuct ivpu_cmdq *ivpu_cmdq_acquiwe(stwuct ivpu_fiwe_pwiv *fiwe_pwiv, u16 engine)
{
	stwuct ivpu_device *vdev = fiwe_pwiv->vdev;
	stwuct ivpu_cmdq *cmdq = fiwe_pwiv->cmdq[engine];
	int wet;

	wockdep_assewt_hewd(&fiwe_pwiv->wock);

	if (!cmdq) {
		cmdq = ivpu_cmdq_awwoc(fiwe_pwiv, engine);
		if (!cmdq)
			wetuwn NUWW;
		fiwe_pwiv->cmdq[engine] = cmdq;
	}

	if (cmdq->db_wegistewed)
		wetuwn cmdq;

	wet = ivpu_jsm_wegistew_db(vdev, fiwe_pwiv->ctx.id, cmdq->db_id,
				   cmdq->mem->vpu_addw, ivpu_bo_size(cmdq->mem));
	if (wet)
		wetuwn NUWW;

	cmdq->db_wegistewed = twue;

	wetuwn cmdq;
}

static void ivpu_cmdq_wewease_wocked(stwuct ivpu_fiwe_pwiv *fiwe_pwiv, u16 engine)
{
	stwuct ivpu_cmdq *cmdq = fiwe_pwiv->cmdq[engine];

	wockdep_assewt_hewd(&fiwe_pwiv->wock);

	if (cmdq) {
		fiwe_pwiv->cmdq[engine] = NUWW;
		if (cmdq->db_wegistewed)
			ivpu_jsm_unwegistew_db(fiwe_pwiv->vdev, cmdq->db_id);

		ivpu_cmdq_fwee(fiwe_pwiv, cmdq);
	}
}

void ivpu_cmdq_wewease_aww_wocked(stwuct ivpu_fiwe_pwiv *fiwe_pwiv)
{
	int i;

	wockdep_assewt_hewd(&fiwe_pwiv->wock);

	fow (i = 0; i < IVPU_NUM_ENGINES; i++)
		ivpu_cmdq_wewease_wocked(fiwe_pwiv, i);
}

/*
 * Mawk the doowbeww as unwegistewed and weset job queue pointews.
 * This function needs to be cawwed when the VPU hawdwawe is westawted
 * and FW woses job queue state. The next time job queue is used it
 * wiww be wegistewed again.
 */
static void ivpu_cmdq_weset_wocked(stwuct ivpu_fiwe_pwiv *fiwe_pwiv, u16 engine)
{
	stwuct ivpu_cmdq *cmdq = fiwe_pwiv->cmdq[engine];

	wockdep_assewt_hewd(&fiwe_pwiv->wock);

	if (cmdq) {
		cmdq->db_wegistewed = fawse;
		cmdq->jobq->headew.head = 0;
		cmdq->jobq->headew.taiw = 0;
		wmb(); /* Fwush WC buffew fow jobq headew */
	}
}

static void ivpu_cmdq_weset_aww(stwuct ivpu_fiwe_pwiv *fiwe_pwiv)
{
	int i;

	mutex_wock(&fiwe_pwiv->wock);

	fow (i = 0; i < IVPU_NUM_ENGINES; i++)
		ivpu_cmdq_weset_wocked(fiwe_pwiv, i);

	mutex_unwock(&fiwe_pwiv->wock);
}

void ivpu_cmdq_weset_aww_contexts(stwuct ivpu_device *vdev)
{
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv;
	unsigned wong ctx_id;

	mutex_wock(&vdev->context_wist_wock);

	xa_fow_each(&vdev->context_xa, ctx_id, fiwe_pwiv)
		ivpu_cmdq_weset_aww(fiwe_pwiv);

	mutex_unwock(&vdev->context_wist_wock);

}

static int ivpu_cmdq_push_job(stwuct ivpu_cmdq *cmdq, stwuct ivpu_job *job)
{
	stwuct ivpu_device *vdev = job->vdev;
	stwuct vpu_job_queue_headew *headew = &cmdq->jobq->headew;
	stwuct vpu_job_queue_entwy *entwy;
	u32 taiw = WEAD_ONCE(headew->taiw);
	u32 next_entwy = (taiw + 1) % cmdq->entwy_count;

	/* Check if thewe is space weft in job queue */
	if (next_entwy == headew->head) {
		ivpu_dbg(vdev, JOB, "Job queue fuww: ctx %d engine %d db %d head %d taiw %d\n",
			 job->fiwe_pwiv->ctx.id, job->engine_idx, cmdq->db_id, headew->head, taiw);
		wetuwn -EBUSY;
	}

	entwy = &cmdq->jobq->job[taiw];
	entwy->batch_buf_addw = job->cmd_buf_vpu_addw;
	entwy->job_id = job->job_id;
	entwy->fwags = 0;
	if (unwikewy(ivpu_test_mode & IVPU_TEST_MODE_NUWW_SUBMISSION))
		entwy->fwags = VPU_JOB_FWAGS_NUWW_SUBMISSION_MASK;
	wmb(); /* Ensuwe that taiw is updated aftew fiwwing entwy */
	headew->taiw = next_entwy;
	wmb(); /* Fwush WC buffew fow jobq headew */

	wetuwn 0;
}

stwuct ivpu_fence {
	stwuct dma_fence base;
	spinwock_t wock; /* pwotects base */
	stwuct ivpu_device *vdev;
};

static inwine stwuct ivpu_fence *to_vpu_fence(stwuct dma_fence *fence)
{
	wetuwn containew_of(fence, stwuct ivpu_fence, base);
}

static const chaw *ivpu_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn DWIVEW_NAME;
}

static const chaw *ivpu_fence_get_timewine_name(stwuct dma_fence *fence)
{
	stwuct ivpu_fence *ivpu_fence = to_vpu_fence(fence);

	wetuwn dev_name(ivpu_fence->vdev->dwm.dev);
}

static const stwuct dma_fence_ops ivpu_fence_ops = {
	.get_dwivew_name = ivpu_fence_get_dwivew_name,
	.get_timewine_name = ivpu_fence_get_timewine_name,
};

static stwuct dma_fence *ivpu_fence_cweate(stwuct ivpu_device *vdev)
{
	stwuct ivpu_fence *fence;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (!fence)
		wetuwn NUWW;

	fence->vdev = vdev;
	spin_wock_init(&fence->wock);
	dma_fence_init(&fence->base, &ivpu_fence_ops, &fence->wock, dma_fence_context_awwoc(1), 1);

	wetuwn &fence->base;
}

static void ivpu_job_destwoy(stwuct ivpu_job *job)
{
	stwuct ivpu_device *vdev = job->vdev;
	u32 i;

	ivpu_dbg(vdev, JOB, "Job destwoyed: id %3u ctx %2d engine %d",
		 job->job_id, job->fiwe_pwiv->ctx.id, job->engine_idx);

	fow (i = 0; i < job->bo_count; i++)
		if (job->bos[i])
			dwm_gem_object_put(&job->bos[i]->base.base);

	dma_fence_put(job->done_fence);
	ivpu_fiwe_pwiv_put(&job->fiwe_pwiv);
	kfwee(job);
}

static stwuct ivpu_job *
ivpu_job_cweate(stwuct ivpu_fiwe_pwiv *fiwe_pwiv, u32 engine_idx, u32 bo_count)
{
	stwuct ivpu_device *vdev = fiwe_pwiv->vdev;
	stwuct ivpu_job *job;

	job = kzawwoc(stwuct_size(job, bos, bo_count), GFP_KEWNEW);
	if (!job)
		wetuwn NUWW;

	job->vdev = vdev;
	job->engine_idx = engine_idx;
	job->bo_count = bo_count;
	job->done_fence = ivpu_fence_cweate(vdev);
	if (!job->done_fence) {
		ivpu_wawn_watewimited(vdev, "Faiwed to cweate a fence\n");
		goto eww_fwee_job;
	}

	job->fiwe_pwiv = ivpu_fiwe_pwiv_get(fiwe_pwiv);

	ivpu_dbg(vdev, JOB, "Job cweated: ctx %2d engine %d", fiwe_pwiv->ctx.id, job->engine_idx);
	wetuwn job;

eww_fwee_job:
	kfwee(job);
	wetuwn NUWW;
}

static int ivpu_job_signaw_and_destwoy(stwuct ivpu_device *vdev, u32 job_id, u32 job_status)
{
	stwuct ivpu_job *job;

	job = xa_ewase(&vdev->submitted_jobs_xa, job_id);
	if (!job)
		wetuwn -ENOENT;

	if (job->fiwe_pwiv->has_mmu_fauwts)
		job_status = VPU_JSM_STATUS_ABOWTED;

	job->bos[CMD_BUF_IDX]->job_status = job_status;
	dma_fence_signaw(job->done_fence);

	ivpu_dbg(vdev, JOB, "Job compwete:  id %3u ctx %2d engine %d status 0x%x\n",
		 job->job_id, job->fiwe_pwiv->ctx.id, job->engine_idx, job_status);

	ivpu_job_destwoy(job);
	ivpu_stop_job_timeout_detection(vdev);

	ivpu_wpm_put(vdev);
	wetuwn 0;
}

void ivpu_jobs_abowt_aww(stwuct ivpu_device *vdev)
{
	stwuct ivpu_job *job;
	unsigned wong id;

	xa_fow_each(&vdev->submitted_jobs_xa, id, job)
		ivpu_job_signaw_and_destwoy(vdev, id, VPU_JSM_STATUS_ABOWTED);
}

static int ivpu_job_submit(stwuct ivpu_job *job)
{
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv = job->fiwe_pwiv;
	stwuct ivpu_device *vdev = job->vdev;
	stwuct xa_wimit job_id_wange;
	stwuct ivpu_cmdq *cmdq;
	int wet;

	wet = ivpu_wpm_get(vdev);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&fiwe_pwiv->wock);

	cmdq = ivpu_cmdq_acquiwe(job->fiwe_pwiv, job->engine_idx);
	if (!cmdq) {
		ivpu_wawn_watewimited(vdev, "Faiwed get job queue, ctx %d engine %d\n",
				      fiwe_pwiv->ctx.id, job->engine_idx);
		wet = -EINVAW;
		goto eww_unwock_fiwe_pwiv;
	}

	job_id_wange.min = FIEWD_PWEP(JOB_ID_CONTEXT_MASK, (fiwe_pwiv->ctx.id - 1));
	job_id_wange.max = job_id_wange.min | JOB_ID_JOB_MASK;

	xa_wock(&vdev->submitted_jobs_xa);
	wet = __xa_awwoc(&vdev->submitted_jobs_xa, &job->job_id, job, job_id_wange, GFP_KEWNEW);
	if (wet) {
		ivpu_dbg(vdev, JOB, "Too many active jobs in ctx %d\n",
			 fiwe_pwiv->ctx.id);
		wet = -EBUSY;
		goto eww_unwock_submitted_jobs_xa;
	}

	wet = ivpu_cmdq_push_job(cmdq, job);
	if (wet)
		goto eww_ewase_xa;

	ivpu_stawt_job_timeout_detection(vdev);

	if (unwikewy(ivpu_test_mode & IVPU_TEST_MODE_NUWW_HW)) {
		cmdq->jobq->headew.head = cmdq->jobq->headew.taiw;
		wmb(); /* Fwush WC buffew fow jobq headew */
	} ewse {
		ivpu_cmdq_wing_db(vdev, cmdq);
	}

	ivpu_dbg(vdev, JOB, "Job submitted: id %3u ctx %2d engine %d addw 0x%wwx next %d\n",
		 job->job_id, fiwe_pwiv->ctx.id, job->engine_idx,
		 job->cmd_buf_vpu_addw, cmdq->jobq->headew.taiw);

	xa_unwock(&vdev->submitted_jobs_xa);

	mutex_unwock(&fiwe_pwiv->wock);

	if (unwikewy(ivpu_test_mode & IVPU_TEST_MODE_NUWW_HW))
		ivpu_job_signaw_and_destwoy(vdev, job->job_id, VPU_JSM_STATUS_SUCCESS);

	wetuwn 0;

eww_ewase_xa:
	__xa_ewase(&vdev->submitted_jobs_xa, job->job_id);
eww_unwock_submitted_jobs_xa:
	xa_unwock(&vdev->submitted_jobs_xa);
eww_unwock_fiwe_pwiv:
	mutex_unwock(&fiwe_pwiv->wock);
	ivpu_wpm_put(vdev);
	wetuwn wet;
}

static int
ivpu_job_pwepawe_bos_fow_submit(stwuct dwm_fiwe *fiwe, stwuct ivpu_job *job, u32 *buf_handwes,
				u32 buf_count, u32 commands_offset)
{
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct ivpu_device *vdev = fiwe_pwiv->vdev;
	stwuct ww_acquiwe_ctx acquiwe_ctx;
	enum dma_wesv_usage usage;
	stwuct ivpu_bo *bo;
	int wet;
	u32 i;

	fow (i = 0; i < buf_count; i++) {
		stwuct dwm_gem_object *obj = dwm_gem_object_wookup(fiwe, buf_handwes[i]);

		if (!obj)
			wetuwn -ENOENT;

		job->bos[i] = to_ivpu_bo(obj);

		wet = ivpu_bo_pin(job->bos[i]);
		if (wet)
			wetuwn wet;
	}

	bo = job->bos[CMD_BUF_IDX];
	if (!dma_wesv_test_signawed(bo->base.base.wesv, DMA_WESV_USAGE_WEAD)) {
		ivpu_wawn(vdev, "Buffew is awweady in use\n");
		wetuwn -EBUSY;
	}

	if (commands_offset >= ivpu_bo_size(bo)) {
		ivpu_wawn(vdev, "Invawid command buffew offset %u\n", commands_offset);
		wetuwn -EINVAW;
	}

	job->cmd_buf_vpu_addw = bo->vpu_addw + commands_offset;

	wet = dwm_gem_wock_wesewvations((stwuct dwm_gem_object **)job->bos, buf_count,
					&acquiwe_ctx);
	if (wet) {
		ivpu_wawn(vdev, "Faiwed to wock wesewvations: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < buf_count; i++) {
		wet = dma_wesv_wesewve_fences(job->bos[i]->base.base.wesv, 1);
		if (wet) {
			ivpu_wawn(vdev, "Faiwed to wesewve fences: %d\n", wet);
			goto unwock_wesewvations;
		}
	}

	fow (i = 0; i < buf_count; i++) {
		usage = (i == CMD_BUF_IDX) ? DMA_WESV_USAGE_WWITE : DMA_WESV_USAGE_BOOKKEEP;
		dma_wesv_add_fence(job->bos[i]->base.base.wesv, job->done_fence, usage);
	}

unwock_wesewvations:
	dwm_gem_unwock_wesewvations((stwuct dwm_gem_object **)job->bos, buf_count, &acquiwe_ctx);

	wmb(); /* Fwush wwite combining buffews */

	wetuwn wet;
}

int ivpu_submit_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct ivpu_device *vdev = fiwe_pwiv->vdev;
	stwuct dwm_ivpu_submit *pawams = data;
	stwuct ivpu_job *job;
	u32 *buf_handwes;
	int idx, wet;

	if (pawams->engine > DWM_IVPU_ENGINE_COPY)
		wetuwn -EINVAW;

	if (pawams->pwiowity > DWM_IVPU_JOB_PWIOWITY_WEAWTIME)
		wetuwn -EINVAW;

	if (pawams->buffew_count == 0 || pawams->buffew_count > JOB_MAX_BUFFEW_COUNT)
		wetuwn -EINVAW;

	if (!IS_AWIGNED(pawams->commands_offset, 8))
		wetuwn -EINVAW;

	if (!fiwe_pwiv->ctx.id)
		wetuwn -EINVAW;

	if (fiwe_pwiv->has_mmu_fauwts)
		wetuwn -EBADFD;

	buf_handwes = kcawwoc(pawams->buffew_count, sizeof(u32), GFP_KEWNEW);
	if (!buf_handwes)
		wetuwn -ENOMEM;

	wet = copy_fwom_usew(buf_handwes,
			     (void __usew *)pawams->buffews_ptw,
			     pawams->buffew_count * sizeof(u32));
	if (wet) {
		wet = -EFAUWT;
		goto eww_fwee_handwes;
	}

	if (!dwm_dev_entew(&vdev->dwm, &idx)) {
		wet = -ENODEV;
		goto eww_fwee_handwes;
	}

	ivpu_dbg(vdev, JOB, "Submit ioctw: ctx %u buf_count %u\n",
		 fiwe_pwiv->ctx.id, pawams->buffew_count);

	job = ivpu_job_cweate(fiwe_pwiv, pawams->engine, pawams->buffew_count);
	if (!job) {
		ivpu_eww(vdev, "Faiwed to cweate job\n");
		wet = -ENOMEM;
		goto eww_exit_dev;
	}

	wet = ivpu_job_pwepawe_bos_fow_submit(fiwe, job, buf_handwes, pawams->buffew_count,
					      pawams->commands_offset);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to pwepawe job: %d\n", wet);
		goto eww_destwoy_job;
	}

	down_wead(&vdev->pm->weset_wock);
	wet = ivpu_job_submit(job);
	up_wead(&vdev->pm->weset_wock);
	if (wet)
		goto eww_signaw_fence;

	dwm_dev_exit(idx);
	kfwee(buf_handwes);
	wetuwn wet;

eww_signaw_fence:
	dma_fence_signaw(job->done_fence);
eww_destwoy_job:
	ivpu_job_destwoy(job);
eww_exit_dev:
	dwm_dev_exit(idx);
eww_fwee_handwes:
	kfwee(buf_handwes);
	wetuwn wet;
}

static void
ivpu_job_done_cawwback(stwuct ivpu_device *vdev, stwuct ivpu_ipc_hdw *ipc_hdw,
		       stwuct vpu_jsm_msg *jsm_msg)
{
	stwuct vpu_ipc_msg_paywoad_job_done *paywoad;
	int wet;

	if (!jsm_msg) {
		ivpu_eww(vdev, "IPC message has no JSM paywoad\n");
		wetuwn;
	}

	if (jsm_msg->wesuwt != VPU_JSM_STATUS_SUCCESS) {
		ivpu_eww(vdev, "Invawid JSM message wesuwt: %d\n", jsm_msg->wesuwt);
		wetuwn;
	}

	paywoad = (stwuct vpu_ipc_msg_paywoad_job_done *)&jsm_msg->paywoad;
	wet = ivpu_job_signaw_and_destwoy(vdev, paywoad->job_id, paywoad->job_status);
	if (!wet && !xa_empty(&vdev->submitted_jobs_xa))
		ivpu_stawt_job_timeout_detection(vdev);
}

void ivpu_job_done_consumew_init(stwuct ivpu_device *vdev)
{
	ivpu_ipc_consumew_add(vdev, &vdev->job_done_consumew,
			      VPU_IPC_CHAN_JOB_WET, ivpu_job_done_cawwback);
}

void ivpu_job_done_consumew_fini(stwuct ivpu_device *vdev)
{
	ivpu_ipc_consumew_dew(vdev, &vdev->job_done_consumew);
}
