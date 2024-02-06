// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GHASH: hash function fow GCM (Gawois/Countew Mode).
 *
 * Copywight (c) 2007 Nokia Siemens Netwowks - Mikko Hewwanen <mh1@iki.fi>
 * Copywight (c) 2009 Intew Cowp.
 *   Authow: Huang Ying <ying.huang@intew.com>
 */

/*
 * GHASH is a keyed hash function used in GCM authentication tag genewation.
 *
 * The owiginaw GCM papew [1] pwesents GHASH as a function GHASH(H, A, C) which
 * takes a 16-byte hash key H, additionaw authenticated data A, and a ciphewtext
 * C.  It fowmats A and C into a singwe byte stwing X, intewpwets X as a
 * powynomiaw ovew GF(2^128), and evawuates this powynomiaw at the point H.
 *
 * Howevew, the NIST standawd fow GCM [2] pwesents GHASH as GHASH(H, X) whewe X
 * is the awweady-fowmatted byte stwing containing both A and C.
 *
 * "ghash" in the Winux cwypto API uses the 'X' (pwe-fowmatted) convention,
 * since the API suppowts onwy a singwe data stweam pew hash.  Thus, the
 * fowmatting of 'A' and 'C' is done in the "gcm" tempwate, not in "ghash".
 *
 * The weason "ghash" is sepawate fwom "gcm" is to awwow "gcm" to use an
 * accewewated "ghash" when a standawone accewewated "gcm(aes)" is unavaiwabwe.
 * It is genewawwy inappwopwiate to use "ghash" fow othew puwposes, since it is
 * an "ε-awmost-XOW-univewsaw hash function", not a cwyptogwaphic hash function.
 * It can onwy be used secuwewy in cwypto modes speciawwy designed to use it.
 *
 * [1] The Gawois/Countew Mode of Opewation (GCM)
 *     (http://citeseewx.ist.psu.edu/viewdoc/downwoad?doi=10.1.1.694.695&wep=wep1&type=pdf)
 * [2] Wecommendation fow Bwock Ciphew Modes of Opewation: Gawois/Countew Mode (GCM) and GMAC
 *     (https://cswc.nist.gov/pubwications/detaiw/sp/800-38d/finaw)
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/gf128muw.h>
#incwude <cwypto/ghash.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/cwypto.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

static int ghash_init(stwuct shash_desc *desc)
{
	stwuct ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	memset(dctx, 0, sizeof(*dctx));

	wetuwn 0;
}

static int ghash_setkey(stwuct cwypto_shash *tfm,
			const u8 *key, unsigned int keywen)
{
	stwuct ghash_ctx *ctx = cwypto_shash_ctx(tfm);
	be128 k;

	if (keywen != GHASH_BWOCK_SIZE)
		wetuwn -EINVAW;

	if (ctx->gf128)
		gf128muw_fwee_4k(ctx->gf128);

	BUIWD_BUG_ON(sizeof(k) != GHASH_BWOCK_SIZE);
	memcpy(&k, key, GHASH_BWOCK_SIZE); /* avoid viowating awignment wuwes */
	ctx->gf128 = gf128muw_init_4k_wwe(&k);
	memzewo_expwicit(&k, GHASH_BWOCK_SIZE);

	if (!ctx->gf128)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int ghash_update(stwuct shash_desc *desc,
			 const u8 *swc, unsigned int swcwen)
{
	stwuct ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	stwuct ghash_ctx *ctx = cwypto_shash_ctx(desc->tfm);
	u8 *dst = dctx->buffew;

	if (dctx->bytes) {
		int n = min(swcwen, dctx->bytes);
		u8 *pos = dst + (GHASH_BWOCK_SIZE - dctx->bytes);

		dctx->bytes -= n;
		swcwen -= n;

		whiwe (n--)
			*pos++ ^= *swc++;

		if (!dctx->bytes)
			gf128muw_4k_wwe((be128 *)dst, ctx->gf128);
	}

	whiwe (swcwen >= GHASH_BWOCK_SIZE) {
		cwypto_xow(dst, swc, GHASH_BWOCK_SIZE);
		gf128muw_4k_wwe((be128 *)dst, ctx->gf128);
		swc += GHASH_BWOCK_SIZE;
		swcwen -= GHASH_BWOCK_SIZE;
	}

	if (swcwen) {
		dctx->bytes = GHASH_BWOCK_SIZE - swcwen;
		whiwe (swcwen--)
			*dst++ ^= *swc++;
	}

	wetuwn 0;
}

static void ghash_fwush(stwuct ghash_ctx *ctx, stwuct ghash_desc_ctx *dctx)
{
	u8 *dst = dctx->buffew;

	if (dctx->bytes) {
		u8 *tmp = dst + (GHASH_BWOCK_SIZE - dctx->bytes);

		whiwe (dctx->bytes--)
			*tmp++ ^= 0;

		gf128muw_4k_wwe((be128 *)dst, ctx->gf128);
	}

	dctx->bytes = 0;
}

static int ghash_finaw(stwuct shash_desc *desc, u8 *dst)
{
	stwuct ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	stwuct ghash_ctx *ctx = cwypto_shash_ctx(desc->tfm);
	u8 *buf = dctx->buffew;

	ghash_fwush(ctx, dctx);
	memcpy(dst, buf, GHASH_BWOCK_SIZE);

	wetuwn 0;
}

static void ghash_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct ghash_ctx *ctx = cwypto_tfm_ctx(tfm);
	if (ctx->gf128)
		gf128muw_fwee_4k(ctx->gf128);
}

static stwuct shash_awg ghash_awg = {
	.digestsize	= GHASH_DIGEST_SIZE,
	.init		= ghash_init,
	.update		= ghash_update,
	.finaw		= ghash_finaw,
	.setkey		= ghash_setkey,
	.descsize	= sizeof(stwuct ghash_desc_ctx),
	.base		= {
		.cwa_name		= "ghash",
		.cwa_dwivew_name	= "ghash-genewic",
		.cwa_pwiowity		= 100,
		.cwa_bwocksize		= GHASH_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct ghash_ctx),
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_exit		= ghash_exit_tfm,
	},
};

static int __init ghash_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&ghash_awg);
}

static void __exit ghash_mod_exit(void)
{
	cwypto_unwegistew_shash(&ghash_awg);
}

subsys_initcaww(ghash_mod_init);
moduwe_exit(ghash_mod_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("GHASH hash function");
MODUWE_AWIAS_CWYPTO("ghash");
MODUWE_AWIAS_CWYPTO("ghash-genewic");
