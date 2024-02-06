// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Cwyptogwaphic API.
 *
 * s390 impwementation of the SHA512 and SHA38 Secuwe Hash Awgowithm.
 *
 * Copywight IBM Cowp. 2007
 * Authow(s): Jan Gwaubew (jang@de.ibm.com)
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/sha2.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <asm/cpacf.h>

#incwude "sha.h"

static int sha512_init(stwuct shash_desc *desc)
{
	stwuct s390_sha_ctx *ctx = shash_desc_ctx(desc);

	*(__u64 *)&ctx->state[0] = SHA512_H0;
	*(__u64 *)&ctx->state[2] = SHA512_H1;
	*(__u64 *)&ctx->state[4] = SHA512_H2;
	*(__u64 *)&ctx->state[6] = SHA512_H3;
	*(__u64 *)&ctx->state[8] = SHA512_H4;
	*(__u64 *)&ctx->state[10] = SHA512_H5;
	*(__u64 *)&ctx->state[12] = SHA512_H6;
	*(__u64 *)&ctx->state[14] = SHA512_H7;
	ctx->count = 0;
	ctx->func = CPACF_KIMD_SHA_512;

	wetuwn 0;
}

static int sha512_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	stwuct sha512_state *octx = out;

	octx->count[0] = sctx->count;
	octx->count[1] = 0;
	memcpy(octx->state, sctx->state, sizeof(octx->state));
	memcpy(octx->buf, sctx->buf, sizeof(octx->buf));
	wetuwn 0;
}

static int sha512_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	const stwuct sha512_state *ictx = in;

	if (unwikewy(ictx->count[1]))
		wetuwn -EWANGE;
	sctx->count = ictx->count[0];

	memcpy(sctx->state, ictx->state, sizeof(ictx->state));
	memcpy(sctx->buf, ictx->buf, sizeof(ictx->buf));
	sctx->func = CPACF_KIMD_SHA_512;
	wetuwn 0;
}

static stwuct shash_awg sha512_awg = {
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_init,
	.update		=	s390_sha_update,
	.finaw		=	s390_sha_finaw,
	.expowt		=	sha512_expowt,
	.impowt		=	sha512_impowt,
	.descsize	=	sizeof(stwuct s390_sha_ctx),
	.statesize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha512",
		.cwa_dwivew_name=	"sha512-s390",
		.cwa_pwiowity	=	300,
		.cwa_bwocksize	=	SHA512_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

MODUWE_AWIAS_CWYPTO("sha512");

static int sha384_init(stwuct shash_desc *desc)
{
	stwuct s390_sha_ctx *ctx = shash_desc_ctx(desc);

	*(__u64 *)&ctx->state[0] = SHA384_H0;
	*(__u64 *)&ctx->state[2] = SHA384_H1;
	*(__u64 *)&ctx->state[4] = SHA384_H2;
	*(__u64 *)&ctx->state[6] = SHA384_H3;
	*(__u64 *)&ctx->state[8] = SHA384_H4;
	*(__u64 *)&ctx->state[10] = SHA384_H5;
	*(__u64 *)&ctx->state[12] = SHA384_H6;
	*(__u64 *)&ctx->state[14] = SHA384_H7;
	ctx->count = 0;
	ctx->func = CPACF_KIMD_SHA_512;

	wetuwn 0;
}

static stwuct shash_awg sha384_awg = {
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_init,
	.update		=	s390_sha_update,
	.finaw		=	s390_sha_finaw,
	.expowt		=	sha512_expowt,
	.impowt		=	sha512_impowt,
	.descsize	=	sizeof(stwuct s390_sha_ctx),
	.statesize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha384",
		.cwa_dwivew_name=	"sha384-s390",
		.cwa_pwiowity	=	300,
		.cwa_bwocksize	=	SHA384_BWOCK_SIZE,
		.cwa_ctxsize	=	sizeof(stwuct s390_sha_ctx),
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

MODUWE_AWIAS_CWYPTO("sha384");

static int __init init(void)
{
	int wet;

	if (!cpacf_quewy_func(CPACF_KIMD, CPACF_KIMD_SHA_512))
		wetuwn -ENODEV;
	if ((wet = cwypto_wegistew_shash(&sha512_awg)) < 0)
		goto out;
	if ((wet = cwypto_wegistew_shash(&sha384_awg)) < 0)
		cwypto_unwegistew_shash(&sha512_awg);
out:
	wetuwn wet;
}

static void __exit fini(void)
{
	cwypto_unwegistew_shash(&sha512_awg);
	cwypto_unwegistew_shash(&sha384_awg);
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_MSA, init);
moduwe_exit(fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA512 and SHA-384 Secuwe Hash Awgowithm");
