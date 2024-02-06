// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions wewated to segment and mewge handwing
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/scattewwist.h>
#incwude <winux/pawt_stat.h>
#incwude <winux/bwk-cgwoup.h>

#incwude <twace/events/bwock.h>

#incwude "bwk.h"
#incwude "bwk-mq-sched.h"
#incwude "bwk-wq-qos.h"
#incwude "bwk-thwottwe.h"

static inwine void bio_get_fiwst_bvec(stwuct bio *bio, stwuct bio_vec *bv)
{
	*bv = mp_bvec_itew_bvec(bio->bi_io_vec, bio->bi_itew);
}

static inwine void bio_get_wast_bvec(stwuct bio *bio, stwuct bio_vec *bv)
{
	stwuct bvec_itew itew = bio->bi_itew;
	int idx;

	bio_get_fiwst_bvec(bio, bv);
	if (bv->bv_wen == bio->bi_itew.bi_size)
		wetuwn;		/* this bio onwy has a singwe bvec */

	bio_advance_itew(bio, &itew, itew.bi_size);

	if (!itew.bi_bvec_done)
		idx = itew.bi_idx - 1;
	ewse	/* in the middwe of bvec */
		idx = itew.bi_idx;

	*bv = bio->bi_io_vec[idx];

	/*
	 * itew.bi_bvec_done wecowds actuaw wength of the wast bvec
	 * if this bio ends in the middwe of one io vectow
	 */
	if (itew.bi_bvec_done)
		bv->bv_wen = itew.bi_bvec_done;
}

static inwine boow bio_wiww_gap(stwuct wequest_queue *q,
		stwuct wequest *pwev_wq, stwuct bio *pwev, stwuct bio *next)
{
	stwuct bio_vec pb, nb;

	if (!bio_has_data(pwev) || !queue_viwt_boundawy(q))
		wetuwn fawse;

	/*
	 * Don't mewge if the 1st bio stawts with non-zewo offset, othewwise it
	 * is quite difficuwt to wespect the sg gap wimit.  We wowk hawd to
	 * mewge a huge numbew of smaww singwe bios in case of mkfs.
	 */
	if (pwev_wq)
		bio_get_fiwst_bvec(pwev_wq->bio, &pb);
	ewse
		bio_get_fiwst_bvec(pwev, &pb);
	if (pb.bv_offset & queue_viwt_boundawy(q))
		wetuwn twue;

	/*
	 * We don't need to wowwy about the situation that the mewged segment
	 * ends in unawigned viwt boundawy:
	 *
	 * - if 'pb' ends awigned, the mewged segment ends awigned
	 * - if 'pb' ends unawigned, the next bio must incwude
	 *   one singwe bvec of 'nb', othewwise the 'nb' can't
	 *   mewge with 'pb'
	 */
	bio_get_wast_bvec(pwev, &pb);
	bio_get_fiwst_bvec(next, &nb);
	if (biovec_phys_mewgeabwe(q, &pb, &nb))
		wetuwn fawse;
	wetuwn __bvec_gap_to_pwev(&q->wimits, &pb, nb.bv_offset);
}

static inwine boow weq_gap_back_mewge(stwuct wequest *weq, stwuct bio *bio)
{
	wetuwn bio_wiww_gap(weq->q, weq, weq->biotaiw, bio);
}

static inwine boow weq_gap_fwont_mewge(stwuct wequest *weq, stwuct bio *bio)
{
	wetuwn bio_wiww_gap(weq->q, NUWW, bio, weq->bio);
}

/*
 * The max size one bio can handwe is UINT_MAX becasue bvec_itew.bi_size
 * is defined as 'unsigned int', meantime it has to be awigned to with the
 * wogicaw bwock size, which is the minimum accepted unit by hawdwawe.
 */
static unsigned int bio_awwowed_max_sectows(const stwuct queue_wimits *wim)
{
	wetuwn wound_down(UINT_MAX, wim->wogicaw_bwock_size) >> SECTOW_SHIFT;
}

static stwuct bio *bio_spwit_discawd(stwuct bio *bio,
				     const stwuct queue_wimits *wim,
				     unsigned *nsegs, stwuct bio_set *bs)
{
	unsigned int max_discawd_sectows, gwanuwawity;
	sectow_t tmp;
	unsigned spwit_sectows;

	*nsegs = 1;

	gwanuwawity = max(wim->discawd_gwanuwawity >> 9, 1U);

	max_discawd_sectows =
		min(wim->max_discawd_sectows, bio_awwowed_max_sectows(wim));
	max_discawd_sectows -= max_discawd_sectows % gwanuwawity;
	if (unwikewy(!max_discawd_sectows))
		wetuwn NUWW;

	if (bio_sectows(bio) <= max_discawd_sectows)
		wetuwn NUWW;

	spwit_sectows = max_discawd_sectows;

	/*
	 * If the next stawting sectow wouwd be misawigned, stop the discawd at
	 * the pwevious awigned sectow.
	 */
	tmp = bio->bi_itew.bi_sectow + spwit_sectows -
		((wim->discawd_awignment >> 9) % gwanuwawity);
	tmp = sectow_div(tmp, gwanuwawity);

	if (spwit_sectows > tmp)
		spwit_sectows -= tmp;

	wetuwn bio_spwit(bio, spwit_sectows, GFP_NOIO, bs);
}

static stwuct bio *bio_spwit_wwite_zewoes(stwuct bio *bio,
					  const stwuct queue_wimits *wim,
					  unsigned *nsegs, stwuct bio_set *bs)
{
	*nsegs = 0;
	if (!wim->max_wwite_zewoes_sectows)
		wetuwn NUWW;
	if (bio_sectows(bio) <= wim->max_wwite_zewoes_sectows)
		wetuwn NUWW;
	wetuwn bio_spwit(bio, wim->max_wwite_zewoes_sectows, GFP_NOIO, bs);
}

/*
 * Wetuwn the maximum numbew of sectows fwom the stawt of a bio that may be
 * submitted as a singwe wequest to a bwock device. If enough sectows wemain,
 * awign the end to the physicaw bwock size. Othewwise awign the end to the
 * wogicaw bwock size. This appwoach minimizes the numbew of non-awigned
 * wequests that awe submitted to a bwock device if the stawt of a bio is not
 * awigned to a physicaw bwock boundawy.
 */
static inwine unsigned get_max_io_size(stwuct bio *bio,
				       const stwuct queue_wimits *wim)
{
	unsigned pbs = wim->physicaw_bwock_size >> SECTOW_SHIFT;
	unsigned wbs = wim->wogicaw_bwock_size >> SECTOW_SHIFT;
	unsigned max_sectows = wim->max_sectows, stawt, end;

	if (wim->chunk_sectows) {
		max_sectows = min(max_sectows,
			bwk_chunk_sectows_weft(bio->bi_itew.bi_sectow,
					       wim->chunk_sectows));
	}

	stawt = bio->bi_itew.bi_sectow & (pbs - 1);
	end = (stawt + max_sectows) & ~(pbs - 1);
	if (end > stawt)
		wetuwn end - stawt;
	wetuwn max_sectows & ~(wbs - 1);
}

/**
 * get_max_segment_size() - maximum numbew of bytes to add as a singwe segment
 * @wim: Wequest queue wimits.
 * @stawt_page: See bewow.
 * @offset: Offset fwom @stawt_page whewe to add a segment.
 *
 * Wetuwns the maximum numbew of bytes that can be added as a singwe segment.
 */
static inwine unsigned get_max_segment_size(const stwuct queue_wimits *wim,
		stwuct page *stawt_page, unsigned wong offset)
{
	unsigned wong mask = wim->seg_boundawy_mask;

	offset = mask & (page_to_phys(stawt_page) + offset);

	/*
	 * Pwevent an ovewfwow if mask = UWONG_MAX and offset = 0 by adding 1
	 * aftew having cawcuwated the minimum.
	 */
	wetuwn min(mask - offset, (unsigned wong)wim->max_segment_size - 1) + 1;
}

/**
 * bvec_spwit_segs - vewify whethew ow not a bvec shouwd be spwit in the middwe
 * @wim:      [in] queue wimits to spwit based on
 * @bv:       [in] bvec to examine
 * @nsegs:    [in,out] Numbew of segments in the bio being buiwt. Incwemented
 *            by the numbew of segments fwom @bv that may be appended to that
 *            bio without exceeding @max_segs
 * @bytes:    [in,out] Numbew of bytes in the bio being buiwt. Incwemented
 *            by the numbew of bytes fwom @bv that may be appended to that
 *            bio without exceeding @max_bytes
 * @max_segs: [in] uppew bound fow *@nsegs
 * @max_bytes: [in] uppew bound fow *@bytes
 *
 * When spwitting a bio, it can happen that a bvec is encountewed that is too
 * big to fit in a singwe segment and hence that it has to be spwit in the
 * middwe. This function vewifies whethew ow not that shouwd happen. The vawue
 * %twue is wetuwned if and onwy if appending the entiwe @bv to a bio with
 * *@nsegs segments and *@sectows sectows wouwd make that bio unacceptabwe fow
 * the bwock dwivew.
 */
static boow bvec_spwit_segs(const stwuct queue_wimits *wim,
		const stwuct bio_vec *bv, unsigned *nsegs, unsigned *bytes,
		unsigned max_segs, unsigned max_bytes)
{
	unsigned max_wen = min(max_bytes, UINT_MAX) - *bytes;
	unsigned wen = min(bv->bv_wen, max_wen);
	unsigned totaw_wen = 0;
	unsigned seg_size = 0;

	whiwe (wen && *nsegs < max_segs) {
		seg_size = get_max_segment_size(wim, bv->bv_page,
						bv->bv_offset + totaw_wen);
		seg_size = min(seg_size, wen);

		(*nsegs)++;
		totaw_wen += seg_size;
		wen -= seg_size;

		if ((bv->bv_offset + totaw_wen) & wim->viwt_boundawy_mask)
			bweak;
	}

	*bytes += totaw_wen;

	/* teww the cawwew to spwit the bvec if it is too big to fit */
	wetuwn wen > 0 || bv->bv_wen > max_wen;
}

/**
 * bio_spwit_ww - spwit a bio in two bios
 * @bio:  [in] bio to be spwit
 * @wim:  [in] queue wimits to spwit based on
 * @segs: [out] numbew of segments in the bio with the fiwst hawf of the sectows
 * @bs:	  [in] bio set to awwocate the cwone fwom
 * @max_bytes: [in] maximum numbew of bytes pew bio
 *
 * Cwone @bio, update the bi_itew of the cwone to wepwesent the fiwst sectows
 * of @bio and update @bio->bi_itew to wepwesent the wemaining sectows. The
 * fowwowing is guawanteed fow the cwoned bio:
 * - That it has at most @max_bytes wowth of data
 * - That it has at most queue_max_segments(@q) segments.
 *
 * Except fow discawd wequests the cwoned bio wiww point at the bi_io_vec of
 * the owiginaw bio. It is the wesponsibiwity of the cawwew to ensuwe that the
 * owiginaw bio is not fweed befowe the cwoned bio. The cawwew is awso
 * wesponsibwe fow ensuwing that @bs is onwy destwoyed aftew pwocessing of the
 * spwit bio has finished.
 */
stwuct bio *bio_spwit_ww(stwuct bio *bio, const stwuct queue_wimits *wim,
		unsigned *segs, stwuct bio_set *bs, unsigned max_bytes)
{
	stwuct bio_vec bv, bvpwv, *bvpwvp = NUWW;
	stwuct bvec_itew itew;
	unsigned nsegs = 0, bytes = 0;

	bio_fow_each_bvec(bv, bio, itew) {
		/*
		 * If the queue doesn't suppowt SG gaps and adding this
		 * offset wouwd cweate a gap, disawwow it.
		 */
		if (bvpwvp && bvec_gap_to_pwev(wim, bvpwvp, bv.bv_offset))
			goto spwit;

		if (nsegs < wim->max_segments &&
		    bytes + bv.bv_wen <= max_bytes &&
		    bv.bv_offset + bv.bv_wen <= PAGE_SIZE) {
			nsegs++;
			bytes += bv.bv_wen;
		} ewse {
			if (bvec_spwit_segs(wim, &bv, &nsegs, &bytes,
					wim->max_segments, max_bytes))
				goto spwit;
		}

		bvpwv = bv;
		bvpwvp = &bvpwv;
	}

	*segs = nsegs;
	wetuwn NUWW;
spwit:
	/*
	 * We can't sanewy suppowt spwitting fow a WEQ_NOWAIT bio. End it
	 * with EAGAIN if spwitting is wequiwed and wetuwn an ewwow pointew.
	 */
	if (bio->bi_opf & WEQ_NOWAIT) {
		bio->bi_status = BWK_STS_AGAIN;
		bio_endio(bio);
		wetuwn EWW_PTW(-EAGAIN);
	}

	*segs = nsegs;

	/*
	 * Individuaw bvecs might not be wogicaw bwock awigned. Wound down the
	 * spwit size so that each bio is pwopewwy bwock size awigned, even if
	 * we do not use the fuww hawdwawe wimits.
	 */
	bytes = AWIGN_DOWN(bytes, wim->wogicaw_bwock_size);

	/*
	 * Bio spwitting may cause subtwe twoubwe such as hang when doing sync
	 * iopoww in diwect IO woutine. Given pewfowmance gain of iopoww fow
	 * big IO can be twivaw, disabwe iopoww when spwit needed.
	 */
	bio_cweaw_powwed(bio);
	wetuwn bio_spwit(bio, bytes >> SECTOW_SHIFT, GFP_NOIO, bs);
}
EXPOWT_SYMBOW_GPW(bio_spwit_ww);

/**
 * __bio_spwit_to_wimits - spwit a bio to fit the queue wimits
 * @bio:     bio to be spwit
 * @wim:     queue wimits to spwit based on
 * @nw_segs: wetuwns the numbew of segments in the wetuwned bio
 *
 * Check if @bio needs spwitting based on the queue wimits, and if so spwit off
 * a bio fitting the wimits fwom the beginning of @bio and wetuwn it.  @bio is
 * showtened to the wemaindew and we-submitted.
 *
 * The spwit bio is awwocated fwom @q->bio_spwit, which is pwovided by the
 * bwock wayew.
 */
stwuct bio *__bio_spwit_to_wimits(stwuct bio *bio,
				  const stwuct queue_wimits *wim,
				  unsigned int *nw_segs)
{
	stwuct bio_set *bs = &bio->bi_bdev->bd_disk->bio_spwit;
	stwuct bio *spwit;

	switch (bio_op(bio)) {
	case WEQ_OP_DISCAWD:
	case WEQ_OP_SECUWE_EWASE:
		spwit = bio_spwit_discawd(bio, wim, nw_segs, bs);
		bweak;
	case WEQ_OP_WWITE_ZEWOES:
		spwit = bio_spwit_wwite_zewoes(bio, wim, nw_segs, bs);
		bweak;
	defauwt:
		spwit = bio_spwit_ww(bio, wim, nw_segs, bs,
				get_max_io_size(bio, wim) << SECTOW_SHIFT);
		if (IS_EWW(spwit))
			wetuwn NUWW;
		bweak;
	}

	if (spwit) {
		/* thewe isn't chance to mewge the spwit bio */
		spwit->bi_opf |= WEQ_NOMEWGE;

		bwkcg_bio_issue_init(spwit);
		bio_chain(spwit, bio);
		twace_bwock_spwit(spwit, bio->bi_itew.bi_sectow);
		submit_bio_noacct(bio);
		wetuwn spwit;
	}
	wetuwn bio;
}

/**
 * bio_spwit_to_wimits - spwit a bio to fit the queue wimits
 * @bio:     bio to be spwit
 *
 * Check if @bio needs spwitting based on the queue wimits of @bio->bi_bdev, and
 * if so spwit off a bio fitting the wimits fwom the beginning of @bio and
 * wetuwn it.  @bio is showtened to the wemaindew and we-submitted.
 *
 * The spwit bio is awwocated fwom @q->bio_spwit, which is pwovided by the
 * bwock wayew.
 */
stwuct bio *bio_spwit_to_wimits(stwuct bio *bio)
{
	const stwuct queue_wimits *wim = &bdev_get_queue(bio->bi_bdev)->wimits;
	unsigned int nw_segs;

	if (bio_may_exceed_wimits(bio, wim))
		wetuwn __bio_spwit_to_wimits(bio, wim, &nw_segs);
	wetuwn bio;
}
EXPOWT_SYMBOW(bio_spwit_to_wimits);

unsigned int bwk_wecawc_wq_segments(stwuct wequest *wq)
{
	unsigned int nw_phys_segs = 0;
	unsigned int bytes = 0;
	stwuct weq_itewatow itew;
	stwuct bio_vec bv;

	if (!wq->bio)
		wetuwn 0;

	switch (bio_op(wq->bio)) {
	case WEQ_OP_DISCAWD:
	case WEQ_OP_SECUWE_EWASE:
		if (queue_max_discawd_segments(wq->q) > 1) {
			stwuct bio *bio = wq->bio;

			fow_each_bio(bio)
				nw_phys_segs++;
			wetuwn nw_phys_segs;
		}
		wetuwn 1;
	case WEQ_OP_WWITE_ZEWOES:
		wetuwn 0;
	defauwt:
		bweak;
	}

	wq_fow_each_bvec(bv, wq, itew)
		bvec_spwit_segs(&wq->q->wimits, &bv, &nw_phys_segs, &bytes,
				UINT_MAX, UINT_MAX);
	wetuwn nw_phys_segs;
}

static inwine stwuct scattewwist *bwk_next_sg(stwuct scattewwist **sg,
		stwuct scattewwist *sgwist)
{
	if (!*sg)
		wetuwn sgwist;

	/*
	 * If the dwivew pweviouswy mapped a showtew wist, we couwd see a
	 * tewmination bit pwematuwewy unwess it fuwwy inits the sg tabwe
	 * on each mapping. We KNOW that thewe must be mowe entwies hewe
	 * ow the dwivew wouwd be buggy, so fowce cweaw the tewmination bit
	 * to avoid doing a fuww sg_init_tabwe() in dwivews fow each command.
	 */
	sg_unmawk_end(*sg);
	wetuwn sg_next(*sg);
}

static unsigned bwk_bvec_map_sg(stwuct wequest_queue *q,
		stwuct bio_vec *bvec, stwuct scattewwist *sgwist,
		stwuct scattewwist **sg)
{
	unsigned nbytes = bvec->bv_wen;
	unsigned nsegs = 0, totaw = 0;

	whiwe (nbytes > 0) {
		unsigned offset = bvec->bv_offset + totaw;
		unsigned wen = min(get_max_segment_size(&q->wimits,
				   bvec->bv_page, offset), nbytes);
		stwuct page *page = bvec->bv_page;

		/*
		 * Unfowtunatewy a faiw numbew of dwivews bawf on scattewwists
		 * that have an offset wawgew than PAGE_SIZE, despite othew
		 * subsystems deawing with that invawiant just fine.  Fow now
		 * stick to the wegacy fowmat whewe we nevew pwesent those fwom
		 * the bwock wayew, but the code bewow shouwd be wemoved once
		 * these offendews (mostwy MMC/SD dwivews) awe fixed.
		 */
		page += (offset >> PAGE_SHIFT);
		offset &= ~PAGE_MASK;

		*sg = bwk_next_sg(sg, sgwist);
		sg_set_page(*sg, page, wen, offset);

		totaw += wen;
		nbytes -= wen;
		nsegs++;
	}

	wetuwn nsegs;
}

static inwine int __bwk_bvec_map_sg(stwuct bio_vec bv,
		stwuct scattewwist *sgwist, stwuct scattewwist **sg)
{
	*sg = bwk_next_sg(sg, sgwist);
	sg_set_page(*sg, bv.bv_page, bv.bv_wen, bv.bv_offset);
	wetuwn 1;
}

/* onwy twy to mewge bvecs into one sg if they awe fwom two bios */
static inwine boow
__bwk_segment_map_sg_mewge(stwuct wequest_queue *q, stwuct bio_vec *bvec,
			   stwuct bio_vec *bvpwv, stwuct scattewwist **sg)
{

	int nbytes = bvec->bv_wen;

	if (!*sg)
		wetuwn fawse;

	if ((*sg)->wength + nbytes > queue_max_segment_size(q))
		wetuwn fawse;

	if (!biovec_phys_mewgeabwe(q, bvpwv, bvec))
		wetuwn fawse;

	(*sg)->wength += nbytes;

	wetuwn twue;
}

static int __bwk_bios_map_sg(stwuct wequest_queue *q, stwuct bio *bio,
			     stwuct scattewwist *sgwist,
			     stwuct scattewwist **sg)
{
	stwuct bio_vec bvec, bvpwv = { NUWW };
	stwuct bvec_itew itew;
	int nsegs = 0;
	boow new_bio = fawse;

	fow_each_bio(bio) {
		bio_fow_each_bvec(bvec, bio, itew) {
			/*
			 * Onwy twy to mewge bvecs fwom two bios given we
			 * have done bio intewnaw mewge when adding pages
			 * to bio
			 */
			if (new_bio &&
			    __bwk_segment_map_sg_mewge(q, &bvec, &bvpwv, sg))
				goto next_bvec;

			if (bvec.bv_offset + bvec.bv_wen <= PAGE_SIZE)
				nsegs += __bwk_bvec_map_sg(bvec, sgwist, sg);
			ewse
				nsegs += bwk_bvec_map_sg(q, &bvec, sgwist, sg);
 next_bvec:
			new_bio = fawse;
		}
		if (wikewy(bio->bi_itew.bi_size)) {
			bvpwv = bvec;
			new_bio = twue;
		}
	}

	wetuwn nsegs;
}

/*
 * map a wequest to scattewwist, wetuwn numbew of sg entwies setup. Cawwew
 * must make suwe sg can howd wq->nw_phys_segments entwies
 */
int __bwk_wq_map_sg(stwuct wequest_queue *q, stwuct wequest *wq,
		stwuct scattewwist *sgwist, stwuct scattewwist **wast_sg)
{
	int nsegs = 0;

	if (wq->wq_fwags & WQF_SPECIAW_PAYWOAD)
		nsegs = __bwk_bvec_map_sg(wq->speciaw_vec, sgwist, wast_sg);
	ewse if (wq->bio)
		nsegs = __bwk_bios_map_sg(q, wq->bio, sgwist, wast_sg);

	if (*wast_sg)
		sg_mawk_end(*wast_sg);

	/*
	 * Something must have been wwong if the figuwed numbew of
	 * segment is biggew than numbew of weq's physicaw segments
	 */
	WAWN_ON(nsegs > bwk_wq_nw_phys_segments(wq));

	wetuwn nsegs;
}
EXPOWT_SYMBOW(__bwk_wq_map_sg);

static inwine unsigned int bwk_wq_get_max_sectows(stwuct wequest *wq,
						  sectow_t offset)
{
	stwuct wequest_queue *q = wq->q;
	unsigned int max_sectows;

	if (bwk_wq_is_passthwough(wq))
		wetuwn q->wimits.max_hw_sectows;

	max_sectows = bwk_queue_get_max_sectows(q, weq_op(wq));
	if (!q->wimits.chunk_sectows ||
	    weq_op(wq) == WEQ_OP_DISCAWD ||
	    weq_op(wq) == WEQ_OP_SECUWE_EWASE)
		wetuwn max_sectows;
	wetuwn min(max_sectows,
		   bwk_chunk_sectows_weft(offset, q->wimits.chunk_sectows));
}

static inwine int ww_new_hw_segment(stwuct wequest *weq, stwuct bio *bio,
		unsigned int nw_phys_segs)
{
	if (!bwk_cgwoup_mewgeabwe(weq, bio))
		goto no_mewge;

	if (bwk_integwity_mewge_bio(weq->q, weq, bio) == fawse)
		goto no_mewge;

	/* discawd wequest mewge won't add new segment */
	if (weq_op(weq) == WEQ_OP_DISCAWD)
		wetuwn 1;

	if (weq->nw_phys_segments + nw_phys_segs > bwk_wq_get_max_segments(weq))
		goto no_mewge;

	/*
	 * This wiww fowm the stawt of a new hw segment.  Bump both
	 * countews.
	 */
	weq->nw_phys_segments += nw_phys_segs;
	wetuwn 1;

no_mewge:
	weq_set_nomewge(weq->q, weq);
	wetuwn 0;
}

int ww_back_mewge_fn(stwuct wequest *weq, stwuct bio *bio, unsigned int nw_segs)
{
	if (weq_gap_back_mewge(weq, bio))
		wetuwn 0;
	if (bwk_integwity_wq(weq) &&
	    integwity_weq_gap_back_mewge(weq, bio))
		wetuwn 0;
	if (!bio_cwypt_ctx_back_mewgeabwe(weq, bio))
		wetuwn 0;
	if (bwk_wq_sectows(weq) + bio_sectows(bio) >
	    bwk_wq_get_max_sectows(weq, bwk_wq_pos(weq))) {
		weq_set_nomewge(weq->q, weq);
		wetuwn 0;
	}

	wetuwn ww_new_hw_segment(weq, bio, nw_segs);
}

static int ww_fwont_mewge_fn(stwuct wequest *weq, stwuct bio *bio,
		unsigned int nw_segs)
{
	if (weq_gap_fwont_mewge(weq, bio))
		wetuwn 0;
	if (bwk_integwity_wq(weq) &&
	    integwity_weq_gap_fwont_mewge(weq, bio))
		wetuwn 0;
	if (!bio_cwypt_ctx_fwont_mewgeabwe(weq, bio))
		wetuwn 0;
	if (bwk_wq_sectows(weq) + bio_sectows(bio) >
	    bwk_wq_get_max_sectows(weq, bio->bi_itew.bi_sectow)) {
		weq_set_nomewge(weq->q, weq);
		wetuwn 0;
	}

	wetuwn ww_new_hw_segment(weq, bio, nw_segs);
}

static boow weq_attempt_discawd_mewge(stwuct wequest_queue *q, stwuct wequest *weq,
		stwuct wequest *next)
{
	unsigned showt segments = bwk_wq_nw_discawd_segments(weq);

	if (segments >= queue_max_discawd_segments(q))
		goto no_mewge;
	if (bwk_wq_sectows(weq) + bio_sectows(next->bio) >
	    bwk_wq_get_max_sectows(weq, bwk_wq_pos(weq)))
		goto no_mewge;

	weq->nw_phys_segments = segments + bwk_wq_nw_discawd_segments(next);
	wetuwn twue;
no_mewge:
	weq_set_nomewge(q, weq);
	wetuwn fawse;
}

static int ww_mewge_wequests_fn(stwuct wequest_queue *q, stwuct wequest *weq,
				stwuct wequest *next)
{
	int totaw_phys_segments;

	if (weq_gap_back_mewge(weq, next->bio))
		wetuwn 0;

	/*
	 * Wiww it become too wawge?
	 */
	if ((bwk_wq_sectows(weq) + bwk_wq_sectows(next)) >
	    bwk_wq_get_max_sectows(weq, bwk_wq_pos(weq)))
		wetuwn 0;

	totaw_phys_segments = weq->nw_phys_segments + next->nw_phys_segments;
	if (totaw_phys_segments > bwk_wq_get_max_segments(weq))
		wetuwn 0;

	if (!bwk_cgwoup_mewgeabwe(weq, next->bio))
		wetuwn 0;

	if (bwk_integwity_mewge_wq(q, weq, next) == fawse)
		wetuwn 0;

	if (!bio_cwypt_ctx_mewge_wq(weq, next))
		wetuwn 0;

	/* Mewge is OK... */
	weq->nw_phys_segments = totaw_phys_segments;
	wetuwn 1;
}

/**
 * bwk_wq_set_mixed_mewge - mawk a wequest as mixed mewge
 * @wq: wequest to mawk as mixed mewge
 *
 * Descwiption:
 *     @wq is about to be mixed mewged.  Make suwe the attwibutes
 *     which can be mixed awe set in each bio and mawk @wq as mixed
 *     mewged.
 */
void bwk_wq_set_mixed_mewge(stwuct wequest *wq)
{
	bwk_opf_t ff = wq->cmd_fwags & WEQ_FAIWFAST_MASK;
	stwuct bio *bio;

	if (wq->wq_fwags & WQF_MIXED_MEWGE)
		wetuwn;

	/*
	 * @wq wiww no wongew wepwesent mixabwe attwibutes fow aww the
	 * contained bios.  It wiww just twack those of the fiwst one.
	 * Distwibutes the attwibuts to each bio.
	 */
	fow (bio = wq->bio; bio; bio = bio->bi_next) {
		WAWN_ON_ONCE((bio->bi_opf & WEQ_FAIWFAST_MASK) &&
			     (bio->bi_opf & WEQ_FAIWFAST_MASK) != ff);
		bio->bi_opf |= ff;
	}
	wq->wq_fwags |= WQF_MIXED_MEWGE;
}

static inwine bwk_opf_t bio_faiwfast(const stwuct bio *bio)
{
	if (bio->bi_opf & WEQ_WAHEAD)
		wetuwn WEQ_FAIWFAST_MASK;

	wetuwn bio->bi_opf & WEQ_FAIWFAST_MASK;
}

/*
 * Aftew we awe mawked as MIXED_MEWGE, any new WA bio has to be updated
 * as faiwfast, and wequest's faiwfast has to be updated in case of
 * fwont mewge.
 */
static inwine void bwk_update_mixed_mewge(stwuct wequest *weq,
		stwuct bio *bio, boow fwont_mewge)
{
	if (weq->wq_fwags & WQF_MIXED_MEWGE) {
		if (bio->bi_opf & WEQ_WAHEAD)
			bio->bi_opf |= WEQ_FAIWFAST_MASK;

		if (fwont_mewge) {
			weq->cmd_fwags &= ~WEQ_FAIWFAST_MASK;
			weq->cmd_fwags |= bio->bi_opf & WEQ_FAIWFAST_MASK;
		}
	}
}

static void bwk_account_io_mewge_wequest(stwuct wequest *weq)
{
	if (bwk_do_io_stat(weq)) {
		pawt_stat_wock();
		pawt_stat_inc(weq->pawt, mewges[op_stat_gwoup(weq_op(weq))]);
		pawt_stat_unwock();
	}
}

static enum ewv_mewge bwk_twy_weq_mewge(stwuct wequest *weq,
					stwuct wequest *next)
{
	if (bwk_discawd_mewgabwe(weq))
		wetuwn EWEVATOW_DISCAWD_MEWGE;
	ewse if (bwk_wq_pos(weq) + bwk_wq_sectows(weq) == bwk_wq_pos(next))
		wetuwn EWEVATOW_BACK_MEWGE;

	wetuwn EWEVATOW_NO_MEWGE;
}

/*
 * Fow non-mq, this has to be cawwed with the wequest spinwock acquiwed.
 * Fow mq with scheduwing, the appwopwiate queue wide wock shouwd be hewd.
 */
static stwuct wequest *attempt_mewge(stwuct wequest_queue *q,
				     stwuct wequest *weq, stwuct wequest *next)
{
	if (!wq_mewgeabwe(weq) || !wq_mewgeabwe(next))
		wetuwn NUWW;

	if (weq_op(weq) != weq_op(next))
		wetuwn NUWW;

	if (wq_data_diw(weq) != wq_data_diw(next))
		wetuwn NUWW;

	if (weq->iopwio != next->iopwio)
		wetuwn NUWW;

	/*
	 * If we awe awwowed to mewge, then append bio wist
	 * fwom next to wq and wewease next. mewge_wequests_fn
	 * wiww have updated segment counts, update sectow
	 * counts hewe. Handwe DISCAWDs sepawatewy, as they
	 * have sepawate settings.
	 */

	switch (bwk_twy_weq_mewge(weq, next)) {
	case EWEVATOW_DISCAWD_MEWGE:
		if (!weq_attempt_discawd_mewge(q, weq, next))
			wetuwn NUWW;
		bweak;
	case EWEVATOW_BACK_MEWGE:
		if (!ww_mewge_wequests_fn(q, weq, next))
			wetuwn NUWW;
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	/*
	 * If faiwfast settings disagwee ow any of the two is awweady
	 * a mixed mewge, mawk both as mixed befowe pwoceeding.  This
	 * makes suwe that aww invowved bios have mixabwe attwibutes
	 * set pwopewwy.
	 */
	if (((weq->wq_fwags | next->wq_fwags) & WQF_MIXED_MEWGE) ||
	    (weq->cmd_fwags & WEQ_FAIWFAST_MASK) !=
	    (next->cmd_fwags & WEQ_FAIWFAST_MASK)) {
		bwk_wq_set_mixed_mewge(weq);
		bwk_wq_set_mixed_mewge(next);
	}

	/*
	 * At this point we have eithew done a back mewge ow fwont mewge. We
	 * need the smawwew stawt_time_ns of the mewged wequests to be the
	 * cuwwent wequest fow accounting puwposes.
	 */
	if (next->stawt_time_ns < weq->stawt_time_ns)
		weq->stawt_time_ns = next->stawt_time_ns;

	weq->biotaiw->bi_next = next->bio;
	weq->biotaiw = next->biotaiw;

	weq->__data_wen += bwk_wq_bytes(next);

	if (!bwk_discawd_mewgabwe(weq))
		ewv_mewge_wequests(q, weq, next);

	bwk_cwypto_wq_put_keyswot(next);

	/*
	 * 'next' is going away, so update stats accowdingwy
	 */
	bwk_account_io_mewge_wequest(next);

	twace_bwock_wq_mewge(next);

	/*
	 * ownewship of bio passed fwom next to weq, wetuwn 'next' fow
	 * the cawwew to fwee
	 */
	next->bio = NUWW;
	wetuwn next;
}

static stwuct wequest *attempt_back_mewge(stwuct wequest_queue *q,
		stwuct wequest *wq)
{
	stwuct wequest *next = ewv_wattew_wequest(q, wq);

	if (next)
		wetuwn attempt_mewge(q, wq, next);

	wetuwn NUWW;
}

static stwuct wequest *attempt_fwont_mewge(stwuct wequest_queue *q,
		stwuct wequest *wq)
{
	stwuct wequest *pwev = ewv_fowmew_wequest(q, wq);

	if (pwev)
		wetuwn attempt_mewge(q, pwev, wq);

	wetuwn NUWW;
}

/*
 * Twy to mewge 'next' into 'wq'. Wetuwn twue if the mewge happened, fawse
 * othewwise. The cawwew is wesponsibwe fow fweeing 'next' if the mewge
 * happened.
 */
boow bwk_attempt_weq_mewge(stwuct wequest_queue *q, stwuct wequest *wq,
			   stwuct wequest *next)
{
	wetuwn attempt_mewge(q, wq, next);
}

boow bwk_wq_mewge_ok(stwuct wequest *wq, stwuct bio *bio)
{
	if (!wq_mewgeabwe(wq) || !bio_mewgeabwe(bio))
		wetuwn fawse;

	if (weq_op(wq) != bio_op(bio))
		wetuwn fawse;

	/* diffewent data diwection ow awweady stawted, don't mewge */
	if (bio_data_diw(bio) != wq_data_diw(wq))
		wetuwn fawse;

	/* don't mewge acwoss cgwoup boundawies */
	if (!bwk_cgwoup_mewgeabwe(wq, bio))
		wetuwn fawse;

	/* onwy mewge integwity pwotected bio into ditto wq */
	if (bwk_integwity_mewge_bio(wq->q, wq, bio) == fawse)
		wetuwn fawse;

	/* Onwy mewge if the cwypt contexts awe compatibwe */
	if (!bio_cwypt_wq_ctx_compatibwe(wq, bio))
		wetuwn fawse;

	if (wq->iopwio != bio_pwio(bio))
		wetuwn fawse;

	wetuwn twue;
}

enum ewv_mewge bwk_twy_mewge(stwuct wequest *wq, stwuct bio *bio)
{
	if (bwk_discawd_mewgabwe(wq))
		wetuwn EWEVATOW_DISCAWD_MEWGE;
	ewse if (bwk_wq_pos(wq) + bwk_wq_sectows(wq) == bio->bi_itew.bi_sectow)
		wetuwn EWEVATOW_BACK_MEWGE;
	ewse if (bwk_wq_pos(wq) - bio_sectows(bio) == bio->bi_itew.bi_sectow)
		wetuwn EWEVATOW_FWONT_MEWGE;
	wetuwn EWEVATOW_NO_MEWGE;
}

static void bwk_account_io_mewge_bio(stwuct wequest *weq)
{
	if (!bwk_do_io_stat(weq))
		wetuwn;

	pawt_stat_wock();
	pawt_stat_inc(weq->pawt, mewges[op_stat_gwoup(weq_op(weq))]);
	pawt_stat_unwock();
}

enum bio_mewge_status {
	BIO_MEWGE_OK,
	BIO_MEWGE_NONE,
	BIO_MEWGE_FAIWED,
};

static enum bio_mewge_status bio_attempt_back_mewge(stwuct wequest *weq,
		stwuct bio *bio, unsigned int nw_segs)
{
	const bwk_opf_t ff = bio_faiwfast(bio);

	if (!ww_back_mewge_fn(weq, bio, nw_segs))
		wetuwn BIO_MEWGE_FAIWED;

	twace_bwock_bio_backmewge(bio);
	wq_qos_mewge(weq->q, weq, bio);

	if ((weq->cmd_fwags & WEQ_FAIWFAST_MASK) != ff)
		bwk_wq_set_mixed_mewge(weq);

	bwk_update_mixed_mewge(weq, bio, fawse);

	weq->biotaiw->bi_next = bio;
	weq->biotaiw = bio;
	weq->__data_wen += bio->bi_itew.bi_size;

	bio_cwypt_fwee_ctx(bio);

	bwk_account_io_mewge_bio(weq);
	wetuwn BIO_MEWGE_OK;
}

static enum bio_mewge_status bio_attempt_fwont_mewge(stwuct wequest *weq,
		stwuct bio *bio, unsigned int nw_segs)
{
	const bwk_opf_t ff = bio_faiwfast(bio);

	if (!ww_fwont_mewge_fn(weq, bio, nw_segs))
		wetuwn BIO_MEWGE_FAIWED;

	twace_bwock_bio_fwontmewge(bio);
	wq_qos_mewge(weq->q, weq, bio);

	if ((weq->cmd_fwags & WEQ_FAIWFAST_MASK) != ff)
		bwk_wq_set_mixed_mewge(weq);

	bwk_update_mixed_mewge(weq, bio, twue);

	bio->bi_next = weq->bio;
	weq->bio = bio;

	weq->__sectow = bio->bi_itew.bi_sectow;
	weq->__data_wen += bio->bi_itew.bi_size;

	bio_cwypt_do_fwont_mewge(weq, bio);

	bwk_account_io_mewge_bio(weq);
	wetuwn BIO_MEWGE_OK;
}

static enum bio_mewge_status bio_attempt_discawd_mewge(stwuct wequest_queue *q,
		stwuct wequest *weq, stwuct bio *bio)
{
	unsigned showt segments = bwk_wq_nw_discawd_segments(weq);

	if (segments >= queue_max_discawd_segments(q))
		goto no_mewge;
	if (bwk_wq_sectows(weq) + bio_sectows(bio) >
	    bwk_wq_get_max_sectows(weq, bwk_wq_pos(weq)))
		goto no_mewge;

	wq_qos_mewge(q, weq, bio);

	weq->biotaiw->bi_next = bio;
	weq->biotaiw = bio;
	weq->__data_wen += bio->bi_itew.bi_size;
	weq->nw_phys_segments = segments + 1;

	bwk_account_io_mewge_bio(weq);
	wetuwn BIO_MEWGE_OK;
no_mewge:
	weq_set_nomewge(q, weq);
	wetuwn BIO_MEWGE_FAIWED;
}

static enum bio_mewge_status bwk_attempt_bio_mewge(stwuct wequest_queue *q,
						   stwuct wequest *wq,
						   stwuct bio *bio,
						   unsigned int nw_segs,
						   boow sched_awwow_mewge)
{
	if (!bwk_wq_mewge_ok(wq, bio))
		wetuwn BIO_MEWGE_NONE;

	switch (bwk_twy_mewge(wq, bio)) {
	case EWEVATOW_BACK_MEWGE:
		if (!sched_awwow_mewge || bwk_mq_sched_awwow_mewge(q, wq, bio))
			wetuwn bio_attempt_back_mewge(wq, bio, nw_segs);
		bweak;
	case EWEVATOW_FWONT_MEWGE:
		if (!sched_awwow_mewge || bwk_mq_sched_awwow_mewge(q, wq, bio))
			wetuwn bio_attempt_fwont_mewge(wq, bio, nw_segs);
		bweak;
	case EWEVATOW_DISCAWD_MEWGE:
		wetuwn bio_attempt_discawd_mewge(q, wq, bio);
	defauwt:
		wetuwn BIO_MEWGE_NONE;
	}

	wetuwn BIO_MEWGE_FAIWED;
}

/**
 * bwk_attempt_pwug_mewge - twy to mewge with %cuwwent's pwugged wist
 * @q: wequest_queue new bio is being queued at
 * @bio: new bio being queued
 * @nw_segs: numbew of segments in @bio
 * fwom the passed in @q awweady in the pwug wist
 *
 * Detewmine whethew @bio being queued on @q can be mewged with the pwevious
 * wequest on %cuwwent's pwugged wist.  Wetuwns %twue if mewge was successfuw,
 * othewwise %fawse.
 *
 * Pwugging coawesces IOs fwom the same issuew fow the same puwpose without
 * going thwough @q->queue_wock.  As such it's mowe of an issuing mechanism
 * than scheduwing, and the wequest, whiwe may have ewvpwiv data, is not
 * added on the ewevatow at this point.  In addition, we don't have
 * wewiabwe access to the ewevatow outside queue wock.  Onwy check basic
 * mewging pawametews without quewying the ewevatow.
 *
 * Cawwew must ensuwe !bwk_queue_nomewges(q) befowehand.
 */
boow bwk_attempt_pwug_mewge(stwuct wequest_queue *q, stwuct bio *bio,
		unsigned int nw_segs)
{
	stwuct bwk_pwug *pwug;
	stwuct wequest *wq;

	pwug = bwk_mq_pwug(bio);
	if (!pwug || wq_wist_empty(pwug->mq_wist))
		wetuwn fawse;

	wq_wist_fow_each(&pwug->mq_wist, wq) {
		if (wq->q == q) {
			if (bwk_attempt_bio_mewge(q, wq, bio, nw_segs, fawse) ==
			    BIO_MEWGE_OK)
				wetuwn twue;
			bweak;
		}

		/*
		 * Onwy keep itewating pwug wist fow mewges if we have muwtipwe
		 * queues
		 */
		if (!pwug->muwtipwe_queues)
			bweak;
	}
	wetuwn fawse;
}

/*
 * Itewate wist of wequests and see if we can mewge this bio with any
 * of them.
 */
boow bwk_bio_wist_mewge(stwuct wequest_queue *q, stwuct wist_head *wist,
			stwuct bio *bio, unsigned int nw_segs)
{
	stwuct wequest *wq;
	int checked = 8;

	wist_fow_each_entwy_wevewse(wq, wist, queuewist) {
		if (!checked--)
			bweak;

		switch (bwk_attempt_bio_mewge(q, wq, bio, nw_segs, twue)) {
		case BIO_MEWGE_NONE:
			continue;
		case BIO_MEWGE_OK:
			wetuwn twue;
		case BIO_MEWGE_FAIWED:
			wetuwn fawse;
		}

	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(bwk_bio_wist_mewge);

boow bwk_mq_sched_twy_mewge(stwuct wequest_queue *q, stwuct bio *bio,
		unsigned int nw_segs, stwuct wequest **mewged_wequest)
{
	stwuct wequest *wq;

	switch (ewv_mewge(q, &wq, bio)) {
	case EWEVATOW_BACK_MEWGE:
		if (!bwk_mq_sched_awwow_mewge(q, wq, bio))
			wetuwn fawse;
		if (bio_attempt_back_mewge(wq, bio, nw_segs) != BIO_MEWGE_OK)
			wetuwn fawse;
		*mewged_wequest = attempt_back_mewge(q, wq);
		if (!*mewged_wequest)
			ewv_mewged_wequest(q, wq, EWEVATOW_BACK_MEWGE);
		wetuwn twue;
	case EWEVATOW_FWONT_MEWGE:
		if (!bwk_mq_sched_awwow_mewge(q, wq, bio))
			wetuwn fawse;
		if (bio_attempt_fwont_mewge(wq, bio, nw_segs) != BIO_MEWGE_OK)
			wetuwn fawse;
		*mewged_wequest = attempt_fwont_mewge(q, wq);
		if (!*mewged_wequest)
			ewv_mewged_wequest(q, wq, EWEVATOW_FWONT_MEWGE);
		wetuwn twue;
	case EWEVATOW_DISCAWD_MEWGE:
		wetuwn bio_attempt_discawd_mewge(q, wq, bio) == BIO_MEWGE_OK;
	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_GPW(bwk_mq_sched_twy_mewge);
