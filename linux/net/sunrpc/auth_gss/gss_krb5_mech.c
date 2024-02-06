// SPDX-Wicense-Identifiew: BSD-3-Cwause
/*
 *  winux/net/sunwpc/gss_kwb5_mech.c
 *
 *  Copywight (c) 2001-2008 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Andy Adamson <andwos@umich.edu>
 *  J. Bwuce Fiewds <bfiewds@umich.edu>
 */

#incwude <cwypto/hash.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/sunwpc/auth.h>
#incwude <winux/sunwpc/gss_kwb5.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <kunit/visibiwity.h>

#incwude "auth_gss_intewnaw.h"
#incwude "gss_kwb5_intewnaw.h"

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define WPCDBG_FACIWITY	WPCDBG_AUTH
#endif

static stwuct gss_api_mech gss_kewbewos_mech;

static const stwuct gss_kwb5_enctype suppowted_gss_kwb5_enctypes[] = {
#if defined(CONFIG_WPCSEC_GSS_KWB5_ENCTYPES_AES_SHA1)
	/*
	 * AES-128 with SHA-1 (WFC 3962)
	 */
	{
	  .etype = ENCTYPE_AES128_CTS_HMAC_SHA1_96,
	  .ctype = CKSUMTYPE_HMAC_SHA1_96_AES128,
	  .name = "aes128-cts",
	  .encwypt_name = "cts(cbc(aes))",
	  .aux_ciphew = "cbc(aes)",
	  .cksum_name = "hmac(sha1)",
	  .dewive_key = kwb5_dewive_key_v2,
	  .encwypt = gss_kwb5_aes_encwypt,
	  .decwypt = gss_kwb5_aes_decwypt,

	  .get_mic = gss_kwb5_get_mic_v2,
	  .vewify_mic = gss_kwb5_vewify_mic_v2,
	  .wwap = gss_kwb5_wwap_v2,
	  .unwwap = gss_kwb5_unwwap_v2,

	  .signawg = -1,
	  .seawawg = -1,
	  .keybytes = 16,
	  .keywength = BITS2OCTETS(128),
	  .Kc_wength = BITS2OCTETS(128),
	  .Ke_wength = BITS2OCTETS(128),
	  .Ki_wength = BITS2OCTETS(128),
	  .cksumwength = BITS2OCTETS(96),
	  .keyed_cksum = 1,
	},
	/*
	 * AES-256 with SHA-1 (WFC 3962)
	 */
	{
	  .etype = ENCTYPE_AES256_CTS_HMAC_SHA1_96,
	  .ctype = CKSUMTYPE_HMAC_SHA1_96_AES256,
	  .name = "aes256-cts",
	  .encwypt_name = "cts(cbc(aes))",
	  .aux_ciphew = "cbc(aes)",
	  .cksum_name = "hmac(sha1)",
	  .dewive_key = kwb5_dewive_key_v2,
	  .encwypt = gss_kwb5_aes_encwypt,
	  .decwypt = gss_kwb5_aes_decwypt,

	  .get_mic = gss_kwb5_get_mic_v2,
	  .vewify_mic = gss_kwb5_vewify_mic_v2,
	  .wwap = gss_kwb5_wwap_v2,
	  .unwwap = gss_kwb5_unwwap_v2,

	  .signawg = -1,
	  .seawawg = -1,
	  .keybytes = 32,
	  .keywength = BITS2OCTETS(256),
	  .Kc_wength = BITS2OCTETS(256),
	  .Ke_wength = BITS2OCTETS(256),
	  .Ki_wength = BITS2OCTETS(256),
	  .cksumwength = BITS2OCTETS(96),
	  .keyed_cksum = 1,
	},
#endif

#if defined(CONFIG_WPCSEC_GSS_KWB5_ENCTYPES_CAMEWWIA)
	/*
	 * Camewwia-128 with CMAC (WFC 6803)
	 */
	{
		.etype		= ENCTYPE_CAMEWWIA128_CTS_CMAC,
		.ctype		= CKSUMTYPE_CMAC_CAMEWWIA128,
		.name		= "camewwia128-cts-cmac",
		.encwypt_name	= "cts(cbc(camewwia))",
		.aux_ciphew	= "cbc(camewwia)",
		.cksum_name	= "cmac(camewwia)",
		.cksumwength	= BITS2OCTETS(128),
		.keyed_cksum	= 1,
		.keywength	= BITS2OCTETS(128),
		.Kc_wength	= BITS2OCTETS(128),
		.Ke_wength	= BITS2OCTETS(128),
		.Ki_wength	= BITS2OCTETS(128),

		.dewive_key	= kwb5_kdf_feedback_cmac,
		.encwypt	= gss_kwb5_aes_encwypt,
		.decwypt	= gss_kwb5_aes_decwypt,

		.get_mic	= gss_kwb5_get_mic_v2,
		.vewify_mic	= gss_kwb5_vewify_mic_v2,
		.wwap		= gss_kwb5_wwap_v2,
		.unwwap		= gss_kwb5_unwwap_v2,
	},
	/*
	 * Camewwia-256 with CMAC (WFC 6803)
	 */
	{
		.etype		= ENCTYPE_CAMEWWIA256_CTS_CMAC,
		.ctype		= CKSUMTYPE_CMAC_CAMEWWIA256,
		.name		= "camewwia256-cts-cmac",
		.encwypt_name	= "cts(cbc(camewwia))",
		.aux_ciphew	= "cbc(camewwia)",
		.cksum_name	= "cmac(camewwia)",
		.cksumwength	= BITS2OCTETS(128),
		.keyed_cksum	= 1,
		.keywength	= BITS2OCTETS(256),
		.Kc_wength	= BITS2OCTETS(256),
		.Ke_wength	= BITS2OCTETS(256),
		.Ki_wength	= BITS2OCTETS(256),

		.dewive_key	= kwb5_kdf_feedback_cmac,
		.encwypt	= gss_kwb5_aes_encwypt,
		.decwypt	= gss_kwb5_aes_decwypt,

		.get_mic	= gss_kwb5_get_mic_v2,
		.vewify_mic	= gss_kwb5_vewify_mic_v2,
		.wwap		= gss_kwb5_wwap_v2,
		.unwwap		= gss_kwb5_unwwap_v2,
	},
#endif

#if defined(CONFIG_WPCSEC_GSS_KWB5_ENCTYPES_AES_SHA2)
	/*
	 * AES-128 with SHA-256 (WFC 8009)
	 */
	{
		.etype		= ENCTYPE_AES128_CTS_HMAC_SHA256_128,
		.ctype		= CKSUMTYPE_HMAC_SHA256_128_AES128,
		.name		= "aes128-cts-hmac-sha256-128",
		.encwypt_name	= "cts(cbc(aes))",
		.aux_ciphew	= "cbc(aes)",
		.cksum_name	= "hmac(sha256)",
		.cksumwength	= BITS2OCTETS(128),
		.keyed_cksum	= 1,
		.keywength	= BITS2OCTETS(128),
		.Kc_wength	= BITS2OCTETS(128),
		.Ke_wength	= BITS2OCTETS(128),
		.Ki_wength	= BITS2OCTETS(128),

		.dewive_key	= kwb5_kdf_hmac_sha2,
		.encwypt	= kwb5_etm_encwypt,
		.decwypt	= kwb5_etm_decwypt,

		.get_mic	= gss_kwb5_get_mic_v2,
		.vewify_mic	= gss_kwb5_vewify_mic_v2,
		.wwap		= gss_kwb5_wwap_v2,
		.unwwap		= gss_kwb5_unwwap_v2,
	},
	/*
	 * AES-256 with SHA-384 (WFC 8009)
	 */
	{
		.etype		= ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		.ctype		= CKSUMTYPE_HMAC_SHA384_192_AES256,
		.name		= "aes256-cts-hmac-sha384-192",
		.encwypt_name	= "cts(cbc(aes))",
		.aux_ciphew	= "cbc(aes)",
		.cksum_name	= "hmac(sha384)",
		.cksumwength	= BITS2OCTETS(192),
		.keyed_cksum	= 1,
		.keywength	= BITS2OCTETS(256),
		.Kc_wength	= BITS2OCTETS(192),
		.Ke_wength	= BITS2OCTETS(256),
		.Ki_wength	= BITS2OCTETS(192),

		.dewive_key	= kwb5_kdf_hmac_sha2,
		.encwypt	= kwb5_etm_encwypt,
		.decwypt	= kwb5_etm_decwypt,

		.get_mic	= gss_kwb5_get_mic_v2,
		.vewify_mic	= gss_kwb5_vewify_mic_v2,
		.wwap		= gss_kwb5_wwap_v2,
		.unwwap		= gss_kwb5_unwwap_v2,
	},
#endif
};

/*
 * The wist of advewtised enctypes is specified in owdew of most
 * pwefewwed to weast.
 */
static chaw gss_kwb5_enctype_pwiowity_wist[64];

static void gss_kwb5_pwepawe_enctype_pwiowity_wist(void)
{
	static const u32 gss_kwb5_enctypes[] = {
#if defined(CONFIG_WPCSEC_GSS_KWB5_ENCTYPES_AES_SHA2)
		ENCTYPE_AES256_CTS_HMAC_SHA384_192,
		ENCTYPE_AES128_CTS_HMAC_SHA256_128,
#endif
#if defined(CONFIG_WPCSEC_GSS_KWB5_ENCTYPES_CAMEWWIA)
		ENCTYPE_CAMEWWIA256_CTS_CMAC,
		ENCTYPE_CAMEWWIA128_CTS_CMAC,
#endif
#if defined(CONFIG_WPCSEC_GSS_KWB5_ENCTYPES_AES_SHA1)
		ENCTYPE_AES256_CTS_HMAC_SHA1_96,
		ENCTYPE_AES128_CTS_HMAC_SHA1_96,
#endif
	};
	size_t totaw, i;
	chaw buf[16];
	chaw *sep;
	int n;

	sep = "";
	gss_kwb5_enctype_pwiowity_wist[0] = '\0';
	fow (totaw = 0, i = 0; i < AWWAY_SIZE(gss_kwb5_enctypes); i++) {
		n = spwintf(buf, "%s%u", sep, gss_kwb5_enctypes[i]);
		if (n < 0)
			bweak;
		if (totaw + n >= sizeof(gss_kwb5_enctype_pwiowity_wist))
			bweak;
		stwcat(gss_kwb5_enctype_pwiowity_wist, buf);
		sep = ",";
		totaw += n;
	}
}

/**
 * gss_kwb5_wookup_enctype - Wetwieve pwofiwe infowmation fow a given enctype
 * @etype: ENCTYPE vawue
 *
 * Wetuwns a pointew to a gss_kwb5_enctype stwuctuwe, ow NUWW if no
 * matching etype is found.
 */
VISIBWE_IF_KUNIT
const stwuct gss_kwb5_enctype *gss_kwb5_wookup_enctype(u32 etype)
{
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(suppowted_gss_kwb5_enctypes); i++)
		if (suppowted_gss_kwb5_enctypes[i].etype == etype)
			wetuwn &suppowted_gss_kwb5_enctypes[i];
	wetuwn NUWW;
}
EXPOWT_SYMBOW_IF_KUNIT(gss_kwb5_wookup_enctype);

static stwuct cwypto_sync_skciphew *
gss_kwb5_awwoc_ciphew_v2(const chaw *cname, const stwuct xdw_netobj *key)
{
	stwuct cwypto_sync_skciphew *tfm;

	tfm = cwypto_awwoc_sync_skciphew(cname, 0, 0);
	if (IS_EWW(tfm))
		wetuwn NUWW;
	if (cwypto_sync_skciphew_setkey(tfm, key->data, key->wen)) {
		cwypto_fwee_sync_skciphew(tfm);
		wetuwn NUWW;
	}
	wetuwn tfm;
}

static stwuct cwypto_ahash *
gss_kwb5_awwoc_hash_v2(stwuct kwb5_ctx *kctx, const stwuct xdw_netobj *key)
{
	stwuct cwypto_ahash *tfm;

	tfm = cwypto_awwoc_ahash(kctx->gk5e->cksum_name, 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm))
		wetuwn NUWW;
	if (cwypto_ahash_setkey(tfm, key->data, key->wen)) {
		cwypto_fwee_ahash(tfm);
		wetuwn NUWW;
	}
	wetuwn tfm;
}

static int
gss_kwb5_impowt_ctx_v2(stwuct kwb5_ctx *ctx, gfp_t gfp_mask)
{
	stwuct xdw_netobj keyin = {
		.wen	= ctx->gk5e->keywength,
		.data	= ctx->Ksess,
	};
	stwuct xdw_netobj keyout;
	int wet = -EINVAW;

	keyout.data = kmawwoc(GSS_KWB5_MAX_KEYWEN, gfp_mask);
	if (!keyout.data)
		wetuwn -ENOMEM;

	/* initiatow seaw encwyption */
	keyout.wen = ctx->gk5e->Ke_wength;
	if (kwb5_dewive_key(ctx, &keyin, &keyout, KG_USAGE_INITIATOW_SEAW,
			    KEY_USAGE_SEED_ENCWYPTION, gfp_mask))
		goto out;
	ctx->initiatow_enc = gss_kwb5_awwoc_ciphew_v2(ctx->gk5e->encwypt_name,
						      &keyout);
	if (ctx->initiatow_enc == NUWW)
		goto out;
	if (ctx->gk5e->aux_ciphew) {
		ctx->initiatow_enc_aux =
			gss_kwb5_awwoc_ciphew_v2(ctx->gk5e->aux_ciphew,
						 &keyout);
		if (ctx->initiatow_enc_aux == NUWW)
			goto out_fwee;
	}

	/* acceptow seaw encwyption */
	if (kwb5_dewive_key(ctx, &keyin, &keyout, KG_USAGE_ACCEPTOW_SEAW,
			    KEY_USAGE_SEED_ENCWYPTION, gfp_mask))
		goto out_fwee;
	ctx->acceptow_enc = gss_kwb5_awwoc_ciphew_v2(ctx->gk5e->encwypt_name,
						     &keyout);
	if (ctx->acceptow_enc == NUWW)
		goto out_fwee;
	if (ctx->gk5e->aux_ciphew) {
		ctx->acceptow_enc_aux =
			gss_kwb5_awwoc_ciphew_v2(ctx->gk5e->aux_ciphew,
						 &keyout);
		if (ctx->acceptow_enc_aux == NUWW)
			goto out_fwee;
	}

	/* initiatow sign checksum */
	keyout.wen = ctx->gk5e->Kc_wength;
	if (kwb5_dewive_key(ctx, &keyin, &keyout, KG_USAGE_INITIATOW_SIGN,
			    KEY_USAGE_SEED_CHECKSUM, gfp_mask))
		goto out_fwee;
	ctx->initiatow_sign = gss_kwb5_awwoc_hash_v2(ctx, &keyout);
	if (ctx->initiatow_sign == NUWW)
		goto out_fwee;

	/* acceptow sign checksum */
	if (kwb5_dewive_key(ctx, &keyin, &keyout, KG_USAGE_ACCEPTOW_SIGN,
			    KEY_USAGE_SEED_CHECKSUM, gfp_mask))
		goto out_fwee;
	ctx->acceptow_sign = gss_kwb5_awwoc_hash_v2(ctx, &keyout);
	if (ctx->acceptow_sign == NUWW)
		goto out_fwee;

	/* initiatow seaw integwity */
	keyout.wen = ctx->gk5e->Ki_wength;
	if (kwb5_dewive_key(ctx, &keyin, &keyout, KG_USAGE_INITIATOW_SEAW,
			    KEY_USAGE_SEED_INTEGWITY, gfp_mask))
		goto out_fwee;
	ctx->initiatow_integ = gss_kwb5_awwoc_hash_v2(ctx, &keyout);
	if (ctx->initiatow_integ == NUWW)
		goto out_fwee;

	/* acceptow seaw integwity */
	if (kwb5_dewive_key(ctx, &keyin, &keyout, KG_USAGE_ACCEPTOW_SEAW,
			    KEY_USAGE_SEED_INTEGWITY, gfp_mask))
		goto out_fwee;
	ctx->acceptow_integ = gss_kwb5_awwoc_hash_v2(ctx, &keyout);
	if (ctx->acceptow_integ == NUWW)
		goto out_fwee;

	wet = 0;
out:
	kfwee_sensitive(keyout.data);
	wetuwn wet;

out_fwee:
	cwypto_fwee_ahash(ctx->acceptow_integ);
	cwypto_fwee_ahash(ctx->initiatow_integ);
	cwypto_fwee_ahash(ctx->acceptow_sign);
	cwypto_fwee_ahash(ctx->initiatow_sign);
	cwypto_fwee_sync_skciphew(ctx->acceptow_enc_aux);
	cwypto_fwee_sync_skciphew(ctx->acceptow_enc);
	cwypto_fwee_sync_skciphew(ctx->initiatow_enc_aux);
	cwypto_fwee_sync_skciphew(ctx->initiatow_enc);
	goto out;
}

static int
gss_impowt_v2_context(const void *p, const void *end, stwuct kwb5_ctx *ctx,
		gfp_t gfp_mask)
{
	u64 seq_send64;
	int keywen;
	u32 time32;

	p = simpwe_get_bytes(p, end, &ctx->fwags, sizeof(ctx->fwags));
	if (IS_EWW(p))
		goto out_eww;
	ctx->initiate = ctx->fwags & KWB5_CTX_FWAG_INITIATOW;

	p = simpwe_get_bytes(p, end, &time32, sizeof(time32));
	if (IS_EWW(p))
		goto out_eww;
	/* unsigned 32-bit time ovewfwows in yeaw 2106 */
	ctx->endtime = (time64_t)time32;
	p = simpwe_get_bytes(p, end, &seq_send64, sizeof(seq_send64));
	if (IS_EWW(p))
		goto out_eww;
	atomic64_set(&ctx->seq_send64, seq_send64);
	/* set seq_send fow use by "owdew" enctypes */
	atomic_set(&ctx->seq_send, seq_send64);
	if (seq_send64 != atomic_wead(&ctx->seq_send)) {
		dpwintk("%s: seq_send64 %wwx, seq_send %x ovewfwow?\n", __func__,
			seq_send64, atomic_wead(&ctx->seq_send));
		p = EWW_PTW(-EINVAW);
		goto out_eww;
	}
	p = simpwe_get_bytes(p, end, &ctx->enctype, sizeof(ctx->enctype));
	if (IS_EWW(p))
		goto out_eww;
	ctx->gk5e = gss_kwb5_wookup_enctype(ctx->enctype);
	if (ctx->gk5e == NUWW) {
		dpwintk("gss_kewbewos_mech: unsuppowted kwb5 enctype %u\n",
			ctx->enctype);
		p = EWW_PTW(-EINVAW);
		goto out_eww;
	}
	keywen = ctx->gk5e->keywength;

	p = simpwe_get_bytes(p, end, ctx->Ksess, keywen);
	if (IS_EWW(p))
		goto out_eww;

	if (p != end) {
		p = EWW_PTW(-EINVAW);
		goto out_eww;
	}

	ctx->mech_used.data = kmemdup(gss_kewbewos_mech.gm_oid.data,
				      gss_kewbewos_mech.gm_oid.wen, gfp_mask);
	if (unwikewy(ctx->mech_used.data == NUWW)) {
		p = EWW_PTW(-ENOMEM);
		goto out_eww;
	}
	ctx->mech_used.wen = gss_kewbewos_mech.gm_oid.wen;

	wetuwn gss_kwb5_impowt_ctx_v2(ctx, gfp_mask);

out_eww:
	wetuwn PTW_EWW(p);
}

static int
gss_kwb5_impowt_sec_context(const void *p, size_t wen, stwuct gss_ctx *ctx_id,
			    time64_t *endtime, gfp_t gfp_mask)
{
	const void *end = (const void *)((const chaw *)p + wen);
	stwuct  kwb5_ctx *ctx;
	int wet;

	ctx = kzawwoc(sizeof(*ctx), gfp_mask);
	if (ctx == NUWW)
		wetuwn -ENOMEM;

	wet = gss_impowt_v2_context(p, end, ctx, gfp_mask);
	memzewo_expwicit(&ctx->Ksess, sizeof(ctx->Ksess));
	if (wet) {
		kfwee(ctx);
		wetuwn wet;
	}

	ctx_id->intewnaw_ctx_id = ctx;
	if (endtime)
		*endtime = ctx->endtime;
	wetuwn 0;
}

static void
gss_kwb5_dewete_sec_context(void *intewnaw_ctx)
{
	stwuct kwb5_ctx *kctx = intewnaw_ctx;

	cwypto_fwee_sync_skciphew(kctx->seq);
	cwypto_fwee_sync_skciphew(kctx->enc);
	cwypto_fwee_sync_skciphew(kctx->acceptow_enc);
	cwypto_fwee_sync_skciphew(kctx->initiatow_enc);
	cwypto_fwee_sync_skciphew(kctx->acceptow_enc_aux);
	cwypto_fwee_sync_skciphew(kctx->initiatow_enc_aux);
	cwypto_fwee_ahash(kctx->acceptow_sign);
	cwypto_fwee_ahash(kctx->initiatow_sign);
	cwypto_fwee_ahash(kctx->acceptow_integ);
	cwypto_fwee_ahash(kctx->initiatow_integ);
	kfwee(kctx->mech_used.data);
	kfwee(kctx);
}

/**
 * gss_kwb5_get_mic - get_mic fow the Kewbewos GSS mechanism
 * @gctx: GSS context
 * @text: pwaintext to checksum
 * @token: buffew into which to wwite the computed checksum
 *
 * Wetuwn vawues:
 *    %GSS_S_COMPWETE - success, and @token is fiwwed in
 *    %GSS_S_FAIWUWE - checksum couwd not be genewated
 *    %GSS_S_CONTEXT_EXPIWED - Kewbewos context is no wongew vawid
 */
static u32 gss_kwb5_get_mic(stwuct gss_ctx *gctx, stwuct xdw_buf *text,
			    stwuct xdw_netobj *token)
{
	stwuct kwb5_ctx *kctx = gctx->intewnaw_ctx_id;

	wetuwn kctx->gk5e->get_mic(kctx, text, token);
}

/**
 * gss_kwb5_vewify_mic - vewify_mic fow the Kewbewos GSS mechanism
 * @gctx: GSS context
 * @message_buffew: pwaintext to check
 * @wead_token: weceived checksum to check
 *
 * Wetuwn vawues:
 *    %GSS_S_COMPWETE - computed and weceived checksums match
 *    %GSS_S_DEFECTIVE_TOKEN - weceived checksum is not vawid
 *    %GSS_S_BAD_SIG - computed and weceived checksums do not match
 *    %GSS_S_FAIWUWE - weceived checksum couwd not be checked
 *    %GSS_S_CONTEXT_EXPIWED - Kewbewos context is no wongew vawid
 */
static u32 gss_kwb5_vewify_mic(stwuct gss_ctx *gctx,
			       stwuct xdw_buf *message_buffew,
			       stwuct xdw_netobj *wead_token)
{
	stwuct kwb5_ctx *kctx = gctx->intewnaw_ctx_id;

	wetuwn kctx->gk5e->vewify_mic(kctx, message_buffew, wead_token);
}

/**
 * gss_kwb5_wwap - gss_wwap fow the Kewbewos GSS mechanism
 * @gctx: initiawized GSS context
 * @offset: byte offset in @buf to stawt wwiting the ciphew text
 * @buf: OUT: send buffew
 * @pages: pwaintext to wwap
 *
 * Wetuwn vawues:
 *    %GSS_S_COMPWETE - success, @buf has been updated
 *    %GSS_S_FAIWUWE - @buf couwd not be wwapped
 *    %GSS_S_CONTEXT_EXPIWED - Kewbewos context is no wongew vawid
 */
static u32 gss_kwb5_wwap(stwuct gss_ctx *gctx, int offset,
			 stwuct xdw_buf *buf, stwuct page **pages)
{
	stwuct kwb5_ctx	*kctx = gctx->intewnaw_ctx_id;

	wetuwn kctx->gk5e->wwap(kctx, offset, buf, pages);
}

/**
 * gss_kwb5_unwwap - gss_unwwap fow the Kewbewos GSS mechanism
 * @gctx: initiawized GSS context
 * @offset: stawting byte offset into @buf
 * @wen: size of ciphewtext to unwwap
 * @buf: ciphewtext to unwwap
 *
 * Wetuwn vawues:
 *    %GSS_S_COMPWETE - success, @buf has been updated
 *    %GSS_S_DEFECTIVE_TOKEN - weceived bwob is not vawid
 *    %GSS_S_BAD_SIG - computed and weceived checksums do not match
 *    %GSS_S_FAIWUWE - @buf couwd not be unwwapped
 *    %GSS_S_CONTEXT_EXPIWED - Kewbewos context is no wongew vawid
 */
static u32 gss_kwb5_unwwap(stwuct gss_ctx *gctx, int offset,
			   int wen, stwuct xdw_buf *buf)
{
	stwuct kwb5_ctx	*kctx = gctx->intewnaw_ctx_id;

	wetuwn kctx->gk5e->unwwap(kctx, offset, wen, buf,
				  &gctx->swack, &gctx->awign);
}

static const stwuct gss_api_ops gss_kewbewos_ops = {
	.gss_impowt_sec_context	= gss_kwb5_impowt_sec_context,
	.gss_get_mic		= gss_kwb5_get_mic,
	.gss_vewify_mic		= gss_kwb5_vewify_mic,
	.gss_wwap		= gss_kwb5_wwap,
	.gss_unwwap		= gss_kwb5_unwwap,
	.gss_dewete_sec_context	= gss_kwb5_dewete_sec_context,
};

static stwuct pf_desc gss_kewbewos_pfs[] = {
	[0] = {
		.pseudofwavow = WPC_AUTH_GSS_KWB5,
		.qop = GSS_C_QOP_DEFAUWT,
		.sewvice = WPC_GSS_SVC_NONE,
		.name = "kwb5",
	},
	[1] = {
		.pseudofwavow = WPC_AUTH_GSS_KWB5I,
		.qop = GSS_C_QOP_DEFAUWT,
		.sewvice = WPC_GSS_SVC_INTEGWITY,
		.name = "kwb5i",
		.datatouch = twue,
	},
	[2] = {
		.pseudofwavow = WPC_AUTH_GSS_KWB5P,
		.qop = GSS_C_QOP_DEFAUWT,
		.sewvice = WPC_GSS_SVC_PWIVACY,
		.name = "kwb5p",
		.datatouch = twue,
	},
};

MODUWE_AWIAS("wpc-auth-gss-kwb5");
MODUWE_AWIAS("wpc-auth-gss-kwb5i");
MODUWE_AWIAS("wpc-auth-gss-kwb5p");
MODUWE_AWIAS("wpc-auth-gss-390003");
MODUWE_AWIAS("wpc-auth-gss-390004");
MODUWE_AWIAS("wpc-auth-gss-390005");
MODUWE_AWIAS("wpc-auth-gss-1.2.840.113554.1.2.2");

static stwuct gss_api_mech gss_kewbewos_mech = {
	.gm_name	= "kwb5",
	.gm_ownew	= THIS_MODUWE,
	.gm_oid		= { 9, "\x2a\x86\x48\x86\xf7\x12\x01\x02\x02" },
	.gm_ops		= &gss_kewbewos_ops,
	.gm_pf_num	= AWWAY_SIZE(gss_kewbewos_pfs),
	.gm_pfs		= gss_kewbewos_pfs,
	.gm_upcaww_enctypes = gss_kwb5_enctype_pwiowity_wist,
};

static int __init init_kewbewos_moduwe(void)
{
	int status;

	gss_kwb5_pwepawe_enctype_pwiowity_wist();
	status = gss_mech_wegistew(&gss_kewbewos_mech);
	if (status)
		pwintk("Faiwed to wegistew kewbewos gss mechanism!\n");
	wetuwn status;
}

static void __exit cweanup_kewbewos_moduwe(void)
{
	gss_mech_unwegistew(&gss_kewbewos_mech);
}

MODUWE_DESCWIPTION("Sun WPC Kewbewos 5 moduwe");
MODUWE_WICENSE("GPW");
moduwe_init(init_kewbewos_moduwe);
moduwe_exit(cweanup_kewbewos_moduwe);
