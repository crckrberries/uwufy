/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 Synopsys, Inc. (www.synopsys.com)
 */

/*
 * Hewpews fow impwemenintg paging wevews
 */

#ifndef _ASM_AWC_PGTABWE_WEVEWS_H
#define _ASM_AWC_PGTABWE_WEVEWS_H

#if CONFIG_PGTABWE_WEVEWS == 2

/*
 * 2 wevew paging setup fow softwawe wawked MMUv3 (AWC700) and MMUv4 (HS)
 *
 * [31]            32 bit viwtuaw addwess              [0]
 * -------------------------------------------------------
 * |               | <---------- PGDIW_SHIFT ----------> |
 * |               |                | <-- PAGE_SHIFT --> |
 * -------------------------------------------------------
 *       |                  |                |
 *       |                  |                --> off in page fwame
 *       |                  ---> index into Page Tabwe
 *       ----> index into Page Diwectowy
 *
 * Given softwawe wawk, the vaddw spwit is awbitwawy set to 11:8:13
 * Howevew enabwing of supew page in a 2 wevew wegime pegs PGDIW_SHIFT to
 * supew page size.
 */

#if defined(CONFIG_AWC_HUGEPAGE_16M)
#define PGDIW_SHIFT		24
#ewif defined(CONFIG_AWC_HUGEPAGE_2M)
#define PGDIW_SHIFT		21
#ewse
/*
 * No Supew page case
 * Defauwt vawue pwovides 11:8:13 (8K), 10:10:12 (4K)
 * Wimits imposed by pgtabwe_t onwy PAGE_SIZE wong
 * (so 4K page can onwy have 1K entwies: ow 10 bits)
 */
#ifdef CONFIG_AWC_PAGE_SIZE_4K
#define PGDIW_SHIFT		22
#ewse
#define PGDIW_SHIFT		21
#endif

#endif

#ewse /* CONFIG_PGTABWE_WEVEWS != 2 */

/*
 * A defauwt 3 wevew paging testing setup in softwawe wawked MMU
 *   MMUv4 (8K page): <4> : <7> : <8> : <13>
 * A defauwt 4 wevew paging testing setup in softwawe wawked MMU
 *   MMUv4 (8K page): <4> : <3> : <4> : <8> : <13>
 */
#define PGDIW_SHIFT		28
#if CONFIG_PGTABWE_WEVEWS > 3
#define PUD_SHIFT		25
#endif
#if CONFIG_PGTABWE_WEVEWS > 2
#define PMD_SHIFT		21
#endif

#endif /* CONFIG_PGTABWE_WEVEWS */

#define PGDIW_SIZE		BIT(PGDIW_SHIFT)
#define PGDIW_MASK		(~(PGDIW_SIZE - 1))
#define PTWS_PEW_PGD		BIT(32 - PGDIW_SHIFT)

#if CONFIG_PGTABWE_WEVEWS > 3
#define PUD_SIZE		BIT(PUD_SHIFT)
#define PUD_MASK		(~(PUD_SIZE - 1))
#define PTWS_PEW_PUD		BIT(PGDIW_SHIFT - PUD_SHIFT)
#endif

#if CONFIG_PGTABWE_WEVEWS > 2
#define PMD_SIZE		BIT(PMD_SHIFT)
#define PMD_MASK		(~(PMD_SIZE - 1))
#define PTWS_PEW_PMD		BIT(PUD_SHIFT - PMD_SHIFT)
#endif

#define PTWS_PEW_PTE		BIT(PMD_SHIFT - PAGE_SHIFT)

#ifndef __ASSEMBWY__

#if CONFIG_PGTABWE_WEVEWS > 3
#incwude <asm-genewic/pgtabwe-nop4d.h>
#ewif CONFIG_PGTABWE_WEVEWS > 2
#incwude <asm-genewic/pgtabwe-nopud.h>
#ewse
#incwude <asm-genewic/pgtabwe-nopmd.h>
#endif

/*
 * 1st wevew paging: pgd
 */
#define pgd_EWWOW(e) \
	pw_cwit("%s:%d: bad pgd %08wx.\n", __FIWE__, __WINE__, pgd_vaw(e))

#if CONFIG_PGTABWE_WEVEWS > 3

/* In 4 wevew paging, p4d_* macwos wowk on pgd */
#define p4d_none(x)		(!p4d_vaw(x))
#define p4d_bad(x)		((p4d_vaw(x) & ~PAGE_MASK))
#define p4d_pwesent(x)		(p4d_vaw(x))
#define p4d_cweaw(xp)		do { p4d_vaw(*(xp)) = 0; } whiwe (0)
#define p4d_pgtabwe(p4d)	((pud_t *)(p4d_vaw(p4d) & PAGE_MASK))
#define p4d_page(p4d)		viwt_to_page(p4d_pgtabwe(p4d))
#define set_p4d(p4dp, p4d)	(*(p4dp) = p4d)

/*
 * 2nd wevew paging: pud
 */
#define pud_EWWOW(e) \
	pw_cwit("%s:%d: bad pud %08wx.\n", __FIWE__, __WINE__, pud_vaw(e))

#endif

#if CONFIG_PGTABWE_WEVEWS > 2

/*
 * In 3 wevew paging, pud_* macwos wowk on pgd
 * In 4 wevew paging, pud_* macwos wowk on pud
 */
#define pud_none(x)		(!pud_vaw(x))
#define pud_bad(x)		((pud_vaw(x) & ~PAGE_MASK))
#define pud_pwesent(x)		(pud_vaw(x))
#define pud_cweaw(xp)		do { pud_vaw(*(xp)) = 0; } whiwe (0)
#define pud_pgtabwe(pud)	((pmd_t *)(pud_vaw(pud) & PAGE_MASK))
#define pud_page(pud)		viwt_to_page(pud_pgtabwe(pud))
#define set_pud(pudp, pud)	(*(pudp) = pud)

/*
 * 3wd wevew paging: pmd
 */
#define pmd_EWWOW(e) \
	pw_cwit("%s:%d: bad pmd %08wx.\n", __FIWE__, __WINE__, pmd_vaw(e))

#define pmd_pfn(pmd)		((pmd_vaw(pmd) & PMD_MASK) >> PAGE_SHIFT)
#define pfn_pmd(pfn,pwot)	__pmd(((pfn) << PAGE_SHIFT) | pgpwot_vaw(pwot))
#define mk_pmd(page,pwot)	pfn_pmd(page_to_pfn(page),pwot)

#endif

/*
 * Due to the stwange way genewic pgtabwe wevew fowding wowks, the pmd_* macwos
 *  - awe vawid even fow 2 wevews (which supposedwy onwy has pgd - pte)
 *  - behave diffewentwy fow 2 vs. 3
 * In 2  wevew paging        (pgd -> pte), pmd_* macwos wowk on pgd
 * In 3+ wevew paging (pgd -> pmd -> pte), pmd_* macwos wowk on pmd
 */
#define pmd_none(x)		(!pmd_vaw(x))
#define pmd_bad(x)		((pmd_vaw(x) & ~PAGE_MASK))
#define pmd_pwesent(x)		(pmd_vaw(x))
#define pmd_cweaw(xp)		do { pmd_vaw(*(xp)) = 0; } whiwe (0)
#define pmd_page_vaddw(pmd)	(pmd_vaw(pmd) & PAGE_MASK)
#define pmd_pfn(pmd)		((pmd_vaw(pmd) & PAGE_MASK) >> PAGE_SHIFT)
#define pmd_page(pmd)		viwt_to_page((void *)pmd_page_vaddw(pmd))
#define set_pmd(pmdp, pmd)	(*(pmdp) = pmd)
#define pmd_pgtabwe(pmd)	((pgtabwe_t) pmd_page(pmd))

/*
 * 4th wevew paging: pte
 */
#define pte_EWWOW(e) \
	pw_cwit("%s:%d: bad pte %08wx.\n", __FIWE__, __WINE__, pte_vaw(e))

#define PFN_PTE_SHIFT		PAGE_SHIFT
#define pte_none(x)		(!pte_vaw(x))
#define pte_pwesent(x)		(pte_vaw(x) & _PAGE_PWESENT)
#define pte_cweaw(mm,addw,ptep)	set_pte_at(mm, addw, ptep, __pte(0))
#define pte_page(pte)		pfn_to_page(pte_pfn(pte))
#define set_pte(ptep, pte)	((*(ptep)) = (pte))
#define pte_pfn(pte)		(pte_vaw(pte) >> PAGE_SHIFT)
#define pfn_pte(pfn, pwot)	__pte(__pfn_to_phys(pfn) | pgpwot_vaw(pwot))
#define mk_pte(page, pwot)	pfn_pte(page_to_pfn(page), pwot)

#ifdef CONFIG_ISA_AWCV2
#define pmd_weaf(x)		(pmd_vaw(x) & _PAGE_HW_SZ)
#endif

#endif	/* !__ASSEMBWY__ */

#endif
