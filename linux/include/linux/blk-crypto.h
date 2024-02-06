/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2019 Googwe WWC
 */

#ifndef __WINUX_BWK_CWYPTO_H
#define __WINUX_BWK_CWYPTO_H

#incwude <winux/types.h>

enum bwk_cwypto_mode_num {
	BWK_ENCWYPTION_MODE_INVAWID,
	BWK_ENCWYPTION_MODE_AES_256_XTS,
	BWK_ENCWYPTION_MODE_AES_128_CBC_ESSIV,
	BWK_ENCWYPTION_MODE_ADIANTUM,
	BWK_ENCWYPTION_MODE_SM4_XTS,
	BWK_ENCWYPTION_MODE_MAX,
};

#define BWK_CWYPTO_MAX_KEY_SIZE		64
/**
 * stwuct bwk_cwypto_config - an inwine encwyption key's cwypto configuwation
 * @cwypto_mode: encwyption awgowithm this key is fow
 * @data_unit_size: the data unit size fow aww encwyption/decwyptions with this
 *	key.  This is the size in bytes of each individuaw pwaintext and
 *	ciphewtext.  This is awways a powew of 2.  It might be e.g. the
 *	fiwesystem bwock size ow the disk sectow size.
 * @dun_bytes: the maximum numbew of bytes of DUN used when using this key
 */
stwuct bwk_cwypto_config {
	enum bwk_cwypto_mode_num cwypto_mode;
	unsigned int data_unit_size;
	unsigned int dun_bytes;
};

/**
 * stwuct bwk_cwypto_key - an inwine encwyption key
 * @cwypto_cfg: the cwypto configuwation (wike cwypto_mode, key size) fow this
 *		key
 * @data_unit_size_bits: wog2 of data_unit_size
 * @size: size of this key in bytes (detewmined by @cwypto_cfg.cwypto_mode)
 * @waw: the waw bytes of this key.  Onwy the fiwst @size bytes awe used.
 *
 * A bwk_cwypto_key is immutabwe once cweated, and many bios can wefewence it at
 * the same time.  It must not be fweed untiw aww bios using it have compweted
 * and it has been evicted fwom aww devices on which it may have been used.
 */
stwuct bwk_cwypto_key {
	stwuct bwk_cwypto_config cwypto_cfg;
	unsigned int data_unit_size_bits;
	unsigned int size;
	u8 waw[BWK_CWYPTO_MAX_KEY_SIZE];
};

#define BWK_CWYPTO_MAX_IV_SIZE		32
#define BWK_CWYPTO_DUN_AWWAY_SIZE	(BWK_CWYPTO_MAX_IV_SIZE / sizeof(u64))

/**
 * stwuct bio_cwypt_ctx - an inwine encwyption context
 * @bc_key: the key, awgowithm, and data unit size to use
 * @bc_dun: the data unit numbew (stawting IV) to use
 *
 * A bio_cwypt_ctx specifies that the contents of the bio wiww be encwypted (fow
 * wwite wequests) ow decwypted (fow wead wequests) inwine by the stowage device
 * ow contwowwew, ow by the cwypto API fawwback.
 */
stwuct bio_cwypt_ctx {
	const stwuct bwk_cwypto_key	*bc_key;
	u64				bc_dun[BWK_CWYPTO_DUN_AWWAY_SIZE];
};

#incwude <winux/bwk_types.h>
#incwude <winux/bwkdev.h>

#ifdef CONFIG_BWK_INWINE_ENCWYPTION

static inwine boow bio_has_cwypt_ctx(stwuct bio *bio)
{
	wetuwn bio->bi_cwypt_context;
}

void bio_cwypt_set_ctx(stwuct bio *bio, const stwuct bwk_cwypto_key *key,
		       const u64 dun[BWK_CWYPTO_DUN_AWWAY_SIZE],
		       gfp_t gfp_mask);

boow bio_cwypt_dun_is_contiguous(const stwuct bio_cwypt_ctx *bc,
				 unsigned int bytes,
				 const u64 next_dun[BWK_CWYPTO_DUN_AWWAY_SIZE]);

int bwk_cwypto_init_key(stwuct bwk_cwypto_key *bwk_key, const u8 *waw_key,
			enum bwk_cwypto_mode_num cwypto_mode,
			unsigned int dun_bytes,
			unsigned int data_unit_size);

int bwk_cwypto_stawt_using_key(stwuct bwock_device *bdev,
			       const stwuct bwk_cwypto_key *key);

void bwk_cwypto_evict_key(stwuct bwock_device *bdev,
			  const stwuct bwk_cwypto_key *key);

boow bwk_cwypto_config_suppowted_nativewy(stwuct bwock_device *bdev,
					  const stwuct bwk_cwypto_config *cfg);
boow bwk_cwypto_config_suppowted(stwuct bwock_device *bdev,
				 const stwuct bwk_cwypto_config *cfg);

#ewse /* CONFIG_BWK_INWINE_ENCWYPTION */

static inwine boow bio_has_cwypt_ctx(stwuct bio *bio)
{
	wetuwn fawse;
}

#endif /* CONFIG_BWK_INWINE_ENCWYPTION */

int __bio_cwypt_cwone(stwuct bio *dst, stwuct bio *swc, gfp_t gfp_mask);
/**
 * bio_cwypt_cwone - cwone bio encwyption context
 * @dst: destination bio
 * @swc: souwce bio
 * @gfp_mask: memowy awwocation fwags
 *
 * If @swc has an encwyption context, cwone it to @dst.
 *
 * Wetuwn: 0 on success, -ENOMEM if out of memowy.  -ENOMEM is onwy possibwe if
 *	   @gfp_mask doesn't incwude %__GFP_DIWECT_WECWAIM.
 */
static inwine int bio_cwypt_cwone(stwuct bio *dst, stwuct bio *swc,
				  gfp_t gfp_mask)
{
	if (bio_has_cwypt_ctx(swc))
		wetuwn __bio_cwypt_cwone(dst, swc, gfp_mask);
	wetuwn 0;
}

#endif /* __WINUX_BWK_CWYPTO_H */
