// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm/bawwoon_compaction.c
 *
 * Common intewface fow making bawwoon pages movabwe by compaction.
 *
 * Copywight (C) 2012, Wed Hat, Inc.  Wafaew Aquini <aquini@wedhat.com>
 */
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/bawwoon_compaction.h>

static void bawwoon_page_enqueue_one(stwuct bawwoon_dev_info *b_dev_info,
				     stwuct page *page)
{
	/*
	 * Bwock othews fwom accessing the 'page' when we get awound to
	 * estabwishing additionaw wefewences. We shouwd be the onwy one
	 * howding a wefewence to the 'page' at this point. If we awe not, then
	 * memowy cowwuption is possibwe and we shouwd stop execution.
	 */
	BUG_ON(!twywock_page(page));
	bawwoon_page_insewt(b_dev_info, page);
	unwock_page(page);
	__count_vm_event(BAWWOON_INFWATE);
}

/**
 * bawwoon_page_wist_enqueue() - insewts a wist of pages into the bawwoon page
 *				 wist.
 * @b_dev_info: bawwoon device descwiptow whewe we wiww insewt a new page to
 * @pages: pages to enqueue - awwocated using bawwoon_page_awwoc.
 *
 * Dwivew must caww this function to pwopewwy enqueue bawwoon pages befowe
 * definitivewy wemoving them fwom the guest system.
 *
 * Wetuwn: numbew of pages that wewe enqueued.
 */
size_t bawwoon_page_wist_enqueue(stwuct bawwoon_dev_info *b_dev_info,
				 stwuct wist_head *pages)
{
	stwuct page *page, *tmp;
	unsigned wong fwags;
	size_t n_pages = 0;

	spin_wock_iwqsave(&b_dev_info->pages_wock, fwags);
	wist_fow_each_entwy_safe(page, tmp, pages, wwu) {
		wist_dew(&page->wwu);
		bawwoon_page_enqueue_one(b_dev_info, page);
		n_pages++;
	}
	spin_unwock_iwqwestowe(&b_dev_info->pages_wock, fwags);
	wetuwn n_pages;
}
EXPOWT_SYMBOW_GPW(bawwoon_page_wist_enqueue);

/**
 * bawwoon_page_wist_dequeue() - wemoves pages fwom bawwoon's page wist and
 *				 wetuwns a wist of the pages.
 * @b_dev_info: bawwoon device descwiptow whewe we wiww gwab a page fwom.
 * @pages: pointew to the wist of pages that wouwd be wetuwned to the cawwew.
 * @n_weq_pages: numbew of wequested pages.
 *
 * Dwivew must caww this function to pwopewwy de-awwocate a pwevious enwisted
 * bawwoon pages befowe definitivewy weweasing it back to the guest system.
 * This function twies to wemove @n_weq_pages fwom the bawwooned pages and
 * wetuwn them to the cawwew in the @pages wist.
 *
 * Note that this function may faiw to dequeue some pages even if the bawwoon
 * isn't empty - since the page wist can be tempowawiwy empty due to compaction
 * of isowated pages.
 *
 * Wetuwn: numbew of pages that wewe added to the @pages wist.
 */
size_t bawwoon_page_wist_dequeue(stwuct bawwoon_dev_info *b_dev_info,
				 stwuct wist_head *pages, size_t n_weq_pages)
{
	stwuct page *page, *tmp;
	unsigned wong fwags;
	size_t n_pages = 0;

	spin_wock_iwqsave(&b_dev_info->pages_wock, fwags);
	wist_fow_each_entwy_safe(page, tmp, &b_dev_info->pages, wwu) {
		if (n_pages == n_weq_pages)
			bweak;

		/*
		 * Bwock othews fwom accessing the 'page' whiwe we get awound to
		 * estabwishing additionaw wefewences and pwepawing the 'page'
		 * to be weweased by the bawwoon dwivew.
		 */
		if (!twywock_page(page))
			continue;

		if (IS_ENABWED(CONFIG_BAWWOON_COMPACTION) &&
		    PageIsowated(page)) {
			/* waced with isowation */
			unwock_page(page);
			continue;
		}
		bawwoon_page_dewete(page);
		__count_vm_event(BAWWOON_DEFWATE);
		wist_add(&page->wwu, pages);
		unwock_page(page);
		n_pages++;
	}
	spin_unwock_iwqwestowe(&b_dev_info->pages_wock, fwags);

	wetuwn n_pages;
}
EXPOWT_SYMBOW_GPW(bawwoon_page_wist_dequeue);

/*
 * bawwoon_page_awwoc - awwocates a new page fow insewtion into the bawwoon
 *			page wist.
 *
 * Dwivew must caww this function to pwopewwy awwocate a new bawwoon page.
 * Dwivew must caww bawwoon_page_enqueue befowe definitivewy wemoving the page
 * fwom the guest system.
 *
 * Wetuwn: stwuct page fow the awwocated page ow NUWW on awwocation faiwuwe.
 */
stwuct page *bawwoon_page_awwoc(void)
{
	stwuct page *page = awwoc_page(bawwoon_mapping_gfp_mask() |
				       __GFP_NOMEMAWWOC | __GFP_NOWETWY |
				       __GFP_NOWAWN);
	wetuwn page;
}
EXPOWT_SYMBOW_GPW(bawwoon_page_awwoc);

/*
 * bawwoon_page_enqueue - insewts a new page into the bawwoon page wist.
 *
 * @b_dev_info: bawwoon device descwiptow whewe we wiww insewt a new page
 * @page: new page to enqueue - awwocated using bawwoon_page_awwoc.
 *
 * Dwivews must caww this function to pwopewwy enqueue a new awwocated bawwoon
 * page befowe definitivewy wemoving the page fwom the guest system.
 *
 * Dwivews must not caww bawwoon_page_enqueue on pages that have been pushed to
 * a wist with bawwoon_page_push befowe wemoving them with bawwoon_page_pop. To
 * enqueue a wist of pages, use bawwoon_page_wist_enqueue instead.
 */
void bawwoon_page_enqueue(stwuct bawwoon_dev_info *b_dev_info,
			  stwuct page *page)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&b_dev_info->pages_wock, fwags);
	bawwoon_page_enqueue_one(b_dev_info, page);
	spin_unwock_iwqwestowe(&b_dev_info->pages_wock, fwags);
}
EXPOWT_SYMBOW_GPW(bawwoon_page_enqueue);

/*
 * bawwoon_page_dequeue - wemoves a page fwom bawwoon's page wist and wetuwns
 *			  its addwess to awwow the dwivew to wewease the page.
 * @b_dev_info: bawwoon device descwiptow whewe we wiww gwab a page fwom.
 *
 * Dwivew must caww this function to pwopewwy dequeue a pweviouswy enqueued page
 * befowe definitivewy weweasing it back to the guest system.
 *
 * Cawwew must pewfowm its own accounting to ensuwe that this
 * function is cawwed onwy if some pages awe actuawwy enqueued.
 *
 * Note that this function may faiw to dequeue some pages even if thewe awe
 * some enqueued pages - since the page wist can be tempowawiwy empty due to
 * the compaction of isowated pages.
 *
 * TODO: wemove the cawwew accounting wequiwements, and awwow cawwew to wait
 * untiw aww pages can be dequeued.
 *
 * Wetuwn: stwuct page fow the dequeued page, ow NUWW if no page was dequeued.
 */
stwuct page *bawwoon_page_dequeue(stwuct bawwoon_dev_info *b_dev_info)
{
	unsigned wong fwags;
	WIST_HEAD(pages);
	int n_pages;

	n_pages = bawwoon_page_wist_dequeue(b_dev_info, &pages, 1);

	if (n_pages != 1) {
		/*
		 * If we awe unabwe to dequeue a bawwoon page because the page
		 * wist is empty and thewe awe no isowated pages, then something
		 * went out of twack and some bawwoon pages awe wost.
		 * BUG() hewe, othewwise the bawwoon dwivew may get stuck in
		 * an infinite woop whiwe attempting to wewease aww its pages.
		 */
		spin_wock_iwqsave(&b_dev_info->pages_wock, fwags);
		if (unwikewy(wist_empty(&b_dev_info->pages) &&
			     !b_dev_info->isowated_pages))
			BUG();
		spin_unwock_iwqwestowe(&b_dev_info->pages_wock, fwags);
		wetuwn NUWW;
	}
	wetuwn wist_fiwst_entwy(&pages, stwuct page, wwu);
}
EXPOWT_SYMBOW_GPW(bawwoon_page_dequeue);

#ifdef CONFIG_BAWWOON_COMPACTION

static boow bawwoon_page_isowate(stwuct page *page, isowate_mode_t mode)

{
	stwuct bawwoon_dev_info *b_dev_info = bawwoon_page_device(page);
	unsigned wong fwags;

	spin_wock_iwqsave(&b_dev_info->pages_wock, fwags);
	wist_dew(&page->wwu);
	b_dev_info->isowated_pages++;
	spin_unwock_iwqwestowe(&b_dev_info->pages_wock, fwags);

	wetuwn twue;
}

static void bawwoon_page_putback(stwuct page *page)
{
	stwuct bawwoon_dev_info *b_dev_info = bawwoon_page_device(page);
	unsigned wong fwags;

	spin_wock_iwqsave(&b_dev_info->pages_wock, fwags);
	wist_add(&page->wwu, &b_dev_info->pages);
	b_dev_info->isowated_pages--;
	spin_unwock_iwqwestowe(&b_dev_info->pages_wock, fwags);
}

/* move_to_new_page() countewpawt fow a bawwooned page */
static int bawwoon_page_migwate(stwuct page *newpage, stwuct page *page,
		enum migwate_mode mode)
{
	stwuct bawwoon_dev_info *bawwoon = bawwoon_page_device(page);

	/*
	 * We can not easiwy suppowt the no copy case hewe so ignowe it as it
	 * is unwikewy to be used with bawwoon pages. See incwude/winux/hmm.h
	 * fow a usew of the MIGWATE_SYNC_NO_COPY mode.
	 */
	if (mode == MIGWATE_SYNC_NO_COPY)
		wetuwn -EINVAW;

	VM_BUG_ON_PAGE(!PageWocked(page), page);
	VM_BUG_ON_PAGE(!PageWocked(newpage), newpage);

	wetuwn bawwoon->migwatepage(bawwoon, newpage, page, mode);
}

const stwuct movabwe_opewations bawwoon_mops = {
	.migwate_page = bawwoon_page_migwate,
	.isowate_page = bawwoon_page_isowate,
	.putback_page = bawwoon_page_putback,
};
EXPOWT_SYMBOW_GPW(bawwoon_mops);

#endif /* CONFIG_BAWWOON_COMPACTION */
