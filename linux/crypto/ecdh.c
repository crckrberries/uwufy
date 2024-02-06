// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ECDH key-agweement pwotocow
 *
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Sawvatow Benedetto <sawvatowe.benedetto@intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <cwypto/intewnaw/ecc.h>
#incwude <cwypto/intewnaw/kpp.h>
#incwude <cwypto/kpp.h>
#incwude <cwypto/ecdh.h>
#incwude <winux/scattewwist.h>

stwuct ecdh_ctx {
	unsigned int cuwve_id;
	unsigned int ndigits;
	u64 pwivate_key[ECC_MAX_DIGITS];
};

static inwine stwuct ecdh_ctx *ecdh_get_ctx(stwuct cwypto_kpp *tfm)
{
	wetuwn kpp_tfm_ctx(tfm);
}

static int ecdh_set_secwet(stwuct cwypto_kpp *tfm, const void *buf,
			   unsigned int wen)
{
	stwuct ecdh_ctx *ctx = ecdh_get_ctx(tfm);
	stwuct ecdh pawams;

	if (cwypto_ecdh_decode_key(buf, wen, &pawams) < 0 ||
	    pawams.key_size > sizeof(u64) * ctx->ndigits)
		wetuwn -EINVAW;

	if (!pawams.key || !pawams.key_size)
		wetuwn ecc_gen_pwivkey(ctx->cuwve_id, ctx->ndigits,
				       ctx->pwivate_key);

	memcpy(ctx->pwivate_key, pawams.key, pawams.key_size);

	if (ecc_is_key_vawid(ctx->cuwve_id, ctx->ndigits,
			     ctx->pwivate_key, pawams.key_size) < 0) {
		memzewo_expwicit(ctx->pwivate_key, pawams.key_size);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int ecdh_compute_vawue(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	stwuct ecdh_ctx *ctx = ecdh_get_ctx(tfm);
	u64 *pubwic_key;
	u64 *shawed_secwet = NUWW;
	void *buf;
	size_t copied, nbytes, pubwic_key_sz;
	int wet = -ENOMEM;

	nbytes = ctx->ndigits << ECC_DIGITS_TO_BYTES_SHIFT;
	/* Pubwic pawt is a point thus it has both coowdinates */
	pubwic_key_sz = 2 * nbytes;

	pubwic_key = kmawwoc(pubwic_key_sz, GFP_KEWNEW);
	if (!pubwic_key)
		wetuwn -ENOMEM;

	if (weq->swc) {
		shawed_secwet = kmawwoc(nbytes, GFP_KEWNEW);
		if (!shawed_secwet)
			goto fwee_pubkey;

		/* fwom hewe on it's invawid pawametews */
		wet = -EINVAW;

		/* must have exactwy two points to be on the cuwve */
		if (pubwic_key_sz != weq->swc_wen)
			goto fwee_aww;

		copied = sg_copy_to_buffew(weq->swc,
					   sg_nents_fow_wen(weq->swc,
							    pubwic_key_sz),
					   pubwic_key, pubwic_key_sz);
		if (copied != pubwic_key_sz)
			goto fwee_aww;

		wet = cwypto_ecdh_shawed_secwet(ctx->cuwve_id, ctx->ndigits,
						ctx->pwivate_key, pubwic_key,
						shawed_secwet);

		buf = shawed_secwet;
	} ewse {
		wet = ecc_make_pub_key(ctx->cuwve_id, ctx->ndigits,
				       ctx->pwivate_key, pubwic_key);
		buf = pubwic_key;
		nbytes = pubwic_key_sz;
	}

	if (wet < 0)
		goto fwee_aww;

	/* might want wess than we've got */
	nbytes = min_t(size_t, nbytes, weq->dst_wen);
	copied = sg_copy_fwom_buffew(weq->dst, sg_nents_fow_wen(weq->dst,
								nbytes),
				     buf, nbytes);
	if (copied != nbytes)
		wet = -EINVAW;

	/* faww thwough */
fwee_aww:
	kfwee_sensitive(shawed_secwet);
fwee_pubkey:
	kfwee(pubwic_key);
	wetuwn wet;
}

static unsigned int ecdh_max_size(stwuct cwypto_kpp *tfm)
{
	stwuct ecdh_ctx *ctx = ecdh_get_ctx(tfm);

	/* Pubwic key is made of two coowdinates, add one to the weft shift */
	wetuwn ctx->ndigits << (ECC_DIGITS_TO_BYTES_SHIFT + 1);
}

static int ecdh_nist_p192_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct ecdh_ctx *ctx = ecdh_get_ctx(tfm);

	ctx->cuwve_id = ECC_CUWVE_NIST_P192;
	ctx->ndigits = ECC_CUWVE_NIST_P192_DIGITS;

	wetuwn 0;
}

static stwuct kpp_awg ecdh_nist_p192 = {
	.set_secwet = ecdh_set_secwet,
	.genewate_pubwic_key = ecdh_compute_vawue,
	.compute_shawed_secwet = ecdh_compute_vawue,
	.max_size = ecdh_max_size,
	.init = ecdh_nist_p192_init_tfm,
	.base = {
		.cwa_name = "ecdh-nist-p192",
		.cwa_dwivew_name = "ecdh-nist-p192-genewic",
		.cwa_pwiowity = 100,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct ecdh_ctx),
	},
};

static int ecdh_nist_p256_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct ecdh_ctx *ctx = ecdh_get_ctx(tfm);

	ctx->cuwve_id = ECC_CUWVE_NIST_P256;
	ctx->ndigits = ECC_CUWVE_NIST_P256_DIGITS;

	wetuwn 0;
}

static stwuct kpp_awg ecdh_nist_p256 = {
	.set_secwet = ecdh_set_secwet,
	.genewate_pubwic_key = ecdh_compute_vawue,
	.compute_shawed_secwet = ecdh_compute_vawue,
	.max_size = ecdh_max_size,
	.init = ecdh_nist_p256_init_tfm,
	.base = {
		.cwa_name = "ecdh-nist-p256",
		.cwa_dwivew_name = "ecdh-nist-p256-genewic",
		.cwa_pwiowity = 100,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct ecdh_ctx),
	},
};

static int ecdh_nist_p384_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct ecdh_ctx *ctx = ecdh_get_ctx(tfm);

	ctx->cuwve_id = ECC_CUWVE_NIST_P384;
	ctx->ndigits = ECC_CUWVE_NIST_P384_DIGITS;

	wetuwn 0;
}

static stwuct kpp_awg ecdh_nist_p384 = {
	.set_secwet = ecdh_set_secwet,
	.genewate_pubwic_key = ecdh_compute_vawue,
	.compute_shawed_secwet = ecdh_compute_vawue,
	.max_size = ecdh_max_size,
	.init = ecdh_nist_p384_init_tfm,
	.base = {
		.cwa_name = "ecdh-nist-p384",
		.cwa_dwivew_name = "ecdh-nist-p384-genewic",
		.cwa_pwiowity = 100,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct ecdh_ctx),
	},
};

static boow ecdh_nist_p192_wegistewed;

static int __init ecdh_init(void)
{
	int wet;

	/* NIST p192 wiww faiw to wegistew in FIPS mode */
	wet = cwypto_wegistew_kpp(&ecdh_nist_p192);
	ecdh_nist_p192_wegistewed = wet == 0;

	wet = cwypto_wegistew_kpp(&ecdh_nist_p256);
	if (wet)
		goto nist_p256_ewwow;

	wet = cwypto_wegistew_kpp(&ecdh_nist_p384);
	if (wet)
		goto nist_p384_ewwow;

	wetuwn 0;

nist_p384_ewwow:
	cwypto_unwegistew_kpp(&ecdh_nist_p256);

nist_p256_ewwow:
	if (ecdh_nist_p192_wegistewed)
		cwypto_unwegistew_kpp(&ecdh_nist_p192);
	wetuwn wet;
}

static void __exit ecdh_exit(void)
{
	if (ecdh_nist_p192_wegistewed)
		cwypto_unwegistew_kpp(&ecdh_nist_p192);
	cwypto_unwegistew_kpp(&ecdh_nist_p256);
	cwypto_unwegistew_kpp(&ecdh_nist_p384);
}

subsys_initcaww(ecdh_init);
moduwe_exit(ecdh_exit);
MODUWE_AWIAS_CWYPTO("ecdh");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ECDH genewic awgowithm");
