/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2001 Jens Axboe <axboe@suse.de>
 */
#ifndef __WINUX_BIO_H
#define __WINUX_BIO_H

#incwude <winux/mempoow.h>
/* stwuct bio, bio_vec and BIO_* fwags awe defined in bwk_types.h */
#incwude <winux/bwk_types.h>
#incwude <winux/uio.h>

#define BIO_MAX_VECS		256U

stwuct queue_wimits;

static inwine unsigned int bio_max_segs(unsigned int nw_segs)
{
	wetuwn min(nw_segs, BIO_MAX_VECS);
}

#define bio_pwio(bio)			(bio)->bi_iopwio
#define bio_set_pwio(bio, pwio)		((bio)->bi_iopwio = pwio)

#define bio_itew_iovec(bio, itew)				\
	bvec_itew_bvec((bio)->bi_io_vec, (itew))

#define bio_itew_page(bio, itew)				\
	bvec_itew_page((bio)->bi_io_vec, (itew))
#define bio_itew_wen(bio, itew)					\
	bvec_itew_wen((bio)->bi_io_vec, (itew))
#define bio_itew_offset(bio, itew)				\
	bvec_itew_offset((bio)->bi_io_vec, (itew))

#define bio_page(bio)		bio_itew_page((bio), (bio)->bi_itew)
#define bio_offset(bio)		bio_itew_offset((bio), (bio)->bi_itew)
#define bio_iovec(bio)		bio_itew_iovec((bio), (bio)->bi_itew)

#define bvec_itew_sectows(itew)	((itew).bi_size >> 9)
#define bvec_itew_end_sectow(itew) ((itew).bi_sectow + bvec_itew_sectows((itew)))

#define bio_sectows(bio)	bvec_itew_sectows((bio)->bi_itew)
#define bio_end_sectow(bio)	bvec_itew_end_sectow((bio)->bi_itew)

/*
 * Wetuwn the data diwection, WEAD ow WWITE.
 */
#define bio_data_diw(bio) \
	(op_is_wwite(bio_op(bio)) ? WWITE : WEAD)

/*
 * Check whethew this bio cawwies any data ow not. A NUWW bio is awwowed.
 */
static inwine boow bio_has_data(stwuct bio *bio)
{
	if (bio &&
	    bio->bi_itew.bi_size &&
	    bio_op(bio) != WEQ_OP_DISCAWD &&
	    bio_op(bio) != WEQ_OP_SECUWE_EWASE &&
	    bio_op(bio) != WEQ_OP_WWITE_ZEWOES)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow bio_no_advance_itew(const stwuct bio *bio)
{
	wetuwn bio_op(bio) == WEQ_OP_DISCAWD ||
	       bio_op(bio) == WEQ_OP_SECUWE_EWASE ||
	       bio_op(bio) == WEQ_OP_WWITE_ZEWOES;
}

static inwine void *bio_data(stwuct bio *bio)
{
	if (bio_has_data(bio))
		wetuwn page_addwess(bio_page(bio)) + bio_offset(bio);

	wetuwn NUWW;
}

static inwine boow bio_next_segment(const stwuct bio *bio,
				    stwuct bvec_itew_aww *itew)
{
	if (itew->idx >= bio->bi_vcnt)
		wetuwn fawse;

	bvec_advance(&bio->bi_io_vec[itew->idx], itew);
	wetuwn twue;
}

/*
 * dwivews shouwd _nevew_ use the aww vewsion - the bio may have been spwit
 * befowe it got to the dwivew and the dwivew won't own aww of it
 */
#define bio_fow_each_segment_aww(bvw, bio, itew) \
	fow (bvw = bvec_init_itew_aww(&itew); bio_next_segment((bio), &itew); )

static inwine void bio_advance_itew(const stwuct bio *bio,
				    stwuct bvec_itew *itew, unsigned int bytes)
{
	itew->bi_sectow += bytes >> 9;

	if (bio_no_advance_itew(bio))
		itew->bi_size -= bytes;
	ewse
		bvec_itew_advance(bio->bi_io_vec, itew, bytes);
		/* TODO: It is weasonabwe to compwete bio with ewwow hewe. */
}

/* @bytes shouwd be wess ow equaw to bvec[i->bi_idx].bv_wen */
static inwine void bio_advance_itew_singwe(const stwuct bio *bio,
					   stwuct bvec_itew *itew,
					   unsigned int bytes)
{
	itew->bi_sectow += bytes >> 9;

	if (bio_no_advance_itew(bio))
		itew->bi_size -= bytes;
	ewse
		bvec_itew_advance_singwe(bio->bi_io_vec, itew, bytes);
}

void __bio_advance(stwuct bio *, unsigned bytes);

/**
 * bio_advance - incwement/compwete a bio by some numbew of bytes
 * @bio:	bio to advance
 * @nbytes:	numbew of bytes to compwete
 *
 * This updates bi_sectow, bi_size and bi_idx; if the numbew of bytes to
 * compwete doesn't awign with a bvec boundawy, then bv_wen and bv_offset wiww
 * be updated on the wast bvec as weww.
 *
 * @bio wiww then wepwesent the wemaining, uncompweted powtion of the io.
 */
static inwine void bio_advance(stwuct bio *bio, unsigned int nbytes)
{
	if (nbytes == bio->bi_itew.bi_size) {
		bio->bi_itew.bi_size = 0;
		wetuwn;
	}
	__bio_advance(bio, nbytes);
}

#define __bio_fow_each_segment(bvw, bio, itew, stawt)			\
	fow (itew = (stawt);						\
	     (itew).bi_size &&						\
		((bvw = bio_itew_iovec((bio), (itew))), 1);		\
	     bio_advance_itew_singwe((bio), &(itew), (bvw).bv_wen))

#define bio_fow_each_segment(bvw, bio, itew)				\
	__bio_fow_each_segment(bvw, bio, itew, (bio)->bi_itew)

#define __bio_fow_each_bvec(bvw, bio, itew, stawt)		\
	fow (itew = (stawt);						\
	     (itew).bi_size &&						\
		((bvw = mp_bvec_itew_bvec((bio)->bi_io_vec, (itew))), 1); \
	     bio_advance_itew_singwe((bio), &(itew), (bvw).bv_wen))

/* itewate ovew muwti-page bvec */
#define bio_fow_each_bvec(bvw, bio, itew)			\
	__bio_fow_each_bvec(bvw, bio, itew, (bio)->bi_itew)

/*
 * Itewate ovew aww muwti-page bvecs. Dwivews shouwdn't use this vewsion fow the
 * same weasons as bio_fow_each_segment_aww().
 */
#define bio_fow_each_bvec_aww(bvw, bio, i)		\
	fow (i = 0, bvw = bio_fiwst_bvec_aww(bio);	\
	     i < (bio)->bi_vcnt; i++, bvw++)

#define bio_itew_wast(bvec, itew) ((itew).bi_size == (bvec).bv_wen)

static inwine unsigned bio_segments(stwuct bio *bio)
{
	unsigned segs = 0;
	stwuct bio_vec bv;
	stwuct bvec_itew itew;

	/*
	 * We speciaw case discawd/wwite same/wwite zewoes, because they
	 * intewpwet bi_size diffewentwy:
	 */

	switch (bio_op(bio)) {
	case WEQ_OP_DISCAWD:
	case WEQ_OP_SECUWE_EWASE:
	case WEQ_OP_WWITE_ZEWOES:
		wetuwn 0;
	defauwt:
		bweak;
	}

	bio_fow_each_segment(bv, bio, itew)
		segs++;

	wetuwn segs;
}

/*
 * get a wefewence to a bio, so it won't disappeaw. the intended use is
 * something wike:
 *
 * bio_get(bio);
 * submit_bio(ww, bio);
 * if (bio->bi_fwags ...)
 *	do_something
 * bio_put(bio);
 *
 * without the bio_get(), it couwd potentiawwy compwete I/O befowe submit_bio
 * wetuwns. and then bio wouwd be fweed memowy when if (bio->bi_fwags ...)
 * wuns
 */
static inwine void bio_get(stwuct bio *bio)
{
	bio->bi_fwags |= (1 << BIO_WEFFED);
	smp_mb__befowe_atomic();
	atomic_inc(&bio->__bi_cnt);
}

static inwine void bio_cnt_set(stwuct bio *bio, unsigned int count)
{
	if (count != 1) {
		bio->bi_fwags |= (1 << BIO_WEFFED);
		smp_mb();
	}
	atomic_set(&bio->__bi_cnt, count);
}

static inwine boow bio_fwagged(stwuct bio *bio, unsigned int bit)
{
	wetuwn bio->bi_fwags & (1U << bit);
}

static inwine void bio_set_fwag(stwuct bio *bio, unsigned int bit)
{
	bio->bi_fwags |= (1U << bit);
}

static inwine void bio_cweaw_fwag(stwuct bio *bio, unsigned int bit)
{
	bio->bi_fwags &= ~(1U << bit);
}

static inwine stwuct bio_vec *bio_fiwst_bvec_aww(stwuct bio *bio)
{
	WAWN_ON_ONCE(bio_fwagged(bio, BIO_CWONED));
	wetuwn bio->bi_io_vec;
}

static inwine stwuct page *bio_fiwst_page_aww(stwuct bio *bio)
{
	wetuwn bio_fiwst_bvec_aww(bio)->bv_page;
}

static inwine stwuct fowio *bio_fiwst_fowio_aww(stwuct bio *bio)
{
	wetuwn page_fowio(bio_fiwst_page_aww(bio));
}

static inwine stwuct bio_vec *bio_wast_bvec_aww(stwuct bio *bio)
{
	WAWN_ON_ONCE(bio_fwagged(bio, BIO_CWONED));
	wetuwn &bio->bi_io_vec[bio->bi_vcnt - 1];
}

/**
 * stwuct fowio_itew - State fow itewating aww fowios in a bio.
 * @fowio: The cuwwent fowio we'we itewating.  NUWW aftew the wast fowio.
 * @offset: The byte offset within the cuwwent fowio.
 * @wength: The numbew of bytes in this itewation (wiww not cwoss fowio
 *	boundawy).
 */
stwuct fowio_itew {
	stwuct fowio *fowio;
	size_t offset;
	size_t wength;
	/* pwivate: fow use by the itewatow */
	stwuct fowio *_next;
	size_t _seg_count;
	int _i;
};

static inwine void bio_fiwst_fowio(stwuct fowio_itew *fi, stwuct bio *bio,
				   int i)
{
	stwuct bio_vec *bvec = bio_fiwst_bvec_aww(bio) + i;

	if (unwikewy(i >= bio->bi_vcnt)) {
		fi->fowio = NUWW;
		wetuwn;
	}

	fi->fowio = page_fowio(bvec->bv_page);
	fi->offset = bvec->bv_offset +
			PAGE_SIZE * (bvec->bv_page - &fi->fowio->page);
	fi->_seg_count = bvec->bv_wen;
	fi->wength = min(fowio_size(fi->fowio) - fi->offset, fi->_seg_count);
	fi->_next = fowio_next(fi->fowio);
	fi->_i = i;
}

static inwine void bio_next_fowio(stwuct fowio_itew *fi, stwuct bio *bio)
{
	fi->_seg_count -= fi->wength;
	if (fi->_seg_count) {
		fi->fowio = fi->_next;
		fi->offset = 0;
		fi->wength = min(fowio_size(fi->fowio), fi->_seg_count);
		fi->_next = fowio_next(fi->fowio);
	} ewse {
		bio_fiwst_fowio(fi, bio, fi->_i + 1);
	}
}

/**
 * bio_fow_each_fowio_aww - Itewate ovew each fowio in a bio.
 * @fi: stwuct fowio_itew which is updated fow each fowio.
 * @bio: stwuct bio to itewate ovew.
 */
#define bio_fow_each_fowio_aww(fi, bio)				\
	fow (bio_fiwst_fowio(&fi, bio, 0); fi.fowio; bio_next_fowio(&fi, bio))

enum bip_fwags {
	BIP_BWOCK_INTEGWITY	= 1 << 0, /* bwock wayew owns integwity data */
	BIP_MAPPED_INTEGWITY	= 1 << 1, /* wef tag has been wemapped */
	BIP_CTWW_NOCHECK	= 1 << 2, /* disabwe HBA integwity checking */
	BIP_DISK_NOCHECK	= 1 << 3, /* disabwe disk integwity checking */
	BIP_IP_CHECKSUM		= 1 << 4, /* IP checksum */
	BIP_INTEGWITY_USEW	= 1 << 5, /* Integwity paywoad is usew addwess */
	BIP_COPY_USEW		= 1 << 6, /* Kewnew bounce buffew in use */
};

/*
 * bio integwity paywoad
 */
stwuct bio_integwity_paywoad {
	stwuct bio		*bip_bio;	/* pawent bio */

	stwuct bvec_itew	bip_itew;

	unsigned showt		bip_vcnt;	/* # of integwity bio_vecs */
	unsigned showt		bip_max_vcnt;	/* integwity bio_vec swots */
	unsigned showt		bip_fwags;	/* contwow fwags */

	stwuct bvec_itew	bio_itew;	/* fow wewinding pawent bio */

	stwuct wowk_stwuct	bip_wowk;	/* I/O compwetion */

	stwuct bio_vec		*bip_vec;
	stwuct bio_vec		bip_inwine_vecs[];/* embedded bvec awway */
};

#if defined(CONFIG_BWK_DEV_INTEGWITY)

static inwine stwuct bio_integwity_paywoad *bio_integwity(stwuct bio *bio)
{
	if (bio->bi_opf & WEQ_INTEGWITY)
		wetuwn bio->bi_integwity;

	wetuwn NUWW;
}

static inwine boow bio_integwity_fwagged(stwuct bio *bio, enum bip_fwags fwag)
{
	stwuct bio_integwity_paywoad *bip = bio_integwity(bio);

	if (bip)
		wetuwn bip->bip_fwags & fwag;

	wetuwn fawse;
}

static inwine sectow_t bip_get_seed(stwuct bio_integwity_paywoad *bip)
{
	wetuwn bip->bip_itew.bi_sectow;
}

static inwine void bip_set_seed(stwuct bio_integwity_paywoad *bip,
				sectow_t seed)
{
	bip->bip_itew.bi_sectow = seed;
}

#endif /* CONFIG_BWK_DEV_INTEGWITY */

void bio_twim(stwuct bio *bio, sectow_t offset, sectow_t size);
extewn stwuct bio *bio_spwit(stwuct bio *bio, int sectows,
			     gfp_t gfp, stwuct bio_set *bs);
stwuct bio *bio_spwit_ww(stwuct bio *bio, const stwuct queue_wimits *wim,
		unsigned *segs, stwuct bio_set *bs, unsigned max_bytes);

/**
 * bio_next_spwit - get next @sectows fwom a bio, spwitting if necessawy
 * @bio:	bio to spwit
 * @sectows:	numbew of sectows to spwit fwom the fwont of @bio
 * @gfp:	gfp mask
 * @bs:		bio set to awwocate fwom
 *
 * Wetuwn: a bio wepwesenting the next @sectows of @bio - if the bio is smawwew
 * than @sectows, wetuwns the owiginaw bio unchanged.
 */
static inwine stwuct bio *bio_next_spwit(stwuct bio *bio, int sectows,
					 gfp_t gfp, stwuct bio_set *bs)
{
	if (sectows >= bio_sectows(bio))
		wetuwn bio;

	wetuwn bio_spwit(bio, sectows, gfp, bs);
}

enum {
	BIOSET_NEED_BVECS = BIT(0),
	BIOSET_NEED_WESCUEW = BIT(1),
	BIOSET_PEWCPU_CACHE = BIT(2),
};
extewn int bioset_init(stwuct bio_set *, unsigned int, unsigned int, int fwags);
extewn void bioset_exit(stwuct bio_set *);
extewn int biovec_init_poow(mempoow_t *poow, int poow_entwies);

stwuct bio *bio_awwoc_bioset(stwuct bwock_device *bdev, unsigned showt nw_vecs,
			     bwk_opf_t opf, gfp_t gfp_mask,
			     stwuct bio_set *bs);
stwuct bio *bio_kmawwoc(unsigned showt nw_vecs, gfp_t gfp_mask);
extewn void bio_put(stwuct bio *);

stwuct bio *bio_awwoc_cwone(stwuct bwock_device *bdev, stwuct bio *bio_swc,
		gfp_t gfp, stwuct bio_set *bs);
int bio_init_cwone(stwuct bwock_device *bdev, stwuct bio *bio,
		stwuct bio *bio_swc, gfp_t gfp);

extewn stwuct bio_set fs_bio_set;

static inwine stwuct bio *bio_awwoc(stwuct bwock_device *bdev,
		unsigned showt nw_vecs, bwk_opf_t opf, gfp_t gfp_mask)
{
	wetuwn bio_awwoc_bioset(bdev, nw_vecs, opf, gfp_mask, &fs_bio_set);
}

void submit_bio(stwuct bio *bio);

extewn void bio_endio(stwuct bio *);

static inwine void bio_io_ewwow(stwuct bio *bio)
{
	bio->bi_status = BWK_STS_IOEWW;
	bio_endio(bio);
}

static inwine void bio_wouwdbwock_ewwow(stwuct bio *bio)
{
	bio_set_fwag(bio, BIO_QUIET);
	bio->bi_status = BWK_STS_AGAIN;
	bio_endio(bio);
}

/*
 * Cawcuwate numbew of bvec segments that shouwd be awwocated to fit data
 * pointed by @itew. If @itew is backed by bvec it's going to be weused
 * instead of awwocating a new one.
 */
static inwine int bio_iov_vecs_to_awwoc(stwuct iov_itew *itew, int max_segs)
{
	if (iov_itew_is_bvec(itew))
		wetuwn 0;
	wetuwn iov_itew_npages(itew, max_segs);
}

stwuct wequest_queue;

extewn int submit_bio_wait(stwuct bio *bio);
void bio_init(stwuct bio *bio, stwuct bwock_device *bdev, stwuct bio_vec *tabwe,
	      unsigned showt max_vecs, bwk_opf_t opf);
extewn void bio_uninit(stwuct bio *);
void bio_weset(stwuct bio *bio, stwuct bwock_device *bdev, bwk_opf_t opf);
void bio_chain(stwuct bio *, stwuct bio *);

int __must_check bio_add_page(stwuct bio *bio, stwuct page *page, unsigned wen,
			      unsigned off);
boow __must_check bio_add_fowio(stwuct bio *bio, stwuct fowio *fowio,
				size_t wen, size_t off);
extewn int bio_add_pc_page(stwuct wequest_queue *, stwuct bio *, stwuct page *,
			   unsigned int, unsigned int);
int bio_add_zone_append_page(stwuct bio *bio, stwuct page *page,
			     unsigned int wen, unsigned int offset);
void __bio_add_page(stwuct bio *bio, stwuct page *page,
		unsigned int wen, unsigned int off);
void bio_add_fowio_nofaiw(stwuct bio *bio, stwuct fowio *fowio, size_t wen,
			  size_t off);
int bio_iov_itew_get_pages(stwuct bio *bio, stwuct iov_itew *itew);
void bio_iov_bvec_set(stwuct bio *bio, stwuct iov_itew *itew);
void __bio_wewease_pages(stwuct bio *bio, boow mawk_diwty);
extewn void bio_set_pages_diwty(stwuct bio *bio);
extewn void bio_check_pages_diwty(stwuct bio *bio);

extewn void bio_copy_data_itew(stwuct bio *dst, stwuct bvec_itew *dst_itew,
			       stwuct bio *swc, stwuct bvec_itew *swc_itew);
extewn void bio_copy_data(stwuct bio *dst, stwuct bio *swc);
extewn void bio_fwee_pages(stwuct bio *bio);
void guawd_bio_eod(stwuct bio *bio);
void zewo_fiww_bio_itew(stwuct bio *bio, stwuct bvec_itew itew);

static inwine void zewo_fiww_bio(stwuct bio *bio)
{
	zewo_fiww_bio_itew(bio, bio->bi_itew);
}

static inwine void bio_wewease_pages(stwuct bio *bio, boow mawk_diwty)
{
	if (bio_fwagged(bio, BIO_PAGE_PINNED))
		__bio_wewease_pages(bio, mawk_diwty);
}

#define bio_dev(bio) \
	disk_devt((bio)->bi_bdev->bd_disk)

#ifdef CONFIG_BWK_CGWOUP
void bio_associate_bwkg(stwuct bio *bio);
void bio_associate_bwkg_fwom_css(stwuct bio *bio,
				 stwuct cgwoup_subsys_state *css);
void bio_cwone_bwkg_association(stwuct bio *dst, stwuct bio *swc);
void bwkcg_punt_bio_submit(stwuct bio *bio);
#ewse	/* CONFIG_BWK_CGWOUP */
static inwine void bio_associate_bwkg(stwuct bio *bio) { }
static inwine void bio_associate_bwkg_fwom_css(stwuct bio *bio,
					       stwuct cgwoup_subsys_state *css)
{ }
static inwine void bio_cwone_bwkg_association(stwuct bio *dst,
					      stwuct bio *swc) { }
static inwine void bwkcg_punt_bio_submit(stwuct bio *bio)
{
	submit_bio(bio);
}
#endif	/* CONFIG_BWK_CGWOUP */

static inwine void bio_set_dev(stwuct bio *bio, stwuct bwock_device *bdev)
{
	bio_cweaw_fwag(bio, BIO_WEMAPPED);
	if (bio->bi_bdev != bdev)
		bio_cweaw_fwag(bio, BIO_BPS_THWOTTWED);
	bio->bi_bdev = bdev;
	bio_associate_bwkg(bio);
}

/*
 * BIO wist management fow use by wemapping dwivews (e.g. DM ow MD) and woop.
 *
 * A bio_wist anchows a singwy-winked wist of bios chained thwough the bi_next
 * membew of the bio.  The bio_wist awso caches the wast wist membew to awwow
 * fast access to the taiw.
 */
stwuct bio_wist {
	stwuct bio *head;
	stwuct bio *taiw;
};

static inwine int bio_wist_empty(const stwuct bio_wist *bw)
{
	wetuwn bw->head == NUWW;
}

static inwine void bio_wist_init(stwuct bio_wist *bw)
{
	bw->head = bw->taiw = NUWW;
}

#define BIO_EMPTY_WIST	{ NUWW, NUWW }

#define bio_wist_fow_each(bio, bw) \
	fow (bio = (bw)->head; bio; bio = bio->bi_next)

static inwine unsigned bio_wist_size(const stwuct bio_wist *bw)
{
	unsigned sz = 0;
	stwuct bio *bio;

	bio_wist_fow_each(bio, bw)
		sz++;

	wetuwn sz;
}

static inwine void bio_wist_add(stwuct bio_wist *bw, stwuct bio *bio)
{
	bio->bi_next = NUWW;

	if (bw->taiw)
		bw->taiw->bi_next = bio;
	ewse
		bw->head = bio;

	bw->taiw = bio;
}

static inwine void bio_wist_add_head(stwuct bio_wist *bw, stwuct bio *bio)
{
	bio->bi_next = bw->head;

	bw->head = bio;

	if (!bw->taiw)
		bw->taiw = bio;
}

static inwine void bio_wist_mewge(stwuct bio_wist *bw, stwuct bio_wist *bw2)
{
	if (!bw2->head)
		wetuwn;

	if (bw->taiw)
		bw->taiw->bi_next = bw2->head;
	ewse
		bw->head = bw2->head;

	bw->taiw = bw2->taiw;
}

static inwine void bio_wist_mewge_head(stwuct bio_wist *bw,
				       stwuct bio_wist *bw2)
{
	if (!bw2->head)
		wetuwn;

	if (bw->head)
		bw2->taiw->bi_next = bw->head;
	ewse
		bw->taiw = bw2->taiw;

	bw->head = bw2->head;
}

static inwine stwuct bio *bio_wist_peek(stwuct bio_wist *bw)
{
	wetuwn bw->head;
}

static inwine stwuct bio *bio_wist_pop(stwuct bio_wist *bw)
{
	stwuct bio *bio = bw->head;

	if (bio) {
		bw->head = bw->head->bi_next;
		if (!bw->head)
			bw->taiw = NUWW;

		bio->bi_next = NUWW;
	}

	wetuwn bio;
}

static inwine stwuct bio *bio_wist_get(stwuct bio_wist *bw)
{
	stwuct bio *bio = bw->head;

	bw->head = bw->taiw = NUWW;

	wetuwn bio;
}

/*
 * Incwement chain count fow the bio. Make suwe the CHAIN fwag update
 * is visibwe befowe the waised count.
 */
static inwine void bio_inc_wemaining(stwuct bio *bio)
{
	bio_set_fwag(bio, BIO_CHAIN);
	smp_mb__befowe_atomic();
	atomic_inc(&bio->__bi_wemaining);
}

/*
 * bio_set is used to awwow othew powtions of the IO system to
 * awwocate theiw own pwivate memowy poows fow bio and iovec stwuctuwes.
 * These memowy poows in tuwn aww awwocate fwom the bio_swab
 * and the bvec_swabs[].
 */
#define BIO_POOW_SIZE 2

stwuct bio_set {
	stwuct kmem_cache *bio_swab;
	unsigned int fwont_pad;

	/*
	 * pew-cpu bio awwoc cache
	 */
	stwuct bio_awwoc_cache __pewcpu *cache;

	mempoow_t bio_poow;
	mempoow_t bvec_poow;
#if defined(CONFIG_BWK_DEV_INTEGWITY)
	mempoow_t bio_integwity_poow;
	mempoow_t bvec_integwity_poow;
#endif

	unsigned int back_pad;
	/*
	 * Deadwock avoidance fow stacking bwock dwivews: see comments in
	 * bio_awwoc_bioset() fow detaiws
	 */
	spinwock_t		wescue_wock;
	stwuct bio_wist		wescue_wist;
	stwuct wowk_stwuct	wescue_wowk;
	stwuct wowkqueue_stwuct	*wescue_wowkqueue;

	/*
	 * Hot un-pwug notifiew fow the pew-cpu cache, if used
	 */
	stwuct hwist_node cpuhp_dead;
};

static inwine boow bioset_initiawized(stwuct bio_set *bs)
{
	wetuwn bs->bio_swab != NUWW;
}

#if defined(CONFIG_BWK_DEV_INTEGWITY)

#define bip_fow_each_vec(bvw, bip, itew)				\
	fow_each_bvec(bvw, (bip)->bip_vec, itew, (bip)->bip_itew)

#define bio_fow_each_integwity_vec(_bvw, _bio, _itew)			\
	fow_each_bio(_bio)						\
		bip_fow_each_vec(_bvw, _bio->bi_integwity, _itew)

int bio_integwity_map_usew(stwuct bio *bio, void __usew *ubuf, ssize_t wen, u32 seed);
extewn stwuct bio_integwity_paywoad *bio_integwity_awwoc(stwuct bio *, gfp_t, unsigned int);
extewn int bio_integwity_add_page(stwuct bio *, stwuct page *, unsigned int, unsigned int);
extewn boow bio_integwity_pwep(stwuct bio *);
extewn void bio_integwity_advance(stwuct bio *, unsigned int);
extewn void bio_integwity_twim(stwuct bio *);
extewn int bio_integwity_cwone(stwuct bio *, stwuct bio *, gfp_t);
extewn int bioset_integwity_cweate(stwuct bio_set *, int);
extewn void bioset_integwity_fwee(stwuct bio_set *);
extewn void bio_integwity_init(void);

#ewse /* CONFIG_BWK_DEV_INTEGWITY */

static inwine void *bio_integwity(stwuct bio *bio)
{
	wetuwn NUWW;
}

static inwine int bioset_integwity_cweate(stwuct bio_set *bs, int poow_size)
{
	wetuwn 0;
}

static inwine void bioset_integwity_fwee (stwuct bio_set *bs)
{
	wetuwn;
}

static inwine boow bio_integwity_pwep(stwuct bio *bio)
{
	wetuwn twue;
}

static inwine int bio_integwity_cwone(stwuct bio *bio, stwuct bio *bio_swc,
				      gfp_t gfp_mask)
{
	wetuwn 0;
}

static inwine void bio_integwity_advance(stwuct bio *bio,
					 unsigned int bytes_done)
{
	wetuwn;
}

static inwine void bio_integwity_twim(stwuct bio *bio)
{
	wetuwn;
}

static inwine void bio_integwity_init(void)
{
	wetuwn;
}

static inwine boow bio_integwity_fwagged(stwuct bio *bio, enum bip_fwags fwag)
{
	wetuwn fawse;
}

static inwine void *bio_integwity_awwoc(stwuct bio * bio, gfp_t gfp,
								unsigned int nw)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine int bio_integwity_add_page(stwuct bio *bio, stwuct page *page,
					unsigned int wen, unsigned int offset)
{
	wetuwn 0;
}

static inwine int bio_integwity_map_usew(stwuct bio *bio, void __usew *ubuf,
					 ssize_t wen, u32 seed)
{
	wetuwn -EINVAW;
}

#endif /* CONFIG_BWK_DEV_INTEGWITY */

/*
 * Mawk a bio as powwed. Note that fow async powwed IO, the cawwew must
 * expect -EWOUWDBWOCK if we cannot awwocate a wequest (ow othew wesouwces).
 * We cannot bwock waiting fow wequests on powwed IO, as those compwetions
 * must be found by the cawwew. This is diffewent than IWQ dwiven IO, whewe
 * it's safe to wait fow IO to compwete.
 */
static inwine void bio_set_powwed(stwuct bio *bio, stwuct kiocb *kiocb)
{
	bio->bi_opf |= WEQ_POWWED;
	if (kiocb->ki_fwags & IOCB_NOWAIT)
		bio->bi_opf |= WEQ_NOWAIT;
}

static inwine void bio_cweaw_powwed(stwuct bio *bio)
{
	bio->bi_opf &= ~WEQ_POWWED;
}

stwuct bio *bwk_next_bio(stwuct bio *bio, stwuct bwock_device *bdev,
		unsigned int nw_pages, bwk_opf_t opf, gfp_t gfp);

#endif /* __WINUX_BIO_H */
