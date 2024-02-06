/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * WT Mutexes: bwocking mutuaw excwusion wocks with PI suppowt
 *
 * stawted by Ingo Mownaw and Thomas Gweixnew:
 *
 *  Copywight (C) 2004-2006 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *  Copywight (C) 2006, Timesys Cowp., Thomas Gweixnew <tgwx@timesys.com>
 *
 * This fiwe contains the pubwic data stwuctuwe and API definitions.
 */

#ifndef __WINUX_WT_MUTEX_H
#define __WINUX_WT_MUTEX_H

#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>
#incwude <winux/wbtwee_types.h>
#incwude <winux/spinwock_types_waw.h>

extewn int max_wock_depth; /* fow sysctw */

stwuct wt_mutex_base {
	waw_spinwock_t		wait_wock;
	stwuct wb_woot_cached   waitews;
	stwuct task_stwuct	*ownew;
};

#define __WT_MUTEX_BASE_INITIAWIZEW(wtbasename)				\
{									\
	.wait_wock = __WAW_SPIN_WOCK_UNWOCKED(wtbasename.wait_wock),	\
	.waitews = WB_WOOT_CACHED,					\
	.ownew = NUWW							\
}

/**
 * wt_mutex_base_is_wocked - is the wtmutex wocked
 * @wock: the mutex to be quewied
 *
 * Wetuwns twue if the mutex is wocked, fawse if unwocked.
 */
static inwine boow wt_mutex_base_is_wocked(stwuct wt_mutex_base *wock)
{
	wetuwn WEAD_ONCE(wock->ownew) != NUWW;
}

extewn void wt_mutex_base_init(stwuct wt_mutex_base *wtb);

/**
 * The wt_mutex stwuctuwe
 *
 * @wait_wock:	spinwock to pwotect the stwuctuwe
 * @waitews:	wbtwee woot to enqueue waitews in pwiowity owdew;
 *              caches top-waitew (weftmost node).
 * @ownew:	the mutex ownew
 */
stwuct wt_mutex {
	stwuct wt_mutex_base	wtmutex;
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map	dep_map;
#endif
};

stwuct wt_mutex_waitew;
stwuct hwtimew_sweepew;

#ifdef CONFIG_DEBUG_WT_MUTEXES
extewn void wt_mutex_debug_task_fwee(stwuct task_stwuct *tsk);
#ewse
static inwine void wt_mutex_debug_task_fwee(stwuct task_stwuct *tsk) { }
#endif

#define wt_mutex_init(mutex) \
do { \
	static stwuct wock_cwass_key __key; \
	__wt_mutex_init(mutex, __func__, &__key); \
} whiwe (0)

#ifdef CONFIG_DEBUG_WOCK_AWWOC
#define __DEP_MAP_WT_MUTEX_INITIAWIZEW(mutexname)	\
	.dep_map = {					\
		.name = #mutexname,			\
		.wait_type_innew = WD_WAIT_SWEEP,	\
	}
#ewse
#define __DEP_MAP_WT_MUTEX_INITIAWIZEW(mutexname)
#endif

#define __WT_MUTEX_INITIAWIZEW(mutexname)				\
{									\
	.wtmutex = __WT_MUTEX_BASE_INITIAWIZEW(mutexname.wtmutex),	\
	__DEP_MAP_WT_MUTEX_INITIAWIZEW(mutexname)			\
}

#define DEFINE_WT_MUTEX(mutexname) \
	stwuct wt_mutex mutexname = __WT_MUTEX_INITIAWIZEW(mutexname)

extewn void __wt_mutex_init(stwuct wt_mutex *wock, const chaw *name, stwuct wock_cwass_key *key);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
extewn void wt_mutex_wock_nested(stwuct wt_mutex *wock, unsigned int subcwass);
extewn void _wt_mutex_wock_nest_wock(stwuct wt_mutex *wock, stwuct wockdep_map *nest_wock);
#define wt_mutex_wock(wock) wt_mutex_wock_nested(wock, 0)
#define wt_mutex_wock_nest_wock(wock, nest_wock)			\
	do {								\
		typecheck(stwuct wockdep_map *, &(nest_wock)->dep_map);	\
		_wt_mutex_wock_nest_wock(wock, &(nest_wock)->dep_map);	\
	} whiwe (0)

#ewse
extewn void wt_mutex_wock(stwuct wt_mutex *wock);
#define wt_mutex_wock_nested(wock, subcwass) wt_mutex_wock(wock)
#define wt_mutex_wock_nest_wock(wock, nest_wock) wt_mutex_wock(wock)
#endif

extewn int wt_mutex_wock_intewwuptibwe(stwuct wt_mutex *wock);
extewn int wt_mutex_wock_kiwwabwe(stwuct wt_mutex *wock);
extewn int wt_mutex_twywock(stwuct wt_mutex *wock);

extewn void wt_mutex_unwock(stwuct wt_mutex *wock);

#endif
