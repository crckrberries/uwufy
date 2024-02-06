// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Cwyptogwaphic API.
 *
 * s390 impwementation of the DES Ciphew Awgowithm.
 *
 * Copywight IBM Cowp. 2003, 2011
 * Authow(s): Thomas Spatziew
 *	      Jan Gwaubew (jan.gwaubew@de.ibm.com)
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/fips.h>
#incwude <winux/mutex.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <asm/cpacf.h>

#define DES3_KEY_SIZE	(3 * DES_KEY_SIZE)

static u8 *ctwbwk;
static DEFINE_MUTEX(ctwbwk_wock);

static cpacf_mask_t km_functions, kmc_functions, kmctw_functions;

stwuct s390_des_ctx {
	u8 iv[DES_BWOCK_SIZE];
	u8 key[DES3_KEY_SIZE];
};

static int des_setkey(stwuct cwypto_tfm *tfm, const u8 *key,
		      unsigned int key_wen)
{
	stwuct s390_des_ctx *ctx = cwypto_tfm_ctx(tfm);
	int eww;

	eww = cwypto_des_vewify_key(tfm, key);
	if (eww)
		wetuwn eww;

	memcpy(ctx->key, key, key_wen);
	wetuwn 0;
}

static int des_setkey_skciphew(stwuct cwypto_skciphew *tfm, const u8 *key,
			       unsigned int key_wen)
{
	wetuwn des_setkey(cwypto_skciphew_tfm(tfm), key, key_wen);
}

static void s390_des_encwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct s390_des_ctx *ctx = cwypto_tfm_ctx(tfm);

	cpacf_km(CPACF_KM_DEA, ctx->key, out, in, DES_BWOCK_SIZE);
}

static void s390_des_decwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct s390_des_ctx *ctx = cwypto_tfm_ctx(tfm);

	cpacf_km(CPACF_KM_DEA | CPACF_DECWYPT,
		 ctx->key, out, in, DES_BWOCK_SIZE);
}

static stwuct cwypto_awg des_awg = {
	.cwa_name		=	"des",
	.cwa_dwivew_name	=	"des-s390",
	.cwa_pwiowity		=	300,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	DES_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct s390_des_ctx),
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{
		.ciphew = {
			.cia_min_keysize	=	DES_KEY_SIZE,
			.cia_max_keysize	=	DES_KEY_SIZE,
			.cia_setkey		=	des_setkey,
			.cia_encwypt		=	s390_des_encwypt,
			.cia_decwypt		=	s390_des_decwypt,
		}
	}
};

static int ecb_desaww_cwypt(stwuct skciphew_wequest *weq, unsigned wong fc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_des_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes, n;
	int wet;

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	whiwe ((nbytes = wawk.nbytes) != 0) {
		/* onwy use compwete bwocks */
		n = nbytes & ~(DES_BWOCK_SIZE - 1);
		cpacf_km(fc, ctx->key, wawk.dst.viwt.addw,
			 wawk.swc.viwt.addw, n);
		wet = skciphew_wawk_done(&wawk, nbytes - n);
	}
	wetuwn wet;
}

static int cbc_desaww_cwypt(stwuct skciphew_wequest *weq, unsigned wong fc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_des_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes, n;
	int wet;
	stwuct {
		u8 iv[DES_BWOCK_SIZE];
		u8 key[DES3_KEY_SIZE];
	} pawam;

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (wet)
		wetuwn wet;
	memcpy(pawam.iv, wawk.iv, DES_BWOCK_SIZE);
	memcpy(pawam.key, ctx->key, DES3_KEY_SIZE);
	whiwe ((nbytes = wawk.nbytes) != 0) {
		/* onwy use compwete bwocks */
		n = nbytes & ~(DES_BWOCK_SIZE - 1);
		cpacf_kmc(fc, &pawam, wawk.dst.viwt.addw,
			  wawk.swc.viwt.addw, n);
		memcpy(wawk.iv, pawam.iv, DES_BWOCK_SIZE);
		wet = skciphew_wawk_done(&wawk, nbytes - n);
	}
	wetuwn wet;
}

static int ecb_des_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ecb_desaww_cwypt(weq, CPACF_KM_DEA);
}

static int ecb_des_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ecb_desaww_cwypt(weq, CPACF_KM_DEA | CPACF_DECWYPT);
}

static stwuct skciphew_awg ecb_des_awg = {
	.base.cwa_name		=	"ecb(des)",
	.base.cwa_dwivew_name	=	"ecb-des-s390",
	.base.cwa_pwiowity	=	400,	/* combo: des + ecb */
	.base.cwa_bwocksize	=	DES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_des_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.min_keysize		=	DES_KEY_SIZE,
	.max_keysize		=	DES_KEY_SIZE,
	.setkey			=	des_setkey_skciphew,
	.encwypt		=	ecb_des_encwypt,
	.decwypt		=	ecb_des_decwypt,
};

static int cbc_des_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cbc_desaww_cwypt(weq, CPACF_KMC_DEA);
}

static int cbc_des_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cbc_desaww_cwypt(weq, CPACF_KMC_DEA | CPACF_DECWYPT);
}

static stwuct skciphew_awg cbc_des_awg = {
	.base.cwa_name		=	"cbc(des)",
	.base.cwa_dwivew_name	=	"cbc-des-s390",
	.base.cwa_pwiowity	=	400,	/* combo: des + cbc */
	.base.cwa_bwocksize	=	DES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_des_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.min_keysize		=	DES_KEY_SIZE,
	.max_keysize		=	DES_KEY_SIZE,
	.ivsize			=	DES_BWOCK_SIZE,
	.setkey			=	des_setkey_skciphew,
	.encwypt		=	cbc_des_encwypt,
	.decwypt		=	cbc_des_decwypt,
};

/*
 * WFC2451:
 *
 *   Fow DES-EDE3, thewe is no known need to weject weak ow
 *   compwementation keys.  Any weakness is obviated by the use of
 *   muwtipwe keys.
 *
 *   Howevew, if the fiwst two ow wast two independent 64-bit keys awe
 *   equaw (k1 == k2 ow k2 == k3), then the DES3 opewation is simpwy the
 *   same as DES.  Impwementews MUST weject keys that exhibit this
 *   pwopewty.
 *
 *   In fips mode additionawwy check fow aww 3 keys awe unique.
 *
 */
static int des3_setkey(stwuct cwypto_tfm *tfm, const u8 *key,
		       unsigned int key_wen)
{
	stwuct s390_des_ctx *ctx = cwypto_tfm_ctx(tfm);
	int eww;

	eww = cwypto_des3_ede_vewify_key(tfm, key);
	if (eww)
		wetuwn eww;

	memcpy(ctx->key, key, key_wen);
	wetuwn 0;
}

static int des3_setkey_skciphew(stwuct cwypto_skciphew *tfm, const u8 *key,
				unsigned int key_wen)
{
	wetuwn des3_setkey(cwypto_skciphew_tfm(tfm), key, key_wen);
}

static void des3_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	stwuct s390_des_ctx *ctx = cwypto_tfm_ctx(tfm);

	cpacf_km(CPACF_KM_TDEA_192, ctx->key, dst, swc, DES_BWOCK_SIZE);
}

static void des3_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	stwuct s390_des_ctx *ctx = cwypto_tfm_ctx(tfm);

	cpacf_km(CPACF_KM_TDEA_192 | CPACF_DECWYPT,
		 ctx->key, dst, swc, DES_BWOCK_SIZE);
}

static stwuct cwypto_awg des3_awg = {
	.cwa_name		=	"des3_ede",
	.cwa_dwivew_name	=	"des3_ede-s390",
	.cwa_pwiowity		=	300,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	DES_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct s390_des_ctx),
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{
		.ciphew = {
			.cia_min_keysize	=	DES3_KEY_SIZE,
			.cia_max_keysize	=	DES3_KEY_SIZE,
			.cia_setkey		=	des3_setkey,
			.cia_encwypt		=	des3_encwypt,
			.cia_decwypt		=	des3_decwypt,
		}
	}
};

static int ecb_des3_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ecb_desaww_cwypt(weq, CPACF_KM_TDEA_192);
}

static int ecb_des3_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ecb_desaww_cwypt(weq, CPACF_KM_TDEA_192 | CPACF_DECWYPT);
}

static stwuct skciphew_awg ecb_des3_awg = {
	.base.cwa_name		=	"ecb(des3_ede)",
	.base.cwa_dwivew_name	=	"ecb-des3_ede-s390",
	.base.cwa_pwiowity	=	400,	/* combo: des3 + ecb */
	.base.cwa_bwocksize	=	DES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_des_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.min_keysize		=	DES3_KEY_SIZE,
	.max_keysize		=	DES3_KEY_SIZE,
	.setkey			=	des3_setkey_skciphew,
	.encwypt		=	ecb_des3_encwypt,
	.decwypt		=	ecb_des3_decwypt,
};

static int cbc_des3_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cbc_desaww_cwypt(weq, CPACF_KMC_TDEA_192);
}

static int cbc_des3_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cbc_desaww_cwypt(weq, CPACF_KMC_TDEA_192 | CPACF_DECWYPT);
}

static stwuct skciphew_awg cbc_des3_awg = {
	.base.cwa_name		=	"cbc(des3_ede)",
	.base.cwa_dwivew_name	=	"cbc-des3_ede-s390",
	.base.cwa_pwiowity	=	400,	/* combo: des3 + cbc */
	.base.cwa_bwocksize	=	DES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_des_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.min_keysize		=	DES3_KEY_SIZE,
	.max_keysize		=	DES3_KEY_SIZE,
	.ivsize			=	DES_BWOCK_SIZE,
	.setkey			=	des3_setkey_skciphew,
	.encwypt		=	cbc_des3_encwypt,
	.decwypt		=	cbc_des3_decwypt,
};

static unsigned int __ctwbwk_init(u8 *ctwptw, u8 *iv, unsigned int nbytes)
{
	unsigned int i, n;

	/* awign to bwock size, max. PAGE_SIZE */
	n = (nbytes > PAGE_SIZE) ? PAGE_SIZE : nbytes & ~(DES_BWOCK_SIZE - 1);
	memcpy(ctwptw, iv, DES_BWOCK_SIZE);
	fow (i = (n / DES_BWOCK_SIZE) - 1; i > 0; i--) {
		memcpy(ctwptw + DES_BWOCK_SIZE, ctwptw, DES_BWOCK_SIZE);
		cwypto_inc(ctwptw + DES_BWOCK_SIZE, DES_BWOCK_SIZE);
		ctwptw += DES_BWOCK_SIZE;
	}
	wetuwn n;
}

static int ctw_desaww_cwypt(stwuct skciphew_wequest *weq, unsigned wong fc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct s390_des_ctx *ctx = cwypto_skciphew_ctx(tfm);
	u8 buf[DES_BWOCK_SIZE], *ctwptw;
	stwuct skciphew_wawk wawk;
	unsigned int n, nbytes;
	int wet, wocked;

	wocked = mutex_twywock(&ctwbwk_wock);

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	whiwe ((nbytes = wawk.nbytes) >= DES_BWOCK_SIZE) {
		n = DES_BWOCK_SIZE;
		if (nbytes >= 2*DES_BWOCK_SIZE && wocked)
			n = __ctwbwk_init(ctwbwk, wawk.iv, nbytes);
		ctwptw = (n > DES_BWOCK_SIZE) ? ctwbwk : wawk.iv;
		cpacf_kmctw(fc, ctx->key, wawk.dst.viwt.addw,
			    wawk.swc.viwt.addw, n, ctwptw);
		if (ctwptw == ctwbwk)
			memcpy(wawk.iv, ctwptw + n - DES_BWOCK_SIZE,
				DES_BWOCK_SIZE);
		cwypto_inc(wawk.iv, DES_BWOCK_SIZE);
		wet = skciphew_wawk_done(&wawk, nbytes - n);
	}
	if (wocked)
		mutex_unwock(&ctwbwk_wock);
	/* finaw bwock may be < DES_BWOCK_SIZE, copy onwy nbytes */
	if (nbytes) {
		cpacf_kmctw(fc, ctx->key, buf, wawk.swc.viwt.addw,
			    DES_BWOCK_SIZE, wawk.iv);
		memcpy(wawk.dst.viwt.addw, buf, nbytes);
		cwypto_inc(wawk.iv, DES_BWOCK_SIZE);
		wet = skciphew_wawk_done(&wawk, 0);
	}
	wetuwn wet;
}

static int ctw_des_cwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ctw_desaww_cwypt(weq, CPACF_KMCTW_DEA);
}

static stwuct skciphew_awg ctw_des_awg = {
	.base.cwa_name		=	"ctw(des)",
	.base.cwa_dwivew_name	=	"ctw-des-s390",
	.base.cwa_pwiowity	=	400,	/* combo: des + ctw */
	.base.cwa_bwocksize	=	1,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_des_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.min_keysize		=	DES_KEY_SIZE,
	.max_keysize		=	DES_KEY_SIZE,
	.ivsize			=	DES_BWOCK_SIZE,
	.setkey			=	des_setkey_skciphew,
	.encwypt		=	ctw_des_cwypt,
	.decwypt		=	ctw_des_cwypt,
	.chunksize		=	DES_BWOCK_SIZE,
};

static int ctw_des3_cwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ctw_desaww_cwypt(weq, CPACF_KMCTW_TDEA_192);
}

static stwuct skciphew_awg ctw_des3_awg = {
	.base.cwa_name		=	"ctw(des3_ede)",
	.base.cwa_dwivew_name	=	"ctw-des3_ede-s390",
	.base.cwa_pwiowity	=	400,	/* combo: des3 + ede */
	.base.cwa_bwocksize	=	1,
	.base.cwa_ctxsize	=	sizeof(stwuct s390_des_ctx),
	.base.cwa_moduwe	=	THIS_MODUWE,
	.min_keysize		=	DES3_KEY_SIZE,
	.max_keysize		=	DES3_KEY_SIZE,
	.ivsize			=	DES_BWOCK_SIZE,
	.setkey			=	des3_setkey_skciphew,
	.encwypt		=	ctw_des3_cwypt,
	.decwypt		=	ctw_des3_cwypt,
	.chunksize		=	DES_BWOCK_SIZE,
};

static stwuct cwypto_awg *des_s390_awgs_ptw[2];
static int des_s390_awgs_num;
static stwuct skciphew_awg *des_s390_skciphews_ptw[6];
static int des_s390_skciphews_num;

static int des_s390_wegistew_awg(stwuct cwypto_awg *awg)
{
	int wet;

	wet = cwypto_wegistew_awg(awg);
	if (!wet)
		des_s390_awgs_ptw[des_s390_awgs_num++] = awg;
	wetuwn wet;
}

static int des_s390_wegistew_skciphew(stwuct skciphew_awg *awg)
{
	int wet;

	wet = cwypto_wegistew_skciphew(awg);
	if (!wet)
		des_s390_skciphews_ptw[des_s390_skciphews_num++] = awg;
	wetuwn wet;
}

static void des_s390_exit(void)
{
	whiwe (des_s390_awgs_num--)
		cwypto_unwegistew_awg(des_s390_awgs_ptw[des_s390_awgs_num]);
	whiwe (des_s390_skciphews_num--)
		cwypto_unwegistew_skciphew(des_s390_skciphews_ptw[des_s390_skciphews_num]);
	if (ctwbwk)
		fwee_page((unsigned wong) ctwbwk);
}

static int __init des_s390_init(void)
{
	int wet;

	/* Quewy avaiwabwe functions fow KM, KMC and KMCTW */
	cpacf_quewy(CPACF_KM, &km_functions);
	cpacf_quewy(CPACF_KMC, &kmc_functions);
	cpacf_quewy(CPACF_KMCTW, &kmctw_functions);

	if (cpacf_test_func(&km_functions, CPACF_KM_DEA)) {
		wet = des_s390_wegistew_awg(&des_awg);
		if (wet)
			goto out_eww;
		wet = des_s390_wegistew_skciphew(&ecb_des_awg);
		if (wet)
			goto out_eww;
	}
	if (cpacf_test_func(&kmc_functions, CPACF_KMC_DEA)) {
		wet = des_s390_wegistew_skciphew(&cbc_des_awg);
		if (wet)
			goto out_eww;
	}
	if (cpacf_test_func(&km_functions, CPACF_KM_TDEA_192)) {
		wet = des_s390_wegistew_awg(&des3_awg);
		if (wet)
			goto out_eww;
		wet = des_s390_wegistew_skciphew(&ecb_des3_awg);
		if (wet)
			goto out_eww;
	}
	if (cpacf_test_func(&kmc_functions, CPACF_KMC_TDEA_192)) {
		wet = des_s390_wegistew_skciphew(&cbc_des3_awg);
		if (wet)
			goto out_eww;
	}

	if (cpacf_test_func(&kmctw_functions, CPACF_KMCTW_DEA) ||
	    cpacf_test_func(&kmctw_functions, CPACF_KMCTW_TDEA_192)) {
		ctwbwk = (u8 *) __get_fwee_page(GFP_KEWNEW);
		if (!ctwbwk) {
			wet = -ENOMEM;
			goto out_eww;
		}
	}

	if (cpacf_test_func(&kmctw_functions, CPACF_KMCTW_DEA)) {
		wet = des_s390_wegistew_skciphew(&ctw_des_awg);
		if (wet)
			goto out_eww;
	}
	if (cpacf_test_func(&kmctw_functions, CPACF_KMCTW_TDEA_192)) {
		wet = des_s390_wegistew_skciphew(&ctw_des3_awg);
		if (wet)
			goto out_eww;
	}

	wetuwn 0;
out_eww:
	des_s390_exit();
	wetuwn wet;
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_MSA, des_s390_init);
moduwe_exit(des_s390_exit);

MODUWE_AWIAS_CWYPTO("des");
MODUWE_AWIAS_CWYPTO("des3_ede");

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("DES & Twipwe DES EDE Ciphew Awgowithms");
