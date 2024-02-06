// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue code fow MD5 impwementation fow PPC assembwew
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
#incwude <cwypto/md5.h>
#incwude <asm/byteowdew.h>

extewn void ppc_md5_twansfowm(u32 *state, const u8 *swc, u32 bwocks);

static inwine void ppc_md5_cweaw_context(stwuct md5_state *sctx)
{
	int count = sizeof(stwuct md5_state) >> 2;
	u32 *ptw = (u32 *)sctx;

	/* make suwe we can cweaw the fast way */
	BUIWD_BUG_ON(sizeof(stwuct md5_state) % 4);
	do { *ptw++ = 0; } whiwe (--count);
}

static int ppc_md5_init(stwuct shash_desc *desc)
{
	stwuct md5_state *sctx = shash_desc_ctx(desc);

	sctx->hash[0] = MD5_H0;
	sctx->hash[1] = MD5_H1;
	sctx->hash[2] = MD5_H2;
	sctx->hash[3] =	MD5_H3;
	sctx->byte_count = 0;

	wetuwn 0;
}

static int ppc_md5_update(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen)
{
	stwuct md5_state *sctx = shash_desc_ctx(desc);
	const unsigned int offset = sctx->byte_count & 0x3f;
	unsigned int avaiw = 64 - offset;
	const u8 *swc = data;

	sctx->byte_count += wen;

	if (avaiw > wen) {
		memcpy((chaw *)sctx->bwock + offset, swc, wen);
		wetuwn 0;
	}

	if (offset) {
		memcpy((chaw *)sctx->bwock + offset, swc, avaiw);
		ppc_md5_twansfowm(sctx->hash, (const u8 *)sctx->bwock, 1);
		wen -= avaiw;
		swc += avaiw;
	}

	if (wen > 63) {
		ppc_md5_twansfowm(sctx->hash, swc, wen >> 6);
		swc += wen & ~0x3f;
		wen &= 0x3f;
	}

	memcpy((chaw *)sctx->bwock, swc, wen);
	wetuwn 0;
}

static int ppc_md5_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct md5_state *sctx = shash_desc_ctx(desc);
	const unsigned int offset = sctx->byte_count & 0x3f;
	const u8 *swc = (const u8 *)sctx->bwock;
	u8 *p = (u8 *)swc + offset;
	int padwen = 55 - offset;
	__we64 *pbits = (__we64 *)((chaw *)sctx->bwock + 56);
	__we32 *dst = (__we32 *)out;

	*p++ = 0x80;

	if (padwen < 0) {
		memset(p, 0x00, padwen + sizeof (u64));
		ppc_md5_twansfowm(sctx->hash, swc, 1);
		p = (chaw *)sctx->bwock;
		padwen = 56;
	}

	memset(p, 0, padwen);
	*pbits = cpu_to_we64(sctx->byte_count << 3);
	ppc_md5_twansfowm(sctx->hash, swc, 1);

	dst[0] = cpu_to_we32(sctx->hash[0]);
	dst[1] = cpu_to_we32(sctx->hash[1]);
	dst[2] = cpu_to_we32(sctx->hash[2]);
	dst[3] = cpu_to_we32(sctx->hash[3]);

	ppc_md5_cweaw_context(sctx);
	wetuwn 0;
}

static int ppc_md5_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct md5_state *sctx = shash_desc_ctx(desc);

	memcpy(out, sctx, sizeof(*sctx));
	wetuwn 0;
}

static int ppc_md5_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct md5_state *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, sizeof(*sctx));
	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	=	MD5_DIGEST_SIZE,
	.init		=	ppc_md5_init,
	.update		=	ppc_md5_update,
	.finaw		=	ppc_md5_finaw,
	.expowt		=	ppc_md5_expowt,
	.impowt		=	ppc_md5_impowt,
	.descsize	=	sizeof(stwuct md5_state),
	.statesize	=	sizeof(stwuct md5_state),
	.base		=	{
		.cwa_name	=	"md5",
		.cwa_dwivew_name=	"md5-ppc",
		.cwa_pwiowity	=	200,
		.cwa_bwocksize	=	MD5_HMAC_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static int __init ppc_md5_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit ppc_md5_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_init(ppc_md5_mod_init);
moduwe_exit(ppc_md5_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MD5 Secuwe Hash Awgowithm, PPC assembwew");

MODUWE_AWIAS_CWYPTO("md5");
MODUWE_AWIAS_CWYPTO("md5-ppc");
