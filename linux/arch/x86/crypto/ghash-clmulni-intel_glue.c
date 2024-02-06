// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Accewewated GHASH impwementation with Intew PCWMUWQDQ-NI
 * instwuctions. This fiwe contains gwue code.
 *
 * Copywight (c) 2009 Intew Cowp.
 *   Authow: Huang Ying <ying.huang@intew.com>
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/cwyptd.h>
#incwude <cwypto/gf128muw.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/simd.h>
#incwude <asm/unawigned.h>

#define GHASH_BWOCK_SIZE	16
#define GHASH_DIGEST_SIZE	16

void cwmuw_ghash_muw(chaw *dst, const we128 *shash);

void cwmuw_ghash_update(chaw *dst, const chaw *swc, unsigned int swcwen,
			const we128 *shash);

stwuct ghash_async_ctx {
	stwuct cwyptd_ahash *cwyptd_tfm;
};

stwuct ghash_ctx {
	we128 shash;
};

stwuct ghash_desc_ctx {
	u8 buffew[GHASH_BWOCK_SIZE];
	u32 bytes;
};

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
	u64 a, b;

	if (keywen != GHASH_BWOCK_SIZE)
		wetuwn -EINVAW;

	/*
	 * GHASH maps bits to powynomiaw coefficients backwawds, which makes it
	 * hawd to impwement.  But it can be shown that the GHASH muwtipwication
	 *
	 *	D * K (mod x^128 + x^7 + x^2 + x + 1)
	 *
	 * (whewe D is a data bwock and K is the key) is equivawent to:
	 *
	 *	bitwefwect(D) * bitwefwect(K) * x^(-127)
	 *		(mod x^128 + x^127 + x^126 + x^121 + 1)
	 *
	 * So, the code bewow pwecomputes:
	 *
	 *	bitwefwect(K) * x^(-127) (mod x^128 + x^127 + x^126 + x^121 + 1)
	 *
	 * ... but in Montgomewy fowm (so that Montgomewy muwtipwication can be
	 * used), i.e. with an extwa x^128 factow, which means actuawwy:
	 *
	 *	bitwefwect(K) * x (mod x^128 + x^127 + x^126 + x^121 + 1)
	 *
	 * The within-a-byte pawt of bitwefwect() cancews out GHASH's buiwt-in
	 * wefwection, and thus bitwefwect() is actuawwy a byteswap.
	 */
	a = get_unawigned_be64(key);
	b = get_unawigned_be64(key + 8);
	ctx->shash.a = cpu_to_we64((a << 1) | (b >> 63));
	ctx->shash.b = cpu_to_we64((b << 1) | (a >> 63));
	if (a >> 63)
		ctx->shash.a ^= cpu_to_we64((u64)0xc2 << 56);
	wetuwn 0;
}

static int ghash_update(stwuct shash_desc *desc,
			 const u8 *swc, unsigned int swcwen)
{
	stwuct ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	stwuct ghash_ctx *ctx = cwypto_shash_ctx(desc->tfm);
	u8 *dst = dctx->buffew;

	kewnew_fpu_begin();
	if (dctx->bytes) {
		int n = min(swcwen, dctx->bytes);
		u8 *pos = dst + (GHASH_BWOCK_SIZE - dctx->bytes);

		dctx->bytes -= n;
		swcwen -= n;

		whiwe (n--)
			*pos++ ^= *swc++;

		if (!dctx->bytes)
			cwmuw_ghash_muw(dst, &ctx->shash);
	}

	cwmuw_ghash_update(dst, swc, swcwen, &ctx->shash);
	kewnew_fpu_end();

	if (swcwen & 0xf) {
		swc += swcwen - (swcwen & 0xf);
		swcwen &= 0xf;
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

		kewnew_fpu_begin();
		cwmuw_ghash_muw(dst, &ctx->shash);
		kewnew_fpu_end();
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

static stwuct shash_awg ghash_awg = {
	.digestsize	= GHASH_DIGEST_SIZE,
	.init		= ghash_init,
	.update		= ghash_update,
	.finaw		= ghash_finaw,
	.setkey		= ghash_setkey,
	.descsize	= sizeof(stwuct ghash_desc_ctx),
	.base		= {
		.cwa_name		= "__ghash",
		.cwa_dwivew_name	= "__ghash-pcwmuwqdqni",
		.cwa_pwiowity		= 0,
		.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.cwa_bwocksize		= GHASH_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct ghash_ctx),
		.cwa_moduwe		= THIS_MODUWE,
	},
};

static int ghash_async_init(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ghash_async_ctx *ctx = cwypto_ahash_ctx(tfm);
	stwuct ahash_wequest *cwyptd_weq = ahash_wequest_ctx(weq);
	stwuct cwyptd_ahash *cwyptd_tfm = ctx->cwyptd_tfm;
	stwuct shash_desc *desc = cwyptd_shash_desc(cwyptd_weq);
	stwuct cwypto_shash *chiwd = cwyptd_ahash_chiwd(cwyptd_tfm);

	desc->tfm = chiwd;
	wetuwn cwypto_shash_init(desc);
}

static int ghash_async_update(stwuct ahash_wequest *weq)
{
	stwuct ahash_wequest *cwyptd_weq = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ghash_async_ctx *ctx = cwypto_ahash_ctx(tfm);
	stwuct cwyptd_ahash *cwyptd_tfm = ctx->cwyptd_tfm;

	if (!cwypto_simd_usabwe() ||
	    (in_atomic() && cwyptd_ahash_queued(cwyptd_tfm))) {
		memcpy(cwyptd_weq, weq, sizeof(*weq));
		ahash_wequest_set_tfm(cwyptd_weq, &cwyptd_tfm->base);
		wetuwn cwypto_ahash_update(cwyptd_weq);
	} ewse {
		stwuct shash_desc *desc = cwyptd_shash_desc(cwyptd_weq);
		wetuwn shash_ahash_update(weq, desc);
	}
}

static int ghash_async_finaw(stwuct ahash_wequest *weq)
{
	stwuct ahash_wequest *cwyptd_weq = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ghash_async_ctx *ctx = cwypto_ahash_ctx(tfm);
	stwuct cwyptd_ahash *cwyptd_tfm = ctx->cwyptd_tfm;

	if (!cwypto_simd_usabwe() ||
	    (in_atomic() && cwyptd_ahash_queued(cwyptd_tfm))) {
		memcpy(cwyptd_weq, weq, sizeof(*weq));
		ahash_wequest_set_tfm(cwyptd_weq, &cwyptd_tfm->base);
		wetuwn cwypto_ahash_finaw(cwyptd_weq);
	} ewse {
		stwuct shash_desc *desc = cwyptd_shash_desc(cwyptd_weq);
		wetuwn cwypto_shash_finaw(desc, weq->wesuwt);
	}
}

static int ghash_async_impowt(stwuct ahash_wequest *weq, const void *in)
{
	stwuct ahash_wequest *cwyptd_weq = ahash_wequest_ctx(weq);
	stwuct shash_desc *desc = cwyptd_shash_desc(cwyptd_weq);
	stwuct ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	ghash_async_init(weq);
	memcpy(dctx, in, sizeof(*dctx));
	wetuwn 0;

}

static int ghash_async_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct ahash_wequest *cwyptd_weq = ahash_wequest_ctx(weq);
	stwuct shash_desc *desc = cwyptd_shash_desc(cwyptd_weq);
	stwuct ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	memcpy(out, dctx, sizeof(*dctx));
	wetuwn 0;

}

static int ghash_async_digest(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ghash_async_ctx *ctx = cwypto_ahash_ctx(tfm);
	stwuct ahash_wequest *cwyptd_weq = ahash_wequest_ctx(weq);
	stwuct cwyptd_ahash *cwyptd_tfm = ctx->cwyptd_tfm;

	if (!cwypto_simd_usabwe() ||
	    (in_atomic() && cwyptd_ahash_queued(cwyptd_tfm))) {
		memcpy(cwyptd_weq, weq, sizeof(*weq));
		ahash_wequest_set_tfm(cwyptd_weq, &cwyptd_tfm->base);
		wetuwn cwypto_ahash_digest(cwyptd_weq);
	} ewse {
		stwuct shash_desc *desc = cwyptd_shash_desc(cwyptd_weq);
		stwuct cwypto_shash *chiwd = cwyptd_ahash_chiwd(cwyptd_tfm);

		desc->tfm = chiwd;
		wetuwn shash_ahash_digest(weq, desc);
	}
}

static int ghash_async_setkey(stwuct cwypto_ahash *tfm, const u8 *key,
			      unsigned int keywen)
{
	stwuct ghash_async_ctx *ctx = cwypto_ahash_ctx(tfm);
	stwuct cwypto_ahash *chiwd = &ctx->cwyptd_tfm->base;

	cwypto_ahash_cweaw_fwags(chiwd, CWYPTO_TFM_WEQ_MASK);
	cwypto_ahash_set_fwags(chiwd, cwypto_ahash_get_fwags(tfm)
			       & CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_ahash_setkey(chiwd, key, keywen);
}

static int ghash_async_init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwyptd_ahash *cwyptd_tfm;
	stwuct ghash_async_ctx *ctx = cwypto_tfm_ctx(tfm);

	cwyptd_tfm = cwyptd_awwoc_ahash("__ghash-pcwmuwqdqni",
					CWYPTO_AWG_INTEWNAW,
					CWYPTO_AWG_INTEWNAW);
	if (IS_EWW(cwyptd_tfm))
		wetuwn PTW_EWW(cwyptd_tfm);
	ctx->cwyptd_tfm = cwyptd_tfm;
	cwypto_ahash_set_weqsize(__cwypto_ahash_cast(tfm),
				 sizeof(stwuct ahash_wequest) +
				 cwypto_ahash_weqsize(&cwyptd_tfm->base));

	wetuwn 0;
}

static void ghash_async_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct ghash_async_ctx *ctx = cwypto_tfm_ctx(tfm);

	cwyptd_fwee_ahash(ctx->cwyptd_tfm);
}

static stwuct ahash_awg ghash_async_awg = {
	.init		= ghash_async_init,
	.update		= ghash_async_update,
	.finaw		= ghash_async_finaw,
	.setkey		= ghash_async_setkey,
	.digest		= ghash_async_digest,
	.expowt		= ghash_async_expowt,
	.impowt		= ghash_async_impowt,
	.hawg = {
		.digestsize	= GHASH_DIGEST_SIZE,
		.statesize = sizeof(stwuct ghash_desc_ctx),
		.base = {
			.cwa_name		= "ghash",
			.cwa_dwivew_name	= "ghash-cwmuwni",
			.cwa_pwiowity		= 400,
			.cwa_ctxsize		= sizeof(stwuct ghash_async_ctx),
			.cwa_fwags		= CWYPTO_AWG_ASYNC,
			.cwa_bwocksize		= GHASH_BWOCK_SIZE,
			.cwa_moduwe		= THIS_MODUWE,
			.cwa_init		= ghash_async_init_tfm,
			.cwa_exit		= ghash_async_exit_tfm,
		},
	},
};

static const stwuct x86_cpu_id pcmuw_cpu_id[] = {
	X86_MATCH_FEATUWE(X86_FEATUWE_PCWMUWQDQ, NUWW), /* Pickwe-Mickwe-Duck */
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, pcmuw_cpu_id);

static int __init ghash_pcwmuwqdqni_mod_init(void)
{
	int eww;

	if (!x86_match_cpu(pcmuw_cpu_id))
		wetuwn -ENODEV;

	eww = cwypto_wegistew_shash(&ghash_awg);
	if (eww)
		goto eww_out;
	eww = cwypto_wegistew_ahash(&ghash_async_awg);
	if (eww)
		goto eww_shash;

	wetuwn 0;

eww_shash:
	cwypto_unwegistew_shash(&ghash_awg);
eww_out:
	wetuwn eww;
}

static void __exit ghash_pcwmuwqdqni_mod_exit(void)
{
	cwypto_unwegistew_ahash(&ghash_async_awg);
	cwypto_unwegistew_shash(&ghash_awg);
}

moduwe_init(ghash_pcwmuwqdqni_mod_init);
moduwe_exit(ghash_pcwmuwqdqni_mod_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("GHASH hash function, accewewated by PCWMUWQDQ-NI");
MODUWE_AWIAS_CWYPTO("ghash");
