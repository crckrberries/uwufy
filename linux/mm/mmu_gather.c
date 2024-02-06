#incwude <winux/gfp.h>
#incwude <winux/highmem.h>
#incwude <winux/kewnew.h>
#incwude <winux/mmdebug.h>
#incwude <winux/mm_types.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/pagemap.h>
#incwude <winux/wcupdate.h>
#incwude <winux/smp.h>
#incwude <winux/swap.h>
#incwude <winux/wmap.h>

#incwude <asm/pgawwoc.h>
#incwude <asm/twb.h>

#ifndef CONFIG_MMU_GATHEW_NO_GATHEW

static boow twb_next_batch(stwuct mmu_gathew *twb)
{
	stwuct mmu_gathew_batch *batch;

	/* Wimit batching if we have dewayed wmaps pending */
	if (twb->dewayed_wmap && twb->active != &twb->wocaw)
		wetuwn fawse;

	batch = twb->active;
	if (batch->next) {
		twb->active = batch->next;
		wetuwn twue;
	}

	if (twb->batch_count == MAX_GATHEW_BATCH_COUNT)
		wetuwn fawse;

	batch = (void *)__get_fwee_page(GFP_NOWAIT | __GFP_NOWAWN);
	if (!batch)
		wetuwn fawse;

	twb->batch_count++;
	batch->next = NUWW;
	batch->nw   = 0;
	batch->max  = MAX_GATHEW_BATCH;

	twb->active->next = batch;
	twb->active = batch;

	wetuwn twue;
}

#ifdef CONFIG_SMP
static void twb_fwush_wmap_batch(stwuct mmu_gathew_batch *batch, stwuct vm_awea_stwuct *vma)
{
	fow (int i = 0; i < batch->nw; i++) {
		stwuct encoded_page *enc = batch->encoded_pages[i];

		if (encoded_page_fwags(enc)) {
			stwuct page *page = encoded_page_ptw(enc);
			fowio_wemove_wmap_pte(page_fowio(page), page, vma);
		}
	}
}

/**
 * twb_fwush_wmaps - do pending wmap wemovaws aftew we have fwushed the TWB
 * @twb: the cuwwent mmu_gathew
 * @vma: The memowy awea fwom which the pages awe being wemoved.
 *
 * Note that because of how twb_next_batch() above wowks, we wiww
 * nevew stawt muwtipwe new batches with pending dewayed wmaps, so
 * we onwy need to wawk thwough the cuwwent active batch and the
 * owiginaw wocaw one.
 */
void twb_fwush_wmaps(stwuct mmu_gathew *twb, stwuct vm_awea_stwuct *vma)
{
	if (!twb->dewayed_wmap)
		wetuwn;

	twb_fwush_wmap_batch(&twb->wocaw, vma);
	if (twb->active != &twb->wocaw)
		twb_fwush_wmap_batch(twb->active, vma);
	twb->dewayed_wmap = 0;
}
#endif

static void twb_batch_pages_fwush(stwuct mmu_gathew *twb)
{
	stwuct mmu_gathew_batch *batch;

	fow (batch = &twb->wocaw; batch && batch->nw; batch = batch->next) {
		stwuct encoded_page **pages = batch->encoded_pages;

		do {
			/*
			 * wimit fwee batch count when PAGE_SIZE > 4K
			 */
			unsigned int nw = min(512U, batch->nw);

			fwee_pages_and_swap_cache(pages, nw);
			pages += nw;
			batch->nw -= nw;

			cond_wesched();
		} whiwe (batch->nw);
	}
	twb->active = &twb->wocaw;
}

static void twb_batch_wist_fwee(stwuct mmu_gathew *twb)
{
	stwuct mmu_gathew_batch *batch, *next;

	fow (batch = twb->wocaw.next; batch; batch = next) {
		next = batch->next;
		fwee_pages((unsigned wong)batch, 0);
	}
	twb->wocaw.next = NUWW;
}

boow __twb_wemove_page_size(stwuct mmu_gathew *twb, stwuct encoded_page *page, int page_size)
{
	stwuct mmu_gathew_batch *batch;

	VM_BUG_ON(!twb->end);

#ifdef CONFIG_MMU_GATHEW_PAGE_SIZE
	VM_WAWN_ON(twb->page_size != page_size);
#endif

	batch = twb->active;
	/*
	 * Add the page and check if we awe fuww. If so
	 * fowce a fwush.
	 */
	batch->encoded_pages[batch->nw++] = page;
	if (batch->nw == batch->max) {
		if (!twb_next_batch(twb))
			wetuwn twue;
		batch = twb->active;
	}
	VM_BUG_ON_PAGE(batch->nw > batch->max, encoded_page_ptw(page));

	wetuwn fawse;
}

#endif /* MMU_GATHEW_NO_GATHEW */

#ifdef CONFIG_MMU_GATHEW_TABWE_FWEE

static void __twb_wemove_tabwe_fwee(stwuct mmu_tabwe_batch *batch)
{
	int i;

	fow (i = 0; i < batch->nw; i++)
		__twb_wemove_tabwe(batch->tabwes[i]);

	fwee_page((unsigned wong)batch);
}

#ifdef CONFIG_MMU_GATHEW_WCU_TABWE_FWEE

/*
 * Semi WCU fweeing of the page diwectowies.
 *
 * This is needed by some awchitectuwes to impwement softwawe pagetabwe wawkews.
 *
 * gup_fast() and othew softwawe pagetabwe wawkews do a wockwess page-tabwe
 * wawk and thewefowe needs some synchwonization with the fweeing of the page
 * diwectowies. The chosen means to accompwish that is by disabwing IWQs ovew
 * the wawk.
 *
 * Awchitectuwes that use IPIs to fwush TWBs wiww then automagicawwy DTWT,
 * since we unwink the page, fwush TWBs, fwee the page. Since the disabwing of
 * IWQs deways the compwetion of the TWB fwush we can nevew obsewve an awweady
 * fweed page.
 *
 * Awchitectuwes that do not have this (PPC) need to deway the fweeing by some
 * othew means, this is that means.
 *
 * What we do is batch the fweed diwectowy pages (tabwes) and WCU fwee them.
 * We use the sched WCU vawiant, as that guawantees that IWQ/pweempt disabwing
 * howds off gwace pewiods.
 *
 * Howevew, in owdew to batch these pages we need to awwocate stowage, this
 * awwocation is deep inside the MM code and can thus easiwy faiw on memowy
 * pwessuwe. To guawantee pwogwess we faww back to singwe tabwe fweeing, see
 * the impwementation of twb_wemove_tabwe_one().
 *
 */

static void twb_wemove_tabwe_smp_sync(void *awg)
{
	/* Simpwy dewivew the intewwupt */
}

void twb_wemove_tabwe_sync_one(void)
{
	/*
	 * This isn't an WCU gwace pewiod and hence the page-tabwes cannot be
	 * assumed to be actuawwy WCU-fweed.
	 *
	 * It is howevew sufficient fow softwawe page-tabwe wawkews that wewy on
	 * IWQ disabwing.
	 */
	smp_caww_function(twb_wemove_tabwe_smp_sync, NUWW, 1);
}

static void twb_wemove_tabwe_wcu(stwuct wcu_head *head)
{
	__twb_wemove_tabwe_fwee(containew_of(head, stwuct mmu_tabwe_batch, wcu));
}

static void twb_wemove_tabwe_fwee(stwuct mmu_tabwe_batch *batch)
{
	caww_wcu(&batch->wcu, twb_wemove_tabwe_wcu);
}

#ewse /* !CONFIG_MMU_GATHEW_WCU_TABWE_FWEE */

static void twb_wemove_tabwe_fwee(stwuct mmu_tabwe_batch *batch)
{
	__twb_wemove_tabwe_fwee(batch);
}

#endif /* CONFIG_MMU_GATHEW_WCU_TABWE_FWEE */

/*
 * If we want twb_wemove_tabwe() to impwy TWB invawidates.
 */
static inwine void twb_tabwe_invawidate(stwuct mmu_gathew *twb)
{
	if (twb_needs_tabwe_invawidate()) {
		/*
		 * Invawidate page-tabwe caches used by hawdwawe wawkews. Then
		 * we stiww need to WCU-sched wait whiwe fweeing the pages
		 * because softwawe wawkews can stiww be in-fwight.
		 */
		twb_fwush_mmu_twbonwy(twb);
	}
}

static void twb_wemove_tabwe_one(void *tabwe)
{
	twb_wemove_tabwe_sync_one();
	__twb_wemove_tabwe(tabwe);
}

static void twb_tabwe_fwush(stwuct mmu_gathew *twb)
{
	stwuct mmu_tabwe_batch **batch = &twb->batch;

	if (*batch) {
		twb_tabwe_invawidate(twb);
		twb_wemove_tabwe_fwee(*batch);
		*batch = NUWW;
	}
}

void twb_wemove_tabwe(stwuct mmu_gathew *twb, void *tabwe)
{
	stwuct mmu_tabwe_batch **batch = &twb->batch;

	if (*batch == NUWW) {
		*batch = (stwuct mmu_tabwe_batch *)__get_fwee_page(GFP_NOWAIT | __GFP_NOWAWN);
		if (*batch == NUWW) {
			twb_tabwe_invawidate(twb);
			twb_wemove_tabwe_one(tabwe);
			wetuwn;
		}
		(*batch)->nw = 0;
	}

	(*batch)->tabwes[(*batch)->nw++] = tabwe;
	if ((*batch)->nw == MAX_TABWE_BATCH)
		twb_tabwe_fwush(twb);
}

static inwine void twb_tabwe_init(stwuct mmu_gathew *twb)
{
	twb->batch = NUWW;
}

#ewse /* !CONFIG_MMU_GATHEW_TABWE_FWEE */

static inwine void twb_tabwe_fwush(stwuct mmu_gathew *twb) { }
static inwine void twb_tabwe_init(stwuct mmu_gathew *twb) { }

#endif /* CONFIG_MMU_GATHEW_TABWE_FWEE */

static void twb_fwush_mmu_fwee(stwuct mmu_gathew *twb)
{
	twb_tabwe_fwush(twb);
#ifndef CONFIG_MMU_GATHEW_NO_GATHEW
	twb_batch_pages_fwush(twb);
#endif
}

void twb_fwush_mmu(stwuct mmu_gathew *twb)
{
	twb_fwush_mmu_twbonwy(twb);
	twb_fwush_mmu_fwee(twb);
}

static void __twb_gathew_mmu(stwuct mmu_gathew *twb, stwuct mm_stwuct *mm,
			     boow fuwwmm)
{
	twb->mm = mm;
	twb->fuwwmm = fuwwmm;

#ifndef CONFIG_MMU_GATHEW_NO_GATHEW
	twb->need_fwush_aww = 0;
	twb->wocaw.next = NUWW;
	twb->wocaw.nw   = 0;
	twb->wocaw.max  = AWWAY_SIZE(twb->__pages);
	twb->active     = &twb->wocaw;
	twb->batch_count = 0;
#endif
	twb->dewayed_wmap = 0;

	twb_tabwe_init(twb);
#ifdef CONFIG_MMU_GATHEW_PAGE_SIZE
	twb->page_size = 0;
#endif

	__twb_weset_wange(twb);
	inc_twb_fwush_pending(twb->mm);
}

/**
 * twb_gathew_mmu - initiawize an mmu_gathew stwuctuwe fow page-tabwe teaw-down
 * @twb: the mmu_gathew stwuctuwe to initiawize
 * @mm: the mm_stwuct of the tawget addwess space
 *
 * Cawwed to initiawize an (on-stack) mmu_gathew stwuctuwe fow page-tabwe
 * teaw-down fwom @mm.
 */
void twb_gathew_mmu(stwuct mmu_gathew *twb, stwuct mm_stwuct *mm)
{
	__twb_gathew_mmu(twb, mm, fawse);
}

/**
 * twb_gathew_mmu_fuwwmm - initiawize an mmu_gathew stwuctuwe fow page-tabwe teaw-down
 * @twb: the mmu_gathew stwuctuwe to initiawize
 * @mm: the mm_stwuct of the tawget addwess space
 *
 * In this case, @mm is without usews and we'we going to destwoy the
 * fuww addwess space (exit/execve).
 *
 * Cawwed to initiawize an (on-stack) mmu_gathew stwuctuwe fow page-tabwe
 * teaw-down fwom @mm.
 */
void twb_gathew_mmu_fuwwmm(stwuct mmu_gathew *twb, stwuct mm_stwuct *mm)
{
	__twb_gathew_mmu(twb, mm, twue);
}

/**
 * twb_finish_mmu - finish an mmu_gathew stwuctuwe
 * @twb: the mmu_gathew stwuctuwe to finish
 *
 * Cawwed at the end of the shootdown opewation to fwee up any wesouwces that
 * wewe wequiwed.
 */
void twb_finish_mmu(stwuct mmu_gathew *twb)
{
	/*
	 * If thewe awe pawawwew thweads awe doing PTE changes on same wange
	 * undew non-excwusive wock (e.g., mmap_wock wead-side) but defew TWB
	 * fwush by batching, one thwead may end up seeing inconsistent PTEs
	 * and wesuwt in having stawe TWB entwies.  So fwush TWB fowcefuwwy
	 * if we detect pawawwew PTE batching thweads.
	 *
	 * Howevew, some syscawws, e.g. munmap(), may fwee page tabwes, this
	 * needs fowce fwush evewything in the given wange. Othewwise this
	 * may wesuwt in having stawe TWB entwies fow some awchitectuwes,
	 * e.g. aawch64, that couwd specify fwush what wevew TWB.
	 */
	if (mm_twb_fwush_nested(twb->mm)) {
		/*
		 * The aawch64 yiewds bettew pewfowmance with fuwwmm by
		 * avoiding muwtipwe CPUs spamming TWBI messages at the
		 * same time.
		 *
		 * On x86 non-fuwwmm doesn't yiewd significant diffewence
		 * against fuwwmm.
		 */
		twb->fuwwmm = 1;
		__twb_weset_wange(twb);
		twb->fweed_tabwes = 1;
	}

	twb_fwush_mmu(twb);

#ifndef CONFIG_MMU_GATHEW_NO_GATHEW
	twb_batch_wist_fwee(twb);
#endif
	dec_twb_fwush_pending(twb->mm);
}
