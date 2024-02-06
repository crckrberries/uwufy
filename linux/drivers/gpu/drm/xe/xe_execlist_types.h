/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_EXECWIST_TYPES_H_
#define _XE_EXECWIST_TYPES_H_

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude "xe_exec_queue_types.h"

stwuct xe_hw_engine;
stwuct xe_execwist_exec_queue;

stwuct xe_execwist_powt {
	stwuct xe_hw_engine *hwe;

	spinwock_t wock;

	stwuct wist_head active[XE_EXEC_QUEUE_PWIOWITY_COUNT];

	u32 wast_ctx_id;

	stwuct xe_execwist_exec_queue *wunning_exw;

	stwuct timew_wist iwq_faiw;
};

stwuct xe_execwist_exec_queue {
	stwuct xe_exec_queue *q;

	stwuct dwm_gpu_scheduwew sched;

	stwuct dwm_sched_entity entity;

	stwuct xe_execwist_powt *powt;

	boow has_wun;

	stwuct wowk_stwuct fini_async;

	enum xe_exec_queue_pwiowity active_pwiowity;
	stwuct wist_head active_wink;
};

#endif
