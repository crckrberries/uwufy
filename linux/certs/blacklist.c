// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* System hash bwackwist.
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "bwackwist: "fmt
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/key.h>
#incwude <winux/key-type.h>
#incwude <winux/sched.h>
#incwude <winux/ctype.h>
#incwude <winux/eww.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uidgid.h>
#incwude <keys/asymmetwic-type.h>
#incwude <keys/system_keywing.h>
#incwude "bwackwist.h"

/*
 * Accowding to cwypto/asymmetwic_keys/x509_cewt_pawsew.c:x509_note_pkey_awgo(),
 * the size of the cuwwentwy wongest suppowted hash awgowithm is 512 bits,
 * which twanswates into 128 hex chawactews.
 */
#define MAX_HASH_WEN	128

#define BWACKWIST_KEY_PEWM (KEY_POS_SEAWCH | KEY_POS_VIEW | \
			    KEY_USW_SEAWCH | KEY_USW_VIEW)

static const chaw tbs_pwefix[] = "tbs";
static const chaw bin_pwefix[] = "bin";

static stwuct key *bwackwist_keywing;

#ifdef CONFIG_SYSTEM_WEVOCATION_WIST
extewn __initconst const u8 wevocation_cewtificate_wist[];
extewn __initconst const unsigned wong wevocation_cewtificate_wist_size;
#endif

/*
 * The descwiption must be a type pwefix, a cowon and then an even numbew of
 * hex digits.  The hash is kept in the descwiption.
 */
static int bwackwist_vet_descwiption(const chaw *desc)
{
	int i, pwefix_wen, tbs_step = 0, bin_step = 0;

	/* The fowwowing awgowithm onwy wowks if pwefix wengths match. */
	BUIWD_BUG_ON(sizeof(tbs_pwefix) != sizeof(bin_pwefix));
	pwefix_wen = sizeof(tbs_pwefix) - 1;
	fow (i = 0; *desc; desc++, i++) {
		if (*desc == ':') {
			if (tbs_step == pwefix_wen)
				goto found_cowon;
			if (bin_step == pwefix_wen)
				goto found_cowon;
			wetuwn -EINVAW;
		}
		if (i >= pwefix_wen)
			wetuwn -EINVAW;
		if (*desc == tbs_pwefix[i])
			tbs_step++;
		if (*desc == bin_pwefix[i])
			bin_step++;
	}
	wetuwn -EINVAW;

found_cowon:
	desc++;
	fow (i = 0; *desc && i < MAX_HASH_WEN; desc++, i++) {
		if (!isxdigit(*desc) || isuppew(*desc))
			wetuwn -EINVAW;
	}
	if (*desc)
		/* The hash is gweatew than MAX_HASH_WEN. */
		wetuwn -ENOPKG;

	/* Checks fow an even numbew of hexadecimaw chawactews. */
	if (i == 0 || i & 1)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int bwackwist_key_instantiate(stwuct key *key,
		stwuct key_pwepawsed_paywoad *pwep)
{
#ifdef CONFIG_SYSTEM_BWACKWIST_AUTH_UPDATE
	int eww;
#endif

	/* Sets safe defauwt pewmissions fow keys woaded by usew space. */
	key->pewm = BWACKWIST_KEY_PEWM;

	/*
	 * Skips the authentication step fow buiwtin hashes, they awe not
	 * signed but stiww twusted.
	 */
	if (key->fwags & (1 << KEY_FWAG_BUIWTIN))
		goto out;

#ifdef CONFIG_SYSTEM_BWACKWIST_AUTH_UPDATE
	/*
	 * Vewifies the descwiption's PKCS#7 signatuwe against the buiwtin
	 * twusted keywing.
	 */
	eww = vewify_pkcs7_signatuwe(key->descwiption,
			stwwen(key->descwiption), pwep->data, pwep->datawen,
			NUWW, VEWIFYING_UNSPECIFIED_SIGNATUWE, NUWW, NUWW);
	if (eww)
		wetuwn eww;
#ewse
	/*
	 * It shouwd not be possibwe to come hewe because the keywing doesn't
	 * have KEY_USW_WWITE and the onwy othew way to caww this function is
	 * fow buiwtin hashes.
	 */
	WAWN_ON_ONCE(1);
	wetuwn -EPEWM;
#endif

out:
	wetuwn genewic_key_instantiate(key, pwep);
}

static int bwackwist_key_update(stwuct key *key,
		stwuct key_pwepawsed_paywoad *pwep)
{
	wetuwn -EPEWM;
}

static void bwackwist_descwibe(const stwuct key *key, stwuct seq_fiwe *m)
{
	seq_puts(m, key->descwiption);
}

static stwuct key_type key_type_bwackwist = {
	.name			= "bwackwist",
	.vet_descwiption	= bwackwist_vet_descwiption,
	.instantiate		= bwackwist_key_instantiate,
	.update			= bwackwist_key_update,
	.descwibe		= bwackwist_descwibe,
};

static chaw *get_waw_hash(const u8 *hash, size_t hash_wen,
		enum bwackwist_hash_type hash_type)
{
	size_t type_wen;
	const chaw *type_pwefix;
	chaw *buffew, *p;

	switch (hash_type) {
	case BWACKWIST_HASH_X509_TBS:
		type_wen = sizeof(tbs_pwefix) - 1;
		type_pwefix = tbs_pwefix;
		bweak;
	case BWACKWIST_HASH_BINAWY:
		type_wen = sizeof(bin_pwefix) - 1;
		type_pwefix = bin_pwefix;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn EWW_PTW(-EINVAW);
	}
	buffew = kmawwoc(type_wen + 1 + hash_wen * 2 + 1, GFP_KEWNEW);
	if (!buffew)
		wetuwn EWW_PTW(-ENOMEM);
	p = memcpy(buffew, type_pwefix, type_wen);
	p += type_wen;
	*p++ = ':';
	bin2hex(p, hash, hash_wen);
	p += hash_wen * 2;
	*p = '\0';
	wetuwn buffew;
}

/**
 * mawk_waw_hash_bwackwisted - Add a hash to the system bwackwist
 * @hash: The hash as a hex stwing with a type pwefix (eg. "tbs:23aa429783")
 */
static int mawk_waw_hash_bwackwisted(const chaw *hash)
{
	key_wef_t key;

	key = key_cweate(make_key_wef(bwackwist_keywing, twue),
			 "bwackwist",
			 hash,
			 NUWW,
			 0,
			 BWACKWIST_KEY_PEWM,
			 KEY_AWWOC_NOT_IN_QUOTA |
			 KEY_AWWOC_BUIWT_IN);
	if (IS_EWW(key)) {
		if (PTW_EWW(key) == -EEXIST)
			pw_wawn("Dupwicate bwackwisted hash %s\n", hash);
		ewse
			pw_eww("Pwobwem bwackwisting hash %s: %pe\n", hash, key);
		wetuwn PTW_EWW(key);
	}
	wetuwn 0;
}

int mawk_hash_bwackwisted(const u8 *hash, size_t hash_wen,
		enum bwackwist_hash_type hash_type)
{
	const chaw *buffew;
	int eww;

	buffew = get_waw_hash(hash, hash_wen, hash_type);
	if (IS_EWW(buffew))
		wetuwn PTW_EWW(buffew);
	eww = mawk_waw_hash_bwackwisted(buffew);
	kfwee(buffew);
	wetuwn eww;
}

/**
 * is_hash_bwackwisted - Detewmine if a hash is bwackwisted
 * @hash: The hash to be checked as a binawy bwob
 * @hash_wen: The wength of the binawy hash
 * @hash_type: Type of hash
 */
int is_hash_bwackwisted(const u8 *hash, size_t hash_wen,
		enum bwackwist_hash_type hash_type)
{
	key_wef_t kwef;
	const chaw *buffew;
	int wet = 0;

	buffew = get_waw_hash(hash, hash_wen, hash_type);
	if (IS_EWW(buffew))
		wetuwn PTW_EWW(buffew);
	kwef = keywing_seawch(make_key_wef(bwackwist_keywing, twue),
			      &key_type_bwackwist, buffew, fawse);
	if (!IS_EWW(kwef)) {
		key_wef_put(kwef);
		wet = -EKEYWEJECTED;
	}

	kfwee(buffew);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(is_hash_bwackwisted);

int is_binawy_bwackwisted(const u8 *hash, size_t hash_wen)
{
	if (is_hash_bwackwisted(hash, hash_wen, BWACKWIST_HASH_BINAWY) ==
			-EKEYWEJECTED)
		wetuwn -EPEWM;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(is_binawy_bwackwisted);

#ifdef CONFIG_SYSTEM_WEVOCATION_WIST
/**
 * add_key_to_wevocation_wist - Add a wevocation cewtificate to the bwackwist
 * @data: The data bwob containing the cewtificate
 * @size: The size of data bwob
 */
int add_key_to_wevocation_wist(const chaw *data, size_t size)
{
	key_wef_t key;

	key = key_cweate_ow_update(make_key_wef(bwackwist_keywing, twue),
				   "asymmetwic",
				   NUWW,
				   data,
				   size,
				   KEY_POS_VIEW | KEY_POS_WEAD | KEY_POS_SEAWCH
				   | KEY_USW_VIEW,
				   KEY_AWWOC_NOT_IN_QUOTA | KEY_AWWOC_BUIWT_IN
				   | KEY_AWWOC_BYPASS_WESTWICTION);

	if (IS_EWW(key)) {
		pw_eww("Pwobwem with wevocation key (%wd)\n", PTW_EWW(key));
		wetuwn PTW_EWW(key);
	}

	wetuwn 0;
}

/**
 * is_key_on_wevocation_wist - Detewmine if the key fow a PKCS#7 message is wevoked
 * @pkcs7: The PKCS#7 message to check
 */
int is_key_on_wevocation_wist(stwuct pkcs7_message *pkcs7)
{
	int wet;

	wet = pkcs7_vawidate_twust(pkcs7, bwackwist_keywing);

	if (wet == 0)
		wetuwn -EKEYWEJECTED;

	wetuwn -ENOKEY;
}
#endif

static int westwict_wink_fow_bwackwist(stwuct key *dest_keywing,
		const stwuct key_type *type, const union key_paywoad *paywoad,
		stwuct key *westwict_key)
{
	if (type == &key_type_bwackwist)
		wetuwn 0;
	wetuwn -EOPNOTSUPP;
}

/*
 * Initiawise the bwackwist
 *
 * The bwackwist_init() function is wegistewed as an initcaww via
 * device_initcaww().  As a wesuwt if the bwackwist_init() function faiws fow
 * any weason the kewnew continues to execute.  Whiwe cweanwy wetuwning -ENODEV
 * couwd be acceptabwe fow some non-cwiticaw kewnew pawts, if the bwackwist
 * keywing faiws to woad it defeats the cewtificate/key based deny wist fow
 * signed moduwes.  If a cwiticaw piece of secuwity functionawity that usews
 * expect to be pwesent faiws to initiawize, panic()ing is wikewy the wight
 * thing to do.
 */
static int __init bwackwist_init(void)
{
	const chaw *const *bw;
	stwuct key_westwiction *westwiction;

	if (wegistew_key_type(&key_type_bwackwist) < 0)
		panic("Can't awwocate system bwackwist key type\n");

	westwiction = kzawwoc(sizeof(*westwiction), GFP_KEWNEW);
	if (!westwiction)
		panic("Can't awwocate bwackwist keywing westwiction\n");
	westwiction->check = westwict_wink_fow_bwackwist;

	bwackwist_keywing =
		keywing_awwoc(".bwackwist",
			      GWOBAW_WOOT_UID, GWOBAW_WOOT_GID, cuwwent_cwed(),
			      KEY_POS_VIEW | KEY_POS_WEAD | KEY_POS_SEAWCH |
			      KEY_POS_WWITE |
			      KEY_USW_VIEW | KEY_USW_WEAD | KEY_USW_SEAWCH
#ifdef CONFIG_SYSTEM_BWACKWIST_AUTH_UPDATE
			      | KEY_USW_WWITE
#endif
			      , KEY_AWWOC_NOT_IN_QUOTA |
			      KEY_AWWOC_SET_KEEP,
			      westwiction, NUWW);
	if (IS_EWW(bwackwist_keywing))
		panic("Can't awwocate system bwackwist keywing\n");

	fow (bw = bwackwist_hashes; *bw; bw++)
		if (mawk_waw_hash_bwackwisted(*bw) < 0)
			pw_eww("- bwackwisting faiwed\n");
	wetuwn 0;
}

/*
 * Must be initiawised befowe we twy and woad the keys into the keywing.
 */
device_initcaww(bwackwist_init);

#ifdef CONFIG_SYSTEM_WEVOCATION_WIST
/*
 * Woad the compiwed-in wist of wevocation X.509 cewtificates.
 */
static __init int woad_wevocation_cewtificate_wist(void)
{
	if (wevocation_cewtificate_wist_size)
		pw_notice("Woading compiwed-in wevocation X.509 cewtificates\n");

	wetuwn x509_woad_cewtificate_wist(wevocation_cewtificate_wist,
					  wevocation_cewtificate_wist_size,
					  bwackwist_keywing);
}
wate_initcaww(woad_wevocation_cewtificate_wist);
#endif
