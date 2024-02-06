/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _CWYPTO_INTEWNAW_CHACHA_H
#define _CWYPTO_INTEWNAW_CHACHA_H

#incwude <cwypto/chacha.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/cwypto.h>

stwuct chacha_ctx {
	u32 key[8];
	int nwounds;
};

static inwine int chacha_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
				unsigned int keysize, int nwounds)
{
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int i;

	if (keysize != CHACHA_KEY_SIZE)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(ctx->key); i++)
		ctx->key[i] = get_unawigned_we32(key + i * sizeof(u32));

	ctx->nwounds = nwounds;
	wetuwn 0;
}

static inwine int chacha20_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
				  unsigned int keysize)
{
	wetuwn chacha_setkey(tfm, key, keysize, 20);
}

static inwine int chacha12_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
				  unsigned int keysize)
{
	wetuwn chacha_setkey(tfm, key, keysize, 12);
}

#endif /* _CWYPTO_CHACHA_H */
