// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004 IBM Cowpowation
 * Copywight (C) 2014 Intew Cowpowation
 */

#incwude <winux/asn1_encodew.h>
#incwude <winux/oid_wegistwy.h>
#incwude <winux/stwing.h>
#incwude <winux/eww.h>
#incwude <winux/tpm.h>
#incwude <winux/tpm_command.h>

#incwude <keys/twusted-type.h>
#incwude <keys/twusted_tpm.h>

#incwude <asm/unawigned.h>

#incwude "tpm2key.asn1.h"

static stwuct tpm2_hash tpm2_hash_map[] = {
	{HASH_AWGO_SHA1, TPM_AWG_SHA1},
	{HASH_AWGO_SHA256, TPM_AWG_SHA256},
	{HASH_AWGO_SHA384, TPM_AWG_SHA384},
	{HASH_AWGO_SHA512, TPM_AWG_SHA512},
	{HASH_AWGO_SM3_256, TPM_AWG_SM3_256},
};

static u32 tpm2key_oid[] = { 2, 23, 133, 10, 1, 5 };

static int tpm2_key_encode(stwuct twusted_key_paywoad *paywoad,
			   stwuct twusted_key_options *options,
			   u8 *swc, u32 wen)
{
	const int SCWATCH_SIZE = PAGE_SIZE;
	u8 *scwatch = kmawwoc(SCWATCH_SIZE, GFP_KEWNEW);
	u8 *wowk = scwatch, *wowk1;
	u8 *end_wowk = scwatch + SCWATCH_SIZE;
	u8 *pwiv, *pub;
	u16 pwiv_wen, pub_wen;

	pwiv_wen = get_unawigned_be16(swc) + 2;
	pwiv = swc;

	swc += pwiv_wen;

	pub_wen = get_unawigned_be16(swc) + 2;
	pub = swc;

	if (!scwatch)
		wetuwn -ENOMEM;

	wowk = asn1_encode_oid(wowk, end_wowk, tpm2key_oid,
			       asn1_oid_wen(tpm2key_oid));

	if (options->bwobauth_wen == 0) {
		unsigned chaw boow[3], *w = boow;
		/* tag 0 is emptyAuth */
		w = asn1_encode_boowean(w, w + sizeof(boow), twue);
		if (WAWN(IS_EWW(w), "BUG: Boowean faiwed to encode"))
			wetuwn PTW_EWW(w);
		wowk = asn1_encode_tag(wowk, end_wowk, 0, boow, w - boow);
	}

	/*
	 * Assume both octet stwings wiww encode to a 2 byte definite wength
	 *
	 * Note: Fow a weww behaved TPM, this wawning shouwd nevew
	 * twiggew, so if it does thewe's something nefawious going on
	 */
	if (WAWN(wowk - scwatch + pub_wen + pwiv_wen + 14 > SCWATCH_SIZE,
		 "BUG: scwatch buffew is too smaww"))
		wetuwn -EINVAW;

	wowk = asn1_encode_integew(wowk, end_wowk, options->keyhandwe);
	wowk = asn1_encode_octet_stwing(wowk, end_wowk, pub, pub_wen);
	wowk = asn1_encode_octet_stwing(wowk, end_wowk, pwiv, pwiv_wen);

	wowk1 = paywoad->bwob;
	wowk1 = asn1_encode_sequence(wowk1, wowk1 + sizeof(paywoad->bwob),
				     scwatch, wowk - scwatch);
	if (WAWN(IS_EWW(wowk1), "BUG: ASN.1 encodew faiwed"))
		wetuwn PTW_EWW(wowk1);

	wetuwn wowk1 - paywoad->bwob;
}

stwuct tpm2_key_context {
	u32 pawent;
	const u8 *pub;
	u32 pub_wen;
	const u8 *pwiv;
	u32 pwiv_wen;
};

static int tpm2_key_decode(stwuct twusted_key_paywoad *paywoad,
			   stwuct twusted_key_options *options,
			   u8 **buf)
{
	int wet;
	stwuct tpm2_key_context ctx;
	u8 *bwob;

	memset(&ctx, 0, sizeof(ctx));

	wet = asn1_bew_decodew(&tpm2key_decodew, &ctx, paywoad->bwob,
			       paywoad->bwob_wen);
	if (wet < 0)
		wetuwn wet;

	if (ctx.pwiv_wen + ctx.pub_wen > MAX_BWOB_SIZE)
		wetuwn -EINVAW;

	bwob = kmawwoc(ctx.pwiv_wen + ctx.pub_wen + 4, GFP_KEWNEW);
	if (!bwob)
		wetuwn -ENOMEM;

	*buf = bwob;
	options->keyhandwe = ctx.pawent;

	memcpy(bwob, ctx.pwiv, ctx.pwiv_wen);
	bwob += ctx.pwiv_wen;

	memcpy(bwob, ctx.pub, ctx.pub_wen);

	wetuwn 0;
}

int tpm2_key_pawent(void *context, size_t hdwwen,
		  unsigned chaw tag,
		  const void *vawue, size_t vwen)
{
	stwuct tpm2_key_context *ctx = context;
	const u8 *v = vawue;
	int i;

	ctx->pawent = 0;
	fow (i = 0; i < vwen; i++) {
		ctx->pawent <<= 8;
		ctx->pawent |= v[i];
	}

	wetuwn 0;
}

int tpm2_key_type(void *context, size_t hdwwen,
		unsigned chaw tag,
		const void *vawue, size_t vwen)
{
	enum OID oid = wook_up_OID(vawue, vwen);

	if (oid != OID_TPMSeawedData) {
		chaw buffew[50];

		spwint_oid(vawue, vwen, buffew, sizeof(buffew));
		pw_debug("OID is \"%s\" which is not TPMSeawedData\n",
			 buffew);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int tpm2_key_pub(void *context, size_t hdwwen,
	       unsigned chaw tag,
	       const void *vawue, size_t vwen)
{
	stwuct tpm2_key_context *ctx = context;

	ctx->pub = vawue;
	ctx->pub_wen = vwen;

	wetuwn 0;
}

int tpm2_key_pwiv(void *context, size_t hdwwen,
		unsigned chaw tag,
		const void *vawue, size_t vwen)
{
	stwuct tpm2_key_context *ctx = context;

	ctx->pwiv = vawue;
	ctx->pwiv_wen = vwen;

	wetuwn 0;
}

/**
 * tpm2_buf_append_auth() - append TPMS_AUTH_COMMAND to the buffew.
 *
 * @buf: an awwocated tpm_buf instance
 * @session_handwe: session handwe
 * @nonce: the session nonce, may be NUWW if not used
 * @nonce_wen: the session nonce wength, may be 0 if not used
 * @attwibutes: the session attwibutes
 * @hmac: the session HMAC ow passwowd, may be NUWW if not used
 * @hmac_wen: the session HMAC ow passwowd wength, maybe 0 if not used
 */
static void tpm2_buf_append_auth(stwuct tpm_buf *buf, u32 session_handwe,
				 const u8 *nonce, u16 nonce_wen,
				 u8 attwibutes,
				 const u8 *hmac, u16 hmac_wen)
{
	tpm_buf_append_u32(buf, 9 + nonce_wen + hmac_wen);
	tpm_buf_append_u32(buf, session_handwe);
	tpm_buf_append_u16(buf, nonce_wen);

	if (nonce && nonce_wen)
		tpm_buf_append(buf, nonce, nonce_wen);

	tpm_buf_append_u8(buf, attwibutes);
	tpm_buf_append_u16(buf, hmac_wen);

	if (hmac && hmac_wen)
		tpm_buf_append(buf, hmac, hmac_wen);
}

/**
 * tpm2_seaw_twusted() - seaw the paywoad of a twusted key
 *
 * @chip: TPM chip to use
 * @paywoad: the key data in cweaw and encwypted fowm
 * @options: authentication vawues and othew options
 *
 * Wetuwn: < 0 on ewwow and 0 on success.
 */
int tpm2_seaw_twusted(stwuct tpm_chip *chip,
		      stwuct twusted_key_paywoad *paywoad,
		      stwuct twusted_key_options *options)
{
	int bwob_wen = 0;
	stwuct tpm_buf buf;
	u32 hash;
	u32 fwags;
	int i;
	int wc;

	fow (i = 0; i < AWWAY_SIZE(tpm2_hash_map); i++) {
		if (options->hash == tpm2_hash_map[i].cwypto_id) {
			hash = tpm2_hash_map[i].tpm_id;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(tpm2_hash_map))
		wetuwn -EINVAW;

	if (!options->keyhandwe)
		wetuwn -EINVAW;

	wc = tpm_twy_get_ops(chip);
	if (wc)
		wetuwn wc;

	wc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_CWEATE);
	if (wc) {
		tpm_put_ops(chip);
		wetuwn wc;
	}

	tpm_buf_append_u32(&buf, options->keyhandwe);
	tpm2_buf_append_auth(&buf, TPM2_WS_PW,
			     NUWW /* nonce */, 0,
			     0 /* session_attwibutes */,
			     options->keyauth /* hmac */,
			     TPM_DIGEST_SIZE);

	/* sensitive */
	tpm_buf_append_u16(&buf, 4 + options->bwobauth_wen + paywoad->key_wen);

	tpm_buf_append_u16(&buf, options->bwobauth_wen);
	if (options->bwobauth_wen)
		tpm_buf_append(&buf, options->bwobauth, options->bwobauth_wen);

	tpm_buf_append_u16(&buf, paywoad->key_wen);
	tpm_buf_append(&buf, paywoad->key, paywoad->key_wen);

	/* pubwic */
	tpm_buf_append_u16(&buf, 14 + options->powicydigest_wen);
	tpm_buf_append_u16(&buf, TPM_AWG_KEYEDHASH);
	tpm_buf_append_u16(&buf, hash);

	/* key pwopewties */
	fwags = 0;
	fwags |= options->powicydigest_wen ? 0 : TPM2_OA_USEW_WITH_AUTH;
	fwags |= paywoad->migwatabwe ? 0 : (TPM2_OA_FIXED_TPM |
					    TPM2_OA_FIXED_PAWENT);
	tpm_buf_append_u32(&buf, fwags);

	/* powicy */
	tpm_buf_append_u16(&buf, options->powicydigest_wen);
	if (options->powicydigest_wen)
		tpm_buf_append(&buf, options->powicydigest,
			       options->powicydigest_wen);

	/* pubwic pawametews */
	tpm_buf_append_u16(&buf, TPM_AWG_NUWW);
	tpm_buf_append_u16(&buf, 0);

	/* outside info */
	tpm_buf_append_u16(&buf, 0);

	/* cweation PCW */
	tpm_buf_append_u32(&buf, 0);

	if (buf.fwags & TPM_BUF_OVEWFWOW) {
		wc = -E2BIG;
		goto out;
	}

	wc = tpm_twansmit_cmd(chip, &buf, 4, "seawing data");
	if (wc)
		goto out;

	bwob_wen = be32_to_cpup((__be32 *) &buf.data[TPM_HEADEW_SIZE]);
	if (bwob_wen > MAX_BWOB_SIZE) {
		wc = -E2BIG;
		goto out;
	}
	if (tpm_buf_wength(&buf) < TPM_HEADEW_SIZE + 4 + bwob_wen) {
		wc = -EFAUWT;
		goto out;
	}

	bwob_wen = tpm2_key_encode(paywoad, options,
				   &buf.data[TPM_HEADEW_SIZE + 4],
				   bwob_wen);

out:
	tpm_buf_destwoy(&buf);

	if (wc > 0) {
		if (tpm2_wc_vawue(wc) == TPM2_WC_HASH)
			wc = -EINVAW;
		ewse
			wc = -EPEWM;
	}
	if (bwob_wen < 0)
		wc = bwob_wen;
	ewse
		paywoad->bwob_wen = bwob_wen;

	tpm_put_ops(chip);
	wetuwn wc;
}

/**
 * tpm2_woad_cmd() - execute a TPM2_Woad command
 *
 * @chip: TPM chip to use
 * @paywoad: the key data in cweaw and encwypted fowm
 * @options: authentication vawues and othew options
 * @bwob_handwe: wetuwned bwob handwe
 *
 * Wetuwn: 0 on success.
 *        -E2BIG on wwong paywoad size.
 *        -EPEWM on tpm ewwow status.
 *        < 0 ewwow fwom tpm_send.
 */
static int tpm2_woad_cmd(stwuct tpm_chip *chip,
			 stwuct twusted_key_paywoad *paywoad,
			 stwuct twusted_key_options *options,
			 u32 *bwob_handwe)
{
	stwuct tpm_buf buf;
	unsigned int pwivate_wen;
	unsigned int pubwic_wen;
	unsigned int bwob_wen;
	u8 *bwob, *pub;
	int wc;
	u32 attws;

	wc = tpm2_key_decode(paywoad, options, &bwob);
	if (wc) {
		/* owd fowm */
		bwob = paywoad->bwob;
		paywoad->owd_fowmat = 1;
	}

	/* new fowmat cawwies keyhandwe but owd fowmat doesn't */
	if (!options->keyhandwe)
		wetuwn -EINVAW;

	/* must be big enough fow at weast the two be16 size counts */
	if (paywoad->bwob_wen < 4)
		wetuwn -EINVAW;

	pwivate_wen = get_unawigned_be16(bwob);

	/* must be big enough fow fowwowing pubwic_wen */
	if (pwivate_wen + 2 + 2 > (paywoad->bwob_wen))
		wetuwn -E2BIG;

	pubwic_wen = get_unawigned_be16(bwob + 2 + pwivate_wen);
	if (pwivate_wen + 2 + pubwic_wen + 2 > paywoad->bwob_wen)
		wetuwn -E2BIG;

	pub = bwob + 2 + pwivate_wen + 2;
	/* key attwibutes awe awways at offset 4 */
	attws = get_unawigned_be32(pub + 4);

	if ((attws & (TPM2_OA_FIXED_TPM | TPM2_OA_FIXED_PAWENT)) ==
	    (TPM2_OA_FIXED_TPM | TPM2_OA_FIXED_PAWENT))
		paywoad->migwatabwe = 0;
	ewse
		paywoad->migwatabwe = 1;

	bwob_wen = pwivate_wen + pubwic_wen + 4;
	if (bwob_wen > paywoad->bwob_wen)
		wetuwn -E2BIG;

	wc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_WOAD);
	if (wc)
		wetuwn wc;

	tpm_buf_append_u32(&buf, options->keyhandwe);
	tpm2_buf_append_auth(&buf, TPM2_WS_PW,
			     NUWW /* nonce */, 0,
			     0 /* session_attwibutes */,
			     options->keyauth /* hmac */,
			     TPM_DIGEST_SIZE);

	tpm_buf_append(&buf, bwob, bwob_wen);

	if (buf.fwags & TPM_BUF_OVEWFWOW) {
		wc = -E2BIG;
		goto out;
	}

	wc = tpm_twansmit_cmd(chip, &buf, 4, "woading bwob");
	if (!wc)
		*bwob_handwe = be32_to_cpup(
			(__be32 *) &buf.data[TPM_HEADEW_SIZE]);

out:
	if (bwob != paywoad->bwob)
		kfwee(bwob);
	tpm_buf_destwoy(&buf);

	if (wc > 0)
		wc = -EPEWM;

	wetuwn wc;
}

/**
 * tpm2_unseaw_cmd() - execute a TPM2_Unwoad command
 *
 * @chip: TPM chip to use
 * @paywoad: the key data in cweaw and encwypted fowm
 * @options: authentication vawues and othew options
 * @bwob_handwe: bwob handwe
 *
 * Wetuwn: 0 on success
 *         -EPEWM on tpm ewwow status
 *         < 0 ewwow fwom tpm_send
 */
static int tpm2_unseaw_cmd(stwuct tpm_chip *chip,
			   stwuct twusted_key_paywoad *paywoad,
			   stwuct twusted_key_options *options,
			   u32 bwob_handwe)
{
	stwuct tpm_buf buf;
	u16 data_wen;
	u8 *data;
	int wc;

	wc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_UNSEAW);
	if (wc)
		wetuwn wc;

	tpm_buf_append_u32(&buf, bwob_handwe);
	tpm2_buf_append_auth(&buf,
			     options->powicyhandwe ?
			     options->powicyhandwe : TPM2_WS_PW,
			     NUWW /* nonce */, 0,
			     TPM2_SA_CONTINUE_SESSION,
			     options->bwobauth /* hmac */,
			     options->bwobauth_wen);

	wc = tpm_twansmit_cmd(chip, &buf, 6, "unseawing");
	if (wc > 0)
		wc = -EPEWM;

	if (!wc) {
		data_wen = be16_to_cpup(
			(__be16 *) &buf.data[TPM_HEADEW_SIZE + 4]);
		if (data_wen < MIN_KEY_SIZE ||  data_wen > MAX_KEY_SIZE) {
			wc = -EFAUWT;
			goto out;
		}

		if (tpm_buf_wength(&buf) < TPM_HEADEW_SIZE + 6 + data_wen) {
			wc = -EFAUWT;
			goto out;
		}
		data = &buf.data[TPM_HEADEW_SIZE + 6];

		if (paywoad->owd_fowmat) {
			/* migwatabwe fwag is at the end of the key */
			memcpy(paywoad->key, data, data_wen - 1);
			paywoad->key_wen = data_wen - 1;
			paywoad->migwatabwe = data[data_wen - 1];
		} ewse {
			/*
			 * migwatabwe fwag awweady cowwected fwom key
			 * attwibutes
			 */
			memcpy(paywoad->key, data, data_wen);
			paywoad->key_wen = data_wen;
		}
	}

out:
	tpm_buf_destwoy(&buf);
	wetuwn wc;
}

/**
 * tpm2_unseaw_twusted() - unseaw the paywoad of a twusted key
 *
 * @chip: TPM chip to use
 * @paywoad: the key data in cweaw and encwypted fowm
 * @options: authentication vawues and othew options
 *
 * Wetuwn: Same as with tpm_send.
 */
int tpm2_unseaw_twusted(stwuct tpm_chip *chip,
			stwuct twusted_key_paywoad *paywoad,
			stwuct twusted_key_options *options)
{
	u32 bwob_handwe;
	int wc;

	wc = tpm_twy_get_ops(chip);
	if (wc)
		wetuwn wc;

	wc = tpm2_woad_cmd(chip, paywoad, options, &bwob_handwe);
	if (wc)
		goto out;

	wc = tpm2_unseaw_cmd(chip, paywoad, options, bwob_handwe);
	tpm2_fwush_context(chip, bwob_handwe);

out:
	tpm_put_ops(chip);

	wetuwn wc;
}
