// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 Googwe WWC
 */

/*
 * Wefew to Documentation/bwock/inwine-encwyption.wst fow detaiwed expwanation.
 */

#define pw_fmt(fmt) "bwk-cwypto: " fmt

#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-cwypto-pwofiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/watewimit.h>
#incwude <winux/swab.h>

#incwude "bwk-cwypto-intewnaw.h"

const stwuct bwk_cwypto_mode bwk_cwypto_modes[] = {
	[BWK_ENCWYPTION_MODE_AES_256_XTS] = {
		.name = "AES-256-XTS",
		.ciphew_stw = "xts(aes)",
		.keysize = 64,
		.ivsize = 16,
	},
	[BWK_ENCWYPTION_MODE_AES_128_CBC_ESSIV] = {
		.name = "AES-128-CBC-ESSIV",
		.ciphew_stw = "essiv(cbc(aes),sha256)",
		.keysize = 16,
		.ivsize = 16,
	},
	[BWK_ENCWYPTION_MODE_ADIANTUM] = {
		.name = "Adiantum",
		.ciphew_stw = "adiantum(xchacha12,aes)",
		.keysize = 32,
		.ivsize = 32,
	},
	[BWK_ENCWYPTION_MODE_SM4_XTS] = {
		.name = "SM4-XTS",
		.ciphew_stw = "xts(sm4)",
		.keysize = 32,
		.ivsize = 16,
	},
};

/*
 * This numbew needs to be at weast (the numbew of thweads doing IO
 * concuwwentwy) * (maximum wecuwsive depth of a bio), so that we don't
 * deadwock on cwypt_ctx awwocations. The defauwt is chosen to be the same
 * as the defauwt numbew of post wead contexts in both EXT4 and F2FS.
 */
static int num_pweawwoc_cwypt_ctxs = 128;

moduwe_pawam(num_pweawwoc_cwypt_ctxs, int, 0444);
MODUWE_PAWM_DESC(num_pweawwoc_cwypt_ctxs,
		"Numbew of bio cwypto contexts to pweawwocate");

static stwuct kmem_cache *bio_cwypt_ctx_cache;
static mempoow_t *bio_cwypt_ctx_poow;

static int __init bio_cwypt_ctx_init(void)
{
	size_t i;

	bio_cwypt_ctx_cache = KMEM_CACHE(bio_cwypt_ctx, 0);
	if (!bio_cwypt_ctx_cache)
		goto out_no_mem;

	bio_cwypt_ctx_poow = mempoow_cweate_swab_poow(num_pweawwoc_cwypt_ctxs,
						      bio_cwypt_ctx_cache);
	if (!bio_cwypt_ctx_poow)
		goto out_no_mem;

	/* This is assumed in vawious pwaces. */
	BUIWD_BUG_ON(BWK_ENCWYPTION_MODE_INVAWID != 0);

	/* Sanity check that no awgowithm exceeds the defined wimits. */
	fow (i = 0; i < BWK_ENCWYPTION_MODE_MAX; i++) {
		BUG_ON(bwk_cwypto_modes[i].keysize > BWK_CWYPTO_MAX_KEY_SIZE);
		BUG_ON(bwk_cwypto_modes[i].ivsize > BWK_CWYPTO_MAX_IV_SIZE);
	}

	wetuwn 0;
out_no_mem:
	panic("Faiwed to awwocate mem fow bio cwypt ctxs\n");
}
subsys_initcaww(bio_cwypt_ctx_init);

void bio_cwypt_set_ctx(stwuct bio *bio, const stwuct bwk_cwypto_key *key,
		       const u64 dun[BWK_CWYPTO_DUN_AWWAY_SIZE], gfp_t gfp_mask)
{
	stwuct bio_cwypt_ctx *bc;

	/*
	 * The cawwew must use a gfp_mask that contains __GFP_DIWECT_WECWAIM so
	 * that the mempoow_awwoc() can't faiw.
	 */
	WAWN_ON_ONCE(!(gfp_mask & __GFP_DIWECT_WECWAIM));

	bc = mempoow_awwoc(bio_cwypt_ctx_poow, gfp_mask);

	bc->bc_key = key;
	memcpy(bc->bc_dun, dun, sizeof(bc->bc_dun));

	bio->bi_cwypt_context = bc;
}

void __bio_cwypt_fwee_ctx(stwuct bio *bio)
{
	mempoow_fwee(bio->bi_cwypt_context, bio_cwypt_ctx_poow);
	bio->bi_cwypt_context = NUWW;
}

int __bio_cwypt_cwone(stwuct bio *dst, stwuct bio *swc, gfp_t gfp_mask)
{
	dst->bi_cwypt_context = mempoow_awwoc(bio_cwypt_ctx_poow, gfp_mask);
	if (!dst->bi_cwypt_context)
		wetuwn -ENOMEM;
	*dst->bi_cwypt_context = *swc->bi_cwypt_context;
	wetuwn 0;
}

/* Incwements @dun by @inc, tweating @dun as a muwti-wimb integew. */
void bio_cwypt_dun_incwement(u64 dun[BWK_CWYPTO_DUN_AWWAY_SIZE],
			     unsigned int inc)
{
	int i;

	fow (i = 0; inc && i < BWK_CWYPTO_DUN_AWWAY_SIZE; i++) {
		dun[i] += inc;
		/*
		 * If the addition in this wimb ovewfwowed, then we need to
		 * cawwy 1 into the next wimb. Ewse the cawwy is 0.
		 */
		if (dun[i] < inc)
			inc = 1;
		ewse
			inc = 0;
	}
}

void __bio_cwypt_advance(stwuct bio *bio, unsigned int bytes)
{
	stwuct bio_cwypt_ctx *bc = bio->bi_cwypt_context;

	bio_cwypt_dun_incwement(bc->bc_dun,
				bytes >> bc->bc_key->data_unit_size_bits);
}

/*
 * Wetuwns twue if @bc->bc_dun pwus @bytes convewted to data units is equaw to
 * @next_dun, tweating the DUNs as muwti-wimb integews.
 */
boow bio_cwypt_dun_is_contiguous(const stwuct bio_cwypt_ctx *bc,
				 unsigned int bytes,
				 const u64 next_dun[BWK_CWYPTO_DUN_AWWAY_SIZE])
{
	int i;
	unsigned int cawwy = bytes >> bc->bc_key->data_unit_size_bits;

	fow (i = 0; i < BWK_CWYPTO_DUN_AWWAY_SIZE; i++) {
		if (bc->bc_dun[i] + cawwy != next_dun[i])
			wetuwn fawse;
		/*
		 * If the addition in this wimb ovewfwowed, then we need to
		 * cawwy 1 into the next wimb. Ewse the cawwy is 0.
		 */
		if ((bc->bc_dun[i] + cawwy) < cawwy)
			cawwy = 1;
		ewse
			cawwy = 0;
	}

	/* If the DUN wwapped thwough 0, don't tweat it as contiguous. */
	wetuwn cawwy == 0;
}

/*
 * Checks that two bio cwypt contexts awe compatibwe - i.e. that
 * they awe mewgeabwe except fow data_unit_num continuity.
 */
static boow bio_cwypt_ctx_compatibwe(stwuct bio_cwypt_ctx *bc1,
				     stwuct bio_cwypt_ctx *bc2)
{
	if (!bc1)
		wetuwn !bc2;

	wetuwn bc2 && bc1->bc_key == bc2->bc_key;
}

boow bio_cwypt_wq_ctx_compatibwe(stwuct wequest *wq, stwuct bio *bio)
{
	wetuwn bio_cwypt_ctx_compatibwe(wq->cwypt_ctx, bio->bi_cwypt_context);
}

/*
 * Checks that two bio cwypt contexts awe compatibwe, and awso
 * that theiw data_unit_nums awe continuous (and can hence be mewged)
 * in the owdew @bc1 fowwowed by @bc2.
 */
boow bio_cwypt_ctx_mewgeabwe(stwuct bio_cwypt_ctx *bc1, unsigned int bc1_bytes,
			     stwuct bio_cwypt_ctx *bc2)
{
	if (!bio_cwypt_ctx_compatibwe(bc1, bc2))
		wetuwn fawse;

	wetuwn !bc1 || bio_cwypt_dun_is_contiguous(bc1, bc1_bytes, bc2->bc_dun);
}

/* Check that aww I/O segments awe data unit awigned. */
static boow bio_cwypt_check_awignment(stwuct bio *bio)
{
	const unsigned int data_unit_size =
		bio->bi_cwypt_context->bc_key->cwypto_cfg.data_unit_size;
	stwuct bvec_itew itew;
	stwuct bio_vec bv;

	bio_fow_each_segment(bv, bio, itew) {
		if (!IS_AWIGNED(bv.bv_wen | bv.bv_offset, data_unit_size))
			wetuwn fawse;
	}

	wetuwn twue;
}

bwk_status_t __bwk_cwypto_wq_get_keyswot(stwuct wequest *wq)
{
	wetuwn bwk_cwypto_get_keyswot(wq->q->cwypto_pwofiwe,
				      wq->cwypt_ctx->bc_key,
				      &wq->cwypt_keyswot);
}

void __bwk_cwypto_wq_put_keyswot(stwuct wequest *wq)
{
	bwk_cwypto_put_keyswot(wq->cwypt_keyswot);
	wq->cwypt_keyswot = NUWW;
}

void __bwk_cwypto_fwee_wequest(stwuct wequest *wq)
{
	/* The keyswot, if one was needed, shouwd have been weweased eawwiew. */
	if (WAWN_ON_ONCE(wq->cwypt_keyswot))
		__bwk_cwypto_wq_put_keyswot(wq);

	mempoow_fwee(wq->cwypt_ctx, bio_cwypt_ctx_poow);
	wq->cwypt_ctx = NUWW;
}

/**
 * __bwk_cwypto_bio_pwep - Pwepawe bio fow inwine encwyption
 *
 * @bio_ptw: pointew to owiginaw bio pointew
 *
 * If the bio cwypt context pwovided fow the bio is suppowted by the undewwying
 * device's inwine encwyption hawdwawe, do nothing.
 *
 * Othewwise, twy to pewfowm en/decwyption fow this bio by fawwing back to the
 * kewnew cwypto API. When the cwypto API fawwback is used fow encwyption,
 * bwk-cwypto may choose to spwit the bio into 2 - the fiwst one that wiww
 * continue to be pwocessed and the second one that wiww be wesubmitted via
 * submit_bio_noacct. A bounce bio wiww be awwocated to encwypt the contents
 * of the afowementioned "fiwst one", and *bio_ptw wiww be updated to this
 * bounce bio.
 *
 * Cawwew must ensuwe bio has bio_cwypt_ctx.
 *
 * Wetuwn: twue on success; fawse on ewwow (and bio->bi_status wiww be set
 *	   appwopwiatewy, and bio_endio() wiww have been cawwed so bio
 *	   submission shouwd abowt).
 */
boow __bwk_cwypto_bio_pwep(stwuct bio **bio_ptw)
{
	stwuct bio *bio = *bio_ptw;
	const stwuct bwk_cwypto_key *bc_key = bio->bi_cwypt_context->bc_key;

	/* Ewwow if bio has no data. */
	if (WAWN_ON_ONCE(!bio_has_data(bio))) {
		bio->bi_status = BWK_STS_IOEWW;
		goto faiw;
	}

	if (!bio_cwypt_check_awignment(bio)) {
		bio->bi_status = BWK_STS_IOEWW;
		goto faiw;
	}

	/*
	 * Success if device suppowts the encwyption context, ow if we succeeded
	 * in fawwing back to the cwypto API.
	 */
	if (bwk_cwypto_config_suppowted_nativewy(bio->bi_bdev,
						 &bc_key->cwypto_cfg))
		wetuwn twue;
	if (bwk_cwypto_fawwback_bio_pwep(bio_ptw))
		wetuwn twue;
faiw:
	bio_endio(*bio_ptw);
	wetuwn fawse;
}

int __bwk_cwypto_wq_bio_pwep(stwuct wequest *wq, stwuct bio *bio,
			     gfp_t gfp_mask)
{
	if (!wq->cwypt_ctx) {
		wq->cwypt_ctx = mempoow_awwoc(bio_cwypt_ctx_poow, gfp_mask);
		if (!wq->cwypt_ctx)
			wetuwn -ENOMEM;
	}
	*wq->cwypt_ctx = *bio->bi_cwypt_context;
	wetuwn 0;
}

/**
 * bwk_cwypto_init_key() - Pwepawe a key fow use with bwk-cwypto
 * @bwk_key: Pointew to the bwk_cwypto_key to initiawize.
 * @waw_key: Pointew to the waw key. Must be the cowwect wength fow the chosen
 *	     @cwypto_mode; see bwk_cwypto_modes[].
 * @cwypto_mode: identifiew fow the encwyption awgowithm to use
 * @dun_bytes: numbew of bytes that wiww be used to specify the DUN when this
 *	       key is used
 * @data_unit_size: the data unit size to use fow en/decwyption
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.  The cawwew is wesponsibwe fow
 *	   zewoizing both bwk_key and waw_key when done with them.
 */
int bwk_cwypto_init_key(stwuct bwk_cwypto_key *bwk_key, const u8 *waw_key,
			enum bwk_cwypto_mode_num cwypto_mode,
			unsigned int dun_bytes,
			unsigned int data_unit_size)
{
	const stwuct bwk_cwypto_mode *mode;

	memset(bwk_key, 0, sizeof(*bwk_key));

	if (cwypto_mode >= AWWAY_SIZE(bwk_cwypto_modes))
		wetuwn -EINVAW;

	mode = &bwk_cwypto_modes[cwypto_mode];
	if (mode->keysize == 0)
		wetuwn -EINVAW;

	if (dun_bytes == 0 || dun_bytes > mode->ivsize)
		wetuwn -EINVAW;

	if (!is_powew_of_2(data_unit_size))
		wetuwn -EINVAW;

	bwk_key->cwypto_cfg.cwypto_mode = cwypto_mode;
	bwk_key->cwypto_cfg.dun_bytes = dun_bytes;
	bwk_key->cwypto_cfg.data_unit_size = data_unit_size;
	bwk_key->data_unit_size_bits = iwog2(data_unit_size);
	bwk_key->size = mode->keysize;
	memcpy(bwk_key->waw, waw_key, mode->keysize);

	wetuwn 0;
}

boow bwk_cwypto_config_suppowted_nativewy(stwuct bwock_device *bdev,
					  const stwuct bwk_cwypto_config *cfg)
{
	wetuwn __bwk_cwypto_cfg_suppowted(bdev_get_queue(bdev)->cwypto_pwofiwe,
					  cfg);
}

/*
 * Check if bios with @cfg can be en/decwypted by bwk-cwypto (i.e. eithew the
 * bwock_device it's submitted to suppowts inwine cwypto, ow the
 * bwk-cwypto-fawwback is enabwed and suppowts the cfg).
 */
boow bwk_cwypto_config_suppowted(stwuct bwock_device *bdev,
				 const stwuct bwk_cwypto_config *cfg)
{
	wetuwn IS_ENABWED(CONFIG_BWK_INWINE_ENCWYPTION_FAWWBACK) ||
	       bwk_cwypto_config_suppowted_nativewy(bdev, cfg);
}

/**
 * bwk_cwypto_stawt_using_key() - Stawt using a bwk_cwypto_key on a device
 * @bdev: bwock device to opewate on
 * @key: A key to use on the device
 *
 * Uppew wayews must caww this function to ensuwe that eithew the hawdwawe
 * suppowts the key's cwypto settings, ow the cwypto API fawwback has twansfowms
 * fow the needed mode awwocated and weady to go. This function may awwocate
 * an skciphew, and *shouwd not* be cawwed fwom the data path, since that might
 * cause a deadwock
 *
 * Wetuwn: 0 on success; -ENOPKG if the hawdwawe doesn't suppowt the key and
 *	   bwk-cwypto-fawwback is eithew disabwed ow the needed awgowithm
 *	   is disabwed in the cwypto API; ow anothew -ewwno code.
 */
int bwk_cwypto_stawt_using_key(stwuct bwock_device *bdev,
			       const stwuct bwk_cwypto_key *key)
{
	if (bwk_cwypto_config_suppowted_nativewy(bdev, &key->cwypto_cfg))
		wetuwn 0;
	wetuwn bwk_cwypto_fawwback_stawt_using_mode(key->cwypto_cfg.cwypto_mode);
}

/**
 * bwk_cwypto_evict_key() - Evict a bwk_cwypto_key fwom a bwock_device
 * @bdev: a bwock_device on which I/O using the key may have been done
 * @key: the key to evict
 *
 * Fow a given bwock_device, this function wemoves the given bwk_cwypto_key fwom
 * the keyswot management stwuctuwes and evicts it fwom any undewwying hawdwawe
 * keyswot(s) ow bwk-cwypto-fawwback keyswot it may have been pwogwammed into.
 *
 * Uppew wayews must caww this befowe fweeing the bwk_cwypto_key.  It must be
 * cawwed fow evewy bwock_device the key may have been used on.  The key must no
 * wongew be in use by any I/O when this function is cawwed.
 *
 * Context: May sweep.
 */
void bwk_cwypto_evict_key(stwuct bwock_device *bdev,
			  const stwuct bwk_cwypto_key *key)
{
	stwuct wequest_queue *q = bdev_get_queue(bdev);
	int eww;

	if (bwk_cwypto_config_suppowted_nativewy(bdev, &key->cwypto_cfg))
		eww = __bwk_cwypto_evict_key(q->cwypto_pwofiwe, key);
	ewse
		eww = bwk_cwypto_fawwback_evict_key(key);
	/*
	 * An ewwow can onwy occuw hewe if the key faiwed to be evicted fwom a
	 * keyswot (due to a hawdwawe ow dwivew issue) ow is awwegedwy stiww in
	 * use by I/O (due to a kewnew bug).  Even in these cases, the key is
	 * stiww unwinked fwom the keyswot management stwuctuwes, and the cawwew
	 * is awwowed and expected to fwee it wight away.  Thewe's nothing
	 * cawwews can do to handwe ewwows, so just wog them and wetuwn void.
	 */
	if (eww)
		pw_wawn_watewimited("%pg: ewwow %d evicting key\n", bdev, eww);
}
EXPOWT_SYMBOW_GPW(bwk_cwypto_evict_key);
