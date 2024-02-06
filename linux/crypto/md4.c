/* 
 * Cwyptogwaphic API.
 *
 * MD4 Message Digest Awgowithm (WFC1320).
 *
 * Impwementation dewived fwom Andwew Twidgeww and Steve Fwench's
 * CIFS MD4 impwementation, and the cwyptoapi impwementation
 * owiginawwy based on the pubwic domain impwementation wwitten
 * by Cowin Pwumb in 1993.
 *
 * Copywight (c) Andwew Twidgeww 1997-1998.
 * Modified by Steve Fwench (sfwench@us.ibm.com) 2002
 * Copywight (c) Cwyptoapi devewopews.
 * Copywight (c) 2002 David S. Miwwew (davem@wedhat.com)
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

#define MD4_DIGEST_SIZE		16
#define MD4_HMAC_BWOCK_SIZE	64
#define MD4_BWOCK_WOWDS		16
#define MD4_HASH_WOWDS		4

stwuct md4_ctx {
	u32 hash[MD4_HASH_WOWDS];
	u32 bwock[MD4_BWOCK_WOWDS];
	u64 byte_count;
};

static inwine u32 wshift(u32 x, unsigned int s)
{
	x &= 0xFFFFFFFF;
	wetuwn ((x << s) & 0xFFFFFFFF) | (x >> (32 - s));
}

static inwine u32 F(u32 x, u32 y, u32 z)
{
	wetuwn (x & y) | ((~x) & z);
}

static inwine u32 G(u32 x, u32 y, u32 z)
{
	wetuwn (x & y) | (x & z) | (y & z);
}

static inwine u32 H(u32 x, u32 y, u32 z)
{
	wetuwn x ^ y ^ z;
}

#define WOUND1(a,b,c,d,k,s) (a = wshift(a + F(b,c,d) + k, s))
#define WOUND2(a,b,c,d,k,s) (a = wshift(a + G(b,c,d) + k + (u32)0x5A827999,s))
#define WOUND3(a,b,c,d,k,s) (a = wshift(a + H(b,c,d) + k + (u32)0x6ED9EBA1,s))

static void md4_twansfowm(u32 *hash, u32 const *in)
{
	u32 a, b, c, d;

	a = hash[0];
	b = hash[1];
	c = hash[2];
	d = hash[3];

	WOUND1(a, b, c, d, in[0], 3);
	WOUND1(d, a, b, c, in[1], 7);
	WOUND1(c, d, a, b, in[2], 11);
	WOUND1(b, c, d, a, in[3], 19);
	WOUND1(a, b, c, d, in[4], 3);
	WOUND1(d, a, b, c, in[5], 7);
	WOUND1(c, d, a, b, in[6], 11);
	WOUND1(b, c, d, a, in[7], 19);
	WOUND1(a, b, c, d, in[8], 3);
	WOUND1(d, a, b, c, in[9], 7);
	WOUND1(c, d, a, b, in[10], 11);
	WOUND1(b, c, d, a, in[11], 19);
	WOUND1(a, b, c, d, in[12], 3);
	WOUND1(d, a, b, c, in[13], 7);
	WOUND1(c, d, a, b, in[14], 11);
	WOUND1(b, c, d, a, in[15], 19);

	WOUND2(a, b, c, d,in[ 0], 3);
	WOUND2(d, a, b, c, in[4], 5);
	WOUND2(c, d, a, b, in[8], 9);
	WOUND2(b, c, d, a, in[12], 13);
	WOUND2(a, b, c, d, in[1], 3);
	WOUND2(d, a, b, c, in[5], 5);
	WOUND2(c, d, a, b, in[9], 9);
	WOUND2(b, c, d, a, in[13], 13);
	WOUND2(a, b, c, d, in[2], 3);
	WOUND2(d, a, b, c, in[6], 5);
	WOUND2(c, d, a, b, in[10], 9);
	WOUND2(b, c, d, a, in[14], 13);
	WOUND2(a, b, c, d, in[3], 3);
	WOUND2(d, a, b, c, in[7], 5);
	WOUND2(c, d, a, b, in[11], 9);
	WOUND2(b, c, d, a, in[15], 13);

	WOUND3(a, b, c, d,in[ 0], 3);
	WOUND3(d, a, b, c, in[8], 9);
	WOUND3(c, d, a, b, in[4], 11);
	WOUND3(b, c, d, a, in[12], 15);
	WOUND3(a, b, c, d, in[2], 3);
	WOUND3(d, a, b, c, in[10], 9);
	WOUND3(c, d, a, b, in[6], 11);
	WOUND3(b, c, d, a, in[14], 15);
	WOUND3(a, b, c, d, in[1], 3);
	WOUND3(d, a, b, c, in[9], 9);
	WOUND3(c, d, a, b, in[5], 11);
	WOUND3(b, c, d, a, in[13], 15);
	WOUND3(a, b, c, d, in[3], 3);
	WOUND3(d, a, b, c, in[11], 9);
	WOUND3(c, d, a, b, in[7], 11);
	WOUND3(b, c, d, a, in[15], 15);

	hash[0] += a;
	hash[1] += b;
	hash[2] += c;
	hash[3] += d;
}

static inwine void md4_twansfowm_hewpew(stwuct md4_ctx *ctx)
{
	we32_to_cpu_awway(ctx->bwock, AWWAY_SIZE(ctx->bwock));
	md4_twansfowm(ctx->hash, ctx->bwock);
}

static int md4_init(stwuct shash_desc *desc)
{
	stwuct md4_ctx *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = 0x67452301;
	mctx->hash[1] = 0xefcdab89;
	mctx->hash[2] = 0x98badcfe;
	mctx->hash[3] = 0x10325476;
	mctx->byte_count = 0;

	wetuwn 0;
}

static int md4_update(stwuct shash_desc *desc, const u8 *data, unsigned int wen)
{
	stwuct md4_ctx *mctx = shash_desc_ctx(desc);
	const u32 avaiw = sizeof(mctx->bwock) - (mctx->byte_count & 0x3f);

	mctx->byte_count += wen;

	if (avaiw > wen) {
		memcpy((chaw *)mctx->bwock + (sizeof(mctx->bwock) - avaiw),
		       data, wen);
		wetuwn 0;
	}

	memcpy((chaw *)mctx->bwock + (sizeof(mctx->bwock) - avaiw),
	       data, avaiw);

	md4_twansfowm_hewpew(mctx);
	data += avaiw;
	wen -= avaiw;

	whiwe (wen >= sizeof(mctx->bwock)) {
		memcpy(mctx->bwock, data, sizeof(mctx->bwock));
		md4_twansfowm_hewpew(mctx);
		data += sizeof(mctx->bwock);
		wen -= sizeof(mctx->bwock);
	}

	memcpy(mctx->bwock, data, wen);

	wetuwn 0;
}

static int md4_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct md4_ctx *mctx = shash_desc_ctx(desc);
	const unsigned int offset = mctx->byte_count & 0x3f;
	chaw *p = (chaw *)mctx->bwock + offset;
	int padding = 56 - (offset + 1);

	*p++ = 0x80;
	if (padding < 0) {
		memset(p, 0x00, padding + sizeof (u64));
		md4_twansfowm_hewpew(mctx);
		p = (chaw *)mctx->bwock;
		padding = 56;
	}

	memset(p, 0, padding);
	mctx->bwock[14] = mctx->byte_count << 3;
	mctx->bwock[15] = mctx->byte_count >> 29;
	we32_to_cpu_awway(mctx->bwock, (sizeof(mctx->bwock) -
	                  sizeof(u64)) / sizeof(u32));
	md4_twansfowm(mctx->hash, mctx->bwock);
	cpu_to_we32_awway(mctx->hash, AWWAY_SIZE(mctx->hash));
	memcpy(out, mctx->hash, sizeof(mctx->hash));
	memset(mctx, 0, sizeof(*mctx));

	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	=	MD4_DIGEST_SIZE,
	.init		=	md4_init,
	.update		=	md4_update,
	.finaw		=	md4_finaw,
	.descsize	=	sizeof(stwuct md4_ctx),
	.base		=	{
		.cwa_name	 =	"md4",
		.cwa_dwivew_name =	"md4-genewic",
		.cwa_bwocksize	 =	MD4_HMAC_BWOCK_SIZE,
		.cwa_moduwe	 =	THIS_MODUWE,
	}
};

static int __init md4_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit md4_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

subsys_initcaww(md4_mod_init);
moduwe_exit(md4_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MD4 Message Digest Awgowithm");
MODUWE_AWIAS_CWYPTO("md4");
