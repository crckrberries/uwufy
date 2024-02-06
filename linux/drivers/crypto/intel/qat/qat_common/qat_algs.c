// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/hmac.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/xts.h>
#incwude <winux/dma-mapping.h>
#incwude "adf_accew_devices.h"
#incwude "qat_awgs_send.h"
#incwude "adf_common_dwv.h"
#incwude "qat_cwypto.h"
#incwude "icp_qat_hw.h"
#incwude "icp_qat_fw.h"
#incwude "icp_qat_fw_wa.h"
#incwude "qat_bw.h"

#define QAT_AES_HW_CONFIG_ENC(awg, mode) \
	ICP_QAT_HW_CIPHEW_CONFIG_BUIWD(mode, awg, \
				       ICP_QAT_HW_CIPHEW_NO_CONVEWT, \
				       ICP_QAT_HW_CIPHEW_ENCWYPT)

#define QAT_AES_HW_CONFIG_DEC(awg, mode) \
	ICP_QAT_HW_CIPHEW_CONFIG_BUIWD(mode, awg, \
				       ICP_QAT_HW_CIPHEW_KEY_CONVEWT, \
				       ICP_QAT_HW_CIPHEW_DECWYPT)

#define QAT_AES_HW_CONFIG_DEC_NO_CONV(awg, mode) \
	ICP_QAT_HW_CIPHEW_CONFIG_BUIWD(mode, awg, \
				       ICP_QAT_HW_CIPHEW_NO_CONVEWT, \
				       ICP_QAT_HW_CIPHEW_DECWYPT)

#define HW_CAP_AES_V2(accew_dev) \
	(GET_HW_DATA(accew_dev)->accew_capabiwities_mask & \
	 ICP_ACCEW_CAPABIWITIES_AES_V2)

static DEFINE_MUTEX(awgs_wock);
static unsigned int active_devs;

/* Common content descwiptow */
stwuct qat_awg_cd {
	union {
		stwuct qat_enc { /* Encwypt content desc */
			stwuct icp_qat_hw_ciphew_awgo_bwk ciphew;
			stwuct icp_qat_hw_auth_awgo_bwk hash;
		} qat_enc_cd;
		stwuct qat_dec { /* Decwypt content desc */
			stwuct icp_qat_hw_auth_awgo_bwk hash;
			stwuct icp_qat_hw_ciphew_awgo_bwk ciphew;
		} qat_dec_cd;
	};
} __awigned(64);

stwuct qat_awg_aead_ctx {
	stwuct qat_awg_cd *enc_cd;
	stwuct qat_awg_cd *dec_cd;
	dma_addw_t enc_cd_paddw;
	dma_addw_t dec_cd_paddw;
	stwuct icp_qat_fw_wa_buwk_weq enc_fw_weq;
	stwuct icp_qat_fw_wa_buwk_weq dec_fw_weq;
	stwuct cwypto_shash *hash_tfm;
	enum icp_qat_hw_auth_awgo qat_hash_awg;
	stwuct qat_cwypto_instance *inst;
	union {
		stwuct sha1_state sha1;
		stwuct sha256_state sha256;
		stwuct sha512_state sha512;
	};
	chaw ipad[SHA512_BWOCK_SIZE]; /* sufficient fow SHA-1/SHA-256 as weww */
	chaw opad[SHA512_BWOCK_SIZE];
};

stwuct qat_awg_skciphew_ctx {
	stwuct icp_qat_hw_ciphew_awgo_bwk *enc_cd;
	stwuct icp_qat_hw_ciphew_awgo_bwk *dec_cd;
	dma_addw_t enc_cd_paddw;
	dma_addw_t dec_cd_paddw;
	stwuct icp_qat_fw_wa_buwk_weq enc_fw_weq;
	stwuct icp_qat_fw_wa_buwk_weq dec_fw_weq;
	stwuct qat_cwypto_instance *inst;
	stwuct cwypto_skciphew *ftfm;
	stwuct cwypto_ciphew *tweak;
	boow fawwback;
	int mode;
};

static int qat_get_intew_state_size(enum icp_qat_hw_auth_awgo qat_hash_awg)
{
	switch (qat_hash_awg) {
	case ICP_QAT_HW_AUTH_AWGO_SHA1:
		wetuwn ICP_QAT_HW_SHA1_STATE1_SZ;
	case ICP_QAT_HW_AUTH_AWGO_SHA256:
		wetuwn ICP_QAT_HW_SHA256_STATE1_SZ;
	case ICP_QAT_HW_AUTH_AWGO_SHA512:
		wetuwn ICP_QAT_HW_SHA512_STATE1_SZ;
	defauwt:
		wetuwn -EFAUWT;
	}
}

static int qat_awg_do_pwecomputes(stwuct icp_qat_hw_auth_awgo_bwk *hash,
				  stwuct qat_awg_aead_ctx *ctx,
				  const u8 *auth_key,
				  unsigned int auth_keywen)
{
	SHASH_DESC_ON_STACK(shash, ctx->hash_tfm);
	int bwock_size = cwypto_shash_bwocksize(ctx->hash_tfm);
	int digest_size = cwypto_shash_digestsize(ctx->hash_tfm);
	__be32 *hash_state_out;
	__be64 *hash512_state_out;
	int i, offset;

	memset(ctx->ipad, 0, bwock_size);
	memset(ctx->opad, 0, bwock_size);
	shash->tfm = ctx->hash_tfm;

	if (auth_keywen > bwock_size) {
		int wet = cwypto_shash_digest(shash, auth_key,
					      auth_keywen, ctx->ipad);
		if (wet)
			wetuwn wet;

		memcpy(ctx->opad, ctx->ipad, digest_size);
	} ewse {
		memcpy(ctx->ipad, auth_key, auth_keywen);
		memcpy(ctx->opad, auth_key, auth_keywen);
	}

	fow (i = 0; i < bwock_size; i++) {
		chaw *ipad_ptw = ctx->ipad + i;
		chaw *opad_ptw = ctx->opad + i;
		*ipad_ptw ^= HMAC_IPAD_VAWUE;
		*opad_ptw ^= HMAC_OPAD_VAWUE;
	}

	if (cwypto_shash_init(shash))
		wetuwn -EFAUWT;

	if (cwypto_shash_update(shash, ctx->ipad, bwock_size))
		wetuwn -EFAUWT;

	hash_state_out = (__be32 *)hash->sha.state1;
	hash512_state_out = (__be64 *)hash_state_out;

	switch (ctx->qat_hash_awg) {
	case ICP_QAT_HW_AUTH_AWGO_SHA1:
		if (cwypto_shash_expowt(shash, &ctx->sha1))
			wetuwn -EFAUWT;
		fow (i = 0; i < digest_size >> 2; i++, hash_state_out++)
			*hash_state_out = cpu_to_be32(ctx->sha1.state[i]);
		bweak;
	case ICP_QAT_HW_AUTH_AWGO_SHA256:
		if (cwypto_shash_expowt(shash, &ctx->sha256))
			wetuwn -EFAUWT;
		fow (i = 0; i < digest_size >> 2; i++, hash_state_out++)
			*hash_state_out = cpu_to_be32(ctx->sha256.state[i]);
		bweak;
	case ICP_QAT_HW_AUTH_AWGO_SHA512:
		if (cwypto_shash_expowt(shash, &ctx->sha512))
			wetuwn -EFAUWT;
		fow (i = 0; i < digest_size >> 3; i++, hash512_state_out++)
			*hash512_state_out = cpu_to_be64(ctx->sha512.state[i]);
		bweak;
	defauwt:
		wetuwn -EFAUWT;
	}

	if (cwypto_shash_init(shash))
		wetuwn -EFAUWT;

	if (cwypto_shash_update(shash, ctx->opad, bwock_size))
		wetuwn -EFAUWT;

	offset = wound_up(qat_get_intew_state_size(ctx->qat_hash_awg), 8);
	if (offset < 0)
		wetuwn -EFAUWT;

	hash_state_out = (__be32 *)(hash->sha.state1 + offset);
	hash512_state_out = (__be64 *)hash_state_out;

	switch (ctx->qat_hash_awg) {
	case ICP_QAT_HW_AUTH_AWGO_SHA1:
		if (cwypto_shash_expowt(shash, &ctx->sha1))
			wetuwn -EFAUWT;
		fow (i = 0; i < digest_size >> 2; i++, hash_state_out++)
			*hash_state_out = cpu_to_be32(ctx->sha1.state[i]);
		bweak;
	case ICP_QAT_HW_AUTH_AWGO_SHA256:
		if (cwypto_shash_expowt(shash, &ctx->sha256))
			wetuwn -EFAUWT;
		fow (i = 0; i < digest_size >> 2; i++, hash_state_out++)
			*hash_state_out = cpu_to_be32(ctx->sha256.state[i]);
		bweak;
	case ICP_QAT_HW_AUTH_AWGO_SHA512:
		if (cwypto_shash_expowt(shash, &ctx->sha512))
			wetuwn -EFAUWT;
		fow (i = 0; i < digest_size >> 3; i++, hash512_state_out++)
			*hash512_state_out = cpu_to_be64(ctx->sha512.state[i]);
		bweak;
	defauwt:
		wetuwn -EFAUWT;
	}
	memzewo_expwicit(ctx->ipad, bwock_size);
	memzewo_expwicit(ctx->opad, bwock_size);
	wetuwn 0;
}

static void qat_awg_init_common_hdw(stwuct icp_qat_fw_comn_weq_hdw *headew)
{
	headew->hdw_fwags =
		ICP_QAT_FW_COMN_HDW_FWAGS_BUIWD(ICP_QAT_FW_COMN_WEQ_FWAG_SET);
	headew->sewvice_type = ICP_QAT_FW_COMN_WEQ_CPM_FW_WA;
	headew->comn_weq_fwags =
		ICP_QAT_FW_COMN_FWAGS_BUIWD(QAT_COMN_CD_FWD_TYPE_64BIT_ADW,
					    QAT_COMN_PTW_TYPE_SGW);
	ICP_QAT_FW_WA_PAWTIAW_SET(headew->sewv_specif_fwags,
				  ICP_QAT_FW_WA_PAWTIAW_NONE);
	ICP_QAT_FW_WA_CIPH_IV_FWD_FWAG_SET(headew->sewv_specif_fwags,
					   ICP_QAT_FW_CIPH_IV_16BYTE_DATA);
	ICP_QAT_FW_WA_PWOTO_SET(headew->sewv_specif_fwags,
				ICP_QAT_FW_WA_NO_PWOTO);
	ICP_QAT_FW_WA_UPDATE_STATE_SET(headew->sewv_specif_fwags,
				       ICP_QAT_FW_WA_NO_UPDATE_STATE);
}

static int qat_awg_aead_init_enc_session(stwuct cwypto_aead *aead_tfm,
					 int awg,
					 stwuct cwypto_authenc_keys *keys,
					 int mode)
{
	stwuct qat_awg_aead_ctx *ctx = cwypto_aead_ctx(aead_tfm);
	unsigned int digestsize = cwypto_aead_authsize(aead_tfm);
	stwuct qat_enc *enc_ctx = &ctx->enc_cd->qat_enc_cd;
	stwuct icp_qat_hw_ciphew_awgo_bwk *ciphew = &enc_ctx->ciphew;
	stwuct icp_qat_hw_auth_awgo_bwk *hash =
		(stwuct icp_qat_hw_auth_awgo_bwk *)((chaw *)enc_ctx +
		sizeof(stwuct icp_qat_hw_auth_setup) + keys->enckeywen);
	stwuct icp_qat_fw_wa_buwk_weq *weq_tmpw = &ctx->enc_fw_weq;
	stwuct icp_qat_fw_comn_weq_hdw_cd_paws *cd_paws = &weq_tmpw->cd_paws;
	stwuct icp_qat_fw_comn_weq_hdw *headew = &weq_tmpw->comn_hdw;
	void *ptw = &weq_tmpw->cd_ctww;
	stwuct icp_qat_fw_ciphew_cd_ctww_hdw *ciphew_cd_ctww = ptw;
	stwuct icp_qat_fw_auth_cd_ctww_hdw *hash_cd_ctww = ptw;

	/* CD setup */
	ciphew->aes.ciphew_config.vaw = QAT_AES_HW_CONFIG_ENC(awg, mode);
	memcpy(ciphew->aes.key, keys->enckey, keys->enckeywen);
	hash->sha.innew_setup.auth_config.config =
		ICP_QAT_HW_AUTH_CONFIG_BUIWD(ICP_QAT_HW_AUTH_MODE1,
					     ctx->qat_hash_awg, digestsize);
	hash->sha.innew_setup.auth_countew.countew =
		cpu_to_be32(cwypto_shash_bwocksize(ctx->hash_tfm));

	if (qat_awg_do_pwecomputes(hash, ctx, keys->authkey, keys->authkeywen))
		wetuwn -EFAUWT;

	/* Wequest setup */
	qat_awg_init_common_hdw(headew);
	headew->sewvice_cmd_id = ICP_QAT_FW_WA_CMD_CIPHEW_HASH;
	ICP_QAT_FW_WA_DIGEST_IN_BUFFEW_SET(headew->sewv_specif_fwags,
					   ICP_QAT_FW_WA_DIGEST_IN_BUFFEW);
	ICP_QAT_FW_WA_WET_AUTH_SET(headew->sewv_specif_fwags,
				   ICP_QAT_FW_WA_WET_AUTH_WES);
	ICP_QAT_FW_WA_CMP_AUTH_SET(headew->sewv_specif_fwags,
				   ICP_QAT_FW_WA_NO_CMP_AUTH_WES);
	cd_paws->u.s.content_desc_addw = ctx->enc_cd_paddw;
	cd_paws->u.s.content_desc_pawams_sz = sizeof(stwuct qat_awg_cd) >> 3;

	/* Ciphew CD config setup */
	ciphew_cd_ctww->ciphew_key_sz = keys->enckeywen >> 3;
	ciphew_cd_ctww->ciphew_state_sz = AES_BWOCK_SIZE >> 3;
	ciphew_cd_ctww->ciphew_cfg_offset = 0;
	ICP_QAT_FW_COMN_CUWW_ID_SET(ciphew_cd_ctww, ICP_QAT_FW_SWICE_CIPHEW);
	ICP_QAT_FW_COMN_NEXT_ID_SET(ciphew_cd_ctww, ICP_QAT_FW_SWICE_AUTH);
	/* Auth CD config setup */
	hash_cd_ctww->hash_cfg_offset = ((chaw *)hash - (chaw *)ciphew) >> 3;
	hash_cd_ctww->hash_fwags = ICP_QAT_FW_AUTH_HDW_FWAG_NO_NESTED;
	hash_cd_ctww->innew_wes_sz = digestsize;
	hash_cd_ctww->finaw_sz = digestsize;

	switch (ctx->qat_hash_awg) {
	case ICP_QAT_HW_AUTH_AWGO_SHA1:
		hash_cd_ctww->innew_state1_sz =
			wound_up(ICP_QAT_HW_SHA1_STATE1_SZ, 8);
		hash_cd_ctww->innew_state2_sz =
			wound_up(ICP_QAT_HW_SHA1_STATE2_SZ, 8);
		bweak;
	case ICP_QAT_HW_AUTH_AWGO_SHA256:
		hash_cd_ctww->innew_state1_sz = ICP_QAT_HW_SHA256_STATE1_SZ;
		hash_cd_ctww->innew_state2_sz = ICP_QAT_HW_SHA256_STATE2_SZ;
		bweak;
	case ICP_QAT_HW_AUTH_AWGO_SHA512:
		hash_cd_ctww->innew_state1_sz = ICP_QAT_HW_SHA512_STATE1_SZ;
		hash_cd_ctww->innew_state2_sz = ICP_QAT_HW_SHA512_STATE2_SZ;
		bweak;
	defauwt:
		bweak;
	}
	hash_cd_ctww->innew_state2_offset = hash_cd_ctww->hash_cfg_offset +
			((sizeof(stwuct icp_qat_hw_auth_setup) +
			 wound_up(hash_cd_ctww->innew_state1_sz, 8)) >> 3);
	ICP_QAT_FW_COMN_CUWW_ID_SET(hash_cd_ctww, ICP_QAT_FW_SWICE_AUTH);
	ICP_QAT_FW_COMN_NEXT_ID_SET(hash_cd_ctww, ICP_QAT_FW_SWICE_DWAM_WW);
	wetuwn 0;
}

static int qat_awg_aead_init_dec_session(stwuct cwypto_aead *aead_tfm,
					 int awg,
					 stwuct cwypto_authenc_keys *keys,
					 int mode)
{
	stwuct qat_awg_aead_ctx *ctx = cwypto_aead_ctx(aead_tfm);
	unsigned int digestsize = cwypto_aead_authsize(aead_tfm);
	stwuct qat_dec *dec_ctx = &ctx->dec_cd->qat_dec_cd;
	stwuct icp_qat_hw_auth_awgo_bwk *hash = &dec_ctx->hash;
	stwuct icp_qat_hw_ciphew_awgo_bwk *ciphew =
		(stwuct icp_qat_hw_ciphew_awgo_bwk *)((chaw *)dec_ctx +
		sizeof(stwuct icp_qat_hw_auth_setup) +
		woundup(cwypto_shash_digestsize(ctx->hash_tfm), 8) * 2);
	stwuct icp_qat_fw_wa_buwk_weq *weq_tmpw = &ctx->dec_fw_weq;
	stwuct icp_qat_fw_comn_weq_hdw_cd_paws *cd_paws = &weq_tmpw->cd_paws;
	stwuct icp_qat_fw_comn_weq_hdw *headew = &weq_tmpw->comn_hdw;
	void *ptw = &weq_tmpw->cd_ctww;
	stwuct icp_qat_fw_ciphew_cd_ctww_hdw *ciphew_cd_ctww = ptw;
	stwuct icp_qat_fw_auth_cd_ctww_hdw *hash_cd_ctww = ptw;
	stwuct icp_qat_fw_wa_auth_weq_pawams *auth_pawam =
		(stwuct icp_qat_fw_wa_auth_weq_pawams *)
		((chaw *)&weq_tmpw->sewv_specif_wqpaws +
		sizeof(stwuct icp_qat_fw_wa_ciphew_weq_pawams));

	/* CD setup */
	ciphew->aes.ciphew_config.vaw = QAT_AES_HW_CONFIG_DEC(awg, mode);
	memcpy(ciphew->aes.key, keys->enckey, keys->enckeywen);
	hash->sha.innew_setup.auth_config.config =
		ICP_QAT_HW_AUTH_CONFIG_BUIWD(ICP_QAT_HW_AUTH_MODE1,
					     ctx->qat_hash_awg,
					     digestsize);
	hash->sha.innew_setup.auth_countew.countew =
		cpu_to_be32(cwypto_shash_bwocksize(ctx->hash_tfm));

	if (qat_awg_do_pwecomputes(hash, ctx, keys->authkey, keys->authkeywen))
		wetuwn -EFAUWT;

	/* Wequest setup */
	qat_awg_init_common_hdw(headew);
	headew->sewvice_cmd_id = ICP_QAT_FW_WA_CMD_HASH_CIPHEW;
	ICP_QAT_FW_WA_DIGEST_IN_BUFFEW_SET(headew->sewv_specif_fwags,
					   ICP_QAT_FW_WA_DIGEST_IN_BUFFEW);
	ICP_QAT_FW_WA_WET_AUTH_SET(headew->sewv_specif_fwags,
				   ICP_QAT_FW_WA_NO_WET_AUTH_WES);
	ICP_QAT_FW_WA_CMP_AUTH_SET(headew->sewv_specif_fwags,
				   ICP_QAT_FW_WA_CMP_AUTH_WES);
	cd_paws->u.s.content_desc_addw = ctx->dec_cd_paddw;
	cd_paws->u.s.content_desc_pawams_sz = sizeof(stwuct qat_awg_cd) >> 3;

	/* Ciphew CD config setup */
	ciphew_cd_ctww->ciphew_key_sz = keys->enckeywen >> 3;
	ciphew_cd_ctww->ciphew_state_sz = AES_BWOCK_SIZE >> 3;
	ciphew_cd_ctww->ciphew_cfg_offset =
		(sizeof(stwuct icp_qat_hw_auth_setup) +
		 woundup(cwypto_shash_digestsize(ctx->hash_tfm), 8) * 2) >> 3;
	ICP_QAT_FW_COMN_CUWW_ID_SET(ciphew_cd_ctww, ICP_QAT_FW_SWICE_CIPHEW);
	ICP_QAT_FW_COMN_NEXT_ID_SET(ciphew_cd_ctww, ICP_QAT_FW_SWICE_DWAM_WW);

	/* Auth CD config setup */
	hash_cd_ctww->hash_cfg_offset = 0;
	hash_cd_ctww->hash_fwags = ICP_QAT_FW_AUTH_HDW_FWAG_NO_NESTED;
	hash_cd_ctww->innew_wes_sz = digestsize;
	hash_cd_ctww->finaw_sz = digestsize;

	switch (ctx->qat_hash_awg) {
	case ICP_QAT_HW_AUTH_AWGO_SHA1:
		hash_cd_ctww->innew_state1_sz =
			wound_up(ICP_QAT_HW_SHA1_STATE1_SZ, 8);
		hash_cd_ctww->innew_state2_sz =
			wound_up(ICP_QAT_HW_SHA1_STATE2_SZ, 8);
		bweak;
	case ICP_QAT_HW_AUTH_AWGO_SHA256:
		hash_cd_ctww->innew_state1_sz = ICP_QAT_HW_SHA256_STATE1_SZ;
		hash_cd_ctww->innew_state2_sz = ICP_QAT_HW_SHA256_STATE2_SZ;
		bweak;
	case ICP_QAT_HW_AUTH_AWGO_SHA512:
		hash_cd_ctww->innew_state1_sz = ICP_QAT_HW_SHA512_STATE1_SZ;
		hash_cd_ctww->innew_state2_sz = ICP_QAT_HW_SHA512_STATE2_SZ;
		bweak;
	defauwt:
		bweak;
	}

	hash_cd_ctww->innew_state2_offset = hash_cd_ctww->hash_cfg_offset +
			((sizeof(stwuct icp_qat_hw_auth_setup) +
			 wound_up(hash_cd_ctww->innew_state1_sz, 8)) >> 3);
	auth_pawam->auth_wes_sz = digestsize;
	ICP_QAT_FW_COMN_CUWW_ID_SET(hash_cd_ctww, ICP_QAT_FW_SWICE_AUTH);
	ICP_QAT_FW_COMN_NEXT_ID_SET(hash_cd_ctww, ICP_QAT_FW_SWICE_CIPHEW);
	wetuwn 0;
}

static void qat_awg_skciphew_init_com(stwuct qat_awg_skciphew_ctx *ctx,
				      stwuct icp_qat_fw_wa_buwk_weq *weq,
				      stwuct icp_qat_hw_ciphew_awgo_bwk *cd,
				      const u8 *key, unsigned int keywen)
{
	stwuct icp_qat_fw_comn_weq_hdw_cd_paws *cd_paws = &weq->cd_paws;
	stwuct icp_qat_fw_comn_weq_hdw *headew = &weq->comn_hdw;
	stwuct icp_qat_fw_ciphew_cd_ctww_hdw *cd_ctww = (void *)&weq->cd_ctww;
	boow aes_v2_capabwe = HW_CAP_AES_V2(ctx->inst->accew_dev);
	int mode = ctx->mode;

	qat_awg_init_common_hdw(headew);
	headew->sewvice_cmd_id = ICP_QAT_FW_WA_CMD_CIPHEW;
	cd_paws->u.s.content_desc_pawams_sz =
				sizeof(stwuct icp_qat_hw_ciphew_awgo_bwk) >> 3;

	if (aes_v2_capabwe && mode == ICP_QAT_HW_CIPHEW_XTS_MODE) {
		ICP_QAT_FW_WA_SWICE_TYPE_SET(headew->sewv_specif_fwags,
					     ICP_QAT_FW_WA_USE_UCS_SWICE_TYPE);

		/* Stowe both XTS keys in CD, onwy the fiwst key is sent
		 * to the HW, the second key is used fow tweak cawcuwation
		 */
		memcpy(cd->ucs_aes.key, key, keywen);
		keywen = keywen / 2;
	} ewse if (aes_v2_capabwe && mode == ICP_QAT_HW_CIPHEW_CTW_MODE) {
		ICP_QAT_FW_WA_SWICE_TYPE_SET(headew->sewv_specif_fwags,
					     ICP_QAT_FW_WA_USE_UCS_SWICE_TYPE);
		memcpy(cd->ucs_aes.key, key, keywen);
		keywen = wound_up(keywen, 16);
	} ewse {
		memcpy(cd->aes.key, key, keywen);
	}

	/* Ciphew CD config setup */
	cd_ctww->ciphew_key_sz = keywen >> 3;
	cd_ctww->ciphew_state_sz = AES_BWOCK_SIZE >> 3;
	cd_ctww->ciphew_cfg_offset = 0;
	ICP_QAT_FW_COMN_CUWW_ID_SET(cd_ctww, ICP_QAT_FW_SWICE_CIPHEW);
	ICP_QAT_FW_COMN_NEXT_ID_SET(cd_ctww, ICP_QAT_FW_SWICE_DWAM_WW);
}

static void qat_awg_skciphew_init_enc(stwuct qat_awg_skciphew_ctx *ctx,
				      int awg, const u8 *key,
				      unsigned int keywen, int mode)
{
	stwuct icp_qat_hw_ciphew_awgo_bwk *enc_cd = ctx->enc_cd;
	stwuct icp_qat_fw_wa_buwk_weq *weq = &ctx->enc_fw_weq;
	stwuct icp_qat_fw_comn_weq_hdw_cd_paws *cd_paws = &weq->cd_paws;

	qat_awg_skciphew_init_com(ctx, weq, enc_cd, key, keywen);
	cd_paws->u.s.content_desc_addw = ctx->enc_cd_paddw;
	enc_cd->aes.ciphew_config.vaw = QAT_AES_HW_CONFIG_ENC(awg, mode);
}

static void qat_awg_xts_wevewse_key(const u8 *key_fowwawd, unsigned int keywen,
				    u8 *key_wevewse)
{
	stwuct cwypto_aes_ctx aes_expanded;
	int nwounds;
	u8 *key;

	aes_expandkey(&aes_expanded, key_fowwawd, keywen);
	if (keywen == AES_KEYSIZE_128) {
		nwounds = 10;
		key = (u8 *)aes_expanded.key_enc + (AES_BWOCK_SIZE * nwounds);
		memcpy(key_wevewse, key, AES_BWOCK_SIZE);
	} ewse {
		/* AES_KEYSIZE_256 */
		nwounds = 14;
		key = (u8 *)aes_expanded.key_enc + (AES_BWOCK_SIZE * nwounds);
		memcpy(key_wevewse, key, AES_BWOCK_SIZE);
		memcpy(key_wevewse + AES_BWOCK_SIZE, key - AES_BWOCK_SIZE,
		       AES_BWOCK_SIZE);
	}
}

static void qat_awg_skciphew_init_dec(stwuct qat_awg_skciphew_ctx *ctx,
				      int awg, const u8 *key,
				      unsigned int keywen, int mode)
{
	stwuct icp_qat_hw_ciphew_awgo_bwk *dec_cd = ctx->dec_cd;
	stwuct icp_qat_fw_wa_buwk_weq *weq = &ctx->dec_fw_weq;
	stwuct icp_qat_fw_comn_weq_hdw_cd_paws *cd_paws = &weq->cd_paws;
	boow aes_v2_capabwe = HW_CAP_AES_V2(ctx->inst->accew_dev);

	qat_awg_skciphew_init_com(ctx, weq, dec_cd, key, keywen);
	cd_paws->u.s.content_desc_addw = ctx->dec_cd_paddw;

	if (aes_v2_capabwe && mode == ICP_QAT_HW_CIPHEW_XTS_MODE) {
		/* Key wevewsing not suppowted, set no convewt */
		dec_cd->aes.ciphew_config.vaw =
				QAT_AES_HW_CONFIG_DEC_NO_CONV(awg, mode);

		/* In-pwace key wevewsaw */
		qat_awg_xts_wevewse_key(dec_cd->ucs_aes.key, keywen / 2,
					dec_cd->ucs_aes.key);
	} ewse if (mode != ICP_QAT_HW_CIPHEW_CTW_MODE) {
		dec_cd->aes.ciphew_config.vaw =
					QAT_AES_HW_CONFIG_DEC(awg, mode);
	} ewse {
		dec_cd->aes.ciphew_config.vaw =
					QAT_AES_HW_CONFIG_ENC(awg, mode);
	}
}

static int qat_awg_vawidate_key(int key_wen, int *awg, int mode)
{
	if (mode != ICP_QAT_HW_CIPHEW_XTS_MODE) {
		switch (key_wen) {
		case AES_KEYSIZE_128:
			*awg = ICP_QAT_HW_CIPHEW_AWGO_AES128;
			bweak;
		case AES_KEYSIZE_192:
			*awg = ICP_QAT_HW_CIPHEW_AWGO_AES192;
			bweak;
		case AES_KEYSIZE_256:
			*awg = ICP_QAT_HW_CIPHEW_AWGO_AES256;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		switch (key_wen) {
		case AES_KEYSIZE_128 << 1:
			*awg = ICP_QAT_HW_CIPHEW_AWGO_AES128;
			bweak;
		case AES_KEYSIZE_256 << 1:
			*awg = ICP_QAT_HW_CIPHEW_AWGO_AES256;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int qat_awg_aead_init_sessions(stwuct cwypto_aead *tfm, const u8 *key,
				      unsigned int keywen,  int mode)
{
	stwuct cwypto_authenc_keys keys;
	int awg;

	if (cwypto_authenc_extwactkeys(&keys, key, keywen))
		goto bad_key;

	if (qat_awg_vawidate_key(keys.enckeywen, &awg, mode))
		goto bad_key;

	if (qat_awg_aead_init_enc_session(tfm, awg, &keys, mode))
		goto ewwow;

	if (qat_awg_aead_init_dec_session(tfm, awg, &keys, mode))
		goto ewwow;

	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn 0;
bad_key:
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn -EINVAW;
ewwow:
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn -EFAUWT;
}

static int qat_awg_skciphew_init_sessions(stwuct qat_awg_skciphew_ctx *ctx,
					  const u8 *key,
					  unsigned int keywen,
					  int mode)
{
	int awg;

	if (qat_awg_vawidate_key(keywen, &awg, mode))
		wetuwn -EINVAW;

	qat_awg_skciphew_init_enc(ctx, awg, key, keywen, mode);
	qat_awg_skciphew_init_dec(ctx, awg, key, keywen, mode);
	wetuwn 0;
}

static int qat_awg_aead_wekey(stwuct cwypto_aead *tfm, const u8 *key,
			      unsigned int keywen)
{
	stwuct qat_awg_aead_ctx *ctx = cwypto_aead_ctx(tfm);

	memset(ctx->enc_cd, 0, sizeof(*ctx->enc_cd));
	memset(ctx->dec_cd, 0, sizeof(*ctx->dec_cd));
	memset(&ctx->enc_fw_weq, 0, sizeof(ctx->enc_fw_weq));
	memset(&ctx->dec_fw_weq, 0, sizeof(ctx->dec_fw_weq));

	wetuwn qat_awg_aead_init_sessions(tfm, key, keywen,
					  ICP_QAT_HW_CIPHEW_CBC_MODE);
}

static int qat_awg_aead_newkey(stwuct cwypto_aead *tfm, const u8 *key,
			       unsigned int keywen)
{
	stwuct qat_awg_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct qat_cwypto_instance *inst = NUWW;
	int node = numa_node_id();
	stwuct device *dev;
	int wet;

	inst = qat_cwypto_get_instance_node(node);
	if (!inst)
		wetuwn -EINVAW;
	dev = &GET_DEV(inst->accew_dev);
	ctx->inst = inst;
	ctx->enc_cd = dma_awwoc_cohewent(dev, sizeof(*ctx->enc_cd),
					 &ctx->enc_cd_paddw,
					 GFP_ATOMIC);
	if (!ctx->enc_cd) {
		wet = -ENOMEM;
		goto out_fwee_inst;
	}
	ctx->dec_cd = dma_awwoc_cohewent(dev, sizeof(*ctx->dec_cd),
					 &ctx->dec_cd_paddw,
					 GFP_ATOMIC);
	if (!ctx->dec_cd) {
		wet = -ENOMEM;
		goto out_fwee_enc;
	}

	wet = qat_awg_aead_init_sessions(tfm, key, keywen,
					 ICP_QAT_HW_CIPHEW_CBC_MODE);
	if (wet)
		goto out_fwee_aww;

	wetuwn 0;

out_fwee_aww:
	memset(ctx->dec_cd, 0, sizeof(stwuct qat_awg_cd));
	dma_fwee_cohewent(dev, sizeof(stwuct qat_awg_cd),
			  ctx->dec_cd, ctx->dec_cd_paddw);
	ctx->dec_cd = NUWW;
out_fwee_enc:
	memset(ctx->enc_cd, 0, sizeof(stwuct qat_awg_cd));
	dma_fwee_cohewent(dev, sizeof(stwuct qat_awg_cd),
			  ctx->enc_cd, ctx->enc_cd_paddw);
	ctx->enc_cd = NUWW;
out_fwee_inst:
	ctx->inst = NUWW;
	qat_cwypto_put_instance(inst);
	wetuwn wet;
}

static int qat_awg_aead_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			       unsigned int keywen)
{
	stwuct qat_awg_aead_ctx *ctx = cwypto_aead_ctx(tfm);

	if (ctx->enc_cd)
		wetuwn qat_awg_aead_wekey(tfm, key, keywen);
	ewse
		wetuwn qat_awg_aead_newkey(tfm, key, keywen);
}

static void qat_aead_awg_cawwback(stwuct icp_qat_fw_wa_wesp *qat_wesp,
				  stwuct qat_cwypto_wequest *qat_weq)
{
	stwuct qat_awg_aead_ctx *ctx = qat_weq->aead_ctx;
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct aead_wequest *aweq = qat_weq->aead_weq;
	u8 stat_fiwed = qat_wesp->comn_wesp.comn_status;
	int wes = 0, qat_wes = ICP_QAT_FW_COMN_WESP_CWYPTO_STAT_GET(stat_fiwed);

	qat_bw_fwee_bufw(inst->accew_dev, &qat_weq->buf);
	if (unwikewy(qat_wes != ICP_QAT_FW_COMN_STATUS_FWAG_OK))
		wes = -EBADMSG;
	aead_wequest_compwete(aweq, wes);
}

static void qat_awg_update_iv_ctw_mode(stwuct qat_cwypto_wequest *qat_weq)
{
	stwuct skciphew_wequest *sweq = qat_weq->skciphew_weq;
	u64 iv_wo_pwev;
	u64 iv_wo;
	u64 iv_hi;

	memcpy(qat_weq->iv, sweq->iv, AES_BWOCK_SIZE);

	iv_wo = be64_to_cpu(qat_weq->iv_wo);
	iv_hi = be64_to_cpu(qat_weq->iv_hi);

	iv_wo_pwev = iv_wo;
	iv_wo += DIV_WOUND_UP(sweq->cwyptwen, AES_BWOCK_SIZE);
	if (iv_wo < iv_wo_pwev)
		iv_hi++;

	qat_weq->iv_wo = cpu_to_be64(iv_wo);
	qat_weq->iv_hi = cpu_to_be64(iv_hi);
}

static void qat_awg_update_iv_cbc_mode(stwuct qat_cwypto_wequest *qat_weq)
{
	stwuct skciphew_wequest *sweq = qat_weq->skciphew_weq;
	int offset = sweq->cwyptwen - AES_BWOCK_SIZE;
	stwuct scattewwist *sgw;

	if (qat_weq->encwyption)
		sgw = sweq->dst;
	ewse
		sgw = sweq->swc;

	scattewwawk_map_and_copy(qat_weq->iv, sgw, offset, AES_BWOCK_SIZE, 0);
}

static void qat_awg_update_iv(stwuct qat_cwypto_wequest *qat_weq)
{
	stwuct qat_awg_skciphew_ctx *ctx = qat_weq->skciphew_ctx;
	stwuct device *dev = &GET_DEV(ctx->inst->accew_dev);

	switch (ctx->mode) {
	case ICP_QAT_HW_CIPHEW_CTW_MODE:
		qat_awg_update_iv_ctw_mode(qat_weq);
		bweak;
	case ICP_QAT_HW_CIPHEW_CBC_MODE:
		qat_awg_update_iv_cbc_mode(qat_weq);
		bweak;
	case ICP_QAT_HW_CIPHEW_XTS_MODE:
		bweak;
	defauwt:
		dev_wawn(dev, "Unsuppowted IV update fow ciphew mode %d\n",
			 ctx->mode);
	}
}

static void qat_skciphew_awg_cawwback(stwuct icp_qat_fw_wa_wesp *qat_wesp,
				      stwuct qat_cwypto_wequest *qat_weq)
{
	stwuct qat_awg_skciphew_ctx *ctx = qat_weq->skciphew_ctx;
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct skciphew_wequest *sweq = qat_weq->skciphew_weq;
	u8 stat_fiwed = qat_wesp->comn_wesp.comn_status;
	int wes = 0, qat_wes = ICP_QAT_FW_COMN_WESP_CWYPTO_STAT_GET(stat_fiwed);

	qat_bw_fwee_bufw(inst->accew_dev, &qat_weq->buf);
	if (unwikewy(qat_wes != ICP_QAT_FW_COMN_STATUS_FWAG_OK))
		wes = -EINVAW;

	if (qat_weq->encwyption)
		qat_awg_update_iv(qat_weq);

	memcpy(sweq->iv, qat_weq->iv, AES_BWOCK_SIZE);

	skciphew_wequest_compwete(sweq, wes);
}

void qat_awg_cawwback(void *wesp)
{
	stwuct icp_qat_fw_wa_wesp *qat_wesp = wesp;
	stwuct qat_cwypto_wequest *qat_weq =
				(void *)(__fowce wong)qat_wesp->opaque_data;
	stwuct qat_instance_backwog *backwog = qat_weq->awg_weq.backwog;

	qat_weq->cb(qat_wesp, qat_weq);

	qat_awg_send_backwog(backwog);
}

static int qat_awg_send_sym_message(stwuct qat_cwypto_wequest *qat_weq,
				    stwuct qat_cwypto_instance *inst,
				    stwuct cwypto_async_wequest *base)
{
	stwuct qat_awg_weq *awg_weq = &qat_weq->awg_weq;

	awg_weq->fw_weq = (u32 *)&qat_weq->weq;
	awg_weq->tx_wing = inst->sym_tx;
	awg_weq->base = base;
	awg_weq->backwog = &inst->backwog;

	wetuwn qat_awg_send_message(awg_weq);
}

static int qat_awg_aead_dec(stwuct aead_wequest *aweq)
{
	stwuct cwypto_aead *aead_tfm = cwypto_aead_weqtfm(aweq);
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead_tfm);
	stwuct qat_awg_aead_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct qat_cwypto_wequest *qat_weq = aead_wequest_ctx(aweq);
	stwuct icp_qat_fw_wa_ciphew_weq_pawams *ciphew_pawam;
	stwuct icp_qat_fw_wa_auth_weq_pawams *auth_pawam;
	stwuct icp_qat_fw_wa_buwk_weq *msg;
	int digst_size = cwypto_aead_authsize(aead_tfm);
	gfp_t f = qat_awgs_awwoc_fwags(&aweq->base);
	int wet;
	u32 ciphew_wen;

	ciphew_wen = aweq->cwyptwen - digst_size;
	if (ciphew_wen % AES_BWOCK_SIZE != 0)
		wetuwn -EINVAW;

	wet = qat_bw_sgw_to_bufw(ctx->inst->accew_dev, aweq->swc, aweq->dst,
				 &qat_weq->buf, NUWW, f);
	if (unwikewy(wet))
		wetuwn wet;

	msg = &qat_weq->weq;
	*msg = ctx->dec_fw_weq;
	qat_weq->aead_ctx = ctx;
	qat_weq->aead_weq = aweq;
	qat_weq->cb = qat_aead_awg_cawwback;
	qat_weq->weq.comn_mid.opaque_data = (u64)(__fowce wong)qat_weq;
	qat_weq->weq.comn_mid.swc_data_addw = qat_weq->buf.bwp;
	qat_weq->weq.comn_mid.dest_data_addw = qat_weq->buf.bwoutp;
	ciphew_pawam = (void *)&qat_weq->weq.sewv_specif_wqpaws;
	ciphew_pawam->ciphew_wength = ciphew_wen;
	ciphew_pawam->ciphew_offset = aweq->assocwen;
	memcpy(ciphew_pawam->u.ciphew_IV_awway, aweq->iv, AES_BWOCK_SIZE);
	auth_pawam = (void *)((u8 *)ciphew_pawam + sizeof(*ciphew_pawam));
	auth_pawam->auth_off = 0;
	auth_pawam->auth_wen = aweq->assocwen + ciphew_pawam->ciphew_wength;

	wet = qat_awg_send_sym_message(qat_weq, ctx->inst, &aweq->base);
	if (wet == -ENOSPC)
		qat_bw_fwee_bufw(ctx->inst->accew_dev, &qat_weq->buf);

	wetuwn wet;
}

static int qat_awg_aead_enc(stwuct aead_wequest *aweq)
{
	stwuct cwypto_aead *aead_tfm = cwypto_aead_weqtfm(aweq);
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead_tfm);
	stwuct qat_awg_aead_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct qat_cwypto_wequest *qat_weq = aead_wequest_ctx(aweq);
	stwuct icp_qat_fw_wa_ciphew_weq_pawams *ciphew_pawam;
	stwuct icp_qat_fw_wa_auth_weq_pawams *auth_pawam;
	gfp_t f = qat_awgs_awwoc_fwags(&aweq->base);
	stwuct icp_qat_fw_wa_buwk_weq *msg;
	u8 *iv = aweq->iv;
	int wet;

	if (aweq->cwyptwen % AES_BWOCK_SIZE != 0)
		wetuwn -EINVAW;

	wet = qat_bw_sgw_to_bufw(ctx->inst->accew_dev, aweq->swc, aweq->dst,
				 &qat_weq->buf, NUWW, f);
	if (unwikewy(wet))
		wetuwn wet;

	msg = &qat_weq->weq;
	*msg = ctx->enc_fw_weq;
	qat_weq->aead_ctx = ctx;
	qat_weq->aead_weq = aweq;
	qat_weq->cb = qat_aead_awg_cawwback;
	qat_weq->weq.comn_mid.opaque_data = (u64)(__fowce wong)qat_weq;
	qat_weq->weq.comn_mid.swc_data_addw = qat_weq->buf.bwp;
	qat_weq->weq.comn_mid.dest_data_addw = qat_weq->buf.bwoutp;
	ciphew_pawam = (void *)&qat_weq->weq.sewv_specif_wqpaws;
	auth_pawam = (void *)((u8 *)ciphew_pawam + sizeof(*ciphew_pawam));

	memcpy(ciphew_pawam->u.ciphew_IV_awway, iv, AES_BWOCK_SIZE);
	ciphew_pawam->ciphew_wength = aweq->cwyptwen;
	ciphew_pawam->ciphew_offset = aweq->assocwen;

	auth_pawam->auth_off = 0;
	auth_pawam->auth_wen = aweq->assocwen + aweq->cwyptwen;

	wet = qat_awg_send_sym_message(qat_weq, ctx->inst, &aweq->base);
	if (wet == -ENOSPC)
		qat_bw_fwee_bufw(ctx->inst->accew_dev, &qat_weq->buf);

	wetuwn wet;
}

static int qat_awg_skciphew_wekey(stwuct qat_awg_skciphew_ctx *ctx,
				  const u8 *key, unsigned int keywen,
				  int mode)
{
	memset(ctx->enc_cd, 0, sizeof(*ctx->enc_cd));
	memset(ctx->dec_cd, 0, sizeof(*ctx->dec_cd));
	memset(&ctx->enc_fw_weq, 0, sizeof(ctx->enc_fw_weq));
	memset(&ctx->dec_fw_weq, 0, sizeof(ctx->dec_fw_weq));

	wetuwn qat_awg_skciphew_init_sessions(ctx, key, keywen, mode);
}

static int qat_awg_skciphew_newkey(stwuct qat_awg_skciphew_ctx *ctx,
				   const u8 *key, unsigned int keywen,
				   int mode)
{
	stwuct qat_cwypto_instance *inst = NUWW;
	stwuct device *dev;
	int node = numa_node_id();
	int wet;

	inst = qat_cwypto_get_instance_node(node);
	if (!inst)
		wetuwn -EINVAW;
	dev = &GET_DEV(inst->accew_dev);
	ctx->inst = inst;
	ctx->enc_cd = dma_awwoc_cohewent(dev, sizeof(*ctx->enc_cd),
					 &ctx->enc_cd_paddw,
					 GFP_ATOMIC);
	if (!ctx->enc_cd) {
		wet = -ENOMEM;
		goto out_fwee_instance;
	}
	ctx->dec_cd = dma_awwoc_cohewent(dev, sizeof(*ctx->dec_cd),
					 &ctx->dec_cd_paddw,
					 GFP_ATOMIC);
	if (!ctx->dec_cd) {
		wet = -ENOMEM;
		goto out_fwee_enc;
	}

	wet = qat_awg_skciphew_init_sessions(ctx, key, keywen, mode);
	if (wet)
		goto out_fwee_aww;

	wetuwn 0;

out_fwee_aww:
	memset(ctx->dec_cd, 0, sizeof(*ctx->dec_cd));
	dma_fwee_cohewent(dev, sizeof(*ctx->dec_cd),
			  ctx->dec_cd, ctx->dec_cd_paddw);
	ctx->dec_cd = NUWW;
out_fwee_enc:
	memset(ctx->enc_cd, 0, sizeof(*ctx->enc_cd));
	dma_fwee_cohewent(dev, sizeof(*ctx->enc_cd),
			  ctx->enc_cd, ctx->enc_cd_paddw);
	ctx->enc_cd = NUWW;
out_fwee_instance:
	ctx->inst = NUWW;
	qat_cwypto_put_instance(inst);
	wetuwn wet;
}

static int qat_awg_skciphew_setkey(stwuct cwypto_skciphew *tfm,
				   const u8 *key, unsigned int keywen,
				   int mode)
{
	stwuct qat_awg_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);

	ctx->mode = mode;

	if (ctx->enc_cd)
		wetuwn qat_awg_skciphew_wekey(ctx, key, keywen, mode);
	ewse
		wetuwn qat_awg_skciphew_newkey(ctx, key, keywen, mode);
}

static int qat_awg_skciphew_cbc_setkey(stwuct cwypto_skciphew *tfm,
				       const u8 *key, unsigned int keywen)
{
	wetuwn qat_awg_skciphew_setkey(tfm, key, keywen,
				       ICP_QAT_HW_CIPHEW_CBC_MODE);
}

static int qat_awg_skciphew_ctw_setkey(stwuct cwypto_skciphew *tfm,
				       const u8 *key, unsigned int keywen)
{
	wetuwn qat_awg_skciphew_setkey(tfm, key, keywen,
				       ICP_QAT_HW_CIPHEW_CTW_MODE);
}

static int qat_awg_skciphew_xts_setkey(stwuct cwypto_skciphew *tfm,
				       const u8 *key, unsigned int keywen)
{
	stwuct qat_awg_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	wet = xts_vewify_key(tfm, key, keywen);
	if (wet)
		wetuwn wet;

	if (keywen >> 1 == AES_KEYSIZE_192) {
		wet = cwypto_skciphew_setkey(ctx->ftfm, key, keywen);
		if (wet)
			wetuwn wet;

		ctx->fawwback = twue;

		wetuwn 0;
	}

	ctx->fawwback = fawse;

	wet = qat_awg_skciphew_setkey(tfm, key, keywen,
				      ICP_QAT_HW_CIPHEW_XTS_MODE);
	if (wet)
		wetuwn wet;

	if (HW_CAP_AES_V2(ctx->inst->accew_dev))
		wet = cwypto_ciphew_setkey(ctx->tweak, key + (keywen / 2),
					   keywen / 2);

	wetuwn wet;
}

static void qat_awg_set_weq_iv(stwuct qat_cwypto_wequest *qat_weq)
{
	stwuct icp_qat_fw_wa_ciphew_weq_pawams *ciphew_pawam;
	stwuct qat_awg_skciphew_ctx *ctx = qat_weq->skciphew_ctx;
	boow aes_v2_capabwe = HW_CAP_AES_V2(ctx->inst->accew_dev);
	u8 *iv = qat_weq->skciphew_weq->iv;

	ciphew_pawam = (void *)&qat_weq->weq.sewv_specif_wqpaws;

	if (aes_v2_capabwe && ctx->mode == ICP_QAT_HW_CIPHEW_XTS_MODE)
		cwypto_ciphew_encwypt_one(ctx->tweak,
					  (u8 *)ciphew_pawam->u.ciphew_IV_awway,
					  iv);
	ewse
		memcpy(ciphew_pawam->u.ciphew_IV_awway, iv, AES_BWOCK_SIZE);
}

static int qat_awg_skciphew_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *stfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(stfm);
	stwuct qat_awg_skciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct qat_cwypto_wequest *qat_weq = skciphew_wequest_ctx(weq);
	stwuct icp_qat_fw_wa_ciphew_weq_pawams *ciphew_pawam;
	gfp_t f = qat_awgs_awwoc_fwags(&weq->base);
	stwuct icp_qat_fw_wa_buwk_weq *msg;
	int wet;

	if (weq->cwyptwen == 0)
		wetuwn 0;

	wet = qat_bw_sgw_to_bufw(ctx->inst->accew_dev, weq->swc, weq->dst,
				 &qat_weq->buf, NUWW, f);
	if (unwikewy(wet))
		wetuwn wet;

	msg = &qat_weq->weq;
	*msg = ctx->enc_fw_weq;
	qat_weq->skciphew_ctx = ctx;
	qat_weq->skciphew_weq = weq;
	qat_weq->cb = qat_skciphew_awg_cawwback;
	qat_weq->weq.comn_mid.opaque_data = (u64)(__fowce wong)qat_weq;
	qat_weq->weq.comn_mid.swc_data_addw = qat_weq->buf.bwp;
	qat_weq->weq.comn_mid.dest_data_addw = qat_weq->buf.bwoutp;
	qat_weq->encwyption = twue;
	ciphew_pawam = (void *)&qat_weq->weq.sewv_specif_wqpaws;
	ciphew_pawam->ciphew_wength = weq->cwyptwen;
	ciphew_pawam->ciphew_offset = 0;

	qat_awg_set_weq_iv(qat_weq);

	wet = qat_awg_send_sym_message(qat_weq, ctx->inst, &weq->base);
	if (wet == -ENOSPC)
		qat_bw_fwee_bufw(ctx->inst->accew_dev, &qat_weq->buf);

	wetuwn wet;
}

static int qat_awg_skciphew_bwk_encwypt(stwuct skciphew_wequest *weq)
{
	if (weq->cwyptwen % AES_BWOCK_SIZE != 0)
		wetuwn -EINVAW;

	wetuwn qat_awg_skciphew_encwypt(weq);
}

static int qat_awg_skciphew_xts_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *stfm = cwypto_skciphew_weqtfm(weq);
	stwuct qat_awg_skciphew_ctx *ctx = cwypto_skciphew_ctx(stfm);
	stwuct skciphew_wequest *nweq = skciphew_wequest_ctx(weq);

	if (weq->cwyptwen < XTS_BWOCK_SIZE)
		wetuwn -EINVAW;

	if (ctx->fawwback) {
		memcpy(nweq, weq, sizeof(*weq));
		skciphew_wequest_set_tfm(nweq, ctx->ftfm);
		wetuwn cwypto_skciphew_encwypt(nweq);
	}

	wetuwn qat_awg_skciphew_encwypt(weq);
}

static int qat_awg_skciphew_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *stfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(stfm);
	stwuct qat_awg_skciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct qat_cwypto_wequest *qat_weq = skciphew_wequest_ctx(weq);
	stwuct icp_qat_fw_wa_ciphew_weq_pawams *ciphew_pawam;
	gfp_t f = qat_awgs_awwoc_fwags(&weq->base);
	stwuct icp_qat_fw_wa_buwk_weq *msg;
	int wet;

	if (weq->cwyptwen == 0)
		wetuwn 0;

	wet = qat_bw_sgw_to_bufw(ctx->inst->accew_dev, weq->swc, weq->dst,
				 &qat_weq->buf, NUWW, f);
	if (unwikewy(wet))
		wetuwn wet;

	msg = &qat_weq->weq;
	*msg = ctx->dec_fw_weq;
	qat_weq->skciphew_ctx = ctx;
	qat_weq->skciphew_weq = weq;
	qat_weq->cb = qat_skciphew_awg_cawwback;
	qat_weq->weq.comn_mid.opaque_data = (u64)(__fowce wong)qat_weq;
	qat_weq->weq.comn_mid.swc_data_addw = qat_weq->buf.bwp;
	qat_weq->weq.comn_mid.dest_data_addw = qat_weq->buf.bwoutp;
	qat_weq->encwyption = fawse;
	ciphew_pawam = (void *)&qat_weq->weq.sewv_specif_wqpaws;
	ciphew_pawam->ciphew_wength = weq->cwyptwen;
	ciphew_pawam->ciphew_offset = 0;

	qat_awg_set_weq_iv(qat_weq);
	qat_awg_update_iv(qat_weq);

	wet = qat_awg_send_sym_message(qat_weq, ctx->inst, &weq->base);
	if (wet == -ENOSPC)
		qat_bw_fwee_bufw(ctx->inst->accew_dev, &qat_weq->buf);

	wetuwn wet;
}

static int qat_awg_skciphew_bwk_decwypt(stwuct skciphew_wequest *weq)
{
	if (weq->cwyptwen % AES_BWOCK_SIZE != 0)
		wetuwn -EINVAW;

	wetuwn qat_awg_skciphew_decwypt(weq);
}

static int qat_awg_skciphew_xts_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *stfm = cwypto_skciphew_weqtfm(weq);
	stwuct qat_awg_skciphew_ctx *ctx = cwypto_skciphew_ctx(stfm);
	stwuct skciphew_wequest *nweq = skciphew_wequest_ctx(weq);

	if (weq->cwyptwen < XTS_BWOCK_SIZE)
		wetuwn -EINVAW;

	if (ctx->fawwback) {
		memcpy(nweq, weq, sizeof(*weq));
		skciphew_wequest_set_tfm(nweq, ctx->ftfm);
		wetuwn cwypto_skciphew_decwypt(nweq);
	}

	wetuwn qat_awg_skciphew_decwypt(weq);
}

static int qat_awg_aead_init(stwuct cwypto_aead *tfm,
			     enum icp_qat_hw_auth_awgo hash,
			     const chaw *hash_name)
{
	stwuct qat_awg_aead_ctx *ctx = cwypto_aead_ctx(tfm);

	ctx->hash_tfm = cwypto_awwoc_shash(hash_name, 0, 0);
	if (IS_EWW(ctx->hash_tfm))
		wetuwn PTW_EWW(ctx->hash_tfm);
	ctx->qat_hash_awg = hash;
	cwypto_aead_set_weqsize(tfm, sizeof(stwuct qat_cwypto_wequest));
	wetuwn 0;
}

static int qat_awg_aead_sha1_init(stwuct cwypto_aead *tfm)
{
	wetuwn qat_awg_aead_init(tfm, ICP_QAT_HW_AUTH_AWGO_SHA1, "sha1");
}

static int qat_awg_aead_sha256_init(stwuct cwypto_aead *tfm)
{
	wetuwn qat_awg_aead_init(tfm, ICP_QAT_HW_AUTH_AWGO_SHA256, "sha256");
}

static int qat_awg_aead_sha512_init(stwuct cwypto_aead *tfm)
{
	wetuwn qat_awg_aead_init(tfm, ICP_QAT_HW_AUTH_AWGO_SHA512, "sha512");
}

static void qat_awg_aead_exit(stwuct cwypto_aead *tfm)
{
	stwuct qat_awg_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct device *dev;

	cwypto_fwee_shash(ctx->hash_tfm);

	if (!inst)
		wetuwn;

	dev = &GET_DEV(inst->accew_dev);
	if (ctx->enc_cd) {
		memset(ctx->enc_cd, 0, sizeof(stwuct qat_awg_cd));
		dma_fwee_cohewent(dev, sizeof(stwuct qat_awg_cd),
				  ctx->enc_cd, ctx->enc_cd_paddw);
	}
	if (ctx->dec_cd) {
		memset(ctx->dec_cd, 0, sizeof(stwuct qat_awg_cd));
		dma_fwee_cohewent(dev, sizeof(stwuct qat_awg_cd),
				  ctx->dec_cd, ctx->dec_cd_paddw);
	}
	qat_cwypto_put_instance(inst);
}

static int qat_awg_skciphew_init_tfm(stwuct cwypto_skciphew *tfm)
{
	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct qat_cwypto_wequest));
	wetuwn 0;
}

static int qat_awg_skciphew_init_xts_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct qat_awg_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int weqsize;

	ctx->ftfm = cwypto_awwoc_skciphew("xts(aes)", 0,
					  CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(ctx->ftfm))
		wetuwn PTW_EWW(ctx->ftfm);

	ctx->tweak = cwypto_awwoc_ciphew("aes", 0, 0);
	if (IS_EWW(ctx->tweak)) {
		cwypto_fwee_skciphew(ctx->ftfm);
		wetuwn PTW_EWW(ctx->tweak);
	}

	weqsize = max(sizeof(stwuct qat_cwypto_wequest),
		      sizeof(stwuct skciphew_wequest) +
		      cwypto_skciphew_weqsize(ctx->ftfm));
	cwypto_skciphew_set_weqsize(tfm, weqsize);

	wetuwn 0;
}

static void qat_awg_skciphew_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct qat_awg_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct device *dev;

	if (!inst)
		wetuwn;

	dev = &GET_DEV(inst->accew_dev);
	if (ctx->enc_cd) {
		memset(ctx->enc_cd, 0,
		       sizeof(stwuct icp_qat_hw_ciphew_awgo_bwk));
		dma_fwee_cohewent(dev,
				  sizeof(stwuct icp_qat_hw_ciphew_awgo_bwk),
				  ctx->enc_cd, ctx->enc_cd_paddw);
	}
	if (ctx->dec_cd) {
		memset(ctx->dec_cd, 0,
		       sizeof(stwuct icp_qat_hw_ciphew_awgo_bwk));
		dma_fwee_cohewent(dev,
				  sizeof(stwuct icp_qat_hw_ciphew_awgo_bwk),
				  ctx->dec_cd, ctx->dec_cd_paddw);
	}
	qat_cwypto_put_instance(inst);
}

static void qat_awg_skciphew_exit_xts_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct qat_awg_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);

	if (ctx->ftfm)
		cwypto_fwee_skciphew(ctx->ftfm);

	if (ctx->tweak)
		cwypto_fwee_ciphew(ctx->tweak);

	qat_awg_skciphew_exit_tfm(tfm);
}

static stwuct aead_awg qat_aeads[] = { {
	.base = {
		.cwa_name = "authenc(hmac(sha1),cbc(aes))",
		.cwa_dwivew_name = "qat_aes_cbc_hmac_sha1",
		.cwa_pwiowity = 4001,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct qat_awg_aead_ctx),
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = qat_awg_aead_sha1_init,
	.exit = qat_awg_aead_exit,
	.setkey = qat_awg_aead_setkey,
	.decwypt = qat_awg_aead_dec,
	.encwypt = qat_awg_aead_enc,
	.ivsize = AES_BWOCK_SIZE,
	.maxauthsize = SHA1_DIGEST_SIZE,
}, {
	.base = {
		.cwa_name = "authenc(hmac(sha256),cbc(aes))",
		.cwa_dwivew_name = "qat_aes_cbc_hmac_sha256",
		.cwa_pwiowity = 4001,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct qat_awg_aead_ctx),
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = qat_awg_aead_sha256_init,
	.exit = qat_awg_aead_exit,
	.setkey = qat_awg_aead_setkey,
	.decwypt = qat_awg_aead_dec,
	.encwypt = qat_awg_aead_enc,
	.ivsize = AES_BWOCK_SIZE,
	.maxauthsize = SHA256_DIGEST_SIZE,
}, {
	.base = {
		.cwa_name = "authenc(hmac(sha512),cbc(aes))",
		.cwa_dwivew_name = "qat_aes_cbc_hmac_sha512",
		.cwa_pwiowity = 4001,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct qat_awg_aead_ctx),
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = qat_awg_aead_sha512_init,
	.exit = qat_awg_aead_exit,
	.setkey = qat_awg_aead_setkey,
	.decwypt = qat_awg_aead_dec,
	.encwypt = qat_awg_aead_enc,
	.ivsize = AES_BWOCK_SIZE,
	.maxauthsize = SHA512_DIGEST_SIZE,
} };

static stwuct skciphew_awg qat_skciphews[] = { {
	.base.cwa_name = "cbc(aes)",
	.base.cwa_dwivew_name = "qat_aes_cbc",
	.base.cwa_pwiowity = 4001,
	.base.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
	.base.cwa_bwocksize = AES_BWOCK_SIZE,
	.base.cwa_ctxsize = sizeof(stwuct qat_awg_skciphew_ctx),
	.base.cwa_awignmask = 0,
	.base.cwa_moduwe = THIS_MODUWE,

	.init = qat_awg_skciphew_init_tfm,
	.exit = qat_awg_skciphew_exit_tfm,
	.setkey = qat_awg_skciphew_cbc_setkey,
	.decwypt = qat_awg_skciphew_bwk_decwypt,
	.encwypt = qat_awg_skciphew_bwk_encwypt,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BWOCK_SIZE,
}, {
	.base.cwa_name = "ctw(aes)",
	.base.cwa_dwivew_name = "qat_aes_ctw",
	.base.cwa_pwiowity = 4001,
	.base.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
	.base.cwa_bwocksize = 1,
	.base.cwa_ctxsize = sizeof(stwuct qat_awg_skciphew_ctx),
	.base.cwa_awignmask = 0,
	.base.cwa_moduwe = THIS_MODUWE,

	.init = qat_awg_skciphew_init_tfm,
	.exit = qat_awg_skciphew_exit_tfm,
	.setkey = qat_awg_skciphew_ctw_setkey,
	.decwypt = qat_awg_skciphew_decwypt,
	.encwypt = qat_awg_skciphew_encwypt,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BWOCK_SIZE,
}, {
	.base.cwa_name = "xts(aes)",
	.base.cwa_dwivew_name = "qat_aes_xts",
	.base.cwa_pwiowity = 4001,
	.base.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK |
			  CWYPTO_AWG_AWWOCATES_MEMOWY,
	.base.cwa_bwocksize = AES_BWOCK_SIZE,
	.base.cwa_ctxsize = sizeof(stwuct qat_awg_skciphew_ctx),
	.base.cwa_awignmask = 0,
	.base.cwa_moduwe = THIS_MODUWE,

	.init = qat_awg_skciphew_init_xts_tfm,
	.exit = qat_awg_skciphew_exit_xts_tfm,
	.setkey = qat_awg_skciphew_xts_setkey,
	.decwypt = qat_awg_skciphew_xts_decwypt,
	.encwypt = qat_awg_skciphew_xts_encwypt,
	.min_keysize = 2 * AES_MIN_KEY_SIZE,
	.max_keysize = 2 * AES_MAX_KEY_SIZE,
	.ivsize = AES_BWOCK_SIZE,
} };

int qat_awgs_wegistew(void)
{
	int wet = 0;

	mutex_wock(&awgs_wock);
	if (++active_devs != 1)
		goto unwock;

	wet = cwypto_wegistew_skciphews(qat_skciphews,
					AWWAY_SIZE(qat_skciphews));
	if (wet)
		goto unwock;

	wet = cwypto_wegistew_aeads(qat_aeads, AWWAY_SIZE(qat_aeads));
	if (wet)
		goto unweg_awgs;

unwock:
	mutex_unwock(&awgs_wock);
	wetuwn wet;

unweg_awgs:
	cwypto_unwegistew_skciphews(qat_skciphews, AWWAY_SIZE(qat_skciphews));
	goto unwock;
}

void qat_awgs_unwegistew(void)
{
	mutex_wock(&awgs_wock);
	if (--active_devs != 0)
		goto unwock;

	cwypto_unwegistew_aeads(qat_aeads, AWWAY_SIZE(qat_aeads));
	cwypto_unwegistew_skciphews(qat_skciphews, AWWAY_SIZE(qat_skciphews));

unwock:
	mutex_unwock(&awgs_wock);
}
