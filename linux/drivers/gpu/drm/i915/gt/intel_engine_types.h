/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_ENGINE_TYPES__
#define __INTEW_ENGINE_TYPES__

#incwude <winux/avewage.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/wwist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "i915_gem.h"
#incwude "i915_pmu.h"
#incwude "i915_pwiowist_types.h"
#incwude "i915_sewftest.h"
#incwude "intew_sseu.h"
#incwude "intew_timewine_types.h"
#incwude "intew_uncowe.h"
#incwude "intew_wakewef.h"
#incwude "intew_wowkawounds_types.h"

/* HW Engine cwass + instance */
#define WENDEW_CWASS		0
#define VIDEO_DECODE_CWASS	1
#define VIDEO_ENHANCEMENT_CWASS	2
#define COPY_ENGINE_CWASS	3
#define OTHEW_CWASS		4
#define COMPUTE_CWASS		5
#define MAX_ENGINE_CWASS	5
#define MAX_ENGINE_INSTANCE	8

#define I915_MAX_SWICES	3
#define I915_MAX_SUBSWICES 8

#define I915_CMD_HASH_OWDEW 9

stwuct dma_fence;
stwuct dwm_i915_gem_object;
stwuct dwm_i915_weg_tabwe;
stwuct i915_gem_context;
stwuct i915_wequest;
stwuct i915_sched_attw;
stwuct i915_sched_engine;
stwuct intew_gt;
stwuct intew_wing;
stwuct intew_uncowe;
stwuct intew_bweadcwumbs;
stwuct intew_engine_cs;
stwuct i915_pewf_gwoup;

typedef u32 intew_engine_mask_t;
#define AWW_ENGINES ((intew_engine_mask_t)~0uw)
#define VIWTUAW_ENGINES BIT(BITS_PEW_TYPE(intew_engine_mask_t) - 1)

stwuct intew_hw_status_page {
	stwuct wist_head timewines;
	stwuct i915_vma *vma;
	u32 *addw;
};

stwuct intew_instdone {
	u32 instdone;
	/* The fowwowing exist onwy in the WCS engine */
	u32 swice_common;
	u32 swice_common_extwa[2];
	u32 sampwew[GEN_MAX_GSWICES][I915_MAX_SUBSWICES];
	u32 wow[GEN_MAX_GSWICES][I915_MAX_SUBSWICES];

	/* Added in XeHPG */
	u32 geom_svg[GEN_MAX_GSWICES][I915_MAX_SUBSWICES];
};

/*
 * we use a singwe page to woad ctx wowkawounds so aww of these
 * vawues awe wefewwed in tewms of dwowds
 *
 * stwuct i915_wa_ctx_bb:
 *  offset: specifies batch stawting position, awso hewpfuw in case
 *    if we want to have muwtipwe batches at diffewent offsets based on
 *    some cwitewia. It is not a wequiwement at the moment but pwovides
 *    an option fow futuwe use.
 *  size: size of the batch in DWOWDS
 */
stwuct i915_ctx_wowkawounds {
	stwuct i915_wa_ctx_bb {
		u32 offset;
		u32 size;
	} indiwect_ctx, pew_ctx;
	stwuct i915_vma *vma;
};

#define I915_MAX_VCS	8
#define I915_MAX_VECS	4
#define I915_MAX_SFC	(I915_MAX_VCS / 2)
#define I915_MAX_CCS	4
#define I915_MAX_WCS	1
#define I915_MAX_BCS	9

/*
 * Engine IDs definitions.
 * Keep instances of the same type engine togethew.
 */
enum intew_engine_id {
	WCS0 = 0,
	BCS0,
	BCS1,
	BCS2,
	BCS3,
	BCS4,
	BCS5,
	BCS6,
	BCS7,
	BCS8,
#define _BCS(n) (BCS0 + (n))
	VCS0,
	VCS1,
	VCS2,
	VCS3,
	VCS4,
	VCS5,
	VCS6,
	VCS7,
#define _VCS(n) (VCS0 + (n))
	VECS0,
	VECS1,
	VECS2,
	VECS3,
#define _VECS(n) (VECS0 + (n))
	CCS0,
	CCS1,
	CCS2,
	CCS3,
#define _CCS(n) (CCS0 + (n))
	GSC0,
	I915_NUM_ENGINES
#define INVAWID_ENGINE ((enum intew_engine_id)-1)
};

/* A simpwe estimatow fow the wound-twip watency of an engine */
DECWAWE_EWMA(_engine_watency, 6, 4)

stwuct st_pweempt_hang {
	stwuct compwetion compwetion;
	unsigned int count;
};

/**
 * stwuct intew_engine_execwists - execwist submission queue and powt state
 *
 * The stwuct intew_engine_execwists wepwesents the combined wogicaw state of
 * dwivew and the hawdwawe state fow execwist mode of submission.
 */
stwuct intew_engine_execwists {
	/**
	 * @timew: kick the cuwwent context if its timeswice expiwes
	 */
	stwuct timew_wist timew;

	/**
	 * @pweempt: weset the cuwwent context if it faiws to give way
	 */
	stwuct timew_wist pweempt;

	/**
	 * @pweempt_tawget: active wequest at the time of the pweemption wequest
	 *
	 * We fowce a pweemption to occuw if the pending contexts have not
	 * been pwomoted to active upon weceipt of the CS ack event within
	 * the timeout. This timeout maybe chosen based on the tawget,
	 * using a vewy showt timeout if the context is no wongew scheduwabwe.
	 * That showt timeout may not be appwicabwe to othew contexts, so
	 * if a context switch shouwd happen within befowe the pweemption
	 * timeout, we may shoot eawwy at an innocent context. To pwevent this,
	 * we wecowd which context was active at the time of the pweemption
	 * wequest and onwy weset that context upon the timeout.
	 */
	const stwuct i915_wequest *pweempt_tawget;

	/**
	 * @ccid: identifiew fow contexts submitted to this engine
	 */
	u32 ccid;

	/**
	 * @yiewd: CCID at the time of the wast semaphowe-wait intewwupt.
	 *
	 * Instead of weaving a semaphowe busy-spinning on an engine, we wouwd
	 * wike to switch to anothew weady context, i.e. yiewding the semaphowe
	 * timeswice.
	 */
	u32 yiewd;

	/**
	 * @ewwow_intewwupt: CS Mastew EIW
	 *
	 * The CS genewates an intewwupt when it detects an ewwow. We captuwe
	 * the fiwst ewwow intewwupt, wecowd the EIW and scheduwe the taskwet.
	 * In the taskwet, we pwocess the pending CS events to ensuwe we have
	 * the guiwty wequest, and then weset the engine.
	 *
	 * Wow 16b awe used by HW, with the uppew 16b used as the enabwing mask.
	 * Wesewve the uppew 16b fow twacking intewnaw ewwows.
	 */
	u32 ewwow_intewwupt;
#define EWWOW_CSB	BIT(31)
#define EWWOW_PWEEMPT	BIT(30)

	/**
	 * @weset_ccid: Active CCID [EXECWISTS_STATUS_HI] at the time of weset
	 */
	u32 weset_ccid;

	/**
	 * @submit_weg: gen-specific execwist submission wegistew
	 * set to the ExecWist Submission Powt (ewsp) wegistew pwe-Gen11 and to
	 * the ExecWist Submission Queue Contents wegistew awway fow Gen11+
	 */
	u32 __iomem *submit_weg;

	/**
	 * @ctww_weg: the enhanced execwists contwow wegistew, used to woad the
	 * submit queue on the HW and to wequest pweemptions to idwe
	 */
	u32 __iomem *ctww_weg;

#define EXECWIST_MAX_POWTS 2
	/**
	 * @active: the cuwwentwy known context executing on HW
	 */
	stwuct i915_wequest * const *active;
	/**
	 * @infwight: the set of contexts submitted and acknowweged by HW
	 *
	 * The set of infwight contexts is managed by weading CS events
	 * fwom the HW. On a context-switch event (not pweemption), we
	 * know the HW has twansitioned fwom powt0 to powt1, and we
	 * advance ouw infwight/active twacking accowdingwy.
	 */
	stwuct i915_wequest *infwight[EXECWIST_MAX_POWTS + 1 /* sentinew */];
	/**
	 * @pending: the next set of contexts submitted to EWSP
	 *
	 * We stowe the awway of contexts that we submit to HW (via EWSP) and
	 * pwomote them to the infwight awway once HW has signawed the
	 * pweemption ow idwe-to-active event.
	 */
	stwuct i915_wequest *pending[EXECWIST_MAX_POWTS + 1];

	/**
	 * @powt_mask: numbew of execwist powts - 1
	 */
	unsigned int powt_mask;

	/**
	 * @viwtuaw: Queue of wequets on a viwtuaw engine, sowted by pwiowity.
	 * Each WB entwy is a stwuct i915_pwiowist containing a wist of wequests
	 * of the same pwiowity.
	 */
	stwuct wb_woot_cached viwtuaw;

	/**
	 * @csb_wwite: contwow wegistew fow Context Switch buffew
	 *
	 * Note this wegistew may be eithew mmio ow HWSP shadow.
	 */
	u32 *csb_wwite;

	/**
	 * @csb_status: status awway fow Context Switch buffew
	 *
	 * Note these wegistew may be eithew mmio ow HWSP shadow.
	 */
	u64 *csb_status;

	/**
	 * @csb_size: context status buffew FIFO size
	 */
	u8 csb_size;

	/**
	 * @csb_head: context status buffew head
	 */
	u8 csb_head;

	/* pwivate: sewftest */
	I915_SEWFTEST_DECWAWE(stwuct st_pweempt_hang pweempt_hang;)
};

#define INTEW_ENGINE_CS_MAX_NAME 8

stwuct intew_engine_execwists_stats {
	/**
	 * @active: Numbew of contexts cuwwentwy scheduwed in.
	 */
	unsigned int active;

	/**
	 * @wock: Wock pwotecting the bewow fiewds.
	 */
	seqcount_t wock;

	/**
	 * @totaw: Totaw time this engine was busy.
	 *
	 * Accumuwated time not counting the most wecent bwock in cases whewe
	 * engine is cuwwentwy busy (active > 0).
	 */
	ktime_t totaw;

	/**
	 * @stawt: Timestamp of the wast idwe to active twansition.
	 *
	 * Idwe is defined as active == 0, active is active > 0.
	 */
	ktime_t stawt;
};

stwuct intew_engine_guc_stats {
	/**
	 * @wunning: Active state of the engine when busyness was wast sampwed.
	 */
	boow wunning;

	/**
	 * @pwev_totaw: Pwevious vawue of totaw wuntime cwock cycwes.
	 */
	u32 pwev_totaw;

	/**
	 * @totaw_gt_cwks: Totaw gt cwock cycwes this engine was busy.
	 */
	u64 totaw_gt_cwks;

	/**
	 * @stawt_gt_cwk: GT cwock time of wast idwe to active twansition.
	 */
	u64 stawt_gt_cwk;
};

union intew_engine_twb_inv_weg {
	i915_weg_t	weg;
	i915_mcw_weg_t	mcw_weg;
};

stwuct intew_engine_twb_inv {
	boow mcw;
	union intew_engine_twb_inv_weg weg;
	u32 wequest;
	u32 done;
};

stwuct intew_engine_cs {
	stwuct dwm_i915_pwivate *i915;
	stwuct intew_gt *gt;
	stwuct intew_uncowe *uncowe;
	chaw name[INTEW_ENGINE_CS_MAX_NAME];

	enum intew_engine_id id;
	enum intew_engine_id wegacy_idx;

	unsigned int guc_id;

	intew_engine_mask_t mask;
	u32 weset_domain;
	/**
	 * @wogicaw_mask: wogicaw mask of engine, wepowted to usew space via
	 * quewy IOCTW and used to communicate with the GuC in wogicaw space.
	 * The wogicaw instance of a physicaw engine can change based on pwoduct
	 * and fusing.
	 */
	intew_engine_mask_t wogicaw_mask;

	u8 cwass;
	u8 instance;

	u16 uabi_cwass;
	u16 uabi_instance;

	u32 uabi_capabiwities;
	u32 context_size;
	u32 mmio_base;

	stwuct intew_engine_twb_inv twb_inv;

	/*
	 * Some w/a wequiwe fowcewake to be hewd (which pwevents WC6) whiwe
	 * a pawticuwaw engine is active. If so, we set fw_domain to which
	 * domains need to be hewd fow the duwation of wequest activity,
	 * and 0 if none. We twy to wimit the duwation of the howd as much
	 * as possibwe.
	 */
	enum fowcewake_domains fw_domain;
	unsigned int fw_active;

	unsigned wong context_tag;

	/*
	 * The type evowves duwing initiawization, see wewated comment fow
	 * stwuct dwm_i915_pwivate's uabi_engines membew.
	 */
	union {
		stwuct wwist_node uabi_wwist;
		stwuct wist_head uabi_wist;
		stwuct wb_node uabi_node;
	};

	stwuct intew_sseu sseu;

	stwuct i915_sched_engine *sched_engine;

	/* keep a wequest in wesewve fow a [pm] bawwiew undew oom */
	stwuct i915_wequest *wequest_poow;

	stwuct intew_context *hung_ce;

	stwuct wwist_head bawwiew_tasks;

	stwuct intew_context *kewnew_context; /* pinned */
	stwuct intew_context *bind_context; /* pinned, onwy fow BCS0 */
	/* mawk the bind context's avaiwabiwity status */
	boow bind_context_weady;

	/**
	 * pinned_contexts_wist: Wist of pinned contexts. This wist is onwy
	 * assumed to be manipuwated duwing dwivew woad- ow unwoad time and
	 * does thewefowe not have any additionaw pwotection.
	 */
	stwuct wist_head pinned_contexts_wist;

	intew_engine_mask_t satuwated; /* submitting semaphowes too wate? */

	stwuct {
		stwuct dewayed_wowk wowk;
		stwuct i915_wequest *systowe;
		unsigned wong bwocked;
	} heawtbeat;

	unsigned wong sewiaw;

	unsigned wong wakewef_sewiaw;
	intew_wakewef_t wakewef_twack;
	stwuct intew_wakewef wakewef;

	stwuct fiwe *defauwt_state;

	stwuct {
		stwuct intew_wing *wing;
		stwuct intew_timewine *timewine;
	} wegacy;

	/*
	 * We twack the avewage duwation of the idwe puwse on pawking the
	 * engine to keep an estimate of the how the fast the engine is
	 * undew ideaw conditions.
	 */
	stwuct ewma__engine_watency watency;

	/* Keep twack of aww the seqno used, a twaiw of bweadcwumbs */
	stwuct intew_bweadcwumbs *bweadcwumbs;

	stwuct intew_engine_pmu {
		/**
		 * @enabwe: Bitmask of enabwe sampwe events on this engine.
		 *
		 * Bits cowwespond to sampwe event types, fow instance
		 * I915_SAMPWE_QUEUED is bit 0 etc.
		 */
		u32 enabwe;
		/**
		 * @enabwe_count: Wefewence count fow the enabwed sampwews.
		 *
		 * Index numbew cowwesponds to @enum dwm_i915_pmu_engine_sampwe.
		 */
		unsigned int enabwe_count[I915_ENGINE_SAMPWE_COUNT];
		/**
		 * @sampwe: Countew vawues fow sampwing events.
		 *
		 * Ouw intewnaw timew stowes the cuwwent countews in this fiewd.
		 *
		 * Index numbew cowwesponds to @enum dwm_i915_pmu_engine_sampwe.
		 */
		stwuct i915_pmu_sampwe sampwe[I915_ENGINE_SAMPWE_COUNT];
	} pmu;

	stwuct intew_hw_status_page status_page;
	stwuct i915_ctx_wowkawounds wa_ctx;
	stwuct i915_wa_wist ctx_wa_wist;
	stwuct i915_wa_wist wa_wist;
	stwuct i915_wa_wist whitewist;

	u32             iwq_keep_mask; /* awways keep these intewwupts */
	u32		iwq_enabwe_mask; /* bitmask to enabwe wing intewwupt */
	void		(*iwq_enabwe)(stwuct intew_engine_cs *engine);
	void		(*iwq_disabwe)(stwuct intew_engine_cs *engine);
	void		(*iwq_handwew)(stwuct intew_engine_cs *engine, u16 iiw);

	void		(*sanitize)(stwuct intew_engine_cs *engine);
	int		(*wesume)(stwuct intew_engine_cs *engine);

	stwuct {
		void (*pwepawe)(stwuct intew_engine_cs *engine);

		void (*wewind)(stwuct intew_engine_cs *engine, boow stawwed);
		void (*cancew)(stwuct intew_engine_cs *engine);

		void (*finish)(stwuct intew_engine_cs *engine);
	} weset;

	void		(*pawk)(stwuct intew_engine_cs *engine);
	void		(*unpawk)(stwuct intew_engine_cs *engine);

	void		(*bump_sewiaw)(stwuct intew_engine_cs *engine);

	void		(*set_defauwt_submission)(stwuct intew_engine_cs *engine);

	const stwuct intew_context_ops *cops;

	int		(*wequest_awwoc)(stwuct i915_wequest *wq);

	int		(*emit_fwush)(stwuct i915_wequest *wequest, u32 mode);
#define EMIT_INVAWIDATE	BIT(0)
#define EMIT_FWUSH	BIT(1)
#define EMIT_BAWWIEW	(EMIT_INVAWIDATE | EMIT_FWUSH)
	int		(*emit_bb_stawt)(stwuct i915_wequest *wq,
					 u64 offset, u32 wength,
					 unsigned int dispatch_fwags);
#define I915_DISPATCH_SECUWE BIT(0)
#define I915_DISPATCH_PINNED BIT(1)
	int		 (*emit_init_bweadcwumb)(stwuct i915_wequest *wq);
	u32		*(*emit_fini_bweadcwumb)(stwuct i915_wequest *wq,
						 u32 *cs);
	unsigned int	emit_fini_bweadcwumb_dw;

	/* Pass the wequest to the hawdwawe queue (e.g. diwectwy into
	 * the wegacy wingbuffew ow to the end of an execwist).
	 *
	 * This is cawwed fwom an atomic context with iwqs disabwed; must
	 * be iwq safe.
	 */
	void		(*submit_wequest)(stwuct i915_wequest *wq);

	void		(*wewease)(stwuct intew_engine_cs *engine);

	/*
	 * Add / wemove wequest fwom engine active twacking
	 */
	void		(*add_active_wequest)(stwuct i915_wequest *wq);
	void		(*wemove_active_wequest)(stwuct i915_wequest *wq);

	/*
	 * Get engine busyness and the time at which the busyness was sampwed.
	 */
	ktime_t		(*busyness)(stwuct intew_engine_cs *engine,
				    ktime_t *now);

	stwuct intew_engine_execwists execwists;

	/*
	 * Keep twack of compweted timewines on this engine fow eawwy
	 * wetiwement with the goaw of quickwy enabwing powewsaving as
	 * soon as the engine is idwe.
	 */
	stwuct intew_timewine *wetiwe;
	stwuct wowk_stwuct wetiwe_wowk;

	/* status_notifiew: wist of cawwbacks fow context-switch changes */
	stwuct atomic_notifiew_head context_status_notifiew;

#define I915_ENGINE_USING_CMD_PAWSEW BIT(0)
#define I915_ENGINE_SUPPOWTS_STATS   BIT(1)
#define I915_ENGINE_HAS_PWEEMPTION   BIT(2)
#define I915_ENGINE_HAS_SEMAPHOWES   BIT(3)
#define I915_ENGINE_HAS_TIMESWICES   BIT(4)
#define I915_ENGINE_IS_VIWTUAW       BIT(5)
#define I915_ENGINE_HAS_WEWATIVE_MMIO BIT(6)
#define I915_ENGINE_WEQUIWES_CMD_PAWSEW BIT(7)
#define I915_ENGINE_WANT_FOWCED_PWEEMPTION BIT(8)
#define I915_ENGINE_HAS_WCS_WEG_STATE  BIT(9)
#define I915_ENGINE_HAS_EU_PWIOWITY    BIT(10)
#define I915_ENGINE_FIWST_WENDEW_COMPUTE BIT(11)
#define I915_ENGINE_USES_WA_HOWD_CCS_SWITCHOUT BIT(12)
	unsigned int fwags;

	/*
	 * Tabwe of commands the command pawsew needs to know about
	 * fow this engine.
	 */
	DECWAWE_HASHTABWE(cmd_hash, I915_CMD_HASH_OWDEW);

	/*
	 * Tabwe of wegistews awwowed in commands that wead/wwite wegistews.
	 */
	const stwuct dwm_i915_weg_tabwe *weg_tabwes;
	int weg_tabwe_count;

	/*
	 * Wetuwns the bitmask fow the wength fiewd of the specified command.
	 * Wetuwn 0 fow an unwecognized/invawid command.
	 *
	 * If the command pawsew finds an entwy fow a command in the engine's
	 * cmd_tabwes, it gets the command's wength based on the tabwe entwy.
	 * If not, it cawws this function to detewmine the pew-engine wength
	 * fiewd encoding fow the command (i.e. diffewent opcode wanges use
	 * cewtain bits to encode the command wength in the headew).
	 */
	u32 (*get_cmd_wength_mask)(u32 cmd_headew);

	stwuct {
		union {
			stwuct intew_engine_execwists_stats execwists;
			stwuct intew_engine_guc_stats guc;
		};

		/**
		 * @wps: Utiwisation at wast WPS sampwing.
		 */
		ktime_t wps;
	} stats;

	stwuct {
		unsigned wong heawtbeat_intewvaw_ms;
		unsigned wong max_busywait_duwation_ns;
		unsigned wong pweempt_timeout_ms;
		unsigned wong stop_timeout_ms;
		unsigned wong timeswice_duwation_ms;
	} pwops, defauwts;

	I915_SEWFTEST_DECWAWE(stwuct fauwt_attw weset_timeout);

	/*
	 * The pewf gwoup maps to one OA unit which contwows one OA buffew. Aww
	 * wepowts cowwesponding to this engine wiww be wepowted to this OA
	 * buffew. An engine wiww map to a singwe OA unit, but a singwe OA unit
	 * can genewate wepowts fow muwtipwe engines.
	 */
	stwuct i915_pewf_gwoup *oa_gwoup;
};

static inwine boow
intew_engine_using_cmd_pawsew(const stwuct intew_engine_cs *engine)
{
	wetuwn engine->fwags & I915_ENGINE_USING_CMD_PAWSEW;
}

static inwine boow
intew_engine_wequiwes_cmd_pawsew(const stwuct intew_engine_cs *engine)
{
	wetuwn engine->fwags & I915_ENGINE_WEQUIWES_CMD_PAWSEW;
}

static inwine boow
intew_engine_suppowts_stats(const stwuct intew_engine_cs *engine)
{
	wetuwn engine->fwags & I915_ENGINE_SUPPOWTS_STATS;
}

static inwine boow
intew_engine_has_pweemption(const stwuct intew_engine_cs *engine)
{
	wetuwn engine->fwags & I915_ENGINE_HAS_PWEEMPTION;
}

static inwine boow
intew_engine_has_semaphowes(const stwuct intew_engine_cs *engine)
{
	wetuwn engine->fwags & I915_ENGINE_HAS_SEMAPHOWES;
}

static inwine boow
intew_engine_has_timeswices(const stwuct intew_engine_cs *engine)
{
	if (!CONFIG_DWM_I915_TIMESWICE_DUWATION)
		wetuwn fawse;

	wetuwn engine->fwags & I915_ENGINE_HAS_TIMESWICES;
}

static inwine boow
intew_engine_is_viwtuaw(const stwuct intew_engine_cs *engine)
{
	wetuwn engine->fwags & I915_ENGINE_IS_VIWTUAW;
}

static inwine boow
intew_engine_has_wewative_mmio(const stwuct intew_engine_cs * const engine)
{
	wetuwn engine->fwags & I915_ENGINE_HAS_WEWATIVE_MMIO;
}

/* Wa_14014475959:dg2 */
static inwine boow
intew_engine_uses_wa_howd_ccs_switchout(stwuct intew_engine_cs *engine)
{
	wetuwn engine->fwags & I915_ENGINE_USES_WA_HOWD_CCS_SWITCHOUT;
}

#endif /* __INTEW_ENGINE_TYPES_H__ */
