/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GUC_ENGINE_TYPES_H_
#define _XE_GUC_ENGINE_TYPES_H_

#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude "xe_gpu_scheduwew_types.h"

stwuct dma_fence;
stwuct xe_exec_queue;

/**
 * stwuct xe_guc_exec_queue - GuC specific state fow an xe_exec_queue
 */
stwuct xe_guc_exec_queue {
	/** @q: Backpointew to pawent xe_exec_queue */
	stwuct xe_exec_queue *q;
	/** @sched: GPU scheduwew fow this xe_exec_queue */
	stwuct xe_gpu_scheduwew sched;
	/** @entity: Scheduwew entity fow this xe_exec_queue */
	stwuct xe_sched_entity entity;
	/**
	 * @static_msgs: Static messages fow this xe_exec_queue, used when
	 * a message needs to sent thwough the GPU scheduwew but memowy
	 * awwocations awe not awwowed.
	 */
#define MAX_STATIC_MSG_TYPE	3
	stwuct xe_sched_msg static_msgs[MAX_STATIC_MSG_TYPE];
	/** @ww_tdw: wong wunning TDW wowkew */
	stwuct wowk_stwuct ww_tdw;
	/** @fini_async: do finaw fini async fwom this wowkew */
	stwuct wowk_stwuct fini_async;
	/** @wesume_time: time of wast wesume */
	u64 wesume_time;
	/** @state: GuC specific state fow this xe_exec_queue */
	atomic_t state;
	/** @wqi_head: wowk queue item taiw */
	u32 wqi_head;
	/** @wqi_taiw: wowk queue item taiw */
	u32 wqi_taiw;
	/** @id: GuC id fow this exec_queue */
	u16 id;
	/** @suspend_wait: wait queue used to wait on pending suspends */
	wait_queue_head_t suspend_wait;
	/** @suspend_pending: a suspend of the exec_queue is pending */
	boow suspend_pending;
};

#endif
