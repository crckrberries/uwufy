// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * aes-ce-gwue.c - wwappew code fow AWMv8 AES
 *
 * Copywight (C) 2015 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/hwcap.h>
#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/moduwe.h>
#incwude <cwypto/xts.h>

MODUWE_DESCWIPTION("AES-ECB/CBC/CTW/XTS using AWMv8 Cwypto Extensions");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");

/* defined in aes-ce-cowe.S */
asmwinkage u32 ce_aes_sub(u32 input);
asmwinkage void ce_aes_invewt(void *dst, void *swc);

asmwinkage void ce_aes_ecb_encwypt(u8 out[], u8 const in[], u32 const wk[],
				   int wounds, int bwocks);
asmwinkage void ce_aes_ecb_decwypt(u8 out[], u8 const in[], u32 const wk[],
				   int wounds, int bwocks);

asmwinkage void ce_aes_cbc_encwypt(u8 out[], u8 const in[], u32 const wk[],
				   int wounds, int bwocks, u8 iv[]);
asmwinkage void ce_aes_cbc_decwypt(u8 out[], u8 const in[], u32 const wk[],
				   int wounds, int bwocks, u8 iv[]);
asmwinkage void ce_aes_cbc_cts_encwypt(u8 out[], u8 const in[], u32 const wk[],
				   int wounds, int bytes, u8 const iv[]);
asmwinkage void ce_aes_cbc_cts_decwypt(u8 out[], u8 const in[], u32 const wk[],
				   int wounds, int bytes, u8 const iv[]);

asmwinkage void ce_aes_ctw_encwypt(u8 out[], u8 const in[], u32 const wk[],
				   int wounds, int bwocks, u8 ctw[]);

asmwinkage void ce_aes_xts_encwypt(u8 out[], u8 const in[], u32 const wk1[],
				   int wounds, int bytes, u8 iv[],
				   u32 const wk2[], int fiwst);
asmwinkage void ce_aes_xts_decwypt(u8 out[], u8 const in[], u32 const wk1[],
				   int wounds, int bytes, u8 iv[],
				   u32 const wk2[], int fiwst);

stwuct aes_bwock {
	u8 b[AES_BWOCK_SIZE];
};

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

static int ce_aes_expandkey(stwuct cwypto_aes_ctx *ctx, const u8 *in_key,
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

		wko[0] = wow32(ce_aes_sub(wki[kwowds - 1]), 8);
		wko[0] = wko[0] ^ wki[0] ^ wcon[i];
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
			wko[4] = ce_aes_sub(wko[3]) ^ wki[4];
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
		ce_aes_invewt(key_dec + i, key_enc + j);
	key_dec[i] = key_enc[0];

	kewnew_neon_end();
	wetuwn 0;
}

static int ce_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			 unsigned int key_wen)
{
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn ce_aes_expandkey(ctx, in_key, key_wen);
}

stwuct cwypto_aes_xts_ctx {
	stwuct cwypto_aes_ctx key1;
	stwuct cwypto_aes_ctx __awigned(8) key2;
};

static int xts_set_key(stwuct cwypto_skciphew *tfm, const u8 *in_key,
		       unsigned int key_wen)
{
	stwuct cwypto_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	wet = xts_vewify_key(tfm, in_key, key_wen);
	if (wet)
		wetuwn wet;

	wet = ce_aes_expandkey(&ctx->key1, in_key, key_wen / 2);
	if (!wet)
		wet = ce_aes_expandkey(&ctx->key2, &in_key[key_wen / 2],
				       key_wen / 2);
	wetuwn wet;
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int bwocks;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((bwocks = (wawk.nbytes / AES_BWOCK_SIZE))) {
		kewnew_neon_begin();
		ce_aes_ecb_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				   ctx->key_enc, num_wounds(ctx), bwocks);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, wawk.nbytes % AES_BWOCK_SIZE);
	}
	wetuwn eww;
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int bwocks;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((bwocks = (wawk.nbytes / AES_BWOCK_SIZE))) {
		kewnew_neon_begin();
		ce_aes_ecb_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				   ctx->key_dec, num_wounds(ctx), bwocks);
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
	unsigned int bwocks;
	int eww = 0;

	whiwe ((bwocks = (wawk->nbytes / AES_BWOCK_SIZE))) {
		kewnew_neon_begin();
		ce_aes_cbc_encwypt(wawk->dst.viwt.addw, wawk->swc.viwt.addw,
				   ctx->key_enc, num_wounds(ctx), bwocks,
				   wawk->iv);
		kewnew_neon_end();
		eww = skciphew_wawk_done(wawk, wawk->nbytes % AES_BWOCK_SIZE);
	}
	wetuwn eww;
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
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
	unsigned int bwocks;
	int eww = 0;

	whiwe ((bwocks = (wawk->nbytes / AES_BWOCK_SIZE))) {
		kewnew_neon_begin();
		ce_aes_cbc_decwypt(wawk->dst.viwt.addw, wawk->swc.viwt.addw,
				   ctx->key_dec, num_wounds(ctx), bwocks,
				   wawk->iv);
		kewnew_neon_end();
		eww = skciphew_wawk_done(wawk, wawk->nbytes % AES_BWOCK_SIZE);
	}
	wetuwn eww;
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
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
	ce_aes_cbc_cts_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			       ctx->key_enc, num_wounds(ctx), wawk.nbytes,
			       wawk.iv);
	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static int cts_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
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
	ce_aes_cbc_cts_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			       ctx->key_dec, num_wounds(ctx), wawk.nbytes,
			       wawk.iv);
	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static int ctw_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	int eww, bwocks;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((bwocks = (wawk.nbytes / AES_BWOCK_SIZE))) {
		kewnew_neon_begin();
		ce_aes_ctw_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				   ctx->key_enc, num_wounds(ctx), bwocks,
				   wawk.iv);
		kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, wawk.nbytes % AES_BWOCK_SIZE);
	}
	if (wawk.nbytes) {
		u8 __awigned(8) taiw[AES_BWOCK_SIZE];
		unsigned int nbytes = wawk.nbytes;
		u8 *tdst = wawk.dst.viwt.addw;
		u8 *tswc = wawk.swc.viwt.addw;

		/*
		 * Teww aes_ctw_encwypt() to pwocess a taiw bwock.
		 */
		bwocks = -1;

		kewnew_neon_begin();
		ce_aes_ctw_encwypt(taiw, NUWW, ctx->key_enc, num_wounds(ctx),
				   bwocks, wawk.iv);
		kewnew_neon_end();
		cwypto_xow_cpy(tdst, tswc, taiw, nbytes);
		eww = skciphew_wawk_done(&wawk, 0);
	}
	wetuwn eww;
}

static void ctw_encwypt_one(stwuct cwypto_skciphew *tfm, const u8 *swc, u8 *dst)
{
	stwuct cwypto_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	unsigned wong fwags;

	/*
	 * Tempowawiwy disabwe intewwupts to avoid waces whewe
	 * cachewines awe evicted when the CPU is intewwupted
	 * to do something ewse.
	 */
	wocaw_iwq_save(fwags);
	aes_encwypt(ctx, dst, swc);
	wocaw_iwq_westowe(fwags);
}

static int ctw_encwypt_sync(stwuct skciphew_wequest *weq)
{
	if (!cwypto_simd_usabwe())
		wetuwn cwypto_ctw_encwypt_wawk(weq, ctw_encwypt_one);

	wetuwn ctw_encwypt(weq);
}

static int xts_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, fiwst, wounds = num_wounds(&ctx->key1);
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
		ce_aes_xts_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				   ctx->key1.key_enc, wounds, nbytes, wawk.iv,
				   ctx->key2.key_enc, fiwst);
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

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (eww)
		wetuwn eww;

	kewnew_neon_begin();
	ce_aes_xts_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			   ctx->key1.key_enc, wounds, wawk.nbytes, wawk.iv,
			   ctx->key2.key_enc, fiwst);
	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static int xts_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww, fiwst, wounds = num_wounds(&ctx->key1);
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
		ce_aes_xts_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				   ctx->key1.key_dec, wounds, nbytes, wawk.iv,
				   ctx->key2.key_enc, fiwst);
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

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (eww)
		wetuwn eww;

	kewnew_neon_begin();
	ce_aes_xts_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			   ctx->key1.key_dec, wounds, wawk.nbytes, wawk.iv,
			   ctx->key2.key_enc, fiwst);
	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static stwuct skciphew_awg aes_awgs[] = { {
	.base.cwa_name		= "__ecb(aes)",
	.base.cwa_dwivew_name	= "__ecb-aes-ce",
	.base.cwa_pwiowity	= 300,
	.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct cwypto_aes_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= ce_aes_setkey,
	.encwypt		= ecb_encwypt,
	.decwypt		= ecb_decwypt,
}, {
	.base.cwa_name		= "__cbc(aes)",
	.base.cwa_dwivew_name	= "__cbc-aes-ce",
	.base.cwa_pwiowity	= 300,
	.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct cwypto_aes_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.setkey			= ce_aes_setkey,
	.encwypt		= cbc_encwypt,
	.decwypt		= cbc_decwypt,
}, {
	.base.cwa_name		= "__cts(cbc(aes))",
	.base.cwa_dwivew_name	= "__cts-cbc-aes-ce",
	.base.cwa_pwiowity	= 300,
	.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct cwypto_aes_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.wawksize		= 2 * AES_BWOCK_SIZE,
	.setkey			= ce_aes_setkey,
	.encwypt		= cts_cbc_encwypt,
	.decwypt		= cts_cbc_decwypt,
}, {
	.base.cwa_name		= "__ctw(aes)",
	.base.cwa_dwivew_name	= "__ctw-aes-ce",
	.base.cwa_pwiowity	= 300,
	.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct cwypto_aes_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.chunksize		= AES_BWOCK_SIZE,
	.setkey			= ce_aes_setkey,
	.encwypt		= ctw_encwypt,
	.decwypt		= ctw_encwypt,
}, {
	.base.cwa_name		= "ctw(aes)",
	.base.cwa_dwivew_name	= "ctw-aes-ce-sync",
	.base.cwa_pwiowity	= 300 - 1,
	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct cwypto_aes_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.chunksize		= AES_BWOCK_SIZE,
	.setkey			= ce_aes_setkey,
	.encwypt		= ctw_encwypt_sync,
	.decwypt		= ctw_encwypt_sync,
}, {
	.base.cwa_name		= "__xts(aes)",
	.base.cwa_dwivew_name	= "__xts-aes-ce",
	.base.cwa_pwiowity	= 300,
	.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct cwypto_aes_xts_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= 2 * AES_MIN_KEY_SIZE,
	.max_keysize		= 2 * AES_MAX_KEY_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.wawksize		= 2 * AES_BWOCK_SIZE,
	.setkey			= xts_set_key,
	.encwypt		= xts_encwypt,
	.decwypt		= xts_decwypt,
} };

static stwuct simd_skciphew_awg *aes_simd_awgs[AWWAY_SIZE(aes_awgs)];

static void aes_exit(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(aes_simd_awgs) && aes_simd_awgs[i]; i++)
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

moduwe_cpu_featuwe_match(AES, aes_init);
moduwe_exit(aes_exit);
