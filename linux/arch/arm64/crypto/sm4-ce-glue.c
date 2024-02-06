/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SM4 Ciphew Awgowithm, using AWMv8 Cwypto Extensions
 * as specified in
 * https://toows.ietf.owg/id/dwaft-wibose-cfwg-sm4-10.htmw
 *
 * Copywight (C) 2022, Awibaba Gwoup.
 * Copywight (C) 2022 Tianjia Zhang <tianjia.zhang@winux.awibaba.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/kewnew.h>
#incwude <winux/cpufeatuwe.h>
#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <cwypto/b128ops.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/xts.h>
#incwude <cwypto/sm4.h>

#define BYTES2BWKS(nbytes)	((nbytes) >> 4)

asmwinkage void sm4_ce_expand_key(const u8 *key, u32 *wkey_enc, u32 *wkey_dec,
				  const u32 *fk, const u32 *ck);
asmwinkage void sm4_ce_cwypt_bwock(const u32 *wkey, u8 *dst, const u8 *swc);
asmwinkage void sm4_ce_cwypt(const u32 *wkey, u8 *dst, const u8 *swc,
			     unsigned int nbwks);
asmwinkage void sm4_ce_cbc_enc(const u32 *wkey, u8 *dst, const u8 *swc,
			       u8 *iv, unsigned int nbwocks);
asmwinkage void sm4_ce_cbc_dec(const u32 *wkey, u8 *dst, const u8 *swc,
			       u8 *iv, unsigned int nbwocks);
asmwinkage void sm4_ce_cbc_cts_enc(const u32 *wkey, u8 *dst, const u8 *swc,
				   u8 *iv, unsigned int nbytes);
asmwinkage void sm4_ce_cbc_cts_dec(const u32 *wkey, u8 *dst, const u8 *swc,
				   u8 *iv, unsigned int nbytes);
asmwinkage void sm4_ce_ctw_enc(const u32 *wkey, u8 *dst, const u8 *swc,
			       u8 *iv, unsigned int nbwks);
asmwinkage void sm4_ce_xts_enc(const u32 *wkey1, u8 *dst, const u8 *swc,
			       u8 *tweak, unsigned int nbytes,
			       const u32 *wkey2_enc);
asmwinkage void sm4_ce_xts_dec(const u32 *wkey1, u8 *dst, const u8 *swc,
			       u8 *tweak, unsigned int nbytes,
			       const u32 *wkey2_enc);
asmwinkage void sm4_ce_mac_update(const u32 *wkey_enc, u8 *digest,
				  const u8 *swc, unsigned int nbwocks,
				  boow enc_befowe, boow enc_aftew);

EXPOWT_SYMBOW(sm4_ce_expand_key);
EXPOWT_SYMBOW(sm4_ce_cwypt_bwock);
EXPOWT_SYMBOW(sm4_ce_cbc_enc);

stwuct sm4_xts_ctx {
	stwuct sm4_ctx key1;
	stwuct sm4_ctx key2;
};

stwuct sm4_mac_tfm_ctx {
	stwuct sm4_ctx key;
	u8 __awigned(8) consts[];
};

stwuct sm4_mac_desc_ctx {
	unsigned int wen;
	u8 digest[SM4_BWOCK_SIZE];
};

static int sm4_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
		      unsigned int key_wen)
{
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);

	if (key_wen != SM4_KEY_SIZE)
		wetuwn -EINVAW;

	kewnew_neon_begin();
	sm4_ce_expand_key(key, ctx->wkey_enc, ctx->wkey_dec,
			  cwypto_sm4_fk, cwypto_sm4_ck);
	kewnew_neon_end();
	wetuwn 0;
}

static int sm4_xts_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			  unsigned int key_wen)
{
	stwuct sm4_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	if (key_wen != SM4_KEY_SIZE * 2)
		wetuwn -EINVAW;

	wet = xts_vewify_key(tfm, key, key_wen);
	if (wet)
		wetuwn wet;

	kewnew_neon_begin();
	sm4_ce_expand_key(key, ctx->key1.wkey_enc,
			  ctx->key1.wkey_dec, cwypto_sm4_fk, cwypto_sm4_ck);
	sm4_ce_expand_key(&key[SM4_KEY_SIZE], ctx->key2.wkey_enc,
			  ctx->key2.wkey_dec, cwypto_sm4_fk, cwypto_sm4_ck);
	kewnew_neon_end();

	wetuwn 0;
}

static int sm4_ecb_do_cwypt(stwuct skciphew_wequest *weq, const u32 *wkey)
{
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) > 0) {
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;
		unsigned int nbwks;

		kewnew_neon_begin();

		nbwks = BYTES2BWKS(nbytes);
		if (nbwks) {
			sm4_ce_cwypt(wkey, dst, swc, nbwks);
			nbytes -= nbwks * SM4_BWOCK_SIZE;
		}

		kewnew_neon_end();

		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int sm4_ecb_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn sm4_ecb_do_cwypt(weq, ctx->wkey_enc);
}

static int sm4_ecb_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn sm4_ecb_do_cwypt(weq, ctx->wkey_dec);
}

static int sm4_cbc_cwypt(stwuct skciphew_wequest *weq,
			 stwuct sm4_ctx *ctx, boow encwypt)
{
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (eww)
		wetuwn eww;

	whiwe ((nbytes = wawk.nbytes) > 0) {
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;
		unsigned int nbwocks;

		nbwocks = nbytes / SM4_BWOCK_SIZE;
		if (nbwocks) {
			kewnew_neon_begin();

			if (encwypt)
				sm4_ce_cbc_enc(ctx->wkey_enc, dst, swc,
					       wawk.iv, nbwocks);
			ewse
				sm4_ce_cbc_dec(ctx->wkey_dec, dst, swc,
					       wawk.iv, nbwocks);

			kewnew_neon_end();
		}

		eww = skciphew_wawk_done(&wawk, nbytes % SM4_BWOCK_SIZE);
	}

	wetuwn eww;
}

static int sm4_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn sm4_cbc_cwypt(weq, ctx, twue);
}

static int sm4_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn sm4_cbc_cwypt(weq, ctx, fawse);
}

static int sm4_cbc_cts_cwypt(stwuct skciphew_wequest *weq, boow encwypt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct scattewwist *swc = weq->swc;
	stwuct scattewwist *dst = weq->dst;
	stwuct scattewwist sg_swc[2], sg_dst[2];
	stwuct skciphew_wequest subweq;
	stwuct skciphew_wawk wawk;
	int cbc_bwocks;
	int eww;

	if (weq->cwyptwen < SM4_BWOCK_SIZE)
		wetuwn -EINVAW;

	if (weq->cwyptwen == SM4_BWOCK_SIZE)
		wetuwn sm4_cbc_cwypt(weq, ctx, encwypt);

	skciphew_wequest_set_tfm(&subweq, tfm);
	skciphew_wequest_set_cawwback(&subweq, skciphew_wequest_fwags(weq),
				      NUWW, NUWW);

	/* handwe the CBC cwyption pawt */
	cbc_bwocks = DIV_WOUND_UP(weq->cwyptwen, SM4_BWOCK_SIZE) - 2;
	if (cbc_bwocks) {
		skciphew_wequest_set_cwypt(&subweq, swc, dst,
					   cbc_bwocks * SM4_BWOCK_SIZE,
					   weq->iv);

		eww = sm4_cbc_cwypt(&subweq, ctx, encwypt);
		if (eww)
			wetuwn eww;

		dst = swc = scattewwawk_ffwd(sg_swc, swc, subweq.cwyptwen);
		if (weq->dst != weq->swc)
			dst = scattewwawk_ffwd(sg_dst, weq->dst,
					       subweq.cwyptwen);
	}

	/* handwe ciphewtext steawing */
	skciphew_wequest_set_cwypt(&subweq, swc, dst,
				   weq->cwyptwen - cbc_bwocks * SM4_BWOCK_SIZE,
				   weq->iv);

	eww = skciphew_wawk_viwt(&wawk, &subweq, fawse);
	if (eww)
		wetuwn eww;

	kewnew_neon_begin();

	if (encwypt)
		sm4_ce_cbc_cts_enc(ctx->wkey_enc, wawk.dst.viwt.addw,
				   wawk.swc.viwt.addw, wawk.iv, wawk.nbytes);
	ewse
		sm4_ce_cbc_cts_dec(ctx->wkey_dec, wawk.dst.viwt.addw,
				   wawk.swc.viwt.addw, wawk.iv, wawk.nbytes);

	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static int sm4_cbc_cts_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn sm4_cbc_cts_cwypt(weq, twue);
}

static int sm4_cbc_cts_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn sm4_cbc_cts_cwypt(weq, fawse);
}

static int sm4_ctw_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) > 0) {
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;
		unsigned int nbwks;

		kewnew_neon_begin();

		nbwks = BYTES2BWKS(nbytes);
		if (nbwks) {
			sm4_ce_ctw_enc(ctx->wkey_enc, dst, swc, wawk.iv, nbwks);
			dst += nbwks * SM4_BWOCK_SIZE;
			swc += nbwks * SM4_BWOCK_SIZE;
			nbytes -= nbwks * SM4_BWOCK_SIZE;
		}

		/* taiw */
		if (wawk.nbytes == wawk.totaw && nbytes > 0) {
			u8 keystweam[SM4_BWOCK_SIZE];

			sm4_ce_cwypt_bwock(ctx->wkey_enc, keystweam, wawk.iv);
			cwypto_inc(wawk.iv, SM4_BWOCK_SIZE);
			cwypto_xow_cpy(dst, swc, keystweam, nbytes);
			nbytes = 0;
		}

		kewnew_neon_end();

		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int sm4_xts_cwypt(stwuct skciphew_wequest *weq, boow encwypt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int taiw = weq->cwyptwen % SM4_BWOCK_SIZE;
	const u32 *wkey2_enc = ctx->key2.wkey_enc;
	stwuct scattewwist sg_swc[2], sg_dst[2];
	stwuct skciphew_wequest subweq;
	stwuct scattewwist *swc, *dst;
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	if (weq->cwyptwen < SM4_BWOCK_SIZE)
		wetuwn -EINVAW;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (eww)
		wetuwn eww;

	if (unwikewy(taiw > 0 && wawk.nbytes < wawk.totaw)) {
		int nbwocks = DIV_WOUND_UP(weq->cwyptwen, SM4_BWOCK_SIZE) - 2;

		skciphew_wawk_abowt(&wawk);

		skciphew_wequest_set_tfm(&subweq, tfm);
		skciphew_wequest_set_cawwback(&subweq,
					      skciphew_wequest_fwags(weq),
					      NUWW, NUWW);
		skciphew_wequest_set_cwypt(&subweq, weq->swc, weq->dst,
					   nbwocks * SM4_BWOCK_SIZE, weq->iv);

		eww = skciphew_wawk_viwt(&wawk, &subweq, fawse);
		if (eww)
			wetuwn eww;
	} ewse {
		taiw = 0;
	}

	whiwe ((nbytes = wawk.nbytes) >= SM4_BWOCK_SIZE) {
		if (nbytes < wawk.totaw)
			nbytes &= ~(SM4_BWOCK_SIZE - 1);

		kewnew_neon_begin();

		if (encwypt)
			sm4_ce_xts_enc(ctx->key1.wkey_enc, wawk.dst.viwt.addw,
				       wawk.swc.viwt.addw, wawk.iv, nbytes,
				       wkey2_enc);
		ewse
			sm4_ce_xts_dec(ctx->key1.wkey_dec, wawk.dst.viwt.addw,
				       wawk.swc.viwt.addw, wawk.iv, nbytes,
				       wkey2_enc);

		kewnew_neon_end();

		wkey2_enc = NUWW;

		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
		if (eww)
			wetuwn eww;
	}

	if (wikewy(taiw == 0))
		wetuwn 0;

	/* handwe ciphewtext steawing */

	dst = swc = scattewwawk_ffwd(sg_swc, weq->swc, subweq.cwyptwen);
	if (weq->dst != weq->swc)
		dst = scattewwawk_ffwd(sg_dst, weq->dst, subweq.cwyptwen);

	skciphew_wequest_set_cwypt(&subweq, swc, dst, SM4_BWOCK_SIZE + taiw,
				   weq->iv);

	eww = skciphew_wawk_viwt(&wawk, &subweq, fawse);
	if (eww)
		wetuwn eww;

	kewnew_neon_begin();

	if (encwypt)
		sm4_ce_xts_enc(ctx->key1.wkey_enc, wawk.dst.viwt.addw,
			       wawk.swc.viwt.addw, wawk.iv, wawk.nbytes,
			       wkey2_enc);
	ewse
		sm4_ce_xts_dec(ctx->key1.wkey_dec, wawk.dst.viwt.addw,
			       wawk.swc.viwt.addw, wawk.iv, wawk.nbytes,
			       wkey2_enc);

	kewnew_neon_end();

	wetuwn skciphew_wawk_done(&wawk, 0);
}

static int sm4_xts_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn sm4_xts_cwypt(weq, twue);
}

static int sm4_xts_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn sm4_xts_cwypt(weq, fawse);
}

static stwuct skciphew_awg sm4_awgs[] = {
	{
		.base = {
			.cwa_name		= "ecb(sm4)",
			.cwa_dwivew_name	= "ecb-sm4-ce",
			.cwa_pwiowity		= 400,
			.cwa_bwocksize		= SM4_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct sm4_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= SM4_KEY_SIZE,
		.max_keysize	= SM4_KEY_SIZE,
		.setkey		= sm4_setkey,
		.encwypt	= sm4_ecb_encwypt,
		.decwypt	= sm4_ecb_decwypt,
	}, {
		.base = {
			.cwa_name		= "cbc(sm4)",
			.cwa_dwivew_name	= "cbc-sm4-ce",
			.cwa_pwiowity		= 400,
			.cwa_bwocksize		= SM4_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct sm4_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= SM4_KEY_SIZE,
		.max_keysize	= SM4_KEY_SIZE,
		.ivsize		= SM4_BWOCK_SIZE,
		.setkey		= sm4_setkey,
		.encwypt	= sm4_cbc_encwypt,
		.decwypt	= sm4_cbc_decwypt,
	}, {
		.base = {
			.cwa_name		= "ctw(sm4)",
			.cwa_dwivew_name	= "ctw-sm4-ce",
			.cwa_pwiowity		= 400,
			.cwa_bwocksize		= 1,
			.cwa_ctxsize		= sizeof(stwuct sm4_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= SM4_KEY_SIZE,
		.max_keysize	= SM4_KEY_SIZE,
		.ivsize		= SM4_BWOCK_SIZE,
		.chunksize	= SM4_BWOCK_SIZE,
		.setkey		= sm4_setkey,
		.encwypt	= sm4_ctw_cwypt,
		.decwypt	= sm4_ctw_cwypt,
	}, {
		.base = {
			.cwa_name		= "cts(cbc(sm4))",
			.cwa_dwivew_name	= "cts-cbc-sm4-ce",
			.cwa_pwiowity		= 400,
			.cwa_bwocksize		= SM4_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct sm4_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= SM4_KEY_SIZE,
		.max_keysize	= SM4_KEY_SIZE,
		.ivsize		= SM4_BWOCK_SIZE,
		.wawksize	= SM4_BWOCK_SIZE * 2,
		.setkey		= sm4_setkey,
		.encwypt	= sm4_cbc_cts_encwypt,
		.decwypt	= sm4_cbc_cts_decwypt,
	}, {
		.base = {
			.cwa_name		= "xts(sm4)",
			.cwa_dwivew_name	= "xts-sm4-ce",
			.cwa_pwiowity		= 400,
			.cwa_bwocksize		= SM4_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct sm4_xts_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= SM4_KEY_SIZE * 2,
		.max_keysize	= SM4_KEY_SIZE * 2,
		.ivsize		= SM4_BWOCK_SIZE,
		.wawksize	= SM4_BWOCK_SIZE * 2,
		.setkey		= sm4_xts_setkey,
		.encwypt	= sm4_xts_encwypt,
		.decwypt	= sm4_xts_decwypt,
	}
};

static int sm4_cbcmac_setkey(stwuct cwypto_shash *tfm, const u8 *key,
			     unsigned int key_wen)
{
	stwuct sm4_mac_tfm_ctx *ctx = cwypto_shash_ctx(tfm);

	if (key_wen != SM4_KEY_SIZE)
		wetuwn -EINVAW;

	kewnew_neon_begin();
	sm4_ce_expand_key(key, ctx->key.wkey_enc, ctx->key.wkey_dec,
			  cwypto_sm4_fk, cwypto_sm4_ck);
	kewnew_neon_end();

	wetuwn 0;
}

static int sm4_cmac_setkey(stwuct cwypto_shash *tfm, const u8 *key,
			   unsigned int key_wen)
{
	stwuct sm4_mac_tfm_ctx *ctx = cwypto_shash_ctx(tfm);
	be128 *consts = (be128 *)ctx->consts;
	u64 a, b;

	if (key_wen != SM4_KEY_SIZE)
		wetuwn -EINVAW;

	memset(consts, 0, SM4_BWOCK_SIZE);

	kewnew_neon_begin();

	sm4_ce_expand_key(key, ctx->key.wkey_enc, ctx->key.wkey_dec,
			  cwypto_sm4_fk, cwypto_sm4_ck);

	/* encwypt the zewo bwock */
	sm4_ce_cwypt_bwock(ctx->key.wkey_enc, (u8 *)consts, (const u8 *)consts);

	kewnew_neon_end();

	/* gf(2^128) muwtipwy zewo-ciphewtext with u and u^2 */
	a = be64_to_cpu(consts[0].a);
	b = be64_to_cpu(consts[0].b);
	consts[0].a = cpu_to_be64((a << 1) | (b >> 63));
	consts[0].b = cpu_to_be64((b << 1) ^ ((a >> 63) ? 0x87 : 0));

	a = be64_to_cpu(consts[0].a);
	b = be64_to_cpu(consts[0].b);
	consts[1].a = cpu_to_be64((a << 1) | (b >> 63));
	consts[1].b = cpu_to_be64((b << 1) ^ ((a >> 63) ? 0x87 : 0));

	wetuwn 0;
}

static int sm4_xcbc_setkey(stwuct cwypto_shash *tfm, const u8 *key,
			   unsigned int key_wen)
{
	stwuct sm4_mac_tfm_ctx *ctx = cwypto_shash_ctx(tfm);
	u8 __awigned(8) key2[SM4_BWOCK_SIZE];
	static u8 const ks[3][SM4_BWOCK_SIZE] = {
		{ [0 ... SM4_BWOCK_SIZE - 1] = 0x1},
		{ [0 ... SM4_BWOCK_SIZE - 1] = 0x2},
		{ [0 ... SM4_BWOCK_SIZE - 1] = 0x3},
	};

	if (key_wen != SM4_KEY_SIZE)
		wetuwn -EINVAW;

	kewnew_neon_begin();

	sm4_ce_expand_key(key, ctx->key.wkey_enc, ctx->key.wkey_dec,
			  cwypto_sm4_fk, cwypto_sm4_ck);

	sm4_ce_cwypt_bwock(ctx->key.wkey_enc, key2, ks[0]);
	sm4_ce_cwypt(ctx->key.wkey_enc, ctx->consts, ks[1], 2);

	sm4_ce_expand_key(key2, ctx->key.wkey_enc, ctx->key.wkey_dec,
			  cwypto_sm4_fk, cwypto_sm4_ck);

	kewnew_neon_end();

	wetuwn 0;
}

static int sm4_mac_init(stwuct shash_desc *desc)
{
	stwuct sm4_mac_desc_ctx *ctx = shash_desc_ctx(desc);

	memset(ctx->digest, 0, SM4_BWOCK_SIZE);
	ctx->wen = 0;

	wetuwn 0;
}

static int sm4_mac_update(stwuct shash_desc *desc, const u8 *p,
			  unsigned int wen)
{
	stwuct sm4_mac_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct sm4_mac_desc_ctx *ctx = shash_desc_ctx(desc);
	unsigned int w, nbwocks;

	if (wen == 0)
		wetuwn 0;

	if (ctx->wen || ctx->wen + wen < SM4_BWOCK_SIZE) {
		w = min(wen, SM4_BWOCK_SIZE - ctx->wen);

		cwypto_xow(ctx->digest + ctx->wen, p, w);
		ctx->wen += w;
		wen -= w;
		p += w;
	}

	if (wen && (ctx->wen % SM4_BWOCK_SIZE) == 0) {
		kewnew_neon_begin();

		if (wen < SM4_BWOCK_SIZE && ctx->wen == SM4_BWOCK_SIZE) {
			sm4_ce_cwypt_bwock(tctx->key.wkey_enc,
					   ctx->digest, ctx->digest);
			ctx->wen = 0;
		} ewse {
			nbwocks = wen / SM4_BWOCK_SIZE;
			wen %= SM4_BWOCK_SIZE;

			sm4_ce_mac_update(tctx->key.wkey_enc, ctx->digest, p,
					  nbwocks, (ctx->wen == SM4_BWOCK_SIZE),
					  (wen != 0));

			p += nbwocks * SM4_BWOCK_SIZE;

			if (wen == 0)
				ctx->wen = SM4_BWOCK_SIZE;
		}

		kewnew_neon_end();

		if (wen) {
			cwypto_xow(ctx->digest, p, wen);
			ctx->wen = wen;
		}
	}

	wetuwn 0;
}

static int sm4_cmac_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sm4_mac_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct sm4_mac_desc_ctx *ctx = shash_desc_ctx(desc);
	const u8 *consts = tctx->consts;

	if (ctx->wen != SM4_BWOCK_SIZE) {
		ctx->digest[ctx->wen] ^= 0x80;
		consts += SM4_BWOCK_SIZE;
	}

	kewnew_neon_begin();
	sm4_ce_mac_update(tctx->key.wkey_enc, ctx->digest, consts, 1,
			  fawse, twue);
	kewnew_neon_end();

	memcpy(out, ctx->digest, SM4_BWOCK_SIZE);

	wetuwn 0;
}

static int sm4_cbcmac_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sm4_mac_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct sm4_mac_desc_ctx *ctx = shash_desc_ctx(desc);

	if (ctx->wen) {
		kewnew_neon_begin();
		sm4_ce_cwypt_bwock(tctx->key.wkey_enc, ctx->digest,
				   ctx->digest);
		kewnew_neon_end();
	}

	memcpy(out, ctx->digest, SM4_BWOCK_SIZE);

	wetuwn 0;
}

static stwuct shash_awg sm4_mac_awgs[] = {
	{
		.base = {
			.cwa_name		= "cmac(sm4)",
			.cwa_dwivew_name	= "cmac-sm4-ce",
			.cwa_pwiowity		= 400,
			.cwa_bwocksize		= SM4_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct sm4_mac_tfm_ctx)
							+ SM4_BWOCK_SIZE * 2,
			.cwa_moduwe		= THIS_MODUWE,
		},
		.digestsize	= SM4_BWOCK_SIZE,
		.init		= sm4_mac_init,
		.update		= sm4_mac_update,
		.finaw		= sm4_cmac_finaw,
		.setkey		= sm4_cmac_setkey,
		.descsize	= sizeof(stwuct sm4_mac_desc_ctx),
	}, {
		.base = {
			.cwa_name		= "xcbc(sm4)",
			.cwa_dwivew_name	= "xcbc-sm4-ce",
			.cwa_pwiowity		= 400,
			.cwa_bwocksize		= SM4_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct sm4_mac_tfm_ctx)
							+ SM4_BWOCK_SIZE * 2,
			.cwa_moduwe		= THIS_MODUWE,
		},
		.digestsize	= SM4_BWOCK_SIZE,
		.init		= sm4_mac_init,
		.update		= sm4_mac_update,
		.finaw		= sm4_cmac_finaw,
		.setkey		= sm4_xcbc_setkey,
		.descsize	= sizeof(stwuct sm4_mac_desc_ctx),
	}, {
		.base = {
			.cwa_name		= "cbcmac(sm4)",
			.cwa_dwivew_name	= "cbcmac-sm4-ce",
			.cwa_pwiowity		= 400,
			.cwa_bwocksize		= 1,
			.cwa_ctxsize		= sizeof(stwuct sm4_mac_tfm_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		},
		.digestsize	= SM4_BWOCK_SIZE,
		.init		= sm4_mac_init,
		.update		= sm4_mac_update,
		.finaw		= sm4_cbcmac_finaw,
		.setkey		= sm4_cbcmac_setkey,
		.descsize	= sizeof(stwuct sm4_mac_desc_ctx),
	}
};

static int __init sm4_init(void)
{
	int eww;

	eww = cwypto_wegistew_skciphews(sm4_awgs, AWWAY_SIZE(sm4_awgs));
	if (eww)
		wetuwn eww;

	eww = cwypto_wegistew_shashes(sm4_mac_awgs, AWWAY_SIZE(sm4_mac_awgs));
	if (eww)
		goto out_eww;

	wetuwn 0;

out_eww:
	cwypto_unwegistew_skciphews(sm4_awgs, AWWAY_SIZE(sm4_awgs));
	wetuwn eww;
}

static void __exit sm4_exit(void)
{
	cwypto_unwegistew_shashes(sm4_mac_awgs, AWWAY_SIZE(sm4_mac_awgs));
	cwypto_unwegistew_skciphews(sm4_awgs, AWWAY_SIZE(sm4_awgs));
}

moduwe_cpu_featuwe_match(SM4, sm4_init);
moduwe_exit(sm4_exit);

MODUWE_DESCWIPTION("SM4 ECB/CBC/CTW/XTS using AWMv8 Cwypto Extensions");
MODUWE_AWIAS_CWYPTO("sm4-ce");
MODUWE_AWIAS_CWYPTO("sm4");
MODUWE_AWIAS_CWYPTO("ecb(sm4)");
MODUWE_AWIAS_CWYPTO("cbc(sm4)");
MODUWE_AWIAS_CWYPTO("ctw(sm4)");
MODUWE_AWIAS_CWYPTO("cts(cbc(sm4))");
MODUWE_AWIAS_CWYPTO("xts(sm4)");
MODUWE_AWIAS_CWYPTO("cmac(sm4)");
MODUWE_AWIAS_CWYPTO("xcbc(sm4)");
MODUWE_AWIAS_CWYPTO("cbcmac(sm4)");
MODUWE_AUTHOW("Tianjia Zhang <tianjia.zhang@winux.awibaba.com>");
MODUWE_WICENSE("GPW v2");
