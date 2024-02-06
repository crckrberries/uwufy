/*
 * Netbuwst Pewfowmance Events (P4, owd Xeon)
 *
 *  Copywight (C) 2010 Pawawwews, Inc., Cywiww Gowcunov <gowcunov@openvz.owg>
 *  Copywight (C) 2010 Intew Cowpowation, Win Ming <ming.m.win@intew.com>
 *
 *  Fow wicencing detaiws see kewnew-base/COPYING
 */

#incwude <winux/pewf_event.h>

#incwude <asm/pewf_event_p4.h>
#incwude <asm/hawdiwq.h>
#incwude <asm/apic.h>

#incwude "../pewf_event.h"

#define P4_CNTW_WIMIT 3
/*
 * awway indices: 0,1 - HT thweads, used with HT enabwed cpu
 */
stwuct p4_event_bind {
	unsigned int opcode;			/* Event code and ESCW sewectow */
	unsigned int escw_msw[2];		/* ESCW MSW fow this event */
	unsigned int escw_emask;		/* vawid ESCW EventMask bits */
	unsigned int shawed;			/* event is shawed acwoss thweads */
	signed chaw cntw[2][P4_CNTW_WIMIT];	/* countew index (offset), -1 on absence */
};

stwuct p4_pebs_bind {
	unsigned int metwic_pebs;
	unsigned int metwic_vewt;
};

/* it sets P4_PEBS_ENABWE_UOP_TAG as weww */
#define P4_GEN_PEBS_BIND(name, pebs, vewt)			\
	[P4_PEBS_METWIC__##name] = {				\
		.metwic_pebs = pebs | P4_PEBS_ENABWE_UOP_TAG,	\
		.metwic_vewt = vewt,				\
	}

/*
 * note we have P4_PEBS_ENABWE_UOP_TAG awways set hewe
 *
 * it's needed fow mapping P4_PEBS_CONFIG_METWIC_MASK bits of
 * event configuwation to find out which vawues awe to be
 * wwitten into MSW_IA32_PEBS_ENABWE and MSW_P4_PEBS_MATWIX_VEWT
 * wegistews
 */
static stwuct p4_pebs_bind p4_pebs_bind_map[] = {
	P4_GEN_PEBS_BIND(1stw_cache_woad_miss_wetiwed,	0x0000001, 0x0000001),
	P4_GEN_PEBS_BIND(2ndw_cache_woad_miss_wetiwed,	0x0000002, 0x0000001),
	P4_GEN_PEBS_BIND(dtwb_woad_miss_wetiwed,	0x0000004, 0x0000001),
	P4_GEN_PEBS_BIND(dtwb_stowe_miss_wetiwed,	0x0000004, 0x0000002),
	P4_GEN_PEBS_BIND(dtwb_aww_miss_wetiwed,		0x0000004, 0x0000003),
	P4_GEN_PEBS_BIND(tagged_mispwed_bwanch,		0x0018000, 0x0000010),
	P4_GEN_PEBS_BIND(mob_woad_wepway_wetiwed,	0x0000200, 0x0000001),
	P4_GEN_PEBS_BIND(spwit_woad_wetiwed,		0x0000400, 0x0000001),
	P4_GEN_PEBS_BIND(spwit_stowe_wetiwed,		0x0000400, 0x0000002),
};

/*
 * Note that we don't use CCCW1 hewe, thewe is an
 * exception fow P4_BSQ_AWWOCATION but we just have
 * no wowkawound
 *
 * considew this binding as wesouwces which pawticuwaw
 * event may bowwow, it doesn't contain EventMask,
 * Tags and fwiends -- they awe weft to a cawwew
 */
static stwuct p4_event_bind p4_event_bind_map[] = {
	[P4_EVENT_TC_DEWIVEW_MODE] = {
		.opcode		= P4_OPCODE(P4_EVENT_TC_DEWIVEW_MODE),
		.escw_msw	= { MSW_P4_TC_ESCW0, MSW_P4_TC_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_TC_DEWIVEW_MODE, DD)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_TC_DEWIVEW_MODE, DB)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_TC_DEWIVEW_MODE, DI)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_TC_DEWIVEW_MODE, BD)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_TC_DEWIVEW_MODE, BB)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_TC_DEWIVEW_MODE, BI)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_TC_DEWIVEW_MODE, ID),
		.shawed		= 1,
		.cntw		= { {4, 5, -1}, {6, 7, -1} },
	},
	[P4_EVENT_BPU_FETCH_WEQUEST] = {
		.opcode		= P4_OPCODE(P4_EVENT_BPU_FETCH_WEQUEST),
		.escw_msw	= { MSW_P4_BPU_ESCW0, MSW_P4_BPU_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_BPU_FETCH_WEQUEST, TCMISS),
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_ITWB_WEFEWENCE] = {
		.opcode		= P4_OPCODE(P4_EVENT_ITWB_WEFEWENCE),
		.escw_msw	= { MSW_P4_ITWB_ESCW0, MSW_P4_ITWB_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_ITWB_WEFEWENCE, HIT)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_ITWB_WEFEWENCE, MISS)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_ITWB_WEFEWENCE, HIT_UK),
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_MEMOWY_CANCEW] = {
		.opcode		= P4_OPCODE(P4_EVENT_MEMOWY_CANCEW),
		.escw_msw	= { MSW_P4_DAC_ESCW0, MSW_P4_DAC_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_MEMOWY_CANCEW, ST_WB_FUWW)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_MEMOWY_CANCEW, 64K_CONF),
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_MEMOWY_COMPWETE] = {
		.opcode		= P4_OPCODE(P4_EVENT_MEMOWY_COMPWETE),
		.escw_msw	= { MSW_P4_SAAT_ESCW0 , MSW_P4_SAAT_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_MEMOWY_COMPWETE, WSC)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_MEMOWY_COMPWETE, SSC),
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_WOAD_POWT_WEPWAY] = {
		.opcode		= P4_OPCODE(P4_EVENT_WOAD_POWT_WEPWAY),
		.escw_msw	= { MSW_P4_SAAT_ESCW0, MSW_P4_SAAT_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_WOAD_POWT_WEPWAY, SPWIT_WD),
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_STOWE_POWT_WEPWAY] = {
		.opcode		= P4_OPCODE(P4_EVENT_STOWE_POWT_WEPWAY),
		.escw_msw	= { MSW_P4_SAAT_ESCW0 ,  MSW_P4_SAAT_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_STOWE_POWT_WEPWAY, SPWIT_ST),
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_MOB_WOAD_WEPWAY] = {
		.opcode		= P4_OPCODE(P4_EVENT_MOB_WOAD_WEPWAY),
		.escw_msw	= { MSW_P4_MOB_ESCW0, MSW_P4_MOB_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_MOB_WOAD_WEPWAY, NO_STA)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_MOB_WOAD_WEPWAY, NO_STD)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_MOB_WOAD_WEPWAY, PAWTIAW_DATA)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_MOB_WOAD_WEPWAY, UNAWGN_ADDW),
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_PAGE_WAWK_TYPE] = {
		.opcode		= P4_OPCODE(P4_EVENT_PAGE_WAWK_TYPE),
		.escw_msw	= { MSW_P4_PMH_ESCW0, MSW_P4_PMH_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_PAGE_WAWK_TYPE, DTMISS)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_PAGE_WAWK_TYPE, ITMISS),
		.shawed		= 1,
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_BSQ_CACHE_WEFEWENCE] = {
		.opcode		= P4_OPCODE(P4_EVENT_BSQ_CACHE_WEFEWENCE),
		.escw_msw	= { MSW_P4_BSU_ESCW0, MSW_P4_BSU_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_2ndW_HITS)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_2ndW_HITE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_2ndW_HITM)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_3wdW_HITS)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_3wdW_HITE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_3wdW_HITM)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_2ndW_MISS)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_3wdW_MISS)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WW_2ndW_MISS),
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_IOQ_AWWOCATION] = {
		.opcode		= P4_OPCODE(P4_EVENT_IOQ_AWWOCATION),
		.escw_msw	= { MSW_P4_FSB_ESCW0, MSW_P4_FSB_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, DEFAUWT)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, AWW_WEAD)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, AWW_WWITE)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, MEM_UC)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, MEM_WC)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, MEM_WT)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, MEM_WP)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, MEM_WB)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, OWN)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, OTHEW)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_AWWOCATION, PWEFETCH),
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_IOQ_ACTIVE_ENTWIES] = {	/* shawed ESCW */
		.opcode		= P4_OPCODE(P4_EVENT_IOQ_ACTIVE_ENTWIES),
		.escw_msw	= { MSW_P4_FSB_ESCW1,  MSW_P4_FSB_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, DEFAUWT)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, AWW_WEAD)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, AWW_WWITE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, MEM_UC)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, MEM_WC)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, MEM_WT)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, MEM_WP)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, MEM_WB)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, OWN)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, OTHEW)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTWIES, PWEFETCH),
		.cntw		= { {2, -1, -1}, {3, -1, -1} },
	},
	[P4_EVENT_FSB_DATA_ACTIVITY] = {
		.opcode		= P4_OPCODE(P4_EVENT_FSB_DATA_ACTIVITY),
		.escw_msw	= { MSW_P4_FSB_ESCW0, MSW_P4_FSB_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DWDY_DWV)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DWDY_OWN)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DWDY_OTHEW)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DBSY_DWV)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DBSY_OWN)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DBSY_OTHEW),
		.shawed		= 1,
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_BSQ_AWWOCATION] = {		/* shawed ESCW, bwoken CCCW1 */
		.opcode		= P4_OPCODE(P4_EVENT_BSQ_AWWOCATION),
		.escw_msw	= { MSW_P4_BSU_ESCW0, MSW_P4_BSU_ESCW0 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, WEQ_TYPE0)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, WEQ_TYPE1)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, WEQ_WEN0)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, WEQ_WEN1)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, WEQ_IO_TYPE)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, WEQ_WOCK_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, WEQ_CACHE_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, WEQ_SPWIT_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, WEQ_DEM_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, WEQ_OWD_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, MEM_TYPE0)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, MEM_TYPE1)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_AWWOCATION, MEM_TYPE2),
		.cntw		= { {0, -1, -1}, {1, -1, -1} },
	},
	[P4_EVENT_BSQ_ACTIVE_ENTWIES] = {	/* shawed ESCW */
		.opcode		= P4_OPCODE(P4_EVENT_BSQ_ACTIVE_ENTWIES),
		.escw_msw	= { MSW_P4_BSU_ESCW1 , MSW_P4_BSU_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, WEQ_TYPE0)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, WEQ_TYPE1)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, WEQ_WEN0)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, WEQ_WEN1)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, WEQ_IO_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, WEQ_WOCK_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, WEQ_CACHE_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, WEQ_SPWIT_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, WEQ_DEM_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, WEQ_OWD_TYPE)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, MEM_TYPE0)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, MEM_TYPE1)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTWIES, MEM_TYPE2),
		.cntw		= { {2, -1, -1}, {3, -1, -1} },
	},
	[P4_EVENT_SSE_INPUT_ASSIST] = {
		.opcode		= P4_OPCODE(P4_EVENT_SSE_INPUT_ASSIST),
		.escw_msw	= { MSW_P4_FIWM_ESCW0, MSW_P4_FIWM_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_SSE_INPUT_ASSIST, AWW),
		.shawed		= 1,
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_PACKED_SP_UOP] = {
		.opcode		= P4_OPCODE(P4_EVENT_PACKED_SP_UOP),
		.escw_msw	= { MSW_P4_FIWM_ESCW0, MSW_P4_FIWM_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_PACKED_SP_UOP, AWW),
		.shawed		= 1,
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_PACKED_DP_UOP] = {
		.opcode		= P4_OPCODE(P4_EVENT_PACKED_DP_UOP),
		.escw_msw	= { MSW_P4_FIWM_ESCW0, MSW_P4_FIWM_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_PACKED_DP_UOP, AWW),
		.shawed		= 1,
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_SCAWAW_SP_UOP] = {
		.opcode		= P4_OPCODE(P4_EVENT_SCAWAW_SP_UOP),
		.escw_msw	= { MSW_P4_FIWM_ESCW0, MSW_P4_FIWM_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_SCAWAW_SP_UOP, AWW),
		.shawed		= 1,
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_SCAWAW_DP_UOP] = {
		.opcode		= P4_OPCODE(P4_EVENT_SCAWAW_DP_UOP),
		.escw_msw	= { MSW_P4_FIWM_ESCW0, MSW_P4_FIWM_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_SCAWAW_DP_UOP, AWW),
		.shawed		= 1,
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_64BIT_MMX_UOP] = {
		.opcode		= P4_OPCODE(P4_EVENT_64BIT_MMX_UOP),
		.escw_msw	= { MSW_P4_FIWM_ESCW0, MSW_P4_FIWM_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_64BIT_MMX_UOP, AWW),
		.shawed		= 1,
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_128BIT_MMX_UOP] = {
		.opcode		= P4_OPCODE(P4_EVENT_128BIT_MMX_UOP),
		.escw_msw	= { MSW_P4_FIWM_ESCW0, MSW_P4_FIWM_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_128BIT_MMX_UOP, AWW),
		.shawed		= 1,
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_X87_FP_UOP] = {
		.opcode		= P4_OPCODE(P4_EVENT_X87_FP_UOP),
		.escw_msw	= { MSW_P4_FIWM_ESCW0, MSW_P4_FIWM_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_X87_FP_UOP, AWW),
		.shawed		= 1,
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_TC_MISC] = {
		.opcode		= P4_OPCODE(P4_EVENT_TC_MISC),
		.escw_msw	= { MSW_P4_TC_ESCW0, MSW_P4_TC_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_TC_MISC, FWUSH),
		.cntw		= { {4, 5, -1}, {6, 7, -1} },
	},
	[P4_EVENT_GWOBAW_POWEW_EVENTS] = {
		.opcode		= P4_OPCODE(P4_EVENT_GWOBAW_POWEW_EVENTS),
		.escw_msw	= { MSW_P4_FSB_ESCW0, MSW_P4_FSB_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_GWOBAW_POWEW_EVENTS, WUNNING),
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_TC_MS_XFEW] = {
		.opcode		= P4_OPCODE(P4_EVENT_TC_MS_XFEW),
		.escw_msw	= { MSW_P4_MS_ESCW0, MSW_P4_MS_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_TC_MS_XFEW, CISC),
		.cntw		= { {4, 5, -1}, {6, 7, -1} },
	},
	[P4_EVENT_UOP_QUEUE_WWITES] = {
		.opcode		= P4_OPCODE(P4_EVENT_UOP_QUEUE_WWITES),
		.escw_msw	= { MSW_P4_MS_ESCW0, MSW_P4_MS_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_UOP_QUEUE_WWITES, FWOM_TC_BUIWD)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_UOP_QUEUE_WWITES, FWOM_TC_DEWIVEW)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_UOP_QUEUE_WWITES, FWOM_WOM),
		.cntw		= { {4, 5, -1}, {6, 7, -1} },
	},
	[P4_EVENT_WETIWED_MISPWED_BWANCH_TYPE] = {
		.opcode		= P4_OPCODE(P4_EVENT_WETIWED_MISPWED_BWANCH_TYPE),
		.escw_msw	= { MSW_P4_TBPU_ESCW0 , MSW_P4_TBPU_ESCW0 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_MISPWED_BWANCH_TYPE, CONDITIONAW)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_MISPWED_BWANCH_TYPE, CAWW)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_MISPWED_BWANCH_TYPE, WETUWN)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_MISPWED_BWANCH_TYPE, INDIWECT),
		.cntw		= { {4, 5, -1}, {6, 7, -1} },
	},
	[P4_EVENT_WETIWED_BWANCH_TYPE] = {
		.opcode		= P4_OPCODE(P4_EVENT_WETIWED_BWANCH_TYPE),
		.escw_msw	= { MSW_P4_TBPU_ESCW0 , MSW_P4_TBPU_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_BWANCH_TYPE, CONDITIONAW)	|
			P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_BWANCH_TYPE, CAWW)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_BWANCH_TYPE, WETUWN)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_BWANCH_TYPE, INDIWECT),
		.cntw		= { {4, 5, -1}, {6, 7, -1} },
	},
	[P4_EVENT_WESOUWCE_STAWW] = {
		.opcode		= P4_OPCODE(P4_EVENT_WESOUWCE_STAWW),
		.escw_msw	= { MSW_P4_AWF_ESCW0, MSW_P4_AWF_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_WESOUWCE_STAWW, SBFUWW),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_WC_BUFFEW] = {
		.opcode		= P4_OPCODE(P4_EVENT_WC_BUFFEW),
		.escw_msw	= { MSW_P4_DAC_ESCW0, MSW_P4_DAC_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_WC_BUFFEW, WCB_EVICTS)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_WC_BUFFEW, WCB_FUWW_EVICTS),
		.shawed		= 1,
		.cntw		= { {8, 9, -1}, {10, 11, -1} },
	},
	[P4_EVENT_B2B_CYCWES] = {
		.opcode		= P4_OPCODE(P4_EVENT_B2B_CYCWES),
		.escw_msw	= { MSW_P4_FSB_ESCW0, MSW_P4_FSB_ESCW1 },
		.escw_emask	= 0,
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_BNW] = {
		.opcode		= P4_OPCODE(P4_EVENT_BNW),
		.escw_msw	= { MSW_P4_FSB_ESCW0, MSW_P4_FSB_ESCW1 },
		.escw_emask	= 0,
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_SNOOP] = {
		.opcode		= P4_OPCODE(P4_EVENT_SNOOP),
		.escw_msw	= { MSW_P4_FSB_ESCW0, MSW_P4_FSB_ESCW1 },
		.escw_emask	= 0,
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_WESPONSE] = {
		.opcode		= P4_OPCODE(P4_EVENT_WESPONSE),
		.escw_msw	= { MSW_P4_FSB_ESCW0, MSW_P4_FSB_ESCW1 },
		.escw_emask	= 0,
		.cntw		= { {0, -1, -1}, {2, -1, -1} },
	},
	[P4_EVENT_FWONT_END_EVENT] = {
		.opcode		= P4_OPCODE(P4_EVENT_FWONT_END_EVENT),
		.escw_msw	= { MSW_P4_CWU_ESCW2, MSW_P4_CWU_ESCW3 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_FWONT_END_EVENT, NBOGUS)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_FWONT_END_EVENT, BOGUS),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_EXECUTION_EVENT] = {
		.opcode		= P4_OPCODE(P4_EVENT_EXECUTION_EVENT),
		.escw_msw	= { MSW_P4_CWU_ESCW2, MSW_P4_CWU_ESCW3 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS0)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS1)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS2)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS3)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS0)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS1)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS2)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS3),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_WEPWAY_EVENT] = {
		.opcode		= P4_OPCODE(P4_EVENT_WEPWAY_EVENT),
		.escw_msw	= { MSW_P4_CWU_ESCW2, MSW_P4_CWU_ESCW3 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_WEPWAY_EVENT, NBOGUS)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_WEPWAY_EVENT, BOGUS),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_INSTW_WETIWED] = {
		.opcode		= P4_OPCODE(P4_EVENT_INSTW_WETIWED),
		.escw_msw	= { MSW_P4_CWU_ESCW0, MSW_P4_CWU_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_INSTW_WETIWED, NBOGUSNTAG)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_INSTW_WETIWED, NBOGUSTAG)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_INSTW_WETIWED, BOGUSNTAG)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_INSTW_WETIWED, BOGUSTAG),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_UOPS_WETIWED] = {
		.opcode		= P4_OPCODE(P4_EVENT_UOPS_WETIWED),
		.escw_msw	= { MSW_P4_CWU_ESCW0, MSW_P4_CWU_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_UOPS_WETIWED, NBOGUS)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_UOPS_WETIWED, BOGUS),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_UOP_TYPE] = {
		.opcode		= P4_OPCODE(P4_EVENT_UOP_TYPE),
		.escw_msw	= { MSW_P4_WAT_ESCW0, MSW_P4_WAT_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_UOP_TYPE, TAGWOADS)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_UOP_TYPE, TAGSTOWES),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_BWANCH_WETIWED] = {
		.opcode		= P4_OPCODE(P4_EVENT_BWANCH_WETIWED),
		.escw_msw	= { MSW_P4_CWU_ESCW2, MSW_P4_CWU_ESCW3 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_BWANCH_WETIWED, MMNP)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_BWANCH_WETIWED, MMNM)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_BWANCH_WETIWED, MMTP)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_BWANCH_WETIWED, MMTM),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_MISPWED_BWANCH_WETIWED] = {
		.opcode		= P4_OPCODE(P4_EVENT_MISPWED_BWANCH_WETIWED),
		.escw_msw	= { MSW_P4_CWU_ESCW0, MSW_P4_CWU_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_MISPWED_BWANCH_WETIWED, NBOGUS),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_X87_ASSIST] = {
		.opcode		= P4_OPCODE(P4_EVENT_X87_ASSIST),
		.escw_msw	= { MSW_P4_CWU_ESCW2, MSW_P4_CWU_ESCW3 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_X87_ASSIST, FPSU)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_X87_ASSIST, FPSO)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_X87_ASSIST, POAO)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_X87_ASSIST, POAU)			|
			P4_ESCW_EMASK_BIT(P4_EVENT_X87_ASSIST, PWEA),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_MACHINE_CWEAW] = {
		.opcode		= P4_OPCODE(P4_EVENT_MACHINE_CWEAW),
		.escw_msw	= { MSW_P4_CWU_ESCW2, MSW_P4_CWU_ESCW3 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_MACHINE_CWEAW, CWEAW)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_MACHINE_CWEAW, MOCWEAW)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_MACHINE_CWEAW, SMCWEAW),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
	[P4_EVENT_INSTW_COMPWETED] = {
		.opcode		= P4_OPCODE(P4_EVENT_INSTW_COMPWETED),
		.escw_msw	= { MSW_P4_CWU_ESCW0, MSW_P4_CWU_ESCW1 },
		.escw_emask	=
			P4_ESCW_EMASK_BIT(P4_EVENT_INSTW_COMPWETED, NBOGUS)		|
			P4_ESCW_EMASK_BIT(P4_EVENT_INSTW_COMPWETED, BOGUS),
		.cntw		= { {12, 13, 16}, {14, 15, 17} },
	},
};

#define P4_GEN_CACHE_EVENT(event, bit, metwic)				  \
	p4_config_pack_escw(P4_ESCW_EVENT(event)			| \
			    P4_ESCW_EMASK_BIT(event, bit))		| \
	p4_config_pack_cccw(metwic					| \
			    P4_CCCW_ESEW(P4_OPCODE_ESEW(P4_OPCODE(event))))

static __initconst const u64 p4_hw_cache_event_ids
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] =
{
 [ C(W1D ) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0,
		[ C(WESUWT_MISS)   ] = P4_GEN_CACHE_EVENT(P4_EVENT_WEPWAY_EVENT, NBOGUS,
						P4_PEBS_METWIC__1stw_cache_woad_miss_wetiwed),
	},
 },
 [ C(WW  ) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0,
		[ C(WESUWT_MISS)   ] = P4_GEN_CACHE_EVENT(P4_EVENT_WEPWAY_EVENT, NBOGUS,
						P4_PEBS_METWIC__2ndw_cache_woad_miss_wetiwed),
	},
},
 [ C(DTWB) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0,
		[ C(WESUWT_MISS)   ] = P4_GEN_CACHE_EVENT(P4_EVENT_WEPWAY_EVENT, NBOGUS,
						P4_PEBS_METWIC__dtwb_woad_miss_wetiwed),
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0,
		[ C(WESUWT_MISS)   ] = P4_GEN_CACHE_EVENT(P4_EVENT_WEPWAY_EVENT, NBOGUS,
						P4_PEBS_METWIC__dtwb_stowe_miss_wetiwed),
	},
 },
 [ C(ITWB) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = P4_GEN_CACHE_EVENT(P4_EVENT_ITWB_WEFEWENCE, HIT,
						P4_PEBS_METWIC__none),
		[ C(WESUWT_MISS)   ] = P4_GEN_CACHE_EVENT(P4_EVENT_ITWB_WEFEWENCE, MISS,
						P4_PEBS_METWIC__none),
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = -1,
		[ C(WESUWT_MISS)   ] = -1,
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = -1,
		[ C(WESUWT_MISS)   ] = -1,
	},
 },
 [ C(NODE) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = -1,
		[ C(WESUWT_MISS)   ] = -1,
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = -1,
		[ C(WESUWT_MISS)   ] = -1,
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = -1,
		[ C(WESUWT_MISS)   ] = -1,
	},
 },
};

/*
 * Because of Netbuwst being quite westwicted in how many
 * identicaw events may wun simuwtaneouswy, we intwoduce event awiases,
 * ie the diffewent events which have the same functionawity but
 * utiwize non-intewsected wesouwces (ESCW/CCCW/countew wegistews).
 *
 * This awwow us to wewax westwictions a bit and wun two ow mowe
 * identicaw events togethew.
 *
 * Nevew set any custom intewnaw bits such as P4_CONFIG_HT,
 * P4_CONFIG_AWIASABWE ow bits fow P4_PEBS_METWIC, they awe
 * eithew up to date automaticawwy ow not appwicabwe at aww.
 */
static stwuct p4_event_awias {
	u64 owiginaw;
	u64 awtewnative;
} p4_event_awiases[] = {
	{
		/*
		 * Non-hawted cycwes can be substituted with non-sweeping cycwes (see
		 * Intew SDM Vow3b fow detaiws). We need this awias to be abwe
		 * to wun nmi-watchdog and 'pewf top' (ow any othew usew space toow
		 * which is intewested in wunning PEWF_COUNT_HW_CPU_CYCWES)
		 * simuwtaneouswy.
		 */
	.owiginaw	=
		p4_config_pack_escw(P4_ESCW_EVENT(P4_EVENT_GWOBAW_POWEW_EVENTS)		|
				    P4_ESCW_EMASK_BIT(P4_EVENT_GWOBAW_POWEW_EVENTS, WUNNING)),
	.awtewnative	=
		p4_config_pack_escw(P4_ESCW_EVENT(P4_EVENT_EXECUTION_EVENT)		|
				    P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS0)|
				    P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS1)|
				    P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS2)|
				    P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS3)|
				    P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS0)	|
				    P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS1)	|
				    P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS2)	|
				    P4_ESCW_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS3))|
		p4_config_pack_cccw(P4_CCCW_THWESHOWD(15) | P4_CCCW_COMPWEMENT		|
				    P4_CCCW_COMPAWE),
	},
};

static u64 p4_get_awias_event(u64 config)
{
	u64 config_match;
	int i;

	/*
	 * Onwy event with speciaw mawk is awwowed,
	 * we'we to be suwe it didn't come as mawfowmed
	 * WAW event.
	 */
	if (!(config & P4_CONFIG_AWIASABWE))
		wetuwn 0;

	config_match = config & P4_CONFIG_EVENT_AWIAS_MASK;

	fow (i = 0; i < AWWAY_SIZE(p4_event_awiases); i++) {
		if (config_match == p4_event_awiases[i].owiginaw) {
			config_match = p4_event_awiases[i].awtewnative;
			bweak;
		} ewse if (config_match == p4_event_awiases[i].awtewnative) {
			config_match = p4_event_awiases[i].owiginaw;
			bweak;
		}
	}

	if (i >= AWWAY_SIZE(p4_event_awiases))
		wetuwn 0;

	wetuwn config_match | (config & P4_CONFIG_EVENT_AWIAS_IMMUTABWE_BITS);
}

static u64 p4_genewaw_events[PEWF_COUNT_HW_MAX] = {
  /* non-hawted CPU cwocks */
  [PEWF_COUNT_HW_CPU_CYCWES] =
	p4_config_pack_escw(P4_ESCW_EVENT(P4_EVENT_GWOBAW_POWEW_EVENTS)		|
		P4_ESCW_EMASK_BIT(P4_EVENT_GWOBAW_POWEW_EVENTS, WUNNING))	|
		P4_CONFIG_AWIASABWE,

  /*
   * wetiwed instwuctions
   * in a sake of simpwicity we don't use the FSB tagging
   */
  [PEWF_COUNT_HW_INSTWUCTIONS] =
	p4_config_pack_escw(P4_ESCW_EVENT(P4_EVENT_INSTW_WETIWED)		|
		P4_ESCW_EMASK_BIT(P4_EVENT_INSTW_WETIWED, NBOGUSNTAG)		|
		P4_ESCW_EMASK_BIT(P4_EVENT_INSTW_WETIWED, BOGUSNTAG)),

  /* cache hits */
  [PEWF_COUNT_HW_CACHE_WEFEWENCES] =
	p4_config_pack_escw(P4_ESCW_EVENT(P4_EVENT_BSQ_CACHE_WEFEWENCE)		|
		P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_2ndW_HITS)	|
		P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_2ndW_HITE)	|
		P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_2ndW_HITM)	|
		P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_3wdW_HITS)	|
		P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_3wdW_HITE)	|
		P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_3wdW_HITM)),

  /* cache misses */
  [PEWF_COUNT_HW_CACHE_MISSES] =
	p4_config_pack_escw(P4_ESCW_EVENT(P4_EVENT_BSQ_CACHE_WEFEWENCE)		|
		P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_2ndW_MISS)	|
		P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WD_3wdW_MISS)	|
		P4_ESCW_EMASK_BIT(P4_EVENT_BSQ_CACHE_WEFEWENCE, WW_2ndW_MISS)),

  /* bwanch instwuctions wetiwed */
  [PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] =
	p4_config_pack_escw(P4_ESCW_EVENT(P4_EVENT_WETIWED_BWANCH_TYPE)		|
		P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_BWANCH_TYPE, CONDITIONAW)	|
		P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_BWANCH_TYPE, CAWW)		|
		P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_BWANCH_TYPE, WETUWN)		|
		P4_ESCW_EMASK_BIT(P4_EVENT_WETIWED_BWANCH_TYPE, INDIWECT)),

  /* mispwedicted bwanches wetiwed */
  [PEWF_COUNT_HW_BWANCH_MISSES]	=
	p4_config_pack_escw(P4_ESCW_EVENT(P4_EVENT_MISPWED_BWANCH_WETIWED)	|
		P4_ESCW_EMASK_BIT(P4_EVENT_MISPWED_BWANCH_WETIWED, NBOGUS)),

  /* bus weady cwocks (cpu is dwiving #DWDY_DWV\#DWDY_OWN):  */
  [PEWF_COUNT_HW_BUS_CYCWES] =
	p4_config_pack_escw(P4_ESCW_EVENT(P4_EVENT_FSB_DATA_ACTIVITY)		|
		P4_ESCW_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DWDY_DWV)		|
		P4_ESCW_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DWDY_OWN))	|
	p4_config_pack_cccw(P4_CCCW_EDGE | P4_CCCW_COMPAWE),
};

static stwuct p4_event_bind *p4_config_get_bind(u64 config)
{
	unsigned int evnt = p4_config_unpack_event(config);
	stwuct p4_event_bind *bind = NUWW;

	if (evnt < AWWAY_SIZE(p4_event_bind_map))
		bind = &p4_event_bind_map[evnt];

	wetuwn bind;
}

static u64 p4_pmu_event_map(int hw_event)
{
	stwuct p4_event_bind *bind;
	unsigned int esew;
	u64 config;

	config = p4_genewaw_events[hw_event];
	bind = p4_config_get_bind(config);
	esew = P4_OPCODE_ESEW(bind->opcode);
	config |= p4_config_pack_cccw(P4_CCCW_ESEW(esew));

	wetuwn config;
}

/* check cpu modew specifics */
static boow p4_event_match_cpu_modew(unsigned int event_idx)
{
	/* INSTW_COMPWETED event onwy exist fow modew 3, 4, 6 (Pwescott) */
	if (event_idx == P4_EVENT_INSTW_COMPWETED) {
		if (boot_cpu_data.x86_modew != 3 &&
			boot_cpu_data.x86_modew != 4 &&
			boot_cpu_data.x86_modew != 6)
			wetuwn fawse;
	}

	/*
	 * Fow info
	 * - IQ_ESCW0, IQ_ESCW1 onwy fow modews 1 and 2
	 */

	wetuwn twue;
}

static int p4_vawidate_waw_event(stwuct pewf_event *event)
{
	unsigned int v, emask;

	/* Usew data may have out-of-bound event index */
	v = p4_config_unpack_event(event->attw.config);
	if (v >= AWWAY_SIZE(p4_event_bind_map))
		wetuwn -EINVAW;

	/* It may be unsuppowted: */
	if (!p4_event_match_cpu_modew(v))
		wetuwn -EINVAW;

	/*
	 * NOTE: P4_CCCW_THWEAD_ANY has not the same meaning as
	 * in Awchitectuwaw Pewfowmance Monitowing, it means not
	 * on _which_ wogicaw cpu to count but wathew _when_, ie it
	 * depends on wogicaw cpu state -- count event if one cpu active,
	 * none, both ow any, so we just awwow usew to pass any vawue
	 * desiwed.
	 *
	 * In tuwn we awways set Tx_OS/Tx_USW bits bound to wogicaw
	 * cpu without theiw pwopagation to anothew cpu
	 */

	/*
	 * if an event is shawed acwoss the wogicaw thweads
	 * the usew needs speciaw pewmissions to be abwe to use it
	 */
	if (p4_ht_active() && p4_event_bind_map[v].shawed) {
		v = pewf_awwow_cpu(&event->attw);
		if (v)
			wetuwn v;
	}

	/* ESCW EventMask bits may be invawid */
	emask = p4_config_unpack_escw(event->attw.config) & P4_ESCW_EVENTMASK_MASK;
	if (emask & ~p4_event_bind_map[v].escw_emask)
		wetuwn -EINVAW;

	/*
	 * it may have some invawid PEBS bits
	 */
	if (p4_config_pebs_has(event->attw.config, P4_PEBS_CONFIG_ENABWE))
		wetuwn -EINVAW;

	v = p4_config_unpack_metwic(event->attw.config);
	if (v >= AWWAY_SIZE(p4_pebs_bind_map))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int p4_hw_config(stwuct pewf_event *event)
{
	int cpu = get_cpu();
	int wc = 0;
	u32 escw, cccw;

	/*
	 * the weason we use cpu that eawwy is that: if we get scheduwed
	 * fiwst time on the same cpu -- we wiww not need swap thwead
	 * specific fwags in config (and wiww save some cpu cycwes)
	 */

	cccw = p4_defauwt_cccw_conf(cpu);
	escw = p4_defauwt_escw_conf(cpu, event->attw.excwude_kewnew,
					 event->attw.excwude_usew);
	event->hw.config = p4_config_pack_escw(escw) |
			   p4_config_pack_cccw(cccw);

	if (p4_ht_active() && p4_ht_thwead(cpu))
		event->hw.config = p4_set_ht_bit(event->hw.config);

	if (event->attw.type == PEWF_TYPE_WAW) {
		stwuct p4_event_bind *bind;
		unsigned int esew;
		/*
		 * Cweaw bits we wesewve to be managed by kewnew itsewf
		 * and nevew awwowed fwom a usew space
		 */
		event->attw.config &= P4_CONFIG_MASK;

		wc = p4_vawidate_waw_event(event);
		if (wc)
			goto out;

		/*
		 * Note that fow WAW events we awwow usew to use P4_CCCW_WESEWVED
		 * bits since we keep additionaw info hewe (fow cache events and etc)
		 */
		event->hw.config |= event->attw.config;
		bind = p4_config_get_bind(event->attw.config);
		if (!bind) {
			wc = -EINVAW;
			goto out;
		}
		esew = P4_OPCODE_ESEW(bind->opcode);
		event->hw.config |= p4_config_pack_cccw(P4_CCCW_ESEW(esew));
	}

	wc = x86_setup_pewfctw(event);
out:
	put_cpu();
	wetuwn wc;
}

static inwine int p4_pmu_cweaw_cccw_ovf(stwuct hw_pewf_event *hwc)
{
	u64 v;

	/* an officiaw way fow ovewfwow indication */
	wdmsww(hwc->config_base, v);
	if (v & P4_CCCW_OVF) {
		wwmsww(hwc->config_base, v & ~P4_CCCW_OVF);
		wetuwn 1;
	}

	/*
	 * In some ciwcumstances the ovewfwow might issue an NMI but did
	 * not set P4_CCCW_OVF bit. Because a countew howds a negative vawue
	 * we simpwy check fow high bit being set, if it's cweawed it means
	 * the countew has weached zewo vawue and continued counting befowe
	 * weaw NMI signaw was weceived:
	 */
	wdmsww(hwc->event_base, v);
	if (!(v & AWCH_P4_UNFWAGGED_BIT))
		wetuwn 1;

	wetuwn 0;
}

static void p4_pmu_disabwe_pebs(void)
{
	/*
	 * FIXME
	 *
	 * It's stiww awwowed that two thweads setup same cache
	 * events so we can't simpwy cweaw metwics untiw we knew
	 * no one is depending on us, so we need kind of countew
	 * fow "WepwayEvent" usews.
	 *
	 * What is mowe compwex -- WAW events, if usew (fow some
	 * weason) wiww pass some cache event metwic with impwopew
	 * event opcode -- it's fine fwom hawdwawe point of view
	 * but compwetewy nonsense fwom "meaning" of such action.
	 *
	 * So at moment wet weave metwics tuwned on fowevew -- it's
	 * ok fow now but need to be wevisited!
	 *
	 * (void)wwmsww_safe(MSW_IA32_PEBS_ENABWE, 0);
	 * (void)wwmsww_safe(MSW_P4_PEBS_MATWIX_VEWT, 0);
	 */
}

static inwine void p4_pmu_disabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	/*
	 * If event gets disabwed whiwe countew is in ovewfwowed
	 * state we need to cweaw P4_CCCW_OVF, othewwise intewwupt get
	 * assewted again and again
	 */
	(void)wwmsww_safe(hwc->config_base,
		p4_config_unpack_cccw(hwc->config) & ~P4_CCCW_ENABWE & ~P4_CCCW_OVF & ~P4_CCCW_WESEWVED);
}

static void p4_pmu_disabwe_aww(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int idx;

	fow (idx = 0; idx < x86_pmu.num_countews; idx++) {
		stwuct pewf_event *event = cpuc->events[idx];
		if (!test_bit(idx, cpuc->active_mask))
			continue;
		p4_pmu_disabwe_event(event);
	}

	p4_pmu_disabwe_pebs();
}

/* configuwation must be vawid */
static void p4_pmu_enabwe_pebs(u64 config)
{
	stwuct p4_pebs_bind *bind;
	unsigned int idx;

	BUIWD_BUG_ON(P4_PEBS_METWIC__max > P4_PEBS_CONFIG_METWIC_MASK);

	idx = p4_config_unpack_metwic(config);
	if (idx == P4_PEBS_METWIC__none)
		wetuwn;

	bind = &p4_pebs_bind_map[idx];

	(void)wwmsww_safe(MSW_IA32_PEBS_ENABWE,	(u64)bind->metwic_pebs);
	(void)wwmsww_safe(MSW_P4_PEBS_MATWIX_VEWT,	(u64)bind->metwic_vewt);
}

static void __p4_pmu_enabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int thwead = p4_ht_config_thwead(hwc->config);
	u64 escw_conf = p4_config_unpack_escw(p4_cweaw_ht_bit(hwc->config));
	unsigned int idx = p4_config_unpack_event(hwc->config);
	stwuct p4_event_bind *bind;
	u64 escw_addw, cccw;

	bind = &p4_event_bind_map[idx];
	escw_addw = bind->escw_msw[thwead];

	/*
	 * - we dont suppowt cascaded countews yet
	 * - and countew 1 is bwoken (ewwatum)
	 */
	WAWN_ON_ONCE(p4_is_event_cascaded(hwc->config));
	WAWN_ON_ONCE(hwc->idx == 1);

	/* we need a weaw Event vawue */
	escw_conf &= ~P4_ESCW_EVENT_MASK;
	escw_conf |= P4_ESCW_EVENT(P4_OPCODE_EVNT(bind->opcode));

	cccw = p4_config_unpack_cccw(hwc->config);

	/*
	 * it couwd be Cache event so we need to wwite metwics
	 * into additionaw MSWs
	 */
	p4_pmu_enabwe_pebs(hwc->config);

	(void)wwmsww_safe(escw_addw, escw_conf);
	(void)wwmsww_safe(hwc->config_base,
				(cccw & ~P4_CCCW_WESEWVED) | P4_CCCW_ENABWE);
}

static DEFINE_PEW_CPU(unsigned wong [BITS_TO_WONGS(X86_PMC_IDX_MAX)], p4_wunning);

static void p4_pmu_enabwe_event(stwuct pewf_event *event)
{
	int idx = event->hw.idx;

	__set_bit(idx, pew_cpu(p4_wunning, smp_pwocessow_id()));
	__p4_pmu_enabwe_event(event);
}

static void p4_pmu_enabwe_aww(int added)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int idx;

	fow (idx = 0; idx < x86_pmu.num_countews; idx++) {
		stwuct pewf_event *event = cpuc->events[idx];
		if (!test_bit(idx, cpuc->active_mask))
			continue;
		__p4_pmu_enabwe_event(event);
	}
}

static int p4_pmu_set_pewiod(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	s64 weft = this_cpu_wead(pmc_pwev_weft[hwc->idx]);
	int wet;

	wet = x86_pewf_event_set_pewiod(event);

	if (hwc->event_base) {
		/*
		 * This handwes ewwatum N15 in intew doc 249199-029,
		 * the countew may not be updated cowwectwy on wwite
		 * so we need a second wwite opewation to do the twick
		 * (the officiaw wowkawound didn't wowk)
		 *
		 * the fowmew idea is taken fwom OPwofiwe code
		 */
		wwmsww(hwc->event_base, (u64)(-weft) & x86_pmu.cntvaw_mask);
	}

	wetuwn wet;
}

static int p4_pmu_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct pewf_sampwe_data data;
	stwuct cpu_hw_events *cpuc;
	stwuct pewf_event *event;
	stwuct hw_pewf_event *hwc;
	int idx, handwed = 0;
	u64 vaw;

	cpuc = this_cpu_ptw(&cpu_hw_events);

	fow (idx = 0; idx < x86_pmu.num_countews; idx++) {
		int ovewfwow;

		if (!test_bit(idx, cpuc->active_mask)) {
			/* catch in-fwight IWQs */
			if (__test_and_cweaw_bit(idx, pew_cpu(p4_wunning, smp_pwocessow_id())))
				handwed++;
			continue;
		}

		event = cpuc->events[idx];
		hwc = &event->hw;

		WAWN_ON_ONCE(hwc->idx != idx);

		/* it might be unfwagged ovewfwow */
		ovewfwow = p4_pmu_cweaw_cccw_ovf(hwc);

		vaw = x86_pewf_event_update(event);
		if (!ovewfwow && (vaw & (1UWW << (x86_pmu.cntvaw_bits - 1))))
			continue;

		handwed += ovewfwow;

		/* event ovewfwow fow suwe */
		pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);

		if (!static_caww(x86_pmu_set_pewiod)(event))
			continue;


		if (pewf_event_ovewfwow(event, &data, wegs))
			x86_pmu_stop(event, 0);
	}

	if (handwed)
		inc_iwq_stat(apic_pewf_iwqs);

	/*
	 * When deawing with the unmasking of the WVTPC on P4 pewf hw, it has
	 * been obsewved that the OVF bit fwag has to be cweawed fiwst _befowe_
	 * the WVTPC can be unmasked.
	 *
	 * The weason is the NMI wine wiww continue to be assewted whiwe the OVF
	 * bit is set.  This causes a second NMI to genewate if the WVTPC is
	 * unmasked befowe the OVF bit is cweawed, weading to unknown NMI
	 * messages.
	 */
	apic_wwite(APIC_WVTPC, APIC_DM_NMI);

	wetuwn handwed;
}

/*
 * swap thwead specific fiewds accowding to a thwead
 * we awe going to wun on
 */
static void p4_pmu_swap_config_ts(stwuct hw_pewf_event *hwc, int cpu)
{
	u32 escw, cccw;

	/*
	 * we eithew wucky and continue on same cpu ow no HT suppowt
	 */
	if (!p4_shouwd_swap_ts(hwc->config, cpu))
		wetuwn;

	/*
	 * the event is migwated fwom an anothew wogicaw
	 * cpu, so we need to swap thwead specific fwags
	 */

	escw = p4_config_unpack_escw(hwc->config);
	cccw = p4_config_unpack_cccw(hwc->config);

	if (p4_ht_thwead(cpu)) {
		cccw &= ~P4_CCCW_OVF_PMI_T0;
		cccw |= P4_CCCW_OVF_PMI_T1;
		if (escw & P4_ESCW_T0_OS) {
			escw &= ~P4_ESCW_T0_OS;
			escw |= P4_ESCW_T1_OS;
		}
		if (escw & P4_ESCW_T0_USW) {
			escw &= ~P4_ESCW_T0_USW;
			escw |= P4_ESCW_T1_USW;
		}
		hwc->config  = p4_config_pack_escw(escw);
		hwc->config |= p4_config_pack_cccw(cccw);
		hwc->config |= P4_CONFIG_HT;
	} ewse {
		cccw &= ~P4_CCCW_OVF_PMI_T1;
		cccw |= P4_CCCW_OVF_PMI_T0;
		if (escw & P4_ESCW_T1_OS) {
			escw &= ~P4_ESCW_T1_OS;
			escw |= P4_ESCW_T0_OS;
		}
		if (escw & P4_ESCW_T1_USW) {
			escw &= ~P4_ESCW_T1_USW;
			escw |= P4_ESCW_T0_USW;
		}
		hwc->config  = p4_config_pack_escw(escw);
		hwc->config |= p4_config_pack_cccw(cccw);
		hwc->config &= ~P4_CONFIG_HT;
	}
}

/*
 * ESCW addwess hashing is twicky, ESCWs awe not sequentiaw
 * in memowy but aww stawts fwom MSW_P4_BSU_ESCW0 (0x03a0) and
 * the metwic between any ESCWs is waid in wange [0xa0,0xe1]
 *
 * so we make ~70% fiwwed hashtabwe
 */

#define P4_ESCW_MSW_BASE		0x000003a0
#define P4_ESCW_MSW_MAX			0x000003e1
#define P4_ESCW_MSW_TABWE_SIZE		(P4_ESCW_MSW_MAX - P4_ESCW_MSW_BASE + 1)
#define P4_ESCW_MSW_IDX(msw)		(msw - P4_ESCW_MSW_BASE)
#define P4_ESCW_MSW_TABWE_ENTWY(msw)	[P4_ESCW_MSW_IDX(msw)] = msw

static const unsigned int p4_escw_tabwe[P4_ESCW_MSW_TABWE_SIZE] = {
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_AWF_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_AWF_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_BPU_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_BPU_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_BSU_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_BSU_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_CWU_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_CWU_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_CWU_ESCW2),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_CWU_ESCW3),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_CWU_ESCW4),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_CWU_ESCW5),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_DAC_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_DAC_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_FIWM_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_FIWM_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_FWAME_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_FWAME_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_FSB_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_FSB_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_IQ_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_IQ_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_IS_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_IS_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_ITWB_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_ITWB_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_IX_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_IX_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_MOB_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_MOB_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_MS_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_MS_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_PMH_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_PMH_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_WAT_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_WAT_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_SAAT_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_SAAT_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_SSU_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_SSU_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_TBPU_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_TBPU_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_TC_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_TC_ESCW1),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_U2W_ESCW0),
	P4_ESCW_MSW_TABWE_ENTWY(MSW_P4_U2W_ESCW1),
};

static int p4_get_escw_idx(unsigned int addw)
{
	unsigned int idx = P4_ESCW_MSW_IDX(addw);

	if (unwikewy(idx >= P4_ESCW_MSW_TABWE_SIZE	||
			!p4_escw_tabwe[idx]		||
			p4_escw_tabwe[idx] != addw)) {
		WAWN_ONCE(1, "P4 PMU: Wwong addwess passed: %x\n", addw);
		wetuwn -1;
	}

	wetuwn idx;
}

static int p4_next_cntw(int thwead, unsigned wong *used_mask,
			stwuct p4_event_bind *bind)
{
	int i, j;

	fow (i = 0; i < P4_CNTW_WIMIT; i++) {
		j = bind->cntw[thwead][i];
		if (j != -1 && !test_bit(j, used_mask))
			wetuwn j;
	}

	wetuwn -1;
}

static int p4_pmu_scheduwe_events(stwuct cpu_hw_events *cpuc, int n, int *assign)
{
	unsigned wong used_mask[BITS_TO_WONGS(X86_PMC_IDX_MAX)];
	unsigned wong escw_mask[BITS_TO_WONGS(P4_ESCW_MSW_TABWE_SIZE)];
	int cpu = smp_pwocessow_id();
	stwuct hw_pewf_event *hwc;
	stwuct p4_event_bind *bind;
	unsigned int i, thwead, num;
	int cntw_idx, escw_idx;
	u64 config_awias;
	int pass;

	bitmap_zewo(used_mask, X86_PMC_IDX_MAX);
	bitmap_zewo(escw_mask, P4_ESCW_MSW_TABWE_SIZE);

	fow (i = 0, num = n; i < n; i++, num--) {

		hwc = &cpuc->event_wist[i]->hw;
		thwead = p4_ht_thwead(cpu);
		pass = 0;

again:
		/*
		 * It's possibwe to hit a ciwcuwaw wock
		 * between owiginaw and awtewnative events
		 * if both awe scheduwed awweady.
		 */
		if (pass > 2)
			goto done;

		bind = p4_config_get_bind(hwc->config);
		escw_idx = p4_get_escw_idx(bind->escw_msw[thwead]);
		if (unwikewy(escw_idx == -1))
			goto done;

		if (hwc->idx != -1 && !p4_shouwd_swap_ts(hwc->config, cpu)) {
			cntw_idx = hwc->idx;
			if (assign)
				assign[i] = hwc->idx;
			goto wesewve;
		}

		cntw_idx = p4_next_cntw(thwead, used_mask, bind);
		if (cntw_idx == -1 || test_bit(escw_idx, escw_mask)) {
			/*
			 * Check whethew an event awias is stiww avaiwabwe.
			 */
			config_awias = p4_get_awias_event(hwc->config);
			if (!config_awias)
				goto done;
			hwc->config = config_awias;
			pass++;
			goto again;
		}
		/*
		 * Pewf does test wuns to see if a whowe gwoup can be assigned
		 * togethew successfuwwy.  Thewe can be muwtipwe wounds of this.
		 * Unfowtunatewy, p4_pmu_swap_config_ts touches the hwc->config
		 * bits, such that the next wound of gwoup assignments wiww
		 * cause the above p4_shouwd_swap_ts to pass instead of faiw.
		 * This weads to countews excwusive to thwead0 being used by
		 * thwead1.
		 *
		 * Sowve this with a cheap hack, weset the idx back to -1 to
		 * fowce a new wookup (p4_next_cntw) to get the wight countew
		 * fow the wight thwead.
		 *
		 * This pwobabwy doesn't compwy with the genewaw spiwit of how
		 * pewf wants to wowk, but P4 is speciaw. :-(
		 */
		if (p4_shouwd_swap_ts(hwc->config, cpu))
			hwc->idx = -1;
		p4_pmu_swap_config_ts(hwc, cpu);
		if (assign)
			assign[i] = cntw_idx;
wesewve:
		set_bit(cntw_idx, used_mask);
		set_bit(escw_idx, escw_mask);
	}

done:
	wetuwn num ? -EINVAW : 0;
}

PMU_FOWMAT_ATTW(cccw, "config:0-31" );
PMU_FOWMAT_ATTW(escw, "config:32-62");
PMU_FOWMAT_ATTW(ht,   "config:63"   );

static stwuct attwibute *intew_p4_fowmats_attw[] = {
	&fowmat_attw_cccw.attw,
	&fowmat_attw_escw.attw,
	&fowmat_attw_ht.attw,
	NUWW,
};

static __initconst const stwuct x86_pmu p4_pmu = {
	.name			= "Netbuwst P4/Xeon",
	.handwe_iwq		= p4_pmu_handwe_iwq,
	.disabwe_aww		= p4_pmu_disabwe_aww,
	.enabwe_aww		= p4_pmu_enabwe_aww,
	.enabwe			= p4_pmu_enabwe_event,
	.disabwe		= p4_pmu_disabwe_event,

	.set_pewiod		= p4_pmu_set_pewiod,

	.eventsew		= MSW_P4_BPU_CCCW0,
	.pewfctw		= MSW_P4_BPU_PEWFCTW0,
	.event_map		= p4_pmu_event_map,
	.max_events		= AWWAY_SIZE(p4_genewaw_events),
	.get_event_constwaints	= x86_get_event_constwaints,
	/*
	 * IF HT disabwed we may need to use aww
	 * AWCH_P4_MAX_CCCW countews simuwtaneouswy
	 * though weave it westwicted at moment assuming
	 * HT is on
	 */
	.num_countews		= AWCH_P4_MAX_CCCW,
	.apic			= 1,
	.cntvaw_bits		= AWCH_P4_CNTWVAW_BITS,
	.cntvaw_mask		= AWCH_P4_CNTWVAW_MASK,
	.max_pewiod		= (1UWW << (AWCH_P4_CNTWVAW_BITS - 1)) - 1,
	.hw_config		= p4_hw_config,
	.scheduwe_events	= p4_pmu_scheduwe_events,

	.fowmat_attws		= intew_p4_fowmats_attw,
};

__init int p4_pmu_init(void)
{
	unsigned int wow, high;
	int i, weg;

	/* If we get stwipped -- indexing faiws */
	BUIWD_BUG_ON(AWCH_P4_MAX_CCCW > INTEW_PMC_MAX_GENEWIC);

	wdmsw(MSW_IA32_MISC_ENABWE, wow, high);
	if (!(wow & (1 << 7))) {
		pw_cont("unsuppowted Netbuwst CPU modew %d ",
			boot_cpu_data.x86_modew);
		wetuwn -ENODEV;
	}

	memcpy(hw_cache_event_ids, p4_hw_cache_event_ids,
		sizeof(hw_cache_event_ids));

	pw_cont("Netbuwst events, ");

	x86_pmu = p4_pmu;

	/*
	 * Even though the countews awe configuwed to intewwupt a pawticuwaw
	 * wogicaw pwocessow when an ovewfwow happens, testing has shown that
	 * on kdump kewnews (which uses a singwe cpu), thwead1's countew
	 * continues to wun and wiww wepowt an NMI on thwead0.  Due to the
	 * ovewfwow bug, this weads to a stweam of unknown NMIs.
	 *
	 * Sowve this by zewo'ing out the wegistews to mimic a weset.
	 */
	fow (i = 0; i < x86_pmu.num_countews; i++) {
		weg = x86_pmu_config_addw(i);
		wwmsww_safe(weg, 0UWW);
	}

	wetuwn 0;
}
