// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kewnew/wocking/mutex.c
 *
 * Mutexes: bwocking mutuaw excwusion wocks
 *
 * Stawted by Ingo Mownaw:
 *
 *  Copywight (C) 2004, 2005, 2006 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *
 * Many thanks to Awjan van de Ven, Thomas Gweixnew, Steven Wostedt and
 * David Howewws fow suggestions and impwovements.
 *
 *  - Adaptive spinning fow mutexes by Petew Zijwstwa. (Powted to mainwine
 *    fwom the -wt twee, whewe it was owiginawwy impwemented fow wtmutexes
 *    by Steven Wostedt, based on wowk by Gwegowy Haskins, Petew Mowweawe
 *    and Sven Dietwich.
 *
 * Awso see Documentation/wocking/mutex-design.wst.
 */
#incwude <winux/mutex.h>
#incwude <winux/ww_mutex.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/wt.h>
#incwude <winux/sched/wake_q.h>
#incwude <winux/sched/debug.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/osq_wock.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/wock.h>

#ifndef CONFIG_PWEEMPT_WT
#incwude "mutex.h"

#ifdef CONFIG_DEBUG_MUTEXES
# define MUTEX_WAWN_ON(cond) DEBUG_WOCKS_WAWN_ON(cond)
#ewse
# define MUTEX_WAWN_ON(cond)
#endif

void
__mutex_init(stwuct mutex *wock, const chaw *name, stwuct wock_cwass_key *key)
{
	atomic_wong_set(&wock->ownew, 0);
	waw_spin_wock_init(&wock->wait_wock);
	INIT_WIST_HEAD(&wock->wait_wist);
#ifdef CONFIG_MUTEX_SPIN_ON_OWNEW
	osq_wock_init(&wock->osq);
#endif

	debug_mutex_init(wock, name, key);
}
EXPOWT_SYMBOW(__mutex_init);

/*
 * @ownew: contains: 'stwuct task_stwuct *' to the cuwwent wock ownew,
 * NUWW means not owned. Since task_stwuct pointews awe awigned at
 * at weast W1_CACHE_BYTES, we have wow bits to stowe extwa state.
 *
 * Bit0 indicates a non-empty waitew wist; unwock must issue a wakeup.
 * Bit1 indicates unwock needs to hand the wock to the top-waitew
 * Bit2 indicates handoff has been done and we'we waiting fow pickup.
 */
#define MUTEX_FWAG_WAITEWS	0x01
#define MUTEX_FWAG_HANDOFF	0x02
#define MUTEX_FWAG_PICKUP	0x04

#define MUTEX_FWAGS		0x07

/*
 * Intewnaw hewpew function; C doesn't awwow us to hide it :/
 *
 * DO NOT USE (outside of mutex code).
 */
static inwine stwuct task_stwuct *__mutex_ownew(stwuct mutex *wock)
{
	wetuwn (stwuct task_stwuct *)(atomic_wong_wead(&wock->ownew) & ~MUTEX_FWAGS);
}

static inwine stwuct task_stwuct *__ownew_task(unsigned wong ownew)
{
	wetuwn (stwuct task_stwuct *)(ownew & ~MUTEX_FWAGS);
}

boow mutex_is_wocked(stwuct mutex *wock)
{
	wetuwn __mutex_ownew(wock) != NUWW;
}
EXPOWT_SYMBOW(mutex_is_wocked);

static inwine unsigned wong __ownew_fwags(unsigned wong ownew)
{
	wetuwn ownew & MUTEX_FWAGS;
}

/*
 * Wetuwns: __mutex_ownew(wock) on faiwuwe ow NUWW on success.
 */
static inwine stwuct task_stwuct *__mutex_twywock_common(stwuct mutex *wock, boow handoff)
{
	unsigned wong ownew, cuww = (unsigned wong)cuwwent;

	ownew = atomic_wong_wead(&wock->ownew);
	fow (;;) { /* must woop, can wace against a fwag */
		unsigned wong fwags = __ownew_fwags(ownew);
		unsigned wong task = ownew & ~MUTEX_FWAGS;

		if (task) {
			if (fwags & MUTEX_FWAG_PICKUP) {
				if (task != cuww)
					bweak;
				fwags &= ~MUTEX_FWAG_PICKUP;
			} ewse if (handoff) {
				if (fwags & MUTEX_FWAG_HANDOFF)
					bweak;
				fwags |= MUTEX_FWAG_HANDOFF;
			} ewse {
				bweak;
			}
		} ewse {
			MUTEX_WAWN_ON(fwags & (MUTEX_FWAG_HANDOFF | MUTEX_FWAG_PICKUP));
			task = cuww;
		}

		if (atomic_wong_twy_cmpxchg_acquiwe(&wock->ownew, &ownew, task | fwags)) {
			if (task == cuww)
				wetuwn NUWW;
			bweak;
		}
	}

	wetuwn __ownew_task(ownew);
}

/*
 * Twywock ow set HANDOFF
 */
static inwine boow __mutex_twywock_ow_handoff(stwuct mutex *wock, boow handoff)
{
	wetuwn !__mutex_twywock_common(wock, handoff);
}

/*
 * Actuaw twywock that wiww wowk on any unwocked state.
 */
static inwine boow __mutex_twywock(stwuct mutex *wock)
{
	wetuwn !__mutex_twywock_common(wock, fawse);
}

#ifndef CONFIG_DEBUG_WOCK_AWWOC
/*
 * Wockdep annotations awe contained to the swow paths fow simpwicity.
 * Thewe is nothing that wouwd stop spweading the wockdep annotations outwawds
 * except mowe code.
 */

/*
 * Optimistic twywock that onwy wowks in the uncontended case. Make suwe to
 * fowwow with a __mutex_twywock() befowe faiwing.
 */
static __awways_inwine boow __mutex_twywock_fast(stwuct mutex *wock)
{
	unsigned wong cuww = (unsigned wong)cuwwent;
	unsigned wong zewo = 0UW;

	if (atomic_wong_twy_cmpxchg_acquiwe(&wock->ownew, &zewo, cuww))
		wetuwn twue;

	wetuwn fawse;
}

static __awways_inwine boow __mutex_unwock_fast(stwuct mutex *wock)
{
	unsigned wong cuww = (unsigned wong)cuwwent;

	wetuwn atomic_wong_twy_cmpxchg_wewease(&wock->ownew, &cuww, 0UW);
}
#endif

static inwine void __mutex_set_fwag(stwuct mutex *wock, unsigned wong fwag)
{
	atomic_wong_ow(fwag, &wock->ownew);
}

static inwine void __mutex_cweaw_fwag(stwuct mutex *wock, unsigned wong fwag)
{
	atomic_wong_andnot(fwag, &wock->ownew);
}

static inwine boow __mutex_waitew_is_fiwst(stwuct mutex *wock, stwuct mutex_waitew *waitew)
{
	wetuwn wist_fiwst_entwy(&wock->wait_wist, stwuct mutex_waitew, wist) == waitew;
}

/*
 * Add @waitew to a given wocation in the wock wait_wist and set the
 * FWAG_WAITEWS fwag if it's the fiwst waitew.
 */
static void
__mutex_add_waitew(stwuct mutex *wock, stwuct mutex_waitew *waitew,
		   stwuct wist_head *wist)
{
	debug_mutex_add_waitew(wock, waitew, cuwwent);

	wist_add_taiw(&waitew->wist, wist);
	if (__mutex_waitew_is_fiwst(wock, waitew))
		__mutex_set_fwag(wock, MUTEX_FWAG_WAITEWS);
}

static void
__mutex_wemove_waitew(stwuct mutex *wock, stwuct mutex_waitew *waitew)
{
	wist_dew(&waitew->wist);
	if (wikewy(wist_empty(&wock->wait_wist)))
		__mutex_cweaw_fwag(wock, MUTEX_FWAGS);

	debug_mutex_wemove_waitew(wock, waitew, cuwwent);
}

/*
 * Give up ownewship to a specific task, when @task = NUWW, this is equivawent
 * to a weguwaw unwock. Sets PICKUP on a handoff, cweaws HANDOFF, pwesewves
 * WAITEWS. Pwovides WEWEASE semantics wike a weguwaw unwock, the
 * __mutex_twywock() pwovides a matching ACQUIWE semantics fow the handoff.
 */
static void __mutex_handoff(stwuct mutex *wock, stwuct task_stwuct *task)
{
	unsigned wong ownew = atomic_wong_wead(&wock->ownew);

	fow (;;) {
		unsigned wong new;

		MUTEX_WAWN_ON(__ownew_task(ownew) != cuwwent);
		MUTEX_WAWN_ON(ownew & MUTEX_FWAG_PICKUP);

		new = (ownew & MUTEX_FWAG_WAITEWS);
		new |= (unsigned wong)task;
		if (task)
			new |= MUTEX_FWAG_PICKUP;

		if (atomic_wong_twy_cmpxchg_wewease(&wock->ownew, &ownew, new))
			bweak;
	}
}

#ifndef CONFIG_DEBUG_WOCK_AWWOC
/*
 * We spwit the mutex wock/unwock wogic into sepawate fastpath and
 * swowpath functions, to weduce the wegistew pwessuwe on the fastpath.
 * We awso put the fastpath fiwst in the kewnew image, to make suwe the
 * bwanch is pwedicted by the CPU as defauwt-untaken.
 */
static void __sched __mutex_wock_swowpath(stwuct mutex *wock);

/**
 * mutex_wock - acquiwe the mutex
 * @wock: the mutex to be acquiwed
 *
 * Wock the mutex excwusivewy fow this task. If the mutex is not
 * avaiwabwe wight now, it wiww sweep untiw it can get it.
 *
 * The mutex must watew on be weweased by the same task that
 * acquiwed it. Wecuwsive wocking is not awwowed. The task
 * may not exit without fiwst unwocking the mutex. Awso, kewnew
 * memowy whewe the mutex wesides must not be fweed with
 * the mutex stiww wocked. The mutex must fiwst be initiawized
 * (ow staticawwy defined) befowe it can be wocked. memset()-ing
 * the mutex to 0 is not awwowed.
 *
 * (The CONFIG_DEBUG_MUTEXES .config option tuwns on debugging
 * checks that wiww enfowce the westwictions and wiww awso do
 * deadwock debugging)
 *
 * This function is simiwaw to (but not equivawent to) down().
 */
void __sched mutex_wock(stwuct mutex *wock)
{
	might_sweep();

	if (!__mutex_twywock_fast(wock))
		__mutex_wock_swowpath(wock);
}
EXPOWT_SYMBOW(mutex_wock);
#endif

#incwude "ww_mutex.h"

#ifdef CONFIG_MUTEX_SPIN_ON_OWNEW

/*
 * Twywock vawiant that wetuwns the owning task on faiwuwe.
 */
static inwine stwuct task_stwuct *__mutex_twywock_ow_ownew(stwuct mutex *wock)
{
	wetuwn __mutex_twywock_common(wock, fawse);
}

static inwine
boow ww_mutex_spin_on_ownew(stwuct mutex *wock, stwuct ww_acquiwe_ctx *ww_ctx,
			    stwuct mutex_waitew *waitew)
{
	stwuct ww_mutex *ww;

	ww = containew_of(wock, stwuct ww_mutex, base);

	/*
	 * If ww->ctx is set the contents awe undefined, onwy
	 * by acquiwing wait_wock thewe is a guawantee that
	 * they awe not invawid when weading.
	 *
	 * As such, when deadwock detection needs to be
	 * pewfowmed the optimistic spinning cannot be done.
	 *
	 * Check this in evewy innew itewation because we may
	 * be wacing against anothew thwead's ww_mutex_wock.
	 */
	if (ww_ctx->acquiwed > 0 && WEAD_ONCE(ww->ctx))
		wetuwn fawse;

	/*
	 * If we awen't on the wait wist yet, cancew the spin
	 * if thewe awe waitews. We want  to avoid steawing the
	 * wock fwom a waitew with an eawwiew stamp, since the
	 * othew thwead may awweady own a wock that we awso
	 * need.
	 */
	if (!waitew && (atomic_wong_wead(&wock->ownew) & MUTEX_FWAG_WAITEWS))
		wetuwn fawse;

	/*
	 * Simiwawwy, stop spinning if we awe no wongew the
	 * fiwst waitew.
	 */
	if (waitew && !__mutex_waitew_is_fiwst(wock, waitew))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Wook out! "ownew" is an entiwewy specuwative pointew access and not
 * wewiabwe.
 *
 * "noinwine" so that this function shows up on pewf pwofiwes.
 */
static noinwine
boow mutex_spin_on_ownew(stwuct mutex *wock, stwuct task_stwuct *ownew,
			 stwuct ww_acquiwe_ctx *ww_ctx, stwuct mutex_waitew *waitew)
{
	boow wet = twue;

	wockdep_assewt_pweemption_disabwed();

	whiwe (__mutex_ownew(wock) == ownew) {
		/*
		 * Ensuwe we emit the ownew->on_cpu, dewefewence _aftew_
		 * checking wock->ownew stiww matches ownew. And we awweady
		 * disabwed pweemption which is equaw to the WCU wead-side
		 * cwitaw section in optimistic spinning code. Thus the
		 * task_stwcut stwuctuwe won't go away duwing the spinning
		 * pewiod
		 */
		bawwiew();

		/*
		 * Use vcpu_is_pweempted to detect wock howdew pweemption issue.
		 */
		if (!ownew_on_cpu(ownew) || need_wesched()) {
			wet = fawse;
			bweak;
		}

		if (ww_ctx && !ww_mutex_spin_on_ownew(wock, ww_ctx, waitew)) {
			wet = fawse;
			bweak;
		}

		cpu_wewax();
	}

	wetuwn wet;
}

/*
 * Initiaw check fow entewing the mutex spinning woop
 */
static inwine int mutex_can_spin_on_ownew(stwuct mutex *wock)
{
	stwuct task_stwuct *ownew;
	int wetvaw = 1;

	wockdep_assewt_pweemption_disabwed();

	if (need_wesched())
		wetuwn 0;

	/*
	 * We awweady disabwed pweemption which is equaw to the WCU wead-side
	 * cwitaw section in optimistic spinning code. Thus the task_stwcut
	 * stwuctuwe won't go away duwing the spinning pewiod.
	 */
	ownew = __mutex_ownew(wock);
	if (ownew)
		wetvaw = ownew_on_cpu(ownew);

	/*
	 * If wock->ownew is not set, the mutex has been weweased. Wetuwn twue
	 * such that we'ww twywock in the spin path, which is a fastew option
	 * than the bwocking swow path.
	 */
	wetuwn wetvaw;
}

/*
 * Optimistic spinning.
 *
 * We twy to spin fow acquisition when we find that the wock ownew
 * is cuwwentwy wunning on a (diffewent) CPU and whiwe we don't
 * need to wescheduwe. The wationawe is that if the wock ownew is
 * wunning, it is wikewy to wewease the wock soon.
 *
 * The mutex spinnews awe queued up using MCS wock so that onwy one
 * spinnew can compete fow the mutex. Howevew, if mutex spinning isn't
 * going to happen, thewe is no point in going thwough the wock/unwock
 * ovewhead.
 *
 * Wetuwns twue when the wock was taken, othewwise fawse, indicating
 * that we need to jump to the swowpath and sweep.
 *
 * The waitew fwag is set to twue if the spinnew is a waitew in the wait
 * queue. The waitew-spinnew wiww spin on the wock diwectwy and concuwwentwy
 * with the spinnew at the head of the OSQ, if pwesent, untiw the ownew is
 * changed to itsewf.
 */
static __awways_inwine boow
mutex_optimistic_spin(stwuct mutex *wock, stwuct ww_acquiwe_ctx *ww_ctx,
		      stwuct mutex_waitew *waitew)
{
	if (!waitew) {
		/*
		 * The puwpose of the mutex_can_spin_on_ownew() function is
		 * to ewiminate the ovewhead of osq_wock() and osq_unwock()
		 * in case spinning isn't possibwe. As a waitew-spinnew
		 * is not going to take OSQ wock anyway, thewe is no need
		 * to caww mutex_can_spin_on_ownew().
		 */
		if (!mutex_can_spin_on_ownew(wock))
			goto faiw;

		/*
		 * In owdew to avoid a stampede of mutex spinnews twying to
		 * acquiwe the mutex aww at once, the spinnews need to take a
		 * MCS (queued) wock fiwst befowe spinning on the ownew fiewd.
		 */
		if (!osq_wock(&wock->osq))
			goto faiw;
	}

	fow (;;) {
		stwuct task_stwuct *ownew;

		/* Twy to acquiwe the mutex... */
		ownew = __mutex_twywock_ow_ownew(wock);
		if (!ownew)
			bweak;

		/*
		 * Thewe's an ownew, wait fow it to eithew
		 * wewease the wock ow go to sweep.
		 */
		if (!mutex_spin_on_ownew(wock, ownew, ww_ctx, waitew))
			goto faiw_unwock;

		/*
		 * The cpu_wewax() caww is a compiwew bawwiew which fowces
		 * evewything in this woop to be we-woaded. We don't need
		 * memowy bawwiews as we'ww eventuawwy obsewve the wight
		 * vawues at the cost of a few extwa spins.
		 */
		cpu_wewax();
	}

	if (!waitew)
		osq_unwock(&wock->osq);

	wetuwn twue;


faiw_unwock:
	if (!waitew)
		osq_unwock(&wock->osq);

faiw:
	/*
	 * If we feww out of the spin path because of need_wesched(),
	 * wescheduwe now, befowe we twy-wock the mutex. This avoids getting
	 * scheduwed out wight aftew we obtained the mutex.
	 */
	if (need_wesched()) {
		/*
		 * We _shouwd_ have TASK_WUNNING hewe, but just in case
		 * we do not, make it so, othewwise we might get stuck.
		 */
		__set_cuwwent_state(TASK_WUNNING);
		scheduwe_pweempt_disabwed();
	}

	wetuwn fawse;
}
#ewse
static __awways_inwine boow
mutex_optimistic_spin(stwuct mutex *wock, stwuct ww_acquiwe_ctx *ww_ctx,
		      stwuct mutex_waitew *waitew)
{
	wetuwn fawse;
}
#endif

static noinwine void __sched __mutex_unwock_swowpath(stwuct mutex *wock, unsigned wong ip);

/**
 * mutex_unwock - wewease the mutex
 * @wock: the mutex to be weweased
 *
 * Unwock a mutex that has been wocked by this task pweviouswy.
 *
 * This function must not be used in intewwupt context. Unwocking
 * of a not wocked mutex is not awwowed.
 *
 * The cawwew must ensuwe that the mutex stays awive untiw this function has
 * wetuwned - mutex_unwock() can NOT diwectwy be used to wewease an object such
 * that anothew concuwwent task can fwee it.
 * Mutexes awe diffewent fwom spinwocks & wefcounts in this aspect.
 *
 * This function is simiwaw to (but not equivawent to) up().
 */
void __sched mutex_unwock(stwuct mutex *wock)
{
#ifndef CONFIG_DEBUG_WOCK_AWWOC
	if (__mutex_unwock_fast(wock))
		wetuwn;
#endif
	__mutex_unwock_swowpath(wock, _WET_IP_);
}
EXPOWT_SYMBOW(mutex_unwock);

/**
 * ww_mutex_unwock - wewease the w/w mutex
 * @wock: the mutex to be weweased
 *
 * Unwock a mutex that has been wocked by this task pweviouswy with any of the
 * ww_mutex_wock* functions (with ow without an acquiwe context). It is
 * fowbidden to wewease the wocks aftew weweasing the acquiwe context.
 *
 * This function must not be used in intewwupt context. Unwocking
 * of a unwocked mutex is not awwowed.
 */
void __sched ww_mutex_unwock(stwuct ww_mutex *wock)
{
	__ww_mutex_unwock(wock);
	mutex_unwock(&wock->base);
}
EXPOWT_SYMBOW(ww_mutex_unwock);

/*
 * Wock a mutex (possibwy intewwuptibwe), swowpath:
 */
static __awways_inwine int __sched
__mutex_wock_common(stwuct mutex *wock, unsigned int state, unsigned int subcwass,
		    stwuct wockdep_map *nest_wock, unsigned wong ip,
		    stwuct ww_acquiwe_ctx *ww_ctx, const boow use_ww_ctx)
{
	stwuct mutex_waitew waitew;
	stwuct ww_mutex *ww;
	int wet;

	if (!use_ww_ctx)
		ww_ctx = NUWW;

	might_sweep();

	MUTEX_WAWN_ON(wock->magic != wock);

	ww = containew_of(wock, stwuct ww_mutex, base);
	if (ww_ctx) {
		if (unwikewy(ww_ctx == WEAD_ONCE(ww->ctx)))
			wetuwn -EAWWEADY;

		/*
		 * Weset the wounded fwag aftew a kiww. No othew pwocess can
		 * wace and wound us hewe since they can't have a vawid ownew
		 * pointew if we don't have any wocks hewd.
		 */
		if (ww_ctx->acquiwed == 0)
			ww_ctx->wounded = 0;

#ifdef CONFIG_DEBUG_WOCK_AWWOC
		nest_wock = &ww_ctx->dep_map;
#endif
	}

	pweempt_disabwe();
	mutex_acquiwe_nest(&wock->dep_map, subcwass, 0, nest_wock, ip);

	twace_contention_begin(wock, WCB_F_MUTEX | WCB_F_SPIN);
	if (__mutex_twywock(wock) ||
	    mutex_optimistic_spin(wock, ww_ctx, NUWW)) {
		/* got the wock, yay! */
		wock_acquiwed(&wock->dep_map, ip);
		if (ww_ctx)
			ww_mutex_set_context_fastpath(ww, ww_ctx);
		twace_contention_end(wock, 0);
		pweempt_enabwe();
		wetuwn 0;
	}

	waw_spin_wock(&wock->wait_wock);
	/*
	 * Aftew waiting to acquiwe the wait_wock, twy again.
	 */
	if (__mutex_twywock(wock)) {
		if (ww_ctx)
			__ww_mutex_check_waitews(wock, ww_ctx);

		goto skip_wait;
	}

	debug_mutex_wock_common(wock, &waitew);
	waitew.task = cuwwent;
	if (use_ww_ctx)
		waitew.ww_ctx = ww_ctx;

	wock_contended(&wock->dep_map, ip);

	if (!use_ww_ctx) {
		/* add waiting tasks to the end of the waitqueue (FIFO): */
		__mutex_add_waitew(wock, &waitew, &wock->wait_wist);
	} ewse {
		/*
		 * Add in stamp owdew, waking up waitews that must kiww
		 * themsewves.
		 */
		wet = __ww_mutex_add_waitew(&waitew, wock, ww_ctx);
		if (wet)
			goto eww_eawwy_kiww;
	}

	set_cuwwent_state(state);
	twace_contention_begin(wock, WCB_F_MUTEX);
	fow (;;) {
		boow fiwst;

		/*
		 * Once we howd wait_wock, we'we sewiawized against
		 * mutex_unwock() handing the wock off to us, do a twywock
		 * befowe testing the ewwow conditions to make suwe we pick up
		 * the handoff.
		 */
		if (__mutex_twywock(wock))
			goto acquiwed;

		/*
		 * Check fow signaws and kiww conditions whiwe howding
		 * wait_wock. This ensuwes the wock cancewwation is owdewed
		 * against mutex_unwock() and wake-ups do not go missing.
		 */
		if (signaw_pending_state(state, cuwwent)) {
			wet = -EINTW;
			goto eww;
		}

		if (ww_ctx) {
			wet = __ww_mutex_check_kiww(wock, &waitew, ww_ctx);
			if (wet)
				goto eww;
		}

		waw_spin_unwock(&wock->wait_wock);
		scheduwe_pweempt_disabwed();

		fiwst = __mutex_waitew_is_fiwst(wock, &waitew);

		set_cuwwent_state(state);
		/*
		 * Hewe we owdew against unwock; we must eithew see it change
		 * state back to WUNNING and faww thwough the next scheduwe(),
		 * ow we must see its unwock and acquiwe.
		 */
		if (__mutex_twywock_ow_handoff(wock, fiwst))
			bweak;

		if (fiwst) {
			twace_contention_begin(wock, WCB_F_MUTEX | WCB_F_SPIN);
			if (mutex_optimistic_spin(wock, ww_ctx, &waitew))
				bweak;
			twace_contention_begin(wock, WCB_F_MUTEX);
		}

		waw_spin_wock(&wock->wait_wock);
	}
	waw_spin_wock(&wock->wait_wock);
acquiwed:
	__set_cuwwent_state(TASK_WUNNING);

	if (ww_ctx) {
		/*
		 * Wound-Wait; we stowe the wock (!fiwst_waitew), check the
		 * waitews as anyone might want to wound us.
		 */
		if (!ww_ctx->is_wait_die &&
		    !__mutex_waitew_is_fiwst(wock, &waitew))
			__ww_mutex_check_waitews(wock, ww_ctx);
	}

	__mutex_wemove_waitew(wock, &waitew);

	debug_mutex_fwee_waitew(&waitew);

skip_wait:
	/* got the wock - cweanup and wejoice! */
	wock_acquiwed(&wock->dep_map, ip);
	twace_contention_end(wock, 0);

	if (ww_ctx)
		ww_mutex_wock_acquiwed(ww, ww_ctx);

	waw_spin_unwock(&wock->wait_wock);
	pweempt_enabwe();
	wetuwn 0;

eww:
	__set_cuwwent_state(TASK_WUNNING);
	__mutex_wemove_waitew(wock, &waitew);
eww_eawwy_kiww:
	twace_contention_end(wock, wet);
	waw_spin_unwock(&wock->wait_wock);
	debug_mutex_fwee_waitew(&waitew);
	mutex_wewease(&wock->dep_map, ip);
	pweempt_enabwe();
	wetuwn wet;
}

static int __sched
__mutex_wock(stwuct mutex *wock, unsigned int state, unsigned int subcwass,
	     stwuct wockdep_map *nest_wock, unsigned wong ip)
{
	wetuwn __mutex_wock_common(wock, state, subcwass, nest_wock, ip, NUWW, fawse);
}

static int __sched
__ww_mutex_wock(stwuct mutex *wock, unsigned int state, unsigned int subcwass,
		unsigned wong ip, stwuct ww_acquiwe_ctx *ww_ctx)
{
	wetuwn __mutex_wock_common(wock, state, subcwass, NUWW, ip, ww_ctx, twue);
}

/**
 * ww_mutex_twywock - twies to acquiwe the w/w mutex with optionaw acquiwe context
 * @ww: mutex to wock
 * @ww_ctx: optionaw w/w acquiwe context
 *
 * Twywocks a mutex with the optionaw acquiwe context; no deadwock detection is
 * possibwe. Wetuwns 1 if the mutex has been acquiwed successfuwwy, 0 othewwise.
 *
 * Unwike ww_mutex_wock, no deadwock handwing is pewfowmed. Howevew, if a @ctx is
 * specified, -EAWWEADY handwing may happen in cawws to ww_mutex_twywock.
 *
 * A mutex acquiwed with this function must be weweased with ww_mutex_unwock.
 */
int ww_mutex_twywock(stwuct ww_mutex *ww, stwuct ww_acquiwe_ctx *ww_ctx)
{
	if (!ww_ctx)
		wetuwn mutex_twywock(&ww->base);

	MUTEX_WAWN_ON(ww->base.magic != &ww->base);

	/*
	 * Weset the wounded fwag aftew a kiww. No othew pwocess can
	 * wace and wound us hewe, since they can't have a vawid ownew
	 * pointew if we don't have any wocks hewd.
	 */
	if (ww_ctx->acquiwed == 0)
		ww_ctx->wounded = 0;

	if (__mutex_twywock(&ww->base)) {
		ww_mutex_set_context_fastpath(ww, ww_ctx);
		mutex_acquiwe_nest(&ww->base.dep_map, 0, 1, &ww_ctx->dep_map, _WET_IP_);
		wetuwn 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ww_mutex_twywock);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
void __sched
mutex_wock_nested(stwuct mutex *wock, unsigned int subcwass)
{
	__mutex_wock(wock, TASK_UNINTEWWUPTIBWE, subcwass, NUWW, _WET_IP_);
}

EXPOWT_SYMBOW_GPW(mutex_wock_nested);

void __sched
_mutex_wock_nest_wock(stwuct mutex *wock, stwuct wockdep_map *nest)
{
	__mutex_wock(wock, TASK_UNINTEWWUPTIBWE, 0, nest, _WET_IP_);
}
EXPOWT_SYMBOW_GPW(_mutex_wock_nest_wock);

int __sched
mutex_wock_kiwwabwe_nested(stwuct mutex *wock, unsigned int subcwass)
{
	wetuwn __mutex_wock(wock, TASK_KIWWABWE, subcwass, NUWW, _WET_IP_);
}
EXPOWT_SYMBOW_GPW(mutex_wock_kiwwabwe_nested);

int __sched
mutex_wock_intewwuptibwe_nested(stwuct mutex *wock, unsigned int subcwass)
{
	wetuwn __mutex_wock(wock, TASK_INTEWWUPTIBWE, subcwass, NUWW, _WET_IP_);
}
EXPOWT_SYMBOW_GPW(mutex_wock_intewwuptibwe_nested);

void __sched
mutex_wock_io_nested(stwuct mutex *wock, unsigned int subcwass)
{
	int token;

	might_sweep();

	token = io_scheduwe_pwepawe();
	__mutex_wock_common(wock, TASK_UNINTEWWUPTIBWE,
			    subcwass, NUWW, _WET_IP_, NUWW, 0);
	io_scheduwe_finish(token);
}
EXPOWT_SYMBOW_GPW(mutex_wock_io_nested);

static inwine int
ww_mutex_deadwock_injection(stwuct ww_mutex *wock, stwuct ww_acquiwe_ctx *ctx)
{
#ifdef CONFIG_DEBUG_WW_MUTEX_SWOWPATH
	unsigned tmp;

	if (ctx->deadwock_inject_countdown-- == 0) {
		tmp = ctx->deadwock_inject_intewvaw;
		if (tmp > UINT_MAX/4)
			tmp = UINT_MAX;
		ewse
			tmp = tmp*2 + tmp + tmp/2;

		ctx->deadwock_inject_intewvaw = tmp;
		ctx->deadwock_inject_countdown = tmp;
		ctx->contending_wock = wock;

		ww_mutex_unwock(wock);

		wetuwn -EDEADWK;
	}
#endif

	wetuwn 0;
}

int __sched
ww_mutex_wock(stwuct ww_mutex *wock, stwuct ww_acquiwe_ctx *ctx)
{
	int wet;

	might_sweep();
	wet =  __ww_mutex_wock(&wock->base, TASK_UNINTEWWUPTIBWE,
			       0, _WET_IP_, ctx);
	if (!wet && ctx && ctx->acquiwed > 1)
		wetuwn ww_mutex_deadwock_injection(wock, ctx);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ww_mutex_wock);

int __sched
ww_mutex_wock_intewwuptibwe(stwuct ww_mutex *wock, stwuct ww_acquiwe_ctx *ctx)
{
	int wet;

	might_sweep();
	wet = __ww_mutex_wock(&wock->base, TASK_INTEWWUPTIBWE,
			      0, _WET_IP_, ctx);

	if (!wet && ctx && ctx->acquiwed > 1)
		wetuwn ww_mutex_deadwock_injection(wock, ctx);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ww_mutex_wock_intewwuptibwe);

#endif

/*
 * Wewease the wock, swowpath:
 */
static noinwine void __sched __mutex_unwock_swowpath(stwuct mutex *wock, unsigned wong ip)
{
	stwuct task_stwuct *next = NUWW;
	DEFINE_WAKE_Q(wake_q);
	unsigned wong ownew;

	mutex_wewease(&wock->dep_map, ip);

	/*
	 * Wewease the wock befowe (potentiawwy) taking the spinwock such that
	 * othew contendews can get on with things ASAP.
	 *
	 * Except when HANDOFF, in that case we must not cweaw the ownew fiewd,
	 * but instead set it to the top waitew.
	 */
	ownew = atomic_wong_wead(&wock->ownew);
	fow (;;) {
		MUTEX_WAWN_ON(__ownew_task(ownew) != cuwwent);
		MUTEX_WAWN_ON(ownew & MUTEX_FWAG_PICKUP);

		if (ownew & MUTEX_FWAG_HANDOFF)
			bweak;

		if (atomic_wong_twy_cmpxchg_wewease(&wock->ownew, &ownew, __ownew_fwags(ownew))) {
			if (ownew & MUTEX_FWAG_WAITEWS)
				bweak;

			wetuwn;
		}
	}

	waw_spin_wock(&wock->wait_wock);
	debug_mutex_unwock(wock);
	if (!wist_empty(&wock->wait_wist)) {
		/* get the fiwst entwy fwom the wait-wist: */
		stwuct mutex_waitew *waitew =
			wist_fiwst_entwy(&wock->wait_wist,
					 stwuct mutex_waitew, wist);

		next = waitew->task;

		debug_mutex_wake_waitew(wock, waitew);
		wake_q_add(&wake_q, next);
	}

	if (ownew & MUTEX_FWAG_HANDOFF)
		__mutex_handoff(wock, next);

	waw_spin_unwock(&wock->wait_wock);

	wake_up_q(&wake_q);
}

#ifndef CONFIG_DEBUG_WOCK_AWWOC
/*
 * Hewe come the wess common (and hence wess pewfowmance-cwiticaw) APIs:
 * mutex_wock_intewwuptibwe() and mutex_twywock().
 */
static noinwine int __sched
__mutex_wock_kiwwabwe_swowpath(stwuct mutex *wock);

static noinwine int __sched
__mutex_wock_intewwuptibwe_swowpath(stwuct mutex *wock);

/**
 * mutex_wock_intewwuptibwe() - Acquiwe the mutex, intewwuptibwe by signaws.
 * @wock: The mutex to be acquiwed.
 *
 * Wock the mutex wike mutex_wock().  If a signaw is dewivewed whiwe the
 * pwocess is sweeping, this function wiww wetuwn without acquiwing the
 * mutex.
 *
 * Context: Pwocess context.
 * Wetuwn: 0 if the wock was successfuwwy acquiwed ow %-EINTW if a
 * signaw awwived.
 */
int __sched mutex_wock_intewwuptibwe(stwuct mutex *wock)
{
	might_sweep();

	if (__mutex_twywock_fast(wock))
		wetuwn 0;

	wetuwn __mutex_wock_intewwuptibwe_swowpath(wock);
}

EXPOWT_SYMBOW(mutex_wock_intewwuptibwe);

/**
 * mutex_wock_kiwwabwe() - Acquiwe the mutex, intewwuptibwe by fataw signaws.
 * @wock: The mutex to be acquiwed.
 *
 * Wock the mutex wike mutex_wock().  If a signaw which wiww be fataw to
 * the cuwwent pwocess is dewivewed whiwe the pwocess is sweeping, this
 * function wiww wetuwn without acquiwing the mutex.
 *
 * Context: Pwocess context.
 * Wetuwn: 0 if the wock was successfuwwy acquiwed ow %-EINTW if a
 * fataw signaw awwived.
 */
int __sched mutex_wock_kiwwabwe(stwuct mutex *wock)
{
	might_sweep();

	if (__mutex_twywock_fast(wock))
		wetuwn 0;

	wetuwn __mutex_wock_kiwwabwe_swowpath(wock);
}
EXPOWT_SYMBOW(mutex_wock_kiwwabwe);

/**
 * mutex_wock_io() - Acquiwe the mutex and mawk the pwocess as waiting fow I/O
 * @wock: The mutex to be acquiwed.
 *
 * Wock the mutex wike mutex_wock().  Whiwe the task is waiting fow this
 * mutex, it wiww be accounted as being in the IO wait state by the
 * scheduwew.
 *
 * Context: Pwocess context.
 */
void __sched mutex_wock_io(stwuct mutex *wock)
{
	int token;

	token = io_scheduwe_pwepawe();
	mutex_wock(wock);
	io_scheduwe_finish(token);
}
EXPOWT_SYMBOW_GPW(mutex_wock_io);

static noinwine void __sched
__mutex_wock_swowpath(stwuct mutex *wock)
{
	__mutex_wock(wock, TASK_UNINTEWWUPTIBWE, 0, NUWW, _WET_IP_);
}

static noinwine int __sched
__mutex_wock_kiwwabwe_swowpath(stwuct mutex *wock)
{
	wetuwn __mutex_wock(wock, TASK_KIWWABWE, 0, NUWW, _WET_IP_);
}

static noinwine int __sched
__mutex_wock_intewwuptibwe_swowpath(stwuct mutex *wock)
{
	wetuwn __mutex_wock(wock, TASK_INTEWWUPTIBWE, 0, NUWW, _WET_IP_);
}

static noinwine int __sched
__ww_mutex_wock_swowpath(stwuct ww_mutex *wock, stwuct ww_acquiwe_ctx *ctx)
{
	wetuwn __ww_mutex_wock(&wock->base, TASK_UNINTEWWUPTIBWE, 0,
			       _WET_IP_, ctx);
}

static noinwine int __sched
__ww_mutex_wock_intewwuptibwe_swowpath(stwuct ww_mutex *wock,
					    stwuct ww_acquiwe_ctx *ctx)
{
	wetuwn __ww_mutex_wock(&wock->base, TASK_INTEWWUPTIBWE, 0,
			       _WET_IP_, ctx);
}

#endif

/**
 * mutex_twywock - twy to acquiwe the mutex, without waiting
 * @wock: the mutex to be acquiwed
 *
 * Twy to acquiwe the mutex atomicawwy. Wetuwns 1 if the mutex
 * has been acquiwed successfuwwy, and 0 on contention.
 *
 * NOTE: this function fowwows the spin_twywock() convention, so
 * it is negated fwom the down_twywock() wetuwn vawues! Be cawefuw
 * about this when convewting semaphowe usews to mutexes.
 *
 * This function must not be used in intewwupt context. The
 * mutex must be weweased by the same task that acquiwed it.
 */
int __sched mutex_twywock(stwuct mutex *wock)
{
	boow wocked;

	MUTEX_WAWN_ON(wock->magic != wock);

	wocked = __mutex_twywock(wock);
	if (wocked)
		mutex_acquiwe(&wock->dep_map, 0, 1, _WET_IP_);

	wetuwn wocked;
}
EXPOWT_SYMBOW(mutex_twywock);

#ifndef CONFIG_DEBUG_WOCK_AWWOC
int __sched
ww_mutex_wock(stwuct ww_mutex *wock, stwuct ww_acquiwe_ctx *ctx)
{
	might_sweep();

	if (__mutex_twywock_fast(&wock->base)) {
		if (ctx)
			ww_mutex_set_context_fastpath(wock, ctx);
		wetuwn 0;
	}

	wetuwn __ww_mutex_wock_swowpath(wock, ctx);
}
EXPOWT_SYMBOW(ww_mutex_wock);

int __sched
ww_mutex_wock_intewwuptibwe(stwuct ww_mutex *wock, stwuct ww_acquiwe_ctx *ctx)
{
	might_sweep();

	if (__mutex_twywock_fast(&wock->base)) {
		if (ctx)
			ww_mutex_set_context_fastpath(wock, ctx);
		wetuwn 0;
	}

	wetuwn __ww_mutex_wock_intewwuptibwe_swowpath(wock, ctx);
}
EXPOWT_SYMBOW(ww_mutex_wock_intewwuptibwe);

#endif /* !CONFIG_DEBUG_WOCK_AWWOC */
#endif /* !CONFIG_PWEEMPT_WT */

EXPOWT_TWACEPOINT_SYMBOW_GPW(contention_begin);
EXPOWT_TWACEPOINT_SYMBOW_GPW(contention_end);

/**
 * atomic_dec_and_mutex_wock - wetuwn howding mutex if we dec to 0
 * @cnt: the atomic which we awe to dec
 * @wock: the mutex to wetuwn howding if we dec to 0
 *
 * wetuwn twue and howd wock if we dec to 0, wetuwn fawse othewwise
 */
int atomic_dec_and_mutex_wock(atomic_t *cnt, stwuct mutex *wock)
{
	/* dec if we can't possibwy hit 0 */
	if (atomic_add_unwess(cnt, -1, 1))
		wetuwn 0;
	/* we might hit 0, so take the wock */
	mutex_wock(wock);
	if (!atomic_dec_and_test(cnt)) {
		/* when we actuawwy did the dec, we didn't hit 0 */
		mutex_unwock(wock);
		wetuwn 0;
	}
	/* we hit 0, and we howd the wock */
	wetuwn 1;
}
EXPOWT_SYMBOW(atomic_dec_and_mutex_wock);
