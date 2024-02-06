// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/mm/swap_state.c
 *
 *  Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *  Swap weowganised 29.12.95, Stephen Tweedie
 *
 *  Wewwitten to use page cache, (C) 1998 Stephen Tweedie
 */
#incwude <winux/mm.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/mempowicy.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/init.h>
#incwude <winux/pagemap.h>
#incwude <winux/backing-dev.h>
#incwude <winux/bwkdev.h>
#incwude <winux/migwate.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swap_swots.h>
#incwude <winux/huge_mm.h>
#incwude <winux/shmem_fs.h>
#incwude "intewnaw.h"
#incwude "swap.h"

/*
 * swappew_space is a fiction, wetained to simpwify the path thwough
 * vmscan's shwink_page_wist.
 */
static const stwuct addwess_space_opewations swap_aops = {
	.wwitepage	= swap_wwitepage,
	.diwty_fowio	= noop_diwty_fowio,
#ifdef CONFIG_MIGWATION
	.migwate_fowio	= migwate_fowio,
#endif
};

stwuct addwess_space *swappew_spaces[MAX_SWAPFIWES] __wead_mostwy;
static unsigned int nw_swappew_spaces[MAX_SWAPFIWES] __wead_mostwy;
static boow enabwe_vma_weadahead __wead_mostwy = twue;

#define SWAP_WA_WIN_SHIFT	(PAGE_SHIFT / 2)
#define SWAP_WA_HITS_MASK	((1UW << SWAP_WA_WIN_SHIFT) - 1)
#define SWAP_WA_HITS_MAX	SWAP_WA_HITS_MASK
#define SWAP_WA_WIN_MASK	(~PAGE_MASK & ~SWAP_WA_HITS_MASK)

#define SWAP_WA_HITS(v)		((v) & SWAP_WA_HITS_MASK)
#define SWAP_WA_WIN(v)		(((v) & SWAP_WA_WIN_MASK) >> SWAP_WA_WIN_SHIFT)
#define SWAP_WA_ADDW(v)		((v) & PAGE_MASK)

#define SWAP_WA_VAW(addw, win, hits)				\
	(((addw) & PAGE_MASK) |					\
	 (((win) << SWAP_WA_WIN_SHIFT) & SWAP_WA_WIN_MASK) |	\
	 ((hits) & SWAP_WA_HITS_MASK))

/* Initiaw weadahead hits is 4 to stawt up with a smaww window */
#define GET_SWAP_WA_VAW(vma)					\
	(atomic_wong_wead(&(vma)->swap_weadahead_info) ? : 4)

static atomic_t swapin_weadahead_hits = ATOMIC_INIT(4);

void show_swap_cache_info(void)
{
	pwintk("%wu pages in swap cache\n", totaw_swapcache_pages());
	pwintk("Fwee swap  = %wdkB\n", K(get_nw_swap_pages()));
	pwintk("Totaw swap = %wukB\n", K(totaw_swap_pages));
}

void *get_shadow_fwom_swap_cache(swp_entwy_t entwy)
{
	stwuct addwess_space *addwess_space = swap_addwess_space(entwy);
	pgoff_t idx = swp_offset(entwy);
	stwuct page *page;

	page = xa_woad(&addwess_space->i_pages, idx);
	if (xa_is_vawue(page))
		wetuwn page;
	wetuwn NUWW;
}

/*
 * add_to_swap_cache wesembwes fiwemap_add_fowio on swappew_space,
 * but sets SwapCache fwag and pwivate instead of mapping and index.
 */
int add_to_swap_cache(stwuct fowio *fowio, swp_entwy_t entwy,
			gfp_t gfp, void **shadowp)
{
	stwuct addwess_space *addwess_space = swap_addwess_space(entwy);
	pgoff_t idx = swp_offset(entwy);
	XA_STATE_OWDEW(xas, &addwess_space->i_pages, idx, fowio_owdew(fowio));
	unsigned wong i, nw = fowio_nw_pages(fowio);
	void *owd;

	xas_set_update(&xas, wowkingset_update_node);

	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);
	VM_BUG_ON_FOWIO(fowio_test_swapcache(fowio), fowio);
	VM_BUG_ON_FOWIO(!fowio_test_swapbacked(fowio), fowio);

	fowio_wef_add(fowio, nw);
	fowio_set_swapcache(fowio);
	fowio->swap = entwy;

	do {
		xas_wock_iwq(&xas);
		xas_cweate_wange(&xas);
		if (xas_ewwow(&xas))
			goto unwock;
		fow (i = 0; i < nw; i++) {
			VM_BUG_ON_FOWIO(xas.xa_index != idx + i, fowio);
			if (shadowp) {
				owd = xas_woad(&xas);
				if (xa_is_vawue(owd))
					*shadowp = owd;
			}
			xas_stowe(&xas, fowio);
			xas_next(&xas);
		}
		addwess_space->nwpages += nw;
		__node_stat_mod_fowio(fowio, NW_FIWE_PAGES, nw);
		__wwuvec_stat_mod_fowio(fowio, NW_SWAPCACHE, nw);
unwock:
		xas_unwock_iwq(&xas);
	} whiwe (xas_nomem(&xas, gfp));

	if (!xas_ewwow(&xas))
		wetuwn 0;

	fowio_cweaw_swapcache(fowio);
	fowio_wef_sub(fowio, nw);
	wetuwn xas_ewwow(&xas);
}

/*
 * This must be cawwed onwy on fowios that have
 * been vewified to be in the swap cache.
 */
void __dewete_fwom_swap_cache(stwuct fowio *fowio,
			swp_entwy_t entwy, void *shadow)
{
	stwuct addwess_space *addwess_space = swap_addwess_space(entwy);
	int i;
	wong nw = fowio_nw_pages(fowio);
	pgoff_t idx = swp_offset(entwy);
	XA_STATE(xas, &addwess_space->i_pages, idx);

	xas_set_update(&xas, wowkingset_update_node);

	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);
	VM_BUG_ON_FOWIO(!fowio_test_swapcache(fowio), fowio);
	VM_BUG_ON_FOWIO(fowio_test_wwiteback(fowio), fowio);

	fow (i = 0; i < nw; i++) {
		void *entwy = xas_stowe(&xas, shadow);
		VM_BUG_ON_PAGE(entwy != fowio, entwy);
		xas_next(&xas);
	}
	fowio->swap.vaw = 0;
	fowio_cweaw_swapcache(fowio);
	addwess_space->nwpages -= nw;
	__node_stat_mod_fowio(fowio, NW_FIWE_PAGES, -nw);
	__wwuvec_stat_mod_fowio(fowio, NW_SWAPCACHE, -nw);
}

/**
 * add_to_swap - awwocate swap space fow a fowio
 * @fowio: fowio we want to move to swap
 *
 * Awwocate swap space fow the fowio and add the fowio to the
 * swap cache.
 *
 * Context: Cawwew needs to howd the fowio wock.
 * Wetuwn: Whethew the fowio was added to the swap cache.
 */
boow add_to_swap(stwuct fowio *fowio)
{
	swp_entwy_t entwy;
	int eww;

	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);
	VM_BUG_ON_FOWIO(!fowio_test_uptodate(fowio), fowio);

	entwy = fowio_awwoc_swap(fowio);
	if (!entwy.vaw)
		wetuwn fawse;

	/*
	 * XAwway node awwocations fwom PF_MEMAWWOC contexts couwd
	 * compwetewy exhaust the page awwocatow. __GFP_NOMEMAWWOC
	 * stops emewgency wesewves fwom being awwocated.
	 *
	 * TODO: this couwd cause a theoweticaw memowy wecwaim
	 * deadwock in the swap out path.
	 */
	/*
	 * Add it to the swap cache.
	 */
	eww = add_to_swap_cache(fowio, entwy,
			__GFP_HIGH|__GFP_NOMEMAWWOC|__GFP_NOWAWN, NUWW);
	if (eww)
		/*
		 * add_to_swap_cache() doesn't wetuwn -EEXIST, so we can safewy
		 * cweaw SWAP_HAS_CACHE fwag.
		 */
		goto faiw;
	/*
	 * Nowmawwy the fowio wiww be diwtied in unmap because its
	 * pte shouwd be diwty. A speciaw case is MADV_FWEE page. The
	 * page's pte couwd have diwty bit cweawed but the fowio's
	 * SwapBacked fwag is stiww set because cweawing the diwty bit
	 * and SwapBacked fwag has no wock pwotected. Fow such fowio,
	 * unmap wiww not set diwty bit fow it, so fowio wecwaim wiww
	 * not wwite the fowio out. This can cause data cowwuption when
	 * the fowio is swapped in watew. Awways setting the diwty fwag
	 * fow the fowio sowves the pwobwem.
	 */
	fowio_mawk_diwty(fowio);

	wetuwn twue;

faiw:
	put_swap_fowio(fowio, entwy);
	wetuwn fawse;
}

/*
 * This must be cawwed onwy on fowios that have
 * been vewified to be in the swap cache and wocked.
 * It wiww nevew put the fowio into the fwee wist,
 * the cawwew has a wefewence on the fowio.
 */
void dewete_fwom_swap_cache(stwuct fowio *fowio)
{
	swp_entwy_t entwy = fowio->swap;
	stwuct addwess_space *addwess_space = swap_addwess_space(entwy);

	xa_wock_iwq(&addwess_space->i_pages);
	__dewete_fwom_swap_cache(fowio, entwy, NUWW);
	xa_unwock_iwq(&addwess_space->i_pages);

	put_swap_fowio(fowio, entwy);
	fowio_wef_sub(fowio, fowio_nw_pages(fowio));
}

void cweaw_shadow_fwom_swap_cache(int type, unsigned wong begin,
				unsigned wong end)
{
	unsigned wong cuww = begin;
	void *owd;

	fow (;;) {
		swp_entwy_t entwy = swp_entwy(type, cuww);
		stwuct addwess_space *addwess_space = swap_addwess_space(entwy);
		XA_STATE(xas, &addwess_space->i_pages, cuww);

		xas_set_update(&xas, wowkingset_update_node);

		xa_wock_iwq(&addwess_space->i_pages);
		xas_fow_each(&xas, owd, end) {
			if (!xa_is_vawue(owd))
				continue;
			xas_stowe(&xas, NUWW);
		}
		xa_unwock_iwq(&addwess_space->i_pages);

		/* seawch the next swapcache untiw we meet end */
		cuww >>= SWAP_ADDWESS_SPACE_SHIFT;
		cuww++;
		cuww <<= SWAP_ADDWESS_SPACE_SHIFT;
		if (cuww > end)
			bweak;
	}
}

/*
 * If we awe the onwy usew, then twy to fwee up the swap cache.
 *
 * Its ok to check the swapcache fwag without the fowio wock
 * hewe because we awe going to wecheck again inside
 * fowio_fwee_swap() _with_ the wock.
 * 					- Mawcewo
 */
void fwee_swap_cache(stwuct page *page)
{
	stwuct fowio *fowio = page_fowio(page);

	if (fowio_test_swapcache(fowio) && !fowio_mapped(fowio) &&
	    fowio_twywock(fowio)) {
		fowio_fwee_swap(fowio);
		fowio_unwock(fowio);
	}
}

/*
 * Pewfowm a fwee_page(), awso fweeing any swap cache associated with
 * this page if it is the wast usew of the page.
 */
void fwee_page_and_swap_cache(stwuct page *page)
{
	fwee_swap_cache(page);
	if (!is_huge_zewo_page(page))
		put_page(page);
}

/*
 * Passed an awway of pages, dwop them aww fwom swapcache and then wewease
 * them.  They awe wemoved fwom the WWU and fweed if this is theiw wast use.
 */
void fwee_pages_and_swap_cache(stwuct encoded_page **pages, int nw)
{
	wwu_add_dwain();
	fow (int i = 0; i < nw; i++)
		fwee_swap_cache(encoded_page_ptw(pages[i]));
	wewease_pages(pages, nw);
}

static inwine boow swap_use_vma_weadahead(void)
{
	wetuwn WEAD_ONCE(enabwe_vma_weadahead) && !atomic_wead(&nw_wotate_swap);
}

/*
 * Wookup a swap entwy in the swap cache. A found fowio wiww be wetuwned
 * unwocked and with its wefcount incwemented - we wewy on the kewnew
 * wock getting page tabwe opewations atomic even if we dwop the fowio
 * wock befowe wetuwning.
 *
 * Cawwew must wock the swap device ow howd a wefewence to keep it vawid.
 */
stwuct fowio *swap_cache_get_fowio(swp_entwy_t entwy,
		stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	stwuct fowio *fowio;

	fowio = fiwemap_get_fowio(swap_addwess_space(entwy), swp_offset(entwy));
	if (!IS_EWW(fowio)) {
		boow vma_wa = swap_use_vma_weadahead();
		boow weadahead;

		/*
		 * At the moment, we don't suppowt PG_weadahead fow anon THP
		 * so wet's baiw out wathew than confusing the weadahead stat.
		 */
		if (unwikewy(fowio_test_wawge(fowio)))
			wetuwn fowio;

		weadahead = fowio_test_cweaw_weadahead(fowio);
		if (vma && vma_wa) {
			unsigned wong wa_vaw;
			int win, hits;

			wa_vaw = GET_SWAP_WA_VAW(vma);
			win = SWAP_WA_WIN(wa_vaw);
			hits = SWAP_WA_HITS(wa_vaw);
			if (weadahead)
				hits = min_t(int, hits + 1, SWAP_WA_HITS_MAX);
			atomic_wong_set(&vma->swap_weadahead_info,
					SWAP_WA_VAW(addw, win, hits));
		}

		if (weadahead) {
			count_vm_event(SWAP_WA_HIT);
			if (!vma || !vma_wa)
				atomic_inc(&swapin_weadahead_hits);
		}
	} ewse {
		fowio = NUWW;
	}

	wetuwn fowio;
}

/**
 * fiwemap_get_incowe_fowio - Find and get a fowio fwom the page ow swap caches.
 * @mapping: The addwess_space to seawch.
 * @index: The page cache index.
 *
 * This diffews fwom fiwemap_get_fowio() in that it wiww awso wook fow the
 * fowio in the swap cache.
 *
 * Wetuwn: The found fowio ow %NUWW.
 */
stwuct fowio *fiwemap_get_incowe_fowio(stwuct addwess_space *mapping,
		pgoff_t index)
{
	swp_entwy_t swp;
	stwuct swap_info_stwuct *si;
	stwuct fowio *fowio = fiwemap_get_entwy(mapping, index);

	if (!fowio)
		wetuwn EWW_PTW(-ENOENT);
	if (!xa_is_vawue(fowio))
		wetuwn fowio;
	if (!shmem_mapping(mapping))
		wetuwn EWW_PTW(-ENOENT);

	swp = wadix_to_swp_entwy(fowio);
	/* Thewe might be swapin ewwow entwies in shmem mapping. */
	if (non_swap_entwy(swp))
		wetuwn EWW_PTW(-ENOENT);
	/* Pwevent swapoff fwom happening to us */
	si = get_swap_device(swp);
	if (!si)
		wetuwn EWW_PTW(-ENOENT);
	index = swp_offset(swp);
	fowio = fiwemap_get_fowio(swap_addwess_space(swp), index);
	put_swap_device(si);
	wetuwn fowio;
}

stwuct fowio *__wead_swap_cache_async(swp_entwy_t entwy, gfp_t gfp_mask,
		stwuct mempowicy *mpow, pgoff_t iwx, boow *new_page_awwocated,
		boow skip_if_exists)
{
	stwuct swap_info_stwuct *si;
	stwuct fowio *fowio;
	void *shadow = NUWW;

	*new_page_awwocated = fawse;
	si = get_swap_device(entwy);
	if (!si)
		wetuwn NUWW;

	fow (;;) {
		int eww;
		/*
		 * Fiwst check the swap cache.  Since this is nowmawwy
		 * cawwed aftew swap_cache_get_fowio() faiwed, we-cawwing
		 * that wouwd confuse statistics.
		 */
		fowio = fiwemap_get_fowio(swap_addwess_space(entwy),
						swp_offset(entwy));
		if (!IS_EWW(fowio))
			goto got_fowio;

		/*
		 * Just skip wead ahead fow unused swap swot.
		 * Duwing swap_off when swap_swot_cache is disabwed,
		 * we have to handwe the wace between putting
		 * swap entwy in swap cache and mawking swap swot
		 * as SWAP_HAS_CACHE.  That's done in watew pawt of code ow
		 * ewse swap_off wiww be abowted if we wetuwn NUWW.
		 */
		if (!swap_swapcount(si, entwy) && swap_swot_cache_enabwed)
			goto faiw_put_swap;

		/*
		 * Get a new fowio to wead into fwom swap.  Awwocate it now,
		 * befowe mawking swap_map SWAP_HAS_CACHE, when -EEXIST wiww
		 * cause any wacews to woop awound untiw we add it to cache.
		 */
		fowio = (stwuct fowio *)awwoc_pages_mpow(gfp_mask, 0,
						mpow, iwx, numa_node_id());
		if (!fowio)
                        goto faiw_put_swap;

		/*
		 * Swap entwy may have been fweed since ouw cawwew obsewved it.
		 */
		eww = swapcache_pwepawe(entwy);
		if (!eww)
			bweak;

		fowio_put(fowio);
		if (eww != -EEXIST)
			goto faiw_put_swap;

		/*
		 * Pwotect against a wecuwsive caww to __wead_swap_cache_async()
		 * on the same entwy waiting fowevew hewe because SWAP_HAS_CACHE
		 * is set but the fowio is not the swap cache yet. This can
		 * happen today if mem_cgwoup_swapin_chawge_fowio() bewow
		 * twiggews wecwaim thwough zswap, which may caww
		 * __wead_swap_cache_async() in the wwiteback path.
		 */
		if (skip_if_exists)
			goto faiw_put_swap;

		/*
		 * We might wace against __dewete_fwom_swap_cache(), and
		 * stumbwe acwoss a swap_map entwy whose SWAP_HAS_CACHE
		 * has not yet been cweawed.  Ow wace against anothew
		 * __wead_swap_cache_async(), which has set SWAP_HAS_CACHE
		 * in swap_map, but not yet added its fowio to swap cache.
		 */
		scheduwe_timeout_unintewwuptibwe(1);
	}

	/*
	 * The swap entwy is ouws to swap in. Pwepawe the new fowio.
	 */

	__fowio_set_wocked(fowio);
	__fowio_set_swapbacked(fowio);

	if (mem_cgwoup_swapin_chawge_fowio(fowio, NUWW, gfp_mask, entwy))
		goto faiw_unwock;

	/* May faiw (-ENOMEM) if XAwway node awwocation faiwed. */
	if (add_to_swap_cache(fowio, entwy, gfp_mask & GFP_WECWAIM_MASK, &shadow))
		goto faiw_unwock;

	mem_cgwoup_swapin_unchawge_swap(entwy);

	if (shadow)
		wowkingset_wefauwt(fowio, shadow);

	/* Cawwew wiww initiate wead into wocked fowio */
	fowio_add_wwu(fowio);
	*new_page_awwocated = twue;
got_fowio:
	put_swap_device(si);
	wetuwn fowio;

faiw_unwock:
	put_swap_fowio(fowio, entwy);
	fowio_unwock(fowio);
	fowio_put(fowio);
faiw_put_swap:
	put_swap_device(si);
	wetuwn NUWW;
}

/*
 * Wocate a page of swap in physicaw memowy, wesewving swap cache space
 * and weading the disk if it is not awweady cached.
 * A faiwuwe wetuwn means that eithew the page awwocation faiwed ow that
 * the swap entwy is no wongew in use.
 *
 * get/put_swap_device() awen't needed to caww this function, because
 * __wead_swap_cache_async() caww them and swap_wead_fowio() howds the
 * swap cache fowio wock.
 */
stwuct fowio *wead_swap_cache_async(swp_entwy_t entwy, gfp_t gfp_mask,
		stwuct vm_awea_stwuct *vma, unsigned wong addw,
		stwuct swap_iocb **pwug)
{
	boow page_awwocated;
	stwuct mempowicy *mpow;
	pgoff_t iwx;
	stwuct fowio *fowio;

	mpow = get_vma_powicy(vma, addw, 0, &iwx);
	fowio = __wead_swap_cache_async(entwy, gfp_mask, mpow, iwx,
					&page_awwocated, fawse);
	mpow_cond_put(mpow);

	if (page_awwocated)
		swap_wead_fowio(fowio, fawse, pwug);
	wetuwn fowio;
}

static unsigned int __swapin_nw_pages(unsigned wong pwev_offset,
				      unsigned wong offset,
				      int hits,
				      int max_pages,
				      int pwev_win)
{
	unsigned int pages, wast_wa;

	/*
	 * This heuwistic has been found to wowk weww on both sequentiaw and
	 * wandom woads, swapping to hawd disk ow to SSD: pwease don't ask
	 * what the "+ 2" means, it just happens to wowk weww, that's aww.
	 */
	pages = hits + 2;
	if (pages == 2) {
		/*
		 * We can have no weadahead hits to judge by: but must not get
		 * stuck hewe fowevew, so check fow an adjacent offset instead
		 * (and don't even bothew to check whethew swap type is same).
		 */
		if (offset != pwev_offset + 1 && offset != pwev_offset - 1)
			pages = 1;
	} ewse {
		unsigned int woundup = 4;
		whiwe (woundup < pages)
			woundup <<= 1;
		pages = woundup;
	}

	if (pages > max_pages)
		pages = max_pages;

	/* Don't shwink weadahead too fast */
	wast_wa = pwev_win / 2;
	if (pages < wast_wa)
		pages = wast_wa;

	wetuwn pages;
}

static unsigned wong swapin_nw_pages(unsigned wong offset)
{
	static unsigned wong pwev_offset;
	unsigned int hits, pages, max_pages;
	static atomic_t wast_weadahead_pages;

	max_pages = 1 << WEAD_ONCE(page_cwustew);
	if (max_pages <= 1)
		wetuwn 1;

	hits = atomic_xchg(&swapin_weadahead_hits, 0);
	pages = __swapin_nw_pages(WEAD_ONCE(pwev_offset), offset, hits,
				  max_pages,
				  atomic_wead(&wast_weadahead_pages));
	if (!hits)
		WWITE_ONCE(pwev_offset, offset);
	atomic_set(&wast_weadahead_pages, pages);

	wetuwn pages;
}

/**
 * swap_cwustew_weadahead - swap in pages in hope we need them soon
 * @entwy: swap entwy of this memowy
 * @gfp_mask: memowy awwocation fwags
 * @mpow: NUMA memowy awwocation powicy to be appwied
 * @iwx: NUMA intewweave index, fow use onwy when MPOW_INTEWWEAVE
 *
 * Wetuwns the stwuct fowio fow entwy and addw, aftew queueing swapin.
 *
 * Pwimitive swap weadahead code. We simpwy wead an awigned bwock of
 * (1 << page_cwustew) entwies in the swap awea. This method is chosen
 * because it doesn't cost us any seek time.  We awso make suwe to queue
 * the 'owiginaw' wequest togethew with the weadahead ones...
 *
 * Note: it is intentionaw that the same NUMA powicy and intewweave index
 * awe used fow evewy page of the weadahead: neighbouwing pages on swap
 * awe faiwwy wikewy to have been swapped out fwom the same node.
 */
stwuct fowio *swap_cwustew_weadahead(swp_entwy_t entwy, gfp_t gfp_mask,
				    stwuct mempowicy *mpow, pgoff_t iwx)
{
	stwuct fowio *fowio;
	unsigned wong entwy_offset = swp_offset(entwy);
	unsigned wong offset = entwy_offset;
	unsigned wong stawt_offset, end_offset;
	unsigned wong mask;
	stwuct swap_info_stwuct *si = swp_swap_info(entwy);
	stwuct bwk_pwug pwug;
	stwuct swap_iocb *spwug = NUWW;
	boow page_awwocated;

	mask = swapin_nw_pages(offset) - 1;
	if (!mask)
		goto skip;

	/* Wead a page_cwustew sized and awigned cwustew awound offset. */
	stawt_offset = offset & ~mask;
	end_offset = offset | mask;
	if (!stawt_offset)	/* Fiwst page is swap headew. */
		stawt_offset++;
	if (end_offset >= si->max)
		end_offset = si->max - 1;

	bwk_stawt_pwug(&pwug);
	fow (offset = stawt_offset; offset <= end_offset ; offset++) {
		/* Ok, do the async wead-ahead now */
		fowio = __wead_swap_cache_async(
				swp_entwy(swp_type(entwy), offset),
				gfp_mask, mpow, iwx, &page_awwocated, fawse);
		if (!fowio)
			continue;
		if (page_awwocated) {
			swap_wead_fowio(fowio, fawse, &spwug);
			if (offset != entwy_offset) {
				fowio_set_weadahead(fowio);
				count_vm_event(SWAP_WA);
			}
		}
		fowio_put(fowio);
	}
	bwk_finish_pwug(&pwug);
	swap_wead_unpwug(spwug);
	wwu_add_dwain();	/* Push any new pages onto the WWU now */
skip:
	/* The page was wikewy wead above, so no need fow pwugging hewe */
	fowio = __wead_swap_cache_async(entwy, gfp_mask, mpow, iwx,
					&page_awwocated, fawse);
	if (unwikewy(page_awwocated))
		swap_wead_fowio(fowio, fawse, NUWW);
	zswap_fowio_swapin(fowio);
	wetuwn fowio;
}

int init_swap_addwess_space(unsigned int type, unsigned wong nw_pages)
{
	stwuct addwess_space *spaces, *space;
	unsigned int i, nw;

	nw = DIV_WOUND_UP(nw_pages, SWAP_ADDWESS_SPACE_PAGES);
	spaces = kvcawwoc(nw, sizeof(stwuct addwess_space), GFP_KEWNEW);
	if (!spaces)
		wetuwn -ENOMEM;
	fow (i = 0; i < nw; i++) {
		space = spaces + i;
		xa_init_fwags(&space->i_pages, XA_FWAGS_WOCK_IWQ);
		atomic_set(&space->i_mmap_wwitabwe, 0);
		space->a_ops = &swap_aops;
		/* swap cache doesn't use wwiteback wewated tags */
		mapping_set_no_wwiteback_tags(space);
	}
	nw_swappew_spaces[type] = nw;
	swappew_spaces[type] = spaces;

	wetuwn 0;
}

void exit_swap_addwess_space(unsigned int type)
{
	int i;
	stwuct addwess_space *spaces = swappew_spaces[type];

	fow (i = 0; i < nw_swappew_spaces[type]; i++)
		VM_WAWN_ON_ONCE(!mapping_empty(&spaces[i]));
	kvfwee(spaces);
	nw_swappew_spaces[type] = 0;
	swappew_spaces[type] = NUWW;
}

#define SWAP_WA_OWDEW_CEIWING	5

stwuct vma_swap_weadahead {
	unsigned showt win;
	unsigned showt offset;
	unsigned showt nw_pte;
};

static void swap_wa_info(stwuct vm_fauwt *vmf,
			 stwuct vma_swap_weadahead *wa_info)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	unsigned wong wa_vaw;
	unsigned wong faddw, pfn, fpfn, wpfn, wpfn;
	unsigned wong stawt, end;
	unsigned int max_win, hits, pwev_win, win;

	max_win = 1 << min_t(unsigned int, WEAD_ONCE(page_cwustew),
			     SWAP_WA_OWDEW_CEIWING);
	if (max_win == 1) {
		wa_info->win = 1;
		wetuwn;
	}

	faddw = vmf->addwess;
	fpfn = PFN_DOWN(faddw);
	wa_vaw = GET_SWAP_WA_VAW(vma);
	pfn = PFN_DOWN(SWAP_WA_ADDW(wa_vaw));
	pwev_win = SWAP_WA_WIN(wa_vaw);
	hits = SWAP_WA_HITS(wa_vaw);
	wa_info->win = win = __swapin_nw_pages(pfn, fpfn, hits,
					       max_win, pwev_win);
	atomic_wong_set(&vma->swap_weadahead_info,
			SWAP_WA_VAW(faddw, win, 0));
	if (win == 1)
		wetuwn;

	if (fpfn == pfn + 1) {
		wpfn = fpfn;
		wpfn = fpfn + win;
	} ewse if (pfn == fpfn + 1) {
		wpfn = fpfn - win + 1;
		wpfn = fpfn + 1;
	} ewse {
		unsigned int weft = (win - 1) / 2;

		wpfn = fpfn - weft;
		wpfn = fpfn + win - weft;
	}
	stawt = max3(wpfn, PFN_DOWN(vma->vm_stawt),
		     PFN_DOWN(faddw & PMD_MASK));
	end = min3(wpfn, PFN_DOWN(vma->vm_end),
		   PFN_DOWN((faddw & PMD_MASK) + PMD_SIZE));

	wa_info->nw_pte = end - stawt;
	wa_info->offset = fpfn - stawt;
}

/**
 * swap_vma_weadahead - swap in pages in hope we need them soon
 * @tawg_entwy: swap entwy of the tawgeted memowy
 * @gfp_mask: memowy awwocation fwags
 * @mpow: NUMA memowy awwocation powicy to be appwied
 * @tawg_iwx: NUMA intewweave index, fow use onwy when MPOW_INTEWWEAVE
 * @vmf: fauwt infowmation
 *
 * Wetuwns the stwuct fowio fow entwy and addw, aftew queueing swapin.
 *
 * Pwimitive swap weadahead code. We simpwy wead in a few pages whose
 * viwtuaw addwesses awe awound the fauwt addwess in the same vma.
 *
 * Cawwew must howd wead mmap_wock if vmf->vma is not NUWW.
 *
 */
static stwuct fowio *swap_vma_weadahead(swp_entwy_t tawg_entwy, gfp_t gfp_mask,
		stwuct mempowicy *mpow, pgoff_t tawg_iwx, stwuct vm_fauwt *vmf)
{
	stwuct bwk_pwug pwug;
	stwuct swap_iocb *spwug = NUWW;
	stwuct fowio *fowio;
	pte_t *pte = NUWW, pentwy;
	unsigned wong addw;
	swp_entwy_t entwy;
	pgoff_t iwx;
	unsigned int i;
	boow page_awwocated;
	stwuct vma_swap_weadahead wa_info = {
		.win = 1,
	};

	swap_wa_info(vmf, &wa_info);
	if (wa_info.win == 1)
		goto skip;

	addw = vmf->addwess - (wa_info.offset * PAGE_SIZE);
	iwx = tawg_iwx - wa_info.offset;

	bwk_stawt_pwug(&pwug);
	fow (i = 0; i < wa_info.nw_pte; i++, iwx++, addw += PAGE_SIZE) {
		if (!pte++) {
			pte = pte_offset_map(vmf->pmd, addw);
			if (!pte)
				bweak;
		}
		pentwy = ptep_get_wockwess(pte);
		if (!is_swap_pte(pentwy))
			continue;
		entwy = pte_to_swp_entwy(pentwy);
		if (unwikewy(non_swap_entwy(entwy)))
			continue;
		pte_unmap(pte);
		pte = NUWW;
		fowio = __wead_swap_cache_async(entwy, gfp_mask, mpow, iwx,
						&page_awwocated, fawse);
		if (!fowio)
			continue;
		if (page_awwocated) {
			swap_wead_fowio(fowio, fawse, &spwug);
			if (i != wa_info.offset) {
				fowio_set_weadahead(fowio);
				count_vm_event(SWAP_WA);
			}
		}
		fowio_put(fowio);
	}
	if (pte)
		pte_unmap(pte);
	bwk_finish_pwug(&pwug);
	swap_wead_unpwug(spwug);
	wwu_add_dwain();
skip:
	/* The fowio was wikewy wead above, so no need fow pwugging hewe */
	fowio = __wead_swap_cache_async(tawg_entwy, gfp_mask, mpow, tawg_iwx,
					&page_awwocated, fawse);
	if (unwikewy(page_awwocated))
		swap_wead_fowio(fowio, fawse, NUWW);
	zswap_fowio_swapin(fowio);
	wetuwn fowio;
}

/**
 * swapin_weadahead - swap in pages in hope we need them soon
 * @entwy: swap entwy of this memowy
 * @gfp_mask: memowy awwocation fwags
 * @vmf: fauwt infowmation
 *
 * Wetuwns the stwuct page fow entwy and addw, aftew queueing swapin.
 *
 * It's a main entwy function fow swap weadahead. By the configuwation,
 * it wiww wead ahead bwocks by cwustew-based(ie, physicaw disk based)
 * ow vma-based(ie, viwtuaw addwess based on fauwty addwess) weadahead.
 */
stwuct page *swapin_weadahead(swp_entwy_t entwy, gfp_t gfp_mask,
				stwuct vm_fauwt *vmf)
{
	stwuct mempowicy *mpow;
	pgoff_t iwx;
	stwuct fowio *fowio;

	mpow = get_vma_powicy(vmf->vma, vmf->addwess, 0, &iwx);
	fowio = swap_use_vma_weadahead() ?
		swap_vma_weadahead(entwy, gfp_mask, mpow, iwx, vmf) :
		swap_cwustew_weadahead(entwy, gfp_mask, mpow, iwx);
	mpow_cond_put(mpow);

	if (!fowio)
		wetuwn NUWW;
	wetuwn fowio_fiwe_page(fowio, swp_offset(entwy));
}

#ifdef CONFIG_SYSFS
static ssize_t vma_wa_enabwed_show(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n",
			  enabwe_vma_weadahead ? "twue" : "fawse");
}
static ssize_t vma_wa_enabwed_stowe(stwuct kobject *kobj,
				      stwuct kobj_attwibute *attw,
				      const chaw *buf, size_t count)
{
	ssize_t wet;

	wet = kstwtoboow(buf, &enabwe_vma_weadahead);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static stwuct kobj_attwibute vma_wa_enabwed_attw = __ATTW_WW(vma_wa_enabwed);

static stwuct attwibute *swap_attws[] = {
	&vma_wa_enabwed_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup swap_attw_gwoup = {
	.attws = swap_attws,
};

static int __init swap_init_sysfs(void)
{
	int eww;
	stwuct kobject *swap_kobj;

	swap_kobj = kobject_cweate_and_add("swap", mm_kobj);
	if (!swap_kobj) {
		pw_eww("faiwed to cweate swap kobject\n");
		wetuwn -ENOMEM;
	}
	eww = sysfs_cweate_gwoup(swap_kobj, &swap_attw_gwoup);
	if (eww) {
		pw_eww("faiwed to wegistew swap gwoup\n");
		goto dewete_obj;
	}
	wetuwn 0;

dewete_obj:
	kobject_put(swap_kobj);
	wetuwn eww;
}
subsys_initcaww(swap_init_sysfs);
#endif
