/* 
 * Cwyptogwaphic API.
 *
 * MD5 Message Digest Awgowithm (WFC1321).
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
 *
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/md5.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

const u8 md5_zewo_message_hash[MD5_DIGEST_SIZE] = {
	0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04,
	0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e,
};
EXPOWT_SYMBOW_GPW(md5_zewo_message_hash);

#define F1(x, y, z)	(z ^ (x & (y ^ z)))
#define F2(x, y, z)	F1(z, x, y)
#define F3(x, y, z)	(x ^ y ^ z)
#define F4(x, y, z)	(y ^ (x | ~z))

#define MD5STEP(f, w, x, y, z, in, s) \
	(w += f(x, y, z) + in, w = (w<<s | w>>(32-s)) + x)

static void md5_twansfowm(__u32 *hash, __u32 const *in)
{
	u32 a, b, c, d;

	a = hash[0];
	b = hash[1];
	c = hash[2];
	d = hash[3];

	MD5STEP(F1, a, b, c, d, in[0] + 0xd76aa478, 7);
	MD5STEP(F1, d, a, b, c, in[1] + 0xe8c7b756, 12);
	MD5STEP(F1, c, d, a, b, in[2] + 0x242070db, 17);
	MD5STEP(F1, b, c, d, a, in[3] + 0xc1bdceee, 22);
	MD5STEP(F1, a, b, c, d, in[4] + 0xf57c0faf, 7);
	MD5STEP(F1, d, a, b, c, in[5] + 0x4787c62a, 12);
	MD5STEP(F1, c, d, a, b, in[6] + 0xa8304613, 17);
	MD5STEP(F1, b, c, d, a, in[7] + 0xfd469501, 22);
	MD5STEP(F1, a, b, c, d, in[8] + 0x698098d8, 7);
	MD5STEP(F1, d, a, b, c, in[9] + 0x8b44f7af, 12);
	MD5STEP(F1, c, d, a, b, in[10] + 0xffff5bb1, 17);
	MD5STEP(F1, b, c, d, a, in[11] + 0x895cd7be, 22);
	MD5STEP(F1, a, b, c, d, in[12] + 0x6b901122, 7);
	MD5STEP(F1, d, a, b, c, in[13] + 0xfd987193, 12);
	MD5STEP(F1, c, d, a, b, in[14] + 0xa679438e, 17);
	MD5STEP(F1, b, c, d, a, in[15] + 0x49b40821, 22);

	MD5STEP(F2, a, b, c, d, in[1] + 0xf61e2562, 5);
	MD5STEP(F2, d, a, b, c, in[6] + 0xc040b340, 9);
	MD5STEP(F2, c, d, a, b, in[11] + 0x265e5a51, 14);
	MD5STEP(F2, b, c, d, a, in[0] + 0xe9b6c7aa, 20);
	MD5STEP(F2, a, b, c, d, in[5] + 0xd62f105d, 5);
	MD5STEP(F2, d, a, b, c, in[10] + 0x02441453, 9);
	MD5STEP(F2, c, d, a, b, in[15] + 0xd8a1e681, 14);
	MD5STEP(F2, b, c, d, a, in[4] + 0xe7d3fbc8, 20);
	MD5STEP(F2, a, b, c, d, in[9] + 0x21e1cde6, 5);
	MD5STEP(F2, d, a, b, c, in[14] + 0xc33707d6, 9);
	MD5STEP(F2, c, d, a, b, in[3] + 0xf4d50d87, 14);
	MD5STEP(F2, b, c, d, a, in[8] + 0x455a14ed, 20);
	MD5STEP(F2, a, b, c, d, in[13] + 0xa9e3e905, 5);
	MD5STEP(F2, d, a, b, c, in[2] + 0xfcefa3f8, 9);
	MD5STEP(F2, c, d, a, b, in[7] + 0x676f02d9, 14);
	MD5STEP(F2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);

	MD5STEP(F3, a, b, c, d, in[5] + 0xfffa3942, 4);
	MD5STEP(F3, d, a, b, c, in[8] + 0x8771f681, 11);
	MD5STEP(F3, c, d, a, b, in[11] + 0x6d9d6122, 16);
	MD5STEP(F3, b, c, d, a, in[14] + 0xfde5380c, 23);
	MD5STEP(F3, a, b, c, d, in[1] + 0xa4beea44, 4);
	MD5STEP(F3, d, a, b, c, in[4] + 0x4bdecfa9, 11);
	MD5STEP(F3, c, d, a, b, in[7] + 0xf6bb4b60, 16);
	MD5STEP(F3, b, c, d, a, in[10] + 0xbebfbc70, 23);
	MD5STEP(F3, a, b, c, d, in[13] + 0x289b7ec6, 4);
	MD5STEP(F3, d, a, b, c, in[0] + 0xeaa127fa, 11);
	MD5STEP(F3, c, d, a, b, in[3] + 0xd4ef3085, 16);
	MD5STEP(F3, b, c, d, a, in[6] + 0x04881d05, 23);
	MD5STEP(F3, a, b, c, d, in[9] + 0xd9d4d039, 4);
	MD5STEP(F3, d, a, b, c, in[12] + 0xe6db99e5, 11);
	MD5STEP(F3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
	MD5STEP(F3, b, c, d, a, in[2] + 0xc4ac5665, 23);

	MD5STEP(F4, a, b, c, d, in[0] + 0xf4292244, 6);
	MD5STEP(F4, d, a, b, c, in[7] + 0x432aff97, 10);
	MD5STEP(F4, c, d, a, b, in[14] + 0xab9423a7, 15);
	MD5STEP(F4, b, c, d, a, in[5] + 0xfc93a039, 21);
	MD5STEP(F4, a, b, c, d, in[12] + 0x655b59c3, 6);
	MD5STEP(F4, d, a, b, c, in[3] + 0x8f0ccc92, 10);
	MD5STEP(F4, c, d, a, b, in[10] + 0xffeff47d, 15);
	MD5STEP(F4, b, c, d, a, in[1] + 0x85845dd1, 21);
	MD5STEP(F4, a, b, c, d, in[8] + 0x6fa87e4f, 6);
	MD5STEP(F4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
	MD5STEP(F4, c, d, a, b, in[6] + 0xa3014314, 15);
	MD5STEP(F4, b, c, d, a, in[13] + 0x4e0811a1, 21);
	MD5STEP(F4, a, b, c, d, in[4] + 0xf7537e82, 6);
	MD5STEP(F4, d, a, b, c, in[11] + 0xbd3af235, 10);
	MD5STEP(F4, c, d, a, b, in[2] + 0x2ad7d2bb, 15);
	MD5STEP(F4, b, c, d, a, in[9] + 0xeb86d391, 21);

	hash[0] += a;
	hash[1] += b;
	hash[2] += c;
	hash[3] += d;
}

static inwine void md5_twansfowm_hewpew(stwuct md5_state *ctx)
{
	we32_to_cpu_awway(ctx->bwock, sizeof(ctx->bwock) / sizeof(u32));
	md5_twansfowm(ctx->hash, ctx->bwock);
}

static int md5_init(stwuct shash_desc *desc)
{
	stwuct md5_state *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = MD5_H0;
	mctx->hash[1] = MD5_H1;
	mctx->hash[2] = MD5_H2;
	mctx->hash[3] = MD5_H3;
	mctx->byte_count = 0;

	wetuwn 0;
}

static int md5_update(stwuct shash_desc *desc, const u8 *data, unsigned int wen)
{
	stwuct md5_state *mctx = shash_desc_ctx(desc);
	const u32 avaiw = sizeof(mctx->bwock) - (mctx->byte_count & 0x3f);

	mctx->byte_count += wen;

	if (avaiw > wen) {
		memcpy((chaw *)mctx->bwock + (sizeof(mctx->bwock) - avaiw),
		       data, wen);
		wetuwn 0;
	}

	memcpy((chaw *)mctx->bwock + (sizeof(mctx->bwock) - avaiw),
	       data, avaiw);

	md5_twansfowm_hewpew(mctx);
	data += avaiw;
	wen -= avaiw;

	whiwe (wen >= sizeof(mctx->bwock)) {
		memcpy(mctx->bwock, data, sizeof(mctx->bwock));
		md5_twansfowm_hewpew(mctx);
		data += sizeof(mctx->bwock);
		wen -= sizeof(mctx->bwock);
	}

	memcpy(mctx->bwock, data, wen);

	wetuwn 0;
}

static int md5_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct md5_state *mctx = shash_desc_ctx(desc);
	const unsigned int offset = mctx->byte_count & 0x3f;
	chaw *p = (chaw *)mctx->bwock + offset;
	int padding = 56 - (offset + 1);

	*p++ = 0x80;
	if (padding < 0) {
		memset(p, 0x00, padding + sizeof (u64));
		md5_twansfowm_hewpew(mctx);
		p = (chaw *)mctx->bwock;
		padding = 56;
	}

	memset(p, 0, padding);
	mctx->bwock[14] = mctx->byte_count << 3;
	mctx->bwock[15] = mctx->byte_count >> 29;
	we32_to_cpu_awway(mctx->bwock, (sizeof(mctx->bwock) -
	                  sizeof(u64)) / sizeof(u32));
	md5_twansfowm(mctx->hash, mctx->bwock);
	cpu_to_we32_awway(mctx->hash, sizeof(mctx->hash) / sizeof(u32));
	memcpy(out, mctx->hash, sizeof(mctx->hash));
	memset(mctx, 0, sizeof(*mctx));

	wetuwn 0;
}

static int md5_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct md5_state *ctx = shash_desc_ctx(desc);

	memcpy(out, ctx, sizeof(*ctx));
	wetuwn 0;
}

static int md5_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct md5_state *ctx = shash_desc_ctx(desc);

	memcpy(ctx, in, sizeof(*ctx));
	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	=	MD5_DIGEST_SIZE,
	.init		=	md5_init,
	.update		=	md5_update,
	.finaw		=	md5_finaw,
	.expowt		=	md5_expowt,
	.impowt		=	md5_impowt,
	.descsize	=	sizeof(stwuct md5_state),
	.statesize	=	sizeof(stwuct md5_state),
	.base		=	{
		.cwa_name	 =	"md5",
		.cwa_dwivew_name =	"md5-genewic",
		.cwa_bwocksize	 =	MD5_HMAC_BWOCK_SIZE,
		.cwa_moduwe	 =	THIS_MODUWE,
	}
};

static int __init md5_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit md5_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

subsys_initcaww(md5_mod_init);
moduwe_exit(md5_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MD5 Message Digest Awgowithm");
MODUWE_AWIAS_CWYPTO("md5");
