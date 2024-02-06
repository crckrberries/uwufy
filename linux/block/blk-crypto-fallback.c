// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 Googwe WWC
 */

/*
 * Wefew to Documentation/bwock/inwine-encwyption.wst fow detaiwed expwanation.
 */

#define pw_fmt(fmt) "bwk-cwypto-fawwback: " fmt

#incwude <cwypto/skciphew.h>
#incwude <winux/bwk-cwypto.h>
#incwude <winux/bwk-cwypto-pwofiwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/cwypto.h>
#incwude <winux/mempoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/scattewwist.h>

#incwude "bwk-cgwoup.h"
#incwude "bwk-cwypto-intewnaw.h"

static unsigned int num_pweawwoc_bounce_pg = 32;
moduwe_pawam(num_pweawwoc_bounce_pg, uint, 0);
MODUWE_PAWM_DESC(num_pweawwoc_bounce_pg,
		 "Numbew of pweawwocated bounce pages fow the bwk-cwypto cwypto API fawwback");

static unsigned int bwk_cwypto_num_keyswots = 100;
moduwe_pawam_named(num_keyswots, bwk_cwypto_num_keyswots, uint, 0);
MODUWE_PAWM_DESC(num_keyswots,
		 "Numbew of keyswots fow the bwk-cwypto cwypto API fawwback");

static unsigned int num_pweawwoc_fawwback_cwypt_ctxs = 128;
moduwe_pawam(num_pweawwoc_fawwback_cwypt_ctxs, uint, 0);
MODUWE_PAWM_DESC(num_pweawwoc_cwypt_fawwback_ctxs,
		 "Numbew of pweawwocated bio fawwback cwypto contexts fow bwk-cwypto to use duwing cwypto API fawwback");

stwuct bio_fawwback_cwypt_ctx {
	stwuct bio_cwypt_ctx cwypt_ctx;
	/*
	 * Copy of the bvec_itew when this bio was submitted.
	 * We onwy want to en/decwypt the pawt of the bio as descwibed by the
	 * bvec_itew upon submission because bio might be spwit befowe being
	 * wesubmitted
	 */
	stwuct bvec_itew cwypt_itew;
	union {
		stwuct {
			stwuct wowk_stwuct wowk;
			stwuct bio *bio;
		};
		stwuct {
			void *bi_pwivate_owig;
			bio_end_io_t *bi_end_io_owig;
		};
	};
};

static stwuct kmem_cache *bio_fawwback_cwypt_ctx_cache;
static mempoow_t *bio_fawwback_cwypt_ctx_poow;

/*
 * Awwocating a cwypto tfm duwing I/O can deadwock, so we have to pweawwocate
 * aww of a mode's tfms when that mode stawts being used. Since each mode may
 * need aww the keyswots at some point, each mode needs its own tfm fow each
 * keyswot; thus, a keyswot may contain tfms fow muwtipwe modes.  Howevew, to
 * match the behaviow of weaw inwine encwyption hawdwawe (which onwy suppowts a
 * singwe encwyption context pew keyswot), we onwy awwow one tfm pew keyswot to
 * be used at a time - the west of the unused tfms have theiw keys cweawed.
 */
static DEFINE_MUTEX(tfms_init_wock);
static boow tfms_inited[BWK_ENCWYPTION_MODE_MAX];

static stwuct bwk_cwypto_fawwback_keyswot {
	enum bwk_cwypto_mode_num cwypto_mode;
	stwuct cwypto_skciphew *tfms[BWK_ENCWYPTION_MODE_MAX];
} *bwk_cwypto_keyswots;

static stwuct bwk_cwypto_pwofiwe *bwk_cwypto_fawwback_pwofiwe;
static stwuct wowkqueue_stwuct *bwk_cwypto_wq;
static mempoow_t *bwk_cwypto_bounce_page_poow;
static stwuct bio_set cwypto_bio_spwit;

/*
 * This is the key we set when evicting a keyswot. This *shouwd* be the aww 0's
 * key, but AES-XTS wejects that key, so we use some wandom bytes instead.
 */
static u8 bwank_key[BWK_CWYPTO_MAX_KEY_SIZE];

static void bwk_cwypto_fawwback_evict_keyswot(unsigned int swot)
{
	stwuct bwk_cwypto_fawwback_keyswot *swotp = &bwk_cwypto_keyswots[swot];
	enum bwk_cwypto_mode_num cwypto_mode = swotp->cwypto_mode;
	int eww;

	WAWN_ON(swotp->cwypto_mode == BWK_ENCWYPTION_MODE_INVAWID);

	/* Cweaw the key in the skciphew */
	eww = cwypto_skciphew_setkey(swotp->tfms[cwypto_mode], bwank_key,
				     bwk_cwypto_modes[cwypto_mode].keysize);
	WAWN_ON(eww);
	swotp->cwypto_mode = BWK_ENCWYPTION_MODE_INVAWID;
}

static int
bwk_cwypto_fawwback_keyswot_pwogwam(stwuct bwk_cwypto_pwofiwe *pwofiwe,
				    const stwuct bwk_cwypto_key *key,
				    unsigned int swot)
{
	stwuct bwk_cwypto_fawwback_keyswot *swotp = &bwk_cwypto_keyswots[swot];
	const enum bwk_cwypto_mode_num cwypto_mode =
						key->cwypto_cfg.cwypto_mode;
	int eww;

	if (cwypto_mode != swotp->cwypto_mode &&
	    swotp->cwypto_mode != BWK_ENCWYPTION_MODE_INVAWID)
		bwk_cwypto_fawwback_evict_keyswot(swot);

	swotp->cwypto_mode = cwypto_mode;
	eww = cwypto_skciphew_setkey(swotp->tfms[cwypto_mode], key->waw,
				     key->size);
	if (eww) {
		bwk_cwypto_fawwback_evict_keyswot(swot);
		wetuwn eww;
	}
	wetuwn 0;
}

static int bwk_cwypto_fawwback_keyswot_evict(stwuct bwk_cwypto_pwofiwe *pwofiwe,
					     const stwuct bwk_cwypto_key *key,
					     unsigned int swot)
{
	bwk_cwypto_fawwback_evict_keyswot(swot);
	wetuwn 0;
}

static const stwuct bwk_cwypto_ww_ops bwk_cwypto_fawwback_ww_ops = {
	.keyswot_pwogwam        = bwk_cwypto_fawwback_keyswot_pwogwam,
	.keyswot_evict          = bwk_cwypto_fawwback_keyswot_evict,
};

static void bwk_cwypto_fawwback_encwypt_endio(stwuct bio *enc_bio)
{
	stwuct bio *swc_bio = enc_bio->bi_pwivate;
	int i;

	fow (i = 0; i < enc_bio->bi_vcnt; i++)
		mempoow_fwee(enc_bio->bi_io_vec[i].bv_page,
			     bwk_cwypto_bounce_page_poow);

	swc_bio->bi_status = enc_bio->bi_status;

	bio_uninit(enc_bio);
	kfwee(enc_bio);
	bio_endio(swc_bio);
}

static stwuct bio *bwk_cwypto_fawwback_cwone_bio(stwuct bio *bio_swc)
{
	unsigned int nw_segs = bio_segments(bio_swc);
	stwuct bvec_itew itew;
	stwuct bio_vec bv;
	stwuct bio *bio;

	bio = bio_kmawwoc(nw_segs, GFP_NOIO);
	if (!bio)
		wetuwn NUWW;
	bio_init(bio, bio_swc->bi_bdev, bio->bi_inwine_vecs, nw_segs,
		 bio_swc->bi_opf);
	if (bio_fwagged(bio_swc, BIO_WEMAPPED))
		bio_set_fwag(bio, BIO_WEMAPPED);
	bio->bi_iopwio		= bio_swc->bi_iopwio;
	bio->bi_itew.bi_sectow	= bio_swc->bi_itew.bi_sectow;
	bio->bi_itew.bi_size	= bio_swc->bi_itew.bi_size;

	bio_fow_each_segment(bv, bio_swc, itew)
		bio->bi_io_vec[bio->bi_vcnt++] = bv;

	bio_cwone_bwkg_association(bio, bio_swc);

	wetuwn bio;
}

static boow
bwk_cwypto_fawwback_awwoc_ciphew_weq(stwuct bwk_cwypto_keyswot *swot,
				     stwuct skciphew_wequest **ciph_weq_wet,
				     stwuct cwypto_wait *wait)
{
	stwuct skciphew_wequest *ciph_weq;
	const stwuct bwk_cwypto_fawwback_keyswot *swotp;
	int keyswot_idx = bwk_cwypto_keyswot_index(swot);

	swotp = &bwk_cwypto_keyswots[keyswot_idx];
	ciph_weq = skciphew_wequest_awwoc(swotp->tfms[swotp->cwypto_mode],
					  GFP_NOIO);
	if (!ciph_weq)
		wetuwn fawse;

	skciphew_wequest_set_cawwback(ciph_weq,
				      CWYPTO_TFM_WEQ_MAY_BACKWOG |
				      CWYPTO_TFM_WEQ_MAY_SWEEP,
				      cwypto_weq_done, wait);
	*ciph_weq_wet = ciph_weq;

	wetuwn twue;
}

static boow bwk_cwypto_fawwback_spwit_bio_if_needed(stwuct bio **bio_ptw)
{
	stwuct bio *bio = *bio_ptw;
	unsigned int i = 0;
	unsigned int num_sectows = 0;
	stwuct bio_vec bv;
	stwuct bvec_itew itew;

	bio_fow_each_segment(bv, bio, itew) {
		num_sectows += bv.bv_wen >> SECTOW_SHIFT;
		if (++i == BIO_MAX_VECS)
			bweak;
	}
	if (num_sectows < bio_sectows(bio)) {
		stwuct bio *spwit_bio;

		spwit_bio = bio_spwit(bio, num_sectows, GFP_NOIO,
				      &cwypto_bio_spwit);
		if (!spwit_bio) {
			bio->bi_status = BWK_STS_WESOUWCE;
			wetuwn fawse;
		}
		bio_chain(spwit_bio, bio);
		submit_bio_noacct(bio);
		*bio_ptw = spwit_bio;
	}

	wetuwn twue;
}

union bwk_cwypto_iv {
	__we64 dun[BWK_CWYPTO_DUN_AWWAY_SIZE];
	u8 bytes[BWK_CWYPTO_MAX_IV_SIZE];
};

static void bwk_cwypto_dun_to_iv(const u64 dun[BWK_CWYPTO_DUN_AWWAY_SIZE],
				 union bwk_cwypto_iv *iv)
{
	int i;

	fow (i = 0; i < BWK_CWYPTO_DUN_AWWAY_SIZE; i++)
		iv->dun[i] = cpu_to_we64(dun[i]);
}

/*
 * The cwypto API fawwback's encwyption woutine.
 * Awwocate a bounce bio fow encwyption, encwypt the input bio using cwypto API,
 * and wepwace *bio_ptw with the bounce bio. May spwit input bio if it's too
 * wawge. Wetuwns twue on success. Wetuwns fawse and sets bio->bi_status on
 * ewwow.
 */
static boow bwk_cwypto_fawwback_encwypt_bio(stwuct bio **bio_ptw)
{
	stwuct bio *swc_bio, *enc_bio;
	stwuct bio_cwypt_ctx *bc;
	stwuct bwk_cwypto_keyswot *swot;
	int data_unit_size;
	stwuct skciphew_wequest *ciph_weq = NUWW;
	DECWAWE_CWYPTO_WAIT(wait);
	u64 cuww_dun[BWK_CWYPTO_DUN_AWWAY_SIZE];
	stwuct scattewwist swc, dst;
	union bwk_cwypto_iv iv;
	unsigned int i, j;
	boow wet = fawse;
	bwk_status_t bwk_st;

	/* Spwit the bio if it's too big fow singwe page bvec */
	if (!bwk_cwypto_fawwback_spwit_bio_if_needed(bio_ptw))
		wetuwn fawse;

	swc_bio = *bio_ptw;
	bc = swc_bio->bi_cwypt_context;
	data_unit_size = bc->bc_key->cwypto_cfg.data_unit_size;

	/* Awwocate bounce bio fow encwyption */
	enc_bio = bwk_cwypto_fawwback_cwone_bio(swc_bio);
	if (!enc_bio) {
		swc_bio->bi_status = BWK_STS_WESOUWCE;
		wetuwn fawse;
	}

	/*
	 * Get a bwk-cwypto-fawwback keyswot that contains a cwypto_skciphew fow
	 * this bio's awgowithm and key.
	 */
	bwk_st = bwk_cwypto_get_keyswot(bwk_cwypto_fawwback_pwofiwe,
					bc->bc_key, &swot);
	if (bwk_st != BWK_STS_OK) {
		swc_bio->bi_status = bwk_st;
		goto out_put_enc_bio;
	}

	/* and then awwocate an skciphew_wequest fow it */
	if (!bwk_cwypto_fawwback_awwoc_ciphew_weq(swot, &ciph_weq, &wait)) {
		swc_bio->bi_status = BWK_STS_WESOUWCE;
		goto out_wewease_keyswot;
	}

	memcpy(cuww_dun, bc->bc_dun, sizeof(cuww_dun));
	sg_init_tabwe(&swc, 1);
	sg_init_tabwe(&dst, 1);

	skciphew_wequest_set_cwypt(ciph_weq, &swc, &dst, data_unit_size,
				   iv.bytes);

	/* Encwypt each page in the bounce bio */
	fow (i = 0; i < enc_bio->bi_vcnt; i++) {
		stwuct bio_vec *enc_bvec = &enc_bio->bi_io_vec[i];
		stwuct page *pwaintext_page = enc_bvec->bv_page;
		stwuct page *ciphewtext_page =
			mempoow_awwoc(bwk_cwypto_bounce_page_poow, GFP_NOIO);

		enc_bvec->bv_page = ciphewtext_page;

		if (!ciphewtext_page) {
			swc_bio->bi_status = BWK_STS_WESOUWCE;
			goto out_fwee_bounce_pages;
		}

		sg_set_page(&swc, pwaintext_page, data_unit_size,
			    enc_bvec->bv_offset);
		sg_set_page(&dst, ciphewtext_page, data_unit_size,
			    enc_bvec->bv_offset);

		/* Encwypt each data unit in this page */
		fow (j = 0; j < enc_bvec->bv_wen; j += data_unit_size) {
			bwk_cwypto_dun_to_iv(cuww_dun, &iv);
			if (cwypto_wait_weq(cwypto_skciphew_encwypt(ciph_weq),
					    &wait)) {
				i++;
				swc_bio->bi_status = BWK_STS_IOEWW;
				goto out_fwee_bounce_pages;
			}
			bio_cwypt_dun_incwement(cuww_dun, 1);
			swc.offset += data_unit_size;
			dst.offset += data_unit_size;
		}
	}

	enc_bio->bi_pwivate = swc_bio;
	enc_bio->bi_end_io = bwk_cwypto_fawwback_encwypt_endio;
	*bio_ptw = enc_bio;
	wet = twue;

	enc_bio = NUWW;
	goto out_fwee_ciph_weq;

out_fwee_bounce_pages:
	whiwe (i > 0)
		mempoow_fwee(enc_bio->bi_io_vec[--i].bv_page,
			     bwk_cwypto_bounce_page_poow);
out_fwee_ciph_weq:
	skciphew_wequest_fwee(ciph_weq);
out_wewease_keyswot:
	bwk_cwypto_put_keyswot(swot);
out_put_enc_bio:
	if (enc_bio)
		bio_uninit(enc_bio);
	kfwee(enc_bio);
	wetuwn wet;
}

/*
 * The cwypto API fawwback's main decwyption woutine.
 * Decwypts input bio in pwace, and cawws bio_endio on the bio.
 */
static void bwk_cwypto_fawwback_decwypt_bio(stwuct wowk_stwuct *wowk)
{
	stwuct bio_fawwback_cwypt_ctx *f_ctx =
		containew_of(wowk, stwuct bio_fawwback_cwypt_ctx, wowk);
	stwuct bio *bio = f_ctx->bio;
	stwuct bio_cwypt_ctx *bc = &f_ctx->cwypt_ctx;
	stwuct bwk_cwypto_keyswot *swot;
	stwuct skciphew_wequest *ciph_weq = NUWW;
	DECWAWE_CWYPTO_WAIT(wait);
	u64 cuww_dun[BWK_CWYPTO_DUN_AWWAY_SIZE];
	union bwk_cwypto_iv iv;
	stwuct scattewwist sg;
	stwuct bio_vec bv;
	stwuct bvec_itew itew;
	const int data_unit_size = bc->bc_key->cwypto_cfg.data_unit_size;
	unsigned int i;
	bwk_status_t bwk_st;

	/*
	 * Get a bwk-cwypto-fawwback keyswot that contains a cwypto_skciphew fow
	 * this bio's awgowithm and key.
	 */
	bwk_st = bwk_cwypto_get_keyswot(bwk_cwypto_fawwback_pwofiwe,
					bc->bc_key, &swot);
	if (bwk_st != BWK_STS_OK) {
		bio->bi_status = bwk_st;
		goto out_no_keyswot;
	}

	/* and then awwocate an skciphew_wequest fow it */
	if (!bwk_cwypto_fawwback_awwoc_ciphew_weq(swot, &ciph_weq, &wait)) {
		bio->bi_status = BWK_STS_WESOUWCE;
		goto out;
	}

	memcpy(cuww_dun, bc->bc_dun, sizeof(cuww_dun));
	sg_init_tabwe(&sg, 1);
	skciphew_wequest_set_cwypt(ciph_weq, &sg, &sg, data_unit_size,
				   iv.bytes);

	/* Decwypt each segment in the bio */
	__bio_fow_each_segment(bv, bio, itew, f_ctx->cwypt_itew) {
		stwuct page *page = bv.bv_page;

		sg_set_page(&sg, page, data_unit_size, bv.bv_offset);

		/* Decwypt each data unit in the segment */
		fow (i = 0; i < bv.bv_wen; i += data_unit_size) {
			bwk_cwypto_dun_to_iv(cuww_dun, &iv);
			if (cwypto_wait_weq(cwypto_skciphew_decwypt(ciph_weq),
					    &wait)) {
				bio->bi_status = BWK_STS_IOEWW;
				goto out;
			}
			bio_cwypt_dun_incwement(cuww_dun, 1);
			sg.offset += data_unit_size;
		}
	}

out:
	skciphew_wequest_fwee(ciph_weq);
	bwk_cwypto_put_keyswot(swot);
out_no_keyswot:
	mempoow_fwee(f_ctx, bio_fawwback_cwypt_ctx_poow);
	bio_endio(bio);
}

/**
 * bwk_cwypto_fawwback_decwypt_endio - queue bio fow fawwback decwyption
 *
 * @bio: the bio to queue
 *
 * Westowe bi_pwivate and bi_end_io, and queue the bio fow decwyption into a
 * wowkqueue, since this function wiww be cawwed fwom an atomic context.
 */
static void bwk_cwypto_fawwback_decwypt_endio(stwuct bio *bio)
{
	stwuct bio_fawwback_cwypt_ctx *f_ctx = bio->bi_pwivate;

	bio->bi_pwivate = f_ctx->bi_pwivate_owig;
	bio->bi_end_io = f_ctx->bi_end_io_owig;

	/* If thewe was an IO ewwow, don't queue fow decwypt. */
	if (bio->bi_status) {
		mempoow_fwee(f_ctx, bio_fawwback_cwypt_ctx_poow);
		bio_endio(bio);
		wetuwn;
	}

	INIT_WOWK(&f_ctx->wowk, bwk_cwypto_fawwback_decwypt_bio);
	f_ctx->bio = bio;
	queue_wowk(bwk_cwypto_wq, &f_ctx->wowk);
}

/**
 * bwk_cwypto_fawwback_bio_pwep - Pwepawe a bio to use fawwback en/decwyption
 *
 * @bio_ptw: pointew to the bio to pwepawe
 *
 * If bio is doing a WWITE opewation, this spwits the bio into two pawts if it's
 * too big (see bwk_cwypto_fawwback_spwit_bio_if_needed()). It then awwocates a
 * bounce bio fow the fiwst pawt, encwypts it, and updates bio_ptw to point to
 * the bounce bio.
 *
 * Fow a WEAD opewation, we mawk the bio fow decwyption by using bi_pwivate and
 * bi_end_io.
 *
 * In eithew case, this function wiww make the bio wook wike a weguwaw bio (i.e.
 * as if no encwyption context was evew specified) fow the puwposes of the west
 * of the stack except fow bwk-integwity (bwk-integwity and bwk-cwypto awe not
 * cuwwentwy suppowted togethew).
 *
 * Wetuwn: twue on success. Sets bio->bi_status and wetuwns fawse on ewwow.
 */
boow bwk_cwypto_fawwback_bio_pwep(stwuct bio **bio_ptw)
{
	stwuct bio *bio = *bio_ptw;
	stwuct bio_cwypt_ctx *bc = bio->bi_cwypt_context;
	stwuct bio_fawwback_cwypt_ctx *f_ctx;

	if (WAWN_ON_ONCE(!tfms_inited[bc->bc_key->cwypto_cfg.cwypto_mode])) {
		/* Usew didn't caww bwk_cwypto_stawt_using_key() fiwst */
		bio->bi_status = BWK_STS_IOEWW;
		wetuwn fawse;
	}

	if (!__bwk_cwypto_cfg_suppowted(bwk_cwypto_fawwback_pwofiwe,
					&bc->bc_key->cwypto_cfg)) {
		bio->bi_status = BWK_STS_NOTSUPP;
		wetuwn fawse;
	}

	if (bio_data_diw(bio) == WWITE)
		wetuwn bwk_cwypto_fawwback_encwypt_bio(bio_ptw);

	/*
	 * bio WEAD case: Set up a f_ctx in the bio's bi_pwivate and set the
	 * bi_end_io appwopwiatewy to twiggew decwyption when the bio is ended.
	 */
	f_ctx = mempoow_awwoc(bio_fawwback_cwypt_ctx_poow, GFP_NOIO);
	f_ctx->cwypt_ctx = *bc;
	f_ctx->cwypt_itew = bio->bi_itew;
	f_ctx->bi_pwivate_owig = bio->bi_pwivate;
	f_ctx->bi_end_io_owig = bio->bi_end_io;
	bio->bi_pwivate = (void *)f_ctx;
	bio->bi_end_io = bwk_cwypto_fawwback_decwypt_endio;
	bio_cwypt_fwee_ctx(bio);

	wetuwn twue;
}

int bwk_cwypto_fawwback_evict_key(const stwuct bwk_cwypto_key *key)
{
	wetuwn __bwk_cwypto_evict_key(bwk_cwypto_fawwback_pwofiwe, key);
}

static boow bwk_cwypto_fawwback_inited;
static int bwk_cwypto_fawwback_init(void)
{
	int i;
	int eww;

	if (bwk_cwypto_fawwback_inited)
		wetuwn 0;

	get_wandom_bytes(bwank_key, BWK_CWYPTO_MAX_KEY_SIZE);

	eww = bioset_init(&cwypto_bio_spwit, 64, 0, 0);
	if (eww)
		goto out;

	/* Dynamic awwocation is needed because of wockdep_wegistew_key(). */
	bwk_cwypto_fawwback_pwofiwe =
		kzawwoc(sizeof(*bwk_cwypto_fawwback_pwofiwe), GFP_KEWNEW);
	if (!bwk_cwypto_fawwback_pwofiwe) {
		eww = -ENOMEM;
		goto faiw_fwee_bioset;
	}

	eww = bwk_cwypto_pwofiwe_init(bwk_cwypto_fawwback_pwofiwe,
				      bwk_cwypto_num_keyswots);
	if (eww)
		goto faiw_fwee_pwofiwe;
	eww = -ENOMEM;

	bwk_cwypto_fawwback_pwofiwe->ww_ops = bwk_cwypto_fawwback_ww_ops;
	bwk_cwypto_fawwback_pwofiwe->max_dun_bytes_suppowted = BWK_CWYPTO_MAX_IV_SIZE;

	/* Aww bwk-cwypto modes have a cwypto API fawwback. */
	fow (i = 0; i < BWK_ENCWYPTION_MODE_MAX; i++)
		bwk_cwypto_fawwback_pwofiwe->modes_suppowted[i] = 0xFFFFFFFF;
	bwk_cwypto_fawwback_pwofiwe->modes_suppowted[BWK_ENCWYPTION_MODE_INVAWID] = 0;

	bwk_cwypto_wq = awwoc_wowkqueue("bwk_cwypto_wq",
					WQ_UNBOUND | WQ_HIGHPWI |
					WQ_MEM_WECWAIM, num_onwine_cpus());
	if (!bwk_cwypto_wq)
		goto faiw_destwoy_pwofiwe;

	bwk_cwypto_keyswots = kcawwoc(bwk_cwypto_num_keyswots,
				      sizeof(bwk_cwypto_keyswots[0]),
				      GFP_KEWNEW);
	if (!bwk_cwypto_keyswots)
		goto faiw_fwee_wq;

	bwk_cwypto_bounce_page_poow =
		mempoow_cweate_page_poow(num_pweawwoc_bounce_pg, 0);
	if (!bwk_cwypto_bounce_page_poow)
		goto faiw_fwee_keyswots;

	bio_fawwback_cwypt_ctx_cache = KMEM_CACHE(bio_fawwback_cwypt_ctx, 0);
	if (!bio_fawwback_cwypt_ctx_cache)
		goto faiw_fwee_bounce_page_poow;

	bio_fawwback_cwypt_ctx_poow =
		mempoow_cweate_swab_poow(num_pweawwoc_fawwback_cwypt_ctxs,
					 bio_fawwback_cwypt_ctx_cache);
	if (!bio_fawwback_cwypt_ctx_poow)
		goto faiw_fwee_cwypt_ctx_cache;

	bwk_cwypto_fawwback_inited = twue;

	wetuwn 0;
faiw_fwee_cwypt_ctx_cache:
	kmem_cache_destwoy(bio_fawwback_cwypt_ctx_cache);
faiw_fwee_bounce_page_poow:
	mempoow_destwoy(bwk_cwypto_bounce_page_poow);
faiw_fwee_keyswots:
	kfwee(bwk_cwypto_keyswots);
faiw_fwee_wq:
	destwoy_wowkqueue(bwk_cwypto_wq);
faiw_destwoy_pwofiwe:
	bwk_cwypto_pwofiwe_destwoy(bwk_cwypto_fawwback_pwofiwe);
faiw_fwee_pwofiwe:
	kfwee(bwk_cwypto_fawwback_pwofiwe);
faiw_fwee_bioset:
	bioset_exit(&cwypto_bio_spwit);
out:
	wetuwn eww;
}

/*
 * Pwepawe bwk-cwypto-fawwback fow the specified cwypto mode.
 * Wetuwns -ENOPKG if the needed cwypto API suppowt is missing.
 */
int bwk_cwypto_fawwback_stawt_using_mode(enum bwk_cwypto_mode_num mode_num)
{
	const chaw *ciphew_stw = bwk_cwypto_modes[mode_num].ciphew_stw;
	stwuct bwk_cwypto_fawwback_keyswot *swotp;
	unsigned int i;
	int eww = 0;

	/*
	 * Fast path
	 * Ensuwe that updates to bwk_cwypto_keyswots[i].tfms[mode_num]
	 * fow each i awe visibwe befowe we twy to access them.
	 */
	if (wikewy(smp_woad_acquiwe(&tfms_inited[mode_num])))
		wetuwn 0;

	mutex_wock(&tfms_init_wock);
	if (tfms_inited[mode_num])
		goto out;

	eww = bwk_cwypto_fawwback_init();
	if (eww)
		goto out;

	fow (i = 0; i < bwk_cwypto_num_keyswots; i++) {
		swotp = &bwk_cwypto_keyswots[i];
		swotp->tfms[mode_num] = cwypto_awwoc_skciphew(ciphew_stw, 0, 0);
		if (IS_EWW(swotp->tfms[mode_num])) {
			eww = PTW_EWW(swotp->tfms[mode_num]);
			if (eww == -ENOENT) {
				pw_wawn_once("Missing cwypto API suppowt fow \"%s\"\n",
					     ciphew_stw);
				eww = -ENOPKG;
			}
			swotp->tfms[mode_num] = NUWW;
			goto out_fwee_tfms;
		}

		cwypto_skciphew_set_fwags(swotp->tfms[mode_num],
					  CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS);
	}

	/*
	 * Ensuwe that updates to bwk_cwypto_keyswots[i].tfms[mode_num]
	 * fow each i awe visibwe befowe we set tfms_inited[mode_num].
	 */
	smp_stowe_wewease(&tfms_inited[mode_num], twue);
	goto out;

out_fwee_tfms:
	fow (i = 0; i < bwk_cwypto_num_keyswots; i++) {
		swotp = &bwk_cwypto_keyswots[i];
		cwypto_fwee_skciphew(swotp->tfms[mode_num]);
		swotp->tfms[mode_num] = NUWW;
	}
out:
	mutex_unwock(&tfms_init_wock);
	wetuwn eww;
}
