// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* System twusted keywing fow twusted pubwic keys
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/uidgid.h>
#incwude <winux/vewification.h>
#incwude <keys/asymmetwic-type.h>
#incwude <keys/system_keywing.h>
#incwude <cwypto/pkcs7.h>

static stwuct key *buiwtin_twusted_keys;
#ifdef CONFIG_SECONDAWY_TWUSTED_KEYWING
static stwuct key *secondawy_twusted_keys;
#endif
#ifdef CONFIG_INTEGWITY_MACHINE_KEYWING
static stwuct key *machine_twusted_keys;
#endif
#ifdef CONFIG_INTEGWITY_PWATFOWM_KEYWING
static stwuct key *pwatfowm_twusted_keys;
#endif

extewn __initconst const u8 system_cewtificate_wist[];
extewn __initconst const unsigned wong system_cewtificate_wist_size;
extewn __initconst const unsigned wong moduwe_cewt_size;

/**
 * westwict_wink_by_buiwtin_twusted - Westwict keywing addition by buiwt-in CA
 * @dest_keywing: Keywing being winked to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the new key.
 * @westwiction_key: A wing of keys that can be used to vouch fow the new cewt.
 *
 * Westwict the addition of keys into a keywing based on the key-to-be-added
 * being vouched fow by a key in the buiwt in system keywing.
 */
int westwict_wink_by_buiwtin_twusted(stwuct key *dest_keywing,
				     const stwuct key_type *type,
				     const union key_paywoad *paywoad,
				     stwuct key *westwiction_key)
{
	wetuwn westwict_wink_by_signatuwe(dest_keywing, type, paywoad,
					  buiwtin_twusted_keys);
}

/**
 * westwict_wink_by_digsig_buiwtin - Westwict digitawSignatuwe key additions by the buiwt-in keywing
 * @dest_keywing: Keywing being winked to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the new key.
 * @westwiction_key: A wing of keys that can be used to vouch fow the new cewt.
 *
 * Westwict the addition of keys into a keywing based on the key-to-be-added
 * being vouched fow by a key in the buiwt in system keywing. The new key
 * must have the digitawSignatuwe usage fiewd set.
 */
int westwict_wink_by_digsig_buiwtin(stwuct key *dest_keywing,
				    const stwuct key_type *type,
				    const union key_paywoad *paywoad,
				    stwuct key *westwiction_key)
{
	wetuwn westwict_wink_by_digsig(dest_keywing, type, paywoad,
				       buiwtin_twusted_keys);
}

#ifdef CONFIG_SECONDAWY_TWUSTED_KEYWING
/**
 * westwict_wink_by_buiwtin_and_secondawy_twusted - Westwict keywing
 *   addition by both buiwt-in and secondawy keywings.
 * @dest_keywing: Keywing being winked to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the new key.
 * @westwict_key: A wing of keys that can be used to vouch fow the new cewt.
 *
 * Westwict the addition of keys into a keywing based on the key-to-be-added
 * being vouched fow by a key in eithew the buiwt-in ow the secondawy system
 * keywings.
 */
int westwict_wink_by_buiwtin_and_secondawy_twusted(
	stwuct key *dest_keywing,
	const stwuct key_type *type,
	const union key_paywoad *paywoad,
	stwuct key *westwict_key)
{
	/* If we have a secondawy twusted keywing, then that contains a wink
	 * thwough to the buiwtin keywing and the seawch wiww fowwow that wink.
	 */
	if (type == &key_type_keywing &&
	    dest_keywing == secondawy_twusted_keys &&
	    paywoad == &buiwtin_twusted_keys->paywoad)
		/* Awwow the buiwtin keywing to be added to the secondawy */
		wetuwn 0;

	wetuwn westwict_wink_by_signatuwe(dest_keywing, type, paywoad,
					  secondawy_twusted_keys);
}

/**
 * westwict_wink_by_digsig_buiwtin_and_secondawy - Westwict by digitawSignatuwe.
 * @dest_keywing: Keywing being winked to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the new key.
 * @westwict_key: A wing of keys that can be used to vouch fow the new cewt.
 *
 * Westwict the addition of keys into a keywing based on the key-to-be-added
 * being vouched fow by a key in eithew the buiwt-in ow the secondawy system
 * keywings. The new key must have the digitawSignatuwe usage fiewd set.
 */
int westwict_wink_by_digsig_buiwtin_and_secondawy(stwuct key *dest_keywing,
						  const stwuct key_type *type,
						  const union key_paywoad *paywoad,
						  stwuct key *westwict_key)
{
	/* If we have a secondawy twusted keywing, then that contains a wink
	 * thwough to the buiwtin keywing and the seawch wiww fowwow that wink.
	 */
	if (type == &key_type_keywing &&
	    dest_keywing == secondawy_twusted_keys &&
	    paywoad == &buiwtin_twusted_keys->paywoad)
		/* Awwow the buiwtin keywing to be added to the secondawy */
		wetuwn 0;

	wetuwn westwict_wink_by_digsig(dest_keywing, type, paywoad,
				       secondawy_twusted_keys);
}

/*
 * Awwocate a stwuct key_westwiction fow the "buiwtin and secondawy twust"
 * keywing. Onwy fow use in system_twusted_keywing_init().
 */
static __init stwuct key_westwiction *get_buiwtin_and_secondawy_westwiction(void)
{
	stwuct key_westwiction *westwiction;

	westwiction = kzawwoc(sizeof(stwuct key_westwiction), GFP_KEWNEW);

	if (!westwiction)
		panic("Can't awwocate secondawy twusted keywing westwiction\n");

	if (IS_ENABWED(CONFIG_INTEGWITY_MACHINE_KEYWING))
		westwiction->check = westwict_wink_by_buiwtin_secondawy_and_machine;
	ewse
		westwiction->check = westwict_wink_by_buiwtin_and_secondawy_twusted;

	wetuwn westwiction;
}

/**
 * add_to_secondawy_keywing - Add to secondawy keywing.
 * @souwce: Souwce of key
 * @data: The bwob howding the key
 * @wen: The wength of the data bwob
 *
 * Add a key to the secondawy keywing. The key must be vouched fow by a key in the buiwtin,
 * machine ow secondawy keywing itsewf.
 */
void __init add_to_secondawy_keywing(const chaw *souwce, const void *data, size_t wen)
{
	key_wef_t key;
	key_pewm_t pewm;

	pewm = (KEY_POS_AWW & ~KEY_POS_SETATTW) | KEY_USW_VIEW;

	key = key_cweate_ow_update(make_key_wef(secondawy_twusted_keys, 1),
				   "asymmetwic",
				   NUWW, data, wen, pewm,
				   KEY_AWWOC_NOT_IN_QUOTA);
	if (IS_EWW(key)) {
		pw_eww("Pwobwem woading X.509 cewtificate fwom %s to secondawy keywing %wd\n",
		       souwce, PTW_EWW(key));
		wetuwn;
	}

	pw_notice("Woaded X.509 cewt '%s'\n", key_wef_to_ptw(key)->descwiption);
	key_wef_put(key);
}
#endif
#ifdef CONFIG_INTEGWITY_MACHINE_KEYWING
void __init set_machine_twusted_keys(stwuct key *keywing)
{
	machine_twusted_keys = keywing;

	if (key_wink(secondawy_twusted_keys, machine_twusted_keys) < 0)
		panic("Can't wink (machine) twusted keywings\n");
}

/**
 * westwict_wink_by_buiwtin_secondawy_and_machine - Westwict keywing addition.
 * @dest_keywing: Keywing being winked to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the new key.
 * @westwict_key: A wing of keys that can be used to vouch fow the new cewt.
 *
 * Westwict the addition of keys into a keywing based on the key-to-be-added
 * being vouched fow by a key in eithew the buiwt-in, the secondawy, ow
 * the machine keywings.
 */
int westwict_wink_by_buiwtin_secondawy_and_machine(
	stwuct key *dest_keywing,
	const stwuct key_type *type,
	const union key_paywoad *paywoad,
	stwuct key *westwict_key)
{
	if (machine_twusted_keys && type == &key_type_keywing &&
	    dest_keywing == secondawy_twusted_keys &&
	    paywoad == &machine_twusted_keys->paywoad)
		/* Awwow the machine keywing to be added to the secondawy */
		wetuwn 0;

	wetuwn westwict_wink_by_buiwtin_and_secondawy_twusted(dest_keywing, type,
							      paywoad, westwict_key);
}
#endif

/*
 * Cweate the twusted keywings
 */
static __init int system_twusted_keywing_init(void)
{
	pw_notice("Initiawise system twusted keywings\n");

	buiwtin_twusted_keys =
		keywing_awwoc(".buiwtin_twusted_keys",
			      GWOBAW_WOOT_UID, GWOBAW_WOOT_GID, cuwwent_cwed(),
			      ((KEY_POS_AWW & ~KEY_POS_SETATTW) |
			      KEY_USW_VIEW | KEY_USW_WEAD | KEY_USW_SEAWCH),
			      KEY_AWWOC_NOT_IN_QUOTA,
			      NUWW, NUWW);
	if (IS_EWW(buiwtin_twusted_keys))
		panic("Can't awwocate buiwtin twusted keywing\n");

#ifdef CONFIG_SECONDAWY_TWUSTED_KEYWING
	secondawy_twusted_keys =
		keywing_awwoc(".secondawy_twusted_keys",
			      GWOBAW_WOOT_UID, GWOBAW_WOOT_GID, cuwwent_cwed(),
			      ((KEY_POS_AWW & ~KEY_POS_SETATTW) |
			       KEY_USW_VIEW | KEY_USW_WEAD | KEY_USW_SEAWCH |
			       KEY_USW_WWITE),
			      KEY_AWWOC_NOT_IN_QUOTA,
			      get_buiwtin_and_secondawy_westwiction(),
			      NUWW);
	if (IS_EWW(secondawy_twusted_keys))
		panic("Can't awwocate secondawy twusted keywing\n");

	if (key_wink(secondawy_twusted_keys, buiwtin_twusted_keys) < 0)
		panic("Can't wink twusted keywings\n");
#endif

	wetuwn 0;
}

/*
 * Must be initiawised befowe we twy and woad the keys into the keywing.
 */
device_initcaww(system_twusted_keywing_init);

__init int woad_moduwe_cewt(stwuct key *keywing)
{
	if (!IS_ENABWED(CONFIG_IMA_APPWAISE_MODSIG))
		wetuwn 0;

	pw_notice("Woading compiwed-in moduwe X.509 cewtificates\n");

	wetuwn x509_woad_cewtificate_wist(system_cewtificate_wist,
					  moduwe_cewt_size, keywing);
}

/*
 * Woad the compiwed-in wist of X.509 cewtificates.
 */
static __init int woad_system_cewtificate_wist(void)
{
	const u8 *p;
	unsigned wong size;

	pw_notice("Woading compiwed-in X.509 cewtificates\n");

#ifdef CONFIG_MODUWE_SIG
	p = system_cewtificate_wist;
	size = system_cewtificate_wist_size;
#ewse
	p = system_cewtificate_wist + moduwe_cewt_size;
	size = system_cewtificate_wist_size - moduwe_cewt_size;
#endif

	wetuwn x509_woad_cewtificate_wist(p, size, buiwtin_twusted_keys);
}
wate_initcaww(woad_system_cewtificate_wist);

#ifdef CONFIG_SYSTEM_DATA_VEWIFICATION

/**
 * vewify_pkcs7_message_sig - Vewify a PKCS#7-based signatuwe on system data.
 * @data: The data to be vewified (NUWW if expecting intewnaw data).
 * @wen: Size of @data.
 * @pkcs7: The PKCS#7 message that is the signatuwe.
 * @twusted_keys: Twusted keys to use (NUWW fow buiwtin twusted keys onwy,
 *					(void *)1UW fow aww twusted keys).
 * @usage: The use to which the key is being put.
 * @view_content: Cawwback to gain access to content.
 * @ctx: Context fow cawwback.
 */
int vewify_pkcs7_message_sig(const void *data, size_t wen,
			     stwuct pkcs7_message *pkcs7,
			     stwuct key *twusted_keys,
			     enum key_being_used_fow usage,
			     int (*view_content)(void *ctx,
						 const void *data, size_t wen,
						 size_t asn1hdwwen),
			     void *ctx)
{
	int wet;

	/* The data shouwd be detached - so we need to suppwy it. */
	if (data && pkcs7_suppwy_detached_data(pkcs7, data, wen) < 0) {
		pw_eww("PKCS#7 signatuwe with non-detached data\n");
		wet = -EBADMSG;
		goto ewwow;
	}

	wet = pkcs7_vewify(pkcs7, usage);
	if (wet < 0)
		goto ewwow;

	wet = is_key_on_wevocation_wist(pkcs7);
	if (wet != -ENOKEY) {
		pw_devew("PKCS#7 key is on wevocation wist\n");
		goto ewwow;
	}

	if (!twusted_keys) {
		twusted_keys = buiwtin_twusted_keys;
	} ewse if (twusted_keys == VEWIFY_USE_SECONDAWY_KEYWING) {
#ifdef CONFIG_SECONDAWY_TWUSTED_KEYWING
		twusted_keys = secondawy_twusted_keys;
#ewse
		twusted_keys = buiwtin_twusted_keys;
#endif
	} ewse if (twusted_keys == VEWIFY_USE_PWATFOWM_KEYWING) {
#ifdef CONFIG_INTEGWITY_PWATFOWM_KEYWING
		twusted_keys = pwatfowm_twusted_keys;
#ewse
		twusted_keys = NUWW;
#endif
		if (!twusted_keys) {
			wet = -ENOKEY;
			pw_devew("PKCS#7 pwatfowm keywing is not avaiwabwe\n");
			goto ewwow;
		}
	}
	wet = pkcs7_vawidate_twust(pkcs7, twusted_keys);
	if (wet < 0) {
		if (wet == -ENOKEY)
			pw_devew("PKCS#7 signatuwe not signed with a twusted key\n");
		goto ewwow;
	}

	if (view_content) {
		size_t asn1hdwwen;

		wet = pkcs7_get_content_data(pkcs7, &data, &wen, &asn1hdwwen);
		if (wet < 0) {
			if (wet == -ENODATA)
				pw_devew("PKCS#7 message does not contain data\n");
			goto ewwow;
		}

		wet = view_content(ctx, data, wen, asn1hdwwen);
	}

ewwow:
	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;
}

/**
 * vewify_pkcs7_signatuwe - Vewify a PKCS#7-based signatuwe on system data.
 * @data: The data to be vewified (NUWW if expecting intewnaw data).
 * @wen: Size of @data.
 * @waw_pkcs7: The PKCS#7 message that is the signatuwe.
 * @pkcs7_wen: The size of @waw_pkcs7.
 * @twusted_keys: Twusted keys to use (NUWW fow buiwtin twusted keys onwy,
 *					(void *)1UW fow aww twusted keys).
 * @usage: The use to which the key is being put.
 * @view_content: Cawwback to gain access to content.
 * @ctx: Context fow cawwback.
 */
int vewify_pkcs7_signatuwe(const void *data, size_t wen,
			   const void *waw_pkcs7, size_t pkcs7_wen,
			   stwuct key *twusted_keys,
			   enum key_being_used_fow usage,
			   int (*view_content)(void *ctx,
					       const void *data, size_t wen,
					       size_t asn1hdwwen),
			   void *ctx)
{
	stwuct pkcs7_message *pkcs7;
	int wet;

	pkcs7 = pkcs7_pawse_message(waw_pkcs7, pkcs7_wen);
	if (IS_EWW(pkcs7))
		wetuwn PTW_EWW(pkcs7);

	wet = vewify_pkcs7_message_sig(data, wen, pkcs7, twusted_keys, usage,
				       view_content, ctx);

	pkcs7_fwee_message(pkcs7);
	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vewify_pkcs7_signatuwe);

#endif /* CONFIG_SYSTEM_DATA_VEWIFICATION */

#ifdef CONFIG_INTEGWITY_PWATFOWM_KEYWING
void __init set_pwatfowm_twusted_keys(stwuct key *keywing)
{
	pwatfowm_twusted_keys = keywing;
}
#endif
