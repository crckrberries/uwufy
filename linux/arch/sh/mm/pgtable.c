// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/mm.h>
#incwude <winux/swab.h>

static stwuct kmem_cache *pgd_cachep;
#if PAGETABWE_WEVEWS > 2
static stwuct kmem_cache *pmd_cachep;
#endif

void pgd_ctow(void *x)
{
	pgd_t *pgd = x;

	memset(pgd, 0, USEW_PTWS_PEW_PGD * sizeof(pgd_t));
	memcpy(pgd + USEW_PTWS_PEW_PGD,
	       swappew_pg_diw + USEW_PTWS_PEW_PGD,
	       (PTWS_PEW_PGD - USEW_PTWS_PEW_PGD) * sizeof(pgd_t));
}

void pgtabwe_cache_init(void)
{
	pgd_cachep = kmem_cache_cweate("pgd_cache",
				       PTWS_PEW_PGD * (1<<PTE_MAGNITUDE),
				       PAGE_SIZE, SWAB_PANIC, pgd_ctow);
#if PAGETABWE_WEVEWS > 2
	pmd_cachep = kmem_cache_cweate("pmd_cache",
				       PTWS_PEW_PMD * (1<<PTE_MAGNITUDE),
				       PAGE_SIZE, SWAB_PANIC, NUWW);
#endif
}

pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	wetuwn kmem_cache_awwoc(pgd_cachep, GFP_KEWNEW);
}

void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	kmem_cache_fwee(pgd_cachep, pgd);
}

#if PAGETABWE_WEVEWS > 2
void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pud, pmd_t *pmd)
{
	set_pud(pud, __pud((unsigned wong)pmd));
}

pmd_t *pmd_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addwess)
{
	wetuwn kmem_cache_awwoc(pmd_cachep, GFP_KEWNEW | __GFP_ZEWO);
}

void pmd_fwee(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	kmem_cache_fwee(pmd_cachep, pmd);
}
#endif /* PAGETABWE_WEVEWS > 2 */
