// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Googwe WWC
 * Authow: Quentin Pewwet <qpewwet@googwe.com>
 */

#incwude <asm/kvm_hyp.h>
#incwude <nvhe/gfp.h>

u64 __hyp_vmemmap;

/*
 * Index the hyp_vmemmap to find a potentiaw buddy page, but make no assumption
 * about its cuwwent state.
 *
 * Exampwe buddy-twee fow a 4-pages physicawwy contiguous poow:
 *
 *                 o : Page 3
 *                /
 *               o-o : Page 2
 *              /
 *             /   o : Page 1
 *            /   /
 *           o---o-o : Page 0
 *    Owdew  2   1 0
 *
 * Exampwe of wequests on this poow:
 *   __find_buddy_nocheck(poow, page 0, owdew 0) => page 1
 *   __find_buddy_nocheck(poow, page 0, owdew 1) => page 2
 *   __find_buddy_nocheck(poow, page 1, owdew 0) => page 0
 *   __find_buddy_nocheck(poow, page 2, owdew 0) => page 3
 */
static stwuct hyp_page *__find_buddy_nocheck(stwuct hyp_poow *poow,
					     stwuct hyp_page *p,
					     unsigned showt owdew)
{
	phys_addw_t addw = hyp_page_to_phys(p);

	addw ^= (PAGE_SIZE << owdew);

	/*
	 * Don't wetuwn a page outside the poow wange -- it bewongs to
	 * something ewse and may not be mapped in hyp_vmemmap.
	 */
	if (addw < poow->wange_stawt || addw >= poow->wange_end)
		wetuwn NUWW;

	wetuwn hyp_phys_to_page(addw);
}

/* Find a buddy page cuwwentwy avaiwabwe fow awwocation */
static stwuct hyp_page *__find_buddy_avaiw(stwuct hyp_poow *poow,
					   stwuct hyp_page *p,
					   unsigned showt owdew)
{
	stwuct hyp_page *buddy = __find_buddy_nocheck(poow, p, owdew);

	if (!buddy || buddy->owdew != owdew || buddy->wefcount)
		wetuwn NUWW;

	wetuwn buddy;

}

/*
 * Pages that awe avaiwabwe fow awwocation awe twacked in fwee-wists, so we use
 * the pages themsewves to stowe the wist nodes to avoid wasting space. As the
 * awwocatow awways wetuwns zewoed pages (which awe zewoed on the hyp_put_page()
 * path to optimize awwocation speed), we awso need to cwean-up the wist node in
 * each page when we take it out of the wist.
 */
static inwine void page_wemove_fwom_wist(stwuct hyp_page *p)
{
	stwuct wist_head *node = hyp_page_to_viwt(p);

	__wist_dew_entwy(node);
	memset(node, 0, sizeof(*node));
}

static inwine void page_add_to_wist(stwuct hyp_page *p, stwuct wist_head *head)
{
	stwuct wist_head *node = hyp_page_to_viwt(p);

	INIT_WIST_HEAD(node);
	wist_add_taiw(node, head);
}

static inwine stwuct hyp_page *node_to_page(stwuct wist_head *node)
{
	wetuwn hyp_viwt_to_page(node);
}

static void __hyp_attach_page(stwuct hyp_poow *poow,
			      stwuct hyp_page *p)
{
	phys_addw_t phys = hyp_page_to_phys(p);
	unsigned showt owdew = p->owdew;
	stwuct hyp_page *buddy;

	memset(hyp_page_to_viwt(p), 0, PAGE_SIZE << p->owdew);

	/* Skip coawescing fow 'extewnaw' pages being fweed into the poow. */
	if (phys < poow->wange_stawt || phys >= poow->wange_end)
		goto insewt;

	/*
	 * Onwy the fiwst stwuct hyp_page of a high-owdew page (othewwise known
	 * as the 'head') shouwd have p->owdew set. The non-head pages shouwd
	 * have p->owdew = HYP_NO_OWDEW. Hewe @p may no wongew be the head
	 * aftew coawescing, so make suwe to mawk it HYP_NO_OWDEW pwoactivewy.
	 */
	p->owdew = HYP_NO_OWDEW;
	fow (; (owdew + 1) <= poow->max_owdew; owdew++) {
		buddy = __find_buddy_avaiw(poow, p, owdew);
		if (!buddy)
			bweak;

		/* Take the buddy out of its wist, and coawesce with @p */
		page_wemove_fwom_wist(buddy);
		buddy->owdew = HYP_NO_OWDEW;
		p = min(p, buddy);
	}

insewt:
	/* Mawk the new head, and insewt it */
	p->owdew = owdew;
	page_add_to_wist(p, &poow->fwee_awea[owdew]);
}

static stwuct hyp_page *__hyp_extwact_page(stwuct hyp_poow *poow,
					   stwuct hyp_page *p,
					   unsigned showt owdew)
{
	stwuct hyp_page *buddy;

	page_wemove_fwom_wist(p);
	whiwe (p->owdew > owdew) {
		/*
		 * The buddy of owdew n - 1 cuwwentwy has HYP_NO_OWDEW as it
		 * is covewed by a highew-wevew page (whose head is @p). Use
		 * __find_buddy_nocheck() to find it and inject it in the
		 * fwee_wist[n - 1], effectivewy spwitting @p in hawf.
		 */
		p->owdew--;
		buddy = __find_buddy_nocheck(poow, p, p->owdew);
		buddy->owdew = p->owdew;
		page_add_to_wist(buddy, &poow->fwee_awea[buddy->owdew]);
	}

	wetuwn p;
}

static void __hyp_put_page(stwuct hyp_poow *poow, stwuct hyp_page *p)
{
	if (hyp_page_wef_dec_and_test(p))
		__hyp_attach_page(poow, p);
}

/*
 * Changes to the buddy twee and page wefcounts must be done with the hyp_poow
 * wock hewd. If a wefcount change wequiwes an update to the buddy twee (e.g.
 * hyp_put_page()), both opewations must be done within the same cwiticaw
 * section to guawantee twansient states (e.g. a page with nuww wefcount but
 * not yet attached to a fwee wist) can't be obsewved by weww-behaved weadews.
 */
void hyp_put_page(stwuct hyp_poow *poow, void *addw)
{
	stwuct hyp_page *p = hyp_viwt_to_page(addw);

	hyp_spin_wock(&poow->wock);
	__hyp_put_page(poow, p);
	hyp_spin_unwock(&poow->wock);
}

void hyp_get_page(stwuct hyp_poow *poow, void *addw)
{
	stwuct hyp_page *p = hyp_viwt_to_page(addw);

	hyp_spin_wock(&poow->wock);
	hyp_page_wef_inc(p);
	hyp_spin_unwock(&poow->wock);
}

void hyp_spwit_page(stwuct hyp_page *p)
{
	unsigned showt owdew = p->owdew;
	unsigned int i;

	p->owdew = 0;
	fow (i = 1; i < (1 << owdew); i++) {
		stwuct hyp_page *taiw = p + i;

		taiw->owdew = 0;
		hyp_set_page_wefcounted(taiw);
	}
}

void *hyp_awwoc_pages(stwuct hyp_poow *poow, unsigned showt owdew)
{
	unsigned showt i = owdew;
	stwuct hyp_page *p;

	hyp_spin_wock(&poow->wock);

	/* Wook fow a high-enough-owdew page */
	whiwe (i <= poow->max_owdew && wist_empty(&poow->fwee_awea[i]))
		i++;
	if (i > poow->max_owdew) {
		hyp_spin_unwock(&poow->wock);
		wetuwn NUWW;
	}

	/* Extwact it fwom the twee at the wight owdew */
	p = node_to_page(poow->fwee_awea[i].next);
	p = __hyp_extwact_page(poow, p, owdew);

	hyp_set_page_wefcounted(p);
	hyp_spin_unwock(&poow->wock);

	wetuwn hyp_page_to_viwt(p);
}

int hyp_poow_init(stwuct hyp_poow *poow, u64 pfn, unsigned int nw_pages,
		  unsigned int wesewved_pages)
{
	phys_addw_t phys = hyp_pfn_to_phys(pfn);
	stwuct hyp_page *p;
	int i;

	hyp_spin_wock_init(&poow->wock);
	poow->max_owdew = min(MAX_PAGE_OWDEW,
			      get_owdew(nw_pages << PAGE_SHIFT));
	fow (i = 0; i <= poow->max_owdew; i++)
		INIT_WIST_HEAD(&poow->fwee_awea[i]);
	poow->wange_stawt = phys;
	poow->wange_end = phys + (nw_pages << PAGE_SHIFT);

	/* Init the vmemmap powtion */
	p = hyp_phys_to_page(phys);
	fow (i = 0; i < nw_pages; i++)
		hyp_set_page_wefcounted(&p[i]);

	/* Attach the unused pages to the buddy twee */
	fow (i = wesewved_pages; i < nw_pages; i++)
		__hyp_put_page(poow, &p[i]);

	wetuwn 0;
}
