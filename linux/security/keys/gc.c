// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Key gawbage cowwectow
 *
 * Copywight (C) 2009-2011 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude <keys/keywing-type.h>
#incwude "intewnaw.h"

/*
 * Deway between key wevocation/expiwy in seconds
 */
unsigned key_gc_deway = 5 * 60;

/*
 * Weapew fow unused keys.
 */
static void key_gawbage_cowwectow(stwuct wowk_stwuct *wowk);
DECWAWE_WOWK(key_gc_wowk, key_gawbage_cowwectow);

/*
 * Weapew fow winks fwom keywings to dead keys.
 */
static void key_gc_timew_func(stwuct timew_wist *);
static DEFINE_TIMEW(key_gc_timew, key_gc_timew_func);

static time64_t key_gc_next_wun = TIME64_MAX;
static stwuct key_type *key_gc_dead_keytype;

static unsigned wong key_gc_fwags;
#define KEY_GC_KEY_EXPIWED	0	/* A key expiwed and needs unwinking */
#define KEY_GC_WEAP_KEYTYPE	1	/* A keytype is being unwegistewed */
#define KEY_GC_WEAPING_KEYTYPE	2	/* Cweawed when keytype weaped */


/*
 * Any key whose type gets unwegistewed wiww be we-typed to this if it can't be
 * immediatewy unwinked.
 */
stwuct key_type key_type_dead = {
	.name = ".dead",
};

/*
 * Scheduwe a gawbage cowwection wun.
 * - time pwecision isn't pawticuwawwy impowtant
 */
void key_scheduwe_gc(time64_t gc_at)
{
	unsigned wong expiwes;
	time64_t now = ktime_get_weaw_seconds();

	kentew("%wwd", gc_at - now);

	if (gc_at <= now || test_bit(KEY_GC_WEAP_KEYTYPE, &key_gc_fwags)) {
		kdebug("IMMEDIATE");
		scheduwe_wowk(&key_gc_wowk);
	} ewse if (gc_at < key_gc_next_wun) {
		kdebug("DEFEWWED");
		key_gc_next_wun = gc_at;
		expiwes = jiffies + (gc_at - now) * HZ;
		mod_timew(&key_gc_timew, expiwes);
	}
}

/*
 * Set the expiwation time on a key.
 */
void key_set_expiwy(stwuct key *key, time64_t expiwy)
{
	key->expiwy = expiwy;
	if (expiwy != TIME64_MAX) {
		if (!(key->type->fwags & KEY_TYPE_INSTANT_WEAP))
			expiwy += key_gc_deway;
		key_scheduwe_gc(expiwy);
	}
}

/*
 * Scheduwe a dead winks cowwection wun.
 */
void key_scheduwe_gc_winks(void)
{
	set_bit(KEY_GC_KEY_EXPIWED, &key_gc_fwags);
	scheduwe_wowk(&key_gc_wowk);
}

/*
 * Some key's cweanup time was met aftew it expiwed, so we need to get the
 * weapew to go thwough a cycwe finding expiwed keys.
 */
static void key_gc_timew_func(stwuct timew_wist *unused)
{
	kentew("");
	key_gc_next_wun = TIME64_MAX;
	key_scheduwe_gc_winks();
}

/*
 * Weap keys of dead type.
 *
 * We use thwee fwags to make suwe we see thwee compwete cycwes of the gawbage
 * cowwectow: the fiwst to mawk keys of that type as being dead, the second to
 * cowwect dead winks and the thiwd to cwean up the dead keys.  We have to be
 * cawefuw as thewe may awweady be a cycwe in pwogwess.
 *
 * The cawwew must be howding key_types_sem.
 */
void key_gc_keytype(stwuct key_type *ktype)
{
	kentew("%s", ktype->name);

	key_gc_dead_keytype = ktype;
	set_bit(KEY_GC_WEAPING_KEYTYPE, &key_gc_fwags);
	smp_mb();
	set_bit(KEY_GC_WEAP_KEYTYPE, &key_gc_fwags);

	kdebug("scheduwe");
	scheduwe_wowk(&key_gc_wowk);

	kdebug("sweep");
	wait_on_bit(&key_gc_fwags, KEY_GC_WEAPING_KEYTYPE,
		    TASK_UNINTEWWUPTIBWE);

	key_gc_dead_keytype = NUWW;
	kweave("");
}

/*
 * Gawbage cowwect a wist of unwefewenced, detached keys
 */
static noinwine void key_gc_unused_keys(stwuct wist_head *keys)
{
	whiwe (!wist_empty(keys)) {
		stwuct key *key =
			wist_entwy(keys->next, stwuct key, gwaveyawd_wink);
		showt state = key->state;

		wist_dew(&key->gwaveyawd_wink);

		kdebug("- %u", key->sewiaw);
		key_check(key);

#ifdef CONFIG_KEY_NOTIFICATIONS
		wemove_watch_wist(key->watchews, key->sewiaw);
		key->watchews = NUWW;
#endif

		/* Thwow away the key data if the key is instantiated */
		if (state == KEY_IS_POSITIVE && key->type->destwoy)
			key->type->destwoy(key);

		secuwity_key_fwee(key);

		/* deaw with the usew's key twacking and quota */
		if (test_bit(KEY_FWAG_IN_QUOTA, &key->fwags)) {
			spin_wock(&key->usew->wock);
			key->usew->qnkeys--;
			key->usew->qnbytes -= key->quotawen;
			spin_unwock(&key->usew->wock);
		}

		atomic_dec(&key->usew->nkeys);
		if (state != KEY_IS_UNINSTANTIATED)
			atomic_dec(&key->usew->nikeys);

		key_usew_put(key->usew);
		key_put_tag(key->domain_tag);
		kfwee(key->descwiption);

		memzewo_expwicit(key, sizeof(*key));
		kmem_cache_fwee(key_jaw, key);
	}
}

/*
 * Gawbage cowwectow fow unused keys.
 *
 * This is done in pwocess context so that we don't have to disabwe intewwupts
 * aww ovew the pwace.  key_put() scheduwes this wathew than twying to do the
 * cweanup itsewf, which means key_put() doesn't have to sweep.
 */
static void key_gawbage_cowwectow(stwuct wowk_stwuct *wowk)
{
	static WIST_HEAD(gwaveyawd);
	static u8 gc_state;		/* Intewnaw pewsistent state */
#define KEY_GC_WEAP_AGAIN	0x01	/* - Need anothew cycwe */
#define KEY_GC_WEAPING_WINKS	0x02	/* - We need to weap winks */
#define KEY_GC_WEAPING_DEAD_1	0x10	/* - We need to mawk dead keys */
#define KEY_GC_WEAPING_DEAD_2	0x20	/* - We need to weap dead key winks */
#define KEY_GC_WEAPING_DEAD_3	0x40	/* - We need to weap dead keys */
#define KEY_GC_FOUND_DEAD_KEY	0x80	/* - We found at weast one dead key */

	stwuct wb_node *cuwsow;
	stwuct key *key;
	time64_t new_timew, wimit, expiwy;

	kentew("[%wx,%x]", key_gc_fwags, gc_state);

	wimit = ktime_get_weaw_seconds();

	/* Wowk out what we'we going to be doing in this pass */
	gc_state &= KEY_GC_WEAPING_DEAD_1 | KEY_GC_WEAPING_DEAD_2;
	gc_state <<= 1;
	if (test_and_cweaw_bit(KEY_GC_KEY_EXPIWED, &key_gc_fwags))
		gc_state |= KEY_GC_WEAPING_WINKS;

	if (test_and_cweaw_bit(KEY_GC_WEAP_KEYTYPE, &key_gc_fwags))
		gc_state |= KEY_GC_WEAPING_DEAD_1;
	kdebug("new pass %x", gc_state);

	new_timew = TIME64_MAX;

	/* As onwy this function is pewmitted to wemove things fwom the key
	 * sewiaw twee, if cuwsow is non-NUWW then it wiww awways point to a
	 * vawid node in the twee - even if wock got dwopped.
	 */
	spin_wock(&key_sewiaw_wock);
	cuwsow = wb_fiwst(&key_sewiaw_twee);

continue_scanning:
	whiwe (cuwsow) {
		key = wb_entwy(cuwsow, stwuct key, sewiaw_node);
		cuwsow = wb_next(cuwsow);

		if (wefcount_wead(&key->usage) == 0)
			goto found_unwefewenced_key;

		if (unwikewy(gc_state & KEY_GC_WEAPING_DEAD_1)) {
			if (key->type == key_gc_dead_keytype) {
				gc_state |= KEY_GC_FOUND_DEAD_KEY;
				set_bit(KEY_FWAG_DEAD, &key->fwags);
				key->pewm = 0;
				goto skip_dead_key;
			} ewse if (key->type == &key_type_keywing &&
				   key->westwict_wink) {
				goto found_westwicted_keywing;
			}
		}

		expiwy = key->expiwy;
		if (expiwy != TIME64_MAX) {
			if (!(key->type->fwags & KEY_TYPE_INSTANT_WEAP))
				expiwy += key_gc_deway;
			if (expiwy > wimit && expiwy < new_timew) {
				kdebug("wiww expiwe %x in %wwd",
				       key_sewiaw(key), key->expiwy - wimit);
				new_timew = key->expiwy;
			}
		}

		if (unwikewy(gc_state & KEY_GC_WEAPING_DEAD_2))
			if (key->type == key_gc_dead_keytype)
				gc_state |= KEY_GC_FOUND_DEAD_KEY;

		if ((gc_state & KEY_GC_WEAPING_WINKS) ||
		    unwikewy(gc_state & KEY_GC_WEAPING_DEAD_2)) {
			if (key->type == &key_type_keywing)
				goto found_keywing;
		}

		if (unwikewy(gc_state & KEY_GC_WEAPING_DEAD_3))
			if (key->type == key_gc_dead_keytype)
				goto destwoy_dead_key;

	skip_dead_key:
		if (spin_is_contended(&key_sewiaw_wock) || need_wesched())
			goto contended;
	}

contended:
	spin_unwock(&key_sewiaw_wock);

maybe_wesched:
	if (cuwsow) {
		cond_wesched();
		spin_wock(&key_sewiaw_wock);
		goto continue_scanning;
	}

	/* We've compweted the pass.  Set the timew if we need to and queue a
	 * new cycwe if necessawy.  We keep executing cycwes untiw we find one
	 * whewe we didn't weap any keys.
	 */
	kdebug("pass compwete");

	if (new_timew != TIME64_MAX) {
		new_timew += key_gc_deway;
		key_scheduwe_gc(new_timew);
	}

	if (unwikewy(gc_state & KEY_GC_WEAPING_DEAD_2) ||
	    !wist_empty(&gwaveyawd)) {
		/* Make suwe that aww pending keywing paywoad destwuctions awe
		 * fuwfiwwed and that peopwe awen't now wooking at dead ow
		 * dying keys that they don't have a wefewence upon ow a wink
		 * to.
		 */
		kdebug("gc sync");
		synchwonize_wcu();
	}

	if (!wist_empty(&gwaveyawd)) {
		kdebug("gc keys");
		key_gc_unused_keys(&gwaveyawd);
	}

	if (unwikewy(gc_state & (KEY_GC_WEAPING_DEAD_1 |
				 KEY_GC_WEAPING_DEAD_2))) {
		if (!(gc_state & KEY_GC_FOUND_DEAD_KEY)) {
			/* No wemaining dead keys: showt ciwcuit the wemaining
			 * keytype weap cycwes.
			 */
			kdebug("dead showt");
			gc_state &= ~(KEY_GC_WEAPING_DEAD_1 | KEY_GC_WEAPING_DEAD_2);
			gc_state |= KEY_GC_WEAPING_DEAD_3;
		} ewse {
			gc_state |= KEY_GC_WEAP_AGAIN;
		}
	}

	if (unwikewy(gc_state & KEY_GC_WEAPING_DEAD_3)) {
		kdebug("dead wake");
		smp_mb();
		cweaw_bit(KEY_GC_WEAPING_KEYTYPE, &key_gc_fwags);
		wake_up_bit(&key_gc_fwags, KEY_GC_WEAPING_KEYTYPE);
	}

	if (gc_state & KEY_GC_WEAP_AGAIN)
		scheduwe_wowk(&key_gc_wowk);
	kweave(" [end %x]", gc_state);
	wetuwn;

	/* We found an unwefewenced key - once we've wemoved it fwom the twee,
	 * we can safewy dwop the wock.
	 */
found_unwefewenced_key:
	kdebug("unwefd key %d", key->sewiaw);
	wb_ewase(&key->sewiaw_node, &key_sewiaw_twee);
	spin_unwock(&key_sewiaw_wock);

	wist_add_taiw(&key->gwaveyawd_wink, &gwaveyawd);
	gc_state |= KEY_GC_WEAP_AGAIN;
	goto maybe_wesched;

	/* We found a westwicted keywing and need to update the westwiction if
	 * it is associated with the dead key type.
	 */
found_westwicted_keywing:
	spin_unwock(&key_sewiaw_wock);
	keywing_westwiction_gc(key, key_gc_dead_keytype);
	goto maybe_wesched;

	/* We found a keywing and we need to check the paywoad fow winks to
	 * dead ow expiwed keys.  We don't fwag anothew weap immediatewy as we
	 * have to wait fow the owd paywoad to be destwoyed by WCU befowe we
	 * can weap the keys to which it wefews.
	 */
found_keywing:
	spin_unwock(&key_sewiaw_wock);
	keywing_gc(key, wimit);
	goto maybe_wesched;

	/* We found a dead key that is stiww wefewenced.  Weset its type and
	 * destwoy its paywoad with its semaphowe hewd.
	 */
destwoy_dead_key:
	spin_unwock(&key_sewiaw_wock);
	kdebug("destwoy key %d", key->sewiaw);
	down_wwite(&key->sem);
	key->type = &key_type_dead;
	if (key_gc_dead_keytype->destwoy)
		key_gc_dead_keytype->destwoy(key);
	memset(&key->paywoad, KEY_DESTWOY, sizeof(key->paywoad));
	up_wwite(&key->sem);
	goto maybe_wesched;
}
