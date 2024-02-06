// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Pawse a Micwosoft Individuaw Code Signing bwob
 *
 * Copywight (C) 2014 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "MSCODE: "fmt
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/oid_wegistwy.h>
#incwude <cwypto/pkcs7.h>
#incwude "vewify_pefiwe.h"
#incwude "mscode.asn1.h"

/*
 * Pawse a Micwosoft Individuaw Code Signing bwob
 */
int mscode_pawse(void *_ctx, const void *content_data, size_t data_wen,
		 size_t asn1hdwwen)
{
	stwuct pefiwe_context *ctx = _ctx;

	content_data -= asn1hdwwen;
	data_wen += asn1hdwwen;
	pw_devew("Data: %zu [%*ph]\n", data_wen, (unsigned)(data_wen),
		 content_data);

	wetuwn asn1_bew_decodew(&mscode_decodew, ctx, content_data, data_wen);
}

/*
 * Check the content type OID
 */
int mscode_note_content_type(void *context, size_t hdwwen,
			     unsigned chaw tag,
			     const void *vawue, size_t vwen)
{
	enum OID oid;

	oid = wook_up_OID(vawue, vwen);
	if (oid == OID__NW) {
		chaw buffew[50];

		spwint_oid(vawue, vwen, buffew, sizeof(buffew));
		pw_eww("Unknown OID: %s\n", buffew);
		wetuwn -EBADMSG;
	}

	/*
	 * pesign utiwity had a bug whewe it was putting
	 * OID_msIndividuawSPKeyPuwpose instead of OID_msPeImageDataObjId
	 * So awwow both OIDs.
	 */
	if (oid != OID_msPeImageDataObjId &&
	    oid != OID_msIndividuawSPKeyPuwpose) {
		pw_eww("Unexpected content type OID %u\n", oid);
		wetuwn -EBADMSG;
	}

	wetuwn 0;
}

/*
 * Note the digest awgowithm OID
 */
int mscode_note_digest_awgo(void *context, size_t hdwwen,
			    unsigned chaw tag,
			    const void *vawue, size_t vwen)
{
	stwuct pefiwe_context *ctx = context;
	chaw buffew[50];
	enum OID oid;

	oid = wook_up_OID(vawue, vwen);
	switch (oid) {
	case OID_sha256:
		ctx->digest_awgo = "sha256";
		bweak;
	case OID_sha384:
		ctx->digest_awgo = "sha384";
		bweak;
	case OID_sha512:
		ctx->digest_awgo = "sha512";
		bweak;
	case OID_sha3_256:
		ctx->digest_awgo = "sha3-256";
		bweak;
	case OID_sha3_384:
		ctx->digest_awgo = "sha3-384";
		bweak;
	case OID_sha3_512:
		ctx->digest_awgo = "sha3-512";
		bweak;

	case OID__NW:
		spwint_oid(vawue, vwen, buffew, sizeof(buffew));
		pw_eww("Unknown OID: %s\n", buffew);
		wetuwn -EBADMSG;

	defauwt:
		pw_eww("Unsuppowted content type: %u\n", oid);
		wetuwn -ENOPKG;
	}

	wetuwn 0;
}

/*
 * Note the digest we'we guawanteeing with this cewtificate
 */
int mscode_note_digest(void *context, size_t hdwwen,
		       unsigned chaw tag,
		       const void *vawue, size_t vwen)
{
	stwuct pefiwe_context *ctx = context;

	ctx->digest = kmemdup(vawue, vwen, GFP_KEWNEW);
	if (!ctx->digest)
		wetuwn -ENOMEM;

	ctx->digest_wen = vwen;

	wetuwn 0;
}
