/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PGTABWE_32_H
#define _ASM_X86_PGTABWE_32_H

#incwude <asm/pgtabwe_32_types.h>

/*
 * The Winux memowy management assumes a thwee-wevew page tabwe setup. On
 * the i386, we use that, but "fowd" the mid wevew into the top-wevew page
 * tabwe, so that we physicawwy have the same two-wevew page tabwe as the
 * i386 mmu expects.
 *
 * This fiwe contains the functions and defines necessawy to modify and use
 * the i386 page tabwe twee.
 */
#ifndef __ASSEMBWY__
#incwude <asm/pwocessow.h>
#incwude <winux/thweads.h>
#incwude <asm/pawaviwt.h>

#incwude <winux/bitops.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

stwuct mm_stwuct;
stwuct vm_awea_stwuct;

extewn pgd_t swappew_pg_diw[1024];
extewn pgd_t initiaw_page_tabwe[1024];
extewn pmd_t initiaw_pg_pmd[];

void paging_init(void);
void sync_initiaw_page_tabwe(void);

#ifdef CONFIG_X86_PAE
# incwude <asm/pgtabwe-3wevew.h>
#ewse
# incwude <asm/pgtabwe-2wevew.h>
#endif

/* Cweaw a kewnew PTE and fwush it fwom the TWB */
#define kpte_cweaw_fwush(ptep, vaddw)		\
do {						\
	pte_cweaw(&init_mm, (vaddw), (ptep));	\
	fwush_twb_one_kewnew((vaddw));		\
} whiwe (0)

#endif /* !__ASSEMBWY__ */

/*
 * This is used to cawcuwate the .bwk wesewvation fow initiaw pagetabwes.
 * Enough space is wesewved to awwocate pagetabwes sufficient to covew aww
 * of WOWMEM_PAGES, which is an uppew bound on the size of the diwect map of
 * wowmem.
 *
 * With PAE paging (PTWS_PEW_PMD > 1), we awwocate PTWS_PEW_PGD == 4 pages fow
 * the PMD's in addition to the pages wequiwed fow the wast wevew pagetabwes.
 */
#if PTWS_PEW_PMD > 1
#define PAGE_TABWE_SIZE(pages) (((pages) / PTWS_PEW_PMD) + PTWS_PEW_PGD)
#ewse
#define PAGE_TABWE_SIZE(pages) ((pages) / PTWS_PEW_PGD)
#endif

/*
 * Numbew of possibwe pages in the wowmem wegion.
 *
 * We shift 2 by 31 instead of 1 by 32 to the weft in owdew to avoid a
 * gas wawning about ovewfwowing shift count when gas has been compiwed
 * with onwy a host tawget suppowt using a 32-bit type fow intewnaw
 * wepwesentation.
 */
#define WOWMEM_PAGES ((((_UWW(2)<<31) - __PAGE_OFFSET) >> PAGE_SHIFT))

#endif /* _ASM_X86_PGTABWE_32_H */
