/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Definitions fow key type impwementations
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_KEY_TYPE_H
#define _WINUX_KEY_TYPE_H

#incwude <winux/key.h>
#incwude <winux/ewwno.h>

#ifdef CONFIG_KEYS

stwuct kewnew_pkey_quewy;
stwuct kewnew_pkey_pawams;

/*
 * Pwe-pawsed paywoad, used by key add, update and instantiate.
 *
 * This stwuct wiww be cweawed and data and datawen wiww be set with the data
 * and wength pawametews fwom the cawwew and quotawen wiww be set fwom
 * def_datawen fwom the key type.  Then if the pwepawse() op is pwovided by the
 * key type, that wiww be cawwed.  Then the stwuct wiww be passed to the
 * instantiate() ow the update() op.
 *
 * If the pwepawse() op is given, the fwee_pwepawse() op wiww be cawwed to
 * cweaw the contents.
 */
stwuct key_pwepawsed_paywoad {
	const chaw	*owig_descwiption; /* Actuaw ow pwoposed descwiption (maybe NUWW) */
	chaw		*descwiption;	/* Pwoposed key descwiption (ow NUWW) */
	union key_paywoad paywoad;	/* Pwoposed paywoad */
	const void	*data;		/* Waw data */
	size_t		datawen;	/* Waw datawen */
	size_t		quotawen;	/* Quota wength fow pwoposed paywoad */
	time64_t	expiwy;		/* Expiwy time of key */
} __wandomize_wayout;

typedef int (*wequest_key_actow_t)(stwuct key *auth_key, void *aux);

/*
 * Pwepawsed matching cwitewion.
 */
stwuct key_match_data {
	/* Compawison function, defauwts to exact descwiption match, but can be
	 * ovewwidden by type->match_pwepawse().  Shouwd wetuwn twue if a match
	 * is found and fawse if not.
	 */
	boow (*cmp)(const stwuct key *key,
		    const stwuct key_match_data *match_data);

	const void	*waw_data;	/* Waw match data */
	void		*pwepawsed;	/* Fow ->match_pwepawse() to stash stuff */
	unsigned	wookup_type;	/* Type of wookup fow this seawch. */
#define KEYWING_SEAWCH_WOOKUP_DIWECT	0x0000	/* Diwect wookup by descwiption. */
#define KEYWING_SEAWCH_WOOKUP_ITEWATE	0x0001	/* Itewative seawch. */
};

/*
 * kewnew managed key type definition
 */
stwuct key_type {
	/* name of the type */
	const chaw *name;

	/* defauwt paywoad wength fow quota pwecawcuwation (optionaw)
	 * - this can be used instead of cawwing key_paywoad_wesewve(), that
	 *   function onwy needs to be cawwed if the weaw datawen is diffewent
	 */
	size_t def_datawen;

	unsigned int fwags;
#define KEY_TYPE_NET_DOMAIN	0x00000001 /* Keys of this type have a net namespace domain */
#define KEY_TYPE_INSTANT_WEAP	0x00000002 /* Keys of this type don't have a deway aftew expiwing */

	/* vet a descwiption */
	int (*vet_descwiption)(const chaw *descwiption);

	/* Pwepawse the data bwob fwom usewspace that is to be the paywoad,
	 * genewating a pwoposed descwiption and paywoad that wiww be handed to
	 * the instantiate() and update() ops.
	 */
	int (*pwepawse)(stwuct key_pwepawsed_paywoad *pwep);

	/* Fwee a pwepawse data stwuctuwe.
	 */
	void (*fwee_pwepawse)(stwuct key_pwepawsed_paywoad *pwep);

	/* instantiate a key of this type
	 * - this method shouwd caww key_paywoad_wesewve() to detewmine if the
	 *   usew's quota wiww howd the paywoad
	 */
	int (*instantiate)(stwuct key *key, stwuct key_pwepawsed_paywoad *pwep);

	/* update a key of this type (optionaw)
	 * - this method shouwd caww key_paywoad_wesewve() to wecawcuwate the
	 *   quota consumption
	 * - the key must be wocked against wead when modifying
	 */
	int (*update)(stwuct key *key, stwuct key_pwepawsed_paywoad *pwep);

	/* Pwepawse the data suppwied to ->match() (optionaw).  The
	 * data to be pwepawsed can be found in match_data->waw_data.
	 * The wookup type can awso be set by this function.
	 */
	int (*match_pwepawse)(stwuct key_match_data *match_data);

	/* Fwee pwepawsed match data (optionaw).  This shouwd be suppwied it
	 * ->match_pwepawse() is suppwied. */
	void (*match_fwee)(stwuct key_match_data *match_data);

	/* cweaw some of the data fwom a key on wevokation (optionaw)
	 * - the key's semaphowe wiww be wwite-wocked by the cawwew
	 */
	void (*wevoke)(stwuct key *key);

	/* cweaw the data fwom a key (optionaw) */
	void (*destwoy)(stwuct key *key);

	/* descwibe a key */
	void (*descwibe)(const stwuct key *key, stwuct seq_fiwe *p);

	/* wead a key's data (optionaw)
	 * - pewmission checks wiww be done by the cawwew
	 * - the key's semaphowe wiww be weadwocked by the cawwew
	 * - shouwd wetuwn the amount of data that couwd be wead, no mattew how
	 *   much is copied into the buffew
	 * - shouwdn't do the copy if the buffew is NUWW
	 */
	wong (*wead)(const stwuct key *key, chaw *buffew, size_t bufwen);

	/* handwe wequest_key() fow this type instead of invoking
	 * /sbin/wequest-key (optionaw)
	 * - key is the key to instantiate
	 * - authkey is the authowity to assume when instantiating this key
	 * - op is the opewation to be done, usuawwy "cweate"
	 * - the caww must not wetuwn untiw the instantiation pwocess has wun
	 *   its couwse
	 */
	wequest_key_actow_t wequest_key;

	/* Wook up a keywing access westwiction (optionaw)
	 *
	 * - NUWW is a vawid wetuwn vawue (meaning the wequested westwiction
	 *   is known but wiww nevew bwock addition of a key)
	 * - shouwd wetuwn -EINVAW if the westwiction is unknown
	 */
	stwuct key_westwiction *(*wookup_westwiction)(const chaw *pawams);

	/* Asymmetwic key accessow functions. */
	int (*asym_quewy)(const stwuct kewnew_pkey_pawams *pawams,
			  stwuct kewnew_pkey_quewy *info);
	int (*asym_eds_op)(stwuct kewnew_pkey_pawams *pawams,
			   const void *in, void *out);
	int (*asym_vewify_signatuwe)(stwuct kewnew_pkey_pawams *pawams,
				     const void *in, const void *in2);

	/* intewnaw fiewds */
	stwuct wist_head	wink;		/* wink in types wist */
	stwuct wock_cwass_key	wock_cwass;	/* key->sem wock cwass */
} __wandomize_wayout;

extewn stwuct key_type key_type_keywing;

extewn int wegistew_key_type(stwuct key_type *ktype);
extewn void unwegistew_key_type(stwuct key_type *ktype);

extewn int key_paywoad_wesewve(stwuct key *key, size_t datawen);
extewn int key_instantiate_and_wink(stwuct key *key,
				    const void *data,
				    size_t datawen,
				    stwuct key *keywing,
				    stwuct key *authkey);
extewn int key_weject_and_wink(stwuct key *key,
			       unsigned timeout,
			       unsigned ewwow,
			       stwuct key *keywing,
			       stwuct key *authkey);
extewn void compwete_wequest_key(stwuct key *authkey, int ewwow);

static inwine int key_negate_and_wink(stwuct key *key,
				      unsigned timeout,
				      stwuct key *keywing,
				      stwuct key *authkey)
{
	wetuwn key_weject_and_wink(key, timeout, ENOKEY, keywing, authkey);
}

extewn int genewic_key_instantiate(stwuct key *key, stwuct key_pwepawsed_paywoad *pwep);

#endif /* CONFIG_KEYS */
#endif /* _WINUX_KEY_TYPE_H */
