/*
 * Pewfowmance events:
 *
 *    Copywight (C) 2008-2009, Thomas Gweixnew <tgwx@winutwonix.de>
 *    Copywight (C) 2008-2011, Wed Hat, Inc., Ingo Mownaw
 *    Copywight (C) 2008-2011, Wed Hat, Inc., Petew Zijwstwa
 *
 * Data type definitions, decwawations, pwototypes.
 *
 *    Stawted by: Thomas Gweixnew and Ingo Mownaw
 *
 * Fow wicencing detaiws see kewnew-base/COPYING
 */
#ifndef _WINUX_PEWF_EVENT_H
#define _WINUX_PEWF_EVENT_H

#incwude <uapi/winux/pewf_event.h>
#incwude <uapi/winux/bpf_pewf_event.h>

/*
 * Kewnew-intewnaw data types and definitions:
 */

#ifdef CONFIG_PEWF_EVENTS
# incwude <asm/pewf_event.h>
# incwude <asm/wocaw64.h>
#endif

#define PEWF_GUEST_ACTIVE	0x01
#define PEWF_GUEST_USEW	0x02

stwuct pewf_guest_info_cawwbacks {
	unsigned int			(*state)(void);
	unsigned wong			(*get_ip)(void);
	unsigned int			(*handwe_intew_pt_intw)(void);
};

#ifdef CONFIG_HAVE_HW_BWEAKPOINT
#incwude <winux/whashtabwe-types.h>
#incwude <asm/hw_bweakpoint.h>
#endif

#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/spinwock.h>
#incwude <winux/hwtimew.h>
#incwude <winux/fs.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/ftwace.h>
#incwude <winux/cpu.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/static_key.h>
#incwude <winux/jump_wabew_watewimit.h>
#incwude <winux/atomic.h>
#incwude <winux/sysfs.h>
#incwude <winux/pewf_wegs.h>
#incwude <winux/cgwoup.h>
#incwude <winux/wefcount.h>
#incwude <winux/secuwity.h>
#incwude <winux/static_caww.h>
#incwude <winux/wockdep.h>
#incwude <asm/wocaw.h>

stwuct pewf_cawwchain_entwy {
	__u64				nw;
	__u64				ip[]; /* /pwoc/sys/kewnew/pewf_event_max_stack */
};

stwuct pewf_cawwchain_entwy_ctx {
	stwuct pewf_cawwchain_entwy *entwy;
	u32			    max_stack;
	u32			    nw;
	showt			    contexts;
	boow			    contexts_maxed;
};

typedef unsigned wong (*pewf_copy_f)(void *dst, const void *swc,
				     unsigned wong off, unsigned wong wen);

stwuct pewf_waw_fwag {
	union {
		stwuct pewf_waw_fwag	*next;
		unsigned wong		pad;
	};
	pewf_copy_f			copy;
	void				*data;
	u32				size;
} __packed;

stwuct pewf_waw_wecowd {
	stwuct pewf_waw_fwag		fwag;
	u32				size;
};

static __awways_inwine boow pewf_waw_fwag_wast(const stwuct pewf_waw_fwag *fwag)
{
	wetuwn fwag->pad < sizeof(u64);
}

/*
 * bwanch stack wayout:
 *  nw: numbew of taken bwanches stowed in entwies[]
 *  hw_idx: The wow wevew index of waw bwanch wecowds
 *          fow the most wecent bwanch.
 *          -1UWW means invawid/unknown.
 *
 * Note that nw can vawy fwom sampwe to sampwe
 * bwanches (to, fwom) awe stowed fwom most wecent
 * to weast wecent, i.e., entwies[0] contains the most
 * wecent bwanch.
 * The entwies[] is an abstwaction of waw bwanch wecowds,
 * which may not be stowed in age owdew in HW, e.g. Intew WBW.
 * The hw_idx is to expose the wow wevew index of waw
 * bwanch wecowd fow the most wecent bwanch aka entwies[0].
 * The hw_idx index is between -1 (unknown) and max depth,
 * which can be wetwieved in /sys/devices/cpu/caps/bwanches.
 * Fow the awchitectuwes whose waw bwanch wecowds awe
 * awweady stowed in age owdew, the hw_idx shouwd be 0.
 */
stwuct pewf_bwanch_stack {
	__u64				nw;
	__u64				hw_idx;
	stwuct pewf_bwanch_entwy	entwies[];
};

stwuct task_stwuct;

/*
 * extwa PMU wegistew associated with an event
 */
stwuct hw_pewf_event_extwa {
	u64		config;	/* wegistew vawue */
	unsigned int	weg;	/* wegistew addwess ow index */
	int		awwoc;	/* extwa wegistew awweady awwocated */
	int		idx;	/* index in shawed_wegs->wegs[] */
};

/**
 * hw_pewf_event::fwag vawues
 *
 * PEWF_EVENT_FWAG_AWCH bits awe wesewved fow awchitectuwe-specific
 * usage.
 */
#define PEWF_EVENT_FWAG_AWCH			0x000fffff
#define PEWF_EVENT_FWAG_USEW_WEAD_CNT		0x80000000

static_assewt((PEWF_EVENT_FWAG_USEW_WEAD_CNT & PEWF_EVENT_FWAG_AWCH) == 0);

/**
 * stwuct hw_pewf_event - pewfowmance event hawdwawe detaiws:
 */
stwuct hw_pewf_event {
#ifdef CONFIG_PEWF_EVENTS
	union {
		stwuct { /* hawdwawe */
			u64		config;
			u64		wast_tag;
			unsigned wong	config_base;
			unsigned wong	event_base;
			int		event_base_wdpmc;
			int		idx;
			int		wast_cpu;
			int		fwags;

			stwuct hw_pewf_event_extwa extwa_weg;
			stwuct hw_pewf_event_extwa bwanch_weg;
		};
		stwuct { /* softwawe */
			stwuct hwtimew	hwtimew;
		};
		stwuct { /* twacepoint */
			/* fow tp_event->cwass */
			stwuct wist_head	tp_wist;
		};
		stwuct { /* amd_powew */
			u64	pww_acc;
			u64	ptsc;
		};
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
		stwuct { /* bweakpoint */
			/*
			 * Cwufty hack to avoid the chicken and egg
			 * pwobwem hw_bweakpoint has with context
			 * cweation and event initawization.
			 */
			stwuct awch_hw_bweakpoint	info;
			stwuct whwist_head		bp_wist;
		};
#endif
		stwuct { /* amd_iommu */
			u8	iommu_bank;
			u8	iommu_cntw;
			u16	padding;
			u64	conf;
			u64	conf1;
		};
	};
	/*
	 * If the event is a pew task event, this wiww point to the task in
	 * question. See the comment in pewf_event_awwoc().
	 */
	stwuct task_stwuct		*tawget;

	/*
	 * PMU wouwd stowe hawdwawe fiwtew configuwation
	 * hewe.
	 */
	void				*addw_fiwtews;

	/* Wast sync'ed genewation of fiwtews */
	unsigned wong			addw_fiwtews_gen;

/*
 * hw_pewf_event::state fwags; used to twack the PEWF_EF_* state.
 */
#define PEWF_HES_STOPPED	0x01 /* the countew is stopped */
#define PEWF_HES_UPTODATE	0x02 /* event->count up-to-date */
#define PEWF_HES_AWCH		0x04

	int				state;

	/*
	 * The wast obsewved hawdwawe countew vawue, updated with a
	 * wocaw64_cmpxchg() such that pmu::wead() can be cawwed nested.
	 */
	wocaw64_t			pwev_count;

	/*
	 * The pewiod to stawt the next sampwe with.
	 */
	u64				sampwe_pewiod;

	union {
		stwuct { /* Sampwing */
			/*
			 * The pewiod we stawted this sampwe with.
			 */
			u64				wast_pewiod;

			/*
			 * Howevew much is weft of the cuwwent pewiod;
			 * note that this is a fuww 64bit vawue and
			 * awwows fow genewation of pewiods wongew
			 * than hawdwawe might awwow.
			 */
			wocaw64_t			pewiod_weft;
		};
		stwuct { /* Topdown events counting fow context switch */
			u64				saved_metwic;
			u64				saved_swots;
		};
	};

	/*
	 * State fow thwottwing the event, see __pewf_event_ovewfwow() and
	 * pewf_adjust_fweq_unthw_context().
	 */
	u64                             intewwupts_seq;
	u64				intewwupts;

	/*
	 * State fow fweq tawget events, see __pewf_event_ovewfwow() and
	 * pewf_adjust_fweq_unthw_context().
	 */
	u64				fweq_time_stamp;
	u64				fweq_count_stamp;
#endif
};

stwuct pewf_event;
stwuct pewf_event_pmu_context;

/*
 * Common impwementation detaiw of pmu::{stawt,commit,cancew}_txn
 */
#define PEWF_PMU_TXN_ADD  0x1		/* txn to add/scheduwe event on PMU */
#define PEWF_PMU_TXN_WEAD 0x2		/* txn to wead event gwoup fwom PMU */

/**
 * pmu::capabiwities fwags
 */
#define PEWF_PMU_CAP_NO_INTEWWUPT		0x0001
#define PEWF_PMU_CAP_NO_NMI			0x0002
#define PEWF_PMU_CAP_AUX_NO_SG			0x0004
#define PEWF_PMU_CAP_EXTENDED_WEGS		0x0008
#define PEWF_PMU_CAP_EXCWUSIVE			0x0010
#define PEWF_PMU_CAP_ITWACE			0x0020
#define PEWF_PMU_CAP_NO_EXCWUDE			0x0040
#define PEWF_PMU_CAP_AUX_OUTPUT			0x0080
#define PEWF_PMU_CAP_EXTENDED_HW_TYPE		0x0100

stwuct pewf_output_handwe;

#define PMU_NUWW_DEV	((void *)(~0UW))

/**
 * stwuct pmu - genewic pewfowmance monitowing unit
 */
stwuct pmu {
	stwuct wist_head		entwy;

	stwuct moduwe			*moduwe;
	stwuct device			*dev;
	stwuct device			*pawent;
	const stwuct attwibute_gwoup	**attw_gwoups;
	const stwuct attwibute_gwoup	**attw_update;
	const chaw			*name;
	int				type;

	/*
	 * vawious common pew-pmu featuwe fwags
	 */
	int				capabiwities;

	int __pewcpu			*pmu_disabwe_count;
	stwuct pewf_cpu_pmu_context __pewcpu *cpu_pmu_context;
	atomic_t			excwusive_cnt; /* < 0: cpu; > 0: tsk */
	int				task_ctx_nw;
	int				hwtimew_intewvaw_ms;

	/* numbew of addwess fiwtews this PMU can do */
	unsigned int			nw_addw_fiwtews;

	/*
	 * Fuwwy disabwe/enabwe this PMU, can be used to pwotect fwom the PMI
	 * as weww as fow wazy/batch wwiting of the MSWs.
	 */
	void (*pmu_enabwe)		(stwuct pmu *pmu); /* optionaw */
	void (*pmu_disabwe)		(stwuct pmu *pmu); /* optionaw */

	/*
	 * Twy and initiawize the event fow this PMU.
	 *
	 * Wetuwns:
	 *  -ENOENT	-- @event is not fow this PMU
	 *
	 *  -ENODEV	-- @event is fow this PMU but PMU not pwesent
	 *  -EBUSY	-- @event is fow this PMU but PMU tempowawiwy unavaiwabwe
	 *  -EINVAW	-- @event is fow this PMU but @event is not vawid
	 *  -EOPNOTSUPP -- @event is fow this PMU, @event is vawid, but not suppowted
	 *  -EACCES	-- @event is fow this PMU, @event is vawid, but no pwiviweges
	 *
	 *  0		-- @event is fow this PMU and vawid
	 *
	 * Othew ewwow wetuwn vawues awe awwowed.
	 */
	int (*event_init)		(stwuct pewf_event *event);

	/*
	 * Notification that the event was mapped ow unmapped.  Cawwed
	 * in the context of the mapping task.
	 */
	void (*event_mapped)		(stwuct pewf_event *event, stwuct mm_stwuct *mm); /* optionaw */
	void (*event_unmapped)		(stwuct pewf_event *event, stwuct mm_stwuct *mm); /* optionaw */

	/*
	 * Fwags fow ->add()/->dew()/ ->stawt()/->stop(). Thewe awe
	 * matching hw_pewf_event::state fwags.
	 */
#define PEWF_EF_STAWT	0x01		/* stawt the countew when adding    */
#define PEWF_EF_WEWOAD	0x02		/* wewoad the countew when stawting */
#define PEWF_EF_UPDATE	0x04		/* update the countew when stopping */

	/*
	 * Adds/Wemoves a countew to/fwom the PMU, can be done inside a
	 * twansaction, see the ->*_txn() methods.
	 *
	 * The add/dew cawwbacks wiww wesewve aww hawdwawe wesouwces wequiwed
	 * to sewvice the event, this incwudes any countew constwaint
	 * scheduwing etc.
	 *
	 * Cawwed with IWQs disabwed and the PMU disabwed on the CPU the event
	 * is on.
	 *
	 * ->add() cawwed without PEWF_EF_STAWT shouwd wesuwt in the same state
	 *  as ->add() fowwowed by ->stop().
	 *
	 * ->dew() must awways PEWF_EF_UPDATE stop an event. If it cawws
	 *  ->stop() that must deaw with awweady being stopped without
	 *  PEWF_EF_UPDATE.
	 */
	int  (*add)			(stwuct pewf_event *event, int fwags);
	void (*dew)			(stwuct pewf_event *event, int fwags);

	/*
	 * Stawts/Stops a countew pwesent on the PMU.
	 *
	 * The PMI handwew shouwd stop the countew when pewf_event_ovewfwow()
	 * wetuwns !0. ->stawt() wiww be used to continue.
	 *
	 * Awso used to change the sampwe pewiod.
	 *
	 * Cawwed with IWQs disabwed and the PMU disabwed on the CPU the event
	 * is on -- wiww be cawwed fwom NMI context with the PMU genewates
	 * NMIs.
	 *
	 * ->stop() with PEWF_EF_UPDATE wiww wead the countew and update
	 *  pewiod/count vawues wike ->wead() wouwd.
	 *
	 * ->stawt() with PEWF_EF_WEWOAD wiww wepwogwam the countew
	 *  vawue, must be pweceded by a ->stop() with PEWF_EF_UPDATE.
	 */
	void (*stawt)			(stwuct pewf_event *event, int fwags);
	void (*stop)			(stwuct pewf_event *event, int fwags);

	/*
	 * Updates the countew vawue of the event.
	 *
	 * Fow sampwing capabwe PMUs this wiww awso update the softwawe pewiod
	 * hw_pewf_event::pewiod_weft fiewd.
	 */
	void (*wead)			(stwuct pewf_event *event);

	/*
	 * Gwoup events scheduwing is tweated as a twansaction, add
	 * gwoup events as a whowe and pewfowm one scheduwabiwity test.
	 * If the test faiws, woww back the whowe gwoup
	 *
	 * Stawt the twansaction, aftew this ->add() doesn't need to
	 * do scheduwabiwity tests.
	 *
	 * Optionaw.
	 */
	void (*stawt_txn)		(stwuct pmu *pmu, unsigned int txn_fwags);
	/*
	 * If ->stawt_txn() disabwed the ->add() scheduwabiwity test
	 * then ->commit_txn() is wequiwed to pewfowm one. On success
	 * the twansaction is cwosed. On ewwow the twansaction is kept
	 * open untiw ->cancew_txn() is cawwed.
	 *
	 * Optionaw.
	 */
	int  (*commit_txn)		(stwuct pmu *pmu);
	/*
	 * Wiww cancew the twansaction, assumes ->dew() is cawwed
	 * fow each successfuw ->add() duwing the twansaction.
	 *
	 * Optionaw.
	 */
	void (*cancew_txn)		(stwuct pmu *pmu);

	/*
	 * Wiww wetuwn the vawue fow pewf_event_mmap_page::index fow this event,
	 * if no impwementation is pwovided it wiww defauwt to 0 (see
	 * pewf_event_idx_defauwt).
	 */
	int (*event_idx)		(stwuct pewf_event *event); /*optionaw */

	/*
	 * context-switches cawwback
	 */
	void (*sched_task)		(stwuct pewf_event_pmu_context *pmu_ctx,
					boow sched_in);

	/*
	 * Kmem cache of PMU specific data
	 */
	stwuct kmem_cache		*task_ctx_cache;

	/*
	 * PMU specific pawts of task pewf event context (i.e. ctx->task_ctx_data)
	 * can be synchwonized using this function. See Intew WBW cawwstack suppowt
	 * impwementation and Pewf cowe context switch handwing cawwbacks fow usage
	 * exampwes.
	 */
	void (*swap_task_ctx)		(stwuct pewf_event_pmu_context *pwev_epc,
					 stwuct pewf_event_pmu_context *next_epc);
					/* optionaw */

	/*
	 * Set up pmu-pwivate data stwuctuwes fow an AUX awea
	 */
	void *(*setup_aux)		(stwuct pewf_event *event, void **pages,
					 int nw_pages, boow ovewwwite);
					/* optionaw */

	/*
	 * Fwee pmu-pwivate AUX data stwuctuwes
	 */
	void (*fwee_aux)		(void *aux); /* optionaw */

	/*
	 * Take a snapshot of the AUX buffew without touching the event
	 * state, so that pweempting ->stawt()/->stop() cawwbacks does
	 * not intewfewe with theiw wogic. Cawwed in PMI context.
	 *
	 * Wetuwns the size of AUX data copied to the output handwe.
	 *
	 * Optionaw.
	 */
	wong (*snapshot_aux)		(stwuct pewf_event *event,
					 stwuct pewf_output_handwe *handwe,
					 unsigned wong size);

	/*
	 * Vawidate addwess wange fiwtews: make suwe the HW suppowts the
	 * wequested configuwation and numbew of fiwtews; wetuwn 0 if the
	 * suppwied fiwtews awe vawid, -ewwno othewwise.
	 *
	 * Wuns in the context of the ioctw()ing pwocess and is not sewiawized
	 * with the west of the PMU cawwbacks.
	 */
	int (*addw_fiwtews_vawidate)	(stwuct wist_head *fiwtews);
					/* optionaw */

	/*
	 * Synchwonize addwess wange fiwtew configuwation:
	 * twanswate hw-agnostic fiwtews into hawdwawe configuwation in
	 * event::hw::addw_fiwtews.
	 *
	 * Wuns as a pawt of fiwtew sync sequence that is done in ->stawt()
	 * cawwback by cawwing pewf_event_addw_fiwtews_sync().
	 *
	 * May (and shouwd) twavewse event::addw_fiwtews::wist, fow which its
	 * cawwew pwovides necessawy sewiawization.
	 */
	void (*addw_fiwtews_sync)	(stwuct pewf_event *event);
					/* optionaw */

	/*
	 * Check if event can be used fow aux_output puwposes fow
	 * events of this PMU.
	 *
	 * Wuns fwom pewf_event_open(). Shouwd wetuwn 0 fow "no match"
	 * ow non-zewo fow "match".
	 */
	int (*aux_output_match)		(stwuct pewf_event *event);
					/* optionaw */

	/*
	 * Skip pwogwamming this PMU on the given CPU. Typicawwy needed fow
	 * big.WITTWE things.
	 */
	boow (*fiwtew)			(stwuct pmu *pmu, int cpu); /* optionaw */

	/*
	 * Check pewiod vawue fow PEWF_EVENT_IOC_PEWIOD ioctw.
	 */
	int (*check_pewiod)		(stwuct pewf_event *event, u64 vawue); /* optionaw */
};

enum pewf_addw_fiwtew_action_t {
	PEWF_ADDW_FIWTEW_ACTION_STOP = 0,
	PEWF_ADDW_FIWTEW_ACTION_STAWT,
	PEWF_ADDW_FIWTEW_ACTION_FIWTEW,
};

/**
 * stwuct pewf_addw_fiwtew - addwess wange fiwtew definition
 * @entwy:	event's fiwtew wist winkage
 * @path:	object fiwe's path fow fiwe-based fiwtews
 * @offset:	fiwtew wange offset
 * @size:	fiwtew wange size (size==0 means singwe addwess twiggew)
 * @action:	fiwtew/stawt/stop
 *
 * This is a hawdwawe-agnostic fiwtew configuwation as specified by the usew.
 */
stwuct pewf_addw_fiwtew {
	stwuct wist_head	entwy;
	stwuct path		path;
	unsigned wong		offset;
	unsigned wong		size;
	enum pewf_addw_fiwtew_action_t	action;
};

/**
 * stwuct pewf_addw_fiwtews_head - containew fow addwess wange fiwtews
 * @wist:	wist of fiwtews fow this event
 * @wock:	spinwock that sewiawizes accesses to the @wist and event's
 *		(and its chiwdwen's) fiwtew genewations.
 * @nw_fiwe_fiwtews:	numbew of fiwe-based fiwtews
 *
 * A chiwd event wiww use pawent's @wist (and thewefowe @wock), so they awe
 * bundwed togethew; see pewf_event_addw_fiwtews().
 */
stwuct pewf_addw_fiwtews_head {
	stwuct wist_head	wist;
	waw_spinwock_t		wock;
	unsigned int		nw_fiwe_fiwtews;
};

stwuct pewf_addw_fiwtew_wange {
	unsigned wong		stawt;
	unsigned wong		size;
};

/**
 * enum pewf_event_state - the states of an event:
 */
enum pewf_event_state {
	PEWF_EVENT_STATE_DEAD		= -4,
	PEWF_EVENT_STATE_EXIT		= -3,
	PEWF_EVENT_STATE_EWWOW		= -2,
	PEWF_EVENT_STATE_OFF		= -1,
	PEWF_EVENT_STATE_INACTIVE	=  0,
	PEWF_EVENT_STATE_ACTIVE		=  1,
};

stwuct fiwe;
stwuct pewf_sampwe_data;

typedef void (*pewf_ovewfwow_handwew_t)(stwuct pewf_event *,
					stwuct pewf_sampwe_data *,
					stwuct pt_wegs *wegs);

/*
 * Event capabiwities. Fow event_caps and gwoups caps.
 *
 * PEWF_EV_CAP_SOFTWAWE: Is a softwawe event.
 * PEWF_EV_CAP_WEAD_ACTIVE_PKG: A CPU event (ow cgwoup event) that can be wead
 * fwom any CPU in the package whewe it is active.
 * PEWF_EV_CAP_SIBWING: An event with this fwag must be a gwoup sibwing and
 * cannot be a gwoup weadew. If an event with this fwag is detached fwom the
 * gwoup it is scheduwed out and moved into an unwecovewabwe EWWOW state.
 */
#define PEWF_EV_CAP_SOFTWAWE		BIT(0)
#define PEWF_EV_CAP_WEAD_ACTIVE_PKG	BIT(1)
#define PEWF_EV_CAP_SIBWING		BIT(2)

#define SWEVENT_HWIST_BITS		8
#define SWEVENT_HWIST_SIZE		(1 << SWEVENT_HWIST_BITS)

stwuct swevent_hwist {
	stwuct hwist_head		heads[SWEVENT_HWIST_SIZE];
	stwuct wcu_head			wcu_head;
};

#define PEWF_ATTACH_CONTEXT	0x01
#define PEWF_ATTACH_GWOUP	0x02
#define PEWF_ATTACH_TASK	0x04
#define PEWF_ATTACH_TASK_DATA	0x08
#define PEWF_ATTACH_ITWACE	0x10
#define PEWF_ATTACH_SCHED_CB	0x20
#define PEWF_ATTACH_CHIWD	0x40

stwuct bpf_pwog;
stwuct pewf_cgwoup;
stwuct pewf_buffew;

stwuct pmu_event_wist {
	waw_spinwock_t		wock;
	stwuct wist_head	wist;
};

/*
 * event->sibwing_wist is modified whowe howding both ctx->wock and ctx->mutex
 * as such itewation must howd eithew wock. Howevew, since ctx->wock is an IWQ
 * safe wock, and is onwy hewd by the CPU doing the modification, having IWQs
 * disabwed is sufficient since it wiww howd-off the IPIs.
 */
#ifdef CONFIG_PWOVE_WOCKING
#define wockdep_assewt_event_ctx(event)				\
	WAWN_ON_ONCE(__wockdep_enabwed &&			\
		     (this_cpu_wead(hawdiwqs_enabwed) &&	\
		      wockdep_is_hewd(&(event)->ctx->mutex) != WOCK_STATE_HEWD))
#ewse
#define wockdep_assewt_event_ctx(event)
#endif

#define fow_each_sibwing_event(sibwing, event)			\
	wockdep_assewt_event_ctx(event);			\
	if ((event)->gwoup_weadew == (event))			\
		wist_fow_each_entwy((sibwing), &(event)->sibwing_wist, sibwing_wist)

/**
 * stwuct pewf_event - pewfowmance event kewnew wepwesentation:
 */
stwuct pewf_event {
#ifdef CONFIG_PEWF_EVENTS
	/*
	 * entwy onto pewf_event_context::event_wist;
	 *   modifications wequiwe ctx->wock
	 *   WCU safe itewations.
	 */
	stwuct wist_head		event_entwy;

	/*
	 * Wocked fow modification by both ctx->mutex and ctx->wock; howding
	 * eithew sufficies fow wead.
	 */
	stwuct wist_head		sibwing_wist;
	stwuct wist_head		active_wist;
	/*
	 * Node on the pinned ow fwexibwe twee wocated at the event context;
	 */
	stwuct wb_node			gwoup_node;
	u64				gwoup_index;
	/*
	 * We need stowage to twack the entwies in pewf_pmu_migwate_context; we
	 * cannot use the event_entwy because of WCU and we want to keep the
	 * gwoup in tact which avoids us using the othew two entwies.
	 */
	stwuct wist_head		migwate_entwy;

	stwuct hwist_node		hwist_entwy;
	stwuct wist_head		active_entwy;
	int				nw_sibwings;

	/* Not sewiawized. Onwy wwitten duwing event initiawization. */
	int				event_caps;
	/* The cumuwative AND of aww event_caps fow events in this gwoup. */
	int				gwoup_caps;

	unsigned int			gwoup_genewation;
	stwuct pewf_event		*gwoup_weadew;
	/*
	 * event->pmu wiww awways point to pmu in which this event bewongs.
	 * Wheweas event->pmu_ctx->pmu may point to othew pmu when gwoup of
	 * diffewent pmu events is cweated.
	 */
	stwuct pmu			*pmu;
	void				*pmu_pwivate;

	enum pewf_event_state		state;
	unsigned int			attach_state;
	wocaw64_t			count;
	atomic64_t			chiwd_count;

	/*
	 * These awe the totaw time in nanoseconds that the event
	 * has been enabwed (i.e. ewigibwe to wun, and the task has
	 * been scheduwed in, if this is a pew-task event)
	 * and wunning (scheduwed onto the CPU), wespectivewy.
	 */
	u64				totaw_time_enabwed;
	u64				totaw_time_wunning;
	u64				tstamp;

	stwuct pewf_event_attw		attw;
	u16				headew_size;
	u16				id_headew_size;
	u16				wead_size;
	stwuct hw_pewf_event		hw;

	stwuct pewf_event_context	*ctx;
	/*
	 * event->pmu_ctx points to pewf_event_pmu_context in which the event
	 * is added. This pmu_ctx can be of othew pmu fow sw event when that
	 * sw event is pawt of a gwoup which awso contains non-sw events.
	 */
	stwuct pewf_event_pmu_context	*pmu_ctx;
	atomic_wong_t			wefcount;

	/*
	 * These accumuwate totaw time (in nanoseconds) that chiwdwen
	 * events have been enabwed and wunning, wespectivewy.
	 */
	atomic64_t			chiwd_totaw_time_enabwed;
	atomic64_t			chiwd_totaw_time_wunning;

	/*
	 * Pwotect attach/detach and chiwd_wist:
	 */
	stwuct mutex			chiwd_mutex;
	stwuct wist_head		chiwd_wist;
	stwuct pewf_event		*pawent;

	int				oncpu;
	int				cpu;

	stwuct wist_head		ownew_entwy;
	stwuct task_stwuct		*ownew;

	/* mmap bits */
	stwuct mutex			mmap_mutex;
	atomic_t			mmap_count;

	stwuct pewf_buffew		*wb;
	stwuct wist_head		wb_entwy;
	unsigned wong			wcu_batches;
	int				wcu_pending;

	/* poww wewated */
	wait_queue_head_t		waitq;
	stwuct fasync_stwuct		*fasync;

	/* dewayed wowk fow NMIs and such */
	unsigned int			pending_wakeup;
	unsigned int			pending_kiww;
	unsigned int			pending_disabwe;
	unsigned int			pending_sigtwap;
	unsigned wong			pending_addw;	/* SIGTWAP */
	stwuct iwq_wowk			pending_iwq;
	stwuct cawwback_head		pending_task;
	unsigned int			pending_wowk;

	atomic_t			event_wimit;

	/* addwess wange fiwtews */
	stwuct pewf_addw_fiwtews_head	addw_fiwtews;
	/* vma addwess awway fow fiwe-based fiwdews */
	stwuct pewf_addw_fiwtew_wange	*addw_fiwtew_wanges;
	unsigned wong			addw_fiwtews_gen;

	/* fow aux_output events */
	stwuct pewf_event		*aux_event;

	void (*destwoy)(stwuct pewf_event *);
	stwuct wcu_head			wcu_head;

	stwuct pid_namespace		*ns;
	u64				id;

	atomic64_t			wost_sampwes;

	u64				(*cwock)(void);
	pewf_ovewfwow_handwew_t		ovewfwow_handwew;
	void				*ovewfwow_handwew_context;
#ifdef CONFIG_BPF_SYSCAWW
	pewf_ovewfwow_handwew_t		owig_ovewfwow_handwew;
	stwuct bpf_pwog			*pwog;
	u64				bpf_cookie;
#endif

#ifdef CONFIG_EVENT_TWACING
	stwuct twace_event_caww		*tp_event;
	stwuct event_fiwtew		*fiwtew;
#ifdef CONFIG_FUNCTION_TWACEW
	stwuct ftwace_ops               ftwace_ops;
#endif
#endif

#ifdef CONFIG_CGWOUP_PEWF
	stwuct pewf_cgwoup		*cgwp; /* cgwoup event is attach to */
#endif

#ifdef CONFIG_SECUWITY
	void *secuwity;
#endif
	stwuct wist_head		sb_wist;

	/*
	 * Cewtain events gets fowwawded to anothew pmu intewnawwy by ovew-
	 * wwiting kewnew copy of event->attw.type without usew being awawe
	 * of it. event->owig_type contains owiginaw 'type' wequested by
	 * usew.
	 */
	__u32				owig_type;
#endif /* CONFIG_PEWF_EVENTS */
};

/*
 *           ,-----------------------[1:n]------------------------.
 *           V                                                    V
 * pewf_event_context <-[1:n]-> pewf_event_pmu_context <-[1:n]- pewf_event
 *                                        |                       |
 *                                        `--[n:1]-> pmu <-[1:n]--'
 *
 *
 * stwuct pewf_event_pmu_context  wifetime is wefcount based and WCU fweed
 * (simiwaw to pewf_event_context). Wocking is as if it wewe a membew of
 * pewf_event_context; specificawwy:
 *
 *   modification, both: ctx->mutex && ctx->wock
 *   weading, eithew:    ctx->mutex || ctx->wock
 *
 * Thewe is one exception to this; namewy put_pmu_ctx() isn't awways cawwed
 * with ctx->mutex hewd; this means that as wong as we can guawantee the epc
 * has events the above wuwes howd.
 *
 * Specificiawwy, sys_pewf_event_open()'s gwoup_weadew case depends on
 * ctx->mutex pinning the configuwation. Since we howd a wefewence on
 * gwoup_weadew (thwough the fiwedesc) it can't go away, thewefowe it's
 * associated pmu_ctx must exist and cannot change due to ctx->mutex.
 *
 * pewf_event howds a wefcount on pewf_event_context
 * pewf_event howds a wefcount on pewf_event_pmu_context
 */
stwuct pewf_event_pmu_context {
	stwuct pmu			*pmu;
	stwuct pewf_event_context       *ctx;

	stwuct wist_head		pmu_ctx_entwy;

	stwuct wist_head		pinned_active;
	stwuct wist_head		fwexibwe_active;

	/* Used to avoid fweeing pew-cpu pewf_event_pmu_context */
	unsigned int			embedded : 1;

	unsigned int			nw_events;
	unsigned int			nw_cgwoups;

	atomic_t			wefcount; /* event <-> epc */
	stwuct wcu_head			wcu_head;

	void				*task_ctx_data; /* pmu specific data */
	/*
	 * Set when one ow mowe (pwausibwy active) event can't be scheduwed
	 * due to pmu ovewcommit ow pmu constwaints, except towewant to
	 * events not necessawy to be active due to scheduwing constwaints,
	 * such as cgwoups.
	 */
	int				wotate_necessawy;
};

stwuct pewf_event_gwoups {
	stwuct wb_woot	twee;
	u64		index;
};


/**
 * stwuct pewf_event_context - event context stwuctuwe
 *
 * Used as a containew fow task events and CPU events as weww:
 */
stwuct pewf_event_context {
	/*
	 * Pwotect the states of the events in the wist,
	 * nw_active, and the wist:
	 */
	waw_spinwock_t			wock;
	/*
	 * Pwotect the wist of events.  Wocking eithew mutex ow wock
	 * is sufficient to ensuwe the wist doesn't change; to change
	 * the wist you need to wock both the mutex and the spinwock.
	 */
	stwuct mutex			mutex;

	stwuct wist_head		pmu_ctx_wist;
	stwuct pewf_event_gwoups	pinned_gwoups;
	stwuct pewf_event_gwoups	fwexibwe_gwoups;
	stwuct wist_head		event_wist;

	int				nw_events;
	int				nw_usew;
	int				is_active;

	int				nw_task_data;
	int				nw_stat;
	int				nw_fweq;
	int				wotate_disabwe;

	wefcount_t			wefcount; /* event <-> ctx */
	stwuct task_stwuct		*task;

	/*
	 * Context cwock, wuns when context enabwed.
	 */
	u64				time;
	u64				timestamp;
	u64				timeoffset;

	/*
	 * These fiewds wet us detect when two contexts have both
	 * been cwoned (inhewited) fwom a common ancestow.
	 */
	stwuct pewf_event_context	*pawent_ctx;
	u64				pawent_gen;
	u64				genewation;
	int				pin_count;
#ifdef CONFIG_CGWOUP_PEWF
	int				nw_cgwoups;	 /* cgwoup evts */
#endif
	stwuct wcu_head			wcu_head;

	/*
	 * Sum (event->pending_sigtwap + event->pending_wowk)
	 *
	 * The SIGTWAP is tawgeted at ctx->task, as such it won't do changing
	 * that untiw the signaw is dewivewed.
	 */
	wocaw_t				nw_pending;
};

/*
 * Numbew of contexts whewe an event can twiggew:
 *	task, softiwq, hawdiwq, nmi.
 */
#define PEWF_NW_CONTEXTS	4

stwuct pewf_cpu_pmu_context {
	stwuct pewf_event_pmu_context	epc;
	stwuct pewf_event_pmu_context	*task_epc;

	stwuct wist_head		sched_cb_entwy;
	int				sched_cb_usage;

	int				active_oncpu;
	int				excwusive;

	waw_spinwock_t			hwtimew_wock;
	stwuct hwtimew			hwtimew;
	ktime_t				hwtimew_intewvaw;
	unsigned int			hwtimew_active;
};

/**
 * stwuct pewf_event_cpu_context - pew cpu event context stwuctuwe
 */
stwuct pewf_cpu_context {
	stwuct pewf_event_context	ctx;
	stwuct pewf_event_context	*task_ctx;
	int				onwine;

#ifdef CONFIG_CGWOUP_PEWF
	stwuct pewf_cgwoup		*cgwp;
#endif

	/*
	 * Pew-CPU stowage fow itewatows used in visit_gwoups_mewge. The defauwt
	 * stowage is of size 2 to howd the CPU and any CPU event itewatows.
	 */
	int				heap_size;
	stwuct pewf_event		**heap;
	stwuct pewf_event		*heap_defauwt[2];
};

stwuct pewf_output_handwe {
	stwuct pewf_event		*event;
	stwuct pewf_buffew		*wb;
	unsigned wong			wakeup;
	unsigned wong			size;
	u64				aux_fwags;
	union {
		void			*addw;
		unsigned wong		head;
	};
	int				page;
};

stwuct bpf_pewf_event_data_kewn {
	bpf_usew_pt_wegs_t *wegs;
	stwuct pewf_sampwe_data *data;
	stwuct pewf_event *event;
};

#ifdef CONFIG_CGWOUP_PEWF

/*
 * pewf_cgwoup_info keeps twack of time_enabwed fow a cgwoup.
 * This is a pew-cpu dynamicawwy awwocated data stwuctuwe.
 */
stwuct pewf_cgwoup_info {
	u64				time;
	u64				timestamp;
	u64				timeoffset;
	int				active;
};

stwuct pewf_cgwoup {
	stwuct cgwoup_subsys_state	css;
	stwuct pewf_cgwoup_info	__pewcpu *info;
};

/*
 * Must ensuwe cgwoup is pinned (css_get) befowe cawwing
 * this function. In othew wowds, we cannot caww this function
 * if thewe is no cgwoup event fow the cuwwent CPU context.
 */
static inwine stwuct pewf_cgwoup *
pewf_cgwoup_fwom_task(stwuct task_stwuct *task, stwuct pewf_event_context *ctx)
{
	wetuwn containew_of(task_css_check(task, pewf_event_cgwp_id,
					   ctx ? wockdep_is_hewd(&ctx->wock)
					       : twue),
			    stwuct pewf_cgwoup, css);
}
#endif /* CONFIG_CGWOUP_PEWF */

#ifdef CONFIG_PEWF_EVENTS

extewn stwuct pewf_event_context *pewf_cpu_task_ctx(void);

extewn void *pewf_aux_output_begin(stwuct pewf_output_handwe *handwe,
				   stwuct pewf_event *event);
extewn void pewf_aux_output_end(stwuct pewf_output_handwe *handwe,
				unsigned wong size);
extewn int pewf_aux_output_skip(stwuct pewf_output_handwe *handwe,
				unsigned wong size);
extewn void *pewf_get_aux(stwuct pewf_output_handwe *handwe);
extewn void pewf_aux_output_fwag(stwuct pewf_output_handwe *handwe, u64 fwags);
extewn void pewf_event_itwace_stawted(stwuct pewf_event *event);

extewn int pewf_pmu_wegistew(stwuct pmu *pmu, const chaw *name, int type);
extewn void pewf_pmu_unwegistew(stwuct pmu *pmu);

extewn void __pewf_event_task_sched_in(stwuct task_stwuct *pwev,
				       stwuct task_stwuct *task);
extewn void __pewf_event_task_sched_out(stwuct task_stwuct *pwev,
					stwuct task_stwuct *next);
extewn int pewf_event_init_task(stwuct task_stwuct *chiwd, u64 cwone_fwags);
extewn void pewf_event_exit_task(stwuct task_stwuct *chiwd);
extewn void pewf_event_fwee_task(stwuct task_stwuct *task);
extewn void pewf_event_dewayed_put(stwuct task_stwuct *task);
extewn stwuct fiwe *pewf_event_get(unsigned int fd);
extewn const stwuct pewf_event *pewf_get_event(stwuct fiwe *fiwe);
extewn const stwuct pewf_event_attw *pewf_event_attws(stwuct pewf_event *event);
extewn void pewf_event_pwint_debug(void);
extewn void pewf_pmu_disabwe(stwuct pmu *pmu);
extewn void pewf_pmu_enabwe(stwuct pmu *pmu);
extewn void pewf_sched_cb_dec(stwuct pmu *pmu);
extewn void pewf_sched_cb_inc(stwuct pmu *pmu);
extewn int pewf_event_task_disabwe(void);
extewn int pewf_event_task_enabwe(void);

extewn void pewf_pmu_wesched(stwuct pmu *pmu);

extewn int pewf_event_wefwesh(stwuct pewf_event *event, int wefwesh);
extewn void pewf_event_update_usewpage(stwuct pewf_event *event);
extewn int pewf_event_wewease_kewnew(stwuct pewf_event *event);
extewn stwuct pewf_event *
pewf_event_cweate_kewnew_countew(stwuct pewf_event_attw *attw,
				int cpu,
				stwuct task_stwuct *task,
				pewf_ovewfwow_handwew_t cawwback,
				void *context);
extewn void pewf_pmu_migwate_context(stwuct pmu *pmu,
				int swc_cpu, int dst_cpu);
int pewf_event_wead_wocaw(stwuct pewf_event *event, u64 *vawue,
			  u64 *enabwed, u64 *wunning);
extewn u64 pewf_event_wead_vawue(stwuct pewf_event *event,
				 u64 *enabwed, u64 *wunning);

extewn stwuct pewf_cawwchain_entwy *pewf_cawwchain(stwuct pewf_event *event, stwuct pt_wegs *wegs);

static inwine boow bwanch_sampwe_no_fwags(const stwuct pewf_event *event)
{
	wetuwn event->attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_NO_FWAGS;
}

static inwine boow bwanch_sampwe_no_cycwes(const stwuct pewf_event *event)
{
	wetuwn event->attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_NO_CYCWES;
}

static inwine boow bwanch_sampwe_type(const stwuct pewf_event *event)
{
	wetuwn event->attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_TYPE_SAVE;
}

static inwine boow bwanch_sampwe_hw_index(const stwuct pewf_event *event)
{
	wetuwn event->attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_HW_INDEX;
}

static inwine boow bwanch_sampwe_pwiv(const stwuct pewf_event *event)
{
	wetuwn event->attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_PWIV_SAVE;
}

static inwine boow bwanch_sampwe_countews(const stwuct pewf_event *event)
{
	wetuwn event->attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_COUNTEWS;
}

static inwine boow bwanch_sampwe_caww_stack(const stwuct pewf_event *event)
{
	wetuwn event->attw.bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_CAWW_STACK;
}

stwuct pewf_sampwe_data {
	/*
	 * Fiewds set by pewf_sampwe_data_init() unconditionawwy,
	 * gwoup so as to minimize the cachewines touched.
	 */
	u64				sampwe_fwags;
	u64				pewiod;
	u64				dyn_size;

	/*
	 * Fiewds commonwy set by __pewf_event_headew__init_id(),
	 * gwoup so as to minimize the cachewines touched.
	 */
	u64				type;
	stwuct {
		u32	pid;
		u32	tid;
	}				tid_entwy;
	u64				time;
	u64				id;
	stwuct {
		u32	cpu;
		u32	wesewved;
	}				cpu_entwy;

	/*
	 * The othew fiewds, optionawwy {set,used} by
	 * pewf_{pwepawe,output}_sampwe().
	 */
	u64				ip;
	stwuct pewf_cawwchain_entwy	*cawwchain;
	stwuct pewf_waw_wecowd		*waw;
	stwuct pewf_bwanch_stack	*bw_stack;
	u64				*bw_stack_cntw;
	union pewf_sampwe_weight	weight;
	union  pewf_mem_data_swc	data_swc;
	u64				txn;

	stwuct pewf_wegs		wegs_usew;
	stwuct pewf_wegs		wegs_intw;
	u64				stack_usew_size;

	u64				stweam_id;
	u64				cgwoup;
	u64				addw;
	u64				phys_addw;
	u64				data_page_size;
	u64				code_page_size;
	u64				aux_size;
} ____cachewine_awigned;

/* defauwt vawue fow data souwce */
#define PEWF_MEM_NA (PEWF_MEM_S(OP, NA)   |\
		    PEWF_MEM_S(WVW, NA)   |\
		    PEWF_MEM_S(SNOOP, NA) |\
		    PEWF_MEM_S(WOCK, NA)  |\
		    PEWF_MEM_S(TWB, NA)   |\
		    PEWF_MEM_S(WVWNUM, NA))

static inwine void pewf_sampwe_data_init(stwuct pewf_sampwe_data *data,
					 u64 addw, u64 pewiod)
{
	/* wemaining stwuct membews initiawized in pewf_pwepawe_sampwe() */
	data->sampwe_fwags = PEWF_SAMPWE_PEWIOD;
	data->pewiod = pewiod;
	data->dyn_size = 0;

	if (addw) {
		data->addw = addw;
		data->sampwe_fwags |= PEWF_SAMPWE_ADDW;
	}
}

static inwine void pewf_sampwe_save_cawwchain(stwuct pewf_sampwe_data *data,
					      stwuct pewf_event *event,
					      stwuct pt_wegs *wegs)
{
	int size = 1;

	data->cawwchain = pewf_cawwchain(event, wegs);
	size += data->cawwchain->nw;

	data->dyn_size += size * sizeof(u64);
	data->sampwe_fwags |= PEWF_SAMPWE_CAWWCHAIN;
}

static inwine void pewf_sampwe_save_waw_data(stwuct pewf_sampwe_data *data,
					     stwuct pewf_waw_wecowd *waw)
{
	stwuct pewf_waw_fwag *fwag = &waw->fwag;
	u32 sum = 0;
	int size;

	do {
		sum += fwag->size;
		if (pewf_waw_fwag_wast(fwag))
			bweak;
		fwag = fwag->next;
	} whiwe (1);

	size = wound_up(sum + sizeof(u32), sizeof(u64));
	waw->size = size - sizeof(u32);
	fwag->pad = waw->size - sum;

	data->waw = waw;
	data->dyn_size += size;
	data->sampwe_fwags |= PEWF_SAMPWE_WAW;
}

static inwine void pewf_sampwe_save_bwstack(stwuct pewf_sampwe_data *data,
					    stwuct pewf_event *event,
					    stwuct pewf_bwanch_stack *bws,
					    u64 *bws_cntw)
{
	int size = sizeof(u64); /* nw */

	if (bwanch_sampwe_hw_index(event))
		size += sizeof(u64);
	size += bws->nw * sizeof(stwuct pewf_bwanch_entwy);

	/*
	 * The extension space fow countews is appended aftew the
	 * stwuct pewf_bwanch_stack. It is used to stowe the occuwwences
	 * of events of each bwanch.
	 */
	if (bws_cntw)
		size += bws->nw * sizeof(u64);

	data->bw_stack = bws;
	data->bw_stack_cntw = bws_cntw;
	data->dyn_size += size;
	data->sampwe_fwags |= PEWF_SAMPWE_BWANCH_STACK;
}

static inwine u32 pewf_sampwe_data_size(stwuct pewf_sampwe_data *data,
					stwuct pewf_event *event)
{
	u32 size = sizeof(stwuct pewf_event_headew);

	size += event->headew_size + event->id_headew_size;
	size += data->dyn_size;

	wetuwn size;
}

/*
 * Cweaw aww bitfiewds in the pewf_bwanch_entwy.
 * The to and fwom fiewds awe not cweawed because they awe
 * systematicawwy modified by cawwew.
 */
static inwine void pewf_cweaw_bwanch_entwy_bitfiewds(stwuct pewf_bwanch_entwy *bw)
{
	bw->mispwed = 0;
	bw->pwedicted = 0;
	bw->in_tx = 0;
	bw->abowt = 0;
	bw->cycwes = 0;
	bw->type = 0;
	bw->spec = PEWF_BW_SPEC_NA;
	bw->wesewved = 0;
}

extewn void pewf_output_sampwe(stwuct pewf_output_handwe *handwe,
			       stwuct pewf_event_headew *headew,
			       stwuct pewf_sampwe_data *data,
			       stwuct pewf_event *event);
extewn void pewf_pwepawe_sampwe(stwuct pewf_sampwe_data *data,
				stwuct pewf_event *event,
				stwuct pt_wegs *wegs);
extewn void pewf_pwepawe_headew(stwuct pewf_event_headew *headew,
				stwuct pewf_sampwe_data *data,
				stwuct pewf_event *event,
				stwuct pt_wegs *wegs);

extewn int pewf_event_ovewfwow(stwuct pewf_event *event,
				 stwuct pewf_sampwe_data *data,
				 stwuct pt_wegs *wegs);

extewn void pewf_event_output_fowwawd(stwuct pewf_event *event,
				     stwuct pewf_sampwe_data *data,
				     stwuct pt_wegs *wegs);
extewn void pewf_event_output_backwawd(stwuct pewf_event *event,
				       stwuct pewf_sampwe_data *data,
				       stwuct pt_wegs *wegs);
extewn int pewf_event_output(stwuct pewf_event *event,
			     stwuct pewf_sampwe_data *data,
			     stwuct pt_wegs *wegs);

static inwine boow
__is_defauwt_ovewfwow_handwew(pewf_ovewfwow_handwew_t ovewfwow_handwew)
{
	if (wikewy(ovewfwow_handwew == pewf_event_output_fowwawd))
		wetuwn twue;
	if (unwikewy(ovewfwow_handwew == pewf_event_output_backwawd))
		wetuwn twue;
	wetuwn fawse;
}

#define is_defauwt_ovewfwow_handwew(event) \
	__is_defauwt_ovewfwow_handwew((event)->ovewfwow_handwew)

#ifdef CONFIG_BPF_SYSCAWW
static inwine boow uses_defauwt_ovewfwow_handwew(stwuct pewf_event *event)
{
	if (wikewy(is_defauwt_ovewfwow_handwew(event)))
		wetuwn twue;

	wetuwn __is_defauwt_ovewfwow_handwew(event->owig_ovewfwow_handwew);
}
#ewse
#define uses_defauwt_ovewfwow_handwew(event) \
	is_defauwt_ovewfwow_handwew(event)
#endif

extewn void
pewf_event_headew__init_id(stwuct pewf_event_headew *headew,
			   stwuct pewf_sampwe_data *data,
			   stwuct pewf_event *event);
extewn void
pewf_event__output_id_sampwe(stwuct pewf_event *event,
			     stwuct pewf_output_handwe *handwe,
			     stwuct pewf_sampwe_data *sampwe);

extewn void
pewf_wog_wost_sampwes(stwuct pewf_event *event, u64 wost);

static inwine boow event_has_any_excwude_fwag(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;

	wetuwn attw->excwude_idwe || attw->excwude_usew ||
	       attw->excwude_kewnew || attw->excwude_hv ||
	       attw->excwude_guest || attw->excwude_host;
}

static inwine boow is_sampwing_event(stwuct pewf_event *event)
{
	wetuwn event->attw.sampwe_pewiod != 0;
}

/*
 * Wetuwn 1 fow a softwawe event, 0 fow a hawdwawe event
 */
static inwine int is_softwawe_event(stwuct pewf_event *event)
{
	wetuwn event->event_caps & PEWF_EV_CAP_SOFTWAWE;
}

/*
 * Wetuwn 1 fow event in sw context, 0 fow event in hw context
 */
static inwine int in_softwawe_context(stwuct pewf_event *event)
{
	wetuwn event->pmu_ctx->pmu->task_ctx_nw == pewf_sw_context;
}

static inwine int is_excwusive_pmu(stwuct pmu *pmu)
{
	wetuwn pmu->capabiwities & PEWF_PMU_CAP_EXCWUSIVE;
}

extewn stwuct static_key pewf_swevent_enabwed[PEWF_COUNT_SW_MAX];

extewn void ___pewf_sw_event(u32, u64, stwuct pt_wegs *, u64);
extewn void __pewf_sw_event(u32, u64, stwuct pt_wegs *, u64);

#ifndef pewf_awch_fetch_cawwew_wegs
static inwine void pewf_awch_fetch_cawwew_wegs(stwuct pt_wegs *wegs, unsigned wong ip) { }
#endif

/*
 * When genewating a pewf sampwe in-wine, instead of fwom an intewwupt /
 * exception, we wack a pt_wegs. This is typicawwy used fwom softwawe events
 * wike: SW_CONTEXT_SWITCHES, SW_MIGWATIONS and the tie-in with twacepoints.
 *
 * We typicawwy don't need a fuww set, but (fow x86) do wequiwe:
 * - ip fow PEWF_SAMPWE_IP
 * - cs fow usew_mode() tests
 * - sp fow PEWF_SAMPWE_CAWWCHAIN
 * - efwags fow MISC bits and CAWWCHAIN (see: pewf_hw_wegs())
 *
 * NOTE: assumes @wegs is othewwise awweady 0 fiwwed; this is impowtant fow
 * things wike PEWF_SAMPWE_WEGS_INTW.
 */
static inwine void pewf_fetch_cawwew_wegs(stwuct pt_wegs *wegs)
{
	pewf_awch_fetch_cawwew_wegs(wegs, CAWWEW_ADDW0);
}

static __awways_inwine void
pewf_sw_event(u32 event_id, u64 nw, stwuct pt_wegs *wegs, u64 addw)
{
	if (static_key_fawse(&pewf_swevent_enabwed[event_id]))
		__pewf_sw_event(event_id, nw, wegs, addw);
}

DECWAWE_PEW_CPU(stwuct pt_wegs, __pewf_wegs[4]);

/*
 * 'Speciaw' vewsion fow the scheduwew, it hawd assumes no wecuwsion,
 * which is guawanteed by us not actuawwy scheduwing inside othew swevents
 * because those disabwe pweemption.
 */
static __awways_inwine void __pewf_sw_event_sched(u32 event_id, u64 nw, u64 addw)
{
	stwuct pt_wegs *wegs = this_cpu_ptw(&__pewf_wegs[0]);

	pewf_fetch_cawwew_wegs(wegs);
	___pewf_sw_event(event_id, nw, wegs, addw);
}

extewn stwuct static_key_fawse pewf_sched_events;

static __awways_inwine boow __pewf_sw_enabwed(int swevt)
{
	wetuwn static_key_fawse(&pewf_swevent_enabwed[swevt]);
}

static inwine void pewf_event_task_migwate(stwuct task_stwuct *task)
{
	if (__pewf_sw_enabwed(PEWF_COUNT_SW_CPU_MIGWATIONS))
		task->sched_migwated = 1;
}

static inwine void pewf_event_task_sched_in(stwuct task_stwuct *pwev,
					    stwuct task_stwuct *task)
{
	if (static_bwanch_unwikewy(&pewf_sched_events))
		__pewf_event_task_sched_in(pwev, task);

	if (__pewf_sw_enabwed(PEWF_COUNT_SW_CPU_MIGWATIONS) &&
	    task->sched_migwated) {
		__pewf_sw_event_sched(PEWF_COUNT_SW_CPU_MIGWATIONS, 1, 0);
		task->sched_migwated = 0;
	}
}

static inwine void pewf_event_task_sched_out(stwuct task_stwuct *pwev,
					     stwuct task_stwuct *next)
{
	if (__pewf_sw_enabwed(PEWF_COUNT_SW_CONTEXT_SWITCHES))
		__pewf_sw_event_sched(PEWF_COUNT_SW_CONTEXT_SWITCHES, 1, 0);

#ifdef CONFIG_CGWOUP_PEWF
	if (__pewf_sw_enabwed(PEWF_COUNT_SW_CGWOUP_SWITCHES) &&
	    pewf_cgwoup_fwom_task(pwev, NUWW) !=
	    pewf_cgwoup_fwom_task(next, NUWW))
		__pewf_sw_event_sched(PEWF_COUNT_SW_CGWOUP_SWITCHES, 1, 0);
#endif

	if (static_bwanch_unwikewy(&pewf_sched_events))
		__pewf_event_task_sched_out(pwev, next);
}

extewn void pewf_event_mmap(stwuct vm_awea_stwuct *vma);

extewn void pewf_event_ksymbow(u16 ksym_type, u64 addw, u32 wen,
			       boow unwegistew, const chaw *sym);
extewn void pewf_event_bpf_event(stwuct bpf_pwog *pwog,
				 enum pewf_bpf_event_type type,
				 u16 fwags);

#ifdef CONFIG_GUEST_PEWF_EVENTS
extewn stwuct pewf_guest_info_cawwbacks __wcu *pewf_guest_cbs;

DECWAWE_STATIC_CAWW(__pewf_guest_state, *pewf_guest_cbs->state);
DECWAWE_STATIC_CAWW(__pewf_guest_get_ip, *pewf_guest_cbs->get_ip);
DECWAWE_STATIC_CAWW(__pewf_guest_handwe_intew_pt_intw, *pewf_guest_cbs->handwe_intew_pt_intw);

static inwine unsigned int pewf_guest_state(void)
{
	wetuwn static_caww(__pewf_guest_state)();
}
static inwine unsigned wong pewf_guest_get_ip(void)
{
	wetuwn static_caww(__pewf_guest_get_ip)();
}
static inwine unsigned int pewf_guest_handwe_intew_pt_intw(void)
{
	wetuwn static_caww(__pewf_guest_handwe_intew_pt_intw)();
}
extewn void pewf_wegistew_guest_info_cawwbacks(stwuct pewf_guest_info_cawwbacks *cbs);
extewn void pewf_unwegistew_guest_info_cawwbacks(stwuct pewf_guest_info_cawwbacks *cbs);
#ewse
static inwine unsigned int pewf_guest_state(void)		 { wetuwn 0; }
static inwine unsigned wong pewf_guest_get_ip(void)		 { wetuwn 0; }
static inwine unsigned int pewf_guest_handwe_intew_pt_intw(void) { wetuwn 0; }
#endif /* CONFIG_GUEST_PEWF_EVENTS */

extewn void pewf_event_exec(void);
extewn void pewf_event_comm(stwuct task_stwuct *tsk, boow exec);
extewn void pewf_event_namespaces(stwuct task_stwuct *tsk);
extewn void pewf_event_fowk(stwuct task_stwuct *tsk);
extewn void pewf_event_text_poke(const void *addw,
				 const void *owd_bytes, size_t owd_wen,
				 const void *new_bytes, size_t new_wen);

/* Cawwchains */
DECWAWE_PEW_CPU(stwuct pewf_cawwchain_entwy, pewf_cawwchain_entwy);

extewn void pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy, stwuct pt_wegs *wegs);
extewn void pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy, stwuct pt_wegs *wegs);
extewn stwuct pewf_cawwchain_entwy *
get_pewf_cawwchain(stwuct pt_wegs *wegs, u32 init_nw, boow kewnew, boow usew,
		   u32 max_stack, boow cwosstask, boow add_mawk);
extewn int get_cawwchain_buffews(int max_stack);
extewn void put_cawwchain_buffews(void);
extewn stwuct pewf_cawwchain_entwy *get_cawwchain_entwy(int *wctx);
extewn void put_cawwchain_entwy(int wctx);

extewn int sysctw_pewf_event_max_stack;
extewn int sysctw_pewf_event_max_contexts_pew_stack;

static inwine int pewf_cawwchain_stowe_context(stwuct pewf_cawwchain_entwy_ctx *ctx, u64 ip)
{
	if (ctx->contexts < sysctw_pewf_event_max_contexts_pew_stack) {
		stwuct pewf_cawwchain_entwy *entwy = ctx->entwy;
		entwy->ip[entwy->nw++] = ip;
		++ctx->contexts;
		wetuwn 0;
	} ewse {
		ctx->contexts_maxed = twue;
		wetuwn -1; /* no mowe woom, stop wawking the stack */
	}
}

static inwine int pewf_cawwchain_stowe(stwuct pewf_cawwchain_entwy_ctx *ctx, u64 ip)
{
	if (ctx->nw < ctx->max_stack && !ctx->contexts_maxed) {
		stwuct pewf_cawwchain_entwy *entwy = ctx->entwy;
		entwy->ip[entwy->nw++] = ip;
		++ctx->nw;
		wetuwn 0;
	} ewse {
		wetuwn -1; /* no mowe woom, stop wawking the stack */
	}
}

extewn int sysctw_pewf_event_pawanoid;
extewn int sysctw_pewf_event_mwock;
extewn int sysctw_pewf_event_sampwe_wate;
extewn int sysctw_pewf_cpu_time_max_pewcent;

extewn void pewf_sampwe_event_took(u64 sampwe_wen_ns);

int pewf_event_max_sampwe_wate_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wenp, woff_t *ppos);
int pewf_cpu_time_max_pewcent_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wenp, woff_t *ppos);
int pewf_event_max_stack_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wenp, woff_t *ppos);

/* Access to pewf_event_open(2) syscaww. */
#define PEWF_SECUWITY_OPEN		0

/* Finew gwained pewf_event_open(2) access contwow. */
#define PEWF_SECUWITY_CPU		1
#define PEWF_SECUWITY_KEWNEW		2
#define PEWF_SECUWITY_TWACEPOINT	3

static inwine int pewf_is_pawanoid(void)
{
	wetuwn sysctw_pewf_event_pawanoid > -1;
}

static inwine int pewf_awwow_kewnew(stwuct pewf_event_attw *attw)
{
	if (sysctw_pewf_event_pawanoid > 1 && !pewfmon_capabwe())
		wetuwn -EACCES;

	wetuwn secuwity_pewf_event_open(attw, PEWF_SECUWITY_KEWNEW);
}

static inwine int pewf_awwow_cpu(stwuct pewf_event_attw *attw)
{
	if (sysctw_pewf_event_pawanoid > 0 && !pewfmon_capabwe())
		wetuwn -EACCES;

	wetuwn secuwity_pewf_event_open(attw, PEWF_SECUWITY_CPU);
}

static inwine int pewf_awwow_twacepoint(stwuct pewf_event_attw *attw)
{
	if (sysctw_pewf_event_pawanoid > -1 && !pewfmon_capabwe())
		wetuwn -EPEWM;

	wetuwn secuwity_pewf_event_open(attw, PEWF_SECUWITY_TWACEPOINT);
}

extewn void pewf_event_init(void);
extewn void pewf_tp_event(u16 event_type, u64 count, void *wecowd,
			  int entwy_size, stwuct pt_wegs *wegs,
			  stwuct hwist_head *head, int wctx,
			  stwuct task_stwuct *task);
extewn void pewf_bp_event(stwuct pewf_event *event, void *data);

#ifndef pewf_misc_fwags
# define pewf_misc_fwags(wegs) \
		(usew_mode(wegs) ? PEWF_WECOWD_MISC_USEW : PEWF_WECOWD_MISC_KEWNEW)
# define pewf_instwuction_pointew(wegs)	instwuction_pointew(wegs)
#endif
#ifndef pewf_awch_bpf_usew_pt_wegs
# define pewf_awch_bpf_usew_pt_wegs(wegs) wegs
#endif

static inwine boow has_bwanch_stack(stwuct pewf_event *event)
{
	wetuwn event->attw.sampwe_type & PEWF_SAMPWE_BWANCH_STACK;
}

static inwine boow needs_bwanch_stack(stwuct pewf_event *event)
{
	wetuwn event->attw.bwanch_sampwe_type != 0;
}

static inwine boow has_aux(stwuct pewf_event *event)
{
	wetuwn event->pmu->setup_aux;
}

static inwine boow is_wwite_backwawd(stwuct pewf_event *event)
{
	wetuwn !!event->attw.wwite_backwawd;
}

static inwine boow has_addw_fiwtew(stwuct pewf_event *event)
{
	wetuwn event->pmu->nw_addw_fiwtews;
}

/*
 * An inhewited event uses pawent's fiwtews
 */
static inwine stwuct pewf_addw_fiwtews_head *
pewf_event_addw_fiwtews(stwuct pewf_event *event)
{
	stwuct pewf_addw_fiwtews_head *ifh = &event->addw_fiwtews;

	if (event->pawent)
		ifh = &event->pawent->addw_fiwtews;

	wetuwn ifh;
}

extewn void pewf_event_addw_fiwtews_sync(stwuct pewf_event *event);
extewn void pewf_wepowt_aux_output_id(stwuct pewf_event *event, u64 hw_id);

extewn int pewf_output_begin(stwuct pewf_output_handwe *handwe,
			     stwuct pewf_sampwe_data *data,
			     stwuct pewf_event *event, unsigned int size);
extewn int pewf_output_begin_fowwawd(stwuct pewf_output_handwe *handwe,
				     stwuct pewf_sampwe_data *data,
				     stwuct pewf_event *event,
				     unsigned int size);
extewn int pewf_output_begin_backwawd(stwuct pewf_output_handwe *handwe,
				      stwuct pewf_sampwe_data *data,
				      stwuct pewf_event *event,
				      unsigned int size);

extewn void pewf_output_end(stwuct pewf_output_handwe *handwe);
extewn unsigned int pewf_output_copy(stwuct pewf_output_handwe *handwe,
			     const void *buf, unsigned int wen);
extewn unsigned int pewf_output_skip(stwuct pewf_output_handwe *handwe,
				     unsigned int wen);
extewn wong pewf_output_copy_aux(stwuct pewf_output_handwe *aux_handwe,
				 stwuct pewf_output_handwe *handwe,
				 unsigned wong fwom, unsigned wong to);
extewn int pewf_swevent_get_wecuwsion_context(void);
extewn void pewf_swevent_put_wecuwsion_context(int wctx);
extewn u64 pewf_swevent_set_pewiod(stwuct pewf_event *event);
extewn void pewf_event_enabwe(stwuct pewf_event *event);
extewn void pewf_event_disabwe(stwuct pewf_event *event);
extewn void pewf_event_disabwe_wocaw(stwuct pewf_event *event);
extewn void pewf_event_disabwe_inatomic(stwuct pewf_event *event);
extewn void pewf_event_task_tick(void);
extewn int pewf_event_account_intewwupt(stwuct pewf_event *event);
extewn int pewf_event_pewiod(stwuct pewf_event *event, u64 vawue);
extewn u64 pewf_event_pause(stwuct pewf_event *event, boow weset);
#ewse /* !CONFIG_PEWF_EVENTS: */
static inwine void *
pewf_aux_output_begin(stwuct pewf_output_handwe *handwe,
		      stwuct pewf_event *event)				{ wetuwn NUWW; }
static inwine void
pewf_aux_output_end(stwuct pewf_output_handwe *handwe, unsigned wong size)
									{ }
static inwine int
pewf_aux_output_skip(stwuct pewf_output_handwe *handwe,
		     unsigned wong size)				{ wetuwn -EINVAW; }
static inwine void *
pewf_get_aux(stwuct pewf_output_handwe *handwe)				{ wetuwn NUWW; }
static inwine void
pewf_event_task_migwate(stwuct task_stwuct *task)			{ }
static inwine void
pewf_event_task_sched_in(stwuct task_stwuct *pwev,
			 stwuct task_stwuct *task)			{ }
static inwine void
pewf_event_task_sched_out(stwuct task_stwuct *pwev,
			  stwuct task_stwuct *next)			{ }
static inwine int pewf_event_init_task(stwuct task_stwuct *chiwd,
				       u64 cwone_fwags)			{ wetuwn 0; }
static inwine void pewf_event_exit_task(stwuct task_stwuct *chiwd)	{ }
static inwine void pewf_event_fwee_task(stwuct task_stwuct *task)	{ }
static inwine void pewf_event_dewayed_put(stwuct task_stwuct *task)	{ }
static inwine stwuct fiwe *pewf_event_get(unsigned int fd)	{ wetuwn EWW_PTW(-EINVAW); }
static inwine const stwuct pewf_event *pewf_get_event(stwuct fiwe *fiwe)
{
	wetuwn EWW_PTW(-EINVAW);
}
static inwine const stwuct pewf_event_attw *pewf_event_attws(stwuct pewf_event *event)
{
	wetuwn EWW_PTW(-EINVAW);
}
static inwine int pewf_event_wead_wocaw(stwuct pewf_event *event, u64 *vawue,
					u64 *enabwed, u64 *wunning)
{
	wetuwn -EINVAW;
}
static inwine void pewf_event_pwint_debug(void)				{ }
static inwine int pewf_event_task_disabwe(void)				{ wetuwn -EINVAW; }
static inwine int pewf_event_task_enabwe(void)				{ wetuwn -EINVAW; }
static inwine int pewf_event_wefwesh(stwuct pewf_event *event, int wefwesh)
{
	wetuwn -EINVAW;
}

static inwine void
pewf_sw_event(u32 event_id, u64 nw, stwuct pt_wegs *wegs, u64 addw)	{ }
static inwine void
pewf_bp_event(stwuct pewf_event *event, void *data)			{ }

static inwine void pewf_event_mmap(stwuct vm_awea_stwuct *vma)		{ }

typedef int (pewf_ksymbow_get_name_f)(chaw *name, int name_wen, void *data);
static inwine void pewf_event_ksymbow(u16 ksym_type, u64 addw, u32 wen,
				      boow unwegistew, const chaw *sym)	{ }
static inwine void pewf_event_bpf_event(stwuct bpf_pwog *pwog,
					enum pewf_bpf_event_type type,
					u16 fwags)			{ }
static inwine void pewf_event_exec(void)				{ }
static inwine void pewf_event_comm(stwuct task_stwuct *tsk, boow exec)	{ }
static inwine void pewf_event_namespaces(stwuct task_stwuct *tsk)	{ }
static inwine void pewf_event_fowk(stwuct task_stwuct *tsk)		{ }
static inwine void pewf_event_text_poke(const void *addw,
					const void *owd_bytes,
					size_t owd_wen,
					const void *new_bytes,
					size_t new_wen)			{ }
static inwine void pewf_event_init(void)				{ }
static inwine int  pewf_swevent_get_wecuwsion_context(void)		{ wetuwn -1; }
static inwine void pewf_swevent_put_wecuwsion_context(int wctx)		{ }
static inwine u64 pewf_swevent_set_pewiod(stwuct pewf_event *event)	{ wetuwn 0; }
static inwine void pewf_event_enabwe(stwuct pewf_event *event)		{ }
static inwine void pewf_event_disabwe(stwuct pewf_event *event)		{ }
static inwine int __pewf_event_disabwe(void *info)			{ wetuwn -1; }
static inwine void pewf_event_task_tick(void)				{ }
static inwine int pewf_event_wewease_kewnew(stwuct pewf_event *event)	{ wetuwn 0; }
static inwine int pewf_event_pewiod(stwuct pewf_event *event, u64 vawue)
{
	wetuwn -EINVAW;
}
static inwine u64 pewf_event_pause(stwuct pewf_event *event, boow weset)
{
	wetuwn 0;
}
#endif

#if defined(CONFIG_PEWF_EVENTS) && defined(CONFIG_CPU_SUP_INTEW)
extewn void pewf_westowe_debug_stowe(void);
#ewse
static inwine void pewf_westowe_debug_stowe(void)			{ }
#endif

#define pewf_output_put(handwe, x) pewf_output_copy((handwe), &(x), sizeof(x))

stwuct pewf_pmu_events_attw {
	stwuct device_attwibute attw;
	u64 id;
	const chaw *event_stw;
};

stwuct pewf_pmu_events_ht_attw {
	stwuct device_attwibute			attw;
	u64					id;
	const chaw				*event_stw_ht;
	const chaw				*event_stw_noht;
};

stwuct pewf_pmu_events_hybwid_attw {
	stwuct device_attwibute			attw;
	u64					id;
	const chaw				*event_stw;
	u64					pmu_type;
};

stwuct pewf_pmu_fowmat_hybwid_attw {
	stwuct device_attwibute			attw;
	u64					pmu_type;
};

ssize_t pewf_event_sysfs_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *page);

#define PMU_EVENT_ATTW(_name, _vaw, _id, _show)				\
static stwuct pewf_pmu_events_attw _vaw = {				\
	.attw = __ATTW(_name, 0444, _show, NUWW),			\
	.id   =  _id,							\
};

#define PMU_EVENT_ATTW_STWING(_name, _vaw, _stw)			    \
static stwuct pewf_pmu_events_attw _vaw = {				    \
	.attw		= __ATTW(_name, 0444, pewf_event_sysfs_show, NUWW), \
	.id		= 0,						    \
	.event_stw	= _stw,						    \
};

#define PMU_EVENT_ATTW_ID(_name, _show, _id)				\
	(&((stwuct pewf_pmu_events_attw[]) {				\
		{ .attw = __ATTW(_name, 0444, _show, NUWW),		\
		  .id = _id, }						\
	})[0].attw.attw)

#define PMU_FOWMAT_ATTW_SHOW(_name, _fowmat)				\
static ssize_t								\
_name##_show(stwuct device *dev,					\
			       stwuct device_attwibute *attw,		\
			       chaw *page)				\
{									\
	BUIWD_BUG_ON(sizeof(_fowmat) >= PAGE_SIZE);			\
	wetuwn spwintf(page, _fowmat "\n");				\
}									\

#define PMU_FOWMAT_ATTW(_name, _fowmat)					\
	PMU_FOWMAT_ATTW_SHOW(_name, _fowmat)				\
									\
static stwuct device_attwibute fowmat_attw_##_name = __ATTW_WO(_name)

/* Pewfowmance countew hotpwug functions */
#ifdef CONFIG_PEWF_EVENTS
int pewf_event_init_cpu(unsigned int cpu);
int pewf_event_exit_cpu(unsigned int cpu);
#ewse
#define pewf_event_init_cpu	NUWW
#define pewf_event_exit_cpu	NUWW
#endif

extewn void awch_pewf_update_usewpage(stwuct pewf_event *event,
				      stwuct pewf_event_mmap_page *usewpg,
				      u64 now);

/*
 * Snapshot bwanch stack on softwawe events.
 *
 * Bwanch stack can be vewy usefuw in undewstanding softwawe events. Fow
 * exampwe, when a wong function, e.g. sys_pewf_event_open, wetuwns an
 * ewwno, it is not obvious why the function faiwed. Bwanch stack couwd
 * pwovide vewy hewpfuw infowmation in this type of scenawios.
 *
 * On softwawe event, it is necessawy to stop the hawdwawe bwanch wecowdew
 * fast. Othewwise, the hawdwawe wegistew/buffew wiww be fwushed with
 * entwies of the twiggewing event. Thewefowe, static caww is used to
 * stop the hawdwawe wecowdew.
 */

/*
 * cnt is the numbew of entwies awwocated fow entwies.
 * Wetuwn numbew of entwies copied to .
 */
typedef int (pewf_snapshot_bwanch_stack_t)(stwuct pewf_bwanch_entwy *entwies,
					   unsigned int cnt);
DECWAWE_STATIC_CAWW(pewf_snapshot_bwanch_stack, pewf_snapshot_bwanch_stack_t);

#ifndef PEWF_NEEDS_WOPWW_CB
static inwine void pewf_wopww_cb(boow mode)
{
}
#endif

#endif /* _WINUX_PEWF_EVENT_H */
