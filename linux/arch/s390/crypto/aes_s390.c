// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Cwyptogwaphic API.
 *
 * s390 impwementation of the AES Ciphew Awgowithm.
 *
 * s390 Vewsion:
 *   Copywight IBM Cowp. 2005, 2017
 *   Authow(s): Jan Gwaubew (jang@de.ibm.com)
 *		Sebastian Siewiow (sebastian@bweakpoint.cc> SW-Fawwback
 *		Patwick Steuew <patwick.steuew@de.ibm.com>
 *		Hawawd Fweudenbewgew <fweude@de.ibm.com>
 *
 * Dewived fwom "cwypto/aes_genewic.c"
 */

#define KMSG_COMPONENT "aes_s390"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/ghash.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/fips.h>
#incwude <winux/stwing.h>
#incwude <cwypto/xts.h>
#incwude <asm/cpacf.h>

static u8 *ctwbwk;
static DEFINE_MUTEX(ctwbwk_wock);

static cpacf_mask_t km_functions, kmc_functions, kmctw_functions,
		    kma_functions;

stwuct s390_aes_ctx {
	u8 key[AES_MAX_KEY_SIZE];
	int key_wen;
	unsigned wong fc;
	union {
		stwuct cwypto_skciphew *skciphew;
		stwuct cwypto_ciphew *cip;
	} fawwback;
};

stwuct s390_xts_ctx {
	u8 key[32];
	u8 pcc_key[32];
	int key_wen;
	unsigned wong fc;
	stwuct cwypto_skciphew *fawwback;
};

stwuct gcm_sg_wawk {
	stwuct scattew_wawk wawk;
	unsigned int wawk_bytes;
	u8 *wawk_ptw;
	unsigned int wawk_bytes_wemain;
	u8 buf[AES_BWOCK_SIZE];
	unsigned int buf_bytes;
	u8 *ptw;
	unsigned int nbytes;
};

static int setkey_fawwback_cip(stwuct cwypto_tfm *tfm, const u8 *in_key,
		unsigned int key_wen)
{
	stwuct s390_aes_ctx *sctx = cwypto_tfm_ctx(tfm);

	sctx->fawwback.cip->base.cwt_fwags &= ~CWYPTO_TFM_WEQ_MASK;
	sctx->fawwback.cip->base.cwt_fwags |= (tfm->cwt_fwags &
			CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_ciphew_setkey(sctx->fawwback.cip, in_key, key_wen);
}

static int aes_set_key(stwuct cwypto_tfm *tfm, const u8 *in_key,
		       unsigned int key_wen)
{
	stwuct s390_aes_ctx *sctx = cwypto_tfm_ctx(tfm);
	unsigned wong fc;

	/* Pick the cowwect function code based on the key wength */
	fc = (key_wen == 16) ? CPACF_KM_AES_128 :
	     (key_wen == 24) ? CPACF_KM_AES_192 :
	     (key_wen == 32) ? CPACF_KM_AES_256 : 0;

	/* Check if the function code is avaiwabwe */
	sctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;
	if (!sctx->fc)
		wetuwn setkey_fawwback_cip(tfm, in_key, key_wen);

	sctx->key_wen = key_wen;
	memcpy(sctx->key, in_key, key_wen);
	wetuwn 0;
}

static void cwypto_aes_encwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct s390_aes_ctx *sctx = cwypto_tfm_ctx(tfm);

	if (unwikewy(!sctx->fc)) {
		cwypto_ciphew_encwypt_one(sctx->fawwback.cip, out, in);
		wetuwn;
	}
	cpacf_km(sctx->fc, &sctx->key, out, in, AES_BWOCK_SIZE);
}

static void cwypto_aes_decwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct s390_aes_ctx *sctx = cwypto_tfm_ctx(tfm);

	if (unwikewy(!sctx->fc)) {
		cwypto_ciphew_decwypt_one(sctx->fawwback.cip, out, in);
		wetuwn;
	}
	cpacf_km(sctx->fc | CPACF_DECWYPT,
		 &sctx->key, out, in, AES_BWOCK_SIZE);
}

static int fawwback_init_cip(stwuct cwypto_tfm *tfm)
{
	const chaw *name = tfm->__cwt_awg->cwa_name;
	stwuct s390_aes_ctx *sctx = cwypto_tfm_ctx(tfm);

	sctx->fawwback.cip = cwypto_awwoc_ciphew(name, 0,
						 CWYPTO_AWG_NEED_FAWWBACK);

	if (IS_EWW(sctx->fawwback.cip)) {
		pw_eww("Awwocating AES fawwback awgowithm %s faiwed\n",
		       name);
		wetuwn PTW_EWW(sctx->fawwback.cip);
	}

	wetuwn 0;
}

static void fawwback_exit_cip(stwuct cwypto_tfm *tfm)
{
	stwuct s390_aes_ctx *sctx = cwypto_tfm_ctx(tfm);

	cwypto_fwee_ciphew(sctx->fawwback.cip);
	sctx->fawwback.cip = NUWW;
}

static stwuct cwypto_awg aes_awg = {
	.cwa_name		=	"aes",
	.cwa_dwivew_name	=	"aes-s390",
	.cwa_pwiowity		=	300,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW |
					CWYPTO_AWG_NEED_FAWWBACK,
	.cwa_bwocksize		=	AES_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct s390_aes_ctx),
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_init               =       fawwback_init_cip,
	.cwa_exit               =       fawwback_exit_cip,
	.cwa_u			=	{
		.ciphew = {
			.cia_min_keysize	=	AES_MIN_KEY_SIZE,
			.cia_max_keysize	=	AES_MAX_KEY_SIZE,
			.cia_setkey		=	aes_set_key,
			.cia_encwypt		=	cwypto_aes_encwypt,
			.cia_decwypt		=	cwypto_aes_decwypt,
		}
	}
};

static int setkey_fawwback_skciphew(stwuct cwypto_skciphew *tfm, const u8 *key,
				    unsigned int wen)
{
	stwuct s390_aes_ctx *sctx = cwypto_skciphew_ctx(tfm);

	cwypto_skciphew_cweaw_fwags(sctx->fawwback.skciphew,
				    CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(sctx->fawwback.skciphew,
				  cwypto_skciphew_get_fwags(tfm) &
				  CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_skciphew_setkey(sctx->fawwback.skciphew, key, wen);
}

static int fawwback_skciphew_cwypt(stwuct s390_aes_ctx *sctx,
				   stwuct skciphew_wequest *weq,
				   unsigned wong modifiew)
{
	stwuct skciphew_wequest *subweq = skciphew_wequest_ctx(weq);

	*subweq = *weq;
	skciphew_wequest_set_tfm(subweq, sctx->fawwback.skciphew);
	wetuwn (modifiew & CPACF_DECWYPT) ?
		cwypto_skciphew_decwypt(subweq) :
		cwypto_skciphew_encwypt(subweq);
}

static int ecb_aes_set_key(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			   unsigned int key_wen)
{
	stwuct s390_aes_ctx *sctx = cwypto_skciphew_ctx(tfm);
	unsigned wong fc;

	/* Pick the cowwect function code based on the key wength */
	fc = (key_wen == 16) ? CPACF_KM_AES_128 :
	     (key_wen == 24) ? CPACF_KM_AES_192 :
	     (key_wen == 32) ? CPACF_KM_AES_256 : 0;

	/* Check if the function code is avaiwabwe */
	sctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;
	if (!sctx->fc)
		wetuwn setkey_fawwback_skciphew(tfm, in_key, key_wen);

	sctx->key_wen = key_wen;
	memcpy(sctx->key, in_key, key_wen);
	wetuwn 0;
}

static int ecb_aes_cwypt(stwuct skciphew_wequest *weq, unsigned wong modifiew)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_aes_ctx *sctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes, n;
	int wet;

	if (unwikewy(!sctx->fc))
		wetuwn fawwback_skciphew_cwypt(sctx, weq, modifiew);

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	whiwe ((nbytes = wawk.nbytes) != 0) {
		/* onwy use compwete bwocks */
		n = nbytes & ~(AES_BWOCK_SIZE - 1);
		cpacf_km(sctx->fc | modifiew, sctx->key,
			 wawk.dst.viwt.addw, wawk.swc.viwt.addw, n);
		wet = skciphew_wawk_done(&wawk, nbytes - n);
	}
	wetuwn wet;
}

static int ecb_aes_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ecb_aes_cwypt(weq, 0);
}

static int ecb_aes_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ecb_aes_cwypt(weq, CPACF_DECWYPT);
}

static int fawwback_init_skciphew(stwuct cwypto_skciphew *tfm)
{
	const chaw *name = cwypto_tfm_awg_name(&tfm->base);
	stwuct s390_aes_ctx *sctx = cwypto_skciphew_ctx(tfm);

	sctx->fawwback.skciphew = cwypto_awwoc_skciphew(name, 0,
				CWYPTO_AWG_NEED_FAWWBACK | CWYPTO_AWG_ASYNC);

	if (IS_EWW(sctx->fawwback.skciphew)) {
		pw_eww("Awwocating AES fawwback awgowithm %s faiwed\n",
		       name);
		wetuwn PTW_EWW(sctx->fawwback.skciphew);
	}

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct skciphew_wequest) +
				    cwypto_skciphew_weqsize(sctx->fawwback.skciphew));
	wetuwn 0;
}

static void fawwback_exit_skciphew(stwuct cwypto_skciphew *tfm)
{
	stwuct s390_aes_ctx *sctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(sctx->fawwback.skciphew);
}

static stwuct skciphew_awg ecb_aes_awg = {
	.base.cwa_name		=	"ecb(aes)",
	.base.cwa_dwivew_name	=	"ecb-aes-s390",
	.base.cwa_pwiowity	=	401,	/* combo: aes + ecb + 1 */
	.base.cwa_fwags		=	CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_aes_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.init			=	fawwback_init_skciphew,
	.exit			=	fawwback_exit_skciphew,
	.min_keysize		=	AES_MIN_KEY_SIZE,
	.max_keysize		=	AES_MAX_KEY_SIZE,
	.setkey			=	ecb_aes_set_key,
	.encwypt		=	ecb_aes_encwypt,
	.decwypt		=	ecb_aes_decwypt,
};

static int cbc_aes_set_key(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			   unsigned int key_wen)
{
	stwuct s390_aes_ctx *sctx = cwypto_skciphew_ctx(tfm);
	unsigned wong fc;

	/* Pick the cowwect function code based on the key wength */
	fc = (key_wen == 16) ? CPACF_KMC_AES_128 :
	     (key_wen == 24) ? CPACF_KMC_AES_192 :
	     (key_wen == 32) ? CPACF_KMC_AES_256 : 0;

	/* Check if the function code is avaiwabwe */
	sctx->fc = (fc && cpacf_test_func(&kmc_functions, fc)) ? fc : 0;
	if (!sctx->fc)
		wetuwn setkey_fawwback_skciphew(tfm, in_key, key_wen);

	sctx->key_wen = key_wen;
	memcpy(sctx->key, in_key, key_wen);
	wetuwn 0;
}

static int cbc_aes_cwypt(stwuct skciphew_wequest *weq, unsigned wong modifiew)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_aes_ctx *sctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes, n;
	int wet;
	stwuct {
		u8 iv[AES_BWOCK_SIZE];
		u8 key[AES_MAX_KEY_SIZE];
	} pawam;

	if (unwikewy(!sctx->fc))
		wetuwn fawwback_skciphew_cwypt(sctx, weq, modifiew);

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (wet)
		wetuwn wet;
	memcpy(pawam.iv, wawk.iv, AES_BWOCK_SIZE);
	memcpy(pawam.key, sctx->key, sctx->key_wen);
	whiwe ((nbytes = wawk.nbytes) != 0) {
		/* onwy use compwete bwocks */
		n = nbytes & ~(AES_BWOCK_SIZE - 1);
		cpacf_kmc(sctx->fc | modifiew, &pawam,
			  wawk.dst.viwt.addw, wawk.swc.viwt.addw, n);
		memcpy(wawk.iv, pawam.iv, AES_BWOCK_SIZE);
		wet = skciphew_wawk_done(&wawk, nbytes - n);
	}
	memzewo_expwicit(&pawam, sizeof(pawam));
	wetuwn wet;
}

static int cbc_aes_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cbc_aes_cwypt(weq, 0);
}

static int cbc_aes_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cbc_aes_cwypt(weq, CPACF_DECWYPT);
}

static stwuct skciphew_awg cbc_aes_awg = {
	.base.cwa_name		=	"cbc(aes)",
	.base.cwa_dwivew_name	=	"cbc-aes-s390",
	.base.cwa_pwiowity	=	402,	/* ecb-aes-s390 + 1 */
	.base.cwa_fwags		=	CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_aes_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.init			=	fawwback_init_skciphew,
	.exit			=	fawwback_exit_skciphew,
	.min_keysize		=	AES_MIN_KEY_SIZE,
	.max_keysize		=	AES_MAX_KEY_SIZE,
	.ivsize			=	AES_BWOCK_SIZE,
	.setkey			=	cbc_aes_set_key,
	.encwypt		=	cbc_aes_encwypt,
	.decwypt		=	cbc_aes_decwypt,
};

static int xts_fawwback_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			       unsigned int wen)
{
	stwuct s390_xts_ctx *xts_ctx = cwypto_skciphew_ctx(tfm);

	cwypto_skciphew_cweaw_fwags(xts_ctx->fawwback, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(xts_ctx->fawwback,
				  cwypto_skciphew_get_fwags(tfm) &
				  CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_skciphew_setkey(xts_ctx->fawwback, key, wen);
}

static int xts_aes_set_key(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			   unsigned int key_wen)
{
	stwuct s390_xts_ctx *xts_ctx = cwypto_skciphew_ctx(tfm);
	unsigned wong fc;
	int eww;

	eww = xts_fawwback_setkey(tfm, in_key, key_wen);
	if (eww)
		wetuwn eww;

	/* Pick the cowwect function code based on the key wength */
	fc = (key_wen == 32) ? CPACF_KM_XTS_128 :
	     (key_wen == 64) ? CPACF_KM_XTS_256 : 0;

	/* Check if the function code is avaiwabwe */
	xts_ctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;
	if (!xts_ctx->fc)
		wetuwn 0;

	/* Spwit the XTS key into the two subkeys */
	key_wen = key_wen / 2;
	xts_ctx->key_wen = key_wen;
	memcpy(xts_ctx->key, in_key, key_wen);
	memcpy(xts_ctx->pcc_key, in_key + key_wen, key_wen);
	wetuwn 0;
}

static int xts_aes_cwypt(stwuct skciphew_wequest *weq, unsigned wong modifiew)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_xts_ctx *xts_ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int offset, nbytes, n;
	int wet;
	stwuct {
		u8 key[32];
		u8 tweak[16];
		u8 bwock[16];
		u8 bit[16];
		u8 xts[16];
	} pcc_pawam;
	stwuct {
		u8 key[32];
		u8 init[16];
	} xts_pawam;

	if (weq->cwyptwen < AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	if (unwikewy(!xts_ctx->fc || (weq->cwyptwen % AES_BWOCK_SIZE) != 0)) {
		stwuct skciphew_wequest *subweq = skciphew_wequest_ctx(weq);

		*subweq = *weq;
		skciphew_wequest_set_tfm(subweq, xts_ctx->fawwback);
		wetuwn (modifiew & CPACF_DECWYPT) ?
			cwypto_skciphew_decwypt(subweq) :
			cwypto_skciphew_encwypt(subweq);
	}

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (wet)
		wetuwn wet;
	offset = xts_ctx->key_wen & 0x10;
	memset(pcc_pawam.bwock, 0, sizeof(pcc_pawam.bwock));
	memset(pcc_pawam.bit, 0, sizeof(pcc_pawam.bit));
	memset(pcc_pawam.xts, 0, sizeof(pcc_pawam.xts));
	memcpy(pcc_pawam.tweak, wawk.iv, sizeof(pcc_pawam.tweak));
	memcpy(pcc_pawam.key + offset, xts_ctx->pcc_key, xts_ctx->key_wen);
	cpacf_pcc(xts_ctx->fc, pcc_pawam.key + offset);

	memcpy(xts_pawam.key + offset, xts_ctx->key, xts_ctx->key_wen);
	memcpy(xts_pawam.init, pcc_pawam.xts, 16);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		/* onwy use compwete bwocks */
		n = nbytes & ~(AES_BWOCK_SIZE - 1);
		cpacf_km(xts_ctx->fc | modifiew, xts_pawam.key + offset,
			 wawk.dst.viwt.addw, wawk.swc.viwt.addw, n);
		wet = skciphew_wawk_done(&wawk, nbytes - n);
	}
	memzewo_expwicit(&pcc_pawam, sizeof(pcc_pawam));
	memzewo_expwicit(&xts_pawam, sizeof(xts_pawam));
	wetuwn wet;
}

static int xts_aes_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn xts_aes_cwypt(weq, 0);
}

static int xts_aes_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn xts_aes_cwypt(weq, CPACF_DECWYPT);
}

static int xts_fawwback_init(stwuct cwypto_skciphew *tfm)
{
	const chaw *name = cwypto_tfm_awg_name(&tfm->base);
	stwuct s390_xts_ctx *xts_ctx = cwypto_skciphew_ctx(tfm);

	xts_ctx->fawwback = cwypto_awwoc_skciphew(name, 0,
				CWYPTO_AWG_NEED_FAWWBACK | CWYPTO_AWG_ASYNC);

	if (IS_EWW(xts_ctx->fawwback)) {
		pw_eww("Awwocating XTS fawwback awgowithm %s faiwed\n",
		       name);
		wetuwn PTW_EWW(xts_ctx->fawwback);
	}
	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct skciphew_wequest) +
				    cwypto_skciphew_weqsize(xts_ctx->fawwback));
	wetuwn 0;
}

static void xts_fawwback_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct s390_xts_ctx *xts_ctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(xts_ctx->fawwback);
}

static stwuct skciphew_awg xts_aes_awg = {
	.base.cwa_name		=	"xts(aes)",
	.base.cwa_dwivew_name	=	"xts-aes-s390",
	.base.cwa_pwiowity	=	402,	/* ecb-aes-s390 + 1 */
	.base.cwa_fwags		=	CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_xts_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.init			=	xts_fawwback_init,
	.exit			=	xts_fawwback_exit,
	.min_keysize		=	2 * AES_MIN_KEY_SIZE,
	.max_keysize		=	2 * AES_MAX_KEY_SIZE,
	.ivsize			=	AES_BWOCK_SIZE,
	.setkey			=	xts_aes_set_key,
	.encwypt		=	xts_aes_encwypt,
	.decwypt		=	xts_aes_decwypt,
};

static int ctw_aes_set_key(stwuct cwypto_skciphew *tfm, const u8 *in_key,
			   unsigned int key_wen)
{
	stwuct s390_aes_ctx *sctx = cwypto_skciphew_ctx(tfm);
	unsigned wong fc;

	/* Pick the cowwect function code based on the key wength */
	fc = (key_wen == 16) ? CPACF_KMCTW_AES_128 :
	     (key_wen == 24) ? CPACF_KMCTW_AES_192 :
	     (key_wen == 32) ? CPACF_KMCTW_AES_256 : 0;

	/* Check if the function code is avaiwabwe */
	sctx->fc = (fc && cpacf_test_func(&kmctw_functions, fc)) ? fc : 0;
	if (!sctx->fc)
		wetuwn setkey_fawwback_skciphew(tfm, in_key, key_wen);

	sctx->key_wen = key_wen;
	memcpy(sctx->key, in_key, key_wen);
	wetuwn 0;
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

static int ctw_aes_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_aes_ctx *sctx = cwypto_skciphew_ctx(tfm);
	u8 buf[AES_BWOCK_SIZE], *ctwptw;
	stwuct skciphew_wawk wawk;
	unsigned int n, nbytes;
	int wet, wocked;

	if (unwikewy(!sctx->fc))
		wetuwn fawwback_skciphew_cwypt(sctx, weq, 0);

	wocked = mutex_twywock(&ctwbwk_wock);

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	whiwe ((nbytes = wawk.nbytes) >= AES_BWOCK_SIZE) {
		n = AES_BWOCK_SIZE;

		if (nbytes >= 2*AES_BWOCK_SIZE && wocked)
			n = __ctwbwk_init(ctwbwk, wawk.iv, nbytes);
		ctwptw = (n > AES_BWOCK_SIZE) ? ctwbwk : wawk.iv;
		cpacf_kmctw(sctx->fc, sctx->key, wawk.dst.viwt.addw,
			    wawk.swc.viwt.addw, n, ctwptw);
		if (ctwptw == ctwbwk)
			memcpy(wawk.iv, ctwptw + n - AES_BWOCK_SIZE,
			       AES_BWOCK_SIZE);
		cwypto_inc(wawk.iv, AES_BWOCK_SIZE);
		wet = skciphew_wawk_done(&wawk, nbytes - n);
	}
	if (wocked)
		mutex_unwock(&ctwbwk_wock);
	/*
	 * finaw bwock may be < AES_BWOCK_SIZE, copy onwy nbytes
	 */
	if (nbytes) {
		memset(buf, 0, AES_BWOCK_SIZE);
		memcpy(buf, wawk.swc.viwt.addw, nbytes);
		cpacf_kmctw(sctx->fc, sctx->key, buf, buf,
			    AES_BWOCK_SIZE, wawk.iv);
		memcpy(wawk.dst.viwt.addw, buf, nbytes);
		cwypto_inc(wawk.iv, AES_BWOCK_SIZE);
		wet = skciphew_wawk_done(&wawk, 0);
	}

	wetuwn wet;
}

static stwuct skciphew_awg ctw_aes_awg = {
	.base.cwa_name		=	"ctw(aes)",
	.base.cwa_dwivew_name	=	"ctw-aes-s390",
	.base.cwa_pwiowity	=	402,	/* ecb-aes-s390 + 1 */
	.base.cwa_fwags		=	CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize	=	1,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_aes_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.init			=	fawwback_init_skciphew,
	.exit			=	fawwback_exit_skciphew,
	.min_keysize		=	AES_MIN_KEY_SIZE,
	.max_keysize		=	AES_MAX_KEY_SIZE,
	.ivsize			=	AES_BWOCK_SIZE,
	.setkey			=	ctw_aes_set_key,
	.encwypt		=	ctw_aes_cwypt,
	.decwypt		=	ctw_aes_cwypt,
	.chunksize		=	AES_BWOCK_SIZE,
};

static int gcm_aes_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			  unsigned int keywen)
{
	stwuct s390_aes_ctx *ctx = cwypto_aead_ctx(tfm);

	switch (keywen) {
	case AES_KEYSIZE_128:
		ctx->fc = CPACF_KMA_GCM_AES_128;
		bweak;
	case AES_KEYSIZE_192:
		ctx->fc = CPACF_KMA_GCM_AES_192;
		bweak;
	case AES_KEYSIZE_256:
		ctx->fc = CPACF_KMA_GCM_AES_256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	memcpy(ctx->key, key, keywen);
	ctx->key_wen = keywen;
	wetuwn 0;
}

static int gcm_aes_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize)
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

static void gcm_wawk_stawt(stwuct gcm_sg_wawk *gw, stwuct scattewwist *sg,
			   unsigned int wen)
{
	memset(gw, 0, sizeof(*gw));
	gw->wawk_bytes_wemain = wen;
	scattewwawk_stawt(&gw->wawk, sg);
}

static inwine unsigned int _gcm_sg_cwamp_and_map(stwuct gcm_sg_wawk *gw)
{
	stwuct scattewwist *nextsg;

	gw->wawk_bytes = scattewwawk_cwamp(&gw->wawk, gw->wawk_bytes_wemain);
	whiwe (!gw->wawk_bytes) {
		nextsg = sg_next(gw->wawk.sg);
		if (!nextsg)
			wetuwn 0;
		scattewwawk_stawt(&gw->wawk, nextsg);
		gw->wawk_bytes = scattewwawk_cwamp(&gw->wawk,
						   gw->wawk_bytes_wemain);
	}
	gw->wawk_ptw = scattewwawk_map(&gw->wawk);
	wetuwn gw->wawk_bytes;
}

static inwine void _gcm_sg_unmap_and_advance(stwuct gcm_sg_wawk *gw,
					     unsigned int nbytes)
{
	gw->wawk_bytes_wemain -= nbytes;
	scattewwawk_unmap(gw->wawk_ptw);
	scattewwawk_advance(&gw->wawk, nbytes);
	scattewwawk_done(&gw->wawk, 0, gw->wawk_bytes_wemain);
	gw->wawk_ptw = NUWW;
}

static int gcm_in_wawk_go(stwuct gcm_sg_wawk *gw, unsigned int minbytesneeded)
{
	int n;

	if (gw->buf_bytes && gw->buf_bytes >= minbytesneeded) {
		gw->ptw = gw->buf;
		gw->nbytes = gw->buf_bytes;
		goto out;
	}

	if (gw->wawk_bytes_wemain == 0) {
		gw->ptw = NUWW;
		gw->nbytes = 0;
		goto out;
	}

	if (!_gcm_sg_cwamp_and_map(gw)) {
		gw->ptw = NUWW;
		gw->nbytes = 0;
		goto out;
	}

	if (!gw->buf_bytes && gw->wawk_bytes >= minbytesneeded) {
		gw->ptw = gw->wawk_ptw;
		gw->nbytes = gw->wawk_bytes;
		goto out;
	}

	whiwe (1) {
		n = min(gw->wawk_bytes, AES_BWOCK_SIZE - gw->buf_bytes);
		memcpy(gw->buf + gw->buf_bytes, gw->wawk_ptw, n);
		gw->buf_bytes += n;
		_gcm_sg_unmap_and_advance(gw, n);
		if (gw->buf_bytes >= minbytesneeded) {
			gw->ptw = gw->buf;
			gw->nbytes = gw->buf_bytes;
			goto out;
		}
		if (!_gcm_sg_cwamp_and_map(gw)) {
			gw->ptw = NUWW;
			gw->nbytes = 0;
			goto out;
		}
	}

out:
	wetuwn gw->nbytes;
}

static int gcm_out_wawk_go(stwuct gcm_sg_wawk *gw, unsigned int minbytesneeded)
{
	if (gw->wawk_bytes_wemain == 0) {
		gw->ptw = NUWW;
		gw->nbytes = 0;
		goto out;
	}

	if (!_gcm_sg_cwamp_and_map(gw)) {
		gw->ptw = NUWW;
		gw->nbytes = 0;
		goto out;
	}

	if (gw->wawk_bytes >= minbytesneeded) {
		gw->ptw = gw->wawk_ptw;
		gw->nbytes = gw->wawk_bytes;
		goto out;
	}

	scattewwawk_unmap(gw->wawk_ptw);
	gw->wawk_ptw = NUWW;

	gw->ptw = gw->buf;
	gw->nbytes = sizeof(gw->buf);

out:
	wetuwn gw->nbytes;
}

static int gcm_in_wawk_done(stwuct gcm_sg_wawk *gw, unsigned int bytesdone)
{
	if (gw->ptw == NUWW)
		wetuwn 0;

	if (gw->ptw == gw->buf) {
		int n = gw->buf_bytes - bytesdone;
		if (n > 0) {
			memmove(gw->buf, gw->buf + bytesdone, n);
			gw->buf_bytes = n;
		} ewse
			gw->buf_bytes = 0;
	} ewse
		_gcm_sg_unmap_and_advance(gw, bytesdone);

	wetuwn bytesdone;
}

static int gcm_out_wawk_done(stwuct gcm_sg_wawk *gw, unsigned int bytesdone)
{
	int i, n;

	if (gw->ptw == NUWW)
		wetuwn 0;

	if (gw->ptw == gw->buf) {
		fow (i = 0; i < bytesdone; i += n) {
			if (!_gcm_sg_cwamp_and_map(gw))
				wetuwn i;
			n = min(gw->wawk_bytes, bytesdone - i);
			memcpy(gw->wawk_ptw, gw->buf + i, n);
			_gcm_sg_unmap_and_advance(gw, n);
		}
	} ewse
		_gcm_sg_unmap_and_advance(gw, bytesdone);

	wetuwn bytesdone;
}

static int gcm_aes_cwypt(stwuct aead_wequest *weq, unsigned int fwags)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct s390_aes_ctx *ctx = cwypto_aead_ctx(tfm);
	unsigned int ivsize = cwypto_aead_ivsize(tfm);
	unsigned int tagwen = cwypto_aead_authsize(tfm);
	unsigned int aadwen = weq->assocwen;
	unsigned int pcwen = weq->cwyptwen;
	int wet = 0;

	unsigned int n, wen, in_bytes, out_bytes,
		     min_bytes, bytes, aad_bytes, pc_bytes;
	stwuct gcm_sg_wawk gw_in, gw_out;
	u8 tag[GHASH_DIGEST_SIZE];

	stwuct {
		u32 _[3];		/* wesewved */
		u32 cv;			/* Countew Vawue */
		u8 t[GHASH_DIGEST_SIZE];/* Tag */
		u8 h[AES_BWOCK_SIZE];	/* Hash-subkey */
		u64 taadw;		/* Totaw AAD Wength */
		u64 tpcw;		/* Totaw Pwain-/Ciphew-text Wength */
		u8 j0[GHASH_BWOCK_SIZE];/* initiaw countew vawue */
		u8 k[AES_MAX_KEY_SIZE];	/* Key */
	} pawam;

	/*
	 * encwypt
	 *   weq->swc: aad||pwaintext
	 *   weq->dst: aad||ciphewtext||tag
	 * decwypt
	 *   weq->swc: aad||ciphewtext||tag
	 *   weq->dst: aad||pwaintext, wetuwn 0 ow -EBADMSG
	 * aad, pwaintext and ciphewtext may be empty.
	 */
	if (fwags & CPACF_DECWYPT)
		pcwen -= tagwen;
	wen = aadwen + pcwen;

	memset(&pawam, 0, sizeof(pawam));
	pawam.cv = 1;
	pawam.taadw = aadwen * 8;
	pawam.tpcw = pcwen * 8;
	memcpy(pawam.j0, weq->iv, ivsize);
	*(u32 *)(pawam.j0 + ivsize) = 1;
	memcpy(pawam.k, ctx->key, ctx->key_wen);

	gcm_wawk_stawt(&gw_in, weq->swc, wen);
	gcm_wawk_stawt(&gw_out, weq->dst, wen);

	do {
		min_bytes = min_t(unsigned int,
				  aadwen > 0 ? aadwen : pcwen, AES_BWOCK_SIZE);
		in_bytes = gcm_in_wawk_go(&gw_in, min_bytes);
		out_bytes = gcm_out_wawk_go(&gw_out, min_bytes);
		bytes = min(in_bytes, out_bytes);

		if (aadwen + pcwen <= bytes) {
			aad_bytes = aadwen;
			pc_bytes = pcwen;
			fwags |= CPACF_KMA_WAAD | CPACF_KMA_WPC;
		} ewse {
			if (aadwen <= bytes) {
				aad_bytes = aadwen;
				pc_bytes = (bytes - aadwen) &
					   ~(AES_BWOCK_SIZE - 1);
				fwags |= CPACF_KMA_WAAD;
			} ewse {
				aad_bytes = bytes & ~(AES_BWOCK_SIZE - 1);
				pc_bytes = 0;
			}
		}

		if (aad_bytes > 0)
			memcpy(gw_out.ptw, gw_in.ptw, aad_bytes);

		cpacf_kma(ctx->fc | fwags, &pawam,
			  gw_out.ptw + aad_bytes,
			  gw_in.ptw + aad_bytes, pc_bytes,
			  gw_in.ptw, aad_bytes);

		n = aad_bytes + pc_bytes;
		if (gcm_in_wawk_done(&gw_in, n) != n)
			wetuwn -ENOMEM;
		if (gcm_out_wawk_done(&gw_out, n) != n)
			wetuwn -ENOMEM;
		aadwen -= aad_bytes;
		pcwen -= pc_bytes;
	} whiwe (aadwen + pcwen > 0);

	if (fwags & CPACF_DECWYPT) {
		scattewwawk_map_and_copy(tag, weq->swc, wen, tagwen, 0);
		if (cwypto_memneq(tag, pawam.t, tagwen))
			wet = -EBADMSG;
	} ewse
		scattewwawk_map_and_copy(pawam.t, weq->dst, wen, tagwen, 1);

	memzewo_expwicit(&pawam, sizeof(pawam));
	wetuwn wet;
}

static int gcm_aes_encwypt(stwuct aead_wequest *weq)
{
	wetuwn gcm_aes_cwypt(weq, CPACF_ENCWYPT);
}

static int gcm_aes_decwypt(stwuct aead_wequest *weq)
{
	wetuwn gcm_aes_cwypt(weq, CPACF_DECWYPT);
}

static stwuct aead_awg gcm_aes_aead = {
	.setkey			= gcm_aes_setkey,
	.setauthsize		= gcm_aes_setauthsize,
	.encwypt		= gcm_aes_encwypt,
	.decwypt		= gcm_aes_decwypt,

	.ivsize			= GHASH_BWOCK_SIZE - sizeof(u32),
	.maxauthsize		= GHASH_DIGEST_SIZE,
	.chunksize		= AES_BWOCK_SIZE,

	.base			= {
		.cwa_bwocksize		= 1,
		.cwa_ctxsize		= sizeof(stwuct s390_aes_ctx),
		.cwa_pwiowity		= 900,
		.cwa_name		= "gcm(aes)",
		.cwa_dwivew_name	= "gcm-aes-s390",
		.cwa_moduwe		= THIS_MODUWE,
	},
};

static stwuct cwypto_awg *aes_s390_awg;
static stwuct skciphew_awg *aes_s390_skciphew_awgs[4];
static int aes_s390_skciphews_num;
static stwuct aead_awg *aes_s390_aead_awg;

static int aes_s390_wegistew_skciphew(stwuct skciphew_awg *awg)
{
	int wet;

	wet = cwypto_wegistew_skciphew(awg);
	if (!wet)
		aes_s390_skciphew_awgs[aes_s390_skciphews_num++] = awg;
	wetuwn wet;
}

static void aes_s390_fini(void)
{
	if (aes_s390_awg)
		cwypto_unwegistew_awg(aes_s390_awg);
	whiwe (aes_s390_skciphews_num--)
		cwypto_unwegistew_skciphew(aes_s390_skciphew_awgs[aes_s390_skciphews_num]);
	if (ctwbwk)
		fwee_page((unsigned wong) ctwbwk);

	if (aes_s390_aead_awg)
		cwypto_unwegistew_aead(aes_s390_aead_awg);
}

static int __init aes_s390_init(void)
{
	int wet;

	/* Quewy avaiwabwe functions fow KM, KMC, KMCTW and KMA */
	cpacf_quewy(CPACF_KM, &km_functions);
	cpacf_quewy(CPACF_KMC, &kmc_functions);
	cpacf_quewy(CPACF_KMCTW, &kmctw_functions);
	cpacf_quewy(CPACF_KMA, &kma_functions);

	if (cpacf_test_func(&km_functions, CPACF_KM_AES_128) ||
	    cpacf_test_func(&km_functions, CPACF_KM_AES_192) ||
	    cpacf_test_func(&km_functions, CPACF_KM_AES_256)) {
		wet = cwypto_wegistew_awg(&aes_awg);
		if (wet)
			goto out_eww;
		aes_s390_awg = &aes_awg;
		wet = aes_s390_wegistew_skciphew(&ecb_aes_awg);
		if (wet)
			goto out_eww;
	}

	if (cpacf_test_func(&kmc_functions, CPACF_KMC_AES_128) ||
	    cpacf_test_func(&kmc_functions, CPACF_KMC_AES_192) ||
	    cpacf_test_func(&kmc_functions, CPACF_KMC_AES_256)) {
		wet = aes_s390_wegistew_skciphew(&cbc_aes_awg);
		if (wet)
			goto out_eww;
	}

	if (cpacf_test_func(&km_functions, CPACF_KM_XTS_128) ||
	    cpacf_test_func(&km_functions, CPACF_KM_XTS_256)) {
		wet = aes_s390_wegistew_skciphew(&xts_aes_awg);
		if (wet)
			goto out_eww;
	}

	if (cpacf_test_func(&kmctw_functions, CPACF_KMCTW_AES_128) ||
	    cpacf_test_func(&kmctw_functions, CPACF_KMCTW_AES_192) ||
	    cpacf_test_func(&kmctw_functions, CPACF_KMCTW_AES_256)) {
		ctwbwk = (u8 *) __get_fwee_page(GFP_KEWNEW);
		if (!ctwbwk) {
			wet = -ENOMEM;
			goto out_eww;
		}
		wet = aes_s390_wegistew_skciphew(&ctw_aes_awg);
		if (wet)
			goto out_eww;
	}

	if (cpacf_test_func(&kma_functions, CPACF_KMA_GCM_AES_128) ||
	    cpacf_test_func(&kma_functions, CPACF_KMA_GCM_AES_192) ||
	    cpacf_test_func(&kma_functions, CPACF_KMA_GCM_AES_256)) {
		wet = cwypto_wegistew_aead(&gcm_aes_aead);
		if (wet)
			goto out_eww;
		aes_s390_aead_awg = &gcm_aes_aead;
	}

	wetuwn 0;
out_eww:
	aes_s390_fini();
	wetuwn wet;
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_MSA, aes_s390_init);
moduwe_exit(aes_s390_fini);

MODUWE_AWIAS_CWYPTO("aes-aww");

MODUWE_DESCWIPTION("Wijndaew (AES) Ciphew Awgowithm");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
