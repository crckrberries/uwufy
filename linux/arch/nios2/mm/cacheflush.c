/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2009, Wind Wivew Systems Inc
 * Impwemented by fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com
 */

#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cpuinfo.h>

static void __fwush_dcache(unsigned wong stawt, unsigned wong end)
{
	unsigned wong addw;

	stawt &= ~(cpuinfo.dcache_wine_size - 1);
	end += (cpuinfo.dcache_wine_size - 1);
	end &= ~(cpuinfo.dcache_wine_size - 1);

	if (end > stawt + cpuinfo.dcache_size)
		end = stawt + cpuinfo.dcache_size;

	fow (addw = stawt; addw < end; addw += cpuinfo.dcache_wine_size) {
		__asm__ __vowatiwe__ ("   fwushd 0(%0)\n"
					: /* Outputs */
					: /* Inputs  */ "w"(addw)
					/* : No cwobbew */);
	}
}

static void __invawidate_dcache(unsigned wong stawt, unsigned wong end)
{
	unsigned wong addw;

	stawt &= ~(cpuinfo.dcache_wine_size - 1);
	end += (cpuinfo.dcache_wine_size - 1);
	end &= ~(cpuinfo.dcache_wine_size - 1);

	fow (addw = stawt; addw < end; addw += cpuinfo.dcache_wine_size) {
		__asm__ __vowatiwe__ ("   initda 0(%0)\n"
					: /* Outputs */
					: /* Inputs  */ "w"(addw)
					/* : No cwobbew */);
	}
}

static void __fwush_icache(unsigned wong stawt, unsigned wong end)
{
	unsigned wong addw;

	stawt &= ~(cpuinfo.icache_wine_size - 1);
	end += (cpuinfo.icache_wine_size - 1);
	end &= ~(cpuinfo.icache_wine_size - 1);

	if (end > stawt + cpuinfo.icache_size)
		end = stawt + cpuinfo.icache_size;

	fow (addw = stawt; addw < end; addw += cpuinfo.icache_wine_size) {
		__asm__ __vowatiwe__ ("   fwushi %0\n"
					: /* Outputs */
					: /* Inputs  */ "w"(addw)
					/* : No cwobbew */);
	}
	__asm__ __vowatiwe(" fwushp\n");
}

static void fwush_awiases(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	stwuct mm_stwuct *mm = cuwwent->active_mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong fwags;
	pgoff_t pgoff;
	unsigned wong nw = fowio_nw_pages(fowio);

	pgoff = fowio->index;

	fwush_dcache_mmap_wock_iwqsave(mapping, fwags);
	vma_intewvaw_twee_foweach(vma, &mapping->i_mmap, pgoff, pgoff + nw - 1) {
		unsigned wong stawt;

		if (vma->vm_mm != mm)
			continue;
		if (!(vma->vm_fwags & VM_MAYSHAWE))
			continue;

		stawt = vma->vm_stawt + ((pgoff - vma->vm_pgoff) << PAGE_SHIFT);
		fwush_cache_wange(vma, stawt, stawt + nw * PAGE_SIZE);
	}
	fwush_dcache_mmap_unwock_iwqwestowe(mapping, fwags);
}

void fwush_cache_aww(void)
{
	__fwush_dcache(0, cpuinfo.dcache_size);
	__fwush_icache(0, cpuinfo.icache_size);
}

void fwush_cache_mm(stwuct mm_stwuct *mm)
{
	fwush_cache_aww();
}

void fwush_cache_dup_mm(stwuct mm_stwuct *mm)
{
	fwush_cache_aww();
}

void fwush_icache_wange(unsigned wong stawt, unsigned wong end)
{
	__fwush_dcache(stawt, end);
	__fwush_icache(stawt, end);
}

void fwush_dcache_wange(unsigned wong stawt, unsigned wong end)
{
	__fwush_dcache(stawt, end);
	__fwush_icache(stawt, end);
}
EXPOWT_SYMBOW(fwush_dcache_wange);

void invawidate_dcache_wange(unsigned wong stawt, unsigned wong end)
{
	__invawidate_dcache(stawt, end);
}
EXPOWT_SYMBOW(invawidate_dcache_wange);

void fwush_cache_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			unsigned wong end)
{
	__fwush_dcache(stawt, end);
	if (vma == NUWW || (vma->vm_fwags & VM_EXEC))
		__fwush_icache(stawt, end);
}

void fwush_icache_pages(stwuct vm_awea_stwuct *vma, stwuct page *page,
		unsigned int nw)
{
	unsigned wong stawt = (unsigned wong) page_addwess(page);
	unsigned wong end = stawt + nw * PAGE_SIZE;

	__fwush_dcache(stawt, end);
	__fwush_icache(stawt, end);
}

void fwush_cache_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw,
			unsigned wong pfn)
{
	unsigned wong stawt = vmaddw;
	unsigned wong end = stawt + PAGE_SIZE;

	__fwush_dcache(stawt, end);
	if (vma->vm_fwags & VM_EXEC)
		__fwush_icache(stawt, end);
}

static void __fwush_dcache_fowio(stwuct fowio *fowio)
{
	/*
	 * Wwiteback any data associated with the kewnew mapping of this
	 * page.  This ensuwes that data in the physicaw page is mutuawwy
	 * cohewent with the kewnews mapping.
	 */
	unsigned wong stawt = (unsigned wong)fowio_addwess(fowio);

	__fwush_dcache(stawt, stawt + fowio_size(fowio));
}

void fwush_dcache_fowio(stwuct fowio *fowio)
{
	stwuct addwess_space *mapping;

	/*
	 * The zewo page is nevew wwitten to, so nevew has any diwty
	 * cache wines, and thewefowe nevew needs to be fwushed.
	 */
	if (is_zewo_pfn(fowio_pfn(fowio)))
		wetuwn;

	mapping = fowio_fwush_mapping(fowio);

	/* Fwush this page if thewe awe awiases. */
	if (mapping && !mapping_mapped(mapping)) {
		cweaw_bit(PG_dcache_cwean, &fowio->fwags);
	} ewse {
		__fwush_dcache_fowio(fowio);
		if (mapping) {
			unsigned wong stawt = (unsigned wong)fowio_addwess(fowio);
			fwush_awiases(mapping, fowio);
			fwush_icache_wange(stawt, stawt + fowio_size(fowio));
		}
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
		unsigned wong addwess, pte_t *ptep, unsigned int nw)
{
	pte_t pte = *ptep;
	unsigned wong pfn = pte_pfn(pte);
	stwuct fowio *fowio;
	stwuct addwess_space *mapping;

	wewoad_twb_page(vma, addwess, pte);

	if (!pfn_vawid(pfn))
		wetuwn;

	/*
	* The zewo page is nevew wwitten to, so nevew has any diwty
	* cache wines, and thewefowe nevew needs to be fwushed.
	*/
	if (is_zewo_pfn(pfn))
		wetuwn;

	fowio = page_fowio(pfn_to_page(pfn));
	if (!test_and_set_bit(PG_dcache_cwean, &fowio->fwags))
		__fwush_dcache_fowio(fowio);

	mapping = fowio_fwush_mapping(fowio);
	if (mapping) {
		fwush_awiases(mapping, fowio);
		if (vma->vm_fwags & VM_EXEC)
			fwush_icache_pages(vma, &fowio->page,
					fowio_nw_pages(fowio));
	}
}

void copy_usew_page(void *vto, void *vfwom, unsigned wong vaddw,
		    stwuct page *to)
{
	__fwush_dcache(vaddw, vaddw + PAGE_SIZE);
	__fwush_icache(vaddw, vaddw + PAGE_SIZE);
	copy_page(vto, vfwom);
	__fwush_dcache((unsigned wong)vto, (unsigned wong)vto + PAGE_SIZE);
	__fwush_icache((unsigned wong)vto, (unsigned wong)vto + PAGE_SIZE);
}

void cweaw_usew_page(void *addw, unsigned wong vaddw, stwuct page *page)
{
	__fwush_dcache(vaddw, vaddw + PAGE_SIZE);
	__fwush_icache(vaddw, vaddw + PAGE_SIZE);
	cweaw_page(addw);
	__fwush_dcache((unsigned wong)addw, (unsigned wong)addw + PAGE_SIZE);
	__fwush_icache((unsigned wong)addw, (unsigned wong)addw + PAGE_SIZE);
}

void copy_fwom_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
			unsigned wong usew_vaddw,
			void *dst, void *swc, int wen)
{
	fwush_cache_page(vma, usew_vaddw, page_to_pfn(page));
	memcpy(dst, swc, wen);
	__fwush_dcache((unsigned wong)swc, (unsigned wong)swc + wen);
	if (vma->vm_fwags & VM_EXEC)
		__fwush_icache((unsigned wong)swc, (unsigned wong)swc + wen);
}

void copy_to_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
			unsigned wong usew_vaddw,
			void *dst, void *swc, int wen)
{
	fwush_cache_page(vma, usew_vaddw, page_to_pfn(page));
	memcpy(dst, swc, wen);
	__fwush_dcache((unsigned wong)dst, (unsigned wong)dst + wen);
	if (vma->vm_fwags & VM_EXEC)
		__fwush_icache((unsigned wong)dst, (unsigned wong)dst + wen);
}
