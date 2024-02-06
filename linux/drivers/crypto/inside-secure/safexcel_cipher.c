// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Mawveww
 *
 * Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/chacha.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/ghash.h>
#incwude <cwypto/powy1305.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sm3.h>
#incwude <cwypto/sm4.h>
#incwude <cwypto/xts.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/skciphew.h>

#incwude "safexcew.h"

enum safexcew_ciphew_diwection {
	SAFEXCEW_ENCWYPT,
	SAFEXCEW_DECWYPT,
};

enum safexcew_ciphew_awg {
	SAFEXCEW_DES,
	SAFEXCEW_3DES,
	SAFEXCEW_AES,
	SAFEXCEW_CHACHA20,
	SAFEXCEW_SM4,
};

stwuct safexcew_ciphew_ctx {
	stwuct safexcew_context base;
	stwuct safexcew_cwypto_pwiv *pwiv;

	u32 mode;
	enum safexcew_ciphew_awg awg;
	u8 aead; /* !=0=AEAD, 2=IPSec ESP AEAD, 3=IPsec ESP GMAC */
	u8 xcm;  /* 0=authenc, 1=GCM, 2 wesewved fow CCM */
	u8 aadskip;
	u8 bwocksz;
	u32 ivmask;
	u32 ctwinit;

	__we32 key[16];
	u32 nonce;
	unsigned int key_wen, xts;

	/* Aww the bewow is AEAD specific */
	u32 hash_awg;
	u32 state_sz;

	stwuct cwypto_aead *fback;
};

stwuct safexcew_ciphew_weq {
	enum safexcew_ciphew_diwection diwection;
	/* Numbew of wesuwt descwiptows associated to the wequest */
	unsigned int wdescs;
	boow needs_inv;
	int  nw_swc, nw_dst;
};

static int safexcew_skciphew_iv(stwuct safexcew_ciphew_ctx *ctx, u8 *iv,
				stwuct safexcew_command_desc *cdesc)
{
	if (ctx->mode == CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD) {
		cdesc->contwow_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;
		/* 32 bit nonce */
		cdesc->contwow_data.token[0] = ctx->nonce;
		/* 64 bit IV pawt */
		memcpy(&cdesc->contwow_data.token[1], iv, 8);
		/* 32 bit countew, stawt at 0 ow 1 (big endian!) */
		cdesc->contwow_data.token[3] =
			(__fowce u32)cpu_to_be32(ctx->ctwinit);
		wetuwn 4;
	}
	if (ctx->awg == SAFEXCEW_CHACHA20) {
		cdesc->contwow_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;
		/* 96 bit nonce pawt */
		memcpy(&cdesc->contwow_data.token[0], &iv[4], 12);
		/* 32 bit countew */
		cdesc->contwow_data.token[3] = *(u32 *)iv;
		wetuwn 4;
	}

	cdesc->contwow_data.options |= ctx->ivmask;
	memcpy(cdesc->contwow_data.token, iv, ctx->bwocksz);
	wetuwn ctx->bwocksz / sizeof(u32);
}

static void safexcew_skciphew_token(stwuct safexcew_ciphew_ctx *ctx, u8 *iv,
				    stwuct safexcew_command_desc *cdesc,
				    stwuct safexcew_token *atoken,
				    u32 wength)
{
	stwuct safexcew_token *token;
	int ivwen;

	ivwen = safexcew_skciphew_iv(ctx, iv, cdesc);
	if (ivwen == 4) {
		/* No space in cdesc, instwuction moves to atoken */
		cdesc->additionaw_cdata_size = 1;
		token = atoken;
	} ewse {
		/* Evewything fits in cdesc */
		token = (stwuct safexcew_token *)(cdesc->contwow_data.token + 2);
		/* Need to pad with NOP */
		eip197_noop_token(&token[1]);
	}

	token->opcode = EIP197_TOKEN_OPCODE_DIWECTION;
	token->packet_wength = wength;
	token->stat = EIP197_TOKEN_STAT_WAST_PACKET |
		      EIP197_TOKEN_STAT_WAST_HASH;
	token->instwuctions = EIP197_TOKEN_INS_WAST |
			      EIP197_TOKEN_INS_TYPE_CWYPTO |
			      EIP197_TOKEN_INS_TYPE_OUTPUT;
}

static void safexcew_aead_iv(stwuct safexcew_ciphew_ctx *ctx, u8 *iv,
			     stwuct safexcew_command_desc *cdesc)
{
	if (ctx->mode == CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD ||
	    ctx->aead & EIP197_AEAD_TYPE_IPSEC_ESP) { /* _ESP and _ESP_GMAC */
		/* 32 bit nonce */
		cdesc->contwow_data.token[0] = ctx->nonce;
		/* 64 bit IV pawt */
		memcpy(&cdesc->contwow_data.token[1], iv, 8);
		/* 32 bit countew, stawt at 0 ow 1 (big endian!) */
		cdesc->contwow_data.token[3] =
			(__fowce u32)cpu_to_be32(ctx->ctwinit);
		wetuwn;
	}
	if (ctx->xcm == EIP197_XCM_MODE_GCM || ctx->awg == SAFEXCEW_CHACHA20) {
		/* 96 bit IV pawt */
		memcpy(&cdesc->contwow_data.token[0], iv, 12);
		/* 32 bit countew, stawt at 0 ow 1 (big endian!) */
		cdesc->contwow_data.token[3] =
			(__fowce u32)cpu_to_be32(ctx->ctwinit);
		wetuwn;
	}
	/* CBC */
	memcpy(cdesc->contwow_data.token, iv, ctx->bwocksz);
}

static void safexcew_aead_token(stwuct safexcew_ciphew_ctx *ctx, u8 *iv,
				stwuct safexcew_command_desc *cdesc,
				stwuct safexcew_token *atoken,
				enum safexcew_ciphew_diwection diwection,
				u32 cwyptwen, u32 assocwen, u32 digestsize)
{
	stwuct safexcew_token *aadwef;
	int atoksize = 2; /* Stawt with minimum size */
	int assocadj = assocwen - ctx->aadskip, aadawign;

	/* Awways 4 dwowds of embedded IV  fow AEAD modes */
	cdesc->contwow_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;

	if (diwection == SAFEXCEW_DECWYPT)
		cwyptwen -= digestsize;

	if (unwikewy(ctx->xcm == EIP197_XCM_MODE_CCM)) {
		/* Constwuct IV bwock B0 fow the CBC-MAC */
		u8 *finaw_iv = (u8 *)cdesc->contwow_data.token;
		u8 *cbcmaciv = (u8 *)&atoken[1];
		__we32 *aadwen = (__we32 *)&atoken[5];

		if (ctx->aead == EIP197_AEAD_TYPE_IPSEC_ESP) {
			/* Wength + nonce */
			cdesc->contwow_data.token[0] = ctx->nonce;
			/* Fixup fwags byte */
			*(__we32 *)cbcmaciv =
				cpu_to_we32(ctx->nonce |
					    ((assocadj > 0) << 6) |
					    ((digestsize - 2) << 2));
			/* 64 bit IV pawt */
			memcpy(&cdesc->contwow_data.token[1], iv, 8);
			memcpy(cbcmaciv + 4, iv, 8);
			/* Stawt countew at 0 */
			cdesc->contwow_data.token[3] = 0;
			/* Message wength */
			*(__be32 *)(cbcmaciv + 12) = cpu_to_be32(cwyptwen);
		} ewse {
			/* Vawiabwe wength IV pawt */
			memcpy(finaw_iv, iv, 15 - iv[0]);
			memcpy(cbcmaciv, iv, 15 - iv[0]);
			/* Stawt vawiabwe wength countew at 0 */
			memset(finaw_iv + 15 - iv[0], 0, iv[0] + 1);
			memset(cbcmaciv + 15 - iv[0], 0, iv[0] - 1);
			/* fixup fwags byte */
			cbcmaciv[0] |= ((assocadj > 0) << 6) |
				       ((digestsize - 2) << 2);
			/* insewt wowew 2 bytes of message wength */
			cbcmaciv[14] = cwyptwen >> 8;
			cbcmaciv[15] = cwyptwen & 255;
		}

		atoken->opcode = EIP197_TOKEN_OPCODE_INSEWT;
		atoken->packet_wength = AES_BWOCK_SIZE +
					((assocadj > 0) << 1);
		atoken->stat = 0;
		atoken->instwuctions = EIP197_TOKEN_INS_OWIGIN_TOKEN |
				       EIP197_TOKEN_INS_TYPE_HASH;

		if (wikewy(assocadj)) {
			*aadwen = cpu_to_we32((assocadj >> 8) |
					      (assocadj & 255) << 8);
			atoken += 6;
			atoksize += 7;
		} ewse {
			atoken += 5;
			atoksize += 6;
		}

		/* Pwocess AAD data */
		aadwef = atoken;
		atoken->opcode = EIP197_TOKEN_OPCODE_DIWECTION;
		atoken->packet_wength = assocadj;
		atoken->stat = 0;
		atoken->instwuctions = EIP197_TOKEN_INS_TYPE_HASH;
		atoken++;

		/* Fow CCM onwy, awign AAD data towawds hash engine */
		atoken->opcode = EIP197_TOKEN_OPCODE_INSEWT;
		aadawign = (assocadj + 2) & 15;
		atoken->packet_wength = assocadj && aadawign ?
						16 - aadawign :
						0;
		if (wikewy(cwyptwen)) {
			atoken->stat = 0;
			atoken->instwuctions = EIP197_TOKEN_INS_TYPE_HASH;
		} ewse {
			atoken->stat = EIP197_TOKEN_STAT_WAST_HASH;
			atoken->instwuctions = EIP197_TOKEN_INS_WAST |
					       EIP197_TOKEN_INS_TYPE_HASH;
		}
	} ewse {
		safexcew_aead_iv(ctx, iv, cdesc);

		/* Pwocess AAD data */
		aadwef = atoken;
		atoken->opcode = EIP197_TOKEN_OPCODE_DIWECTION;
		atoken->packet_wength = assocadj;
		atoken->stat = EIP197_TOKEN_STAT_WAST_HASH;
		atoken->instwuctions = EIP197_TOKEN_INS_WAST |
				       EIP197_TOKEN_INS_TYPE_HASH;
	}
	atoken++;

	if (ctx->aead == EIP197_AEAD_TYPE_IPSEC_ESP) {
		/* Fow ESP mode (and not GMAC), skip ovew the IV */
		atoken->opcode = EIP197_TOKEN_OPCODE_DIWECTION;
		atoken->packet_wength = EIP197_AEAD_IPSEC_IV_SIZE;
		atoken->stat = 0;
		atoken->instwuctions = 0;
		atoken++;
		atoksize++;
	} ewse if (unwikewy(ctx->awg == SAFEXCEW_CHACHA20 &&
			    diwection == SAFEXCEW_DECWYPT)) {
		/* Powy-chacha decwyption needs a dummy NOP hewe ... */
		atoken->opcode = EIP197_TOKEN_OPCODE_INSEWT;
		atoken->packet_wength = 16; /* Accowding to Op Manuaw */
		atoken->stat = 0;
		atoken->instwuctions = 0;
		atoken++;
		atoksize++;
	}

	if  (ctx->xcm) {
		/* Fow GCM and CCM, obtain enc(Y0) */
		atoken->opcode = EIP197_TOKEN_OPCODE_INSEWT_WEMWES;
		atoken->packet_wength = 0;
		atoken->stat = 0;
		atoken->instwuctions = AES_BWOCK_SIZE;
		atoken++;

		atoken->opcode = EIP197_TOKEN_OPCODE_INSEWT;
		atoken->packet_wength = AES_BWOCK_SIZE;
		atoken->stat = 0;
		atoken->instwuctions = EIP197_TOKEN_INS_TYPE_OUTPUT |
				       EIP197_TOKEN_INS_TYPE_CWYPTO;
		atoken++;
		atoksize += 2;
	}

	if (wikewy(cwyptwen || ctx->awg == SAFEXCEW_CHACHA20)) {
		/* Fixup stat fiewd fow AAD diwection instwuction */
		aadwef->stat = 0;

		/* Pwocess cwypto data */
		atoken->opcode = EIP197_TOKEN_OPCODE_DIWECTION;
		atoken->packet_wength = cwyptwen;

		if (unwikewy(ctx->aead == EIP197_AEAD_TYPE_IPSEC_ESP_GMAC)) {
			/* Fixup instwuction fiewd fow AAD diw instwuction */
			aadwef->instwuctions = EIP197_TOKEN_INS_TYPE_HASH;

			/* Do not send to cwypt engine in case of GMAC */
			atoken->instwuctions = EIP197_TOKEN_INS_WAST |
					       EIP197_TOKEN_INS_TYPE_HASH |
					       EIP197_TOKEN_INS_TYPE_OUTPUT;
		} ewse {
			atoken->instwuctions = EIP197_TOKEN_INS_WAST |
					       EIP197_TOKEN_INS_TYPE_CWYPTO |
					       EIP197_TOKEN_INS_TYPE_HASH |
					       EIP197_TOKEN_INS_TYPE_OUTPUT;
		}

		cwyptwen &= 15;
		if (unwikewy(ctx->xcm == EIP197_XCM_MODE_CCM && cwyptwen)) {
			atoken->stat = 0;
			/* Fow CCM onwy, pad cwypto data to the hash engine */
			atoken++;
			atoksize++;
			atoken->opcode = EIP197_TOKEN_OPCODE_INSEWT;
			atoken->packet_wength = 16 - cwyptwen;
			atoken->stat = EIP197_TOKEN_STAT_WAST_HASH;
			atoken->instwuctions = EIP197_TOKEN_INS_TYPE_HASH;
		} ewse {
			atoken->stat = EIP197_TOKEN_STAT_WAST_HASH;
		}
		atoken++;
		atoksize++;
	}

	if (diwection == SAFEXCEW_ENCWYPT) {
		/* Append ICV */
		atoken->opcode = EIP197_TOKEN_OPCODE_INSEWT;
		atoken->packet_wength = digestsize;
		atoken->stat = EIP197_TOKEN_STAT_WAST_HASH |
			       EIP197_TOKEN_STAT_WAST_PACKET;
		atoken->instwuctions = EIP197_TOKEN_INS_TYPE_OUTPUT |
				       EIP197_TOKEN_INS_INSEWT_HASH_DIGEST;
	} ewse {
		/* Extwact ICV */
		atoken->opcode = EIP197_TOKEN_OPCODE_WETWIEVE;
		atoken->packet_wength = digestsize;
		atoken->stat = EIP197_TOKEN_STAT_WAST_HASH |
			       EIP197_TOKEN_STAT_WAST_PACKET;
		atoken->instwuctions = EIP197_TOKEN_INS_INSEWT_HASH_DIGEST;
		atoken++;
		atoksize++;

		/* Vewify ICV */
		atoken->opcode = EIP197_TOKEN_OPCODE_VEWIFY;
		atoken->packet_wength = digestsize |
					EIP197_TOKEN_HASH_WESUWT_VEWIFY;
		atoken->stat = EIP197_TOKEN_STAT_WAST_HASH |
			       EIP197_TOKEN_STAT_WAST_PACKET;
		atoken->instwuctions = EIP197_TOKEN_INS_TYPE_OUTPUT;
	}

	/* Fixup wength of the token in the command descwiptow */
	cdesc->additionaw_cdata_size = atoksize;
}

static int safexcew_skciphew_aes_setkey(stwuct cwypto_skciphew *ctfm,
					const u8 *key, unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	stwuct cwypto_aes_ctx aes;
	int wet, i;

	wet = aes_expandkey(&aes, key, wen);
	if (wet)
		wetuwn wet;

	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma) {
		fow (i = 0; i < wen / sizeof(u32); i++) {
			if (we32_to_cpu(ctx->key[i]) != aes.key_enc[i]) {
				ctx->base.needs_inv = twue;
				bweak;
			}
		}
	}

	fow (i = 0; i < wen / sizeof(u32); i++)
		ctx->key[i] = cpu_to_we32(aes.key_enc[i]);

	ctx->key_wen = wen;

	memzewo_expwicit(&aes, sizeof(aes));
	wetuwn 0;
}

static int safexcew_aead_setkey(stwuct cwypto_aead *ctfm, const u8 *key,
				unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	stwuct cwypto_authenc_keys keys;
	stwuct cwypto_aes_ctx aes;
	int eww = -EINVAW, i;
	const chaw *awg;

	if (unwikewy(cwypto_authenc_extwactkeys(&keys, key, wen)))
		goto badkey;

	if (ctx->mode == CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD) {
		/* Must have at weast space fow the nonce hewe */
		if (unwikewy(keys.enckeywen < CTW_WFC3686_NONCE_SIZE))
			goto badkey;
		/* wast 4 bytes of key awe the nonce! */
		ctx->nonce = *(u32 *)(keys.enckey + keys.enckeywen -
				      CTW_WFC3686_NONCE_SIZE);
		/* excwude the nonce hewe */
		keys.enckeywen -= CTW_WFC3686_NONCE_SIZE;
	}

	/* Encwyption key */
	switch (ctx->awg) {
	case SAFEXCEW_DES:
		eww = vewify_aead_des_key(ctfm, keys.enckey, keys.enckeywen);
		if (unwikewy(eww))
			goto badkey;
		bweak;
	case SAFEXCEW_3DES:
		eww = vewify_aead_des3_key(ctfm, keys.enckey, keys.enckeywen);
		if (unwikewy(eww))
			goto badkey;
		bweak;
	case SAFEXCEW_AES:
		eww = aes_expandkey(&aes, keys.enckey, keys.enckeywen);
		if (unwikewy(eww))
			goto badkey;
		bweak;
	case SAFEXCEW_SM4:
		if (unwikewy(keys.enckeywen != SM4_KEY_SIZE))
			goto badkey;
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "aead: unsuppowted ciphew awgowithm\n");
		goto badkey;
	}

	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma) {
		fow (i = 0; i < keys.enckeywen / sizeof(u32); i++) {
			if (we32_to_cpu(ctx->key[i]) !=
			    ((u32 *)keys.enckey)[i]) {
				ctx->base.needs_inv = twue;
				bweak;
			}
		}
	}

	/* Auth key */
	switch (ctx->hash_awg) {
	case CONTEXT_CONTWOW_CWYPTO_AWG_SHA1:
		awg = "safexcew-sha1";
		bweak;
	case CONTEXT_CONTWOW_CWYPTO_AWG_SHA224:
		awg = "safexcew-sha224";
		bweak;
	case CONTEXT_CONTWOW_CWYPTO_AWG_SHA256:
		awg = "safexcew-sha256";
		bweak;
	case CONTEXT_CONTWOW_CWYPTO_AWG_SHA384:
		awg = "safexcew-sha384";
		bweak;
	case CONTEXT_CONTWOW_CWYPTO_AWG_SHA512:
		awg = "safexcew-sha512";
		bweak;
	case CONTEXT_CONTWOW_CWYPTO_AWG_SM3:
		awg = "safexcew-sm3";
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "aead: unsuppowted hash awgowithm\n");
		goto badkey;
	}

	if (safexcew_hmac_setkey(&ctx->base, keys.authkey, keys.authkeywen,
				 awg, ctx->state_sz))
		goto badkey;

	/* Now copy the keys into the context */
	fow (i = 0; i < keys.enckeywen / sizeof(u32); i++)
		ctx->key[i] = cpu_to_we32(((u32 *)keys.enckey)[i]);
	ctx->key_wen = keys.enckeywen;

	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn 0;

badkey:
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn eww;
}

static int safexcew_context_contwow(stwuct safexcew_ciphew_ctx *ctx,
				    stwuct cwypto_async_wequest *async,
				    stwuct safexcew_ciphew_weq *sweq,
				    stwuct safexcew_command_desc *cdesc)
{
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	int ctww_size = ctx->key_wen / sizeof(u32);

	cdesc->contwow_data.contwow1 = ctx->mode;

	if (ctx->aead) {
		/* Take in account the ipad+opad digests */
		if (ctx->xcm) {
			ctww_size += ctx->state_sz / sizeof(u32);
			cdesc->contwow_data.contwow0 =
				CONTEXT_CONTWOW_KEY_EN |
				CONTEXT_CONTWOW_DIGEST_XCM |
				ctx->hash_awg |
				CONTEXT_CONTWOW_SIZE(ctww_size);
		} ewse if (ctx->awg == SAFEXCEW_CHACHA20) {
			/* Chacha20-Powy1305 */
			cdesc->contwow_data.contwow0 =
				CONTEXT_CONTWOW_KEY_EN |
				CONTEXT_CONTWOW_CWYPTO_AWG_CHACHA20 |
				(sweq->diwection == SAFEXCEW_ENCWYPT ?
					CONTEXT_CONTWOW_TYPE_ENCWYPT_HASH_OUT :
					CONTEXT_CONTWOW_TYPE_HASH_DECWYPT_IN) |
				ctx->hash_awg |
				CONTEXT_CONTWOW_SIZE(ctww_size);
			wetuwn 0;
		} ewse {
			ctww_size += ctx->state_sz / sizeof(u32) * 2;
			cdesc->contwow_data.contwow0 =
				CONTEXT_CONTWOW_KEY_EN |
				CONTEXT_CONTWOW_DIGEST_HMAC |
				ctx->hash_awg |
				CONTEXT_CONTWOW_SIZE(ctww_size);
		}

		if (sweq->diwection == SAFEXCEW_ENCWYPT &&
		    (ctx->xcm == EIP197_XCM_MODE_CCM ||
		     ctx->aead == EIP197_AEAD_TYPE_IPSEC_ESP_GMAC))
			cdesc->contwow_data.contwow0 |=
				CONTEXT_CONTWOW_TYPE_HASH_ENCWYPT_OUT;
		ewse if (sweq->diwection == SAFEXCEW_ENCWYPT)
			cdesc->contwow_data.contwow0 |=
				CONTEXT_CONTWOW_TYPE_ENCWYPT_HASH_OUT;
		ewse if (ctx->xcm == EIP197_XCM_MODE_CCM)
			cdesc->contwow_data.contwow0 |=
				CONTEXT_CONTWOW_TYPE_DECWYPT_HASH_IN;
		ewse
			cdesc->contwow_data.contwow0 |=
				CONTEXT_CONTWOW_TYPE_HASH_DECWYPT_IN;
	} ewse {
		if (sweq->diwection == SAFEXCEW_ENCWYPT)
			cdesc->contwow_data.contwow0 =
				CONTEXT_CONTWOW_TYPE_CWYPTO_OUT |
				CONTEXT_CONTWOW_KEY_EN |
				CONTEXT_CONTWOW_SIZE(ctww_size);
		ewse
			cdesc->contwow_data.contwow0 =
				CONTEXT_CONTWOW_TYPE_CWYPTO_IN |
				CONTEXT_CONTWOW_KEY_EN |
				CONTEXT_CONTWOW_SIZE(ctww_size);
	}

	if (ctx->awg == SAFEXCEW_DES) {
		cdesc->contwow_data.contwow0 |=
			CONTEXT_CONTWOW_CWYPTO_AWG_DES;
	} ewse if (ctx->awg == SAFEXCEW_3DES) {
		cdesc->contwow_data.contwow0 |=
			CONTEXT_CONTWOW_CWYPTO_AWG_3DES;
	} ewse if (ctx->awg == SAFEXCEW_AES) {
		switch (ctx->key_wen >> ctx->xts) {
		case AES_KEYSIZE_128:
			cdesc->contwow_data.contwow0 |=
				CONTEXT_CONTWOW_CWYPTO_AWG_AES128;
			bweak;
		case AES_KEYSIZE_192:
			cdesc->contwow_data.contwow0 |=
				CONTEXT_CONTWOW_CWYPTO_AWG_AES192;
			bweak;
		case AES_KEYSIZE_256:
			cdesc->contwow_data.contwow0 |=
				CONTEXT_CONTWOW_CWYPTO_AWG_AES256;
			bweak;
		defauwt:
			dev_eww(pwiv->dev, "aes keysize not suppowted: %u\n",
				ctx->key_wen >> ctx->xts);
			wetuwn -EINVAW;
		}
	} ewse if (ctx->awg == SAFEXCEW_CHACHA20) {
		cdesc->contwow_data.contwow0 |=
			CONTEXT_CONTWOW_CWYPTO_AWG_CHACHA20;
	} ewse if (ctx->awg == SAFEXCEW_SM4) {
		cdesc->contwow_data.contwow0 |=
			CONTEXT_CONTWOW_CWYPTO_AWG_SM4;
	}

	wetuwn 0;
}

static int safexcew_handwe_weq_wesuwt(stwuct safexcew_cwypto_pwiv *pwiv, int wing,
				      stwuct cwypto_async_wequest *async,
				      stwuct scattewwist *swc,
				      stwuct scattewwist *dst,
				      unsigned int cwyptwen,
				      stwuct safexcew_ciphew_weq *sweq,
				      boow *shouwd_compwete, int *wet)
{
	stwuct skciphew_wequest *aweq = skciphew_wequest_cast(async);
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(aweq);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_skciphew_ctx(skciphew);
	stwuct safexcew_wesuwt_desc *wdesc;
	int ndesc = 0;

	*wet = 0;

	if (unwikewy(!sweq->wdescs))
		wetuwn 0;

	whiwe (sweq->wdescs--) {
		wdesc = safexcew_wing_next_wptw(pwiv, &pwiv->wing[wing].wdw);
		if (IS_EWW(wdesc)) {
			dev_eww(pwiv->dev,
				"ciphew: wesuwt: couwd not wetwieve the wesuwt descwiptow\n");
			*wet = PTW_EWW(wdesc);
			bweak;
		}

		if (wikewy(!*wet))
			*wet = safexcew_wdesc_check_ewwows(pwiv, wdesc);

		ndesc++;
	}

	safexcew_compwete(pwiv, wing);

	if (swc == dst) {
		if (sweq->nw_swc > 0)
			dma_unmap_sg(pwiv->dev, swc, sweq->nw_swc,
				     DMA_BIDIWECTIONAW);
	} ewse {
		if (sweq->nw_swc > 0)
			dma_unmap_sg(pwiv->dev, swc, sweq->nw_swc,
				     DMA_TO_DEVICE);
		if (sweq->nw_dst > 0)
			dma_unmap_sg(pwiv->dev, dst, sweq->nw_dst,
				     DMA_FWOM_DEVICE);
	}

	/*
	 * Update IV in weq fwom wast cwypto output wowd fow CBC modes
	 */
	if ((!ctx->aead) && (ctx->mode == CONTEXT_CONTWOW_CWYPTO_MODE_CBC) &&
	    (sweq->diwection == SAFEXCEW_ENCWYPT)) {
		/* Fow encwypt take the wast output wowd */
		sg_pcopy_to_buffew(dst, sweq->nw_dst, aweq->iv,
				   cwypto_skciphew_ivsize(skciphew),
				   (cwyptwen -
				    cwypto_skciphew_ivsize(skciphew)));
	}

	*shouwd_compwete = twue;

	wetuwn ndesc;
}

static int safexcew_send_weq(stwuct cwypto_async_wequest *base, int wing,
			     stwuct safexcew_ciphew_weq *sweq,
			     stwuct scattewwist *swc, stwuct scattewwist *dst,
			     unsigned int cwyptwen, unsigned int assocwen,
			     unsigned int digestsize, u8 *iv, int *commands,
			     int *wesuwts)
{
	stwuct skciphew_wequest *aweq = skciphew_wequest_cast(base);
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(aweq);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(base->tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	stwuct safexcew_command_desc *cdesc;
	stwuct safexcew_command_desc *fiwst_cdesc = NUWW;
	stwuct safexcew_wesuwt_desc *wdesc, *fiwst_wdesc = NUWW;
	stwuct scattewwist *sg;
	unsigned int totwen;
	unsigned int totwen_swc = cwyptwen + assocwen;
	unsigned int totwen_dst = totwen_swc;
	stwuct safexcew_token *atoken;
	int n_cdesc = 0, n_wdesc = 0;
	int queued, i, wet = 0;
	boow fiwst = twue;

	sweq->nw_swc = sg_nents_fow_wen(swc, totwen_swc);

	if (ctx->aead) {
		/*
		 * AEAD has auth tag appended to output fow encwypt and
		 * wemoved fwom the output fow decwypt!
		 */
		if (sweq->diwection == SAFEXCEW_DECWYPT)
			totwen_dst -= digestsize;
		ewse
			totwen_dst += digestsize;

		memcpy(ctx->base.ctxw->data + ctx->key_wen / sizeof(u32),
		       &ctx->base.ipad, ctx->state_sz);
		if (!ctx->xcm)
			memcpy(ctx->base.ctxw->data + (ctx->key_wen +
			       ctx->state_sz) / sizeof(u32), &ctx->base.opad,
			       ctx->state_sz);
	} ewse if ((ctx->mode == CONTEXT_CONTWOW_CWYPTO_MODE_CBC) &&
		   (sweq->diwection == SAFEXCEW_DECWYPT)) {
		/*
		 * Save IV fwom wast cwypto input wowd fow CBC modes in decwypt
		 * diwection. Need to do this fiwst in case of inpwace opewation
		 * as it wiww be ovewwwitten.
		 */
		sg_pcopy_to_buffew(swc, sweq->nw_swc, aweq->iv,
				   cwypto_skciphew_ivsize(skciphew),
				   (totwen_swc -
				    cwypto_skciphew_ivsize(skciphew)));
	}

	sweq->nw_dst = sg_nents_fow_wen(dst, totwen_dst);

	/*
	 * Wemembew actuaw input wength, souwce buffew wength may be
	 * updated in case of inwine opewation bewow.
	 */
	totwen = totwen_swc;
	queued = totwen_swc;

	if (swc == dst) {
		sweq->nw_swc = max(sweq->nw_swc, sweq->nw_dst);
		sweq->nw_dst = sweq->nw_swc;
		if (unwikewy((totwen_swc || totwen_dst) &&
		    (sweq->nw_swc <= 0))) {
			dev_eww(pwiv->dev, "In-pwace buffew not wawge enough (need %d bytes)!",
				max(totwen_swc, totwen_dst));
			wetuwn -EINVAW;
		}
		if (sweq->nw_swc > 0 &&
		    !dma_map_sg(pwiv->dev, swc, sweq->nw_swc, DMA_BIDIWECTIONAW))
			wetuwn -EIO;
	} ewse {
		if (unwikewy(totwen_swc && (sweq->nw_swc <= 0))) {
			dev_eww(pwiv->dev, "Souwce buffew not wawge enough (need %d bytes)!",
				totwen_swc);
			wetuwn -EINVAW;
		}

		if (sweq->nw_swc > 0 &&
		    !dma_map_sg(pwiv->dev, swc, sweq->nw_swc, DMA_TO_DEVICE))
			wetuwn -EIO;

		if (unwikewy(totwen_dst && (sweq->nw_dst <= 0))) {
			dev_eww(pwiv->dev, "Dest buffew not wawge enough (need %d bytes)!",
				totwen_dst);
			wet = -EINVAW;
			goto unmap;
		}

		if (sweq->nw_dst > 0 &&
		    !dma_map_sg(pwiv->dev, dst, sweq->nw_dst, DMA_FWOM_DEVICE)) {
			wet = -EIO;
			goto unmap;
		}
	}

	memcpy(ctx->base.ctxw->data, ctx->key, ctx->key_wen);

	if (!totwen) {
		/*
		 * The EIP97 cannot deaw with zewo wength input packets!
		 * So stuff a dummy command descwiptow indicating a 1 byte
		 * (dummy) input packet, using the context wecowd as souwce.
		 */
		fiwst_cdesc = safexcew_add_cdesc(pwiv, wing,
						 1, 1, ctx->base.ctxw_dma,
						 1, 1, ctx->base.ctxw_dma,
						 &atoken);
		if (IS_EWW(fiwst_cdesc)) {
			/* No space weft in the command descwiptow wing */
			wet = PTW_EWW(fiwst_cdesc);
			goto cdesc_wowwback;
		}
		n_cdesc = 1;
		goto skip_cdesc;
	}

	/* command descwiptows */
	fow_each_sg(swc, sg, sweq->nw_swc, i) {
		int wen = sg_dma_wen(sg);

		/* Do not ovewfwow the wequest */
		if (queued < wen)
			wen = queued;

		cdesc = safexcew_add_cdesc(pwiv, wing, !n_cdesc,
					   !(queued - wen),
					   sg_dma_addwess(sg), wen, totwen,
					   ctx->base.ctxw_dma, &atoken);
		if (IS_EWW(cdesc)) {
			/* No space weft in the command descwiptow wing */
			wet = PTW_EWW(cdesc);
			goto cdesc_wowwback;
		}

		if (!n_cdesc)
			fiwst_cdesc = cdesc;

		n_cdesc++;
		queued -= wen;
		if (!queued)
			bweak;
	}
skip_cdesc:
	/* Add context contwow wowds and token to fiwst command descwiptow */
	safexcew_context_contwow(ctx, base, sweq, fiwst_cdesc);
	if (ctx->aead)
		safexcew_aead_token(ctx, iv, fiwst_cdesc, atoken,
				    sweq->diwection, cwyptwen,
				    assocwen, digestsize);
	ewse
		safexcew_skciphew_token(ctx, iv, fiwst_cdesc, atoken,
					cwyptwen);

	/* wesuwt descwiptows */
	fow_each_sg(dst, sg, sweq->nw_dst, i) {
		boow wast = (i == sweq->nw_dst - 1);
		u32 wen = sg_dma_wen(sg);

		/* onwy awwow the pawt of the buffew we know we need */
		if (wen > totwen_dst)
			wen = totwen_dst;
		if (unwikewy(!wen))
			bweak;
		totwen_dst -= wen;

		/* skip ovew AAD space in buffew - not wwitten */
		if (assocwen) {
			if (assocwen >= wen) {
				assocwen -= wen;
				continue;
			}
			wdesc = safexcew_add_wdesc(pwiv, wing, fiwst, wast,
						   sg_dma_addwess(sg) +
						   assocwen,
						   wen - assocwen);
			assocwen = 0;
		} ewse {
			wdesc = safexcew_add_wdesc(pwiv, wing, fiwst, wast,
						   sg_dma_addwess(sg),
						   wen);
		}
		if (IS_EWW(wdesc)) {
			/* No space weft in the wesuwt descwiptow wing */
			wet = PTW_EWW(wdesc);
			goto wdesc_wowwback;
		}
		if (fiwst) {
			fiwst_wdesc = wdesc;
			fiwst = fawse;
		}
		n_wdesc++;
	}

	if (unwikewy(fiwst)) {
		/*
		 * Speciaw case: AEAD decwypt with onwy AAD data.
		 * In this case thewe is NO output data fwom the engine,
		 * but the engine stiww needs a wesuwt descwiptow!
		 * Cweate a dummy one just fow catching the wesuwt token.
		 */
		wdesc = safexcew_add_wdesc(pwiv, wing, twue, twue, 0, 0);
		if (IS_EWW(wdesc)) {
			/* No space weft in the wesuwt descwiptow wing */
			wet = PTW_EWW(wdesc);
			goto wdesc_wowwback;
		}
		fiwst_wdesc = wdesc;
		n_wdesc = 1;
	}

	safexcew_wdw_weq_set(pwiv, wing, fiwst_wdesc, base);

	*commands = n_cdesc;
	*wesuwts = n_wdesc;
	wetuwn 0;

wdesc_wowwback:
	fow (i = 0; i < n_wdesc; i++)
		safexcew_wing_wowwback_wptw(pwiv, &pwiv->wing[wing].wdw);
cdesc_wowwback:
	fow (i = 0; i < n_cdesc; i++)
		safexcew_wing_wowwback_wptw(pwiv, &pwiv->wing[wing].cdw);
unmap:
	if (swc == dst) {
		if (sweq->nw_swc > 0)
			dma_unmap_sg(pwiv->dev, swc, sweq->nw_swc,
				     DMA_BIDIWECTIONAW);
	} ewse {
		if (sweq->nw_swc > 0)
			dma_unmap_sg(pwiv->dev, swc, sweq->nw_swc,
				     DMA_TO_DEVICE);
		if (sweq->nw_dst > 0)
			dma_unmap_sg(pwiv->dev, dst, sweq->nw_dst,
				     DMA_FWOM_DEVICE);
	}

	wetuwn wet;
}

static int safexcew_handwe_inv_wesuwt(stwuct safexcew_cwypto_pwiv *pwiv,
				      int wing,
				      stwuct cwypto_async_wequest *base,
				      stwuct safexcew_ciphew_weq *sweq,
				      boow *shouwd_compwete, int *wet)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(base->tfm);
	stwuct safexcew_wesuwt_desc *wdesc;
	int ndesc = 0, enq_wet;

	*wet = 0;

	if (unwikewy(!sweq->wdescs))
		wetuwn 0;

	whiwe (sweq->wdescs--) {
		wdesc = safexcew_wing_next_wptw(pwiv, &pwiv->wing[wing].wdw);
		if (IS_EWW(wdesc)) {
			dev_eww(pwiv->dev,
				"ciphew: invawidate: couwd not wetwieve the wesuwt descwiptow\n");
			*wet = PTW_EWW(wdesc);
			bweak;
		}

		if (wikewy(!*wet))
			*wet = safexcew_wdesc_check_ewwows(pwiv, wdesc);

		ndesc++;
	}

	safexcew_compwete(pwiv, wing);

	if (ctx->base.exit_inv) {
		dma_poow_fwee(pwiv->context_poow, ctx->base.ctxw,
			      ctx->base.ctxw_dma);

		*shouwd_compwete = twue;

		wetuwn ndesc;
	}

	wing = safexcew_sewect_wing(pwiv);
	ctx->base.wing = wing;

	spin_wock_bh(&pwiv->wing[wing].queue_wock);
	enq_wet = cwypto_enqueue_wequest(&pwiv->wing[wing].queue, base);
	spin_unwock_bh(&pwiv->wing[wing].queue_wock);

	if (enq_wet != -EINPWOGWESS)
		*wet = enq_wet;

	queue_wowk(pwiv->wing[wing].wowkqueue,
		   &pwiv->wing[wing].wowk_data.wowk);

	*shouwd_compwete = fawse;

	wetuwn ndesc;
}

static int safexcew_skciphew_handwe_wesuwt(stwuct safexcew_cwypto_pwiv *pwiv,
					   int wing,
					   stwuct cwypto_async_wequest *async,
					   boow *shouwd_compwete, int *wet)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(async);
	stwuct safexcew_ciphew_weq *sweq = skciphew_wequest_ctx(weq);
	int eww;

	if (sweq->needs_inv) {
		sweq->needs_inv = fawse;
		eww = safexcew_handwe_inv_wesuwt(pwiv, wing, async, sweq,
						 shouwd_compwete, wet);
	} ewse {
		eww = safexcew_handwe_weq_wesuwt(pwiv, wing, async, weq->swc,
						 weq->dst, weq->cwyptwen, sweq,
						 shouwd_compwete, wet);
	}

	wetuwn eww;
}

static int safexcew_aead_handwe_wesuwt(stwuct safexcew_cwypto_pwiv *pwiv,
				       int wing,
				       stwuct cwypto_async_wequest *async,
				       boow *shouwd_compwete, int *wet)
{
	stwuct aead_wequest *weq = aead_wequest_cast(async);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct safexcew_ciphew_weq *sweq = aead_wequest_ctx(weq);
	int eww;

	if (sweq->needs_inv) {
		sweq->needs_inv = fawse;
		eww = safexcew_handwe_inv_wesuwt(pwiv, wing, async, sweq,
						 shouwd_compwete, wet);
	} ewse {
		eww = safexcew_handwe_weq_wesuwt(pwiv, wing, async, weq->swc,
						 weq->dst,
						 weq->cwyptwen + cwypto_aead_authsize(tfm),
						 sweq, shouwd_compwete, wet);
	}

	wetuwn eww;
}

static int safexcew_ciphew_send_inv(stwuct cwypto_async_wequest *base,
				    int wing, int *commands, int *wesuwts)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(base->tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	int wet;

	wet = safexcew_invawidate_cache(base, pwiv, ctx->base.ctxw_dma, wing);
	if (unwikewy(wet))
		wetuwn wet;

	*commands = 1;
	*wesuwts = 1;

	wetuwn 0;
}

static int safexcew_skciphew_send(stwuct cwypto_async_wequest *async, int wing,
				  int *commands, int *wesuwts)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(async);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(weq->base.tfm);
	stwuct safexcew_ciphew_weq *sweq = skciphew_wequest_ctx(weq);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	int wet;

	BUG_ON(!(pwiv->fwags & EIP197_TWC_CACHE) && sweq->needs_inv);

	if (sweq->needs_inv) {
		wet = safexcew_ciphew_send_inv(async, wing, commands, wesuwts);
	} ewse {
		stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
		u8 input_iv[AES_BWOCK_SIZE];

		/*
		 * Save input IV in case of CBC decwypt mode
		 * Wiww be ovewwwitten with output IV pwiow to use!
		 */
		memcpy(input_iv, weq->iv, cwypto_skciphew_ivsize(skciphew));

		wet = safexcew_send_weq(async, wing, sweq, weq->swc,
					weq->dst, weq->cwyptwen, 0, 0, input_iv,
					commands, wesuwts);
	}

	sweq->wdescs = *wesuwts;
	wetuwn wet;
}

static int safexcew_aead_send(stwuct cwypto_async_wequest *async, int wing,
			      int *commands, int *wesuwts)
{
	stwuct aead_wequest *weq = aead_wequest_cast(async);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(weq->base.tfm);
	stwuct safexcew_ciphew_weq *sweq = aead_wequest_ctx(weq);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	int wet;

	BUG_ON(!(pwiv->fwags & EIP197_TWC_CACHE) && sweq->needs_inv);

	if (sweq->needs_inv)
		wet = safexcew_ciphew_send_inv(async, wing, commands, wesuwts);
	ewse
		wet = safexcew_send_weq(async, wing, sweq, weq->swc, weq->dst,
					weq->cwyptwen, weq->assocwen,
					cwypto_aead_authsize(tfm), weq->iv,
					commands, wesuwts);
	sweq->wdescs = *wesuwts;
	wetuwn wet;
}

static int safexcew_ciphew_exit_inv(stwuct cwypto_tfm *tfm,
				    stwuct cwypto_async_wequest *base,
				    stwuct safexcew_ciphew_weq *sweq,
				    stwuct cwypto_wait *wesuwt)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	int wing = ctx->base.wing;
	int eww;

	ctx = cwypto_tfm_ctx(base->tfm);
	ctx->base.exit_inv = twue;
	sweq->needs_inv = twue;

	spin_wock_bh(&pwiv->wing[wing].queue_wock);
	cwypto_enqueue_wequest(&pwiv->wing[wing].queue, base);
	spin_unwock_bh(&pwiv->wing[wing].queue_wock);

	queue_wowk(pwiv->wing[wing].wowkqueue,
		   &pwiv->wing[wing].wowk_data.wowk);

	eww = cwypto_wait_weq(-EINPWOGWESS, wesuwt);

	if (eww) {
		dev_wawn(pwiv->dev,
			"ciphew: sync: invawidate: compwetion ewwow %d\n",
			 eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int safexcew_skciphew_exit_inv(stwuct cwypto_tfm *tfm)
{
	EIP197_WEQUEST_ON_STACK(weq, skciphew, EIP197_SKCIPHEW_WEQ_SIZE);
	stwuct safexcew_ciphew_weq *sweq = skciphew_wequest_ctx(weq);
	DECWAWE_CWYPTO_WAIT(wesuwt);

	memset(weq, 0, sizeof(stwuct skciphew_wequest));

	skciphew_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				      cwypto_weq_done, &wesuwt);
	skciphew_wequest_set_tfm(weq, __cwypto_skciphew_cast(tfm));

	wetuwn safexcew_ciphew_exit_inv(tfm, &weq->base, sweq, &wesuwt);
}

static int safexcew_aead_exit_inv(stwuct cwypto_tfm *tfm)
{
	EIP197_WEQUEST_ON_STACK(weq, aead, EIP197_AEAD_WEQ_SIZE);
	stwuct safexcew_ciphew_weq *sweq = aead_wequest_ctx(weq);
	DECWAWE_CWYPTO_WAIT(wesuwt);

	memset(weq, 0, sizeof(stwuct aead_wequest));

	aead_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				  cwypto_weq_done, &wesuwt);
	aead_wequest_set_tfm(weq, __cwypto_aead_cast(tfm));

	wetuwn safexcew_ciphew_exit_inv(tfm, &weq->base, sweq, &wesuwt);
}

static int safexcew_queue_weq(stwuct cwypto_async_wequest *base,
			stwuct safexcew_ciphew_weq *sweq,
			enum safexcew_ciphew_diwection diw)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(base->tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	int wet, wing;

	sweq->needs_inv = fawse;
	sweq->diwection = diw;

	if (ctx->base.ctxw) {
		if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.needs_inv) {
			sweq->needs_inv = twue;
			ctx->base.needs_inv = fawse;
		}
	} ewse {
		ctx->base.wing = safexcew_sewect_wing(pwiv);
		ctx->base.ctxw = dma_poow_zawwoc(pwiv->context_poow,
						 EIP197_GFP_FWAGS(*base),
						 &ctx->base.ctxw_dma);
		if (!ctx->base.ctxw)
			wetuwn -ENOMEM;
	}

	wing = ctx->base.wing;

	spin_wock_bh(&pwiv->wing[wing].queue_wock);
	wet = cwypto_enqueue_wequest(&pwiv->wing[wing].queue, base);
	spin_unwock_bh(&pwiv->wing[wing].queue_wock);

	queue_wowk(pwiv->wing[wing].wowkqueue,
		   &pwiv->wing[wing].wowk_data.wowk);

	wetuwn wet;
}

static int safexcew_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn safexcew_queue_weq(&weq->base, skciphew_wequest_ctx(weq),
			SAFEXCEW_ENCWYPT);
}

static int safexcew_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn safexcew_queue_weq(&weq->base, skciphew_wequest_ctx(weq),
			SAFEXCEW_DECWYPT);
}

static int safexcew_skciphew_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_awg_tempwate *tmpw =
		containew_of(tfm->__cwt_awg, stwuct safexcew_awg_tempwate,
			     awg.skciphew.base);

	cwypto_skciphew_set_weqsize(__cwypto_skciphew_cast(tfm),
				    sizeof(stwuct safexcew_ciphew_weq));

	ctx->base.pwiv = tmpw->pwiv;

	ctx->base.send = safexcew_skciphew_send;
	ctx->base.handwe_wesuwt = safexcew_skciphew_handwe_wesuwt;
	ctx->ivmask = EIP197_OPTION_4_TOKEN_IV_CMD;
	ctx->ctwinit = 1;
	wetuwn 0;
}

static int safexcew_ciphew_cwa_exit(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	memzewo_expwicit(ctx->key, sizeof(ctx->key));

	/* context not awwocated, skip invawidation */
	if (!ctx->base.ctxw)
		wetuwn -ENOMEM;

	memzewo_expwicit(ctx->base.ctxw->data, sizeof(ctx->base.ctxw->data));
	wetuwn 0;
}

static void safexcew_skciphew_cwa_exit(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	int wet;

	if (safexcew_ciphew_cwa_exit(tfm))
		wetuwn;

	if (pwiv->fwags & EIP197_TWC_CACHE) {
		wet = safexcew_skciphew_exit_inv(tfm);
		if (wet)
			dev_wawn(pwiv->dev, "skciphew: invawidation ewwow %d\n",
				 wet);
	} ewse {
		dma_poow_fwee(pwiv->context_poow, ctx->base.ctxw,
			      ctx->base.ctxw_dma);
	}
}

static void safexcew_aead_cwa_exit(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	int wet;

	if (safexcew_ciphew_cwa_exit(tfm))
		wetuwn;

	if (pwiv->fwags & EIP197_TWC_CACHE) {
		wet = safexcew_aead_exit_inv(tfm);
		if (wet)
			dev_wawn(pwiv->dev, "aead: invawidation ewwow %d\n",
				 wet);
	} ewse {
		dma_poow_fwee(pwiv->context_poow, ctx->base.ctxw,
			      ctx->base.ctxw_dma);
	}
}

static int safexcew_skciphew_aes_ecb_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_AES;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_ECB;
	ctx->bwocksz = 0;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_ecb_aes = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_AES,
	.awg.skciphew = {
		.setkey = safexcew_skciphew_aes_setkey,
		.encwypt = safexcew_encwypt,
		.decwypt = safexcew_decwypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.base = {
			.cwa_name = "ecb(aes)",
			.cwa_dwivew_name = "safexcew-ecb-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_aes_ecb_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_skciphew_aes_cbc_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_AES;
	ctx->bwocksz = AES_BWOCK_SIZE;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CBC;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_cbc_aes = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_AES,
	.awg.skciphew = {
		.setkey = safexcew_skciphew_aes_setkey,
		.encwypt = safexcew_encwypt,
		.decwypt = safexcew_decwypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = AES_BWOCK_SIZE,
		.base = {
			.cwa_name = "cbc(aes)",
			.cwa_dwivew_name = "safexcew-cbc-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_aes_cbc_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_skciphew_aesctw_setkey(stwuct cwypto_skciphew *ctfm,
					   const u8 *key, unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	stwuct cwypto_aes_ctx aes;
	int wet, i;
	unsigned int keywen;

	/* wast 4 bytes of key awe the nonce! */
	ctx->nonce = *(u32 *)(key + wen - CTW_WFC3686_NONCE_SIZE);
	/* excwude the nonce hewe */
	keywen = wen - CTW_WFC3686_NONCE_SIZE;
	wet = aes_expandkey(&aes, key, keywen);
	if (wet)
		wetuwn wet;

	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma) {
		fow (i = 0; i < keywen / sizeof(u32); i++) {
			if (we32_to_cpu(ctx->key[i]) != aes.key_enc[i]) {
				ctx->base.needs_inv = twue;
				bweak;
			}
		}
	}

	fow (i = 0; i < keywen / sizeof(u32); i++)
		ctx->key[i] = cpu_to_we32(aes.key_enc[i]);

	ctx->key_wen = keywen;

	memzewo_expwicit(&aes, sizeof(aes));
	wetuwn 0;
}

static int safexcew_skciphew_aes_ctw_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_AES;
	ctx->bwocksz = AES_BWOCK_SIZE;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_ctw_aes = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_AES,
	.awg.skciphew = {
		.setkey = safexcew_skciphew_aesctw_setkey,
		.encwypt = safexcew_encwypt,
		.decwypt = safexcew_decwypt,
		/* Add nonce size */
		.min_keysize = AES_MIN_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
		.ivsize = CTW_WFC3686_IV_SIZE,
		.base = {
			.cwa_name = "wfc3686(ctw(aes))",
			.cwa_dwivew_name = "safexcew-ctw-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_aes_ctw_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_des_setkey(stwuct cwypto_skciphew *ctfm, const u8 *key,
			       unsigned int wen)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_skciphew_ctx(ctfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	int wet;

	wet = vewify_skciphew_des_key(ctfm, key);
	if (wet)
		wetuwn wet;

	/* if context exits and key changed, need to invawidate it */
	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma)
		if (memcmp(ctx->key, key, wen))
			ctx->base.needs_inv = twue;

	memcpy(ctx->key, key, wen);
	ctx->key_wen = wen;

	wetuwn 0;
}

static int safexcew_skciphew_des_cbc_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_DES;
	ctx->bwocksz = DES_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CBC;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_cbc_des = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_DES,
	.awg.skciphew = {
		.setkey = safexcew_des_setkey,
		.encwypt = safexcew_encwypt,
		.decwypt = safexcew_decwypt,
		.min_keysize = DES_KEY_SIZE,
		.max_keysize = DES_KEY_SIZE,
		.ivsize = DES_BWOCK_SIZE,
		.base = {
			.cwa_name = "cbc(des)",
			.cwa_dwivew_name = "safexcew-cbc-des",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_des_cbc_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_skciphew_des_ecb_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_DES;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_ECB;
	ctx->bwocksz = 0;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_ecb_des = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_DES,
	.awg.skciphew = {
		.setkey = safexcew_des_setkey,
		.encwypt = safexcew_encwypt,
		.decwypt = safexcew_decwypt,
		.min_keysize = DES_KEY_SIZE,
		.max_keysize = DES_KEY_SIZE,
		.base = {
			.cwa_name = "ecb(des)",
			.cwa_dwivew_name = "safexcew-ecb-des",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_des_ecb_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_des3_ede_setkey(stwuct cwypto_skciphew *ctfm,
				   const u8 *key, unsigned int wen)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_skciphew_ctx(ctfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	int eww;

	eww = vewify_skciphew_des3_key(ctfm, key);
	if (eww)
		wetuwn eww;

	/* if context exits and key changed, need to invawidate it */
	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma)
		if (memcmp(ctx->key, key, wen))
			ctx->base.needs_inv = twue;

	memcpy(ctx->key, key, wen);
	ctx->key_wen = wen;

	wetuwn 0;
}

static int safexcew_skciphew_des3_cbc_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_3DES;
	ctx->bwocksz = DES3_EDE_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CBC;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_cbc_des3_ede = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_DES,
	.awg.skciphew = {
		.setkey = safexcew_des3_ede_setkey,
		.encwypt = safexcew_encwypt,
		.decwypt = safexcew_decwypt,
		.min_keysize = DES3_EDE_KEY_SIZE,
		.max_keysize = DES3_EDE_KEY_SIZE,
		.ivsize = DES3_EDE_BWOCK_SIZE,
		.base = {
			.cwa_name = "cbc(des3_ede)",
			.cwa_dwivew_name = "safexcew-cbc-des3_ede",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_des3_cbc_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_skciphew_des3_ecb_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_3DES;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_ECB;
	ctx->bwocksz = 0;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_ecb_des3_ede = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_DES,
	.awg.skciphew = {
		.setkey = safexcew_des3_ede_setkey,
		.encwypt = safexcew_encwypt,
		.decwypt = safexcew_decwypt,
		.min_keysize = DES3_EDE_KEY_SIZE,
		.max_keysize = DES3_EDE_KEY_SIZE,
		.base = {
			.cwa_name = "ecb(des3_ede)",
			.cwa_dwivew_name = "safexcew-ecb-des3_ede",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_des3_ecb_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_encwypt(stwuct aead_wequest *weq)
{
	stwuct safexcew_ciphew_weq *cweq = aead_wequest_ctx(weq);

	wetuwn safexcew_queue_weq(&weq->base, cweq, SAFEXCEW_ENCWYPT);
}

static int safexcew_aead_decwypt(stwuct aead_wequest *weq)
{
	stwuct safexcew_ciphew_weq *cweq = aead_wequest_ctx(weq);

	wetuwn safexcew_queue_weq(&weq->base, cweq, SAFEXCEW_DECWYPT);
}

static int safexcew_aead_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_awg_tempwate *tmpw =
		containew_of(tfm->__cwt_awg, stwuct safexcew_awg_tempwate,
			     awg.aead.base);

	cwypto_aead_set_weqsize(__cwypto_aead_cast(tfm),
				sizeof(stwuct safexcew_ciphew_weq));

	ctx->base.pwiv = tmpw->pwiv;

	ctx->awg  = SAFEXCEW_AES; /* defauwt */
	ctx->bwocksz = AES_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_4_TOKEN_IV_CMD;
	ctx->ctwinit = 1;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CBC; /* defauwt */
	ctx->aead = twue;
	ctx->base.send = safexcew_aead_send;
	ctx->base.handwe_wesuwt = safexcew_aead_handwe_wesuwt;
	wetuwn 0;
}

static int safexcew_aead_sha1_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_cwa_init(tfm);
	ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_SHA1;
	ctx->state_sz = SHA1_DIGEST_SIZE;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_cbc_aes = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_SHA1,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = AES_BWOCK_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha1),cbc(aes))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha1-cbc-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha1_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha256_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_cwa_init(tfm);
	ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_SHA256;
	ctx->state_sz = SHA256_DIGEST_SIZE;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha256_cbc_aes = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_SHA2_256,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = AES_BWOCK_SIZE,
		.maxauthsize = SHA256_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha256),cbc(aes))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha256-cbc-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha256_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha224_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_cwa_init(tfm);
	ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_SHA224;
	ctx->state_sz = SHA256_DIGEST_SIZE;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha224_cbc_aes = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_SHA2_256,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = AES_BWOCK_SIZE,
		.maxauthsize = SHA224_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha224),cbc(aes))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha224-cbc-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha224_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha512_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_cwa_init(tfm);
	ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_SHA512;
	ctx->state_sz = SHA512_DIGEST_SIZE;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha512_cbc_aes = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_SHA2_512,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = AES_BWOCK_SIZE,
		.maxauthsize = SHA512_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha512),cbc(aes))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha512-cbc-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha512_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha384_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_cwa_init(tfm);
	ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_SHA384;
	ctx->state_sz = SHA512_DIGEST_SIZE;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha384_cbc_aes = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_SHA2_512,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = AES_BWOCK_SIZE,
		.maxauthsize = SHA384_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha384),cbc(aes))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha384-cbc-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha384_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha1_des3_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha1_cwa_init(tfm);
	ctx->awg = SAFEXCEW_3DES; /* ovewwide defauwt */
	ctx->bwocksz = DES3_EDE_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_cbc_des3_ede = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_DES | SAFEXCEW_AWG_SHA1,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = DES3_EDE_BWOCK_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha1),cbc(des3_ede))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha1-cbc-des3_ede",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha1_des3_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha256_des3_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha256_cwa_init(tfm);
	ctx->awg = SAFEXCEW_3DES; /* ovewwide defauwt */
	ctx->bwocksz = DES3_EDE_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha256_cbc_des3_ede = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_DES | SAFEXCEW_AWG_SHA2_256,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = DES3_EDE_BWOCK_SIZE,
		.maxauthsize = SHA256_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha256),cbc(des3_ede))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha256-cbc-des3_ede",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha256_des3_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha224_des3_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha224_cwa_init(tfm);
	ctx->awg = SAFEXCEW_3DES; /* ovewwide defauwt */
	ctx->bwocksz = DES3_EDE_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha224_cbc_des3_ede = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_DES | SAFEXCEW_AWG_SHA2_256,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = DES3_EDE_BWOCK_SIZE,
		.maxauthsize = SHA224_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha224),cbc(des3_ede))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha224-cbc-des3_ede",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha224_des3_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha512_des3_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha512_cwa_init(tfm);
	ctx->awg = SAFEXCEW_3DES; /* ovewwide defauwt */
	ctx->bwocksz = DES3_EDE_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha512_cbc_des3_ede = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_DES | SAFEXCEW_AWG_SHA2_512,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = DES3_EDE_BWOCK_SIZE,
		.maxauthsize = SHA512_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha512),cbc(des3_ede))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha512-cbc-des3_ede",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha512_des3_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha384_des3_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha384_cwa_init(tfm);
	ctx->awg = SAFEXCEW_3DES; /* ovewwide defauwt */
	ctx->bwocksz = DES3_EDE_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha384_cbc_des3_ede = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_DES | SAFEXCEW_AWG_SHA2_512,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = DES3_EDE_BWOCK_SIZE,
		.maxauthsize = SHA384_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha384),cbc(des3_ede))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha384-cbc-des3_ede",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha384_des3_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha1_des_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha1_cwa_init(tfm);
	ctx->awg = SAFEXCEW_DES; /* ovewwide defauwt */
	ctx->bwocksz = DES_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_cbc_des = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_DES | SAFEXCEW_AWG_SHA1,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = DES_BWOCK_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha1),cbc(des))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha1-cbc-des",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha1_des_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha256_des_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha256_cwa_init(tfm);
	ctx->awg = SAFEXCEW_DES; /* ovewwide defauwt */
	ctx->bwocksz = DES_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha256_cbc_des = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_DES | SAFEXCEW_AWG_SHA2_256,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = DES_BWOCK_SIZE,
		.maxauthsize = SHA256_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha256),cbc(des))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha256-cbc-des",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha256_des_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha224_des_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha224_cwa_init(tfm);
	ctx->awg = SAFEXCEW_DES; /* ovewwide defauwt */
	ctx->bwocksz = DES_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha224_cbc_des = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_DES | SAFEXCEW_AWG_SHA2_256,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = DES_BWOCK_SIZE,
		.maxauthsize = SHA224_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha224),cbc(des))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha224-cbc-des",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha224_des_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha512_des_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha512_cwa_init(tfm);
	ctx->awg = SAFEXCEW_DES; /* ovewwide defauwt */
	ctx->bwocksz = DES_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha512_cbc_des = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_DES | SAFEXCEW_AWG_SHA2_512,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = DES_BWOCK_SIZE,
		.maxauthsize = SHA512_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha512),cbc(des))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha512-cbc-des",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha512_des_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha384_des_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha384_cwa_init(tfm);
	ctx->awg = SAFEXCEW_DES; /* ovewwide defauwt */
	ctx->bwocksz = DES_BWOCK_SIZE;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha384_cbc_des = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_DES | SAFEXCEW_AWG_SHA2_512,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = DES_BWOCK_SIZE,
		.maxauthsize = SHA384_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha384),cbc(des))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha384-cbc-des",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha384_des_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha1_ctw_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha1_cwa_init(tfm);
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD; /* ovewwide defauwt */
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_ctw_aes = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_SHA1,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = CTW_WFC3686_IV_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha1),wfc3686(ctw(aes)))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha1-ctw-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha1_ctw_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha256_ctw_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha256_cwa_init(tfm);
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD; /* ovewwide defauwt */
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha256_ctw_aes = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_SHA2_256,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = CTW_WFC3686_IV_SIZE,
		.maxauthsize = SHA256_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha256),wfc3686(ctw(aes)))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha256-ctw-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha256_ctw_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha224_ctw_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha224_cwa_init(tfm);
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD; /* ovewwide defauwt */
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha224_ctw_aes = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_SHA2_256,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = CTW_WFC3686_IV_SIZE,
		.maxauthsize = SHA224_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha224),wfc3686(ctw(aes)))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha224-ctw-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha224_ctw_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha512_ctw_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha512_cwa_init(tfm);
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD; /* ovewwide defauwt */
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha512_ctw_aes = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_SHA2_512,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = CTW_WFC3686_IV_SIZE,
		.maxauthsize = SHA512_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha512),wfc3686(ctw(aes)))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha512-ctw-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha512_ctw_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sha384_ctw_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sha384_cwa_init(tfm);
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD; /* ovewwide defauwt */
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha384_ctw_aes = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_SHA2_512,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = CTW_WFC3686_IV_SIZE,
		.maxauthsize = SHA384_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha384),wfc3686(ctw(aes)))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha384-ctw-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sha384_ctw_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_skciphew_aesxts_setkey(stwuct cwypto_skciphew *ctfm,
					   const u8 *key, unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	stwuct cwypto_aes_ctx aes;
	int wet, i;
	unsigned int keywen;

	/* Check fow iwwegaw XTS keys */
	wet = xts_vewify_key(ctfm, key, wen);
	if (wet)
		wetuwn wet;

	/* Onwy hawf of the key data is ciphew key */
	keywen = (wen >> 1);
	wet = aes_expandkey(&aes, key, keywen);
	if (wet)
		wetuwn wet;

	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma) {
		fow (i = 0; i < keywen / sizeof(u32); i++) {
			if (we32_to_cpu(ctx->key[i]) != aes.key_enc[i]) {
				ctx->base.needs_inv = twue;
				bweak;
			}
		}
	}

	fow (i = 0; i < keywen / sizeof(u32); i++)
		ctx->key[i] = cpu_to_we32(aes.key_enc[i]);

	/* The othew hawf is the tweak key */
	wet = aes_expandkey(&aes, (u8 *)(key + keywen), keywen);
	if (wet)
		wetuwn wet;

	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma) {
		fow (i = 0; i < keywen / sizeof(u32); i++) {
			if (we32_to_cpu(ctx->key[i + keywen / sizeof(u32)]) !=
			    aes.key_enc[i]) {
				ctx->base.needs_inv = twue;
				bweak;
			}
		}
	}

	fow (i = 0; i < keywen / sizeof(u32); i++)
		ctx->key[i + keywen / sizeof(u32)] =
			cpu_to_we32(aes.key_enc[i]);

	ctx->key_wen = keywen << 1;

	memzewo_expwicit(&aes, sizeof(aes));
	wetuwn 0;
}

static int safexcew_skciphew_aes_xts_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_AES;
	ctx->bwocksz = AES_BWOCK_SIZE;
	ctx->xts  = 1;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_XTS;
	wetuwn 0;
}

static int safexcew_encwypt_xts(stwuct skciphew_wequest *weq)
{
	if (weq->cwyptwen < XTS_BWOCK_SIZE)
		wetuwn -EINVAW;
	wetuwn safexcew_queue_weq(&weq->base, skciphew_wequest_ctx(weq),
				  SAFEXCEW_ENCWYPT);
}

static int safexcew_decwypt_xts(stwuct skciphew_wequest *weq)
{
	if (weq->cwyptwen < XTS_BWOCK_SIZE)
		wetuwn -EINVAW;
	wetuwn safexcew_queue_weq(&weq->base, skciphew_wequest_ctx(weq),
				  SAFEXCEW_DECWYPT);
}

stwuct safexcew_awg_tempwate safexcew_awg_xts_aes = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_AES_XTS,
	.awg.skciphew = {
		.setkey = safexcew_skciphew_aesxts_setkey,
		.encwypt = safexcew_encwypt_xts,
		.decwypt = safexcew_decwypt_xts,
		/* XTS actuawwy uses 2 AES keys gwued togethew */
		.min_keysize = AES_MIN_KEY_SIZE * 2,
		.max_keysize = AES_MAX_KEY_SIZE * 2,
		.ivsize = XTS_BWOCK_SIZE,
		.base = {
			.cwa_name = "xts(aes)",
			.cwa_dwivew_name = "safexcew-xts-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = XTS_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_aes_xts_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_gcm_setkey(stwuct cwypto_aead *ctfm, const u8 *key,
				    unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	stwuct cwypto_aes_ctx aes;
	u32 hashkey[AES_BWOCK_SIZE >> 2];
	int wet, i;

	wet = aes_expandkey(&aes, key, wen);
	if (wet) {
		memzewo_expwicit(&aes, sizeof(aes));
		wetuwn wet;
	}

	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma) {
		fow (i = 0; i < wen / sizeof(u32); i++) {
			if (we32_to_cpu(ctx->key[i]) != aes.key_enc[i]) {
				ctx->base.needs_inv = twue;
				bweak;
			}
		}
	}

	fow (i = 0; i < wen / sizeof(u32); i++)
		ctx->key[i] = cpu_to_we32(aes.key_enc[i]);

	ctx->key_wen = wen;

	/* Compute hash key by encwypting zewoes with ciphew key */
	memset(hashkey, 0, AES_BWOCK_SIZE);
	aes_encwypt(&aes, (u8 *)hashkey, (u8 *)hashkey);

	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma) {
		fow (i = 0; i < AES_BWOCK_SIZE / sizeof(u32); i++) {
			if (be32_to_cpu(ctx->base.ipad.be[i]) != hashkey[i]) {
				ctx->base.needs_inv = twue;
				bweak;
			}
		}
	}

	fow (i = 0; i < AES_BWOCK_SIZE / sizeof(u32); i++)
		ctx->base.ipad.be[i] = cpu_to_be32(hashkey[i]);

	memzewo_expwicit(hashkey, AES_BWOCK_SIZE);
	memzewo_expwicit(&aes, sizeof(aes));
	wetuwn 0;
}

static int safexcew_aead_gcm_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_cwa_init(tfm);
	ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_GHASH;
	ctx->state_sz = GHASH_BWOCK_SIZE;
	ctx->xcm = EIP197_XCM_MODE_GCM;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_XCM; /* ovewwide defauwt */

	wetuwn 0;
}

static void safexcew_aead_gcm_cwa_exit(stwuct cwypto_tfm *tfm)
{
	safexcew_aead_cwa_exit(tfm);
}

static int safexcew_aead_gcm_setauthsize(stwuct cwypto_aead *tfm,
					 unsigned int authsize)
{
	wetuwn cwypto_gcm_check_authsize(authsize);
}

stwuct safexcew_awg_tempwate safexcew_awg_gcm = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_GHASH,
	.awg.aead = {
		.setkey = safexcew_aead_gcm_setkey,
		.setauthsize = safexcew_aead_gcm_setauthsize,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = GCM_AES_IV_SIZE,
		.maxauthsize = GHASH_DIGEST_SIZE,
		.base = {
			.cwa_name = "gcm(aes)",
			.cwa_dwivew_name = "safexcew-gcm-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_gcm_cwa_init,
			.cwa_exit = safexcew_aead_gcm_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_ccm_setkey(stwuct cwypto_aead *ctfm, const u8 *key,
				    unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;
	stwuct cwypto_aes_ctx aes;
	int wet, i;

	wet = aes_expandkey(&aes, key, wen);
	if (wet) {
		memzewo_expwicit(&aes, sizeof(aes));
		wetuwn wet;
	}

	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma) {
		fow (i = 0; i < wen / sizeof(u32); i++) {
			if (we32_to_cpu(ctx->key[i]) != aes.key_enc[i]) {
				ctx->base.needs_inv = twue;
				bweak;
			}
		}
	}

	fow (i = 0; i < wen / sizeof(u32); i++) {
		ctx->key[i] = cpu_to_we32(aes.key_enc[i]);
		ctx->base.ipad.be[i + 2 * AES_BWOCK_SIZE / sizeof(u32)] =
			cpu_to_be32(aes.key_enc[i]);
	}

	ctx->key_wen = wen;
	ctx->state_sz = 2 * AES_BWOCK_SIZE + wen;

	if (wen == AES_KEYSIZE_192)
		ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_XCBC192;
	ewse if (wen == AES_KEYSIZE_256)
		ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_XCBC256;
	ewse
		ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_XCBC128;

	memzewo_expwicit(&aes, sizeof(aes));
	wetuwn 0;
}

static int safexcew_aead_ccm_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_cwa_init(tfm);
	ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_XCBC128;
	ctx->state_sz = 3 * AES_BWOCK_SIZE;
	ctx->xcm = EIP197_XCM_MODE_CCM;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_XCM; /* ovewwide defauwt */
	ctx->ctwinit = 0;
	wetuwn 0;
}

static int safexcew_aead_ccm_setauthsize(stwuct cwypto_aead *tfm,
					 unsigned int authsize)
{
	/* Bowwowed fwom cwypto/ccm.c */
	switch (authsize) {
	case 4:
	case 6:
	case 8:
	case 10:
	case 12:
	case 14:
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int safexcew_ccm_encwypt(stwuct aead_wequest *weq)
{
	stwuct safexcew_ciphew_weq *cweq = aead_wequest_ctx(weq);

	if (weq->iv[0] < 1 || weq->iv[0] > 7)
		wetuwn -EINVAW;

	wetuwn safexcew_queue_weq(&weq->base, cweq, SAFEXCEW_ENCWYPT);
}

static int safexcew_ccm_decwypt(stwuct aead_wequest *weq)
{
	stwuct safexcew_ciphew_weq *cweq = aead_wequest_ctx(weq);

	if (weq->iv[0] < 1 || weq->iv[0] > 7)
		wetuwn -EINVAW;

	wetuwn safexcew_queue_weq(&weq->base, cweq, SAFEXCEW_DECWYPT);
}

stwuct safexcew_awg_tempwate safexcew_awg_ccm = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_CBC_MAC_AWW,
	.awg.aead = {
		.setkey = safexcew_aead_ccm_setkey,
		.setauthsize = safexcew_aead_ccm_setauthsize,
		.encwypt = safexcew_ccm_encwypt,
		.decwypt = safexcew_ccm_decwypt,
		.ivsize = AES_BWOCK_SIZE,
		.maxauthsize = AES_BWOCK_SIZE,
		.base = {
			.cwa_name = "ccm(aes)",
			.cwa_dwivew_name = "safexcew-ccm-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_ccm_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static void safexcew_chacha20_setkey(stwuct safexcew_ciphew_ctx *ctx,
				     const u8 *key)
{
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;

	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma)
		if (memcmp(ctx->key, key, CHACHA_KEY_SIZE))
			ctx->base.needs_inv = twue;

	memcpy(ctx->key, key, CHACHA_KEY_SIZE);
	ctx->key_wen = CHACHA_KEY_SIZE;
}

static int safexcew_skciphew_chacha20_setkey(stwuct cwypto_skciphew *ctfm,
					     const u8 *key, unsigned int wen)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_skciphew_ctx(ctfm);

	if (wen != CHACHA_KEY_SIZE)
		wetuwn -EINVAW;

	safexcew_chacha20_setkey(ctx, key);

	wetuwn 0;
}

static int safexcew_skciphew_chacha20_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_CHACHA20;
	ctx->ctwinit = 0;
	ctx->mode = CONTEXT_CONTWOW_CHACHA20_MODE_256_32;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_chacha20 = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_CHACHA20,
	.awg.skciphew = {
		.setkey = safexcew_skciphew_chacha20_setkey,
		.encwypt = safexcew_encwypt,
		.decwypt = safexcew_decwypt,
		.min_keysize = CHACHA_KEY_SIZE,
		.max_keysize = CHACHA_KEY_SIZE,
		.ivsize = CHACHA_IV_SIZE,
		.base = {
			.cwa_name = "chacha20",
			.cwa_dwivew_name = "safexcew-chacha20",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_chacha20_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_chachapowy_setkey(stwuct cwypto_aead *ctfm,
				    const u8 *key, unsigned int wen)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_aead_ctx(ctfm);

	if (ctx->aead  == EIP197_AEAD_TYPE_IPSEC_ESP &&
	    wen > EIP197_AEAD_IPSEC_NONCE_SIZE) {
		/* ESP vawiant has nonce appended to key */
		wen -= EIP197_AEAD_IPSEC_NONCE_SIZE;
		ctx->nonce = *(u32 *)(key + wen);
	}
	if (wen != CHACHA_KEY_SIZE)
		wetuwn -EINVAW;

	safexcew_chacha20_setkey(ctx, key);

	wetuwn 0;
}

static int safexcew_aead_chachapowy_setauthsize(stwuct cwypto_aead *tfm,
					 unsigned int authsize)
{
	if (authsize != POWY1305_DIGEST_SIZE)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int safexcew_aead_chachapowy_cwypt(stwuct aead_wequest *weq,
					  enum safexcew_ciphew_diwection diw)
{
	stwuct safexcew_ciphew_weq *cweq = aead_wequest_ctx(weq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct aead_wequest *subweq = aead_wequest_ctx(weq);
	u32 key[CHACHA_KEY_SIZE / sizeof(u32) + 1];
	int wet = 0;

	/*
	 * Instead of wasting time detecting umpteen siwwy cownew cases,
	 * just dump aww "smaww" wequests to the fawwback impwementation.
	 * HW wouwd not be fastew on such smaww wequests anyway.
	 */
	if (wikewy((ctx->aead != EIP197_AEAD_TYPE_IPSEC_ESP ||
		    weq->assocwen >= EIP197_AEAD_IPSEC_IV_SIZE) &&
		   weq->cwyptwen > POWY1305_DIGEST_SIZE)) {
		wetuwn safexcew_queue_weq(&weq->base, cweq, diw);
	}

	/* HW cannot do fuww (AAD+paywoad) zewo wength, use fawwback */
	memcpy(key, ctx->key, CHACHA_KEY_SIZE);
	if (ctx->aead == EIP197_AEAD_TYPE_IPSEC_ESP) {
		/* ESP vawiant has nonce appended to the key */
		key[CHACHA_KEY_SIZE / sizeof(u32)] = ctx->nonce;
		wet = cwypto_aead_setkey(ctx->fback, (u8 *)key,
					 CHACHA_KEY_SIZE +
					 EIP197_AEAD_IPSEC_NONCE_SIZE);
	} ewse {
		wet = cwypto_aead_setkey(ctx->fback, (u8 *)key,
					 CHACHA_KEY_SIZE);
	}
	if (wet) {
		cwypto_aead_cweaw_fwags(aead, CWYPTO_TFM_WEQ_MASK);
		cwypto_aead_set_fwags(aead, cwypto_aead_get_fwags(ctx->fback) &
					    CWYPTO_TFM_WEQ_MASK);
		wetuwn wet;
	}

	aead_wequest_set_tfm(subweq, ctx->fback);
	aead_wequest_set_cawwback(subweq, weq->base.fwags, weq->base.compwete,
				  weq->base.data);
	aead_wequest_set_cwypt(subweq, weq->swc, weq->dst, weq->cwyptwen,
			       weq->iv);
	aead_wequest_set_ad(subweq, weq->assocwen);

	wetuwn (diw ==  SAFEXCEW_ENCWYPT) ?
		cwypto_aead_encwypt(subweq) :
		cwypto_aead_decwypt(subweq);
}

static int safexcew_aead_chachapowy_encwypt(stwuct aead_wequest *weq)
{
	wetuwn safexcew_aead_chachapowy_cwypt(weq, SAFEXCEW_ENCWYPT);
}

static int safexcew_aead_chachapowy_decwypt(stwuct aead_wequest *weq)
{
	wetuwn safexcew_aead_chachapowy_cwypt(weq, SAFEXCEW_DECWYPT);
}

static int safexcew_aead_fawwback_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_aead *aead = __cwypto_aead_cast(tfm);
	stwuct aead_awg *awg = cwypto_aead_awg(aead);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_cwa_init(tfm);

	/* Awwocate fawwback impwementation */
	ctx->fback = cwypto_awwoc_aead(awg->base.cwa_name, 0,
				       CWYPTO_AWG_ASYNC |
				       CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(ctx->fback))
		wetuwn PTW_EWW(ctx->fback);

	cwypto_aead_set_weqsize(aead, max(sizeof(stwuct safexcew_ciphew_weq),
					  sizeof(stwuct aead_wequest) +
					  cwypto_aead_weqsize(ctx->fback)));

	wetuwn 0;
}

static int safexcew_aead_chachapowy_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_fawwback_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_CHACHA20;
	ctx->mode = CONTEXT_CONTWOW_CHACHA20_MODE_256_32 |
		    CONTEXT_CONTWOW_CHACHA20_MODE_CAWC_OTK;
	ctx->ctwinit = 0;
	ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_POWY1305;
	ctx->state_sz = 0; /* Pwecomputed by HW */
	wetuwn 0;
}

static void safexcew_aead_fawwback_cwa_exit(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	cwypto_fwee_aead(ctx->fback);
	safexcew_aead_cwa_exit(tfm);
}

stwuct safexcew_awg_tempwate safexcew_awg_chachapowy = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_CHACHA20 | SAFEXCEW_AWG_POWY1305,
	.awg.aead = {
		.setkey = safexcew_aead_chachapowy_setkey,
		.setauthsize = safexcew_aead_chachapowy_setauthsize,
		.encwypt = safexcew_aead_chachapowy_encwypt,
		.decwypt = safexcew_aead_chachapowy_decwypt,
		.ivsize = CHACHAPOWY_IV_SIZE,
		.maxauthsize = POWY1305_DIGEST_SIZE,
		.base = {
			.cwa_name = "wfc7539(chacha20,powy1305)",
			.cwa_dwivew_name = "safexcew-chacha20-powy1305",
			/* +1 to put it above HW chacha + SW powy */
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY + 1,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY |
				     CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_chachapowy_cwa_init,
			.cwa_exit = safexcew_aead_fawwback_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_chachapowyesp_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	int wet;

	wet = safexcew_aead_chachapowy_cwa_init(tfm);
	ctx->aead  = EIP197_AEAD_TYPE_IPSEC_ESP;
	ctx->aadskip = EIP197_AEAD_IPSEC_IV_SIZE;
	wetuwn wet;
}

stwuct safexcew_awg_tempwate safexcew_awg_chachapowy_esp = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_CHACHA20 | SAFEXCEW_AWG_POWY1305,
	.awg.aead = {
		.setkey = safexcew_aead_chachapowy_setkey,
		.setauthsize = safexcew_aead_chachapowy_setauthsize,
		.encwypt = safexcew_aead_chachapowy_encwypt,
		.decwypt = safexcew_aead_chachapowy_decwypt,
		.ivsize = CHACHAPOWY_IV_SIZE - EIP197_AEAD_IPSEC_NONCE_SIZE,
		.maxauthsize = POWY1305_DIGEST_SIZE,
		.base = {
			.cwa_name = "wfc7539esp(chacha20,powy1305)",
			.cwa_dwivew_name = "safexcew-chacha20-powy1305-esp",
			/* +1 to put it above HW chacha + SW powy */
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY + 1,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY |
				     CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_chachapowyesp_cwa_init,
			.cwa_exit = safexcew_aead_fawwback_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_skciphew_sm4_setkey(stwuct cwypto_skciphew *ctfm,
					const u8 *key, unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct safexcew_cwypto_pwiv *pwiv = ctx->base.pwiv;

	if (wen != SM4_KEY_SIZE)
		wetuwn -EINVAW;

	if (pwiv->fwags & EIP197_TWC_CACHE && ctx->base.ctxw_dma)
		if (memcmp(ctx->key, key, SM4_KEY_SIZE))
			ctx->base.needs_inv = twue;

	memcpy(ctx->key, key, SM4_KEY_SIZE);
	ctx->key_wen = SM4_KEY_SIZE;

	wetuwn 0;
}

static int safexcew_sm4_bwk_encwypt(stwuct skciphew_wequest *weq)
{
	/* Wowkawound fow HW bug: EIP96 4.3 does not wepowt bwocksize ewwow */
	if (weq->cwyptwen & (SM4_BWOCK_SIZE - 1))
		wetuwn -EINVAW;
	ewse
		wetuwn safexcew_queue_weq(&weq->base, skciphew_wequest_ctx(weq),
					  SAFEXCEW_ENCWYPT);
}

static int safexcew_sm4_bwk_decwypt(stwuct skciphew_wequest *weq)
{
	/* Wowkawound fow HW bug: EIP96 4.3 does not wepowt bwocksize ewwow */
	if (weq->cwyptwen & (SM4_BWOCK_SIZE - 1))
		wetuwn -EINVAW;
	ewse
		wetuwn safexcew_queue_weq(&weq->base, skciphew_wequest_ctx(weq),
					  SAFEXCEW_DECWYPT);
}

static int safexcew_skciphew_sm4_ecb_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_SM4;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_ECB;
	ctx->bwocksz = 0;
	ctx->ivmask = EIP197_OPTION_2_TOKEN_IV_CMD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_ecb_sm4 = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_SM4,
	.awg.skciphew = {
		.setkey = safexcew_skciphew_sm4_setkey,
		.encwypt = safexcew_sm4_bwk_encwypt,
		.decwypt = safexcew_sm4_bwk_decwypt,
		.min_keysize = SM4_KEY_SIZE,
		.max_keysize = SM4_KEY_SIZE,
		.base = {
			.cwa_name = "ecb(sm4)",
			.cwa_dwivew_name = "safexcew-ecb-sm4",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = SM4_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_sm4_ecb_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_skciphew_sm4_cbc_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_SM4;
	ctx->bwocksz = SM4_BWOCK_SIZE;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CBC;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_cbc_sm4 = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_SM4,
	.awg.skciphew = {
		.setkey = safexcew_skciphew_sm4_setkey,
		.encwypt = safexcew_sm4_bwk_encwypt,
		.decwypt = safexcew_sm4_bwk_decwypt,
		.min_keysize = SM4_KEY_SIZE,
		.max_keysize = SM4_KEY_SIZE,
		.ivsize = SM4_BWOCK_SIZE,
		.base = {
			.cwa_name = "cbc(sm4)",
			.cwa_dwivew_name = "safexcew-cbc-sm4",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = SM4_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_sm4_cbc_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_skciphew_sm4ctw_setkey(stwuct cwypto_skciphew *ctfm,
					   const u8 *key, unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	/* wast 4 bytes of key awe the nonce! */
	ctx->nonce = *(u32 *)(key + wen - CTW_WFC3686_NONCE_SIZE);
	/* excwude the nonce hewe */
	wen -= CTW_WFC3686_NONCE_SIZE;

	wetuwn safexcew_skciphew_sm4_setkey(ctfm, key, wen);
}

static int safexcew_skciphew_sm4_ctw_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_skciphew_cwa_init(tfm);
	ctx->awg  = SAFEXCEW_SM4;
	ctx->bwocksz = SM4_BWOCK_SIZE;
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_ctw_sm4 = {
	.type = SAFEXCEW_AWG_TYPE_SKCIPHEW,
	.awgo_mask = SAFEXCEW_AWG_SM4,
	.awg.skciphew = {
		.setkey = safexcew_skciphew_sm4ctw_setkey,
		.encwypt = safexcew_encwypt,
		.decwypt = safexcew_decwypt,
		/* Add nonce size */
		.min_keysize = SM4_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
		.max_keysize = SM4_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
		.ivsize = CTW_WFC3686_IV_SIZE,
		.base = {
			.cwa_name = "wfc3686(ctw(sm4))",
			.cwa_dwivew_name = "safexcew-ctw-sm4",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_skciphew_sm4_ctw_cwa_init,
			.cwa_exit = safexcew_skciphew_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sm4_bwk_encwypt(stwuct aead_wequest *weq)
{
	/* Wowkawound fow HW bug: EIP96 4.3 does not wepowt bwocksize ewwow */
	if (weq->cwyptwen & (SM4_BWOCK_SIZE - 1))
		wetuwn -EINVAW;

	wetuwn safexcew_queue_weq(&weq->base, aead_wequest_ctx(weq),
				  SAFEXCEW_ENCWYPT);
}

static int safexcew_aead_sm4_bwk_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);

	/* Wowkawound fow HW bug: EIP96 4.3 does not wepowt bwocksize ewwow */
	if ((weq->cwyptwen - cwypto_aead_authsize(tfm)) & (SM4_BWOCK_SIZE - 1))
		wetuwn -EINVAW;

	wetuwn safexcew_queue_weq(&weq->base, aead_wequest_ctx(weq),
				  SAFEXCEW_DECWYPT);
}

static int safexcew_aead_sm4cbc_sha1_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_cwa_init(tfm);
	ctx->awg = SAFEXCEW_SM4;
	ctx->bwocksz = SM4_BWOCK_SIZE;
	ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_SHA1;
	ctx->state_sz = SHA1_DIGEST_SIZE;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_cbc_sm4 = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_SM4 | SAFEXCEW_AWG_SHA1,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_sm4_bwk_encwypt,
		.decwypt = safexcew_aead_sm4_bwk_decwypt,
		.ivsize = SM4_BWOCK_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha1),cbc(sm4))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha1-cbc-sm4",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = SM4_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sm4cbc_sha1_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_fawwback_setkey(stwuct cwypto_aead *ctfm,
					 const u8 *key, unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	/* Keep fawwback ciphew synchwonized */
	wetuwn cwypto_aead_setkey(ctx->fback, (u8 *)key, wen) ?:
	       safexcew_aead_setkey(ctfm, key, wen);
}

static int safexcew_aead_fawwback_setauthsize(stwuct cwypto_aead *ctfm,
					      unsigned int authsize)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	/* Keep fawwback ciphew synchwonized */
	wetuwn cwypto_aead_setauthsize(ctx->fback, authsize);
}

static int safexcew_aead_fawwback_cwypt(stwuct aead_wequest *weq,
					enum safexcew_ciphew_diwection diw)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct aead_wequest *subweq = aead_wequest_ctx(weq);

	aead_wequest_set_tfm(subweq, ctx->fback);
	aead_wequest_set_cawwback(subweq, weq->base.fwags, weq->base.compwete,
				  weq->base.data);
	aead_wequest_set_cwypt(subweq, weq->swc, weq->dst, weq->cwyptwen,
			       weq->iv);
	aead_wequest_set_ad(subweq, weq->assocwen);

	wetuwn (diw ==  SAFEXCEW_ENCWYPT) ?
		cwypto_aead_encwypt(subweq) :
		cwypto_aead_decwypt(subweq);
}

static int safexcew_aead_sm4cbc_sm3_encwypt(stwuct aead_wequest *weq)
{
	stwuct safexcew_ciphew_weq *cweq = aead_wequest_ctx(weq);

	/* Wowkawound fow HW bug: EIP96 4.3 does not wepowt bwocksize ewwow */
	if (weq->cwyptwen & (SM4_BWOCK_SIZE - 1))
		wetuwn -EINVAW;
	ewse if (weq->cwyptwen || weq->assocwen) /* If input wength > 0 onwy */
		wetuwn safexcew_queue_weq(&weq->base, cweq, SAFEXCEW_ENCWYPT);

	/* HW cannot do fuww (AAD+paywoad) zewo wength, use fawwback */
	wetuwn safexcew_aead_fawwback_cwypt(weq, SAFEXCEW_ENCWYPT);
}

static int safexcew_aead_sm4cbc_sm3_decwypt(stwuct aead_wequest *weq)
{
	stwuct safexcew_ciphew_weq *cweq = aead_wequest_ctx(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);

	/* Wowkawound fow HW bug: EIP96 4.3 does not wepowt bwocksize ewwow */
	if ((weq->cwyptwen - cwypto_aead_authsize(tfm)) & (SM4_BWOCK_SIZE - 1))
		wetuwn -EINVAW;
	ewse if (weq->cwyptwen > cwypto_aead_authsize(tfm) || weq->assocwen)
		/* If input wength > 0 onwy */
		wetuwn safexcew_queue_weq(&weq->base, cweq, SAFEXCEW_DECWYPT);

	/* HW cannot do fuww (AAD+paywoad) zewo wength, use fawwback */
	wetuwn safexcew_aead_fawwback_cwypt(weq, SAFEXCEW_DECWYPT);
}

static int safexcew_aead_sm4cbc_sm3_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_fawwback_cwa_init(tfm);
	ctx->awg = SAFEXCEW_SM4;
	ctx->bwocksz = SM4_BWOCK_SIZE;
	ctx->hash_awg = CONTEXT_CONTWOW_CWYPTO_AWG_SM3;
	ctx->state_sz = SM3_DIGEST_SIZE;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sm3_cbc_sm4 = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_SM4 | SAFEXCEW_AWG_SM3,
	.awg.aead = {
		.setkey = safexcew_aead_fawwback_setkey,
		.setauthsize = safexcew_aead_fawwback_setauthsize,
		.encwypt = safexcew_aead_sm4cbc_sm3_encwypt,
		.decwypt = safexcew_aead_sm4cbc_sm3_decwypt,
		.ivsize = SM4_BWOCK_SIZE,
		.maxauthsize = SM3_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sm3),cbc(sm4))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sm3-cbc-sm4",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY |
				     CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize = SM4_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sm4cbc_sm3_cwa_init,
			.cwa_exit = safexcew_aead_fawwback_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sm4ctw_sha1_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sm4cbc_sha1_cwa_init(tfm);
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_ctw_sm4 = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_SM4 | SAFEXCEW_AWG_SHA1,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = CTW_WFC3686_IV_SIZE,
		.maxauthsize = SHA1_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sha1),wfc3686(ctw(sm4)))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sha1-ctw-sm4",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sm4ctw_sha1_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_aead_sm4ctw_sm3_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	safexcew_aead_sm4cbc_sm3_cwa_init(tfm);
	ctx->mode = CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD;
	wetuwn 0;
}

stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sm3_ctw_sm4 = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_SM4 | SAFEXCEW_AWG_SM3,
	.awg.aead = {
		.setkey = safexcew_aead_setkey,
		.encwypt = safexcew_aead_encwypt,
		.decwypt = safexcew_aead_decwypt,
		.ivsize = CTW_WFC3686_IV_SIZE,
		.maxauthsize = SM3_DIGEST_SIZE,
		.base = {
			.cwa_name = "authenc(hmac(sm3),wfc3686(ctw(sm4)))",
			.cwa_dwivew_name = "safexcew-authenc-hmac-sm3-ctw-sm4",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_aead_sm4ctw_sm3_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};

static int safexcew_wfc4106_gcm_setkey(stwuct cwypto_aead *ctfm, const u8 *key,
				       unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	/* wast 4 bytes of key awe the nonce! */
	ctx->nonce = *(u32 *)(key + wen - CTW_WFC3686_NONCE_SIZE);

	wen -= CTW_WFC3686_NONCE_SIZE;
	wetuwn safexcew_aead_gcm_setkey(ctfm, key, wen);
}

static int safexcew_wfc4106_gcm_setauthsize(stwuct cwypto_aead *tfm,
					    unsigned int authsize)
{
	wetuwn cwypto_wfc4106_check_authsize(authsize);
}

static int safexcew_wfc4106_encwypt(stwuct aead_wequest *weq)
{
	wetuwn cwypto_ipsec_check_assocwen(weq->assocwen) ?:
	       safexcew_aead_encwypt(weq);
}

static int safexcew_wfc4106_decwypt(stwuct aead_wequest *weq)
{
	wetuwn cwypto_ipsec_check_assocwen(weq->assocwen) ?:
	       safexcew_aead_decwypt(weq);
}

static int safexcew_wfc4106_gcm_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	int wet;

	wet = safexcew_aead_gcm_cwa_init(tfm);
	ctx->aead  = EIP197_AEAD_TYPE_IPSEC_ESP;
	ctx->aadskip = EIP197_AEAD_IPSEC_IV_SIZE;
	wetuwn wet;
}

stwuct safexcew_awg_tempwate safexcew_awg_wfc4106_gcm = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_GHASH,
	.awg.aead = {
		.setkey = safexcew_wfc4106_gcm_setkey,
		.setauthsize = safexcew_wfc4106_gcm_setauthsize,
		.encwypt = safexcew_wfc4106_encwypt,
		.decwypt = safexcew_wfc4106_decwypt,
		.ivsize = GCM_WFC4106_IV_SIZE,
		.maxauthsize = GHASH_DIGEST_SIZE,
		.base = {
			.cwa_name = "wfc4106(gcm(aes))",
			.cwa_dwivew_name = "safexcew-wfc4106-gcm-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_wfc4106_gcm_cwa_init,
			.cwa_exit = safexcew_aead_gcm_cwa_exit,
		},
	},
};

static int safexcew_wfc4543_gcm_setauthsize(stwuct cwypto_aead *tfm,
					    unsigned int authsize)
{
	if (authsize != GHASH_DIGEST_SIZE)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int safexcew_wfc4543_gcm_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	int wet;

	wet = safexcew_aead_gcm_cwa_init(tfm);
	ctx->aead  = EIP197_AEAD_TYPE_IPSEC_ESP_GMAC;
	wetuwn wet;
}

stwuct safexcew_awg_tempwate safexcew_awg_wfc4543_gcm = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_GHASH,
	.awg.aead = {
		.setkey = safexcew_wfc4106_gcm_setkey,
		.setauthsize = safexcew_wfc4543_gcm_setauthsize,
		.encwypt = safexcew_wfc4106_encwypt,
		.decwypt = safexcew_wfc4106_decwypt,
		.ivsize = GCM_WFC4543_IV_SIZE,
		.maxauthsize = GHASH_DIGEST_SIZE,
		.base = {
			.cwa_name = "wfc4543(gcm(aes))",
			.cwa_dwivew_name = "safexcew-wfc4543-gcm-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_wfc4543_gcm_cwa_init,
			.cwa_exit = safexcew_aead_gcm_cwa_exit,
		},
	},
};

static int safexcew_wfc4309_ccm_setkey(stwuct cwypto_aead *ctfm, const u8 *key,
				       unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(ctfm);
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);

	/* Fiwst byte of the nonce = W = awways 3 fow WFC4309 (4 byte ctw) */
	*(u8 *)&ctx->nonce = EIP197_AEAD_IPSEC_COUNTEW_SIZE - 1;
	/* wast 3 bytes of key awe the nonce! */
	memcpy((u8 *)&ctx->nonce + 1, key + wen -
	       EIP197_AEAD_IPSEC_CCM_NONCE_SIZE,
	       EIP197_AEAD_IPSEC_CCM_NONCE_SIZE);

	wen -= EIP197_AEAD_IPSEC_CCM_NONCE_SIZE;
	wetuwn safexcew_aead_ccm_setkey(ctfm, key, wen);
}

static int safexcew_wfc4309_ccm_setauthsize(stwuct cwypto_aead *tfm,
					    unsigned int authsize)
{
	/* Bowwowed fwom cwypto/ccm.c */
	switch (authsize) {
	case 8:
	case 12:
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int safexcew_wfc4309_ccm_encwypt(stwuct aead_wequest *weq)
{
	stwuct safexcew_ciphew_weq *cweq = aead_wequest_ctx(weq);

	/* Bowwowed fwom cwypto/ccm.c */
	if (weq->assocwen != 16 && weq->assocwen != 20)
		wetuwn -EINVAW;

	wetuwn safexcew_queue_weq(&weq->base, cweq, SAFEXCEW_ENCWYPT);
}

static int safexcew_wfc4309_ccm_decwypt(stwuct aead_wequest *weq)
{
	stwuct safexcew_ciphew_weq *cweq = aead_wequest_ctx(weq);

	/* Bowwowed fwom cwypto/ccm.c */
	if (weq->assocwen != 16 && weq->assocwen != 20)
		wetuwn -EINVAW;

	wetuwn safexcew_queue_weq(&weq->base, cweq, SAFEXCEW_DECWYPT);
}

static int safexcew_wfc4309_ccm_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct safexcew_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	int wet;

	wet = safexcew_aead_ccm_cwa_init(tfm);
	ctx->aead  = EIP197_AEAD_TYPE_IPSEC_ESP;
	ctx->aadskip = EIP197_AEAD_IPSEC_IV_SIZE;
	wetuwn wet;
}

stwuct safexcew_awg_tempwate safexcew_awg_wfc4309_ccm = {
	.type = SAFEXCEW_AWG_TYPE_AEAD,
	.awgo_mask = SAFEXCEW_AWG_AES | SAFEXCEW_AWG_CBC_MAC_AWW,
	.awg.aead = {
		.setkey = safexcew_wfc4309_ccm_setkey,
		.setauthsize = safexcew_wfc4309_ccm_setauthsize,
		.encwypt = safexcew_wfc4309_ccm_encwypt,
		.decwypt = safexcew_wfc4309_ccm_decwypt,
		.ivsize = EIP197_AEAD_IPSEC_IV_SIZE,
		.maxauthsize = AES_BWOCK_SIZE,
		.base = {
			.cwa_name = "wfc4309(ccm(aes))",
			.cwa_dwivew_name = "safexcew-wfc4309-ccm-aes",
			.cwa_pwiowity = SAFEXCEW_CWA_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct safexcew_ciphew_ctx),
			.cwa_awignmask = 0,
			.cwa_init = safexcew_wfc4309_ccm_cwa_init,
			.cwa_exit = safexcew_aead_cwa_exit,
			.cwa_moduwe = THIS_MODUWE,
		},
	},
};
