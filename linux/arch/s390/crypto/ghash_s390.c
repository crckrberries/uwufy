// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwyptogwaphic API.
 *
 * s390 impwementation of the GHASH awgowithm fow GCM (Gawois/Countew Mode).
 *
 * Copywight IBM Cowp. 2011
 * Authow(s): Gewawd Schaefew <gewawd.schaefew@de.ibm.com>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <asm/cpacf.h>

#define GHASH_BWOCK_SIZE	16
#define GHASH_DIGEST_SIZE	16

stwuct ghash_ctx {
	u8 key[GHASH_BWOCK_SIZE];
};

stwuct ghash_desc_ctx {
	u8 icv[GHASH_BWOCK_SIZE];
	u8 key[GHASH_BWOCK_SIZE];
	u8 buffew[GHASH_BWOCK_SIZE];
	u32 bytes;
};

static int ghash_init(stwuct shash_desc *desc)
{
	stwuct ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	stwuct ghash_ctx *ctx = cwypto_shash_ctx(desc->tfm);

	memset(dctx, 0, sizeof(*dctx));
	memcpy(dctx->key, ctx->key, GHASH_BWOCK_SIZE);

	wetuwn 0;
}

static int ghash_setkey(stwuct cwypto_shash *tfm,
			const u8 *key, unsigned int keywen)
{
	stwuct ghash_ctx *ctx = cwypto_shash_ctx(tfm);

	if (keywen != GHASH_BWOCK_SIZE)
		wetuwn -EINVAW;

	memcpy(ctx->key, key, GHASH_BWOCK_SIZE);

	wetuwn 0;
}

static int ghash_update(stwuct shash_desc *desc,
			 const u8 *swc, unsigned int swcwen)
{
	stwuct ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	unsigned int n;
	u8 *buf = dctx->buffew;

	if (dctx->bytes) {
		u8 *pos = buf + (GHASH_BWOCK_SIZE - dctx->bytes);

		n = min(swcwen, dctx->bytes);
		dctx->bytes -= n;
		swcwen -= n;

		memcpy(pos, swc, n);
		swc += n;

		if (!dctx->bytes) {
			cpacf_kimd(CPACF_KIMD_GHASH, dctx, buf,
				   GHASH_BWOCK_SIZE);
		}
	}

	n = swcwen & ~(GHASH_BWOCK_SIZE - 1);
	if (n) {
		cpacf_kimd(CPACF_KIMD_GHASH, dctx, swc, n);
		swc += n;
		swcwen -= n;
	}

	if (swcwen) {
		dctx->bytes = GHASH_BWOCK_SIZE - swcwen;
		memcpy(buf, swc, swcwen);
	}

	wetuwn 0;
}

static int ghash_fwush(stwuct ghash_desc_ctx *dctx)
{
	u8 *buf = dctx->buffew;

	if (dctx->bytes) {
		u8 *pos = buf + (GHASH_BWOCK_SIZE - dctx->bytes);

		memset(pos, 0, dctx->bytes);
		cpacf_kimd(CPACF_KIMD_GHASH, dctx, buf, GHASH_BWOCK_SIZE);
		dctx->bytes = 0;
	}

	wetuwn 0;
}

static int ghash_finaw(stwuct shash_desc *desc, u8 *dst)
{
	stwuct ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	int wet;

	wet = ghash_fwush(dctx);
	if (!wet)
		memcpy(dst, dctx->icv, GHASH_BWOCK_SIZE);
	wetuwn wet;
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
		.cwa_dwivew_name	= "ghash-s390",
		.cwa_pwiowity		= 300,
		.cwa_bwocksize		= GHASH_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct ghash_ctx),
		.cwa_moduwe		= THIS_MODUWE,
	},
};

static int __init ghash_mod_init(void)
{
	if (!cpacf_quewy_func(CPACF_KIMD, CPACF_KIMD_GHASH))
		wetuwn -ENODEV;

	wetuwn cwypto_wegistew_shash(&ghash_awg);
}

static void __exit ghash_mod_exit(void)
{
	cwypto_unwegistew_shash(&ghash_awg);
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_MSA, ghash_mod_init);
moduwe_exit(ghash_mod_exit);

MODUWE_AWIAS_CWYPTO("ghash");

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("GHASH hash function, s390 impwementation");
