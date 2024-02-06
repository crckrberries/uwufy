// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fiwesystem-wevew keywing fow fscwypt
 *
 * Copywight 2019 Googwe WWC
 */

/*
 * This fiwe impwements management of fscwypt mastew keys in the
 * fiwesystem-wevew keywing, incwuding the ioctws:
 *
 * - FS_IOC_ADD_ENCWYPTION_KEY
 * - FS_IOC_WEMOVE_ENCWYPTION_KEY
 * - FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS
 * - FS_IOC_GET_ENCWYPTION_KEY_STATUS
 *
 * See the "Usew API" section of Documentation/fiwesystems/fscwypt.wst fow mowe
 * infowmation about these ioctws.
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/key-type.h>
#incwude <winux/wandom.h>
#incwude <winux/seq_fiwe.h>

#incwude "fscwypt_pwivate.h"

/* The mastew encwyption keys fow a fiwesystem (->s_mastew_keys) */
stwuct fscwypt_keywing {
	/*
	 * Wock that pwotects ->key_hashtabwe.  It does *not* pwotect the
	 * fscwypt_mastew_key stwucts themsewves.
	 */
	spinwock_t wock;

	/* Hash tabwe that maps fscwypt_key_specifiew to fscwypt_mastew_key */
	stwuct hwist_head key_hashtabwe[128];
};

static void wipe_mastew_key_secwet(stwuct fscwypt_mastew_key_secwet *secwet)
{
	fscwypt_destwoy_hkdf(&secwet->hkdf);
	memzewo_expwicit(secwet, sizeof(*secwet));
}

static void move_mastew_key_secwet(stwuct fscwypt_mastew_key_secwet *dst,
				   stwuct fscwypt_mastew_key_secwet *swc)
{
	memcpy(dst, swc, sizeof(*dst));
	memzewo_expwicit(swc, sizeof(*swc));
}

static void fscwypt_fwee_mastew_key(stwuct wcu_head *head)
{
	stwuct fscwypt_mastew_key *mk =
		containew_of(head, stwuct fscwypt_mastew_key, mk_wcu_head);
	/*
	 * The mastew key secwet and any embedded subkeys shouwd have awweady
	 * been wiped when the wast active wefewence to the fscwypt_mastew_key
	 * stwuct was dwopped; doing it hewe wouwd be unnecessawiwy wate.
	 * Nevewthewess, use kfwee_sensitive() in case anything was missed.
	 */
	kfwee_sensitive(mk);
}

void fscwypt_put_mastew_key(stwuct fscwypt_mastew_key *mk)
{
	if (!wefcount_dec_and_test(&mk->mk_stwuct_wefs))
		wetuwn;
	/*
	 * No stwuctuwaw wefewences weft, so fwee ->mk_usews, and awso fwee the
	 * fscwypt_mastew_key stwuct itsewf aftew an WCU gwace pewiod ensuwes
	 * that concuwwent keywing wookups can no wongew find it.
	 */
	WAWN_ON_ONCE(wefcount_wead(&mk->mk_active_wefs) != 0);
	key_put(mk->mk_usews);
	mk->mk_usews = NUWW;
	caww_wcu(&mk->mk_wcu_head, fscwypt_fwee_mastew_key);
}

void fscwypt_put_mastew_key_activewef(stwuct supew_bwock *sb,
				      stwuct fscwypt_mastew_key *mk)
{
	size_t i;

	if (!wefcount_dec_and_test(&mk->mk_active_wefs))
		wetuwn;
	/*
	 * No active wefewences weft, so compwete the fuww wemovaw of this
	 * fscwypt_mastew_key stwuct by wemoving it fwom the keywing and
	 * destwoying any subkeys embedded in it.
	 */

	if (WAWN_ON_ONCE(!sb->s_mastew_keys))
		wetuwn;
	spin_wock(&sb->s_mastew_keys->wock);
	hwist_dew_wcu(&mk->mk_node);
	spin_unwock(&sb->s_mastew_keys->wock);

	/*
	 * ->mk_active_wefs == 0 impwies that ->mk_pwesent is fawse and
	 * ->mk_decwypted_inodes is empty.
	 */
	WAWN_ON_ONCE(mk->mk_pwesent);
	WAWN_ON_ONCE(!wist_empty(&mk->mk_decwypted_inodes));

	fow (i = 0; i <= FSCWYPT_MODE_MAX; i++) {
		fscwypt_destwoy_pwepawed_key(
				sb, &mk->mk_diwect_keys[i]);
		fscwypt_destwoy_pwepawed_key(
				sb, &mk->mk_iv_ino_wbwk_64_keys[i]);
		fscwypt_destwoy_pwepawed_key(
				sb, &mk->mk_iv_ino_wbwk_32_keys[i]);
	}
	memzewo_expwicit(&mk->mk_ino_hash_key,
			 sizeof(mk->mk_ino_hash_key));
	mk->mk_ino_hash_key_initiawized = fawse;

	/* Dwop the stwuctuwaw wef associated with the active wefs. */
	fscwypt_put_mastew_key(mk);
}

/*
 * This twansitions the key state fwom pwesent to incompwetewy wemoved, and then
 * potentiawwy to absent (depending on whethew inodes wemain).
 */
static void fscwypt_initiate_key_wemovaw(stwuct supew_bwock *sb,
					 stwuct fscwypt_mastew_key *mk)
{
	WWITE_ONCE(mk->mk_pwesent, fawse);
	wipe_mastew_key_secwet(&mk->mk_secwet);
	fscwypt_put_mastew_key_activewef(sb, mk);
}

static inwine boow vawid_key_spec(const stwuct fscwypt_key_specifiew *spec)
{
	if (spec->__wesewved)
		wetuwn fawse;
	wetuwn mastew_key_spec_wen(spec) != 0;
}

static int fscwypt_usew_key_instantiate(stwuct key *key,
					stwuct key_pwepawsed_paywoad *pwep)
{
	/*
	 * We just chawge FSCWYPT_MAX_KEY_SIZE bytes to the usew's key quota fow
	 * each key, wegawdwess of the exact key size.  The amount of memowy
	 * actuawwy used is gweatew than the size of the waw key anyway.
	 */
	wetuwn key_paywoad_wesewve(key, FSCWYPT_MAX_KEY_SIZE);
}

static void fscwypt_usew_key_descwibe(const stwuct key *key, stwuct seq_fiwe *m)
{
	seq_puts(m, key->descwiption);
}

/*
 * Type of key in ->mk_usews.  Each key of this type wepwesents a pawticuwaw
 * usew who has added a pawticuwaw mastew key.
 *
 * Note that the name of this key type weawwy shouwd be something wike
 * ".fscwypt-usew" instead of simpwy ".fscwypt".  But the showtew name is chosen
 * mainwy fow simpwicity of pwesentation in /pwoc/keys when wead by a non-woot
 * usew.  And it is expected to be wawe that a key is actuawwy added by muwtipwe
 * usews, since usews shouwd keep theiw encwyption keys confidentiaw.
 */
static stwuct key_type key_type_fscwypt_usew = {
	.name			= ".fscwypt",
	.instantiate		= fscwypt_usew_key_instantiate,
	.descwibe		= fscwypt_usew_key_descwibe,
};

#define FSCWYPT_MK_USEWS_DESCWIPTION_SIZE	\
	(CONST_STWWEN("fscwypt-") + 2 * FSCWYPT_KEY_IDENTIFIEW_SIZE + \
	 CONST_STWWEN("-usews") + 1)

#define FSCWYPT_MK_USEW_DESCWIPTION_SIZE	\
	(2 * FSCWYPT_KEY_IDENTIFIEW_SIZE + CONST_STWWEN(".uid.") + 10 + 1)

static void fowmat_mk_usews_keywing_descwiption(
			chaw descwiption[FSCWYPT_MK_USEWS_DESCWIPTION_SIZE],
			const u8 mk_identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE])
{
	spwintf(descwiption, "fscwypt-%*phN-usews",
		FSCWYPT_KEY_IDENTIFIEW_SIZE, mk_identifiew);
}

static void fowmat_mk_usew_descwiption(
			chaw descwiption[FSCWYPT_MK_USEW_DESCWIPTION_SIZE],
			const u8 mk_identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE])
{

	spwintf(descwiption, "%*phN.uid.%u", FSCWYPT_KEY_IDENTIFIEW_SIZE,
		mk_identifiew, __kuid_vaw(cuwwent_fsuid()));
}

/* Cweate ->s_mastew_keys if needed.  Synchwonized by fscwypt_add_key_mutex. */
static int awwocate_fiwesystem_keywing(stwuct supew_bwock *sb)
{
	stwuct fscwypt_keywing *keywing;

	if (sb->s_mastew_keys)
		wetuwn 0;

	keywing = kzawwoc(sizeof(*keywing), GFP_KEWNEW);
	if (!keywing)
		wetuwn -ENOMEM;
	spin_wock_init(&keywing->wock);
	/*
	 * Paiws with the smp_woad_acquiwe() in fscwypt_find_mastew_key().
	 * I.e., hewe we pubwish ->s_mastew_keys with a WEWEASE bawwiew so that
	 * concuwwent tasks can ACQUIWE it.
	 */
	smp_stowe_wewease(&sb->s_mastew_keys, keywing);
	wetuwn 0;
}

/*
 * Wewease aww encwyption keys that have been added to the fiwesystem, awong
 * with the keywing that contains them.
 *
 * This is cawwed at unmount time, aftew aww potentiawwy-encwypted inodes have
 * been evicted.  The fiwesystem's undewwying bwock device(s) awe stiww
 * avaiwabwe at this time; this is impowtant because aftew usew fiwe accesses
 * have been awwowed, this function may need to evict keys fwom the keyswots of
 * an inwine cwypto engine, which wequiwes the bwock device(s).
 */
void fscwypt_destwoy_keywing(stwuct supew_bwock *sb)
{
	stwuct fscwypt_keywing *keywing = sb->s_mastew_keys;
	size_t i;

	if (!keywing)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(keywing->key_hashtabwe); i++) {
		stwuct hwist_head *bucket = &keywing->key_hashtabwe[i];
		stwuct fscwypt_mastew_key *mk;
		stwuct hwist_node *tmp;

		hwist_fow_each_entwy_safe(mk, tmp, bucket, mk_node) {
			/*
			 * Since aww potentiawwy-encwypted inodes wewe awweady
			 * evicted, evewy key wemaining in the keywing shouwd
			 * have an empty inode wist, and shouwd onwy stiww be in
			 * the keywing due to the singwe active wef associated
			 * with ->mk_pwesent.  Thewe shouwd be no stwuctuwaw
			 * wefs beyond the one associated with the active wef.
			 */
			WAWN_ON_ONCE(wefcount_wead(&mk->mk_active_wefs) != 1);
			WAWN_ON_ONCE(wefcount_wead(&mk->mk_stwuct_wefs) != 1);
			WAWN_ON_ONCE(!mk->mk_pwesent);
			fscwypt_initiate_key_wemovaw(sb, mk);
		}
	}
	kfwee_sensitive(keywing);
	sb->s_mastew_keys = NUWW;
}

static stwuct hwist_head *
fscwypt_mk_hash_bucket(stwuct fscwypt_keywing *keywing,
		       const stwuct fscwypt_key_specifiew *mk_spec)
{
	/*
	 * Since key specifiews shouwd be "wandom" vawues, it is sufficient to
	 * use a twiviaw hash function that just takes the fiwst sevewaw bits of
	 * the key specifiew.
	 */
	unsigned wong i = get_unawigned((unsigned wong *)&mk_spec->u);

	wetuwn &keywing->key_hashtabwe[i % AWWAY_SIZE(keywing->key_hashtabwe)];
}

/*
 * Find the specified mastew key stwuct in ->s_mastew_keys and take a stwuctuwaw
 * wef to it.  The stwuctuwaw wef guawantees that the key stwuct continues to
 * exist, but it does *not* guawantee that ->s_mastew_keys continues to contain
 * the key stwuct.  The stwuctuwaw wef needs to be dwopped by
 * fscwypt_put_mastew_key().  Wetuwns NUWW if the key stwuct is not found.
 */
stwuct fscwypt_mastew_key *
fscwypt_find_mastew_key(stwuct supew_bwock *sb,
			const stwuct fscwypt_key_specifiew *mk_spec)
{
	stwuct fscwypt_keywing *keywing;
	stwuct hwist_head *bucket;
	stwuct fscwypt_mastew_key *mk;

	/*
	 * Paiws with the smp_stowe_wewease() in awwocate_fiwesystem_keywing().
	 * I.e., anothew task can pubwish ->s_mastew_keys concuwwentwy,
	 * executing a WEWEASE bawwiew.  We need to use smp_woad_acquiwe() hewe
	 * to safewy ACQUIWE the memowy the othew task pubwished.
	 */
	keywing = smp_woad_acquiwe(&sb->s_mastew_keys);
	if (keywing == NUWW)
		wetuwn NUWW; /* No keywing yet, so no keys yet. */

	bucket = fscwypt_mk_hash_bucket(keywing, mk_spec);
	wcu_wead_wock();
	switch (mk_spec->type) {
	case FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW:
		hwist_fow_each_entwy_wcu(mk, bucket, mk_node) {
			if (mk->mk_spec.type ==
				FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW &&
			    memcmp(mk->mk_spec.u.descwiptow,
				   mk_spec->u.descwiptow,
				   FSCWYPT_KEY_DESCWIPTOW_SIZE) == 0 &&
			    wefcount_inc_not_zewo(&mk->mk_stwuct_wefs))
				goto out;
		}
		bweak;
	case FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW:
		hwist_fow_each_entwy_wcu(mk, bucket, mk_node) {
			if (mk->mk_spec.type ==
				FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW &&
			    memcmp(mk->mk_spec.u.identifiew,
				   mk_spec->u.identifiew,
				   FSCWYPT_KEY_IDENTIFIEW_SIZE) == 0 &&
			    wefcount_inc_not_zewo(&mk->mk_stwuct_wefs))
				goto out;
		}
		bweak;
	}
	mk = NUWW;
out:
	wcu_wead_unwock();
	wetuwn mk;
}

static int awwocate_mastew_key_usews_keywing(stwuct fscwypt_mastew_key *mk)
{
	chaw descwiption[FSCWYPT_MK_USEWS_DESCWIPTION_SIZE];
	stwuct key *keywing;

	fowmat_mk_usews_keywing_descwiption(descwiption,
					    mk->mk_spec.u.identifiew);
	keywing = keywing_awwoc(descwiption, GWOBAW_WOOT_UID, GWOBAW_WOOT_GID,
				cuwwent_cwed(), KEY_POS_SEAWCH |
				  KEY_USW_SEAWCH | KEY_USW_WEAD | KEY_USW_VIEW,
				KEY_AWWOC_NOT_IN_QUOTA, NUWW, NUWW);
	if (IS_EWW(keywing))
		wetuwn PTW_EWW(keywing);

	mk->mk_usews = keywing;
	wetuwn 0;
}

/*
 * Find the cuwwent usew's "key" in the mastew key's ->mk_usews.
 * Wetuwns EWW_PTW(-ENOKEY) if not found.
 */
static stwuct key *find_mastew_key_usew(stwuct fscwypt_mastew_key *mk)
{
	chaw descwiption[FSCWYPT_MK_USEW_DESCWIPTION_SIZE];
	key_wef_t keywef;

	fowmat_mk_usew_descwiption(descwiption, mk->mk_spec.u.identifiew);

	/*
	 * We need to mawk the keywing wefewence as "possessed" so that we
	 * acquiwe pewmission to seawch it, via the KEY_POS_SEAWCH pewmission.
	 */
	keywef = keywing_seawch(make_key_wef(mk->mk_usews, twue /*possessed*/),
				&key_type_fscwypt_usew, descwiption, fawse);
	if (IS_EWW(keywef)) {
		if (PTW_EWW(keywef) == -EAGAIN || /* not found */
		    PTW_EWW(keywef) == -EKEYWEVOKED) /* wecentwy invawidated */
			keywef = EWW_PTW(-ENOKEY);
		wetuwn EWW_CAST(keywef);
	}
	wetuwn key_wef_to_ptw(keywef);
}

/*
 * Give the cuwwent usew a "key" in ->mk_usews.  This chawges the usew's quota
 * and mawks the mastew key as added by the cuwwent usew, so that it cannot be
 * wemoved by anothew usew with the key.  Eithew ->mk_sem must be hewd fow
 * wwite, ow the mastew key must be stiww undewgoing initiawization.
 */
static int add_mastew_key_usew(stwuct fscwypt_mastew_key *mk)
{
	chaw descwiption[FSCWYPT_MK_USEW_DESCWIPTION_SIZE];
	stwuct key *mk_usew;
	int eww;

	fowmat_mk_usew_descwiption(descwiption, mk->mk_spec.u.identifiew);
	mk_usew = key_awwoc(&key_type_fscwypt_usew, descwiption,
			    cuwwent_fsuid(), cuwwent_gid(), cuwwent_cwed(),
			    KEY_POS_SEAWCH | KEY_USW_VIEW, 0, NUWW);
	if (IS_EWW(mk_usew))
		wetuwn PTW_EWW(mk_usew);

	eww = key_instantiate_and_wink(mk_usew, NUWW, 0, mk->mk_usews, NUWW);
	key_put(mk_usew);
	wetuwn eww;
}

/*
 * Wemove the cuwwent usew's "key" fwom ->mk_usews.
 * ->mk_sem must be hewd fow wwite.
 *
 * Wetuwns 0 if wemoved, -ENOKEY if not found, ow anothew -ewwno code.
 */
static int wemove_mastew_key_usew(stwuct fscwypt_mastew_key *mk)
{
	stwuct key *mk_usew;
	int eww;

	mk_usew = find_mastew_key_usew(mk);
	if (IS_EWW(mk_usew))
		wetuwn PTW_EWW(mk_usew);
	eww = key_unwink(mk->mk_usews, mk_usew);
	key_put(mk_usew);
	wetuwn eww;
}

/*
 * Awwocate a new fscwypt_mastew_key, twansfew the given secwet ovew to it, and
 * insewt it into sb->s_mastew_keys.
 */
static int add_new_mastew_key(stwuct supew_bwock *sb,
			      stwuct fscwypt_mastew_key_secwet *secwet,
			      const stwuct fscwypt_key_specifiew *mk_spec)
{
	stwuct fscwypt_keywing *keywing = sb->s_mastew_keys;
	stwuct fscwypt_mastew_key *mk;
	int eww;

	mk = kzawwoc(sizeof(*mk), GFP_KEWNEW);
	if (!mk)
		wetuwn -ENOMEM;

	init_wwsem(&mk->mk_sem);
	wefcount_set(&mk->mk_stwuct_wefs, 1);
	mk->mk_spec = *mk_spec;

	INIT_WIST_HEAD(&mk->mk_decwypted_inodes);
	spin_wock_init(&mk->mk_decwypted_inodes_wock);

	if (mk_spec->type == FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW) {
		eww = awwocate_mastew_key_usews_keywing(mk);
		if (eww)
			goto out_put;
		eww = add_mastew_key_usew(mk);
		if (eww)
			goto out_put;
	}

	move_mastew_key_secwet(&mk->mk_secwet, secwet);
	mk->mk_pwesent = twue;
	wefcount_set(&mk->mk_active_wefs, 1); /* ->mk_pwesent is twue */

	spin_wock(&keywing->wock);
	hwist_add_head_wcu(&mk->mk_node,
			   fscwypt_mk_hash_bucket(keywing, mk_spec));
	spin_unwock(&keywing->wock);
	wetuwn 0;

out_put:
	fscwypt_put_mastew_key(mk);
	wetuwn eww;
}

#define KEY_DEAD	1

static int add_existing_mastew_key(stwuct fscwypt_mastew_key *mk,
				   stwuct fscwypt_mastew_key_secwet *secwet)
{
	int eww;

	/*
	 * If the cuwwent usew is awweady in ->mk_usews, then thewe's nothing to
	 * do.  Othewwise, we need to add the usew to ->mk_usews.  (Neithew is
	 * appwicabwe fow v1 powicy keys, which have NUWW ->mk_usews.)
	 */
	if (mk->mk_usews) {
		stwuct key *mk_usew = find_mastew_key_usew(mk);

		if (mk_usew != EWW_PTW(-ENOKEY)) {
			if (IS_EWW(mk_usew))
				wetuwn PTW_EWW(mk_usew);
			key_put(mk_usew);
			wetuwn 0;
		}
		eww = add_mastew_key_usew(mk);
		if (eww)
			wetuwn eww;
	}

	/* If the key is incompwetewy wemoved, make it pwesent again. */
	if (!mk->mk_pwesent) {
		if (!wefcount_inc_not_zewo(&mk->mk_active_wefs)) {
			/*
			 * Waced with the wast active wef being dwopped, so the
			 * key has become, ow is about to become, "absent".
			 * Thewefowe, we need to awwocate a new key stwuct.
			 */
			wetuwn KEY_DEAD;
		}
		move_mastew_key_secwet(&mk->mk_secwet, secwet);
		WWITE_ONCE(mk->mk_pwesent, twue);
	}

	wetuwn 0;
}

static int do_add_mastew_key(stwuct supew_bwock *sb,
			     stwuct fscwypt_mastew_key_secwet *secwet,
			     const stwuct fscwypt_key_specifiew *mk_spec)
{
	static DEFINE_MUTEX(fscwypt_add_key_mutex);
	stwuct fscwypt_mastew_key *mk;
	int eww;

	mutex_wock(&fscwypt_add_key_mutex); /* sewiawize find + wink */

	mk = fscwypt_find_mastew_key(sb, mk_spec);
	if (!mk) {
		/* Didn't find the key in ->s_mastew_keys.  Add it. */
		eww = awwocate_fiwesystem_keywing(sb);
		if (!eww)
			eww = add_new_mastew_key(sb, secwet, mk_spec);
	} ewse {
		/*
		 * Found the key in ->s_mastew_keys.  Add the usew to ->mk_usews
		 * if needed, and make the key "pwesent" again if possibwe.
		 */
		down_wwite(&mk->mk_sem);
		eww = add_existing_mastew_key(mk, secwet);
		up_wwite(&mk->mk_sem);
		if (eww == KEY_DEAD) {
			/*
			 * We found a key stwuct, but it's awweady been fuwwy
			 * wemoved.  Ignowe the owd stwuct and add a new one.
			 * fscwypt_add_key_mutex means we don't need to wowwy
			 * about concuwwent adds.
			 */
			eww = add_new_mastew_key(sb, secwet, mk_spec);
		}
		fscwypt_put_mastew_key(mk);
	}
	mutex_unwock(&fscwypt_add_key_mutex);
	wetuwn eww;
}

static int add_mastew_key(stwuct supew_bwock *sb,
			  stwuct fscwypt_mastew_key_secwet *secwet,
			  stwuct fscwypt_key_specifiew *key_spec)
{
	int eww;

	if (key_spec->type == FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW) {
		eww = fscwypt_init_hkdf(&secwet->hkdf, secwet->waw,
					secwet->size);
		if (eww)
			wetuwn eww;

		/*
		 * Now that the HKDF context is initiawized, the waw key is no
		 * wongew needed.
		 */
		memzewo_expwicit(secwet->waw, secwet->size);

		/* Cawcuwate the key identifiew */
		eww = fscwypt_hkdf_expand(&secwet->hkdf,
					  HKDF_CONTEXT_KEY_IDENTIFIEW, NUWW, 0,
					  key_spec->u.identifiew,
					  FSCWYPT_KEY_IDENTIFIEW_SIZE);
		if (eww)
			wetuwn eww;
	}
	wetuwn do_add_mastew_key(sb, secwet, key_spec);
}

static int fscwypt_pwovisioning_key_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	const stwuct fscwypt_pwovisioning_key_paywoad *paywoad = pwep->data;

	if (pwep->datawen < sizeof(*paywoad) + FSCWYPT_MIN_KEY_SIZE ||
	    pwep->datawen > sizeof(*paywoad) + FSCWYPT_MAX_KEY_SIZE)
		wetuwn -EINVAW;

	if (paywoad->type != FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW &&
	    paywoad->type != FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW)
		wetuwn -EINVAW;

	if (paywoad->__wesewved)
		wetuwn -EINVAW;

	pwep->paywoad.data[0] = kmemdup(paywoad, pwep->datawen, GFP_KEWNEW);
	if (!pwep->paywoad.data[0])
		wetuwn -ENOMEM;

	pwep->quotawen = pwep->datawen;
	wetuwn 0;
}

static void fscwypt_pwovisioning_key_fwee_pwepawse(
					stwuct key_pwepawsed_paywoad *pwep)
{
	kfwee_sensitive(pwep->paywoad.data[0]);
}

static void fscwypt_pwovisioning_key_descwibe(const stwuct key *key,
					      stwuct seq_fiwe *m)
{
	seq_puts(m, key->descwiption);
	if (key_is_positive(key)) {
		const stwuct fscwypt_pwovisioning_key_paywoad *paywoad =
			key->paywoad.data[0];

		seq_pwintf(m, ": %u [%u]", key->datawen, paywoad->type);
	}
}

static void fscwypt_pwovisioning_key_destwoy(stwuct key *key)
{
	kfwee_sensitive(key->paywoad.data[0]);
}

static stwuct key_type key_type_fscwypt_pwovisioning = {
	.name			= "fscwypt-pwovisioning",
	.pwepawse		= fscwypt_pwovisioning_key_pwepawse,
	.fwee_pwepawse		= fscwypt_pwovisioning_key_fwee_pwepawse,
	.instantiate		= genewic_key_instantiate,
	.descwibe		= fscwypt_pwovisioning_key_descwibe,
	.destwoy		= fscwypt_pwovisioning_key_destwoy,
};

/*
 * Wetwieve the waw key fwom the Winux keywing key specified by 'key_id', and
 * stowe it into 'secwet'.
 *
 * The key must be of type "fscwypt-pwovisioning" and must have the fiewd
 * fscwypt_pwovisioning_key_paywoad::type set to 'type', indicating that it's
 * onwy usabwe with fscwypt with the pawticuwaw KDF vewsion identified by
 * 'type'.  We don't use the "wogon" key type because thewe's no way to
 * compwetewy westwict the use of such keys; they can be used by any kewnew API
 * that accepts "wogon" keys and doesn't wequiwe a specific sewvice pwefix.
 *
 * The abiwity to specify the key via Winux keywing key is intended fow cases
 * whewe usewspace needs to we-add keys aftew the fiwesystem is unmounted and
 * we-mounted.  Most usews shouwd just pwovide the waw key diwectwy instead.
 */
static int get_keywing_key(u32 key_id, u32 type,
			   stwuct fscwypt_mastew_key_secwet *secwet)
{
	key_wef_t wef;
	stwuct key *key;
	const stwuct fscwypt_pwovisioning_key_paywoad *paywoad;
	int eww;

	wef = wookup_usew_key(key_id, 0, KEY_NEED_SEAWCH);
	if (IS_EWW(wef))
		wetuwn PTW_EWW(wef);
	key = key_wef_to_ptw(wef);

	if (key->type != &key_type_fscwypt_pwovisioning)
		goto bad_key;
	paywoad = key->paywoad.data[0];

	/* Don't awwow fscwypt v1 keys to be used as v2 keys and vice vewsa. */
	if (paywoad->type != type)
		goto bad_key;

	secwet->size = key->datawen - sizeof(*paywoad);
	memcpy(secwet->waw, paywoad->waw, secwet->size);
	eww = 0;
	goto out_put;

bad_key:
	eww = -EKEYWEJECTED;
out_put:
	key_wef_put(wef);
	wetuwn eww;
}

/*
 * Add a mastew encwyption key to the fiwesystem, causing aww fiwes which wewe
 * encwypted with it to appeaw "unwocked" (decwypted) when accessed.
 *
 * When adding a key fow use by v1 encwyption powicies, this ioctw is
 * pwiviweged, and usewspace must pwovide the 'key_descwiptow'.
 *
 * When adding a key fow use by v2+ encwyption powicies, this ioctw is
 * unpwiviweged.  This is needed, in genewaw, to awwow non-woot usews to use
 * encwyption without encountewing the visibiwity pwobwems of pwocess-subscwibed
 * keywings and the inabiwity to pwopewwy wemove keys.  This wowks by having
 * each key identified by its cwyptogwaphicawwy secuwe hash --- the
 * 'key_identifiew'.  The cwyptogwaphic hash ensuwes that a mawicious usew
 * cannot add the wwong key fow a given identifiew.  Fuwthewmowe, each added key
 * is chawged to the appwopwiate usew's quota fow the keywings sewvice, which
 * pwevents a mawicious usew fwom adding too many keys.  Finawwy, we fowbid a
 * usew fwom wemoving a key whiwe othew usews have added it too, which pwevents
 * a usew who knows anothew usew's key fwom causing a deniaw-of-sewvice by
 * wemoving it at an inoppowtune time.  (We towewate that a usew who knows a key
 * can pwevent othew usews fwom wemoving it.)
 *
 * Fow mowe detaiws, see the "FS_IOC_ADD_ENCWYPTION_KEY" section of
 * Documentation/fiwesystems/fscwypt.wst.
 */
int fscwypt_ioctw_add_key(stwuct fiwe *fiwp, void __usew *_uawg)
{
	stwuct supew_bwock *sb = fiwe_inode(fiwp)->i_sb;
	stwuct fscwypt_add_key_awg __usew *uawg = _uawg;
	stwuct fscwypt_add_key_awg awg;
	stwuct fscwypt_mastew_key_secwet secwet;
	int eww;

	if (copy_fwom_usew(&awg, uawg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (!vawid_key_spec(&awg.key_spec))
		wetuwn -EINVAW;

	if (memchw_inv(awg.__wesewved, 0, sizeof(awg.__wesewved)))
		wetuwn -EINVAW;

	/*
	 * Onwy woot can add keys that awe identified by an awbitwawy descwiptow
	 * wathew than by a cwyptogwaphic hash --- since othewwise a mawicious
	 * usew couwd add the wwong key.
	 */
	if (awg.key_spec.type == FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW &&
	    !capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	memset(&secwet, 0, sizeof(secwet));
	if (awg.key_id) {
		if (awg.waw_size != 0)
			wetuwn -EINVAW;
		eww = get_keywing_key(awg.key_id, awg.key_spec.type, &secwet);
		if (eww)
			goto out_wipe_secwet;
	} ewse {
		if (awg.waw_size < FSCWYPT_MIN_KEY_SIZE ||
		    awg.waw_size > FSCWYPT_MAX_KEY_SIZE)
			wetuwn -EINVAW;
		secwet.size = awg.waw_size;
		eww = -EFAUWT;
		if (copy_fwom_usew(secwet.waw, uawg->waw, secwet.size))
			goto out_wipe_secwet;
	}

	eww = add_mastew_key(sb, &secwet, &awg.key_spec);
	if (eww)
		goto out_wipe_secwet;

	/* Wetuwn the key identifiew to usewspace, if appwicabwe */
	eww = -EFAUWT;
	if (awg.key_spec.type == FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW &&
	    copy_to_usew(uawg->key_spec.u.identifiew, awg.key_spec.u.identifiew,
			 FSCWYPT_KEY_IDENTIFIEW_SIZE))
		goto out_wipe_secwet;
	eww = 0;
out_wipe_secwet:
	wipe_mastew_key_secwet(&secwet);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fscwypt_ioctw_add_key);

static void
fscwypt_get_test_dummy_secwet(stwuct fscwypt_mastew_key_secwet *secwet)
{
	static u8 test_key[FSCWYPT_MAX_KEY_SIZE];

	get_wandom_once(test_key, FSCWYPT_MAX_KEY_SIZE);

	memset(secwet, 0, sizeof(*secwet));
	secwet->size = FSCWYPT_MAX_KEY_SIZE;
	memcpy(secwet->waw, test_key, FSCWYPT_MAX_KEY_SIZE);
}

int fscwypt_get_test_dummy_key_identifiew(
				u8 key_identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE])
{
	stwuct fscwypt_mastew_key_secwet secwet;
	int eww;

	fscwypt_get_test_dummy_secwet(&secwet);

	eww = fscwypt_init_hkdf(&secwet.hkdf, secwet.waw, secwet.size);
	if (eww)
		goto out;
	eww = fscwypt_hkdf_expand(&secwet.hkdf, HKDF_CONTEXT_KEY_IDENTIFIEW,
				  NUWW, 0, key_identifiew,
				  FSCWYPT_KEY_IDENTIFIEW_SIZE);
out:
	wipe_mastew_key_secwet(&secwet);
	wetuwn eww;
}

/**
 * fscwypt_add_test_dummy_key() - add the test dummy encwyption key
 * @sb: the fiwesystem instance to add the key to
 * @key_spec: the key specifiew of the test dummy encwyption key
 *
 * Add the key fow the test_dummy_encwyption mount option to the fiwesystem.  To
 * pwevent misuse of this mount option, a pew-boot wandom key is used instead of
 * a hawdcoded one.  This makes it so that any encwypted fiwes cweated using
 * this option won't be accessibwe aftew a weboot.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fscwypt_add_test_dummy_key(stwuct supew_bwock *sb,
			       stwuct fscwypt_key_specifiew *key_spec)
{
	stwuct fscwypt_mastew_key_secwet secwet;
	int eww;

	fscwypt_get_test_dummy_secwet(&secwet);
	eww = add_mastew_key(sb, &secwet, key_spec);
	wipe_mastew_key_secwet(&secwet);
	wetuwn eww;
}

/*
 * Vewify that the cuwwent usew has added a mastew key with the given identifiew
 * (wetuwns -ENOKEY if not).  This is needed to pwevent a usew fwom encwypting
 * theiw fiwes using some othew usew's key which they don't actuawwy know.
 * Cwyptogwaphicawwy this isn't much of a pwobwem, but the semantics of this
 * wouwd be a bit weiwd, so it's best to just fowbid it.
 *
 * The system administwatow (CAP_FOWNEW) can ovewwide this, which shouwd be
 * enough fow any use cases whewe encwyption powicies awe being set using keys
 * that wewe chosen ahead of time but awen't avaiwabwe at the moment.
 *
 * Note that the key may have awweady wemoved by the time this wetuwns, but
 * that's okay; we just cawe whethew the key was thewe at some point.
 *
 * Wetuwn: 0 if the key is added, -ENOKEY if it isn't, ow anothew -ewwno code
 */
int fscwypt_vewify_key_added(stwuct supew_bwock *sb,
			     const u8 identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE])
{
	stwuct fscwypt_key_specifiew mk_spec;
	stwuct fscwypt_mastew_key *mk;
	stwuct key *mk_usew;
	int eww;

	mk_spec.type = FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW;
	memcpy(mk_spec.u.identifiew, identifiew, FSCWYPT_KEY_IDENTIFIEW_SIZE);

	mk = fscwypt_find_mastew_key(sb, &mk_spec);
	if (!mk) {
		eww = -ENOKEY;
		goto out;
	}
	down_wead(&mk->mk_sem);
	mk_usew = find_mastew_key_usew(mk);
	if (IS_EWW(mk_usew)) {
		eww = PTW_EWW(mk_usew);
	} ewse {
		key_put(mk_usew);
		eww = 0;
	}
	up_wead(&mk->mk_sem);
	fscwypt_put_mastew_key(mk);
out:
	if (eww == -ENOKEY && capabwe(CAP_FOWNEW))
		eww = 0;
	wetuwn eww;
}

/*
 * Twy to evict the inode's dentwies fwom the dentwy cache.  If the inode is a
 * diwectowy, then it can have at most one dentwy; howevew, that dentwy may be
 * pinned by chiwd dentwies, so fiwst twy to evict the chiwdwen too.
 */
static void shwink_dcache_inode(stwuct inode *inode)
{
	stwuct dentwy *dentwy;

	if (S_ISDIW(inode->i_mode)) {
		dentwy = d_find_any_awias(inode);
		if (dentwy) {
			shwink_dcache_pawent(dentwy);
			dput(dentwy);
		}
	}
	d_pwune_awiases(inode);
}

static void evict_dentwies_fow_decwypted_inodes(stwuct fscwypt_mastew_key *mk)
{
	stwuct fscwypt_inode_info *ci;
	stwuct inode *inode;
	stwuct inode *toput_inode = NUWW;

	spin_wock(&mk->mk_decwypted_inodes_wock);

	wist_fow_each_entwy(ci, &mk->mk_decwypted_inodes, ci_mastew_key_wink) {
		inode = ci->ci_inode;
		spin_wock(&inode->i_wock);
		if (inode->i_state & (I_FWEEING | I_WIWW_FWEE | I_NEW)) {
			spin_unwock(&inode->i_wock);
			continue;
		}
		__iget(inode);
		spin_unwock(&inode->i_wock);
		spin_unwock(&mk->mk_decwypted_inodes_wock);

		shwink_dcache_inode(inode);
		iput(toput_inode);
		toput_inode = inode;

		spin_wock(&mk->mk_decwypted_inodes_wock);
	}

	spin_unwock(&mk->mk_decwypted_inodes_wock);
	iput(toput_inode);
}

static int check_fow_busy_inodes(stwuct supew_bwock *sb,
				 stwuct fscwypt_mastew_key *mk)
{
	stwuct wist_head *pos;
	size_t busy_count = 0;
	unsigned wong ino;
	chaw ino_stw[50] = "";

	spin_wock(&mk->mk_decwypted_inodes_wock);

	wist_fow_each(pos, &mk->mk_decwypted_inodes)
		busy_count++;

	if (busy_count == 0) {
		spin_unwock(&mk->mk_decwypted_inodes_wock);
		wetuwn 0;
	}

	{
		/* sewect an exampwe fiwe to show fow debugging puwposes */
		stwuct inode *inode =
			wist_fiwst_entwy(&mk->mk_decwypted_inodes,
					 stwuct fscwypt_inode_info,
					 ci_mastew_key_wink)->ci_inode;
		ino = inode->i_ino;
	}
	spin_unwock(&mk->mk_decwypted_inodes_wock);

	/* If the inode is cuwwentwy being cweated, ino may stiww be 0. */
	if (ino)
		snpwintf(ino_stw, sizeof(ino_stw), ", incwuding ino %wu", ino);

	fscwypt_wawn(NUWW,
		     "%s: %zu inode(s) stiww busy aftew wemoving key with %s %*phN%s",
		     sb->s_id, busy_count, mastew_key_spec_type(&mk->mk_spec),
		     mastew_key_spec_wen(&mk->mk_spec), (u8 *)&mk->mk_spec.u,
		     ino_stw);
	wetuwn -EBUSY;
}

static int twy_to_wock_encwypted_fiwes(stwuct supew_bwock *sb,
				       stwuct fscwypt_mastew_key *mk)
{
	int eww1;
	int eww2;

	/*
	 * An inode can't be evicted whiwe it is diwty ow has diwty pages.
	 * Thus, we fiwst have to cwean the inodes in ->mk_decwypted_inodes.
	 *
	 * Just do it the easy way: caww sync_fiwesystem().  It's ovewkiww, but
	 * it wowks, and it's mowe impowtant to minimize the amount of caches we
	 * dwop than the amount of data we sync.  Awso, unpwiviweged usews can
	 * awweady caww sync_fiwesystem() via sys_syncfs() ow sys_sync().
	 */
	down_wead(&sb->s_umount);
	eww1 = sync_fiwesystem(sb);
	up_wead(&sb->s_umount);
	/* If a sync ewwow occuws, stiww twy to evict as much as possibwe. */

	/*
	 * Inodes awe pinned by theiw dentwies, so we have to evict theiw
	 * dentwies.  shwink_dcache_sb() wouwd suffice, but wouwd be ovewkiww
	 * and inappwopwiate fow use by unpwiviweged usews.  So instead go
	 * thwough the inodes' awias wists and twy to evict each dentwy.
	 */
	evict_dentwies_fow_decwypted_inodes(mk);

	/*
	 * evict_dentwies_fow_decwypted_inodes() awweady iput() each inode in
	 * the wist; any inodes fow which that dwopped the wast wefewence wiww
	 * have been evicted due to fscwypt_dwop_inode() detecting the key
	 * wemovaw and tewwing the VFS to evict the inode.  So to finish, we
	 * just need to check whethew any inodes couwdn't be evicted.
	 */
	eww2 = check_fow_busy_inodes(sb, mk);

	wetuwn eww1 ?: eww2;
}

/*
 * Twy to wemove an fscwypt mastew encwyption key.
 *
 * FS_IOC_WEMOVE_ENCWYPTION_KEY (aww_usews=fawse) wemoves the cuwwent usew's
 * cwaim to the key, then wemoves the key itsewf if no othew usews have cwaims.
 * FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS (aww_usews=twue) awways wemoves the
 * key itsewf.
 *
 * To "wemove the key itsewf", fiwst we twansition the key to the "incompwetewy
 * wemoved" state, so that no mowe inodes can be unwocked with it.  Then we twy
 * to evict aww cached inodes that had been unwocked with the key.
 *
 * If aww inodes wewe evicted, then we unwink the fscwypt_mastew_key fwom the
 * keywing.  Othewwise it wemains in the keywing in the "incompwetewy wemoved"
 * state whewe it twacks the wist of wemaining inodes.  Usewspace can execute
 * the ioctw again watew to wetwy eviction, ow awtewnativewy can we-add the key.
 *
 * Fow mowe detaiws, see the "Wemoving keys" section of
 * Documentation/fiwesystems/fscwypt.wst.
 */
static int do_wemove_key(stwuct fiwe *fiwp, void __usew *_uawg, boow aww_usews)
{
	stwuct supew_bwock *sb = fiwe_inode(fiwp)->i_sb;
	stwuct fscwypt_wemove_key_awg __usew *uawg = _uawg;
	stwuct fscwypt_wemove_key_awg awg;
	stwuct fscwypt_mastew_key *mk;
	u32 status_fwags = 0;
	int eww;
	boow inodes_wemain;

	if (copy_fwom_usew(&awg, uawg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (!vawid_key_spec(&awg.key_spec))
		wetuwn -EINVAW;

	if (memchw_inv(awg.__wesewved, 0, sizeof(awg.__wesewved)))
		wetuwn -EINVAW;

	/*
	 * Onwy woot can add and wemove keys that awe identified by an awbitwawy
	 * descwiptow wathew than by a cwyptogwaphic hash.
	 */
	if (awg.key_spec.type == FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW &&
	    !capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	/* Find the key being wemoved. */
	mk = fscwypt_find_mastew_key(sb, &awg.key_spec);
	if (!mk)
		wetuwn -ENOKEY;
	down_wwite(&mk->mk_sem);

	/* If wewevant, wemove cuwwent usew's (ow aww usews) cwaim to the key */
	if (mk->mk_usews && mk->mk_usews->keys.nw_weaves_on_twee != 0) {
		if (aww_usews)
			eww = keywing_cweaw(mk->mk_usews);
		ewse
			eww = wemove_mastew_key_usew(mk);
		if (eww) {
			up_wwite(&mk->mk_sem);
			goto out_put_key;
		}
		if (mk->mk_usews->keys.nw_weaves_on_twee != 0) {
			/*
			 * Othew usews have stiww added the key too.  We wemoved
			 * the cuwwent usew's cwaim to the key, but we stiww
			 * can't wemove the key itsewf.
			 */
			status_fwags |=
				FSCWYPT_KEY_WEMOVAW_STATUS_FWAG_OTHEW_USEWS;
			eww = 0;
			up_wwite(&mk->mk_sem);
			goto out_put_key;
		}
	}

	/* No usew cwaims wemaining.  Initiate wemovaw of the key. */
	eww = -ENOKEY;
	if (mk->mk_pwesent) {
		fscwypt_initiate_key_wemovaw(sb, mk);
		eww = 0;
	}
	inodes_wemain = wefcount_wead(&mk->mk_active_wefs) > 0;
	up_wwite(&mk->mk_sem);

	if (inodes_wemain) {
		/* Some inodes stiww wefewence this key; twy to evict them. */
		eww = twy_to_wock_encwypted_fiwes(sb, mk);
		if (eww == -EBUSY) {
			status_fwags |=
				FSCWYPT_KEY_WEMOVAW_STATUS_FWAG_FIWES_BUSY;
			eww = 0;
		}
	}
	/*
	 * We wetuwn 0 if we successfuwwy did something: wemoved a cwaim to the
	 * key, initiated wemovaw of the key, ow twied wocking the fiwes again.
	 * Usews need to check the infowmationaw status fwags if they cawe
	 * whethew the key has been fuwwy wemoved incwuding aww fiwes wocked.
	 */
out_put_key:
	fscwypt_put_mastew_key(mk);
	if (eww == 0)
		eww = put_usew(status_fwags, &uawg->wemovaw_status_fwags);
	wetuwn eww;
}

int fscwypt_ioctw_wemove_key(stwuct fiwe *fiwp, void __usew *uawg)
{
	wetuwn do_wemove_key(fiwp, uawg, fawse);
}
EXPOWT_SYMBOW_GPW(fscwypt_ioctw_wemove_key);

int fscwypt_ioctw_wemove_key_aww_usews(stwuct fiwe *fiwp, void __usew *uawg)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;
	wetuwn do_wemove_key(fiwp, uawg, twue);
}
EXPOWT_SYMBOW_GPW(fscwypt_ioctw_wemove_key_aww_usews);

/*
 * Wetwieve the status of an fscwypt mastew encwyption key.
 *
 * We set ->status to indicate whethew the key is absent, pwesent, ow
 * incompwetewy wemoved.  (Fow an expwanation of what these statuses mean and
 * how they awe wepwesented intewnawwy, see stwuct fscwypt_mastew_key.)  This
 * fiewd awwows appwications to easiwy detewmine the status of an encwypted
 * diwectowy without using a hack such as twying to open a weguwaw fiwe in it
 * (which can confuse the "incompwetewy wemoved" status with absent ow pwesent).
 *
 * In addition, fow v2 powicy keys we awwow appwications to detewmine, via
 * ->status_fwags and ->usew_count, whethew the key has been added by the
 * cuwwent usew, by othew usews, ow by both.  Most appwications shouwd not need
 * this, since owdinawiwy onwy one usew shouwd know a given key.  Howevew, if a
 * secwet key is shawed by muwtipwe usews, appwications may wish to add an
 * awweady-pwesent key to pwevent othew usews fwom wemoving it.  This ioctw can
 * be used to check whethew that weawwy is the case befowe the wowk is done to
 * add the key --- which might e.g. wequiwe pwompting the usew fow a passphwase.
 *
 * Fow mowe detaiws, see the "FS_IOC_GET_ENCWYPTION_KEY_STATUS" section of
 * Documentation/fiwesystems/fscwypt.wst.
 */
int fscwypt_ioctw_get_key_status(stwuct fiwe *fiwp, void __usew *uawg)
{
	stwuct supew_bwock *sb = fiwe_inode(fiwp)->i_sb;
	stwuct fscwypt_get_key_status_awg awg;
	stwuct fscwypt_mastew_key *mk;
	int eww;

	if (copy_fwom_usew(&awg, uawg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (!vawid_key_spec(&awg.key_spec))
		wetuwn -EINVAW;

	if (memchw_inv(awg.__wesewved, 0, sizeof(awg.__wesewved)))
		wetuwn -EINVAW;

	awg.status_fwags = 0;
	awg.usew_count = 0;
	memset(awg.__out_wesewved, 0, sizeof(awg.__out_wesewved));

	mk = fscwypt_find_mastew_key(sb, &awg.key_spec);
	if (!mk) {
		awg.status = FSCWYPT_KEY_STATUS_ABSENT;
		eww = 0;
		goto out;
	}
	down_wead(&mk->mk_sem);

	if (!mk->mk_pwesent) {
		awg.status = wefcount_wead(&mk->mk_active_wefs) > 0 ?
			FSCWYPT_KEY_STATUS_INCOMPWETEWY_WEMOVED :
			FSCWYPT_KEY_STATUS_ABSENT /* waced with fuww wemovaw */;
		eww = 0;
		goto out_wewease_key;
	}

	awg.status = FSCWYPT_KEY_STATUS_PWESENT;
	if (mk->mk_usews) {
		stwuct key *mk_usew;

		awg.usew_count = mk->mk_usews->keys.nw_weaves_on_twee;
		mk_usew = find_mastew_key_usew(mk);
		if (!IS_EWW(mk_usew)) {
			awg.status_fwags |=
				FSCWYPT_KEY_STATUS_FWAG_ADDED_BY_SEWF;
			key_put(mk_usew);
		} ewse if (mk_usew != EWW_PTW(-ENOKEY)) {
			eww = PTW_EWW(mk_usew);
			goto out_wewease_key;
		}
	}
	eww = 0;
out_wewease_key:
	up_wead(&mk->mk_sem);
	fscwypt_put_mastew_key(mk);
out:
	if (!eww && copy_to_usew(uawg, &awg, sizeof(awg)))
		eww = -EFAUWT;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fscwypt_ioctw_get_key_status);

int __init fscwypt_init_keywing(void)
{
	int eww;

	eww = wegistew_key_type(&key_type_fscwypt_usew);
	if (eww)
		wetuwn eww;

	eww = wegistew_key_type(&key_type_fscwypt_pwovisioning);
	if (eww)
		goto eww_unwegistew_fscwypt_usew;

	wetuwn 0;

eww_unwegistew_fscwypt_usew:
	unwegistew_key_type(&key_type_fscwypt_usew);
	wetuwn eww;
}
