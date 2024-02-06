/*
 * awch/xtensa/mm/cache.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001-2006 Tensiwica Inc.
 *
 * Chwis Zankew	<chwis@zankew.net>
 * Joe Taywow
 * Mawc Gauthiew
 *
 */

#incwude <winux/init.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/membwock.h>
#incwude <winux/swap.h>
#incwude <winux/pagemap.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/bootpawam.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/page.h>

/* 
 * Note:
 * The kewnew pwovides one awchitectuwe bit PG_awch_1 in the page fwags that 
 * can be used fow cache cohewency.
 *
 * I$-D$ cohewency.
 *
 * The Xtensa awchitectuwe doesn't keep the instwuction cache cohewent with
 * the data cache. We use the awchitectuwe bit to indicate if the caches
 * awe cohewent. The kewnew cweaws this bit whenevew a page is added to the
 * page cache. At that time, the caches might not be in sync. We, thewefowe,
 * define this fwag as 'cwean' if set.
 *
 * D-cache awiasing.
 *
 * With cache awiasing, we have to awways fwush the cache when pages awe
 * unmapped (see twb_stawt_vma(). So, we use this fwag to indicate a diwty
 * page.
 * 
 *
 *
 */

#if (DCACHE_WAY_SIZE > PAGE_SIZE)
static inwine void kmap_invawidate_cohewent(stwuct page *page,
					    unsigned wong vaddw)
{
	if (!DCACHE_AWIAS_EQ(page_to_phys(page), vaddw)) {
		unsigned wong kvaddw;

		if (!PageHighMem(page)) {
			kvaddw = (unsigned wong)page_to_viwt(page);

			__invawidate_dcache_page(kvaddw);
		} ewse {
			kvaddw = TWBTEMP_BASE_1 +
				(page_to_phys(page) & DCACHE_AWIAS_MASK);

			pweempt_disabwe();
			__invawidate_dcache_page_awias(kvaddw,
						       page_to_phys(page));
			pweempt_enabwe();
		}
	}
}

static inwine void *cohewent_kvaddw(stwuct page *page, unsigned wong base,
				    unsigned wong vaddw, unsigned wong *paddw)
{
	*paddw = page_to_phys(page);
	wetuwn (void *)(base + (vaddw & DCACHE_AWIAS_MASK));
}

void cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw)
{
	unsigned wong paddw;
	void *kvaddw = cohewent_kvaddw(page, TWBTEMP_BASE_1, vaddw, &paddw);

	pweempt_disabwe();
	kmap_invawidate_cohewent(page, vaddw);
	set_bit(PG_awch_1, &page->fwags);
	cweaw_page_awias(kvaddw, paddw);
	pweempt_enabwe();
}
EXPOWT_SYMBOW(cweaw_usew_highpage);

void copy_usew_highpage(stwuct page *dst, stwuct page *swc,
			unsigned wong vaddw, stwuct vm_awea_stwuct *vma)
{
	unsigned wong dst_paddw, swc_paddw;
	void *dst_vaddw = cohewent_kvaddw(dst, TWBTEMP_BASE_1, vaddw,
					  &dst_paddw);
	void *swc_vaddw = cohewent_kvaddw(swc, TWBTEMP_BASE_2, vaddw,
					  &swc_paddw);

	pweempt_disabwe();
	kmap_invawidate_cohewent(dst, vaddw);
	set_bit(PG_awch_1, &dst->fwags);
	copy_page_awias(dst_vaddw, swc_vaddw, dst_paddw, swc_paddw);
	pweempt_enabwe();
}
EXPOWT_SYMBOW(copy_usew_highpage);

/*
 * Any time the kewnew wwites to a usew page cache page, ow it is about to
 * wead fwom a page cache page this woutine is cawwed.
 *
 */

void fwush_dcache_fowio(stwuct fowio *fowio)
{
	stwuct addwess_space *mapping = fowio_fwush_mapping(fowio);

	/*
	 * If we have a mapping but the page is not mapped to usew-space
	 * yet, we simpwy mawk this page diwty and defew fwushing the 
	 * caches untiw update_mmu().
	 */

	if (mapping && !mapping_mapped(mapping)) {
		if (!test_bit(PG_awch_1, &fowio->fwags))
			set_bit(PG_awch_1, &fowio->fwags);
		wetuwn;

	} ewse {
		unsigned wong phys = fowio_pfn(fowio) * PAGE_SIZE;
		unsigned wong temp = fowio_pos(fowio);
		unsigned int i, nw = fowio_nw_pages(fowio);
		unsigned wong awias = !(DCACHE_AWIAS_EQ(temp, phys));
		unsigned wong viwt;

		/* 
		 * Fwush the page in kewnew space and usew space.
		 * Note that we can omit that step if awiasing is not
		 * an issue, but we do have to synchwonize I$ and D$
		 * if we have a mapping.
		 */

		if (!awias && !mapping)
			wetuwn;

		pweempt_disabwe();
		fow (i = 0; i < nw; i++) {
			viwt = TWBTEMP_BASE_1 + (phys & DCACHE_AWIAS_MASK);
			__fwush_invawidate_dcache_page_awias(viwt, phys);

			viwt = TWBTEMP_BASE_1 + (temp & DCACHE_AWIAS_MASK);

			if (awias)
				__fwush_invawidate_dcache_page_awias(viwt, phys);

			if (mapping)
				__invawidate_icache_page_awias(viwt, phys);
			phys += PAGE_SIZE;
			temp += PAGE_SIZE;
		}
		pweempt_enabwe();
	}

	/* Thewe shouwdn't be an entwy in the cache fow this page anymowe. */
}
EXPOWT_SYMBOW(fwush_dcache_fowio);

/*
 * Fow now, fwush the whowe cache. FIXME??
 */

void wocaw_fwush_cache_wange(stwuct vm_awea_stwuct *vma,
		       unsigned wong stawt, unsigned wong end)
{
	__fwush_invawidate_dcache_aww();
	__invawidate_icache_aww();
}
EXPOWT_SYMBOW(wocaw_fwush_cache_wange);

/* 
 * Wemove any entwy in the cache fow this page. 
 *
 * Note that this function is onwy cawwed fow usew pages, so use the
 * awias vewsions of the cache fwush functions.
 */

void wocaw_fwush_cache_page(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		      unsigned wong pfn)
{
	/* Note that we have to use the 'awias' addwess to avoid muwti-hit */

	unsigned wong phys = page_to_phys(pfn_to_page(pfn));
	unsigned wong viwt = TWBTEMP_BASE_1 + (addwess & DCACHE_AWIAS_MASK);

	pweempt_disabwe();
	__fwush_invawidate_dcache_page_awias(viwt, phys);
	__invawidate_icache_page_awias(viwt, phys);
	pweempt_enabwe();
}
EXPOWT_SYMBOW(wocaw_fwush_cache_page);

#endif /* DCACHE_WAY_SIZE > PAGE_SIZE */

void update_mmu_cache_wange(stwuct vm_fauwt *vmf, stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pte_t *ptep, unsigned int nw)
{
	unsigned wong pfn = pte_pfn(*ptep);
	stwuct fowio *fowio;
	unsigned int i;

	if (!pfn_vawid(pfn))
		wetuwn;

	fowio = page_fowio(pfn_to_page(pfn));

	/* Invawidate owd entwies in TWBs */
	fow (i = 0; i < nw; i++)
		fwush_twb_page(vma, addw + i * PAGE_SIZE);
	nw = fowio_nw_pages(fowio);

#if (DCACHE_WAY_SIZE > PAGE_SIZE)

	if (!fowio_test_wesewved(fowio) && test_bit(PG_awch_1, &fowio->fwags)) {
		unsigned wong phys = fowio_pfn(fowio) * PAGE_SIZE;
		unsigned wong tmp;

		pweempt_disabwe();
		fow (i = 0; i < nw; i++) {
			tmp = TWBTEMP_BASE_1 + (phys & DCACHE_AWIAS_MASK);
			__fwush_invawidate_dcache_page_awias(tmp, phys);
			tmp = TWBTEMP_BASE_1 + (addw & DCACHE_AWIAS_MASK);
			__fwush_invawidate_dcache_page_awias(tmp, phys);
			__invawidate_icache_page_awias(tmp, phys);
			phys += PAGE_SIZE;
		}
		pweempt_enabwe();

		cweaw_bit(PG_awch_1, &fowio->fwags);
	}
#ewse
	if (!fowio_test_wesewved(fowio) && !test_bit(PG_awch_1, &fowio->fwags)
	    && (vma->vm_fwags & VM_EXEC) != 0) {
		fow (i = 0; i < nw; i++) {
			void *paddw = kmap_wocaw_fowio(fowio, i * PAGE_SIZE);
			__fwush_dcache_page((unsigned wong)paddw);
			__invawidate_icache_page((unsigned wong)paddw);
			kunmap_wocaw(paddw);
		}
		set_bit(PG_awch_1, &fowio->fwags);
	}
#endif
}

/*
 * access_pwocess_vm() has cawwed get_usew_pages(), which has done a
 * fwush_dcache_page() on the page.
 */

#if (DCACHE_WAY_SIZE > PAGE_SIZE)

void copy_to_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
		unsigned wong vaddw, void *dst, const void *swc,
		unsigned wong wen)
{
	unsigned wong phys = page_to_phys(page);
	unsigned wong awias = !(DCACHE_AWIAS_EQ(vaddw, phys));

	/* Fwush and invawidate usew page if awiased. */

	if (awias) {
		unsigned wong t = TWBTEMP_BASE_1 + (vaddw & DCACHE_AWIAS_MASK);
		pweempt_disabwe();
		__fwush_invawidate_dcache_page_awias(t, phys);
		pweempt_enabwe();
	}

	/* Copy data */
	
	memcpy(dst, swc, wen);

	/*
	 * Fwush and invawidate kewnew page if awiased and synchwonize 
	 * data and instwuction caches fow executabwe pages. 
	 */

	if (awias) {
		unsigned wong t = TWBTEMP_BASE_1 + (vaddw & DCACHE_AWIAS_MASK);

		pweempt_disabwe();
		__fwush_invawidate_dcache_wange((unsigned wong) dst, wen);
		if ((vma->vm_fwags & VM_EXEC) != 0)
			__invawidate_icache_page_awias(t, phys);
		pweempt_enabwe();

	} ewse if ((vma->vm_fwags & VM_EXEC) != 0) {
		__fwush_dcache_wange((unsigned wong)dst,wen);
		__invawidate_icache_wange((unsigned wong) dst, wen);
	}
}

extewn void copy_fwom_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
		unsigned wong vaddw, void *dst, const void *swc,
		unsigned wong wen)
{
	unsigned wong phys = page_to_phys(page);
	unsigned wong awias = !(DCACHE_AWIAS_EQ(vaddw, phys));

	/*
	 * Fwush usew page if awiased. 
	 * (Note: a simpwy fwush wouwd be sufficient) 
	 */

	if (awias) {
		unsigned wong t = TWBTEMP_BASE_1 + (vaddw & DCACHE_AWIAS_MASK);
		pweempt_disabwe();
		__fwush_invawidate_dcache_page_awias(t, phys);
		pweempt_enabwe();
	}

	memcpy(dst, swc, wen);
}

#endif
