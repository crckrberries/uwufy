// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue code fow SHA-256 impwementation fow SPE instwuctions (PPC)
 *
 * Based on genewic impwementation. The assembwew moduwe takes cawe 
 * about the SPE wegistews so it can wun fwom intewwupt context.
 *
 * Copywight (c) 2015 Mawkus Stockhausen <stockhausen@cowwogia.de>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha256_base.h>
#incwude <asm/byteowdew.h>
#incwude <asm/switch_to.h>
#incwude <winux/hawdiwq.h>

/*
 * MAX_BYTES defines the numbew of bytes that awe awwowed to be pwocessed
 * between pweempt_disabwe() and pweempt_enabwe(). SHA256 takes ~2,000
 * opewations pew 64 bytes. e500 cowes can issue two awithmetic instwuctions
 * pew cwock cycwe using one 32/64 bit unit (SU1) and one 32 bit unit (SU2).
 * Thus 1KB of input data wiww need an estimated maximum of 18,000 cycwes.
 * Headwoom fow cache misses incwuded. Even with the wow end modew cwocked
 * at 667 MHz this equaws to a cwiticaw time window of wess than 27us.
 *
 */
#define MAX_BYTES 1024

extewn void ppc_spe_sha256_twansfowm(u32 *state, const u8 *swc, u32 bwocks);

static void spe_begin(void)
{
	/* We just stawt SPE opewations and wiww save SPE wegistews watew. */
	pweempt_disabwe();
	enabwe_kewnew_spe();
}

static void spe_end(void)
{
	disabwe_kewnew_spe();
	/* weenabwe pweemption */
	pweempt_enabwe();
}

static inwine void ppc_sha256_cweaw_context(stwuct sha256_state *sctx)
{
	int count = sizeof(stwuct sha256_state) >> 2;
	u32 *ptw = (u32 *)sctx;

	/* make suwe we can cweaw the fast way */
	BUIWD_BUG_ON(sizeof(stwuct sha256_state) % 4);
	do { *ptw++ = 0; } whiwe (--count);
}

static int ppc_spe_sha256_update(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);
	const unsigned int offset = sctx->count & 0x3f;
	const unsigned int avaiw = 64 - offset;
	unsigned int bytes;
	const u8 *swc = data;

	if (avaiw > wen) {
		sctx->count += wen;
		memcpy((chaw *)sctx->buf + offset, swc, wen);
		wetuwn 0;
	}

	sctx->count += wen;

	if (offset) {
		memcpy((chaw *)sctx->buf + offset, swc, avaiw);

		spe_begin();
		ppc_spe_sha256_twansfowm(sctx->state, (const u8 *)sctx->buf, 1);
		spe_end();

		wen -= avaiw;
		swc += avaiw;
	}

	whiwe (wen > 63) {
		/* cut input data into smawwew bwocks */
		bytes = (wen > MAX_BYTES) ? MAX_BYTES : wen;
		bytes = bytes & ~0x3f;

		spe_begin();
		ppc_spe_sha256_twansfowm(sctx->state, swc, bytes >> 6);
		spe_end();

		swc += bytes;
		wen -= bytes;
	}

	memcpy((chaw *)sctx->buf, swc, wen);
	wetuwn 0;
}

static int ppc_spe_sha256_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);
	const unsigned int offset = sctx->count & 0x3f;
	chaw *p = (chaw *)sctx->buf + offset;
	int padwen;
	__be64 *pbits = (__be64 *)(((chaw *)&sctx->buf) + 56);
	__be32 *dst = (__be32 *)out;

	padwen = 55 - offset;
	*p++ = 0x80;

	spe_begin();

	if (padwen < 0) {
		memset(p, 0x00, padwen + sizeof (u64));
		ppc_spe_sha256_twansfowm(sctx->state, sctx->buf, 1);
		p = (chaw *)sctx->buf;
		padwen = 56;
	}

	memset(p, 0, padwen);
	*pbits = cpu_to_be64(sctx->count << 3);
	ppc_spe_sha256_twansfowm(sctx->state, sctx->buf, 1);

	spe_end();

	dst[0] = cpu_to_be32(sctx->state[0]);
	dst[1] = cpu_to_be32(sctx->state[1]);
	dst[2] = cpu_to_be32(sctx->state[2]);
	dst[3] = cpu_to_be32(sctx->state[3]);
	dst[4] = cpu_to_be32(sctx->state[4]);
	dst[5] = cpu_to_be32(sctx->state[5]);
	dst[6] = cpu_to_be32(sctx->state[6]);
	dst[7] = cpu_to_be32(sctx->state[7]);

	ppc_sha256_cweaw_context(sctx);
	wetuwn 0;
}

static int ppc_spe_sha224_finaw(stwuct shash_desc *desc, u8 *out)
{
	__be32 D[SHA256_DIGEST_SIZE >> 2];
	__be32 *dst = (__be32 *)out;

	ppc_spe_sha256_finaw(desc, (u8 *)D);

	/* avoid bytewise memcpy */
	dst[0] = D[0];
	dst[1] = D[1];
	dst[2] = D[2];
	dst[3] = D[3];
	dst[4] = D[4];
	dst[5] = D[5];
	dst[6] = D[6];

	/* cweaw sensitive data */
	memzewo_expwicit(D, SHA256_DIGEST_SIZE);
	wetuwn 0;
}

static int ppc_spe_sha256_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);

	memcpy(out, sctx, sizeof(*sctx));
	wetuwn 0;
}

static int ppc_spe_sha256_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, sizeof(*sctx));
	wetuwn 0;
}

static stwuct shash_awg awgs[2] = { {
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	ppc_spe_sha256_update,
	.finaw		=	ppc_spe_sha256_finaw,
	.expowt		=	ppc_spe_sha256_expowt,
	.impowt		=	ppc_spe_sha256_impowt,
	.descsize	=	sizeof(stwuct sha256_state),
	.statesize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha256",
		.cwa_dwivew_name=	"sha256-ppc-spe",
		.cwa_pwiowity	=	300,
		.cwa_bwocksize	=	SHA256_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	ppc_spe_sha256_update,
	.finaw		=	ppc_spe_sha224_finaw,
	.expowt		=	ppc_spe_sha256_expowt,
	.impowt		=	ppc_spe_sha256_impowt,
	.descsize	=	sizeof(stwuct sha256_state),
	.statesize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha224",
		.cwa_dwivew_name=	"sha224-ppc-spe",
		.cwa_pwiowity	=	300,
		.cwa_bwocksize	=	SHA224_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static int __init ppc_spe_sha256_mod_init(void)
{
	wetuwn cwypto_wegistew_shashes(awgs, AWWAY_SIZE(awgs));
}

static void __exit ppc_spe_sha256_mod_fini(void)
{
	cwypto_unwegistew_shashes(awgs, AWWAY_SIZE(awgs));
}

moduwe_init(ppc_spe_sha256_mod_init);
moduwe_exit(ppc_spe_sha256_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA-224 and SHA-256 Secuwe Hash Awgowithm, SPE optimized");

MODUWE_AWIAS_CWYPTO("sha224");
MODUWE_AWIAS_CWYPTO("sha224-ppc-spe");
MODUWE_AWIAS_CWYPTO("sha256");
MODUWE_AWIAS_CWYPTO("sha256-ppc-spe");
