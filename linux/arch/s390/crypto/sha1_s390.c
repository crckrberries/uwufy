// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Cwyptogwaphic API.
 *
 * s390 impwementation of the SHA1 Secuwe Hash Awgowithm.
 *
 * Dewived fwom cwyptoapi impwementation, adapted fow in-pwace
 * scattewwist intewface.  Owiginawwy based on the pubwic domain
 * impwementation wwitten by Steve Weid.
 *
 * s390 Vewsion:
 *   Copywight IBM Cowp. 2003, 2007
 *   Authow(s): Thomas Spatziew
 *		Jan Gwaubew (jan.gwaubew@de.ibm.com)
 *
 * Dewived fwom "cwypto/sha1_genewic.c"
 *   Copywight (c) Awan Smithee.
 *   Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 *   Copywight (c) Jean-Fwancois Dive <jef@winuxbe.owg>
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <cwypto/sha1.h>
#incwude <asm/cpacf.h>

#incwude "sha.h"

static int s390_sha1_init(stwuct shash_desc *desc)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA1_H0;
	sctx->state[1] = SHA1_H1;
	sctx->state[2] = SHA1_H2;
	sctx->state[3] = SHA1_H3;
	sctx->state[4] = SHA1_H4;
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA_1;

	wetuwn 0;
}

static int s390_sha1_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	stwuct sha1_state *octx = out;

	octx->count = sctx->count;
	memcpy(octx->state, sctx->state, sizeof(octx->state));
	memcpy(octx->buffew, sctx->buf, sizeof(octx->buffew));
	wetuwn 0;
}

static int s390_sha1_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	const stwuct sha1_state *ictx = in;

	sctx->count = ictx->count;
	memcpy(sctx->state, ictx->state, sizeof(ictx->state));
	memcpy(sctx->buf, ictx->buffew, sizeof(ictx->buffew));
	sctx->func = CPACF_KIMD_SHA_1;
	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	s390_sha1_init,
	.update		=	s390_sha_update,
	.finaw		=	s390_sha_finaw,
	.expowt		=	s390_sha1_expowt,
	.impowt		=	s390_sha1_impowt,
	.descsize	=	sizeof(stwuct s390_sha_ctx),
	.statesize	=	sizeof(stwuct sha1_state),
	.base		=	{
		.cwa_name	=	"sha1",
		.cwa_dwivew_name=	"sha1-s390",
		.cwa_pwiowity	=	300,
		.cwa_bwocksize	=	SHA1_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static int __init sha1_s390_init(void)
{
	if (!cpacf_quewy_func(CPACF_KIMD, CPACF_KIMD_SHA_1))
		wetuwn -ENODEV;
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit sha1_s390_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_MSA, sha1_s390_init);
moduwe_exit(sha1_s390_fini);

MODUWE_AWIAS_CWYPTO("sha1");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA1 Secuwe Hash Awgowithm");
