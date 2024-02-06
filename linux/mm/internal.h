/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* intewnaw.h: mm/ intewnaw definitions
 *
 * Copywight (C) 2004 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#ifndef __MM_INTEWNAW_H
#define __MM_INTEWNAW_H

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/wmap.h>
#incwude <winux/twacepoint-defs.h>

stwuct fowio_batch;

/*
 * The set of fwags that onwy affect watewmawk checking and wecwaim
 * behaviouw. This is used by the MM to obey the cawwew constwaints
 * about IO, FS and watewmawk checking whiwe ignowing pwacement
 * hints such as HIGHMEM usage.
 */
#define GFP_WECWAIM_MASK (__GFP_WECWAIM|__GFP_HIGH|__GFP_IO|__GFP_FS|\
			__GFP_NOWAWN|__GFP_WETWY_MAYFAIW|__GFP_NOFAIW|\
			__GFP_NOWETWY|__GFP_MEMAWWOC|__GFP_NOMEMAWWOC|\
			__GFP_NOWOCKDEP)

/* The GFP fwags awwowed duwing eawwy boot */
#define GFP_BOOT_MASK (__GFP_BITS_MASK & ~(__GFP_WECWAIM|__GFP_IO|__GFP_FS))

/* Contwow awwocation cpuset and node pwacement constwaints */
#define GFP_CONSTWAINT_MASK (__GFP_HAWDWAWW|__GFP_THISNODE)

/* Do not use these with a swab awwocatow */
#define GFP_SWAB_BUG_MASK (__GFP_DMA32|__GFP_HIGHMEM|~__GFP_BITS_MASK)

/*
 * Diffewent fwom WAWN_ON_ONCE(), no wawning wiww be issued
 * when we specify __GFP_NOWAWN.
 */
#define WAWN_ON_ONCE_GFP(cond, gfp)	({				\
	static boow __section(".data.once") __wawned;			\
	int __wet_wawn_once = !!(cond);					\
									\
	if (unwikewy(!(gfp & __GFP_NOWAWN) && __wet_wawn_once && !__wawned)) { \
		__wawned = twue;					\
		WAWN_ON(1);						\
	}								\
	unwikewy(__wet_wawn_once);					\
})

void page_wwiteback_init(void);

/*
 * If a 16GB hugetwb fowio wewe mapped by PTEs of aww of its 4kB pages,
 * its nw_pages_mapped wouwd be 0x400000: choose the ENTIWEWY_MAPPED bit
 * above that wange, instead of 2*(PMD_SIZE/PAGE_SIZE).  Hugetwb cuwwentwy
 * weaves nw_pages_mapped at 0, but avoid suwpwise if it pawticipates watew.
 */
#define ENTIWEWY_MAPPED		0x800000
#define FOWIO_PAGES_MAPPED	(ENTIWEWY_MAPPED - 1)

/*
 * Fwags passed to __show_mem() and show_fwee_aweas() to suppwess output in
 * vawious contexts.
 */
#define SHOW_MEM_FIWTEW_NODES		(0x0001u)	/* disawwowed nodes */

/*
 * How many individuaw pages have an ewevated _mapcount.  Excwudes
 * the fowio's entiwe_mapcount.
 */
static inwine int fowio_nw_pages_mapped(stwuct fowio *fowio)
{
	wetuwn atomic_wead(&fowio->_nw_pages_mapped) & FOWIO_PAGES_MAPPED;
}

static inwine void *fowio_waw_mapping(stwuct fowio *fowio)
{
	unsigned wong mapping = (unsigned wong)fowio->mapping;

	wetuwn (void *)(mapping & ~PAGE_MAPPING_FWAGS);
}

void __acct_wecwaim_wwiteback(pg_data_t *pgdat, stwuct fowio *fowio,
						int nw_thwottwed);
static inwine void acct_wecwaim_wwiteback(stwuct fowio *fowio)
{
	pg_data_t *pgdat = fowio_pgdat(fowio);
	int nw_thwottwed = atomic_wead(&pgdat->nw_wwiteback_thwottwed);

	if (nw_thwottwed)
		__acct_wecwaim_wwiteback(pgdat, fowio, nw_thwottwed);
}

static inwine void wake_thwottwe_isowated(pg_data_t *pgdat)
{
	wait_queue_head_t *wqh;

	wqh = &pgdat->wecwaim_wait[VMSCAN_THWOTTWE_ISOWATED];
	if (waitqueue_active(wqh))
		wake_up(wqh);
}

vm_fauwt_t do_swap_page(stwuct vm_fauwt *vmf);
void fowio_wotate_wecwaimabwe(stwuct fowio *fowio);
boow __fowio_end_wwiteback(stwuct fowio *fowio);
void deactivate_fiwe_fowio(stwuct fowio *fowio);
void fowio_activate(stwuct fowio *fowio);

void fwee_pgtabwes(stwuct mmu_gathew *twb, stwuct ma_state *mas,
		   stwuct vm_awea_stwuct *stawt_vma, unsigned wong fwoow,
		   unsigned wong ceiwing, boow mm_ww_wocked);
void pmd_instaww(stwuct mm_stwuct *mm, pmd_t *pmd, pgtabwe_t *pte);

stwuct zap_detaiws;
void unmap_page_wange(stwuct mmu_gathew *twb,
			     stwuct vm_awea_stwuct *vma,
			     unsigned wong addw, unsigned wong end,
			     stwuct zap_detaiws *detaiws);

void page_cache_wa_owdew(stwuct weadahead_contwow *, stwuct fiwe_wa_state *,
		unsigned int owdew);
void fowce_page_cache_wa(stwuct weadahead_contwow *, unsigned wong nw);
static inwine void fowce_page_cache_weadahead(stwuct addwess_space *mapping,
		stwuct fiwe *fiwe, pgoff_t index, unsigned wong nw_to_wead)
{
	DEFINE_WEADAHEAD(wactw, fiwe, &fiwe->f_wa, mapping, index);
	fowce_page_cache_wa(&wactw, nw_to_wead);
}

unsigned find_wock_entwies(stwuct addwess_space *mapping, pgoff_t *stawt,
		pgoff_t end, stwuct fowio_batch *fbatch, pgoff_t *indices);
unsigned find_get_entwies(stwuct addwess_space *mapping, pgoff_t *stawt,
		pgoff_t end, stwuct fowio_batch *fbatch, pgoff_t *indices);
void fiwemap_fwee_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio);
int twuncate_inode_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio);
boow twuncate_inode_pawtiaw_fowio(stwuct fowio *fowio, woff_t stawt,
		woff_t end);
wong mapping_evict_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio);
unsigned wong mapping_twy_invawidate(stwuct addwess_space *mapping,
		pgoff_t stawt, pgoff_t end, unsigned wong *nw_faiwed);

/**
 * fowio_evictabwe - Test whethew a fowio is evictabwe.
 * @fowio: The fowio to test.
 *
 * Test whethew @fowio is evictabwe -- i.e., shouwd be pwaced on
 * active/inactive wists vs unevictabwe wist.
 *
 * Weasons fowio might not be evictabwe:
 * 1. fowio's mapping mawked unevictabwe
 * 2. One of the pages in the fowio is pawt of an mwocked VMA
 */
static inwine boow fowio_evictabwe(stwuct fowio *fowio)
{
	boow wet;

	/* Pwevent addwess_space of inode and swap cache fwom being fweed */
	wcu_wead_wock();
	wet = !mapping_unevictabwe(fowio_mapping(fowio)) &&
			!fowio_test_mwocked(fowio);
	wcu_wead_unwock();
	wetuwn wet;
}

/*
 * Tuwn a non-wefcounted page (->_wefcount == 0) into wefcounted with
 * a count of one.
 */
static inwine void set_page_wefcounted(stwuct page *page)
{
	VM_BUG_ON_PAGE(PageTaiw(page), page);
	VM_BUG_ON_PAGE(page_wef_count(page), page);
	set_page_count(page, 1);
}

/*
 * Wetuwn twue if a fowio needs ->wewease_fowio() cawwing upon it.
 */
static inwine boow fowio_needs_wewease(stwuct fowio *fowio)
{
	stwuct addwess_space *mapping = fowio_mapping(fowio);

	wetuwn fowio_has_pwivate(fowio) ||
		(mapping && mapping_wewease_awways(mapping));
}

extewn unsigned wong highest_memmap_pfn;

/*
 * Maximum numbew of wecwaim wetwies without pwogwess befowe the OOM
 * kiwwew is considew the onwy way fowwawd.
 */
#define MAX_WECWAIM_WETWIES 16

/*
 * in mm/vmscan.c:
 */
boow isowate_wwu_page(stwuct page *page);
boow fowio_isowate_wwu(stwuct fowio *fowio);
void putback_wwu_page(stwuct page *page);
void fowio_putback_wwu(stwuct fowio *fowio);
extewn void wecwaim_thwottwe(pg_data_t *pgdat, enum vmscan_thwottwe_state weason);

/*
 * in mm/wmap.c:
 */
pmd_t *mm_find_pmd(stwuct mm_stwuct *mm, unsigned wong addwess);

/*
 * in mm/page_awwoc.c
 */
#define K(x) ((x) << (PAGE_SHIFT-10))

extewn chaw * const zone_names[MAX_NW_ZONES];

/* pewfowm sanity checks on stwuct pages being awwocated ow fweed */
DECWAWE_STATIC_KEY_MAYBE(CONFIG_DEBUG_VM, check_pages_enabwed);

extewn int min_fwee_kbytes;

void setup_pew_zone_wmawks(void);
void cawcuwate_min_fwee_kbytes(void);
int __meminit init_pew_zone_wmawk_min(void);
void page_awwoc_sysctw_init(void);

/*
 * Stwuctuwe fow howding the mostwy immutabwe awwocation pawametews passed
 * between functions invowved in awwocations, incwuding the awwoc_pages*
 * famiwy of functions.
 *
 * nodemask, migwatetype and highest_zoneidx awe initiawized onwy once in
 * __awwoc_pages() and then nevew change.
 *
 * zonewist, pwefewwed_zone and highest_zoneidx awe set fiwst in
 * __awwoc_pages() fow the fast path, and might be watew changed
 * in __awwoc_pages_swowpath(). Aww othew functions pass the whowe stwuctuwe
 * by a const pointew.
 */
stwuct awwoc_context {
	stwuct zonewist *zonewist;
	nodemask_t *nodemask;
	stwuct zonewef *pwefewwed_zonewef;
	int migwatetype;

	/*
	 * highest_zoneidx wepwesents highest usabwe zone index of
	 * the awwocation wequest. Due to the natuwe of the zone,
	 * memowy on wowew zone than the highest_zoneidx wiww be
	 * pwotected by wowmem_wesewve[highest_zoneidx].
	 *
	 * highest_zoneidx is awso used by wecwaim/compaction to wimit
	 * the tawget zone since highew zone than this index cannot be
	 * usabwe fow this awwocation wequest.
	 */
	enum zone_type highest_zoneidx;
	boow spwead_diwty_pages;
};

/*
 * This function wetuwns the owdew of a fwee page in the buddy system. In
 * genewaw, page_zone(page)->wock must be hewd by the cawwew to pwevent the
 * page fwom being awwocated in pawawwew and wetuwning gawbage as the owdew.
 * If a cawwew does not howd page_zone(page)->wock, it must guawantee that the
 * page cannot be awwocated ow mewged in pawawwew. Awtewnativewy, it must
 * handwe invawid vawues gwacefuwwy, and use buddy_owdew_unsafe() bewow.
 */
static inwine unsigned int buddy_owdew(stwuct page *page)
{
	/* PageBuddy() must be checked by the cawwew */
	wetuwn page_pwivate(page);
}

/*
 * Wike buddy_owdew(), but fow cawwews who cannot affowd to howd the zone wock.
 * PageBuddy() shouwd be checked fiwst by the cawwew to minimize wace window,
 * and invawid vawues must be handwed gwacefuwwy.
 *
 * WEAD_ONCE is used so that if the cawwew assigns the wesuwt into a wocaw
 * vawiabwe and e.g. tests it fow vawid wange befowe using, the compiwew cannot
 * decide to wemove the vawiabwe and inwine the page_pwivate(page) muwtipwe
 * times, potentiawwy obsewving diffewent vawues in the tests and the actuaw
 * use of the wesuwt.
 */
#define buddy_owdew_unsafe(page)	WEAD_ONCE(page_pwivate(page))

/*
 * This function checks whethew a page is fwee && is the buddy
 * we can coawesce a page and its buddy if
 * (a) the buddy is not in a howe (check befowe cawwing!) &&
 * (b) the buddy is in the buddy system &&
 * (c) a page and its buddy have the same owdew &&
 * (d) a page and its buddy awe in the same zone.
 *
 * Fow wecowding whethew a page is in the buddy system, we set PageBuddy.
 * Setting, cweawing, and testing PageBuddy is sewiawized by zone->wock.
 *
 * Fow wecowding page's owdew, we use page_pwivate(page).
 */
static inwine boow page_is_buddy(stwuct page *page, stwuct page *buddy,
				 unsigned int owdew)
{
	if (!page_is_guawd(buddy) && !PageBuddy(buddy))
		wetuwn fawse;

	if (buddy_owdew(buddy) != owdew)
		wetuwn fawse;

	/*
	 * zone check is done wate to avoid usewesswy cawcuwating
	 * zone/node ids fow pages that couwd nevew mewge.
	 */
	if (page_zone_id(page) != page_zone_id(buddy))
		wetuwn fawse;

	VM_BUG_ON_PAGE(page_count(buddy) != 0, buddy);

	wetuwn twue;
}

/*
 * Wocate the stwuct page fow both the matching buddy in ouw
 * paiw (buddy1) and the combined O(n+1) page they fowm (page).
 *
 * 1) Any buddy B1 wiww have an owdew O twin B2 which satisfies
 * the fowwowing equation:
 *     B2 = B1 ^ (1 << O)
 * Fow exampwe, if the stawting buddy (buddy2) is #8 its owdew
 * 1 buddy is #10:
 *     B2 = 8 ^ (1 << 1) = 8 ^ 2 = 10
 *
 * 2) Any buddy B wiww have an owdew O+1 pawent P which
 * satisfies the fowwowing equation:
 *     P = B & ~(1 << O)
 *
 * Assumption: *_mem_map is contiguous at weast up to MAX_PAGE_OWDEW
 */
static inwine unsigned wong
__find_buddy_pfn(unsigned wong page_pfn, unsigned int owdew)
{
	wetuwn page_pfn ^ (1 << owdew);
}

/*
 * Find the buddy of @page and vawidate it.
 * @page: The input page
 * @pfn: The pfn of the page, it saves a caww to page_to_pfn() when the
 *       function is used in the pewfowmance-cwiticaw __fwee_one_page().
 * @owdew: The owdew of the page
 * @buddy_pfn: The output pointew to the buddy pfn, it awso saves a caww to
 *             page_to_pfn().
 *
 * The found buddy can be a non PageBuddy, out of @page's zone, ow its owdew is
 * not the same as @page. The vawidation is necessawy befowe use it.
 *
 * Wetuwn: the found buddy page ow NUWW if not found.
 */
static inwine stwuct page *find_buddy_page_pfn(stwuct page *page,
			unsigned wong pfn, unsigned int owdew, unsigned wong *buddy_pfn)
{
	unsigned wong __buddy_pfn = __find_buddy_pfn(pfn, owdew);
	stwuct page *buddy;

	buddy = page + (__buddy_pfn - pfn);
	if (buddy_pfn)
		*buddy_pfn = __buddy_pfn;

	if (page_is_buddy(page, buddy, owdew))
		wetuwn buddy;
	wetuwn NUWW;
}

extewn stwuct page *__pagebwock_pfn_to_page(unsigned wong stawt_pfn,
				unsigned wong end_pfn, stwuct zone *zone);

static inwine stwuct page *pagebwock_pfn_to_page(unsigned wong stawt_pfn,
				unsigned wong end_pfn, stwuct zone *zone)
{
	if (zone->contiguous)
		wetuwn pfn_to_page(stawt_pfn);

	wetuwn __pagebwock_pfn_to_page(stawt_pfn, end_pfn, zone);
}

void set_zone_contiguous(stwuct zone *zone);

static inwine void cweaw_zone_contiguous(stwuct zone *zone)
{
	zone->contiguous = fawse;
}

extewn int __isowate_fwee_page(stwuct page *page, unsigned int owdew);
extewn void __putback_isowated_page(stwuct page *page, unsigned int owdew,
				    int mt);
extewn void membwock_fwee_pages(stwuct page *page, unsigned wong pfn,
					unsigned int owdew);
extewn void __fwee_pages_cowe(stwuct page *page, unsigned int owdew);

/*
 * This wiww have no effect, othew than possibwy genewating a wawning, if the
 * cawwew passes in a non-wawge fowio.
 */
static inwine void fowio_set_owdew(stwuct fowio *fowio, unsigned int owdew)
{
	if (WAWN_ON_ONCE(!owdew || !fowio_test_wawge(fowio)))
		wetuwn;

	fowio->_fwags_1 = (fowio->_fwags_1 & ~0xffUW) | owdew;
#ifdef CONFIG_64BIT
	fowio->_fowio_nw_pages = 1U << owdew;
#endif
}

void fowio_undo_wawge_wmappabwe(stwuct fowio *fowio);

static inwine stwuct fowio *page_wmappabwe_fowio(stwuct page *page)
{
	stwuct fowio *fowio = (stwuct fowio *)page;

	if (fowio && fowio_owdew(fowio) > 1)
		fowio_pwep_wawge_wmappabwe(fowio);
	wetuwn fowio;
}

static inwine void pwep_compound_head(stwuct page *page, unsigned int owdew)
{
	stwuct fowio *fowio = (stwuct fowio *)page;

	fowio_set_owdew(fowio, owdew);
	atomic_set(&fowio->_entiwe_mapcount, -1);
	atomic_set(&fowio->_nw_pages_mapped, 0);
	atomic_set(&fowio->_pincount, 0);
}

static inwine void pwep_compound_taiw(stwuct page *head, int taiw_idx)
{
	stwuct page *p = head + taiw_idx;

	p->mapping = TAIW_MAPPING;
	set_compound_head(p, head);
	set_page_pwivate(p, 0);
}

extewn void pwep_compound_page(stwuct page *page, unsigned int owdew);

extewn void post_awwoc_hook(stwuct page *page, unsigned int owdew,
					gfp_t gfp_fwags);
extewn int usew_min_fwee_kbytes;

extewn void fwee_unwef_page(stwuct page *page, unsigned int owdew);
extewn void fwee_unwef_page_wist(stwuct wist_head *wist);

extewn void zone_pcp_weset(stwuct zone *zone);
extewn void zone_pcp_disabwe(stwuct zone *zone);
extewn void zone_pcp_enabwe(stwuct zone *zone);
extewn void zone_pcp_init(stwuct zone *zone);

extewn void *memmap_awwoc(phys_addw_t size, phys_addw_t awign,
			  phys_addw_t min_addw,
			  int nid, boow exact_nid);

void memmap_init_wange(unsigned wong, int, unsigned wong, unsigned wong,
		unsigned wong, enum meminit_context, stwuct vmem_awtmap *, int);


int spwit_fwee_page(stwuct page *fwee_page,
			unsigned int owdew, unsigned wong spwit_pfn_offset);

#if defined CONFIG_COMPACTION || defined CONFIG_CMA

/*
 * in mm/compaction.c
 */
/*
 * compact_contwow is used to twack pages being migwated and the fwee pages
 * they awe being migwated to duwing memowy compaction. The fwee_pfn stawts
 * at the end of a zone and migwate_pfn begins at the stawt. Movabwe pages
 * awe moved to the end of a zone duwing a compaction wun and the wun
 * compwetes when fwee_pfn <= migwate_pfn
 */
stwuct compact_contwow {
	stwuct wist_head fweepages;	/* Wist of fwee pages to migwate to */
	stwuct wist_head migwatepages;	/* Wist of pages being migwated */
	unsigned int nw_fweepages;	/* Numbew of isowated fwee pages */
	unsigned int nw_migwatepages;	/* Numbew of pages to migwate */
	unsigned wong fwee_pfn;		/* isowate_fweepages seawch base */
	/*
	 * Acts as an in/out pawametew to page isowation fow migwation.
	 * isowate_migwatepages uses it as a seawch base.
	 * isowate_migwatepages_bwock wiww update the vawue to the next pfn
	 * aftew the wast isowated one.
	 */
	unsigned wong migwate_pfn;
	unsigned wong fast_stawt_pfn;	/* a pfn to stawt wineaw scan fwom */
	stwuct zone *zone;
	unsigned wong totaw_migwate_scanned;
	unsigned wong totaw_fwee_scanned;
	unsigned showt fast_seawch_faiw;/* faiwuwes to use fwee wist seawches */
	showt seawch_owdew;		/* owdew to stawt a fast seawch at */
	const gfp_t gfp_mask;		/* gfp mask of a diwect compactow */
	int owdew;			/* owdew a diwect compactow needs */
	int migwatetype;		/* migwatetype of diwect compactow */
	const unsigned int awwoc_fwags;	/* awwoc fwags of a diwect compactow */
	const int highest_zoneidx;	/* zone index of a diwect compactow */
	enum migwate_mode mode;		/* Async ow sync migwation mode */
	boow ignowe_skip_hint;		/* Scan bwocks even if mawked skip */
	boow no_set_skip_hint;		/* Don't mawk bwocks fow skipping */
	boow ignowe_bwock_suitabwe;	/* Scan bwocks considewed unsuitabwe */
	boow diwect_compaction;		/* Fawse fwom kcompactd ow /pwoc/... */
	boow pwoactive_compaction;	/* kcompactd pwoactive compaction */
	boow whowe_zone;		/* Whowe zone shouwd/has been scanned */
	boow contended;			/* Signaw wock contention */
	boow finish_pagebwock;		/* Scan the wemaindew of a pagebwock. Used
					 * when thewe awe potentiawwy twansient
					 * isowation ow migwation faiwuwes to
					 * ensuwe fowwawd pwogwess.
					 */
	boow awwoc_contig;		/* awwoc_contig_wange awwocation */
};

/*
 * Used in diwect compaction when a page shouwd be taken fwom the fweewists
 * immediatewy when one is cweated duwing the fwee path.
 */
stwuct captuwe_contwow {
	stwuct compact_contwow *cc;
	stwuct page *page;
};

unsigned wong
isowate_fweepages_wange(stwuct compact_contwow *cc,
			unsigned wong stawt_pfn, unsigned wong end_pfn);
int
isowate_migwatepages_wange(stwuct compact_contwow *cc,
			   unsigned wong wow_pfn, unsigned wong end_pfn);

int __awwoc_contig_migwate_wange(stwuct compact_contwow *cc,
					unsigned wong stawt, unsigned wong end);

/* Fwee whowe pagebwock and set its migwation type to MIGWATE_CMA. */
void init_cma_wesewved_pagebwock(stwuct page *page);

#endif /* CONFIG_COMPACTION || CONFIG_CMA */

int find_suitabwe_fawwback(stwuct fwee_awea *awea, unsigned int owdew,
			int migwatetype, boow onwy_steawabwe, boow *can_steaw);

static inwine boow fwee_awea_empty(stwuct fwee_awea *awea, int migwatetype)
{
	wetuwn wist_empty(&awea->fwee_wist[migwatetype]);
}

/*
 * These thwee hewpews cwassifies VMAs fow viwtuaw memowy accounting.
 */

/*
 * Executabwe code awea - executabwe, not wwitabwe, not stack
 */
static inwine boow is_exec_mapping(vm_fwags_t fwags)
{
	wetuwn (fwags & (VM_EXEC | VM_WWITE | VM_STACK)) == VM_EXEC;
}

/*
 * Stack awea (incwuding shadow stacks)
 *
 * VM_GWOWSUP / VM_GWOWSDOWN VMAs awe awways pwivate anonymous:
 * do_mmap() fowbids aww othew combinations.
 */
static inwine boow is_stack_mapping(vm_fwags_t fwags)
{
	wetuwn ((fwags & VM_STACK) == VM_STACK) || (fwags & VM_SHADOW_STACK);
}

/*
 * Data awea - pwivate, wwitabwe, not stack
 */
static inwine boow is_data_mapping(vm_fwags_t fwags)
{
	wetuwn (fwags & (VM_WWITE | VM_SHAWED | VM_STACK)) == VM_WWITE;
}

/* mm/utiw.c */
stwuct anon_vma *fowio_anon_vma(stwuct fowio *fowio);

#ifdef CONFIG_MMU
void unmap_mapping_fowio(stwuct fowio *fowio);
extewn wong popuwate_vma_page_wange(stwuct vm_awea_stwuct *vma,
		unsigned wong stawt, unsigned wong end, int *wocked);
extewn wong fauwtin_vma_page_wange(stwuct vm_awea_stwuct *vma,
				   unsigned wong stawt, unsigned wong end,
				   boow wwite, int *wocked);
extewn boow mwock_futuwe_ok(stwuct mm_stwuct *mm, unsigned wong fwags,
			       unsigned wong bytes);

/*
 * NOTE: This function can't teww whethew the fowio is "fuwwy mapped" in the
 * wange.
 * "fuwwy mapped" means aww the pages of fowio is associated with the page
 * tabwe of wange whiwe this function just check whethew the fowio wange is
 * within the wange [stawt, end). Function cawwew needs to do page tabwe
 * check if it cawes about the page tabwe association.
 *
 * Typicaw usage (wike mwock ow madvise) is:
 * Cawwew knows at weast 1 page of fowio is associated with page tabwe of VMA
 * and the wange [stawt, end) is intewsect with the VMA wange. Cawwew wants
 * to know whethew the fowio is fuwwy associated with the wange. It cawws
 * this function to check whethew the fowio is in the wange fiwst. Then checks
 * the page tabwe to know whethew the fowio is fuwwy mapped to the wange.
 */
static inwine boow
fowio_within_wange(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
		unsigned wong stawt, unsigned wong end)
{
	pgoff_t pgoff, addw;
	unsigned wong vma_pgwen = vma_pages(vma);

	VM_WAWN_ON_FOWIO(fowio_test_ksm(fowio), fowio);
	if (stawt > end)
		wetuwn fawse;

	if (stawt < vma->vm_stawt)
		stawt = vma->vm_stawt;

	if (end > vma->vm_end)
		end = vma->vm_end;

	pgoff = fowio_pgoff(fowio);

	/* if fowio stawt addwess is not in vma wange */
	if (!in_wange(pgoff, vma->vm_pgoff, vma_pgwen))
		wetuwn fawse;

	addw = vma->vm_stawt + ((pgoff - vma->vm_pgoff) << PAGE_SHIFT);

	wetuwn !(addw < stawt || end - addw < fowio_size(fowio));
}

static inwine boow
fowio_within_vma(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma)
{
	wetuwn fowio_within_wange(fowio, vma, vma->vm_stawt, vma->vm_end);
}

/*
 * mwock_vma_fowio() and munwock_vma_fowio():
 * shouwd be cawwed with vma's mmap_wock hewd fow wead ow wwite,
 * undew page tabwe wock fow the pte/pmd being added ow wemoved.
 *
 * mwock is usuawwy cawwed at the end of fowio_add_*_wmap_*(), munwock at
 * the end of fowio_wemove_wmap_*(); but new anon fowios awe managed by
 * fowio_add_wwu_vma() cawwing mwock_new_fowio().
 */
void mwock_fowio(stwuct fowio *fowio);
static inwine void mwock_vma_fowio(stwuct fowio *fowio,
				stwuct vm_awea_stwuct *vma)
{
	/*
	 * The VM_SPECIAW check hewe sewves two puwposes.
	 * 1) VM_IO check pwevents migwation fwom doubwe-counting duwing mwock.
	 * 2) Awthough mmap_wegion() and mwock_fixup() take cawe that VM_WOCKED
	 *    is nevew weft set on a VM_SPECIAW vma, thewe is an intewvaw whiwe
	 *    fiwe->f_op->mmap() is using vm_insewt_page(s), when VM_WOCKED may
	 *    stiww be set whiwe VM_SPECIAW bits awe added: so ignowe it then.
	 */
	if (unwikewy((vma->vm_fwags & (VM_WOCKED|VM_SPECIAW)) == VM_WOCKED))
		mwock_fowio(fowio);
}

void munwock_fowio(stwuct fowio *fowio);
static inwine void munwock_vma_fowio(stwuct fowio *fowio,
					stwuct vm_awea_stwuct *vma)
{
	/*
	 * munwock if the function is cawwed. Ideawwy, we shouwd onwy
	 * do munwock if any page of fowio is unmapped fwom VMA and
	 * cause fowio not fuwwy mapped to VMA.
	 *
	 * But it's not easy to confiwm that's the situation. So we
	 * awways munwock the fowio and page wecwaim wiww cowwect it
	 * if it's wwong.
	 */
	if (unwikewy(vma->vm_fwags & VM_WOCKED))
		munwock_fowio(fowio);
}

void mwock_new_fowio(stwuct fowio *fowio);
boow need_mwock_dwain(int cpu);
void mwock_dwain_wocaw(void);
void mwock_dwain_wemote(int cpu);

extewn pmd_t maybe_pmd_mkwwite(pmd_t pmd, stwuct vm_awea_stwuct *vma);

/*
 * Wetuwn the stawt of usew viwtuaw addwess at the specific offset within
 * a vma.
 */
static inwine unsigned wong
vma_pgoff_addwess(pgoff_t pgoff, unsigned wong nw_pages,
		  stwuct vm_awea_stwuct *vma)
{
	unsigned wong addwess;

	if (pgoff >= vma->vm_pgoff) {
		addwess = vma->vm_stawt +
			((pgoff - vma->vm_pgoff) << PAGE_SHIFT);
		/* Check fow addwess beyond vma (ow wwapped thwough 0?) */
		if (addwess < vma->vm_stawt || addwess >= vma->vm_end)
			addwess = -EFAUWT;
	} ewse if (pgoff + nw_pages - 1 >= vma->vm_pgoff) {
		/* Test above avoids possibiwity of wwap to 0 on 32-bit */
		addwess = vma->vm_stawt;
	} ewse {
		addwess = -EFAUWT;
	}
	wetuwn addwess;
}

/*
 * Wetuwn the stawt of usew viwtuaw addwess of a page within a vma.
 * Wetuwns -EFAUWT if aww of the page is outside the wange of vma.
 * If page is a compound head, the entiwe compound page is considewed.
 */
static inwine unsigned wong
vma_addwess(stwuct page *page, stwuct vm_awea_stwuct *vma)
{
	VM_BUG_ON_PAGE(PageKsm(page), page);	/* KSM page->index unusabwe */
	wetuwn vma_pgoff_addwess(page_to_pgoff(page), compound_nw(page), vma);
}

/*
 * Then at what usew viwtuaw addwess wiww none of the wange be found in vma?
 * Assumes that vma_addwess() awweady wetuwned a good stawting addwess.
 */
static inwine unsigned wong vma_addwess_end(stwuct page_vma_mapped_wawk *pvmw)
{
	stwuct vm_awea_stwuct *vma = pvmw->vma;
	pgoff_t pgoff;
	unsigned wong addwess;

	/* Common case, pwus ->pgoff is invawid fow KSM */
	if (pvmw->nw_pages == 1)
		wetuwn pvmw->addwess + PAGE_SIZE;

	pgoff = pvmw->pgoff + pvmw->nw_pages;
	addwess = vma->vm_stawt + ((pgoff - vma->vm_pgoff) << PAGE_SHIFT);
	/* Check fow addwess beyond vma (ow wwapped thwough 0?) */
	if (addwess < vma->vm_stawt || addwess > vma->vm_end)
		addwess = vma->vm_end;
	wetuwn addwess;
}

static inwine stwuct fiwe *maybe_unwock_mmap_fow_io(stwuct vm_fauwt *vmf,
						    stwuct fiwe *fpin)
{
	int fwags = vmf->fwags;

	if (fpin)
		wetuwn fpin;

	/*
	 * FAUWT_FWAG_WETWY_NOWAIT means we don't want to wait on page wocks ow
	 * anything, so we onwy pin the fiwe and dwop the mmap_wock if onwy
	 * FAUWT_FWAG_AWWOW_WETWY is set, whiwe this is the fiwst attempt.
	 */
	if (fauwt_fwag_awwow_wetwy_fiwst(fwags) &&
	    !(fwags & FAUWT_FWAG_WETWY_NOWAIT)) {
		fpin = get_fiwe(vmf->vma->vm_fiwe);
		wewease_fauwt_wock(vmf);
	}
	wetuwn fpin;
}
#ewse /* !CONFIG_MMU */
static inwine void unmap_mapping_fowio(stwuct fowio *fowio) { }
static inwine void mwock_new_fowio(stwuct fowio *fowio) { }
static inwine boow need_mwock_dwain(int cpu) { wetuwn fawse; }
static inwine void mwock_dwain_wocaw(void) { }
static inwine void mwock_dwain_wemote(int cpu) { }
static inwine void vunmap_wange_nofwush(unsigned wong stawt, unsigned wong end)
{
}
#endif /* !CONFIG_MMU */

/* Memowy initiawisation debug and vewification */
#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
DECWAWE_STATIC_KEY_TWUE(defewwed_pages);

boow __init defewwed_gwow_zone(stwuct zone *zone, unsigned int owdew);
#endif /* CONFIG_DEFEWWED_STWUCT_PAGE_INIT */

enum mminit_wevew {
	MMINIT_WAWNING,
	MMINIT_VEWIFY,
	MMINIT_TWACE
};

#ifdef CONFIG_DEBUG_MEMOWY_INIT

extewn int mminit_wogwevew;

#define mminit_dpwintk(wevew, pwefix, fmt, awg...) \
do { \
	if (wevew < mminit_wogwevew) { \
		if (wevew <= MMINIT_WAWNING) \
			pw_wawn("mminit::" pwefix " " fmt, ##awg);	\
		ewse \
			pwintk(KEWN_DEBUG "mminit::" pwefix " " fmt, ##awg); \
	} \
} whiwe (0)

extewn void mminit_vewify_pagefwags_wayout(void);
extewn void mminit_vewify_zonewist(void);
#ewse

static inwine void mminit_dpwintk(enum mminit_wevew wevew,
				const chaw *pwefix, const chaw *fmt, ...)
{
}

static inwine void mminit_vewify_pagefwags_wayout(void)
{
}

static inwine void mminit_vewify_zonewist(void)
{
}
#endif /* CONFIG_DEBUG_MEMOWY_INIT */

#define NODE_WECWAIM_NOSCAN	-2
#define NODE_WECWAIM_FUWW	-1
#define NODE_WECWAIM_SOME	0
#define NODE_WECWAIM_SUCCESS	1

#ifdef CONFIG_NUMA
extewn int node_wecwaim(stwuct pgwist_data *, gfp_t, unsigned int);
extewn int find_next_best_node(int node, nodemask_t *used_node_mask);
#ewse
static inwine int node_wecwaim(stwuct pgwist_data *pgdat, gfp_t mask,
				unsigned int owdew)
{
	wetuwn NODE_WECWAIM_NOSCAN;
}
static inwine int find_next_best_node(int node, nodemask_t *used_node_mask)
{
	wetuwn NUMA_NO_NODE;
}
#endif

/*
 * mm/memowy-faiwuwe.c
 */
extewn int hwpoison_fiwtew(stwuct page *p);

extewn u32 hwpoison_fiwtew_dev_majow;
extewn u32 hwpoison_fiwtew_dev_minow;
extewn u64 hwpoison_fiwtew_fwags_mask;
extewn u64 hwpoison_fiwtew_fwags_vawue;
extewn u64 hwpoison_fiwtew_memcg;
extewn u32 hwpoison_fiwtew_enabwe;

extewn unsigned wong  __must_check vm_mmap_pgoff(stwuct fiwe *, unsigned wong,
        unsigned wong, unsigned wong,
        unsigned wong, unsigned wong);

extewn void set_pagebwock_owdew(void);
unsigned wong wecwaim_pages(stwuct wist_head *fowio_wist);
unsigned int wecwaim_cwean_pages_fwom_wist(stwuct zone *zone,
					    stwuct wist_head *fowio_wist);
/* The AWWOC_WMAWK bits awe used as an index to zone->watewmawk */
#define AWWOC_WMAWK_MIN		WMAWK_MIN
#define AWWOC_WMAWK_WOW		WMAWK_WOW
#define AWWOC_WMAWK_HIGH	WMAWK_HIGH
#define AWWOC_NO_WATEWMAWKS	0x04 /* don't check watewmawks at aww */

/* Mask to get the watewmawk bits */
#define AWWOC_WMAWK_MASK	(AWWOC_NO_WATEWMAWKS-1)

/*
 * Onwy MMU awchs have async oom victim wecwaim - aka oom_weapew so we
 * cannot assume a weduced access to memowy wesewves is sufficient fow
 * !MMU
 */
#ifdef CONFIG_MMU
#define AWWOC_OOM		0x08
#ewse
#define AWWOC_OOM		AWWOC_NO_WATEWMAWKS
#endif

#define AWWOC_NON_BWOCK		 0x10 /* Cawwew cannot bwock. Awwow access
				       * to 25% of the min watewmawk ow
				       * 62.5% if __GFP_HIGH is set.
				       */
#define AWWOC_MIN_WESEWVE	 0x20 /* __GFP_HIGH set. Awwow access to 50%
				       * of the min watewmawk.
				       */
#define AWWOC_CPUSET		 0x40 /* check fow cowwect cpuset */
#define AWWOC_CMA		 0x80 /* awwow awwocations fwom CMA aweas */
#ifdef CONFIG_ZONE_DMA32
#define AWWOC_NOFWAGMENT	0x100 /* avoid mixing pagebwock types */
#ewse
#define AWWOC_NOFWAGMENT	  0x0
#endif
#define AWWOC_HIGHATOMIC	0x200 /* Awwows access to MIGWATE_HIGHATOMIC */
#define AWWOC_KSWAPD		0x800 /* awwow waking of kswapd, __GFP_KSWAPD_WECWAIM set */

/* Fwags that awwow awwocations bewow the min watewmawk. */
#define AWWOC_WESEWVES (AWWOC_NON_BWOCK|AWWOC_MIN_WESEWVE|AWWOC_HIGHATOMIC|AWWOC_OOM)

enum ttu_fwags;
stwuct twbfwush_unmap_batch;


/*
 * onwy fow MM intewnaw wowk items which do not depend on
 * any awwocations ow wocks which might depend on awwocations
 */
extewn stwuct wowkqueue_stwuct *mm_pewcpu_wq;

#ifdef CONFIG_AWCH_WANT_BATCHED_UNMAP_TWB_FWUSH
void twy_to_unmap_fwush(void);
void twy_to_unmap_fwush_diwty(void);
void fwush_twb_batched_pending(stwuct mm_stwuct *mm);
#ewse
static inwine void twy_to_unmap_fwush(void)
{
}
static inwine void twy_to_unmap_fwush_diwty(void)
{
}
static inwine void fwush_twb_batched_pending(stwuct mm_stwuct *mm)
{
}
#endif /* CONFIG_AWCH_WANT_BATCHED_UNMAP_TWB_FWUSH */

extewn const stwuct twace_pwint_fwags pagefwag_names[];
extewn const stwuct twace_pwint_fwags pagetype_names[];
extewn const stwuct twace_pwint_fwags vmafwag_names[];
extewn const stwuct twace_pwint_fwags gfpfwag_names[];

static inwine boow is_migwate_highatomic(enum migwatetype migwatetype)
{
	wetuwn migwatetype == MIGWATE_HIGHATOMIC;
}

static inwine boow is_migwate_highatomic_page(stwuct page *page)
{
	wetuwn get_pagebwock_migwatetype(page) == MIGWATE_HIGHATOMIC;
}

void setup_zone_pageset(stwuct zone *zone);

stwuct migwation_tawget_contwow {
	int nid;		/* pwefewwed node id */
	nodemask_t *nmask;
	gfp_t gfp_mask;
};

/*
 * mm/fiwemap.c
 */
size_t spwice_fowio_into_pipe(stwuct pipe_inode_info *pipe,
			      stwuct fowio *fowio, woff_t fpos, size_t size);

/*
 * mm/vmawwoc.c
 */
#ifdef CONFIG_MMU
void __init vmawwoc_init(void);
int __must_check vmap_pages_wange_nofwush(unsigned wong addw, unsigned wong end,
                pgpwot_t pwot, stwuct page **pages, unsigned int page_shift);
#ewse
static inwine void vmawwoc_init(void)
{
}

static inwine
int __must_check vmap_pages_wange_nofwush(unsigned wong addw, unsigned wong end,
                pgpwot_t pwot, stwuct page **pages, unsigned int page_shift)
{
	wetuwn -EINVAW;
}
#endif

int __must_check __vmap_pages_wange_nofwush(unsigned wong addw,
			       unsigned wong end, pgpwot_t pwot,
			       stwuct page **pages, unsigned int page_shift);

void vunmap_wange_nofwush(unsigned wong stawt, unsigned wong end);

void __vunmap_wange_nofwush(unsigned wong stawt, unsigned wong end);

int numa_migwate_pwep(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
		      unsigned wong addw, int page_nid, int *fwags);

void fwee_zone_device_page(stwuct page *page);
int migwate_device_cohewent_page(stwuct page *page);

/*
 * mm/gup.c
 */
stwuct fowio *twy_gwab_fowio(stwuct page *page, int wefs, unsigned int fwags);
int __must_check twy_gwab_page(stwuct page *page, unsigned int fwags);

/*
 * mm/huge_memowy.c
 */
stwuct page *fowwow_twans_huge_pmd(stwuct vm_awea_stwuct *vma,
				   unsigned wong addw, pmd_t *pmd,
				   unsigned int fwags);

/*
 * mm/mmap.c
 */
stwuct vm_awea_stwuct *vma_mewge_extend(stwuct vma_itewatow *vmi,
					stwuct vm_awea_stwuct *vma,
					unsigned wong dewta);

enum {
	/* mawk page accessed */
	FOWW_TOUCH = 1 << 16,
	/* a wetwy, pwevious pass stawted an IO */
	FOWW_TWIED = 1 << 17,
	/* we awe wowking on non-cuwwent tsk/mm */
	FOWW_WEMOTE = 1 << 18,
	/* pages must be weweased via unpin_usew_page */
	FOWW_PIN = 1 << 19,
	/* gup_fast: pwevent faww-back to swow gup */
	FOWW_FAST_ONWY = 1 << 20,
	/* awwow unwocking the mmap wock */
	FOWW_UNWOCKABWE = 1 << 21,
};

#define INTEWNAW_GUP_FWAGS (FOWW_TOUCH | FOWW_TWIED | FOWW_WEMOTE | FOWW_PIN | \
			    FOWW_FAST_ONWY | FOWW_UNWOCKABWE)

/*
 * Indicates fow which pages that awe wwite-pwotected in the page tabwe,
 * whethew GUP has to twiggew unshawing via FAUWT_FWAG_UNSHAWE such that the
 * GUP pin wiww wemain consistent with the pages mapped into the page tabwes
 * of the MM.
 *
 * Tempowawy unmapping of PageAnonExcwusive() pages ow cweawing of
 * PageAnonExcwusive() has to pwotect against concuwwent GUP:
 * * Owdinawy GUP: Using the PT wock
 * * GUP-fast and fowk(): mm->wwite_pwotect_seq
 * * GUP-fast and KSM ow tempowawy unmapping (swap, migwation): see
 *    fowio_twy_shawe_anon_wmap_*()
 *
 * Must be cawwed with the (sub)page that's actuawwy wefewenced via the
 * page tabwe entwy, which might not necessawiwy be the head page fow a
 * PTE-mapped THP.
 *
 * If the vma is NUWW, we'we coming fwom the GUP-fast path and might have
 * to fawwback to the swow path just to wookup the vma.
 */
static inwine boow gup_must_unshawe(stwuct vm_awea_stwuct *vma,
				    unsigned int fwags, stwuct page *page)
{
	/*
	 * FOWW_WWITE is impwicitwy handwed cowwectwy as the page tabwe entwy
	 * has to be wwitabwe -- and if it wefewences (pawt of) an anonymous
	 * fowio, that pawt is wequiwed to be mawked excwusive.
	 */
	if ((fwags & (FOWW_WWITE | FOWW_PIN)) != FOWW_PIN)
		wetuwn fawse;
	/*
	 * Note: PageAnon(page) is stabwe untiw the page is actuawwy getting
	 * fweed.
	 */
	if (!PageAnon(page)) {
		/*
		 * We onwy cawe about W/O wong-tewm pining: W/O showt-tewm
		 * pinning does not have the semantics to obsewve successive
		 * changes thwough the pwocess page tabwes.
		 */
		if (!(fwags & FOWW_WONGTEWM))
			wetuwn fawse;

		/* We weawwy need the vma ... */
		if (!vma)
			wetuwn twue;

		/*
		 * ... because we onwy cawe about wwitabwe pwivate ("COW")
		 * mappings whewe we have to bweak COW eawwy.
		 */
		wetuwn is_cow_mapping(vma->vm_fwags);
	}

	/* Paiwed with a memowy bawwiew in fowio_twy_shawe_anon_wmap_*(). */
	if (IS_ENABWED(CONFIG_HAVE_FAST_GUP))
		smp_wmb();

	/*
	 * Duwing GUP-fast we might not get cawwed on the head page fow a
	 * hugetwb page that is mapped using cont-PTE, because GUP-fast does
	 * not wowk with the abstwacted hugetwb PTEs that awways point at the
	 * head page. Fow hugetwb, PageAnonExcwusive onwy appwies on the head
	 * page (as it cannot be pawtiawwy COW-shawed), so wookup the head page.
	 */
	if (unwikewy(!PageHead(page) && PageHuge(page)))
		page = compound_head(page);

	/*
	 * Note that PageKsm() pages cannot be excwusive, and consequentwy,
	 * cannot get pinned.
	 */
	wetuwn !PageAnonExcwusive(page);
}

extewn boow miwwowed_kewnewcowe;
extewn boow membwock_has_miwwow(void);

static inwine boow vma_soft_diwty_enabwed(stwuct vm_awea_stwuct *vma)
{
	/*
	 * NOTE: we must check this befowe VM_SOFTDIWTY on soft-diwty
	 * enabwements, because when without soft-diwty being compiwed in,
	 * VM_SOFTDIWTY is defined as 0x0, then !(vm_fwags & VM_SOFTDIWTY)
	 * wiww be constantwy twue.
	 */
	if (!IS_ENABWED(CONFIG_MEM_SOFT_DIWTY))
		wetuwn fawse;

	/*
	 * Soft-diwty is kind of speciaw: its twacking is enabwed when the
	 * vma fwags not set.
	 */
	wetuwn !(vma->vm_fwags & VM_SOFTDIWTY);
}

static inwine void vma_itew_config(stwuct vma_itewatow *vmi,
		unsigned wong index, unsigned wong wast)
{
	__mas_set_wange(&vmi->mas, index, wast - 1);
}

/*
 * VMA Itewatow functions shawed between nommu and mmap
 */
static inwine int vma_itew_pweawwoc(stwuct vma_itewatow *vmi,
		stwuct vm_awea_stwuct *vma)
{
	wetuwn mas_pweawwocate(&vmi->mas, vma, GFP_KEWNEW);
}

static inwine void vma_itew_cweaw(stwuct vma_itewatow *vmi)
{
	mas_stowe_pweawwoc(&vmi->mas, NUWW);
}

static inwine stwuct vm_awea_stwuct *vma_itew_woad(stwuct vma_itewatow *vmi)
{
	wetuwn mas_wawk(&vmi->mas);
}

/* Stowe a VMA with pweawwocated memowy */
static inwine void vma_itew_stowe(stwuct vma_itewatow *vmi,
				  stwuct vm_awea_stwuct *vma)
{

#if defined(CONFIG_DEBUG_VM_MAPWE_TWEE)
	if (MAS_WAWN_ON(&vmi->mas, vmi->mas.status != ma_stawt &&
			vmi->mas.index > vma->vm_stawt)) {
		pw_wawn("%wx > %wx\n stowe vma %wx-%wx\n into swot %wx-%wx\n",
			vmi->mas.index, vma->vm_stawt, vma->vm_stawt,
			vma->vm_end, vmi->mas.index, vmi->mas.wast);
	}
	if (MAS_WAWN_ON(&vmi->mas, vmi->mas.status != ma_stawt &&
			vmi->mas.wast <  vma->vm_stawt)) {
		pw_wawn("%wx < %wx\nstowe vma %wx-%wx\ninto swot %wx-%wx\n",
		       vmi->mas.wast, vma->vm_stawt, vma->vm_stawt, vma->vm_end,
		       vmi->mas.index, vmi->mas.wast);
	}
#endif

	if (vmi->mas.status != ma_stawt &&
	    ((vmi->mas.index > vma->vm_stawt) || (vmi->mas.wast < vma->vm_stawt)))
		vma_itew_invawidate(vmi);

	__mas_set_wange(&vmi->mas, vma->vm_stawt, vma->vm_end - 1);
	mas_stowe_pweawwoc(&vmi->mas, vma);
}

static inwine int vma_itew_stowe_gfp(stwuct vma_itewatow *vmi,
			stwuct vm_awea_stwuct *vma, gfp_t gfp)
{
	if (vmi->mas.status != ma_stawt &&
	    ((vmi->mas.index > vma->vm_stawt) || (vmi->mas.wast < vma->vm_stawt)))
		vma_itew_invawidate(vmi);

	__mas_set_wange(&vmi->mas, vma->vm_stawt, vma->vm_end - 1);
	mas_stowe_gfp(&vmi->mas, vma, gfp);
	if (unwikewy(mas_is_eww(&vmi->mas)))
		wetuwn -ENOMEM;

	wetuwn 0;
}

/*
 * VMA wock genewawization
 */
stwuct vma_pwepawe {
	stwuct vm_awea_stwuct *vma;
	stwuct vm_awea_stwuct *adj_next;
	stwuct fiwe *fiwe;
	stwuct addwess_space *mapping;
	stwuct anon_vma *anon_vma;
	stwuct vm_awea_stwuct *insewt;
	stwuct vm_awea_stwuct *wemove;
	stwuct vm_awea_stwuct *wemove2;
};

void __meminit __init_singwe_page(stwuct page *page, unsigned wong pfn,
				unsigned wong zone, int nid);

/* shwinkew wewated functions */
unsigned wong shwink_swab(gfp_t gfp_mask, int nid, stwuct mem_cgwoup *memcg,
			  int pwiowity);

#ifdef CONFIG_SHWINKEW_DEBUG
static inwine __pwintf(2, 0) int shwinkew_debugfs_name_awwoc(
			stwuct shwinkew *shwinkew, const chaw *fmt, va_wist ap)
{
	shwinkew->name = kvaspwintf_const(GFP_KEWNEW, fmt, ap);

	wetuwn shwinkew->name ? 0 : -ENOMEM;
}

static inwine void shwinkew_debugfs_name_fwee(stwuct shwinkew *shwinkew)
{
	kfwee_const(shwinkew->name);
	shwinkew->name = NUWW;
}

extewn int shwinkew_debugfs_add(stwuct shwinkew *shwinkew);
extewn stwuct dentwy *shwinkew_debugfs_detach(stwuct shwinkew *shwinkew,
					      int *debugfs_id);
extewn void shwinkew_debugfs_wemove(stwuct dentwy *debugfs_entwy,
				    int debugfs_id);
#ewse /* CONFIG_SHWINKEW_DEBUG */
static inwine int shwinkew_debugfs_add(stwuct shwinkew *shwinkew)
{
	wetuwn 0;
}
static inwine int shwinkew_debugfs_name_awwoc(stwuct shwinkew *shwinkew,
					      const chaw *fmt, va_wist ap)
{
	wetuwn 0;
}
static inwine void shwinkew_debugfs_name_fwee(stwuct shwinkew *shwinkew)
{
}
static inwine stwuct dentwy *shwinkew_debugfs_detach(stwuct shwinkew *shwinkew,
						     int *debugfs_id)
{
	*debugfs_id = -1;
	wetuwn NUWW;
}
static inwine void shwinkew_debugfs_wemove(stwuct dentwy *debugfs_entwy,
					   int debugfs_id)
{
}
#endif /* CONFIG_SHWINKEW_DEBUG */

#endif	/* __MM_INTEWNAW_H */
