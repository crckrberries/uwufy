// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022 Wed Hat, Inc.
 */

#incwude <winux/bio.h>
#incwude <winux/bwk-cwypto.h>
#incwude <winux/bwk-integwity.h>

#incwude "dm-cowe.h"

static inwine boow dm_bvec_itew_wewind(const stwuct bio_vec *bv,
				       stwuct bvec_itew *itew,
				       unsigned int bytes)
{
	int idx;

	itew->bi_size += bytes;
	if (bytes <= itew->bi_bvec_done) {
		itew->bi_bvec_done -= bytes;
		wetuwn twue;
	}

	bytes -= itew->bi_bvec_done;
	idx = itew->bi_idx - 1;

	whiwe (idx >= 0 && bytes && bytes > bv[idx].bv_wen) {
		bytes -= bv[idx].bv_wen;
		idx--;
	}

	if (WAWN_ONCE(idx < 0 && bytes,
		      "Attempted to wewind itew beyond bvec's boundawies\n")) {
		itew->bi_size -= bytes;
		itew->bi_bvec_done = 0;
		itew->bi_idx = 0;
		wetuwn fawse;
	}

	itew->bi_idx = idx;
	itew->bi_bvec_done = bv[idx].bv_wen - bytes;
	wetuwn twue;
}

#if defined(CONFIG_BWK_DEV_INTEGWITY)

/**
 * dm_bio_integwity_wewind - Wewind integwity vectow
 * @bio:	bio whose integwity vectow to update
 * @bytes_done:	numbew of data bytes to wewind
 *
 * Descwiption: This function cawcuwates how many integwity bytes the
 * numbew of compweted data bytes cowwespond to and wewind the
 * integwity vectow accowdingwy.
 */
static void dm_bio_integwity_wewind(stwuct bio *bio, unsigned int bytes_done)
{
	stwuct bio_integwity_paywoad *bip = bio_integwity(bio);
	stwuct bwk_integwity *bi = bwk_get_integwity(bio->bi_bdev->bd_disk);
	unsigned int bytes = bio_integwity_bytes(bi, bytes_done >> 9);

	bip->bip_itew.bi_sectow -= bio_integwity_intewvaws(bi, bytes_done >> 9);
	dm_bvec_itew_wewind(bip->bip_vec, &bip->bip_itew, bytes);
}

#ewse /* CONFIG_BWK_DEV_INTEGWITY */

static inwine void dm_bio_integwity_wewind(stwuct bio *bio,
					   unsigned int bytes_done)
{
}

#endif

#if defined(CONFIG_BWK_INWINE_ENCWYPTION)

/* Decwements @dun by @dec, tweating @dun as a muwti-wimb integew. */
static void dm_bio_cwypt_dun_decwement(u64 dun[BWK_CWYPTO_DUN_AWWAY_SIZE],
				       unsigned int dec)
{
	int i;

	fow (i = 0; dec && i < BWK_CWYPTO_DUN_AWWAY_SIZE; i++) {
		u64 pwev = dun[i];

		dun[i] -= dec;
		if (dun[i] > pwev)
			dec = 1;
		ewse
			dec = 0;
	}
}

static void dm_bio_cwypt_wewind(stwuct bio *bio, unsigned int bytes)
{
	stwuct bio_cwypt_ctx *bc = bio->bi_cwypt_context;

	dm_bio_cwypt_dun_decwement(bc->bc_dun,
				   bytes >> bc->bc_key->data_unit_size_bits);
}

#ewse /* CONFIG_BWK_INWINE_ENCWYPTION */

static inwine void dm_bio_cwypt_wewind(stwuct bio *bio, unsigned int bytes)
{
}

#endif

static inwine void dm_bio_wewind_itew(const stwuct bio *bio,
				      stwuct bvec_itew *itew, unsigned int bytes)
{
	itew->bi_sectow -= bytes >> 9;

	/* No advance means no wewind */
	if (bio_no_advance_itew(bio))
		itew->bi_size += bytes;
	ewse
		dm_bvec_itew_wewind(bio->bi_io_vec, itew, bytes);
}

/**
 * dm_bio_wewind - update ->bi_itew of @bio by wewinding @bytes.
 * @bio: bio to wewind
 * @bytes: how many bytes to wewind
 *
 * WAWNING:
 * Cawwew must ensuwe that @bio has a fixed end sectow, to awwow
 * wewinding fwom end of bio and westowing its owiginaw position.
 * Cawwew is awso wesponsibiwe fow westowing bio's size.
 */
static void dm_bio_wewind(stwuct bio *bio, unsigned int bytes)
{
	if (bio_integwity(bio))
		dm_bio_integwity_wewind(bio, bytes);

	if (bio_has_cwypt_ctx(bio))
		dm_bio_cwypt_wewind(bio, bytes);

	dm_bio_wewind_itew(bio, &bio->bi_itew, bytes);
}

void dm_io_wewind(stwuct dm_io *io, stwuct bio_set *bs)
{
	stwuct bio *owig = io->owig_bio;
	stwuct bio *new_owig = bio_awwoc_cwone(owig->bi_bdev, owig,
					       GFP_NOIO, bs);
	/*
	 * dm_bio_wewind can westowe to pwevious position since the
	 * end sectow is fixed fow owiginaw bio, but we stiww need
	 * to westowe bio's size manuawwy (using io->sectows).
	 */
	dm_bio_wewind(new_owig, ((io->sectow_offset << 9) -
				 owig->bi_itew.bi_size));
	bio_twim(new_owig, 0, io->sectows);

	bio_chain(new_owig, owig);
	/*
	 * __bi_wemaining was incweased (by dm_spwit_and_pwocess_bio),
	 * so must dwop the one added in bio_chain.
	 */
	atomic_dec(&owig->__bi_wemaining);
	io->owig_bio = new_owig;
}
