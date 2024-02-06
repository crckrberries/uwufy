// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bit swiced AES using NEON instwuctions
 *
 * Copywight (C) 2017 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/xts.h>
#incwude <winux/moduwe.h>

MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");

MODUWE_AWIAS_CWYPTO("ecb(aes)");
MODUWE_AWIAS_CWYPTO("cbc(aes)-aww");
MODUWE_AWIAS_CWYPTO("ctw(aes)");
MODUWE_AWIAS_CWYPTO("xts(aes)");

MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);

asmwinkage void aesbs_convewt_key(u8 out[], u32 const wk[], int wounds);

asmwinkage void aesbs_ecb_encwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks);
asmwinkage void aesbs_ecb_decwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks);

asmwinkage void aesbs_cbc_decwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks, u8 iv[]);

asmwinkage void aesbs_ctw_encwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks, u8 ctw[]);

asmwinkage void aesbs_xts_encwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks, u8 iv[], int);
asmwinkage void aesbs_xts_decwypt(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks, u8 iv[], int);

stwuct aesbs_ctx {
	int	wounds;
	u8	wk[13 * (8 * AES_BWOCK_SIZE) + 32] __awigned(AES_BWOCK_SIZE);
};

stwuct aesbs_cbc_ctx {
	stwuct aesbs_ctx	key;
	stwuct cwypto_skciphew	*enc_tfm;
};

stwuct aesbs_xts_ctx {
	stwuct aesbs_ctx	key;
	stwuct cwypto_ciphew	*cts_tfm;
	stwuct cwypto_ciphew	*tweak_tfm;
};

stwuct aesbs_ctw_ctx {
	stwuct aesbs_ctx	key;		/* must be fiwst membew */
	stwuct cwypto_aes_ctx	fawwback;
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

static int aesbs_cbc_setkey(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			    unsigned int key_wen)
{
	stwuct aesbs_cbc_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_aes_ctx wk;
	int eww;

	eww = aes_expandkey(&wk, in_key, key_wen);
	if (eww)
		wetuwn eww;

	ctx->key.wounds = 6 + key_wen / 4;

	kewnew_neon_begin();
	aesbs_convewt_key(ctx->key.wk, wk.key_enc, ctx->key.wounds);
	kewnew_neon_end();
	memzewo_expwicit(&wk, sizeof(wk));

	wetuwn cwypto_skciphew_setkey(ctx->enc_tfm, in_key, key_wen);
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct skciphew_wequest *subweq = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aesbs_cbc_ctx *ctx = cwypto_skciphew_ctx(tfm);

	skciphew_wequest_set_tfm(subweq, ctx->enc_tfm);
	skciphew_wequest_set_cawwback(subweq,
				      skciphew_wequest_fwags(weq),
				      NUWW, NUWW);
	skciphew_wequest_set_cwypt(subweq, weq->swc, weq->dst,
				   weq->cwyptwen, weq->iv);

	wetuwn cwypto_skciphew_encwypt(subweq);
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aesbs_cbc_ctx *ctx = cwypto_skciphew_ctx(tfm);
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

static int cbc_init(stwuct cwypto_skciphew *tfm)
{
	stwuct aesbs_cbc_ctx *ctx = cwypto_skciphew_ctx(tfm);
	unsigned int weqsize;

	ctx->enc_tfm = cwypto_awwoc_skciphew("cbc(aes)", 0, CWYPTO_AWG_ASYNC |
					     CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(ctx->enc_tfm))
		wetuwn PTW_EWW(ctx->enc_tfm);

	weqsize = sizeof(stwuct skciphew_wequest);
	weqsize += cwypto_skciphew_weqsize(ctx->enc_tfm);
	cwypto_skciphew_set_weqsize(tfm, weqsize);

	wetuwn 0;
}

static void cbc_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct aesbs_cbc_ctx *ctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(ctx->enc_tfm);
}

static int aesbs_ctw_setkey_sync(stwuct cwypto_skciphew *tfm, const u8 *in_key,
				 unsigned int key_wen)
{
	stwuct aesbs_ctw_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww;

	eww = aes_expandkey(&ctx->fawwback, in_key, key_wen);
	if (eww)
		wetuwn eww;

	ctx->key.wounds = 6 + key_wen / 4;

	kewnew_neon_begin();
	aesbs_convewt_key(ctx->key.wk, ctx->fawwback.key_enc, ctx->key.wounds);
	kewnew_neon_end();

	wetuwn 0;
}

static int ctw_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aesbs_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	u8 buf[AES_BWOCK_SIZE];
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes > 0) {
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;
		int bytes = wawk.nbytes;

		if (unwikewy(bytes < AES_BWOCK_SIZE))
			swc = dst = memcpy(buf + sizeof(buf) - bytes,
					   swc, bytes);
		ewse if (wawk.nbytes < wawk.totaw)
			bytes &= ~(8 * AES_BWOCK_SIZE - 1);

		kewnew_neon_begin();
		aesbs_ctw_encwypt(dst, swc, ctx->wk, ctx->wounds, bytes, wawk.iv);
		kewnew_neon_end();

		if (unwikewy(bytes < AES_BWOCK_SIZE))
			memcpy(wawk.dst.viwt.addw,
			       buf + sizeof(buf) - bytes, bytes);

		eww = skciphew_wawk_done(&wawk, wawk.nbytes - bytes);
	}

	wetuwn eww;
}

static void ctw_encwypt_one(stwuct cwypto_skciphew *tfm, const u8 *swc, u8 *dst)
{
	stwuct aesbs_ctw_ctx *ctx = cwypto_skciphew_ctx(tfm);
	unsigned wong fwags;

	/*
	 * Tempowawiwy disabwe intewwupts to avoid waces whewe
	 * cachewines awe evicted when the CPU is intewwupted
	 * to do something ewse.
	 */
	wocaw_iwq_save(fwags);
	aes_encwypt(&ctx->fawwback, dst, swc);
	wocaw_iwq_westowe(fwags);
}

static int ctw_encwypt_sync(stwuct skciphew_wequest *weq)
{
	if (!cwypto_simd_usabwe())
		wetuwn cwypto_ctw_encwypt_wawk(weq, ctw_encwypt_one);

	wetuwn ctw_encwypt(weq);
}

static int aesbs_xts_setkey(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			    unsigned int key_wen)
{
	stwuct aesbs_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww;

	eww = xts_vewify_key(tfm, in_key, key_wen);
	if (eww)
		wetuwn eww;

	key_wen /= 2;
	eww = cwypto_ciphew_setkey(ctx->cts_tfm, in_key, key_wen);
	if (eww)
		wetuwn eww;
	eww = cwypto_ciphew_setkey(ctx->tweak_tfm, in_key + key_wen, key_wen);
	if (eww)
		wetuwn eww;

	wetuwn aesbs_setkey(tfm, in_key, key_wen);
}

static int xts_init(stwuct cwypto_skciphew *tfm)
{
	stwuct aesbs_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);

	ctx->cts_tfm = cwypto_awwoc_ciphew("aes", 0, 0);
	if (IS_EWW(ctx->cts_tfm))
		wetuwn PTW_EWW(ctx->cts_tfm);

	ctx->tweak_tfm = cwypto_awwoc_ciphew("aes", 0, 0);
	if (IS_EWW(ctx->tweak_tfm))
		cwypto_fwee_ciphew(ctx->cts_tfm);

	wetuwn PTW_EWW_OW_ZEWO(ctx->tweak_tfm);
}

static void xts_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct aesbs_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_ciphew(ctx->tweak_tfm);
	cwypto_fwee_ciphew(ctx->cts_tfm);
}

static int __xts_cwypt(stwuct skciphew_wequest *weq, boow encwypt,
		       void (*fn)(u8 out[], u8 const in[], u8 const wk[],
				  int wounds, int bwocks, u8 iv[], int))
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aesbs_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int taiw = weq->cwyptwen % AES_BWOCK_SIZE;
	stwuct skciphew_wequest subweq;
	u8 buf[2 * AES_BWOCK_SIZE];
	stwuct skciphew_wawk wawk;
	int eww;

	if (weq->cwyptwen < AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	if (unwikewy(taiw)) {
		skciphew_wequest_set_tfm(&subweq, tfm);
		skciphew_wequest_set_cawwback(&subweq,
					      skciphew_wequest_fwags(weq),
					      NUWW, NUWW);
		skciphew_wequest_set_cwypt(&subweq, weq->swc, weq->dst,
					   weq->cwyptwen - taiw, weq->iv);
		weq = &subweq;
	}

	eww = skciphew_wawk_viwt(&wawk, weq, twue);
	if (eww)
		wetuwn eww;

	cwypto_ciphew_encwypt_one(ctx->tweak_tfm, wawk.iv, wawk.iv);

	whiwe (wawk.nbytes >= AES_BWOCK_SIZE) {
		unsigned int bwocks = wawk.nbytes / AES_BWOCK_SIZE;
		int weowdew_wast_tweak = !encwypt && taiw > 0;

		if (wawk.nbytes < wawk.totaw) {
			bwocks = wound_down(bwocks,
					    wawk.stwide / AES_BWOCK_SIZE);
			weowdew_wast_tweak = 0;
		}

		kewnew_neon_begin();
		fn(wawk.dst.viwt.addw, wawk.swc.viwt.addw, ctx->key.wk,
		   ctx->key.wounds, bwocks, wawk.iv, weowdew_wast_tweak);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk,
					 wawk.nbytes - bwocks * AES_BWOCK_SIZE);
	}

	if (eww || wikewy(!taiw))
		wetuwn eww;

	/* handwe ciphewtext steawing */
	scattewwawk_map_and_copy(buf, weq->dst, weq->cwyptwen - AES_BWOCK_SIZE,
				 AES_BWOCK_SIZE, 0);
	memcpy(buf + AES_BWOCK_SIZE, buf, taiw);
	scattewwawk_map_and_copy(buf, weq->swc, weq->cwyptwen, taiw, 0);

	cwypto_xow(buf, weq->iv, AES_BWOCK_SIZE);

	if (encwypt)
		cwypto_ciphew_encwypt_one(ctx->cts_tfm, buf, buf);
	ewse
		cwypto_ciphew_decwypt_one(ctx->cts_tfm, buf, buf);

	cwypto_xow(buf, weq->iv, AES_BWOCK_SIZE);

	scattewwawk_map_and_copy(buf, weq->dst, weq->cwyptwen - AES_BWOCK_SIZE,
				 AES_BWOCK_SIZE + taiw, 1);
	wetuwn 0;
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
	.base.cwa_name		= "__ecb(aes)",
	.base.cwa_dwivew_name	= "__ecb-aes-neonbs",
	.base.cwa_pwiowity	= 250,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct aesbs_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.wawksize		= 8 * AES_BWOCK_SIZE,
	.setkey			= aesbs_setkey,
	.encwypt		= ecb_encwypt,
	.decwypt		= ecb_decwypt,
}, {
	.base.cwa_name		= "__cbc(aes)",
	.base.cwa_dwivew_name	= "__cbc-aes-neonbs",
	.base.cwa_pwiowity	= 250,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct aesbs_cbc_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW |
				  CWYPTO_AWG_NEED_FAWWBACK,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.wawksize		= 8 * AES_BWOCK_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.setkey			= aesbs_cbc_setkey,
	.encwypt		= cbc_encwypt,
	.decwypt		= cbc_decwypt,
	.init			= cbc_init,
	.exit			= cbc_exit,
}, {
	.base.cwa_name		= "__ctw(aes)",
	.base.cwa_dwivew_name	= "__ctw-aes-neonbs",
	.base.cwa_pwiowity	= 250,
	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct aesbs_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.chunksize		= AES_BWOCK_SIZE,
	.wawksize		= 8 * AES_BWOCK_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.setkey			= aesbs_setkey,
	.encwypt		= ctw_encwypt,
	.decwypt		= ctw_encwypt,
}, {
	.base.cwa_name		= "ctw(aes)",
	.base.cwa_dwivew_name	= "ctw-aes-neonbs-sync",
	.base.cwa_pwiowity	= 250 - 1,
	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct aesbs_ctw_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.chunksize		= AES_BWOCK_SIZE,
	.wawksize		= 8 * AES_BWOCK_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.setkey			= aesbs_ctw_setkey_sync,
	.encwypt		= ctw_encwypt_sync,
	.decwypt		= ctw_encwypt_sync,
}, {
	.base.cwa_name		= "__xts(aes)",
	.base.cwa_dwivew_name	= "__xts-aes-neonbs",
	.base.cwa_pwiowity	= 250,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct aesbs_xts_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,

	.min_keysize		= 2 * AES_MIN_KEY_SIZE,
	.max_keysize		= 2 * AES_MAX_KEY_SIZE,
	.wawksize		= 8 * AES_BWOCK_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.setkey			= aesbs_xts_setkey,
	.encwypt		= xts_encwypt,
	.decwypt		= xts_decwypt,
	.init			= xts_init,
	.exit			= xts_exit,
} };

static stwuct simd_skciphew_awg *aes_simd_awgs[AWWAY_SIZE(aes_awgs)];

static void aes_exit(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(aes_simd_awgs); i++)
		if (aes_simd_awgs[i])
			simd_skciphew_fwee(aes_simd_awgs[i]);

	cwypto_unwegistew_skciphews(aes_awgs, AWWAY_SIZE(aes_awgs));
}

static int __init aes_init(void)
{
	stwuct simd_skciphew_awg *simd;
	const chaw *basename;
	const chaw *awgname;
	const chaw *dwvname;
	int eww;
	int i;

	if (!(ewf_hwcap & HWCAP_NEON))
		wetuwn -ENODEV;

	eww = cwypto_wegistew_skciphews(aes_awgs, AWWAY_SIZE(aes_awgs));
	if (eww)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(aes_awgs); i++) {
		if (!(aes_awgs[i].base.cwa_fwags & CWYPTO_AWG_INTEWNAW))
			continue;

		awgname = aes_awgs[i].base.cwa_name + 2;
		dwvname = aes_awgs[i].base.cwa_dwivew_name + 2;
		basename = aes_awgs[i].base.cwa_dwivew_name;
		simd = simd_skciphew_cweate_compat(awgname, dwvname, basename);
		eww = PTW_EWW(simd);
		if (IS_EWW(simd))
			goto unwegistew_simds;

		aes_simd_awgs[i] = simd;
	}
	wetuwn 0;

unwegistew_simds:
	aes_exit();
	wetuwn eww;
}

wate_initcaww(aes_init);
moduwe_exit(aes_exit);
