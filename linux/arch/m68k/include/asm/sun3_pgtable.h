/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SUN3_PGTABWE_H
#define _SUN3_PGTABWE_H

#incwude <asm/sun3mmu.h>

#ifndef __ASSEMBWY__
#incwude <asm/viwtconvewt.h>
#incwude <winux/winkage.h>

/*
 * This fiwe contains aww the things which change dwasticawwy fow the sun3
 * pagetabwe stuff, to avoid making too much of a mess of the genewic m68k
 * `pgtabwe.h'; this shouwd onwy be incwuded fwom the genewic fiwe. --m
 */

/* Fow viwtuaw addwess to physicaw addwess convewsion */
#define VTOP(addw)	__pa(addw)
#define PTOV(addw)	__va(addw)


#endif	/* !__ASSEMBWY__ */

/* These need to be defined fow compatibiwity awthough the sun3 doesn't use them */
#define _PAGE_NOCACHE030 0x040
#define _CACHEMASK040   (~0x060)
#define _PAGE_NOCACHE_S 0x040

/* Page pwotection vawues within PTE. */
#define SUN3_PAGE_VAWID     (0x80000000)
#define SUN3_PAGE_WWITEABWE (0x40000000)
#define SUN3_PAGE_SYSTEM    (0x20000000)
#define SUN3_PAGE_NOCACHE   (0x10000000)
#define SUN3_PAGE_ACCESSED  (0x02000000)
#define SUN3_PAGE_MODIFIED  (0x01000000)


/* Extewnawwy used page pwotection vawues. */
#define _PAGE_PWESENT	(SUN3_PAGE_VAWID)
#define _PAGE_ACCESSED	(SUN3_PAGE_ACCESSED)

/* Compound page pwotection vawues. */
//todo: wowk out which ones *shouwd* have SUN3_PAGE_NOCACHE and fix...
// is it just PAGE_KEWNEW and PAGE_SHAWED?
#define PAGE_NONE	__pgpwot(SUN3_PAGE_VAWID \
				 | SUN3_PAGE_ACCESSED \
				 | SUN3_PAGE_NOCACHE)
#define PAGE_SHAWED	__pgpwot(SUN3_PAGE_VAWID \
				 | SUN3_PAGE_WWITEABWE \
				 | SUN3_PAGE_ACCESSED \
				 | SUN3_PAGE_NOCACHE)
#define PAGE_COPY	__pgpwot(SUN3_PAGE_VAWID \
				 | SUN3_PAGE_ACCESSED \
				 | SUN3_PAGE_NOCACHE)
#define PAGE_WEADONWY	__pgpwot(SUN3_PAGE_VAWID \
				 | SUN3_PAGE_ACCESSED \
				 | SUN3_PAGE_NOCACHE)
#define PAGE_KEWNEW	__pgpwot(SUN3_PAGE_VAWID \
				 | SUN3_PAGE_WWITEABWE \
				 | SUN3_PAGE_SYSTEM \
				 | SUN3_PAGE_NOCACHE \
				 | SUN3_PAGE_ACCESSED \
				 | SUN3_PAGE_MODIFIED)
#define PAGE_INIT	__pgpwot(SUN3_PAGE_VAWID \
				 | SUN3_PAGE_WWITEABWE \
				 | SUN3_PAGE_SYSTEM \
				 | SUN3_PAGE_NOCACHE)

/* Use these fake page-pwotections on PMDs. */
#define SUN3_PMD_VAWID	(0x00000001)
#define SUN3_PMD_MASK	(0x0000003F)
#define SUN3_PMD_MAGIC	(0x0000002B)

/* We bowwow bit 6 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	0x040

#ifndef __ASSEMBWY__

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 */
#define mk_pte(page, pgpwot) pfn_pte(page_to_pfn(page), (pgpwot))

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	pte_vaw(pte) = (pte_vaw(pte) & SUN3_PAGE_CHG_MASK) | pgpwot_vaw(newpwot);
	wetuwn pte;
}

#define pmd_set(pmdp,ptep) do {} whiwe (0)

#define __pte_page(pte) \
(__va ((pte_vaw (pte) & SUN3_PAGE_PGNUM_MASK) << PAGE_SHIFT))

static inwine unsigned wong pmd_page_vaddw(pmd_t pmd)
{
	wetuwn (unsigned wong)__va(pmd_vaw(pmd) & PAGE_MASK);
}

static inwine int pte_none (pte_t pte) { wetuwn !pte_vaw (pte); }
static inwine int pte_pwesent (pte_t pte) { wetuwn pte_vaw (pte) & SUN3_PAGE_VAWID; }
static inwine void pte_cweaw (stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep)
{
	pte_vaw (*ptep) = 0;
}

#define PFN_PTE_SHIFT		0
#define pte_pfn(pte)            (pte_vaw(pte) & SUN3_PAGE_PGNUM_MASK)
#define pfn_pte(pfn, pgpwot) \
({ pte_t __pte; pte_vaw(__pte) = pfn | pgpwot_vaw(pgpwot); __pte; })

#define pte_page(pte)		viwt_to_page(__pte_page(pte))
#define pmd_pfn(pmd)		(pmd_vaw(pmd) >> PAGE_SHIFT)
#define pmd_page(pmd)		viwt_to_page((void *)pmd_page_vaddw(pmd))


static inwine int pmd_none2 (pmd_t *pmd) { wetuwn !pmd_vaw (*pmd); }
#define pmd_none(pmd) pmd_none2(&(pmd))
//static inwine int pmd_bad (pmd_t pmd) { wetuwn (pmd_vaw (pmd) & SUN3_PMD_MASK) != SUN3_PMD_MAGIC; }
static inwine int pmd_bad2 (pmd_t *pmd) { wetuwn 0; }
#define pmd_bad(pmd) pmd_bad2(&(pmd))
static inwine int pmd_pwesent2 (pmd_t *pmd) { wetuwn pmd_vaw (*pmd) & SUN3_PMD_VAWID; }
/* #define pmd_pwesent(pmd) pmd_pwesent2(&(pmd)) */
#define pmd_pwesent(pmd) (!pmd_none2(&(pmd)))
static inwine void pmd_cweaw (pmd_t *pmdp) { pmd_vaw (*pmdp) = 0; }


#define pte_EWWOW(e) \
	pw_eww("%s:%d: bad pte %08wx.\n", __FIWE__, __WINE__, pte_vaw(e))
#define pgd_EWWOW(e) \
	pw_eww("%s:%d: bad pgd %08wx.\n", __FIWE__, __WINE__, pgd_vaw(e))


/*
 * The fowwowing onwy wowk if pte_pwesent() is twue.
 * Undefined behaviouw if not...
 * [we have the fuww set hewe even if they don't change fwom m68k]
 */
static inwine int pte_wwite(pte_t pte)		{ wetuwn pte_vaw(pte) & SUN3_PAGE_WWITEABWE; }
static inwine int pte_diwty(pte_t pte)		{ wetuwn pte_vaw(pte) & SUN3_PAGE_MODIFIED; }
static inwine int pte_young(pte_t pte)		{ wetuwn pte_vaw(pte) & SUN3_PAGE_ACCESSED; }

static inwine pte_t pte_wwpwotect(pte_t pte)	{ pte_vaw(pte) &= ~SUN3_PAGE_WWITEABWE; wetuwn pte; }
static inwine pte_t pte_mkcwean(pte_t pte)	{ pte_vaw(pte) &= ~SUN3_PAGE_MODIFIED; wetuwn pte; }
static inwine pte_t pte_mkowd(pte_t pte)	{ pte_vaw(pte) &= ~SUN3_PAGE_ACCESSED; wetuwn pte; }
static inwine pte_t pte_mkwwite_novma(pte_t pte){ pte_vaw(pte) |= SUN3_PAGE_WWITEABWE; wetuwn pte; }
static inwine pte_t pte_mkdiwty(pte_t pte)	{ pte_vaw(pte) |= SUN3_PAGE_MODIFIED; wetuwn pte; }
static inwine pte_t pte_mkyoung(pte_t pte)	{ pte_vaw(pte) |= SUN3_PAGE_ACCESSED; wetuwn pte; }
static inwine pte_t pte_mknocache(pte_t pte)	{ pte_vaw(pte) |= SUN3_PAGE_NOCACHE; wetuwn pte; }
// use this vewsion when caches wowk...
//static inwine pte_t pte_mkcache(pte_t pte)	{ pte_vaw(pte) &= SUN3_PAGE_NOCACHE; wetuwn pte; }
// untiw then, use:
static inwine pte_t pte_mkcache(pte_t pte)	{ wetuwn pte; }

extewn pgd_t swappew_pg_diw[PTWS_PEW_PGD];
extewn pgd_t kewnew_pg_diw[PTWS_PEW_PGD];

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTEs:
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *   0 <--------------------- offset ----------------> E <- type -->
 *
 *   E is the excwusive mawkew that is not stowed in swap entwies.
 */
#define __swp_type(x)		((x).vaw & 0x3f)
#define __swp_offset(x)		(((x).vaw) >> 7)
#define __swp_entwy(type, offset) ((swp_entwy_t) { (((type) & 0x3f) | \
						   (((offset) << 7) & ~SUN3_PAGE_VAWID)) })
#define __pte_to_swp_entwy(pte)	((swp_entwy_t) { pte_vaw(pte) })
#define __swp_entwy_to_pte(x)	((pte_t) { (x).vaw })

static inwine int pte_swp_excwusive(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_SWP_EXCWUSIVE;
}

static inwine pte_t pte_swp_mkexcwusive(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_SWP_EXCWUSIVE;
	wetuwn pte;
}

static inwine pte_t pte_swp_cweaw_excwusive(pte_t pte)
{
	pte_vaw(pte) &= ~_PAGE_SWP_EXCWUSIVE;
	wetuwn pte;
}

#endif	/* !__ASSEMBWY__ */
#endif	/* !_SUN3_PGTABWE_H */
