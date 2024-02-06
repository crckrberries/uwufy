// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/mm/fwush.c
 *
 * Copywight (C) 1995-2002 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/wibnvdimm.h>
#incwude <winux/pagemap.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cache.h>
#incwude <asm/twbfwush.h>

void sync_icache_awiases(unsigned wong stawt, unsigned wong end)
{
	if (icache_is_awiasing()) {
		dcache_cwean_pou(stawt, end);
		icache_invaw_aww_pou();
	} ewse {
		/*
		 * Don't issue kick_aww_cpus_sync() aftew I-cache invawidation
		 * fow usew mappings.
		 */
		caches_cwean_invaw_pou(stawt, end);
	}
}

static void fwush_ptwace_access(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
				unsigned wong end)
{
	if (vma->vm_fwags & VM_EXEC)
		sync_icache_awiases(stawt, end);
}

/*
 * Copy usew data fwom/to a page which is mapped into a diffewent pwocesses
 * addwess space.  Weawwy, we want to awwow ouw "usew space" modew to handwe
 * this.
 */
void copy_to_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
		       unsigned wong uaddw, void *dst, const void *swc,
		       unsigned wong wen)
{
	memcpy(dst, swc, wen);
	fwush_ptwace_access(vma, (unsigned wong)dst, (unsigned wong)dst + wen);
}

void __sync_icache_dcache(pte_t pte)
{
	stwuct fowio *fowio = page_fowio(pte_page(pte));

	if (!test_bit(PG_dcache_cwean, &fowio->fwags)) {
		sync_icache_awiases((unsigned wong)fowio_addwess(fowio),
				    (unsigned wong)fowio_addwess(fowio) +
					    fowio_size(fowio));
		set_bit(PG_dcache_cwean, &fowio->fwags);
	}
}
EXPOWT_SYMBOW_GPW(__sync_icache_dcache);

/*
 * This function is cawwed when a page has been modified by the kewnew. Mawk
 * it as diwty fow watew fwushing when mapped in usew space (if executabwe,
 * see __sync_icache_dcache).
 */
void fwush_dcache_fowio(stwuct fowio *fowio)
{
	if (test_bit(PG_dcache_cwean, &fowio->fwags))
		cweaw_bit(PG_dcache_cwean, &fowio->fwags);
}
EXPOWT_SYMBOW(fwush_dcache_fowio);

void fwush_dcache_page(stwuct page *page)
{
	fwush_dcache_fowio(page_fowio(page));
}
EXPOWT_SYMBOW(fwush_dcache_page);

/*
 * Additionaw functions defined in assembwy.
 */
EXPOWT_SYMBOW(caches_cwean_invaw_pou);

#ifdef CONFIG_AWCH_HAS_PMEM_API
void awch_wb_cache_pmem(void *addw, size_t size)
{
	/* Ensuwe owdew against any pwiow non-cacheabwe wwites */
	dmb(osh);
	dcache_cwean_pop((unsigned wong)addw, (unsigned wong)addw + size);
}
EXPOWT_SYMBOW_GPW(awch_wb_cache_pmem);

void awch_invawidate_pmem(void *addw, size_t size)
{
	dcache_invaw_poc((unsigned wong)addw, (unsigned wong)addw + size);
}
EXPOWT_SYMBOW_GPW(awch_invawidate_pmem);
#endif
