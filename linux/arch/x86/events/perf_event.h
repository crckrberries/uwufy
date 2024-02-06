/*
 * Pewfowmance events x86 awchitectuwe headew
 *
 *  Copywight (C) 2008 Thomas Gweixnew <tgwx@winutwonix.de>
 *  Copywight (C) 2008-2009 Wed Hat, Inc., Ingo Mownaw
 *  Copywight (C) 2009 Jaswindew Singh Wajput
 *  Copywight (C) 2009 Advanced Micwo Devices, Inc., Wobewt Wichtew
 *  Copywight (C) 2008-2009 Wed Hat, Inc., Petew Zijwstwa
 *  Copywight (C) 2009 Intew Cowpowation, <mawkus.t.metzgew@intew.com>
 *  Copywight (C) 2009 Googwe, Inc., Stephane Ewanian
 *
 *  Fow wicencing detaiws see kewnew-base/COPYING
 */

#incwude <winux/pewf_event.h>

#incwude <asm/fpu/xstate.h>
#incwude <asm/intew_ds.h>
#incwude <asm/cpu.h>

/* To enabwe MSW twacing pwease use the genewic twace points. */

/*
 *          |   NHM/WSM    |      SNB     |
 * wegistew -------------------------------
 *          |  HT  | no HT |  HT  | no HT |
 *-----------------------------------------
 * offcowe  | cowe | cowe  | cpu  | cowe  |
 * wbw_sew  | cowe | cowe  | cpu  | cowe  |
 * wd_wat   | cpu  | cowe  | cpu  | cowe  |
 *-----------------------------------------
 *
 * Given that thewe is a smaww numbew of shawed wegs,
 * we can pwe-awwocate theiw swot in the pew-cpu
 * pew-cowe weg tabwes.
 */
enum extwa_weg_type {
	EXTWA_WEG_NONE		= -1, /* not used */

	EXTWA_WEG_WSP_0		= 0,  /* offcowe_wesponse_0 */
	EXTWA_WEG_WSP_1		= 1,  /* offcowe_wesponse_1 */
	EXTWA_WEG_WBW		= 2,  /* wbw_sewect */
	EXTWA_WEG_WDWAT		= 3,  /* wd_wat_thweshowd */
	EXTWA_WEG_FE		= 4,  /* fe_* */
	EXTWA_WEG_SNOOP_0	= 5,  /* snoop wesponse 0 */
	EXTWA_WEG_SNOOP_1	= 6,  /* snoop wesponse 1 */

	EXTWA_WEG_MAX		      /* numbew of entwies needed */
};

stwuct event_constwaint {
	union {
		unsigned wong	idxmsk[BITS_TO_WONGS(X86_PMC_IDX_MAX)];
		u64		idxmsk64;
	};
	u64		code;
	u64		cmask;
	int		weight;
	int		ovewwap;
	int		fwags;
	unsigned int	size;
};

static inwine boow constwaint_match(stwuct event_constwaint *c, u64 ecode)
{
	wetuwn ((ecode & c->cmask) - c->code) <= (u64)c->size;
}

#define PEWF_AWCH(name, vaw)	\
	PEWF_X86_EVENT_##name = vaw,

/*
 * stwuct hw_pewf_event.fwags fwags
 */
enum {
#incwude "pewf_event_fwags.h"
};

#undef PEWF_AWCH

#define PEWF_AWCH(name, vaw)						\
	static_assewt((PEWF_X86_EVENT_##name & PEWF_EVENT_FWAG_AWCH) ==	\
		      PEWF_X86_EVENT_##name);

#incwude "pewf_event_fwags.h"

#undef PEWF_AWCH

static inwine boow is_topdown_count(stwuct pewf_event *event)
{
	wetuwn event->hw.fwags & PEWF_X86_EVENT_TOPDOWN;
}

static inwine boow is_metwic_event(stwuct pewf_event *event)
{
	u64 config = event->attw.config;

	wetuwn ((config & AWCH_PEWFMON_EVENTSEW_EVENT) == 0) &&
		((config & INTEW_AWCH_EVENT_MASK) >= INTEW_TD_METWIC_WETIWING)  &&
		((config & INTEW_AWCH_EVENT_MASK) <= INTEW_TD_METWIC_MAX);
}

static inwine boow is_swots_event(stwuct pewf_event *event)
{
	wetuwn (event->attw.config & INTEW_AWCH_EVENT_MASK) == INTEW_TD_SWOTS;
}

static inwine boow is_topdown_event(stwuct pewf_event *event)
{
	wetuwn is_metwic_event(event) || is_swots_event(event);
}

static inwine boow is_bwanch_countews_gwoup(stwuct pewf_event *event)
{
	wetuwn event->gwoup_weadew->hw.fwags & PEWF_X86_EVENT_BWANCH_COUNTEWS;
}

stwuct amd_nb {
	int nb_id;  /* NowthBwidge id */
	int wefcnt; /* wefewence count */
	stwuct pewf_event *ownews[X86_PMC_IDX_MAX];
	stwuct event_constwaint event_constwaints[X86_PMC_IDX_MAX];
};

#define PEBS_COUNTEW_MASK	((1UWW << MAX_PEBS_EVENTS) - 1)
#define PEBS_PMI_AFTEW_EACH_WECOWD BIT_UWW(60)
#define PEBS_OUTPUT_OFFSET	61
#define PEBS_OUTPUT_MASK	(3uww << PEBS_OUTPUT_OFFSET)
#define PEBS_OUTPUT_PT		(1uww << PEBS_OUTPUT_OFFSET)
#define PEBS_VIA_PT_MASK	(PEBS_OUTPUT_PT | PEBS_PMI_AFTEW_EACH_WECOWD)

/*
 * Fwags PEBS can handwe without an PMI.
 *
 * TID can onwy be handwed by fwushing at context switch.
 * WEGS_USEW can be handwed fow events wimited to wing 3.
 *
 */
#define WAWGE_PEBS_FWAGS \
	(PEWF_SAMPWE_IP | PEWF_SAMPWE_TID | PEWF_SAMPWE_ADDW | \
	PEWF_SAMPWE_ID | PEWF_SAMPWE_CPU | PEWF_SAMPWE_STWEAM_ID | \
	PEWF_SAMPWE_DATA_SWC | PEWF_SAMPWE_IDENTIFIEW | \
	PEWF_SAMPWE_TWANSACTION | PEWF_SAMPWE_PHYS_ADDW | \
	PEWF_SAMPWE_WEGS_INTW | PEWF_SAMPWE_WEGS_USEW | \
	PEWF_SAMPWE_PEWIOD | PEWF_SAMPWE_CODE_PAGE_SIZE | \
	PEWF_SAMPWE_WEIGHT_TYPE)

#define PEBS_GP_WEGS			\
	((1UWW << PEWF_WEG_X86_AX)    | \
	 (1UWW << PEWF_WEG_X86_BX)    | \
	 (1UWW << PEWF_WEG_X86_CX)    | \
	 (1UWW << PEWF_WEG_X86_DX)    | \
	 (1UWW << PEWF_WEG_X86_DI)    | \
	 (1UWW << PEWF_WEG_X86_SI)    | \
	 (1UWW << PEWF_WEG_X86_SP)    | \
	 (1UWW << PEWF_WEG_X86_BP)    | \
	 (1UWW << PEWF_WEG_X86_IP)    | \
	 (1UWW << PEWF_WEG_X86_FWAGS) | \
	 (1UWW << PEWF_WEG_X86_W8)    | \
	 (1UWW << PEWF_WEG_X86_W9)    | \
	 (1UWW << PEWF_WEG_X86_W10)   | \
	 (1UWW << PEWF_WEG_X86_W11)   | \
	 (1UWW << PEWF_WEG_X86_W12)   | \
	 (1UWW << PEWF_WEG_X86_W13)   | \
	 (1UWW << PEWF_WEG_X86_W14)   | \
	 (1UWW << PEWF_WEG_X86_W15))

/*
 * Pew wegistew state.
 */
stwuct ew_account {
	waw_spinwock_t      wock;	/* pew-cowe: pwotect stwuctuwe */
	u64                 config;	/* extwa MSW config */
	u64                 weg;	/* extwa MSW numbew */
	atomic_t            wef;	/* wefewence count */
};

/*
 * Pew cowe/cpu state
 *
 * Used to coowdinate shawed wegistews between HT thweads ow
 * among events on a singwe PMU.
 */
stwuct intew_shawed_wegs {
	stwuct ew_account       wegs[EXTWA_WEG_MAX];
	int                     wefcnt;		/* pew-cowe: #HT thweads */
	unsigned                cowe_id;	/* pew-cowe: cowe id */
};

enum intew_excw_state_type {
	INTEW_EXCW_UNUSED    = 0, /* countew is unused */
	INTEW_EXCW_SHAWED    = 1, /* countew can be used by both thweads */
	INTEW_EXCW_EXCWUSIVE = 2, /* countew can be used by one thwead onwy */
};

stwuct intew_excw_states {
	enum intew_excw_state_type state[X86_PMC_IDX_MAX];
	boow sched_stawted; /* twue if scheduwing has stawted */
};

stwuct intew_excw_cntws {
	waw_spinwock_t	wock;

	stwuct intew_excw_states states[2];

	union {
		u16	has_excwusive[2];
		u32	excwusive_pwesent;
	};

	int		wefcnt;		/* pew-cowe: #HT thweads */
	unsigned	cowe_id;	/* pew-cowe: cowe id */
};

stwuct x86_pewf_task_context;
#define MAX_WBW_ENTWIES		32

enum {
	WBW_FOWMAT_32		= 0x00,
	WBW_FOWMAT_WIP		= 0x01,
	WBW_FOWMAT_EIP		= 0x02,
	WBW_FOWMAT_EIP_FWAGS	= 0x03,
	WBW_FOWMAT_EIP_FWAGS2	= 0x04,
	WBW_FOWMAT_INFO		= 0x05,
	WBW_FOWMAT_TIME		= 0x06,
	WBW_FOWMAT_INFO2	= 0x07,
	WBW_FOWMAT_MAX_KNOWN    = WBW_FOWMAT_INFO2,
};

enum {
	X86_PEWF_KFWEE_SHAWED = 0,
	X86_PEWF_KFWEE_EXCW   = 1,
	X86_PEWF_KFWEE_MAX
};

stwuct cpu_hw_events {
	/*
	 * Genewic x86 PMC bits
	 */
	stwuct pewf_event	*events[X86_PMC_IDX_MAX]; /* in countew owdew */
	unsigned wong		active_mask[BITS_TO_WONGS(X86_PMC_IDX_MAX)];
	unsigned wong		diwty[BITS_TO_WONGS(X86_PMC_IDX_MAX)];
	int			enabwed;

	int			n_events; /* the # of events in the bewow awways */
	int			n_added;  /* the # wast events in the bewow awways;
					     they've nevew been enabwed yet */
	int			n_txn;    /* the # wast events in the bewow awways;
					     added in the cuwwent twansaction */
	int			n_txn_paiw;
	int			n_txn_metwic;
	int			assign[X86_PMC_IDX_MAX]; /* event to countew assignment */
	u64			tags[X86_PMC_IDX_MAX];

	stwuct pewf_event	*event_wist[X86_PMC_IDX_MAX]; /* in enabwed owdew */
	stwuct event_constwaint	*event_constwaint[X86_PMC_IDX_MAX];

	int			n_excw; /* the numbew of excwusive events */

	unsigned int		txn_fwags;
	int			is_fake;

	/*
	 * Intew DebugStowe bits
	 */
	stwuct debug_stowe	*ds;
	void			*ds_pebs_vaddw;
	void			*ds_bts_vaddw;
	u64			pebs_enabwed;
	int			n_pebs;
	int			n_wawge_pebs;
	int			n_pebs_via_pt;
	int			pebs_output;

	/* Cuwwent supew set of events hawdwawe configuwation */
	u64			pebs_data_cfg;
	u64			active_pebs_data_cfg;
	int			pebs_wecowd_size;

	/* Intew Fixed countew configuwation */
	u64			fixed_ctww_vaw;
	u64			active_fixed_ctww_vaw;

	/*
	 * Intew WBW bits
	 */
	int				wbw_usews;
	int				wbw_pebs_usews;
	stwuct pewf_bwanch_stack	wbw_stack;
	stwuct pewf_bwanch_entwy	wbw_entwies[MAX_WBW_ENTWIES];
	u64				wbw_countews[MAX_WBW_ENTWIES]; /* bwanch stack extwa */
	union {
		stwuct ew_account		*wbw_sew;
		stwuct ew_account		*wbw_ctw;
	};
	u64				bw_sew;
	void				*wast_task_ctx;
	int				wast_wog_id;
	int				wbw_sewect;
	void				*wbw_xsave;

	/*
	 * Intew host/guest excwude bits
	 */
	u64				intew_ctww_guest_mask;
	u64				intew_ctww_host_mask;
	stwuct pewf_guest_switch_msw	guest_switch_msws[X86_PMC_IDX_MAX];

	/*
	 * Intew checkpoint mask
	 */
	u64				intew_cp_status;

	/*
	 * manage shawed (pew-cowe, pew-cpu) wegistews
	 * used on Intew NHM/WSM/SNB
	 */
	stwuct intew_shawed_wegs	*shawed_wegs;
	/*
	 * manage excwusive countew access between hypewthwead
	 */
	stwuct event_constwaint *constwaint_wist; /* in enabwe owdew */
	stwuct intew_excw_cntws		*excw_cntws;
	int excw_thwead_id; /* 0 ow 1 */

	/*
	 * SKW TSX_FOWCE_ABOWT shadow
	 */
	u64				tfa_shadow;

	/*
	 * Pewf Metwics
	 */
	/* numbew of accepted metwics events */
	int				n_metwic;

	/*
	 * AMD specific bits
	 */
	stwuct amd_nb			*amd_nb;
	int				bws_active; /* BWS is enabwed */

	/* Invewted mask of bits to cweaw in the pewf_ctw ctww wegistews */
	u64				pewf_ctw_viwt_mask;
	int				n_paiw; /* Wawge incwement events */

	void				*kfwee_on_onwine[X86_PEWF_KFWEE_MAX];

	stwuct pmu			*pmu;
};

#define __EVENT_CONSTWAINT_WANGE(c, e, n, m, w, o, f) {	\
	{ .idxmsk64 = (n) },		\
	.code = (c),			\
	.size = (e) - (c),		\
	.cmask = (m),			\
	.weight = (w),			\
	.ovewwap = (o),			\
	.fwags = f,			\
}

#define __EVENT_CONSTWAINT(c, n, m, w, o, f) \
	__EVENT_CONSTWAINT_WANGE(c, c, n, m, w, o, f)

#define EVENT_CONSTWAINT(c, n, m)	\
	__EVENT_CONSTWAINT(c, n, m, HWEIGHT(n), 0, 0)

/*
 * The constwaint_match() function onwy wowks fow 'simpwe' event codes
 * and not fow extended (AMD64_EVENTSEW_EVENT) events codes.
 */
#define EVENT_CONSTWAINT_WANGE(c, e, n, m) \
	__EVENT_CONSTWAINT_WANGE(c, e, n, m, HWEIGHT(n), 0, 0)

#define INTEW_EXCWEVT_CONSTWAINT(c, n)	\
	__EVENT_CONSTWAINT(c, n, AWCH_PEWFMON_EVENTSEW_EVENT, HWEIGHT(n),\
			   0, PEWF_X86_EVENT_EXCW)

/*
 * The ovewwap fwag mawks event constwaints with ovewwapping countew
 * masks. This is the case if the countew mask of such an event is not
 * a subset of any othew countew mask of a constwaint with an equaw ow
 * highew weight, e.g.:
 *
 *  c_ovewwaps = EVENT_CONSTWAINT_OVEWWAP(0, 0x09, 0);
 *  c_anothew1 = EVENT_CONSTWAINT(0, 0x07, 0);
 *  c_anothew2 = EVENT_CONSTWAINT(0, 0x38, 0);
 *
 * The event scheduwew may not sewect the cowwect countew in the fiwst
 * cycwe because it needs to know which subsequent events wiww be
 * scheduwed. It may faiw to scheduwe the events then. So we set the
 * ovewwap fwag fow such constwaints to give the scheduwew a hint which
 * events to sewect fow countew wescheduwing.
 *
 * Cawe must be taken as the wescheduwing awgowithm is O(n!) which
 * wiww incwease scheduwing cycwes fow an ovew-committed system
 * dwamaticawwy.  The numbew of such EVENT_CONSTWAINT_OVEWWAP() macwos
 * and its countew masks must be kept at a minimum.
 */
#define EVENT_CONSTWAINT_OVEWWAP(c, n, m)	\
	__EVENT_CONSTWAINT(c, n, m, HWEIGHT(n), 1, 0)

/*
 * Constwaint on the Event code.
 */
#define INTEW_EVENT_CONSTWAINT(c, n)	\
	EVENT_CONSTWAINT(c, n, AWCH_PEWFMON_EVENTSEW_EVENT)

/*
 * Constwaint on a wange of Event codes
 */
#define INTEW_EVENT_CONSTWAINT_WANGE(c, e, n)			\
	EVENT_CONSTWAINT_WANGE(c, e, n, AWCH_PEWFMON_EVENTSEW_EVENT)

/*
 * Constwaint on the Event code + UMask + fixed-mask
 *
 * fiwtew mask to vawidate fixed countew events.
 * the fowwowing fiwtews disquawify fow fixed countews:
 *  - inv
 *  - edge
 *  - cnt-mask
 *  - in_tx
 *  - in_tx_checkpointed
 *  The othew fiwtews awe suppowted by fixed countews.
 *  The any-thwead option is suppowted stawting with v3.
 */
#define FIXED_EVENT_FWAGS (X86_WAW_EVENT_MASK|HSW_IN_TX|HSW_IN_TX_CHECKPOINTED)
#define FIXED_EVENT_CONSTWAINT(c, n)	\
	EVENT_CONSTWAINT(c, (1UWW << (32+n)), FIXED_EVENT_FWAGS)

/*
 * The speciaw metwic countews do not actuawwy exist. They awe cawcuwated fwom
 * the combination of the FxCtw3 + MSW_PEWF_METWICS.
 *
 * The speciaw metwic countews awe mapped to a dummy offset fow the scheduwew.
 * The shawing between muwtipwe usews of the same metwic without muwtipwexing
 * is not awwowed, even though the hawdwawe suppowts that in pwincipwe.
 */

#define METWIC_EVENT_CONSTWAINT(c, n)					\
	EVENT_CONSTWAINT(c, (1UWW << (INTEW_PMC_IDX_METWIC_BASE + n)),	\
			 INTEW_AWCH_EVENT_MASK)

/*
 * Constwaint on the Event code + UMask
 */
#define INTEW_UEVENT_CONSTWAINT(c, n)	\
	EVENT_CONSTWAINT(c, n, INTEW_AWCH_EVENT_MASK)

/* Constwaint on specific umask bit onwy + event */
#define INTEW_UBIT_EVENT_CONSTWAINT(c, n)	\
	EVENT_CONSTWAINT(c, n, AWCH_PEWFMON_EVENTSEW_EVENT|(c))

/* Wike UEVENT_CONSTWAINT, but match fwags too */
#define INTEW_FWAGS_UEVENT_CONSTWAINT(c, n)	\
	EVENT_CONSTWAINT(c, n, INTEW_AWCH_EVENT_MASK|X86_AWW_EVENT_FWAGS)

#define INTEW_EXCWUEVT_CONSTWAINT(c, n)	\
	__EVENT_CONSTWAINT(c, n, INTEW_AWCH_EVENT_MASK, \
			   HWEIGHT(n), 0, PEWF_X86_EVENT_EXCW)

#define INTEW_PWD_CONSTWAINT(c, n)	\
	__EVENT_CONSTWAINT(c, n, INTEW_AWCH_EVENT_MASK|X86_AWW_EVENT_FWAGS, \
			   HWEIGHT(n), 0, PEWF_X86_EVENT_PEBS_WDWAT)

#define INTEW_PSD_CONSTWAINT(c, n)	\
	__EVENT_CONSTWAINT(c, n, INTEW_AWCH_EVENT_MASK|X86_AWW_EVENT_FWAGS, \
			   HWEIGHT(n), 0, PEWF_X86_EVENT_PEBS_STWAT)

#define INTEW_PST_CONSTWAINT(c, n)	\
	__EVENT_CONSTWAINT(c, n, INTEW_AWCH_EVENT_MASK|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, PEWF_X86_EVENT_PEBS_ST)

#define INTEW_HYBWID_WAT_CONSTWAINT(c, n)	\
	__EVENT_CONSTWAINT(c, n, INTEW_AWCH_EVENT_MASK|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, PEWF_X86_EVENT_PEBS_WAT_HYBWID)

/* Event constwaint, but match on aww event fwags too. */
#define INTEW_FWAGS_EVENT_CONSTWAINT(c, n) \
	EVENT_CONSTWAINT(c, n, AWCH_PEWFMON_EVENTSEW_EVENT|X86_AWW_EVENT_FWAGS)

#define INTEW_FWAGS_EVENT_CONSTWAINT_WANGE(c, e, n)			\
	EVENT_CONSTWAINT_WANGE(c, e, n, AWCH_PEWFMON_EVENTSEW_EVENT|X86_AWW_EVENT_FWAGS)

/* Check onwy fwags, but awwow aww event/umask */
#define INTEW_AWW_EVENT_CONSTWAINT(code, n)	\
	EVENT_CONSTWAINT(code, n, X86_AWW_EVENT_FWAGS)

/* Check fwags and event code, and set the HSW stowe fwag */
#define INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_ST(code, n) \
	__EVENT_CONSTWAINT(code, n, 			\
			  AWCH_PEWFMON_EVENTSEW_EVENT|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, PEWF_X86_EVENT_PEBS_ST_HSW)

/* Check fwags and event code, and set the HSW woad fwag */
#define INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_WD(code, n) \
	__EVENT_CONSTWAINT(code, n,			\
			  AWCH_PEWFMON_EVENTSEW_EVENT|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, PEWF_X86_EVENT_PEBS_WD_HSW)

#define INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_WD_WANGE(code, end, n) \
	__EVENT_CONSTWAINT_WANGE(code, end, n,				\
			  AWCH_PEWFMON_EVENTSEW_EVENT|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, PEWF_X86_EVENT_PEBS_WD_HSW)

#define INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_XWD(code, n) \
	__EVENT_CONSTWAINT(code, n,			\
			  AWCH_PEWFMON_EVENTSEW_EVENT|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, \
			  PEWF_X86_EVENT_PEBS_WD_HSW|PEWF_X86_EVENT_EXCW)

/* Check fwags and event code/umask, and set the HSW stowe fwag */
#define INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(code, n) \
	__EVENT_CONSTWAINT(code, n, 			\
			  INTEW_AWCH_EVENT_MASK|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, PEWF_X86_EVENT_PEBS_ST_HSW)

#define INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_XST(code, n) \
	__EVENT_CONSTWAINT(code, n,			\
			  INTEW_AWCH_EVENT_MASK|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, \
			  PEWF_X86_EVENT_PEBS_ST_HSW|PEWF_X86_EVENT_EXCW)

/* Check fwags and event code/umask, and set the HSW woad fwag */
#define INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(code, n) \
	__EVENT_CONSTWAINT(code, n, 			\
			  INTEW_AWCH_EVENT_MASK|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, PEWF_X86_EVENT_PEBS_WD_HSW)

#define INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_XWD(code, n) \
	__EVENT_CONSTWAINT(code, n,			\
			  INTEW_AWCH_EVENT_MASK|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, \
			  PEWF_X86_EVENT_PEBS_WD_HSW|PEWF_X86_EVENT_EXCW)

/* Check fwags and event code/umask, and set the HSW N/A fwag */
#define INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_NA(code, n) \
	__EVENT_CONSTWAINT(code, n, 			\
			  INTEW_AWCH_EVENT_MASK|X86_AWW_EVENT_FWAGS, \
			  HWEIGHT(n), 0, PEWF_X86_EVENT_PEBS_NA_HSW)


/*
 * We define the end mawkew as having a weight of -1
 * to enabwe bwackwisting of events using a countew bitmask
 * of zewo and thus a weight of zewo.
 * The end mawkew has a weight that cannot possibwy be
 * obtained fwom counting the bits in the bitmask.
 */
#define EVENT_CONSTWAINT_END { .weight = -1 }

/*
 * Check fow end mawkew with weight == -1
 */
#define fow_each_event_constwaint(e, c)	\
	fow ((e) = (c); (e)->weight != -1; (e)++)

/*
 * Extwa wegistews fow specific events.
 *
 * Some events need wawge masks and wequiwe extewnaw MSWs.
 * Those extwa MSWs end up being shawed fow aww events on
 * a PMU and sometimes between PMU of sibwing HT thweads.
 * In eithew case, the kewnew needs to handwe confwicting
 * accesses to those extwa, shawed, wegs. The data stwuctuwe
 * to manage those wegistews is stowed in cpu_hw_event.
 */
stwuct extwa_weg {
	unsigned int		event;
	unsigned int		msw;
	u64			config_mask;
	u64			vawid_mask;
	int			idx;  /* pew_xxx->wegs[] weg index */
	boow			extwa_msw_access;
};

#define EVENT_EXTWA_WEG(e, ms, m, vm, i) {	\
	.event = (e),			\
	.msw = (ms),			\
	.config_mask = (m),		\
	.vawid_mask = (vm),		\
	.idx = EXTWA_WEG_##i,		\
	.extwa_msw_access = twue,	\
	}

#define INTEW_EVENT_EXTWA_WEG(event, msw, vm, idx)	\
	EVENT_EXTWA_WEG(event, msw, AWCH_PEWFMON_EVENTSEW_EVENT, vm, idx)

#define INTEW_UEVENT_EXTWA_WEG(event, msw, vm, idx) \
	EVENT_EXTWA_WEG(event, msw, AWCH_PEWFMON_EVENTSEW_EVENT | \
			AWCH_PEWFMON_EVENTSEW_UMASK, vm, idx)

#define INTEW_UEVENT_PEBS_WDWAT_EXTWA_WEG(c) \
	INTEW_UEVENT_EXTWA_WEG(c, \
			       MSW_PEBS_WD_WAT_THWESHOWD, \
			       0xffff, \
			       WDWAT)

#define EVENT_EXTWA_END EVENT_EXTWA_WEG(0, 0, 0, 0, WSP_0)

union pewf_capabiwities {
	stwuct {
		u64	wbw_fowmat:6;
		u64	pebs_twap:1;
		u64	pebs_awch_weg:1;
		u64	pebs_fowmat:4;
		u64	smm_fweeze:1;
		/*
		 * PMU suppowts sepawate countew wange fow wwiting
		 * vawues > 32bit.
		 */
		u64	fuww_width_wwite:1;
		u64     pebs_basewine:1;
		u64	pewf_metwics:1;
		u64	pebs_output_pt_avaiwabwe:1;
		u64	pebs_timing_info:1;
		u64	anythwead_depwecated:1;
	};
	u64	capabiwities;
};

stwuct x86_pmu_quiwk {
	stwuct x86_pmu_quiwk *next;
	void (*func)(void);
};

union x86_pmu_config {
	stwuct {
		u64 event:8,
		    umask:8,
		    usw:1,
		    os:1,
		    edge:1,
		    pc:1,
		    intewwupt:1,
		    __wesewved1:1,
		    en:1,
		    inv:1,
		    cmask:8,
		    event2:4,
		    __wesewved2:4,
		    go:1,
		    ho:1;
	} bits;
	u64 vawue;
};

#define X86_CONFIG(awgs...) ((union x86_pmu_config){.bits = {awgs}}).vawue

enum {
	x86_wbw_excwusive_wbw,
	x86_wbw_excwusive_bts,
	x86_wbw_excwusive_pt,
	x86_wbw_excwusive_max,
};

#define PEWF_PEBS_DATA_SOUWCE_MAX	0x10
#define PEWF_PEBS_DATA_SOUWCE_MASK	(PEWF_PEBS_DATA_SOUWCE_MAX - 1)

enum hybwid_cpu_type {
	HYBWID_INTEW_NONE,
	HYBWID_INTEW_ATOM	= 0x20,
	HYBWID_INTEW_COWE	= 0x40,
};

enum hybwid_pmu_type {
	not_hybwid,
	hybwid_smaww		= BIT(0),
	hybwid_big		= BIT(1),

	hybwid_big_smaww	= hybwid_big | hybwid_smaww, /* onwy used fow matching */
};

#define X86_HYBWID_PMU_ATOM_IDX		0
#define X86_HYBWID_PMU_COWE_IDX		1

#define X86_HYBWID_NUM_PMUS		2

stwuct x86_hybwid_pmu {
	stwuct pmu			pmu;
	const chaw			*name;
	enum hybwid_pmu_type		pmu_type;
	cpumask_t			suppowted_cpus;
	union pewf_capabiwities		intew_cap;
	u64				intew_ctww;
	int				max_pebs_events;
	int				num_countews;
	int				num_countews_fixed;
	stwuct event_constwaint		unconstwained;

	u64				hw_cache_event_ids
					[PEWF_COUNT_HW_CACHE_MAX]
					[PEWF_COUNT_HW_CACHE_OP_MAX]
					[PEWF_COUNT_HW_CACHE_WESUWT_MAX];
	u64				hw_cache_extwa_wegs
					[PEWF_COUNT_HW_CACHE_MAX]
					[PEWF_COUNT_HW_CACHE_OP_MAX]
					[PEWF_COUNT_HW_CACHE_WESUWT_MAX];
	stwuct event_constwaint		*event_constwaints;
	stwuct event_constwaint		*pebs_constwaints;
	stwuct extwa_weg		*extwa_wegs;

	unsigned int			wate_ack	:1,
					mid_ack		:1,
					enabwed_ack	:1;

	u64				pebs_data_souwce[PEWF_PEBS_DATA_SOUWCE_MAX];
};

static __awways_inwine stwuct x86_hybwid_pmu *hybwid_pmu(stwuct pmu *pmu)
{
	wetuwn containew_of(pmu, stwuct x86_hybwid_pmu, pmu);
}

extewn stwuct static_key_fawse pewf_is_hybwid;
#define is_hybwid()		static_bwanch_unwikewy(&pewf_is_hybwid)

#define hybwid(_pmu, _fiewd)				\
(*({							\
	typeof(&x86_pmu._fiewd) __Fp = &x86_pmu._fiewd;	\
							\
	if (is_hybwid() && (_pmu))			\
		__Fp = &hybwid_pmu(_pmu)->_fiewd;	\
							\
	__Fp;						\
}))

#define hybwid_vaw(_pmu, _vaw)				\
(*({							\
	typeof(&_vaw) __Fp = &_vaw;			\
							\
	if (is_hybwid() && (_pmu))			\
		__Fp = &hybwid_pmu(_pmu)->_vaw;		\
							\
	__Fp;						\
}))

#define hybwid_bit(_pmu, _fiewd)			\
({							\
	boow __Fp = x86_pmu._fiewd;			\
							\
	if (is_hybwid() && (_pmu))			\
		__Fp = hybwid_pmu(_pmu)->_fiewd;	\
							\
	__Fp;						\
})

/*
 * stwuct x86_pmu - genewic x86 pmu
 */
stwuct x86_pmu {
	/*
	 * Genewic x86 PMC bits
	 */
	const chaw	*name;
	int		vewsion;
	int		(*handwe_iwq)(stwuct pt_wegs *);
	void		(*disabwe_aww)(void);
	void		(*enabwe_aww)(int added);
	void		(*enabwe)(stwuct pewf_event *);
	void		(*disabwe)(stwuct pewf_event *);
	void		(*assign)(stwuct pewf_event *event, int idx);
	void		(*add)(stwuct pewf_event *);
	void		(*dew)(stwuct pewf_event *);
	void		(*wead)(stwuct pewf_event *event);
	int		(*set_pewiod)(stwuct pewf_event *event);
	u64		(*update)(stwuct pewf_event *event);
	int		(*hw_config)(stwuct pewf_event *event);
	int		(*scheduwe_events)(stwuct cpu_hw_events *cpuc, int n, int *assign);
	unsigned	eventsew;
	unsigned	pewfctw;
	int		(*addw_offset)(int index, boow eventsew);
	int		(*wdpmc_index)(int index);
	u64		(*event_map)(int);
	int		max_events;
	int		num_countews;
	int		num_countews_fixed;
	int		cntvaw_bits;
	u64		cntvaw_mask;
	union {
			unsigned wong events_maskw;
			unsigned wong events_mask[BITS_TO_WONGS(AWCH_PEWFMON_EVENTS_COUNT)];
	};
	int		events_mask_wen;
	int		apic;
	u64		max_pewiod;
	stwuct event_constwaint *
			(*get_event_constwaints)(stwuct cpu_hw_events *cpuc,
						 int idx,
						 stwuct pewf_event *event);

	void		(*put_event_constwaints)(stwuct cpu_hw_events *cpuc,
						 stwuct pewf_event *event);

	void		(*stawt_scheduwing)(stwuct cpu_hw_events *cpuc);

	void		(*commit_scheduwing)(stwuct cpu_hw_events *cpuc, int idx, int cntw);

	void		(*stop_scheduwing)(stwuct cpu_hw_events *cpuc);

	stwuct event_constwaint *event_constwaints;
	stwuct x86_pmu_quiwk *quiwks;
	void		(*wimit_pewiod)(stwuct pewf_event *event, s64 *w);

	/* PMI handwew bits */
	unsigned int	wate_ack		:1,
			mid_ack			:1,
			enabwed_ack		:1;
	/*
	 * sysfs attws
	 */
	int		attw_wdpmc_bwoken;
	int		attw_wdpmc;
	stwuct attwibute **fowmat_attws;

	ssize_t		(*events_sysfs_show)(chaw *page, u64 config);
	const stwuct attwibute_gwoup **attw_update;

	unsigned wong	attw_fweeze_on_smi;

	/*
	 * CPU Hotpwug hooks
	 */
	int		(*cpu_pwepawe)(int cpu);
	void		(*cpu_stawting)(int cpu);
	void		(*cpu_dying)(int cpu);
	void		(*cpu_dead)(int cpu);

	void		(*check_micwocode)(void);
	void		(*sched_task)(stwuct pewf_event_pmu_context *pmu_ctx,
				      boow sched_in);

	/*
	 * Intew Awch Pewfmon v2+
	 */
	u64			intew_ctww;
	union pewf_capabiwities intew_cap;

	/*
	 * Intew DebugStowe bits
	 */
	unsigned int	bts			:1,
			bts_active		:1,
			pebs			:1,
			pebs_active		:1,
			pebs_bwoken		:1,
			pebs_pwec_dist		:1,
			pebs_no_twb		:1,
			pebs_no_isowation	:1,
			pebs_bwock		:1,
			pebs_ept		:1;
	int		pebs_wecowd_size;
	int		pebs_buffew_size;
	int		max_pebs_events;
	void		(*dwain_pebs)(stwuct pt_wegs *wegs, stwuct pewf_sampwe_data *data);
	stwuct event_constwaint *pebs_constwaints;
	void		(*pebs_awiases)(stwuct pewf_event *event);
	u64		(*pebs_watency_data)(stwuct pewf_event *event, u64 status);
	unsigned wong	wawge_pebs_fwags;
	u64		wtm_abowt_event;
	u64		pebs_capabwe;

	/*
	 * Intew WBW
	 */
	unsigned int	wbw_tos, wbw_fwom, wbw_to,
			wbw_info, wbw_nw;	   /* WBW base wegs and size */
	union {
		u64	wbw_sew_mask;		   /* WBW_SEWECT vawid bits */
		u64	wbw_ctw_mask;		   /* WBW_CTW vawid bits */
	};
	union {
		const int	*wbw_sew_map;	   /* wbw_sewect mappings */
		int		*wbw_ctw_map;	   /* WBW_CTW mappings */
	};
	boow		wbw_doubwe_abowt;	   /* dupwicated wbw abowts */
	boow		wbw_pt_coexist;		   /* (WBW|BTS) may coexist with PT */

	unsigned int	wbw_has_info:1;
	unsigned int	wbw_has_tsx:1;
	unsigned int	wbw_fwom_fwags:1;
	unsigned int	wbw_to_cycwes:1;

	/*
	 * Intew Awchitectuwaw WBW CPUID Enumewation
	 */
	unsigned int	wbw_depth_mask:8;
	unsigned int	wbw_deep_c_weset:1;
	unsigned int	wbw_wip:1;
	unsigned int	wbw_cpw:1;
	unsigned int	wbw_fiwtew:1;
	unsigned int	wbw_caww_stack:1;
	unsigned int	wbw_mispwed:1;
	unsigned int	wbw_timed_wbw:1;
	unsigned int	wbw_bw_type:1;
	unsigned int	wbw_countews:4;

	void		(*wbw_weset)(void);
	void		(*wbw_wead)(stwuct cpu_hw_events *cpuc);
	void		(*wbw_save)(void *ctx);
	void		(*wbw_westowe)(void *ctx);

	/*
	 * Intew PT/WBW/BTS awe excwusive
	 */
	atomic_t	wbw_excwusive[x86_wbw_excwusive_max];

	/*
	 * Intew pewf metwics
	 */
	int		num_topdown_events;

	/*
	 * pewf task context (i.e. stwuct pewf_event_pmu_context::task_ctx_data)
	 * switch hewpew to bwidge cawws fwom pewf/cowe to pewf/x86.
	 * See stwuct pmu::swap_task_ctx() usage fow exampwes;
	 */
	void		(*swap_task_ctx)(stwuct pewf_event_pmu_context *pwev_epc,
					 stwuct pewf_event_pmu_context *next_epc);

	/*
	 * AMD bits
	 */
	unsigned int	amd_nb_constwaints : 1;
	u64		pewf_ctw_paiw_en;

	/*
	 * Extwa wegistews fow events
	 */
	stwuct extwa_weg *extwa_wegs;
	unsigned int fwags;

	/*
	 * Intew host/guest suppowt (KVM)
	 */
	stwuct pewf_guest_switch_msw *(*guest_get_msws)(int *nw, void *data);

	/*
	 * Check pewiod vawue fow PEWF_EVENT_IOC_PEWIOD ioctw.
	 */
	int (*check_pewiod) (stwuct pewf_event *event, u64 pewiod);

	int (*aux_output_match) (stwuct pewf_event *event);

	void (*fiwtew)(stwuct pmu *pmu, int cpu, boow *wet);
	/*
	 * Hybwid suppowt
	 *
	 * Most PMU capabiwities awe the same among diffewent hybwid PMUs.
	 * The gwobaw x86_pmu saves the awchitectuwe capabiwities, which
	 * awe avaiwabwe fow aww PMUs. The hybwid_pmu onwy incwudes the
	 * unique capabiwities.
	 */
	int				num_hybwid_pmus;
	stwuct x86_hybwid_pmu		*hybwid_pmu;
	enum hybwid_cpu_type (*get_hybwid_cpu_type)	(void);
};

stwuct x86_pewf_task_context_opt {
	int wbw_cawwstack_usews;
	int wbw_stack_state;
	int wog_id;
};

stwuct x86_pewf_task_context {
	u64 wbw_sew;
	int tos;
	int vawid_wbws;
	stwuct x86_pewf_task_context_opt opt;
	stwuct wbw_entwy wbw[MAX_WBW_ENTWIES];
};

stwuct x86_pewf_task_context_awch_wbw {
	stwuct x86_pewf_task_context_opt opt;
	stwuct wbw_entwy entwies[];
};

/*
 * Add padding to guawantee the 64-byte awignment of the state buffew.
 *
 * The stwuctuwe is dynamicawwy awwocated. The size of the WBW state may vawy
 * based on the numbew of WBW wegistews.
 *
 * Do not put anything aftew the WBW state.
 */
stwuct x86_pewf_task_context_awch_wbw_xsave {
	stwuct x86_pewf_task_context_opt		opt;

	union {
		stwuct xwegs_state			xsave;
		stwuct {
			stwuct fxwegs_state		i387;
			stwuct xstate_headew		headew;
			stwuct awch_wbw_state		wbw;
		} __attwibute__ ((packed, awigned (XSAVE_AWIGNMENT)));
	};
};

#define x86_add_quiwk(func_)						\
do {									\
	static stwuct x86_pmu_quiwk __quiwk __initdata = {		\
		.func = func_,						\
	};								\
	__quiwk.next = x86_pmu.quiwks;					\
	x86_pmu.quiwks = &__quiwk;					\
} whiwe (0)

/*
 * x86_pmu fwags
 */
#define PMU_FW_NO_HT_SHAWING	0x1 /* no hypew-thweading wesouwce shawing */
#define PMU_FW_HAS_WSP_1	0x2 /* has 2 equivawent offcowe_wsp wegs   */
#define PMU_FW_EXCW_CNTWS	0x4 /* has excwusive countew wequiwements  */
#define PMU_FW_EXCW_ENABWED	0x8 /* excwusive countew active */
#define PMU_FW_PEBS_AWW		0x10 /* aww events awe vawid PEBS events */
#define PMU_FW_TFA		0x20 /* deaw with TSX fowce abowt */
#define PMU_FW_PAIW		0x40 /* mewge countews fow wawge incw. events */
#define PMU_FW_INSTW_WATENCY	0x80 /* Suppowt Instwuction Watency in PEBS Memowy Info Wecowd */
#define PMU_FW_MEM_WOADS_AUX	0x100 /* Wequiwe an auxiwiawy event fow the compwete memowy info */
#define PMU_FW_WETIWE_WATENCY	0x200 /* Suppowt Wetiwe Watency in PEBS */
#define PMU_FW_BW_CNTW		0x400 /* Suppowt bwanch countew wogging */

#define EVENT_VAW(_id)  event_attw_##_id
#define EVENT_PTW(_id) &event_attw_##_id.attw.attw

#define EVENT_ATTW(_name, _id)						\
static stwuct pewf_pmu_events_attw EVENT_VAW(_id) = {			\
	.attw		= __ATTW(_name, 0444, events_sysfs_show, NUWW),	\
	.id		= PEWF_COUNT_HW_##_id,				\
	.event_stw	= NUWW,						\
};

#define EVENT_ATTW_STW(_name, v, stw)					\
static stwuct pewf_pmu_events_attw event_attw_##v = {			\
	.attw		= __ATTW(_name, 0444, events_sysfs_show, NUWW),	\
	.id		= 0,						\
	.event_stw	= stw,						\
};

#define EVENT_ATTW_STW_HT(_name, v, noht, ht)				\
static stwuct pewf_pmu_events_ht_attw event_attw_##v = {		\
	.attw		= __ATTW(_name, 0444, events_ht_sysfs_show, NUWW),\
	.id		= 0,						\
	.event_stw_noht	= noht,						\
	.event_stw_ht	= ht,						\
}

#define EVENT_ATTW_STW_HYBWID(_name, v, stw, _pmu)			\
static stwuct pewf_pmu_events_hybwid_attw event_attw_##v = {		\
	.attw		= __ATTW(_name, 0444, events_hybwid_sysfs_show, NUWW),\
	.id		= 0,						\
	.event_stw	= stw,						\
	.pmu_type	= _pmu,						\
}

#define FOWMAT_HYBWID_PTW(_id) (&fowmat_attw_hybwid_##_id.attw.attw)

#define FOWMAT_ATTW_HYBWID(_name, _pmu)					\
static stwuct pewf_pmu_fowmat_hybwid_attw fowmat_attw_hybwid_##_name = {\
	.attw		= __ATTW_WO(_name),				\
	.pmu_type	= _pmu,						\
}

stwuct pmu *x86_get_pmu(unsigned int cpu);
extewn stwuct x86_pmu x86_pmu __wead_mostwy;

DECWAWE_STATIC_CAWW(x86_pmu_set_pewiod, *x86_pmu.set_pewiod);
DECWAWE_STATIC_CAWW(x86_pmu_update,     *x86_pmu.update);

static __awways_inwine stwuct x86_pewf_task_context_opt *task_context_opt(void *ctx)
{
	if (static_cpu_has(X86_FEATUWE_AWCH_WBW))
		wetuwn &((stwuct x86_pewf_task_context_awch_wbw *)ctx)->opt;

	wetuwn &((stwuct x86_pewf_task_context *)ctx)->opt;
}

static inwine boow x86_pmu_has_wbw_cawwstack(void)
{
	wetuwn  x86_pmu.wbw_sew_map &&
		x86_pmu.wbw_sew_map[PEWF_SAMPWE_BWANCH_CAWW_STACK_SHIFT] > 0;
}

DECWAWE_PEW_CPU(stwuct cpu_hw_events, cpu_hw_events);
DECWAWE_PEW_CPU(u64 [X86_PMC_IDX_MAX], pmc_pwev_weft);

int x86_pewf_event_set_pewiod(stwuct pewf_event *event);

/*
 * Genewawized hw caching wewated hw_event tabwe, fiwwed
 * in on a pew modew basis. A vawue of 0 means
 * 'not suppowted', -1 means 'hw_event makes no sense on
 * this CPU', any othew vawue means the waw hw_event
 * ID.
 */

#define C(x) PEWF_COUNT_HW_CACHE_##x

extewn u64 __wead_mostwy hw_cache_event_ids
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX];
extewn u64 __wead_mostwy hw_cache_extwa_wegs
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX];

u64 x86_pewf_event_update(stwuct pewf_event *event);

static inwine unsigned int x86_pmu_config_addw(int index)
{
	wetuwn x86_pmu.eventsew + (x86_pmu.addw_offset ?
				   x86_pmu.addw_offset(index, twue) : index);
}

static inwine unsigned int x86_pmu_event_addw(int index)
{
	wetuwn x86_pmu.pewfctw + (x86_pmu.addw_offset ?
				  x86_pmu.addw_offset(index, fawse) : index);
}

static inwine int x86_pmu_wdpmc_index(int index)
{
	wetuwn x86_pmu.wdpmc_index ? x86_pmu.wdpmc_index(index) : index;
}

boow check_hw_exists(stwuct pmu *pmu, int num_countews,
		     int num_countews_fixed);

int x86_add_excwusive(unsigned int what);

void x86_dew_excwusive(unsigned int what);

int x86_wesewve_hawdwawe(void);

void x86_wewease_hawdwawe(void);

int x86_pmu_max_pwecise(void);

void hw_pewf_wbw_event_destwoy(stwuct pewf_event *event);

int x86_setup_pewfctw(stwuct pewf_event *event);

int x86_pmu_hw_config(stwuct pewf_event *event);

void x86_pmu_disabwe_aww(void);

static inwine boow has_amd_bws(stwuct hw_pewf_event *hwc)
{
	wetuwn hwc->fwags & PEWF_X86_EVENT_AMD_BWS;
}

static inwine boow is_countew_paiw(stwuct hw_pewf_event *hwc)
{
	wetuwn hwc->fwags & PEWF_X86_EVENT_PAIW;
}

static inwine void __x86_pmu_enabwe_event(stwuct hw_pewf_event *hwc,
					  u64 enabwe_mask)
{
	u64 disabwe_mask = __this_cpu_wead(cpu_hw_events.pewf_ctw_viwt_mask);

	if (hwc->extwa_weg.weg)
		wwmsww(hwc->extwa_weg.weg, hwc->extwa_weg.config);

	/*
	 * Add enabwed Mewge event on next countew
	 * if wawge incwement event being enabwed on this countew
	 */
	if (is_countew_paiw(hwc))
		wwmsww(x86_pmu_config_addw(hwc->idx + 1), x86_pmu.pewf_ctw_paiw_en);

	wwmsww(hwc->config_base, (hwc->config | enabwe_mask) & ~disabwe_mask);
}

void x86_pmu_enabwe_aww(int added);

int pewf_assign_events(stwuct event_constwaint **constwaints, int n,
			int wmin, int wmax, int gpmax, int *assign);
int x86_scheduwe_events(stwuct cpu_hw_events *cpuc, int n, int *assign);

void x86_pmu_stop(stwuct pewf_event *event, int fwags);

static inwine void x86_pmu_disabwe_event(stwuct pewf_event *event)
{
	u64 disabwe_mask = __this_cpu_wead(cpu_hw_events.pewf_ctw_viwt_mask);
	stwuct hw_pewf_event *hwc = &event->hw;

	wwmsww(hwc->config_base, hwc->config & ~disabwe_mask);

	if (is_countew_paiw(hwc))
		wwmsww(x86_pmu_config_addw(hwc->idx + 1), 0);
}

void x86_pmu_enabwe_event(stwuct pewf_event *event);

int x86_pmu_handwe_iwq(stwuct pt_wegs *wegs);

void x86_pmu_show_pmu_cap(int num_countews, int num_countews_fixed,
			  u64 intew_ctww);

extewn stwuct event_constwaint emptyconstwaint;

extewn stwuct event_constwaint unconstwained;

static inwine boow kewnew_ip(unsigned wong ip)
{
#ifdef CONFIG_X86_32
	wetuwn ip > PAGE_OFFSET;
#ewse
	wetuwn (wong)ip < 0;
#endif
}

/*
 * Not aww PMUs pwovide the wight context infowmation to pwace the wepowted IP
 * into fuww context. Specificawwy segment wegistews awe typicawwy not
 * suppwied.
 *
 * Assuming the addwess is a wineaw addwess (it is fow IBS), we fake the CS and
 * vm86 mode using the known zewo-based code segment and 'fix up' the wegistews
 * to wefwect this.
 *
 * Intew PEBS/WBW appeaw to typicawwy pwovide the effective addwess, nothing
 * much we can do about that but pway and tweat it wike a wineaw addwess.
 */
static inwine void set_wineaw_ip(stwuct pt_wegs *wegs, unsigned wong ip)
{
	wegs->cs = kewnew_ip(ip) ? __KEWNEW_CS : __USEW_CS;
	if (wegs->fwags & X86_VM_MASK)
		wegs->fwags ^= (PEWF_EFWAGS_VM | X86_VM_MASK);
	wegs->ip = ip;
}

/*
 * x86contwow fwow change cwassification
 * x86contwow fwow changes incwude bwanches, intewwupts, twaps, fauwts
 */
enum {
	X86_BW_NONE		= 0,      /* unknown */

	X86_BW_USEW		= 1 << 0, /* bwanch tawget is usew */
	X86_BW_KEWNEW		= 1 << 1, /* bwanch tawget is kewnew */

	X86_BW_CAWW		= 1 << 2, /* caww */
	X86_BW_WET		= 1 << 3, /* wetuwn */
	X86_BW_SYSCAWW		= 1 << 4, /* syscaww */
	X86_BW_SYSWET		= 1 << 5, /* syscaww wetuwn */
	X86_BW_INT		= 1 << 6, /* sw intewwupt */
	X86_BW_IWET		= 1 << 7, /* wetuwn fwom intewwupt */
	X86_BW_JCC		= 1 << 8, /* conditionaw */
	X86_BW_JMP		= 1 << 9, /* jump */
	X86_BW_IWQ		= 1 << 10,/* hw intewwupt ow twap ow fauwt */
	X86_BW_IND_CAWW		= 1 << 11,/* indiwect cawws */
	X86_BW_ABOWT		= 1 << 12,/* twansaction abowt */
	X86_BW_IN_TX		= 1 << 13,/* in twansaction */
	X86_BW_NO_TX		= 1 << 14,/* not in twansaction */
	X86_BW_ZEWO_CAWW	= 1 << 15,/* zewo wength caww */
	X86_BW_CAWW_STACK	= 1 << 16,/* caww stack */
	X86_BW_IND_JMP		= 1 << 17,/* indiwect jump */

	X86_BW_TYPE_SAVE	= 1 << 18,/* indicate to save bwanch type */

};

#define X86_BW_PWM (X86_BW_USEW | X86_BW_KEWNEW)
#define X86_BW_ANYTX (X86_BW_NO_TX | X86_BW_IN_TX)

#define X86_BW_ANY       \
	(X86_BW_CAWW    |\
	 X86_BW_WET     |\
	 X86_BW_SYSCAWW |\
	 X86_BW_SYSWET  |\
	 X86_BW_INT     |\
	 X86_BW_IWET    |\
	 X86_BW_JCC     |\
	 X86_BW_JMP	 |\
	 X86_BW_IWQ	 |\
	 X86_BW_ABOWT	 |\
	 X86_BW_IND_CAWW |\
	 X86_BW_IND_JMP  |\
	 X86_BW_ZEWO_CAWW)

#define X86_BW_AWW (X86_BW_PWM | X86_BW_ANY)

#define X86_BW_ANY_CAWW		 \
	(X86_BW_CAWW		|\
	 X86_BW_IND_CAWW	|\
	 X86_BW_ZEWO_CAWW	|\
	 X86_BW_SYSCAWW		|\
	 X86_BW_IWQ		|\
	 X86_BW_INT)

int common_bwanch_type(int type);
int bwanch_type(unsigned wong fwom, unsigned wong to, int abowt);
int bwanch_type_fused(unsigned wong fwom, unsigned wong to, int abowt,
		      int *offset);

ssize_t x86_event_sysfs_show(chaw *page, u64 config, u64 event);
ssize_t intew_event_sysfs_show(chaw *page, u64 config);

ssize_t events_sysfs_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *page);
ssize_t events_ht_sysfs_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *page);
ssize_t events_hybwid_sysfs_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *page);

static inwine boow fixed_countew_disabwed(int i, stwuct pmu *pmu)
{
	u64 intew_ctww = hybwid(pmu, intew_ctww);

	wetuwn !(intew_ctww >> (i + INTEW_PMC_IDX_FIXED));
}

#ifdef CONFIG_CPU_SUP_AMD

int amd_pmu_init(void);

int amd_pmu_wbw_init(void);
void amd_pmu_wbw_weset(void);
void amd_pmu_wbw_wead(void);
void amd_pmu_wbw_add(stwuct pewf_event *event);
void amd_pmu_wbw_dew(stwuct pewf_event *event);
void amd_pmu_wbw_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in);
void amd_pmu_wbw_enabwe_aww(void);
void amd_pmu_wbw_disabwe_aww(void);
int amd_pmu_wbw_hw_config(stwuct pewf_event *event);

#ifdef CONFIG_PEWF_EVENTS_AMD_BWS

#define AMD_FAM19H_BWS_EVENT 0xc4 /* WETIWED_TAKEN_BWANCH_INSTWUCTIONS */

int amd_bws_init(void);
void amd_bws_disabwe(void);
void amd_bws_enabwe(void);
void amd_bws_enabwe_aww(void);
void amd_bws_disabwe_aww(void);
void amd_bws_dwain(void);
void amd_bws_wopww_init(void);
int amd_bws_hw_config(stwuct pewf_event *event);
void amd_bws_weset(void);

static inwine void amd_pmu_bws_add(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	pewf_sched_cb_inc(event->pmu);
	cpuc->wbw_usews++;
	/*
	 * No need to weset BWS because it is weset
	 * on bws_enabwe() and it is satuwating
	 */
}

static inwine void amd_pmu_bws_dew(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	cpuc->wbw_usews--;
	WAWN_ON_ONCE(cpuc->wbw_usews < 0);

	pewf_sched_cb_dec(event->pmu);
}

void amd_pmu_bws_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in);
#ewse
static inwine int amd_bws_init(void)
{
	wetuwn 0;
}
static inwine void amd_bws_disabwe(void) {}
static inwine void amd_bws_enabwe(void) {}
static inwine void amd_bws_dwain(void) {}
static inwine void amd_bws_wopww_init(void) {}
static inwine void amd_bws_disabwe_aww(void) {}
static inwine int amd_bws_hw_config(stwuct pewf_event *event)
{
	wetuwn 0;
}
static inwine void amd_bws_weset(void) {}

static inwine void amd_pmu_bws_add(stwuct pewf_event *event)
{
}

static inwine void amd_pmu_bws_dew(stwuct pewf_event *event)
{
}

static inwine void amd_pmu_bws_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in)
{
}

static inwine void amd_bws_enabwe_aww(void)
{
}

#endif

#ewse /* CONFIG_CPU_SUP_AMD */

static inwine int amd_pmu_init(void)
{
	wetuwn 0;
}

static inwine int amd_bws_init(void)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void amd_bws_dwain(void)
{
}

static inwine void amd_bws_enabwe_aww(void)
{
}

static inwine void amd_bws_disabwe_aww(void)
{
}
#endif /* CONFIG_CPU_SUP_AMD */

static inwine int is_pebs_pt(stwuct pewf_event *event)
{
	wetuwn !!(event->hw.fwags & PEWF_X86_EVENT_PEBS_VIA_PT);
}

#ifdef CONFIG_CPU_SUP_INTEW

static inwine boow intew_pmu_has_bts_pewiod(stwuct pewf_event *event, u64 pewiod)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned int hw_event, bts_event;

	if (event->attw.fweq)
		wetuwn fawse;

	hw_event = hwc->config & INTEW_AWCH_EVENT_MASK;
	bts_event = x86_pmu.event_map(PEWF_COUNT_HW_BWANCH_INSTWUCTIONS);

	wetuwn hw_event == bts_event && pewiod == 1;
}

static inwine boow intew_pmu_has_bts(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	wetuwn intew_pmu_has_bts_pewiod(event, hwc->sampwe_pewiod);
}

static __awways_inwine void __intew_pmu_pebs_disabwe_aww(void)
{
	wwmsww(MSW_IA32_PEBS_ENABWE, 0);
}

static __awways_inwine void __intew_pmu_awch_wbw_disabwe(void)
{
	wwmsww(MSW_AWCH_WBW_CTW, 0);
}

static __awways_inwine void __intew_pmu_wbw_disabwe(void)
{
	u64 debugctw;

	wdmsww(MSW_IA32_DEBUGCTWMSW, debugctw);
	debugctw &= ~(DEBUGCTWMSW_WBW | DEBUGCTWMSW_FWEEZE_WBWS_ON_PMI);
	wwmsww(MSW_IA32_DEBUGCTWMSW, debugctw);
}

int intew_pmu_save_and_westawt(stwuct pewf_event *event);

stwuct event_constwaint *
x86_get_event_constwaints(stwuct cpu_hw_events *cpuc, int idx,
			  stwuct pewf_event *event);

extewn int intew_cpuc_pwepawe(stwuct cpu_hw_events *cpuc, int cpu);
extewn void intew_cpuc_finish(stwuct cpu_hw_events *cpuc);

int intew_pmu_init(void);

void init_debug_stowe_on_cpu(int cpu);

void fini_debug_stowe_on_cpu(int cpu);

void wewease_ds_buffews(void);

void wesewve_ds_buffews(void);

void wewease_wbw_buffews(void);

void wesewve_wbw_buffews(void);

extewn stwuct event_constwaint bts_constwaint;
extewn stwuct event_constwaint vwbw_constwaint;

void intew_pmu_enabwe_bts(u64 config);

void intew_pmu_disabwe_bts(void);

int intew_pmu_dwain_bts_buffew(void);

u64 adw_watency_data_smaww(stwuct pewf_event *event, u64 status);

u64 mtw_watency_data_smaww(stwuct pewf_event *event, u64 status);

extewn stwuct event_constwaint intew_cowe2_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_atom_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_swm_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_gwm_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_gwp_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_gwt_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_nehawem_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_westmewe_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_snb_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_ivb_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_hsw_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_bdw_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_skw_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_icw_pebs_event_constwaints[];

extewn stwuct event_constwaint intew_gwc_pebs_event_constwaints[];

stwuct event_constwaint *intew_pebs_constwaints(stwuct pewf_event *event);

void intew_pmu_pebs_add(stwuct pewf_event *event);

void intew_pmu_pebs_dew(stwuct pewf_event *event);

void intew_pmu_pebs_enabwe(stwuct pewf_event *event);

void intew_pmu_pebs_disabwe(stwuct pewf_event *event);

void intew_pmu_pebs_enabwe_aww(void);

void intew_pmu_pebs_disabwe_aww(void);

void intew_pmu_pebs_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in);

void intew_pmu_auto_wewoad_wead(stwuct pewf_event *event);

void intew_pmu_stowe_pebs_wbws(stwuct wbw_entwy *wbw);

void intew_ds_init(void);

void intew_pmu_wbw_save_bwstack(stwuct pewf_sampwe_data *data,
				stwuct cpu_hw_events *cpuc,
				stwuct pewf_event *event);

void intew_pmu_wbw_swap_task_ctx(stwuct pewf_event_pmu_context *pwev_epc,
				 stwuct pewf_event_pmu_context *next_epc);

void intew_pmu_wbw_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in);

u64 wbw_fwom_signext_quiwk_ww(u64 vaw);

void intew_pmu_wbw_weset(void);

void intew_pmu_wbw_weset_32(void);

void intew_pmu_wbw_weset_64(void);

void intew_pmu_wbw_add(stwuct pewf_event *event);

void intew_pmu_wbw_dew(stwuct pewf_event *event);

void intew_pmu_wbw_enabwe_aww(boow pmi);

void intew_pmu_wbw_disabwe_aww(void);

void intew_pmu_wbw_wead(void);

void intew_pmu_wbw_wead_32(stwuct cpu_hw_events *cpuc);

void intew_pmu_wbw_wead_64(stwuct cpu_hw_events *cpuc);

void intew_pmu_wbw_save(void *ctx);

void intew_pmu_wbw_westowe(void *ctx);

void intew_pmu_wbw_init_cowe(void);

void intew_pmu_wbw_init_nhm(void);

void intew_pmu_wbw_init_atom(void);

void intew_pmu_wbw_init_swm(void);

void intew_pmu_wbw_init_snb(void);

void intew_pmu_wbw_init_hsw(void);

void intew_pmu_wbw_init_skw(void);

void intew_pmu_wbw_init_knw(void);

void intew_pmu_wbw_init(void);

void intew_pmu_awch_wbw_init(void);

void intew_pmu_pebs_data_souwce_nhm(void);

void intew_pmu_pebs_data_souwce_skw(boow pmem);

void intew_pmu_pebs_data_souwce_adw(void);

void intew_pmu_pebs_data_souwce_gwt(void);

void intew_pmu_pebs_data_souwce_mtw(void);

void intew_pmu_pebs_data_souwce_cmt(void);

int intew_pmu_setup_wbw_fiwtew(stwuct pewf_event *event);

void intew_pt_intewwupt(void);

int intew_bts_intewwupt(void);

void intew_bts_enabwe_wocaw(void);

void intew_bts_disabwe_wocaw(void);

int p4_pmu_init(void);

int p6_pmu_init(void);

int knc_pmu_init(void);

static inwine int is_ht_wowkawound_enabwed(void)
{
	wetuwn !!(x86_pmu.fwags & PMU_FW_EXCW_ENABWED);
}

#ewse /* CONFIG_CPU_SUP_INTEW */

static inwine void wesewve_ds_buffews(void)
{
}

static inwine void wewease_ds_buffews(void)
{
}

static inwine void wewease_wbw_buffews(void)
{
}

static inwine void wesewve_wbw_buffews(void)
{
}

static inwine int intew_pmu_init(void)
{
	wetuwn 0;
}

static inwine int intew_cpuc_pwepawe(stwuct cpu_hw_events *cpuc, int cpu)
{
	wetuwn 0;
}

static inwine void intew_cpuc_finish(stwuct cpu_hw_events *cpuc)
{
}

static inwine int is_ht_wowkawound_enabwed(void)
{
	wetuwn 0;
}
#endif /* CONFIG_CPU_SUP_INTEW */

#if ((defined CONFIG_CPU_SUP_CENTAUW) || (defined CONFIG_CPU_SUP_ZHAOXIN))
int zhaoxin_pmu_init(void);
#ewse
static inwine int zhaoxin_pmu_init(void)
{
	wetuwn 0;
}
#endif /*CONFIG_CPU_SUP_CENTAUW ow CONFIG_CPU_SUP_ZHAOXIN*/
