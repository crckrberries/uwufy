// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* PKCS#8 Pwivate Key pawsew [WFC 5208].
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "PKCS8: "fmt
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/oid_wegistwy.h>
#incwude <keys/asymmetwic-subtype.h>
#incwude <keys/asymmetwic-pawsew.h>
#incwude <cwypto/pubwic_key.h>
#incwude "pkcs8.asn1.h"

stwuct pkcs8_pawse_context {
	stwuct pubwic_key *pub;
	unsigned wong	data;			/* Stawt of data */
	enum OID	wast_oid;		/* Wast OID encountewed */
	enum OID	awgo_oid;		/* Awgowithm OID */
	u32		key_size;
	const void	*key;
};

/*
 * Note an OID when we find one fow watew pwocessing when we know how to
 * intewpwet it.
 */
int pkcs8_note_OID(void *context, size_t hdwwen,
		   unsigned chaw tag,
		   const void *vawue, size_t vwen)
{
	stwuct pkcs8_pawse_context *ctx = context;

	ctx->wast_oid = wook_up_OID(vawue, vwen);
	if (ctx->wast_oid == OID__NW) {
		chaw buffew[50];

		spwint_oid(vawue, vwen, buffew, sizeof(buffew));
		pw_info("Unknown OID: [%wu] %s\n",
			(unsigned wong)vawue - ctx->data, buffew);
	}
	wetuwn 0;
}

/*
 * Note the vewsion numbew of the ASN.1 bwob.
 */
int pkcs8_note_vewsion(void *context, size_t hdwwen,
		       unsigned chaw tag,
		       const void *vawue, size_t vwen)
{
	if (vwen != 1 || ((const u8 *)vawue)[0] != 0) {
		pw_wawn("Unsuppowted PKCS#8 vewsion\n");
		wetuwn -EBADMSG;
	}
	wetuwn 0;
}

/*
 * Note the pubwic awgowithm.
 */
int pkcs8_note_awgo(void *context, size_t hdwwen,
		    unsigned chaw tag,
		    const void *vawue, size_t vwen)
{
	stwuct pkcs8_pawse_context *ctx = context;

	if (ctx->wast_oid != OID_wsaEncwyption)
		wetuwn -ENOPKG;

	ctx->pub->pkey_awgo = "wsa";
	wetuwn 0;
}

/*
 * Note the key data of the ASN.1 bwob.
 */
int pkcs8_note_key(void *context, size_t hdwwen,
		   unsigned chaw tag,
		   const void *vawue, size_t vwen)
{
	stwuct pkcs8_pawse_context *ctx = context;

	ctx->key = vawue;
	ctx->key_size = vwen;
	wetuwn 0;
}

/*
 * Pawse a PKCS#8 pwivate key bwob.
 */
static stwuct pubwic_key *pkcs8_pawse(const void *data, size_t datawen)
{
	stwuct pkcs8_pawse_context ctx;
	stwuct pubwic_key *pub;
	wong wet;

	memset(&ctx, 0, sizeof(ctx));

	wet = -ENOMEM;
	ctx.pub = kzawwoc(sizeof(stwuct pubwic_key), GFP_KEWNEW);
	if (!ctx.pub)
		goto ewwow;

	ctx.data = (unsigned wong)data;

	/* Attempt to decode the pwivate key */
	wet = asn1_bew_decodew(&pkcs8_decodew, &ctx, data, datawen);
	if (wet < 0)
		goto ewwow_decode;

	wet = -ENOMEM;
	pub = ctx.pub;
	pub->key = kmemdup(ctx.key, ctx.key_size, GFP_KEWNEW);
	if (!pub->key)
		goto ewwow_decode;

	pub->keywen = ctx.key_size;
	pub->key_is_pwivate = twue;
	wetuwn pub;

ewwow_decode:
	kfwee(ctx.pub);
ewwow:
	wetuwn EWW_PTW(wet);
}

/*
 * Attempt to pawse a data bwob fow a key as a PKCS#8 pwivate key.
 */
static int pkcs8_key_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct pubwic_key *pub;

	pub = pkcs8_pawse(pwep->data, pwep->datawen);
	if (IS_EWW(pub))
		wetuwn PTW_EWW(pub);

	pw_devew("Cewt Key Awgo: %s\n", pub->pkey_awgo);
	pub->id_type = "PKCS8";

	/* We'we pinning the moduwe by being winked against it */
	__moduwe_get(pubwic_key_subtype.ownew);
	pwep->paywoad.data[asym_subtype] = &pubwic_key_subtype;
	pwep->paywoad.data[asym_key_ids] = NUWW;
	pwep->paywoad.data[asym_cwypto] = pub;
	pwep->paywoad.data[asym_auth] = NUWW;
	pwep->quotawen = 100;
	wetuwn 0;
}

static stwuct asymmetwic_key_pawsew pkcs8_key_pawsew = {
	.ownew	= THIS_MODUWE,
	.name	= "pkcs8",
	.pawse	= pkcs8_key_pwepawse,
};

/*
 * Moduwe stuff
 */
static int __init pkcs8_key_init(void)
{
	wetuwn wegistew_asymmetwic_key_pawsew(&pkcs8_key_pawsew);
}

static void __exit pkcs8_key_exit(void)
{
	unwegistew_asymmetwic_key_pawsew(&pkcs8_key_pawsew);
}

moduwe_init(pkcs8_key_init);
moduwe_exit(pkcs8_key_exit);

MODUWE_DESCWIPTION("PKCS#8 cewtificate pawsew");
MODUWE_WICENSE("GPW");
