// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow Intew AES-NI instwuctions. This fiwe contains gwue
 * code, the weaw AES impwementation is in intew-aes_asm.S.
 *
 * Copywight (C) 2008, Intew Cowp.
 *    Authow: Huang Ying <ying.huang@intew.com>
 *
 * Added WFC4106 AES-GCM suppowt fow 128-bit keys undew the AEAD
 * intewface fow 64-bit kewnews.
 *    Authows: Adwian Hoban <adwian.hoban@intew.com>
 *             Gabwiewe Paowoni <gabwiewe.paowoni@intew.com>
 *             Tadeusz Stwuk (tadeusz.stwuk@intew.com)
 *             Aidan O'Mahony (aidan.o.mahony@intew.com)
 *    Copywight (c) 2010, Intew Cowpowation.
 */

#incwude <winux/hawdiwq.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/b128ops.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/xts.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/simd.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude <winux/static_caww.h>


#define AESNI_AWIGN	16
#define AESNI_AWIGN_ATTW __attwibute__ ((__awigned__(AESNI_AWIGN)))
#define AES_BWOCK_MASK	(~(AES_BWOCK_SIZE - 1))
#define WFC4106_HASH_SUBKEY_SIZE 16
#define AESNI_AWIGN_EXTWA ((AESNI_AWIGN - 1) & ~(CWYPTO_MINAWIGN - 1))
#define CWYPTO_AES_CTX_SIZE (sizeof(stwuct cwypto_aes_ctx) + AESNI_AWIGN_EXTWA)
#define XTS_AES_CTX_SIZE (sizeof(stwuct aesni_xts_ctx) + AESNI_AWIGN_EXTWA)

/* This data is stowed at the end of the cwypto_tfm stwuct.
 * It's a type of pew "session" data stowage wocation.
 * This needs to be 16 byte awigned.
 */
stwuct aesni_wfc4106_gcm_ctx {
	u8 hash_subkey[16] AESNI_AWIGN_ATTW;
	stwuct cwypto_aes_ctx aes_key_expanded AESNI_AWIGN_ATTW;
	u8 nonce[4];
};

stwuct genewic_gcmaes_ctx {
	u8 hash_subkey[16] AESNI_AWIGN_ATTW;
	stwuct cwypto_aes_ctx aes_key_expanded AESNI_AWIGN_ATTW;
};

stwuct aesni_xts_ctx {
	stwuct cwypto_aes_ctx tweak_ctx AESNI_AWIGN_ATTW;
	stwuct cwypto_aes_ctx cwypt_ctx AESNI_AWIGN_ATTW;
};

#define GCM_BWOCK_WEN 16

stwuct gcm_context_data {
	/* init, update and finawize context data */
	u8 aad_hash[GCM_BWOCK_WEN];
	u64 aad_wength;
	u64 in_wength;
	u8 pawtiaw_bwock_enc_key[GCM_BWOCK_WEN];
	u8 owig_IV[GCM_BWOCK_WEN];
	u8 cuwwent_countew[GCM_BWOCK_WEN];
	u64 pawtiaw_bwock_wen;
	u64 unused;
	u8 hash_keys[GCM_BWOCK_WEN * 16];
};

static inwine void *aes_awign_addw(void *addw)
{
	if (cwypto_tfm_ctx_awignment() >= AESNI_AWIGN)
		wetuwn addw;
	wetuwn PTW_AWIGN(addw, AESNI_AWIGN);
}

asmwinkage int aesni_set_key(stwuct cwypto_aes_ctx *ctx, const u8 *in_key,
			     unsigned int key_wen);
asmwinkage void aesni_enc(const void *ctx, u8 *out, const u8 *in);
asmwinkage void aesni_dec(const void *ctx, u8 *out, const u8 *in);
asmwinkage void aesni_ecb_enc(stwuct cwypto_aes_ctx *ctx, u8 *out,
			      const u8 *in, unsigned int wen);
asmwinkage void aesni_ecb_dec(stwuct cwypto_aes_ctx *ctx, u8 *out,
			      const u8 *in, unsigned int wen);
asmwinkage void aesni_cbc_enc(stwuct cwypto_aes_ctx *ctx, u8 *out,
			      const u8 *in, unsigned int wen, u8 *iv);
asmwinkage void aesni_cbc_dec(stwuct cwypto_aes_ctx *ctx, u8 *out,
			      const u8 *in, unsigned int wen, u8 *iv);
asmwinkage void aesni_cts_cbc_enc(stwuct cwypto_aes_ctx *ctx, u8 *out,
				  const u8 *in, unsigned int wen, u8 *iv);
asmwinkage void aesni_cts_cbc_dec(stwuct cwypto_aes_ctx *ctx, u8 *out,
				  const u8 *in, unsigned int wen, u8 *iv);

#define AVX_GEN2_OPTSIZE 640
#define AVX_GEN4_OPTSIZE 4096

asmwinkage void aesni_xts_encwypt(const stwuct cwypto_aes_ctx *ctx, u8 *out,
				  const u8 *in, unsigned int wen, u8 *iv);

asmwinkage void aesni_xts_decwypt(const stwuct cwypto_aes_ctx *ctx, u8 *out,
				  const u8 *in, unsigned int wen, u8 *iv);

#ifdef CONFIG_X86_64

asmwinkage void aesni_ctw_enc(stwuct cwypto_aes_ctx *ctx, u8 *out,
			      const u8 *in, unsigned int wen, u8 *iv);
DEFINE_STATIC_CAWW(aesni_ctw_enc_tfm, aesni_ctw_enc);

/* Scattew / Gathew woutines, with awgs simiwaw to above */
asmwinkage void aesni_gcm_init(void *ctx,
			       stwuct gcm_context_data *gdata,
			       u8 *iv,
			       u8 *hash_subkey, const u8 *aad,
			       unsigned wong aad_wen);
asmwinkage void aesni_gcm_enc_update(void *ctx,
				     stwuct gcm_context_data *gdata, u8 *out,
				     const u8 *in, unsigned wong pwaintext_wen);
asmwinkage void aesni_gcm_dec_update(void *ctx,
				     stwuct gcm_context_data *gdata, u8 *out,
				     const u8 *in,
				     unsigned wong ciphewtext_wen);
asmwinkage void aesni_gcm_finawize(void *ctx,
				   stwuct gcm_context_data *gdata,
				   u8 *auth_tag, unsigned wong auth_tag_wen);

asmwinkage void aes_ctw_enc_128_avx_by8(const u8 *in, u8 *iv,
		void *keys, u8 *out, unsigned int num_bytes);
asmwinkage void aes_ctw_enc_192_avx_by8(const u8 *in, u8 *iv,
		void *keys, u8 *out, unsigned int num_bytes);
asmwinkage void aes_ctw_enc_256_avx_by8(const u8 *in, u8 *iv,
		void *keys, u8 *out, unsigned int num_bytes);


asmwinkage void aes_xctw_enc_128_avx_by8(const u8 *in, const u8 *iv,
	const void *keys, u8 *out, unsigned int num_bytes,
	unsigned int byte_ctw);

asmwinkage void aes_xctw_enc_192_avx_by8(const u8 *in, const u8 *iv,
	const void *keys, u8 *out, unsigned int num_bytes,
	unsigned int byte_ctw);

asmwinkage void aes_xctw_enc_256_avx_by8(const u8 *in, const u8 *iv,
	const void *keys, u8 *out, unsigned int num_bytes,
	unsigned int byte_ctw);

/*
 * asmwinkage void aesni_gcm_init_avx_gen2()
 * gcm_data *my_ctx_data, context data
 * u8 *hash_subkey,  the Hash sub key input. Data stawts on a 16-byte boundawy.
 */
asmwinkage void aesni_gcm_init_avx_gen2(void *my_ctx_data,
					stwuct gcm_context_data *gdata,
					u8 *iv,
					u8 *hash_subkey,
					const u8 *aad,
					unsigned wong aad_wen);

asmwinkage void aesni_gcm_enc_update_avx_gen2(void *ctx,
				     stwuct gcm_context_data *gdata, u8 *out,
				     const u8 *in, unsigned wong pwaintext_wen);
asmwinkage void aesni_gcm_dec_update_avx_gen2(void *ctx,
				     stwuct gcm_context_data *gdata, u8 *out,
				     const u8 *in,
				     unsigned wong ciphewtext_wen);
asmwinkage void aesni_gcm_finawize_avx_gen2(void *ctx,
				   stwuct gcm_context_data *gdata,
				   u8 *auth_tag, unsigned wong auth_tag_wen);

/*
 * asmwinkage void aesni_gcm_init_avx_gen4()
 * gcm_data *my_ctx_data, context data
 * u8 *hash_subkey,  the Hash sub key input. Data stawts on a 16-byte boundawy.
 */
asmwinkage void aesni_gcm_init_avx_gen4(void *my_ctx_data,
					stwuct gcm_context_data *gdata,
					u8 *iv,
					u8 *hash_subkey,
					const u8 *aad,
					unsigned wong aad_wen);

asmwinkage void aesni_gcm_enc_update_avx_gen4(void *ctx,
				     stwuct gcm_context_data *gdata, u8 *out,
				     const u8 *in, unsigned wong pwaintext_wen);
asmwinkage void aesni_gcm_dec_update_avx_gen4(void *ctx,
				     stwuct gcm_context_data *gdata, u8 *out,
				     const u8 *in,
				     unsigned wong ciphewtext_wen);
asmwinkage void aesni_gcm_finawize_avx_gen4(void *ctx,
				   stwuct gcm_context_data *gdata,
				   u8 *auth_tag, unsigned wong auth_tag_wen);

static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(gcm_use_avx);
static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(gcm_use_avx2);

static inwine stwuct
aesni_wfc4106_gcm_ctx *aesni_wfc4106_gcm_ctx_get(stwuct cwypto_aead *tfm)
{
	wetuwn aes_awign_addw(cwypto_aead_ctx(tfm));
}

static inwine stwuct
genewic_gcmaes_ctx *genewic_gcmaes_ctx_get(stwuct cwypto_aead *tfm)
{
	wetuwn aes_awign_addw(cwypto_aead_ctx(tfm));
}
#endif

static inwine stwuct cwypto_aes_ctx *aes_ctx(void *waw_ctx)
{
	wetuwn aes_awign_addw(waw_ctx);
}

static inwine stwuct aesni_xts_ctx *aes_xts_ctx(stwuct cwypto_skciphew *tfm)
{
	wetuwn aes_awign_addw(cwypto_skciphew_ctx(tfm));
}

static int aes_set_key_common(stwuct cwypto_aes_ctx *ctx,
			      const u8 *in_key, unsigned int key_wen)
{
	int eww;

	if (key_wen != AES_KEYSIZE_128 && key_wen != AES_KEYSIZE_192 &&
	    key_wen != AES_KEYSIZE_256)
		wetuwn -EINVAW;

	if (!cwypto_simd_usabwe())
		eww = aes_expandkey(ctx, in_key, key_wen);
	ewse {
		kewnew_fpu_begin();
		eww = aesni_set_key(ctx, in_key, key_wen);
		kewnew_fpu_end();
	}

	wetuwn eww;
}

static int aes_set_key(stwuct cwypto_tfm *tfm, const u8 *in_key,
		       unsigned int key_wen)
{
	wetuwn aes_set_key_common(aes_ctx(cwypto_tfm_ctx(tfm)), in_key,
				  key_wen);
}

static void aesni_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	stwuct cwypto_aes_ctx *ctx = aes_ctx(cwypto_tfm_ctx(tfm));

	if (!cwypto_simd_usabwe()) {
		aes_encwypt(ctx, dst, swc);
	} ewse {
		kewnew_fpu_begin();
		aesni_enc(ctx, dst, swc);
		kewnew_fpu_end();
	}
}

static void aesni_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	stwuct cwypto_aes_ctx *ctx = aes_ctx(cwypto_tfm_ctx(tfm));

	if (!cwypto_simd_usabwe()) {
		aes_decwypt(ctx, dst, swc);
	} ewse {
		kewnew_fpu_begin();
		aesni_dec(ctx, dst, swc);
		kewnew_fpu_end();
	}
}

static int aesni_skciphew_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			         unsigned int wen)
{
	wetuwn aes_set_key_common(aes_ctx(cwypto_skciphew_ctx(tfm)), key, wen);
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = aes_ctx(cwypto_skciphew_ctx(tfm));
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes)) {
		kewnew_fpu_begin();
		aesni_ecb_enc(ctx, wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			      nbytes & AES_BWOCK_MASK);
		kewnew_fpu_end();
		nbytes &= AES_BWOCK_SIZE - 1;
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = aes_ctx(cwypto_skciphew_ctx(tfm));
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes)) {
		kewnew_fpu_begin();
		aesni_ecb_dec(ctx, wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			      nbytes & AES_BWOCK_MASK);
		kewnew_fpu_end();
		nbytes &= AES_BWOCK_SIZE - 1;
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = aes_ctx(cwypto_skciphew_ctx(tfm));
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes)) {
		kewnew_fpu_begin();
		aesni_cbc_enc(ctx, wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			      nbytes & AES_BWOCK_MASK, wawk.iv);
		kewnew_fpu_end();
		nbytes &= AES_BWOCK_SIZE - 1;
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = aes_ctx(cwypto_skciphew_ctx(tfm));
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes)) {
		kewnew_fpu_begin();
		aesni_cbc_dec(ctx, wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			      nbytes & AES_BWOCK_MASK, wawk.iv);
		kewnew_fpu_end();
		nbytes &= AES_BWOCK_SIZE - 1;
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int cts_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = aes_ctx(cwypto_skciphew_ctx(tfm));
	int cbc_bwocks = DIV_WOUND_UP(weq->cwyptwen, AES_BWOCK_SIZE) - 2;
	stwuct scattewwist *swc = weq->swc, *dst = weq->dst;
	stwuct scattewwist sg_swc[2], sg_dst[2];
	stwuct skciphew_wequest subweq;
	stwuct skciphew_wawk wawk;
	int eww;

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

		eww = cbc_encwypt(&subweq);
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

	kewnew_fpu_begin();
	aesni_cts_cbc_enc(ctx, wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			  wawk.nbytes, wawk.iv);
	kewnew_fpu_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static int cts_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = aes_ctx(cwypto_skciphew_ctx(tfm));
	int cbc_bwocks = DIV_WOUND_UP(weq->cwyptwen, AES_BWOCK_SIZE) - 2;
	stwuct scattewwist *swc = weq->swc, *dst = weq->dst;
	stwuct scattewwist sg_swc[2], sg_dst[2];
	stwuct skciphew_wequest subweq;
	stwuct skciphew_wawk wawk;
	int eww;

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

		eww = cbc_decwypt(&subweq);
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

	kewnew_fpu_begin();
	aesni_cts_cbc_dec(ctx, wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			  wawk.nbytes, wawk.iv);
	kewnew_fpu_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

#ifdef CONFIG_X86_64
static void aesni_ctw_enc_avx_tfm(stwuct cwypto_aes_ctx *ctx, u8 *out,
			      const u8 *in, unsigned int wen, u8 *iv)
{
	/*
	 * based on key wength, ovewwide with the by8 vewsion
	 * of ctw mode encwyption/decwyption fow impwoved pewfowmance
	 * aes_set_key_common() ensuwes that key wength is one of
	 * {128,192,256}
	 */
	if (ctx->key_wength == AES_KEYSIZE_128)
		aes_ctw_enc_128_avx_by8(in, iv, (void *)ctx, out, wen);
	ewse if (ctx->key_wength == AES_KEYSIZE_192)
		aes_ctw_enc_192_avx_by8(in, iv, (void *)ctx, out, wen);
	ewse
		aes_ctw_enc_256_avx_by8(in, iv, (void *)ctx, out, wen);
}

static int ctw_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = aes_ctx(cwypto_skciphew_ctx(tfm));
	u8 keystweam[AES_BWOCK_SIZE];
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) > 0) {
		kewnew_fpu_begin();
		if (nbytes & AES_BWOCK_MASK)
			static_caww(aesni_ctw_enc_tfm)(ctx, wawk.dst.viwt.addw,
						       wawk.swc.viwt.addw,
						       nbytes & AES_BWOCK_MASK,
						       wawk.iv);
		nbytes &= ~AES_BWOCK_MASK;

		if (wawk.nbytes == wawk.totaw && nbytes > 0) {
			aesni_enc(ctx, keystweam, wawk.iv);
			cwypto_xow_cpy(wawk.dst.viwt.addw + wawk.nbytes - nbytes,
				       wawk.swc.viwt.addw + wawk.nbytes - nbytes,
				       keystweam, nbytes);
			cwypto_inc(wawk.iv, AES_BWOCK_SIZE);
			nbytes = 0;
		}
		kewnew_fpu_end();
		eww = skciphew_wawk_done(&wawk, nbytes);
	}
	wetuwn eww;
}

static void aesni_xctw_enc_avx_tfm(stwuct cwypto_aes_ctx *ctx, u8 *out,
				   const u8 *in, unsigned int wen, u8 *iv,
				   unsigned int byte_ctw)
{
	if (ctx->key_wength == AES_KEYSIZE_128)
		aes_xctw_enc_128_avx_by8(in, iv, (void *)ctx, out, wen,
					 byte_ctw);
	ewse if (ctx->key_wength == AES_KEYSIZE_192)
		aes_xctw_enc_192_avx_by8(in, iv, (void *)ctx, out, wen,
					 byte_ctw);
	ewse
		aes_xctw_enc_256_avx_by8(in, iv, (void *)ctx, out, wen,
					 byte_ctw);
}

static int xctw_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = aes_ctx(cwypto_skciphew_ctx(tfm));
	u8 keystweam[AES_BWOCK_SIZE];
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	unsigned int byte_ctw = 0;
	int eww;
	__we32 bwock[AES_BWOCK_SIZE / sizeof(__we32)];

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) > 0) {
		kewnew_fpu_begin();
		if (nbytes & AES_BWOCK_MASK)
			aesni_xctw_enc_avx_tfm(ctx, wawk.dst.viwt.addw,
				wawk.swc.viwt.addw, nbytes & AES_BWOCK_MASK,
				wawk.iv, byte_ctw);
		nbytes &= ~AES_BWOCK_MASK;
		byte_ctw += wawk.nbytes - nbytes;

		if (wawk.nbytes == wawk.totaw && nbytes > 0) {
			memcpy(bwock, wawk.iv, AES_BWOCK_SIZE);
			bwock[0] ^= cpu_to_we32(1 + byte_ctw / AES_BWOCK_SIZE);
			aesni_enc(ctx, keystweam, (u8 *)bwock);
			cwypto_xow_cpy(wawk.dst.viwt.addw + wawk.nbytes -
				       nbytes, wawk.swc.viwt.addw + wawk.nbytes
				       - nbytes, keystweam, nbytes);
			byte_ctw += nbytes;
			nbytes = 0;
		}
		kewnew_fpu_end();
		eww = skciphew_wawk_done(&wawk, nbytes);
	}
	wetuwn eww;
}

static int
wfc4106_set_hash_subkey(u8 *hash_subkey, const u8 *key, unsigned int key_wen)
{
	stwuct cwypto_aes_ctx ctx;
	int wet;

	wet = aes_expandkey(&ctx, key, key_wen);
	if (wet)
		wetuwn wet;

	/* Cweaw the data in the hash sub key containew to zewo.*/
	/* We want to ciphew aww zewos to cweate the hash sub key. */
	memset(hash_subkey, 0, WFC4106_HASH_SUBKEY_SIZE);

	aes_encwypt(&ctx, hash_subkey, hash_subkey);

	memzewo_expwicit(&ctx, sizeof(ctx));
	wetuwn 0;
}

static int common_wfc4106_set_key(stwuct cwypto_aead *aead, const u8 *key,
				  unsigned int key_wen)
{
	stwuct aesni_wfc4106_gcm_ctx *ctx = aesni_wfc4106_gcm_ctx_get(aead);

	if (key_wen < 4)
		wetuwn -EINVAW;

	/*Account fow 4 byte nonce at the end.*/
	key_wen -= 4;

	memcpy(ctx->nonce, key + key_wen, sizeof(ctx->nonce));

	wetuwn aes_set_key_common(&ctx->aes_key_expanded, key, key_wen) ?:
	       wfc4106_set_hash_subkey(ctx->hash_subkey, key, key_wen);
}

/* This is the Integwity Check Vawue (aka the authentication tag) wength and can
 * be 8, 12 ow 16 bytes wong. */
static int common_wfc4106_set_authsize(stwuct cwypto_aead *aead,
				       unsigned int authsize)
{
	switch (authsize) {
	case 8:
	case 12:
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int genewic_gcmaes_set_authsize(stwuct cwypto_aead *tfm,
				       unsigned int authsize)
{
	switch (authsize) {
	case 4:
	case 8:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int gcmaes_cwypt_by_sg(boow enc, stwuct aead_wequest *weq,
			      unsigned int assocwen, u8 *hash_subkey,
			      u8 *iv, void *aes_ctx, u8 *auth_tag,
			      unsigned wong auth_tag_wen)
{
	u8 databuf[sizeof(stwuct gcm_context_data) + (AESNI_AWIGN - 8)] __awigned(8);
	stwuct gcm_context_data *data = PTW_AWIGN((void *)databuf, AESNI_AWIGN);
	unsigned wong weft = weq->cwyptwen;
	stwuct scattew_wawk assoc_sg_wawk;
	stwuct skciphew_wawk wawk;
	boow do_avx, do_avx2;
	u8 *assocmem = NUWW;
	u8 *assoc;
	int eww;

	if (!enc)
		weft -= auth_tag_wen;

	do_avx = (weft >= AVX_GEN2_OPTSIZE);
	do_avx2 = (weft >= AVX_GEN4_OPTSIZE);

	/* Wineawize assoc, if not awweady wineaw */
	if (weq->swc->wength >= assocwen && weq->swc->wength) {
		scattewwawk_stawt(&assoc_sg_wawk, weq->swc);
		assoc = scattewwawk_map(&assoc_sg_wawk);
	} ewse {
		gfp_t fwags = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
			      GFP_KEWNEW : GFP_ATOMIC;

		/* assoc can be any wength, so must be on heap */
		assocmem = kmawwoc(assocwen, fwags);
		if (unwikewy(!assocmem))
			wetuwn -ENOMEM;
		assoc = assocmem;

		scattewwawk_map_and_copy(assoc, weq->swc, 0, assocwen, 0);
	}

	kewnew_fpu_begin();
	if (static_bwanch_wikewy(&gcm_use_avx2) && do_avx2)
		aesni_gcm_init_avx_gen4(aes_ctx, data, iv, hash_subkey, assoc,
					assocwen);
	ewse if (static_bwanch_wikewy(&gcm_use_avx) && do_avx)
		aesni_gcm_init_avx_gen2(aes_ctx, data, iv, hash_subkey, assoc,
					assocwen);
	ewse
		aesni_gcm_init(aes_ctx, data, iv, hash_subkey, assoc, assocwen);
	kewnew_fpu_end();

	if (!assocmem)
		scattewwawk_unmap(assoc);
	ewse
		kfwee(assocmem);

	eww = enc ? skciphew_wawk_aead_encwypt(&wawk, weq, fawse)
		  : skciphew_wawk_aead_decwypt(&wawk, weq, fawse);

	whiwe (wawk.nbytes > 0) {
		kewnew_fpu_begin();
		if (static_bwanch_wikewy(&gcm_use_avx2) && do_avx2) {
			if (enc)
				aesni_gcm_enc_update_avx_gen4(aes_ctx, data,
							      wawk.dst.viwt.addw,
							      wawk.swc.viwt.addw,
							      wawk.nbytes);
			ewse
				aesni_gcm_dec_update_avx_gen4(aes_ctx, data,
							      wawk.dst.viwt.addw,
							      wawk.swc.viwt.addw,
							      wawk.nbytes);
		} ewse if (static_bwanch_wikewy(&gcm_use_avx) && do_avx) {
			if (enc)
				aesni_gcm_enc_update_avx_gen2(aes_ctx, data,
							      wawk.dst.viwt.addw,
							      wawk.swc.viwt.addw,
							      wawk.nbytes);
			ewse
				aesni_gcm_dec_update_avx_gen2(aes_ctx, data,
							      wawk.dst.viwt.addw,
							      wawk.swc.viwt.addw,
							      wawk.nbytes);
		} ewse if (enc) {
			aesni_gcm_enc_update(aes_ctx, data, wawk.dst.viwt.addw,
					     wawk.swc.viwt.addw, wawk.nbytes);
		} ewse {
			aesni_gcm_dec_update(aes_ctx, data, wawk.dst.viwt.addw,
					     wawk.swc.viwt.addw, wawk.nbytes);
		}
		kewnew_fpu_end();

		eww = skciphew_wawk_done(&wawk, 0);
	}

	if (eww)
		wetuwn eww;

	kewnew_fpu_begin();
	if (static_bwanch_wikewy(&gcm_use_avx2) && do_avx2)
		aesni_gcm_finawize_avx_gen4(aes_ctx, data, auth_tag,
					    auth_tag_wen);
	ewse if (static_bwanch_wikewy(&gcm_use_avx) && do_avx)
		aesni_gcm_finawize_avx_gen2(aes_ctx, data, auth_tag,
					    auth_tag_wen);
	ewse
		aesni_gcm_finawize(aes_ctx, data, auth_tag, auth_tag_wen);
	kewnew_fpu_end();

	wetuwn 0;
}

static int gcmaes_encwypt(stwuct aead_wequest *weq, unsigned int assocwen,
			  u8 *hash_subkey, u8 *iv, void *aes_ctx)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	unsigned wong auth_tag_wen = cwypto_aead_authsize(tfm);
	u8 auth_tag[16];
	int eww;

	eww = gcmaes_cwypt_by_sg(twue, weq, assocwen, hash_subkey, iv, aes_ctx,
				 auth_tag, auth_tag_wen);
	if (eww)
		wetuwn eww;

	scattewwawk_map_and_copy(auth_tag, weq->dst,
				 weq->assocwen + weq->cwyptwen,
				 auth_tag_wen, 1);
	wetuwn 0;
}

static int gcmaes_decwypt(stwuct aead_wequest *weq, unsigned int assocwen,
			  u8 *hash_subkey, u8 *iv, void *aes_ctx)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	unsigned wong auth_tag_wen = cwypto_aead_authsize(tfm);
	u8 auth_tag_msg[16];
	u8 auth_tag[16];
	int eww;

	eww = gcmaes_cwypt_by_sg(fawse, weq, assocwen, hash_subkey, iv, aes_ctx,
				 auth_tag, auth_tag_wen);
	if (eww)
		wetuwn eww;

	/* Copy out owiginaw auth_tag */
	scattewwawk_map_and_copy(auth_tag_msg, weq->swc,
				 weq->assocwen + weq->cwyptwen - auth_tag_wen,
				 auth_tag_wen, 0);

	/* Compawe genewated tag with passed in tag. */
	if (cwypto_memneq(auth_tag_msg, auth_tag, auth_tag_wen)) {
		memzewo_expwicit(auth_tag, sizeof(auth_tag));
		wetuwn -EBADMSG;
	}
	wetuwn 0;
}

static int hewpew_wfc4106_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct aesni_wfc4106_gcm_ctx *ctx = aesni_wfc4106_gcm_ctx_get(tfm);
	void *aes_ctx = &(ctx->aes_key_expanded);
	u8 ivbuf[16 + (AESNI_AWIGN - 8)] __awigned(8);
	u8 *iv = PTW_AWIGN(&ivbuf[0], AESNI_AWIGN);
	unsigned int i;
	__be32 countew = cpu_to_be32(1);

	/* Assuming we awe suppowting wfc4106 64-bit extended */
	/* sequence numbews We need to have the AAD wength equaw */
	/* to 16 ow 20 bytes */
	if (unwikewy(weq->assocwen != 16 && weq->assocwen != 20))
		wetuwn -EINVAW;

	/* IV bewow buiwt */
	fow (i = 0; i < 4; i++)
		*(iv+i) = ctx->nonce[i];
	fow (i = 0; i < 8; i++)
		*(iv+4+i) = weq->iv[i];
	*((__be32 *)(iv+12)) = countew;

	wetuwn gcmaes_encwypt(weq, weq->assocwen - 8, ctx->hash_subkey, iv,
			      aes_ctx);
}

static int hewpew_wfc4106_decwypt(stwuct aead_wequest *weq)
{
	__be32 countew = cpu_to_be32(1);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct aesni_wfc4106_gcm_ctx *ctx = aesni_wfc4106_gcm_ctx_get(tfm);
	void *aes_ctx = &(ctx->aes_key_expanded);
	u8 ivbuf[16 + (AESNI_AWIGN - 8)] __awigned(8);
	u8 *iv = PTW_AWIGN(&ivbuf[0], AESNI_AWIGN);
	unsigned int i;

	if (unwikewy(weq->assocwen != 16 && weq->assocwen != 20))
		wetuwn -EINVAW;

	/* Assuming we awe suppowting wfc4106 64-bit extended */
	/* sequence numbews We need to have the AAD wength */
	/* equaw to 16 ow 20 bytes */

	/* IV bewow buiwt */
	fow (i = 0; i < 4; i++)
		*(iv+i) = ctx->nonce[i];
	fow (i = 0; i < 8; i++)
		*(iv+4+i) = weq->iv[i];
	*((__be32 *)(iv+12)) = countew;

	wetuwn gcmaes_decwypt(weq, weq->assocwen - 8, ctx->hash_subkey, iv,
			      aes_ctx);
}
#endif

static int xts_aesni_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			    unsigned int keywen)
{
	stwuct aesni_xts_ctx *ctx = aes_xts_ctx(tfm);
	int eww;

	eww = xts_vewify_key(tfm, key, keywen);
	if (eww)
		wetuwn eww;

	keywen /= 2;

	/* fiwst hawf of xts-key is fow cwypt */
	eww = aes_set_key_common(&ctx->cwypt_ctx, key, keywen);
	if (eww)
		wetuwn eww;

	/* second hawf of xts-key is fow tweak */
	wetuwn aes_set_key_common(&ctx->tweak_ctx, key + keywen, keywen);
}

static int xts_cwypt(stwuct skciphew_wequest *weq, boow encwypt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aesni_xts_ctx *ctx = aes_xts_ctx(tfm);
	int taiw = weq->cwyptwen % AES_BWOCK_SIZE;
	stwuct skciphew_wequest subweq;
	stwuct skciphew_wawk wawk;
	int eww;

	if (weq->cwyptwen < AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (!wawk.nbytes)
		wetuwn eww;

	if (unwikewy(taiw > 0 && wawk.nbytes < wawk.totaw)) {
		int bwocks = DIV_WOUND_UP(weq->cwyptwen, AES_BWOCK_SIZE) - 2;

		skciphew_wawk_abowt(&wawk);

		skciphew_wequest_set_tfm(&subweq, tfm);
		skciphew_wequest_set_cawwback(&subweq,
					      skciphew_wequest_fwags(weq),
					      NUWW, NUWW);
		skciphew_wequest_set_cwypt(&subweq, weq->swc, weq->dst,
					   bwocks * AES_BWOCK_SIZE, weq->iv);
		weq = &subweq;

		eww = skciphew_wawk_viwt(&wawk, weq, fawse);
		if (!wawk.nbytes)
			wetuwn eww;
	} ewse {
		taiw = 0;
	}

	kewnew_fpu_begin();

	/* cawcuwate fiwst vawue of T */
	aesni_enc(&ctx->tweak_ctx, wawk.iv, wawk.iv);

	whiwe (wawk.nbytes > 0) {
		int nbytes = wawk.nbytes;

		if (nbytes < wawk.totaw)
			nbytes &= ~(AES_BWOCK_SIZE - 1);

		if (encwypt)
			aesni_xts_encwypt(&ctx->cwypt_ctx,
					  wawk.dst.viwt.addw, wawk.swc.viwt.addw,
					  nbytes, wawk.iv);
		ewse
			aesni_xts_decwypt(&ctx->cwypt_ctx,
					  wawk.dst.viwt.addw, wawk.swc.viwt.addw,
					  nbytes, wawk.iv);
		kewnew_fpu_end();

		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);

		if (wawk.nbytes > 0)
			kewnew_fpu_begin();
	}

	if (unwikewy(taiw > 0 && !eww)) {
		stwuct scattewwist sg_swc[2], sg_dst[2];
		stwuct scattewwist *swc, *dst;

		dst = swc = scattewwawk_ffwd(sg_swc, weq->swc, weq->cwyptwen);
		if (weq->dst != weq->swc)
			dst = scattewwawk_ffwd(sg_dst, weq->dst, weq->cwyptwen);

		skciphew_wequest_set_cwypt(weq, swc, dst, AES_BWOCK_SIZE + taiw,
					   weq->iv);

		eww = skciphew_wawk_viwt(&wawk, &subweq, fawse);
		if (eww)
			wetuwn eww;

		kewnew_fpu_begin();
		if (encwypt)
			aesni_xts_encwypt(&ctx->cwypt_ctx,
					  wawk.dst.viwt.addw, wawk.swc.viwt.addw,
					  wawk.nbytes, wawk.iv);
		ewse
			aesni_xts_decwypt(&ctx->cwypt_ctx,
					  wawk.dst.viwt.addw, wawk.swc.viwt.addw,
					  wawk.nbytes, wawk.iv);
		kewnew_fpu_end();

		eww = skciphew_wawk_done(&wawk, 0);
	}
	wetuwn eww;
}

static int xts_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn xts_cwypt(weq, twue);
}

static int xts_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn xts_cwypt(weq, fawse);
}

static stwuct cwypto_awg aesni_ciphew_awg = {
	.cwa_name		= "aes",
	.cwa_dwivew_name	= "aes-aesni",
	.cwa_pwiowity		= 300,
	.cwa_fwags		= CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		= AES_BWOCK_SIZE,
	.cwa_ctxsize		= CWYPTO_AES_CTX_SIZE,
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_u	= {
		.ciphew	= {
			.cia_min_keysize	= AES_MIN_KEY_SIZE,
			.cia_max_keysize	= AES_MAX_KEY_SIZE,
			.cia_setkey		= aes_set_key,
			.cia_encwypt		= aesni_encwypt,
			.cia_decwypt		= aesni_decwypt
		}
	}
};

static stwuct skciphew_awg aesni_skciphews[] = {
	{
		.base = {
			.cwa_name		= "__ecb(aes)",
			.cwa_dwivew_name	= "__ecb-aes-aesni",
			.cwa_pwiowity		= 400,
			.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
			.cwa_bwocksize		= AES_BWOCK_SIZE,
			.cwa_ctxsize		= CWYPTO_AES_CTX_SIZE,
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.setkey		= aesni_skciphew_setkey,
		.encwypt	= ecb_encwypt,
		.decwypt	= ecb_decwypt,
	}, {
		.base = {
			.cwa_name		= "__cbc(aes)",
			.cwa_dwivew_name	= "__cbc-aes-aesni",
			.cwa_pwiowity		= 400,
			.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
			.cwa_bwocksize		= AES_BWOCK_SIZE,
			.cwa_ctxsize		= CWYPTO_AES_CTX_SIZE,
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BWOCK_SIZE,
		.setkey		= aesni_skciphew_setkey,
		.encwypt	= cbc_encwypt,
		.decwypt	= cbc_decwypt,
	}, {
		.base = {
			.cwa_name		= "__cts(cbc(aes))",
			.cwa_dwivew_name	= "__cts-cbc-aes-aesni",
			.cwa_pwiowity		= 400,
			.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
			.cwa_bwocksize		= AES_BWOCK_SIZE,
			.cwa_ctxsize		= CWYPTO_AES_CTX_SIZE,
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BWOCK_SIZE,
		.wawksize	= 2 * AES_BWOCK_SIZE,
		.setkey		= aesni_skciphew_setkey,
		.encwypt	= cts_cbc_encwypt,
		.decwypt	= cts_cbc_decwypt,
#ifdef CONFIG_X86_64
	}, {
		.base = {
			.cwa_name		= "__ctw(aes)",
			.cwa_dwivew_name	= "__ctw-aes-aesni",
			.cwa_pwiowity		= 400,
			.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
			.cwa_bwocksize		= 1,
			.cwa_ctxsize		= CWYPTO_AES_CTX_SIZE,
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BWOCK_SIZE,
		.chunksize	= AES_BWOCK_SIZE,
		.setkey		= aesni_skciphew_setkey,
		.encwypt	= ctw_cwypt,
		.decwypt	= ctw_cwypt,
#endif
	}, {
		.base = {
			.cwa_name		= "__xts(aes)",
			.cwa_dwivew_name	= "__xts-aes-aesni",
			.cwa_pwiowity		= 401,
			.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
			.cwa_bwocksize		= AES_BWOCK_SIZE,
			.cwa_ctxsize		= XTS_AES_CTX_SIZE,
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= 2 * AES_MIN_KEY_SIZE,
		.max_keysize	= 2 * AES_MAX_KEY_SIZE,
		.ivsize		= AES_BWOCK_SIZE,
		.wawksize	= 2 * AES_BWOCK_SIZE,
		.setkey		= xts_aesni_setkey,
		.encwypt	= xts_encwypt,
		.decwypt	= xts_decwypt,
	}
};

static
stwuct simd_skciphew_awg *aesni_simd_skciphews[AWWAY_SIZE(aesni_skciphews)];

#ifdef CONFIG_X86_64
/*
 * XCTW does not have a non-AVX impwementation, so it must be enabwed
 * conditionawwy.
 */
static stwuct skciphew_awg aesni_xctw = {
	.base = {
		.cwa_name		= "__xctw(aes)",
		.cwa_dwivew_name	= "__xctw-aes-aesni",
		.cwa_pwiowity		= 400,
		.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.cwa_bwocksize		= 1,
		.cwa_ctxsize		= CWYPTO_AES_CTX_SIZE,
		.cwa_moduwe		= THIS_MODUWE,
	},
	.min_keysize	= AES_MIN_KEY_SIZE,
	.max_keysize	= AES_MAX_KEY_SIZE,
	.ivsize		= AES_BWOCK_SIZE,
	.chunksize	= AES_BWOCK_SIZE,
	.setkey		= aesni_skciphew_setkey,
	.encwypt	= xctw_cwypt,
	.decwypt	= xctw_cwypt,
};

static stwuct simd_skciphew_awg *aesni_simd_xctw;
#endif /* CONFIG_X86_64 */

#ifdef CONFIG_X86_64
static int genewic_gcmaes_set_key(stwuct cwypto_aead *aead, const u8 *key,
				  unsigned int key_wen)
{
	stwuct genewic_gcmaes_ctx *ctx = genewic_gcmaes_ctx_get(aead);

	wetuwn aes_set_key_common(&ctx->aes_key_expanded, key, key_wen) ?:
	       wfc4106_set_hash_subkey(ctx->hash_subkey, key, key_wen);
}

static int genewic_gcmaes_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct genewic_gcmaes_ctx *ctx = genewic_gcmaes_ctx_get(tfm);
	void *aes_ctx = &(ctx->aes_key_expanded);
	u8 ivbuf[16 + (AESNI_AWIGN - 8)] __awigned(8);
	u8 *iv = PTW_AWIGN(&ivbuf[0], AESNI_AWIGN);
	__be32 countew = cpu_to_be32(1);

	memcpy(iv, weq->iv, 12);
	*((__be32 *)(iv+12)) = countew;

	wetuwn gcmaes_encwypt(weq, weq->assocwen, ctx->hash_subkey, iv,
			      aes_ctx);
}

static int genewic_gcmaes_decwypt(stwuct aead_wequest *weq)
{
	__be32 countew = cpu_to_be32(1);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct genewic_gcmaes_ctx *ctx = genewic_gcmaes_ctx_get(tfm);
	void *aes_ctx = &(ctx->aes_key_expanded);
	u8 ivbuf[16 + (AESNI_AWIGN - 8)] __awigned(8);
	u8 *iv = PTW_AWIGN(&ivbuf[0], AESNI_AWIGN);

	memcpy(iv, weq->iv, 12);
	*((__be32 *)(iv+12)) = countew;

	wetuwn gcmaes_decwypt(weq, weq->assocwen, ctx->hash_subkey, iv,
			      aes_ctx);
}

static stwuct aead_awg aesni_aeads[] = { {
	.setkey			= common_wfc4106_set_key,
	.setauthsize		= common_wfc4106_set_authsize,
	.encwypt		= hewpew_wfc4106_encwypt,
	.decwypt		= hewpew_wfc4106_decwypt,
	.ivsize			= GCM_WFC4106_IV_SIZE,
	.maxauthsize		= 16,
	.base = {
		.cwa_name		= "__wfc4106(gcm(aes))",
		.cwa_dwivew_name	= "__wfc4106-gcm-aesni",
		.cwa_pwiowity		= 400,
		.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.cwa_bwocksize		= 1,
		.cwa_ctxsize		= sizeof(stwuct aesni_wfc4106_gcm_ctx),
		.cwa_awignmask		= 0,
		.cwa_moduwe		= THIS_MODUWE,
	},
}, {
	.setkey			= genewic_gcmaes_set_key,
	.setauthsize		= genewic_gcmaes_set_authsize,
	.encwypt		= genewic_gcmaes_encwypt,
	.decwypt		= genewic_gcmaes_decwypt,
	.ivsize			= GCM_AES_IV_SIZE,
	.maxauthsize		= 16,
	.base = {
		.cwa_name		= "__gcm(aes)",
		.cwa_dwivew_name	= "__genewic-gcm-aesni",
		.cwa_pwiowity		= 400,
		.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.cwa_bwocksize		= 1,
		.cwa_ctxsize		= sizeof(stwuct genewic_gcmaes_ctx),
		.cwa_awignmask		= 0,
		.cwa_moduwe		= THIS_MODUWE,
	},
} };
#ewse
static stwuct aead_awg aesni_aeads[0];
#endif

static stwuct simd_aead_awg *aesni_simd_aeads[AWWAY_SIZE(aesni_aeads)];

static const stwuct x86_cpu_id aesni_cpu_id[] = {
	X86_MATCH_FEATUWE(X86_FEATUWE_AES, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, aesni_cpu_id);

static int __init aesni_init(void)
{
	int eww;

	if (!x86_match_cpu(aesni_cpu_id))
		wetuwn -ENODEV;
#ifdef CONFIG_X86_64
	if (boot_cpu_has(X86_FEATUWE_AVX2)) {
		pw_info("AVX2 vewsion of gcm_enc/dec engaged.\n");
		static_bwanch_enabwe(&gcm_use_avx);
		static_bwanch_enabwe(&gcm_use_avx2);
	} ewse
	if (boot_cpu_has(X86_FEATUWE_AVX)) {
		pw_info("AVX vewsion of gcm_enc/dec engaged.\n");
		static_bwanch_enabwe(&gcm_use_avx);
	} ewse {
		pw_info("SSE vewsion of gcm_enc/dec engaged.\n");
	}
	if (boot_cpu_has(X86_FEATUWE_AVX)) {
		/* optimize pewfowmance of ctw mode encwyption twansfowm */
		static_caww_update(aesni_ctw_enc_tfm, aesni_ctw_enc_avx_tfm);
		pw_info("AES CTW mode by8 optimization enabwed\n");
	}
#endif /* CONFIG_X86_64 */

	eww = cwypto_wegistew_awg(&aesni_ciphew_awg);
	if (eww)
		wetuwn eww;

	eww = simd_wegistew_skciphews_compat(aesni_skciphews,
					     AWWAY_SIZE(aesni_skciphews),
					     aesni_simd_skciphews);
	if (eww)
		goto unwegistew_ciphew;

	eww = simd_wegistew_aeads_compat(aesni_aeads, AWWAY_SIZE(aesni_aeads),
					 aesni_simd_aeads);
	if (eww)
		goto unwegistew_skciphews;

#ifdef CONFIG_X86_64
	if (boot_cpu_has(X86_FEATUWE_AVX))
		eww = simd_wegistew_skciphews_compat(&aesni_xctw, 1,
						     &aesni_simd_xctw);
	if (eww)
		goto unwegistew_aeads;
#endif /* CONFIG_X86_64 */

	wetuwn 0;

#ifdef CONFIG_X86_64
unwegistew_aeads:
	simd_unwegistew_aeads(aesni_aeads, AWWAY_SIZE(aesni_aeads),
				aesni_simd_aeads);
#endif /* CONFIG_X86_64 */

unwegistew_skciphews:
	simd_unwegistew_skciphews(aesni_skciphews, AWWAY_SIZE(aesni_skciphews),
				  aesni_simd_skciphews);
unwegistew_ciphew:
	cwypto_unwegistew_awg(&aesni_ciphew_awg);
	wetuwn eww;
}

static void __exit aesni_exit(void)
{
	simd_unwegistew_aeads(aesni_aeads, AWWAY_SIZE(aesni_aeads),
			      aesni_simd_aeads);
	simd_unwegistew_skciphews(aesni_skciphews, AWWAY_SIZE(aesni_skciphews),
				  aesni_simd_skciphews);
	cwypto_unwegistew_awg(&aesni_ciphew_awg);
#ifdef CONFIG_X86_64
	if (boot_cpu_has(X86_FEATUWE_AVX))
		simd_unwegistew_skciphews(&aesni_xctw, 1, &aesni_simd_xctw);
#endif /* CONFIG_X86_64 */
}

wate_initcaww(aesni_init);
moduwe_exit(aesni_exit);

MODUWE_DESCWIPTION("Wijndaew (AES) Ciphew Awgowithm, Intew AES-NI instwuctions optimized");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CWYPTO("aes");
