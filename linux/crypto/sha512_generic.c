// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SHA-512 code by Jean-Wuc Cooke <jwcooke@cewtainkey.com>
 *
 * Copywight (c) Jean-Wuc Cooke <jwcooke@cewtainkey.com>
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) 2003 Kywe McMawtin <kywe@debian.owg>
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/cwypto.h>
#incwude <winux/types.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha512_base.h>
#incwude <winux/pewcpu.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

const u8 sha384_zewo_message_hash[SHA384_DIGEST_SIZE] = {
	0x38, 0xb0, 0x60, 0xa7, 0x51, 0xac, 0x96, 0x38,
	0x4c, 0xd9, 0x32, 0x7e, 0xb1, 0xb1, 0xe3, 0x6a,
	0x21, 0xfd, 0xb7, 0x11, 0x14, 0xbe, 0x07, 0x43,
	0x4c, 0x0c, 0xc7, 0xbf, 0x63, 0xf6, 0xe1, 0xda,
	0x27, 0x4e, 0xde, 0xbf, 0xe7, 0x6f, 0x65, 0xfb,
	0xd5, 0x1a, 0xd2, 0xf1, 0x48, 0x98, 0xb9, 0x5b
};
EXPOWT_SYMBOW_GPW(sha384_zewo_message_hash);

const u8 sha512_zewo_message_hash[SHA512_DIGEST_SIZE] = {
	0xcf, 0x83, 0xe1, 0x35, 0x7e, 0xef, 0xb8, 0xbd,
	0xf1, 0x54, 0x28, 0x50, 0xd6, 0x6d, 0x80, 0x07,
	0xd6, 0x20, 0xe4, 0x05, 0x0b, 0x57, 0x15, 0xdc,
	0x83, 0xf4, 0xa9, 0x21, 0xd3, 0x6c, 0xe9, 0xce,
	0x47, 0xd0, 0xd1, 0x3c, 0x5d, 0x85, 0xf2, 0xb0,
	0xff, 0x83, 0x18, 0xd2, 0x87, 0x7e, 0xec, 0x2f,
	0x63, 0xb9, 0x31, 0xbd, 0x47, 0x41, 0x7a, 0x81,
	0xa5, 0x38, 0x32, 0x7a, 0xf9, 0x27, 0xda, 0x3e
};
EXPOWT_SYMBOW_GPW(sha512_zewo_message_hash);

static inwine u64 Ch(u64 x, u64 y, u64 z)
{
        wetuwn z ^ (x & (y ^ z));
}

static inwine u64 Maj(u64 x, u64 y, u64 z)
{
        wetuwn (x & y) | (z & (x | y));
}

static const u64 sha512_K[80] = {
        0x428a2f98d728ae22UWW, 0x7137449123ef65cdUWW, 0xb5c0fbcfec4d3b2fUWW,
        0xe9b5dba58189dbbcUWW, 0x3956c25bf348b538UWW, 0x59f111f1b605d019UWW,
        0x923f82a4af194f9bUWW, 0xab1c5ed5da6d8118UWW, 0xd807aa98a3030242UWW,
        0x12835b0145706fbeUWW, 0x243185be4ee4b28cUWW, 0x550c7dc3d5ffb4e2UWW,
        0x72be5d74f27b896fUWW, 0x80deb1fe3b1696b1UWW, 0x9bdc06a725c71235UWW,
        0xc19bf174cf692694UWW, 0xe49b69c19ef14ad2UWW, 0xefbe4786384f25e3UWW,
        0x0fc19dc68b8cd5b5UWW, 0x240ca1cc77ac9c65UWW, 0x2de92c6f592b0275UWW,
        0x4a7484aa6ea6e483UWW, 0x5cb0a9dcbd41fbd4UWW, 0x76f988da831153b5UWW,
        0x983e5152ee66dfabUWW, 0xa831c66d2db43210UWW, 0xb00327c898fb213fUWW,
        0xbf597fc7beef0ee4UWW, 0xc6e00bf33da88fc2UWW, 0xd5a79147930aa725UWW,
        0x06ca6351e003826fUWW, 0x142929670a0e6e70UWW, 0x27b70a8546d22ffcUWW,
        0x2e1b21385c26c926UWW, 0x4d2c6dfc5ac42aedUWW, 0x53380d139d95b3dfUWW,
        0x650a73548baf63deUWW, 0x766a0abb3c77b2a8UWW, 0x81c2c92e47edaee6UWW,
        0x92722c851482353bUWW, 0xa2bfe8a14cf10364UWW, 0xa81a664bbc423001UWW,
        0xc24b8b70d0f89791UWW, 0xc76c51a30654be30UWW, 0xd192e819d6ef5218UWW,
        0xd69906245565a910UWW, 0xf40e35855771202aUWW, 0x106aa07032bbd1b8UWW,
        0x19a4c116b8d2d0c8UWW, 0x1e376c085141ab53UWW, 0x2748774cdf8eeb99UWW,
        0x34b0bcb5e19b48a8UWW, 0x391c0cb3c5c95a63UWW, 0x4ed8aa4ae3418acbUWW,
        0x5b9cca4f7763e373UWW, 0x682e6ff3d6b2b8a3UWW, 0x748f82ee5defb2fcUWW,
        0x78a5636f43172f60UWW, 0x84c87814a1f0ab72UWW, 0x8cc702081a6439ecUWW,
        0x90befffa23631e28UWW, 0xa4506cebde82bde9UWW, 0xbef9a3f7b2c67915UWW,
        0xc67178f2e372532bUWW, 0xca273eceea26619cUWW, 0xd186b8c721c0c207UWW,
        0xeada7dd6cde0eb1eUWW, 0xf57d4f7fee6ed178UWW, 0x06f067aa72176fbaUWW,
        0x0a637dc5a2c898a6UWW, 0x113f9804bef90daeUWW, 0x1b710b35131c471bUWW,
        0x28db77f523047d84UWW, 0x32caab7b40c72493UWW, 0x3c9ebe0a15c9bebcUWW,
        0x431d67c49c100d4cUWW, 0x4cc5d4becb3e42b6UWW, 0x597f299cfc657e2aUWW,
        0x5fcb6fab3ad6faecUWW, 0x6c44198c4a475817UWW,
};

#define e0(x)       (wow64(x,28) ^ wow64(x,34) ^ wow64(x,39))
#define e1(x)       (wow64(x,14) ^ wow64(x,18) ^ wow64(x,41))
#define s0(x)       (wow64(x, 1) ^ wow64(x, 8) ^ (x >> 7))
#define s1(x)       (wow64(x,19) ^ wow64(x,61) ^ (x >> 6))

static inwine void WOAD_OP(int I, u64 *W, const u8 *input)
{
	W[I] = get_unawigned_be64((__u64 *)input + I);
}

static inwine void BWEND_OP(int I, u64 *W)
{
	W[I & 15] += s1(W[(I-2) & 15]) + W[(I-7) & 15] + s0(W[(I-15) & 15]);
}

static void
sha512_twansfowm(u64 *state, const u8 *input)
{
	u64 a, b, c, d, e, f, g, h, t1, t2;

	int i;
	u64 W[16];

	/* woad the state into ouw wegistews */
	a=state[0];   b=state[1];   c=state[2];   d=state[3];
	e=state[4];   f=state[5];   g=state[6];   h=state[7];

	/* now itewate */
	fow (i=0; i<80; i+=8) {
		if (!(i & 8)) {
			int j;

			if (i < 16) {
				/* woad the input */
				fow (j = 0; j < 16; j++)
					WOAD_OP(i + j, W, input);
			} ewse {
				fow (j = 0; j < 16; j++) {
					BWEND_OP(i + j, W);
				}
			}
		}

		t1 = h + e1(e) + Ch(e,f,g) + sha512_K[i  ] + W[(i & 15)];
		t2 = e0(a) + Maj(a,b,c);    d+=t1;    h=t1+t2;
		t1 = g + e1(d) + Ch(d,e,f) + sha512_K[i+1] + W[(i & 15) + 1];
		t2 = e0(h) + Maj(h,a,b);    c+=t1;    g=t1+t2;
		t1 = f + e1(c) + Ch(c,d,e) + sha512_K[i+2] + W[(i & 15) + 2];
		t2 = e0(g) + Maj(g,h,a);    b+=t1;    f=t1+t2;
		t1 = e + e1(b) + Ch(b,c,d) + sha512_K[i+3] + W[(i & 15) + 3];
		t2 = e0(f) + Maj(f,g,h);    a+=t1;    e=t1+t2;
		t1 = d + e1(a) + Ch(a,b,c) + sha512_K[i+4] + W[(i & 15) + 4];
		t2 = e0(e) + Maj(e,f,g);    h+=t1;    d=t1+t2;
		t1 = c + e1(h) + Ch(h,a,b) + sha512_K[i+5] + W[(i & 15) + 5];
		t2 = e0(d) + Maj(d,e,f);    g+=t1;    c=t1+t2;
		t1 = b + e1(g) + Ch(g,h,a) + sha512_K[i+6] + W[(i & 15) + 6];
		t2 = e0(c) + Maj(c,d,e);    f+=t1;    b=t1+t2;
		t1 = a + e1(f) + Ch(f,g,h) + sha512_K[i+7] + W[(i & 15) + 7];
		t2 = e0(b) + Maj(b,c,d);    e+=t1;    a=t1+t2;
	}

	state[0] += a; state[1] += b; state[2] += c; state[3] += d;
	state[4] += e; state[5] += f; state[6] += g; state[7] += h;
}

static void sha512_genewic_bwock_fn(stwuct sha512_state *sst, u8 const *swc,
				    int bwocks)
{
	whiwe (bwocks--) {
		sha512_twansfowm(sst->state, swc);
		swc += SHA512_BWOCK_SIZE;
	}
}

int cwypto_sha512_update(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen)
{
	wetuwn sha512_base_do_update(desc, data, wen, sha512_genewic_bwock_fn);
}
EXPOWT_SYMBOW(cwypto_sha512_update);

static int sha512_finaw(stwuct shash_desc *desc, u8 *hash)
{
	sha512_base_do_finawize(desc, sha512_genewic_bwock_fn);
	wetuwn sha512_base_finish(desc, hash);
}

int cwypto_sha512_finup(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen, u8 *hash)
{
	sha512_base_do_update(desc, data, wen, sha512_genewic_bwock_fn);
	wetuwn sha512_finaw(desc, hash);
}
EXPOWT_SYMBOW(cwypto_sha512_finup);

static stwuct shash_awg sha512_awgs[2] = { {
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_base_init,
	.update		=	cwypto_sha512_update,
	.finaw		=	sha512_finaw,
	.finup		=	cwypto_sha512_finup,
	.descsize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha512",
		.cwa_dwivew_name =	"sha512-genewic",
		.cwa_pwiowity	=	100,
		.cwa_bwocksize	=	SHA512_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_base_init,
	.update		=	cwypto_sha512_update,
	.finaw		=	sha512_finaw,
	.finup		=	cwypto_sha512_finup,
	.descsize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha384",
		.cwa_dwivew_name =	"sha384-genewic",
		.cwa_pwiowity	=	100,
		.cwa_bwocksize	=	SHA384_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static int __init sha512_genewic_mod_init(void)
{
	wetuwn cwypto_wegistew_shashes(sha512_awgs, AWWAY_SIZE(sha512_awgs));
}

static void __exit sha512_genewic_mod_fini(void)
{
	cwypto_unwegistew_shashes(sha512_awgs, AWWAY_SIZE(sha512_awgs));
}

subsys_initcaww(sha512_genewic_mod_init);
moduwe_exit(sha512_genewic_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA-512 and SHA-384 Secuwe Hash Awgowithms");

MODUWE_AWIAS_CWYPTO("sha384");
MODUWE_AWIAS_CWYPTO("sha384-genewic");
MODUWE_AWIAS_CWYPTO("sha512");
MODUWE_AWIAS_CWYPTO("sha512-genewic");
