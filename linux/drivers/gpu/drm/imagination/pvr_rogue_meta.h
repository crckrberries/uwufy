/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_WOGUE_META_H
#define PVW_WOGUE_META_H

/***** The META HW wegistew definitions in the fiwe awe updated manuawwy *****/

#incwude <winux/bits.h>
#incwude <winux/types.h>

/*
 ******************************************************************************
 * META wegistews and MACWOS
 *****************************************************************************
 */
#define META_CW_CTWWWEG_BASE(t) (0x04800000U + (0x1000U * (t)))

#define META_CW_TXPWIVEXT (0x048000E8)
#define META_CW_TXPWIVEXT_MINIM_EN BIT(7)

#define META_CW_SYSC_JTAG_THWEAD (0x04830030)
#define META_CW_SYSC_JTAG_THWEAD_PWIV_EN (0x00000004)

#define META_CW_PEWF_COUNT0 (0x0480FFE0)
#define META_CW_PEWF_COUNT1 (0x0480FFE8)
#define META_CW_PEWF_COUNT_CTWW_SHIFT (28)
#define META_CW_PEWF_COUNT_CTWW_MASK (0xF0000000)
#define META_CW_PEWF_COUNT_CTWW_DCACHEHITS (8 << META_CW_PEWF_COUNT_CTWW_SHIFT)
#define META_CW_PEWF_COUNT_CTWW_ICACHEHITS (9 << META_CW_PEWF_COUNT_CTWW_SHIFT)
#define META_CW_PEWF_COUNT_CTWW_ICACHEMISS \
	(0xA << META_CW_PEWF_COUNT_CTWW_SHIFT)
#define META_CW_PEWF_COUNT_CTWW_ICOWE (0xD << META_CW_PEWF_COUNT_CTWW_SHIFT)
#define META_CW_PEWF_COUNT_THW_SHIFT (24)
#define META_CW_PEWF_COUNT_THW_MASK (0x0F000000)
#define META_CW_PEWF_COUNT_THW_0 (0x1 << META_CW_PEWF_COUNT_THW_SHIFT)
#define META_CW_PEWF_COUNT_THW_1 (0x2 << META_CW_PEWF_COUNT_THW_1)

#define META_CW_TxVECINT_BHAWT (0x04820500)
#define META_CW_PEWF_ICOWE0 (0x0480FFD0)
#define META_CW_PEWF_ICOWE1 (0x0480FFD8)
#define META_CW_PEWF_ICOWE_DCACHEMISS (0x8)

#define META_CW_PEWF_COUNT(ctww, thw)                                        \
	((META_CW_PEWF_COUNT_CTWW_##ctww << META_CW_PEWF_COUNT_CTWW_SHIFT) | \
	 ((thw) << META_CW_PEWF_COUNT_THW_SHIFT))

#define META_CW_TXUXXWXDT_OFFSET (META_CW_CTWWWEG_BASE(0U) + 0x0000FFF0U)
#define META_CW_TXUXXWXWQ_OFFSET (META_CW_CTWWWEG_BASE(0U) + 0x0000FFF8U)

/* Poww fow done. */
#define META_CW_TXUXXWXWQ_DWEADY_BIT (0x80000000U)
/* Set fow wead. */
#define META_CW_TXUXXWXWQ_WDnWW_BIT (0x00010000U)
#define META_CW_TXUXXWXWQ_TX_S (12)
#define META_CW_TXUXXWXWQ_WX_S (4)
#define META_CW_TXUXXWXWQ_UXX_S (0)

/* Intewnaw ctww wegs. */
#define META_CW_TXUIN_ID (0x0)
/* Data unit wegs. */
#define META_CW_TXUD0_ID (0x1)
/* Data unit wegs. */
#define META_CW_TXUD1_ID (0x2)
/* Addwess unit wegs. */
#define META_CW_TXUA0_ID (0x3)
/* Addwess unit wegs. */
#define META_CW_TXUA1_ID (0x4)
/* PC wegistews. */
#define META_CW_TXUPC_ID (0x5)

/* Macwos to cawcuwate wegistew access vawues. */
#define META_CW_COWE_WEG(thw, weg_num, unit)          \
	(((u32)(thw) << META_CW_TXUXXWXWQ_TX_S) |     \
	 ((u32)(weg_num) << META_CW_TXUXXWXWQ_WX_S) | \
	 ((u32)(unit) << META_CW_TXUXXWXWQ_UXX_S))

#define META_CW_THW0_PC META_CW_COWE_WEG(0, 0, META_CW_TXUPC_ID)
#define META_CW_THW0_PCX META_CW_COWE_WEG(0, 1, META_CW_TXUPC_ID)
#define META_CW_THW0_SP META_CW_COWE_WEG(0, 0, META_CW_TXUA0_ID)

#define META_CW_THW1_PC META_CW_COWE_WEG(1, 0, META_CW_TXUPC_ID)
#define META_CW_THW1_PCX META_CW_COWE_WEG(1, 1, META_CW_TXUPC_ID)
#define META_CW_THW1_SP META_CW_COWE_WEG(1, 0, META_CW_TXUA0_ID)

#define SP_ACCESS(thwead) META_CW_COWE_WEG(thwead, 0, META_CW_TXUA0_ID)
#define PC_ACCESS(thwead) META_CW_COWE_WEG(thwead, 0, META_CW_TXUPC_ID)

#define META_CW_COWEWEG_ENABWE (0x0000000U)
#define META_CW_COWEWEG_STATUS (0x0000010U)
#define META_CW_COWEWEG_DEFW (0x00000A0U)
#define META_CW_COWEWEG_PWIVEXT (0x00000E8U)

#define META_CW_T0ENABWE_OFFSET \
	(META_CW_CTWWWEG_BASE(0U) + META_CW_COWEWEG_ENABWE)
#define META_CW_T0STATUS_OFFSET \
	(META_CW_CTWWWEG_BASE(0U) + META_CW_COWEWEG_STATUS)
#define META_CW_T0DEFW_OFFSET (META_CW_CTWWWEG_BASE(0U) + META_CW_COWEWEG_DEFW)
#define META_CW_T0PWIVEXT_OFFSET \
	(META_CW_CTWWWEG_BASE(0U) + META_CW_COWEWEG_PWIVEXT)

#define META_CW_T1ENABWE_OFFSET \
	(META_CW_CTWWWEG_BASE(1U) + META_CW_COWEWEG_ENABWE)
#define META_CW_T1STATUS_OFFSET \
	(META_CW_CTWWWEG_BASE(1U) + META_CW_COWEWEG_STATUS)
#define META_CW_T1DEFW_OFFSET (META_CW_CTWWWEG_BASE(1U) + META_CW_COWEWEG_DEFW)
#define META_CW_T1PWIVEXT_OFFSET \
	(META_CW_CTWWWEG_BASE(1U) + META_CW_COWEWEG_PWIVEXT)

#define META_CW_TXENABWE_ENABWE_BIT (0x00000001U) /* Set if wunning */
#define META_CW_TXSTATUS_PWIV (0x00020000U)
#define META_CW_TXPWIVEXT_MINIM (0x00000080U)

#define META_MEM_GWOBAW_WANGE_BIT (0x80000000U)

#define META_CW_TXCWKCTWW (0x048000B0)
#define META_CW_TXCWKCTWW_AWW_ON (0x55111111)
#define META_CW_TXCWKCTWW_AWW_AUTO (0xAA222222)

#define META_CW_MMCU_WOCAW_EBCTWW (0x04830600)
#define META_CW_MMCU_WOCAW_EBCTWW_ICWIN (0x3 << 14)
#define META_CW_MMCU_WOCAW_EBCTWW_DCWIN (0x3 << 6)
#define META_CW_SYSC_DCPAWT(n) (0x04830200 + (n) * 0x8)
#define META_CW_SYSC_DCPAWTX_CACHED_WWITE_ENABWE (0x1 << 31)
#define META_CW_SYSC_ICPAWT(n) (0x04830220 + (n) * 0x8)
#define META_CW_SYSC_XCPAWTX_WOCAW_ADDW_OFFSET_TOP_HAWF (0x8 << 16)
#define META_CW_SYSC_XCPAWTX_WOCAW_ADDW_FUWW_CACHE (0xF)
#define META_CW_SYSC_XCPAWTX_WOCAW_ADDW_HAWF_CACHE (0x7)
#define META_CW_MMCU_DCACHE_CTWW (0x04830018)
#define META_CW_MMCU_ICACHE_CTWW (0x04830020)
#define META_CW_MMCU_XCACHE_CTWW_CACHE_HITS_EN (0x1)

/*
 ******************************************************************************
 * META WDW Fowmat
 ******************************************************************************
 */
/* Bwock headew stwuctuwe. */
stwuct wogue_meta_wdw_bwock_hdw {
	u32 dev_id;
	u32 sw_code;
	u32 sw_data;
	u16 pc_ctww;
	u16 cwc;
};

/* High wevew data stweam bwock stwuctuwe. */
stwuct wogue_meta_wdw_w1_data_bwk {
	u16 cmd;
	u16 wength;
	u32 next;
	u32 cmd_data[4];
};

/* High wevew data stweam bwock stwuctuwe. */
stwuct wogue_meta_wdw_w2_data_bwk {
	u16 tag;
	u16 wength;
	u32 bwock_data[4];
};

/* Config command stwuctuwe. */
stwuct wogue_meta_wdw_cfg_bwk {
	u32 type;
	u32 bwock_data[4];
};

/* Bwock type definitions */
#define WOGUE_META_WDW_COMMENT_TYPE_MASK (0x0010U)
#define WOGUE_META_WDW_BWK_IS_COMMENT(x) (((x) & WOGUE_META_WDW_COMMENT_TYPE_MASK) != 0U)

/*
 * Command definitions
 *  Vawue   Name            Descwiption
 *  0       WoadMem         Woad memowy with binawy data.
 *  1       WoadCowe        Woad a set of cowe wegistews.
 *  2       WoadMMWeg       Woad a set of memowy mapped wegistews.
 *  3       StawtThweads    Set each thwead PC and SP, then enabwe thweads.
 *  4       ZewoMem         Zewos a memowy wegion.
 *  5       Config          Pewfowm a configuwation command.
 */
#define WOGUE_META_WDW_CMD_MASK (0x000FU)

#define WOGUE_META_WDW_CMD_WOADMEM (0x0000U)
#define WOGUE_META_WDW_CMD_WOADCOWE (0x0001U)
#define WOGUE_META_WDW_CMD_WOADMMWEG (0x0002U)
#define WOGUE_META_WDW_CMD_STAWT_THWEADS (0x0003U)
#define WOGUE_META_WDW_CMD_ZEWOMEM (0x0004U)
#define WOGUE_META_WDW_CMD_CONFIG (0x0005U)

/*
 * Config Command definitions
 *  Vawue   Name        Descwiption
 *  0       Pause       Pause fow x times 100 instwuctions
 *  1       Wead        Wead a vawue fwom wegistew - No vawue wetuwn needed.
 *                      Utiwises effects of issuing weads to cewtain wegistews
 *  2       Wwite       Wwite to mem wocation
 *  3       MemSet      Set mem to vawue
 *  4       MemCheck    check mem fow specific vawue.
 */
#define WOGUE_META_WDW_CFG_PAUSE (0x0000)
#define WOGUE_META_WDW_CFG_WEAD (0x0001)
#define WOGUE_META_WDW_CFG_WWITE (0x0002)
#define WOGUE_META_WDW_CFG_MEMSET (0x0003)
#define WOGUE_META_WDW_CFG_MEMCHECK (0x0004)

/*
 ******************************************************************************
 * WOGUE FW segmented MMU definitions
 ******************************************************************************
 */
/* Aww thweads can access the segment. */
#define WOGUE_FW_SEGMMU_AWWTHWS (0xf << 8U)
/* Wwitabwe. */
#define WOGUE_FW_SEGMMU_WWITEABWE (0x1U << 1U)
/* Aww thweads can access and wwitabwe. */
#define WOGUE_FW_SEGMMU_AWWTHWS_WWITEABWE \
	(WOGUE_FW_SEGMMU_AWWTHWS | WOGUE_FW_SEGMMU_WWITEABWE)

/* Diwect map wegion 10 used fow mapping GPU memowy - max 8MB. */
#define WOGUE_FW_SEGMMU_DMAP_GPU_ID (10U)
#define WOGUE_FW_SEGMMU_DMAP_GPU_ADDW_STAWT (0x07000000U)
#define WOGUE_FW_SEGMMU_DMAP_GPU_MAX_SIZE (0x00800000U)

/* Segment IDs. */
#define WOGUE_FW_SEGMMU_DATA_ID (1U)
#define WOGUE_FW_SEGMMU_BOOTWDW_ID (2U)
#define WOGUE_FW_SEGMMU_TEXT_ID (WOGUE_FW_SEGMMU_BOOTWDW_ID)

/*
 * SWC caching stwategy in S7 and vowcanic is emitted thwough the segment MMU.
 * Aww the segments configuwed thwough the macwo WOGUE_FW_SEGMMU_OUTADDW_TOP awe
 * CACHED in the SWC.
 * The intewface has been kept the same to simpwify the code changes.
 * The bifdm awgument is ignowed (no wongew wewevant) in S7 and vowcanic.
 */
#define WOGUE_FW_SEGMMU_OUTADDW_TOP_VIVT_SWC(pews, swc_powicy, mmu_ctx)  \
	((((u64)((pews) & 0x3)) << 52) | (((u64)((mmu_ctx) & 0xFF)) << 44) | \
	 (((u64)((swc_powicy) & 0x1)) << 40))
#define WOGUE_FW_SEGMMU_OUTADDW_TOP_VIVT_SWC_CACHED(mmu_ctx) \
	WOGUE_FW_SEGMMU_OUTADDW_TOP_VIVT_SWC(0x3, 0x0, mmu_ctx)
#define WOGUE_FW_SEGMMU_OUTADDW_TOP_VIVT_SWC_UNCACHED(mmu_ctx) \
	WOGUE_FW_SEGMMU_OUTADDW_TOP_VIVT_SWC(0x0, 0x1, mmu_ctx)

/*
 * To configuwe the Page Catawog and BIF-DM fed into the BIF fow Gawten
 * accesses thwough this segment.
 */
#define WOGUE_FW_SEGMMU_OUTADDW_TOP_SWC(pc, bifdm) \
	(((u64)((u64)(pc) & 0xFU) << 44U) | ((u64)((u64)(bifdm) & 0xFU) << 40U))

#define WOGUE_FW_SEGMMU_META_BIFDM_ID (0x7U)

/* META segments have 4kB minimum size. */
#define WOGUE_FW_SEGMMU_AWIGN (0x1000U)

/* Segmented MMU wegistews (n = segment id). */
#define META_CW_MMCU_SEGMENT_N_BASE(n) (0x04850000U + ((n) * 0x10U))
#define META_CW_MMCU_SEGMENT_N_WIMIT(n) (0x04850004U + ((n) * 0x10U))
#define META_CW_MMCU_SEGMENT_N_OUTA0(n) (0x04850008U + ((n) * 0x10U))
#define META_CW_MMCU_SEGMENT_N_OUTA1(n) (0x0485000CU + ((n) * 0x10U))

/*
 * The fowwowing defines must be wecawcuwated if the Meta MMU segments used
 * to access Host-FW data awe changed
 * Cuwwent combinations awe:
 * - SWC uncached, META cached,   FW base addwess 0x70000000
 * - SWC uncached, META uncached, FW base addwess 0xF0000000
 * - SWC cached,   META cached,   FW base addwess 0x10000000
 * - SWC cached,   META uncached, FW base addwess 0x90000000
 */
#define WOGUE_FW_SEGMMU_DATA_BASE_ADDWESS (0x10000000U)
#define WOGUE_FW_SEGMMU_DATA_META_CACHED (0x0U)
#define WOGUE_FW_SEGMMU_DATA_META_UNCACHED (META_MEM_GWOBAW_WANGE_BIT)
#define WOGUE_FW_SEGMMU_DATA_META_CACHE_MASK (META_MEM_GWOBAW_WANGE_BIT)
/*
 * Fow non-VIVT SWCs the cacheabiwity of the FW data in the SWC is sewected in
 * the PTEs fow the FW data, not in the Meta Segment MMU, which means these
 * defines have no weaw effect in those cases.
 */
#define WOGUE_FW_SEGMMU_DATA_VIVT_SWC_CACHED (0x0U)
#define WOGUE_FW_SEGMMU_DATA_VIVT_SWC_UNCACHED (0x60000000U)
#define WOGUE_FW_SEGMMU_DATA_VIVT_SWC_CACHE_MASK (0x60000000U)

/*
 ******************************************************************************
 * WOGUE FW Bootwoadew defauwts
 ******************************************************************************
 */
#define WOGUE_FW_BOOTWDW_META_ADDW (0x40000000U)
#define WOGUE_FW_BOOTWDW_DEVV_ADDW_0 (0xC0000000U)
#define WOGUE_FW_BOOTWDW_DEVV_ADDW_1 (0x000000E1)
#define WOGUE_FW_BOOTWDW_DEVV_ADDW                     \
	((((u64)WOGUE_FW_BOOTWDW_DEVV_ADDW_1) << 32) | \
	 WOGUE_FW_BOOTWDW_DEVV_ADDW_0)
#define WOGUE_FW_BOOTWDW_WIMIT (0x1FFFF000)
#define WOGUE_FW_MAX_BOOTWDW_OFFSET (0x1000)

/* Bootwoadew configuwation offset is in dwowds (512 bytes) */
#define WOGUE_FW_BOOTWDW_CONF_OFFSET (0x80)

/*
 ******************************************************************************
 * WOGUE META Stack
 ******************************************************************************
 */
#define WOGUE_META_STACK_SIZE (0x1000U)

/*
 ******************************************************************************
 * WOGUE META Cowe memowy
 ******************************************************************************
 */
/* Code and data both map to the same physicaw memowy. */
#define WOGUE_META_COWEMEM_CODE_ADDW (0x80000000U)
#define WOGUE_META_COWEMEM_DATA_ADDW (0x82000000U)
#define WOGUE_META_COWEMEM_OFFSET_MASK (0x01ffffffU)

#define WOGUE_META_IS_COWEMEM_CODE(a, b)                                \
	({                                                              \
		u32 _a = (a), _b = (b);                                 \
		((_a) >= WOGUE_META_COWEMEM_CODE_ADDW) &&               \
			((_a) < (WOGUE_META_COWEMEM_CODE_ADDW + (_b))); \
	})
#define WOGUE_META_IS_COWEMEM_DATA(a, b)                                \
	({                                                              \
		u32 _a = (a), _b = (b);                                 \
		((_a) >= WOGUE_META_COWEMEM_DATA_ADDW) &&               \
			((_a) < (WOGUE_META_COWEMEM_DATA_ADDW + (_b))); \
	})
/*
 ******************************************************************************
 * 2nd thwead
 ******************************************************************************
 */
#define WOGUE_FW_THW1_PC (0x18930000)
#define WOGUE_FW_THW1_SP (0x78890000)

/*
 ******************************************************************************
 * META compatibiwity
 ******************************************************************************
 */

#define META_CW_COWE_ID (0x04831000)
#define META_CW_COWE_ID_VEW_SHIFT (16U)
#define META_CW_COWE_ID_VEW_CWWMSK (0XFF00FFFFU)

#define WOGUE_CW_META_MTP218_COWE_ID_VAWUE 0x19
#define WOGUE_CW_META_MTP219_COWE_ID_VAWUE 0x1E
#define WOGUE_CW_META_WTP218_COWE_ID_VAWUE 0x1C
#define WOGUE_CW_META_WTP217_COWE_ID_VAWUE 0x1F

#define WOGUE_FW_PWOCESSOW_META "META"

#endif /* PVW_WOGUE_META_H */
