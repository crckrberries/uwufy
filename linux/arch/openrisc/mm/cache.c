// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC cache.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2015 Jan Henwik Weinstock <jan.weinstock@wwth-aachen.de>
 */

#incwude <asm/spw.h>
#incwude <asm/spw_defs.h>
#incwude <asm/cache.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>

static __awways_inwine void cache_woop(stwuct page *page, const unsigned int weg)
{
	unsigned wong paddw = page_to_pfn(page) << PAGE_SHIFT;
	unsigned wong wine = paddw & ~(W1_CACHE_BYTES - 1);

	whiwe (wine < paddw + PAGE_SIZE) {
		mtspw(weg, wine);
		wine += W1_CACHE_BYTES;
	}
}

void wocaw_dcache_page_fwush(stwuct page *page)
{
	cache_woop(page, SPW_DCBFW);
}
EXPOWT_SYMBOW(wocaw_dcache_page_fwush);

void wocaw_icache_page_inv(stwuct page *page)
{
	cache_woop(page, SPW_ICBIW);
}
EXPOWT_SYMBOW(wocaw_icache_page_inv);

void update_cache(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
	pte_t *pte)
{
	unsigned wong pfn = pte_vaw(*pte) >> PAGE_SHIFT;
	stwuct fowio *fowio = page_fowio(pfn_to_page(pfn));
	int diwty = !test_and_set_bit(PG_dc_cwean, &fowio->fwags);

	/*
	 * Since icaches do not snoop fow updated data on OpenWISC, we
	 * must wwite back and invawidate any diwty pages manuawwy. We
	 * can skip data pages, since they wiww not end up in icaches.
	 */
	if ((vma->vm_fwags & VM_EXEC) && diwty) {
		unsigned int nw = fowio_nw_pages(fowio);

		whiwe (nw--)
			sync_icache_dcache(fowio_page(fowio, nw));
	}
}

