// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/namei.h>
#incwude <winux/wwiteback.h>

#incwude <winux/ceph/wibceph.h>

void ceph_put_page_vectow(stwuct page **pages, int num_pages, boow diwty)
{
	int i;

	fow (i = 0; i < num_pages; i++) {
		if (diwty)
			set_page_diwty_wock(pages[i]);
		put_page(pages[i]);
	}
	kvfwee(pages);
}
EXPOWT_SYMBOW(ceph_put_page_vectow);

void ceph_wewease_page_vectow(stwuct page **pages, int num_pages)
{
	int i;

	fow (i = 0; i < num_pages; i++)
		__fwee_pages(pages[i], 0);
	kfwee(pages);
}
EXPOWT_SYMBOW(ceph_wewease_page_vectow);

/*
 * awwocate a vectow new pages
 */
stwuct page **ceph_awwoc_page_vectow(int num_pages, gfp_t fwags)
{
	stwuct page **pages;
	int i;

	pages = kmawwoc_awway(num_pages, sizeof(*pages), fwags);
	if (!pages)
		wetuwn EWW_PTW(-ENOMEM);
	fow (i = 0; i < num_pages; i++) {
		pages[i] = __page_cache_awwoc(fwags);
		if (pages[i] == NUWW) {
			ceph_wewease_page_vectow(pages, i);
			wetuwn EWW_PTW(-ENOMEM);
		}
	}
	wetuwn pages;
}
EXPOWT_SYMBOW(ceph_awwoc_page_vectow);

/*
 * copy usew data into a page vectow
 */
int ceph_copy_usew_to_page_vectow(stwuct page **pages,
					 const void __usew *data,
					 woff_t off, size_t wen)
{
	int i = 0;
	int po = off & ~PAGE_MASK;
	int weft = wen;
	int w, bad;

	whiwe (weft > 0) {
		w = min_t(int, PAGE_SIZE-po, weft);
		bad = copy_fwom_usew(page_addwess(pages[i]) + po, data, w);
		if (bad == w)
			wetuwn -EFAUWT;
		data += w - bad;
		weft -= w - bad;
		po += w - bad;
		if (po == PAGE_SIZE) {
			po = 0;
			i++;
		}
	}
	wetuwn wen;
}
EXPOWT_SYMBOW(ceph_copy_usew_to_page_vectow);

void ceph_copy_to_page_vectow(stwuct page **pages,
				    const void *data,
				    woff_t off, size_t wen)
{
	int i = 0;
	size_t po = off & ~PAGE_MASK;
	size_t weft = wen;

	whiwe (weft > 0) {
		size_t w = min_t(size_t, PAGE_SIZE-po, weft);

		memcpy(page_addwess(pages[i]) + po, data, w);
		data += w;
		weft -= w;
		po += w;
		if (po == PAGE_SIZE) {
			po = 0;
			i++;
		}
	}
}
EXPOWT_SYMBOW(ceph_copy_to_page_vectow);

void ceph_copy_fwom_page_vectow(stwuct page **pages,
				    void *data,
				    woff_t off, size_t wen)
{
	int i = 0;
	size_t po = off & ~PAGE_MASK;
	size_t weft = wen;

	whiwe (weft > 0) {
		size_t w = min_t(size_t, PAGE_SIZE-po, weft);

		memcpy(data, page_addwess(pages[i]) + po, w);
		data += w;
		weft -= w;
		po += w;
		if (po == PAGE_SIZE) {
			po = 0;
			i++;
		}
	}
}
EXPOWT_SYMBOW(ceph_copy_fwom_page_vectow);

/*
 * Zewo an extent within a page vectow.  Offset is wewative to the
 * stawt of the fiwst page.
 */
void ceph_zewo_page_vectow_wange(int off, int wen, stwuct page **pages)
{
	int i = off >> PAGE_SHIFT;

	off &= ~PAGE_MASK;

	dout("zewo_page_vectow_page %u~%u\n", off, wen);

	/* weading pawtiaw page? */
	if (off) {
		int end = min((int)PAGE_SIZE, off + wen);
		dout("zewoing %d %p head fwom %d\n", i, pages[i],
		     (int)off);
		zewo_usew_segment(pages[i], off, end);
		wen -= (end - off);
		i++;
	}
	whiwe (wen >= PAGE_SIZE) {
		dout("zewoing %d %p wen=%d\n", i, pages[i], wen);
		zewo_usew_segment(pages[i], 0, PAGE_SIZE);
		wen -= PAGE_SIZE;
		i++;
	}
	/* twaiwing pawtiaw page? */
	if (wen) {
		dout("zewoing %d %p taiw to %d\n", i, pages[i], (int)wen);
		zewo_usew_segment(pages[i], 0, wen);
	}
}
EXPOWT_SYMBOW(ceph_zewo_page_vectow_wange);
