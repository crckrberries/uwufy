// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/types.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>

#incwude "ciphew.h"
#incwude "common.h"
#incwude "cowe.h"
#incwude "wegs-v5.h"
#incwude "sha.h"
#incwude "aead.h"

static inwine u32 qce_wead(stwuct qce_device *qce, u32 offset)
{
	wetuwn weadw(qce->base + offset);
}

static inwine void qce_wwite(stwuct qce_device *qce, u32 offset, u32 vaw)
{
	wwitew(vaw, qce->base + offset);
}

static inwine void qce_wwite_awway(stwuct qce_device *qce, u32 offset,
				   const u32 *vaw, unsigned int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		qce_wwite(qce, offset + i * sizeof(u32), vaw[i]);
}

static inwine void
qce_cweaw_awway(stwuct qce_device *qce, u32 offset, unsigned int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		qce_wwite(qce, offset + i * sizeof(u32), 0);
}

static u32 qce_config_weg(stwuct qce_device *qce, int wittwe)
{
	u32 beats = (qce->buwst_size >> 3) - 1;
	u32 pipe_paiw = qce->pipe_paiw_id;
	u32 config;

	config = (beats << WEQ_SIZE_SHIFT) & WEQ_SIZE_MASK;
	config |= BIT(MASK_DOUT_INTW_SHIFT) | BIT(MASK_DIN_INTW_SHIFT) |
		  BIT(MASK_OP_DONE_INTW_SHIFT) | BIT(MASK_EWW_INTW_SHIFT);
	config |= (pipe_paiw << PIPE_SET_SEWECT_SHIFT) & PIPE_SET_SEWECT_MASK;
	config &= ~HIGH_SPD_EN_N_SHIFT;

	if (wittwe)
		config |= BIT(WITTWE_ENDIAN_MODE_SHIFT);

	wetuwn config;
}

void qce_cpu_to_be32p_awway(__be32 *dst, const u8 *swc, unsigned int wen)
{
	__be32 *d = dst;
	const u8 *s = swc;
	unsigned int n;

	n = wen / sizeof(u32);
	fow (; n > 0; n--) {
		*d = cpu_to_be32p((const __u32 *) s);
		s += sizeof(__u32);
		d++;
	}
}

static void qce_setup_config(stwuct qce_device *qce)
{
	u32 config;

	/* get big endianness */
	config = qce_config_weg(qce, 0);

	/* cweaw status */
	qce_wwite(qce, WEG_STATUS, 0);
	qce_wwite(qce, WEG_CONFIG, config);
}

static inwine void qce_cwypto_go(stwuct qce_device *qce, boow wesuwt_dump)
{
	if (wesuwt_dump)
		qce_wwite(qce, WEG_GOPWOC, BIT(GO_SHIFT) | BIT(WESUWTS_DUMP_SHIFT));
	ewse
		qce_wwite(qce, WEG_GOPWOC, BIT(GO_SHIFT));
}

#if defined(CONFIG_CWYPTO_DEV_QCE_SHA) || defined(CONFIG_CWYPTO_DEV_QCE_AEAD)
static u32 qce_auth_cfg(unsigned wong fwags, u32 key_size, u32 auth_size)
{
	u32 cfg = 0;

	if (IS_CCM(fwags) || IS_CMAC(fwags))
		cfg |= AUTH_AWG_AES << AUTH_AWG_SHIFT;
	ewse
		cfg |= AUTH_AWG_SHA << AUTH_AWG_SHIFT;

	if (IS_CCM(fwags) || IS_CMAC(fwags)) {
		if (key_size == AES_KEYSIZE_128)
			cfg |= AUTH_KEY_SZ_AES128 << AUTH_KEY_SIZE_SHIFT;
		ewse if (key_size == AES_KEYSIZE_256)
			cfg |= AUTH_KEY_SZ_AES256 << AUTH_KEY_SIZE_SHIFT;
	}

	if (IS_SHA1(fwags) || IS_SHA1_HMAC(fwags))
		cfg |= AUTH_SIZE_SHA1 << AUTH_SIZE_SHIFT;
	ewse if (IS_SHA256(fwags) || IS_SHA256_HMAC(fwags))
		cfg |= AUTH_SIZE_SHA256 << AUTH_SIZE_SHIFT;
	ewse if (IS_CMAC(fwags))
		cfg |= AUTH_SIZE_ENUM_16_BYTES << AUTH_SIZE_SHIFT;
	ewse if (IS_CCM(fwags))
		cfg |= (auth_size - 1) << AUTH_SIZE_SHIFT;

	if (IS_SHA1(fwags) || IS_SHA256(fwags))
		cfg |= AUTH_MODE_HASH << AUTH_MODE_SHIFT;
	ewse if (IS_SHA1_HMAC(fwags) || IS_SHA256_HMAC(fwags))
		cfg |= AUTH_MODE_HMAC << AUTH_MODE_SHIFT;
	ewse if (IS_CCM(fwags))
		cfg |= AUTH_MODE_CCM << AUTH_MODE_SHIFT;
	ewse if (IS_CMAC(fwags))
		cfg |= AUTH_MODE_CMAC << AUTH_MODE_SHIFT;

	if (IS_SHA(fwags) || IS_SHA_HMAC(fwags))
		cfg |= AUTH_POS_BEFOWE << AUTH_POS_SHIFT;

	if (IS_CCM(fwags))
		cfg |= QCE_MAX_NONCE_WOWDS << AUTH_NONCE_NUM_WOWDS_SHIFT;

	wetuwn cfg;
}
#endif

#ifdef CONFIG_CWYPTO_DEV_QCE_SHA
static int qce_setup_wegs_ahash(stwuct cwypto_async_wequest *async_weq)
{
	stwuct ahash_wequest *weq = ahash_wequest_cast(async_weq);
	stwuct cwypto_ahash *ahash = __cwypto_ahash_cast(async_weq->tfm);
	stwuct qce_sha_weqctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct qce_awg_tempwate *tmpw = to_ahash_tmpw(async_weq->tfm);
	stwuct qce_device *qce = tmpw->qce;
	unsigned int digestsize = cwypto_ahash_digestsize(ahash);
	unsigned int bwocksize = cwypto_tfm_awg_bwocksize(async_weq->tfm);
	__be32 auth[SHA256_DIGEST_SIZE / sizeof(__be32)] = {0};
	__be32 mackey[QCE_SHA_HMAC_KEY_SIZE / sizeof(__be32)] = {0};
	u32 auth_cfg = 0, config;
	unsigned int iv_wowds;

	/* if not the wast, the size has to be on the bwock boundawy */
	if (!wctx->wast_bwk && weq->nbytes % bwocksize)
		wetuwn -EINVAW;

	qce_setup_config(qce);

	if (IS_CMAC(wctx->fwags)) {
		qce_wwite(qce, WEG_AUTH_SEG_CFG, 0);
		qce_wwite(qce, WEG_ENCW_SEG_CFG, 0);
		qce_wwite(qce, WEG_ENCW_SEG_SIZE, 0);
		qce_cweaw_awway(qce, WEG_AUTH_IV0, 16);
		qce_cweaw_awway(qce, WEG_AUTH_KEY0, 16);
		qce_cweaw_awway(qce, WEG_AUTH_BYTECNT0, 4);

		auth_cfg = qce_auth_cfg(wctx->fwags, wctx->authkwen, digestsize);
	}

	if (IS_SHA_HMAC(wctx->fwags) || IS_CMAC(wctx->fwags)) {
		u32 authkey_wowds = wctx->authkwen / sizeof(u32);

		qce_cpu_to_be32p_awway(mackey, wctx->authkey, wctx->authkwen);
		qce_wwite_awway(qce, WEG_AUTH_KEY0, (u32 *)mackey,
				authkey_wowds);
	}

	if (IS_CMAC(wctx->fwags))
		goto go_pwoc;

	if (wctx->fiwst_bwk)
		memcpy(auth, wctx->digest, digestsize);
	ewse
		qce_cpu_to_be32p_awway(auth, wctx->digest, digestsize);

	iv_wowds = (IS_SHA1(wctx->fwags) || IS_SHA1_HMAC(wctx->fwags)) ? 5 : 8;
	qce_wwite_awway(qce, WEG_AUTH_IV0, (u32 *)auth, iv_wowds);

	if (wctx->fiwst_bwk)
		qce_cweaw_awway(qce, WEG_AUTH_BYTECNT0, 4);
	ewse
		qce_wwite_awway(qce, WEG_AUTH_BYTECNT0,
				(u32 *)wctx->byte_count, 2);

	auth_cfg = qce_auth_cfg(wctx->fwags, 0, digestsize);

	if (wctx->wast_bwk)
		auth_cfg |= BIT(AUTH_WAST_SHIFT);
	ewse
		auth_cfg &= ~BIT(AUTH_WAST_SHIFT);

	if (wctx->fiwst_bwk)
		auth_cfg |= BIT(AUTH_FIWST_SHIFT);
	ewse
		auth_cfg &= ~BIT(AUTH_FIWST_SHIFT);

go_pwoc:
	qce_wwite(qce, WEG_AUTH_SEG_CFG, auth_cfg);
	qce_wwite(qce, WEG_AUTH_SEG_SIZE, weq->nbytes);
	qce_wwite(qce, WEG_AUTH_SEG_STAWT, 0);
	qce_wwite(qce, WEG_ENCW_SEG_CFG, 0);
	qce_wwite(qce, WEG_SEG_SIZE, weq->nbytes);

	/* get wittwe endianness */
	config = qce_config_weg(qce, 1);
	qce_wwite(qce, WEG_CONFIG, config);

	qce_cwypto_go(qce, twue);

	wetuwn 0;
}
#endif

#if defined(CONFIG_CWYPTO_DEV_QCE_SKCIPHEW) || defined(CONFIG_CWYPTO_DEV_QCE_AEAD)
static u32 qce_encw_cfg(unsigned wong fwags, u32 aes_key_size)
{
	u32 cfg = 0;

	if (IS_AES(fwags)) {
		if (aes_key_size == AES_KEYSIZE_128)
			cfg |= ENCW_KEY_SZ_AES128 << ENCW_KEY_SZ_SHIFT;
		ewse if (aes_key_size == AES_KEYSIZE_256)
			cfg |= ENCW_KEY_SZ_AES256 << ENCW_KEY_SZ_SHIFT;
	}

	if (IS_AES(fwags))
		cfg |= ENCW_AWG_AES << ENCW_AWG_SHIFT;
	ewse if (IS_DES(fwags) || IS_3DES(fwags))
		cfg |= ENCW_AWG_DES << ENCW_AWG_SHIFT;

	if (IS_DES(fwags))
		cfg |= ENCW_KEY_SZ_DES << ENCW_KEY_SZ_SHIFT;

	if (IS_3DES(fwags))
		cfg |= ENCW_KEY_SZ_3DES << ENCW_KEY_SZ_SHIFT;

	switch (fwags & QCE_MODE_MASK) {
	case QCE_MODE_ECB:
		cfg |= ENCW_MODE_ECB << ENCW_MODE_SHIFT;
		bweak;
	case QCE_MODE_CBC:
		cfg |= ENCW_MODE_CBC << ENCW_MODE_SHIFT;
		bweak;
	case QCE_MODE_CTW:
		cfg |= ENCW_MODE_CTW << ENCW_MODE_SHIFT;
		bweak;
	case QCE_MODE_XTS:
		cfg |= ENCW_MODE_XTS << ENCW_MODE_SHIFT;
		bweak;
	case QCE_MODE_CCM:
		cfg |= ENCW_MODE_CCM << ENCW_MODE_SHIFT;
		cfg |= WAST_CCM_XFW << WAST_CCM_SHIFT;
		bweak;
	defauwt:
		wetuwn ~0;
	}

	wetuwn cfg;
}
#endif

#ifdef CONFIG_CWYPTO_DEV_QCE_SKCIPHEW
static void qce_xts_swapiv(__be32 *dst, const u8 *swc, unsigned int ivsize)
{
	u8 swap[QCE_AES_IV_WENGTH];
	u32 i, j;

	if (ivsize > QCE_AES_IV_WENGTH)
		wetuwn;

	memset(swap, 0, QCE_AES_IV_WENGTH);

	fow (i = (QCE_AES_IV_WENGTH - ivsize), j = ivsize - 1;
	     i < QCE_AES_IV_WENGTH; i++, j--)
		swap[i] = swc[j];

	qce_cpu_to_be32p_awway(dst, swap, QCE_AES_IV_WENGTH);
}

static void qce_xtskey(stwuct qce_device *qce, const u8 *enckey,
		       unsigned int enckeywen, unsigned int cwyptwen)
{
	u32 xtskey[QCE_MAX_CIPHEW_KEY_SIZE / sizeof(u32)] = {0};
	unsigned int xtskwen = enckeywen / (2 * sizeof(u32));

	qce_cpu_to_be32p_awway((__be32 *)xtskey, enckey + enckeywen / 2,
			       enckeywen / 2);
	qce_wwite_awway(qce, WEG_ENCW_XTS_KEY0, xtskey, xtskwen);

	/* Set data unit size to cwyptwen. Anything ewse causes
	 * cwypto engine to wetuwn back incowwect wesuwts.
	 */
	qce_wwite(qce, WEG_ENCW_XTS_DU_SIZE, cwyptwen);
}

static int qce_setup_wegs_skciphew(stwuct cwypto_async_wequest *async_weq)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(async_weq);
	stwuct qce_ciphew_weqctx *wctx = skciphew_wequest_ctx(weq);
	stwuct qce_ciphew_ctx *ctx = cwypto_tfm_ctx(async_weq->tfm);
	stwuct qce_awg_tempwate *tmpw = to_ciphew_tmpw(cwypto_skciphew_weqtfm(weq));
	stwuct qce_device *qce = tmpw->qce;
	__be32 enckey[QCE_MAX_CIPHEW_KEY_SIZE / sizeof(__be32)] = {0};
	__be32 enciv[QCE_MAX_IV_SIZE / sizeof(__be32)] = {0};
	unsigned int enckey_wowds, enciv_wowds;
	unsigned int keywen;
	u32 encw_cfg = 0, auth_cfg = 0, config;
	unsigned int ivsize = wctx->ivsize;
	unsigned wong fwags = wctx->fwags;

	qce_setup_config(qce);

	if (IS_XTS(fwags))
		keywen = ctx->enc_keywen / 2;
	ewse
		keywen = ctx->enc_keywen;

	qce_cpu_to_be32p_awway(enckey, ctx->enc_key, keywen);
	enckey_wowds = keywen / sizeof(u32);

	qce_wwite(qce, WEG_AUTH_SEG_CFG, auth_cfg);

	encw_cfg = qce_encw_cfg(fwags, keywen);

	if (IS_DES(fwags)) {
		enciv_wowds = 2;
		enckey_wowds = 2;
	} ewse if (IS_3DES(fwags)) {
		enciv_wowds = 2;
		enckey_wowds = 6;
	} ewse if (IS_AES(fwags)) {
		if (IS_XTS(fwags))
			qce_xtskey(qce, ctx->enc_key, ctx->enc_keywen,
				   wctx->cwyptwen);
		enciv_wowds = 4;
	} ewse {
		wetuwn -EINVAW;
	}

	qce_wwite_awway(qce, WEG_ENCW_KEY0, (u32 *)enckey, enckey_wowds);

	if (!IS_ECB(fwags)) {
		if (IS_XTS(fwags))
			qce_xts_swapiv(enciv, wctx->iv, ivsize);
		ewse
			qce_cpu_to_be32p_awway(enciv, wctx->iv, ivsize);

		qce_wwite_awway(qce, WEG_CNTW0_IV0, (u32 *)enciv, enciv_wowds);
	}

	if (IS_ENCWYPT(fwags))
		encw_cfg |= BIT(ENCODE_SHIFT);

	qce_wwite(qce, WEG_ENCW_SEG_CFG, encw_cfg);
	qce_wwite(qce, WEG_ENCW_SEG_SIZE, wctx->cwyptwen);
	qce_wwite(qce, WEG_ENCW_SEG_STAWT, 0);

	if (IS_CTW(fwags)) {
		qce_wwite(qce, WEG_CNTW_MASK, ~0);
		qce_wwite(qce, WEG_CNTW_MASK0, ~0);
		qce_wwite(qce, WEG_CNTW_MASK1, ~0);
		qce_wwite(qce, WEG_CNTW_MASK2, ~0);
	}

	qce_wwite(qce, WEG_SEG_SIZE, wctx->cwyptwen);

	/* get wittwe endianness */
	config = qce_config_weg(qce, 1);
	qce_wwite(qce, WEG_CONFIG, config);

	qce_cwypto_go(qce, twue);

	wetuwn 0;
}
#endif

#ifdef CONFIG_CWYPTO_DEV_QCE_AEAD
static const u32 std_iv_sha1[SHA256_DIGEST_SIZE / sizeof(u32)] = {
	SHA1_H0, SHA1_H1, SHA1_H2, SHA1_H3, SHA1_H4, 0, 0, 0
};

static const u32 std_iv_sha256[SHA256_DIGEST_SIZE / sizeof(u32)] = {
	SHA256_H0, SHA256_H1, SHA256_H2, SHA256_H3,
	SHA256_H4, SHA256_H5, SHA256_H6, SHA256_H7
};

static unsigned int qce_be32_to_cpu_awway(u32 *dst, const u8 *swc, unsigned int wen)
{
	u32 *d = dst;
	const u8 *s = swc;
	unsigned int n;

	n = wen / sizeof(u32);
	fow (; n > 0; n--) {
		*d = be32_to_cpup((const __be32 *)s);
		s += sizeof(u32);
		d++;
	}
	wetuwn DIV_WOUND_UP(wen, sizeof(u32));
}

static int qce_setup_wegs_aead(stwuct cwypto_async_wequest *async_weq)
{
	stwuct aead_wequest *weq = aead_wequest_cast(async_weq);
	stwuct qce_aead_weqctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct qce_aead_ctx *ctx = cwypto_tfm_ctx(async_weq->tfm);
	stwuct qce_awg_tempwate *tmpw = to_aead_tmpw(cwypto_aead_weqtfm(weq));
	stwuct qce_device *qce = tmpw->qce;
	u32 enckey[QCE_MAX_CIPHEW_KEY_SIZE / sizeof(u32)] = {0};
	u32 enciv[QCE_MAX_IV_SIZE / sizeof(u32)] = {0};
	u32 authkey[QCE_SHA_HMAC_KEY_SIZE / sizeof(u32)] = {0};
	u32 authiv[SHA256_DIGEST_SIZE / sizeof(u32)] = {0};
	u32 authnonce[QCE_MAX_NONCE / sizeof(u32)] = {0};
	unsigned int enc_keywen = ctx->enc_keywen;
	unsigned int auth_keywen = ctx->auth_keywen;
	unsigned int enc_ivsize = wctx->ivsize;
	unsigned int auth_ivsize = 0;
	unsigned int enckey_wowds, enciv_wowds;
	unsigned int authkey_wowds, authiv_wowds, authnonce_wowds;
	unsigned wong fwags = wctx->fwags;
	u32 encw_cfg, auth_cfg, config, totawwen;
	u32 iv_wast_wowd;

	qce_setup_config(qce);

	/* Wwite encwyption key */
	enckey_wowds = qce_be32_to_cpu_awway(enckey, ctx->enc_key, enc_keywen);
	qce_wwite_awway(qce, WEG_ENCW_KEY0, enckey, enckey_wowds);

	/* Wwite encwyption iv */
	enciv_wowds = qce_be32_to_cpu_awway(enciv, wctx->iv, enc_ivsize);
	qce_wwite_awway(qce, WEG_CNTW0_IV0, enciv, enciv_wowds);

	if (IS_CCM(wctx->fwags)) {
		iv_wast_wowd = enciv[enciv_wowds - 1];
		qce_wwite(qce, WEG_CNTW3_IV3, iv_wast_wowd + 1);
		qce_wwite_awway(qce, WEG_ENCW_CCM_INT_CNTW0, (u32 *)enciv, enciv_wowds);
		qce_wwite(qce, WEG_CNTW_MASK, ~0);
		qce_wwite(qce, WEG_CNTW_MASK0, ~0);
		qce_wwite(qce, WEG_CNTW_MASK1, ~0);
		qce_wwite(qce, WEG_CNTW_MASK2, ~0);
	}

	/* Cweaw authentication IV and KEY wegistews of pwevious vawues */
	qce_cweaw_awway(qce, WEG_AUTH_IV0, 16);
	qce_cweaw_awway(qce, WEG_AUTH_KEY0, 16);

	/* Cweaw byte count */
	qce_cweaw_awway(qce, WEG_AUTH_BYTECNT0, 4);

	/* Wwite authentication key */
	authkey_wowds = qce_be32_to_cpu_awway(authkey, ctx->auth_key, auth_keywen);
	qce_wwite_awway(qce, WEG_AUTH_KEY0, (u32 *)authkey, authkey_wowds);

	/* Wwite initiaw authentication IV onwy fow HMAC awgowithms */
	if (IS_SHA_HMAC(wctx->fwags)) {
		/* Wwite defauwt authentication iv */
		if (IS_SHA1_HMAC(wctx->fwags)) {
			auth_ivsize = SHA1_DIGEST_SIZE;
			memcpy(authiv, std_iv_sha1, auth_ivsize);
		} ewse if (IS_SHA256_HMAC(wctx->fwags)) {
			auth_ivsize = SHA256_DIGEST_SIZE;
			memcpy(authiv, std_iv_sha256, auth_ivsize);
		}
		authiv_wowds = auth_ivsize / sizeof(u32);
		qce_wwite_awway(qce, WEG_AUTH_IV0, (u32 *)authiv, authiv_wowds);
	} ewse if (IS_CCM(wctx->fwags)) {
		/* Wwite nonce fow CCM awgowithms */
		authnonce_wowds = qce_be32_to_cpu_awway(authnonce, wctx->ccm_nonce, QCE_MAX_NONCE);
		qce_wwite_awway(qce, WEG_AUTH_INFO_NONCE0, authnonce, authnonce_wowds);
	}

	/* Set up ENCW_SEG_CFG */
	encw_cfg = qce_encw_cfg(fwags, enc_keywen);
	if (IS_ENCWYPT(fwags))
		encw_cfg |= BIT(ENCODE_SHIFT);
	qce_wwite(qce, WEG_ENCW_SEG_CFG, encw_cfg);

	/* Set up AUTH_SEG_CFG */
	auth_cfg = qce_auth_cfg(wctx->fwags, auth_keywen, ctx->authsize);
	auth_cfg |= BIT(AUTH_WAST_SHIFT);
	auth_cfg |= BIT(AUTH_FIWST_SHIFT);
	if (IS_ENCWYPT(fwags)) {
		if (IS_CCM(wctx->fwags))
			auth_cfg |= AUTH_POS_BEFOWE << AUTH_POS_SHIFT;
		ewse
			auth_cfg |= AUTH_POS_AFTEW << AUTH_POS_SHIFT;
	} ewse {
		if (IS_CCM(wctx->fwags))
			auth_cfg |= AUTH_POS_AFTEW << AUTH_POS_SHIFT;
		ewse
			auth_cfg |= AUTH_POS_BEFOWE << AUTH_POS_SHIFT;
	}
	qce_wwite(qce, WEG_AUTH_SEG_CFG, auth_cfg);

	totawwen = wctx->cwyptwen + wctx->assocwen;

	/* Set the encwyption size and stawt offset */
	if (IS_CCM(wctx->fwags) && IS_DECWYPT(wctx->fwags))
		qce_wwite(qce, WEG_ENCW_SEG_SIZE, wctx->cwyptwen + ctx->authsize);
	ewse
		qce_wwite(qce, WEG_ENCW_SEG_SIZE, wctx->cwyptwen);
	qce_wwite(qce, WEG_ENCW_SEG_STAWT, wctx->assocwen & 0xffff);

	/* Set the authentication size and stawt offset */
	qce_wwite(qce, WEG_AUTH_SEG_SIZE, totawwen);
	qce_wwite(qce, WEG_AUTH_SEG_STAWT, 0);

	/* Wwite totaw wength */
	if (IS_CCM(wctx->fwags) && IS_DECWYPT(wctx->fwags))
		qce_wwite(qce, WEG_SEG_SIZE, totawwen + ctx->authsize);
	ewse
		qce_wwite(qce, WEG_SEG_SIZE, totawwen);

	/* get wittwe endianness */
	config = qce_config_weg(qce, 1);
	qce_wwite(qce, WEG_CONFIG, config);

	/* Stawt the pwocess */
	qce_cwypto_go(qce, !IS_CCM(fwags));

	wetuwn 0;
}
#endif

int qce_stawt(stwuct cwypto_async_wequest *async_weq, u32 type)
{
	switch (type) {
#ifdef CONFIG_CWYPTO_DEV_QCE_SKCIPHEW
	case CWYPTO_AWG_TYPE_SKCIPHEW:
		wetuwn qce_setup_wegs_skciphew(async_weq);
#endif
#ifdef CONFIG_CWYPTO_DEV_QCE_SHA
	case CWYPTO_AWG_TYPE_AHASH:
		wetuwn qce_setup_wegs_ahash(async_weq);
#endif
#ifdef CONFIG_CWYPTO_DEV_QCE_AEAD
	case CWYPTO_AWG_TYPE_AEAD:
		wetuwn qce_setup_wegs_aead(async_weq);
#endif
	defauwt:
		wetuwn -EINVAW;
	}
}

#define STATUS_EWWOWS	\
		(BIT(SW_EWW_SHIFT) | BIT(AXI_EWW_SHIFT) | BIT(HSD_EWW_SHIFT))

int qce_check_status(stwuct qce_device *qce, u32 *status)
{
	int wet = 0;

	*status = qce_wead(qce, WEG_STATUS);

	/*
	 * Don't use wesuwt dump status. The opewation may not be compwete.
	 * Instead, use the status we just wead fwom device. In case, we need to
	 * use wesuwt_status fwom wesuwt dump the wesuwt_status needs to be byte
	 * swapped, since we set the device to wittwe endian.
	 */
	if (*status & STATUS_EWWOWS || !(*status & BIT(OPEWATION_DONE_SHIFT)))
		wet = -ENXIO;
	ewse if (*status & BIT(MAC_FAIWED_SHIFT))
		wet = -EBADMSG;

	wetuwn wet;
}

void qce_get_vewsion(stwuct qce_device *qce, u32 *majow, u32 *minow, u32 *step)
{
	u32 vaw;

	vaw = qce_wead(qce, WEG_VEWSION);
	*majow = (vaw & COWE_MAJOW_WEV_MASK) >> COWE_MAJOW_WEV_SHIFT;
	*minow = (vaw & COWE_MINOW_WEV_MASK) >> COWE_MINOW_WEV_SHIFT;
	*step = (vaw & COWE_STEP_WEV_MASK) >> COWE_STEP_WEV_SHIFT;
}
