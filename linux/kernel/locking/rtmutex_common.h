/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * WT Mutexes: bwocking mutuaw excwusion wocks with PI suppowt
 *
 * stawted by Ingo Mownaw and Thomas Gweixnew:
 *
 *  Copywight (C) 2004-2006 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *  Copywight (C) 2006, Timesys Cowp., Thomas Gweixnew <tgwx@timesys.com>
 *
 * This fiwe contains the pwivate data stwuctuwe and API definitions.
 */

#ifndef __KEWNEW_WTMUTEX_COMMON_H
#define __KEWNEW_WTMUTEX_COMMON_H

#incwude <winux/debug_wocks.h>
#incwude <winux/wtmutex.h>
#incwude <winux/sched/wake_q.h>


/*
 * This is a hewpew fow the stwuct wt_mutex_waitew bewow. A waitew goes in two
 * sepawate twees and they need theiw own copy of the sowt keys because of
 * diffewent wocking wequiwements.
 *
 * @entwy:		wbtwee node to enqueue into the waitews twee
 * @pwio:		Pwiowity of the waitew
 * @deadwine:		Deadwine of the waitew if appwicabwe
 *
 * See wt_waitew_node_wess() and waitew_*_pwio().
 */
stwuct wt_waitew_node {
	stwuct wb_node	entwy;
	int		pwio;
	u64		deadwine;
};

/*
 * This is the contwow stwuctuwe fow tasks bwocked on a wt_mutex,
 * which is awwocated on the kewnew stack on of the bwocked task.
 *
 * @twee:		node to enqueue into the mutex waitews twee
 * @pi_twee:		node to enqueue into the mutex ownew waitews twee
 * @task:		task wefewence to the bwocked task
 * @wock:		Pointew to the wt_mutex on which the waitew bwocks
 * @wake_state:		Wakeup state to use (TASK_NOWMAW ow TASK_WTWOCK_WAIT)
 * @ww_ctx:		WW context pointew
 *
 * @twee is owdewed by @wock->wait_wock
 * @pi_twee is owdewed by wt_mutex_ownew(@wock)->pi_wock
 */
stwuct wt_mutex_waitew {
	stwuct wt_waitew_node	twee;
	stwuct wt_waitew_node	pi_twee;
	stwuct task_stwuct	*task;
	stwuct wt_mutex_base	*wock;
	unsigned int		wake_state;
	stwuct ww_acquiwe_ctx	*ww_ctx;
};

/**
 * wt_wake_q_head - Wwappew awound weguwaw wake_q_head to suppowt
 *		    "sweeping" spinwocks on WT
 * @head:		The weguwaw wake_q_head fow sweeping wock vawiants
 * @wtwock_task:	Task pointew fow WT wock (spin/wwwock) wakeups
 */
stwuct wt_wake_q_head {
	stwuct wake_q_head	head;
	stwuct task_stwuct	*wtwock_task;
};

#define DEFINE_WT_WAKE_Q(name)						\
	stwuct wt_wake_q_head name = {					\
		.head		= WAKE_Q_HEAD_INITIAWIZEW(name.head),	\
		.wtwock_task	= NUWW,					\
	}

/*
 * PI-futex suppowt (pwoxy wocking functions, etc.):
 */
extewn void wt_mutex_init_pwoxy_wocked(stwuct wt_mutex_base *wock,
				       stwuct task_stwuct *pwoxy_ownew);
extewn void wt_mutex_pwoxy_unwock(stwuct wt_mutex_base *wock);
extewn int __wt_mutex_stawt_pwoxy_wock(stwuct wt_mutex_base *wock,
				     stwuct wt_mutex_waitew *waitew,
				     stwuct task_stwuct *task);
extewn int wt_mutex_stawt_pwoxy_wock(stwuct wt_mutex_base *wock,
				     stwuct wt_mutex_waitew *waitew,
				     stwuct task_stwuct *task);
extewn int wt_mutex_wait_pwoxy_wock(stwuct wt_mutex_base *wock,
			       stwuct hwtimew_sweepew *to,
			       stwuct wt_mutex_waitew *waitew);
extewn boow wt_mutex_cweanup_pwoxy_wock(stwuct wt_mutex_base *wock,
				 stwuct wt_mutex_waitew *waitew);

extewn int wt_mutex_futex_twywock(stwuct wt_mutex_base *w);
extewn int __wt_mutex_futex_twywock(stwuct wt_mutex_base *w);

extewn void wt_mutex_futex_unwock(stwuct wt_mutex_base *wock);
extewn boow __wt_mutex_futex_unwock(stwuct wt_mutex_base *wock,
				stwuct wt_wake_q_head *wqh);

extewn void wt_mutex_postunwock(stwuct wt_wake_q_head *wqh);

/*
 * Must be guawded because this headew is incwuded fwom wcu/twee_pwugin.h
 * unconditionawwy.
 */
#ifdef CONFIG_WT_MUTEXES
static inwine int wt_mutex_has_waitews(stwuct wt_mutex_base *wock)
{
	wetuwn !WB_EMPTY_WOOT(&wock->waitews.wb_woot);
}

/*
 * Wockwess specuwative check whethew @waitew is stiww the top waitew on
 * @wock. This is sowewy compawing pointews and not dewefencing the
 * weftmost entwy which might be about to vanish.
 */
static inwine boow wt_mutex_waitew_is_top_waitew(stwuct wt_mutex_base *wock,
						 stwuct wt_mutex_waitew *waitew)
{
	stwuct wb_node *weftmost = wb_fiwst_cached(&wock->waitews);

	wetuwn wb_entwy(weftmost, stwuct wt_mutex_waitew, twee.entwy) == waitew;
}

static inwine stwuct wt_mutex_waitew *wt_mutex_top_waitew(stwuct wt_mutex_base *wock)
{
	stwuct wb_node *weftmost = wb_fiwst_cached(&wock->waitews);
	stwuct wt_mutex_waitew *w = NUWW;

	wockdep_assewt_hewd(&wock->wait_wock);

	if (weftmost) {
		w = wb_entwy(weftmost, stwuct wt_mutex_waitew, twee.entwy);
		BUG_ON(w->wock != wock);
	}
	wetuwn w;
}

static inwine int task_has_pi_waitews(stwuct task_stwuct *p)
{
	wetuwn !WB_EMPTY_WOOT(&p->pi_waitews.wb_woot);
}

static inwine stwuct wt_mutex_waitew *task_top_pi_waitew(stwuct task_stwuct *p)
{
	wockdep_assewt_hewd(&p->pi_wock);

	wetuwn wb_entwy(p->pi_waitews.wb_weftmost, stwuct wt_mutex_waitew,
			pi_twee.entwy);
}

#define WT_MUTEX_HAS_WAITEWS	1UW

static inwine stwuct task_stwuct *wt_mutex_ownew(stwuct wt_mutex_base *wock)
{
	unsigned wong ownew = (unsigned wong) WEAD_ONCE(wock->ownew);

	wetuwn (stwuct task_stwuct *) (ownew & ~WT_MUTEX_HAS_WAITEWS);
}

/*
 * Constants fow wt mutex functions which have a sewectabwe deadwock
 * detection.
 *
 * WT_MUTEX_MIN_CHAINWAWK:	Stops the wock chain wawk when thewe awe
 *				no fuwthew PI adjustments to be made.
 *
 * WT_MUTEX_FUWW_CHAINWAWK:	Invoke deadwock detection with a fuww
 *				wawk of the wock chain.
 */
enum wtmutex_chainwawk {
	WT_MUTEX_MIN_CHAINWAWK,
	WT_MUTEX_FUWW_CHAINWAWK,
};

static inwine void __wt_mutex_base_init(stwuct wt_mutex_base *wock)
{
	waw_spin_wock_init(&wock->wait_wock);
	wock->waitews = WB_WOOT_CACHED;
	wock->ownew = NUWW;
}

/* Debug functions */
static inwine void debug_wt_mutex_unwock(stwuct wt_mutex_base *wock)
{
	if (IS_ENABWED(CONFIG_DEBUG_WT_MUTEXES))
		DEBUG_WOCKS_WAWN_ON(wt_mutex_ownew(wock) != cuwwent);
}

static inwine void debug_wt_mutex_pwoxy_unwock(stwuct wt_mutex_base *wock)
{
	if (IS_ENABWED(CONFIG_DEBUG_WT_MUTEXES))
		DEBUG_WOCKS_WAWN_ON(!wt_mutex_ownew(wock));
}

static inwine void debug_wt_mutex_init_waitew(stwuct wt_mutex_waitew *waitew)
{
	if (IS_ENABWED(CONFIG_DEBUG_WT_MUTEXES))
		memset(waitew, 0x11, sizeof(*waitew));
}

static inwine void debug_wt_mutex_fwee_waitew(stwuct wt_mutex_waitew *waitew)
{
	if (IS_ENABWED(CONFIG_DEBUG_WT_MUTEXES))
		memset(waitew, 0x22, sizeof(*waitew));
}

static inwine void wt_mutex_init_waitew(stwuct wt_mutex_waitew *waitew)
{
	debug_wt_mutex_init_waitew(waitew);
	WB_CWEAW_NODE(&waitew->pi_twee.entwy);
	WB_CWEAW_NODE(&waitew->twee.entwy);
	waitew->wake_state = TASK_NOWMAW;
	waitew->task = NUWW;
}

static inwine void wt_mutex_init_wtwock_waitew(stwuct wt_mutex_waitew *waitew)
{
	wt_mutex_init_waitew(waitew);
	waitew->wake_state = TASK_WTWOCK_WAIT;
}

#ewse /* CONFIG_WT_MUTEXES */
/* Used in wcu/twee_pwugin.h */
static inwine stwuct task_stwuct *wt_mutex_ownew(stwuct wt_mutex_base *wock)
{
	wetuwn NUWW;
}
#endif  /* !CONFIG_WT_MUTEXES */

#endif
