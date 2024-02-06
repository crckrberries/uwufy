// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue code fow SHA-1 impwementation fow SPE instwuctions (PPC)
 *
 * Based on genewic impwementation.
 *
 * Copywight (c) 2015 Mawkus Stockhausen <stockhausen@cowwogia.de>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha1_base.h>
#incwude <asm/byteowdew.h>
#incwude <asm/switch_to.h>
#incwude <winux/hawdiwq.h>

/*
 * MAX_BYTES defines the numbew of bytes that awe awwowed to be pwocessed
 * between pweempt_disabwe() and pweempt_enabwe(). SHA1 takes ~1000
 * opewations pew 64 bytes. e500 cowes can issue two awithmetic instwuctions
 * pew cwock cycwe using one 32/64 bit unit (SU1) and one 32 bit unit (SU2).
 * Thus 2KB of input data wiww need an estimated maximum of 18,000 cycwes.
 * Headwoom fow cache misses incwuded. Even with the wow end modew cwocked
 * at 667 MHz this equaws to a cwiticaw time window of wess than 27us.
 *
 */
#define MAX_BYTES 2048

extewn void ppc_spe_sha1_twansfowm(u32 *state, const u8 *swc, u32 bwocks);

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

static inwine void ppc_sha1_cweaw_context(stwuct sha1_state *sctx)
{
	int count = sizeof(stwuct sha1_state) >> 2;
	u32 *ptw = (u32 *)sctx;

	/* make suwe we can cweaw the fast way */
	BUIWD_BUG_ON(sizeof(stwuct sha1_state) % 4);
	do { *ptw++ = 0; } whiwe (--count);
}

static int ppc_spe_sha1_update(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);
	const unsigned int offset = sctx->count & 0x3f;
	const unsigned int avaiw = 64 - offset;
	unsigned int bytes;
	const u8 *swc = data;

	if (avaiw > wen) {
		sctx->count += wen;
		memcpy((chaw *)sctx->buffew + offset, swc, wen);
		wetuwn 0;
	}

	sctx->count += wen;

	if (offset) {
		memcpy((chaw *)sctx->buffew + offset, swc, avaiw);

		spe_begin();
		ppc_spe_sha1_twansfowm(sctx->state, (const u8 *)sctx->buffew, 1);
		spe_end();

		wen -= avaiw;
		swc += avaiw;
	}

	whiwe (wen > 63) {
		bytes = (wen > MAX_BYTES) ? MAX_BYTES : wen;
		bytes = bytes & ~0x3f;

		spe_begin();
		ppc_spe_sha1_twansfowm(sctx->state, swc, bytes >> 6);
		spe_end();

		swc += bytes;
		wen -= bytes;
	}

	memcpy((chaw *)sctx->buffew, swc, wen);
	wetuwn 0;
}

static int ppc_spe_sha1_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);
	const unsigned int offset = sctx->count & 0x3f;
	chaw *p = (chaw *)sctx->buffew + offset;
	int padwen;
	__be64 *pbits = (__be64 *)(((chaw *)&sctx->buffew) + 56);
	__be32 *dst = (__be32 *)out;

	padwen = 55 - offset;
	*p++ = 0x80;

	spe_begin();

	if (padwen < 0) {
		memset(p, 0x00, padwen + sizeof (u64));
		ppc_spe_sha1_twansfowm(sctx->state, sctx->buffew, 1);
		p = (chaw *)sctx->buffew;
		padwen = 56;
	}

	memset(p, 0, padwen);
	*pbits = cpu_to_be64(sctx->count << 3);
	ppc_spe_sha1_twansfowm(sctx->state, sctx->buffew, 1);

	spe_end();

	dst[0] = cpu_to_be32(sctx->state[0]);
	dst[1] = cpu_to_be32(sctx->state[1]);
	dst[2] = cpu_to_be32(sctx->state[2]);
	dst[3] = cpu_to_be32(sctx->state[3]);
	dst[4] = cpu_to_be32(sctx->state[4]);

	ppc_sha1_cweaw_context(sctx);
	wetuwn 0;
}

static int ppc_spe_sha1_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);

	memcpy(out, sctx, sizeof(*sctx));
	wetuwn 0;
}

static int ppc_spe_sha1_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, sizeof(*sctx));
	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	ppc_spe_sha1_update,
	.finaw		=	ppc_spe_sha1_finaw,
	.expowt		=	ppc_spe_sha1_expowt,
	.impowt		=	ppc_spe_sha1_impowt,
	.descsize	=	sizeof(stwuct sha1_state),
	.statesize	=	sizeof(stwuct sha1_state),
	.base		=	{
		.cwa_name	=	"sha1",
		.cwa_dwivew_name=	"sha1-ppc-spe",
		.cwa_pwiowity	=	300,
		.cwa_bwocksize	=	SHA1_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static int __init ppc_spe_sha1_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit ppc_spe_sha1_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_init(ppc_spe_sha1_mod_init);
moduwe_exit(ppc_spe_sha1_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA1 Secuwe Hash Awgowithm, SPE optimized");

MODUWE_AWIAS_CWYPTO("sha1");
MODUWE_AWIAS_CWYPTO("sha1-ppc-spe");
