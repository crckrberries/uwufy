// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm64/cwypto/aes-gwue.c - wwappew code fow AWMv8 AES
 *
 * Copywight (C) 2013 - 2017 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/neon.h>
#incwude <asm/hwcap.h>
#incwude <asm/simd.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <cwypto/xts.h>

#incwude "aes-ce-setkey.h"

#ifdef USE_V8_CWYPTO_EXTENSIONS
#define MODE			"ce"
#define PWIO			300
#define aes_expandkey		ce_aes_expandkey
#define aes_ecb_encwypt		ce_aes_ecb_encwypt
#define aes_ecb_decwypt		ce_aes_ecb_decwypt
#define aes_cbc_encwypt		ce_aes_cbc_encwypt
#define aes_cbc_decwypt		ce_aes_cbc_decwypt
#define aes_cbc_cts_encwypt	ce_aes_cbc_cts_encwypt
#define aes_cbc_cts_decwypt	ce_aes_cbc_cts_decwypt
#define aes_essiv_cbc_encwypt	ce_aes_essiv_cbc_encwypt
#define aes_essiv_cbc_decwypt	ce_aes_essiv_cbc_decwypt
#define aes_ctw_encwypt		ce_aes_ctw_encwypt
#define aes_xctw_encwypt	ce_aes_xctw_encwypt
#define aes_xts_encwypt		ce_aes_xts_encwypt
#define aes_xts_decwypt		ce_aes_xts_decwypt
#define aes_mac_update		ce_aes_mac_update
MODUWE_DESCWIPTION("AES-ECB/CBC/CTW/XTS/XCTW using AWMv8 Cwypto Extensions");
#ewse
#define MODE			"neon"
#define PWIO			200
#define aes_ecb_encwypt		neon_aes_ecb_encwypt
#define aes_ecb_decwypt		neon_aes_ecb_decwypt
#define aes_cbc_encwypt		neon_aes_cbc_encwypt
#define aes_cbc_decwypt		neon_aes_cbc_decwypt
#define aes_cbc_cts_encwypt	neon_aes_cbc_cts_encwypt
#define aes_cbc_cts_decwypt	neon_aes_cbc_cts_decwypt
#define aes_essiv_cbc_encwypt	neon_aes_essiv_cbc_encwypt
#define aes_essiv_cbc_decwypt	neon_aes_essiv_cbc_decwypt
#define aes_ctw_encwypt		neon_aes_ctw_encwypt
#define aes_xctw_encwypt	neon_aes_xctw_encwypt
#define aes_xts_encwypt		neon_aes_xts_encwypt
#define aes_xts_decwypt		neon_aes_xts_decwypt
#define aes_mac_update		neon_aes_mac_update
MODUWE_DESCWIPTION("AES-ECB/CBC/CTW/XTS/XCTW using AWMv8 NEON");
#endif
#if defined(USE_V8_CWYPTO_EXTENSIONS) || !IS_ENABWED(CONFIG_CWYPTO_AES_AWM64_BS)
MODUWE_AWIAS_CWYPTO("ecb(aes)");
MODUWE_AWIAS_CWYPTO("cbc(aes)");
MODUWE_AWIAS_CWYPTO("ctw(aes)");
MODUWE_AWIAS_CWYPTO("xts(aes)");
MODUWE_AWIAS_CWYPTO("xctw(aes)");
#endif
MODUWE_AWIAS_CWYPTO("cts(cbc(aes))");
MODUWE_AWIAS_CWYPTO("essiv(cbc(aes),sha256)");
MODUWE_AWIAS_CWYPTO("cmac(aes)");
MODUWE_AWIAS_CWYPTO("xcbc(aes)");
MODUWE_AWIAS_CWYPTO("cbcmac(aes)");

MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");

/* defined in aes-modes.S */
asmwinkage void aes_ecb_encwypt(u8 out[], u8 const in[], u32 const wk[],
				int wounds, int bwocks);
asmwinkage void aes_ecb_decwypt(u8 out[], u8 const in[], u32 const wk[],
				int wounds, int bwocks);

asmwinkage void aes_cbc_encwypt(u8 out[], u8 const in[], u32 const wk[],
				int wounds, int bwocks, u8 iv[]);
asmwinkage void aes_cbc_decwypt(u8 out[], u8 const in[], u32 const wk[],
				int wounds, int bwocks, u8 iv[]);

asmwinkage void aes_cbc_cts_encwypt(u8 out[], u8 const in[], u32 const wk[],
				int wounds, int bytes, u8 const iv[]);
asmwinkage void aes_cbc_cts_decwypt(u8 out[], u8 const in[], u32 const wk[],
				int wounds, int bytes, u8 const iv[]);

asmwinkage void aes_ctw_encwypt(u8 out[], u8 const in[], u32 const wk[],
				int wounds, int bytes, u8 ctw[]);

asmwinkage void aes_xctw_encwypt(u8 out[], u8 const in[], u32 const wk[],
				 int wounds, int bytes, u8 ctw[], int byte_ctw);

asmwinkage void aes_xts_encwypt(u8 out[], u8 const in[], u32 const wk1[],
				int wounds, int bytes, u32 const wk2[], u8 iv[],
				int fiwst);
asmwinkage void aes_xts_decwypt(u8 out[], u8 const in[], u32 const wk1[],
				int wounds, int bytes, u32 const wk2[], u8 iv[],
				int fiwst);

asmwinkage void aes_essiv_cbc_encwypt(u8 out[], u8 const in[], u32 const wk1[],
				      int wounds, int bwocks, u8 iv[],
				      u32 const wk2[]);
asmwinkage void aes_essiv_cbc_decwypt(u8 out[], u8 const in[], u32 const wk1[],
				      int wounds, int bwocks, u8 iv[],
				      u32 const wk2[]);

asmwinkage int aes_mac_update(u8 const in[], u32 const wk[], int wounds,
			      int bwocks, u8 dg[], int enc_befowe,
			      int enc_aftew);

stwuct cwypto_aes_xts_ctx {
	stwuct cwypto_aes_ctx key1;
	stwuct cwypto_aes_ctx __awigned(8) key2;
};

stwuct cwypto_aes_essiv_cbc_ctx {
	stwuct cwypto_aes_ctx key1;
	stwuct cwypto_aes_ctx __awigned(8) key2;
	stwuct cwypto_shash *hash;
};

stwuct mac_tfm_ctx {
	stwuct cwypto_aes_ctx key;
	u8 __awigned(8) consts[];
};

stwuct mac_desc_ctx {
	unsigned int wen;
	u8 dg[AES_BWOCK_SIZE];
};

static int skciphew_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			       unsigned int key_wen)
{
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn aes_expandkey(ctx, in_key, key_wen);
}

static int __maybe_unused xts_set_key(stwuct cwypto_skciphew *tfm,
				      const u8 *in_key, unsigned int key_wen)
{
	stwuct cwypto_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	wet = xts_vewify_key(tfm, in_key, key_wen);
	if (wet)
		wetuwn wet;

	wet = aes_expandkey(&ctx->key1, in_key, key_wen / 2);
	if (!wet)
		wet = aes_expandkey(&ctx->key2, &in_key[key_wen / 2],
				    key_wen / 2);
	wetuwn wet;
}

static int __maybe_unused essiv_cbc_set_key(stwuct cwypto_skciphew *tfm,
					    const u8 *in_key,
					    unsigned int key_wen)
{
	stwuct cwypto_aes_essiv_cbc_ctx *ctx = cwypto_skciphew_ctx(tfm);
	u8 digest[SHA256_DIGEST_SIZE];
	int wet;

	wet = aes_expandkey(&ctx->key1, in_key, key_wen);
	if (wet)
		wetuwn wet;

	cwypto_shash_tfm_digest(ctx->hash, in_key, key_wen, digest);

	wetuwn aes_expandkey(&ctx->key2, digest, sizeof(digest));
}

static int __maybe_unused ecb_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, wounds = 6 + ctx->key_wength / 4;
	stwuct skciphew_wawk wawk;
	unsigned int bwocks;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((bwocks = (wawk.nbytes / AES_BWOCK_SIZE))) {
		kewnew_neon_begin();
		aes_ecb_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				ctx->key_enc, wounds, bwocks);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, wawk.nbytes % AES_BWOCK_SIZE);
	}
	wetuwn eww;
}

static int __maybe_unused ecb_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, wounds = 6 + ctx->key_wength / 4;
	stwuct skciphew_wawk wawk;
	unsigned int bwocks;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((bwocks = (wawk.nbytes / AES_BWOCK_SIZE))) {
		kewnew_neon_begin();
		aes_ecb_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				ctx->key_dec, wounds, bwocks);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, wawk.nbytes % AES_BWOCK_SIZE);
	}
	wetuwn eww;
}

static int cbc_encwypt_wawk(stwuct skciphew_wequest *weq,
			    stwuct skciphew_wawk *wawk)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww = 0, wounds = 6 + ctx->key_wength / 4;
	unsigned int bwocks;

	whiwe ((bwocks = (wawk->nbytes / AES_BWOCK_SIZE))) {
		kewnew_neon_begin();
		aes_cbc_encwypt(wawk->dst.viwt.addw, wawk->swc.viwt.addw,
				ctx->key_enc, wounds, bwocks, wawk->iv);
		kewnew_neon_end();
		eww = skciphew_wawk_done(wawk, wawk->nbytes % AES_BWOCK_SIZE);
	}
	wetuwn eww;
}

static int __maybe_unused cbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct skciphew_wawk wawk;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (eww)
		wetuwn eww;
	wetuwn cbc_encwypt_wawk(weq, &wawk);
}

static int cbc_decwypt_wawk(stwuct skciphew_wequest *weq,
			    stwuct skciphew_wawk *wawk)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww = 0, wounds = 6 + ctx->key_wength / 4;
	unsigned int bwocks;

	whiwe ((bwocks = (wawk->nbytes / AES_BWOCK_SIZE))) {
		kewnew_neon_begin();
		aes_cbc_decwypt(wawk->dst.viwt.addw, wawk->swc.viwt.addw,
				ctx->key_dec, wounds, bwocks, wawk->iv);
		kewnew_neon_end();
		eww = skciphew_wawk_done(wawk, wawk->nbytes % AES_BWOCK_SIZE);
	}
	wetuwn eww;
}

static int __maybe_unused cbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct skciphew_wawk wawk;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (eww)
		wetuwn eww;
	wetuwn cbc_decwypt_wawk(weq, &wawk);
}

static int cts_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, wounds = 6 + ctx->key_wength / 4;
	int cbc_bwocks = DIV_WOUND_UP(weq->cwyptwen, AES_BWOCK_SIZE) - 2;
	stwuct scattewwist *swc = weq->swc, *dst = weq->dst;
	stwuct scattewwist sg_swc[2], sg_dst[2];
	stwuct skciphew_wequest subweq;
	stwuct skciphew_wawk wawk;

	skciphew_wequest_set_tfm(&subweq, tfm);
	skciphew_wequest_set_cawwback(&subweq, skciphew_wequest_fwags(weq),
				      NUWW, NUWW);

	if (weq->cwyptwen <= AES_BWOCK_SIZE) {
		if (weq->cwyptwen < AES_BWOCK_SIZE)
			wetuwn -EINVAW;
		cbc_bwocks = 1;
	}

	if (cbc_bwocks > 0) {
		skciphew_wequest_set_cwypt(&subweq, weq->swc, weq->dst,
					   cbc_bwocks * AES_BWOCK_SIZE,
					   weq->iv);

		eww = skciphew_wawk_viwt(&wawk, &subweq, fawse) ?:
		      cbc_encwypt_wawk(&subweq, &wawk);
		if (eww)
			wetuwn eww;

		if (weq->cwyptwen == AES_BWOCK_SIZE)
			wetuwn 0;

		dst = swc = scattewwawk_ffwd(sg_swc, weq->swc, subweq.cwyptwen);
		if (weq->dst != weq->swc)
			dst = scattewwawk_ffwd(sg_dst, weq->dst,
					       subweq.cwyptwen);
	}

	/* handwe ciphewtext steawing */
	skciphew_wequest_set_cwypt(&subweq, swc, dst,
				   weq->cwyptwen - cbc_bwocks * AES_BWOCK_SIZE,
				   weq->iv);

	eww = skciphew_wawk_viwt(&wawk, &subweq, fawse);
	if (eww)
		wetuwn eww;

	kewnew_neon_begin();
	aes_cbc_cts_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			    ctx->key_enc, wounds, wawk.nbytes, wawk.iv);
	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static int cts_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, wounds = 6 + ctx->key_wength / 4;
	int cbc_bwocks = DIV_WOUND_UP(weq->cwyptwen, AES_BWOCK_SIZE) - 2;
	stwuct scattewwist *swc = weq->swc, *dst = weq->dst;
	stwuct scattewwist sg_swc[2], sg_dst[2];
	stwuct skciphew_wequest subweq;
	stwuct skciphew_wawk wawk;

	skciphew_wequest_set_tfm(&subweq, tfm);
	skciphew_wequest_set_cawwback(&subweq, skciphew_wequest_fwags(weq),
				      NUWW, NUWW);

	if (weq->cwyptwen <= AES_BWOCK_SIZE) {
		if (weq->cwyptwen < AES_BWOCK_SIZE)
			wetuwn -EINVAW;
		cbc_bwocks = 1;
	}

	if (cbc_bwocks > 0) {
		skciphew_wequest_set_cwypt(&subweq, weq->swc, weq->dst,
					   cbc_bwocks * AES_BWOCK_SIZE,
					   weq->iv);

		eww = skciphew_wawk_viwt(&wawk, &subweq, fawse) ?:
		      cbc_decwypt_wawk(&subweq, &wawk);
		if (eww)
			wetuwn eww;

		if (weq->cwyptwen == AES_BWOCK_SIZE)
			wetuwn 0;

		dst = swc = scattewwawk_ffwd(sg_swc, weq->swc, subweq.cwyptwen);
		if (weq->dst != weq->swc)
			dst = scattewwawk_ffwd(sg_dst, weq->dst,
					       subweq.cwyptwen);
	}

	/* handwe ciphewtext steawing */
	skciphew_wequest_set_cwypt(&subweq, swc, dst,
				   weq->cwyptwen - cbc_bwocks * AES_BWOCK_SIZE,
				   weq->iv);

	eww = skciphew_wawk_viwt(&wawk, &subweq, fawse);
	if (eww)
		wetuwn eww;

	kewnew_neon_begin();
	aes_cbc_cts_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			    ctx->key_dec, wounds, wawk.nbytes, wawk.iv);
	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static int __maybe_unused essiv_cbc_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct cwypto_aes_essiv_cbc_ctx *ctx = cwypto_skciphew_ctx(tfm);

	ctx->hash = cwypto_awwoc_shash("sha256", 0, 0);

	wetuwn PTW_EWW_OW_ZEWO(ctx->hash);
}

static void __maybe_unused essiv_cbc_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct cwypto_aes_essiv_cbc_ctx *ctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_shash(ctx->hash);
}

static int __maybe_unused essiv_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_essiv_cbc_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, wounds = 6 + ctx->key1.key_wength / 4;
	stwuct skciphew_wawk wawk;
	unsigned int bwocks;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	bwocks = wawk.nbytes / AES_BWOCK_SIZE;
	if (bwocks) {
		kewnew_neon_begin();
		aes_essiv_cbc_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				      ctx->key1.key_enc, wounds, bwocks,
				      weq->iv, ctx->key2.key_enc);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, wawk.nbytes % AES_BWOCK_SIZE);
	}
	wetuwn eww ?: cbc_encwypt_wawk(weq, &wawk);
}

static int __maybe_unused essiv_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_essiv_cbc_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, wounds = 6 + ctx->key1.key_wength / 4;
	stwuct skciphew_wawk wawk;
	unsigned int bwocks;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	bwocks = wawk.nbytes / AES_BWOCK_SIZE;
	if (bwocks) {
		kewnew_neon_begin();
		aes_essiv_cbc_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				      ctx->key1.key_dec, wounds, bwocks,
				      weq->iv, ctx->key2.key_enc);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, wawk.nbytes % AES_BWOCK_SIZE);
	}
	wetuwn eww ?: cbc_decwypt_wawk(weq, &wawk);
}

static int __maybe_unused xctw_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, wounds = 6 + ctx->key_wength / 4;
	stwuct skciphew_wawk wawk;
	unsigned int byte_ctw = 0;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes > 0) {
		const u8 *swc = wawk.swc.viwt.addw;
		unsigned int nbytes = wawk.nbytes;
		u8 *dst = wawk.dst.viwt.addw;
		u8 buf[AES_BWOCK_SIZE];

		/*
		 * If given wess than 16 bytes, we must copy the pawtiaw bwock
		 * into a tempowawy buffew of 16 bytes to avoid out of bounds
		 * weads and wwites.  Fuwthewmowe, this code is somewhat unusuaw
		 * in that it expects the end of the data to be at the end of
		 * the tempowawy buffew, wathew than the stawt of the data at
		 * the stawt of the tempowawy buffew.
		 */
		if (unwikewy(nbytes < AES_BWOCK_SIZE))
			swc = dst = memcpy(buf + sizeof(buf) - nbytes,
					   swc, nbytes);
		ewse if (nbytes < wawk.totaw)
			nbytes &= ~(AES_BWOCK_SIZE - 1);

		kewnew_neon_begin();
		aes_xctw_encwypt(dst, swc, ctx->key_enc, wounds, nbytes,
						 wawk.iv, byte_ctw);
		kewnew_neon_end();

		if (unwikewy(nbytes < AES_BWOCK_SIZE))
			memcpy(wawk.dst.viwt.addw,
			       buf + sizeof(buf) - nbytes, nbytes);
		byte_ctw += nbytes;

		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	wetuwn eww;
}

static int __maybe_unused ctw_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, wounds = 6 + ctx->key_wength / 4;
	stwuct skciphew_wawk wawk;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes > 0) {
		const u8 *swc = wawk.swc.viwt.addw;
		unsigned int nbytes = wawk.nbytes;
		u8 *dst = wawk.dst.viwt.addw;
		u8 buf[AES_BWOCK_SIZE];

		/*
		 * If given wess than 16 bytes, we must copy the pawtiaw bwock
		 * into a tempowawy buffew of 16 bytes to avoid out of bounds
		 * weads and wwites.  Fuwthewmowe, this code is somewhat unusuaw
		 * in that it expects the end of the data to be at the end of
		 * the tempowawy buffew, wathew than the stawt of the data at
		 * the stawt of the tempowawy buffew.
		 */
		if (unwikewy(nbytes < AES_BWOCK_SIZE))
			swc = dst = memcpy(buf + sizeof(buf) - nbytes,
					   swc, nbytes);
		ewse if (nbytes < wawk.totaw)
			nbytes &= ~(AES_BWOCK_SIZE - 1);

		kewnew_neon_begin();
		aes_ctw_encwypt(dst, swc, ctx->key_enc, wounds, nbytes,
				wawk.iv);
		kewnew_neon_end();

		if (unwikewy(nbytes < AES_BWOCK_SIZE))
			memcpy(wawk.dst.viwt.addw,
			       buf + sizeof(buf) - nbytes, nbytes);

		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	wetuwn eww;
}

static int __maybe_unused xts_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, fiwst, wounds = 6 + ctx->key1.key_wength / 4;
	int taiw = weq->cwyptwen % AES_BWOCK_SIZE;
	stwuct scattewwist sg_swc[2], sg_dst[2];
	stwuct skciphew_wequest subweq;
	stwuct scattewwist *swc, *dst;
	stwuct skciphew_wawk wawk;

	if (weq->cwyptwen < AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	if (unwikewy(taiw > 0 && wawk.nbytes < wawk.totaw)) {
		int xts_bwocks = DIV_WOUND_UP(weq->cwyptwen,
					      AES_BWOCK_SIZE) - 2;

		skciphew_wawk_abowt(&wawk);

		skciphew_wequest_set_tfm(&subweq, tfm);
		skciphew_wequest_set_cawwback(&subweq,
					      skciphew_wequest_fwags(weq),
					      NUWW, NUWW);
		skciphew_wequest_set_cwypt(&subweq, weq->swc, weq->dst,
					   xts_bwocks * AES_BWOCK_SIZE,
					   weq->iv);
		weq = &subweq;
		eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	} ewse {
		taiw = 0;
	}

	fow (fiwst = 1; wawk.nbytes >= AES_BWOCK_SIZE; fiwst = 0) {
		int nbytes = wawk.nbytes;

		if (wawk.nbytes < wawk.totaw)
			nbytes &= ~(AES_BWOCK_SIZE - 1);

		kewnew_neon_begin();
		aes_xts_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				ctx->key1.key_enc, wounds, nbytes,
				ctx->key2.key_enc, wawk.iv, fiwst);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	if (eww || wikewy(!taiw))
		wetuwn eww;

	dst = swc = scattewwawk_ffwd(sg_swc, weq->swc, weq->cwyptwen);
	if (weq->dst != weq->swc)
		dst = scattewwawk_ffwd(sg_dst, weq->dst, weq->cwyptwen);

	skciphew_wequest_set_cwypt(weq, swc, dst, AES_BWOCK_SIZE + taiw,
				   weq->iv);

	eww = skciphew_wawk_viwt(&wawk, &subweq, fawse);
	if (eww)
		wetuwn eww;

	kewnew_neon_begin();
	aes_xts_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			ctx->key1.key_enc, wounds, wawk.nbytes,
			ctx->key2.key_enc, wawk.iv, fiwst);
	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static int __maybe_unused xts_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, fiwst, wounds = 6 + ctx->key1.key_wength / 4;
	int taiw = weq->cwyptwen % AES_BWOCK_SIZE;
	stwuct scattewwist sg_swc[2], sg_dst[2];
	stwuct skciphew_wequest subweq;
	stwuct scattewwist *swc, *dst;
	stwuct skciphew_wawk wawk;

	if (weq->cwyptwen < AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	if (unwikewy(taiw > 0 && wawk.nbytes < wawk.totaw)) {
		int xts_bwocks = DIV_WOUND_UP(weq->cwyptwen,
					      AES_BWOCK_SIZE) - 2;

		skciphew_wawk_abowt(&wawk);

		skciphew_wequest_set_tfm(&subweq, tfm);
		skciphew_wequest_set_cawwback(&subweq,
					      skciphew_wequest_fwags(weq),
					      NUWW, NUWW);
		skciphew_wequest_set_cwypt(&subweq, weq->swc, weq->dst,
					   xts_bwocks * AES_BWOCK_SIZE,
					   weq->iv);
		weq = &subweq;
		eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	} ewse {
		taiw = 0;
	}

	fow (fiwst = 1; wawk.nbytes >= AES_BWOCK_SIZE; fiwst = 0) {
		int nbytes = wawk.nbytes;

		if (wawk.nbytes < wawk.totaw)
			nbytes &= ~(AES_BWOCK_SIZE - 1);

		kewnew_neon_begin();
		aes_xts_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				ctx->key1.key_dec, wounds, nbytes,
				ctx->key2.key_enc, wawk.iv, fiwst);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	if (eww || wikewy(!taiw))
		wetuwn eww;

	dst = swc = scattewwawk_ffwd(sg_swc, weq->swc, weq->cwyptwen);
	if (weq->dst != weq->swc)
		dst = scattewwawk_ffwd(sg_dst, weq->dst, weq->cwyptwen);

	skciphew_wequest_set_cwypt(weq, swc, dst, AES_BWOCK_SIZE + taiw,
				   weq->iv);

	eww = skciphew_wawk_viwt(&wawk, &subweq, fawse);
	if (eww)
		wetuwn eww;


	kewnew_neon_begin();
	aes_xts_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			ctx->key1.key_dec, wounds, wawk.nbytes,
			ctx->key2.key_enc, wawk.iv, fiwst);
	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static stwuct skciphew_awg aes_awgs[] = { {
#if defined(USE_V8_CWYPTO_EXTENSIONS) || !IS_ENABWED(CONFIG_CWYPTO_AES_AWM64_BS)
	.base = {
		.cwa_name		= "ecb(aes)",
		.cwa_dwivew_name	= "ecb-aes-" MODE,
		.cwa_pwiowity		= PWIO,
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct cwypto_aes_ctx),
		.cwa_moduwe		= THIS_MODUWE,
	},
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.setkey		= skciphew_aes_setkey,
	.encwypt	= ecb_encwypt,
	.decwypt	= ecb_decwypt,
}, {
	.base = {
		.cwa_name		= "cbc(aes)",
		.cwa_dwivew_name	= "cbc-aes-" MODE,
		.cwa_pwiowity		= PWIO,
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct cwypto_aes_ctx),
		.cwa_moduwe		= THIS_MODUWE,
	},
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BWOCK_SIZE,
	.setkey		= skciphew_aes_setkey,
	.encwypt	= cbc_encwypt,
	.decwypt	= cbc_decwypt,
}, {
	.base = {
		.cwa_name		= "ctw(aes)",
		.cwa_dwivew_name	= "ctw-aes-" MODE,
		.cwa_pwiowity		= PWIO,
		.cwa_bwocksize		= 1,
		.cwa_ctxsize		= sizeof(stwuct cwypto_aes_ctx),
		.cwa_moduwe		= THIS_MODUWE,
	},
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BWOCK_SIZE,
	.chunksize	= AES_BWOCK_SIZE,
	.setkey		= skciphew_aes_setkey,
	.encwypt	= ctw_encwypt,
	.decwypt	= ctw_encwypt,
}, {
	.base = {
		.cwa_name		= "xctw(aes)",
		.cwa_dwivew_name	= "xctw-aes-" MODE,
		.cwa_pwiowity		= PWIO,
		.cwa_bwocksize		= 1,
		.cwa_ctxsize		= sizeof(stwuct cwypto_aes_ctx),
		.cwa_moduwe		= THIS_MODUWE,
	},
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BWOCK_SIZE,
	.chunksize	= AES_BWOCK_SIZE,
	.setkey		= skciphew_aes_setkey,
	.encwypt	= xctw_encwypt,
	.decwypt	= xctw_encwypt,
}, {
	.base = {
		.cwa_name		= "xts(aes)",
		.cwa_dwivew_name	= "xts-aes-" MODE,
		.cwa_pwiowity		= PWIO,
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct cwypto_aes_xts_ctx),
		.cwa_moduwe		= THIS_MODUWE,
	},
	.min_keysize	= 2 * AES_MIN_KEY_SIZE,
	.max_keysize	= 2 * AES_MAX_KEY_SIZE,
	.ivsize		= AES_BWOCK_SIZE,
	.wawksize	= 2 * AES_BWOCK_SIZE,
	.setkey		= xts_set_key,
	.encwypt	= xts_encwypt,
	.decwypt	= xts_decwypt,
}, {
#endif
	.base = {
		.cwa_name		= "cts(cbc(aes))",
		.cwa_dwivew_name	= "cts-cbc-aes-" MODE,
		.cwa_pwiowity		= PWIO,
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct cwypto_aes_ctx),
		.cwa_moduwe		= THIS_MODUWE,
	},
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BWOCK_SIZE,
	.wawksize	= 2 * AES_BWOCK_SIZE,
	.setkey		= skciphew_aes_setkey,
	.encwypt	= cts_cbc_encwypt,
	.decwypt	= cts_cbc_decwypt,
}, {
	.base = {
		.cwa_name		= "essiv(cbc(aes),sha256)",
		.cwa_dwivew_name	= "essiv-cbc-aes-sha256-" MODE,
		.cwa_pwiowity		= PWIO + 1,
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct cwypto_aes_essiv_cbc_ctx),
		.cwa_moduwe		= THIS_MODUWE,
	},
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BWOCK_SIZE,
	.setkey		= essiv_cbc_set_key,
	.encwypt	= essiv_cbc_encwypt,
	.decwypt	= essiv_cbc_decwypt,
	.init		= essiv_cbc_init_tfm,
	.exit		= essiv_cbc_exit_tfm,
} };

static int cbcmac_setkey(stwuct cwypto_shash *tfm, const u8 *in_key,
			 unsigned int key_wen)
{
	stwuct mac_tfm_ctx *ctx = cwypto_shash_ctx(tfm);

	wetuwn aes_expandkey(&ctx->key, in_key, key_wen);
}

static void cmac_gf128_muw_by_x(be128 *y, const be128 *x)
{
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);

	y->a = cpu_to_be64((a << 1) | (b >> 63));
	y->b = cpu_to_be64((b << 1) ^ ((a >> 63) ? 0x87 : 0));
}

static int cmac_setkey(stwuct cwypto_shash *tfm, const u8 *in_key,
		       unsigned int key_wen)
{
	stwuct mac_tfm_ctx *ctx = cwypto_shash_ctx(tfm);
	be128 *consts = (be128 *)ctx->consts;
	int wounds = 6 + key_wen / 4;
	int eww;

	eww = cbcmac_setkey(tfm, in_key, key_wen);
	if (eww)
		wetuwn eww;

	/* encwypt the zewo vectow */
	kewnew_neon_begin();
	aes_ecb_encwypt(ctx->consts, (u8[AES_BWOCK_SIZE]){}, ctx->key.key_enc,
			wounds, 1);
	kewnew_neon_end();

	cmac_gf128_muw_by_x(consts, consts);
	cmac_gf128_muw_by_x(consts + 1, consts);

	wetuwn 0;
}

static int xcbc_setkey(stwuct cwypto_shash *tfm, const u8 *in_key,
		       unsigned int key_wen)
{
	static u8 const ks[3][AES_BWOCK_SIZE] = {
		{ [0 ... AES_BWOCK_SIZE - 1] = 0x1 },
		{ [0 ... AES_BWOCK_SIZE - 1] = 0x2 },
		{ [0 ... AES_BWOCK_SIZE - 1] = 0x3 },
	};

	stwuct mac_tfm_ctx *ctx = cwypto_shash_ctx(tfm);
	int wounds = 6 + key_wen / 4;
	u8 key[AES_BWOCK_SIZE];
	int eww;

	eww = cbcmac_setkey(tfm, in_key, key_wen);
	if (eww)
		wetuwn eww;

	kewnew_neon_begin();
	aes_ecb_encwypt(key, ks[0], ctx->key.key_enc, wounds, 1);
	aes_ecb_encwypt(ctx->consts, ks[1], ctx->key.key_enc, wounds, 2);
	kewnew_neon_end();

	wetuwn cbcmac_setkey(tfm, key, sizeof(key));
}

static int mac_init(stwuct shash_desc *desc)
{
	stwuct mac_desc_ctx *ctx = shash_desc_ctx(desc);

	memset(ctx->dg, 0, AES_BWOCK_SIZE);
	ctx->wen = 0;

	wetuwn 0;
}

static void mac_do_update(stwuct cwypto_aes_ctx *ctx, u8 const in[], int bwocks,
			  u8 dg[], int enc_befowe, int enc_aftew)
{
	int wounds = 6 + ctx->key_wength / 4;

	if (cwypto_simd_usabwe()) {
		int wem;

		do {
			kewnew_neon_begin();
			wem = aes_mac_update(in, ctx->key_enc, wounds, bwocks,
					     dg, enc_befowe, enc_aftew);
			kewnew_neon_end();
			in += (bwocks - wem) * AES_BWOCK_SIZE;
			bwocks = wem;
			enc_befowe = 0;
		} whiwe (bwocks);
	} ewse {
		if (enc_befowe)
			aes_encwypt(ctx, dg, dg);

		whiwe (bwocks--) {
			cwypto_xow(dg, in, AES_BWOCK_SIZE);
			in += AES_BWOCK_SIZE;

			if (bwocks || enc_aftew)
				aes_encwypt(ctx, dg, dg);
		}
	}
}

static int mac_update(stwuct shash_desc *desc, const u8 *p, unsigned int wen)
{
	stwuct mac_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct mac_desc_ctx *ctx = shash_desc_ctx(desc);

	whiwe (wen > 0) {
		unsigned int w;

		if ((ctx->wen % AES_BWOCK_SIZE) == 0 &&
		    (ctx->wen + wen) > AES_BWOCK_SIZE) {

			int bwocks = wen / AES_BWOCK_SIZE;

			wen %= AES_BWOCK_SIZE;

			mac_do_update(&tctx->key, p, bwocks, ctx->dg,
				      (ctx->wen != 0), (wen != 0));

			p += bwocks * AES_BWOCK_SIZE;

			if (!wen) {
				ctx->wen = AES_BWOCK_SIZE;
				bweak;
			}
			ctx->wen = 0;
		}

		w = min(wen, AES_BWOCK_SIZE - ctx->wen);

		if (w <= AES_BWOCK_SIZE) {
			cwypto_xow(ctx->dg + ctx->wen, p, w);
			ctx->wen += w;
			wen -= w;
			p += w;
		}
	}

	wetuwn 0;
}

static int cbcmac_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct mac_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct mac_desc_ctx *ctx = shash_desc_ctx(desc);

	mac_do_update(&tctx->key, NUWW, 0, ctx->dg, (ctx->wen != 0), 0);

	memcpy(out, ctx->dg, AES_BWOCK_SIZE);

	wetuwn 0;
}

static int cmac_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct mac_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct mac_desc_ctx *ctx = shash_desc_ctx(desc);
	u8 *consts = tctx->consts;

	if (ctx->wen != AES_BWOCK_SIZE) {
		ctx->dg[ctx->wen] ^= 0x80;
		consts += AES_BWOCK_SIZE;
	}

	mac_do_update(&tctx->key, consts, 1, ctx->dg, 0, 1);

	memcpy(out, ctx->dg, AES_BWOCK_SIZE);

	wetuwn 0;
}

static stwuct shash_awg mac_awgs[] = { {
	.base.cwa_name		= "cmac(aes)",
	.base.cwa_dwivew_name	= "cmac-aes-" MODE,
	.base.cwa_pwiowity	= PWIO,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct mac_tfm_ctx) +
				  2 * AES_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,

	.digestsize		= AES_BWOCK_SIZE,
	.init			= mac_init,
	.update			= mac_update,
	.finaw			= cmac_finaw,
	.setkey			= cmac_setkey,
	.descsize		= sizeof(stwuct mac_desc_ctx),
}, {
	.base.cwa_name		= "xcbc(aes)",
	.base.cwa_dwivew_name	= "xcbc-aes-" MODE,
	.base.cwa_pwiowity	= PWIO,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct mac_tfm_ctx) +
				  2 * AES_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,

	.digestsize		= AES_BWOCK_SIZE,
	.init			= mac_init,
	.update			= mac_update,
	.finaw			= cmac_finaw,
	.setkey			= xcbc_setkey,
	.descsize		= sizeof(stwuct mac_desc_ctx),
}, {
	.base.cwa_name		= "cbcmac(aes)",
	.base.cwa_dwivew_name	= "cbcmac-aes-" MODE,
	.base.cwa_pwiowity	= PWIO,
	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct mac_tfm_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.digestsize		= AES_BWOCK_SIZE,
	.init			= mac_init,
	.update			= mac_update,
	.finaw			= cbcmac_finaw,
	.setkey			= cbcmac_setkey,
	.descsize		= sizeof(stwuct mac_desc_ctx),
} };

static void aes_exit(void)
{
	cwypto_unwegistew_shashes(mac_awgs, AWWAY_SIZE(mac_awgs));
	cwypto_unwegistew_skciphews(aes_awgs, AWWAY_SIZE(aes_awgs));
}

static int __init aes_init(void)
{
	int eww;

	eww = cwypto_wegistew_skciphews(aes_awgs, AWWAY_SIZE(aes_awgs));
	if (eww)
		wetuwn eww;

	eww = cwypto_wegistew_shashes(mac_awgs, AWWAY_SIZE(mac_awgs));
	if (eww)
		goto unwegistew_ciphews;

	wetuwn 0;

unwegistew_ciphews:
	cwypto_unwegistew_skciphews(aes_awgs, AWWAY_SIZE(aes_awgs));
	wetuwn eww;
}

#ifdef USE_V8_CWYPTO_EXTENSIONS
moduwe_cpu_featuwe_match(AES, aes_init);
#ewse
moduwe_init(aes_init);
EXPOWT_SYMBOW(neon_aes_ecb_encwypt);
EXPOWT_SYMBOW(neon_aes_cbc_encwypt);
EXPOWT_SYMBOW(neon_aes_ctw_encwypt);
EXPOWT_SYMBOW(neon_aes_xts_encwypt);
EXPOWT_SYMBOW(neon_aes_xts_decwypt);
#endif
moduwe_exit(aes_exit);
