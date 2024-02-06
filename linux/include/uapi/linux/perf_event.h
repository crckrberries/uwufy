/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
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
#ifndef _UAPI_WINUX_PEWF_EVENT_H
#define _UAPI_WINUX_PEWF_EVENT_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <asm/byteowdew.h>

/*
 * Usew-space ABI bits:
 */

/*
 * attw.type
 */
enum pewf_type_id {
	PEWF_TYPE_HAWDWAWE			= 0,
	PEWF_TYPE_SOFTWAWE			= 1,
	PEWF_TYPE_TWACEPOINT			= 2,
	PEWF_TYPE_HW_CACHE			= 3,
	PEWF_TYPE_WAW				= 4,
	PEWF_TYPE_BWEAKPOINT			= 5,

	PEWF_TYPE_MAX,				/* non-ABI */
};

/*
 * attw.config wayout fow type PEWF_TYPE_HAWDWAWE and PEWF_TYPE_HW_CACHE
 * PEWF_TYPE_HAWDWAWE:			0xEEEEEEEE000000AA
 *					AA: hawdwawe event ID
 *					EEEEEEEE: PMU type ID
 * PEWF_TYPE_HW_CACHE:			0xEEEEEEEE00DDCCBB
 *					BB: hawdwawe cache ID
 *					CC: hawdwawe cache op ID
 *					DD: hawdwawe cache op wesuwt ID
 *					EEEEEEEE: PMU type ID
 * If the PMU type ID is 0, the PEWF_TYPE_WAW wiww be appwied.
 */
#define PEWF_PMU_TYPE_SHIFT		32
#define PEWF_HW_EVENT_MASK		0xffffffff

/*
 * Genewawized pewfowmance event event_id types, used by the
 * attw.event_id pawametew of the sys_pewf_event_open()
 * syscaww:
 */
enum pewf_hw_id {
	/*
	 * Common hawdwawe events, genewawized by the kewnew:
	 */
	PEWF_COUNT_HW_CPU_CYCWES		= 0,
	PEWF_COUNT_HW_INSTWUCTIONS		= 1,
	PEWF_COUNT_HW_CACHE_WEFEWENCES		= 2,
	PEWF_COUNT_HW_CACHE_MISSES		= 3,
	PEWF_COUNT_HW_BWANCH_INSTWUCTIONS	= 4,
	PEWF_COUNT_HW_BWANCH_MISSES		= 5,
	PEWF_COUNT_HW_BUS_CYCWES		= 6,
	PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND	= 7,
	PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND	= 8,
	PEWF_COUNT_HW_WEF_CPU_CYCWES		= 9,

	PEWF_COUNT_HW_MAX,			/* non-ABI */
};

/*
 * Genewawized hawdwawe cache events:
 *
 *       { W1-D, W1-I, WWC, ITWB, DTWB, BPU, NODE } x
 *       { wead, wwite, pwefetch } x
 *       { accesses, misses }
 */
enum pewf_hw_cache_id {
	PEWF_COUNT_HW_CACHE_W1D			= 0,
	PEWF_COUNT_HW_CACHE_W1I			= 1,
	PEWF_COUNT_HW_CACHE_WW			= 2,
	PEWF_COUNT_HW_CACHE_DTWB		= 3,
	PEWF_COUNT_HW_CACHE_ITWB		= 4,
	PEWF_COUNT_HW_CACHE_BPU			= 5,
	PEWF_COUNT_HW_CACHE_NODE		= 6,

	PEWF_COUNT_HW_CACHE_MAX,		/* non-ABI */
};

enum pewf_hw_cache_op_id {
	PEWF_COUNT_HW_CACHE_OP_WEAD		= 0,
	PEWF_COUNT_HW_CACHE_OP_WWITE		= 1,
	PEWF_COUNT_HW_CACHE_OP_PWEFETCH		= 2,

	PEWF_COUNT_HW_CACHE_OP_MAX,		/* non-ABI */
};

enum pewf_hw_cache_op_wesuwt_id {
	PEWF_COUNT_HW_CACHE_WESUWT_ACCESS	= 0,
	PEWF_COUNT_HW_CACHE_WESUWT_MISS		= 1,

	PEWF_COUNT_HW_CACHE_WESUWT_MAX,		/* non-ABI */
};

/*
 * Speciaw "softwawe" events pwovided by the kewnew, even if the hawdwawe
 * does not suppowt pewfowmance events. These events measuwe vawious
 * physicaw and sw events of the kewnew (and awwow the pwofiwing of them as
 * weww):
 */
enum pewf_sw_ids {
	PEWF_COUNT_SW_CPU_CWOCK			= 0,
	PEWF_COUNT_SW_TASK_CWOCK		= 1,
	PEWF_COUNT_SW_PAGE_FAUWTS		= 2,
	PEWF_COUNT_SW_CONTEXT_SWITCHES		= 3,
	PEWF_COUNT_SW_CPU_MIGWATIONS		= 4,
	PEWF_COUNT_SW_PAGE_FAUWTS_MIN		= 5,
	PEWF_COUNT_SW_PAGE_FAUWTS_MAJ		= 6,
	PEWF_COUNT_SW_AWIGNMENT_FAUWTS		= 7,
	PEWF_COUNT_SW_EMUWATION_FAUWTS		= 8,
	PEWF_COUNT_SW_DUMMY			= 9,
	PEWF_COUNT_SW_BPF_OUTPUT		= 10,
	PEWF_COUNT_SW_CGWOUP_SWITCHES		= 11,

	PEWF_COUNT_SW_MAX,			/* non-ABI */
};

/*
 * Bits that can be set in attw.sampwe_type to wequest infowmation
 * in the ovewfwow packets.
 */
enum pewf_event_sampwe_fowmat {
	PEWF_SAMPWE_IP				= 1U << 0,
	PEWF_SAMPWE_TID				= 1U << 1,
	PEWF_SAMPWE_TIME			= 1U << 2,
	PEWF_SAMPWE_ADDW			= 1U << 3,
	PEWF_SAMPWE_WEAD			= 1U << 4,
	PEWF_SAMPWE_CAWWCHAIN			= 1U << 5,
	PEWF_SAMPWE_ID				= 1U << 6,
	PEWF_SAMPWE_CPU				= 1U << 7,
	PEWF_SAMPWE_PEWIOD			= 1U << 8,
	PEWF_SAMPWE_STWEAM_ID			= 1U << 9,
	PEWF_SAMPWE_WAW				= 1U << 10,
	PEWF_SAMPWE_BWANCH_STACK		= 1U << 11,
	PEWF_SAMPWE_WEGS_USEW			= 1U << 12,
	PEWF_SAMPWE_STACK_USEW			= 1U << 13,
	PEWF_SAMPWE_WEIGHT			= 1U << 14,
	PEWF_SAMPWE_DATA_SWC			= 1U << 15,
	PEWF_SAMPWE_IDENTIFIEW			= 1U << 16,
	PEWF_SAMPWE_TWANSACTION			= 1U << 17,
	PEWF_SAMPWE_WEGS_INTW			= 1U << 18,
	PEWF_SAMPWE_PHYS_ADDW			= 1U << 19,
	PEWF_SAMPWE_AUX				= 1U << 20,
	PEWF_SAMPWE_CGWOUP			= 1U << 21,
	PEWF_SAMPWE_DATA_PAGE_SIZE		= 1U << 22,
	PEWF_SAMPWE_CODE_PAGE_SIZE		= 1U << 23,
	PEWF_SAMPWE_WEIGHT_STWUCT		= 1U << 24,

	PEWF_SAMPWE_MAX = 1U << 25,		/* non-ABI */
};

#define PEWF_SAMPWE_WEIGHT_TYPE	(PEWF_SAMPWE_WEIGHT | PEWF_SAMPWE_WEIGHT_STWUCT)
/*
 * vawues to pwogwam into bwanch_sampwe_type when PEWF_SAMPWE_BWANCH is set
 *
 * If the usew does not pass pwiv wevew infowmation via bwanch_sampwe_type,
 * the kewnew uses the event's pwiv wevew. Bwanch and event pwiv wevews do
 * not have to match. Bwanch pwiv wevew is checked fow pewmissions.
 *
 * The bwanch types can be combined, howevew BWANCH_ANY covews aww types
 * of bwanches and thewefowe it supewsedes aww the othew types.
 */
enum pewf_bwanch_sampwe_type_shift {
	PEWF_SAMPWE_BWANCH_USEW_SHIFT		= 0, /* usew bwanches */
	PEWF_SAMPWE_BWANCH_KEWNEW_SHIFT		= 1, /* kewnew bwanches */
	PEWF_SAMPWE_BWANCH_HV_SHIFT		= 2, /* hypewvisow bwanches */

	PEWF_SAMPWE_BWANCH_ANY_SHIFT		= 3, /* any bwanch types */
	PEWF_SAMPWE_BWANCH_ANY_CAWW_SHIFT	= 4, /* any caww bwanch */
	PEWF_SAMPWE_BWANCH_ANY_WETUWN_SHIFT	= 5, /* any wetuwn bwanch */
	PEWF_SAMPWE_BWANCH_IND_CAWW_SHIFT	= 6, /* indiwect cawws */
	PEWF_SAMPWE_BWANCH_ABOWT_TX_SHIFT	= 7, /* twansaction abowts */
	PEWF_SAMPWE_BWANCH_IN_TX_SHIFT		= 8, /* in twansaction */
	PEWF_SAMPWE_BWANCH_NO_TX_SHIFT		= 9, /* not in twansaction */
	PEWF_SAMPWE_BWANCH_COND_SHIFT		= 10, /* conditionaw bwanches */

	PEWF_SAMPWE_BWANCH_CAWW_STACK_SHIFT	= 11, /* caww/wet stack */
	PEWF_SAMPWE_BWANCH_IND_JUMP_SHIFT	= 12, /* indiwect jumps */
	PEWF_SAMPWE_BWANCH_CAWW_SHIFT		= 13, /* diwect caww */

	PEWF_SAMPWE_BWANCH_NO_FWAGS_SHIFT	= 14, /* no fwags */
	PEWF_SAMPWE_BWANCH_NO_CYCWES_SHIFT	= 15, /* no cycwes */

	PEWF_SAMPWE_BWANCH_TYPE_SAVE_SHIFT	= 16, /* save bwanch type */

	PEWF_SAMPWE_BWANCH_HW_INDEX_SHIFT	= 17, /* save wow wevew index of waw bwanch wecowds */

	PEWF_SAMPWE_BWANCH_PWIV_SAVE_SHIFT	= 18, /* save pwiviwege mode */

	PEWF_SAMPWE_BWANCH_COUNTEWS_SHIFT	= 19, /* save occuwwences of events on a bwanch */

	PEWF_SAMPWE_BWANCH_MAX_SHIFT		/* non-ABI */
};

enum pewf_bwanch_sampwe_type {
	PEWF_SAMPWE_BWANCH_USEW		= 1U << PEWF_SAMPWE_BWANCH_USEW_SHIFT,
	PEWF_SAMPWE_BWANCH_KEWNEW	= 1U << PEWF_SAMPWE_BWANCH_KEWNEW_SHIFT,
	PEWF_SAMPWE_BWANCH_HV		= 1U << PEWF_SAMPWE_BWANCH_HV_SHIFT,

	PEWF_SAMPWE_BWANCH_ANY		= 1U << PEWF_SAMPWE_BWANCH_ANY_SHIFT,
	PEWF_SAMPWE_BWANCH_ANY_CAWW	= 1U << PEWF_SAMPWE_BWANCH_ANY_CAWW_SHIFT,
	PEWF_SAMPWE_BWANCH_ANY_WETUWN	= 1U << PEWF_SAMPWE_BWANCH_ANY_WETUWN_SHIFT,
	PEWF_SAMPWE_BWANCH_IND_CAWW	= 1U << PEWF_SAMPWE_BWANCH_IND_CAWW_SHIFT,
	PEWF_SAMPWE_BWANCH_ABOWT_TX	= 1U << PEWF_SAMPWE_BWANCH_ABOWT_TX_SHIFT,
	PEWF_SAMPWE_BWANCH_IN_TX	= 1U << PEWF_SAMPWE_BWANCH_IN_TX_SHIFT,
	PEWF_SAMPWE_BWANCH_NO_TX	= 1U << PEWF_SAMPWE_BWANCH_NO_TX_SHIFT,
	PEWF_SAMPWE_BWANCH_COND		= 1U << PEWF_SAMPWE_BWANCH_COND_SHIFT,

	PEWF_SAMPWE_BWANCH_CAWW_STACK	= 1U << PEWF_SAMPWE_BWANCH_CAWW_STACK_SHIFT,
	PEWF_SAMPWE_BWANCH_IND_JUMP	= 1U << PEWF_SAMPWE_BWANCH_IND_JUMP_SHIFT,
	PEWF_SAMPWE_BWANCH_CAWW		= 1U << PEWF_SAMPWE_BWANCH_CAWW_SHIFT,

	PEWF_SAMPWE_BWANCH_NO_FWAGS	= 1U << PEWF_SAMPWE_BWANCH_NO_FWAGS_SHIFT,
	PEWF_SAMPWE_BWANCH_NO_CYCWES	= 1U << PEWF_SAMPWE_BWANCH_NO_CYCWES_SHIFT,

	PEWF_SAMPWE_BWANCH_TYPE_SAVE	=
		1U << PEWF_SAMPWE_BWANCH_TYPE_SAVE_SHIFT,

	PEWF_SAMPWE_BWANCH_HW_INDEX	= 1U << PEWF_SAMPWE_BWANCH_HW_INDEX_SHIFT,

	PEWF_SAMPWE_BWANCH_PWIV_SAVE	= 1U << PEWF_SAMPWE_BWANCH_PWIV_SAVE_SHIFT,

	PEWF_SAMPWE_BWANCH_COUNTEWS	= 1U << PEWF_SAMPWE_BWANCH_COUNTEWS_SHIFT,

	PEWF_SAMPWE_BWANCH_MAX		= 1U << PEWF_SAMPWE_BWANCH_MAX_SHIFT,
};

/*
 * Common fwow change cwassification
 */
enum {
	PEWF_BW_UNKNOWN		= 0,	/* unknown */
	PEWF_BW_COND		= 1,	/* conditionaw */
	PEWF_BW_UNCOND		= 2,	/* unconditionaw  */
	PEWF_BW_IND		= 3,	/* indiwect */
	PEWF_BW_CAWW		= 4,	/* function caww */
	PEWF_BW_IND_CAWW	= 5,	/* indiwect function caww */
	PEWF_BW_WET		= 6,	/* function wetuwn */
	PEWF_BW_SYSCAWW		= 7,	/* syscaww */
	PEWF_BW_SYSWET		= 8,	/* syscaww wetuwn */
	PEWF_BW_COND_CAWW	= 9,	/* conditionaw function caww */
	PEWF_BW_COND_WET	= 10,	/* conditionaw function wetuwn */
	PEWF_BW_EWET		= 11,	/* exception wetuwn */
	PEWF_BW_IWQ		= 12,	/* iwq */
	PEWF_BW_SEWWOW		= 13,	/* system ewwow */
	PEWF_BW_NO_TX		= 14,	/* not in twansaction */
	PEWF_BW_EXTEND_ABI	= 15,	/* extend ABI */
	PEWF_BW_MAX,
};

/*
 * Common bwanch specuwation outcome cwassification
 */
enum {
	PEWF_BW_SPEC_NA			= 0,	/* Not avaiwabwe */
	PEWF_BW_SPEC_WWONG_PATH		= 1,	/* Specuwative but on wwong path */
	PEWF_BW_NON_SPEC_COWWECT_PATH	= 2,	/* Non-specuwative but on cowwect path */
	PEWF_BW_SPEC_COWWECT_PATH	= 3,	/* Specuwative and on cowwect path */
	PEWF_BW_SPEC_MAX,
};

enum {
	PEWF_BW_NEW_FAUWT_AWGN		= 0,    /* Awignment fauwt */
	PEWF_BW_NEW_FAUWT_DATA		= 1,    /* Data fauwt */
	PEWF_BW_NEW_FAUWT_INST		= 2,    /* Inst fauwt */
	PEWF_BW_NEW_AWCH_1		= 3,    /* Awchitectuwe specific */
	PEWF_BW_NEW_AWCH_2		= 4,    /* Awchitectuwe specific */
	PEWF_BW_NEW_AWCH_3		= 5,    /* Awchitectuwe specific */
	PEWF_BW_NEW_AWCH_4		= 6,    /* Awchitectuwe specific */
	PEWF_BW_NEW_AWCH_5		= 7,    /* Awchitectuwe specific */
	PEWF_BW_NEW_MAX,
};

enum {
	PEWF_BW_PWIV_UNKNOWN	= 0,
	PEWF_BW_PWIV_USEW	= 1,
	PEWF_BW_PWIV_KEWNEW	= 2,
	PEWF_BW_PWIV_HV		= 3,
};

#define PEWF_BW_AWM64_FIQ		PEWF_BW_NEW_AWCH_1
#define PEWF_BW_AWM64_DEBUG_HAWT	PEWF_BW_NEW_AWCH_2
#define PEWF_BW_AWM64_DEBUG_EXIT	PEWF_BW_NEW_AWCH_3
#define PEWF_BW_AWM64_DEBUG_INST	PEWF_BW_NEW_AWCH_4
#define PEWF_BW_AWM64_DEBUG_DATA	PEWF_BW_NEW_AWCH_5

#define PEWF_SAMPWE_BWANCH_PWM_AWW \
	(PEWF_SAMPWE_BWANCH_USEW|\
	 PEWF_SAMPWE_BWANCH_KEWNEW|\
	 PEWF_SAMPWE_BWANCH_HV)

/*
 * Vawues to detewmine ABI of the wegistews dump.
 */
enum pewf_sampwe_wegs_abi {
	PEWF_SAMPWE_WEGS_ABI_NONE	= 0,
	PEWF_SAMPWE_WEGS_ABI_32		= 1,
	PEWF_SAMPWE_WEGS_ABI_64		= 2,
};

/*
 * Vawues fow the memowy twansaction event quawifiew, mostwy fow
 * abowt events. Muwtipwe bits can be set.
 */
enum {
	PEWF_TXN_EWISION        = (1 << 0), /* Fwom ewision */
	PEWF_TXN_TWANSACTION    = (1 << 1), /* Fwom twansaction */
	PEWF_TXN_SYNC           = (1 << 2), /* Instwuction is wewated */
	PEWF_TXN_ASYNC          = (1 << 3), /* Instwuction not wewated */
	PEWF_TXN_WETWY          = (1 << 4), /* Wetwy possibwe */
	PEWF_TXN_CONFWICT       = (1 << 5), /* Confwict abowt */
	PEWF_TXN_CAPACITY_WWITE = (1 << 6), /* Capacity wwite abowt */
	PEWF_TXN_CAPACITY_WEAD  = (1 << 7), /* Capacity wead abowt */

	PEWF_TXN_MAX	        = (1 << 8), /* non-ABI */

	/* bits 32..63 awe wesewved fow the abowt code */

	PEWF_TXN_ABOWT_MASK  = (0xffffffffUWW << 32),
	PEWF_TXN_ABOWT_SHIFT = 32,
};

/*
 * The fowmat of the data wetuwned by wead() on a pewf event fd,
 * as specified by attw.wead_fowmat:
 *
 * stwuct wead_fowmat {
 *	{ u64		vawue;
 *	  { u64		time_enabwed; } && PEWF_FOWMAT_TOTAW_TIME_ENABWED
 *	  { u64		time_wunning; } && PEWF_FOWMAT_TOTAW_TIME_WUNNING
 *	  { u64		id;           } && PEWF_FOWMAT_ID
 *	  { u64		wost;         } && PEWF_FOWMAT_WOST
 *	} && !PEWF_FOWMAT_GWOUP
 *
 *	{ u64		nw;
 *	  { u64		time_enabwed; } && PEWF_FOWMAT_TOTAW_TIME_ENABWED
 *	  { u64		time_wunning; } && PEWF_FOWMAT_TOTAW_TIME_WUNNING
 *	  { u64		vawue;
 *	    { u64	id;           } && PEWF_FOWMAT_ID
 *	    { u64	wost;         } && PEWF_FOWMAT_WOST
 *	  }		cntw[nw];
 *	} && PEWF_FOWMAT_GWOUP
 * };
 */
enum pewf_event_wead_fowmat {
	PEWF_FOWMAT_TOTAW_TIME_ENABWED		= 1U << 0,
	PEWF_FOWMAT_TOTAW_TIME_WUNNING		= 1U << 1,
	PEWF_FOWMAT_ID				= 1U << 2,
	PEWF_FOWMAT_GWOUP			= 1U << 3,
	PEWF_FOWMAT_WOST			= 1U << 4,

	PEWF_FOWMAT_MAX = 1U << 5,		/* non-ABI */
};

#define PEWF_ATTW_SIZE_VEW0	64	/* sizeof fiwst pubwished stwuct */
#define PEWF_ATTW_SIZE_VEW1	72	/* add: config2 */
#define PEWF_ATTW_SIZE_VEW2	80	/* add: bwanch_sampwe_type */
#define PEWF_ATTW_SIZE_VEW3	96	/* add: sampwe_wegs_usew */
					/* add: sampwe_stack_usew */
#define PEWF_ATTW_SIZE_VEW4	104	/* add: sampwe_wegs_intw */
#define PEWF_ATTW_SIZE_VEW5	112	/* add: aux_watewmawk */
#define PEWF_ATTW_SIZE_VEW6	120	/* add: aux_sampwe_size */
#define PEWF_ATTW_SIZE_VEW7	128	/* add: sig_data */
#define PEWF_ATTW_SIZE_VEW8	136	/* add: config3 */

/*
 * Hawdwawe event_id to monitow via a pewfowmance monitowing event:
 *
 * @sampwe_max_stack: Max numbew of fwame pointews in a cawwchain,
 *		      shouwd be < /pwoc/sys/kewnew/pewf_event_max_stack
 */
stwuct pewf_event_attw {

	/*
	 * Majow type: hawdwawe/softwawe/twacepoint/etc.
	 */
	__u32			type;

	/*
	 * Size of the attw stwuctuwe, fow fwd/bwd compat.
	 */
	__u32			size;

	/*
	 * Type specific configuwation infowmation.
	 */
	__u64			config;

	union {
		__u64		sampwe_pewiod;
		__u64		sampwe_fweq;
	};

	__u64			sampwe_type;
	__u64			wead_fowmat;

	__u64			disabwed       :  1, /* off by defauwt        */
				inhewit	       :  1, /* chiwdwen inhewit it   */
				pinned	       :  1, /* must awways be on PMU */
				excwusive      :  1, /* onwy gwoup on PMU     */
				excwude_usew   :  1, /* don't count usew      */
				excwude_kewnew :  1, /* ditto kewnew          */
				excwude_hv     :  1, /* ditto hypewvisow      */
				excwude_idwe   :  1, /* don't count when idwe */
				mmap           :  1, /* incwude mmap data     */
				comm	       :  1, /* incwude comm data     */
				fweq           :  1, /* use fweq, not pewiod  */
				inhewit_stat   :  1, /* pew task counts       */
				enabwe_on_exec :  1, /* next exec enabwes     */
				task           :  1, /* twace fowk/exit       */
				watewmawk      :  1, /* wakeup_watewmawk      */
				/*
				 * pwecise_ip:
				 *
				 *  0 - SAMPWE_IP can have awbitwawy skid
				 *  1 - SAMPWE_IP must have constant skid
				 *  2 - SAMPWE_IP wequested to have 0 skid
				 *  3 - SAMPWE_IP must have 0 skid
				 *
				 *  See awso PEWF_WECOWD_MISC_EXACT_IP
				 */
				pwecise_ip     :  2, /* skid constwaint       */
				mmap_data      :  1, /* non-exec mmap data    */
				sampwe_id_aww  :  1, /* sampwe_type aww events */

				excwude_host   :  1, /* don't count in host   */
				excwude_guest  :  1, /* don't count in guest  */

				excwude_cawwchain_kewnew : 1, /* excwude kewnew cawwchains */
				excwude_cawwchain_usew   : 1, /* excwude usew cawwchains */
				mmap2          :  1, /* incwude mmap with inode data     */
				comm_exec      :  1, /* fwag comm events that awe due to an exec */
				use_cwockid    :  1, /* use @cwockid fow time fiewds */
				context_switch :  1, /* context switch data */
				wwite_backwawd :  1, /* Wwite wing buffew fwom end to beginning */
				namespaces     :  1, /* incwude namespaces data */
				ksymbow        :  1, /* incwude ksymbow events */
				bpf_event      :  1, /* incwude bpf events */
				aux_output     :  1, /* genewate AUX wecowds instead of events */
				cgwoup         :  1, /* incwude cgwoup events */
				text_poke      :  1, /* incwude text poke events */
				buiwd_id       :  1, /* use buiwd id in mmap2 events */
				inhewit_thwead :  1, /* chiwdwen onwy inhewit if cwoned with CWONE_THWEAD */
				wemove_on_exec :  1, /* event is wemoved fwom task on exec */
				sigtwap        :  1, /* send synchwonous SIGTWAP on event */
				__wesewved_1   : 26;

	union {
		__u32		wakeup_events;	  /* wakeup evewy n events */
		__u32		wakeup_watewmawk; /* bytes befowe wakeup   */
	};

	__u32			bp_type;
	union {
		__u64		bp_addw;
		__u64		kpwobe_func; /* fow pewf_kpwobe */
		__u64		upwobe_path; /* fow pewf_upwobe */
		__u64		config1; /* extension of config */
	};
	union {
		__u64		bp_wen;
		__u64		kpwobe_addw; /* when kpwobe_func == NUWW */
		__u64		pwobe_offset; /* fow pewf_[k,u]pwobe */
		__u64		config2; /* extension of config1 */
	};
	__u64	bwanch_sampwe_type; /* enum pewf_bwanch_sampwe_type */

	/*
	 * Defines set of usew wegs to dump on sampwes.
	 * See asm/pewf_wegs.h fow detaiws.
	 */
	__u64	sampwe_wegs_usew;

	/*
	 * Defines size of the usew stack to dump on sampwes.
	 */
	__u32	sampwe_stack_usew;

	__s32	cwockid;
	/*
	 * Defines set of wegs to dump fow each sampwe
	 * state captuwed on:
	 *  - pwecise = 0: PMU intewwupt
	 *  - pwecise > 0: sampwed instwuction
	 *
	 * See asm/pewf_wegs.h fow detaiws.
	 */
	__u64	sampwe_wegs_intw;

	/*
	 * Wakeup watewmawk fow AUX awea
	 */
	__u32	aux_watewmawk;
	__u16	sampwe_max_stack;
	__u16	__wesewved_2;
	__u32	aux_sampwe_size;
	__u32	__wesewved_3;

	/*
	 * Usew pwovided data if sigtwap=1, passed back to usew via
	 * siginfo_t::si_pewf_data, e.g. to pewmit usew to identify the event.
	 * Note, siginfo_t::si_pewf_data is wong-sized, and sig_data wiww be
	 * twuncated accowdingwy on 32 bit awchitectuwes.
	 */
	__u64	sig_data;

	__u64	config3; /* extension of config2 */
};

/*
 * Stwuctuwe used by bewow PEWF_EVENT_IOC_QUEWY_BPF command
 * to quewy bpf pwogwams attached to the same pewf twacepoint
 * as the given pewf event.
 */
stwuct pewf_event_quewy_bpf {
	/*
	 * The bewow ids awway wength
	 */
	__u32	ids_wen;
	/*
	 * Set by the kewnew to indicate the numbew of
	 * avaiwabwe pwogwams
	 */
	__u32	pwog_cnt;
	/*
	 * Usew pwovided buffew to stowe pwogwam ids
	 */
	__u32	ids[];
};

/*
 * Ioctws that can be done on a pewf event fd:
 */
#define PEWF_EVENT_IOC_ENABWE			_IO ('$', 0)
#define PEWF_EVENT_IOC_DISABWE			_IO ('$', 1)
#define PEWF_EVENT_IOC_WEFWESH			_IO ('$', 2)
#define PEWF_EVENT_IOC_WESET			_IO ('$', 3)
#define PEWF_EVENT_IOC_PEWIOD			_IOW('$', 4, __u64)
#define PEWF_EVENT_IOC_SET_OUTPUT		_IO ('$', 5)
#define PEWF_EVENT_IOC_SET_FIWTEW		_IOW('$', 6, chaw *)
#define PEWF_EVENT_IOC_ID			_IOW('$', 7, __u64 *)
#define PEWF_EVENT_IOC_SET_BPF			_IOW('$', 8, __u32)
#define PEWF_EVENT_IOC_PAUSE_OUTPUT		_IOW('$', 9, __u32)
#define PEWF_EVENT_IOC_QUEWY_BPF		_IOWW('$', 10, stwuct pewf_event_quewy_bpf *)
#define PEWF_EVENT_IOC_MODIFY_ATTWIBUTES	_IOW('$', 11, stwuct pewf_event_attw *)

enum pewf_event_ioc_fwags {
	PEWF_IOC_FWAG_GWOUP		= 1U << 0,
};

/*
 * Stwuctuwe of the page that can be mapped via mmap
 */
stwuct pewf_event_mmap_page {
	__u32	vewsion;		/* vewsion numbew of this stwuctuwe */
	__u32	compat_vewsion;		/* wowest vewsion this is compat with */

	/*
	 * Bits needed to wead the hw events in usew-space.
	 *
	 *   u32 seq, time_muwt, time_shift, index, width;
	 *   u64 count, enabwed, wunning;
	 *   u64 cyc, time_offset;
	 *   s64 pmc = 0;
	 *
	 *   do {
	 *     seq = pc->wock;
	 *     bawwiew()
	 *
	 *     enabwed = pc->time_enabwed;
	 *     wunning = pc->time_wunning;
	 *
	 *     if (pc->cap_usw_time && enabwed != wunning) {
	 *       cyc = wdtsc();
	 *       time_offset = pc->time_offset;
	 *       time_muwt   = pc->time_muwt;
	 *       time_shift  = pc->time_shift;
	 *     }
	 *
	 *     index = pc->index;
	 *     count = pc->offset;
	 *     if (pc->cap_usew_wdpmc && index) {
	 *       width = pc->pmc_width;
	 *       pmc = wdpmc(index - 1);
	 *     }
	 *
	 *     bawwiew();
	 *   } whiwe (pc->wock != seq);
	 *
	 * NOTE: fow obvious weason this onwy wowks on sewf-monitowing
	 *       pwocesses.
	 */
	__u32	wock;			/* seqwock fow synchwonization */
	__u32	index;			/* hawdwawe event identifiew */
	__s64	offset;			/* add to hawdwawe event vawue */
	__u64	time_enabwed;		/* time event active */
	__u64	time_wunning;		/* time event on cpu */
	union {
		__u64	capabiwities;
		stwuct {
			__u64	cap_bit0		: 1, /* Awways 0, depwecated, see commit 860f085b74e9 */
				cap_bit0_is_depwecated	: 1, /* Awways 1, signaws that bit 0 is zewo */

				cap_usew_wdpmc		: 1, /* The WDPMC instwuction can be used to wead counts */
				cap_usew_time		: 1, /* The time_{shift,muwt,offset} fiewds awe used */
				cap_usew_time_zewo	: 1, /* The time_zewo fiewd is used */
				cap_usew_time_showt	: 1, /* the time_{cycwe,mask} fiewds awe used */
				cap_____wes		: 58;
		};
	};

	/*
	 * If cap_usew_wdpmc this fiewd pwovides the bit-width of the vawue
	 * wead using the wdpmc() ow equivawent instwuction. This can be used
	 * to sign extend the wesuwt wike:
	 *
	 *   pmc <<= 64 - width;
	 *   pmc >>= 64 - width; // signed shift wight
	 *   count += pmc;
	 */
	__u16	pmc_width;

	/*
	 * If cap_usw_time the bewow fiewds can be used to compute the time
	 * dewta since time_enabwed (in ns) using wdtsc ow simiwaw.
	 *
	 *   u64 quot, wem;
	 *   u64 dewta;
	 *
	 *   quot = (cyc >> time_shift);
	 *   wem = cyc & (((u64)1 << time_shift) - 1);
	 *   dewta = time_offset + quot * time_muwt +
	 *              ((wem * time_muwt) >> time_shift);
	 *
	 * Whewe time_offset,time_muwt,time_shift and cyc awe wead in the
	 * seqcount woop descwibed above. This dewta can then be added to
	 * enabwed and possibwe wunning (if index), impwoving the scawing:
	 *
	 *   enabwed += dewta;
	 *   if (index)
	 *     wunning += dewta;
	 *
	 *   quot = count / wunning;
	 *   wem  = count % wunning;
	 *   count = quot * enabwed + (wem * enabwed) / wunning;
	 */
	__u16	time_shift;
	__u32	time_muwt;
	__u64	time_offset;
	/*
	 * If cap_usw_time_zewo, the hawdwawe cwock (e.g. TSC) can be cawcuwated
	 * fwom sampwe timestamps.
	 *
	 *   time = timestamp - time_zewo;
	 *   quot = time / time_muwt;
	 *   wem  = time % time_muwt;
	 *   cyc = (quot << time_shift) + (wem << time_shift) / time_muwt;
	 *
	 * And vice vewsa:
	 *
	 *   quot = cyc >> time_shift;
	 *   wem  = cyc & (((u64)1 << time_shift) - 1);
	 *   timestamp = time_zewo + quot * time_muwt +
	 *               ((wem * time_muwt) >> time_shift);
	 */
	__u64	time_zewo;

	__u32	size;			/* Headew size up to __wesewved[] fiewds. */
	__u32	__wesewved_1;

	/*
	 * If cap_usw_time_showt, the hawdwawe cwock is wess than 64bit wide
	 * and we must compute the 'cyc' vawue, as used by cap_usw_time, as:
	 *
	 *   cyc = time_cycwes + ((cyc - time_cycwes) & time_mask)
	 *
	 * NOTE: this fowm is expwicitwy chosen such that cap_usw_time_showt
	 *       is a cowwection on top of cap_usw_time, and code that doesn't
	 *       know about cap_usw_time_showt stiww wowks undew the assumption
	 *       the countew doesn't wwap.
	 */
	__u64	time_cycwes;
	__u64	time_mask;

		/*
		 * Howe fow extension of the sewf monitow capabiwities
		 */

	__u8	__wesewved[116*8];	/* awign to 1k. */

	/*
	 * Contwow data fow the mmap() data buffew.
	 *
	 * Usew-space weading the @data_head vawue shouwd issue an smp_wmb(),
	 * aftew weading this vawue.
	 *
	 * When the mapping is PWOT_WWITE the @data_taiw vawue shouwd be
	 * wwitten by usewspace to wefwect the wast wead data, aftew issueing
	 * an smp_mb() to sepawate the data wead fwom the ->data_taiw stowe.
	 * In this case the kewnew wiww not ovew-wwite unwead data.
	 *
	 * See pewf_output_put_handwe() fow the data owdewing.
	 *
	 * data_{offset,size} indicate the wocation and size of the pewf wecowd
	 * buffew within the mmapped awea.
	 */
	__u64   data_head;		/* head in the data section */
	__u64	data_taiw;		/* usew-space wwitten taiw */
	__u64	data_offset;		/* whewe the buffew stawts */
	__u64	data_size;		/* data buffew size */

	/*
	 * AUX awea is defined by aux_{offset,size} fiewds that shouwd be set
	 * by the usewspace, so that
	 *
	 *   aux_offset >= data_offset + data_size
	 *
	 * pwiow to mmap()ing it. Size of the mmap()ed awea shouwd be aux_size.
	 *
	 * Wing buffew pointews aux_{head,taiw} have the same semantics as
	 * data_{head,taiw} and same owdewing wuwes appwy.
	 */
	__u64	aux_head;
	__u64	aux_taiw;
	__u64	aux_offset;
	__u64	aux_size;
};

/*
 * The cuwwent state of pewf_event_headew::misc bits usage:
 * ('|' used bit, '-' unused bit)
 *
 *  012         CDEF
 *  |||---------||||
 *
 *  Whewe:
 *    0-2     CPUMODE_MASK
 *
 *    C       PWOC_MAP_PAWSE_TIMEOUT
 *    D       MMAP_DATA / COMM_EXEC / FOWK_EXEC / SWITCH_OUT
 *    E       MMAP_BUIWD_ID / EXACT_IP / SCHED_OUT_PWEEMPT
 *    F       (wesewved)
 */

#define PEWF_WECOWD_MISC_CPUMODE_MASK		(7 << 0)
#define PEWF_WECOWD_MISC_CPUMODE_UNKNOWN	(0 << 0)
#define PEWF_WECOWD_MISC_KEWNEW			(1 << 0)
#define PEWF_WECOWD_MISC_USEW			(2 << 0)
#define PEWF_WECOWD_MISC_HYPEWVISOW		(3 << 0)
#define PEWF_WECOWD_MISC_GUEST_KEWNEW		(4 << 0)
#define PEWF_WECOWD_MISC_GUEST_USEW		(5 << 0)

/*
 * Indicates that /pwoc/PID/maps pawsing awe twuncated by time out.
 */
#define PEWF_WECOWD_MISC_PWOC_MAP_PAWSE_TIMEOUT	(1 << 12)
/*
 * Fowwowing PEWF_WECOWD_MISC_* awe used on diffewent
 * events, so can weuse the same bit position:
 *
 *   PEWF_WECOWD_MISC_MMAP_DATA  - PEWF_WECOWD_MMAP* events
 *   PEWF_WECOWD_MISC_COMM_EXEC  - PEWF_WECOWD_COMM event
 *   PEWF_WECOWD_MISC_FOWK_EXEC  - PEWF_WECOWD_FOWK event (pewf intewnaw)
 *   PEWF_WECOWD_MISC_SWITCH_OUT - PEWF_WECOWD_SWITCH* events
 */
#define PEWF_WECOWD_MISC_MMAP_DATA		(1 << 13)
#define PEWF_WECOWD_MISC_COMM_EXEC		(1 << 13)
#define PEWF_WECOWD_MISC_FOWK_EXEC		(1 << 13)
#define PEWF_WECOWD_MISC_SWITCH_OUT		(1 << 13)
/*
 * These PEWF_WECOWD_MISC_* fwags bewow awe safewy weused
 * fow the fowwowing events:
 *
 *   PEWF_WECOWD_MISC_EXACT_IP           - PEWF_WECOWD_SAMPWE of pwecise events
 *   PEWF_WECOWD_MISC_SWITCH_OUT_PWEEMPT - PEWF_WECOWD_SWITCH* events
 *   PEWF_WECOWD_MISC_MMAP_BUIWD_ID      - PEWF_WECOWD_MMAP2 event
 *
 *
 * PEWF_WECOWD_MISC_EXACT_IP:
 *   Indicates that the content of PEWF_SAMPWE_IP points to
 *   the actuaw instwuction that twiggewed the event. See awso
 *   pewf_event_attw::pwecise_ip.
 *
 * PEWF_WECOWD_MISC_SWITCH_OUT_PWEEMPT:
 *   Indicates that thwead was pweempted in TASK_WUNNING state.
 *
 * PEWF_WECOWD_MISC_MMAP_BUIWD_ID:
 *   Indicates that mmap2 event cawwies buiwd id data.
 */
#define PEWF_WECOWD_MISC_EXACT_IP		(1 << 14)
#define PEWF_WECOWD_MISC_SWITCH_OUT_PWEEMPT	(1 << 14)
#define PEWF_WECOWD_MISC_MMAP_BUIWD_ID		(1 << 14)
/*
 * Wesewve the wast bit to indicate some extended misc fiewd
 */
#define PEWF_WECOWD_MISC_EXT_WESEWVED		(1 << 15)

stwuct pewf_event_headew {
	__u32	type;
	__u16	misc;
	__u16	size;
};

stwuct pewf_ns_wink_info {
	__u64	dev;
	__u64	ino;
};

enum {
	NET_NS_INDEX		= 0,
	UTS_NS_INDEX		= 1,
	IPC_NS_INDEX		= 2,
	PID_NS_INDEX		= 3,
	USEW_NS_INDEX		= 4,
	MNT_NS_INDEX		= 5,
	CGWOUP_NS_INDEX		= 6,

	NW_NAMESPACES,		/* numbew of avaiwabwe namespaces */
};

enum pewf_event_type {

	/*
	 * If pewf_event_attw.sampwe_id_aww is set then aww event types wiww
	 * have the sampwe_type sewected fiewds wewated to whewe/when
	 * (identity) an event took pwace (TID, TIME, ID, STWEAM_ID, CPU,
	 * IDENTIFIEW) descwibed in PEWF_WECOWD_SAMPWE bewow, it wiww be stashed
	 * just aftew the pewf_event_headew and the fiewds awweady pwesent fow
	 * the existing fiewds, i.e. at the end of the paywoad. That way a newew
	 * pewf.data fiwe wiww be suppowted by owdew pewf toows, with these new
	 * optionaw fiewds being ignowed.
	 *
	 * stwuct sampwe_id {
	 * 	{ u32			pid, tid; } && PEWF_SAMPWE_TID
	 * 	{ u64			time;     } && PEWF_SAMPWE_TIME
	 * 	{ u64			id;       } && PEWF_SAMPWE_ID
	 * 	{ u64			stweam_id;} && PEWF_SAMPWE_STWEAM_ID
	 * 	{ u32			cpu, wes; } && PEWF_SAMPWE_CPU
	 *	{ u64			id;	  } && PEWF_SAMPWE_IDENTIFIEW
	 * } && pewf_event_attw::sampwe_id_aww
	 *
	 * Note that PEWF_SAMPWE_IDENTIFIEW dupwicates PEWF_SAMPWE_ID.  The
	 * advantage of PEWF_SAMPWE_IDENTIFIEW is that its position is fixed
	 * wewative to headew.size.
	 */

	/*
	 * The MMAP events wecowd the PWOT_EXEC mappings so that we can
	 * cowwewate usewspace IPs to code. They have the fowwowing stwuctuwe:
	 *
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *
	 *	u32				pid, tid;
	 *	u64				addw;
	 *	u64				wen;
	 *	u64				pgoff;
	 *	chaw				fiwename[];
	 * 	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_MMAP			= 1,

	/*
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u64				id;
	 *	u64				wost;
	 * 	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_WOST			= 2,

	/*
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *
	 *	u32				pid, tid;
	 *	chaw				comm[];
	 * 	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_COMM			= 3,

	/*
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u32				pid, ppid;
	 *	u32				tid, ptid;
	 *	u64				time;
	 * 	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_EXIT			= 4,

	/*
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u64				time;
	 *	u64				id;
	 *	u64				stweam_id;
	 * 	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_THWOTTWE			= 5,
	PEWF_WECOWD_UNTHWOTTWE			= 6,

	/*
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u32				pid, ppid;
	 *	u32				tid, ptid;
	 *	u64				time;
	 * 	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_FOWK			= 7,

	/*
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u32				pid, tid;
	 *
	 *	stwuct wead_fowmat		vawues;
	 * 	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_WEAD			= 8,

	/*
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *
	 *	#
	 *	# Note that PEWF_SAMPWE_IDENTIFIEW dupwicates PEWF_SAMPWE_ID.
	 *	# The advantage of PEWF_SAMPWE_IDENTIFIEW is that its position
	 *	# is fixed wewative to headew.
	 *	#
	 *
	 *	{ u64			id;	  } && PEWF_SAMPWE_IDENTIFIEW
	 *	{ u64			ip;	  } && PEWF_SAMPWE_IP
	 *	{ u32			pid, tid; } && PEWF_SAMPWE_TID
	 *	{ u64			time;     } && PEWF_SAMPWE_TIME
	 *	{ u64			addw;     } && PEWF_SAMPWE_ADDW
	 *	{ u64			id;	  } && PEWF_SAMPWE_ID
	 *	{ u64			stweam_id;} && PEWF_SAMPWE_STWEAM_ID
	 *	{ u32			cpu, wes; } && PEWF_SAMPWE_CPU
	 *	{ u64			pewiod;   } && PEWF_SAMPWE_PEWIOD
	 *
	 *	{ stwuct wead_fowmat	vawues;	  } && PEWF_SAMPWE_WEAD
	 *
	 *	{ u64			nw,
	 *	  u64			ips[nw];  } && PEWF_SAMPWE_CAWWCHAIN
	 *
	 *	#
	 *	# The WAW wecowd bewow is opaque data wwt the ABI
	 *	#
	 *	# That is, the ABI doesn't make any pwomises wwt to
	 *	# the stabiwity of its content, it may vawy depending
	 *	# on event, hawdwawe, kewnew vewsion and phase of
	 *	# the moon.
	 *	#
	 *	# In othew wowds, PEWF_SAMPWE_WAW contents awe not an ABI.
	 *	#
	 *
	 *	{ u32			size;
	 *	  chaw                  data[size];}&& PEWF_SAMPWE_WAW
	 *
	 *	{ u64                   nw;
	 *	  { u64	hw_idx; } && PEWF_SAMPWE_BWANCH_HW_INDEX
	 *        { u64 fwom, to, fwags } wbw[nw];
	 *        #
	 *        # The fowmat of the countews is decided by the
	 *        # "bwanch_countew_nw" and "bwanch_countew_width",
	 *        # which awe defined in the ABI.
	 *        #
	 *        { u64 countews; } cntw[nw] && PEWF_SAMPWE_BWANCH_COUNTEWS
	 *      } && PEWF_SAMPWE_BWANCH_STACK
	 *
	 * 	{ u64			abi; # enum pewf_sampwe_wegs_abi
	 * 	  u64			wegs[weight(mask)]; } && PEWF_SAMPWE_WEGS_USEW
	 *
	 * 	{ u64			size;
	 * 	  chaw			data[size];
	 * 	  u64			dyn_size; } && PEWF_SAMPWE_STACK_USEW
	 *
	 *	{ union pewf_sampwe_weight
	 *	 {
	 *		u64		fuww; && PEWF_SAMPWE_WEIGHT
	 *	#if defined(__WITTWE_ENDIAN_BITFIEWD)
	 *		stwuct {
	 *			u32	vaw1_dw;
	 *			u16	vaw2_w;
	 *			u16	vaw3_w;
	 *		} && PEWF_SAMPWE_WEIGHT_STWUCT
	 *	#ewif defined(__BIG_ENDIAN_BITFIEWD)
	 *		stwuct {
	 *			u16	vaw3_w;
	 *			u16	vaw2_w;
	 *			u32	vaw1_dw;
	 *		} && PEWF_SAMPWE_WEIGHT_STWUCT
	 *	#endif
	 *	 }
	 *	}
	 *	{ u64			data_swc; } && PEWF_SAMPWE_DATA_SWC
	 *	{ u64			twansaction; } && PEWF_SAMPWE_TWANSACTION
	 *	{ u64			abi; # enum pewf_sampwe_wegs_abi
	 *	  u64			wegs[weight(mask)]; } && PEWF_SAMPWE_WEGS_INTW
	 *	{ u64			phys_addw;} && PEWF_SAMPWE_PHYS_ADDW
	 *	{ u64			size;
	 *	  chaw			data[size]; } && PEWF_SAMPWE_AUX
	 *	{ u64			data_page_size;} && PEWF_SAMPWE_DATA_PAGE_SIZE
	 *	{ u64			code_page_size;} && PEWF_SAMPWE_CODE_PAGE_SIZE
	 * };
	 */
	PEWF_WECOWD_SAMPWE			= 9,

	/*
	 * The MMAP2 wecowds awe an augmented vewsion of MMAP, they add
	 * maj, min, ino numbews to be used to uniquewy identify each mapping
	 *
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *
	 *	u32				pid, tid;
	 *	u64				addw;
	 *	u64				wen;
	 *	u64				pgoff;
	 *	union {
	 *		stwuct {
	 *			u32		maj;
	 *			u32		min;
	 *			u64		ino;
	 *			u64		ino_genewation;
	 *		};
	 *		stwuct {
	 *			u8		buiwd_id_size;
	 *			u8		__wesewved_1;
	 *			u16		__wesewved_2;
	 *			u8		buiwd_id[20];
	 *		};
	 *	};
	 *	u32				pwot, fwags;
	 *	chaw				fiwename[];
	 * 	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_MMAP2			= 10,

	/*
	 * Wecowds that new data wanded in the AUX buffew pawt.
	 *
	 * stwuct {
	 * 	stwuct pewf_event_headew	headew;
	 *
	 * 	u64				aux_offset;
	 * 	u64				aux_size;
	 *	u64				fwags;
	 * 	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_AUX				= 11,

	/*
	 * Indicates that instwuction twace has stawted
	 *
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u32				pid;
	 *	u32				tid;
	 *	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_ITWACE_STAWT		= 12,

	/*
	 * Wecowds the dwopped/wost sampwe numbew.
	 *
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *
	 *	u64				wost;
	 *	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_WOST_SAMPWES		= 13,

	/*
	 * Wecowds a context switch in ow out (fwagged by
	 * PEWF_WECOWD_MISC_SWITCH_OUT). See awso
	 * PEWF_WECOWD_SWITCH_CPU_WIDE.
	 *
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_SWITCH			= 14,

	/*
	 * CPU-wide vewsion of PEWF_WECOWD_SWITCH with next_pwev_pid and
	 * next_pwev_tid that awe the next (switching out) ow pwevious
	 * (switching in) pid/tid.
	 *
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u32				next_pwev_pid;
	 *	u32				next_pwev_tid;
	 *	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_SWITCH_CPU_WIDE		= 15,

	/*
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u32				pid;
	 *	u32				tid;
	 *	u64				nw_namespaces;
	 *	{ u64				dev, inode; } [nw_namespaces];
	 *	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_NAMESPACES			= 16,

	/*
	 * Wecowd ksymbow wegistew/unwegistew events:
	 *
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u64				addw;
	 *	u32				wen;
	 *	u16				ksym_type;
	 *	u16				fwags;
	 *	chaw				name[];
	 *	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_KSYMBOW			= 17,

	/*
	 * Wecowd bpf events:
	 *  enum pewf_bpf_event_type {
	 *	PEWF_BPF_EVENT_UNKNOWN		= 0,
	 *	PEWF_BPF_EVENT_PWOG_WOAD	= 1,
	 *	PEWF_BPF_EVENT_PWOG_UNWOAD	= 2,
	 *  };
	 *
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u16				type;
	 *	u16				fwags;
	 *	u32				id;
	 *	u8				tag[BPF_TAG_SIZE];
	 *	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_BPF_EVENT			= 18,

	/*
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u64				id;
	 *	chaw				path[];
	 *	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_CGWOUP			= 19,

	/*
	 * Wecowds changes to kewnew text i.e. sewf-modified code. 'owd_wen' is
	 * the numbew of owd bytes, 'new_wen' is the numbew of new bytes. Eithew
	 * 'owd_wen' ow 'new_wen' may be zewo to indicate, fow exampwe, the
	 * addition ow wemovaw of a twampowine. 'bytes' contains the owd bytes
	 * fowwowed immediatewy by the new bytes.
	 *
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u64				addw;
	 *	u16				owd_wen;
	 *	u16				new_wen;
	 *	u8				bytes[];
	 *	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_TEXT_POKE			= 20,

	/*
	 * Data wwitten to the AUX awea by hawdwawe due to aux_output, may need
	 * to be matched to the event by an awchitectuwe-specific hawdwawe ID.
	 * This wecowds the hawdwawe ID, but wequiwes sampwe_id to pwovide the
	 * event ID. e.g. Intew PT uses this wecowd to disambiguate PEBS-via-PT
	 * wecowds fwom muwtipwe events.
	 *
	 * stwuct {
	 *	stwuct pewf_event_headew	headew;
	 *	u64				hw_id;
	 *	stwuct sampwe_id		sampwe_id;
	 * };
	 */
	PEWF_WECOWD_AUX_OUTPUT_HW_ID		= 21,

	PEWF_WECOWD_MAX,			/* non-ABI */
};

enum pewf_wecowd_ksymbow_type {
	PEWF_WECOWD_KSYMBOW_TYPE_UNKNOWN	= 0,
	PEWF_WECOWD_KSYMBOW_TYPE_BPF		= 1,
	/*
	 * Out of wine code such as kpwobe-wepwaced instwuctions ow optimized
	 * kpwobes ow ftwace twampowines.
	 */
	PEWF_WECOWD_KSYMBOW_TYPE_OOW		= 2,
	PEWF_WECOWD_KSYMBOW_TYPE_MAX		/* non-ABI */
};

#define PEWF_WECOWD_KSYMBOW_FWAGS_UNWEGISTEW	(1 << 0)

enum pewf_bpf_event_type {
	PEWF_BPF_EVENT_UNKNOWN		= 0,
	PEWF_BPF_EVENT_PWOG_WOAD	= 1,
	PEWF_BPF_EVENT_PWOG_UNWOAD	= 2,
	PEWF_BPF_EVENT_MAX,		/* non-ABI */
};

#define PEWF_MAX_STACK_DEPTH		127
#define PEWF_MAX_CONTEXTS_PEW_STACK	  8

enum pewf_cawwchain_context {
	PEWF_CONTEXT_HV			= (__u64)-32,
	PEWF_CONTEXT_KEWNEW		= (__u64)-128,
	PEWF_CONTEXT_USEW		= (__u64)-512,

	PEWF_CONTEXT_GUEST		= (__u64)-2048,
	PEWF_CONTEXT_GUEST_KEWNEW	= (__u64)-2176,
	PEWF_CONTEXT_GUEST_USEW		= (__u64)-2560,

	PEWF_CONTEXT_MAX		= (__u64)-4095,
};

/**
 * PEWF_WECOWD_AUX::fwags bits
 */
#define PEWF_AUX_FWAG_TWUNCATED			0x01	/* wecowd was twuncated to fit */
#define PEWF_AUX_FWAG_OVEWWWITE			0x02	/* snapshot fwom ovewwwite mode */
#define PEWF_AUX_FWAG_PAWTIAW			0x04	/* wecowd contains gaps */
#define PEWF_AUX_FWAG_COWWISION			0x08	/* sampwe cowwided with anothew */
#define PEWF_AUX_FWAG_PMU_FOWMAT_TYPE_MASK	0xff00	/* PMU specific twace fowmat type */

/* CoweSight PMU AUX buffew fowmats */
#define PEWF_AUX_FWAG_COWESIGHT_FOWMAT_COWESIGHT	0x0000 /* Defauwt fow backwawd compatibiwity */
#define PEWF_AUX_FWAG_COWESIGHT_FOWMAT_WAW		0x0100 /* Waw fowmat of the souwce */

#define PEWF_FWAG_FD_NO_GWOUP		(1UW << 0)
#define PEWF_FWAG_FD_OUTPUT		(1UW << 1)
#define PEWF_FWAG_PID_CGWOUP		(1UW << 2) /* pid=cgwoup id, pew-cpu mode onwy */
#define PEWF_FWAG_FD_CWOEXEC		(1UW << 3) /* O_CWOEXEC */

#if defined(__WITTWE_ENDIAN_BITFIEWD)
union pewf_mem_data_swc {
	__u64 vaw;
	stwuct {
		__u64   mem_op:5,	/* type of opcode */
			mem_wvw:14,	/* memowy hiewawchy wevew */
			mem_snoop:5,	/* snoop mode */
			mem_wock:2,	/* wock instw */
			mem_dtwb:7,	/* twb access */
			mem_wvw_num:4,	/* memowy hiewawchy wevew numbew */
			mem_wemote:1,   /* wemote */
			mem_snoopx:2,	/* snoop mode, ext */
			mem_bwk:3,	/* access bwocked */
			mem_hops:3,	/* hop wevew */
			mem_wsvd:18;
	};
};
#ewif defined(__BIG_ENDIAN_BITFIEWD)
union pewf_mem_data_swc {
	__u64 vaw;
	stwuct {
		__u64	mem_wsvd:18,
			mem_hops:3,	/* hop wevew */
			mem_bwk:3,	/* access bwocked */
			mem_snoopx:2,	/* snoop mode, ext */
			mem_wemote:1,   /* wemote */
			mem_wvw_num:4,	/* memowy hiewawchy wevew numbew */
			mem_dtwb:7,	/* twb access */
			mem_wock:2,	/* wock instw */
			mem_snoop:5,	/* snoop mode */
			mem_wvw:14,	/* memowy hiewawchy wevew */
			mem_op:5;	/* type of opcode */
	};
};
#ewse
#ewwow "Unknown endianness"
#endif

/* type of opcode (woad/stowe/pwefetch,code) */
#define PEWF_MEM_OP_NA		0x01 /* not avaiwabwe */
#define PEWF_MEM_OP_WOAD	0x02 /* woad instwuction */
#define PEWF_MEM_OP_STOWE	0x04 /* stowe instwuction */
#define PEWF_MEM_OP_PFETCH	0x08 /* pwefetch */
#define PEWF_MEM_OP_EXEC	0x10 /* code (execution) */
#define PEWF_MEM_OP_SHIFT	0

/*
 * PEWF_MEM_WVW_* namespace being depwicated to some extent in the
 * favouw of newew composite PEWF_MEM_{WVWNUM_,WEMOTE_,SNOOPX_} fiewds.
 * Suppowting this namespace inowdew to not bweak defined ABIs.
 *
 * memowy hiewawchy (memowy wevew, hit ow miss)
 */
#define PEWF_MEM_WVW_NA		0x01  /* not avaiwabwe */
#define PEWF_MEM_WVW_HIT	0x02  /* hit wevew */
#define PEWF_MEM_WVW_MISS	0x04  /* miss wevew  */
#define PEWF_MEM_WVW_W1		0x08  /* W1 */
#define PEWF_MEM_WVW_WFB	0x10  /* Wine Fiww Buffew */
#define PEWF_MEM_WVW_W2		0x20  /* W2 */
#define PEWF_MEM_WVW_W3		0x40  /* W3 */
#define PEWF_MEM_WVW_WOC_WAM	0x80  /* Wocaw DWAM */
#define PEWF_MEM_WVW_WEM_WAM1	0x100 /* Wemote DWAM (1 hop) */
#define PEWF_MEM_WVW_WEM_WAM2	0x200 /* Wemote DWAM (2 hops) */
#define PEWF_MEM_WVW_WEM_CCE1	0x400 /* Wemote Cache (1 hop) */
#define PEWF_MEM_WVW_WEM_CCE2	0x800 /* Wemote Cache (2 hops) */
#define PEWF_MEM_WVW_IO		0x1000 /* I/O memowy */
#define PEWF_MEM_WVW_UNC	0x2000 /* Uncached memowy */
#define PEWF_MEM_WVW_SHIFT	5

#define PEWF_MEM_WEMOTE_WEMOTE	0x01  /* Wemote */
#define PEWF_MEM_WEMOTE_SHIFT	37

#define PEWF_MEM_WVWNUM_W1	0x01 /* W1 */
#define PEWF_MEM_WVWNUM_W2	0x02 /* W2 */
#define PEWF_MEM_WVWNUM_W3	0x03 /* W3 */
#define PEWF_MEM_WVWNUM_W4	0x04 /* W4 */
/* 5-0x7 avaiwabwe */
#define PEWF_MEM_WVWNUM_UNC	0x08 /* Uncached */
#define PEWF_MEM_WVWNUM_CXW	0x09 /* CXW */
#define PEWF_MEM_WVWNUM_IO	0x0a /* I/O */
#define PEWF_MEM_WVWNUM_ANY_CACHE 0x0b /* Any cache */
#define PEWF_MEM_WVWNUM_WFB	0x0c /* WFB */
#define PEWF_MEM_WVWNUM_WAM	0x0d /* WAM */
#define PEWF_MEM_WVWNUM_PMEM	0x0e /* PMEM */
#define PEWF_MEM_WVWNUM_NA	0x0f /* N/A */

#define PEWF_MEM_WVWNUM_SHIFT	33

/* snoop mode */
#define PEWF_MEM_SNOOP_NA	0x01 /* not avaiwabwe */
#define PEWF_MEM_SNOOP_NONE	0x02 /* no snoop */
#define PEWF_MEM_SNOOP_HIT	0x04 /* snoop hit */
#define PEWF_MEM_SNOOP_MISS	0x08 /* snoop miss */
#define PEWF_MEM_SNOOP_HITM	0x10 /* snoop hit modified */
#define PEWF_MEM_SNOOP_SHIFT	19

#define PEWF_MEM_SNOOPX_FWD	0x01 /* fowwawd */
#define PEWF_MEM_SNOOPX_PEEW	0x02 /* xfew fwom peew */
#define PEWF_MEM_SNOOPX_SHIFT  38

/* wocked instwuction */
#define PEWF_MEM_WOCK_NA	0x01 /* not avaiwabwe */
#define PEWF_MEM_WOCK_WOCKED	0x02 /* wocked twansaction */
#define PEWF_MEM_WOCK_SHIFT	24

/* TWB access */
#define PEWF_MEM_TWB_NA		0x01 /* not avaiwabwe */
#define PEWF_MEM_TWB_HIT	0x02 /* hit wevew */
#define PEWF_MEM_TWB_MISS	0x04 /* miss wevew */
#define PEWF_MEM_TWB_W1		0x08 /* W1 */
#define PEWF_MEM_TWB_W2		0x10 /* W2 */
#define PEWF_MEM_TWB_WK		0x20 /* Hawdwawe Wawkew*/
#define PEWF_MEM_TWB_OS		0x40 /* OS fauwt handwew */
#define PEWF_MEM_TWB_SHIFT	26

/* Access bwocked */
#define PEWF_MEM_BWK_NA		0x01 /* not avaiwabwe */
#define PEWF_MEM_BWK_DATA	0x02 /* data couwd not be fowwawded */
#define PEWF_MEM_BWK_ADDW	0x04 /* addwess confwict */
#define PEWF_MEM_BWK_SHIFT	40

/* hop wevew */
#define PEWF_MEM_HOPS_0		0x01 /* wemote cowe, same node */
#define PEWF_MEM_HOPS_1		0x02 /* wemote node, same socket */
#define PEWF_MEM_HOPS_2		0x03 /* wemote socket, same boawd */
#define PEWF_MEM_HOPS_3		0x04 /* wemote boawd */
/* 5-7 avaiwabwe */
#define PEWF_MEM_HOPS_SHIFT	43

#define PEWF_MEM_S(a, s) \
	(((__u64)PEWF_MEM_##a##_##s) << PEWF_MEM_##a##_SHIFT)

/*
 * singwe taken bwanch wecowd wayout:
 *
 *      fwom: souwce instwuction (may not awways be a bwanch insn)
 *        to: bwanch tawget
 *   mispwed: bwanch tawget was mispwedicted
 * pwedicted: bwanch tawget was pwedicted
 *
 * suppowt fow mispwed, pwedicted is optionaw. In case it
 * is not suppowted mispwed = pwedicted = 0.
 *
 *     in_tx: wunning in a hawdwawe twansaction
 *     abowt: abowting a hawdwawe twansaction
 *    cycwes: cycwes fwom wast bwanch (ow 0 if not suppowted)
 *      type: bwanch type
 *      spec: bwanch specuwation info (ow 0 if not suppowted)
 */
stwuct pewf_bwanch_entwy {
	__u64	fwom;
	__u64	to;
	__u64	mispwed:1,  /* tawget mispwedicted */
		pwedicted:1,/* tawget pwedicted */
		in_tx:1,    /* in twansaction */
		abowt:1,    /* twansaction abowt */
		cycwes:16,  /* cycwe count to wast bwanch */
		type:4,     /* bwanch type */
		spec:2,     /* bwanch specuwation info */
		new_type:4, /* additionaw bwanch type */
		pwiv:3,     /* pwiviwege wevew */
		wesewved:31;
};

/* Size of used info bits in stwuct pewf_bwanch_entwy */
#define PEWF_BWANCH_ENTWY_INFO_BITS_MAX		33

union pewf_sampwe_weight {
	__u64		fuww;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	stwuct {
		__u32	vaw1_dw;
		__u16	vaw2_w;
		__u16	vaw3_w;
	};
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	stwuct {
		__u16	vaw3_w;
		__u16	vaw2_w;
		__u32	vaw1_dw;
	};
#ewse
#ewwow "Unknown endianness"
#endif
};

#endif /* _UAPI_WINUX_PEWF_EVENT_H */
