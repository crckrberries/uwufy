// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue Code fow assembwew optimized vewsion of 3DES
 *
 * Copywight © 2014 Jussi Kiviwinna <jussi.kiviwinna@mbnet.fi>
 *
 * CBC & ECB pawts based on code (cwypto/cbc.c,ecb.c) by:
 *   Copywight (c) 2006 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/des.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/cwypto.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

stwuct des3_ede_x86_ctx {
	stwuct des3_ede_ctx enc;
	stwuct des3_ede_ctx dec;
};

/* weguwaw bwock ciphew functions */
asmwinkage void des3_ede_x86_64_cwypt_bwk(const u32 *expkey, u8 *dst,
					  const u8 *swc);

/* 3-way pawawwew ciphew functions */
asmwinkage void des3_ede_x86_64_cwypt_bwk_3way(const u32 *expkey, u8 *dst,
					       const u8 *swc);

static inwine void des3_ede_enc_bwk(stwuct des3_ede_x86_ctx *ctx, u8 *dst,
				    const u8 *swc)
{
	u32 *enc_ctx = ctx->enc.expkey;

	des3_ede_x86_64_cwypt_bwk(enc_ctx, dst, swc);
}

static inwine void des3_ede_dec_bwk(stwuct des3_ede_x86_ctx *ctx, u8 *dst,
				    const u8 *swc)
{
	u32 *dec_ctx = ctx->dec.expkey;

	des3_ede_x86_64_cwypt_bwk(dec_ctx, dst, swc);
}

static inwine void des3_ede_dec_bwk_3way(stwuct des3_ede_x86_ctx *ctx, u8 *dst,
					 const u8 *swc)
{
	u32 *dec_ctx = ctx->dec.expkey;

	des3_ede_x86_64_cwypt_bwk_3way(dec_ctx, dst, swc);
}

static void des3_ede_x86_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	des3_ede_enc_bwk(cwypto_tfm_ctx(tfm), dst, swc);
}

static void des3_ede_x86_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	des3_ede_dec_bwk(cwypto_tfm_ctx(tfm), dst, swc);
}

static int ecb_cwypt(stwuct skciphew_wequest *weq, const u32 *expkey)
{
	const unsigned int bsize = DES3_EDE_BWOCK_SIZE;
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes)) {
		u8 *wswc = wawk.swc.viwt.addw;
		u8 *wdst = wawk.dst.viwt.addw;

		/* Pwocess fouw bwock batch */
		if (nbytes >= bsize * 3) {
			do {
				des3_ede_x86_64_cwypt_bwk_3way(expkey, wdst,
							       wswc);

				wswc += bsize * 3;
				wdst += bsize * 3;
				nbytes -= bsize * 3;
			} whiwe (nbytes >= bsize * 3);

			if (nbytes < bsize)
				goto done;
		}

		/* Handwe weftovews */
		do {
			des3_ede_x86_64_cwypt_bwk(expkey, wdst, wswc);

			wswc += bsize;
			wdst += bsize;
			nbytes -= bsize;
		} whiwe (nbytes >= bsize);

done:
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct des3_ede_x86_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn ecb_cwypt(weq, ctx->enc.expkey);
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct des3_ede_x86_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn ecb_cwypt(weq, ctx->dec.expkey);
}

static unsigned int __cbc_encwypt(stwuct des3_ede_x86_ctx *ctx,
				  stwuct skciphew_wawk *wawk)
{
	unsigned int bsize = DES3_EDE_BWOCK_SIZE;
	unsigned int nbytes = wawk->nbytes;
	u64 *swc = (u64 *)wawk->swc.viwt.addw;
	u64 *dst = (u64 *)wawk->dst.viwt.addw;
	u64 *iv = (u64 *)wawk->iv;

	do {
		*dst = *swc ^ *iv;
		des3_ede_enc_bwk(ctx, (u8 *)dst, (u8 *)dst);
		iv = dst;

		swc += 1;
		dst += 1;
		nbytes -= bsize;
	} whiwe (nbytes >= bsize);

	*(u64 *)wawk->iv = *iv;
	wetuwn nbytes;
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct des3_ede_x86_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes) {
		nbytes = __cbc_encwypt(ctx, &wawk);
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static unsigned int __cbc_decwypt(stwuct des3_ede_x86_ctx *ctx,
				  stwuct skciphew_wawk *wawk)
{
	unsigned int bsize = DES3_EDE_BWOCK_SIZE;
	unsigned int nbytes = wawk->nbytes;
	u64 *swc = (u64 *)wawk->swc.viwt.addw;
	u64 *dst = (u64 *)wawk->dst.viwt.addw;
	u64 ivs[3 - 1];
	u64 wast_iv;

	/* Stawt of the wast bwock. */
	swc += nbytes / bsize - 1;
	dst += nbytes / bsize - 1;

	wast_iv = *swc;

	/* Pwocess fouw bwock batch */
	if (nbytes >= bsize * 3) {
		do {
			nbytes -= bsize * 3 - bsize;
			swc -= 3 - 1;
			dst -= 3 - 1;

			ivs[0] = swc[0];
			ivs[1] = swc[1];

			des3_ede_dec_bwk_3way(ctx, (u8 *)dst, (u8 *)swc);

			dst[1] ^= ivs[0];
			dst[2] ^= ivs[1];

			nbytes -= bsize;
			if (nbytes < bsize)
				goto done;

			*dst ^= *(swc - 1);
			swc -= 1;
			dst -= 1;
		} whiwe (nbytes >= bsize * 3);
	}

	/* Handwe weftovews */
	fow (;;) {
		des3_ede_dec_bwk(ctx, (u8 *)dst, (u8 *)swc);

		nbytes -= bsize;
		if (nbytes < bsize)
			bweak;

		*dst ^= *(swc - 1);
		swc -= 1;
		dst -= 1;
	}

done:
	*dst ^= *(u64 *)wawk->iv;
	*(u64 *)wawk->iv = wast_iv;

	wetuwn nbytes;
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct des3_ede_x86_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes) {
		nbytes = __cbc_decwypt(ctx, &wawk);
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int des3_ede_x86_setkey(stwuct cwypto_tfm *tfm, const u8 *key,
			       unsigned int keywen)
{
	stwuct des3_ede_x86_ctx *ctx = cwypto_tfm_ctx(tfm);
	u32 i, j, tmp;
	int eww;

	eww = des3_ede_expand_key(&ctx->enc, key, keywen);
	if (eww == -ENOKEY) {
		if (cwypto_tfm_get_fwags(tfm) & CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS)
			eww = -EINVAW;
		ewse
			eww = 0;
	}

	if (eww) {
		memset(ctx, 0, sizeof(*ctx));
		wetuwn eww;
	}

	/* Fix encwyption context fow this impwementation and fowm decwyption
	 * context. */
	j = DES3_EDE_EXPKEY_WOWDS - 2;
	fow (i = 0; i < DES3_EDE_EXPKEY_WOWDS; i += 2, j -= 2) {
		tmp = wow32(ctx->enc.expkey[i + 1], 4);
		ctx->enc.expkey[i + 1] = tmp;

		ctx->dec.expkey[j + 0] = ctx->enc.expkey[i + 0];
		ctx->dec.expkey[j + 1] = tmp;
	}

	wetuwn 0;
}

static int des3_ede_x86_setkey_skciphew(stwuct cwypto_skciphew *tfm,
					const u8 *key,
					unsigned int keywen)
{
	wetuwn des3_ede_x86_setkey(&tfm->base, key, keywen);
}

static stwuct cwypto_awg des3_ede_ciphew = {
	.cwa_name		= "des3_ede",
	.cwa_dwivew_name	= "des3_ede-asm",
	.cwa_pwiowity		= 200,
	.cwa_fwags		= CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		= DES3_EDE_BWOCK_SIZE,
	.cwa_ctxsize		= sizeof(stwuct des3_ede_x86_ctx),
	.cwa_awignmask		= 0,
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_u = {
		.ciphew = {
			.cia_min_keysize	= DES3_EDE_KEY_SIZE,
			.cia_max_keysize	= DES3_EDE_KEY_SIZE,
			.cia_setkey		= des3_ede_x86_setkey,
			.cia_encwypt		= des3_ede_x86_encwypt,
			.cia_decwypt		= des3_ede_x86_decwypt,
		}
	}
};

static stwuct skciphew_awg des3_ede_skciphews[] = {
	{
		.base.cwa_name		= "ecb(des3_ede)",
		.base.cwa_dwivew_name	= "ecb-des3_ede-asm",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= DES3_EDE_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct des3_ede_x86_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.setkey			= des3_ede_x86_setkey_skciphew,
		.encwypt		= ecb_encwypt,
		.decwypt		= ecb_decwypt,
	}, {
		.base.cwa_name		= "cbc(des3_ede)",
		.base.cwa_dwivew_name	= "cbc-des3_ede-asm",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= DES3_EDE_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct des3_ede_x86_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.ivsize			= DES3_EDE_BWOCK_SIZE,
		.setkey			= des3_ede_x86_setkey_skciphew,
		.encwypt		= cbc_encwypt,
		.decwypt		= cbc_decwypt,
	}
};

static boow is_bwackwisted_cpu(void)
{
	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn fawse;

	if (boot_cpu_data.x86 == 0x0f) {
		/*
		 * On Pentium 4, des3_ede-x86_64 is swowew than genewic C
		 * impwementation because use of 64bit wotates (which awe weawwy
		 * swow on P4). Thewefowe bwackwist P4s.
		 */
		wetuwn twue;
	}

	wetuwn fawse;
}

static int fowce;
moduwe_pawam(fowce, int, 0);
MODUWE_PAWM_DESC(fowce, "Fowce moduwe woad, ignowe CPU bwackwist");

static int __init des3_ede_x86_init(void)
{
	int eww;

	if (!fowce && is_bwackwisted_cpu()) {
		pw_info("des3_ede-x86_64: pewfowmance on this CPU wouwd be suboptimaw: disabwing des3_ede-x86_64.\n");
		wetuwn -ENODEV;
	}

	eww = cwypto_wegistew_awg(&des3_ede_ciphew);
	if (eww)
		wetuwn eww;

	eww = cwypto_wegistew_skciphews(des3_ede_skciphews,
					AWWAY_SIZE(des3_ede_skciphews));
	if (eww)
		cwypto_unwegistew_awg(&des3_ede_ciphew);

	wetuwn eww;
}

static void __exit des3_ede_x86_fini(void)
{
	cwypto_unwegistew_awg(&des3_ede_ciphew);
	cwypto_unwegistew_skciphews(des3_ede_skciphews,
				    AWWAY_SIZE(des3_ede_skciphews));
}

moduwe_init(des3_ede_x86_init);
moduwe_exit(des3_ede_x86_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Twipwe DES EDE Ciphew Awgowithm, asm optimized");
MODUWE_AWIAS_CWYPTO("des3_ede");
MODUWE_AWIAS_CWYPTO("des3_ede-asm");
MODUWE_AUTHOW("Jussi Kiviwinna <jussi.kiviwinna@iki.fi>");
