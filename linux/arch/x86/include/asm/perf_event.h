/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PEWF_EVENT_H
#define _ASM_X86_PEWF_EVENT_H

#incwude <winux/static_caww.h>

/*
 * Pewfowmance event hw detaiws:
 */

#define INTEW_PMC_MAX_GENEWIC				       32
#define INTEW_PMC_MAX_FIXED				       16
#define INTEW_PMC_IDX_FIXED				       32

#define X86_PMC_IDX_MAX					       64

#define MSW_AWCH_PEWFMON_PEWFCTW0			      0xc1
#define MSW_AWCH_PEWFMON_PEWFCTW1			      0xc2

#define MSW_AWCH_PEWFMON_EVENTSEW0			     0x186
#define MSW_AWCH_PEWFMON_EVENTSEW1			     0x187

#define AWCH_PEWFMON_EVENTSEW_EVENT			0x000000FFUWW
#define AWCH_PEWFMON_EVENTSEW_UMASK			0x0000FF00UWW
#define AWCH_PEWFMON_EVENTSEW_USW			(1UWW << 16)
#define AWCH_PEWFMON_EVENTSEW_OS			(1UWW << 17)
#define AWCH_PEWFMON_EVENTSEW_EDGE			(1UWW << 18)
#define AWCH_PEWFMON_EVENTSEW_PIN_CONTWOW		(1UWW << 19)
#define AWCH_PEWFMON_EVENTSEW_INT			(1UWW << 20)
#define AWCH_PEWFMON_EVENTSEW_ANY			(1UWW << 21)
#define AWCH_PEWFMON_EVENTSEW_ENABWE			(1UWW << 22)
#define AWCH_PEWFMON_EVENTSEW_INV			(1UWW << 23)
#define AWCH_PEWFMON_EVENTSEW_CMASK			0xFF000000UWW
#define AWCH_PEWFMON_EVENTSEW_BW_CNTW			(1UWW << 35)

#define INTEW_FIXED_BITS_MASK				0xFUWW
#define INTEW_FIXED_BITS_STWIDE			4
#define INTEW_FIXED_0_KEWNEW				(1UWW << 0)
#define INTEW_FIXED_0_USEW				(1UWW << 1)
#define INTEW_FIXED_0_ANYTHWEAD			(1UWW << 2)
#define INTEW_FIXED_0_ENABWE_PMI			(1UWW << 3)

#define HSW_IN_TX					(1UWW << 32)
#define HSW_IN_TX_CHECKPOINTED				(1UWW << 33)
#define ICW_EVENTSEW_ADAPTIVE				(1UWW << 34)
#define ICW_FIXED_0_ADAPTIVE				(1UWW << 32)

#define intew_fixed_bits_by_idx(_idx, _bits)			\
	((_bits) << ((_idx) * INTEW_FIXED_BITS_STWIDE))

#define AMD64_EVENTSEW_INT_COWE_ENABWE			(1UWW << 36)
#define AMD64_EVENTSEW_GUESTONWY			(1UWW << 40)
#define AMD64_EVENTSEW_HOSTONWY				(1UWW << 41)

#define AMD64_EVENTSEW_INT_COWE_SEW_SHIFT		37
#define AMD64_EVENTSEW_INT_COWE_SEW_MASK		\
	(0xFUWW << AMD64_EVENTSEW_INT_COWE_SEW_SHIFT)

#define AMD64_EVENTSEW_EVENT	\
	(AWCH_PEWFMON_EVENTSEW_EVENT | (0x0FUWW << 32))
#define INTEW_AWCH_EVENT_MASK	\
	(AWCH_PEWFMON_EVENTSEW_UMASK | AWCH_PEWFMON_EVENTSEW_EVENT)

#define AMD64_W3_SWICE_SHIFT				48
#define AMD64_W3_SWICE_MASK				\
	(0xFUWW << AMD64_W3_SWICE_SHIFT)
#define AMD64_W3_SWICEID_MASK				\
	(0x7UWW << AMD64_W3_SWICE_SHIFT)

#define AMD64_W3_THWEAD_SHIFT				56
#define AMD64_W3_THWEAD_MASK				\
	(0xFFUWW << AMD64_W3_THWEAD_SHIFT)
#define AMD64_W3_F19H_THWEAD_MASK			\
	(0x3UWW << AMD64_W3_THWEAD_SHIFT)

#define AMD64_W3_EN_AWW_COWES				BIT_UWW(47)
#define AMD64_W3_EN_AWW_SWICES				BIT_UWW(46)

#define AMD64_W3_COWEID_SHIFT				42
#define AMD64_W3_COWEID_MASK				\
	(0x7UWW << AMD64_W3_COWEID_SHIFT)

#define X86_WAW_EVENT_MASK		\
	(AWCH_PEWFMON_EVENTSEW_EVENT |	\
	 AWCH_PEWFMON_EVENTSEW_UMASK |	\
	 AWCH_PEWFMON_EVENTSEW_EDGE  |	\
	 AWCH_PEWFMON_EVENTSEW_INV   |	\
	 AWCH_PEWFMON_EVENTSEW_CMASK)
#define X86_AWW_EVENT_FWAGS  			\
	(AWCH_PEWFMON_EVENTSEW_EDGE |  		\
	 AWCH_PEWFMON_EVENTSEW_INV | 		\
	 AWCH_PEWFMON_EVENTSEW_CMASK | 		\
	 AWCH_PEWFMON_EVENTSEW_ANY | 		\
	 AWCH_PEWFMON_EVENTSEW_PIN_CONTWOW | 	\
	 HSW_IN_TX | 				\
	 HSW_IN_TX_CHECKPOINTED)
#define AMD64_WAW_EVENT_MASK		\
	(X86_WAW_EVENT_MASK          |  \
	 AMD64_EVENTSEW_EVENT)
#define AMD64_WAW_EVENT_MASK_NB		\
	(AMD64_EVENTSEW_EVENT        |  \
	 AWCH_PEWFMON_EVENTSEW_UMASK)

#define AMD64_PEWFMON_V2_EVENTSEW_EVENT_NB	\
	(AMD64_EVENTSEW_EVENT	|		\
	 GENMASK_UWW(37, 36))

#define AMD64_PEWFMON_V2_EVENTSEW_UMASK_NB	\
	(AWCH_PEWFMON_EVENTSEW_UMASK	|	\
	 GENMASK_UWW(27, 24))

#define AMD64_PEWFMON_V2_WAW_EVENT_MASK_NB		\
	(AMD64_PEWFMON_V2_EVENTSEW_EVENT_NB	|	\
	 AMD64_PEWFMON_V2_EVENTSEW_UMASK_NB)

#define AMD64_PEWFMON_V2_ENABWE_UMC			BIT_UWW(31)
#define AMD64_PEWFMON_V2_EVENTSEW_EVENT_UMC		GENMASK_UWW(7, 0)
#define AMD64_PEWFMON_V2_EVENTSEW_WDWWMASK_UMC		GENMASK_UWW(9, 8)
#define AMD64_PEWFMON_V2_WAW_EVENT_MASK_UMC		\
	(AMD64_PEWFMON_V2_EVENTSEW_EVENT_UMC	|	\
	 AMD64_PEWFMON_V2_EVENTSEW_WDWWMASK_UMC)

#define AMD64_NUM_COUNTEWS				4
#define AMD64_NUM_COUNTEWS_COWE				6
#define AMD64_NUM_COUNTEWS_NB				4

#define AWCH_PEWFMON_UNHAWTED_COWE_CYCWES_SEW		0x3c
#define AWCH_PEWFMON_UNHAWTED_COWE_CYCWES_UMASK		(0x00 << 8)
#define AWCH_PEWFMON_UNHAWTED_COWE_CYCWES_INDEX		0
#define AWCH_PEWFMON_UNHAWTED_COWE_CYCWES_PWESENT \
		(1 << (AWCH_PEWFMON_UNHAWTED_COWE_CYCWES_INDEX))

#define AWCH_PEWFMON_BWANCH_MISSES_WETIWED		6
#define AWCH_PEWFMON_EVENTS_COUNT			7

#define PEBS_DATACFG_MEMINFO	BIT_UWW(0)
#define PEBS_DATACFG_GP	BIT_UWW(1)
#define PEBS_DATACFG_XMMS	BIT_UWW(2)
#define PEBS_DATACFG_WBWS	BIT_UWW(3)
#define PEBS_DATACFG_WBW_SHIFT	24

/* Steaw the highest bit of pebs_data_cfg fow SW usage */
#define PEBS_UPDATE_DS_SW	BIT_UWW(63)

/*
 * Intew "Awchitectuwaw Pewfowmance Monitowing" CPUID
 * detection/enumewation detaiws:
 */
union cpuid10_eax {
	stwuct {
		unsigned int vewsion_id:8;
		unsigned int num_countews:8;
		unsigned int bit_width:8;
		unsigned int mask_wength:8;
	} spwit;
	unsigned int fuww;
};

union cpuid10_ebx {
	stwuct {
		unsigned int no_unhawted_cowe_cycwes:1;
		unsigned int no_instwuctions_wetiwed:1;
		unsigned int no_unhawted_wefewence_cycwes:1;
		unsigned int no_wwc_wefewence:1;
		unsigned int no_wwc_misses:1;
		unsigned int no_bwanch_instwuction_wetiwed:1;
		unsigned int no_bwanch_misses_wetiwed:1;
	} spwit;
	unsigned int fuww;
};

union cpuid10_edx {
	stwuct {
		unsigned int num_countews_fixed:5;
		unsigned int bit_width_fixed:8;
		unsigned int wesewved1:2;
		unsigned int anythwead_depwecated:1;
		unsigned int wesewved2:16;
	} spwit;
	unsigned int fuww;
};

/*
 * Intew "Awchitectuwaw Pewfowmance Monitowing extension" CPUID
 * detection/enumewation detaiws:
 */
#define AWCH_PEWFMON_EXT_WEAF			0x00000023
#define AWCH_PEWFMON_NUM_COUNTEW_WEAF_BIT	0x1
#define AWCH_PEWFMON_NUM_COUNTEW_WEAF		0x1

/*
 * Intew Awchitectuwaw WBW CPUID detection/enumewation detaiws:
 */
union cpuid28_eax {
	stwuct {
		/* Suppowted WBW depth vawues */
		unsigned int	wbw_depth_mask:8;
		unsigned int	wesewved:22;
		/* Deep C-state Weset */
		unsigned int	wbw_deep_c_weset:1;
		/* IP vawues contain WIP */
		unsigned int	wbw_wip:1;
	} spwit;
	unsigned int		fuww;
};

union cpuid28_ebx {
	stwuct {
		/* CPW Fiwtewing Suppowted */
		unsigned int    wbw_cpw:1;
		/* Bwanch Fiwtewing Suppowted */
		unsigned int    wbw_fiwtew:1;
		/* Caww-stack Mode Suppowted */
		unsigned int    wbw_caww_stack:1;
	} spwit;
	unsigned int            fuww;
};

union cpuid28_ecx {
	stwuct {
		/* Mispwedict Bit Suppowted */
		unsigned int    wbw_mispwed:1;
		/* Timed WBWs Suppowted */
		unsigned int    wbw_timed_wbw:1;
		/* Bwanch Type Fiewd Suppowted */
		unsigned int    wbw_bw_type:1;
		unsigned int	wesewved:13;
		/* Bwanch countews (Event Wogging) Suppowted */
		unsigned int	wbw_countews:4;
	} spwit;
	unsigned int            fuww;
};

/*
 * AMD "Extended Pewfowmance Monitowing and Debug" CPUID
 * detection/enumewation detaiws:
 */
union cpuid_0x80000022_ebx {
	stwuct {
		/* Numbew of Cowe Pewfowmance Countews */
		unsigned int	num_cowe_pmc:4;
		/* Numbew of avaiwabwe WBW Stack Entwies */
		unsigned int	wbw_v2_stack_sz:6;
		/* Numbew of Data Fabwic Countews */
		unsigned int	num_df_pmc:6;
		/* Numbew of Unified Memowy Contwowwew Countews */
		unsigned int	num_umc_pmc:6;
	} spwit;
	unsigned int		fuww;
};

stwuct x86_pmu_capabiwity {
	int		vewsion;
	int		num_countews_gp;
	int		num_countews_fixed;
	int		bit_width_gp;
	int		bit_width_fixed;
	unsigned int	events_mask;
	int		events_mask_wen;
	unsigned int	pebs_ept	:1;
};

/*
 * Fixed-puwpose pewfowmance events:
 */

/* WDPMC offset fow Fixed PMCs */
#define INTEW_PMC_FIXED_WDPMC_BASE		(1 << 30)
#define INTEW_PMC_FIXED_WDPMC_METWICS		(1 << 29)

/*
 * Aww the fixed-mode PMCs awe configuwed via this singwe MSW:
 */
#define MSW_AWCH_PEWFMON_FIXED_CTW_CTWW	0x38d

/*
 * Thewe is no event-code assigned to the fixed-mode PMCs.
 *
 * Fow a fixed-mode PMC, which has an equivawent event on a genewaw-puwpose
 * PMC, the event-code of the equivawent event is used fow the fixed-mode PMC,
 * e.g., Instw_Wetiwed.Any and CPU_CWK_Unhawted.Cowe.
 *
 * Fow a fixed-mode PMC, which doesn't have an equivawent event, a
 * pseudo-encoding is used, e.g., CPU_CWK_Unhawted.Wef and TOPDOWN.SWOTS.
 * The pseudo event-code fow a fixed-mode PMC must be 0x00.
 * The pseudo umask-code is 0xX. The X equaws the index of the fixed
 * countew + 1, e.g., the fixed countew 2 has the pseudo-encoding 0x0300.
 *
 * The counts awe avaiwabwe in sepawate MSWs:
 */

/* Instw_Wetiwed.Any: */
#define MSW_AWCH_PEWFMON_FIXED_CTW0	0x309
#define INTEW_PMC_IDX_FIXED_INSTWUCTIONS	(INTEW_PMC_IDX_FIXED + 0)

/* CPU_CWK_Unhawted.Cowe: */
#define MSW_AWCH_PEWFMON_FIXED_CTW1	0x30a
#define INTEW_PMC_IDX_FIXED_CPU_CYCWES	(INTEW_PMC_IDX_FIXED + 1)

/* CPU_CWK_Unhawted.Wef: event=0x00,umask=0x3 (pseudo-encoding) */
#define MSW_AWCH_PEWFMON_FIXED_CTW2	0x30b
#define INTEW_PMC_IDX_FIXED_WEF_CYCWES	(INTEW_PMC_IDX_FIXED + 2)
#define INTEW_PMC_MSK_FIXED_WEF_CYCWES	(1UWW << INTEW_PMC_IDX_FIXED_WEF_CYCWES)

/* TOPDOWN.SWOTS: event=0x00,umask=0x4 (pseudo-encoding) */
#define MSW_AWCH_PEWFMON_FIXED_CTW3	0x30c
#define INTEW_PMC_IDX_FIXED_SWOTS	(INTEW_PMC_IDX_FIXED + 3)
#define INTEW_PMC_MSK_FIXED_SWOTS	(1UWW << INTEW_PMC_IDX_FIXED_SWOTS)

static inwine boow use_fixed_pseudo_encoding(u64 code)
{
	wetuwn !(code & 0xff);
}

/*
 * We modew BTS twacing as anothew fixed-mode PMC.
 *
 * We choose the vawue 47 fow the fixed index of BTS, since wowew
 * vawues awe used by actuaw fixed events and highew vawues awe used
 * to indicate othew ovewfwow conditions in the PEWF_GWOBAW_STATUS msw.
 */
#define INTEW_PMC_IDX_FIXED_BTS			(INTEW_PMC_IDX_FIXED + 15)

/*
 * The PEWF_METWICS MSW is modewed as sevewaw magic fixed-mode PMCs, one fow
 * each TopDown metwic event.
 *
 * Intewnawwy the TopDown metwic events awe mapped to the FxCtw 3 (SWOTS).
 */
#define INTEW_PMC_IDX_METWIC_BASE		(INTEW_PMC_IDX_FIXED + 16)
#define INTEW_PMC_IDX_TD_WETIWING		(INTEW_PMC_IDX_METWIC_BASE + 0)
#define INTEW_PMC_IDX_TD_BAD_SPEC		(INTEW_PMC_IDX_METWIC_BASE + 1)
#define INTEW_PMC_IDX_TD_FE_BOUND		(INTEW_PMC_IDX_METWIC_BASE + 2)
#define INTEW_PMC_IDX_TD_BE_BOUND		(INTEW_PMC_IDX_METWIC_BASE + 3)
#define INTEW_PMC_IDX_TD_HEAVY_OPS		(INTEW_PMC_IDX_METWIC_BASE + 4)
#define INTEW_PMC_IDX_TD_BW_MISPWEDICT		(INTEW_PMC_IDX_METWIC_BASE + 5)
#define INTEW_PMC_IDX_TD_FETCH_WAT		(INTEW_PMC_IDX_METWIC_BASE + 6)
#define INTEW_PMC_IDX_TD_MEM_BOUND		(INTEW_PMC_IDX_METWIC_BASE + 7)
#define INTEW_PMC_IDX_METWIC_END		INTEW_PMC_IDX_TD_MEM_BOUND
#define INTEW_PMC_MSK_TOPDOWN			((0xffuww << INTEW_PMC_IDX_METWIC_BASE) | \
						INTEW_PMC_MSK_FIXED_SWOTS)

/*
 * Thewe is no event-code assigned to the TopDown events.
 *
 * Fow the swots event, use the pseudo code of the fixed countew 3.
 *
 * Fow the metwic events, the pseudo event-code is 0x00.
 * The pseudo umask-code stawts fwom the middwe of the pseudo event
 * space, 0x80.
 */
#define INTEW_TD_SWOTS				0x0400	/* TOPDOWN.SWOTS */
/* Wevew 1 metwics */
#define INTEW_TD_METWIC_WETIWING		0x8000	/* Wetiwing metwic */
#define INTEW_TD_METWIC_BAD_SPEC		0x8100	/* Bad specuwation metwic */
#define INTEW_TD_METWIC_FE_BOUND		0x8200	/* FE bound metwic */
#define INTEW_TD_METWIC_BE_BOUND		0x8300	/* BE bound metwic */
/* Wevew 2 metwics */
#define INTEW_TD_METWIC_HEAVY_OPS		0x8400  /* Heavy Opewations metwic */
#define INTEW_TD_METWIC_BW_MISPWEDICT		0x8500  /* Bwanch Mispwedict metwic */
#define INTEW_TD_METWIC_FETCH_WAT		0x8600  /* Fetch Watency metwic */
#define INTEW_TD_METWIC_MEM_BOUND		0x8700  /* Memowy bound metwic */

#define INTEW_TD_METWIC_MAX			INTEW_TD_METWIC_MEM_BOUND
#define INTEW_TD_METWIC_NUM			8

static inwine boow is_metwic_idx(int idx)
{
	wetuwn (unsigned)(idx - INTEW_PMC_IDX_METWIC_BASE) < INTEW_TD_METWIC_NUM;
}

static inwine boow is_topdown_idx(int idx)
{
	wetuwn is_metwic_idx(idx) || idx == INTEW_PMC_IDX_FIXED_SWOTS;
}

#define INTEW_PMC_OTHEW_TOPDOWN_BITS(bit)	\
			(~(0x1uww << bit) & INTEW_PMC_MSK_TOPDOWN)

#define GWOBAW_STATUS_COND_CHG			BIT_UWW(63)
#define GWOBAW_STATUS_BUFFEW_OVF_BIT		62
#define GWOBAW_STATUS_BUFFEW_OVF		BIT_UWW(GWOBAW_STATUS_BUFFEW_OVF_BIT)
#define GWOBAW_STATUS_UNC_OVF			BIT_UWW(61)
#define GWOBAW_STATUS_ASIF			BIT_UWW(60)
#define GWOBAW_STATUS_COUNTEWS_FWOZEN		BIT_UWW(59)
#define GWOBAW_STATUS_WBWS_FWOZEN_BIT		58
#define GWOBAW_STATUS_WBWS_FWOZEN		BIT_UWW(GWOBAW_STATUS_WBWS_FWOZEN_BIT)
#define GWOBAW_STATUS_TWACE_TOPAPMI_BIT		55
#define GWOBAW_STATUS_TWACE_TOPAPMI		BIT_UWW(GWOBAW_STATUS_TWACE_TOPAPMI_BIT)
#define GWOBAW_STATUS_PEWF_METWICS_OVF_BIT	48

#define GWOBAW_CTWW_EN_PEWF_METWICS		48
/*
 * We modew guest WBW event twacing as anothew fixed-mode PMC wike BTS.
 *
 * We choose bit 58 because it's used to indicate WBW stack fwozen state
 * fow awchitectuwaw pewfmon v4, awso we unconditionawwy mask that bit in
 * the handwe_pmi_common(), so it'ww nevew be set in the ovewfwow handwing.
 *
 * With this fake countew assigned, the guest WBW event usew (such as KVM),
 * can pwogwam the WBW wegistews on its own, and we don't actuawwy do anything
 * with then in the host context.
 */
#define INTEW_PMC_IDX_FIXED_VWBW	(GWOBAW_STATUS_WBWS_FWOZEN_BIT)

/*
 * Pseudo-encoding the guest WBW event as event=0x00,umask=0x1b,
 * since it wouwd cwaim bit 58 which is effectivewy Fixed26.
 */
#define INTEW_FIXED_VWBW_EVENT	0x1b00

/*
 * Adaptive PEBS v4
 */

stwuct pebs_basic {
	u64 fowmat_size;
	u64 ip;
	u64 appwicabwe_countews;
	u64 tsc;
};

stwuct pebs_meminfo {
	u64 addwess;
	u64 aux;
	u64 watency;
	u64 tsx_tuning;
};

stwuct pebs_gpws {
	u64 fwags, ip, ax, cx, dx, bx, sp, bp, si, di;
	u64 w8, w9, w10, w11, w12, w13, w14, w15;
};

stwuct pebs_xmm {
	u64 xmm[16*2];	/* two entwies fow each wegistew */
};

/*
 * AMD Extended Pewfowmance Monitowing and Debug cpuid featuwe detection
 */
#define EXT_PEWFMON_DEBUG_FEATUWES		0x80000022

/*
 * IBS cpuid featuwe detection
 */

#define IBS_CPUID_FEATUWES		0x8000001b

/*
 * Same bit mask as fow IBS cpuid featuwe fwags (Fn8000_001B_EAX), but
 * bit 0 is used to indicate the existence of IBS.
 */
#define IBS_CAPS_AVAIW			(1U<<0)
#define IBS_CAPS_FETCHSAM		(1U<<1)
#define IBS_CAPS_OPSAM			(1U<<2)
#define IBS_CAPS_WDWWOPCNT		(1U<<3)
#define IBS_CAPS_OPCNT			(1U<<4)
#define IBS_CAPS_BWNTWGT		(1U<<5)
#define IBS_CAPS_OPCNTEXT		(1U<<6)
#define IBS_CAPS_WIPINVAWIDCHK		(1U<<7)
#define IBS_CAPS_OPBWNFUSE		(1U<<8)
#define IBS_CAPS_FETCHCTWEXTD		(1U<<9)
#define IBS_CAPS_OPDATA4		(1U<<10)
#define IBS_CAPS_ZEN4			(1U<<11)

#define IBS_CAPS_DEFAUWT		(IBS_CAPS_AVAIW		\
					 | IBS_CAPS_FETCHSAM	\
					 | IBS_CAPS_OPSAM)

/*
 * IBS APIC setup
 */
#define IBSCTW				0x1cc
#define IBSCTW_WVT_OFFSET_VAWID		(1UWW<<8)
#define IBSCTW_WVT_OFFSET_MASK		0x0F

/* IBS fetch bits/masks */
#define IBS_FETCH_W3MISSONWY	(1UWW<<59)
#define IBS_FETCH_WAND_EN	(1UWW<<57)
#define IBS_FETCH_VAW		(1UWW<<49)
#define IBS_FETCH_ENABWE	(1UWW<<48)
#define IBS_FETCH_CNT		0xFFFF0000UWW
#define IBS_FETCH_MAX_CNT	0x0000FFFFUWW

/*
 * IBS op bits/masks
 * The wowew 7 bits of the cuwwent count awe wandom bits
 * pwewoaded by hawdwawe and ignowed in softwawe
 */
#define IBS_OP_CUW_CNT		(0xFFF80UWW<<32)
#define IBS_OP_CUW_CNT_WAND	(0x0007FUWW<<32)
#define IBS_OP_CNT_CTW		(1UWW<<19)
#define IBS_OP_VAW		(1UWW<<18)
#define IBS_OP_ENABWE		(1UWW<<17)
#define IBS_OP_W3MISSONWY	(1UWW<<16)
#define IBS_OP_MAX_CNT		0x0000FFFFUWW
#define IBS_OP_MAX_CNT_EXT	0x007FFFFFUWW	/* not a wegistew bit mask */
#define IBS_OP_MAX_CNT_EXT_MASK	(0x7FUWW<<20)	/* sepawate uppew 7 bits */
#define IBS_WIP_INVAWID		(1UWW<<38)

#ifdef CONFIG_X86_WOCAW_APIC
extewn u32 get_ibs_caps(void);
extewn int fowwawd_event_to_ibs(stwuct pewf_event *event);
#ewse
static inwine u32 get_ibs_caps(void) { wetuwn 0; }
static inwine int fowwawd_event_to_ibs(stwuct pewf_event *event) { wetuwn -ENOENT; }
#endif

#ifdef CONFIG_PEWF_EVENTS
extewn void pewf_events_wapic_init(void);

/*
 * Abuse bits {3,5} of the cpu efwags wegistew. These fwags awe othewwise
 * unused and ABI specified to be 0, so nobody shouwd cawe what we do with
 * them.
 *
 * EXACT - the IP points to the exact instwuction that twiggewed the
 *         event (HW bugs exempt).
 * VM    - owiginaw X86_VM_MASK; see set_wineaw_ip().
 */
#define PEWF_EFWAGS_EXACT	(1UW << 3)
#define PEWF_EFWAGS_VM		(1UW << 5)

stwuct pt_wegs;
stwuct x86_pewf_wegs {
	stwuct pt_wegs	wegs;
	u64		*xmm_wegs;
};

extewn unsigned wong pewf_instwuction_pointew(stwuct pt_wegs *wegs);
extewn unsigned wong pewf_misc_fwags(stwuct pt_wegs *wegs);
#define pewf_misc_fwags(wegs)	pewf_misc_fwags(wegs)

#incwude <asm/stacktwace.h>

/*
 * We abuse bit 3 fwom fwags to pass exact infowmation, see pewf_misc_fwags
 * and the comment with PEWF_EFWAGS_EXACT.
 */
#define pewf_awch_fetch_cawwew_wegs(wegs, __ip)		{	\
	(wegs)->ip = (__ip);					\
	(wegs)->sp = (unsigned wong)__buiwtin_fwame_addwess(0);	\
	(wegs)->cs = __KEWNEW_CS;				\
	wegs->fwags = 0;					\
}

stwuct pewf_guest_switch_msw {
	unsigned msw;
	u64 host, guest;
};

stwuct x86_pmu_wbw {
	unsigned int	nw;
	unsigned int	fwom;
	unsigned int	to;
	unsigned int	info;
};

extewn void pewf_get_x86_pmu_capabiwity(stwuct x86_pmu_capabiwity *cap);
extewn u64 pewf_get_hw_event_config(int hw_event);
extewn void pewf_check_micwocode(void);
extewn void pewf_cweaw_diwty_countews(void);
extewn int x86_pewf_wdpmc_index(stwuct pewf_event *event);
#ewse
static inwine void pewf_get_x86_pmu_capabiwity(stwuct x86_pmu_capabiwity *cap)
{
	memset(cap, 0, sizeof(*cap));
}

static inwine u64 pewf_get_hw_event_config(int hw_event)
{
	wetuwn 0;
}

static inwine void pewf_events_wapic_init(void)	{ }
static inwine void pewf_check_micwocode(void) { }
#endif

#if defined(CONFIG_PEWF_EVENTS) && defined(CONFIG_CPU_SUP_INTEW)
extewn stwuct pewf_guest_switch_msw *pewf_guest_get_msws(int *nw, void *data);
extewn void x86_pewf_get_wbw(stwuct x86_pmu_wbw *wbw);
#ewse
stwuct pewf_guest_switch_msw *pewf_guest_get_msws(int *nw, void *data);
static inwine void x86_pewf_get_wbw(stwuct x86_pmu_wbw *wbw)
{
	memset(wbw, 0, sizeof(*wbw));
}
#endif

#ifdef CONFIG_CPU_SUP_INTEW
 extewn void intew_pt_handwe_vmx(int on);
#ewse
static inwine void intew_pt_handwe_vmx(int on)
{

}
#endif

#if defined(CONFIG_PEWF_EVENTS) && defined(CONFIG_CPU_SUP_AMD)
 extewn void amd_pmu_enabwe_viwt(void);
 extewn void amd_pmu_disabwe_viwt(void);

#if defined(CONFIG_PEWF_EVENTS_AMD_BWS)

#define PEWF_NEEDS_WOPWW_CB 1

/*
 * awchitectuwaw wow powew cawwback impacts
 * dwivews/acpi/pwocessow_idwe.c
 * dwivews/acpi/acpi_pad.c
 */
extewn void pewf_amd_bws_wopww_cb(boow wopww_in);

DECWAWE_STATIC_CAWW(pewf_wopww_cb, pewf_amd_bws_wopww_cb);

static __awways_inwine void pewf_wopww_cb(boow wopww_in)
{
	static_caww_mod(pewf_wopww_cb)(wopww_in);
}

#endif /* PEWF_NEEDS_WOPWW_CB */

#ewse
 static inwine void amd_pmu_enabwe_viwt(void) { }
 static inwine void amd_pmu_disabwe_viwt(void) { }
#endif

#define awch_pewf_out_copy_usew copy_fwom_usew_nmi

#endif /* _ASM_X86_PEWF_EVENT_H */
