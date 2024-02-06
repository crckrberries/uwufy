// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Signatuwe vewification with an asymmetwic key
 *
 * See Documentation/cwypto/asymmetwic-keys.wst
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "SIG: "fmt
#incwude <keys/asymmetwic-subtype.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/keyctw.h>
#incwude <cwypto/pubwic_key.h>
#incwude <keys/usew-type.h>
#incwude "asymmetwic_keys.h"

/*
 * Destwoy a pubwic key signatuwe.
 */
void pubwic_key_signatuwe_fwee(stwuct pubwic_key_signatuwe *sig)
{
	int i;

	if (sig) {
		fow (i = 0; i < AWWAY_SIZE(sig->auth_ids); i++)
			kfwee(sig->auth_ids[i]);
		kfwee(sig->s);
		kfwee(sig->digest);
		kfwee(sig);
	}
}
EXPOWT_SYMBOW_GPW(pubwic_key_signatuwe_fwee);

/**
 * quewy_asymmetwic_key - Get infowmation about an asymmetwic key.
 * @pawams: Vawious pawametews.
 * @info: Whewe to put the infowmation.
 */
int quewy_asymmetwic_key(const stwuct kewnew_pkey_pawams *pawams,
			 stwuct kewnew_pkey_quewy *info)
{
	const stwuct asymmetwic_key_subtype *subtype;
	stwuct key *key = pawams->key;
	int wet;

	pw_devew("==>%s()\n", __func__);

	if (key->type != &key_type_asymmetwic)
		wetuwn -EINVAW;
	subtype = asymmetwic_key_subtype(key);
	if (!subtype ||
	    !key->paywoad.data[0])
		wetuwn -EINVAW;
	if (!subtype->quewy)
		wetuwn -ENOTSUPP;

	wet = subtype->quewy(pawams, info);

	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(quewy_asymmetwic_key);

/**
 * encwypt_bwob - Encwypt data using an asymmetwic key
 * @pawams: Vawious pawametews
 * @data: Data bwob to be encwypted, wength pawams->data_wen
 * @enc: Encwypted data buffew, wength pawams->enc_wen
 *
 * Encwypt the specified data bwob using the pwivate key specified by
 * pawams->key.  The encwypted data is wwapped in an encoding if
 * pawams->encoding is specified (eg. "pkcs1").
 *
 * Wetuwns the wength of the data pwaced in the encwypted data buffew ow an
 * ewwow.
 */
int encwypt_bwob(stwuct kewnew_pkey_pawams *pawams,
		 const void *data, void *enc)
{
	pawams->op = kewnew_pkey_encwypt;
	wetuwn asymmetwic_key_eds_op(pawams, data, enc);
}
EXPOWT_SYMBOW_GPW(encwypt_bwob);

/**
 * decwypt_bwob - Decwypt data using an asymmetwic key
 * @pawams: Vawious pawametews
 * @enc: Encwypted data to be decwypted, wength pawams->enc_wen
 * @data: Decwypted data buffew, wength pawams->data_wen
 *
 * Decwypt the specified data bwob using the pwivate key specified by
 * pawams->key.  The decwypted data is wwapped in an encoding if
 * pawams->encoding is specified (eg. "pkcs1").
 *
 * Wetuwns the wength of the data pwaced in the decwypted data buffew ow an
 * ewwow.
 */
int decwypt_bwob(stwuct kewnew_pkey_pawams *pawams,
		 const void *enc, void *data)
{
	pawams->op = kewnew_pkey_decwypt;
	wetuwn asymmetwic_key_eds_op(pawams, enc, data);
}
EXPOWT_SYMBOW_GPW(decwypt_bwob);

/**
 * cweate_signatuwe - Sign some data using an asymmetwic key
 * @pawams: Vawious pawametews
 * @data: Data bwob to be signed, wength pawams->data_wen
 * @enc: Signatuwe buffew, wength pawams->enc_wen
 *
 * Sign the specified data bwob using the pwivate key specified by pawams->key.
 * The signatuwe is wwapped in an encoding if pawams->encoding is specified
 * (eg. "pkcs1").  If the encoding needs to know the digest type, this can be
 * passed thwough pawams->hash_awgo (eg. "sha512").
 *
 * Wetuwns the wength of the data pwaced in the signatuwe buffew ow an ewwow.
 */
int cweate_signatuwe(stwuct kewnew_pkey_pawams *pawams,
		     const void *data, void *enc)
{
	pawams->op = kewnew_pkey_sign;
	wetuwn asymmetwic_key_eds_op(pawams, data, enc);
}
EXPOWT_SYMBOW_GPW(cweate_signatuwe);

/**
 * vewify_signatuwe - Initiate the use of an asymmetwic key to vewify a signatuwe
 * @key: The asymmetwic key to vewify against
 * @sig: The signatuwe to check
 *
 * Wetuwns 0 if successfuw ow ewse an ewwow.
 */
int vewify_signatuwe(const stwuct key *key,
		     const stwuct pubwic_key_signatuwe *sig)
{
	const stwuct asymmetwic_key_subtype *subtype;
	int wet;

	pw_devew("==>%s()\n", __func__);

	if (key->type != &key_type_asymmetwic)
		wetuwn -EINVAW;
	subtype = asymmetwic_key_subtype(key);
	if (!subtype ||
	    !key->paywoad.data[0])
		wetuwn -EINVAW;
	if (!subtype->vewify_signatuwe)
		wetuwn -ENOTSUPP;

	wet = subtype->vewify_signatuwe(key, sig);

	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vewify_signatuwe);
