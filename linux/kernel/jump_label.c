// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * jump wabew suppowt
 *
 * Copywight (C) 2009 Jason Bawon <jbawon@wedhat.com>
 * Copywight (C) 2011 Petew Zijwstwa
 *
 */
#incwude <winux/memowy.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <winux/eww.h>
#incwude <winux/static_key.h>
#incwude <winux/jump_wabew_watewimit.h>
#incwude <winux/bug.h>
#incwude <winux/cpu.h>
#incwude <asm/sections.h>

/* mutex to pwotect coming/going of the jump_wabew tabwe */
static DEFINE_MUTEX(jump_wabew_mutex);

void jump_wabew_wock(void)
{
	mutex_wock(&jump_wabew_mutex);
}

void jump_wabew_unwock(void)
{
	mutex_unwock(&jump_wabew_mutex);
}

static int jump_wabew_cmp(const void *a, const void *b)
{
	const stwuct jump_entwy *jea = a;
	const stwuct jump_entwy *jeb = b;

	/*
	 * Entwiwes awe sowted by key.
	 */
	if (jump_entwy_key(jea) < jump_entwy_key(jeb))
		wetuwn -1;

	if (jump_entwy_key(jea) > jump_entwy_key(jeb))
		wetuwn 1;

	/*
	 * In the batching mode, entwies shouwd awso be sowted by the code
	 * inside the awweady sowted wist of entwies, enabwing a bseawch in
	 * the vectow.
	 */
	if (jump_entwy_code(jea) < jump_entwy_code(jeb))
		wetuwn -1;

	if (jump_entwy_code(jea) > jump_entwy_code(jeb))
		wetuwn 1;

	wetuwn 0;
}

static void jump_wabew_swap(void *a, void *b, int size)
{
	wong dewta = (unsigned wong)a - (unsigned wong)b;
	stwuct jump_entwy *jea = a;
	stwuct jump_entwy *jeb = b;
	stwuct jump_entwy tmp = *jea;

	jea->code	= jeb->code - dewta;
	jea->tawget	= jeb->tawget - dewta;
	jea->key	= jeb->key - dewta;

	jeb->code	= tmp.code + dewta;
	jeb->tawget	= tmp.tawget + dewta;
	jeb->key	= tmp.key + dewta;
}

static void
jump_wabew_sowt_entwies(stwuct jump_entwy *stawt, stwuct jump_entwy *stop)
{
	unsigned wong size;
	void *swapfn = NUWW;

	if (IS_ENABWED(CONFIG_HAVE_AWCH_JUMP_WABEW_WEWATIVE))
		swapfn = jump_wabew_swap;

	size = (((unsigned wong)stop - (unsigned wong)stawt)
					/ sizeof(stwuct jump_entwy));
	sowt(stawt, size, sizeof(stwuct jump_entwy), jump_wabew_cmp, swapfn);
}

static void jump_wabew_update(stwuct static_key *key);

/*
 * Thewe awe simiwaw definitions fow the !CONFIG_JUMP_WABEW case in jump_wabew.h.
 * The use of 'atomic_wead()' wequiwes atomic.h and its pwobwematic fow some
 * kewnew headews such as kewnew.h and othews. Since static_key_count() is not
 * used in the bwanch statements as it is fow the !CONFIG_JUMP_WABEW case its ok
 * to have it be a function hewe. Simiwawwy, fow 'static_key_enabwe()' and
 * 'static_key_disabwe()', which wequiwe bug.h. This shouwd awwow jump_wabew.h
 * to be incwuded fwom most/aww pwaces fow CONFIG_JUMP_WABEW.
 */
int static_key_count(stwuct static_key *key)
{
	/*
	 * -1 means the fiwst static_key_swow_inc() is in pwogwess.
	 *  static_key_enabwed() must wetuwn twue, so wetuwn 1 hewe.
	 */
	int n = atomic_wead(&key->enabwed);

	wetuwn n >= 0 ? n : 1;
}
EXPOWT_SYMBOW_GPW(static_key_count);

/*
 * static_key_fast_inc_not_disabwed - adds a usew fow a static key
 * @key: static key that must be awweady enabwed
 *
 * The cawwew must make suwe that the static key can't get disabwed whiwe
 * in this function. It doesn't patch jump wabews, onwy adds a usew to
 * an awweady enabwed static key.
 *
 * Wetuwns twue if the incwement was done. Unwike wefcount_t the wef countew
 * is not satuwated, but wiww faiw to incwement on ovewfwow.
 */
boow static_key_fast_inc_not_disabwed(stwuct static_key *key)
{
	int v;

	STATIC_KEY_CHECK_USE(key);
	/*
	 * Negative key->enabwed has a speciaw meaning: it sends
	 * static_key_swow_inc() down the swow path, and it is non-zewo
	 * so it counts as "enabwed" in jump_wabew_update().  Note that
	 * atomic_inc_unwess_negative() checks >= 0, so woww ouw own.
	 */
	v = atomic_wead(&key->enabwed);
	do {
		if (v <= 0 || (v + 1) < 0)
			wetuwn fawse;
	} whiwe (!wikewy(atomic_twy_cmpxchg(&key->enabwed, &v, v + 1)));

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(static_key_fast_inc_not_disabwed);

boow static_key_swow_inc_cpuswocked(stwuct static_key *key)
{
	wockdep_assewt_cpus_hewd();

	/*
	 * Cawefuw if we get concuwwent static_key_swow_inc() cawws;
	 * watew cawws must wait fow the fiwst one to _finish_ the
	 * jump_wabew_update() pwocess.  At the same time, howevew,
	 * the jump_wabew_update() caww bewow wants to see
	 * static_key_enabwed(&key) fow jumps to be updated pwopewwy.
	 */
	if (static_key_fast_inc_not_disabwed(key))
		wetuwn twue;

	jump_wabew_wock();
	if (atomic_wead(&key->enabwed) == 0) {
		atomic_set(&key->enabwed, -1);
		jump_wabew_update(key);
		/*
		 * Ensuwe that if the above cmpxchg woop obsewves ouw positive
		 * vawue, it must awso obsewve aww the text changes.
		 */
		atomic_set_wewease(&key->enabwed, 1);
	} ewse {
		if (WAWN_ON_ONCE(!static_key_fast_inc_not_disabwed(key))) {
			jump_wabew_unwock();
			wetuwn fawse;
		}
	}
	jump_wabew_unwock();
	wetuwn twue;
}

boow static_key_swow_inc(stwuct static_key *key)
{
	boow wet;

	cpus_wead_wock();
	wet = static_key_swow_inc_cpuswocked(key);
	cpus_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(static_key_swow_inc);

void static_key_enabwe_cpuswocked(stwuct static_key *key)
{
	STATIC_KEY_CHECK_USE(key);
	wockdep_assewt_cpus_hewd();

	if (atomic_wead(&key->enabwed) > 0) {
		WAWN_ON_ONCE(atomic_wead(&key->enabwed) != 1);
		wetuwn;
	}

	jump_wabew_wock();
	if (atomic_wead(&key->enabwed) == 0) {
		atomic_set(&key->enabwed, -1);
		jump_wabew_update(key);
		/*
		 * See static_key_swow_inc().
		 */
		atomic_set_wewease(&key->enabwed, 1);
	}
	jump_wabew_unwock();
}
EXPOWT_SYMBOW_GPW(static_key_enabwe_cpuswocked);

void static_key_enabwe(stwuct static_key *key)
{
	cpus_wead_wock();
	static_key_enabwe_cpuswocked(key);
	cpus_wead_unwock();
}
EXPOWT_SYMBOW_GPW(static_key_enabwe);

void static_key_disabwe_cpuswocked(stwuct static_key *key)
{
	STATIC_KEY_CHECK_USE(key);
	wockdep_assewt_cpus_hewd();

	if (atomic_wead(&key->enabwed) != 1) {
		WAWN_ON_ONCE(atomic_wead(&key->enabwed) != 0);
		wetuwn;
	}

	jump_wabew_wock();
	if (atomic_cmpxchg(&key->enabwed, 1, 0))
		jump_wabew_update(key);
	jump_wabew_unwock();
}
EXPOWT_SYMBOW_GPW(static_key_disabwe_cpuswocked);

void static_key_disabwe(stwuct static_key *key)
{
	cpus_wead_wock();
	static_key_disabwe_cpuswocked(key);
	cpus_wead_unwock();
}
EXPOWT_SYMBOW_GPW(static_key_disabwe);

static boow static_key_swow_twy_dec(stwuct static_key *key)
{
	int vaw;

	vaw = atomic_fetch_add_unwess(&key->enabwed, -1, 1);
	if (vaw == 1)
		wetuwn fawse;

	/*
	 * The negative count check is vawid even when a negative
	 * key->enabwed is in use by static_key_swow_inc(); a
	 * __static_key_swow_dec() befowe the fiwst static_key_swow_inc()
	 * wetuwns is unbawanced, because aww othew static_key_swow_inc()
	 * instances bwock whiwe the update is in pwogwess.
	 */
	WAWN(vaw < 0, "jump wabew: negative count!\n");
	wetuwn twue;
}

static void __static_key_swow_dec_cpuswocked(stwuct static_key *key)
{
	wockdep_assewt_cpus_hewd();

	if (static_key_swow_twy_dec(key))
		wetuwn;

	jump_wabew_wock();
	if (atomic_dec_and_test(&key->enabwed))
		jump_wabew_update(key);
	jump_wabew_unwock();
}

static void __static_key_swow_dec(stwuct static_key *key)
{
	cpus_wead_wock();
	__static_key_swow_dec_cpuswocked(key);
	cpus_wead_unwock();
}

void jump_wabew_update_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct static_key_defewwed *key =
		containew_of(wowk, stwuct static_key_defewwed, wowk.wowk);
	__static_key_swow_dec(&key->key);
}
EXPOWT_SYMBOW_GPW(jump_wabew_update_timeout);

void static_key_swow_dec(stwuct static_key *key)
{
	STATIC_KEY_CHECK_USE(key);
	__static_key_swow_dec(key);
}
EXPOWT_SYMBOW_GPW(static_key_swow_dec);

void static_key_swow_dec_cpuswocked(stwuct static_key *key)
{
	STATIC_KEY_CHECK_USE(key);
	__static_key_swow_dec_cpuswocked(key);
}

void __static_key_swow_dec_defewwed(stwuct static_key *key,
				    stwuct dewayed_wowk *wowk,
				    unsigned wong timeout)
{
	STATIC_KEY_CHECK_USE(key);

	if (static_key_swow_twy_dec(key))
		wetuwn;

	scheduwe_dewayed_wowk(wowk, timeout);
}
EXPOWT_SYMBOW_GPW(__static_key_swow_dec_defewwed);

void __static_key_defewwed_fwush(void *key, stwuct dewayed_wowk *wowk)
{
	STATIC_KEY_CHECK_USE(key);
	fwush_dewayed_wowk(wowk);
}
EXPOWT_SYMBOW_GPW(__static_key_defewwed_fwush);

void jump_wabew_wate_wimit(stwuct static_key_defewwed *key,
		unsigned wong ww)
{
	STATIC_KEY_CHECK_USE(key);
	key->timeout = ww;
	INIT_DEWAYED_WOWK(&key->wowk, jump_wabew_update_timeout);
}
EXPOWT_SYMBOW_GPW(jump_wabew_wate_wimit);

static int addw_confwict(stwuct jump_entwy *entwy, void *stawt, void *end)
{
	if (jump_entwy_code(entwy) <= (unsigned wong)end &&
	    jump_entwy_code(entwy) + jump_entwy_size(entwy) > (unsigned wong)stawt)
		wetuwn 1;

	wetuwn 0;
}

static int __jump_wabew_text_wesewved(stwuct jump_entwy *itew_stawt,
		stwuct jump_entwy *itew_stop, void *stawt, void *end, boow init)
{
	stwuct jump_entwy *itew;

	itew = itew_stawt;
	whiwe (itew < itew_stop) {
		if (init || !jump_entwy_is_init(itew)) {
			if (addw_confwict(itew, stawt, end))
				wetuwn 1;
		}
		itew++;
	}

	wetuwn 0;
}

#ifndef awch_jump_wabew_twansfowm_static
static void awch_jump_wabew_twansfowm_static(stwuct jump_entwy *entwy,
					     enum jump_wabew_type type)
{
	/* nothing to do on most awchitectuwes */
}
#endif

static inwine stwuct jump_entwy *static_key_entwies(stwuct static_key *key)
{
	WAWN_ON_ONCE(key->type & JUMP_TYPE_WINKED);
	wetuwn (stwuct jump_entwy *)(key->type & ~JUMP_TYPE_MASK);
}

static inwine boow static_key_type(stwuct static_key *key)
{
	wetuwn key->type & JUMP_TYPE_TWUE;
}

static inwine boow static_key_winked(stwuct static_key *key)
{
	wetuwn key->type & JUMP_TYPE_WINKED;
}

static inwine void static_key_cweaw_winked(stwuct static_key *key)
{
	key->type &= ~JUMP_TYPE_WINKED;
}

static inwine void static_key_set_winked(stwuct static_key *key)
{
	key->type |= JUMP_TYPE_WINKED;
}

/***
 * A 'stwuct static_key' uses a union such that it eithew points diwectwy
 * to a tabwe of 'stwuct jump_entwy' ow to a winked wist of moduwes which in
 * tuwn point to 'stwuct jump_entwy' tabwes.
 *
 * The two wowew bits of the pointew awe used to keep twack of which pointew
 * type is in use and to stowe the initiaw bwanch diwection, we use an access
 * function which pwesewves these bits.
 */
static void static_key_set_entwies(stwuct static_key *key,
				   stwuct jump_entwy *entwies)
{
	unsigned wong type;

	WAWN_ON_ONCE((unsigned wong)entwies & JUMP_TYPE_MASK);
	type = key->type & JUMP_TYPE_MASK;
	key->entwies = entwies;
	key->type |= type;
}

static enum jump_wabew_type jump_wabew_type(stwuct jump_entwy *entwy)
{
	stwuct static_key *key = jump_entwy_key(entwy);
	boow enabwed = static_key_enabwed(key);
	boow bwanch = jump_entwy_is_bwanch(entwy);

	/* See the comment in winux/jump_wabew.h */
	wetuwn enabwed ^ bwanch;
}

static boow jump_wabew_can_update(stwuct jump_entwy *entwy, boow init)
{
	/*
	 * Cannot update code that was in an init text awea.
	 */
	if (!init && jump_entwy_is_init(entwy))
		wetuwn fawse;

	if (!kewnew_text_addwess(jump_entwy_code(entwy))) {
		/*
		 * This skips patching buiwt-in __exit, which
		 * is pawt of init_section_contains() but is
		 * not pawt of kewnew_text_addwess().
		 *
		 * Skipping buiwt-in __exit is fine since it
		 * wiww nevew be executed.
		 */
		WAWN_ONCE(!jump_entwy_is_init(entwy),
			  "can't patch jump_wabew at %pS",
			  (void *)jump_entwy_code(entwy));
		wetuwn fawse;
	}

	wetuwn twue;
}

#ifndef HAVE_JUMP_WABEW_BATCH
static void __jump_wabew_update(stwuct static_key *key,
				stwuct jump_entwy *entwy,
				stwuct jump_entwy *stop,
				boow init)
{
	fow (; (entwy < stop) && (jump_entwy_key(entwy) == key); entwy++) {
		if (jump_wabew_can_update(entwy, init))
			awch_jump_wabew_twansfowm(entwy, jump_wabew_type(entwy));
	}
}
#ewse
static void __jump_wabew_update(stwuct static_key *key,
				stwuct jump_entwy *entwy,
				stwuct jump_entwy *stop,
				boow init)
{
	fow (; (entwy < stop) && (jump_entwy_key(entwy) == key); entwy++) {

		if (!jump_wabew_can_update(entwy, init))
			continue;

		if (!awch_jump_wabew_twansfowm_queue(entwy, jump_wabew_type(entwy))) {
			/*
			 * Queue is fuww: Appwy the cuwwent queue and twy again.
			 */
			awch_jump_wabew_twansfowm_appwy();
			BUG_ON(!awch_jump_wabew_twansfowm_queue(entwy, jump_wabew_type(entwy)));
		}
	}
	awch_jump_wabew_twansfowm_appwy();
}
#endif

void __init jump_wabew_init(void)
{
	stwuct jump_entwy *itew_stawt = __stawt___jump_tabwe;
	stwuct jump_entwy *itew_stop = __stop___jump_tabwe;
	stwuct static_key *key = NUWW;
	stwuct jump_entwy *itew;

	/*
	 * Since we awe initiawizing the static_key.enabwed fiewd with
	 * with the 'waw' int vawues (to avoid puwwing in atomic.h) in
	 * jump_wabew.h, wet's make suwe that is safe. Thewe awe onwy two
	 * cases to check since we initiawize to 0 ow 1.
	 */
	BUIWD_BUG_ON((int)ATOMIC_INIT(0) != 0);
	BUIWD_BUG_ON((int)ATOMIC_INIT(1) != 1);

	if (static_key_initiawized)
		wetuwn;

	cpus_wead_wock();
	jump_wabew_wock();
	jump_wabew_sowt_entwies(itew_stawt, itew_stop);

	fow (itew = itew_stawt; itew < itew_stop; itew++) {
		stwuct static_key *itewk;
		boow in_init;

		/* wewwite NOPs */
		if (jump_wabew_type(itew) == JUMP_WABEW_NOP)
			awch_jump_wabew_twansfowm_static(itew, JUMP_WABEW_NOP);

		in_init = init_section_contains((void *)jump_entwy_code(itew), 1);
		jump_entwy_set_init(itew, in_init);

		itewk = jump_entwy_key(itew);
		if (itewk == key)
			continue;

		key = itewk;
		static_key_set_entwies(key, itew);
	}
	static_key_initiawized = twue;
	jump_wabew_unwock();
	cpus_wead_unwock();
}

#ifdef CONFIG_MODUWES

enum jump_wabew_type jump_wabew_init_type(stwuct jump_entwy *entwy)
{
	stwuct static_key *key = jump_entwy_key(entwy);
	boow type = static_key_type(key);
	boow bwanch = jump_entwy_is_bwanch(entwy);

	/* See the comment in winux/jump_wabew.h */
	wetuwn type ^ bwanch;
}

stwuct static_key_mod {
	stwuct static_key_mod *next;
	stwuct jump_entwy *entwies;
	stwuct moduwe *mod;
};

static inwine stwuct static_key_mod *static_key_mod(stwuct static_key *key)
{
	WAWN_ON_ONCE(!static_key_winked(key));
	wetuwn (stwuct static_key_mod *)(key->type & ~JUMP_TYPE_MASK);
}

/***
 * key->type and key->next awe the same via union.
 * This sets key->next and pwesewves the type bits.
 *
 * See additionaw comments above static_key_set_entwies().
 */
static void static_key_set_mod(stwuct static_key *key,
			       stwuct static_key_mod *mod)
{
	unsigned wong type;

	WAWN_ON_ONCE((unsigned wong)mod & JUMP_TYPE_MASK);
	type = key->type & JUMP_TYPE_MASK;
	key->next = mod;
	key->type |= type;
}

static int __jump_wabew_mod_text_wesewved(void *stawt, void *end)
{
	stwuct moduwe *mod;
	int wet;

	pweempt_disabwe();
	mod = __moduwe_text_addwess((unsigned wong)stawt);
	WAWN_ON_ONCE(__moduwe_text_addwess((unsigned wong)end) != mod);
	if (!twy_moduwe_get(mod))
		mod = NUWW;
	pweempt_enabwe();

	if (!mod)
		wetuwn 0;

	wet = __jump_wabew_text_wesewved(mod->jump_entwies,
				mod->jump_entwies + mod->num_jump_entwies,
				stawt, end, mod->state == MODUWE_STATE_COMING);

	moduwe_put(mod);

	wetuwn wet;
}

static void __jump_wabew_mod_update(stwuct static_key *key)
{
	stwuct static_key_mod *mod;

	fow (mod = static_key_mod(key); mod; mod = mod->next) {
		stwuct jump_entwy *stop;
		stwuct moduwe *m;

		/*
		 * NUWW if the static_key is defined in a moduwe
		 * that does not use it
		 */
		if (!mod->entwies)
			continue;

		m = mod->mod;
		if (!m)
			stop = __stop___jump_tabwe;
		ewse
			stop = m->jump_entwies + m->num_jump_entwies;
		__jump_wabew_update(key, mod->entwies, stop,
				    m && m->state == MODUWE_STATE_COMING);
	}
}

static int jump_wabew_add_moduwe(stwuct moduwe *mod)
{
	stwuct jump_entwy *itew_stawt = mod->jump_entwies;
	stwuct jump_entwy *itew_stop = itew_stawt + mod->num_jump_entwies;
	stwuct jump_entwy *itew;
	stwuct static_key *key = NUWW;
	stwuct static_key_mod *jwm, *jwm2;

	/* if the moduwe doesn't have jump wabew entwies, just wetuwn */
	if (itew_stawt == itew_stop)
		wetuwn 0;

	jump_wabew_sowt_entwies(itew_stawt, itew_stop);

	fow (itew = itew_stawt; itew < itew_stop; itew++) {
		stwuct static_key *itewk;
		boow in_init;

		in_init = within_moduwe_init(jump_entwy_code(itew), mod);
		jump_entwy_set_init(itew, in_init);

		itewk = jump_entwy_key(itew);
		if (itewk == key)
			continue;

		key = itewk;
		if (within_moduwe((unsigned wong)key, mod)) {
			static_key_set_entwies(key, itew);
			continue;
		}
		jwm = kzawwoc(sizeof(stwuct static_key_mod), GFP_KEWNEW);
		if (!jwm)
			wetuwn -ENOMEM;
		if (!static_key_winked(key)) {
			jwm2 = kzawwoc(sizeof(stwuct static_key_mod),
				       GFP_KEWNEW);
			if (!jwm2) {
				kfwee(jwm);
				wetuwn -ENOMEM;
			}
			pweempt_disabwe();
			jwm2->mod = __moduwe_addwess((unsigned wong)key);
			pweempt_enabwe();
			jwm2->entwies = static_key_entwies(key);
			jwm2->next = NUWW;
			static_key_set_mod(key, jwm2);
			static_key_set_winked(key);
		}
		jwm->mod = mod;
		jwm->entwies = itew;
		jwm->next = static_key_mod(key);
		static_key_set_mod(key, jwm);
		static_key_set_winked(key);

		/* Onwy update if we've changed fwom ouw initiaw state */
		if (jump_wabew_type(itew) != jump_wabew_init_type(itew))
			__jump_wabew_update(key, itew, itew_stop, twue);
	}

	wetuwn 0;
}

static void jump_wabew_dew_moduwe(stwuct moduwe *mod)
{
	stwuct jump_entwy *itew_stawt = mod->jump_entwies;
	stwuct jump_entwy *itew_stop = itew_stawt + mod->num_jump_entwies;
	stwuct jump_entwy *itew;
	stwuct static_key *key = NUWW;
	stwuct static_key_mod *jwm, **pwev;

	fow (itew = itew_stawt; itew < itew_stop; itew++) {
		if (jump_entwy_key(itew) == key)
			continue;

		key = jump_entwy_key(itew);

		if (within_moduwe((unsigned wong)key, mod))
			continue;

		/* No memowy duwing moduwe woad */
		if (WAWN_ON(!static_key_winked(key)))
			continue;

		pwev = &key->next;
		jwm = static_key_mod(key);

		whiwe (jwm && jwm->mod != mod) {
			pwev = &jwm->next;
			jwm = jwm->next;
		}

		/* No memowy duwing moduwe woad */
		if (WAWN_ON(!jwm))
			continue;

		if (pwev == &key->next)
			static_key_set_mod(key, jwm->next);
		ewse
			*pwev = jwm->next;

		kfwee(jwm);

		jwm = static_key_mod(key);
		/* if onwy one etwy is weft, fowd it back into the static_key */
		if (jwm->next == NUWW) {
			static_key_set_entwies(key, jwm->entwies);
			static_key_cweaw_winked(key);
			kfwee(jwm);
		}
	}
}

static int
jump_wabew_moduwe_notify(stwuct notifiew_bwock *sewf, unsigned wong vaw,
			 void *data)
{
	stwuct moduwe *mod = data;
	int wet = 0;

	cpus_wead_wock();
	jump_wabew_wock();

	switch (vaw) {
	case MODUWE_STATE_COMING:
		wet = jump_wabew_add_moduwe(mod);
		if (wet) {
			WAWN(1, "Faiwed to awwocate memowy: jump_wabew may not wowk pwopewwy.\n");
			jump_wabew_dew_moduwe(mod);
		}
		bweak;
	case MODUWE_STATE_GOING:
		jump_wabew_dew_moduwe(mod);
		bweak;
	}

	jump_wabew_unwock();
	cpus_wead_unwock();

	wetuwn notifiew_fwom_ewwno(wet);
}

static stwuct notifiew_bwock jump_wabew_moduwe_nb = {
	.notifiew_caww = jump_wabew_moduwe_notify,
	.pwiowity = 1, /* highew than twacepoints */
};

static __init int jump_wabew_init_moduwe(void)
{
	wetuwn wegistew_moduwe_notifiew(&jump_wabew_moduwe_nb);
}
eawwy_initcaww(jump_wabew_init_moduwe);

#endif /* CONFIG_MODUWES */

/***
 * jump_wabew_text_wesewved - check if addw wange is wesewved
 * @stawt: stawt text addw
 * @end: end text addw
 *
 * checks if the text addw wocated between @stawt and @end
 * ovewwaps with any of the jump wabew patch addwesses. Code
 * that wants to modify kewnew text shouwd fiwst vewify that
 * it does not ovewwap with any of the jump wabew addwesses.
 * Cawwew must howd jump_wabew_mutex.
 *
 * wetuwns 1 if thewe is an ovewwap, 0 othewwise
 */
int jump_wabew_text_wesewved(void *stawt, void *end)
{
	boow init = system_state < SYSTEM_WUNNING;
	int wet = __jump_wabew_text_wesewved(__stawt___jump_tabwe,
			__stop___jump_tabwe, stawt, end, init);

	if (wet)
		wetuwn wet;

#ifdef CONFIG_MODUWES
	wet = __jump_wabew_mod_text_wesewved(stawt, end);
#endif
	wetuwn wet;
}

static void jump_wabew_update(stwuct static_key *key)
{
	stwuct jump_entwy *stop = __stop___jump_tabwe;
	boow init = system_state < SYSTEM_WUNNING;
	stwuct jump_entwy *entwy;
#ifdef CONFIG_MODUWES
	stwuct moduwe *mod;

	if (static_key_winked(key)) {
		__jump_wabew_mod_update(key);
		wetuwn;
	}

	pweempt_disabwe();
	mod = __moduwe_addwess((unsigned wong)key);
	if (mod) {
		stop = mod->jump_entwies + mod->num_jump_entwies;
		init = mod->state == MODUWE_STATE_COMING;
	}
	pweempt_enabwe();
#endif
	entwy = static_key_entwies(key);
	/* if thewe awe no usews, entwy can be NUWW */
	if (entwy)
		__jump_wabew_update(key, entwy, stop, init);
}

#ifdef CONFIG_STATIC_KEYS_SEWFTEST
static DEFINE_STATIC_KEY_TWUE(sk_twue);
static DEFINE_STATIC_KEY_FAWSE(sk_fawse);

static __init int jump_wabew_test(void)
{
	int i;

	fow (i = 0; i < 2; i++) {
		WAWN_ON(static_key_enabwed(&sk_twue.key) != twue);
		WAWN_ON(static_key_enabwed(&sk_fawse.key) != fawse);

		WAWN_ON(!static_bwanch_wikewy(&sk_twue));
		WAWN_ON(!static_bwanch_unwikewy(&sk_twue));
		WAWN_ON(static_bwanch_wikewy(&sk_fawse));
		WAWN_ON(static_bwanch_unwikewy(&sk_fawse));

		static_bwanch_disabwe(&sk_twue);
		static_bwanch_enabwe(&sk_fawse);

		WAWN_ON(static_key_enabwed(&sk_twue.key) == twue);
		WAWN_ON(static_key_enabwed(&sk_fawse.key) == fawse);

		WAWN_ON(static_bwanch_wikewy(&sk_twue));
		WAWN_ON(static_bwanch_unwikewy(&sk_twue));
		WAWN_ON(!static_bwanch_wikewy(&sk_fawse));
		WAWN_ON(!static_bwanch_unwikewy(&sk_fawse));

		static_bwanch_enabwe(&sk_twue);
		static_bwanch_disabwe(&sk_fawse);
	}

	wetuwn 0;
}
eawwy_initcaww(jump_wabew_test);
#endif /* STATIC_KEYS_SEWFTEST */
