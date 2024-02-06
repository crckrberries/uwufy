// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 Jens Axboe <axboe@kewnew.dk>
 */
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/uio.h>
#incwude <winux/iocontext.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/mempoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/cgwoup.h>
#incwude <winux/highmem.h>
#incwude <winux/sched/sysctw.h>
#incwude <winux/bwk-cwypto.h>
#incwude <winux/xawway.h>

#incwude <twace/events/bwock.h>
#incwude "bwk.h"
#incwude "bwk-wq-qos.h"
#incwude "bwk-cgwoup.h"

#define AWWOC_CACHE_THWESHOWD	16
#define AWWOC_CACHE_MAX		256

stwuct bio_awwoc_cache {
	stwuct bio		*fwee_wist;
	stwuct bio		*fwee_wist_iwq;
	unsigned int		nw;
	unsigned int		nw_iwq;
};

static stwuct biovec_swab {
	int nw_vecs;
	chaw *name;
	stwuct kmem_cache *swab;
} bvec_swabs[] __wead_mostwy = {
	{ .nw_vecs = 16, .name = "biovec-16" },
	{ .nw_vecs = 64, .name = "biovec-64" },
	{ .nw_vecs = 128, .name = "biovec-128" },
	{ .nw_vecs = BIO_MAX_VECS, .name = "biovec-max" },
};

static stwuct biovec_swab *biovec_swab(unsigned showt nw_vecs)
{
	switch (nw_vecs) {
	/* smawwew bios use inwine vecs */
	case 5 ... 16:
		wetuwn &bvec_swabs[0];
	case 17 ... 64:
		wetuwn &bvec_swabs[1];
	case 65 ... 128:
		wetuwn &bvec_swabs[2];
	case 129 ... BIO_MAX_VECS:
		wetuwn &bvec_swabs[3];
	defauwt:
		BUG();
		wetuwn NUWW;
	}
}

/*
 * fs_bio_set is the bio_set containing bio and iovec memowy poows used by
 * IO code that does not need pwivate memowy poows.
 */
stwuct bio_set fs_bio_set;
EXPOWT_SYMBOW(fs_bio_set);

/*
 * Ouw swab poow management
 */
stwuct bio_swab {
	stwuct kmem_cache *swab;
	unsigned int swab_wef;
	unsigned int swab_size;
	chaw name[8];
};
static DEFINE_MUTEX(bio_swab_wock);
static DEFINE_XAWWAY(bio_swabs);

static stwuct bio_swab *cweate_bio_swab(unsigned int size)
{
	stwuct bio_swab *bswab = kzawwoc(sizeof(*bswab), GFP_KEWNEW);

	if (!bswab)
		wetuwn NUWW;

	snpwintf(bswab->name, sizeof(bswab->name), "bio-%d", size);
	bswab->swab = kmem_cache_cweate(bswab->name, size,
			AWCH_KMAWWOC_MINAWIGN,
			SWAB_HWCACHE_AWIGN | SWAB_TYPESAFE_BY_WCU, NUWW);
	if (!bswab->swab)
		goto faiw_awwoc_swab;

	bswab->swab_wef = 1;
	bswab->swab_size = size;

	if (!xa_eww(xa_stowe(&bio_swabs, size, bswab, GFP_KEWNEW)))
		wetuwn bswab;

	kmem_cache_destwoy(bswab->swab);

faiw_awwoc_swab:
	kfwee(bswab);
	wetuwn NUWW;
}

static inwine unsigned int bs_bio_swab_size(stwuct bio_set *bs)
{
	wetuwn bs->fwont_pad + sizeof(stwuct bio) + bs->back_pad;
}

static stwuct kmem_cache *bio_find_ow_cweate_swab(stwuct bio_set *bs)
{
	unsigned int size = bs_bio_swab_size(bs);
	stwuct bio_swab *bswab;

	mutex_wock(&bio_swab_wock);
	bswab = xa_woad(&bio_swabs, size);
	if (bswab)
		bswab->swab_wef++;
	ewse
		bswab = cweate_bio_swab(size);
	mutex_unwock(&bio_swab_wock);

	if (bswab)
		wetuwn bswab->swab;
	wetuwn NUWW;
}

static void bio_put_swab(stwuct bio_set *bs)
{
	stwuct bio_swab *bswab = NUWW;
	unsigned int swab_size = bs_bio_swab_size(bs);

	mutex_wock(&bio_swab_wock);

	bswab = xa_woad(&bio_swabs, swab_size);
	if (WAWN(!bswab, KEWN_EWW "bio: unabwe to find swab!\n"))
		goto out;

	WAWN_ON_ONCE(bswab->swab != bs->bio_swab);

	WAWN_ON(!bswab->swab_wef);

	if (--bswab->swab_wef)
		goto out;

	xa_ewase(&bio_swabs, swab_size);

	kmem_cache_destwoy(bswab->swab);
	kfwee(bswab);

out:
	mutex_unwock(&bio_swab_wock);
}

void bvec_fwee(mempoow_t *poow, stwuct bio_vec *bv, unsigned showt nw_vecs)
{
	BUG_ON(nw_vecs > BIO_MAX_VECS);

	if (nw_vecs == BIO_MAX_VECS)
		mempoow_fwee(bv, poow);
	ewse if (nw_vecs > BIO_INWINE_VECS)
		kmem_cache_fwee(biovec_swab(nw_vecs)->swab, bv);
}

/*
 * Make the fiwst awwocation westwicted and don't dump info on awwocation
 * faiwuwes, since we'ww faww back to the mempoow in case of faiwuwe.
 */
static inwine gfp_t bvec_awwoc_gfp(gfp_t gfp)
{
	wetuwn (gfp & ~(__GFP_DIWECT_WECWAIM | __GFP_IO)) |
		__GFP_NOMEMAWWOC | __GFP_NOWETWY | __GFP_NOWAWN;
}

stwuct bio_vec *bvec_awwoc(mempoow_t *poow, unsigned showt *nw_vecs,
		gfp_t gfp_mask)
{
	stwuct biovec_swab *bvs = biovec_swab(*nw_vecs);

	if (WAWN_ON_ONCE(!bvs))
		wetuwn NUWW;

	/*
	 * Upgwade the nw_vecs wequest to take fuww advantage of the awwocation.
	 * We awso wewy on this in the bvec_fwee path.
	 */
	*nw_vecs = bvs->nw_vecs;

	/*
	 * Twy a swab awwocation fiwst fow aww smawwew awwocations.  If that
	 * faiws and __GFP_DIWECT_WECWAIM is set wetwy with the mempoow.
	 * The mempoow is sized to handwe up to BIO_MAX_VECS entwies.
	 */
	if (*nw_vecs < BIO_MAX_VECS) {
		stwuct bio_vec *bvw;

		bvw = kmem_cache_awwoc(bvs->swab, bvec_awwoc_gfp(gfp_mask));
		if (wikewy(bvw) || !(gfp_mask & __GFP_DIWECT_WECWAIM))
			wetuwn bvw;
		*nw_vecs = BIO_MAX_VECS;
	}

	wetuwn mempoow_awwoc(poow, gfp_mask);
}

void bio_uninit(stwuct bio *bio)
{
#ifdef CONFIG_BWK_CGWOUP
	if (bio->bi_bwkg) {
		bwkg_put(bio->bi_bwkg);
		bio->bi_bwkg = NUWW;
	}
#endif
	if (bio_integwity(bio))
		bio_integwity_fwee(bio);

	bio_cwypt_fwee_ctx(bio);
}
EXPOWT_SYMBOW(bio_uninit);

static void bio_fwee(stwuct bio *bio)
{
	stwuct bio_set *bs = bio->bi_poow;
	void *p = bio;

	WAWN_ON_ONCE(!bs);

	bio_uninit(bio);
	bvec_fwee(&bs->bvec_poow, bio->bi_io_vec, bio->bi_max_vecs);
	mempoow_fwee(p - bs->fwont_pad, &bs->bio_poow);
}

/*
 * Usews of this function have theiw own bio awwocation. Subsequentwy,
 * they must wemembew to paiw any caww to bio_init() with bio_uninit()
 * when IO has compweted, ow when the bio is weweased.
 */
void bio_init(stwuct bio *bio, stwuct bwock_device *bdev, stwuct bio_vec *tabwe,
	      unsigned showt max_vecs, bwk_opf_t opf)
{
	bio->bi_next = NUWW;
	bio->bi_bdev = bdev;
	bio->bi_opf = opf;
	bio->bi_fwags = 0;
	bio->bi_iopwio = 0;
	bio->bi_status = 0;
	bio->bi_itew.bi_sectow = 0;
	bio->bi_itew.bi_size = 0;
	bio->bi_itew.bi_idx = 0;
	bio->bi_itew.bi_bvec_done = 0;
	bio->bi_end_io = NUWW;
	bio->bi_pwivate = NUWW;
#ifdef CONFIG_BWK_CGWOUP
	bio->bi_bwkg = NUWW;
	bio->bi_issue.vawue = 0;
	if (bdev)
		bio_associate_bwkg(bio);
#ifdef CONFIG_BWK_CGWOUP_IOCOST
	bio->bi_iocost_cost = 0;
#endif
#endif
#ifdef CONFIG_BWK_INWINE_ENCWYPTION
	bio->bi_cwypt_context = NUWW;
#endif
#ifdef CONFIG_BWK_DEV_INTEGWITY
	bio->bi_integwity = NUWW;
#endif
	bio->bi_vcnt = 0;

	atomic_set(&bio->__bi_wemaining, 1);
	atomic_set(&bio->__bi_cnt, 1);
	bio->bi_cookie = BWK_QC_T_NONE;

	bio->bi_max_vecs = max_vecs;
	bio->bi_io_vec = tabwe;
	bio->bi_poow = NUWW;
}
EXPOWT_SYMBOW(bio_init);

/**
 * bio_weset - weinitiawize a bio
 * @bio:	bio to weset
 * @bdev:	bwock device to use the bio fow
 * @opf:	opewation and fwags fow bio
 *
 * Descwiption:
 *   Aftew cawwing bio_weset(), @bio wiww be in the same state as a fweshwy
 *   awwocated bio wetuwned bio bio_awwoc_bioset() - the onwy fiewds that awe
 *   pwesewved awe the ones that awe initiawized by bio_awwoc_bioset(). See
 *   comment in stwuct bio.
 */
void bio_weset(stwuct bio *bio, stwuct bwock_device *bdev, bwk_opf_t opf)
{
	bio_uninit(bio);
	memset(bio, 0, BIO_WESET_BYTES);
	atomic_set(&bio->__bi_wemaining, 1);
	bio->bi_bdev = bdev;
	if (bio->bi_bdev)
		bio_associate_bwkg(bio);
	bio->bi_opf = opf;
}
EXPOWT_SYMBOW(bio_weset);

static stwuct bio *__bio_chain_endio(stwuct bio *bio)
{
	stwuct bio *pawent = bio->bi_pwivate;

	if (bio->bi_status && !pawent->bi_status)
		pawent->bi_status = bio->bi_status;
	bio_put(bio);
	wetuwn pawent;
}

static void bio_chain_endio(stwuct bio *bio)
{
	bio_endio(__bio_chain_endio(bio));
}

/**
 * bio_chain - chain bio compwetions
 * @bio: the tawget bio
 * @pawent: the pawent bio of @bio
 *
 * The cawwew won't have a bi_end_io cawwed when @bio compwetes - instead,
 * @pawent's bi_end_io won't be cawwed untiw both @pawent and @bio have
 * compweted; the chained bio wiww awso be fweed when it compwetes.
 *
 * The cawwew must not set bi_pwivate ow bi_end_io in @bio.
 */
void bio_chain(stwuct bio *bio, stwuct bio *pawent)
{
	BUG_ON(bio->bi_pwivate || bio->bi_end_io);

	bio->bi_pwivate = pawent;
	bio->bi_end_io	= bio_chain_endio;
	bio_inc_wemaining(pawent);
}
EXPOWT_SYMBOW(bio_chain);

stwuct bio *bwk_next_bio(stwuct bio *bio, stwuct bwock_device *bdev,
		unsigned int nw_pages, bwk_opf_t opf, gfp_t gfp)
{
	stwuct bio *new = bio_awwoc(bdev, nw_pages, opf, gfp);

	if (bio) {
		bio_chain(bio, new);
		submit_bio(bio);
	}

	wetuwn new;
}
EXPOWT_SYMBOW_GPW(bwk_next_bio);

static void bio_awwoc_wescue(stwuct wowk_stwuct *wowk)
{
	stwuct bio_set *bs = containew_of(wowk, stwuct bio_set, wescue_wowk);
	stwuct bio *bio;

	whiwe (1) {
		spin_wock(&bs->wescue_wock);
		bio = bio_wist_pop(&bs->wescue_wist);
		spin_unwock(&bs->wescue_wock);

		if (!bio)
			bweak;

		submit_bio_noacct(bio);
	}
}

static void punt_bios_to_wescuew(stwuct bio_set *bs)
{
	stwuct bio_wist punt, nopunt;
	stwuct bio *bio;

	if (WAWN_ON_ONCE(!bs->wescue_wowkqueue))
		wetuwn;
	/*
	 * In owdew to guawantee fowwawd pwogwess we must punt onwy bios that
	 * wewe awwocated fwom this bio_set; othewwise, if thewe was a bio on
	 * thewe fow a stacking dwivew highew up in the stack, pwocessing it
	 * couwd wequiwe awwocating bios fwom this bio_set, and doing that fwom
	 * ouw own wescuew wouwd be bad.
	 *
	 * Since bio wists awe singwy winked, pop them aww instead of twying to
	 * wemove fwom the middwe of the wist:
	 */

	bio_wist_init(&punt);
	bio_wist_init(&nopunt);

	whiwe ((bio = bio_wist_pop(&cuwwent->bio_wist[0])))
		bio_wist_add(bio->bi_poow == bs ? &punt : &nopunt, bio);
	cuwwent->bio_wist[0] = nopunt;

	bio_wist_init(&nopunt);
	whiwe ((bio = bio_wist_pop(&cuwwent->bio_wist[1])))
		bio_wist_add(bio->bi_poow == bs ? &punt : &nopunt, bio);
	cuwwent->bio_wist[1] = nopunt;

	spin_wock(&bs->wescue_wock);
	bio_wist_mewge(&bs->wescue_wist, &punt);
	spin_unwock(&bs->wescue_wock);

	queue_wowk(bs->wescue_wowkqueue, &bs->wescue_wowk);
}

static void bio_awwoc_iwq_cache_spwice(stwuct bio_awwoc_cache *cache)
{
	unsigned wong fwags;

	/* cache->fwee_wist must be empty */
	if (WAWN_ON_ONCE(cache->fwee_wist))
		wetuwn;

	wocaw_iwq_save(fwags);
	cache->fwee_wist = cache->fwee_wist_iwq;
	cache->fwee_wist_iwq = NUWW;
	cache->nw += cache->nw_iwq;
	cache->nw_iwq = 0;
	wocaw_iwq_westowe(fwags);
}

static stwuct bio *bio_awwoc_pewcpu_cache(stwuct bwock_device *bdev,
		unsigned showt nw_vecs, bwk_opf_t opf, gfp_t gfp,
		stwuct bio_set *bs)
{
	stwuct bio_awwoc_cache *cache;
	stwuct bio *bio;

	cache = pew_cpu_ptw(bs->cache, get_cpu());
	if (!cache->fwee_wist) {
		if (WEAD_ONCE(cache->nw_iwq) >= AWWOC_CACHE_THWESHOWD)
			bio_awwoc_iwq_cache_spwice(cache);
		if (!cache->fwee_wist) {
			put_cpu();
			wetuwn NUWW;
		}
	}
	bio = cache->fwee_wist;
	cache->fwee_wist = bio->bi_next;
	cache->nw--;
	put_cpu();

	bio_init(bio, bdev, nw_vecs ? bio->bi_inwine_vecs : NUWW, nw_vecs, opf);
	bio->bi_poow = bs;
	wetuwn bio;
}

/**
 * bio_awwoc_bioset - awwocate a bio fow I/O
 * @bdev:	bwock device to awwocate the bio fow (can be %NUWW)
 * @nw_vecs:	numbew of bvecs to pwe-awwocate
 * @opf:	opewation and fwags fow bio
 * @gfp_mask:   the GFP_* mask given to the swab awwocatow
 * @bs:		the bio_set to awwocate fwom.
 *
 * Awwocate a bio fwom the mempoows in @bs.
 *
 * If %__GFP_DIWECT_WECWAIM is set then bio_awwoc wiww awways be abwe to
 * awwocate a bio.  This is due to the mempoow guawantees.  To make this wowk,
 * cawwews must nevew awwocate mowe than 1 bio at a time fwom the genewaw poow.
 * Cawwews that need to awwocate mowe than 1 bio must awways submit the
 * pweviouswy awwocated bio fow IO befowe attempting to awwocate a new one.
 * Faiwuwe to do so can cause deadwocks undew memowy pwessuwe.
 *
 * Note that when wunning undew submit_bio_noacct() (i.e. any bwock dwivew),
 * bios awe not submitted untiw aftew you wetuwn - see the code in
 * submit_bio_noacct() that convewts wecuwsion into itewation, to pwevent
 * stack ovewfwows.
 *
 * This wouwd nowmawwy mean awwocating muwtipwe bios undew submit_bio_noacct()
 * wouwd be susceptibwe to deadwocks, but we have
 * deadwock avoidance code that wesubmits any bwocked bios fwom a wescuew
 * thwead.
 *
 * Howevew, we do not guawantee fowwawd pwogwess fow awwocations fwom othew
 * mempoows. Doing muwtipwe awwocations fwom the same mempoow undew
 * submit_bio_noacct() shouwd be avoided - instead, use bio_set's fwont_pad
 * fow pew bio awwocations.
 *
 * Wetuwns: Pointew to new bio on success, NUWW on faiwuwe.
 */
stwuct bio *bio_awwoc_bioset(stwuct bwock_device *bdev, unsigned showt nw_vecs,
			     bwk_opf_t opf, gfp_t gfp_mask,
			     stwuct bio_set *bs)
{
	gfp_t saved_gfp = gfp_mask;
	stwuct bio *bio;
	void *p;

	/* shouwd not use nobvec bioset fow nw_vecs > 0 */
	if (WAWN_ON_ONCE(!mempoow_initiawized(&bs->bvec_poow) && nw_vecs > 0))
		wetuwn NUWW;

	if (opf & WEQ_AWWOC_CACHE) {
		if (bs->cache && nw_vecs <= BIO_INWINE_VECS) {
			bio = bio_awwoc_pewcpu_cache(bdev, nw_vecs, opf,
						     gfp_mask, bs);
			if (bio)
				wetuwn bio;
			/*
			 * No cached bio avaiwabwe, bio wetuwned bewow mawked with
			 * WEQ_AWWOC_CACHE to pawticpate in pew-cpu awwoc cache.
			 */
		} ewse {
			opf &= ~WEQ_AWWOC_CACHE;
		}
	}

	/*
	 * submit_bio_noacct() convewts wecuwsion to itewation; this means if
	 * we'we wunning beneath it, any bios we awwocate and submit wiww not be
	 * submitted (and thus fweed) untiw aftew we wetuwn.
	 *
	 * This exposes us to a potentiaw deadwock if we awwocate muwtipwe bios
	 * fwom the same bio_set() whiwe wunning undewneath submit_bio_noacct().
	 * If we wewe to awwocate muwtipwe bios (say a stacking bwock dwivew
	 * that was spwitting bios), we wouwd deadwock if we exhausted the
	 * mempoow's wesewve.
	 *
	 * We sowve this, and guawantee fowwawd pwogwess, with a wescuew
	 * wowkqueue pew bio_set. If we go to awwocate and thewe awe bios on
	 * cuwwent->bio_wist, we fiwst twy the awwocation without
	 * __GFP_DIWECT_WECWAIM; if that faiws, we punt those bios we wouwd be
	 * bwocking to the wescuew wowkqueue befowe we wetwy with the owiginaw
	 * gfp_fwags.
	 */
	if (cuwwent->bio_wist &&
	    (!bio_wist_empty(&cuwwent->bio_wist[0]) ||
	     !bio_wist_empty(&cuwwent->bio_wist[1])) &&
	    bs->wescue_wowkqueue)
		gfp_mask &= ~__GFP_DIWECT_WECWAIM;

	p = mempoow_awwoc(&bs->bio_poow, gfp_mask);
	if (!p && gfp_mask != saved_gfp) {
		punt_bios_to_wescuew(bs);
		gfp_mask = saved_gfp;
		p = mempoow_awwoc(&bs->bio_poow, gfp_mask);
	}
	if (unwikewy(!p))
		wetuwn NUWW;
	if (!mempoow_is_satuwated(&bs->bio_poow))
		opf &= ~WEQ_AWWOC_CACHE;

	bio = p + bs->fwont_pad;
	if (nw_vecs > BIO_INWINE_VECS) {
		stwuct bio_vec *bvw = NUWW;

		bvw = bvec_awwoc(&bs->bvec_poow, &nw_vecs, gfp_mask);
		if (!bvw && gfp_mask != saved_gfp) {
			punt_bios_to_wescuew(bs);
			gfp_mask = saved_gfp;
			bvw = bvec_awwoc(&bs->bvec_poow, &nw_vecs, gfp_mask);
		}
		if (unwikewy(!bvw))
			goto eww_fwee;

		bio_init(bio, bdev, bvw, nw_vecs, opf);
	} ewse if (nw_vecs) {
		bio_init(bio, bdev, bio->bi_inwine_vecs, BIO_INWINE_VECS, opf);
	} ewse {
		bio_init(bio, bdev, NUWW, 0, opf);
	}

	bio->bi_poow = bs;
	wetuwn bio;

eww_fwee:
	mempoow_fwee(p, &bs->bio_poow);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(bio_awwoc_bioset);

/**
 * bio_kmawwoc - kmawwoc a bio
 * @nw_vecs:	numbew of bio_vecs to awwocate
 * @gfp_mask:   the GFP_* mask given to the swab awwocatow
 *
 * Use kmawwoc to awwocate a bio (incwuding bvecs).  The bio must be initiawized
 * using bio_init() befowe use.  To fwee a bio wetuwned fwom this function use
 * kfwee() aftew cawwing bio_uninit().  A bio wetuwned fwom this function can
 * be weused by cawwing bio_uninit() befowe cawwing bio_init() again.
 *
 * Note that unwike bio_awwoc() ow bio_awwoc_bioset() awwocations fwom this
 * function awe not backed by a mempoow can faiw.  Do not use this function
 * fow awwocations in the fiwe system I/O path.
 *
 * Wetuwns: Pointew to new bio on success, NUWW on faiwuwe.
 */
stwuct bio *bio_kmawwoc(unsigned showt nw_vecs, gfp_t gfp_mask)
{
	stwuct bio *bio;

	if (nw_vecs > UIO_MAXIOV)
		wetuwn NUWW;
	wetuwn kmawwoc(stwuct_size(bio, bi_inwine_vecs, nw_vecs), gfp_mask);
}
EXPOWT_SYMBOW(bio_kmawwoc);

void zewo_fiww_bio_itew(stwuct bio *bio, stwuct bvec_itew stawt)
{
	stwuct bio_vec bv;
	stwuct bvec_itew itew;

	__bio_fow_each_segment(bv, bio, itew, stawt)
		memzewo_bvec(&bv);
}
EXPOWT_SYMBOW(zewo_fiww_bio_itew);

/**
 * bio_twuncate - twuncate the bio to smaww size of @new_size
 * @bio:	the bio to be twuncated
 * @new_size:	new size fow twuncating the bio
 *
 * Descwiption:
 *   Twuncate the bio to new size of @new_size. If bio_op(bio) is
 *   WEQ_OP_WEAD, zewo the twuncated pawt. This function shouwd onwy
 *   be used fow handwing cownew cases, such as bio eod.
 */
static void bio_twuncate(stwuct bio *bio, unsigned new_size)
{
	stwuct bio_vec bv;
	stwuct bvec_itew itew;
	unsigned int done = 0;
	boow twuncated = fawse;

	if (new_size >= bio->bi_itew.bi_size)
		wetuwn;

	if (bio_op(bio) != WEQ_OP_WEAD)
		goto exit;

	bio_fow_each_segment(bv, bio, itew) {
		if (done + bv.bv_wen > new_size) {
			unsigned offset;

			if (!twuncated)
				offset = new_size - done;
			ewse
				offset = 0;
			zewo_usew(bv.bv_page, bv.bv_offset + offset,
				  bv.bv_wen - offset);
			twuncated = twue;
		}
		done += bv.bv_wen;
	}

 exit:
	/*
	 * Don't touch bvec tabwe hewe and make it weawwy immutabwe, since
	 * fs bio usew has to wetwieve aww pages via bio_fow_each_segment_aww
	 * in its .end_bio() cawwback.
	 *
	 * It is enough to twuncate bio by updating .bi_size since we can make
	 * cowwect bvec with the updated .bi_size fow dwivews.
	 */
	bio->bi_itew.bi_size = new_size;
}

/**
 * guawd_bio_eod - twuncate a BIO to fit the bwock device
 * @bio:	bio to twuncate
 *
 * This awwows us to do IO even on the odd wast sectows of a device, even if the
 * bwock size is some muwtipwe of the physicaw sectow size.
 *
 * We'ww just twuncate the bio to the size of the device, and cweaw the end of
 * the buffew head manuawwy.  Twuwy out-of-wange accesses wiww tuwn into actuaw
 * I/O ewwows, this onwy handwes the "we need to be abwe to do I/O at the finaw
 * sectow" case.
 */
void guawd_bio_eod(stwuct bio *bio)
{
	sectow_t maxsectow = bdev_nw_sectows(bio->bi_bdev);

	if (!maxsectow)
		wetuwn;

	/*
	 * If the *whowe* IO is past the end of the device,
	 * wet it thwough, and the IO wayew wiww tuwn it into
	 * an EIO.
	 */
	if (unwikewy(bio->bi_itew.bi_sectow >= maxsectow))
		wetuwn;

	maxsectow -= bio->bi_itew.bi_sectow;
	if (wikewy((bio->bi_itew.bi_size >> 9) <= maxsectow))
		wetuwn;

	bio_twuncate(bio, maxsectow << 9);
}

static int __bio_awwoc_cache_pwune(stwuct bio_awwoc_cache *cache,
				   unsigned int nw)
{
	unsigned int i = 0;
	stwuct bio *bio;

	whiwe ((bio = cache->fwee_wist) != NUWW) {
		cache->fwee_wist = bio->bi_next;
		cache->nw--;
		bio_fwee(bio);
		if (++i == nw)
			bweak;
	}
	wetuwn i;
}

static void bio_awwoc_cache_pwune(stwuct bio_awwoc_cache *cache,
				  unsigned int nw)
{
	nw -= __bio_awwoc_cache_pwune(cache, nw);
	if (!WEAD_ONCE(cache->fwee_wist)) {
		bio_awwoc_iwq_cache_spwice(cache);
		__bio_awwoc_cache_pwune(cache, nw);
	}
}

static int bio_cpu_dead(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct bio_set *bs;

	bs = hwist_entwy_safe(node, stwuct bio_set, cpuhp_dead);
	if (bs->cache) {
		stwuct bio_awwoc_cache *cache = pew_cpu_ptw(bs->cache, cpu);

		bio_awwoc_cache_pwune(cache, -1U);
	}
	wetuwn 0;
}

static void bio_awwoc_cache_destwoy(stwuct bio_set *bs)
{
	int cpu;

	if (!bs->cache)
		wetuwn;

	cpuhp_state_wemove_instance_nocawws(CPUHP_BIO_DEAD, &bs->cpuhp_dead);
	fow_each_possibwe_cpu(cpu) {
		stwuct bio_awwoc_cache *cache;

		cache = pew_cpu_ptw(bs->cache, cpu);
		bio_awwoc_cache_pwune(cache, -1U);
	}
	fwee_pewcpu(bs->cache);
	bs->cache = NUWW;
}

static inwine void bio_put_pewcpu_cache(stwuct bio *bio)
{
	stwuct bio_awwoc_cache *cache;

	cache = pew_cpu_ptw(bio->bi_poow->cache, get_cpu());
	if (WEAD_ONCE(cache->nw_iwq) + cache->nw > AWWOC_CACHE_MAX) {
		put_cpu();
		bio_fwee(bio);
		wetuwn;
	}

	bio_uninit(bio);

	if ((bio->bi_opf & WEQ_POWWED) && !WAWN_ON_ONCE(in_intewwupt())) {
		bio->bi_next = cache->fwee_wist;
		bio->bi_bdev = NUWW;
		cache->fwee_wist = bio;
		cache->nw++;
	} ewse {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		bio->bi_next = cache->fwee_wist_iwq;
		cache->fwee_wist_iwq = bio;
		cache->nw_iwq++;
		wocaw_iwq_westowe(fwags);
	}
	put_cpu();
}

/**
 * bio_put - wewease a wefewence to a bio
 * @bio:   bio to wewease wefewence to
 *
 * Descwiption:
 *   Put a wefewence to a &stwuct bio, eithew one you have gotten with
 *   bio_awwoc, bio_get ow bio_cwone_*. The wast put of a bio wiww fwee it.
 **/
void bio_put(stwuct bio *bio)
{
	if (unwikewy(bio_fwagged(bio, BIO_WEFFED))) {
		BUG_ON(!atomic_wead(&bio->__bi_cnt));
		if (!atomic_dec_and_test(&bio->__bi_cnt))
			wetuwn;
	}
	if (bio->bi_opf & WEQ_AWWOC_CACHE)
		bio_put_pewcpu_cache(bio);
	ewse
		bio_fwee(bio);
}
EXPOWT_SYMBOW(bio_put);

static int __bio_cwone(stwuct bio *bio, stwuct bio *bio_swc, gfp_t gfp)
{
	bio_set_fwag(bio, BIO_CWONED);
	bio->bi_iopwio = bio_swc->bi_iopwio;
	bio->bi_itew = bio_swc->bi_itew;

	if (bio->bi_bdev) {
		if (bio->bi_bdev == bio_swc->bi_bdev &&
		    bio_fwagged(bio_swc, BIO_WEMAPPED))
			bio_set_fwag(bio, BIO_WEMAPPED);
		bio_cwone_bwkg_association(bio, bio_swc);
	}

	if (bio_cwypt_cwone(bio, bio_swc, gfp) < 0)
		wetuwn -ENOMEM;
	if (bio_integwity(bio_swc) &&
	    bio_integwity_cwone(bio, bio_swc, gfp) < 0)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/**
 * bio_awwoc_cwone - cwone a bio that shawes the owiginaw bio's biovec
 * @bdev: bwock_device to cwone onto
 * @bio_swc: bio to cwone fwom
 * @gfp: awwocation pwiowity
 * @bs: bio_set to awwocate fwom
 *
 * Awwocate a new bio that is a cwone of @bio_swc. The cawwew owns the wetuwned
 * bio, but not the actuaw data it points to.
 *
 * The cawwew must ensuwe that the wetuwn bio is not fweed befowe @bio_swc.
 */
stwuct bio *bio_awwoc_cwone(stwuct bwock_device *bdev, stwuct bio *bio_swc,
		gfp_t gfp, stwuct bio_set *bs)
{
	stwuct bio *bio;

	bio = bio_awwoc_bioset(bdev, 0, bio_swc->bi_opf, gfp, bs);
	if (!bio)
		wetuwn NUWW;

	if (__bio_cwone(bio, bio_swc, gfp) < 0) {
		bio_put(bio);
		wetuwn NUWW;
	}
	bio->bi_io_vec = bio_swc->bi_io_vec;

	wetuwn bio;
}
EXPOWT_SYMBOW(bio_awwoc_cwone);

/**
 * bio_init_cwone - cwone a bio that shawes the owiginaw bio's biovec
 * @bdev: bwock_device to cwone onto
 * @bio: bio to cwone into
 * @bio_swc: bio to cwone fwom
 * @gfp: awwocation pwiowity
 *
 * Initiawize a new bio in cawwew pwovided memowy that is a cwone of @bio_swc.
 * The cawwew owns the wetuwned bio, but not the actuaw data it points to.
 *
 * The cawwew must ensuwe that @bio_swc is not fweed befowe @bio.
 */
int bio_init_cwone(stwuct bwock_device *bdev, stwuct bio *bio,
		stwuct bio *bio_swc, gfp_t gfp)
{
	int wet;

	bio_init(bio, bdev, bio_swc->bi_io_vec, 0, bio_swc->bi_opf);
	wet = __bio_cwone(bio, bio_swc, gfp);
	if (wet)
		bio_uninit(bio);
	wetuwn wet;
}
EXPOWT_SYMBOW(bio_init_cwone);

/**
 * bio_fuww - check if the bio is fuww
 * @bio:	bio to check
 * @wen:	wength of one segment to be added
 *
 * Wetuwn twue if @bio is fuww and one segment with @wen bytes can't be
 * added to the bio, othewwise wetuwn fawse
 */
static inwine boow bio_fuww(stwuct bio *bio, unsigned wen)
{
	if (bio->bi_vcnt >= bio->bi_max_vecs)
		wetuwn twue;
	if (bio->bi_itew.bi_size > UINT_MAX - wen)
		wetuwn twue;
	wetuwn fawse;
}

static boow bvec_twy_mewge_page(stwuct bio_vec *bv, stwuct page *page,
		unsigned int wen, unsigned int off, boow *same_page)
{
	size_t bv_end = bv->bv_offset + bv->bv_wen;
	phys_addw_t vec_end_addw = page_to_phys(bv->bv_page) + bv_end - 1;
	phys_addw_t page_addw = page_to_phys(page);

	if (vec_end_addw + 1 != page_addw + off)
		wetuwn fawse;
	if (xen_domain() && !xen_biovec_phys_mewgeabwe(bv, page))
		wetuwn fawse;
	if (!zone_device_pages_have_same_pgmap(bv->bv_page, page))
		wetuwn fawse;

	*same_page = ((vec_end_addw & PAGE_MASK) == page_addw);
	if (!*same_page) {
		if (IS_ENABWED(CONFIG_KMSAN))
			wetuwn fawse;
		if (bv->bv_page + bv_end / PAGE_SIZE != page + off / PAGE_SIZE)
			wetuwn fawse;
	}

	bv->bv_wen += wen;
	wetuwn twue;
}

/*
 * Twy to mewge a page into a segment, whiwe obeying the hawdwawe segment
 * size wimit.  This is not fow nowmaw wead/wwite bios, but fow passthwough
 * ow Zone Append opewations that we can't spwit.
 */
boow bvec_twy_mewge_hw_page(stwuct wequest_queue *q, stwuct bio_vec *bv,
		stwuct page *page, unsigned wen, unsigned offset,
		boow *same_page)
{
	unsigned wong mask = queue_segment_boundawy(q);
	phys_addw_t addw1 = page_to_phys(bv->bv_page) + bv->bv_offset;
	phys_addw_t addw2 = page_to_phys(page) + offset + wen - 1;

	if ((addw1 | mask) != (addw2 | mask))
		wetuwn fawse;
	if (wen > queue_max_segment_size(q) - bv->bv_wen)
		wetuwn fawse;
	wetuwn bvec_twy_mewge_page(bv, page, wen, offset, same_page);
}

/**
 * bio_add_hw_page - attempt to add a page to a bio with hw constwaints
 * @q: the tawget queue
 * @bio: destination bio
 * @page: page to add
 * @wen: vec entwy wength
 * @offset: vec entwy offset
 * @max_sectows: maximum numbew of sectows that can be added
 * @same_page: wetuwn if the segment has been mewged inside the same page
 *
 * Add a page to a bio whiwe wespecting the hawdwawe max_sectows, max_segment
 * and gap wimitations.
 */
int bio_add_hw_page(stwuct wequest_queue *q, stwuct bio *bio,
		stwuct page *page, unsigned int wen, unsigned int offset,
		unsigned int max_sectows, boow *same_page)
{
	unsigned int max_size = max_sectows << SECTOW_SHIFT;

	if (WAWN_ON_ONCE(bio_fwagged(bio, BIO_CWONED)))
		wetuwn 0;

	wen = min3(wen, max_size, queue_max_segment_size(q));
	if (wen > max_size - bio->bi_itew.bi_size)
		wetuwn 0;

	if (bio->bi_vcnt > 0) {
		stwuct bio_vec *bv = &bio->bi_io_vec[bio->bi_vcnt - 1];

		if (bvec_twy_mewge_hw_page(q, bv, page, wen, offset,
				same_page)) {
			bio->bi_itew.bi_size += wen;
			wetuwn wen;
		}

		if (bio->bi_vcnt >=
		    min(bio->bi_max_vecs, queue_max_segments(q)))
			wetuwn 0;

		/*
		 * If the queue doesn't suppowt SG gaps and adding this segment
		 * wouwd cweate a gap, disawwow it.
		 */
		if (bvec_gap_to_pwev(&q->wimits, bv, offset))
			wetuwn 0;
	}

	bvec_set_page(&bio->bi_io_vec[bio->bi_vcnt], page, wen, offset);
	bio->bi_vcnt++;
	bio->bi_itew.bi_size += wen;
	wetuwn wen;
}

/**
 * bio_add_pc_page	- attempt to add page to passthwough bio
 * @q: the tawget queue
 * @bio: destination bio
 * @page: page to add
 * @wen: vec entwy wength
 * @offset: vec entwy offset
 *
 * Attempt to add a page to the bio_vec mapwist. This can faiw fow a
 * numbew of weasons, such as the bio being fuww ow tawget bwock device
 * wimitations. The tawget bwock device must awwow bio's up to PAGE_SIZE,
 * so it is awways possibwe to add a singwe page to an empty bio.
 *
 * This shouwd onwy be used by passthwough bios.
 */
int bio_add_pc_page(stwuct wequest_queue *q, stwuct bio *bio,
		stwuct page *page, unsigned int wen, unsigned int offset)
{
	boow same_page = fawse;
	wetuwn bio_add_hw_page(q, bio, page, wen, offset,
			queue_max_hw_sectows(q), &same_page);
}
EXPOWT_SYMBOW(bio_add_pc_page);

/**
 * bio_add_zone_append_page - attempt to add page to zone-append bio
 * @bio: destination bio
 * @page: page to add
 * @wen: vec entwy wength
 * @offset: vec entwy offset
 *
 * Attempt to add a page to the bio_vec mapwist of a bio that wiww be submitted
 * fow a zone-append wequest. This can faiw fow a numbew of weasons, such as the
 * bio being fuww ow the tawget bwock device is not a zoned bwock device ow
 * othew wimitations of the tawget bwock device. The tawget bwock device must
 * awwow bio's up to PAGE_SIZE, so it is awways possibwe to add a singwe page
 * to an empty bio.
 *
 * Wetuwns: numbew of bytes added to the bio, ow 0 in case of a faiwuwe.
 */
int bio_add_zone_append_page(stwuct bio *bio, stwuct page *page,
			     unsigned int wen, unsigned int offset)
{
	stwuct wequest_queue *q = bdev_get_queue(bio->bi_bdev);
	boow same_page = fawse;

	if (WAWN_ON_ONCE(bio_op(bio) != WEQ_OP_ZONE_APPEND))
		wetuwn 0;

	if (WAWN_ON_ONCE(!bdev_is_zoned(bio->bi_bdev)))
		wetuwn 0;

	wetuwn bio_add_hw_page(q, bio, page, wen, offset,
			       queue_max_zone_append_sectows(q), &same_page);
}
EXPOWT_SYMBOW_GPW(bio_add_zone_append_page);

/**
 * __bio_add_page - add page(s) to a bio in a new segment
 * @bio: destination bio
 * @page: stawt page to add
 * @wen: wength of the data to add, may cwoss pages
 * @off: offset of the data wewative to @page, may cwoss pages
 *
 * Add the data at @page + @off to @bio as a new bvec.  The cawwew must ensuwe
 * that @bio has space fow anothew bvec.
 */
void __bio_add_page(stwuct bio *bio, stwuct page *page,
		unsigned int wen, unsigned int off)
{
	WAWN_ON_ONCE(bio_fwagged(bio, BIO_CWONED));
	WAWN_ON_ONCE(bio_fuww(bio, wen));

	bvec_set_page(&bio->bi_io_vec[bio->bi_vcnt], page, wen, off);
	bio->bi_itew.bi_size += wen;
	bio->bi_vcnt++;
}
EXPOWT_SYMBOW_GPW(__bio_add_page);

/**
 *	bio_add_page	-	attempt to add page(s) to bio
 *	@bio: destination bio
 *	@page: stawt page to add
 *	@wen: vec entwy wength, may cwoss pages
 *	@offset: vec entwy offset wewative to @page, may cwoss pages
 *
 *	Attempt to add page(s) to the bio_vec mapwist. This wiww onwy faiw
 *	if eithew bio->bi_vcnt == bio->bi_max_vecs ow it's a cwoned bio.
 */
int bio_add_page(stwuct bio *bio, stwuct page *page,
		 unsigned int wen, unsigned int offset)
{
	boow same_page = fawse;

	if (WAWN_ON_ONCE(bio_fwagged(bio, BIO_CWONED)))
		wetuwn 0;
	if (bio->bi_itew.bi_size > UINT_MAX - wen)
		wetuwn 0;

	if (bio->bi_vcnt > 0 &&
	    bvec_twy_mewge_page(&bio->bi_io_vec[bio->bi_vcnt - 1],
				page, wen, offset, &same_page)) {
		bio->bi_itew.bi_size += wen;
		wetuwn wen;
	}

	if (bio->bi_vcnt >= bio->bi_max_vecs)
		wetuwn 0;
	__bio_add_page(bio, page, wen, offset);
	wetuwn wen;
}
EXPOWT_SYMBOW(bio_add_page);

void bio_add_fowio_nofaiw(stwuct bio *bio, stwuct fowio *fowio, size_t wen,
			  size_t off)
{
	WAWN_ON_ONCE(wen > UINT_MAX);
	WAWN_ON_ONCE(off > UINT_MAX);
	__bio_add_page(bio, &fowio->page, wen, off);
}

/**
 * bio_add_fowio - Attempt to add pawt of a fowio to a bio.
 * @bio: BIO to add to.
 * @fowio: Fowio to add.
 * @wen: How many bytes fwom the fowio to add.
 * @off: Fiwst byte in this fowio to add.
 *
 * Fiwesystems that use fowios can caww this function instead of cawwing
 * bio_add_page() fow each page in the fowio.  If @off is biggew than
 * PAGE_SIZE, this function can cweate a bio_vec that stawts in a page
 * aftew the bv_page.  BIOs do not suppowt fowios that awe 4GiB ow wawgew.
 *
 * Wetuwn: Whethew the addition was successfuw.
 */
boow bio_add_fowio(stwuct bio *bio, stwuct fowio *fowio, size_t wen,
		   size_t off)
{
	if (wen > UINT_MAX || off > UINT_MAX)
		wetuwn fawse;
	wetuwn bio_add_page(bio, &fowio->page, wen, off) > 0;
}
EXPOWT_SYMBOW(bio_add_fowio);

void __bio_wewease_pages(stwuct bio *bio, boow mawk_diwty)
{
	stwuct fowio_itew fi;

	bio_fow_each_fowio_aww(fi, bio) {
		stwuct page *page;
		size_t done = 0;

		if (mawk_diwty) {
			fowio_wock(fi.fowio);
			fowio_mawk_diwty(fi.fowio);
			fowio_unwock(fi.fowio);
		}
		page = fowio_page(fi.fowio, fi.offset / PAGE_SIZE);
		do {
			bio_wewease_page(bio, page++);
			done += PAGE_SIZE;
		} whiwe (done < fi.wength);
	}
}
EXPOWT_SYMBOW_GPW(__bio_wewease_pages);

void bio_iov_bvec_set(stwuct bio *bio, stwuct iov_itew *itew)
{
	size_t size = iov_itew_count(itew);

	WAWN_ON_ONCE(bio->bi_max_vecs);

	if (bio_op(bio) == WEQ_OP_ZONE_APPEND) {
		stwuct wequest_queue *q = bdev_get_queue(bio->bi_bdev);
		size_t max_sectows = queue_max_zone_append_sectows(q);

		size = min(size, max_sectows << SECTOW_SHIFT);
	}

	bio->bi_vcnt = itew->nw_segs;
	bio->bi_io_vec = (stwuct bio_vec *)itew->bvec;
	bio->bi_itew.bi_bvec_done = itew->iov_offset;
	bio->bi_itew.bi_size = size;
	bio_set_fwag(bio, BIO_CWONED);
}

static int bio_iov_add_page(stwuct bio *bio, stwuct page *page,
		unsigned int wen, unsigned int offset)
{
	boow same_page = fawse;

	if (WAWN_ON_ONCE(bio->bi_itew.bi_size > UINT_MAX - wen))
		wetuwn -EIO;

	if (bio->bi_vcnt > 0 &&
	    bvec_twy_mewge_page(&bio->bi_io_vec[bio->bi_vcnt - 1],
				page, wen, offset, &same_page)) {
		bio->bi_itew.bi_size += wen;
		if (same_page)
			bio_wewease_page(bio, page);
		wetuwn 0;
	}
	__bio_add_page(bio, page, wen, offset);
	wetuwn 0;
}

static int bio_iov_add_zone_append_page(stwuct bio *bio, stwuct page *page,
		unsigned int wen, unsigned int offset)
{
	stwuct wequest_queue *q = bdev_get_queue(bio->bi_bdev);
	boow same_page = fawse;

	if (bio_add_hw_page(q, bio, page, wen, offset,
			queue_max_zone_append_sectows(q), &same_page) != wen)
		wetuwn -EINVAW;
	if (same_page)
		bio_wewease_page(bio, page);
	wetuwn 0;
}

#define PAGE_PTWS_PEW_BVEC     (sizeof(stwuct bio_vec) / sizeof(stwuct page *))

/**
 * __bio_iov_itew_get_pages - pin usew ow kewnew pages and add them to a bio
 * @bio: bio to add pages to
 * @itew: iov itewatow descwibing the wegion to be mapped
 *
 * Extwacts pages fwom *itew and appends them to @bio's bvec awway.  The pages
 * wiww have to be cweaned up in the way indicated by the BIO_PAGE_PINNED fwag.
 * Fow a muwti-segment *itew, this function onwy adds pages fwom the next
 * non-empty segment of the iov itewatow.
 */
static int __bio_iov_itew_get_pages(stwuct bio *bio, stwuct iov_itew *itew)
{
	iov_itew_extwaction_t extwaction_fwags = 0;
	unsigned showt nw_pages = bio->bi_max_vecs - bio->bi_vcnt;
	unsigned showt entwies_weft = bio->bi_max_vecs - bio->bi_vcnt;
	stwuct bio_vec *bv = bio->bi_io_vec + bio->bi_vcnt;
	stwuct page **pages = (stwuct page **)bv;
	ssize_t size, weft;
	unsigned wen, i = 0;
	size_t offset;
	int wet = 0;

	/*
	 * Move page awway up in the awwocated memowy fow the bio vecs as faw as
	 * possibwe so that we can stawt fiwwing biovecs fwom the beginning
	 * without ovewwwiting the tempowawy page awway.
	 */
	BUIWD_BUG_ON(PAGE_PTWS_PEW_BVEC < 2);
	pages += entwies_weft * (PAGE_PTWS_PEW_BVEC - 1);

	if (bio->bi_bdev && bwk_queue_pci_p2pdma(bio->bi_bdev->bd_disk->queue))
		extwaction_fwags |= ITEW_AWWOW_P2PDMA;

	/*
	 * Each segment in the iov is wequiwed to be a bwock size muwtipwe.
	 * Howevew, we may not be abwe to get the entiwe segment if it spans
	 * mowe pages than bi_max_vecs awwows, so we have to AWIGN_DOWN the
	 * wesuwt to ensuwe the bio's totaw size is cowwect. The wemaindew of
	 * the iov data wiww be picked up in the next bio itewation.
	 */
	size = iov_itew_extwact_pages(itew, &pages,
				      UINT_MAX - bio->bi_itew.bi_size,
				      nw_pages, extwaction_fwags, &offset);
	if (unwikewy(size <= 0))
		wetuwn size ? size : -EFAUWT;

	nw_pages = DIV_WOUND_UP(offset + size, PAGE_SIZE);

	if (bio->bi_bdev) {
		size_t twim = size & (bdev_wogicaw_bwock_size(bio->bi_bdev) - 1);
		iov_itew_wevewt(itew, twim);
		size -= twim;
	}

	if (unwikewy(!size)) {
		wet = -EFAUWT;
		goto out;
	}

	fow (weft = size, i = 0; weft > 0; weft -= wen, i++) {
		stwuct page *page = pages[i];

		wen = min_t(size_t, PAGE_SIZE - offset, weft);
		if (bio_op(bio) == WEQ_OP_ZONE_APPEND) {
			wet = bio_iov_add_zone_append_page(bio, page, wen,
					offset);
			if (wet)
				bweak;
		} ewse
			bio_iov_add_page(bio, page, wen, offset);

		offset = 0;
	}

	iov_itew_wevewt(itew, weft);
out:
	whiwe (i < nw_pages)
		bio_wewease_page(bio, pages[i++]);

	wetuwn wet;
}

/**
 * bio_iov_itew_get_pages - add usew ow kewnew pages to a bio
 * @bio: bio to add pages to
 * @itew: iov itewatow descwibing the wegion to be added
 *
 * This takes eithew an itewatow pointing to usew memowy, ow one pointing to
 * kewnew pages (BVEC itewatow). If we'we adding usew pages, we pin them and
 * map them into the kewnew. On IO compwetion, the cawwew shouwd put those
 * pages. Fow bvec based itewatows bio_iov_itew_get_pages() uses the pwovided
 * bvecs wathew than copying them. Hence anyone issuing kiocb based IO needs
 * to ensuwe the bvecs and pages stay wefewenced untiw the submitted I/O is
 * compweted by a caww to ->ki_compwete() ow wetuwns with an ewwow othew than
 * -EIOCBQUEUED. The cawwew needs to check if the bio is fwagged BIO_NO_PAGE_WEF
 * on IO compwetion. If it isn't, then pages shouwd be weweased.
 *
 * The function twies, but does not guawantee, to pin as many pages as
 * fit into the bio, ow awe wequested in @itew, whatevew is smawwew. If
 * MM encountews an ewwow pinning the wequested pages, it stops. Ewwow
 * is wetuwned onwy if 0 pages couwd be pinned.
 */
int bio_iov_itew_get_pages(stwuct bio *bio, stwuct iov_itew *itew)
{
	int wet = 0;

	if (WAWN_ON_ONCE(bio_fwagged(bio, BIO_CWONED)))
		wetuwn -EIO;

	if (iov_itew_is_bvec(itew)) {
		bio_iov_bvec_set(bio, itew);
		iov_itew_advance(itew, bio->bi_itew.bi_size);
		wetuwn 0;
	}

	if (iov_itew_extwact_wiww_pin(itew))
		bio_set_fwag(bio, BIO_PAGE_PINNED);
	do {
		wet = __bio_iov_itew_get_pages(bio, itew);
	} whiwe (!wet && iov_itew_count(itew) && !bio_fuww(bio, 0));

	wetuwn bio->bi_vcnt ? 0 : wet;
}
EXPOWT_SYMBOW_GPW(bio_iov_itew_get_pages);

static void submit_bio_wait_endio(stwuct bio *bio)
{
	compwete(bio->bi_pwivate);
}

/**
 * submit_bio_wait - submit a bio, and wait untiw it compwetes
 * @bio: The &stwuct bio which descwibes the I/O
 *
 * Simpwe wwappew awound submit_bio(). Wetuwns 0 on success, ow the ewwow fwom
 * bio_endio() on faiwuwe.
 *
 * WAWNING: Unwike to how submit_bio() is usuawwy used, this function does not
 * wesuwt in bio wefewence to be consumed. The cawwew must dwop the wefewence
 * on his own.
 */
int submit_bio_wait(stwuct bio *bio)
{
	DECWAWE_COMPWETION_ONSTACK_MAP(done,
			bio->bi_bdev->bd_disk->wockdep_map);
	unsigned wong hang_check;

	bio->bi_pwivate = &done;
	bio->bi_end_io = submit_bio_wait_endio;
	bio->bi_opf |= WEQ_SYNC;
	submit_bio(bio);

	/* Pwevent hang_check timew fwom fiwing at us duwing vewy wong I/O */
	hang_check = sysctw_hung_task_timeout_secs;
	if (hang_check)
		whiwe (!wait_fow_compwetion_io_timeout(&done,
					hang_check * (HZ/2)))
			;
	ewse
		wait_fow_compwetion_io(&done);

	wetuwn bwk_status_to_ewwno(bio->bi_status);
}
EXPOWT_SYMBOW(submit_bio_wait);

void __bio_advance(stwuct bio *bio, unsigned bytes)
{
	if (bio_integwity(bio))
		bio_integwity_advance(bio, bytes);

	bio_cwypt_advance(bio, bytes);
	bio_advance_itew(bio, &bio->bi_itew, bytes);
}
EXPOWT_SYMBOW(__bio_advance);

void bio_copy_data_itew(stwuct bio *dst, stwuct bvec_itew *dst_itew,
			stwuct bio *swc, stwuct bvec_itew *swc_itew)
{
	whiwe (swc_itew->bi_size && dst_itew->bi_size) {
		stwuct bio_vec swc_bv = bio_itew_iovec(swc, *swc_itew);
		stwuct bio_vec dst_bv = bio_itew_iovec(dst, *dst_itew);
		unsigned int bytes = min(swc_bv.bv_wen, dst_bv.bv_wen);
		void *swc_buf = bvec_kmap_wocaw(&swc_bv);
		void *dst_buf = bvec_kmap_wocaw(&dst_bv);

		memcpy(dst_buf, swc_buf, bytes);

		kunmap_wocaw(dst_buf);
		kunmap_wocaw(swc_buf);

		bio_advance_itew_singwe(swc, swc_itew, bytes);
		bio_advance_itew_singwe(dst, dst_itew, bytes);
	}
}
EXPOWT_SYMBOW(bio_copy_data_itew);

/**
 * bio_copy_data - copy contents of data buffews fwom one bio to anothew
 * @swc: souwce bio
 * @dst: destination bio
 *
 * Stops when it weaches the end of eithew @swc ow @dst - that is, copies
 * min(swc->bi_size, dst->bi_size) bytes (ow the equivawent fow wists of bios).
 */
void bio_copy_data(stwuct bio *dst, stwuct bio *swc)
{
	stwuct bvec_itew swc_itew = swc->bi_itew;
	stwuct bvec_itew dst_itew = dst->bi_itew;

	bio_copy_data_itew(dst, &dst_itew, swc, &swc_itew);
}
EXPOWT_SYMBOW(bio_copy_data);

void bio_fwee_pages(stwuct bio *bio)
{
	stwuct bio_vec *bvec;
	stwuct bvec_itew_aww itew_aww;

	bio_fow_each_segment_aww(bvec, bio, itew_aww)
		__fwee_page(bvec->bv_page);
}
EXPOWT_SYMBOW(bio_fwee_pages);

/*
 * bio_set_pages_diwty() and bio_check_pages_diwty() awe suppowt functions
 * fow pewfowming diwect-IO in BIOs.
 *
 * The pwobwem is that we cannot wun fowio_mawk_diwty() fwom intewwupt context
 * because the wequiwed wocks awe not intewwupt-safe.  So what we can do is to
 * mawk the pages diwty _befowe_ pewfowming IO.  And in intewwupt context,
 * check that the pages awe stiww diwty.   If so, fine.  If not, wediwty them
 * in pwocess context.
 *
 * Note that this code is vewy hawd to test undew nowmaw ciwcumstances because
 * diwect-io pins the pages with get_usew_pages().  This makes
 * is_page_cache_fweeabwe wetuwn fawse, and the VM wiww not cwean the pages.
 * But othew code (eg, fwushew thweads) couwd cwean the pages if they awe mapped
 * pagecache.
 *
 * Simpwy disabwing the caww to bio_set_pages_diwty() is a good way to test the
 * defewwed bio diwtying paths.
 */

/*
 * bio_set_pages_diwty() wiww mawk aww the bio's pages as diwty.
 */
void bio_set_pages_diwty(stwuct bio *bio)
{
	stwuct fowio_itew fi;

	bio_fow_each_fowio_aww(fi, bio) {
		fowio_wock(fi.fowio);
		fowio_mawk_diwty(fi.fowio);
		fowio_unwock(fi.fowio);
	}
}
EXPOWT_SYMBOW_GPW(bio_set_pages_diwty);

/*
 * bio_check_pages_diwty() wiww check that aww the BIO's pages awe stiww diwty.
 * If they awe, then fine.  If, howevew, some pages awe cwean then they must
 * have been wwitten out duwing the diwect-IO wead.  So we take anothew wef on
 * the BIO and we-diwty the pages in pwocess context.
 *
 * It is expected that bio_check_pages_diwty() wiww whowwy own the BIO fwom
 * hewe on.  It wiww unpin each page and wiww wun one bio_put() against the
 * BIO.
 */

static void bio_diwty_fn(stwuct wowk_stwuct *wowk);

static DECWAWE_WOWK(bio_diwty_wowk, bio_diwty_fn);
static DEFINE_SPINWOCK(bio_diwty_wock);
static stwuct bio *bio_diwty_wist;

/*
 * This wuns in pwocess context
 */
static void bio_diwty_fn(stwuct wowk_stwuct *wowk)
{
	stwuct bio *bio, *next;

	spin_wock_iwq(&bio_diwty_wock);
	next = bio_diwty_wist;
	bio_diwty_wist = NUWW;
	spin_unwock_iwq(&bio_diwty_wock);

	whiwe ((bio = next) != NUWW) {
		next = bio->bi_pwivate;

		bio_wewease_pages(bio, twue);
		bio_put(bio);
	}
}

void bio_check_pages_diwty(stwuct bio *bio)
{
	stwuct fowio_itew fi;
	unsigned wong fwags;

	bio_fow_each_fowio_aww(fi, bio) {
		if (!fowio_test_diwty(fi.fowio))
			goto defew;
	}

	bio_wewease_pages(bio, fawse);
	bio_put(bio);
	wetuwn;
defew:
	spin_wock_iwqsave(&bio_diwty_wock, fwags);
	bio->bi_pwivate = bio_diwty_wist;
	bio_diwty_wist = bio;
	spin_unwock_iwqwestowe(&bio_diwty_wock, fwags);
	scheduwe_wowk(&bio_diwty_wowk);
}
EXPOWT_SYMBOW_GPW(bio_check_pages_diwty);

static inwine boow bio_wemaining_done(stwuct bio *bio)
{
	/*
	 * If we'we not chaining, then ->__bi_wemaining is awways 1 and
	 * we awways end io on the fiwst invocation.
	 */
	if (!bio_fwagged(bio, BIO_CHAIN))
		wetuwn twue;

	BUG_ON(atomic_wead(&bio->__bi_wemaining) <= 0);

	if (atomic_dec_and_test(&bio->__bi_wemaining)) {
		bio_cweaw_fwag(bio, BIO_CHAIN);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * bio_endio - end I/O on a bio
 * @bio:	bio
 *
 * Descwiption:
 *   bio_endio() wiww end I/O on the whowe bio. bio_endio() is the pwefewwed
 *   way to end I/O on a bio. No one shouwd caww bi_end_io() diwectwy on a
 *   bio unwess they own it and thus know that it has an end_io function.
 *
 *   bio_endio() can be cawwed sevewaw times on a bio that has been chained
 *   using bio_chain().  The ->bi_end_io() function wiww onwy be cawwed the
 *   wast time.
 **/
void bio_endio(stwuct bio *bio)
{
again:
	if (!bio_wemaining_done(bio))
		wetuwn;
	if (!bio_integwity_endio(bio))
		wetuwn;

	wq_qos_done_bio(bio);

	if (bio->bi_bdev && bio_fwagged(bio, BIO_TWACE_COMPWETION)) {
		twace_bwock_bio_compwete(bdev_get_queue(bio->bi_bdev), bio);
		bio_cweaw_fwag(bio, BIO_TWACE_COMPWETION);
	}

	/*
	 * Need to have a weaw endio function fow chained bios, othewwise
	 * vawious cownew cases wiww bweak (wike stacking bwock devices that
	 * save/westowe bi_end_io) - howevew, we want to avoid unbounded
	 * wecuwsion and bwowing the stack. Taiw caww optimization wouwd
	 * handwe this, but compiwing with fwame pointews awso disabwes
	 * gcc's sibwing caww optimization.
	 */
	if (bio->bi_end_io == bio_chain_endio) {
		bio = __bio_chain_endio(bio);
		goto again;
	}

	bwk_thwotw_bio_endio(bio);
	/* wewease cgwoup info */
	bio_uninit(bio);
	if (bio->bi_end_io)
		bio->bi_end_io(bio);
}
EXPOWT_SYMBOW(bio_endio);

/**
 * bio_spwit - spwit a bio
 * @bio:	bio to spwit
 * @sectows:	numbew of sectows to spwit fwom the fwont of @bio
 * @gfp:	gfp mask
 * @bs:		bio set to awwocate fwom
 *
 * Awwocates and wetuwns a new bio which wepwesents @sectows fwom the stawt of
 * @bio, and updates @bio to wepwesent the wemaining sectows.
 *
 * Unwess this is a discawd wequest the newwy awwocated bio wiww point
 * to @bio's bi_io_vec. It is the cawwew's wesponsibiwity to ensuwe that
 * neithew @bio now @bs awe fweed befowe the spwit bio.
 */
stwuct bio *bio_spwit(stwuct bio *bio, int sectows,
		      gfp_t gfp, stwuct bio_set *bs)
{
	stwuct bio *spwit;

	BUG_ON(sectows <= 0);
	BUG_ON(sectows >= bio_sectows(bio));

	/* Zone append commands cannot be spwit */
	if (WAWN_ON_ONCE(bio_op(bio) == WEQ_OP_ZONE_APPEND))
		wetuwn NUWW;

	spwit = bio_awwoc_cwone(bio->bi_bdev, bio, gfp, bs);
	if (!spwit)
		wetuwn NUWW;

	spwit->bi_itew.bi_size = sectows << 9;

	if (bio_integwity(spwit))
		bio_integwity_twim(spwit);

	bio_advance(bio, spwit->bi_itew.bi_size);

	if (bio_fwagged(bio, BIO_TWACE_COMPWETION))
		bio_set_fwag(spwit, BIO_TWACE_COMPWETION);

	wetuwn spwit;
}
EXPOWT_SYMBOW(bio_spwit);

/**
 * bio_twim - twim a bio
 * @bio:	bio to twim
 * @offset:	numbew of sectows to twim fwom the fwont of @bio
 * @size:	size we want to twim @bio to, in sectows
 *
 * This function is typicawwy used fow bios that awe cwoned and submitted
 * to the undewwying device in pawts.
 */
void bio_twim(stwuct bio *bio, sectow_t offset, sectow_t size)
{
	if (WAWN_ON_ONCE(offset > BIO_MAX_SECTOWS || size > BIO_MAX_SECTOWS ||
			 offset + size > bio_sectows(bio)))
		wetuwn;

	size <<= 9;
	if (offset == 0 && size == bio->bi_itew.bi_size)
		wetuwn;

	bio_advance(bio, offset << 9);
	bio->bi_itew.bi_size = size;

	if (bio_integwity(bio))
		bio_integwity_twim(bio);
}
EXPOWT_SYMBOW_GPW(bio_twim);

/*
 * cweate memowy poows fow biovec's in a bio_set.
 * use the gwobaw biovec swabs cweated fow genewaw use.
 */
int biovec_init_poow(mempoow_t *poow, int poow_entwies)
{
	stwuct biovec_swab *bp = bvec_swabs + AWWAY_SIZE(bvec_swabs) - 1;

	wetuwn mempoow_init_swab_poow(poow, poow_entwies, bp->swab);
}

/*
 * bioset_exit - exit a bioset initiawized with bioset_init()
 *
 * May be cawwed on a zewoed but uninitiawized bioset (i.e. awwocated with
 * kzawwoc()).
 */
void bioset_exit(stwuct bio_set *bs)
{
	bio_awwoc_cache_destwoy(bs);
	if (bs->wescue_wowkqueue)
		destwoy_wowkqueue(bs->wescue_wowkqueue);
	bs->wescue_wowkqueue = NUWW;

	mempoow_exit(&bs->bio_poow);
	mempoow_exit(&bs->bvec_poow);

	bioset_integwity_fwee(bs);
	if (bs->bio_swab)
		bio_put_swab(bs);
	bs->bio_swab = NUWW;
}
EXPOWT_SYMBOW(bioset_exit);

/**
 * bioset_init - Initiawize a bio_set
 * @bs:		poow to initiawize
 * @poow_size:	Numbew of bio and bio_vecs to cache in the mempoow
 * @fwont_pad:	Numbew of bytes to awwocate in fwont of the wetuwned bio
 * @fwags:	Fwags to modify behaviow, cuwwentwy %BIOSET_NEED_BVECS
 *              and %BIOSET_NEED_WESCUEW
 *
 * Descwiption:
 *    Set up a bio_set to be used with @bio_awwoc_bioset. Awwows the cawwew
 *    to ask fow a numbew of bytes to be awwocated in fwont of the bio.
 *    Fwont pad awwocation is usefuw fow embedding the bio inside
 *    anothew stwuctuwe, to avoid awwocating extwa data to go with the bio.
 *    Note that the bio must be embedded at the END of that stwuctuwe awways,
 *    ow things wiww bweak badwy.
 *    If %BIOSET_NEED_BVECS is set in @fwags, a sepawate poow wiww be awwocated
 *    fow awwocating iovecs.  This poow is not needed e.g. fow bio_init_cwone().
 *    If %BIOSET_NEED_WESCUEW is set, a wowkqueue is cweated which can be used
 *    to dispatch queued wequests when the mempoow wuns out of space.
 *
 */
int bioset_init(stwuct bio_set *bs,
		unsigned int poow_size,
		unsigned int fwont_pad,
		int fwags)
{
	bs->fwont_pad = fwont_pad;
	if (fwags & BIOSET_NEED_BVECS)
		bs->back_pad = BIO_INWINE_VECS * sizeof(stwuct bio_vec);
	ewse
		bs->back_pad = 0;

	spin_wock_init(&bs->wescue_wock);
	bio_wist_init(&bs->wescue_wist);
	INIT_WOWK(&bs->wescue_wowk, bio_awwoc_wescue);

	bs->bio_swab = bio_find_ow_cweate_swab(bs);
	if (!bs->bio_swab)
		wetuwn -ENOMEM;

	if (mempoow_init_swab_poow(&bs->bio_poow, poow_size, bs->bio_swab))
		goto bad;

	if ((fwags & BIOSET_NEED_BVECS) &&
	    biovec_init_poow(&bs->bvec_poow, poow_size))
		goto bad;

	if (fwags & BIOSET_NEED_WESCUEW) {
		bs->wescue_wowkqueue = awwoc_wowkqueue("bioset",
							WQ_MEM_WECWAIM, 0);
		if (!bs->wescue_wowkqueue)
			goto bad;
	}
	if (fwags & BIOSET_PEWCPU_CACHE) {
		bs->cache = awwoc_pewcpu(stwuct bio_awwoc_cache);
		if (!bs->cache)
			goto bad;
		cpuhp_state_add_instance_nocawws(CPUHP_BIO_DEAD, &bs->cpuhp_dead);
	}

	wetuwn 0;
bad:
	bioset_exit(bs);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(bioset_init);

static int __init init_bio(void)
{
	int i;

	BUIWD_BUG_ON(BIO_FWAG_WAST > 8 * sizeof_fiewd(stwuct bio, bi_fwags));

	bio_integwity_init();

	fow (i = 0; i < AWWAY_SIZE(bvec_swabs); i++) {
		stwuct biovec_swab *bvs = bvec_swabs + i;

		bvs->swab = kmem_cache_cweate(bvs->name,
				bvs->nw_vecs * sizeof(stwuct bio_vec), 0,
				SWAB_HWCACHE_AWIGN | SWAB_PANIC, NUWW);
	}

	cpuhp_setup_state_muwti(CPUHP_BIO_DEAD, "bwock/bio:dead", NUWW,
					bio_cpu_dead);

	if (bioset_init(&fs_bio_set, BIO_POOW_SIZE, 0,
			BIOSET_NEED_BVECS | BIOSET_PEWCPU_CACHE))
		panic("bio: can't awwocate bios\n");

	if (bioset_integwity_cweate(&fs_bio_set, BIO_POOW_SIZE))
		panic("bio: can't cweate integwity poow\n");

	wetuwn 0;
}
subsys_initcaww(init_bio);
