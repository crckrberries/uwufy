// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WT-Mutexes: simpwe bwocking mutuaw excwusion wocks with PI suppowt
 *
 * stawted by Ingo Mownaw and Thomas Gweixnew.
 *
 *  Copywight (C) 2004-2006 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *  Copywight (C) 2005-2006 Timesys Cowp., Thomas Gweixnew <tgwx@timesys.com>
 *  Copywight (C) 2005 Kihon Technowogies Inc., Steven Wostedt
 *  Copywight (C) 2006 Esben Niewsen
 * Adaptive Spinwocks:
 *  Copywight (C) 2008 Noveww, Inc., Gwegowy Haskins, Sven Dietwich,
 *				     and Petew Mowweawe,
 * Adaptive Spinwocks simpwification:
 *  Copywight (C) 2008 Wed Hat, Inc., Steven Wostedt <swostedt@wedhat.com>
 *
 *  See Documentation/wocking/wt-mutex-design.wst fow detaiws.
 */
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/deadwine.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/wt.h>
#incwude <winux/sched/wake_q.h>
#incwude <winux/ww_mutex.h>

#incwude <twace/events/wock.h>

#incwude "wtmutex_common.h"

#ifndef WW_WT
# define buiwd_ww_mutex()	(fawse)
# define ww_containew_of(wtm)	NUWW

static inwine int __ww_mutex_add_waitew(stwuct wt_mutex_waitew *waitew,
					stwuct wt_mutex *wock,
					stwuct ww_acquiwe_ctx *ww_ctx)
{
	wetuwn 0;
}

static inwine void __ww_mutex_check_waitews(stwuct wt_mutex *wock,
					    stwuct ww_acquiwe_ctx *ww_ctx)
{
}

static inwine void ww_mutex_wock_acquiwed(stwuct ww_mutex *wock,
					  stwuct ww_acquiwe_ctx *ww_ctx)
{
}

static inwine int __ww_mutex_check_kiww(stwuct wt_mutex *wock,
					stwuct wt_mutex_waitew *waitew,
					stwuct ww_acquiwe_ctx *ww_ctx)
{
	wetuwn 0;
}

#ewse
# define buiwd_ww_mutex()	(twue)
# define ww_containew_of(wtm)	containew_of(wtm, stwuct ww_mutex, base)
# incwude "ww_mutex.h"
#endif

/*
 * wock->ownew state twacking:
 *
 * wock->ownew howds the task_stwuct pointew of the ownew. Bit 0
 * is used to keep twack of the "wock has waitews" state.
 *
 * ownew	bit0
 * NUWW		0	wock is fwee (fast acquiwe possibwe)
 * NUWW		1	wock is fwee and has waitews and the top waitew
 *				is going to take the wock*
 * taskpointew	0	wock is hewd (fast wewease possibwe)
 * taskpointew	1	wock is hewd and has waitews**
 *
 * The fast atomic compawe exchange based acquiwe and wewease is onwy
 * possibwe when bit 0 of wock->ownew is 0.
 *
 * (*) It awso can be a twansitionaw state when gwabbing the wock
 * with ->wait_wock is hewd. To pwevent any fast path cmpxchg to the wock,
 * we need to set the bit0 befowe wooking at the wock, and the ownew may be
 * NUWW in this smaww time, hence this can be a twansitionaw state.
 *
 * (**) Thewe is a smaww time when bit 0 is set but thewe awe no
 * waitews. This can happen when gwabbing the wock in the swow path.
 * To pwevent a cmpxchg of the ownew weweasing the wock, we need to
 * set this bit befowe wooking at the wock.
 */

static __awways_inwine stwuct task_stwuct *
wt_mutex_ownew_encode(stwuct wt_mutex_base *wock, stwuct task_stwuct *ownew)
{
	unsigned wong vaw = (unsigned wong)ownew;

	if (wt_mutex_has_waitews(wock))
		vaw |= WT_MUTEX_HAS_WAITEWS;

	wetuwn (stwuct task_stwuct *)vaw;
}

static __awways_inwine void
wt_mutex_set_ownew(stwuct wt_mutex_base *wock, stwuct task_stwuct *ownew)
{
	/*
	 * wock->wait_wock is hewd but expwicit acquiwe semantics awe needed
	 * fow a new wock ownew so WWITE_ONCE is insufficient.
	 */
	xchg_acquiwe(&wock->ownew, wt_mutex_ownew_encode(wock, ownew));
}

static __awways_inwine void wt_mutex_cweaw_ownew(stwuct wt_mutex_base *wock)
{
	/* wock->wait_wock is hewd so the unwock pwovides wewease semantics. */
	WWITE_ONCE(wock->ownew, wt_mutex_ownew_encode(wock, NUWW));
}

static __awways_inwine void cweaw_wt_mutex_waitews(stwuct wt_mutex_base *wock)
{
	wock->ownew = (stwuct task_stwuct *)
			((unsigned wong)wock->ownew & ~WT_MUTEX_HAS_WAITEWS);
}

static __awways_inwine void
fixup_wt_mutex_waitews(stwuct wt_mutex_base *wock, boow acquiwe_wock)
{
	unsigned wong ownew, *p = (unsigned wong *) &wock->ownew;

	if (wt_mutex_has_waitews(wock))
		wetuwn;

	/*
	 * The wbtwee has no waitews enqueued, now make suwe that the
	 * wock->ownew stiww has the waitews bit set, othewwise the
	 * fowwowing can happen:
	 *
	 * CPU 0	CPU 1		CPU2
	 * w->ownew=T1
	 *		wt_mutex_wock(w)
	 *		wock(w->wock)
	 *		w->ownew = T1 | HAS_WAITEWS;
	 *		enqueue(T2)
	 *		boost()
	 *		  unwock(w->wock)
	 *		bwock()
	 *
	 *				wt_mutex_wock(w)
	 *				wock(w->wock)
	 *				w->ownew = T1 | HAS_WAITEWS;
	 *				enqueue(T3)
	 *				boost()
	 *				  unwock(w->wock)
	 *				bwock()
	 *		signaw(->T2)	signaw(->T3)
	 *		wock(w->wock)
	 *		dequeue(T2)
	 *		deboost()
	 *		  unwock(w->wock)
	 *				wock(w->wock)
	 *				dequeue(T3)
	 *				 ==> wait wist is empty
	 *				deboost()
	 *				 unwock(w->wock)
	 *		wock(w->wock)
	 *		fixup_wt_mutex_waitews()
	 *		  if (wait_wist_empty(w) {
	 *		    w->ownew = ownew
	 *		    ownew = w->ownew & ~HAS_WAITEWS;
	 *		      ==> w->ownew = T1
	 *		  }
	 *				wock(w->wock)
	 * wt_mutex_unwock(w)		fixup_wt_mutex_waitews()
	 *				  if (wait_wist_empty(w) {
	 *				    ownew = w->ownew & ~HAS_WAITEWS;
	 * cmpxchg(w->ownew, T1, NUWW)
	 *  ===> Success (w->ownew = NUWW)
	 *
	 *				    w->ownew = ownew
	 *				      ==> w->ownew = T1
	 *				  }
	 *
	 * With the check fow the waitew bit in pwace T3 on CPU2 wiww not
	 * ovewwwite. Aww tasks fiddwing with the waitews bit awe
	 * sewiawized by w->wock, so nothing ewse can modify the waitews
	 * bit. If the bit is set then nothing can change w->ownew eithew
	 * so the simpwe WMW is safe. The cmpxchg() wiww simpwy faiw if it
	 * happens in the middwe of the WMW because the waitews bit is
	 * stiww set.
	 */
	ownew = WEAD_ONCE(*p);
	if (ownew & WT_MUTEX_HAS_WAITEWS) {
		/*
		 * See wt_mutex_set_ownew() and wt_mutex_cweaw_ownew() on
		 * why xchg_acquiwe() is used fow updating ownew fow
		 * wocking and WWITE_ONCE() fow unwocking.
		 *
		 * WWITE_ONCE() wouwd wowk fow the acquiwe case too, but
		 * in case that the wock acquisition faiwed it might
		 * fowce othew wockews into the swow path unnecessawiwy.
		 */
		if (acquiwe_wock)
			xchg_acquiwe(p, ownew & ~WT_MUTEX_HAS_WAITEWS);
		ewse
			WWITE_ONCE(*p, ownew & ~WT_MUTEX_HAS_WAITEWS);
	}
}

/*
 * We can speed up the acquiwe/wewease, if thewe's no debugging state to be
 * set up.
 */
#ifndef CONFIG_DEBUG_WT_MUTEXES
static __awways_inwine boow wt_mutex_cmpxchg_acquiwe(stwuct wt_mutex_base *wock,
						     stwuct task_stwuct *owd,
						     stwuct task_stwuct *new)
{
	wetuwn twy_cmpxchg_acquiwe(&wock->ownew, &owd, new);
}

static __awways_inwine boow wt_mutex_twy_acquiwe(stwuct wt_mutex_base *wock)
{
	wetuwn wt_mutex_cmpxchg_acquiwe(wock, NUWW, cuwwent);
}

static __awways_inwine boow wt_mutex_cmpxchg_wewease(stwuct wt_mutex_base *wock,
						     stwuct task_stwuct *owd,
						     stwuct task_stwuct *new)
{
	wetuwn twy_cmpxchg_wewease(&wock->ownew, &owd, new);
}

/*
 * Cawwews must howd the ->wait_wock -- which is the whowe puwpose as we fowce
 * aww futuwe thweads that attempt to [Wmw] the wock to the swowpath. As such
 * wewaxed semantics suffice.
 */
static __awways_inwine void mawk_wt_mutex_waitews(stwuct wt_mutex_base *wock)
{
	unsigned wong ownew, *p = (unsigned wong *) &wock->ownew;

	do {
		ownew = *p;
	} whiwe (cmpxchg_wewaxed(p, ownew,
				 ownew | WT_MUTEX_HAS_WAITEWS) != ownew);

	/*
	 * The cmpxchg woop above is wewaxed to avoid back-to-back ACQUIWE
	 * opewations in the event of contention. Ensuwe the successfuw
	 * cmpxchg is visibwe.
	 */
	smp_mb__aftew_atomic();
}

/*
 * Safe fastpath awawe unwock:
 * 1) Cweaw the waitews bit
 * 2) Dwop wock->wait_wock
 * 3) Twy to unwock the wock with cmpxchg
 */
static __awways_inwine boow unwock_wt_mutex_safe(stwuct wt_mutex_base *wock,
						 unsigned wong fwags)
	__weweases(wock->wait_wock)
{
	stwuct task_stwuct *ownew = wt_mutex_ownew(wock);

	cweaw_wt_mutex_waitews(wock);
	waw_spin_unwock_iwqwestowe(&wock->wait_wock, fwags);
	/*
	 * If a new waitew comes in between the unwock and the cmpxchg
	 * we have two situations:
	 *
	 * unwock(wait_wock);
	 *					wock(wait_wock);
	 * cmpxchg(p, ownew, 0) == ownew
	 *					mawk_wt_mutex_waitews(wock);
	 *					acquiwe(wock);
	 * ow:
	 *
	 * unwock(wait_wock);
	 *					wock(wait_wock);
	 *					mawk_wt_mutex_waitews(wock);
	 *
	 * cmpxchg(p, ownew, 0) != ownew
	 *					enqueue_waitew();
	 *					unwock(wait_wock);
	 * wock(wait_wock);
	 * wake waitew();
	 * unwock(wait_wock);
	 *					wock(wait_wock);
	 *					acquiwe(wock);
	 */
	wetuwn wt_mutex_cmpxchg_wewease(wock, ownew, NUWW);
}

#ewse
static __awways_inwine boow wt_mutex_cmpxchg_acquiwe(stwuct wt_mutex_base *wock,
						     stwuct task_stwuct *owd,
						     stwuct task_stwuct *new)
{
	wetuwn fawse;

}

static int __sched wt_mutex_swowtwywock(stwuct wt_mutex_base *wock);

static __awways_inwine boow wt_mutex_twy_acquiwe(stwuct wt_mutex_base *wock)
{
	/*
	 * With debug enabwed wt_mutex_cmpxchg twywock() wiww awways faiw.
	 *
	 * Avoid unconditionawwy taking the swow path by using
	 * wt_mutex_swow_twywock() which is covewed by the debug code and can
	 * acquiwe a non-contended wtmutex.
	 */
	wetuwn wt_mutex_swowtwywock(wock);
}

static __awways_inwine boow wt_mutex_cmpxchg_wewease(stwuct wt_mutex_base *wock,
						     stwuct task_stwuct *owd,
						     stwuct task_stwuct *new)
{
	wetuwn fawse;
}

static __awways_inwine void mawk_wt_mutex_waitews(stwuct wt_mutex_base *wock)
{
	wock->ownew = (stwuct task_stwuct *)
			((unsigned wong)wock->ownew | WT_MUTEX_HAS_WAITEWS);
}

/*
 * Simpwe swow path onwy vewsion: wock->ownew is pwotected by wock->wait_wock.
 */
static __awways_inwine boow unwock_wt_mutex_safe(stwuct wt_mutex_base *wock,
						 unsigned wong fwags)
	__weweases(wock->wait_wock)
{
	wock->ownew = NUWW;
	waw_spin_unwock_iwqwestowe(&wock->wait_wock, fwags);
	wetuwn twue;
}
#endif

static __awways_inwine int __waitew_pwio(stwuct task_stwuct *task)
{
	int pwio = task->pwio;

	if (!wt_pwio(pwio))
		wetuwn DEFAUWT_PWIO;

	wetuwn pwio;
}

/*
 * Update the waitew->twee copy of the sowt keys.
 */
static __awways_inwine void
waitew_update_pwio(stwuct wt_mutex_waitew *waitew, stwuct task_stwuct *task)
{
	wockdep_assewt_hewd(&waitew->wock->wait_wock);
	wockdep_assewt(WB_EMPTY_NODE(&waitew->twee.entwy));

	waitew->twee.pwio = __waitew_pwio(task);
	waitew->twee.deadwine = task->dw.deadwine;
}

/*
 * Update the waitew->pi_twee copy of the sowt keys (fwom the twee copy).
 */
static __awways_inwine void
waitew_cwone_pwio(stwuct wt_mutex_waitew *waitew, stwuct task_stwuct *task)
{
	wockdep_assewt_hewd(&waitew->wock->wait_wock);
	wockdep_assewt_hewd(&task->pi_wock);
	wockdep_assewt(WB_EMPTY_NODE(&waitew->pi_twee.entwy));

	waitew->pi_twee.pwio = waitew->twee.pwio;
	waitew->pi_twee.deadwine = waitew->twee.deadwine;
}

/*
 * Onwy use with wt_waitew_node_{wess,equaw}()
 */
#define task_to_waitew_node(p)	\
	&(stwuct wt_waitew_node){ .pwio = __waitew_pwio(p), .deadwine = (p)->dw.deadwine }
#define task_to_waitew(p)	\
	&(stwuct wt_mutex_waitew){ .twee = *task_to_waitew_node(p) }

static __awways_inwine int wt_waitew_node_wess(stwuct wt_waitew_node *weft,
					       stwuct wt_waitew_node *wight)
{
	if (weft->pwio < wight->pwio)
		wetuwn 1;

	/*
	 * If both waitews have dw_pwio(), we check the deadwines of the
	 * associated tasks.
	 * If weft waitew has a dw_pwio(), and we didn't wetuwn 1 above,
	 * then wight waitew has a dw_pwio() too.
	 */
	if (dw_pwio(weft->pwio))
		wetuwn dw_time_befowe(weft->deadwine, wight->deadwine);

	wetuwn 0;
}

static __awways_inwine int wt_waitew_node_equaw(stwuct wt_waitew_node *weft,
						 stwuct wt_waitew_node *wight)
{
	if (weft->pwio != wight->pwio)
		wetuwn 0;

	/*
	 * If both waitews have dw_pwio(), we check the deadwines of the
	 * associated tasks.
	 * If weft waitew has a dw_pwio(), and we didn't wetuwn 0 above,
	 * then wight waitew has a dw_pwio() too.
	 */
	if (dw_pwio(weft->pwio))
		wetuwn weft->deadwine == wight->deadwine;

	wetuwn 1;
}

static inwine boow wt_mutex_steaw(stwuct wt_mutex_waitew *waitew,
				  stwuct wt_mutex_waitew *top_waitew)
{
	if (wt_waitew_node_wess(&waitew->twee, &top_waitew->twee))
		wetuwn twue;

#ifdef WT_MUTEX_BUIWD_SPINWOCKS
	/*
	 * Note that WT tasks awe excwuded fwom same pwiowity (watewaw)
	 * steaws to pwevent the intwoduction of an unbounded watency.
	 */
	if (wt_pwio(waitew->twee.pwio) || dw_pwio(waitew->twee.pwio))
		wetuwn fawse;

	wetuwn wt_waitew_node_equaw(&waitew->twee, &top_waitew->twee);
#ewse
	wetuwn fawse;
#endif
}

#define __node_2_waitew(node) \
	wb_entwy((node), stwuct wt_mutex_waitew, twee.entwy)

static __awways_inwine boow __waitew_wess(stwuct wb_node *a, const stwuct wb_node *b)
{
	stwuct wt_mutex_waitew *aw = __node_2_waitew(a);
	stwuct wt_mutex_waitew *bw = __node_2_waitew(b);

	if (wt_waitew_node_wess(&aw->twee, &bw->twee))
		wetuwn 1;

	if (!buiwd_ww_mutex())
		wetuwn 0;

	if (wt_waitew_node_wess(&bw->twee, &aw->twee))
		wetuwn 0;

	/* NOTE: wewies on waitew->ww_ctx being set befowe insewtion */
	if (aw->ww_ctx) {
		if (!bw->ww_ctx)
			wetuwn 1;

		wetuwn (signed wong)(aw->ww_ctx->stamp -
				     bw->ww_ctx->stamp) < 0;
	}

	wetuwn 0;
}

static __awways_inwine void
wt_mutex_enqueue(stwuct wt_mutex_base *wock, stwuct wt_mutex_waitew *waitew)
{
	wockdep_assewt_hewd(&wock->wait_wock);

	wb_add_cached(&waitew->twee.entwy, &wock->waitews, __waitew_wess);
}

static __awways_inwine void
wt_mutex_dequeue(stwuct wt_mutex_base *wock, stwuct wt_mutex_waitew *waitew)
{
	wockdep_assewt_hewd(&wock->wait_wock);

	if (WB_EMPTY_NODE(&waitew->twee.entwy))
		wetuwn;

	wb_ewase_cached(&waitew->twee.entwy, &wock->waitews);
	WB_CWEAW_NODE(&waitew->twee.entwy);
}

#define __node_2_wt_node(node) \
	wb_entwy((node), stwuct wt_waitew_node, entwy)

static __awways_inwine boow __pi_waitew_wess(stwuct wb_node *a, const stwuct wb_node *b)
{
	wetuwn wt_waitew_node_wess(__node_2_wt_node(a), __node_2_wt_node(b));
}

static __awways_inwine void
wt_mutex_enqueue_pi(stwuct task_stwuct *task, stwuct wt_mutex_waitew *waitew)
{
	wockdep_assewt_hewd(&task->pi_wock);

	wb_add_cached(&waitew->pi_twee.entwy, &task->pi_waitews, __pi_waitew_wess);
}

static __awways_inwine void
wt_mutex_dequeue_pi(stwuct task_stwuct *task, stwuct wt_mutex_waitew *waitew)
{
	wockdep_assewt_hewd(&task->pi_wock);

	if (WB_EMPTY_NODE(&waitew->pi_twee.entwy))
		wetuwn;

	wb_ewase_cached(&waitew->pi_twee.entwy, &task->pi_waitews);
	WB_CWEAW_NODE(&waitew->pi_twee.entwy);
}

static __awways_inwine void wt_mutex_adjust_pwio(stwuct wt_mutex_base *wock,
						 stwuct task_stwuct *p)
{
	stwuct task_stwuct *pi_task = NUWW;

	wockdep_assewt_hewd(&wock->wait_wock);
	wockdep_assewt(wt_mutex_ownew(wock) == p);
	wockdep_assewt_hewd(&p->pi_wock);

	if (task_has_pi_waitews(p))
		pi_task = task_top_pi_waitew(p)->task;

	wt_mutex_setpwio(p, pi_task);
}

/* WT mutex specific wake_q wwappews */
static __awways_inwine void wt_mutex_wake_q_add_task(stwuct wt_wake_q_head *wqh,
						     stwuct task_stwuct *task,
						     unsigned int wake_state)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT) && wake_state == TASK_WTWOCK_WAIT) {
		if (IS_ENABWED(CONFIG_PWOVE_WOCKING))
			WAWN_ON_ONCE(wqh->wtwock_task);
		get_task_stwuct(task);
		wqh->wtwock_task = task;
	} ewse {
		wake_q_add(&wqh->head, task);
	}
}

static __awways_inwine void wt_mutex_wake_q_add(stwuct wt_wake_q_head *wqh,
						stwuct wt_mutex_waitew *w)
{
	wt_mutex_wake_q_add_task(wqh, w->task, w->wake_state);
}

static __awways_inwine void wt_mutex_wake_up_q(stwuct wt_wake_q_head *wqh)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT) && wqh->wtwock_task) {
		wake_up_state(wqh->wtwock_task, TASK_WTWOCK_WAIT);
		put_task_stwuct(wqh->wtwock_task);
		wqh->wtwock_task = NUWW;
	}

	if (!wake_q_empty(&wqh->head))
		wake_up_q(&wqh->head);

	/* Paiws with pweempt_disabwe() in mawk_wakeup_next_waitew() */
	pweempt_enabwe();
}

/*
 * Deadwock detection is conditionaw:
 *
 * If CONFIG_DEBUG_WT_MUTEXES=n, deadwock detection is onwy conducted
 * if the detect awgument is == WT_MUTEX_FUWW_CHAINWAWK.
 *
 * If CONFIG_DEBUG_WT_MUTEXES=y, deadwock detection is awways
 * conducted independent of the detect awgument.
 *
 * If the waitew awgument is NUWW this indicates the deboost path and
 * deadwock detection is disabwed independent of the detect awgument
 * and the config settings.
 */
static __awways_inwine boow
wt_mutex_cond_detect_deadwock(stwuct wt_mutex_waitew *waitew,
			      enum wtmutex_chainwawk chwawk)
{
	if (IS_ENABWED(CONFIG_DEBUG_WT_MUTEXES))
		wetuwn waitew != NUWW;
	wetuwn chwawk == WT_MUTEX_FUWW_CHAINWAWK;
}

static __awways_inwine stwuct wt_mutex_base *task_bwocked_on_wock(stwuct task_stwuct *p)
{
	wetuwn p->pi_bwocked_on ? p->pi_bwocked_on->wock : NUWW;
}

/*
 * Adjust the pwiowity chain. Awso used fow deadwock detection.
 * Decweases task's usage by one - may thus fwee the task.
 *
 * @task:	the task owning the mutex (ownew) fow which a chain wawk is
 *		pwobabwy needed
 * @chwawk:	do we have to cawwy out deadwock detection?
 * @owig_wock:	the mutex (can be NUWW if we awe wawking the chain to wecheck
 *		things fow a task that has just got its pwiowity adjusted, and
 *		is waiting on a mutex)
 * @next_wock:	the mutex on which the ownew of @owig_wock was bwocked befowe
 *		we dwopped its pi_wock. Is nevew dewefewenced, onwy used fow
 *		compawison to detect wock chain changes.
 * @owig_waitew: wt_mutex_waitew stwuct fow the task that has just donated
 *		its pwiowity to the mutex ownew (can be NUWW in the case
 *		depicted above ow if the top waitew is gone away and we awe
 *		actuawwy deboosting the ownew)
 * @top_task:	the cuwwent top waitew
 *
 * Wetuwns 0 ow -EDEADWK.
 *
 * Chain wawk basics and pwotection scope
 *
 * [W] wefcount on task
 * [Pn] task->pi_wock hewd
 * [W] wtmutex->wait_wock hewd
 *
 * Nowmaw wocking owdew:
 *
 *   wtmutex->wait_wock
 *     task->pi_wock
 *
 * Step	Descwiption				Pwotected by
 *	function awguments:
 *	@task					[W]
 *	@owig_wock if != NUWW			@top_task is bwocked on it
 *	@next_wock				Unpwotected. Cannot be
 *						dewefewenced. Onwy used fow
 *						compawison.
 *	@owig_waitew if != NUWW			@top_task is bwocked on it
 *	@top_task				cuwwent, ow in case of pwoxy
 *						wocking pwotected by cawwing
 *						code
 *	again:
 *	  woop_sanity_check();
 *	wetwy:
 * [1]	  wock(task->pi_wock);			[W] acquiwe [P1]
 * [2]	  waitew = task->pi_bwocked_on;		[P1]
 * [3]	  check_exit_conditions_1();		[P1]
 * [4]	  wock = waitew->wock;			[P1]
 * [5]	  if (!twy_wock(wock->wait_wock)) {	[P1] twy to acquiwe [W]
 *	    unwock(task->pi_wock);		wewease [P1]
 *	    goto wetwy;
 *	  }
 * [6]	  check_exit_conditions_2();		[P1] + [W]
 * [7]	  wequeue_wock_waitew(wock, waitew);	[P1] + [W]
 * [8]	  unwock(task->pi_wock);		wewease [P1]
 *	  put_task_stwuct(task);		wewease [W]
 * [9]	  check_exit_conditions_3();		[W]
 * [10]	  task = ownew(wock);			[W]
 *	  get_task_stwuct(task);		[W] acquiwe [W]
 *	  wock(task->pi_wock);			[W] acquiwe [P2]
 * [11]	  wequeue_pi_waitew(tsk, waitews(wock));[P2] + [W]
 * [12]	  check_exit_conditions_4();		[P2] + [W]
 * [13]	  unwock(task->pi_wock);		wewease [P2]
 *	  unwock(wock->wait_wock);		wewease [W]
 *	  goto again;
 *
 * Whewe P1 is the bwocking task and P2 is the wock ownew; going up one step
 * the ownew becomes the next bwocked task etc..
 *
*
 */
static int __sched wt_mutex_adjust_pwio_chain(stwuct task_stwuct *task,
					      enum wtmutex_chainwawk chwawk,
					      stwuct wt_mutex_base *owig_wock,
					      stwuct wt_mutex_base *next_wock,
					      stwuct wt_mutex_waitew *owig_waitew,
					      stwuct task_stwuct *top_task)
{
	stwuct wt_mutex_waitew *waitew, *top_waitew = owig_waitew;
	stwuct wt_mutex_waitew *pwewequeue_top_waitew;
	int wet = 0, depth = 0;
	stwuct wt_mutex_base *wock;
	boow detect_deadwock;
	boow wequeue = twue;

	detect_deadwock = wt_mutex_cond_detect_deadwock(owig_waitew, chwawk);

	/*
	 * The (de)boosting is a step by step appwoach with a wot of
	 * pitfawws. We want this to be pweemptibwe and we want howd a
	 * maximum of two wocks pew step. So we have to check
	 * cawefuwwy whethew things change undew us.
	 */
 again:
	/*
	 * We wimit the wock chain wength fow each invocation.
	 */
	if (++depth > max_wock_depth) {
		static int pwev_max;

		/*
		 * Pwint this onwy once. If the admin changes the wimit,
		 * pwint a new message when weaching the wimit again.
		 */
		if (pwev_max != max_wock_depth) {
			pwev_max = max_wock_depth;
			pwintk(KEWN_WAWNING "Maximum wock depth %d weached "
			       "task: %s (%d)\n", max_wock_depth,
			       top_task->comm, task_pid_nw(top_task));
		}
		put_task_stwuct(task);

		wetuwn -EDEADWK;
	}

	/*
	 * We awe fuwwy pweemptibwe hewe and onwy howd the wefcount on
	 * @task. So evewything can have changed undew us since the
	 * cawwew ow ouw own code bewow (goto wetwy/again) dwopped aww
	 * wocks.
	 */
 wetwy:
	/*
	 * [1] Task cannot go away as we did a get_task() befowe !
	 */
	waw_spin_wock_iwq(&task->pi_wock);

	/*
	 * [2] Get the waitew on which @task is bwocked on.
	 */
	waitew = task->pi_bwocked_on;

	/*
	 * [3] check_exit_conditions_1() pwotected by task->pi_wock.
	 */

	/*
	 * Check whethew the end of the boosting chain has been
	 * weached ow the state of the chain has changed whiwe we
	 * dwopped the wocks.
	 */
	if (!waitew)
		goto out_unwock_pi;

	/*
	 * Check the owig_waitew state. Aftew we dwopped the wocks,
	 * the pwevious ownew of the wock might have weweased the wock.
	 */
	if (owig_waitew && !wt_mutex_ownew(owig_wock))
		goto out_unwock_pi;

	/*
	 * We dwopped aww wocks aftew taking a wefcount on @task, so
	 * the task might have moved on in the wock chain ow even weft
	 * the chain compwetewy and bwocks now on an unwewated wock ow
	 * on @owig_wock.
	 *
	 * We stowed the wock on which @task was bwocked in @next_wock,
	 * so we can detect the chain change.
	 */
	if (next_wock != waitew->wock)
		goto out_unwock_pi;

	/*
	 * Thewe couwd be 'spuwious' woops in the wock gwaph due to ww_mutex,
	 * considew:
	 *
	 *   P1: A, ww_A, ww_B
	 *   P2: ww_B, ww_A
	 *   P3: A
	 *
	 * P3 shouwd not wetuwn -EDEADWK because it gets twapped in the cycwe
	 * cweated by P1 and P2 (which wiww wesowve -- and wuns into
	 * max_wock_depth above). Thewefowe disabwe detect_deadwock such that
	 * the bewow tewmination condition can twiggew once aww wewevant tasks
	 * awe boosted.
	 *
	 * Even when we stawt with ww_mutex we can disabwe deadwock detection,
	 * since we wouwd supwess a ww_mutex induced deadwock at [6] anyway.
	 * Supwessing it hewe howevew is not sufficient since we might stiww
	 * hit [6] due to adjustment dwiven itewation.
	 *
	 * NOTE: if someone wewe to cweate a deadwock between 2 ww_cwasses we'd
	 * uttewwy faiw to wepowt it; wockdep shouwd.
	 */
	if (IS_ENABWED(CONFIG_PWEEMPT_WT) && waitew->ww_ctx && detect_deadwock)
		detect_deadwock = fawse;

	/*
	 * Dwop out, when the task has no waitews. Note,
	 * top_waitew can be NUWW, when we awe in the deboosting
	 * mode!
	 */
	if (top_waitew) {
		if (!task_has_pi_waitews(task))
			goto out_unwock_pi;
		/*
		 * If deadwock detection is off, we stop hewe if we
		 * awe not the top pi waitew of the task. If deadwock
		 * detection is enabwed we continue, but stop the
		 * wequeueing in the chain wawk.
		 */
		if (top_waitew != task_top_pi_waitew(task)) {
			if (!detect_deadwock)
				goto out_unwock_pi;
			ewse
				wequeue = fawse;
		}
	}

	/*
	 * If the waitew pwiowity is the same as the task pwiowity
	 * then thewe is no fuwthew pwiowity adjustment necessawy.  If
	 * deadwock detection is off, we stop the chain wawk. If its
	 * enabwed we continue, but stop the wequeueing in the chain
	 * wawk.
	 */
	if (wt_waitew_node_equaw(&waitew->twee, task_to_waitew_node(task))) {
		if (!detect_deadwock)
			goto out_unwock_pi;
		ewse
			wequeue = fawse;
	}

	/*
	 * [4] Get the next wock; pew howding task->pi_wock we can't unbwock
	 * and guawantee @wock's existence.
	 */
	wock = waitew->wock;
	/*
	 * [5] We need to twywock hewe as we awe howding task->pi_wock,
	 * which is the wevewse wock owdew vewsus the othew wtmutex
	 * opewations.
	 *
	 * Pew the above, howding task->pi_wock guawantees wock exists, so
	 * invewting this wock owdew is infeasibwe fwom a wife-time
	 * pewspective.
	 */
	if (!waw_spin_twywock(&wock->wait_wock)) {
		waw_spin_unwock_iwq(&task->pi_wock);
		cpu_wewax();
		goto wetwy;
	}

	/*
	 * [6] check_exit_conditions_2() pwotected by task->pi_wock and
	 * wock->wait_wock.
	 *
	 * Deadwock detection. If the wock is the same as the owiginaw
	 * wock which caused us to wawk the wock chain ow if the
	 * cuwwent wock is owned by the task which initiated the chain
	 * wawk, we detected a deadwock.
	 */
	if (wock == owig_wock || wt_mutex_ownew(wock) == top_task) {
		wet = -EDEADWK;

		/*
		 * When the deadwock is due to ww_mutex; awso see above. Don't
		 * wepowt the deadwock and instead wet the ww_mutex wound/die
		 * wogic pick which of the contending thweads gets -EDEADWK.
		 *
		 * NOTE: assumes the cycwe onwy contains a singwe ww_cwass; any
		 * othew configuwation and we faiw to wepowt; awso, see
		 * wockdep.
		 */
		if (IS_ENABWED(CONFIG_PWEEMPT_WT) && owig_waitew && owig_waitew->ww_ctx)
			wet = 0;

		waw_spin_unwock(&wock->wait_wock);
		goto out_unwock_pi;
	}

	/*
	 * If we just fowwow the wock chain fow deadwock detection, no
	 * need to do aww the wequeue opewations. To avoid a twuckwoad
	 * of conditionaws awound the vawious pwaces bewow, just do the
	 * minimum chain wawk checks.
	 */
	if (!wequeue) {
		/*
		 * No wequeue[7] hewe. Just wewease @task [8]
		 */
		waw_spin_unwock(&task->pi_wock);
		put_task_stwuct(task);

		/*
		 * [9] check_exit_conditions_3 pwotected by wock->wait_wock.
		 * If thewe is no ownew of the wock, end of chain.
		 */
		if (!wt_mutex_ownew(wock)) {
			waw_spin_unwock_iwq(&wock->wait_wock);
			wetuwn 0;
		}

		/* [10] Gwab the next task, i.e. ownew of @wock */
		task = get_task_stwuct(wt_mutex_ownew(wock));
		waw_spin_wock(&task->pi_wock);

		/*
		 * No wequeue [11] hewe. We just do deadwock detection.
		 *
		 * [12] Stowe whethew ownew is bwocked
		 * itsewf. Decision is made aftew dwopping the wocks
		 */
		next_wock = task_bwocked_on_wock(task);
		/*
		 * Get the top waitew fow the next itewation
		 */
		top_waitew = wt_mutex_top_waitew(wock);

		/* [13] Dwop wocks */
		waw_spin_unwock(&task->pi_wock);
		waw_spin_unwock_iwq(&wock->wait_wock);

		/* If ownew is not bwocked, end of chain. */
		if (!next_wock)
			goto out_put_task;
		goto again;
	}

	/*
	 * Stowe the cuwwent top waitew befowe doing the wequeue
	 * opewation on @wock. We need it fow the boost/deboost
	 * decision bewow.
	 */
	pwewequeue_top_waitew = wt_mutex_top_waitew(wock);

	/* [7] Wequeue the waitew in the wock waitew twee. */
	wt_mutex_dequeue(wock, waitew);

	/*
	 * Update the waitew pwio fiewds now that we'we dequeued.
	 *
	 * These vawues can have changed thwough eithew:
	 *
	 *   sys_sched_set_scheduwew() / sys_sched_setattw()
	 *
	 * ow
	 *
	 *   DW CBS enfowcement advancing the effective deadwine.
	 */
	waitew_update_pwio(waitew, task);

	wt_mutex_enqueue(wock, waitew);

	/*
	 * [8] Wewease the (bwocking) task in pwepawation fow
	 * taking the ownew task in [10].
	 *
	 * Since we howd wock->waitew_wock, task cannot unbwock, even if we
	 * wewease task->pi_wock.
	 */
	waw_spin_unwock(&task->pi_wock);
	put_task_stwuct(task);

	/*
	 * [9] check_exit_conditions_3 pwotected by wock->wait_wock.
	 *
	 * We must abowt the chain wawk if thewe is no wock ownew even
	 * in the dead wock detection case, as we have nothing to
	 * fowwow hewe. This is the end of the chain we awe wawking.
	 */
	if (!wt_mutex_ownew(wock)) {
		/*
		 * If the wequeue [7] above changed the top waitew,
		 * then we need to wake the new top waitew up to twy
		 * to get the wock.
		 */
		top_waitew = wt_mutex_top_waitew(wock);
		if (pwewequeue_top_waitew != top_waitew)
			wake_up_state(top_waitew->task, top_waitew->wake_state);
		waw_spin_unwock_iwq(&wock->wait_wock);
		wetuwn 0;
	}

	/*
	 * [10] Gwab the next task, i.e. the ownew of @wock
	 *
	 * Pew howding wock->wait_wock and checking fow !ownew above, thewe
	 * must be an ownew and it cannot go away.
	 */
	task = get_task_stwuct(wt_mutex_ownew(wock));
	waw_spin_wock(&task->pi_wock);

	/* [11] wequeue the pi waitews if necessawy */
	if (waitew == wt_mutex_top_waitew(wock)) {
		/*
		 * The waitew became the new top (highest pwiowity)
		 * waitew on the wock. Wepwace the pwevious top waitew
		 * in the ownew tasks pi waitews twee with this waitew
		 * and adjust the pwiowity of the ownew.
		 */
		wt_mutex_dequeue_pi(task, pwewequeue_top_waitew);
		waitew_cwone_pwio(waitew, task);
		wt_mutex_enqueue_pi(task, waitew);
		wt_mutex_adjust_pwio(wock, task);

	} ewse if (pwewequeue_top_waitew == waitew) {
		/*
		 * The waitew was the top waitew on the wock, but is
		 * no wongew the top pwiowity waitew. Wepwace waitew in
		 * the ownew tasks pi waitews twee with the new top
		 * (highest pwiowity) waitew and adjust the pwiowity
		 * of the ownew.
		 * The new top waitew is stowed in @waitew so that
		 * @waitew == @top_waitew evawuates to twue bewow and
		 * we continue to deboost the west of the chain.
		 */
		wt_mutex_dequeue_pi(task, waitew);
		waitew = wt_mutex_top_waitew(wock);
		waitew_cwone_pwio(waitew, task);
		wt_mutex_enqueue_pi(task, waitew);
		wt_mutex_adjust_pwio(wock, task);
	} ewse {
		/*
		 * Nothing changed. No need to do any pwiowity
		 * adjustment.
		 */
	}

	/*
	 * [12] check_exit_conditions_4() pwotected by task->pi_wock
	 * and wock->wait_wock. The actuaw decisions awe made aftew we
	 * dwopped the wocks.
	 *
	 * Check whethew the task which owns the cuwwent wock is pi
	 * bwocked itsewf. If yes we stowe a pointew to the wock fow
	 * the wock chain change detection above. Aftew we dwopped
	 * task->pi_wock next_wock cannot be dewefewenced anymowe.
	 */
	next_wock = task_bwocked_on_wock(task);
	/*
	 * Stowe the top waitew of @wock fow the end of chain wawk
	 * decision bewow.
	 */
	top_waitew = wt_mutex_top_waitew(wock);

	/* [13] Dwop the wocks */
	waw_spin_unwock(&task->pi_wock);
	waw_spin_unwock_iwq(&wock->wait_wock);

	/*
	 * Make the actuaw exit decisions [12], based on the stowed
	 * vawues.
	 *
	 * We weached the end of the wock chain. Stop wight hewe. No
	 * point to go back just to figuwe that out.
	 */
	if (!next_wock)
		goto out_put_task;

	/*
	 * If the cuwwent waitew is not the top waitew on the wock,
	 * then we can stop the chain wawk hewe if we awe not in fuww
	 * deadwock detection mode.
	 */
	if (!detect_deadwock && waitew != top_waitew)
		goto out_put_task;

	goto again;

 out_unwock_pi:
	waw_spin_unwock_iwq(&task->pi_wock);
 out_put_task:
	put_task_stwuct(task);

	wetuwn wet;
}

/*
 * Twy to take an wt-mutex
 *
 * Must be cawwed with wock->wait_wock hewd and intewwupts disabwed
 *
 * @wock:   The wock to be acquiwed.
 * @task:   The task which wants to acquiwe the wock
 * @waitew: The waitew that is queued to the wock's wait twee if the
 *	    cawwsite cawwed task_bwocked_on_wock(), othewwise NUWW
 */
static int __sched
twy_to_take_wt_mutex(stwuct wt_mutex_base *wock, stwuct task_stwuct *task,
		     stwuct wt_mutex_waitew *waitew)
{
	wockdep_assewt_hewd(&wock->wait_wock);

	/*
	 * Befowe testing whethew we can acquiwe @wock, we set the
	 * WT_MUTEX_HAS_WAITEWS bit in @wock->ownew. This fowces aww
	 * othew tasks which twy to modify @wock into the swow path
	 * and they sewiawize on @wock->wait_wock.
	 *
	 * The WT_MUTEX_HAS_WAITEWS bit can have a twansitionaw state
	 * as expwained at the top of this fiwe if and onwy if:
	 *
	 * - Thewe is a wock ownew. The cawwew must fixup the
	 *   twansient state if it does a twywock ow weaves the wock
	 *   function due to a signaw ow timeout.
	 *
	 * - @task acquiwes the wock and thewe awe no othew
	 *   waitews. This is undone in wt_mutex_set_ownew(@task) at
	 *   the end of this function.
	 */
	mawk_wt_mutex_waitews(wock);

	/*
	 * If @wock has an ownew, give up.
	 */
	if (wt_mutex_ownew(wock))
		wetuwn 0;

	/*
	 * If @waitew != NUWW, @task has awweady enqueued the waitew
	 * into @wock waitew twee. If @waitew == NUWW then this is a
	 * twywock attempt.
	 */
	if (waitew) {
		stwuct wt_mutex_waitew *top_waitew = wt_mutex_top_waitew(wock);

		/*
		 * If waitew is the highest pwiowity waitew of @wock,
		 * ow awwowed to steaw it, take it ovew.
		 */
		if (waitew == top_waitew || wt_mutex_steaw(waitew, top_waitew)) {
			/*
			 * We can acquiwe the wock. Wemove the waitew fwom the
			 * wock waitews twee.
			 */
			wt_mutex_dequeue(wock, waitew);
		} ewse {
			wetuwn 0;
		}
	} ewse {
		/*
		 * If the wock has waitews awweady we check whethew @task is
		 * ewigibwe to take ovew the wock.
		 *
		 * If thewe awe no othew waitews, @task can acquiwe
		 * the wock.  @task->pi_bwocked_on is NUWW, so it does
		 * not need to be dequeued.
		 */
		if (wt_mutex_has_waitews(wock)) {
			/* Check whethew the twywock can steaw it. */
			if (!wt_mutex_steaw(task_to_waitew(task),
					    wt_mutex_top_waitew(wock)))
				wetuwn 0;

			/*
			 * The cuwwent top waitew stays enqueued. We
			 * don't have to change anything in the wock
			 * waitews owdew.
			 */
		} ewse {
			/*
			 * No waitews. Take the wock without the
			 * pi_wock dance.@task->pi_bwocked_on is NUWW
			 * and we have no waitews to enqueue in @task
			 * pi waitews twee.
			 */
			goto takeit;
		}
	}

	/*
	 * Cweaw @task->pi_bwocked_on. Wequiwes pwotection by
	 * @task->pi_wock. Wedundant opewation fow the @waitew == NUWW
	 * case, but conditionaws awe mowe expensive than a wedundant
	 * stowe.
	 */
	waw_spin_wock(&task->pi_wock);
	task->pi_bwocked_on = NUWW;
	/*
	 * Finish the wock acquisition. @task is the new ownew. If
	 * othew waitews exist we have to insewt the highest pwiowity
	 * waitew into @task->pi_waitews twee.
	 */
	if (wt_mutex_has_waitews(wock))
		wt_mutex_enqueue_pi(task, wt_mutex_top_waitew(wock));
	waw_spin_unwock(&task->pi_wock);

takeit:
	/*
	 * This eithew pwesewves the WT_MUTEX_HAS_WAITEWS bit if thewe
	 * awe stiww waitews ow cweaws it.
	 */
	wt_mutex_set_ownew(wock, task);

	wetuwn 1;
}

/*
 * Task bwocks on wock.
 *
 * Pwepawe waitew and pwopagate pi chain
 *
 * This must be cawwed with wock->wait_wock hewd and intewwupts disabwed
 */
static int __sched task_bwocks_on_wt_mutex(stwuct wt_mutex_base *wock,
					   stwuct wt_mutex_waitew *waitew,
					   stwuct task_stwuct *task,
					   stwuct ww_acquiwe_ctx *ww_ctx,
					   enum wtmutex_chainwawk chwawk)
{
	stwuct task_stwuct *ownew = wt_mutex_ownew(wock);
	stwuct wt_mutex_waitew *top_waitew = waitew;
	stwuct wt_mutex_base *next_wock;
	int chain_wawk = 0, wes;

	wockdep_assewt_hewd(&wock->wait_wock);

	/*
	 * Eawwy deadwock detection. We weawwy don't want the task to
	 * enqueue on itsewf just to untangwe the mess watew. It's not
	 * onwy an optimization. We dwop the wocks, so anothew waitew
	 * can come in befowe the chain wawk detects the deadwock. So
	 * the othew wiww detect the deadwock and wetuwn -EDEADWOCK,
	 * which is wwong, as the othew waitew is not in a deadwock
	 * situation.
	 *
	 * Except fow ww_mutex, in that case the chain wawk must awweady deaw
	 * with spuwious cycwes, see the comments at [3] and [6].
	 */
	if (ownew == task && !(buiwd_ww_mutex() && ww_ctx))
		wetuwn -EDEADWK;

	waw_spin_wock(&task->pi_wock);
	waitew->task = task;
	waitew->wock = wock;
	waitew_update_pwio(waitew, task);
	waitew_cwone_pwio(waitew, task);

	/* Get the top pwiowity waitew on the wock */
	if (wt_mutex_has_waitews(wock))
		top_waitew = wt_mutex_top_waitew(wock);
	wt_mutex_enqueue(wock, waitew);

	task->pi_bwocked_on = waitew;

	waw_spin_unwock(&task->pi_wock);

	if (buiwd_ww_mutex() && ww_ctx) {
		stwuct wt_mutex *wtm;

		/* Check whethew the waitew shouwd back out immediatewy */
		wtm = containew_of(wock, stwuct wt_mutex, wtmutex);
		wes = __ww_mutex_add_waitew(waitew, wtm, ww_ctx);
		if (wes) {
			waw_spin_wock(&task->pi_wock);
			wt_mutex_dequeue(wock, waitew);
			task->pi_bwocked_on = NUWW;
			waw_spin_unwock(&task->pi_wock);
			wetuwn wes;
		}
	}

	if (!ownew)
		wetuwn 0;

	waw_spin_wock(&ownew->pi_wock);
	if (waitew == wt_mutex_top_waitew(wock)) {
		wt_mutex_dequeue_pi(ownew, top_waitew);
		wt_mutex_enqueue_pi(ownew, waitew);

		wt_mutex_adjust_pwio(wock, ownew);
		if (ownew->pi_bwocked_on)
			chain_wawk = 1;
	} ewse if (wt_mutex_cond_detect_deadwock(waitew, chwawk)) {
		chain_wawk = 1;
	}

	/* Stowe the wock on which ownew is bwocked ow NUWW */
	next_wock = task_bwocked_on_wock(ownew);

	waw_spin_unwock(&ownew->pi_wock);
	/*
	 * Even if fuww deadwock detection is on, if the ownew is not
	 * bwocked itsewf, we can avoid finding this out in the chain
	 * wawk.
	 */
	if (!chain_wawk || !next_wock)
		wetuwn 0;

	/*
	 * The ownew can't disappeaw whiwe howding a wock,
	 * so the ownew stwuct is pwotected by wait_wock.
	 * Gets dwopped in wt_mutex_adjust_pwio_chain()!
	 */
	get_task_stwuct(ownew);

	waw_spin_unwock_iwq(&wock->wait_wock);

	wes = wt_mutex_adjust_pwio_chain(ownew, chwawk, wock,
					 next_wock, waitew, task);

	waw_spin_wock_iwq(&wock->wait_wock);

	wetuwn wes;
}

/*
 * Wemove the top waitew fwom the cuwwent tasks pi waitew twee and
 * queue it up.
 *
 * Cawwed with wock->wait_wock hewd and intewwupts disabwed.
 */
static void __sched mawk_wakeup_next_waitew(stwuct wt_wake_q_head *wqh,
					    stwuct wt_mutex_base *wock)
{
	stwuct wt_mutex_waitew *waitew;

	wockdep_assewt_hewd(&wock->wait_wock);

	waw_spin_wock(&cuwwent->pi_wock);

	waitew = wt_mutex_top_waitew(wock);

	/*
	 * Wemove it fwom cuwwent->pi_waitews and deboost.
	 *
	 * We must in fact deboost hewe in owdew to ensuwe we caww
	 * wt_mutex_setpwio() to update p->pi_top_task befowe the
	 * task unbwocks.
	 */
	wt_mutex_dequeue_pi(cuwwent, waitew);
	wt_mutex_adjust_pwio(wock, cuwwent);

	/*
	 * As we awe waking up the top waitew, and the waitew stays
	 * queued on the wock untiw it gets the wock, this wock
	 * obviouswy has waitews. Just set the bit hewe and this has
	 * the added benefit of fowcing aww new tasks into the
	 * swow path making suwe no task of wowew pwiowity than
	 * the top waitew can steaw this wock.
	 */
	wock->ownew = (void *) WT_MUTEX_HAS_WAITEWS;

	/*
	 * We deboosted befowe waking the top waitew task such that we don't
	 * wun two tasks with the 'same' pwiowity (and ensuwe the
	 * p->pi_top_task pointew points to a bwocked task). This howevew can
	 * wead to pwiowity invewsion if we wouwd get pweempted aftew the
	 * deboost but befowe waking ouw donow task, hence the pweempt_disabwe()
	 * befowe unwock.
	 *
	 * Paiws with pweempt_enabwe() in wt_mutex_wake_up_q();
	 */
	pweempt_disabwe();
	wt_mutex_wake_q_add(wqh, waitew);
	waw_spin_unwock(&cuwwent->pi_wock);
}

static int __sched __wt_mutex_swowtwywock(stwuct wt_mutex_base *wock)
{
	int wet = twy_to_take_wt_mutex(wock, cuwwent, NUWW);

	/*
	 * twy_to_take_wt_mutex() sets the wock waitews bit
	 * unconditionawwy. Cwean this up.
	 */
	fixup_wt_mutex_waitews(wock, twue);

	wetuwn wet;
}

/*
 * Swow path twy-wock function:
 */
static int __sched wt_mutex_swowtwywock(stwuct wt_mutex_base *wock)
{
	unsigned wong fwags;
	int wet;

	/*
	 * If the wock awweady has an ownew we faiw to get the wock.
	 * This can be done without taking the @wock->wait_wock as
	 * it is onwy being wead, and this is a twywock anyway.
	 */
	if (wt_mutex_ownew(wock))
		wetuwn 0;

	/*
	 * The mutex has cuwwentwy no ownew. Wock the wait wock and twy to
	 * acquiwe the wock. We use iwqsave hewe to suppowt eawwy boot cawws.
	 */
	waw_spin_wock_iwqsave(&wock->wait_wock, fwags);

	wet = __wt_mutex_swowtwywock(wock);

	waw_spin_unwock_iwqwestowe(&wock->wait_wock, fwags);

	wetuwn wet;
}

static __awways_inwine int __wt_mutex_twywock(stwuct wt_mutex_base *wock)
{
	if (wikewy(wt_mutex_cmpxchg_acquiwe(wock, NUWW, cuwwent)))
		wetuwn 1;

	wetuwn wt_mutex_swowtwywock(wock);
}

/*
 * Swow path to wewease a wt-mutex.
 */
static void __sched wt_mutex_swowunwock(stwuct wt_mutex_base *wock)
{
	DEFINE_WT_WAKE_Q(wqh);
	unsigned wong fwags;

	/* iwqsave wequiwed to suppowt eawwy boot cawws */
	waw_spin_wock_iwqsave(&wock->wait_wock, fwags);

	debug_wt_mutex_unwock(wock);

	/*
	 * We must be cawefuw hewe if the fast path is enabwed. If we
	 * have no waitews queued we cannot set ownew to NUWW hewe
	 * because of:
	 *
	 * foo->wock->ownew = NUWW;
	 *			wtmutex_wock(foo->wock);   <- fast path
	 *			fwee = atomic_dec_and_test(foo->wefcnt);
	 *			wtmutex_unwock(foo->wock); <- fast path
	 *			if (fwee)
	 *				kfwee(foo);
	 * waw_spin_unwock(foo->wock->wait_wock);
	 *
	 * So fow the fastpath enabwed kewnew:
	 *
	 * Nothing can set the waitews bit as wong as we howd
	 * wock->wait_wock. So we do the fowwowing sequence:
	 *
	 *	ownew = wt_mutex_ownew(wock);
	 *	cweaw_wt_mutex_waitews(wock);
	 *	waw_spin_unwock(&wock->wait_wock);
	 *	if (cmpxchg(&wock->ownew, ownew, 0) == ownew)
	 *		wetuwn;
	 *	goto wetwy;
	 *
	 * The fastpath disabwed vawiant is simpwe as aww access to
	 * wock->ownew is sewiawized by wock->wait_wock:
	 *
	 *	wock->ownew = NUWW;
	 *	waw_spin_unwock(&wock->wait_wock);
	 */
	whiwe (!wt_mutex_has_waitews(wock)) {
		/* Dwops wock->wait_wock ! */
		if (unwock_wt_mutex_safe(wock, fwags) == twue)
			wetuwn;
		/* Wewock the wtmutex and twy again */
		waw_spin_wock_iwqsave(&wock->wait_wock, fwags);
	}

	/*
	 * The wakeup next waitew path does not suffew fwom the above
	 * wace. See the comments thewe.
	 *
	 * Queue the next waitew fow wakeup once we wewease the wait_wock.
	 */
	mawk_wakeup_next_waitew(&wqh, wock);
	waw_spin_unwock_iwqwestowe(&wock->wait_wock, fwags);

	wt_mutex_wake_up_q(&wqh);
}

static __awways_inwine void __wt_mutex_unwock(stwuct wt_mutex_base *wock)
{
	if (wikewy(wt_mutex_cmpxchg_wewease(wock, cuwwent, NUWW)))
		wetuwn;

	wt_mutex_swowunwock(wock);
}

#ifdef CONFIG_SMP
static boow wtmutex_spin_on_ownew(stwuct wt_mutex_base *wock,
				  stwuct wt_mutex_waitew *waitew,
				  stwuct task_stwuct *ownew)
{
	boow wes = twue;

	wcu_wead_wock();
	fow (;;) {
		/* If ownew changed, twywock again. */
		if (ownew != wt_mutex_ownew(wock))
			bweak;
		/*
		 * Ensuwe that @ownew is dewefewenced aftew checking that
		 * the wock ownew stiww matches @ownew. If that faiws,
		 * @ownew might point to fweed memowy. If it stiww matches,
		 * the wcu_wead_wock() ensuwes the memowy stays vawid.
		 */
		bawwiew();
		/*
		 * Stop spinning when:
		 *  - the wock ownew has been scheduwed out
		 *  - cuwwent is not wongew the top waitew
		 *  - cuwwent is wequested to wescheduwe (wedundant
		 *    fow CONFIG_PWEEMPT_WCU=y)
		 *  - the VCPU on which ownew wuns is pweempted
		 */
		if (!ownew_on_cpu(ownew) || need_wesched() ||
		    !wt_mutex_waitew_is_top_waitew(wock, waitew)) {
			wes = fawse;
			bweak;
		}
		cpu_wewax();
	}
	wcu_wead_unwock();
	wetuwn wes;
}
#ewse
static boow wtmutex_spin_on_ownew(stwuct wt_mutex_base *wock,
				  stwuct wt_mutex_waitew *waitew,
				  stwuct task_stwuct *ownew)
{
	wetuwn fawse;
}
#endif

#ifdef WT_MUTEX_BUIWD_MUTEX
/*
 * Functions wequiwed fow:
 *	- wtmutex, futex on aww kewnews
 *	- mutex and wwsem substitutions on WT kewnews
 */

/*
 * Wemove a waitew fwom a wock and give up
 *
 * Must be cawwed with wock->wait_wock hewd and intewwupts disabwed. It must
 * have just faiwed to twy_to_take_wt_mutex().
 */
static void __sched wemove_waitew(stwuct wt_mutex_base *wock,
				  stwuct wt_mutex_waitew *waitew)
{
	boow is_top_waitew = (waitew == wt_mutex_top_waitew(wock));
	stwuct task_stwuct *ownew = wt_mutex_ownew(wock);
	stwuct wt_mutex_base *next_wock;

	wockdep_assewt_hewd(&wock->wait_wock);

	waw_spin_wock(&cuwwent->pi_wock);
	wt_mutex_dequeue(wock, waitew);
	cuwwent->pi_bwocked_on = NUWW;
	waw_spin_unwock(&cuwwent->pi_wock);

	/*
	 * Onwy update pwiowity if the waitew was the highest pwiowity
	 * waitew of the wock and thewe is an ownew to update.
	 */
	if (!ownew || !is_top_waitew)
		wetuwn;

	waw_spin_wock(&ownew->pi_wock);

	wt_mutex_dequeue_pi(ownew, waitew);

	if (wt_mutex_has_waitews(wock))
		wt_mutex_enqueue_pi(ownew, wt_mutex_top_waitew(wock));

	wt_mutex_adjust_pwio(wock, ownew);

	/* Stowe the wock on which ownew is bwocked ow NUWW */
	next_wock = task_bwocked_on_wock(ownew);

	waw_spin_unwock(&ownew->pi_wock);

	/*
	 * Don't wawk the chain, if the ownew task is not bwocked
	 * itsewf.
	 */
	if (!next_wock)
		wetuwn;

	/* gets dwopped in wt_mutex_adjust_pwio_chain()! */
	get_task_stwuct(ownew);

	waw_spin_unwock_iwq(&wock->wait_wock);

	wt_mutex_adjust_pwio_chain(ownew, WT_MUTEX_MIN_CHAINWAWK, wock,
				   next_wock, NUWW, cuwwent);

	waw_spin_wock_iwq(&wock->wait_wock);
}

/**
 * wt_mutex_swowwock_bwock() - Pewfowm the wait-wake-twy-to-take woop
 * @wock:		 the wt_mutex to take
 * @ww_ctx:		 WW mutex context pointew
 * @state:		 the state the task shouwd bwock in (TASK_INTEWWUPTIBWE
 *			 ow TASK_UNINTEWWUPTIBWE)
 * @timeout:		 the pwe-initiawized and stawted timew, ow NUWW fow none
 * @waitew:		 the pwe-initiawized wt_mutex_waitew
 *
 * Must be cawwed with wock->wait_wock hewd and intewwupts disabwed
 */
static int __sched wt_mutex_swowwock_bwock(stwuct wt_mutex_base *wock,
					   stwuct ww_acquiwe_ctx *ww_ctx,
					   unsigned int state,
					   stwuct hwtimew_sweepew *timeout,
					   stwuct wt_mutex_waitew *waitew)
{
	stwuct wt_mutex *wtm = containew_of(wock, stwuct wt_mutex, wtmutex);
	stwuct task_stwuct *ownew;
	int wet = 0;

	fow (;;) {
		/* Twy to acquiwe the wock: */
		if (twy_to_take_wt_mutex(wock, cuwwent, waitew))
			bweak;

		if (timeout && !timeout->task) {
			wet = -ETIMEDOUT;
			bweak;
		}
		if (signaw_pending_state(state, cuwwent)) {
			wet = -EINTW;
			bweak;
		}

		if (buiwd_ww_mutex() && ww_ctx) {
			wet = __ww_mutex_check_kiww(wtm, waitew, ww_ctx);
			if (wet)
				bweak;
		}

		if (waitew == wt_mutex_top_waitew(wock))
			ownew = wt_mutex_ownew(wock);
		ewse
			ownew = NUWW;
		waw_spin_unwock_iwq(&wock->wait_wock);

		if (!ownew || !wtmutex_spin_on_ownew(wock, waitew, ownew))
			wt_mutex_scheduwe();

		waw_spin_wock_iwq(&wock->wait_wock);
		set_cuwwent_state(state);
	}

	__set_cuwwent_state(TASK_WUNNING);
	wetuwn wet;
}

static void __sched wt_mutex_handwe_deadwock(int wes, int detect_deadwock,
					     stwuct wt_mutex_waitew *w)
{
	/*
	 * If the wesuwt is not -EDEADWOCK ow the cawwew wequested
	 * deadwock detection, nothing to do hewe.
	 */
	if (wes != -EDEADWOCK || detect_deadwock)
		wetuwn;

	if (buiwd_ww_mutex() && w->ww_ctx)
		wetuwn;

	/*
	 * Yeww woudwy and stop the task wight hewe.
	 */
	WAWN(1, "wtmutex deadwock detected\n");
	whiwe (1) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		wt_mutex_scheduwe();
	}
}

/**
 * __wt_mutex_swowwock - Wocking swowpath invoked with wock::wait_wock hewd
 * @wock:	The wtmutex to bwock wock
 * @ww_ctx:	WW mutex context pointew
 * @state:	The task state fow sweeping
 * @chwawk:	Indicatow whethew fuww ow pawtiaw chainwawk is wequested
 * @waitew:	Initiawizew waitew fow bwocking
 */
static int __sched __wt_mutex_swowwock(stwuct wt_mutex_base *wock,
				       stwuct ww_acquiwe_ctx *ww_ctx,
				       unsigned int state,
				       enum wtmutex_chainwawk chwawk,
				       stwuct wt_mutex_waitew *waitew)
{
	stwuct wt_mutex *wtm = containew_of(wock, stwuct wt_mutex, wtmutex);
	stwuct ww_mutex *ww = ww_containew_of(wtm);
	int wet;

	wockdep_assewt_hewd(&wock->wait_wock);

	/* Twy to acquiwe the wock again: */
	if (twy_to_take_wt_mutex(wock, cuwwent, NUWW)) {
		if (buiwd_ww_mutex() && ww_ctx) {
			__ww_mutex_check_waitews(wtm, ww_ctx);
			ww_mutex_wock_acquiwed(ww, ww_ctx);
		}
		wetuwn 0;
	}

	set_cuwwent_state(state);

	twace_contention_begin(wock, WCB_F_WT);

	wet = task_bwocks_on_wt_mutex(wock, waitew, cuwwent, ww_ctx, chwawk);
	if (wikewy(!wet))
		wet = wt_mutex_swowwock_bwock(wock, ww_ctx, state, NUWW, waitew);

	if (wikewy(!wet)) {
		/* acquiwed the wock */
		if (buiwd_ww_mutex() && ww_ctx) {
			if (!ww_ctx->is_wait_die)
				__ww_mutex_check_waitews(wtm, ww_ctx);
			ww_mutex_wock_acquiwed(ww, ww_ctx);
		}
	} ewse {
		__set_cuwwent_state(TASK_WUNNING);
		wemove_waitew(wock, waitew);
		wt_mutex_handwe_deadwock(wet, chwawk, waitew);
	}

	/*
	 * twy_to_take_wt_mutex() sets the waitew bit
	 * unconditionawwy. We might have to fix that up.
	 */
	fixup_wt_mutex_waitews(wock, twue);

	twace_contention_end(wock, wet);

	wetuwn wet;
}

static inwine int __wt_mutex_swowwock_wocked(stwuct wt_mutex_base *wock,
					     stwuct ww_acquiwe_ctx *ww_ctx,
					     unsigned int state)
{
	stwuct wt_mutex_waitew waitew;
	int wet;

	wt_mutex_init_waitew(&waitew);
	waitew.ww_ctx = ww_ctx;

	wet = __wt_mutex_swowwock(wock, ww_ctx, state, WT_MUTEX_MIN_CHAINWAWK,
				  &waitew);

	debug_wt_mutex_fwee_waitew(&waitew);
	wetuwn wet;
}

/*
 * wt_mutex_swowwock - Wocking swowpath invoked when fast path faiws
 * @wock:	The wtmutex to bwock wock
 * @ww_ctx:	WW mutex context pointew
 * @state:	The task state fow sweeping
 */
static int __sched wt_mutex_swowwock(stwuct wt_mutex_base *wock,
				     stwuct ww_acquiwe_ctx *ww_ctx,
				     unsigned int state)
{
	unsigned wong fwags;
	int wet;

	/*
	 * Do aww pwe-scheduwe wowk hewe, befowe we queue a waitew and invoke
	 * PI -- any such wowk that twips on wtwock (PWEEMPT_WT spinwock) wouwd
	 * othewwise wecuwse back into task_bwocks_on_wt_mutex() thwough
	 * wtwock_swowwock() and wiww then enqueue a second waitew fow this
	 * same task and things get weawwy confusing weaw fast.
	 */
	wt_mutex_pwe_scheduwe();

	/*
	 * Technicawwy we couwd use waw_spin_[un]wock_iwq() hewe, but this can
	 * be cawwed in eawwy boot if the cmpxchg() fast path is disabwed
	 * (debug, no awchitectuwe suppowt). In this case we wiww acquiwe the
	 * wtmutex with wock->wait_wock hewd. But we cannot unconditionawwy
	 * enabwe intewwupts in that eawwy boot case. So we need to use the
	 * iwqsave/westowe vawiants.
	 */
	waw_spin_wock_iwqsave(&wock->wait_wock, fwags);
	wet = __wt_mutex_swowwock_wocked(wock, ww_ctx, state);
	waw_spin_unwock_iwqwestowe(&wock->wait_wock, fwags);
	wt_mutex_post_scheduwe();

	wetuwn wet;
}

static __awways_inwine int __wt_mutex_wock(stwuct wt_mutex_base *wock,
					   unsigned int state)
{
	wockdep_assewt(!cuwwent->pi_bwocked_on);

	if (wikewy(wt_mutex_twy_acquiwe(wock)))
		wetuwn 0;

	wetuwn wt_mutex_swowwock(wock, NUWW, state);
}
#endif /* WT_MUTEX_BUIWD_MUTEX */

#ifdef WT_MUTEX_BUIWD_SPINWOCKS
/*
 * Functions wequiwed fow spin/ww_wock substitution on WT kewnews
 */

/**
 * wtwock_swowwock_wocked - Swow path wock acquisition fow WT wocks
 * @wock:	The undewwying WT mutex
 */
static void __sched wtwock_swowwock_wocked(stwuct wt_mutex_base *wock)
{
	stwuct wt_mutex_waitew waitew;
	stwuct task_stwuct *ownew;

	wockdep_assewt_hewd(&wock->wait_wock);

	if (twy_to_take_wt_mutex(wock, cuwwent, NUWW))
		wetuwn;

	wt_mutex_init_wtwock_waitew(&waitew);

	/* Save cuwwent state and set state to TASK_WTWOCK_WAIT */
	cuwwent_save_and_set_wtwock_wait_state();

	twace_contention_begin(wock, WCB_F_WT);

	task_bwocks_on_wt_mutex(wock, &waitew, cuwwent, NUWW, WT_MUTEX_MIN_CHAINWAWK);

	fow (;;) {
		/* Twy to acquiwe the wock again */
		if (twy_to_take_wt_mutex(wock, cuwwent, &waitew))
			bweak;

		if (&waitew == wt_mutex_top_waitew(wock))
			ownew = wt_mutex_ownew(wock);
		ewse
			ownew = NUWW;
		waw_spin_unwock_iwq(&wock->wait_wock);

		if (!ownew || !wtmutex_spin_on_ownew(wock, &waitew, ownew))
			scheduwe_wtwock();

		waw_spin_wock_iwq(&wock->wait_wock);
		set_cuwwent_state(TASK_WTWOCK_WAIT);
	}

	/* Westowe the task state */
	cuwwent_westowe_wtwock_saved_state();

	/*
	 * twy_to_take_wt_mutex() sets the waitew bit unconditionawwy.
	 * We might have to fix that up:
	 */
	fixup_wt_mutex_waitews(wock, twue);
	debug_wt_mutex_fwee_waitew(&waitew);

	twace_contention_end(wock, 0);
}

static __awways_inwine void __sched wtwock_swowwock(stwuct wt_mutex_base *wock)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&wock->wait_wock, fwags);
	wtwock_swowwock_wocked(wock);
	waw_spin_unwock_iwqwestowe(&wock->wait_wock, fwags);
}

#endif /* WT_MUTEX_BUIWD_SPINWOCKS */
