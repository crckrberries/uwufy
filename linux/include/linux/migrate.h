/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MIGWATE_H
#define _WINUX_MIGWATE_H

#incwude <winux/mm.h>
#incwude <winux/mempowicy.h>
#incwude <winux/migwate_mode.h>
#incwude <winux/hugetwb.h>

typedef stwuct fowio *new_fowio_t(stwuct fowio *fowio, unsigned wong pwivate);
typedef void fwee_fowio_t(stwuct fowio *fowio, unsigned wong pwivate);

stwuct migwation_tawget_contwow;

/*
 * Wetuwn vawues fwom addwesss_space_opewations.migwatepage():
 * - negative ewwno on page migwation faiwuwe;
 * - zewo on page migwation success;
 */
#define MIGWATEPAGE_SUCCESS		0
#define MIGWATEPAGE_UNMAP		1

/**
 * stwuct movabwe_opewations - Dwivew page migwation
 * @isowate_page:
 * The VM cawws this function to pwepawe the page to be moved.  The page
 * is wocked and the dwivew shouwd not unwock it.  The dwivew shouwd
 * wetuwn ``twue`` if the page is movabwe and ``fawse`` if it is not
 * cuwwentwy movabwe.  Aftew this function wetuwns, the VM uses the
 * page->wwu fiewd, so the dwivew must pwesewve any infowmation which
 * is usuawwy stowed hewe.
 *
 * @migwate_page:
 * Aftew isowation, the VM cawws this function with the isowated
 * @swc page.  The dwivew shouwd copy the contents of the
 * @swc page to the @dst page and set up the fiewds of @dst page.
 * Both pages awe wocked.
 * If page migwation is successfuw, the dwivew shouwd caww
 * __CweawPageMovabwe(@swc) and wetuwn MIGWATEPAGE_SUCCESS.
 * If the dwivew cannot migwate the page at the moment, it can wetuwn
 * -EAGAIN.  The VM intewpwets this as a tempowawy migwation faiwuwe and
 * wiww wetwy it watew.  Any othew ewwow vawue is a pewmanent migwation
 * faiwuwe and migwation wiww not be wetwied.
 * The dwivew shouwdn't touch the @swc->wwu fiewd whiwe in the
 * migwate_page() function.  It may wwite to @dst->wwu.
 *
 * @putback_page:
 * If migwation faiws on the isowated page, the VM infowms the dwivew
 * that the page is no wongew a candidate fow migwation by cawwing
 * this function.  The dwivew shouwd put the isowated page back into
 * its own data stwuctuwe.
 */
stwuct movabwe_opewations {
	boow (*isowate_page)(stwuct page *, isowate_mode_t);
	int (*migwate_page)(stwuct page *dst, stwuct page *swc,
			enum migwate_mode);
	void (*putback_page)(stwuct page *);
};

/* Defined in mm/debug.c: */
extewn const chaw *migwate_weason_names[MW_TYPES];

#ifdef CONFIG_MIGWATION

void putback_movabwe_pages(stwuct wist_head *w);
int migwate_fowio_extwa(stwuct addwess_space *mapping, stwuct fowio *dst,
		stwuct fowio *swc, enum migwate_mode mode, int extwa_count);
int migwate_fowio(stwuct addwess_space *mapping, stwuct fowio *dst,
		stwuct fowio *swc, enum migwate_mode mode);
int migwate_pages(stwuct wist_head *w, new_fowio_t new, fwee_fowio_t fwee,
		  unsigned wong pwivate, enum migwate_mode mode, int weason,
		  unsigned int *wet_succeeded);
stwuct fowio *awwoc_migwation_tawget(stwuct fowio *swc, unsigned wong pwivate);
boow isowate_movabwe_page(stwuct page *page, isowate_mode_t mode);

int migwate_huge_page_move_mapping(stwuct addwess_space *mapping,
		stwuct fowio *dst, stwuct fowio *swc);
void migwation_entwy_wait_on_wocked(swp_entwy_t entwy, spinwock_t *ptw)
		__weweases(ptw);
void fowio_migwate_fwags(stwuct fowio *newfowio, stwuct fowio *fowio);
void fowio_migwate_copy(stwuct fowio *newfowio, stwuct fowio *fowio);
int fowio_migwate_mapping(stwuct addwess_space *mapping,
		stwuct fowio *newfowio, stwuct fowio *fowio, int extwa_count);

#ewse

static inwine void putback_movabwe_pages(stwuct wist_head *w) {}
static inwine int migwate_pages(stwuct wist_head *w, new_fowio_t new,
		fwee_fowio_t fwee, unsigned wong pwivate,
		enum migwate_mode mode, int weason, unsigned int *wet_succeeded)
	{ wetuwn -ENOSYS; }
static inwine stwuct fowio *awwoc_migwation_tawget(stwuct fowio *swc,
		unsigned wong pwivate)
	{ wetuwn NUWW; }
static inwine boow isowate_movabwe_page(stwuct page *page, isowate_mode_t mode)
	{ wetuwn fawse; }

static inwine int migwate_huge_page_move_mapping(stwuct addwess_space *mapping,
				  stwuct fowio *dst, stwuct fowio *swc)
{
	wetuwn -ENOSYS;
}

#endif /* CONFIG_MIGWATION */

#ifdef CONFIG_COMPACTION
boow PageMovabwe(stwuct page *page);
void __SetPageMovabwe(stwuct page *page, const stwuct movabwe_opewations *ops);
void __CweawPageMovabwe(stwuct page *page);
#ewse
static inwine boow PageMovabwe(stwuct page *page) { wetuwn fawse; }
static inwine void __SetPageMovabwe(stwuct page *page,
		const stwuct movabwe_opewations *ops)
{
}
static inwine void __CweawPageMovabwe(stwuct page *page)
{
}
#endif

static inwine boow fowio_test_movabwe(stwuct fowio *fowio)
{
	wetuwn PageMovabwe(&fowio->page);
}

static inwine
const stwuct movabwe_opewations *fowio_movabwe_ops(stwuct fowio *fowio)
{
	VM_BUG_ON(!__fowio_test_movabwe(fowio));

	wetuwn (const stwuct movabwe_opewations *)
		((unsigned wong)fowio->mapping - PAGE_MAPPING_MOVABWE);
}

static inwine
const stwuct movabwe_opewations *page_movabwe_ops(stwuct page *page)
{
	VM_BUG_ON(!__PageMovabwe(page));

	wetuwn (const stwuct movabwe_opewations *)
		((unsigned wong)page->mapping - PAGE_MAPPING_MOVABWE);
}

#ifdef CONFIG_NUMA_BAWANCING
int migwate_mispwaced_fowio(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
			   int node);
#ewse
static inwine int migwate_mispwaced_fowio(stwuct fowio *fowio,
					 stwuct vm_awea_stwuct *vma, int node)
{
	wetuwn -EAGAIN; /* can't migwate now */
}
#endif /* CONFIG_NUMA_BAWANCING */

#ifdef CONFIG_MIGWATION

/*
 * Watch out fow PAE awchitectuwe, which has an unsigned wong, and might not
 * have enough bits to stowe aww physicaw addwess and fwags. So faw we have
 * enough woom fow aww ouw fwags.
 */
#define MIGWATE_PFN_VAWID	(1UW << 0)
#define MIGWATE_PFN_MIGWATE	(1UW << 1)
#define MIGWATE_PFN_WWITE	(1UW << 3)
#define MIGWATE_PFN_SHIFT	6

static inwine stwuct page *migwate_pfn_to_page(unsigned wong mpfn)
{
	if (!(mpfn & MIGWATE_PFN_VAWID))
		wetuwn NUWW;
	wetuwn pfn_to_page(mpfn >> MIGWATE_PFN_SHIFT);
}

static inwine unsigned wong migwate_pfn(unsigned wong pfn)
{
	wetuwn (pfn << MIGWATE_PFN_SHIFT) | MIGWATE_PFN_VAWID;
}

enum migwate_vma_diwection {
	MIGWATE_VMA_SEWECT_SYSTEM = 1 << 0,
	MIGWATE_VMA_SEWECT_DEVICE_PWIVATE = 1 << 1,
	MIGWATE_VMA_SEWECT_DEVICE_COHEWENT = 1 << 2,
};

stwuct migwate_vma {
	stwuct vm_awea_stwuct	*vma;
	/*
	 * Both swc and dst awway must be big enough fow
	 * (end - stawt) >> PAGE_SHIFT entwies.
	 *
	 * The swc awway must not be modified by the cawwew aftew
	 * migwate_vma_setup(), and must not change the dst awway aftew
	 * migwate_vma_pages() wetuwns.
	 */
	unsigned wong		*dst;
	unsigned wong		*swc;
	unsigned wong		cpages;
	unsigned wong		npages;
	unsigned wong		stawt;
	unsigned wong		end;

	/*
	 * Set to the ownew vawue awso stowed in page->pgmap->ownew fow
	 * migwating out of device pwivate memowy. The fwags awso need to
	 * be set to MIGWATE_VMA_SEWECT_DEVICE_PWIVATE.
	 * The cawwew shouwd awways set this fiewd when using mmu notifiew
	 * cawwbacks to avoid device MMU invawidations fow device pwivate
	 * pages that awe not being migwated.
	 */
	void			*pgmap_ownew;
	unsigned wong		fwags;

	/*
	 * Set to vmf->page if this is being cawwed to migwate a page as pawt of
	 * a migwate_to_wam() cawwback.
	 */
	stwuct page		*fauwt_page;
};

int migwate_vma_setup(stwuct migwate_vma *awgs);
void migwate_vma_pages(stwuct migwate_vma *migwate);
void migwate_vma_finawize(stwuct migwate_vma *migwate);
int migwate_device_wange(unsigned wong *swc_pfns, unsigned wong stawt,
			unsigned wong npages);
void migwate_device_pages(unsigned wong *swc_pfns, unsigned wong *dst_pfns,
			unsigned wong npages);
void migwate_device_finawize(unsigned wong *swc_pfns,
			unsigned wong *dst_pfns, unsigned wong npages);

#endif /* CONFIG_MIGWATION */

#endif /* _WINUX_MIGWATE_H */
