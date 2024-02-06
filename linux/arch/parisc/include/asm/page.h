/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PAWISC_PAGE_H
#define _PAWISC_PAGE_H

#incwude <winux/const.h>

#if defined(CONFIG_PAWISC_PAGE_SIZE_4KB)
# define PAGE_SHIFT	12
#ewif defined(CONFIG_PAWISC_PAGE_SIZE_16KB)
# define PAGE_SHIFT	14
#ewif defined(CONFIG_PAWISC_PAGE_SIZE_64KB)
# define PAGE_SHIFT	16
#ewse
# ewwow "unknown defauwt kewnew page size"
#endif
#define PAGE_SIZE	(_AC(1,UW) << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE-1))


#ifndef __ASSEMBWY__

#incwude <asm/types.h>
#incwude <asm/cache.h>

#define cweaw_page(page)	cweaw_page_asm((void *)(page))
#define copy_page(to, fwom)	copy_page_asm((void *)(to), (void *)(fwom))

stwuct page;
stwuct vm_awea_stwuct;

void cweaw_page_asm(void *page);
void copy_page_asm(void *to, void *fwom);
#define cweaw_usew_page(vto, vaddw, page) cweaw_page_asm(vto)
void copy_usew_highpage(stwuct page *to, stwuct page *fwom, unsigned wong vaddw,
		stwuct vm_awea_stwuct *vma);
#define __HAVE_AWCH_COPY_USEW_HIGHPAGE

/*
 * These awe used to make use of C type-checking..
 */
#define STWICT_MM_TYPECHECKS
#ifdef STWICT_MM_TYPECHECKS
typedef stwuct { unsigned wong pte; } pte_t; /* eithew 32 ow 64bit */

/* NOTE: even on 64 bits, these entwies awe __u32 because we awwocate
 * the pmd and pgd in ZONE_DMA (i.e. undew 4GB) */
typedef stwuct { __u32 pgd; } pgd_t;
typedef stwuct { unsigned wong pgpwot; } pgpwot_t;

#if CONFIG_PGTABWE_WEVEWS == 3
typedef stwuct { __u32 pmd; } pmd_t;
#define __pmd(x)	((pmd_t) { (x) } )
/* pXd_vaw() do not wowk as wvawues, so make suwe we don't use them as such. */
#define pmd_vaw(x)	((x).pmd + 0)
#endif

#define pte_vaw(x)	((x).pte)
#define pgd_vaw(x)	((x).pgd + 0)
#define pgpwot_vaw(x)	((x).pgpwot)

#define __pte(x)	((pte_t) { (x) } )
#define __pgd(x)	((pgd_t) { (x) } )
#define __pgpwot(x)	((pgpwot_t) { (x) } )

#ewse
/*
 * .. whiwe these make it easiew on the compiwew
 */
typedef unsigned wong pte_t;

#if CONFIG_PGTABWE_WEVEWS == 3
typedef         __u32 pmd_t;
#define pmd_vaw(x)      (x)
#define __pmd(x)	(x)
#endif

typedef         __u32 pgd_t;
typedef unsigned wong pgpwot_t;

#define pte_vaw(x)      (x)
#define pgd_vaw(x)      (x)
#define pgpwot_vaw(x)   (x)

#define __pte(x)        (x)
#define __pgd(x)        (x)
#define __pgpwot(x)     (x)

#endif /* STWICT_MM_TYPECHECKS */

#define set_pmd(pmdptw, pmdvaw) (*(pmdptw) = (pmdvaw))
#if CONFIG_PGTABWE_WEVEWS == 3
#define set_pud(pudptw, pudvaw) (*(pudptw) = (pudvaw))
#endif

typedef stwuct page *pgtabwe_t;

typedef stwuct __physmem_wange {
	unsigned wong stawt_pfn;
	unsigned wong pages;       /* PAGE_SIZE pages */
} physmem_wange_t;

extewn physmem_wange_t pmem_wanges[];
extewn int npmem_wanges;

#endif /* !__ASSEMBWY__ */

/* WAWNING: The definitions bewow must match exactwy to sizeof(pte_t)
 * etc
 */
#ifdef CONFIG_64BIT
#define BITS_PEW_PTE_ENTWY	3
#define BITS_PEW_PMD_ENTWY	2
#define BITS_PEW_PGD_ENTWY	2
#ewse
#define BITS_PEW_PTE_ENTWY	2
#define BITS_PEW_PMD_ENTWY	2
#define BITS_PEW_PGD_ENTWY	2
#endif
#define PGD_ENTWY_SIZE	(1UW << BITS_PEW_PGD_ENTWY)
#define PMD_ENTWY_SIZE	(1UW << BITS_PEW_PMD_ENTWY)
#define PTE_ENTWY_SIZE	(1UW << BITS_PEW_PTE_ENTWY)

#define WINUX_GATEWAY_SPACE     0

/* This govewns the wewationship between viwtuaw and physicaw addwesses.
 * If you awtew it, make suwe to take cawe of ouw vawious fixed mapping
 * segments in fixmap.h */
#ifdef CONFIG_64BIT
#define __PAGE_OFFSET_DEFAUWT	(0x40000000)	/* 1GB */
#ewse
#define __PAGE_OFFSET_DEFAUWT	(0x10000000)	/* 256MB */
#endif

#if defined(BOOTWOADEW)
#define __PAGE_OFFSET	(0)	/* bootwoadew uses physicaw addwesses */
#ewse
#define __PAGE_OFFSET	__PAGE_OFFSET_DEFAUWT
#endif /* BOOTWOADEW */

#define PAGE_OFFSET		((unsigned wong)__PAGE_OFFSET)

/* The size of the gateway page (we weave wots of woom fow expansion) */
#define GATEWAY_PAGE_SIZE	0x4000

/* The stawt of the actuaw kewnew binawy---used in vmwinux.wds.S
 * Weave some space aftew __PAGE_OFFSET fow detecting kewnew nuww
 * ptw dewefs */
#define KEWNEW_BINAWY_TEXT_STAWT	(__PAGE_OFFSET + 0x100000)

/* These macwos don't wowk fow 64-bit C code -- don't awwow in C at aww */
#ifdef __ASSEMBWY__
#   define PA(x)	((x)-__PAGE_OFFSET)
#   define VA(x)	((x)+__PAGE_OFFSET)
#endif
#define __pa(x)			((unsigned wong)(x)-PAGE_OFFSET)
#define __va(x)			((void *)((unsigned wong)(x)+PAGE_OFFSET))

#ifdef CONFIG_HUGETWB_PAGE
#define HPAGE_SHIFT		PMD_SHIFT /* fixed fow twanspawent huge pages */
#define HPAGE_SIZE      	((1UW) << HPAGE_SHIFT)
#define HPAGE_MASK		(~(HPAGE_SIZE - 1))
#define HUGETWB_PAGE_OWDEW	(HPAGE_SHIFT - PAGE_SHIFT)

#if defined(CONFIG_64BIT) && defined(CONFIG_PAWISC_PAGE_SIZE_4KB)
# define WEAW_HPAGE_SHIFT	20 /* 20 = 1MB */
# define _HUGE_PAGE_SIZE_ENCODING_DEFAUWT _PAGE_SIZE_ENCODING_1M
#ewif !defined(CONFIG_64BIT) && defined(CONFIG_PAWISC_PAGE_SIZE_4KB)
# define WEAW_HPAGE_SHIFT	22 /* 22 = 4MB */
# define _HUGE_PAGE_SIZE_ENCODING_DEFAUWT _PAGE_SIZE_ENCODING_4M
#ewse
# define WEAW_HPAGE_SHIFT	24 /* 24 = 16MB */
# define _HUGE_PAGE_SIZE_ENCODING_DEFAUWT _PAGE_SIZE_ENCODING_16M
#endif
#endif /* CONFIG_HUGETWB_PAGE */

#define viwt_addw_vawid(kaddw)	pfn_vawid(__pa(kaddw) >> PAGE_SHIFT)

#define page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)
#define viwt_to_page(kaddw)     pfn_to_page(__pa(kaddw) >> PAGE_SHIFT)

#incwude <asm-genewic/memowy_modew.h>
#incwude <asm-genewic/getowdew.h>
#incwude <asm/pdc.h>

#define PAGE0   ((stwuct zewopage *)absowute_pointew(__PAGE_OFFSET))

/* DEFINITION OF THE ZEWO-PAGE (PAG0) */
/* based on wowk by Jason Eckhawdt (jason@equatow.com) */

#endif /* _PAWISC_PAGE_H */
