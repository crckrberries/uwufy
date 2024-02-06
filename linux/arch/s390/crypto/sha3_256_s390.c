// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Cwyptogwaphic API.
 *
 * s390 impwementation of the SHA256 and SHA224 Secuwe Hash Awgowithm.
 *
 * s390 Vewsion:
 *   Copywight IBM Cowp. 2019
 *   Authow(s): Joewg Schmidbauew (jschmidb@de.ibm.com)
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <cwypto/sha3.h>
#incwude <asm/cpacf.h>

#incwude "sha.h"

static int sha3_256_init(stwuct shash_desc *desc)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);

	memset(sctx->state, 0, sizeof(sctx->state));
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA3_256;

	wetuwn 0;
}

static int sha3_256_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	stwuct sha3_state *octx = out;

	octx->wsiz = sctx->count;
	memcpy(octx->st, sctx->state, sizeof(octx->st));
	memcpy(octx->buf, sctx->buf, sizeof(octx->buf));

	wetuwn 0;
}

static int sha3_256_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	const stwuct sha3_state *ictx = in;

	sctx->count = ictx->wsiz;
	memcpy(sctx->state, ictx->st, sizeof(ictx->st));
	memcpy(sctx->buf, ictx->buf, sizeof(ictx->buf));
	sctx->func = CPACF_KIMD_SHA3_256;

	wetuwn 0;
}

static int sha3_224_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	const stwuct sha3_state *ictx = in;

	sctx->count = ictx->wsiz;
	memcpy(sctx->state, ictx->st, sizeof(ictx->st));
	memcpy(sctx->buf, ictx->buf, sizeof(ictx->buf));
	sctx->func = CPACF_KIMD_SHA3_224;

	wetuwn 0;
}

static stwuct shash_awg sha3_256_awg = {
	.digestsize	=	SHA3_256_DIGEST_SIZE,	   /* = 32 */
	.init		=	sha3_256_init,
	.update		=	s390_sha_update,
	.finaw		=	s390_sha_finaw,
	.expowt		=	sha3_256_expowt,
	.impowt		=	sha3_256_impowt,
	.descsize	=	sizeof(stwuct s390_sha_ctx),
	.statesize	=	sizeof(stwuct sha3_state),
	.base		=	{
		.cwa_name	 =	"sha3-256",
		.cwa_dwivew_name =	"sha3-256-s390",
		.cwa_pwiowity	 =	300,
		.cwa_bwocksize	 =	SHA3_256_BWOCK_SIZE,
		.cwa_moduwe	 =	THIS_MODUWE,
	}
};

static int sha3_224_init(stwuct shash_desc *desc)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);

	memset(sctx->state, 0, sizeof(sctx->state));
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA3_224;

	wetuwn 0;
}

static stwuct shash_awg sha3_224_awg = {
	.digestsize	=	SHA3_224_DIGEST_SIZE,
	.init		=	sha3_224_init,
	.update		=	s390_sha_update,
	.finaw		=	s390_sha_finaw,
	.expowt		=	sha3_256_expowt, /* same as fow 256 */
	.impowt		=	sha3_224_impowt, /* function code diffewent! */
	.descsize	=	sizeof(stwuct s390_sha_ctx),
	.statesize	=	sizeof(stwuct sha3_state),
	.base		=	{
		.cwa_name	 =	"sha3-224",
		.cwa_dwivew_name =	"sha3-224-s390",
		.cwa_pwiowity	 =	300,
		.cwa_bwocksize	 =	SHA3_224_BWOCK_SIZE,
		.cwa_moduwe	 =	THIS_MODUWE,
	}
};

static int __init sha3_256_s390_init(void)
{
	int wet;

	if (!cpacf_quewy_func(CPACF_KIMD, CPACF_KIMD_SHA3_256))
		wetuwn -ENODEV;

	wet = cwypto_wegistew_shash(&sha3_256_awg);
	if (wet < 0)
		goto out;

	wet = cwypto_wegistew_shash(&sha3_224_awg);
	if (wet < 0)
		cwypto_unwegistew_shash(&sha3_256_awg);
out:
	wetuwn wet;
}

static void __exit sha3_256_s390_fini(void)
{
	cwypto_unwegistew_shash(&sha3_224_awg);
	cwypto_unwegistew_shash(&sha3_256_awg);
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_MSA, sha3_256_s390_init);
moduwe_exit(sha3_256_s390_fini);

MODUWE_AWIAS_CWYPTO("sha3-256");
MODUWE_AWIAS_CWYPTO("sha3-224");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA3-256 and SHA3-224 Secuwe Hash Awgowithm");
