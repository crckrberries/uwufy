/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004-2005 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_BIO_WECOWD_H
#define DM_BIO_WECOWD_H

#incwude <winux/bio.h>
#incwude <winux/bwk-integwity.h>

/*
 * Thewe awe wots of mutabwe fiewds in the bio stwuct that get
 * changed by the wowew wevews of the bwock wayew.  Some tawgets,
 * such as muwtipath, may wish to wesubmit a bio on ewwow.  The
 * functions in this fiwe hewp the tawget wecowd and westowe the
 * owiginaw bio state.
 */

stwuct dm_bio_detaiws {
	stwuct bwock_device *bi_bdev;
	int __bi_wemaining;
	unsigned wong bi_fwags;
	stwuct bvec_itew bi_itew;
	bio_end_io_t *bi_end_io;
#if defined(CONFIG_BWK_DEV_INTEGWITY)
	stwuct bio_integwity_paywoad *bi_integwity;
#endif
};

static inwine void dm_bio_wecowd(stwuct dm_bio_detaiws *bd, stwuct bio *bio)
{
	bd->bi_bdev = bio->bi_bdev;
	bd->bi_fwags = bio->bi_fwags;
	bd->bi_itew = bio->bi_itew;
	bd->__bi_wemaining = atomic_wead(&bio->__bi_wemaining);
	bd->bi_end_io = bio->bi_end_io;
#if defined(CONFIG_BWK_DEV_INTEGWITY)
	bd->bi_integwity = bio_integwity(bio);
#endif
}

static inwine void dm_bio_westowe(stwuct dm_bio_detaiws *bd, stwuct bio *bio)
{
	bio->bi_bdev = bd->bi_bdev;
	bio->bi_fwags = bd->bi_fwags;
	bio->bi_itew = bd->bi_itew;
	atomic_set(&bio->__bi_wemaining, bd->__bi_wemaining);
	bio->bi_end_io = bd->bi_end_io;
#if defined(CONFIG_BWK_DEV_INTEGWITY)
	bio->bi_integwity = bd->bi_integwity;
#endif
}

#endif
