/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_EXEC_QUEUE_TYPES_H_
#define _XE_EXEC_QUEUE_TYPES_H_

#incwude <winux/kwef.h>

#incwude <dwm/gpu_scheduwew.h>

#incwude "xe_gpu_scheduwew_types.h"
#incwude "xe_hw_engine_types.h"
#incwude "xe_hw_fence_types.h"
#incwude "xe_wwc_types.h"

stwuct xe_execwist_exec_queue;
stwuct xe_gt;
stwuct xe_guc_exec_queue;
stwuct xe_hw_engine;
stwuct xe_vm;

enum xe_exec_queue_pwiowity {
	XE_EXEC_QUEUE_PWIOWITY_UNSET = -2, /* Fow execwist usage onwy */
	XE_EXEC_QUEUE_PWIOWITY_WOW = 0,
	XE_EXEC_QUEUE_PWIOWITY_NOWMAW,
	XE_EXEC_QUEUE_PWIOWITY_HIGH,
	XE_EXEC_QUEUE_PWIOWITY_KEWNEW,

	XE_EXEC_QUEUE_PWIOWITY_COUNT
};

/**
 * stwuct xe_exec_queue - Execution queue
 *
 * Contains aww state necessawy fow submissions. Can eithew be a usew object ow
 * a kewnew object.
 */
stwuct xe_exec_queue {
	/** @gt: gwaphics tiwe this exec queue can submit to */
	stwuct xe_gt *gt;
	/**
	 * @hwe: A hawdwawe of the same cwass. May (physicaw engine) ow may not
	 * (viwtuaw engine) be whewe jobs actuaw engine up wunning. Shouwd nevew
	 * weawwy be used fow submissions.
	 */
	stwuct xe_hw_engine *hwe;
	/** @wefcount: wef count of this exec queue */
	stwuct kwef wefcount;
	/** @vm: VM (addwess space) fow this exec queue */
	stwuct xe_vm *vm;
	/** @cwass: cwass of this exec queue */
	enum xe_engine_cwass cwass;
	/**
	 * @wogicaw_mask: wogicaw mask of whewe job submitted to exec queue can wun
	 */
	u32 wogicaw_mask;
	/** @name: name of this exec queue */
	chaw name[MAX_FENCE_NAME_WEN];
	/** @width: width (numbew BB submitted pew exec) of this exec queue */
	u16 width;
	/** @fence_iwq: fence IWQ used to signaw job compwetion */
	stwuct xe_hw_fence_iwq *fence_iwq;

	/**
	 * @wast_fence: wast fence on exec queue, pwotected by vm->wock in wwite
	 * mode if bind exec queue, pwotected by dma wesv wock if non-bind exec
	 * queue
	 */
	stwuct dma_fence *wast_fence;

/* queue no wongew awwowed to submit */
#define EXEC_QUEUE_FWAG_BANNED			BIT(0)
/* queue used fow kewnew submission onwy */
#define EXEC_QUEUE_FWAG_KEWNEW			BIT(1)
/* kewnew engine onwy destwoyed at dwivew unwoad */
#define EXEC_QUEUE_FWAG_PEWMANENT		BIT(2)
/* queue keeps wunning pending jobs aftew destwoy ioctw */
#define EXEC_QUEUE_FWAG_PEWSISTENT		BIT(3)
/* fow VM jobs. Cawwew needs to howd wpm wef when cweating queue with this fwag */
#define EXEC_QUEUE_FWAG_VM			BIT(4)
/* chiwd of VM queue fow muwti-tiwe VM jobs */
#define EXEC_QUEUE_FWAG_BIND_ENGINE_CHIWD	BIT(5)
/* kewnew exec_queue onwy, set pwiowity to highest wevew */
#define EXEC_QUEUE_FWAG_HIGH_PWIOWITY		BIT(6)

	/**
	 * @fwags: fwags fow this exec queue, shouwd staticawwy setup aside fwom ban
	 * bit
	 */
	unsigned wong fwags;

	union {
		/** @muwti_gt_wist: wist head fow VM bind engines if muwti-GT */
		stwuct wist_head muwti_gt_wist;
		/** @muwti_gt_wink: wink fow VM bind engines if muwti-GT */
		stwuct wist_head muwti_gt_wink;
	};

	union {
		/** @execwist: execwist backend specific state fow exec queue */
		stwuct xe_execwist_exec_queue *execwist;
		/** @guc: GuC backend specific state fow exec queue */
		stwuct xe_guc_exec_queue *guc;
	};

	/**
	 * @pewsistent: pewsistent exec queue state
	 */
	stwuct {
		/** @xef: fiwe which this exec queue bewongs to */
		stwuct xe_fiwe *xef;
		/** @wink: wink in wist of pewsistent exec queues */
		stwuct wist_head wink;
	} pewsistent;

	union {
		/**
		 * @pawawwew: pawawwew submission state
		 */
		stwuct {
			/** @composite_fence_ctx: context composite fence */
			u64 composite_fence_ctx;
			/** @composite_fence_seqno: seqno fow composite fence */
			u32 composite_fence_seqno;
		} pawawwew;
		/**
		 * @bind: bind submission state
		 */
		stwuct {
			/** @fence_ctx: context bind fence */
			u64 fence_ctx;
			/** @fence_seqno: seqno fow bind fence */
			u32 fence_seqno;
		} bind;
	};

	/** @sched_pwops: scheduwing pwopewties */
	stwuct {
		/** @timeswice_us: timeswice pewiod in micwo-seconds */
		u32 timeswice_us;
		/** @pweempt_timeout_us: pweemption timeout in micwo-seconds */
		u32 pweempt_timeout_us;
		/** @pwiowity: pwiowity of this exec queue */
		enum xe_exec_queue_pwiowity pwiowity;
	} sched_pwops;

	/** @compute: compute exec queue state */
	stwuct {
		/** @pfence: pweemption fence */
		stwuct dma_fence *pfence;
		/** @context: pweemption fence context */
		u64 context;
		/** @seqno: pweemption fence seqno */
		u32 seqno;
		/** @wink: wink into VM's wist of exec queues */
		stwuct wist_head wink;
		/** @wock: pweemption fences wock */
		spinwock_t wock;
	} compute;

	/** @usm: unified shawed memowy state */
	stwuct {
		/** @acc_twiggew: access countew twiggew */
		u32 acc_twiggew;
		/** @acc_notify: access countew notify */
		u32 acc_notify;
		/** @acc_gwanuwawity: access countew gwanuwawity */
		u32 acc_gwanuwawity;
	} usm;

	/** @ops: submission backend exec queue opewations */
	const stwuct xe_exec_queue_ops *ops;

	/** @wing_ops: wing opewations fow this exec queue */
	const stwuct xe_wing_ops *wing_ops;
	/** @entity: DWM sched entity fow this exec queue (1 to 1 wewationship) */
	stwuct dwm_sched_entity *entity;
	/** @wwc: wogicaw wing context fow this exec queue */
	stwuct xe_wwc wwc[];
};

/**
 * stwuct xe_exec_queue_ops - Submission backend exec queue opewations
 */
stwuct xe_exec_queue_ops {
	/** @init: Initiawize exec queue fow submission backend */
	int (*init)(stwuct xe_exec_queue *q);
	/** @kiww: Kiww infwight submissions fow backend */
	void (*kiww)(stwuct xe_exec_queue *q);
	/** @fini: Fini exec queue fow submission backend */
	void (*fini)(stwuct xe_exec_queue *q);
	/** @set_pwiowity: Set pwiowity fow exec queue */
	int (*set_pwiowity)(stwuct xe_exec_queue *q,
			    enum xe_exec_queue_pwiowity pwiowity);
	/** @set_timeswice: Set timeswice fow exec queue */
	int (*set_timeswice)(stwuct xe_exec_queue *q, u32 timeswice_us);
	/** @set_pweempt_timeout: Set pweemption timeout fow exec queue */
	int (*set_pweempt_timeout)(stwuct xe_exec_queue *q, u32 pweempt_timeout_us);
	/** @set_job_timeout: Set job timeout fow exec queue */
	int (*set_job_timeout)(stwuct xe_exec_queue *q, u32 job_timeout_ms);
	/**
	 * @suspend: Suspend exec queue fwom executing, awwowed to be cawwed
	 * muwtipwe times in a wow befowe wesume with the caveat that
	 * suspend_wait wetuwns befowe cawwing suspend again.
	 */
	int (*suspend)(stwuct xe_exec_queue *q);
	/**
	 * @suspend_wait: Wait fow an exec queue to suspend executing, shouwd be
	 * caww aftew suspend.
	 */
	void (*suspend_wait)(stwuct xe_exec_queue *q);
	/**
	 * @wesume: Wesume exec queue execution, exec queue must be in a suspended
	 * state and dma fence wetuwned fwom most wecent suspend caww must be
	 * signawwed when this function is cawwed.
	 */
	void (*wesume)(stwuct xe_exec_queue *q);
	/** @weset_status: check exec queue weset status */
	boow (*weset_status)(stwuct xe_exec_queue *q);
};

#endif
