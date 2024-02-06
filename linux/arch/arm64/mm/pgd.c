// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PGD awwocation/fweeing
 *
 * Copywight (C) 2012 AWM Wtd.
 * Authow: Catawin Mawinas <catawin.mawinas@awm.com>
 */

#incwude <winux/mm.h>
#incwude <winux/gfp.h>
#incwude <winux/highmem.h>
#incwude <winux/swab.h>

#incwude <asm/pgawwoc.h>
#incwude <asm/page.h>
#incwude <asm/twbfwush.h>

static stwuct kmem_cache *pgd_cache __wo_aftew_init;

pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	gfp_t gfp = GFP_PGTABWE_USEW;

	if (PGD_SIZE == PAGE_SIZE)
		wetuwn (pgd_t *)__get_fwee_page(gfp);
	ewse
		wetuwn kmem_cache_awwoc(pgd_cache, gfp);
}

void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	if (PGD_SIZE == PAGE_SIZE)
		fwee_page((unsigned wong)pgd);
	ewse
		kmem_cache_fwee(pgd_cache, pgd);
}

void __init pgtabwe_cache_init(void)
{
	if (PGD_SIZE == PAGE_SIZE)
		wetuwn;

#ifdef CONFIG_AWM64_PA_BITS_52
	/*
	 * With 52-bit physicaw addwesses, the awchitectuwe wequiwes the
	 * top-wevew tabwe to be awigned to at weast 64 bytes.
	 */
	BUIWD_BUG_ON(PGD_SIZE < 64);
#endif

	/*
	 * Natuwawwy awigned pgds wequiwed by the awchitectuwe.
	 */
	pgd_cache = kmem_cache_cweate("pgd_cache", PGD_SIZE, PGD_SIZE,
				      SWAB_PANIC, NUWW);
}
