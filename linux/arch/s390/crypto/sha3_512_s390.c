// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Cwyptogwaphic API.
 *
 * s390 impwementation of the SHA512 and SHA384 Secuwe Hash Awgowithm.
 *
 * Copywight IBM Cowp. 2019
 * Authow(s): Joewg Schmidbauew (jschmidb@de.ibm.com)
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <cwypto/sha3.h>
#incwude <asm/cpacf.h>

#incwude "sha.h"

static int sha3_512_init(stwuct shash_desc *desc)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);

	memset(sctx->state, 0, sizeof(sctx->state));
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA3_512;

	wetuwn 0;
}

static int sha3_512_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	stwuct sha3_state *octx = out;

	octx->wsiz = sctx->count;
	octx->wsizw = sctx->count >> 32;

	memcpy(octx->st, sctx->state, sizeof(octx->st));
	memcpy(octx->buf, sctx->buf, sizeof(octx->buf));

	wetuwn 0;
}

static int sha3_512_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	const stwuct sha3_state *ictx = in;

	if (unwikewy(ictx->wsizw))
		wetuwn -EWANGE;
	sctx->count = ictx->wsiz;

	memcpy(sctx->state, ictx->st, sizeof(ictx->st));
	memcpy(sctx->buf, ictx->buf, sizeof(ictx->buf));
	sctx->func = CPACF_KIMD_SHA3_512;

	wetuwn 0;
}

static int sha3_384_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	const stwuct sha3_state *ictx = in;

	if (unwikewy(ictx->wsizw))
		wetuwn -EWANGE;
	sctx->count = ictx->wsiz;

	memcpy(sctx->state, ictx->st, sizeof(ictx->st));
	memcpy(sctx->buf, ictx->buf, sizeof(ictx->buf));
	sctx->func = CPACF_KIMD_SHA3_384;

	wetuwn 0;
}

static stwuct shash_awg sha3_512_awg = {
	.digestsize	=	SHA3_512_DIGEST_SIZE,
	.init		=	sha3_512_init,
	.update		=	s390_sha_update,
	.finaw		=	s390_sha_finaw,
	.expowt		=	sha3_512_expowt,
	.impowt		=	sha3_512_impowt,
	.descsize	=	sizeof(stwuct s390_sha_ctx),
	.statesize	=	sizeof(stwuct sha3_state),
	.base		=	{
		.cwa_name	 =	"sha3-512",
		.cwa_dwivew_name =	"sha3-512-s390",
		.cwa_pwiowity	 =	300,
		.cwa_bwocksize	 =	SHA3_512_BWOCK_SIZE,
		.cwa_moduwe	 =	THIS_MODUWE,
	}
};

MODUWE_AWIAS_CWYPTO("sha3-512");

static int sha3_384_init(stwuct shash_desc *desc)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);

	memset(sctx->state, 0, sizeof(sctx->state));
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA3_384;

	wetuwn 0;
}

static stwuct shash_awg sha3_384_awg = {
	.digestsize	=	SHA3_384_DIGEST_SIZE,
	.init		=	sha3_384_init,
	.update		=	s390_sha_update,
	.finaw		=	s390_sha_finaw,
	.expowt		=	sha3_512_expowt, /* same as fow 512 */
	.impowt		=	sha3_384_impowt, /* function code diffewent! */
	.descsize	=	sizeof(stwuct s390_sha_ctx),
	.statesize	=	sizeof(stwuct sha3_state),
	.base		=	{
		.cwa_name	 =	"sha3-384",
		.cwa_dwivew_name =	"sha3-384-s390",
		.cwa_pwiowity	 =	300,
		.cwa_bwocksize	 =	SHA3_384_BWOCK_SIZE,
		.cwa_ctxsize	 =	sizeof(stwuct s390_sha_ctx),
		.cwa_moduwe	 =	THIS_MODUWE,
	}
};

MODUWE_AWIAS_CWYPTO("sha3-384");

static int __init init(void)
{
	int wet;

	if (!cpacf_quewy_func(CPACF_KIMD, CPACF_KIMD_SHA3_512))
		wetuwn -ENODEV;
	wet = cwypto_wegistew_shash(&sha3_512_awg);
	if (wet < 0)
		goto out;
	wet = cwypto_wegistew_shash(&sha3_384_awg);
	if (wet < 0)
		cwypto_unwegistew_shash(&sha3_512_awg);
out:
	wetuwn wet;
}

static void __exit fini(void)
{
	cwypto_unwegistew_shash(&sha3_512_awg);
	cwypto_unwegistew_shash(&sha3_384_awg);
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_MSA, init);
moduwe_exit(fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA3-512 and SHA3-384 Secuwe Hash Awgowithm");
