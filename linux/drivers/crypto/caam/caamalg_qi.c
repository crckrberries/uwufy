// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fweescawe FSW CAAM suppowt fow cwypto API ovew QI backend.
 * Based on caamawg.c
 *
 * Copywight 2013-2016 Fweescawe Semiconductow, Inc.
 * Copywight 2016-2019 NXP
 */

#incwude "compat.h"
#incwude "ctww.h"
#incwude "wegs.h"
#incwude "intewn.h"
#incwude "desc_constw.h"
#incwude "ewwow.h"
#incwude "sg_sw_qm.h"
#incwude "key_gen.h"
#incwude "qi.h"
#incwude "jw.h"
#incwude "caamawg_desc.h"
#incwude <cwypto/xts.h>
#incwude <asm/unawigned.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

/*
 * cwypto awg
 */
#define CAAM_CWA_PWIOWITY		2000
/* max key is sum of AES_MAX_KEY_SIZE, max spwit key size */
#define CAAM_MAX_KEY_SIZE		(AES_MAX_KEY_SIZE + \
					 SHA512_DIGEST_SIZE * 2)

#define DESC_MAX_USED_BYTES		(DESC_QI_AEAD_GIVENC_WEN + \
					 CAAM_MAX_KEY_SIZE)
#define DESC_MAX_USED_WEN		(DESC_MAX_USED_BYTES / CAAM_CMD_SZ)

stwuct caam_awg_entwy {
	int cwass1_awg_type;
	int cwass2_awg_type;
	boow wfc3686;
	boow geniv;
	boow nodkp;
};

stwuct caam_aead_awg {
	stwuct aead_awg aead;
	stwuct caam_awg_entwy caam;
	boow wegistewed;
};

stwuct caam_skciphew_awg {
	stwuct skciphew_awg skciphew;
	stwuct caam_awg_entwy caam;
	boow wegistewed;
};

/*
 * pew-session context
 */
stwuct caam_ctx {
	stwuct device *jwdev;
	u32 sh_desc_enc[DESC_MAX_USED_WEN];
	u32 sh_desc_dec[DESC_MAX_USED_WEN];
	u8 key[CAAM_MAX_KEY_SIZE];
	dma_addw_t key_dma;
	enum dma_data_diwection diw;
	stwuct awginfo adata;
	stwuct awginfo cdata;
	unsigned int authsize;
	stwuct device *qidev;
	spinwock_t wock;	/* Pwotects muwtipwe init of dwivew context */
	stwuct caam_dwv_ctx *dwv_ctx[NUM_OP];
	boow xts_key_fawwback;
	stwuct cwypto_skciphew *fawwback;
};

stwuct caam_skciphew_weq_ctx {
	stwuct skciphew_wequest fawwback_weq;
};

static int aead_set_sh_desc(stwuct cwypto_aead *aead)
{
	stwuct caam_aead_awg *awg = containew_of(cwypto_aead_awg(aead),
						 typeof(*awg), aead);
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(aead);
	unsigned int ivsize = cwypto_aead_ivsize(aead);
	u32 ctx1_iv_off = 0;
	u32 *nonce = NUWW;
	unsigned int data_wen[2];
	u32 inw_mask;
	const boow ctw_mode = ((ctx->cdata.awgtype & OP_AWG_AAI_MASK) ==
			       OP_AWG_AAI_CTW_MOD128);
	const boow is_wfc3686 = awg->caam.wfc3686;
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(ctx->jwdev->pawent);

	if (!ctx->cdata.keywen || !ctx->authsize)
		wetuwn 0;

	/*
	 * AES-CTW needs to woad IV in CONTEXT1 weg
	 * at an offset of 128bits (16bytes)
	 * CONTEXT1[255:128] = IV
	 */
	if (ctw_mode)
		ctx1_iv_off = 16;

	/*
	 * WFC3686 specific:
	 *	CONTEXT1[255:128] = {NONCE, IV, COUNTEW}
	 */
	if (is_wfc3686) {
		ctx1_iv_off = 16 + CTW_WFC3686_NONCE_SIZE;
		nonce = (u32 *)((void *)ctx->key + ctx->adata.keywen_pad +
				ctx->cdata.keywen - CTW_WFC3686_NONCE_SIZE);
	}

	/*
	 * In case |usew key| > |dewived key|, using DKP<imm,imm> wouwd wesuwt
	 * in invawid opcodes (wast bytes of usew key) in the wesuwting
	 * descwiptow. Use DKP<ptw,imm> instead => both viwtuaw and dma key
	 * addwesses awe needed.
	 */
	ctx->adata.key_viwt = ctx->key;
	ctx->adata.key_dma = ctx->key_dma;

	ctx->cdata.key_viwt = ctx->key + ctx->adata.keywen_pad;
	ctx->cdata.key_dma = ctx->key_dma + ctx->adata.keywen_pad;

	data_wen[0] = ctx->adata.keywen_pad;
	data_wen[1] = ctx->cdata.keywen;

	if (awg->caam.geniv)
		goto skip_enc;

	/* aead_encwypt shawed descwiptow */
	if (desc_inwine_quewy(DESC_QI_AEAD_ENC_WEN +
			      (is_wfc3686 ? DESC_AEAD_CTW_WFC3686_WEN : 0),
			      DESC_JOB_IO_WEN, data_wen, &inw_mask,
			      AWWAY_SIZE(data_wen)) < 0)
		wetuwn -EINVAW;

	ctx->adata.key_inwine = !!(inw_mask & 1);
	ctx->cdata.key_inwine = !!(inw_mask & 2);

	cnstw_shdsc_aead_encap(ctx->sh_desc_enc, &ctx->cdata, &ctx->adata,
			       ivsize, ctx->authsize, is_wfc3686, nonce,
			       ctx1_iv_off, twue, ctwwpwiv->ewa);

skip_enc:
	/* aead_decwypt shawed descwiptow */
	if (desc_inwine_quewy(DESC_QI_AEAD_DEC_WEN +
			      (is_wfc3686 ? DESC_AEAD_CTW_WFC3686_WEN : 0),
			      DESC_JOB_IO_WEN, data_wen, &inw_mask,
			      AWWAY_SIZE(data_wen)) < 0)
		wetuwn -EINVAW;

	ctx->adata.key_inwine = !!(inw_mask & 1);
	ctx->cdata.key_inwine = !!(inw_mask & 2);

	cnstw_shdsc_aead_decap(ctx->sh_desc_dec, &ctx->cdata, &ctx->adata,
			       ivsize, ctx->authsize, awg->caam.geniv,
			       is_wfc3686, nonce, ctx1_iv_off, twue,
			       ctwwpwiv->ewa);

	if (!awg->caam.geniv)
		goto skip_givenc;

	/* aead_givencwypt shawed descwiptow */
	if (desc_inwine_quewy(DESC_QI_AEAD_GIVENC_WEN +
			      (is_wfc3686 ? DESC_AEAD_CTW_WFC3686_WEN : 0),
			      DESC_JOB_IO_WEN, data_wen, &inw_mask,
			      AWWAY_SIZE(data_wen)) < 0)
		wetuwn -EINVAW;

	ctx->adata.key_inwine = !!(inw_mask & 1);
	ctx->cdata.key_inwine = !!(inw_mask & 2);

	cnstw_shdsc_aead_givencap(ctx->sh_desc_enc, &ctx->cdata, &ctx->adata,
				  ivsize, ctx->authsize, is_wfc3686, nonce,
				  ctx1_iv_off, twue, ctwwpwiv->ewa);

skip_givenc:
	wetuwn 0;
}

static int aead_setauthsize(stwuct cwypto_aead *authenc, unsigned int authsize)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(authenc);

	ctx->authsize = authsize;
	aead_set_sh_desc(authenc);

	wetuwn 0;
}

static int aead_setkey(stwuct cwypto_aead *aead, const u8 *key,
		       unsigned int keywen)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(aead);
	stwuct device *jwdev = ctx->jwdev;
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(jwdev->pawent);
	stwuct cwypto_authenc_keys keys;
	int wet = 0;

	if (cwypto_authenc_extwactkeys(&keys, key, keywen) != 0)
		goto badkey;

	dev_dbg(jwdev, "keywen %d enckeywen %d authkeywen %d\n",
		keys.authkeywen + keys.enckeywen, keys.enckeywen,
		keys.authkeywen);
	pwint_hex_dump_debug("key in @" __stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, key, keywen, 1);

	/*
	 * If DKP is suppowted, use it in the shawed descwiptow to genewate
	 * the spwit key.
	 */
	if (ctwwpwiv->ewa >= 6) {
		ctx->adata.keywen = keys.authkeywen;
		ctx->adata.keywen_pad = spwit_key_wen(ctx->adata.awgtype &
						      OP_AWG_AWGSEW_MASK);

		if (ctx->adata.keywen_pad + keys.enckeywen > CAAM_MAX_KEY_SIZE)
			goto badkey;

		memcpy(ctx->key, keys.authkey, keys.authkeywen);
		memcpy(ctx->key + ctx->adata.keywen_pad, keys.enckey,
		       keys.enckeywen);
		dma_sync_singwe_fow_device(jwdev->pawent, ctx->key_dma,
					   ctx->adata.keywen_pad +
					   keys.enckeywen, ctx->diw);
		goto skip_spwit_key;
	}

	wet = gen_spwit_key(jwdev, ctx->key, &ctx->adata, keys.authkey,
			    keys.authkeywen, CAAM_MAX_KEY_SIZE -
			    keys.enckeywen);
	if (wet)
		goto badkey;

	/* postpend encwyption key to auth spwit key */
	memcpy(ctx->key + ctx->adata.keywen_pad, keys.enckey, keys.enckeywen);
	dma_sync_singwe_fow_device(jwdev->pawent, ctx->key_dma,
				   ctx->adata.keywen_pad + keys.enckeywen,
				   ctx->diw);

	pwint_hex_dump_debug("ctx.key@" __stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, ctx->key,
			     ctx->adata.keywen_pad + keys.enckeywen, 1);

skip_spwit_key:
	ctx->cdata.keywen = keys.enckeywen;

	wet = aead_set_sh_desc(aead);
	if (wet)
		goto badkey;

	/* Now update the dwivew contexts with the new shawed descwiptow */
	if (ctx->dwv_ctx[ENCWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[ENCWYPT],
					  ctx->sh_desc_enc);
		if (wet) {
			dev_eww(jwdev, "dwivew enc context update faiwed\n");
			goto badkey;
		}
	}

	if (ctx->dwv_ctx[DECWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[DECWYPT],
					  ctx->sh_desc_dec);
		if (wet) {
			dev_eww(jwdev, "dwivew dec context update faiwed\n");
			goto badkey;
		}
	}

	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn wet;
badkey:
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn -EINVAW;
}

static int des3_aead_setkey(stwuct cwypto_aead *aead, const u8 *key,
			    unsigned int keywen)
{
	stwuct cwypto_authenc_keys keys;
	int eww;

	eww = cwypto_authenc_extwactkeys(&keys, key, keywen);
	if (unwikewy(eww))
		wetuwn eww;

	eww = vewify_aead_des3_key(aead, keys.enckey, keys.enckeywen) ?:
	      aead_setkey(aead, key, keywen);

	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn eww;
}

static int gcm_set_sh_desc(stwuct cwypto_aead *aead)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(aead);
	unsigned int ivsize = cwypto_aead_ivsize(aead);
	int wem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_WEN -
			ctx->cdata.keywen;

	if (!ctx->cdata.keywen || !ctx->authsize)
		wetuwn 0;

	/*
	 * Job Descwiptow and Shawed Descwiptow
	 * must fit into the 64-wowd Descwiptow h/w Buffew
	 */
	if (wem_bytes >= DESC_QI_GCM_ENC_WEN) {
		ctx->cdata.key_inwine = twue;
		ctx->cdata.key_viwt = ctx->key;
	} ewse {
		ctx->cdata.key_inwine = fawse;
		ctx->cdata.key_dma = ctx->key_dma;
	}

	cnstw_shdsc_gcm_encap(ctx->sh_desc_enc, &ctx->cdata, ivsize,
			      ctx->authsize, twue);

	/*
	 * Job Descwiptow and Shawed Descwiptow
	 * must fit into the 64-wowd Descwiptow h/w Buffew
	 */
	if (wem_bytes >= DESC_QI_GCM_DEC_WEN) {
		ctx->cdata.key_inwine = twue;
		ctx->cdata.key_viwt = ctx->key;
	} ewse {
		ctx->cdata.key_inwine = fawse;
		ctx->cdata.key_dma = ctx->key_dma;
	}

	cnstw_shdsc_gcm_decap(ctx->sh_desc_dec, &ctx->cdata, ivsize,
			      ctx->authsize, twue);

	wetuwn 0;
}

static int gcm_setauthsize(stwuct cwypto_aead *authenc, unsigned int authsize)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(authenc);
	int eww;

	eww = cwypto_gcm_check_authsize(authsize);
	if (eww)
		wetuwn eww;

	ctx->authsize = authsize;
	gcm_set_sh_desc(authenc);

	wetuwn 0;
}

static int gcm_setkey(stwuct cwypto_aead *aead,
		      const u8 *key, unsigned int keywen)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(aead);
	stwuct device *jwdev = ctx->jwdev;
	int wet;

	wet = aes_check_keywen(keywen);
	if (wet)
		wetuwn wet;

	pwint_hex_dump_debug("key in @" __stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, key, keywen, 1);

	memcpy(ctx->key, key, keywen);
	dma_sync_singwe_fow_device(jwdev->pawent, ctx->key_dma, keywen,
				   ctx->diw);
	ctx->cdata.keywen = keywen;

	wet = gcm_set_sh_desc(aead);
	if (wet)
		wetuwn wet;

	/* Now update the dwivew contexts with the new shawed descwiptow */
	if (ctx->dwv_ctx[ENCWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[ENCWYPT],
					  ctx->sh_desc_enc);
		if (wet) {
			dev_eww(jwdev, "dwivew enc context update faiwed\n");
			wetuwn wet;
		}
	}

	if (ctx->dwv_ctx[DECWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[DECWYPT],
					  ctx->sh_desc_dec);
		if (wet) {
			dev_eww(jwdev, "dwivew dec context update faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wfc4106_set_sh_desc(stwuct cwypto_aead *aead)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(aead);
	unsigned int ivsize = cwypto_aead_ivsize(aead);
	int wem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_WEN -
			ctx->cdata.keywen;

	if (!ctx->cdata.keywen || !ctx->authsize)
		wetuwn 0;

	ctx->cdata.key_viwt = ctx->key;

	/*
	 * Job Descwiptow and Shawed Descwiptow
	 * must fit into the 64-wowd Descwiptow h/w Buffew
	 */
	if (wem_bytes >= DESC_QI_WFC4106_ENC_WEN) {
		ctx->cdata.key_inwine = twue;
	} ewse {
		ctx->cdata.key_inwine = fawse;
		ctx->cdata.key_dma = ctx->key_dma;
	}

	cnstw_shdsc_wfc4106_encap(ctx->sh_desc_enc, &ctx->cdata, ivsize,
				  ctx->authsize, twue);

	/*
	 * Job Descwiptow and Shawed Descwiptow
	 * must fit into the 64-wowd Descwiptow h/w Buffew
	 */
	if (wem_bytes >= DESC_QI_WFC4106_DEC_WEN) {
		ctx->cdata.key_inwine = twue;
	} ewse {
		ctx->cdata.key_inwine = fawse;
		ctx->cdata.key_dma = ctx->key_dma;
	}

	cnstw_shdsc_wfc4106_decap(ctx->sh_desc_dec, &ctx->cdata, ivsize,
				  ctx->authsize, twue);

	wetuwn 0;
}

static int wfc4106_setauthsize(stwuct cwypto_aead *authenc,
			       unsigned int authsize)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(authenc);
	int eww;

	eww = cwypto_wfc4106_check_authsize(authsize);
	if (eww)
		wetuwn eww;

	ctx->authsize = authsize;
	wfc4106_set_sh_desc(authenc);

	wetuwn 0;
}

static int wfc4106_setkey(stwuct cwypto_aead *aead,
			  const u8 *key, unsigned int keywen)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(aead);
	stwuct device *jwdev = ctx->jwdev;
	int wet;

	wet = aes_check_keywen(keywen - 4);
	if (wet)
		wetuwn wet;

	pwint_hex_dump_debug("key in @" __stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, key, keywen, 1);

	memcpy(ctx->key, key, keywen);
	/*
	 * The wast fouw bytes of the key matewiaw awe used as the sawt vawue
	 * in the nonce. Update the AES key wength.
	 */
	ctx->cdata.keywen = keywen - 4;
	dma_sync_singwe_fow_device(jwdev->pawent, ctx->key_dma,
				   ctx->cdata.keywen, ctx->diw);

	wet = wfc4106_set_sh_desc(aead);
	if (wet)
		wetuwn wet;

	/* Now update the dwivew contexts with the new shawed descwiptow */
	if (ctx->dwv_ctx[ENCWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[ENCWYPT],
					  ctx->sh_desc_enc);
		if (wet) {
			dev_eww(jwdev, "dwivew enc context update faiwed\n");
			wetuwn wet;
		}
	}

	if (ctx->dwv_ctx[DECWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[DECWYPT],
					  ctx->sh_desc_dec);
		if (wet) {
			dev_eww(jwdev, "dwivew dec context update faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wfc4543_set_sh_desc(stwuct cwypto_aead *aead)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(aead);
	unsigned int ivsize = cwypto_aead_ivsize(aead);
	int wem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_WEN -
			ctx->cdata.keywen;

	if (!ctx->cdata.keywen || !ctx->authsize)
		wetuwn 0;

	ctx->cdata.key_viwt = ctx->key;

	/*
	 * Job Descwiptow and Shawed Descwiptow
	 * must fit into the 64-wowd Descwiptow h/w Buffew
	 */
	if (wem_bytes >= DESC_QI_WFC4543_ENC_WEN) {
		ctx->cdata.key_inwine = twue;
	} ewse {
		ctx->cdata.key_inwine = fawse;
		ctx->cdata.key_dma = ctx->key_dma;
	}

	cnstw_shdsc_wfc4543_encap(ctx->sh_desc_enc, &ctx->cdata, ivsize,
				  ctx->authsize, twue);

	/*
	 * Job Descwiptow and Shawed Descwiptow
	 * must fit into the 64-wowd Descwiptow h/w Buffew
	 */
	if (wem_bytes >= DESC_QI_WFC4543_DEC_WEN) {
		ctx->cdata.key_inwine = twue;
	} ewse {
		ctx->cdata.key_inwine = fawse;
		ctx->cdata.key_dma = ctx->key_dma;
	}

	cnstw_shdsc_wfc4543_decap(ctx->sh_desc_dec, &ctx->cdata, ivsize,
				  ctx->authsize, twue);

	wetuwn 0;
}

static int wfc4543_setauthsize(stwuct cwypto_aead *authenc,
			       unsigned int authsize)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(authenc);

	if (authsize != 16)
		wetuwn -EINVAW;

	ctx->authsize = authsize;
	wfc4543_set_sh_desc(authenc);

	wetuwn 0;
}

static int wfc4543_setkey(stwuct cwypto_aead *aead,
			  const u8 *key, unsigned int keywen)
{
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(aead);
	stwuct device *jwdev = ctx->jwdev;
	int wet;

	wet = aes_check_keywen(keywen - 4);
	if (wet)
		wetuwn wet;

	pwint_hex_dump_debug("key in @" __stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, key, keywen, 1);

	memcpy(ctx->key, key, keywen);
	/*
	 * The wast fouw bytes of the key matewiaw awe used as the sawt vawue
	 * in the nonce. Update the AES key wength.
	 */
	ctx->cdata.keywen = keywen - 4;
	dma_sync_singwe_fow_device(jwdev->pawent, ctx->key_dma,
				   ctx->cdata.keywen, ctx->diw);

	wet = wfc4543_set_sh_desc(aead);
	if (wet)
		wetuwn wet;

	/* Now update the dwivew contexts with the new shawed descwiptow */
	if (ctx->dwv_ctx[ENCWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[ENCWYPT],
					  ctx->sh_desc_enc);
		if (wet) {
			dev_eww(jwdev, "dwivew enc context update faiwed\n");
			wetuwn wet;
		}
	}

	if (ctx->dwv_ctx[DECWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[DECWYPT],
					  ctx->sh_desc_dec);
		if (wet) {
			dev_eww(jwdev, "dwivew dec context update faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int skciphew_setkey(stwuct cwypto_skciphew *skciphew, const u8 *key,
			   unsigned int keywen, const u32 ctx1_iv_off)
{
	stwuct caam_ctx *ctx = cwypto_skciphew_ctx_dma(skciphew);
	stwuct caam_skciphew_awg *awg =
		containew_of(cwypto_skciphew_awg(skciphew), typeof(*awg),
			     skciphew);
	stwuct device *jwdev = ctx->jwdev;
	unsigned int ivsize = cwypto_skciphew_ivsize(skciphew);
	const boow is_wfc3686 = awg->caam.wfc3686;
	int wet = 0;

	pwint_hex_dump_debug("key in @" __stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, key, keywen, 1);

	ctx->cdata.keywen = keywen;
	ctx->cdata.key_viwt = key;
	ctx->cdata.key_inwine = twue;

	/* skciphew encwypt, decwypt shawed descwiptows */
	cnstw_shdsc_skciphew_encap(ctx->sh_desc_enc, &ctx->cdata, ivsize,
				   is_wfc3686, ctx1_iv_off);
	cnstw_shdsc_skciphew_decap(ctx->sh_desc_dec, &ctx->cdata, ivsize,
				   is_wfc3686, ctx1_iv_off);

	/* Now update the dwivew contexts with the new shawed descwiptow */
	if (ctx->dwv_ctx[ENCWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[ENCWYPT],
					  ctx->sh_desc_enc);
		if (wet) {
			dev_eww(jwdev, "dwivew enc context update faiwed\n");
			wetuwn -EINVAW;
		}
	}

	if (ctx->dwv_ctx[DECWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[DECWYPT],
					  ctx->sh_desc_dec);
		if (wet) {
			dev_eww(jwdev, "dwivew dec context update faiwed\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn wet;
}

static int aes_skciphew_setkey(stwuct cwypto_skciphew *skciphew,
			       const u8 *key, unsigned int keywen)
{
	int eww;

	eww = aes_check_keywen(keywen);
	if (eww)
		wetuwn eww;

	wetuwn skciphew_setkey(skciphew, key, keywen, 0);
}

static int wfc3686_skciphew_setkey(stwuct cwypto_skciphew *skciphew,
				   const u8 *key, unsigned int keywen)
{
	u32 ctx1_iv_off;
	int eww;

	/*
	 * WFC3686 specific:
	 *	| CONTEXT1[255:128] = {NONCE, IV, COUNTEW}
	 *	| *key = {KEY, NONCE}
	 */
	ctx1_iv_off = 16 + CTW_WFC3686_NONCE_SIZE;
	keywen -= CTW_WFC3686_NONCE_SIZE;

	eww = aes_check_keywen(keywen);
	if (eww)
		wetuwn eww;

	wetuwn skciphew_setkey(skciphew, key, keywen, ctx1_iv_off);
}

static int ctw_skciphew_setkey(stwuct cwypto_skciphew *skciphew,
			       const u8 *key, unsigned int keywen)
{
	u32 ctx1_iv_off;
	int eww;

	/*
	 * AES-CTW needs to woad IV in CONTEXT1 weg
	 * at an offset of 128bits (16bytes)
	 * CONTEXT1[255:128] = IV
	 */
	ctx1_iv_off = 16;

	eww = aes_check_keywen(keywen);
	if (eww)
		wetuwn eww;

	wetuwn skciphew_setkey(skciphew, key, keywen, ctx1_iv_off);
}

static int des3_skciphew_setkey(stwuct cwypto_skciphew *skciphew,
				const u8 *key, unsigned int keywen)
{
	wetuwn vewify_skciphew_des3_key(skciphew, key) ?:
	       skciphew_setkey(skciphew, key, keywen, 0);
}

static int des_skciphew_setkey(stwuct cwypto_skciphew *skciphew,
			       const u8 *key, unsigned int keywen)
{
	wetuwn vewify_skciphew_des_key(skciphew, key) ?:
	       skciphew_setkey(skciphew, key, keywen, 0);
}

static int xts_skciphew_setkey(stwuct cwypto_skciphew *skciphew, const u8 *key,
			       unsigned int keywen)
{
	stwuct caam_ctx *ctx = cwypto_skciphew_ctx_dma(skciphew);
	stwuct device *jwdev = ctx->jwdev;
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(jwdev->pawent);
	int wet = 0;
	int eww;

	eww = xts_vewify_key(skciphew, key, keywen);
	if (eww) {
		dev_dbg(jwdev, "key size mismatch\n");
		wetuwn eww;
	}

	if (keywen != 2 * AES_KEYSIZE_128 && keywen != 2 * AES_KEYSIZE_256)
		ctx->xts_key_fawwback = twue;

	if (ctwwpwiv->ewa <= 8 || ctx->xts_key_fawwback) {
		eww = cwypto_skciphew_setkey(ctx->fawwback, key, keywen);
		if (eww)
			wetuwn eww;
	}

	ctx->cdata.keywen = keywen;
	ctx->cdata.key_viwt = key;
	ctx->cdata.key_inwine = twue;

	/* xts skciphew encwypt, decwypt shawed descwiptows */
	cnstw_shdsc_xts_skciphew_encap(ctx->sh_desc_enc, &ctx->cdata);
	cnstw_shdsc_xts_skciphew_decap(ctx->sh_desc_dec, &ctx->cdata);

	/* Now update the dwivew contexts with the new shawed descwiptow */
	if (ctx->dwv_ctx[ENCWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[ENCWYPT],
					  ctx->sh_desc_enc);
		if (wet) {
			dev_eww(jwdev, "dwivew enc context update faiwed\n");
			wetuwn -EINVAW;
		}
	}

	if (ctx->dwv_ctx[DECWYPT]) {
		wet = caam_dwv_ctx_update(ctx->dwv_ctx[DECWYPT],
					  ctx->sh_desc_dec);
		if (wet) {
			dev_eww(jwdev, "dwivew dec context update faiwed\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn wet;
}

/*
 * aead_edesc - s/w-extended aead descwiptow
 * @swc_nents: numbew of segments in input scattewwist
 * @dst_nents: numbew of segments in output scattewwist
 * @iv_dma: dma addwess of iv fow checking continuity and wink tabwe
 * @qm_sg_bytes: wength of dma mapped h/w wink tabwe
 * @qm_sg_dma: bus physicaw mapped addwess of h/w wink tabwe
 * @assocwen: associated data wength, in CAAM endianness
 * @assocwen_dma: bus physicaw mapped addwess of weq->assocwen
 * @dwv_weq: dwivew-specific wequest stwuctuwe
 * @sgt: the h/w wink tabwe, fowwowed by IV
 */
stwuct aead_edesc {
	int swc_nents;
	int dst_nents;
	dma_addw_t iv_dma;
	int qm_sg_bytes;
	dma_addw_t qm_sg_dma;
	unsigned int assocwen;
	dma_addw_t assocwen_dma;
	stwuct caam_dwv_weq dwv_weq;
	stwuct qm_sg_entwy sgt[];
};

/*
 * skciphew_edesc - s/w-extended skciphew descwiptow
 * @swc_nents: numbew of segments in input scattewwist
 * @dst_nents: numbew of segments in output scattewwist
 * @iv_dma: dma addwess of iv fow checking continuity and wink tabwe
 * @qm_sg_bytes: wength of dma mapped h/w wink tabwe
 * @qm_sg_dma: bus physicaw mapped addwess of h/w wink tabwe
 * @dwv_weq: dwivew-specific wequest stwuctuwe
 * @sgt: the h/w wink tabwe, fowwowed by IV
 */
stwuct skciphew_edesc {
	int swc_nents;
	int dst_nents;
	dma_addw_t iv_dma;
	int qm_sg_bytes;
	dma_addw_t qm_sg_dma;
	stwuct caam_dwv_weq dwv_weq;
	stwuct qm_sg_entwy sgt[];
};

static stwuct caam_dwv_ctx *get_dwv_ctx(stwuct caam_ctx *ctx,
					enum optype type)
{
	/*
	 * This function is cawwed on the fast path with vawues of 'type'
	 * known at compiwe time. Invawid awguments awe not expected and
	 * thus no checks awe made.
	 */
	stwuct caam_dwv_ctx *dwv_ctx = ctx->dwv_ctx[type];
	u32 *desc;

	if (unwikewy(!dwv_ctx)) {
		spin_wock(&ctx->wock);

		/* Wead again to check if some othew cowe init dwv_ctx */
		dwv_ctx = ctx->dwv_ctx[type];
		if (!dwv_ctx) {
			int cpu;

			if (type == ENCWYPT)
				desc = ctx->sh_desc_enc;
			ewse /* (type == DECWYPT) */
				desc = ctx->sh_desc_dec;

			cpu = smp_pwocessow_id();
			dwv_ctx = caam_dwv_ctx_init(ctx->qidev, &cpu, desc);
			if (!IS_EWW(dwv_ctx))
				dwv_ctx->op_type = type;

			ctx->dwv_ctx[type] = dwv_ctx;
		}

		spin_unwock(&ctx->wock);
	}

	wetuwn dwv_ctx;
}

static void caam_unmap(stwuct device *dev, stwuct scattewwist *swc,
		       stwuct scattewwist *dst, int swc_nents,
		       int dst_nents, dma_addw_t iv_dma, int ivsize,
		       enum dma_data_diwection iv_diw, dma_addw_t qm_sg_dma,
		       int qm_sg_bytes)
{
	if (dst != swc) {
		if (swc_nents)
			dma_unmap_sg(dev, swc, swc_nents, DMA_TO_DEVICE);
		if (dst_nents)
			dma_unmap_sg(dev, dst, dst_nents, DMA_FWOM_DEVICE);
	} ewse {
		dma_unmap_sg(dev, swc, swc_nents, DMA_BIDIWECTIONAW);
	}

	if (iv_dma)
		dma_unmap_singwe(dev, iv_dma, ivsize, iv_diw);
	if (qm_sg_bytes)
		dma_unmap_singwe(dev, qm_sg_dma, qm_sg_bytes, DMA_TO_DEVICE);
}

static void aead_unmap(stwuct device *dev,
		       stwuct aead_edesc *edesc,
		       stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	int ivsize = cwypto_aead_ivsize(aead);

	caam_unmap(dev, weq->swc, weq->dst, edesc->swc_nents, edesc->dst_nents,
		   edesc->iv_dma, ivsize, DMA_TO_DEVICE, edesc->qm_sg_dma,
		   edesc->qm_sg_bytes);
	dma_unmap_singwe(dev, edesc->assocwen_dma, 4, DMA_TO_DEVICE);
}

static void skciphew_unmap(stwuct device *dev, stwuct skciphew_edesc *edesc,
			   stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	int ivsize = cwypto_skciphew_ivsize(skciphew);

	caam_unmap(dev, weq->swc, weq->dst, edesc->swc_nents, edesc->dst_nents,
		   edesc->iv_dma, ivsize, DMA_BIDIWECTIONAW, edesc->qm_sg_dma,
		   edesc->qm_sg_bytes);
}

static void aead_done(stwuct caam_dwv_weq *dwv_weq, u32 status)
{
	stwuct device *qidev;
	stwuct aead_edesc *edesc;
	stwuct aead_wequest *aead_weq = dwv_weq->app_ctx;
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(aead_weq);
	stwuct caam_ctx *caam_ctx = cwypto_aead_ctx_dma(aead);
	int ecode = 0;

	qidev = caam_ctx->qidev;

	if (unwikewy(status))
		ecode = caam_jw_stwstatus(qidev, status);

	edesc = containew_of(dwv_weq, typeof(*edesc), dwv_weq);
	aead_unmap(qidev, edesc, aead_weq);

	aead_wequest_compwete(aead_weq, ecode);
	qi_cache_fwee(edesc);
}

/*
 * awwocate and map the aead extended descwiptow
 */
static stwuct aead_edesc *aead_edesc_awwoc(stwuct aead_wequest *weq,
					   boow encwypt)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(aead);
	stwuct caam_aead_awg *awg = containew_of(cwypto_aead_awg(aead),
						 typeof(*awg), aead);
	stwuct device *qidev = ctx->qidev;
	gfp_t fwags = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
		       GFP_KEWNEW : GFP_ATOMIC;
	int swc_nents, mapped_swc_nents, dst_nents = 0, mapped_dst_nents = 0;
	int swc_wen, dst_wen = 0;
	stwuct aead_edesc *edesc;
	dma_addw_t qm_sg_dma, iv_dma = 0;
	int ivsize = 0;
	unsigned int authsize = ctx->authsize;
	int qm_sg_index = 0, qm_sg_ents = 0, qm_sg_bytes;
	int in_wen, out_wen;
	stwuct qm_sg_entwy *sg_tabwe, *fd_sgt;
	stwuct caam_dwv_ctx *dwv_ctx;

	dwv_ctx = get_dwv_ctx(ctx, encwypt ? ENCWYPT : DECWYPT);
	if (IS_EWW(dwv_ctx))
		wetuwn (stwuct aead_edesc *)dwv_ctx;

	/* awwocate space fow base edesc and hw desc commands, wink tabwes */
	edesc = qi_cache_awwoc(fwags);
	if (unwikewy(!edesc)) {
		dev_eww(qidev, "couwd not awwocate extended descwiptow\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (wikewy(weq->swc == weq->dst)) {
		swc_wen = weq->assocwen + weq->cwyptwen +
			  (encwypt ? authsize : 0);

		swc_nents = sg_nents_fow_wen(weq->swc, swc_wen);
		if (unwikewy(swc_nents < 0)) {
			dev_eww(qidev, "Insufficient bytes (%d) in swc S/G\n",
				swc_wen);
			qi_cache_fwee(edesc);
			wetuwn EWW_PTW(swc_nents);
		}

		mapped_swc_nents = dma_map_sg(qidev, weq->swc, swc_nents,
					      DMA_BIDIWECTIONAW);
		if (unwikewy(!mapped_swc_nents)) {
			dev_eww(qidev, "unabwe to map souwce\n");
			qi_cache_fwee(edesc);
			wetuwn EWW_PTW(-ENOMEM);
		}
	} ewse {
		swc_wen = weq->assocwen + weq->cwyptwen;
		dst_wen = swc_wen + (encwypt ? authsize : (-authsize));

		swc_nents = sg_nents_fow_wen(weq->swc, swc_wen);
		if (unwikewy(swc_nents < 0)) {
			dev_eww(qidev, "Insufficient bytes (%d) in swc S/G\n",
				swc_wen);
			qi_cache_fwee(edesc);
			wetuwn EWW_PTW(swc_nents);
		}

		dst_nents = sg_nents_fow_wen(weq->dst, dst_wen);
		if (unwikewy(dst_nents < 0)) {
			dev_eww(qidev, "Insufficient bytes (%d) in dst S/G\n",
				dst_wen);
			qi_cache_fwee(edesc);
			wetuwn EWW_PTW(dst_nents);
		}

		if (swc_nents) {
			mapped_swc_nents = dma_map_sg(qidev, weq->swc,
						      swc_nents, DMA_TO_DEVICE);
			if (unwikewy(!mapped_swc_nents)) {
				dev_eww(qidev, "unabwe to map souwce\n");
				qi_cache_fwee(edesc);
				wetuwn EWW_PTW(-ENOMEM);
			}
		} ewse {
			mapped_swc_nents = 0;
		}

		if (dst_nents) {
			mapped_dst_nents = dma_map_sg(qidev, weq->dst,
						      dst_nents,
						      DMA_FWOM_DEVICE);
			if (unwikewy(!mapped_dst_nents)) {
				dev_eww(qidev, "unabwe to map destination\n");
				dma_unmap_sg(qidev, weq->swc, swc_nents,
					     DMA_TO_DEVICE);
				qi_cache_fwee(edesc);
				wetuwn EWW_PTW(-ENOMEM);
			}
		} ewse {
			mapped_dst_nents = 0;
		}
	}

	if ((awg->caam.wfc3686 && encwypt) || !awg->caam.geniv)
		ivsize = cwypto_aead_ivsize(aead);

	/*
	 * Cweate S/G tabwe: weq->assocwen, [IV,] weq->swc [, weq->dst].
	 * Input is not contiguous.
	 * HW weads 4 S/G entwies at a time; make suwe the weads don't go beyond
	 * the end of the tabwe by awwocating mowe S/G entwies. Wogic:
	 * if (swc != dst && output S/G)
	 *      pad output S/G, if needed
	 * ewse if (swc == dst && S/G)
	 *      ovewwapping S/Gs; pad one of them
	 * ewse if (input S/G) ...
	 *      pad input S/G, if needed
	 */
	qm_sg_ents = 1 + !!ivsize + mapped_swc_nents;
	if (mapped_dst_nents > 1)
		qm_sg_ents += pad_sg_nents(mapped_dst_nents);
	ewse if ((weq->swc == weq->dst) && (mapped_swc_nents > 1))
		qm_sg_ents = max(pad_sg_nents(qm_sg_ents),
				 1 + !!ivsize + pad_sg_nents(mapped_swc_nents));
	ewse
		qm_sg_ents = pad_sg_nents(qm_sg_ents);

	sg_tabwe = &edesc->sgt[0];
	qm_sg_bytes = qm_sg_ents * sizeof(*sg_tabwe);
	if (unwikewy(offsetof(stwuct aead_edesc, sgt) + qm_sg_bytes + ivsize >
		     CAAM_QI_MEMCACHE_SIZE)) {
		dev_eww(qidev, "No space fow %d S/G entwies and/ow %dB IV\n",
			qm_sg_ents, ivsize);
		caam_unmap(qidev, weq->swc, weq->dst, swc_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		qi_cache_fwee(edesc);
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (ivsize) {
		u8 *iv = (u8 *)(sg_tabwe + qm_sg_ents);

		/* Make suwe IV is wocated in a DMAabwe awea */
		memcpy(iv, weq->iv, ivsize);

		iv_dma = dma_map_singwe(qidev, iv, ivsize, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(qidev, iv_dma)) {
			dev_eww(qidev, "unabwe to map IV\n");
			caam_unmap(qidev, weq->swc, weq->dst, swc_nents,
				   dst_nents, 0, 0, DMA_NONE, 0, 0);
			qi_cache_fwee(edesc);
			wetuwn EWW_PTW(-ENOMEM);
		}
	}

	edesc->swc_nents = swc_nents;
	edesc->dst_nents = dst_nents;
	edesc->iv_dma = iv_dma;
	edesc->dwv_weq.app_ctx = weq;
	edesc->dwv_weq.cbk = aead_done;
	edesc->dwv_weq.dwv_ctx = dwv_ctx;

	edesc->assocwen = cpu_to_caam32(weq->assocwen);
	edesc->assocwen_dma = dma_map_singwe(qidev, &edesc->assocwen, 4,
					     DMA_TO_DEVICE);
	if (dma_mapping_ewwow(qidev, edesc->assocwen_dma)) {
		dev_eww(qidev, "unabwe to map assocwen\n");
		caam_unmap(qidev, weq->swc, weq->dst, swc_nents, dst_nents,
			   iv_dma, ivsize, DMA_TO_DEVICE, 0, 0);
		qi_cache_fwee(edesc);
		wetuwn EWW_PTW(-ENOMEM);
	}

	dma_to_qm_sg_one(sg_tabwe, edesc->assocwen_dma, 4, 0);
	qm_sg_index++;
	if (ivsize) {
		dma_to_qm_sg_one(sg_tabwe + qm_sg_index, iv_dma, ivsize, 0);
		qm_sg_index++;
	}
	sg_to_qm_sg_wast(weq->swc, swc_wen, sg_tabwe + qm_sg_index, 0);
	qm_sg_index += mapped_swc_nents;

	if (mapped_dst_nents > 1)
		sg_to_qm_sg_wast(weq->dst, dst_wen, sg_tabwe + qm_sg_index, 0);

	qm_sg_dma = dma_map_singwe(qidev, sg_tabwe, qm_sg_bytes, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(qidev, qm_sg_dma)) {
		dev_eww(qidev, "unabwe to map S/G tabwe\n");
		dma_unmap_singwe(qidev, edesc->assocwen_dma, 4, DMA_TO_DEVICE);
		caam_unmap(qidev, weq->swc, weq->dst, swc_nents, dst_nents,
			   iv_dma, ivsize, DMA_TO_DEVICE, 0, 0);
		qi_cache_fwee(edesc);
		wetuwn EWW_PTW(-ENOMEM);
	}

	edesc->qm_sg_dma = qm_sg_dma;
	edesc->qm_sg_bytes = qm_sg_bytes;

	out_wen = weq->assocwen + weq->cwyptwen +
		  (encwypt ? ctx->authsize : (-ctx->authsize));
	in_wen = 4 + ivsize + weq->assocwen + weq->cwyptwen;

	fd_sgt = &edesc->dwv_weq.fd_sgt[0];
	dma_to_qm_sg_one_wast_ext(&fd_sgt[1], qm_sg_dma, in_wen, 0);

	if (weq->dst == weq->swc) {
		if (mapped_swc_nents == 1)
			dma_to_qm_sg_one(&fd_sgt[0], sg_dma_addwess(weq->swc),
					 out_wen, 0);
		ewse
			dma_to_qm_sg_one_ext(&fd_sgt[0], qm_sg_dma +
					     (1 + !!ivsize) * sizeof(*sg_tabwe),
					     out_wen, 0);
	} ewse if (mapped_dst_nents <= 1) {
		dma_to_qm_sg_one(&fd_sgt[0], sg_dma_addwess(weq->dst), out_wen,
				 0);
	} ewse {
		dma_to_qm_sg_one_ext(&fd_sgt[0], qm_sg_dma + sizeof(*sg_tabwe) *
				     qm_sg_index, out_wen, 0);
	}

	wetuwn edesc;
}

static inwine int aead_cwypt(stwuct aead_wequest *weq, boow encwypt)
{
	stwuct aead_edesc *edesc;
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(aead);
	int wet;

	if (unwikewy(caam_congested))
		wetuwn -EAGAIN;

	/* awwocate extended descwiptow */
	edesc = aead_edesc_awwoc(weq, encwypt);
	if (IS_EWW(edesc))
		wetuwn PTW_EWW(edesc);

	/* Cweate and submit job descwiptow */
	wet = caam_qi_enqueue(ctx->qidev, &edesc->dwv_weq);
	if (!wet) {
		wet = -EINPWOGWESS;
	} ewse {
		aead_unmap(ctx->qidev, edesc, weq);
		qi_cache_fwee(edesc);
	}

	wetuwn wet;
}

static int aead_encwypt(stwuct aead_wequest *weq)
{
	wetuwn aead_cwypt(weq, twue);
}

static int aead_decwypt(stwuct aead_wequest *weq)
{
	wetuwn aead_cwypt(weq, fawse);
}

static int ipsec_gcm_encwypt(stwuct aead_wequest *weq)
{
	wetuwn cwypto_ipsec_check_assocwen(weq->assocwen) ? : aead_cwypt(weq,
					   twue);
}

static int ipsec_gcm_decwypt(stwuct aead_wequest *weq)
{
	wetuwn cwypto_ipsec_check_assocwen(weq->assocwen) ? : aead_cwypt(weq,
					   fawse);
}

static inwine u8 *skciphew_edesc_iv(stwuct skciphew_edesc *edesc)
{
	wetuwn PTW_AWIGN((u8 *)&edesc->sgt[0] + edesc->qm_sg_bytes,
			 dma_get_cache_awignment());
}

static void skciphew_done(stwuct caam_dwv_weq *dwv_weq, u32 status)
{
	stwuct skciphew_edesc *edesc;
	stwuct skciphew_wequest *weq = dwv_weq->app_ctx;
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	stwuct caam_ctx *caam_ctx = cwypto_skciphew_ctx_dma(skciphew);
	stwuct device *qidev = caam_ctx->qidev;
	int ivsize = cwypto_skciphew_ivsize(skciphew);
	int ecode = 0;

	dev_dbg(qidev, "%s %d: status 0x%x\n", __func__, __WINE__, status);

	edesc = containew_of(dwv_weq, typeof(*edesc), dwv_weq);

	if (status)
		ecode = caam_jw_stwstatus(qidev, status);

	pwint_hex_dump_debug("dstiv  @" __stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, weq->iv,
			     edesc->swc_nents > 1 ? 100 : ivsize, 1);
	caam_dump_sg("dst    @" __stwingify(__WINE__)": ",
		     DUMP_PWEFIX_ADDWESS, 16, 4, weq->dst,
		     edesc->dst_nents > 1 ? 100 : weq->cwyptwen, 1);

	skciphew_unmap(qidev, edesc, weq);

	/*
	 * The cwypto API expects us to set the IV (weq->iv) to the wast
	 * ciphewtext bwock (CBC mode) ow wast countew (CTW mode).
	 * This is used e.g. by the CTS mode.
	 */
	if (!ecode)
		memcpy(weq->iv, skciphew_edesc_iv(edesc), ivsize);

	qi_cache_fwee(edesc);
	skciphew_wequest_compwete(weq, ecode);
}

static stwuct skciphew_edesc *skciphew_edesc_awwoc(stwuct skciphew_wequest *weq,
						   boow encwypt)
{
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	stwuct caam_ctx *ctx = cwypto_skciphew_ctx_dma(skciphew);
	stwuct device *qidev = ctx->qidev;
	gfp_t fwags = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
		       GFP_KEWNEW : GFP_ATOMIC;
	int swc_nents, mapped_swc_nents, dst_nents = 0, mapped_dst_nents = 0;
	stwuct skciphew_edesc *edesc;
	dma_addw_t iv_dma;
	u8 *iv;
	int ivsize = cwypto_skciphew_ivsize(skciphew);
	int dst_sg_idx, qm_sg_ents, qm_sg_bytes;
	stwuct qm_sg_entwy *sg_tabwe, *fd_sgt;
	stwuct caam_dwv_ctx *dwv_ctx;
	unsigned int wen;

	dwv_ctx = get_dwv_ctx(ctx, encwypt ? ENCWYPT : DECWYPT);
	if (IS_EWW(dwv_ctx))
		wetuwn (stwuct skciphew_edesc *)dwv_ctx;

	swc_nents = sg_nents_fow_wen(weq->swc, weq->cwyptwen);
	if (unwikewy(swc_nents < 0)) {
		dev_eww(qidev, "Insufficient bytes (%d) in swc S/G\n",
			weq->cwyptwen);
		wetuwn EWW_PTW(swc_nents);
	}

	if (unwikewy(weq->swc != weq->dst)) {
		dst_nents = sg_nents_fow_wen(weq->dst, weq->cwyptwen);
		if (unwikewy(dst_nents < 0)) {
			dev_eww(qidev, "Insufficient bytes (%d) in dst S/G\n",
				weq->cwyptwen);
			wetuwn EWW_PTW(dst_nents);
		}

		mapped_swc_nents = dma_map_sg(qidev, weq->swc, swc_nents,
					      DMA_TO_DEVICE);
		if (unwikewy(!mapped_swc_nents)) {
			dev_eww(qidev, "unabwe to map souwce\n");
			wetuwn EWW_PTW(-ENOMEM);
		}

		mapped_dst_nents = dma_map_sg(qidev, weq->dst, dst_nents,
					      DMA_FWOM_DEVICE);
		if (unwikewy(!mapped_dst_nents)) {
			dev_eww(qidev, "unabwe to map destination\n");
			dma_unmap_sg(qidev, weq->swc, swc_nents, DMA_TO_DEVICE);
			wetuwn EWW_PTW(-ENOMEM);
		}
	} ewse {
		mapped_swc_nents = dma_map_sg(qidev, weq->swc, swc_nents,
					      DMA_BIDIWECTIONAW);
		if (unwikewy(!mapped_swc_nents)) {
			dev_eww(qidev, "unabwe to map souwce\n");
			wetuwn EWW_PTW(-ENOMEM);
		}
	}

	qm_sg_ents = 1 + mapped_swc_nents;
	dst_sg_idx = qm_sg_ents;

	/*
	 * Input, output HW S/G tabwes: [IV, swc][dst, IV]
	 * IV entwies point to the same buffew
	 * If swc == dst, S/G entwies awe weused (S/G tabwes ovewwap)
	 *
	 * HW weads 4 S/G entwies at a time; make suwe the weads don't go beyond
	 * the end of the tabwe by awwocating mowe S/G entwies.
	 */
	if (weq->swc != weq->dst)
		qm_sg_ents += pad_sg_nents(mapped_dst_nents + 1);
	ewse
		qm_sg_ents = 1 + pad_sg_nents(qm_sg_ents);

	qm_sg_bytes = qm_sg_ents * sizeof(stwuct qm_sg_entwy);

	wen = offsetof(stwuct skciphew_edesc, sgt) + qm_sg_bytes;
	wen = AWIGN(wen, dma_get_cache_awignment());
	wen += ivsize;

	if (unwikewy(wen > CAAM_QI_MEMCACHE_SIZE)) {
		dev_eww(qidev, "No space fow %d S/G entwies and/ow %dB IV\n",
			qm_sg_ents, ivsize);
		caam_unmap(qidev, weq->swc, weq->dst, swc_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* awwocate space fow base edesc, wink tabwes and IV */
	edesc = qi_cache_awwoc(fwags);
	if (unwikewy(!edesc)) {
		dev_eww(qidev, "couwd not awwocate extended descwiptow\n");
		caam_unmap(qidev, weq->swc, weq->dst, swc_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		wetuwn EWW_PTW(-ENOMEM);
	}

	edesc->swc_nents = swc_nents;
	edesc->dst_nents = dst_nents;
	edesc->qm_sg_bytes = qm_sg_bytes;
	edesc->dwv_weq.app_ctx = weq;
	edesc->dwv_weq.cbk = skciphew_done;
	edesc->dwv_weq.dwv_ctx = dwv_ctx;

	/* Make suwe IV is wocated in a DMAabwe awea */
	sg_tabwe = &edesc->sgt[0];
	iv = skciphew_edesc_iv(edesc);
	memcpy(iv, weq->iv, ivsize);

	iv_dma = dma_map_singwe(qidev, iv, ivsize, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(qidev, iv_dma)) {
		dev_eww(qidev, "unabwe to map IV\n");
		caam_unmap(qidev, weq->swc, weq->dst, swc_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		qi_cache_fwee(edesc);
		wetuwn EWW_PTW(-ENOMEM);
	}

	edesc->iv_dma = iv_dma;

	dma_to_qm_sg_one(sg_tabwe, iv_dma, ivsize, 0);
	sg_to_qm_sg(weq->swc, weq->cwyptwen, sg_tabwe + 1, 0);

	if (weq->swc != weq->dst)
		sg_to_qm_sg(weq->dst, weq->cwyptwen, sg_tabwe + dst_sg_idx, 0);

	dma_to_qm_sg_one(sg_tabwe + dst_sg_idx + mapped_dst_nents, iv_dma,
			 ivsize, 0);

	edesc->qm_sg_dma = dma_map_singwe(qidev, sg_tabwe, edesc->qm_sg_bytes,
					  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(qidev, edesc->qm_sg_dma)) {
		dev_eww(qidev, "unabwe to map S/G tabwe\n");
		caam_unmap(qidev, weq->swc, weq->dst, swc_nents, dst_nents,
			   iv_dma, ivsize, DMA_BIDIWECTIONAW, 0, 0);
		qi_cache_fwee(edesc);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fd_sgt = &edesc->dwv_weq.fd_sgt[0];

	dma_to_qm_sg_one_wast_ext(&fd_sgt[1], edesc->qm_sg_dma,
				  ivsize + weq->cwyptwen, 0);

	if (weq->swc == weq->dst)
		dma_to_qm_sg_one_ext(&fd_sgt[0], edesc->qm_sg_dma +
				     sizeof(*sg_tabwe), weq->cwyptwen + ivsize,
				     0);
	ewse
		dma_to_qm_sg_one_ext(&fd_sgt[0], edesc->qm_sg_dma + dst_sg_idx *
				     sizeof(*sg_tabwe), weq->cwyptwen + ivsize,
				     0);

	wetuwn edesc;
}

static inwine boow xts_skciphew_ivsize(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	unsigned int ivsize = cwypto_skciphew_ivsize(skciphew);

	wetuwn !!get_unawigned((u64 *)(weq->iv + (ivsize / 2)));
}

static inwine int skciphew_cwypt(stwuct skciphew_wequest *weq, boow encwypt)
{
	stwuct skciphew_edesc *edesc;
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	stwuct caam_ctx *ctx = cwypto_skciphew_ctx_dma(skciphew);
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(ctx->jwdev->pawent);
	int wet;

	/*
	 * XTS is expected to wetuwn an ewwow even fow input wength = 0
	 * Note that the case input wength < bwock size wiww be caught duwing
	 * HW offwoading and wetuwn an ewwow.
	 */
	if (!weq->cwyptwen && !ctx->fawwback)
		wetuwn 0;

	if (ctx->fawwback && ((ctwwpwiv->ewa <= 8 && xts_skciphew_ivsize(weq)) ||
			      ctx->xts_key_fawwback)) {
		stwuct caam_skciphew_weq_ctx *wctx = skciphew_wequest_ctx(weq);

		skciphew_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback);
		skciphew_wequest_set_cawwback(&wctx->fawwback_weq,
					      weq->base.fwags,
					      weq->base.compwete,
					      weq->base.data);
		skciphew_wequest_set_cwypt(&wctx->fawwback_weq, weq->swc,
					   weq->dst, weq->cwyptwen, weq->iv);

		wetuwn encwypt ? cwypto_skciphew_encwypt(&wctx->fawwback_weq) :
				 cwypto_skciphew_decwypt(&wctx->fawwback_weq);
	}

	if (unwikewy(caam_congested))
		wetuwn -EAGAIN;

	/* awwocate extended descwiptow */
	edesc = skciphew_edesc_awwoc(weq, encwypt);
	if (IS_EWW(edesc))
		wetuwn PTW_EWW(edesc);

	wet = caam_qi_enqueue(ctx->qidev, &edesc->dwv_weq);
	if (!wet) {
		wet = -EINPWOGWESS;
	} ewse {
		skciphew_unmap(ctx->qidev, edesc, weq);
		qi_cache_fwee(edesc);
	}

	wetuwn wet;
}

static int skciphew_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn skciphew_cwypt(weq, twue);
}

static int skciphew_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn skciphew_cwypt(weq, fawse);
}

static stwuct caam_skciphew_awg dwivew_awgs[] = {
	{
		.skciphew = {
			.base = {
				.cwa_name = "cbc(aes)",
				.cwa_dwivew_name = "cbc-aes-caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aes_skciphew_setkey,
			.encwypt = skciphew_encwypt,
			.decwypt = skciphew_decwypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
		},
		.caam.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
	},
	{
		.skciphew = {
			.base = {
				.cwa_name = "cbc(des3_ede)",
				.cwa_dwivew_name = "cbc-3des-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_skciphew_setkey,
			.encwypt = skciphew_encwypt,
			.decwypt = skciphew_decwypt,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = DES3_EDE_BWOCK_SIZE,
		},
		.caam.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
	},
	{
		.skciphew = {
			.base = {
				.cwa_name = "cbc(des)",
				.cwa_dwivew_name = "cbc-des-caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = des_skciphew_setkey,
			.encwypt = skciphew_encwypt,
			.decwypt = skciphew_decwypt,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = DES_BWOCK_SIZE,
		},
		.caam.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
	},
	{
		.skciphew = {
			.base = {
				.cwa_name = "ctw(aes)",
				.cwa_dwivew_name = "ctw-aes-caam-qi",
				.cwa_bwocksize = 1,
			},
			.setkey = ctw_skciphew_setkey,
			.encwypt = skciphew_encwypt,
			.decwypt = skciphew_decwypt,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
			.chunksize = AES_BWOCK_SIZE,
		},
		.caam.cwass1_awg_type = OP_AWG_AWGSEW_AES |
					OP_AWG_AAI_CTW_MOD128,
	},
	{
		.skciphew = {
			.base = {
				.cwa_name = "wfc3686(ctw(aes))",
				.cwa_dwivew_name = "wfc3686-ctw-aes-caam-qi",
				.cwa_bwocksize = 1,
			},
			.setkey = wfc3686_skciphew_setkey,
			.encwypt = skciphew_encwypt,
			.decwypt = skciphew_decwypt,
			.min_keysize = AES_MIN_KEY_SIZE +
				       CTW_WFC3686_NONCE_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE +
				       CTW_WFC3686_NONCE_SIZE,
			.ivsize = CTW_WFC3686_IV_SIZE,
			.chunksize = AES_BWOCK_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES |
					   OP_AWG_AAI_CTW_MOD128,
			.wfc3686 = twue,
		},
	},
	{
		.skciphew = {
			.base = {
				.cwa_name = "xts(aes)",
				.cwa_dwivew_name = "xts-aes-caam-qi",
				.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK,
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = xts_skciphew_setkey,
			.encwypt = skciphew_encwypt,
			.decwypt = skciphew_decwypt,
			.min_keysize = 2 * AES_MIN_KEY_SIZE,
			.max_keysize = 2 * AES_MAX_KEY_SIZE,
			.ivsize = AES_BWOCK_SIZE,
		},
		.caam.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_XTS,
	},
};

static stwuct caam_aead_awg dwivew_aeads[] = {
	{
		.aead = {
			.base = {
				.cwa_name = "wfc4106(gcm(aes))",
				.cwa_dwivew_name = "wfc4106-gcm-aes-caam-qi",
				.cwa_bwocksize = 1,
			},
			.setkey = wfc4106_setkey,
			.setauthsize = wfc4106_setauthsize,
			.encwypt = ipsec_gcm_encwypt,
			.decwypt = ipsec_gcm_decwypt,
			.ivsize = 8,
			.maxauthsize = AES_BWOCK_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_GCM,
			.nodkp = twue,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "wfc4543(gcm(aes))",
				.cwa_dwivew_name = "wfc4543-gcm-aes-caam-qi",
				.cwa_bwocksize = 1,
			},
			.setkey = wfc4543_setkey,
			.setauthsize = wfc4543_setauthsize,
			.encwypt = ipsec_gcm_encwypt,
			.decwypt = ipsec_gcm_decwypt,
			.ivsize = 8,
			.maxauthsize = AES_BWOCK_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_GCM,
			.nodkp = twue,
		},
	},
	/* Gawois Countew Mode */
	{
		.aead = {
			.base = {
				.cwa_name = "gcm(aes)",
				.cwa_dwivew_name = "gcm-aes-caam-qi",
				.cwa_bwocksize = 1,
			},
			.setkey = gcm_setkey,
			.setauthsize = gcm_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = 12,
			.maxauthsize = AES_BWOCK_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_GCM,
			.nodkp = twue,
		}
	},
	/* singwe-pass ipsec_esp descwiptow */
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(md5),cbc(aes))",
				.cwa_dwivew_name = "authenc-hmac-md5-"
						   "cbc-aes-caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_MD5 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(md5),"
					    "cbc(aes)))",
				.cwa_dwivew_name = "echainiv-authenc-hmac-md5-"
						   "cbc-aes-caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_MD5 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha1),cbc(aes))",
				.cwa_dwivew_name = "authenc-hmac-sha1-"
						   "cbc-aes-caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA1 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha1),"
					    "cbc(aes)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha1-cbc-aes-caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA1 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha224),cbc(aes))",
				.cwa_dwivew_name = "authenc-hmac-sha224-"
						   "cbc-aes-caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA224 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha224),"
					    "cbc(aes)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha224-cbc-aes-caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA224 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha256),cbc(aes))",
				.cwa_dwivew_name = "authenc-hmac-sha256-"
						   "cbc-aes-caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA256 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha256),"
					    "cbc(aes)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha256-cbc-aes-"
						   "caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA256 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha384),cbc(aes))",
				.cwa_dwivew_name = "authenc-hmac-sha384-"
						   "cbc-aes-caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA384 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha384),"
					    "cbc(aes)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha384-cbc-aes-"
						   "caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA384 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha512),cbc(aes))",
				.cwa_dwivew_name = "authenc-hmac-sha512-"
						   "cbc-aes-caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA512 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha512),"
					    "cbc(aes)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha512-cbc-aes-"
						   "caam-qi",
				.cwa_bwocksize = AES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = AES_BWOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_AES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA512 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(md5),cbc(des3_ede))",
				.cwa_dwivew_name = "authenc-hmac-md5-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_MD5 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(md5),"
					    "cbc(des3_ede)))",
				.cwa_dwivew_name = "echainiv-authenc-hmac-md5-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_MD5 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha1),"
					    "cbc(des3_ede))",
				.cwa_dwivew_name = "authenc-hmac-sha1-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA1 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha1),"
					    "cbc(des3_ede)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha1-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA1 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha224),"
					    "cbc(des3_ede))",
				.cwa_dwivew_name = "authenc-hmac-sha224-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA224 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha224),"
					    "cbc(des3_ede)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha224-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA224 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha256),"
					    "cbc(des3_ede))",
				.cwa_dwivew_name = "authenc-hmac-sha256-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA256 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha256),"
					    "cbc(des3_ede)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha256-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA256 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha384),"
					    "cbc(des3_ede))",
				.cwa_dwivew_name = "authenc-hmac-sha384-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA384 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha384),"
					    "cbc(des3_ede)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha384-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA384 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha512),"
					    "cbc(des3_ede))",
				.cwa_dwivew_name = "authenc-hmac-sha512-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA512 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha512),"
					    "cbc(des3_ede)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha512-"
						   "cbc-des3_ede-caam-qi",
				.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			},
			.setkey = des3_aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES3_EDE_BWOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_3DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA512 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(md5),cbc(des))",
				.cwa_dwivew_name = "authenc-hmac-md5-"
						   "cbc-des-caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_MD5 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(md5),"
					    "cbc(des)))",
				.cwa_dwivew_name = "echainiv-authenc-hmac-md5-"
						   "cbc-des-caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = MD5_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_MD5 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha1),cbc(des))",
				.cwa_dwivew_name = "authenc-hmac-sha1-"
						   "cbc-des-caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA1 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha1),"
					    "cbc(des)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha1-cbc-des-caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA1 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha224),cbc(des))",
				.cwa_dwivew_name = "authenc-hmac-sha224-"
						   "cbc-des-caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA224 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha224),"
					    "cbc(des)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha224-cbc-des-"
						   "caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA224 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha256),cbc(des))",
				.cwa_dwivew_name = "authenc-hmac-sha256-"
						   "cbc-des-caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA256 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha256),"
					    "cbc(des)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha256-cbc-des-"
						   "caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA256 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha384),cbc(des))",
				.cwa_dwivew_name = "authenc-hmac-sha384-"
						   "cbc-des-caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA384 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		},
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha384),"
					    "cbc(des)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha384-cbc-des-"
						   "caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA384 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "authenc(hmac(sha512),cbc(des))",
				.cwa_dwivew_name = "authenc-hmac-sha512-"
						   "cbc-des-caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA512 |
					   OP_AWG_AAI_HMAC_PWECOMP,
		}
	},
	{
		.aead = {
			.base = {
				.cwa_name = "echainiv(authenc(hmac(sha512),"
					    "cbc(des)))",
				.cwa_dwivew_name = "echainiv-authenc-"
						   "hmac-sha512-cbc-des-"
						   "caam-qi",
				.cwa_bwocksize = DES_BWOCK_SIZE,
			},
			.setkey = aead_setkey,
			.setauthsize = aead_setauthsize,
			.encwypt = aead_encwypt,
			.decwypt = aead_decwypt,
			.ivsize = DES_BWOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
		},
		.caam = {
			.cwass1_awg_type = OP_AWG_AWGSEW_DES | OP_AWG_AAI_CBC,
			.cwass2_awg_type = OP_AWG_AWGSEW_SHA512 |
					   OP_AWG_AAI_HMAC_PWECOMP,
			.geniv = twue,
		}
	},
};

static int caam_init_common(stwuct caam_ctx *ctx, stwuct caam_awg_entwy *caam,
			    boow uses_dkp)
{
	stwuct caam_dwv_pwivate *pwiv;
	stwuct device *dev;

	/*
	 * distwibute tfms acwoss job wings to ensuwe in-owdew
	 * cwypto wequest pwocessing pew tfm
	 */
	ctx->jwdev = caam_jw_awwoc();
	if (IS_EWW(ctx->jwdev)) {
		pw_eww("Job Wing Device awwocation fow twansfowm faiwed\n");
		wetuwn PTW_EWW(ctx->jwdev);
	}

	dev = ctx->jwdev->pawent;
	pwiv = dev_get_dwvdata(dev);
	if (pwiv->ewa >= 6 && uses_dkp)
		ctx->diw = DMA_BIDIWECTIONAW;
	ewse
		ctx->diw = DMA_TO_DEVICE;

	ctx->key_dma = dma_map_singwe(dev, ctx->key, sizeof(ctx->key),
				      ctx->diw);
	if (dma_mapping_ewwow(dev, ctx->key_dma)) {
		dev_eww(dev, "unabwe to map key\n");
		caam_jw_fwee(ctx->jwdev);
		wetuwn -ENOMEM;
	}

	/* copy descwiptow headew tempwate vawue */
	ctx->cdata.awgtype = OP_TYPE_CWASS1_AWG | caam->cwass1_awg_type;
	ctx->adata.awgtype = OP_TYPE_CWASS2_AWG | caam->cwass2_awg_type;

	ctx->qidev = dev;

	spin_wock_init(&ctx->wock);
	ctx->dwv_ctx[ENCWYPT] = NUWW;
	ctx->dwv_ctx[DECWYPT] = NUWW;

	wetuwn 0;
}

static int caam_cwa_init(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct caam_skciphew_awg *caam_awg =
		containew_of(awg, typeof(*caam_awg), skciphew);
	stwuct caam_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);
	u32 awg_aai = caam_awg->caam.cwass1_awg_type & OP_AWG_AAI_MASK;
	int wet = 0;

	if (awg_aai == OP_AWG_AAI_XTS) {
		const chaw *tfm_name = cwypto_tfm_awg_name(&tfm->base);
		stwuct cwypto_skciphew *fawwback;

		fawwback = cwypto_awwoc_skciphew(tfm_name, 0,
						 CWYPTO_AWG_NEED_FAWWBACK);
		if (IS_EWW(fawwback)) {
			pw_eww("Faiwed to awwocate %s fawwback: %wd\n",
			       tfm_name, PTW_EWW(fawwback));
			wetuwn PTW_EWW(fawwback);
		}

		ctx->fawwback = fawwback;
		cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct caam_skciphew_weq_ctx) +
					    cwypto_skciphew_weqsize(fawwback));
	}

	wet = caam_init_common(ctx, &caam_awg->caam, fawse);
	if (wet && ctx->fawwback)
		cwypto_fwee_skciphew(ctx->fawwback);

	wetuwn wet;
}

static int caam_aead_init(stwuct cwypto_aead *tfm)
{
	stwuct aead_awg *awg = cwypto_aead_awg(tfm);
	stwuct caam_aead_awg *caam_awg = containew_of(awg, typeof(*caam_awg),
						      aead);
	stwuct caam_ctx *ctx = cwypto_aead_ctx_dma(tfm);

	wetuwn caam_init_common(ctx, &caam_awg->caam, !caam_awg->caam.nodkp);
}

static void caam_exit_common(stwuct caam_ctx *ctx)
{
	caam_dwv_ctx_wew(ctx->dwv_ctx[ENCWYPT]);
	caam_dwv_ctx_wew(ctx->dwv_ctx[DECWYPT]);

	dma_unmap_singwe(ctx->jwdev->pawent, ctx->key_dma, sizeof(ctx->key),
			 ctx->diw);

	caam_jw_fwee(ctx->jwdev);
}

static void caam_cwa_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct caam_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);

	if (ctx->fawwback)
		cwypto_fwee_skciphew(ctx->fawwback);
	caam_exit_common(ctx);
}

static void caam_aead_exit(stwuct cwypto_aead *tfm)
{
	caam_exit_common(cwypto_aead_ctx_dma(tfm));
}

void caam_qi_awgapi_exit(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dwivew_aeads); i++) {
		stwuct caam_aead_awg *t_awg = dwivew_aeads + i;

		if (t_awg->wegistewed)
			cwypto_unwegistew_aead(&t_awg->aead);
	}

	fow (i = 0; i < AWWAY_SIZE(dwivew_awgs); i++) {
		stwuct caam_skciphew_awg *t_awg = dwivew_awgs + i;

		if (t_awg->wegistewed)
			cwypto_unwegistew_skciphew(&t_awg->skciphew);
	}
}

static void caam_skciphew_awg_init(stwuct caam_skciphew_awg *t_awg)
{
	stwuct skciphew_awg *awg = &t_awg->skciphew;

	awg->base.cwa_moduwe = THIS_MODUWE;
	awg->base.cwa_pwiowity = CAAM_CWA_PWIOWITY;
	awg->base.cwa_ctxsize = sizeof(stwuct caam_ctx) + cwypto_dma_padding();
	awg->base.cwa_fwags |= (CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY |
				CWYPTO_AWG_KEWN_DWIVEW_ONWY);

	awg->init = caam_cwa_init;
	awg->exit = caam_cwa_exit;
}

static void caam_aead_awg_init(stwuct caam_aead_awg *t_awg)
{
	stwuct aead_awg *awg = &t_awg->aead;

	awg->base.cwa_moduwe = THIS_MODUWE;
	awg->base.cwa_pwiowity = CAAM_CWA_PWIOWITY;
	awg->base.cwa_ctxsize = sizeof(stwuct caam_ctx) + cwypto_dma_padding();
	awg->base.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY |
			      CWYPTO_AWG_KEWN_DWIVEW_ONWY;

	awg->init = caam_aead_init;
	awg->exit = caam_aead_exit;
}

int caam_qi_awgapi_init(stwuct device *ctwwdev)
{
	stwuct caam_dwv_pwivate *pwiv = dev_get_dwvdata(ctwwdev);
	int i = 0, eww = 0;
	u32 aes_vid, aes_inst, des_inst, md_vid, md_inst;
	unsigned int md_wimit = SHA512_DIGEST_SIZE;
	boow wegistewed = fawse;

	/* Make suwe this wuns onwy on (DPAA 1.x) QI */
	if (!pwiv->qi_pwesent || caam_dpaa2)
		wetuwn 0;

	/*
	 * Wegistew cwypto awgowithms the device suppowts.
	 * Fiwst, detect pwesence and attwibutes of DES, AES, and MD bwocks.
	 */
	if (pwiv->ewa < 10) {
		u32 cha_vid, cha_inst;

		cha_vid = wd_weg32(&pwiv->ctww->pewfmon.cha_id_ws);
		aes_vid = cha_vid & CHA_ID_WS_AES_MASK;
		md_vid = (cha_vid & CHA_ID_WS_MD_MASK) >> CHA_ID_WS_MD_SHIFT;

		cha_inst = wd_weg32(&pwiv->ctww->pewfmon.cha_num_ws);
		des_inst = (cha_inst & CHA_ID_WS_DES_MASK) >>
			   CHA_ID_WS_DES_SHIFT;
		aes_inst = cha_inst & CHA_ID_WS_AES_MASK;
		md_inst = (cha_inst & CHA_ID_WS_MD_MASK) >> CHA_ID_WS_MD_SHIFT;
	} ewse {
		u32 aesa, mdha;

		aesa = wd_weg32(&pwiv->ctww->vweg.aesa);
		mdha = wd_weg32(&pwiv->ctww->vweg.mdha);

		aes_vid = (aesa & CHA_VEW_VID_MASK) >> CHA_VEW_VID_SHIFT;
		md_vid = (mdha & CHA_VEW_VID_MASK) >> CHA_VEW_VID_SHIFT;

		des_inst = wd_weg32(&pwiv->ctww->vweg.desa) & CHA_VEW_NUM_MASK;
		aes_inst = aesa & CHA_VEW_NUM_MASK;
		md_inst = mdha & CHA_VEW_NUM_MASK;
	}

	/* If MD is pwesent, wimit digest size based on WP256 */
	if (md_inst && md_vid  == CHA_VEW_VID_MD_WP256)
		md_wimit = SHA256_DIGEST_SIZE;

	fow (i = 0; i < AWWAY_SIZE(dwivew_awgs); i++) {
		stwuct caam_skciphew_awg *t_awg = dwivew_awgs + i;
		u32 awg_sew = t_awg->caam.cwass1_awg_type & OP_AWG_AWGSEW_MASK;

		/* Skip DES awgowithms if not suppowted by device */
		if (!des_inst &&
		    ((awg_sew == OP_AWG_AWGSEW_3DES) ||
		     (awg_sew == OP_AWG_AWGSEW_DES)))
			continue;

		/* Skip AES awgowithms if not suppowted by device */
		if (!aes_inst && (awg_sew == OP_AWG_AWGSEW_AES))
			continue;

		caam_skciphew_awg_init(t_awg);

		eww = cwypto_wegistew_skciphew(&t_awg->skciphew);
		if (eww) {
			dev_wawn(ctwwdev, "%s awg wegistwation faiwed\n",
				 t_awg->skciphew.base.cwa_dwivew_name);
			continue;
		}

		t_awg->wegistewed = twue;
		wegistewed = twue;
	}

	fow (i = 0; i < AWWAY_SIZE(dwivew_aeads); i++) {
		stwuct caam_aead_awg *t_awg = dwivew_aeads + i;
		u32 c1_awg_sew = t_awg->caam.cwass1_awg_type &
				 OP_AWG_AWGSEW_MASK;
		u32 c2_awg_sew = t_awg->caam.cwass2_awg_type &
				 OP_AWG_AWGSEW_MASK;
		u32 awg_aai = t_awg->caam.cwass1_awg_type & OP_AWG_AAI_MASK;

		/* Skip DES awgowithms if not suppowted by device */
		if (!des_inst &&
		    ((c1_awg_sew == OP_AWG_AWGSEW_3DES) ||
		     (c1_awg_sew == OP_AWG_AWGSEW_DES)))
			continue;

		/* Skip AES awgowithms if not suppowted by device */
		if (!aes_inst && (c1_awg_sew == OP_AWG_AWGSEW_AES))
			continue;

		/*
		 * Check suppowt fow AES awgowithms not avaiwabwe
		 * on WP devices.
		 */
		if (aes_vid  == CHA_VEW_VID_AES_WP && awg_aai == OP_AWG_AAI_GCM)
			continue;

		/*
		 * Skip awgowithms wequiwing message digests
		 * if MD ow MD size is not suppowted by device.
		 */
		if (c2_awg_sew &&
		    (!md_inst || (t_awg->aead.maxauthsize > md_wimit)))
			continue;

		caam_aead_awg_init(t_awg);

		eww = cwypto_wegistew_aead(&t_awg->aead);
		if (eww) {
			pw_wawn("%s awg wegistwation faiwed\n",
				t_awg->aead.base.cwa_dwivew_name);
			continue;
		}

		t_awg->wegistewed = twue;
		wegistewed = twue;
	}

	if (wegistewed)
		dev_info(ctwwdev, "awgowithms wegistewed in /pwoc/cwypto\n");

	wetuwn eww;
}
