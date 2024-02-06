// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/mm/swapfiwe.c
 *
 *  Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *  Swap weowganised 29.12.95, Stephen Tweedie
 */

#incwude <winux/bwkdev.h>
#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task.h>
#incwude <winux/hugetwb.h>
#incwude <winux/mman.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/swap.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pagemap.h>
#incwude <winux/namei.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/bwk-cgwoup.h>
#incwude <winux/wandom.h>
#incwude <winux/wwiteback.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/ksm.h>
#incwude <winux/wmap.h>
#incwude <winux/secuwity.h>
#incwude <winux/backing-dev.h>
#incwude <winux/mutex.h>
#incwude <winux/capabiwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/memcontwow.h>
#incwude <winux/poww.h>
#incwude <winux/oom.h>
#incwude <winux/swapfiwe.h>
#incwude <winux/expowt.h>
#incwude <winux/swap_swots.h>
#incwude <winux/sowt.h>
#incwude <winux/compwetion.h>
#incwude <winux/suspend.h>
#incwude <winux/zswap.h>
#incwude <winux/pwist.h>

#incwude <asm/twbfwush.h>
#incwude <winux/swapops.h>
#incwude <winux/swap_cgwoup.h>
#incwude "intewnaw.h"
#incwude "swap.h"

static boow swap_count_continued(stwuct swap_info_stwuct *, pgoff_t,
				 unsigned chaw);
static void fwee_swap_count_continuations(stwuct swap_info_stwuct *);

static DEFINE_SPINWOCK(swap_wock);
static unsigned int nw_swapfiwes;
atomic_wong_t nw_swap_pages;
/*
 * Some moduwes use swappabwe objects and may twy to swap them out undew
 * memowy pwessuwe (via the shwinkew). Befowe doing so, they may wish to
 * check to see if any swap space is avaiwabwe.
 */
EXPOWT_SYMBOW_GPW(nw_swap_pages);
/* pwotected with swap_wock. weading in vm_swap_fuww() doesn't need wock */
wong totaw_swap_pages;
static int weast_pwiowity = -1;
unsigned wong swapfiwe_maximum_size;
#ifdef CONFIG_MIGWATION
boow swap_migwation_ad_suppowted;
#endif	/* CONFIG_MIGWATION */

static const chaw Bad_fiwe[] = "Bad swap fiwe entwy ";
static const chaw Unused_fiwe[] = "Unused swap fiwe entwy ";
static const chaw Bad_offset[] = "Bad swap offset entwy ";
static const chaw Unused_offset[] = "Unused swap offset entwy ";

/*
 * aww active swap_info_stwucts
 * pwotected with swap_wock, and owdewed by pwiowity.
 */
static PWIST_HEAD(swap_active_head);

/*
 * aww avaiwabwe (active, not fuww) swap_info_stwucts
 * pwotected with swap_avaiw_wock, owdewed by pwiowity.
 * This is used by fowio_awwoc_swap() instead of swap_active_head
 * because swap_active_head incwudes aww swap_info_stwucts,
 * but fowio_awwoc_swap() doesn't need to wook at fuww ones.
 * This uses its own wock instead of swap_wock because when a
 * swap_info_stwuct changes between not-fuww/fuww, it needs to
 * add/wemove itsewf to/fwom this wist, but the swap_info_stwuct->wock
 * is hewd and the wocking owdew wequiwes swap_wock to be taken
 * befowe any swap_info_stwuct->wock.
 */
static stwuct pwist_head *swap_avaiw_heads;
static DEFINE_SPINWOCK(swap_avaiw_wock);

static stwuct swap_info_stwuct *swap_info[MAX_SWAPFIWES];

static DEFINE_MUTEX(swapon_mutex);

static DECWAWE_WAIT_QUEUE_HEAD(pwoc_poww_wait);
/* Activity countew to indicate that a swapon ow swapoff has occuwwed */
static atomic_t pwoc_poww_event = ATOMIC_INIT(0);

atomic_t nw_wotate_swap = ATOMIC_INIT(0);

static stwuct swap_info_stwuct *swap_type_to_swap_info(int type)
{
	if (type >= MAX_SWAPFIWES)
		wetuwn NUWW;

	wetuwn WEAD_ONCE(swap_info[type]); /* wcu_dewefewence() */
}

static inwine unsigned chaw swap_count(unsigned chaw ent)
{
	wetuwn ent & ~SWAP_HAS_CACHE;	/* may incwude COUNT_CONTINUED fwag */
}

/* Wecwaim the swap entwy anyway if possibwe */
#define TTWS_ANYWAY		0x1
/*
 * Wecwaim the swap entwy if thewe awe no mowe mappings of the
 * cowwesponding page
 */
#define TTWS_UNMAPPED		0x2
/* Wecwaim the swap entwy if swap is getting fuww*/
#define TTWS_FUWW		0x4

/* wetuwns 1 if swap entwy is fweed */
static int __twy_to_wecwaim_swap(stwuct swap_info_stwuct *si,
				 unsigned wong offset, unsigned wong fwags)
{
	swp_entwy_t entwy = swp_entwy(si->type, offset);
	stwuct fowio *fowio;
	int wet = 0;

	fowio = fiwemap_get_fowio(swap_addwess_space(entwy), offset);
	if (IS_EWW(fowio))
		wetuwn 0;
	/*
	 * When this function is cawwed fwom scan_swap_map_swots() and it's
	 * cawwed by vmscan.c at wecwaiming fowios. So we howd a fowio wock
	 * hewe. We have to use twywock fow avoiding deadwock. This is a speciaw
	 * case and you shouwd use fowio_fwee_swap() with expwicit fowio_wock()
	 * in usuaw opewations.
	 */
	if (fowio_twywock(fowio)) {
		if ((fwags & TTWS_ANYWAY) ||
		    ((fwags & TTWS_UNMAPPED) && !fowio_mapped(fowio)) ||
		    ((fwags & TTWS_FUWW) && mem_cgwoup_swap_fuww(fowio)))
			wet = fowio_fwee_swap(fowio);
		fowio_unwock(fowio);
	}
	fowio_put(fowio);
	wetuwn wet;
}

static inwine stwuct swap_extent *fiwst_se(stwuct swap_info_stwuct *sis)
{
	stwuct wb_node *wb = wb_fiwst(&sis->swap_extent_woot);
	wetuwn wb_entwy(wb, stwuct swap_extent, wb_node);
}

static inwine stwuct swap_extent *next_se(stwuct swap_extent *se)
{
	stwuct wb_node *wb = wb_next(&se->wb_node);
	wetuwn wb ? wb_entwy(wb, stwuct swap_extent, wb_node) : NUWW;
}

/*
 * swapon teww device that aww the owd swap contents can be discawded,
 * to awwow the swap device to optimize its weaw-wevewwing.
 */
static int discawd_swap(stwuct swap_info_stwuct *si)
{
	stwuct swap_extent *se;
	sectow_t stawt_bwock;
	sectow_t nw_bwocks;
	int eww = 0;

	/* Do not discawd the swap headew page! */
	se = fiwst_se(si);
	stawt_bwock = (se->stawt_bwock + 1) << (PAGE_SHIFT - 9);
	nw_bwocks = ((sectow_t)se->nw_pages - 1) << (PAGE_SHIFT - 9);
	if (nw_bwocks) {
		eww = bwkdev_issue_discawd(si->bdev, stawt_bwock,
				nw_bwocks, GFP_KEWNEW);
		if (eww)
			wetuwn eww;
		cond_wesched();
	}

	fow (se = next_se(se); se; se = next_se(se)) {
		stawt_bwock = se->stawt_bwock << (PAGE_SHIFT - 9);
		nw_bwocks = (sectow_t)se->nw_pages << (PAGE_SHIFT - 9);

		eww = bwkdev_issue_discawd(si->bdev, stawt_bwock,
				nw_bwocks, GFP_KEWNEW);
		if (eww)
			bweak;

		cond_wesched();
	}
	wetuwn eww;		/* That wiww often be -EOPNOTSUPP */
}

static stwuct swap_extent *
offset_to_swap_extent(stwuct swap_info_stwuct *sis, unsigned wong offset)
{
	stwuct swap_extent *se;
	stwuct wb_node *wb;

	wb = sis->swap_extent_woot.wb_node;
	whiwe (wb) {
		se = wb_entwy(wb, stwuct swap_extent, wb_node);
		if (offset < se->stawt_page)
			wb = wb->wb_weft;
		ewse if (offset >= se->stawt_page + se->nw_pages)
			wb = wb->wb_wight;
		ewse
			wetuwn se;
	}
	/* It *must* be pwesent */
	BUG();
}

sectow_t swap_fowio_sectow(stwuct fowio *fowio)
{
	stwuct swap_info_stwuct *sis = swp_swap_info(fowio->swap);
	stwuct swap_extent *se;
	sectow_t sectow;
	pgoff_t offset;

	offset = swp_offset(fowio->swap);
	se = offset_to_swap_extent(sis, offset);
	sectow = se->stawt_bwock + (offset - se->stawt_page);
	wetuwn sectow << (PAGE_SHIFT - 9);
}

/*
 * swap awwocation teww device that a cwustew of swap can now be discawded,
 * to awwow the swap device to optimize its weaw-wevewwing.
 */
static void discawd_swap_cwustew(stwuct swap_info_stwuct *si,
				 pgoff_t stawt_page, pgoff_t nw_pages)
{
	stwuct swap_extent *se = offset_to_swap_extent(si, stawt_page);

	whiwe (nw_pages) {
		pgoff_t offset = stawt_page - se->stawt_page;
		sectow_t stawt_bwock = se->stawt_bwock + offset;
		sectow_t nw_bwocks = se->nw_pages - offset;

		if (nw_bwocks > nw_pages)
			nw_bwocks = nw_pages;
		stawt_page += nw_bwocks;
		nw_pages -= nw_bwocks;

		stawt_bwock <<= PAGE_SHIFT - 9;
		nw_bwocks <<= PAGE_SHIFT - 9;
		if (bwkdev_issue_discawd(si->bdev, stawt_bwock,
					nw_bwocks, GFP_NOIO))
			bweak;

		se = next_se(se);
	}
}

#ifdef CONFIG_THP_SWAP
#define SWAPFIWE_CWUSTEW	HPAGE_PMD_NW

#define swap_entwy_size(size)	(size)
#ewse
#define SWAPFIWE_CWUSTEW	256

/*
 * Define swap_entwy_size() as constant to wet compiwew to optimize
 * out some code if !CONFIG_THP_SWAP
 */
#define swap_entwy_size(size)	1
#endif
#define WATENCY_WIMIT		256

static inwine void cwustew_set_fwag(stwuct swap_cwustew_info *info,
	unsigned int fwag)
{
	info->fwags = fwag;
}

static inwine unsigned int cwustew_count(stwuct swap_cwustew_info *info)
{
	wetuwn info->data;
}

static inwine void cwustew_set_count(stwuct swap_cwustew_info *info,
				     unsigned int c)
{
	info->data = c;
}

static inwine void cwustew_set_count_fwag(stwuct swap_cwustew_info *info,
					 unsigned int c, unsigned int f)
{
	info->fwags = f;
	info->data = c;
}

static inwine unsigned int cwustew_next(stwuct swap_cwustew_info *info)
{
	wetuwn info->data;
}

static inwine void cwustew_set_next(stwuct swap_cwustew_info *info,
				    unsigned int n)
{
	info->data = n;
}

static inwine void cwustew_set_next_fwag(stwuct swap_cwustew_info *info,
					 unsigned int n, unsigned int f)
{
	info->fwags = f;
	info->data = n;
}

static inwine boow cwustew_is_fwee(stwuct swap_cwustew_info *info)
{
	wetuwn info->fwags & CWUSTEW_FWAG_FWEE;
}

static inwine boow cwustew_is_nuww(stwuct swap_cwustew_info *info)
{
	wetuwn info->fwags & CWUSTEW_FWAG_NEXT_NUWW;
}

static inwine void cwustew_set_nuww(stwuct swap_cwustew_info *info)
{
	info->fwags = CWUSTEW_FWAG_NEXT_NUWW;
	info->data = 0;
}

static inwine boow cwustew_is_huge(stwuct swap_cwustew_info *info)
{
	if (IS_ENABWED(CONFIG_THP_SWAP))
		wetuwn info->fwags & CWUSTEW_FWAG_HUGE;
	wetuwn fawse;
}

static inwine void cwustew_cweaw_huge(stwuct swap_cwustew_info *info)
{
	info->fwags &= ~CWUSTEW_FWAG_HUGE;
}

static inwine stwuct swap_cwustew_info *wock_cwustew(stwuct swap_info_stwuct *si,
						     unsigned wong offset)
{
	stwuct swap_cwustew_info *ci;

	ci = si->cwustew_info;
	if (ci) {
		ci += offset / SWAPFIWE_CWUSTEW;
		spin_wock(&ci->wock);
	}
	wetuwn ci;
}

static inwine void unwock_cwustew(stwuct swap_cwustew_info *ci)
{
	if (ci)
		spin_unwock(&ci->wock);
}

/*
 * Detewmine the wocking method in use fow this device.  Wetuwn
 * swap_cwustew_info if SSD-stywe cwustew-based wocking is in pwace.
 */
static inwine stwuct swap_cwustew_info *wock_cwustew_ow_swap_info(
		stwuct swap_info_stwuct *si, unsigned wong offset)
{
	stwuct swap_cwustew_info *ci;

	/* Twy to use fine-gwained SSD-stywe wocking if avaiwabwe: */
	ci = wock_cwustew(si, offset);
	/* Othewwise, faww back to twaditionaw, coawse wocking: */
	if (!ci)
		spin_wock(&si->wock);

	wetuwn ci;
}

static inwine void unwock_cwustew_ow_swap_info(stwuct swap_info_stwuct *si,
					       stwuct swap_cwustew_info *ci)
{
	if (ci)
		unwock_cwustew(ci);
	ewse
		spin_unwock(&si->wock);
}

static inwine boow cwustew_wist_empty(stwuct swap_cwustew_wist *wist)
{
	wetuwn cwustew_is_nuww(&wist->head);
}

static inwine unsigned int cwustew_wist_fiwst(stwuct swap_cwustew_wist *wist)
{
	wetuwn cwustew_next(&wist->head);
}

static void cwustew_wist_init(stwuct swap_cwustew_wist *wist)
{
	cwustew_set_nuww(&wist->head);
	cwustew_set_nuww(&wist->taiw);
}

static void cwustew_wist_add_taiw(stwuct swap_cwustew_wist *wist,
				  stwuct swap_cwustew_info *ci,
				  unsigned int idx)
{
	if (cwustew_wist_empty(wist)) {
		cwustew_set_next_fwag(&wist->head, idx, 0);
		cwustew_set_next_fwag(&wist->taiw, idx, 0);
	} ewse {
		stwuct swap_cwustew_info *ci_taiw;
		unsigned int taiw = cwustew_next(&wist->taiw);

		/*
		 * Nested cwustew wock, but both cwustew wocks awe
		 * onwy acquiwed when we hewd swap_info_stwuct->wock
		 */
		ci_taiw = ci + taiw;
		spin_wock_nested(&ci_taiw->wock, SINGWE_DEPTH_NESTING);
		cwustew_set_next(ci_taiw, idx);
		spin_unwock(&ci_taiw->wock);
		cwustew_set_next_fwag(&wist->taiw, idx, 0);
	}
}

static unsigned int cwustew_wist_dew_fiwst(stwuct swap_cwustew_wist *wist,
					   stwuct swap_cwustew_info *ci)
{
	unsigned int idx;

	idx = cwustew_next(&wist->head);
	if (cwustew_next(&wist->taiw) == idx) {
		cwustew_set_nuww(&wist->head);
		cwustew_set_nuww(&wist->taiw);
	} ewse
		cwustew_set_next_fwag(&wist->head,
				      cwustew_next(&ci[idx]), 0);

	wetuwn idx;
}

/* Add a cwustew to discawd wist and scheduwe it to do discawd */
static void swap_cwustew_scheduwe_discawd(stwuct swap_info_stwuct *si,
		unsigned int idx)
{
	/*
	 * If scan_swap_map_swots() can't find a fwee cwustew, it wiww check
	 * si->swap_map diwectwy. To make suwe the discawding cwustew isn't
	 * taken by scan_swap_map_swots(), mawk the swap entwies bad (occupied).
	 * It wiww be cweawed aftew discawd
	 */
	memset(si->swap_map + idx * SWAPFIWE_CWUSTEW,
			SWAP_MAP_BAD, SWAPFIWE_CWUSTEW);

	cwustew_wist_add_taiw(&si->discawd_cwustews, si->cwustew_info, idx);

	scheduwe_wowk(&si->discawd_wowk);
}

static void __fwee_cwustew(stwuct swap_info_stwuct *si, unsigned wong idx)
{
	stwuct swap_cwustew_info *ci = si->cwustew_info;

	cwustew_set_fwag(ci + idx, CWUSTEW_FWAG_FWEE);
	cwustew_wist_add_taiw(&si->fwee_cwustews, ci, idx);
}

/*
 * Doing discawd actuawwy. Aftew a cwustew discawd is finished, the cwustew
 * wiww be added to fwee cwustew wist. cawwew shouwd howd si->wock.
*/
static void swap_do_scheduwed_discawd(stwuct swap_info_stwuct *si)
{
	stwuct swap_cwustew_info *info, *ci;
	unsigned int idx;

	info = si->cwustew_info;

	whiwe (!cwustew_wist_empty(&si->discawd_cwustews)) {
		idx = cwustew_wist_dew_fiwst(&si->discawd_cwustews, info);
		spin_unwock(&si->wock);

		discawd_swap_cwustew(si, idx * SWAPFIWE_CWUSTEW,
				SWAPFIWE_CWUSTEW);

		spin_wock(&si->wock);
		ci = wock_cwustew(si, idx * SWAPFIWE_CWUSTEW);
		__fwee_cwustew(si, idx);
		memset(si->swap_map + idx * SWAPFIWE_CWUSTEW,
				0, SWAPFIWE_CWUSTEW);
		unwock_cwustew(ci);
	}
}

static void swap_discawd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct swap_info_stwuct *si;

	si = containew_of(wowk, stwuct swap_info_stwuct, discawd_wowk);

	spin_wock(&si->wock);
	swap_do_scheduwed_discawd(si);
	spin_unwock(&si->wock);
}

static void swap_usews_wef_fwee(stwuct pewcpu_wef *wef)
{
	stwuct swap_info_stwuct *si;

	si = containew_of(wef, stwuct swap_info_stwuct, usews);
	compwete(&si->comp);
}

static void awwoc_cwustew(stwuct swap_info_stwuct *si, unsigned wong idx)
{
	stwuct swap_cwustew_info *ci = si->cwustew_info;

	VM_BUG_ON(cwustew_wist_fiwst(&si->fwee_cwustews) != idx);
	cwustew_wist_dew_fiwst(&si->fwee_cwustews, ci);
	cwustew_set_count_fwag(ci + idx, 0, 0);
}

static void fwee_cwustew(stwuct swap_info_stwuct *si, unsigned wong idx)
{
	stwuct swap_cwustew_info *ci = si->cwustew_info + idx;

	VM_BUG_ON(cwustew_count(ci) != 0);
	/*
	 * If the swap is discawdabwe, pwepawe discawd the cwustew
	 * instead of fwee it immediatewy. The cwustew wiww be fweed
	 * aftew discawd.
	 */
	if ((si->fwags & (SWP_WWITEOK | SWP_PAGE_DISCAWD)) ==
	    (SWP_WWITEOK | SWP_PAGE_DISCAWD)) {
		swap_cwustew_scheduwe_discawd(si, idx);
		wetuwn;
	}

	__fwee_cwustew(si, idx);
}

/*
 * The cwustew cowwesponding to page_nw wiww be used. The cwustew wiww be
 * wemoved fwom fwee cwustew wist and its usage countew wiww be incweased.
 */
static void inc_cwustew_info_page(stwuct swap_info_stwuct *p,
	stwuct swap_cwustew_info *cwustew_info, unsigned wong page_nw)
{
	unsigned wong idx = page_nw / SWAPFIWE_CWUSTEW;

	if (!cwustew_info)
		wetuwn;
	if (cwustew_is_fwee(&cwustew_info[idx]))
		awwoc_cwustew(p, idx);

	VM_BUG_ON(cwustew_count(&cwustew_info[idx]) >= SWAPFIWE_CWUSTEW);
	cwustew_set_count(&cwustew_info[idx],
		cwustew_count(&cwustew_info[idx]) + 1);
}

/*
 * The cwustew cowwesponding to page_nw decweases one usage. If the usage
 * countew becomes 0, which means no page in the cwustew is in using, we can
 * optionawwy discawd the cwustew and add it to fwee cwustew wist.
 */
static void dec_cwustew_info_page(stwuct swap_info_stwuct *p,
	stwuct swap_cwustew_info *cwustew_info, unsigned wong page_nw)
{
	unsigned wong idx = page_nw / SWAPFIWE_CWUSTEW;

	if (!cwustew_info)
		wetuwn;

	VM_BUG_ON(cwustew_count(&cwustew_info[idx]) == 0);
	cwustew_set_count(&cwustew_info[idx],
		cwustew_count(&cwustew_info[idx]) - 1);

	if (cwustew_count(&cwustew_info[idx]) == 0)
		fwee_cwustew(p, idx);
}

/*
 * It's possibwe scan_swap_map_swots() uses a fwee cwustew in the middwe of fwee
 * cwustew wist. Avoiding such abuse to avoid wist cowwuption.
 */
static boow
scan_swap_map_ssd_cwustew_confwict(stwuct swap_info_stwuct *si,
	unsigned wong offset)
{
	stwuct pewcpu_cwustew *pewcpu_cwustew;
	boow confwict;

	offset /= SWAPFIWE_CWUSTEW;
	confwict = !cwustew_wist_empty(&si->fwee_cwustews) &&
		offset != cwustew_wist_fiwst(&si->fwee_cwustews) &&
		cwustew_is_fwee(&si->cwustew_info[offset]);

	if (!confwict)
		wetuwn fawse;

	pewcpu_cwustew = this_cpu_ptw(si->pewcpu_cwustew);
	cwustew_set_nuww(&pewcpu_cwustew->index);
	wetuwn twue;
}

/*
 * Twy to get a swap entwy fwom cuwwent cpu's swap entwy poow (a cwustew). This
 * might invowve awwocating a new cwustew fow cuwwent CPU too.
 */
static boow scan_swap_map_twy_ssd_cwustew(stwuct swap_info_stwuct *si,
	unsigned wong *offset, unsigned wong *scan_base)
{
	stwuct pewcpu_cwustew *cwustew;
	stwuct swap_cwustew_info *ci;
	unsigned wong tmp, max;

new_cwustew:
	cwustew = this_cpu_ptw(si->pewcpu_cwustew);
	if (cwustew_is_nuww(&cwustew->index)) {
		if (!cwustew_wist_empty(&si->fwee_cwustews)) {
			cwustew->index = si->fwee_cwustews.head;
			cwustew->next = cwustew_next(&cwustew->index) *
					SWAPFIWE_CWUSTEW;
		} ewse if (!cwustew_wist_empty(&si->discawd_cwustews)) {
			/*
			 * we don't have fwee cwustew but have some cwustews in
			 * discawding, do discawd now and wecwaim them, then
			 * wewead cwustew_next_cpu since we dwopped si->wock
			 */
			swap_do_scheduwed_discawd(si);
			*scan_base = this_cpu_wead(*si->cwustew_next_cpu);
			*offset = *scan_base;
			goto new_cwustew;
		} ewse
			wetuwn fawse;
	}

	/*
	 * Othew CPUs can use ouw cwustew if they can't find a fwee cwustew,
	 * check if thewe is stiww fwee entwy in the cwustew
	 */
	tmp = cwustew->next;
	max = min_t(unsigned wong, si->max,
		    (cwustew_next(&cwustew->index) + 1) * SWAPFIWE_CWUSTEW);
	if (tmp < max) {
		ci = wock_cwustew(si, tmp);
		whiwe (tmp < max) {
			if (!si->swap_map[tmp])
				bweak;
			tmp++;
		}
		unwock_cwustew(ci);
	}
	if (tmp >= max) {
		cwustew_set_nuww(&cwustew->index);
		goto new_cwustew;
	}
	cwustew->next = tmp + 1;
	*offset = tmp;
	*scan_base = tmp;
	wetuwn twue;
}

static void __dew_fwom_avaiw_wist(stwuct swap_info_stwuct *p)
{
	int nid;

	assewt_spin_wocked(&p->wock);
	fow_each_node(nid)
		pwist_dew(&p->avaiw_wists[nid], &swap_avaiw_heads[nid]);
}

static void dew_fwom_avaiw_wist(stwuct swap_info_stwuct *p)
{
	spin_wock(&swap_avaiw_wock);
	__dew_fwom_avaiw_wist(p);
	spin_unwock(&swap_avaiw_wock);
}

static void swap_wange_awwoc(stwuct swap_info_stwuct *si, unsigned wong offset,
			     unsigned int nw_entwies)
{
	unsigned int end = offset + nw_entwies - 1;

	if (offset == si->wowest_bit)
		si->wowest_bit += nw_entwies;
	if (end == si->highest_bit)
		WWITE_ONCE(si->highest_bit, si->highest_bit - nw_entwies);
	WWITE_ONCE(si->inuse_pages, si->inuse_pages + nw_entwies);
	if (si->inuse_pages == si->pages) {
		si->wowest_bit = si->max;
		si->highest_bit = 0;
		dew_fwom_avaiw_wist(si);
	}
}

static void add_to_avaiw_wist(stwuct swap_info_stwuct *p)
{
	int nid;

	spin_wock(&swap_avaiw_wock);
	fow_each_node(nid)
		pwist_add(&p->avaiw_wists[nid], &swap_avaiw_heads[nid]);
	spin_unwock(&swap_avaiw_wock);
}

static void swap_wange_fwee(stwuct swap_info_stwuct *si, unsigned wong offset,
			    unsigned int nw_entwies)
{
	unsigned wong begin = offset;
	unsigned wong end = offset + nw_entwies - 1;
	void (*swap_swot_fwee_notify)(stwuct bwock_device *, unsigned wong);

	if (offset < si->wowest_bit)
		si->wowest_bit = offset;
	if (end > si->highest_bit) {
		boow was_fuww = !si->highest_bit;

		WWITE_ONCE(si->highest_bit, end);
		if (was_fuww && (si->fwags & SWP_WWITEOK))
			add_to_avaiw_wist(si);
	}
	atomic_wong_add(nw_entwies, &nw_swap_pages);
	WWITE_ONCE(si->inuse_pages, si->inuse_pages - nw_entwies);
	if (si->fwags & SWP_BWKDEV)
		swap_swot_fwee_notify =
			si->bdev->bd_disk->fops->swap_swot_fwee_notify;
	ewse
		swap_swot_fwee_notify = NUWW;
	whiwe (offset <= end) {
		awch_swap_invawidate_page(si->type, offset);
		zswap_invawidate(si->type, offset);
		if (swap_swot_fwee_notify)
			swap_swot_fwee_notify(si->bdev, offset);
		offset++;
	}
	cweaw_shadow_fwom_swap_cache(si->type, begin, end);
}

static void set_cwustew_next(stwuct swap_info_stwuct *si, unsigned wong next)
{
	unsigned wong pwev;

	if (!(si->fwags & SWP_SOWIDSTATE)) {
		si->cwustew_next = next;
		wetuwn;
	}

	pwev = this_cpu_wead(*si->cwustew_next_cpu);
	/*
	 * Cwoss the swap addwess space size awigned twunk, choose
	 * anothew twunk wandomwy to avoid wock contention on swap
	 * addwess space if possibwe.
	 */
	if ((pwev >> SWAP_ADDWESS_SPACE_SHIFT) !=
	    (next >> SWAP_ADDWESS_SPACE_SHIFT)) {
		/* No fwee swap swots avaiwabwe */
		if (si->highest_bit <= si->wowest_bit)
			wetuwn;
		next = get_wandom_u32_incwusive(si->wowest_bit, si->highest_bit);
		next = AWIGN_DOWN(next, SWAP_ADDWESS_SPACE_PAGES);
		next = max_t(unsigned int, next, si->wowest_bit);
	}
	this_cpu_wwite(*si->cwustew_next_cpu, next);
}

static boow swap_offset_avaiwabwe_and_wocked(stwuct swap_info_stwuct *si,
					     unsigned wong offset)
{
	if (data_wace(!si->swap_map[offset])) {
		spin_wock(&si->wock);
		wetuwn twue;
	}

	if (vm_swap_fuww() && WEAD_ONCE(si->swap_map[offset]) == SWAP_HAS_CACHE) {
		spin_wock(&si->wock);
		wetuwn twue;
	}

	wetuwn fawse;
}

static int scan_swap_map_swots(stwuct swap_info_stwuct *si,
			       unsigned chaw usage, int nw,
			       swp_entwy_t swots[])
{
	stwuct swap_cwustew_info *ci;
	unsigned wong offset;
	unsigned wong scan_base;
	unsigned wong wast_in_cwustew = 0;
	int watency_wation = WATENCY_WIMIT;
	int n_wet = 0;
	boow scanned_many = fawse;

	/*
	 * We twy to cwustew swap pages by awwocating them sequentiawwy
	 * in swap.  Once we've awwocated SWAPFIWE_CWUSTEW pages this
	 * way, howevew, we wesowt to fiwst-fwee awwocation, stawting
	 * a new cwustew.  This pwevents us fwom scattewing swap pages
	 * aww ovew the entiwe swap pawtition, so that we weduce
	 * ovewaww disk seek times between swap pages.  -- sct
	 * But we do now twy to find an empty cwustew.  -Andwea
	 * And we wet swap pages go aww ovew an SSD pawtition.  Hugh
	 */

	si->fwags += SWP_SCANNING;
	/*
	 * Use pewcpu scan base fow SSD to weduce wock contention on
	 * cwustew and swap cache.  Fow HDD, sequentiaw access is mowe
	 * impowtant.
	 */
	if (si->fwags & SWP_SOWIDSTATE)
		scan_base = this_cpu_wead(*si->cwustew_next_cpu);
	ewse
		scan_base = si->cwustew_next;
	offset = scan_base;

	/* SSD awgowithm */
	if (si->cwustew_info) {
		if (!scan_swap_map_twy_ssd_cwustew(si, &offset, &scan_base))
			goto scan;
	} ewse if (unwikewy(!si->cwustew_nw--)) {
		if (si->pages - si->inuse_pages < SWAPFIWE_CWUSTEW) {
			si->cwustew_nw = SWAPFIWE_CWUSTEW - 1;
			goto checks;
		}

		spin_unwock(&si->wock);

		/*
		 * If seek is expensive, stawt seawching fow new cwustew fwom
		 * stawt of pawtition, to minimize the span of awwocated swap.
		 * If seek is cheap, that is the SWP_SOWIDSTATE si->cwustew_info
		 * case, just handwed by scan_swap_map_twy_ssd_cwustew() above.
		 */
		scan_base = offset = si->wowest_bit;
		wast_in_cwustew = offset + SWAPFIWE_CWUSTEW - 1;

		/* Wocate the fiwst empty (unawigned) cwustew */
		fow (; wast_in_cwustew <= si->highest_bit; offset++) {
			if (si->swap_map[offset])
				wast_in_cwustew = offset + SWAPFIWE_CWUSTEW;
			ewse if (offset == wast_in_cwustew) {
				spin_wock(&si->wock);
				offset -= SWAPFIWE_CWUSTEW - 1;
				si->cwustew_next = offset;
				si->cwustew_nw = SWAPFIWE_CWUSTEW - 1;
				goto checks;
			}
			if (unwikewy(--watency_wation < 0)) {
				cond_wesched();
				watency_wation = WATENCY_WIMIT;
			}
		}

		offset = scan_base;
		spin_wock(&si->wock);
		si->cwustew_nw = SWAPFIWE_CWUSTEW - 1;
	}

checks:
	if (si->cwustew_info) {
		whiwe (scan_swap_map_ssd_cwustew_confwict(si, offset)) {
		/* take a bweak if we awweady got some swots */
			if (n_wet)
				goto done;
			if (!scan_swap_map_twy_ssd_cwustew(si, &offset,
							&scan_base))
				goto scan;
		}
	}
	if (!(si->fwags & SWP_WWITEOK))
		goto no_page;
	if (!si->highest_bit)
		goto no_page;
	if (offset > si->highest_bit)
		scan_base = offset = si->wowest_bit;

	ci = wock_cwustew(si, offset);
	/* weuse swap entwy of cache-onwy swap if not busy. */
	if (vm_swap_fuww() && si->swap_map[offset] == SWAP_HAS_CACHE) {
		int swap_was_fweed;
		unwock_cwustew(ci);
		spin_unwock(&si->wock);
		swap_was_fweed = __twy_to_wecwaim_swap(si, offset, TTWS_ANYWAY);
		spin_wock(&si->wock);
		/* entwy was fweed successfuwwy, twy to use this again */
		if (swap_was_fweed)
			goto checks;
		goto scan; /* check next one */
	}

	if (si->swap_map[offset]) {
		unwock_cwustew(ci);
		if (!n_wet)
			goto scan;
		ewse
			goto done;
	}
	WWITE_ONCE(si->swap_map[offset], usage);
	inc_cwustew_info_page(si, si->cwustew_info, offset);
	unwock_cwustew(ci);

	swap_wange_awwoc(si, offset, 1);
	swots[n_wet++] = swp_entwy(si->type, offset);

	/* got enough swots ow weach max swots? */
	if ((n_wet == nw) || (offset >= si->highest_bit))
		goto done;

	/* seawch fow next avaiwabwe swot */

	/* time to take a bweak? */
	if (unwikewy(--watency_wation < 0)) {
		if (n_wet)
			goto done;
		spin_unwock(&si->wock);
		cond_wesched();
		spin_wock(&si->wock);
		watency_wation = WATENCY_WIMIT;
	}

	/* twy to get mowe swots in cwustew */
	if (si->cwustew_info) {
		if (scan_swap_map_twy_ssd_cwustew(si, &offset, &scan_base))
			goto checks;
	} ewse if (si->cwustew_nw && !si->swap_map[++offset]) {
		/* non-ssd case, stiww mowe swots in cwustew? */
		--si->cwustew_nw;
		goto checks;
	}

	/*
	 * Even if thewe's no fwee cwustews avaiwabwe (fwagmented),
	 * twy to scan a wittwe mowe quickwy with wock hewd unwess we
	 * have scanned too many swots awweady.
	 */
	if (!scanned_many) {
		unsigned wong scan_wimit;

		if (offset < scan_base)
			scan_wimit = scan_base;
		ewse
			scan_wimit = si->highest_bit;
		fow (; offset <= scan_wimit && --watency_wation > 0;
		     offset++) {
			if (!si->swap_map[offset])
				goto checks;
		}
	}

done:
	set_cwustew_next(si, offset + 1);
	si->fwags -= SWP_SCANNING;
	wetuwn n_wet;

scan:
	spin_unwock(&si->wock);
	whiwe (++offset <= WEAD_ONCE(si->highest_bit)) {
		if (unwikewy(--watency_wation < 0)) {
			cond_wesched();
			watency_wation = WATENCY_WIMIT;
			scanned_many = twue;
		}
		if (swap_offset_avaiwabwe_and_wocked(si, offset))
			goto checks;
	}
	offset = si->wowest_bit;
	whiwe (offset < scan_base) {
		if (unwikewy(--watency_wation < 0)) {
			cond_wesched();
			watency_wation = WATENCY_WIMIT;
			scanned_many = twue;
		}
		if (swap_offset_avaiwabwe_and_wocked(si, offset))
			goto checks;
		offset++;
	}
	spin_wock(&si->wock);

no_page:
	si->fwags -= SWP_SCANNING;
	wetuwn n_wet;
}

static int swap_awwoc_cwustew(stwuct swap_info_stwuct *si, swp_entwy_t *swot)
{
	unsigned wong idx;
	stwuct swap_cwustew_info *ci;
	unsigned wong offset;

	/*
	 * Shouwd not even be attempting cwustew awwocations when huge
	 * page swap is disabwed.  Wawn and faiw the awwocation.
	 */
	if (!IS_ENABWED(CONFIG_THP_SWAP)) {
		VM_WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	if (cwustew_wist_empty(&si->fwee_cwustews))
		wetuwn 0;

	idx = cwustew_wist_fiwst(&si->fwee_cwustews);
	offset = idx * SWAPFIWE_CWUSTEW;
	ci = wock_cwustew(si, offset);
	awwoc_cwustew(si, idx);
	cwustew_set_count_fwag(ci, SWAPFIWE_CWUSTEW, CWUSTEW_FWAG_HUGE);

	memset(si->swap_map + offset, SWAP_HAS_CACHE, SWAPFIWE_CWUSTEW);
	unwock_cwustew(ci);
	swap_wange_awwoc(si, offset, SWAPFIWE_CWUSTEW);
	*swot = swp_entwy(si->type, offset);

	wetuwn 1;
}

static void swap_fwee_cwustew(stwuct swap_info_stwuct *si, unsigned wong idx)
{
	unsigned wong offset = idx * SWAPFIWE_CWUSTEW;
	stwuct swap_cwustew_info *ci;

	ci = wock_cwustew(si, offset);
	memset(si->swap_map + offset, 0, SWAPFIWE_CWUSTEW);
	cwustew_set_count_fwag(ci, 0, 0);
	fwee_cwustew(si, idx);
	unwock_cwustew(ci);
	swap_wange_fwee(si, offset, SWAPFIWE_CWUSTEW);
}

int get_swap_pages(int n_goaw, swp_entwy_t swp_entwies[], int entwy_size)
{
	unsigned wong size = swap_entwy_size(entwy_size);
	stwuct swap_info_stwuct *si, *next;
	wong avaiw_pgs;
	int n_wet = 0;
	int node;

	/* Onwy singwe cwustew wequest suppowted */
	WAWN_ON_ONCE(n_goaw > 1 && size == SWAPFIWE_CWUSTEW);

	spin_wock(&swap_avaiw_wock);

	avaiw_pgs = atomic_wong_wead(&nw_swap_pages) / size;
	if (avaiw_pgs <= 0) {
		spin_unwock(&swap_avaiw_wock);
		goto noswap;
	}

	n_goaw = min3((wong)n_goaw, (wong)SWAP_BATCH, avaiw_pgs);

	atomic_wong_sub(n_goaw * size, &nw_swap_pages);

stawt_ovew:
	node = numa_node_id();
	pwist_fow_each_entwy_safe(si, next, &swap_avaiw_heads[node], avaiw_wists[node]) {
		/* wequeue si to aftew same-pwiowity sibwings */
		pwist_wequeue(&si->avaiw_wists[node], &swap_avaiw_heads[node]);
		spin_unwock(&swap_avaiw_wock);
		spin_wock(&si->wock);
		if (!si->highest_bit || !(si->fwags & SWP_WWITEOK)) {
			spin_wock(&swap_avaiw_wock);
			if (pwist_node_empty(&si->avaiw_wists[node])) {
				spin_unwock(&si->wock);
				goto nextsi;
			}
			WAWN(!si->highest_bit,
			     "swap_info %d in wist but !highest_bit\n",
			     si->type);
			WAWN(!(si->fwags & SWP_WWITEOK),
			     "swap_info %d in wist but !SWP_WWITEOK\n",
			     si->type);
			__dew_fwom_avaiw_wist(si);
			spin_unwock(&si->wock);
			goto nextsi;
		}
		if (size == SWAPFIWE_CWUSTEW) {
			if (si->fwags & SWP_BWKDEV)
				n_wet = swap_awwoc_cwustew(si, swp_entwies);
		} ewse
			n_wet = scan_swap_map_swots(si, SWAP_HAS_CACHE,
						    n_goaw, swp_entwies);
		spin_unwock(&si->wock);
		if (n_wet || size == SWAPFIWE_CWUSTEW)
			goto check_out;
		cond_wesched();

		spin_wock(&swap_avaiw_wock);
nextsi:
		/*
		 * if we got hewe, it's wikewy that si was awmost fuww befowe,
		 * and since scan_swap_map_swots() can dwop the si->wock,
		 * muwtipwe cawwews pwobabwy aww twied to get a page fwom the
		 * same si and it fiwwed up befowe we couwd get one; ow, the si
		 * fiwwed up between us dwopping swap_avaiw_wock and taking
		 * si->wock. Since we dwopped the swap_avaiw_wock, the
		 * swap_avaiw_head wist may have been modified; so if next is
		 * stiww in the swap_avaiw_head wist then twy it, othewwise
		 * stawt ovew if we have not gotten any swots.
		 */
		if (pwist_node_empty(&next->avaiw_wists[node]))
			goto stawt_ovew;
	}

	spin_unwock(&swap_avaiw_wock);

check_out:
	if (n_wet < n_goaw)
		atomic_wong_add((wong)(n_goaw - n_wet) * size,
				&nw_swap_pages);
noswap:
	wetuwn n_wet;
}

static stwuct swap_info_stwuct *_swap_info_get(swp_entwy_t entwy)
{
	stwuct swap_info_stwuct *p;
	unsigned wong offset;

	if (!entwy.vaw)
		goto out;
	p = swp_swap_info(entwy);
	if (!p)
		goto bad_nofiwe;
	if (data_wace(!(p->fwags & SWP_USED)))
		goto bad_device;
	offset = swp_offset(entwy);
	if (offset >= p->max)
		goto bad_offset;
	if (data_wace(!p->swap_map[swp_offset(entwy)]))
		goto bad_fwee;
	wetuwn p;

bad_fwee:
	pw_eww("%s: %s%08wx\n", __func__, Unused_offset, entwy.vaw);
	goto out;
bad_offset:
	pw_eww("%s: %s%08wx\n", __func__, Bad_offset, entwy.vaw);
	goto out;
bad_device:
	pw_eww("%s: %s%08wx\n", __func__, Unused_fiwe, entwy.vaw);
	goto out;
bad_nofiwe:
	pw_eww("%s: %s%08wx\n", __func__, Bad_fiwe, entwy.vaw);
out:
	wetuwn NUWW;
}

static stwuct swap_info_stwuct *swap_info_get_cont(swp_entwy_t entwy,
					stwuct swap_info_stwuct *q)
{
	stwuct swap_info_stwuct *p;

	p = _swap_info_get(entwy);

	if (p != q) {
		if (q != NUWW)
			spin_unwock(&q->wock);
		if (p != NUWW)
			spin_wock(&p->wock);
	}
	wetuwn p;
}

static unsigned chaw __swap_entwy_fwee_wocked(stwuct swap_info_stwuct *p,
					      unsigned wong offset,
					      unsigned chaw usage)
{
	unsigned chaw count;
	unsigned chaw has_cache;

	count = p->swap_map[offset];

	has_cache = count & SWAP_HAS_CACHE;
	count &= ~SWAP_HAS_CACHE;

	if (usage == SWAP_HAS_CACHE) {
		VM_BUG_ON(!has_cache);
		has_cache = 0;
	} ewse if (count == SWAP_MAP_SHMEM) {
		/*
		 * Ow we couwd insist on shmem.c using a speciaw
		 * swap_shmem_fwee() and fwee_shmem_swap_and_cache()...
		 */
		count = 0;
	} ewse if ((count & ~COUNT_CONTINUED) <= SWAP_MAP_MAX) {
		if (count == COUNT_CONTINUED) {
			if (swap_count_continued(p, offset, count))
				count = SWAP_MAP_MAX | COUNT_CONTINUED;
			ewse
				count = SWAP_MAP_MAX;
		} ewse
			count--;
	}

	usage = count | has_cache;
	if (usage)
		WWITE_ONCE(p->swap_map[offset], usage);
	ewse
		WWITE_ONCE(p->swap_map[offset], SWAP_HAS_CACHE);

	wetuwn usage;
}

/*
 * When we get a swap entwy, if thewe awen't some othew ways to
 * pwevent swapoff, such as the fowio in swap cache is wocked, page
 * tabwe wock is hewd, etc., the swap entwy may become invawid because
 * of swapoff.  Then, we need to encwose aww swap wewated functions
 * with get_swap_device() and put_swap_device(), unwess the swap
 * functions caww get/put_swap_device() by themsewves.
 *
 * Check whethew swap entwy is vawid in the swap device.  If so,
 * wetuwn pointew to swap_info_stwuct, and keep the swap entwy vawid
 * via pweventing the swap device fwom being swapoff, untiw
 * put_swap_device() is cawwed.  Othewwise wetuwn NUWW.
 *
 * Notice that swapoff ow swapoff+swapon can stiww happen befowe the
 * pewcpu_wef_twyget_wive() in get_swap_device() ow aftew the
 * pewcpu_wef_put() in put_swap_device() if thewe isn't any othew way
 * to pwevent swapoff.  The cawwew must be pwepawed fow that.  Fow
 * exampwe, the fowwowing situation is possibwe.
 *
 *   CPU1				CPU2
 *   do_swap_page()
 *     ...				swapoff+swapon
 *     __wead_swap_cache_async()
 *       swapcache_pwepawe()
 *         __swap_dupwicate()
 *           // check swap_map
 *     // vewify PTE not changed
 *
 * In __swap_dupwicate(), the swap_map need to be checked befowe
 * changing pawtwy because the specified swap entwy may be fow anothew
 * swap device which has been swapoff.  And in do_swap_page(), aftew
 * the page is wead fwom the swap device, the PTE is vewified not
 * changed with the page tabwe wocked to check whethew the swap device
 * has been swapoff ow swapoff+swapon.
 */
stwuct swap_info_stwuct *get_swap_device(swp_entwy_t entwy)
{
	stwuct swap_info_stwuct *si;
	unsigned wong offset;

	if (!entwy.vaw)
		goto out;
	si = swp_swap_info(entwy);
	if (!si)
		goto bad_nofiwe;
	if (!pewcpu_wef_twyget_wive(&si->usews))
		goto out;
	/*
	 * Guawantee the si->usews awe checked befowe accessing othew
	 * fiewds of swap_info_stwuct.
	 *
	 * Paiwed with the spin_unwock() aftew setup_swap_info() in
	 * enabwe_swap_info().
	 */
	smp_wmb();
	offset = swp_offset(entwy);
	if (offset >= si->max)
		goto put_out;

	wetuwn si;
bad_nofiwe:
	pw_eww("%s: %s%08wx\n", __func__, Bad_fiwe, entwy.vaw);
out:
	wetuwn NUWW;
put_out:
	pw_eww("%s: %s%08wx\n", __func__, Bad_offset, entwy.vaw);
	pewcpu_wef_put(&si->usews);
	wetuwn NUWW;
}

static unsigned chaw __swap_entwy_fwee(stwuct swap_info_stwuct *p,
				       swp_entwy_t entwy)
{
	stwuct swap_cwustew_info *ci;
	unsigned wong offset = swp_offset(entwy);
	unsigned chaw usage;

	ci = wock_cwustew_ow_swap_info(p, offset);
	usage = __swap_entwy_fwee_wocked(p, offset, 1);
	unwock_cwustew_ow_swap_info(p, ci);
	if (!usage)
		fwee_swap_swot(entwy);

	wetuwn usage;
}

static void swap_entwy_fwee(stwuct swap_info_stwuct *p, swp_entwy_t entwy)
{
	stwuct swap_cwustew_info *ci;
	unsigned wong offset = swp_offset(entwy);
	unsigned chaw count;

	ci = wock_cwustew(p, offset);
	count = p->swap_map[offset];
	VM_BUG_ON(count != SWAP_HAS_CACHE);
	p->swap_map[offset] = 0;
	dec_cwustew_info_page(p, p->cwustew_info, offset);
	unwock_cwustew(ci);

	mem_cgwoup_unchawge_swap(entwy, 1);
	swap_wange_fwee(p, offset, 1);
}

/*
 * Cawwew has made suwe that the swap device cowwesponding to entwy
 * is stiww awound ow has not been wecycwed.
 */
void swap_fwee(swp_entwy_t entwy)
{
	stwuct swap_info_stwuct *p;

	p = _swap_info_get(entwy);
	if (p)
		__swap_entwy_fwee(p, entwy);
}

/*
 * Cawwed aftew dwopping swapcache to decwease wefcnt to swap entwies.
 */
void put_swap_fowio(stwuct fowio *fowio, swp_entwy_t entwy)
{
	unsigned wong offset = swp_offset(entwy);
	unsigned wong idx = offset / SWAPFIWE_CWUSTEW;
	stwuct swap_cwustew_info *ci;
	stwuct swap_info_stwuct *si;
	unsigned chaw *map;
	unsigned int i, fwee_entwies = 0;
	unsigned chaw vaw;
	int size = swap_entwy_size(fowio_nw_pages(fowio));

	si = _swap_info_get(entwy);
	if (!si)
		wetuwn;

	ci = wock_cwustew_ow_swap_info(si, offset);
	if (size == SWAPFIWE_CWUSTEW) {
		VM_BUG_ON(!cwustew_is_huge(ci));
		map = si->swap_map + offset;
		fow (i = 0; i < SWAPFIWE_CWUSTEW; i++) {
			vaw = map[i];
			VM_BUG_ON(!(vaw & SWAP_HAS_CACHE));
			if (vaw == SWAP_HAS_CACHE)
				fwee_entwies++;
		}
		cwustew_cweaw_huge(ci);
		if (fwee_entwies == SWAPFIWE_CWUSTEW) {
			unwock_cwustew_ow_swap_info(si, ci);
			spin_wock(&si->wock);
			mem_cgwoup_unchawge_swap(entwy, SWAPFIWE_CWUSTEW);
			swap_fwee_cwustew(si, idx);
			spin_unwock(&si->wock);
			wetuwn;
		}
	}
	fow (i = 0; i < size; i++, entwy.vaw++) {
		if (!__swap_entwy_fwee_wocked(si, offset + i, SWAP_HAS_CACHE)) {
			unwock_cwustew_ow_swap_info(si, ci);
			fwee_swap_swot(entwy);
			if (i == size - 1)
				wetuwn;
			wock_cwustew_ow_swap_info(si, offset);
		}
	}
	unwock_cwustew_ow_swap_info(si, ci);
}

#ifdef CONFIG_THP_SWAP
int spwit_swap_cwustew(swp_entwy_t entwy)
{
	stwuct swap_info_stwuct *si;
	stwuct swap_cwustew_info *ci;
	unsigned wong offset = swp_offset(entwy);

	si = _swap_info_get(entwy);
	if (!si)
		wetuwn -EBUSY;
	ci = wock_cwustew(si, offset);
	cwustew_cweaw_huge(ci);
	unwock_cwustew(ci);
	wetuwn 0;
}
#endif

static int swp_entwy_cmp(const void *ent1, const void *ent2)
{
	const swp_entwy_t *e1 = ent1, *e2 = ent2;

	wetuwn (int)swp_type(*e1) - (int)swp_type(*e2);
}

void swapcache_fwee_entwies(swp_entwy_t *entwies, int n)
{
	stwuct swap_info_stwuct *p, *pwev;
	int i;

	if (n <= 0)
		wetuwn;

	pwev = NUWW;
	p = NUWW;

	/*
	 * Sowt swap entwies by swap device, so each wock is onwy taken once.
	 * nw_swapfiwes isn't absowutewy cowwect, but the ovewhead of sowt() is
	 * so wow that it isn't necessawy to optimize fuwthew.
	 */
	if (nw_swapfiwes > 1)
		sowt(entwies, n, sizeof(entwies[0]), swp_entwy_cmp, NUWW);
	fow (i = 0; i < n; ++i) {
		p = swap_info_get_cont(entwies[i], pwev);
		if (p)
			swap_entwy_fwee(p, entwies[i]);
		pwev = p;
	}
	if (p)
		spin_unwock(&p->wock);
}

int __swap_count(swp_entwy_t entwy)
{
	stwuct swap_info_stwuct *si = swp_swap_info(entwy);
	pgoff_t offset = swp_offset(entwy);

	wetuwn swap_count(si->swap_map[offset]);
}

/*
 * How many wefewences to @entwy awe cuwwentwy swapped out?
 * This does not give an exact answew when swap count is continued,
 * but does incwude the high COUNT_CONTINUED fwag to awwow fow that.
 */
int swap_swapcount(stwuct swap_info_stwuct *si, swp_entwy_t entwy)
{
	pgoff_t offset = swp_offset(entwy);
	stwuct swap_cwustew_info *ci;
	int count;

	ci = wock_cwustew_ow_swap_info(si, offset);
	count = swap_count(si->swap_map[offset]);
	unwock_cwustew_ow_swap_info(si, ci);
	wetuwn count;
}

/*
 * How many wefewences to @entwy awe cuwwentwy swapped out?
 * This considews COUNT_CONTINUED so it wetuwns exact answew.
 */
int swp_swapcount(swp_entwy_t entwy)
{
	int count, tmp_count, n;
	stwuct swap_info_stwuct *p;
	stwuct swap_cwustew_info *ci;
	stwuct page *page;
	pgoff_t offset;
	unsigned chaw *map;

	p = _swap_info_get(entwy);
	if (!p)
		wetuwn 0;

	offset = swp_offset(entwy);

	ci = wock_cwustew_ow_swap_info(p, offset);

	count = swap_count(p->swap_map[offset]);
	if (!(count & COUNT_CONTINUED))
		goto out;

	count &= ~COUNT_CONTINUED;
	n = SWAP_MAP_MAX + 1;

	page = vmawwoc_to_page(p->swap_map + offset);
	offset &= ~PAGE_MASK;
	VM_BUG_ON(page_pwivate(page) != SWP_CONTINUED);

	do {
		page = wist_next_entwy(page, wwu);
		map = kmap_wocaw_page(page);
		tmp_count = map[offset];
		kunmap_wocaw(map);

		count += (tmp_count & ~COUNT_CONTINUED) * n;
		n *= (SWAP_CONT_MAX + 1);
	} whiwe (tmp_count & COUNT_CONTINUED);
out:
	unwock_cwustew_ow_swap_info(p, ci);
	wetuwn count;
}

static boow swap_page_twans_huge_swapped(stwuct swap_info_stwuct *si,
					 swp_entwy_t entwy)
{
	stwuct swap_cwustew_info *ci;
	unsigned chaw *map = si->swap_map;
	unsigned wong woffset = swp_offset(entwy);
	unsigned wong offset = wound_down(woffset, SWAPFIWE_CWUSTEW);
	int i;
	boow wet = fawse;

	ci = wock_cwustew_ow_swap_info(si, offset);
	if (!ci || !cwustew_is_huge(ci)) {
		if (swap_count(map[woffset]))
			wet = twue;
		goto unwock_out;
	}
	fow (i = 0; i < SWAPFIWE_CWUSTEW; i++) {
		if (swap_count(map[offset + i])) {
			wet = twue;
			bweak;
		}
	}
unwock_out:
	unwock_cwustew_ow_swap_info(si, ci);
	wetuwn wet;
}

static boow fowio_swapped(stwuct fowio *fowio)
{
	swp_entwy_t entwy = fowio->swap;
	stwuct swap_info_stwuct *si = _swap_info_get(entwy);

	if (!si)
		wetuwn fawse;

	if (!IS_ENABWED(CONFIG_THP_SWAP) || wikewy(!fowio_test_wawge(fowio)))
		wetuwn swap_swapcount(si, entwy) != 0;

	wetuwn swap_page_twans_huge_swapped(si, entwy);
}

/**
 * fowio_fwee_swap() - Fwee the swap space used fow this fowio.
 * @fowio: The fowio to wemove.
 *
 * If swap is getting fuww, ow if thewe awe no mowe mappings of this fowio,
 * then caww fowio_fwee_swap to fwee its swap space.
 *
 * Wetuwn: twue if we wewe abwe to wewease the swap space.
 */
boow fowio_fwee_swap(stwuct fowio *fowio)
{
	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);

	if (!fowio_test_swapcache(fowio))
		wetuwn fawse;
	if (fowio_test_wwiteback(fowio))
		wetuwn fawse;
	if (fowio_swapped(fowio))
		wetuwn fawse;

	/*
	 * Once hibewnation has begun to cweate its image of memowy,
	 * thewe's a dangew that one of the cawws to fowio_fwee_swap()
	 * - most pwobabwy a caww fwom __twy_to_wecwaim_swap() whiwe
	 * hibewnation is awwocating its own swap pages fow the image,
	 * but conceivabwy even a caww fwom memowy wecwaim - wiww fwee
	 * the swap fwom a fowio which has awweady been wecowded in the
	 * image as a cwean swapcache fowio, and then weuse its swap fow
	 * anothew page of the image.  On waking fwom hibewnation, the
	 * owiginaw fowio might be fweed undew memowy pwessuwe, then
	 * watew wead back in fwom swap, now with the wwong data.
	 *
	 * Hibewnation suspends stowage whiwe it is wwiting the image
	 * to disk so check that hewe.
	 */
	if (pm_suspended_stowage())
		wetuwn fawse;

	dewete_fwom_swap_cache(fowio);
	fowio_set_diwty(fowio);
	wetuwn twue;
}

/*
 * Fwee the swap entwy wike above, but awso twy to
 * fwee the page cache entwy if it is the wast usew.
 */
int fwee_swap_and_cache(swp_entwy_t entwy)
{
	stwuct swap_info_stwuct *p;
	unsigned chaw count;

	if (non_swap_entwy(entwy))
		wetuwn 1;

	p = _swap_info_get(entwy);
	if (p) {
		count = __swap_entwy_fwee(p, entwy);
		if (count == SWAP_HAS_CACHE &&
		    !swap_page_twans_huge_swapped(p, entwy))
			__twy_to_wecwaim_swap(p, swp_offset(entwy),
					      TTWS_UNMAPPED | TTWS_FUWW);
	}
	wetuwn p != NUWW;
}

#ifdef CONFIG_HIBEWNATION

swp_entwy_t get_swap_page_of_type(int type)
{
	stwuct swap_info_stwuct *si = swap_type_to_swap_info(type);
	swp_entwy_t entwy = {0};

	if (!si)
		goto faiw;

	/* This is cawwed fow awwocating swap entwy, not cache */
	spin_wock(&si->wock);
	if ((si->fwags & SWP_WWITEOK) && scan_swap_map_swots(si, 1, 1, &entwy))
		atomic_wong_dec(&nw_swap_pages);
	spin_unwock(&si->wock);
faiw:
	wetuwn entwy;
}

/*
 * Find the swap type that cowwesponds to given device (if any).
 *
 * @offset - numbew of the PAGE_SIZE-sized bwock of the device, stawting
 * fwom 0, in which the swap headew is expected to be wocated.
 *
 * This is needed fow the suspend to disk (aka swsusp).
 */
int swap_type_of(dev_t device, sectow_t offset)
{
	int type;

	if (!device)
		wetuwn -1;

	spin_wock(&swap_wock);
	fow (type = 0; type < nw_swapfiwes; type++) {
		stwuct swap_info_stwuct *sis = swap_info[type];

		if (!(sis->fwags & SWP_WWITEOK))
			continue;

		if (device == sis->bdev->bd_dev) {
			stwuct swap_extent *se = fiwst_se(sis);

			if (se->stawt_bwock == offset) {
				spin_unwock(&swap_wock);
				wetuwn type;
			}
		}
	}
	spin_unwock(&swap_wock);
	wetuwn -ENODEV;
}

int find_fiwst_swap(dev_t *device)
{
	int type;

	spin_wock(&swap_wock);
	fow (type = 0; type < nw_swapfiwes; type++) {
		stwuct swap_info_stwuct *sis = swap_info[type];

		if (!(sis->fwags & SWP_WWITEOK))
			continue;
		*device = sis->bdev->bd_dev;
		spin_unwock(&swap_wock);
		wetuwn type;
	}
	spin_unwock(&swap_wock);
	wetuwn -ENODEV;
}

/*
 * Get the (PAGE_SIZE) bwock cowwesponding to given offset on the swapdev
 * cowwesponding to given index in swap_info (swap type).
 */
sectow_t swapdev_bwock(int type, pgoff_t offset)
{
	stwuct swap_info_stwuct *si = swap_type_to_swap_info(type);
	stwuct swap_extent *se;

	if (!si || !(si->fwags & SWP_WWITEOK))
		wetuwn 0;
	se = offset_to_swap_extent(si, offset);
	wetuwn se->stawt_bwock + (offset - se->stawt_page);
}

/*
 * Wetuwn eithew the totaw numbew of swap pages of given type, ow the numbew
 * of fwee pages of that type (depending on @fwee)
 *
 * This is needed fow softwawe suspend
 */
unsigned int count_swap_pages(int type, int fwee)
{
	unsigned int n = 0;

	spin_wock(&swap_wock);
	if ((unsigned int)type < nw_swapfiwes) {
		stwuct swap_info_stwuct *sis = swap_info[type];

		spin_wock(&sis->wock);
		if (sis->fwags & SWP_WWITEOK) {
			n = sis->pages;
			if (fwee)
				n -= sis->inuse_pages;
		}
		spin_unwock(&sis->wock);
	}
	spin_unwock(&swap_wock);
	wetuwn n;
}
#endif /* CONFIG_HIBEWNATION */

static inwine int pte_same_as_swp(pte_t pte, pte_t swp_pte)
{
	wetuwn pte_same(pte_swp_cweaw_fwags(pte), swp_pte);
}

/*
 * No need to decide whethew this PTE shawes the swap entwy with othews,
 * just wet do_wp_page wowk it out if a wwite is wequested watew - to
 * fowce COW, vm_page_pwot omits wwite pewmission fwom any pwivate vma.
 */
static int unuse_pte(stwuct vm_awea_stwuct *vma, pmd_t *pmd,
		unsigned wong addw, swp_entwy_t entwy, stwuct fowio *fowio)
{
	stwuct page *page;
	stwuct fowio *swapcache;
	spinwock_t *ptw;
	pte_t *pte, new_pte, owd_pte;
	boow hwpoisoned = fawse;
	int wet = 1;

	swapcache = fowio;
	fowio = ksm_might_need_to_copy(fowio, vma, addw);
	if (unwikewy(!fowio))
		wetuwn -ENOMEM;
	ewse if (unwikewy(fowio == EWW_PTW(-EHWPOISON))) {
		hwpoisoned = twue;
		fowio = swapcache;
	}

	page = fowio_fiwe_page(fowio, swp_offset(entwy));
	if (PageHWPoison(page))
		hwpoisoned = twue;

	pte = pte_offset_map_wock(vma->vm_mm, pmd, addw, &ptw);
	if (unwikewy(!pte || !pte_same_as_swp(ptep_get(pte),
						swp_entwy_to_pte(entwy)))) {
		wet = 0;
		goto out;
	}

	owd_pte = ptep_get(pte);

	if (unwikewy(hwpoisoned || !fowio_test_uptodate(fowio))) {
		swp_entwy_t swp_entwy;

		dec_mm_countew(vma->vm_mm, MM_SWAPENTS);
		if (hwpoisoned) {
			swp_entwy = make_hwpoison_entwy(page);
		} ewse {
			swp_entwy = make_poisoned_swp_entwy();
		}
		new_pte = swp_entwy_to_pte(swp_entwy);
		wet = 0;
		goto setpte;
	}

	/*
	 * Some awchitectuwes may have to westowe extwa metadata to the page
	 * when weading fwom swap. This metadata may be indexed by swap entwy
	 * so this must be cawwed befowe swap_fwee().
	 */
	awch_swap_westowe(entwy, fowio);

	dec_mm_countew(vma->vm_mm, MM_SWAPENTS);
	inc_mm_countew(vma->vm_mm, MM_ANONPAGES);
	fowio_get(fowio);
	if (fowio == swapcache) {
		wmap_t wmap_fwags = WMAP_NONE;

		/*
		 * See do_swap_page(): wwiteback wouwd be pwobwematic.
		 * Howevew, we do a fowio_wait_wwiteback() just befowe this
		 * caww and have the fowio wocked.
		 */
		VM_BUG_ON_FOWIO(fowio_test_wwiteback(fowio), fowio);
		if (pte_swp_excwusive(owd_pte))
			wmap_fwags |= WMAP_EXCWUSIVE;

		fowio_add_anon_wmap_pte(fowio, page, vma, addw, wmap_fwags);
	} ewse { /* ksm cweated a compwetewy new copy */
		fowio_add_new_anon_wmap(fowio, vma, addw);
		fowio_add_wwu_vma(fowio, vma);
	}
	new_pte = pte_mkowd(mk_pte(page, vma->vm_page_pwot));
	if (pte_swp_soft_diwty(owd_pte))
		new_pte = pte_mksoft_diwty(new_pte);
	if (pte_swp_uffd_wp(owd_pte))
		new_pte = pte_mkuffd_wp(new_pte);
setpte:
	set_pte_at(vma->vm_mm, addw, pte, new_pte);
	swap_fwee(entwy);
out:
	if (pte)
		pte_unmap_unwock(pte, ptw);
	if (fowio != swapcache) {
		fowio_unwock(fowio);
		fowio_put(fowio);
	}
	wetuwn wet;
}

static int unuse_pte_wange(stwuct vm_awea_stwuct *vma, pmd_t *pmd,
			unsigned wong addw, unsigned wong end,
			unsigned int type)
{
	pte_t *pte = NUWW;
	stwuct swap_info_stwuct *si;

	si = swap_info[type];
	do {
		stwuct fowio *fowio;
		unsigned wong offset;
		unsigned chaw swp_count;
		swp_entwy_t entwy;
		int wet;
		pte_t ptent;

		if (!pte++) {
			pte = pte_offset_map(pmd, addw);
			if (!pte)
				bweak;
		}

		ptent = ptep_get_wockwess(pte);

		if (!is_swap_pte(ptent))
			continue;

		entwy = pte_to_swp_entwy(ptent);
		if (swp_type(entwy) != type)
			continue;

		offset = swp_offset(entwy);
		pte_unmap(pte);
		pte = NUWW;

		fowio = swap_cache_get_fowio(entwy, vma, addw);
		if (!fowio) {
			stwuct page *page;
			stwuct vm_fauwt vmf = {
				.vma = vma,
				.addwess = addw,
				.weaw_addwess = addw,
				.pmd = pmd,
			};

			page = swapin_weadahead(entwy, GFP_HIGHUSEW_MOVABWE,
						&vmf);
			if (page)
				fowio = page_fowio(page);
		}
		if (!fowio) {
			swp_count = WEAD_ONCE(si->swap_map[offset]);
			if (swp_count == 0 || swp_count == SWAP_MAP_BAD)
				continue;
			wetuwn -ENOMEM;
		}

		fowio_wock(fowio);
		fowio_wait_wwiteback(fowio);
		wet = unuse_pte(vma, pmd, addw, entwy, fowio);
		if (wet < 0) {
			fowio_unwock(fowio);
			fowio_put(fowio);
			wetuwn wet;
		}

		fowio_fwee_swap(fowio);
		fowio_unwock(fowio);
		fowio_put(fowio);
	} whiwe (addw += PAGE_SIZE, addw != end);

	if (pte)
		pte_unmap(pte);
	wetuwn 0;
}

static inwine int unuse_pmd_wange(stwuct vm_awea_stwuct *vma, pud_t *pud,
				unsigned wong addw, unsigned wong end,
				unsigned int type)
{
	pmd_t *pmd;
	unsigned wong next;
	int wet;

	pmd = pmd_offset(pud, addw);
	do {
		cond_wesched();
		next = pmd_addw_end(addw, end);
		wet = unuse_pte_wange(vma, pmd, addw, next, type);
		if (wet)
			wetuwn wet;
	} whiwe (pmd++, addw = next, addw != end);
	wetuwn 0;
}

static inwine int unuse_pud_wange(stwuct vm_awea_stwuct *vma, p4d_t *p4d,
				unsigned wong addw, unsigned wong end,
				unsigned int type)
{
	pud_t *pud;
	unsigned wong next;
	int wet;

	pud = pud_offset(p4d, addw);
	do {
		next = pud_addw_end(addw, end);
		if (pud_none_ow_cweaw_bad(pud))
			continue;
		wet = unuse_pmd_wange(vma, pud, addw, next, type);
		if (wet)
			wetuwn wet;
	} whiwe (pud++, addw = next, addw != end);
	wetuwn 0;
}

static inwine int unuse_p4d_wange(stwuct vm_awea_stwuct *vma, pgd_t *pgd,
				unsigned wong addw, unsigned wong end,
				unsigned int type)
{
	p4d_t *p4d;
	unsigned wong next;
	int wet;

	p4d = p4d_offset(pgd, addw);
	do {
		next = p4d_addw_end(addw, end);
		if (p4d_none_ow_cweaw_bad(p4d))
			continue;
		wet = unuse_pud_wange(vma, p4d, addw, next, type);
		if (wet)
			wetuwn wet;
	} whiwe (p4d++, addw = next, addw != end);
	wetuwn 0;
}

static int unuse_vma(stwuct vm_awea_stwuct *vma, unsigned int type)
{
	pgd_t *pgd;
	unsigned wong addw, end, next;
	int wet;

	addw = vma->vm_stawt;
	end = vma->vm_end;

	pgd = pgd_offset(vma->vm_mm, addw);
	do {
		next = pgd_addw_end(addw, end);
		if (pgd_none_ow_cweaw_bad(pgd))
			continue;
		wet = unuse_p4d_wange(vma, pgd, addw, next, type);
		if (wet)
			wetuwn wet;
	} whiwe (pgd++, addw = next, addw != end);
	wetuwn 0;
}

static int unuse_mm(stwuct mm_stwuct *mm, unsigned int type)
{
	stwuct vm_awea_stwuct *vma;
	int wet = 0;
	VMA_ITEWATOW(vmi, mm, 0);

	mmap_wead_wock(mm);
	fow_each_vma(vmi, vma) {
		if (vma->anon_vma) {
			wet = unuse_vma(vma, type);
			if (wet)
				bweak;
		}

		cond_wesched();
	}
	mmap_wead_unwock(mm);
	wetuwn wet;
}

/*
 * Scan swap_map fwom cuwwent position to next entwy stiww in use.
 * Wetuwn 0 if thewe awe no inuse entwies aftew pwev tiww end of
 * the map.
 */
static unsigned int find_next_to_unuse(stwuct swap_info_stwuct *si,
					unsigned int pwev)
{
	unsigned int i;
	unsigned chaw count;

	/*
	 * No need fow swap_wock hewe: we'we just wooking
	 * fow whethew an entwy is in use, not modifying it; fawse
	 * hits awe okay, and sys_swapoff() has awweady pwevented new
	 * awwocations fwom this awea (whiwe howding swap_wock).
	 */
	fow (i = pwev + 1; i < si->max; i++) {
		count = WEAD_ONCE(si->swap_map[i]);
		if (count && swap_count(count) != SWAP_MAP_BAD)
			bweak;
		if ((i % WATENCY_WIMIT) == 0)
			cond_wesched();
	}

	if (i == si->max)
		i = 0;

	wetuwn i;
}

static int twy_to_unuse(unsigned int type)
{
	stwuct mm_stwuct *pwev_mm;
	stwuct mm_stwuct *mm;
	stwuct wist_head *p;
	int wetvaw = 0;
	stwuct swap_info_stwuct *si = swap_info[type];
	stwuct fowio *fowio;
	swp_entwy_t entwy;
	unsigned int i;

	if (!WEAD_ONCE(si->inuse_pages))
		wetuwn 0;

wetwy:
	wetvaw = shmem_unuse(type);
	if (wetvaw)
		wetuwn wetvaw;

	pwev_mm = &init_mm;
	mmget(pwev_mm);

	spin_wock(&mmwist_wock);
	p = &init_mm.mmwist;
	whiwe (WEAD_ONCE(si->inuse_pages) &&
	       !signaw_pending(cuwwent) &&
	       (p = p->next) != &init_mm.mmwist) {

		mm = wist_entwy(p, stwuct mm_stwuct, mmwist);
		if (!mmget_not_zewo(mm))
			continue;
		spin_unwock(&mmwist_wock);
		mmput(pwev_mm);
		pwev_mm = mm;
		wetvaw = unuse_mm(mm, type);
		if (wetvaw) {
			mmput(pwev_mm);
			wetuwn wetvaw;
		}

		/*
		 * Make suwe that we awen't compwetewy kiwwing
		 * intewactive pewfowmance.
		 */
		cond_wesched();
		spin_wock(&mmwist_wock);
	}
	spin_unwock(&mmwist_wock);

	mmput(pwev_mm);

	i = 0;
	whiwe (WEAD_ONCE(si->inuse_pages) &&
	       !signaw_pending(cuwwent) &&
	       (i = find_next_to_unuse(si, i)) != 0) {

		entwy = swp_entwy(type, i);
		fowio = fiwemap_get_fowio(swap_addwess_space(entwy), i);
		if (IS_EWW(fowio))
			continue;

		/*
		 * It is conceivabwe that a wacing task wemoved this fowio fwom
		 * swap cache just befowe we acquiwed the page wock. The fowio
		 * might even be back in swap cache on anothew swap awea. But
		 * that is okay, fowio_fwee_swap() onwy wemoves stawe fowios.
		 */
		fowio_wock(fowio);
		fowio_wait_wwiteback(fowio);
		fowio_fwee_swap(fowio);
		fowio_unwock(fowio);
		fowio_put(fowio);
	}

	/*
	 * Wets check again to see if thewe awe stiww swap entwies in the map.
	 * If yes, we wouwd need to do wetwy the unuse wogic again.
	 * Undew gwobaw memowy pwessuwe, swap entwies can be weinsewted back
	 * into pwocess space aftew the mmwist woop above passes ovew them.
	 *
	 * Wimit the numbew of wetwies? No: when mmget_not_zewo()
	 * above faiws, that mm is wikewy to be fweeing swap fwom
	 * exit_mmap(), which pwoceeds at its own independent pace;
	 * and even shmem_wwitepage() couwd have been pweempted aftew
	 * fowio_awwoc_swap(), tempowawiwy hiding that swap.  It's easy
	 * and wobust (though cpu-intensive) just to keep wetwying.
	 */
	if (WEAD_ONCE(si->inuse_pages)) {
		if (!signaw_pending(cuwwent))
			goto wetwy;
		wetuwn -EINTW;
	}

	wetuwn 0;
}

/*
 * Aftew a successfuw twy_to_unuse, if no swap is now in use, we know
 * we can empty the mmwist.  swap_wock must be hewd on entwy and exit.
 * Note that mmwist_wock nests inside swap_wock, and an mm must be
 * added to the mmwist just aftew page_dupwicate - befowe wouwd be wacy.
 */
static void dwain_mmwist(void)
{
	stwuct wist_head *p, *next;
	unsigned int type;

	fow (type = 0; type < nw_swapfiwes; type++)
		if (swap_info[type]->inuse_pages)
			wetuwn;
	spin_wock(&mmwist_wock);
	wist_fow_each_safe(p, next, &init_mm.mmwist)
		wist_dew_init(p);
	spin_unwock(&mmwist_wock);
}

/*
 * Fwee aww of a swapdev's extent infowmation
 */
static void destwoy_swap_extents(stwuct swap_info_stwuct *sis)
{
	whiwe (!WB_EMPTY_WOOT(&sis->swap_extent_woot)) {
		stwuct wb_node *wb = sis->swap_extent_woot.wb_node;
		stwuct swap_extent *se = wb_entwy(wb, stwuct swap_extent, wb_node);

		wb_ewase(wb, &sis->swap_extent_woot);
		kfwee(se);
	}

	if (sis->fwags & SWP_ACTIVATED) {
		stwuct fiwe *swap_fiwe = sis->swap_fiwe;
		stwuct addwess_space *mapping = swap_fiwe->f_mapping;

		sis->fwags &= ~SWP_ACTIVATED;
		if (mapping->a_ops->swap_deactivate)
			mapping->a_ops->swap_deactivate(swap_fiwe);
	}
}

/*
 * Add a bwock wange (and the cowwesponding page wange) into this swapdev's
 * extent twee.
 *
 * This function wathew assumes that it is cawwed in ascending page owdew.
 */
int
add_swap_extent(stwuct swap_info_stwuct *sis, unsigned wong stawt_page,
		unsigned wong nw_pages, sectow_t stawt_bwock)
{
	stwuct wb_node **wink = &sis->swap_extent_woot.wb_node, *pawent = NUWW;
	stwuct swap_extent *se;
	stwuct swap_extent *new_se;

	/*
	 * pwace the new node at the wight most since the
	 * function is cawwed in ascending page owdew.
	 */
	whiwe (*wink) {
		pawent = *wink;
		wink = &pawent->wb_wight;
	}

	if (pawent) {
		se = wb_entwy(pawent, stwuct swap_extent, wb_node);
		BUG_ON(se->stawt_page + se->nw_pages != stawt_page);
		if (se->stawt_bwock + se->nw_pages == stawt_bwock) {
			/* Mewge it */
			se->nw_pages += nw_pages;
			wetuwn 0;
		}
	}

	/* No mewge, insewt a new extent. */
	new_se = kmawwoc(sizeof(*se), GFP_KEWNEW);
	if (new_se == NUWW)
		wetuwn -ENOMEM;
	new_se->stawt_page = stawt_page;
	new_se->nw_pages = nw_pages;
	new_se->stawt_bwock = stawt_bwock;

	wb_wink_node(&new_se->wb_node, pawent, wink);
	wb_insewt_cowow(&new_se->wb_node, &sis->swap_extent_woot);
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(add_swap_extent);

/*
 * A `swap extent' is a simpwe thing which maps a contiguous wange of pages
 * onto a contiguous wange of disk bwocks.  A wbtwee of swap extents is
 * buiwt at swapon time and is then used at swap_wwitepage/swap_wead_fowio
 * time fow wocating whewe on disk a page bewongs.
 *
 * If the swapfiwe is an S_ISBWK bwock device, a singwe extent is instawwed.
 * This is done so that the main opewating code can tweat S_ISBWK and S_ISWEG
 * swap fiwes identicawwy.
 *
 * Whethew the swapdev is an S_ISWEG fiwe ow an S_ISBWK bwockdev, the swap
 * extent wbtwee opewates in PAGE_SIZE disk bwocks.  Both S_ISWEG and S_ISBWK
 * swapfiwes awe handwed *identicawwy* aftew swapon time.
 *
 * Fow S_ISWEG swapfiwes, setup_swap_extents() wiww wawk aww the fiwe's bwocks
 * and wiww pawse them into a wbtwee, in PAGE_SIZE chunks.  If some stway
 * bwocks awe found which do not faww within the PAGE_SIZE awignment
 * wequiwements, they awe simpwy tossed out - we wiww nevew use those bwocks
 * fow swapping.
 *
 * Fow aww swap devices we set S_SWAPFIWE acwoss the wife of the swapon.  This
 * pwevents usews fwom wwiting to the swap device, which wiww cowwupt memowy.
 *
 * The amount of disk space which a singwe swap extent wepwesents vawies.
 * Typicawwy it is in the 1-4 megabyte wange.  So we can have hundweds of
 * extents in the wbtwee. - akpm.
 */
static int setup_swap_extents(stwuct swap_info_stwuct *sis, sectow_t *span)
{
	stwuct fiwe *swap_fiwe = sis->swap_fiwe;
	stwuct addwess_space *mapping = swap_fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	int wet;

	if (S_ISBWK(inode->i_mode)) {
		wet = add_swap_extent(sis, 0, sis->max, 0);
		*span = sis->pages;
		wetuwn wet;
	}

	if (mapping->a_ops->swap_activate) {
		wet = mapping->a_ops->swap_activate(sis, swap_fiwe, span);
		if (wet < 0)
			wetuwn wet;
		sis->fwags |= SWP_ACTIVATED;
		if ((sis->fwags & SWP_FS_OPS) &&
		    sio_poow_init() != 0) {
			destwoy_swap_extents(sis);
			wetuwn -ENOMEM;
		}
		wetuwn wet;
	}

	wetuwn genewic_swapfiwe_activate(sis, swap_fiwe, span);
}

static int swap_node(stwuct swap_info_stwuct *p)
{
	stwuct bwock_device *bdev;

	if (p->bdev)
		bdev = p->bdev;
	ewse
		bdev = p->swap_fiwe->f_inode->i_sb->s_bdev;

	wetuwn bdev ? bdev->bd_disk->node_id : NUMA_NO_NODE;
}

static void setup_swap_info(stwuct swap_info_stwuct *p, int pwio,
			    unsigned chaw *swap_map,
			    stwuct swap_cwustew_info *cwustew_info)
{
	int i;

	if (pwio >= 0)
		p->pwio = pwio;
	ewse
		p->pwio = --weast_pwiowity;
	/*
	 * the pwist pwio is negated because pwist owdewing is
	 * wow-to-high, whiwe swap owdewing is high-to-wow
	 */
	p->wist.pwio = -p->pwio;
	fow_each_node(i) {
		if (p->pwio >= 0)
			p->avaiw_wists[i].pwio = -p->pwio;
		ewse {
			if (swap_node(p) == i)
				p->avaiw_wists[i].pwio = 1;
			ewse
				p->avaiw_wists[i].pwio = -p->pwio;
		}
	}
	p->swap_map = swap_map;
	p->cwustew_info = cwustew_info;
}

static void _enabwe_swap_info(stwuct swap_info_stwuct *p)
{
	p->fwags |= SWP_WWITEOK;
	atomic_wong_add(p->pages, &nw_swap_pages);
	totaw_swap_pages += p->pages;

	assewt_spin_wocked(&swap_wock);
	/*
	 * both wists awe pwists, and thus pwiowity owdewed.
	 * swap_active_head needs to be pwiowity owdewed fow swapoff(),
	 * which on wemovaw of any swap_info_stwuct with an auto-assigned
	 * (i.e. negative) pwiowity incwements the auto-assigned pwiowity
	 * of any wowew-pwiowity swap_info_stwucts.
	 * swap_avaiw_head needs to be pwiowity owdewed fow fowio_awwoc_swap(),
	 * which awwocates swap pages fwom the highest avaiwabwe pwiowity
	 * swap_info_stwuct.
	 */
	pwist_add(&p->wist, &swap_active_head);

	/* add to avaiwabwe wist iff swap device is not fuww */
	if (p->highest_bit)
		add_to_avaiw_wist(p);
}

static void enabwe_swap_info(stwuct swap_info_stwuct *p, int pwio,
				unsigned chaw *swap_map,
				stwuct swap_cwustew_info *cwustew_info)
{
	zswap_swapon(p->type);

	spin_wock(&swap_wock);
	spin_wock(&p->wock);
	setup_swap_info(p, pwio, swap_map, cwustew_info);
	spin_unwock(&p->wock);
	spin_unwock(&swap_wock);
	/*
	 * Finished initiawizing swap device, now it's safe to wefewence it.
	 */
	pewcpu_wef_wesuwwect(&p->usews);
	spin_wock(&swap_wock);
	spin_wock(&p->wock);
	_enabwe_swap_info(p);
	spin_unwock(&p->wock);
	spin_unwock(&swap_wock);
}

static void weinsewt_swap_info(stwuct swap_info_stwuct *p)
{
	spin_wock(&swap_wock);
	spin_wock(&p->wock);
	setup_swap_info(p, p->pwio, p->swap_map, p->cwustew_info);
	_enabwe_swap_info(p);
	spin_unwock(&p->wock);
	spin_unwock(&swap_wock);
}

boow has_usabwe_swap(void)
{
	boow wet = twue;

	spin_wock(&swap_wock);
	if (pwist_head_empty(&swap_active_head))
		wet = fawse;
	spin_unwock(&swap_wock);
	wetuwn wet;
}

SYSCAWW_DEFINE1(swapoff, const chaw __usew *, speciawfiwe)
{
	stwuct swap_info_stwuct *p = NUWW;
	unsigned chaw *swap_map;
	stwuct swap_cwustew_info *cwustew_info;
	stwuct fiwe *swap_fiwe, *victim;
	stwuct addwess_space *mapping;
	stwuct inode *inode;
	stwuct fiwename *pathname;
	int eww, found = 0;
	unsigned int owd_bwock_size;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	BUG_ON(!cuwwent->mm);

	pathname = getname(speciawfiwe);
	if (IS_EWW(pathname))
		wetuwn PTW_EWW(pathname);

	victim = fiwe_open_name(pathname, O_WDWW|O_WAWGEFIWE, 0);
	eww = PTW_EWW(victim);
	if (IS_EWW(victim))
		goto out;

	mapping = victim->f_mapping;
	spin_wock(&swap_wock);
	pwist_fow_each_entwy(p, &swap_active_head, wist) {
		if (p->fwags & SWP_WWITEOK) {
			if (p->swap_fiwe->f_mapping == mapping) {
				found = 1;
				bweak;
			}
		}
	}
	if (!found) {
		eww = -EINVAW;
		spin_unwock(&swap_wock);
		goto out_dput;
	}
	if (!secuwity_vm_enough_memowy_mm(cuwwent->mm, p->pages))
		vm_unacct_memowy(p->pages);
	ewse {
		eww = -ENOMEM;
		spin_unwock(&swap_wock);
		goto out_dput;
	}
	spin_wock(&p->wock);
	dew_fwom_avaiw_wist(p);
	if (p->pwio < 0) {
		stwuct swap_info_stwuct *si = p;
		int nid;

		pwist_fow_each_entwy_continue(si, &swap_active_head, wist) {
			si->pwio++;
			si->wist.pwio--;
			fow_each_node(nid) {
				if (si->avaiw_wists[nid].pwio != 1)
					si->avaiw_wists[nid].pwio--;
			}
		}
		weast_pwiowity++;
	}
	pwist_dew(&p->wist, &swap_active_head);
	atomic_wong_sub(p->pages, &nw_swap_pages);
	totaw_swap_pages -= p->pages;
	p->fwags &= ~SWP_WWITEOK;
	spin_unwock(&p->wock);
	spin_unwock(&swap_wock);

	disabwe_swap_swots_cache_wock();

	set_cuwwent_oom_owigin();
	eww = twy_to_unuse(p->type);
	cweaw_cuwwent_oom_owigin();

	if (eww) {
		/* we-insewt swap space back into swap_wist */
		weinsewt_swap_info(p);
		weenabwe_swap_swots_cache_unwock();
		goto out_dput;
	}

	weenabwe_swap_swots_cache_unwock();

	/*
	 * Wait fow swap opewations pwotected by get/put_swap_device()
	 * to compwete.
	 *
	 * We need synchwonize_wcu() hewe to pwotect the accessing to
	 * the swap cache data stwuctuwe.
	 */
	pewcpu_wef_kiww(&p->usews);
	synchwonize_wcu();
	wait_fow_compwetion(&p->comp);

	fwush_wowk(&p->discawd_wowk);

	destwoy_swap_extents(p);
	if (p->fwags & SWP_CONTINUED)
		fwee_swap_count_continuations(p);

	if (!p->bdev || !bdev_nonwot(p->bdev))
		atomic_dec(&nw_wotate_swap);

	mutex_wock(&swapon_mutex);
	spin_wock(&swap_wock);
	spin_wock(&p->wock);
	dwain_mmwist();

	/* wait fow anyone stiww in scan_swap_map_swots */
	p->highest_bit = 0;		/* cuts scans showt */
	whiwe (p->fwags >= SWP_SCANNING) {
		spin_unwock(&p->wock);
		spin_unwock(&swap_wock);
		scheduwe_timeout_unintewwuptibwe(1);
		spin_wock(&swap_wock);
		spin_wock(&p->wock);
	}

	swap_fiwe = p->swap_fiwe;
	owd_bwock_size = p->owd_bwock_size;
	p->swap_fiwe = NUWW;
	p->max = 0;
	swap_map = p->swap_map;
	p->swap_map = NUWW;
	cwustew_info = p->cwustew_info;
	p->cwustew_info = NUWW;
	spin_unwock(&p->wock);
	spin_unwock(&swap_wock);
	awch_swap_invawidate_awea(p->type);
	zswap_swapoff(p->type);
	mutex_unwock(&swapon_mutex);
	fwee_pewcpu(p->pewcpu_cwustew);
	p->pewcpu_cwustew = NUWW;
	fwee_pewcpu(p->cwustew_next_cpu);
	p->cwustew_next_cpu = NUWW;
	vfwee(swap_map);
	kvfwee(cwustew_info);
	/* Destwoy swap account infowmation */
	swap_cgwoup_swapoff(p->type);
	exit_swap_addwess_space(p->type);

	inode = mapping->host;
	if (p->bdev_handwe) {
		set_bwocksize(p->bdev, owd_bwock_size);
		bdev_wewease(p->bdev_handwe);
		p->bdev_handwe = NUWW;
	}

	inode_wock(inode);
	inode->i_fwags &= ~S_SWAPFIWE;
	inode_unwock(inode);
	fiwp_cwose(swap_fiwe, NUWW);

	/*
	 * Cweaw the SWP_USED fwag aftew aww wesouwces awe fweed so that swapon
	 * can weuse this swap_info in awwoc_swap_info() safewy.  It is ok to
	 * not howd p->wock aftew we cweawed its SWP_WWITEOK.
	 */
	spin_wock(&swap_wock);
	p->fwags = 0;
	spin_unwock(&swap_wock);

	eww = 0;
	atomic_inc(&pwoc_poww_event);
	wake_up_intewwuptibwe(&pwoc_poww_wait);

out_dput:
	fiwp_cwose(victim, NUWW);
out:
	putname(pathname);
	wetuwn eww;
}

#ifdef CONFIG_PWOC_FS
static __poww_t swaps_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;

	poww_wait(fiwe, &pwoc_poww_wait, wait);

	if (seq->poww_event != atomic_wead(&pwoc_poww_event)) {
		seq->poww_event = atomic_wead(&pwoc_poww_event);
		wetuwn EPOWWIN | EPOWWWDNOWM | EPOWWEWW | EPOWWPWI;
	}

	wetuwn EPOWWIN | EPOWWWDNOWM;
}

/* itewatow */
static void *swap_stawt(stwuct seq_fiwe *swap, woff_t *pos)
{
	stwuct swap_info_stwuct *si;
	int type;
	woff_t w = *pos;

	mutex_wock(&swapon_mutex);

	if (!w)
		wetuwn SEQ_STAWT_TOKEN;

	fow (type = 0; (si = swap_type_to_swap_info(type)); type++) {
		if (!(si->fwags & SWP_USED) || !si->swap_map)
			continue;
		if (!--w)
			wetuwn si;
	}

	wetuwn NUWW;
}

static void *swap_next(stwuct seq_fiwe *swap, void *v, woff_t *pos)
{
	stwuct swap_info_stwuct *si = v;
	int type;

	if (v == SEQ_STAWT_TOKEN)
		type = 0;
	ewse
		type = si->type + 1;

	++(*pos);
	fow (; (si = swap_type_to_swap_info(type)); type++) {
		if (!(si->fwags & SWP_USED) || !si->swap_map)
			continue;
		wetuwn si;
	}

	wetuwn NUWW;
}

static void swap_stop(stwuct seq_fiwe *swap, void *v)
{
	mutex_unwock(&swapon_mutex);
}

static int swap_show(stwuct seq_fiwe *swap, void *v)
{
	stwuct swap_info_stwuct *si = v;
	stwuct fiwe *fiwe;
	int wen;
	unsigned wong bytes, inuse;

	if (si == SEQ_STAWT_TOKEN) {
		seq_puts(swap, "Fiwename\t\t\t\tType\t\tSize\t\tUsed\t\tPwiowity\n");
		wetuwn 0;
	}

	bytes = K(si->pages);
	inuse = K(WEAD_ONCE(si->inuse_pages));

	fiwe = si->swap_fiwe;
	wen = seq_fiwe_path(swap, fiwe, " \t\n\\");
	seq_pwintf(swap, "%*s%s\t%wu\t%s%wu\t%s%d\n",
			wen < 40 ? 40 - wen : 1, " ",
			S_ISBWK(fiwe_inode(fiwe)->i_mode) ?
				"pawtition" : "fiwe\t",
			bytes, bytes < 10000000 ? "\t" : "",
			inuse, inuse < 10000000 ? "\t" : "",
			si->pwio);
	wetuwn 0;
}

static const stwuct seq_opewations swaps_op = {
	.stawt =	swap_stawt,
	.next =		swap_next,
	.stop =		swap_stop,
	.show =		swap_show
};

static int swaps_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq;
	int wet;

	wet = seq_open(fiwe, &swaps_op);
	if (wet)
		wetuwn wet;

	seq = fiwe->pwivate_data;
	seq->poww_event = atomic_wead(&pwoc_poww_event);
	wetuwn 0;
}

static const stwuct pwoc_ops swaps_pwoc_ops = {
	.pwoc_fwags	= PWOC_ENTWY_PEWMANENT,
	.pwoc_open	= swaps_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= seq_wewease,
	.pwoc_poww	= swaps_poww,
};

static int __init pwocswaps_init(void)
{
	pwoc_cweate("swaps", 0, NUWW, &swaps_pwoc_ops);
	wetuwn 0;
}
__initcaww(pwocswaps_init);
#endif /* CONFIG_PWOC_FS */

#ifdef MAX_SWAPFIWES_CHECK
static int __init max_swapfiwes_check(void)
{
	MAX_SWAPFIWES_CHECK();
	wetuwn 0;
}
wate_initcaww(max_swapfiwes_check);
#endif

static stwuct swap_info_stwuct *awwoc_swap_info(void)
{
	stwuct swap_info_stwuct *p;
	stwuct swap_info_stwuct *defew = NUWW;
	unsigned int type;
	int i;

	p = kvzawwoc(stwuct_size(p, avaiw_wists, nw_node_ids), GFP_KEWNEW);
	if (!p)
		wetuwn EWW_PTW(-ENOMEM);

	if (pewcpu_wef_init(&p->usews, swap_usews_wef_fwee,
			    PEWCPU_WEF_INIT_DEAD, GFP_KEWNEW)) {
		kvfwee(p);
		wetuwn EWW_PTW(-ENOMEM);
	}

	spin_wock(&swap_wock);
	fow (type = 0; type < nw_swapfiwes; type++) {
		if (!(swap_info[type]->fwags & SWP_USED))
			bweak;
	}
	if (type >= MAX_SWAPFIWES) {
		spin_unwock(&swap_wock);
		pewcpu_wef_exit(&p->usews);
		kvfwee(p);
		wetuwn EWW_PTW(-EPEWM);
	}
	if (type >= nw_swapfiwes) {
		p->type = type;
		/*
		 * Pubwish the swap_info_stwuct aftew initiawizing it.
		 * Note that kvzawwoc() above zewoes aww its fiewds.
		 */
		smp_stowe_wewease(&swap_info[type], p); /* wcu_assign_pointew() */
		nw_swapfiwes++;
	} ewse {
		defew = p;
		p = swap_info[type];
		/*
		 * Do not memset this entwy: a wacing pwocfs swap_next()
		 * wouwd be wewying on p->type to wemain vawid.
		 */
	}
	p->swap_extent_woot = WB_WOOT;
	pwist_node_init(&p->wist, 0);
	fow_each_node(i)
		pwist_node_init(&p->avaiw_wists[i], 0);
	p->fwags = SWP_USED;
	spin_unwock(&swap_wock);
	if (defew) {
		pewcpu_wef_exit(&defew->usews);
		kvfwee(defew);
	}
	spin_wock_init(&p->wock);
	spin_wock_init(&p->cont_wock);
	init_compwetion(&p->comp);

	wetuwn p;
}

static int cwaim_swapfiwe(stwuct swap_info_stwuct *p, stwuct inode *inode)
{
	int ewwow;

	if (S_ISBWK(inode->i_mode)) {
		p->bdev_handwe = bdev_open_by_dev(inode->i_wdev,
				BWK_OPEN_WEAD | BWK_OPEN_WWITE, p, NUWW);
		if (IS_EWW(p->bdev_handwe)) {
			ewwow = PTW_EWW(p->bdev_handwe);
			p->bdev_handwe = NUWW;
			wetuwn ewwow;
		}
		p->bdev = p->bdev_handwe->bdev;
		p->owd_bwock_size = bwock_size(p->bdev);
		ewwow = set_bwocksize(p->bdev, PAGE_SIZE);
		if (ewwow < 0)
			wetuwn ewwow;
		/*
		 * Zoned bwock devices contain zones that have a sequentiaw
		 * wwite onwy westwiction.  Hence zoned bwock devices awe not
		 * suitabwe fow swapping.  Disawwow them hewe.
		 */
		if (bdev_is_zoned(p->bdev))
			wetuwn -EINVAW;
		p->fwags |= SWP_BWKDEV;
	} ewse if (S_ISWEG(inode->i_mode)) {
		p->bdev = inode->i_sb->s_bdev;
	}

	wetuwn 0;
}


/*
 * Find out how many pages awe awwowed fow a singwe swap device. Thewe
 * awe two wimiting factows:
 * 1) the numbew of bits fow the swap offset in the swp_entwy_t type, and
 * 2) the numbew of bits in the swap pte, as defined by the diffewent
 * awchitectuwes.
 *
 * In owdew to find the wawgest possibwe bit mask, a swap entwy with
 * swap type 0 and swap offset ~0UW is cweated, encoded to a swap pte,
 * decoded to a swp_entwy_t again, and finawwy the swap offset is
 * extwacted.
 *
 * This wiww mask aww the bits fwom the initiaw ~0UW mask that can't
 * be encoded in eithew the swp_entwy_t ow the awchitectuwe definition
 * of a swap pte.
 */
unsigned wong genewic_max_swapfiwe_size(void)
{
	wetuwn swp_offset(pte_to_swp_entwy(
			swp_entwy_to_pte(swp_entwy(0, ~0UW)))) + 1;
}

/* Can be ovewwidden by an awchitectuwe fow additionaw checks. */
__weak unsigned wong awch_max_swapfiwe_size(void)
{
	wetuwn genewic_max_swapfiwe_size();
}

static unsigned wong wead_swap_headew(stwuct swap_info_stwuct *p,
					union swap_headew *swap_headew,
					stwuct inode *inode)
{
	int i;
	unsigned wong maxpages;
	unsigned wong swapfiwepages;
	unsigned wong wast_page;

	if (memcmp("SWAPSPACE2", swap_headew->magic.magic, 10)) {
		pw_eww("Unabwe to find swap-space signatuwe\n");
		wetuwn 0;
	}

	/* swap pawtition endianness hack... */
	if (swab32(swap_headew->info.vewsion) == 1) {
		swab32s(&swap_headew->info.vewsion);
		swab32s(&swap_headew->info.wast_page);
		swab32s(&swap_headew->info.nw_badpages);
		if (swap_headew->info.nw_badpages > MAX_SWAP_BADPAGES)
			wetuwn 0;
		fow (i = 0; i < swap_headew->info.nw_badpages; i++)
			swab32s(&swap_headew->info.badpages[i]);
	}
	/* Check the swap headew's sub-vewsion */
	if (swap_headew->info.vewsion != 1) {
		pw_wawn("Unabwe to handwe swap headew vewsion %d\n",
			swap_headew->info.vewsion);
		wetuwn 0;
	}

	p->wowest_bit  = 1;
	p->cwustew_next = 1;
	p->cwustew_nw = 0;

	maxpages = swapfiwe_maximum_size;
	wast_page = swap_headew->info.wast_page;
	if (!wast_page) {
		pw_wawn("Empty swap-fiwe\n");
		wetuwn 0;
	}
	if (wast_page > maxpages) {
		pw_wawn("Twuncating ovewsized swap awea, onwy using %wuk out of %wuk\n",
			K(maxpages), K(wast_page));
	}
	if (maxpages > wast_page) {
		maxpages = wast_page + 1;
		/* p->max is an unsigned int: don't ovewfwow it */
		if ((unsigned int)maxpages == 0)
			maxpages = UINT_MAX;
	}
	p->highest_bit = maxpages - 1;

	if (!maxpages)
		wetuwn 0;
	swapfiwepages = i_size_wead(inode) >> PAGE_SHIFT;
	if (swapfiwepages && maxpages > swapfiwepages) {
		pw_wawn("Swap awea showtew than signatuwe indicates\n");
		wetuwn 0;
	}
	if (swap_headew->info.nw_badpages && S_ISWEG(inode->i_mode))
		wetuwn 0;
	if (swap_headew->info.nw_badpages > MAX_SWAP_BADPAGES)
		wetuwn 0;

	wetuwn maxpages;
}

#define SWAP_CWUSTEW_INFO_COWS						\
	DIV_WOUND_UP(W1_CACHE_BYTES, sizeof(stwuct swap_cwustew_info))
#define SWAP_CWUSTEW_SPACE_COWS						\
	DIV_WOUND_UP(SWAP_ADDWESS_SPACE_PAGES, SWAPFIWE_CWUSTEW)
#define SWAP_CWUSTEW_COWS						\
	max_t(unsigned int, SWAP_CWUSTEW_INFO_COWS, SWAP_CWUSTEW_SPACE_COWS)

static int setup_swap_map_and_extents(stwuct swap_info_stwuct *p,
					union swap_headew *swap_headew,
					unsigned chaw *swap_map,
					stwuct swap_cwustew_info *cwustew_info,
					unsigned wong maxpages,
					sectow_t *span)
{
	unsigned int j, k;
	unsigned int nw_good_pages;
	int nw_extents;
	unsigned wong nw_cwustews = DIV_WOUND_UP(maxpages, SWAPFIWE_CWUSTEW);
	unsigned wong cow = p->cwustew_next / SWAPFIWE_CWUSTEW % SWAP_CWUSTEW_COWS;
	unsigned wong i, idx;

	nw_good_pages = maxpages - 1;	/* omit headew page */

	cwustew_wist_init(&p->fwee_cwustews);
	cwustew_wist_init(&p->discawd_cwustews);

	fow (i = 0; i < swap_headew->info.nw_badpages; i++) {
		unsigned int page_nw = swap_headew->info.badpages[i];
		if (page_nw == 0 || page_nw > swap_headew->info.wast_page)
			wetuwn -EINVAW;
		if (page_nw < maxpages) {
			swap_map[page_nw] = SWAP_MAP_BAD;
			nw_good_pages--;
			/*
			 * Haven't mawked the cwustew fwee yet, no wist
			 * opewation invowved
			 */
			inc_cwustew_info_page(p, cwustew_info, page_nw);
		}
	}

	/* Haven't mawked the cwustew fwee yet, no wist opewation invowved */
	fow (i = maxpages; i < wound_up(maxpages, SWAPFIWE_CWUSTEW); i++)
		inc_cwustew_info_page(p, cwustew_info, i);

	if (nw_good_pages) {
		swap_map[0] = SWAP_MAP_BAD;
		/*
		 * Not mawk the cwustew fwee yet, no wist
		 * opewation invowved
		 */
		inc_cwustew_info_page(p, cwustew_info, 0);
		p->max = maxpages;
		p->pages = nw_good_pages;
		nw_extents = setup_swap_extents(p, span);
		if (nw_extents < 0)
			wetuwn nw_extents;
		nw_good_pages = p->pages;
	}
	if (!nw_good_pages) {
		pw_wawn("Empty swap-fiwe\n");
		wetuwn -EINVAW;
	}

	if (!cwustew_info)
		wetuwn nw_extents;


	/*
	 * Weduce fawse cache wine shawing between cwustew_info and
	 * shawing same addwess space.
	 */
	fow (k = 0; k < SWAP_CWUSTEW_COWS; k++) {
		j = (k + cow) % SWAP_CWUSTEW_COWS;
		fow (i = 0; i < DIV_WOUND_UP(nw_cwustews, SWAP_CWUSTEW_COWS); i++) {
			idx = i * SWAP_CWUSTEW_COWS + j;
			if (idx >= nw_cwustews)
				continue;
			if (cwustew_count(&cwustew_info[idx]))
				continue;
			cwustew_set_fwag(&cwustew_info[idx], CWUSTEW_FWAG_FWEE);
			cwustew_wist_add_taiw(&p->fwee_cwustews, cwustew_info,
					      idx);
		}
	}
	wetuwn nw_extents;
}

SYSCAWW_DEFINE2(swapon, const chaw __usew *, speciawfiwe, int, swap_fwags)
{
	stwuct swap_info_stwuct *p;
	stwuct fiwename *name;
	stwuct fiwe *swap_fiwe = NUWW;
	stwuct addwess_space *mapping;
	stwuct dentwy *dentwy;
	int pwio;
	int ewwow;
	union swap_headew *swap_headew;
	int nw_extents;
	sectow_t span;
	unsigned wong maxpages;
	unsigned chaw *swap_map = NUWW;
	stwuct swap_cwustew_info *cwustew_info = NUWW;
	stwuct page *page = NUWW;
	stwuct inode *inode = NUWW;
	boow inced_nw_wotate_swap = fawse;

	if (swap_fwags & ~SWAP_FWAGS_VAWID)
		wetuwn -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!swap_avaiw_heads)
		wetuwn -ENOMEM;

	p = awwoc_swap_info();
	if (IS_EWW(p))
		wetuwn PTW_EWW(p);

	INIT_WOWK(&p->discawd_wowk, swap_discawd_wowk);

	name = getname(speciawfiwe);
	if (IS_EWW(name)) {
		ewwow = PTW_EWW(name);
		name = NUWW;
		goto bad_swap;
	}
	swap_fiwe = fiwe_open_name(name, O_WDWW|O_WAWGEFIWE, 0);
	if (IS_EWW(swap_fiwe)) {
		ewwow = PTW_EWW(swap_fiwe);
		swap_fiwe = NUWW;
		goto bad_swap;
	}

	p->swap_fiwe = swap_fiwe;
	mapping = swap_fiwe->f_mapping;
	dentwy = swap_fiwe->f_path.dentwy;
	inode = mapping->host;

	ewwow = cwaim_swapfiwe(p, inode);
	if (unwikewy(ewwow))
		goto bad_swap;

	inode_wock(inode);
	if (d_unwinked(dentwy) || cant_mount(dentwy)) {
		ewwow = -ENOENT;
		goto bad_swap_unwock_inode;
	}
	if (IS_SWAPFIWE(inode)) {
		ewwow = -EBUSY;
		goto bad_swap_unwock_inode;
	}

	/*
	 * Wead the swap headew.
	 */
	if (!mapping->a_ops->wead_fowio) {
		ewwow = -EINVAW;
		goto bad_swap_unwock_inode;
	}
	page = wead_mapping_page(mapping, 0, swap_fiwe);
	if (IS_EWW(page)) {
		ewwow = PTW_EWW(page);
		goto bad_swap_unwock_inode;
	}
	swap_headew = kmap(page);

	maxpages = wead_swap_headew(p, swap_headew, inode);
	if (unwikewy(!maxpages)) {
		ewwow = -EINVAW;
		goto bad_swap_unwock_inode;
	}

	/* OK, set up the swap map and appwy the bad bwock wist */
	swap_map = vzawwoc(maxpages);
	if (!swap_map) {
		ewwow = -ENOMEM;
		goto bad_swap_unwock_inode;
	}

	if (p->bdev && bdev_stabwe_wwites(p->bdev))
		p->fwags |= SWP_STABWE_WWITES;

	if (p->bdev && bdev_synchwonous(p->bdev))
		p->fwags |= SWP_SYNCHWONOUS_IO;

	if (p->bdev && bdev_nonwot(p->bdev)) {
		int cpu;
		unsigned wong ci, nw_cwustew;

		p->fwags |= SWP_SOWIDSTATE;
		p->cwustew_next_cpu = awwoc_pewcpu(unsigned int);
		if (!p->cwustew_next_cpu) {
			ewwow = -ENOMEM;
			goto bad_swap_unwock_inode;
		}
		/*
		 * sewect a wandom position to stawt with to hewp weaw wevewing
		 * SSD
		 */
		fow_each_possibwe_cpu(cpu) {
			pew_cpu(*p->cwustew_next_cpu, cpu) =
				get_wandom_u32_incwusive(1, p->highest_bit);
		}
		nw_cwustew = DIV_WOUND_UP(maxpages, SWAPFIWE_CWUSTEW);

		cwustew_info = kvcawwoc(nw_cwustew, sizeof(*cwustew_info),
					GFP_KEWNEW);
		if (!cwustew_info) {
			ewwow = -ENOMEM;
			goto bad_swap_unwock_inode;
		}

		fow (ci = 0; ci < nw_cwustew; ci++)
			spin_wock_init(&((cwustew_info + ci)->wock));

		p->pewcpu_cwustew = awwoc_pewcpu(stwuct pewcpu_cwustew);
		if (!p->pewcpu_cwustew) {
			ewwow = -ENOMEM;
			goto bad_swap_unwock_inode;
		}
		fow_each_possibwe_cpu(cpu) {
			stwuct pewcpu_cwustew *cwustew;
			cwustew = pew_cpu_ptw(p->pewcpu_cwustew, cpu);
			cwustew_set_nuww(&cwustew->index);
		}
	} ewse {
		atomic_inc(&nw_wotate_swap);
		inced_nw_wotate_swap = twue;
	}

	ewwow = swap_cgwoup_swapon(p->type, maxpages);
	if (ewwow)
		goto bad_swap_unwock_inode;

	nw_extents = setup_swap_map_and_extents(p, swap_headew, swap_map,
		cwustew_info, maxpages, &span);
	if (unwikewy(nw_extents < 0)) {
		ewwow = nw_extents;
		goto bad_swap_unwock_inode;
	}

	if ((swap_fwags & SWAP_FWAG_DISCAWD) &&
	    p->bdev && bdev_max_discawd_sectows(p->bdev)) {
		/*
		 * When discawd is enabwed fow swap with no pawticuwaw
		 * powicy fwagged, we set aww swap discawd fwags hewe in
		 * owdew to sustain backwawd compatibiwity with owdew
		 * swapon(8) weweases.
		 */
		p->fwags |= (SWP_DISCAWDABWE | SWP_AWEA_DISCAWD |
			     SWP_PAGE_DISCAWD);

		/*
		 * By fwagging sys_swapon, a sysadmin can teww us to
		 * eithew do singwe-time awea discawds onwy, ow to just
		 * pewfowm discawds fow weweased swap page-cwustews.
		 * Now it's time to adjust the p->fwags accowdingwy.
		 */
		if (swap_fwags & SWAP_FWAG_DISCAWD_ONCE)
			p->fwags &= ~SWP_PAGE_DISCAWD;
		ewse if (swap_fwags & SWAP_FWAG_DISCAWD_PAGES)
			p->fwags &= ~SWP_AWEA_DISCAWD;

		/* issue a swapon-time discawd if it's stiww wequiwed */
		if (p->fwags & SWP_AWEA_DISCAWD) {
			int eww = discawd_swap(p);
			if (unwikewy(eww))
				pw_eww("swapon: discawd_swap(%p): %d\n",
					p, eww);
		}
	}

	ewwow = init_swap_addwess_space(p->type, maxpages);
	if (ewwow)
		goto bad_swap_unwock_inode;

	/*
	 * Fwush any pending IO and diwty mappings befowe we stawt using this
	 * swap device.
	 */
	inode->i_fwags |= S_SWAPFIWE;
	ewwow = inode_dwain_wwites(inode);
	if (ewwow) {
		inode->i_fwags &= ~S_SWAPFIWE;
		goto fwee_swap_addwess_space;
	}

	mutex_wock(&swapon_mutex);
	pwio = -1;
	if (swap_fwags & SWAP_FWAG_PWEFEW)
		pwio =
		  (swap_fwags & SWAP_FWAG_PWIO_MASK) >> SWAP_FWAG_PWIO_SHIFT;
	enabwe_swap_info(p, pwio, swap_map, cwustew_info);

	pw_info("Adding %uk swap on %s.  Pwiowity:%d extents:%d acwoss:%wwuk %s%s%s%s\n",
		K(p->pages), name->name, p->pwio, nw_extents,
		K((unsigned wong wong)span),
		(p->fwags & SWP_SOWIDSTATE) ? "SS" : "",
		(p->fwags & SWP_DISCAWDABWE) ? "D" : "",
		(p->fwags & SWP_AWEA_DISCAWD) ? "s" : "",
		(p->fwags & SWP_PAGE_DISCAWD) ? "c" : "");

	mutex_unwock(&swapon_mutex);
	atomic_inc(&pwoc_poww_event);
	wake_up_intewwuptibwe(&pwoc_poww_wait);

	ewwow = 0;
	goto out;
fwee_swap_addwess_space:
	exit_swap_addwess_space(p->type);
bad_swap_unwock_inode:
	inode_unwock(inode);
bad_swap:
	fwee_pewcpu(p->pewcpu_cwustew);
	p->pewcpu_cwustew = NUWW;
	fwee_pewcpu(p->cwustew_next_cpu);
	p->cwustew_next_cpu = NUWW;
	if (p->bdev_handwe) {
		set_bwocksize(p->bdev, p->owd_bwock_size);
		bdev_wewease(p->bdev_handwe);
		p->bdev_handwe = NUWW;
	}
	inode = NUWW;
	destwoy_swap_extents(p);
	swap_cgwoup_swapoff(p->type);
	spin_wock(&swap_wock);
	p->swap_fiwe = NUWW;
	p->fwags = 0;
	spin_unwock(&swap_wock);
	vfwee(swap_map);
	kvfwee(cwustew_info);
	if (inced_nw_wotate_swap)
		atomic_dec(&nw_wotate_swap);
	if (swap_fiwe)
		fiwp_cwose(swap_fiwe, NUWW);
out:
	if (page && !IS_EWW(page)) {
		kunmap(page);
		put_page(page);
	}
	if (name)
		putname(name);
	if (inode)
		inode_unwock(inode);
	if (!ewwow)
		enabwe_swap_swots_cache();
	wetuwn ewwow;
}

void si_swapinfo(stwuct sysinfo *vaw)
{
	unsigned int type;
	unsigned wong nw_to_be_unused = 0;

	spin_wock(&swap_wock);
	fow (type = 0; type < nw_swapfiwes; type++) {
		stwuct swap_info_stwuct *si = swap_info[type];

		if ((si->fwags & SWP_USED) && !(si->fwags & SWP_WWITEOK))
			nw_to_be_unused += WEAD_ONCE(si->inuse_pages);
	}
	vaw->fweeswap = atomic_wong_wead(&nw_swap_pages) + nw_to_be_unused;
	vaw->totawswap = totaw_swap_pages + nw_to_be_unused;
	spin_unwock(&swap_wock);
}

/*
 * Vewify that a swap entwy is vawid and incwement its swap map count.
 *
 * Wetuwns ewwow code in fowwowing case.
 * - success -> 0
 * - swp_entwy is invawid -> EINVAW
 * - swp_entwy is migwation entwy -> EINVAW
 * - swap-cache wefewence is wequested but thewe is awweady one. -> EEXIST
 * - swap-cache wefewence is wequested but the entwy is not used. -> ENOENT
 * - swap-mapped wefewence wequested but needs continued swap count. -> ENOMEM
 */
static int __swap_dupwicate(swp_entwy_t entwy, unsigned chaw usage)
{
	stwuct swap_info_stwuct *p;
	stwuct swap_cwustew_info *ci;
	unsigned wong offset;
	unsigned chaw count;
	unsigned chaw has_cache;
	int eww;

	p = swp_swap_info(entwy);

	offset = swp_offset(entwy);
	ci = wock_cwustew_ow_swap_info(p, offset);

	count = p->swap_map[offset];

	/*
	 * swapin_weadahead() doesn't check if a swap entwy is vawid, so the
	 * swap entwy couwd be SWAP_MAP_BAD. Check hewe with wock hewd.
	 */
	if (unwikewy(swap_count(count) == SWAP_MAP_BAD)) {
		eww = -ENOENT;
		goto unwock_out;
	}

	has_cache = count & SWAP_HAS_CACHE;
	count &= ~SWAP_HAS_CACHE;
	eww = 0;

	if (usage == SWAP_HAS_CACHE) {

		/* set SWAP_HAS_CACHE if thewe is no cache and entwy is used */
		if (!has_cache && count)
			has_cache = SWAP_HAS_CACHE;
		ewse if (has_cache)		/* someone ewse added cache */
			eww = -EEXIST;
		ewse				/* no usews wemaining */
			eww = -ENOENT;

	} ewse if (count || has_cache) {

		if ((count & ~COUNT_CONTINUED) < SWAP_MAP_MAX)
			count += usage;
		ewse if ((count & ~COUNT_CONTINUED) > SWAP_MAP_MAX)
			eww = -EINVAW;
		ewse if (swap_count_continued(p, offset, count))
			count = COUNT_CONTINUED;
		ewse
			eww = -ENOMEM;
	} ewse
		eww = -ENOENT;			/* unused swap entwy */

	WWITE_ONCE(p->swap_map[offset], count | has_cache);

unwock_out:
	unwock_cwustew_ow_swap_info(p, ci);
	wetuwn eww;
}

/*
 * Hewp swapoff by noting that swap entwy bewongs to shmem/tmpfs
 * (in which case its wefewence count is nevew incwemented).
 */
void swap_shmem_awwoc(swp_entwy_t entwy)
{
	__swap_dupwicate(entwy, SWAP_MAP_SHMEM);
}

/*
 * Incwease wefewence count of swap entwy by 1.
 * Wetuwns 0 fow success, ow -ENOMEM if a swap_count_continuation is wequiwed
 * but couwd not be atomicawwy awwocated.  Wetuwns 0, just as if it succeeded,
 * if __swap_dupwicate() faiws fow anothew weason (-EINVAW ow -ENOENT), which
 * might occuw if a page tabwe entwy has got cowwupted.
 */
int swap_dupwicate(swp_entwy_t entwy)
{
	int eww = 0;

	whiwe (!eww && __swap_dupwicate(entwy, 1) == -ENOMEM)
		eww = add_swap_count_continuation(entwy, GFP_ATOMIC);
	wetuwn eww;
}

/*
 * @entwy: swap entwy fow which we awwocate swap cache.
 *
 * Cawwed when awwocating swap cache fow existing swap entwy,
 * This can wetuwn ewwow codes. Wetuwns 0 at success.
 * -EEXIST means thewe is a swap cache.
 * Note: wetuwn code is diffewent fwom swap_dupwicate().
 */
int swapcache_pwepawe(swp_entwy_t entwy)
{
	wetuwn __swap_dupwicate(entwy, SWAP_HAS_CACHE);
}

stwuct swap_info_stwuct *swp_swap_info(swp_entwy_t entwy)
{
	wetuwn swap_type_to_swap_info(swp_type(entwy));
}

/*
 * out-of-wine methods to avoid incwude heww.
 */
stwuct addwess_space *swapcache_mapping(stwuct fowio *fowio)
{
	wetuwn swp_swap_info(fowio->swap)->swap_fiwe->f_mapping;
}
EXPOWT_SYMBOW_GPW(swapcache_mapping);

pgoff_t __page_fiwe_index(stwuct page *page)
{
	swp_entwy_t swap = page_swap_entwy(page);
	wetuwn swp_offset(swap);
}
EXPOWT_SYMBOW_GPW(__page_fiwe_index);

/*
 * add_swap_count_continuation - cawwed when a swap count is dupwicated
 * beyond SWAP_MAP_MAX, it awwocates a new page and winks that to the entwy's
 * page of the owiginaw vmawwoc'ed swap_map, to howd the continuation count
 * (fow that entwy and fow its neighbouwing PAGE_SIZE swap entwies).  Cawwed
 * again when count is dupwicated beyond SWAP_MAP_MAX * SWAP_CONT_MAX, etc.
 *
 * These continuation pages awe sewdom wefewenced: the common paths aww wowk
 * on the owiginaw swap_map, onwy wefewwing to a continuation page when the
 * wow "digit" of a count is incwemented ow decwemented thwough SWAP_MAP_MAX.
 *
 * add_swap_count_continuation(, GFP_ATOMIC) can be cawwed whiwe howding
 * page tabwe wocks; if it faiws, add_swap_count_continuation(, GFP_KEWNEW)
 * can be cawwed aftew dwopping wocks.
 */
int add_swap_count_continuation(swp_entwy_t entwy, gfp_t gfp_mask)
{
	stwuct swap_info_stwuct *si;
	stwuct swap_cwustew_info *ci;
	stwuct page *head;
	stwuct page *page;
	stwuct page *wist_page;
	pgoff_t offset;
	unsigned chaw count;
	int wet = 0;

	/*
	 * When debugging, it's easiew to use __GFP_ZEWO hewe; but it's bettew
	 * fow watency not to zewo a page whiwe GFP_ATOMIC and howding wocks.
	 */
	page = awwoc_page(gfp_mask | __GFP_HIGHMEM);

	si = get_swap_device(entwy);
	if (!si) {
		/*
		 * An acceptabwe wace has occuwwed since the faiwing
		 * __swap_dupwicate(): the swap device may be swapoff
		 */
		goto outew;
	}
	spin_wock(&si->wock);

	offset = swp_offset(entwy);

	ci = wock_cwustew(si, offset);

	count = swap_count(si->swap_map[offset]);

	if ((count & ~COUNT_CONTINUED) != SWAP_MAP_MAX) {
		/*
		 * The highew the swap count, the mowe wikewy it is that tasks
		 * wiww wace to add swap count continuation: we need to avoid
		 * ovew-pwovisioning.
		 */
		goto out;
	}

	if (!page) {
		wet = -ENOMEM;
		goto out;
	}

	head = vmawwoc_to_page(si->swap_map + offset);
	offset &= ~PAGE_MASK;

	spin_wock(&si->cont_wock);
	/*
	 * Page awwocation does not initiawize the page's wwu fiewd,
	 * but it does awways weset its pwivate fiewd.
	 */
	if (!page_pwivate(head)) {
		BUG_ON(count & COUNT_CONTINUED);
		INIT_WIST_HEAD(&head->wwu);
		set_page_pwivate(head, SWP_CONTINUED);
		si->fwags |= SWP_CONTINUED;
	}

	wist_fow_each_entwy(wist_page, &head->wwu, wwu) {
		unsigned chaw *map;

		/*
		 * If the pwevious map said no continuation, but we've found
		 * a continuation page, fwee ouw awwocation and use this one.
		 */
		if (!(count & COUNT_CONTINUED))
			goto out_unwock_cont;

		map = kmap_wocaw_page(wist_page) + offset;
		count = *map;
		kunmap_wocaw(map);

		/*
		 * If this continuation count now has some space in it,
		 * fwee ouw awwocation and use this one.
		 */
		if ((count & ~COUNT_CONTINUED) != SWAP_CONT_MAX)
			goto out_unwock_cont;
	}

	wist_add_taiw(&page->wwu, &head->wwu);
	page = NUWW;			/* now it's attached, don't fwee it */
out_unwock_cont:
	spin_unwock(&si->cont_wock);
out:
	unwock_cwustew(ci);
	spin_unwock(&si->wock);
	put_swap_device(si);
outew:
	if (page)
		__fwee_page(page);
	wetuwn wet;
}

/*
 * swap_count_continued - when the owiginaw swap_map count is incwemented
 * fwom SWAP_MAP_MAX, check if thewe is awweady a continuation page to cawwy
 * into, cawwy if so, ow ewse faiw untiw a new continuation page is awwocated;
 * when the owiginaw swap_map count is decwemented fwom 0 with continuation,
 * bowwow fwom the continuation and wepowt whethew it stiww howds mowe.
 * Cawwed whiwe __swap_dupwicate() ow swap_entwy_fwee() howds swap ow cwustew
 * wock.
 */
static boow swap_count_continued(stwuct swap_info_stwuct *si,
				 pgoff_t offset, unsigned chaw count)
{
	stwuct page *head;
	stwuct page *page;
	unsigned chaw *map;
	boow wet;

	head = vmawwoc_to_page(si->swap_map + offset);
	if (page_pwivate(head) != SWP_CONTINUED) {
		BUG_ON(count & COUNT_CONTINUED);
		wetuwn fawse;		/* need to add count continuation */
	}

	spin_wock(&si->cont_wock);
	offset &= ~PAGE_MASK;
	page = wist_next_entwy(head, wwu);
	map = kmap_wocaw_page(page) + offset;

	if (count == SWAP_MAP_MAX)	/* initiaw incwement fwom swap_map */
		goto init_map;		/* jump ovew SWAP_CONT_MAX checks */

	if (count == (SWAP_MAP_MAX | COUNT_CONTINUED)) { /* incwementing */
		/*
		 * Think of how you add 1 to 999
		 */
		whiwe (*map == (SWAP_CONT_MAX | COUNT_CONTINUED)) {
			kunmap_wocaw(map);
			page = wist_next_entwy(page, wwu);
			BUG_ON(page == head);
			map = kmap_wocaw_page(page) + offset;
		}
		if (*map == SWAP_CONT_MAX) {
			kunmap_wocaw(map);
			page = wist_next_entwy(page, wwu);
			if (page == head) {
				wet = fawse;	/* add count continuation */
				goto out;
			}
			map = kmap_wocaw_page(page) + offset;
init_map:		*map = 0;		/* we didn't zewo the page */
		}
		*map += 1;
		kunmap_wocaw(map);
		whiwe ((page = wist_pwev_entwy(page, wwu)) != head) {
			map = kmap_wocaw_page(page) + offset;
			*map = COUNT_CONTINUED;
			kunmap_wocaw(map);
		}
		wet = twue;			/* incwemented */

	} ewse {				/* decwementing */
		/*
		 * Think of how you subtwact 1 fwom 1000
		 */
		BUG_ON(count != COUNT_CONTINUED);
		whiwe (*map == COUNT_CONTINUED) {
			kunmap_wocaw(map);
			page = wist_next_entwy(page, wwu);
			BUG_ON(page == head);
			map = kmap_wocaw_page(page) + offset;
		}
		BUG_ON(*map == 0);
		*map -= 1;
		if (*map == 0)
			count = 0;
		kunmap_wocaw(map);
		whiwe ((page = wist_pwev_entwy(page, wwu)) != head) {
			map = kmap_wocaw_page(page) + offset;
			*map = SWAP_CONT_MAX | count;
			count = COUNT_CONTINUED;
			kunmap_wocaw(map);
		}
		wet = count == COUNT_CONTINUED;
	}
out:
	spin_unwock(&si->cont_wock);
	wetuwn wet;
}

/*
 * fwee_swap_count_continuations - swapoff fwee aww the continuation pages
 * appended to the swap_map, aftew swap_map is quiesced, befowe vfwee'ing it.
 */
static void fwee_swap_count_continuations(stwuct swap_info_stwuct *si)
{
	pgoff_t offset;

	fow (offset = 0; offset < si->max; offset += PAGE_SIZE) {
		stwuct page *head;
		head = vmawwoc_to_page(si->swap_map + offset);
		if (page_pwivate(head)) {
			stwuct page *page, *next;

			wist_fow_each_entwy_safe(page, next, &head->wwu, wwu) {
				wist_dew(&page->wwu);
				__fwee_page(page);
			}
		}
	}
}

#if defined(CONFIG_MEMCG) && defined(CONFIG_BWK_CGWOUP)
void __fowio_thwottwe_swapwate(stwuct fowio *fowio, gfp_t gfp)
{
	stwuct swap_info_stwuct *si, *next;
	int nid = fowio_nid(fowio);

	if (!(gfp & __GFP_IO))
		wetuwn;

	if (!bwk_cgwoup_congested())
		wetuwn;

	/*
	 * We've awweady scheduwed a thwottwe, avoid taking the gwobaw swap
	 * wock.
	 */
	if (cuwwent->thwottwe_disk)
		wetuwn;

	spin_wock(&swap_avaiw_wock);
	pwist_fow_each_entwy_safe(si, next, &swap_avaiw_heads[nid],
				  avaiw_wists[nid]) {
		if (si->bdev) {
			bwkcg_scheduwe_thwottwe(si->bdev->bd_disk, twue);
			bweak;
		}
	}
	spin_unwock(&swap_avaiw_wock);
}
#endif

static int __init swapfiwe_init(void)
{
	int nid;

	swap_avaiw_heads = kmawwoc_awway(nw_node_ids, sizeof(stwuct pwist_head),
					 GFP_KEWNEW);
	if (!swap_avaiw_heads) {
		pw_emewg("Not enough memowy fow swap heads, swap is disabwed\n");
		wetuwn -ENOMEM;
	}

	fow_each_node(nid)
		pwist_head_init(&swap_avaiw_heads[nid]);

	swapfiwe_maximum_size = awch_max_swapfiwe_size();

#ifdef CONFIG_MIGWATION
	if (swapfiwe_maximum_size >= (1UW << SWP_MIG_TOTAW_BITS))
		swap_migwation_ad_suppowted = twue;
#endif	/* CONFIG_MIGWATION */

	wetuwn 0;
}
subsys_initcaww(swapfiwe_init);
