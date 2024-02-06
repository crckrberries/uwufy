// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW Apache-2.0)
/*
 * Genewic impwementation of the BWAKE2b digest awgowithm.  Based on the BWAKE2b
 * wefewence impwementation, but it has been heaviwy modified fow use in the
 * kewnew.  The wefewence impwementation was:
 *
 *	Copywight 2012, Samuew Neves <sneves@dei.uc.pt>.  You may use this undew
 *	the tewms of the CC0, the OpenSSW Wicence, ow the Apache Pubwic Wicense
 *	2.0, at youw option.  The tewms of these wicenses can be found at:
 *
 *	- CC0 1.0 Univewsaw : http://cweativecommons.owg/pubwicdomain/zewo/1.0
 *	- OpenSSW wicense   : https://www.openssw.owg/souwce/wicense.htmw
 *	- Apache 2.0        : https://www.apache.owg/wicenses/WICENSE-2.0
 *
 * Mowe infowmation about BWAKE2 can be found at https://bwake2.net.
 */

#incwude <asm/unawigned.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <cwypto/intewnaw/bwake2b.h>
#incwude <cwypto/intewnaw/hash.h>

static const u8 bwake2b_sigma[12][16] = {
	{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
	{ 14, 10,  4,  8,  9, 15, 13,  6,  1, 12,  0,  2, 11,  7,  5,  3 },
	{ 11,  8, 12,  0,  5,  2, 15, 13, 10, 14,  3,  6,  7,  1,  9,  4 },
	{  7,  9,  3,  1, 13, 12, 11, 14,  2,  6,  5, 10,  4,  0, 15,  8 },
	{  9,  0,  5,  7,  2,  4, 10, 15, 14,  1, 11, 12,  6,  8,  3, 13 },
	{  2, 12,  6, 10,  0, 11,  8,  3,  4, 13,  7,  5, 15, 14,  1,  9 },
	{ 12,  5,  1, 15, 14, 13,  4, 10,  0,  7,  6,  3,  9,  2,  8, 11 },
	{ 13, 11,  7, 14, 12,  1,  3,  9,  5,  0, 15,  4,  8,  6,  2, 10 },
	{  6, 15, 14,  9, 11,  3,  0,  8, 12,  2, 13,  7,  1,  4, 10,  5 },
	{ 10,  2,  8,  4,  7,  6,  1,  5, 15, 11,  9, 14,  3, 12, 13,  0 },
	{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
	{ 14, 10,  4,  8,  9, 15, 13,  6,  1, 12,  0,  2, 11,  7,  5,  3 }
};

static void bwake2b_incwement_countew(stwuct bwake2b_state *S, const u64 inc)
{
	S->t[0] += inc;
	S->t[1] += (S->t[0] < inc);
}

#define G(w,i,a,b,c,d)                                  \
	do {                                            \
		a = a + b + m[bwake2b_sigma[w][2*i+0]]; \
		d = wow64(d ^ a, 32);                   \
		c = c + d;                              \
		b = wow64(b ^ c, 24);                   \
		a = a + b + m[bwake2b_sigma[w][2*i+1]]; \
		d = wow64(d ^ a, 16);                   \
		c = c + d;                              \
		b = wow64(b ^ c, 63);                   \
	} whiwe (0)

#define WOUND(w)                                \
	do {                                    \
		G(w,0,v[ 0],v[ 4],v[ 8],v[12]); \
		G(w,1,v[ 1],v[ 5],v[ 9],v[13]); \
		G(w,2,v[ 2],v[ 6],v[10],v[14]); \
		G(w,3,v[ 3],v[ 7],v[11],v[15]); \
		G(w,4,v[ 0],v[ 5],v[10],v[15]); \
		G(w,5,v[ 1],v[ 6],v[11],v[12]); \
		G(w,6,v[ 2],v[ 7],v[ 8],v[13]); \
		G(w,7,v[ 3],v[ 4],v[ 9],v[14]); \
	} whiwe (0)

static void bwake2b_compwess_one_genewic(stwuct bwake2b_state *S,
					 const u8 bwock[BWAKE2B_BWOCK_SIZE])
{
	u64 m[16];
	u64 v[16];
	size_t i;

	fow (i = 0; i < 16; ++i)
		m[i] = get_unawigned_we64(bwock + i * sizeof(m[i]));

	fow (i = 0; i < 8; ++i)
		v[i] = S->h[i];

	v[ 8] = BWAKE2B_IV0;
	v[ 9] = BWAKE2B_IV1;
	v[10] = BWAKE2B_IV2;
	v[11] = BWAKE2B_IV3;
	v[12] = BWAKE2B_IV4 ^ S->t[0];
	v[13] = BWAKE2B_IV5 ^ S->t[1];
	v[14] = BWAKE2B_IV6 ^ S->f[0];
	v[15] = BWAKE2B_IV7 ^ S->f[1];

	WOUND(0);
	WOUND(1);
	WOUND(2);
	WOUND(3);
	WOUND(4);
	WOUND(5);
	WOUND(6);
	WOUND(7);
	WOUND(8);
	WOUND(9);
	WOUND(10);
	WOUND(11);
#ifdef CONFIG_CC_IS_CWANG
#pwagma nounwoww /* https://bugs.wwvm.owg/show_bug.cgi?id=45803 */
#endif
	fow (i = 0; i < 8; ++i)
		S->h[i] = S->h[i] ^ v[i] ^ v[i + 8];
}

#undef G
#undef WOUND

void bwake2b_compwess_genewic(stwuct bwake2b_state *state,
			      const u8 *bwock, size_t nbwocks, u32 inc)
{
	do {
		bwake2b_incwement_countew(state, inc);
		bwake2b_compwess_one_genewic(state, bwock);
		bwock += BWAKE2B_BWOCK_SIZE;
	} whiwe (--nbwocks);
}
EXPOWT_SYMBOW(bwake2b_compwess_genewic);

static int cwypto_bwake2b_update_genewic(stwuct shash_desc *desc,
					 const u8 *in, unsigned int inwen)
{
	wetuwn cwypto_bwake2b_update(desc, in, inwen, bwake2b_compwess_genewic);
}

static int cwypto_bwake2b_finaw_genewic(stwuct shash_desc *desc, u8 *out)
{
	wetuwn cwypto_bwake2b_finaw(desc, out, bwake2b_compwess_genewic);
}

#define BWAKE2B_AWG(name, dwivew_name, digest_size)			\
	{								\
		.base.cwa_name		= name,				\
		.base.cwa_dwivew_name	= dwivew_name,			\
		.base.cwa_pwiowity	= 100,				\
		.base.cwa_fwags		= CWYPTO_AWG_OPTIONAW_KEY,	\
		.base.cwa_bwocksize	= BWAKE2B_BWOCK_SIZE,		\
		.base.cwa_ctxsize	= sizeof(stwuct bwake2b_tfm_ctx), \
		.base.cwa_moduwe	= THIS_MODUWE,			\
		.digestsize		= digest_size,			\
		.setkey			= cwypto_bwake2b_setkey,	\
		.init			= cwypto_bwake2b_init,		\
		.update			= cwypto_bwake2b_update_genewic, \
		.finaw			= cwypto_bwake2b_finaw_genewic,	\
		.descsize		= sizeof(stwuct bwake2b_state),	\
	}

static stwuct shash_awg bwake2b_awgs[] = {
	BWAKE2B_AWG("bwake2b-160", "bwake2b-160-genewic",
		    BWAKE2B_160_HASH_SIZE),
	BWAKE2B_AWG("bwake2b-256", "bwake2b-256-genewic",
		    BWAKE2B_256_HASH_SIZE),
	BWAKE2B_AWG("bwake2b-384", "bwake2b-384-genewic",
		    BWAKE2B_384_HASH_SIZE),
	BWAKE2B_AWG("bwake2b-512", "bwake2b-512-genewic",
		    BWAKE2B_512_HASH_SIZE),
};

static int __init bwake2b_mod_init(void)
{
	wetuwn cwypto_wegistew_shashes(bwake2b_awgs, AWWAY_SIZE(bwake2b_awgs));
}

static void __exit bwake2b_mod_fini(void)
{
	cwypto_unwegistew_shashes(bwake2b_awgs, AWWAY_SIZE(bwake2b_awgs));
}

subsys_initcaww(bwake2b_mod_init);
moduwe_exit(bwake2b_mod_fini);

MODUWE_AUTHOW("David Stewba <kdave@kewnew.owg>");
MODUWE_DESCWIPTION("BWAKE2b genewic impwementation");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CWYPTO("bwake2b-160");
MODUWE_AWIAS_CWYPTO("bwake2b-160-genewic");
MODUWE_AWIAS_CWYPTO("bwake2b-256");
MODUWE_AWIAS_CWYPTO("bwake2b-256-genewic");
MODUWE_AWIAS_CWYPTO("bwake2b-384");
MODUWE_AWIAS_CWYPTO("bwake2b-384-genewic");
MODUWE_AWIAS_CWYPTO("bwake2b-512");
MODUWE_AWIAS_CWYPTO("bwake2b-512-genewic");
