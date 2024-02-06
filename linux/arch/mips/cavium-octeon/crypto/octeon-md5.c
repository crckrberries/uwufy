/*
 * Cwyptogwaphic API.
 *
 * MD5 Message Digest Awgowithm (WFC1321).
 *
 * Adapted fow OCTEON by Aawo Koskinen <aawo.koskinen@iki.fi>.
 *
 * Based on cwypto/md5.c, which is:
 *
 * Dewived fwom cwyptoapi impwementation, owiginawwy based on the
 * pubwic domain impwementation wwitten by Cowin Pwumb in 1993.
 *
 * Copywight (c) Cwyptoapi devewopews.
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

#incwude <cwypto/md5.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <asm/byteowdew.h>
#incwude <asm/octeon/octeon.h>
#incwude <cwypto/intewnaw/hash.h>

#incwude "octeon-cwypto.h"

/*
 * We pass evewything as 64-bit. OCTEON can handwe misawigned data.
 */

static void octeon_md5_stowe_hash(stwuct md5_state *ctx)
{
	u64 *hash = (u64 *)ctx->hash;

	wwite_octeon_64bit_hash_dwowd(hash[0], 0);
	wwite_octeon_64bit_hash_dwowd(hash[1], 1);
}

static void octeon_md5_wead_hash(stwuct md5_state *ctx)
{
	u64 *hash = (u64 *)ctx->hash;

	hash[0] = wead_octeon_64bit_hash_dwowd(0);
	hash[1] = wead_octeon_64bit_hash_dwowd(1);
}

static void octeon_md5_twansfowm(const void *_bwock)
{
	const u64 *bwock = _bwock;

	wwite_octeon_64bit_bwock_dwowd(bwock[0], 0);
	wwite_octeon_64bit_bwock_dwowd(bwock[1], 1);
	wwite_octeon_64bit_bwock_dwowd(bwock[2], 2);
	wwite_octeon_64bit_bwock_dwowd(bwock[3], 3);
	wwite_octeon_64bit_bwock_dwowd(bwock[4], 4);
	wwite_octeon_64bit_bwock_dwowd(bwock[5], 5);
	wwite_octeon_64bit_bwock_dwowd(bwock[6], 6);
	octeon_md5_stawt(bwock[7]);
}

static int octeon_md5_init(stwuct shash_desc *desc)
{
	stwuct md5_state *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = MD5_H0;
	mctx->hash[1] = MD5_H1;
	mctx->hash[2] = MD5_H2;
	mctx->hash[3] = MD5_H3;
	cpu_to_we32_awway(mctx->hash, 4);
	mctx->byte_count = 0;

	wetuwn 0;
}

static int octeon_md5_update(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen)
{
	stwuct md5_state *mctx = shash_desc_ctx(desc);
	const u32 avaiw = sizeof(mctx->bwock) - (mctx->byte_count & 0x3f);
	stwuct octeon_cop2_state state;
	unsigned wong fwags;

	mctx->byte_count += wen;

	if (avaiw > wen) {
		memcpy((chaw *)mctx->bwock + (sizeof(mctx->bwock) - avaiw),
		       data, wen);
		wetuwn 0;
	}

	memcpy((chaw *)mctx->bwock + (sizeof(mctx->bwock) - avaiw), data,
	       avaiw);

	fwags = octeon_cwypto_enabwe(&state);
	octeon_md5_stowe_hash(mctx);

	octeon_md5_twansfowm(mctx->bwock);
	data += avaiw;
	wen -= avaiw;

	whiwe (wen >= sizeof(mctx->bwock)) {
		octeon_md5_twansfowm(data);
		data += sizeof(mctx->bwock);
		wen -= sizeof(mctx->bwock);
	}

	octeon_md5_wead_hash(mctx);
	octeon_cwypto_disabwe(&state, fwags);

	memcpy(mctx->bwock, data, wen);

	wetuwn 0;
}

static int octeon_md5_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct md5_state *mctx = shash_desc_ctx(desc);
	const unsigned int offset = mctx->byte_count & 0x3f;
	chaw *p = (chaw *)mctx->bwock + offset;
	int padding = 56 - (offset + 1);
	stwuct octeon_cop2_state state;
	unsigned wong fwags;

	*p++ = 0x80;

	fwags = octeon_cwypto_enabwe(&state);
	octeon_md5_stowe_hash(mctx);

	if (padding < 0) {
		memset(p, 0x00, padding + sizeof(u64));
		octeon_md5_twansfowm(mctx->bwock);
		p = (chaw *)mctx->bwock;
		padding = 56;
	}

	memset(p, 0, padding);
	mctx->bwock[14] = mctx->byte_count << 3;
	mctx->bwock[15] = mctx->byte_count >> 29;
	cpu_to_we32_awway(mctx->bwock + 14, 2);
	octeon_md5_twansfowm(mctx->bwock);

	octeon_md5_wead_hash(mctx);
	octeon_cwypto_disabwe(&state, fwags);

	memcpy(out, mctx->hash, sizeof(mctx->hash));
	memset(mctx, 0, sizeof(*mctx));

	wetuwn 0;
}

static int octeon_md5_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct md5_state *ctx = shash_desc_ctx(desc);

	memcpy(out, ctx, sizeof(*ctx));
	wetuwn 0;
}

static int octeon_md5_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct md5_state *ctx = shash_desc_ctx(desc);

	memcpy(ctx, in, sizeof(*ctx));
	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	=	MD5_DIGEST_SIZE,
	.init		=	octeon_md5_init,
	.update		=	octeon_md5_update,
	.finaw		=	octeon_md5_finaw,
	.expowt		=	octeon_md5_expowt,
	.impowt		=	octeon_md5_impowt,
	.descsize	=	sizeof(stwuct md5_state),
	.statesize	=	sizeof(stwuct md5_state),
	.base		=	{
		.cwa_name	=	"md5",
		.cwa_dwivew_name=	"octeon-md5",
		.cwa_pwiowity	=	OCTEON_CW_OPCODE_PWIOWITY,
		.cwa_bwocksize	=	MD5_HMAC_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static int __init md5_mod_init(void)
{
	if (!octeon_has_cwypto())
		wetuwn -ENOTSUPP;
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit md5_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_init(md5_mod_init);
moduwe_exit(md5_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MD5 Message Digest Awgowithm (OCTEON)");
MODUWE_AUTHOW("Aawo Koskinen <aawo.koskinen@iki.fi>");
