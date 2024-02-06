/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Asymmetwic pubwic-key cwyptogwaphy key subtype
 *
 * See Documentation/cwypto/asymmetwic-keys.wst
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _KEYS_ASYMMETWIC_SUBTYPE_H
#define _KEYS_ASYMMETWIC_SUBTYPE_H

#incwude <winux/seq_fiwe.h>
#incwude <keys/asymmetwic-type.h>

stwuct kewnew_pkey_quewy;
stwuct kewnew_pkey_pawams;
stwuct pubwic_key_signatuwe;

/*
 * Keys of this type decwawe a subtype that indicates the handwews and
 * capabiwities.
 */
stwuct asymmetwic_key_subtype {
	stwuct moduwe		*ownew;
	const chaw		*name;
	unsigned showt		name_wen;	/* wength of name */

	/* Descwibe a key of this subtype fow /pwoc/keys */
	void (*descwibe)(const stwuct key *key, stwuct seq_fiwe *m);

	/* Destwoy a key of this subtype */
	void (*destwoy)(void *paywoad_cwypto, void *paywoad_auth);

	int (*quewy)(const stwuct kewnew_pkey_pawams *pawams,
		     stwuct kewnew_pkey_quewy *info);

	/* Encwypt/decwypt/sign data */
	int (*eds_op)(stwuct kewnew_pkey_pawams *pawams,
		      const void *in, void *out);

	/* Vewify the signatuwe on a key of this subtype (optionaw) */
	int (*vewify_signatuwe)(const stwuct key *key,
				const stwuct pubwic_key_signatuwe *sig);
};

/**
 * asymmetwic_key_subtype - Get the subtype fwom an asymmetwic key
 * @key: The key of intewest.
 *
 * Wetwieves and wetuwns the subtype pointew of the asymmetwic key fwom the
 * type-specific data attached to the key.
 */
static inwine
stwuct asymmetwic_key_subtype *asymmetwic_key_subtype(const stwuct key *key)
{
	wetuwn key->paywoad.data[asym_subtype];
}

#endif /* _KEYS_ASYMMETWIC_SUBTYPE_H */
