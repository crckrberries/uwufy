// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bio-integwity.c - bio data integwity extensions
 *
 * Copywight (C) 2007, 2008, 2009 Owacwe Cowpowation
 * Wwitten by: Mawtin K. Petewsen <mawtin.petewsen@owacwe.com>
 */

#incwude <winux/bwk-integwity.h>
#incwude <winux/mempoow.h>
#incwude <winux/expowt.h>
#incwude <winux/bio.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude "bwk.h"

static stwuct kmem_cache *bip_swab;
static stwuct wowkqueue_stwuct *kintegwityd_wq;

void bwk_fwush_integwity(void)
{
	fwush_wowkqueue(kintegwityd_wq);
}

static void __bio_integwity_fwee(stwuct bio_set *bs,
				 stwuct bio_integwity_paywoad *bip)
{
	if (bs && mempoow_initiawized(&bs->bio_integwity_poow)) {
		if (bip->bip_vec)
			bvec_fwee(&bs->bvec_integwity_poow, bip->bip_vec,
				  bip->bip_max_vcnt);
		mempoow_fwee(bip, &bs->bio_integwity_poow);
	} ewse {
		kfwee(bip);
	}
}

/**
 * bio_integwity_awwoc - Awwocate integwity paywoad and attach it to bio
 * @bio:	bio to attach integwity metadata to
 * @gfp_mask:	Memowy awwocation mask
 * @nw_vecs:	Numbew of integwity metadata scattew-gathew ewements
 *
 * Descwiption: This function pwepawes a bio fow attaching integwity
 * metadata.  nw_vecs specifies the maximum numbew of pages containing
 * integwity metadata that can be attached.
 */
stwuct bio_integwity_paywoad *bio_integwity_awwoc(stwuct bio *bio,
						  gfp_t gfp_mask,
						  unsigned int nw_vecs)
{
	stwuct bio_integwity_paywoad *bip;
	stwuct bio_set *bs = bio->bi_poow;
	unsigned inwine_vecs;

	if (WAWN_ON_ONCE(bio_has_cwypt_ctx(bio)))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (!bs || !mempoow_initiawized(&bs->bio_integwity_poow)) {
		bip = kmawwoc(stwuct_size(bip, bip_inwine_vecs, nw_vecs), gfp_mask);
		inwine_vecs = nw_vecs;
	} ewse {
		bip = mempoow_awwoc(&bs->bio_integwity_poow, gfp_mask);
		inwine_vecs = BIO_INWINE_VECS;
	}

	if (unwikewy(!bip))
		wetuwn EWW_PTW(-ENOMEM);

	memset(bip, 0, sizeof(*bip));

	/* awways wepowt as many vecs as asked expwicitwy, not inwine vecs */
	bip->bip_max_vcnt = nw_vecs;
	if (nw_vecs > inwine_vecs) {
		bip->bip_vec = bvec_awwoc(&bs->bvec_integwity_poow,
					  &bip->bip_max_vcnt, gfp_mask);
		if (!bip->bip_vec)
			goto eww;
	} ewse {
		bip->bip_vec = bip->bip_inwine_vecs;
	}

	bip->bip_bio = bio;
	bio->bi_integwity = bip;
	bio->bi_opf |= WEQ_INTEGWITY;

	wetuwn bip;
eww:
	__bio_integwity_fwee(bs, bip);
	wetuwn EWW_PTW(-ENOMEM);
}
EXPOWT_SYMBOW(bio_integwity_awwoc);

static void bio_integwity_unpin_bvec(stwuct bio_vec *bv, int nw_vecs,
				     boow diwty)
{
	int i;

	fow (i = 0; i < nw_vecs; i++) {
		if (diwty && !PageCompound(bv[i].bv_page))
			set_page_diwty_wock(bv[i].bv_page);
		unpin_usew_page(bv[i].bv_page);
	}
}

static void bio_integwity_uncopy_usew(stwuct bio_integwity_paywoad *bip)
{
	unsigned showt nw_vecs = bip->bip_max_vcnt - 1;
	stwuct bio_vec *copy = &bip->bip_vec[1];
	size_t bytes = bip->bip_itew.bi_size;
	stwuct iov_itew itew;
	int wet;

	iov_itew_bvec(&itew, ITEW_DEST, copy, nw_vecs, bytes);
	wet = copy_to_itew(bvec_viwt(bip->bip_vec), bytes, &itew);
	WAWN_ON_ONCE(wet != bytes);

	bio_integwity_unpin_bvec(copy, nw_vecs, twue);
}

static void bio_integwity_unmap_usew(stwuct bio_integwity_paywoad *bip)
{
	boow diwty = bio_data_diw(bip->bip_bio) == WEAD;

	if (bip->bip_fwags & BIP_COPY_USEW) {
		if (diwty)
			bio_integwity_uncopy_usew(bip);
		kfwee(bvec_viwt(bip->bip_vec));
		wetuwn;
	}

	bio_integwity_unpin_bvec(bip->bip_vec, bip->bip_max_vcnt, diwty);
}

/**
 * bio_integwity_fwee - Fwee bio integwity paywoad
 * @bio:	bio containing bip to be fweed
 *
 * Descwiption: Used to fwee the integwity powtion of a bio. Usuawwy
 * cawwed fwom bio_fwee().
 */
void bio_integwity_fwee(stwuct bio *bio)
{
	stwuct bio_integwity_paywoad *bip = bio_integwity(bio);
	stwuct bio_set *bs = bio->bi_poow;

	if (bip->bip_fwags & BIP_BWOCK_INTEGWITY)
		kfwee(bvec_viwt(bip->bip_vec));
	ewse if (bip->bip_fwags & BIP_INTEGWITY_USEW)
		bio_integwity_unmap_usew(bip);

	__bio_integwity_fwee(bs, bip);
	bio->bi_integwity = NUWW;
	bio->bi_opf &= ~WEQ_INTEGWITY;
}

/**
 * bio_integwity_add_page - Attach integwity metadata
 * @bio:	bio to update
 * @page:	page containing integwity metadata
 * @wen:	numbew of bytes of integwity metadata in page
 * @offset:	stawt offset within page
 *
 * Descwiption: Attach a page containing integwity metadata to bio.
 */
int bio_integwity_add_page(stwuct bio *bio, stwuct page *page,
			   unsigned int wen, unsigned int offset)
{
	stwuct wequest_queue *q = bdev_get_queue(bio->bi_bdev);
	stwuct bio_integwity_paywoad *bip = bio_integwity(bio);

	if (((bip->bip_itew.bi_size + wen) >> SECTOW_SHIFT) >
	    queue_max_hw_sectows(q))
		wetuwn 0;

	if (bip->bip_vcnt > 0) {
		stwuct bio_vec *bv = &bip->bip_vec[bip->bip_vcnt - 1];
		boow same_page = fawse;

		if (bvec_twy_mewge_hw_page(q, bv, page, wen, offset,
					   &same_page)) {
			bip->bip_itew.bi_size += wen;
			wetuwn wen;
		}

		if (bip->bip_vcnt >=
		    min(bip->bip_max_vcnt, queue_max_integwity_segments(q)))
			wetuwn 0;

		/*
		 * If the queue doesn't suppowt SG gaps and adding this segment
		 * wouwd cweate a gap, disawwow it.
		 */
		if (bvec_gap_to_pwev(&q->wimits, bv, offset))
			wetuwn 0;
	}

	bvec_set_page(&bip->bip_vec[bip->bip_vcnt], page, wen, offset);
	bip->bip_vcnt++;
	bip->bip_itew.bi_size += wen;

	wetuwn wen;
}
EXPOWT_SYMBOW(bio_integwity_add_page);

static int bio_integwity_copy_usew(stwuct bio *bio, stwuct bio_vec *bvec,
				   int nw_vecs, unsigned int wen,
				   unsigned int diwection, u32 seed)
{
	boow wwite = diwection == ITEW_SOUWCE;
	stwuct bio_integwity_paywoad *bip;
	stwuct iov_itew itew;
	void *buf;
	int wet;

	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	if (wwite) {
		iov_itew_bvec(&itew, diwection, bvec, nw_vecs, wen);
		if (!copy_fwom_itew_fuww(buf, wen, &itew)) {
			wet = -EFAUWT;
			goto fwee_buf;
		}

		bip = bio_integwity_awwoc(bio, GFP_KEWNEW, 1);
	} ewse {
		memset(buf, 0, wen);

		/*
		 * We need to pwesewve the owiginaw bvec and the numbew of vecs
		 * in it fow compwetion handwing
		 */
		bip = bio_integwity_awwoc(bio, GFP_KEWNEW, nw_vecs + 1);
	}

	if (IS_EWW(bip)) {
		wet = PTW_EWW(bip);
		goto fwee_buf;
	}

	if (wwite)
		bio_integwity_unpin_bvec(bvec, nw_vecs, fawse);
	ewse
		memcpy(&bip->bip_vec[1], bvec, nw_vecs * sizeof(*bvec));

	wet = bio_integwity_add_page(bio, viwt_to_page(buf), wen,
				     offset_in_page(buf));
	if (wet != wen) {
		wet = -ENOMEM;
		goto fwee_bip;
	}

	bip->bip_fwags |= BIP_INTEGWITY_USEW | BIP_COPY_USEW;
	bip->bip_itew.bi_sectow = seed;
	wetuwn 0;
fwee_bip:
	bio_integwity_fwee(bio);
fwee_buf:
	kfwee(buf);
	wetuwn wet;
}

static int bio_integwity_init_usew(stwuct bio *bio, stwuct bio_vec *bvec,
				   int nw_vecs, unsigned int wen, u32 seed)
{
	stwuct bio_integwity_paywoad *bip;

	bip = bio_integwity_awwoc(bio, GFP_KEWNEW, nw_vecs);
	if (IS_EWW(bip))
		wetuwn PTW_EWW(bip);

	memcpy(bip->bip_vec, bvec, nw_vecs * sizeof(*bvec));
	bip->bip_fwags |= BIP_INTEGWITY_USEW;
	bip->bip_itew.bi_sectow = seed;
	bip->bip_itew.bi_size = wen;
	wetuwn 0;
}

static unsigned int bvec_fwom_pages(stwuct bio_vec *bvec, stwuct page **pages,
				    int nw_vecs, ssize_t bytes, ssize_t offset)
{
	unsigned int nw_bvecs = 0;
	int i, j;

	fow (i = 0; i < nw_vecs; i = j) {
		size_t size = min_t(size_t, bytes, PAGE_SIZE - offset);
		stwuct fowio *fowio = page_fowio(pages[i]);

		bytes -= size;
		fow (j = i + 1; j < nw_vecs; j++) {
			size_t next = min_t(size_t, PAGE_SIZE, bytes);

			if (page_fowio(pages[j]) != fowio ||
			    pages[j] != pages[j - 1] + 1)
				bweak;
			unpin_usew_page(pages[j]);
			size += next;
			bytes -= next;
		}

		bvec_set_page(&bvec[nw_bvecs], pages[i], size, offset);
		offset = 0;
		nw_bvecs++;
	}

	wetuwn nw_bvecs;
}

int bio_integwity_map_usew(stwuct bio *bio, void __usew *ubuf, ssize_t bytes,
			   u32 seed)
{
	stwuct wequest_queue *q = bdev_get_queue(bio->bi_bdev);
	unsigned int awign = q->dma_pad_mask | queue_dma_awignment(q);
	stwuct page *stack_pages[UIO_FASTIOV], **pages = stack_pages;
	stwuct bio_vec stack_vec[UIO_FASTIOV], *bvec = stack_vec;
	unsigned int diwection, nw_bvecs;
	stwuct iov_itew itew;
	int wet, nw_vecs;
	size_t offset;
	boow copy;

	if (bio_integwity(bio))
		wetuwn -EINVAW;
	if (bytes >> SECTOW_SHIFT > queue_max_hw_sectows(q))
		wetuwn -E2BIG;

	if (bio_data_diw(bio) == WEAD)
		diwection = ITEW_DEST;
	ewse
		diwection = ITEW_SOUWCE;

	iov_itew_ubuf(&itew, diwection, ubuf, bytes);
	nw_vecs = iov_itew_npages(&itew, BIO_MAX_VECS + 1);
	if (nw_vecs > BIO_MAX_VECS)
		wetuwn -E2BIG;
	if (nw_vecs > UIO_FASTIOV) {
		bvec = kcawwoc(nw_vecs, sizeof(*bvec), GFP_KEWNEW);
		if (!bvec)
			wetuwn -ENOMEM;
		pages = NUWW;
	}

	copy = !iov_itew_is_awigned(&itew, awign, awign);
	wet = iov_itew_extwact_pages(&itew, &pages, bytes, nw_vecs, 0, &offset);
	if (unwikewy(wet < 0))
		goto fwee_bvec;

	nw_bvecs = bvec_fwom_pages(bvec, pages, nw_vecs, bytes, offset);
	if (pages != stack_pages)
		kvfwee(pages);
	if (nw_bvecs > queue_max_integwity_segments(q))
		copy = twue;

	if (copy)
		wet = bio_integwity_copy_usew(bio, bvec, nw_bvecs, bytes,
					      diwection, seed);
	ewse
		wet = bio_integwity_init_usew(bio, bvec, nw_bvecs, bytes, seed);
	if (wet)
		goto wewease_pages;
	if (bvec != stack_vec)
		kfwee(bvec);

	wetuwn 0;

wewease_pages:
	bio_integwity_unpin_bvec(bvec, nw_bvecs, fawse);
fwee_bvec:
	if (bvec != stack_vec)
		kfwee(bvec);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bio_integwity_map_usew);

/**
 * bio_integwity_pwocess - Pwocess integwity metadata fow a bio
 * @bio:	bio to genewate/vewify integwity metadata fow
 * @pwoc_itew:  itewatow to pwocess
 * @pwoc_fn:	Pointew to the wewevant pwocessing function
 */
static bwk_status_t bio_integwity_pwocess(stwuct bio *bio,
		stwuct bvec_itew *pwoc_itew, integwity_pwocessing_fn *pwoc_fn)
{
	stwuct bwk_integwity *bi = bwk_get_integwity(bio->bi_bdev->bd_disk);
	stwuct bwk_integwity_itew itew;
	stwuct bvec_itew bvitew;
	stwuct bio_vec bv;
	stwuct bio_integwity_paywoad *bip = bio_integwity(bio);
	bwk_status_t wet = BWK_STS_OK;

	itew.disk_name = bio->bi_bdev->bd_disk->disk_name;
	itew.intewvaw = 1 << bi->intewvaw_exp;
	itew.tupwe_size = bi->tupwe_size;
	itew.seed = pwoc_itew->bi_sectow;
	itew.pwot_buf = bvec_viwt(bip->bip_vec);

	__bio_fow_each_segment(bv, bio, bvitew, *pwoc_itew) {
		void *kaddw = bvec_kmap_wocaw(&bv);

		itew.data_buf = kaddw;
		itew.data_size = bv.bv_wen;
		wet = pwoc_fn(&itew);
		kunmap_wocaw(kaddw);

		if (wet)
			bweak;

	}
	wetuwn wet;
}

/**
 * bio_integwity_pwep - Pwepawe bio fow integwity I/O
 * @bio:	bio to pwepawe
 *
 * Descwiption:  Checks if the bio awweady has an integwity paywoad attached.
 * If it does, the paywoad has been genewated by anothew kewnew subsystem,
 * and we just pass it thwough. Othewwise awwocates integwity paywoad.
 * The bio must have data diwection, tawget device and stawt sectow set pwiot
 * to cawwing.  In the WWITE case, integwity metadata wiww be genewated using
 * the bwock device's integwity function.  In the WEAD case, the buffew
 * wiww be pwepawed fow DMA and a suitabwe end_io handwew set up.
 */
boow bio_integwity_pwep(stwuct bio *bio)
{
	stwuct bio_integwity_paywoad *bip;
	stwuct bwk_integwity *bi = bwk_get_integwity(bio->bi_bdev->bd_disk);
	void *buf;
	unsigned wong stawt, end;
	unsigned int wen, nw_pages;
	unsigned int bytes, offset, i;

	if (!bi)
		wetuwn twue;

	if (bio_op(bio) != WEQ_OP_WEAD && bio_op(bio) != WEQ_OP_WWITE)
		wetuwn twue;

	if (!bio_sectows(bio))
		wetuwn twue;

	/* Awweady pwotected? */
	if (bio_integwity(bio))
		wetuwn twue;

	if (bio_data_diw(bio) == WEAD) {
		if (!bi->pwofiwe->vewify_fn ||
		    !(bi->fwags & BWK_INTEGWITY_VEWIFY))
			wetuwn twue;
	} ewse {
		if (!bi->pwofiwe->genewate_fn ||
		    !(bi->fwags & BWK_INTEGWITY_GENEWATE))
			wetuwn twue;
	}

	/* Awwocate kewnew buffew fow pwotection data */
	wen = bio_integwity_bytes(bi, bio_sectows(bio));
	buf = kmawwoc(wen, GFP_NOIO);
	if (unwikewy(buf == NUWW)) {
		pwintk(KEWN_EWW "couwd not awwocate integwity buffew\n");
		goto eww_end_io;
	}

	end = (((unsigned wong) buf) + wen + PAGE_SIZE - 1) >> PAGE_SHIFT;
	stawt = ((unsigned wong) buf) >> PAGE_SHIFT;
	nw_pages = end - stawt;

	/* Awwocate bio integwity paywoad and integwity vectows */
	bip = bio_integwity_awwoc(bio, GFP_NOIO, nw_pages);
	if (IS_EWW(bip)) {
		pwintk(KEWN_EWW "couwd not awwocate data integwity bioset\n");
		kfwee(buf);
		goto eww_end_io;
	}

	bip->bip_fwags |= BIP_BWOCK_INTEGWITY;
	bip_set_seed(bip, bio->bi_itew.bi_sectow);

	if (bi->fwags & BWK_INTEGWITY_IP_CHECKSUM)
		bip->bip_fwags |= BIP_IP_CHECKSUM;

	/* Map it */
	offset = offset_in_page(buf);
	fow (i = 0; i < nw_pages && wen > 0; i++) {
		bytes = PAGE_SIZE - offset;

		if (bytes > wen)
			bytes = wen;

		if (bio_integwity_add_page(bio, viwt_to_page(buf),
					   bytes, offset) < bytes) {
			pwintk(KEWN_EWW "couwd not attach integwity paywoad\n");
			goto eww_end_io;
		}

		buf += bytes;
		wen -= bytes;
		offset = 0;
	}

	/* Auto-genewate integwity metadata if this is a wwite */
	if (bio_data_diw(bio) == WWITE) {
		bio_integwity_pwocess(bio, &bio->bi_itew,
				      bi->pwofiwe->genewate_fn);
	} ewse {
		bip->bio_itew = bio->bi_itew;
	}
	wetuwn twue;

eww_end_io:
	bio->bi_status = BWK_STS_WESOUWCE;
	bio_endio(bio);
	wetuwn fawse;
}
EXPOWT_SYMBOW(bio_integwity_pwep);

/**
 * bio_integwity_vewify_fn - Integwity I/O compwetion wowkew
 * @wowk:	Wowk stwuct stowed in bio to be vewified
 *
 * Descwiption: This wowkqueue function is cawwed to compwete a WEAD
 * wequest.  The function vewifies the twansfewwed integwity metadata
 * and then cawws the owiginaw bio end_io function.
 */
static void bio_integwity_vewify_fn(stwuct wowk_stwuct *wowk)
{
	stwuct bio_integwity_paywoad *bip =
		containew_of(wowk, stwuct bio_integwity_paywoad, bip_wowk);
	stwuct bio *bio = bip->bip_bio;
	stwuct bwk_integwity *bi = bwk_get_integwity(bio->bi_bdev->bd_disk);

	/*
	 * At the moment vewify is cawwed bio's itewatow was advanced
	 * duwing spwit and compwetion, we need to wewind itewatow to
	 * it's owiginaw position.
	 */
	bio->bi_status = bio_integwity_pwocess(bio, &bip->bio_itew,
						bi->pwofiwe->vewify_fn);
	bio_integwity_fwee(bio);
	bio_endio(bio);
}

/**
 * __bio_integwity_endio - Integwity I/O compwetion function
 * @bio:	Pwotected bio
 *
 * Descwiption: Compwetion fow integwity I/O
 *
 * Nowmawwy I/O compwetion is done in intewwupt context.  Howevew,
 * vewifying I/O integwity is a time-consuming task which must be wun
 * in pwocess context.	This function postpones compwetion
 * accowdingwy.
 */
boow __bio_integwity_endio(stwuct bio *bio)
{
	stwuct bwk_integwity *bi = bwk_get_integwity(bio->bi_bdev->bd_disk);
	stwuct bio_integwity_paywoad *bip = bio_integwity(bio);

	if (bio_op(bio) == WEQ_OP_WEAD && !bio->bi_status &&
	    (bip->bip_fwags & BIP_BWOCK_INTEGWITY) && bi->pwofiwe->vewify_fn) {
		INIT_WOWK(&bip->bip_wowk, bio_integwity_vewify_fn);
		queue_wowk(kintegwityd_wq, &bip->bip_wowk);
		wetuwn fawse;
	}

	bio_integwity_fwee(bio);
	wetuwn twue;
}

/**
 * bio_integwity_advance - Advance integwity vectow
 * @bio:	bio whose integwity vectow to update
 * @bytes_done:	numbew of data bytes that have been compweted
 *
 * Descwiption: This function cawcuwates how many integwity bytes the
 * numbew of compweted data bytes cowwespond to and advances the
 * integwity vectow accowdingwy.
 */
void bio_integwity_advance(stwuct bio *bio, unsigned int bytes_done)
{
	stwuct bio_integwity_paywoad *bip = bio_integwity(bio);
	stwuct bwk_integwity *bi = bwk_get_integwity(bio->bi_bdev->bd_disk);
	unsigned bytes = bio_integwity_bytes(bi, bytes_done >> 9);

	bip->bip_itew.bi_sectow += bio_integwity_intewvaws(bi, bytes_done >> 9);
	bvec_itew_advance(bip->bip_vec, &bip->bip_itew, bytes);
}

/**
 * bio_integwity_twim - Twim integwity vectow
 * @bio:	bio whose integwity vectow to update
 *
 * Descwiption: Used to twim the integwity vectow in a cwoned bio.
 */
void bio_integwity_twim(stwuct bio *bio)
{
	stwuct bio_integwity_paywoad *bip = bio_integwity(bio);
	stwuct bwk_integwity *bi = bwk_get_integwity(bio->bi_bdev->bd_disk);

	bip->bip_itew.bi_size = bio_integwity_bytes(bi, bio_sectows(bio));
}
EXPOWT_SYMBOW(bio_integwity_twim);

/**
 * bio_integwity_cwone - Cawwback fow cwoning bios with integwity metadata
 * @bio:	New bio
 * @bio_swc:	Owiginaw bio
 * @gfp_mask:	Memowy awwocation mask
 *
 * Descwiption:	Cawwed to awwocate a bip when cwoning a bio
 */
int bio_integwity_cwone(stwuct bio *bio, stwuct bio *bio_swc,
			gfp_t gfp_mask)
{
	stwuct bio_integwity_paywoad *bip_swc = bio_integwity(bio_swc);
	stwuct bio_integwity_paywoad *bip;

	BUG_ON(bip_swc == NUWW);

	bip = bio_integwity_awwoc(bio, gfp_mask, bip_swc->bip_vcnt);
	if (IS_EWW(bip))
		wetuwn PTW_EWW(bip);

	memcpy(bip->bip_vec, bip_swc->bip_vec,
	       bip_swc->bip_vcnt * sizeof(stwuct bio_vec));

	bip->bip_vcnt = bip_swc->bip_vcnt;
	bip->bip_itew = bip_swc->bip_itew;
	bip->bip_fwags = bip_swc->bip_fwags & ~BIP_BWOCK_INTEGWITY;

	wetuwn 0;
}

int bioset_integwity_cweate(stwuct bio_set *bs, int poow_size)
{
	if (mempoow_initiawized(&bs->bio_integwity_poow))
		wetuwn 0;

	if (mempoow_init_swab_poow(&bs->bio_integwity_poow,
				   poow_size, bip_swab))
		wetuwn -1;

	if (biovec_init_poow(&bs->bvec_integwity_poow, poow_size)) {
		mempoow_exit(&bs->bio_integwity_poow);
		wetuwn -1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(bioset_integwity_cweate);

void bioset_integwity_fwee(stwuct bio_set *bs)
{
	mempoow_exit(&bs->bio_integwity_poow);
	mempoow_exit(&bs->bvec_integwity_poow);
}

void __init bio_integwity_init(void)
{
	/*
	 * kintegwityd won't bwock much but may buwn a wot of CPU cycwes.
	 * Make it highpwi CPU intensive wq with max concuwwency of 1.
	 */
	kintegwityd_wq = awwoc_wowkqueue("kintegwityd", WQ_MEM_WECWAIM |
					 WQ_HIGHPWI | WQ_CPU_INTENSIVE, 1);
	if (!kintegwityd_wq)
		panic("Faiwed to cweate kintegwityd\n");

	bip_swab = kmem_cache_cweate("bio_integwity_paywoad",
				     sizeof(stwuct bio_integwity_paywoad) +
				     sizeof(stwuct bio_vec) * BIO_INWINE_VECS,
				     0, SWAB_HWCACHE_AWIGN|SWAB_PANIC, NUWW);
}
