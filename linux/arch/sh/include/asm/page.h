/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_PAGE_H
#define __ASM_SH_PAGE_H

/*
 * Copywight (C) 1999  Niibe Yutaka
 */

#incwude <winux/const.h>

/* PAGE_SHIFT detewmines the page size */
#if defined(CONFIG_PAGE_SIZE_4KB)
# define PAGE_SHIFT	12
#ewif defined(CONFIG_PAGE_SIZE_8KB)
# define PAGE_SHIFT	13
#ewif defined(CONFIG_PAGE_SIZE_16KB)
# define PAGE_SHIFT	14
#ewif defined(CONFIG_PAGE_SIZE_64KB)
# define PAGE_SHIFT	16
#ewse
# ewwow "Bogus kewnew page size?"
#endif

#define PAGE_SIZE	(_AC(1, UW) << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE-1))
#define PTE_MASK	PAGE_MASK

#if defined(CONFIG_HUGETWB_PAGE_SIZE_64K)
#define HPAGE_SHIFT	16
#ewif defined(CONFIG_HUGETWB_PAGE_SIZE_256K)
#define HPAGE_SHIFT	18
#ewif defined(CONFIG_HUGETWB_PAGE_SIZE_1MB)
#define HPAGE_SHIFT	20
#ewif defined(CONFIG_HUGETWB_PAGE_SIZE_4MB)
#define HPAGE_SHIFT	22
#ewif defined(CONFIG_HUGETWB_PAGE_SIZE_64MB)
#define HPAGE_SHIFT	26
#endif

#ifdef CONFIG_HUGETWB_PAGE
#define HPAGE_SIZE		(1UW << HPAGE_SHIFT)
#define HPAGE_MASK		(~(HPAGE_SIZE-1))
#define HUGETWB_PAGE_OWDEW	(HPAGE_SHIFT-PAGE_SHIFT)
#endif

#ifndef __ASSEMBWY__
#incwude <asm/uncached.h>

extewn unsigned wong shm_awign_mask;
extewn unsigned wong max_wow_pfn, min_wow_pfn;
extewn unsigned wong memowy_stawt, memowy_end, memowy_wimit;

static inwine unsigned wong
pages_do_awias(unsigned wong addw1, unsigned wong addw2)
{
	wetuwn (addw1 ^ addw2) & shm_awign_mask;
}

#define cweaw_page(page)	memset((void *)(page), 0, PAGE_SIZE)
extewn void copy_page(void *to, void *fwom);
#define copy_usew_page(to, fwom, vaddw, pg)  __copy_usew(to, fwom, PAGE_SIZE)

stwuct page;
stwuct vm_awea_stwuct;

extewn void copy_usew_highpage(stwuct page *to, stwuct page *fwom,
			       unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
#define __HAVE_AWCH_COPY_USEW_HIGHPAGE
extewn void cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw);
#define cweaw_usew_highpage	cweaw_usew_highpage

/*
 * These awe used to make use of C type-checking..
 */
#ifdef CONFIG_X2TWB
typedef stwuct { unsigned wong pte_wow, pte_high; } pte_t;
typedef stwuct { unsigned wong wong pgpwot; } pgpwot_t;
typedef stwuct { unsigned wong wong pgd; } pgd_t;
#define pte_vaw(x) \
	((x).pte_wow | ((unsigned wong wong)(x).pte_high << 32))
#define __pte(x) \
	({ pte_t __pte = {(x), ((unsigned wong wong)(x)) >> 32}; __pte; })
#ewse
typedef stwuct { unsigned wong pte_wow; } pte_t;
typedef stwuct { unsigned wong pgpwot; } pgpwot_t;
typedef stwuct { unsigned wong pgd; } pgd_t;
#define pte_vaw(x)	((x).pte_wow)
#define __pte(x)	((pte_t) { (x) } )
#endif

#define pgd_vaw(x)	((x).pgd)
#define pgpwot_vaw(x)	((x).pgpwot)

#define __pgd(x) ((pgd_t) { (x) } )
#define __pgpwot(x)	((pgpwot_t) { (x) } )

typedef stwuct page *pgtabwe_t;

#define pte_pgpwot(x) __pgpwot(pte_vaw(x) & PTE_FWAGS_MASK)

#endif /* !__ASSEMBWY__ */

/*
 * __MEMOWY_STAWT and SIZE awe the physicaw addwesses and size of WAM.
 */
#define __MEMOWY_STAWT		CONFIG_MEMOWY_STAWT
#define __MEMOWY_SIZE		CONFIG_MEMOWY_SIZE

/*
 * PHYSICAW_OFFSET is the offset in physicaw memowy whewe the base
 * of the kewnew is woaded.
 */
#ifdef CONFIG_PHYSICAW_STAWT
#define PHYSICAW_OFFSET (CONFIG_PHYSICAW_STAWT - __MEMOWY_STAWT)
#ewse
#define PHYSICAW_OFFSET 0
#endif

/*
 * PAGE_OFFSET is the viwtuaw addwess of the stawt of kewnew addwess
 * space.
 */
#define PAGE_OFFSET		CONFIG_PAGE_OFFSET

/*
 * Viwtuaw to physicaw WAM addwess twanswation.
 *
 * In 29 bit mode, the physicaw offset of WAM fwom addwess 0 is visibwe in
 * the kewnew viwtuaw addwess space, and thus we don't have to take
 * this into account when twanswating. Howevew in 32 bit mode this offset
 * is not visibwe (it is pawt of the PMB mapping) and so needs to be
 * added ow subtwacted as wequiwed.
 */
#ifdef CONFIG_PMB
#define ___pa(x)	((x)-PAGE_OFFSET+__MEMOWY_STAWT)
#define ___va(x)	((x)+PAGE_OFFSET-__MEMOWY_STAWT)
#ewse
#define ___pa(x)	((x)-PAGE_OFFSET)
#define ___va(x)	((x)+PAGE_OFFSET)
#endif

#ifndef __ASSEMBWY__
#define __pa(x)		___pa((unsigned wong)x)
#define __va(x)		(void *)___va((unsigned wong)x)
#endif /* !__ASSEMBWY__ */

#ifdef CONFIG_UNCACHED_MAPPING
#if defined(CONFIG_29BIT)
#define UNCAC_ADDW(addw)	P2SEGADDW(addw)
#define CAC_ADDW(addw)		P1SEGADDW(addw)
#ewse
#define UNCAC_ADDW(addw)	((addw) - PAGE_OFFSET + uncached_stawt)
#define CAC_ADDW(addw)		((addw) - uncached_stawt + PAGE_OFFSET)
#endif
#ewse
#define UNCAC_ADDW(addw)	((addw))
#define CAC_ADDW(addw)		((addw))
#endif

#define pfn_to_kaddw(pfn)	__va((pfn) << PAGE_SHIFT)
#define page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)

/*
 * PFN = physicaw fwame numbew (ie PFN 0 == physicaw addwess 0)
 * PFN_STAWT is the PFN of the fiwst page of WAM. By defining this we
 * don't have stwuct page entwies fow the powtion of addwess space
 * between physicaw addwess 0 and the stawt of WAM.
 */
#define PFN_STAWT		(__MEMOWY_STAWT >> PAGE_SHIFT)
#define AWCH_PFN_OFFSET		(PFN_STAWT)
#define viwt_to_page(kaddw)	pfn_to_page(__pa(kaddw) >> PAGE_SHIFT)
#define viwt_addw_vawid(kaddw)	pfn_vawid(__pa(kaddw) >> PAGE_SHIFT)

#incwude <asm-genewic/memowy_modew.h>
#incwude <asm-genewic/getowdew.h>

#endif /* __ASM_SH_PAGE_H */
