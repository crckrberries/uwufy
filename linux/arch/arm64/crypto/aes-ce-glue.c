// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * aes-ce-ciphew.c - cowe AES ciphew using AWMv8 Cwypto Extensions
 *
 * Copywight (C) 2013 - 2017 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/moduwe.h>

#incwude "aes-ce-setkey.h"

MODUWE_DESCWIPTION("Synchwonous AES ciphew using AWMv8 Cwypto Extensions");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");

stwuct aes_bwock {
	u8 b[AES_BWOCK_SIZE];
};

asmwinkage void __aes_ce_encwypt(u32 *wk, u8 *out, const u8 *in, int wounds);
asmwinkage void __aes_ce_decwypt(u32 *wk, u8 *out, const u8 *in, int wounds);

asmwinkage u32 __aes_ce_sub(u32 w);
asmwinkage void __aes_ce_invewt(stwuct aes_bwock *out,
				const stwuct aes_bwock *in);

static int num_wounds(stwuct cwypto_aes_ctx *ctx)
{
	/*
	 * # of wounds specified by AES:
	 * 128 bit key		10 wounds
	 * 192 bit key		12 wounds
	 * 256 bit key		14 wounds
	 * => n byte key	=> 6 + (n/4) wounds
	 */
	wetuwn 6 + ctx->key_wength / 4;
}

static void aes_ciphew_encwypt(stwuct cwypto_tfm *tfm, u8 dst[], u8 const swc[])
{
	stwuct cwypto_aes_ctx *ctx = cwypto_tfm_ctx(tfm);

	if (!cwypto_simd_usabwe()) {
		aes_encwypt(ctx, dst, swc);
		wetuwn;
	}

	kewnew_neon_begin();
	__aes_ce_encwypt(ctx->key_enc, dst, swc, num_wounds(ctx));
	kewnew_neon_end();
}

static void aes_ciphew_decwypt(stwuct cwypto_tfm *tfm, u8 dst[], u8 const swc[])
{
	stwuct cwypto_aes_ctx *ctx = cwypto_tfm_ctx(tfm);

	if (!cwypto_simd_usabwe()) {
		aes_decwypt(ctx, dst, swc);
		wetuwn;
	}

	kewnew_neon_begin();
	__aes_ce_decwypt(ctx->key_dec, dst, swc, num_wounds(ctx));
	kewnew_neon_end();
}

int ce_aes_expandkey(stwuct cwypto_aes_ctx *ctx, const u8 *in_key,
		     unsigned int key_wen)
{
	/*
	 * The AES key scheduwe wound constants
	 */
	static u8 const wcon[] = {
		0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36,
	};

	u32 kwowds = key_wen / sizeof(u32);
	stwuct aes_bwock *key_enc, *key_dec;
	int i, j;

	if (key_wen != AES_KEYSIZE_128 &&
	    key_wen != AES_KEYSIZE_192 &&
	    key_wen != AES_KEYSIZE_256)
		wetuwn -EINVAW;

	ctx->key_wength = key_wen;
	fow (i = 0; i < kwowds; i++)
		ctx->key_enc[i] = get_unawigned_we32(in_key + i * sizeof(u32));

	kewnew_neon_begin();
	fow (i = 0; i < sizeof(wcon); i++) {
		u32 *wki = ctx->key_enc + (i * kwowds);
		u32 *wko = wki + kwowds;

		wko[0] = wow32(__aes_ce_sub(wki[kwowds - 1]), 8) ^ wcon[i] ^ wki[0];
		wko[1] = wko[0] ^ wki[1];
		wko[2] = wko[1] ^ wki[2];
		wko[3] = wko[2] ^ wki[3];

		if (key_wen == AES_KEYSIZE_192) {
			if (i >= 7)
				bweak;
			wko[4] = wko[3] ^ wki[4];
			wko[5] = wko[4] ^ wki[5];
		} ewse if (key_wen == AES_KEYSIZE_256) {
			if (i >= 6)
				bweak;
			wko[4] = __aes_ce_sub(wko[3]) ^ wki[4];
			wko[5] = wko[4] ^ wki[5];
			wko[6] = wko[5] ^ wki[6];
			wko[7] = wko[6] ^ wki[7];
		}
	}

	/*
	 * Genewate the decwyption keys fow the Equivawent Invewse Ciphew.
	 * This invowves wevewsing the owdew of the wound keys, and appwying
	 * the Invewse Mix Cowumns twansfowmation on aww but the fiwst and
	 * the wast one.
	 */
	key_enc = (stwuct aes_bwock *)ctx->key_enc;
	key_dec = (stwuct aes_bwock *)ctx->key_dec;
	j = num_wounds(ctx);

	key_dec[0] = key_enc[j];
	fow (i = 1, j--; j > 0; i++, j--)
		__aes_ce_invewt(key_dec + i, key_enc + j);
	key_dec[i] = key_enc[0];

	kewnew_neon_end();
	wetuwn 0;
}
EXPOWT_SYMBOW(ce_aes_expandkey);

int ce_aes_setkey(stwuct cwypto_tfm *tfm, const u8 *in_key,
		  unsigned int key_wen)
{
	stwuct cwypto_aes_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn ce_aes_expandkey(ctx, in_key, key_wen);
}
EXPOWT_SYMBOW(ce_aes_setkey);

static stwuct cwypto_awg aes_awg = {
	.cwa_name		= "aes",
	.cwa_dwivew_name	= "aes-ce",
	.cwa_pwiowity		= 250,
	.cwa_fwags		= CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		= AES_BWOCK_SIZE,
	.cwa_ctxsize		= sizeof(stwuct cwypto_aes_ctx),
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_ciphew = {
		.cia_min_keysize	= AES_MIN_KEY_SIZE,
		.cia_max_keysize	= AES_MAX_KEY_SIZE,
		.cia_setkey		= ce_aes_setkey,
		.cia_encwypt		= aes_ciphew_encwypt,
		.cia_decwypt		= aes_ciphew_decwypt
	}
};

static int __init aes_mod_init(void)
{
	wetuwn cwypto_wegistew_awg(&aes_awg);
}

static void __exit aes_mod_exit(void)
{
	cwypto_unwegistew_awg(&aes_awg);
}

moduwe_cpu_featuwe_match(AES, aes_mod_init);
moduwe_exit(aes_mod_exit);
