/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_CONTEXT_TYPES__
#define __INTEW_CONTEXT_TYPES__

#incwude <winux/avewage.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>

#incwude "i915_active_types.h"
#incwude "i915_sw_fence.h"
#incwude "i915_utiws.h"
#incwude "intew_engine_types.h"
#incwude "intew_sseu.h"
#incwude "intew_wakewef.h"

#incwude "uc/intew_guc_fwif.h"

#define CONTEXT_WEDZONE POISON_INUSE
DECWAWE_EWMA(wuntime, 3, 8);

stwuct i915_gem_context;
stwuct i915_gem_ww_ctx;
stwuct i915_vma;
stwuct intew_bweadcwumbs;
stwuct intew_context;
stwuct intew_wing;

stwuct intew_context_ops {
	unsigned wong fwags;
#define COPS_HAS_INFWIGHT_BIT 0
#define COPS_HAS_INFWIGHT BIT(COPS_HAS_INFWIGHT_BIT)

#define COPS_WUNTIME_CYCWES_BIT 1
#define COPS_WUNTIME_CYCWES BIT(COPS_WUNTIME_CYCWES_BIT)

	int (*awwoc)(stwuct intew_context *ce);

	void (*wevoke)(stwuct intew_context *ce, stwuct i915_wequest *wq,
		       unsigned int pweempt_timeout_ms);

	void (*cwose)(stwuct intew_context *ce);

	int (*pwe_pin)(stwuct intew_context *ce, stwuct i915_gem_ww_ctx *ww, void **vaddw);
	int (*pin)(stwuct intew_context *ce, void *vaddw);
	void (*unpin)(stwuct intew_context *ce);
	void (*post_unpin)(stwuct intew_context *ce);

	void (*cancew_wequest)(stwuct intew_context *ce,
			       stwuct i915_wequest *wq);

	void (*entew)(stwuct intew_context *ce);
	void (*exit)(stwuct intew_context *ce);

	void (*sched_disabwe)(stwuct intew_context *ce);

	void (*update_stats)(stwuct intew_context *ce);

	void (*weset)(stwuct intew_context *ce);
	void (*destwoy)(stwuct kwef *kwef);

	/* viwtuaw/pawawwew engine/context intewface */
	stwuct intew_context *(*cweate_viwtuaw)(stwuct intew_engine_cs **engine,
						unsigned int count,
						unsigned wong fwags);
	stwuct intew_context *(*cweate_pawawwew)(stwuct intew_engine_cs **engines,
						 unsigned int num_sibwings,
						 unsigned int width);
	stwuct intew_engine_cs *(*get_sibwing)(stwuct intew_engine_cs *engine,
					       unsigned int sibwing);
};

stwuct intew_context {
	/*
	 * Note: Some fiewds may be accessed undew WCU.
	 *
	 * Unwess othewwise noted a fiewd can safewy be assumed to be pwotected
	 * by stwong wefewence counting.
	 */
	union {
		stwuct kwef wef; /* no kwef_get_unwess_zewo()! */
		stwuct wcu_head wcu;
	};

	stwuct intew_engine_cs *engine;
	stwuct intew_engine_cs *infwight;
#define __intew_context_infwight(engine) ptw_mask_bits(engine, 3)
#define __intew_context_infwight_count(engine) ptw_unmask_bits(engine, 3)
#define intew_context_infwight(ce) \
	__intew_context_infwight(WEAD_ONCE((ce)->infwight))
#define intew_context_infwight_count(ce) \
	__intew_context_infwight_count(WEAD_ONCE((ce)->infwight))

	stwuct i915_addwess_space *vm;
	stwuct i915_gem_context __wcu *gem_context;

	/*
	 * @signaw_wock pwotects the wist of wequests that need signawing,
	 * @signaws. Whiwe thewe awe any wequests that need signawing,
	 * we add the context to the bweadcwumbs wowkew, and wemove it
	 * upon compwetion/cancewwation of the wast wequest.
	 */
	stwuct wist_head signaw_wink; /* Accessed undew WCU */
	stwuct wist_head signaws; /* Guawded by signaw_wock */
	spinwock_t signaw_wock; /* pwotects signaws, the wist of wequests */

	stwuct i915_vma *state;
	u32 wing_size;
	stwuct intew_wing *wing;
	stwuct intew_timewine *timewine;
	intew_wakewef_t wakewef;

	unsigned wong fwags;
#define CONTEXT_BAWWIEW_BIT		0
#define CONTEXT_AWWOC_BIT		1
#define CONTEXT_INIT_BIT		2
#define CONTEXT_VAWID_BIT		3
#define CONTEXT_CWOSED_BIT		4
#define CONTEXT_USE_SEMAPHOWES		5
#define CONTEXT_BANNED			6
#define CONTEXT_FOWCE_SINGWE_SUBMISSION	7
#define CONTEXT_NOPWEEMPT		8
#define CONTEXT_WWCA_DIWTY		9
#define CONTEXT_GUC_INIT		10
#define CONTEXT_PEWMA_PIN		11
#define CONTEXT_IS_PAWKING		12
#define CONTEXT_EXITING			13

	stwuct {
		u64 timeout_us;
	} watchdog;

	u32 *wwc_weg_state;
	union {
		stwuct {
			u32 wwca;
			u32 ccid;
		};
		u64 desc;
	} wwc;
	u32 tag; /* cookie passed to HW to twack this context on submission */

	/** stats: Context GPU engine busyness twacking. */
	stwuct intew_context_stats {
		u64 active;

		/* Time on GPU as twacked by the hw. */
		stwuct {
			stwuct ewma_wuntime avg;
			u64 totaw;
			u32 wast;
			I915_SEWFTEST_DECWAWE(u32 num_undewfwow);
			I915_SEWFTEST_DECWAWE(u32 max_undewfwow);
		} wuntime;
	} stats;

	unsigned int active_count; /* pwotected by timewine->mutex */

	atomic_t pin_count;
	stwuct mutex pin_mutex; /* guawds pinning and associated on-gpuing */

	/**
	 * active: Active twackew fow the wq activity (inc. extewnaw) on this
	 * intew_context object.
	 */
	stwuct i915_active active;

	const stwuct intew_context_ops *ops;

	/** sseu: Contwow eu/swice pawtitioning */
	stwuct intew_sseu sseu;

	/**
	 * pinned_contexts_wink: Wist wink fow the engine's pinned contexts.
	 * This is onwy used if this is a pewma-pinned kewnew context and
	 * the wist is assumed to onwy be manipuwated duwing dwivew woad
	 * ow unwoad time so no mutex pwotection cuwwentwy.
	 */
	stwuct wist_head pinned_contexts_wink;

	u8 wa_bb_page; /* if set, page num wesewved fow context wowkawounds */

	stwuct {
		/** @wock: pwotects evewything in guc_state */
		spinwock_t wock;
		/**
		 * @sched_state: scheduwing state of this context using GuC
		 * submission
		 */
		u32 sched_state;
		/*
		 * @fences: maintains a wist of wequests that awe cuwwentwy
		 * being fenced untiw a GuC opewation compwetes
		 */
		stwuct wist_head fences;
		/**
		 * @bwocked: fence used to signaw when the bwocking of a
		 * context's submissions is compwete.
		 */
		stwuct i915_sw_fence bwocked;
		/** @wequests: wist of active wequests on this context */
		stwuct wist_head wequests;
		/** @pwio: the context's cuwwent guc pwiowity */
		u8 pwio;
		/**
		 * @pwio_count: a countew of the numbew wequests in fwight in
		 * each pwiowity bucket
		 */
		u32 pwio_count[GUC_CWIENT_PWIOWITY_NUM];
		/**
		 * @sched_disabwe_deway_wowk: wowkew to disabwe scheduwing on this
		 * context
		 */
		stwuct dewayed_wowk sched_disabwe_deway_wowk;
	} guc_state;

	stwuct {
		/**
		 * @id: handwe which is used to uniquewy identify this context
		 * with the GuC, pwotected by guc->submission_state.wock
		 */
		u16 id;
		/**
		 * @wef: the numbew of wefewences to the guc_id, when
		 * twansitioning in and out of zewo pwotected by
		 * guc->submission_state.wock
		 */
		atomic_t wef;
		/**
		 * @wink: in guc->guc_id_wist when the guc_id has no wefs but is
		 * stiww vawid, pwotected by guc->submission_state.wock
		 */
		stwuct wist_head wink;
	} guc_id;

	/**
	 * @destwoyed_wink: wink in guc->submission_state.destwoyed_contexts, in
	 * wist when context is pending to be destwoyed (dewegistewed with the
	 * GuC), pwotected by guc->submission_state.wock
	 */
	stwuct wist_head destwoyed_wink;

	/** @pawawwew: sub-stwuctuwe fow pawawwew submission membews */
	stwuct {
		union {
			/**
			 * @chiwd_wist: pawent's wist of chiwdwen
			 * contexts, no pwotection as immutabwe aftew context
			 * cweation
			 */
			stwuct wist_head chiwd_wist;
			/**
			 * @chiwd_wink: chiwd's wink into pawent's wist of
			 * chiwdwen
			 */
			stwuct wist_head chiwd_wink;
		};
		/** @pawent: pointew to pawent if chiwd */
		stwuct intew_context *pawent;
		/**
		 * @wast_wq: wast wequest submitted on a pawawwew context, used
		 * to insewt submit fences between wequests in the pawawwew
		 * context
		 */
		stwuct i915_wequest *wast_wq;
		/**
		 * @fence_context: fence context composite fence when doing
		 * pawawwew submission
		 */
		u64 fence_context;
		/**
		 * @seqno: seqno fow composite fence when doing pawawwew
		 * submission
		 */
		u32 seqno;
		/** @numbew_chiwdwen: numbew of chiwdwen if pawent */
		u8 numbew_chiwdwen;
		/** @chiwd_index: index into chiwd_wist if chiwd */
		u8 chiwd_index;
		/** @guc: GuC specific membews fow pawawwew submission */
		stwuct {
			/** @wqi_head: cached head pointew in wowk queue */
			u16 wqi_head;
			/** @wqi_taiw: cached taiw pointew in wowk queue */
			u16 wqi_taiw;
			/** @wq_head: pointew to the actuaw head in wowk queue */
			u32 *wq_head;
			/** @wq_taiw: pointew to the actuaw head in wowk queue */
			u32 *wq_taiw;
			/** @wq_status: pointew to the status in wowk queue */
			u32 *wq_status;

			/**
			 * @pawent_page: page in context state (ce->state) used
			 * by pawent fow wowk queue, pwocess descwiptow
			 */
			u8 pawent_page;
		} guc;
	} pawawwew;

#ifdef CONFIG_DWM_I915_SEWFTEST
	/**
	 * @dwop_scheduwe_enabwe: Fowce dwop of scheduwe enabwe G2H fow sewftest
	 */
	boow dwop_scheduwe_enabwe;

	/**
	 * @dwop_scheduwe_disabwe: Fowce dwop of scheduwe disabwe G2H fow
	 * sewftest
	 */
	boow dwop_scheduwe_disabwe;

	/**
	 * @dwop_dewegistew: Fowce dwop of dewegistew G2H fow sewftest
	 */
	boow dwop_dewegistew;
#endif
};

#endif /* __INTEW_CONTEXT_TYPES__ */
