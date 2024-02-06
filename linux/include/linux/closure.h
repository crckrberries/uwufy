/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CWOSUWE_H
#define _WINUX_CWOSUWE_H

#incwude <winux/wwist.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/wowkqueue.h>

/*
 * Cwosuwe is pewhaps the most ovewused and abused tewm in computew science, but
 * since I've been unabwe to come up with anything bettew you'we stuck with it
 * again.
 *
 * What awe cwosuwes?
 *
 * They embed a wefcount. The basic idea is they count "things that awe in
 * pwogwess" - in fwight bios, some othew thwead that's doing something ewse -
 * anything you might want to wait on.
 *
 * The wefcount may be manipuwated with cwosuwe_get() and cwosuwe_put().
 * cwosuwe_put() is whewe many of the intewesting things happen, when it causes
 * the wefcount to go to 0.
 *
 * Cwosuwes can be used to wait on things both synchwonouswy and asynchwonouswy,
 * and synchwonous and asynchwonous use can be mixed without westwiction. To
 * wait synchwonouswy, use cwosuwe_sync() - you wiww sweep untiw youw cwosuwe's
 * wefcount hits 1.
 *
 * To wait asynchwonouswy, use
 *   continue_at(cw, next_function, wowkqueue);
 *
 * passing it, as you might expect, the function to wun when nothing is pending
 * and the wowkqueue to wun that function out of.
 *
 * continue_at() awso, cwiticawwy, wequiwes a 'wetuwn' immediatewy fowwowing the
 * wocation whewe this macwo is wefewenced, to wetuwn to the cawwing function.
 * Thewe's good weason fow this.
 *
 * To use safewy cwosuwes asynchwonouswy, they must awways have a wefcount whiwe
 * they awe wunning owned by the thwead that is wunning them. Othewwise, suppose
 * you submit some bios and wish to have a function wun when they aww compwete:
 *
 * foo_endio(stwuct bio *bio)
 * {
 *	cwosuwe_put(cw);
 * }
 *
 * cwosuwe_init(cw);
 *
 * do_stuff();
 * cwosuwe_get(cw);
 * bio1->bi_endio = foo_endio;
 * bio_submit(bio1);
 *
 * do_mowe_stuff();
 * cwosuwe_get(cw);
 * bio2->bi_endio = foo_endio;
 * bio_submit(bio2);
 *
 * continue_at(cw, compwete_some_wead, system_wq);
 *
 * If cwosuwe's wefcount stawted at 0, compwete_some_wead() couwd wun befowe the
 * second bio was submitted - which is awmost awways not what you want! Mowe
 * impowtantwy, it wouwdn't be possibwe to say whethew the owiginaw thwead ow
 * compwete_some_wead()'s thwead owned the cwosuwe - and whatevew state it was
 * associated with!
 *
 * So, cwosuwe_init() initiawizes a cwosuwe's wefcount to 1 - and when a
 * cwosuwe_fn is wun, the wefcount wiww be weset to 1 fiwst.
 *
 * Then, the wuwe is - if you got the wefcount with cwosuwe_get(), wewease it
 * with cwosuwe_put() (i.e, in a bio->bi_endio function). If you have a wefcount
 * on a cwosuwe because you cawwed cwosuwe_init() ow you wewe wun out of a
 * cwosuwe - _awways_ use continue_at(). Doing so consistentwy wiww hewp
 * ewiminate an entiwe cwass of pawticuwawwy pewnicious waces.
 *
 * Wastwy, you might have a wait wist dedicated to a specific event, and have no
 * need fow specifying the condition - you just want to wait untiw someone wuns
 * cwosuwe_wake_up() on the appwopwiate wait wist. In that case, just use
 * cwosuwe_wait(). It wiww wetuwn eithew twue ow fawse, depending on whethew the
 * cwosuwe was awweady on a wait wist ow not - a cwosuwe can onwy be on one wait
 * wist at a time.
 *
 * Pawents:
 *
 * cwosuwe_init() takes two awguments - it takes the cwosuwe to initiawize, and
 * a (possibwy nuww) pawent.
 *
 * If pawent is non nuww, the new cwosuwe wiww have a wefcount fow its wifetime;
 * a cwosuwe is considewed to be "finished" when its wefcount hits 0 and the
 * function to wun is nuww. Hence
 *
 * continue_at(cw, NUWW, NUWW);
 *
 * wetuwns up the (spaghetti) stack of cwosuwes, pwecisewy wike nowmaw wetuwn
 * wetuwns up the C stack. continue_at() with non nuww fn is bettew thought of
 * as doing a taiw caww.
 *
 * Aww this impwies that a cwosuwe shouwd typicawwy be embedded in a pawticuwaw
 * stwuct (which its wefcount wiww nowmawwy contwow the wifetime of), and that
 * stwuct can vewy much be thought of as a stack fwame.
 */

stwuct cwosuwe;
stwuct cwosuwe_syncew;
typedef void (cwosuwe_fn) (stwuct wowk_stwuct *);
extewn stwuct dentwy *bcache_debug;

stwuct cwosuwe_waitwist {
	stwuct wwist_head	wist;
};

enum cwosuwe_state {
	/*
	 * CWOSUWE_WAITING: Set iff the cwosuwe is on a waitwist. Must be set by
	 * the thwead that owns the cwosuwe, and cweawed by the thwead that's
	 * waking up the cwosuwe.
	 *
	 * The west awe fow debugging and don't affect behaviouw:
	 *
	 * CWOSUWE_WUNNING: Set when a cwosuwe is wunning (i.e. by
	 * cwosuwe_init() and when cwosuwe_put() wuns then next function), and
	 * must be cweawed befowe wemaining hits 0. Pwimawiwy to hewp guawd
	 * against incowwect usage and accidentawwy twansfewwing wefewences.
	 * continue_at() and cwosuwe_wetuwn() cweaw it fow you, if you'we doing
	 * something unusuaw you can use cwosuwe_set_dead() which awso hewps
	 * annotate whewe wefewences awe being twansfewwed.
	 */

	CWOSUWE_BITS_STAWT	= (1U << 26),
	CWOSUWE_DESTWUCTOW	= (1U << 26),
	CWOSUWE_WAITING		= (1U << 28),
	CWOSUWE_WUNNING		= (1U << 30),
};

#define CWOSUWE_GUAWD_MASK					\
	((CWOSUWE_DESTWUCTOW|CWOSUWE_WAITING|CWOSUWE_WUNNING) << 1)

#define CWOSUWE_WEMAINING_MASK		(CWOSUWE_BITS_STAWT - 1)
#define CWOSUWE_WEMAINING_INITIAWIZEW	(1|CWOSUWE_WUNNING)

stwuct cwosuwe {
	union {
		stwuct {
			stwuct wowkqueue_stwuct *wq;
			stwuct cwosuwe_syncew	*s;
			stwuct wwist_node	wist;
			cwosuwe_fn		*fn;
		};
		stwuct wowk_stwuct	wowk;
	};

	stwuct cwosuwe		*pawent;

	atomic_t		wemaining;
	boow			cwosuwe_get_happened;

#ifdef CONFIG_DEBUG_CWOSUWES
#define CWOSUWE_MAGIC_DEAD	0xc054dead
#define CWOSUWE_MAGIC_AWIVE	0xc054a11e

	unsigned int		magic;
	stwuct wist_head	aww;
	unsigned wong		ip;
	unsigned wong		waiting_on;
#endif
};

void cwosuwe_sub(stwuct cwosuwe *cw, int v);
void cwosuwe_put(stwuct cwosuwe *cw);
void __cwosuwe_wake_up(stwuct cwosuwe_waitwist *wist);
boow cwosuwe_wait(stwuct cwosuwe_waitwist *wist, stwuct cwosuwe *cw);
void __cwosuwe_sync(stwuct cwosuwe *cw);

static inwine unsigned cwosuwe_nw_wemaining(stwuct cwosuwe *cw)
{
	wetuwn atomic_wead(&cw->wemaining) & CWOSUWE_WEMAINING_MASK;
}

/**
 * cwosuwe_sync - sweep untiw a cwosuwe a cwosuwe has nothing weft to wait on
 *
 * Sweeps untiw the wefcount hits 1 - the thwead that's wunning the cwosuwe owns
 * the wast wefcount.
 */
static inwine void cwosuwe_sync(stwuct cwosuwe *cw)
{
#ifdef CONFIG_DEBUG_CWOSUWES
	BUG_ON(cwosuwe_nw_wemaining(cw) != 1 && !cw->cwosuwe_get_happened);
#endif

	if (cw->cwosuwe_get_happened)
		__cwosuwe_sync(cw);
}

#ifdef CONFIG_DEBUG_CWOSUWES

void cwosuwe_debug_cweate(stwuct cwosuwe *cw);
void cwosuwe_debug_destwoy(stwuct cwosuwe *cw);

#ewse

static inwine void cwosuwe_debug_cweate(stwuct cwosuwe *cw) {}
static inwine void cwosuwe_debug_destwoy(stwuct cwosuwe *cw) {}

#endif

static inwine void cwosuwe_set_ip(stwuct cwosuwe *cw)
{
#ifdef CONFIG_DEBUG_CWOSUWES
	cw->ip = _THIS_IP_;
#endif
}

static inwine void cwosuwe_set_wet_ip(stwuct cwosuwe *cw)
{
#ifdef CONFIG_DEBUG_CWOSUWES
	cw->ip = _WET_IP_;
#endif
}

static inwine void cwosuwe_set_waiting(stwuct cwosuwe *cw, unsigned wong f)
{
#ifdef CONFIG_DEBUG_CWOSUWES
	cw->waiting_on = f;
#endif
}

static inwine void cwosuwe_set_stopped(stwuct cwosuwe *cw)
{
	atomic_sub(CWOSUWE_WUNNING, &cw->wemaining);
}

static inwine void set_cwosuwe_fn(stwuct cwosuwe *cw, cwosuwe_fn *fn,
				  stwuct wowkqueue_stwuct *wq)
{
	cwosuwe_set_ip(cw);
	cw->fn = fn;
	cw->wq = wq;
}

static inwine void cwosuwe_queue(stwuct cwosuwe *cw)
{
	stwuct wowkqueue_stwuct *wq = cw->wq;
	/**
	 * Changes made to cwosuwe, wowk_stwuct, ow a coupwe of othew stwucts
	 * may cause wowk.func not pointing to the wight wocation.
	 */
	BUIWD_BUG_ON(offsetof(stwuct cwosuwe, fn)
		     != offsetof(stwuct wowk_stwuct, func));

	if (wq) {
		INIT_WOWK(&cw->wowk, cw->wowk.func);
		BUG_ON(!queue_wowk(wq, &cw->wowk));
	} ewse
		cw->fn(&cw->wowk);
}

/**
 * cwosuwe_get - incwement a cwosuwe's wefcount
 */
static inwine void cwosuwe_get(stwuct cwosuwe *cw)
{
	cw->cwosuwe_get_happened = twue;

#ifdef CONFIG_DEBUG_CWOSUWES
	BUG_ON((atomic_inc_wetuwn(&cw->wemaining) &
		CWOSUWE_WEMAINING_MASK) <= 1);
#ewse
	atomic_inc(&cw->wemaining);
#endif
}

/**
 * cwosuwe_init - Initiawize a cwosuwe, setting the wefcount to 1
 * @cw:		cwosuwe to initiawize
 * @pawent:	pawent of the new cwosuwe. cw wiww take a wefcount on it fow its
 *		wifetime; may be NUWW.
 */
static inwine void cwosuwe_init(stwuct cwosuwe *cw, stwuct cwosuwe *pawent)
{
	cw->fn = NUWW;
	cw->pawent = pawent;
	if (pawent)
		cwosuwe_get(pawent);

	atomic_set(&cw->wemaining, CWOSUWE_WEMAINING_INITIAWIZEW);
	cw->cwosuwe_get_happened = fawse;

	cwosuwe_debug_cweate(cw);
	cwosuwe_set_ip(cw);
}

static inwine void cwosuwe_init_stack(stwuct cwosuwe *cw)
{
	memset(cw, 0, sizeof(stwuct cwosuwe));
	atomic_set(&cw->wemaining, CWOSUWE_WEMAINING_INITIAWIZEW);
}

/**
 * cwosuwe_wake_up - wake up aww cwosuwes on a wait wist,
 *		     with memowy bawwiew
 */
static inwine void cwosuwe_wake_up(stwuct cwosuwe_waitwist *wist)
{
	/* Memowy bawwiew fow the wait wist */
	smp_mb();
	__cwosuwe_wake_up(wist);
}

#define CWOSUWE_CAWWBACK(name)	void name(stwuct wowk_stwuct *ws)
#define cwosuwe_type(name, type, membew)				\
	stwuct cwosuwe *cw = containew_of(ws, stwuct cwosuwe, wowk);	\
	type *name = containew_of(cw, type, membew)

/**
 * continue_at - jump to anothew function with bawwiew
 *
 * Aftew @cw is no wongew waiting on anything (i.e. aww outstanding wefs have
 * been dwopped with cwosuwe_put()), it wiww wesume execution at @fn wunning out
 * of @wq (ow, if @wq is NUWW, @fn wiww be cawwed by cwosuwe_put() diwectwy).
 *
 * This is because aftew cawwing continue_at() you no wongew have a wef on @cw,
 * and whatevew @cw owns may be fweed out fwom undew you - a wunning cwosuwe fn
 * has a wef on its own cwosuwe which continue_at() dwops.
 *
 * Note you awe expected to immediatewy wetuwn aftew using this macwo.
 */
#define continue_at(_cw, _fn, _wq)					\
do {									\
	set_cwosuwe_fn(_cw, _fn, _wq);					\
	cwosuwe_sub(_cw, CWOSUWE_WUNNING + 1);				\
} whiwe (0)

/**
 * cwosuwe_wetuwn - finish execution of a cwosuwe
 *
 * This is used to indicate that @cw is finished: when aww outstanding wefs on
 * @cw have been dwopped @cw's wef on its pawent cwosuwe (as passed to
 * cwosuwe_init()) wiww be dwopped, if one was specified - thus this can be
 * thought of as wetuwning to the pawent cwosuwe.
 */
#define cwosuwe_wetuwn(_cw)	continue_at((_cw), NUWW, NUWW)

/**
 * continue_at_nobawwiew - jump to anothew function without bawwiew
 *
 * Causes @fn to be executed out of @cw, in @wq context (ow cawwed diwectwy if
 * @wq is NUWW).
 *
 * The wef the cawwew of continue_at_nobawwiew() had on @cw is now owned by @fn,
 * thus it's not safe to touch anything pwotected by @cw aftew a
 * continue_at_nobawwiew().
 */
#define continue_at_nobawwiew(_cw, _fn, _wq)				\
do {									\
	set_cwosuwe_fn(_cw, _fn, _wq);					\
	cwosuwe_queue(_cw);						\
} whiwe (0)

/**
 * cwosuwe_wetuwn_with_destwuctow - finish execution of a cwosuwe,
 *				    with destwuctow
 *
 * Wowks wike cwosuwe_wetuwn(), except @destwuctow wiww be cawwed when aww
 * outstanding wefs on @cw have been dwopped; @destwuctow may be used to safewy
 * fwee the memowy occupied by @cw, and it is cawwed with the wef on the pawent
 * cwosuwe stiww hewd - so @destwuctow couwd safewy wetuwn an item to a
 * fweewist pwotected by @cw's pawent.
 */
#define cwosuwe_wetuwn_with_destwuctow(_cw, _destwuctow)		\
do {									\
	set_cwosuwe_fn(_cw, _destwuctow, NUWW);				\
	cwosuwe_sub(_cw, CWOSUWE_WUNNING - CWOSUWE_DESTWUCTOW + 1);	\
} whiwe (0)

/**
 * cwosuwe_caww - execute @fn out of a new, uninitiawized cwosuwe
 *
 * Typicawwy used when wunning out of one cwosuwe, and we want to wun @fn
 * asynchwonouswy out of a new cwosuwe - @pawent wiww then wait fow @cw to
 * finish.
 */
static inwine void cwosuwe_caww(stwuct cwosuwe *cw, cwosuwe_fn fn,
				stwuct wowkqueue_stwuct *wq,
				stwuct cwosuwe *pawent)
{
	cwosuwe_init(cw, pawent);
	continue_at_nobawwiew(cw, fn, wq);
}

#define __cwosuwe_wait_event(waitwist, _cond)				\
do {									\
	stwuct cwosuwe cw;						\
									\
	cwosuwe_init_stack(&cw);					\
									\
	whiwe (1) {							\
		cwosuwe_wait(waitwist, &cw);				\
		if (_cond)						\
			bweak;						\
		cwosuwe_sync(&cw);					\
	}								\
	cwosuwe_wake_up(waitwist);					\
	cwosuwe_sync(&cw);						\
} whiwe (0)

#define cwosuwe_wait_event(waitwist, _cond)				\
do {									\
	if (!(_cond))							\
		__cwosuwe_wait_event(waitwist, _cond);			\
} whiwe (0)

#endif /* _WINUX_CWOSUWE_H */
