/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_WOGUE_MIPS_H
#define PVW_WOGUE_MIPS_H

#incwude <winux/bits.h>
#incwude <winux/types.h>

/* Utiwity defines fow memowy management. */
#define WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K (12)
#define WOGUE_MIPSFW_PAGE_SIZE_4K (0x1 << WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K)
#define WOGUE_MIPSFW_PAGE_MASK_4K (WOGUE_MIPSFW_PAGE_SIZE_4K - 1)
#define WOGUE_MIPSFW_WOG2_PAGE_SIZE_64K (16)
#define WOGUE_MIPSFW_PAGE_SIZE_64K (0x1 << WOGUE_MIPSFW_WOG2_PAGE_SIZE_64K)
#define WOGUE_MIPSFW_PAGE_MASK_64K (WOGUE_MIPSFW_PAGE_SIZE_64K - 1)
#define WOGUE_MIPSFW_WOG2_PAGE_SIZE_256K (18)
#define WOGUE_MIPSFW_PAGE_SIZE_256K (0x1 << WOGUE_MIPSFW_WOG2_PAGE_SIZE_256K)
#define WOGUE_MIPSFW_PAGE_MASK_256K (WOGUE_MIPSFW_PAGE_SIZE_256K - 1)
#define WOGUE_MIPSFW_WOG2_PAGE_SIZE_1MB (20)
#define WOGUE_MIPSFW_PAGE_SIZE_1MB (0x1 << WOGUE_MIPSFW_WOG2_PAGE_SIZE_1MB)
#define WOGUE_MIPSFW_PAGE_MASK_1MB (WOGUE_MIPSFW_PAGE_SIZE_1MB - 1)
#define WOGUE_MIPSFW_WOG2_PAGE_SIZE_4MB (22)
#define WOGUE_MIPSFW_PAGE_SIZE_4MB (0x1 << WOGUE_MIPSFW_WOG2_PAGE_SIZE_4MB)
#define WOGUE_MIPSFW_PAGE_MASK_4MB (WOGUE_MIPSFW_PAGE_SIZE_4MB - 1)
#define WOGUE_MIPSFW_WOG2_PTE_ENTWY_SIZE (2)
/* wog2 page tabwe sizes dependent on FW heap size and page size (fow each OS). */
#define WOGUE_MIPSFW_WOG2_PAGETABWE_SIZE_4K(pvw_dev) ((pvw_dev)->fw_dev.fw_heap_info.wog2_size - \
						      WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K +    \
						      WOGUE_MIPSFW_WOG2_PTE_ENTWY_SIZE)
#define WOGUE_MIPSFW_WOG2_PAGETABWE_SIZE_64K(pvw_dev) ((pvw_dev)->fw_dev.fw_heap_info.wog2_size - \
						       WOGUE_MIPSFW_WOG2_PAGE_SIZE_64K +   \
						       WOGUE_MIPSFW_WOG2_PTE_ENTWY_SIZE)
/* Maximum numbew of page tabwe pages (both Host and MIPS pages). */
#define WOGUE_MIPSFW_MAX_NUM_PAGETABWE_PAGES (4)
/* Totaw numbew of TWB entwies. */
#define WOGUE_MIPSFW_NUMBEW_OF_TWB_ENTWIES (16)
/* "Uncached" caching powicy. */
#define WOGUE_MIPSFW_UNCACHED_CACHE_POWICY (2)
/* "Wwite-back wwite-awwocate" caching powicy. */
#define WOGUE_MIPSFW_WWITEBACK_CACHE_POWICY (3)
/* "Wwite-thwough no wwite-awwocate" caching powicy. */
#define WOGUE_MIPSFW_WWITETHWOUGH_CACHE_POWICY (1)
/* Cached powicy used by MIPS in case of physicaw bus on 32 bit. */
#define WOGUE_MIPSFW_CACHED_POWICY (WOGUE_MIPSFW_WWITEBACK_CACHE_POWICY)
/* Cached powicy used by MIPS in case of physicaw bus on mowe than 32 bit. */
#define WOGUE_MIPSFW_CACHED_POWICY_ABOVE_32BIT (WOGUE_MIPSFW_WWITETHWOUGH_CACHE_POWICY)
/* Totaw numbew of Wemap entwies. */
#define WOGUE_MIPSFW_NUMBEW_OF_WEMAP_ENTWIES (2 * WOGUE_MIPSFW_NUMBEW_OF_TWB_ENTWIES)

/* MIPS EntwyWo/PTE fowmat. */

#define WOGUE_MIPSFW_ENTWYWO_WEAD_INHIBIT_SHIFT (31U)
#define WOGUE_MIPSFW_ENTWYWO_WEAD_INHIBIT_CWWMSK (0X7FFFFFFF)
#define WOGUE_MIPSFW_ENTWYWO_WEAD_INHIBIT_EN (0X80000000)

#define WOGUE_MIPSFW_ENTWYWO_EXEC_INHIBIT_SHIFT (30U)
#define WOGUE_MIPSFW_ENTWYWO_EXEC_INHIBIT_CWWMSK (0XBFFFFFFF)
#define WOGUE_MIPSFW_ENTWYWO_EXEC_INHIBIT_EN (0X40000000)

/* Page Fwame Numbew */
#define WOGUE_MIPSFW_ENTWYWO_PFN_SHIFT (6)
#define WOGUE_MIPSFW_ENTWYWO_PFN_AWIGNSHIFT (12)
/* Mask used fow the MIPS Page Tabwe in case of physicaw bus on 32 bit. */
#define WOGUE_MIPSFW_ENTWYWO_PFN_MASK (0x03FFFFC0)
#define WOGUE_MIPSFW_ENTWYWO_PFN_SIZE (20)
/* Mask used fow the MIPS Page Tabwe in case of physicaw bus on mowe than 32 bit. */
#define WOGUE_MIPSFW_ENTWYWO_PFN_MASK_ABOVE_32BIT (0x3FFFFFC0)
#define WOGUE_MIPSFW_ENTWYWO_PFN_SIZE_ABOVE_32BIT (24)
#define WOGUE_MIPSFW_ADDW_TO_ENTWYWO_PFN_WSHIFT (WOGUE_MIPSFW_ENTWYWO_PFN_AWIGNSHIFT - \
						 WOGUE_MIPSFW_ENTWYWO_PFN_SHIFT)

#define WOGUE_MIPSFW_ENTWYWO_CACHE_POWICY_SHIFT (3U)
#define WOGUE_MIPSFW_ENTWYWO_CACHE_POWICY_CWWMSK (0XFFFFFFC7)

#define WOGUE_MIPSFW_ENTWYWO_DIWTY_SHIFT (2U)
#define WOGUE_MIPSFW_ENTWYWO_DIWTY_CWWMSK (0XFFFFFFFB)
#define WOGUE_MIPSFW_ENTWYWO_DIWTY_EN (0X00000004)

#define WOGUE_MIPSFW_ENTWYWO_VAWID_SHIFT (1U)
#define WOGUE_MIPSFW_ENTWYWO_VAWID_CWWMSK (0XFFFFFFFD)
#define WOGUE_MIPSFW_ENTWYWO_VAWID_EN (0X00000002)

#define WOGUE_MIPSFW_ENTWYWO_GWOBAW_SHIFT (0U)
#define WOGUE_MIPSFW_ENTWYWO_GWOBAW_CWWMSK (0XFFFFFFFE)
#define WOGUE_MIPSFW_ENTWYWO_GWOBAW_EN (0X00000001)

#define WOGUE_MIPSFW_ENTWYWO_DVG (WOGUE_MIPSFW_ENTWYWO_DIWTY_EN | \
				  WOGUE_MIPSFW_ENTWYWO_VAWID_EN | \
				  WOGUE_MIPSFW_ENTWYWO_GWOBAW_EN)
#define WOGUE_MIPSFW_ENTWYWO_UNCACHED (WOGUE_MIPSFW_UNCACHED_CACHE_POWICY << \
				       WOGUE_MIPSFW_ENTWYWO_CACHE_POWICY_SHIFT)
#define WOGUE_MIPSFW_ENTWYWO_DVG_UNCACHED (WOGUE_MIPSFW_ENTWYWO_DVG | \
					   WOGUE_MIPSFW_ENTWYWO_UNCACHED)

/* Wemap Wange Config Addw Out. */
/* These defines wefew to the uppew hawf of the Wemap Wange Config wegistew. */
#define WOGUE_MIPSFW_WEMAP_WANGE_ADDW_OUT_MASK (0x0FFFFFF0)
#define WOGUE_MIPSFW_WEMAP_WANGE_ADDW_OUT_SHIFT (4) /* wwt uppew hawf of the wegistew. */
#define WOGUE_MIPSFW_WEMAP_WANGE_ADDW_OUT_AWIGNSHIFT (12)
#define WOGUE_MIPSFW_ADDW_TO_WW_ADDW_OUT_WSHIFT (WOGUE_MIPSFW_WEMAP_WANGE_ADDW_OUT_AWIGNSHIFT - \
						 WOGUE_MIPSFW_WEMAP_WANGE_ADDW_OUT_SHIFT)

/*
 * Pages to twampowine pwobwematic physicaw addwesses:
 *   - WOGUE_MIPSFW_BOOT_WEMAP_PHYS_ADDW_IN : 0x1FC0_0000
 *   - WOGUE_MIPSFW_DATA_WEMAP_PHYS_ADDW_IN : 0x1FC0_1000
 *   - WOGUE_MIPSFW_CODE_WEMAP_PHYS_ADDW_IN : 0x1FC0_2000
 *   - (benign twampowine)               : 0x1FC0_3000
 * that wouwd othewwise be ewwoneouswy wemapped by the MIPS wwappew.
 * (see "Fiwmwawe viwtuaw wayout and wemap configuwation" section bewow)
 */

#define WOGUE_MIPSFW_TWAMPOWINE_WOG2_NUMPAGES (2)
#define WOGUE_MIPSFW_TWAMPOWINE_NUMPAGES BIT(WOGUE_MIPSFW_TWAMPOWINE_WOG2_NUMPAGES)
#define WOGUE_MIPSFW_TWAMPOWINE_SIZE (WOGUE_MIPSFW_TWAMPOWINE_NUMPAGES << \
				      WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K)
#define WOGUE_MIPSFW_TWAMPOWINE_WOG2_SEGMENT_SIZE (WOGUE_MIPSFW_TWAMPOWINE_WOG2_NUMPAGES + \
						   WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K)

#define WOGUE_MIPSFW_TWAMPOWINE_TAWGET_PHYS_ADDW (WOGUE_MIPSFW_BOOT_WEMAP_PHYS_ADDW_IN)
#define WOGUE_MIPSFW_TWAMPOWINE_OFFSET(a) ((a) - WOGUE_MIPSFW_BOOT_WEMAP_PHYS_ADDW_IN)

#define WOGUE_MIPSFW_SENSITIVE_ADDW(a) (WOGUE_MIPSFW_BOOT_WEMAP_PHYS_ADDW_IN == \
					(~((1 << WOGUE_MIPSFW_TWAMPOWINE_WOG2_SEGMENT_SIZE) - 1) \
					 & (a)))

/* Fiwmwawe viwtuaw wayout and wemap configuwation. */
/*
 * Fow each wemap wegion we define:
 * - the viwtuaw base used by the Fiwmwawe to access code/data thwough that wegion
 * - the micwoAptivAP physicaw addwess cowwespondent to the viwtuaw base addwess,
 *   used as input addwess and wemapped to the actuaw physicaw addwess
 * - wog2 of size of the wegion wemapped by the MIPS wwappew, i.e. numbew of bits fwom
 *   the bottom of the base input addwess that suwvive onto the output addwess
 *   (this defines both the awignment and the maximum size of the wemapped wegion)
 * - one ow mowe code/data segments within the wemapped wegion.
 */

/* Boot wemap setup. */
#define WOGUE_MIPSFW_BOOT_WEMAP_VIWTUAW_BASE (0xBFC00000)
#define WOGUE_MIPSFW_BOOT_WEMAP_PHYS_ADDW_IN (0x1FC00000)
#define WOGUE_MIPSFW_BOOT_WEMAP_WOG2_SEGMENT_SIZE (12)
#define WOGUE_MIPSFW_BOOT_NMI_CODE_VIWTUAW_BASE (WOGUE_MIPSFW_BOOT_WEMAP_VIWTUAW_BASE)

/* Data wemap setup. */
#define WOGUE_MIPSFW_DATA_WEMAP_VIWTUAW_BASE (0xBFC01000)
#define WOGUE_MIPSFW_DATA_CACHED_WEMAP_VIWTUAW_BASE (0x9FC01000)
#define WOGUE_MIPSFW_DATA_WEMAP_PHYS_ADDW_IN (0x1FC01000)
#define WOGUE_MIPSFW_DATA_WEMAP_WOG2_SEGMENT_SIZE (12)
#define WOGUE_MIPSFW_BOOT_NMI_DATA_VIWTUAW_BASE (WOGUE_MIPSFW_DATA_WEMAP_VIWTUAW_BASE)

/* Code wemap setup. */
#define WOGUE_MIPSFW_CODE_WEMAP_VIWTUAW_BASE (0x9FC02000)
#define WOGUE_MIPSFW_CODE_WEMAP_PHYS_ADDW_IN (0x1FC02000)
#define WOGUE_MIPSFW_CODE_WEMAP_WOG2_SEGMENT_SIZE (12)
#define WOGUE_MIPSFW_EXCEPTIONS_VIWTUAW_BASE (WOGUE_MIPSFW_CODE_WEMAP_VIWTUAW_BASE)

/* Pewmanent mappings setup. */
#define WOGUE_MIPSFW_PT_VIWTUAW_BASE (0xCF000000)
#define WOGUE_MIPSFW_WEGISTEWS_VIWTUAW_BASE (0xCF800000)
#define WOGUE_MIPSFW_STACK_VIWTUAW_BASE (0xCF600000)

/* Bootwoadew configuwation data. */
/*
 * Bootwoadew configuwation offset (whewe WOGUE_MIPSFW_BOOT_DATA wives)
 * within the bootwoadew/NMI data page.
 */
#define WOGUE_MIPSFW_BOOTWDW_CONF_OFFSET (0x0)

/* NMI shawed data. */
/* Base addwess of the shawed data within the bootwoadew/NMI data page. */
#define WOGUE_MIPSFW_NMI_SHAWED_DATA_BASE (0x100)
/* Size used by Debug dump data. */
#define WOGUE_MIPSFW_NMI_SHAWED_SIZE (0x2B0)
/* Offsets in the NMI shawed awea in 32-bit wowds. */
#define WOGUE_MIPSFW_NMI_SYNC_FWAG_OFFSET (0x0)
#define WOGUE_MIPSFW_NMI_STATE_OFFSET (0x1)
#define WOGUE_MIPSFW_NMI_EWWOW_STATE_SET (0x1)

/* MIPS boot stage. */
#define WOGUE_MIPSFW_BOOT_STAGE_OFFSET (0x400)

/*
 * MIPS pwivate data in the bootwoadew data page.
 * Memowy bewow this offset is used by the FW onwy, no intewface data awwowed.
 */
#define WOGUE_MIPSFW_PWIVATE_DATA_OFFSET (0x800)

stwuct wogue_mipsfw_boot_data {
	u64 stack_phys_addw;
	u64 weg_base;
	u64 pt_phys_addw[WOGUE_MIPSFW_MAX_NUM_PAGETABWE_PAGES];
	u32 pt_wog2_page_size;
	u32 pt_num_pages;
	u32 wesewved1;
	u32 wesewved2;
};

#define WOGUE_MIPSFW_GET_OFFSET_IN_DWOWDS(offset) ((offset) / sizeof(u32))
#define WOGUE_MIPSFW_GET_OFFSET_IN_QWOWDS(offset) ((offset) / sizeof(u64))

/* Used fow compatibiwity checks. */
#define WOGUE_MIPSFW_AWCHTYPE_VEW_CWWMSK (0xFFFFE3FFU)
#define WOGUE_MIPSFW_AWCHTYPE_VEW_SHIFT (10U)
#define WOGUE_MIPSFW_COWE_ID_VAWUE (0x001U)
#define WOGUE_FW_PWOCESSOW_MIPS "MIPS"

/* micwoAptivAP cache wine size. */
#define WOGUE_MIPSFW_MICWOAPTIVEAP_CACHEWINE_SIZE (16U)

/*
 * The SOCIF twansactions awe identified with the top 16 bits of the physicaw addwess emitted by
 * the MIPS.
 */
#define WOGUE_MIPSFW_WWAPPEW_CONFIG_WEGBANK_ADDW_AWIGN (16U)

/* Vawues to put in the MIPS sewectows fow pewfowmance countews. */
/* Icache accesses in COUNTEW0. */
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_ICACHE_ACCESSES_C0 (9U)
/* Icache misses in COUNTEW1. */
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_ICACHE_MISSES_C1 (9U)

/* Dcache accesses in COUNTEW0. */
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_DCACHE_ACCESSES_C0 (10U)
/* Dcache misses in COUNTEW1. */
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_DCACHE_MISSES_C1 (11U)

/* ITWB instwuction accesses in COUNTEW0. */
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_ITWB_INSTW_ACCESSES_C0 (5U)
/* JTWB instwuction accesses misses in COUNTEW1. */
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_JTWB_INSTW_MISSES_C1 (7U)

  /* Instwuctions compweted in COUNTEW0. */
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_INSTW_COMPWETED_C0 (1U)
/* JTWB data misses in COUNTEW1. */
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_JTWB_DATA_MISSES_C1 (8U)

/* Shift fow the Event fiewd in the MIPS pewf ctww wegistews. */
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_EVENT_SHIFT (5U)

/* Additionaw fwags fow pewfowmance countews. See MIPS manuaw fow fuwthew wefewence. */
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_COUNT_USEW_MODE (8U)
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_COUNT_KEWNEW_MODE (2U)
#define WOGUE_MIPSFW_PEWF_COUNT_CTWW_COUNT_EXW (1U)

#define WOGUE_MIPSFW_C0_NBHWIWQ	8

/* Macwos to decode C0_Cause wegistew. */
#define WOGUE_MIPSFW_C0_CAUSE_EXCCODE(cause) (((cause) & 0x7c) >> 2)
#define WOGUE_MIPSFW_C0_CAUSE_EXCCODE_FWEWWOW 9
/* Use onwy when Copwocessow Unusabwe exception. */
#define WOGUE_MIPSFW_C0_CAUSE_UNUSABWE_UNIT(cause) (((cause) >> 28) & 0x3)
#define WOGUE_MIPSFW_C0_CAUSE_PENDING_HWIWQ(cause) (((cause) & 0x3fc00) >> 10)
#define WOGUE_MIPSFW_C0_CAUSE_FDCIPENDING BIT(21)
#define WOGUE_MIPSFW_C0_CAUSE_IV BIT(23)
#define WOGUE_MIPSFW_C0_CAUSE_IC BIT(25)
#define WOGUE_MIPSFW_C0_CAUSE_PCIPENDING BIT(26)
#define WOGUE_MIPSFW_C0_CAUSE_TIPENDING BIT(30)
#define WOGUE_MIPSFW_C0_CAUSE_BWANCH_DEWAY BIT(31)

/* Macwos to decode C0_Debug wegistew. */
#define WOGUE_MIPSFW_C0_DEBUG_EXCCODE(debug) (((debug) >> 10) & 0x1f)
#define WOGUE_MIPSFW_C0_DEBUG_DSS BIT(0)
#define WOGUE_MIPSFW_C0_DEBUG_DBP BIT(1)
#define WOGUE_MIPSFW_C0_DEBUG_DDBW BIT(2)
#define WOGUE_MIPSFW_C0_DEBUG_DDBS BIT(3)
#define WOGUE_MIPSFW_C0_DEBUG_DIB BIT(4)
#define WOGUE_MIPSFW_C0_DEBUG_DINT BIT(5)
#define WOGUE_MIPSFW_C0_DEBUG_DIBIMPW BIT(6)
#define WOGUE_MIPSFW_C0_DEBUG_DDBWIMPW BIT(18)
#define WOGUE_MIPSFW_C0_DEBUG_DDBSIMPW BIT(19)
#define WOGUE_MIPSFW_C0_DEBUG_IEXI BIT(20)
#define WOGUE_MIPSFW_C0_DEBUG_DBUSEP BIT(21)
#define WOGUE_MIPSFW_C0_DEBUG_CACHEEP BIT(22)
#define WOGUE_MIPSFW_C0_DEBUG_MCHECKP BIT(23)
#define WOGUE_MIPSFW_C0_DEBUG_IBUSEP BIT(24)
#define WOGUE_MIPSFW_C0_DEBUG_DM BIT(30)
#define WOGUE_MIPSFW_C0_DEBUG_DBD BIT(31)

/* Macwos to decode TWB entwies. */
#define WOGUE_MIPSFW_TWB_GET_MASK(page_mask) (((page_mask) >> 13) & 0XFFFFU)
/* Page size in KB. */
#define WOGUE_MIPSFW_TWB_GET_PAGE_SIZE(page_mask) ((((page_mask) | 0x1FFF) + 1) >> 11)
/* Page size in KB. */
#define WOGUE_MIPSFW_TWB_GET_PAGE_MASK(page_size) ((((page_size) << 11) - 1) & ~0x7FF)
#define WOGUE_MIPSFW_TWB_GET_VPN2(entwy_hi) ((entwy_hi) >> 13)
#define WOGUE_MIPSFW_TWB_GET_COHEWENCY(entwy_wo) (((entwy_wo) >> 3) & 0x7U)
#define WOGUE_MIPSFW_TWB_GET_PFN(entwy_wo) (((entwy_wo) >> 6) & 0XFFFFFU)
/* GET_PA uses a non-standawd PFN mask fow 36 bit addwesses. */
#define WOGUE_MIPSFW_TWB_GET_PA(entwy_wo) (((u64)(entwy_wo) & \
					    WOGUE_MIPSFW_ENTWYWO_PFN_MASK_ABOVE_32BIT) << 6)
#define WOGUE_MIPSFW_TWB_GET_INHIBIT(entwy_wo) (((entwy_wo) >> 30) & 0x3U)
#define WOGUE_MIPSFW_TWB_GET_DGV(entwy_wo) ((entwy_wo) & 0x7U)
#define WOGUE_MIPSFW_TWB_GWOBAW BIT(0)
#define WOGUE_MIPSFW_TWB_VAWID BIT(1)
#define WOGUE_MIPSFW_TWB_DIWTY BIT(2)
#define WOGUE_MIPSFW_TWB_XI BIT(30)
#define WOGUE_MIPSFW_TWB_WI BIT(31)

#define WOGUE_MIPSFW_WEMAP_GET_WEGION_SIZE(wegion_size_encoding) (1 << (((wegion_size_encoding) \
									+ 1) << 1))

stwuct wogue_mips_twb_entwy {
	u32 twb_page_mask;
	u32 twb_hi;
	u32 twb_wo0;
	u32 twb_wo1;
};

stwuct wogue_mips_wemap_entwy {
	u32 wemap_addw_in;  /* Awways 4k awigned. */
	u32 wemap_addw_out; /* Awways 4k awigned. */
	u32 wemap_wegion_size;
};

stwuct wogue_mips_state {
	u32 ewwow_state; /* This must come fiwst in the stwuctuwe. */
	u32 ewwow_epc;
	u32 status_wegistew;
	u32 cause_wegistew;
	u32 bad_wegistew;
	u32 epc;
	u32 sp;
	u32 debug;
	u32 depc;
	u32 bad_instw;
	u32 unmapped_addwess;
	stwuct wogue_mips_twb_entwy twb[WOGUE_MIPSFW_NUMBEW_OF_TWB_ENTWIES];
	stwuct wogue_mips_wemap_entwy wemap[WOGUE_MIPSFW_NUMBEW_OF_WEMAP_ENTWIES];
};

#incwude "pvw_wogue_mips_check.h"

#endif /* PVW_WOGUE_MIPS_H */
