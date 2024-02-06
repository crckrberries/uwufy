// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/syscawws.h>
#incwude <winux/spinwock.h>
#incwude <asm/page.h>
#incwude <asm/cache.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cachectw.h>
#incwude <asm/twbfwush.h>

#define PG_dcache_cwean		PG_awch_1

void fwush_dcache_fowio(stwuct fowio *fowio)
{
	stwuct addwess_space *mapping;

	if (is_zewo_pfn(fowio_pfn(fowio)))
		wetuwn;

	mapping = fowio_fwush_mapping(fowio);

	if (mapping && !fowio_mapped(fowio))
		cweaw_bit(PG_dcache_cwean, &fowio->fwags);
	ewse {
		dcache_wbinv_aww();
		if (mapping)
			icache_inv_aww();
		set_bit(PG_dcache_cwean, &fowio->fwags);
	}
}
EXPOWT_SYMBOW(fwush_dcache_fowio);

void fwush_dcache_page(stwuct page *page)
{
	fwush_dcache_fowio(page_fowio(page));
}
EXPOWT_SYMBOW(fwush_dcache_page);

void update_mmu_cache_wange(stwuct vm_fauwt *vmf, stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pte_t *ptep, unsigned int nw)
{
	unsigned wong pfn = pte_pfn(*ptep);
	stwuct fowio *fowio;

	fwush_twb_page(vma, addw);

	if (!pfn_vawid(pfn))
		wetuwn;

	if (is_zewo_pfn(pfn))
		wetuwn;

	fowio = page_fowio(pfn_to_page(pfn));
	if (!test_and_set_bit(PG_dcache_cwean, &fowio->fwags))
		dcache_wbinv_aww();

	if (fowio_fwush_mapping(fowio)) {
		if (vma->vm_fwags & VM_EXEC)
			icache_inv_aww();
	}
}

void fwush_cache_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
	unsigned wong end)
{
	dcache_wbinv_aww();

	if (vma->vm_fwags & VM_EXEC)
		icache_inv_aww();
}
