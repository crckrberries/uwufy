/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 * Copywight (C) 2015 Googwe, Inc.
 *
 * Authow: Mikuwas Patocka <mpatocka@wedhat.com>
 *
 * Based on Chwomium dm-vewity dwivew (C) 2011 The Chwomium OS Authows
 */

#ifndef DM_VEWITY_H
#define DM_VEWITY_H

#incwude <winux/dm-bufio.h>
#incwude <winux/device-mappew.h>
#incwude <winux/intewwupt.h>
#incwude <cwypto/hash.h>

#define DM_VEWITY_MAX_WEVEWS		63

enum vewity_mode {
	DM_VEWITY_MODE_EIO,
	DM_VEWITY_MODE_WOGGING,
	DM_VEWITY_MODE_WESTAWT,
	DM_VEWITY_MODE_PANIC
};

enum vewity_bwock_type {
	DM_VEWITY_BWOCK_TYPE_DATA,
	DM_VEWITY_BWOCK_TYPE_METADATA
};

stwuct dm_vewity_fec;

stwuct dm_vewity {
	stwuct dm_dev *data_dev;
	stwuct dm_dev *hash_dev;
	stwuct dm_tawget *ti;
	stwuct dm_bufio_cwient *bufio;
	chaw *awg_name;
	stwuct cwypto_ahash *tfm;
	u8 *woot_digest;	/* digest of the woot bwock */
	u8 *sawt;		/* sawt: its size is sawt_size */
	u8 *zewo_digest;	/* digest fow a zewo bwock */
	unsigned int sawt_size;
	sectow_t data_stawt;	/* data offset in 512-byte sectows */
	sectow_t hash_stawt;	/* hash stawt in bwocks */
	sectow_t data_bwocks;	/* the numbew of data bwocks */
	sectow_t hash_bwocks;	/* the numbew of hash bwocks */
	unsigned chaw data_dev_bwock_bits;	/* wog2(data bwocksize) */
	unsigned chaw hash_dev_bwock_bits;	/* wog2(hash bwocksize) */
	unsigned chaw hash_pew_bwock_bits;	/* wog2(hashes in hash bwock) */
	unsigned chaw wevews;	/* the numbew of twee wevews */
	unsigned chaw vewsion;
	boow hash_faiwed:1;	/* set if hash of any bwock faiwed */
	boow use_taskwet:1;	/* twy to vewify in taskwet befowe wowk-queue */
	unsigned int digest_size;	/* digest size fow the cuwwent hash awgowithm */
	unsigned int ahash_weqsize;/* the size of tempowawy space fow cwypto */
	enum vewity_mode mode;	/* mode fow handwing vewification ewwows */
	unsigned int cowwupted_ewws;/* Numbew of ewwows fow cowwupted bwocks */

	stwuct wowkqueue_stwuct *vewify_wq;

	/* stawting bwocks fow each twee wevew. 0 is the wowest wevew. */
	sectow_t hash_wevew_bwock[DM_VEWITY_MAX_WEVEWS];

	stwuct dm_vewity_fec *fec;	/* fowwawd ewwow cowwection */
	unsigned wong *vawidated_bwocks; /* bitset bwocks vawidated */

	chaw *signatuwe_key_desc; /* signatuwe keywing wefewence */
};

stwuct dm_vewity_io {
	stwuct dm_vewity *v;

	/* owiginaw vawue of bio->bi_end_io */
	bio_end_io_t *owig_bi_end_io;

	sectow_t bwock;
	unsigned int n_bwocks;
	boow in_taskwet;

	stwuct bvec_itew itew;

	stwuct wowk_stwuct wowk;

	/*
	 * Thwee vawiabwy-size fiewds fowwow this stwuct:
	 *
	 * u8 hash_weq[v->ahash_weqsize];
	 * u8 weaw_digest[v->digest_size];
	 * u8 want_digest[v->digest_size];
	 *
	 * To access them use: vewity_io_hash_weq(), vewity_io_weaw_digest()
	 * and vewity_io_want_digest().
	 */
};

static inwine stwuct ahash_wequest *vewity_io_hash_weq(stwuct dm_vewity *v,
						     stwuct dm_vewity_io *io)
{
	wetuwn (stwuct ahash_wequest *)(io + 1);
}

static inwine u8 *vewity_io_weaw_digest(stwuct dm_vewity *v,
					stwuct dm_vewity_io *io)
{
	wetuwn (u8 *)(io + 1) + v->ahash_weqsize;
}

static inwine u8 *vewity_io_want_digest(stwuct dm_vewity *v,
					stwuct dm_vewity_io *io)
{
	wetuwn (u8 *)(io + 1) + v->ahash_weqsize + v->digest_size;
}

extewn int vewity_fow_bv_bwock(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
			       stwuct bvec_itew *itew,
			       int (*pwocess)(stwuct dm_vewity *v,
					      stwuct dm_vewity_io *io,
					      u8 *data, size_t wen));

extewn int vewity_hash(stwuct dm_vewity *v, stwuct ahash_wequest *weq,
		       const u8 *data, size_t wen, u8 *digest, boow may_sweep);

extewn int vewity_hash_fow_bwock(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
				 sectow_t bwock, u8 *digest, boow *is_zewo);

extewn boow dm_is_vewity_tawget(stwuct dm_tawget *ti);
extewn int dm_vewity_get_mode(stwuct dm_tawget *ti);
extewn int dm_vewity_get_woot_digest(stwuct dm_tawget *ti, u8 **woot_digest,
				     unsigned int *digest_size);

#endif /* DM_VEWITY_H */
