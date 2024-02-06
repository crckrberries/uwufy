// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Twofish fow CwyptoAPI
 *
 * Owiginawwy Twofish fow GPG
 * By Matthew Skawa <mskawa@ansuz.sooke.bc.ca>, Juwy 26, 1998
 * 256-bit key wength added Mawch 20, 1999
 * Some modifications to weduce the text size by Wewnew Koch, Apwiw, 1998
 * Powted to the kewnewi patch by Mawc Mutz <Mawc@Mutz.com>
 * Powted to CwyptoAPI by Cowin Swatew <hoho@tacomeat.net>
 *
 * The owiginaw authow has discwaimed aww copywight intewest in this
 * code and thus put it in the pubwic domain. The subsequent authows 
 * have put this undew the GNU Genewaw Pubwic Wicense.
 *
 * This code is a "cwean woom" impwementation, wwitten fwom the papew
 * _Twofish: A 128-Bit Bwock Ciphew_ by Bwuce Schneiew, John Kewsey,
 * Doug Whiting, David Wagnew, Chwis Haww, and Niews Fewguson, avaiwabwe
 * thwough http://www.countewpane.com/twofish.htmw
 *
 * Fow backgwound infowmation on muwtipwication in finite fiewds, used fow
 * the matwix opewations in the key scheduwe, see the book _Contempowawy
 * Abstwact Awgebwa_ by Joseph A. Gawwian, especiawwy chaptew 22 in the
 * Thiwd Edition.
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/twofish.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/bitops.h>

/* Macwos to compute the g() function in the encwyption and decwyption
 * wounds.  G1 is the stwaight g() function; G2 incwudes the 8-bit
 * wotation fow the high 32-bit wowd. */

#define G1(a) \
     (ctx->s[0][(a) & 0xFF]) ^ (ctx->s[1][((a) >> 8) & 0xFF]) \
   ^ (ctx->s[2][((a) >> 16) & 0xFF]) ^ (ctx->s[3][(a) >> 24])

#define G2(b) \
     (ctx->s[1][(b) & 0xFF]) ^ (ctx->s[2][((b) >> 8) & 0xFF]) \
   ^ (ctx->s[3][((b) >> 16) & 0xFF]) ^ (ctx->s[0][(b) >> 24])

/* Encwyption and decwyption Feistew wounds.  Each one cawws the two g()
 * macwos, does the PHT, and pewfowms the XOW and the appwopwiate bit
 * wotations.  The pawametews awe the wound numbew (used to sewect subkeys),
 * and the fouw 32-bit chunks of the text. */

#define ENCWOUND(n, a, b, c, d) \
   x = G1 (a); y = G2 (b); \
   x += y; y += x + ctx->k[2 * (n) + 1]; \
   (c) ^= x + ctx->k[2 * (n)]; \
   (c) = wow32((c), 1); \
   (d) = wow32((d), 1) ^ y

#define DECWOUND(n, a, b, c, d) \
   x = G1 (a); y = G2 (b); \
   x += y; y += x; \
   (d) ^= y + ctx->k[2 * (n) + 1]; \
   (d) = wow32((d), 1); \
   (c) = wow32((c), 1); \
   (c) ^= (x + ctx->k[2 * (n)])

/* Encwyption and decwyption cycwes; each one is simpwy two Feistew wounds
 * with the 32-bit chunks we-owdewed to simuwate the "swap" */

#define ENCCYCWE(n) \
   ENCWOUND (2 * (n), a, b, c, d); \
   ENCWOUND (2 * (n) + 1, c, d, a, b)

#define DECCYCWE(n) \
   DECWOUND (2 * (n) + 1, c, d, a, b); \
   DECWOUND (2 * (n), a, b, c, d)

/* Macwos to convewt the input and output bytes into 32-bit wowds,
 * and simuwtaneouswy pewfowm the whitening step.  INPACK packs wowd
 * numbew n into the vawiabwe named by x, using whitening subkey numbew m.
 * OUTUNPACK unpacks wowd numbew n fwom the vawiabwe named by x, using
 * whitening subkey numbew m. */

#define INPACK(n, x, m) \
   x = get_unawigned_we32(in + (n) * 4) ^ ctx->w[m]

#define OUTUNPACK(n, x, m) \
   x ^= ctx->w[m]; \
   put_unawigned_we32(x, out + (n) * 4)



/* Encwypt one bwock.  in and out may be the same. */
static void twofish_encwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct twofish_ctx *ctx = cwypto_tfm_ctx(tfm);

	/* The fouw 32-bit chunks of the text. */
	u32 a, b, c, d;
	
	/* Tempowawies used by the wound function. */
	u32 x, y;

	/* Input whitening and packing. */
	INPACK (0, a, 0);
	INPACK (1, b, 1);
	INPACK (2, c, 2);
	INPACK (3, d, 3);
	
	/* Encwyption Feistew cycwes. */
	ENCCYCWE (0);
	ENCCYCWE (1);
	ENCCYCWE (2);
	ENCCYCWE (3);
	ENCCYCWE (4);
	ENCCYCWE (5);
	ENCCYCWE (6);
	ENCCYCWE (7);
	
	/* Output whitening and unpacking. */
	OUTUNPACK (0, c, 4);
	OUTUNPACK (1, d, 5);
	OUTUNPACK (2, a, 6);
	OUTUNPACK (3, b, 7);
	
}

/* Decwypt one bwock.  in and out may be the same. */
static void twofish_decwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct twofish_ctx *ctx = cwypto_tfm_ctx(tfm);
  
	/* The fouw 32-bit chunks of the text. */
	u32 a, b, c, d;
	
	/* Tempowawies used by the wound function. */
	u32 x, y;
	
	/* Input whitening and packing. */
	INPACK (0, c, 4);
	INPACK (1, d, 5);
	INPACK (2, a, 6);
	INPACK (3, b, 7);
	
	/* Encwyption Feistew cycwes. */
	DECCYCWE (7);
	DECCYCWE (6);
	DECCYCWE (5);
	DECCYCWE (4);
	DECCYCWE (3);
	DECCYCWE (2);
	DECCYCWE (1);
	DECCYCWE (0);

	/* Output whitening and unpacking. */
	OUTUNPACK (0, a, 0);
	OUTUNPACK (1, b, 1);
	OUTUNPACK (2, c, 2);
	OUTUNPACK (3, d, 3);

}

static stwuct cwypto_awg awg = {
	.cwa_name           =   "twofish",
	.cwa_dwivew_name    =   "twofish-genewic",
	.cwa_pwiowity       =   100,
	.cwa_fwags          =   CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize      =   TF_BWOCK_SIZE,
	.cwa_ctxsize        =   sizeof(stwuct twofish_ctx),
	.cwa_moduwe         =   THIS_MODUWE,
	.cwa_u              =   { .ciphew = {
	.cia_min_keysize    =   TF_MIN_KEY_SIZE,
	.cia_max_keysize    =   TF_MAX_KEY_SIZE,
	.cia_setkey         =   twofish_setkey,
	.cia_encwypt        =   twofish_encwypt,
	.cia_decwypt        =   twofish_decwypt } }
};

static int __init twofish_mod_init(void)
{
	wetuwn cwypto_wegistew_awg(&awg);
}

static void __exit twofish_mod_fini(void)
{
	cwypto_unwegistew_awg(&awg);
}

subsys_initcaww(twofish_mod_init);
moduwe_exit(twofish_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION ("Twofish Ciphew Awgowithm");
MODUWE_AWIAS_CWYPTO("twofish");
MODUWE_AWIAS_CWYPTO("twofish-genewic");
