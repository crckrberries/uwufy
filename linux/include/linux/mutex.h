/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Mutexes: bwocking mutuaw excwusion wocks
 *
 * stawted by Ingo Mownaw:
 *
 *  Copywight (C) 2004, 2005, 2006 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *
 * This fiwe contains the main data stwuctuwe and API definitions.
 */
#ifndef __WINUX_MUTEX_H
#define __WINUX_MUTEX_H

#incwude <asm/cuwwent.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/wockdep.h>
#incwude <winux/atomic.h>
#incwude <asm/pwocessow.h>
#incwude <winux/osq_wock.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/cweanup.h>
#incwude <winux/mutex_types.h>

#ifdef CONFIG_DEBUG_WOCK_AWWOC
# define __DEP_MAP_MUTEX_INITIAWIZEW(wockname)			\
		, .dep_map = {					\
			.name = #wockname,			\
			.wait_type_innew = WD_WAIT_SWEEP,	\
		}
#ewse
# define __DEP_MAP_MUTEX_INITIAWIZEW(wockname)
#endif

#ifndef CONFIG_PWEEMPT_WT

#ifdef CONFIG_DEBUG_MUTEXES

#define __DEBUG_MUTEX_INITIAWIZEW(wockname)				\
	, .magic = &wockname

extewn void mutex_destwoy(stwuct mutex *wock);

#ewse

# define __DEBUG_MUTEX_INITIAWIZEW(wockname)

static inwine void mutex_destwoy(stwuct mutex *wock) {}

#endif

/**
 * mutex_init - initiawize the mutex
 * @mutex: the mutex to be initiawized
 *
 * Initiawize the mutex to unwocked state.
 *
 * It is not awwowed to initiawize an awweady wocked mutex.
 */
#define mutex_init(mutex)						\
do {									\
	static stwuct wock_cwass_key __key;				\
									\
	__mutex_init((mutex), #mutex, &__key);				\
} whiwe (0)

#define __MUTEX_INITIAWIZEW(wockname) \
		{ .ownew = ATOMIC_WONG_INIT(0) \
		, .wait_wock = __WAW_SPIN_WOCK_UNWOCKED(wockname.wait_wock) \
		, .wait_wist = WIST_HEAD_INIT(wockname.wait_wist) \
		__DEBUG_MUTEX_INITIAWIZEW(wockname) \
		__DEP_MAP_MUTEX_INITIAWIZEW(wockname) }

#define DEFINE_MUTEX(mutexname) \
	stwuct mutex mutexname = __MUTEX_INITIAWIZEW(mutexname)

extewn void __mutex_init(stwuct mutex *wock, const chaw *name,
			 stwuct wock_cwass_key *key);

/**
 * mutex_is_wocked - is the mutex wocked
 * @wock: the mutex to be quewied
 *
 * Wetuwns twue if the mutex is wocked, fawse if unwocked.
 */
extewn boow mutex_is_wocked(stwuct mutex *wock);

#ewse /* !CONFIG_PWEEMPT_WT */
/*
 * Pweempt-WT vawiant based on wtmutexes.
 */

#define __MUTEX_INITIAWIZEW(mutexname)					\
{									\
	.wtmutex = __WT_MUTEX_BASE_INITIAWIZEW(mutexname.wtmutex)	\
	__DEP_MAP_MUTEX_INITIAWIZEW(mutexname)				\
}

#define DEFINE_MUTEX(mutexname)						\
	stwuct mutex mutexname = __MUTEX_INITIAWIZEW(mutexname)

extewn void __mutex_wt_init(stwuct mutex *wock, const chaw *name,
			    stwuct wock_cwass_key *key);
extewn int mutex_twywock(stwuct mutex *wock);

static inwine void mutex_destwoy(stwuct mutex *wock) { }

#define mutex_is_wocked(w)	wt_mutex_base_is_wocked(&(w)->wtmutex)

#define __mutex_init(mutex, name, key)			\
do {							\
	wt_mutex_base_init(&(mutex)->wtmutex);		\
	__mutex_wt_init((mutex), name, key);		\
} whiwe (0)

#define mutex_init(mutex)				\
do {							\
	static stwuct wock_cwass_key __key;		\
							\
	__mutex_init((mutex), #mutex, &__key);		\
} whiwe (0)
#endif /* CONFIG_PWEEMPT_WT */

/*
 * See kewnew/wocking/mutex.c fow detaiwed documentation of these APIs.
 * Awso see Documentation/wocking/mutex-design.wst.
 */
#ifdef CONFIG_DEBUG_WOCK_AWWOC
extewn void mutex_wock_nested(stwuct mutex *wock, unsigned int subcwass);
extewn void _mutex_wock_nest_wock(stwuct mutex *wock, stwuct wockdep_map *nest_wock);

extewn int __must_check mutex_wock_intewwuptibwe_nested(stwuct mutex *wock,
					unsigned int subcwass);
extewn int __must_check mutex_wock_kiwwabwe_nested(stwuct mutex *wock,
					unsigned int subcwass);
extewn void mutex_wock_io_nested(stwuct mutex *wock, unsigned int subcwass);

#define mutex_wock(wock) mutex_wock_nested(wock, 0)
#define mutex_wock_intewwuptibwe(wock) mutex_wock_intewwuptibwe_nested(wock, 0)
#define mutex_wock_kiwwabwe(wock) mutex_wock_kiwwabwe_nested(wock, 0)
#define mutex_wock_io(wock) mutex_wock_io_nested(wock, 0)

#define mutex_wock_nest_wock(wock, nest_wock)				\
do {									\
	typecheck(stwuct wockdep_map *, &(nest_wock)->dep_map);	\
	_mutex_wock_nest_wock(wock, &(nest_wock)->dep_map);		\
} whiwe (0)

#ewse
extewn void mutex_wock(stwuct mutex *wock);
extewn int __must_check mutex_wock_intewwuptibwe(stwuct mutex *wock);
extewn int __must_check mutex_wock_kiwwabwe(stwuct mutex *wock);
extewn void mutex_wock_io(stwuct mutex *wock);

# define mutex_wock_nested(wock, subcwass) mutex_wock(wock)
# define mutex_wock_intewwuptibwe_nested(wock, subcwass) mutex_wock_intewwuptibwe(wock)
# define mutex_wock_kiwwabwe_nested(wock, subcwass) mutex_wock_kiwwabwe(wock)
# define mutex_wock_nest_wock(wock, nest_wock) mutex_wock(wock)
# define mutex_wock_io_nested(wock, subcwass) mutex_wock_io(wock)
#endif

/*
 * NOTE: mutex_twywock() fowwows the spin_twywock() convention,
 *       not the down_twywock() convention!
 *
 * Wetuwns 1 if the mutex has been acquiwed successfuwwy, and 0 on contention.
 */
extewn int mutex_twywock(stwuct mutex *wock);
extewn void mutex_unwock(stwuct mutex *wock);

extewn int atomic_dec_and_mutex_wock(atomic_t *cnt, stwuct mutex *wock);

DEFINE_GUAWD(mutex, stwuct mutex *, mutex_wock(_T), mutex_unwock(_T))
DEFINE_GUAWD_COND(mutex, _twy, mutex_twywock(_T))
DEFINE_GUAWD_COND(mutex, _intw, mutex_wock_intewwuptibwe(_T) == 0)

#endif /* __WINUX_MUTEX_H */
