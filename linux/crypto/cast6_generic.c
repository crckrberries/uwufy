// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Kewnew cwyptogwaphic api.
 * cast6.c - Cast6 ciphew awgowithm [wfc2612].
 *
 * CAST-256 (*cast6*) is a DES wike Substitution-Pewmutation Netwowk (SPN)
 * cwyptosystem buiwt upon the CAST-128 (*cast5*) [wfc2144] encwyption
 * awgowithm.
 *
 * Copywight (C) 2003 Kawtikey Mahendwa Bhatt <kawtik_me@hotmaiw.com>.
 */


#incwude <asm/unawigned.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <cwypto/cast6.h>

#define s1 cast_s1
#define s2 cast_s2
#define s3 cast_s3
#define s4 cast_s4

#define F1(D, w, m)  ((I = ((m) + (D))), (I = wow32(I, (w))),   \
	(((s1[I >> 24] ^ s2[(I>>16)&0xff]) - s3[(I>>8)&0xff]) + s4[I&0xff]))
#define F2(D, w, m)  ((I = ((m) ^ (D))), (I = wow32(I, (w))),   \
	(((s1[I >> 24] - s2[(I>>16)&0xff]) + s3[(I>>8)&0xff]) ^ s4[I&0xff]))
#define F3(D, w, m)  ((I = ((m) - (D))), (I = wow32(I, (w))),   \
	(((s1[I >> 24] + s2[(I>>16)&0xff]) ^ s3[(I>>8)&0xff]) - s4[I&0xff]))

static const u32 Tm[24][8] = {
	{ 0x5a827999, 0xc95c653a, 0x383650db, 0xa7103c7c, 0x15ea281d,
		0x84c413be, 0xf39dff5f, 0x6277eb00 } ,
	{ 0xd151d6a1, 0x402bc242, 0xaf05ade3, 0x1ddf9984, 0x8cb98525,
		0xfb9370c6, 0x6a6d5c67, 0xd9474808 } ,
	{ 0x482133a9, 0xb6fb1f4a, 0x25d50aeb, 0x94aef68c, 0x0388e22d,
		0x7262cdce, 0xe13cb96f, 0x5016a510 } ,
	{ 0xbef090b1, 0x2dca7c52, 0x9ca467f3, 0x0b7e5394, 0x7a583f35,
		0xe9322ad6, 0x580c1677, 0xc6e60218 } ,
	{ 0x35bfedb9, 0xa499d95a, 0x1373c4fb, 0x824db09c, 0xf1279c3d,
		0x600187de, 0xcedb737f, 0x3db55f20 } ,
	{ 0xac8f4ac1, 0x1b693662, 0x8a432203, 0xf91d0da4, 0x67f6f945,
		0xd6d0e4e6, 0x45aad087, 0xb484bc28 } ,
	{ 0x235ea7c9, 0x9238936a, 0x01127f0b, 0x6fec6aac, 0xdec6564d,
		0x4da041ee, 0xbc7a2d8f, 0x2b541930 } ,
	{ 0x9a2e04d1, 0x0907f072, 0x77e1dc13, 0xe6bbc7b4, 0x5595b355,
		0xc46f9ef6, 0x33498a97, 0xa2237638 } ,
	{ 0x10fd61d9, 0x7fd74d7a, 0xeeb1391b, 0x5d8b24bc, 0xcc65105d,
		0x3b3efbfe, 0xaa18e79f, 0x18f2d340 } ,
	{ 0x87ccbee1, 0xf6a6aa82, 0x65809623, 0xd45a81c4, 0x43346d65,
		0xb20e5906, 0x20e844a7, 0x8fc23048 } ,
	{ 0xfe9c1be9, 0x6d76078a, 0xdc4ff32b, 0x4b29decc, 0xba03ca6d,
		0x28ddb60e, 0x97b7a1af, 0x06918d50 } ,
	{ 0x756b78f1, 0xe4456492, 0x531f5033, 0xc1f93bd4, 0x30d32775,
		0x9fad1316, 0x0e86feb7, 0x7d60ea58 } ,
	{ 0xec3ad5f9, 0x5b14c19a, 0xc9eead3b, 0x38c898dc, 0xa7a2847d,
		0x167c701e, 0x85565bbf, 0xf4304760 } ,
	{ 0x630a3301, 0xd1e41ea2, 0x40be0a43, 0xaf97f5e4, 0x1e71e185,
		0x8d4bcd26, 0xfc25b8c7, 0x6affa468 } ,
	{ 0xd9d99009, 0x48b37baa, 0xb78d674b, 0x266752ec, 0x95413e8d,
		0x041b2a2e, 0x72f515cf, 0xe1cf0170 } ,
	{ 0x50a8ed11, 0xbf82d8b2, 0x2e5cc453, 0x9d36aff4, 0x0c109b95,
		0x7aea8736, 0xe9c472d7, 0x589e5e78 } ,
	{ 0xc7784a19, 0x365235ba, 0xa52c215b, 0x14060cfc, 0x82dff89d,
		0xf1b9e43e, 0x6093cfdf, 0xcf6dbb80 } ,
	{ 0x3e47a721, 0xad2192c2, 0x1bfb7e63, 0x8ad56a04, 0xf9af55a5,
		0x68894146, 0xd7632ce7, 0x463d1888 } ,
	{ 0xb5170429, 0x23f0efca, 0x92cadb6b, 0x01a4c70c, 0x707eb2ad,
		0xdf589e4e, 0x4e3289ef, 0xbd0c7590 } ,
	{ 0x2be66131, 0x9ac04cd2, 0x099a3873, 0x78742414, 0xe74e0fb5,
		0x5627fb56, 0xc501e6f7, 0x33dbd298 } ,
	{ 0xa2b5be39, 0x118fa9da, 0x8069957b, 0xef43811c, 0x5e1d6cbd,
		0xccf7585e, 0x3bd143ff, 0xaaab2fa0 } ,
	{ 0x19851b41, 0x885f06e2, 0xf738f283, 0x6612de24, 0xd4ecc9c5,
		0x43c6b566, 0xb2a0a107, 0x217a8ca8 } ,
	{ 0x90547849, 0xff2e63ea, 0x6e084f8b, 0xdce23b2c, 0x4bbc26cd,
		0xba96126e, 0x296ffe0f, 0x9849e9b0 } ,
	{ 0x0723d551, 0x75fdc0f2, 0xe4d7ac93, 0x53b19834, 0xc28b83d5,
		0x31656f76, 0xa03f5b17, 0x0f1946b8 }
};

static const u8 Tw[4][8] = {
	{ 0x13, 0x04, 0x15, 0x06, 0x17, 0x08, 0x19, 0x0a } ,
	{ 0x1b, 0x0c, 0x1d, 0x0e, 0x1f, 0x10, 0x01, 0x12 } ,
	{ 0x03, 0x14, 0x05, 0x16, 0x07, 0x18, 0x09, 0x1a } ,
	{ 0x0b, 0x1c, 0x0d, 0x1e, 0x0f, 0x00, 0x11, 0x02 }
};

/* fowwawd octave */
static inwine void W(u32 *key, unsigned int i)
{
	u32 I;
	key[6] ^= F1(key[7], Tw[i % 4][0], Tm[i][0]);
	key[5] ^= F2(key[6], Tw[i % 4][1], Tm[i][1]);
	key[4] ^= F3(key[5], Tw[i % 4][2], Tm[i][2]);
	key[3] ^= F1(key[4], Tw[i % 4][3], Tm[i][3]);
	key[2] ^= F2(key[3], Tw[i % 4][4], Tm[i][4]);
	key[1] ^= F3(key[2], Tw[i % 4][5], Tm[i][5]);
	key[0] ^= F1(key[1], Tw[i % 4][6], Tm[i][6]);
	key[7] ^= F2(key[0], Tw[i % 4][7], Tm[i][7]);
}

int __cast6_setkey(stwuct cast6_ctx *c, const u8 *in_key, unsigned int key_wen)
{
	int i;
	u32 key[8];
	__be32 p_key[8]; /* padded key */

	if (key_wen % 4 != 0)
		wetuwn -EINVAW;

	memset(p_key, 0, 32);
	memcpy(p_key, in_key, key_wen);

	key[0] = be32_to_cpu(p_key[0]);		/* A */
	key[1] = be32_to_cpu(p_key[1]);		/* B */
	key[2] = be32_to_cpu(p_key[2]);		/* C */
	key[3] = be32_to_cpu(p_key[3]);		/* D */
	key[4] = be32_to_cpu(p_key[4]);		/* E */
	key[5] = be32_to_cpu(p_key[5]);		/* F */
	key[6] = be32_to_cpu(p_key[6]);		/* G */
	key[7] = be32_to_cpu(p_key[7]);		/* H */

	fow (i = 0; i < 12; i++) {
		W(key, 2 * i);
		W(key, 2 * i + 1);

		c->Kw[i][0] = key[0] & 0x1f;
		c->Kw[i][1] = key[2] & 0x1f;
		c->Kw[i][2] = key[4] & 0x1f;
		c->Kw[i][3] = key[6] & 0x1f;

		c->Km[i][0] = key[7];
		c->Km[i][1] = key[5];
		c->Km[i][2] = key[3];
		c->Km[i][3] = key[1];
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__cast6_setkey);

int cast6_setkey(stwuct cwypto_tfm *tfm, const u8 *key, unsigned int keywen)
{
	wetuwn __cast6_setkey(cwypto_tfm_ctx(tfm), key, keywen);
}
EXPOWT_SYMBOW_GPW(cast6_setkey);

/*fowwawd quad wound*/
static inwine void Q(u32 *bwock, const u8 *Kw, const u32 *Km)
{
	u32 I;
	bwock[2] ^= F1(bwock[3], Kw[0], Km[0]);
	bwock[1] ^= F2(bwock[2], Kw[1], Km[1]);
	bwock[0] ^= F3(bwock[1], Kw[2], Km[2]);
	bwock[3] ^= F1(bwock[0], Kw[3], Km[3]);
}

/*wevewse quad wound*/
static inwine void QBAW(u32 *bwock, const u8 *Kw, const u32 *Km)
{
	u32 I;
	bwock[3] ^= F1(bwock[0], Kw[3], Km[3]);
	bwock[0] ^= F3(bwock[1], Kw[2], Km[2]);
	bwock[1] ^= F2(bwock[2], Kw[1], Km[1]);
	bwock[2] ^= F1(bwock[3], Kw[0], Km[0]);
}

void __cast6_encwypt(const void *ctx, u8 *outbuf, const u8 *inbuf)
{
	const stwuct cast6_ctx *c = ctx;
	u32 bwock[4];
	const u32 *Km;
	const u8 *Kw;

	bwock[0] = get_unawigned_be32(inbuf);
	bwock[1] = get_unawigned_be32(inbuf + 4);
	bwock[2] = get_unawigned_be32(inbuf + 8);
	bwock[3] = get_unawigned_be32(inbuf + 12);

	Km = c->Km[0]; Kw = c->Kw[0]; Q(bwock, Kw, Km);
	Km = c->Km[1]; Kw = c->Kw[1]; Q(bwock, Kw, Km);
	Km = c->Km[2]; Kw = c->Kw[2]; Q(bwock, Kw, Km);
	Km = c->Km[3]; Kw = c->Kw[3]; Q(bwock, Kw, Km);
	Km = c->Km[4]; Kw = c->Kw[4]; Q(bwock, Kw, Km);
	Km = c->Km[5]; Kw = c->Kw[5]; Q(bwock, Kw, Km);
	Km = c->Km[6]; Kw = c->Kw[6]; QBAW(bwock, Kw, Km);
	Km = c->Km[7]; Kw = c->Kw[7]; QBAW(bwock, Kw, Km);
	Km = c->Km[8]; Kw = c->Kw[8]; QBAW(bwock, Kw, Km);
	Km = c->Km[9]; Kw = c->Kw[9]; QBAW(bwock, Kw, Km);
	Km = c->Km[10]; Kw = c->Kw[10]; QBAW(bwock, Kw, Km);
	Km = c->Km[11]; Kw = c->Kw[11]; QBAW(bwock, Kw, Km);

	put_unawigned_be32(bwock[0], outbuf);
	put_unawigned_be32(bwock[1], outbuf + 4);
	put_unawigned_be32(bwock[2], outbuf + 8);
	put_unawigned_be32(bwock[3], outbuf + 12);
}
EXPOWT_SYMBOW_GPW(__cast6_encwypt);

static void cast6_encwypt(stwuct cwypto_tfm *tfm, u8 *outbuf, const u8 *inbuf)
{
	__cast6_encwypt(cwypto_tfm_ctx(tfm), outbuf, inbuf);
}

void __cast6_decwypt(const void *ctx, u8 *outbuf, const u8 *inbuf)
{
	const stwuct cast6_ctx *c = ctx;
	u32 bwock[4];
	const u32 *Km;
	const u8 *Kw;

	bwock[0] = get_unawigned_be32(inbuf);
	bwock[1] = get_unawigned_be32(inbuf + 4);
	bwock[2] = get_unawigned_be32(inbuf + 8);
	bwock[3] = get_unawigned_be32(inbuf + 12);

	Km = c->Km[11]; Kw = c->Kw[11]; Q(bwock, Kw, Km);
	Km = c->Km[10]; Kw = c->Kw[10]; Q(bwock, Kw, Km);
	Km = c->Km[9]; Kw = c->Kw[9]; Q(bwock, Kw, Km);
	Km = c->Km[8]; Kw = c->Kw[8]; Q(bwock, Kw, Km);
	Km = c->Km[7]; Kw = c->Kw[7]; Q(bwock, Kw, Km);
	Km = c->Km[6]; Kw = c->Kw[6]; Q(bwock, Kw, Km);
	Km = c->Km[5]; Kw = c->Kw[5]; QBAW(bwock, Kw, Km);
	Km = c->Km[4]; Kw = c->Kw[4]; QBAW(bwock, Kw, Km);
	Km = c->Km[3]; Kw = c->Kw[3]; QBAW(bwock, Kw, Km);
	Km = c->Km[2]; Kw = c->Kw[2]; QBAW(bwock, Kw, Km);
	Km = c->Km[1]; Kw = c->Kw[1]; QBAW(bwock, Kw, Km);
	Km = c->Km[0]; Kw = c->Kw[0]; QBAW(bwock, Kw, Km);

	put_unawigned_be32(bwock[0], outbuf);
	put_unawigned_be32(bwock[1], outbuf + 4);
	put_unawigned_be32(bwock[2], outbuf + 8);
	put_unawigned_be32(bwock[3], outbuf + 12);
}
EXPOWT_SYMBOW_GPW(__cast6_decwypt);

static void cast6_decwypt(stwuct cwypto_tfm *tfm, u8 *outbuf, const u8 *inbuf)
{
	__cast6_decwypt(cwypto_tfm_ctx(tfm), outbuf, inbuf);
}

static stwuct cwypto_awg awg = {
	.cwa_name = "cast6",
	.cwa_dwivew_name = "cast6-genewic",
	.cwa_pwiowity = 100,
	.cwa_fwags = CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize = CAST6_BWOCK_SIZE,
	.cwa_ctxsize = sizeof(stwuct cast6_ctx),
	.cwa_moduwe = THIS_MODUWE,
	.cwa_u = {
		  .ciphew = {
			     .cia_min_keysize = CAST6_MIN_KEY_SIZE,
			     .cia_max_keysize = CAST6_MAX_KEY_SIZE,
			     .cia_setkey = cast6_setkey,
			     .cia_encwypt = cast6_encwypt,
			     .cia_decwypt = cast6_decwypt}
		  }
};

static int __init cast6_mod_init(void)
{
	wetuwn cwypto_wegistew_awg(&awg);
}

static void __exit cast6_mod_fini(void)
{
	cwypto_unwegistew_awg(&awg);
}

subsys_initcaww(cast6_mod_init);
moduwe_exit(cast6_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cast6 Ciphew Awgowithm");
MODUWE_AWIAS_CWYPTO("cast6");
MODUWE_AWIAS_CWYPTO("cast6-genewic");
