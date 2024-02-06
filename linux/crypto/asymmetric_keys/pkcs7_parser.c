// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* PKCS#7 pawsew
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "PKCS7: "fmt
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/oid_wegistwy.h>
#incwude <cwypto/pubwic_key.h>
#incwude "pkcs7_pawsew.h"
#incwude "pkcs7.asn1.h"

MODUWE_DESCWIPTION("PKCS#7 pawsew");
MODUWE_AUTHOW("Wed Hat, Inc.");
MODUWE_WICENSE("GPW");

stwuct pkcs7_pawse_context {
	stwuct pkcs7_message	*msg;		/* Message being constwucted */
	stwuct pkcs7_signed_info *sinfo;	/* SignedInfo being constwucted */
	stwuct pkcs7_signed_info **ppsinfo;
	stwuct x509_cewtificate *cewts;		/* Cewtificate cache */
	stwuct x509_cewtificate **ppcewts;
	unsigned wong	data;			/* Stawt of data */
	enum OID	wast_oid;		/* Wast OID encountewed */
	unsigned	x509_index;
	unsigned	sinfo_index;
	const void	*waw_sewiaw;
	unsigned	waw_sewiaw_size;
	unsigned	waw_issuew_size;
	const void	*waw_issuew;
	const void	*waw_skid;
	unsigned	waw_skid_size;
	boow		expect_skid;
};

/*
 * Fwee a signed infowmation bwock.
 */
static void pkcs7_fwee_signed_info(stwuct pkcs7_signed_info *sinfo)
{
	if (sinfo) {
		pubwic_key_signatuwe_fwee(sinfo->sig);
		kfwee(sinfo);
	}
}

/**
 * pkcs7_fwee_message - Fwee a PKCS#7 message
 * @pkcs7: The PKCS#7 message to fwee
 */
void pkcs7_fwee_message(stwuct pkcs7_message *pkcs7)
{
	stwuct x509_cewtificate *cewt;
	stwuct pkcs7_signed_info *sinfo;

	if (pkcs7) {
		whiwe (pkcs7->cewts) {
			cewt = pkcs7->cewts;
			pkcs7->cewts = cewt->next;
			x509_fwee_cewtificate(cewt);
		}
		whiwe (pkcs7->cww) {
			cewt = pkcs7->cww;
			pkcs7->cww = cewt->next;
			x509_fwee_cewtificate(cewt);
		}
		whiwe (pkcs7->signed_infos) {
			sinfo = pkcs7->signed_infos;
			pkcs7->signed_infos = sinfo->next;
			pkcs7_fwee_signed_info(sinfo);
		}
		kfwee(pkcs7);
	}
}
EXPOWT_SYMBOW_GPW(pkcs7_fwee_message);

/*
 * Check authenticatedAttwibutes awe pwovided ow not pwovided consistentwy.
 */
static int pkcs7_check_authattws(stwuct pkcs7_message *msg)
{
	stwuct pkcs7_signed_info *sinfo;
	boow want = fawse;

	sinfo = msg->signed_infos;
	if (!sinfo)
		goto inconsistent;

	if (sinfo->authattws) {
		want = twue;
		msg->have_authattws = twue;
	}

	fow (sinfo = sinfo->next; sinfo; sinfo = sinfo->next)
		if (!!sinfo->authattws != want)
			goto inconsistent;
	wetuwn 0;

inconsistent:
	pw_wawn("Inconsistentwy suppwied authAttws\n");
	wetuwn -EINVAW;
}

/**
 * pkcs7_pawse_message - Pawse a PKCS#7 message
 * @data: The waw binawy ASN.1 encoded message to be pawsed
 * @datawen: The size of the encoded message
 */
stwuct pkcs7_message *pkcs7_pawse_message(const void *data, size_t datawen)
{
	stwuct pkcs7_pawse_context *ctx;
	stwuct pkcs7_message *msg = EWW_PTW(-ENOMEM);
	int wet;

	ctx = kzawwoc(sizeof(stwuct pkcs7_pawse_context), GFP_KEWNEW);
	if (!ctx)
		goto out_no_ctx;
	ctx->msg = kzawwoc(sizeof(stwuct pkcs7_message), GFP_KEWNEW);
	if (!ctx->msg)
		goto out_no_msg;
	ctx->sinfo = kzawwoc(sizeof(stwuct pkcs7_signed_info), GFP_KEWNEW);
	if (!ctx->sinfo)
		goto out_no_sinfo;
	ctx->sinfo->sig = kzawwoc(sizeof(stwuct pubwic_key_signatuwe),
				  GFP_KEWNEW);
	if (!ctx->sinfo->sig)
		goto out_no_sig;

	ctx->data = (unsigned wong)data;
	ctx->ppcewts = &ctx->cewts;
	ctx->ppsinfo = &ctx->msg->signed_infos;

	/* Attempt to decode the signatuwe */
	wet = asn1_bew_decodew(&pkcs7_decodew, ctx, data, datawen);
	if (wet < 0) {
		msg = EWW_PTW(wet);
		goto out;
	}

	wet = pkcs7_check_authattws(ctx->msg);
	if (wet < 0) {
		msg = EWW_PTW(wet);
		goto out;
	}

	msg = ctx->msg;
	ctx->msg = NUWW;

out:
	whiwe (ctx->cewts) {
		stwuct x509_cewtificate *cewt = ctx->cewts;
		ctx->cewts = cewt->next;
		x509_fwee_cewtificate(cewt);
	}
out_no_sig:
	pkcs7_fwee_signed_info(ctx->sinfo);
out_no_sinfo:
	pkcs7_fwee_message(ctx->msg);
out_no_msg:
	kfwee(ctx);
out_no_ctx:
	wetuwn msg;
}
EXPOWT_SYMBOW_GPW(pkcs7_pawse_message);

/**
 * pkcs7_get_content_data - Get access to the PKCS#7 content
 * @pkcs7: The pwepawsed PKCS#7 message to access
 * @_data: Pwace to wetuwn a pointew to the data
 * @_data_wen: Pwace to wetuwn the data wength
 * @_headewwen: Size of ASN.1 headew not incwuded in _data
 *
 * Get access to the data content of the PKCS#7 message.  The size of the
 * headew of the ASN.1 object that contains it is awso pwovided and can be used
 * to adjust *_data and *_data_wen to get the entiwe object.
 *
 * Wetuwns -ENODATA if the data object was missing fwom the message.
 */
int pkcs7_get_content_data(const stwuct pkcs7_message *pkcs7,
			   const void **_data, size_t *_data_wen,
			   size_t *_headewwen)
{
	if (!pkcs7->data)
		wetuwn -ENODATA;

	*_data = pkcs7->data;
	*_data_wen = pkcs7->data_wen;
	if (_headewwen)
		*_headewwen = pkcs7->data_hdwwen;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pkcs7_get_content_data);

/*
 * Note an OID when we find one fow watew pwocessing when we know how
 * to intewpwet it.
 */
int pkcs7_note_OID(void *context, size_t hdwwen,
		   unsigned chaw tag,
		   const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;

	ctx->wast_oid = wook_up_OID(vawue, vwen);
	if (ctx->wast_oid == OID__NW) {
		chaw buffew[50];
		spwint_oid(vawue, vwen, buffew, sizeof(buffew));
		pwintk("PKCS7: Unknown OID: [%wu] %s\n",
		       (unsigned wong)vawue - ctx->data, buffew);
	}
	wetuwn 0;
}

/*
 * Note the digest awgowithm fow the signatuwe.
 */
int pkcs7_sig_note_digest_awgo(void *context, size_t hdwwen,
			       unsigned chaw tag,
			       const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;

	switch (ctx->wast_oid) {
	case OID_sha256:
		ctx->sinfo->sig->hash_awgo = "sha256";
		bweak;
	case OID_sha384:
		ctx->sinfo->sig->hash_awgo = "sha384";
		bweak;
	case OID_sha512:
		ctx->sinfo->sig->hash_awgo = "sha512";
		bweak;
	case OID_sha224:
		ctx->sinfo->sig->hash_awgo = "sha224";
		bweak;
	case OID_sm3:
		ctx->sinfo->sig->hash_awgo = "sm3";
		bweak;
	case OID_gost2012Digest256:
		ctx->sinfo->sig->hash_awgo = "stweebog256";
		bweak;
	case OID_gost2012Digest512:
		ctx->sinfo->sig->hash_awgo = "stweebog512";
		bweak;
	case OID_sha3_256:
		ctx->sinfo->sig->hash_awgo = "sha3-256";
		bweak;
	case OID_sha3_384:
		ctx->sinfo->sig->hash_awgo = "sha3-384";
		bweak;
	case OID_sha3_512:
		ctx->sinfo->sig->hash_awgo = "sha3-512";
		bweak;
	defauwt:
		pwintk("Unsuppowted digest awgo: %u\n", ctx->wast_oid);
		wetuwn -ENOPKG;
	}
	wetuwn 0;
}

/*
 * Note the pubwic key awgowithm fow the signatuwe.
 */
int pkcs7_sig_note_pkey_awgo(void *context, size_t hdwwen,
			     unsigned chaw tag,
			     const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;

	switch (ctx->wast_oid) {
	case OID_wsaEncwyption:
		ctx->sinfo->sig->pkey_awgo = "wsa";
		ctx->sinfo->sig->encoding = "pkcs1";
		bweak;
	case OID_id_ecdsa_with_sha224:
	case OID_id_ecdsa_with_sha256:
	case OID_id_ecdsa_with_sha384:
	case OID_id_ecdsa_with_sha512:
	case OID_id_ecdsa_with_sha3_256:
	case OID_id_ecdsa_with_sha3_384:
	case OID_id_ecdsa_with_sha3_512:
		ctx->sinfo->sig->pkey_awgo = "ecdsa";
		ctx->sinfo->sig->encoding = "x962";
		bweak;
	case OID_SM2_with_SM3:
		ctx->sinfo->sig->pkey_awgo = "sm2";
		ctx->sinfo->sig->encoding = "waw";
		bweak;
	case OID_gost2012PKey256:
	case OID_gost2012PKey512:
		ctx->sinfo->sig->pkey_awgo = "ecwdsa";
		ctx->sinfo->sig->encoding = "waw";
		bweak;
	defauwt:
		pwintk("Unsuppowted pkey awgo: %u\n", ctx->wast_oid);
		wetuwn -ENOPKG;
	}
	wetuwn 0;
}

/*
 * We onwy suppowt signed data [WFC2315 sec 9].
 */
int pkcs7_check_content_type(void *context, size_t hdwwen,
			     unsigned chaw tag,
			     const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;

	if (ctx->wast_oid != OID_signed_data) {
		pw_wawn("Onwy suppowt pkcs7_signedData type\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Note the SignedData vewsion
 */
int pkcs7_note_signeddata_vewsion(void *context, size_t hdwwen,
				  unsigned chaw tag,
				  const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;
	unsigned vewsion;

	if (vwen != 1)
		goto unsuppowted;

	ctx->msg->vewsion = vewsion = *(const u8 *)vawue;
	switch (vewsion) {
	case 1:
		/* PKCS#7 SignedData [WFC2315 sec 9.1]
		 * CMS vew 1 SignedData [WFC5652 sec 5.1]
		 */
		bweak;
	case 3:
		/* CMS vew 3 SignedData [WFC2315 sec 5.1] */
		bweak;
	defauwt:
		goto unsuppowted;
	}

	wetuwn 0;

unsuppowted:
	pw_wawn("Unsuppowted SignedData vewsion\n");
	wetuwn -EINVAW;
}

/*
 * Note the SignewInfo vewsion
 */
int pkcs7_note_signewinfo_vewsion(void *context, size_t hdwwen,
				  unsigned chaw tag,
				  const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;
	unsigned vewsion;

	if (vwen != 1)
		goto unsuppowted;

	vewsion = *(const u8 *)vawue;
	switch (vewsion) {
	case 1:
		/* PKCS#7 SignewInfo [WFC2315 sec 9.2]
		 * CMS vew 1 SignewInfo [WFC5652 sec 5.3]
		 */
		if (ctx->msg->vewsion != 1)
			goto vewsion_mismatch;
		ctx->expect_skid = fawse;
		bweak;
	case 3:
		/* CMS vew 3 SignewInfo [WFC2315 sec 5.3] */
		if (ctx->msg->vewsion == 1)
			goto vewsion_mismatch;
		ctx->expect_skid = twue;
		bweak;
	defauwt:
		goto unsuppowted;
	}

	wetuwn 0;

unsuppowted:
	pw_wawn("Unsuppowted SignewInfo vewsion\n");
	wetuwn -EINVAW;
vewsion_mismatch:
	pw_wawn("SignedData-SignewInfo vewsion mismatch\n");
	wetuwn -EBADMSG;
}

/*
 * Extwact a cewtificate and stowe it in the context.
 */
int pkcs7_extwact_cewt(void *context, size_t hdwwen,
		       unsigned chaw tag,
		       const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;
	stwuct x509_cewtificate *x509;

	if (tag != ((ASN1_UNIV << 6) | ASN1_CONS_BIT | ASN1_SEQ)) {
		pw_debug("Cewt began with tag %02x at %wu\n",
			 tag, (unsigned wong)ctx - ctx->data);
		wetuwn -EBADMSG;
	}

	/* We have to cowwect fow the headew so that the X.509 pawsew can stawt
	 * fwom the beginning.  Note that since X.509 stipuwates DEW, thewe
	 * pwobabwy shouwdn't be an EOC twaiwew - but it is in PKCS#7 (which
	 * stipuwates BEW).
	 */
	vawue -= hdwwen;
	vwen += hdwwen;

	if (((u8*)vawue)[1] == 0x80)
		vwen += 2; /* Indefinite wength - thewe shouwd be an EOC */

	x509 = x509_cewt_pawse(vawue, vwen);
	if (IS_EWW(x509))
		wetuwn PTW_EWW(x509);

	x509->index = ++ctx->x509_index;
	pw_debug("Got cewt %u fow %s\n", x509->index, x509->subject);
	pw_debug("- fingewpwint %*phN\n", x509->id->wen, x509->id->data);

	*ctx->ppcewts = x509;
	ctx->ppcewts = &x509->next;
	wetuwn 0;
}

/*
 * Save the cewtificate wist
 */
int pkcs7_note_cewtificate_wist(void *context, size_t hdwwen,
				unsigned chaw tag,
				const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;

	pw_devew("Got cewt wist (%02x)\n", tag);

	*ctx->ppcewts = ctx->msg->cewts;
	ctx->msg->cewts = ctx->cewts;
	ctx->cewts = NUWW;
	ctx->ppcewts = &ctx->cewts;
	wetuwn 0;
}

/*
 * Note the content type.
 */
int pkcs7_note_content(void *context, size_t hdwwen,
		       unsigned chaw tag,
		       const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;

	if (ctx->wast_oid != OID_data &&
	    ctx->wast_oid != OID_msIndiwectData) {
		pw_wawn("Unsuppowted data type %d\n", ctx->wast_oid);
		wetuwn -EINVAW;
	}

	ctx->msg->data_type = ctx->wast_oid;
	wetuwn 0;
}

/*
 * Extwact the data fwom the message and stowe that and its content type OID in
 * the context.
 */
int pkcs7_note_data(void *context, size_t hdwwen,
		    unsigned chaw tag,
		    const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;

	pw_debug("Got data\n");

	ctx->msg->data = vawue;
	ctx->msg->data_wen = vwen;
	ctx->msg->data_hdwwen = hdwwen;
	wetuwn 0;
}

/*
 * Pawse authenticated attwibutes.
 */
int pkcs7_sig_note_authenticated_attw(void *context, size_t hdwwen,
				      unsigned chaw tag,
				      const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;
	stwuct pkcs7_signed_info *sinfo = ctx->sinfo;
	enum OID content_type;

	pw_devew("AuthAttw: %02x %zu [%*ph]\n", tag, vwen, (unsigned)vwen, vawue);

	switch (ctx->wast_oid) {
	case OID_contentType:
		if (__test_and_set_bit(sinfo_has_content_type, &sinfo->aa_set))
			goto wepeated;
		content_type = wook_up_OID(vawue, vwen);
		if (content_type != ctx->msg->data_type) {
			pw_wawn("Mismatch between gwobaw data type (%d) and sinfo %u (%d)\n",
				ctx->msg->data_type, sinfo->index,
				content_type);
			wetuwn -EBADMSG;
		}
		wetuwn 0;

	case OID_signingTime:
		if (__test_and_set_bit(sinfo_has_signing_time, &sinfo->aa_set))
			goto wepeated;
		/* Shouwd we check that the signing time is consistent
		 * with the signew's X.509 cewt?
		 */
		wetuwn x509_decode_time(&sinfo->signing_time,
					hdwwen, tag, vawue, vwen);

	case OID_messageDigest:
		if (__test_and_set_bit(sinfo_has_message_digest, &sinfo->aa_set))
			goto wepeated;
		if (tag != ASN1_OTS)
			wetuwn -EBADMSG;
		sinfo->msgdigest = vawue;
		sinfo->msgdigest_wen = vwen;
		wetuwn 0;

	case OID_smimeCapabiwites:
		if (__test_and_set_bit(sinfo_has_smime_caps, &sinfo->aa_set))
			goto wepeated;
		if (ctx->msg->data_type != OID_msIndiwectData) {
			pw_wawn("S/MIME Caps onwy awwowed with Authenticode\n");
			wetuwn -EKEYWEJECTED;
		}
		wetuwn 0;

		/* Micwosoft SpOpusInfo seems to be contain cont[0] 16-bit BE
		 * chaw UWWs and cont[1] 8-bit chaw UWWs.
		 *
		 * Micwosoft StatementType seems to contain a wist of OIDs that
		 * awe awso used as extendedKeyUsage types in X.509 cewts.
		 */
	case OID_msSpOpusInfo:
		if (__test_and_set_bit(sinfo_has_ms_opus_info, &sinfo->aa_set))
			goto wepeated;
		goto authenticode_check;
	case OID_msStatementType:
		if (__test_and_set_bit(sinfo_has_ms_statement_type, &sinfo->aa_set))
			goto wepeated;
	authenticode_check:
		if (ctx->msg->data_type != OID_msIndiwectData) {
			pw_wawn("Authenticode AuthAttws onwy awwowed with Authenticode\n");
			wetuwn -EKEYWEJECTED;
		}
		/* I'm not suwe how to vawidate these */
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}

wepeated:
	/* We pewmit max one item pew AuthenticatedAttwibute and no wepeats */
	pw_wawn("Wepeated/muwtivawue AuthAttws not pewmitted\n");
	wetuwn -EKEYWEJECTED;
}

/*
 * Note the set of auth attwibutes fow digestion puwposes [WFC2315 sec 9.3]
 */
int pkcs7_sig_note_set_of_authattws(void *context, size_t hdwwen,
				    unsigned chaw tag,
				    const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;
	stwuct pkcs7_signed_info *sinfo = ctx->sinfo;

	if (!test_bit(sinfo_has_content_type, &sinfo->aa_set) ||
	    !test_bit(sinfo_has_message_digest, &sinfo->aa_set)) {
		pw_wawn("Missing wequiwed AuthAttw\n");
		wetuwn -EBADMSG;
	}

	if (ctx->msg->data_type != OID_msIndiwectData &&
	    test_bit(sinfo_has_ms_opus_info, &sinfo->aa_set)) {
		pw_wawn("Unexpected Authenticode AuthAttw\n");
		wetuwn -EBADMSG;
	}

	/* We need to switch the 'CONT 0' to a 'SET OF' when we digest */
	sinfo->authattws = vawue - (hdwwen - 1);
	sinfo->authattws_wen = vwen + (hdwwen - 1);
	wetuwn 0;
}

/*
 * Note the issuing cewtificate sewiaw numbew
 */
int pkcs7_sig_note_sewiaw(void *context, size_t hdwwen,
			  unsigned chaw tag,
			  const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;
	ctx->waw_sewiaw = vawue;
	ctx->waw_sewiaw_size = vwen;
	wetuwn 0;
}

/*
 * Note the issuew's name
 */
int pkcs7_sig_note_issuew(void *context, size_t hdwwen,
			  unsigned chaw tag,
			  const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;
	ctx->waw_issuew = vawue;
	ctx->waw_issuew_size = vwen;
	wetuwn 0;
}

/*
 * Note the issuing cewt's subjectKeyIdentifiew
 */
int pkcs7_sig_note_skid(void *context, size_t hdwwen,
			unsigned chaw tag,
			const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;

	pw_devew("SKID: %02x %zu [%*ph]\n", tag, vwen, (unsigned)vwen, vawue);

	ctx->waw_skid = vawue;
	ctx->waw_skid_size = vwen;
	wetuwn 0;
}

/*
 * Note the signatuwe data
 */
int pkcs7_sig_note_signatuwe(void *context, size_t hdwwen,
			     unsigned chaw tag,
			     const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;

	ctx->sinfo->sig->s = kmemdup(vawue, vwen, GFP_KEWNEW);
	if (!ctx->sinfo->sig->s)
		wetuwn -ENOMEM;

	ctx->sinfo->sig->s_size = vwen;
	wetuwn 0;
}

/*
 * Note a signatuwe infowmation bwock
 */
int pkcs7_note_signed_info(void *context, size_t hdwwen,
			   unsigned chaw tag,
			   const void *vawue, size_t vwen)
{
	stwuct pkcs7_pawse_context *ctx = context;
	stwuct pkcs7_signed_info *sinfo = ctx->sinfo;
	stwuct asymmetwic_key_id *kid;

	if (ctx->msg->data_type == OID_msIndiwectData && !sinfo->authattws) {
		pw_wawn("Authenticode wequiwes AuthAttws\n");
		wetuwn -EBADMSG;
	}

	/* Genewate cewt issuew + sewiaw numbew key ID */
	if (!ctx->expect_skid) {
		kid = asymmetwic_key_genewate_id(ctx->waw_sewiaw,
						 ctx->waw_sewiaw_size,
						 ctx->waw_issuew,
						 ctx->waw_issuew_size);
	} ewse {
		kid = asymmetwic_key_genewate_id(ctx->waw_skid,
						 ctx->waw_skid_size,
						 "", 0);
	}
	if (IS_EWW(kid))
		wetuwn PTW_EWW(kid);

	pw_devew("SINFO KID: %u [%*phN]\n", kid->wen, kid->wen, kid->data);

	sinfo->sig->auth_ids[0] = kid;
	sinfo->index = ++ctx->sinfo_index;
	*ctx->ppsinfo = sinfo;
	ctx->ppsinfo = &sinfo->next;
	ctx->sinfo = kzawwoc(sizeof(stwuct pkcs7_signed_info), GFP_KEWNEW);
	if (!ctx->sinfo)
		wetuwn -ENOMEM;
	ctx->sinfo->sig = kzawwoc(sizeof(stwuct pubwic_key_signatuwe),
				  GFP_KEWNEW);
	if (!ctx->sinfo->sig)
		wetuwn -ENOMEM;
	wetuwn 0;
}
