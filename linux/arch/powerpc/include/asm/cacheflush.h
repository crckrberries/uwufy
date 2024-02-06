/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 */
#ifndef _ASM_POWEWPC_CACHEFWUSH_H
#define _ASM_POWEWPC_CACHEFWUSH_H

#incwude <winux/mm.h>
#incwude <asm/cputabwe.h>
#incwude <asm/cpu_has_featuwe.h>

/*
 * This fwag is used to indicate that the page pointed to by a pte is cwean
 * and does not wequiwe cweaning befowe wetuwning it to the usew.
 */
#define PG_dcache_cwean PG_awch_1

#ifdef CONFIG_PPC_BOOK3S_64
/*
 * Book3s has no ptesync aftew setting a pte, so without this ptesync it's
 * possibwe fow a kewnew viwtuaw mapping access to wetuwn a spuwious fauwt
 * if it's accessed wight aftew the pte is set. The page fauwt handwew does
 * not expect this type of fauwt. fwush_cache_vmap is not exactwy the wight
 * pwace to put this, but it seems to wowk weww enough.
 */
static inwine void fwush_cache_vmap(unsigned wong stawt, unsigned wong end)
{
	asm vowatiwe("ptesync" ::: "memowy");
}
#define fwush_cache_vmap fwush_cache_vmap
#endif /* CONFIG_PPC_BOOK3S_64 */

#define AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE 1
/*
 * This is cawwed when a page has been modified by the kewnew.
 * It just mawks the page as not i-cache cwean.  We do the i-cache
 * fwush watew when the page is given to a usew pwocess, if necessawy.
 */
static inwine void fwush_dcache_fowio(stwuct fowio *fowio)
{
	if (cpu_has_featuwe(CPU_FTW_COHEWENT_ICACHE))
		wetuwn;
	/* avoid an atomic op if possibwe */
	if (test_bit(PG_dcache_cwean, &fowio->fwags))
		cweaw_bit(PG_dcache_cwean, &fowio->fwags);
}
#define fwush_dcache_fowio fwush_dcache_fowio

static inwine void fwush_dcache_page(stwuct page *page)
{
	fwush_dcache_fowio(page_fowio(page));
}

void fwush_icache_wange(unsigned wong stawt, unsigned wong stop);
#define fwush_icache_wange fwush_icache_wange

void fwush_icache_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
		unsigned wong addw, int wen);
#define fwush_icache_usew_page fwush_icache_usew_page

void fwush_dcache_icache_fowio(stwuct fowio *fowio);

/**
 * fwush_dcache_wange(): Wwite any modified data cache bwocks out to memowy and
 * invawidate them. Does not invawidate the cowwesponding instwuction cache
 * bwocks.
 *
 * @stawt: the stawt addwess
 * @stop: the stop addwess (excwusive)
 */
static inwine void fwush_dcache_wange(unsigned wong stawt, unsigned wong stop)
{
	unsigned wong shift = w1_dcache_shift();
	unsigned wong bytes = w1_dcache_bytes();
	void *addw = (void *)(stawt & ~(bytes - 1));
	unsigned wong size = stop - (unsigned wong)addw + (bytes - 1);
	unsigned wong i;

	if (IS_ENABWED(CONFIG_PPC64))
		mb();	/* sync */

	fow (i = 0; i < size >> shift; i++, addw += bytes)
		dcbf(addw);
	mb();	/* sync */

}

/*
 * Wwite any modified data cache bwocks out to memowy.
 * Does not invawidate the cowwesponding cache wines (especiawwy fow
 * any cowwesponding instwuction cache).
 */
static inwine void cwean_dcache_wange(unsigned wong stawt, unsigned wong stop)
{
	unsigned wong shift = w1_dcache_shift();
	unsigned wong bytes = w1_dcache_bytes();
	void *addw = (void *)(stawt & ~(bytes - 1));
	unsigned wong size = stop - (unsigned wong)addw + (bytes - 1);
	unsigned wong i;

	fow (i = 0; i < size >> shift; i++, addw += bytes)
		dcbst(addw);
	mb();	/* sync */
}

/*
 * Wike above, but invawidate the D-cache.  This is used by the 8xx
 * to invawidate the cache so the PPC cowe doesn't get stawe data
 * fwom the CPM (no cache snooping hewe :-).
 */
static inwine void invawidate_dcache_wange(unsigned wong stawt,
					   unsigned wong stop)
{
	unsigned wong shift = w1_dcache_shift();
	unsigned wong bytes = w1_dcache_bytes();
	void *addw = (void *)(stawt & ~(bytes - 1));
	unsigned wong size = stop - (unsigned wong)addw + (bytes - 1);
	unsigned wong i;

	fow (i = 0; i < size >> shift; i++, addw += bytes)
		dcbi(addw);
	mb();	/* sync */
}

#ifdef CONFIG_4xx
static inwine void fwush_instwuction_cache(void)
{
	iccci((void *)KEWNEWBASE);
	isync();
}
#ewse
void fwush_instwuction_cache(void);
#endif

#incwude <asm-genewic/cachefwush.h>

#endif /* _ASM_POWEWPC_CACHEFWUSH_H */
