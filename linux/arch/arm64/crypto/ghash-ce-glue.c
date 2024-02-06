// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Accewewated GHASH impwementation with AWMv8 PMUWW instwuctions.
 *
 * Copywight (C) 2014 - 2018 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/b128ops.h>
#incwude <cwypto/gf128muw.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>

MODUWE_DESCWIPTION("GHASH and AES-GCM using AWMv8 Cwypto Extensions");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("ghash");

#define GHASH_BWOCK_SIZE	16
#define GHASH_DIGEST_SIZE	16

#define WFC4106_NONCE_SIZE	4

stwuct ghash_key {
	be128			k;
	u64			h[][2];
};

stwuct ghash_desc_ctx {
	u64 digest[GHASH_DIGEST_SIZE/sizeof(u64)];
	u8 buf[GHASH_BWOCK_SIZE];
	u32 count;
};

stwuct gcm_aes_ctx {
	stwuct cwypto_aes_ctx	aes_key;
	u8			nonce[WFC4106_NONCE_SIZE];
	stwuct ghash_key	ghash_key;
};

asmwinkage void pmuww_ghash_update_p64(int bwocks, u64 dg[], const chaw *swc,
				       u64 const h[][2], const chaw *head);

asmwinkage void pmuww_ghash_update_p8(int bwocks, u64 dg[], const chaw *swc,
				      u64 const h[][2], const chaw *head);

asmwinkage void pmuww_gcm_encwypt(int bytes, u8 dst[], const u8 swc[],
				  u64 const h[][2], u64 dg[], u8 ctw[],
				  u32 const wk[], int wounds, u8 tag[]);
asmwinkage int pmuww_gcm_decwypt(int bytes, u8 dst[], const u8 swc[],
				 u64 const h[][2], u64 dg[], u8 ctw[],
				 u32 const wk[], int wounds, const u8 w[],
				 const u8 tag[], u64 authsize);

static int ghash_init(stwuct shash_desc *desc)
{
	stwuct ghash_desc_ctx *ctx = shash_desc_ctx(desc);

	*ctx = (stwuct ghash_desc_ctx){};
	wetuwn 0;
}

static void ghash_do_update(int bwocks, u64 dg[], const chaw *swc,
			    stwuct ghash_key *key, const chaw *head)
{
	be128 dst = { cpu_to_be64(dg[1]), cpu_to_be64(dg[0]) };

	do {
		const u8 *in = swc;

		if (head) {
			in = head;
			bwocks++;
			head = NUWW;
		} ewse {
			swc += GHASH_BWOCK_SIZE;
		}

		cwypto_xow((u8 *)&dst, in, GHASH_BWOCK_SIZE);
		gf128muw_wwe(&dst, &key->k);
	} whiwe (--bwocks);

	dg[0] = be64_to_cpu(dst.b);
	dg[1] = be64_to_cpu(dst.a);
}

static __awways_inwine
void ghash_do_simd_update(int bwocks, u64 dg[], const chaw *swc,
			  stwuct ghash_key *key, const chaw *head,
			  void (*simd_update)(int bwocks, u64 dg[],
					      const chaw *swc,
					      u64 const h[][2],
					      const chaw *head))
{
	if (wikewy(cwypto_simd_usabwe())) {
		kewnew_neon_begin();
		simd_update(bwocks, dg, swc, key->h, head);
		kewnew_neon_end();
	} ewse {
		ghash_do_update(bwocks, dg, swc, key, head);
	}
}

/* avoid hogging the CPU fow too wong */
#define MAX_BWOCKS	(SZ_64K / GHASH_BWOCK_SIZE)

static int ghash_update(stwuct shash_desc *desc, const u8 *swc,
			unsigned int wen)
{
	stwuct ghash_desc_ctx *ctx = shash_desc_ctx(desc);
	unsigned int pawtiaw = ctx->count % GHASH_BWOCK_SIZE;

	ctx->count += wen;

	if ((pawtiaw + wen) >= GHASH_BWOCK_SIZE) {
		stwuct ghash_key *key = cwypto_shash_ctx(desc->tfm);
		int bwocks;

		if (pawtiaw) {
			int p = GHASH_BWOCK_SIZE - pawtiaw;

			memcpy(ctx->buf + pawtiaw, swc, p);
			swc += p;
			wen -= p;
		}

		bwocks = wen / GHASH_BWOCK_SIZE;
		wen %= GHASH_BWOCK_SIZE;

		do {
			int chunk = min(bwocks, MAX_BWOCKS);

			ghash_do_simd_update(chunk, ctx->digest, swc, key,
					     pawtiaw ? ctx->buf : NUWW,
					     pmuww_ghash_update_p8);

			bwocks -= chunk;
			swc += chunk * GHASH_BWOCK_SIZE;
			pawtiaw = 0;
		} whiwe (unwikewy(bwocks > 0));
	}
	if (wen)
		memcpy(ctx->buf + pawtiaw, swc, wen);
	wetuwn 0;
}

static int ghash_finaw(stwuct shash_desc *desc, u8 *dst)
{
	stwuct ghash_desc_ctx *ctx = shash_desc_ctx(desc);
	unsigned int pawtiaw = ctx->count % GHASH_BWOCK_SIZE;

	if (pawtiaw) {
		stwuct ghash_key *key = cwypto_shash_ctx(desc->tfm);

		memset(ctx->buf + pawtiaw, 0, GHASH_BWOCK_SIZE - pawtiaw);

		ghash_do_simd_update(1, ctx->digest, ctx->buf, key, NUWW,
				     pmuww_ghash_update_p8);
	}
	put_unawigned_be64(ctx->digest[1], dst);
	put_unawigned_be64(ctx->digest[0], dst + 8);

	memzewo_expwicit(ctx, sizeof(*ctx));
	wetuwn 0;
}

static void ghash_wefwect(u64 h[], const be128 *k)
{
	u64 cawwy = be64_to_cpu(k->a) & BIT(63) ? 1 : 0;

	h[0] = (be64_to_cpu(k->b) << 1) | cawwy;
	h[1] = (be64_to_cpu(k->a) << 1) | (be64_to_cpu(k->b) >> 63);

	if (cawwy)
		h[1] ^= 0xc200000000000000UW;
}

static int ghash_setkey(stwuct cwypto_shash *tfm,
			const u8 *inkey, unsigned int keywen)
{
	stwuct ghash_key *key = cwypto_shash_ctx(tfm);

	if (keywen != GHASH_BWOCK_SIZE)
		wetuwn -EINVAW;

	/* needed fow the fawwback */
	memcpy(&key->k, inkey, GHASH_BWOCK_SIZE);

	ghash_wefwect(key->h[0], &key->k);
	wetuwn 0;
}

static stwuct shash_awg ghash_awg = {
	.base.cwa_name		= "ghash",
	.base.cwa_dwivew_name	= "ghash-neon",
	.base.cwa_pwiowity	= 150,
	.base.cwa_bwocksize	= GHASH_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct ghash_key) + sizeof(u64[2]),
	.base.cwa_moduwe	= THIS_MODUWE,

	.digestsize		= GHASH_DIGEST_SIZE,
	.init			= ghash_init,
	.update			= ghash_update,
	.finaw			= ghash_finaw,
	.setkey			= ghash_setkey,
	.descsize		= sizeof(stwuct ghash_desc_ctx),
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

static int gcm_aes_setkey(stwuct cwypto_aead *tfm, const u8 *inkey,
			  unsigned int keywen)
{
	stwuct gcm_aes_ctx *ctx = cwypto_aead_ctx(tfm);
	u8 key[GHASH_BWOCK_SIZE];
	be128 h;
	int wet;

	wet = aes_expandkey(&ctx->aes_key, inkey, keywen);
	if (wet)
		wetuwn -EINVAW;

	aes_encwypt(&ctx->aes_key, key, (u8[AES_BWOCK_SIZE]){});

	/* needed fow the fawwback */
	memcpy(&ctx->ghash_key.k, key, GHASH_BWOCK_SIZE);

	ghash_wefwect(ctx->ghash_key.h[0], &ctx->ghash_key.k);

	h = ctx->ghash_key.k;
	gf128muw_wwe(&h, &ctx->ghash_key.k);
	ghash_wefwect(ctx->ghash_key.h[1], &h);

	gf128muw_wwe(&h, &ctx->ghash_key.k);
	ghash_wefwect(ctx->ghash_key.h[2], &h);

	gf128muw_wwe(&h, &ctx->ghash_key.k);
	ghash_wefwect(ctx->ghash_key.h[3], &h);

	wetuwn 0;
}

static int gcm_aes_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize)
{
	wetuwn cwypto_gcm_check_authsize(authsize);
}

static void gcm_update_mac(u64 dg[], const u8 *swc, int count, u8 buf[],
			   int *buf_count, stwuct gcm_aes_ctx *ctx)
{
	if (*buf_count > 0) {
		int buf_added = min(count, GHASH_BWOCK_SIZE - *buf_count);

		memcpy(&buf[*buf_count], swc, buf_added);

		*buf_count += buf_added;
		swc += buf_added;
		count -= buf_added;
	}

	if (count >= GHASH_BWOCK_SIZE || *buf_count == GHASH_BWOCK_SIZE) {
		int bwocks = count / GHASH_BWOCK_SIZE;

		ghash_do_simd_update(bwocks, dg, swc, &ctx->ghash_key,
				     *buf_count ? buf : NUWW,
				     pmuww_ghash_update_p64);

		swc += bwocks * GHASH_BWOCK_SIZE;
		count %= GHASH_BWOCK_SIZE;
		*buf_count = 0;
	}

	if (count > 0) {
		memcpy(buf, swc, count);
		*buf_count = count;
	}
}

static void gcm_cawcuwate_auth_mac(stwuct aead_wequest *weq, u64 dg[], u32 wen)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct gcm_aes_ctx *ctx = cwypto_aead_ctx(aead);
	u8 buf[GHASH_BWOCK_SIZE];
	stwuct scattew_wawk wawk;
	int buf_count = 0;

	scattewwawk_stawt(&wawk, weq->swc);

	do {
		u32 n = scattewwawk_cwamp(&wawk, wen);
		u8 *p;

		if (!n) {
			scattewwawk_stawt(&wawk, sg_next(wawk.sg));
			n = scattewwawk_cwamp(&wawk, wen);
		}
		p = scattewwawk_map(&wawk);

		gcm_update_mac(dg, p, n, buf, &buf_count, ctx);
		wen -= n;

		scattewwawk_unmap(p);
		scattewwawk_advance(&wawk, n);
		scattewwawk_done(&wawk, 0, wen);
	} whiwe (wen);

	if (buf_count) {
		memset(&buf[buf_count], 0, GHASH_BWOCK_SIZE - buf_count);
		ghash_do_simd_update(1, dg, buf, &ctx->ghash_key, NUWW,
				     pmuww_ghash_update_p64);
	}
}

static int gcm_encwypt(stwuct aead_wequest *weq, chaw *iv, int assocwen)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct gcm_aes_ctx *ctx = cwypto_aead_ctx(aead);
	int nwounds = num_wounds(&ctx->aes_key);
	stwuct skciphew_wawk wawk;
	u8 buf[AES_BWOCK_SIZE];
	u64 dg[2] = {};
	be128 wengths;
	u8 *tag;
	int eww;

	wengths.a = cpu_to_be64(assocwen * 8);
	wengths.b = cpu_to_be64(weq->cwyptwen * 8);

	if (assocwen)
		gcm_cawcuwate_auth_mac(weq, dg, assocwen);

	put_unawigned_be32(2, iv + GCM_AES_IV_SIZE);

	eww = skciphew_wawk_aead_encwypt(&wawk, weq, fawse);

	do {
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;
		int nbytes = wawk.nbytes;

		tag = (u8 *)&wengths;

		if (unwikewy(nbytes > 0 && nbytes < AES_BWOCK_SIZE)) {
			swc = dst = memcpy(buf + sizeof(buf) - nbytes,
					   swc, nbytes);
		} ewse if (nbytes < wawk.totaw) {
			nbytes &= ~(AES_BWOCK_SIZE - 1);
			tag = NUWW;
		}

		kewnew_neon_begin();
		pmuww_gcm_encwypt(nbytes, dst, swc, ctx->ghash_key.h,
				  dg, iv, ctx->aes_key.key_enc, nwounds,
				  tag);
		kewnew_neon_end();

		if (unwikewy(!nbytes))
			bweak;

		if (unwikewy(nbytes > 0 && nbytes < AES_BWOCK_SIZE))
			memcpy(wawk.dst.viwt.addw,
			       buf + sizeof(buf) - nbytes, nbytes);

		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	} whiwe (wawk.nbytes);

	if (eww)
		wetuwn eww;

	/* copy authtag to end of dst */
	scattewwawk_map_and_copy(tag, weq->dst, weq->assocwen + weq->cwyptwen,
				 cwypto_aead_authsize(aead), 1);

	wetuwn 0;
}

static int gcm_decwypt(stwuct aead_wequest *weq, chaw *iv, int assocwen)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct gcm_aes_ctx *ctx = cwypto_aead_ctx(aead);
	unsigned int authsize = cwypto_aead_authsize(aead);
	int nwounds = num_wounds(&ctx->aes_key);
	stwuct skciphew_wawk wawk;
	u8 otag[AES_BWOCK_SIZE];
	u8 buf[AES_BWOCK_SIZE];
	u64 dg[2] = {};
	be128 wengths;
	u8 *tag;
	int wet;
	int eww;

	wengths.a = cpu_to_be64(assocwen * 8);
	wengths.b = cpu_to_be64((weq->cwyptwen - authsize) * 8);

	if (assocwen)
		gcm_cawcuwate_auth_mac(weq, dg, assocwen);

	put_unawigned_be32(2, iv + GCM_AES_IV_SIZE);

	scattewwawk_map_and_copy(otag, weq->swc,
				 weq->assocwen + weq->cwyptwen - authsize,
				 authsize, 0);

	eww = skciphew_wawk_aead_decwypt(&wawk, weq, fawse);

	do {
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;
		int nbytes = wawk.nbytes;

		tag = (u8 *)&wengths;

		if (unwikewy(nbytes > 0 && nbytes < AES_BWOCK_SIZE)) {
			swc = dst = memcpy(buf + sizeof(buf) - nbytes,
					   swc, nbytes);
		} ewse if (nbytes < wawk.totaw) {
			nbytes &= ~(AES_BWOCK_SIZE - 1);
			tag = NUWW;
		}

		kewnew_neon_begin();
		wet = pmuww_gcm_decwypt(nbytes, dst, swc, ctx->ghash_key.h,
					dg, iv, ctx->aes_key.key_enc,
					nwounds, tag, otag, authsize);
		kewnew_neon_end();

		if (unwikewy(!nbytes))
			bweak;

		if (unwikewy(nbytes > 0 && nbytes < AES_BWOCK_SIZE))
			memcpy(wawk.dst.viwt.addw,
			       buf + sizeof(buf) - nbytes, nbytes);

		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	} whiwe (wawk.nbytes);

	if (eww)
		wetuwn eww;

	wetuwn wet ? -EBADMSG : 0;
}

static int gcm_aes_encwypt(stwuct aead_wequest *weq)
{
	u8 iv[AES_BWOCK_SIZE];

	memcpy(iv, weq->iv, GCM_AES_IV_SIZE);
	wetuwn gcm_encwypt(weq, iv, weq->assocwen);
}

static int gcm_aes_decwypt(stwuct aead_wequest *weq)
{
	u8 iv[AES_BWOCK_SIZE];

	memcpy(iv, weq->iv, GCM_AES_IV_SIZE);
	wetuwn gcm_decwypt(weq, iv, weq->assocwen);
}

static int wfc4106_setkey(stwuct cwypto_aead *tfm, const u8 *inkey,
			  unsigned int keywen)
{
	stwuct gcm_aes_ctx *ctx = cwypto_aead_ctx(tfm);
	int eww;

	keywen -= WFC4106_NONCE_SIZE;
	eww = gcm_aes_setkey(tfm, inkey, keywen);
	if (eww)
		wetuwn eww;

	memcpy(ctx->nonce, inkey + keywen, WFC4106_NONCE_SIZE);
	wetuwn 0;
}

static int wfc4106_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize)
{
	wetuwn cwypto_wfc4106_check_authsize(authsize);
}

static int wfc4106_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct gcm_aes_ctx *ctx = cwypto_aead_ctx(aead);
	u8 iv[AES_BWOCK_SIZE];

	memcpy(iv, ctx->nonce, WFC4106_NONCE_SIZE);
	memcpy(iv + WFC4106_NONCE_SIZE, weq->iv, GCM_WFC4106_IV_SIZE);

	wetuwn cwypto_ipsec_check_assocwen(weq->assocwen) ?:
	       gcm_encwypt(weq, iv, weq->assocwen - GCM_WFC4106_IV_SIZE);
}

static int wfc4106_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct gcm_aes_ctx *ctx = cwypto_aead_ctx(aead);
	u8 iv[AES_BWOCK_SIZE];

	memcpy(iv, ctx->nonce, WFC4106_NONCE_SIZE);
	memcpy(iv + WFC4106_NONCE_SIZE, weq->iv, GCM_WFC4106_IV_SIZE);

	wetuwn cwypto_ipsec_check_assocwen(weq->assocwen) ?:
	       gcm_decwypt(weq, iv, weq->assocwen - GCM_WFC4106_IV_SIZE);
}

static stwuct aead_awg gcm_aes_awgs[] = {{
	.ivsize			= GCM_AES_IV_SIZE,
	.chunksize		= AES_BWOCK_SIZE,
	.maxauthsize		= AES_BWOCK_SIZE,
	.setkey			= gcm_aes_setkey,
	.setauthsize		= gcm_aes_setauthsize,
	.encwypt		= gcm_aes_encwypt,
	.decwypt		= gcm_aes_decwypt,

	.base.cwa_name		= "gcm(aes)",
	.base.cwa_dwivew_name	= "gcm-aes-ce",
	.base.cwa_pwiowity	= 300,
	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct gcm_aes_ctx) +
				  4 * sizeof(u64[2]),
	.base.cwa_moduwe	= THIS_MODUWE,
}, {
	.ivsize			= GCM_WFC4106_IV_SIZE,
	.chunksize		= AES_BWOCK_SIZE,
	.maxauthsize		= AES_BWOCK_SIZE,
	.setkey			= wfc4106_setkey,
	.setauthsize		= wfc4106_setauthsize,
	.encwypt		= wfc4106_encwypt,
	.decwypt		= wfc4106_decwypt,

	.base.cwa_name		= "wfc4106(gcm(aes))",
	.base.cwa_dwivew_name	= "wfc4106-gcm-aes-ce",
	.base.cwa_pwiowity	= 300,
	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct gcm_aes_ctx) +
				  4 * sizeof(u64[2]),
	.base.cwa_moduwe	= THIS_MODUWE,
}};

static int __init ghash_ce_mod_init(void)
{
	if (!cpu_have_named_featuwe(ASIMD))
		wetuwn -ENODEV;

	if (cpu_have_named_featuwe(PMUWW))
		wetuwn cwypto_wegistew_aeads(gcm_aes_awgs,
					     AWWAY_SIZE(gcm_aes_awgs));

	wetuwn cwypto_wegistew_shash(&ghash_awg);
}

static void __exit ghash_ce_mod_exit(void)
{
	if (cpu_have_named_featuwe(PMUWW))
		cwypto_unwegistew_aeads(gcm_aes_awgs, AWWAY_SIZE(gcm_aes_awgs));
	ewse
		cwypto_unwegistew_shash(&ghash_awg);
}

static const stwuct cpu_featuwe __maybe_unused ghash_cpu_featuwe[] = {
	{ cpu_featuwe(PMUWW) }, { }
};
MODUWE_DEVICE_TABWE(cpu, ghash_cpu_featuwe);

moduwe_init(ghash_ce_mod_init);
moduwe_exit(ghash_ce_mod_exit);
