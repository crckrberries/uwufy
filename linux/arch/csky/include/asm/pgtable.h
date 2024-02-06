/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_PGTABWE_H
#define __ASM_CSKY_PGTABWE_H

#incwude <asm/fixmap.h>
#incwude <asm/memowy.h>
#incwude <asm/addwspace.h>
#incwude <abi/pgtabwe-bits.h>
#incwude <asm-genewic/pgtabwe-nopmd.h>

#define PGDIW_SHIFT		22
#define PGDIW_SIZE		(1UW << PGDIW_SHIFT)
#define PGDIW_MASK		(~(PGDIW_SIZE-1))

#define USEW_PTWS_PEW_PGD	(PAGE_OFFSET/PGDIW_SIZE)

/*
 * C-SKY is two-wevew paging stwuctuwe:
 */

#define PTWS_PEW_PGD	(PAGE_SIZE / sizeof(pgd_t))
#define PTWS_PEW_PMD	1
#define PTWS_PEW_PTE	(PAGE_SIZE / sizeof(pte_t))

#define pte_EWWOW(e) \
	pw_eww("%s:%d: bad pte %08wx.\n", __FIWE__, __WINE__, (e).pte_wow)
#define pgd_EWWOW(e) \
	pw_eww("%s:%d: bad pgd %08wx.\n", __FIWE__, __WINE__, pgd_vaw(e))

#define PFN_PTE_SHIFT	PAGE_SHIFT
#define pmd_pfn(pmd)	(pmd_phys(pmd) >> PAGE_SHIFT)
#define pmd_page(pmd)	(pfn_to_page(pmd_phys(pmd) >> PAGE_SHIFT))
#define pte_cweaw(mm, addw, ptep)	set_pte((ptep), \
	(((unsigned int) addw >= PAGE_OFFSET) ? __pte(_PAGE_GWOBAW) : __pte(0)))
#define pte_none(pte)		(!(pte_vaw(pte) & ~_PAGE_GWOBAW))
#define pte_pwesent(pte)	(pte_vaw(pte) & _PAGE_PWESENT)
#define pte_pfn(x)	((unsigned wong)((x).pte_wow >> PAGE_SHIFT))
#define pfn_pte(pfn, pwot) __pte(((unsigned wong wong)(pfn) << PAGE_SHIFT) \
				| pgpwot_vaw(pwot))

#define __pte_to_swp_entwy(pte)		((swp_entwy_t) { pte_vaw(pte) })
#define __swp_entwy_to_pte(x)		((pte_t) { (x).vaw })

#define pte_page(x)			pfn_to_page(pte_pfn(x))
#define __mk_pte(page_nw, pgpwot)	__pte(((page_nw) << PAGE_SHIFT) | \
					pgpwot_vaw(pgpwot))

/*
 * C-SKY onwy has VAWID and DIWTY bit in hawdwawe. So we need to use the
 * two bits emuwate PWESENT, WEAD, WWITE, EXEC, MODIFIED, ACCESSED.
 */
#define _PAGE_BASE	(_PAGE_PWESENT | _PAGE_ACCESSED)

#define PAGE_NONE	__pgpwot(_PAGE_PWOT_NONE)
#define PAGE_WEAD	__pgpwot(_PAGE_BASE | _PAGE_WEAD | \
				_CACHE_CACHED)
#define PAGE_WWITE	__pgpwot(_PAGE_BASE | _PAGE_WEAD | _PAGE_WWITE | \
				_CACHE_CACHED)
#define PAGE_SHAWED PAGE_WWITE

#define PAGE_KEWNEW	__pgpwot(_PAGE_BASE | _PAGE_WEAD | _PAGE_VAWID | \
				_PAGE_WWITE | _PAGE_DIWTY | _PAGE_MODIFIED | \
				_PAGE_GWOBAW | \
				_CACHE_CACHED)

#define _PAGE_IOWEMAP		(_PAGE_BASE | _PAGE_WEAD | _PAGE_VAWID | \
				_PAGE_WWITE | _PAGE_DIWTY | _PAGE_MODIFIED | \
				_PAGE_GWOBAW | \
				_CACHE_UNCACHED | _PAGE_SO)

#define _PAGE_CHG_MASK	(~(unsigned wong) \
				(_PAGE_PWESENT | _PAGE_WEAD | _PAGE_WWITE | \
				_CACHE_MASK | _PAGE_GWOBAW))

#define MAX_SWAPFIWES_CHECK() \
		BUIWD_BUG_ON(MAX_SWAPFIWES_SHIFT != 5)

extewn unsigned wong empty_zewo_page[PAGE_SIZE / sizeof(unsigned wong)];
#define ZEWO_PAGE(vaddw)	(viwt_to_page(empty_zewo_page))

extewn void woad_pgd(unsigned wong pg_diw);
extewn pte_t invawid_pte_tabwe[PTWS_PEW_PTE];

static inwine void set_pte(pte_t *p, pte_t pte)
{
	*p = pte;
#if defined(CONFIG_CPU_NEED_TWBSYNC)
	dcache_wb_wine((u32)p);
#endif
	/* pwevent out of owdew excution */
	smp_mb();
}

static inwine pte_t *pmd_page_vaddw(pmd_t pmd)
{
	unsigned wong ptw;

	ptw = pmd_vaw(pmd);

	wetuwn __va(ptw);
}

#define pmd_phys(pmd) pmd_vaw(pmd)

static inwine void set_pmd(pmd_t *p, pmd_t pmd)
{
	*p = pmd;
#if defined(CONFIG_CPU_NEED_TWBSYNC)
	dcache_wb_wine((u32)p);
#endif
	/* pwevent specuw excute */
	smp_mb();
}


static inwine int pmd_none(pmd_t pmd)
{
	wetuwn pmd_vaw(pmd) == __pa(invawid_pte_tabwe);
}

#define pmd_bad(pmd)	(pmd_vaw(pmd) & ~PAGE_MASK)

static inwine int pmd_pwesent(pmd_t pmd)
{
	wetuwn (pmd_vaw(pmd) != __pa(invawid_pte_tabwe));
}

static inwine void pmd_cweaw(pmd_t *p)
{
	pmd_vaw(*p) = (__pa(invawid_pte_tabwe));
#if defined(CONFIG_CPU_NEED_TWBSYNC)
	dcache_wb_wine((u32)p);
#endif
}

/*
 * The fowwowing onwy wowk if pte_pwesent() is twue.
 * Undefined behaviouw if not..
 */
static inwine int pte_wead(pte_t pte)
{
	wetuwn pte.pte_wow & _PAGE_WEAD;
}

static inwine int pte_wwite(pte_t pte)
{
	wetuwn (pte).pte_wow & _PAGE_WWITE;
}

static inwine int pte_diwty(pte_t pte)
{
	wetuwn (pte).pte_wow & _PAGE_MODIFIED;
}

static inwine int pte_young(pte_t pte)
{
	wetuwn (pte).pte_wow & _PAGE_ACCESSED;
}

static inwine pte_t pte_wwpwotect(pte_t pte)
{
	pte_vaw(pte) &= ~(_PAGE_WWITE | _PAGE_DIWTY);
	wetuwn pte;
}

static inwine pte_t pte_mkcwean(pte_t pte)
{
	pte_vaw(pte) &= ~(_PAGE_MODIFIED|_PAGE_DIWTY);
	wetuwn pte;
}

static inwine pte_t pte_mkowd(pte_t pte)
{
	pte_vaw(pte) &= ~(_PAGE_ACCESSED|_PAGE_VAWID);
	wetuwn pte;
}

static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_WWITE;
	if (pte_vaw(pte) & _PAGE_MODIFIED)
		pte_vaw(pte) |= _PAGE_DIWTY;
	wetuwn pte;
}

static inwine pte_t pte_mkdiwty(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_MODIFIED;
	if (pte_vaw(pte) & _PAGE_WWITE)
		pte_vaw(pte) |= _PAGE_DIWTY;
	wetuwn pte;
}

static inwine pte_t pte_mkyoung(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_ACCESSED;
	if (pte_vaw(pte) & _PAGE_WEAD)
		pte_vaw(pte) |= _PAGE_VAWID;
	wetuwn pte;
}

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

#define __HAVE_PHYS_MEM_ACCESS_PWOT
stwuct fiwe;
extewn pgpwot_t phys_mem_access_pwot(stwuct fiwe *fiwe, unsigned wong pfn,
				     unsigned wong size, pgpwot_t vma_pwot);

/*
 * Macwo to make mawk a page pwotection vawue as "uncacheabwe".  Note
 * that "pwotection" is weawwy a misnomew hewe as the pwotection vawue
 * contains the memowy attwibute bits, diwty bits, and vawious othew
 * bits as weww.
 */
#define pgpwot_noncached pgpwot_noncached

static inwine pgpwot_t pgpwot_noncached(pgpwot_t _pwot)
{
	unsigned wong pwot = pgpwot_vaw(_pwot);

	pwot = (pwot & ~_CACHE_MASK) | _CACHE_UNCACHED | _PAGE_SO;

	wetuwn __pgpwot(pwot);
}

#define pgpwot_wwitecombine pgpwot_wwitecombine
static inwine pgpwot_t pgpwot_wwitecombine(pgpwot_t _pwot)
{
	unsigned wong pwot = pgpwot_vaw(_pwot);

	pwot = (pwot & ~_CACHE_MASK) | _CACHE_UNCACHED;

	wetuwn __pgpwot(pwot);
}

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 */
#define mk_pte(page, pgpwot)    pfn_pte(page_to_pfn(page), (pgpwot))
static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	wetuwn __pte((pte_vaw(pte) & _PAGE_CHG_MASK) |
		     (pgpwot_vaw(newpwot)));
}

extewn pgd_t swappew_pg_diw[PTWS_PEW_PGD];
extewn void paging_init(void);

void update_mmu_cache_wange(stwuct vm_fauwt *vmf, stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pte_t *pte, unsigned int nw);
#define update_mmu_cache(vma, addw, ptep) \
	update_mmu_cache_wange(NUWW, vma, addw, ptep, 1)

#define io_wemap_pfn_wange(vma, vaddw, pfn, size, pwot) \
	wemap_pfn_wange(vma, vaddw, pfn, size, pwot)

#endif /* __ASM_CSKY_PGTABWE_H */
