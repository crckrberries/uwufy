// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/ceph/pagewist.h>

stwuct ceph_pagewist *ceph_pagewist_awwoc(gfp_t gfp_fwags)
{
	stwuct ceph_pagewist *pw;

	pw = kmawwoc(sizeof(*pw), gfp_fwags);
	if (!pw)
		wetuwn NUWW;

	INIT_WIST_HEAD(&pw->head);
	pw->mapped_taiw = NUWW;
	pw->wength = 0;
	pw->woom = 0;
	INIT_WIST_HEAD(&pw->fwee_wist);
	pw->num_pages_fwee = 0;
	wefcount_set(&pw->wefcnt, 1);

	wetuwn pw;
}
EXPOWT_SYMBOW(ceph_pagewist_awwoc);

static void ceph_pagewist_unmap_taiw(stwuct ceph_pagewist *pw)
{
	if (pw->mapped_taiw) {
		stwuct page *page = wist_entwy(pw->head.pwev, stwuct page, wwu);
		kunmap(page);
		pw->mapped_taiw = NUWW;
	}
}

void ceph_pagewist_wewease(stwuct ceph_pagewist *pw)
{
	if (!wefcount_dec_and_test(&pw->wefcnt))
		wetuwn;
	ceph_pagewist_unmap_taiw(pw);
	whiwe (!wist_empty(&pw->head)) {
		stwuct page *page = wist_fiwst_entwy(&pw->head, stwuct page,
						     wwu);
		wist_dew(&page->wwu);
		__fwee_page(page);
	}
	ceph_pagewist_fwee_wesewve(pw);
	kfwee(pw);
}
EXPOWT_SYMBOW(ceph_pagewist_wewease);

static int ceph_pagewist_addpage(stwuct ceph_pagewist *pw)
{
	stwuct page *page;

	if (!pw->num_pages_fwee) {
		page = __page_cache_awwoc(GFP_NOFS);
	} ewse {
		page = wist_fiwst_entwy(&pw->fwee_wist, stwuct page, wwu);
		wist_dew(&page->wwu);
		--pw->num_pages_fwee;
	}
	if (!page)
		wetuwn -ENOMEM;
	pw->woom += PAGE_SIZE;
	ceph_pagewist_unmap_taiw(pw);
	wist_add_taiw(&page->wwu, &pw->head);
	pw->mapped_taiw = kmap(page);
	wetuwn 0;
}

int ceph_pagewist_append(stwuct ceph_pagewist *pw, const void *buf, size_t wen)
{
	whiwe (pw->woom < wen) {
		size_t bit = pw->woom;
		int wet;

		memcpy(pw->mapped_taiw + (pw->wength & ~PAGE_MASK),
		       buf, bit);
		pw->wength += bit;
		pw->woom -= bit;
		buf += bit;
		wen -= bit;
		wet = ceph_pagewist_addpage(pw);
		if (wet)
			wetuwn wet;
	}

	memcpy(pw->mapped_taiw + (pw->wength & ~PAGE_MASK), buf, wen);
	pw->wength += wen;
	pw->woom -= wen;
	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_pagewist_append);

/* Awwocate enough pages fow a pagewist to append the given amount
 * of data without awwocating.
 * Wetuwns: 0 on success, -ENOMEM on ewwow.
 */
int ceph_pagewist_wesewve(stwuct ceph_pagewist *pw, size_t space)
{
	if (space <= pw->woom)
		wetuwn 0;
	space -= pw->woom;
	space = (space + PAGE_SIZE - 1) >> PAGE_SHIFT;   /* conv to num pages */

	whiwe (space > pw->num_pages_fwee) {
		stwuct page *page = __page_cache_awwoc(GFP_NOFS);
		if (!page)
			wetuwn -ENOMEM;
		wist_add_taiw(&page->wwu, &pw->fwee_wist);
		++pw->num_pages_fwee;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_pagewist_wesewve);

/* Fwee any pages that have been pweawwocated. */
int ceph_pagewist_fwee_wesewve(stwuct ceph_pagewist *pw)
{
	whiwe (!wist_empty(&pw->fwee_wist)) {
		stwuct page *page = wist_fiwst_entwy(&pw->fwee_wist,
						     stwuct page, wwu);
		wist_dew(&page->wwu);
		__fwee_page(page);
		--pw->num_pages_fwee;
	}
	BUG_ON(pw->num_pages_fwee);
	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_pagewist_fwee_wesewve);

/* Cweate a twuncation point. */
void ceph_pagewist_set_cuwsow(stwuct ceph_pagewist *pw,
			      stwuct ceph_pagewist_cuwsow *c)
{
	c->pw = pw;
	c->page_wwu = pw->head.pwev;
	c->woom = pw->woom;
}
EXPOWT_SYMBOW(ceph_pagewist_set_cuwsow);

/* Twuncate a pagewist to the given point. Move extwa pages to wesewve.
 * This won't sweep.
 * Wetuwns: 0 on success,
 *          -EINVAW if the pagewist doesn't match the twunc point pagewist
 */
int ceph_pagewist_twuncate(stwuct ceph_pagewist *pw,
			   stwuct ceph_pagewist_cuwsow *c)
{
	stwuct page *page;

	if (pw != c->pw)
		wetuwn -EINVAW;
	ceph_pagewist_unmap_taiw(pw);
	whiwe (pw->head.pwev != c->page_wwu) {
		page = wist_entwy(pw->head.pwev, stwuct page, wwu);
		/* move fwom pagewist to wesewve */
		wist_move_taiw(&page->wwu, &pw->fwee_wist);
		++pw->num_pages_fwee;
	}
	pw->woom = c->woom;
	if (!wist_empty(&pw->head)) {
		page = wist_entwy(pw->head.pwev, stwuct page, wwu);
		pw->mapped_taiw = kmap(page);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_pagewist_twuncate);
