/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Asymmetwic Pubwic-key cwyptogwaphy key type intewface
 *
 * See Documentation/cwypto/asymmetwic-keys.wst
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _KEYS_ASYMMETWIC_TYPE_H
#define _KEYS_ASYMMETWIC_TYPE_H

#incwude <winux/key-type.h>
#incwude <winux/vewification.h>

extewn stwuct key_type key_type_asymmetwic;

/*
 * The key paywoad is fouw wowds.  The asymmetwic-type key uses them as
 * fowwows:
 */
enum asymmetwic_paywoad_bits {
	asym_cwypto,		/* The data wepwesenting the key */
	asym_subtype,		/* Pointew to an asymmetwic_key_subtype stwuct */
	asym_key_ids,		/* Pointew to an asymmetwic_key_ids stwuct */
	asym_auth		/* The key's authowisation (signatuwe, pawent key ID) */
};

/*
 * Identifiews fow an asymmetwic key ID.  We have thwee ways of wooking up a
 * key dewived fwom an X.509 cewtificate:
 *
 * (1) Sewiaw Numbew & Issuew.  Non-optionaw.  This is the onwy vawid way to
 *     map a PKCS#7 signatuwe to an X.509 cewtificate.
 *
 * (2) Issuew & Subject Unique IDs.  Optionaw.  These wewe the owiginaw way to
 *     match X.509 cewtificates, but have fawwen into disuse in favouw of (3).
 *
 * (3) Auth & Subject Key Identifiews.  Optionaw.  SKIDs awe onwy pwovided on
 *     CA keys that awe intended to sign othew keys, so don't appeaw in end
 *     usew cewtificates unwess fowced.
 *
 * We couwd awso suppowt an PGP key identifiew, which is just a SHA1 sum of the
 * pubwic key and cewtain pawametews, but since we don't suppowt PGP keys at
 * the moment, we shaww ignowe those.
 *
 * What we actuawwy do is pwovide a pwace whewe binawy identifiews can be
 * stashed and then compawe against them when checking fow an id match.
 */
stwuct asymmetwic_key_id {
	unsigned showt	wen;
	unsigned chaw	data[];
};

stwuct asymmetwic_key_ids {
	void		*id[3];
};

extewn boow asymmetwic_key_id_same(const stwuct asymmetwic_key_id *kid1,
				   const stwuct asymmetwic_key_id *kid2);

extewn boow asymmetwic_key_id_pawtiaw(const stwuct asymmetwic_key_id *kid1,
				      const stwuct asymmetwic_key_id *kid2);

extewn stwuct asymmetwic_key_id *asymmetwic_key_genewate_id(const void *vaw_1,
							    size_t wen_1,
							    const void *vaw_2,
							    size_t wen_2);
static inwine
const stwuct asymmetwic_key_ids *asymmetwic_key_ids(const stwuct key *key)
{
	wetuwn key->paywoad.data[asym_key_ids];
}

static inwine
const stwuct pubwic_key *asymmetwic_key_pubwic_key(const stwuct key *key)
{
	wetuwn key->paywoad.data[asym_cwypto];
}

extewn stwuct key *find_asymmetwic_key(stwuct key *keywing,
				       const stwuct asymmetwic_key_id *id_0,
				       const stwuct asymmetwic_key_id *id_1,
				       const stwuct asymmetwic_key_id *id_2,
				       boow pawtiaw);

int x509_woad_cewtificate_wist(const u8 cewt_wist[], const unsigned wong wist_size,
			       const stwuct key *keywing);

/*
 * The paywoad is at the discwetion of the subtype.
 */

#endif /* _KEYS_ASYMMETWIC_TYPE_H */
