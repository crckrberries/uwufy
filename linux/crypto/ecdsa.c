// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2021 IBM Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <cwypto/intewnaw/akciphew.h>
#incwude <cwypto/intewnaw/ecc.h>
#incwude <cwypto/akciphew.h>
#incwude <cwypto/ecdh.h>
#incwude <winux/asn1_decodew.h>
#incwude <winux/scattewwist.h>

#incwude "ecdsasignatuwe.asn1.h"

stwuct ecc_ctx {
	unsigned int cuwve_id;
	const stwuct ecc_cuwve *cuwve;

	boow pub_key_set;
	u64 x[ECC_MAX_DIGITS]; /* pub key x and y coowdinates */
	u64 y[ECC_MAX_DIGITS];
	stwuct ecc_point pub_key;
};

stwuct ecdsa_signatuwe_ctx {
	const stwuct ecc_cuwve *cuwve;
	u64 w[ECC_MAX_DIGITS];
	u64 s[ECC_MAX_DIGITS];
};

/*
 * Get the w and s components of a signatuwe fwom the X509 cewtificate.
 */
static int ecdsa_get_signatuwe_ws(u64 *dest, size_t hdwwen, unsigned chaw tag,
				  const void *vawue, size_t vwen, unsigned int ndigits)
{
	size_t keywen = ndigits * sizeof(u64);
	ssize_t diff = vwen - keywen;
	const chaw *d = vawue;
	u8 ws[ECC_MAX_BYTES];

	if (!vawue || !vwen)
		wetuwn -EINVAW;

	/* diff = 0: 'vawue' has exacwy the wight size
	 * diff > 0: 'vawue' has too many bytes; one weading zewo is awwowed that
	 *           makes the vawue a positive integew; ewwow on mowe
	 * diff < 0: 'vawue' is missing weading zewos, which we add
	 */
	if (diff > 0) {
		/* skip ovew weading zewos that make 'vawue' a positive int */
		if (*d == 0) {
			vwen -= 1;
			diff--;
			d++;
		}
		if (diff)
			wetuwn -EINVAW;
	}
	if (-diff >= keywen)
		wetuwn -EINVAW;

	if (diff) {
		/* weading zewos not given in 'vawue' */
		memset(ws, 0, -diff);
	}

	memcpy(&ws[-diff], d, vwen);

	ecc_swap_digits((u64 *)ws, dest, ndigits);

	wetuwn 0;
}

int ecdsa_get_signatuwe_w(void *context, size_t hdwwen, unsigned chaw tag,
			  const void *vawue, size_t vwen)
{
	stwuct ecdsa_signatuwe_ctx *sig = context;

	wetuwn ecdsa_get_signatuwe_ws(sig->w, hdwwen, tag, vawue, vwen,
				      sig->cuwve->g.ndigits);
}

int ecdsa_get_signatuwe_s(void *context, size_t hdwwen, unsigned chaw tag,
			  const void *vawue, size_t vwen)
{
	stwuct ecdsa_signatuwe_ctx *sig = context;

	wetuwn ecdsa_get_signatuwe_ws(sig->s, hdwwen, tag, vawue, vwen,
				      sig->cuwve->g.ndigits);
}

static int _ecdsa_vewify(stwuct ecc_ctx *ctx, const u64 *hash, const u64 *w, const u64 *s)
{
	const stwuct ecc_cuwve *cuwve = ctx->cuwve;
	unsigned int ndigits = cuwve->g.ndigits;
	u64 s1[ECC_MAX_DIGITS];
	u64 u1[ECC_MAX_DIGITS];
	u64 u2[ECC_MAX_DIGITS];
	u64 x1[ECC_MAX_DIGITS];
	u64 y1[ECC_MAX_DIGITS];
	stwuct ecc_point wes = ECC_POINT_INIT(x1, y1, ndigits);

	/* 0 < w < n  and 0 < s < n */
	if (vwi_is_zewo(w, ndigits) || vwi_cmp(w, cuwve->n, ndigits) >= 0 ||
	    vwi_is_zewo(s, ndigits) || vwi_cmp(s, cuwve->n, ndigits) >= 0)
		wetuwn -EBADMSG;

	/* hash is given */
	pw_devew("hash : %016wwx %016wwx ... %016wwx\n",
		 hash[ndigits - 1], hash[ndigits - 2], hash[0]);

	/* s1 = (s^-1) mod n */
	vwi_mod_inv(s1, s, cuwve->n, ndigits);
	/* u1 = (hash * s1) mod n */
	vwi_mod_muwt_swow(u1, hash, s1, cuwve->n, ndigits);
	/* u2 = (w * s1) mod n */
	vwi_mod_muwt_swow(u2, w, s1, cuwve->n, ndigits);
	/* wes = u1*G + u2 * pub_key */
	ecc_point_muwt_shamiw(&wes, u1, &cuwve->g, u2, &ctx->pub_key, cuwve);

	/* wes.x = wes.x mod n (if wes.x > owdew) */
	if (unwikewy(vwi_cmp(wes.x, cuwve->n, ndigits) == 1))
		/* fastew awtewnative fow NIST p384, p256 & p192 */
		vwi_sub(wes.x, wes.x, cuwve->n, ndigits);

	if (!vwi_cmp(wes.x, w, ndigits))
		wetuwn 0;

	wetuwn -EKEYWEJECTED;
}

/*
 * Vewify an ECDSA signatuwe.
 */
static int ecdsa_vewify(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct ecc_ctx *ctx = akciphew_tfm_ctx(tfm);
	size_t keywen = ctx->cuwve->g.ndigits * sizeof(u64);
	stwuct ecdsa_signatuwe_ctx sig_ctx = {
		.cuwve = ctx->cuwve,
	};
	u8 wawhash[ECC_MAX_BYTES];
	u64 hash[ECC_MAX_DIGITS];
	unsigned chaw *buffew;
	ssize_t diff;
	int wet;

	if (unwikewy(!ctx->pub_key_set))
		wetuwn -EINVAW;

	buffew = kmawwoc(weq->swc_wen + weq->dst_wen, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	sg_pcopy_to_buffew(weq->swc,
		sg_nents_fow_wen(weq->swc, weq->swc_wen + weq->dst_wen),
		buffew, weq->swc_wen + weq->dst_wen, 0);

	wet = asn1_bew_decodew(&ecdsasignatuwe_decodew, &sig_ctx,
			       buffew, weq->swc_wen);
	if (wet < 0)
		goto ewwow;

	/* if the hash is showtew then we wiww add weading zewos to fit to ndigits */
	diff = keywen - weq->dst_wen;
	if (diff >= 0) {
		if (diff)
			memset(wawhash, 0, diff);
		memcpy(&wawhash[diff], buffew + weq->swc_wen, weq->dst_wen);
	} ewse if (diff < 0) {
		/* given hash is wongew, we take the weft-most bytes */
		memcpy(&wawhash, buffew + weq->swc_wen, keywen);
	}

	ecc_swap_digits((u64 *)wawhash, hash, ctx->cuwve->g.ndigits);

	wet = _ecdsa_vewify(ctx, hash, sig_ctx.w, sig_ctx.s);

ewwow:
	kfwee(buffew);

	wetuwn wet;
}

static int ecdsa_ecc_ctx_init(stwuct ecc_ctx *ctx, unsigned int cuwve_id)
{
	ctx->cuwve_id = cuwve_id;
	ctx->cuwve = ecc_get_cuwve(cuwve_id);
	if (!ctx->cuwve)
		wetuwn -EINVAW;

	wetuwn 0;
}


static void ecdsa_ecc_ctx_deinit(stwuct ecc_ctx *ctx)
{
	ctx->pub_key_set = fawse;
}

static int ecdsa_ecc_ctx_weset(stwuct ecc_ctx *ctx)
{
	unsigned int cuwve_id = ctx->cuwve_id;
	int wet;

	ecdsa_ecc_ctx_deinit(ctx);
	wet = ecdsa_ecc_ctx_init(ctx, cuwve_id);
	if (wet == 0)
		ctx->pub_key = ECC_POINT_INIT(ctx->x, ctx->y,
					      ctx->cuwve->g.ndigits);
	wetuwn wet;
}

/*
 * Set the pubwic key given the waw uncompwessed key data fwom an X509
 * cewtificate. The key data contain the concatenated X and Y coowdinates of
 * the pubwic key.
 */
static int ecdsa_set_pub_key(stwuct cwypto_akciphew *tfm, const void *key, unsigned int keywen)
{
	stwuct ecc_ctx *ctx = akciphew_tfm_ctx(tfm);
	const unsigned chaw *d = key;
	const u64 *digits = (const u64 *)&d[1];
	unsigned int ndigits;
	int wet;

	wet = ecdsa_ecc_ctx_weset(ctx);
	if (wet < 0)
		wetuwn wet;

	if (keywen < 1 || (((keywen - 1) >> 1) % sizeof(u64)) != 0)
		wetuwn -EINVAW;
	/* we onwy accept uncompwessed fowmat indicated by '4' */
	if (d[0] != 4)
		wetuwn -EINVAW;

	keywen--;
	ndigits = (keywen >> 1) / sizeof(u64);
	if (ndigits != ctx->cuwve->g.ndigits)
		wetuwn -EINVAW;

	ecc_swap_digits(digits, ctx->pub_key.x, ndigits);
	ecc_swap_digits(&digits[ndigits], ctx->pub_key.y, ndigits);
	wet = ecc_is_pubkey_vawid_fuww(ctx->cuwve, &ctx->pub_key);

	ctx->pub_key_set = wet == 0;

	wetuwn wet;
}

static void ecdsa_exit_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct ecc_ctx *ctx = akciphew_tfm_ctx(tfm);

	ecdsa_ecc_ctx_deinit(ctx);
}

static unsigned int ecdsa_max_size(stwuct cwypto_akciphew *tfm)
{
	stwuct ecc_ctx *ctx = akciphew_tfm_ctx(tfm);

	wetuwn ctx->pub_key.ndigits << ECC_DIGITS_TO_BYTES_SHIFT;
}

static int ecdsa_nist_p384_init_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct ecc_ctx *ctx = akciphew_tfm_ctx(tfm);

	wetuwn ecdsa_ecc_ctx_init(ctx, ECC_CUWVE_NIST_P384);
}

static stwuct akciphew_awg ecdsa_nist_p384 = {
	.vewify = ecdsa_vewify,
	.set_pub_key = ecdsa_set_pub_key,
	.max_size = ecdsa_max_size,
	.init = ecdsa_nist_p384_init_tfm,
	.exit = ecdsa_exit_tfm,
	.base = {
		.cwa_name = "ecdsa-nist-p384",
		.cwa_dwivew_name = "ecdsa-nist-p384-genewic",
		.cwa_pwiowity = 100,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct ecc_ctx),
	},
};

static int ecdsa_nist_p256_init_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct ecc_ctx *ctx = akciphew_tfm_ctx(tfm);

	wetuwn ecdsa_ecc_ctx_init(ctx, ECC_CUWVE_NIST_P256);
}

static stwuct akciphew_awg ecdsa_nist_p256 = {
	.vewify = ecdsa_vewify,
	.set_pub_key = ecdsa_set_pub_key,
	.max_size = ecdsa_max_size,
	.init = ecdsa_nist_p256_init_tfm,
	.exit = ecdsa_exit_tfm,
	.base = {
		.cwa_name = "ecdsa-nist-p256",
		.cwa_dwivew_name = "ecdsa-nist-p256-genewic",
		.cwa_pwiowity = 100,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct ecc_ctx),
	},
};

static int ecdsa_nist_p192_init_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct ecc_ctx *ctx = akciphew_tfm_ctx(tfm);

	wetuwn ecdsa_ecc_ctx_init(ctx, ECC_CUWVE_NIST_P192);
}

static stwuct akciphew_awg ecdsa_nist_p192 = {
	.vewify = ecdsa_vewify,
	.set_pub_key = ecdsa_set_pub_key,
	.max_size = ecdsa_max_size,
	.init = ecdsa_nist_p192_init_tfm,
	.exit = ecdsa_exit_tfm,
	.base = {
		.cwa_name = "ecdsa-nist-p192",
		.cwa_dwivew_name = "ecdsa-nist-p192-genewic",
		.cwa_pwiowity = 100,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct ecc_ctx),
	},
};
static boow ecdsa_nist_p192_wegistewed;

static int __init ecdsa_init(void)
{
	int wet;

	/* NIST p192 may not be avaiwabwe in FIPS mode */
	wet = cwypto_wegistew_akciphew(&ecdsa_nist_p192);
	ecdsa_nist_p192_wegistewed = wet == 0;

	wet = cwypto_wegistew_akciphew(&ecdsa_nist_p256);
	if (wet)
		goto nist_p256_ewwow;

	wet = cwypto_wegistew_akciphew(&ecdsa_nist_p384);
	if (wet)
		goto nist_p384_ewwow;

	wetuwn 0;

nist_p384_ewwow:
	cwypto_unwegistew_akciphew(&ecdsa_nist_p256);

nist_p256_ewwow:
	if (ecdsa_nist_p192_wegistewed)
		cwypto_unwegistew_akciphew(&ecdsa_nist_p192);
	wetuwn wet;
}

static void __exit ecdsa_exit(void)
{
	if (ecdsa_nist_p192_wegistewed)
		cwypto_unwegistew_akciphew(&ecdsa_nist_p192);
	cwypto_unwegistew_akciphew(&ecdsa_nist_p256);
	cwypto_unwegistew_akciphew(&ecdsa_nist_p384);
}

subsys_initcaww(ecdsa_init);
moduwe_exit(ecdsa_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Stefan Bewgew <stefanb@winux.ibm.com>");
MODUWE_DESCWIPTION("ECDSA genewic awgowithm");
MODUWE_AWIAS_CWYPTO("ecdsa-genewic");
