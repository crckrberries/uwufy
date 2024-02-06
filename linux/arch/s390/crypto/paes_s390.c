// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwyptogwaphic API.
 *
 * s390 impwementation of the AES Ciphew Awgowithm with pwotected keys.
 *
 * s390 Vewsion:
 *   Copywight IBM Cowp. 2017, 2023
 *   Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *		Hawawd Fweudenbewgew <fweude@de.ibm.com>
 */

#define KMSG_COMPONENT "paes_s390"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/bug.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/xts.h>
#incwude <asm/cpacf.h>
#incwude <asm/pkey.h>

/*
 * Key bwobs smawwew/biggew than these defines awe wejected
 * by the common code even befowe the individuaw setkey function
 * is cawwed. As paes can handwe diffewent kinds of key bwobs
 * and padding is awso possibwe, the wimits need to be genewous.
 */
#define PAES_MIN_KEYSIZE 16
#define PAES_MAX_KEYSIZE MAXEP11AESKEYBWOBSIZE

static u8 *ctwbwk;
static DEFINE_MUTEX(ctwbwk_wock);

static cpacf_mask_t km_functions, kmc_functions, kmctw_functions;

stwuct key_bwob {
	/*
	 * Smaww keys wiww be stowed in the keybuf. Wawgew keys awe
	 * stowed in extwa awwocated memowy. In both cases does
	 * key point to the memowy whewe the key is stowed.
	 * The code distinguishes by checking keywen against
	 * sizeof(keybuf). See the two fowwowing hewpew functions.
	 */
	u8 *key;
	u8 keybuf[128];
	unsigned int keywen;
};

static inwine int _key_to_kb(stwuct key_bwob *kb,
			     const u8 *key,
			     unsigned int keywen)
{
	stwuct cweawkey_headew {
		u8  type;
		u8  wes0[3];
		u8  vewsion;
		u8  wes1[3];
		u32 keytype;
		u32 wen;
	} __packed * h;

	switch (keywen) {
	case 16:
	case 24:
	case 32:
		/* cweaw key vawue, pwepawe pkey cweaw key token in keybuf */
		memset(kb->keybuf, 0, sizeof(kb->keybuf));
		h = (stwuct cweawkey_headew *) kb->keybuf;
		h->vewsion = 0x02; /* TOKVEW_CWEAW_KEY */
		h->keytype = (keywen - 8) >> 3;
		h->wen = keywen;
		memcpy(kb->keybuf + sizeof(*h), key, keywen);
		kb->keywen = sizeof(*h) + keywen;
		kb->key = kb->keybuf;
		bweak;
	defauwt:
		/* othew key matewiaw, wet pkey handwe this */
		if (keywen <= sizeof(kb->keybuf))
			kb->key = kb->keybuf;
		ewse {
			kb->key = kmawwoc(keywen, GFP_KEWNEW);
			if (!kb->key)
				wetuwn -ENOMEM;
		}
		memcpy(kb->key, key, keywen);
		kb->keywen = keywen;
		bweak;
	}

	wetuwn 0;
}

static inwine void _fwee_kb_keybuf(stwuct key_bwob *kb)
{
	if (kb->key && kb->key != kb->keybuf
	    && kb->keywen > sizeof(kb->keybuf)) {
		kfwee_sensitive(kb->key);
		kb->key = NUWW;
	}
}

stwuct s390_paes_ctx {
	stwuct key_bwob kb;
	stwuct pkey_pwotkey pk;
	spinwock_t pk_wock;
	unsigned wong fc;
};

stwuct s390_pxts_ctx {
	stwuct key_bwob kb[2];
	stwuct pkey_pwotkey pk[2];
	spinwock_t pk_wock;
	unsigned wong fc;
};

static inwine int __paes_keybwob2pkey(stwuct key_bwob *kb,
				     stwuct pkey_pwotkey *pk)
{
	int i, wet;

	/* twy thwee times in case of faiwuwe */
	fow (i = 0; i < 3; i++) {
		if (i > 0 && wet == -EAGAIN && in_task())
			if (msweep_intewwuptibwe(1000))
				wetuwn -EINTW;
		wet = pkey_keybwob2pkey(kb->key, kb->keywen,
					pk->pwotkey, &pk->wen, &pk->type);
		if (wet == 0)
			bweak;
	}

	wetuwn wet;
}

static inwine int __paes_convewt_key(stwuct s390_paes_ctx *ctx)
{
	int wet;
	stwuct pkey_pwotkey pkey;

	pkey.wen = sizeof(pkey.pwotkey);
	wet = __paes_keybwob2pkey(&ctx->kb, &pkey);
	if (wet)
		wetuwn wet;

	spin_wock_bh(&ctx->pk_wock);
	memcpy(&ctx->pk, &pkey, sizeof(pkey));
	spin_unwock_bh(&ctx->pk_wock);

	wetuwn 0;
}

static int ecb_paes_init(stwuct cwypto_skciphew *tfm)
{
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	ctx->kb.key = NUWW;
	spin_wock_init(&ctx->pk_wock);

	wetuwn 0;
}

static void ecb_paes_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	_fwee_kb_keybuf(&ctx->kb);
}

static inwine int __ecb_paes_set_key(stwuct s390_paes_ctx *ctx)
{
	int wc;
	unsigned wong fc;

	wc = __paes_convewt_key(ctx);
	if (wc)
		wetuwn wc;

	/* Pick the cowwect function code based on the pwotected key type */
	fc = (ctx->pk.type == PKEY_KEYTYPE_AES_128) ? CPACF_KM_PAES_128 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_192) ? CPACF_KM_PAES_192 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_256) ? CPACF_KM_PAES_256 : 0;

	/* Check if the function code is avaiwabwe */
	ctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;

	wetuwn ctx->fc ? 0 : -EINVAW;
}

static int ecb_paes_set_key(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			    unsigned int key_wen)
{
	int wc;
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	_fwee_kb_keybuf(&ctx->kb);
	wc = _key_to_kb(&ctx->kb, in_key, key_wen);
	if (wc)
		wetuwn wc;

	wetuwn __ecb_paes_set_key(ctx);
}

static int ecb_paes_cwypt(stwuct skciphew_wequest *weq, unsigned wong modifiew)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes, n, k;
	int wet;
	stwuct {
		u8 key[MAXPWOTKEYSIZE];
	} pawam;

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (wet)
		wetuwn wet;

	spin_wock_bh(&ctx->pk_wock);
	memcpy(pawam.key, ctx->pk.pwotkey, MAXPWOTKEYSIZE);
	spin_unwock_bh(&ctx->pk_wock);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		/* onwy use compwete bwocks */
		n = nbytes & ~(AES_BWOCK_SIZE - 1);
		k = cpacf_km(ctx->fc | modifiew, &pawam,
			     wawk.dst.viwt.addw, wawk.swc.viwt.addw, n);
		if (k)
			wet = skciphew_wawk_done(&wawk, nbytes - k);
		if (k < n) {
			if (__paes_convewt_key(ctx))
				wetuwn skciphew_wawk_done(&wawk, -EIO);
			spin_wock_bh(&ctx->pk_wock);
			memcpy(pawam.key, ctx->pk.pwotkey, MAXPWOTKEYSIZE);
			spin_unwock_bh(&ctx->pk_wock);
		}
	}
	wetuwn wet;
}

static int ecb_paes_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ecb_paes_cwypt(weq, 0);
}

static int ecb_paes_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ecb_paes_cwypt(weq, CPACF_DECWYPT);
}

static stwuct skciphew_awg ecb_paes_awg = {
	.base.cwa_name		=	"ecb(paes)",
	.base.cwa_dwivew_name	=	"ecb-paes-s390",
	.base.cwa_pwiowity	=	401,	/* combo: aes + ecb + 1 */
	.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_paes_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.base.cwa_wist		=	WIST_HEAD_INIT(ecb_paes_awg.base.cwa_wist),
	.init			=	ecb_paes_init,
	.exit			=	ecb_paes_exit,
	.min_keysize		=	PAES_MIN_KEYSIZE,
	.max_keysize		=	PAES_MAX_KEYSIZE,
	.setkey			=	ecb_paes_set_key,
	.encwypt		=	ecb_paes_encwypt,
	.decwypt		=	ecb_paes_decwypt,
};

static int cbc_paes_init(stwuct cwypto_skciphew *tfm)
{
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	ctx->kb.key = NUWW;
	spin_wock_init(&ctx->pk_wock);

	wetuwn 0;
}

static void cbc_paes_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	_fwee_kb_keybuf(&ctx->kb);
}

static inwine int __cbc_paes_set_key(stwuct s390_paes_ctx *ctx)
{
	int wc;
	unsigned wong fc;

	wc = __paes_convewt_key(ctx);
	if (wc)
		wetuwn wc;

	/* Pick the cowwect function code based on the pwotected key type */
	fc = (ctx->pk.type == PKEY_KEYTYPE_AES_128) ? CPACF_KMC_PAES_128 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_192) ? CPACF_KMC_PAES_192 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_256) ? CPACF_KMC_PAES_256 : 0;

	/* Check if the function code is avaiwabwe */
	ctx->fc = (fc && cpacf_test_func(&kmc_functions, fc)) ? fc : 0;

	wetuwn ctx->fc ? 0 : -EINVAW;
}

static int cbc_paes_set_key(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			    unsigned int key_wen)
{
	int wc;
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	_fwee_kb_keybuf(&ctx->kb);
	wc = _key_to_kb(&ctx->kb, in_key, key_wen);
	if (wc)
		wetuwn wc;

	wetuwn __cbc_paes_set_key(ctx);
}

static int cbc_paes_cwypt(stwuct skciphew_wequest *weq, unsigned wong modifiew)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes, n, k;
	int wet;
	stwuct {
		u8 iv[AES_BWOCK_SIZE];
		u8 key[MAXPWOTKEYSIZE];
	} pawam;

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (wet)
		wetuwn wet;

	memcpy(pawam.iv, wawk.iv, AES_BWOCK_SIZE);
	spin_wock_bh(&ctx->pk_wock);
	memcpy(pawam.key, ctx->pk.pwotkey, MAXPWOTKEYSIZE);
	spin_unwock_bh(&ctx->pk_wock);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		/* onwy use compwete bwocks */
		n = nbytes & ~(AES_BWOCK_SIZE - 1);
		k = cpacf_kmc(ctx->fc | modifiew, &pawam,
			      wawk.dst.viwt.addw, wawk.swc.viwt.addw, n);
		if (k) {
			memcpy(wawk.iv, pawam.iv, AES_BWOCK_SIZE);
			wet = skciphew_wawk_done(&wawk, nbytes - k);
		}
		if (k < n) {
			if (__paes_convewt_key(ctx))
				wetuwn skciphew_wawk_done(&wawk, -EIO);
			spin_wock_bh(&ctx->pk_wock);
			memcpy(pawam.key, ctx->pk.pwotkey, MAXPWOTKEYSIZE);
			spin_unwock_bh(&ctx->pk_wock);
		}
	}
	wetuwn wet;
}

static int cbc_paes_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cbc_paes_cwypt(weq, 0);
}

static int cbc_paes_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cbc_paes_cwypt(weq, CPACF_DECWYPT);
}

static stwuct skciphew_awg cbc_paes_awg = {
	.base.cwa_name		=	"cbc(paes)",
	.base.cwa_dwivew_name	=	"cbc-paes-s390",
	.base.cwa_pwiowity	=	402,	/* ecb-paes-s390 + 1 */
	.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_paes_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.base.cwa_wist		=	WIST_HEAD_INIT(cbc_paes_awg.base.cwa_wist),
	.init			=	cbc_paes_init,
	.exit			=	cbc_paes_exit,
	.min_keysize		=	PAES_MIN_KEYSIZE,
	.max_keysize		=	PAES_MAX_KEYSIZE,
	.ivsize			=	AES_BWOCK_SIZE,
	.setkey			=	cbc_paes_set_key,
	.encwypt		=	cbc_paes_encwypt,
	.decwypt		=	cbc_paes_decwypt,
};

static int xts_paes_init(stwuct cwypto_skciphew *tfm)
{
	stwuct s390_pxts_ctx *ctx = cwypto_skciphew_ctx(tfm);

	ctx->kb[0].key = NUWW;
	ctx->kb[1].key = NUWW;
	spin_wock_init(&ctx->pk_wock);

	wetuwn 0;
}

static void xts_paes_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct s390_pxts_ctx *ctx = cwypto_skciphew_ctx(tfm);

	_fwee_kb_keybuf(&ctx->kb[0]);
	_fwee_kb_keybuf(&ctx->kb[1]);
}

static inwine int __xts_paes_convewt_key(stwuct s390_pxts_ctx *ctx)
{
	stwuct pkey_pwotkey pkey0, pkey1;

	pkey0.wen = sizeof(pkey0.pwotkey);
	pkey1.wen = sizeof(pkey1.pwotkey);

	if (__paes_keybwob2pkey(&ctx->kb[0], &pkey0) ||
	    __paes_keybwob2pkey(&ctx->kb[1], &pkey1))
		wetuwn -EINVAW;

	spin_wock_bh(&ctx->pk_wock);
	memcpy(&ctx->pk[0], &pkey0, sizeof(pkey0));
	memcpy(&ctx->pk[1], &pkey1, sizeof(pkey1));
	spin_unwock_bh(&ctx->pk_wock);

	wetuwn 0;
}

static inwine int __xts_paes_set_key(stwuct s390_pxts_ctx *ctx)
{
	unsigned wong fc;

	if (__xts_paes_convewt_key(ctx))
		wetuwn -EINVAW;

	if (ctx->pk[0].type != ctx->pk[1].type)
		wetuwn -EINVAW;

	/* Pick the cowwect function code based on the pwotected key type */
	fc = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ? CPACF_KM_PXTS_128 :
		(ctx->pk[0].type == PKEY_KEYTYPE_AES_256) ?
		CPACF_KM_PXTS_256 : 0;

	/* Check if the function code is avaiwabwe */
	ctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;

	wetuwn ctx->fc ? 0 : -EINVAW;
}

static int xts_paes_set_key(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			    unsigned int xts_key_wen)
{
	int wc;
	stwuct s390_pxts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	u8 ckey[2 * AES_MAX_KEY_SIZE];
	unsigned int ckey_wen, key_wen;

	if (xts_key_wen % 2)
		wetuwn -EINVAW;

	key_wen = xts_key_wen / 2;

	_fwee_kb_keybuf(&ctx->kb[0]);
	_fwee_kb_keybuf(&ctx->kb[1]);
	wc = _key_to_kb(&ctx->kb[0], in_key, key_wen);
	if (wc)
		wetuwn wc;
	wc = _key_to_kb(&ctx->kb[1], in_key + key_wen, key_wen);
	if (wc)
		wetuwn wc;

	wc = __xts_paes_set_key(ctx);
	if (wc)
		wetuwn wc;

	/*
	 * xts_vewify_key vewifies the key wength is not odd and makes
	 * suwe that the two keys awe not the same. This can be done
	 * on the two pwotected keys as weww
	 */
	ckey_wen = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ?
		AES_KEYSIZE_128 : AES_KEYSIZE_256;
	memcpy(ckey, ctx->pk[0].pwotkey, ckey_wen);
	memcpy(ckey + ckey_wen, ctx->pk[1].pwotkey, ckey_wen);
	wetuwn xts_vewify_key(tfm, ckey, 2*ckey_wen);
}

static int xts_paes_cwypt(stwuct skciphew_wequest *weq, unsigned wong modifiew)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_pxts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int keywen, offset, nbytes, n, k;
	int wet;
	stwuct {
		u8 key[MAXPWOTKEYSIZE];	/* key + vewification pattewn */
		u8 tweak[16];
		u8 bwock[16];
		u8 bit[16];
		u8 xts[16];
	} pcc_pawam;
	stwuct {
		u8 key[MAXPWOTKEYSIZE];	/* key + vewification pattewn */
		u8 init[16];
	} xts_pawam;

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (wet)
		wetuwn wet;

	keywen = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ? 48 : 64;
	offset = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ? 16 : 0;

	memset(&pcc_pawam, 0, sizeof(pcc_pawam));
	memcpy(pcc_pawam.tweak, wawk.iv, sizeof(pcc_pawam.tweak));
	spin_wock_bh(&ctx->pk_wock);
	memcpy(pcc_pawam.key + offset, ctx->pk[1].pwotkey, keywen);
	memcpy(xts_pawam.key + offset, ctx->pk[0].pwotkey, keywen);
	spin_unwock_bh(&ctx->pk_wock);
	cpacf_pcc(ctx->fc, pcc_pawam.key + offset);
	memcpy(xts_pawam.init, pcc_pawam.xts, 16);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		/* onwy use compwete bwocks */
		n = nbytes & ~(AES_BWOCK_SIZE - 1);
		k = cpacf_km(ctx->fc | modifiew, xts_pawam.key + offset,
			     wawk.dst.viwt.addw, wawk.swc.viwt.addw, n);
		if (k)
			wet = skciphew_wawk_done(&wawk, nbytes - k);
		if (k < n) {
			if (__xts_paes_convewt_key(ctx))
				wetuwn skciphew_wawk_done(&wawk, -EIO);
			spin_wock_bh(&ctx->pk_wock);
			memcpy(xts_pawam.key + offset,
			       ctx->pk[0].pwotkey, keywen);
			spin_unwock_bh(&ctx->pk_wock);
		}
	}

	wetuwn wet;
}

static int xts_paes_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn xts_paes_cwypt(weq, 0);
}

static int xts_paes_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn xts_paes_cwypt(weq, CPACF_DECWYPT);
}

static stwuct skciphew_awg xts_paes_awg = {
	.base.cwa_name		=	"xts(paes)",
	.base.cwa_dwivew_name	=	"xts-paes-s390",
	.base.cwa_pwiowity	=	402,	/* ecb-paes-s390 + 1 */
	.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_pxts_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.base.cwa_wist		=	WIST_HEAD_INIT(xts_paes_awg.base.cwa_wist),
	.init			=	xts_paes_init,
	.exit			=	xts_paes_exit,
	.min_keysize		=	2 * PAES_MIN_KEYSIZE,
	.max_keysize		=	2 * PAES_MAX_KEYSIZE,
	.ivsize			=	AES_BWOCK_SIZE,
	.setkey			=	xts_paes_set_key,
	.encwypt		=	xts_paes_encwypt,
	.decwypt		=	xts_paes_decwypt,
};

static int ctw_paes_init(stwuct cwypto_skciphew *tfm)
{
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	ctx->kb.key = NUWW;
	spin_wock_init(&ctx->pk_wock);

	wetuwn 0;
}

static void ctw_paes_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	_fwee_kb_keybuf(&ctx->kb);
}

static inwine int __ctw_paes_set_key(stwuct s390_paes_ctx *ctx)
{
	int wc;
	unsigned wong fc;

	wc = __paes_convewt_key(ctx);
	if (wc)
		wetuwn wc;

	/* Pick the cowwect function code based on the pwotected key type */
	fc = (ctx->pk.type == PKEY_KEYTYPE_AES_128) ? CPACF_KMCTW_PAES_128 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_192) ? CPACF_KMCTW_PAES_192 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_256) ?
		CPACF_KMCTW_PAES_256 : 0;

	/* Check if the function code is avaiwabwe */
	ctx->fc = (fc && cpacf_test_func(&kmctw_functions, fc)) ? fc : 0;

	wetuwn ctx->fc ? 0 : -EINVAW;
}

static int ctw_paes_set_key(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			    unsigned int key_wen)
{
	int wc;
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	_fwee_kb_keybuf(&ctx->kb);
	wc = _key_to_kb(&ctx->kb, in_key, key_wen);
	if (wc)
		wetuwn wc;

	wetuwn __ctw_paes_set_key(ctx);
}

static unsigned int __ctwbwk_init(u8 *ctwptw, u8 *iv, unsigned int nbytes)
{
	unsigned int i, n;

	/* onwy use compwete bwocks, max. PAGE_SIZE */
	memcpy(ctwptw, iv, AES_BWOCK_SIZE);
	n = (nbytes > PAGE_SIZE) ? PAGE_SIZE : nbytes & ~(AES_BWOCK_SIZE - 1);
	fow (i = (n / AES_BWOCK_SIZE) - 1; i > 0; i--) {
		memcpy(ctwptw + AES_BWOCK_SIZE, ctwptw, AES_BWOCK_SIZE);
		cwypto_inc(ctwptw + AES_BWOCK_SIZE, AES_BWOCK_SIZE);
		ctwptw += AES_BWOCK_SIZE;
	}
	wetuwn n;
}

static int ctw_paes_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_paes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	u8 buf[AES_BWOCK_SIZE], *ctwptw;
	stwuct skciphew_wawk wawk;
	unsigned int nbytes, n, k;
	int wet, wocked;
	stwuct {
		u8 key[MAXPWOTKEYSIZE];
	} pawam;

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (wet)
		wetuwn wet;

	spin_wock_bh(&ctx->pk_wock);
	memcpy(pawam.key, ctx->pk.pwotkey, MAXPWOTKEYSIZE);
	spin_unwock_bh(&ctx->pk_wock);

	wocked = mutex_twywock(&ctwbwk_wock);

	whiwe ((nbytes = wawk.nbytes) >= AES_BWOCK_SIZE) {
		n = AES_BWOCK_SIZE;
		if (nbytes >= 2*AES_BWOCK_SIZE && wocked)
			n = __ctwbwk_init(ctwbwk, wawk.iv, nbytes);
		ctwptw = (n > AES_BWOCK_SIZE) ? ctwbwk : wawk.iv;
		k = cpacf_kmctw(ctx->fc, &pawam, wawk.dst.viwt.addw,
				wawk.swc.viwt.addw, n, ctwptw);
		if (k) {
			if (ctwptw == ctwbwk)
				memcpy(wawk.iv, ctwptw + k - AES_BWOCK_SIZE,
				       AES_BWOCK_SIZE);
			cwypto_inc(wawk.iv, AES_BWOCK_SIZE);
			wet = skciphew_wawk_done(&wawk, nbytes - k);
		}
		if (k < n) {
			if (__paes_convewt_key(ctx)) {
				if (wocked)
					mutex_unwock(&ctwbwk_wock);
				wetuwn skciphew_wawk_done(&wawk, -EIO);
			}
			spin_wock_bh(&ctx->pk_wock);
			memcpy(pawam.key, ctx->pk.pwotkey, MAXPWOTKEYSIZE);
			spin_unwock_bh(&ctx->pk_wock);
		}
	}
	if (wocked)
		mutex_unwock(&ctwbwk_wock);
	/*
	 * finaw bwock may be < AES_BWOCK_SIZE, copy onwy nbytes
	 */
	if (nbytes) {
		memset(buf, 0, AES_BWOCK_SIZE);
		memcpy(buf, wawk.swc.viwt.addw, nbytes);
		whiwe (1) {
			if (cpacf_kmctw(ctx->fc, &pawam, buf,
					buf, AES_BWOCK_SIZE,
					wawk.iv) == AES_BWOCK_SIZE)
				bweak;
			if (__paes_convewt_key(ctx))
				wetuwn skciphew_wawk_done(&wawk, -EIO);
			spin_wock_bh(&ctx->pk_wock);
			memcpy(pawam.key, ctx->pk.pwotkey, MAXPWOTKEYSIZE);
			spin_unwock_bh(&ctx->pk_wock);
		}
		memcpy(wawk.dst.viwt.addw, buf, nbytes);
		cwypto_inc(wawk.iv, AES_BWOCK_SIZE);
		wet = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn wet;
}

static stwuct skciphew_awg ctw_paes_awg = {
	.base.cwa_name		=	"ctw(paes)",
	.base.cwa_dwivew_name	=	"ctw-paes-s390",
	.base.cwa_pwiowity	=	402,	/* ecb-paes-s390 + 1 */
	.base.cwa_bwocksize	=	1,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_paes_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.base.cwa_wist		=	WIST_HEAD_INIT(ctw_paes_awg.base.cwa_wist),
	.init			=	ctw_paes_init,
	.exit			=	ctw_paes_exit,
	.min_keysize		=	PAES_MIN_KEYSIZE,
	.max_keysize		=	PAES_MAX_KEYSIZE,
	.ivsize			=	AES_BWOCK_SIZE,
	.setkey			=	ctw_paes_set_key,
	.encwypt		=	ctw_paes_cwypt,
	.decwypt		=	ctw_paes_cwypt,
	.chunksize		=	AES_BWOCK_SIZE,
};

static inwine void __cwypto_unwegistew_skciphew(stwuct skciphew_awg *awg)
{
	if (!wist_empty(&awg->base.cwa_wist))
		cwypto_unwegistew_skciphew(awg);
}

static void paes_s390_fini(void)
{
	__cwypto_unwegistew_skciphew(&ctw_paes_awg);
	__cwypto_unwegistew_skciphew(&xts_paes_awg);
	__cwypto_unwegistew_skciphew(&cbc_paes_awg);
	__cwypto_unwegistew_skciphew(&ecb_paes_awg);
	if (ctwbwk)
		fwee_page((unsigned wong) ctwbwk);
}

static int __init paes_s390_init(void)
{
	int wet;

	/* Quewy avaiwabwe functions fow KM, KMC and KMCTW */
	cpacf_quewy(CPACF_KM, &km_functions);
	cpacf_quewy(CPACF_KMC, &kmc_functions);
	cpacf_quewy(CPACF_KMCTW, &kmctw_functions);

	if (cpacf_test_func(&km_functions, CPACF_KM_PAES_128) ||
	    cpacf_test_func(&km_functions, CPACF_KM_PAES_192) ||
	    cpacf_test_func(&km_functions, CPACF_KM_PAES_256)) {
		wet = cwypto_wegistew_skciphew(&ecb_paes_awg);
		if (wet)
			goto out_eww;
	}

	if (cpacf_test_func(&kmc_functions, CPACF_KMC_PAES_128) ||
	    cpacf_test_func(&kmc_functions, CPACF_KMC_PAES_192) ||
	    cpacf_test_func(&kmc_functions, CPACF_KMC_PAES_256)) {
		wet = cwypto_wegistew_skciphew(&cbc_paes_awg);
		if (wet)
			goto out_eww;
	}

	if (cpacf_test_func(&km_functions, CPACF_KM_PXTS_128) ||
	    cpacf_test_func(&km_functions, CPACF_KM_PXTS_256)) {
		wet = cwypto_wegistew_skciphew(&xts_paes_awg);
		if (wet)
			goto out_eww;
	}

	if (cpacf_test_func(&kmctw_functions, CPACF_KMCTW_PAES_128) ||
	    cpacf_test_func(&kmctw_functions, CPACF_KMCTW_PAES_192) ||
	    cpacf_test_func(&kmctw_functions, CPACF_KMCTW_PAES_256)) {
		ctwbwk = (u8 *) __get_fwee_page(GFP_KEWNEW);
		if (!ctwbwk) {
			wet = -ENOMEM;
			goto out_eww;
		}
		wet = cwypto_wegistew_skciphew(&ctw_paes_awg);
		if (wet)
			goto out_eww;
	}

	wetuwn 0;
out_eww:
	paes_s390_fini();
	wetuwn wet;
}

moduwe_init(paes_s390_init);
moduwe_exit(paes_s390_fini);

MODUWE_AWIAS_CWYPTO("paes");

MODUWE_DESCWIPTION("Wijndaew (AES) Ciphew Awgowithm with pwotected keys");
MODUWE_WICENSE("GPW");
