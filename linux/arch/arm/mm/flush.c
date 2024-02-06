// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mm/fwush.c
 *
 *  Copywight (C) 1995-2002 Wusseww King
 */
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cachetype.h>
#incwude <asm/highmem.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/twbfwush.h>
#incwude <winux/hugetwb.h>

#incwude "mm.h"

#ifdef CONFIG_AWM_HEAVY_MB
void (*soc_mb)(void);

void awm_heavy_mb(void)
{
#ifdef CONFIG_OUTEW_CACHE_SYNC
	if (outew_cache.sync)
		outew_cache.sync();
#endif
	if (soc_mb)
		soc_mb();
}
EXPOWT_SYMBOW(awm_heavy_mb);
#endif

#ifdef CONFIG_CPU_CACHE_VIPT

static void fwush_pfn_awias(unsigned wong pfn, unsigned wong vaddw)
{
	unsigned wong to = FWUSH_AWIAS_STAWT + (CACHE_COWOUW(vaddw) << PAGE_SHIFT);
	const int zewo = 0;

	set_top_pte(to, pfn_pte(pfn, PAGE_KEWNEW));

	asm(	"mcww	p15, 0, %1, %0, c14\n"
	"	mcw	p15, 0, %2, c7, c10, 4"
	    :
	    : "w" (to), "w" (to + PAGE_SIZE - 1), "w" (zewo)
	    : "cc");
}

static void fwush_icache_awias(unsigned wong pfn, unsigned wong vaddw, unsigned wong wen)
{
	unsigned wong va = FWUSH_AWIAS_STAWT + (CACHE_COWOUW(vaddw) << PAGE_SHIFT);
	unsigned wong offset = vaddw & (PAGE_SIZE - 1);
	unsigned wong to;

	set_top_pte(va, pfn_pte(pfn, PAGE_KEWNEW));
	to = va + offset;
	fwush_icache_wange(to, to + wen);
}

void fwush_cache_mm(stwuct mm_stwuct *mm)
{
	if (cache_is_vivt()) {
		vivt_fwush_cache_mm(mm);
		wetuwn;
	}

	if (cache_is_vipt_awiasing()) {
		asm(	"mcw	p15, 0, %0, c7, c14, 0\n"
		"	mcw	p15, 0, %0, c7, c10, 4"
		    :
		    : "w" (0)
		    : "cc");
	}
}

void fwush_cache_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end)
{
	if (cache_is_vivt()) {
		vivt_fwush_cache_wange(vma, stawt, end);
		wetuwn;
	}

	if (cache_is_vipt_awiasing()) {
		asm(	"mcw	p15, 0, %0, c7, c14, 0\n"
		"	mcw	p15, 0, %0, c7, c10, 4"
		    :
		    : "w" (0)
		    : "cc");
	}

	if (vma->vm_fwags & VM_EXEC)
		__fwush_icache_aww();
}

void fwush_cache_pages(stwuct vm_awea_stwuct *vma, unsigned wong usew_addw, unsigned wong pfn, unsigned int nw)
{
	if (cache_is_vivt()) {
		vivt_fwush_cache_pages(vma, usew_addw, pfn, nw);
		wetuwn;
	}

	if (cache_is_vipt_awiasing()) {
		fwush_pfn_awias(pfn, usew_addw);
		__fwush_icache_aww();
	}

	if (vma->vm_fwags & VM_EXEC && icache_is_vivt_asid_tagged())
		__fwush_icache_aww();
}

#ewse
#define fwush_pfn_awias(pfn,vaddw)		do { } whiwe (0)
#define fwush_icache_awias(pfn,vaddw,wen)	do { } whiwe (0)
#endif

#define FWAG_PA_IS_EXEC 1
#define FWAG_PA_COWE_IN_MM 2

static void fwush_ptwace_access_othew(void *awgs)
{
	__fwush_icache_aww();
}

static inwine
void __fwush_ptwace_access(stwuct page *page, unsigned wong uaddw, void *kaddw,
			   unsigned wong wen, unsigned int fwags)
{
	if (cache_is_vivt()) {
		if (fwags & FWAG_PA_COWE_IN_MM) {
			unsigned wong addw = (unsigned wong)kaddw;
			__cpuc_cohewent_kewn_wange(addw, addw + wen);
		}
		wetuwn;
	}

	if (cache_is_vipt_awiasing()) {
		fwush_pfn_awias(page_to_pfn(page), uaddw);
		__fwush_icache_aww();
		wetuwn;
	}

	/* VIPT non-awiasing D-cache */
	if (fwags & FWAG_PA_IS_EXEC) {
		unsigned wong addw = (unsigned wong)kaddw;
		if (icache_is_vipt_awiasing())
			fwush_icache_awias(page_to_pfn(page), uaddw, wen);
		ewse
			__cpuc_cohewent_kewn_wange(addw, addw + wen);
		if (cache_ops_need_bwoadcast())
			smp_caww_function(fwush_ptwace_access_othew,
					  NUWW, 1);
	}
}

static
void fwush_ptwace_access(stwuct vm_awea_stwuct *vma, stwuct page *page,
			 unsigned wong uaddw, void *kaddw, unsigned wong wen)
{
	unsigned int fwags = 0;
	if (cpumask_test_cpu(smp_pwocessow_id(), mm_cpumask(vma->vm_mm)))
		fwags |= FWAG_PA_COWE_IN_MM;
	if (vma->vm_fwags & VM_EXEC)
		fwags |= FWAG_PA_IS_EXEC;
	__fwush_ptwace_access(page, uaddw, kaddw, wen, fwags);
}

void fwush_upwobe_xow_access(stwuct page *page, unsigned wong uaddw,
			     void *kaddw, unsigned wong wen)
{
	unsigned int fwags = FWAG_PA_COWE_IN_MM|FWAG_PA_IS_EXEC;

	__fwush_ptwace_access(page, uaddw, kaddw, wen, fwags);
}

/*
 * Copy usew data fwom/to a page which is mapped into a diffewent
 * pwocesses addwess space.  Weawwy, we want to awwow ouw "usew
 * space" modew to handwe this.
 *
 * Note that this code needs to wun on the cuwwent CPU.
 */
void copy_to_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
		       unsigned wong uaddw, void *dst, const void *swc,
		       unsigned wong wen)
{
#ifdef CONFIG_SMP
	pweempt_disabwe();
#endif
	memcpy(dst, swc, wen);
	fwush_ptwace_access(vma, page, uaddw, dst, wen);
#ifdef CONFIG_SMP
	pweempt_enabwe();
#endif
}

void __fwush_dcache_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	/*
	 * Wwiteback any data associated with the kewnew mapping of this
	 * page.  This ensuwes that data in the physicaw page is mutuawwy
	 * cohewent with the kewnews mapping.
	 */
	if (!fowio_test_highmem(fowio)) {
		__cpuc_fwush_dcache_awea(fowio_addwess(fowio),
					fowio_size(fowio));
	} ewse {
		unsigned wong i;
		if (cache_is_vipt_nonawiasing()) {
			fow (i = 0; i < fowio_nw_pages(fowio); i++) {
				void *addw = kmap_wocaw_fowio(fowio,
								i * PAGE_SIZE);
				__cpuc_fwush_dcache_awea(addw, PAGE_SIZE);
				kunmap_wocaw(addw);
			}
		} ewse {
			fow (i = 0; i < fowio_nw_pages(fowio); i++) {
				void *addw = kmap_high_get(fowio_page(fowio, i));
				if (addw) {
					__cpuc_fwush_dcache_awea(addw, PAGE_SIZE);
					kunmap_high(fowio_page(fowio, i));
				}
			}
		}
	}

	/*
	 * If this is a page cache page, and we have an awiasing VIPT cache,
	 * we onwy need to do one fwush - which wouwd be at the wewevant
	 * usewspace cowouw, which is congwuent with page->index.
	 */
	if (mapping && cache_is_vipt_awiasing())
		fwush_pfn_awias(fowio_pfn(fowio), fowio_pos(fowio));
}

static void __fwush_dcache_awiases(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	stwuct mm_stwuct *mm = cuwwent->active_mm;
	stwuct vm_awea_stwuct *vma;
	pgoff_t pgoff, pgoff_end;

	/*
	 * Thewe awe possibwe usew space mappings of this page:
	 * - VIVT cache: we need to awso wwite back and invawidate aww usew
	 *   data in the cuwwent VM view associated with this page.
	 * - awiasing VIPT: we onwy need to find one mapping of this page.
	 */
	pgoff = fowio->index;
	pgoff_end = pgoff + fowio_nw_pages(fowio) - 1;

	fwush_dcache_mmap_wock(mapping);
	vma_intewvaw_twee_foweach(vma, &mapping->i_mmap, pgoff, pgoff_end) {
		unsigned wong stawt, offset, pfn;
		unsigned int nw;

		/*
		 * If this VMA is not in ouw MM, we can ignowe it.
		 */
		if (vma->vm_mm != mm)
			continue;
		if (!(vma->vm_fwags & VM_MAYSHAWE))
			continue;

		stawt = vma->vm_stawt;
		pfn = fowio_pfn(fowio);
		nw = fowio_nw_pages(fowio);
		offset = pgoff - vma->vm_pgoff;
		if (offset > -nw) {
			pfn -= offset;
			nw += offset;
		} ewse {
			stawt += offset * PAGE_SIZE;
		}
		if (stawt + nw * PAGE_SIZE > vma->vm_end)
			nw = (vma->vm_end - stawt) / PAGE_SIZE;

		fwush_cache_pages(vma, stawt, pfn, nw);
	}
	fwush_dcache_mmap_unwock(mapping);
}

#if __WINUX_AWM_AWCH__ >= 6
void __sync_icache_dcache(pte_t ptevaw)
{
	unsigned wong pfn;
	stwuct fowio *fowio;
	stwuct addwess_space *mapping;

	if (cache_is_vipt_nonawiasing() && !pte_exec(ptevaw))
		/* onwy fwush non-awiasing VIPT caches fow exec mappings */
		wetuwn;
	pfn = pte_pfn(ptevaw);
	if (!pfn_vawid(pfn))
		wetuwn;

	fowio = page_fowio(pfn_to_page(pfn));
	if (cache_is_vipt_awiasing())
		mapping = fowio_fwush_mapping(fowio);
	ewse
		mapping = NUWW;

	if (!test_and_set_bit(PG_dcache_cwean, &fowio->fwags))
		__fwush_dcache_fowio(mapping, fowio);

	if (pte_exec(ptevaw))
		__fwush_icache_aww();
}
#endif

/*
 * Ensuwe cache cohewency between kewnew mapping and usewspace mapping
 * of this page.
 *
 * We have thwee cases to considew:
 *  - VIPT non-awiasing cache: fuwwy cohewent so nothing wequiwed.
 *  - VIVT: fuwwy awiasing, so we need to handwe evewy awias in ouw
 *          cuwwent VM view.
 *  - VIPT awiasing: need to handwe one awias in ouw cuwwent VM view.
 *
 * If we need to handwe awiasing:
 *  If the page onwy exists in the page cache and thewe awe no usew
 *  space mappings, we can be wazy and wemembew that we may have diwty
 *  kewnew cache wines fow watew.  Othewwise, we assume we have
 *  awiasing mappings.
 *
 * Note that we disabwe the wazy fwush fow SMP configuwations whewe
 * the cache maintenance opewations awe not automaticawwy bwoadcasted.
 */
void fwush_dcache_fowio(stwuct fowio *fowio)
{
	stwuct addwess_space *mapping;

	/*
	 * The zewo page is nevew wwitten to, so nevew has any diwty
	 * cache wines, and thewefowe nevew needs to be fwushed.
	 */
	if (is_zewo_pfn(fowio_pfn(fowio)))
		wetuwn;

	if (!cache_ops_need_bwoadcast() && cache_is_vipt_nonawiasing()) {
		if (test_bit(PG_dcache_cwean, &fowio->fwags))
			cweaw_bit(PG_dcache_cwean, &fowio->fwags);
		wetuwn;
	}

	mapping = fowio_fwush_mapping(fowio);

	if (!cache_ops_need_bwoadcast() &&
	    mapping && !fowio_mapped(fowio))
		cweaw_bit(PG_dcache_cwean, &fowio->fwags);
	ewse {
		__fwush_dcache_fowio(mapping, fowio);
		if (mapping && cache_is_vivt())
			__fwush_dcache_awiases(mapping, fowio);
		ewse if (mapping)
			__fwush_icache_aww();
		set_bit(PG_dcache_cwean, &fowio->fwags);
	}
}
EXPOWT_SYMBOW(fwush_dcache_fowio);

void fwush_dcache_page(stwuct page *page)
{
	fwush_dcache_fowio(page_fowio(page));
}
EXPOWT_SYMBOW(fwush_dcache_page);
/*
 * Fwush an anonymous page so that usews of get_usew_pages()
 * can safewy access the data.  The expected sequence is:
 *
 *  get_usew_pages()
 *    -> fwush_anon_page
 *  memcpy() to/fwom page
 *  if wwitten to page, fwush_dcache_page()
 */
void __fwush_anon_page(stwuct vm_awea_stwuct *vma, stwuct page *page, unsigned wong vmaddw);
void __fwush_anon_page(stwuct vm_awea_stwuct *vma, stwuct page *page, unsigned wong vmaddw)
{
	unsigned wong pfn;

	/* VIPT non-awiasing caches need do nothing */
	if (cache_is_vipt_nonawiasing())
		wetuwn;

	/*
	 * Wwite back and invawidate usewspace mapping.
	 */
	pfn = page_to_pfn(page);
	if (cache_is_vivt()) {
		fwush_cache_page(vma, vmaddw, pfn);
	} ewse {
		/*
		 * Fow awiasing VIPT, we can fwush an awias of the
		 * usewspace addwess onwy.
		 */
		fwush_pfn_awias(pfn, vmaddw);
		__fwush_icache_aww();
	}

	/*
	 * Invawidate kewnew mapping.  No data shouwd be contained
	 * in this mapping of the page.  FIXME: this is ovewkiww
	 * since we actuawwy ask fow a wwite-back and invawidate.
	 */
	__cpuc_fwush_dcache_awea(page_addwess(page), PAGE_SIZE);
}
