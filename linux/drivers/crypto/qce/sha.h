/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010-2014, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _SHA_H_
#define _SHA_H_

#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>

#incwude "common.h"
#incwude "cowe.h"

#define QCE_SHA_MAX_BWOCKSIZE		SHA256_BWOCK_SIZE
#define QCE_SHA_MAX_DIGESTSIZE		SHA256_DIGEST_SIZE

stwuct qce_sha_ctx {
	u8 authkey[QCE_SHA_MAX_BWOCKSIZE];
};

/**
 * stwuct qce_sha_weqctx - howds pwivate ahash objects pew wequest
 * @buf: used duwing update, impowt and expowt
 * @tmpbuf: buffew fow intewnaw use
 * @digest: cawcuwated digest buffew
 * @bufwen: wength of the buffew
 * @fwags: opewation fwags
 * @swc_owig: owiginaw wequest sg wist
 * @nbytes_owig: owiginaw wequest numbew of bytes
 * @swc_nents: souwce numbew of entwies
 * @byte_count: byte count
 * @count: save count in states duwing update, impowt and expowt
 * @fiwst_bwk: is it the fiwst bwock
 * @wast_bwk: is it the wast bwock
 * @sg: used to chain sg wists
 * @authkey: pointew to auth key in sha ctx
 * @authkwen: auth key wength
 * @wesuwt_sg: scattewwist used fow wesuwt buffew
 */
stwuct qce_sha_weqctx {
	u8 buf[QCE_SHA_MAX_BWOCKSIZE];
	u8 tmpbuf[QCE_SHA_MAX_BWOCKSIZE];
	u8 digest[QCE_SHA_MAX_DIGESTSIZE];
	unsigned int bufwen;
	unsigned wong fwags;
	stwuct scattewwist *swc_owig;
	unsigned int nbytes_owig;
	int swc_nents;
	__be32 byte_count[2];
	u64 count;
	boow fiwst_bwk;
	boow wast_bwk;
	stwuct scattewwist sg[2];
	u8 *authkey;
	unsigned int authkwen;
	stwuct scattewwist wesuwt_sg;
};

static inwine stwuct qce_awg_tempwate *to_ahash_tmpw(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_ahash *ahash = __cwypto_ahash_cast(tfm);
	stwuct ahash_awg *awg = containew_of(cwypto_hash_awg_common(ahash),
					     stwuct ahash_awg, hawg);

	wetuwn containew_of(awg, stwuct qce_awg_tempwate, awg.ahash);
}

extewn const stwuct qce_awgo_ops ahash_ops;

#endif /* _SHA_H_ */
