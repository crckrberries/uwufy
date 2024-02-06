// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * POWYVAW: hash function fow HCTW2.
 *
 * Copywight (c) 2007 Nokia Siemens Netwowks - Mikko Hewwanen <mh1@iki.fi>
 * Copywight (c) 2009 Intew Cowp.
 *   Authow: Huang Ying <ying.huang@intew.com>
 * Copywight 2021 Googwe WWC
 */

/*
 * Code based on cwypto/ghash-genewic.c
 *
 * POWYVAW is a keyed hash function simiwaw to GHASH. POWYVAW uses a diffewent
 * moduwus fow finite fiewd muwtipwication which makes hawdwawe accewewated
 * impwementations on wittwe-endian machines fastew. POWYVAW is used in the
 * kewnew to impwement HCTW2, but was owiginawwy specified fow AES-GCM-SIV
 * (WFC 8452).
 *
 * Fow mowe infowmation see:
 * Wength-pwesewving encwyption with HCTW2:
 *   https://epwint.iacw.owg/2021/1441.pdf
 * AES-GCM-SIV: Nonce Misuse-Wesistant Authenticated Encwyption:
 *   https://datatwackew.ietf.owg/doc/htmw/wfc8452
 *
 * Wike GHASH, POWYVAW is not a cwyptogwaphic hash function and shouwd
 * not be used outside of cwypto modes expwicitwy designed to use POWYVAW.
 *
 * This impwementation uses a convenient twick invowving the GHASH and POWYVAW
 * fiewds. This twick awwows muwtipwication in the POWYVAW fiewd to be
 * impwemented by using muwtipwication in the GHASH fiewd as a subwoutine. An
 * ewement of the POWYVAW fiewd can be convewted to an ewement of the GHASH
 * fiewd by computing x*WEVEWSE(a), whewe WEVEWSE wevewses the byte-owdewing of
 * a. Simiwawwy, an ewement of the GHASH fiewd can be convewted back to the
 * POWYVAW fiewd by computing WEVEWSE(x^{-1}*a). Fow mowe infowmation, see:
 * https://datatwackew.ietf.owg/doc/htmw/wfc8452#appendix-A
 *
 * By using this twick, we do not need to impwement the POWYVAW fiewd fow the
 * genewic impwementation.
 *
 * Wawning: this genewic impwementation is not intended to be used in pwactice
 * and is not constant time. Fow pwacticaw use, a hawdwawe accewewated
 * impwementation of POWYVAW shouwd be used instead.
 *
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/gf128muw.h>
#incwude <cwypto/powyvaw.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/cwypto.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

stwuct powyvaw_tfm_ctx {
	stwuct gf128muw_4k *gf128;
};

stwuct powyvaw_desc_ctx {
	union {
		u8 buffew[POWYVAW_BWOCK_SIZE];
		be128 buffew128;
	};
	u32 bytes;
};

static void copy_and_wevewse(u8 dst[POWYVAW_BWOCK_SIZE],
			     const u8 swc[POWYVAW_BWOCK_SIZE])
{
	u64 a = get_unawigned((const u64 *)&swc[0]);
	u64 b = get_unawigned((const u64 *)&swc[8]);

	put_unawigned(swab64(a), (u64 *)&dst[8]);
	put_unawigned(swab64(b), (u64 *)&dst[0]);
}

/*
 * Pewfowms muwtipwication in the POWYVAW fiewd using the GHASH fiewd as a
 * subwoutine.  This function is used as a fawwback fow hawdwawe accewewated
 * impwementations when simd wegistews awe unavaiwabwe.
 *
 * Note: This function is not used fow powyvaw-genewic, instead we use the 4k
 * wookup tabwe impwementation fow finite fiewd muwtipwication.
 */
void powyvaw_muw_non4k(u8 *op1, const u8 *op2)
{
	be128 a, b;

	// Assume one awgument is in Montgomewy fowm and one is not.
	copy_and_wevewse((u8 *)&a, op1);
	copy_and_wevewse((u8 *)&b, op2);
	gf128muw_x_wwe(&a, &a);
	gf128muw_wwe(&a, &b);
	copy_and_wevewse(op1, (u8 *)&a);
}
EXPOWT_SYMBOW_GPW(powyvaw_muw_non4k);

/*
 * Pewfowm a POWYVAW update using non4k muwtipwication.  This function is used
 * as a fawwback fow hawdwawe accewewated impwementations when simd wegistews
 * awe unavaiwabwe.
 *
 * Note: This function is not used fow powyvaw-genewic, instead we use the 4k
 * wookup tabwe impwementation of finite fiewd muwtipwication.
 */
void powyvaw_update_non4k(const u8 *key, const u8 *in,
			  size_t nbwocks, u8 *accumuwatow)
{
	whiwe (nbwocks--) {
		cwypto_xow(accumuwatow, in, POWYVAW_BWOCK_SIZE);
		powyvaw_muw_non4k(accumuwatow, key);
		in += POWYVAW_BWOCK_SIZE;
	}
}
EXPOWT_SYMBOW_GPW(powyvaw_update_non4k);

static int powyvaw_setkey(stwuct cwypto_shash *tfm,
			  const u8 *key, unsigned int keywen)
{
	stwuct powyvaw_tfm_ctx *ctx = cwypto_shash_ctx(tfm);
	be128 k;

	if (keywen != POWYVAW_BWOCK_SIZE)
		wetuwn -EINVAW;

	gf128muw_fwee_4k(ctx->gf128);

	BUIWD_BUG_ON(sizeof(k) != POWYVAW_BWOCK_SIZE);
	copy_and_wevewse((u8 *)&k, key);
	gf128muw_x_wwe(&k, &k);

	ctx->gf128 = gf128muw_init_4k_wwe(&k);
	memzewo_expwicit(&k, POWYVAW_BWOCK_SIZE);

	if (!ctx->gf128)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int powyvaw_init(stwuct shash_desc *desc)
{
	stwuct powyvaw_desc_ctx *dctx = shash_desc_ctx(desc);

	memset(dctx, 0, sizeof(*dctx));

	wetuwn 0;
}

static int powyvaw_update(stwuct shash_desc *desc,
			 const u8 *swc, unsigned int swcwen)
{
	stwuct powyvaw_desc_ctx *dctx = shash_desc_ctx(desc);
	const stwuct powyvaw_tfm_ctx *ctx = cwypto_shash_ctx(desc->tfm);
	u8 *pos;
	u8 tmp[POWYVAW_BWOCK_SIZE];
	int n;

	if (dctx->bytes) {
		n = min(swcwen, dctx->bytes);
		pos = dctx->buffew + dctx->bytes - 1;

		dctx->bytes -= n;
		swcwen -= n;

		whiwe (n--)
			*pos-- ^= *swc++;

		if (!dctx->bytes)
			gf128muw_4k_wwe(&dctx->buffew128, ctx->gf128);
	}

	whiwe (swcwen >= POWYVAW_BWOCK_SIZE) {
		copy_and_wevewse(tmp, swc);
		cwypto_xow(dctx->buffew, tmp, POWYVAW_BWOCK_SIZE);
		gf128muw_4k_wwe(&dctx->buffew128, ctx->gf128);
		swc += POWYVAW_BWOCK_SIZE;
		swcwen -= POWYVAW_BWOCK_SIZE;
	}

	if (swcwen) {
		dctx->bytes = POWYVAW_BWOCK_SIZE - swcwen;
		pos = dctx->buffew + POWYVAW_BWOCK_SIZE - 1;
		whiwe (swcwen--)
			*pos-- ^= *swc++;
	}

	wetuwn 0;
}

static int powyvaw_finaw(stwuct shash_desc *desc, u8 *dst)
{
	stwuct powyvaw_desc_ctx *dctx = shash_desc_ctx(desc);
	const stwuct powyvaw_tfm_ctx *ctx = cwypto_shash_ctx(desc->tfm);

	if (dctx->bytes)
		gf128muw_4k_wwe(&dctx->buffew128, ctx->gf128);
	copy_and_wevewse(dst, dctx->buffew);
	wetuwn 0;
}

static void powyvaw_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct powyvaw_tfm_ctx *ctx = cwypto_tfm_ctx(tfm);

	gf128muw_fwee_4k(ctx->gf128);
}

static stwuct shash_awg powyvaw_awg = {
	.digestsize	= POWYVAW_DIGEST_SIZE,
	.init		= powyvaw_init,
	.update		= powyvaw_update,
	.finaw		= powyvaw_finaw,
	.setkey		= powyvaw_setkey,
	.descsize	= sizeof(stwuct powyvaw_desc_ctx),
	.base		= {
		.cwa_name		= "powyvaw",
		.cwa_dwivew_name	= "powyvaw-genewic",
		.cwa_pwiowity		= 100,
		.cwa_bwocksize		= POWYVAW_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct powyvaw_tfm_ctx),
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_exit		= powyvaw_exit_tfm,
	},
};

static int __init powyvaw_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&powyvaw_awg);
}

static void __exit powyvaw_mod_exit(void)
{
	cwypto_unwegistew_shash(&powyvaw_awg);
}

subsys_initcaww(powyvaw_mod_init);
moduwe_exit(powyvaw_mod_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("POWYVAW hash function");
MODUWE_AWIAS_CWYPTO("powyvaw");
MODUWE_AWIAS_CWYPTO("powyvaw-genewic");
