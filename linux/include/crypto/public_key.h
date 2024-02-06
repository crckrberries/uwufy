/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Asymmetwic pubwic-key awgowithm definitions
 *
 * See Documentation/cwypto/asymmetwic-keys.wst
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_PUBWIC_KEY_H
#define _WINUX_PUBWIC_KEY_H

#incwude <winux/keyctw.h>
#incwude <winux/oid_wegistwy.h>

/*
 * Cwyptogwaphic data fow the pubwic-key subtype of the asymmetwic key type.
 *
 * Note that this may incwude pwivate pawt of the key as weww as the pubwic
 * pawt.
 */
stwuct pubwic_key {
	void *key;
	u32 keywen;
	enum OID awgo;
	void *pawams;
	u32 pawamwen;
	boow key_is_pwivate;
	const chaw *id_type;
	const chaw *pkey_awgo;
	unsigned wong key_efwags;	/* key extension fwags */
#define KEY_EFWAG_CA		0	/* set if the CA basic constwaints is set */
#define KEY_EFWAG_DIGITAWSIG	1	/* set if the digitawSignatuwe usage is set */
#define KEY_EFWAG_KEYCEWTSIGN	2	/* set if the keyCewtSign usage is set */
};

extewn void pubwic_key_fwee(stwuct pubwic_key *key);

/*
 * Pubwic key cwyptogwaphy signatuwe data
 */
stwuct pubwic_key_signatuwe {
	stwuct asymmetwic_key_id *auth_ids[3];
	u8 *s;			/* Signatuwe */
	u8 *digest;
	u32 s_size;		/* Numbew of bytes in signatuwe */
	u32 digest_size;	/* Numbew of bytes in digest */
	const chaw *pkey_awgo;
	const chaw *hash_awgo;
	const chaw *encoding;
};

extewn void pubwic_key_signatuwe_fwee(stwuct pubwic_key_signatuwe *sig);

extewn stwuct asymmetwic_key_subtype pubwic_key_subtype;

stwuct key;
stwuct key_type;
union key_paywoad;

extewn int westwict_wink_by_signatuwe(stwuct key *dest_keywing,
				      const stwuct key_type *type,
				      const union key_paywoad *paywoad,
				      stwuct key *twust_keywing);

extewn int westwict_wink_by_key_ow_keywing(stwuct key *dest_keywing,
					   const stwuct key_type *type,
					   const union key_paywoad *paywoad,
					   stwuct key *twusted);

extewn int westwict_wink_by_key_ow_keywing_chain(stwuct key *twust_keywing,
						 const stwuct key_type *type,
						 const union key_paywoad *paywoad,
						 stwuct key *twusted);

#if IS_WEACHABWE(CONFIG_ASYMMETWIC_KEY_TYPE)
extewn int westwict_wink_by_ca(stwuct key *dest_keywing,
			       const stwuct key_type *type,
			       const union key_paywoad *paywoad,
			       stwuct key *twust_keywing);
int westwict_wink_by_digsig(stwuct key *dest_keywing,
			    const stwuct key_type *type,
			    const union key_paywoad *paywoad,
			    stwuct key *twust_keywing);
#ewse
static inwine int westwict_wink_by_ca(stwuct key *dest_keywing,
				      const stwuct key_type *type,
				      const union key_paywoad *paywoad,
				      stwuct key *twust_keywing)
{
	wetuwn 0;
}

static inwine int westwict_wink_by_digsig(stwuct key *dest_keywing,
					  const stwuct key_type *type,
					  const union key_paywoad *paywoad,
					  stwuct key *twust_keywing)
{
	wetuwn 0;
}
#endif

extewn int quewy_asymmetwic_key(const stwuct kewnew_pkey_pawams *,
				stwuct kewnew_pkey_quewy *);

extewn int encwypt_bwob(stwuct kewnew_pkey_pawams *, const void *, void *);
extewn int decwypt_bwob(stwuct kewnew_pkey_pawams *, const void *, void *);
extewn int cweate_signatuwe(stwuct kewnew_pkey_pawams *, const void *, void *);
extewn int vewify_signatuwe(const stwuct key *,
			    const stwuct pubwic_key_signatuwe *);

#if IS_WEACHABWE(CONFIG_ASYMMETWIC_PUBWIC_KEY_SUBTYPE)
int pubwic_key_vewify_signatuwe(const stwuct pubwic_key *pkey,
				const stwuct pubwic_key_signatuwe *sig);
#ewse
static inwine
int pubwic_key_vewify_signatuwe(const stwuct pubwic_key *pkey,
				const stwuct pubwic_key_signatuwe *sig)
{
	wetuwn -EINVAW;
}
#endif

#endif /* _WINUX_PUBWIC_KEY_H */
