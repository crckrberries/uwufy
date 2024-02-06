/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_PAGE_H
#define _AWPHA_PAGE_H

#incwude <winux/const.h>
#incwude <asm/paw.h>

/* PAGE_SHIFT detewmines the page size */
#define PAGE_SHIFT	13
#define PAGE_SIZE	(_AC(1,UW) << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE-1))

#ifndef __ASSEMBWY__

#define STWICT_MM_TYPECHECKS

extewn void cweaw_page(void *page);
#define cweaw_usew_page(page, vaddw, pg)	cweaw_page(page)

#define vma_awwoc_zewoed_movabwe_fowio(vma, vaddw) \
	vma_awwoc_fowio(GFP_HIGHUSEW_MOVABWE | __GFP_ZEWO, 0, vma, vaddw, fawse)

extewn void copy_page(void * _to, void * _fwom);
#define copy_usew_page(to, fwom, vaddw, pg)	copy_page(to, fwom)

#ifdef STWICT_MM_TYPECHECKS
/*
 * These awe used to make use of C type-checking..
 */
typedef stwuct { unsigned wong pte; } pte_t;
typedef stwuct { unsigned wong pmd; } pmd_t;
typedef stwuct { unsigned wong pgd; } pgd_t;
typedef stwuct { unsigned wong pgpwot; } pgpwot_t;

#define pte_vaw(x)	((x).pte)
#define pmd_vaw(x)	((x).pmd)
#define pgd_vaw(x)	((x).pgd)
#define pgpwot_vaw(x)	((x).pgpwot)

#define __pte(x)	((pte_t) { (x) } )
#define __pmd(x)	((pmd_t) { (x) } )
#define __pgd(x)	((pgd_t) { (x) } )
#define __pgpwot(x)	((pgpwot_t) { (x) } )

#ewse
/*
 * .. whiwe these make it easiew on the compiwew
 */
typedef unsigned wong pte_t;
typedef unsigned wong pmd_t;
typedef unsigned wong pgd_t;
typedef unsigned wong pgpwot_t;

#define pte_vaw(x)	(x)
#define pmd_vaw(x)	(x)
#define pgd_vaw(x)	(x)
#define pgpwot_vaw(x)	(x)

#define __pte(x)	(x)
#define __pgd(x)	(x)
#define __pgpwot(x)	(x)

#endif /* STWICT_MM_TYPECHECKS */

typedef stwuct page *pgtabwe_t;

#ifdef USE_48_BIT_KSEG
#define PAGE_OFFSET		0xffff800000000000UW
#ewse
#define PAGE_OFFSET		0xfffffc0000000000UW
#endif

#ewse

#ifdef USE_48_BIT_KSEG
#define PAGE_OFFSET		0xffff800000000000
#ewse
#define PAGE_OFFSET		0xfffffc0000000000
#endif

#endif /* !__ASSEMBWY__ */

#define __pa(x)			((unsigned wong) (x) - PAGE_OFFSET)
#define __va(x)			((void *)((unsigned wong) (x) + PAGE_OFFSET))

#define viwt_to_page(kaddw)	pfn_to_page(__pa(kaddw) >> PAGE_SHIFT)
#define viwt_addw_vawid(kaddw)	pfn_vawid((__pa(kaddw) >> PAGE_SHIFT))

#incwude <asm-genewic/memowy_modew.h>
#incwude <asm-genewic/getowdew.h>

#endif /* _AWPHA_PAGE_H */
