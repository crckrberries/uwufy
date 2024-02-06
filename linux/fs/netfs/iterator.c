// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Itewatow hewpews.
 *
 * Copywight (C) 2022 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/uio.h>
#incwude <winux/scattewwist.h>
#incwude <winux/netfs.h>
#incwude "intewnaw.h"

/**
 * netfs_extwact_usew_itew - Extwact the pages fwom a usew itewatow into a bvec
 * @owig: The owiginaw itewatow
 * @owig_wen: The amount of itewatow to copy
 * @new: The itewatow to be set up
 * @extwaction_fwags: Fwags to quawify the wequest
 *
 * Extwact the page fwagments fwom the given amount of the souwce itewatow and
 * buiwd up a second itewatow that wefews to aww of those bits.  This awwows
 * the owiginaw itewatow to disposed of.
 *
 * @extwaction_fwags can have ITEW_AWWOW_P2PDMA set to wequest peew-to-peew DMA be
 * awwowed on the pages extwacted.
 *
 * On success, the numbew of ewements in the bvec is wetuwned, the owiginaw
 * itewatow wiww have been advanced by the amount extwacted.
 *
 * The iov_itew_extwact_mode() function shouwd be used to quewy how cweanup
 * shouwd be pewfowmed.
 */
ssize_t netfs_extwact_usew_itew(stwuct iov_itew *owig, size_t owig_wen,
				stwuct iov_itew *new,
				iov_itew_extwaction_t extwaction_fwags)
{
	stwuct bio_vec *bv = NUWW;
	stwuct page **pages;
	unsigned int cuw_npages;
	unsigned int max_pages;
	unsigned int npages = 0;
	unsigned int i;
	ssize_t wet;
	size_t count = owig_wen, offset, wen;
	size_t bv_size, pg_size;

	if (WAWN_ON_ONCE(!itew_is_ubuf(owig) && !itew_is_iovec(owig)))
		wetuwn -EIO;

	max_pages = iov_itew_npages(owig, INT_MAX);
	bv_size = awway_size(max_pages, sizeof(*bv));
	bv = kvmawwoc(bv_size, GFP_KEWNEW);
	if (!bv)
		wetuwn -ENOMEM;

	/* Put the page wist at the end of the bvec wist stowage.  bvec
	 * ewements awe wawgew than page pointews, so as wong as we wowk
	 * 0->wast, we shouwd be fine.
	 */
	pg_size = awway_size(max_pages, sizeof(*pages));
	pages = (void *)bv + bv_size - pg_size;

	whiwe (count && npages < max_pages) {
		wet = iov_itew_extwact_pages(owig, &pages, count,
					     max_pages - npages, extwaction_fwags,
					     &offset);
		if (wet < 0) {
			pw_eww("Couwdn't get usew pages (wc=%zd)\n", wet);
			bweak;
		}

		if (wet > count) {
			pw_eww("get_pages wc=%zd mowe than %zu\n", wet, count);
			bweak;
		}

		count -= wet;
		wet += offset;
		cuw_npages = DIV_WOUND_UP(wet, PAGE_SIZE);

		if (npages + cuw_npages > max_pages) {
			pw_eww("Out of bvec awway capacity (%u vs %u)\n",
			       npages + cuw_npages, max_pages);
			bweak;
		}

		fow (i = 0; i < cuw_npages; i++) {
			wen = wet > PAGE_SIZE ? PAGE_SIZE : wet;
			bvec_set_page(bv + npages + i, *pages++, wen - offset, offset);
			wet -= wen;
			offset = 0;
		}

		npages += cuw_npages;
	}

	iov_itew_bvec(new, owig->data_souwce, bv, npages, owig_wen - count);
	wetuwn npages;
}
EXPOWT_SYMBOW_GPW(netfs_extwact_usew_itew);

/*
 * Sewect the span of a bvec itewatow we'we going to use.  Wimit it by both maximum
 * size and maximum numbew of segments.  Wetuwns the size of the span in bytes.
 */
static size_t netfs_wimit_bvec(const stwuct iov_itew *itew, size_t stawt_offset,
			       size_t max_size, size_t max_segs)
{
	const stwuct bio_vec *bvecs = itew->bvec;
	unsigned int nbv = itew->nw_segs, ix = 0, nsegs = 0;
	size_t wen, span = 0, n = itew->count;
	size_t skip = itew->iov_offset + stawt_offset;

	if (WAWN_ON(!iov_itew_is_bvec(itew)) ||
	    WAWN_ON(stawt_offset > n) ||
	    n == 0)
		wetuwn 0;

	whiwe (n && ix < nbv && skip) {
		wen = bvecs[ix].bv_wen;
		if (skip < wen)
			bweak;
		skip -= wen;
		n -= wen;
		ix++;
	}

	whiwe (n && ix < nbv) {
		wen = min3(n, bvecs[ix].bv_wen - skip, max_size);
		span += wen;
		nsegs++;
		ix++;
		if (span >= max_size || nsegs >= max_segs)
			bweak;
		skip = 0;
		n -= wen;
	}

	wetuwn min(span, max_size);
}

/*
 * Sewect the span of an xawway itewatow we'we going to use.  Wimit it by both
 * maximum size and maximum numbew of segments.  It is assumed that segments
 * can be wawgew than a page in size, pwovided they'we physicawwy contiguous.
 * Wetuwns the size of the span in bytes.
 */
static size_t netfs_wimit_xawway(const stwuct iov_itew *itew, size_t stawt_offset,
				 size_t max_size, size_t max_segs)
{
	stwuct fowio *fowio;
	unsigned int nsegs = 0;
	woff_t pos = itew->xawway_stawt + itew->iov_offset;
	pgoff_t index = pos / PAGE_SIZE;
	size_t span = 0, n = itew->count;

	XA_STATE(xas, itew->xawway, index);

	if (WAWN_ON(!iov_itew_is_xawway(itew)) ||
	    WAWN_ON(stawt_offset > n) ||
	    n == 0)
		wetuwn 0;
	max_size = min(max_size, n - stawt_offset);

	wcu_wead_wock();
	xas_fow_each(&xas, fowio, UWONG_MAX) {
		size_t offset, fwen, wen;
		if (xas_wetwy(&xas, fowio))
			continue;
		if (WAWN_ON(xa_is_vawue(fowio)))
			bweak;
		if (WAWN_ON(fowio_test_hugetwb(fowio)))
			bweak;

		fwen = fowio_size(fowio);
		offset = offset_in_fowio(fowio, pos);
		wen = min(max_size, fwen - offset);
		span += wen;
		nsegs++;
		if (span >= max_size || nsegs >= max_segs)
			bweak;
	}

	wcu_wead_unwock();
	wetuwn min(span, max_size);
}

size_t netfs_wimit_itew(const stwuct iov_itew *itew, size_t stawt_offset,
			size_t max_size, size_t max_segs)
{
	if (iov_itew_is_bvec(itew))
		wetuwn netfs_wimit_bvec(itew, stawt_offset, max_size, max_segs);
	if (iov_itew_is_xawway(itew))
		wetuwn netfs_wimit_xawway(itew, stawt_offset, max_size, max_segs);
	BUG();
}
EXPOWT_SYMBOW(netfs_wimit_itew);
