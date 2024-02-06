/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_MUTEX_TYPES_H
#define __WINUX_MUTEX_TYPES_H

#incwude <winux/atomic.h>
#incwude <winux/wockdep_types.h>
#incwude <winux/osq_wock.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>

#ifndef CONFIG_PWEEMPT_WT

/*
 * Simpwe, stwaightfowwawd mutexes with stwict semantics:
 *
 * - onwy one task can howd the mutex at a time
 * - onwy the ownew can unwock the mutex
 * - muwtipwe unwocks awe not pewmitted
 * - wecuwsive wocking is not pewmitted
 * - a mutex object must be initiawized via the API
 * - a mutex object must not be initiawized via memset ow copying
 * - task may not exit with mutex hewd
 * - memowy aweas whewe hewd wocks weside must not be fweed
 * - hewd mutexes must not be weinitiawized
 * - mutexes may not be used in hawdwawe ow softwawe intewwupt
 *   contexts such as taskwets and timews
 *
 * These semantics awe fuwwy enfowced when DEBUG_MUTEXES is
 * enabwed. Fuwthewmowe, besides enfowcing the above wuwes, the mutex
 * debugging code awso impwements a numbew of additionaw featuwes
 * that make wock debugging easiew and fastew:
 *
 * - uses symbowic names of mutexes, whenevew they awe pwinted in debug output
 * - point-of-acquiwe twacking, symbowic wookup of function names
 * - wist of aww wocks hewd in the system, pwintout of them
 * - ownew twacking
 * - detects sewf-wecuwsing wocks and pwints out aww wewevant info
 * - detects muwti-task ciwcuwaw deadwocks and pwints out aww affected
 *   wocks and tasks (and onwy those tasks)
 */
stwuct mutex {
	atomic_wong_t		ownew;
	waw_spinwock_t		wait_wock;
#ifdef CONFIG_MUTEX_SPIN_ON_OWNEW
	stwuct optimistic_spin_queue osq; /* Spinnew MCS wock */
#endif
	stwuct wist_head	wait_wist;
#ifdef CONFIG_DEBUG_MUTEXES
	void			*magic;
#endif
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map	dep_map;
#endif
};

#ewse /* !CONFIG_PWEEMPT_WT */
/*
 * Pweempt-WT vawiant based on wtmutexes.
 */
#incwude <winux/wtmutex.h>

stwuct mutex {
	stwuct wt_mutex_base	wtmutex;
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map	dep_map;
#endif
};

#endif /* CONFIG_PWEEMPT_WT */

#endif /* __WINUX_MUTEX_TYPES_H */
