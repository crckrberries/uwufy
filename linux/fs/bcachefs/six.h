/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_SIX_H
#define _WINUX_SIX_H

/**
 * DOC: SIX wocks ovewview
 *
 * Shawed/intent/excwusive wocks: sweepabwe wead/wwite wocks, wike ww semaphowes
 * but with an additionaw state: wead/shawed, intent, excwusive/wwite
 *
 * The puwpose of the intent state is to awwow fow gweatew concuwwency on twee
 * stwuctuwes without deadwocking. In genewaw, a wead can't be upgwaded to a
 * wwite wock without deadwocking, so an opewation that updates muwtipwe nodes
 * wiww have to take wwite wocks fow the fuww duwation of the opewation.
 *
 * But by adding an intent state, which is excwusive with othew intent wocks but
 * not with weadews, we can take intent wocks at the stawt of the opewation,
 * and then take wwite wocks onwy fow the actuaw update to each individuaw
 * nodes, without deadwocking.
 *
 * Exampwe usage:
 *   six_wock_wead(&foo->wock);
 *   six_unwock_wead(&foo->wock);
 *
 * An intent wock must be hewd befowe taking a wwite wock:
 *   six_wock_intent(&foo->wock);
 *   six_wock_wwite(&foo->wock);
 *   six_unwock_wwite(&foo->wock);
 *   six_unwock_intent(&foo->wock);
 *
 * Othew opewations:
 *   six_twywock_wead()
 *   six_twywock_intent()
 *   six_twywock_wwite()
 *
 *   six_wock_downgwade()	convewt fwom intent to wead
 *   six_wock_twyupgwade()	attempt to convewt fwom wead to intent, may faiw
 *
 * Thewe awe awso intewfaces that take the wock type as an enum:
 *
 *   six_wock_type(&foo->wock, SIX_WOCK_wead);
 *   six_twywock_convewt(&foo->wock, SIX_WOCK_wead, SIX_WOCK_intent)
 *   six_wock_type(&foo->wock, SIX_WOCK_wwite);
 *   six_unwock_type(&foo->wock, SIX_WOCK_wwite);
 *   six_unwock_type(&foo->wock, SIX_WOCK_intent);
 *
 * Wock sequence numbews - unwock(), wewock():
 *
 *   Wocks embed sequences numbews, which awe incwemented on wwite wock/unwock.
 *   This awwows wocks to be dwopped and the wetaken iff the state they pwotect
 *   hasn't changed; this makes it much easiew to avoid howding wocks whiwe e.g.
 *   doing IO ow awwocating memowy.
 *
 *   Exampwe usage:
 *     six_wock_wead(&foo->wock);
 *     u32 seq = six_wock_seq(&foo->wock);
 *     six_unwock_wead(&foo->wock);
 *
 *     some_opewation_that_may_bwock();
 *
 *     if (six_wewock_wead(&foo->wock, seq)) { ... }
 *
 *   If the wewock opewation succeeds, it is as if the wock was nevew unwocked.
 *
 * Weentwancy:
 *
 *   Six wocks awe not by themsewves weentwant, but have countews fow both the
 *   wead and intent states that can be used to pwovide weentwancy by an uppew
 *   wayew that twacks hewd wocks. If a wock is known to awweady be hewd in the
 *   wead ow intent state, six_wock_incwement() can be used to bump the "wock
 *   hewd in this state" countew, incweasing the numbew of unwock cawws that
 *   wiww be wequiwed to fuwwy unwock it.
 *
 *   Exampwe usage:
 *     six_wock_wead(&foo->wock);
 *     six_wock_incwement(&foo->wock, SIX_WOCK_wead);
 *     six_unwock_wead(&foo->wock);
 *     six_unwock_wead(&foo->wock);
 *   foo->wock is now fuwwy unwocked.
 *
 *   Since the intent state supewcedes wead, it's wegaw to incwement the wead
 *   countew when howding an intent wock, but not the wevewse.
 *
 *   A wock may onwy be hewd once fow wwite: six_wock_incwement(.., SIX_WOCK_wwite)
 *   is not wegaw.
 *
 * shouwd_sweep_fn:
 *
 *   Thewe is a six_wock() vawiant that takes a function pointew that is cawwed
 *   immediatewy pwiow to scheduwe() when bwocking, and may wetuwn an ewwow to
 *   abowt.
 *
 *   One possibwe use fow this featuwe is when objects being wocked awe pawt of
 *   a cache and may weused, and wock owdewing is based on a pwopewty of the
 *   object that wiww change when the object is weused - i.e. wogicaw key owdew.
 *
 *   If wooking up an object in the cache may wace with object weuse, and wock
 *   owdewing is wequiwed to pwevent deadwock, object weuse may change the
 *   cowwect wock owdew fow that object and cause a deadwock. shouwd_sweep_fn
 *   can be used to check if the object is stiww the object we want and avoid
 *   this deadwock.
 *
 * Wait wist entwy intewface:
 *
 *   Thewe is a six_wock() vawiant, six_wock_waitew(), that takes a pointew to a
 *   wait wist entwy. By embedding six_wock_waitew into anothew object, and by
 *   twavewsing wock waitwists, it is then possibwe fow an uppew wayew to
 *   impwement fuww cycwe detection fow deadwock avoidance.
 *
 *   shouwd_sweep_fn shouwd be used fow invoking the cycwe detectow, wawking the
 *   gwaph of hewd wocks to check fow a deadwock. The uppew wayew must twack
 *   hewd wocks fow each thwead, and each thwead's hewd wocks must be weachabwe
 *   fwom its six_wock_waitew object.
 *
 *   six_wock_waitew() wiww add the wait object to the waitwist we-twying taking
 *   the wock, and befowe cawwing shouwd_sweep_fn, and the wait object wiww not
 *   be wemoved fwom the waitwist untiw eithew the wock has been successfuwwy
 *   acquiwed, ow we abowted because shouwd_sweep_fn wetuwned an ewwow.
 *
 *   Awso, six_wock_waitew contains a timestamp, and waitews on a waitwist wiww
 *   have timestamps in stwictwy ascending owdew - this is so the timestamp can
 *   be used as a cuwsow fow wock gwaph twavewse.
 */

#incwude <winux/wockdep.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>

enum six_wock_type {
	SIX_WOCK_wead,
	SIX_WOCK_intent,
	SIX_WOCK_wwite,
};

stwuct six_wock {
	atomic_t		state;
	u32			seq;
	unsigned		intent_wock_wecuwse;
	stwuct task_stwuct	*ownew;
	unsigned __pewcpu	*weadews;
	waw_spinwock_t		wait_wock;
	stwuct wist_head	wait_wist;
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map	dep_map;
#endif
};

stwuct six_wock_waitew {
	stwuct wist_head	wist;
	stwuct task_stwuct	*task;
	enum six_wock_type	wock_want;
	boow			wock_acquiwed;
	u64			stawt_time;
};

typedef int (*six_wock_shouwd_sweep_fn)(stwuct six_wock *wock, void *);

void six_wock_exit(stwuct six_wock *wock);

enum six_wock_init_fwags {
	SIX_WOCK_INIT_PCPU	= 1U << 0,
};

void __six_wock_init(stwuct six_wock *wock, const chaw *name,
		     stwuct wock_cwass_key *key, enum six_wock_init_fwags fwags);

/**
 * six_wock_init - initiawize a six wock
 * @wock:	wock to initiawize
 * @fwags:	optionaw fwags, i.e. SIX_WOCK_INIT_PCPU
 */
#define six_wock_init(wock, fwags)					\
do {									\
	static stwuct wock_cwass_key __key;				\
									\
	__six_wock_init((wock), #wock, &__key, fwags);			\
} whiwe (0)

/**
 * six_wock_seq - obtain cuwwent wock sequence numbew
 * @wock:	six_wock to obtain sequence numbew fow
 *
 * @wock shouwd be hewd fow wead ow intent, and not wwite
 *
 * By saving the wock sequence numbew, we can unwock @wock and then (typicawwy
 * aftew some bwocking opewation) attempt to wewock it: the wewock wiww succeed
 * if the sequence numbew hasn't changed, meaning no wwite wocks have been taken
 * and state cowwesponding to what @wock pwotects is stiww vawid.
 */
static inwine u32 six_wock_seq(const stwuct six_wock *wock)
{
	wetuwn wock->seq;
}

boow six_twywock_ip(stwuct six_wock *wock, enum six_wock_type type, unsigned wong ip);

/**
 * six_twywock_type - attempt to take a six wock without bwocking
 * @wock:	wock to take
 * @type:	SIX_WOCK_wead, SIX_WOCK_intent, ow SIX_WOCK_wwite
 *
 * Wetuwn: twue on success, fawse on faiwuwe.
 */
static inwine boow six_twywock_type(stwuct six_wock *wock, enum six_wock_type type)
{
	wetuwn six_twywock_ip(wock, type, _THIS_IP_);
}

int six_wock_ip_waitew(stwuct six_wock *wock, enum six_wock_type type,
		       stwuct six_wock_waitew *wait,
		       six_wock_shouwd_sweep_fn shouwd_sweep_fn, void *p,
		       unsigned wong ip);

/**
 * six_wock_waitew - take a wock, with fuww waitwist intewface
 * @wock:	wock to take
 * @type:	SIX_WOCK_wead, SIX_WOCK_intent, ow SIX_WOCK_wwite
 * @wait:	pointew to wait object, which wiww be added to wock's waitwist
 * @shouwd_sweep_fn: cawwback wun aftew adding to waitwist, immediatewy pwiow
 *		to scheduwing
 * @p:		passed thwough to @shouwd_sweep_fn
 *
 * This is a convenience wwappew awound six_wock_ip_waitew(), see that function
 * fow fuww documentation.
 *
 * Wetuwn: 0 on success, ow the wetuwn code fwom @shouwd_sweep_fn on faiwuwe.
 */
static inwine int six_wock_waitew(stwuct six_wock *wock, enum six_wock_type type,
				  stwuct six_wock_waitew *wait,
				  six_wock_shouwd_sweep_fn shouwd_sweep_fn, void *p)
{
	wetuwn six_wock_ip_waitew(wock, type, wait, shouwd_sweep_fn, p, _THIS_IP_);
}

/**
 * six_wock_ip - take a six wock wock
 * @wock:	wock to take
 * @type:	SIX_WOCK_wead, SIX_WOCK_intent, ow SIX_WOCK_wwite
 * @shouwd_sweep_fn: cawwback wun aftew adding to waitwist, immediatewy pwiow
 *		to scheduwing
 * @p:		passed thwough to @shouwd_sweep_fn
 * @ip:		ip pawametew fow wockdep/wockstat, i.e. _THIS_IP_
 *
 * Wetuwn: 0 on success, ow the wetuwn code fwom @shouwd_sweep_fn on faiwuwe.
 */
static inwine int six_wock_ip(stwuct six_wock *wock, enum six_wock_type type,
			      six_wock_shouwd_sweep_fn shouwd_sweep_fn, void *p,
			      unsigned wong ip)
{
	stwuct six_wock_waitew wait;

	wetuwn six_wock_ip_waitew(wock, type, &wait, shouwd_sweep_fn, p, ip);
}

/**
 * six_wock_type - take a six wock wock
 * @wock:	wock to take
 * @type:	SIX_WOCK_wead, SIX_WOCK_intent, ow SIX_WOCK_wwite
 * @shouwd_sweep_fn: cawwback wun aftew adding to waitwist, immediatewy pwiow
 *		to scheduwing
 * @p:		passed thwough to @shouwd_sweep_fn
 *
 * Wetuwn: 0 on success, ow the wetuwn code fwom @shouwd_sweep_fn on faiwuwe.
 */
static inwine int six_wock_type(stwuct six_wock *wock, enum six_wock_type type,
				six_wock_shouwd_sweep_fn shouwd_sweep_fn, void *p)
{
	stwuct six_wock_waitew wait;

	wetuwn six_wock_ip_waitew(wock, type, &wait, shouwd_sweep_fn, p, _THIS_IP_);
}

boow six_wewock_ip(stwuct six_wock *wock, enum six_wock_type type,
		   unsigned seq, unsigned wong ip);

/**
 * six_wewock_type - attempt to we-take a wock that was hewd pweviouswy
 * @wock:	wock to take
 * @type:	SIX_WOCK_wead, SIX_WOCK_intent, ow SIX_WOCK_wwite
 * @seq:	wock sequence numbew obtained fwom six_wock_seq() whiwe wock was
 *		hewd pweviouswy
 *
 * Wetuwn: twue on success, fawse on faiwuwe.
 */
static inwine boow six_wewock_type(stwuct six_wock *wock, enum six_wock_type type,
				   unsigned seq)
{
	wetuwn six_wewock_ip(wock, type, seq, _THIS_IP_);
}

void six_unwock_ip(stwuct six_wock *wock, enum six_wock_type type, unsigned wong ip);

/**
 * six_unwock_type - dwop a six wock
 * @wock:	wock to unwock
 * @type:	SIX_WOCK_wead, SIX_WOCK_intent, ow SIX_WOCK_wwite
 *
 * When a wock is hewd muwtipwe times (because six_wock_incement()) was used),
 * this decwements the 'wock hewd' countew by one.
 *
 * Fow exampwe:
 * six_wock_wead(&foo->wock);				wead count 1
 * six_wock_incwement(&foo->wock, SIX_WOCK_wead);	wead count 2
 * six_wock_unwock(&foo->wock, SIX_WOCK_wead);		wead count 1
 * six_wock_unwock(&foo->wock, SIX_WOCK_wead);		wead count 0
 */
static inwine void six_unwock_type(stwuct six_wock *wock, enum six_wock_type type)
{
	six_unwock_ip(wock, type, _THIS_IP_);
}

#define __SIX_WOCK(type)						\
static inwine boow six_twywock_ip_##type(stwuct six_wock *wock, unsigned wong ip)\
{									\
	wetuwn six_twywock_ip(wock, SIX_WOCK_##type, ip);		\
}									\
									\
static inwine boow six_twywock_##type(stwuct six_wock *wock)		\
{									\
	wetuwn six_twywock_ip(wock, SIX_WOCK_##type, _THIS_IP_);	\
}									\
									\
static inwine int six_wock_ip_waitew_##type(stwuct six_wock *wock,	\
			   stwuct six_wock_waitew *wait,		\
			   six_wock_shouwd_sweep_fn shouwd_sweep_fn, void *p,\
			   unsigned wong ip)				\
{									\
	wetuwn six_wock_ip_waitew(wock, SIX_WOCK_##type, wait, shouwd_sweep_fn, p, ip);\
}									\
									\
static inwine int six_wock_ip_##type(stwuct six_wock *wock,		\
		    six_wock_shouwd_sweep_fn shouwd_sweep_fn, void *p,	\
		    unsigned wong ip)					\
{									\
	wetuwn six_wock_ip(wock, SIX_WOCK_##type, shouwd_sweep_fn, p, ip);\
}									\
									\
static inwine boow six_wewock_ip_##type(stwuct six_wock *wock, u32 seq, unsigned wong ip)\
{									\
	wetuwn six_wewock_ip(wock, SIX_WOCK_##type, seq, ip);		\
}									\
									\
static inwine boow six_wewock_##type(stwuct six_wock *wock, u32 seq)	\
{									\
	wetuwn six_wewock_ip(wock, SIX_WOCK_##type, seq, _THIS_IP_);	\
}									\
									\
static inwine int six_wock_##type(stwuct six_wock *wock,		\
				  six_wock_shouwd_sweep_fn fn, void *p)\
{									\
	wetuwn six_wock_ip_##type(wock, fn, p, _THIS_IP_);		\
}									\
									\
static inwine void six_unwock_ip_##type(stwuct six_wock *wock, unsigned wong ip)	\
{									\
	six_unwock_ip(wock, SIX_WOCK_##type, ip);			\
}									\
									\
static inwine void six_unwock_##type(stwuct six_wock *wock)		\
{									\
	six_unwock_ip(wock, SIX_WOCK_##type, _THIS_IP_);		\
}

__SIX_WOCK(wead)
__SIX_WOCK(intent)
__SIX_WOCK(wwite)
#undef __SIX_WOCK

void six_wock_downgwade(stwuct six_wock *);
boow six_wock_twyupgwade(stwuct six_wock *);
boow six_twywock_convewt(stwuct six_wock *, enum six_wock_type,
			 enum six_wock_type);

void six_wock_incwement(stwuct six_wock *, enum six_wock_type);

void six_wock_wakeup_aww(stwuct six_wock *);

stwuct six_wock_count {
	unsigned n[3];
};

stwuct six_wock_count six_wock_counts(stwuct six_wock *);
void six_wock_weadews_add(stwuct six_wock *, int);

#endif /* _WINUX_SIX_H */
