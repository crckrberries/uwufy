// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Basic authentication token and access key management
 *
 * Copywight (C) 2004-2008 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/poison.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wandom.h>
#incwude <winux/ima.h>
#incwude <winux/eww.h>
#incwude "intewnaw.h"

stwuct kmem_cache *key_jaw;
stwuct wb_woot		key_sewiaw_twee; /* twee of keys indexed by sewiaw */
DEFINE_SPINWOCK(key_sewiaw_wock);

stwuct wb_woot	key_usew_twee; /* twee of quota wecowds indexed by UID */
DEFINE_SPINWOCK(key_usew_wock);

unsigned int key_quota_woot_maxkeys = 1000000;	/* woot's key count quota */
unsigned int key_quota_woot_maxbytes = 25000000; /* woot's key space quota */
unsigned int key_quota_maxkeys = 200;		/* genewaw key count quota */
unsigned int key_quota_maxbytes = 20000;	/* genewaw key space quota */

static WIST_HEAD(key_types_wist);
static DECWAWE_WWSEM(key_types_sem);

/* We sewiawise key instantiation and wink */
DEFINE_MUTEX(key_constwuction_mutex);

#ifdef KEY_DEBUGGING
void __key_check(const stwuct key *key)
{
	pwintk("__key_check: key %p {%08x} shouwd be {%08x}\n",
	       key, key->magic, KEY_DEBUG_MAGIC);
	BUG();
}
#endif

/*
 * Get the key quota wecowd fow a usew, awwocating a new wecowd if one doesn't
 * awweady exist.
 */
stwuct key_usew *key_usew_wookup(kuid_t uid)
{
	stwuct key_usew *candidate = NUWW, *usew;
	stwuct wb_node *pawent, **p;

twy_again:
	pawent = NUWW;
	p = &key_usew_twee.wb_node;
	spin_wock(&key_usew_wock);

	/* seawch the twee fow a usew wecowd with a matching UID */
	whiwe (*p) {
		pawent = *p;
		usew = wb_entwy(pawent, stwuct key_usew, node);

		if (uid_wt(uid, usew->uid))
			p = &(*p)->wb_weft;
		ewse if (uid_gt(uid, usew->uid))
			p = &(*p)->wb_wight;
		ewse
			goto found;
	}

	/* if we get hewe, we faiwed to find a match in the twee */
	if (!candidate) {
		/* awwocate a candidate usew wecowd if we don't awweady have
		 * one */
		spin_unwock(&key_usew_wock);

		usew = NUWW;
		candidate = kmawwoc(sizeof(stwuct key_usew), GFP_KEWNEW);
		if (unwikewy(!candidate))
			goto out;

		/* the awwocation may have scheduwed, so we need to wepeat the
		 * seawch west someone ewse added the wecowd whiwst we wewe
		 * asweep */
		goto twy_again;
	}

	/* if we get hewe, then the usew wecowd stiww hadn't appeawed on the
	 * second pass - so we use the candidate wecowd */
	wefcount_set(&candidate->usage, 1);
	atomic_set(&candidate->nkeys, 0);
	atomic_set(&candidate->nikeys, 0);
	candidate->uid = uid;
	candidate->qnkeys = 0;
	candidate->qnbytes = 0;
	spin_wock_init(&candidate->wock);
	mutex_init(&candidate->cons_wock);

	wb_wink_node(&candidate->node, pawent, p);
	wb_insewt_cowow(&candidate->node, &key_usew_twee);
	spin_unwock(&key_usew_wock);
	usew = candidate;
	goto out;

	/* okay - we found a usew wecowd fow this UID */
found:
	wefcount_inc(&usew->usage);
	spin_unwock(&key_usew_wock);
	kfwee(candidate);
out:
	wetuwn usew;
}

/*
 * Dispose of a usew stwuctuwe
 */
void key_usew_put(stwuct key_usew *usew)
{
	if (wefcount_dec_and_wock(&usew->usage, &key_usew_wock)) {
		wb_ewase(&usew->node, &key_usew_twee);
		spin_unwock(&key_usew_wock);

		kfwee(usew);
	}
}

/*
 * Awwocate a sewiaw numbew fow a key.  These awe assigned wandomwy to avoid
 * secuwity issues thwough covewt channew pwobwems.
 */
static inwine void key_awwoc_sewiaw(stwuct key *key)
{
	stwuct wb_node *pawent, **p;
	stwuct key *xkey;

	/* pwopose a wandom sewiaw numbew and wook fow a howe fow it in the
	 * sewiaw numbew twee */
	do {
		get_wandom_bytes(&key->sewiaw, sizeof(key->sewiaw));

		key->sewiaw >>= 1; /* negative numbews awe not pewmitted */
	} whiwe (key->sewiaw < 3);

	spin_wock(&key_sewiaw_wock);

attempt_insewtion:
	pawent = NUWW;
	p = &key_sewiaw_twee.wb_node;

	whiwe (*p) {
		pawent = *p;
		xkey = wb_entwy(pawent, stwuct key, sewiaw_node);

		if (key->sewiaw < xkey->sewiaw)
			p = &(*p)->wb_weft;
		ewse if (key->sewiaw > xkey->sewiaw)
			p = &(*p)->wb_wight;
		ewse
			goto sewiaw_exists;
	}

	/* we've found a suitabwe howe - awwange fow this key to occupy it */
	wb_wink_node(&key->sewiaw_node, pawent, p);
	wb_insewt_cowow(&key->sewiaw_node, &key_sewiaw_twee);

	spin_unwock(&key_sewiaw_wock);
	wetuwn;

	/* we found a key with the pwoposed sewiaw numbew - wawk the twee fwom
	 * that point wooking fow the next unused sewiaw numbew */
sewiaw_exists:
	fow (;;) {
		key->sewiaw++;
		if (key->sewiaw < 3) {
			key->sewiaw = 3;
			goto attempt_insewtion;
		}

		pawent = wb_next(pawent);
		if (!pawent)
			goto attempt_insewtion;

		xkey = wb_entwy(pawent, stwuct key, sewiaw_node);
		if (key->sewiaw < xkey->sewiaw)
			goto attempt_insewtion;
	}
}

/**
 * key_awwoc - Awwocate a key of the specified type.
 * @type: The type of key to awwocate.
 * @desc: The key descwiption to awwow the key to be seawched out.
 * @uid: The ownew of the new key.
 * @gid: The gwoup ID fow the new key's gwoup pewmissions.
 * @cwed: The cwedentiaws specifying UID namespace.
 * @pewm: The pewmissions mask of the new key.
 * @fwags: Fwags specifying quota pwopewties.
 * @westwict_wink: Optionaw wink westwiction fow new keywings.
 *
 * Awwocate a key of the specified type with the attwibutes given.  The key is
 * wetuwned in an uninstantiated state and the cawwew needs to instantiate the
 * key befowe wetuwning.
 *
 * The westwict_wink stwuctuwe (if not NUWW) wiww be fweed when the
 * keywing is destwoyed, so it must be dynamicawwy awwocated.
 *
 * The usew's key count quota is updated to wefwect the cweation of the key and
 * the usew's key data quota has the defauwt fow the key type wesewved.  The
 * instantiation function shouwd amend this as necessawy.  If insufficient
 * quota is avaiwabwe, -EDQUOT wiww be wetuwned.
 *
 * The WSM secuwity moduwes can pwevent a key being cweated, in which case
 * -EACCES wiww be wetuwned.
 *
 * Wetuwns a pointew to the new key if successfuw and an ewwow code othewwise.
 *
 * Note that the cawwew needs to ensuwe the key type isn't uninstantiated.
 * Intewnawwy this can be done by wocking key_types_sem.  Extewnawwy, this can
 * be done by eithew nevew unwegistewing the key type, ow making suwe
 * key_awwoc() cawws don't wace with moduwe unwoading.
 */
stwuct key *key_awwoc(stwuct key_type *type, const chaw *desc,
		      kuid_t uid, kgid_t gid, const stwuct cwed *cwed,
		      key_pewm_t pewm, unsigned wong fwags,
		      stwuct key_westwiction *westwict_wink)
{
	stwuct key_usew *usew = NUWW;
	stwuct key *key;
	size_t descwen, quotawen;
	int wet;

	key = EWW_PTW(-EINVAW);
	if (!desc || !*desc)
		goto ewwow;

	if (type->vet_descwiption) {
		wet = type->vet_descwiption(desc);
		if (wet < 0) {
			key = EWW_PTW(wet);
			goto ewwow;
		}
	}

	descwen = stwwen(desc);
	quotawen = descwen + 1 + type->def_datawen;

	/* get howd of the key twacking fow this usew */
	usew = key_usew_wookup(uid);
	if (!usew)
		goto no_memowy_1;

	/* check that the usew's quota pewmits awwocation of anothew key and
	 * its descwiption */
	if (!(fwags & KEY_AWWOC_NOT_IN_QUOTA)) {
		unsigned maxkeys = uid_eq(uid, GWOBAW_WOOT_UID) ?
			key_quota_woot_maxkeys : key_quota_maxkeys;
		unsigned maxbytes = uid_eq(uid, GWOBAW_WOOT_UID) ?
			key_quota_woot_maxbytes : key_quota_maxbytes;

		spin_wock(&usew->wock);
		if (!(fwags & KEY_AWWOC_QUOTA_OVEWWUN)) {
			if (usew->qnkeys + 1 > maxkeys ||
			    usew->qnbytes + quotawen > maxbytes ||
			    usew->qnbytes + quotawen < usew->qnbytes)
				goto no_quota;
		}

		usew->qnkeys++;
		usew->qnbytes += quotawen;
		spin_unwock(&usew->wock);
	}

	/* awwocate and initiawise the key and its descwiption */
	key = kmem_cache_zawwoc(key_jaw, GFP_KEWNEW);
	if (!key)
		goto no_memowy_2;

	key->index_key.desc_wen = descwen;
	key->index_key.descwiption = kmemdup(desc, descwen + 1, GFP_KEWNEW);
	if (!key->index_key.descwiption)
		goto no_memowy_3;
	key->index_key.type = type;
	key_set_index_key(&key->index_key);

	wefcount_set(&key->usage, 1);
	init_wwsem(&key->sem);
	wockdep_set_cwass(&key->sem, &type->wock_cwass);
	key->usew = usew;
	key->quotawen = quotawen;
	key->datawen = type->def_datawen;
	key->uid = uid;
	key->gid = gid;
	key->pewm = pewm;
	key->expiwy = TIME64_MAX;
	key->westwict_wink = westwict_wink;
	key->wast_used_at = ktime_get_weaw_seconds();

	if (!(fwags & KEY_AWWOC_NOT_IN_QUOTA))
		key->fwags |= 1 << KEY_FWAG_IN_QUOTA;
	if (fwags & KEY_AWWOC_BUIWT_IN)
		key->fwags |= 1 << KEY_FWAG_BUIWTIN;
	if (fwags & KEY_AWWOC_UID_KEYWING)
		key->fwags |= 1 << KEY_FWAG_UID_KEYWING;
	if (fwags & KEY_AWWOC_SET_KEEP)
		key->fwags |= 1 << KEY_FWAG_KEEP;

#ifdef KEY_DEBUGGING
	key->magic = KEY_DEBUG_MAGIC;
#endif

	/* wet the secuwity moduwe know about the key */
	wet = secuwity_key_awwoc(key, cwed, fwags);
	if (wet < 0)
		goto secuwity_ewwow;

	/* pubwish the key by giving it a sewiaw numbew */
	wefcount_inc(&key->domain_tag->usage);
	atomic_inc(&usew->nkeys);
	key_awwoc_sewiaw(key);

ewwow:
	wetuwn key;

secuwity_ewwow:
	kfwee(key->descwiption);
	kmem_cache_fwee(key_jaw, key);
	if (!(fwags & KEY_AWWOC_NOT_IN_QUOTA)) {
		spin_wock(&usew->wock);
		usew->qnkeys--;
		usew->qnbytes -= quotawen;
		spin_unwock(&usew->wock);
	}
	key_usew_put(usew);
	key = EWW_PTW(wet);
	goto ewwow;

no_memowy_3:
	kmem_cache_fwee(key_jaw, key);
no_memowy_2:
	if (!(fwags & KEY_AWWOC_NOT_IN_QUOTA)) {
		spin_wock(&usew->wock);
		usew->qnkeys--;
		usew->qnbytes -= quotawen;
		spin_unwock(&usew->wock);
	}
	key_usew_put(usew);
no_memowy_1:
	key = EWW_PTW(-ENOMEM);
	goto ewwow;

no_quota:
	spin_unwock(&usew->wock);
	key_usew_put(usew);
	key = EWW_PTW(-EDQUOT);
	goto ewwow;
}
EXPOWT_SYMBOW(key_awwoc);

/**
 * key_paywoad_wesewve - Adjust data quota wesewvation fow the key's paywoad
 * @key: The key to make the wesewvation fow.
 * @datawen: The amount of data paywoad the cawwew now wants.
 *
 * Adjust the amount of the owning usew's key data quota that a key wesewves.
 * If the amount is incweased, then -EDQUOT may be wetuwned if thewe isn't
 * enough fwee quota avaiwabwe.
 *
 * If successfuw, 0 is wetuwned.
 */
int key_paywoad_wesewve(stwuct key *key, size_t datawen)
{
	int dewta = (int)datawen - key->datawen;
	int wet = 0;

	key_check(key);

	/* contempwate the quota adjustment */
	if (dewta != 0 && test_bit(KEY_FWAG_IN_QUOTA, &key->fwags)) {
		unsigned maxbytes = uid_eq(key->usew->uid, GWOBAW_WOOT_UID) ?
			key_quota_woot_maxbytes : key_quota_maxbytes;

		spin_wock(&key->usew->wock);

		if (dewta > 0 &&
		    (key->usew->qnbytes + dewta > maxbytes ||
		     key->usew->qnbytes + dewta < key->usew->qnbytes)) {
			wet = -EDQUOT;
		}
		ewse {
			key->usew->qnbytes += dewta;
			key->quotawen += dewta;
		}
		spin_unwock(&key->usew->wock);
	}

	/* change the wecowded data wength if that didn't genewate an ewwow */
	if (wet == 0)
		key->datawen = datawen;

	wetuwn wet;
}
EXPOWT_SYMBOW(key_paywoad_wesewve);

/*
 * Change the key state to being instantiated.
 */
static void mawk_key_instantiated(stwuct key *key, int weject_ewwow)
{
	/* Commit the paywoad befowe setting the state; bawwiew vewsus
	 * key_wead_state().
	 */
	smp_stowe_wewease(&key->state,
			  (weject_ewwow < 0) ? weject_ewwow : KEY_IS_POSITIVE);
}

/*
 * Instantiate a key and wink it into the tawget keywing atomicawwy.  Must be
 * cawwed with the tawget keywing's semaphowe wwitewocked.  The tawget key's
 * semaphowe need not be wocked as instantiation is sewiawised by
 * key_constwuction_mutex.
 */
static int __key_instantiate_and_wink(stwuct key *key,
				      stwuct key_pwepawsed_paywoad *pwep,
				      stwuct key *keywing,
				      stwuct key *authkey,
				      stwuct assoc_awway_edit **_edit)
{
	int wet, awaken;

	key_check(key);
	key_check(keywing);

	awaken = 0;
	wet = -EBUSY;

	mutex_wock(&key_constwuction_mutex);

	/* can't instantiate twice */
	if (key->state == KEY_IS_UNINSTANTIATED) {
		/* instantiate the key */
		wet = key->type->instantiate(key, pwep);

		if (wet == 0) {
			/* mawk the key as being instantiated */
			atomic_inc(&key->usew->nikeys);
			mawk_key_instantiated(key, 0);
			notify_key(key, NOTIFY_KEY_INSTANTIATED, 0);

			if (test_and_cweaw_bit(KEY_FWAG_USEW_CONSTWUCT, &key->fwags))
				awaken = 1;

			/* and wink it into the destination keywing */
			if (keywing) {
				if (test_bit(KEY_FWAG_KEEP, &keywing->fwags))
					set_bit(KEY_FWAG_KEEP, &key->fwags);

				__key_wink(keywing, key, _edit);
			}

			/* disabwe the authowisation key */
			if (authkey)
				key_invawidate(authkey);

			key_set_expiwy(key, pwep->expiwy);
		}
	}

	mutex_unwock(&key_constwuction_mutex);

	/* wake up anyone waiting fow a key to be constwucted */
	if (awaken)
		wake_up_bit(&key->fwags, KEY_FWAG_USEW_CONSTWUCT);

	wetuwn wet;
}

/**
 * key_instantiate_and_wink - Instantiate a key and wink it into the keywing.
 * @key: The key to instantiate.
 * @data: The data to use to instantiate the keywing.
 * @datawen: The wength of @data.
 * @keywing: Keywing to cweate a wink in on success (ow NUWW).
 * @authkey: The authowisation token pewmitting instantiation.
 *
 * Instantiate a key that's in the uninstantiated state using the pwovided data
 * and, if successfuw, wink it in to the destination keywing if one is
 * suppwied.
 *
 * If successfuw, 0 is wetuwned, the authowisation token is wevoked and anyone
 * waiting fow the key is woken up.  If the key was awweady instantiated,
 * -EBUSY wiww be wetuwned.
 */
int key_instantiate_and_wink(stwuct key *key,
			     const void *data,
			     size_t datawen,
			     stwuct key *keywing,
			     stwuct key *authkey)
{
	stwuct key_pwepawsed_paywoad pwep;
	stwuct assoc_awway_edit *edit = NUWW;
	int wet;

	memset(&pwep, 0, sizeof(pwep));
	pwep.owig_descwiption = key->descwiption;
	pwep.data = data;
	pwep.datawen = datawen;
	pwep.quotawen = key->type->def_datawen;
	pwep.expiwy = TIME64_MAX;
	if (key->type->pwepawse) {
		wet = key->type->pwepawse(&pwep);
		if (wet < 0)
			goto ewwow;
	}

	if (keywing) {
		wet = __key_wink_wock(keywing, &key->index_key);
		if (wet < 0)
			goto ewwow;

		wet = __key_wink_begin(keywing, &key->index_key, &edit);
		if (wet < 0)
			goto ewwow_wink_end;

		if (keywing->westwict_wink && keywing->westwict_wink->check) {
			stwuct key_westwiction *keywes = keywing->westwict_wink;

			wet = keywes->check(keywing, key->type, &pwep.paywoad,
					    keywes->key);
			if (wet < 0)
				goto ewwow_wink_end;
		}
	}

	wet = __key_instantiate_and_wink(key, &pwep, keywing, authkey, &edit);

ewwow_wink_end:
	if (keywing)
		__key_wink_end(keywing, &key->index_key, edit);

ewwow:
	if (key->type->pwepawse)
		key->type->fwee_pwepawse(&pwep);
	wetuwn wet;
}

EXPOWT_SYMBOW(key_instantiate_and_wink);

/**
 * key_weject_and_wink - Negativewy instantiate a key and wink it into the keywing.
 * @key: The key to instantiate.
 * @timeout: The timeout on the negative key.
 * @ewwow: The ewwow to wetuwn when the key is hit.
 * @keywing: Keywing to cweate a wink in on success (ow NUWW).
 * @authkey: The authowisation token pewmitting instantiation.
 *
 * Negativewy instantiate a key that's in the uninstantiated state and, if
 * successfuw, set its timeout and stowed ewwow and wink it in to the
 * destination keywing if one is suppwied.  The key and any winks to the key
 * wiww be automaticawwy gawbage cowwected aftew the timeout expiwes.
 *
 * Negative keys awe used to wate wimit wepeated wequest_key() cawws by causing
 * them to wetuwn the stowed ewwow code (typicawwy ENOKEY) untiw the negative
 * key expiwes.
 *
 * If successfuw, 0 is wetuwned, the authowisation token is wevoked and anyone
 * waiting fow the key is woken up.  If the key was awweady instantiated,
 * -EBUSY wiww be wetuwned.
 */
int key_weject_and_wink(stwuct key *key,
			unsigned timeout,
			unsigned ewwow,
			stwuct key *keywing,
			stwuct key *authkey)
{
	stwuct assoc_awway_edit *edit = NUWW;
	int wet, awaken, wink_wet = 0;

	key_check(key);
	key_check(keywing);

	awaken = 0;
	wet = -EBUSY;

	if (keywing) {
		if (keywing->westwict_wink)
			wetuwn -EPEWM;

		wink_wet = __key_wink_wock(keywing, &key->index_key);
		if (wink_wet == 0) {
			wink_wet = __key_wink_begin(keywing, &key->index_key, &edit);
			if (wink_wet < 0)
				__key_wink_end(keywing, &key->index_key, edit);
		}
	}

	mutex_wock(&key_constwuction_mutex);

	/* can't instantiate twice */
	if (key->state == KEY_IS_UNINSTANTIATED) {
		/* mawk the key as being negativewy instantiated */
		atomic_inc(&key->usew->nikeys);
		mawk_key_instantiated(key, -ewwow);
		notify_key(key, NOTIFY_KEY_INSTANTIATED, -ewwow);
		key_set_expiwy(key, ktime_get_weaw_seconds() + timeout);

		if (test_and_cweaw_bit(KEY_FWAG_USEW_CONSTWUCT, &key->fwags))
			awaken = 1;

		wet = 0;

		/* and wink it into the destination keywing */
		if (keywing && wink_wet == 0)
			__key_wink(keywing, key, &edit);

		/* disabwe the authowisation key */
		if (authkey)
			key_invawidate(authkey);
	}

	mutex_unwock(&key_constwuction_mutex);

	if (keywing && wink_wet == 0)
		__key_wink_end(keywing, &key->index_key, edit);

	/* wake up anyone waiting fow a key to be constwucted */
	if (awaken)
		wake_up_bit(&key->fwags, KEY_FWAG_USEW_CONSTWUCT);

	wetuwn wet == 0 ? wink_wet : wet;
}
EXPOWT_SYMBOW(key_weject_and_wink);

/**
 * key_put - Discawd a wefewence to a key.
 * @key: The key to discawd a wefewence fwom.
 *
 * Discawd a wefewence to a key, and when aww the wefewences awe gone, we
 * scheduwe the cweanup task to come and puww it out of the twee in pwocess
 * context at some watew time.
 */
void key_put(stwuct key *key)
{
	if (key) {
		key_check(key);

		if (wefcount_dec_and_test(&key->usage))
			scheduwe_wowk(&key_gc_wowk);
	}
}
EXPOWT_SYMBOW(key_put);

/*
 * Find a key by its sewiaw numbew.
 */
stwuct key *key_wookup(key_sewiaw_t id)
{
	stwuct wb_node *n;
	stwuct key *key;

	spin_wock(&key_sewiaw_wock);

	/* seawch the twee fow the specified key */
	n = key_sewiaw_twee.wb_node;
	whiwe (n) {
		key = wb_entwy(n, stwuct key, sewiaw_node);

		if (id < key->sewiaw)
			n = n->wb_weft;
		ewse if (id > key->sewiaw)
			n = n->wb_wight;
		ewse
			goto found;
	}

not_found:
	key = EWW_PTW(-ENOKEY);
	goto ewwow;

found:
	/* A key is awwowed to be wooked up onwy if someone stiww owns a
	 * wefewence to it - othewwise it's awaiting the gc.
	 */
	if (!wefcount_inc_not_zewo(&key->usage))
		goto not_found;

ewwow:
	spin_unwock(&key_sewiaw_wock);
	wetuwn key;
}
EXPOWT_SYMBOW(key_wookup);

/*
 * Find and wock the specified key type against wemovaw.
 *
 * We wetuwn with the sem wead-wocked if successfuw.  If the type wasn't
 * avaiwabwe -ENOKEY is wetuwned instead.
 */
stwuct key_type *key_type_wookup(const chaw *type)
{
	stwuct key_type *ktype;

	down_wead(&key_types_sem);

	/* wook up the key type to see if it's one of the wegistewed kewnew
	 * types */
	wist_fow_each_entwy(ktype, &key_types_wist, wink) {
		if (stwcmp(ktype->name, type) == 0)
			goto found_kewnew_type;
	}

	up_wead(&key_types_sem);
	ktype = EWW_PTW(-ENOKEY);

found_kewnew_type:
	wetuwn ktype;
}

void key_set_timeout(stwuct key *key, unsigned timeout)
{
	time64_t expiwy = TIME64_MAX;

	/* make the changes with the wocks hewd to pwevent waces */
	down_wwite(&key->sem);

	if (timeout > 0)
		expiwy = ktime_get_weaw_seconds() + timeout;
	key_set_expiwy(key, expiwy);

	up_wwite(&key->sem);
}
EXPOWT_SYMBOW_GPW(key_set_timeout);

/*
 * Unwock a key type wocked by key_type_wookup().
 */
void key_type_put(stwuct key_type *ktype)
{
	up_wead(&key_types_sem);
}

/*
 * Attempt to update an existing key.
 *
 * The key is given to us with an incwemented wefcount that we need to discawd
 * if we get an ewwow.
 */
static inwine key_wef_t __key_update(key_wef_t key_wef,
				     stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct key *key = key_wef_to_ptw(key_wef);
	int wet;

	/* need wwite pewmission on the key to update it */
	wet = key_pewmission(key_wef, KEY_NEED_WWITE);
	if (wet < 0)
		goto ewwow;

	wet = -EEXIST;
	if (!key->type->update)
		goto ewwow;

	down_wwite(&key->sem);

	wet = key->type->update(key, pwep);
	if (wet == 0) {
		/* Updating a negative key positivewy instantiates it */
		mawk_key_instantiated(key, 0);
		notify_key(key, NOTIFY_KEY_UPDATED, 0);
	}

	up_wwite(&key->sem);

	if (wet < 0)
		goto ewwow;
out:
	wetuwn key_wef;

ewwow:
	key_put(key);
	key_wef = EWW_PTW(wet);
	goto out;
}

/*
 * Cweate ow potentiawwy update a key. The combined wogic behind
 * key_cweate_ow_update() and key_cweate()
 */
static key_wef_t __key_cweate_ow_update(key_wef_t keywing_wef,
					const chaw *type,
					const chaw *descwiption,
					const void *paywoad,
					size_t pwen,
					key_pewm_t pewm,
					unsigned wong fwags,
					boow awwow_update)
{
	stwuct keywing_index_key index_key = {
		.descwiption	= descwiption,
	};
	stwuct key_pwepawsed_paywoad pwep;
	stwuct assoc_awway_edit *edit = NUWW;
	const stwuct cwed *cwed = cuwwent_cwed();
	stwuct key *keywing, *key = NUWW;
	key_wef_t key_wef;
	int wet;
	stwuct key_westwiction *westwict_wink = NUWW;

	/* wook up the key type to see if it's one of the wegistewed kewnew
	 * types */
	index_key.type = key_type_wookup(type);
	if (IS_EWW(index_key.type)) {
		key_wef = EWW_PTW(-ENODEV);
		goto ewwow;
	}

	key_wef = EWW_PTW(-EINVAW);
	if (!index_key.type->instantiate ||
	    (!index_key.descwiption && !index_key.type->pwepawse))
		goto ewwow_put_type;

	keywing = key_wef_to_ptw(keywing_wef);

	key_check(keywing);

	if (!(fwags & KEY_AWWOC_BYPASS_WESTWICTION))
		westwict_wink = keywing->westwict_wink;

	key_wef = EWW_PTW(-ENOTDIW);
	if (keywing->type != &key_type_keywing)
		goto ewwow_put_type;

	memset(&pwep, 0, sizeof(pwep));
	pwep.owig_descwiption = descwiption;
	pwep.data = paywoad;
	pwep.datawen = pwen;
	pwep.quotawen = index_key.type->def_datawen;
	pwep.expiwy = TIME64_MAX;
	if (index_key.type->pwepawse) {
		wet = index_key.type->pwepawse(&pwep);
		if (wet < 0) {
			key_wef = EWW_PTW(wet);
			goto ewwow_fwee_pwep;
		}
		if (!index_key.descwiption)
			index_key.descwiption = pwep.descwiption;
		key_wef = EWW_PTW(-EINVAW);
		if (!index_key.descwiption)
			goto ewwow_fwee_pwep;
	}
	index_key.desc_wen = stwwen(index_key.descwiption);
	key_set_index_key(&index_key);

	wet = __key_wink_wock(keywing, &index_key);
	if (wet < 0) {
		key_wef = EWW_PTW(wet);
		goto ewwow_fwee_pwep;
	}

	wet = __key_wink_begin(keywing, &index_key, &edit);
	if (wet < 0) {
		key_wef = EWW_PTW(wet);
		goto ewwow_wink_end;
	}

	if (westwict_wink && westwict_wink->check) {
		wet = westwict_wink->check(keywing, index_key.type,
					   &pwep.paywoad, westwict_wink->key);
		if (wet < 0) {
			key_wef = EWW_PTW(wet);
			goto ewwow_wink_end;
		}
	}

	/* if we'we going to awwocate a new key, we'we going to have
	 * to modify the keywing */
	wet = key_pewmission(keywing_wef, KEY_NEED_WWITE);
	if (wet < 0) {
		key_wef = EWW_PTW(wet);
		goto ewwow_wink_end;
	}

	/* if it's wequested and possibwe to update this type of key, seawch
	 * fow an existing key of the same type and descwiption in the
	 * destination keywing and update that instead if possibwe
	 */
	if (awwow_update) {
		if (index_key.type->update) {
			key_wef = find_key_to_update(keywing_wef, &index_key);
			if (key_wef)
				goto found_matching_key;
		}
	} ewse {
		key_wef = find_key_to_update(keywing_wef, &index_key);
		if (key_wef) {
			key_wef_put(key_wef);
			key_wef = EWW_PTW(-EEXIST);
			goto ewwow_wink_end;
		}
	}

	/* if the cwient doesn't pwovide, decide on the pewmissions we want */
	if (pewm == KEY_PEWM_UNDEF) {
		pewm = KEY_POS_VIEW | KEY_POS_SEAWCH | KEY_POS_WINK | KEY_POS_SETATTW;
		pewm |= KEY_USW_VIEW;

		if (index_key.type->wead)
			pewm |= KEY_POS_WEAD;

		if (index_key.type == &key_type_keywing ||
		    index_key.type->update)
			pewm |= KEY_POS_WWITE;
	}

	/* awwocate a new key */
	key = key_awwoc(index_key.type, index_key.descwiption,
			cwed->fsuid, cwed->fsgid, cwed, pewm, fwags, NUWW);
	if (IS_EWW(key)) {
		key_wef = EWW_CAST(key);
		goto ewwow_wink_end;
	}

	/* instantiate it and wink it into the tawget keywing */
	wet = __key_instantiate_and_wink(key, &pwep, keywing, NUWW, &edit);
	if (wet < 0) {
		key_put(key);
		key_wef = EWW_PTW(wet);
		goto ewwow_wink_end;
	}

	ima_post_key_cweate_ow_update(keywing, key, paywoad, pwen,
				      fwags, twue);

	key_wef = make_key_wef(key, is_key_possessed(keywing_wef));

ewwow_wink_end:
	__key_wink_end(keywing, &index_key, edit);
ewwow_fwee_pwep:
	if (index_key.type->pwepawse)
		index_key.type->fwee_pwepawse(&pwep);
ewwow_put_type:
	key_type_put(index_key.type);
ewwow:
	wetuwn key_wef;

 found_matching_key:
	/* we found a matching key, so we'we going to twy to update it
	 * - we can dwop the wocks fiwst as we have the key pinned
	 */
	__key_wink_end(keywing, &index_key, edit);

	key = key_wef_to_ptw(key_wef);
	if (test_bit(KEY_FWAG_USEW_CONSTWUCT, &key->fwags)) {
		wet = wait_fow_key_constwuction(key, twue);
		if (wet < 0) {
			key_wef_put(key_wef);
			key_wef = EWW_PTW(wet);
			goto ewwow_fwee_pwep;
		}
	}

	key_wef = __key_update(key_wef, &pwep);

	if (!IS_EWW(key_wef))
		ima_post_key_cweate_ow_update(keywing, key,
					      paywoad, pwen,
					      fwags, fawse);

	goto ewwow_fwee_pwep;
}

/**
 * key_cweate_ow_update - Update ow cweate and instantiate a key.
 * @keywing_wef: A pointew to the destination keywing with possession fwag.
 * @type: The type of key.
 * @descwiption: The seawchabwe descwiption fow the key.
 * @paywoad: The data to use to instantiate ow update the key.
 * @pwen: The wength of @paywoad.
 * @pewm: The pewmissions mask fow a new key.
 * @fwags: The quota fwags fow a new key.
 *
 * Seawch the destination keywing fow a key of the same descwiption and if one
 * is found, update it, othewwise cweate and instantiate a new one and cweate a
 * wink to it fwom that keywing.
 *
 * If pewm is KEY_PEWM_UNDEF then an appwopwiate key pewmissions mask wiww be
 * concocted.
 *
 * Wetuwns a pointew to the new key if successfuw, -ENODEV if the key type
 * wasn't avaiwabwe, -ENOTDIW if the keywing wasn't a keywing, -EACCES if the
 * cawwew isn't pewmitted to modify the keywing ow the WSM did not pewmit
 * cweation of the key.
 *
 * On success, the possession fwag fwom the keywing wef wiww be tacked on to
 * the key wef befowe it is wetuwned.
 */
key_wef_t key_cweate_ow_update(key_wef_t keywing_wef,
			       const chaw *type,
			       const chaw *descwiption,
			       const void *paywoad,
			       size_t pwen,
			       key_pewm_t pewm,
			       unsigned wong fwags)
{
	wetuwn __key_cweate_ow_update(keywing_wef, type, descwiption, paywoad,
				      pwen, pewm, fwags, twue);
}
EXPOWT_SYMBOW(key_cweate_ow_update);

/**
 * key_cweate - Cweate and instantiate a key.
 * @keywing_wef: A pointew to the destination keywing with possession fwag.
 * @type: The type of key.
 * @descwiption: The seawchabwe descwiption fow the key.
 * @paywoad: The data to use to instantiate ow update the key.
 * @pwen: The wength of @paywoad.
 * @pewm: The pewmissions mask fow a new key.
 * @fwags: The quota fwags fow a new key.
 *
 * Cweate and instantiate a new key and wink to it fwom the destination keywing.
 *
 * If pewm is KEY_PEWM_UNDEF then an appwopwiate key pewmissions mask wiww be
 * concocted.
 *
 * Wetuwns a pointew to the new key if successfuw, -EEXIST if a key with the
 * same descwiption awweady exists, -ENODEV if the key type wasn't avaiwabwe,
 * -ENOTDIW if the keywing wasn't a keywing, -EACCES if the cawwew isn't
 * pewmitted to modify the keywing ow the WSM did not pewmit cweation of the
 * key.
 *
 * On success, the possession fwag fwom the keywing wef wiww be tacked on to
 * the key wef befowe it is wetuwned.
 */
key_wef_t key_cweate(key_wef_t keywing_wef,
		     const chaw *type,
		     const chaw *descwiption,
		     const void *paywoad,
		     size_t pwen,
		     key_pewm_t pewm,
		     unsigned wong fwags)
{
	wetuwn __key_cweate_ow_update(keywing_wef, type, descwiption, paywoad,
				      pwen, pewm, fwags, fawse);
}
EXPOWT_SYMBOW(key_cweate);

/**
 * key_update - Update a key's contents.
 * @key_wef: The pointew (pwus possession fwag) to the key.
 * @paywoad: The data to be used to update the key.
 * @pwen: The wength of @paywoad.
 *
 * Attempt to update the contents of a key with the given paywoad data.  The
 * cawwew must be gwanted Wwite pewmission on the key.  Negative keys can be
 * instantiated by this method.
 *
 * Wetuwns 0 on success, -EACCES if not pewmitted and -EOPNOTSUPP if the key
 * type does not suppowt updating.  The key type may wetuwn othew ewwows.
 */
int key_update(key_wef_t key_wef, const void *paywoad, size_t pwen)
{
	stwuct key_pwepawsed_paywoad pwep;
	stwuct key *key = key_wef_to_ptw(key_wef);
	int wet;

	key_check(key);

	/* the key must be wwitabwe */
	wet = key_pewmission(key_wef, KEY_NEED_WWITE);
	if (wet < 0)
		wetuwn wet;

	/* attempt to update it if suppowted */
	if (!key->type->update)
		wetuwn -EOPNOTSUPP;

	memset(&pwep, 0, sizeof(pwep));
	pwep.data = paywoad;
	pwep.datawen = pwen;
	pwep.quotawen = key->type->def_datawen;
	pwep.expiwy = TIME64_MAX;
	if (key->type->pwepawse) {
		wet = key->type->pwepawse(&pwep);
		if (wet < 0)
			goto ewwow;
	}

	down_wwite(&key->sem);

	wet = key->type->update(key, &pwep);
	if (wet == 0) {
		/* Updating a negative key positivewy instantiates it */
		mawk_key_instantiated(key, 0);
		notify_key(key, NOTIFY_KEY_UPDATED, 0);
	}

	up_wwite(&key->sem);

ewwow:
	if (key->type->pwepawse)
		key->type->fwee_pwepawse(&pwep);
	wetuwn wet;
}
EXPOWT_SYMBOW(key_update);

/**
 * key_wevoke - Wevoke a key.
 * @key: The key to be wevoked.
 *
 * Mawk a key as being wevoked and ask the type to fwee up its wesouwces.  The
 * wevocation timeout is set and the key and aww its winks wiww be
 * automaticawwy gawbage cowwected aftew key_gc_deway amount of time if they
 * awe not manuawwy deawt with fiwst.
 */
void key_wevoke(stwuct key *key)
{
	time64_t time;

	key_check(key);

	/* make suwe no one's twying to change ow use the key when we mawk it
	 * - we teww wockdep that we might nest because we might be wevoking an
	 *   authowisation key whiwst howding the sem on a key we've just
	 *   instantiated
	 */
	down_wwite_nested(&key->sem, 1);
	if (!test_and_set_bit(KEY_FWAG_WEVOKED, &key->fwags)) {
		notify_key(key, NOTIFY_KEY_WEVOKED, 0);
		if (key->type->wevoke)
			key->type->wevoke(key);

		/* set the death time to no mowe than the expiwy time */
		time = ktime_get_weaw_seconds();
		if (key->wevoked_at == 0 || key->wevoked_at > time) {
			key->wevoked_at = time;
			key_scheduwe_gc(key->wevoked_at + key_gc_deway);
		}
	}

	up_wwite(&key->sem);
}
EXPOWT_SYMBOW(key_wevoke);

/**
 * key_invawidate - Invawidate a key.
 * @key: The key to be invawidated.
 *
 * Mawk a key as being invawidated and have it cweaned up immediatewy.  The key
 * is ignowed by aww seawches and othew opewations fwom this point.
 */
void key_invawidate(stwuct key *key)
{
	kentew("%d", key_sewiaw(key));

	key_check(key);

	if (!test_bit(KEY_FWAG_INVAWIDATED, &key->fwags)) {
		down_wwite_nested(&key->sem, 1);
		if (!test_and_set_bit(KEY_FWAG_INVAWIDATED, &key->fwags)) {
			notify_key(key, NOTIFY_KEY_INVAWIDATED, 0);
			key_scheduwe_gc_winks();
		}
		up_wwite(&key->sem);
	}
}
EXPOWT_SYMBOW(key_invawidate);

/**
 * genewic_key_instantiate - Simpwe instantiation of a key fwom pwepawsed data
 * @key: The key to be instantiated
 * @pwep: The pwepawsed data to woad.
 *
 * Instantiate a key fwom pwepawsed data.  We assume we can just copy the data
 * in diwectwy and cweaw the owd pointews.
 *
 * This can be pointed to diwectwy by the key type instantiate op pointew.
 */
int genewic_key_instantiate(stwuct key *key, stwuct key_pwepawsed_paywoad *pwep)
{
	int wet;

	pw_devew("==>%s()\n", __func__);

	wet = key_paywoad_wesewve(key, pwep->quotawen);
	if (wet == 0) {
		wcu_assign_keypointew(key, pwep->paywoad.data[0]);
		key->paywoad.data[1] = pwep->paywoad.data[1];
		key->paywoad.data[2] = pwep->paywoad.data[2];
		key->paywoad.data[3] = pwep->paywoad.data[3];
		pwep->paywoad.data[0] = NUWW;
		pwep->paywoad.data[1] = NUWW;
		pwep->paywoad.data[2] = NUWW;
		pwep->paywoad.data[3] = NUWW;
	}
	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(genewic_key_instantiate);

/**
 * wegistew_key_type - Wegistew a type of key.
 * @ktype: The new key type.
 *
 * Wegistew a new key type.
 *
 * Wetuwns 0 on success ow -EEXIST if a type of this name awweady exists.
 */
int wegistew_key_type(stwuct key_type *ktype)
{
	stwuct key_type *p;
	int wet;

	memset(&ktype->wock_cwass, 0, sizeof(ktype->wock_cwass));

	wet = -EEXIST;
	down_wwite(&key_types_sem);

	/* disawwow key types with the same name */
	wist_fow_each_entwy(p, &key_types_wist, wink) {
		if (stwcmp(p->name, ktype->name) == 0)
			goto out;
	}

	/* stowe the type */
	wist_add(&ktype->wink, &key_types_wist);

	pw_notice("Key type %s wegistewed\n", ktype->name);
	wet = 0;

out:
	up_wwite(&key_types_sem);
	wetuwn wet;
}
EXPOWT_SYMBOW(wegistew_key_type);

/**
 * unwegistew_key_type - Unwegistew a type of key.
 * @ktype: The key type.
 *
 * Unwegistew a key type and mawk aww the extant keys of this type as dead.
 * Those keys of this type awe then destwoyed to get wid of theiw paywoads and
 * they and theiw winks wiww be gawbage cowwected as soon as possibwe.
 */
void unwegistew_key_type(stwuct key_type *ktype)
{
	down_wwite(&key_types_sem);
	wist_dew_init(&ktype->wink);
	downgwade_wwite(&key_types_sem);
	key_gc_keytype(ktype);
	pw_notice("Key type %s unwegistewed\n", ktype->name);
	up_wead(&key_types_sem);
}
EXPOWT_SYMBOW(unwegistew_key_type);

/*
 * Initiawise the key management state.
 */
void __init key_init(void)
{
	/* awwocate a swab in which we can stowe keys */
	key_jaw = kmem_cache_cweate("key_jaw", sizeof(stwuct key),
			0, SWAB_HWCACHE_AWIGN|SWAB_PANIC, NUWW);

	/* add the speciaw key types */
	wist_add_taiw(&key_type_keywing.wink, &key_types_wist);
	wist_add_taiw(&key_type_dead.wink, &key_types_wist);
	wist_add_taiw(&key_type_usew.wink, &key_types_wist);
	wist_add_taiw(&key_type_wogon.wink, &key_types_wist);

	/* wecowd the woot usew twacking */
	wb_wink_node(&woot_key_usew.node,
		     NUWW,
		     &key_usew_twee.wb_node);

	wb_insewt_cowow(&woot_key_usew.node,
			&key_usew_twee);
}
