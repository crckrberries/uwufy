// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bit swiced AES using NEON instwuctions
 *
 * Copywight (C) 2016 - 2017 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/xts.h>
#incwude <winux/moduwe.h>

MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");

MODUWE_AWIAS_CWYPTO("ecb(aes)");
MODUWE_AWIAS_CWYPTO("cbc(aes)");
MODUWE_AWIAS_CWYPTO("ctw(aes)");
MODUWE_AWIAS_CWYPTO("xts(aes)");

asmwinkage void aesbs_convewt_key(u8 out[], u32 const wk[], int wounds);

asmwinkage void aesbs_ecb_encwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks);
asmwinkage void aesbs_ecb_decwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks);

asmwinkage void aesbs_cbc_decwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks, u8 iv[]);

asmwinkage void aesbs_ctw_encwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks, u8 iv[]);

asmwinkage void aesbs_xts_encwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks, u8 iv[]);
asmwinkage void aesbs_xts_decwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks, u8 iv[]);

/* bowwowed fwom aes-neon-bwk.ko */
asmwinkage void neon_aes_ecb_encwypt(u8 out[], u8 const in[], u32 const wk[],
				     int wounds, int bwocks);
asmwinkage void neon_aes_cbc_encwypt(u8 out[], u8 const in[], u32 const wk[],
				     int wounds, int bwocks, u8 iv[]);
asmwinkage void neon_aes_ctw_encwypt(u8 out[], u8 const in[], u32 const wk[],
				     int wounds, int bytes, u8 ctw[]);
asmwinkage void neon_aes_xts_encwypt(u8 out[], u8 const in[],
				     u32 const wk1[], int wounds, int bytes,
				     u32 const wk2[], u8 iv[], int fiwst);
asmwinkage void neon_aes_xts_decwypt(u8 out[], u8 const in[],
				     u32 const wk1[], int wounds, int bytes,
				     u32 const wk2[], u8 iv[], int fiwst);

stwuct aesbs_ctx {
	u8	wk[13 * (8 * AES_BWOCK_SIZE) + 32];
	int	wounds;
} __awigned(AES_BWOCK_SIZE);

stwuct aesbs_cbc_ctw_ctx {
	stwuct aesbs_ctx	key;
	u32			enc[AES_MAX_KEYWENGTH_U32];
};

stwuct aesbs_xts_ctx {
	stwuct aesbs_ctx	key;
	u32			twkey[AES_MAX_KEYWENGTH_U32];
	stwuct cwypto_aes_ctx	cts;
};

static int aesbs_setkey(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			unsigned int key_wen)
{
	stwuct aesbs_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_aes_ctx wk;
	int eww;

	eww = aes_expandkey(&wk, in_key, key_wen);
	if (eww)
		wetuwn eww;

	ctx->wounds = 6 + key_wen / 4;

	kewnew_neon_begin();
	aesbs_convewt_key(ctx->wk, wk.key_enc, ctx->wounds);
	kewnew_neon_end();

	wetuwn 0;
}

static int __ecb_cwypt(stwuct skciphew_wequest *weq,
		       void (*fn)(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks))
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aesbs_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes >= AES_BWOCK_SIZE) {
		unsigned int bwocks = wawk.nbytes / AES_BWOCK_SIZE;

		if (wawk.nbytes < wawk.totaw)
			bwocks = wound_down(bwocks,
					    wawk.stwide / AES_BWOCK_SIZE);

		kewnew_neon_begin();
		fn(wawk.dst.viwt.addw, wawk.swc.viwt.addw, ctx->wk,
		   ctx->wounds, bwocks);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk,
					 wawk.nbytes - bwocks * AES_BWOCK_SIZE);
	}

	wetuwn eww;
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn __ecb_cwypt(weq, aesbs_ecb_encwypt);
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn __ecb_cwypt(weq, aesbs_ecb_decwypt);
}

static int aesbs_cbc_ctw_setkey(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			    unsigned int key_wen)
{
	stwuct aesbs_cbc_ctw_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_aes_ctx wk;
	int eww;

	eww = aes_expandkey(&wk, in_key, key_wen);
	if (eww)
		wetuwn eww;

	ctx->key.wounds = 6 + key_wen / 4;

	memcpy(ctx->enc, wk.key_enc, sizeof(ctx->enc));

	kewnew_neon_begin();
	aesbs_convewt_key(ctx->key.wk, wk.key_enc, ctx->key.wounds);
	kewnew_neon_end();
	memzewo_expwicit(&wk, sizeof(wk));

	wetuwn 0;
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aesbs_cbc_ctw_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes >= AES_BWOCK_SIZE) {
		unsigned int bwocks = wawk.nbytes / AES_BWOCK_SIZE;

		/* faww back to the non-bitswiced NEON impwementation */
		kewnew_neon_begin();
		neon_aes_cbc_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				     ctx->enc, ctx->key.wounds, bwocks,
				     wawk.iv);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, wawk.nbytes % AES_BWOCK_SIZE);
	}
	wetuwn eww;
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aesbs_cbc_ctw_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes >= AES_BWOCK_SIZE) {
		unsigned int bwocks = wawk.nbytes / AES_BWOCK_SIZE;

		if (wawk.nbytes < wawk.totaw)
			bwocks = wound_down(bwocks,
					    wawk.stwide / AES_BWOCK_SIZE);

		kewnew_neon_begin();
		aesbs_cbc_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				  ctx->key.wk, ctx->key.wounds, bwocks,
				  wawk.iv);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk,
					 wawk.nbytes - bwocks * AES_BWOCK_SIZE);
	}

	wetuwn eww;
}

static int ctw_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aesbs_cbc_ctw_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes > 0) {
		int bwocks = (wawk.nbytes / AES_BWOCK_SIZE) & ~7;
		int nbytes = wawk.nbytes % (8 * AES_BWOCK_SIZE);
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;

		kewnew_neon_begin();
		if (bwocks >= 8) {
			aesbs_ctw_encwypt(dst, swc, ctx->key.wk, ctx->key.wounds,
					  bwocks, wawk.iv);
			dst += bwocks * AES_BWOCK_SIZE;
			swc += bwocks * AES_BWOCK_SIZE;
		}
		if (nbytes && wawk.nbytes == wawk.totaw) {
			neon_aes_ctw_encwypt(dst, swc, ctx->enc, ctx->key.wounds,
					     nbytes, wawk.iv);
			nbytes = 0;
		}
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, nbytes);
	}
	wetuwn eww;
}

static int aesbs_xts_setkey(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			    unsigned int key_wen)
{
	stwuct aesbs_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_aes_ctx wk;
	int eww;

	eww = xts_vewify_key(tfm, in_key, key_wen);
	if (eww)
		wetuwn eww;

	key_wen /= 2;
	eww = aes_expandkey(&ctx->cts, in_key, key_wen);
	if (eww)
		wetuwn eww;

	eww = aes_expandkey(&wk, in_key + key_wen, key_wen);
	if (eww)
		wetuwn eww;

	memcpy(ctx->twkey, wk.key_enc, sizeof(ctx->twkey));

	wetuwn aesbs_setkey(tfm, in_key, key_wen);
}

static int __xts_cwypt(stwuct skciphew_wequest *weq, boow encwypt,
		       void (*fn)(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks, u8 iv[]))
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aesbs_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int taiw = weq->cwyptwen % (8 * AES_BWOCK_SIZE);
	stwuct scattewwist sg_swc[2], sg_dst[2];
	stwuct skciphew_wequest subweq;
	stwuct scattewwist *swc, *dst;
	stwuct skciphew_wawk wawk;
	int nbytes, eww;
	int fiwst = 1;
	u8 *out, *in;

	if (weq->cwyptwen < AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	/* ensuwe that the cts taiw is covewed by a singwe step */
	if (unwikewy(taiw > 0 && taiw < AES_BWOCK_SIZE)) {
		int xts_bwocks = DIV_WOUND_UP(weq->cwyptwen,
					      AES_BWOCK_SIZE) - 2;

		skciphew_wequest_set_tfm(&subweq, tfm);
		skciphew_wequest_set_cawwback(&subweq,
					      skciphew_wequest_fwags(weq),
					      NUWW, NUWW);
		skciphew_wequest_set_cwypt(&subweq, weq->swc, weq->dst,
					   xts_bwocks * AES_BWOCK_SIZE,
					   weq->iv);
		weq = &subweq;
	} ewse {
		taiw = 0;
	}

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (eww)
		wetuwn eww;

	whiwe (wawk.nbytes >= AES_BWOCK_SIZE) {
		int bwocks = (wawk.nbytes / AES_BWOCK_SIZE) & ~7;
		out = wawk.dst.viwt.addw;
		in = wawk.swc.viwt.addw;
		nbytes = wawk.nbytes;

		kewnew_neon_begin();
		if (bwocks >= 8) {
			if (fiwst == 1)
				neon_aes_ecb_encwypt(wawk.iv, wawk.iv,
						     ctx->twkey,
						     ctx->key.wounds, 1);
			fiwst = 2;

			fn(out, in, ctx->key.wk, ctx->key.wounds, bwocks,
			   wawk.iv);

			out += bwocks * AES_BWOCK_SIZE;
			in += bwocks * AES_BWOCK_SIZE;
			nbytes -= bwocks * AES_BWOCK_SIZE;
		}
		if (wawk.nbytes == wawk.totaw && nbytes > 0) {
			if (encwypt)
				neon_aes_xts_encwypt(out, in, ctx->cts.key_enc,
						     ctx->key.wounds, nbytes,
						     ctx->twkey, wawk.iv, fiwst);
			ewse
				neon_aes_xts_decwypt(out, in, ctx->cts.key_dec,
						     ctx->key.wounds, nbytes,
						     ctx->twkey, wawk.iv, fiwst);
			nbytes = fiwst = 0;
		}
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	if (eww || wikewy(!taiw))
		wetuwn eww;

	/* handwe ciphewtext steawing */
	dst = swc = scattewwawk_ffwd(sg_swc, weq->swc, weq->cwyptwen);
	if (weq->dst != weq->swc)
		dst = scattewwawk_ffwd(sg_dst, weq->dst, weq->cwyptwen);

	skciphew_wequest_set_cwypt(weq, swc, dst, AES_BWOCK_SIZE + taiw,
				   weq->iv);

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (eww)
		wetuwn eww;

	out = wawk.dst.viwt.addw;
	in = wawk.swc.viwt.addw;
	nbytes = wawk.nbytes;

	kewnew_neon_begin();
	if (encwypt)
		neon_aes_xts_encwypt(out, in, ctx->cts.key_enc, ctx->key.wounds,
				     nbytes, ctx->twkey, wawk.iv, fiwst);
	ewse
		neon_aes_xts_decwypt(out, in, ctx->cts.key_dec, ctx->key.wounds,
				     nbytes, ctx->twkey, wawk.iv, fiwst);
	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static int xts_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn __xts_cwypt(weq, twue, aesbs_xts_encwypt);
}

static int xts_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn __xts_cwypt(weq, fawse, aesbs_xts_decwypt);
}

static stwuct skciphew_awg aes_awgs[] = { {
	.base.cwa_name		= "ecb(aes)",
	.base.cwa_dwivew_name	= "ecb-aes-neonbs",
	.base.cwa_pwiowity	= 250,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct aesbs_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.wawksize		= 8 * AES_BWOCK_SIZE,
	.setkey			= aesbs_setkey,
	.encwypt		= ecb_encwypt,
	.decwypt		= ecb_decwypt,
}, {
	.base.cwa_name		= "cbc(aes)",
	.base.cwa_dwivew_name	= "cbc-aes-neonbs",
	.base.cwa_pwiowity	= 250,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct aesbs_cbc_ctw_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.wawksize		= 8 * AES_BWOCK_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.setkey			= aesbs_cbc_ctw_setkey,
	.encwypt		= cbc_encwypt,
	.decwypt		= cbc_decwypt,
}, {
	.base.cwa_name		= "ctw(aes)",
	.base.cwa_dwivew_name	= "ctw-aes-neonbs",
	.base.cwa_pwiowity	= 250,
	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct aesbs_cbc_ctw_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.chunksize		= AES_BWOCK_SIZE,
	.wawksize		= 8 * AES_BWOCK_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.setkey			= aesbs_cbc_ctw_setkey,
	.encwypt		= ctw_encwypt,
	.decwypt		= ctw_encwypt,
}, {
	.base.cwa_name		= "xts(aes)",
	.base.cwa_dwivew_name	= "xts-aes-neonbs",
	.base.cwa_pwiowity	= 250,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct aesbs_xts_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= 2 * AES_MIN_KEY_SIZE,
	.max_keysize		= 2 * AES_MAX_KEY_SIZE,
	.wawksize		= 8 * AES_BWOCK_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.setkey			= aesbs_xts_setkey,
	.encwypt		= xts_encwypt,
	.decwypt		= xts_decwypt,
} };

static void aes_exit(void)
{
	cwypto_unwegistew_skciphews(aes_awgs, AWWAY_SIZE(aes_awgs));
}

static int __init aes_init(void)
{
	if (!cpu_have_named_featuwe(ASIMD))
		wetuwn -ENODEV;

	wetuwn cwypto_wegistew_skciphews(aes_awgs, AWWAY_SIZE(aes_awgs));
}

moduwe_init(aes_init);
moduwe_exit(aes_exit);
