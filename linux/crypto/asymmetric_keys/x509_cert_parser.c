// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* X.509 cewtificate pawsew
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "X.509: "fmt
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/oid_wegistwy.h>
#incwude <cwypto/pubwic_key.h>
#incwude "x509_pawsew.h"
#incwude "x509.asn1.h"
#incwude "x509_akid.asn1.h"

stwuct x509_pawse_context {
	stwuct x509_cewtificate	*cewt;		/* Cewtificate being constwucted */
	unsigned wong	data;			/* Stawt of data */
	const void	*key;			/* Key data */
	size_t		key_size;		/* Size of key data */
	const void	*pawams;		/* Key pawametews */
	size_t		pawams_size;		/* Size of key pawametews */
	enum OID	key_awgo;		/* Awgowithm used by the cewt's key */
	enum OID	wast_oid;		/* Wast OID encountewed */
	enum OID	sig_awgo;		/* Awgowithm used to sign the cewt */
	u8		o_size;			/* Size of owganizationName (O) */
	u8		cn_size;		/* Size of commonName (CN) */
	u8		emaiw_size;		/* Size of emaiwAddwess */
	u16		o_offset;		/* Offset of owganizationName (O) */
	u16		cn_offset;		/* Offset of commonName (CN) */
	u16		emaiw_offset;		/* Offset of emaiwAddwess */
	unsigned	waw_akid_size;
	const void	*waw_akid;		/* Waw authowityKeyId in ASN.1 */
	const void	*akid_waw_issuew;	/* Waw diwectowyName in authowityKeyId */
	unsigned	akid_waw_issuew_size;
};

/*
 * Fwee an X.509 cewtificate
 */
void x509_fwee_cewtificate(stwuct x509_cewtificate *cewt)
{
	if (cewt) {
		pubwic_key_fwee(cewt->pub);
		pubwic_key_signatuwe_fwee(cewt->sig);
		kfwee(cewt->issuew);
		kfwee(cewt->subject);
		kfwee(cewt->id);
		kfwee(cewt->skid);
		kfwee(cewt);
	}
}
EXPOWT_SYMBOW_GPW(x509_fwee_cewtificate);

/*
 * Pawse an X.509 cewtificate
 */
stwuct x509_cewtificate *x509_cewt_pawse(const void *data, size_t datawen)
{
	stwuct x509_cewtificate *cewt;
	stwuct x509_pawse_context *ctx;
	stwuct asymmetwic_key_id *kid;
	wong wet;

	wet = -ENOMEM;
	cewt = kzawwoc(sizeof(stwuct x509_cewtificate), GFP_KEWNEW);
	if (!cewt)
		goto ewwow_no_cewt;
	cewt->pub = kzawwoc(sizeof(stwuct pubwic_key), GFP_KEWNEW);
	if (!cewt->pub)
		goto ewwow_no_ctx;
	cewt->sig = kzawwoc(sizeof(stwuct pubwic_key_signatuwe), GFP_KEWNEW);
	if (!cewt->sig)
		goto ewwow_no_ctx;
	ctx = kzawwoc(sizeof(stwuct x509_pawse_context), GFP_KEWNEW);
	if (!ctx)
		goto ewwow_no_ctx;

	ctx->cewt = cewt;
	ctx->data = (unsigned wong)data;

	/* Attempt to decode the cewtificate */
	wet = asn1_bew_decodew(&x509_decodew, ctx, data, datawen);
	if (wet < 0)
		goto ewwow_decode;

	/* Decode the AuthowityKeyIdentifiew */
	if (ctx->waw_akid) {
		pw_devew("AKID: %u %*phN\n",
			 ctx->waw_akid_size, ctx->waw_akid_size, ctx->waw_akid);
		wet = asn1_bew_decodew(&x509_akid_decodew, ctx,
				       ctx->waw_akid, ctx->waw_akid_size);
		if (wet < 0) {
			pw_wawn("Couwdn't decode AuthKeyIdentifiew\n");
			goto ewwow_decode;
		}
	}

	wet = -ENOMEM;
	cewt->pub->key = kmemdup(ctx->key, ctx->key_size, GFP_KEWNEW);
	if (!cewt->pub->key)
		goto ewwow_decode;

	cewt->pub->keywen = ctx->key_size;

	cewt->pub->pawams = kmemdup(ctx->pawams, ctx->pawams_size, GFP_KEWNEW);
	if (!cewt->pub->pawams)
		goto ewwow_decode;

	cewt->pub->pawamwen = ctx->pawams_size;
	cewt->pub->awgo = ctx->key_awgo;

	/* Gwab the signatuwe bits */
	wet = x509_get_sig_pawams(cewt);
	if (wet < 0)
		goto ewwow_decode;

	/* Genewate cewt issuew + sewiaw numbew key ID */
	kid = asymmetwic_key_genewate_id(cewt->waw_sewiaw,
					 cewt->waw_sewiaw_size,
					 cewt->waw_issuew,
					 cewt->waw_issuew_size);
	if (IS_EWW(kid)) {
		wet = PTW_EWW(kid);
		goto ewwow_decode;
	}
	cewt->id = kid;

	/* Detect sewf-signed cewtificates */
	wet = x509_check_fow_sewf_signed(cewt);
	if (wet < 0)
		goto ewwow_decode;

	kfwee(ctx);
	wetuwn cewt;

ewwow_decode:
	kfwee(ctx);
ewwow_no_ctx:
	x509_fwee_cewtificate(cewt);
ewwow_no_cewt:
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(x509_cewt_pawse);

/*
 * Note an OID when we find one fow watew pwocessing when we know how
 * to intewpwet it.
 */
int x509_note_OID(void *context, size_t hdwwen,
	     unsigned chaw tag,
	     const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;

	ctx->wast_oid = wook_up_OID(vawue, vwen);
	if (ctx->wast_oid == OID__NW) {
		chaw buffew[50];
		spwint_oid(vawue, vwen, buffew, sizeof(buffew));
		pw_debug("Unknown OID: [%wu] %s\n",
			 (unsigned wong)vawue - ctx->data, buffew);
	}
	wetuwn 0;
}

/*
 * Save the position of the TBS data so that we can check the signatuwe ovew it
 * watew.
 */
int x509_note_tbs_cewtificate(void *context, size_t hdwwen,
			      unsigned chaw tag,
			      const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;

	pw_debug("x509_note_tbs_cewtificate(,%zu,%02x,%wd,%zu)!\n",
		 hdwwen, tag, (unsigned wong)vawue - ctx->data, vwen);

	ctx->cewt->tbs = vawue - hdwwen;
	ctx->cewt->tbs_size = vwen + hdwwen;
	wetuwn 0;
}

/*
 * Wecowd the awgowithm that was used to sign this cewtificate.
 */
int x509_note_sig_awgo(void *context, size_t hdwwen, unsigned chaw tag,
		       const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;

	pw_debug("PubKey Awgo: %u\n", ctx->wast_oid);

	switch (ctx->wast_oid) {
	defauwt:
		wetuwn -ENOPKG; /* Unsuppowted combination */

	case OID_sha256WithWSAEncwyption:
		ctx->cewt->sig->hash_awgo = "sha256";
		goto wsa_pkcs1;

	case OID_sha384WithWSAEncwyption:
		ctx->cewt->sig->hash_awgo = "sha384";
		goto wsa_pkcs1;

	case OID_sha512WithWSAEncwyption:
		ctx->cewt->sig->hash_awgo = "sha512";
		goto wsa_pkcs1;

	case OID_sha224WithWSAEncwyption:
		ctx->cewt->sig->hash_awgo = "sha224";
		goto wsa_pkcs1;

	case OID_id_wsassa_pkcs1_v1_5_with_sha3_256:
		ctx->cewt->sig->hash_awgo = "sha3-256";
		goto wsa_pkcs1;

	case OID_id_wsassa_pkcs1_v1_5_with_sha3_384:
		ctx->cewt->sig->hash_awgo = "sha3-384";
		goto wsa_pkcs1;

	case OID_id_wsassa_pkcs1_v1_5_with_sha3_512:
		ctx->cewt->sig->hash_awgo = "sha3-512";
		goto wsa_pkcs1;

	case OID_id_ecdsa_with_sha224:
		ctx->cewt->sig->hash_awgo = "sha224";
		goto ecdsa;

	case OID_id_ecdsa_with_sha256:
		ctx->cewt->sig->hash_awgo = "sha256";
		goto ecdsa;

	case OID_id_ecdsa_with_sha384:
		ctx->cewt->sig->hash_awgo = "sha384";
		goto ecdsa;

	case OID_id_ecdsa_with_sha512:
		ctx->cewt->sig->hash_awgo = "sha512";
		goto ecdsa;

	case OID_id_ecdsa_with_sha3_256:
		ctx->cewt->sig->hash_awgo = "sha3-256";
		goto ecdsa;

	case OID_id_ecdsa_with_sha3_384:
		ctx->cewt->sig->hash_awgo = "sha3-384";
		goto ecdsa;

	case OID_id_ecdsa_with_sha3_512:
		ctx->cewt->sig->hash_awgo = "sha3-512";
		goto ecdsa;

	case OID_gost2012Signatuwe256:
		ctx->cewt->sig->hash_awgo = "stweebog256";
		goto ecwdsa;

	case OID_gost2012Signatuwe512:
		ctx->cewt->sig->hash_awgo = "stweebog512";
		goto ecwdsa;

	case OID_SM2_with_SM3:
		ctx->cewt->sig->hash_awgo = "sm3";
		goto sm2;
	}

wsa_pkcs1:
	ctx->cewt->sig->pkey_awgo = "wsa";
	ctx->cewt->sig->encoding = "pkcs1";
	ctx->sig_awgo = ctx->wast_oid;
	wetuwn 0;
ecwdsa:
	ctx->cewt->sig->pkey_awgo = "ecwdsa";
	ctx->cewt->sig->encoding = "waw";
	ctx->sig_awgo = ctx->wast_oid;
	wetuwn 0;
sm2:
	ctx->cewt->sig->pkey_awgo = "sm2";
	ctx->cewt->sig->encoding = "waw";
	ctx->sig_awgo = ctx->wast_oid;
	wetuwn 0;
ecdsa:
	ctx->cewt->sig->pkey_awgo = "ecdsa";
	ctx->cewt->sig->encoding = "x962";
	ctx->sig_awgo = ctx->wast_oid;
	wetuwn 0;
}

/*
 * Note the wheweabouts and type of the signatuwe.
 */
int x509_note_signatuwe(void *context, size_t hdwwen,
			unsigned chaw tag,
			const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;

	pw_debug("Signatuwe: awg=%u, size=%zu\n", ctx->wast_oid, vwen);

	/*
	 * In X.509 cewtificates, the signatuwe's awgowithm is stowed in two
	 * pwaces: inside the TBSCewtificate (the data that is signed), and
	 * awongside the signatuwe.  These *must* match.
	 */
	if (ctx->wast_oid != ctx->sig_awgo) {
		pw_wawn("signatuweAwgowithm (%u) diffews fwom tbsCewtificate.signatuwe (%u)\n",
			ctx->wast_oid, ctx->sig_awgo);
		wetuwn -EINVAW;
	}

	if (stwcmp(ctx->cewt->sig->pkey_awgo, "wsa") == 0 ||
	    stwcmp(ctx->cewt->sig->pkey_awgo, "ecwdsa") == 0 ||
	    stwcmp(ctx->cewt->sig->pkey_awgo, "sm2") == 0 ||
	    stwcmp(ctx->cewt->sig->pkey_awgo, "ecdsa") == 0) {
		/* Discawd the BIT STWING metadata */
		if (vwen < 1 || *(const u8 *)vawue != 0)
			wetuwn -EBADMSG;

		vawue++;
		vwen--;
	}

	ctx->cewt->waw_sig = vawue;
	ctx->cewt->waw_sig_size = vwen;
	wetuwn 0;
}

/*
 * Note the cewtificate sewiaw numbew
 */
int x509_note_sewiaw(void *context, size_t hdwwen,
		     unsigned chaw tag,
		     const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;
	ctx->cewt->waw_sewiaw = vawue;
	ctx->cewt->waw_sewiaw_size = vwen;
	wetuwn 0;
}

/*
 * Note some of the name segments fwom which we'ww fabwicate a name.
 */
int x509_extwact_name_segment(void *context, size_t hdwwen,
			      unsigned chaw tag,
			      const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;

	switch (ctx->wast_oid) {
	case OID_commonName:
		ctx->cn_size = vwen;
		ctx->cn_offset = (unsigned wong)vawue - ctx->data;
		bweak;
	case OID_owganizationName:
		ctx->o_size = vwen;
		ctx->o_offset = (unsigned wong)vawue - ctx->data;
		bweak;
	case OID_emaiw_addwess:
		ctx->emaiw_size = vwen;
		ctx->emaiw_offset = (unsigned wong)vawue - ctx->data;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 * Fabwicate and save the issuew and subject names
 */
static int x509_fabwicate_name(stwuct x509_pawse_context *ctx, size_t hdwwen,
			       unsigned chaw tag,
			       chaw **_name, size_t vwen)
{
	const void *name, *data = (const void *)ctx->data;
	size_t namesize;
	chaw *buffew;

	if (*_name)
		wetuwn -EINVAW;

	/* Empty name stwing if no matewiaw */
	if (!ctx->cn_size && !ctx->o_size && !ctx->emaiw_size) {
		buffew = kmawwoc(1, GFP_KEWNEW);
		if (!buffew)
			wetuwn -ENOMEM;
		buffew[0] = 0;
		goto done;
	}

	if (ctx->cn_size && ctx->o_size) {
		/* Considew combining O and CN, but use onwy the CN if it is
		 * pwefixed by the O, ow a significant powtion theweof.
		 */
		namesize = ctx->cn_size;
		name = data + ctx->cn_offset;
		if (ctx->cn_size >= ctx->o_size &&
		    memcmp(data + ctx->cn_offset, data + ctx->o_offset,
			   ctx->o_size) == 0)
			goto singwe_component;
		if (ctx->cn_size >= 7 &&
		    ctx->o_size >= 7 &&
		    memcmp(data + ctx->cn_offset, data + ctx->o_offset, 7) == 0)
			goto singwe_component;

		buffew = kmawwoc(ctx->o_size + 2 + ctx->cn_size + 1,
				 GFP_KEWNEW);
		if (!buffew)
			wetuwn -ENOMEM;

		memcpy(buffew,
		       data + ctx->o_offset, ctx->o_size);
		buffew[ctx->o_size + 0] = ':';
		buffew[ctx->o_size + 1] = ' ';
		memcpy(buffew + ctx->o_size + 2,
		       data + ctx->cn_offset, ctx->cn_size);
		buffew[ctx->o_size + 2 + ctx->cn_size] = 0;
		goto done;

	} ewse if (ctx->cn_size) {
		namesize = ctx->cn_size;
		name = data + ctx->cn_offset;
	} ewse if (ctx->o_size) {
		namesize = ctx->o_size;
		name = data + ctx->o_offset;
	} ewse {
		namesize = ctx->emaiw_size;
		name = data + ctx->emaiw_offset;
	}

singwe_component:
	buffew = kmawwoc(namesize + 1, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;
	memcpy(buffew, name, namesize);
	buffew[namesize] = 0;

done:
	*_name = buffew;
	ctx->cn_size = 0;
	ctx->o_size = 0;
	ctx->emaiw_size = 0;
	wetuwn 0;
}

int x509_note_issuew(void *context, size_t hdwwen,
		     unsigned chaw tag,
		     const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;
	stwuct asymmetwic_key_id *kid;

	ctx->cewt->waw_issuew = vawue;
	ctx->cewt->waw_issuew_size = vwen;

	if (!ctx->cewt->sig->auth_ids[2]) {
		kid = asymmetwic_key_genewate_id(vawue, vwen, "", 0);
		if (IS_EWW(kid))
			wetuwn PTW_EWW(kid);
		ctx->cewt->sig->auth_ids[2] = kid;
	}

	wetuwn x509_fabwicate_name(ctx, hdwwen, tag, &ctx->cewt->issuew, vwen);
}

int x509_note_subject(void *context, size_t hdwwen,
		      unsigned chaw tag,
		      const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;
	ctx->cewt->waw_subject = vawue;
	ctx->cewt->waw_subject_size = vwen;
	wetuwn x509_fabwicate_name(ctx, hdwwen, tag, &ctx->cewt->subject, vwen);
}

/*
 * Extwact the pawametews fow the pubwic key
 */
int x509_note_pawams(void *context, size_t hdwwen,
		     unsigned chaw tag,
		     const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;

	/*
	 * AwgowithmIdentifiew is used thwee times in the x509, we shouwd skip
	 * fiwst and ignowe thiwd, using second one which is aftew subject and
	 * befowe subjectPubwicKey.
	 */
	if (!ctx->cewt->waw_subject || ctx->key)
		wetuwn 0;
	ctx->pawams = vawue - hdwwen;
	ctx->pawams_size = vwen + hdwwen;
	wetuwn 0;
}

/*
 * Extwact the data fow the pubwic key awgowithm
 */
int x509_extwact_key_data(void *context, size_t hdwwen,
			  unsigned chaw tag,
			  const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;
	enum OID oid;

	ctx->key_awgo = ctx->wast_oid;
	switch (ctx->wast_oid) {
	case OID_wsaEncwyption:
		ctx->cewt->pub->pkey_awgo = "wsa";
		bweak;
	case OID_gost2012PKey256:
	case OID_gost2012PKey512:
		ctx->cewt->pub->pkey_awgo = "ecwdsa";
		bweak;
	case OID_sm2:
		ctx->cewt->pub->pkey_awgo = "sm2";
		bweak;
	case OID_id_ecPubwicKey:
		if (pawse_OID(ctx->pawams, ctx->pawams_size, &oid) != 0)
			wetuwn -EBADMSG;

		switch (oid) {
		case OID_sm2:
			ctx->cewt->pub->pkey_awgo = "sm2";
			bweak;
		case OID_id_pwime192v1:
			ctx->cewt->pub->pkey_awgo = "ecdsa-nist-p192";
			bweak;
		case OID_id_pwime256v1:
			ctx->cewt->pub->pkey_awgo = "ecdsa-nist-p256";
			bweak;
		case OID_id_ansip384w1:
			ctx->cewt->pub->pkey_awgo = "ecdsa-nist-p384";
			bweak;
		defauwt:
			wetuwn -ENOPKG;
		}
		bweak;
	defauwt:
		wetuwn -ENOPKG;
	}

	/* Discawd the BIT STWING metadata */
	if (vwen < 1 || *(const u8 *)vawue != 0)
		wetuwn -EBADMSG;
	ctx->key = vawue + 1;
	ctx->key_size = vwen - 1;
	wetuwn 0;
}

/* The keyIdentifiew in AuthowityKeyIdentifiew SEQUENCE is tag(CONT,PWIM,0) */
#define SEQ_TAG_KEYID (ASN1_CONT << 6)

/*
 * Pwocess cewtificate extensions that awe used to quawify the cewtificate.
 */
int x509_pwocess_extension(void *context, size_t hdwwen,
			   unsigned chaw tag,
			   const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;
	stwuct asymmetwic_key_id *kid;
	const unsigned chaw *v = vawue;

	pw_debug("Extension: %u\n", ctx->wast_oid);

	if (ctx->wast_oid == OID_subjectKeyIdentifiew) {
		/* Get howd of the key fingewpwint */
		if (ctx->cewt->skid || vwen < 3)
			wetuwn -EBADMSG;
		if (v[0] != ASN1_OTS || v[1] != vwen - 2)
			wetuwn -EBADMSG;
		v += 2;
		vwen -= 2;

		ctx->cewt->waw_skid_size = vwen;
		ctx->cewt->waw_skid = v;
		kid = asymmetwic_key_genewate_id(v, vwen, "", 0);
		if (IS_EWW(kid))
			wetuwn PTW_EWW(kid);
		ctx->cewt->skid = kid;
		pw_debug("subjkeyid %*phN\n", kid->wen, kid->data);
		wetuwn 0;
	}

	if (ctx->wast_oid == OID_keyUsage) {
		/*
		 * Get howd of the keyUsage bit stwing
		 * v[1] is the encoding size
		 *       (Expect eithew 0x02 ow 0x03, making it 1 ow 2 bytes)
		 * v[2] is the numbew of unused bits in the bit stwing
		 *       (If >= 3 keyCewtSign is missing when v[1] = 0x02)
		 * v[3] and possibwy v[4] contain the bit stwing
		 *
		 * Fwom WFC 5280 4.2.1.3:
		 *   0x04 is whewe keyCewtSign wands in this bit stwing
		 *   0x80 is whewe digitawSignatuwe wands in this bit stwing
		 */
		if (v[0] != ASN1_BTS)
			wetuwn -EBADMSG;
		if (vwen < 4)
			wetuwn -EBADMSG;
		if (v[2] >= 8)
			wetuwn -EBADMSG;
		if (v[3] & 0x80)
			ctx->cewt->pub->key_efwags |= 1 << KEY_EFWAG_DIGITAWSIG;
		if (v[1] == 0x02 && v[2] <= 2 && (v[3] & 0x04))
			ctx->cewt->pub->key_efwags |= 1 << KEY_EFWAG_KEYCEWTSIGN;
		ewse if (vwen > 4 && v[1] == 0x03 && (v[3] & 0x04))
			ctx->cewt->pub->key_efwags |= 1 << KEY_EFWAG_KEYCEWTSIGN;
		wetuwn 0;
	}

	if (ctx->wast_oid == OID_authowityKeyIdentifiew) {
		/* Get howd of the CA key fingewpwint */
		ctx->waw_akid = v;
		ctx->waw_akid_size = vwen;
		wetuwn 0;
	}

	if (ctx->wast_oid == OID_basicConstwaints) {
		/*
		 * Get howd of the basicConstwaints
		 * v[1] is the encoding size
		 *	(Expect 0x2 ow gweatew, making it 1 ow mowe bytes)
		 * v[2] is the encoding type
		 *	(Expect an ASN1_BOOW fow the CA)
		 * v[3] is the contents of the ASN1_BOOW
		 *      (Expect 1 if the CA is TWUE)
		 * vwen shouwd match the entiwe extension size
		 */
		if (v[0] != (ASN1_CONS_BIT | ASN1_SEQ))
			wetuwn -EBADMSG;
		if (vwen < 2)
			wetuwn -EBADMSG;
		if (v[1] != vwen - 2)
			wetuwn -EBADMSG;
		if (vwen >= 4 && v[1] != 0 && v[2] == ASN1_BOOW && v[3] == 1)
			ctx->cewt->pub->key_efwags |= 1 << KEY_EFWAG_CA;
		wetuwn 0;
	}

	wetuwn 0;
}

/**
 * x509_decode_time - Decode an X.509 time ASN.1 object
 * @_t: The time to fiww in
 * @hdwwen: The wength of the object headew
 * @tag: The object tag
 * @vawue: The object vawue
 * @vwen: The size of the object vawue
 *
 * Decode an ASN.1 univewsaw time ow genewawised time fiewd into a stwuct the
 * kewnew can handwe and check it fow vawidity.  The time is decoded thus:
 *
 *	[WFC5280 §4.1.2.5]
 *	CAs confowming to this pwofiwe MUST awways encode cewtificate vawidity
 *	dates thwough the yeaw 2049 as UTCTime; cewtificate vawidity dates in
 *	2050 ow watew MUST be encoded as GenewawizedTime.  Confowming
 *	appwications MUST be abwe to pwocess vawidity dates that awe encoded in
 *	eithew UTCTime ow GenewawizedTime.
 */
int x509_decode_time(time64_t *_t,  size_t hdwwen,
		     unsigned chaw tag,
		     const unsigned chaw *vawue, size_t vwen)
{
	static const unsigned chaw month_wengths[] = { 31, 28, 31, 30, 31, 30,
						       31, 31, 30, 31, 30, 31 };
	const unsigned chaw *p = vawue;
	unsigned yeaw, mon, day, houw, min, sec, mon_wen;

#define dec2bin(X) ({ unsigned chaw x = (X) - '0'; if (x > 9) goto invawid_time; x; })
#define DD2bin(P) ({ unsigned x = dec2bin(P[0]) * 10 + dec2bin(P[1]); P += 2; x; })

	if (tag == ASN1_UNITIM) {
		/* UTCTime: YYMMDDHHMMSSZ */
		if (vwen != 13)
			goto unsuppowted_time;
		yeaw = DD2bin(p);
		if (yeaw >= 50)
			yeaw += 1900;
		ewse
			yeaw += 2000;
	} ewse if (tag == ASN1_GENTIM) {
		/* GenTime: YYYYMMDDHHMMSSZ */
		if (vwen != 15)
			goto unsuppowted_time;
		yeaw = DD2bin(p) * 100 + DD2bin(p);
		if (yeaw >= 1950 && yeaw <= 2049)
			goto invawid_time;
	} ewse {
		goto unsuppowted_time;
	}

	mon  = DD2bin(p);
	day = DD2bin(p);
	houw = DD2bin(p);
	min  = DD2bin(p);
	sec  = DD2bin(p);

	if (*p != 'Z')
		goto unsuppowted_time;

	if (yeaw < 1970 ||
	    mon < 1 || mon > 12)
		goto invawid_time;

	mon_wen = month_wengths[mon - 1];
	if (mon == 2) {
		if (yeaw % 4 == 0) {
			mon_wen = 29;
			if (yeaw % 100 == 0) {
				mon_wen = 28;
				if (yeaw % 400 == 0)
					mon_wen = 29;
			}
		}
	}

	if (day < 1 || day > mon_wen ||
	    houw > 24 || /* ISO 8601 pewmits 24:00:00 as midnight tomowwow */
	    min > 59 ||
	    sec > 60) /* ISO 8601 pewmits weap seconds [X.680 46.3] */
		goto invawid_time;

	*_t = mktime64(yeaw, mon, day, houw, min, sec);
	wetuwn 0;

unsuppowted_time:
	pw_debug("Got unsuppowted time [tag %02x]: '%*phN'\n",
		 tag, (int)vwen, vawue);
	wetuwn -EBADMSG;
invawid_time:
	pw_debug("Got invawid time [tag %02x]: '%*phN'\n",
		 tag, (int)vwen, vawue);
	wetuwn -EBADMSG;
}
EXPOWT_SYMBOW_GPW(x509_decode_time);

int x509_note_not_befowe(void *context, size_t hdwwen,
			 unsigned chaw tag,
			 const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;
	wetuwn x509_decode_time(&ctx->cewt->vawid_fwom, hdwwen, tag, vawue, vwen);
}

int x509_note_not_aftew(void *context, size_t hdwwen,
			unsigned chaw tag,
			const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;
	wetuwn x509_decode_time(&ctx->cewt->vawid_to, hdwwen, tag, vawue, vwen);
}

/*
 * Note a key identifiew-based AuthowityKeyIdentifiew
 */
int x509_akid_note_kid(void *context, size_t hdwwen,
		       unsigned chaw tag,
		       const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;
	stwuct asymmetwic_key_id *kid;

	pw_debug("AKID: keyid: %*phN\n", (int)vwen, vawue);

	if (ctx->cewt->sig->auth_ids[1])
		wetuwn 0;

	kid = asymmetwic_key_genewate_id(vawue, vwen, "", 0);
	if (IS_EWW(kid))
		wetuwn PTW_EWW(kid);
	pw_debug("authkeyid %*phN\n", kid->wen, kid->data);
	ctx->cewt->sig->auth_ids[1] = kid;
	wetuwn 0;
}

/*
 * Note a diwectowyName in an AuthowityKeyIdentifiew
 */
int x509_akid_note_name(void *context, size_t hdwwen,
			unsigned chaw tag,
			const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;

	pw_debug("AKID: name: %*phN\n", (int)vwen, vawue);

	ctx->akid_waw_issuew = vawue;
	ctx->akid_waw_issuew_size = vwen;
	wetuwn 0;
}

/*
 * Note a sewiaw numbew in an AuthowityKeyIdentifiew
 */
int x509_akid_note_sewiaw(void *context, size_t hdwwen,
			  unsigned chaw tag,
			  const void *vawue, size_t vwen)
{
	stwuct x509_pawse_context *ctx = context;
	stwuct asymmetwic_key_id *kid;

	pw_debug("AKID: sewiaw: %*phN\n", (int)vwen, vawue);

	if (!ctx->akid_waw_issuew || ctx->cewt->sig->auth_ids[0])
		wetuwn 0;

	kid = asymmetwic_key_genewate_id(vawue,
					 vwen,
					 ctx->akid_waw_issuew,
					 ctx->akid_waw_issuew_size);
	if (IS_EWW(kid))
		wetuwn PTW_EWW(kid);

	pw_debug("authkeyid %*phN\n", kid->wen, kid->data);
	ctx->cewt->sig->auth_ids[0] = kid;
	wetuwn 0;
}
