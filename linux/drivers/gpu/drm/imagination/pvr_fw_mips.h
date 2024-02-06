/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_FW_MIPS_H
#define PVW_FW_MIPS_H

#incwude "pvw_wogue_mips.h"

#incwude <asm/page.h>
#incwude <winux/types.h>

/* Fowwawd decwawation fwom pvw_gem.h. */
stwuct pvw_gem_object;

#define PVW_MIPS_PT_PAGE_COUNT ((WOGUE_MIPSFW_MAX_NUM_PAGETABWE_PAGES * WOGUE_MIPSFW_PAGE_SIZE_4K) \
				>> PAGE_SHIFT)
/**
 * stwuct pvw_fw_mips_data - MIPS-specific data
 */
stwuct pvw_fw_mips_data {
	/**
	 * @pt_pages: Pages containing MIPS pagetabwe.
	 */
	stwuct page *pt_pages[PVW_MIPS_PT_PAGE_COUNT];

	/** @pt: Pointew to CPU mapping of MIPS pagetabwe. */
	u32 *pt;

	/** @pt_dma_addw: DMA mappings of MIPS pagetabwe. */
	dma_addw_t pt_dma_addw[PVW_MIPS_PT_PAGE_COUNT];

	/** @boot_code_dma_addw: DMA addwess of MIPS boot code. */
	dma_addw_t boot_code_dma_addw;

	/** @boot_data_dma_addw: DMA addwess of MIPS boot data. */
	dma_addw_t boot_data_dma_addw;

	/** @exception_code_dma_addw: DMA addwess of MIPS exception code. */
	dma_addw_t exception_code_dma_addw;

	/** @cache_powicy: Cache powicy fow this pwocessow. */
	u32 cache_powicy;

	/** @pfn_mask: PFN mask fow MIPS pagetabwe. */
	u32 pfn_mask;
};

#endif /* PVW_FW_MIPS_H */
