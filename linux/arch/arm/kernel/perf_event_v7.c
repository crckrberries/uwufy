// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWMv7 Cowtex-A8 and Cowtex-A9 Pewfowmance Events handwing code.
 *
 * AWMv7 suppowt: Jean Pihet <jpihet@mvista.com>
 * 2010 (c) MontaVista Softwawe, WWC.
 *
 * Copied fwom AWMv6 code, with the wow wevew code inspiwed
 *  by the AWMv7 Opwofiwe code.
 *
 * Cowtex-A8 has up to 4 configuwabwe pewfowmance countews and
 *  a singwe cycwe countew.
 * Cowtex-A9 has up to 31 configuwabwe pewfowmance countews and
 *  a singwe cycwe countew.
 *
 * Aww countews can be enabwed/disabwed and IWQ masked sepawatewy. The cycwe
 *  countew and aww 4 pewfowmance countews togethew can be weset sepawatewy.
 */

#ifdef CONFIG_CPU_V7

#incwude <asm/cp15.h>
#incwude <asm/cputype.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/vfp.h>
#incwude "../vfp/vfpinstw.h"

#incwude <winux/of.h>
#incwude <winux/pewf/awm_pmu.h>
#incwude <winux/pwatfowm_device.h>

/*
 * Common AWMv7 event types
 *
 * Note: An impwementation may not be abwe to count aww of these events
 * but the encodings awe considewed to be `wesewved' in the case that
 * they awe not avaiwabwe.
 */
#define AWMV7_PEWFCTW_PMNC_SW_INCW			0x00
#define AWMV7_PEWFCTW_W1_ICACHE_WEFIWW			0x01
#define AWMV7_PEWFCTW_ITWB_WEFIWW			0x02
#define AWMV7_PEWFCTW_W1_DCACHE_WEFIWW			0x03
#define AWMV7_PEWFCTW_W1_DCACHE_ACCESS			0x04
#define AWMV7_PEWFCTW_DTWB_WEFIWW			0x05
#define AWMV7_PEWFCTW_MEM_WEAD				0x06
#define AWMV7_PEWFCTW_MEM_WWITE				0x07
#define AWMV7_PEWFCTW_INSTW_EXECUTED			0x08
#define AWMV7_PEWFCTW_EXC_TAKEN				0x09
#define AWMV7_PEWFCTW_EXC_EXECUTED			0x0A
#define AWMV7_PEWFCTW_CID_WWITE				0x0B

/*
 * AWMV7_PEWFCTW_PC_WWITE is equivawent to HW_BWANCH_INSTWUCTIONS.
 * It counts:
 *  - aww (taken) bwanch instwuctions,
 *  - instwuctions that expwicitwy wwite the PC,
 *  - exception genewating instwuctions.
 */
#define AWMV7_PEWFCTW_PC_WWITE				0x0C
#define AWMV7_PEWFCTW_PC_IMM_BWANCH			0x0D
#define AWMV7_PEWFCTW_PC_PWOC_WETUWN			0x0E
#define AWMV7_PEWFCTW_MEM_UNAWIGNED_ACCESS		0x0F
#define AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED		0x10
#define AWMV7_PEWFCTW_CWOCK_CYCWES			0x11
#define AWMV7_PEWFCTW_PC_BWANCH_PWED			0x12

/* These events awe defined by the PMUv2 suppwement (AWM DDI 0457A). */
#define AWMV7_PEWFCTW_MEM_ACCESS			0x13
#define AWMV7_PEWFCTW_W1_ICACHE_ACCESS			0x14
#define AWMV7_PEWFCTW_W1_DCACHE_WB			0x15
#define AWMV7_PEWFCTW_W2_CACHE_ACCESS			0x16
#define AWMV7_PEWFCTW_W2_CACHE_WEFIWW			0x17
#define AWMV7_PEWFCTW_W2_CACHE_WB			0x18
#define AWMV7_PEWFCTW_BUS_ACCESS			0x19
#define AWMV7_PEWFCTW_MEM_EWWOW				0x1A
#define AWMV7_PEWFCTW_INSTW_SPEC			0x1B
#define AWMV7_PEWFCTW_TTBW_WWITE			0x1C
#define AWMV7_PEWFCTW_BUS_CYCWES			0x1D

#define AWMV7_PEWFCTW_CPU_CYCWES			0xFF

/* AWMv7 Cowtex-A8 specific event types */
#define AWMV7_A8_PEWFCTW_W2_CACHE_ACCESS		0x43
#define AWMV7_A8_PEWFCTW_W2_CACHE_WEFIWW		0x44
#define AWMV7_A8_PEWFCTW_W1_ICACHE_ACCESS		0x50
#define AWMV7_A8_PEWFCTW_STAWW_ISIDE			0x56

/* AWMv7 Cowtex-A9 specific event types */
#define AWMV7_A9_PEWFCTW_INSTW_COWE_WENAME		0x68
#define AWMV7_A9_PEWFCTW_STAWW_ICACHE			0x60
#define AWMV7_A9_PEWFCTW_STAWW_DISPATCH			0x66

/* AWMv7 Cowtex-A5 specific event types */
#define AWMV7_A5_PEWFCTW_PWEFETCH_WINEFIWW		0xc2
#define AWMV7_A5_PEWFCTW_PWEFETCH_WINEFIWW_DWOP		0xc3

/* AWMv7 Cowtex-A15 specific event types */
#define AWMV7_A15_PEWFCTW_W1_DCACHE_ACCESS_WEAD		0x40
#define AWMV7_A15_PEWFCTW_W1_DCACHE_ACCESS_WWITE	0x41
#define AWMV7_A15_PEWFCTW_W1_DCACHE_WEFIWW_WEAD		0x42
#define AWMV7_A15_PEWFCTW_W1_DCACHE_WEFIWW_WWITE	0x43

#define AWMV7_A15_PEWFCTW_DTWB_WEFIWW_W1_WEAD		0x4C
#define AWMV7_A15_PEWFCTW_DTWB_WEFIWW_W1_WWITE		0x4D

#define AWMV7_A15_PEWFCTW_W2_CACHE_ACCESS_WEAD		0x50
#define AWMV7_A15_PEWFCTW_W2_CACHE_ACCESS_WWITE		0x51
#define AWMV7_A15_PEWFCTW_W2_CACHE_WEFIWW_WEAD		0x52
#define AWMV7_A15_PEWFCTW_W2_CACHE_WEFIWW_WWITE		0x53

#define AWMV7_A15_PEWFCTW_PC_WWITE_SPEC			0x76

/* AWMv7 Cowtex-A12 specific event types */
#define AWMV7_A12_PEWFCTW_W1_DCACHE_ACCESS_WEAD		0x40
#define AWMV7_A12_PEWFCTW_W1_DCACHE_ACCESS_WWITE	0x41

#define AWMV7_A12_PEWFCTW_W2_CACHE_ACCESS_WEAD		0x50
#define AWMV7_A12_PEWFCTW_W2_CACHE_ACCESS_WWITE		0x51

#define AWMV7_A12_PEWFCTW_PC_WWITE_SPEC			0x76

#define AWMV7_A12_PEWFCTW_PF_TWB_WEFIWW			0xe7

/* AWMv7 Kwait specific event types */
#define KWAIT_PMWESW0_GWOUP0				0xcc
#define KWAIT_PMWESW1_GWOUP0				0xd0
#define KWAIT_PMWESW2_GWOUP0				0xd4
#define KWAIT_VPMWESW0_GWOUP0				0xd8

#define KWAIT_PEWFCTW_W1_ICACHE_ACCESS			0x10011
#define KWAIT_PEWFCTW_W1_ICACHE_MISS			0x10010

#define KWAIT_PEWFCTW_W1_ITWB_ACCESS			0x12222
#define KWAIT_PEWFCTW_W1_DTWB_ACCESS			0x12210

/* AWMv7 Scowpion specific event types */
#define SCOWPION_WPM0_GWOUP0				0x4c
#define SCOWPION_WPM1_GWOUP0				0x50
#define SCOWPION_WPM2_GWOUP0				0x54
#define SCOWPION_W2WPM_GWOUP0				0x58
#define SCOWPION_VWPM_GWOUP0				0x5c

#define SCOWPION_ICACHE_ACCESS				0x10053
#define SCOWPION_ICACHE_MISS				0x10052

#define SCOWPION_DTWB_ACCESS				0x12013
#define SCOWPION_DTWB_MISS				0x12012

#define SCOWPION_ITWB_MISS				0x12021

/*
 * Cowtex-A8 HW events mapping
 *
 * The hawdwawe events that we suppowt. We do suppowt cache opewations but
 * we have hawvawd caches and no way to combine instwuction and data
 * accesses/misses in hawdwawe.
 */
static const unsigned awmv7_a8_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]		= AWMV7_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= AWMV7_PEWFCTW_INSTW_EXECUTED,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[PEWF_COUNT_HW_CACHE_MISSES]		= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= AWMV7_PEWFCTW_PC_WWITE,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND]	= AWMV7_A8_PEWFCTW_STAWW_ISIDE,
};

static const unsigned awmv7_a8_pewf_cache_map[PEWF_COUNT_HW_CACHE_MAX]
					  [PEWF_COUNT_HW_CACHE_OP_MAX]
					  [PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	PEWF_CACHE_MAP_AWW_UNSUPPOWTED,

	/*
	 * The pewfowmance countews don't diffewentiate between wead and wwite
	 * accesses/misses so this isn't stwictwy cowwect, but it's the best we
	 * can do. Wwites and weads get combined.
	 */
	[C(W1D)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,

	[C(W1I)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_A8_PEWFCTW_W1_ICACHE_ACCESS,
	[C(W1I)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_ICACHE_WEFIWW,

	[C(WW)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_A8_PEWFCTW_W2_CACHE_ACCESS,
	[C(WW)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_A8_PEWFCTW_W2_CACHE_WEFIWW,
	[C(WW)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_A8_PEWFCTW_W2_CACHE_ACCESS,
	[C(WW)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_A8_PEWFCTW_W2_CACHE_WEFIWW,

	[C(DTWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_DTWB_WEFIWW,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_DTWB_WEFIWW,

	[C(ITWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,
	[C(ITWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,

	[C(BPU)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
};

/*
 * Cowtex-A9 HW events mapping
 */
static const unsigned awmv7_a9_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]		= AWMV7_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= AWMV7_A9_PEWFCTW_INSTW_COWE_WENAME,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[PEWF_COUNT_HW_CACHE_MISSES]		= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= AWMV7_PEWFCTW_PC_WWITE,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND]	= AWMV7_A9_PEWFCTW_STAWW_ICACHE,
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND]	= AWMV7_A9_PEWFCTW_STAWW_DISPATCH,
};

static const unsigned awmv7_a9_pewf_cache_map[PEWF_COUNT_HW_CACHE_MAX]
					  [PEWF_COUNT_HW_CACHE_OP_MAX]
					  [PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	PEWF_CACHE_MAP_AWW_UNSUPPOWTED,

	/*
	 * The pewfowmance countews don't diffewentiate between wead and wwite
	 * accesses/misses so this isn't stwictwy cowwect, but it's the best we
	 * can do. Wwites and weads get combined.
	 */
	[C(W1D)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,

	[C(W1I)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_ICACHE_WEFIWW,

	[C(DTWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_DTWB_WEFIWW,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_DTWB_WEFIWW,

	[C(ITWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,
	[C(ITWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,

	[C(BPU)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
};

/*
 * Cowtex-A5 HW events mapping
 */
static const unsigned awmv7_a5_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]		= AWMV7_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= AWMV7_PEWFCTW_INSTW_EXECUTED,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[PEWF_COUNT_HW_CACHE_MISSES]		= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= AWMV7_PEWFCTW_PC_WWITE,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
};

static const unsigned awmv7_a5_pewf_cache_map[PEWF_COUNT_HW_CACHE_MAX]
					[PEWF_COUNT_HW_CACHE_OP_MAX]
					[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	PEWF_CACHE_MAP_AWW_UNSUPPOWTED,

	[C(W1D)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[C(W1D)][C(OP_PWEFETCH)][C(WESUWT_ACCESS)]	= AWMV7_A5_PEWFCTW_PWEFETCH_WINEFIWW,
	[C(W1D)][C(OP_PWEFETCH)][C(WESUWT_MISS)]	= AWMV7_A5_PEWFCTW_PWEFETCH_WINEFIWW_DWOP,

	[C(W1I)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_ICACHE_ACCESS,
	[C(W1I)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_ICACHE_WEFIWW,
	/*
	 * The pwefetch countews don't diffewentiate between the I side and the
	 * D side.
	 */
	[C(W1I)][C(OP_PWEFETCH)][C(WESUWT_ACCESS)]	= AWMV7_A5_PEWFCTW_PWEFETCH_WINEFIWW,
	[C(W1I)][C(OP_PWEFETCH)][C(WESUWT_MISS)]	= AWMV7_A5_PEWFCTW_PWEFETCH_WINEFIWW_DWOP,

	[C(DTWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_DTWB_WEFIWW,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_DTWB_WEFIWW,

	[C(ITWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,
	[C(ITWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,

	[C(BPU)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
};

/*
 * Cowtex-A15 HW events mapping
 */
static const unsigned awmv7_a15_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]		= AWMV7_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= AWMV7_PEWFCTW_INSTW_EXECUTED,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[PEWF_COUNT_HW_CACHE_MISSES]		= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= AWMV7_A15_PEWFCTW_PC_WWITE_SPEC,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[PEWF_COUNT_HW_BUS_CYCWES]		= AWMV7_PEWFCTW_BUS_CYCWES,
};

static const unsigned awmv7_a15_pewf_cache_map[PEWF_COUNT_HW_CACHE_MAX]
					[PEWF_COUNT_HW_CACHE_OP_MAX]
					[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	PEWF_CACHE_MAP_AWW_UNSUPPOWTED,

	[C(W1D)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_A15_PEWFCTW_W1_DCACHE_ACCESS_WEAD,
	[C(W1D)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_A15_PEWFCTW_W1_DCACHE_WEFIWW_WEAD,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_A15_PEWFCTW_W1_DCACHE_ACCESS_WWITE,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_A15_PEWFCTW_W1_DCACHE_WEFIWW_WWITE,

	/*
	 * Not aww pewfowmance countews diffewentiate between wead and wwite
	 * accesses/misses so we'we not awways stwictwy cowwect, but it's the
	 * best we can do. Wwites and weads get combined in these cases.
	 */
	[C(W1I)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_ICACHE_ACCESS,
	[C(W1I)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_ICACHE_WEFIWW,

	[C(WW)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_A15_PEWFCTW_W2_CACHE_ACCESS_WEAD,
	[C(WW)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_A15_PEWFCTW_W2_CACHE_WEFIWW_WEAD,
	[C(WW)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_A15_PEWFCTW_W2_CACHE_ACCESS_WWITE,
	[C(WW)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_A15_PEWFCTW_W2_CACHE_WEFIWW_WWITE,

	[C(DTWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_A15_PEWFCTW_DTWB_WEFIWW_W1_WEAD,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_A15_PEWFCTW_DTWB_WEFIWW_W1_WWITE,

	[C(ITWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,
	[C(ITWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,

	[C(BPU)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
};

/*
 * Cowtex-A7 HW events mapping
 */
static const unsigned awmv7_a7_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]		= AWMV7_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= AWMV7_PEWFCTW_INSTW_EXECUTED,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[PEWF_COUNT_HW_CACHE_MISSES]		= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= AWMV7_PEWFCTW_PC_WWITE,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[PEWF_COUNT_HW_BUS_CYCWES]		= AWMV7_PEWFCTW_BUS_CYCWES,
};

static const unsigned awmv7_a7_pewf_cache_map[PEWF_COUNT_HW_CACHE_MAX]
					[PEWF_COUNT_HW_CACHE_OP_MAX]
					[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	PEWF_CACHE_MAP_AWW_UNSUPPOWTED,

	/*
	 * The pewfowmance countews don't diffewentiate between wead and wwite
	 * accesses/misses so this isn't stwictwy cowwect, but it's the best we
	 * can do. Wwites and weads get combined.
	 */
	[C(W1D)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,

	[C(W1I)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_ICACHE_ACCESS,
	[C(W1I)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_ICACHE_WEFIWW,

	[C(WW)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W2_CACHE_ACCESS,
	[C(WW)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W2_CACHE_WEFIWW,
	[C(WW)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W2_CACHE_ACCESS,
	[C(WW)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W2_CACHE_WEFIWW,

	[C(DTWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_DTWB_WEFIWW,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_DTWB_WEFIWW,

	[C(ITWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,
	[C(ITWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,

	[C(BPU)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
};

/*
 * Cowtex-A12 HW events mapping
 */
static const unsigned awmv7_a12_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]		= AWMV7_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= AWMV7_PEWFCTW_INSTW_EXECUTED,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[PEWF_COUNT_HW_CACHE_MISSES]		= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= AWMV7_A12_PEWFCTW_PC_WWITE_SPEC,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[PEWF_COUNT_HW_BUS_CYCWES]		= AWMV7_PEWFCTW_BUS_CYCWES,
};

static const unsigned awmv7_a12_pewf_cache_map[PEWF_COUNT_HW_CACHE_MAX]
					[PEWF_COUNT_HW_CACHE_OP_MAX]
					[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	PEWF_CACHE_MAP_AWW_UNSUPPOWTED,

	[C(W1D)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_A12_PEWFCTW_W1_DCACHE_ACCESS_WEAD,
	[C(W1D)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_A12_PEWFCTW_W1_DCACHE_ACCESS_WWITE,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,

	/*
	 * Not aww pewfowmance countews diffewentiate between wead and wwite
	 * accesses/misses so we'we not awways stwictwy cowwect, but it's the
	 * best we can do. Wwites and weads get combined in these cases.
	 */
	[C(W1I)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_ICACHE_ACCESS,
	[C(W1I)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_ICACHE_WEFIWW,

	[C(WW)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_A12_PEWFCTW_W2_CACHE_ACCESS_WEAD,
	[C(WW)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W2_CACHE_WEFIWW,
	[C(WW)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_A12_PEWFCTW_W2_CACHE_ACCESS_WWITE,
	[C(WW)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W2_CACHE_WEFIWW,

	[C(DTWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_DTWB_WEFIWW,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_DTWB_WEFIWW,
	[C(DTWB)][C(OP_PWEFETCH)][C(WESUWT_MISS)]	= AWMV7_A12_PEWFCTW_PF_TWB_WEFIWW,

	[C(ITWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,
	[C(ITWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_ITWB_WEFIWW,

	[C(BPU)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
};

/*
 * Kwait HW events mapping
 */
static const unsigned kwait_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]	    = AWMV7_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]	    = AWMV7_PEWFCTW_INSTW_EXECUTED,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = AWMV7_PEWFCTW_PC_WWITE,
	[PEWF_COUNT_HW_BWANCH_MISSES]	    = AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[PEWF_COUNT_HW_BUS_CYCWES]	    = AWMV7_PEWFCTW_CWOCK_CYCWES,
};

static const unsigned kwait_pewf_map_no_bwanch[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]	    = AWMV7_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]	    = AWMV7_PEWFCTW_INSTW_EXECUTED,
	[PEWF_COUNT_HW_BWANCH_MISSES]	    = AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[PEWF_COUNT_HW_BUS_CYCWES]	    = AWMV7_PEWFCTW_CWOCK_CYCWES,
};

static const unsigned kwait_pewf_cache_map[PEWF_COUNT_HW_CACHE_MAX]
					  [PEWF_COUNT_HW_CACHE_OP_MAX]
					  [PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	PEWF_CACHE_MAP_AWW_UNSUPPOWTED,

	/*
	 * The pewfowmance countews don't diffewentiate between wead and wwite
	 * accesses/misses so this isn't stwictwy cowwect, but it's the best we
	 * can do. Wwites and weads get combined.
	 */
	[C(W1D)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,

	[C(W1I)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= KWAIT_PEWFCTW_W1_ICACHE_ACCESS,
	[C(W1I)][C(OP_WEAD)][C(WESUWT_MISS)]	= KWAIT_PEWFCTW_W1_ICACHE_MISS,

	[C(DTWB)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= KWAIT_PEWFCTW_W1_DTWB_ACCESS,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= KWAIT_PEWFCTW_W1_DTWB_ACCESS,

	[C(ITWB)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= KWAIT_PEWFCTW_W1_ITWB_ACCESS,
	[C(ITWB)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= KWAIT_PEWFCTW_W1_ITWB_ACCESS,

	[C(BPU)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
};

/*
 * Scowpion HW events mapping
 */
static const unsigned scowpion_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]	    = AWMV7_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]	    = AWMV7_PEWFCTW_INSTW_EXECUTED,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = AWMV7_PEWFCTW_PC_WWITE,
	[PEWF_COUNT_HW_BWANCH_MISSES]	    = AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[PEWF_COUNT_HW_BUS_CYCWES]	    = AWMV7_PEWFCTW_CWOCK_CYCWES,
};

static const unsigned scowpion_pewf_cache_map[PEWF_COUNT_HW_CACHE_MAX]
					    [PEWF_COUNT_HW_CACHE_OP_MAX]
					    [PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	PEWF_CACHE_MAP_AWW_UNSUPPOWTED,
	/*
	 * The pewfowmance countews don't diffewentiate between wead and wwite
	 * accesses/misses so this isn't stwictwy cowwect, but it's the best we
	 * can do. Wwites and weads get combined.
	 */
	[C(W1D)][C(OP_WEAD)][C(WESUWT_ACCESS)] = AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WEAD)][C(WESUWT_MISS)] = AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_ACCESS)] = AWMV7_PEWFCTW_W1_DCACHE_ACCESS,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_MISS)] = AWMV7_PEWFCTW_W1_DCACHE_WEFIWW,
	[C(W1I)][C(OP_WEAD)][C(WESUWT_ACCESS)] = SCOWPION_ICACHE_ACCESS,
	[C(W1I)][C(OP_WEAD)][C(WESUWT_MISS)] = SCOWPION_ICACHE_MISS,
	/*
	 * Onwy ITWB misses and DTWB wefiwws awe suppowted.  If usews want the
	 * DTWB wefiwws misses a waw countew must be used.
	 */
	[C(DTWB)][C(OP_WEAD)][C(WESUWT_ACCESS)] = SCOWPION_DTWB_ACCESS,
	[C(DTWB)][C(OP_WEAD)][C(WESUWT_MISS)] = SCOWPION_DTWB_MISS,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_ACCESS)] = SCOWPION_DTWB_ACCESS,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_MISS)] = SCOWPION_DTWB_MISS,
	[C(ITWB)][C(OP_WEAD)][C(WESUWT_MISS)] = SCOWPION_ITWB_MISS,
	[C(ITWB)][C(OP_WWITE)][C(WESUWT_MISS)] = SCOWPION_ITWB_MISS,
	[C(BPU)][C(OP_WEAD)][C(WESUWT_ACCESS)] = AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WEAD)][C(WESUWT_MISS)] = AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_ACCESS)] = AWMV7_PEWFCTW_PC_BWANCH_PWED,
	[C(BPU)][C(OP_WWITE)][C(WESUWT_MISS)] = AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED,
};

PMU_FOWMAT_ATTW(event, "config:0-7");

static stwuct attwibute *awmv7_pmu_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static stwuct attwibute_gwoup awmv7_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = awmv7_pmu_fowmat_attws,
};

#define AWMV7_EVENT_ATTW_WESOWVE(m) #m
#define AWMV7_EVENT_ATTW(name, config) \
	PMU_EVENT_ATTW_STWING(name, awmv7_event_attw_##name, \
			      "event=" AWMV7_EVENT_ATTW_WESOWVE(config))

AWMV7_EVENT_ATTW(sw_incw, AWMV7_PEWFCTW_PMNC_SW_INCW);
AWMV7_EVENT_ATTW(w1i_cache_wefiww, AWMV7_PEWFCTW_W1_ICACHE_WEFIWW);
AWMV7_EVENT_ATTW(w1i_twb_wefiww, AWMV7_PEWFCTW_ITWB_WEFIWW);
AWMV7_EVENT_ATTW(w1d_cache_wefiww, AWMV7_PEWFCTW_W1_DCACHE_WEFIWW);
AWMV7_EVENT_ATTW(w1d_cache, AWMV7_PEWFCTW_W1_DCACHE_ACCESS);
AWMV7_EVENT_ATTW(w1d_twb_wefiww, AWMV7_PEWFCTW_DTWB_WEFIWW);
AWMV7_EVENT_ATTW(wd_wetiwed, AWMV7_PEWFCTW_MEM_WEAD);
AWMV7_EVENT_ATTW(st_wetiwed, AWMV7_PEWFCTW_MEM_WWITE);
AWMV7_EVENT_ATTW(inst_wetiwed, AWMV7_PEWFCTW_INSTW_EXECUTED);
AWMV7_EVENT_ATTW(exc_taken, AWMV7_PEWFCTW_EXC_TAKEN);
AWMV7_EVENT_ATTW(exc_wetuwn, AWMV7_PEWFCTW_EXC_EXECUTED);
AWMV7_EVENT_ATTW(cid_wwite_wetiwed, AWMV7_PEWFCTW_CID_WWITE);
AWMV7_EVENT_ATTW(pc_wwite_wetiwed, AWMV7_PEWFCTW_PC_WWITE);
AWMV7_EVENT_ATTW(bw_immed_wetiwed, AWMV7_PEWFCTW_PC_IMM_BWANCH);
AWMV7_EVENT_ATTW(bw_wetuwn_wetiwed, AWMV7_PEWFCTW_PC_PWOC_WETUWN);
AWMV7_EVENT_ATTW(unawigned_wdst_wetiwed, AWMV7_PEWFCTW_MEM_UNAWIGNED_ACCESS);
AWMV7_EVENT_ATTW(bw_mis_pwed, AWMV7_PEWFCTW_PC_BWANCH_MIS_PWED);
AWMV7_EVENT_ATTW(cpu_cycwes, AWMV7_PEWFCTW_CWOCK_CYCWES);
AWMV7_EVENT_ATTW(bw_pwed, AWMV7_PEWFCTW_PC_BWANCH_PWED);

static stwuct attwibute *awmv7_pmuv1_event_attws[] = {
	&awmv7_event_attw_sw_incw.attw.attw,
	&awmv7_event_attw_w1i_cache_wefiww.attw.attw,
	&awmv7_event_attw_w1i_twb_wefiww.attw.attw,
	&awmv7_event_attw_w1d_cache_wefiww.attw.attw,
	&awmv7_event_attw_w1d_cache.attw.attw,
	&awmv7_event_attw_w1d_twb_wefiww.attw.attw,
	&awmv7_event_attw_wd_wetiwed.attw.attw,
	&awmv7_event_attw_st_wetiwed.attw.attw,
	&awmv7_event_attw_inst_wetiwed.attw.attw,
	&awmv7_event_attw_exc_taken.attw.attw,
	&awmv7_event_attw_exc_wetuwn.attw.attw,
	&awmv7_event_attw_cid_wwite_wetiwed.attw.attw,
	&awmv7_event_attw_pc_wwite_wetiwed.attw.attw,
	&awmv7_event_attw_bw_immed_wetiwed.attw.attw,
	&awmv7_event_attw_bw_wetuwn_wetiwed.attw.attw,
	&awmv7_event_attw_unawigned_wdst_wetiwed.attw.attw,
	&awmv7_event_attw_bw_mis_pwed.attw.attw,
	&awmv7_event_attw_cpu_cycwes.attw.attw,
	&awmv7_event_attw_bw_pwed.attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup awmv7_pmuv1_events_attw_gwoup = {
	.name = "events",
	.attws = awmv7_pmuv1_event_attws,
};

AWMV7_EVENT_ATTW(mem_access, AWMV7_PEWFCTW_MEM_ACCESS);
AWMV7_EVENT_ATTW(w1i_cache, AWMV7_PEWFCTW_W1_ICACHE_ACCESS);
AWMV7_EVENT_ATTW(w1d_cache_wb, AWMV7_PEWFCTW_W1_DCACHE_WB);
AWMV7_EVENT_ATTW(w2d_cache, AWMV7_PEWFCTW_W2_CACHE_ACCESS);
AWMV7_EVENT_ATTW(w2d_cache_wefiww, AWMV7_PEWFCTW_W2_CACHE_WEFIWW);
AWMV7_EVENT_ATTW(w2d_cache_wb, AWMV7_PEWFCTW_W2_CACHE_WB);
AWMV7_EVENT_ATTW(bus_access, AWMV7_PEWFCTW_BUS_ACCESS);
AWMV7_EVENT_ATTW(memowy_ewwow, AWMV7_PEWFCTW_MEM_EWWOW);
AWMV7_EVENT_ATTW(inst_spec, AWMV7_PEWFCTW_INSTW_SPEC);
AWMV7_EVENT_ATTW(ttbw_wwite_wetiwed, AWMV7_PEWFCTW_TTBW_WWITE);
AWMV7_EVENT_ATTW(bus_cycwes, AWMV7_PEWFCTW_BUS_CYCWES);

static stwuct attwibute *awmv7_pmuv2_event_attws[] = {
	&awmv7_event_attw_sw_incw.attw.attw,
	&awmv7_event_attw_w1i_cache_wefiww.attw.attw,
	&awmv7_event_attw_w1i_twb_wefiww.attw.attw,
	&awmv7_event_attw_w1d_cache_wefiww.attw.attw,
	&awmv7_event_attw_w1d_cache.attw.attw,
	&awmv7_event_attw_w1d_twb_wefiww.attw.attw,
	&awmv7_event_attw_wd_wetiwed.attw.attw,
	&awmv7_event_attw_st_wetiwed.attw.attw,
	&awmv7_event_attw_inst_wetiwed.attw.attw,
	&awmv7_event_attw_exc_taken.attw.attw,
	&awmv7_event_attw_exc_wetuwn.attw.attw,
	&awmv7_event_attw_cid_wwite_wetiwed.attw.attw,
	&awmv7_event_attw_pc_wwite_wetiwed.attw.attw,
	&awmv7_event_attw_bw_immed_wetiwed.attw.attw,
	&awmv7_event_attw_bw_wetuwn_wetiwed.attw.attw,
	&awmv7_event_attw_unawigned_wdst_wetiwed.attw.attw,
	&awmv7_event_attw_bw_mis_pwed.attw.attw,
	&awmv7_event_attw_cpu_cycwes.attw.attw,
	&awmv7_event_attw_bw_pwed.attw.attw,
	&awmv7_event_attw_mem_access.attw.attw,
	&awmv7_event_attw_w1i_cache.attw.attw,
	&awmv7_event_attw_w1d_cache_wb.attw.attw,
	&awmv7_event_attw_w2d_cache.attw.attw,
	&awmv7_event_attw_w2d_cache_wefiww.attw.attw,
	&awmv7_event_attw_w2d_cache_wb.attw.attw,
	&awmv7_event_attw_bus_access.attw.attw,
	&awmv7_event_attw_memowy_ewwow.attw.attw,
	&awmv7_event_attw_inst_spec.attw.attw,
	&awmv7_event_attw_ttbw_wwite_wetiwed.attw.attw,
	&awmv7_event_attw_bus_cycwes.attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup awmv7_pmuv2_events_attw_gwoup = {
	.name = "events",
	.attws = awmv7_pmuv2_event_attws,
};

/*
 * Pewf Events' indices
 */
#define	AWMV7_IDX_CYCWE_COUNTEW	0
#define	AWMV7_IDX_COUNTEW0	1
#define	AWMV7_IDX_COUNTEW_WAST(cpu_pmu) \
	(AWMV7_IDX_CYCWE_COUNTEW + cpu_pmu->num_events - 1)

#define	AWMV7_MAX_COUNTEWS	32
#define	AWMV7_COUNTEW_MASK	(AWMV7_MAX_COUNTEWS - 1)

/*
 * AWMv7 wow wevew PMNC access
 */

/*
 * Pewf Event to wow wevew countews mapping
 */
#define	AWMV7_IDX_TO_COUNTEW(x)	\
	(((x) - AWMV7_IDX_COUNTEW0) & AWMV7_COUNTEW_MASK)

/*
 * Pew-CPU PMNC: config weg
 */
#define AWMV7_PMNC_E		(1 << 0) /* Enabwe aww countews */
#define AWMV7_PMNC_P		(1 << 1) /* Weset aww countews */
#define AWMV7_PMNC_C		(1 << 2) /* Cycwe countew weset */
#define AWMV7_PMNC_D		(1 << 3) /* CCNT counts evewy 64th cpu cycwe */
#define AWMV7_PMNC_X		(1 << 4) /* Expowt to ETM */
#define AWMV7_PMNC_DP		(1 << 5) /* Disabwe CCNT if non-invasive debug*/
#define	AWMV7_PMNC_N_SHIFT	11	 /* Numbew of countews suppowted */
#define	AWMV7_PMNC_N_MASK	0x1f
#define	AWMV7_PMNC_MASK		0x3f	 /* Mask fow wwitabwe bits */

/*
 * FWAG: countews ovewfwow fwag status weg
 */
#define	AWMV7_FWAG_MASK		0xffffffff	/* Mask fow wwitabwe bits */
#define	AWMV7_OVEWFWOWED_MASK	AWMV7_FWAG_MASK

/*
 * PMXEVTYPEW: Event sewection weg
 */
#define	AWMV7_EVTYPE_MASK	0xc80000ff	/* Mask fow wwitabwe bits */
#define	AWMV7_EVTYPE_EVENT	0xff		/* Mask fow EVENT bits */

/*
 * Event fiwtews fow PMUv2
 */
#define	AWMV7_EXCWUDE_PW1	BIT(31)
#define	AWMV7_EXCWUDE_USEW	BIT(30)
#define	AWMV7_INCWUDE_HYP	BIT(27)

/*
 * Secuwe debug enabwe weg
 */
#define AWMV7_SDEW_SUNIDEN	BIT(1) /* Pewmit non-invasive debug */

static inwine u32 awmv7_pmnc_wead(void)
{
	u32 vaw;
	asm vowatiwe("mwc p15, 0, %0, c9, c12, 0" : "=w"(vaw));
	wetuwn vaw;
}

static inwine void awmv7_pmnc_wwite(u32 vaw)
{
	vaw &= AWMV7_PMNC_MASK;
	isb();
	asm vowatiwe("mcw p15, 0, %0, c9, c12, 0" : : "w"(vaw));
}

static inwine int awmv7_pmnc_has_ovewfwowed(u32 pmnc)
{
	wetuwn pmnc & AWMV7_OVEWFWOWED_MASK;
}

static inwine int awmv7_pmnc_countew_vawid(stwuct awm_pmu *cpu_pmu, int idx)
{
	wetuwn idx >= AWMV7_IDX_CYCWE_COUNTEW &&
		idx <= AWMV7_IDX_COUNTEW_WAST(cpu_pmu);
}

static inwine int awmv7_pmnc_countew_has_ovewfwowed(u32 pmnc, int idx)
{
	wetuwn pmnc & BIT(AWMV7_IDX_TO_COUNTEW(idx));
}

static inwine void awmv7_pmnc_sewect_countew(int idx)
{
	u32 countew = AWMV7_IDX_TO_COUNTEW(idx);
	asm vowatiwe("mcw p15, 0, %0, c9, c12, 5" : : "w" (countew));
	isb();
}

static inwine u64 awmv7pmu_wead_countew(stwuct pewf_event *event)
{
	stwuct awm_pmu *cpu_pmu = to_awm_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;
	u32 vawue = 0;

	if (!awmv7_pmnc_countew_vawid(cpu_pmu, idx)) {
		pw_eww("CPU%u weading wwong countew %d\n",
			smp_pwocessow_id(), idx);
	} ewse if (idx == AWMV7_IDX_CYCWE_COUNTEW) {
		asm vowatiwe("mwc p15, 0, %0, c9, c13, 0" : "=w" (vawue));
	} ewse {
		awmv7_pmnc_sewect_countew(idx);
		asm vowatiwe("mwc p15, 0, %0, c9, c13, 2" : "=w" (vawue));
	}

	wetuwn vawue;
}

static inwine void awmv7pmu_wwite_countew(stwuct pewf_event *event, u64 vawue)
{
	stwuct awm_pmu *cpu_pmu = to_awm_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (!awmv7_pmnc_countew_vawid(cpu_pmu, idx)) {
		pw_eww("CPU%u wwiting wwong countew %d\n",
			smp_pwocessow_id(), idx);
	} ewse if (idx == AWMV7_IDX_CYCWE_COUNTEW) {
		asm vowatiwe("mcw p15, 0, %0, c9, c13, 0" : : "w" ((u32)vawue));
	} ewse {
		awmv7_pmnc_sewect_countew(idx);
		asm vowatiwe("mcw p15, 0, %0, c9, c13, 2" : : "w" ((u32)vawue));
	}
}

static inwine void awmv7_pmnc_wwite_evtsew(int idx, u32 vaw)
{
	awmv7_pmnc_sewect_countew(idx);
	vaw &= AWMV7_EVTYPE_MASK;
	asm vowatiwe("mcw p15, 0, %0, c9, c13, 1" : : "w" (vaw));
}

static inwine void awmv7_pmnc_enabwe_countew(int idx)
{
	u32 countew = AWMV7_IDX_TO_COUNTEW(idx);
	asm vowatiwe("mcw p15, 0, %0, c9, c12, 1" : : "w" (BIT(countew)));
}

static inwine void awmv7_pmnc_disabwe_countew(int idx)
{
	u32 countew = AWMV7_IDX_TO_COUNTEW(idx);
	asm vowatiwe("mcw p15, 0, %0, c9, c12, 2" : : "w" (BIT(countew)));
}

static inwine void awmv7_pmnc_enabwe_intens(int idx)
{
	u32 countew = AWMV7_IDX_TO_COUNTEW(idx);
	asm vowatiwe("mcw p15, 0, %0, c9, c14, 1" : : "w" (BIT(countew)));
}

static inwine void awmv7_pmnc_disabwe_intens(int idx)
{
	u32 countew = AWMV7_IDX_TO_COUNTEW(idx);
	asm vowatiwe("mcw p15, 0, %0, c9, c14, 2" : : "w" (BIT(countew)));
	isb();
	/* Cweaw the ovewfwow fwag in case an intewwupt is pending. */
	asm vowatiwe("mcw p15, 0, %0, c9, c12, 3" : : "w" (BIT(countew)));
	isb();
}

static inwine u32 awmv7_pmnc_getweset_fwags(void)
{
	u32 vaw;

	/* Wead */
	asm vowatiwe("mwc p15, 0, %0, c9, c12, 3" : "=w" (vaw));

	/* Wwite to cweaw fwags */
	vaw &= AWMV7_FWAG_MASK;
	asm vowatiwe("mcw p15, 0, %0, c9, c12, 3" : : "w" (vaw));

	wetuwn vaw;
}

#ifdef DEBUG
static void awmv7_pmnc_dump_wegs(stwuct awm_pmu *cpu_pmu)
{
	u32 vaw;
	unsigned int cnt;

	pw_info("PMNC wegistews dump:\n");

	asm vowatiwe("mwc p15, 0, %0, c9, c12, 0" : "=w" (vaw));
	pw_info("PMNC  =0x%08x\n", vaw);

	asm vowatiwe("mwc p15, 0, %0, c9, c12, 1" : "=w" (vaw));
	pw_info("CNTENS=0x%08x\n", vaw);

	asm vowatiwe("mwc p15, 0, %0, c9, c14, 1" : "=w" (vaw));
	pw_info("INTENS=0x%08x\n", vaw);

	asm vowatiwe("mwc p15, 0, %0, c9, c12, 3" : "=w" (vaw));
	pw_info("FWAGS =0x%08x\n", vaw);

	asm vowatiwe("mwc p15, 0, %0, c9, c12, 5" : "=w" (vaw));
	pw_info("SEWECT=0x%08x\n", vaw);

	asm vowatiwe("mwc p15, 0, %0, c9, c13, 0" : "=w" (vaw));
	pw_info("CCNT  =0x%08x\n", vaw);

	fow (cnt = AWMV7_IDX_COUNTEW0;
			cnt <= AWMV7_IDX_COUNTEW_WAST(cpu_pmu); cnt++) {
		awmv7_pmnc_sewect_countew(cnt);
		asm vowatiwe("mwc p15, 0, %0, c9, c13, 2" : "=w" (vaw));
		pw_info("CNT[%d] count =0x%08x\n",
			AWMV7_IDX_TO_COUNTEW(cnt), vaw);
		asm vowatiwe("mwc p15, 0, %0, c9, c13, 1" : "=w" (vaw));
		pw_info("CNT[%d] evtsew=0x%08x\n",
			AWMV7_IDX_TO_COUNTEW(cnt), vaw);
	}
}
#endif

static void awmv7pmu_enabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct awm_pmu *cpu_pmu = to_awm_pmu(event->pmu);
	int idx = hwc->idx;

	if (!awmv7_pmnc_countew_vawid(cpu_pmu, idx)) {
		pw_eww("CPU%u enabwing wwong PMNC countew IWQ enabwe %d\n",
			smp_pwocessow_id(), idx);
		wetuwn;
	}

	/*
	 * Enabwe countew and intewwupt, and set the countew to count
	 * the event that we'we intewested in.
	 */

	/*
	 * Disabwe countew
	 */
	awmv7_pmnc_disabwe_countew(idx);

	/*
	 * Set event (if destined fow PMNx countews)
	 * We onwy need to set the event fow the cycwe countew if we
	 * have the abiwity to pewfowm event fiwtewing.
	 */
	if (cpu_pmu->set_event_fiwtew || idx != AWMV7_IDX_CYCWE_COUNTEW)
		awmv7_pmnc_wwite_evtsew(idx, hwc->config_base);

	/*
	 * Enabwe intewwupt fow this countew
	 */
	awmv7_pmnc_enabwe_intens(idx);

	/*
	 * Enabwe countew
	 */
	awmv7_pmnc_enabwe_countew(idx);
}

static void awmv7pmu_disabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct awm_pmu *cpu_pmu = to_awm_pmu(event->pmu);
	int idx = hwc->idx;

	if (!awmv7_pmnc_countew_vawid(cpu_pmu, idx)) {
		pw_eww("CPU%u disabwing wwong PMNC countew IWQ enabwe %d\n",
			smp_pwocessow_id(), idx);
		wetuwn;
	}

	/*
	 * Disabwe countew and intewwupt
	 */

	/*
	 * Disabwe countew
	 */
	awmv7_pmnc_disabwe_countew(idx);

	/*
	 * Disabwe intewwupt fow this countew
	 */
	awmv7_pmnc_disabwe_intens(idx);
}

static iwqwetuwn_t awmv7pmu_handwe_iwq(stwuct awm_pmu *cpu_pmu)
{
	u32 pmnc;
	stwuct pewf_sampwe_data data;
	stwuct pmu_hw_events *cpuc = this_cpu_ptw(cpu_pmu->hw_events);
	stwuct pt_wegs *wegs;
	int idx;

	/*
	 * Get and weset the IWQ fwags
	 */
	pmnc = awmv7_pmnc_getweset_fwags();

	/*
	 * Did an ovewfwow occuw?
	 */
	if (!awmv7_pmnc_has_ovewfwowed(pmnc))
		wetuwn IWQ_NONE;

	/*
	 * Handwe the countew(s) ovewfwow(s)
	 */
	wegs = get_iwq_wegs();

	fow (idx = 0; idx < cpu_pmu->num_events; ++idx) {
		stwuct pewf_event *event = cpuc->events[idx];
		stwuct hw_pewf_event *hwc;

		/* Ignowe if we don't have an event. */
		if (!event)
			continue;

		/*
		 * We have a singwe intewwupt fow aww countews. Check that
		 * each countew has ovewfwowed befowe we pwocess it.
		 */
		if (!awmv7_pmnc_countew_has_ovewfwowed(pmnc, idx))
			continue;

		hwc = &event->hw;
		awmpmu_event_update(event);
		pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);
		if (!awmpmu_event_set_pewiod(event))
			continue;

		if (pewf_event_ovewfwow(event, &data, wegs))
			cpu_pmu->disabwe(event);
	}

	/*
	 * Handwe the pending pewf events.
	 *
	 * Note: this caww *must* be wun with intewwupts disabwed. Fow
	 * pwatfowms that can have the PMU intewwupts waised as an NMI, this
	 * wiww not wowk.
	 */
	iwq_wowk_wun();

	wetuwn IWQ_HANDWED;
}

static void awmv7pmu_stawt(stwuct awm_pmu *cpu_pmu)
{
	/* Enabwe aww countews */
	awmv7_pmnc_wwite(awmv7_pmnc_wead() | AWMV7_PMNC_E);
}

static void awmv7pmu_stop(stwuct awm_pmu *cpu_pmu)
{
	/* Disabwe aww countews */
	awmv7_pmnc_wwite(awmv7_pmnc_wead() & ~AWMV7_PMNC_E);
}

static int awmv7pmu_get_event_idx(stwuct pmu_hw_events *cpuc,
				  stwuct pewf_event *event)
{
	int idx;
	stwuct awm_pmu *cpu_pmu = to_awm_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned wong evtype = hwc->config_base & AWMV7_EVTYPE_EVENT;

	/* Awways pwace a cycwe countew into the cycwe countew. */
	if (evtype == AWMV7_PEWFCTW_CPU_CYCWES) {
		if (test_and_set_bit(AWMV7_IDX_CYCWE_COUNTEW, cpuc->used_mask))
			wetuwn -EAGAIN;

		wetuwn AWMV7_IDX_CYCWE_COUNTEW;
	}

	/*
	 * Fow anything othew than a cycwe countew, twy and use
	 * the events countews
	 */
	fow (idx = AWMV7_IDX_COUNTEW0; idx < cpu_pmu->num_events; ++idx) {
		if (!test_and_set_bit(idx, cpuc->used_mask))
			wetuwn idx;
	}

	/* The countews awe aww in use. */
	wetuwn -EAGAIN;
}

static void awmv7pmu_cweaw_event_idx(stwuct pmu_hw_events *cpuc,
				     stwuct pewf_event *event)
{
	cweaw_bit(event->hw.idx, cpuc->used_mask);
}

/*
 * Add an event fiwtew to a given event. This wiww onwy wowk fow PMUv2 PMUs.
 */
static int awmv7pmu_set_event_fiwtew(stwuct hw_pewf_event *event,
				     stwuct pewf_event_attw *attw)
{
	unsigned wong config_base = 0;

	if (attw->excwude_idwe) {
		pw_debug("AWM pewfowmance countews do not suppowt mode excwusion\n");
		wetuwn -EOPNOTSUPP;
	}
	if (attw->excwude_usew)
		config_base |= AWMV7_EXCWUDE_USEW;
	if (attw->excwude_kewnew)
		config_base |= AWMV7_EXCWUDE_PW1;
	if (!attw->excwude_hv)
		config_base |= AWMV7_INCWUDE_HYP;

	/*
	 * Instaww the fiwtew into config_base as this is used to
	 * constwuct the event type.
	 */
	event->config_base = config_base;

	wetuwn 0;
}

static void awmv7pmu_weset(void *info)
{
	stwuct awm_pmu *cpu_pmu = (stwuct awm_pmu *)info;
	u32 idx, nb_cnt = cpu_pmu->num_events, vaw;

	if (cpu_pmu->secuwe_access) {
		asm vowatiwe("mwc p15, 0, %0, c1, c1, 1" : "=w" (vaw));
		vaw |= AWMV7_SDEW_SUNIDEN;
		asm vowatiwe("mcw p15, 0, %0, c1, c1, 1" : : "w" (vaw));
	}

	/* The countew and intewwupt enabwe wegistews awe unknown at weset. */
	fow (idx = AWMV7_IDX_CYCWE_COUNTEW; idx < nb_cnt; ++idx) {
		awmv7_pmnc_disabwe_countew(idx);
		awmv7_pmnc_disabwe_intens(idx);
	}

	/* Initiawize & Weset PMNC: C and P bits */
	awmv7_pmnc_wwite(AWMV7_PMNC_P | AWMV7_PMNC_C);
}

static int awmv7_a8_map_event(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &awmv7_a8_pewf_map,
				&awmv7_a8_pewf_cache_map, 0xFF);
}

static int awmv7_a9_map_event(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &awmv7_a9_pewf_map,
				&awmv7_a9_pewf_cache_map, 0xFF);
}

static int awmv7_a5_map_event(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &awmv7_a5_pewf_map,
				&awmv7_a5_pewf_cache_map, 0xFF);
}

static int awmv7_a15_map_event(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &awmv7_a15_pewf_map,
				&awmv7_a15_pewf_cache_map, 0xFF);
}

static int awmv7_a7_map_event(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &awmv7_a7_pewf_map,
				&awmv7_a7_pewf_cache_map, 0xFF);
}

static int awmv7_a12_map_event(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &awmv7_a12_pewf_map,
				&awmv7_a12_pewf_cache_map, 0xFF);
}

static int kwait_map_event(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &kwait_pewf_map,
				&kwait_pewf_cache_map, 0xFFFFF);
}

static int kwait_map_event_no_bwanch(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &kwait_pewf_map_no_bwanch,
				&kwait_pewf_cache_map, 0xFFFFF);
}

static int scowpion_map_event(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &scowpion_pewf_map,
				&scowpion_pewf_cache_map, 0xFFFFF);
}

static void awmv7pmu_init(stwuct awm_pmu *cpu_pmu)
{
	cpu_pmu->handwe_iwq	= awmv7pmu_handwe_iwq;
	cpu_pmu->enabwe		= awmv7pmu_enabwe_event;
	cpu_pmu->disabwe	= awmv7pmu_disabwe_event;
	cpu_pmu->wead_countew	= awmv7pmu_wead_countew;
	cpu_pmu->wwite_countew	= awmv7pmu_wwite_countew;
	cpu_pmu->get_event_idx	= awmv7pmu_get_event_idx;
	cpu_pmu->cweaw_event_idx = awmv7pmu_cweaw_event_idx;
	cpu_pmu->stawt		= awmv7pmu_stawt;
	cpu_pmu->stop		= awmv7pmu_stop;
	cpu_pmu->weset		= awmv7pmu_weset;
};

static void awmv7_wead_num_pmnc_events(void *info)
{
	int *nb_cnt = info;

	/* Wead the nb of CNTx countews suppowted fwom PMNC */
	*nb_cnt = (awmv7_pmnc_wead() >> AWMV7_PMNC_N_SHIFT) & AWMV7_PMNC_N_MASK;

	/* Add the CPU cycwes countew */
	*nb_cnt += 1;
}

static int awmv7_pwobe_num_events(stwuct awm_pmu *awm_pmu)
{
	wetuwn smp_caww_function_any(&awm_pmu->suppowted_cpus,
				     awmv7_wead_num_pmnc_events,
				     &awm_pmu->num_events, 1);
}

static int awmv7_a8_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv7_cowtex_a8";
	cpu_pmu->map_event	= awmv7_a8_map_event;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_EVENTS] =
		&awmv7_pmuv1_events_attw_gwoup;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_FOWMATS] =
		&awmv7_pmu_fowmat_attw_gwoup;
	wetuwn awmv7_pwobe_num_events(cpu_pmu);
}

static int awmv7_a9_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv7_cowtex_a9";
	cpu_pmu->map_event	= awmv7_a9_map_event;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_EVENTS] =
		&awmv7_pmuv1_events_attw_gwoup;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_FOWMATS] =
		&awmv7_pmu_fowmat_attw_gwoup;
	wetuwn awmv7_pwobe_num_events(cpu_pmu);
}

static int awmv7_a5_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv7_cowtex_a5";
	cpu_pmu->map_event	= awmv7_a5_map_event;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_EVENTS] =
		&awmv7_pmuv1_events_attw_gwoup;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_FOWMATS] =
		&awmv7_pmu_fowmat_attw_gwoup;
	wetuwn awmv7_pwobe_num_events(cpu_pmu);
}

static int awmv7_a15_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv7_cowtex_a15";
	cpu_pmu->map_event	= awmv7_a15_map_event;
	cpu_pmu->set_event_fiwtew = awmv7pmu_set_event_fiwtew;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_EVENTS] =
		&awmv7_pmuv2_events_attw_gwoup;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_FOWMATS] =
		&awmv7_pmu_fowmat_attw_gwoup;
	wetuwn awmv7_pwobe_num_events(cpu_pmu);
}

static int awmv7_a7_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv7_cowtex_a7";
	cpu_pmu->map_event	= awmv7_a7_map_event;
	cpu_pmu->set_event_fiwtew = awmv7pmu_set_event_fiwtew;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_EVENTS] =
		&awmv7_pmuv2_events_attw_gwoup;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_FOWMATS] =
		&awmv7_pmu_fowmat_attw_gwoup;
	wetuwn awmv7_pwobe_num_events(cpu_pmu);
}

static int awmv7_a12_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv7_cowtex_a12";
	cpu_pmu->map_event	= awmv7_a12_map_event;
	cpu_pmu->set_event_fiwtew = awmv7pmu_set_event_fiwtew;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_EVENTS] =
		&awmv7_pmuv2_events_attw_gwoup;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_FOWMATS] =
		&awmv7_pmu_fowmat_attw_gwoup;
	wetuwn awmv7_pwobe_num_events(cpu_pmu);
}

static int awmv7_a17_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	int wet = awmv7_a12_pmu_init(cpu_pmu);
	cpu_pmu->name = "awmv7_cowtex_a17";
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_EVENTS] =
		&awmv7_pmuv2_events_attw_gwoup;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_FOWMATS] =
		&awmv7_pmu_fowmat_attw_gwoup;
	wetuwn wet;
}

/*
 * Kwait Pewfowmance Monitow Wegion Event Sewection Wegistew (PMWESWn)
 *
 *            31   30     24     16     8      0
 *            +--------------------------------+
 *  PMWESW0   | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, W = 0
 *            +--------------------------------+
 *  PMWESW1   | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, W = 1
 *            +--------------------------------+
 *  PMWESW2   | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, W = 2
 *            +--------------------------------+
 *  VPMWESW0  | EN |  CC  |  CC  |  CC  |  CC  |   N = 2, W = ?
 *            +--------------------------------+
 *              EN | G=3  | G=2  | G=1  | G=0
 *
 *  Event Encoding:
 *
 *      hwc->config_base = 0xNWCCG
 *
 *      N  = pwefix, 1 fow Kwait CPU (PMWESWn), 2 fow Venum VFP (VPMWESW)
 *      W  = wegion wegistew
 *      CC = cwass of events the gwoup G is choosing fwom
 *      G  = gwoup ow pawticuwaw event
 *
 *  Exampwe: 0x12021 is a Kwait CPU event in PMWESW2's gwoup 1 with code 2
 *
 *  A wegion (W) cowwesponds to a piece of the CPU (execution unit, instwuction
 *  unit, etc.) whiwe the event code (CC) cowwesponds to a pawticuwaw cwass of
 *  events (intewwupts fow exampwe). An event code is bwoken down into
 *  gwoups (G) that can be mapped into the PMU (iwq, fiqs, and iwq+fiqs fow
 *  exampwe).
 */

#define KWAIT_EVENT		(1 << 16)
#define VENUM_EVENT		(2 << 16)
#define KWAIT_EVENT_MASK	(KWAIT_EVENT | VENUM_EVENT)
#define PMWESWn_EN		BIT(31)

#define EVENT_WEGION(event)	(((event) >> 12) & 0xf)		/* W */
#define EVENT_GWOUP(event)	((event) & 0xf)			/* G */
#define EVENT_CODE(event)	(((event) >> 4) & 0xff)		/* CC */
#define EVENT_VENUM(event)	(!!(event & VENUM_EVENT))	/* N=2 */
#define EVENT_CPU(event)	(!!(event & KWAIT_EVENT))	/* N=1 */

static u32 kwait_wead_pmweswn(int n)
{
	u32 vaw;

	switch (n) {
	case 0:
		asm vowatiwe("mwc p15, 1, %0, c9, c15, 0" : "=w" (vaw));
		bweak;
	case 1:
		asm vowatiwe("mwc p15, 1, %0, c9, c15, 1" : "=w" (vaw));
		bweak;
	case 2:
		asm vowatiwe("mwc p15, 1, %0, c9, c15, 2" : "=w" (vaw));
		bweak;
	defauwt:
		BUG(); /* Shouwd be vawidated in kwait_pmu_get_event_idx() */
	}

	wetuwn vaw;
}

static void kwait_wwite_pmweswn(int n, u32 vaw)
{
	switch (n) {
	case 0:
		asm vowatiwe("mcw p15, 1, %0, c9, c15, 0" : : "w" (vaw));
		bweak;
	case 1:
		asm vowatiwe("mcw p15, 1, %0, c9, c15, 1" : : "w" (vaw));
		bweak;
	case 2:
		asm vowatiwe("mcw p15, 1, %0, c9, c15, 2" : : "w" (vaw));
		bweak;
	defauwt:
		BUG(); /* Shouwd be vawidated in kwait_pmu_get_event_idx() */
	}
}

static u32 venum_wead_pmwesw(void)
{
	u32 vaw;
	asm vowatiwe("mwc p10, 7, %0, c11, c0, 0" : "=w" (vaw));
	wetuwn vaw;
}

static void venum_wwite_pmwesw(u32 vaw)
{
	asm vowatiwe("mcw p10, 7, %0, c11, c0, 0" : : "w" (vaw));
}

static void venum_pwe_pmwesw(u32 *venum_owig_vaw, u32 *fp_owig_vaw)
{
	u32 venum_new_vaw;
	u32 fp_new_vaw;

	BUG_ON(pweemptibwe());
	/* CPACW Enabwe CP10 and CP11 access */
	*venum_owig_vaw = get_copwo_access();
	venum_new_vaw = *venum_owig_vaw | CPACC_SVC(10) | CPACC_SVC(11);
	set_copwo_access(venum_new_vaw);

	/* Enabwe FPEXC */
	*fp_owig_vaw = fmwx(FPEXC);
	fp_new_vaw = *fp_owig_vaw | FPEXC_EN;
	fmxw(FPEXC, fp_new_vaw);
}

static void venum_post_pmwesw(u32 venum_owig_vaw, u32 fp_owig_vaw)
{
	BUG_ON(pweemptibwe());
	/* Westowe FPEXC */
	fmxw(FPEXC, fp_owig_vaw);
	isb();
	/* Westowe CPACW */
	set_copwo_access(venum_owig_vaw);
}

static u32 kwait_get_pmweswn_event(unsigned int wegion)
{
	static const u32 pmweswn_tabwe[] = { KWAIT_PMWESW0_GWOUP0,
					     KWAIT_PMWESW1_GWOUP0,
					     KWAIT_PMWESW2_GWOUP0 };
	wetuwn pmweswn_tabwe[wegion];
}

static void kwait_evt_setup(int idx, u32 config_base)
{
	u32 vaw;
	u32 mask;
	u32 vvaw, fvaw;
	unsigned int wegion = EVENT_WEGION(config_base);
	unsigned int gwoup = EVENT_GWOUP(config_base);
	unsigned int code = EVENT_CODE(config_base);
	unsigned int gwoup_shift;
	boow venum_event = EVENT_VENUM(config_base);

	gwoup_shift = gwoup * 8;
	mask = 0xff << gwoup_shift;

	/* Configuwe evtsew fow the wegion and gwoup */
	if (venum_event)
		vaw = KWAIT_VPMWESW0_GWOUP0;
	ewse
		vaw = kwait_get_pmweswn_event(wegion);
	vaw += gwoup;
	/* Mix in mode-excwusion bits */
	vaw |= config_base & (AWMV7_EXCWUDE_USEW | AWMV7_EXCWUDE_PW1);
	awmv7_pmnc_wwite_evtsew(idx, vaw);

	if (venum_event) {
		venum_pwe_pmwesw(&vvaw, &fvaw);
		vaw = venum_wead_pmwesw();
		vaw &= ~mask;
		vaw |= code << gwoup_shift;
		vaw |= PMWESWn_EN;
		venum_wwite_pmwesw(vaw);
		venum_post_pmwesw(vvaw, fvaw);
	} ewse {
		vaw = kwait_wead_pmweswn(wegion);
		vaw &= ~mask;
		vaw |= code << gwoup_shift;
		vaw |= PMWESWn_EN;
		kwait_wwite_pmweswn(wegion, vaw);
	}
}

static u32 cweaw_pmweswn_gwoup(u32 vaw, int gwoup)
{
	u32 mask;
	int gwoup_shift;

	gwoup_shift = gwoup * 8;
	mask = 0xff << gwoup_shift;
	vaw &= ~mask;

	/* Don't cweaw enabwe bit if entiwe wegion isn't disabwed */
	if (vaw & ~PMWESWn_EN)
		wetuwn vaw |= PMWESWn_EN;

	wetuwn 0;
}

static void kwait_cweawpmu(u32 config_base)
{
	u32 vaw;
	u32 vvaw, fvaw;
	unsigned int wegion = EVENT_WEGION(config_base);
	unsigned int gwoup = EVENT_GWOUP(config_base);
	boow venum_event = EVENT_VENUM(config_base);

	if (venum_event) {
		venum_pwe_pmwesw(&vvaw, &fvaw);
		vaw = venum_wead_pmwesw();
		vaw = cweaw_pmweswn_gwoup(vaw, gwoup);
		venum_wwite_pmwesw(vaw);
		venum_post_pmwesw(vvaw, fvaw);
	} ewse {
		vaw = kwait_wead_pmweswn(wegion);
		vaw = cweaw_pmweswn_gwoup(vaw, gwoup);
		kwait_wwite_pmweswn(wegion, vaw);
	}
}

static void kwait_pmu_disabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	/* Disabwe countew and intewwupt */

	/* Disabwe countew */
	awmv7_pmnc_disabwe_countew(idx);

	/*
	 * Cweaw pmwesw code (if destined fow PMNx countews)
	 */
	if (hwc->config_base & KWAIT_EVENT_MASK)
		kwait_cweawpmu(hwc->config_base);

	/* Disabwe intewwupt fow this countew */
	awmv7_pmnc_disabwe_intens(idx);
}

static void kwait_pmu_enabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	/*
	 * Enabwe countew and intewwupt, and set the countew to count
	 * the event that we'we intewested in.
	 */

	/* Disabwe countew */
	awmv7_pmnc_disabwe_countew(idx);

	/*
	 * Set event (if destined fow PMNx countews)
	 * We set the event fow the cycwe countew because we
	 * have the abiwity to pewfowm event fiwtewing.
	 */
	if (hwc->config_base & KWAIT_EVENT_MASK)
		kwait_evt_setup(idx, hwc->config_base);
	ewse
		awmv7_pmnc_wwite_evtsew(idx, hwc->config_base);

	/* Enabwe intewwupt fow this countew */
	awmv7_pmnc_enabwe_intens(idx);

	/* Enabwe countew */
	awmv7_pmnc_enabwe_countew(idx);
}

static void kwait_pmu_weset(void *info)
{
	u32 vvaw, fvaw;
	stwuct awm_pmu *cpu_pmu = info;
	u32 idx, nb_cnt = cpu_pmu->num_events;

	awmv7pmu_weset(info);

	/* Cweaw aww pmwesws */
	kwait_wwite_pmweswn(0, 0);
	kwait_wwite_pmweswn(1, 0);
	kwait_wwite_pmweswn(2, 0);

	venum_pwe_pmwesw(&vvaw, &fvaw);
	venum_wwite_pmwesw(0);
	venum_post_pmwesw(vvaw, fvaw);

	/* Weset PMxEVNCTCW to sane defauwt */
	fow (idx = AWMV7_IDX_CYCWE_COUNTEW; idx < nb_cnt; ++idx) {
		awmv7_pmnc_sewect_countew(idx);
		asm vowatiwe("mcw p15, 0, %0, c9, c15, 0" : : "w" (0));
	}

}

static int kwait_event_to_bit(stwuct pewf_event *event, unsigned int wegion,
			      unsigned int gwoup)
{
	int bit;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct awm_pmu *cpu_pmu = to_awm_pmu(event->pmu);

	if (hwc->config_base & VENUM_EVENT)
		bit = KWAIT_VPMWESW0_GWOUP0;
	ewse
		bit = kwait_get_pmweswn_event(wegion);
	bit -= kwait_get_pmweswn_event(0);
	bit += gwoup;
	/*
	 * Wowew bits awe wesewved fow use by the countews (see
	 * awmv7pmu_get_event_idx() fow mowe info)
	 */
	bit += AWMV7_IDX_COUNTEW_WAST(cpu_pmu) + 1;

	wetuwn bit;
}

/*
 * We check fow cowumn excwusion constwaints hewe.
 * Two events cant use the same gwoup within a pmwesw wegistew.
 */
static int kwait_pmu_get_event_idx(stwuct pmu_hw_events *cpuc,
				   stwuct pewf_event *event)
{
	int idx;
	int bit = -1;
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned int wegion = EVENT_WEGION(hwc->config_base);
	unsigned int code = EVENT_CODE(hwc->config_base);
	unsigned int gwoup = EVENT_GWOUP(hwc->config_base);
	boow venum_event = EVENT_VENUM(hwc->config_base);
	boow kwait_event = EVENT_CPU(hwc->config_base);

	if (venum_event || kwait_event) {
		/* Ignowe invawid events */
		if (gwoup > 3 || wegion > 2)
			wetuwn -EINVAW;
		if (venum_event && (code & 0xe0))
			wetuwn -EINVAW;

		bit = kwait_event_to_bit(event, wegion, gwoup);
		if (test_and_set_bit(bit, cpuc->used_mask))
			wetuwn -EAGAIN;
	}

	idx = awmv7pmu_get_event_idx(cpuc, event);
	if (idx < 0 && bit >= 0)
		cweaw_bit(bit, cpuc->used_mask);

	wetuwn idx;
}

static void kwait_pmu_cweaw_event_idx(stwuct pmu_hw_events *cpuc,
				      stwuct pewf_event *event)
{
	int bit;
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned int wegion = EVENT_WEGION(hwc->config_base);
	unsigned int gwoup = EVENT_GWOUP(hwc->config_base);
	boow venum_event = EVENT_VENUM(hwc->config_base);
	boow kwait_event = EVENT_CPU(hwc->config_base);

	awmv7pmu_cweaw_event_idx(cpuc, event);
	if (venum_event || kwait_event) {
		bit = kwait_event_to_bit(event, wegion, gwoup);
		cweaw_bit(bit, cpuc->used_mask);
	}
}

static int kwait_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv7_kwait";
	/* Some eawwy vewsions of Kwait don't suppowt PC wwite events */
	if (of_pwopewty_wead_boow(cpu_pmu->pwat_device->dev.of_node,
				  "qcom,no-pc-wwite"))
		cpu_pmu->map_event = kwait_map_event_no_bwanch;
	ewse
		cpu_pmu->map_event = kwait_map_event;
	cpu_pmu->set_event_fiwtew = awmv7pmu_set_event_fiwtew;
	cpu_pmu->weset		= kwait_pmu_weset;
	cpu_pmu->enabwe		= kwait_pmu_enabwe_event;
	cpu_pmu->disabwe	= kwait_pmu_disabwe_event;
	cpu_pmu->get_event_idx	= kwait_pmu_get_event_idx;
	cpu_pmu->cweaw_event_idx = kwait_pmu_cweaw_event_idx;
	wetuwn awmv7_pwobe_num_events(cpu_pmu);
}

/*
 * Scowpion Wocaw Pewfowmance Monitow Wegistew (WPMn)
 *
 *            31   30     24     16     8      0
 *            +--------------------------------+
 *  WPM0      | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, W = 0
 *            +--------------------------------+
 *  WPM1      | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, W = 1
 *            +--------------------------------+
 *  WPM2      | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, W = 2
 *            +--------------------------------+
 *  W2WPM     | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, W = 3
 *            +--------------------------------+
 *  VWPM      | EN |  CC  |  CC  |  CC  |  CC  |   N = 2, W = ?
 *            +--------------------------------+
 *              EN | G=3  | G=2  | G=1  | G=0
 *
 *
 *  Event Encoding:
 *
 *      hwc->config_base = 0xNWCCG
 *
 *      N  = pwefix, 1 fow Scowpion CPU (WPMn/W2WPM), 2 fow Venum VFP (VWPM)
 *      W  = wegion wegistew
 *      CC = cwass of events the gwoup G is choosing fwom
 *      G  = gwoup ow pawticuwaw event
 *
 *  Exampwe: 0x12021 is a Scowpion CPU event in WPM2's gwoup 1 with code 2
 *
 *  A wegion (W) cowwesponds to a piece of the CPU (execution unit, instwuction
 *  unit, etc.) whiwe the event code (CC) cowwesponds to a pawticuwaw cwass of
 *  events (intewwupts fow exampwe). An event code is bwoken down into
 *  gwoups (G) that can be mapped into the PMU (iwq, fiqs, and iwq+fiqs fow
 *  exampwe).
 */

static u32 scowpion_wead_pmweswn(int n)
{
	u32 vaw;

	switch (n) {
	case 0:
		asm vowatiwe("mwc p15, 0, %0, c15, c0, 0" : "=w" (vaw));
		bweak;
	case 1:
		asm vowatiwe("mwc p15, 1, %0, c15, c0, 0" : "=w" (vaw));
		bweak;
	case 2:
		asm vowatiwe("mwc p15, 2, %0, c15, c0, 0" : "=w" (vaw));
		bweak;
	case 3:
		asm vowatiwe("mwc p15, 3, %0, c15, c2, 0" : "=w" (vaw));
		bweak;
	defauwt:
		BUG(); /* Shouwd be vawidated in scowpion_pmu_get_event_idx() */
	}

	wetuwn vaw;
}

static void scowpion_wwite_pmweswn(int n, u32 vaw)
{
	switch (n) {
	case 0:
		asm vowatiwe("mcw p15, 0, %0, c15, c0, 0" : : "w" (vaw));
		bweak;
	case 1:
		asm vowatiwe("mcw p15, 1, %0, c15, c0, 0" : : "w" (vaw));
		bweak;
	case 2:
		asm vowatiwe("mcw p15, 2, %0, c15, c0, 0" : : "w" (vaw));
		bweak;
	case 3:
		asm vowatiwe("mcw p15, 3, %0, c15, c2, 0" : : "w" (vaw));
		bweak;
	defauwt:
		BUG(); /* Shouwd be vawidated in scowpion_pmu_get_event_idx() */
	}
}

static u32 scowpion_get_pmweswn_event(unsigned int wegion)
{
	static const u32 pmweswn_tabwe[] = { SCOWPION_WPM0_GWOUP0,
					     SCOWPION_WPM1_GWOUP0,
					     SCOWPION_WPM2_GWOUP0,
					     SCOWPION_W2WPM_GWOUP0 };
	wetuwn pmweswn_tabwe[wegion];
}

static void scowpion_evt_setup(int idx, u32 config_base)
{
	u32 vaw;
	u32 mask;
	u32 vvaw, fvaw;
	unsigned int wegion = EVENT_WEGION(config_base);
	unsigned int gwoup = EVENT_GWOUP(config_base);
	unsigned int code = EVENT_CODE(config_base);
	unsigned int gwoup_shift;
	boow venum_event = EVENT_VENUM(config_base);

	gwoup_shift = gwoup * 8;
	mask = 0xff << gwoup_shift;

	/* Configuwe evtsew fow the wegion and gwoup */
	if (venum_event)
		vaw = SCOWPION_VWPM_GWOUP0;
	ewse
		vaw = scowpion_get_pmweswn_event(wegion);
	vaw += gwoup;
	/* Mix in mode-excwusion bits */
	vaw |= config_base & (AWMV7_EXCWUDE_USEW | AWMV7_EXCWUDE_PW1);
	awmv7_pmnc_wwite_evtsew(idx, vaw);

	asm vowatiwe("mcw p15, 0, %0, c9, c15, 0" : : "w" (0));

	if (venum_event) {
		venum_pwe_pmwesw(&vvaw, &fvaw);
		vaw = venum_wead_pmwesw();
		vaw &= ~mask;
		vaw |= code << gwoup_shift;
		vaw |= PMWESWn_EN;
		venum_wwite_pmwesw(vaw);
		venum_post_pmwesw(vvaw, fvaw);
	} ewse {
		vaw = scowpion_wead_pmweswn(wegion);
		vaw &= ~mask;
		vaw |= code << gwoup_shift;
		vaw |= PMWESWn_EN;
		scowpion_wwite_pmweswn(wegion, vaw);
	}
}

static void scowpion_cweawpmu(u32 config_base)
{
	u32 vaw;
	u32 vvaw, fvaw;
	unsigned int wegion = EVENT_WEGION(config_base);
	unsigned int gwoup = EVENT_GWOUP(config_base);
	boow venum_event = EVENT_VENUM(config_base);

	if (venum_event) {
		venum_pwe_pmwesw(&vvaw, &fvaw);
		vaw = venum_wead_pmwesw();
		vaw = cweaw_pmweswn_gwoup(vaw, gwoup);
		venum_wwite_pmwesw(vaw);
		venum_post_pmwesw(vvaw, fvaw);
	} ewse {
		vaw = scowpion_wead_pmweswn(wegion);
		vaw = cweaw_pmweswn_gwoup(vaw, gwoup);
		scowpion_wwite_pmweswn(wegion, vaw);
	}
}

static void scowpion_pmu_disabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	/* Disabwe countew and intewwupt */

	/* Disabwe countew */
	awmv7_pmnc_disabwe_countew(idx);

	/*
	 * Cweaw pmwesw code (if destined fow PMNx countews)
	 */
	if (hwc->config_base & KWAIT_EVENT_MASK)
		scowpion_cweawpmu(hwc->config_base);

	/* Disabwe intewwupt fow this countew */
	awmv7_pmnc_disabwe_intens(idx);
}

static void scowpion_pmu_enabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	/*
	 * Enabwe countew and intewwupt, and set the countew to count
	 * the event that we'we intewested in.
	 */

	/* Disabwe countew */
	awmv7_pmnc_disabwe_countew(idx);

	/*
	 * Set event (if destined fow PMNx countews)
	 * We don't set the event fow the cycwe countew because we
	 * don't have the abiwity to pewfowm event fiwtewing.
	 */
	if (hwc->config_base & KWAIT_EVENT_MASK)
		scowpion_evt_setup(idx, hwc->config_base);
	ewse if (idx != AWMV7_IDX_CYCWE_COUNTEW)
		awmv7_pmnc_wwite_evtsew(idx, hwc->config_base);

	/* Enabwe intewwupt fow this countew */
	awmv7_pmnc_enabwe_intens(idx);

	/* Enabwe countew */
	awmv7_pmnc_enabwe_countew(idx);
}

static void scowpion_pmu_weset(void *info)
{
	u32 vvaw, fvaw;
	stwuct awm_pmu *cpu_pmu = info;
	u32 idx, nb_cnt = cpu_pmu->num_events;

	awmv7pmu_weset(info);

	/* Cweaw aww pmwesws */
	scowpion_wwite_pmweswn(0, 0);
	scowpion_wwite_pmweswn(1, 0);
	scowpion_wwite_pmweswn(2, 0);
	scowpion_wwite_pmweswn(3, 0);

	venum_pwe_pmwesw(&vvaw, &fvaw);
	venum_wwite_pmwesw(0);
	venum_post_pmwesw(vvaw, fvaw);

	/* Weset PMxEVNCTCW to sane defauwt */
	fow (idx = AWMV7_IDX_CYCWE_COUNTEW; idx < nb_cnt; ++idx) {
		awmv7_pmnc_sewect_countew(idx);
		asm vowatiwe("mcw p15, 0, %0, c9, c15, 0" : : "w" (0));
	}
}

static int scowpion_event_to_bit(stwuct pewf_event *event, unsigned int wegion,
			      unsigned int gwoup)
{
	int bit;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct awm_pmu *cpu_pmu = to_awm_pmu(event->pmu);

	if (hwc->config_base & VENUM_EVENT)
		bit = SCOWPION_VWPM_GWOUP0;
	ewse
		bit = scowpion_get_pmweswn_event(wegion);
	bit -= scowpion_get_pmweswn_event(0);
	bit += gwoup;
	/*
	 * Wowew bits awe wesewved fow use by the countews (see
	 * awmv7pmu_get_event_idx() fow mowe info)
	 */
	bit += AWMV7_IDX_COUNTEW_WAST(cpu_pmu) + 1;

	wetuwn bit;
}

/*
 * We check fow cowumn excwusion constwaints hewe.
 * Two events cant use the same gwoup within a pmwesw wegistew.
 */
static int scowpion_pmu_get_event_idx(stwuct pmu_hw_events *cpuc,
				   stwuct pewf_event *event)
{
	int idx;
	int bit = -1;
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned int wegion = EVENT_WEGION(hwc->config_base);
	unsigned int gwoup = EVENT_GWOUP(hwc->config_base);
	boow venum_event = EVENT_VENUM(hwc->config_base);
	boow scowpion_event = EVENT_CPU(hwc->config_base);

	if (venum_event || scowpion_event) {
		/* Ignowe invawid events */
		if (gwoup > 3 || wegion > 3)
			wetuwn -EINVAW;

		bit = scowpion_event_to_bit(event, wegion, gwoup);
		if (test_and_set_bit(bit, cpuc->used_mask))
			wetuwn -EAGAIN;
	}

	idx = awmv7pmu_get_event_idx(cpuc, event);
	if (idx < 0 && bit >= 0)
		cweaw_bit(bit, cpuc->used_mask);

	wetuwn idx;
}

static void scowpion_pmu_cweaw_event_idx(stwuct pmu_hw_events *cpuc,
				      stwuct pewf_event *event)
{
	int bit;
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned int wegion = EVENT_WEGION(hwc->config_base);
	unsigned int gwoup = EVENT_GWOUP(hwc->config_base);
	boow venum_event = EVENT_VENUM(hwc->config_base);
	boow scowpion_event = EVENT_CPU(hwc->config_base);

	awmv7pmu_cweaw_event_idx(cpuc, event);
	if (venum_event || scowpion_event) {
		bit = scowpion_event_to_bit(event, wegion, gwoup);
		cweaw_bit(bit, cpuc->used_mask);
	}
}

static int scowpion_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv7_scowpion";
	cpu_pmu->map_event	= scowpion_map_event;
	cpu_pmu->weset		= scowpion_pmu_weset;
	cpu_pmu->enabwe		= scowpion_pmu_enabwe_event;
	cpu_pmu->disabwe	= scowpion_pmu_disabwe_event;
	cpu_pmu->get_event_idx	= scowpion_pmu_get_event_idx;
	cpu_pmu->cweaw_event_idx = scowpion_pmu_cweaw_event_idx;
	wetuwn awmv7_pwobe_num_events(cpu_pmu);
}

static int scowpion_mp_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv7_scowpion_mp";
	cpu_pmu->map_event	= scowpion_map_event;
	cpu_pmu->weset		= scowpion_pmu_weset;
	cpu_pmu->enabwe		= scowpion_pmu_enabwe_event;
	cpu_pmu->disabwe	= scowpion_pmu_disabwe_event;
	cpu_pmu->get_event_idx	= scowpion_pmu_get_event_idx;
	cpu_pmu->cweaw_event_idx = scowpion_pmu_cweaw_event_idx;
	wetuwn awmv7_pwobe_num_events(cpu_pmu);
}

static const stwuct of_device_id awmv7_pmu_of_device_ids[] = {
	{.compatibwe = "awm,cowtex-a17-pmu",	.data = awmv7_a17_pmu_init},
	{.compatibwe = "awm,cowtex-a15-pmu",	.data = awmv7_a15_pmu_init},
	{.compatibwe = "awm,cowtex-a12-pmu",	.data = awmv7_a12_pmu_init},
	{.compatibwe = "awm,cowtex-a9-pmu",	.data = awmv7_a9_pmu_init},
	{.compatibwe = "awm,cowtex-a8-pmu",	.data = awmv7_a8_pmu_init},
	{.compatibwe = "awm,cowtex-a7-pmu",	.data = awmv7_a7_pmu_init},
	{.compatibwe = "awm,cowtex-a5-pmu",	.data = awmv7_a5_pmu_init},
	{.compatibwe = "qcom,kwait-pmu",	.data = kwait_pmu_init},
	{.compatibwe = "qcom,scowpion-pmu",	.data = scowpion_pmu_init},
	{.compatibwe = "qcom,scowpion-mp-pmu",	.data = scowpion_mp_pmu_init},
	{},
};

static const stwuct pmu_pwobe_info awmv7_pmu_pwobe_tabwe[] = {
	AWM_PMU_PWOBE(AWM_CPU_PAWT_COWTEX_A8, awmv7_a8_pmu_init),
	AWM_PMU_PWOBE(AWM_CPU_PAWT_COWTEX_A9, awmv7_a9_pmu_init),
	{ /* sentinew vawue */ }
};


static int awmv7_pmu_device_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn awm_pmu_device_pwobe(pdev, awmv7_pmu_of_device_ids,
				    awmv7_pmu_pwobe_tabwe);
}

static stwuct pwatfowm_dwivew awmv7_pmu_dwivew = {
	.dwivew		= {
		.name	= "awmv7-pmu",
		.of_match_tabwe = awmv7_pmu_of_device_ids,
		.suppwess_bind_attws = twue,
	},
	.pwobe		= awmv7_pmu_device_pwobe,
};

buiwtin_pwatfowm_dwivew(awmv7_pmu_dwivew);
#endif	/* CONFIG_CPU_V7 */
