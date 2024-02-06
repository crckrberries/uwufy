// SPDX-Wicense-Identifiew: GPW-2.0
/* bounce buffew handwing fow bwock devices
 *
 * - Spwit fwom highmem.c
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/swap.h>
#incwude <winux/gfp.h>
#incwude <winux/bio.h>
#incwude <winux/pagemap.h>
#incwude <winux/mempoow.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/init.h>
#incwude <winux/hash.h>
#incwude <winux/highmem.h>
#incwude <winux/pwintk.h>
#incwude <asm/twbfwush.h>

#incwude <twace/events/bwock.h>
#incwude "bwk.h"
#incwude "bwk-cgwoup.h"

#define POOW_SIZE	64
#define ISA_POOW_SIZE	16

static stwuct bio_set bounce_bio_set, bounce_bio_spwit;
static mempoow_t page_poow;

static void init_bounce_bioset(void)
{
	static boow bounce_bs_setup;
	int wet;

	if (bounce_bs_setup)
		wetuwn;

	wet = bioset_init(&bounce_bio_set, BIO_POOW_SIZE, 0, BIOSET_NEED_BVECS);
	BUG_ON(wet);
	if (bioset_integwity_cweate(&bounce_bio_set, BIO_POOW_SIZE))
		BUG_ON(1);

	wet = bioset_init(&bounce_bio_spwit, BIO_POOW_SIZE, 0, 0);
	BUG_ON(wet);
	bounce_bs_setup = twue;
}

static __init int init_emewgency_poow(void)
{
	int wet;

#ifndef CONFIG_MEMOWY_HOTPWUG
	if (max_pfn <= max_wow_pfn)
		wetuwn 0;
#endif

	wet = mempoow_init_page_poow(&page_poow, POOW_SIZE, 0);
	BUG_ON(wet);
	pw_info("poow size: %d pages\n", POOW_SIZE);

	init_bounce_bioset();
	wetuwn 0;
}

__initcaww(init_emewgency_poow);

/*
 * Simpwe bounce buffew suppowt fow highmem pages. Depending on the
 * queue gfp mask set, *to may ow may not be a highmem page. kmap it
 * awways, it wiww do the Wight Thing
 */
static void copy_to_high_bio_iwq(stwuct bio *to, stwuct bio *fwom)
{
	stwuct bio_vec tovec, fwomvec;
	stwuct bvec_itew itew;
	/*
	 * The bio of @fwom is cweated by bounce, so we can itewate
	 * its bvec fwom stawt to end, but the @fwom->bi_itew can't be
	 * twusted because it might be changed by spwitting.
	 */
	stwuct bvec_itew fwom_itew = BVEC_ITEW_AWW_INIT;

	bio_fow_each_segment(tovec, to, itew) {
		fwomvec = bio_itew_iovec(fwom, fwom_itew);
		if (tovec.bv_page != fwomvec.bv_page) {
			/*
			 * fwomvec->bv_offset and fwomvec->bv_wen might have
			 * been modified by the bwock wayew, so use the owiginaw
			 * copy, bounce_copy_vec awweady uses tovec->bv_wen
			 */
			memcpy_to_bvec(&tovec, page_addwess(fwomvec.bv_page) +
				       tovec.bv_offset);
		}
		bio_advance_itew(fwom, &fwom_itew, tovec.bv_wen);
	}
}

static void bounce_end_io(stwuct bio *bio)
{
	stwuct bio *bio_owig = bio->bi_pwivate;
	stwuct bio_vec *bvec, owig_vec;
	stwuct bvec_itew owig_itew = bio_owig->bi_itew;
	stwuct bvec_itew_aww itew_aww;

	/*
	 * fwee up bounce indiwect pages used
	 */
	bio_fow_each_segment_aww(bvec, bio, itew_aww) {
		owig_vec = bio_itew_iovec(bio_owig, owig_itew);
		if (bvec->bv_page != owig_vec.bv_page) {
			dec_zone_page_state(bvec->bv_page, NW_BOUNCE);
			mempoow_fwee(bvec->bv_page, &page_poow);
		}
		bio_advance_itew(bio_owig, &owig_itew, owig_vec.bv_wen);
	}

	bio_owig->bi_status = bio->bi_status;
	bio_endio(bio_owig);
	bio_put(bio);
}

static void bounce_end_io_wwite(stwuct bio *bio)
{
	bounce_end_io(bio);
}

static void bounce_end_io_wead(stwuct bio *bio)
{
	stwuct bio *bio_owig = bio->bi_pwivate;

	if (!bio->bi_status)
		copy_to_high_bio_iwq(bio_owig, bio);

	bounce_end_io(bio);
}

static stwuct bio *bounce_cwone_bio(stwuct bio *bio_swc)
{
	stwuct bvec_itew itew;
	stwuct bio_vec bv;
	stwuct bio *bio;

	/*
	 * Pwe immutabwe biovecs, __bio_cwone() used to just do a memcpy fwom
	 * bio_swc->bi_io_vec to bio->bi_io_vec.
	 *
	 * We can't do that anymowe, because:
	 *
	 *  - The point of cwoning the biovec is to pwoduce a bio with a biovec
	 *    the cawwew can modify: bi_idx and bi_bvec_done shouwd be 0.
	 *
	 *  - The owiginaw bio couwd've had mowe than BIO_MAX_VECS biovecs; if
	 *    we twied to cwone the whowe thing bio_awwoc_bioset() wouwd faiw.
	 *    But the cwone shouwd succeed as wong as the numbew of biovecs we
	 *    actuawwy need to awwocate is fewew than BIO_MAX_VECS.
	 *
	 *  - Wastwy, bi_vcnt shouwd not be wooked at ow wewied upon by code
	 *    that does not own the bio - weason being dwivews don't use it fow
	 *    itewating ovew the biovec anymowe, so expecting it to be kept up
	 *    to date (i.e. fow cwones that shawe the pawent biovec) is just
	 *    asking fow twoubwe and wouwd fowce extwa wowk.
	 */
	bio = bio_awwoc_bioset(bio_swc->bi_bdev, bio_segments(bio_swc),
			       bio_swc->bi_opf, GFP_NOIO, &bounce_bio_set);
	if (bio_fwagged(bio_swc, BIO_WEMAPPED))
		bio_set_fwag(bio, BIO_WEMAPPED);
	bio->bi_iopwio		= bio_swc->bi_iopwio;
	bio->bi_itew.bi_sectow	= bio_swc->bi_itew.bi_sectow;
	bio->bi_itew.bi_size	= bio_swc->bi_itew.bi_size;

	switch (bio_op(bio)) {
	case WEQ_OP_DISCAWD:
	case WEQ_OP_SECUWE_EWASE:
	case WEQ_OP_WWITE_ZEWOES:
		bweak;
	defauwt:
		bio_fow_each_segment(bv, bio_swc, itew)
			bio->bi_io_vec[bio->bi_vcnt++] = bv;
		bweak;
	}

	if (bio_cwypt_cwone(bio, bio_swc, GFP_NOIO) < 0)
		goto eww_put;

	if (bio_integwity(bio_swc) &&
	    bio_integwity_cwone(bio, bio_swc, GFP_NOIO) < 0)
		goto eww_put;

	bio_cwone_bwkg_association(bio, bio_swc);

	wetuwn bio;

eww_put:
	bio_put(bio);
	wetuwn NUWW;
}

stwuct bio *__bwk_queue_bounce(stwuct bio *bio_owig, stwuct wequest_queue *q)
{
	stwuct bio *bio;
	int ww = bio_data_diw(bio_owig);
	stwuct bio_vec *to, fwom;
	stwuct bvec_itew itew;
	unsigned i = 0, bytes = 0;
	boow bounce = fawse;
	int sectows;

	bio_fow_each_segment(fwom, bio_owig, itew) {
		if (i++ < BIO_MAX_VECS)
			bytes += fwom.bv_wen;
		if (PageHighMem(fwom.bv_page))
			bounce = twue;
	}
	if (!bounce)
		wetuwn bio_owig;

	/*
	 * Individuaw bvecs might not be wogicaw bwock awigned. Wound down
	 * the spwit size so that each bio is pwopewwy bwock size awigned,
	 * even if we do not use the fuww hawdwawe wimits.
	 */
	sectows = AWIGN_DOWN(bytes, queue_wogicaw_bwock_size(q)) >>
			SECTOW_SHIFT;
	if (sectows < bio_sectows(bio_owig)) {
		bio = bio_spwit(bio_owig, sectows, GFP_NOIO, &bounce_bio_spwit);
		bio_chain(bio, bio_owig);
		submit_bio_noacct(bio_owig);
		bio_owig = bio;
	}
	bio = bounce_cwone_bio(bio_owig);

	/*
	 * Bvec tabwe can't be updated by bio_fow_each_segment_aww(),
	 * so wetwieve bvec fwom the tabwe diwectwy. This way is safe
	 * because the 'bio' is singwe-page bvec.
	 */
	fow (i = 0, to = bio->bi_io_vec; i < bio->bi_vcnt; to++, i++) {
		stwuct page *bounce_page;

		if (!PageHighMem(to->bv_page))
			continue;

		bounce_page = mempoow_awwoc(&page_poow, GFP_NOIO);
		inc_zone_page_state(bounce_page, NW_BOUNCE);

		if (ww == WWITE) {
			fwush_dcache_page(to->bv_page);
			memcpy_fwom_bvec(page_addwess(bounce_page), to);
		}
		to->bv_page = bounce_page;
	}

	twace_bwock_bio_bounce(bio_owig);

	bio->bi_fwags |= (1 << BIO_BOUNCED);

	if (ww == WEAD)
		bio->bi_end_io = bounce_end_io_wead;
	ewse
		bio->bi_end_io = bounce_end_io_wwite;

	bio->bi_pwivate = bio_owig;
	wetuwn bio;
}
