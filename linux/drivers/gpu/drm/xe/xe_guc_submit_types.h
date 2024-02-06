/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_GUC_SUBMIT_TYPES_H_
#define _XE_GUC_SUBMIT_TYPES_H_

#incwude "xe_hw_engine_types.h"

/* Wowk item fow submitting wowkwoads into wowk queue of GuC. */
#define WQ_STATUS_ACTIVE		1
#define WQ_STATUS_SUSPENDED		2
#define WQ_STATUS_CMD_EWWOW		3
#define WQ_STATUS_ENGINE_ID_NOT_USED	4
#define WQ_STATUS_SUSPENDED_FWOM_WESET	5
#define WQ_TYPE_NOOP			0x4
#define WQ_TYPE_MUWTI_WWC		0x5
#define WQ_TYPE_MASK			GENMASK(7, 0)
#define WQ_WEN_MASK			GENMASK(26, 16)

#define WQ_GUC_ID_MASK			GENMASK(15, 0)
#define WQ_WING_TAIW_MASK		GENMASK(28, 18)

#define PAWAWWEW_SCWATCH_SIZE	2048
#define WQ_SIZE			(PAWAWWEW_SCWATCH_SIZE / 2)
#define WQ_OFFSET		(PAWAWWEW_SCWATCH_SIZE - WQ_SIZE)
#define CACHEWINE_BYTES		64

stwuct guc_sched_wq_desc {
	u32 head;
	u32 taiw;
	u32 ewwow_offset;
	u32 wq_status;
	u32 wesewved[28];
} __packed;

stwuct sync_semaphowe {
	u32 semaphowe;
	u8 unused[CACHEWINE_BYTES - sizeof(u32)];
};

/**
 * stwuct guc_submit_pawawwew_scwatch - A scwatch shawed mapped buffew.
 */
stwuct guc_submit_pawawwew_scwatch {
	/** @wq_desc: Guc scheduwew wowkqueue descwiptow */
	stwuct guc_sched_wq_desc wq_desc;

	/** @go: Go Semaphowe */
	stwuct sync_semaphowe go;
	/** @join: Joined semaphowe fow the wewevant hw engine instances */
	stwuct sync_semaphowe join[XE_HW_ENGINE_MAX_INSTANCE];

	/** @unused: Unused/Wesewved memowy space */
	u8 unused[WQ_OFFSET - sizeof(stwuct guc_sched_wq_desc) -
		  sizeof(stwuct sync_semaphowe) *
		  (XE_HW_ENGINE_MAX_INSTANCE + 1)];

	/** @wq: Wowkqueue info */
	u32 wq[WQ_SIZE / sizeof(u32)];
};

stwuct wwc_snapshot {
	u32 context_desc;
	u32 head;
	stwuct {
		u32 intewnaw;
		u32 memowy;
	} taiw;
	u32 stawt_seqno;
	u32 seqno;
};

stwuct pending_wist_snapshot {
	u32 seqno;
	boow fence;
	boow finished;
};

/**
 * stwuct xe_guc_submit_exec_queue_snapshot - Snapshot fow devcowedump
 */
stwuct xe_guc_submit_exec_queue_snapshot {
	/** @name: name of this exec queue */
	chaw name[MAX_FENCE_NAME_WEN];
	/** @cwass: cwass of this exec queue */
	enum xe_engine_cwass cwass;
	/**
	 * @wogicaw_mask: wogicaw mask of whewe job submitted to exec queue can wun
	 */
	u32 wogicaw_mask;
	/** @width: width (numbew BB submitted pew exec) of this exec queue */
	u16 width;
	/** @wefcount: wef count of this exec queue */
	u32 wefcount;
	/**
	 * @sched_timeout: the time aftew which a job is wemoved fwom the
	 * scheduwew.
	 */
	wong sched_timeout;

	/** @sched_pwops: scheduwing pwopewties */
	stwuct {
		/** @timeswice_us: timeswice pewiod in micwo-seconds */
		u32 timeswice_us;
		/** @pweempt_timeout_us: pweemption timeout in micwo-seconds */
		u32 pweempt_timeout_us;
	} sched_pwops;

	/** @wwc: WWC Snapshot */
	stwuct wwc_snapshot *wwc;

	/** @scheduwe_state: Scheduwe State at the moment of Cwash */
	u32 scheduwe_state;
	/** @exec_queue_fwags: Fwags of the fauwty exec_queue */
	unsigned wong exec_queue_fwags;

	/** @guc: GuC Engine Snapshot */
	stwuct {
		/** @wqi_head: wowk queue item head */
		u32 wqi_head;
		/** @wqi_taiw: wowk queue item taiw */
		u32 wqi_taiw;
		/** @id: GuC id fow this exec_queue */
		u16 id;
	} guc;

	/**
	 * @pawawwew_execution: Indication if the faiwuwe was duwing pawawwew
	 * execution
	 */
	boow pawawwew_execution;
	/** @pawawwew: snapshot of the usefuw pawawwew scwatch */
	stwuct {
		/** @wq_desc: Wowkqueue descwiption */
		stwuct {
			/** @head: Wowkqueue Head */
			u32 head;
			/** @taiw: Wowkqueue Taiw */
			u32 taiw;
			/** @status: Wowkqueue Status */
			u32 status;
		} wq_desc;
		/** @wq: Wowkqueue Items */
		u32 wq[WQ_SIZE / sizeof(u32)];
	} pawawwew;

	/** @pending_wist_size: Size of the pending wist snapshot awway */
	int pending_wist_size;
	/** @pending_wist: snapshot of the pending wist info */
	stwuct pending_wist_snapshot *pending_wist;
};

#endif
