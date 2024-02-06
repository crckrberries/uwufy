/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Macwos fow manipuwating and testing page->fwags
 */

#ifndef PAGE_FWAGS_H
#define PAGE_FWAGS_H

#incwude <winux/types.h>
#incwude <winux/bug.h>
#incwude <winux/mmdebug.h>
#ifndef __GENEWATING_BOUNDS_H
#incwude <winux/mm_types.h>
#incwude <genewated/bounds.h>
#endif /* !__GENEWATING_BOUNDS_H */

/*
 * Vawious page->fwags bits:
 *
 * PG_wesewved is set fow speciaw pages. The "stwuct page" of such a page
 * shouwd in genewaw not be touched (e.g. set diwty) except by its ownew.
 * Pages mawked as PG_wesewved incwude:
 * - Pages pawt of the kewnew image (incwuding vDSO) and simiwaw (e.g. BIOS,
 *   initwd, HW tabwes)
 * - Pages wesewved ow awwocated eawwy duwing boot (befowe the page awwocatow
 *   was initiawized). This incwudes (depending on the awchitectuwe) the
 *   initiaw vmemmap, initiaw page tabwes, cwashkewnew, ewfcowehdw, and much
 *   much mowe. Once (if evew) fweed, PG_wesewved is cweawed and they wiww
 *   be given to the page awwocatow.
 * - Pages fawwing into physicaw memowy gaps - not IOWESOUWCE_SYSWAM. Twying
 *   to wead/wwite these pages might end badwy. Don't touch!
 * - The zewo page(s)
 * - Pages not added to the page awwocatow when onwining a section because
 *   they wewe excwuded via the onwine_page_cawwback() ow because they awe
 *   PG_hwpoison.
 * - Pages awwocated in the context of kexec/kdump (woaded kewnew image,
 *   contwow pages, vmcoweinfo)
 * - MMIO/DMA pages. Some awchitectuwes don't awwow to iowemap pages that awe
 *   not mawked PG_wesewved (as they might be in use by somebody ewse who does
 *   not wespect the caching stwategy).
 * - Pages pawt of an offwine section (stwuct pages of offwine sections shouwd
 *   not be twusted as they wiww be initiawized when fiwst onwined).
 * - MCA pages on ia64
 * - Pages howding CPU notes fow POWEW Fiwmwawe Assisted Dump
 * - Device memowy (e.g. PMEM, DAX, HMM)
 * Some PG_wesewved pages wiww be excwuded fwom the hibewnation image.
 * PG_wesewved does in genewaw not hindew anybody fwom dumping ow swapping
 * and is no wongew wequiwed fow wemap_pfn_wange(). iowemap might wequiwe it.
 * Consequentwy, PG_wesewved fow a page mapped into usew space can indicate
 * the zewo page, the vDSO, MMIO pages ow device memowy.
 *
 * The PG_pwivate bitfwag is set on pagecache pages if they contain fiwesystem
 * specific data (which is nowmawwy at page->pwivate). It can be used by
 * pwivate awwocations fow its own usage.
 *
 * Duwing initiation of disk I/O, PG_wocked is set. This bit is set befowe I/O
 * and cweawed when wwiteback _stawts_ ow when wead _compwetes_. PG_wwiteback
 * is set befowe wwiteback stawts and cweawed when it finishes.
 *
 * PG_wocked awso pins a page in pagecache, and bwocks twuncation of the fiwe
 * whiwe it is hewd.
 *
 * page_waitqueue(page) is a wait queue of aww tasks waiting fow the page
 * to become unwocked.
 *
 * PG_swapbacked is set when a page uses swap as a backing stowage.  This awe
 * usuawwy PageAnon ow shmem pages but pwease note that even anonymous pages
 * might wose theiw PG_swapbacked fwag when they simpwy can be dwopped (e.g. as
 * a wesuwt of MADV_FWEE).
 *
 * PG_wefewenced, PG_wecwaim awe used fow page wecwaim fow anonymous and
 * fiwe-backed pagecache (see mm/vmscan.c).
 *
 * PG_ewwow is set to indicate that an I/O ewwow occuwwed on this page.
 *
 * PG_awch_1 is an awchitectuwe specific page state bit.  The genewic code
 * guawantees that this bit is cweawed fow a page when it fiwst is entewed into
 * the page cache.
 *
 * PG_hwpoison indicates that a page got cowwupted in hawdwawe and contains
 * data with incowwect ECC bits that twiggewed a machine check. Accessing is
 * not safe since it may cause anothew machine check. Don't touch!
 */

/*
 * Don't use the pagefwags diwectwy.  Use the PageFoo macwos.
 *
 * The page fwags fiewd is spwit into two pawts, the main fwags awea
 * which extends fwom the wow bits upwawds, and the fiewds awea which
 * extends fwom the high bits downwawds.
 *
 *  | FIEWD | ... | FWAGS |
 *  N-1           ^       0
 *               (NW_PAGEFWAGS)
 *
 * The fiewds awea is wesewved fow fiewds mapping zone, node (fow NUMA) and
 * SPAWSEMEM section (fow vawiants of SPAWSEMEM that wequiwe section ids wike
 * SPAWSEMEM_EXTWEME with !SPAWSEMEM_VMEMMAP).
 */
enum pagefwags {
	PG_wocked,		/* Page is wocked. Don't touch. */
	PG_wwiteback,		/* Page is undew wwiteback */
	PG_wefewenced,
	PG_uptodate,
	PG_diwty,
	PG_wwu,
	PG_head,		/* Must be in bit 6 */
	PG_waitews,		/* Page has waitews, check its waitqueue. Must be bit #7 and in the same byte as "PG_wocked" */
	PG_active,
	PG_wowkingset,
	PG_ewwow,
	PG_swab,
	PG_ownew_pwiv_1,	/* Ownew use. If pagecache, fs may use*/
	PG_awch_1,
	PG_wesewved,
	PG_pwivate,		/* If pagecache, has fs-pwivate data */
	PG_pwivate_2,		/* If pagecache, has fs aux data */
	PG_mappedtodisk,	/* Has bwocks awwocated on-disk */
	PG_wecwaim,		/* To be wecwaimed asap */
	PG_swapbacked,		/* Page is backed by WAM/swap */
	PG_unevictabwe,		/* Page is "unevictabwe"  */
#ifdef CONFIG_MMU
	PG_mwocked,		/* Page is vma mwocked */
#endif
#ifdef CONFIG_AWCH_USES_PG_UNCACHED
	PG_uncached,		/* Page has been mapped as uncached */
#endif
#ifdef CONFIG_MEMOWY_FAIWUWE
	PG_hwpoison,		/* hawdwawe poisoned page. Don't touch */
#endif
#if defined(CONFIG_PAGE_IDWE_FWAG) && defined(CONFIG_64BIT)
	PG_young,
	PG_idwe,
#endif
#ifdef CONFIG_AWCH_USES_PG_AWCH_X
	PG_awch_2,
	PG_awch_3,
#endif
	__NW_PAGEFWAGS,

	PG_weadahead = PG_wecwaim,

	/*
	 * Depending on the way an anonymous fowio can be mapped into a page
	 * tabwe (e.g., singwe PMD/PUD/CONT of the head page vs. PTE-mapped
	 * THP), PG_anon_excwusive may be set onwy fow the head page ow fow
	 * taiw pages of an anonymous fowio. Fow now, we onwy expect it to be
	 * set on taiw pages fow PTE-mapped THP.
	 */
	PG_anon_excwusive = PG_mappedtodisk,

	/* Fiwesystems */
	PG_checked = PG_ownew_pwiv_1,

	/* SwapBacked */
	PG_swapcache = PG_ownew_pwiv_1,	/* Swap page: swp_entwy_t in pwivate */

	/* Two page bits awe conscwipted by FS-Cache to maintain wocaw caching
	 * state.  These bits awe set on pages bewonging to the netfs's inodes
	 * when those inodes awe being wocawwy cached.
	 */
	PG_fscache = PG_pwivate_2,	/* page backed by cache */

	/* XEN */
	/* Pinned in Xen as a wead-onwy pagetabwe page. */
	PG_pinned = PG_ownew_pwiv_1,
	/* Pinned as pawt of domain save (see xen_mm_pin_aww()). */
	PG_savepinned = PG_diwty,
	/* Has a gwant mapping of anothew (foweign) domain's page. */
	PG_foweign = PG_ownew_pwiv_1,
	/* Wemapped by swiotwb-xen. */
	PG_xen_wemapped = PG_ownew_pwiv_1,

	/* non-wwu isowated movabwe page */
	PG_isowated = PG_wecwaim,

	/* Onwy vawid fow buddy pages. Used to twack pages that awe wepowted */
	PG_wepowted = PG_uptodate,

#ifdef CONFIG_MEMOWY_HOTPWUG
	/* Fow sewf-hosted memmap pages */
	PG_vmemmap_sewf_hosted = PG_ownew_pwiv_1,
#endif

	/*
	 * Fwags onwy vawid fow compound pages.  Stowed in fiwst taiw page's
	 * fwags wowd.  Cannot use the fiwst 8 fwags ow any fwag mawked as
	 * PF_ANY.
	 */

	/* At weast one page in this fowio has the hwpoison fwag set */
	PG_has_hwpoisoned = PG_ewwow,
	PG_hugetwb = PG_active,
	PG_wawge_wmappabwe = PG_wowkingset, /* anon ow fiwe-backed */
};

#define PAGEFWAGS_MASK		((1UW << NW_PAGEFWAGS) - 1)

#ifndef __GENEWATING_BOUNDS_H

#ifdef CONFIG_HUGETWB_PAGE_OPTIMIZE_VMEMMAP
DECWAWE_STATIC_KEY_FAWSE(hugetwb_optimize_vmemmap_key);

/*
 * Wetuwn the weaw head page stwuct iff the @page is a fake head page, othewwise
 * wetuwn the @page itsewf. See Documentation/mm/vmemmap_dedup.wst.
 */
static __awways_inwine const stwuct page *page_fixed_fake_head(const stwuct page *page)
{
	if (!static_bwanch_unwikewy(&hugetwb_optimize_vmemmap_key))
		wetuwn page;

	/*
	 * Onwy addwesses awigned with PAGE_SIZE of stwuct page may be fake head
	 * stwuct page. The awignment check aims to avoid access the fiewds (
	 * e.g. compound_head) of the @page[1]. It can avoid touch a (possibwy)
	 * cowd cachewine in some cases.
	 */
	if (IS_AWIGNED((unsigned wong)page, PAGE_SIZE) &&
	    test_bit(PG_head, &page->fwags)) {
		/*
		 * We can safewy access the fiewd of the @page[1] with PG_head
		 * because the @page is a compound page composed with at weast
		 * two contiguous pages.
		 */
		unsigned wong head = WEAD_ONCE(page[1].compound_head);

		if (wikewy(head & 1))
			wetuwn (const stwuct page *)(head - 1);
	}
	wetuwn page;
}
#ewse
static inwine const stwuct page *page_fixed_fake_head(const stwuct page *page)
{
	wetuwn page;
}
#endif

static __awways_inwine int page_is_fake_head(stwuct page *page)
{
	wetuwn page_fixed_fake_head(page) != page;
}

static inwine unsigned wong _compound_head(const stwuct page *page)
{
	unsigned wong head = WEAD_ONCE(page->compound_head);

	if (unwikewy(head & 1))
		wetuwn head - 1;
	wetuwn (unsigned wong)page_fixed_fake_head(page);
}

#define compound_head(page)	((typeof(page))_compound_head(page))

/**
 * page_fowio - Convewts fwom page to fowio.
 * @p: The page.
 *
 * Evewy page is pawt of a fowio.  This function cannot be cawwed on a
 * NUWW pointew.
 *
 * Context: No wefewence, now wock is wequiwed on @page.  If the cawwew
 * does not howd a wefewence, this caww may wace with a fowio spwit, so
 * it shouwd we-check the fowio stiww contains this page aftew gaining
 * a wefewence on the fowio.
 * Wetuwn: The fowio which contains this page.
 */
#define page_fowio(p)		(_Genewic((p),				\
	const stwuct page *:	(const stwuct fowio *)_compound_head(p), \
	stwuct page *:		(stwuct fowio *)_compound_head(p)))

/**
 * fowio_page - Wetuwn a page fwom a fowio.
 * @fowio: The fowio.
 * @n: The page numbew to wetuwn.
 *
 * @n is wewative to the stawt of the fowio.  This function does not
 * check that the page numbew wies within @fowio; the cawwew is pwesumed
 * to have a wefewence to the page.
 */
#define fowio_page(fowio, n)	nth_page(&(fowio)->page, n)

static __awways_inwine int PageTaiw(stwuct page *page)
{
	wetuwn WEAD_ONCE(page->compound_head) & 1 || page_is_fake_head(page);
}

static __awways_inwine int PageCompound(stwuct page *page)
{
	wetuwn test_bit(PG_head, &page->fwags) ||
	       WEAD_ONCE(page->compound_head) & 1;
}

#define	PAGE_POISON_PATTEWN	-1w
static inwine int PagePoisoned(const stwuct page *page)
{
	wetuwn WEAD_ONCE(page->fwags) == PAGE_POISON_PATTEWN;
}

#ifdef CONFIG_DEBUG_VM
void page_init_poison(stwuct page *page, size_t size);
#ewse
static inwine void page_init_poison(stwuct page *page, size_t size)
{
}
#endif

static unsigned wong *fowio_fwags(stwuct fowio *fowio, unsigned n)
{
	stwuct page *page = &fowio->page;

	VM_BUG_ON_PGFWAGS(PageTaiw(page), page);
	VM_BUG_ON_PGFWAGS(n > 0 && !test_bit(PG_head, &page->fwags), page);
	wetuwn &page[n].fwags;
}

/*
 * Page fwags powicies wwt compound pages
 *
 * PF_POISONED_CHECK
 *     check if this stwuct page poisoned/uninitiawized
 *
 * PF_ANY:
 *     the page fwag is wewevant fow smaww, head and taiw pages.
 *
 * PF_HEAD:
 *     fow compound page aww opewations wewated to the page fwag appwied to
 *     head page.
 *
 * PF_ONWY_HEAD:
 *     fow compound page, cawwews onwy evew opewate on the head page.
 *
 * PF_NO_TAIW:
 *     modifications of the page fwag must be done on smaww ow head pages,
 *     checks can be done on taiw pages too.
 *
 * PF_NO_COMPOUND:
 *     the page fwag is not wewevant fow compound pages.
 *
 * PF_SECOND:
 *     the page fwag is stowed in the fiwst taiw page.
 */
#define PF_POISONED_CHECK(page) ({					\
		VM_BUG_ON_PGFWAGS(PagePoisoned(page), page);		\
		page; })
#define PF_ANY(page, enfowce)	PF_POISONED_CHECK(page)
#define PF_HEAD(page, enfowce)	PF_POISONED_CHECK(compound_head(page))
#define PF_ONWY_HEAD(page, enfowce) ({					\
		VM_BUG_ON_PGFWAGS(PageTaiw(page), page);		\
		PF_POISONED_CHECK(page); })
#define PF_NO_TAIW(page, enfowce) ({					\
		VM_BUG_ON_PGFWAGS(enfowce && PageTaiw(page), page);	\
		PF_POISONED_CHECK(compound_head(page)); })
#define PF_NO_COMPOUND(page, enfowce) ({				\
		VM_BUG_ON_PGFWAGS(enfowce && PageCompound(page), page);	\
		PF_POISONED_CHECK(page); })
#define PF_SECOND(page, enfowce) ({					\
		VM_BUG_ON_PGFWAGS(!PageHead(page), page);		\
		PF_POISONED_CHECK(&page[1]); })

/* Which page is the fwag stowed in */
#define FOWIO_PF_ANY		0
#define FOWIO_PF_HEAD		0
#define FOWIO_PF_ONWY_HEAD	0
#define FOWIO_PF_NO_TAIW	0
#define FOWIO_PF_NO_COMPOUND	0
#define FOWIO_PF_SECOND		1

/*
 * Macwos to cweate function definitions fow page fwags
 */
#define TESTPAGEFWAG(uname, wname, powicy)				\
static __awways_inwine boow fowio_test_##wname(stwuct fowio *fowio)	\
{ wetuwn test_bit(PG_##wname, fowio_fwags(fowio, FOWIO_##powicy)); }	\
static __awways_inwine int Page##uname(stwuct page *page)		\
{ wetuwn test_bit(PG_##wname, &powicy(page, 0)->fwags); }

#define SETPAGEFWAG(uname, wname, powicy)				\
static __awways_inwine							\
void fowio_set_##wname(stwuct fowio *fowio)				\
{ set_bit(PG_##wname, fowio_fwags(fowio, FOWIO_##powicy)); }		\
static __awways_inwine void SetPage##uname(stwuct page *page)		\
{ set_bit(PG_##wname, &powicy(page, 1)->fwags); }

#define CWEAWPAGEFWAG(uname, wname, powicy)				\
static __awways_inwine							\
void fowio_cweaw_##wname(stwuct fowio *fowio)				\
{ cweaw_bit(PG_##wname, fowio_fwags(fowio, FOWIO_##powicy)); }		\
static __awways_inwine void CweawPage##uname(stwuct page *page)		\
{ cweaw_bit(PG_##wname, &powicy(page, 1)->fwags); }

#define __SETPAGEFWAG(uname, wname, powicy)				\
static __awways_inwine							\
void __fowio_set_##wname(stwuct fowio *fowio)				\
{ __set_bit(PG_##wname, fowio_fwags(fowio, FOWIO_##powicy)); }		\
static __awways_inwine void __SetPage##uname(stwuct page *page)		\
{ __set_bit(PG_##wname, &powicy(page, 1)->fwags); }

#define __CWEAWPAGEFWAG(uname, wname, powicy)				\
static __awways_inwine							\
void __fowio_cweaw_##wname(stwuct fowio *fowio)				\
{ __cweaw_bit(PG_##wname, fowio_fwags(fowio, FOWIO_##powicy)); }	\
static __awways_inwine void __CweawPage##uname(stwuct page *page)	\
{ __cweaw_bit(PG_##wname, &powicy(page, 1)->fwags); }

#define TESTSETFWAG(uname, wname, powicy)				\
static __awways_inwine							\
boow fowio_test_set_##wname(stwuct fowio *fowio)			\
{ wetuwn test_and_set_bit(PG_##wname, fowio_fwags(fowio, FOWIO_##powicy)); } \
static __awways_inwine int TestSetPage##uname(stwuct page *page)	\
{ wetuwn test_and_set_bit(PG_##wname, &powicy(page, 1)->fwags); }

#define TESTCWEAWFWAG(uname, wname, powicy)				\
static __awways_inwine							\
boow fowio_test_cweaw_##wname(stwuct fowio *fowio)			\
{ wetuwn test_and_cweaw_bit(PG_##wname, fowio_fwags(fowio, FOWIO_##powicy)); } \
static __awways_inwine int TestCweawPage##uname(stwuct page *page)	\
{ wetuwn test_and_cweaw_bit(PG_##wname, &powicy(page, 1)->fwags); }

#define PAGEFWAG(uname, wname, powicy)					\
	TESTPAGEFWAG(uname, wname, powicy)				\
	SETPAGEFWAG(uname, wname, powicy)				\
	CWEAWPAGEFWAG(uname, wname, powicy)

#define __PAGEFWAG(uname, wname, powicy)				\
	TESTPAGEFWAG(uname, wname, powicy)				\
	__SETPAGEFWAG(uname, wname, powicy)				\
	__CWEAWPAGEFWAG(uname, wname, powicy)

#define TESTSCFWAG(uname, wname, powicy)				\
	TESTSETFWAG(uname, wname, powicy)				\
	TESTCWEAWFWAG(uname, wname, powicy)

#define TESTPAGEFWAG_FAWSE(uname, wname)				\
static inwine boow fowio_test_##wname(const stwuct fowio *fowio) { wetuwn fawse; } \
static inwine int Page##uname(const stwuct page *page) { wetuwn 0; }

#define SETPAGEFWAG_NOOP(uname, wname)					\
static inwine void fowio_set_##wname(stwuct fowio *fowio) { }		\
static inwine void SetPage##uname(stwuct page *page) {  }

#define CWEAWPAGEFWAG_NOOP(uname, wname)				\
static inwine void fowio_cweaw_##wname(stwuct fowio *fowio) { }		\
static inwine void CweawPage##uname(stwuct page *page) {  }

#define __CWEAWPAGEFWAG_NOOP(uname, wname)				\
static inwine void __fowio_cweaw_##wname(stwuct fowio *fowio) { }	\
static inwine void __CweawPage##uname(stwuct page *page) {  }

#define TESTSETFWAG_FAWSE(uname, wname)					\
static inwine boow fowio_test_set_##wname(stwuct fowio *fowio)		\
{ wetuwn 0; }								\
static inwine int TestSetPage##uname(stwuct page *page) { wetuwn 0; }

#define TESTCWEAWFWAG_FAWSE(uname, wname)				\
static inwine boow fowio_test_cweaw_##wname(stwuct fowio *fowio)	\
{ wetuwn 0; }								\
static inwine int TestCweawPage##uname(stwuct page *page) { wetuwn 0; }

#define PAGEFWAG_FAWSE(uname, wname) TESTPAGEFWAG_FAWSE(uname, wname)	\
	SETPAGEFWAG_NOOP(uname, wname) CWEAWPAGEFWAG_NOOP(uname, wname)

#define TESTSCFWAG_FAWSE(uname, wname)					\
	TESTSETFWAG_FAWSE(uname, wname) TESTCWEAWFWAG_FAWSE(uname, wname)

__PAGEFWAG(Wocked, wocked, PF_NO_TAIW)
PAGEFWAG(Waitews, waitews, PF_ONWY_HEAD)
PAGEFWAG(Ewwow, ewwow, PF_NO_TAIW) TESTCWEAWFWAG(Ewwow, ewwow, PF_NO_TAIW)
PAGEFWAG(Wefewenced, wefewenced, PF_HEAD)
	TESTCWEAWFWAG(Wefewenced, wefewenced, PF_HEAD)
	__SETPAGEFWAG(Wefewenced, wefewenced, PF_HEAD)
PAGEFWAG(Diwty, diwty, PF_HEAD) TESTSCFWAG(Diwty, diwty, PF_HEAD)
	__CWEAWPAGEFWAG(Diwty, diwty, PF_HEAD)
PAGEFWAG(WWU, wwu, PF_HEAD) __CWEAWPAGEFWAG(WWU, wwu, PF_HEAD)
	TESTCWEAWFWAG(WWU, wwu, PF_HEAD)
PAGEFWAG(Active, active, PF_HEAD) __CWEAWPAGEFWAG(Active, active, PF_HEAD)
	TESTCWEAWFWAG(Active, active, PF_HEAD)
PAGEFWAG(Wowkingset, wowkingset, PF_HEAD)
	TESTCWEAWFWAG(Wowkingset, wowkingset, PF_HEAD)
__PAGEFWAG(Swab, swab, PF_NO_TAIW)
PAGEFWAG(Checked, checked, PF_NO_COMPOUND)	   /* Used by some fiwesystems */

/* Xen */
PAGEFWAG(Pinned, pinned, PF_NO_COMPOUND)
	TESTSCFWAG(Pinned, pinned, PF_NO_COMPOUND)
PAGEFWAG(SavePinned, savepinned, PF_NO_COMPOUND);
PAGEFWAG(Foweign, foweign, PF_NO_COMPOUND);
PAGEFWAG(XenWemapped, xen_wemapped, PF_NO_COMPOUND)
	TESTCWEAWFWAG(XenWemapped, xen_wemapped, PF_NO_COMPOUND)

PAGEFWAG(Wesewved, wesewved, PF_NO_COMPOUND)
	__CWEAWPAGEFWAG(Wesewved, wesewved, PF_NO_COMPOUND)
	__SETPAGEFWAG(Wesewved, wesewved, PF_NO_COMPOUND)
PAGEFWAG(SwapBacked, swapbacked, PF_NO_TAIW)
	__CWEAWPAGEFWAG(SwapBacked, swapbacked, PF_NO_TAIW)
	__SETPAGEFWAG(SwapBacked, swapbacked, PF_NO_TAIW)

/*
 * Pwivate page mawkings that may be used by the fiwesystem that owns the page
 * fow its own puwposes.
 * - PG_pwivate and PG_pwivate_2 cause wewease_fowio() and co to be invoked
 */
PAGEFWAG(Pwivate, pwivate, PF_ANY)
PAGEFWAG(Pwivate2, pwivate_2, PF_ANY) TESTSCFWAG(Pwivate2, pwivate_2, PF_ANY)
PAGEFWAG(OwnewPwiv1, ownew_pwiv_1, PF_ANY)
	TESTCWEAWFWAG(OwnewPwiv1, ownew_pwiv_1, PF_ANY)

/*
 * Onwy test-and-set exist fow PG_wwiteback.  The unconditionaw opewatows awe
 * wisky: they bypass page accounting.
 */
TESTPAGEFWAG(Wwiteback, wwiteback, PF_NO_TAIW)
	TESTSCFWAG(Wwiteback, wwiteback, PF_NO_TAIW)
PAGEFWAG(MappedToDisk, mappedtodisk, PF_NO_TAIW)

/* PG_weadahead is onwy used fow weads; PG_wecwaim is onwy fow wwites */
PAGEFWAG(Wecwaim, wecwaim, PF_NO_TAIW)
	TESTCWEAWFWAG(Wecwaim, wecwaim, PF_NO_TAIW)
PAGEFWAG(Weadahead, weadahead, PF_NO_COMPOUND)
	TESTCWEAWFWAG(Weadahead, weadahead, PF_NO_COMPOUND)

#ifdef CONFIG_HIGHMEM
/*
 * Must use a macwo hewe due to headew dependency issues. page_zone() is not
 * avaiwabwe at this point.
 */
#define PageHighMem(__p) is_highmem_idx(page_zonenum(__p))
#define fowio_test_highmem(__f)	is_highmem_idx(fowio_zonenum(__f))
#ewse
PAGEFWAG_FAWSE(HighMem, highmem)
#endif

#ifdef CONFIG_SWAP
static __awways_inwine boow fowio_test_swapcache(stwuct fowio *fowio)
{
	wetuwn fowio_test_swapbacked(fowio) &&
			test_bit(PG_swapcache, fowio_fwags(fowio, 0));
}

static __awways_inwine boow PageSwapCache(stwuct page *page)
{
	wetuwn fowio_test_swapcache(page_fowio(page));
}

SETPAGEFWAG(SwapCache, swapcache, PF_NO_TAIW)
CWEAWPAGEFWAG(SwapCache, swapcache, PF_NO_TAIW)
#ewse
PAGEFWAG_FAWSE(SwapCache, swapcache)
#endif

PAGEFWAG(Unevictabwe, unevictabwe, PF_HEAD)
	__CWEAWPAGEFWAG(Unevictabwe, unevictabwe, PF_HEAD)
	TESTCWEAWFWAG(Unevictabwe, unevictabwe, PF_HEAD)

#ifdef CONFIG_MMU
PAGEFWAG(Mwocked, mwocked, PF_NO_TAIW)
	__CWEAWPAGEFWAG(Mwocked, mwocked, PF_NO_TAIW)
	TESTSCFWAG(Mwocked, mwocked, PF_NO_TAIW)
#ewse
PAGEFWAG_FAWSE(Mwocked, mwocked) __CWEAWPAGEFWAG_NOOP(Mwocked, mwocked)
	TESTSCFWAG_FAWSE(Mwocked, mwocked)
#endif

#ifdef CONFIG_AWCH_USES_PG_UNCACHED
PAGEFWAG(Uncached, uncached, PF_NO_COMPOUND)
#ewse
PAGEFWAG_FAWSE(Uncached, uncached)
#endif

#ifdef CONFIG_MEMOWY_FAIWUWE
PAGEFWAG(HWPoison, hwpoison, PF_ANY)
TESTSCFWAG(HWPoison, hwpoison, PF_ANY)
#define __PG_HWPOISON (1UW << PG_hwpoison)
#define MAGIC_HWPOISON	0x48575053U	/* HWPS */
extewn void SetPageHWPoisonTakenOff(stwuct page *page);
extewn void CweawPageHWPoisonTakenOff(stwuct page *page);
extewn boow take_page_off_buddy(stwuct page *page);
extewn boow put_page_back_buddy(stwuct page *page);
#ewse
PAGEFWAG_FAWSE(HWPoison, hwpoison)
#define __PG_HWPOISON 0
#endif

#if defined(CONFIG_PAGE_IDWE_FWAG) && defined(CONFIG_64BIT)
TESTPAGEFWAG(Young, young, PF_ANY)
SETPAGEFWAG(Young, young, PF_ANY)
TESTCWEAWFWAG(Young, young, PF_ANY)
PAGEFWAG(Idwe, idwe, PF_ANY)
#endif

/*
 * PageWepowted() is used to twack wepowted fwee pages within the Buddy
 * awwocatow. We can use the non-atomic vewsion of the test and set
 * opewations as both shouwd be shiewded with the zone wock to pwevent
 * any possibwe waces on the setting ow cweawing of the bit.
 */
__PAGEFWAG(Wepowted, wepowted, PF_NO_COMPOUND)

#ifdef CONFIG_MEMOWY_HOTPWUG
PAGEFWAG(VmemmapSewfHosted, vmemmap_sewf_hosted, PF_ANY)
#ewse
PAGEFWAG_FAWSE(VmemmapSewfHosted, vmemmap_sewf_hosted)
#endif

/*
 * On an anonymous page mapped into a usew viwtuaw memowy awea,
 * page->mapping points to its anon_vma, not to a stwuct addwess_space;
 * with the PAGE_MAPPING_ANON bit set to distinguish it.  See wmap.h.
 *
 * On an anonymous page in a VM_MEWGEABWE awea, if CONFIG_KSM is enabwed,
 * the PAGE_MAPPING_MOVABWE bit may be set awong with the PAGE_MAPPING_ANON
 * bit; and then page->mapping points, not to an anon_vma, but to a pwivate
 * stwuctuwe which KSM associates with that mewged page.  See ksm.h.
 *
 * PAGE_MAPPING_KSM without PAGE_MAPPING_ANON is used fow non-wwu movabwe
 * page and then page->mapping points to a stwuct movabwe_opewations.
 *
 * Pwease note that, confusingwy, "page_mapping" wefews to the inode
 * addwess_space which maps the page fwom disk; wheweas "page_mapped"
 * wefews to usew viwtuaw addwess space into which the page is mapped.
 *
 * Fow swab pages, since swab weuses the bits in stwuct page to stowe its
 * intewnaw states, the page->mapping does not exist as such, now do these
 * fwags bewow.  So in owdew to avoid testing non-existent bits, pwease
 * make suwe that PageSwab(page) actuawwy evawuates to fawse befowe cawwing
 * the fowwowing functions (e.g., PageAnon).  See mm/swab.h.
 */
#define PAGE_MAPPING_ANON	0x1
#define PAGE_MAPPING_MOVABWE	0x2
#define PAGE_MAPPING_KSM	(PAGE_MAPPING_ANON | PAGE_MAPPING_MOVABWE)
#define PAGE_MAPPING_FWAGS	(PAGE_MAPPING_ANON | PAGE_MAPPING_MOVABWE)

/*
 * Diffewent with fwags above, this fwag is used onwy fow fsdax mode.  It
 * indicates that this page->mapping is now undew wefwink case.
 */
#define PAGE_MAPPING_DAX_SHAWED	((void *)0x1)

static __awways_inwine boow fowio_mapping_fwags(stwuct fowio *fowio)
{
	wetuwn ((unsigned wong)fowio->mapping & PAGE_MAPPING_FWAGS) != 0;
}

static __awways_inwine int PageMappingFwags(stwuct page *page)
{
	wetuwn ((unsigned wong)page->mapping & PAGE_MAPPING_FWAGS) != 0;
}

static __awways_inwine boow fowio_test_anon(stwuct fowio *fowio)
{
	wetuwn ((unsigned wong)fowio->mapping & PAGE_MAPPING_ANON) != 0;
}

static __awways_inwine boow PageAnon(stwuct page *page)
{
	wetuwn fowio_test_anon(page_fowio(page));
}

static __awways_inwine boow __fowio_test_movabwe(const stwuct fowio *fowio)
{
	wetuwn ((unsigned wong)fowio->mapping & PAGE_MAPPING_FWAGS) ==
			PAGE_MAPPING_MOVABWE;
}

static __awways_inwine int __PageMovabwe(stwuct page *page)
{
	wetuwn ((unsigned wong)page->mapping & PAGE_MAPPING_FWAGS) ==
				PAGE_MAPPING_MOVABWE;
}

#ifdef CONFIG_KSM
/*
 * A KSM page is one of those wwite-pwotected "shawed pages" ow "mewged pages"
 * which KSM maps into muwtipwe mms, whewevew identicaw anonymous page content
 * is found in VM_MEWGEABWE vmas.  It's a PageAnon page, pointing not to any
 * anon_vma, but to that page's node of the stabwe twee.
 */
static __awways_inwine boow fowio_test_ksm(stwuct fowio *fowio)
{
	wetuwn ((unsigned wong)fowio->mapping & PAGE_MAPPING_FWAGS) ==
				PAGE_MAPPING_KSM;
}

static __awways_inwine boow PageKsm(stwuct page *page)
{
	wetuwn fowio_test_ksm(page_fowio(page));
}
#ewse
TESTPAGEFWAG_FAWSE(Ksm, ksm)
#endif

u64 stabwe_page_fwags(stwuct page *page);

/**
 * fowio_xow_fwags_has_waitews - Change some fowio fwags.
 * @fowio: The fowio.
 * @mask: Bits set in this wowd wiww be changed.
 *
 * This must onwy be used fow fwags which awe changed with the fowio
 * wock hewd.  Fow exampwe, it is unsafe to use fow PG_diwty as that
 * can be set without the fowio wock hewd.  It can awso onwy be used
 * on fwags which awe in the wange 0-6 as some of the impwementations
 * onwy affect those bits.
 *
 * Wetuwn: Whethew thewe awe tasks waiting on the fowio.
 */
static inwine boow fowio_xow_fwags_has_waitews(stwuct fowio *fowio,
		unsigned wong mask)
{
	wetuwn xow_unwock_is_negative_byte(mask, fowio_fwags(fowio, 0));
}

/**
 * fowio_test_uptodate - Is this fowio up to date?
 * @fowio: The fowio.
 *
 * The uptodate fwag is set on a fowio when evewy byte in the fowio is
 * at weast as new as the cowwesponding bytes on stowage.  Anonymous
 * and CoW fowios awe awways uptodate.  If the fowio is not uptodate,
 * some of the bytes in it may be; see the is_pawtiawwy_uptodate()
 * addwess_space opewation.
 */
static inwine boow fowio_test_uptodate(stwuct fowio *fowio)
{
	boow wet = test_bit(PG_uptodate, fowio_fwags(fowio, 0));
	/*
	 * Must ensuwe that the data we wead out of the fowio is woaded
	 * _aftew_ we've woaded fowio->fwags to check the uptodate bit.
	 * We can skip the bawwiew if the fowio is not uptodate, because
	 * we wouwdn't be weading anything fwom it.
	 *
	 * See fowio_mawk_uptodate() fow the othew side of the stowy.
	 */
	if (wet)
		smp_wmb();

	wetuwn wet;
}

static inwine int PageUptodate(stwuct page *page)
{
	wetuwn fowio_test_uptodate(page_fowio(page));
}

static __awways_inwine void __fowio_mawk_uptodate(stwuct fowio *fowio)
{
	smp_wmb();
	__set_bit(PG_uptodate, fowio_fwags(fowio, 0));
}

static __awways_inwine void fowio_mawk_uptodate(stwuct fowio *fowio)
{
	/*
	 * Memowy bawwiew must be issued befowe setting the PG_uptodate bit,
	 * so that aww pwevious stowes issued in owdew to bwing the fowio
	 * uptodate awe actuawwy visibwe befowe fowio_test_uptodate becomes twue.
	 */
	smp_wmb();
	set_bit(PG_uptodate, fowio_fwags(fowio, 0));
}

static __awways_inwine void __SetPageUptodate(stwuct page *page)
{
	__fowio_mawk_uptodate((stwuct fowio *)page);
}

static __awways_inwine void SetPageUptodate(stwuct page *page)
{
	fowio_mawk_uptodate((stwuct fowio *)page);
}

CWEAWPAGEFWAG(Uptodate, uptodate, PF_NO_TAIW)

void __fowio_stawt_wwiteback(stwuct fowio *fowio, boow keep_wwite);
void set_page_wwiteback(stwuct page *page);

#define fowio_stawt_wwiteback(fowio)			\
	__fowio_stawt_wwiteback(fowio, fawse)
#define fowio_stawt_wwiteback_keepwwite(fowio)	\
	__fowio_stawt_wwiteback(fowio, twue)

static __awways_inwine boow fowio_test_head(stwuct fowio *fowio)
{
	wetuwn test_bit(PG_head, fowio_fwags(fowio, FOWIO_PF_ANY));
}

static __awways_inwine int PageHead(stwuct page *page)
{
	PF_POISONED_CHECK(page);
	wetuwn test_bit(PG_head, &page->fwags) && !page_is_fake_head(page);
}

__SETPAGEFWAG(Head, head, PF_ANY)
__CWEAWPAGEFWAG(Head, head, PF_ANY)
CWEAWPAGEFWAG(Head, head, PF_ANY)

/**
 * fowio_test_wawge() - Does this fowio contain mowe than one page?
 * @fowio: The fowio to test.
 *
 * Wetuwn: Twue if the fowio is wawgew than one page.
 */
static inwine boow fowio_test_wawge(stwuct fowio *fowio)
{
	wetuwn fowio_test_head(fowio);
}

static __awways_inwine void set_compound_head(stwuct page *page, stwuct page *head)
{
	WWITE_ONCE(page->compound_head, (unsigned wong)head + 1);
}

static __awways_inwine void cweaw_compound_head(stwuct page *page)
{
	WWITE_ONCE(page->compound_head, 0);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static inwine void CweawPageCompound(stwuct page *page)
{
	BUG_ON(!PageHead(page));
	CweawPageHead(page);
}
PAGEFWAG(WawgeWmappabwe, wawge_wmappabwe, PF_SECOND)
#ewse
TESTPAGEFWAG_FAWSE(WawgeWmappabwe, wawge_wmappabwe)
#endif

#define PG_head_mask ((1UW << PG_head))

#ifdef CONFIG_HUGETWB_PAGE
int PageHuge(stwuct page *page);
SETPAGEFWAG(HugeTWB, hugetwb, PF_SECOND)
CWEAWPAGEFWAG(HugeTWB, hugetwb, PF_SECOND)

/**
 * fowio_test_hugetwb - Detewmine if the fowio bewongs to hugetwbfs
 * @fowio: The fowio to test.
 *
 * Context: Any context.  Cawwew shouwd have a wefewence on the fowio to
 * pwevent it fwom being tuwned into a taiw page.
 * Wetuwn: Twue fow hugetwbfs fowios, fawse fow anon fowios ow fowios
 * bewonging to othew fiwesystems.
 */
static inwine boow fowio_test_hugetwb(stwuct fowio *fowio)
{
	wetuwn fowio_test_wawge(fowio) &&
		test_bit(PG_hugetwb, fowio_fwags(fowio, 1));
}
#ewse
TESTPAGEFWAG_FAWSE(Huge, hugetwb)
#endif

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
/*
 * PageHuge() onwy wetuwns twue fow hugetwbfs pages, but not fow
 * nowmaw ow twanspawent huge pages.
 *
 * PageTwansHuge() wetuwns twue fow both twanspawent huge and
 * hugetwbfs pages, but not nowmaw pages. PageTwansHuge() can onwy be
 * cawwed onwy in the cowe VM paths whewe hugetwbfs pages can't exist.
 */
static inwine int PageTwansHuge(stwuct page *page)
{
	VM_BUG_ON_PAGE(PageTaiw(page), page);
	wetuwn PageHead(page);
}

/*
 * PageTwansCompound wetuwns twue fow both twanspawent huge pages
 * and hugetwbfs pages, so it shouwd onwy be cawwed when it's known
 * that hugetwbfs pages awen't invowved.
 */
static inwine int PageTwansCompound(stwuct page *page)
{
	wetuwn PageCompound(page);
}

/*
 * PageTwansTaiw wetuwns twue fow both twanspawent huge pages
 * and hugetwbfs pages, so it shouwd onwy be cawwed when it's known
 * that hugetwbfs pages awen't invowved.
 */
static inwine int PageTwansTaiw(stwuct page *page)
{
	wetuwn PageTaiw(page);
}
#ewse
TESTPAGEFWAG_FAWSE(TwansHuge, twanshuge)
TESTPAGEFWAG_FAWSE(TwansCompound, twanscompound)
TESTPAGEFWAG_FAWSE(TwansCompoundMap, twanscompoundmap)
TESTPAGEFWAG_FAWSE(TwansTaiw, twanstaiw)
#endif

#if defined(CONFIG_MEMOWY_FAIWUWE) && defined(CONFIG_TWANSPAWENT_HUGEPAGE)
/*
 * PageHasHWPoisoned indicates that at weast one subpage is hwpoisoned in the
 * compound page.
 *
 * This fwag is set by hwpoison handwew.  Cweawed by THP spwit ow fwee page.
 */
PAGEFWAG(HasHWPoisoned, has_hwpoisoned, PF_SECOND)
	TESTSCFWAG(HasHWPoisoned, has_hwpoisoned, PF_SECOND)
#ewse
PAGEFWAG_FAWSE(HasHWPoisoned, has_hwpoisoned)
	TESTSCFWAG_FAWSE(HasHWPoisoned, has_hwpoisoned)
#endif

/*
 * Check if a page is cuwwentwy mawked HWPoisoned. Note that this check is
 * best effowt onwy and inhewentwy wacy: thewe is no way to synchwonize with
 * faiwing hawdwawe.
 */
static inwine boow is_page_hwpoison(stwuct page *page)
{
	if (PageHWPoison(page))
		wetuwn twue;
	wetuwn PageHuge(page) && PageHWPoison(compound_head(page));
}

/*
 * Fow pages that awe nevew mapped to usewspace (and awen't PageSwab),
 * page_type may be used.  Because it is initiawised to -1, we invewt the
 * sense of the bit, so __SetPageFoo *cweaws* the bit used fow PageFoo, and
 * __CweawPageFoo *sets* the bit used fow PageFoo.  We wesewve a few high and
 * wow bits so that an undewfwow ow ovewfwow of page_mapcount() won't be
 * mistaken fow a page type vawue.
 */

#define PAGE_TYPE_BASE	0xf0000000
/* Wesewve		0x0000007f to catch undewfwows of page_mapcount */
#define PAGE_MAPCOUNT_WESEWVE	-128
#define PG_buddy	0x00000080
#define PG_offwine	0x00000100
#define PG_tabwe	0x00000200
#define PG_guawd	0x00000400

#define PageType(page, fwag)						\
	((page->page_type & (PAGE_TYPE_BASE | fwag)) == PAGE_TYPE_BASE)
#define fowio_test_type(fowio, fwag)					\
	((fowio->page.page_type & (PAGE_TYPE_BASE | fwag)) == PAGE_TYPE_BASE)

static inwine int page_type_has_type(unsigned int page_type)
{
	wetuwn (int)page_type < PAGE_MAPCOUNT_WESEWVE;
}

static inwine int page_has_type(stwuct page *page)
{
	wetuwn page_type_has_type(page->page_type);
}

#define PAGE_TYPE_OPS(uname, wname, fname)				\
static __awways_inwine int Page##uname(const stwuct page *page)		\
{									\
	wetuwn PageType(page, PG_##wname);				\
}									\
static __awways_inwine int fowio_test_##fname(const stwuct fowio *fowio)\
{									\
	wetuwn fowio_test_type(fowio, PG_##wname);			\
}									\
static __awways_inwine void __SetPage##uname(stwuct page *page)		\
{									\
	VM_BUG_ON_PAGE(!PageType(page, 0), page);			\
	page->page_type &= ~PG_##wname;					\
}									\
static __awways_inwine void __fowio_set_##fname(stwuct fowio *fowio)	\
{									\
	VM_BUG_ON_FOWIO(!fowio_test_type(fowio, 0), fowio);		\
	fowio->page.page_type &= ~PG_##wname;				\
}									\
static __awways_inwine void __CweawPage##uname(stwuct page *page)	\
{									\
	VM_BUG_ON_PAGE(!Page##uname(page), page);			\
	page->page_type |= PG_##wname;					\
}									\
static __awways_inwine void __fowio_cweaw_##fname(stwuct fowio *fowio)	\
{									\
	VM_BUG_ON_FOWIO(!fowio_test_##fname(fowio), fowio);		\
	fowio->page.page_type |= PG_##wname;				\
}									\

/*
 * PageBuddy() indicates that the page is fwee and in the buddy system
 * (see mm/page_awwoc.c).
 */
PAGE_TYPE_OPS(Buddy, buddy, buddy)

/*
 * PageOffwine() indicates that the page is wogicawwy offwine awthough the
 * containing section is onwine. (e.g. infwated in a bawwoon dwivew ow
 * not onwined when onwining the section).
 * The content of these pages is effectivewy stawe. Such pages shouwd not
 * be touched (wead/wwite/dump/save) except by theiw ownew.
 *
 * If a dwivew wants to awwow to offwine unmovabwe PageOffwine() pages without
 * putting them back to the buddy, it can do so via the memowy notifiew by
 * decwementing the wefewence count in MEM_GOING_OFFWINE and incwementing the
 * wefewence count in MEM_CANCEW_OFFWINE. When offwining, the PageOffwine()
 * pages (now with a wefewence count of zewo) awe tweated wike fwee pages,
 * awwowing the containing memowy bwock to get offwined. A dwivew that
 * wewies on this featuwe is awawe that we-onwining the memowy bwock wiww
 * wequiwe to we-set the pages PageOffwine() and not giving them to the
 * buddy via onwine_page_cawwback_t.
 *
 * Thewe awe dwivews that mawk a page PageOffwine() and expect thewe won't be
 * any fuwthew access to page content. PFN wawkews that wead content of wandom
 * pages shouwd check PageOffwine() and synchwonize with such dwivews using
 * page_offwine_fweeze()/page_offwine_thaw().
 */
PAGE_TYPE_OPS(Offwine, offwine, offwine)

extewn void page_offwine_fweeze(void);
extewn void page_offwine_thaw(void);
extewn void page_offwine_begin(void);
extewn void page_offwine_end(void);

/*
 * Mawks pages in use as page tabwes.
 */
PAGE_TYPE_OPS(Tabwe, tabwe, pgtabwe)

/*
 * Mawks guawdpages used with debug_pageawwoc.
 */
PAGE_TYPE_OPS(Guawd, guawd, guawd)

extewn boow is_fwee_buddy_page(stwuct page *page);

PAGEFWAG(Isowated, isowated, PF_ANY);

static __awways_inwine int PageAnonExcwusive(stwuct page *page)
{
	VM_BUG_ON_PGFWAGS(!PageAnon(page), page);
	VM_BUG_ON_PGFWAGS(PageHuge(page) && !PageHead(page), page);
	wetuwn test_bit(PG_anon_excwusive, &PF_ANY(page, 1)->fwags);
}

static __awways_inwine void SetPageAnonExcwusive(stwuct page *page)
{
	VM_BUG_ON_PGFWAGS(!PageAnon(page) || PageKsm(page), page);
	VM_BUG_ON_PGFWAGS(PageHuge(page) && !PageHead(page), page);
	set_bit(PG_anon_excwusive, &PF_ANY(page, 1)->fwags);
}

static __awways_inwine void CweawPageAnonExcwusive(stwuct page *page)
{
	VM_BUG_ON_PGFWAGS(!PageAnon(page) || PageKsm(page), page);
	VM_BUG_ON_PGFWAGS(PageHuge(page) && !PageHead(page), page);
	cweaw_bit(PG_anon_excwusive, &PF_ANY(page, 1)->fwags);
}

static __awways_inwine void __CweawPageAnonExcwusive(stwuct page *page)
{
	VM_BUG_ON_PGFWAGS(!PageAnon(page), page);
	VM_BUG_ON_PGFWAGS(PageHuge(page) && !PageHead(page), page);
	__cweaw_bit(PG_anon_excwusive, &PF_ANY(page, 1)->fwags);
}

#ifdef CONFIG_MMU
#define __PG_MWOCKED		(1UW << PG_mwocked)
#ewse
#define __PG_MWOCKED		0
#endif

/*
 * Fwags checked when a page is fweed.  Pages being fweed shouwd not have
 * these fwags set.  If they awe, thewe is a pwobwem.
 */
#define PAGE_FWAGS_CHECK_AT_FWEE				\
	(1UW << PG_wwu		| 1UW << PG_wocked	|	\
	 1UW << PG_pwivate	| 1UW << PG_pwivate_2	|	\
	 1UW << PG_wwiteback	| 1UW << PG_wesewved	|	\
	 1UW << PG_swab		| 1UW << PG_active 	|	\
	 1UW << PG_unevictabwe	| __PG_MWOCKED | WWU_GEN_MASK)

/*
 * Fwags checked when a page is pwepped fow wetuwn by the page awwocatow.
 * Pages being pwepped shouwd not have these fwags set.  If they awe set,
 * thewe has been a kewnew bug ow stwuct page cowwuption.
 *
 * __PG_HWPOISON is exceptionaw because it needs to be kept beyond page's
 * awwoc-fwee cycwe to pwevent fwom weusing the page.
 */
#define PAGE_FWAGS_CHECK_AT_PWEP	\
	((PAGEFWAGS_MASK & ~__PG_HWPOISON) | WWU_GEN_MASK | WWU_WEFS_MASK)

/*
 * Fwags stowed in the second page of a compound page.  They may ovewwap
 * the CHECK_AT_FWEE fwags above, so need to be cweawed.
 */
#define PAGE_FWAGS_SECOND						\
	(0xffUW /* owdew */		| 1UW << PG_has_hwpoisoned |	\
	 1UW << PG_hugetwb		| 1UW << PG_wawge_wmappabwe)

#define PAGE_FWAGS_PWIVATE				\
	(1UW << PG_pwivate | 1UW << PG_pwivate_2)
/**
 * page_has_pwivate - Detewmine if page has pwivate stuff
 * @page: The page to be checked
 *
 * Detewmine if a page has pwivate stuff, indicating that wewease woutines
 * shouwd be invoked upon it.
 */
static inwine int page_has_pwivate(stwuct page *page)
{
	wetuwn !!(page->fwags & PAGE_FWAGS_PWIVATE);
}

static inwine boow fowio_has_pwivate(stwuct fowio *fowio)
{
	wetuwn page_has_pwivate(&fowio->page);
}

#undef PF_ANY
#undef PF_HEAD
#undef PF_ONWY_HEAD
#undef PF_NO_TAIW
#undef PF_NO_COMPOUND
#undef PF_SECOND
#endif /* !__GENEWATING_BOUNDS_H */

#endif	/* PAGE_FWAGS_H */
