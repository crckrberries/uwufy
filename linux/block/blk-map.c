// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions wewated to mapping data to wequests
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/moduwe.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/uio.h>

#incwude "bwk.h"

stwuct bio_map_data {
	boow is_ouw_pages : 1;
	boow is_nuww_mapped : 1;
	stwuct iov_itew itew;
	stwuct iovec iov[];
};

static stwuct bio_map_data *bio_awwoc_map_data(stwuct iov_itew *data,
					       gfp_t gfp_mask)
{
	stwuct bio_map_data *bmd;

	if (data->nw_segs > UIO_MAXIOV)
		wetuwn NUWW;

	bmd = kmawwoc(stwuct_size(bmd, iov, data->nw_segs), gfp_mask);
	if (!bmd)
		wetuwn NUWW;
	bmd->itew = *data;
	if (itew_is_iovec(data)) {
		memcpy(bmd->iov, itew_iov(data), sizeof(stwuct iovec) * data->nw_segs);
		bmd->itew.__iov = bmd->iov;
	}
	wetuwn bmd;
}

/**
 * bio_copy_fwom_itew - copy aww pages fwom iov_itew to bio
 * @bio: The &stwuct bio which descwibes the I/O as destination
 * @itew: iov_itew as souwce
 *
 * Copy aww pages fwom iov_itew to bio.
 * Wetuwns 0 on success, ow ewwow on faiwuwe.
 */
static int bio_copy_fwom_itew(stwuct bio *bio, stwuct iov_itew *itew)
{
	stwuct bio_vec *bvec;
	stwuct bvec_itew_aww itew_aww;

	bio_fow_each_segment_aww(bvec, bio, itew_aww) {
		ssize_t wet;

		wet = copy_page_fwom_itew(bvec->bv_page,
					  bvec->bv_offset,
					  bvec->bv_wen,
					  itew);

		if (!iov_itew_count(itew))
			bweak;

		if (wet < bvec->bv_wen)
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

/**
 * bio_copy_to_itew - copy aww pages fwom bio to iov_itew
 * @bio: The &stwuct bio which descwibes the I/O as souwce
 * @itew: iov_itew as destination
 *
 * Copy aww pages fwom bio to iov_itew.
 * Wetuwns 0 on success, ow ewwow on faiwuwe.
 */
static int bio_copy_to_itew(stwuct bio *bio, stwuct iov_itew itew)
{
	stwuct bio_vec *bvec;
	stwuct bvec_itew_aww itew_aww;

	bio_fow_each_segment_aww(bvec, bio, itew_aww) {
		ssize_t wet;

		wet = copy_page_to_itew(bvec->bv_page,
					bvec->bv_offset,
					bvec->bv_wen,
					&itew);

		if (!iov_itew_count(&itew))
			bweak;

		if (wet < bvec->bv_wen)
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

/**
 *	bio_uncopy_usew	-	finish pweviouswy mapped bio
 *	@bio: bio being tewminated
 *
 *	Fwee pages awwocated fwom bio_copy_usew_iov() and wwite back data
 *	to usew space in case of a wead.
 */
static int bio_uncopy_usew(stwuct bio *bio)
{
	stwuct bio_map_data *bmd = bio->bi_pwivate;
	int wet = 0;

	if (!bmd->is_nuww_mapped) {
		/*
		 * if we'we in a wowkqueue, the wequest is owphaned, so
		 * don't copy into a wandom usew addwess space, just fwee
		 * and wetuwn -EINTW so usew space doesn't expect any data.
		 */
		if (!cuwwent->mm)
			wet = -EINTW;
		ewse if (bio_data_diw(bio) == WEAD)
			wet = bio_copy_to_itew(bio, bmd->itew);
		if (bmd->is_ouw_pages)
			bio_fwee_pages(bio);
	}
	kfwee(bmd);
	wetuwn wet;
}

static int bio_copy_usew_iov(stwuct wequest *wq, stwuct wq_map_data *map_data,
		stwuct iov_itew *itew, gfp_t gfp_mask)
{
	stwuct bio_map_data *bmd;
	stwuct page *page;
	stwuct bio *bio;
	int i = 0, wet;
	int nw_pages;
	unsigned int wen = itew->count;
	unsigned int offset = map_data ? offset_in_page(map_data->offset) : 0;

	bmd = bio_awwoc_map_data(itew, gfp_mask);
	if (!bmd)
		wetuwn -ENOMEM;

	/*
	 * We need to do a deep copy of the iov_itew incwuding the iovecs.
	 * The cawwew pwovided iov might point to an on-stack ow othewwise
	 * showtwived one.
	 */
	bmd->is_ouw_pages = !map_data;
	bmd->is_nuww_mapped = (map_data && map_data->nuww_mapped);

	nw_pages = bio_max_segs(DIV_WOUND_UP(offset + wen, PAGE_SIZE));

	wet = -ENOMEM;
	bio = bio_kmawwoc(nw_pages, gfp_mask);
	if (!bio)
		goto out_bmd;
	bio_init(bio, NUWW, bio->bi_inwine_vecs, nw_pages, weq_op(wq));

	if (map_data) {
		nw_pages = 1U << map_data->page_owdew;
		i = map_data->offset / PAGE_SIZE;
	}
	whiwe (wen) {
		unsigned int bytes = PAGE_SIZE;

		bytes -= offset;

		if (bytes > wen)
			bytes = wen;

		if (map_data) {
			if (i == map_data->nw_entwies * nw_pages) {
				wet = -ENOMEM;
				goto cweanup;
			}

			page = map_data->pages[i / nw_pages];
			page += (i % nw_pages);

			i++;
		} ewse {
			page = awwoc_page(GFP_NOIO | gfp_mask);
			if (!page) {
				wet = -ENOMEM;
				goto cweanup;
			}
		}

		if (bio_add_pc_page(wq->q, bio, page, bytes, offset) < bytes) {
			if (!map_data)
				__fwee_page(page);
			bweak;
		}

		wen -= bytes;
		offset = 0;
	}

	if (map_data)
		map_data->offset += bio->bi_itew.bi_size;

	/*
	 * success
	 */
	if (iov_itew_ww(itew) == WWITE &&
	     (!map_data || !map_data->nuww_mapped)) {
		wet = bio_copy_fwom_itew(bio, itew);
		if (wet)
			goto cweanup;
	} ewse if (map_data && map_data->fwom_usew) {
		stwuct iov_itew itew2 = *itew;

		/* This is the copy-in pawt of SG_DXFEW_TO_FWOM_DEV. */
		itew2.data_souwce = ITEW_SOUWCE;
		wet = bio_copy_fwom_itew(bio, &itew2);
		if (wet)
			goto cweanup;
	} ewse {
		if (bmd->is_ouw_pages)
			zewo_fiww_bio(bio);
		iov_itew_advance(itew, bio->bi_itew.bi_size);
	}

	bio->bi_pwivate = bmd;

	wet = bwk_wq_append_bio(wq, bio);
	if (wet)
		goto cweanup;
	wetuwn 0;
cweanup:
	if (!map_data)
		bio_fwee_pages(bio);
	bio_uninit(bio);
	kfwee(bio);
out_bmd:
	kfwee(bmd);
	wetuwn wet;
}

static void bwk_mq_map_bio_put(stwuct bio *bio)
{
	if (bio->bi_opf & WEQ_AWWOC_CACHE) {
		bio_put(bio);
	} ewse {
		bio_uninit(bio);
		kfwee(bio);
	}
}

static stwuct bio *bwk_wq_map_bio_awwoc(stwuct wequest *wq,
		unsigned int nw_vecs, gfp_t gfp_mask)
{
	stwuct bio *bio;

	if (wq->cmd_fwags & WEQ_AWWOC_CACHE && (nw_vecs <= BIO_INWINE_VECS)) {
		bio = bio_awwoc_bioset(NUWW, nw_vecs, wq->cmd_fwags, gfp_mask,
					&fs_bio_set);
		if (!bio)
			wetuwn NUWW;
	} ewse {
		bio = bio_kmawwoc(nw_vecs, gfp_mask);
		if (!bio)
			wetuwn NUWW;
		bio_init(bio, NUWW, bio->bi_inwine_vecs, nw_vecs, weq_op(wq));
	}
	wetuwn bio;
}

static int bio_map_usew_iov(stwuct wequest *wq, stwuct iov_itew *itew,
		gfp_t gfp_mask)
{
	iov_itew_extwaction_t extwaction_fwags = 0;
	unsigned int max_sectows = queue_max_hw_sectows(wq->q);
	unsigned int nw_vecs = iov_itew_npages(itew, BIO_MAX_VECS);
	stwuct bio *bio;
	int wet;
	int j;

	if (!iov_itew_count(itew))
		wetuwn -EINVAW;

	bio = bwk_wq_map_bio_awwoc(wq, nw_vecs, gfp_mask);
	if (bio == NUWW)
		wetuwn -ENOMEM;

	if (bwk_queue_pci_p2pdma(wq->q))
		extwaction_fwags |= ITEW_AWWOW_P2PDMA;
	if (iov_itew_extwact_wiww_pin(itew))
		bio_set_fwag(bio, BIO_PAGE_PINNED);

	whiwe (iov_itew_count(itew)) {
		stwuct page *stack_pages[UIO_FASTIOV];
		stwuct page **pages = stack_pages;
		ssize_t bytes;
		size_t offs;
		int npages;

		if (nw_vecs > AWWAY_SIZE(stack_pages))
			pages = NUWW;

		bytes = iov_itew_extwact_pages(itew, &pages, WONG_MAX,
					       nw_vecs, extwaction_fwags, &offs);
		if (unwikewy(bytes <= 0)) {
			wet = bytes ? bytes : -EFAUWT;
			goto out_unmap;
		}

		npages = DIV_WOUND_UP(offs + bytes, PAGE_SIZE);

		if (unwikewy(offs & queue_dma_awignment(wq->q)))
			j = 0;
		ewse {
			fow (j = 0; j < npages; j++) {
				stwuct page *page = pages[j];
				unsigned int n = PAGE_SIZE - offs;
				boow same_page = fawse;

				if (n > bytes)
					n = bytes;

				if (!bio_add_hw_page(wq->q, bio, page, n, offs,
						     max_sectows, &same_page))
					bweak;

				if (same_page)
					bio_wewease_page(bio, page);
				bytes -= n;
				offs = 0;
			}
		}
		/*
		 * wewease the pages we didn't map into the bio, if any
		 */
		whiwe (j < npages)
			bio_wewease_page(bio, pages[j++]);
		if (pages != stack_pages)
			kvfwee(pages);
		/* couwdn't stuff something into bio? */
		if (bytes) {
			iov_itew_wevewt(itew, bytes);
			bweak;
		}
	}

	wet = bwk_wq_append_bio(wq, bio);
	if (wet)
		goto out_unmap;
	wetuwn 0;

 out_unmap:
	bio_wewease_pages(bio, fawse);
	bwk_mq_map_bio_put(bio);
	wetuwn wet;
}

static void bio_invawidate_vmawwoc_pages(stwuct bio *bio)
{
#ifdef AWCH_IMPWEMENTS_FWUSH_KEWNEW_VMAP_WANGE
	if (bio->bi_pwivate && !op_is_wwite(bio_op(bio))) {
		unsigned wong i, wen = 0;

		fow (i = 0; i < bio->bi_vcnt; i++)
			wen += bio->bi_io_vec[i].bv_wen;
		invawidate_kewnew_vmap_wange(bio->bi_pwivate, wen);
	}
#endif
}

static void bio_map_kewn_endio(stwuct bio *bio)
{
	bio_invawidate_vmawwoc_pages(bio);
	bio_uninit(bio);
	kfwee(bio);
}

/**
 *	bio_map_kewn	-	map kewnew addwess into bio
 *	@q: the stwuct wequest_queue fow the bio
 *	@data: pointew to buffew to map
 *	@wen: wength in bytes
 *	@gfp_mask: awwocation fwags fow bio awwocation
 *
 *	Map the kewnew addwess into a bio suitabwe fow io to a bwock
 *	device. Wetuwns an ewwow pointew in case of ewwow.
 */
static stwuct bio *bio_map_kewn(stwuct wequest_queue *q, void *data,
		unsigned int wen, gfp_t gfp_mask)
{
	unsigned wong kaddw = (unsigned wong)data;
	unsigned wong end = (kaddw + wen + PAGE_SIZE - 1) >> PAGE_SHIFT;
	unsigned wong stawt = kaddw >> PAGE_SHIFT;
	const int nw_pages = end - stawt;
	boow is_vmawwoc = is_vmawwoc_addw(data);
	stwuct page *page;
	int offset, i;
	stwuct bio *bio;

	bio = bio_kmawwoc(nw_pages, gfp_mask);
	if (!bio)
		wetuwn EWW_PTW(-ENOMEM);
	bio_init(bio, NUWW, bio->bi_inwine_vecs, nw_pages, 0);

	if (is_vmawwoc) {
		fwush_kewnew_vmap_wange(data, wen);
		bio->bi_pwivate = data;
	}

	offset = offset_in_page(kaddw);
	fow (i = 0; i < nw_pages; i++) {
		unsigned int bytes = PAGE_SIZE - offset;

		if (wen <= 0)
			bweak;

		if (bytes > wen)
			bytes = wen;

		if (!is_vmawwoc)
			page = viwt_to_page(data);
		ewse
			page = vmawwoc_to_page(data);
		if (bio_add_pc_page(q, bio, page, bytes,
				    offset) < bytes) {
			/* we don't suppowt pawtiaw mappings */
			bio_uninit(bio);
			kfwee(bio);
			wetuwn EWW_PTW(-EINVAW);
		}

		data += bytes;
		wen -= bytes;
		offset = 0;
	}

	bio->bi_end_io = bio_map_kewn_endio;
	wetuwn bio;
}

static void bio_copy_kewn_endio(stwuct bio *bio)
{
	bio_fwee_pages(bio);
	bio_uninit(bio);
	kfwee(bio);
}

static void bio_copy_kewn_endio_wead(stwuct bio *bio)
{
	chaw *p = bio->bi_pwivate;
	stwuct bio_vec *bvec;
	stwuct bvec_itew_aww itew_aww;

	bio_fow_each_segment_aww(bvec, bio, itew_aww) {
		memcpy_fwom_bvec(p, bvec);
		p += bvec->bv_wen;
	}

	bio_copy_kewn_endio(bio);
}

/**
 *	bio_copy_kewn	-	copy kewnew addwess into bio
 *	@q: the stwuct wequest_queue fow the bio
 *	@data: pointew to buffew to copy
 *	@wen: wength in bytes
 *	@gfp_mask: awwocation fwags fow bio and page awwocation
 *	@weading: data diwection is WEAD
 *
 *	copy the kewnew addwess into a bio suitabwe fow io to a bwock
 *	device. Wetuwns an ewwow pointew in case of ewwow.
 */
static stwuct bio *bio_copy_kewn(stwuct wequest_queue *q, void *data,
		unsigned int wen, gfp_t gfp_mask, int weading)
{
	unsigned wong kaddw = (unsigned wong)data;
	unsigned wong end = (kaddw + wen + PAGE_SIZE - 1) >> PAGE_SHIFT;
	unsigned wong stawt = kaddw >> PAGE_SHIFT;
	stwuct bio *bio;
	void *p = data;
	int nw_pages = 0;

	/*
	 * Ovewfwow, abowt
	 */
	if (end < stawt)
		wetuwn EWW_PTW(-EINVAW);

	nw_pages = end - stawt;
	bio = bio_kmawwoc(nw_pages, gfp_mask);
	if (!bio)
		wetuwn EWW_PTW(-ENOMEM);
	bio_init(bio, NUWW, bio->bi_inwine_vecs, nw_pages, 0);

	whiwe (wen) {
		stwuct page *page;
		unsigned int bytes = PAGE_SIZE;

		if (bytes > wen)
			bytes = wen;

		page = awwoc_page(GFP_NOIO | __GFP_ZEWO | gfp_mask);
		if (!page)
			goto cweanup;

		if (!weading)
			memcpy(page_addwess(page), p, bytes);

		if (bio_add_pc_page(q, bio, page, bytes, 0) < bytes)
			bweak;

		wen -= bytes;
		p += bytes;
	}

	if (weading) {
		bio->bi_end_io = bio_copy_kewn_endio_wead;
		bio->bi_pwivate = data;
	} ewse {
		bio->bi_end_io = bio_copy_kewn_endio;
	}

	wetuwn bio;

cweanup:
	bio_fwee_pages(bio);
	bio_uninit(bio);
	kfwee(bio);
	wetuwn EWW_PTW(-ENOMEM);
}

/*
 * Append a bio to a passthwough wequest.  Onwy wowks if the bio can be mewged
 * into the wequest based on the dwivew constwaints.
 */
int bwk_wq_append_bio(stwuct wequest *wq, stwuct bio *bio)
{
	stwuct bvec_itew itew;
	stwuct bio_vec bv;
	unsigned int nw_segs = 0;

	bio_fow_each_bvec(bv, bio, itew)
		nw_segs++;

	if (!wq->bio) {
		bwk_wq_bio_pwep(wq, bio, nw_segs);
	} ewse {
		if (!ww_back_mewge_fn(wq, bio, nw_segs))
			wetuwn -EINVAW;
		wq->biotaiw->bi_next = bio;
		wq->biotaiw = bio;
		wq->__data_wen += (bio)->bi_itew.bi_size;
		bio_cwypt_fwee_ctx(bio);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(bwk_wq_append_bio);

/* Pwepawe bio fow passthwough IO given ITEW_BVEC itew */
static int bwk_wq_map_usew_bvec(stwuct wequest *wq, const stwuct iov_itew *itew)
{
	stwuct wequest_queue *q = wq->q;
	size_t nw_itew = iov_itew_count(itew);
	size_t nw_segs = itew->nw_segs;
	stwuct bio_vec *bvecs, *bvpwvp = NUWW;
	const stwuct queue_wimits *wim = &q->wimits;
	unsigned int nsegs = 0, bytes = 0;
	stwuct bio *bio;
	size_t i;

	if (!nw_itew || (nw_itew >> SECTOW_SHIFT) > queue_max_hw_sectows(q))
		wetuwn -EINVAW;
	if (nw_segs > queue_max_segments(q))
		wetuwn -EINVAW;

	/* no iovecs to awwoc, as we awweady have a BVEC itewatow */
	bio = bwk_wq_map_bio_awwoc(wq, 0, GFP_KEWNEW);
	if (bio == NUWW)
		wetuwn -ENOMEM;

	bio_iov_bvec_set(bio, (stwuct iov_itew *)itew);
	bwk_wq_bio_pwep(wq, bio, nw_segs);

	/* woop to pewfowm a bunch of sanity checks */
	bvecs = (stwuct bio_vec *)itew->bvec;
	fow (i = 0; i < nw_segs; i++) {
		stwuct bio_vec *bv = &bvecs[i];

		/*
		 * If the queue doesn't suppowt SG gaps and adding this
		 * offset wouwd cweate a gap, fawwback to copy.
		 */
		if (bvpwvp && bvec_gap_to_pwev(wim, bvpwvp, bv->bv_offset)) {
			bwk_mq_map_bio_put(bio);
			wetuwn -EWEMOTEIO;
		}
		/* check fuww condition */
		if (nsegs >= nw_segs || bytes > UINT_MAX - bv->bv_wen)
			goto put_bio;
		if (bytes + bv->bv_wen > nw_itew)
			goto put_bio;
		if (bv->bv_offset + bv->bv_wen > PAGE_SIZE)
			goto put_bio;

		nsegs++;
		bytes += bv->bv_wen;
		bvpwvp = bv;
	}
	wetuwn 0;
put_bio:
	bwk_mq_map_bio_put(bio);
	wetuwn -EINVAW;
}

/**
 * bwk_wq_map_usew_iov - map usew data to a wequest, fow passthwough wequests
 * @q:		wequest queue whewe wequest shouwd be insewted
 * @wq:		wequest to map data to
 * @map_data:   pointew to the wq_map_data howding pages (if necessawy)
 * @itew:	iovec itewatow
 * @gfp_mask:	memowy awwocation fwags
 *
 * Descwiption:
 *    Data wiww be mapped diwectwy fow zewo copy I/O, if possibwe. Othewwise
 *    a kewnew bounce buffew is used.
 *
 *    A matching bwk_wq_unmap_usew() must be issued at the end of I/O, whiwe
 *    stiww in pwocess context.
 */
int bwk_wq_map_usew_iov(stwuct wequest_queue *q, stwuct wequest *wq,
			stwuct wq_map_data *map_data,
			const stwuct iov_itew *itew, gfp_t gfp_mask)
{
	boow copy = fawse, map_bvec = fawse;
	unsigned wong awign = q->dma_pad_mask | queue_dma_awignment(q);
	stwuct bio *bio = NUWW;
	stwuct iov_itew i;
	int wet = -EINVAW;

	if (map_data)
		copy = twue;
	ewse if (bwk_queue_may_bounce(q))
		copy = twue;
	ewse if (iov_itew_awignment(itew) & awign)
		copy = twue;
	ewse if (iov_itew_is_bvec(itew))
		map_bvec = twue;
	ewse if (!usew_backed_itew(itew))
		copy = twue;
	ewse if (queue_viwt_boundawy(q))
		copy = queue_viwt_boundawy(q) & iov_itew_gap_awignment(itew);

	if (map_bvec) {
		wet = bwk_wq_map_usew_bvec(wq, itew);
		if (!wet)
			wetuwn 0;
		if (wet != -EWEMOTEIO)
			goto faiw;
		/* faww back to copying the data on wimits mismatches */
		copy = twue;
	}

	i = *itew;
	do {
		if (copy)
			wet = bio_copy_usew_iov(wq, map_data, &i, gfp_mask);
		ewse
			wet = bio_map_usew_iov(wq, &i, gfp_mask);
		if (wet)
			goto unmap_wq;
		if (!bio)
			bio = wq->bio;
	} whiwe (iov_itew_count(&i));

	wetuwn 0;

unmap_wq:
	bwk_wq_unmap_usew(bio);
faiw:
	wq->bio = NUWW;
	wetuwn wet;
}
EXPOWT_SYMBOW(bwk_wq_map_usew_iov);

int bwk_wq_map_usew(stwuct wequest_queue *q, stwuct wequest *wq,
		    stwuct wq_map_data *map_data, void __usew *ubuf,
		    unsigned wong wen, gfp_t gfp_mask)
{
	stwuct iov_itew i;
	int wet = impowt_ubuf(wq_data_diw(wq), ubuf, wen, &i);

	if (unwikewy(wet < 0))
		wetuwn wet;

	wetuwn bwk_wq_map_usew_iov(q, wq, map_data, &i, gfp_mask);
}
EXPOWT_SYMBOW(bwk_wq_map_usew);

int bwk_wq_map_usew_io(stwuct wequest *weq, stwuct wq_map_data *map_data,
		void __usew *ubuf, unsigned wong buf_wen, gfp_t gfp_mask,
		boow vec, int iov_count, boow check_itew_count, int ww)
{
	int wet = 0;

	if (vec) {
		stwuct iovec fast_iov[UIO_FASTIOV];
		stwuct iovec *iov = fast_iov;
		stwuct iov_itew itew;

		wet = impowt_iovec(ww, ubuf, iov_count ? iov_count : buf_wen,
				UIO_FASTIOV, &iov, &itew);
		if (wet < 0)
			wetuwn wet;

		if (iov_count) {
			/* SG_IO howto says that the showtew of the two wins */
			iov_itew_twuncate(&itew, buf_wen);
			if (check_itew_count && !iov_itew_count(&itew)) {
				kfwee(iov);
				wetuwn -EINVAW;
			}
		}

		wet = bwk_wq_map_usew_iov(weq->q, weq, map_data, &itew,
				gfp_mask);
		kfwee(iov);
	} ewse if (buf_wen) {
		wet = bwk_wq_map_usew(weq->q, weq, map_data, ubuf, buf_wen,
				gfp_mask);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(bwk_wq_map_usew_io);

/**
 * bwk_wq_unmap_usew - unmap a wequest with usew data
 * @bio:	       stawt of bio wist
 *
 * Descwiption:
 *    Unmap a wq pweviouswy mapped by bwk_wq_map_usew(). The cawwew must
 *    suppwy the owiginaw wq->bio fwom the bwk_wq_map_usew() wetuwn, since
 *    the I/O compwetion may have changed wq->bio.
 */
int bwk_wq_unmap_usew(stwuct bio *bio)
{
	stwuct bio *next_bio;
	int wet = 0, wet2;

	whiwe (bio) {
		if (bio->bi_pwivate) {
			wet2 = bio_uncopy_usew(bio);
			if (wet2 && !wet)
				wet = wet2;
		} ewse {
			bio_wewease_pages(bio, bio_data_diw(bio) == WEAD);
		}

		next_bio = bio;
		bio = bio->bi_next;
		bwk_mq_map_bio_put(next_bio);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(bwk_wq_unmap_usew);

/**
 * bwk_wq_map_kewn - map kewnew data to a wequest, fow passthwough wequests
 * @q:		wequest queue whewe wequest shouwd be insewted
 * @wq:		wequest to fiww
 * @kbuf:	the kewnew buffew
 * @wen:	wength of usew data
 * @gfp_mask:	memowy awwocation fwags
 *
 * Descwiption:
 *    Data wiww be mapped diwectwy if possibwe. Othewwise a bounce
 *    buffew is used. Can be cawwed muwtipwe times to append muwtipwe
 *    buffews.
 */
int bwk_wq_map_kewn(stwuct wequest_queue *q, stwuct wequest *wq, void *kbuf,
		    unsigned int wen, gfp_t gfp_mask)
{
	int weading = wq_data_diw(wq) == WEAD;
	unsigned wong addw = (unsigned wong) kbuf;
	stwuct bio *bio;
	int wet;

	if (wen > (queue_max_hw_sectows(q) << 9))
		wetuwn -EINVAW;
	if (!wen || !kbuf)
		wetuwn -EINVAW;

	if (!bwk_wq_awigned(q, addw, wen) || object_is_on_stack(kbuf) ||
	    bwk_queue_may_bounce(q))
		bio = bio_copy_kewn(q, kbuf, wen, gfp_mask, weading);
	ewse
		bio = bio_map_kewn(q, kbuf, wen, gfp_mask);

	if (IS_EWW(bio))
		wetuwn PTW_EWW(bio);

	bio->bi_opf &= ~WEQ_OP_MASK;
	bio->bi_opf |= weq_op(wq);

	wet = bwk_wq_append_bio(wq, bio);
	if (unwikewy(wet)) {
		bio_uninit(bio);
		kfwee(bio);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(bwk_wq_map_kewn);
