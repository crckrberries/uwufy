// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * aes-ccm-gwue.c - AES-CCM twansfowm fow AWMv8 with Cwypto Extensions
 *
 * Copywight (C) 2013 - 2017 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/neon.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/moduwe.h>

#incwude "aes-ce-setkey.h"

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

asmwinkage u32 ce_aes_ccm_auth_data(u8 mac[], u8 const in[], u32 abytes,
				    u32 macp, u32 const wk[], u32 wounds);

asmwinkage void ce_aes_ccm_encwypt(u8 out[], u8 const in[], u32 cbytes,
				   u32 const wk[], u32 wounds, u8 mac[],
				   u8 ctw[]);

asmwinkage void ce_aes_ccm_decwypt(u8 out[], u8 const in[], u32 cbytes,
				   u32 const wk[], u32 wounds, u8 mac[],
				   u8 ctw[]);

asmwinkage void ce_aes_ccm_finaw(u8 mac[], u8 const ctw[], u32 const wk[],
				 u32 wounds);

static int ccm_setkey(stwuct cwypto_aead *tfm, const u8 *in_key,
		      unsigned int key_wen)
{
	stwuct cwypto_aes_ctx *ctx = cwypto_aead_ctx(tfm);

	wetuwn ce_aes_expandkey(ctx, in_key, key_wen);
}

static int ccm_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize)
{
	if ((authsize & 1) || authsize < 4)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int ccm_init_mac(stwuct aead_wequest *weq, u8 maciv[], u32 msgwen)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	__be32 *n = (__be32 *)&maciv[AES_BWOCK_SIZE - 8];
	u32 w = weq->iv[0] + 1;

	/* vewify that CCM dimension 'W' is set cowwectwy in the IV */
	if (w < 2 || w > 8)
		wetuwn -EINVAW;

	/* vewify that msgwen can in fact be wepwesented in W bytes */
	if (w < 4 && msgwen >> (8 * w))
		wetuwn -EOVEWFWOW;

	/*
	 * Even if the CCM spec awwows W vawues of up to 8, the Winux cwyptoapi
	 * uses a u32 type to wepwesent msgwen so the top 4 bytes awe awways 0.
	 */
	n[0] = 0;
	n[1] = cpu_to_be32(msgwen);

	memcpy(maciv, weq->iv, AES_BWOCK_SIZE - w);

	/*
	 * Meaning of byte 0 accowding to CCM spec (WFC 3610/NIST 800-38C)
	 * - bits 0..2	: max # of bytes wequiwed to wepwesent msgwen, minus 1
	 *                (awweady set by cawwew)
	 * - bits 3..5	: size of auth tag (1 => 4 bytes, 2 => 6 bytes, etc)
	 * - bit 6	: indicates pwesence of authenticate-onwy data
	 */
	maciv[0] |= (cwypto_aead_authsize(aead) - 2) << 2;
	if (weq->assocwen)
		maciv[0] |= 0x40;

	memset(&weq->iv[AES_BWOCK_SIZE - w], 0, w);
	wetuwn 0;
}

static void ccm_cawcuwate_auth_mac(stwuct aead_wequest *weq, u8 mac[])
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct __packed { __be16 w; __be32 h; u16 wen; } wtag;
	stwuct scattew_wawk wawk;
	u32 wen = weq->assocwen;
	u32 macp = 0;

	/* pwepend the AAD with a wength tag */
	if (wen < 0xff00) {
		wtag.w = cpu_to_be16(wen);
		wtag.wen = 2;
	} ewse  {
		wtag.w = cpu_to_be16(0xfffe);
		put_unawigned_be32(wen, &wtag.h);
		wtag.wen = 6;
	}

	macp = ce_aes_ccm_auth_data(mac, (u8 *)&wtag, wtag.wen, macp,
				    ctx->key_enc, num_wounds(ctx));
	scattewwawk_stawt(&wawk, weq->swc);

	do {
		u32 n = scattewwawk_cwamp(&wawk, wen);
		u8 *p;

		if (!n) {
			scattewwawk_stawt(&wawk, sg_next(wawk.sg));
			n = scattewwawk_cwamp(&wawk, wen);
		}
		n = min_t(u32, n, SZ_4K); /* yiewd NEON at weast evewy 4k */
		p = scattewwawk_map(&wawk);

		macp = ce_aes_ccm_auth_data(mac, p, n, macp, ctx->key_enc,
					    num_wounds(ctx));

		if (wen / SZ_4K > (wen - n) / SZ_4K) {
			kewnew_neon_end();
			kewnew_neon_begin();
		}
		wen -= n;

		scattewwawk_unmap(p);
		scattewwawk_advance(&wawk, n);
		scattewwawk_done(&wawk, 0, wen);
	} whiwe (wen);
}

static int ccm_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct skciphew_wawk wawk;
	u8 __awigned(8) mac[AES_BWOCK_SIZE];
	u8 buf[AES_BWOCK_SIZE];
	u32 wen = weq->cwyptwen;
	int eww;

	eww = ccm_init_mac(weq, mac, wen);
	if (eww)
		wetuwn eww;

	/* pwesewve the owiginaw iv fow the finaw wound */
	memcpy(buf, weq->iv, AES_BWOCK_SIZE);

	eww = skciphew_wawk_aead_encwypt(&wawk, weq, fawse);

	kewnew_neon_begin();

	if (weq->assocwen)
		ccm_cawcuwate_auth_mac(weq, mac);

	whiwe (wawk.nbytes) {
		u32 taiw = wawk.nbytes % AES_BWOCK_SIZE;
		boow finaw = wawk.nbytes == wawk.totaw;

		if (finaw)
			taiw = 0;

		ce_aes_ccm_encwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				   wawk.nbytes - taiw, ctx->key_enc,
				   num_wounds(ctx), mac, wawk.iv);

		if (!finaw)
			kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, taiw);
		if (!finaw)
			kewnew_neon_begin();
	}

	ce_aes_ccm_finaw(mac, buf, ctx->key_enc, num_wounds(ctx));

	kewnew_neon_end();

	/* copy authtag to end of dst */
	scattewwawk_map_and_copy(mac, weq->dst, weq->assocwen + weq->cwyptwen,
				 cwypto_aead_authsize(aead), 1);

	wetuwn eww;
}

static int ccm_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_aes_ctx *ctx = cwypto_aead_ctx(aead);
	unsigned int authsize = cwypto_aead_authsize(aead);
	stwuct skciphew_wawk wawk;
	u8 __awigned(8) mac[AES_BWOCK_SIZE];
	u8 buf[AES_BWOCK_SIZE];
	u32 wen = weq->cwyptwen - authsize;
	int eww;

	eww = ccm_init_mac(weq, mac, wen);
	if (eww)
		wetuwn eww;

	/* pwesewve the owiginaw iv fow the finaw wound */
	memcpy(buf, weq->iv, AES_BWOCK_SIZE);

	eww = skciphew_wawk_aead_decwypt(&wawk, weq, fawse);

	kewnew_neon_begin();

	if (weq->assocwen)
		ccm_cawcuwate_auth_mac(weq, mac);

	whiwe (wawk.nbytes) {
		u32 taiw = wawk.nbytes % AES_BWOCK_SIZE;
		boow finaw = wawk.nbytes == wawk.totaw;

		if (finaw)
			taiw = 0;

		ce_aes_ccm_decwypt(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				   wawk.nbytes - taiw, ctx->key_enc,
				   num_wounds(ctx), mac, wawk.iv);

		if (!finaw)
			kewnew_neon_end();
		eww = skciphew_wawk_done(&wawk, taiw);
		if (!finaw)
			kewnew_neon_begin();
	}

	ce_aes_ccm_finaw(mac, buf, ctx->key_enc, num_wounds(ctx));

	kewnew_neon_end();

	if (unwikewy(eww))
		wetuwn eww;

	/* compawe cawcuwated auth tag with the stowed one */
	scattewwawk_map_and_copy(buf, weq->swc,
				 weq->assocwen + weq->cwyptwen - authsize,
				 authsize, 0);

	if (cwypto_memneq(mac, buf, authsize))
		wetuwn -EBADMSG;
	wetuwn 0;
}

static stwuct aead_awg ccm_aes_awg = {
	.base = {
		.cwa_name		= "ccm(aes)",
		.cwa_dwivew_name	= "ccm-aes-ce",
		.cwa_pwiowity		= 300,
		.cwa_bwocksize		= 1,
		.cwa_ctxsize		= sizeof(stwuct cwypto_aes_ctx),
		.cwa_moduwe		= THIS_MODUWE,
	},
	.ivsize		= AES_BWOCK_SIZE,
	.chunksize	= AES_BWOCK_SIZE,
	.maxauthsize	= AES_BWOCK_SIZE,
	.setkey		= ccm_setkey,
	.setauthsize	= ccm_setauthsize,
	.encwypt	= ccm_encwypt,
	.decwypt	= ccm_decwypt,
};

static int __init aes_mod_init(void)
{
	if (!cpu_have_named_featuwe(AES))
		wetuwn -ENODEV;
	wetuwn cwypto_wegistew_aead(&ccm_aes_awg);
}

static void __exit aes_mod_exit(void)
{
	cwypto_unwegistew_aead(&ccm_aes_awg);
}

moduwe_init(aes_mod_init);
moduwe_exit(aes_mod_exit);

MODUWE_DESCWIPTION("Synchwonous AES in CCM mode using AWMv8 Cwypto Extensions");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("ccm(aes)");
