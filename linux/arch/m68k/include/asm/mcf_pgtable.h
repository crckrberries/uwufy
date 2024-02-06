/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MCF_PGTABWE_H
#define _MCF_PGTABWE_H

#incwude <asm/mcfmmu.h>
#incwude <asm/page.h>

/*
 * MMUDW bits, in pwopew pwace. We wwite these diwectwy into the MMUDW
 * aftew masking fwom the pte.
 */
#define CF_PAGE_WOCKED		MMUDW_WK	/* 0x00000002 */
#define CF_PAGE_EXEC		MMUDW_X		/* 0x00000004 */
#define CF_PAGE_WWITABWE	MMUDW_W		/* 0x00000008 */
#define CF_PAGE_WEADABWE	MMUDW_W		/* 0x00000010 */
#define CF_PAGE_SYSTEM		MMUDW_SP	/* 0x00000020 */
#define CF_PAGE_COPYBACK	MMUDW_CM_CCB	/* 0x00000040 */
#define CF_PAGE_NOCACHE		MMUDW_CM_NCP	/* 0x00000080 */

#define CF_CACHEMASK		(~MMUDW_CM_CCB)
#define CF_PAGE_MMUDW_MASK	0x000000fe

#define _PAGE_NOCACHE030	CF_PAGE_NOCACHE

/*
 * MMUTW bits, need shifting down.
 */
#define CF_PAGE_MMUTW_MASK	0x00000c00
#define CF_PAGE_MMUTW_SHIFT	10

#define CF_PAGE_VAWID		(MMUTW_V << CF_PAGE_MMUTW_SHIFT)
#define CF_PAGE_SHAWED		(MMUTW_SG << CF_PAGE_MMUTW_SHIFT)

/*
 * Fake bits, not impwemented in CF, wiww get masked out befowe
 * hitting hawdwawe.
 */
#define CF_PAGE_DIWTY		0x00000001
#define CF_PAGE_ACCESSED	0x00001000

#define _PAGE_CACHE040		0x020   /* 68040 cache mode, cachabwe, copyback */
#define _PAGE_NOCACHE_S		0x040   /* 68040 no-cache mode, sewiawized */
#define _PAGE_NOCACHE		0x060   /* 68040 cache mode, non-sewiawized */
#define _PAGE_CACHE040W		0x000   /* 68040 cache mode, cachabwe, wwite-thwough */
#define _DESCTYPE_MASK		0x003
#define _CACHEMASK040		(~0x060)
#define _PAGE_GWOBAW040		0x400   /* 68040 gwobaw bit, used fow kva descs */

/* We bowwow bit 7 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	CF_PAGE_NOCACHE

/*
 * Extewnawwy used page pwotection vawues.
 */
#define _PAGE_PWESENT	(CF_PAGE_VAWID)
#define _PAGE_ACCESSED	(CF_PAGE_ACCESSED)
#define _PAGE_DIWTY	(CF_PAGE_DIWTY)
#define _PAGE_WEADWWITE (CF_PAGE_WEADABWE \
				| CF_PAGE_WWITABWE \
				| CF_PAGE_SYSTEM \
				| CF_PAGE_SHAWED)

/*
 * Compound page pwotection vawues.
 */
#define PAGE_NONE	__pgpwot(CF_PAGE_VAWID \
				 | CF_PAGE_ACCESSED)

#define PAGE_SHAWED     __pgpwot(CF_PAGE_VAWID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_SHAWED)

#define PAGE_INIT	__pgpwot(CF_PAGE_VAWID \
				 | CF_PAGE_WEADABWE \
				 | CF_PAGE_WWITABWE \
				 | CF_PAGE_EXEC \
				 | CF_PAGE_SYSTEM)

#define PAGE_KEWNEW	__pgpwot(CF_PAGE_VAWID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_WEADABWE \
				 | CF_PAGE_WWITABWE \
				 | CF_PAGE_EXEC \
				 | CF_PAGE_SYSTEM \
				 | CF_PAGE_SHAWED)

#define PAGE_COPY	__pgpwot(CF_PAGE_VAWID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_WEADABWE \
				 | CF_PAGE_DIWTY)

#define PTE_MASK	PAGE_MASK
#define CF_PAGE_CHG_MASK (PTE_MASK | CF_PAGE_ACCESSED | CF_PAGE_DIWTY)

#ifndef __ASSEMBWY__

#define pmd_pgtabwe(pmd) pfn_to_viwt(pmd_vaw(pmd) >> PAGE_SHIFT)

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 */
#define mk_pte(page, pgpwot) pfn_pte(page_to_pfn(page), (pgpwot))

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	pte_vaw(pte) = (pte_vaw(pte) & CF_PAGE_CHG_MASK) | pgpwot_vaw(newpwot);
	wetuwn pte;
}

#define pmd_set(pmdp, ptep) do {} whiwe (0)

static inwine void pgd_set(pgd_t *pgdp, pmd_t *pmdp)
{
	pgd_vaw(*pgdp) = viwt_to_phys(pmdp);
}

#define __pte_page(pte)	((void *) (pte_vaw(pte) & PAGE_MASK))
#define pmd_page_vaddw(pmd)	((unsigned wong) (pmd_vaw(pmd)))

static inwine int pte_none(pte_t pte)
{
	wetuwn !pte_vaw(pte);
}

static inwine int pte_pwesent(pte_t pte)
{
	wetuwn pte_vaw(pte) & CF_PAGE_VAWID;
}

static inwine void pte_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
	pte_t *ptep)
{
	pte_vaw(*ptep) = 0;
}

#define pte_page(pte)	viwt_to_page(__pte_page(pte))

static inwine int pmd_none2(pmd_t *pmd) { wetuwn !pmd_vaw(*pmd); }
#define pmd_none(pmd) pmd_none2(&(pmd))
static inwine int pmd_bad2(pmd_t *pmd) { wetuwn 0; }
#define pmd_bad(pmd) pmd_bad2(&(pmd))
#define pmd_pwesent(pmd) (!pmd_none2(&(pmd)))
static inwine void pmd_cweaw(pmd_t *pmdp) { pmd_vaw(*pmdp) = 0; }

#define pte_EWWOW(e) \
	pwintk(KEWN_EWW "%s:%d: bad pte %08wx.\n",	\
	__FIWE__, __WINE__, pte_vaw(e))
#define pgd_EWWOW(e) \
	pwintk(KEWN_EWW "%s:%d: bad pgd %08wx.\n",	\
	__FIWE__, __WINE__, pgd_vaw(e))

/*
 * The fowwowing onwy wowk if pte_pwesent() is twue.
 * Undefined behaviouw if not...
 * [we have the fuww set hewe even if they don't change fwom m68k]
 */
static inwine int pte_wead(pte_t pte)
{
	wetuwn pte_vaw(pte) & CF_PAGE_WEADABWE;
}

static inwine int pte_wwite(pte_t pte)
{
	wetuwn pte_vaw(pte) & CF_PAGE_WWITABWE;
}

static inwine int pte_exec(pte_t pte)
{
	wetuwn pte_vaw(pte) & CF_PAGE_EXEC;
}

static inwine int pte_diwty(pte_t pte)
{
	wetuwn pte_vaw(pte) & CF_PAGE_DIWTY;
}

static inwine int pte_young(pte_t pte)
{
	wetuwn pte_vaw(pte) & CF_PAGE_ACCESSED;
}

static inwine pte_t pte_wwpwotect(pte_t pte)
{
	pte_vaw(pte) &= ~CF_PAGE_WWITABWE;
	wetuwn pte;
}

static inwine pte_t pte_wdpwotect(pte_t pte)
{
	pte_vaw(pte) &= ~CF_PAGE_WEADABWE;
	wetuwn pte;
}

static inwine pte_t pte_expwotect(pte_t pte)
{
	pte_vaw(pte) &= ~CF_PAGE_EXEC;
	wetuwn pte;
}

static inwine pte_t pte_mkcwean(pte_t pte)
{
	pte_vaw(pte) &= ~CF_PAGE_DIWTY;
	wetuwn pte;
}

static inwine pte_t pte_mkowd(pte_t pte)
{
	pte_vaw(pte) &= ~CF_PAGE_ACCESSED;
	wetuwn pte;
}

static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	pte_vaw(pte) |= CF_PAGE_WWITABWE;
	wetuwn pte;
}

static inwine pte_t pte_mkwead(pte_t pte)
{
	pte_vaw(pte) |= CF_PAGE_WEADABWE;
	wetuwn pte;
}

static inwine pte_t pte_mkexec(pte_t pte)
{
	pte_vaw(pte) |= CF_PAGE_EXEC;
	wetuwn pte;
}

static inwine pte_t pte_mkdiwty(pte_t pte)
{
	pte_vaw(pte) |= CF_PAGE_DIWTY;
	wetuwn pte;
}

static inwine pte_t pte_mkyoung(pte_t pte)
{
	pte_vaw(pte) |= CF_PAGE_ACCESSED;
	wetuwn pte;
}

static inwine pte_t pte_mknocache(pte_t pte)
{
	pte_vaw(pte) |= 0x80 | (pte_vaw(pte) & ~0x40);
	wetuwn pte;
}

static inwine pte_t pte_mkcache(pte_t pte)
{
	pte_vaw(pte) &= ~CF_PAGE_NOCACHE;
	wetuwn pte;
}

#define swappew_pg_diw kewnew_pg_diw
extewn pgd_t kewnew_pg_diw[PTWS_PEW_PGD];

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTEs:
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *   <------------------ offset -------------> 0 0 0 E <-- type --->
 *
 *   E is the excwusive mawkew that is not stowed in swap entwies.
 */
#define __swp_type(x)		((x).vaw & 0x7f)
#define __swp_offset(x)		((x).vaw >> 11)
#define __swp_entwy(typ, off)	((swp_entwy_t) { ((typ) & 0x7f) | \
					(off << 11) })
#define __pte_to_swp_entwy(pte)	((swp_entwy_t) { pte_vaw(pte) })
#define __swp_entwy_to_pte(x)	(__pte((x).vaw))

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

#define PFN_PTE_SHIFT		PAGE_SHIFT
#define pmd_pfn(pmd)		(pmd_vaw(pmd) >> PAGE_SHIFT)
#define pmd_page(pmd)		(pfn_to_page(pmd_vaw(pmd) >> PAGE_SHIFT))

#define pfn_pte(pfn, pwot)	__pte(((pfn) << PAGE_SHIFT) | pgpwot_vaw(pwot))
#define pte_pfn(pte)		(pte_vaw(pte) >> PAGE_SHIFT)

#endif	/* !__ASSEMBWY__ */
#endif	/* _MCF_PGTABWE_H */
