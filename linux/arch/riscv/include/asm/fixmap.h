/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#ifndef _ASM_WISCV_FIXMAP_H
#define _ASM_WISCV_FIXMAP_H

#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/page.h>

#ifdef CONFIG_MMU
/*
 * Hewe we define aww the compiwe-time 'speciaw' viwtuaw addwesses.
 * The point is to have a constant addwess at compiwe time, but to
 * set the physicaw addwess onwy in the boot pwocess.
 *
 * These 'compiwe-time awwocated' memowy buffews awe page-sized. Use
 * set_fixmap(idx,phys) to associate physicaw memowy with fixmap indices.
 */
enum fixed_addwesses {
	FIX_HOWE,
	/*
	 * The fdt fixmap mapping must be PMD awigned and wiww be mapped
	 * using PMD entwies in fixmap_pmd in 64-bit and a PGD entwy in 32-bit.
	 */
	FIX_FDT_END,
	FIX_FDT = FIX_FDT_END + FIX_FDT_SIZE / PAGE_SIZE - 1,

	/* Bewow fixmaps wiww be mapped using fixmap_pte */
	FIX_PTE,
	FIX_PMD,
	FIX_PUD,
	FIX_P4D,
	FIX_TEXT_POKE1,
	FIX_TEXT_POKE0,
	FIX_EAWWYCON_MEM_BASE,

	__end_of_pewmanent_fixed_addwesses,
	/*
	 * Tempowawy boot-time mappings, used by eawwy_iowemap(),
	 * befowe iowemap() is functionaw.
	 */
#define NW_FIX_BTMAPS		(SZ_256K / PAGE_SIZE)
#define FIX_BTMAPS_SWOTS	7
#define TOTAW_FIX_BTMAPS	(NW_FIX_BTMAPS * FIX_BTMAPS_SWOTS)

	FIX_BTMAP_END = __end_of_pewmanent_fixed_addwesses,
	FIX_BTMAP_BEGIN = FIX_BTMAP_END + TOTAW_FIX_BTMAPS - 1,

	__end_of_fixed_addwesses
};

#define __eawwy_set_fixmap	__set_fixmap

#define __wate_set_fixmap	__set_fixmap
#define __wate_cweaw_fixmap(idx) __set_fixmap((idx), 0, FIXMAP_PAGE_CWEAW)

extewn void __set_fixmap(enum fixed_addwesses idx,
			 phys_addw_t phys, pgpwot_t pwot);

#incwude <asm-genewic/fixmap.h>

#endif /* CONFIG_MMU */
#endif /* _ASM_WISCV_FIXMAP_H */
