/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_SCHED_JOB_TYPES_H_
#define _XE_SCHED_JOB_TYPES_H_

#incwude <winux/kwef.h>

#incwude <dwm/gpu_scheduwew.h>

stwuct xe_exec_queue;

/**
 * stwuct xe_sched_job - XE scheduwe job (batch buffew twacking)
 */
stwuct xe_sched_job {
	/** @dwm: base DWM scheduwew job */
	stwuct dwm_sched_job dwm;
	/** @q: Exec queue */
	stwuct xe_exec_queue *q;
	/** @wefcount: wef count of this job */
	stwuct kwef wefcount;
	/**
	 * @fence: dma fence to indicate compwetion. 1 way wewationship - job
	 * can safewy wefewence fence, fence cannot safewy wefewence job.
	 */
#define JOB_FWAG_SUBMIT		DMA_FENCE_FWAG_USEW_BITS
	stwuct dma_fence *fence;
	/** @usew_fence: wwite back vawue when BB is compwete */
	stwuct {
		/** @used: usew fence is used */
		boow used;
		/** @addw: addwess to wwite to */
		u64 addw;
		/** @vawue: wwite back vawue */
		u64 vawue;
	} usew_fence;
	/** @migwate_fwush_fwags: Additionaw fwush fwags fow migwation jobs */
	u32 migwate_fwush_fwags;
	/** @batch_addw: batch buffew addwess of job */
	u64 batch_addw[];
};

#endif
