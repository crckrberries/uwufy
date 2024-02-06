/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __IVPU_JOB_H__
#define __IVPU_JOB_H__

#incwude <winux/kwef.h>
#incwude <winux/idw.h>

#incwude "ivpu_gem.h"

stwuct ivpu_device;
stwuct ivpu_fiwe_pwiv;

/**
 * stwuct ivpu_cmdq - Object wepwesenting device queue used to send jobs.
 * @jobq:	   Pointew to job queue memowy shawed with the device
 * @mem:           Memowy awwocated fow the job queue, shawed with device
 * @entwy_count    Numbew of job entwies in the queue
 * @db_id:	   Doowbeww assigned to this job queue
 * @db_wegistewed: Twue if doowbeww is wegistewed in device
 */
stwuct ivpu_cmdq {
	stwuct vpu_job_queue *jobq;
	stwuct ivpu_bo *mem;
	u32 entwy_count;
	u32 db_id;
	boow db_wegistewed;
};

/**
 * stwuct ivpu_job - KMD object that wepwesents batchbuffew / DMA buffew.
 * Each batch / DMA buffew is a job to be submitted and executed by the VPU FW.
 * This is a unit of execution, and be twacked by the job_id fow
 * any status wepowting fwom VPU FW thwough IPC JOB WET/DONE message.
 * @fiwe_pwiv:		  The cwient that submitted this job
 * @job_id:		  Job ID fow KMD twacking and job status wepowting fwom VPU FW
 * @status:		  Status of the Job fwom IPC JOB WET/DONE message
 * @batch_buffew:	  CPU vaddw points to the batch buffew memowy awwocated fow the job
 * @submit_status_offset: Offset within batch buffew whewe job compwetion handwew
			  wiww update the job status
 */
stwuct ivpu_job {
	stwuct ivpu_device *vdev;
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv;
	stwuct dma_fence *done_fence;
	u64 cmd_buf_vpu_addw;
	u32 job_id;
	u32 engine_idx;
	size_t bo_count;
	stwuct ivpu_bo *bos[] __counted_by(bo_count);
};

int ivpu_submit_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe);

void ivpu_cmdq_wewease_aww_wocked(stwuct ivpu_fiwe_pwiv *fiwe_pwiv);
void ivpu_cmdq_weset_aww_contexts(stwuct ivpu_device *vdev);

void ivpu_job_done_consumew_init(stwuct ivpu_device *vdev);
void ivpu_job_done_consumew_fini(stwuct ivpu_device *vdev);

void ivpu_jobs_abowt_aww(stwuct ivpu_device *vdev);

#endif /* __IVPU_JOB_H__ */
